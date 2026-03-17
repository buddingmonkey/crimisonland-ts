/* grim_noop @ 10001160 */

/* debug stub (no-op) */

void grim_noop(void)

{
  return;
}



/* grim_config_save @ 100019f0 */

undefined4 grim_config_save(void)

{
  FILE *_File;
  int iVar1;
  
  _File = fopen(s_crimson_cfg,s_file_mode_wb);
  iVar1 = 0;
  if (_File != (FILE *)0x0) {
    fwrite(&grim_config_data,0x480,1,_File);
    iVar1 = fclose(_File);
  }
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}



/* grim_config_load @ 10001a30 */

undefined4 grim_config_load(void)

{
  FILE *_File;
  long lVar1;
  undefined4 uVar2;
  int iVar3;
  
  _File = fopen(s_crimson_cfg,s_file_mode_read_binary);
  if (_File == (FILE *)0x0) {
    grim_config_save();
    _File = fopen(s_crimson_cfg,s_file_mode_read_binary);
    if (_File == (FILE *)0x0) {
      return 0;
    }
  }
  fseek(_File,0,2);
  lVar1 = ftell(_File);
  if (lVar1 != 0x480) {
    fclose(_File);
    uVar2 = grim_config_save();
    return CONCAT31((int3)((uint)uVar2 >> 8),1);
  }
  fseek(_File,0,0);
  fread(&grim_config_data,0x480,1,_File);
  iVar3 = fclose(_File);
  return CONCAT31((int3)((uint)iVar3 >> 8),1);
}



/* grim_dialog_populate_resolutions @ 10001e90 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

void grim_dialog_populate_resolutions(void)

{
  HWND pHVar1;
  HRESULT HVar2;
  uint wParam;
  WPARAM WVar3;
  char *pcVar4;
  UINT UVar5;
  LPARAM LVar6;
  
  wParam = grim_use_ref_device_flag & 0xff;
  LVar6 = 0;
  UVar5 = 0xf1;
  grim_windowed_supported_flag = (byte)(grim_display_capabilities >> 0x13) & 1;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3ed);
  SendMessageA(pHVar1,UVar5,wParam,LVar6);
  grim_display_mode_saved = grim_vsync_enabled;
  HVar2 = (*grim_d3d8_interface->lpVtbl->CheckDeviceType)
                    (grim_d3d8_interface,0,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,D3DFMT_X8R8G8B8,0);
  LVar6 = 0;
  WVar3 = 0;
  grim_32bit_supported_flag = -1 < HVar2;
  UVar5 = 0x14b;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,LVar6);
  if (grim_windowed_supported_flag != 0) {
    pcVar4 = s_res_640x480_windowed;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_800x600_windowed;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_960x600_widescreen_windowed;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_1024x768_windowed;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  }
  pcVar4 = s_res_640x480x16;
  WVar3 = 0;
  UVar5 = 0x143;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  pcVar4 = s_res_800x600x16;
  WVar3 = 0;
  UVar5 = 0x143;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  pcVar4 = s_res_960x600x16_wide;
  WVar3 = 0;
  UVar5 = 0x143;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  pcVar4 = s_res_1024x768x16;
  WVar3 = 0;
  UVar5 = 0x143;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  if (grim_32bit_supported_flag != '\0') {
    pcVar4 = s_res_640x480x32;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_800x600x32;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_960x600x32_wide;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
    pcVar4 = s_res_1024x768x32;
    WVar3 = 0;
    UVar5 = 0x143;
    pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
    SendMessageA(pHVar1,UVar5,WVar3,(LPARAM)pcVar4);
  }
  if (grim_display_width == 0x280) {
    WVar3 = 0;
  }
  else if (grim_display_width == 800) {
    WVar3 = 1;
  }
  else if (grim_display_width == 0x3c0) {
    WVar3 = 2;
  }
  else if (grim_display_width == 0x400) {
    WVar3 = 3;
  }
  else {
    WVar3 = (-(uint)(grim_display_width != 0x690) & 0xfffffffd) + 4;
  }
  if ((grim_windowed_mode_flag != '\x01') || (grim_windowed_supported_flag == 0)) {
    if (grim_display_bit_depth == 0x10) {
      WVar3 = WVar3 + 4;
    }
    else if (grim_display_bit_depth == 0x20) {
      WVar3 = WVar3 + 8;
    }
    if (grim_windowed_supported_flag == 0) {
      WVar3 = WVar3 - 4;
    }
  }
  LVar6 = 0;
  UVar5 = 0x14e;
  pHVar1 = GetDlgItem(grim_dialog_handle,0x3f9);
  SendMessageA(pHVar1,UVar5,WVar3,LVar6);
  return;
}



/* grim_config_dialog_proc @ 10002120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* dialog procedure for the Grim2D config UI */

int grim_config_dialog_proc(int hwnd,uint msg,uint wparam,int lparam)

{
  undefined4 uVar1;
  HRESULT HVar2;
  LRESULT LVar3;
  char *pcVar4;
  HWND pHVar5;
  UINT UVar6;
  HRESULT HVar7;
  undefined4 *puVar8;
  UINT Adapter;
  bool bVar9;
  UINT UVar10;
  char *pcVar11;
  WPARAM WVar12;
  int iVar13;
  LPARAM LVar14;
  char *pcStack_404;
  char cStack_400;
  undefined4 uStack_3ff;
  char acStack_200 [512];
  
  if (msg == 0x10) {
LAB_10002629:
    grim_dialog_canceled_flag = 1;
LAB_10002631:
    EndDialog((HWND)hwnd,wparam & 0xffff);
  }
  else {
    if (msg == 0x110) {
      iVar13 = 5;
      grim_dialog_handle = hwnd;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f2);
      ShowWindow(pHVar5,iVar13);
      iVar13 = 0;
      pHVar5 = GetDlgItem((HWND)hwnd,0x40b);
      ShowWindow(pHVar5,iVar13);
      SendMessageA((HWND)hwnd,0x80,1,grim_icon_handle);
      SendMessageA((HWND)hwnd,0x80,0,grim_icon_handle);
      GetLocalTime((LPSYSTEMTIME)&grim_local_system_time);
      UVar6 = (*grim_d3d8_interface->lpVtbl->GetAdapterCount)(grim_d3d8_interface);
      Adapter = 0;
      grim_adapter_found_flag = '\0';
      if (0 < (int)UVar6) {
        do {
          (*grim_d3d8_interface->lpVtbl->GetAdapterIdentifier)
                    (grim_d3d8_interface,Adapter,2,(D3DADAPTER_IDENTIFIER8 *)&DAT_10059788);
          if (Adapter == 0) {
            pcVar11 = s_adapter_format;
          }
          else {
            pcVar11 = &DAT_10053308;
          }
          sprintf(acStack_200,pcVar11,&DAT_10059988);
          HVar7 = (*grim_d3d8_interface->lpVtbl->CheckDeviceType)
                            (grim_d3d8_interface,Adapter,D3DDEVTYPE_HAL,D3DFMT_R5G6B5,D3DFMT_R5G6B5,0);
          if ((-1 < HVar7) ||
             (HVar7 = (*grim_d3d8_interface->lpVtbl->CheckDeviceType)
                                (grim_d3d8_interface,Adapter,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,
                                 D3DFMT_X8R8G8B8,0), -1 < HVar7)) {
            pcVar11 = acStack_200;
            WVar12 = 0;
            UVar10 = 0x143;
            pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
            SendMessageA(pHVar5,UVar10,WVar12,(LPARAM)pcVar11);
            grim_adapter_found_flag = '\x01';
          }
          Adapter = Adapter + 1;
        } while ((int)Adapter < (int)UVar6);
      }
      LVar14 = 0;
      UVar10 = 0x14e;
      WVar12 = grim_adapter_index;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
      SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      LVar14 = 0;
      WVar12 = 0;
      UVar10 = 0x147;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
      grim_adapter_index = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      grim_dialog_populate_resolutions();
      if (grim_adapter_found_flag == '\0') {
        pcVar11 = s_error_no_adapters;
        WVar12 = 0;
        UVar10 = 0x143;
        pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
        SendMessageA(pHVar5,UVar10,WVar12,(LPARAM)pcVar11);
        iVar13 = MessageBoxA((HWND)hwnd,s_error_no_adapters_long,
                             s_crimsonland_title,0x33);
        if (iVar13 != 6) {
          grim_dialog_canceled_flag = 1;
          EndDialog((HWND)hwnd,wparam & 0xffff);
        }
      }
      return 1;
    }
    if (msg != 0x111) {
      return 0;
    }
    switch(wparam & 0xffff) {
    case 1000:
      LVar14 = 0;
      WVar12 = 0;
      UVar10 = 0xf0;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3ef);
      LVar3 = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      LVar14 = 0;
      WVar12 = 0;
      grim_vsync_enabled = LVar3 != 0;
      UVar10 = 0x147;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f9);
      WVar12 = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      cStack_400 = '\0';
      puVar8 = &uStack_3ff;
      for (iVar13 = 0x7f; iVar13 != 0; iVar13 = iVar13 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      *(undefined2 *)puVar8 = 0;
      *(undefined1 *)((int)puVar8 + 2) = 0;
      pcVar11 = &cStack_400;
      UVar10 = 0x148;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f9);
      SendMessageA(pHVar5,UVar10,WVar12,(LPARAM)pcVar11);
      pcVar11 = strstr(&cStack_400,s_window_keyword);
      grim_is_windowed_resolution = pcVar11 != (char *)0x0;
      pcVar11 = strchr(&cStack_400,0x78);
      *pcVar11 = '\0';
      pcVar4 = strchr(pcVar11 + 1,0x78);
      if (pcVar4 == (char *)0x0) {
        pcStack_404 = &DAT_10053490;
      }
      else {
        *pcVar4 = '\0';
        pcStack_404 = pcVar4 + 1;
        pcVar4[4] = '\0';
      }
      grim_parsed_width = atoi(&cStack_400);
      grim_parsed_height = atoi(pcVar11 + 1);
      grim_display_width = grim_parsed_width;
      grim_display_height = grim_parsed_height;
      iVar13 = atoi(pcStack_404);
      bVar9 = iVar13 == 0x10;
      grim_16bit_color_mode = CONCAT31(grim_16bit_color_mode._1_3_,bVar9);
      grim_display_bit_depth = (-(uint)bVar9 & 0xfffffff0) + 0x20;
      sprintf(&cStack_400,s_resolution_format,grim_parsed_width,grim_parsed_height,bVar9);
      grim_dialog_canceled_flag = 0;
      LVar14 = 0;
      WVar12 = 0;
      UVar10 = 0x147;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
      grim_adapter_index = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      goto LAB_10002631;
    case 0x3e9:
      goto LAB_10002629;
    case 0x3f1:
      LVar14 = 0;
      WVar12 = 0;
      UVar10 = 0x147;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
      grim_adapter_index = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      grim_dialog_populate_resolutions();
      return 0;
    case 0x3f2:
      HVar2 = HlinkNavigateString((IUnknown *)0x0,s_website_url);
      if (HVar2 < 0) {
        MessageBoxA((HWND)0x0,s_error_browser_open,s_crimsonland_title,
                    0x30);
        return 0;
      }
      break;
    case 0x3f5:
      UVar10 = WinExec(s_manual_path,3);
      if (UVar10 < 0x20) {
        MessageBoxA((HWND)0x0,s_error_manual_open,s_crimsonland_title,
                    0x30);
        return 0;
      }
      break;
    case 0x3fb:
      uVar1 = grim_config_load();
      if ((char)uVar1 != '\0') {
        DialogBoxParamA(grim_module_handle,(LPCSTR)0x89,(HWND)hwnd,(DLGPROC)&LAB_10001ad0,0);
        return 0;
      }
      MessageBoxA((HWND)hwnd,s_error_config_load,
                  s_parental_lock_title,0x40);
      return 0;
    case 0x3fc:
      LVar14 = 0;
      WVar12 = 0;
      UVar10 = 0x147;
      pHVar5 = GetDlgItem((HWND)hwnd,0x3f1);
      grim_adapter_index = SendMessageA(pHVar5,UVar10,WVar12,LVar14);
      DialogBoxParamA(grim_module_handle,(LPCSTR)0x8a,(HWND)hwnd,(DLGPROC)&LAB_10001170,0);
      return 0;
    }
  }
  return 0;
}



