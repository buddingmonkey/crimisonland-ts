/* projectile_meta_table_atexit_register @ 004121f0 */

/* [binja] int32_t sub_4121f0() */

int projectile_meta_table_atexit_register(void)

{
  int iVar1;
  
  iVar1 = crt_atexit(&LAB_00412200);
  return iVar1;
}



/* projectile_spawn @ 00420440 */

/* allocates a projectile slot, initializes fields, and returns the index (overrides to type 0x2d
   when Fire Bullets is active) */

int __cdecl projectile_spawn(float *pos,float angle,projectile_type_id_t type_id,int owner_id)

{
  projectile_t *ppVar1;
  int iVar2;
  float10 fVar3;
  
  if (bonus_spawn_guard == '\0') {
    while (((((owner_id == -100 || (owner_id == -1)) || (owner_id == -2)) || (owner_id == -3)) &&
           ((highscore_active_record.shots_fired = highscore_active_record.shots_fired + 1,
            type_id != PROJECTILE_TYPE_FIRE_BULLETS &&
            ((0.0 < player_state_table.fire_bullets_timer || (0.0 < player2_fire_bullets_timer))))))
          ) {
      type_id = PROJECTILE_TYPE_FIRE_BULLETS;
    }
  }
  iVar2 = 0;
  ppVar1 = projectile_pool;
  do {
    if (ppVar1->active == '\0') goto LAB_004204d7;
    ppVar1 = ppVar1 + 1;
    iVar2 = iVar2 + 1;
  } while ((int)ppVar1 < 0x493eb8);
  iVar2 = 0x5f;
LAB_004204d7:
  fVar3 = (float10)fcos((float10)angle);
  projectile_pool[iVar2].pos.tail.vy.owner_id = owner_id;
  projectile_pool[iVar2].active = '\x01';
  projectile_pool[iVar2].pos.tail.vy.base_damage = (&weapon_table)[type_id].projectile_meta;
  projectile_pool[iVar2].pos_x = *pos;
  projectile_pool[iVar2].pos.pos_y = pos[1];
  projectile_pool[iVar2].pos.origin_x = *pos;
  projectile_pool[iVar2].pos.tail.origin_y = pos[1];
  projectile_pool[iVar2].angle = angle;
  projectile_pool[iVar2].pos.tail.vy.type_id = type_id;
  projectile_pool[iVar2].pos.tail.vy.life_timer = 0.4;
  projectile_pool[iVar2].pos.tail.vy.reserved = 0.0;
  projectile_pool[iVar2].pos.tail.vy.speed_scale = 1.0;
  projectile_pool[iVar2].pos.tail.vel_x = (float)(fVar3 * (float10)1.5);
  fVar3 = (float10)fsin((float10)angle);
  projectile_pool[iVar2].pos.tail.vy.vel_y = (float)(fVar3 * (float10)1.5);
  if (type_id == PROJECTILE_TYPE_ION_MINIGUN) {
    projectile_pool[iVar2].pos.tail.vy.hit_radius = 3.0;
    projectile_pool[iVar2].pos.tail.vy.damage_pool = 1.0;
    return iVar2;
  }
  if (type_id == PROJECTILE_TYPE_ION_RIFLE) {
    projectile_pool[iVar2].pos.tail.vy.hit_radius = 5.0;
    projectile_pool[iVar2].pos.tail.vy.damage_pool = 1.0;
    return iVar2;
  }
  if ((type_id == PROJECTILE_TYPE_ION_CANNON) || (type_id == PROJECTILE_TYPE_PLASMA_CANNON)) {
    projectile_pool[iVar2].pos.tail.vy.hit_radius = 10.0;
  }
  else {
    projectile_pool[iVar2].pos.tail.vy.hit_radius = 1.0;
    if (type_id == PROJECTILE_TYPE_GAUSS_GUN) {
      projectile_pool[iVar2].pos.tail.vy.damage_pool = 300.0;
      return iVar2;
    }
    if (type_id == PROJECTILE_TYPE_FIRE_BULLETS) {
      projectile_pool[iVar2].pos.tail.vy.damage_pool = 240.0;
      return iVar2;
    }
    if (type_id == PROJECTILE_TYPE_BLADE_GUN) {
      projectile_pool[iVar2].pos.tail.vy.damage_pool = 50.0;
      return iVar2;
    }
  }
  projectile_pool[iVar2].pos.tail.vy.damage_pool = 1.0;
  return iVar2;
}



/* projectile_reset_pools @ 004205d0 */

/* clears projectile and effect pools (DAT_004926b8, crt_ctype_table_base) */

void projectile_reset_pools(void)

{
  projectile_t *ppVar1;
  particle_t *ppVar2;
  
  ppVar1 = projectile_pool;
  do {
    ppVar1->active = '\0';
    ppVar1 = ppVar1 + 1;
  } while ((int)ppVar1 < 0x493eb8);
  ppVar2 = &particle_pool;
  do {
    ppVar2->active = '\0';
    ppVar2 = ppVar2 + 1;
  } while ((int)ppVar2 < 0x495ab8);
  return;
}



/* projectile_update @ 00420b90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates projectile movement, collisions, and hit effects */

void projectile_update(void)

