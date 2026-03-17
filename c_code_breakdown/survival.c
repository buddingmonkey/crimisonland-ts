/* rush_mode_update @ 004072b0 */

/* rush mode update: spawns edge waves and handles demo exit */

void rush_mode_update(void)

{
  int iVar1;
  float10 fVar2;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  undefined4 local_4;
  
  player_state_table.weapon_id = 2;
  player_state_table.ammo = 0x41f00000;
  player2_weapon_id = 2;
  player2_ammo = 0x41f00000;
  if (console_open_flag == '\0') {
    survival_spawn_cooldown = survival_spawn_cooldown - config_blob.reserved0._20_4_ * frame_dt_ms;
    while (survival_spawn_cooldown < 0) {
      survival_spawn_cooldown = survival_spawn_cooldown + 0xfa;
      fVar2 = (float10)(int)(highscore_active_record.survival_elapsed_ms + 1);
      local_4 = 0x3f800000;
      local_10 = (float)(fVar2 * (float10)8.333333e-06 + (float10)0.3);
      local_c = (float)(fVar2 * (float10)10000.0 + (float10)0.3);
      fVar2 = (float10)fsin(fVar2 * (float10)0.000100000005);
      local_8 = (float)(fVar2 + (float10)0.3);
      if (0.0 <= local_10) {
        if (1.0 < local_10) {
          local_10 = 1.0;
        }
      }
      else {
        local_10 = 0.0;
      }
      if (0.0 <= local_c) {
        if (1.0 < local_c) {
          local_c = 1.0;
        }
      }
      else {
        local_c = 0.0;
      }
      if (0.0 <= local_8) {
        if (1.0 < local_8) {
          local_8 = 1.0;
        }
      }
      else {
        local_8 = 0.0;
      }
      local_20 = (float)terrain_texture_width + 64.0;
      fVar2 = (float10)fcos((float10)(int)highscore_active_record.survival_elapsed_ms *
                            (float10)0.001);
      local_1c = (float)((float10)terrain_texture_height * (float10)0.5 + fVar2 * (float10)256.0);
      iVar1 = creature_spawn(&local_20,&local_10,2);
      local_18 = -64.0;
      fVar2 = (float10)fsin((float10)(int)highscore_active_record.survival_elapsed_ms *
                            (float10)0.001);
      (&creature_pool)[iVar1].ai_mode = 8;
      local_14 = (float)((float10)terrain_texture_height * (float10)0.5 + fVar2 * (float10)256.0);
      iVar1 = creature_spawn(&local_18,&local_10,3);
      (&creature_pool)[iVar1].ai_mode = 8;
      (&creature_pool)[iVar1].flags = (&creature_pool)[iVar1].flags | 0x80;
      (&creature_pool)[iVar1].move_speed = (&creature_pool)[iVar1].move_speed * 1.4;
    }
    if ((demo_mode_active != '\0') && (demo_time_limit_ms < quest_spawn_timeline)) {
      render_pass_mode = 0;
      demo_mode_start();
    }
  }
  return;
}



/* survival_update @ 00407cd0 */

/* main survival mode update: timers, scripted spawns, and enemy wave spawning */

