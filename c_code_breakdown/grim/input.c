/* grim_input_init @ 10004920 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_input_init(void)

{
  _DAT_1005d3b0 = 0x3a83126f;
  DAT_10059dc4 = timeGetTime();
  _grim_fps = 0;
  grim_frame_delta_time = 0;
  grim_time_ms = 0;
  grim_suspended_flag = 0;
  DAT_1005bad0 = DAT_10059dc4;
  DAT_1005bad4 = DAT_10059dc4;
  timeBeginPeriod(1);
  return;
}



/* grim_input_update @ 10004970 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_input_update(void)

{
  ulonglong uVar1;
  uint uVar2;
  
  DAT_10059dc4 = DAT_1005bad0;
  do {
    DAT_1005bad0 = timeGetTime();
    uVar2 = DAT_1005bad0 - DAT_10059dc4;
  } while (uVar2 < 2);
  if (grim_suspended_flag == '\0') {
    grim_time_ms = grim_time_ms + uVar2;
    DAT_1005d814 = DAT_1005d814 + 1;
    grim_frame_delta_time = (float)uVar2 * _DAT_1005d3b0;
    DAT_1005d818 = DAT_1005d818 + uVar2;
  }
  else {
    grim_frame_delta_time = 0.0;
    DAT_1005bad4 = DAT_1005bad4 + uVar2;
  }
  uVar2 = DAT_1005d814;
  if (500 < DAT_1005d818) {
    DAT_1005d814 = 0;
    uVar1 = (ulonglong)DAT_1005d818;
    DAT_1005d818 = DAT_1005d818 - 500;
    _grim_fps = (float)uVar2 / ((float)uVar1 * _DAT_1005d3b0);
  }
  return;
}



/* grim_set_key_char_buffer @ 10005c20 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x54 (provisional): set input character ring buffer */

void grim_set_key_char_buffer(uchar *buffer,int *count,int size)

{
  grim_key_char_buffer_ptr = buffer;
  grim_key_char_count_ptr = (undefined *)count;
  grim_key_char_buffer_size = size;
  return;
}



/* grim_get_key_char @ 10005c40 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x50 (provisional) */