{
  float *pfVar1;
  float fVar2;
  char cVar3;
  projectile_type_id_t pVar4;
  secondary_projectile_type_id_t sVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  float fVar11;
  int iVar12;
  float *pfVar13;
  secondary_projectile_vel_y_block_t *psVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 fVar18;
  float10 fVar19;
  float10 fVar20;
  float10 fVar21;
  longlong lVar22;
  float fVar23;
  int local_ec;
  int local_e8;
  int local_e4;
  float local_dc;
  int local_d8;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  float fStack_50;
  float local_4c;
  float local_48;
  float local_44;
  float fStack_40;
  float local_3c;
  float fStack_38;
  float local_34;
  float fStack_30;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  float fStack_18;
  float local_14;
  float local_10 [4];
  
  crt_atexit_count = crt_atexit_count + 1;
  local_c0 = 1.0;
  iVar7 = perk_count_get(perk_id_ion_gun_master);
  if (iVar7 != 0) {
    local_c0 = 1.2;
  }
  local_e8 = 0;
  do {
    if (projectile_pool[local_e8].active != '\0') {
      if (projectile_pool[local_e8].pos.tail.vy.life_timer <= 0.0) {
        projectile_pool[local_e8].active = '\0';
      }
      if (0.4 <= projectile_pool[local_e8].pos.tail.vy.life_timer) {
        pfVar13 = &projectile_pool[local_e8].pos_x;
        if ((((projectile_pool[local_e8].pos_x < -64.0) ||
             (projectile_pool[local_e8].pos.pos_y < -64.0)) ||
            ((float)(terrain_texture_width + 0x40) < *pfVar13)) ||
           ((float)(terrain_texture_height + 0x40) < projectile_pool[local_e8].pos.pos_y)) {
LAB_004219ef:
          fVar11 = projectile_pool[local_e8].pos.tail.vy.life_timer - frame_dt;
LAB_004219f8:
          projectile_pool[local_e8].pos.tail.vy.life_timer = fVar11;
        }
        else {
          lVar22 = __ftol();
          local_dc = (float)lVar22;
          fVar20 = (float10)projectile_pool[local_e8].angle - (float10)1.5707964;
          fVar15 = (float10)fcos(fVar20);
          fVar21 = (float10)frame_dt;
          fVar16 = (float10)fsin(fVar20);
          fVar20 = (float10)frame_dt;
          iVar7 = perk_count_get(perk_id_barrel_greaser);
          if ((iVar7 != 0) && (projectile_pool[local_e8].pos.tail.vy.owner_id < 0)) {
            lVar22 = __ftol();
            local_dc = (float)lVar22;
          }
          local_c8 = 0.0;
          local_cc = 0.0;
          local_c4 = 0.0;
          if (0 < (int)local_dc) {
            do {
              fVar11 = local_c4;
              local_cc = (float)(fVar15 * fVar21 * (float10)20.0) *
                         projectile_pool[local_e8].pos.tail.vy.speed_scale * 3.0 + local_cc;
              local_c8 = (float)(fVar16 * fVar20 * (float10)20.0) *
                         projectile_pool[local_e8].pos.tail.vy.speed_scale * 3.0 + local_c8;
              if ((4.0 <= SQRT(local_c8 * local_c8 + local_cc * local_cc)) ||
                 ((int)local_dc <= (int)local_c4 + 3)) {
                vec2_add(pfVar13,&local_cc);
                iVar7 = creature_find_in_radius
                                  (pfVar13,projectile_pool[local_e8].pos.tail.vy.hit_radius,0);
                if ((iVar7 == -1) || (iVar7 == projectile_pool[local_e8].pos.tail.vy.owner_id)) {
                  if (local_e8 != shock_chain_projectile_id) {
                    iVar12 = projectile_pool[local_e8].pos.tail.vy.owner_id;
                    if (iVar12 != -100) {
                      iVar7 = player_find_in_radius
                                        (iVar12,pfVar13,
                                         projectile_pool[local_e8].pos.tail.vy.hit_radius);
                    }
                    if (iVar7 != -1) {
                      projectile_pool[local_e8].pos.tail.vy.life_timer = 0.25;
                      if ((&player_state_table)[iVar7].shield_timer <= 0.0) {
                        (&player_state_table)[iVar7].health =
                             (&player_state_table)[iVar7].health - 10.0;
                      }
                    }
                  }
                }
                else {
                  iVar12 = perk_count_get(perk_id_poison_bullets);
                  if ((iVar12 != 0) && (iVar12 = crt_rand(), ((byte)iVar12 & 7) == 1)) {
                    (&creature_pool)[iVar7].flags = (&creature_pool)[iVar7].flags | 1;
                  }
                  pVar4 = projectile_pool[local_e8].pos.tail.vy.type_id;
                  if (pVar4 == PROJECTILE_TYPE_BLADE_GUN) {
                    iVar12 = 8;
                    do {
                      fVar11 = 0.0;
                      uVar10 = crt_rand();
                      effect_spawn_blood_splatter
                                (pfVar13,(float)(uVar10 & 0xff) * 0.024543693,fVar11);
                      iVar12 = iVar12 + -1;
                    } while (iVar12 != 0);
                  }
                  else if (pVar4 == PROJECTILE_TYPE_SPLITTER_GUN) {
                    fx_spawn_fire_particles(pfVar13,26.0,3);
                    projectile_spawn(pfVar13,projectile_pool[local_e8].angle - 1.0471976,
                                     PROJECTILE_TYPE_SPLITTER_GUN,iVar7);
                    projectile_spawn(pfVar13,projectile_pool[local_e8].angle + 1.0471976,
                                     PROJECTILE_TYPE_SPLITTER_GUN,iVar7);
                  }
                  local_64 = 0x3f800000;
                  local_68 = 1.0;
                  effect_template_color_g = 0x3f800000;
                  local_60 = 0x3f800000;
                  local_5c = 0x3f800000;
                  effect_template_color_r = 0x3f800000;
                  effect_template_flags = 0x59;
                  effect_template_color_b = 0x3f800000;
                  effect_template_color_a = 0x3f800000;
                  effect_template_lifetime = 0x3eb33333;
                  effect_template_age = 0;
                  effect_template_half_width = 0x40800000;
                  effect_template_half_height = 0x40800000;
                  if (config_blob.fx_toggle == '\0') {
                    iVar12 = perk_count_get(perk_id_bloody_mess_quick_learner);
                    if (iVar12 == 0) {
                      if (bonus_freeze_timer <= 0.0) {
                        iVar12 = 2;
                        do {
                          effect_spawn_blood_splatter
                                    (pfVar13,projectile_pool[local_e8].angle - 1.5707964,0.0);
                          iVar9 = crt_rand();
                          if (((byte)iVar9 & 7) == 2) {
                            effect_spawn_blood_splatter
                                      (pfVar13,(projectile_pool[local_e8].angle - 1.5707964) +
                                               3.1415927,0.0);
                          }
                          iVar12 = iVar12 + -1;
                        } while (iVar12 != 0);
                      }
                    }
                    else {
                      iVar12 = 8;
                      do {
                        fVar11 = 0.0;
                        uVar10 = crt_rand();
                        effect_spawn_blood_splatter
                                  (pfVar13,(projectile_pool[local_e8].angle - 1.5707964) +
                                           (float)(int)((uVar10 & 0x1f) - 0x10) * 0.0625,fVar11);
                        iVar12 = iVar12 + -1;
                      } while (iVar12 != 0);
                      effect_spawn_blood_splatter
                                (pfVar13,(projectile_pool[local_e8].angle - 1.5707964) + 3.1415927,
                                 0.0);
                    }
                  }
                  if ((&creature_pool)[iVar7].hitbox_size == 16.0) {
                    highscore_active_record.shots_hit = highscore_active_record.shots_hit + 1;
                  }
                  iVar12 = perk_count_get(perk_id_bloody_mess_quick_learner);
                  if (iVar12 != 0) {
                    local_d8 = 0x1e;
                    iVar12 = -0x1e;
                    do {
                      iVar9 = local_d8 - iVar12;
                      iVar8 = crt_rand();
                      local_58 = (float)(iVar8 % iVar9 + iVar12);
                      iVar8 = crt_rand();
                      local_20 = local_58 + (&creature_pool)[iVar7].pos_x;
                      local_1c = (float)(iVar8 % iVar9 + iVar12) + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_20);
                      iVar8 = crt_rand();
                      local_28 = (float)(iVar8 % iVar9 + iVar12);
                      iVar8 = crt_rand();
                      local_48 = local_28 + (&creature_pool)[iVar7].pos_x;
                      local_44 = (float)(iVar8 % iVar9 + iVar12) + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_48);
                      iVar12 = iVar12 + -10;
                      local_d8 = local_d8 + 10;
                    } while (-0x3c < iVar12);
                  }
                  pVar4 = projectile_pool[local_e8].pos.tail.vy.type_id;
                  if (((pVar4 != PROJECTILE_TYPE_FIRE_BULLETS) &&
                      (pVar4 != PROJECTILE_TYPE_GAUSS_GUN)) && (pVar4 != PROJECTILE_TYPE_BLADE_GUN))
                  {
                    projectile_pool[local_e8].pos.tail.vy.life_timer = 0.25;
                    uVar10 = crt_rand();
                    fVar17 = (float10)projectile_pool[local_e8].angle - (float10)1.5707964;
                    fVar18 = (float10)fcos(fVar17);
                    *pfVar13 = (float)(fVar18 * (float10)(uVar10 & 3) + (float10)*pfVar13);
                    fVar17 = (float10)fsin(fVar17);
                    projectile_pool[local_e8].pos.pos_y =
                         (float)(fVar17 * (float10)(uVar10 & 3) +
                                (float10)projectile_pool[local_e8].pos.pos_y);
                  }
                  fVar11 = projectile_pool[local_e8].pos.origin_x - *pfVar13;
                  fVar23 = projectile_pool[local_e8].pos.tail.origin_y -
                           projectile_pool[local_e8].pos.pos_y;
                  fVar11 = SQRT(fVar11 * fVar11 + fVar23 * fVar23);
                  if (fVar11 < 50.0) {
                    fVar11 = 50.0;
                  }
                  pVar4 = projectile_pool[local_e8].pos.tail.vy.type_id;
                  fVar23 = (&weapon_table)[pVar4].damage_scale;
                  if (pVar4 == PROJECTILE_TYPE_ION_MINIGUN) {
                    fx_spawn_electric_arc(pfVar13,1.5,0.1);
                    fx_spawn_shockwave((int)pfVar13,0.8);
                  }
                  else if (pVar4 == PROJECTILE_TYPE_ION_RIFLE) {
                    if ((0 < shock_chain_links_left) && (local_e8 == shock_chain_projectile_id)) {
                      shock_chain_links_left = shock_chain_links_left + -1;
                      iVar12 = creature_find_nearest(pfVar13,iVar7,100.0);
                      bonus_spawn_guard = 1;
                      fVar17 = (float10)fpatan((float10)(&creature_pool)[iVar12].pos_y -
                                               (float10)(&creature_pool)[iVar7].pos_y,
                                               (float10)(&creature_pool)[iVar12].pos_x -
                                               (float10)(&creature_pool)[iVar7].pos_x);
                      shock_chain_projectile_id =
                           projectile_spawn(pfVar13,(float)((fVar17 - (float10)1.5707964) -
                                                           (float10)3.1415927),
                                            PROJECTILE_TYPE_ION_RIFLE,iVar7);
                      bonus_spawn_guard = 0;
                    }
                    fx_spawn_electric_arc(pfVar13,1.2,0.4);
                    fx_spawn_shockwave((int)pfVar13,1.2);
                  }
                  else if (pVar4 == PROJECTILE_TYPE_ION_CANNON) {
                    fx_spawn_electric_arc(pfVar13,1.0,1.0);
                    fx_spawn_shockwave((int)pfVar13,2.2);
                    sfx_play_panned(sfx_shockwave);
                  }
                  else if (pVar4 == PROJECTILE_TYPE_PLASMA_CANNON) {
                    bonus_spawn_guard = 1;
                    local_e4 = 0;
                    fVar6 = (&creature_pool)[iVar7].size * 0.5 + 1.0;
                    do {
                      fVar2 = (float)((float10)local_e4 * (float10)0.5235988);
                      fVar17 = (float10)fcos((float10)local_e4 * (float10)0.5235988);
                      fVar18 = (float10)fsin((float10)fVar2);
                      local_34 = (float)(fVar18 * (float10)fVar6);
                      local_88 = (float)(fVar17 * (float10)fVar6 + (float10)*pfVar13);
                      local_84 = local_34 + projectile_pool[local_e8].pos.pos_y;
                      projectile_spawn(&local_88,fVar2,PROJECTILE_TYPE_PLASMA_RIFLE,-100);
                      local_e4 = local_e4 + 1;
                    } while (local_e4 < 0xc);
                    bonus_spawn_guard = 0;
                    sfx_play_panned(sfx_explosion_medium);
                    sfx_play_panned(sfx_shockwave);
                    fx_spawn_plasma_explosion(pfVar13,1.5,0x3f800000);
                    fx_spawn_plasma_explosion(pfVar13,1.0,0x3f800000);
                  }
                  else if (pVar4 == PROJECTILE_TYPE_SHRINKIFIER) {
                    effect_spawn_shrink_fx(pfVar13);
                    fVar6 = (&creature_pool)[iVar7].size * 0.65;
                    projectile_pool[local_e8].pos.tail.vy.life_timer = 0.25;
                    (&creature_pool)[iVar7].size = fVar6;
                    if (fVar6 < 16.0) {
                      creature_handle_death(iVar7,true);
                    }
                  }
                  else if (pVar4 == PROJECTILE_TYPE_PULSE_GUN) {
                    local_14 = local_c8 * 3.0;
                    (&creature_pool)[iVar7].pos_x = local_cc * 3.0 + (&creature_pool)[iVar7].pos_x;
                    (&creature_pool)[iVar7].pos_y = local_14 + (&creature_pool)[iVar7].pos_y;
                  }
                  else if (pVar4 == PROJECTILE_TYPE_PLAGUE_SPREADER) {
                    (&creature_pool)[iVar7].collision_flag = '\x01';
                  }
                  fVar11 = ((100.0 / fVar11) * fVar23 * 30.0 + 10.0) * 0.95;
                  if ((0.0 < fVar11) && (0.0 < (&creature_pool)[iVar7].health)) {
                    fVar23 = projectile_pool[local_e8].pos.tail.vy.damage_pool - 1.0;
                    projectile_pool[local_e8].pos.tail.vy.damage_pool = fVar23;
                    fVar17 = (float10)fcos((float10)projectile_pool[local_e8].angle -
                                           (float10)1.5707964);
                    fVar18 = fVar17 * (float10)projectile_pool[local_e8].pos.tail.vy.speed_scale;
                    if (fVar23 <= 0.0) {
                      local_98 = (float)fVar18;
                      local_94 = (float)(fVar17 * (float10)projectile_pool[local_e8].pos.tail.vy.
                                                           speed_scale);
                      creature_apply_damage(iVar7,fVar11,1,&local_98);
                      if (projectile_pool[local_e8].pos.tail.vy.life_timer != 0.25) {
                        projectile_pool[local_e8].pos.tail.vy.life_timer = 0.25;
                      }
                    }
                    else {
                      local_78 = (float)fVar18;
                      local_74 = (float)(fVar17 * (float10)projectile_pool[local_e8].pos.tail.vy.
                                                           speed_scale);
                      creature_apply_damage(iVar7,fVar23,1,&local_78);
                      projectile_pool[local_e8].pos.tail.vy.damage_pool =
                           projectile_pool[local_e8].pos.tail.vy.damage_pool -
                           (&creature_pool)[iVar7].health;
                    }
                  }
                  if ((projectile_pool[local_e8].pos.tail.vy.damage_pool == 1.0) &&
                     (fVar11 = projectile_pool[local_e8].pos.tail.vy.life_timer,
                     projectile_pool[local_e8].pos.tail.vy.damage_pool = 0.0, fVar11 != 0.25)) {
                    projectile_pool[local_e8].pos.tail.vy.life_timer = 0.25;
                  }
                  (&creature_pool)[iVar7].state_flag = '\x01';
                  crt_rand();
                  pVar4 = projectile_pool[local_e8].pos.tail.vy.type_id;
                  if ((pVar4 == PROJECTILE_TYPE_GAUSS_GUN) ||
                     (pVar4 == PROJECTILE_TYPE_FIRE_BULLETS)) {
                    perk_count_get(perk_id_bloody_mess_quick_learner);
                    local_ec = 6;
                    do {
                      iVar12 = crt_rand();
                      fVar17 = (float10)(iVar12 % 100) * (float10)0.1;
                      if ((float10)4.0 < fVar17) {
                        iVar12 = crt_rand();
                        fVar17 = (float10)(iVar12 % 0x5a + 10) * (float10)0.1;
                      }
                      if ((float10)7.0 < fVar17) {
                        iVar12 = crt_rand();
                        fVar17 = (float10)(iVar12 % 0x50 + 0x14) * (float10)0.1;
                      }
                      fVar18 = (float10)projectile_pool[local_e8].angle - (float10)1.5707964;
                      fVar19 = (float10)fcos(fVar18);
                      local_a8 = 0.0;
                      local_a4 = 0.0;
                      fVar11 = (float)(fVar19 * fVar17 * (float10)20.0);
                      fVar18 = (float10)fsin(fVar18);
                      fVar23 = (float)(fVar18 * fVar17 * (float10)20.0);
                      local_b0 = fVar11 + (&creature_pool)[iVar7].pos_x;
                      local_ac = fVar23 + (&creature_pool)[iVar7].pos_y;
                      vec2_add_inplace(iVar7,&local_b0,&local_a8);
                      crt_rand();
                      if (0.0 < bonus_freeze_timer) {
                        local_a0 = fVar11 + *pfVar13;
                        local_9c = fVar23 + projectile_pool[local_e8].pos.pos_y;
                        iVar12 = crt_rand();
                        effect_spawn_freeze_shard
                                  (&local_a0,
                                   (projectile_pool[local_e8].angle - 1.5707964) +
                                   (float)(iVar12 % 100) * 0.01);
                      }
                      local_b8 = fVar11 + (&creature_pool)[iVar7].pos_x;
                      local_b4 = fVar23 + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_b8);
                      local_ec = local_ec + -1;
                    } while (local_ec != 0);
                  }
                  else if (bonus_freeze_timer <= 0.0) {
                    pfVar1 = &(&creature_pool)[iVar7].pos_x;
                    iVar12 = 3;
                    do {
                      iVar9 = crt_rand();
                      fVar18 = ((float10)projectile_pool[local_e8].angle - (float10)1.5707964) +
                               (float10)(iVar9 % 0x14 + -10) * (float10)0.1;
                      fVar17 = (float10)fcos(fVar18);
                      fVar11 = (float)(fVar17 * (float10)20.0);
                      fVar17 = (float10)fsin(fVar18);
                      fVar23 = (float)(fVar17 * (float10)20.0);
                      fx_queue_add_random(pfVar1);
                      local_4c = fVar23 * 1.5;
                      local_70 = fVar11 * 1.5 + *pfVar1;
                      local_6c = local_4c + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_70);
                      local_3c = fVar23 + fVar23;
                      local_80 = fVar11 + fVar11 + *pfVar1;
                      local_7c = local_3c + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_80);
                      local_2c = fVar23 * 2.5;
                      local_90 = fVar11 * 2.5 + *pfVar1;
                      local_8c = local_2c + (&creature_pool)[iVar7].pos_y;
                      fx_queue_add_random(&local_90);
                      iVar12 = iVar12 + -1;
                    } while (iVar12 != 0);
                  }
                  else {
                    iVar7 = crt_rand();
                    effect_spawn_freeze_shard
                              (pfVar13,(projectile_pool[local_e8].angle - 1.5707964) +
                                       (float)(iVar7 % 100) * 0.01);
                  }
                  if (((demo_mode_active == '\0') && (music_muted_flag == '\0')) &&
                     (config_blob.reserved0._24_4_ != 2)) {
                    sfx_play_exclusive(music_track_extra_0);
                  }
                  else {
                    fVar11 = sfx_shock_hit_01;
                    if ((&weapon_ammo_class)[projectile_pool[local_e8].pos.tail.vy.type_id * 0x1f]
                        != 4) {
                      iVar7 = crt_rand();
                      fVar11 = (float)(iVar7 % 6 + sfx_bullet_hit_01);
                    }
                    sfx_play_panned(fVar11);
                  }
                  fVar11 = local_c4;
                  if (projectile_pool[local_e8].pos.tail.vy.damage_pool <= 0.0) break;
                }
                local_c8 = 0.0;
                local_cc = 0.0;
              }
              local_c4 = (float)((int)fVar11 + 3);
            } while ((int)local_c4 < (int)local_dc);
          }
        }
      }
      else {
        pVar4 = projectile_pool[local_e8].pos.tail.vy.type_id;
        if ((pVar4 == PROJECTILE_TYPE_ION_RIFLE) || (pVar4 == PROJECTILE_TYPE_ION_MINIGUN)) {
          if (local_e8 == shock_chain_projectile_id) {
            shock_chain_projectile_id = -1;
            shock_chain_links_left = 0;
          }
          projectile_pool[local_e8].pos.tail.vy.life_timer =
               projectile_pool[local_e8].pos.tail.vy.life_timer - frame_dt;
          if (pVar4 == PROJECTILE_TYPE_ION_RIFLE) {
            fVar23 = frame_dt * 100.0;
            fVar11 = local_c0 * 88.0;
          }
          else {
            fVar23 = frame_dt * 40.0;
            fVar11 = local_c0 * 60.0;
          }
        }
        else {
          if (pVar4 != PROJECTILE_TYPE_ION_CANNON) {
            if (pVar4 != PROJECTILE_TYPE_GAUSS_GUN) goto LAB_004219ef;
            fVar11 = projectile_pool[local_e8].pos.tail.vy.life_timer - frame_dt * 0.1;
            goto LAB_004219f8;
          }
          projectile_pool[local_e8].pos.tail.vy.life_timer =
               projectile_pool[local_e8].pos.tail.vy.life_timer - frame_dt * 0.7;
          fVar23 = frame_dt * 300.0;
          fVar11 = local_c0 * 128.0;
        }
        creatures_apply_radius_damage(&projectile_pool[local_e8].pos_x,fVar11,fVar23,7);
      }
    }
    local_e8 = local_e8 + 1;
  } while (local_e8 < 0x60);
  psVar14 = &secondary_projectile_pool[0].pos.vx.vy;
  do {
    if (*(char *)((int)(psVar14 + -2) + 0x10) != '\0') {
      if (psVar14->type_id == SECONDARY_PROJECTILE_TYPE_EXPLODING) {
        camera_shake_pulses = 4;
        fVar11 = frame_dt * 3.0 + *(float *)((int)(psVar14 + -1) + 0x10);
        *(float *)((int)(psVar14 + -1) + 0x10) = fVar11;
        if (1.0 < fVar11) {
          fVar11 = psVar14->vel_y * 256.0;
          local_10[0] = 0.0;
          local_10[1] = 0.0;
          local_10[2] = 0.0;
          local_10[3] = 0.25;
          fx_queue_add(0x10,(float *)((int)(psVar14 + -1) + 8),fVar11,fVar11,0.0,local_10);
          *(undefined1 *)((int)(psVar14 + -2) + 0x10) = 0;
        }
        fVar11 = psVar14->vel_y;
        fVar23 = *(float *)((int)(psVar14 + -1) + 0x10);
        iVar7 = 0;
        pfVar13 = &creature_pool.pos_y;
        do {
          if ((((creature_t *)(pfVar13 + -6))->active != '\0') && (0.0 < pfVar13[3])) {
            fVar6 = pfVar13[-1] - *(float *)((int)(psVar14 + -1) + 8);
            fVar2 = *pfVar13 - *(float *)((int)(psVar14 + -1) + 0xc);
            if (SQRT(fVar6 * fVar6 + fVar2 * fVar2) < fVar11 * fVar23 * 80.0) {
              local_c0 = fVar6;
              local_bc = fVar2;
              player_aim_update_thunk();
              local_c0 = local_c8 * 0.1;
              local_bc = local_c4 * 0.1;
              creature_apply_damage(iVar7,frame_dt * psVar14->vel_y * 700.0,3,&local_c0);
              if (pfVar13[3] <= 0.0) {
                fx_queue_add_random(pfVar13 + -1);
                fx_queue_add_random(pfVar13 + -1);
                creature_handle_death(iVar7,true);
              }
            }
          }
          pfVar13 = pfVar13 + 0x26;
          iVar7 = iVar7 + 1;
        } while ((int)pfVar13 < 0x4aa350);
      }
      else {
        local_a0 = frame_dt * *(float *)((int)(psVar14 + -1) + 0x10);
        pfVar13 = (float *)((int)(psVar14 + -1) + 8);
        local_9c = frame_dt * psVar14->vel_y;
        vec2_add(pfVar13,&local_a0);
        sVar5 = psVar14->type_id;
        if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET) {
          if (SQRT(*(float *)((int)(psVar14 + -1) + 0x10) * *(float *)((int)(psVar14 + -1) + 0x10) +
                   psVar14->vel_y * psVar14->vel_y) < 500.0) {
            fVar11 = 3.0;
LAB_00421c48:
            fVar11 = frame_dt * fVar11 + 1.0;
            *(float *)((int)(psVar14 + -1) + 0x10) = fVar11 * *(float *)((int)(psVar14 + -1) + 0x10)
            ;
            psVar14->vel_y = fVar11 * psVar14->vel_y;
          }
LAB_00421c5a:
          fVar11 = *(float *)((int)(psVar14 + -1) + 4) - frame_dt;
LAB_00421d65:
          *(float *)((int)(psVar14 + -1) + 4) = fVar11;
        }
        else {
          if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN) {
            if (SQRT(*(float *)((int)(psVar14 + -1) + 0x10) * *(float *)((int)(psVar14 + -1) + 0x10)
                     + psVar14->vel_y * psVar14->vel_y) < 600.0) {
              fVar11 = 4.0;
              goto LAB_00421c48;
            }
            goto LAB_00421c5a;
          }
          if (sVar5 == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
            if ((&creature_pool)[psVar14->target_id].active == '\0') {
              iVar7 = creature_find_nearest(pfVar13,-1,0.0);
              psVar14->target_id = iVar7;
            }
            fVar21 = (float10)fpatan((float10)*(float *)((int)(psVar14 + -1) + 0xc) -
                                     (float10)(&creature_pool)[psVar14->target_id].pos_y,
                                     (float10)*pfVar13 -
                                     (float10)(&creature_pool)[psVar14->target_id].pos_x);
            psVar14[-1].vel_y = (float)(fVar21 - (float10)1.5707964);
            fVar21 = (float10)fcos((fVar21 - (float10)1.5707964) - (float10)1.5707964);
            *(float *)((int)(psVar14 + -1) + 0x10) =
                 (float)(fVar21 * (float10)frame_dt * (float10)800.0 +
                        (float10)*(float *)((int)(psVar14 + -1) + 0x10));
            fVar21 = (float10)fsin((float10)psVar14[-1].vel_y - (float10)1.5707964);
            psVar14->vel_y =
                 (float)(fVar21 * (float10)frame_dt * (float10)800.0 + (float10)psVar14->vel_y);
            if (350.0 < SQRT(*(float *)((int)(psVar14 + -1) + 0x10) *
                             *(float *)((int)(psVar14 + -1) + 0x10) +
                             psVar14->vel_y * psVar14->vel_y)) {
              fVar21 = (float10)fcos((float10)psVar14[-1].vel_y - (float10)1.5707964);
              *(float *)((int)(psVar14 + -1) + 0x10) =
                   (float)((float10)*(float *)((int)(psVar14 + -1) + 0x10) -
                          fVar21 * (float10)frame_dt * (float10)800.0);
              fVar21 = (float10)fsin((float10)psVar14[-1].vel_y - (float10)1.5707964);
              psVar14->vel_y =
                   (float)((float10)psVar14->vel_y - fVar21 * (float10)frame_dt * (float10)800.0);
            }
            fVar11 = *(float *)((int)(psVar14 + -1) + 4) - frame_dt * 0.5;
            goto LAB_00421d65;
          }
        }
        local_c4 = psVar14->vel_y;
        fVar11 = psVar14->trail_timer -
                 (ABS(local_c4) + ABS(*(float *)((int)(psVar14 + -1) + 0x10))) * frame_dt * 0.01;
        psVar14->trail_timer = fVar11;
        if (fVar11 < 0.0) {
          fVar21 = (float10)fcos((float10)psVar14[-1].vel_y + (float10)1.5707964);
          fStack_30 = (float)fVar21;
          local_b0 = fStack_30 * 90.0;
          local_ac = (float)(fVar21 * (float10)90.0);
          fVar21 = (float10)fcos((float10)psVar14[-1].vel_y - (float10)1.5707964);
          fStack_40 = (float)fVar21;
          fVar21 = (float10)fsin((float10)psVar14[-1].vel_y - (float10)1.5707964);
          fStack_50 = fStack_40 * 9.0;
          local_a8 = *pfVar13 - fStack_50;
          local_a4 = (float)((float10)*(float *)((int)(psVar14 + -1) + 0xc) - fVar21 * (float10)9.0)
          ;
          iVar7 = fx_spawn_sprite(&local_a8,&local_b0,14.0);
          psVar14->trail_timer = 0.06;
          (&sprite_effect_pool)[iVar7].color_a = 0.25;
        }
        iVar7 = creature_find_in_radius(pfVar13,8.0,0);
        if (iVar7 != -1) {
          if ((&creature_pool)[iVar7].hitbox_size == 16.0) {
            highscore_active_record.shots_hit = highscore_active_record.shots_hit + 1;
          }
          if (bonus_freeze_timer <= 0.0) {
            iVar12 = crt_rand();
            fStack_18 = (float)(iVar12 % 0x14 + -10);
            iVar12 = crt_rand();
            local_90 = fStack_18 + (&creature_pool)[iVar7].pos_x;
            local_8c = (float)(iVar12 % 0x14 + -10) + (&creature_pool)[iVar7].pos_y;
            fx_queue_add_random(&local_90);
            iVar12 = crt_rand();
            fStack_38 = (float)(iVar12 % 0x14 + -10);
            iVar12 = crt_rand();
            local_80 = fStack_38 + (&creature_pool)[iVar7].pos_x;
            local_7c = (float)(iVar12 % 0x14 + -10) + (&creature_pool)[iVar7].pos_y;
            fx_queue_add_random(&local_80);
            iVar12 = crt_rand();
            local_28 = (float)(iVar12 % 0x14 + -10);
            iVar12 = crt_rand();
            local_70 = local_28 + (&creature_pool)[iVar7].pos_x;
            local_6c = (float)(iVar12 % 0x14 + -10) + (&creature_pool)[iVar7].pos_y;
            fx_queue_add_random(&local_70);
          }
          else {
            local_ec = 4;
            do {
              iVar12 = crt_rand();
              effect_spawn_freeze_shard(pfVar13,(float)(iVar12 % 0x264) * 0.01);
              local_ec = local_ec + -1;
            } while (local_ec != 0);
          }
          sVar5 = psVar14->type_id;
          local_dc = 150.0;
          if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET) {
            local_dc = *(float *)((int)(psVar14 + -1) + 4) * 50.0 + 500.0;
            if (2 < config_blob.detail_preset) {
              effect_spawn_explosion_burst(pfVar13,0.4);
            }
          }
          else if (sVar5 == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
            local_dc = *(float *)((int)(psVar14 + -1) + 4) * 20.0 + 80.0;
          }
          else if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN) {
            local_dc = *(float *)((int)(psVar14 + -1) + 4) * 20.0 + 40.0;
          }
          if (((demo_mode_active == '\0') && (music_muted_flag == '\0')) &&
             (config_blob.reserved0._24_4_ != 2)) {
            sfx_play_exclusive(music_track_extra_0);
          }
          else {
            sfx_play_panned(sfx_explosion_medium);
          }
          local_94 = 1.0 / frame_dt;
          (&creature_pool)[iVar7].state_flag = '\x01';
          local_98 = local_94 * *(float *)((int)(psVar14 + -1) + 0x10);
          local_94 = local_94 * psVar14->vel_y;
          creature_apply_damage(iVar7,local_dc,3,&local_98);
          fVar11 = bonus_freeze_timer;
          sVar5 = psVar14->type_id;
          if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET) {
            psVar14->type_id = SECONDARY_PROJECTILE_TYPE_EXPLODING;
            *(undefined4 *)((int)(psVar14 + -1) + 0x10) = 0;
            psVar14->vel_y = 1.0;
            if (fVar11 <= 0.0) {
              iVar12 = 0x14;
              do {
                iVar9 = crt_rand();
                fVar11 = (float)(iVar9 % 0x274) * 0.01;
                iVar9 = crt_rand();
                fVar21 = (float10)fcos((float10)fVar11);
                local_58 = (float)(fVar21 * (float10)(iVar9 % 0x5a));
                fVar21 = (float10)fsin((float10)fVar11);
                local_78 = local_58 + (&creature_pool)[iVar7].pos_x;
                local_74 = (float)(fVar21 * (float10)(iVar9 % 0x5a) +
                                  (float10)(&creature_pool)[iVar7].pos_y);
                fx_queue_add_random(&local_78);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            else {
              iVar7 = 8;
              do {
                iVar12 = crt_rand();
                effect_spawn_freeze_shard(pfVar13,(float)(iVar12 % 0x264) * 0.01);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else if (sVar5 == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
            psVar14->type_id = SECONDARY_PROJECTILE_TYPE_EXPLODING;
            *(undefined4 *)((int)(psVar14 + -1) + 0x10) = 0;
            psVar14->vel_y = 0.35;
            if (fVar11 <= 0.0) {
              iVar12 = 10;
              do {
                iVar9 = crt_rand();
                fVar11 = (float)(iVar9 % 0x274) * 0.01;
                uVar10 = crt_rand();
                uVar10 = uVar10 & 0x8000003f;
                if ((int)uVar10 < 0) {
                  uVar10 = (uVar10 - 1 | 0xffffffc0) + 1;
                }
                fVar21 = (float10)fcos((float10)fVar11);
                fVar20 = (float10)fsin((float10)fVar11);
                local_88 = (float)(fVar21 * (float10)(int)uVar10) + (&creature_pool)[iVar7].pos_x;
                local_84 = (float)(fVar20 * (float10)(int)uVar10 +
                                  (float10)(&creature_pool)[iVar7].pos_y);
                fx_queue_add_random(&local_88);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            else {
              iVar7 = 8;
              do {
                iVar12 = crt_rand();
                effect_spawn_freeze_shard(pfVar13,(float)(iVar12 % 0x264) * 0.01);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
          else if (sVar5 == SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN) {
            psVar14->type_id = SECONDARY_PROJECTILE_TYPE_EXPLODING;
            *(undefined4 *)((int)(psVar14 + -1) + 0x10) = 0;
            psVar14->vel_y = 0.25;
            if (fVar11 <= 0.0) {
              iVar12 = 3;
              do {
                iVar9 = crt_rand();
                fVar11 = (float)(iVar9 % 0x274) * 0.01;
                iVar9 = crt_rand();
                fVar21 = (float10)fcos((float10)fVar11);
                fVar20 = (float10)fsin((float10)fVar11);
                local_48 = (float)(fVar21 * (float10)(iVar9 % 0x2c)) + (&creature_pool)[iVar7].pos_x
                ;
                local_44 = (float)(fVar20 * (float10)(iVar9 % 0x2c) +
                                  (float10)(&creature_pool)[iVar7].pos_y);
                fx_queue_add_random(&local_48);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            else {
              iVar12 = 8;
              do {
                iVar9 = crt_rand();
                effect_spawn_freeze_shard
                          (&(&creature_pool)[iVar7].pos_x,(float)(iVar9 % 0x264) * 0.01);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
          }
          local_ec = 0;
          do {
            iVar7 = crt_rand();
            fVar21 = (float10)(iVar7 % 800) * (float10)0.1;
            fVar20 = (float10)fcos((float10)local_ec * (float10)0.62831855);
            local_68 = (float)fVar20;
            fVar20 = (float10)fsin((float10)local_ec * (float10)0.62831855);
            local_20 = (float)(fVar21 * (float10)local_68);
            local_1c = (float)(fVar20 * fVar21);
            iVar7 = fx_spawn_sprite(pfVar13,&local_20,14.0);
            local_ec = local_ec + 1;
            (&sprite_effect_pool)[iVar7].color_a = 0.37;
          } while (local_ec < 10);
        }
        if (*(float *)((int)(psVar14 + -1) + 4) <= 0.0) {
          psVar14->type_id = SECONDARY_PROJECTILE_TYPE_EXPLODING;
          *(undefined4 *)((int)(psVar14 + -1) + 0x10) = 0;
          psVar14->vel_y = 0.5;
        }
      }
    }
    psVar14 = (secondary_projectile_vel_y_block_t *)((int)(psVar14 + 2) + 4);
  } while ((int)psVar14 < 0x4965f0);
  pfVar13 = &sprite_effect_pool.pos_y;
  do {
    if ((char)((sprite_effect_t *)(pfVar13 + -7))->active != '\0') {
      local_68 = frame_dt * pfVar13[1];
      fVar11 = frame_dt * pfVar13[2];
      pfVar13[-1] = local_68 + pfVar13[-1];
      *pfVar13 = fVar11 + *pfVar13;
      pfVar13[-2] = frame_dt * 3.0 + pfVar13[-2];
      fVar11 = pfVar13[-3] - frame_dt;
      pfVar13[-3] = fVar11;
      if (fVar11 <= 0.0) {
        *(undefined1 *)&((sprite_effect_t *)(pfVar13 + -7))->active = 0;
      }
      pfVar13[3] = frame_dt * 60.0 + pfVar13[3];
    }
    pfVar13 = pfVar13 + 0xb;
  } while ((int)pfVar13 < 0x49aa3c);
  local_e8 = 0;
  pfVar13 = &particle_pool.vel_y;
  do {
    if (((particle_t *)(pfVar13 + -4))->active != '\0') {
      if (SUB41(pfVar13[8],0) == '\b') {
        pfVar13[5] = pfVar13[5] - frame_dt * 0.11;
        pfVar13[7] = frame_dt * 5.0 + pfVar13[7];
        if (*(uchar *)((int)pfVar13 + -0xf) != '\0') {
          fVar11 = frame_dt * pfVar13[-1];
          if (pfVar13[5] <= 0.15) {
            fStack_40 = fVar11 * 0.55;
            fVar23 = fStack_40 * pfVar13[5];
            fVar6 = frame_dt * *pfVar13 * 0.55 * pfVar13[5];
            fStack_50 = fVar23;
            fStack_30 = fVar11;
            goto LAB_004226a3;
          }
          local_b8 = fVar11 * pfVar13[5];
          local_b4 = frame_dt * *pfVar13 * pfVar13[5];
          local_68 = fVar11;
          vec2_add(pfVar13 + -3,&local_b8);
        }
      }
      else {
        pfVar13[5] = pfVar13[5] - frame_dt * 0.9;
        pfVar13[7] = frame_dt + pfVar13[7];
        fVar11 = frame_dt * pfVar13[-1];
        if (pfVar13[5] <= 0.15) {
          local_58 = fVar11 * 2.5;
          fVar23 = local_58 * 0.15;
          fVar6 = frame_dt * *pfVar13 * 2.5 * 0.15;
          local_90 = fVar23;
          local_28 = fVar11;
LAB_004226a3:
          pfVar13[-3] = fVar23 + pfVar13[-3];
          pfVar13[-2] = fVar6 + pfVar13[-2];
        }
        else {
          fStack_38 = fVar11 * 2.5;
          local_a0 = fStack_38 * pfVar13[5];
          local_9c = frame_dt * *pfVar13 * 2.5 * pfVar13[5];
          fStack_18 = fVar11;
          vec2_add(pfVar13 + -3,&local_a0);
        }
      }
      cVar3 = SUB41(pfVar13[8],0);
      if (cVar3 == '\0') {
        if (0.0 < pfVar13[5]) {
LAB_00422767:
          if (*(uchar *)((int)pfVar13 + -0xf) == '\x01') {
            if (cVar3 == '\0') {
              iVar7 = crt_rand();
              fVar21 = (float10)(iVar7 % 100 + -0x32) * (float10)0.06 * (float10)pfVar13[5] *
                       (float10)frame_dt * (float10)1.96;
LAB_00422821:
              fVar11 = pfVar13[6];
              pfVar13[6] = (float)((float10)fVar11 - fVar21);
              fVar21 = (float10)fcos((float10)fVar11 - fVar21);
              pfVar13[-1] = (float)(fVar21 * (float10)82.0);
              fVar21 = (float10)fsin((float10)pfVar13[6]);
              fVar21 = fVar21 * (float10)82.0;
            }
            else {
              if (cVar3 != '\b') {
                iVar7 = crt_rand();
                fVar21 = (float10)(iVar7 % 100 + -0x32) * (float10)0.06 * (float10)pfVar13[5] *
                         (float10)frame_dt * (float10)1.1;
                goto LAB_00422821;
              }
              iVar7 = crt_rand();
              fVar21 = (float10)pfVar13[6] -
                       (float10)(iVar7 % 100 + -0x32) * (float10)0.06 * (float10)pfVar13[5] *
                       (float10)frame_dt * (float10)1.1;
              pfVar13[6] = (float)fVar21;
              fVar21 = (float10)fcos(fVar21);
              pfVar13[-1] = (float)(fVar21 * (float10)62.0);
              fVar21 = (float10)fsin((float10)pfVar13[6]);
              fVar21 = fVar21 * (float10)62.0;
            }
            *pfVar13 = (float)fVar21;
          }
          if (pfVar13[5] <= 1.0) {
            fVar11 = pfVar13[5];
          }
          else {
            fVar11 = 1.0;
          }
          pfVar13[4] = fVar11;
          fVar11 = 1.0 - pfVar13[5] * 0.95;
          pfVar13[1] = fVar11;
          pfVar13[2] = fVar11;
          if (*(uchar *)((int)pfVar13 + -0xf) != '\0') {
            pfVar1 = pfVar13 + -3;
            fVar11 = (float)creature_find_in_radius(pfVar1,pfVar13[5] * 8.0,0);
            if (fVar11 != -NAN) {
              *(uchar *)((int)pfVar13 + -0xf) = '\0';
              if (SUB41(pfVar13[8],0) == '\b') {
                fVar23 = (&creature_pool)[(int)fVar11].pos_y;
                *pfVar1 = (&creature_pool)[(int)fVar11].pos_x;
                pfVar13[-2] = fVar23;
                pfVar13[-1] = 0.0;
                *pfVar13 = 0.0;
                (&creature_pool)[(int)fVar11].state_flag = '\0';
                pfVar13[9] = fVar11;
              }
              else {
                fVar23 = pfVar13[6];
                while (6.2831855 < fVar23) {
                  fVar23 = pfVar13[6] - 6.2831855;
                  pfVar13[6] = fVar23;
                }
                fVar23 = pfVar13[6];
                while (fVar23 < 0.0) {
                  fVar23 = pfVar13[6] + 6.2831855;
                  pfVar13[6] = fVar23;
                }
                local_80 = (float)((float10)frame_dt * (float10)pfVar13[-1]);
                local_70 = *pfVar1 - local_80;
                pfVar1 = &(&creature_pool)[(int)fVar11].pos_x;
                local_98 = local_70 - *pfVar1;
                fVar21 = (float10)fpatan(((float10)pfVar13[-2] -
                                         (float10)frame_dt * (float10)*pfVar13) -
                                         (float10)(&creature_pool)[(int)fVar11].pos_y,
                                         (float10)local_98);
                if ((float10)6.2831855 < fVar21) {
                  do {
                    fVar21 = fVar21 - (float10)6.2831855;
                  } while ((float10)6.2831855 < fVar21);
                }
                if (fVar21 < (float10)0.0) {
                  do {
                    fVar21 = fVar21 + (float10)6.2831855;
                  } while (fVar21 < (float10)0.0);
                }
                if ((float10)pfVar13[6] <= fVar21) {
                  fVar23 = pfVar13[6] + 1.2566371;
                }
                else {
                  fVar23 = pfVar13[6] - 1.2566371;
                }
                pfVar13[6] = fVar23;
                fVar21 = (float10)fcos((float10)pfVar13[6]);
                pfVar13[-1] = (float)(fVar21 * (float10)82.0);
                fVar21 = (float10)fsin((float10)pfVar13[6]);
                *pfVar13 = (float)(fVar21 * (float10)82.0);
                iVar7 = crt_rand();
                (&creature_pool)[(int)fVar11].state_flag = '\x01';
                local_b0 = 0.0;
                local_ac = 0.0;
                fVar23 = (float)(iVar7 % 10) * 0.1;
                pfVar13[-1] = fVar23 * pfVar13[-1];
                *pfVar13 = fVar23 * *pfVar13;
                creature_apply_damage((int)fVar11,pfVar13[5] * 10.0,4,&local_b0);
                if (1.6 < (&creature_pool)[(int)fVar11].tint_g +
                          (&creature_pool)[(int)fVar11].tint_b +
                          (&creature_pool)[(int)fVar11].tint_r) {
                  fVar23 = 1.0 - pfVar13[5] * 0.01;
                  (&creature_pool)[(int)fVar11].tint_r =
                       fVar23 * (&creature_pool)[(int)fVar11].tint_r;
                  (&creature_pool)[(int)fVar11].tint_g =
                       fVar23 * (&creature_pool)[(int)fVar11].tint_g;
                  (&creature_pool)[(int)fVar11].tint_b =
                       fVar23 * (&creature_pool)[(int)fVar11].tint_b;
                  if (0.0 <= (&creature_pool)[(int)fVar11].tint_r) {
                    if (1.0 < (&creature_pool)[(int)fVar11].tint_r) {
                      (&creature_pool)[(int)fVar11].tint_r = 1.0;
                    }
                  }
                  else {
                    (&creature_pool)[(int)fVar11].tint_r = 0.0;
                  }
                  if (0.0 <= (&creature_pool)[(int)fVar11].tint_g) {
                    if (1.0 < (&creature_pool)[(int)fVar11].tint_g) {
                      (&creature_pool)[(int)fVar11].tint_g = 1.0;
                    }
                  }
                  else {
                    (&creature_pool)[(int)fVar11].tint_g = 0.0;
                  }
                  if (0.0 <= (&creature_pool)[(int)fVar11].tint_b) {
                    if (1.0 < (&creature_pool)[(int)fVar11].tint_b) {
                      (&creature_pool)[(int)fVar11].tint_b = 1.0;
                    }
                  }
                  else {
                    (&creature_pool)[(int)fVar11].tint_b = 0.0;
                  }
                  if (0.0 <= (&creature_pool)[(int)fVar11].tint_a) {
                    if (1.0 < (&creature_pool)[(int)fVar11].tint_a) {
                      (&creature_pool)[(int)fVar11].tint_a = 1.0;
                    }
                  }
                  else {
                    (&creature_pool)[(int)fVar11].tint_a = 0.0;
                  }
                }
                if (local_e8 % 3 == 0) {
                  iVar7 = crt_rand();
                  iVar12 = crt_rand();
                  local_a4 = (float)(iVar12 % 0x3c + -0x1e);
                  local_a8 = (float)(iVar7 % 0x3c + -0x1e);
                  iVar7 = fx_spawn_sprite(pfVar1,&local_a8,13.0);
                  (&sprite_effect_pool)[iVar7].color_a = 0.7;
                }
                fx_queue_add_random(pfVar1);
                local_74 = *pfVar13;
                local_84 = local_74 * frame_dt;
                *pfVar1 = pfVar13[-1] * frame_dt + *pfVar1;
                (&creature_pool)[(int)fVar11].pos_y = local_84 + (&creature_pool)[(int)fVar11].pos_y
                ;
              }
            }
          }
        }
        else {
          ((particle_t *)(pfVar13 + -4))->active = '\0';
        }
      }
      else {
        if (0.8 < pfVar13[5]) goto LAB_00422767;
        ((particle_t *)(pfVar13 + -4))->active = '\0';
        if ((SUB41(pfVar13[8],0) == '\b') && (pfVar13[9] != -NAN)) {
          if ((&creature_pool)[(int)pfVar13[9]].active != '\0') {
            iVar7 = crt_rand();
            sfx_play_panned((float)(&creature_type_table)[(&creature_pool)[(int)pfVar13[9]].type_id]
                                   .sfx_bank_a[iVar7 % 3]);
          }
          creature_handle_death((int)pfVar13[9],false);
        }
      }
    }
    pfVar13 = pfVar13 + 0xe;
    local_e8 = local_e8 + 1;
    if (0x495ac7 < (int)pfVar13) {
      return;
    }
  } while( true );
}



/* projectile_render @ 00422c70 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders projectiles/secondary projectiles and related beam/trail effects */

void projectile_render(void)

{
  projectile_type_id_t pVar1;
  secondary_projectile_type_id_t sVar2;
  IGrim2D_vtbl *pIVar3;
  projectile_tail_t *ppVar4;
  projectile_vel_y_block_t *ppVar5;
  projectile_t *ppVar6;
  projectile_pos_y_block_t *ppVar7;
  float *pfVar8;
  secondary_projectile_pos_y_block_t *psVar9;
  float unaff_EDI;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  ulonglong uVar15;
  longlong lVar16;
  float in_stack_00000004;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float in_stack_fffffe10;
  float fVar23;
  float fVar24;
  int iVar25;
  float in_stack_fffffe20;
  float in_stack_fffffe24;
  float fVar26;
  float in_stack_fffffe34;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fStack_198;
  float fStack_194;
  float fStack_190;
  float fStack_168;
  float fStack_160;
  float fStack_150;
  float fStack_134;
  float fStack_12c;
  float fStack_128;
  float fStack_120;
  float fStack_118;
  float fStack_114;
  float fStack_ec;
  float fStack_c4;
  float fStack_74;
  float fStack_5c;
  float fStack_54;
  float fStack_4c;
  float fStack_24;
  
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.0,0.0,in_stack_00000004 * 0.5);
  (*grim_interface_ptr->vtable->grim_set_color_slot)(2,0.0,0.0,0.0,in_stack_00000004 * 0.2);
  (*grim_interface_ptr->vtable->grim_set_color_slot)(3,0.0,0.0,0.0,in_stack_00000004 * 0.2);
  (*grim_interface_ptr->vtable->grim_bind_texture)((int)bullet_trail_texture,0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,0.5);
  iVar10 = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    pfVar8 = &player_state_table.aim_heading;
    do {
      if (0.0 < pfVar8[-0xb7]) {
        fVar11 = (float10)*pfVar8 - (float10)1.5707964;
        fVar12 = (float10)fcos(fVar11);
        fVar13 = (float10)fsin(fVar11);
        fVar30 = pfVar8[-0xbb];
        fStack_ec = (float)fVar13 * 512.0 + pfVar8[-0xba];
        fVar14 = (float10)fcos(fVar11 - (float10)0.150915);
        fVar28 = (float)(fVar14 * (float10)15.0);
        fVar11 = (float10)fsin(fVar11 - (float10)0.150915);
        fVar29 = (float)((float10)pfVar8[-0xba] + fVar11 * (float10)15.0);
        fVar14 = (float10)fcos((float10)*pfVar8);
        fVar11 = (float10)fsin((float10)*pfVar8);
        fStack_150 = (float)(((float10)(pfVar8[-0xbb] + fVar28) + (float10)camera_offset_x) -
                            fVar14 * (float10)1.1);
        fStack_114 = fVar29 + camera_offset_y + (float)(fVar11 * (float10)1.1);
        fVar11 = (float10)camera_offset_x;
        if (0 < player_state_table.perk_counts[perk_id_sharpshooter]) {
          (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
          (*grim_interface_ptr->vtable->grim_begin_batch)();
          in_stack_fffffe24 = fStack_160;
          (*grim_interface_ptr->vtable->grim_draw_quad_points)
                    (fVar29,fStack_160,fStack_12c,fStack_128,fStack_134,fVar28,(float)fVar13 * 512.0
                     ,(float)((float10)(float)(fVar12 * (float10)512.0 + (float10)fVar30) + fVar11 +
                             fVar14 * (float10)1.1));
          (*grim_interface_ptr->vtable->grim_end_batch)();
          unaff_EDI = 2.8026e-44;
          (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
          in_stack_fffffe20 = fVar29;
          in_stack_fffffe34 = fVar28;
        }
      }
      iVar10 = iVar10 + 1;
      pfVar8 = pfVar8 + 0xd8;
    } while (iVar10 < (int)config_blob.reserved0._20_4_);
  }
  fStack_198 = 0.0;
  (*grim_interface_ptr->vtable->grim_set_color_slot)(0,0.5,0.5,0.5,0.0);
  fVar30 = 0.0;
  fVar29 = 0.5;
  fVar28 = 0.5;
  (*grim_interface_ptr->vtable->grim_set_color_slot)(1,0.5,0.5,0.5,0.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  ppVar5 = &projectile_pool[0].pos.tail.vy;
  fStack_194 = in_stack_fffffe20;
  fStack_168 = in_stack_fffffe24;
  do {
    if ((*(char *)((int)(ppVar5 + -1) + 8) != '\0') &&
       ((pVar1 = ppVar5->type_id, (int)pVar1 < 8 || (pVar1 == PROJECTILE_TYPE_SPLITTER_GUN)))) {
      if (pVar1 == PROJECTILE_TYPE_NONE) {
        *(undefined1 *)((int)(ppVar5 + -1) + 8) = 0;
      }
      fStack_5c = ppVar5->life_timer;
      if (fStack_5c <= 1.0) {
        if (fStack_5c < 0.0) {
          fStack_5c = 0.0;
        }
      }
      else {
        fStack_5c = 1.0;
      }
      (*grim_interface_ptr->vtable->grim_set_color_slot)(2,0.5,0.5,0.5,fStack_5c * fStack_24);
      (*grim_interface_ptr->vtable->grim_set_color_slot)(3,0.5,0.5,0.5,fStack_5c * fStack_24);
      pVar1 = ppVar5->type_id;
      if (pVar1 == PROJECTILE_TYPE_ASSAULT_RIFLE) {
        fVar27 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x18);
        fStack_4c = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x1c);
        fVar17 = fVar27 - *(float *)((int)(ppVar5 + -1) + 0x20);
        in_stack_fffffe10 = fStack_4c - ppVar5->vel_y;
        fVar27 = fVar27 + *(float *)((int)(ppVar5 + -1) + 0x20);
        fVar23 = fStack_4c + ppVar5->vel_y;
        fStack_168 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x10);
        fVar24 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x14);
        fStack_198 = fStack_168 + *(float *)((int)(ppVar5 + -1) + 0x20);
        fStack_194 = fVar24 + ppVar5->vel_y;
        fStack_168 = fStack_168 - *(float *)((int)(ppVar5 + -1) + 0x20);
        fVar24 = fVar24 - ppVar5->vel_y;
        fStack_114 = fVar23;
      }
      else if (pVar1 == PROJECTILE_TYPE_PISTOL) {
        fVar21 = *(float *)((int)(ppVar5 + -1) + 0x20) * 1.2;
        fVar24 = ppVar5->vel_y * 1.2;
        fVar27 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x18);
        fStack_54 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x1c);
        fVar17 = fVar27 - fVar21;
        in_stack_fffffe10 = fStack_54 - fVar24;
        fVar27 = fVar27 + fVar21;
        fVar23 = fStack_54 + fVar24;
        fStack_168 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x10);
        fStack_74 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x14);
        fStack_198 = fStack_168 + fVar21;
        fStack_194 = fStack_74 + fVar24;
        fStack_168 = fStack_168 - fVar21;
        fVar24 = fStack_74 - fVar24;
        fStack_190 = fVar17;
      }
      else if (pVar1 == PROJECTILE_TYPE_GAUSS_GUN) {
        (*grim_interface_ptr->vtable->grim_set_color_slot)(2,0.2,0.5,1.0,fStack_5c);
        (*grim_interface_ptr->vtable->grim_set_color_slot)(3,0.2,0.5,1.0,fStack_5c);
        fVar28 = *(float *)((int)(ppVar5 + -1) + 0x20) * 1.1;
        fStack_c4 = ppVar5->vel_y * 1.1;
        fVar27 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x18);
        fVar23 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x1c);
        fVar17 = fVar27 - fVar28;
        in_stack_fffffe10 = fVar23 - fStack_c4;
        fVar27 = fVar27 + fVar28;
        fVar23 = fVar23 + fStack_c4;
        fStack_168 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x10);
        fVar24 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x14);
        fStack_198 = fStack_168 + fVar28;
        fStack_194 = fVar24 + fStack_c4;
        fStack_168 = fStack_168 - fVar28;
        fVar24 = fVar24 - fStack_c4;
        fVar28 = fVar24;
        fStack_ec = in_stack_fffffe10;
      }
      else {
        fVar30 = *(float *)((int)(ppVar5 + -1) + 0x20) * 0.7;
        unaff_EDI = ppVar5->vel_y * 0.7;
        fVar27 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x18);
        fVar23 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x1c);
        fVar17 = fVar27 - fVar30;
        in_stack_fffffe10 = fVar23 - unaff_EDI;
        fVar27 = fVar27 + fVar30;
        fVar23 = fVar23 + unaff_EDI;
        fStack_168 = camera_offset_x + *(float *)((int)(ppVar5 + -1) + 0x10);
        fVar24 = camera_offset_y + *(float *)((int)(ppVar5 + -1) + 0x14);
        fStack_198 = fStack_168 + fVar30;
        fStack_194 = fVar24 + unaff_EDI;
        fStack_168 = fStack_168 - fVar30;
        fVar24 = fVar24 - unaff_EDI;
        fStack_150 = fStack_198;
      }
      (*grim_interface_ptr->vtable->grim_draw_quad_points)
                (fVar17,in_stack_fffffe10,fVar27,fVar23,fStack_198,fStack_194,fStack_168,fVar24);
    }
    ppVar5 = (projectile_vel_y_block_t *)((int)(ppVar5 + 1) + 0x1c);
  } while ((int)ppVar5 < 0x493ed4);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  fVar23 = 6.080727e-39;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
  effect_select_texture(0xd);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  if (0.0 < (&player_state_table)[render_overlay_player_index].muzzle_flash_alpha) {
    fVar11 = ((float10)(&player_state_table)[render_overlay_player_index].aim_heading -
             (float10)1.5707964) - (float10)0.150915;
    fVar12 = (float10)fcos(fVar11);
    fVar24 = (float)(fVar12 * (float10)15.0);
    fVar11 = (float10)fsin(fVar11);
    in_stack_fffffe34 = (float)(fVar11 * (float10)15.0);
    (*grim_interface_ptr->vtable->grim_set_color)
              (1.0,1.0,1.0,
               fStack_4c * (&player_state_table)[render_overlay_player_index].muzzle_flash_alpha);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_draw_quad)
              ((fVar24 + (&player_state_table)[render_overlay_player_index].pos_x + camera_offset_x
               ) - 80.0,(in_stack_fffffe34 +
                         (&player_state_table)[render_overlay_player_index].pos_y + camera_offset_y
                        ) - 80.0,160.0,160.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  ppVar7 = &projectile_pool[0].pos;
  do {
    if ((*(char *)((int)(ppVar7 + -1) + 0x28) != '\0') &&
       ((((pVar1 = (ppVar7->tail).vy.type_id, pVar1 == PROJECTILE_TYPE_PLASMA_RIFLE ||
          (pVar1 == PROJECTILE_TYPE_PLASMA_MINIGUN)) || (pVar1 == PROJECTILE_TYPE_SPIDER_PLASMA)) ||
        ((pVar1 == PROJECTILE_TYPE_SHRINKIFIER || (pVar1 == PROJECTILE_TYPE_PLASMA_CANNON)))))) {
      if ((ppVar7->tail).vy.life_timer == 0.4) {
        if (pVar1 == PROJECTILE_TYPE_PLASMA_RIFLE) {
          uVar15 = __ftol();
          lVar16 = __ftol();
          iVar10 = (int)((longlong)
                         ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff) /
                        (longlong)(int)lVar16);
          if (8 < iVar10) {
            iVar10 = 8;
          }
          fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
          fVar12 = (float10)fcos(fVar11);
          fVar30 = (float)(fVar12 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.5);
          fVar11 = (float10)fsin(fVar11);
          fVar23 = (float)(fVar11 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.5);
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c * 0.4);
          iVar25 = 0;
          if (0 < iVar10) {
            do {
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        (((float)iVar25 * fVar30 + *(float *)((int)(ppVar7 + -1) + 0x30) +
                         camera_offset_x) - 11.0,
                         ((float)iVar25 * fVar23 + ppVar7->pos_y + camera_offset_y) - 11.0,22.0,
                         22.0);
              iVar25 = iVar25 + 1;
            } while (iVar25 < iVar10);
          }
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c * 0.45);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 28.0,
                     (camera_offset_y + ppVar7->pos_y) - 28.0,56.0,56.0);
          fVar24 = fStack_4c * 0.3;
          pIVar3 = grim_interface_ptr->vtable;
LAB_00423cb4:
          (*pIVar3->grim_set_color)(1.0,1.0,1.0,fVar24);
          if (config_blob.reserved0[0x10] != '\0') {
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 128.0,
                       (camera_offset_y + ppVar7->pos_y) - 128.0,256.0,256.0);
          }
        }
        else {
          if (pVar1 == PROJECTILE_TYPE_PLASMA_MINIGUN) {
            uVar15 = __ftol();
            lVar16 = __ftol();
            iVar10 = (int)((longlong)
                           ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff) /
                          (longlong)(int)lVar16);
            if (3 < iVar10) {
              iVar10 = 3;
            }
            fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
            fVar12 = (float10)fcos(fVar11);
            fVar30 = (float)(fVar12 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
            fVar11 = (float10)fsin(fVar11);
            fVar23 = (float)(fVar11 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c * 0.4);
            iVar25 = 0;
            if (0 < iVar10) {
              do {
                (*grim_interface_ptr->vtable->grim_draw_quad)
                          (((float)iVar25 * fVar30 + *(float *)((int)(ppVar7 + -1) + 0x30) +
                           camera_offset_x) - 6.0,
                           ((float)iVar25 * fVar23 + ppVar7->pos_y + camera_offset_y) - 6.0,12.0,
                           12.0);
                iVar25 = iVar25 + 1;
              } while (iVar25 < iVar10);
            }
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_168);
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 8.0,
                       (camera_offset_y + ppVar7->pos_y) - 8.0,16.0,16.0);
            pIVar3 = grim_interface_ptr->vtable;
            fVar27 = 1.0;
            fVar24 = 1.0;
            fVar17 = 1.0;
          }
          else {
            if (pVar1 == PROJECTILE_TYPE_PLASMA_CANNON) {
              uVar15 = __ftol();
              lVar16 = __ftol();
              iVar10 = (int)((longlong)
                             ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff)
                            / (longlong)(int)lVar16);
              if (0x12 < iVar10) {
                iVar10 = 0x12;
              }
              fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
              fVar12 = (float10)fcos(fVar11);
              fVar30 = (float)(fVar12 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.6);
              fVar11 = (float10)fsin(fVar11);
              fVar23 = (float)(fVar11 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.6);
              fVar24 = fStack_4c * 0.4;
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar24);
              iVar25 = 0;
              if (0 < iVar10) {
                do {
                  (*grim_interface_ptr->vtable->grim_draw_quad)
                            (((float)iVar25 * fVar30 + *(float *)((int)(ppVar7 + -1) + 0x30) +
                             camera_offset_x) - 22.0,
                             ((float)iVar25 * fVar23 + ppVar7->pos_y + camera_offset_y) - 22.0,44.0
                             ,44.0);
                  iVar25 = iVar25 + 1;
                } while (iVar25 < iVar10);
              }
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c * 0.45);
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 42.0,
                         (camera_offset_y + ppVar7->pos_y) - 42.0,84.0,84.0);
              pIVar3 = grim_interface_ptr->vtable;
              goto LAB_00423cb4;
            }
            if (pVar1 == PROJECTILE_TYPE_SPIDER_PLASMA) {
              uVar15 = __ftol();
              lVar16 = __ftol();
              iVar10 = (int)((longlong)
                             ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff)
                            / (longlong)(int)lVar16);
              if (3 < iVar10) {
                iVar10 = 3;
              }
              fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
              fVar12 = (float10)fcos(fVar11);
              fVar30 = (float)(fVar12 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
              fVar11 = (float10)fsin(fVar11);
              fVar23 = (float)(fVar11 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
              (*grim_interface_ptr->vtable->grim_set_color)(0.3,1.0,0.3,fStack_4c * 0.4);
              iVar25 = 0;
              if (0 < iVar10) {
                do {
                  (*grim_interface_ptr->vtable->grim_draw_quad)
                            (((float)iVar25 * fVar30 + *(float *)((int)(ppVar7 + -1) + 0x30) +
                             camera_offset_x) - 6.0,
                             ((float)iVar25 * fVar23 + ppVar7->pos_y + camera_offset_y) - 6.0,12.0,
                             12.0);
                  iVar25 = iVar25 + 1;
                } while (iVar25 < iVar10);
              }
              (*grim_interface_ptr->vtable->grim_set_color)(0.3,1.0,0.3,fStack_168);
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 8.0,
                         (camera_offset_y + ppVar7->pos_y) - 8.0,16.0,16.0);
              pIVar3 = grim_interface_ptr->vtable;
              fVar27 = 0.3;
              fVar24 = 1.0;
            }
            else {
              if (pVar1 != PROJECTILE_TYPE_SHRINKIFIER) goto LAB_00424111;
              uVar15 = __ftol();
              lVar16 = __ftol();
              iVar10 = (int)((longlong)
                             ((ulonglong)(uint)((int)uVar15 >> 0x1f) << 0x20 | uVar15 & 0xffffffff)
                            / (longlong)(int)lVar16);
              if (3 < iVar10) {
                iVar10 = 3;
              }
              fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
              fVar12 = (float10)fcos(fVar11);
              fVar30 = (float)(fVar12 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
              fVar11 = (float10)fsin(fVar11);
              fVar23 = (float)(fVar11 * (float10)(ppVar7->tail).vy.speed_scale * (float10)2.1);
              (*grim_interface_ptr->vtable->grim_set_color)(0.3,0.3,1.0,fStack_4c * 0.4);
              iVar25 = 0;
              if (0 < iVar10) {
                do {
                  (*grim_interface_ptr->vtable->grim_draw_quad)
                            (((float)iVar25 * fVar30 + *(float *)((int)(ppVar7 + -1) + 0x30) +
                             camera_offset_x) - 6.0,
                             ((float)iVar25 * fVar23 + ppVar7->pos_y + camera_offset_y) - 6.0,12.0,
                             12.0);
                  iVar25 = iVar25 + 1;
                } while (iVar25 < iVar10);
              }
              (*grim_interface_ptr->vtable->grim_set_color)(0.3,0.3,1.0,fStack_168);
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 8.0,
                         (camera_offset_y + ppVar7->pos_y) - 8.0,16.0,16.0);
              pIVar3 = grim_interface_ptr->vtable;
              fVar27 = 1.0;
              fVar24 = 0.3;
            }
            fVar17 = 0.3;
          }
          (*pIVar3->grim_set_color)(fVar17,fVar24,fVar27,fStack_4c * 0.15);
          if (config_blob.reserved0[0x10] != '\0') {
            fVar21 = 120.0;
            fVar17 = 120.0;
            fVar24 = (camera_offset_y + ppVar7->pos_y) - 60.0;
            pIVar3 = grim_interface_ptr->vtable;
            fVar27 = (camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 60.0;
            goto LAB_00424107;
          }
        }
      }
      else {
        fVar24 = (ppVar7->tail).vy.life_timer * 2.5;
        if (fVar24 <= 1.0) {
          if (fVar24 < 0.0) {
            fVar24 = 0.0;
          }
        }
        else {
          fVar24 = 1.0;
        }
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar24 * fStack_4c);
        fVar21 = 56.0;
        fVar17 = 56.0;
        fVar24 = (camera_offset_y + ppVar7->pos_y) - 28.0;
        pIVar3 = grim_interface_ptr->vtable;
        fVar27 = (camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 28.0;
LAB_00424107:
        (*pIVar3->grim_draw_quad)(fVar27,fVar24,fVar17,fVar21);
      }
    }