/* grim_window_create @ 10002680 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* registers the window class and creates the main game window */

BOOL grim_window_create(void)

{
  HWND hWndParent;
  int nHeight;
  int nWidth;
  int iVar1;
  int iVar2;
  uint uVar3;
  WINBOOL WVar4;
  DWORD dwExStyle;
  DWORD dwStyle;
  HMENU hMenu;
  HMODULE hInstance;
  LPVOID lpParam;
  tagRECT local_10;
  
  if (grim_module_instance == (HMODULE)0x0) {
    grim_module_instance = GetModuleHandleA((LPCSTR)0x0);
  }
  grim_wndclass_size = 0x30;
  grim_wndclass_style = 3;
  grim_wndclass_wndproc = &LAB_100033b0;
  grim_wndclass_cls_extra = 0;
  grim_wndclass_wnd_extra = 0;
  grim_wndclass_icon = grim_icon_handle;
  grim_wndclass_instance = grim_module_instance;
  grim_wndclass_cursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  grim_wndclass_background = GetStockObject(4);
  grim_wndclass_menu_name = 0;
  grim_wndclass_class_name = s_crimson_class_name;
  grim_wndclass_small_icon = grim_icon_handle;
  RegisterClassExA((WNDCLASSEXA *)&grim_wndclass_struct);
  lpParam = (LPVOID)0x0;
  if (grim_windowed_mode_flag == '\0') {
    hMenu = (HMENU)0x0;
    hInstance = grim_module_instance;
    hWndParent = GetDesktopWindow();
    nHeight = GetSystemMetrics(1);
    nWidth = GetSystemMetrics(0);
    dwStyle = 0x80000000;
    dwExStyle = 8;
    iVar1 = 0;
    iVar2 = 0;
  }
  else {
    iVar1 = GetSystemMetrics(0);
    iVar2 = GetSystemMetrics(1);
    local_10.left = iVar1 / 2 - (grim_backbuffer_width >> 1);
    local_10.right = (grim_backbuffer_width >> 1) + iVar1 / 2;
    local_10.top = iVar2 / 2 - (grim_backbuffer_height >> 1);
    local_10.bottom = (grim_backbuffer_height >> 1) + iVar2 / 2;
    AdjustWindowRectEx(&local_10,0xcb0000,0,0x40000);
    lpParam = (LPVOID)0x0;
    hMenu = (HMENU)0x0;
    hInstance = grim_module_instance;
    hWndParent = GetDesktopWindow();
    nHeight = local_10.bottom - local_10.top;
    nWidth = local_10.right - local_10.left;
    dwStyle = 0xcb0000;
    dwExStyle = 0x40000;
    iVar1 = local_10.left;
    iVar2 = local_10.top;
  }
  grim_window_handle = CreateWindowExA(dwExStyle,grim_wndclass_class_name,grim_window_title,dwStyle,iVar1,iVar2,nWidth,
                                 nHeight,hWndParent,hMenu,hInstance,lpParam);
  if (grim_window_handle == (HWND)0x0) {
    grim_error_text = s_error_window_create;
    uVar3 = grim_window_destroy();
    return uVar3 & 0xffffff00;
  }
  ShowWindow(grim_window_handle,1);
  UpdateWindow(grim_window_handle);
  SetFocus(grim_window_handle);
  ShowWindow(grim_window_handle,1);
  WVar4 = UpdateWindow(grim_window_handle);
  return CONCAT31((int3)((uint)WVar4 >> 8),1);
}



/* grim_window_destroy @ 10002880 */

/* posts quit and destroys the main window */

BOOL grim_window_destroy(void)

{
  WINBOOL WVar1;
  
  PostQuitMessage(0);
  if (grim_window_handle != (HWND)0x0) {
    DestroyWindow(grim_window_handle);
  }
  if (grim_parent_window_handle != 0) {
    DestroyWindow(grim_window_handle);
  }
  WVar1 = UnregisterClassA(grim_wndclass_class_name,grim_wndclass_instance);
  return WVar1;
}



/* grim_device_reset @ 10002cf0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

undefined4 grim_device_reset(void)

{
  int *piVar1;
  ULONG UVar2;
  int iVar3;
  HRESULT HVar4;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  int *piVar5;
  int iVar6;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  grim_noop();
  if ((grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) &&
     (UVar2 = (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface), UVar2 == 0
     )) {
    grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
  }
  if ((grim_backbuffer_surface != (LPDIRECT3DSURFACE8)0x0) &&
     (UVar2 = (*grim_backbuffer_surface->lpVtbl->Release)(grim_backbuffer_surface), UVar2 == 0)) {
    grim_backbuffer_surface = (LPDIRECT3DSURFACE8)0x0;
  }
  iVar6 = 0;
  if (-1 < grim_texture_slot_max_index) {
    piVar5 = &grim_texture_slots;
    do {
      iVar3 = *piVar5;
      if ((((iVar3 != 0) && (*(char *)(iVar3 + 8) != '\0')) &&
          (piVar1 = *(int **)(iVar3 + 4), piVar1 != (int *)0x0)) &&
         (iVar3 = (**(code **)(*piVar1 + 8))(piVar1), iVar3 == 0)) {
        *(undefined4 *)(*piVar5 + 4) = 0;
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar6 <= grim_texture_slot_max_index);
  }
  iVar6 = (*grim_d3d_device->lpVtbl->Reset)
                    (grim_d3d_device,(D3DPRESENT_PARAMETERS *)&grim_present_width);
  do {
    if (iVar6 == 0) {
      grim_d3d_render_states_init();
      iVar6 = 0;
      if (-1 < grim_texture_slot_max_index) {
        piVar5 = &grim_texture_slots;
        do {
          iVar3 = *piVar5;
          if (((iVar3 != 0) && (*(char *)(iVar3 + 8) != '\0')) &&
             (HVar4 = (*grim_d3d_device->lpVtbl->CreateTexture)
                                (grim_d3d_device,*(UINT *)(iVar3 + 0xc),*(UINT *)(iVar3 + 0x10),1,1,
                                 grim_texture_format,D3DPOOL_DEFAULT,
                                 (IDirect3DTexture8 **)(iVar3 + 4)), HVar4 < 0)) {
            grim_error_text = s_error_texture_recreate;
            grim_noop();
            *(undefined4 *)(*piVar5 + 4) = 0;
            Sleep(200);
          }
          iVar6 = iVar6 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar6 <= grim_texture_slot_max_index);
      }
      iVar6 = grim_restore_textures();
      if ((char)iVar6 == '\0') {
        grim_noop();
      }
      grim_noop();
      grim_device_reset_attempts = 0;
      return 0;
    }
    grim_device_reset_attempts = grim_device_reset_attempts + 1;
    Sleep(500);
    if (3 < grim_device_reset_attempts) {
      grim_error_text = s_error_device_restore;
      iVar6 = MessageBoxA(grim_window_handle,s_error_device_restore,&DAT_10053824,5);
      if (iVar6 == 2) {
        grim_noop();
        return 0x88760869;
      }
      iVar6 = 0;
      if (-1 < grim_texture_slot_max_index) {
        piVar5 = &grim_texture_slots;
        do {
          iVar3 = *piVar5;
          if ((iVar3 != 0) && (*(char *)(iVar3 + 8) != '\0')) {
            piVar1 = *(int **)(iVar3 + 0x14);
            if ((piVar1 != (int *)0x0) && (iVar3 = (**(code **)(*piVar1 + 8))(piVar1), iVar3 == 0))
            {
              *(undefined4 *)(*piVar5 + 0x14) = 0;
            }
            piVar1 = *(int **)(*piVar5 + 4);
            if ((piVar1 != (int *)0x0) && (iVar3 = (**(code **)(*piVar1 + 8))(piVar1), iVar3 == 0))
            {
              *(undefined4 *)(*piVar5 + 4) = 0;
            }
            grim_texture_backup_flag1 = CONCAT31((int3)((uint)unaff_EBP >> 8),1);
            grim_texture_backup_flag3 = uStack_10;
            grim_texture_backup_flag4 = uStack_c;
            grim_texture_backup_flag2 = unaff_EBX;
            unaff_EBP = grim_texture_backup_flag1;
          }
          iVar6 = iVar6 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar6 <= grim_texture_slot_max_index);
      }
    }
    iVar6 = (*grim_d3d_device->lpVtbl->Reset)
                      (grim_d3d_device,(D3DPRESENT_PARAMETERS *)&grim_present_width);
  } while( true );
}



/* grim_timer_update @ 10002f80 */

/* [binja] uint32_t __fastcall sub_10002f80(void* arg1) */

uint __fastcall grim_timer_update(void *arg1)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  
  DVar2 = timeGetTime();
  iVar1 = *(int *)((int)arg1 + 4);
  if (iVar1 < 0) {
    *(DWORD *)((int)arg1 + 4) = DVar2;
    return DVar2 & 0xffffff00;
  }
  *(DWORD *)((int)arg1 + 4) = DVar2;
  uVar3 = *(int *)((int)arg1 + 8) + (DVar2 - iVar1);
  *(uint *)((int)arg1 + 8) = uVar3;
  if ((int)uVar3 < 0x1e) {
    return uVar3 & 0xffffff00;
  }
  *(int *)((int)arg1 + 8) = (int)uVar3 % 0x1e;
  return CONCAT31((int3)((uint)((int)uVar3 / 0x1e) >> 8),1);
}



/* grim_state_init @ 10002fc0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t __fastcall sub_10002fc0(char* arg1) */

int __fastcall grim_state_init(char *arg1)