int grim_get_key_char(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (grim_key_char_queue_count != 0) {
    iVar1 = grim_key_char_queue;
    if (0 < grim_key_char_queue_count) {
      puVar2 = &grim_key_char_queue;
      iVar3 = grim_key_char_queue_count;
      do {
        *puVar2 = puVar2[1];
        puVar2 = puVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    grim_key_char_queue_count = grim_key_char_queue_count + -1;
    return iVar1;
  }
  return 0;
}



/* grim_joystick_axis_up @ 10006ea0 */

undefined4 grim_joystick_axis_up(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = grim_joystick_y_center;
  fVar1 = grim_joystick_deadzone;
  iVar3 = (*grim_interface_instance->vtable->grim_get_joystick_y)();
  if ((float)iVar3 - fVar2 < -fVar1) {
    return 1;
  }
  return 0;
}



/* grim_joystick_axis_down @ 10006ef0 */

undefined4 grim_joystick_axis_down(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = grim_joystick_y_center;
  fVar1 = grim_joystick_deadzone;
  iVar3 = (*grim_interface_instance->vtable->grim_get_joystick_y)();
  if (fVar1 < (float)iVar3 - fVar2) {
    return 1;
  }
  return 0;
}



/* grim_joystick_axis_left @ 10006f40 */

undefined4 grim_joystick_axis_left(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = grim_joystick_x_center;
  fVar1 = grim_joystick_deadzone;
  iVar3 = (*grim_interface_instance->vtable->grim_get_joystick_x)();
  if ((float)iVar3 - fVar2 < -fVar1) {
    return 1;
  }
  return 0;
}



/* grim_joystick_axis_right @ 10006f90 */

undefined4 grim_joystick_axis_right(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = grim_joystick_x_center;
  fVar1 = grim_joystick_deadzone;
  iVar3 = (*grim_interface_instance->vtable->grim_get_joystick_x)();
  if (fVar1 < (float)iVar3 - fVar2) {
    return 1;
  }
  return 0;
}



/* grim_is_key_active @ 10006fe0 */

/* Grim2D vtable 0x80: routes key/mouse/joystick IDs */

int __thiscall grim_is_key_active(void *this,int key)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  if (key < 0x100) {
    iVar2 = (**(code **)(*(int *)this + 0x44))(key);
    return iVar2;
  }
  if (key == 0x100) {
    iVar2 = (**(code **)(*(int *)this + 0x58))(0);
    return iVar2;
  }
  if (key == 0x101) {
    iVar2 = (**(code **)(*(int *)this + 0x58))(1);
    return iVar2;
  }
  if (key == 0x102) {
    iVar2 = (**(code **)(*(int *)this + 0x58))(2);
    return iVar2;
  }
  if (key == 0x103) {
    iVar2 = (**(code **)(*(int *)this + 0x58))(3);
    return iVar2;
  }
  if (key == 0x104) {
    iVar2 = (**(code **)(*(int *)this + 0x58))(4);
    return iVar2;
  }
  uVar3 = 1;
  do {
    if (key == uVar3 + 0x11e) {
      iVar2 = (**(code **)(*(int *)this + 0xa8))(uVar3 - 1);
      return iVar2;
    }
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 0xd);
  if (key == 0x131) {
    iVar2 = grim_joystick_axis_up();
    return iVar2;
  }
  if (key == 0x132) {
    iVar2 = grim_joystick_axis_down();
    return iVar2;
  }
  if (key == 0x133) {
    iVar2 = grim_joystick_axis_left();
    return iVar2;
  }
  if (key == 0x134) {
    iVar2 = grim_joystick_axis_right();
    return iVar2;
  }
  if (key == 0x13f) {
    fVar1 = (float)grim_joystick_device_state.lX;
  }
  else if (key == 0x140) {
    fVar1 = (float)grim_joystick_device_state.lY;
  }
  else if (key == 0x141) {
    fVar1 = (float)grim_joystick_device_state.lZ;
  }
  else if (key == 0x153) {
    fVar1 = (float)grim_joystick_device_state.lRx;
  }
  else if (key == 0x154) {
    fVar1 = (float)grim_joystick_device_state.lRy;
  }
  else {
    if (key != 0x155) {
      if (grim_render_callback_ptr == (int *)0x0) {
        return uVar3 & 0xffffff00;
      }
      iVar2 = 0;
      iVar5 = 0x16d;
      do {
        uVar3 = 0;
        iVar4 = iVar5;
        do {
          if (key == iVar4) {
            iVar2 = (**(code **)(*grim_render_callback_ptr + 0xc))(iVar2,uVar3);
            return iVar2;
          }
          uVar3 = uVar3 + 1;
          iVar4 = iVar4 + 1;
        } while ((int)uVar3 < 5);
        iVar5 = iVar5 + 5;
        iVar2 = iVar2 + 1;
      } while (iVar5 < 0x17c);
      return uVar3 & 0xffffff00;
    }
    fVar1 = (float)grim_joystick_device_state.lRz;
  }
  if (0.5 < ABS(fVar1 * 0.001)) {
    return 1;
  }
  return 0;
}



/* grim_is_key_down @ 10007320 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x44 (provisional) */

int grim_is_key_down(uint key)

{
  int iVar1;
  
  iVar1 = grim_keyboard_key_down(key);
  return iVar1;
}



/* grim_flush_input @ 10007330 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x4c (provisional): clear buffered input/device state */

void grim_flush_input(void)

{
  int iVar1;
  undefined4 *puVar2;
  DWORD DStack_4;
  
  DStack_4 = 10;
  puVar2 = &grim_keyboard_state;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  iVar1 = 0;
  do {
    (*grim_keyboard_device->lpVtbl->GetDeviceData)
              (grim_keyboard_device,0x14,(LPDIDEVICEOBJECTDATA)&grim_keyboard_event_buffer,&DStack_4
               ,0);
    if (99 < iVar1) break;
    iVar1 = iVar1 + 1;
  } while (DStack_4 != 0);
  grim_key_char_queue_count = 0;
  puVar2 = &grim_keyboard_state;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}



/* grim_was_key_pressed @ 10007390 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Grim2D vtable 0x48 (provisional) */

int grim_was_key_pressed(uint key)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = grim_keyboard_key_down(key);
  if ((char)iVar2 == '\0') {
    uVar3 = key & 0xff;
    (&grim_key_cooldown_table)[uVar3] = 0;
    (&DAT_10059f44)[uVar3] = 1;
  }
  else {
    uVar4 = key & 0xff;
    fVar1 = (float)(&grim_key_cooldown_table)[uVar4];
    uVar3 = CONCAT22((short)((uint)iVar2 >> 0x10),
                     (ushort)(fVar1 < 0.0) << 8 | (ushort)NAN(fVar1) << 10 |
                     (ushort)(fVar1 == 0.0) << 0xe);
    if ((fVar1 == 0.0) != 0) {
      fVar1 = _DAT_10053044;
      if ((&DAT_10059f44)[uVar4] == '\0') {
        fVar1 = _DAT_10053044 * 0.2;
      }
      (&grim_key_cooldown_table)[uVar4] = fVar1;
      (&DAT_10059f44)[uVar4] = 0;
      return CONCAT31((int3)(uVar3 >> 8),1);
    }
  }
  return uVar3 & 0xffffff00;
}



