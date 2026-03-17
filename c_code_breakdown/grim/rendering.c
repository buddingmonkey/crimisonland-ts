/* grim_bitmap_delete @ 10002f60 */

/* [binja] BOOL __fastcall sub_10002f60(void* arg1) */

bool __fastcall grim_bitmap_delete(void *arg1)

{
  undefined1 uVar1;
  WINBOOL WVar2;
  
  uVar1 = 0;
  if (*(HGDIOBJ *)((int)arg1 + 0x1c) != (HGDIOBJ)0x0) {
    WVar2 = DeleteObject(*(HGDIOBJ *)((int)arg1 + 0x1c));
    uVar1 = (undefined1)WVar2;
    *(undefined4 *)((int)arg1 + 0x1c) = 0;
  }
  return (bool)uVar1;
}



/* grim_clear_color @ 10006cb0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0x2c: packs RGBA into device clear color */

void grim_clear_color(float r,float g,float b,float a)

{
  IDirect3DDevice8Vtbl *pIVar1;
  LPDIRECT3DDEVICE8 This;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  float z;
  DWORD stencil;
  
  This = grim_d3d_device;
  if ((grim_render_disabled == '\0') && (grim_device_cooperative != '\0')) {
    stencil = 0;
    z = 0.0;
    pIVar1 = grim_d3d_device->lpVtbl;
    uVar2 = ftol();
    iVar3 = ftol();
    uVar4 = ftol();
    uVar5 = ftol();
    (*pIVar1->Clear)(This,0,(D3DRECT *)0x0,1,
                     ((uVar2 & 0xff | iVar3 << 8) << 8 | uVar4 & 0xff) << 8 | uVar5 & 0xff,z,stencil
                    );
  }
  return;
}



/* grim_set_render_target @ 10006d50 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0x30 (provisional): set render target; -1 resets */

int grim_set_render_target(int target_index)

{
  undefined4 in_EAX;
  uint uVar1;
  ULONG UVar2;
  
  UVar2 = CONCAT31((int3)((uint)in_EAX >> 8),grim_render_disabled);
  if (grim_render_disabled == '\0') {
    if (target_index < 0) {
      if (grim_backbuffer_surface != (LPDIRECT3DSURFACE8)0x0) {
        if (grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) {
          (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface);
        }
        grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
        uVar1 = (*grim_d3d_device->lpVtbl->SetRenderTarget)
                          (grim_d3d_device,grim_backbuffer_surface,(IDirect3DSurface8 *)0x0);
        if ((int)uVar1 < 0) {
          return uVar1 & 0xffffff00;
        }
        UVar2 = 0;
        if (grim_backbuffer_surface != (LPDIRECT3DSURFACE8)0x0) {
          UVar2 = (*grim_backbuffer_surface->lpVtbl->Release)(grim_backbuffer_surface);
        }
        grim_backbuffer_surface = (LPDIRECT3DSURFACE8)0x0;
      }
    }
    else {
      if (grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) {
        (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface);
        grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
      }
      if (grim_backbuffer_surface == (LPDIRECT3DSURFACE8)0x0) {
        (*grim_d3d_device->lpVtbl->GetRenderTarget)(grim_d3d_device,&grim_backbuffer_surface);
      }
      uVar1 = (**(code **)(**(int **)((&grim_texture_slots)[target_index] + 4) + 0x3c))
                        (*(int **)((&grim_texture_slots)[target_index] + 4),0,
                         &grim_render_target_surface);
      if ((int)uVar1 < 0) {
        return uVar1 & 0xffffff00;
      }
      UVar2 = (*grim_d3d_device->lpVtbl->SetRenderTarget)
                        (grim_d3d_device,grim_render_target_surface,(IDirect3DSurface8 *)0x0);
      if ((int)UVar2 < 0) {
        uVar1 = 0;
        if (grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) {
          uVar1 = (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface);
        }
        grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
        return uVar1 & 0xffffff00;
      }
    }
  }
  return CONCAT31((int3)(UVar2 >> 8),1);
}



/* grim_draw_fullscreen_quad @ 10007870 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xc8: full-screen quad with current texture */

void grim_draw_fullscreen_quad(void)

{
  int *in_ECX;
  
  (**(code **)(*in_ECX + 0xfc))(0);
  (**(code **)(*in_ECX + 0xe8))();
  (**(code **)(*in_ECX + 0x11c))(0,0,(float)grim_backbuffer_width,(float)grim_backbuffer_height);
  (**(code **)(*in_ECX + 0xf0))();
  return;
}



