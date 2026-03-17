/* player_start_reload @ 00413430 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* starts reload for the active player, sets timers, and plays SFX */

void player_start_reload(void)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  if (((char)(&player_state_table)[render_overlay_player_index].reload_active == '\0') ||
     ((iVar3 = perk_count_get(perk_id_ammunition_within), iVar3 == 0 &&
      (iVar3 = perk_count_get(perk_id_regression_bullets), iVar3 == 0)))) {
    iVar3 = render_overlay_player_index;
    if ((char)(&player_state_table)[render_overlay_player_index].reload_active == '\0') {
      sfx_play_panned((float)(&weapon_table)
                             [(&player_state_table)[render_overlay_player_index].weapon_id].
                             reload_sfx_id);
      iVar3 = render_overlay_player_index;
      *(undefined1 *)&(&player_state_table)[render_overlay_player_index].reload_active = 1;
    }
    iVar2 = perk_id_fastloader;
    fVar1 = (&weapon_table)[(&player_state_table)[iVar3].weapon_id].reload_time;
    (&player_state_table)[iVar3].reload_timer = fVar1;
    if (0 < player_state_table.perk_counts[iVar2]) {
      (&player_state_table)[iVar3].reload_timer = fVar1 * 0.7;
    }
    if (0.0 < bonus_weapon_power_up_timer) {
      (&player_state_table)[iVar3].reload_timer = (&player_state_table)[iVar3].reload_timer * 0.6;
    }
    (&player_state_table)[iVar3].reload_timer_max = (&player_state_table)[iVar3].reload_timer;
  }
  return;
}



/* player_update @ 004136b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* per-player gameplay update: movement, firing, status timers, and effects */