/* grim_is_mouse_button_down @ 10007410 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x58: cached mouse button state or poll */

int grim_is_mouse_button_down(int button)

{
  int iVar1;
  
  if (grim_hide_cursor_flag != '\0') {
    return CONCAT31((int3)((uint)button >> 8),(&grim_mouse_button_cache)[button]);
  }
  iVar1 = grim_mouse_button_down(button);
  return iVar1;
}



/* grim_was_mouse_button_pressed @ 10007440 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x5c (provisional): edge-triggered mouse button */

int grim_was_mouse_button_pressed(int button)

{
  char cVar1;
  undefined4 in_EAX;
  uint3 uVar3;
  undefined4 uVar2;
  int *in_ECX;
  undefined1 uVar4;
  
  uVar3 = (uint3)((uint)in_EAX >> 8);
  if (grim_hide_cursor_flag == '\0') {
    cVar1 = (**(code **)(*in_ECX + 0x58))(button);
    if ((cVar1 == '\0') || ((&grim_mouse_button_latch)[button] == '\0')) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
    uVar2 = (**(code **)(*in_ECX + 0x58))(button);
    (&grim_mouse_button_latch)[button] = (char)uVar2 == '\0';
    return CONCAT31((int3)((uint)uVar2 >> 8),uVar4);
  }
  cVar1 = (&grim_mouse_button_cache)[button];
  if ((cVar1 != '\0') && ((&grim_mouse_button_latch)[button] != '\0')) {
    (&grim_mouse_button_latch)[button] = cVar1 == '\0';
    return CONCAT31(uVar3,1);
  }
  (&grim_mouse_button_latch)[button] = cVar1 == '\0';
  return (uint)uVar3 << 8;
}



/* grim_get_mouse_dx @ 100074d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x70: cached mouse delta X */

float grim_get_mouse_dx(void)

{
  return _grim_mouse_dx;
}



/* grim_get_mouse_dy @ 100074e0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x74: cached mouse delta Y */

float grim_get_mouse_dy(void)

{
  return _grim_mouse_dy;
}



/* grim_get_mouse_dx_indexed @ 100074f0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x78: alias of get_mouse_dx */

float grim_get_mouse_dx_indexed(int index)

{
  int *in_ECX;
  float10 fVar1;
  
  fVar1 = (float10)(**(code **)(*in_ECX + 0x70))();
  return (float)fVar1;
}



