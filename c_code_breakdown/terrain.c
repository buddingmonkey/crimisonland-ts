/* terrain_generate @ 00417b80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* generates terrain texture into a render target using a level descriptor */

void __cdecl terrain_generate(void *desc)

{
  IGrim2D_vtbl *pIVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fStack_58;
  float fStack_54;
  undefined4 uStack_50;
  int iVar5;
  undefined4 in_stack_ffffffcc;
  
  camera_offset_x = 0;
  camera_offset_y = 0;
  if (terrain_texture_failed == '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (0x12,CONCAT31((int3)((uint)in_stack_ffffffcc >> 8),1));
    iVar5 = 0x13;
    uStack_50 = 0x417c0c;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_render_target)((int)terrain_render_target);
    (*grim_interface_ptr->vtable->grim_clear_color)(0.24705882,0.21960784,0.09803922,1.0);
    (*grim_interface_ptr->vtable->grim_bind_texture)
              ((&terrain_texture_handles)[*(int *)(iVar5 + 0x10)],0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.9);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 800;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_58 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.01384e-39;
        fStack_54 = fVar4 * 6.01384e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_58,7.697716e-37,7.697716e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 800;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_bind_texture)
              ((&terrain_texture_handles)[*(int *)(iVar5 + 0x14)],0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.9);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 0x23;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_58 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.01384e-39;
        fStack_54 = fVar4 * 6.01384e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_58,7.697716e-37,7.697716e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 0x23;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_bind_texture)
              ((&terrain_texture_handles)[*(int *)(iVar5 + 0x18)],0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 0xf;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_58 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.01384e-39;
        fStack_54 = fVar4 * 6.01384e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_58,7.697716e-37,7.697716e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 0xf;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    camera_offset_x = 0;
    camera_offset_y = 0;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_render_target)(-1);
    return;
  }
  terrain_render_target = (float)(&terrain_texture_handles)[*(int *)((int)desc + 0x10)];
  return;
}



/* terrain_generate_random @ 004181b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* selects a terrain variant and generates the terrain texture */

void terrain_generate_random(void)

{
  IGrim2D_vtbl *pIVar1;
  float handle;
  int iVar2;
  int iVar3;
  float fVar4;
  float fStack_64;
  float fStack_60;
  int iStack_54;
  undefined4 in_stack_ffffffbc;
  
  renderer_stat_b = crt_rand();
  renderer_stat_b = renderer_stat_b % 7;
  renderer_stat_a = crt_rand();
  renderer_stat_a = renderer_stat_a % 7;
  crt_rand();
  handle = terrain_texture_q1_tex1;
  fVar4 = terrain_texture_handles;
  renderer_stat_b = 0;
  renderer_stat_a = 1;
  _DAT_0048f544 = 0;
  if ((0x27 < game_status_blob.quest_unlock_index) && (iVar2 = crt_rand(), ((byte)iVar2 & 7) == 3))
  {
    terrain_generate(&DAT_00484c84);
    return;
  }
  if ((0x1d < game_status_blob.quest_unlock_index) && (iVar2 = crt_rand(), ((byte)iVar2 & 7) == 3))
  {
    terrain_generate(&DAT_00484acc);
    return;
  }
  if ((0x13 < game_status_blob.quest_unlock_index) && (iVar2 = crt_rand(), ((byte)iVar2 & 7) == 3))
  {
    terrain_generate(&game_level_score_table);
    return;
  }
  camera_offset_y = 0;
  camera_offset_x = 0;
  if (terrain_texture_failed == '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (0x12,CONCAT31((int3)((uint)in_stack_ffffffbc >> 8),1));
    fStack_60 = 6.01629e-39;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_render_target)(terrain_render_target);
    (*grim_interface_ptr->vtable->grim_clear_color)(0.24705882,0.21960784,0.09803922,1.0);
    (*grim_interface_ptr->vtable->grim_bind_texture)((int)fVar4,0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.9);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 800;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_64 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.016324e-39;
        fStack_60 = fVar4 * 6.016324e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_64,7.700894e-37,7.700894e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 800;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_bind_texture)((int)handle,0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.9);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 0x23;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_64 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.016324e-39;
        fStack_60 = fVar4 * 6.016324e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_64,7.700894e-37,7.700894e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 0x23;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_bind_texture)(iStack_54,0);
    (*grim_interface_ptr->vtable->grim_set_color)(0.7,0.7,0.7,0.6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    iVar3 = 0;
    iVar2 = terrain_texture_height * terrain_texture_width * 0xf;
    if (0 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13) {
      do {
        pIVar1 = grim_interface_ptr->vtable;
        iVar2 = crt_rand();
        (*pIVar1->grim_set_rotation)((float)(iVar2 % 0x13a) * 0.01);
        iVar2 = crt_rand();
        fVar4 = (float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0;
        iVar2 = crt_rand();
        fStack_64 = ((float)(iVar2 % (terrain_texture_width + 0x80)) - 64.0) * 6.016324e-39;
        fStack_60 = fVar4 * 6.016324e-39;
        (*grim_interface_ptr->vtable->grim_draw_quad_xy)(&fStack_64,7.700894e-37,7.700894e-37);
        iVar3 = iVar3 + 1;
        iVar2 = terrain_texture_height * terrain_texture_width * 0xf;
      } while (iVar3 < (int)(iVar2 + (iVar2 >> 0x1f & 0x7ffffU)) >> 0x13);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    camera_offset_x = 0;
    camera_offset_y = 0;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_render_target)(-1);
    if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
      console_printf(&console_log_queue,s_____Generated_terrain__0047377a + 2);
    }
  }
  return;
}