void player_update(void)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  player_state_t *ppVar6;
  int iVar7;
  bool bVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  creature_t *pcVar13;
  float fVar14;
  float *unaff_EBP;
  float fVar15;
  int iVar16;
  float *pfVar17;
  float10 fVar18;
  float10 fVar19;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  longlong lVar20;
  float *player_index;
  projectile_type_id_t pVar21;
  float *delta;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_30 [2];
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar7 = render_overlay_player_index;
  if (console_open_flag != '\0') {
    return;
  }
  (&player_aim_screen_x)[render_overlay_player_index * 2] = ui_mouse_x;
  (&player_aim_screen_y)[iVar7 * 2] = ui_mouse_y;
  local_28 = (&player_state_table)[iVar7].pos_x;
  pfVar17 = &(&player_state_table)[iVar7].pos_x;
  local_24 = (&player_state_table)[iVar7].pos_y;
  if ((&player_state_table)[iVar7].health <= 0.0) {
    (&player_state_table)[iVar7].death_timer =
         (&player_state_table)[iVar7].death_timer - frame_dt * 20.0;
    return;
  }
  if (0.0 < (&player_state_table)[iVar7].speed_bonus_timer) {
    (&player_state_table)[iVar7].speed_multiplier =
         (&player_state_table)[iVar7].speed_multiplier + 1.0;
  }
  if ((((&player_state_table)[iVar7].low_health_timer != 100.0) &&
      ((&player_state_table)[iVar7].health < 20.0)) &&
     (fVar15 = (&player_state_table)[iVar7].low_health_timer - frame_dt,
     (&player_state_table)[iVar7].low_health_timer = fVar15, fVar15 < 0.0)) {
    fVar18 = (float10)fcos(((float10)(&player_state_table)[iVar7].aim_heading + (float10)1.5707964)
                           - (float10)0.5);
    fVar19 = (float10)fsin(((float10)(&player_state_table)[iVar7].aim_heading + (float10)1.5707964)
                           - (float10)0.5);
    fVar15 = (&player_state_table)[iVar7].aim_heading;
    local_18 = (float)(fVar18 * (float10)-6.0 + (float10)*pfVar17);
    local_14 = (float)(fVar19 * (float10)-6.0) + (&player_state_table)[iVar7].pos_y;
    effect_spawn_blood_splatter(&local_18,fVar15,0.0);
    effect_spawn_blood_splatter(&local_18,fVar15,0.0);
    effect_spawn_blood_splatter(&local_18,fVar15,0.0);
    uVar9 = crt_rand();
    sfx_play_panned((float)((uVar9 & 1) + sfx_bloodspill_01));
    (&player_state_table)[iVar7].low_health_timer = 1.0;
  }
  pfVar1 = &(&player_state_table)[iVar7].muzzle_flash_alpha;
  fVar15 = *pfVar1 - (frame_dt + frame_dt);
  *pfVar1 = fVar15;
  if (fVar15 < 0.0) {
    *pfVar1 = 0.0;
  }
  if (bonus_weapon_power_up_timer <= 0.0) {
    fVar15 = (&player_state_table)[iVar7].shot_cooldown - frame_dt;
  }
  else {
    fVar15 = (&player_state_table)[iVar7].shot_cooldown - frame_dt * 1.5;
  }
  (&player_state_table)[iVar7].shot_cooldown = fVar15;
  if ((&player_state_table)[iVar7].shot_cooldown < 0.0) {
    (&player_state_table)[iVar7].shot_cooldown = 0.0;
  }
  iVar10 = perk_count_get(perk_id_man_bomb);
  if (iVar10 == 0) {
    (&player_state_table)[iVar7].man_bomb_timer = 0.0;
  }
  else {
    fVar15 = frame_dt + (&player_state_table)[iVar7].man_bomb_timer;
    (&player_state_table)[iVar7].man_bomb_timer = fVar15;
    if (man_bomb_cooldown_threshold < fVar15) {
      if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
        iVar10 = -100;
      }
      else {
        iVar10 = -1 - render_overlay_player_index;
      }
      local_38 = 0.0;
      do {
        iVar16 = iVar10;
        if (((uint)local_38 & 1) == 0) {
          pVar21 = PROJECTILE_TYPE_ION_MINIGUN;
          iVar11 = crt_rand();
        }
        else {
          pVar21 = PROJECTILE_TYPE_ION_RIFLE;
          iVar11 = crt_rand();
        }
        projectile_spawn(pfVar17,((float)(int)local_38 * 0.7853982 + (float)(iVar11 % 0x32) * 0.01)
                                 - 0.25,pVar21,iVar16);
        local_38 = (float)((int)local_38 + 1);
      } while ((int)local_38 < 8);
      sfx_play_panned(sfx_explosion_small);
      (&player_state_table)[iVar7].man_bomb_timer =
           (&player_state_table)[iVar7].man_bomb_timer - man_bomb_cooldown_threshold;
      man_bomb_cooldown_threshold = 4.0;
    }
  }
  iVar10 = perk_count_get(perk_id_living_fortress);
  if (iVar10 == 0) {
    (&player_state_table)[iVar7].living_fortress_timer = 0.0;
  }
  else {
    fVar15 = frame_dt + (&player_state_table)[iVar7].living_fortress_timer;
    (&player_state_table)[iVar7].living_fortress_timer = fVar15;
    if (30.0 < fVar15) {
      (&player_state_table)[iVar7].living_fortress_timer = 30.0;
    }
  }
  iVar10 = perk_count_get(perk_id_fire_cough);
  if (iVar10 == 0) {
    (&player_state_table)[iVar7].fire_cough_timer = 0.0;
  }
  else {
    fVar15 = frame_dt + (&player_state_table)[iVar7].fire_cough_timer;
    (&player_state_table)[iVar7].fire_cough_timer = fVar15;
    if (fire_cough_cooldown_threshold < fVar15) {
      if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
        local_40 = -NAN;
      }
      else {
        local_40 = (float)(-1 - render_overlay_player_index);
      }
      sfx_play_panned(sfx_player_fire_reload_a);
      sfx_play_panned(sfx_player_fire_reload_b);
      iVar10 = render_overlay_player_index;
      fVar15 = (&player_state_table)[iVar7].aim_heading;
      fVar18 = ((float10)fVar15 - (float10)1.5707964) - (float10)0.150915;
      fVar19 = (float10)fcos(fVar18);
      local_1c = (&player_state_table)[render_overlay_player_index].aim_y;
      local_20 = (&player_state_table)[render_overlay_player_index].aim_x;
      ppVar6 = &player_state_table + render_overlay_player_index;
      local_18 = (float)(fVar19 * (float10)16.0);
      fVar18 = (float10)fsin(fVar18);
      local_14 = (float)(fVar18 * (float10)16.0);
      local_c = local_1c - (&player_state_table)[render_overlay_player_index].pos_y;
      local_10 = local_20 - ppVar6->pos_x;
      local_30[0] = vec2_length(&local_10);
      local_30[0] = local_30[0] * 0.5;
      uVar9 = crt_rand();
      fVar14 = (float)(uVar9 & 0x1ff) * 0.012271847;
      uVar9 = crt_rand();
      local_44 = (float)(uVar9 & 0x1ff);
      fVar18 = (float10)local_30[0] * (float10)(&player_state_table)[iVar10].spread_heat *
               (float10)(int)local_44 * (float10)0.001953125;
      fVar19 = (float10)fcos((float10)fVar14);
      local_20 = (float)(fVar19 * fVar18 + (float10)local_20);
      fVar19 = (float10)fsin((float10)fVar14);
      local_1c = (float)(fVar19 * fVar18 + (float10)local_1c);
      pfVar12 = vec2_sub(&ppVar6->pos_x,local_30,&local_20,unaff_EBP);
      fVar18 = (float10)fpatan((float10)pfVar12[1],(float10)*pfVar12);
      local_30[0] = (float)(fVar18 - (float10)1.5707964);
      local_c = local_14 + (&player_state_table)[iVar7].pos_y;
      local_10 = local_18 + *pfVar17;
      projectile_spawn(&local_10,local_30[0],PROJECTILE_TYPE_FIRE_BULLETS,(int)local_40);
      fVar18 = (float10)fcos((float10)fVar15);
      local_10 = (float)(fVar18 * (float10)25.0);
      fVar18 = (float10)fsin((float10)fVar15);
      local_c = (float)(fVar18 * (float10)25.0);
      local_14 = local_14 + (&player_state_table)[iVar7].pos_y;
      local_18 = local_18 + *pfVar17;
      iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
      (&sprite_effect_pool)[iVar10].color_r = 0.5;
      (&sprite_effect_pool)[iVar10].color_g = 0.5;
      (&sprite_effect_pool)[iVar10].color_b = 0.5;
      (&sprite_effect_pool)[iVar10].color_a = 0.413;
      (&player_state_table)[iVar7].fire_cough_timer =
           (&player_state_table)[iVar7].fire_cough_timer - fire_cough_cooldown_threshold;
      uVar9 = crt_rand();
      local_30[0] = (float)(uVar9 & 0x80000003);
      if ((int)local_30[0] < 0) {
        local_30[0] = (float)(((int)local_30[0] - 1U | 0xfffffffc) + 1);
      }
      fire_cough_cooldown_threshold = (float)(int)local_30[0] + 2.0;
    }
  }
  iVar10 = perk_count_get(perk_id_hot_tempered);
  if (iVar10 == 0) {
    (&player_state_table)[iVar7].hot_tempered_timer = 0.0;
  }
  else {
    fVar15 = frame_dt + (&player_state_table)[iVar7].hot_tempered_timer;
    (&player_state_table)[iVar7].hot_tempered_timer = fVar15;
    if (hot_tempered_cooldown_threshold < fVar15) {
      if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
        iVar10 = -100;
      }
      else {
        iVar10 = -1 - render_overlay_player_index;
      }
      local_38 = 0.0;
      do {
        if (((uint)local_38 & 1) == 0) {
          pVar21 = PROJECTILE_TYPE_PLASMA_MINIGUN;
        }
        else {
          pVar21 = PROJECTILE_TYPE_PLASMA_RIFLE;
        }
        projectile_spawn(pfVar17,(float)(int)local_38 * 0.7853982,pVar21,iVar10);
        local_38 = (float)((int)local_38 + 1);
      } while ((int)local_38 < 8);
      sfx_play_panned(sfx_explosion_small);
      (&player_state_table)[iVar7].hot_tempered_timer =
           (&player_state_table)[iVar7].hot_tempered_timer - hot_tempered_cooldown_threshold;
      uVar9 = crt_rand();
      local_30[0] = (float)(uVar9 & 0x80000007);
      if ((int)local_30[0] < 0) {
        local_30[0] = (float)(((int)local_30[0] - 1U | 0xfffffff8) + 1);
      }
      hot_tempered_cooldown_threshold = (float)(int)local_30[0] + 2.0;
    }
  }
  if (movement_boost_timer <= 0.0) {
    movement_decay_rate = frame_dt * 0.8 + movement_decay_rate;
    if (1.0 < movement_decay_rate) {
      movement_decay_rate = 1.0;
    }
  }
  else {
    movement_decay_rate = movement_decay_rate - frame_dt;
    if (movement_decay_rate < 0.3) {
      movement_decay_rate = 0.3;
    }
  }
  fVar15 = (&player_state_table)[iVar7].speed_multiplier;
  local_18 = 0.0;
  local_14 = 0.0;
  (&player_state_table)[iVar7].move_dx = 0.0;
  (&player_state_table)[iVar7].move_dy = 0.0;
  if (time_scale_active != '\0') {
    frame_dt = (0.6 / time_scale_factor) * frame_dt;
  }
  pfVar12 = pfVar17;
  if (((demo_mode_active == '\0') &&
      (*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c) != 5)) &&
     (*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x44) != 5)) {
LAB_00413f2d:
    iVar10 = *(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c);
    if (iVar10 == 5) goto LAB_00414c7f;
    if (iVar10 == 4) {
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(config_blob.key_reload);
      if ((char)iVar10 != '\0') {
        local_14 = (float)(&player_aim_screen_y)[render_overlay_player_index * 2] - camera_offset_y
        ;
        local_18 = (float)(&player_aim_screen_x)[render_overlay_player_index * 2] - camera_offset_x
        ;
        (&player_state_table)[iVar7].move_target_x = local_18;
        (&player_state_table)[iVar7].move_target_y = local_14;
      }
      if ((&player_state_table)[iVar7].move_target_x == -1.0) {
LAB_0041412c:
        fVar14 = (&player_state_table)[iVar7].move_speed - frame_dt * 15.0;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (fVar14 < 0.0) {
          (&player_state_table)[iVar7].move_speed = 0.0;
        }
        delta = &local_10;
        fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
        player_index = (float *)render_overlay_player_index;
        goto LAB_00414f1c;
      }
      fVar18 = (float10)(&player_state_table)[iVar7].pos_y -
               (float10)(&player_state_table)[iVar7].move_target_y;
      fVar19 = (float10)*pfVar17 - (float10)(&player_state_table)[iVar7].move_target_x;
      if (SQRT(fVar18 * fVar18 + fVar19 * fVar19) <= (float10)20.0) goto LAB_0041412c;
      fVar18 = (float10)fpatan(fVar18,fVar19);
      fVar18 = fVar18 - (float10)1.5707964;
      if (fVar18 < (float10)0.0) {
        do {
          fVar18 = fVar18 + (float10)6.2831855;
        } while (fVar18 < (float10)0.0);
      }
      local_38 = (float)fVar18;
      if (fVar18 == (float10)-1.0) goto LAB_0041412c;
      fVar18 = (float10)heading_normalize_or_calc(local_38);
      if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
        fVar14 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (2.0 < fVar14) {
          (&player_state_table)[iVar7].move_speed = 2.0;
        }
      }
      else {
        if ((&player_state_table)[iVar7].move_speed < 2.0) {
          (&player_state_table)[iVar7].move_speed =
               frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
        }
        fVar14 = frame_dt + (&player_state_table)[iVar7].move_speed;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (2.8 < fVar14) {
          (&player_state_table)[iVar7].move_speed = 2.8;
        }
      }
      if (((&player_state_table)[iVar7].weapon_id == 7) &&
         (0.8 < (&player_state_table)[iVar7].move_speed)) {
        (&player_state_table)[iVar7].move_speed = 0.8;
      }
      fVar19 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dx =
           (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                   (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                  (float10)7.957747);
      fVar19 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dy =
           (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                   (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                  (float10)7.957747);
      local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
      local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
      goto LAB_00414f13;
    }
    if (iVar10 == 3) {
      (*grim_interface_ptr->vtable->grim_get_config_float)
                ((&player_state_table)[iVar7].input.axis_move_y);
      fVar14 = (float)-extraout_ST0;
      (*grim_interface_ptr->vtable->grim_get_config_float)
                ((&player_state_table)[iVar7].input.axis_move_x);
      local_20 = (float)-extraout_ST0_00;
      local_1c = fVar14;
      if (SQRT(fVar14 * fVar14 + local_20 * local_20) <= 0.2) {
LAB_00414390:
        fVar14 = (&player_state_table)[iVar7].move_speed - frame_dt * 15.0;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (fVar14 < 0.0) {
          (&player_state_table)[iVar7].move_speed = 0.0;
        }
        delta = &local_10;
        fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
        player_index = (float *)render_overlay_player_index;
        pfVar12 = pfVar17;
      }
      else {
        delta = &local_20;
        pfVar12 = &local_20;
        player_aim_update_thunk();
        fVar18 = (float10)fpatan((float10)local_24,(float10)local_28);
        fVar18 = fVar18 - (float10)1.5707964;
        if (fVar18 < (float10)0.0) {
          do {
            fVar18 = fVar18 + (float10)6.2831855;
          } while (fVar18 < (float10)0.0);
        }
        local_40 = (float)fVar18;
        if (fVar18 == (float10)-1.0) goto LAB_00414390;
        fVar18 = (float10)heading_normalize_or_calc(local_40);
        if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
          fVar15 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar15;
          if (2.0 < fVar15) {
            (&player_state_table)[iVar7].move_speed = 2.0;
          }
        }
        else {
          if ((&player_state_table)[iVar7].move_speed < 2.0) {
            (&player_state_table)[iVar7].move_speed =
                 frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
          }
          fVar15 = frame_dt + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar15;
          if (2.8 < fVar15) {
            (&player_state_table)[iVar7].move_speed = 2.8;
          }
        }
        if (((&player_state_table)[iVar7].weapon_id == 7) &&
           (0.8 < (&player_state_table)[iVar7].move_speed)) {
          (&player_state_table)[iVar7].move_speed = 0.8;
        }
        local_40 = (float)((float10)3.1415927 - fVar18);
        fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)local_40 *
                     (float10)local_44 * (float10)7.957747);
        fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)local_40 *
                     (float10)local_44 * (float10)7.957747);
        local_14 = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_18 = frame_dt * (&player_state_table)[iVar7].move_dx;
        player_index = &local_18;
      }
      goto LAB_00414f1c;
    }
    if (iVar10 == 1) {
      bVar4 = false;
      if ((&player_state_table)[iVar7].turn_speed < 1.0) {
        (&player_state_table)[iVar7].turn_speed = 1.0;
      }
      if (7.0 < (&player_state_table)[iVar7].turn_speed) {
        (&player_state_table)[iVar7].turn_speed = 7.0;
      }
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.turn_key_left);
      if ((char)iVar10 == '\0') {
        if (config_blob.reserved0._20_4_ == 1) {
          iVar10 = (*grim_interface_ptr->vtable->grim_is_key_down)
                             (CONCAT31((int3)((uint)iVar10 >> 8),
                                       (undefined1)player_alt_turn_key_left));
          if ((char)iVar10 != '\0') goto LAB_00414520;
        }
        iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                           ((&player_state_table)[iVar7].input.turn_key_right);
        if ((char)iVar10 != '\0') {
LAB_004144dc:
          fVar14 = frame_dt * 10.0 + (&player_state_table)[iVar7].turn_speed;
          (&player_state_table)[iVar7].turn_speed = fVar14;
          (&player_state_table)[iVar7].heading =
               fVar14 * frame_dt * 0.5 + (&player_state_table)[iVar7].heading;
          fVar14 = frame_dt * (&player_state_table)[iVar7].turn_speed * 0.5 +
                   (&player_state_table)[iVar7].aim_heading;
          goto LAB_00414562;
        }
        if (config_blob.reserved0._20_4_ == 1) {
          iVar10 = (*grim_interface_ptr->vtable->grim_is_key_down)
                             (CONCAT31((int3)((uint)iVar10 >> 8),
                                       (undefined1)player_alt_turn_key_right));
          if ((char)iVar10 != '\0') goto LAB_004144dc;
        }
      }
      else {
LAB_00414520:
        fVar14 = frame_dt * 10.0 + (&player_state_table)[iVar7].turn_speed;
        (&player_state_table)[iVar7].turn_speed = fVar14;
        (&player_state_table)[iVar7].heading =
             (&player_state_table)[iVar7].heading - fVar14 * frame_dt * 0.5;
        fVar14 = (&player_state_table)[iVar7].aim_heading -
                 frame_dt * (&player_state_table)[iVar7].turn_speed * 0.5;
LAB_00414562:
        (&player_state_table)[iVar7].aim_heading = fVar14;
        bVar4 = true;
      }
      local_38 = 1.0;
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.move_key_forward);
      if ((char)iVar10 == '\0') {
        if (config_blob.reserved0._20_4_ == 1) {
          iVar10 = (*grim_interface_ptr->vtable->grim_is_key_down)
                             (CONCAT31((int3)((uint)iVar10 >> 8),
                                       (undefined1)player_alt_move_key_forward));
          if ((char)iVar10 != '\0') goto LAB_00414750;
        }
        iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                           ((&player_state_table)[iVar7].input.move_key_backward);
        if ((char)iVar10 == '\0') {
          if (config_blob.reserved0._20_4_ == 1) {
            iVar10 = (*grim_interface_ptr->vtable->grim_is_key_down)
                               (CONCAT31((int3)((uint)iVar10 >> 8),
                                         (undefined1)player_alt_move_key_backward));
            if ((char)iVar10 != '\0') goto LAB_0041467b;
          }
          if (!bVar4) {
            (&player_state_table)[iVar7].turn_speed = 1.0;
          }
          fVar14 = (&player_state_table)[iVar7].move_speed - frame_dt * 15.0;
          (&player_state_table)[iVar7].move_speed = fVar14;
          if (fVar14 < 0.0) {
            (&player_state_table)[iVar7].move_speed = 0.0;
          }
          fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964)
          ;
          (&player_state_table)[iVar7].move_dx =
               (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                      (float10)25.0);
          fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964)
          ;
          (&player_state_table)[iVar7].move_dy =
               (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                      (float10)25.0);
          local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
          local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
        }
        else {
LAB_0041467b:
          if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
            fVar14 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
            (&player_state_table)[iVar7].move_speed = fVar14;
            if (2.0 < fVar14) {
              (&player_state_table)[iVar7].move_speed = 2.0;
            }
          }
          else {
            if ((&player_state_table)[iVar7].move_speed < 2.0) {
              (&player_state_table)[iVar7].move_speed =
                   frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
            }
            fVar14 = frame_dt + (&player_state_table)[iVar7].move_speed;
            (&player_state_table)[iVar7].move_speed = fVar14;
            if (2.8 < fVar14) {
              (&player_state_table)[iVar7].move_speed = 2.8;
            }
          }
          local_38 = -1.0;
          fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964)
          ;
          (&player_state_table)[iVar7].move_dx =
               (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                      (float10)-25.0);
          fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964)
          ;
          (&player_state_table)[iVar7].move_dy =
               (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                      (float10)-25.0);
          local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
          local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
        }
      }
      else {
LAB_00414750:
        if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
          fVar14 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar14;
          if (2.0 < fVar14) {
            (&player_state_table)[iVar7].move_speed = 2.0;
          }
        }
        else {
          if ((&player_state_table)[iVar7].move_speed < 2.0) {
            (&player_state_table)[iVar7].move_speed =
                 frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
          }
          fVar14 = frame_dt + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar14;
          if (2.8 < fVar14) {
            (&player_state_table)[iVar7].move_speed = 2.8;
          }
        }
        if (((&player_state_table)[iVar7].weapon_id == 7) &&
           (0.8 < (&player_state_table)[iVar7].move_speed)) {
          (&player_state_table)[iVar7].move_speed = 0.8;
        }
        fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
      }
      player_apply_move_with_spawn_avoidance(render_overlay_player_index,pfVar17,&local_10);
      fVar15 = local_38 * (&player_state_table)[iVar7].move_speed * frame_dt;
      goto LAB_00414f2d;
    }
    if (iVar10 == 2) {
      local_40 = -1.0;
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.turn_key_left);
      if (((char)iVar10 != '\0') ||
         ((config_blob.reserved0._20_4_ == 1 &&
          (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_left),
          (char)iVar10 != '\0')))) {
        local_40 = 4.712389;
      }
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.turn_key_right);
      if (((char)iVar10 != '\0') ||
         ((config_blob.reserved0._20_4_ == 1 &&
          (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_right),
          (char)iVar10 != '\0')))) {
        local_40 = 1.5707964;
      }
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.move_key_forward);
      if (((char)iVar10 != '\0') ||
         ((config_blob.reserved0._20_4_ == 1 &&
          (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_move_key_forward),
          (char)iVar10 != '\0')))) {
        iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                           ((&player_state_table)[iVar7].input.turn_key_left);
        if (((char)iVar10 == '\0') &&
           ((config_blob.reserved0._20_4_ != 1 ||
            (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_left),
            (char)iVar10 == '\0')))) {
          iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                             ((&player_state_table)[iVar7].input.turn_key_right);
          if (((char)iVar10 == '\0') &&
             ((config_blob.reserved0._20_4_ != 1 ||
              (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_right)
              , (char)iVar10 == '\0')))) {
            local_40 = 0.0;
          }
          else {
            local_40 = 0.7853982;
          }
        }
        else {
          local_40 = 5.4977875;
        }
      }
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                         ((&player_state_table)[iVar7].input.move_key_backward);
      if (((char)iVar10 == '\0') &&
         ((config_blob.reserved0._20_4_ != 1 ||
          (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_move_key_backward),
          (char)iVar10 == '\0')))) {
        if (local_40 != -1.0) goto LAB_00414aab;
        fVar14 = (&player_state_table)[iVar7].move_speed - frame_dt * 15.0;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (fVar14 < 0.0) {
          (&player_state_table)[iVar7].move_speed = 0.0;
        }
        fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                    (float10)25.0);
        local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
      }
      else {
        iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                           ((&player_state_table)[iVar7].input.turn_key_left);
        if (((char)iVar10 == '\0') &&
           ((config_blob.reserved0._20_4_ != 1 ||
            (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_left),
            (char)iVar10 == '\0')))) {
          iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                             ((&player_state_table)[iVar7].input.turn_key_right);
          if (((char)iVar10 == '\0') &&
             ((config_blob.reserved0._20_4_ != 1 ||
              (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(player_alt_turn_key_right)
              , (char)iVar10 == '\0')))) {
            local_40 = 3.1415927;
          }
          else {
            local_40 = 2.3561945;
          }
        }
        else {
          local_40 = 3.926991;
        }