void survival_update(void)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  float *pfVar7;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (console_open_flag != '\0') {
    return;
  }
  quest_spawn_timeline = quest_spawn_timeline + frame_dt_ms;
  if (demo_mode_active != '\0') {
    if (quest_spawn_timeline <= demo_time_limit_ms) {
      return;
    }
    render_pass_mode = 0;
    demo_mode_start();
    return;
  }
  if (config_blob.reserved0._20_4_ == 1) {
    if ((((survival_reward_damage_seen == '\0') && (survival_reward_fire_seen == '\0')) &&
        (64000 < (int)highscore_active_record.survival_elapsed_ms)) &&
       (survival_reward_handout_enabled != '\0')) {
      if (player_state_table.weapon_id == 1) {
        weapon_assign_player(0,0x18);
        player_last_weapon_id = 0x18;
      }
      survival_reward_handout_enabled = '\0';
      survival_reward_damage_seen = '\x01';
      survival_reward_fire_seen = '\x01';
    }
    if (((survival_recent_death_count == 3) && (survival_reward_fire_seen == '\0')) &&
       ((local_44 = (survival_recent_death_pos_2.y +
                    survival_recent_death_pos_1.y + survival_recent_death_pos.y) * 0.33333334,
        fVar1 = player_state_table.pos_x -
                (survival_recent_death_pos.x + survival_recent_death_pos_1.x +
                survival_recent_death_pos_2.x) * 0.33333334,
        SQRT(fVar1 * fVar1 +
             (player_state_table.pos_y - local_44) * (player_state_table.pos_y - local_44)) < 16.0
        && (player_state_table.health < 15.0)))) {
      weapon_assign_player(0,0x19);
      player_last_weapon_id = 0x19;
      survival_reward_fire_seen = '\x01';
      survival_reward_handout_enabled = '\0';
    }
  }
  if (survival_spawn_stage == 0) {
    if (player_state_table.level < 5) goto LAB_004082d6;
    survival_spawn_stage = 1;
    local_48 = -164.0;
    local_44 = 512.0;
    creature_spawn_template(0x12,&local_48,3.1415927);
    local_48 = 1188.0;
    local_44 = 512.0;
    creature_spawn_template(0x12,&local_48,3.1415927);
  }
  if (survival_spawn_stage == 1) {
    if (player_state_table.level < 9) goto LAB_004082d6;
    survival_spawn_stage = 2;
    local_48 = 1088.0;
    local_44 = 512.0;
    creature_spawn_template(0x2c,&local_48,3.1415927);
  }
  if (survival_spawn_stage == 2) {
    if (player_state_table.level < 0xb) goto LAB_004082d6;
    survival_spawn_stage = 3;
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = 1088.0;
      local_3c = (float)(int)local_48 * 42.666668 + 256.0;
      creature_spawn_template(0x35,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 0xc);
  }
  if (survival_spawn_stage == 3) {
    if (player_state_table.level < 0xd) goto LAB_004082d6;
    survival_spawn_stage = 4;
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = 1088.0;
      local_3c = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x2b,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
  }
  if (survival_spawn_stage == 4) {
    if (player_state_table.level < 0xf) goto LAB_004082d6;
    survival_spawn_stage = 5;
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = 1088.0;
      local_3c = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x38,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = -64.0;
      local_3c = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x38,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
  }
  if (survival_spawn_stage == 5) {
    if (player_state_table.level < 0x11) goto LAB_004082d6;
    survival_spawn_stage = 6;
    local_40 = 1088.0;
    local_3c = 512.0;
    creature_spawn_template(0x3a,&local_40,3.1415927);
  }
  if (survival_spawn_stage == 6) {
    if (player_state_table.level < 0x13) goto LAB_004082d6;
    survival_spawn_stage = 7;
    local_40 = 640.0;
    local_3c = 512.0;
    creature_spawn_template(1,&local_40,3.1415927);
  }
  if (survival_spawn_stage == 7) {
    if (player_state_table.level < 0x15) goto LAB_004082d6;
    survival_spawn_stage = 8;
    local_40 = 384.0;
    local_3c = 256.0;
    creature_spawn_template(1,&local_40,3.1415927);
    local_40 = 640.0;
    local_3c = 768.0;
    creature_spawn_template(1,&local_40,3.1415927);
  }
  if (survival_spawn_stage == 8) {
    if (player_state_table.level < 0x1a) goto LAB_004082d6;
    survival_spawn_stage = 9;
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = 1088.0;
      local_3c = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x3c,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_40 = -64.0;
      local_3c = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x3c,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
  }
  if ((survival_spawn_stage == 9) && (0x1f < player_state_table.level)) {
    survival_spawn_stage = 10;
    local_40 = 1088.0;
    local_3c = 512.0;
    creature_spawn_template(0x3a,&local_40,3.1415927);
    local_40 = -64.0;
    local_3c = 512.0;
    creature_spawn_template(0x3a,&local_40,3.1415927);
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_3c = -64.0;
      local_40 = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x3c,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
    local_48 = 0.0;
    do {
      fVar1 = local_48;
      local_3c = 1088.0;
      local_40 = (float)(int)local_48 * 64.0 + 384.0;
      creature_spawn_template(0x3c,&local_40,3.1415927);
      local_48 = (float)((int)fVar1 + 1);
    } while ((int)local_48 < 4);
  }
LAB_004082d6:
  survival_spawn_cooldown = survival_spawn_cooldown - config_blob.reserved0._20_4_ * frame_dt_ms;
  render_overlay_player_index = 0;