{
  int iVar1;
  undefined4 *puVar2;
  tagRECT local_10;
  
  grim_noop();
  *arg1 = '\0';
  arg1[4] = -1;
  arg1[5] = -1;
  arg1[6] = -1;
  arg1[7] = -1;
  arg1[8] = '\0';
  arg1[9] = '\0';
  arg1[10] = '\0';
  arg1[0xb] = '\0';
  arg1[0x1c] = '\0';
  arg1[0x1d] = '\0';
  arg1[0x1e] = '\0';
  arg1[0x1f] = '\0';
  arg1[0x24] = '\0';
  arg1[0x25] = '\0';
  arg1[0x26] = '\0';
  arg1[0x27] = '\0';
  arg1[0x29] = '\0';
  arg1[0x28] = '\0';
  arg1[0x14] = '\0';
  arg1[0x15] = '\0';
  arg1[0x16] = '\0';
  arg1[0x17] = '\0';
  GetClientRect(grim_window_handle,&local_10);
  *(LONG *)(arg1 + 0x10) = local_10.right;
  *(LONG *)(arg1 + 0xc) = local_10.bottom;
  *(undefined4 *)(arg1 + 0x10) = grim_backbuffer_width;
  *(undefined4 *)(arg1 + 0xc) = grim_backbuffer_height;
  puVar2 = &grim_working_directory;
  for (iVar1 = 0x41; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _getcwd((char *)&grim_working_directory,0x104);
  local_10.left = local_10.left & 0xffffff00;
  grim_viewport_left = local_10.left;
  grim_viewport_top = local_10.top;
  grim_viewport_bottom = local_10.bottom;
  grim_viewport_right = local_10.right;
  return CONCAT31((int3)((uint)local_10.bottom >> 8),1);
}



/* grim_timer_tick @ 10003090 */

/* [binja] int32_t sub_10003090() */

int __fastcall grim_timer_tick(void)

{
  uint uVar1;
  int extraout_EAX;
  void *in_ECX;
  
  uVar1 = grim_timer_update(in_ECX);
  if ((char)uVar1 != '\0') {
    grim_noop();
    return extraout_EAX;
  }
  return uVar1;
}



/* grim_device_test_and_reset @ 100030b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

undefined4 grim_device_test_and_reset(void)

{
  int *piVar1;
  HRESULT HVar2;
  ULONG UVar3;
  int iVar4;
  int extraout_EAX;
  uint uVar5;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  int *piVar6;
  int iVar7;
  undefined4 uStack_10;
  
  uVar5 = 0;
  if (grim_d3d_device == (LPDIRECT3DDEVICE8)0x0) {
LAB_100033a0:
    return uVar5 & 0xffffff00;
  }
  HVar2 = (*grim_d3d_device->lpVtbl->TestCooperativeLevel)(grim_d3d_device);
  grim_device_cooperative = HVar2 == 0;
  if ((!(bool)grim_device_cooperative) && (HVar2 == -0x7789f797)) {
    Sleep(100);
    if ((grim_render_target_surface != (LPDIRECT3DSURFACE8)0x0) &&
       (UVar3 = (*grim_render_target_surface->lpVtbl->Release)(grim_render_target_surface),
       UVar3 == 0)) {
      grim_render_target_surface = (LPDIRECT3DSURFACE8)0x0;
    }
    if ((grim_backbuffer_surface != (LPDIRECT3DSURFACE8)0x0) &&
       (UVar3 = (*grim_backbuffer_surface->lpVtbl->Release)(grim_backbuffer_surface), UVar3 == 0)) {
      grim_backbuffer_surface = (LPDIRECT3DSURFACE8)0x0;
    }
    iVar7 = 0;
    if (-1 < grim_texture_slot_max_index) {
      piVar6 = &grim_texture_slots;
      do {
        iVar4 = *piVar6;
        if ((((iVar4 != 0) && (*(char *)(iVar4 + 8) != '\0')) &&
            (piVar1 = *(int **)(iVar4 + 4), piVar1 != (int *)0x0)) &&
           (iVar4 = (**(code **)(*piVar1 + 8))(piVar1), iVar4 == 0)) {
          *(undefined4 *)(*piVar6 + 4) = 0;
        }
        iVar7 = iVar7 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar7 <= grim_texture_slot_max_index);
    }
    HVar2 = (*grim_d3d_device->lpVtbl->Reset)
                      (grim_d3d_device,(D3DPRESENT_PARAMETERS *)&grim_present_width);
    if (HVar2 == 0) {
      grim_d3d_render_states_init();
      iVar7 = 0;
      if (-1 < grim_texture_slot_max_index) {
        piVar6 = &grim_texture_slots;
        do {
          iVar4 = *piVar6;
          if (((iVar4 != 0) && (*(char *)(iVar4 + 8) != '\0')) &&
             (HVar2 = (*grim_d3d_device->lpVtbl->CreateTexture)
                                (grim_d3d_device,*(UINT *)(iVar4 + 0xc),*(UINT *)(iVar4 + 0x10),1,1,
                                 grim_texture_format,D3DPOOL_DEFAULT,
                                 (IDirect3DTexture8 **)(iVar4 + 4)), HVar2 < 0)) {
            grim_error_text = s_error_texture_recreate;
            *(undefined4 *)(*piVar6 + 4) = 0;
            grim_noop();
            grim_noop();
          }
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar7 <= grim_texture_slot_max_index);
      }
      iVar7 = grim_restore_textures();
      grim_device_reset_attempts = 0;
      return CONCAT31((int3)((uint)iVar7 >> 8),1);
    }
    grim_device_reset_attempts = grim_device_reset_attempts + 1;
    Sleep(500);
    HVar2 = extraout_EAX;
    if (grim_device_reset_attempts == 5) {
      iVar7 = 0;
      HVar2 = grim_texture_slot_max_index;
      if (grim_texture_slot_max_index < 0) goto LAB_10003396;
      piVar6 = &grim_texture_slots;
      do {
        iVar4 = *piVar6;
        if ((iVar4 != 0) && (*(char *)(iVar4 + 8) != '\0')) {
          piVar1 = *(int **)(iVar4 + 0x14);
          if ((piVar1 != (int *)0x0) && (iVar4 = (**(code **)(*piVar1 + 8))(piVar1), iVar4 == 0)) {
            *(undefined4 *)(*piVar6 + 0x14) = 0;
          }
          piVar1 = *(int **)(*piVar6 + 4);
          if ((piVar1 != (int *)0x0) && (iVar4 = (**(code **)(*piVar1 + 8))(piVar1), iVar4 == 0)) {
            *(undefined4 *)(*piVar6 + 4) = 0;
          }
          grim_texture_backup_flag1 = CONCAT31((int3)((uint)unaff_ESI >> 8),1);
          grim_texture_backup_flag4 = uStack_10;
          grim_texture_backup_flag2 = unaff_EBP;
          grim_texture_backup_flag3 = unaff_EBX;
          unaff_ESI = grim_texture_backup_flag1;
        }
        iVar7 = iVar7 + 1;
        piVar6 = piVar6 + 1;
        HVar2 = grim_texture_slot_max_index;
      } while (iVar7 <= grim_texture_slot_max_index);
    }
    if (6 < grim_device_reset_attempts) {
      grim_error_text = s_error_device_restore;
      uVar5 = MessageBoxA(grim_window_handle,s_error_device_restore,&DAT_10053824,5);
      if (uVar5 == 2) goto LAB_100033a0;
      iVar7 = 0;
      HVar2 = grim_texture_slot_max_index;
      if (-1 < grim_texture_slot_max_index) {
        piVar6 = &grim_texture_slots;
        do {
          iVar4 = *piVar6;
          if ((iVar4 != 0) && (*(char *)(iVar4 + 8) != '\0')) {
            piVar1 = *(int **)(iVar4 + 0x14);
            if ((piVar1 != (int *)0x0) && (iVar4 = (**(code **)(*piVar1 + 8))(piVar1), iVar4 == 0))
            {
              *(undefined4 *)(*piVar6 + 0x14) = 0;
            }
            piVar1 = *(int **)(*piVar6 + 4);
            if ((piVar1 != (int *)0x0) && (iVar4 = (**(code **)(*piVar1 + 8))(piVar1), iVar4 == 0))
            {
              *(undefined4 *)(*piVar6 + 4) = 0;
            }
            grim_texture_backup_flag1 = CONCAT31((int3)((uint)unaff_ESI >> 8),1);
            grim_texture_backup_flag4 = uStack_10;
            grim_texture_backup_flag2 = unaff_EBP;
            grim_texture_backup_flag3 = unaff_EBX;
            unaff_ESI = grim_texture_backup_flag1;
          }
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 1;
          HVar2 = grim_texture_slot_max_index;
        } while (iVar7 <= grim_texture_slot_max_index);
      }
    }
  }
LAB_10003396:
  return CONCAT31((int3)((uint)HVar2 >> 8),1);
}



/* grim_main_loop @ 10003c00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */

undefined4 grim_main_loop(void)

{
  float fVar1;
  char cVar2;
  WINBOOL WVar3;
  HRESULT HVar4;
  int iVar5;
  float *pfVar6;
  tagMSG *ptVar7;
  tagMSG local_1c;
  
  ptVar7 = &local_1c;
  for (iVar5 = 7; iVar5 != 0; iVar5 = iVar5 + -1) {
    ptVar7->hwnd = (HWND)0x0;
    ptVar7 = (tagMSG *)&ptVar7->message;
  }
  PeekMessageA(&local_1c,(HWND)0x0,0,0,0);
  grim_input_init();
  grim_input_update();
  grim_input_init();
  grim_input_update();
  grim_input_update();
  grim_state_init(&grim_frame_timer);
  SetFocus(grim_window_handle);
  SetForegroundWindow(grim_window_handle);
  if (grim_window_handle != (HWND)0x0) {
    do {
      while( true ) {
        do {
          while( true ) {
            while( true ) {
              if (local_1c.message == 0x12) goto LAB_10003e30;
              WVar3 = PeekMessageA(&local_1c,(HWND)0x0,0,0,1);
              if (WVar3 == 0) break;
              TranslateMessage(&local_1c);
              DispatchMessageA(&local_1c);
            }
            if (grim_device_lost_flag == '\0') {
              grim_input_update();
            }
            if ((((grim_paused_flag == '\0') && (grim_device_lost_flag == '\0')) && (grim_device_cooperative != '\0'))
               && (grim_suspended_flag == '\0')) {
              if (grim_keyboard_enabled_flag != '\0') {
                grim_keyboard_poll();
                pfVar6 = (float *)&grim_key_cooldown_table;
                do {
                  fVar1 = *pfVar6 - grim_frame_delta_time;
                  *pfVar6 = fVar1;
                  if (fVar1 < 0.0) {
                    *pfVar6 = 0.0;
                  }
                  pfVar6 = pfVar6 + 1;
                } while ((int)pfVar6 < 0x1005a458);
              }
              grim_joystick_poll();
              grim_joystick_state_ptr = &grim_joystick_device_state;
              if (grim_hide_cursor_flag == '\0') {
                grim_prev_mouse_x = grim_mouse_x;
                grim_prev_mouse_y = grim_mouse_y;
                grim_mouse_poll();
              }
            }
            grim_device_cooperative = '\0';
            if (grim_device_lost_flag != '\0') {
              grim_suspended_flag = '\x01';
              grim_timer_tick();
            }
            if (grim_suspended_flag == '\0') break;
            if (grim_device_lost_flag == '\0') {
              Sleep(0x32);
            }
          }
        } while ((grim_device_lost_flag != '\0') || (grim_d3d_device == (LPDIRECT3DDEVICE8)0x0));
        HVar4 = (*grim_d3d_device->lpVtbl->TestCooperativeLevel)(grim_d3d_device);
        grim_device_cooperative = HVar4 == 0;
        if (!(bool)grim_device_cooperative) break;
        if (grim_needs_device_restore_flag != '\0') {
          (*grim_on_device_restore_callback)();
          grim_needs_device_restore_flag = '\0';
        }
        cVar2 = (*grim_frame_callback)();
        if (cVar2 == '\0') goto LAB_10003e30;
        if (grim_render_callback_ptr != (int *)0x0) {
          (**(code **)(*grim_render_callback_ptr + 0x14))();
        }
        if (grim_render_disabled == '\0') {
          (*grim_d3d_device->lpVtbl->Present)
                    (grim_d3d_device,(RECT *)0x0,(RECT *)0x0,(HWND)0x0,(RGNDATA *)0x0);
        }
      }
      Sleep(500);
      HVar4 = (*grim_d3d_device->lpVtbl->TestCooperativeLevel)(grim_d3d_device);
      grim_device_cooperative = HVar4 == 0;
    } while ((HVar4 != -0x7789f797) || (iVar5 = grim_device_reset(), iVar5 != -0x7789f797));
  }
LAB_10003e30:
  timeEndPeriod(1);
  thunk_grim_bitmap_delete(&grim_frame_timer);
  if (grim_hide_cursor_flag != '\0') {
    ShowCursor(1);
  }
  grim_window_destroy();
  return 0;
}



/* grim_engine_full_init @ 100052f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_engine_full_init(void)

{
  char cVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined4 *puVar11;
  char *pcVar12;
  int local_14;
  uint local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  _DAT_1005cbf8 = local_10;
  DAT_1005a47c = 0;
  grim_config_var1_table = 0;
  DAT_1005a480 = 0;
  grim_config_var0_table = 0;
  _grim_config_var2_table = 0;
  _grim_config_var3_table = 0;
  puVar9 = &grim_config_var0_table;
  puVar11 = &DAT_1005cb98;
  for (iVar4 = 0x1fc; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar11 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar11 = puVar11 + 1;
  }
  DAT_1005a484 = 0;
  DAT_1005a478 = 0;
  _DAT_1005ce5c = local_c;
  _DAT_1005ce58 = local_10;
  _DAT_1005ce64 = &LAB_10001140;
  _DAT_1005cbe8 = local_10;
  _DAT_1005ce60 = local_8;
  _DAT_1005cbf4 = &LAB_10001150;
  _DAT_1005cbf0 = local_8;
  _DAT_1005cbec = local_c;
  _DAT_1005cbe4 = &LAB_10001150;
  _DAT_1005cbdc = local_c;
  _DAT_1005cbd8 = local_10;
  _DAT_1005cc04 = &DAT_10053824;
  uVar5 = local_10 >> 8;
  local_10 = uVar5 << 8;
  _DAT_1005cbe0 = local_8;
  _grim_windowed_mode_flag = local_10;
  _DAT_1005cbfc = local_c;
  _DAT_1005cc00 = local_8;
  _DAT_1005cc14 = local_4;
  _DAT_1005cc0c = local_c;
  _DAT_1005cc10 = local_8;
  grim_display_height = 0x1e0;
  _DAT_1005ce2c = local_c;
  _DAT_1005ce30 = local_8;
  _DAT_1005ce34 = local_4;
  grim_display_width = 0x10;
  _DAT_1005ce1c = local_c;
  _DAT_1005ce20 = local_8;
  local_10 = uVar5 << 8;
  _DAT_1005ce24 = local_4;
  _grim_keyboard_enabled_flag = local_10;
  _DAT_1005cc3c = local_c;
  local_10 = uVar5 << 8;
  _DAT_1005cc44 = local_4;
  _DAT_1005cc48 = local_10;
  _DAT_1005cc50 = local_8;
  _DAT_1005cc54 = local_4;
  _DAT_1005cc40 = local_8;
  _DAT_1005cc6c = local_c;
  _DAT_1005cc70 = local_8;
  _DAT_1005cc4c = local_c;
  local_10 = uVar5 << 8;
  _DAT_1005cc68 = local_10;
  _DAT_1005cebc = local_c;
  _DAT_1005cec0 = local_8;
  local_10 = uVar5 << 8;
  _DAT_1005cec4 = local_4;
  _grim_hide_cursor_flag = local_10;
  _DAT_1005cc5c = local_c;
  _DAT_1005cc60 = local_8;
  local_10 = uVar5 << 8;
  _DAT_1005cc64 = local_4;
  _DAT_1005cc74 = local_4;
  grim_texture_backup_flag1 = local_10;
  grim_texture_backup_flag2 = local_c;
  grim_texture_backup_flag3 = local_8;
  local_10 = CONCAT31(SUB43(_DAT_1005cbf8,1),1);
  grim_texture_backup_flag4 = local_4;
  grim_dither_enabled = local_10;
  _DAT_1005d10c = local_c;
  _DAT_1005d110 = local_8;
  _DAT_1005d114 = local_4;
  _DAT_1005d118 = 0x3f800000;
  _DAT_1005d11c = local_c;
  _DAT_1005d120 = local_8;
  _DAT_1005d124 = local_4;
  _grim_font_texture_bound = 0x3f800000;
  _DAT_1005ccfc = local_c;
  _DAT_1005cd00 = local_8;
  _DAT_1005cd04 = local_4;
  DAT_1005cd08 = 0x3f800000;
  grim_fullscreen_refresh_rate = 1;
  _DAT_1005cd0c = local_c;
  _DAT_1005cd10 = local_8;
  _DAT_1005cd14 = local_4;
  grim_viewport_top = local_c;
  _DAT_1005ccac = local_c;
  grim_viewport_left = 0x3f800001;
  grim_viewport_bottom = local_4;
  grim_src_blend_mode = 5;
  grim_viewport_right = local_8;
  _DAT_1005ccb0 = local_8;
  _DAT_1005ccbc = local_c;
  grim_alpha_blend_enabled = 0x3f800001;
  _DAT_1005ccc0 = local_8;
  grim_dest_blend_mode = 6;
  _DAT_1005ccb4 = local_4;
  _DAT_1005cccc = local_c;
  _DAT_1005ccd0 = local_8;
  _DAT_1005ccc4 = local_4;
  DAT_1005b288 = 0x3f000000;
  DAT_1005b28c = 0x3f800000;
  _DAT_1005ccd4 = local_4;
  grim_uv_v0 = 0;
  grim_uv_u1 = 0x3f800000;
  grim_joystick_deadzone = 0x42c80000;
  grim_joystick_x_center = 0;
  grim_joystick_y_center = 0;
  grim_error_text = &DAT_1005d828;
  DAT_1005d3ac = 0;
  grim_string_table_loaded = 0;
  grim_string_table_data = 0;
  grim_string_table_size = 0;
  grim_backbuffer_width = 0x280;
  grim_backbuffer_height = 0x1e0;
  grim_texture_format = 0x17;
  grim_preferred_texture_format = 0;
  grim_window_handle = 0;
  grim_color_slot0 = 0xffffffff;
  grim_color_slot3 = 0xffffffff;
  grim_color_slot1 = 0xffffffff;
  grim_color_slot2 = 0xffffffff;
  grim_uv_u0 = 0;
  grim_uv_v1 = 0;
  grim_uv_u2 = 0x3f800000;
  grim_uv_v2 = 0x3f800000;
  grim_uv_u3 = 0;
  _grim_mouse_button_latch = 0;
  grim_uv_v3 = 0x3f800000;
  _DAT_1005c8ec = 0;
  uVar5 = 0xffffffff;
  pcVar10 = s_default_window_title;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar10 + 1;
  } while (cVar1 != '\0');
  grim_window_title = operator_new(~uVar5);
  uVar5 = 0xffffffff;
  pcVar10 = s_default_window_title;
  do {
    pcVar12 = pcVar10;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar12 = pcVar10 + 1;
    cVar1 = *pcVar10;
    pcVar10 = pcVar12;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar10 = pcVar12 + -uVar5;
  pcVar12 = grim_window_title;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar12 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar12 = pcVar12 + 1;
  }
  puVar9 = &grim_key_cooldown_table;
  for (iVar4 = 0x100; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  grim_frame_callback = &LAB_10001140;
  grim_on_device_restore_callback = &LAB_10001150;
  DAT_1005d3a8 = &LAB_10001150;
  _DAT_1005cc94 = _strdup(&DAT_1005d828);
  puVar9 = &grim_font2_glyph_widths;
  for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  local_14 = 0;
  pfVar8 = (float *)&grim_font2_uv_v;
  do {
    local_10 = 0;
    pfVar3 = pfVar8;
    do {
      fVar2 = (float)(int)local_10;
      local_10 = local_10 + 1;
      pfVar3[-1] = fVar2 * 0.0625;
      *pfVar3 = (float)local_14 * 0.0625;
      pfVar3 = pfVar3 + 2;
    } while ((int)local_10 < 0x10);
    local_14 = local_14 + 1;
    pfVar8 = pfVar8 + 0x20;
  } while (local_14 < 0x10);
  iVar4 = 0;
  puVar9 = &grim_subrect_ptr_table;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  do {
    (&grim_font2_char_map)[iVar4] = (char)iVar4;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  grim_char_map_a_umlaut = 0xe4;
  grim_char_map_o_umlaut = 0xf6;
  grim_char_map_A_umlaut = 0xc4;
  grim_char_map_O_umlaut = 0xd6;
  grim_char_map_A_ring = 0xc5;
  grim_char_map_a_ring = 0xe5;
  _grim_subrect_ptr0 = &grim_subrect_table_0;
  _grim_subrect_ptr1 = &grim_subrect_table_1;
  _grim_subrect_ptr2 = &grim_subrect_table_2;
  _grim_subrect_ptr3 = &grim_subrect_table;
  local_14 = 0;
  pfVar8 = (float *)&DAT_1005d38c;
  do {
    local_10 = 0;
    pfVar3 = pfVar8;
    do {
      fVar2 = (float)(int)local_10;
      local_10 = local_10 + 1;
      pfVar3[-1] = fVar2 * 0.5;
      *pfVar3 = (float)local_14 * 0.5;
      pfVar3 = pfVar3 + 2;
    } while ((int)local_10 < 2);
    local_14 = local_14 + 1;
    pfVar8 = pfVar8 + 4;
  } while (local_14 < 2);
  local_14 = 0;
  pfVar8 = (float *)&DAT_1005cb0c;
  do {
    local_10 = 0;
    pfVar3 = pfVar8;
    do {
      fVar2 = (float)(int)local_10;
      local_10 = local_10 + 1;
      pfVar3[-1] = fVar2 * 0.25;
      *pfVar3 = (float)local_14 * 0.25;
      pfVar3 = pfVar3 + 2;
    } while ((int)local_10 < 4);
    local_14 = local_14 + 1;
    pfVar8 = pfVar8 + 8;
  } while (local_14 < 4);
  local_14 = 0;
  pfVar8 = (float *)&DAT_1005c90c;
  do {
    local_10 = 0;
    pfVar3 = pfVar8;
    do {
      fVar2 = (float)(int)local_10;
      local_10 = local_10 + 1;
      pfVar3[-1] = fVar2 * 0.125;
      *pfVar3 = (float)local_14 * 0.125;
      pfVar3 = pfVar3 + 2;
    } while ((int)local_10 < 8);
    local_14 = local_14 + 1;
    pfVar8 = pfVar8 + 0x10;
  } while (local_14 < 8);
  local_14 = 0;
  pfVar8 = (float *)&DAT_1005a67c;
  do {
    local_10 = 0;
    pfVar3 = pfVar8;
    do {
      fVar2 = (float)(int)local_10;
      local_10 = local_10 + 1;
      pfVar3[-1] = fVar2 * 0.0625;
      *pfVar3 = (float)local_14 * 0.0625;
      pfVar3 = pfVar3 + 2;
    } while ((int)local_10 < 0x10);
    local_14 = local_14 + 1;
    pfVar8 = pfVar8 + 0x20;
  } while (local_14 < 0x10);
  return;
}



/* grim_release @ 10005c80 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x0: delete interface */

void grim_release(void)

{
  void *in_ECX;
  
  operator_delete(in_ECX);
  return;
}



/* grim_set_paused @ 10005c90 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x4 (provisional): pause game tick update */

void grim_set_paused(int paused)

{
  grim_paused_flag = (undefined1)paused;
  return;
}



/* grim_get_version @ 10005ca0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x8 (provisional): engine version constant */

float grim_get_version(void)

{
  return 1.21;
}



/* grim_check_device @ 10005cb0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xc: device creation test */

int grim_check_device(void)

{
  uint uVar1;
  HRESULT HVar2;
  ULONG UVar3;
  int iVar4;
  LPDIRECT3DDEVICE8 arg3;
  LPDIRECT3DDEVICE8 pDestSurface;
  IDirect3DSurface8 *pIStack_4;
  
  pIStack_4 = (IDirect3DSurface8 *)0x0;
  pDestSurface = grim_d3d_device;
  uVar1 = (*grim_d3d_device->lpVtbl->CreateImageSurface)
                    (grim_d3d_device,grim_present_width,grim_present_height,D3DFMT_A8R8G8B8,
                     &pIStack_4);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  arg3 = grim_d3d_device;
  HVar2 = (*grim_d3d_device->lpVtbl->GetFrontBuffer)
                    (grim_d3d_device,(IDirect3DSurface8 *)pDestSurface);
  if (HVar2 < 0) {
    UVar3 = (*arg3->lpVtbl->Release)(arg3);
    return UVar3 & 0xffffff00;
  }
  iVar4 = grim_image_get_info_simple((int)pDestSurface,0,(int *)arg3,0,(int *)0x0);
  if (iVar4 < 0) {
    UVar3 = (*arg3->lpVtbl->Release)(arg3);
    return UVar3 & 0xffffff00;
  }
  UVar3 = (*arg3->lpVtbl->Release)(arg3);
  return CONCAT31((int3)(UVar3 >> 8),1);
}



/* grim_apply_config @ 10005d40 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0x10: opens D3D config dialog and applies settings */

int grim_apply_config(void)

{
  uint uVar1;
  int *in_ECX;
  
  if (grim_icon_handle == (HICON)0x0) {
    grim_icon_handle = LoadIconA(grim_module_handle,(LPCSTR)0x72);
  }
  grim_dialog_canceled_flag = '\0';
  grim_d3d8_interface = Direct3DCreate8(0xdc);
  if (grim_d3d8_interface == (IDirect3D8 *)0x0) {
    grim_error_text = s_error_d3d_init;
    uVar1 = MessageBoxA((HWND)0x0,s_error_d3d_init,&DAT_10053824,0);
    return uVar1 & 0xffffff00;
  }
  (*grim_d3d8_interface->lpVtbl->GetDeviceCaps)
            (grim_d3d8_interface,0,D3DDEVTYPE_HAL,(D3DCAPS8 *)&grim_d3d_caps);
  DialogBoxParamA(grim_module_handle,(LPCSTR)0x74,(HWND)0x0,grim_config_dialog_proc,0);
  (*grim_d3d8_interface->lpVtbl->Release)(grim_d3d8_interface);
  if (grim_dialog_canceled_flag == '\0') {
    (**(code **)(*in_ECX + 0x20))(0x54,grim_display_mode_saved);
    if ((char)grim_16bit_color_mode == '\0') {
      (**(code **)(*in_ECX + 0x20))(0x2b,0x20);
    }
    else {
      (**(code **)(*in_ECX + 0x20))(0x2b,0x10);
    }
    (**(code **)(*in_ECX + 0x20))(0x54,grim_display_mode_saved);
    (**(code **)(*in_ECX + 0x20))(8,grim_is_windowed_resolution);
    (**(code **)(*in_ECX + 0x20))(0x34,0);
    (**(code **)(*in_ECX + 0x20))(8,grim_is_windowed_resolution);
    (**(code **)(*in_ECX + 0x20))(0x29,grim_parsed_width);
    (**(code **)(*in_ECX + 0x20))(0x2a,grim_parsed_height);
  }
  return (uint)(grim_dialog_canceled_flag == '\0');
}



/* grim_init_system @ 10005eb0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Grim2D vtable 0x14: Grim2D init; returns success */

int __fastcall grim_init_system(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int *in_ECX;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar2 = &grim_working_directory;
  for (iVar3 = 0x41; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  _getcwd((char *)&grim_working_directory,0x104);
  iVar3 = grim_d3d_init();
  if ((char)iVar3 == '\0') {
    return iVar3;
  }
  if ((DAT_1005cc48 == '\x01') && (grim_hide_cursor_flag == '\0')) {
    iVar3 = grim_mouse_init();
    if ((char)iVar3 == '\0') {
      grim_error_text = s_error_mouse_init;
      grim_mouse_shutdown();
      grim_d3d_shutdown();
      uVar1 = grim_window_destroy();
      return uVar1 & 0xffffff00;
    }
  }
  if (grim_keyboard_enabled_flag == '\x01') {
    iVar3 = grim_keyboard_init(grim_window_handle);
    if ((char)iVar3 == '\0') {
      grim_error_text = s_error_keyboard_init;
      grim_mouse_shutdown();
      grim_keyboard_shutdown();
      grim_d3d_shutdown();
      uVar1 = grim_window_destroy();
      return uVar1 & 0xffffff00;
    }
  }
  if (DAT_1005cc68 == '\x01') {
    iVar3 = grim_joystick_init(grim_window_handle);
    if ((char)iVar3 == '\0') {
      grim_error_text = s_error_joystick_init;
      DAT_1005cc68 = '\0';
    }
  }
  grim_input_init();
  grim_input_update();
  (**(code **)(*in_ECX + 0x20))(0x15,2);
  _DAT_1005d0b4 = &grim_window_handle;
  (**(code **)(*in_ECX + 0x20))(0x10);
  puVar2 = (undefined4 *)grim_string_table_lookup_str((byte *)s_load_smallfnt_dat);
  if (puVar2 != (undefined4 *)0x0) {
    puVar4 = puVar2;
    puVar5 = &grim_font2_glyph_widths;
    for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  return CONCAT31((int3)((uint)puVar2 >> 8),1);
}



/* grim_shutdown @ 10005ff0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x18 (provisional): Grim2D shutdown */

void grim_shutdown(void)

{
  grim_string_table_load(&DAT_1005d828);
  grim_mouse_shutdown();
  grim_keyboard_shutdown();
  grim_joystick_shutdown();
  grim_d3d_shutdown();
  grim_window_destroy();
  return;
}



/* grim_apply_settings @ 10006020 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x1c: apply Grim2D settings after config load */

void grim_apply_settings(void)

{
  grim_main_loop();
  return;
}



/* grim_set_config_var @ 10006580 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0x20: config/state dispatcher; updates config tables, some IDs map to D3D
   render/texture state; extra args for some IDs */

void grim_set_config_var(uint id,uint value)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  WORD WVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  char *pcVar9;
  uint uVar10;
  uint *puVar11;
  WORD *pWVar12;
  byte *pbVar13;
  int iVar14;
  byte *pbVar15;
  bool bVar16;
  uint in_stack_0000000c;
  uint in_stack_00000010;
  byte *in_stack_00000014;
  D3DGAMMARAMP DStack_600;
  
  switch(id) {
  case 5:
    DAT_1005d3a8 = in_stack_00000014;
    return;
  case 6:
    grim_on_device_restore_callback = in_stack_00000014;
    return;
  case 7:
    if (grim_window_title != (byte *)0x0) {
      operator_delete(grim_window_title);
    }
    uVar6 = 0xffffffff;
    pbVar13 = in_stack_00000014;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar1 = *pbVar13;
      pbVar13 = pbVar13 + 1;
    } while (bVar1 != 0);
    grim_window_title = operator_new(~uVar6);
    uVar6 = 0xffffffff;
    do {
      pbVar13 = in_stack_00000014;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pbVar13 = in_stack_00000014 + 1;
      bVar1 = *in_stack_00000014;
      in_stack_00000014 = pbVar13;
    } while (bVar1 != 0);
    uVar6 = ~uVar6;
    pbVar13 = pbVar13 + -uVar6;
    pbVar15 = grim_window_title;
    for (uVar10 = uVar6 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pbVar15 = *(undefined4 *)pbVar13;
      pbVar13 = pbVar13 + 4;
      pbVar15 = pbVar15 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pbVar15 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      pbVar15 = pbVar15 + 1;
    }
    *(byte **)(&grim_config_var3_table + id * 0x10) = grim_window_title;
    return;
  default:
    puVar11 = &grim_config_var0_table + id * 4;
    *puVar11 = value;
    goto LAB_10006b54;
  case 0xb:
  case 0xc:
  case 0xe:
  case 0x42:
    *(char *)(&grim_config_var0_table + id * 4) = (char)value;
    return;
  case 0xd:
    *(char *)(&grim_config_var0_table + id * 4) = (char)value;
    if (grim_hide_cursor_flag != '\0') {
      DAT_1005cc48 = 1;
      return;
    }
    break;
  case 0x10:
    pbVar15 = &DAT_1005d828;
    pbVar13 = in_stack_00000014;
    do {
      bVar1 = *pbVar13;
      bVar16 = bVar1 < *pbVar15;
      if (bVar1 != *pbVar15) {
LAB_10006882:
        iVar14 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
        goto LAB_10006887;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar13[1];
      bVar16 = bVar1 < pbVar15[1];
      if (bVar1 != pbVar15[1]) goto LAB_10006882;
      pbVar13 = pbVar13 + 2;
      pbVar15 = pbVar15 + 2;
    } while (bVar1 != 0);
    iVar14 = 0;
LAB_10006887:
    if (iVar14 == 0) {
      if (*(void **)(&grim_config_var3_table + id * 0x10) != (void *)0x0) {
        operator_delete(*(void **)(&grim_config_var3_table + id * 0x10));
      }
      _DAT_1005cc94 = _strdup(&DAT_1005d828);
      grim_string_table_loaded = 0;
    }
    uVar8 = grim_string_table_load((char *)in_stack_00000014);
    grim_string_table_loaded = (undefined1)uVar8;
    if (*(void **)(&grim_config_var3_table + id * 0x10) != (void *)0x0) {
      operator_delete(*(void **)(&grim_config_var3_table + id * 0x10));
    }
    pcVar9 = _strdup((char *)in_stack_00000014);
    *(char **)(&grim_config_var3_table + id * 0x10) = pcVar9;
    *(undefined1 *)(&grim_config_var0_table + id * 4) = grim_string_table_loaded;
    return;
  case 0x12:
    if (*(char *)(&grim_config_var0_table + id * 4) != (char)value) {
      (*grim_d3d_device->lpVtbl->SetRenderState)
                (grim_d3d_device,D3DRS_ALPHABLENDENABLE,value & 0xff);
      *(char *)(&grim_config_var0_table + id * 4) = (char)value;
      return;
    }
    break;
  case 0x13:
    if ((&grim_config_var0_table)[id * 4] != value) {
      (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_SRCBLEND,value);
      (&grim_config_var0_table)[id * 4] = value;
      return;
    }
    break;
  case 0x14:
    if ((&grim_config_var0_table)[id * 4] != value) {
      (*grim_d3d_device->lpVtbl->SetRenderState)(grim_d3d_device,D3DRS_DESTBLEND,value);
      (&grim_config_var0_table)[id * 4] = value;
      return;
    }
    break;
  case 0x15:
    if (0 < (int)value) {
      if (2 < (int)value) {
        if (value != 3) {
          return;
        }
        if ((&grim_config_var0_table)[id * 4] != 3) {
          (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MAXANISOTROPY,3)
          ;
        }
      }
      if ((&grim_config_var0_table)[id * 4] == 3) {
        (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MAXANISOTROPY,1);
      }
      (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MINFILTER,value);
      (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_MAGFILTER,value);
      (&grim_config_var0_table)[id * 4] = value;
      return;
    }
    break;
  case 0x1a:
    uVar6 = grim_set_texture_stage_ops(value);
    if ((char)uVar6 == '\0') {
      return;
    }
    puVar11 = &grim_config_var0_table + id * 4;
    *puVar11 = value;
LAB_10006b54:
    puVar11[1] = in_stack_0000000c;
    puVar11[2] = in_stack_00000010;
    puVar11[3] = (uint)in_stack_00000014;
    break;
  case 0x1b:
    (&grim_config_var0_table)[id * 4] = value;
    (&grim_config_var1_table)[id * 4] = in_stack_0000000c;
    *(uint *)(&grim_config_var2_table + id * 0x10) = in_stack_00000010;
    *(byte **)(&grim_config_var3_table + id * 0x10) = in_stack_00000014;
    uVar2 = ftol();
    uVar3 = ftol();
    uVar4 = ftol();
    (*grim_d3d_device->lpVtbl->SetRenderState)
              (grim_d3d_device,D3DRS_TEXTUREFACTOR,(uint)CONCAT21(CONCAT11(uVar2,uVar3),uVar4));
    return;
  case 0x1c:
    iVar14 = 0;
    pWVar12 = DStack_600.green;
    do {
      iVar7 = ftol();
      if (iVar7 < 0x10000) {
        if (iVar7 < 0) {
          iVar7 = 0;
        }
      }
      else {
        iVar7 = 0xffff;
      }
      WVar5 = (WORD)iVar7;
      ((D3DGAMMARAMP *)(pWVar12 + -0x100))->red[0] = WVar5;
      *pWVar12 = WVar5;
      pWVar12[0x100] = WVar5;
      iVar14 = iVar14 + 1;
      pWVar12 = pWVar12 + 1;
    } while (iVar14 < 0x100);
    (*grim_d3d_device->lpVtbl->SetGammaRamp)(grim_d3d_device,1,&DStack_600);
    (&grim_config_var0_table)[id * 4] = value;
    (&grim_config_var1_table)[id * 4] = in_stack_0000000c;
    *(uint *)(&grim_config_var2_table + id * 0x10) = in_stack_00000010;
    *(byte **)(&grim_config_var3_table + id * 0x10) = in_stack_00000014;
    return;
  case 0x29:
    grim_backbuffer_width = value;
    (&grim_config_var0_table)[id * 4] = value;
    return;
  case 0x2a:
    grim_backbuffer_height = value;
    (&grim_config_var0_table)[id * 4] = value;
    return;
  case 0x2b:
    (&grim_config_var0_table)[id * 4] = value;
    grim_texture_format = (value != 0x20) + 0x16;
    return;
  case 0x2d:
    grim_frame_callback = in_stack_00000014;
    return;
  case 0x34:
    *(char *)(&grim_config_var0_table + id * 4) = (char)value;
    return;
  case 0x36:
    (*grim_d3d_device->lpVtbl->Present)
              (grim_d3d_device,(RECT *)0x0,(RECT *)0x0,(HWND)0x0,(RGNDATA *)0x0);
    return;
  case 0x52:
    (&grim_config_var0_table)[id * 4] = value;
    (&grim_config_var1_table)[id * 4] = in_stack_0000000c;
    *(uint *)(&grim_config_var2_table + id * 0x10) = in_stack_00000010;
    *(byte **)(&grim_config_var3_table + id * 0x10) = in_stack_00000014;
    grim_parent_window_handle = *(undefined4 *)in_stack_00000014;
    return;
  case 0x55:
    grim_render_disabled = (char)value;
    return;
  }
  return;
}



/* grim_get_config_var @ 10006c30 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x24 (provisional): fills 4 dwords for config entry (id 0..0x7f) */

void grim_get_config_var(uint *out,int id)

{
  if ((-1 < id) && (id < 0x80)) {
    *out = (&grim_config_var0_table)[id * 4];
    out[1] = (&grim_config_var1_table)[id * 4];
    out[2] = *(uint *)(&grim_config_var2_table + id * 0x10);
    out[3] = *(uint *)(&grim_config_var3_table + id * 0x10);
    return;
  }
  *out = DAT_1005a478;
  out[1] = DAT_1005a47c;
  out[2] = DAT_1005a480;
  out[3] = DAT_1005a484;
  return;
}



/* grim_get_error_text @ 10006ca0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x28: error string for MessageBox */

char * grim_get_error_text(void)

{
  return grim_error_text;
}



/* grim_get_time_ms @ 10006e40 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x34: accumulated time (ms) */

int grim_get_time_ms(void)

{
  return grim_time_ms;
}



/* grim_set_time_ms @ 10006e50 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x38: set accumulated time */

void grim_set_time_ms(int ms)

{
  grim_time_ms = ms;
  return;
}



/* grim_get_frame_dt @ 10006e60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x3c: clamped frame delta */

float grim_get_frame_dt(void)

{
  if (0.1 < grim_frame_delta_time) {
    return 0.1;
  }
  return grim_frame_delta_time;
}



/* grim_get_fps @ 10006e90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x40: frames per second */

float grim_get_fps(void)

{
  return _grim_fps;
}



/* grim_get_config_float @ 100071b0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x84: config float lookup (scaled) */

float grim_get_config_float(int id)

{
  int iVar1;
  int *in_ECX;
  int iVar2;
  float10 fVar3;
  
  if (0xff < id) {
    if (id == 0x13f) {
      return (float)grim_joystick_device_state.lX * 0.001;
    }
    if (id == 0x140) {
      return (float)grim_joystick_device_state.lY * 0.001;
    }
    if (id == 0x141) {
      return (float)grim_joystick_device_state.lZ * 0.001;
    }
    if (id == 0x153) {
      return (float)grim_joystick_device_state.lRx * 0.001;
    }
    if (id == 0x154) {
      return (float)grim_joystick_device_state.lRy * 0.001;
    }
    if (id == 0x155) {
      return (float)grim_joystick_device_state.lRz * 0.001;
    }
    if (id == 0x15f) {
      fVar3 = (float10)(**(code **)(*in_ECX + 0x70))();
      return (float)fVar3;
    }
    if (id == 0x160) {
      fVar3 = (float10)(**(code **)(*in_ECX + 0x74))();
      return (float)fVar3;
    }
    iVar2 = 0;
    iVar1 = 0x168;
    do {
      if (id == iVar1 + -5) {
        fVar3 = (float10)(**(code **)(*in_ECX + 0x78))(iVar2);
        return (float)fVar3;
      }
      if (id == iVar1) {
        fVar3 = (float10)(**(code **)(*in_ECX + 0x7c))(iVar2);
        return (float)fVar3;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x16b);
  }
  return 0.0;
}



/* grim_get_slot_float @ 100072c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x88 (provisional): float slot accessor */

float grim_get_slot_float(int index)

{
  return *(float *)(&grim_slot_floats + index * 4);
}



/* grim_get_slot_int @ 100072d0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x8c (provisional): int slot accessor */

int grim_get_slot_int(int index)

{
  return *(int *)(&grim_slot_ints + index * 4);
}



/* grim_set_slot_float @ 100072e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x90 (provisional): float slot setter */

void grim_set_slot_float(int index,float value)

{
  *(float *)(&grim_slot_floats + index * 4) = value;
  return;
}



/* grim_set_slot_int @ 10007300 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x94 (provisional): int slot setter */

void grim_set_slot_int(int index,int value)

{
  *(int *)(&grim_slot_ints + index * 4) = value;
  return;
}



/* GRIM__GetInterface @ 100099c0 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* export: constructs (singleton) Grim2D interface instance backed by grim_interface_vtable */

IGrim2D * GRIM__GetInterface(void)

{
                    /* 0x99c0  1  GRIM__GetInterface */
  grim_d3d8_interface = Direct3DCreate8(0xdc);
  if (grim_d3d8_interface == (IDirect3D8 *)0x0) {
    grim_error_text = s_error_d3d_init;
    MessageBoxA((HWND)0x0,s_error_d3d_init,&DAT_10053824,0);
    return (IGrim2D *)0x0;
  }
  (*grim_d3d8_interface->lpVtbl->Release)(grim_d3d8_interface);
  grim_engine_full_init();
  grim_interface_instance = operator_new(4);
  if (grim_interface_instance != (IGrim2D *)0x0) {
    grim_interface_instance->vtable = &grim_interface_vtable;
    return grim_interface_instance;
  }
  grim_interface_instance = (IGrim2D *)0x0;
  return (IGrim2D *)0x0;
}



/* DllMain @ 10009a20 */

/* DLL entrypoint (process attach): caches module handle and loads dialog icon */

BOOL DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)

{
  if (fdwReason == 1) {
    grim_module_handle = hinstDLL;
    grim_icon_handle = LoadIconA((HINSTANCE)hinstDLL,(LPCSTR)0x72);
  }
  return 1;
}



/* grim_identity_int @ 1000a810 */

/* [binja] int32_t __fastcall sub_1000a810(int32_t arg1) __pure */

int __fastcall grim_identity_int(int arg1)

{
  return arg1;
}



/* grim_check_valid_pool @ 1000a820 */

undefined4 __cdecl grim_check_valid_pool(int param_1)

{
  if (((param_1 != 0) && (param_1 != 1)) && (param_1 + -2 != 0)) {
    return CONCAT31((int3)((uint)(param_1 + -2) >> 8),1);
  }
  return 0;
}



/* grim_onexit_register @ 1000a900 */

void __cdecl grim_onexit_register(_onexit_t param_1)

{
  if (DAT_1005dbcc == -1) {
    _onexit((_onexit_t)param_1);
    return;
  }
  __dllonexit(param_1,&DAT_1005dbcc,&DAT_1005dbc8);
  return;
}



/* grim_atexit_register @ 1000a92c */

int __cdecl grim_atexit_register(_onexit_t param_1)

{
  int iVar1;
  
  iVar1 = grim_onexit_register(param_1);
  return (iVar1 != 0) - 1;
}



/* grim_dll_init_term @ 1000a93e */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t __stdcall sub_1000a93e(int32_t arg1) */

int grim_dll_init_term(int arg1)

{
  int iVar1;
  undefined4 *_Memory;
  undefined4 *puVar2;
  int in_stack_00000008;
  
  if (in_stack_00000008 == 0) {
    if (0 < DAT_1005db5c) {
      DAT_1005db5c = DAT_1005db5c + -1;
      goto LAB_1000a954;
    }
LAB_1000a97c:
    iVar1 = 0;
  }
  else {
LAB_1000a954:
    _DAT_1005dbc0 = *(undefined4 *)_adjust_fdiv_exref;
    if (in_stack_00000008 == 1) {
      DAT_1005dbcc = malloc(0x80);
      if (DAT_1005dbcc == (undefined4 *)0x0) goto LAB_1000a97c;
      *DAT_1005dbcc = 0;
      DAT_1005dbc8 = DAT_1005dbcc;
      initterm(&DAT_10053000,&DAT_10053034);
      DAT_1005db5c = DAT_1005db5c + 1;
    }
    else if ((in_stack_00000008 == 0) &&
            (_Memory = DAT_1005dbcc, puVar2 = DAT_1005dbc8, DAT_1005dbcc != (undefined4 *)0x0)) {
      while (puVar2 = puVar2 + -1, _Memory <= puVar2) {
        if ((code *)*puVar2 != (code *)0x0) {
          (*(code *)*puVar2)();
          _Memory = DAT_1005dbcc;
        }
      }
      free(_Memory);
      DAT_1005dbcc = (undefined4 *)0x0;
    }
    iVar1 = 1;
  }
  return iVar1;
}



/* entry @ 1000a9e9 */

/* [binja] int32_t __stdcall _start(HINSTANCE arg1, int32_t arg2, int32_t arg3) */

int entry(HINSTANCE arg1,int arg2,int arg3)

{
  int iVar1;
  BOOL BVar2;
  int iVar3;
  
  iVar1 = arg2;
  iVar3 = DAT_1005db5c;
  if (arg2 != 0) {
    if ((arg2 != 1) && (arg2 != 2)) goto LAB_1000aa31;
    if ((DAT_1005dbc4 != (code *)0x0) && (iVar3 = (*DAT_1005dbc4)(arg1,arg2,arg3), iVar3 == 0)) {
      return 0;
    }
    iVar3 = grim_dll_init_term((int)arg1);
  }
  if (iVar3 == 0) {
    return 0;
  }
LAB_1000aa31:
  BVar2 = DllMain(arg1,arg2,(LPVOID)arg3);
  if (arg2 == 1) {
    if (BVar2 != 0) {
      return BVar2;
    }
    grim_dll_init_term((int)arg1);
  }
  if ((arg2 != 0) && (arg2 != 3)) {
    return BVar2;
  }
  iVar3 = grim_dll_init_term((int)arg1);
  arg2 = BVar2;
  if (iVar3 == 0) {
    arg2 = 0;
  }
  if (arg2 != 0) {
    if (DAT_1005dbc4 != (code *)0x0) {
      iVar3 = (*DAT_1005dbc4)(arg1,iVar1,arg3);
      return iVar3;
    }
    return arg2;
  }
  return 0;
}



/* grim_alloc_block @ 1001237e */

/* [binja] int32_t __thiscall sub_1001237e(int32_t* arg1, int32_t arg2, int32_t arg3, int32_t* arg4)
    */

int grim_alloc_block(int *arg1,int arg2,int arg3,int *arg4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  int *extraout_ECX;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  int unaff_EBP;
  undefined4 *puVar8;
  int *unaff_EDI;
  undefined4 *puVar9;
  HANDLE arg2_00;
  
  seh_prolog();
  *(int **)(unaff_EBP + -0x20) = extraout_ECX;
  grim_memory_block_zero((int *)(unaff_EBP + -0x3c));
  iVar5 = *(int *)(unaff_EBP + 0xc);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if (iVar5 == 0) {
LAB_100123d3:
    piVar6 = (int *)&DAT_10053e28;
LAB_100123d8:
    piVar1 = grim_format_info_lookup(*extraout_ECX);
    iVar2 = grim_format_find_best(piVar6,extraout_ECX[2],piVar1);
    *(int *)(unaff_EBP + -0x1c) = iVar2;
    if (iVar2 != 0) {
      piVar6 = extraout_ECX;
      if (iVar2 != *extraout_ECX) {
        grim_alloc_context_init((int *)(unaff_EBP + -0x2c));
        *(undefined1 *)(unaff_EBP + -4) = 1;
        piVar1 = grim_format_info_lookup(iVar2);
        uVar3 = (uint)piVar1[2] >> 3;
        *(uint *)(unaff_EBP + -0x10) = uVar3;
        *(int **)(unaff_EBP + -0x14) = extraout_ECX;
        do {
          puVar7 = *(undefined4 **)(unaff_EBP + -0x14);
          if (puVar7 != (undefined4 *)0x0) {
            do {
              pvVar4 = operator_new(puVar7[5] * puVar7[3] * uVar3 * puVar7[4]);
              *(void **)(unaff_EBP + -0x18) = pvVar4;
              if (pvVar4 == (void *)0x0) {
                *(undefined1 *)(unaff_EBP + -4) = 0;
                grim_alloc_context_free((int *)(unaff_EBP + -0x2c));
                iVar2 = -0x7ff8fff2;
                goto LAB_10012628;
              }
              *(undefined4 *)(unaff_EBP + -0xd4) = puVar7[1];
              *(undefined4 *)(unaff_EBP + -0xd0) = *puVar7;
              *(undefined4 *)(unaff_EBP + -0xcc) = puVar7[0xc];
              *(undefined4 *)(unaff_EBP + -200) = puVar7[0xd];
              puVar8 = puVar7 + 6;
              puVar9 = (undefined4 *)(unaff_EBP + -0xc4);
              for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar9 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar9 = puVar9 + 1;
              }
              puVar8 = puVar7 + 6;
              puVar9 = (undefined4 *)(unaff_EBP + -0xac);
              for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar9 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar9 = puVar9 + 1;
              }
              *(undefined4 *)(unaff_EBP + -0x90) = 0;
              *(undefined4 *)(unaff_EBP + -0x94) = 1;
              *(undefined4 *)(unaff_EBP + -0x8c) = puVar7[2];
              *(undefined4 *)(unaff_EBP + -0x88) = *(undefined4 *)(unaff_EBP + -0x18);
              *(undefined4 *)(unaff_EBP + -0x84) = *(undefined4 *)(unaff_EBP + -0x1c);
              *(int *)(unaff_EBP + -0x80) = puVar7[3] * *(int *)(unaff_EBP + -0x10);
              *(int *)(unaff_EBP + -0x7c) = puVar7[3] * *(int *)(unaff_EBP + -0x10) * puVar7[4];
              *(undefined4 *)(unaff_EBP + -0x78) = 0;
              *(undefined4 *)(unaff_EBP + -0x74) = 0;
              *(undefined4 *)(unaff_EBP + -0x70) = puVar7[3];
              *(undefined4 *)(unaff_EBP + -0x6c) = puVar7[4];
              *(undefined4 *)(unaff_EBP + -0x68) = 0;
              *(undefined4 *)(unaff_EBP + -100) = puVar7[5];
              puVar8 = (undefined4 *)(unaff_EBP + -0x78);
              puVar9 = (undefined4 *)(unaff_EBP + -0x60);
              for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar9 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar9 = puVar9 + 1;
              }
              *(undefined4 *)(unaff_EBP + -0x44) = 0;
              *(undefined4 *)(unaff_EBP + -0x48) = 1;
              *(undefined4 *)(unaff_EBP + -0x40) = puVar7[2];
              iVar2 = grim_zip_decompress((void *)(unaff_EBP + -0x2c),(int *)(unaff_EBP + -0x88),
                                   (void ***)(unaff_EBP + -0xd4),(void ***)0x80001,(int)unaff_EDI);
              if (iVar2 < 0) {
                operator_delete(*(void **)(unaff_EBP + -0x18));
                *(undefined1 *)(unaff_EBP + -4) = 0;
                grim_alloc_context_free((int *)(unaff_EBP + -0x2c));
                goto LAB_10012628;
              }
              if (((void *)puVar7[1] != (void *)0x0) && (puVar7[0xe] != 0)) {
                operator_delete((void *)puVar7[1]);
                puVar7[1] = 0;
              }
              *puVar7 = *(undefined4 *)(unaff_EBP + -0x1c);
              puVar7[1] = *(undefined4 *)(unaff_EBP + -0x18);
              puVar8 = (undefined4 *)(unaff_EBP + -0x60);
              puVar9 = puVar7 + 6;
              for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar9 = *puVar8;
                puVar8 = puVar8 + 1;
                puVar9 = puVar9 + 1;
              }
              puVar7[0xc] = *(undefined4 *)(unaff_EBP + -0x80);
              puVar7[0xd] = *(undefined4 *)(unaff_EBP + -0x7c);
              uVar3 = *(uint *)(unaff_EBP + -0x10);
              puVar7[0xe] = 1;
              puVar7 = (undefined4 *)puVar7[0x13];
            } while (puVar7 != (undefined4 *)0x0);
            iVar5 = *(int *)(unaff_EBP + 0xc);
            piVar6 = *(int **)(unaff_EBP + -0x20);
          }
          iVar2 = *(int *)(*(int *)(unaff_EBP + -0x14) + 0x50);
          *(int *)(unaff_EBP + -0x14) = iVar2;
        } while (iVar2 != 0);
        *(undefined1 *)(unaff_EBP + -4) = 0;
        grim_alloc_context_free((int *)(unaff_EBP + -0x2c));
      }
      iVar2 = grim_crt_file_read_with_size((void *)(unaff_EBP + -0x3c),*(void ***)(unaff_EBP + 8),
                           *(int *)(unaff_EBP + 0x10),unaff_EDI);
      if (iVar2 < 0) goto LAB_10012628;
      if (iVar5 == 0) {
        arg2_00 = (HANDLE)0x1;
LAB_10012618:
        iVar2 = grim_mesh_data_parse(piVar6,*(int **)(unaff_EBP + -0x3c),arg2_00);
      }
      else {
        if (iVar5 != 4) {
          if (iVar5 != 6) {
            iVar2 = -0x7fffbfff;
            goto LAB_10012628;
          }
          arg2_00 = (HANDLE)0x0;
          goto LAB_10012618;
        }
        iVar2 = grim_mesh_load_from_buffer(piVar6,*(int **)(unaff_EBP + -0x3c),unaff_EDI);
      }
      if (-1 < iVar2) {
        iVar2 = 0;
      }
      goto LAB_10012628;
    }
  }
  else {
    if (iVar5 < 1) {
LAB_100125be:
      iVar2 = -0x7789f794;
      goto LAB_10012628;
    }
    if (3 < iVar5) {
      if (iVar5 == 4) {
        piVar6 = (int *)&DAT_10053e40;
        goto LAB_100123d8;
      }
      if (iVar5 != 5) {
        if (iVar5 == 6) goto LAB_100123d3;
        goto LAB_100125be;
      }
    }
  }
  iVar2 = -0x7789f4a7;