LAB_00414aab:
        fVar18 = (float10)heading_normalize_or_calc(local_40);
        (&player_state_table)[iVar7].aim_heading =
             player_turn_speed_accumulated + (&player_state_table)[iVar7].aim_heading;
        if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
          fVar14 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar14;
          if (2.0 < fVar14) {
            (&player_state_table)[iVar7].move_speed = 2.0;
          }
        }
        else {
          if ((&player_state_table)[iVar7].move_speed < 2.0) {
            (&player_state_table)[iVar7].move_speed =
                 frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
          }
          fVar14 = frame_dt + (&player_state_table)[iVar7].move_speed;
          (&player_state_table)[iVar7].move_speed = fVar14;
          if (2.8 < fVar14) {
            (&player_state_table)[iVar7].move_speed = 2.8;
          }
        }
        if (((&player_state_table)[iVar7].weapon_id == 7) &&
           (0.8 < (&player_state_table)[iVar7].move_speed)) {
          (&player_state_table)[iVar7].move_speed = 0.8;
        }
        fVar19 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dx =
             (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                     (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                    (float10)7.957747);
        fVar19 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
        (&player_state_table)[iVar7].move_dy =
             (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                     (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                    (float10)7.957747);
        local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
        local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
      }
      player_apply_move_with_spawn_avoidance(render_overlay_player_index,pfVar17,&local_10);
      (&player_state_table)[iVar7].move_phase =
           frame_dt * (&player_state_table)[iVar7].move_speed * 19.0 +
           (&player_state_table)[iVar7].move_phase;
    }
  }
  else {
    if ((&player_state_table)[iVar7].auto_target < 0) {
      (&player_state_table)[iVar7].auto_target = 0;
    }
    iVar10 = (&player_state_table)[iVar7].auto_target;
    if (((&creature_pool)[iVar10].active == '\0') || ((&creature_pool)[iVar10].health <= 0.0)) {
      fVar14 = 100000.0;
    }
    else {
      fVar14 = (&player_state_table)[iVar7].pos_y - (&creature_pool)[iVar10].pos_y;
      fVar2 = *pfVar17 - (&creature_pool)[iVar10].pos_x;
      fVar14 = SQRT(fVar14 * fVar14 + fVar2 * fVar2);
    }
    iVar10 = 0;
    pcVar13 = &creature_pool;
    do {
      if (((pcVar13->active != '\0') && (0.0 < pcVar13->health)) &&
         (fVar3 = (&player_state_table)[iVar7].pos_y - pcVar13->pos_y,
         fVar2 = *pfVar17 - pcVar13->pos_x, local_30[0] = SQRT(fVar3 * fVar3 + fVar2 * fVar2),
         local_30[0] < fVar14 - 64.0)) {
        (&player_state_table)[iVar7].auto_target = iVar10;
        fVar14 = local_30[0];
      }
      pcVar13 = pcVar13 + 1;
      iVar10 = iVar10 + 1;
    } while ((int)pcVar13 < 0x4aa338);
    if (demo_mode_active == '\0') goto LAB_00413f2d;
LAB_00414c7f:
    if (((&player_state_table)[iVar7].auto_target < 0) ||
       ((&creature_pool)[(&player_state_table)[iVar7].auto_target].health <= 0.0)) {
      fVar18 = (float10)fpatan((float10)(&player_state_table)[iVar7].pos_y - (float10)512.0,
                               (float10)*pfVar17 - (float10)512.0);
      fVar18 = fVar18 + (float10)3.1415927;
    }
    else {
      fVar14 = (&player_state_table)[iVar7].pos_y - 512.0;
      if (SQRT(fVar14 * fVar14 + (*pfVar17 - 512.0) * (*pfVar17 - 512.0)) <= 300.0) {
        local_14 = (&player_state_table)[iVar7].pos_y -
                   (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_y;
        local_18 = *pfVar17 - (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_x;
      }
      else {
        local_14 = (&player_state_table)[iVar7].pos_y - 512.0;
        local_18 = *pfVar17 - 512.0;
      }
      fVar18 = (float10)fpatan((float10)local_14,(float10)local_18);
      fVar18 = fVar18 - (float10)1.5707964;
      local_20 = local_18;
      local_1c = local_14;
    }
    if (fVar18 == (float10)-1.0) {
      fVar14 = (&player_state_table)[iVar7].move_speed - frame_dt * 15.0;
      (&player_state_table)[iVar7].move_speed = fVar14;
      if (fVar14 < 0.0) {
        (&player_state_table)[iVar7].move_speed = 0.0;
      }
      fVar18 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dx =
           (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                  (float10)25.0);
      fVar18 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dy =
           (float)(fVar18 * (float10)(&player_state_table)[iVar7].move_speed * (float10)fVar15 *
                  (float10)25.0);
      local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
      local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
LAB_00414f13:
      delta = &local_10;
      player_index = (float *)render_overlay_player_index;
    }
    else {
      fVar18 = (float10)heading_normalize_or_calc((float)fVar18);
      if (player_state_table.perk_counts[perk_id_long_distance_runner] < 1) {
        fVar14 = frame_dt * 5.0 + (&player_state_table)[iVar7].move_speed;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (2.0 < fVar14) {
          (&player_state_table)[iVar7].move_speed = 2.0;
        }
      }
      else {
        if ((&player_state_table)[iVar7].move_speed < 2.0) {
          (&player_state_table)[iVar7].move_speed =
               frame_dt * 4.0 + (&player_state_table)[iVar7].move_speed;
        }
        fVar14 = frame_dt + (&player_state_table)[iVar7].move_speed;
        (&player_state_table)[iVar7].move_speed = fVar14;
        if (2.8 < fVar14) {
          (&player_state_table)[iVar7].move_speed = 2.8;
        }
      }
      if (((&player_state_table)[iVar7].weapon_id == 7) &&
         (0.8 < (&player_state_table)[iVar7].move_speed)) {
        (&player_state_table)[iVar7].move_speed = 0.8;
      }
      delta = &local_10;
      fVar19 = (float10)fcos((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dx =
           (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                   (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                  (float10)7.957747);
      fVar19 = (float10)fsin((float10)(&player_state_table)[iVar7].heading - (float10)1.5707964);
      (&player_state_table)[iVar7].move_dy =
           (float)(fVar19 * (float10)(&player_state_table)[iVar7].move_speed *
                   (float10)(float)((float10)3.1415927 - fVar18) * (float10)fVar15 *
                  (float10)7.957747);
      local_c = frame_dt * (&player_state_table)[iVar7].move_dy;
      local_10 = frame_dt * (&player_state_table)[iVar7].move_dx;
      player_index = (float *)render_overlay_player_index;
    }
LAB_00414f1c:
    player_apply_move_with_spawn_avoidance((int)player_index,pfVar12,delta);
    fVar15 = frame_dt * (&player_state_table)[iVar7].move_speed;
LAB_00414f2d:
    (&player_state_table)[iVar7].move_phase =
         fVar15 * 19.0 + (&player_state_table)[iVar7].move_phase;
  }
  if (time_scale_active != '\0') {
    frame_dt = time_scale_factor * frame_dt * 1.6666666;
  }
  iVar10 = perk_count_get(perk_id_sharpshooter);
  if (iVar10 == 0) {
    fVar15 = (&player_state_table)[iVar7].spread_heat - frame_dt * 0.4;
    (&player_state_table)[iVar7].spread_heat = fVar15;
    if (fVar15 < 0.01) {
      (&player_state_table)[iVar7].spread_heat = 0.01;
    }
  }
  else {
    fVar15 = (&player_state_table)[iVar7].spread_heat - (frame_dt + frame_dt);
    (&player_state_table)[iVar7].spread_heat = fVar15;
    if (fVar15 < 0.25) {
      (&player_state_table)[iVar7].spread_heat = 0.25;
    }
    (&player_state_table)[iVar7].spread_heat = 0.02;
  }
  iVar10 = perk_count_get(perk_id_anxious_loader);
  if ((((iVar10 != 0) && (iVar10 = input_primary_just_pressed(), (char)iVar10 != '\0')) &&
      (0.0 < (&player_state_table)[iVar7].reload_timer)) &&
     (fVar15 = (&player_state_table)[iVar7].reload_timer - 0.05,
     (&player_state_table)[iVar7].reload_timer = fVar15, fVar15 <= 0.0)) {
    (&player_state_table)[iVar7].reload_timer = frame_dt * 0.8;
  }
  if (((&player_state_table)[iVar7].reload_timer - frame_dt < 0.0) &&
     (0.0 <= (&player_state_table)[iVar7].reload_timer)) {
    (&player_state_table)[iVar7].ammo = (&player_state_table)[iVar7].clip_size;
  }
  local_38 = 1.0;
  if ((*pfVar17 == local_28) && ((&player_state_table)[iVar7].pos_y == local_24)) {
    iVar10 = perk_count_get(perk_id_stationary_reloader);
    if (iVar10 != 0) {
      local_38 = 3.0;
    }
  }
  else {
    (&player_state_table)[iVar7].man_bomb_timer = 0.0;
    (&player_state_table)[iVar7].living_fortress_timer = 0.0;
  }
  iVar10 = perk_count_get(perk_id_angry_reloader);
  if (((iVar10 == 0) || ((&player_state_table)[iVar7].reload_timer_max <= 0.5)) ||
     (fVar15 = (&player_state_table)[iVar7].reload_timer_max * 0.5,
     (&player_state_table)[iVar7].reload_timer <= fVar15)) {
    (&player_state_table)[iVar7].reload_timer =
         (&player_state_table)[iVar7].reload_timer - local_38 * frame_dt;
  }
  else {
    fVar14 = (&player_state_table)[iVar7].reload_timer - local_38 * frame_dt;
    (&player_state_table)[iVar7].reload_timer = fVar14;
    if (fVar14 <= fVar15) {
      bonus_spawn_guard = 1;
      if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
        local_38 = -NAN;
      }
      else {
        local_38 = (float)(-1 - render_overlay_player_index);
      }
      lVar20 = __ftol();
      fVar15 = (float)(7 - (int)lVar20);
      local_3c = 0.0;
      local_30[0] = fVar15;
      if (0 < (int)fVar15) {
        local_30[0] = 6.2831855 / (float)(int)fVar15;
        do {
          projectile_spawn(pfVar17,(float)(int)local_3c * local_30[0] + 0.1,
                           PROJECTILE_TYPE_PLASMA_MINIGUN,(int)local_38);
          local_3c = (float)((int)local_3c + 1);
        } while ((int)local_3c < (int)fVar15);
      }
      bonus_spawn_guard = 0;
      sfx_play_panned(sfx_explosion_small);
    }
  }
  if ((&player_state_table)[iVar7].reload_timer < 0.0) {
    (&player_state_table)[iVar7].reload_timer = 0.0;
  }
  if ((((demo_mode_active == '\0') &&
       (iVar10 = perk_count_get(perk_id_alternate_weapon), iVar10 == 0)) &&
      ((*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c) != 4 &&
       ((iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(config_blob.key_reload),
        (char)iVar10 != '\0' && ((&player_state_table)[iVar7].reload_timer == 0.0)))))) &&
     (config_blob.reserved0._20_4_ == 1)) {
    player_start_reload();
  }
  bVar4 = false;
  if ((demo_mode_active == '\0') &&
     (iVar10 = *(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x44), iVar10 != 5
     )) {
    if (iVar10 == 0) {
      local_14 = (float)(&player_aim_screen_y)[render_overlay_player_index * 2] - camera_offset_y;
      local_18 = (float)(&player_aim_screen_x)[render_overlay_player_index * 2] - camera_offset_x;
      (&player_state_table)[iVar7].aim_x = local_18;
      (&player_state_table)[iVar7].aim_y = local_14;
    }
    else {
      if (iVar10 != 4) {
        if (iVar10 == 3) {
          fVar18 = (float10)(float)(&player_aim_screen_y)[render_overlay_player_index * 2] -
                   (float10)200.0;
          local_20 = (float)(&player_aim_screen_x)[render_overlay_player_index * 2] - 200.0;
          local_1c = (float)fVar18;
          if ((local_20 != 0.0) || (fVar18 != (float10)0.0)) {
            fVar18 = (float10)fpatan(fVar18,(float10)local_20);
            (&player_state_table)[iVar7].aim_heading = (float)(fVar18 + (float10)1.5707964);
            fVar18 = (fVar18 + (float10)1.5707964) - (float10)1.5707964;
            local_30[0] = (float)fVar18;
            fVar18 = (float10)fcos(fVar18);
            fVar19 = (float10)fsin((float10)local_30[0]);
            local_c = (float)fVar19;
            local_14 = local_c * 60.0 + (&player_state_table)[iVar7].pos_y;
            local_18 = (float)(fVar18 * (float10)60.0 + (float10)*pfVar17);
            (&player_state_table)[iVar7].aim_x = local_18;
            (&player_state_table)[iVar7].aim_y = local_14;
          }
          if (30.0 < SQRT(local_20 * local_20 + local_1c * local_1c)) {
            player_aim_update_thunk();
            iVar10 = render_overlay_player_index;
            local_14 = local_24 * 30.0;
            local_20 = local_28 * 30.0 + 200.0;
            local_1c = local_14 + 200.0;
            (&player_aim_screen_x)[render_overlay_player_index * 2] = local_20;
            (&player_aim_screen_y)[iVar10 * 2] = local_1c;
          }
        }
        else if (iVar10 == 1) {
          if ((*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c) == 1) ||
             (*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c) == 2)) {
            iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                               ((&player_state_table)[iVar7].input.aim_key_right);
            if ((char)iVar10 != '\0') {
              (&player_state_table)[iVar7].aim_heading =
                   frame_dt * 3.0 + (&player_state_table)[iVar7].aim_heading;
            }
            iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                               ((&player_state_table)[iVar7].input.aim_key_left);
            if ((char)iVar10 != '\0') {
              (&player_state_table)[iVar7].aim_heading =
                   (&player_state_table)[iVar7].aim_heading - frame_dt * 3.0;
            }
            fVar18 = (float10)(&player_state_table)[iVar7].aim_heading - (float10)1.5707964;
            local_30[0] = (float)fVar18;
            fVar18 = (float10)fcos(fVar18);
            fVar19 = (float10)fsin((float10)local_30[0]);
            local_c = (float)fVar19;
            local_14 = local_c * 60.0 + (&player_state_table)[iVar7].pos_y;
            local_18 = (float)(fVar18 * (float10)60.0 + (float10)*pfVar17);
            (&player_state_table)[iVar7].aim_x = local_18;
            (&player_state_table)[iVar7].aim_y = local_14;
          }
        }
        else {
          bVar8 = joystick_pov_check_up();
          if (bVar8) {
            (&player_state_table)[iVar7].aim_heading =
                 (&player_state_table)[iVar7].aim_heading - frame_dt * 4.0;
          }
          bVar8 = joystick_pov_check_down();
          if (bVar8) {
            (&player_state_table)[iVar7].aim_heading =
                 frame_dt * 4.0 + (&player_state_table)[iVar7].aim_heading;
          }
          fVar18 = (float10)(&player_state_table)[iVar7].aim_heading - (float10)1.5707964;
          local_30[0] = (float)fVar18;
          fVar18 = (float10)fcos(fVar18);
          fVar19 = (float10)fsin((float10)local_30[0]);
          local_c = (float)fVar19;
          local_14 = local_c * 60.0 + (&player_state_table)[iVar7].pos_y;
          local_18 = (float)(fVar18 * (float10)60.0 + (float10)*pfVar17);
          (&player_state_table)[iVar7].aim_x = local_18;
          (&player_state_table)[iVar7].aim_y = local_14;
        }
        goto LAB_0041572e;
      }
      (*grim_interface_ptr->vtable->grim_get_config_float)
                ((&player_state_table)[iVar7].input.axis_aim_y);
      (*grim_interface_ptr->vtable->grim_get_config_float)
                ((&player_state_table)[iVar7].input.axis_aim_x);
      local_20 = (float)extraout_ST0_02;
      local_1c = (float)extraout_ST0_01;
      player_aim_update_thunk();
      fVar15 = local_40 * *(float *)((int)cv_padAimDistMul + 0xc) + 42.0;
      local_18 = fVar15 * local_28;
      local_1c = fVar15 * local_24 + (&player_state_table)[iVar7].pos_y;
      local_20 = local_18 + *pfVar17;
      (&player_state_table)[iVar7].aim_x = local_20;
      (&player_state_table)[iVar7].aim_y = local_1c;
    }
    fVar18 = (float10)fpatan((float10)(&player_state_table)[iVar7].pos_y -
                             (float10)(&player_state_table)[iVar7].aim_y,
                             (float10)*pfVar17 - (float10)(&player_state_table)[iVar7].aim_x);
    (&player_state_table)[iVar7].aim_heading = (float)(fVar18 - (float10)1.5707964);
  }
  else {
    pfVar12 = &(&player_state_table)[iVar7].aim_x;
    local_1c = (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_y -
               (&player_state_table)[iVar7].aim_y;
    local_20 = (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_x - *pfVar12;
    fVar15 = SQRT(local_1c * local_1c + local_20 * local_20);
    if (4.0 <= fVar15) {
      player_aim_update_thunk();
      fVar14 = local_40 * 6.0 * frame_dt;
      local_18 = local_28 * fVar14;
      *pfVar12 = local_18 + *pfVar12;
      (&player_state_table)[iVar7].aim_y = fVar14 * local_24 + (&player_state_table)[iVar7].aim_y;
    }
    else {
      iVar10 = (&player_state_table)[iVar7].auto_target;
      *pfVar12 = (&creature_pool)[iVar10].pos_x;
      (&player_state_table)[iVar7].aim_y = (&creature_pool)[iVar10].pos_y;
    }
    if ((fVar15 < 128.0) &&
       (0.0 < (&creature_pool)[(&player_state_table)[iVar7].auto_target].health)) {
      bVar4 = true;
    }
  }
LAB_0041572e:
  fVar18 = (float10)fpatan((float10)(&player_state_table)[iVar7].pos_y -
                           (float10)(&player_state_table)[iVar7].aim_y,
                           (float10)*pfVar17 - (float10)(&player_state_table)[iVar7].aim_x);
  pfVar12 = &(&player_state_table)[iVar7].shot_cooldown;
  bVar8 = false;
  bVar5 = false;
  (&player_state_table)[iVar7].aim_heading = (float)(fVar18 - (float10)1.5707964);
  if ((*pfVar12 <= 0.0) && ((&player_state_table)[iVar7].reload_timer == 0.0)) {
    bVar8 = true;
    *(undefined1 *)&(&player_state_table)[iVar7].reload_active = 0;
  }
  if (((*pfVar12 <= 0.0) && (0 < (&player_state_table)[iVar7].experience)) &&
     ((iVar10 = perk_count_get(perk_id_regression_bullets), iVar10 != 0 ||
      (iVar10 = perk_count_get(perk_id_ammunition_within), iVar10 != 0)))) {
    bVar5 = true;
  }
  iVar10 = perk_count_get(perk_id_alternate_weapon);
  if (iVar10 != 0) {
    if (((weapon_swap_cooldown_ms < 1) || (weapon_swap_cooldown_ms = weapon_swap_cooldown_ms - frame_dt_ms, weapon_swap_cooldown_ms < 1)) &&
       (iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(config_blob.key_reload),
       (char)iVar10 != '\0')) {
      iVar10 = (&player_state_table)[iVar7].alt_weapon_id;
      (&player_state_table)[iVar7].alt_weapon_id = (&player_state_table)[iVar7].weapon_id;
      (&player_state_table)[iVar7].weapon_id = iVar10;
      iVar10 = (&player_state_table)[iVar7].alt_clip_size;
      (&player_state_table)[iVar7].alt_clip_size = (&player_state_table)[iVar7].clip_size;
      (&player_state_table)[iVar7].clip_size = iVar10;
      iVar10 = (&player_state_table)[iVar7].alt_reload_active;
      *(char *)&(&player_state_table)[iVar7].alt_reload_active =
           (char)(&player_state_table)[iVar7].reload_active;
      *(char *)&(&player_state_table)[iVar7].reload_active = (char)iVar10;
      iVar10 = (&player_state_table)[iVar7].alt_ammo;
      (&player_state_table)[iVar7].alt_ammo = (&player_state_table)[iVar7].ammo;
      (&player_state_table)[iVar7].ammo = iVar10;
      fVar15 = (&player_state_table)[iVar7].alt_reload_timer;
      (&player_state_table)[iVar7].alt_reload_timer = (&player_state_table)[iVar7].reload_timer;
      (&player_state_table)[iVar7].reload_timer = fVar15;
      fVar15 = (&player_state_table)[iVar7].alt_shot_cooldown;
      (&player_state_table)[iVar7].alt_shot_cooldown = *pfVar12;
      *pfVar12 = fVar15;
      fVar15 = (&player_state_table)[iVar7].alt_reload_timer_max;
      (&player_state_table)[iVar7].alt_reload_timer_max =
           (&player_state_table)[iVar7].reload_timer_max;
      (&player_state_table)[iVar7].reload_timer_max = fVar15;
      sfx_play_panned((float)(&weapon_table)[(&player_state_table)[iVar7].weapon_id].reload_sfx_id);
      *pfVar12 = *pfVar12 + 0.1;
      weapon_swap_cooldown_ms = 200;
    }
    else {
      iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(config_blob.key_reload);
      if ((char)iVar10 == '\0') {
        weapon_swap_cooldown_ms = 0;
      }
    }
  }
  if ((!bVar8) && (!bVar5)) goto LAB_0041753e;
  fVar15 = (&player_state_table)[iVar7].aim_heading;
  iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)
                     ((&player_state_table)[iVar7].input.fire_key);
  if (((char)iVar10 == '\0') && (!bVar4)) goto LAB_0041753e;
  survival_reward_fire_seen = 1;
  if (!bVar8) {
    iVar10 = perk_count_get(perk_id_regression_bullets);
    if (iVar10 == 0) {
      iVar10 = perk_count_get(perk_id_ammunition_within);
      if (iVar10 != 0) {
        if ((&weapon_ammo_class)[(&player_state_table)[iVar7].weapon_id * 0x1f] == 1) {
          fVar14 = 0.15;
        }
        else {
          fVar14 = 1.0;
        }
        player_take_damage(render_overlay_player_index,fVar14);
      }
    }
    else if ((&weapon_ammo_class)[(&player_state_table)[iVar7].weapon_id * 0x1f] == 1) {
      lVar20 = __ftol();
      (&player_state_table)[iVar7].experience = (int)lVar20;
    }
    else {
      lVar20 = __ftol();
      (&player_state_table)[iVar7].experience = (int)lVar20;
    }
    if ((&player_state_table)[iVar7].experience < 0) {
      (&player_state_table)[iVar7].experience = 0;
    }
  }
  fVar14 = (float)((float10)fVar15 - (float10)1.5707964);
  fVar18 = ((float10)fVar15 - (float10)1.5707964) - (float10)0.150915;
  fVar19 = (float10)fcos(fVar18);
  local_20 = (float)(fVar19 * (float10)16.0);
  fVar18 = (float10)fsin(fVar18);
  local_1c = (float)(fVar18 * (float10)16.0);
  if (((&weapon_table)[(&player_state_table)[iVar7].weapon_id].flags & 1) != 0) {
    uVar9 = crt_rand();
    local_30[0] = (float)(uVar9 & 0x3f);
    fVar2 = (float)(int)local_30[0] * 0.01 + fVar15;
    uVar9 = crt_rand();
    local_30[0] = (float)(uVar9 & 0x3f);
    local_10 = 1.0;
    local_c = 1.0;
    uStack_8 = 0x3f800000;
    uStack_4 = 0x3f19999a;
    effect_template_color_r = 0x3f800000;
    effect_template_flags = 0x1c5;
    fVar18 = (float10)(int)local_30[0] * (float10)0.022727273 + (float10)1.0;
    fVar19 = (float10)fcos((float10)fVar2);
    effect_template_color_g = 0x3f800000;
    effect_template_color_b = 0x3f800000;
    effect_template_color_a = 0x3f19999a;
    effect_template_lifetime = 0x3e19999a;
    effect_template_age = 0;
    local_18 = (float)(fVar19 * fVar18);
    fVar19 = (float10)fsin((float10)fVar2);
    local_14 = (float)(fVar19 * fVar18);
    uVar9 = crt_rand();
    effect_template_half_height = 0x40000000;
    local_30[0] = (float)((uVar9 & 0x3f) - 0x20);
    effect_template_half_width = 0x40000000;
    effect_template_rotation = (float)(int)local_30[0] * 0.1;
    effect_template_vel_x = local_18 * 100.0;
    effect_template_vel_y = local_14 * 100.0;
    iVar10 = crt_rand();
    effect_template_scale_step = 0;
    local_30[0] = (float)(iVar10 % 0x14);
    effect_template_rotation_step = ((float)(int)local_30[0] * 0.1 - 1.0) * 14.0;
    local_c = local_1c + (&player_state_table)[iVar7].pos_y;
    local_10 = local_20 + *pfVar17;
    effect_spawn(0x12,&local_10);
  }
  if (1.0 < *pfVar1) {
    *pfVar1 = 1.0;
  }
  iVar10 = render_overlay_player_index;
  local_38 = 1.0;
  if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
    iVar16 = -100;
  }
  else {
    iVar16 = -1 - render_overlay_player_index;
  }
  local_14 = (&player_state_table)[render_overlay_player_index].aim_y;
  local_18 = (&player_state_table)[render_overlay_player_index].aim_x;
  local_c = local_14 - (&player_state_table)[render_overlay_player_index].pos_y;
  local_10 = local_18 - (&player_state_table)[render_overlay_player_index].pos_x;
  local_28 = vec2_length(&local_10);
  local_28 = local_28 * 0.5;
  uVar9 = crt_rand();
  local_30[0] = (float)(uVar9 & 0x1ff);
  fVar2 = (float)(int)local_30[0];
  uVar9 = crt_rand();
  local_30[0] = (float)(uVar9 & 0x1ff);
  fVar18 = (float10)local_28 * (float10)(&player_state_table)[iVar10].spread_heat *
           (float10)(int)local_30[0] * (float10)0.001953125;
  fVar19 = (float10)fcos((float10)(fVar2 * 0.012271847));
  local_18 = (float)(fVar19 * fVar18 + (float10)local_18);
  fVar19 = (float10)fsin((float10)(fVar2 * 0.012271847));
  fVar18 = (float10)fpatan((float10)(&player_state_table)[iVar10].pos_y -
                           (fVar19 * fVar18 + (float10)local_14),
                           (float10)(&player_state_table)[iVar10].pos_x - (float10)local_18);
  fVar2 = (float)(fVar18 - (float10)1.5707964);
  iVar10 = (*grim_interface_ptr->vtable->grim_is_key_active)(0x22);
  if ((char)iVar10 != '\0') {
    (&player_state_table)[iVar7].fire_bullets_timer = 10.0;
  }
  if ((&player_state_table)[iVar7].fire_bullets_timer <= 0.0) {
    (&player_state_table)[iVar7].shot_cooldown =
         (&weapon_table)[(&player_state_table)[iVar7].weapon_id].shot_cooldown;
    *pfVar1 = (&weapon_table)[(&player_state_table)[iVar7].weapon_id].spread_heat + *pfVar1;
    iVar10 = (&player_state_table)[iVar7].weapon_id;
    iVar11 = crt_rand();
    sfx_play_panned((float)(iVar11 % (&weapon_table)[iVar10].shot_sfx_variant_count +
                           (&weapon_table)[iVar10].shot_sfx_base_id));
    iVar10 = (&player_state_table)[iVar7].weapon_id;
    if (iVar10 == 0x18) {
      local_c = local_1c + (&player_state_table)[iVar7].pos_y;
      local_10 = local_20 + *pfVar17;
      projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_SHRINKIFIER,iVar16);
      fVar18 = (float10)fcos((float10)fVar15);
      local_10 = (float)(fVar18 * (float10)25.0);
      fVar19 = (float10)fsin((float10)fVar15);
      local_c = (float)(fVar19 * (float10)25.0);
      local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
      local_18 = local_20 + *pfVar17;
      iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
      (&sprite_effect_pool)[iVar10].color_r = 0.5;
      (&sprite_effect_pool)[iVar10].color_g = 0.5;
      (&sprite_effect_pool)[iVar10].color_b = 0.5;
      (&sprite_effect_pool)[iVar10].color_a = 0.23;
      local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
      local_18 = local_20 + *pfVar17;
LAB_0041600e:
      local_3c = (float)fVar19;
      local_40 = (float)fVar18;
      local_c = local_3c * 15.0;
      local_10 = local_40 * 15.0;
      iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
      (&sprite_effect_pool)[iVar10].color_r = 0.5;
      (&sprite_effect_pool)[iVar10].color_g = 0.5;
      (&sprite_effect_pool)[iVar10].color_b = 0.5;
      (&sprite_effect_pool)[iVar10].color_a = 0.213;
    }
    else {
      if (iVar10 == 1) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PISTOL,iVar16);
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.23;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        goto LAB_0041600e;
      }
      if (iVar10 == 2) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.23;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.213;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_ASSAULT_RIFLE,iVar16);
      }
      else if (iVar10 == 3) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.25;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        local_3c = 1.68156e-44;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.223;
        do {
          pVar21 = PROJECTILE_TYPE_SHOTGUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 200 + -100);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.0013 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 100);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.0;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 0x14) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)15.0);
        fVar18 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar18 * (float10)15.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        local_3c = 5.60519e-45;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.223;
        do {
          pVar21 = PROJECTILE_TYPE_SHOTGUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 200 + -100);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.0013 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 100);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.0;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 4) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.26;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        local_3c = 1.68156e-44;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.233;
        do {
          pVar21 = PROJECTILE_TYPE_SHOTGUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 200 + -100);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.004 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 100);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.0;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 8) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        fx_spawn_particle(&local_10,fVar14,&(&player_state_table)[iVar7].move_dx,1.0);
        local_38 = 0.1;
      }
      else if (iVar10 == 0x10) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        iVar10 = fx_spawn_particle(&local_10,fVar14,&(&player_state_table)[iVar7].move_dx,1.0);
        if (iVar10 != -1) {
          *(undefined1 *)&(&particle_pool)[iVar10].style_id = 2;
        }
        local_38 = 0.1;
      }
      else if (iVar10 == 0xf) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        iVar10 = fx_spawn_particle(&local_10,fVar14,&(&player_state_table)[iVar7].move_dx,1.0);
        if (iVar10 != -1) {
          *(undefined1 *)&(&particle_pool)[iVar10].style_id = 1;
        }
        local_38 = 0.05;
      }
      else if (iVar10 == 5) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.23;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.213;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_SUBMACHINE_GUN,iVar16);
      }
      else if (iVar10 == 9) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PLASMA_RIFLE,iVar16);
      }
      else if (iVar10 == 10) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2 - 0.31415927,PROJECTILE_TYPE_PLASMA_RIFLE,iVar16);
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2 - 0.5235988,PROJECTILE_TYPE_PLASMA_MINIGUN,iVar16);
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PLASMA_RIFLE,iVar16);
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2 + 0.5235988,PROJECTILE_TYPE_PLASMA_MINIGUN,iVar16);
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2 + 0.31415927,PROJECTILE_TYPE_PLASMA_RIFLE,iVar16);
      }
      else if (iVar10 == 0x13) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PULSE_GUN,iVar16);
      }
      else if (iVar10 == 0x19) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_BLADE_GUN,iVar16);
      }
      else if (iVar10 == 0x1d) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_SPLITTER_GUN,iVar16);
      }
      else if (iVar10 == 0x15) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_ION_RIFLE,iVar16);
      }
      else if (iVar10 == 0x16) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_ION_MINIGUN,iVar16);
      }
      else if (iVar10 == 0x17) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_ION_CANNON,iVar16);
      }
      else if (iVar10 == 0x1c) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PLASMA_CANNON,iVar16);
      }
      else if (iVar10 == 0x1f) {
        local_3c = 1.12104e-44;
        do {
          pVar21 = PROJECTILE_TYPE_ION_MINIGUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 200 + -100);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.0026 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 0x50);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.4;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 0xb) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PLASMA_MINIGUN,iVar16);
      }
      else if (iVar10 == 0x1e) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.33;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        local_3c = 8.40779e-45;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.263;
        do {
          pVar21 = PROJECTILE_TYPE_GAUSS_GUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 200 + -100);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.002 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 0x50);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.4;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 6) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.33;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.263;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_GAUSS_GUN,iVar16);
      }
      else if (iVar10 == 0xc) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.34;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.283;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        fx_spawn_secondary_projectile(&local_10,fVar2,SECONDARY_PROJECTILE_TYPE_ROCKET);
      }
      else if (iVar10 == 0x11) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.34;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.283;
        fVar15 = (float)(&player_state_table)[iVar7].ammo * 1.0471976;
        fVar14 = 0.0;
        local_3c = (fVar2 - 3.1415927) - fVar15 * (float)(&player_state_table)[iVar7].ammo * 0.5;
        if (0.0 < (float)(&player_state_table)[iVar7].ammo) {
          do {
            local_c = local_1c + (&player_state_table)[iVar7].pos_y;
            local_10 = local_20 + *pfVar17;
            fx_spawn_secondary_projectile
                      (&local_10,local_3c,SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET);
            local_3c = local_3c + fVar15;
            fVar14 = (float)((int)fVar14 + 1);
            local_28 = fVar14;
          } while ((float)(int)fVar14 < (float)(&player_state_table)[iVar7].ammo);
        }
        local_38 = (float)(&player_state_table)[iVar7].ammo;
      }
      else if (iVar10 == 0x12) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar18 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar18 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.34;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        fx_spawn_secondary_projectile(&local_10,fVar2,SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN);
      }
      else if (iVar10 == 0xd) {
        fVar18 = (float10)fcos((float10)fVar15);
        local_10 = (float)(fVar18 * (float10)25.0);
        fVar19 = (float10)fsin((float10)fVar15);
        local_c = (float)(fVar19 * (float10)25.0);
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,1.0);
        local_10 = (float)fVar18 * 15.0;
        local_c = (float)fVar19 * 15.0;
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.31;
        local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
        local_18 = local_20 + *pfVar17;
        iVar10 = fx_spawn_sprite(&local_18,&local_10,2.0);
        (&sprite_effect_pool)[iVar10].color_r = 0.5;
        (&sprite_effect_pool)[iVar10].color_g = 0.5;
        (&sprite_effect_pool)[iVar10].color_b = 0.5;
        (&sprite_effect_pool)[iVar10].color_a = 0.243;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        fx_spawn_secondary_projectile(&local_10,fVar2,SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET);
      }
      else if (iVar10 == 7) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PISTOL,iVar16);
      }
      else if (iVar10 == 0xe) {
        local_3c = 1.96182e-44;
        do {
          pVar21 = PROJECTILE_TYPE_PLASMA_MINIGUN;
          local_c = local_1c + (&player_state_table)[iVar7].pos_y;
          local_10 = local_20 + *pfVar17;
          iVar10 = iVar16;
          uVar9 = crt_rand();
          local_28 = (float)((uVar9 & 0xff) - 0x80);
          iVar10 = projectile_spawn(&local_10,(float)(int)local_28 * 0.002 + fVar2,pVar21,iVar10);
          iVar11 = crt_rand();
          local_28 = (float)(iVar11 % 100);
          local_3c = (float)((int)local_3c + -1);
          projectile_pool[iVar10].pos.tail.vy.speed_scale = (float)(int)local_28 * 0.01 + 1.0;
        } while (local_3c != 0.0);
      }
      else if (iVar10 == 0x29) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_PLAGUE_SPREADER,iVar16);
      }
      else if (iVar10 == 0x2b) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,fVar2,PROJECTILE_TYPE_RAINBOW_GUN,iVar16);
      }
      else if (iVar10 == 0x2a) {
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        fx_spawn_particle_slow(&local_10,fVar2 - 1.5707964);
        local_38 = 0.15;
      }
    }
    iVar10 = perk_count_get(perk_id_sharpshooter);
    if (iVar10 == 0) {
      (&player_state_table)[iVar7].spread_heat =
           (&weapon_table)[(&player_state_table)[iVar7].weapon_id].spread_heat * 1.3 +
           (&player_state_table)[iVar7].spread_heat;
    }
    if (bonus_reflex_boost_timer <= 0.0) {
      (&player_state_table)[iVar7].ammo = (int)((float)(&player_state_table)[iVar7].ammo - local_38)
      ;
    }
  }
  else {
    sfx_play_panned(sfx_player_fire_reload_a);
    sfx_play_panned(sfx_player_fire_reload_b);
    if ((&weapon_table)[(&player_state_table)[iVar7].weapon_id].pellet_count == 1) {
      (&player_state_table)[iVar7].shot_cooldown = weapon_default_shot_cooldown_single;
      fVar14 = weapon_default_reload_delay;
    }
    else {
      (&player_state_table)[iVar7].shot_cooldown =
           (&weapon_table)[(&player_state_table)[iVar7].weapon_id].shot_cooldown;
      fVar14 = (&weapon_table)[(&player_state_table)[iVar7].weapon_id].spread_heat;
    }
    iVar10 = 0;
    *pfVar1 = fVar14 + *pfVar1;
    if (0 < (&weapon_table)[(&player_state_table)[iVar7].weapon_id].pellet_count) {
      do {
        iVar11 = crt_rand();
        local_28 = (float)(iVar11 % 200 + -100) * 0.0015 + fVar2;
        local_c = local_1c + (&player_state_table)[iVar7].pos_y;
        local_10 = local_20 + *pfVar17;
        projectile_spawn(&local_10,local_28,PROJECTILE_TYPE_FIRE_BULLETS,iVar16);
        iVar10 = iVar10 + 1;
      } while (iVar10 < (&weapon_table)[(&player_state_table)[iVar7].weapon_id].pellet_count);
    }
    fVar18 = (float10)fcos((float10)fVar15);
    local_10 = (float)(fVar18 * (float10)25.0);
    fVar18 = (float10)fsin((float10)fVar15);
    local_c = (float)(fVar18 * (float10)25.0);
    local_14 = local_1c + (&player_state_table)[iVar7].pos_y;
    local_18 = local_20 + *pfVar17;
    iVar16 = fx_spawn_sprite(&local_18,&local_10,1.0);
    iVar10 = perk_id_sharpshooter;
    (&sprite_effect_pool)[iVar16].color_r = 0.5;
    (&sprite_effect_pool)[iVar16].color_g = 0.5;
    (&sprite_effect_pool)[iVar16].color_b = 0.5;
    (&sprite_effect_pool)[iVar16].color_a = 0.413;
    iVar10 = perk_count_get(iVar10);
    if (iVar10 == 0) {
      (&player_state_table)[iVar7].spread_heat =
           weapon_default_reload_delay * 1.3 + (&player_state_table)[iVar7].spread_heat;
    }
  }
  if (0.48 < (&player_state_table)[iVar7].spread_heat) {
    (&player_state_table)[iVar7].spread_heat = 0.48;
  }
  if (0 < player_state_table.perk_counts[perk_id_fastshot]) {
    (&player_state_table)[iVar7].shot_cooldown = (&player_state_table)[iVar7].shot_cooldown * 0.88;
  }
  if (0 < player_state_table.perk_counts[perk_id_sharpshooter]) {
    (&player_state_table)[iVar7].shot_cooldown = (&player_state_table)[iVar7].shot_cooldown * 1.05;
  }
  if ((float)(&player_state_table)[iVar7].ammo <= 0.0) {
    player_start_reload();
  }
