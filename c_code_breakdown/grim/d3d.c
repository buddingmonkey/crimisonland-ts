/* grim_backup_textures @ 100028d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* backup texture surfaces before device reset */

int grim_backup_textures(void)

{
  undefined4 extraout_EAX;
  HRESULT HVar1;
  int iVar2;
  ULONG UVar3;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  uint extraout_EAX_02;
  uint extraout_EAX_03;
  uint extraout_EAX_04;
  int *piVar4;
  int iVar5;
  IDirect3DSurface8 *local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  grim_noop();
  if (grim_textures_backed_up_flag != '\0') {
    grim_noop();
    if (grim_textures_backed_up_flag != '\0') {
      return CONCAT31((int3)((uint)extraout_EAX >> 8),1);
    }
  }
  iVar5 = 0;
  local_14 = (IDirect3DSurface8 *)0x0;
  if (-1 < grim_texture_slot_max_index) {
    piVar4 = &grim_texture_slots;
    do {
      if ((*piVar4 != 0) && (*(char *)(*piVar4 + 8) != '\0')) {
        grim_noop();
        iVar2 = *piVar4;
        HVar1 = (*grim_d3d_device->lpVtbl->CreateImageSurface)
                          (grim_d3d_device,*(UINT *)(iVar2 + 0xc),*(UINT *)(iVar2 + 0x10),
                           grim_texture_format,(IDirect3DSurface8 **)(iVar2 + 0x14));
        if (HVar1 < 0) {
          grim_error_text = s_error_texture_backup1;
          grim_noop();
          grim_noop();
          return extraout_EAX_00 & 0xffffff00;
        }
        iVar2 = (**(code **)(**(int **)(*piVar4 + 4) + 0x3c))(*(int **)(*piVar4 + 4),0,&local_14);
        if (iVar2 < 0) {
          piVar4 = *(int **)((&grim_texture_slots)[iVar5] + 0x14);
          if (piVar4 != (int *)0x0) {
            iVar2 = (**(code **)(*piVar4 + 8))(piVar4);
            if (iVar2 == 0) {
              *(undefined4 *)((&grim_texture_slots)[iVar5] + 0x14) = 0;
            }
          }
          grim_error_text = s_error_texture_backup2;
          grim_noop();
          grim_noop();
          return extraout_EAX_01 & 0xffffff00;
        }
        HVar1 = (*grim_d3d_device->lpVtbl->CopyRects)
                          (grim_d3d_device,local_14,(RECT *)0x0,0,
                           *(IDirect3DSurface8 **)(*piVar4 + 0x14),(POINT *)0x0);
        if (HVar1 < 0) {
          piVar4 = *(int **)((&grim_texture_slots)[iVar5] + 0x14);
          if (piVar4 != (int *)0x0) {
            iVar2 = (**(code **)(*piVar4 + 8))(piVar4);
            if (iVar2 == 0) {
              *(undefined4 *)((&grim_texture_slots)[iVar5] + 0x14) = 0;
            }
          }
          if (local_14 != (IDirect3DSurface8 *)0x0) {
            UVar3 = (*local_14->lpVtbl->Release)(local_14);
            if (UVar3 == 0) {
              local_14 = (IDirect3DSurface8 *)0x0;
            }
          }
          grim_error_text = s_error_texture_backup3;
          grim_noop();
          uStack_10 = CONCAT31(uStack_10._1_3_,1);
          grim_texture_backup_flag1 = uStack_10;
          grim_texture_backup_flag2 = uStack_c;
          grim_texture_backup_flag3 = uStack_8;
          grim_texture_backup_flag4 = uStack_4;
          if (HVar1 == -0x7789f798) {
            grim_noop();
            return extraout_EAX_02 & 0xffffff00;
          }
          if (HVar1 == -0x7789f794) {
            grim_noop();
            return extraout_EAX_03 & 0xffffff00;
          }
          grim_noop();
          return extraout_EAX_04 & 0xffffff00;
        }
        if (local_14 != (IDirect3DSurface8 *)0x0) {
          UVar3 = (*local_14->lpVtbl->Release)(local_14);
          if (UVar3 == 0) {
            local_14 = (IDirect3DSurface8 *)0x0;
          }
        }
      }
      iVar5 = iVar5 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar5 <= grim_texture_slot_max_index);
  }
  grim_textures_backed_up_flag = '\x01';
  return CONCAT31((int3)((uint)grim_texture_slot_max_index >> 8),1);
}



/* grim_restore_textures @ 10002b40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* restore texture surfaces after device reset */

int grim_restore_textures(void)

