/* fx_queue_add @ 0041e840 */

/* pushes a quad entry into fx_queue_ground_pool (capped at 0x80); returns 1 on success */

int __cdecl fx_queue_add(int effect_id,float *pos,float w,float h,float rotation,float *rgba)

{
  fx_queue_entry_t *pfVar1;
  int iVar2;
  int iVar3;
  uint3 uVar4;
  int iVar5;
  
  iVar2 = fx_queue_count;
  iVar3 = fx_queue_count * 0x28;
  iVar5 = fx_queue_count + 1;
  (&fx_queue)[fx_queue_count].pos_x = *pos;
  (&fx_queue)[fx_queue_count].pos_y = pos[1];
  (&fx_queue)[fx_queue_count].color_r = *rgba;
  (&fx_queue)[fx_queue_count].color_g = rgba[1];
  (&fx_queue)[fx_queue_count].color_b = rgba[2];
  pfVar1 = &fx_queue + fx_queue_count;
  fx_queue_count = iVar5;
  pfVar1->color_a = rgba[3];
  (&fx_queue)[iVar2].width = w;
  (&fx_queue)[iVar2].height = h;
  (&fx_queue)[iVar2].rotation = rotation;
  (&fx_queue)[iVar2].effect_id = effect_id;
  uVar4 = (uint3)((uint)iVar3 >> 8);
  if (0x7f < iVar5) {
    fx_queue_count = 0x7f;
    return (uint)uVar4 << 8;
  }
  return CONCAT31(uVar4,1);
}



/* fx_spawn_sprite @ 0041fbb0 */

/* spawns a sprite effect entry in DAT_00496820 */

int __cdecl fx_spawn_sprite(float *pos,float *vel,float scale)

{
  sprite_effect_t *psVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  psVar1 = &sprite_effect_pool;
  do {
    if ((char)psVar1->active == '\0') goto LAB_0041fbd8;
    psVar1 = psVar1 + 1;
    iVar3 = iVar3 + 1;
  } while ((int)psVar1 < 0x49aa20);
  iVar3 = crt_rand();
  iVar3 = iVar3 % 0x180;
LAB_0041fbd8:
  *(undefined1 *)&(&sprite_effect_pool)[iVar3].active = 1;
  (&sprite_effect_pool)[iVar3].color_b = 1.0;
  (&sprite_effect_pool)[iVar3].color_g = 1.0;
  (&sprite_effect_pool)[iVar3].color_r = 1.0;
  (&sprite_effect_pool)[iVar3].color_a = 1.0;
  (&sprite_effect_pool)[iVar3].pos_x = *pos;
  (&sprite_effect_pool)[iVar3].pos_y = pos[1];
  (&sprite_effect_pool)[iVar3].vel_x = *vel;
  (&sprite_effect_pool)[iVar3].vel_y = vel[1];
  (&sprite_effect_pool)[iVar3].scale = scale;
  iVar2 = crt_rand();
  (&sprite_effect_pool)[iVar3].rotation = (float)(iVar2 % 0x274) * 0.01;
  return iVar3;
}



/* effect_uv_tables_init @ 0041fed0 */

/* precomputes UV grids for 2x2, 4x4, 8x8, 16x16 effect atlases */

void effect_uv_tables_init(void)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float *pfVar4;
  float *pfVar5;
  int local_8;
  int local_4;
  
  local_8 = 0;
  puVar2 = &effect_uv_16x16_table;
  do {
    fVar1 = (float)local_8;
    puVar3 = puVar2 + 2;
    local_8 = local_8 + 1;
    puVar2[-1] = fVar1 * 0.0625;
    *puVar2 = 0;
    puVar2 = puVar3;
  } while ((int)puVar3 < 0x491004);
  local_4 = 0;
  pfVar5 = &effect_uv2.v;
  do {
    local_8 = 0;
    pfVar4 = pfVar5;
    do {
      fVar1 = (float)local_8;
      local_8 = local_8 + 1;
      ((uv2f_t *)(pfVar4 + -1))->u = fVar1 * 0.5;
      *pfVar4 = (float)local_4 * 0.5;
      pfVar4 = pfVar4 + 2;
    } while (local_8 < 2);
    local_4 = local_4 + 1;
    pfVar5 = pfVar5 + 4;
  } while (local_4 < 2);
  local_4 = 0;
  pfVar5 = &effect_uv4.v;
  do {
    local_8 = 0;
    pfVar4 = pfVar5;
    do {
      fVar1 = (float)local_8;
      local_8 = local_8 + 1;
      ((uv2f_t *)(pfVar4 + -1))->u = fVar1 * 0.25;
      *pfVar4 = (float)local_4 * 0.25;
      pfVar4 = pfVar4 + 2;
    } while (local_8 < 4);
    local_4 = local_4 + 1;
    pfVar5 = pfVar5 + 8;
  } while (local_4 < 4);
  local_4 = 0;
  pfVar5 = &effect_uv8.v;
  do {
    local_8 = 0;
    pfVar4 = pfVar5;
    do {
      fVar1 = (float)local_8;
      local_8 = local_8 + 1;
      ((uv2f_t *)(pfVar4 + -1))->u = fVar1 * 0.125;
      *pfVar4 = (float)local_4 * 0.125;
      pfVar4 = pfVar4 + 2;
    } while (local_8 < 8);
    local_4 = local_4 + 1;
    pfVar5 = pfVar5 + 0x10;
  } while (local_4 < 8);
  local_4 = 0;
  pfVar5 = &effect_uv16.v;
  do {
    local_8 = 0;
    pfVar4 = pfVar5;
    do {
      fVar1 = (float)local_8;
      local_8 = local_8 + 1;
      ((uv2f_t *)(pfVar4 + -1))->u = fVar1 * 0.0625;
      *pfVar4 = (float)local_4 * 0.0625;
      pfVar4 = pfVar4 + 2;
    } while (local_8 < 0x10);
    local_4 = local_4 + 1;
    pfVar5 = pfVar5 + 0x20;
  } while (local_4 < 0x10);
  return;
}



/* fx_spawn_particle @ 00420130 */

/* spawns a fast particle entry in crt_ctype_table_base */

int __cdecl fx_spawn_particle(float *pos,float angle,void *unused,float intensity)

{
  particle_t *ppVar1;
  int iVar2;
  uint uVar3;
  float10 fVar4;
  
  ppVar1 = &particle_pool;
  uVar3 = 0;
  do {
    if (ppVar1->active == '\0') goto LAB_00420160;
    ppVar1 = ppVar1 + 1;
    uVar3 = uVar3 + 1;
  } while ((int)ppVar1 < 0x495ab8);
  uVar3 = crt_rand();
  uVar3 = uVar3 & 0x8000007f;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xffffff80) + 1;
  }