LAB_0041753e:
  fVar15 = (&player_state_table)[iVar7].move_phase;
  while (14.0 < fVar15) {
    fVar15 = (&player_state_table)[iVar7].move_phase - 14.0;
    (&player_state_table)[iVar7].move_phase = fVar15;
  }
  fVar15 = (&player_state_table)[iVar7].move_phase;
  while (fVar15 < 0.0) {
    fVar15 = (&player_state_table)[iVar7].move_phase + 14.0;
    (&player_state_table)[iVar7].move_phase = fVar15;
  }
  if (0.0 < (&player_state_table)[iVar7].speed_bonus_timer) {
    (&player_state_table)[iVar7].speed_multiplier =
         (&player_state_table)[iVar7].speed_multiplier - 1.0;
  }
  fVar15 = (&player_state_table)[iVar7].size * 0.5;
  if (*pfVar17 < fVar15) {
    *pfVar17 = fVar15;
  }
  if ((float)terrain_texture_width - fVar15 < *pfVar17) {
    *pfVar17 = (float)terrain_texture_width - fVar15;
  }
  pfVar17 = &(&player_state_table)[iVar7].pos_y;
  if ((&player_state_table)[iVar7].pos_y < fVar15) {
    *pfVar17 = fVar15;
  }
  if ((float)terrain_texture_height - fVar15 < *pfVar17) {
    *pfVar17 = (float)terrain_texture_height - fVar15;
  }
  if (0.8 < *pfVar1) {
    *pfVar1 = 0.8;
  }
  return;
}



