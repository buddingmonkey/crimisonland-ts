/* bonus_apply @ 00409890 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* applies a picked bonus to the player and spawns related effects */

void __cdecl bonus_apply(int player_index,bonus_entry_t *bonus_entry)

{
  float fVar1;
  bonus_id_t bVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  float *pfVar8;
  creature_t *pcVar9;
  float10 fVar10;
  projectile_type_id_t pVar11;
  int owner_id;
  float local_10 [4];
  
  sfx_play(sfx_ui_bonus);
  local_10[0] = 1.0;
  iVar4 = perk_count_get(perk_id_bonus_economist);
  if (iVar4 != 0) {
    local_10[0] = 1.5;
  }
  bVar2 = bonus_entry->bonus_id;
  if (bVar2 == BONUS_ID_WEAPON) {
    weapon_assign_player(player_index,(bonus_entry->time).amount);
  }
  else if (bVar2 == BONUS_ID_MEDIKIT) {
    pfVar8 = &(&player_state_table)[player_index].health;
    if (((&player_state_table)[player_index].health < 100.0) &&
       (fVar1 = *pfVar8, *pfVar8 = fVar1 + 10.0, 100.0 < fVar1 + 10.0)) {
      *pfVar8 = 100.0;
    }
  }
  else if (bVar2 == BONUS_ID_REFLEX_BOOST) {
    if (bonus_reflex_boost_timer <= 0.0) {
      bonus_hud_add_slot(bonus_reflex_boost_name,bonus_reflex_boost_icon_id,&bonus_reflex_boost_timer,0);
    }
    bonus_reflex_boost_timer =
         (float)(bonus_entry->time).amount * local_10[0] + bonus_reflex_boost_timer;
    if (0 < (int)config_blob.reserved0._20_4_) {
      piVar5 = &player_state_table.ammo;
      iVar4 = config_blob.reserved0._20_4_;
      do {
        *piVar5 = piVar5[-2];
        piVar5[1] = 0;
        piVar5 = piVar5 + 0xd8;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    local_10[1] = 0.6;
    local_10[0] = 0.6;
    effect_template_color_g = 0x3f19999a;
    local_10[2] = 1.0;
    local_10[3] = 1.0;
    effect_template_color_r = 0x3f19999a;
    effect_template_flags = 0x19;
    effect_template_color_b = 0x3f800000;
    effect_template_color_a = 0x3f800000;
    effect_template_lifetime = 0x3e800000;
    effect_template_age = 0;
    effect_template_half_width = 0x42000000;
    effect_template_half_height = 0x42000000;
    effect_template_rotation = 0.0;
    effect_template_vel_x = 0.0;
    effect_template_vel_y = 0.0;
    effect_template_scale_step = 0x42480000;
    effect_spawn(1,&(bonus_entry->time).pos_x);
    effect_template_rotation = 0.0;
    effect_template_vel_x = 0.0;
    effect_template_vel_y = 0.0;
  }
  else if (bVar2 == BONUS_ID_WEAPON_POWER_UP) {
    if (bonus_weapon_power_up_timer <= 0.0) {
      bonus_hud_add_slot(bonus_weapon_power_up_name,bonus_weapon_power_up_icon_id,&bonus_weapon_power_up_timer,0);
    }
    bonus_weapon_power_up_timer =
         (float)(bonus_entry->time).amount * local_10[0] + bonus_weapon_power_up_timer;
    (&player_state_table)[player_index].weapon_reset_latch = 0;
    (&player_state_table)[player_index].shot_cooldown = 0.0;
    (&player_state_table)[player_index].reload_timer = 0.0;
    (&player_state_table)[player_index].ammo = (&player_state_table)[player_index].clip_size;
  }
  else if (bVar2 == BONUS_ID_SPEED) {
    if ((player_state_table.speed_bonus_timer <= 0.0) && (player2_speed_bonus_timer <= 0.0)) {
      bonus_hud_add_slot(bonus_speed_name,bonus_speed_icon_id,0x490bc4,&player2_speed_bonus_timer);
    }
    (&player_state_table)[player_index].speed_bonus_timer =
         (float)(bonus_entry->time).amount * local_10[0] +
         (&player_state_table)[player_index].speed_bonus_timer;
  }
  else if (bVar2 == BONUS_ID_FREEZE) {
    if (bonus_freeze_timer <= 0.0) {
      bonus_hud_add_slot(bonus_freeze_name,bonus_freeze_icon_id,&bonus_freeze_timer,0);
    }
    pfVar8 = &creature_pool.pos_x;
    bonus_freeze_timer = (float)(bonus_entry->time).amount * local_10[0] + bonus_freeze_timer;
    do {
      if ((((creature_t *)(pfVar8 + -5))->active != '\0') && (pfVar8[4] <= 0.0)) {
        iVar4 = 8;
        do {
          iVar6 = crt_rand();
          effect_spawn_freeze_shard(pfVar8,(float)(iVar6 % 0x264) * 0.01);
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        iVar4 = crt_rand();
        effect_spawn_freeze_shatter(pfVar8,(float)(iVar4 % 0x264) * 0.01);
        ((creature_t *)(pfVar8 + -5))->active = '\0';
      }
      pfVar8 = pfVar8 + 0x26;
    } while ((int)pfVar8 < 0x4aa34c);
    local_10[0] = 0.3;
    local_10[1] = 0.5;
    local_10[2] = 0.8;
    local_10[3] = 1.0;
    effect_template_color_r = 0x3e99999a;
    effect_template_flags = 0x19;
    effect_template_color_g = 0x3f000000;
    effect_template_color_b = 0x3f4ccccd;
    effect_template_color_a = 0x3f800000;
    effect_template_lifetime = 0x3e800000;
    effect_template_age = 0;
    effect_template_half_width = 0x42000000;
    effect_template_half_height = 0x42000000;
    effect_template_rotation = 0.0;
    effect_template_vel_x = 0.0;
    effect_template_vel_y = 0.0;
    effect_template_scale_step = 0x42480000;
    effect_spawn(1,&(bonus_entry->time).pos_x);
    sfx_play_panned(sfx_shockwave);
    effect_template_rotation = 0.0;
    effect_template_vel_x = 0.0;
    effect_template_vel_y = 0.0;
  }
  else if (bVar2 == BONUS_ID_SHIELD) {
    if ((player_state_table.shield_timer <= 0.0) && (player2_shield_timer <= 0.0)) {
      bonus_hud_add_slot(bonus_shield_name,bonus_shield_icon_id,0x490bc8,&player2_shield_timer);
    }
    (&player_state_table)[player_index].shield_timer =
         (float)(bonus_entry->time).amount * local_10[0] +
         (&player_state_table)[player_index].shield_timer;
  }
  else if (bVar2 == BONUS_ID_SHOCK_CHAIN) {
    bonus_spawn_guard = 1;
    if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
      iVar4 = -100;
    }
    else {
      iVar4 = -1 - player_index;
    }
    pfVar8 = &(bonus_entry->time).pos_x;
    shock_chain_links_left = 0x20;
    iVar6 = creature_find_nearest(pfVar8,-1,0.0);
    fVar10 = (float10)fpatan((float10)(&creature_pool)[iVar6].pos_y -
                             (float10)(bonus_entry->time).pos_y,
                             (float10)(&creature_pool)[iVar6].pos_x - (float10)*pfVar8);
    shock_chain_projectile_id =
         projectile_spawn(pfVar8,(float)((fVar10 - (float10)1.5707964) - (float10)3.1415927),
                          PROJECTILE_TYPE_ION_RIFLE,iVar4);
    bonus_spawn_guard = 0;
    sfx_play_panned(sfx_shock_hit_01);
  }
  else if (bVar2 == BONUS_ID_FIREBLAST) {
    bonus_spawn_guard = 1;
    if (*(float *)((int)cv_friendlyFire + 0xc) == 0.0) {
      iVar4 = -100;
    }
    else {
      iVar4 = -1 - player_index;
    }
    player_index = 0;
    do {
      projectile_spawn(&(bonus_entry->time).pos_x,(float)player_index * 0.3926991,
                       PROJECTILE_TYPE_PLASMA_RIFLE,iVar4);
      player_index = player_index + 1;
    } while (player_index < 0x10);
    bonus_spawn_guard = 0;
    sfx_play_panned(sfx_explosion_medium);
  }
  else if (bVar2 == BONUS_ID_FIRE_BULLETS) {
    if ((player_state_table.fire_bullets_timer <= 0.0) && (player2_fire_bullets_timer <= 0.0)) {
      bonus_hud_add_slot(bonus_fire_bullets_name,bonus_fire_bullets_icon_id,0x490bcc,&player2_fire_bullets_timer);
    }
    (&player_state_table)[player_index].fire_bullets_timer =
         local_10[0] * 5.0 + (&player_state_table)[player_index].fire_bullets_timer;
    (&player_state_table)[player_index].weapon_reset_latch = 0;
    (&player_state_table)[player_index].shot_cooldown = 0.0;
    (&player_state_table)[player_index].reload_timer = 0.0;
    (&player_state_table)[player_index].ammo = (&player_state_table)[player_index].clip_size;
  }
  else if (bVar2 == BONUS_ID_ENERGIZER) {
    if (bonus_energizer_timer <= 0.0) {
      bonus_hud_add_slot(bonus_energizer_name,bonus_energizer_icon_id,&bonus_energizer_timer,0);
    }
    bonus_energizer_timer = local_10[0] * 8.0 + bonus_energizer_timer;
  }
  else if (bVar2 == BONUS_ID_DOUBLE_EXPERIENCE) {
    if (bonus_double_xp_timer <= 0.0) {
      bonus_hud_add_slot(bonus_double_xp_name,bonus_double_xp_icon_id,&bonus_double_xp_timer,0);
    }
    bonus_double_xp_timer = local_10[0] * 6.0 + bonus_double_xp_timer;
  }
  else if (bVar2 == BONUS_ID_NUKE) {
    uVar7 = crt_rand();
    iVar4 = (uVar7 & 3) + 4;
    if (iVar4 != 0) {
      do {
        owner_id = -100;
        pVar11 = PROJECTILE_TYPE_PISTOL;
        iVar6 = crt_rand();
        iVar6 = projectile_spawn(&(bonus_entry->time).pos_x,(float)(iVar6 % 0x274) * 0.01,pVar11,
                                 owner_id);
        if (iVar6 != -1) {
          pfVar8 = &projectile_pool[iVar6].pos.tail.vy.speed_scale;
          iVar6 = crt_rand();
          *pfVar8 = ((float)(iVar6 % 0x32) * 0.01 + 0.5) * *pfVar8;
        }
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar6 = -100;
    pVar11 = PROJECTILE_TYPE_GAUSS_GUN;
    pfVar8 = &(bonus_entry->time).pos_x;
    iVar4 = crt_rand();
    projectile_spawn(pfVar8,(float)(iVar4 % 0x274) * 0.01,pVar11,iVar6);
    iVar6 = -100;
    pVar11 = PROJECTILE_TYPE_GAUSS_GUN;
    iVar4 = crt_rand();
    projectile_spawn(pfVar8,(float)(iVar4 % 0x274) * 0.01,pVar11,iVar6);
    effect_spawn_explosion_burst(pfVar8,1.0);
    camera_shake_pulses = 0x14;
    camera_shake_timer = 0x3e4ccccd;
    bonus_spawn_guard = 1;
    iVar4 = 0;
    pcVar9 = &creature_pool;
    do {
      if ((((pcVar9->active != '\0') && (ABS(pcVar9->pos_x - *pfVar8) <= 256.0)) &&
          (ABS(pcVar9->pos_y - (bonus_entry->time).pos_y) <= 256.0)) &&
         (fVar1 = pcVar9->pos_x - *pfVar8, fVar3 = pcVar9->pos_y - (bonus_entry->time).pos_y,
         fVar1 = 256.0 - SQRT(fVar3 * fVar3 + fVar1 * fVar1), 0.0 < fVar1)) {
        local_10[0] = 0.0;
        local_10[1] = 0.0;
        creature_apply_damage(iVar4,fVar1 * 5.0,3,local_10);
      }
      pcVar9 = pcVar9 + 1;
      iVar4 = iVar4 + 1;
    } while ((int)pcVar9 < 0x4aa338);
    bonus_spawn_guard = 0;
    sfx_play_panned(sfx_explosion_large);
    sfx_play_panned(sfx_shockwave);
  }
  else if (bVar2 == BONUS_ID_POINTS) {
    player_state_table.experience = player_state_table.experience + (bonus_entry->time).amount;
  }
  local_10[0] = 0.4;
  local_10[1] = 0.5;
  local_10[2] = 1.0;
  local_10[3] = 0.5;
  effect_template_color_r = 0x3ecccccd;
  effect_template_flags = 0x1d;
  effect_template_color_g = 0x3f000000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f000000;
  effect_template_lifetime = 0x3ecccccd;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  if (bonus_entry->bonus_id != BONUS_ID_NUKE) {
    iVar4 = 0xc;
    do {
      uVar7 = crt_rand();
      effect_template_rotation = (float)(uVar7 & 0x7f) * 0.049087387;
      uVar7 = crt_rand();
      uVar7 = uVar7 & 0x8000007f;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_x = (float)(int)(uVar7 - 0x40);
      uVar7 = crt_rand();
      uVar7 = uVar7 & 0x8000007f;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_y = (float)(int)(uVar7 - 0x40);
      effect_template_scale_step = 0x3dcccccd;
      effect_spawn(0,&(bonus_entry->time).pos_x);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return;
}



/* bonus_update @ 0040a320 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates bonus lifetimes and handles player pickups */

void bonus_update(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bonus_entry_time_block_t *pbVar5;
  
  if (render_pass_mode != '\0') {
    pbVar5 = &bonus_pool[0].time;
    iVar4 = config_blob.reserved0._20_4_;
    do {
      if (*(int *)((int)(pbVar5 + -1) + 0xc) != 0) {
        cVar1 = *(char *)((int)(pbVar5 + -1) + 0x10);
        if (cVar1 == '\0') {
          fVar2 = pbVar5->time_left - frame_dt;
        }
        else {
          fVar2 = pbVar5->time_left - frame_dt * 3.0;
        }
        pbVar5->time_left = fVar2;
        if ((cVar1 == '\0') && (config_blob.reserved0._24_4_ == 8)) {
          pbVar5->time_left = 5.0;
        }
        if (pbVar5->time_left < 0.0) {
          ((bonus_entry_t *)((int)(pbVar5 + -1) + 0xc))->bonus_id = BONUS_ID_NONE;
        }
        if (cVar1 == '\0') {
          render_overlay_player_index = 0;
          if (0 < iVar4) {
            do {
              fVar2 = pbVar5->pos_x - (&player_state_table)[render_overlay_player_index].pos_x;
              fVar3 = pbVar5->pos_y - (&player_state_table)[render_overlay_player_index].pos_y;
              if (SQRT(fVar3 * fVar3 + fVar2 * fVar2) < 26.0) {
                bonus_apply(render_overlay_player_index,(bonus_entry_t *)((int)(pbVar5 + -1) + 0xc))
                ;
                iVar4 = config_blob.reserved0._20_4_;
                *(undefined1 *)((int)(pbVar5 + -1) + 0x10) = 1;
                pbVar5->time_left = 0.5;
              }
              render_overlay_player_index = render_overlay_player_index + 1;
            } while (render_overlay_player_index < iVar4);
          }
        }
      }
      pbVar5 = (bonus_entry_time_block_t *)((int)(pbVar5 + 1) + 8);
    } while ((int)pbVar5 < 0x482b10);
    render_overlay_player_index = 0;
    if (bonus_freeze_timer <= 0.0) {
      bonus_freeze_timer = 0.0;
    }
    else {
      bonus_freeze_timer = bonus_freeze_timer - frame_dt;
    }
    if (bonus_double_xp_timer <= 0.0) {
      bonus_double_xp_timer = 0.0;
    }
    else {
      bonus_double_xp_timer = bonus_double_xp_timer - frame_dt;
    }
    if (0.0 <= crt_newmode) {
      crt_newmode = (crt_newmode + 1.0) * frame_dt * 1.8 + crt_newmode;
    }
  }
  return;
}



/* bonus_meta_table_ctor @ 004123d0 */

/* [binja] int32_t sub_4123d0() */

int bonus_meta_table_ctor(void)

{
  int extraout_EAX;
  
  crt_ehvec_ctor(&bonus_meta_table,0x14,0xf,&LAB_004123f0,bonus_meta_entry_dtor);
  return extraout_EAX;
}



/* bonus_meta_entry_dtor @ 00412410 */

/* [binja] void* __fastcall sub_412410(int32_t* arg1) */

void * __fastcall bonus_meta_entry_dtor(int *arg1)

{
  void *extraout_EAX;
  void *extraout_EAX_00;
  void *pvVar1;
  
  pvVar1 = (void *)0x0;
  if ((void *)*arg1 != (void *)0x0) {
    crt_free((void *)*arg1);
    pvVar1 = extraout_EAX;
  }
  if ((void *)arg1[1] != (void *)0x0) {
    crt_free((void *)arg1[1]);
    pvVar1 = extraout_EAX_00;
  }
  return pvVar1;
}



/* bonus_meta_table_atexit_register @ 00412440 */

/* [binja] int32_t sub_412440() */

int bonus_meta_table_atexit_register(void)

{
  int iVar1;
  
  iVar1 = crt_atexit(&LAB_00412450);
  return iVar1;
}



/* bonus_pick_random_type @ 00412470 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* rolls a bonus id while respecting timers, perks, quest stage, and enabled flags */

bonus_id_t bonus_pick_random_type(void)

{
  bool bVar1;
  bool bVar2;
  uchar *puVar3;
  int iVar4;
  uint uVar5;
  bonus_id_t bVar6;
  bonus_id_t bVar7;
  bonus_id_t bVar8;
  int local_4;
  
  local_4 = 0;
  bVar2 = false;
  puVar3 = &bonus_pool[0].state;
  do {
    if ((((bonus_entry_t *)(puVar3 + -4))->bonus_id == BONUS_ID_FIRE_BULLETS) && (*puVar3 == '\0'))
    {
      bVar2 = true;
    }
    puVar3 = puVar3 + 0x1c;
  } while ((int)puVar3 < 0x482b0c);
  do {
    iVar4 = crt_rand();
    iVar4 = iVar4 % 0xa2;
    bVar7 = (bonus_id_t)(iVar4 + 1 < 0xe);
    if ((bVar7 == BONUS_ID_NONE) && (iVar4 + -0xc < 2)) {
      bVar7 = BONUS_ID_ENERGIZER;
    }
    iVar4 = iVar4 + -0xd;
    bVar8 = bVar7;
    if (bVar7 == BONUS_ID_ENERGIZER) {
      uVar5 = crt_rand();
      if ((uVar5 & 0x3f) != 0) {
        bVar7 = BONUS_ID_NONE;
LAB_004124e2:
        bVar6 = BONUS_ID_WEAPON;
        do {
          bVar8 = bVar6;
          if (iVar4 < 0xb) break;
          iVar4 = iVar4 + -10;
          bVar6 = bVar6 + BONUS_ID_POINTS;
          bVar8 = bVar7;
        } while ((int)bVar6 < 0xf);
      }
    }
    else if (bVar7 == BONUS_ID_NONE) goto LAB_004124e2;
    if ((shock_chain_links_left < 1) || (bVar8 != BONUS_ID_SHOCK_CHAIN)) {
      if (config_blob.reserved0._24_4_ == 3) {
        if ((((config_blob.hardcore == '\0') || (quest_stage_major != 3)) &&
            (quest_stage_major != 2)) || ((quest_stage_minor != 10 || (bVar8 != BONUS_ID_NUKE))))
        {
          if ((config_blob.hardcore != '\0') && (quest_stage_major == 2)) {
            if (quest_stage_minor == 10) {
joined_r0x00412584:
              if (bVar8 == BONUS_ID_FREEZE) goto LAB_00412613;
            }
            goto LAB_0041258a;
          }
          if (quest_stage_major == 4) {
            if (quest_stage_minor != 10) goto LAB_0041258a;
            if (bVar8 != BONUS_ID_NUKE) goto joined_r0x00412584;
          }
          else if (((quest_stage_major != 5) || (quest_stage_minor != 10)) ||
                  (bVar8 != BONUS_ID_NUKE)) goto LAB_0041258a;
        }
      }
      else {
LAB_0041258a:
        if ((((bonus_freeze_timer <= 0.0) || (bVar8 != BONUS_ID_FREEZE)) &&
            ((((player_state_table.shield_timer <= 0.0 && (player2_shield_timer <= 0.0)) ||
              (bVar8 != BONUS_ID_SHIELD)) &&
             ((iVar4 = perk_count_get(perk_id_my_favourite_weapon), iVar4 == 0 ||
              (bVar8 != BONUS_ID_WEAPON)))))) &&
           (((iVar4 = perk_count_get(perk_id_death_clock), iVar4 == 0 || (bVar8 != BONUS_ID_MEDIKIT)
             ) && (((bVar8 != BONUS_ID_WEAPON || (!bVar2)) &&
                   ((&bonus_meta_table)[bVar8].enabled != '\0')))))) {
          return bVar8;
        }
      }
    }
LAB_00412613:
    bVar1 = 99 < local_4;
    local_4 = local_4 + 1;
    if (bVar1) {
      return BONUS_ID_POINTS;
    }
  } while( true );
}



/* bonus_metadata_init @ 00412660 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* builds bonus metadata table (labels, descriptions, durations) */

void bonus_metadata_init(void)

{
  void *this;
  void *this_00;
  void *this_01;
  void *this_02;
  void *this_03;
  void *this_04;
  void *this_05;
  void *this_06;
  void *this_07;
  void *this_08;
  void *this_09;
  void *this_10;
  void *this_11;
  void *this_12;
  
  bonus_points_format_prefix = strdup_malloc(s_bonus_points_label);
  bonus_xp_desc_ptr = wrap_text_to_width_alloc(this,s_You_gain_some_experience_points__004735e0,0x100);
  bonus_xp_icon_id = 0xc;
  bonus_xp_points_value = 500;
  bonus_points_enabled = 1;
  bonus_new_weapon_name = strdup_malloc(s_bonus_weapon_label);
  bonus_new_weapon_desc = wrap_text_to_width_alloc(this_00,s_You_get_a_new_weapon__004735c0,0x100);
  bonus_new_weapon_icon_id = 0xffffffff;
  bonus_new_weapon_priority = 3;
  bonus_nuke_name = strdup_malloc(&s_bonus_nuke_label);
  bonus_nuke_desc =
       wrap_text_to_width_alloc(this_01,s_An_amazing_explosion_of_ATOMIC_p_00473590,0x100);
  bonus_nuke_priority = 1;
  bonus_double_xp_name = strdup_malloc(s_bonus_double_experience);
  bonus_double_xp_desc =
       wrap_text_to_width_alloc(this_02,s_Every_experience_point_you_get_i_00473534,0x100);
  bonus_double_xp_icon_id = 4;
  bonus_fireblast_name = strdup_malloc(s_bonus_fireblast);
  bonus_fireblast_desc = wrap_text_to_width_alloc(this_03,s_Fireballs_all_over_the_place__00473508,0x100);
  bonus_fireblast_icon_id = 2;
  bonus_shock_chain_name = strdup_malloc(s_bonus_shock_chain);
  bonus_shock_chain_desc =
       wrap_text_to_width_alloc(this_04,s_Chain_of_shocks_shock_the_crowd__004734d8,0x100);
  bonus_shock_chain_icon_id = 3;
  bonus_reflex_boost_name = strdup_malloc(s_bonus_reflex_boost);
  bonus_reflex_boost_desc =
       wrap_text_to_width_alloc(this_05,s_You_get_more_time_to_react_as_th_00473494,0x100);
  bonus_reflex_boost_icon_id = 5;
  bonus_reflex_boost_priority = 3;
  bonus_shield_name = strdup_malloc(s_bonus_shield);
  bonus_shield_desc =
       wrap_text_to_width_alloc(this_06,s_Force_field_protects_you_for_a_w_00473464,0x100);
  bonus_shield_icon_id = 6;
  bonus_shield_priority = 7;
  bonus_freeze_name = strdup_malloc(s_bonus_freeze);
  bonus_freeze_desc = wrap_text_to_width_alloc(this_07,s_Monsters_are_frozen__00473444,0x100);
  bonus_freeze_icon_id = 8;
  bonus_freeze_priority = 5;
  bonus_speed_name = strdup_malloc(s_bonus_speed);
  bonus_speed_desc =
       wrap_text_to_width_alloc(this_08,s_Your_movement_speed_increases_fo_00473410,0x100);
  bonus_speed_icon_id = 9;
  bonus_speed_priority = 8;
  bonus_energizer_name = strdup_malloc(s_Energizer_00473404);
  bonus_energizer_desc =
       wrap_text_to_width_alloc(this_09,s_Suddenly_monsters_run_away_from_y_004733c8,0x100);
  bonus_energizer_icon_id = 10;
  bonus_energizer_priority = 8;
  bonus_weapon_power_up_name = strdup_malloc(s_Weapon_Power_Up_004733b8);
  bonus_weapon_power_up_desc =
       wrap_text_to_width_alloc(this_10,s_Your_firerate_and_load_time_incr_0047337c,0x100);
  bonus_weapon_power_up_icon_id = 7;
  bonus_weapon_power_up_priority = 10;
  bonus_fire_bullets_name = strdup_malloc(s_Fire_Bullets_0047336c);
  bonus_fire_bullets_desc =
       wrap_text_to_width_alloc(this_11,s_For_few_seconds____make_them_cou_00473348,0x100);
  bonus_fire_bullets_icon_id = 0xb;
  bonus_fire_bullets_priority = 4;
  bonus_medikit_name = strdup_malloc(s_MediKit_00473340);
  bonus_medikit_desc =
       wrap_text_to_width_alloc(this_12,s__You_regain_some_of_your_health__0047331b + 1,0x100);
  bonus_medikit_priority = 10;
  bonus_medikit_icon_id = 0xe;
  return;
}



/* bonus_reset_availability @ 00412940 */

/* [binja] char* sub_412940() */

char * bonus_reset_availability(void)

{
  uchar *puVar1;
  
  puVar1 = &bonus_meta_table.enabled;
  do {
    *puVar1 = '\x01';
    puVar1 = puVar1 + 0x14;
  } while ((int)puVar1 < 0x485508);
  bonus_meta_table.enabled = '\0';
  return (char *)puVar1;
}



/* bonus_hud_add_slot @ 0041a810 */

void __cdecl bonus_hud_add_slot(char *param_1,int param_2,float *param_3,float *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  bonus_hud_slot_t *pbVar4;
  int iVar5;
  float **ppfVar6;
  
  iVar2 = 0;
  pbVar4 = bonus_hud_slot_table;
  do {
    if (pbVar4->active == '\0') {
      bonus_hud_slot_table[iVar2].slide.timer_ptr = param_3;
      bonus_hud_slot_table[iVar2].slide.icon_id = param_2;
      uVar1 = config_blob.reserved0._20_4_;
      bonus_hud_slot_table[iVar2].slide.alt_timer_ptr = param_4;
      bonus_hud_slot_table[iVar2].active = '\x01';
      bonus_hud_slot_table[iVar2].slide.slide_x = -184.0;
      bonus_hud_slot_table[iVar2].slide.label = param_1;
      if ((int)uVar1 < 2) {
        bonus_hud_slot_table[iVar2].slide.alt_timer_ptr = (float *)0x0;
      }
      iVar2 = 0;
      ppfVar6 = &bonus_hud_slot_table[0].slide.timer_ptr;
      do {
        if ((char)ppfVar6[-3] != '\0') {
          iVar5 = 0x10;
          puVar3 = &bonus_hud_slot_table_end_ptr;
          do {
            if ((*ppfVar6 == *(float **)(puVar3 + 0xc)) && (iVar2 != iVar5)) {
              *puVar3 = 0;
            }
            puVar3 = puVar3 + -0x20;
            iVar5 = iVar5 + -1;
          } while (0x48f587 < (int)puVar3);
        }
        ppfVar6 = ppfVar6 + 8;
        iVar2 = iVar2 + 1;
      } while ((int)ppfVar6 < 0x48f794);
      return;
    }
    pbVar4 = pbVar4 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)pbVar4 < 0x48f788);
  return;
}



/* bonus_hud_slot_update_and_render @ 0041a8b0 */

/* updates bonus HUD slot animation and renders icon/timers */

void __cdecl bonus_hud_slot_update_and_render(float *xy,int slot)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  IGrim2D_vtbl *pIVar4;
  bonus_hud_slot_t *pbVar5;
  float fVar6;
  bool bVar7;
  float in_stack_0000000c;
  char *text;
  float fStack_18;
  float fStack_14;
  float afStack_10 [4];
  
  if (bonus_hud_slot_table[slot].active != '\0') {
    if ((0.0 < *bonus_hud_slot_table[slot].slide.timer_ptr) ||
       ((pfVar2 = bonus_hud_slot_table[slot].slide.alt_timer_ptr, pfVar2 != (float *)0x0 &&
        (0.0 < *pfVar2)))) {
      fVar6 = frame_dt * 350.0 + bonus_hud_slot_table[slot].slide.slide_x;
    }
    else {
      fVar6 = bonus_hud_slot_table[slot].slide.slide_x - frame_dt * 320.0;
    }
    bonus_hud_slot_table[slot].slide.slide_x = fVar6;
    if (-2.0 < bonus_hud_slot_table[slot].slide.slide_x) {
      bonus_hud_slot_table[slot].slide.slide_x = -2.0;
    }
    if (bonus_hud_slot_table[slot].slide.slide_x < -184.0) {
      iVar3 = 0xf;
      if (slot < 0x10) {
        pbVar5 = bonus_hud_slot_table + 0xf;
        bVar7 = slot == 0xf;
        do {
          if (bVar7) {
            bonus_hud_slot_table[slot].active = '\0';
          }
          else if (pbVar5->active != '\0') break;
          iVar3 = iVar3 + -1;
          pbVar5 = pbVar5 + -1;
          bVar7 = slot == iVar3;
        } while (slot <= iVar3);
      }
      *xy = *xy + 52.0;
      return;
    }
    if (*(float *)((int)cv_uiSmallIndicators + 0xc) == 0.0) {
      (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
      (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
      (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,in_stack_0000000c * 0.7);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      (*grim_interface_ptr->vtable->grim_draw_quad)
                (bonus_hud_slot_table[slot].slide.slide_x,*xy - 11.0,182.0,53.0);
      (*grim_interface_ptr->vtable->grim_end_batch)();
    }
    else {
      (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
      (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
      (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,in_stack_0000000c * 0.7);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      (*grim_interface_ptr->vtable->grim_draw_quad)
                ((bonus_hud_slot_table[slot].slide.slide_x - 100.0) + 4.0,*xy + 5.0,182.0,26.5);
      (*grim_interface_ptr->vtable->grim_end_batch)();
    }
    fVar6 = in_stack_0000000c * 0.7;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,in_stack_0000000c);
    (*grim_interface_ptr->vtable->grim_bind_texture)(bonus_texture,0);
    (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,bonus_hud_slot_table[slot].slide.icon_id);
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (bonus_hud_slot_table[slot].slide.slide_x - 1.0,*xy,32.0,32.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    pfVar2 = bonus_hud_slot_table[slot].slide.alt_timer_ptr;
    afStack_10[3] = fVar6;
    if (*(float *)((int)cv_uiSmallIndicators + 0xc) != 0.0) {
      if (pfVar2 == (float *)0x0) {
        fStack_18 = bonus_hud_slot_table[slot].slide.slide_x;
        fStack_14 = *xy + 21.0;
        fVar1 = *bonus_hud_slot_table[slot].slide.timer_ptr;
      }
      else {
        fStack_18 = bonus_hud_slot_table[slot].slide.slide_x + 36.0;
        afStack_10[0] = 0.1;
        afStack_10[1] = 0.3;
        afStack_10[2] = 0.6;
        fStack_14 = ((*xy + 21.0) - 4.0) - 4.0;
        ui_draw_progress_bar
                  (&fStack_18,32.0,*bonus_hud_slot_table[slot].slide.timer_ptr * 0.05,afStack_10);
        fStack_18 = bonus_hud_slot_table[slot].slide.slide_x;
        fStack_14 = *xy + 23.0;
        fVar1 = *bonus_hud_slot_table[slot].slide.alt_timer_ptr;
      }
      fStack_14 = fStack_14 - 4.0;
      fStack_18 = fStack_18 + 36.0;
      afStack_10[2] = 0.6;
      afStack_10[1] = 0.3;
      afStack_10[0] = 0.1;
      afStack_10[3] = fVar6;
      ui_draw_progress_bar(&fStack_18,32.0,fVar1 * 0.05,afStack_10);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar6);
      *xy = *xy + 52.0;
      return;
    }
    if (pfVar2 == (float *)0x0) {
      fStack_18 = bonus_hud_slot_table[slot].slide.slide_x + 36.0;
      fStack_14 = *xy + 21.0;
      afStack_10[0] = 0.1;
      afStack_10[1] = 0.3;
      afStack_10[2] = 0.6;
      ui_draw_progress_bar
                (&fStack_18,100.0,*bonus_hud_slot_table[slot].slide.timer_ptr * 0.05,afStack_10);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar6);
      text = bonus_hud_slot_table[slot].slide.label;
      pIVar4 = grim_interface_ptr->vtable;
      fVar6 = *xy + 6.0;
    }
    else {
      fStack_18 = bonus_hud_slot_table[slot].slide.slide_x + 36.0;
      afStack_10[0] = 0.1;
      fStack_14 = (*xy + 21.0) - 4.0;
      afStack_10[1] = 0.3;
      afStack_10[2] = 0.6;
      ui_draw_progress_bar
                (&fStack_18,100.0,*bonus_hud_slot_table[slot].slide.timer_ptr * 0.05,afStack_10);
      fStack_18 = bonus_hud_slot_table[slot].slide.slide_x + 36.0;
      fStack_14 = *xy + 23.0;
      afStack_10[0] = 0.1;
      afStack_10[1] = 0.3;
      afStack_10[2] = 0.6;
      afStack_10[3] = fVar6;
      ui_draw_progress_bar
                (&fStack_18,100.0,*bonus_hud_slot_table[slot].slide.alt_timer_ptr * 0.05,afStack_10)
      ;
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar6);
      text = bonus_hud_slot_table[slot].slide.label;
      pIVar4 = grim_interface_ptr->vtable;
      fVar6 = *xy + 2.0;
    }
    (*pIVar4->grim_draw_text_small)(bonus_hud_slot_table[slot].slide.slide_x + 36.0,fVar6,text);
    *xy = *xy + 52.0;
  }
  return;
}



/* bonus_alloc_slot @ 0041f580 */

/* returns a free bonus slot in DAT_00482948 (or DAT_00490630 sentinel) */

bonus_entry_t * bonus_alloc_slot(void)

{
  bonus_entry_t *pbVar1;
  int iVar2;
  
  iVar2 = 0;
  pbVar1 = bonus_pool;
  do {
    if (pbVar1->bonus_id == BONUS_ID_NONE) {
      return bonus_pool + iVar2;
    }
    pbVar1 = pbVar1 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)pbVar1 < 0x482b08);
  return &bonus_pool_sentinel;
}



/* bonus_spawn_at @ 0041f5b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* clamps position, fills bonus entry fields, and spawns pickup effect */

bonus_entry_t * __cdecl bonus_spawn_at(float *pos,bonus_id_t bonus_id,int duration_override)

{
  bonus_entry_t *pbVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if (*pos < 32.0) {
    *pos = 32.0;
  }
  if (pos[1] < 32.0) {
    pos[1] = 32.0;
  }
  if ((float)(terrain_texture_width + -0x20) < *pos) {
    *pos = (float)(terrain_texture_width + -0x20);
  }
  if ((float)(terrain_texture_height + -0x20) < pos[1]) {
    pos[1] = (float)(terrain_texture_height + -0x20);
  }
  if (config_blob.reserved0._24_4_ != 2) {
    pbVar1 = bonus_alloc_slot();
    pbVar1->state = '\0';
    (pbVar1->time).pos_x = *pos;
    (pbVar1->time).pos_y = pos[1];
    (pbVar1->time).time_left = 10.0;
    (pbVar1->time).time_max = 10.0;
    pbVar1->bonus_id = bonus_id;
    (pbVar1->time).amount = duration_override;
    if (duration_override == -1) {
      (pbVar1->time).amount = (&bonus_meta_table)[bonus_id].default_amount;
    }
    effect_template_color_r = 0x3ecccccd;
    effect_template_flags = 0x1d;
    effect_template_color_g = 0x3f000000;
    effect_template_color_b = 0x3f800000;
    effect_template_color_a = 0x3f000000;
    effect_template_lifetime = 0x3f000000;
    effect_template_half_width = 0x42000000;
    effect_template_half_height = 0x42000000;
    iVar4 = 0x10;
    do {
      uVar2 = crt_rand();
      effect_template_rotation = (float)(uVar2 & 0x7f) * 0.049087387;
      uVar2 = crt_rand();
      uVar2 = uVar2 & 0x8000007f;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_x = (float)(int)(uVar2 - 0x40);
      uVar2 = crt_rand();
      uVar2 = uVar2 & 0x8000007f;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_y = (float)(int)(uVar2 - 0x40);
      iVar3 = crt_rand();
      effect_template_scale_step = (float)(iVar3 % 100) * 0.01 + 0.1;
      effect_spawn(0,pos);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    return pbVar1;
  }
  return &bonus_pool_sentinel;
}



/* bonus_spawn_at_pos @ 0041f790 */

/* allocates a bonus slot near pos, enforces spacing/edges, picks bonus type + amount */

bonus_entry_t * __cdecl bonus_spawn_at_pos(float *pos)

{
  float fVar1;
  float fVar2;
  bonus_entry_t *pbVar3;
  bonus_id_t bVar4;
  int iVar5;
  bonus_entry_t *pbVar6;
  
  if ((((*pos < 32.0) || ((float)(terrain_texture_width + -0x20) < *pos)) || (pos[1] < 32.0)) ||
     (((float)(terrain_texture_height + -0x20) < pos[1] || (config_blob.reserved0._24_4_ == 2)))) {
    return &bonus_pool_sentinel;
  }
  pbVar3 = bonus_alloc_slot();
  pbVar6 = bonus_pool;
  while ((pbVar6->bonus_id == BONUS_ID_NONE ||
         (fVar1 = *pos - (pbVar6->time).pos_x, fVar2 = pos[1] - (pbVar6->time).pos_y,
         32.0 <= SQRT(fVar2 * fVar2 + fVar1 * fVar1)))) {
    pbVar6 = pbVar6 + 1;
    if (0x482b07 < (int)pbVar6) {
LAB_0041f853:
      pbVar3->state = '\0';
      (pbVar3->time).pos_x = *pos;
      (pbVar3->time).pos_y = pos[1];
      (pbVar3->time).time_left = 10.0;
      (pbVar3->time).time_max = 10.0;
      bVar4 = bonus_pick_random_type();
      pbVar3->bonus_id = bVar4;
      if (bVar4 == BONUS_ID_WEAPON) {
        iVar5 = weapon_pick_random_available();
        (pbVar3->time).amount = iVar5;
        return pbVar3;
      }
      if (pbVar3->bonus_id == BONUS_ID_POINTS) {
        (pbVar3->time).amount = 500;
        iVar5 = crt_rand();
        if (((byte)iVar5 & 7) < 3) {
          (pbVar3->time).amount = 1000;
          return pbVar3;
        }
      }
      else {
        (pbVar3->time).amount = (&bonus_meta_table)[pbVar3->bonus_id].default_amount;
      }
      return pbVar3;
    }
  }
  pbVar3 = &bonus_pool_sentinel;
  goto LAB_0041f853;
}



/* bonus_try_spawn_on_kill @ 0041f8d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* decides whether to drop a bonus on kill (mode/perk rules) and spawns pickup burst */

void __cdecl bonus_try_spawn_on_kill(float *pos)

{
  int iVar1;
  bonus_entry_t *pbVar2;
  bonus_entry_t *pbVar3;
  uint uVar4;
  int iVar5;
  
  if (config_blob.reserved0._24_4_ == 4) {
    return;
  }
  if (demo_mode_active != '\0') {
    return;
  }
  if (config_blob.reserved0._24_4_ == 2) {
    return;
  }
  if (config_blob.reserved0._24_4_ == 8) {
    return;
  }
  if (((player_state_table.weapon_id == 1) ||
      ((player2_weapon_id == 1 && (config_blob.reserved0._20_4_ == 2)))) &&
     (iVar1 = crt_rand(), ((byte)iVar1 & 3) < 3)) {
    pbVar2 = bonus_spawn_at_pos(pos);
    pbVar2->bonus_id = BONUS_ID_WEAPON;
    iVar1 = weapon_pick_random_available();
    (pbVar2->time).amount = iVar1;
    if (iVar1 == 1) {
      iVar1 = weapon_pick_random_available();
      (pbVar2->time).amount = iVar1;
    }
    iVar1 = 0;
    if (pbVar2->bonus_id != BONUS_ID_POINTS) {
      pbVar3 = bonus_pool;
      do {
        if (pbVar3->bonus_id == pbVar2->bonus_id) {
          iVar1 = iVar1 + 1;
        }
        pbVar3 = pbVar3 + 1;
      } while ((int)pbVar3 < 0x482b08);
      if (1 < iVar1) goto LAB_0041f998;
    }
    if (((pbVar2->time).amount == 1) ||
       (iVar1 = perk_count_get(perk_id_my_favourite_weapon), iVar1 != 0)) {
LAB_0041f998:
      pbVar2->bonus_id = BONUS_ID_NONE;
      return;
    }
  }
  else {
    iVar1 = crt_rand();
    if ((iVar1 % 9 != 1) &&
       ((player_state_table.weapon_id != 1 || (iVar1 = crt_rand(), iVar1 % 5 != 1)))) {
      iVar1 = perk_count_get(perk_id_bonus_magnet);
      if (iVar1 == 0) {
        return;
      }
      iVar1 = crt_rand();
      if (iVar1 % 10 != 2) {
        return;
      }
    }
    pbVar2 = bonus_spawn_at_pos(pos);
    if ((pbVar2->bonus_id == BONUS_ID_WEAPON) &&
       (SQRT((pos[1] - player_state_table.pos_y) * (pos[1] - player_state_table.pos_y) +
             (*pos - player_state_table.pos_x) * (*pos - player_state_table.pos_x)) < 56.0)) {
      pbVar2->bonus_id = BONUS_ID_POINTS;
      (pbVar2->time).amount = 100;
    }
    iVar1 = 0;
    if (pbVar2->bonus_id != BONUS_ID_POINTS) {
      pbVar3 = bonus_pool;
      do {
        if (pbVar3->bonus_id == pbVar2->bonus_id) {
          iVar1 = iVar1 + 1;
        }
        pbVar3 = pbVar3 + 1;
      } while ((int)pbVar3 < 0x482b08);
      if (1 < iVar1) goto LAB_0041fa76;
    }
    if ((pbVar2->time).amount == player_state_table.weapon_id) {
LAB_0041fa76:
      pbVar2->bonus_id = BONUS_ID_NONE;
      return;
    }
  }
  if ((pbVar2 != (bonus_entry_t *)0x0) && (pbVar2 != &bonus_pool_sentinel)) {
    effect_template_color_r = 0x3ecccccd;
    effect_template_flags = 0x1d;
    effect_template_color_g = 0x3f000000;
    effect_template_color_b = 0x3f800000;
    effect_template_color_a = 0x3f000000;
    effect_template_lifetime = 0x3f000000;
    effect_template_half_width = 0x42000000;
    effect_template_half_height = 0x42000000;
    iVar1 = 0x10;
    do {
      uVar4 = crt_rand();
      effect_template_rotation = (float)(uVar4 & 0x7f) * 0.049087387;
      uVar4 = crt_rand();
      uVar4 = uVar4 & 0x8000007f;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_x = (float)(int)(uVar4 - 0x40);
      uVar4 = crt_rand();
      uVar4 = uVar4 & 0x8000007f;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xffffff80) + 1;
      }
      effect_template_vel_y = (float)(int)(uVar4 - 0x40);
      iVar5 = crt_rand();
      effect_template_scale_step = (float)(iVar5 % 100) * 0.01 + 0.1;
      effect_spawn(0,pos);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}



/* bonus_label_for_entry @ 00429580 */

/* returns the label string for a bonus entry (formatting weapon/score cases) */

char * __cdecl bonus_label_for_entry(bonus_entry_t *bonus_entry)

{
  bonus_id_t bVar1;
  char *pcVar2;
  
  bVar1 = bonus_entry->bonus_id;
  if (bVar1 == BONUS_ID_WEAPON) {
    pcVar2 = weapon_table_entry((bonus_entry->time).amount);
    crt_sprintf(&bonus_label_buffer,&s_fmt_percent_s,pcVar2);
    return &bonus_label_buffer;
  }
  if (bVar1 == BONUS_ID_POINTS) {
    crt_sprintf(&bonus_label_buffer,s_fmt_str_number,bonus_points_format_prefix,(bonus_entry->time).amount);
    return &bonus_label_buffer;
  }
  return (&bonus_meta_table)[bVar1].label;
}



/* bonus_render @ 004295f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders bonus icons and labels from the pickup pool */

void bonus_render(void)

{
  int iVar1;
  char *text;
  uint uVar2;
  bonus_entry_t *pbVar3;
  int iVar4;
  float *pfVar5;
  bonus_entry_time_block_t *pbVar6;
  int iVar7;
  int *piVar8;
  secondary_projectile_vel_x_block_t *psVar9;
  uint uVar10;
  bool bVar11;
  float10 extraout_ST0;
  float10 fVar12;
  float10 extraout_ST0_00;
  float10 fVar13;
  int *piStack_8c;
  int iStack_84;
  float fVar14;
  float fVar15;
  float fStack_70;
  float fVar16;
  float fVar17;
  
  if ((((0.0 < ui_transition_alpha) && (game_state_id != 0x14)) && (game_state_id != 0x16)) &&
     ((game_state_prev != 0x14 && (game_state_prev != 0x16)))) {
    bonus_animation_timer = frame_dt * 1.3 + bonus_animation_timer;
    (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
    effect_select_texture(0x10);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    fStack_70 = 6.11523e-39;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    fVar14 = 2.66247e-44;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_bind_texture)((int)bonus_texture,0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    fStack_70 = 1.0;
    fVar16 = 1.0;
    fVar17 = 1.0;
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iStack_84 = 0;
    pbVar6 = &bonus_pool[0].time;
    do {
      if (*(int *)((int)(pbVar6 + -1) + 0xc) != 0) {
        if (pbVar6->time_left < 2.0) {
          fsin((float10)pbVar6->time_left * (float10)18.849556);
        }
        if (0.0 <= fStack_70) {
          if (1.0 < fStack_70) {
            fStack_70 = 1.0;
          }
        }
        else {
          fStack_70 = 0.0;
        }
        if (0.0 <= fVar16) {
          if (1.0 < fVar16) {
            fVar16 = 1.0;
          }
        }
        else {
          fVar16 = 0.0;
        }
        if (0.0 <= fVar17) {
          if (1.0 < fVar17) {
            fVar17 = 1.0;
          }
        }
        else {
          fVar17 = 0.0;
        }
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_70);
        (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
        (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,0);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + pbVar6->pos_x) - 16.0,
                   (camera_offset_y + pbVar6->pos_y) - 16.0,32.0,32.0);
        iVar4 = (&bonus_meta_table)[*(int *)((int)(pbVar6 + -1) + 0xc)].icon_id;
        if (-1 < iVar4) {
          if (0.5 <= pbVar6->time_left) {
            fVar15 = pbVar6->time_max - pbVar6->time_left;
            if (0.5 <= fVar15) {
              fVar15 = 1.0;
            }
            else {
              fVar15 = fVar15 + fVar15;
            }
          }
          else {
            fVar15 = pbVar6->time_left + pbVar6->time_left;
          }
          fVar15 = fVar15 * fVar14;
          if (0.0 <= fStack_70) {
            if (1.0 < fStack_70) {
              fStack_70 = 1.0;
            }
          }
          else {
            fStack_70 = 0.0;
          }
          if (0.0 <= fVar16) {
            if (1.0 < fVar16) {
              fVar16 = 1.0;
            }
          }
          else {
            fVar16 = 0.0;
          }
          if (0.0 <= fVar17) {
            if (1.0 < fVar17) {
              fVar17 = 1.0;
            }
          }
          else {
            fVar17 = 0.0;
          }
          (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_70);
          fsin((float10)iStack_84 + (float10)bonus_animation_timer);
          crt_ci_pow();
          fVar15 = (float)((extraout_ST0 * (float10)0.25 + (float10)0.75) * (float10)fVar15);
          (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_70);
          fVar12 = (float10)fsin((float10)iStack_84 -
                                 (float10)(int)highscore_active_record.survival_elapsed_ms *
                                 (float10)0.003);
          (*grim_interface_ptr->vtable->grim_set_rotation)((float)(fVar12 * (float10)0.2));
          if ((*(int *)((int)(pbVar6 + -1) + 0xc) == 1) && (pbVar6->amount == 1000)) {
            (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,iVar4 + 1);
          }
          else {
            (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,iVar4);
          }
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pbVar6->pos_x) - fVar15 * 16.0,
                     (camera_offset_y + pbVar6->pos_y) - fVar15 * 16.0,fVar15 * 32.0,fVar15 * 32.0)
          ;
        }
      }
      pbVar6 = (bonus_entry_time_block_t *)((int)(pbVar6 + 1) + 8);
      iStack_84 = iStack_84 + 1;
    } while ((int)pbVar6 < 0x482b10);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    iVar4 = 0;
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_weapon_icons_texture,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iStack_84 = 0;
    pbVar6 = &bonus_pool[0].time;
    do {
      if (*(int *)((int)(pbVar6 + -1) + 0xc) == 3) {
        if (0.5 <= pbVar6->time_left) {
          fVar16 = pbVar6->time_max - pbVar6->time_left;
          if (0.5 <= fVar16) {
            fVar16 = 1.0;
          }
          else {
            fVar16 = fVar16 + fVar16;
          }
        }
        else {
          fVar16 = pbVar6->time_left + pbVar6->time_left;
        }
        fVar16 = fVar16 * fVar14;
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_70);
        fsin((float10)bonus_animation_timer);
        crt_ci_pow();
        fVar16 = (float)((extraout_ST0_00 * (float10)0.25 + (float10)0.75) * (float10)fVar16);
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_70);
        fVar12 = (float10)fsin((float10)iStack_84 -
                               (float10)(int)highscore_active_record.survival_elapsed_ms *
                               (float10)0.003);
        (*grim_interface_ptr->vtable->grim_set_rotation)((float)fVar12);
        (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
        (*grim_interface_ptr->vtable->grim_set_sub_rect)
                  (8,2,1,(&weapon_table)[pbVar6->amount].hud_icon_id << 1);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + pbVar6->pos_x) - fVar16 * 30.0,
                   (camera_offset_y + pbVar6->pos_y) - fVar16 * 15.0,fVar16 * 60.0,fVar16 * 30.0);
      }
      pbVar6 = (bonus_entry_time_block_t *)((int)(pbVar6 + 1) + 8);
      iStack_84 = iStack_84 + 1;
    } while ((int)pbVar6 < 0x482b10);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
    if (0 < (int)config_blob.reserved0._20_4_) {
      pfVar5 = &player_state_table.aim_x;
      piStack_8c = &crt_atexit_table;
      do {
        if (0.0 < pfVar5[-0xb]) {
          iVar7 = 0;
          pbVar3 = bonus_pool;
          do {
            if ((pbVar3->bonus_id != BONUS_ID_NONE) &&
               (fVar14 = *pfVar5 - (pbVar3->time).pos_x, fVar16 = pfVar5[1] - (pbVar3->time).pos_y,
               SQRT(fVar14 * fVar14 + fVar16 * fVar16) < 24.0)) {
              if (game_state_id == 9) {
                *piStack_8c = *piStack_8c + frame_dt_ms;
              }
              text = bonus_label_for_entry(bonus_pool + iVar7);
              fVar14 = camera_offset_x + *pfVar5 + 16.0;
              fVar16 = (camera_offset_y + pfVar5[1]) - 7.0;
              iVar1 = (*grim_interface_ptr->vtable->grim_measure_text_width)(text);
              if ((float)config_blob.screen_width < (float)iVar1 + fVar14) {
                fVar14 = (float)config_blob.screen_width - (float)iVar1;
              }
              (*grim_interface_ptr->vtable->grim_draw_text_small)(fVar14,fVar16,text);
              goto LAB_00429df8;
            }
            pbVar3 = pbVar3 + 1;
            iVar7 = iVar7 + 1;
          } while ((int)pbVar3 < 0x482b08);
          *piStack_8c = 0;
LAB_00429df8:
          if (((0x28a < *piStack_8c) && (iVar1 = perk_count_get(perk_id_telekinetic), iVar1 != 0))
             && (bonus_pool[iVar7].state == '\0')) {
            bonus_apply(iVar4,bonus_pool + iVar7);
            bonus_pool[iVar7].state = '\x01';
            bonus_pool[iVar7].time.time_left = 0.5;
            (&crt_atexit_table)[iVar4] = 0;
            break;
          }
        }
        iVar4 = iVar4 + 1;
        pfVar5 = pfVar5 + 0xd8;
        piStack_8c = piStack_8c + 1;
      } while (iVar4 < (int)config_blob.reserved0._20_4_);
    }
    if (config_blob.reserved0[0x10] != '\0') {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
      (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
      effect_select_texture(0xd);
      (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.065);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      uVar10 = 0;
      piVar8 = &particle_pool.style_id;
      do {
        if (((particle_t *)(piVar8 + -0xc))->active != '\0') {
          uVar2 = uVar10 & 0x80000001;
          bVar11 = uVar2 == 0;
          if ((int)uVar2 < 0) {
            bVar11 = (uVar2 - 1 | 0xfffffffe) == 0xffffffff;
          }
          if ((bVar11) && ((char)*piVar8 != '\b')) {
            fVar12 = (float10)fsin(((float10)1.0 - (float10)(float)piVar8[-3]) * (float10)1.5707964)
            ;
            fVar12 = (fVar12 + (float10)0.1) * (float10)55.0 + (float10)4.0;
            if (fVar12 < (float10)16.0) {
              fVar12 = (float10)16.0;
            }
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((float)(((float10)camera_offset_x + (float10)(float)piVar8[-0xb]) - fVar12),
                       (float)(((float10)camera_offset_y + (float10)(float)piVar8[-10]) - fVar12),
                       (float)(fVar12 + fVar12),(float)(fVar12 + fVar12));
          }
        }
        piVar8 = piVar8 + 0xe;
        uVar10 = uVar10 + 1;
      } while ((int)piVar8 < 0x495ae8);
      (*grim_interface_ptr->vtable->grim_end_batch)();
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    }
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
    effect_select_texture(0xc);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    pfVar5 = &particle_pool.spin;
    do {
      if ((((particle_t *)(pfVar5 + -0xb))->active != '\0') && (SUB41(pfVar5[1],0) != '\b')) {
        (*grim_interface_ptr->vtable->grim_set_rotation)(*pfVar5);
        (*grim_interface_ptr->vtable->grim_set_color)(pfVar5[-6],pfVar5[-5],pfVar5[-4],pfVar5[-3]);
        fVar12 = (float10)fsin(((float10)1.0 - (float10)pfVar5[-2]) * (float10)1.5707964);
        fVar12 = fVar12 * (float10)24.0;
        if (SUB41(pfVar5[1],0) == '\x01') {
          fVar12 = fVar12 * (float10)0.8;
        }
        if (fVar12 < (float10)2.0) {
          fVar12 = (float10)2.0;
        }
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)(((float10)camera_offset_x + (float10)pfVar5[-10]) - fVar12),
                   (float)(((float10)camera_offset_y + (float10)pfVar5[-9]) - fVar12),
                   (float)(fVar12 + fVar12),(float)(fVar12 + fVar12));
      }
      pfVar5 = pfVar5 + 0xe;
    } while ((int)pfVar5 < 0x495ae4);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    effect_select_texture(2);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    piVar8 = &particle_pool.style_id;
    do {
      if ((((particle_t *)(piVar8 + -0xc))->active != '\0') && ((char)*piVar8 == '\b')) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)piVar8[-4]);
        fVar12 = (float10)fsin((float10)(float)piVar8[-1]);
        fVar13 = (fVar12 * (float10)3.0 + (float10)15.0) * (float10)(float)piVar8[-7] * (float10)7.0
        ;
        fVar14 = (float)((float10)15.0 - fVar12 * (float10)3.0) * (float)piVar8[-7] * 7.0;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + (float)piVar8[-0xb]) - fVar14,
                   (float)(((float10)camera_offset_y + (float10)(float)piVar8[-10]) - fVar13),
                   fVar14 + fVar14,(float)(fVar13 + fVar13));
      }
      piVar8 = piVar8 + 0xe;
    } while ((int)piVar8 < 0x495ae8);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    psVar9 = &secondary_projectile_pool[0].pos.vx;
    do {
      if ((*(char *)((int)(psVar9 + -1) + 4) != '\0') &&
         ((psVar9->vy).type_id == SECONDARY_PROJECTILE_TYPE_EXPLODING)) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.6,0.1,1.0 - psVar9->vel_x);
        fVar14 = (psVar9->vy).vel_y * psVar9->vel_x * 64.0;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x10)) - fVar14 * 0.5,
                   (camera_offset_y + *(float *)((int)(psVar9 + -1) + 0x14)) - fVar14 * 0.5,fVar14,
                   fVar14);
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.6,0.1,(1.0 - psVar9->vel_x) * 0.3);
        fVar14 = (psVar9->vy).vel_y * psVar9->vel_x * 200.0;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x10)) - fVar14 * 0.5,
                   (camera_offset_y + *(float *)((int)(psVar9 + -1) + 0x14)) - fVar14 * 0.5,fVar14,
                   fVar14);
      }
      psVar9 = (secondary_projectile_vel_x_block_t *)((int)(psVar9 + 1) + 0x14);
    } while ((int)psVar9 < 0x4965ec);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    if (config_blob.reserved0[0x11] != '\0') {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
      (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
      (*grim_interface_ptr->vtable->grim_set_uv)
                (sprite_effect_uv_u,sprite_effect_uv_v,sprite_effect_uv_u + 0.25,sprite_effect_uv_v + 0.25);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      pfVar5 = &sprite_effect_pool.scale;
      do {
        if ((char)((sprite_effect_t *)(pfVar5 + -10))->active != '\0') {
          fVar14 = *pfVar5;
          (*grim_interface_ptr->vtable->grim_set_rotation)(pfVar5[-5]);
          (*grim_interface_ptr->vtable->grim_set_color)(pfVar5[-9],pfVar5[-8],pfVar5[-7],pfVar5[-6])
          ;
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pfVar5[-4]) - fVar14 * 0.5,
                     (camera_offset_y + pfVar5[-3]) - fVar14 * 0.5,fVar14,fVar14);
        }
        pfVar5 = pfVar5 + 0xb;
      } while ((int)pfVar5 < 0x49aa48);
      (*grim_interface_ptr->vtable->grim_end_batch)();
    }
    effects_render();
  }
  return;
}