/* grim_draw_rect_filled @ 100078e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xd0: UI panel fill/quad */

void grim_draw_rect_filled(float *xy,float w,float h)

{
  int *in_ECX;
  int in_stack_00000010;
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (0.0 < *(float *)(in_stack_00000010 + 0xc)) {
    (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,0,(IDirect3DBaseTexture8 *)0x0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,3);
    uVar3 = 3;
    uVar2 = 4;
    puVar1 = (undefined4 *)0x0;
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,3);
    (**(code **)(*in_ECX + 0x110))();
    (**(code **)(*in_ECX + 0xfc))(0);
    (**(code **)(*in_ECX + 0xe8))();
    (**(code **)(*in_ECX + 0x11c))(*puVar1,puVar1[1],uVar2,uVar3);
    (**(code **)(*in_ECX + 0xf0))();
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
  }
  return;
}



/* grim_draw_fullscreen_color @ 100079b0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xcc: fullscreen color/fade overlay */

void grim_draw_fullscreen_color(float r,float g,float b,float a)

{
  int *in_ECX;
  LPDIRECT3DDEVICE8 pIVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (0.0 < a) {
    (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,0,(IDirect3DBaseTexture8 *)0x0);
    uVar4 = 3;
    uVar3 = 1;
    uVar2 = 0;
    pIVar1 = grim_d3d_device;
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,3);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,3);
    (**(code **)(*in_ECX + 0x114))(pIVar1,uVar2,uVar3,uVar4);
    (**(code **)(*in_ECX + 0xfc))(0);
    (**(code **)(*in_ECX + 0xe8))();
    (**(code **)(*in_ECX + 0x11c))(0,0,(float)grim_backbuffer_width,(float)grim_backbuffer_height);
    (**(code **)(*in_ECX + 0xf0))();
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
  }
  return;
}



/* grim_begin_batch @ 10007ac0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xe8 (provisional): begin draw batch */

void grim_begin_batch(void)

{
  int iVar1;
  
  if (((grim_render_disabled == '\0') && (grim_batch_active == '\0')) &&
     (grim_batch_active = '\x01', grim_device_cooperative != '\0')) {
    (*grim_d3d_device->lpVtbl->BeginScene)(grim_d3d_device);
    iVar1 = (**(code **)(*grim_vertex_buffer + 0x2c))
                      (grim_vertex_buffer,0,0,&grim_vertex_write_ptr,0x2800);
    if (iVar1 < 0) {
      grim_device_cooperative = '\0';
    }
    grim_vertex_count._0_2_ = 0;
  }
  return;
}



/* grim_end_batch @ 10007b20 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xf0 (provisional): end draw batch/flush */

void grim_end_batch(void)

{
  if ((grim_render_disabled == '\0') && (grim_batch_active != '\0')) {
    (**(code **)(*grim_vertex_buffer + 0x30))(grim_vertex_buffer);
    if (grim_device_cooperative != '\0') {
      if ((short)grim_vertex_count != 0) {
        (*grim_d3d_device->lpVtbl->DrawIndexedPrimitive)
                  (grim_d3d_device,D3DPT_TRIANGLELIST,0,grim_vertex_count & 0xffff,0,
                   (grim_vertex_count & 0xffff) >> 1);
      }
      (*grim_d3d_device->lpVtbl->EndScene)(grim_d3d_device);
      grim_batch_active = '\0';
    }
  }
  return;
}



/* grim_draw_circle_filled @ 10007b90 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xd8 (provisional): triangle fan circle fill */