/* player_apply_move_with_spawn_avoidance @ 0041e290 */

/* applies movement delta (scaled by alternate-weapon perk) and resolves collisions with creature
   spawn slots */

void __cdecl player_apply_move_with_spawn_avoidance(int player_index,float *pos,float *delta)

{
  float fVar1;
  float fVar2;
  creature_t *pcVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  creature_spawn_slot_t *pcVar7;
  
  iVar6 = perk_count_get(perk_id_alternate_weapon);
  if (iVar6 != 0) {
    *delta = *delta * 0.8;
    delta[1] = delta[1] * 0.8;
  }
  pcVar7 = &creature_spawn_slot_table;
  *pos = *pos + *delta;
  pos[1] = delta[1] + pos[1];
  do {
    pcVar3 = pcVar7->owner;
    if ((pcVar3 != (creature_t *)0x0) &&
       (fVar4 = (pcVar3->size + (&player_state_table)[player_index].size) * 0.33333334,
       fVar1 = pcVar3->pos_x - *pos, fVar2 = pcVar3->pos_y - pos[1],
       SQRT(fVar1 * fVar1 + fVar2 * fVar2) <= fVar4)) {
      *pos = *pos - *delta;
      fVar1 = pos[1];
      fVar2 = delta[1];
      pos[1] = fVar1 - fVar2;
      fVar5 = pcVar3->pos_x - *pos;
      fVar1 = pcVar3->pos_y - (fVar1 - fVar2);
      fVar2 = *pos + *delta;
      if (fVar4 < SQRT(fVar5 * fVar5 + fVar1 * fVar1)) {
        *pos = fVar2;
        fVar1 = pcVar3->pos_x - fVar2;
        fVar5 = pcVar3->pos_y - pos[1];
        if (SQRT(fVar1 * fVar1 + fVar5 * fVar5) <= fVar4) {
          *pos = fVar2 - *delta;
          fVar1 = delta[1] + pos[1];
          pos[1] = fVar1;
          fVar5 = pcVar3->pos_x - *pos;
          fVar2 = pcVar3->pos_y - fVar1;
          if (SQRT(fVar5 * fVar5 + fVar2 * fVar2) <= fVar4) {
            pos[1] = fVar1 - delta[1];
          }
        }
      }
      else {
        *pos = fVar2;
        pos[1] = delta[1] + pos[1];
      }
    }
    pcVar7 = pcVar7 + 1;
  } while ((int)pcVar7 < 0x4852d0);
  return;
}