LAB_10012628:
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_registry_read_config((int *)(unaff_EBP + -0x3c));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar2;
}



/* grim_alloc_context_init @ 1001284c */

/* [binja] int32_t* __fastcall sub_1001284c(int32_t* arg1) */

int * __fastcall grim_alloc_context_init(int *arg1)

{
  arg1[1] = 0;
  *arg1 = 0;
  return arg1;
}



/* grim_alloc_context_free @ 10012856 */

/* [binja] void __fastcall sub_10012856(int32_t* arg1) */

void __fastcall grim_alloc_context_free(int *arg1)

{
  if ((undefined4 *)arg1[1] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)arg1[1])(1);
  }
  if ((undefined4 *)*arg1 != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)*arg1)(1);
  }
  return;
}



/* grim_memory_block_zero @ 1001bca5 */

/* [binja] int32_t* __fastcall sub_1001bca5(int32_t* arg1) */

int * __fastcall grim_memory_block_zero(int *arg1)

{
  *arg1 = -1;
  arg1[1] = -1;
  arg1[2] = 0;
  arg1[3] = 0;
  return arg1;
}



/* grim_crt_file_read_all @ 1001bcb7 */

/* [binja] int32_t __thiscall sub_1001bcb7(int32_t* arg1, int32_t* arg2, int32_t* arg3) */