{
  int *piVar1;
  uint in_EAX;
  uint extraout_EAX;
  int iVar2;
  HRESULT HVar3;
  ULONG UVar4;
  uint extraout_EAX_00;
  uint extraout_EAX_01;
  int *piVar5;
  int iVar6;
  IDirect3DSurface8 *local_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (grim_device_lost_flag != '\0') {
    return in_EAX & 0xffffff00;
  }
  grim_noop();
  if (grim_textures_backed_up_flag == '\0') {
    grim_noop();
    if (grim_textures_backed_up_flag == '\0') {
      return extraout_EAX & 0xffffff00;
    }
  }
  iVar6 = 0;
  local_14 = (IDirect3DSurface8 *)0x0;
  if (-1 < grim_texture_slot_max_index) {
    piVar5 = &grim_texture_slots;
    do {
      iVar2 = *piVar5;
      if (((iVar2 != 0) && (*(char *)(iVar2 + 8) != '\0')) && (*(int *)(iVar2 + 0x14) != 0)) {
        grim_noop();
        piVar1 = *(int **)(*piVar5 + 4);
        if (piVar1 != (int *)0x0) {
          iVar2 = (**(code **)(*piVar1 + 0x3c))(piVar1,0,&local_14);
          if (iVar2 < 0) {
            grim_error_text = s_error_texture_recreate;
            grim_noop();
            return extraout_EAX_00 & 0xffffff00;
          }
        }
        HVar3 = (*grim_d3d_device->lpVtbl->CopyRects)
                          (grim_d3d_device,*(IDirect3DSurface8 **)(*piVar5 + 0x14),(RECT *)0x0,0,
                           local_14,(POINT *)0x0);
        if (HVar3 < 0) {
          if (local_14 != (IDirect3DSurface8 *)0x0) {
            UVar4 = (*local_14->lpVtbl->Release)(local_14);
            if (UVar4 == 0) {
              local_14 = (IDirect3DSurface8 *)0x0;
            }
          }
          piVar5 = *(int **)((&grim_texture_slots)[iVar6] + 0x14);
          if (piVar5 != (int *)0x0) {
            iVar2 = (**(code **)(*piVar5 + 8))(piVar5);
            if (iVar2 == 0) {
              *(undefined4 *)((&grim_texture_slots)[iVar6] + 0x14) = 0;
            }
          }
          uStack_10 = CONCAT31(uStack_10._1_3_,1);
          grim_texture_backup_flag1 = uStack_10;
          grim_textures_backed_up_flag = 0;
          grim_error_text = s_error_texture_restore;
          grim_texture_backup_flag2 = uStack_c;
          grim_texture_backup_flag3 = uStack_8;
          grim_texture_backup_flag4 = uStack_4;
          grim_noop();
          return extraout_EAX_01 & 0xffffff00;
        }
        if (local_14 != (IDirect3DSurface8 *)0x0) {
          UVar4 = (*local_14->lpVtbl->Release)(local_14);
          if (UVar4 == 0) {
            local_14 = (IDirect3DSurface8 *)0x0;
          }
        }
        piVar1 = *(int **)(*piVar5 + 0x14);
        if (piVar1 != (int *)0x0) {
          iVar2 = (**(code **)(*piVar1 + 8))(piVar1);
          if (iVar2 == 0) {
            *(undefined4 *)(*piVar5 + 0x14) = 0;
          }
        }
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar6 <= grim_texture_slot_max_index);
  }
  grim_textures_backed_up_flag = 0;
  return CONCAT31((int3)((uint)grim_texture_slot_max_index >> 8),1);
}



/* grim_d3d_init @ 10003e60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* creates the Direct3D8 interface, configures display mode, and opens the window */

int grim_d3d_init(void)

{
  byte bVar1;
  char *pcVar2;
  HRESULT HVar3;
  uint uVar4;
  BOOL BVar5;
  undefined4 uVar6;
  HRSRC pHVar7;
  HGLOBAL pvVar8;
  LPVOID pvVar9;
  int *piVar10;
  int iVar11;
  undefined4 *puVar12;
  D3DDISPLAYMODE DStack_43c;
  D3DADAPTER_IDENTIFIER8 DStack_42c;
  
  grim_device_cooperative = 0;
  grim_d3d8 = (LPDIRECT3D8)0x0;
  grim_d3d_device = (LPDIRECT3DDEVICE8)0x0;
  grim_device_type = D3DDEVTYPE_HAL;
  if ((char)grim_use_ref_device_flag == '\x01') {
    grim_device_type = D3DDEVTYPE_REF;
  }
  grim_d3d8 = Direct3DCreate8(0xdc);
  if (grim_d3d8 == (IDirect3D8 *)0x0) {
    grim_error_text = s_error_d3d_init;
    return 0;
  }
  (*grim_d3d8->lpVtbl->GetDeviceCaps)(grim_d3d8,grim_adapter_index,grim_device_type,(D3DCAPS8 *)&grim_d3d_caps)
  ;
  bVar1 = 0;
  (*grim_d3d8->lpVtbl->GetAdapterIdentifier)(grim_d3d8,grim_adapter_index,2,&DStack_42c);
  pcVar2 = strchr(DStack_42c.Description,0x56);
  if (((((pcVar2 != (char *)0x0) && (pcVar2[1] == 'o')) && (pcVar2[2] == 'o')) &&
      ((pcVar2[3] == 'd' && (pcVar2[4] == 'o')))) && ((pcVar2[5] == 'o' && (pcVar2[6] == '3')))) {
    bVar1 = 1;
  }
  HVar3 = (*grim_d3d8->lpVtbl->GetAdapterDisplayMode)(grim_d3d8,0,&DStack_43c);
  if (HVar3 < 0) {
    grim_error_text = s_error_adapter_display;
    uVar4 = 0;
    if ((grim_d3d8 != (LPDIRECT3D8)0x0) &&
       (uVar4 = (*grim_d3d8->lpVtbl->Release)(grim_d3d8), uVar4 == 0)) {
      grim_d3d8 = (LPDIRECT3D8)0x0;
    }
    return uVar4 & 0xffffff00;
  }
  BVar5 = grim_window_create();
  uVar6 = grim_fullscreen_refresh_rate;
  if ((char)BVar5 == '\0') {
    return BVar5;
  }
  puVar12 = &grim_present_width;
  for (iVar11 = 0xd; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  grim_present_refresh_rate = uVar6;
  if (grim_windowed_mode_flag != '\x01') {
    grim_present_multisample_type = bVar1 + 1;
    grim_present_fullscreen_refresh_rate = 0;
    grim_present_swap_effect = 0x80000000;
  }
  else {
    grim_present_multisample_type = 1;
    grim_texture_format = (IDirect3D8 *)DStack_43c.Format;
  }
  grim_present_windowed = (uint)(grim_windowed_mode_flag == '\x01');
  grim_present_height = grim_backbuffer_height;
  grim_present_width = grim_backbuffer_width;
  grim_present_format = grim_texture_format;
  grim_present_back_buffer_count = 0;
  grim_present_flags = 1;
  grim_present_enable_auto_depth = (uint)(grim_depth_buffer_enabled != '\0');
  grim_present_auto_depth_format = 0x50;
  grim_present_device_window = grim_parent_window_handle;
  if (grim_parent_window_handle == (HWND)0x0) {
    grim_present_device_window = grim_window_handle;
  }
  HVar3 = (*grim_d3d8->lpVtbl->CreateDevice)
                    (grim_d3d8,grim_adapter_index,grim_device_type,grim_window_handle,0x20,
                     (D3DPRESENT_PARAMETERS *)&grim_present_width,&grim_d3d_device);
  if (HVar3 < 0) {
    grim_error_text = s_error_display_mode;
    MessageBoxA((HWND)0x0,s_error_display_mode,&DAT_10053824,0);
    grim_d3d_shutdown();
    uVar4 = grim_window_destroy();
    return uVar4 & 0xffffff00;
  }
  (*grim_d3d8->lpVtbl->GetDeviceCaps)(grim_d3d8,grim_adapter_index,grim_device_type,(D3DCAPS8 *)&grim_d3d_caps)
  ;
  uVar6 = grim_vertex_buffer_create();
  if ((char)uVar6 == '\0') {
    grim_d3d_shutdown();
    uVar4 = grim_window_destroy();
    return uVar4 & 0xffffff00;
  }
  puVar12 = &grim_texture_slots;
  for (iVar11 = 0x100; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  if (grim_preferred_texture_format != (void *)0x0) {
    iVar11 = grim_is_texture_format_supported((uint)grim_preferred_texture_format);
    if ((char)iVar11 == '\0') {
      grim_preferred_texture_format = (void *)0x0;
    }
    else if (grim_preferred_texture_format != (void *)0x0) goto LAB_10004142;
  }
  iVar11 = grim_select_texture_format();
  if ((char)iVar11 == '\0') {
    grim_error_text = s_error_texture_format;
    grim_d3d_shutdown();
    grim_window_destroy();
  }
LAB_10004142:
  grim_d3d_render_states_init();
  pHVar7 = FindResourceA(grim_module_handle,(LPCSTR)0x6f,(LPCSTR)0xa);
  pvVar8 = LoadResource(grim_module_handle,pHVar7);
  pvVar9 = LockResource(pvVar8);
  piVar10 = (int *)SizeofResource(grim_module_handle,pHVar7);
  uVar4 = grim_texture_create_from_memory((int **)grim_d3d_device,pvVar9,piVar10,-1,-1,1,0,
                       grim_preferred_texture_format,1,-1,(int **)0xffffffff,0,0,0,0x1005d3ec);
  if ((int)uVar4 < 0) {
    grim_error_text = s_error_font_load;
    return uVar4 & 0xffffff00;
  }
  pHVar7 = FindResourceA(grim_module_handle,(LPCSTR)0x71,(LPCSTR)0xa);
  pvVar8 = LoadResource(grim_module_handle,pHVar7);
  pvVar9 = LockResource(pvVar8);
  piVar10 = (int *)SizeofResource(grim_module_handle,pHVar7);
  uVar4 = grim_texture_create_from_memory((int **)grim_d3d_device,pvVar9,piVar10,-1,-1,1,0,
                       grim_preferred_texture_format,1,-1,(int **)0xffffffff,0,0,0,0x1005d3f0);
  if ((int)uVar4 < 0) {
    grim_error_text = s_error_splash_load;
    return uVar4 & 0xffffff00;
  }
  grim_backbuffer_surface = (LPDIRECT3DSURFACE8)0x0;
  grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
  grim_d3d8_ptr = grim_d3d8;
  grim_d3d_device_ptr = grim_d3d_device;
  grim_device_cooperative = 1;
  return CONCAT31((int3)((uint)grim_d3d8 >> 8),1);
}



/* grim_d3d_shutdown @ 10004280 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

void grim_d3d_shutdown(void)

{
  void *texture;
  ULONG UVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (grim_backbuffer_surface != (LPDIRECT3DSURFACE8)0x0) {
    UVar1 = (*grim_backbuffer_surface->lpVtbl->Release)(grim_backbuffer_surface);
    if (UVar1 == 0) {
      grim_backbuffer_surface = (LPDIRECT3DSURFACE8)0x0;
    }
  }
  if (grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) {
    UVar1 = (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface);
    if (UVar1 == 0) {
      grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
    }
  }
  if (grim_font_texture != (int *)0x0) {
    iVar2 = (**(code **)(*grim_font_texture + 8))(grim_font_texture);
    if (iVar2 == 0) {
      grim_font_texture = (int *)0x0;
    }
  }
  if (grim_splash_texture != (int *)0x0) {
    iVar2 = (**(code **)(*grim_splash_texture + 8))(grim_splash_texture);
    if (iVar2 == 0) {
      grim_splash_texture = (int *)0x0;
    }
  }
  puVar3 = &grim_texture_slots;
  do {
    texture = (void *)*puVar3;
    if (texture != (void *)0x0) {
      grim_texture_release(texture);
      operator_delete(texture);
      *puVar3 = 0;
    }
    puVar3 = puVar3 + 1;
  } while ((int)puVar3 < 0x1005d804);
  grim_vertex_buffer_release();
  if (grim_d3d_device != (LPDIRECT3DDEVICE8)0x0) {
    (*grim_d3d_device->lpVtbl->Release)(grim_d3d_device);
  }
  grim_d3d_device = (LPDIRECT3DDEVICE8)0x0;
  if (grim_d3d8 != (LPDIRECT3D8)0x0) {
    (*grim_d3d8->lpVtbl->Release)(grim_d3d8);
  }
  grim_d3d8 = (LPDIRECT3D8)0x0;
  return;
}



/* grim_vertex_buffer_create @ 10004350 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

uint grim_vertex_buffer_create(void)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  HRESULT HVar4;
  
  grim_vertex_capacity = 0x100;
  uVar3 = (*grim_d3d_device->lpVtbl->CreateVertexBuffer)
                    (grim_d3d_device,0x1c00,0x218,0,D3DPOOL_SYSTEMMEM,&grim_vertex_buffer);
  if ((int)uVar3 < 0) {
    grim_error_text = s_D3D__Internal__Could_not_create_v_10053ac4;
    return uVar3 & 0xffffff00;
  }
  HVar4 = (*grim_d3d_device->lpVtbl->CreateIndexBuffer)
                    (grim_d3d_device,grim_vertex_capacity * 0xc,0x218,D3DFMT_INDEX16,
                     D3DPOOL_SYSTEMMEM,&grim_index_buffer);
  if (-1 < HVar4) {
    uVar3 = (*grim_index_buffer->lpVtbl->Lock)(grim_index_buffer,0,0,(BYTE **)&grim_index_write_ptr,0x2000);
    if (-1 < (int)uVar3) {
      if (grim_vertex_capacity != 0) {
        sVar2 = 2;
        do {
          *grim_index_write_ptr = sVar2 + -2;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          *grim_index_write_ptr = sVar2 + -1;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          *grim_index_write_ptr = sVar2;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          *grim_index_write_ptr = sVar2;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          *grim_index_write_ptr = sVar2 + 1;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          *grim_index_write_ptr = sVar2 + -2;
          grim_index_write_ptr = grim_index_write_ptr + 1;
          uVar1 = sVar2 + 2;
          sVar2 = sVar2 + 4;
        } while (uVar1 < grim_vertex_capacity);
      }
      (*grim_index_buffer->lpVtbl->Unlock)(grim_index_buffer);
      (*grim_d3d_device->lpVtbl->SetStreamSource)(grim_d3d_device,0,grim_vertex_buffer,0x1c);
      HVar4 = (*grim_d3d_device->lpVtbl->SetIndices)(grim_d3d_device,grim_index_buffer,0);
      return CONCAT31((int3)((uint)HVar4 >> 8),1);
    }
    grim_device_cooperative = 0;
    return uVar3 & 0xffffff00;
  }
  grim_error_text = s_D3D__Internal__Could_not_create_i_10053a94;
  uVar3 = grim_vertex_buffer_release();
  return uVar3 & 0xffffff00;
}



/* grim_vertex_buffer_release @ 100044e0 */

void grim_vertex_buffer_release(void)

{
  if (grim_vertex_buffer != (int *)0x0) {
    (**(code **)(*grim_vertex_buffer + 8))(grim_vertex_buffer);
  }
  grim_vertex_buffer = (int *)0x0;
  if (grim_index_buffer != (int *)0x0) {
    (**(code **)(*grim_index_buffer + 8))(grim_index_buffer);
  }
  grim_index_buffer = (int *)0x0;
  return;
}



/* grim_d3d_render_states_init @ 10004520 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

void grim_d3d_render_states_init(void)

{
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_LIGHTING,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_SPECULARENABLE,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_ZENABLE,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_ZWRITEENABLE,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_FOGENABLE,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_NORMALIZENORMALS,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_CULLMODE,1);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_SHADEMODE,2);
  (*grim_d3d_device->lpVtbl->SetRenderState)
            (grim_d3d_device,D3DRS_DITHERENABLE,grim_dither_enabled & 0xff);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_ALPHATESTENABLE,1);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_ALPHAFUNC,7);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_ALPHAREF,4);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MINFILTER,2);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MAGFILTER,2);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MIPFILTER,0);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG1,2);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG2,0);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,1);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_TEXCOORDINDEX,0);
  (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_TEXCOORDINDEX,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_WRAP0,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_WRAP1,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_WRAP2,0);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_WRAP3,0);
  (*grim_d3d_device->lpVtbl->SetStreamSource)(grim_d3d_device,0,grim_vertex_buffer,0x1c);
  (*grim_d3d_device->lpVtbl->SetIndices)(grim_d3d_device,grim_index_buffer,0);
  (*grim_d3d_device->lpVtbl->SetVertexShader)(grim_d3d_device,0x144);
  (*grim_d3d_device->lpVtbl->SetRenderState)
            (grim_d3d_device,D3DRS_ALPHABLENDENABLE,grim_alpha_blend_enabled & 0xff);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_SRCBLEND,grim_src_blend_mode);
  (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_DESTBLEND,grim_dest_blend_mode);
  return;
}



/* grim_d3d_texture_create_from_file @ 1000cb9c */

/* [binja] int32_t __stdcall sub_1000cb9c(int32_t** arg1, int32_t* arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, int32_t arg6, void* arg7, int32_t arg8, int32_t arg9, int32_t** arg10, int32_t
   arg11, int32_t arg12, int32_t arg13, int32_t arg14) */

int grim_d3d_texture_create_from_file(int **arg1,int *arg2,int arg3,int arg4,int arg5,int arg6,void *arg7,int arg8,
                int arg9,int **arg10,int arg11,int arg12,int arg13,int arg14)

{
  int iVar1;
  int *unaff_ESI;
  int local_14 [2];
  void *local_c;
  int *local_8;
  
  grim_memory_block_zero(local_14);
  iVar1 = grim_crt_file_read_all(local_14,arg2,(int *)0x0,unaff_ESI);
  if (-1 < iVar1) {
    iVar1 = grim_texture_create_from_memory(arg1,local_c,local_8,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,
                         arg13,arg14);
  }
  grim_registry_read_config(local_14);
  return iVar1;
}



/* grim_d3d_set_blend_mode_a @ 1000cc3f */

/* [binja] int32_t __stdcall sub_1000cc3f(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_d3d_set_blend_mode_a(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053c9c)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_blend_mode_a_impl @ 1000cc69 */

/* [binja] float* __stdcall sub_1000cc69(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_blend_mode_a_impl(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar3 = (fVar2 - (fVar1 + fVar1)) + arg6;
  fVar4 = fVar1 * 3.0 - (fVar2 + fVar2);
  *arg1 = (fVar2 - fVar1) * *arg5 + fVar4 * *arg4 + fVar3 * *arg3 + fVar5 * *arg2;
  arg1[1] = fVar5 * arg2[1] + fVar3 * arg3[1] + fVar4 * arg4[1] + (fVar2 - fVar1) * arg5[1];
  return arg1;
}



/* grim_d3d_set_blend_mode_b @ 1000ccf7 */

/* [binja] int32_t __stdcall sub_1000ccf7(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_d3d_set_blend_mode_b(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d14)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_blend_mode_b_impl @ 1000cd21 */

/* [binja] float* __stdcall sub_1000cd21(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_blend_mode_b_impl(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - arg6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + arg6;
  *arg1 = ((fVar2 - fVar1) * *arg5 + fVar3 * *arg4 + fVar4 * *arg3 + fVar5 * *arg2) * 0.5;
  arg1[1] = (fVar5 * arg2[1] + fVar4 * arg3[1] + fVar3 * arg4[1] + (fVar2 - fVar1) * arg5[1]) * 0.5;
  return arg1;
}



/* grim_d3d_set_blend_mode_c @ 1000cdd0 */

/* [binja] int32_t __stdcall sub_1000cdd0(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   float arg5, float arg6) */

int grim_d3d_set_blend_mode_c(int arg1,int arg2,int arg3,int arg4,float arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d18)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_blend_mode_c_impl @ 1000cdff */

/* [binja] float* __stdcall sub_1000cdff(float* arg1, float* arg2, float* arg3, float* arg4, float
   arg5, float arg6) */

float * grim_d3d_set_blend_mode_c_impl(float *arg1,float *arg2,float *arg3,float *arg4,float arg5,float arg6)

{
  *arg1 = (*arg4 - *arg2) * arg6 + (*arg3 - *arg2) * arg5 + *arg2;
  arg1[1] = (arg4[1] - arg2[1]) * arg6 + (arg3[1] - arg2[1]) * arg5 + arg2[1];
  return arg1;
}



/* grim_d3d_set_alpha_test @ 1000ce69 */

void grim_d3d_set_alpha_test(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000ce70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_10053c74)();
  return;
}



/* grim_d3d_set_alpha_test_impl @ 1000cea6 */

/* [binja] float* __stdcall sub_1000cea6(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_alpha_test_impl(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar3 = (fVar2 - (fVar1 + fVar1)) + arg6;
  fVar4 = fVar1 * 3.0 - (fVar2 + fVar2);
  fVar2 = fVar2 - fVar1;
  *arg1 = fVar2 * *arg5 + fVar4 * *arg4 + fVar3 * *arg3 + fVar5 * *arg2;
  arg1[1] = fVar5 * arg2[1] + fVar3 * arg3[1] + fVar4 * arg4[1] + fVar2 * arg5[1];
  arg1[2] = fVar5 * arg2[2] + fVar3 * arg3[2] + fVar4 * arg4[2] + fVar2 * arg5[2];
  return arg1;
}



/* grim_d3d_set_filter_mode_a @ 1000cf54 */

/* [binja] int32_t __stdcall sub_1000cf54(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_d3d_set_filter_mode_a(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d20)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_filter_mode_a_impl @ 1000cf7e */

/* [binja] float* __stdcall sub_1000cf7e(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_filter_mode_a_impl(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - arg6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + arg6;
  fVar2 = fVar2 - fVar1;
  *arg1 = (fVar2 * *arg5 + fVar3 * *arg4 + fVar4 * *arg3 + fVar5 * *arg2) * 0.5;
  arg1[1] = (fVar5 * arg2[1] + fVar4 * arg3[1] + fVar3 * arg4[1] + fVar2 * arg5[1]) * 0.5;
  arg1[2] = (fVar5 * arg2[2] + fVar4 * arg3[2] + fVar3 * arg4[2] + fVar2 * arg5[2]) * 0.5;
  return arg1;
}



/* grim_d3d_set_filter_mode_b @ 1000d04f */

/* [binja] int32_t __stdcall sub_1000d04f(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   float arg5, float arg6) */

int grim_d3d_set_filter_mode_b(int arg1,int arg2,int arg3,int arg4,float arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d24)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_filter_mode_b_impl @ 1000d07e */

/* [binja] float* __stdcall sub_1000d07e(float* arg1, float* arg2, float* arg3, float* arg4, float
   arg5, float arg6) */

float * grim_d3d_set_filter_mode_b_impl(float *arg1,float *arg2,float *arg3,float *arg4,float arg5,float arg6)

{
  *arg1 = (*arg4 - *arg2) * arg6 + (*arg3 - *arg2) * arg5 + *arg2;
  arg1[1] = (arg4[1] - arg2[1]) * arg6 + (arg3[1] - arg2[1]) * arg5 + arg2[1];
  arg1[2] = (arg4[2] - arg2[2]) * arg6 + (arg3[2] - arg2[2]) * arg5 + arg2[2];
  return arg1;
}



/* grim_d3d_set_z_enable @ 1000d173 */

void grim_d3d_set_z_enable(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000d17a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_10053c80)();
  return;
}



/* grim_d3d_set_fog_enable @ 1000d1f9 */

void grim_d3d_set_fog_enable(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000d204. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_10053c90)();
  return;
}