LAB_00420160:
  fVar4 = (float10)fcos((float10)angle);
  (&particle_pool)[uVar3].active = '\x01';
  (&particle_pool)[uVar3].pos_x = *pos;
  (&particle_pool)[uVar3].pos_y = pos[1];
  (&particle_pool)[uVar3].vel_x = (float)(fVar4 * (float10)90.0);
  fVar4 = (float10)fsin((float10)angle);
  (&particle_pool)[uVar3].vel_y = (float)(fVar4 * (float10)90.0);
  (&particle_pool)[uVar3].intensity = intensity;
  (&particle_pool)[uVar3].scale_x = 1.0;
  (&particle_pool)[uVar3].scale_y = 1.0;
  (&particle_pool)[uVar3].scale_z = 1.0;
  (&particle_pool)[uVar3].age = 0.0;
  (&particle_pool)[uVar3].angle = angle;
  iVar2 = crt_rand();
  (&particle_pool)[uVar3].spin = (float)(iVar2 % 0x274) * 0.01;
  (&particle_pool)[uVar3].render_flag = '\x01';
  *(undefined1 *)&(&particle_pool)[uVar3].style_id = 0;
  return uVar3;
}



/* fx_spawn_particle_slow @ 00420240 */

/* spawns a slow particle entry in crt_ctype_table_base */

int __cdecl fx_spawn_particle_slow(float *pos,float angle)

{
  particle_t *ppVar1;
  int iVar2;
  uint uVar3;
  float10 fVar4;
  
  ppVar1 = &particle_pool;
  uVar3 = 0;
  do {
    if (ppVar1->active == '\0') goto LAB_00420270;
    ppVar1 = ppVar1 + 1;
    uVar3 = uVar3 + 1;
  } while ((int)ppVar1 < 0x495ab8);
  uVar3 = crt_rand();
  uVar3 = uVar3 & 0x8000007f;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xffffff80) + 1;
  }
LAB_00420270:
  fVar4 = (float10)fcos((float10)angle);
  (&particle_pool)[uVar3].active = '\x01';
  (&particle_pool)[uVar3].pos_x = *pos;
  (&particle_pool)[uVar3].pos_y = pos[1];
  (&particle_pool)[uVar3].vel_x = (float)(fVar4 * (float10)30.0);
  fVar4 = (float10)fsin((float10)angle);
  (&particle_pool)[uVar3].vel_y = (float)(fVar4 * (float10)30.0);
  (&particle_pool)[uVar3].intensity = 1.0;
  (&particle_pool)[uVar3].scale_x = 1.0;
  (&particle_pool)[uVar3].scale_y = 1.0;
  (&particle_pool)[uVar3].scale_z = 1.0;
  (&particle_pool)[uVar3].age = 0.0;
  (&particle_pool)[uVar3].angle = angle;
  iVar2 = crt_rand();
  (&particle_pool)[uVar3].spin = (float)(iVar2 % 0x274) * 0.01;
  (&particle_pool)[uVar3].render_flag = '\x01';
  *(undefined1 *)&(&particle_pool)[uVar3].style_id = 8;
  (&particle_pool)[uVar3].target_id = -1;
  return uVar3;
}



/* fx_spawn_secondary_projectile @ 00420360 */

/* spawns a typed entry in DAT_00495ad8 (secondary projectile pool) */

int __cdecl
fx_spawn_secondary_projectile(float *pos,float angle,secondary_projectile_type_id_t type_id)

{
  secondary_projectile_t *psVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  
  iVar3 = 0;
  psVar1 = secondary_projectile_pool;
  do {
    if (psVar1->active == '\0') goto LAB_0042037f;
    psVar1 = psVar1 + 1;
    iVar3 = iVar3 + 1;
  } while ((int)psVar1 < 0x4965d8);
  iVar3 = 0x3f;
LAB_0042037f:
  highscore_active_record.shots_fired = highscore_active_record.shots_fired + 1;
  fVar4 = (float10)fcos((float10)angle - (float10)1.5707964);
  secondary_projectile_pool[iVar3].active = '\x01';
  secondary_projectile_pool[iVar3].pos_x = *pos;
  secondary_projectile_pool[iVar3].pos.pos_y = pos[1];
  secondary_projectile_pool[iVar3].life_timer = 2.0;
  secondary_projectile_pool[iVar3].angle = angle;
  secondary_projectile_pool[iVar3].pos.vx.vy.trail_timer = 0.0;
  secondary_projectile_pool[iVar3].pos.vx.vy.type_id = type_id;
  secondary_projectile_pool[iVar3].pos.vx.vel_x = (float)(fVar4 * (float10)90.0);
  fVar5 = (float10)fsin((float10)angle - (float10)1.5707964);
  secondary_projectile_pool[iVar3].pos.vx.vy.vel_y = (float)(fVar5 * (float10)90.0);
  if (type_id == SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET) {
    iVar2 = creature_find_nearest(&(&player_state_table)[render_overlay_player_index].aim_x,-1,0.0);
    secondary_projectile_pool[iVar3].pos.vx.vy.target_id = iVar2;
    secondary_projectile_pool[iVar3].pos.vx.vel_x = (float)fVar4 * 190.0;
    secondary_projectile_pool[iVar3].pos.vx.vy.vel_y = (float)fVar5 * 190.0;
  }
  return iVar3;
}



/* fx_queue_add_random @ 00427700 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* spawns a random fx_queue_add entry (effect ids 3..7) with grayscale color/size */

void __cdecl fx_queue_add_random(float *pos)

{
  uint uVar1;
  int iVar2;
  float *pos_00;
  float w;
  float h;
  float rotation;
  float *rgba;
  float local_8;
  float local_4;
  
  if (config_blob.fx_toggle == '\0') {
    if ((crt_mbcs_table & 1) == 0) {
      crt_mbcs_table = crt_mbcs_table | 1;
      fx_queue_random_color_r = 0.9;
      fx_queue_random_color_g = 0.9;
      fx_queue_random_color_b = 0.9;
      fx_queue_random_color_a = 0x3f47ae14;
      crt_atexit(&DAT_00427830);
    }
    uVar1 = crt_rand();
    fx_queue_random_color_r = (float)(uVar1 & 0xf) * 0.01 + 0.84;
    fx_queue_random_color_g = fx_queue_random_color_r;
    fx_queue_random_color_b = fx_queue_random_color_r;
    iVar2 = crt_rand();
    w = (float)(iVar2 % 0x18 + -0xc) + 30.0;
    iVar2 = crt_rand();
    rgba = (float *)&fx_queue_random_color_r;
    rotation = (float)(iVar2 % 0x274) * 0.01;
    local_8 = *pos - w * 0.5;
    local_4 = pos[1] - w * 0.5;
    pos_00 = &local_8;
    h = w;
    iVar2 = crt_rand();
    fx_queue_add(iVar2 % 5 + 3,pos_00,w,h,rotation,rgba);
  }
  return;
}



/* fx_queue_add_rotated @ 00427840 */

/* pushes a rotated sprite into fx_queue_rotated_pool (capped at 0x40); returns 1 on success */

int __cdecl fx_queue_add_rotated(float *pos,float *rgba,float rotation,float scale,int effect_id)