/* player_reset_all @ 0041fc80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] void* sub_41fc80() */

void * player_reset_all(void)

{
  float fVar1;
  float fVar2;
  player_state_t *ppVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  uchar *puVar7;
  uint uVar8;
  int *piVar9;
  bool bVar10;
  
  if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
    console_printf(&console_log_queue,s___Reseting_players__00473e54);
  }
  render_overlay_player_index = 0;
  do {
    uVar5 = render_overlay_player_index;
    fVar1 = (float)terrain_texture_width;
    player_state_aux_counter = 0;
    iVar6 = render_overlay_player_index * 0x360;
    fVar2 = (float)terrain_texture_height;
    (&player_state_table)[render_overlay_player_index].speed_bonus_timer = 0.0;
    (&player_state_table)[uVar5].shield_timer = 0.0;
    (&player_state_table)[uVar5].state_aux = 0;
    (&player_plaguebearer_active)[iVar6] = 0;
    (&player_state_table)[uVar5].pos_x = fVar1 * 0.5;
    (&player_state_table)[uVar5].pos_y = fVar2 * 0.5;
    uVar8 = uVar5 & 0x80000001;
    bVar10 = uVar8 == 0;
    (&player_state_table)[uVar5].health = 100.0;
    if ((int)uVar8 < 0) {
      bVar10 = (uVar8 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar10) {
      (&player_state_table)[uVar5].pos_x =
           (float)(int)(uVar5 * 0x50) + (&player_state_table)[uVar5].pos_x;
      (&player_state_table)[uVar5].pos_y =
           (float)(int)(uVar5 * 0x50) + (&player_state_table)[uVar5].pos_y;
    }
    else {
      (&player_state_table)[uVar5].pos_x =
           (&player_state_table)[uVar5].pos_x - (float)(int)(uVar5 * 0x50);
      (&player_state_table)[uVar5].pos_y =
           (&player_state_table)[uVar5].pos_y - (float)(int)(uVar5 * 0x50);
    }
    fVar1 = (float)weapon_default_clip_size;
    (&player_state_table)[render_overlay_player_index].size = 48.0;
    (&player_state_table)[render_overlay_player_index].speed_multiplier = 2.0;
    (&player_state_table)[render_overlay_player_index].level = 1;
    (&player_state_table)[render_overlay_player_index].heading = 0.0;
    (&player_state_table)[render_overlay_player_index].experience = 0;
    ppVar3 = &player_state_table + render_overlay_player_index;
    ppVar3->_pad5[0] = '\0';
    ppVar3->_pad5[1] = '\0';
    ppVar3->_pad5[2] = '\0';
    ppVar3->_pad5[3] = '\0';
    (&player_state_table)[render_overlay_player_index].spread_heat = 0.0;
    (&player_state_table)[render_overlay_player_index].move_speed = 0.0;
    (&player_state_table)[render_overlay_player_index].ammo = 0x41200000;
    (&player_state_table)[render_overlay_player_index].clip_size = 0x41200000;
    (&player_state_table)[render_overlay_player_index].reload_timer_max = 1.0;
    (&player_state_table)[render_overlay_player_index].reload_timer = 0.0;
    (&player_state_table)[render_overlay_player_index].alt_weapon_id = 1;
    (&player_state_table)[render_overlay_player_index].alt_clip_size = (int)fVar1;
    *(undefined1 *)&(&player_state_table)[render_overlay_player_index].alt_reload_active = 0;
    (&player_state_table)[render_overlay_player_index].alt_ammo =
         (&player_state_table)[render_overlay_player_index].alt_clip_size;
    fVar1 = weapon_default_reload_time;
    (&player_state_table)[render_overlay_player_index].alt_reload_timer = 0.0;
    (&player_state_table)[render_overlay_player_index].alt_shot_cooldown = 0.0;
    (&player_state_table)[render_overlay_player_index].alt_reload_timer_max = fVar1;
    cVar4 = demo_mode_active;
    (&player_state_table)[render_overlay_player_index].shot_cooldown = 0.8;
    (&player_state_table)[render_overlay_player_index].weapon_id = 1;
    ppVar3 = &player_state_table + render_overlay_player_index;
    ppVar3->_pad7[0] = '\0';
    ppVar3->_pad7[1] = '\0';
    ppVar3->_pad7[2] = '\0';
    ppVar3->_pad7[3] = '\0';
    (&player_state_table)[render_overlay_player_index].death_timer = 16.0;
    if (cVar4 == '\0') {
      ui_mouse_x = 0x43a00000;
      ui_mouse_y = 0x430c0000;
    }
    piVar9 = (&player_state_table)[render_overlay_player_index].perk_counts;
    for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = 0;
      piVar9 = piVar9 + 1;
    }
    puVar7 = &creature_pool.collision_flag;
    do {
      *puVar7 = '\0';
      puVar7 = puVar7 + 0x98;
    } while ((int)puVar7 < 0x4aa341);
    render_overlay_player_index = render_overlay_player_index + 1;
  } while ((int)render_overlay_player_index < 2);
  render_overlay_player_index = 0;
  return puVar7;
}



/* player_find_in_radius @ 00420730 */

/* returns a player index in range, skipping owner_id (-1/-2/-3 -> player 0/1/2) */

int __cdecl player_find_in_radius(int owner_id,float *pos,float radius)

{
  int iVar1;
  float *pfVar2;
  
  iVar1 = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    pfVar2 = &player_state_table.health;
    do {
      if (iVar1 != -1 - owner_id) {
        if (0.0 < *pfVar2) {
          if (SQRT((pfVar2[-3] - pos[1]) * (pfVar2[-3] - pos[1]) +
                   (pfVar2[-4] - *pos) * (pfVar2[-4] - *pos)) - radius <
              pfVar2[4] * 0.14285715 + 3.0) {
            return iVar1;
          }
        }
      }
      iVar1 = iVar1 + 1;
      pfVar2 = pfVar2 + 0xd8;
    } while (iVar1 < (int)config_blob.reserved0._20_4_);
  }
  return -1;
}



/* player_take_damage @ 00425e50 */

/* applies player damage with perk modifiers, SFX, and retaliation effects */

void __cdecl player_take_damage(int player_index,float damage)

{
  float *pos;
  float fVar1;
  float fVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  creature_t *pcVar6;
  bool bVar7;
  float local_c;
  float local_8 [2];
  
  iVar4 = perk_count_get(perk_id_death_clock);
  if (iVar4 != 0) {
    return;
  }
  iVar4 = perk_count_get(perk_id_tough_reloader);
  if ((iVar4 != 0) && ((char)(&player_state_table)[player_index].reload_active != '\0')) {
    damage = damage * 0.5;
  }
  survival_reward_damage_seen = 1;
  local_c = 1.0;
  if (0.0 < (&player_state_table)[player_index].shield_timer) {
    survival_reward_damage_seen = 1;
    return;
  }
  bVar7 = player_state_table.health <= 0.0;
  iVar4 = perk_count_get(perk_id_thick_skinned);
  if (iVar4 != 0) {
    local_c = 0.666;
  }
  bVar3 = false;
  iVar4 = perk_count_get(perk_id_ninja);
  if (iVar4 == 0) {
    iVar4 = perk_count_get(perk_id_dodger);
    if ((iVar4 != 0) && (iVar4 = crt_rand(), iVar4 % 5 == 0)) {
      bVar3 = true;
      goto LAB_00425fa1;
    }
  }
  else {
    iVar4 = crt_rand();
    if (iVar4 % 3 == 0) {
      bVar3 = true;
      goto LAB_00425fa1;
    }
  }
  iVar4 = perk_count_get(perk_id_highlander);
  if (iVar4 == 0) {
    (&player_state_table)[player_index].health =
         (&player_state_table)[player_index].health - local_c * damage;
  }
  else {
    iVar4 = crt_rand();
    if (iVar4 % 10 == 0) {
      (&player_state_table)[player_index].health = 0.0;
    }
  }
LAB_00425fa1:
  if (0.0 <= (&player_state_table)[player_index].health) {
    iVar4 = crt_rand();
    sfx_play_panned((float)(iVar4 % 3 + sfx_trooper_inpain_01));
    if (bVar7) {
      return;
    }
  }
  else {
    (&player_state_table)[player_index].death_timer =
         (&player_state_table)[player_index].death_timer - frame_dt * 28.0;
    if (bVar7) {
      return;
    }
    iVar4 = perk_count_get(perk_id_final_revenge);
    if (iVar4 == 0) {
      uVar5 = crt_rand();
      uVar5 = uVar5 & 0x80000001;
      if ((int)uVar5 < 0) {
        uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
      }
      sfx_play_panned((float)(uVar5 + sfx_trooper_die_01));
    }
    else {
      pos = &(&player_state_table)[player_index].pos_x;
      effect_spawn_explosion_burst(pos,1.8);
      bonus_spawn_guard = 1;
      iVar4 = 0;
      pcVar6 = &creature_pool;
      do {
        if ((((pcVar6->active != '\0') && (ABS(pcVar6->pos_x - *pos) <= 512.0)) &&
            (ABS(pcVar6->pos_y - (&player_state_table)[player_index].pos_y) <= 512.0)) &&
           (fVar1 = pcVar6->pos_x - *pos,
           fVar2 = pcVar6->pos_y - (&player_state_table)[player_index].pos_y,
           fVar1 = 512.0 - SQRT(fVar1 * fVar1 + fVar2 * fVar2), 0.0 < fVar1)) {
          local_8[0] = 0.0;
          local_8[1] = 0.0;
          creature_apply_damage(iVar4,fVar1 * 5.0,3,local_8);
        }
        pcVar6 = pcVar6 + 1;
        iVar4 = iVar4 + 1;
      } while ((int)pcVar6 < 0x4aa338);
      bonus_spawn_guard = 0;
      sfx_play_panned(sfx_explosion_large);
      sfx_play_panned(sfx_shockwave);
    }
  }
  if (!bVar3) {
    iVar4 = perk_count_get(perk_id_unstoppable);
    if (iVar4 == 0) {
      iVar4 = crt_rand();
      (&player_state_table)[player_index].heading =
           (float)(iVar4 % 100 + -0x32) * 0.04 + (&player_state_table)[player_index].heading;
      fVar1 = damage * 0.01 + (&player_state_table)[player_index].spread_heat;
      (&player_state_table)[player_index].spread_heat = fVar1;
      if (0.48 < fVar1) {
        (&player_state_table)[player_index].spread_heat = 0.48;
      }
    }
    if (((&player_state_table)[player_index].health <= 20.0) &&
       (iVar4 = crt_rand(), ((byte)iVar4 & 7) == 3)) {
      (&player_state_table)[player_index].low_health_timer = 0.0;
    }
  }
  return;
}