LAB_00424111:
    ppVar7 = (projectile_pos_y_block_t *)((int)(ppVar7 + 1) + 0xc);
  } while ((int)ppVar7 < 0x493ec4);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  fVar24 = 1.0;
  iVar10 = perk_count_get(perk_id_ion_gun_master);
  if (iVar10 != 0) {
    fVar24 = 1.2;
  }
  (*grim_interface_ptr->vtable->grim_bind_texture)(projectile_texture,0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  fVar27 = 0.0;
  ppVar4 = &projectile_pool[0].pos.tail;
  fVar17 = fStack_4c;
  do {
    fVar21 = (float)((int)(ppVar4 + -1) + 0x18);
    fVar26 = in_stack_fffffe34;
    if (*(char *)((int)(ppVar4 + -1) + 0x18) != '\0') {
      pVar1 = (ppVar4->vy).type_id;
      if (pVar1 == PROJECTILE_TYPE_PULSE_GUN) {
        if ((ppVar4->vy).life_timer == 0.4) {
          fVar26 = *(float *)((int)(ppVar4 + -1) + 0x28) - *(float *)((int)(ppVar4 + -1) + 0x20);
          fVar18 = ppVar4->origin_y - *(float *)((int)(ppVar4 + -1) + 0x24);
          fVar18 = SQRT(fVar18 * fVar18 + fVar26 * fVar26) * 0.01;
          (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(ppVar4 + -1) + 0x1c));
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(2,0);
          (*grim_interface_ptr->vtable->grim_set_color)(0.1,0.6,0.2,fStack_4c * 0.7);
          fVar26 = fVar18 * 16.0;
          pIVar3 = grim_interface_ptr->vtable;
          fVar18 = fVar18 * 8.0;
LAB_00424257:
          (*pIVar3->grim_draw_quad)
                    ((camera_offset_x + *(float *)((int)(ppVar4 + -1) + 0x20)) - fVar18,
                     (camera_offset_y + *(float *)((int)(ppVar4 + -1) + 0x24)) - fVar18,fVar26,
                     fVar26);
          fVar26 = in_stack_fffffe34;
        }
        else {
          (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(ppVar4 + -1) + 0x1c));
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(2,0);
          fVar26 = (ppVar4->vy).life_timer * 2.5;
          if (fVar26 <= 1.0) {
            if (fVar26 < 0.0) {
              fVar26 = 0.0;
            }
          }
          else {
            fVar26 = 1.0;
          }
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar26 * fStack_4c);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + *(float *)((int)(ppVar4 + -1) + 0x20)) - 28.0,
                     (camera_offset_y + *(float *)((int)(ppVar4 + -1) + 0x24)) - 28.0,56.0,56.0);
          fVar26 = in_stack_fffffe34;
        }
      }
      else if (pVar1 == PROJECTILE_TYPE_SPLITTER_GUN) {
        if ((ppVar4->vy).life_timer == 0.4) {
          fVar26 = *(float *)((int)(ppVar4 + -1) + 0x28) - *(float *)((int)(ppVar4 + -1) + 0x20);
          fVar18 = ppVar4->origin_y - *(float *)((int)(ppVar4 + -1) + 0x24);
          fVar26 = SQRT(fVar18 * fVar18 + fVar26 * fVar26);
          if (20.0 < fVar26) {
            fVar26 = 20.0;
          }
          (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(ppVar4 + -1) + 0x1c));
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,3);
          fVar20 = 1.0;
          fVar19 = 1.0;
          pIVar3 = grim_interface_ptr->vtable;
          fVar18 = 1.0;