{
  undefined4 in_EAX;
  float fVar1;
  uint3 uVar2;
  
  uVar2 = (uint3)((uint)in_EAX >> 8);
  fVar1 = (float)CONCAT31(uVar2,terrain_texture_failed);
  if (terrain_texture_failed == '\0') {
    if (fx_queue_rotated == 0x3f) {
      return (uint)uVar2 << 8;
    }
    (&fx_rotated_color_r)[fx_queue_rotated * 4] = *rgba;
    (&fx_rotated_color_g)[fx_queue_rotated * 4] = rgba[1];
    (&fx_rotated_color_b)[fx_queue_rotated * 4] = rgba[2];
    (&fx_rotated_color_a)[fx_queue_rotated * 4] = rgba[3];
    if (*(float *)((int)cv_terrainBodiesTransparency + 0xc) == 0.0) {
      fVar1 = (float)(&fx_rotated_color_a)[fx_queue_rotated * 4] * 0.8;
    }
    else {
      fVar1 = (1.0 / *(float *)((int)cv_terrainBodiesTransparency + 0xc)) *
              (float)(&fx_rotated_color_a)[fx_queue_rotated * 4];
    }
    (&fx_rotated_color_a)[fx_queue_rotated * 4] = fVar1;
    (&fx_rotated_rotation)[fx_queue_rotated] = rotation;
    (&fx_rotated_effect_id)[fx_queue_rotated] = effect_id;
    (&fx_rotated_scale)[fx_queue_rotated] = scale;
    (&fx_rotated_pos_x)[fx_queue_rotated * 2] = *pos;
    fVar1 = pos[1];
    (&fx_rotated_pos_y)[fx_queue_rotated * 2] = fVar1;
    fx_queue_rotated = fx_queue_rotated + 1;
    if (0x3f < fx_queue_rotated) {
      fx_queue_rotated = 0x3f;
    }
  }
  return CONCAT31((int3)((uint)fVar1 >> 8),1);
}



/* fx_queue_render @ 00427920 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* bakes FX queues (fx_queue_ground_pool/fx_queue_rotated_pool) into the ground render target (terrain_render_target)
   and clears them */

void fx_queue_render(void)