int __thiscall grim_crt_file_read_all(void *this,int *arg1,int *arg2,int *arg3)

{
  HANDLE pvVar1;
  LPVOID pvVar2;
  DWORD DVar3;
  _OSVERSIONINFOA local_9c;
  int local_8;
  
  if (arg1 == (int *)0x0) {
    return -0x7789f794;
  }
  if (arg2 != (int *)0x0) {
    local_9c.dwOSVersionInfoSize = 0x94;
    GetVersionExA(&local_9c);
    if (local_9c.dwPlatformId != 2) {
      local_8 = WideCharToMultiByte(0,0,(LPCWCH)arg1,-1,(LPSTR)0x0,0,(LPCCH)0x0,(LPBOOL)0x0);
      grim_crt_cleanup_handler();
      WideCharToMultiByte(0,0,(LPCWCH)arg1,-1,&stack0xffffff58,local_8,(LPCCH)0x0,(LPBOOL)0x0);
      arg2 = (int *)0x0;
      arg1 = (int *)&stack0xffffff58;
    }
    if (arg2 != (int *)0x0) {
      pvVar1 = CreateFileW((LPCWSTR)arg1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x10000000,
                           (HANDLE)0x0);
      goto LAB_1001bd6b;
    }
  }
  pvVar1 = CreateFileA((LPCSTR)arg1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x10000000,(HANDLE)0x0
                      );
LAB_1001bd6b:
  *(HANDLE *)this = pvVar1;
  if (pvVar1 != (HANDLE)0xffffffff) {
    pvVar1 = CreateFileMappingA(pvVar1,(LPSECURITY_ATTRIBUTES)0x0,2,0,0,(LPCSTR)0x0);
    *(HANDLE *)((int)this + 4) = pvVar1;
    if (pvVar1 != (HANDLE)0xffffffff) {
      pvVar2 = MapViewOfFile(pvVar1,4,0,0,0);
      *(LPVOID *)((int)this + 8) = pvVar2;
      if (pvVar2 != (LPVOID)0x0) {
        DVar3 = GetFileSize(*(HANDLE *)this,(LPDWORD)0x0);
        *(DWORD *)((int)this + 0xc) = DVar3;
        if (DVar3 != 0xffffffff) {
          return 0;
        }
      }
    }
  }
  GetLastError();
  return -0x7789f4a7;
}