LAB_00424475:
          (*pIVar3->grim_set_color)(fVar18,fVar19,fVar20,fVar17);
          fVar18 = fVar26 * 0.5;
          pIVar3 = grim_interface_ptr->vtable;
          goto LAB_00424257;
        }
      }
      else if (pVar1 == PROJECTILE_TYPE_BLADE_GUN) {
        if ((ppVar4->vy).life_timer == 0.4) {
          fVar26 = *(float *)((int)(ppVar4 + -1) + 0x28) - *(float *)((int)(ppVar4 + -1) + 0x20);
          fVar18 = ppVar4->origin_y - *(float *)((int)(ppVar4 + -1) + 0x24);
          fVar26 = SQRT(fVar18 * fVar18 + fVar26 * fVar26);
          if (20.0 < fVar26) {
            fVar26 = 20.0;
          }
          (*grim_interface_ptr->vtable->grim_set_rotation)
                    ((float)(int)fVar27 * 0.1 - (float)quest_spawn_timeline * 0.1);
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,6);
          fVar20 = 0.8;
          fVar19 = 0.8;
          pIVar3 = grim_interface_ptr->vtable;
          fVar18 = 0.8;
          goto LAB_00424475;
        }
      }
      else if (((pVar1 == PROJECTILE_TYPE_ION_MINIGUN) || (pVar1 == PROJECTILE_TYPE_ION_RIFLE)) ||
              ((pVar1 == PROJECTILE_TYPE_ION_CANNON || (pVar1 == PROJECTILE_TYPE_FIRE_BULLETS)))) {
        if ((ppVar4->vy).life_timer == 0.4) {
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(2,2);
          player_aim_update_thunk();
          if ((ppVar4->vy).type_id == PROJECTILE_TYPE_FIRE_BULLETS) {
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.6,0.1,fVar17);
            fVar21 = in_stack_fffffe34;
          }
          else {
            (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.6,1.0,fVar17);
            fVar21 = in_stack_fffffe34;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,2);
          fVar17 = fStack_194 * 16.0;
          fVar26 = camera_offset_x + *(float *)((int)(ppVar4 + -1) + 0x28);
          fVar18 = camera_offset_y + ppVar4->origin_y;
          if (fStack_190 <= 256.0) {
            fVar19 = 0.0;
            fStack_120 = fStack_190;
          }
          else {
            fVar19 = fStack_190 - 256.0;
            fStack_120 = 256.0;
          }
          fVar23 = fStack_194 * 3.1;
          if (9.0 < fVar23) {
            fVar23 = 9.0;
          }
          fVar28 = fVar19;
          if (fVar19 < fStack_190) {
            fVar20 = fStack_194 * 32.0;
            do {
              if ((ppVar4->vy).type_id == PROJECTILE_TYPE_FIRE_BULLETS) {
                (*grim_interface_ptr->vtable->grim_set_color)
                          (1.0,0.6,0.1,((fVar28 - fVar19) / fStack_120) * fStack_54);
              }
              else {
                (*grim_interface_ptr->vtable->grim_set_color)
                          (0.5,0.6,1.0,((fVar28 - fVar19) / fStack_120) * fStack_54);
              }
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        (fVar30 * fVar28 + (fVar26 - fVar17),unaff_EDI * fVar28 + (fVar18 - fVar17),
                         fVar20,fVar20);
              fVar28 = fVar23 + fVar28;
            } while (fVar28 < fStack_190);
          }
          fVar26 = fVar21;
          (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)fVar21 + 4));
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,0.7,fStack_54);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + *(float *)((int)fVar21 + 8)) - fVar17,
                     (camera_offset_y + *(float *)((int)fVar21 + 0xc)) - fVar17,fStack_194 * 32.0,
                     fStack_194 * 32.0);
          fVar17 = fStack_54;
        }
        else {
          (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(ppVar4 + -1) + 0x1c));
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,2);
          player_aim_update_thunk();
          pVar1 = (ppVar4->vy).type_id;
          if (pVar1 == PROJECTILE_TYPE_ION_MINIGUN) {
            fStack_194 = 1.05;
          }
          else if (pVar1 == PROJECTILE_TYPE_ION_RIFLE) {
            fStack_194 = 2.2;
          }
          else {
            fStack_194 = 0.8;
            if (pVar1 != PROJECTILE_TYPE_FIRE_BULLETS) {
              fStack_194 = 3.5;
            }
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,2);
          fVar17 = fStack_194 * 16.0;
          fVar18 = (camera_offset_x + *(float *)((int)(ppVar4 + -1) + 0x28)) - fVar17;
          fVar21 = camera_offset_y + ppVar4->origin_y;
          if (fStack_190 <= 256.0) {
            fVar26 = 0.0;
            fStack_118 = fStack_190;
          }
          else {
            fVar26 = fStack_190 - 256.0;
            fStack_118 = 256.0;
          }
          fVar19 = fStack_194 * 3.1;
          if (9.0 < fVar19) {
            fVar19 = 9.0;
          }
          if (fVar26 < fStack_190) {
            fVar20 = fStack_194 * 32.0;
            fVar22 = fVar26;
            do {
              if ((ppVar4->vy).type_id == PROJECTILE_TYPE_FIRE_BULLETS) {
                (*grim_interface_ptr->vtable->grim_set_color)
                          (1.0,0.6,0.1,((fVar22 - fVar26) / fStack_118) * fVar23 * fStack_54);
              }
              else {
                (*grim_interface_ptr->vtable->grim_set_color)
                          (0.5,0.6,1.0,((fVar22 - fVar26) / fStack_118) * fVar23 * fStack_54);
              }
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        (fVar22 * fVar30 + fVar18,fVar22 * unaff_EDI + (fVar21 - fVar17),fVar20,
                         fVar20);
              fVar22 = fVar19 + fVar22;
            } while (fVar22 < fStack_190);
          }
          fVar17 = fVar23 * fStack_54;
          (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.6,1.0,fVar17);
          pfVar8 = (float *)((int)in_stack_fffffe34 + 8);
          fVar21 = in_stack_fffffe34;
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + *pfVar8) - 16.0,
                     (camera_offset_y + *(float *)((int)in_stack_fffffe34 + 0xc)) - 16.0,32.0,32.0)
          ;
          (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.6,1.0,fVar17);
          fStack_190 = fStack_194 * in_stack_fffffe10 * 40.0;
          fVar17 = fStack_54;
          fVar26 = fVar21;
          if (*(int *)((int)in_stack_fffffe34 + 0x20) != 0x2d) {
            iVar10 = creature_find_in_radius(pfVar8,fStack_190,1);
            fVar17 = fVar28;
            while (fVar28 = fVar17, fVar17 = fStack_54, fVar26 = fVar21, iVar10 != -1) {
              (*grim_interface_ptr->vtable->grim_set_uv_point)(0,0.625,0.0);
              (*grim_interface_ptr->vtable->grim_set_uv_point)(1,0.625,0.25);
              (*grim_interface_ptr->vtable->grim_set_uv_point)(2,0.625,0.25);
              (*grim_interface_ptr->vtable->grim_set_uv_point)(3,0.625,0.0);
              player_aim_update_thunk();
              fVar17 = -fVar29;
              fStack_150 = camera_offset_x + *pfVar8;
              unaff_EDI = camera_offset_y + *(float *)((int)in_stack_fffffe34 + 0xc);
              fVar29 = fVar17 * fVar24;
              fStack_c4 = fVar24 * fVar28;
              fVar27 = fStack_150 - fVar29 * 10.0;
              fVar20 = unaff_EDI - fStack_c4 * 10.0;
              fVar30 = fStack_150 + fVar29 * 10.0;
              unaff_EDI = fStack_c4 * 10.0 + unaff_EDI;
              fVar26 = camera_offset_x + (&creature_pool)[iVar10].pos_x;
              fVar22 = camera_offset_y + (&creature_pool)[iVar10].pos_y;
              fVar19 = fVar29 * 10.0 + fVar26;
              fVar21 = fStack_c4 * 10.0 + fVar22;
              fVar26 = fVar26 - fVar29 * 10.0;
              fVar22 = fVar22 - fStack_c4 * 10.0;
              (*grim_interface_ptr->vtable->grim_draw_quad_points)
                        (fVar27,fVar20,fVar30,unaff_EDI,fVar19,fVar21,fVar26,fVar22);
              fVar29 = fVar17 * fVar24;
              fStack_ec = fVar28 * fVar24;
              fVar21 = fStack_ec * 4.0 + fVar21;
              fVar27 = fVar27 - fVar29 * 4.0;
              fVar30 = fVar30 + fVar29 * 4.0;
              unaff_EDI = fStack_ec * 4.0 + unaff_EDI;
              (*grim_interface_ptr->vtable->grim_draw_quad_points)
                        (fVar27,fVar20 - fStack_ec * 4.0,fVar30,unaff_EDI,fVar19 + fVar29 * 4.0,
                         fVar21,fVar26 - fVar29 * 4.0,fVar22 - fStack_ec * 4.0);
              (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,2);
              (*grim_interface_ptr->vtable->grim_draw_quad)
                        ((camera_offset_x + (&creature_pool)[iVar10].pos_x) - fVar18,
                         (camera_offset_y + (&creature_pool)[iVar10].pos_y) - fVar18,fVar23,fVar23)
              ;
              iVar10 = creature_find_in_radius(pfVar8,fStack_198,iVar10 + 1);
              fVar29 = fVar28;
            }
          }
        }
      }
    }
    ppVar4 = (projectile_tail_t *)((int)(ppVar4 + 1) + 0x14);
    fVar27 = (float)((int)fVar27 + 1);
    in_stack_fffffe34 = fVar26;
  } while ((int)ppVar4 < 0x493ecc);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  iVar10 = 0;
  ppVar7 = &projectile_pool[0].pos;
  do {
    if ((*(char *)((int)(ppVar7 + -1) + 0x28) != '\0') &&
       ((ppVar7->tail).vy.type_id == PROJECTILE_TYPE_PLAGUE_SPREADER)) {
      if ((ppVar7->tail).vy.life_timer == 0.4) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar17);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 30.0,
                   (camera_offset_y + ppVar7->pos_y) - 30.0,60.0,60.0);
        fVar11 = (float10)*(float *)((int)(ppVar7 + -1) + 0x2c) + (float10)1.5707964;
        fVar12 = (float10)fsin(fVar11);
        fVar11 = (float10)fcos(fVar11);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)((((float10)camera_offset_x +
                            (float10)*(float *)((int)(ppVar7 + -1) + 0x30)) - (float10)30.0) +
                          fVar11 * (float10)15.0),
                   (float)((((float10)camera_offset_y + (float10)ppVar7->pos_y) - (float10)30.0) +
                          fVar12 * (float10)15.0),60.0,60.0);
        fVar30 = (float)((float10)iVar10 + (float10)fStack_150);
        fVar11 = (float10)fcos((float10)iVar10 + (float10)fStack_150);
        fVar12 = (float10)fsin((float10)fVar30);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)(fVar11 * fVar11 +
                          (((float10)camera_offset_x +
                           (float10)*(float *)((int)(ppVar7 + -1) + 0x30)) - (float10)31.0)),
                   (float)((((float10)camera_offset_y + (float10)ppVar7->pos_y) - (float10)31.0) +
                          fVar12 * (float10)11.0),52.0,52.0);
        fVar11 = (float10)fsin((float10)fVar30 + (float10)2.0943952);
        fVar28 = (float)fVar11;
        fVar11 = (float10)fcos((float10)fVar30 + (float10)2.0943952);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)((((float10)camera_offset_x +
                            (float10)*(float *)((int)(ppVar7 + -1) + 0x30)) - (float10)31.0) +
                          fVar11 * (float10)10.0),
                   fVar28 * 10.0 + ((camera_offset_y + ppVar7->pos_y) - 31.0),62.0,62.0);
        fVar11 = (float10)fsin((float10)fVar30 + (float10)4.1887903);
        fVar12 = (float10)fcos((float10)fVar30 + (float10)4.1887903);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)((((float10)camera_offset_x +
                            (float10)*(float *)((int)(ppVar7 + -1) + 0x30)) - (float10)31.0) +
                          fVar12 * (float10)10.0),
                   (float)((((float10)camera_offset_y + (float10)ppVar7->pos_y) - (float10)31.0) +
                          fVar11 * (float10)fVar28),62.0,62.0);
      }
      else {
        fVar30 = (ppVar7->tail).vy.life_timer * 2.5;
        if (fVar30 <= 1.0) {
          if (fVar30 < 0.0) {
            fVar30 = 0.0;
          }
        }
        else {
          fVar30 = 1.0;
        }
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar30 * fStack_74);
        fVar28 = fVar30 * 40.0 + 32.0;
        fVar30 = fVar30 * 20.0 + 16.0;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - fVar30,
                   (camera_offset_y + ppVar7->pos_y) - fVar30,fVar28,fVar28);
      }
    }
    ppVar7 = (projectile_pos_y_block_t *)((int)(ppVar7 + 1) + 0xc);
    iVar10 = iVar10 + 1;
  } while ((int)ppVar7 < 0x493ec4);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
  effect_select_texture(0xd);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar17);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  ppVar6 = projectile_pool;
  do {
    if (((ppVar6->active != '\0') && (*(int *)((int)fVar21 + 0x20) == 0x2d)) &&
       ((ppVar6->pos).tail.vy.life_timer == 0.4)) {
      (*grim_interface_ptr->vtable->grim_set_rotation)(ppVar6->angle);
      (*grim_interface_ptr->vtable->grim_draw_quad)
                ((camera_offset_x + ppVar6->pos_x) - 32.0,
                 (camera_offset_y + (ppVar6->pos).pos_y) - 32.0,64.0,64.0);
    }
    ppVar6 = ppVar6 + 1;
  } while ((int)ppVar6 < 0x493eb8);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  fVar30 = fStack_c4 * 0.9;
  (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,fVar30);
  (*grim_interface_ptr->vtable->grim_bind_texture)(projectile_bullet_texture,0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  ppVar7 = &projectile_pool[0].pos;
  do {
    if (((*(char *)((int)(ppVar7 + -1) + 0x28) != '\0') && ((ppVar7->tail).vy.life_timer == 0.4)) &&
       ((pVar1 = (ppVar7->tail).vy.type_id, pVar1 != PROJECTILE_TYPE_PLASMA_RIFLE &&
        ((pVar1 != PROJECTILE_TYPE_PLASMA_MINIGUN && (pVar1 != PROJECTILE_TYPE_PULSE_GUN)))))) {
      (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(ppVar7 + -1) + 0x2c));
      pVar1 = (ppVar7->tail).vy.type_id;
      if (pVar1 == PROJECTILE_TYPE_PISTOL) {
        fVar24 = 6.0;
        fVar23 = 6.0;
        pIVar3 = grim_interface_ptr->vtable;
        fVar29 = (camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30)) - 3.0;
        fVar28 = (camera_offset_y + ppVar7->pos_y) - 3.0;
      }
      else {
        fVar29 = camera_offset_x + *(float *)((int)(ppVar7 + -1) + 0x30);
        fVar28 = camera_offset_y + ppVar7->pos_y;
        if (pVar1 == 4) {
          fVar24 = 8.0;
          fVar29 = fVar29 - 4.0;
          pIVar3 = grim_interface_ptr->vtable;
          fVar23 = 8.0;
          fVar28 = fVar28 - 4.0;
        }
        else {
          fVar24 = 4.0;
          fVar29 = fVar29 - 2.0;
          pIVar3 = grim_interface_ptr->vtable;
          fVar23 = 4.0;
          fVar28 = fVar28 - 2.0;
        }
      }
      (*pIVar3->grim_draw_quad)(fVar29,fVar28,fVar23,fVar24);
    }
    ppVar7 = (projectile_pos_y_block_t *)((int)(ppVar7 + 1) + 0xc);
  } while ((int)ppVar7 < 0x493ec4);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  if (config_blob.reserved0[0x10] != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
    effect_select_texture(0xd);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    pfVar8 = &secondary_projectile_pool[0].angle;
    do {
      if (((secondary_projectile_t *)(pfVar8 + -1))->active != '\0') {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_ec * 0.48);
        fVar11 = (float10)fcos((float10)*pfVar8 - (float10)1.5707964);
        fVar12 = (float10)fsin((float10)*pfVar8 - (float10)1.5707964);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  (((camera_offset_x + pfVar8[2]) - (float)fVar11 * 5.0) - 70.0,
                   (float)(((float10)(camera_offset_y +
                                     ((secondary_projectile_pos_y_block_t *)(pfVar8 + 3))->pos_y) -
                           fVar12 * (float10)5.0) - (float10)70.0),140.0,140.0);
      }
      pfVar8 = pfVar8 + 0xb;
    } while ((int)pfVar8 < 0x4965dc);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,fVar30);
  (*grim_interface_ptr->vtable->grim_bind_texture)(projectile_texture,0);
  (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,3);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  psVar9 = &secondary_projectile_pool[0].pos;
  do {
    if ((*(char *)((int)(psVar9 + -1) + 0xc) != '\0') &&
       ((psVar9->vx).vy.type_id != SECONDARY_PROJECTILE_TYPE_EXPLODING)) {
      (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)((int)(psVar9 + -1) + 0x10));
      sVar2 = (psVar9->vx).vy.type_id;
      if (sVar2 == SECONDARY_PROJECTILE_TYPE_ROCKET) {
        fVar29 = (camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) - 7.0;
        fVar28 = (camera_offset_y + psVar9->pos_y) - 7.0;
        (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,fVar30);
        fVar24 = 14.0;
        fVar23 = 14.0;
        pIVar3 = grim_interface_ptr->vtable;
LAB_00425a07:
        (*pIVar3->grim_draw_quad)(fVar29,fVar28,fVar23,fVar24);
      }
      else if (sVar2 == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
        fVar29 = (camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) - 5.0;
        fVar28 = (camera_offset_y + psVar9->pos_y) - 5.0;
        (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,fVar30);
        (*grim_interface_ptr->vtable->grim_draw_quad)(fVar29,fVar28,10.0,10.0);
      }
      else if (sVar2 == SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN) {
        fVar29 = (camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) - 4.0;
        fVar28 = (camera_offset_y + psVar9->pos_y) - 4.0;
        (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,fVar30);
        fVar24 = 8.0;
        fVar23 = 8.0;
        pIVar3 = grim_interface_ptr->vtable;
        goto LAB_00425a07;
      }
    }
    psVar9 = (secondary_projectile_pos_y_block_t *)((int)(psVar9 + 1) + 0x10);
  } while ((int)psVar9 < 0x4965e8);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  if (config_blob.reserved0[0x10] != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
    effect_select_texture(0xd);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    psVar9 = &secondary_projectile_pool[0].pos;
    do {
      if (*(char *)((int)(psVar9 + -1) + 0xc) != '\0') {
        sVar2 = (psVar9->vx).vy.type_id;
        if (sVar2 == SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN) {
          (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,1.0,fStack_114 * 0.158);
          fVar11 = (float10)*(float *)((int)(psVar9 + -1) + 0x10) - (float10)1.5707964;
          fVar29 = 30.0;
          fVar28 = 30.0;
          fVar12 = (float10)fcos(fVar11);
          pIVar3 = grim_interface_ptr->vtable;
          fVar11 = (float10)fsin(fVar11);
          fVar30 = ((camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) - (float)fVar12 * 9.0
                   ) - 15.0;
          fVar11 = ((float10)(camera_offset_y + psVar9->pos_y) - fVar11 * (float10)9.0) -
                   (float10)15.0;
LAB_00425d30:
          (*pIVar3->grim_draw_quad)(fVar30,(float)fVar11,fVar28,fVar29);
        }
        else if (sVar2 == SECONDARY_PROJECTILE_TYPE_ROCKET) {
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_114 * 0.68);
          fVar11 = (float10)*(float *)((int)(psVar9 + -1) + 0x10) - (float10)1.5707964;
          fVar12 = (float10)fcos(fVar11);
          fVar11 = (float10)fsin(fVar11);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    (((camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) -
                     (float)fVar12 * 9.0) - 30.0,
                     (float)(((float10)(camera_offset_y + psVar9->pos_y) - fVar11 * (float10)9.0) -
                            (float10)30.0),60.0,60.0);
        }
        else if (sVar2 == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_114 * 0.58);
          fVar11 = (float10)*(float *)((int)(psVar9 + -1) + 0x10) - (float10)1.5707964;
          fVar29 = 40.0;
          fVar28 = 40.0;
          fVar12 = (float10)fcos(fVar11);
          pIVar3 = grim_interface_ptr->vtable;
          fVar11 = (float10)fsin(fVar11);
          fVar30 = ((camera_offset_x + *(float *)((int)(psVar9 + -1) + 0x18)) - (float)fVar12 * 9.0
                   ) - 20.0;
          fVar11 = ((float10)(camera_offset_y + psVar9->pos_y) - fVar11 * (float10)9.0) -
                   (float10)20.0;
          goto LAB_00425d30;
        }
      }
      psVar9 = (secondary_projectile_pos_y_block_t *)((int)(psVar9 + 1) + 0x10);
    } while ((int)psVar9 < 0x4965e8);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  }
  return;
}