{
  int iVar1;
  float w;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  float fVar5;
  
  fVar5 = 1.0 / (float)config_blob.reserved0._112_4_;
  if (terrain_texture_failed == '\0') {
    if ((fx_queue_rotated != 0) || (fx_queue_count != 0)) {
      (*grim_interface_ptr->vtable->grim_set_render_target)(terrain_render_target);
      (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
      if (0 < fx_queue_count) {
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
        iVar3 = 0;
        if (0 < fx_queue_count) {
          pfVar2 = &fx_queue.rotation;
          do {
            (*grim_interface_ptr->vtable->grim_set_color_ptr)(pfVar2 + 5);
            (*grim_interface_ptr->vtable->grim_set_rotation)(*pfVar2);
            effect_select_texture(((fx_queue_entry_t *)(pfVar2 + -1))->effect_id);
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((pfVar2[1] - pfVar2[4] * 0.5) * fVar5,(pfVar2[2] - pfVar2[3] * 0.5) * fVar5,
                       fVar5 * pfVar2[4],fVar5 * pfVar2[3]);
            iVar3 = iVar3 + 1;
            pfVar2 = pfVar2 + 10;
          } while (iVar3 < fx_queue_count);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
      }
      if (0 < fx_queue_rotated) {
        (*grim_interface_ptr->vtable->grim_bind_texture)(bodyset_texture,0);
        fVar5 = 2.66247e-44;
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        iVar3 = 0;
        if (0 < fx_queue_rotated) {
          pfVar2 = (float *)&fx_rotated_pos_x;
          pfVar4 = (float *)&fx_rotated_color_b;
          do {
            iVar1 = (&creature_type_table)[(&fx_rotated_effect_id)[iVar3]].corpse_frame;
            render_scratch_f0 = (&effect_uv4)[iVar1].u;
            render_scratch_f1 = (&effect_uv4)[iVar1].v;
            render_scratch_f2 = (&effect_uv4)[iVar1].u + 0.25;
            render_scratch_f3 = (&effect_uv4)[iVar1].v + 0.25;
            (*grim_interface_ptr->vtable->grim_set_uv)
                      (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
            (*grim_interface_ptr->vtable->grim_set_color)
                      (pfVar4[-2],pfVar4[-1],*pfVar4,pfVar4[1] * 0.5);
            (*grim_interface_ptr->vtable->grim_set_rotation)
                      ((float)(&fx_rotated_rotation)[iVar3] - 1.5707964);
            render_scratch_f0 = *pfVar2 - 0.5;
            render_scratch_f1 = pfVar2[1] - 0.5;
            w = (float)(&fx_rotated_scale)[iVar3] * 6.106354e-39 * 1.064;
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      (render_scratch_f0 * 6.106354e-39 - fVar5,
                       render_scratch_f1 * 6.106354e-39 - fVar5,w,w);
            iVar3 = iVar3 + 1;
            pfVar4 = pfVar4 + 4;
            pfVar2 = pfVar2 + 2;
          } while (iVar3 < fx_queue_rotated);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
        fVar5 = 2.66247e-44;
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        iVar3 = 0;
        if (0 < fx_queue_rotated) {
          pfVar2 = (float *)&fx_rotated_pos_x;
          pfVar4 = (float *)&fx_rotated_color_b;
          do {
            iVar1 = (&creature_type_table)[(&fx_rotated_effect_id)[iVar3]].corpse_frame;
            render_scratch_f0 = (&effect_uv4)[iVar1].u;
            render_scratch_f1 = (&effect_uv4)[iVar1].v;
            render_scratch_f2 = (&effect_uv4)[iVar1].u + 0.25;
            render_scratch_f3 = (&effect_uv4)[iVar1].v + 0.25;
            (*grim_interface_ptr->vtable->grim_set_uv)
                      (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
            (*grim_interface_ptr->vtable->grim_set_color)(pfVar4[-2],pfVar4[-1],*pfVar4,pfVar4[1]);
            (*grim_interface_ptr->vtable->grim_set_rotation)
                      ((float)(&fx_rotated_rotation)[iVar3] - 1.5707964);
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      (*pfVar2 * 6.106968e-39 - fVar5,pfVar2[1] * 6.106968e-39 - fVar5,
                       (float)(&fx_rotated_scale)[iVar3] * 6.106968e-39,
                       (float)(&fx_rotated_scale)[iVar3] * 6.106968e-39);
            iVar3 = iVar3 + 1;
            pfVar4 = pfVar4 + 4;
            pfVar2 = pfVar2 + 2;
          } while (iVar3 < fx_queue_rotated);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
      }
      fx_queue_count = 0;
      fx_queue_rotated = 0;
      (*grim_interface_ptr->vtable->grim_set_render_target)(-1);
    }
  }
  else if (0 < fx_queue_rotated) {
    (*grim_interface_ptr->vtable->grim_bind_texture)(bodyset_texture,0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    if (0 < fx_queue_rotated) {
      pfVar2 = (float *)&fx_rotated_pos_x;
      pfVar4 = (float *)&fx_rotated_color_b;
      do {
        iVar1 = (&creature_type_table)[(&fx_rotated_effect_id)[iVar3]].corpse_frame;
        render_scratch_f0 = (&effect_uv4)[iVar1].u;
        render_scratch_f1 = (&effect_uv4)[iVar1].v;
        render_scratch_f2 = (&effect_uv4)[iVar1].u + 0.25;
        render_scratch_f3 = (&effect_uv4)[iVar1].v + 0.25;
        (*grim_interface_ptr->vtable->grim_set_uv)
                  (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
        (*grim_interface_ptr->vtable->grim_set_color)(pfVar4[-2],pfVar4[-1],*pfVar4,pfVar4[1] * 0.5)
        ;
        (*grim_interface_ptr->vtable->grim_set_rotation)
                  ((float)(&fx_rotated_rotation)[iVar3] - 1.5707964);
        render_scratch_f0 = *pfVar2 + 2.0;
        render_scratch_f1 = pfVar2[1] + 2.0;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  (render_scratch_f0 + camera_offset_x,render_scratch_f1 + camera_offset_y,
                   (float)(&fx_rotated_scale)[iVar3] * 1.04,(float)(&fx_rotated_scale)[iVar3] * 1.04
                  );
        iVar3 = iVar3 + 1;
        pfVar4 = pfVar4 + 4;
        pfVar2 = pfVar2 + 2;
      } while (iVar3 < fx_queue_rotated);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    if (0 < fx_queue_rotated) {
      pfVar2 = (float *)&fx_rotated_pos_x;
      pfVar4 = (float *)&fx_rotated_color_b;
      do {
        iVar1 = (&creature_type_table)[(&fx_rotated_effect_id)[iVar3]].corpse_frame;
        render_scratch_f0 = (&effect_uv4)[iVar1].u;
        render_scratch_f1 = (&effect_uv4)[iVar1].v;
        render_scratch_f2 = (&effect_uv4)[iVar1].u + 0.25;
        render_scratch_f3 = (&effect_uv4)[iVar1].v + 0.25;
        (*grim_interface_ptr->vtable->grim_set_uv)
                  (render_scratch_f0,render_scratch_f1,render_scratch_f2,render_scratch_f3);
        (*grim_interface_ptr->vtable->grim_set_color)(pfVar4[-2],pfVar4[-1],*pfVar4,pfVar4[1]);
        (*grim_interface_ptr->vtable->grim_set_rotation)
                  ((float)(&fx_rotated_rotation)[iVar3] - 1.5707964);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  (camera_offset_x + *pfVar2,camera_offset_y + pfVar2[1],
                   (float)(&fx_rotated_scale)[iVar3],(float)(&fx_rotated_scale)[iVar3]);
        iVar3 = iVar3 + 1;
        pfVar4 = pfVar4 + 4;
        pfVar2 = pfVar2 + 2;
      } while (iVar3 < fx_queue_rotated);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    return;
  }
  return;
}



/* effect_init_entry @ 0042de80 */

/* initializes an effect entry to default values */

void __cdecl effect_init_entry(void *entry)

{
  undefined4 *puVar1;
  int iVar2;
  
  *(undefined4 *)((int)entry + 0x2c) = 0;
  *(undefined4 *)((int)entry + 0x24) = 0;
  *(undefined4 *)((int)entry + 0x14) = 0;
  *(undefined4 *)((int)entry + 0x30) = 0x3f800000;
  *(undefined4 *)((int)entry + 0x34) = 0x3f800000;
  *(undefined4 *)((int)entry + 0x18) = 0x3f800000;
  *(undefined4 *)((int)entry + 0x38) = 0x3f800000;
  *(undefined4 *)((int)entry + 0x3c) = 0x3f800000;
  puVar1 = (undefined4 *)((int)entry + 0x50);
  iVar2 = 4;
  do {
    puVar1[2] = 0xffffffff;
    *puVar1 = 0x3f000000;
    puVar1[1] = 0x3f800000;
    puVar1 = puVar1 + 7;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



/* effect_defaults_reset @ 0042df10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* resets global effect template values */

void effect_defaults_reset(void)

{
  undefined4 *puVar1;
  
  effect_template_color_r = 0x3f800000;
  effect_template_color_g = 0x3f800000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f800000;
  _DAT_004ab1b0 = 0;
  effect_template_flags = 1;
  effect_template_rotation = 0;
  _effect_template_scale = 0x3f800000;
  effect_template_age = 0;
  effect_template_lifetime = 0x3f000000;
  effect_template_half_height = 0x42000000;
  effect_template_half_width = 0x42000000;
  _DAT_004ab1b4 = 0;
  effect_template_rotation_step = 0x3f800000;
  effect_template_scale_step = 0x3f800000;
  effect_template_vel_x = 0;
  effect_template_vel_y = 0;
  _DAT_004ab268 = 0;
  effect_pool_pos_x.quad_data[0x1c] = (float)&DAT_004ab3ec;
  effect_init_entry(&effect_pool_pos_x);
  puVar1 = &DAT_004ab4a4;
  do {
    *puVar1 = puVar1 + 1;
    effect_init_entry(puVar1 + -0x2e);
    puVar1 = puVar1 + 0x2f;
  } while ((int)puVar1 < 0x4c2b2c);
  _DAT_004c2a70 = &DAT_004c2a74;
  effect_init_entry(&DAT_004c29b8);
  effect_free_list_head = &effect_pool_pos_x;
  _DAT_004c2b34 = 0;
  return;
}



/* effect_free @ 0042e080 */

/* returns an effect entry to the free list */

void __cdecl effect_free(void *entry)

{
  *(void **)((int)entry + 0xb8) = effect_free_list_head;
  *(undefined4 *)((int)entry + 0x2c) = 0;
  effect_free_list_head = entry;
  return;
}



/* effect_select_texture @ 0042e0a0 */

/* selects effect texture page based on effect id */

void __cdecl effect_select_texture(int effect_id)

{
  int iVar1;
  int frame;
  
  iVar1 = (&effect_id_table)[effect_id].size_code;
  frame = (&effect_id_table)[effect_id].frame;
  if (iVar1 == 0x10) {
    (*grim_interface_ptr->vtable->grim_set_atlas_frame)(0x10,frame);
    return;
  }
  if (iVar1 == 0x20) {
    (*grim_interface_ptr->vtable->grim_set_atlas_frame)(8,frame);
    return;
  }
  if (iVar1 == 0x40) {
    (*grim_interface_ptr->vtable->grim_set_atlas_frame)(4,frame);
    return;
  }
  if (iVar1 == 0x80) {
    (*grim_interface_ptr->vtable->grim_set_atlas_frame)(2,frame);
  }
  return;
}



/* effect_spawn @ 0042e120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* allocates an effect entry and assigns quad UVs */

void * __cdecl effect_spawn(int effect_id,float *pos)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  
  if (config_blob.detail_preset < 3) {
    uVar4 = effect_spawn_skip_counter & 1;
    effect_spawn_skip_counter = effect_spawn_skip_counter + 1;
    if (uVar4 != 0) {
      return &effect_dummy_entry;
    }
  }
  iVar2 = (&effect_id_table)[effect_id].size_code;
  iVar3 = (&effect_id_table)[effect_id].frame;
  pfVar5 = effect_free_list_head;
  pfVar7 = (float *)effect_free_list_head[0x2e];
  if ((float *)effect_free_list_head[0x2e] == (float *)0x0) {
    pfVar5 = (float *)&effect_dummy_entry;
    pfVar7 = effect_free_list_head;
  }
  effect_free_list_head = pfVar7;
  pfVar7 = (float *)&effect_template_vel_x;
  pfVar8 = pfVar5 + 3;
  for (iVar6 = 0xf; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar8 = *pfVar7;
    pfVar7 = pfVar7 + 1;
    pfVar8 = pfVar8 + 1;
  }
  *pfVar5 = *pos;
  pfVar5[1] = pos[1];
  *(char *)(pfVar5 + 2) = (char)effect_id;
  if (iVar2 == 0x10) {
    pfVar5[0x17] = (&effect_uv16)[iVar3].u;
    pfVar5[0x18] = (&effect_uv16)[iVar3].v;
    fVar1 = -effect_template_half_height;
    pfVar5[0x12] = -effect_template_half_width;
    pfVar5[0x13] = fVar1;
    fVar1 = (&effect_uv16)[iVar3].v;
    pfVar5[0x1e] = effect_uv_step_16 + (&effect_uv16)[iVar3].u;
    pfVar5[0x1f] = fVar1;
    fVar1 = -effect_template_half_height;
    pfVar5[0x19] = effect_template_half_width;
    pfVar5[0x1a] = fVar1;
    fVar1 = effect_uv_step_16 + (&effect_uv16)[iVar3].v;
    pfVar5[0x25] = effect_uv_step_16 + (&effect_uv16)[iVar3].u;
    pfVar5[0x26] = fVar1;
    fVar1 = effect_template_half_height;
    pfVar5[0x20] = effect_template_half_width;
    pfVar5[0x21] = fVar1;
    fVar1 = effect_uv_step_16 + (&effect_uv16)[iVar3].v;
    pfVar5[0x2c] = (&effect_uv16)[iVar3].u;
    pfVar5[0x2d] = fVar1;
    fVar1 = effect_template_half_height;
    pfVar5[0x27] = -effect_template_half_width;
    pfVar5[0x28] = fVar1;
    return pfVar5;
  }
  if (iVar2 == 0x20) {
    pfVar5[0x17] = (&effect_uv8)[iVar3].u;
    pfVar5[0x18] = (&effect_uv8)[iVar3].v;
    fVar1 = -effect_template_half_height;
    pfVar5[0x12] = -effect_template_half_width;
    pfVar5[0x13] = fVar1;
    fVar1 = (&effect_uv8)[iVar3].v;
    pfVar5[0x1e] = effect_uv_step_8 + (&effect_uv8)[iVar3].u;
    pfVar5[0x1f] = fVar1;
    fVar1 = -effect_template_half_height;
    pfVar5[0x19] = effect_template_half_width;
    pfVar5[0x1a] = fVar1;
    fVar1 = effect_uv_step_8 + (&effect_uv8)[iVar3].v;
    pfVar5[0x25] = effect_uv_step_8 + (&effect_uv8)[iVar3].u;
    pfVar5[0x26] = fVar1;
    fVar1 = effect_template_half_height;
    pfVar5[0x20] = effect_template_half_width;
    pfVar5[0x21] = fVar1;
    fVar1 = effect_uv_step_8 + (&effect_uv8)[iVar3].v;
    pfVar5[0x2c] = (&effect_uv8)[iVar3].u;
    pfVar5[0x2d] = fVar1;
    fVar1 = effect_template_half_height;
    pfVar5[0x27] = -effect_template_half_width;
    pfVar5[0x28] = fVar1;
    return pfVar5;
  }
  if (iVar2 != 0x40) {
    if (iVar2 == 0x80) {
      pfVar5[0x17] = (&effect_uv2)[iVar3].u;
      pfVar5[0x18] = (&effect_uv2)[iVar3].v;
      fVar1 = -effect_template_half_height;
      pfVar5[0x12] = -effect_template_half_width;
      pfVar5[0x13] = fVar1;
      fVar1 = (&effect_uv2)[iVar3].v;
      pfVar5[0x1e] = effect_uv_step_2 + (&effect_uv2)[iVar3].u;
      pfVar5[0x1f] = fVar1;
      fVar1 = -effect_template_half_height;
      pfVar5[0x19] = effect_template_half_width;
      pfVar5[0x1a] = fVar1;
      fVar1 = effect_uv_step_2 + (&effect_uv2)[iVar3].v;
      pfVar5[0x25] = effect_uv_step_2 + (&effect_uv2)[iVar3].u;
      pfVar5[0x26] = fVar1;
      fVar1 = effect_template_half_height;
      pfVar5[0x20] = effect_template_half_width;
      pfVar5[0x21] = fVar1;
      fVar1 = effect_uv_step_2 + (&effect_uv2)[iVar3].v;
      pfVar5[0x2c] = (&effect_uv2)[iVar3].u;
      pfVar5[0x2d] = fVar1;
      fVar1 = effect_template_half_height;
      pfVar5[0x27] = -effect_template_half_width;
      pfVar5[0x28] = fVar1;
    }
    return pfVar5;
  }
  pfVar5[0x17] = (&effect_uv4)[iVar3].u;
  pfVar5[0x18] = (&effect_uv4)[iVar3].v;
  fVar1 = -effect_template_half_height;
  pfVar5[0x12] = -effect_template_half_width;
  pfVar5[0x13] = fVar1;
  fVar1 = (&effect_uv4)[iVar3].v;
  pfVar5[0x1e] = effect_uv_step_4 + (&effect_uv4)[iVar3].u;
  pfVar5[0x1f] = fVar1;
  fVar1 = -effect_template_half_height;
  pfVar5[0x19] = effect_template_half_width;
  pfVar5[0x1a] = fVar1;
  fVar1 = effect_uv_step_4 + (&effect_uv4)[iVar3].v;
  pfVar5[0x25] = effect_uv_step_4 + (&effect_uv4)[iVar3].u;
  pfVar5[0x26] = fVar1;
  fVar1 = effect_template_half_height;
  pfVar5[0x20] = effect_template_half_width;
  pfVar5[0x21] = fVar1;
  fVar1 = effect_uv_step_4 + (&effect_uv4)[iVar3].v;
  pfVar5[0x2c] = (&effect_uv4)[iVar3].u;
  pfVar5[0x2d] = fVar1;
  fVar1 = effect_template_half_height;
  pfVar5[0x27] = -effect_template_half_width;
  pfVar5[0x28] = fVar1;
  return pfVar5;
}



/* effects_update @ 0042e710 */

/* ticks active effects and frees expired entries */

void effects_update(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  
  pfVar4 = &effect_pool_pos_x.age;
  do {
    fVar1 = pfVar4[2];
    if (fVar1 != 0.0) {
      fVar2 = frame_dt + *pfVar4;
      *pfVar4 = fVar2;
      if (fVar2 < pfVar4[1]) {
        if (0.0 <= fVar2) {
          fVar3 = frame_dt * pfVar4[-5];
          ((effect_entry_t *)(pfVar4 + -9))->pos_x =
               frame_dt * pfVar4[-6] + ((effect_entry_t *)(pfVar4 + -9))->pos_x;
          pfVar4[-8] = fVar3 + pfVar4[-8];
          if (((uint)fVar1 & 4) != 0) {
            pfVar4[-4] = frame_dt * pfVar4[7] + pfVar4[-4];
          }
          if (((uint)fVar1 & 8) != 0) {
            pfVar4[-3] = frame_dt * pfVar4[8] + pfVar4[-3];
          }
          if (((uint)fVar1 & 0x10) != 0) {
            pfVar4[6] = 1.0 - fVar2 / pfVar4[1];
          }
        }
      }
      else {
        if (((uint)fVar1 & 0x80) != 0) {
          if (((uint)fVar1 & 0x100) == 0) {
            pfVar4[6] = 0.8;
          }
          else {
            pfVar4[6] = 0.35;
          }
          fx_queue_add((uint)*(byte *)(pfVar4 + -7),(float *)(pfVar4 + -9),pfVar4[-2] + pfVar4[-2],
                       pfVar4[-1] + pfVar4[-1],pfVar4[-4],pfVar4 + 3);
        }
        effect_free((effect_entry_t *)(pfVar4 + -9));
      }
    }
    pfVar4 = pfVar4 + 0x2f;
  } while ((int)pfVar4 < 0x4c2b54);
  return;
}



/* effects_render @ 0042e820 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders active effects (rotated quads) */

void effects_render(void)

{
  undefined1 uVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  longlong lVar5;
  undefined2 uVar7;
  undefined3 uVar6;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  
  fStack_40 = 6.144453e-39;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_bind_texture)((int)particles_texture,0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  iVar2 = 0x4ab364;
  do {
    if (((*(uint *)(iVar2 + -8) != 0) && (0.0 <= *(float *)(iVar2 + -0x10))) &&
       ((*(uint *)(iVar2 + -8) & 0x40) != 0)) {
      fStack_44 = *(float *)(iVar2 + -0x20);
      fcos((float10)fStack_44);
      fsin((float10)fStack_44);
      lVar5 = __ftol();
      uVar1 = (undefined1)lVar5;
      lVar5 = __ftol();
      uVar7 = CONCAT11(uVar1,(char)lVar5);
      lVar5 = __ftol();
      uVar6 = CONCAT21(uVar7,(char)lVar5);
      lVar5 = __ftol();
      fStack_40 = camera_offset_x + *(float *)(iVar2 + -0x34);
      fStack_48 = (float)CONCAT31(uVar6,(char)lVar5);
      (*grim_interface_ptr->vtable->grim_submit_vertices_transform_color)
                ((float *)(iVar2 + 0x14),4,&fStack_40,(float *)&stack0xffffffc8,&fStack_48);
    }
    iVar2 = iVar2 + 0xbc;
  } while (iVar2 < 0x4c2b64);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  iVar2 = 0x4ab364;
  do {
    if (((*(uint *)(iVar2 + -8) != 0) && (0.0 <= *(float *)(iVar2 + -0x10))) &&
       ((*(uint *)(iVar2 + -8) & 0x40) == 0)) {
      fVar3 = (float10)fcos((float10)*(float *)(iVar2 + -0x20));
      fVar4 = (float10)fsin((float10)*(float *)(iVar2 + -0x20));
      fStack_48 = (float)-fVar4 * *(float *)(iVar2 + -0x1c);
      fStack_44 = (float)fVar4 * *(float *)(iVar2 + -0x1c);
      fStack_40 = (float)(fVar3 * (float10)*(float *)(iVar2 + -0x1c));
      __ftol();
      __ftol();
      __ftol();
      __ftol();
      (*grim_interface_ptr->vtable->grim_submit_vertices_transform_color)
                ((float *)(iVar2 + 0x14),4,(float *)&stack0xffffffac,(float *)&stack0xffffffb4,
                 (float *)&stack0xffffffa4);
    }
    iVar2 = iVar2 + 0xbc;
  } while (iVar2 < 0x4c2b64);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  return;
}



/* effect_spawn_blood_splatter @ 0042eb10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* spawns blood splatter particles (effect id 7) */

void __cdecl effect_spawn_blood_splatter(float *pos,float angle,float age)

{
  uint uVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  
  if (config_blob.fx_toggle == '\0') {
    effect_template_lifetime = 0.25 - age;
    fVar3 = (float10)angle + (float10)3.1415927;
    effect_template_color_r = 0x3f800000;
    effect_template_color_g = 0x3f800000;
    fVar4 = (float10)fcos(fVar3);
    effect_template_flags = 0xc9;
    effect_template_color_b = 0x3f800000;
    effect_template_color_a = 0x3f000000;
    effect_template_scale_step = 0.0;
    effect_template_age = age;
    iVar2 = 2;
    fVar5 = (float10)fsin(fVar3);
    do {
      uVar1 = crt_rand();
      effect_template_rotation = (float)(int)((uVar1 & 0x3f) - 0x20) * 0.1 + (float)fVar3;
      uVar1 = crt_rand();
      effect_template_half_width = (float)((uVar1 & 7) + 1);
      effect_template_half_height = effect_template_half_width;
      uVar1 = crt_rand();
      effect_template_vel_x = (float)((uVar1 & 0x3f) + 100) * (float)fVar4;
      uVar1 = crt_rand();
      effect_template_rotation_step = 0;
      effect_template_vel_y = (float)((uVar1 & 0x3f) + 100) * (float)fVar5;
      uVar1 = crt_rand();
      effect_template_scale_step = (float)(uVar1 & 0x7f) * 0.03 + 0.1;
      effect_spawn(7,pos);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}



/* effect_spawn_freeze_shard @ 0042ec80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* spawns a random freeze shard effect (ids 8..10) around the given angle */

void __cdecl effect_spawn_freeze_shard(float *pos,float angle)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  
  effect_template_color_r = 0x3f800000;
  effect_template_flags = 0x1cd;
  effect_template_color_g = 0x3f800000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f000000;
  uVar2 = crt_rand();
  effect_template_age = 0;
  effect_template_half_width = 8.0;
  effect_template_half_height = 8.0;
  effect_template_lifetime = (float)(uVar2 & 0xf) * 0.01 + 0.2;
  fVar1 = angle + 3.1415927;
  iVar3 = crt_rand();
  effect_template_rotation = (float)(iVar3 % 100) * 0.01 + fVar1;
  iVar3 = crt_rand();
  effect_template_half_width = (float)(iVar3 % 5 + 7);
  fVar4 = (float10)fcos((float10)fVar1);
  effect_template_vel_x = (float)(fVar4 * (float10)114.0);
  fVar4 = (float10)fsin((float10)fVar1);
  effect_template_vel_y = (float)(fVar4 * (float10)114.0);
  effect_template_half_height = effect_template_half_width;
  iVar3 = crt_rand();
  effect_template_rotation_step = ((float)(iVar3 % 0x14) * 0.1 - 1.0) * 4.0;
  uVar2 = crt_rand();
  effect_template_scale_step = (float)(int)-(uVar2 & 0xf) * 0.1;
  iVar3 = crt_rand();
  effect_spawn(iVar3 % 3 + 8,pos);
  return;
}



/* effect_spawn_freeze_shatter @ 0042ee00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* four-way shatter burst (id 0xe) plus extra freeze shards */

void __cdecl effect_spawn_freeze_shatter(float *pos,float angle)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  undefined4 local_14;
  
  effect_template_color_r = 0x3f800000;
  effect_template_flags = 0x5d;
  effect_template_color_g = 0x3f800000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f000000;
  effect_template_age = 0;
  effect_template_lifetime = 0x3f8ccccd;
  effect_template_scale_step = 0;
  local_14 = 0;
  do {
    fVar3 = (float10)local_14 * (float10)1.5707964 + (float10)angle;
    effect_template_rotation = (float)fVar3;
    fVar3 = (float10)fcos(fVar3);
    effect_template_vel_x = (float)(fVar3 * (float10)42.0);
    fVar3 = (float10)fsin((float10)effect_template_rotation);
    effect_template_vel_y = (float)(fVar3 * (float10)42.0);
    iVar1 = crt_rand();
    effect_template_half_width = (float)(iVar1 % 10 + 0x12);
    effect_template_half_height = effect_template_half_width;
    iVar1 = crt_rand();
    effect_template_rotation_step = ((float)(iVar1 % 0x14) * 0.1 - 1.0) * 1.9;
    effect_spawn(0xe,pos);
    local_14 = local_14 + 1;
  } while (local_14 < 4);
  iVar1 = 4;
  do {
    iVar2 = crt_rand();
    effect_spawn_freeze_shard(pos,(float)(iVar2 % 0x264) * 0.01);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}



/* effect_spawn_burst @ 0042ef60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* generic burst loop for effect id 0 */

void __cdecl effect_spawn_burst(float *pos,int count)

{
  uint uVar1;
  int iVar2;
  
  effect_template_color_r = 0x3ecccccd;
  effect_template_flags = 0x1d;
  effect_template_color_g = 0x3f000000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f000000;
  effect_template_age = 0;
  effect_template_lifetime = 0x3f000000;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  if (0 < count) {
    do {
      uVar1 = crt_rand();
      effect_template_rotation = (float)(uVar1 & 0x7f) * 0.049087387;
      uVar1 = crt_rand();
      effect_template_vel_x = (float)(int)((uVar1 & 0x7f) - 0x40);
      uVar1 = crt_rand();
      effect_template_vel_y = (float)(int)((uVar1 & 0x7f) - 0x40);
      iVar2 = crt_rand();
      effect_template_scale_step = (float)(iVar2 % 100) * 0.01 + 0.1;
      effect_spawn(0,pos);
      count = count + -1;
    } while (count != 0);
  }
  return;
}



/* effect_spawn_shrink_fx @ 0042f080 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] void* sub_42f080(float* arg1) */

void * __cdecl effect_spawn_shrink_fx(float *arg1)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  
  effect_template_color_r = 0x3e99999a;
  effect_template_flags = 0x19;
  effect_template_color_g = 0x3f19999a;
  effect_template_color_b = 0x3f666666;
  effect_template_color_a = 0x3f800000;
  effect_template_age = 0;
  effect_template_lifetime = 0x3e99999a;
  effect_template_half_width = 0x42100000;
  effect_template_half_height = 0x42100000;
  effect_template_rotation = 0.0;
  effect_template_vel_x = 0.0;
  effect_template_vel_y = 0.0;
  effect_template_scale_step = -4.0;
  effect_spawn(1,arg1);
  effect_template_color_b = 0x3f800000;
  effect_template_color_r = 0x3ecccccd;
  effect_template_flags = 0x1d;
  effect_template_color_g = 0x3f000000;
  effect_template_color_a = 0x3f000000;
  effect_template_age = 0;
  effect_template_lifetime = 0x3e99999a;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  iVar4 = 4;
  pvVar3 = (void *)config_blob.detail_preset;
  if (config_blob.detail_preset < 3) {
    iVar4 = 2;
  }
  for (; iVar4 != 0; iVar4 = iVar4 + -1) {
    uVar1 = crt_rand();
    effect_template_rotation = (float)(uVar1 & 0x7f) * 0.049087387;
    uVar1 = crt_rand();
    effect_template_vel_x = (float)(int)((uVar1 & 0x7f) - 0x40) * 1.4;
    uVar1 = crt_rand();
    effect_template_vel_y = (float)(int)((uVar1 & 0x7f) - 0x40) * 1.4;
    iVar2 = crt_rand();
    effect_template_scale_step = (float)(iVar2 % 100) * 0.01 + 0.1;
    pvVar3 = effect_spawn(0,arg1);
  }
  return pvVar3;
}



/* fx_spawn_electric_arc @ 0042f270 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] void* sub_42f270(float* arg1, float arg2, float arg3) */

void * __cdecl fx_spawn_electric_arc(float *arg1,float arg2,float arg3)

{
  void *pvVar1;
  
  effect_template_lifetime = arg3 * 0.8;
  effect_template_color_g = 0x3f19999a;
  effect_template_scale_step = arg2 * 45.0;
  effect_template_color_r = 0x3f19999a;
  effect_template_flags = 0x19;
  effect_template_color_b = 0x3f666666;
  effect_template_color_a = 0x3f800000;
  effect_template_age = 0;
  effect_template_half_width = 0x40800000;
  effect_template_half_height = 0x40800000;
  effect_template_rotation = 0;
  effect_template_vel_x = 0;
  effect_template_vel_y = 0;
  pvVar1 = effect_spawn(1,arg1);
  return pvVar1;
}



/* fx_spawn_plasma_explosion @ 0042f330 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] void* sub_42f330(float* arg1, float arg2, int32_t arg3) */

void * __cdecl fx_spawn_plasma_explosion(float *arg1,float arg2,int arg3)

{
  void *pvVar1;
  
  effect_template_scale_step = arg2 * 45.0;
  effect_template_color_b = 0x3e99999a;
  effect_template_color_r = 0x3f666666;
  effect_template_color_g = 0x3f19999a;
  effect_template_flags = 0x19;
  effect_template_color_a = 0x3f800000;
  effect_template_age = 0x3dcccccd;
  effect_template_lifetime = arg3;
  effect_template_half_width = 0x40800000;
  effect_template_half_height = 0x40800000;
  effect_template_rotation = 0;
  effect_template_vel_x = 0;
  effect_template_vel_y = 0;
  pvVar1 = effect_spawn(1,arg1);
  return pvVar1;
}



/* fx_spawn_fire_particles @ 0042f3f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] void* sub_42f3f0(float* arg1, float arg2, int32_t arg3) */

void * __cdecl fx_spawn_fire_particles(float *arg1,float arg2,int arg3)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  float10 fVar5;
  float10 fVar6;
  longlong lVar7;
  float local_10;
  float local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = 1.0;
  local_c = 0.9;
  local_8 = 0x3dcccccd;
  local_4 = 0x3f800000;
  effect_template_color_r = 0x3f800000;
  pvVar4 = (void *)0x3f800000;
  effect_template_flags = 0x19;
  effect_template_color_g = 0x3f666666;
  effect_template_color_b = 0x3dcccccd;
  effect_template_color_a = 0x3f800000;
  effect_template_half_width = 0x40800000;
  effect_template_half_height = 0x40800000;
  effect_template_rotation = 0;
  effect_template_vel_x = 0;
  effect_template_vel_y = 0;
  effect_template_scale_step = 0x425c0000;
  if (0 < arg3) {
    lVar7 = __ftol();
    do {
      uVar2 = crt_rand();
      fVar1 = (float)(uVar2 & 0x1ff) * 0.001953125 * 6.2831855;
      iVar3 = crt_rand();
      fVar5 = (float10)(iVar3 % (int)lVar7);
      fVar6 = (float10)fcos((float10)fVar1);
      local_10 = (float)(fVar6 * fVar5 + (float10)*arg1);
      fVar6 = (float10)fsin((float10)fVar1);
      local_c = (float)(fVar6 * fVar5 + (float10)arg1[1]);
      uVar2 = crt_rand();
      effect_template_age = (float)(int)-(uVar2 & 0xff) * 0.0012;
      effect_template_lifetime = 0.1 - effect_template_age;
      pvVar4 = effect_spawn(0,&local_10);
      arg3 = arg3 + -1;
    } while (arg3 != 0);
  }
  return pvVar4;
}



/* fx_spawn_shockwave @ 0042f540 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_42f540(int32_t arg1, float arg2) */

int __cdecl fx_spawn_shockwave(int arg1,float arg2)

{
  float fVar1;
  void *pvVar2;
  uint uVar3;
  int iVar4;
  void *pvVar5;
  longlong lVar6;
  
  fVar1 = arg2 * 0.8;
  effect_template_color_r = 0x3ecccccd;
  effect_template_lifetime = fVar1 * 0.7;
  effect_template_color_a = 0x3f000000;
  effect_template_flags = 0x1d;
  effect_template_color_g = 0x3f000000;
  effect_template_color_b = 0x3f800000;
  effect_template_age = 0;
  if (1.1 < effect_template_lifetime) {
    effect_template_lifetime = 1.1;
  }
  effect_template_half_width = fVar1 * 32.0;
  effect_template_half_height = effect_template_half_width;
  lVar6 = __ftol();
  pvVar2 = (void *)lVar6;
  if (config_blob.detail_preset < 3) {
    pvVar2 = (void *)((int)pvVar2 / 2);
  }
  pvVar5 = pvVar2;
  if (0 < (int)pvVar2) {
    do {
      uVar3 = crt_rand();
      effect_template_rotation = (float)(uVar3 & 0x7f) * 0.049087387;
      uVar3 = crt_rand();
      effect_template_vel_x = (float)(int)((uVar3 & 0x7f) - 0x40) * fVar1 * 1.4;
      uVar3 = crt_rand();
      effect_template_vel_y = (float)(int)((uVar3 & 0x7f) - 0x40) * fVar1 * 1.4;
      iVar4 = crt_rand();
      effect_template_scale_step = ((float)(iVar4 % 100) * 0.01 + 0.1) * fVar1;
      pvVar2 = effect_spawn(0,(float *)arg1);
      pvVar5 = (void *)((int)pvVar5 + -1);
    } while (pvVar5 != (void *)0x0);
  }
  return (int)pvVar2;
}



/* effect_spawn_explosion_burst @ 0042f6c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* spawns explosion burst and shockwave particles */

void __cdecl effect_spawn_explosion_burst(float *pos,float scale)

{
  float *pos_00;
  int iVar1;
  int iVar2;
  uint uVar3;
  
  pos_00 = pos;
  effect_template_scale_step = scale * 25.0;
  effect_template_color_r = 0x3f19999a;
  effect_template_flags = 0x19;
  effect_template_color_g = 0x3f19999a;
  effect_template_color_b = 0x3f19999a;
  effect_template_color_a = 0x3f800000;
  effect_template_lifetime = 0.35;
  effect_template_age = -0.1;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  effect_template_rotation = 0.0;
  effect_template_vel_x = 0.0;
  effect_template_vel_y = 0.0;
  effect_spawn(1,pos);
  effect_template_color_b = 0x3dcccccd;
  effect_template_color_r = 0x3dcccccd;
  effect_template_flags = 0x5d;
  effect_template_color_g = 0x3dcccccd;
  effect_template_color_a = 0x3f800000;
  effect_template_rotation = 0.0;
  effect_template_vel_x = 0.0;
  effect_template_vel_y = 0.0;
  if (3 < config_blob.detail_preset) {
    pos = (float *)0x0;
    do {
      effect_template_half_width = 0x42000000;
      effect_template_half_height = 0x42000000;
      effect_template_age = (float)(int)pos * 0.2 - 0.5;
      effect_template_lifetime = (float)(int)pos * 0.2 + 0.6;
      iVar1 = crt_rand();
      effect_template_rotation_step = 1.4;
      effect_template_rotation = (float)(iVar1 % 0x266) * 0.02;
      effect_template_scale_step = scale * 5.0;
      effect_spawn(0x11,pos_00);
      pos = (float *)((int)pos + 1);
    } while ((int)pos < 2);
  }
  effect_template_scale_step = scale * 45.0;
  effect_template_color_r = 0x3f800000;
  effect_template_flags = 0x19;
  effect_template_color_g = 0x3f800000;
  effect_template_color_b = 0x3f800000;
  effect_template_color_a = 0x3f800000;
  effect_template_age = 0.0;
  effect_template_lifetime = 0.3;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  effect_template_rotation = 0.0;
  effect_template_vel_x = 0.0;
  effect_template_vel_y = 0.0;
  effect_spawn(0,pos_00);
  effect_template_color_b = 0x3f800000;
  effect_template_color_r = 0x3f800000;
  effect_template_flags = 0x1d;
  effect_template_color_g = 0x3f800000;
  effect_template_color_a = 0x3f800000;
  effect_template_lifetime = 0.7;
  effect_template_age = 0.0;
  effect_template_half_width = 0x42000000;
  effect_template_half_height = 0x42000000;
  if (config_blob.detail_preset < 2) {
    iVar1 = 1;
  }
  else {
    iVar1 = (3 < config_blob.detail_preset) + 3;
  }
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    iVar2 = crt_rand();
    effect_template_rotation = (float)(iVar2 % 0x13a) * 0.02;
    uVar3 = crt_rand();
    effect_template_vel_x = (float)(int)((uVar3 & 0x3f) * 2 + -0x40);
    uVar3 = crt_rand();
    effect_template_vel_y = (float)(int)((uVar3 & 0x3f) * 2 + -0x40);
    iVar2 = crt_rand();
    effect_template_scale_step = (float)(iVar2 - 3U & 7) * scale;
    iVar2 = crt_rand();
    effect_template_rotation_step = (float)(iVar2 + 3U & 7);
    effect_spawn(0xc,pos_00);
  }
  return;
}