joined_r0x004082fb:
  if (-1 < survival_spawn_cooldown) {
    config_blob.reserved0[0x14] = config_blob.reserved0[0x14];
    config_blob.reserved0[0x15] = config_blob.reserved0[0x15];
    config_blob.reserved0[0x16] = config_blob.reserved0[0x16];
    config_blob.reserved0[0x17] = config_blob.reserved0[0x17];
    return;
  }
  iVar5 = 500 - (int)highscore_active_record.survival_elapsed_ms / 0x708;
  if (iVar5 < 0) {
    uVar6 = 1U - iVar5 >> 1;
    iVar5 = iVar5 + uVar6 * 2;
    do {
      uVar2 = crt_rand();
      iVar3 = terrain_texture_height;
      iVar4 = terrain_texture_width;
      switch(uVar2 & 3) {
      case 0:
        iVar3 = crt_rand();
        local_48 = (float)(iVar3 % iVar4);
        local_3c = -40.0;
        pfVar7 = &local_40;
        local_40 = (float)(int)local_48;
        break;
      case 1:
        iVar3 = crt_rand();
        local_48 = (float)(iVar3 % iVar4);
        pfVar7 = &local_38;
        local_38 = (float)(int)local_48;
        local_34 = (float)terrain_texture_height + 40.0;
        break;
      case 2:
        iVar4 = crt_rand();
        local_48 = (float)(iVar4 % iVar3);
        pfVar7 = &local_30;
        local_30 = -40.0;
        local_2c = (float)(int)local_48;
        break;
      case 3:
        iVar4 = crt_rand();
        local_48 = (float)(iVar4 % iVar3);
        pfVar7 = &local_28;
        local_24 = (float)(int)local_48;
        local_28 = (float)terrain_texture_width + 40.0;
        break;
      default:
        goto switchD_00408344_default;
      }
      survival_spawn_creature(pfVar7);
switchD_00408344_default:
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  if (iVar5 < 1) {
    iVar5 = 1;
  }
  survival_spawn_cooldown = survival_spawn_cooldown + iVar5;
  uVar6 = crt_rand();
  iVar4 = terrain_texture_height;
  iVar5 = terrain_texture_width;
  switch(uVar6 & 3) {
  case 0:
    iVar4 = crt_rand();
    local_48 = (float)(iVar4 % iVar5);
    local_1c = 0xc2200000;
    pfVar7 = &local_20;
    local_20 = (float)(int)local_48;
    break;
  case 1:
    iVar4 = crt_rand();
    local_48 = (float)(iVar4 % iVar5);
    pfVar7 = &local_18;
    local_18 = (float)(int)local_48;
    local_14 = (float)terrain_texture_height + 40.0;
    break;
  case 2:
    iVar5 = crt_rand();
    local_48 = (float)(iVar5 % iVar4);
    pfVar7 = &local_10;
    local_10 = -40.0;
    local_c = (float)(int)local_48;
    break;
  case 3:
    iVar5 = crt_rand();
    local_48 = (float)(iVar5 % iVar4);
    pfVar7 = &local_8;
    local_4 = (float)(int)local_48;
    local_8 = (float)terrain_texture_width + 40.0;
    break;
  default:
    goto joined_r0x004082fb;
  }
  survival_spawn_creature(pfVar7);
  goto joined_r0x004082fb;
}



/* survival_gameplay_update_and_render @ 004457c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* survival mode frame loop: effects, spawns, death handling, world render, HUD, and debug name
   input */

void survival_gameplay_update_and_render(void)

{
  undefined1 *puVar1;
  byte bVar2;
  IGrim2D_vtbl *pIVar3;
  IGrim2D *pIVar4;
  int iVar5;
  uint uVar6;
  bonus_entry_t *pbVar7;
  byte *pbVar8;
  bool bVar9;
  float10 fVar10;
  longlong lVar11;
  char *pcVar12;
  float a;
  float fVar13;
  float local_30;
  float fStack_2c;
  float local_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float local_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  local_30 = (float)((uint)local_30 & 0xffffff00);
  local_28 = (float)((uint)local_28 & 0xffffff00);
  if ((camera_follow_init_flags & 1) == 0) {
    camera_follow_x = player_state_table.pos_x + 128.0;
    camera_follow_init_flags = camera_follow_init_flags | 1;
    camera_follow_y = player_state_table.pos_y;
    crt_atexit(&DAT_00445ff0);
  }
  pIVar4 = grim_interface_ptr;
  if (creature_name_input_reset != '\0') {
    creature_name_input_cursor = 0;
    creature_name_input_buffer = 0;
    creature_name_input_reset = '\0';
  }
  local_14 = (float)config_blob.screen_height - 128.0;
  (&creature_name_input_next)[creature_name_input_cursor] = 0;
  iVar5 = (*pIVar4->vtable->grim_is_key_down)(0x1c);
  if (((char)iVar5 != '\0') && (0 < creature_name_input_cursor)) {
    sfx_play(sfx_ui_typeenter);
    shots_fired_count = shots_fired_count + 1;
    (&creature_name_input_buffer)[creature_name_input_cursor] = 0;
    iVar5 = creature_find_by_name(&creature_name_input_buffer);
    if (iVar5 == -1) {
      pbVar8 = &creature_name_input_buffer;
      pcVar12 = s_reload_00478e38;
      do {
        bVar2 = *pcVar12;
        bVar9 = bVar2 < *pbVar8;
        if (bVar2 != *pbVar8) {
LAB_00445900:
          iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_00445905;
        }
        if (bVar2 == 0) break;
        bVar2 = ((byte *)pcVar12)[1];
        bVar9 = bVar2 < pbVar8[1];
        if (bVar2 != pbVar8[1]) goto LAB_00445900;
        pcVar12 = (char *)((byte *)pcVar12 + 2);
        pbVar8 = pbVar8 + 2;
      } while (bVar2 != 0);
      iVar5 = 0;
LAB_00445905:
      if (iVar5 == 0) {
        local_28 = (float)CONCAT31(local_28._1_3_,1);
      }
    }
    else {
      local_30 = (float)CONCAT31(local_30._1_3_,1);
      camera_follow_x = (&creature_pool)[iVar5].pos_x;
      camera_follow_y = (&creature_pool)[iVar5].pos_y;
      shots_hit_count = shots_hit_count + 1;
    }
    creature_name_input_cursor = 0;
    creature_name_input_buffer = 0;
  }
  iVar5 = console_input_poll();
  if ((iVar5 != 0) && (iVar5 != 0xd)) {
    if (iVar5 == 8) {
      uVar6 = crt_rand();
      uVar6 = uVar6 & 0x80000001;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
      }
      sfx_play(uVar6 + _sfx_ui_typeclick_01);
      if (creature_name_input_cursor < 1) {
        creature_name_input_buffer = 0;
      }
      else {
        puVar1 = &creature_name_input_penult + creature_name_input_cursor;
        creature_name_input_cursor = creature_name_input_cursor + -1;
        *puVar1 = 0;
      }
    }
    else {
      if (creature_name_input_cursor < 0x11) {
        (&creature_name_input_buffer)[creature_name_input_cursor] = (char)iVar5;
        creature_name_input_cursor = creature_name_input_cursor + 1;
      }
      (&creature_name_input_buffer)[creature_name_input_cursor] = 0;
      uVar6 = crt_rand();
      uVar6 = uVar6 & 0x80000001;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
      }
      sfx_play(uVar6 + _sfx_ui_typeclick_01);
    }
  }
  perks_update_effects();
  fStack_24 = frame_dt;
  if (time_scale_active != '\0') {
    frame_dt = frame_dt * 0.3;
    time_scale_factor = 0x3e99999a;
    lVar11 = __ftol();
    frame_dt_ms = (int)lVar11;
  }
  effects_update();
  if (game_state_id == 0x12) {
    creature_update_all();
    projectile_update();
    fVar13 = local_30;
    if ((game_state_id == 0x12) &&
       (render_overlay_player_index = 0, 0 < (int)config_blob.reserved0._20_4_)) {
      do {
        player_fire_weapon('p',SUB41(fVar13,0));
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
    }
  }
  render_overlay_player_index = 0;
  player_state_table.weapon_id = 3;
  player_state_table.ammo = 0x41f00000;
  if (console_open_flag == '\0') {
    survival_spawn_cooldown = survival_spawn_cooldown - config_blob.reserved0._20_4_ * frame_dt_ms;
  }
  while (survival_spawn_cooldown < 0) {
    survival_spawn_cooldown =
         survival_spawn_cooldown + (0xdac - (int)highscore_active_record.survival_elapsed_ms / 800);
    if (survival_spawn_cooldown < 100) {
      survival_spawn_cooldown = 100;
    }
    local_28 = (float)(highscore_active_record.survival_elapsed_ms + 1);
    uStack_4 = 0x3f800000;
    fVar10 = (float10)(int)local_28;
    fStack_10 = (float)(fVar10 * (float10)8.333333e-06 + (float10)0.3);
    fStack_c = (float)(fVar10 * (float10)10000.0 + (float10)0.3);
    fVar10 = (float10)fsin(fVar10 * (float10)0.000100000005);
    fStack_8 = (float)(fVar10 + (float10)0.3);
    if (0.0 <= fStack_10) {
      if (1.0 < fStack_10) {
        fStack_10 = 1.0;
      }
    }
    else {
      fStack_10 = 0.0;
    }
    if (0.0 <= fStack_c) {
      if (1.0 < fStack_c) {
        fStack_c = 1.0;
      }
    }
    else {
      fStack_c = 0.0;
    }
    if (0.0 <= fStack_8) {
      if (1.0 < fStack_8) {
        fStack_8 = 1.0;
      }
    }
    else {
      fStack_8 = 0.0;
    }
    creature_search_tick = creature_search_tick + 1;
    local_30 = (float)terrain_texture_width + 64.0;
    fVar10 = (float10)fcos((float10)(int)highscore_active_record.survival_elapsed_ms *
                           (float10)0.001);
    fStack_2c = (float)((float10)terrain_texture_height * (float10)0.5 + fVar10 * (float10)256.0);
    iVar5 = creature_spawn_tinted(&local_30,&fStack_10,4);
    creature_name_assign_random(iVar5);
    fStack_20 = -64.0;
    fVar10 = (float10)fcos((float10)(int)highscore_active_record.survival_elapsed_ms *
                           (float10)0.001);
    fStack_1c = (float)((float10)terrain_texture_height * (float10)0.5 + fVar10 * (float10)256.0);
    iVar5 = creature_spawn_tinted(&fStack_20,&fStack_10,2);
    creature_name_assign_random(iVar5);
  }
  highscore_active_record.score_xp = player_state_table.experience;
  if (console_open_flag == '\0') {
    bonus_weapon_power_up_timer = 0;
    highscore_active_record.survival_elapsed_ms =
         highscore_active_record.survival_elapsed_ms + frame_dt_ms;
    bonus_reflex_boost_timer = 0;
    time_scale_active = '\0';
    (&weapon_usage_time)[player_state_table.weapon_id] =
         (&weapon_usage_time)[player_state_table.weapon_id] + frame_dt_ms;
  }
  camera_update();
  gameplay_render_world();
  creature_name_draw_labels();
  pbVar7 = bonus_pool;
  do {
    pbVar7->bonus_id = BONUS_ID_NONE;
    pbVar7 = pbVar7 + 1;
  } while ((int)pbVar7 < 0x482b08);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  if ((((demo_mode_active == '\0') && (player_state_table.health <= 0.0)) &&
      (player_state_table.death_timer < 0.0)) &&
     ((config_blob.reserved0._20_4_ == 1 ||
      ((player2_health <= 0.0 && (_player2_death_timer < 0.0)))))) {
    render_pass_mode = 0;
    game_state_pending = 7;
    ui_transition_direction = 0;
    (*grim_interface_ptr->vtable->grim_flush_input)();
    console_input_poll();
    sfx_mute_all(music_track_extra_0);
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_shortie_monk_id);
  }
  frame_dt = fStack_24;
  lVar11 = __ftol();
  frame_dt_ms = (int)lVar11;
  perk_prompt_update_and_render();
  hud_update_and_render();
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  fVar13 = 2.94273e-44;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(-1.0,local_28 - 16.0,182.0,53.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  fVar13 = fVar13 + 1.0;
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,6.0,fVar13,&s_creature_name_font_spec,&creature_name_input_buffer);
  a = 1.0;
  fVar10 = (float10)fsin((float10)game_time_s * (float10)4.0);
  if ((float10)0.0 < fVar10) {
    a = 0.4;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
  pcVar12 = &console_cmd_table_entry;
  pIVar3 = grim_interface_ptr->vtable;
  iVar5 = (*pIVar3->grim_measure_text_width)(&creature_name_input_buffer);
  (*pIVar3->grim_draw_text_small_fmt)(grim_interface_ptr,(float)iVar5 + 14.0,fVar13,pcVar12);
  highscore_active_record.shots_hit = shots_hit_count;
  highscore_active_record.shots_fired = shots_fired_count;
  ui_elements_update_and_render();
  return;
}