/* grim_get_mouse_dy_indexed @ 10007500 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x7c: alias of get_mouse_dy */

float grim_get_mouse_dy_indexed(int index)

{
  int *in_ECX;
  float10 fVar1;
  
  fVar1 = (float10)(**(code **)(*in_ECX + 0x74))();
  return (float)fVar1;
}



/* grim_get_mouse_x @ 10007510 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x68: cached mouse X position */

float grim_get_mouse_x(void)

{
  return grim_prev_mouse_x;
}



/* grim_get_mouse_y @ 10007520 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x6c: cached mouse Y position */

float grim_get_mouse_y(void)

{
  return grim_prev_mouse_y;
}



/* grim_set_mouse_pos @ 10007530 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x64: set cached mouse position */

void grim_set_mouse_pos(float x,float y)

{
  grim_mouse_x = x;
  grim_mouse_y = y;
  grim_prev_mouse_x = x;
  grim_prev_mouse_y = y;
  return;
}



/* grim_get_mouse_wheel_delta @ 10007560 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x60 (provisional) */

float grim_get_mouse_wheel_delta(void)

{
  if (grim_hide_cursor_flag != '\0') {
    return _DAT_1005d3b8;
  }
  return _DAT_1005db58;
}



/* grim_get_joystick_x @ 10007580 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x98 (provisional): joystick axis X */

int grim_get_joystick_x(void)

{
  return grim_joystick_device_state.lX;
}



/* grim_get_joystick_y @ 10007590 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x9c (provisional): joystick axis Y */

int grim_get_joystick_y(void)

{
  return grim_joystick_device_state.lY;
}



/* grim_get_joystick_z @ 100075a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xa0 (provisional): joystick axis Z */

int grim_get_joystick_z(void)

{
  return grim_joystick_device_state.lZ;
}



/* grim_get_joystick_pov @ 100075b0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xa4 (provisional): joystick POV hat value */

int grim_get_joystick_pov(int index)

{
  return grim_joystick_device_state.rgdwPOV[index];
}



/* grim_is_joystick_button_down @ 100075c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xa8 (provisional): joystick button state */

int grim_is_joystick_button_down(int button)

{
  byte bVar1;
  undefined3 extraout_var;
  
  bVar1 = grim_joystick_button_down(button);
  return CONCAT31(extraout_var,bVar1);
}



/* grim_joystick_init @ 1000a1c0 */

/* initializes DirectInput joystick device and acquires it */

int __cdecl grim_joystick_init(int hwnd)

{
  HWND pHVar1;
  HMODULE pHVar2;
  uint uVar3;
  HRESULT HVar4;
  uint3 uVar6;
  int iVar5;
  DWORD DVar7;
  REFIID pIVar8;
  LPDIRECTINPUT8A *ppIVar9;
  LPDIRECTINPUT8A pIVar10;
  
  if ((hwnd == 0) && (pHVar1 = GetForegroundWindow(), pHVar1 == (HWND)0x0)) {
    GetDesktopWindow();
  }
  if (grim_dinput_joystick == (LPDIRECTINPUT8A)0x0) {
    ppIVar9 = &grim_dinput_joystick;
    pIVar8 = (REFIID)&grim_guid_directinput8;
    DVar7 = 0x800;
    pIVar10 = grim_dinput_joystick;
    pHVar2 = GetModuleHandleA((LPCSTR)0x0);
    uVar3 = DirectInput8Create(pHVar2,DVar7,pIVar8,ppIVar9,(LPUNKNOWN)pIVar10);
    if ((int)uVar3 < 0) {
      grim_dinput_joystick = (LPDIRECTINPUT8A)0x0;
      return uVar3 & 0xffffff00;
    }
  }
  if (grim_joystick_device == (LPDIRECTINPUTDEVICE8A)0x0) {
    HVar4 = (*grim_dinput_joystick->lpVtbl->EnumDevices)
                      (grim_dinput_joystick,4,(LPDIENUMDEVICESCALLBACKA)&LAB_1000a110,(LPVOID)0x0,1)
    ;
    uVar6 = (uint3)((uint)HVar4 >> 8);
    if (HVar4 < 0) {
      return (uint)uVar6 << 8;
    }
    if (grim_joystick_found_flag == '\0') {
      return (uint)uVar6 << 8;
    }
    uVar3 = (*grim_joystick_device->lpVtbl->SetDataFormat)
                      (grim_joystick_device,(LPCDIDATAFORMAT)&DAT_1004fe74);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_joystick_device->lpVtbl->SetCooperativeLevel)(grim_joystick_device,(HWND)hwnd,5);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_joystick_device->lpVtbl->EnumObjects)
                      (grim_joystick_device,(LPDIENUMDEVICEOBJECTSCALLBACKA)&LAB_1000a150,
                       (LPVOID)hwnd,0);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    if (grim_joystick_device != (LPDIRECTINPUTDEVICE8A)0x0) {
      (*grim_joystick_device->lpVtbl->Acquire)(grim_joystick_device);
    }
  }
  iVar5 = grim_joystick_poll();
  return CONCAT31((int3)((uint)iVar5 >> 8),1);
}