/* grim_d3d_set_fog_params @ 1000d34f */

/* [binja] float* __stdcall sub_1000d34f(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_fog_params(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar4 = (fVar2 - (fVar1 + fVar1)) + arg6;
  fVar3 = fVar1 * 3.0 - (fVar2 + fVar2);
  fVar2 = fVar2 - fVar1;
  *arg1 = fVar2 * *arg5 + fVar3 * *arg4 + fVar4 * *arg3 + fVar5 * *arg2;
  arg1[1] = fVar5 * arg2[1] + fVar4 * arg3[1] + fVar3 * arg4[1] + fVar2 * arg5[1];
  arg1[2] = fVar5 * arg2[2] + fVar4 * arg3[2] + fVar3 * arg4[2] + fVar2 * arg5[2];
  arg1[3] = fVar5 * arg2[3] + fVar4 * arg3[3] + fVar3 * arg4[3] + fVar2 * arg5[3];
  return arg1;
}



/* grim_d3d_set_multitex_op_a @ 1000d420 */

/* [binja] int32_t __stdcall sub_1000d420(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_d3d_set_multitex_op_a(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d2c)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_multitex_op_a_impl @ 1000d44a */

/* [binja] float* __stdcall sub_1000d44a(float* arg1, float* arg2, float* arg3, float* arg4, float*
   arg5, float arg6) */