/* terrain_render @ 004188a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the terrain layer from terrain_render_target (ground RT) with UV scrolling; honors
   cv_terrainFilter (point filter when value==2.0); tiles fallback when texture missing */

void terrain_render(void)

{
  float v0;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_stack_ffffff9c;
  uint in_stack_ffffffc4;
  int iVar5;
  float fVar6;
  
  if (*(int *)((int)cv_terrainFilter + 0xc) == 0x40000000) {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  }
  if (terrain_texture_failed != '\0') {
    (*grim_interface_ptr->vtable->grim_bind_texture)(terrain_render_target,0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x12,in_stack_ffffffc4 & 0xffffff00);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    iVar4 = 0;
    iVar1 = (int)(terrain_texture_height + (terrain_texture_height >> 0x1f & 0xffU)) >> 8;
    if (iVar1 != -1 && -1 < iVar1 + 1) {
      iVar5 = 0;
      iVar1 = terrain_texture_width;
      do {
        iVar3 = 0;
        iVar2 = (int)(iVar1 + (iVar1 >> 0x1f & 0xffU)) >> 8;
        if (iVar2 != -1 && -1 < iVar2 + 1) {
          fVar6 = (float)iVar5;
          iVar2 = 0;
          do {
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((float)iVar2 + camera_offset_x,fVar6 + camera_offset_y,256.0,256.0);
            iVar2 = iVar2 + 0x100;
            iVar3 = iVar3 + 1;
            iVar1 = terrain_texture_width;
          } while (iVar3 < ((int)(terrain_texture_width + (terrain_texture_width >> 0x1f & 0xffU))
                           >> 8) + 1);
        }
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x100;
      } while (iVar4 < ((int)(terrain_texture_height + (terrain_texture_height >> 0x1f & 0xffU)) >>
                       8) + 1);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (0x12,CONCAT31((int3)((uint)in_stack_ffffff9c >> 8),1));
    return;
  }
  (*grim_interface_ptr->vtable->grim_bind_texture)(terrain_render_target,0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  fVar6 = -(camera_offset_x / (float)terrain_texture_width);
  v0 = -(camera_offset_y / (float)terrain_texture_height);
  (*grim_interface_ptr->vtable->grim_set_uv)
            (fVar6,v0,(float)config_blob.screen_width / (float)terrain_texture_width + fVar6,
             (float)config_blob.screen_height / (float)terrain_texture_height + v0);
  (*grim_interface_ptr->vtable->grim_draw_fullscreen_quad)(0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  return;
}