void grim_draw_circle_filled(float x,float y,float radius)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  float10 fVar6;
  int iVar7;
  float fStack_30;
  undefined4 **ppuStack_2c;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  if ((grim_batch_active == '\0') && (grim_batch_active = '\x01', grim_device_cooperative != '\0')) {
    ppuStack_2c = (undefined4 **)0x10007bc2;
    (*grim_d3d_device->lpVtbl->BeginScene)(grim_d3d_device);
    ppuStack_2c = &grim_vertex_write_ptr;
    fStack_30 = 0.0;
    iVar1 = (**(code **)(*grim_vertex_buffer + 0x2c))(grim_vertex_buffer,0);
    if (iVar1 < 0) {
      grim_device_cooperative = '\0';
    }
    grim_vertex_count = grim_vertex_count & 0xffff0000;
    (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,0,(IDirect3DBaseTexture8 *)0x0);
    ppuStack_2c = (undefined4 **)fStack_c;
    fStack_30 = fStack_10;
    pfVar3 = &fStack_30;
    pfVar4 = (float *)grim_vertex_write_ptr;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar4 = *pfVar3;
      pfVar3 = pfVar3 + 1;
      pfVar4 = pfVar4 + 1;
    }
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    grim_vertex_count._0_2_ = (short)grim_vertex_count + 1;
    iVar1 = ftol();
    iVar7 = 0;
    if (-1 < iVar1) {
      do {
        iVar2 = 7;
        fVar5 = ((float10)iVar7 * (float10)6.2831855) / (float10)iVar1;
        fVar6 = (float10)fcos(fVar5);
        fStack_30 = (float)(fVar6 * (float10)fStack_8 + (float10)fStack_10);
        fVar5 = (float10)fsin(fVar5);
        ppuStack_2c = (undefined4 **)(float)(fVar5 * (float10)fStack_8 + (float10)fStack_c);
        pfVar3 = &fStack_30;
        pfVar4 = (float *)grim_vertex_write_ptr;
        for (; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar4 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar4 = pfVar4 + 1;
        }
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        grim_vertex_count._0_2_ = (short)grim_vertex_count + 1;
        iVar7 = iVar7 + 1;
      } while (iVar7 <= iVar1);
    }
    (**(code **)(*grim_vertex_buffer + 0x30))(grim_vertex_buffer);
    if (grim_device_cooperative != '\0') {
      (*grim_d3d_device->lpVtbl->DrawPrimitive)
                (grim_d3d_device,D3DPT_TRIANGLEFAN,0,(grim_vertex_count & 0xffff) - 2);
      (*grim_d3d_device->lpVtbl->EndScene)(grim_d3d_device);
      grim_batch_active = '\0';
    }
  }
  return;
}



/* grim_draw_circle_outline @ 10007d40 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xdc (provisional): triangle strip ring/outline */

void grim_draw_circle_outline(float x,float y,float radius)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float10 fVar5;
  float10 fVar6;
  int iVar7;
  float fStack_30;
  float **ppfStack_2c;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  if ((grim_batch_active == '\0') && (grim_batch_active = '\x01', grim_device_cooperative != '\0')) {
    ppfStack_2c = (float **)0x10007d72;
    (*grim_d3d_device->lpVtbl->BeginScene)(grim_d3d_device);
    ppfStack_2c = &grim_vertex_write_ptr;
    fStack_30 = 0.0;
    iVar1 = (**(code **)(*grim_vertex_buffer + 0x2c))(grim_vertex_buffer,0);
    if (iVar1 < 0) {
      grim_device_cooperative = '\0';
    }
    grim_vertex_count = grim_vertex_count & 0xffff0000;
    iVar1 = ftol();
    iVar7 = 0;
    if (-1 < iVar1) {
      do {
        iVar2 = 7;
        fVar5 = ((float10)iVar7 * (float10)6.2831855) / (float10)iVar1;
        fVar6 = (float10)fcos(fVar5);
        fStack_30 = (float)(fVar6 * (float10)fStack_8 + (float10)fStack_10);
        fVar5 = (float10)fsin(fVar5);
        ppfStack_2c = (float **)(float)(fVar5 * (float10)fStack_8 + (float10)fStack_c);
        pfVar3 = &fStack_30;
        pfVar4 = grim_vertex_write_ptr;
        for (; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar4 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar4 = pfVar4 + 1;
        }
        fStack_30 = (float)(((float10)fStack_8 + (float10)2.0) * (float10)(float)fVar6 +
                           (float10)fStack_10);
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        grim_vertex_count._0_2_ = (short)grim_vertex_count + 1;
        ppfStack_2c = (float **)
                      (float)(((float10)fStack_8 + (float10)2.0) * fVar5 + (float10)fStack_c);
        pfVar3 = &fStack_30;
        pfVar4 = grim_vertex_write_ptr;
        for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
          *pfVar4 = *pfVar3;
          pfVar3 = pfVar3 + 1;
          pfVar4 = pfVar4 + 1;
        }
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        grim_vertex_count._0_2_ = (short)grim_vertex_count + 1;
        iVar7 = iVar7 + 1;
      } while (iVar7 <= iVar1);
    }
    (**(code **)(*grim_vertex_buffer + 0x30))(grim_vertex_buffer);
    if (grim_device_cooperative != '\0') {
      (*grim_d3d_device->lpVtbl->DrawPrimitive)
                (grim_d3d_device,D3DPT_TRIANGLESTRIP,0,(grim_vertex_count & 0xffff) - 2);
      (*grim_d3d_device->lpVtbl->EndScene)(grim_d3d_device);
      grim_batch_active = '\0';
    }
  }
  return;
}