/* grim_crt_file_read_with_size @ 1001bdc7 */

/* [binja] int32_t __thiscall sub_1001bdc7(void** arg1, int32_t arg2, int32_t* arg3) */

int __thiscall grim_crt_file_read_with_size(void *this,void **arg1,int arg2,int *arg3)

{
  int iVar1;
  HANDLE pvVar2;
  void **lpFileName;
  _OSVERSIONINFOA local_9c;
  undefined4 *local_8;
  
  if (arg1 == (void **)0x0) {
    return -0x7789f794;
  }
  lpFileName = arg1;
  local_8 = this;
  if (arg2 != 0) {
    local_9c.dwOSVersionInfoSize = 0x94;
    GetVersionExA(&local_9c);
    if (local_9c.dwPlatformId != 2) {
      lpFileName = (void **)&stack0xffffff58;
      iVar1 = WideCharToMultiByte(0,0,(LPCWCH)arg1,-1,(LPSTR)0x0,0,(LPCCH)0x0,(LPBOOL)0x0);
      grim_crt_cleanup_handler();
      WideCharToMultiByte(0,0,(LPCWCH)arg1,-1,&stack0xffffff58,iVar1,(LPCCH)0x0,(LPBOOL)0x0);
      arg2 = 0;
      this = local_8;
    }
    if (arg2 != 0) {
      pvVar2 = CreateFileW((LPCWSTR)lpFileName,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0,
                           (HANDLE)0x0);
      goto LAB_1001be6e;
    }
  }
  pvVar2 = CreateFileA((LPCSTR)lpFileName,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0,(HANDLE)0x0);
LAB_1001be6e:
  *(HANDLE *)this = pvVar2;
  if (pvVar2 == (HANDLE)0xffffffff) {
    GetLastError();
    iVar1 = -0x7789f4a7;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}



/* grim_registry_key_exists @ 1001be91 */

/* [binja] int32_t __fastcall sub_1001be91(int32_t* arg1) */

int __fastcall grim_registry_key_exists(int *arg1)

{
  if ((LPCVOID)arg1[2] != (LPCVOID)0x0) {
    UnmapViewOfFile((LPCVOID)arg1[2]);
    arg1[2] = 0;
    arg1[3] = 0;
  }
  if ((HANDLE)arg1[1] != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)arg1[1]);
    arg1[1] = -1;
  }
  if ((HANDLE)*arg1 != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)*arg1);
    *arg1 = -1;
  }
  return 0;
}