/* player_render_overlays @ 00428390 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Renders per-player overlays/indicators using player_state_table + effect_uv8. Runtime
   (analysis/frida/player_sprite_trace_summary.json): when alive (health>0) draws 2 sprite layers
   per call from effect_uv8[frame] (0–14) and effect_uv8[frame+0x10] (16–30) using heading vs
   aim_heading rotations, with a shadow/outline pass (scale ~1.02/1.03 and offset +3,+3 / +1,+1)
   before the main pass. When dead, draws a single layer from effect_uv8[ftol(death_timer)]
   (32–51) with 0x34 fallback, also with shadow+main passes. */

void player_render_overlays(void)

{
  uv2f_t *puVar1;
  int iVar2;
  int iVar3;
  IGrim2D_vtbl *pIVar4;
  int *piVar5;
  float10 fVar6;
  float10 fVar7;
  longlong lVar8;
  float *pfVar9;
  float fStack_a4;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fVar14;
  float fStack_5c;
  
  if (((((player_render_disabled_flag != '\0') || (ui_transition_alpha <= 0.0)) || (game_state_id == 0x14)) ||
      ((game_state_id == 0x16 || (game_state_prev == 0x14)))) || (game_state_prev == 0x16)) {
    return;
  }
  iVar2 = perk_count_get(perk_id_radioactive);
  if (iVar2 != 0) {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_bind_texture)((int)particles_texture,0);
    effect_select_texture(0x10);
    fVar6 = (float10)fsin((float10)game_time_s);
    (*grim_interface_ptr->vtable->grim_set_color)
              (0.3,0.6,0.3,
               (float)(((fVar6 + (float10)1.0) * (float10)0.1875 + (float10)0.25) *
                      (float10)6.108539e-39));
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_draw_quad)
              ((camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - 50.0,
               (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - 50.0,
               100.0,100.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_bind_texture)(player_sprite_texture_id,0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
  fVar14 = 8.40779e-45;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  iVar2 = render_overlay_player_index;
  if (0.0 < (&player_state_table)[render_overlay_player_index].health) {
    lVar8 = __ftol();
    iVar3 = (int)lVar8;
    fVar6 = (float10)(&player_state_table)[iVar2].aim_heading + (float10)1.5707964;
    fVar7 = (float10)fcos(fVar6);
    fVar12 = (&player_state_table)[iVar2].muzzle_flash_alpha;
    fVar6 = (float10)fsin(fVar6);
    fVar13 = (&player_state_table)[iVar2].muzzle_flash_alpha;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,2.138129e-39);
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((&player_state_table)[render_overlay_player_index].heading);
    render_scratch_f0 = (&effect_uv8)[iVar3].u;
    render_scratch_f1 = (&effect_uv8)[iVar3].v;
    puVar1 = &effect_uv8 + iVar3;
    render_scratch_f2 = puVar1->u + 0.125;
    render_scratch_f3 = (&effect_uv8)[iVar3].v + 0.125;
    (*grim_interface_ptr->vtable->grim_set_uv)
              (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    fVar10 = (&player_state_table)[render_overlay_player_index].size * 0.5 - 2.0;
    render_scratch_f0 =
         (camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - fVar10;
    render_scratch_f1 =
         (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - fVar10;
    fVar10 = (&player_state_table)[render_overlay_player_index].size * 1.02;
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (render_scratch_f0 + 1.0,render_scratch_f1 + 1.0,fVar10,fVar10);
    render_scratch_f0 = *(float *)(&effect_uv8_secondary_u + iVar3 * 8);
    render_scratch_f1 = *(float *)(&effect_uv8_secondary_v + iVar3 * 8);
    iVar2 = iVar3 * 8;
    pfVar9 = (float *)(&effect_uv8_secondary_u + iVar2);
    render_scratch_f2 = *pfVar9 + 0.125;
    render_scratch_f3 = *(float *)(&effect_uv8_secondary_v + iVar2) + 0.125;
    (*grim_interface_ptr->vtable->grim_set_uv)
              (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((&player_state_table)[render_overlay_player_index].aim_heading);
    fVar10 = (&player_state_table)[render_overlay_player_index].size * 0.5;
    render_scratch_f0 =
         ((camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - fVar10) +
         (float)(fVar7 * (float10)fVar12 * (float10)12.0);
    render_scratch_f1 =
         ((camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - fVar10) +
         (float)(fVar6 * (float10)fVar13 * (float10)12.0);
    fVar12 = (&player_state_table)[render_overlay_player_index].size * 1.03;
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (render_scratch_f0 + 1.0,render_scratch_f1 + 1.0,fVar12,fVar12);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_bind_texture)(player_sprite_texture_id,0);
    fStack_7c = 6.111067e-39;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    fVar13 = 8.40779e-45;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_7c);
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((&player_state_table)[render_overlay_player_index].heading);
    render_scratch_f0 = puVar1->u;
    render_scratch_f1 = (&effect_uv8)[iVar3].v;
    render_scratch_f2 = puVar1->u + 0.125;
    render_scratch_f3 = (&effect_uv8)[iVar3].v + 0.125;
    (*grim_interface_ptr->vtable->grim_set_uv)
              (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
    fVar12 = (&player_state_table)[render_overlay_player_index].size * 0.5;
    render_scratch_f0 =
         (camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - fVar12;
    render_scratch_f1 =
         (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - fVar12;
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (render_scratch_f0,render_scratch_f1,
               (&player_state_table)[render_overlay_player_index].size,
               (&player_state_table)[render_overlay_player_index].size);
    fVar12 = fStack_7c;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_7c);
    if (1 < (int)config_blob.reserved0._20_4_) {
      if (render_overlay_player_index == 0) {
        (*grim_interface_ptr->vtable->grim_set_color)(0.3,0.3,1.0,fVar12);
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.55,0.35,fVar12);
      }
    }
    render_scratch_f0 = *pfVar9;
    render_scratch_f1 = *(float *)(&effect_uv8_secondary_v + iVar2);
    render_scratch_f2 = *pfVar9 + 0.125;
    render_scratch_f3 = *(float *)(&effect_uv8_secondary_v + iVar2) + 0.125;
    (*grim_interface_ptr->vtable->grim_set_uv)
              (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((&player_state_table)[render_overlay_player_index].aim_heading);
    fVar12 = (&player_state_table)[render_overlay_player_index].size * 0.5;
    render_scratch_f0 =
         ((camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - fVar12) +
         fVar14;
    render_scratch_f1 =
         ((camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - fVar12) +
         fStack_5c;
    fVar14 = render_scratch_f1;
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (render_scratch_f0,render_scratch_f1,
               (&player_state_table)[render_overlay_player_index].size,
               (&player_state_table)[render_overlay_player_index].size);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    if (0.0 < (&player_state_table)[render_overlay_player_index].shield_timer) {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
      (*grim_interface_ptr->vtable->grim_bind_texture)((int)particles_texture,0);
      effect_select_texture(2);
      fVar6 = (float10)fsin((float10)game_time_s);
      pfVar9 = &(&player_state_table)[render_overlay_player_index].shield_timer;
      fVar6 = (fVar6 + (float10)1.0) * (float10)0.25 + (float10)*pfVar9;
      if (*pfVar9 < 1.0) {
        fVar6 = fVar6 * (float10)*pfVar9;
      }
      if ((float10)1.0 < fVar6) {
        fVar6 = (float10)1.0;
      }
      fVar14 = (float)(fVar6 * (float10)6.112132e-39);
      (*grim_interface_ptr->vtable->grim_set_color)(0.35686275,0.7058824,1.0,fVar14 * 0.4);
      fVar6 = (float10)fsin((float10)game_time_s * (float10)3.0);
      fVar12 = (float)(fVar6 + (float10)17.5);
      fVar6 = (float10)(&player_state_table)[render_overlay_player_index].aim_heading -
              (float10)1.5707964;
      fVar7 = (float10)fcos(fVar6);
      fStack_80 = (float)(fVar7 * (float10)3.0);
      fVar6 = (float10)fsin(fVar6);
      fStack_7c = (float)(fVar6 * (float10)3.0);
      (*grim_interface_ptr->vtable->grim_set_rotation)(game_time_s + game_time_s);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      (*grim_interface_ptr->vtable->grim_draw_quad)
                (((camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) -
                 fVar12) + fStack_80,
                 (fStack_7c + (&player_state_table)[render_overlay_player_index].pos_y +
                 camera_offset_y) - fVar12,fVar12 + fVar12,fVar12 + fVar12);
      (*grim_interface_ptr->vtable->grim_set_color)(0.35686275,0.7058824,1.0,fVar14 * 0.3);
      fVar6 = (float10)fsin((float10)game_time_s * (float10)3.0);
      fVar12 = (float)(fVar6 * (float10)4.0 + (float10)24.0);
      (*grim_interface_ptr->vtable->grim_set_rotation)(game_time_s * -2.0);
      fVar14 = fVar12 + fVar12;
      (*grim_interface_ptr->vtable->grim_draw_quad)
                (((camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) -
                 fVar12) + fStack_80,
                 (fStack_7c + (&player_state_table)[render_overlay_player_index].pos_y +
                 camera_offset_y) - fVar12,fVar14,fVar14);
      (*grim_interface_ptr->vtable->grim_end_batch)();
      fVar13 = 8.40779e-45;
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    }
    if (((&weapon_table)[(&player_state_table)[render_overlay_player_index].weapon_id].flags & 8) ==
        0) {
      fVar6 = (float10)(&player_state_table)[render_overlay_player_index].aim_heading +
              (float10)1.5707964;
      fcos(fVar6);
      fsin(fVar6);
      fVar14 = 6.113207e-39;
      (*grim_interface_ptr->vtable->grim_bind_texture)(tex_muzzle_flash,0);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,2);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
      (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
      fVar12 = (&player_state_table)[render_overlay_player_index].muzzle_flash_alpha * 0.8;
      if (1.0 < fVar12) {
        fVar12 = 1.0;
      }
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar12 * 6.11324e-39);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      (*grim_interface_ptr->vtable->grim_set_rotation)
                ((&player_state_table)[render_overlay_player_index].aim_heading);
      if (((&weapon_table)[(&player_state_table)[render_overlay_player_index].weapon_id].flags & 4)
          == 0) {
        fStack_7c = (&player_state_table)[render_overlay_player_index].size * 0.5;
        fVar12 = (&player_state_table)[render_overlay_player_index].size;
        fStack_80 = (camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) -
                    fStack_7c;
        fStack_7c = (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) -
                    fStack_7c;
        pIVar4 = grim_interface_ptr->vtable;
      }
      else {
        fStack_7c = (&player_state_table)[render_overlay_player_index].size * 0.25;
        fStack_80 = (camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) -
                    fStack_7c;
        fStack_7c = (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) -
                    fStack_7c;
        fVar12 = (&player_state_table)[render_overlay_player_index].size * 0.5;
        pIVar4 = grim_interface_ptr->vtable;
      }
      fStack_7c = fStack_7c + fStack_84;
      fStack_80 = fStack_80 + fVar13;
      render_scratch_f0 = fStack_80;
      render_scratch_f1 = fStack_7c;
      (*pIVar4->grim_draw_quad)(fStack_80,fStack_7c,fVar12,fVar12);
      (*grim_interface_ptr->vtable->grim_end_batch)();
    }
    iVar2 = perk_count_get(perk_init_counter);
    if (iVar2 != 0) {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      pfVar9 = (float *)0x14;
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
      (*grim_interface_ptr->vtable->grim_bind_texture)(projectile_texture,0);
      (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,2);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      iVar2 = 0;
      if (0 < (int)config_blob.reserved0._20_4_) {
        piVar5 = &player_state_table.auto_target;
        do {
          if ((0.25 < (float)piVar5[-0xa2]) &&
             (iVar3 = *piVar5, fVar12 = (&creature_pool)[iVar3].pos_x - (float)piVar5[-0xc3],
             fVar13 = (&creature_pool)[iVar3].pos_y - (float)piVar5[-0xc2],
             SQRT(fVar12 * fVar12 + fVar13 * fVar13) <= 80.0)) {
            fVar12 = (&creature_pool)[iVar3].pos_x - (float)piVar5[-0xc3];
            fVar13 = (&creature_pool)[iVar3].pos_y - (float)piVar5[-0xc2];
            pfVar9 = &fStack_80;
            fStack_80 = fVar12;
            fStack_7c = fVar13;
            player_aim_update_thunk();
            fVar10 = (camera_offset_x + (float)piVar5[-0xc3]) - 16.0;
            fVar11 = (camera_offset_y + (float)piVar5[-0xc2]) - 16.0;
            (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.6,1.0,6.113987e-39);
            fStack_a4 = 0.0;
            if (0.0 < fVar14) {
              do {
                (*grim_interface_ptr->vtable->grim_draw_quad)
                          (fVar12 * fStack_a4 + fVar10,fVar13 * fStack_a4 + fVar11,32.0,32.0);
                fStack_a4 = fStack_a4 + 8.0;
              } while (fStack_a4 < fVar14);
            }
          }
          iVar2 = iVar2 + 1;
          piVar5 = piVar5 + 0xd8;
        } while (iVar2 < (int)config_blob.reserved0._20_4_);
      }
      (*grim_interface_ptr->vtable->grim_end_batch)(pfVar9);
    }
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    return;
  }
  if (0.0 <= (&player_state_table)[render_overlay_player_index].death_timer) {
    lVar8 = __ftol();
    iVar2 = (int)lVar8;
  }
  else {
    iVar2 = 0x34;
  }
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  render_scratch_f0 = (&effect_uv8)[iVar2].u;
  render_scratch_f1 = (&effect_uv8)[iVar2].v;
  render_scratch_f2 = (&effect_uv8)[iVar2].u + 0.125;
  render_scratch_f3 = (&effect_uv8)[iVar2].v + 0.125;
  (*grim_interface_ptr->vtable->grim_set_uv)
            (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,2.138129e-39);
  (*grim_interface_ptr->vtable->grim_set_rotation)
            ((&player_state_table)[render_overlay_player_index].aim_heading);
  fVar14 = (&player_state_table)[render_overlay_player_index].size * 0.5;
  render_scratch_f0 =
       (camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x) - fVar14;
  render_scratch_f1 =
       (camera_offset_y + (&player_state_table)[render_overlay_player_index].pos_y) - fVar14;
  fVar14 = (&player_state_table)[render_overlay_player_index].size * 1.03;
  (*grim_interface_ptr->vtable->grim_draw_quad)
            (render_scratch_f0 + 1.0,render_scratch_f1 + 1.0,fVar14,fVar14);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  fStack_7c = 6.10966e-39;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  if (config_blob.reserved0._20_4_ == 1) {
    fVar13 = 1.0;
    pIVar4 = grim_interface_ptr->vtable;
    fVar12 = 1.0;
  }
  else {
    pIVar4 = grim_interface_ptr->vtable;
    if (render_overlay_player_index == 0) {
      fVar13 = 1.0;
      fVar12 = 0.3;
      fVar14 = 0.3;
      goto LAB_004287af;
    }
    fVar13 = 0.35;
    fVar12 = 0.55;
  }
  fVar14 = 1.0;
LAB_004287af:
  (*pIVar4->grim_set_color)(fVar14,fVar12,fVar13,fStack_7c);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)
            (render_scratch_f0,render_scratch_f1,
             (&player_state_table)[render_overlay_player_index].size,
             (&player_state_table)[render_overlay_player_index].size);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  return;
}



/* player_fire_weapon @ 00444980 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* handles player firing: cooldowns, ammo, projectiles, and muzzle effects */

void __cdecl player_fire_weapon(char param_1,char param_2)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float *unaff_retaddr;
  projectile_type_id_t type_id;
  int iVar9;
  float fVar10;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar5 = game_is_full_version();
  if ((char)iVar5 == '\0') {
    crt_exit(0);
  }
  iVar5 = render_overlay_player_index;
  if (console_open_flag == '\0') {
    if ((&player_state_table)[render_overlay_player_index].health <= 0.0) {
      (&player_state_table)[render_overlay_player_index].death_timer =
           (&player_state_table)[render_overlay_player_index].death_timer - frame_dt * 20.0;
      return;
    }
    fVar2 = (&player_state_table)[render_overlay_player_index].muzzle_flash_alpha -
            (frame_dt + frame_dt);
    (&player_state_table)[render_overlay_player_index].muzzle_flash_alpha = fVar2;
    if (fVar2 < 0.0) {
      (&player_state_table)[iVar5].muzzle_flash_alpha = 0.0;
    }
    (&player_state_table)[iVar5].shot_cooldown = 0.0;
    (&player_state_table)[iVar5].move_dx = 0.0;
    (&player_state_table)[iVar5].move_dy = 0.0;
    (&player_state_table)[iVar5].spread_heat = 0.0;
    (&player_state_table)[iVar5].ammo = (&player_state_table)[iVar5].clip_size;
    (&player_state_table)[iVar5].reload_timer = 0.0;
    if (param_2 != '\0') {
      player_start_reload();
      iVar5 = render_overlay_player_index;
    }
    bVar3 = false;
    (&player_state_table)[iVar5].aim_x = *unaff_retaddr;
    (&player_state_table)[iVar5].aim_y = unaff_retaddr[1];
    fVar8 = (float10)fpatan((float10)(&player_state_table)[iVar5].pos_y -
                            (float10)(&player_state_table)[iVar5].aim_y,
                            (float10)(&player_state_table)[iVar5].pos_x -
                            (float10)(&player_state_table)[iVar5].aim_x);
    (&player_state_table)[iVar5].aim_heading = (float)(fVar8 - (float10)1.5707964);
    if (((&player_state_table)[iVar5].shot_cooldown <= 0.0) &&
       ((&player_state_table)[iVar5].reload_timer == 0.0)) {
      bVar3 = true;
      *(undefined1 *)&(&player_state_table)[iVar5].reload_active = 0;
    }
    bVar4 = false;
    if ((((&player_state_table)[iVar5].shot_cooldown <= 0.0) &&
        (0 < (&player_state_table)[iVar5].experience)) &&
       ((iVar5 = perk_count_get(perk_id_regression_bullets), iVar5 != 0 ||
        (iVar6 = perk_count_get(perk_id_ammunition_within), iVar5 = render_overlay_player_index,
        bVar4 = false, iVar6 != 0)))) {
      bVar4 = true;
      iVar5 = render_overlay_player_index;
    }
    if ((bVar3) || (bVar4)) {
      fVar2 = (&player_state_table)[iVar5].aim_heading;
      if (param_1 != '\0') {
        fVar8 = ((float10)fVar2 - (float10)1.5707964) - (float10)0.150915;
        fVar7 = (float10)fcos(fVar8);
        fVar10 = (float)(fVar7 * (float10)16.0);
        fVar8 = (float10)fsin(fVar8);
        fVar1 = (float)(fVar8 * (float10)16.0);
        if (((&weapon_table)[(&player_state_table)[iVar5].weapon_id].flags & 1) != 0) {
          crt_rand();
          crt_rand();
          iVar5 = render_overlay_player_index;
        }
        if (1.0 < (&player_state_table)[iVar5].muzzle_flash_alpha) {
          (&player_state_table)[iVar5].muzzle_flash_alpha = 1.0;
        }
        (&player_state_table)[iVar5].muzzle_flash_alpha =
             (&weapon_table)[(&player_state_table)[iVar5].weapon_id].spread_heat +
             (&player_state_table)[iVar5].muzzle_flash_alpha;
        sfx_play_panned((float)(&weapon_table)[(&player_state_table)[iVar5].weapon_id].
                               shot_sfx_base_id);
        if ((&player_state_table)[render_overlay_player_index].weapon_id == 3) {
          fVar8 = (float10)fcos((float10)fVar2);
          local_14 = (float)(fVar8 * (float10)25.0);
          fVar7 = (float10)fsin((float10)fVar2);
          local_10 = (float)(fVar7 * (float10)25.0);
          local_8 = fVar1 + (&player_state_table)[render_overlay_player_index].pos_y;
          local_c = fVar10 + (&player_state_table)[render_overlay_player_index].pos_x;
          iVar5 = fx_spawn_sprite(&local_c,&local_14,1.0);
          local_c = (float)fVar8 * 15.0;
          (&sprite_effect_pool)[iVar5].color_r = 0.5;
          (&sprite_effect_pool)[iVar5].color_g = 0.5;
          local_8 = (float)fVar7 * 15.0;
          (&sprite_effect_pool)[iVar5].color_b = 0.5;
          (&sprite_effect_pool)[iVar5].color_a = 0.25;
          local_10 = fVar1 + (&player_state_table)[render_overlay_player_index].pos_y;
          local_14 = fVar10 + (&player_state_table)[render_overlay_player_index].pos_x;
          iVar5 = fx_spawn_sprite(&local_14,&local_c,2.0);
          iVar6 = 0xc;
          (&sprite_effect_pool)[iVar5].color_r = 0.5;
          (&sprite_effect_pool)[iVar5].color_g = 0.5;
          (&sprite_effect_pool)[iVar5].color_b = 0.5;
          (&sprite_effect_pool)[iVar5].color_a = 0.223;
          do {
            iVar9 = -100;
            type_id = PROJECTILE_TYPE_SHOTGUN;
            local_8 = fVar1 + (&player_state_table)[render_overlay_player_index].pos_y;
            local_c = fVar10 + (&player_state_table)[render_overlay_player_index].pos_x;
            iVar5 = crt_rand();
            iVar5 = projectile_spawn(&local_c,(float)(iVar5 % 200 + -100) * 0.0013 + fVar2,type_id,
                                     iVar9);
            iVar9 = crt_rand();
            iVar6 = iVar6 + -1;
            projectile_pool[iVar5].pos.tail.vy.speed_scale = (float)(iVar9 % 100) * 0.01 + 1.0;
          } while (iVar6 != 0);
        }
        iVar6 = perk_id_sharpshooter;
        iVar5 = render_overlay_player_index;
        if (player_state_table.perk_counts[perk_id_sharpshooter] < 1) {
          (&player_state_table)[render_overlay_player_index].spread_heat =
               movement_decay_rate * frame_dt * 150.0 +
               (&player_state_table)[render_overlay_player_index].spread_heat;
        }
        if (movement_decay_rate + movement_decay_rate < (&player_state_table)[iVar5].spread_heat) {
          (&player_state_table)[iVar5].spread_heat = movement_decay_rate + movement_decay_rate;
        }
        iVar9 = perk_id_fastshot;
        (&player_state_table)[iVar5].spread_heat =
             movement_decay_rate * (&player_state_table)[iVar5].spread_heat;
        if (0 < player_state_table.perk_counts[iVar9]) {
          (&player_state_table)[iVar5].shot_cooldown =
               (&player_state_table)[iVar5].shot_cooldown * 0.88;
        }
        if (0 < player_state_table.perk_counts[iVar6]) {
          (&player_state_table)[iVar5].shot_cooldown =
               (&player_state_table)[iVar5].shot_cooldown * 1.05;
        }
        if ((float)(&player_state_table)[iVar5].ammo <= 0.0) {
          player_start_reload();
          iVar5 = render_overlay_player_index;
        }
      }
    }
    fVar2 = (&player_state_table)[iVar5].move_phase;
    while (14.0 < fVar2) {
      fVar2 = (&player_state_table)[iVar5].move_phase - 14.0;
      (&player_state_table)[iVar5].move_phase = fVar2;
    }
    fVar2 = (&player_state_table)[iVar5].size * 0.5;
    if ((&player_state_table)[iVar5].pos_x < fVar2) {
      (&player_state_table)[iVar5].pos_x = fVar2;
    }
    if ((float)terrain_texture_width - fVar2 < (&player_state_table)[iVar5].pos_x) {
      (&player_state_table)[iVar5].pos_x = (float)terrain_texture_width - fVar2;
    }
    if ((&player_state_table)[iVar5].pos_y < fVar2) {
      (&player_state_table)[iVar5].pos_y = fVar2;
    }
    if ((float)terrain_texture_height - fVar2 < (&player_state_table)[iVar5].pos_y) {
      (&player_state_table)[iVar5].pos_y = (float)terrain_texture_height - fVar2;
    }
    if (0.8 < (&player_state_table)[iVar5].muzzle_flash_alpha) {
      (&player_state_table)[iVar5].muzzle_flash_alpha = 0.8;
    }
  }
  return;
}