/* grim_joystick_poll @ 1000a2b0 */

/* polls the joystick device and updates cached state */

int grim_joystick_poll(void)

{
  HRESULT HVar1;
  uint uVar2;
  
  uVar2 = 0;
  if ((grim_dinput_joystick != (LPDIRECTINPUT8A)0x0) &&
     (uVar2 = 0, grim_joystick_device != (LPDIRECTINPUTDEVICE8A)0x0)) {
    HVar1 = (*grim_joystick_device->lpVtbl->Poll)(grim_joystick_device);
    if (-1 < HVar1) {
      HVar1 = (*grim_joystick_device->lpVtbl->GetDeviceState)
                        (grim_joystick_device,0x110,&grim_joystick_device_state);
      return CONCAT31((int3)((uint)HVar1 >> 8),-1 < HVar1);
    }
    uVar2 = (*grim_joystick_device->lpVtbl->Acquire)(grim_joystick_device);
    while (uVar2 == 0x8007001e) {
      uVar2 = (*grim_joystick_device->lpVtbl->Acquire)(grim_joystick_device);
    }
  }
  return uVar2 & 0xffffff00;
}



/* grim_joystick_button_down @ 1000a310 */

byte __cdecl grim_joystick_button_down(uint param_1)

{
  return grim_joystick_device_state.rgbButtons[param_1 & 0xff] >> 7;
}



/* grim_joystick_shutdown @ 1000a330 */

void grim_joystick_shutdown(void)

{
  if (grim_joystick_device != (LPDIRECTINPUTDEVICE8A)0x0) {
    (*grim_joystick_device->lpVtbl->Unacquire)(grim_joystick_device);
    (*grim_joystick_device->lpVtbl->Release)(grim_joystick_device);
    grim_joystick_device = (LPDIRECTINPUTDEVICE8A)0x0;
  }
  if (grim_dinput_joystick != (LPDIRECTINPUT8A)0x0) {
    (*grim_dinput_joystick->lpVtbl->Release)(grim_dinput_joystick);
    grim_dinput_joystick = (LPDIRECTINPUT8A)0x0;
  }
  return;
}



/* grim_keyboard_key_down @ 1000a370 */

/* reads the cached key state array */

int __cdecl grim_keyboard_key_down(uint key)

{
  return (uint)(*(byte *)((int)&grim_keyboard_state + (key & 0xff)) >> 7);
}



/* grim_keyboard_init @ 1000a390 */

/* initializes DirectInput keyboard device and acquires it */

int __cdecl grim_keyboard_init(int hwnd)