/* grim_registry_read_config @ 1001bed2 */

/* [binja] void __fastcall sub_1001bed2(int32_t* arg1) */

void __fastcall grim_registry_read_config(int *arg1)

{
  if (*arg1 != -1) {
    grim_registry_key_exists(arg1);
    return;
  }
  return;
}



/* grim_registry_read_dword @ 1001bedd */

undefined4 __cdecl grim_registry_read_dword(DWORD param_1,LPCSTR param_2,LPBYTE param_3)

{
  LONG LVar1;
  DWORD local_c;
  HKEY local_8;
  
  local_8 = (HKEY)0x0;
  LVar1 = RegOpenKeyA((HKEY)0x80000002,"Software\\Microsoft\\Direct3D",&local_8);
  if (LVar1 == 0) {
    LVar1 = RegQueryValueExA(local_8,param_2,(LPDWORD)0x0,&local_c,param_3,(LPDWORD)&stack0x00000010
                            );
    RegCloseKey(local_8);
    if ((LVar1 == 0) && (local_c == param_1)) {
      return 1;
    }
  }
  return 0;
}



/* grim_crt_buffer_alloc @ 1004b5cf */

/* [binja] int32_t __stdcall sub_1004b5cf(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int grim_crt_buffer_alloc(int arg1,int arg2,int arg3,int arg4)

{
  int iVar1;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_100516b8;
  puStack_10 = &DAT_1004b7cc;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  while( true ) {
    arg3 = arg3 + -1;
    if (arg3 < 0) break;
    (*(code *)arg4)();
  }
  local_8 = 0xffffffff;
  iVar1 = grim_crt_buffer_realloc();
  ExceptionList = local_14;
  return iVar1;
}



/* grim_crt_buffer_realloc @ 1004b637 */