float * grim_d3d_set_multitex_op_a_impl(float *arg1,float *arg2,float *arg3,float *arg4,float *arg5,float arg6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = arg6 * arg6;
  fVar2 = arg6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - arg6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + arg6;
  fVar2 = fVar2 - fVar1;
  *arg1 = (fVar2 * *arg5 + fVar3 * *arg4 + fVar4 * *arg3 + fVar5 * *arg2) * 0.5;
  arg1[1] = (fVar5 * arg2[1] + fVar4 * arg3[1] + fVar3 * arg4[1] + fVar2 * arg5[1]) * 0.5;
  arg1[2] = (fVar5 * arg2[2] + fVar4 * arg3[2] + fVar3 * arg4[2] + fVar2 * arg5[2]) * 0.5;
  arg1[3] = (fVar5 * arg2[3] + fVar4 * arg3[3] + fVar3 * arg4[3] + fVar2 * arg5[3]) * 0.5;
  return arg1;
}



/* grim_d3d_set_multitex_op_b @ 1000d53d */

/* [binja] int32_t __stdcall sub_1000d53d(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   float arg5, float arg6) */

int grim_d3d_set_multitex_op_b(int arg1,int arg2,int arg3,int arg4,float arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d30)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_d3d_set_multitex_op_b_impl @ 1000d56c */