{
  HWND pHVar1;
  HMODULE pHVar2;
  uint uVar3;
  int iVar4;
  DWORD DVar5;
  REFIID pIVar6;
  LPDIRECTINPUT8A *ppIVar7;
  LPDIRECTINPUT8A pIVar8;
  DIPROPHEADER DStack_14;
  undefined4 uStack_4;
  
  if ((hwnd == 0) && (pHVar1 = GetForegroundWindow(), pHVar1 == (HWND)0x0)) {
    GetDesktopWindow();
  }
  if (grim_dinput_keyboard == (LPDIRECTINPUT8A)0x0) {
    ppIVar7 = &grim_dinput_keyboard;
    pIVar6 = (REFIID)&grim_guid_directinput8;
    DVar5 = 0x800;
    pIVar8 = grim_dinput_keyboard;
    pHVar2 = GetModuleHandleA((LPCSTR)0x0);
    uVar3 = DirectInput8Create(pHVar2,DVar5,pIVar6,ppIVar7,(LPUNKNOWN)pIVar8);
    if ((int)uVar3 < 0) {
      grim_dinput_keyboard = (LPDIRECTINPUT8A)0x0;
      return uVar3 & 0xffffff00;
    }
  }
  if (grim_keyboard_device == (LPDIRECTINPUTDEVICE8A)0x0) {
    uVar3 = (*grim_dinput_keyboard->lpVtbl->CreateDevice)
                      (grim_dinput_keyboard,(REFGUID)&grim_guid_keyboard,&grim_keyboard_device,
                       (LPUNKNOWN)0x0);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_keyboard_device->lpVtbl->SetDataFormat)
                      (grim_keyboard_device,(LPCDIDATAFORMAT)&DAT_1005007c);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_keyboard_device->lpVtbl->SetCooperativeLevel)
                      (grim_keyboard_device,(HWND)hwnd,0x16);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    DStack_14.dwSize = 0x14;
    DStack_14.dwHeaderSize = 0x10;
    DStack_14.dwObj = 0;
    DStack_14.dwHow = 0;
    uStack_4 = 10;
    (*grim_keyboard_device->lpVtbl->SetProperty)(grim_keyboard_device,(REFGUID)0x1,&DStack_14);
    if (grim_keyboard_device != (LPDIRECTINPUTDEVICE8A)0x0) {
      (*grim_keyboard_device->lpVtbl->Acquire)(grim_keyboard_device);
    }
  }
  iVar4 = grim_keyboard_poll();
  return CONCAT31((int3)((uint)iVar4 >> 8),1);
}



/* grim_keyboard_poll @ 1000a4a0 */

/* polls the keyboard device and updates cached key state */

int grim_keyboard_poll(void)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  DWORD DStack_4;
  
  uVar2 = 0;
  if (grim_keyboard_device != (LPDIRECTINPUTDEVICE8A)0x0) {
    uVar2 = (*grim_keyboard_device->lpVtbl->Acquire)(grim_keyboard_device);
    while ((uVar2 == 0x8007001e || (uVar2 == 0x80070005))) {
      uVar2 = (*grim_keyboard_device->lpVtbl->Acquire)(grim_keyboard_device);
    }
    if (-1 < (int)uVar2) {
      puVar5 = &grim_keyboard_state;
      for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      (*grim_keyboard_device->lpVtbl->GetDeviceState)
                (grim_keyboard_device,0x100,&grim_keyboard_state);
      DStack_4 = 10;
      piVar3 = (int *)(*grim_keyboard_device->lpVtbl->GetDeviceData)
                                (grim_keyboard_device,0x14,
                                 (LPDIDEVICEOBJECTDATA)&grim_keyboard_event_buffer,&DStack_4,0);
      if ((-1 < (int)piVar3) && (0 < (int)DStack_4)) {
        piVar3 = &grim_keyboard_event_buffer;
        do {
          iVar4 = *piVar3;
          piVar1 = piVar3 + 1;
          piVar3 = piVar3 + 5;
          DStack_4 = DStack_4 - 1;
          *(char *)((int)&grim_keyboard_state + iVar4) = (char)*piVar1;
        } while (DStack_4 != 0);
      }
      return CONCAT31((int3)((uint)piVar3 >> 8),1);
    }
  }
  return uVar2 & 0xffffff00;
}