void grim_crt_buffer_realloc(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    grim_crt_buffer_free(*(int *)(unaff_EBP + 8),*(int *)(unaff_EBP + 0xc),*(int *)(unaff_EBP + 0x10),
                 *(int *)(unaff_EBP + 0x14));
  }
  return;
}



/* grim_crt_buffer_free @ 1004b64f */

/* [binja] struct _EXCEPTION_REGISTRATION_RECORD* __stdcall sub_1004b64f(int32_t arg1, int32_t arg2,
   int32_t arg3, int32_t arg4) */

void * grim_crt_buffer_free(int arg1,int arg2,int arg3,int arg4)

{
  void *pvVar1;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_100516c8;
  puStack_10 = &DAT_1004b7cc;
  local_14 = ExceptionList;
  local_8 = 0;
  pvVar1 = ExceptionList;
  ExceptionList = &local_14;
  while( true ) {
    arg3 = arg3 + -1;
    if (arg3 < 0) break;
    pvVar1 = (void *)(*(code *)arg4)();
  }
  ExceptionList = local_14;
  return pvVar1;
}



/* grim_crt_buffer_alloc_zeroed @ 1004b6c3 */

/* [binja] int32_t __stdcall sub_1004b6c3(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int grim_crt_buffer_alloc_zeroed(int arg1,int arg2,int arg3,int arg4)

{
  int iVar1;
  int local_20;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_100516d8;
  puStack_10 = &DAT_1004b7cc;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  for (local_20 = 0; local_20 < arg3; local_20 = local_20 + 1) {
    (*(code *)arg4)();
  }
  local_8 = 0xffffffff;
  iVar1 = grim_crt_buffer_realloc_zeroed();
  ExceptionList = local_14;
  return iVar1;
}



/* grim_crt_buffer_realloc_zeroed @ 1004b72d */

void grim_crt_buffer_realloc_zeroed(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x20) == 0) {
    grim_crt_buffer_free(*(int *)(unaff_EBP + 8),*(int *)(unaff_EBP + 0xc),*(int *)(unaff_EBP + -0x1c),
                 *(int *)(unaff_EBP + 0x18));
  }
  return;
}



/* grim_crt_cleanup_handler @ 1004b790 */

/* WARNING: Unable to track spacebase fully for stack */

void grim_crt_cleanup_handler(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