/* [binja] float* __stdcall sub_1000d56c(float* arg1, float* arg2, float* arg3, float* arg4, float
   arg5, float arg6) */

float * grim_d3d_set_multitex_op_b_impl(float *arg1,float *arg2,float *arg3,float *arg4,float arg5,float arg6)

{
  *arg1 = (*arg4 - *arg2) * arg6 + (*arg3 - *arg2) * arg5 + *arg2;
  arg1[1] = (arg4[1] - arg2[1]) * arg6 + (arg3[1] - arg2[1]) * arg5 + arg2[1];
  arg1[2] = (arg4[2] - arg2[2]) * arg6 + (arg3[2] - arg2[2]) * arg5 + arg2[2];
  arg1[3] = (arg4[3] - arg2[3]) * arg6 + (arg3[3] - arg2[3]) * arg5 + arg2[3];
  return arg1;
}



/* grim_d3d_set_cull_mode @ 1000d766 */

void grim_d3d_set_cull_mode(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000d76d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_10053c64)();
  return;
}



/* grim_d3d_set_dither_enable @ 1000d9af */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_d3d_set_dither_enable(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000d9b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053cec)();
  return;
}



/* grim_d3d_set_fillmode @ 1000dc72 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_d3d_set_fillmode(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000dc79. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053ca0)();
  return;
}



/* grim_d3d_set_wrap_mode @ 1000e012 */