/* grim_keyboard_shutdown @ 1000a550 */

/* releases DirectInput keyboard objects */

void grim_keyboard_shutdown(void)

{
  if (grim_keyboard_device != (LPDIRECTINPUTDEVICE8A)0x0) {
    (*grim_keyboard_device->lpVtbl->Unacquire)(grim_keyboard_device);
    (*grim_keyboard_device->lpVtbl->Release)(grim_keyboard_device);
    grim_keyboard_device = (LPDIRECTINPUTDEVICE8A)0x0;
  }
  if (grim_dinput_keyboard != (LPDIRECTINPUT8A)0x0) {
    (*grim_dinput_keyboard->lpVtbl->Release)(grim_dinput_keyboard);
    grim_dinput_keyboard = (LPDIRECTINPUT8A)0x0;
  }
  return;
}



/* grim_mouse_button_down @ 1000a590 */

/* reads the cached mouse button state */

int __cdecl grim_mouse_button_down(int button)

{
  return CONCAT31((int3)((uint)button >> 8),grim_mouse_state.rgbButtons[button] >> 7);
}



/* grim_mouse_init @ 1000a5a0 */

/* initializes DirectInput mouse device and acquires it */

int grim_mouse_init(void)

{
  HWND hwnd;
  HWND pHVar1;
  HMODULE pHVar2;
  uint uVar3;
  int iVar4;
  DWORD DVar5;
  REFIID pIVar6;
  LPDIRECTINPUT8A *ppIVar7;
  LPDIRECTINPUT8A pIVar8;
  
  hwnd = grim_window_handle;
  if ((grim_window_handle == (HWND)0x0) && (pHVar1 = GetForegroundWindow(), pHVar1 == (HWND)0x0)) {
    GetDesktopWindow();
  }
  if (grim_dinput_mouse == (LPDIRECTINPUT8A)0x0) {
    ppIVar7 = &grim_dinput_mouse;
    pIVar6 = (REFIID)&grim_guid_directinput8;
    DVar5 = 0x800;
    pIVar8 = grim_dinput_mouse;
    pHVar2 = GetModuleHandleA((LPCSTR)0x0);
    uVar3 = DirectInput8Create(pHVar2,DVar5,pIVar6,ppIVar7,(LPUNKNOWN)pIVar8);
    if ((int)uVar3 < 0) {
      grim_dinput_mouse = (LPDIRECTINPUT8A)0x0;
      return uVar3 & 0xffffff00;
    }
  }
  if (grim_mouse_device == (LPDIRECTINPUTDEVICE8A)0x0) {
    uVar3 = (*grim_dinput_mouse->lpVtbl->CreateDevice)
                      (grim_dinput_mouse,(REFGUID)&DAT_100502ac,&grim_mouse_device,(LPUNKNOWN)0x0);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_mouse_device->lpVtbl->SetDataFormat)
                      (grim_mouse_device,(LPCDIDATAFORMAT)&DAT_10050284);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    uVar3 = (*grim_mouse_device->lpVtbl->SetCooperativeLevel)(grim_mouse_device,hwnd,5);
    if ((int)uVar3 < 0) {
      return uVar3 & 0xffffff00;
    }
    if (grim_mouse_device != (LPDIRECTINPUTDEVICE8A)0x0) {
      (*grim_mouse_device->lpVtbl->Acquire)(grim_mouse_device);
    }
  }
  iVar4 = grim_mouse_poll();
  return CONCAT31((int3)((uint)iVar4 >> 8),1);
}



/* grim_mouse_poll @ 1000a670 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* polls the mouse device and updates cached position/delta */

int grim_mouse_poll(void)