/* grim_set_rotation @ 10007f30 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xfc: precompute sin/cos (+45deg) for rotation matrix */

void grim_set_rotation(float radians)

{
  float10 fVar1;
  
  grim_rotation_angle = radians;
  fVar1 = (float10)fcos((float10)radians + (float10)0.7853982);
  grim_rotation_cos = (float)fVar1;
  fVar1 = (float10)fsin((float10)radians + (float10)0.7853982);
  grim_rotation_m00 = grim_rotation_cos;
  grim_rotation_m11 = grim_rotation_cos;
  grim_rotation_sin = (float)fVar1;
  grim_rotation_m10 = -grim_rotation_sin;
  grim_rotation_m01 = grim_rotation_sin;
  return;
}



/* grim_set_color @ 10007f90 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x114 (provisional) */

void grim_set_color(float r,float g,float b,float a)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = ftol();
  iVar2 = ftol();
  uVar3 = ftol();
  uVar4 = ftol();
  grim_color_slot0 = ((uVar1 & 0xff | iVar2 << 8) << 8 | uVar3 & 0xff) << 8 | uVar4 & 0xff;
  grim_color_slot3 = grim_color_slot0;
  grim_color_slot1 = grim_color_slot0;
  grim_color_slot2 = grim_color_slot0;
  return;
}



/* grim_set_color_ptr @ 10008040 */

/* Grim2D vtable 0x110: set color from float[4] */

void grim_set_color_ptr(float *rgba)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  uVar1 = ftol();
  uVar2 = ftol();
  uVar3 = ftol();
  uVar4 = ftol();
  rgba = (float *)CONCAT31(CONCAT21(CONCAT11(uVar1,uVar2),uVar3),uVar4);
  grim_color_slot0 = rgba;
  grim_color_slot3 = rgba;
  grim_color_slot1 = rgba;
  grim_color_slot2 = rgba;
  return;
}



/* grim_draw_line @ 100080b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xe0 (provisional): builds line quad from endpoints */

void grim_draw_line(float *p0,float *p1,float thickness)

{
  int *in_ECX;
  undefined *puVar1;
  undefined *puVar2;
  
  if ((DAT_10059bb4 & 1) == 0) {
    DAT_10059bb4 = DAT_10059bb4 | 1;
    grim_atexit_register((_onexit_t)&DAT_10008140);
  }
  puVar2 = &grim_line_normal_x;
  puVar1 = &grim_line_normal_x;
  _grim_line_normal_x = *p1 - *p0;
  _grim_line_normal_y = p1[1] - p0[1];
  thunk_FUN_1000cc2c();
  _grim_line_normal_x = _grim_line_normal_y * (float)p0;
  _grim_line_normal_y = _grim_line_normal_x * (float)p0;
  (**(code **)(*in_ECX + 0xe4))(p0,p1,&grim_line_normal_x,puVar1,puVar2);
  return;
}



/* grim_draw_line_quad @ 10008150 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xe4 (provisional): line quad from endpoints + half-width vector */

void grim_draw_line_quad(float *p0,float *p1,float *half_vec)

{
  int *in_ECX;
  
  (**(code **)(*in_ECX + 0x138))
            (*p0 - *half_vec,p0[1] - half_vec[1],*p0 + *half_vec,p0[1] + half_vec[1],*p1 + *half_vec
             ,p1[1] + half_vec[1],*p1 - *half_vec,p1[1] - half_vec[1]);
  return;
}



/* grim_set_color_slot @ 100081c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x118 (provisional): set color slot */

void grim_set_color_slot(int index,float r,float g,float b,float a)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = ftol();
  iVar2 = ftol();
  uVar3 = ftol();
  uVar4 = ftol();
  (&grim_color_slot0)[index] = ((uVar1 & 0xff | iVar2 << 8) << 8 | uVar3 & 0xff) << 8 | uVar4 & 0xff
  ;
  return;
}



/* grim_set_atlas_frame @ 10008230 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x104 (provisional) */

void grim_set_atlas_frame(int atlas_size,int frame)

{
  float fVar1;
  
  fVar1 = 1.0 / (float)atlas_size;
  grim_uv_u3 = *(float *)((&grim_subrect_ptr_table)[atlas_size] + frame * 8);
  grim_uv_v1 = *(float *)((&grim_subrect_ptr_table)[atlas_size] + 4 + frame * 8);
  grim_uv_u0 = grim_uv_u3;
  grim_uv_v0 = grim_uv_v1;
  grim_uv_u1 = grim_uv_u3 + fVar1;
  grim_uv_u2 = grim_uv_u3 + fVar1;
  grim_uv_v2 = grim_uv_v1 + fVar1;
  grim_uv_v3 = grim_uv_v1 + fVar1;
  return;
}