/* [binja] int32_t __stdcall sub_1000e012(float arg1, float arg2, float arg3) */

int grim_d3d_set_wrap_mode(float arg1,float arg2,float arg3)

{
  int iVar1;
  undefined4 in_stack_00000010;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cdc)(arg1,arg2,arg3,in_stack_00000010);
  return iVar1;
}



/* grim_d3d_set_clamp_mode @ 1000e09c */

/* [binja] int32_t __stdcall sub_1000e09c(float arg1, float arg2, float arg3) */

int grim_d3d_set_clamp_mode(float arg1,float arg2,float arg3)

{
  int iVar1;
  undefined4 in_stack_00000010;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cc0)(arg1,arg2,arg3,in_stack_00000010);
  return iVar1;
}



/* grim_d3d_set_mirror_mode @ 1000e126 */

/* [binja] int32_t __stdcall sub_1000e126(float arg1) */

int grim_d3d_set_mirror_mode(float arg1)

{
  int iVar1;
  undefined4 in_stack_00000008;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cd0)(arg1,in_stack_00000008);
  return iVar1;
}



/* grim_d3d_set_mirror_mode_impl @ 1000e142 */

/* [binja] float* __stdcall sub_1000e142(float* arg1, float arg2) */

float * grim_d3d_set_mirror_mode_impl(float *arg1,float arg2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)arg2);
  fVar2 = (float10)fsin((float10)arg2);
  *arg1 = 1.0;
  arg1[1] = 0.0;
  arg1[6] = (float)fVar2;
  arg1[2] = 0.0;
  arg1[3] = 0.0;
  arg1[4] = 0.0;
  arg1[5] = (float)fVar1;
  arg1[7] = 0.0;
  arg1[8] = 0.0;
  arg1[9] = -(float)fVar2;
  arg1[10] = (float)fVar1;
  arg1[0xb] = 0.0;
  arg1[0xc] = 0.0;
  arg1[0xd] = 0.0;
  arg1[0xe] = 0.0;
  arg1[0xf] = 1.0;
  return arg1;
}



/* grim_d3d_set_border_mode @ 1000e1bc */

/* [binja] int32_t __stdcall sub_1000e1bc(float arg1) */

int grim_d3d_set_border_mode(float arg1)

{
  int iVar1;
  undefined4 in_stack_00000008;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cd4)(arg1,in_stack_00000008);
  return iVar1;
}



/* grim_d3d_set_border_mode_impl @ 1000e1d8 */

/* [binja] float* __stdcall sub_1000e1d8(float* arg1, float arg2) */

float * grim_d3d_set_border_mode_impl(float *arg1,float arg2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)arg2);
  fVar2 = (float10)fsin((float10)arg2);
  *arg1 = (float)fVar1;
  arg1[1] = 0.0;
  arg1[2] = -(float)fVar2;
  arg1[3] = 0.0;
  arg1[4] = 0.0;
  arg1[5] = 1.0;
  arg1[6] = 0.0;
  arg1[7] = 0.0;
  arg1[8] = (float)fVar2;
  arg1[9] = 0.0;
  arg1[10] = (float)fVar1;
  arg1[0xb] = 0.0;
  arg1[0xc] = 0.0;
  arg1[0xd] = 0.0;
  arg1[0xe] = 0.0;
  arg1[0xf] = 1.0;
  return arg1;
}



/* grim_d3d_set_mirroronce_mode @ 1000e253 */

/* [binja] int32_t __stdcall sub_1000e253(float arg1) */

int grim_d3d_set_mirroronce_mode(float arg1)

{
  int iVar1;
  undefined4 in_stack_00000008;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cd8)(arg1,in_stack_00000008);
  return iVar1;
}



/* grim_d3d_set_mirroronce_mode_impl @ 1000e26f */

/* [binja] float* __stdcall sub_1000e26f(float* arg1, float arg2) */

float * grim_d3d_set_mirroronce_mode_impl(float *arg1,float arg2)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)fcos((float10)arg2);
  fVar2 = (float10)fsin((float10)arg2);
  *arg1 = (float)fVar1;
  arg1[1] = (float)fVar2;
  arg1[2] = 0.0;
  arg1[3] = 0.0;
  arg1[4] = -(float)fVar2;
  arg1[5] = (float)fVar1;
  arg1[6] = 0.0;
  arg1[7] = 0.0;
  arg1[8] = 0.0;
  arg1[9] = 0.0;
  arg1[10] = 1.0;
  arg1[0xb] = 0.0;
  arg1[0xc] = 0.0;
  arg1[0xd] = 0.0;
  arg1[0xe] = 0.0;
  arg1[0xf] = 1.0;
  return arg1;
}



/* grim_d3d_set_vertex_color_mode @ 1000e2eb */

/* [binja] int32_t __stdcall sub_1000e2eb(int32_t arg1, float arg2) */