{
  int iVar1;
  int iVar2;
  HRESULT HVar3;
  int extraout_EAX;
  int iVar4;
  
  iVar2 = 0;
  if (grim_mouse_device != (LPDIRECTINPUTDEVICE8A)0x0) {
    grim_mouse_state.lX = 0;
    _DAT_1005db58 = 0.0;
    grim_mouse_state.lY = 0;
    _grim_mouse_dy = 0.0;
    grim_mouse_state.lZ = 0;
    _grim_mouse_dx = 0.0;
    grim_mouse_state.rgbButtons[0] = '\0';
    grim_mouse_state.rgbButtons[1] = '\0';
    grim_mouse_state.rgbButtons[2] = '\0';
    grim_mouse_state.rgbButtons[3] = '\0';
    grim_mouse_state.rgbButtons[4] = '\0';
    grim_mouse_state.rgbButtons[5] = '\0';
    grim_mouse_state.rgbButtons[6] = '\0';
    grim_mouse_state.rgbButtons[7] = '\0';
    iVar1 = (*grim_mouse_device->lpVtbl->GetDeviceState)(grim_mouse_device,0x14,&grim_mouse_state);
    iVar2 = 0;
    while (-1 < iVar1) {
      iVar4 = iVar2 + 1;
      _grim_mouse_dx = (float)grim_mouse_state.lX + _grim_mouse_dx;
      _grim_mouse_dy = (float)grim_mouse_state.lY + _grim_mouse_dy;
      _DAT_1005db58 = (float)grim_mouse_state.lZ + _DAT_1005db58;
      if ((99 < iVar2) ||
         (((grim_mouse_state.lX == 0 && (grim_mouse_state.lY == 0)) &&
          (iVar2 = 0, grim_mouse_state.lZ == 0)))) {
        if (2 < iVar4) {
          grim_noop();
          iVar2 = extraout_EAX;
        }
        grim_mouse_x = grim_mouse_x + _grim_mouse_dx;
        grim_mouse_y = grim_mouse_y + _grim_mouse_dy;
        _DAT_1005db4c = _DAT_1005db4c + _DAT_1005db58;
        goto LAB_1000a7cb;
      }
      grim_mouse_state.lX = 0;
      grim_mouse_state.lY = 0;
      grim_mouse_state.lZ = 0;
      grim_mouse_state.rgbButtons[0] = '\0';
      grim_mouse_state.rgbButtons[1] = '\0';
      grim_mouse_state.rgbButtons[2] = '\0';
      grim_mouse_state.rgbButtons[3] = '\0';
      grim_mouse_state.rgbButtons[4] = '\0';
      grim_mouse_state.rgbButtons[5] = '\0';
      grim_mouse_state.rgbButtons[6] = '\0';
      grim_mouse_state.rgbButtons[7] = '\0';
      iVar1 = (*grim_mouse_device->lpVtbl->GetDeviceState)(grim_mouse_device,0x14,&grim_mouse_state)
      ;
      iVar2 = iVar4;
    }
    iVar2 = (*grim_mouse_device->lpVtbl->Acquire)(grim_mouse_device);
    if (iVar2 == -0x7ff8ffe2) {
      do {
        HVar3 = (*grim_mouse_device->lpVtbl->Acquire)(grim_mouse_device);
      } while (HVar3 == -0x7ff8ffe2);
      return CONCAT31((int3)((uint)HVar3 >> 8),1);
    }
  }
LAB_1000a7cb:
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}



/* grim_mouse_shutdown @ 1000a7d0 */

/* releases DirectInput mouse objects */

void grim_mouse_shutdown(void)

{
  if (grim_mouse_device != (LPDIRECTINPUTDEVICE8A)0x0) {
    (*grim_mouse_device->lpVtbl->Unacquire)(grim_mouse_device);
    (*grim_mouse_device->lpVtbl->Release)(grim_mouse_device);
    grim_mouse_device = (LPDIRECTINPUTDEVICE8A)0x0;
  }
  if (grim_dinput_mouse != (LPDIRECTINPUT8A)0x0) {
    (*grim_dinput_mouse->lpVtbl->Release)(grim_dinput_mouse);
    grim_dinput_mouse = (LPDIRECTINPUT8A)0x0;
  }
  return;
}