/* grim_set_sub_rect @ 100082c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x108: atlas sub-rect from grid table */

void grim_set_sub_rect(int atlas_size,int width,int height,int frame)

{
  float fVar1;
  
  grim_uv_u3 = *(float *)((&grim_subrect_ptr_table)[atlas_size] + frame * 8);
  grim_uv_v1 = *(float *)((&grim_subrect_ptr_table)[atlas_size] + 4 + frame * 8);
  grim_uv_u0 = grim_uv_u3;
  grim_uv_v0 = grim_uv_v1;
  grim_uv_u1 = (float)width * (1.0 / (float)atlas_size) + grim_uv_u3;
  grim_uv_u2 = grim_uv_u1;
  fVar1 = (1.0 / (float)atlas_size) * (float)height;
  grim_uv_v2 = fVar1 + grim_uv_v1;
  grim_uv_v3 = fVar1 + grim_uv_v1;
  return;
}



/* grim_set_uv @ 10008350 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x100 (provisional) */

void grim_set_uv(float u0,float v0,float u1,float v1)

{
  grim_uv_u0 = u0;
  grim_uv_v0 = v0;
  grim_uv_u1 = u1;
  grim_uv_v1 = v0;
  grim_uv_u2 = u1;
  grim_uv_v2 = v1;
  grim_uv_u3 = u0;
  grim_uv_v3 = v1;
  return;
}



/* grim_set_uv_point @ 100083a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x10c: set UV point */

void grim_set_uv_point(int index,float u,float v)

{
  (&grim_uv_u0)[index * 2] = u;
  (&grim_uv_v0)[index * 2] = v;
  return;
}



/* grim_flush_batch @ 100083c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xec: flush batch when vertex buffer fills */

void grim_flush_batch(void)

{
  int iVar1;
  
  if ((grim_render_disabled == '\0') && (grim_batch_active != '\0')) {
    (**(code **)(*grim_vertex_buffer + 0x30))(grim_vertex_buffer);
    (*grim_d3d_device->lpVtbl->DrawIndexedPrimitive)
              (grim_d3d_device,D3DPT_TRIANGLELIST,0,grim_vertex_count & 0xffff,0,
               (grim_vertex_count & 0xffff) >> 1);
    iVar1 = (**(code **)(*grim_vertex_buffer + 0x2c))
                      (grim_vertex_buffer,0,0,&grim_vertex_write_ptr,0x2800);
    if (-1 < iVar1) {
      grim_vertex_count = grim_vertex_count & 0xffff0000;
    }
  }
  return;
}



/* grim_submit_vertices_offset_color @ 10008430 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x130: translate + apply color */

void grim_submit_vertices_offset_color(float *verts,int count,float *offset,float *color)