int grim_d3d_set_vertex_color_mode(int arg1,float arg2)

{
  int iVar1;
  undefined4 in_stack_0000000c;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053d00)(arg1,arg2,in_stack_0000000c);
  return iVar1;
}



/* grim_d3d_set_vertex_color_mode_impl @ 1000e30b */

/* [binja] float* __stdcall sub_1000e30b(float* arg1, float arg2, float arg3) */

float * grim_d3d_set_vertex_color_mode_impl(float *arg1,float arg2,float arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float10 fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float10 fVar11;
  
  fVar6 = (float10)fcos((float10)arg3);
  fVar11 = (float10)fsin((float10)arg3);
  fVar1 = (float)fVar6;
  fVar2 = (float)fVar11;
  fVar7 = 1.0 - fVar1;
  fVar3 = *(float *)arg2;
  fVar4 = *(float *)((int)arg2 + 4);
  fVar5 = *(float *)((int)arg2 + 8);
  thunk_vec3_normalize();
  fVar8 = fVar4 * fVar3 * fVar7;
  fVar9 = fVar4 * fVar5 * fVar7;
  fVar10 = fVar5 * fVar3 * fVar7;
  *arg1 = fVar3 * fVar3 * fVar7 + fVar1;
  arg1[1] = fVar8 + fVar5 * fVar2;
  arg1[2] = fVar10 - fVar4 * fVar2;
  arg1[3] = 0.0;
  arg1[4] = fVar8 - fVar5 * fVar2;
  arg1[5] = fVar4 * fVar4 * fVar7 + fVar1;
  arg1[6] = fVar3 * fVar2 + fVar9;
  arg1[7] = 0.0;
  arg1[8] = fVar4 * fVar2 + fVar10;
  arg1[9] = fVar9 - fVar3 * fVar2;
  arg1[10] = fVar5 * fVar5 * fVar7 + fVar1;
  arg1[0xb] = 0.0;
  arg1[0xc] = 0.0;
  arg1[0xd] = 0.0;
  arg1[0xe] = 0.0;
  arg1[0xf] = 1.0;
  return arg1;
}



/* grim_d3d_flush_and_present @ 1000e40d */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_d3d_flush_and_present(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000e414. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053cf0)();
  return;
}



/* grim_d3d_set_sound_and_stage @ 1000e502 */

/* [binja] int32_t __stdcall sub_1000e502(float arg1, float arg2, float arg3) */

int grim_d3d_set_sound_and_stage(float arg1,float arg2,float arg3)

{
  int iVar1;
  undefined4 in_stack_00000010;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cf8)(arg1,arg2,arg3,in_stack_00000010);
  return iVar1;
}



/* grim_d3d_set_stage_colorop @ 1000e541 */

/* [binja] int32_t __stdcall sub_1000e541(int32_t arg1, float arg2, int32_t arg3, int32_t arg4,
   int32_t arg5) */

int grim_d3d_set_stage_colorop(int arg1,float arg2,int arg3,int arg4,int arg5)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)PTR_FUN_10053cfc)(arg1,arg2,arg3,arg4,arg5);
  return iVar1;
}



/* grim_d3d_debug_set_mute @ 100101f5 */

/* loads DebugSetMute from d3d8/d3d8d and toggles D3D debug output */

void __cdecl grim_d3d_debug_set_mute(int mute)

{
  HMODULE pHVar1;
  
  if (DAT_1005db64 == (FARPROC)0x0) {
    if (DAT_1005db60 != (FARPROC)0x0) goto LAB_1001027e;
    pHVar1 = GetModuleHandleA("d3d8.dll");
    if (pHVar1 != (HMODULE)0x0) {
      pHVar1 = LoadLibraryA("d3d8.dll");
      if (pHVar1 != (HMODULE)0x0) {
        DAT_1005db64 = GetProcAddress(pHVar1,"DebugSetMute");
      }
    }
    pHVar1 = GetModuleHandleA("d3d8d.dll");
    if (pHVar1 != (HMODULE)0x0) {
      pHVar1 = LoadLibraryA("d3d8d.dll");
      if (pHVar1 != (HMODULE)0x0) {
        DAT_1005db60 = GetProcAddress(pHVar1,"DebugSetMute");
      }
    }
    if (DAT_1005db64 != (FARPROC)0x0) goto LAB_1001026a;
  }
  else {
LAB_1001026a:
    (*DAT_1005db64)(mute);
  }
  if (DAT_1005db60 == (FARPROC)0x0) {
    return;
  }
LAB_1001027e:
                    /* WARNING: Could not recover jumptable at 0x1001027e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_1005db60)();
  return;
}



/* grim_d3dx_sse_feature_init @ 1001bf39 */

/* WARNING: Removing unreachable block (ram,0x1001bf45) */
/* [binja] int32_t __fastcall sub_1001bf39(int32_t arg1) */

int __fastcall grim_d3dx_sse_feature_init(int arg1)

{
  int iVar1;
  
  iVar1 = cpuid_Version_info(1);
  return (uint)((*(uint *)(iVar1 + 8) & 0x800000) != 0);
}



/* grim_select_renderer_backend @ 1001c188 */

/* copies the render backend vtable and selects D3DX/alt paths based on config */

int grim_select_renderer_backend(int force)

{
  uint uVar1;
  int iVar2;
  undefined **ppuVar3;
  undefined **ppuVar4;
  
  if (force == 0) {
    grim_simd_mode = 0xffff;
    ppuVar3 = &grim_math_vtable_default;
    ppuVar4 = &grim_math_vtable_active;
    for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
      *ppuVar4 = *ppuVar3;
      ppuVar3 = ppuVar3 + 1;
      ppuVar4 = ppuVar4 + 1;
    }
  }
  else if (grim_simd_mode == 0xffff) {
    grim_simd_mode = 0;
    ppuVar3 = &grim_math_vtable_default;
    ppuVar4 = &grim_math_vtable_active;
    for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
      *ppuVar4 = *ppuVar3;
      ppuVar3 = ppuVar3 + 1;
      ppuVar4 = ppuVar4 + 1;
    }
    grim_d3dx_math_init(&grim_math_vtable_active);
    iVar2 = grim_registry_read_dword(4,"DisableD3DXPSGP",(LPBYTE)&force);
    if (iVar2 == 0) {
      force = 0;
    }
    if (force != 1) {
      uVar1 = grim_is_processor_feature_present(7);
      if (uVar1 == 0) {
        uVar1 = grim_is_processor_feature_present(10);
        if (uVar1 == 0) {
          uVar1 = grim_is_processor_feature_present(6);
          if (uVar1 != 0) {
            grim_sse_math_init(&grim_math_vtable_active);
            grim_simd_mode = 3;
          }
        }
        else {
          grim_sse2_math_init(&grim_math_vtable_active);
          grim_simd_mode = 2;
        }
      }
      else {
        grim_init_mmx_sse_functions(&grim_math_vtable_active);
        grim_simd_mode = 1;
      }
    }
  }
  return grim_simd_mode;
}



/* grim_render_context_destroy @ 1003dd00 */

void __cdecl grim_render_context_destroy(int param_1)

{
  (**(code **)(*(int *)(param_1 + 4) + 0x24))(param_1,1);
  *(uint *)(param_1 + 0x10) = (-(uint)(*(char *)(param_1 + 0xc) != '\0') & 100) + 100;
  return;
}



/* grim_render_update_state @ 1003e040 */

void __cdecl grim_render_update_state(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  
  piVar3 = param_1;
  puVar4 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x1c);
  param_1[0x5f] = (int)puVar4;
  *puVar4 = grim_jpg_input_fill_buffer;
  puVar4[1] = &LAB_1003e430;
  *(undefined1 *)(puVar4 + 2) = 0;
  iVar2 = param_1[0x5f];
  grim_jpg_input_controller_init(param_1);
  puVar5 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x580);
  iVar6 = 0;
  param_1[0x47] = (int)(puVar5 + 0x40);
  puVar4 = puVar5;
  for (iVar8 = 0x40; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  do {
    *(char *)(iVar6 + (int)(puVar5 + 0x40)) = (char)iVar6;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x100);
  puVar4 = puVar5 + 0x80;
  for (iVar6 = 0x60; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar5 + 0xe0;
  for (iVar6 = 0x60; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = (undefined4 *)param_1[0x47];
  puVar5 = puVar5 + 0x140;
  for (iVar6 = 0x20; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  *(undefined4 *)(iVar2 + 0xc) = 0;
  uVar7 = grim_jpg_input_consume_markers((int)param_1);
  *(char *)(iVar2 + 0x10) = (char)uVar7;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  *(undefined4 *)(iVar2 + 0x18) = 0;
  if ((*(char *)((int)param_1 + 0x4a) == '\0') || ((char)param_1[0x10] == '\0')) {
    *(undefined1 *)(param_1 + 0x16) = 0;
    *(undefined1 *)((int)param_1 + 0x59) = 0;
    *(undefined1 *)((int)param_1 + 0x5a) = 0;
  }
  if (*(char *)((int)param_1 + 0x4a) != '\0') {
    if (*(char *)((int)param_1 + 0x41) != '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x2e;
      (**(code **)*param_1)(param_1);
    }
    if (param_1[0x19] == 3) {
      if (param_1[0x1d] == 0) {
        if ((char)param_1[0x14] == '\0') {
          *(undefined1 *)(param_1 + 0x16) = 1;
        }
        else {
          *(undefined1 *)((int)param_1 + 0x5a) = 1;
        }
      }
      else {
        *(undefined1 *)((int)param_1 + 0x59) = 1;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x16) = 1;
      *(undefined1 *)((int)param_1 + 0x59) = 0;
      *(undefined1 *)((int)param_1 + 0x5a) = 0;
      param_1[0x1d] = 0;
    }
    if ((char)param_1[0x16] != '\0') {
      grim_zlib_deflate_process(param_1);
      *(int *)(iVar2 + 0x14) = param_1[0x69];
    }
    if ((*(char *)((int)param_1 + 0x5a) != '\0') || (*(char *)((int)param_1 + 0x59) != '\0')) {
      grim_zlib_inflate_init2_internal(param_1);
      *(int *)(iVar2 + 0x18) = param_1[0x69];
    }
  }
  if (*(char *)((int)param_1 + 0x41) == '\0') {
    if (*(char *)(iVar2 + 0x10) == '\0') {
      grim_zlib_inflate_process(param_1);
      grim_zlib_inflate_blocks_sync_point(param_1);
    }
    else {
      grim_zlib_inflate_init_internal((int)param_1);
    }
    grim_zlib_inflate_blocks_init((int)param_1,*(char *)((int)param_1 + 0x5a));
  }
  grim_zlib_inflate_codes_free_state(param_1);
  if (*(char *)((int)param_1 + 0xc9) == '\0') {
    if ((char)param_1[0x32] == '\0') {
      grim_zlib_inflate_reset((int)param_1);
    }
    else {
      grim_zlib_inflate_codes_init((int)param_1);
    }
  }
  else {
    *(undefined4 *)(*param_1 + 0x14) = 1;
    (**(code **)*param_1)(param_1);
  }
  if ((*(char *)(param_1[99] + 0x10) != '\0') ||
     (piVar1 = param_1 + 0x10, param_1._0_1_ = '\0', (char)*piVar1 != '\0')) {
    param_1._0_1_ = '\x01';
  }
  grim_png_inflate_init((int)piVar3,(char)param_1);
  if (*(char *)((int)piVar3 + 0x41) == '\0') {
    grim_jpg_data_src_setup(piVar3,'\0');
  }
  (**(code **)(piVar3[1] + 0x18))(piVar3);
  (**(code **)(piVar3[99] + 8))(piVar3);
  if (((piVar3[2] != 0) && ((char)piVar3[0x10] == '\0')) && (*(char *)(piVar3[99] + 0x10) != '\0'))
  {
    iVar6 = piVar3[8];
    if ((char)piVar3[0x32] != '\0') {
      iVar6 = iVar6 * 3 + 2;
    }
    *(undefined4 *)(piVar3[2] + 4) = 0;
    *(int *)(piVar3[2] + 8) = piVar3[0x46] * iVar6;
    *(undefined4 *)(piVar3[2] + 0xc) = 0;
    *(uint *)(piVar3[2] + 0x10) = (*(char *)((int)piVar3 + 0x5a) != '\0') + 2;
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + 1;
  }
  return;
}