{
  int *in_ECX;
  uint uVar1;
  int iVar2;
  float *pfVar3;
  
  if (grim_render_disabled == '\0') {
    pfVar3 = grim_vertex_write_ptr;
    for (uVar1 = (uint)(count * 0x1c) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *pfVar3 = *verts;
      verts = verts + 1;
      pfVar3 = pfVar3 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)pfVar3 = *(undefined1 *)verts;
      verts = (float *)((int)verts + 1);
      pfVar3 = (float *)((int)pfVar3 + 1);
    }
    iVar2 = count;
    if (0 < count) {
      do {
        pfVar3 = grim_vertex_write_ptr;
        *grim_vertex_write_ptr = *offset + *grim_vertex_write_ptr;
        pfVar3[1] = offset[1] + pfVar3[1];
        grim_vertex_write_ptr[4] = *color;
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + (short)count;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_submit_vertices_transform_color @ 100084e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x134: rotate + translate + apply color */

void grim_submit_vertices_transform_color
               (float *verts,int count,float *offset,float *matrix,float *color)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *in_ECX;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  
  if (grim_render_disabled == '\0') {
    pfVar7 = grim_vertex_write_ptr;
    for (uVar5 = (uint)(count * 0x1c) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pfVar7 = *verts;
      verts = verts + 1;
      pfVar7 = pfVar7 + 1;
    }
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined1 *)pfVar7 = *(undefined1 *)verts;
      verts = (float *)((int)verts + 1);
      pfVar7 = (float *)((int)pfVar7 + 1);
    }
    iVar6 = count;
    if (0 < count) {
      do {
        pfVar7 = grim_vertex_write_ptr;
        fVar1 = grim_vertex_write_ptr[1];
        fVar2 = matrix[1];
        fVar3 = *grim_vertex_write_ptr;
        fVar4 = *matrix;
        grim_vertex_write_ptr[1] =
             *grim_vertex_write_ptr * matrix[2] + grim_vertex_write_ptr[1] * matrix[3];
        *pfVar7 = fVar3 * fVar4 + fVar1 * fVar2;
        pfVar7 = grim_vertex_write_ptr;
        *grim_vertex_write_ptr = *offset + *grim_vertex_write_ptr;
        pfVar7[1] = offset[1] + pfVar7[1];
        grim_vertex_write_ptr[4] = *color;
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + (short)count;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_submit_vertices_transform @ 100085c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x128: copy verts, rotate, translate */

void grim_submit_vertices_transform(float *verts,int count,float *offset,float *matrix)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *in_ECX;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  
  if (grim_render_disabled == '\0') {
    pfVar7 = grim_vertex_write_ptr;
    for (uVar5 = (uint)(count * 0x1c) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pfVar7 = *verts;
      verts = verts + 1;
      pfVar7 = pfVar7 + 1;
    }
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined1 *)pfVar7 = *(undefined1 *)verts;
      verts = (float *)((int)verts + 1);
      pfVar7 = (float *)((int)pfVar7 + 1);
    }
    iVar6 = count;
    if (0 < count) {
      do {
        pfVar7 = grim_vertex_write_ptr;
        fVar1 = grim_vertex_write_ptr[1];
        fVar2 = matrix[1];
        fVar3 = *matrix;
        fVar4 = *grim_vertex_write_ptr;
        grim_vertex_write_ptr[1] =
             *grim_vertex_write_ptr * matrix[2] + grim_vertex_write_ptr[1] * matrix[3];
        *pfVar7 = fVar3 * fVar4 + fVar1 * fVar2;
        pfVar7 = grim_vertex_write_ptr;
        *grim_vertex_write_ptr = *offset + *grim_vertex_write_ptr;
        pfVar7[1] = offset[1] + pfVar7[1];
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + (short)count;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_submit_vertices_offset @ 10008680 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x12c: copy verts, translate */

void grim_submit_vertices_offset(float *verts,int count,float *offset)

{
  int *in_ECX;
  uint uVar1;
  int iVar2;
  float *pfVar3;
  
  if (grim_render_disabled == '\0') {
    pfVar3 = grim_vertex_write_ptr;
    for (uVar1 = (uint)(count * 0x1c) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *pfVar3 = *verts;
      verts = verts + 1;
      pfVar3 = pfVar3 + 1;
    }
    for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)pfVar3 = *(undefined1 *)verts;
      verts = (float *)((int)verts + 1);
      pfVar3 = (float *)((int)pfVar3 + 1);
    }
    iVar2 = count;
    if (0 < count) {
      do {
        pfVar3 = grim_vertex_write_ptr;
        *grim_vertex_write_ptr = *grim_vertex_write_ptr + *offset;
        pfVar3[1] = offset[1] + pfVar3[1];
        grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + (short)count;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_draw_quad_xy @ 10008720 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x120: draw quad from xy pointer */

void grim_draw_quad_xy(float *xy,float w,float h)

{
  int *in_ECX;
  
  (**(code **)(*in_ECX + 0x11c))(*xy,xy[1],w,h);
  return;
}



/* grim_draw_quad_rotated_matrix @ 10008750 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x124 (provisional): quad with rotation matrix */

void grim_draw_quad_rotated_matrix(float x,float y,float w,float h)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *in_ECX;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  if ((grim_render_disabled == '\0') && (grim_device_cooperative != '\0')) {
    if (grim_batch_active == '\0') {
      (**(code **)(*in_ECX + 0xe8))();
    }
    if (grim_rotation_angle == 0.0) {
      fStack_18 = x + w;
      fStack_20 = x;
      fStack_1c = y;
      fStack_14 = y;
      fStack_c = y + h;
      fStack_8 = x;
      fStack_10 = fStack_18;
      fStack_4 = fStack_c;
    }
    else {
      fVar3 = w * 0.5;
      fStack_8 = fVar3 + x;
      fVar1 = h * 0.5;
      fStack_4 = fVar1 + y;
      fVar2 = w * -0.5;
      fVar4 = h * -0.5;
      fStack_20 = grim_rotation_m00 * fVar2 + grim_rotation_m01 * fVar4 + fStack_8;
      fStack_1c = fStack_4 + grim_rotation_m10 * fVar2 + fVar4 * grim_rotation_m11;
      fStack_18 = grim_rotation_m00 * fVar3 + grim_rotation_m01 * fVar4 + fStack_8;
      fStack_14 = fStack_4 + grim_rotation_m10 * fVar3 + fVar4 * grim_rotation_m11;
      fStack_10 = grim_rotation_m00 * fVar3 + grim_rotation_m01 * fVar1 + fStack_8;
      fStack_c = fStack_4 + grim_rotation_m10 * fVar3 + grim_rotation_m11 * fVar1;
      fStack_8 = grim_rotation_m00 * fVar2 + grim_rotation_m01 * fVar1 + fStack_8;
      fStack_4 = fStack_4 + grim_rotation_m10 * fVar2 + grim_rotation_m11 * fVar1;
    }
    *grim_vertex_write_ptr = fStack_20;
    grim_vertex_write_ptr[1] = fStack_1c;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot0;
    grim_vertex_write_ptr[5] = grim_uv_u0;
    grim_vertex_write_ptr[6] = grim_uv_v0;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_18;
    grim_vertex_write_ptr[1] = fStack_14;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot2;
    grim_vertex_write_ptr[5] = grim_uv_u1;
    grim_vertex_write_ptr[6] = grim_uv_v1;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_10;
    grim_vertex_write_ptr[1] = fStack_c;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot1;
    grim_vertex_write_ptr[5] = grim_uv_u2;
    grim_vertex_write_ptr[6] = grim_uv_v2;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_8;
    grim_vertex_write_ptr[1] = fStack_4;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot3;
    grim_vertex_write_ptr[5] = grim_uv_u3;
    grim_vertex_write_ptr[6] = grim_uv_v3;
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + 4;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_draw_quad @ 10008b10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x11c (provisional) */

void grim_draw_quad(float x,float y,float w,float h)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int *in_ECX;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  
  if ((grim_render_disabled == '\0') && (grim_device_cooperative != '\0')) {
    if (grim_batch_active == '\0') {
      (**(code **)(*in_ECX + 0xe8))();
    }
    if (grim_rotation_angle == 0.0) {
      fStack_20 = x + w;
      fStack_28 = x;
      fStack_24 = y;
      fStack_1c = y;
      fVar1 = y + h;
      fStack_10 = x;
      fStack_18 = fStack_20;
      fStack_14 = fVar1;
    }
    else {
      fStack_10 = w * 0.5 + x;
      fVar1 = h * 0.5 + y;
      fVar2 = h * h + w * w;
      fVar3 = (float)(0x5f3759df - ((int)fVar2 >> 1));
      fVar2 = (1.5 - fVar2 * 0.5 * fVar3 * fVar3) * fVar3 * fVar2 * 0.5;
      fVar3 = grim_rotation_cos * fVar2;
      fVar2 = fVar2 * grim_rotation_sin;
      fStack_28 = fStack_10 - fVar3;
      fStack_24 = fVar1 - fVar2;
      fStack_20 = fStack_10 + fVar2;
      fStack_1c = -fVar3 + fVar1;
      fStack_18 = fStack_10 + fVar3;
      fStack_14 = fVar1 + fVar2;
      fStack_10 = -fVar2 + fStack_10;
      fVar1 = fVar1 + fVar3;
    }
    *grim_vertex_write_ptr = fStack_28;
    grim_vertex_write_ptr[1] = fStack_24;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot0;
    grim_vertex_write_ptr[5] = grim_uv_u0;
    grim_vertex_write_ptr[6] = grim_uv_v0;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_20;
    grim_vertex_write_ptr[1] = fStack_1c;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot2;
    grim_vertex_write_ptr[5] = grim_uv_u1;
    grim_vertex_write_ptr[6] = grim_uv_v1;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_18;
    grim_vertex_write_ptr[1] = fStack_14;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot1;
    grim_vertex_write_ptr[5] = grim_uv_u2;
    grim_vertex_write_ptr[6] = grim_uv_v2;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = fStack_10;
    grim_vertex_write_ptr[1] = fVar1;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot3;
    grim_vertex_write_ptr[5] = grim_uv_u3;
    grim_vertex_write_ptr[6] = grim_uv_v3;
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + 4;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_submit_vertex_raw @ 10008e30 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xf4: push 1 raw vertex (7 floats) */

void grim_submit_vertex_raw(float *vertex)

{
  int *in_ECX;
  int iVar1;
  float *pfVar2;
  
  if ((grim_render_disabled == '\0') && (grim_device_cooperative != '\0')) {
    if (grim_batch_active == '\0') {
      (**(code **)(*in_ECX + 0xe8))();
    }
    pfVar2 = grim_vertex_write_ptr;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar2 = *vertex;
      vertex = vertex + 1;
      pfVar2 = pfVar2 + 1;
    }
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + 1;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_submit_quad_raw @ 10008eb0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xf8: push 4 raw vertices (28 floats) */

void grim_submit_quad_raw(float *verts)

{
  int *in_ECX;
  int iVar1;
  float *pfVar2;
  
  if (grim_render_disabled == '\0') {
    pfVar2 = grim_vertex_write_ptr;
    for (iVar1 = 0x1c; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar2 = *verts;
      verts = verts + 1;
      pfVar2 = pfVar2 + 1;
    }
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + 4;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 0x1c;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}



/* grim_draw_rect_outline @ 10008f10 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xd4: UI panel outline/frame (4 edge quads) */

void grim_draw_rect_outline(float *xy,float w,float h)

{
  int *in_ECX;
  int iVar1;
  float *unaff_retaddr;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  
  (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,0,(IDirect3DBaseTexture8 *)0x0);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,3);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,3);
  uVar4 = 0;
  (**(code **)(*in_ECX + 0xfc))(0);
  (**(code **)(*in_ECX + 0xe8))();
  if (w == 1.0) {
    iVar1 = *in_ECX;
    w = 1.0;
  }
  else {
    if ((float)xy != 1.0) {
      fVar3 = unaff_retaddr[1];
      (**(code **)(*in_ECX + 0x11c))(*unaff_retaddr,fVar3,xy,0x3f800000);
      fVar2 = unaff_retaddr[1];
      (**(code **)(*in_ECX + 0x11c))(*unaff_retaddr,fVar2,0x3f800000,uVar4);
      (**(code **)(*in_ECX + 0x11c))
                (*unaff_retaddr,(float)xy + unaff_retaddr[1],fVar3 + 1.0,0x3f800000);
      (**(code **)(*in_ECX + 0x11c))(fVar2 + *unaff_retaddr,unaff_retaddr[1],0x3f800000,uVar4);
      goto LAB_1000903e;
    }
    iVar1 = *in_ECX;
    xy = (float *)0x3f800000;
  }
  (**(code **)(iVar1 + 0x11c))(*unaff_retaddr,unaff_retaddr[1],xy,w);
LAB_1000903e:
  (**(code **)(*in_ECX + 0xf0))();
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
  return;
}



/* grim_draw_quad_points @ 10009080 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x138 (provisional): push quad using 4 points */

void grim_draw_quad_points(float x0,float y0,float x1,float y1,float x2,float y2,float x3,float y3)

{
  int *in_ECX;
  
  if ((grim_render_disabled == '\0') && (grim_device_cooperative != '\0')) {
    if (grim_batch_active == '\0') {
      (**(code **)(*in_ECX + 0xe8))();
    }
    *grim_vertex_write_ptr = x0;
    grim_vertex_write_ptr[1] = y0;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot0;
    grim_vertex_write_ptr[5] = grim_uv_u0;
    grim_vertex_write_ptr[6] = grim_uv_v0;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = x1;
    grim_vertex_write_ptr[1] = y1;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot2;
    grim_vertex_write_ptr[5] = grim_uv_u1;
    grim_vertex_write_ptr[6] = grim_uv_v1;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = x2;
    grim_vertex_write_ptr[1] = y2;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot1;
    grim_vertex_write_ptr[5] = grim_uv_u2;
    grim_vertex_write_ptr[6] = grim_uv_v2;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    *grim_vertex_write_ptr = x3;
    grim_vertex_write_ptr[1] = y3;
    grim_vertex_write_ptr[2] = DAT_1005b288;
    grim_vertex_write_ptr[3] = DAT_1005b28c;
    grim_vertex_write_ptr[4] = grim_color_slot3;
    grim_vertex_write_ptr[5] = grim_uv_u3;
    grim_vertex_write_ptr[6] = grim_uv_v3;
    grim_vertex_count._0_2_ = (ushort)grim_vertex_count + 4;
    grim_vertex_write_ptr = grim_vertex_write_ptr + 7;
    if (grim_vertex_capacity <= (ushort)grim_vertex_count) {
      (**(code **)(*in_ECX + 0xec))();
    }
  }
  return;
}


