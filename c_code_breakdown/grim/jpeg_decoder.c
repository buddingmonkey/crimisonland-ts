/* grim_jpg_error_exit @ 10010dd0 */

void grim_jpg_error_exit(int *param_1)

{
  (**(code **)(*param_1 + 8))(param_1);
                    /* WARNING: Subroutine does not return */
  longjmp((int *)(*param_1 + 0x84),1);
}



/* grim_jpg_start_decompress @ 1001bf5e */

int grim_jpg_start_decompress(void)

{
  LONG LVar1;
  int iVar2;
  int extraout_ECX;
  int extraout_ECX_00;
  int local_14;
  DWORD local_10 [2];
  HKEY local_8;
  
  LVar1 = RegOpenKeyA((HKEY)0x80000002,"Software\\Microsoft\\Direct3D",&local_8);
  iVar2 = extraout_ECX;
  if (LVar1 == 0) {
    local_10[1] = 4;
    LVar1 = RegQueryValueExA(local_8,"DisableMMX",(LPDWORD)0x0,local_10,(LPBYTE)&local_14,
                             local_10 + 1);
    if (((LVar1 == 0) && (local_10[0] == 4)) && (local_14 != 0)) {
      RegCloseKey(local_8);
      DAT_10054498 = 0;
      return 0;
    }
    RegCloseKey(local_8);
    iVar2 = extraout_ECX_00;
  }
  if (DAT_10054498 < 0) {
    DAT_10054498 = 0;
    iVar2 = grim_d3dx_sse_feature_init(iVar2);
    if (iVar2 != 0) {
      DAT_10054498 = 1;
    }
  }
  return DAT_10054498;
}



/* grim_jpg_create_decompress @ 1001c265 */

void __cdecl grim_jpg_create_decompress(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  
  param_1[1] = 0;
  if (param_2 != 0x3d) {
    *(undefined4 *)(*param_1 + 0x14) = 10;
    *(undefined4 *)(*param_1 + 0x18) = 0x3d;
    *(int *)(*param_1 + 0x1c) = param_2;
    (**(code **)*param_1)(param_1);
  }
  if (param_3 != 0x1a8) {
    *(undefined4 *)(*param_1 + 0x14) = 0x13;
    *(undefined4 *)(*param_1 + 0x18) = 0x1a8;
    *(int *)(*param_1 + 0x1c) = param_3;
    (**(code **)*param_1)(param_1);
  }
  iVar3 = *param_1;
  piVar1 = param_1;
  for (iVar2 = 0x6a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
  }
  *param_1 = iVar3;
  *(undefined1 *)(param_1 + 3) = 1;
  grim_jpg_mem_init(param_1);
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[0x24] = 0;
  param_1[0x25] = 0;
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  iVar3 = 4;
  piVar1 = param_1 + 0x2c;
  do {
    piVar1[-4] = 0;
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  grim_jpg_marker_init((int)param_1);
  grim_jpg_error_init((int)param_1);
  if (grim_jpg_idct_mode == '\x02') {
    iVar3 = grim_check_sse2_available(unaff_ESI);
    grim_jpg_idct_mode = (char)iVar3;
  }
  param_1[4] = 200;
  return;
}



/* grim_jpg_default_colorspace @ 1001c32a */

void grim_jpg_default_colorspace(void)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *unaff_ESI;
  
  iVar2 = unaff_ESI[8];
  if (iVar2 == 1) {
    unaff_ESI[9] = 1;
    unaff_ESI[10] = 1;
    goto LAB_1001c456;
  }
  if (iVar2 == 3) {
    if ((char)unaff_ESI[0x40] == '\0') {
      if (*(char *)((int)unaff_ESI + 0x106) == '\0') {
        piVar3 = (int *)unaff_ESI[0x31];
        iVar2 = *piVar3;
        iVar4 = piVar3[0x15];
        iVar5 = piVar3[0x2a];
        if (iVar2 == 1) {
          if ((iVar4 != 2) || (iVar5 != 3)) goto LAB_1001c408;
        }
        else {
          if (((iVar2 == 0x52) && (iVar4 == 0x47)) && (iVar5 == 0x42)) {
            unaff_ESI[9] = 2;
            goto LAB_1001c42c;
          }
LAB_1001c408:
          iVar6 = *unaff_ESI;
          *(int *)(iVar6 + 0x18) = iVar2;
          *(int *)(iVar6 + 0x1c) = iVar4;
          *(int *)(iVar6 + 0x20) = iVar5;
          *(undefined4 *)(*unaff_ESI + 0x14) = 0x6b;
          (**(code **)(*unaff_ESI + 4))();
        }
        unaff_ESI[9] = 3;
      }
      else {
        bVar1 = *(byte *)((int)unaff_ESI + 0x107);
        if (bVar1 != 0) {
          if (bVar1 != 1) {
            *(undefined4 *)(*unaff_ESI + 0x14) = 0x6e;
            *(uint *)(*unaff_ESI + 0x18) = (uint)*(byte *)((int)unaff_ESI + 0x107);
            (**(code **)(*unaff_ESI + 4))();
          }
          goto LAB_1001c3d7;
        }
        unaff_ESI[9] = 2;
      }
    }
    else {
LAB_1001c3d7:
      unaff_ESI[9] = 3;
    }
LAB_1001c42c:
    unaff_ESI[10] = 2;
    goto LAB_1001c456;
  }
  if (iVar2 != 4) {
    unaff_ESI[9] = 0;
    unaff_ESI[10] = 0;
    goto LAB_1001c456;
  }
  if (*(char *)((int)unaff_ESI + 0x106) == '\0') {
LAB_1001c38e:
    unaff_ESI[9] = 4;
  }
  else {
    bVar1 = *(byte *)((int)unaff_ESI + 0x107);
    if (bVar1 == 0) goto LAB_1001c38e;
    if (bVar1 != 2) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x6e;
      *(uint *)(*unaff_ESI + 0x18) = (uint)*(byte *)((int)unaff_ESI + 0x107);
      (**(code **)(*unaff_ESI + 4))();
    }
    unaff_ESI[9] = 5;
  }
  unaff_ESI[10] = 4;
LAB_1001c456:
  *(undefined1 *)(unaff_ESI + 0x10) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x41) = 0;
  unaff_ESI[0xe] = 0;
  unaff_ESI[0xf] = 0x3ff00000;
  unaff_ESI[0x11] = 0;
  *(undefined1 *)((int)unaff_ESI + 0x4a) = 0;
  unaff_ESI[0x1d] = 0;
  *(undefined1 *)(unaff_ESI + 0x16) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x59) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x5a) = 0;
  unaff_ESI[0xb] = 1;
  unaff_ESI[0xc] = 1;
  *(undefined1 *)(unaff_ESI + 0x12) = 1;
  *(undefined1 *)((int)unaff_ESI + 0x49) = 1;
  unaff_ESI[0x13] = 2;
  *(undefined1 *)(unaff_ESI + 0x14) = 1;
  unaff_ESI[0x15] = 0x100;
  return;
}



/* grim_jpg_consume_input @ 1001c49d */

int __cdecl grim_jpg_consume_input(int *param_1)

{
  int iVar1;
  
  iVar1 = param_1[4];
  if (iVar1 == 200) {
    (**(code **)(param_1[99] + 4))(param_1);
    (**(code **)(param_1[5] + 8))(param_1);
    param_1[4] = 0xc9;
  }
  else if (iVar1 != 0xc9) {
    if (iVar1 == 0xca) {
      return 1;
    }
    if ((0xca < iVar1) && ((iVar1 < 0xd1 || (iVar1 == 0xd2)))) {
      iVar1 = (**(code **)param_1[99])(param_1);
      return iVar1;
    }
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
    return 0;
  }
  iVar1 = (**(code **)param_1[99])(param_1);
  if (iVar1 == 1) {
    grim_jpg_default_colorspace();
    param_1[4] = 0xca;
  }
  return iVar1;
}



/* grim_jpg_destroy_decompress @ 1001c537 */

undefined4 __cdecl grim_jpg_destroy_decompress(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1[4];
  if (((iVar1 == 0xcd) || (iVar1 == 0xce)) && ((char)param_1[0x10] == '\0')) {
    if ((uint)param_1[0x1e] < (uint)param_1[0x18]) {
      *(undefined4 *)(*param_1 + 0x14) = 0x42;
      (**(code **)*param_1)(param_1);
    }
    (**(code **)(param_1[0x5f] + 4))(param_1);
    param_1[4] = 0xd2;
  }
  else if (iVar1 == 0xcf) {
    param_1[4] = 0xd2;
  }
  else if (iVar1 != 0xd2) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  do {
    if (*(char *)(param_1[99] + 0x11) != '\0') {
      (**(code **)(param_1[5] + 0x18))(param_1);
      uVar2 = grim_jpg_mem_term((int)param_1);
      return CONCAT31((int3)((uint)uVar2 >> 8),1);
    }
    iVar1 = (**(code **)param_1[99])(param_1);
  } while (iVar1 != 0);
  return 0;
}



/* grim_jpg_read_header @ 1001c5de */

int __cdecl grim_jpg_read_header(int *param_1,char param_2)

{
  int iVar1;
  
  if ((param_1[4] != 200) && (param_1[4] != 0xc9)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  iVar1 = grim_jpg_consume_input(param_1);
  if (iVar1 == 1) {
    iVar1 = 1;
  }
  else if (iVar1 == 2) {
    if (param_2 != '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x32;
      (**(code **)*param_1)(param_1);
    }
    grim_jpg_mem_term((int)param_1);
    return 2;
  }
  return iVar1;
}



/* grim_jpg_process_scanlines @ 1001c641 */

uint grim_jpg_process_scanlines(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int unaff_ESI;
  
  if (*(int *)(unaff_ESI + 0x10) != 0xcc) {
    (*(code *)**(undefined4 **)(unaff_ESI + 0x17c))();
    *(undefined4 *)(unaff_ESI + 0x78) = 0;
    *(undefined4 *)(unaff_ESI + 0x10) = 0xcc;
  }
  if (*(char *)(*(int *)(unaff_ESI + 0x17c) + 8) != '\0') {
    puVar1 = (uint *)(unaff_ESI + 0x78);
    do {
      uVar3 = *puVar1;
      if (uVar3 < *(uint *)(unaff_ESI + 0x60)) {
        do {
          if (*(int *)(unaff_ESI + 8) != 0) {
            *(uint *)(*(int *)(unaff_ESI + 8) + 4) = uVar3;
            *(undefined4 *)(*(int *)(unaff_ESI + 8) + 8) = *(undefined4 *)(unaff_ESI + 0x60);
            (*(code *)**(undefined4 **)(unaff_ESI + 8))();
          }
          uVar2 = *puVar1;
          (**(code **)(*(int *)(unaff_ESI + 0x180) + 4))();
          uVar3 = *puVar1;
          if (uVar3 == uVar2) {
            return uVar3 & 0xffffff00;
          }
        } while (uVar3 < *(uint *)(unaff_ESI + 0x60));
      }
      (**(code **)(*(int *)(unaff_ESI + 0x17c) + 4))();
      (*(code *)**(undefined4 **)(unaff_ESI + 0x17c))();
      *puVar1 = 0;
    } while (*(char *)(*(int *)(unaff_ESI + 0x17c) + 8) != '\0');
  }
  iVar4 = (*(char *)(unaff_ESI + 0x41) != '\0') + 0xcd;
  *(int *)(unaff_ESI + 0x10) = iVar4;
  return CONCAT31((int3)((uint)iVar4 >> 8),1);
}



/* grim_jpg_read_scanlines @ 1001c6ea */

int * __cdecl grim_jpg_read_scanlines(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  
  piVar1 = param_1;
  if (param_1[4] != 0xcd) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  if ((uint)piVar1[0x1e] < (uint)piVar1[0x18]) {
    if (piVar1[2] != 0) {
      *(int *)(piVar1[2] + 4) = piVar1[0x1e];
      *(int *)(piVar1[2] + 8) = piVar1[0x18];
      (**(code **)piVar1[2])(piVar1);
    }
    param_1 = (int *)0x0;
    (**(code **)(piVar1[0x60] + 4))(piVar1,param_2,&param_1,param_3);
    piVar1[0x1e] = piVar1[0x1e] + (int)param_1;
  }
  else {
    *(undefined4 *)(*piVar1 + 0x14) = 0x77;
    (**(code **)(*piVar1 + 4))(piVar1,0xffffffff);
    param_1 = (int *)0x0;
  }
  return param_1;
}



/* grim_jpg_finish_decompress @ 1001c76e */

uint __cdecl grim_jpg_finish_decompress(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  if (param_1[4] == 0xca) {
    uVar2 = grim_zlib_stream_init((int)param_1);
    if ((char)param_1[0x10] != '\0') {
      param_1[4] = 0xcf;
      return CONCAT31((int3)((uint)uVar2 >> 8),1);
    }
    param_1[4] = 0xcb;
  }
  if (param_1[4] == 0xcb) {
    if (*(char *)(param_1[99] + 0x10) != '\0') {
      while( true ) {
        if ((undefined4 *)param_1[2] != (undefined4 *)0x0) {
          (**(code **)param_1[2])(param_1);
        }
        iVar3 = (**(code **)param_1[99])(param_1);
        if (iVar3 == 0) {
          return 0;
        }
        if (iVar3 == 2) break;
        if ((param_1[2] != 0) && ((iVar3 == 3 || (iVar3 == 1)))) {
          piVar1 = (int *)(param_1[2] + 4);
          *piVar1 = *piVar1 + 1;
          iVar3 = param_1[2];
          if (*(int *)(iVar3 + 8) <= *(int *)(iVar3 + 4)) {
            *(int *)(iVar3 + 8) = param_1[0x46] + *(int *)(iVar3 + 8);
          }
        }
      }
    }
    param_1[0x21] = param_1[0x1f];
  }
  else if (param_1[4] != 0xcc) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  uVar4 = grim_jpg_process_scanlines();
  return uVar4;
}



/* grim_jpg_idct_islow_1d @ 1001c82f */

undefined4 grim_jpg_idct_islow_1d(void)

{
  undefined1 *puVar1;
  int iVar2;
  int *unaff_ESI;
  
  *(undefined4 *)(*unaff_ESI + 0x14) = 0x65;
  (**(code **)(*unaff_ESI + 4))();
  if (*(char *)(unaff_ESI[100] + 0x50) != '\0') {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x3c;
    (**(code **)*unaff_ESI)();
  }
  puVar1 = (undefined1 *)((int)unaff_ESI + 0xda);
  iVar2 = 0x10;
  do {
    puVar1[-0x10] = 0;
    *puVar1 = 1;
    puVar1[0x10] = 5;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = unaff_ESI[100];
  unaff_ESI[0x3f] = 0;
  unaff_ESI[9] = 0;
  *(undefined1 *)(unaff_ESI + 0x42) = 0;
  *(undefined1 *)(unaff_ESI + 0x40) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x101) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x106) = 0;
  *(undefined1 *)((int)unaff_ESI + 0x107) = 0;
  *(undefined2 *)((int)unaff_ESI + 0x102) = 1;
  *(undefined2 *)(unaff_ESI + 0x41) = 1;
  *(undefined1 *)(iVar2 + 0x50) = 1;
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}



/* grim_jpg_idct_islow @ 1001c8bd */

uint __thiscall grim_jpg_idct_islow(undefined1 param_1,undefined1 param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int *unaff_ESI;
  byte *pbVar7;
  byte *pbVar8;
  uint local_c;
  int local_8;
  
  puVar3 = (undefined4 *)unaff_ESI[5];
  local_8 = puVar3[1];
  pbVar7 = (byte *)*puVar3;
  *(undefined1 *)(unaff_ESI + 0x32) = param_1;
  *(undefined1 *)((int)unaff_ESI + 0xc9) = param_2;
  if (local_8 == 0) {
    uVar4 = (*(code *)puVar3[3])();
    if ((char)uVar4 != '\0') {
      local_8 = puVar3[1];
      pbVar7 = (byte *)*puVar3;
      goto LAB_1001c8f7;
    }
LAB_1001cbb1:
    uVar4 = uVar4 & 0xffffff00;
  }
  else {
LAB_1001c8f7:
    local_8 = local_8 + -1;
    bVar1 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar7 = (byte *)*puVar3;
    }
    bVar2 = *pbVar7;
    local_8 = local_8 + -1;
    pbVar7 = pbVar7 + 1;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar7 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar8 = pbVar7 + 1;
    unaff_ESI[0x30] = (uint)*pbVar7;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar7 = pbVar8 + 1;
    unaff_ESI[7] = (uint)*pbVar8 << 8;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar7 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    unaff_ESI[7] = unaff_ESI[7] + (uint)*pbVar7;
    pbVar7 = pbVar7 + 1;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar7 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar8 = pbVar7 + 1;
    unaff_ESI[6] = (uint)*pbVar7 << 8;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    unaff_ESI[6] = unaff_ESI[6] + (uint)*pbVar8;
    pbVar8 = pbVar8 + 1;
    if (local_8 == 0) {
      uVar4 = (*(code *)puVar3[3])();
      if ((char)uVar4 == '\0') goto LAB_1001cbb1;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    unaff_ESI[8] = (uint)*pbVar8;
    iVar5 = *unaff_ESI;
    *(int *)(iVar5 + 0x18) = unaff_ESI[0x5e];
    *(int *)(iVar5 + 0x1c) = unaff_ESI[6];
    *(int *)(iVar5 + 0x20) = unaff_ESI[7];
    *(int *)(iVar5 + 0x24) = unaff_ESI[8];
    *(undefined4 *)(*unaff_ESI + 0x14) = 99;
    pbVar8 = pbVar8 + 1;
    (**(code **)(*unaff_ESI + 4))();
    if (*(char *)(unaff_ESI[100] + 0x51) != '\0') {
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x39;
      (**(code **)*unaff_ESI)();
    }
    if (((unaff_ESI[7] == 0) || (unaff_ESI[6] == 0)) || (unaff_ESI[8] < 1)) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x1f;
      (**(code **)*unaff_ESI)();
    }
    if ((uint)bVar1 * 0x100 + (uint)bVar2 + -8 != unaff_ESI[8] * 3) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 9;
      (**(code **)*unaff_ESI)();
    }
    if (unaff_ESI[0x31] == 0) {
      iVar5 = (**(code **)unaff_ESI[1])();
      unaff_ESI[0x31] = iVar5;
    }
    local_c = 0;
    puVar6 = (uint *)unaff_ESI[0x31];
    if (0 < unaff_ESI[8]) {
      do {
        puVar6[1] = local_c;
        if (local_8 == 0) {
          uVar4 = (*(code *)puVar3[3])();
          if ((char)uVar4 == '\0') goto LAB_1001cbb1;
          local_8 = puVar3[1];
          pbVar8 = (byte *)*puVar3;
        }
        local_8 = local_8 + -1;
        pbVar7 = pbVar8 + 1;
        *puVar6 = (uint)*pbVar8;
        if (local_8 == 0) {
          uVar4 = (*(code *)puVar3[3])();
          if ((char)uVar4 == '\0') goto LAB_1001cbb1;
          local_8 = puVar3[1];
          pbVar7 = (byte *)*puVar3;
        }
        bVar1 = *pbVar7;
        local_8 = local_8 + -1;
        pbVar7 = pbVar7 + 1;
        puVar6[2] = (int)(uint)bVar1 >> 4;
        puVar6[3] = bVar1 & 0xf;
        if (local_8 == 0) {
          uVar4 = (*(code *)puVar3[3])();
          if ((char)uVar4 == '\0') goto LAB_1001cbb1;
          local_8 = puVar3[1];
          pbVar7 = (byte *)*puVar3;
        }
        local_8 = local_8 + -1;
        puVar6[4] = (uint)*pbVar7;
        iVar5 = *unaff_ESI;
        *(uint *)(iVar5 + 0x18) = *puVar6;
        *(uint *)(iVar5 + 0x1c) = puVar6[2];
        *(uint *)(iVar5 + 0x20) = puVar6[3];
        *(uint *)(iVar5 + 0x24) = puVar6[4];
        *(undefined4 *)(*unaff_ESI + 0x14) = 100;
        pbVar8 = pbVar7 + 1;
        (**(code **)(*unaff_ESI + 4))();
        local_c = local_c + 1;
        puVar6 = puVar6 + 0x15;
      } while ((int)local_c < unaff_ESI[8]);
    }
    *(undefined1 *)(unaff_ESI[100] + 0x51) = 1;
    puVar3[1] = local_8;
    *puVar3 = pbVar8;
    uVar4 = CONCAT31((int3)((uint)local_8 >> 8),1);
  }
  return uVar4;
}



/* grim_jpg_idct_ifast @ 1001cbb8 */

uint grim_jpg_idct_ifast(void)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int *unaff_ESI;
  byte *pbVar8;
  byte *pbVar9;
  uint *local_20;
  int local_18;
  int *local_14;
  int local_c;
  int local_8;
  
  puVar3 = (undefined4 *)unaff_ESI[5];
  local_8 = puVar3[1];
  pbVar8 = (byte *)*puVar3;
  if (*(char *)(unaff_ESI[100] + 0x51) == '\0') {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x3d;
    (**(code **)*unaff_ESI)();
  }
  if (local_8 == 0) {
    uVar5 = (*(code *)puVar3[3])();
    if ((char)uVar5 != '\0') {
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
      goto LAB_1001cc01;
    }
LAB_1001cdec:
    uVar5 = uVar5 & 0xffffff00;
  }
  else {
LAB_1001cc01:
    local_8 = local_8 + -1;
    bVar1 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001cdec;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    bVar2 = *pbVar8;
    local_8 = local_8 + -1;
    pbVar8 = pbVar8 + 1;
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001cdec;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    uVar6 = (uint)*pbVar8;
    local_8 = local_8 + -1;
    pbVar8 = pbVar8 + 1;
    if ((((uint)bVar1 * 0x100 + (uint)bVar2 != uVar6 * 2 + 6) || (uVar6 == 0)) || (4 < uVar6)) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 9;
      (**(code **)*unaff_ESI)();
    }
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x66;
    *(uint *)(*unaff_ESI + 0x18) = uVar6;
    (**(code **)(*unaff_ESI + 4))();
    local_18 = 0;
    unaff_ESI[0x48] = uVar6;
    if (uVar6 != 0) {
      local_14 = unaff_ESI + 0x49;
      do {
        if (local_8 == 0) {
          uVar5 = (*(code *)puVar3[3])();
          if ((char)uVar5 == '\0') goto LAB_1001cdec;
          local_8 = puVar3[1];
          pbVar8 = (byte *)*puVar3;
        }
        uVar7 = (uint)*pbVar8;
        local_8 = local_8 + -1;
        pbVar8 = pbVar8 + 1;
        if (local_8 == 0) {
          uVar5 = (*(code *)puVar3[3])();
          if ((char)uVar5 == '\0') goto LAB_1001cdec;
          local_8 = puVar3[1];
          pbVar8 = (byte *)*puVar3;
        }
        bVar1 = *pbVar8;
        local_8 = local_8 + -1;
        local_c = 0;
        local_20 = (uint *)unaff_ESI[0x31];
        pbVar8 = pbVar8 + 1;
        if (0 < unaff_ESI[8]) {
          do {
            if (uVar7 == *local_20) goto LAB_1001cd43;
            local_c = local_c + 1;
            local_20 = local_20 + 0x15;
          } while (local_c < unaff_ESI[8]);
        }
        *(undefined4 *)(*unaff_ESI + 0x14) = 5;
        *(uint *)(*unaff_ESI + 0x18) = uVar7;
        (**(code **)*unaff_ESI)();
LAB_1001cd43:
        *local_14 = (int)local_20;
        local_20[6] = bVar1 & 0xf;
        local_20[5] = (int)(uint)bVar1 >> 4;
        iVar4 = *unaff_ESI;
        *(uint *)(iVar4 + 0x18) = uVar7;
        *(uint *)(iVar4 + 0x1c) = local_20[5];
        *(uint *)(iVar4 + 0x20) = local_20[6];
        *(undefined4 *)(*unaff_ESI + 0x14) = 0x67;
        (**(code **)(*unaff_ESI + 4))();
        local_18 = local_18 + 1;
        local_14 = local_14 + 1;
      } while (local_18 < (int)uVar6);
    }
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001cdec;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar9 = pbVar8 + 1;
    unaff_ESI[0x5a] = (uint)*pbVar8;
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001cdec;
      local_8 = puVar3[1];
      pbVar9 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar8 = pbVar9 + 1;
    unaff_ESI[0x5b] = (uint)*pbVar9;
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001cdec;
      local_8 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    bVar1 = *pbVar8;
    unaff_ESI[0x5d] = bVar1 & 0xf;
    iVar4 = *unaff_ESI;
    unaff_ESI[0x5c] = (int)(uint)bVar1 >> 4;
    *(int *)(iVar4 + 0x18) = unaff_ESI[0x5a];
    *(int *)(iVar4 + 0x1c) = unaff_ESI[0x5b];
    *(int *)(iVar4 + 0x20) = unaff_ESI[0x5c];
    *(int *)(iVar4 + 0x24) = unaff_ESI[0x5d];
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x68;
    (**(code **)(*unaff_ESI + 4))();
    *(undefined4 *)(unaff_ESI[100] + 0x54) = 0;
    unaff_ESI[0x1f] = unaff_ESI[0x1f] + 1;
    puVar3[1] = local_8 + -1;
    *puVar3 = pbVar8 + 1;
    uVar5 = CONCAT31((int3)((uint)(local_8 + -1) >> 8),1);
  }
  return uVar5;
}



/* grim_jpg_idct_float @ 1001ce6a */

undefined4 __cdecl grim_jpg_idct_float(int *param_1)

{
  byte *pbVar1;
  int iVar2;
  byte bVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  ushort uVar9;
  byte *pbVar10;
  byte local_1c [4];
  char local_18;
  byte local_17;
  byte local_16;
  undefined1 local_15;
  byte local_14;
  byte local_13;
  byte local_12;
  byte local_11;
  byte local_10;
  byte local_f;
  int local_c;
  int local_8;
  
  piVar5 = param_1;
  puVar4 = (undefined4 *)param_1[5];
  pbVar10 = (byte *)*puVar4;
  piVar6 = (int *)puVar4[1];
  if ((int *)puVar4[1] == (int *)0x0) {
    uVar7 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar7 == '\0') goto LAB_1001cf6a;
    pbVar10 = (byte *)*puVar4;
    piVar6 = (int *)puVar4[1];
  }
  param_1 = piVar6;
  param_1 = (int *)((int)param_1 + -1);
  local_8 = (uint)*pbVar10 << 8;
  pbVar10 = pbVar10 + 1;
  if (param_1 == (int *)0x0) {
    uVar7 = (*(code *)puVar4[3])(piVar5);
    if ((char)uVar7 == '\0') {
LAB_1001cf6a:
      return uVar7 & 0xffffff00;
    }
    param_1 = (int *)puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  param_1 = (int *)((int)param_1 + -1);
  local_8 = local_8 + (uint)*pbVar10 + -2;
  pbVar10 = pbVar10 + 1;
  if (local_8 < 0xe) {
    *(undefined4 *)(*piVar5 + 0x14) = 0x4c;
    *(int *)(*piVar5 + 0x18) = local_8;
  }
  else {
    local_c = 0;
    do {
      if (param_1 == (int *)0x0) {
        uVar7 = (*(code *)puVar4[3])(piVar5);
        if ((char)uVar7 == '\0') goto LAB_1001cf6a;
        param_1 = (int *)puVar4[1];
        pbVar10 = (byte *)*puVar4;
      }
      param_1 = (int *)((int)param_1 + -1);
      bVar3 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      iVar2 = local_c + 1;
      pbVar1 = local_1c + local_c;
      local_c = iVar2;
      *pbVar1 = bVar3;
    } while (iVar2 < 0xe);
    iVar2 = local_8 + -0xe;
    if ((((local_1c[0] == 0x4a) && (local_1c[1] == 'F')) && (local_1c[2] == 'I')) &&
       ((local_1c[3] == 'F' && (local_18 == '\0')))) {
      if (local_17 == 1) {
        local_8 = iVar2;
        if (2 < local_16) {
          *(undefined4 *)(*piVar5 + 0x14) = 0x58;
          *(undefined4 *)(*piVar5 + 0x18) = 1;
          *(uint *)(*piVar5 + 0x1c) = (uint)local_16;
          (**(code **)(*piVar5 + 4))(piVar5,1);
        }
      }
      else {
        *(undefined4 *)(*piVar5 + 0x14) = 0x73;
        *(uint *)(*piVar5 + 0x18) = (uint)local_17;
        *(uint *)(*piVar5 + 0x1c) = (uint)local_16;
        local_8 = iVar2;
        (**(code **)(*piVar5 + 4))(piVar5,0xffffffff);
      }
      *(undefined1 *)((int)piVar5 + 0x101) = local_15;
      *(undefined1 *)(piVar5 + 0x40) = 1;
      uVar9 = (ushort)local_13 + (ushort)local_14 * 0x100;
      *(ushort *)((int)piVar5 + 0x102) = uVar9;
      *(ushort *)(piVar5 + 0x41) = (ushort)local_12 * 0x100 + (ushort)local_11;
      iVar2 = *piVar5;
      *(uint *)(iVar2 + 0x18) = (uint)uVar9;
      *(uint *)(iVar2 + 0x1c) = (uint)*(ushort *)(piVar5 + 0x41);
      *(uint *)(iVar2 + 0x20) = (uint)*(byte *)((int)piVar5 + 0x101);
      *(undefined4 *)(*piVar5 + 0x14) = 0x56;
      (**(code **)(*piVar5 + 4))(piVar5,1);
      if (local_f != 0 || local_10 != 0) {
        *(undefined4 *)(*piVar5 + 0x14) = 0x59;
        *(uint *)(*piVar5 + 0x18) = (uint)local_10;
        *(uint *)(*piVar5 + 0x1c) = (uint)local_f;
        (**(code **)(*piVar5 + 4))(piVar5,1);
      }
      if (local_8 == (uint)local_f * (uint)local_10 * 3) goto LAB_1001d085;
      *(undefined4 *)(*piVar5 + 0x14) = 0x57;
      iVar8 = local_8;
    }
    else {
      *(undefined4 *)(*piVar5 + 0x14) = 0x4c;
      iVar8 = local_8;
      local_8 = iVar2;
    }
    *(int *)(*piVar5 + 0x18) = iVar8;
  }
  (**(code **)(*piVar5 + 4))(piVar5,1);
LAB_1001d085:
  *puVar4 = pbVar10;
  puVar4[1] = param_1;
  if (0 < local_8) {
    param_1 = (int *)(**(code **)(piVar5[5] + 0x10))(piVar5,local_8);
  }
  return CONCAT31((int3)((uint)param_1 >> 8),1);
}



/* grim_jpg_upsample_h2v1 @ 1001d0a6 */

undefined4 __cdecl grim_jpg_upsample_h2v1(int *param_1)

{
  byte *pbVar1;
  int iVar2;
  byte bVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  byte *pbVar8;
  byte local_18 [4];
  char local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  byte local_d;
  int local_c;
  int local_8;
  
  piVar5 = param_1;
  puVar4 = (undefined4 *)param_1[5];
  pbVar8 = (byte *)*puVar4;
  piVar6 = (int *)puVar4[1];
  if ((int *)puVar4[1] == (int *)0x0) {
    uVar7 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar7 == '\0') goto LAB_1001d1ca;
    pbVar8 = (byte *)*puVar4;
    piVar6 = (int *)puVar4[1];
  }
  param_1 = piVar6;
  param_1 = (int *)((int)param_1 + -1);
  local_8 = (uint)*pbVar8 << 8;
  pbVar8 = pbVar8 + 1;
  if (param_1 == (int *)0x0) {
    uVar7 = (*(code *)puVar4[3])(piVar5);
    if ((char)uVar7 == '\0') {
LAB_1001d1ca:
      return uVar7 & 0xffffff00;
    }
    param_1 = (int *)puVar4[1];
    pbVar8 = (byte *)*puVar4;
  }
  param_1 = (int *)((int)param_1 + -1);
  local_8 = local_8 + (uint)*pbVar8 + -2;
  pbVar8 = pbVar8 + 1;
  if (local_8 < 0xc) {
    *(undefined4 *)(*piVar5 + 0x14) = 0x4d;
    *(int *)(*piVar5 + 0x18) = local_8;
  }
  else {
    local_c = 0;
    do {
      if (param_1 == (int *)0x0) {
        uVar7 = (*(code *)puVar4[3])(piVar5);
        if ((char)uVar7 == '\0') goto LAB_1001d1ca;
        param_1 = (int *)puVar4[1];
        pbVar8 = (byte *)*puVar4;
      }
      param_1 = (int *)((int)param_1 + -1);
      bVar3 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      iVar2 = local_c + 1;
      pbVar1 = local_18 + local_c;
      local_c = iVar2;
      *pbVar1 = bVar3;
    } while (iVar2 < 0xc);
    if ((((local_18[0] == 0x41) && (local_18[1] == 'd')) && (local_18[2] == 'o')) &&
       ((local_18[3] == 'b' && (local_14 == 'e')))) {
      iVar2 = *piVar5;
      *(uint *)(iVar2 + 0x18) = (uint)CONCAT11(local_13,local_12);
      *(uint *)(iVar2 + 0x1c) = (uint)CONCAT11(local_11,local_10);
      *(uint *)(iVar2 + 0x20) = (uint)CONCAT11(local_f,local_e);
      *(uint *)(iVar2 + 0x24) = (uint)local_d;
      *(undefined4 *)(*piVar5 + 0x14) = 0x4b;
      local_8 = local_8 + -0xc;
      (**(code **)(*piVar5 + 4))(piVar5,1);
      *(undefined1 *)((int)piVar5 + 0x106) = 1;
      *(byte *)((int)piVar5 + 0x107) = local_d;
      goto LAB_1001d1fd;
    }
    *(undefined4 *)(*piVar5 + 0x14) = 0x4d;
    *(int *)(*piVar5 + 0x18) = local_8;
    local_8 = local_8 + -0xc;
  }
  (**(code **)(*piVar5 + 4))(piVar5,1);
LAB_1001d1fd:
  *puVar4 = pbVar8;
  puVar4[1] = param_1;
  if (0 < local_8) {
    param_1 = (int *)(**(code **)(piVar5[5] + 0x10))(piVar5,local_8);
  }
  return CONCAT31((int3)((uint)param_1 >> 8),1);
}



/* grim_jpg_upsample_h2v2 @ 1001d220 */

uint grim_jpg_upsample_h2v2(void)

{
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  int *unaff_ESI;
  byte *pbVar6;
  byte *pbVar7;
  int local_c;
  int local_8;
  
  puVar2 = (undefined4 *)unaff_ESI[5];
  local_8 = puVar2[1];
  pbVar6 = (byte *)*puVar2;
  if (local_8 == 0) {
    uVar3 = (*(code *)puVar2[3])();
    if ((char)uVar3 != '\0') {
      local_8 = puVar2[1];
      pbVar6 = (byte *)*puVar2;
      goto LAB_1001d24c;
    }
LAB_1001d373:
    uVar3 = uVar3 & 0xffffff00;
  }
  else {
LAB_1001d24c:
    local_8 = local_8 + -1;
    bVar1 = *pbVar6;
    pbVar6 = pbVar6 + 1;
    if (local_8 == 0) {
      uVar3 = (*(code *)puVar2[3])();
      if ((char)uVar3 == '\0') goto LAB_1001d373;
      local_8 = puVar2[1];
      pbVar6 = (byte *)*puVar2;
    }
    local_8 = local_8 + -1;
    pbVar7 = pbVar6 + 1;
    local_c = (uint)bVar1 * 0x100 + (uint)*pbVar6 + -2;
    while (0 < local_c) {
      if (local_8 == 0) {
        uVar3 = (*(code *)puVar2[3])();
        if ((char)uVar3 == '\0') goto LAB_1001d373;
        local_8 = puVar2[1];
        pbVar7 = (byte *)*puVar2;
      }
      uVar4 = (uint)*pbVar7;
      local_8 = local_8 + -1;
      pbVar7 = pbVar7 + 1;
      if (local_8 == 0) {
        uVar3 = (*(code *)puVar2[3])();
        if ((char)uVar3 == '\0') goto LAB_1001d373;
        local_8 = puVar2[1];
        pbVar7 = (byte *)*puVar2;
      }
      bVar1 = *pbVar7;
      uVar3 = (uint)bVar1;
      local_8 = local_8 + -1;
      local_c = local_c + -2;
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x4e;
      *(uint *)(*unaff_ESI + 0x18) = uVar4;
      *(uint *)(*unaff_ESI + 0x1c) = uVar3;
      pbVar7 = pbVar7 + 1;
      (**(code **)(*unaff_ESI + 4))();
      if (0x1f < uVar4) {
        *(undefined4 *)(*unaff_ESI + 0x14) = 0x1a;
        *(uint *)(*unaff_ESI + 0x18) = uVar4;
        (**(code **)*unaff_ESI)();
      }
      if (uVar4 < 0x10) {
        bVar5 = (byte)((int)uVar3 >> 4);
        *(byte *)(uVar4 + 0xca + (int)unaff_ESI) = bVar1 & 0xf;
        *(byte *)(uVar4 + 0xda + (int)unaff_ESI) = bVar5;
        if (bVar5 < (bVar1 & 0xf)) {
          *(undefined4 *)(*unaff_ESI + 0x14) = 0x1b;
          *(uint *)(*unaff_ESI + 0x18) = uVar3;
          (**(code **)*unaff_ESI)();
        }
      }
      else {
        *(byte *)(uVar4 + 0xda + (int)unaff_ESI) = bVar1;
      }
    }
    puVar2[1] = local_8;
    *puVar2 = pbVar7;
    uVar3 = CONCAT31((int3)((uint)local_8 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_inverse_dct_scaled @ 1001d377 */

uint grim_jpg_inverse_dct_scaled(void)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  int *unaff_EBX;
  byte *pbVar4;
  int *piVar5;
  byte *pbVar6;
  int iVar7;
  undefined4 *puVar8;
  byte local_134 [256];
  uint local_34;
  int *local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  byte local_1c;
  int local_18;
  int *local_14;
  int local_10;
  byte *local_c;
  int local_8;
  
  piVar5 = (int *)unaff_EBX[5];
  local_8 = piVar5[1];
  pbVar6 = (byte *)*piVar5;
  local_30 = piVar5;
  if (local_8 == 0) {
    uVar3 = (*(code *)piVar5[3])();
    if ((char)uVar3 != '\0') {
      pbVar6 = (byte *)*piVar5;
      local_8 = piVar5[1];
      local_c = pbVar6;
      goto LAB_1001d3af;
    }
LAB_1001d607:
    uVar3 = uVar3 & 0xffffff00;
  }
  else {
LAB_1001d3af:
    local_8 = local_8 + -1;
    local_10 = (uint)*pbVar6 << 8;
    pbVar6 = pbVar6 + 1;
    if (local_8 == 0) {
      uVar3 = (*(code *)piVar5[3])();
      if ((char)uVar3 == '\0') goto LAB_1001d607;
      pbVar6 = (byte *)*piVar5;
      local_8 = piVar5[1];
      local_c = pbVar6;
    }
    local_8 = local_8 + -1;
    local_10 = local_10 + (uint)*pbVar6 + -2;
    pbVar6 = pbVar6 + 1;
    while (0 < local_10) {
      if (local_8 == 0) {
        uVar3 = (*(code *)piVar5[3])();
        if ((char)uVar3 == '\0') goto LAB_1001d607;
        pbVar6 = (byte *)*piVar5;
        local_8 = piVar5[1];
        local_c = pbVar6;
      }
      local_34 = (uint)*pbVar6;
      local_8 = local_8 + -1;
      *(undefined4 *)(*unaff_EBX + 0x14) = 0x4f;
      *(uint *)(*unaff_EBX + 0x18) = local_34;
      pbVar6 = pbVar6 + 1;
      (**(code **)(*unaff_EBX + 4))();
      local_2c = local_2c & 0xffffff00;
      local_18 = 0;
      local_14 = (int *)0x1;
      do {
        if (local_8 == 0) {
          uVar3 = (*(code *)piVar5[3])();
          if ((char)uVar3 == '\0') goto LAB_1001d607;
          pbVar6 = (byte *)*piVar5;
          local_8 = piVar5[1];
        }
        bVar1 = *pbVar6;
        local_8 = local_8 + -1;
        *(byte *)((int)&local_2c + (int)local_14) = bVar1;
        local_18 = local_18 + (uint)bVar1;
        pbVar6 = pbVar6 + 1;
        local_14 = (int *)((int)local_14 + 1);
        local_c = pbVar6;
      } while ((int)local_14 < 0x11);
      iVar7 = *unaff_EBX;
      *(uint *)(iVar7 + 0x18) = local_2c >> 8 & 0xff;
      *(uint *)(iVar7 + 0x1c) = local_2c >> 0x10 & 0xff;
      *(uint *)(iVar7 + 0x20) = local_2c >> 0x18;
      local_10 = local_10 + -0x11;
      *(uint *)(iVar7 + 0x24) = local_28 & 0xff;
      *(uint *)(iVar7 + 0x28) = local_28 >> 8 & 0xff;
      *(uint *)(iVar7 + 0x2c) = local_28 >> 0x10 & 0xff;
      *(uint *)(iVar7 + 0x30) = local_28 >> 0x18;
      *(uint *)(iVar7 + 0x34) = local_24 & 0xff;
      *(undefined4 *)(*unaff_EBX + 0x14) = 0x55;
      (**(code **)(*unaff_EBX + 4))();
      iVar7 = *unaff_EBX;
      *(uint *)(iVar7 + 0x18) = local_24 >> 8 & 0xff;
      *(uint *)(iVar7 + 0x1c) = local_24 >> 0x10 & 0xff;
      *(uint *)(iVar7 + 0x20) = local_24 >> 0x18;
      *(uint *)(iVar7 + 0x24) = local_20 & 0xff;
      *(uint *)(iVar7 + 0x28) = local_20 >> 8 & 0xff;
      *(uint *)(iVar7 + 0x2c) = local_20 >> 0x10 & 0xff;
      *(uint *)(iVar7 + 0x30) = local_20 >> 0x18;
      *(uint *)(iVar7 + 0x34) = (uint)local_1c;
      *(undefined4 *)(*unaff_EBX + 0x14) = 0x55;
      (**(code **)(*unaff_EBX + 4))();
      if ((0x100 < local_18) || (local_10 < local_18)) {
        *(undefined4 *)(*unaff_EBX + 0x14) = 0x1c;
        (**(code **)*unaff_EBX)();
      }
      iVar7 = 0;
      if (0 < local_18) {
        do {
          if (local_8 == 0) {
            uVar3 = (*(code *)piVar5[3])();
            if ((char)uVar3 == '\0') goto LAB_1001d607;
            local_c = (byte *)*piVar5;
            local_8 = piVar5[1];
          }
          local_8 = local_8 + -1;
          bVar1 = *local_c;
          local_c = local_c + 1;
          local_134[iVar7] = bVar1;
          iVar7 = iVar7 + 1;
        } while (iVar7 < local_18);
      }
      local_10 = local_10 - local_18;
      if ((local_34 & 0x10) == 0) {
        piVar5 = unaff_EBX + local_34 + 0x28;
        local_14 = piVar5;
        uVar3 = local_34;
      }
      else {
        piVar5 = unaff_EBX + local_34 + 0x1c;
        local_14 = piVar5;
        uVar3 = local_34 - 0x10;
      }
      local_14 = piVar5;
      if (((int)uVar3 < 0) || (3 < (int)uVar3)) {
        *(undefined4 *)(*unaff_EBX + 0x14) = 0x1d;
        *(uint *)(*unaff_EBX + 0x18) = uVar3;
        (**(code **)*unaff_EBX)();
      }
      if (*piVar5 == 0) {
        iVar7 = grim_jpg_zigzag_index_lookup((int)unaff_EBX);
        *piVar5 = iVar7;
      }
      puVar2 = (uint *)*piVar5;
      *puVar2 = local_2c;
      puVar2[1] = local_28;
      puVar2[2] = local_24;
      puVar2[3] = local_20;
      *(byte *)(puVar2 + 4) = local_1c;
      pbVar4 = local_134;
      puVar8 = (undefined4 *)(*local_14 + 0x11);
      for (iVar7 = 0x40; piVar5 = local_30, pbVar6 = local_c, iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = *(undefined4 *)pbVar4;
        pbVar4 = pbVar4 + 4;
        puVar8 = puVar8 + 1;
      }
    }
    piVar5[1] = local_8;
    *piVar5 = (int)pbVar6;
    uVar3 = CONCAT31((int3)((uint)local_8 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_dequant_merge_idct @ 1001d60b */

uint grim_jpg_dequant_merge_idct(void)

{
  int *piVar1;
  byte bVar2;
  undefined4 *puVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  int *unaff_EBX;
  byte *pbVar9;
  byte *pbVar10;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  puVar3 = (undefined4 *)unaff_EBX[5];
  local_8 = puVar3[1];
  pbVar9 = (byte *)*puVar3;
  if (local_8 == 0) {
    uVar5 = (*(code *)puVar3[3])();
    if ((char)uVar5 != '\0') {
      local_8 = puVar3[1];
      pbVar9 = (byte *)*puVar3;
      goto LAB_1001d637;
    }
LAB_1001d830:
    uVar5 = uVar5 & 0xffffff00;
  }
  else {
LAB_1001d637:
    local_8 = local_8 + -1;
    bVar2 = *pbVar9;
    pbVar9 = pbVar9 + 1;
    if (local_8 == 0) {
      uVar5 = (*(code *)puVar3[3])();
      if ((char)uVar5 == '\0') goto LAB_1001d830;
      local_8 = puVar3[1];
      pbVar9 = (byte *)*puVar3;
    }
    local_8 = local_8 + -1;
    pbVar10 = pbVar9 + 1;
    iVar7 = (uint)bVar2 * 0x100 + (uint)*pbVar9 + -2;
    while (local_c = iVar7, 0 < local_c) {
      if (local_8 == 0) {
        uVar5 = (*(code *)puVar3[3])();
        if ((char)uVar5 == '\0') goto LAB_1001d830;
        local_8 = puVar3[1];
        pbVar10 = (byte *)*puVar3;
      }
      bVar2 = *pbVar10;
      local_8 = local_8 + -1;
      *(undefined4 *)(*unaff_EBX + 0x14) = 0x50;
      uVar5 = bVar2 & 0xf;
      *(uint *)(*unaff_EBX + 0x18) = uVar5;
      iVar6 = (int)(uint)bVar2 >> 4;
      *(int *)(*unaff_EBX + 0x1c) = iVar6;
      pbVar10 = pbVar10 + 1;
      (**(code **)(*unaff_EBX + 4))();
      if (3 < uVar5) {
        *(undefined4 *)(*unaff_EBX + 0x14) = 0x1e;
        *(uint *)(*unaff_EBX + 0x18) = uVar5;
        (**(code **)*unaff_EBX)();
      }
      piVar1 = unaff_EBX + uVar5 + 0x24;
      if (*piVar1 == 0) {
        iVar7 = grim_jpg_natural_order_lookup((int)unaff_EBX);
        *piVar1 = iVar7;
      }
      iVar7 = *piVar1;
      local_14 = &grim_jpg_zigzag_order;
      do {
        if (iVar6 == 0) {
          if (local_8 == 0) {
            uVar5 = (*(code *)puVar3[3])();
            if ((char)uVar5 == '\0') goto LAB_1001d830;
            local_8 = puVar3[1];
            pbVar10 = (byte *)*puVar3;
          }
          uVar4 = (ushort)*pbVar10;
        }
        else {
          if (local_8 == 0) {
            uVar5 = (*(code *)puVar3[3])();
            if ((char)uVar5 == '\0') goto LAB_1001d830;
            local_8 = puVar3[1];
            pbVar10 = (byte *)*puVar3;
          }
          local_8 = local_8 + -1;
          bVar2 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          if (local_8 == 0) {
            uVar5 = (*(code *)puVar3[3])();
            if ((char)uVar5 == '\0') goto LAB_1001d830;
            local_8 = puVar3[1];
            pbVar10 = (byte *)*puVar3;
          }
          uVar4 = (ushort)bVar2 * 0x100 + (ushort)*pbVar10;
        }
        local_8 = local_8 + -1;
        piVar1 = local_14 + 1;
        pbVar10 = pbVar10 + 1;
        *(ushort *)(iVar7 + *local_14 * 2) = uVar4;
        local_14 = piVar1;
      } while ((int)piVar1 < 0x1004e9c0);
      if (1 < *(int *)(*unaff_EBX + 0x68)) {
        puVar8 = (ushort *)(iVar7 + 4);
        local_10 = 8;
        do {
          iVar7 = *unaff_EBX;
          *(uint *)(iVar7 + 0x18) = (uint)puVar8[-2];
          *(uint *)(iVar7 + 0x1c) = (uint)puVar8[-1];
          *(uint *)(iVar7 + 0x20) = (uint)*puVar8;
          *(uint *)(iVar7 + 0x24) = (uint)puVar8[1];
          *(uint *)(iVar7 + 0x28) = (uint)puVar8[2];
          *(uint *)(iVar7 + 0x2c) = (uint)puVar8[3];
          *(uint *)(iVar7 + 0x30) = (uint)puVar8[4];
          *(uint *)(iVar7 + 0x34) = (uint)puVar8[5];
          *(undefined4 *)(*unaff_EBX + 0x14) = 0x5c;
          (**(code **)(*unaff_EBX + 4))();
          puVar8 = puVar8 + 8;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      iVar7 = local_c + -0x41;
      if (iVar6 != 0) {
        iVar7 = local_c + -0x81;
      }
    }
    puVar3[1] = local_8;
    *puVar3 = pbVar10;
    uVar5 = CONCAT31((int3)((uint)local_8 >> 8),1);
  }
  return uVar5;
}



/* grim_jpg_color_convert_ycbcr_rgb @ 1001d834 */

uint __cdecl grim_jpg_color_convert_ycbcr_rgb(int *param_1)

{
  int iVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  puVar3 = (undefined4 *)param_1[5];
  iVar5 = puVar3[1];
  pbVar6 = (byte *)*puVar3;
  if (iVar5 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 != '\0') {
      pbVar6 = (byte *)*puVar3;
      iVar5 = puVar3[1];
      goto LAB_1001d85b;
    }
LAB_1001d8c4:
    uVar4 = uVar4 & 0xffffff00;
  }
  else {
LAB_1001d85b:
    bVar2 = *pbVar6;
    iVar5 = iVar5 + -1;
    pbVar6 = pbVar6 + 1;
    if (iVar5 == 0) {
      uVar4 = (*(code *)puVar3[3])(param_1);
      if ((char)uVar4 == '\0') goto LAB_1001d8c4;
      pbVar6 = (byte *)*puVar3;
      iVar5 = puVar3[1];
    }
    iVar5 = iVar5 + -1;
    pbVar7 = pbVar6 + 1;
    if ((uint)bVar2 * 0x100 + (uint)*pbVar6 != 4) {
      *(undefined4 *)(*param_1 + 0x14) = 9;
      (**(code **)*param_1)(param_1);
    }
    if (iVar5 == 0) {
      uVar4 = (*(code *)puVar3[3])(param_1);
      if ((char)uVar4 == '\0') goto LAB_1001d8c4;
      pbVar7 = (byte *)*puVar3;
      iVar5 = puVar3[1];
    }
    bVar2 = *pbVar7;
    iVar5 = iVar5 + -1;
    pbVar7 = pbVar7 + 1;
    if (iVar5 == 0) {
      uVar4 = (*(code *)puVar3[3])(param_1);
      if ((char)uVar4 == '\0') goto LAB_1001d8c4;
      pbVar7 = (byte *)*puVar3;
      iVar5 = puVar3[1];
    }
    iVar1 = (uint)bVar2 * 0x100 + (uint)*pbVar7;
    *(undefined4 *)(*param_1 + 0x14) = 0x51;
    *(int *)(*param_1 + 0x18) = iVar1;
    (**(code **)(*param_1 + 4))(param_1,1);
    param_1[0x3f] = iVar1;
    *puVar3 = pbVar7 + 1;
    puVar3[1] = iVar5 + -1;
    uVar4 = CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  return uVar4;
}



/* grim_jpg_color_convert_ycbcr_bgr @ 1001d90b */

uint __cdecl grim_jpg_color_convert_ycbcr_bgr(int *param_1)

{
  int iVar1;
  byte bVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  undefined4 uVar7;
  byte *pbVar8;
  
  piVar4 = param_1;
  puVar3 = (undefined4 *)param_1[5];
  pbVar8 = (byte *)*puVar3;
  piVar5 = (int *)puVar3[1];
  if ((int *)puVar3[1] == (int *)0x0) {
    uVar6 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar6 != '\0') {
      pbVar8 = (byte *)*puVar3;
      piVar5 = (int *)puVar3[1];
      goto LAB_1001d935;
    }
LAB_1001d94f:
    uVar6 = uVar6 & 0xffffff00;
  }
  else {
LAB_1001d935:
    param_1 = piVar5;
    param_1 = (int *)((int)param_1 + -1);
    bVar2 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    if (param_1 == (int *)0x0) {
      uVar6 = (*(code *)puVar3[3])(piVar4);
      if ((char)uVar6 == '\0') goto LAB_1001d94f;
      param_1 = (int *)puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    iVar1 = (uint)bVar2 * 0x100 + (uint)*pbVar8;
    *(undefined4 *)(*piVar4 + 0x14) = 0x5a;
    *(int *)(*piVar4 + 0x18) = piVar4[0x5e];
    *(int *)(*piVar4 + 0x1c) = iVar1;
    (**(code **)(*piVar4 + 4))(piVar4,1);
    *puVar3 = pbVar8 + 1;
    puVar3[1] = (int)param_1 + -1;
    uVar7 = (**(code **)(piVar4[5] + 0x10))(piVar4,iVar1 + -2);
    uVar6 = CONCAT31((int3)((uint)uVar7 >> 8),1);
  }
  return uVar6;
}



/* grim_jpg_color_convert_grayscale @ 1001d9a7 */

undefined4 __cdecl grim_jpg_color_convert_grayscale(int *param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  puVar2 = (undefined4 *)param_1[5];
  iVar4 = puVar2[1];
  pbVar5 = (byte *)*puVar2;
  do {
    if (iVar4 == 0) {
      uVar3 = (*(code *)puVar2[3])(param_1);
      if ((char)uVar3 == '\0') {
LAB_1001da20:
        return uVar3 & 0xffffff00;
      }
      pbVar5 = (byte *)*puVar2;
      iVar4 = puVar2[1];
    }
    bVar1 = *pbVar5;
    iVar4 = iVar4 + -1;
    pbVar5 = pbVar5 + 1;
    if (bVar1 == 0xff) {
      do {
        if (iVar4 == 0) {
          uVar3 = (*(code *)puVar2[3])(param_1);
          if ((char)uVar3 == '\0') goto LAB_1001da20;
          pbVar5 = (byte *)*puVar2;
          iVar4 = puVar2[1];
        }
        uVar3 = (uint)*pbVar5;
        iVar4 = iVar4 + -1;
        pbVar5 = pbVar5 + 1;
      } while (uVar3 == 0xff);
      if (uVar3 != 0) {
        if (*(int *)(param_1[100] + 0x58) != 0) {
          *(undefined4 *)(*param_1 + 0x14) = 0x70;
          *(undefined4 *)(*param_1 + 0x18) = *(undefined4 *)(param_1[100] + 0x58);
          *(uint *)(*param_1 + 0x1c) = uVar3;
          (**(code **)(*param_1 + 4))(param_1,0xffffffff);
          *(undefined4 *)(param_1[100] + 0x58) = 0;
        }
        param_1[0x5e] = uVar3;
        *puVar2 = pbVar5;
        puVar2[1] = iVar4;
        return CONCAT31((int3)((uint)param_1 >> 8),1);
      }
      *(int *)(param_1[100] + 0x58) = *(int *)(param_1[100] + 0x58) + 2;
    }
    else {
      *(int *)(param_1[100] + 0x58) = *(int *)(param_1[100] + 0x58) + 1;
    }
    *puVar2 = pbVar5;
    puVar2[1] = iVar4;
  } while( true );
}



/* grim_jpg_color_convert_ycck @ 1001da7e */

uint __cdecl grim_jpg_color_convert_ycck(int *param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  puVar2 = (undefined4 *)param_1[5];
  iVar4 = puVar2[1];
  pbVar5 = (byte *)*puVar2;
  if (iVar4 == 0) {
    uVar3 = (*(code *)puVar2[3])(param_1);
    if ((char)uVar3 != '\0') {
      pbVar5 = (byte *)*puVar2;
      iVar4 = puVar2[1];
      goto LAB_1001daa5;
    }
LAB_1001daba:
    uVar3 = uVar3 & 0xffffff00;
  }
  else {
LAB_1001daa5:
    bVar1 = *pbVar5;
    iVar4 = iVar4 + -1;
    pbVar5 = pbVar5 + 1;
    if (iVar4 == 0) {
      uVar3 = (*(code *)puVar2[3])(param_1);
      if ((char)uVar3 == '\0') goto LAB_1001daba;
      pbVar5 = (byte *)*puVar2;
      iVar4 = puVar2[1];
    }
    uVar3 = (uint)*pbVar5;
    if ((bVar1 != 0xff) || (uVar3 != 0xd8)) {
      *(undefined4 *)(*param_1 + 0x14) = 0x34;
      *(uint *)(*param_1 + 0x18) = (uint)bVar1;
      *(uint *)(*param_1 + 0x1c) = uVar3;
      (**(code **)*param_1)(param_1);
    }
    param_1[0x5e] = uVar3;
    *puVar2 = pbVar5 + 1;
    puVar2[1] = iVar4 + -1;
    uVar3 = CONCAT31((int3)((uint)param_1 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_color_convert_init_tables @ 1001dd02 */

uint __cdecl grim_jpg_color_convert_init_tables(int *param_1)

{
  uint uVar1;
  
  if (param_1[0x5e] == 0) {
    uVar1 = grim_jpg_color_convert_grayscale(param_1);
    if ((char)uVar1 == '\0') goto LAB_1001dd7c;
  }
  if (param_1[0x5e] == *(int *)(param_1[100] + 0x54) + 0xd0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x61;
    *(undefined4 *)(*param_1 + 0x18) = *(undefined4 *)(param_1[100] + 0x54);
    (**(code **)(*param_1 + 4))(param_1,3);
    param_1[0x5e] = 0;
  }
  else {
    uVar1 = (**(code **)(param_1[5] + 0x14))(param_1,*(int *)(param_1[100] + 0x54));
    if ((char)uVar1 == '\0') {
LAB_1001dd7c:
      return uVar1 & 0xffffff00;
    }
  }
  *(uint *)(param_1[100] + 0x54) = *(int *)(param_1[100] + 0x54) + 1U & 7;
  return 1;
}



/* grim_jpg_decompress_setup @ 1001de6f */

void __cdecl grim_jpg_decompress_setup(int param_1)

{
  int *piVar1;
  
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x178) = 0;
  piVar1 = (int *)(param_1 + 400);
  *(undefined1 *)(*piVar1 + 0x50) = 0;
  *(undefined1 *)(*piVar1 + 0x51) = 0;
  *(undefined4 *)(*piVar1 + 0x58) = 0;
  return;
}



/* grim_jpg_marker_init @ 1001de99 */

void __cdecl grim_jpg_marker_init(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x5c);
  *(undefined4 **)(param_1 + 400) = puVar1;
  *puVar1 = grim_jpg_decompress_setup;
  *(undefined1 **)(*(int *)(param_1 + 400) + 4) = &LAB_1001db15;
  *(code **)(*(int *)(param_1 + 400) + 8) = grim_jpg_color_convert_init_tables;
  *(code **)(*(int *)(param_1 + 400) + 0xc) = grim_jpg_color_convert_ycbcr_bgr;
  iVar2 = 0x10;
  do {
    *(code **)(iVar2 + *(int *)(param_1 + 400)) = grim_jpg_color_convert_ycbcr_bgr;
    iVar2 = iVar2 + 4;
  } while (iVar2 < 0x50);
  *(code **)(*(int *)(param_1 + 400) + 0x10) = grim_jpg_idct_float;
  *(code **)(*(int *)(param_1 + 400) + 0x48) = grim_jpg_upsample_h2v1;
  grim_jpg_decompress_setup(param_1);
  return;
}



/* grim_jpg_create_decompress_full @ 1001df16 */

void grim_jpg_create_decompress_full(int *param_1)

{
  (**(code **)(*param_1 + 8))(param_1);
  grim_jpg_cleanup((int)param_1);
                    /* WARNING: Subroutine does not return */
  exit(1);
}



/* grim_jpg_decompress_init @ 1001e027 */

void __cdecl grim_jpg_decompress_init(undefined4 *param_1)

{
  *param_1 = grim_jpg_create_decompress_full;
  param_1[1] = &LAB_1001df4e;
  param_1[2] = &LAB_1001df31;
  param_1[3] = &LAB_1001df7f;
  param_1[4] = &LAB_1001e016;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[5] = 0;
  param_1[0x1c] = &PTR_s_Bogus_message_code__d_1004ce48;
  param_1[0x1d] = 0x77;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  return;
}



/* grim_jpg_error_setup_longjmp @ 100230f1 */

void __cdecl grim_jpg_error_setup_longjmp(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)param_1[99];
  *(undefined1 *)(puVar1 + 4) = 0;
  *(undefined1 *)((int)puVar1 + 0x11) = 0;
  *puVar1 = &LAB_1002305e;
  *(undefined1 *)(puVar1 + 5) = 1;
  (**(code **)(*param_1 + 0x10))(param_1);
  (**(code **)param_1[100])(param_1);
  param_1[0x23] = 0;
  return;
}



/* grim_jpg_error_init @ 10023139 */

void __cdecl grim_jpg_error_init(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x18);
  *(undefined4 **)(param_1 + 0x18c) = puVar1;
  *(undefined1 *)(puVar1 + 4) = 0;
  *(undefined1 *)((int)puVar1 + 0x11) = 0;
  *puVar1 = &LAB_1002305e;
  puVar1[1] = grim_jpg_error_setup_longjmp;
  puVar1[2] = grim_fpu_matrix_inverse_and_transform;
  puVar1[3] = &LAB_10023128;
  *(undefined1 *)(puVar1 + 5) = 1;
  return;
}



/* grim_jpg_bit_buffer_init @ 1002317a */

void __fastcall grim_jpg_bit_buffer_init(undefined4 param_1,undefined4 param_2)

{
  int *in_EAX;
  
  *(undefined4 *)(*in_EAX + 0x14) = 0x35;
  *(undefined4 *)(*in_EAX + 0x18) = param_2;
  (**(code **)*in_EAX)();
  return;
}



/* grim_jpg_entropy_read_bits @ 1002318f */

/* [binja] void* sub_1002318f(int32_t* arg1, int32_t* arg2, int32_t* arg3) */

void * __thiscall grim_jpg_entropy_read_bits(void *this,int *arg1,int *arg2,int *arg3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  
  iVar3 = arg1[1];
  if ((int *)0x3b9ac9f0 < arg3) {
    grim_jpg_bit_buffer_init(this,1);
  }
  piVar6 = arg3;
  if (((uint)arg3 & 7) != 0) {
    piVar6 = (int *)((int)arg3 + (8 - ((uint)arg3 & 7)));
  }
  if (((int)arg2 < 0) || (1 < (int)arg2)) {
    *(undefined4 *)(*arg1 + 0x14) = 0xc;
    *(int **)(*arg1 + 0x18) = arg2;
    (**(code **)*arg1)(arg1);
  }
  arg3 = (int *)0x0;
  piVar2 = (int *)(iVar3 + 0x30 + (int)arg2 * 4);
  piVar5 = (int *)*piVar2;
  if (piVar5 != (int *)0x0) {
    do {
      piVar4 = piVar5;
      piVar5 = piVar4;
      if (piVar6 <= (int *)piVar4[2]) break;
      piVar5 = (int *)*piVar4;
      arg3 = piVar4;
    } while (piVar5 != (int *)0x0);
    if (piVar5 != (int *)0x0) goto LAB_10023275;
  }
  piVar4 = piVar6 + 4;
  if (arg3 == (int *)0x0) {
    uVar7 = *(uint *)(&DAT_1004ea00 + (int)arg2 * 4);
  }
  else {
    uVar7 = *(uint *)(&DAT_1004ea08 + (int)arg2 * 4);
  }
  if (1000000000U - (int)piVar4 < uVar7) {
    uVar7 = 1000000000U - (int)piVar4;
  }
  while( true ) {
    iVar8 = uVar7 + (int)piVar4;
    piVar5 = (int *)grim_jpg_bit_read_byte((uint)arg1);
    if (piVar5 != (int *)0x0) break;
    uVar7 = uVar7 >> 1;
    if (uVar7 < 0x32) {
      grim_jpg_bit_buffer_init(iVar8,2);
    }
  }
  piVar1 = (int *)(iVar3 + 0x48);
  *piVar1 = (int)piVar4 + *piVar1 + uVar7;
  *piVar5 = 0;
  piVar5[1] = 0;
  piVar5[2] = uVar7 + (int)piVar6;
  if (arg3 == (int *)0x0) {
    arg3 = piVar2;
  }
  *arg3 = (int)piVar5;
LAB_10023275:
  iVar3 = piVar5[1];
  piVar5[2] = piVar5[2] - (int)piVar6;
  piVar5[1] = iVar3 + (int)piVar6;
  return (void *)(iVar3 + 0x10 + (int)piVar5);
}



/* grim_jpg_entropy_peek_bits @ 1002328b */

/* [binja] void* sub_1002328b(uint32_t arg1, int32_t arg2, int32_t arg3) */

void * __thiscall grim_jpg_entropy_peek_bits(void *this,uint arg1,int arg2,int arg3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  
  iVar3 = *(int *)(arg1 + 4);
  if (0x3b9ac9f0 < (uint)arg3) {
    grim_jpg_bit_buffer_init(this,3);
  }
  if ((arg3 & 7U) != 0) {
    arg3 = arg3 + (8 - (arg3 & 7U));
  }
  if ((arg2 < 0) || (1 < arg2)) {
    *(undefined4 *)(*(int *)arg1 + 0x14) = 0xc;
    *(int *)(*(int *)arg1 + 0x18) = arg2;
    (*(code *)**(undefined4 **)arg1)(arg1);
  }
  iVar6 = arg3 + 0x10;
  puVar5 = (undefined4 *)grim_jpg_bit_read_byte(arg1);
  if (puVar5 == (undefined4 *)0x0) {
    grim_jpg_bit_buffer_init(iVar6,4);
  }
  piVar1 = (int *)(iVar3 + 0x48);
  *piVar1 = *piVar1 + arg3 + 0x10;
  puVar2 = (undefined4 *)(iVar3 + 0x38 + arg2 * 4);
  uVar4 = *puVar2;
  puVar5[2] = 0;
  puVar5[1] = arg3;
  *puVar5 = uVar4;
  *puVar2 = puVar5;
  return puVar5 + 4;
}



/* grim_jpg_entropy_decode_ac_coeff @ 10023319 */

int __cdecl grim_jpg_entropy_decode_ac_coeff(int *param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  void *pvVar4;
  int *this;
  void *extraout_ECX;
  void *this_00;
  void *extraout_ECX_00;
  uint uVar5;
  uint uVar6;
  
  uVar2 = (uint)(0x3b9ac9f0 / (ulonglong)param_3);
  iVar1 = param_1[1];
  this = param_1;
  if (uVar2 == 0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x45;
    (**(code **)*param_1)();
  }
  if ((int)param_4 <= (int)uVar2) {
    uVar2 = param_4;
  }
  *(uint *)(iVar1 + 0x4c) = uVar2;
  pvVar3 = grim_jpg_entropy_read_bits(this,param_1,(int *)param_2,(int *)(param_4 << 2));
  uVar6 = 0;
  this_00 = extraout_ECX;
  if (param_4 != 0) {
    do {
      if (param_4 - uVar6 <= uVar2) {
        uVar2 = param_4 - uVar6;
      }
      pvVar4 = grim_jpg_entropy_peek_bits(this_00,(uint)param_1,param_2,uVar2 * param_3);
      this_00 = extraout_ECX_00;
      for (uVar5 = uVar2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(void **)((int)pvVar3 + uVar6 * 4) = pvVar4;
        pvVar4 = (void *)((int)pvVar4 + param_3);
        uVar6 = uVar6 + 1;
        this_00 = (void *)0x0;
      }
    } while (uVar6 < param_4);
  }
  return (int)pvVar3;
}



/* grim_jpg_entropy_decode_dc_coeff @ 100233ab */

int __cdecl grim_jpg_entropy_decode_dc_coeff(int *param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  void *pvVar3;
  void *pvVar4;
  int *piVar5;
  int *this;
  void *extraout_ECX;
  void *this_00;
  void *extraout_ECX_00;
  uint uVar6;
  uint uVar7;
  
  piVar5 = (int *)(param_3 * 0x80);
  uVar2 = (uint)(0x3b9ac9f0 / ZEXT48(piVar5));
  iVar1 = param_1[1];
  this = piVar5;
  if (uVar2 == 0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x45;
    this = param_1;
    (**(code **)*param_1)();
  }
  if ((int)param_4 <= (int)uVar2) {
    uVar2 = param_4;
  }
  *(uint *)(iVar1 + 0x4c) = uVar2;
  pvVar3 = grim_jpg_entropy_read_bits(this,param_1,(int *)param_2,(int *)(param_4 << 2));
  uVar7 = 0;
  this_00 = extraout_ECX;
  if (param_4 != 0) {
    do {
      if (param_4 - uVar7 <= uVar2) {
        uVar2 = param_4 - uVar7;
      }
      pvVar4 = grim_jpg_entropy_peek_bits(this_00,(uint)param_1,param_2,uVar2 * param_3 * 0x80);
      this_00 = extraout_ECX_00;
      for (uVar6 = uVar2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(void **)((int)pvVar3 + uVar7 * 4) = pvVar4;
        pvVar4 = (void *)((int)pvVar4 + (int)piVar5);
        uVar7 = uVar7 + 1;
        this_00 = (void *)0x0;
      }
    } while (uVar7 < param_4);
  }
  return (int)pvVar3;
}



/* grim_jpg_entropy_skip_bits @ 10023449 */

/* [binja] void* sub_10023449(int32_t* arg1, int32_t* arg2, char arg3, int32_t arg4, int32_t arg5,
   int32_t arg6) */

void * __thiscall grim_jpg_entropy_skip_bits(void *this,int *arg1,int *arg2,char arg3,int arg4,int arg5,int arg6)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = arg1[1];
  if (arg2 != (int *)0x1) {
    *(undefined4 *)(*arg1 + 0x14) = 0xc;
    *(int **)(*arg1 + 0x18) = arg2;
    this = arg1;
    (**(code **)*arg1)();
  }
  puVar2 = grim_jpg_entropy_read_bits(this,arg1,arg2,(int *)0x78);
  *puVar2 = 0;
  puVar2[1] = arg5;
  puVar2[2] = arg4;
  puVar2[3] = arg6;
  *(undefined1 *)((int)puVar2 + 0x22) = 0;
  *(char *)(puVar2 + 8) = arg3;
  puVar2[9] = *(undefined4 *)(iVar1 + 0x40);
  *(undefined4 **)(iVar1 + 0x40) = puVar2;
  return puVar2;
}



/* grim_jpg_entropy_align_byte @ 100234aa */

/* [binja] void* sub_100234aa(int32_t* arg1, int32_t* arg2, char arg3, int32_t arg4, int32_t arg5,
   int32_t arg6) */

void * __thiscall grim_jpg_entropy_align_byte(void *this,int *arg1,int *arg2,char arg3,int arg4,int arg5,int arg6)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = arg1[1];
  if (arg2 != (int *)0x1) {
    *(undefined4 *)(*arg1 + 0x14) = 0xc;
    *(int **)(*arg1 + 0x18) = arg2;
    this = arg1;
    (**(code **)*arg1)();
  }
  puVar2 = grim_jpg_entropy_read_bits(this,arg1,arg2,(int *)0x78);
  *puVar2 = 0;
  puVar2[1] = arg5;
  puVar2[2] = arg4;
  puVar2[3] = arg6;
  *(undefined1 *)((int)puVar2 + 0x22) = 0;
  *(char *)(puVar2 + 8) = arg3;
  puVar2[9] = *(undefined4 *)(iVar1 + 0x44);
  *(undefined4 **)(iVar1 + 0x44) = puVar2;
  return puVar2;
}



/* grim_jpg_entropy_decode_block @ 1002350b */

void __cdecl grim_jpg_entropy_decode_block(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int local_8;
  
  iVar1 = param_1[1];
  iVar4 = 0;
  iVar3 = 0;
  for (piVar2 = *(int **)(iVar1 + 0x40); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[9]) {
    if (*piVar2 == 0) {
      iVar4 = iVar4 + piVar2[3] * piVar2[2];
      iVar3 = iVar3 + piVar2[1] * piVar2[2];
    }
  }
  for (piVar2 = *(int **)(iVar1 + 0x44); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[9]) {
    if (*piVar2 == 0) {
      iVar4 = iVar4 + piVar2[3] * piVar2[2] * 0x80;
      iVar3 = iVar3 + piVar2[1] * piVar2[2] * 0x80;
    }
  }
  if (0 < iVar4) {
    local_8 = grim_jpg_bit_skip_byte((int)param_1);
    if (local_8 < iVar3) {
      local_8 = local_8 / iVar4;
      if (local_8 < 1) {
        local_8 = 1;
      }
    }
    else {
      local_8 = 1000000000;
    }
    for (piVar2 = *(int **)(iVar1 + 0x40); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[9]) {
      if (*piVar2 == 0) {
        if (local_8 < (int)((piVar2[1] - 1U) / (uint)piVar2[3] + 1)) {
          piVar2[4] = piVar2[3] * local_8;
          grim_jpg_bit_peek_byte(param_1);
          *(undefined1 *)((int)piVar2 + 0x22) = 1;
        }
        else {
          piVar2[4] = piVar2[1];
        }
        iVar3 = grim_jpg_entropy_decode_ac_coeff(param_1,1,piVar2[2],piVar2[4]);
        *piVar2 = iVar3;
        iVar3 = *(int *)(iVar1 + 0x4c);
        piVar2[6] = 0;
        piVar2[7] = 0;
        *(undefined1 *)((int)piVar2 + 0x21) = 0;
        piVar2[5] = iVar3;
      }
    }
    for (piVar2 = *(int **)(iVar1 + 0x44); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[9]) {
      if (*piVar2 == 0) {
        if (local_8 < (int)((piVar2[1] - 1U) / (uint)piVar2[3] + 1)) {
          piVar2[4] = piVar2[3] * local_8;
          grim_jpg_bit_peek_byte(param_1);
          *(undefined1 *)((int)piVar2 + 0x22) = 1;
        }
        else {
          piVar2[4] = piVar2[1];
        }
        iVar3 = grim_jpg_entropy_decode_dc_coeff(param_1,1,piVar2[2],piVar2[4]);
        *piVar2 = iVar3;
        iVar3 = *(int *)(iVar1 + 0x4c);
        piVar2[6] = 0;
        piVar2[7] = 0;
        *(undefined1 *)((int)piVar2 + 0x21) = 0;
        piVar2[5] = iVar3;
      }
    }
  }
  return;
}



/* grim_jpg_dequant_table_scale_islow @ 1002368a */

void __cdecl grim_jpg_dequant_table_scale_islow(undefined4 param_1,char param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *unaff_ESI;
  int iVar5;
  
  iVar1 = unaff_ESI[2];
  iVar4 = unaff_ESI[6] * iVar1;
  iVar3 = unaff_ESI[4];
  iVar5 = 0;
  if (0 < iVar3) {
    do {
      iVar2 = iVar3 - iVar5;
      if (unaff_ESI[5] < iVar3 - iVar5) {
        iVar2 = unaff_ESI[5];
      }
      iVar3 = unaff_ESI[7] - (unaff_ESI[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      iVar3 = unaff_ESI[1] - (unaff_ESI[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      if (iVar2 < 1) {
        return;
      }
      iVar2 = iVar2 * iVar1;
      if (param_2 == '\0') {
        (*(code *)unaff_ESI[10])
                  (param_1,unaff_ESI + 10,*(undefined4 *)(*unaff_ESI + iVar5 * 4),iVar4,iVar2);
      }
      else {
        (*(code *)unaff_ESI[0xb])(param_1,unaff_ESI + 10,*(undefined4 *)(*unaff_ESI + iVar5 * 4));
      }
      iVar5 = iVar5 + unaff_ESI[5];
      iVar3 = unaff_ESI[4];
      iVar4 = iVar4 + iVar2;
    } while (iVar5 < iVar3);
  }
  return;
}



/* grim_jpg_dequant_table_scale_ifast @ 10023712 */

void __cdecl grim_jpg_dequant_table_scale_ifast(undefined4 param_1,char param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *unaff_ESI;
  int iVar5;
  
  iVar1 = unaff_ESI[2];
  iVar4 = unaff_ESI[6] * iVar1 * 0x80;
  iVar3 = unaff_ESI[4];
  iVar5 = 0;
  if (0 < iVar3) {
    do {
      iVar2 = iVar3 - iVar5;
      if (unaff_ESI[5] < iVar3 - iVar5) {
        iVar2 = unaff_ESI[5];
      }
      iVar3 = unaff_ESI[7] - (unaff_ESI[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      iVar3 = unaff_ESI[1] - (unaff_ESI[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      if (iVar2 < 1) {
        return;
      }
      iVar2 = iVar2 * iVar1 * 0x80;
      if (param_2 == '\0') {
        (*(code *)unaff_ESI[10])
                  (param_1,unaff_ESI + 10,*(undefined4 *)(*unaff_ESI + iVar5 * 4),iVar4,iVar2);
      }
      else {
        (*(code *)unaff_ESI[0xb])(param_1,unaff_ESI + 10,*(undefined4 *)(*unaff_ESI + iVar5 * 4));
      }
      iVar5 = iVar5 + unaff_ESI[5];
      iVar3 = unaff_ESI[4];
      iVar4 = iVar4 + iVar2;
    } while (iVar5 < iVar3);
  }
  return;
}



/* grim_jpg_dequant_table_prepare_islow @ 1002379d */

int __cdecl grim_jpg_dequant_table_prepare_islow(int *param_1,int *param_2,uint param_3,uint param_4,char param_5)

{
  uint uVar1;
  uint size;
  int iVar2;
  uint uVar3;
  
  uVar1 = param_3 + param_4;
  if ((((uint)param_2[1] < uVar1) || ((uint)param_2[3] < param_4)) || (*param_2 == 0)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    (**(code **)*param_1)(param_1);
  }
  if ((param_3 < (uint)param_2[6]) || ((uint)(param_2[4] + param_2[6]) < uVar1)) {
    if (*(char *)((int)param_2 + 0x22) == '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x44;
      (**(code **)*param_1)(param_1);
    }
    if (*(char *)((int)param_2 + 0x21) != '\0') {
      grim_jpg_dequant_table_scale_islow(param_1,'\x01');
      *(undefined1 *)((int)param_2 + 0x21) = 0;
    }
    uVar3 = param_3;
    if ((param_3 <= (uint)param_2[6]) && (uVar3 = uVar1 - param_2[4], (int)uVar3 < 0)) {
      uVar3 = 0;
    }
    param_2[6] = uVar3;
    grim_jpg_dequant_table_scale_islow(param_1,'\0');
  }
  uVar3 = param_2[7];
  if (uVar3 < uVar1) {
    if ((uVar3 < param_3) && (uVar3 = param_3, param_5 != '\0')) {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      (**(code **)*param_1)(param_1);
    }
    if (param_5 != '\0') {
      param_2[7] = uVar1;
    }
    if ((char)param_2[8] != '\0') {
      size = param_2[2];
      iVar2 = param_2[6];
      for (uVar3 = uVar3 - iVar2; uVar3 < uVar1 - iVar2; uVar3 = uVar3 + 1) {
        memzero(*(void **)(*param_2 + uVar3 * 4),size);
      }
      goto LAB_100238a1;
    }
    if (param_5 == '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      (**(code **)*param_1)(param_1);
      goto LAB_100238a1;
    }
  }
  else {
LAB_100238a1:
    if (param_5 == '\0') goto LAB_100238ab;
  }
  *(undefined1 *)((int)param_2 + 0x21) = 1;
LAB_100238ab:
  return *param_2 + (param_3 - param_2[6]) * 4;
}



/* grim_jpg_dequant_table_prepare_ifast @ 100238bb */

int __cdecl grim_jpg_dequant_table_prepare_ifast(int *param_1,int *param_2,uint param_3,uint param_4,char param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = param_3 + param_4;
  if ((((uint)param_2[1] < uVar1) || ((uint)param_2[3] < param_4)) || (*param_2 == 0)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x14;
    (**(code **)*param_1)(param_1);
  }
  if ((param_3 < (uint)param_2[6]) || ((uint)(param_2[4] + param_2[6]) < uVar1)) {
    if (*(char *)((int)param_2 + 0x22) == '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x44;
      (**(code **)*param_1)(param_1);
    }
    if (*(char *)((int)param_2 + 0x21) != '\0') {
      grim_jpg_dequant_table_scale_ifast(param_1,'\x01');
      *(undefined1 *)((int)param_2 + 0x21) = 0;
    }
    if ((uint)param_2[6] < param_3) {
      param_2[6] = param_3;
    }
    else {
      iVar3 = uVar1 - param_2[4];
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      param_2[6] = iVar3;
    }
    grim_jpg_dequant_table_scale_ifast(param_1,'\0');
  }
  uVar4 = param_2[7];
  if (uVar4 < uVar1) {
    if ((uVar4 < param_3) && (uVar4 = param_3, param_5 != '\0')) {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      (**(code **)*param_1)(param_1);
    }
    if (param_5 != '\0') {
      param_2[7] = uVar1;
    }
    if ((char)param_2[8] != '\0') {
      iVar3 = param_2[6];
      iVar2 = param_2[2];
      for (uVar4 = uVar4 - iVar3; uVar4 < uVar1 - iVar3; uVar4 = uVar4 + 1) {
        memzero(*(void **)(*param_2 + uVar4 * 4),iVar2 << 7);
      }
      goto LAB_100239c4;
    }
    if (param_5 == '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x14;
      (**(code **)*param_1)(param_1);
      goto LAB_100239c4;
    }
  }
  else {
LAB_100239c4:
    if (param_5 == '\0') goto LAB_100239ce;
  }
  *(undefined1 *)((int)param_2 + 0x21) = 1;
LAB_100239ce:
  return *param_2 + (param_3 - param_2[6]) * 4;
}



/* grim_jpg_dequant_table_prepare_float @ 100239de */

void __cdecl grim_jpg_dequant_table_prepare_float(int *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar1 = param_1[1];
  if ((param_2 < 0) || (1 < param_2)) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  if (param_2 == 1) {
    for (iVar5 = *(int *)(iVar1 + 0x40); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x24)) {
      if (*(char *)(iVar5 + 0x22) != '\0') {
        *(undefined1 *)(iVar5 + 0x22) = 0;
        (**(code **)(iVar5 + 0x30))(param_1,iVar5 + 0x28);
      }
    }
    *(undefined4 *)(iVar1 + 0x40) = 0;
    for (iVar5 = *(int *)(iVar1 + 0x44); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x24)) {
      if (*(char *)(iVar5 + 0x22) != '\0') {
        *(undefined1 *)(iVar5 + 0x22) = 0;
        (**(code **)(iVar5 + 0x30))(param_1,iVar5 + 0x28);
      }
    }
    *(undefined4 *)(iVar1 + 0x44) = 0;
  }
  puVar2 = *(undefined4 **)(iVar1 + 0x38 + param_2 * 4);
  *(undefined4 *)(iVar1 + 0x38 + param_2 * 4) = 0;
  while (puVar2 != (undefined4 *)0x0) {
    iVar5 = puVar2[2];
    iVar3 = puVar2[1];
    puVar4 = (undefined4 *)*puVar2;
    zcfree(param_1,puVar2);
    *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) - (iVar5 + 0x10 + iVar3);
    puVar2 = puVar4;
  }
  puVar2 = (undefined4 *)(iVar1 + 0x30 + param_2 * 4);
  puVar4 = (undefined4 *)*puVar2;
  *puVar2 = 0;
  while (puVar4 != (undefined4 *)0x0) {
    iVar5 = puVar4[2];
    iVar3 = puVar4[1];
    puVar2 = (undefined4 *)*puVar4;
    zcfree(param_1,puVar4);
    *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) - (iVar5 + 0x10 + iVar3);
    puVar4 = puVar2;
  }
  return;
}



/* grim_jpg_entropy_decoder_init @ 10023abf */

void __cdecl grim_jpg_entropy_decoder_init(int *param_1)

{
  int iVar1;
  
  iVar1 = 1;
  do {
    grim_jpg_dequant_table_prepare_float(param_1,iVar1);
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  zcfree(param_1,(voidpf)param_1[1]);
  param_1[1] = 0;
  grim_pixel_noop();
  return;
}



/* grim_jpg_mem_init @ 10023aef */

void __cdecl grim_jpg_mem_init(int *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  
  param_1[1] = 0;
  uVar1 = grim_jpg_bit_read_short();
  puVar2 = (undefined4 *)grim_jpg_bit_read_byte((uint)param_1);
  if (puVar2 == (undefined4 *)0x0) {
    piVar5 = param_1;
    grim_pixel_noop();
    *(undefined4 *)(*param_1 + 0x14) = 0x35;
    *(undefined4 *)(*param_1 + 0x18) = 0;
    (**(code **)*param_1)(param_1,piVar5);
  }
  else {
    *puVar2 = grim_jpg_entropy_read_bits;
    puVar2[1] = grim_jpg_entropy_peek_bits;
    puVar2[2] = grim_jpg_entropy_decode_ac_coeff;
    puVar2[3] = grim_jpg_entropy_decode_dc_coeff;
    puVar2[4] = grim_jpg_entropy_skip_bits;
    puVar2[5] = grim_jpg_entropy_align_byte;
    puVar2[6] = grim_jpg_entropy_decode_block;
    puVar2[7] = grim_jpg_dequant_table_prepare_islow;
    puVar2[8] = grim_jpg_dequant_table_prepare_ifast;
    puVar2[9] = grim_jpg_dequant_table_prepare_float;
    puVar2[10] = grim_jpg_entropy_decoder_init;
    puVar2[0xb] = uVar1;
    puVar3 = puVar2 + 0xf;
    iVar4 = 2;
    do {
      puVar3[-2] = 0;
      *puVar3 = 0;
      puVar3 = puVar3 + -1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    puVar2[0x10] = 0;
    puVar2[0x11] = 0;
    puVar2[0x12] = 0x50;
    param_1[1] = (int)puVar2;
  }
  return;
}



/* grim_jpg_mem_term @ 10023ba3 */

void __cdecl grim_jpg_mem_term(int param_1)

{
  (**(code **)(*(int *)(param_1 + 4) + 0x24))(param_1,1);
  *(uint *)(param_1 + 0x10) = (-(uint)(*(char *)(param_1 + 0xc) != '\0') & 100) + 100;
  return;
}



/* grim_jpg_cleanup @ 10023bc5 */

void __cdecl grim_jpg_cleanup(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(*(int *)(param_1 + 4) + 0x28))(param_1);
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}



/* grim_jpg_natural_order_lookup @ 10023be0 */

void __cdecl grim_jpg_natural_order_lookup(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x82);
  *(undefined1 *)(iVar1 + 0x80) = 0;
  return;
}



/* grim_jpg_zigzag_index_lookup @ 10023bfc */

void __cdecl grim_jpg_zigzag_index_lookup(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x112);
  *(undefined1 *)(iVar1 + 0x111) = 0;
  return;
}



/* grim_jpg_mem_alloc_small @ 10023c18 */

/* [binja] int32_t __fastcall sub_10023c18(int32_t arg1, void* arg2) */

int __fastcall grim_jpg_mem_alloc_small(int arg1,void *arg2)

{
  int iVar1;
  int iVar2;
  uint in_EAX;
  
  if (((((*(char *)((int)arg2 + 0x48) != '\0') || (*(char *)((int)arg2 + 0x108) != '\0')) ||
       (*(int *)((int)arg2 + 0x24) != 3)) ||
      (((*(int *)((int)arg2 + 0x20) != 3 || (*(int *)((int)arg2 + 0x28) != 2)) ||
       ((*(int *)((int)arg2 + 100) != 3 ||
        ((iVar1 = *(int *)((int)arg2 + 0xc4), *(int *)(iVar1 + 8) != 2 ||
         (in_EAX = 1, *(int *)(iVar1 + 0x5c) != 1)))))))) ||
     ((*(int *)(iVar1 + 0xb0) != 1 ||
      (((((2 < *(int *)(iVar1 + 0xc) || (*(int *)(iVar1 + 0x60) != 1)) ||
         (*(int *)(iVar1 + 0xb4) != 1)) ||
        ((iVar2 = *(int *)((int)arg2 + 0x114), *(int *)(iVar1 + 0x24) != iVar2 ||
         (*(int *)(iVar1 + 0x78) != iVar2)))) || (*(int *)(iVar1 + 0xcc) != iVar2)))))) {
    in_EAX = in_EAX & 0xffffff00;
  }
  return in_EAX;
}



/* grim_jpg_mem_alloc_large @ 10023c89 */

void __cdecl grim_jpg_mem_alloc_large(int *param_1)

{
  uint uVar1;
  int *piVar2;
  int *arg2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_8;
  
  arg2 = param_1;
  if (param_1[4] != 0xca) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  iVar3 = param_1[0xb];
  uVar1 = param_1[0xc];
  if (uVar1 < (uint)(iVar3 << 3)) {
    if (uVar1 < (uint)(iVar3 << 2)) {
      if (uVar1 < (uint)(iVar3 * 2)) {
        param_1[0x17] = param_1[6];
        iVar3 = param_1[7];
        param_1[0x45] = 8;
      }
      else {
        iVar3 = grim_fpu_control_word(param_1[6],2);
        param_1[0x17] = iVar3;
        iVar3 = grim_fpu_control_word(param_1[7],2);
        param_1[0x45] = 4;
      }
    }
    else {
      iVar3 = grim_fpu_control_word(param_1[6],4);
      param_1[0x17] = iVar3;
      iVar3 = grim_fpu_control_word(param_1[7],4);
      param_1[0x45] = 2;
    }
  }
  else {
    iVar3 = grim_fpu_control_word(param_1[6],8);
    param_1[0x17] = iVar3;
    iVar3 = grim_fpu_control_word(param_1[7],8);
    param_1[0x45] = 1;
  }
  local_8 = 0;
  param_1[0x18] = iVar3;
  if (0 < param_1[8]) {
    piVar4 = (int *)(param_1[0x31] + 0xc);
    do {
      piVar2 = (int *)arg2[0x45];
      param_1 = piVar2;
      if ((int)piVar2 < 8) {
        do {
          iVar3 = piVar4[-1] * (int)param_1 * 2;
          if ((iVar3 - arg2[0x43] * (int)piVar2 != 0 && arg2[0x43] * (int)piVar2 <= iVar3) ||
             (iVar3 = *piVar4 * (int)param_1 * 2,
             iVar3 - arg2[0x44] * (int)piVar2 != 0 && arg2[0x44] * (int)piVar2 <= iVar3)) break;
          param_1 = (int *)((int)param_1 * 2);
        } while ((int)param_1 < 8);
      }
      local_8 = local_8 + 1;
      piVar4[6] = (int)param_1;
      piVar4 = piVar4 + 0x15;
    } while (local_8 < arg2[8]);
  }
  iVar3 = 0;
  if (0 < arg2[8]) {
    piVar4 = (int *)(arg2[0x31] + 0x24);
    do {
      iVar5 = grim_fpu_control_word(piVar4[-7] * *piVar4 * arg2[6],arg2[0x43] << 3);
      piVar4[1] = iVar5;
      iVar5 = grim_fpu_control_word(piVar4[-6] * arg2[7] * *piVar4,arg2[0x44] << 3);
      piVar4[2] = iVar5;
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 0x15;
    } while (iVar3 < arg2[8]);
  }
  iVar3 = arg2[10];
  iVar5 = 1;
  if (iVar3 == 1) {
LAB_10023e44:
    arg2[0x19] = iVar5;
  }
  else {
    if (1 < iVar3) {
      iVar5 = 3;
      if (iVar3 < 4) goto LAB_10023e44;
      if (iVar3 < 6) {
        arg2[0x19] = 4;
        goto LAB_10023e47;
      }
    }
    arg2[0x19] = arg2[8];
  }
LAB_10023e47:
  if (*(char *)((int)arg2 + 0x4a) == '\0') {
    iVar3 = arg2[0x19];
  }
  else {
    iVar3 = 1;
  }
  arg2[0x1a] = iVar3;
  iVar3 = grim_jpg_mem_alloc_small(iVar5,arg2);
  if ((char)iVar3 == '\0') {
    arg2[0x1b] = 1;
  }
  else {
    arg2[0x1b] = arg2[0x44];
  }
  return;
}



/* grim_jpg_mem_alloc_sarray @ 10023e78 */

void grim_jpg_mem_alloc_sarray(void)

{
  int in_EAX;
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(in_EAX + 4))();
  iVar2 = 0;
  *(undefined4 **)(in_EAX + 0x11c) = puVar1 + 0x40;
  puVar4 = puVar1;
  for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  do {
    *(char *)(iVar2 + (int)(puVar1 + 0x40)) = (char)iVar2;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  puVar4 = puVar1 + 0x80;
  for (iVar3 = 0x60; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  puVar4 = puVar1 + 0xe0;
  for (iVar3 = 0x60; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = *(undefined4 **)(in_EAX + 0x11c);
  puVar1 = puVar1 + 0x140;
  for (iVar3 = 0x20; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar1 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar1 = puVar1 + 1;
  }
  return;
}



/* grim_jpg_mem_manager_init @ 10023ee7 */

void grim_jpg_mem_manager_init(void)

{
  int iVar1;
  int iVar2;
  int arg1;
  int *unaff_ESI;
  char local_8;
  
  iVar1 = unaff_ESI[0x5f];
  grim_jpg_mem_alloc_large(unaff_ESI);
  grim_jpg_mem_alloc_sarray();
  *(undefined4 *)(iVar1 + 0xc) = 0;
  iVar2 = grim_jpg_mem_alloc_small(arg1,unaff_ESI);
  *(char *)(iVar1 + 0x10) = (char)iVar2;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  if ((*(char *)((int)unaff_ESI + 0x4a) == '\0') || ((char)unaff_ESI[0x10] == '\0')) {
    *(undefined1 *)(unaff_ESI + 0x16) = 0;
    *(undefined1 *)((int)unaff_ESI + 0x59) = 0;
    *(undefined1 *)((int)unaff_ESI + 0x5a) = 0;
  }
  if (*(char *)((int)unaff_ESI + 0x4a) == '\0') goto LAB_10023f85;
  if (*(char *)((int)unaff_ESI + 0x41) != '\0') {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x2e;
    (**(code **)*unaff_ESI)();
  }
  if (unaff_ESI[0x19] == 3) {
    if (unaff_ESI[0x1d] == 0) {
      if ((char)unaff_ESI[0x14] == '\0') goto LAB_10023f52;
      *(undefined1 *)((int)unaff_ESI + 0x5a) = 1;
    }
    else {
      *(undefined1 *)((int)unaff_ESI + 0x59) = 1;
    }
  }
  else {
    *(undefined1 *)((int)unaff_ESI + 0x59) = 0;
    *(undefined1 *)((int)unaff_ESI + 0x5a) = 0;
    unaff_ESI[0x1d] = 0;
LAB_10023f52:
    *(undefined1 *)(unaff_ESI + 0x16) = 1;
  }
  if ((char)unaff_ESI[0x16] != '\0') {
    grim_jpg_cquantize_init(unaff_ESI);
    *(int *)(iVar1 + 0x14) = unaff_ESI[0x69];
  }
  if ((*(char *)((int)unaff_ESI + 0x5a) != '\0') || (*(char *)((int)unaff_ESI + 0x59) != '\0')) {
    grim_jpg_coeff_quantize_and_pack(unaff_ESI);
    *(int *)(iVar1 + 0x18) = unaff_ESI[0x69];
  }
LAB_10023f85:
  if (*(char *)((int)unaff_ESI + 0x41) == '\0') {
    if (*(char *)(iVar1 + 0x10) == '\0') {
      grim_jpg_coeff_transform_setup(unaff_ESI);
      grim_jpg_coeff_pipeline_setup(unaff_ESI);
    }
    else {
      grim_jpg_coeff_col_transform_setup((int)unaff_ESI);
    }
    grim_jpg_coeff_block_to_samples((int)unaff_ESI,*(char *)((int)unaff_ESI + 0x5a));
  }
  grim_jpg_scanline_output_start(unaff_ESI);
  if (*(char *)((int)unaff_ESI + 0xc9) == '\0') {
    if ((char)unaff_ESI[0x32] == '\0') {
      grim_jpg_huff_decoder_init((int)unaff_ESI);
    }
    else {
      grim_jpg_mcu_decoder_start((int)unaff_ESI);
    }
  }
  else {
    *(undefined4 *)(*unaff_ESI + 0x14) = 1;
    (**(code **)*unaff_ESI)();
  }
  if ((*(char *)(unaff_ESI[99] + 0x10) != '\0') || (local_8 = '\0', (char)unaff_ESI[0x10] != '\0'))
  {
    local_8 = '\x01';
  }
  grim_jpg_huff_decoder_setup((int)unaff_ESI,local_8);
  if (*(char *)((int)unaff_ESI + 0x41) == '\0') {
    grim_jpg_marker_read_tables(unaff_ESI,'\0');
  }
  (**(code **)(unaff_ESI[1] + 0x18))();
  (**(code **)(unaff_ESI[99] + 8))();
  if (((unaff_ESI[2] != 0) && ((char)unaff_ESI[0x10] == '\0')) &&
     (*(char *)(unaff_ESI[99] + 0x10) != '\0')) {
    iVar2 = unaff_ESI[8];
    if ((char)unaff_ESI[0x32] != '\0') {
      iVar2 = iVar2 * 3 + 2;
    }
    *(undefined4 *)(unaff_ESI[2] + 4) = 0;
    *(int *)(unaff_ESI[2] + 8) = unaff_ESI[0x46] * iVar2;
    *(undefined4 *)(unaff_ESI[2] + 0xc) = 0;
    *(uint *)(unaff_ESI[2] + 0x10) = (*(char *)((int)unaff_ESI + 0x5a) != '\0') + 2;
    *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 1;
  }
  return;
}



/* grim_jpg_huff_table_build @ 1002c7c0 */

void grim_jpg_huff_table_build(undefined8 *param_1,undefined4 *param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined8 in_MM4;
  undefined8 uVar8;
  undefined4 uVar10;
  undefined8 uVar9;
  undefined8 in_MM5;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 in_MM6;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 in_MM7;
  undefined8 uVar17;
  undefined4 uStack_2c;
  
  uVar2 = param_3[2];
  uVar3 = param_3[4];
  uVar11 = PackedSwapDWords(in_MM5,uVar2);
  uVar8 = PackedSwapDWords(in_MM4,uVar3);
  uVar1 = *param_3;
  uVar14 = PackedSwapDWords(in_MM6,param_3[6]);
  uVar17 = PackedSwapDWords(in_MM7,uVar3);
  uVar11 = PackedFloatingMUL(uVar11,uVar1);
  uVar8 = PackedFloatingMUL(uVar8,uVar1);
  uVar14 = PackedFloatingMUL(uVar14,uVar1);
  uVar1 = PackedSwapDWords(uVar1,param_3[6]);
  uVar17 = PackedFloatingMUL(uVar17,uVar2);
  uVar12 = PackedFloatingNegAccumulate(uVar11,uVar8);
  uVar2 = PackedFloatingMUL(uVar2,uVar1);
  uVar3 = PackedFloatingMUL(uVar3,uVar1);
  uVar17 = PackedFloatingNegAccumulate(uVar14,uVar17);
  uVar1 = PackedFloatingNegAccumulate(uVar2,uVar3);
  uVar2 = param_3[7];
  uVar3 = param_3[5];
  uVar4 = (undefined4)((ulonglong)uVar17 >> 0x20);
  uVar10 = (undefined4)((ulonglong)uVar1 >> 0x20);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),uVar2);
  uVar6 = (undefined4)uVar1;
  uVar1 = PackedFloatingMUL(CONCAT44(uVar10,uVar10),param_3[3]);
  uVar11 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),uVar3);
  uVar1 = PackedFloatingADD(uVar8,uVar1);
  uVar14 = PackedFloatingSUB(uVar1,uVar11);
  uVar7 = (undefined4)uVar17;
  uVar5 = (undefined4)((ulonglong)uVar12 >> 0x20);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar10,uVar10),param_3[1]);
  uVar1 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar2);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar7,uVar7),uVar3);
  uVar1 = PackedFloatingSUB(uVar1,uVar9);
  uVar17 = PackedFloatingADD(uVar1,uVar8);
  uVar8 = CONCAT44((int)uVar12,(int)uVar12);
  uVar1 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),param_3[1]);
  uVar2 = PackedFloatingMUL(uVar2,uVar8);
  uVar11 = PackedFloatingMUL(CONCAT44(uVar7,uVar7),param_3[3]);
  uVar2 = PackedFloatingADD(uVar2,uVar1);
  uVar11 = PackedFloatingSUB(uVar2,uVar11);
  uVar1 = PackedFloatingMUL(uVar8,uVar3);
  uVar13 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),param_3[3]);
  uVar2 = param_3[1];
  uVar15 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),param_3[1]);
  uVar1 = PackedFloatingSUB(uVar1,uVar13);
  uVar12 = PackedFloatingADD(uVar1,uVar15);
  uVar1 = param_3[3];
  uVar8 = param_3[5];
  uVar13 = PackedSwapDWords(uVar13,uVar1);
  uVar9 = PackedSwapDWords(uVar9,uVar8);
  uVar13 = PackedFloatingMUL(uVar13,uVar2);
  uVar15 = PackedSwapDWords(uVar15,param_3[7]);
  uVar9 = PackedFloatingMUL(uVar9,uVar2);
  uVar3 = PackedSwapDWords(uVar3,uVar8);
  uVar16 = PackedFloatingMUL(uVar15,uVar2);
  uVar2 = PackedSwapDWords(uVar2,param_3[7]);
  uVar15 = PackedFloatingNegAccumulate(uVar13,uVar9);
  uVar9 = PackedFloatingMUL(uVar3,uVar1);
  uVar3 = PackedFloatingMUL(uVar1,uVar2);
  uVar2 = PackedFloatingMUL(uVar8,uVar2);
  uVar13 = PackedFloatingNegAccumulate(uVar16,uVar9);
  uVar1 = PackedFloatingNegAccumulate(uVar3,uVar2);
  uVar2 = param_3[6];
  uVar3 = param_3[4];
  uVar10 = (undefined4)((ulonglong)uVar1 >> 0x20);
  uVar6 = (undefined4)uVar1;
  uVar4 = (undefined4)((ulonglong)uVar13 >> 0x20);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar10,uVar10),param_3[2]);
  uVar1 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),uVar2);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),uVar3);
  uVar1 = PackedFloatingADD(uVar1,uVar9);
  uVar9 = PackedFloatingSUB(uVar1,uVar8);
  uVar7 = (undefined4)uVar13;
  uVar5 = (undefined4)((ulonglong)uVar15 >> 0x20);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar10,uVar10),*param_3);
  uVar1 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar2);
  uVar13 = PackedFloatingMUL(CONCAT44(uVar7,uVar7),uVar3);
  uVar1 = PackedFloatingSUB(uVar1,uVar13);
  uVar13 = PackedFloatingADD(uVar1,uVar8);
  uVar15 = CONCAT44((int)uVar15,(int)uVar15);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),*param_3);
  uVar1 = PackedFloatingMUL(uVar2,uVar15);
  uVar16 = PackedFloatingMUL(CONCAT44(uVar7,uVar7),param_3[2]);
  uVar1 = PackedFloatingADD(uVar1,uVar8);
  uVar1 = PackedFloatingSUB(uVar1,uVar16);
  uVar8 = PackedFloatingMUL(uVar15,uVar3);
  uVar15 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),param_3[2]);
  uVar16 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),*param_3);
  uVar8 = PackedFloatingSUB(uVar8,uVar15);
  uVar15 = PackedFloatingADD(uVar8,uVar16);
  uStack_2c = (undefined4)((ulonglong)uVar13 >> 0x20);
  uVar8 = CONCAT44(uStack_2c,(int)((ulonglong)uVar9 >> 0x20));
  uVar2 = PackedFloatingMUL(CONCAT44((int)((ulonglong)uVar15 >> 0x20),
                                     (int)((ulonglong)uVar1 >> 0x20)),
                            CONCAT44((int)uVar2,(int)uVar3));
  uVar3 = PackedFloatingMUL(CONCAT44(*(undefined4 *)(param_3 + 2),(int)*param_3),uVar8);
  uVar2 = PackedFloatingNegAccumulate(uVar2,uVar3);
  uVar2 = PackedFloatingAccumulate(uVar2,uVar2);
  uVar4 = (undefined4)uVar2;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = uVar4;
  }
  uVar3 = FloatingReciprocalAprox(uVar8,uVar2);
  uVar8 = PackedFloatingCompareEQ(0,uVar2);
  uVar2 = PackedFloatingReciprocalIter1(CONCAT44(uVar4,uVar4),uVar3);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar3);
  uVar2 = PackedFloatingMUL(uVar2,0xbf8000003f800000);
  uVar3 = PackedSwapDWords(uVar3,uVar2);
  if ((int)uVar8 == 0) {
    uVar8 = PackedFloatingMUL(uVar9,uVar3);
    uVar9 = PackedFloatingMUL(uVar13,uVar2);
    uVar14 = PackedFloatingMUL(uVar14,uVar3);
    uVar17 = PackedFloatingMUL(uVar17,uVar2);
    *param_1 = CONCAT44((int)((ulonglong)uVar9 >> 0x20),(int)((ulonglong)uVar8 >> 0x20));
    param_1[2] = CONCAT44((int)uVar9,(int)uVar8);
    param_1[4] = CONCAT44((int)((ulonglong)uVar17 >> 0x20),(int)((ulonglong)uVar14 >> 0x20));
    param_1[6] = CONCAT44((int)uVar17,(int)uVar14);
    uVar1 = PackedFloatingMUL(uVar1,uVar3);
    uVar8 = PackedFloatingMUL(uVar15,uVar2);
    uVar3 = PackedFloatingMUL(uVar11,uVar3);
    uVar2 = PackedFloatingMUL(uVar12,uVar2);
    param_1[1] = CONCAT44((int)((ulonglong)uVar8 >> 0x20),(int)((ulonglong)uVar1 >> 0x20));
    param_1[3] = CONCAT44((int)uVar8,(int)uVar1);
    param_1[5] = CONCAT44((int)((ulonglong)uVar2 >> 0x20),(int)((ulonglong)uVar3 >> 0x20));
    param_1[7] = CONCAT44((int)uVar2,(int)uVar3);
  }
  FastExitMediaState();
  return;
}



/* grim_jpg_huff_table_generate @ 1002ce9a */

undefined8 * grim_jpg_huff_table_generate(undefined8 *param_1,undefined4 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  undefined4 uVar4;
  undefined8 uVar3;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  undefined4 uVar11;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined4 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined4 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined4 uVar21;
  undefined8 uVar20;
  undefined4 uStack_34;
  
  uVar11 = (undefined4)((ulonglong)*param_3 >> 0x20);
  uVar2 = (undefined4)param_3[4];
  uVar16 = (undefined4)param_3[2];
  uVar12 = (undefined4)*param_3;
  uVar21 = (undefined4)((ulonglong)param_3[2] >> 0x20);
  uVar4 = (undefined4)((ulonglong)param_3[4] >> 0x20);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),CONCAT44(uVar2,uVar16));
  uVar13 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),CONCAT44(uVar4,uVar21));
  uVar14 = PackedFloatingSUB(uVar13,uVar9);
  uVar5 = (undefined4)((ulonglong)param_3[6] >> 0x20);
  uVar8 = (undefined4)param_3[6];
  uVar17 = PackedFloatingMUL(CONCAT44(uVar4,uVar5),CONCAT44(uVar16,uVar12));
  uVar20 = PackedFloatingMUL(CONCAT44(uVar21,uVar11),CONCAT44(uVar2,uVar8));
  uVar9 = PackedFloatingMUL(CONCAT44(uVar2,uVar16),CONCAT44(uVar5,uVar5));
  uVar13 = PackedFloatingMUL(CONCAT44(uVar4,uVar21),CONCAT44(uVar8,uVar8));
  uVar18 = PackedFloatingSUB(uVar17,uVar20);
  uVar17 = PackedFloatingSUBR(uVar13,uVar9);
  uVar9 = param_3[7];
  uVar13 = param_3[5];
  uVar2 = (undefined4)((ulonglong)uVar18 >> 0x20);
  uVar11 = (undefined4)((ulonglong)uVar17 >> 0x20);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar2,uVar2),uVar9);
  uVar5 = (undefined4)uVar17;
  uVar17 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),param_3[3]);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar13);
  uVar17 = PackedFloatingADD(uVar20,uVar17);
  uVar3 = PackedFloatingSUB(uVar17,uVar6);
  uVar8 = (undefined4)uVar18;
  uVar4 = (undefined4)((ulonglong)uVar14 >> 0x20);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),param_3[1]);
  uVar17 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),uVar9);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar8,uVar8),uVar13);
  uVar17 = PackedFloatingSUB(uVar17,uVar6);
  uVar18 = PackedFloatingADD(uVar17,uVar20);
  uVar20 = CONCAT44((int)uVar14,(int)uVar14);
  uVar17 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),param_3[1]);
  uVar9 = PackedFloatingMUL(uVar9,uVar20);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar8,uVar8),param_3[3]);
  uVar9 = PackedFloatingADD(uVar9,uVar17);
  uVar17 = PackedFloatingSUB(uVar9,uVar6);
  uVar9 = PackedFloatingMUL(uVar20,uVar13);
  uVar13 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),param_3[3]);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar2,uVar2),param_3[1]);
  uVar9 = PackedFloatingSUB(uVar9,uVar13);
  uVar14 = PackedFloatingADD(uVar9,uVar20);
  uVar11 = (undefined4)((ulonglong)param_3[1] >> 0x20);
  uVar2 = (undefined4)param_3[5];
  uVar16 = (undefined4)param_3[3];
  uVar12 = (undefined4)param_3[1];
  uVar21 = (undefined4)((ulonglong)param_3[3] >> 0x20);
  uVar4 = (undefined4)((ulonglong)param_3[5] >> 0x20);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),CONCAT44(uVar2,uVar16));
  uVar13 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),CONCAT44(uVar4,uVar21));
  uVar15 = PackedFloatingSUB(uVar13,uVar9);
  uVar5 = (undefined4)((ulonglong)param_3[7] >> 0x20);
  uVar8 = (undefined4)param_3[7];
  uVar20 = PackedFloatingMUL(CONCAT44(uVar4,uVar5),CONCAT44(uVar16,uVar12));
  uVar6 = PackedFloatingMUL(CONCAT44(uVar21,uVar11),CONCAT44(uVar2,uVar8));
  uVar9 = PackedFloatingMUL(CONCAT44(uVar2,uVar16),CONCAT44(uVar5,uVar5));
  uVar13 = PackedFloatingMUL(CONCAT44(uVar4,uVar21),CONCAT44(uVar8,uVar8));
  uVar19 = PackedFloatingSUB(uVar20,uVar6);
  uVar20 = PackedFloatingSUBR(uVar13,uVar9);
  uVar9 = param_3[6];
  uVar13 = param_3[4];
  uVar11 = (undefined4)((ulonglong)uVar20 >> 0x20);
  uVar5 = (undefined4)uVar20;
  uVar2 = (undefined4)((ulonglong)uVar19 >> 0x20);
  uVar10 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),param_3[2]);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar2,uVar2),uVar9);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar13);
  uVar20 = PackedFloatingADD(uVar20,uVar10);
  uVar10 = PackedFloatingSUB(uVar20,uVar6);
  uVar8 = (undefined4)uVar19;
  uVar4 = (undefined4)((ulonglong)uVar15 >> 0x20);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar11,uVar11),*param_3);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),uVar9);
  uVar19 = PackedFloatingMUL(CONCAT44(uVar8,uVar8),uVar13);
  uVar20 = PackedFloatingSUB(uVar20,uVar19);
  uVar19 = PackedFloatingADD(uVar20,uVar6);
  uVar15 = CONCAT44((int)uVar15,(int)uVar15);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),*param_3);
  uVar20 = PackedFloatingMUL(uVar9,uVar15);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar8,uVar8),param_3[2]);
  uVar20 = PackedFloatingADD(uVar20,uVar6);
  uVar20 = PackedFloatingSUB(uVar20,uVar7);
  uVar6 = PackedFloatingMUL(uVar15,uVar13);
  uVar15 = PackedFloatingMUL(CONCAT44(uVar4,uVar4),param_3[2]);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar2,uVar2),*param_3);
  uVar6 = PackedFloatingSUB(uVar6,uVar15);
  uVar6 = PackedFloatingADD(uVar6,uVar7);
  uVar9 = PackedFloatingMUL(CONCAT44((int)uVar9,(int)uVar13),0xbf8000003f800000);
  uStack_34 = (undefined4)((ulonglong)uVar19 >> 0x20);
  uVar13 = CONCAT44(uStack_34,(int)((ulonglong)uVar10 >> 0x20));
  uVar15 = PackedFloatingMUL(CONCAT44(*(undefined4 *)(param_3 + 2),(int)*param_3),0xbf8000003f800000
                            );
  uVar9 = PackedFloatingMUL(CONCAT44((int)((ulonglong)uVar6 >> 0x20),
                                     (int)((ulonglong)uVar20 >> 0x20)),uVar9);
  uVar15 = PackedFloatingMUL(uVar15,uVar13);
  uVar9 = PackedFloatingADD(uVar9,uVar15);
  uVar9 = PackedFloatingAccumulate(uVar9,uVar9);
  uVar2 = (undefined4)uVar9;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = uVar2;
  }
  uVar13 = FloatingReciprocalAprox(uVar13,uVar9);
  uVar15 = PackedFloatingCompareEQ(0,uVar9);
  uVar9 = PackedFloatingReciprocalIter1(CONCAT44(uVar2,uVar2),uVar13);
  uVar9 = PackedFloatingReciprocalIter2(uVar9,uVar13);
  uVar13 = PackedFloatingMUL(uVar9,0xbf8000003f800000);
  uVar9 = CONCAT44((int)uVar13,(int)((ulonglong)uVar13 >> 0x20));
  puVar1 = (undefined8 *)uVar15;
  if ((undefined8 *)uVar15 == (undefined8 *)0x0) {
    uVar10 = PackedFloatingMUL(uVar10,uVar9);
    uVar19 = PackedFloatingMUL(uVar19,uVar13);
    uVar3 = PackedFloatingMUL(uVar3,uVar9);
    uVar18 = PackedFloatingMUL(uVar18,uVar13);
    *param_1 = CONCAT44((int)((ulonglong)uVar19 >> 0x20),(int)((ulonglong)uVar10 >> 0x20));
    param_1[2] = CONCAT44((int)uVar19,(int)uVar10);
    param_1[4] = CONCAT44((int)((ulonglong)uVar18 >> 0x20),(int)((ulonglong)uVar3 >> 0x20));
    param_1[6] = CONCAT44((int)uVar18,(int)uVar3);
    uVar20 = PackedFloatingMUL(uVar20,uVar9);
    uVar6 = PackedFloatingMUL(uVar6,uVar13);
    uVar9 = PackedFloatingMUL(uVar17,uVar9);
    uVar13 = PackedFloatingMUL(uVar14,uVar13);
    param_1[1] = CONCAT44((int)((ulonglong)uVar6 >> 0x20),(int)((ulonglong)uVar20 >> 0x20));
    param_1[3] = CONCAT44((int)uVar6,(int)uVar20);
    param_1[5] = CONCAT44((int)((ulonglong)uVar13 >> 0x20),(int)((ulonglong)uVar9 >> 0x20));
    param_1[7] = CONCAT44((int)uVar13,(int)uVar9);
    puVar1 = param_1;
  }
  return puVar1;
}



/* grim_jpg_huff_tree_node_alloc @ 1002d550 */

undefined8 * grim_jpg_huff_tree_node_alloc(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  FastExitMediaState();
  uVar1 = (undefined4)*param_2;
  uVar4 = CONCAT44(uVar1,uVar1);
  uVar1 = (undefined4)((ulonglong)*param_2 >> 0x20);
  uVar7 = CONCAT44(uVar1,uVar1);
  uVar8 = CONCAT44(*(undefined4 *)(param_2 + 1),*(undefined4 *)(param_2 + 1));
  uVar2 = PackedFloatingMUL(uVar4,*param_3);
  uVar3 = PackedFloatingMUL(uVar7,param_3[2]);
  uVar5 = PackedFloatingMUL(uVar8,param_3[4]);
  uVar2 = PackedFloatingADD(uVar2,param_3[6]);
  uVar6 = PackedFloatingMUL(uVar4,param_3[1]);
  uVar4 = PackedFloatingADD(uVar3,uVar5);
  uVar3 = PackedFloatingMUL(uVar7,param_3[3]);
  uVar8 = PackedFloatingMUL(uVar8,param_3[5]);
  uVar7 = PackedFloatingADD(uVar6,param_3[7]);
  uVar4 = PackedFloatingADD(uVar2,uVar4);
  uVar3 = PackedFloatingADD(uVar3,uVar8);
  uVar2 = PackedFloatingADD(uVar7,uVar3);
  uVar1 = (undefined4)((ulonglong)uVar2 >> 0x20);
  uVar8 = CONCAT44(uVar1,uVar1);
  uVar7 = FloatingReciprocalAprox(uVar3,uVar8);
  uVar3 = PackedFloatingReciprocalIter1(uVar8,uVar7);
  uVar7 = PackedFloatingReciprocalIter2(uVar3,uVar7);
  uVar4 = PackedFloatingMUL(uVar4,uVar7);
  uVar2 = PackedFloatingMUL(uVar2,uVar7);
  *param_1 = uVar4;
  *(int *)(param_1 + 1) = (int)uVar2;
  FastExitMediaState();
  return param_1;
}



/* grim_jpg_huff_tree_build_codes @ 1002d5db */

undefined8 * grim_jpg_huff_tree_build_codes(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar1 = (undefined4)((ulonglong)*param_2 >> 0x20);
  uVar2 = (undefined4)((ulonglong)param_2[1] >> 0x20);
  uVar3 = (undefined4)*param_2;
  uVar6 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)param_2[1];
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar7 = PackedFloatingMUL(*param_3,uVar6);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar6,param_3[1]);
  uVar8 = PackedFloatingMUL(param_3[2],uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,param_3[3]);
  uVar7 = PackedFloatingADD(uVar8,uVar7);
  uVar8 = PackedFloatingMUL(param_3[4],uVar9);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar9,param_3[5]);
  uVar9 = PackedFloatingADD(uVar8,uVar7);
  uVar7 = PackedFloatingMUL(param_3[6],uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,param_3[7]);
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = param_2[2];
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = param_2[3];
  *param_1 = uVar7;
  uVar4 = *param_3;
  param_1[1] = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,param_3[1]);
  uVar9 = PackedFloatingMUL(param_3[2],uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,param_3[3]);
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(param_3[4],uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,param_3[5]);
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(param_3[6],uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,param_3[7]);
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = param_2[4];
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = param_2[5];
  param_1[2] = uVar7;
  uVar4 = *param_3;
  param_1[3] = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,param_3[1]);
  uVar9 = PackedFloatingMUL(param_3[2],uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,param_3[3]);
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(param_3[4],uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,param_3[5]);
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(param_3[6],uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,param_3[7]);
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = param_2[6];
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = param_2[7];
  param_1[4] = uVar7;
  uVar4 = *param_3;
  param_1[5] = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,param_3[1]);
  uVar9 = PackedFloatingMUL(param_3[2],uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,param_3[3]);
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(param_3[4],uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,param_3[5]);
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(param_3[6],uVar6);
  uVar5 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,param_3[7]);
  uVar4 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = PackedFloatingADD(uVar6,uVar5);
  param_1[6] = uVar4;
  param_1[7] = uVar5;
  FastExitMediaState();
  return param_1;
}



/* grim_jpg_huff_tree_optimize @ 1002d7a7 */

ulonglong *
grim_jpg_huff_tree_optimize(ulonglong *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
            undefined8 *param_5,undefined8 *param_6)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined4 uVar8;
  undefined8 uVar7;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  puVar1 = (undefined8 *)&local_44;
  switch(((param_6 != (undefined8 *)0x0) << 1 | param_5 != (undefined8 *)0x0) << 1 |
         param_4 != (undefined8 *)0x0) {
  case '\0':
    uStack_c = 0;
    uStack_10 = 0;
    uStack_14 = 0;
    uStack_18 = 0;
    uStack_20 = 0;
    uStack_24 = 0;
    uStack_28 = 0;
    uStack_2c = 0;
    uStack_34 = 0;
    uStack_38 = 0;
    uStack_3c = 0;
    uStack_40 = 0;
    uStack_8 = 0x3f800000;
    uStack_1c = 0x3f800000;
    uStack_30 = 0x3f800000;
    local_44 = 0x3f800000;
    break;
  case '\x01':
    puVar1 = param_4;
    break;
  case '\x02':
    puVar1 = param_5;
    break;
  case '\x03':
    FastExitMediaState();
    grim_jpg_huff_tree_build_codes((undefined8 *)&local_44,param_5,param_4);
    FastExitMediaState();
    break;
  case '\x04':
    puVar1 = param_6;
    break;
  case '\x05':
    FastExitMediaState();
    grim_jpg_huff_tree_build_codes((undefined8 *)&local_44,param_6,param_4);
    FastExitMediaState();
    break;
  case '\x06':
    FastExitMediaState();
    grim_jpg_huff_tree_build_codes((undefined8 *)&local_44,param_6,param_5);
    FastExitMediaState();
    break;
  case '\a':
    FastExitMediaState();
    grim_jpg_huff_tree_build_codes((undefined8 *)&local_44,param_6,param_5);
    grim_jpg_huff_tree_build_codes((undefined8 *)&local_44,(undefined8 *)&local_44,param_4);
    FastExitMediaState();
  }
  grim_jpg_huff_tree_node_alloc(param_1,param_2,puVar1);
  if (param_3 != (undefined8 *)0x0) {
    FastExitMediaState();
    uVar4 = param_3[2];
    uVar5 = PackedIntToFloatingDwordConv(*param_3,*param_3);
    uVar6 = PackedIntToFloatingDwordConv(param_3[1],param_3[1]);
    uVar2 = PackedFloatingADD(*param_1 ^ 0x8000000000000000,0x3f8000003f800000);
    uVar6 = PackedFloatingMUL(uVar6,0x3f0000003f000000);
    uVar8 = (undefined4)((ulonglong)uVar4 >> 0x20);
    uVar7 = PackedFloatingSUB(CONCAT44(uVar8,uVar8),uVar4);
    uVar2 = PackedFloatingMUL(uVar2,uVar6);
    uVar6 = PackedFloatingMUL((ulonglong)(uint)param_1[1],uVar7);
    uVar4 = PackedFloatingADD(uVar6,uVar4);
    uVar3 = PackedFloatingADD(uVar2,uVar5);
    *param_1 = uVar3;
    *(int *)(param_1 + 1) = (int)uVar4;
    FastExitMediaState();
  }
  return param_1;
}



/* grim_jpg_huff_tree_init @ 1002db55 */

ulonglong *
grim_jpg_huff_tree_init(ulonglong *param_1,ulonglong *param_2,undefined8 *param_3,undefined8 *param_4,
            undefined8 *param_5,undefined8 *param_6)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar6;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 in_MM5;
  undefined8 uVar7;
  undefined8 in_MM6;
  undefined8 local_44 [8];
  
  switch(((param_6 != (undefined8 *)0x0) << 1 | param_5 != (undefined8 *)0x0) << 1 |
         param_4 != (undefined8 *)0x0) {
  case '\0':
    grim_dxt_alpha_init_table(local_44);
    goto switchD_1002db8b_default;
  case '\x01':
    param_6 = param_4;
    goto LAB_1002dbcf;
  case '\x02':
    param_6 = param_5;
    goto LAB_1002dbcf;
  case '\x03':
    param_6 = param_5;
    break;
  case '\x04':
    goto LAB_1002dbcf;
  case '\x05':
    break;
  case '\x06':
    param_4 = param_5;
    break;
  case '\a':
    grim_jpg_huff_tree_build_codes(local_44,param_6,param_5);
    param_6 = local_44;
    break;
  default:
    goto switchD_1002db8b_default;
  }
  grim_jpg_huff_tree_build_codes(local_44,param_6,param_4);
  param_6 = local_44;
LAB_1002dbcf:
  grim_jpg_huff_table_build(local_44,(undefined4 *)0x0,param_6);
switchD_1002db8b_default:
  if (param_3 != (undefined8 *)0x0) {
    FastExitMediaState();
    uVar2 = PackedIntToFloatingDwordConv(*param_3,*param_3);
    uVar5 = param_3[2];
    uVar3 = PackedIntToFloatingDwordConv(param_3[1],param_3[1]);
    uVar6 = (undefined4)((ulonglong)uVar3 >> 0x20);
    uVar4 = CONCAT44(uVar6,uVar6);
    uVar7 = FloatingReciprocalAprox(in_MM5,uVar3);
    uVar4 = FloatingReciprocalAprox(uVar4,uVar4);
    uVar2 = PackedFloatingSUB(*param_2,uVar2);
    uVar4 = CONCAT44((int)uVar4,(int)uVar7);
    uVar3 = PackedFloatingReciprocalIter1(uVar3,uVar4);
    uVar3 = PackedFloatingReciprocalIter2(uVar3,uVar4);
    uVar3 = PackedFloatingMUL(uVar3,0x4000000040000000);
    uVar2 = PackedFloatingMUL(uVar2,uVar3);
    uVar6 = (undefined4)((ulonglong)uVar5 >> 0x20);
    uVar1 = PackedFloatingSUB(uVar2,0x3f8000003f800000);
    uVar2 = PackedFloatingSUB(CONCAT44(uVar6,uVar6),uVar5);
    uVar3 = FloatingReciprocalAprox(in_MM6,uVar2);
    uVar2 = PackedFloatingReciprocalIter1(uVar2,uVar3);
    uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar3);
    uVar5 = PackedFloatingSUB((ulonglong)(uint)param_2[1],uVar5);
    uVar5 = PackedFloatingMUL(uVar5,uVar2);
    *param_1 = uVar1 ^ 0x8000000000000000;
    *(int *)(param_1 + 1) = (int)uVar5;
    FastExitMediaState();
    param_2 = param_1;
  }
  grim_jpg_huff_tree_node_alloc(param_1,param_2,local_44);
  return param_1;
}



/* grim_jpg_marker_read_sos @ 1002e578 */

void grim_jpg_marker_read_sos(undefined8 *param_1,ulonglong *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 in_MM4;
  undefined8 uVar5;
  
  uVar1 = *param_2;
  uVar3 = param_2[1] & 0xffffffff;
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar3,uVar3);
  uVar2 = PackedFloatingADD(uVar2,uVar4);
  uVar2 = PackedFloatingAccumulate(uVar2,uVar2);
  uVar5 = PackedFloatingReciprocalSQRAprox(in_MM4,uVar2);
  uVar3 = PackedFloatingCompareGT(uVar2,0x80000000800000);
  uVar4 = PackedFloatingMUL(uVar5,uVar5);
  uVar2 = PackedFloatingReciprocalSQRIter1(uVar2,uVar4);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar5);
  uVar4 = PackedFloatingMUL(uVar1 & uVar3,uVar2);
  uVar2 = PackedFloatingMUL(param_2[1] & uVar3,uVar2);
  *param_1 = uVar4;
  param_1[1] = uVar2;
  FastExitMediaState();
  return;
}



/* grim_jpg_bit_read_byte @ 1002e65a */

/* [binja] int32_t sub_1002e65a(uint32_t arg1) */

int __cdecl grim_jpg_bit_read_byte(uint arg1)

{
  void *pvVar1;
  size_t in_stack_00000008;
  
  pvVar1 = malloc(in_stack_00000008);
  return (int)pvVar1;
}



/* grim_jpg_bit_skip_byte @ 1002e670 */

/* [binja] int32_t sub_1002e670(int32_t arg1) __pure */

int __cdecl grim_jpg_bit_skip_byte(int arg1)

{
  int in_stack_0000000c;
  
  return in_stack_0000000c;
}



/* grim_jpg_bit_peek_byte @ 1002e675 */

void __cdecl grim_jpg_bit_peek_byte(int *param_1)

{
  *(undefined4 *)(*param_1 + 0x14) = 0x30;
  (**(code **)*param_1)(param_1);
  return;
}



/* grim_jpg_bit_read_short @ 1002e689 */

undefined4 grim_jpg_bit_read_short(void)

{
  return 0;
}



/* grim_jpg_bit_read_n_bytes @ 1002e68c */

void grim_jpg_bit_read_n_bytes(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int unaff_ESI;
  int local_8;
  
  iVar1 = *(int *)(unaff_ESI + 0x180);
  iVar2 = *(int *)(unaff_ESI + 0x114);
  iVar3 = (*(code *)**(undefined4 **)(unaff_ESI + 4))();
  local_8 = 0;
  *(int *)(iVar1 + 0x38) = iVar3;
  *(int *)(iVar1 + 0x3c) = iVar3 + *(int *)(unaff_ESI + 0x20) * 4;
  if (0 < *(int *)(unaff_ESI + 0x20)) {
    piVar5 = (int *)(*(int *)(unaff_ESI + 0xc4) + 0xc);
    do {
      iVar4 = (piVar5[6] * *piVar5) / *(int *)(unaff_ESI + 0x114);
      iVar3 = (*(code *)**(undefined4 **)(unaff_ESI + 4))();
      piVar5 = piVar5 + 0x15;
      iVar3 = iVar3 + iVar4 * 4;
      iVar6 = local_8 * 4;
      *(int *)(iVar6 + *(int *)(iVar1 + 0x38)) = iVar3;
      local_8 = local_8 + 1;
      *(int *)(iVar6 + *(int *)(iVar1 + 0x3c)) = iVar3 + (iVar2 + 4) * iVar4 * 4;
    } while (local_8 < *(int *)(unaff_ESI + 0x20));
  }
  return;
}



/* grim_jpg_marker_scan @ 1002e734 */

void grim_jpg_marker_scan(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  int unaff_EDI;
  int local_24;
  int *local_18;
  int local_14;
  int local_10;
  undefined4 *local_c;
  
  iVar1 = *(int *)(unaff_EDI + 0x114);
  local_10 = 0;
  iVar2 = *(int *)(unaff_EDI + 0x180);
  if (0 < *(int *)(unaff_EDI + 0x20)) {
    piVar8 = (int *)(*(int *)(unaff_EDI + 0xc4) + 0xc);
    local_18 = (int *)(iVar2 + 8);
    do {
      iVar6 = (piVar8[6] * *piVar8) / *(int *)(unaff_EDI + 0x114);
      puVar3 = *(undefined4 **)(local_10 * 4 + *(int *)(iVar2 + 0x38));
      puVar9 = *(undefined4 **)(local_10 * 4 + *(int *)(iVar2 + 0x3c));
      iVar4 = *local_18;
      local_14 = (iVar1 + 2) * iVar6;
      if (0 < local_14) {
        puVar7 = puVar9;
        do {
          uVar5 = *(undefined4 *)((iVar4 - (int)puVar9) + (int)puVar7);
          *puVar7 = uVar5;
          *(undefined4 *)(((int)puVar3 - (int)puVar9) + (int)puVar7) = uVar5;
          puVar7 = puVar7 + 1;
          local_14 = local_14 + -1;
        } while (local_14 != 0);
      }
      if (0 < iVar6 * 2) {
        puVar7 = (undefined4 *)(iVar4 + (iVar1 + -2) * iVar6 * 4);
        local_24 = iVar6 * 2;
        local_c = puVar9 + iVar6 * iVar1;
        do {
          *(undefined4 *)(((int)puVar9 - iVar4) + (int)puVar7) =
               *(undefined4 *)((int)local_c + (iVar4 - (int)puVar9));
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
          local_24 = local_24 + -1;
          *local_c = uVar5;
          local_c = local_c + 1;
        } while (local_24 != 0);
      }
      if (0 < iVar6) {
        puVar9 = puVar3 + -iVar6;
        do {
          *puVar9 = *puVar3;
          puVar9 = puVar9 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      local_10 = local_10 + 1;
      local_18 = local_18 + 1;
      piVar8 = piVar8 + 0x15;
    } while (local_10 < *(int *)(unaff_EDI + 0x20));
  }
  return;
}



/* grim_jpg_marker_validate_sof @ 1002e865 */

void grim_jpg_marker_validate_sof(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  int unaff_EDI;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  iVar1 = *(int *)(unaff_EDI + 0x180);
  local_c = 0;
  iVar2 = *(int *)(unaff_EDI + 0x114);
  if (0 < *(int *)(unaff_EDI + 0x20)) {
    piVar6 = (int *)(*(int *)(unaff_EDI + 0xc4) + 0xc);
    do {
      local_10 = (piVar6[6] * *piVar6) / *(int *)(unaff_EDI + 0x114);
      local_8 = *(undefined4 **)(local_c * 4 + *(int *)(iVar1 + 0x3c));
      if (0 < local_10) {
        puVar7 = local_8 + (iVar2 + 2) * local_10;
        puVar5 = local_8 + -local_10;
        puVar4 = local_8 + (iVar2 + 1) * local_10;
        iVar8 = *(int *)(local_c * 4 + *(int *)(iVar1 + 0x38)) - (int)local_8;
        do {
          *(undefined4 *)(iVar8 + (int)puVar5) = *(undefined4 *)(iVar8 + (int)puVar4);
          *puVar5 = *puVar4;
          *(undefined4 *)(iVar8 + (int)puVar7) = *(undefined4 *)(iVar8 + (int)local_8);
          uVar3 = *local_8;
          local_8 = local_8 + 1;
          *puVar7 = uVar3;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
          puVar7 = puVar7 + 1;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      local_c = local_c + 1;
      piVar6 = piVar6 + 0x15;
    } while (local_c < *(int *)(unaff_EDI + 0x20));
  }
  return;
}



/* grim_jpg_marker_validate_sos @ 1002e939 */

void grim_jpg_marker_validate_sos(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int unaff_ESI;
  int *piVar5;
  int local_10;
  uint local_c;
  int local_8;
  
  local_8 = 0;
  iVar2 = *(int *)(unaff_ESI + 0x180);
  if (0 < *(int *)(unaff_ESI + 0x20)) {
    piVar5 = (int *)(*(int *)(unaff_ESI + 0xc4) + 0xc);
    do {
      uVar3 = piVar5[6] * *piVar5;
      local_10 = (int)uVar3 / *(int *)(unaff_ESI + 0x114);
      local_c = (uint)piVar5[8] % uVar3;
      if ((uint)piVar5[8] % uVar3 == 0) {
        local_c = uVar3;
      }
      if (local_8 == 0) {
        *(int *)(iVar2 + 0x48) = (int)(local_c - 1) / local_10 + 1;
      }
      local_10 = local_10 * 2;
      if (0 < local_10) {
        puVar1 = (undefined4 *)
                 (*(int *)(*(int *)(iVar2 + 0x38 + *(int *)(iVar2 + 0x40) * 4) + local_8 * 4) +
                 local_c * 4);
        puVar4 = puVar1;
        do {
          *puVar4 = puVar1[-1];
          puVar4 = puVar4 + 1;
          local_10 = local_10 + -1;
        } while (local_10 != 0);
      }
      local_8 = local_8 + 1;
      piVar5 = piVar5 + 0x15;
    } while (local_8 < *(int *)(unaff_ESI + 0x20));
  }
  return;
}



/* grim_jpg_marker_read_app0 @ 1002e9cf */

void __cdecl grim_jpg_marker_read_app0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_1 + 0x180);
  if (*(char *)(iVar2 + 0x30) == '\0') {
    iVar4 = (**(code **)(*(int *)(param_1 + 0x184) + 0xc))(param_1,iVar2 + 8);
    if (iVar4 == 0) {
      return;
    }
    *(undefined1 *)(iVar2 + 0x30) = 1;
  }
  uVar3 = *(uint *)(param_1 + 0x114);
  puVar1 = (uint *)(iVar2 + 0x34);
  (**(code **)(*(int *)(param_1 + 0x188) + 4))
            (param_1,iVar2 + 8,puVar1,uVar3,param_2,param_3,param_4);
  if (uVar3 <= *puVar1) {
    *(undefined1 *)(iVar2 + 0x30) = 0;
    *puVar1 = 0;
  }
  return;
}



/* grim_jpg_marker_read_sof @ 1002ea37 */

void __cdecl grim_jpg_marker_read_sof(int param_1,undefined4 param_2,uint *param_3,uint param_4)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x180);
  if (*(char *)(iVar2 + 0x30) == '\0') {
    iVar3 = (**(code **)(*(int *)(param_1 + 0x184) + 0xc))
                      (param_1,*(undefined4 *)(iVar2 + 0x38 + *(int *)(iVar2 + 0x40) * 4));
    if (iVar3 == 0) {
      return;
    }
    *(int *)(iVar2 + 0x4c) = *(int *)(iVar2 + 0x4c) + 1;
    *(undefined1 *)(iVar2 + 0x30) = 1;
  }
  iVar3 = *(int *)(iVar2 + 0x44);
  if (iVar3 != 0) {
    if (iVar3 == 1) goto LAB_1002eae4;
    if (iVar3 != 2) {
      return;
    }
    (**(code **)(*(int *)(param_1 + 0x188) + 4))
              (param_1,*(undefined4 *)(iVar2 + 0x38 + *(int *)(iVar2 + 0x40) * 4),
               (uint *)(iVar2 + 0x34),*(undefined4 *)(iVar2 + 0x48),param_2,param_3,param_4);
    if (*(uint *)(iVar2 + 0x34) < *(uint *)(iVar2 + 0x48)) {
      return;
    }
    *(undefined4 *)(iVar2 + 0x44) = 0;
    if (param_4 <= *param_3) {
      return;
    }
  }
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(int *)(iVar2 + 0x48) = *(int *)(param_1 + 0x114) + -1;
  if (*(int *)(iVar2 + 0x4c) == *(int *)(param_1 + 0x118)) {
    grim_jpg_marker_validate_sos();
  }
  *(undefined4 *)(iVar2 + 0x44) = 1;
LAB_1002eae4:
  puVar1 = (uint *)(iVar2 + 0x34);
  (**(code **)(*(int *)(param_1 + 0x188) + 4))
            (param_1,*(undefined4 *)(iVar2 + 0x38 + *(int *)(iVar2 + 0x40) * 4),puVar1,
             *(undefined4 *)(iVar2 + 0x48),param_2,param_3,param_4);
  if (*(uint *)(iVar2 + 0x48) <= *puVar1) {
    if (*(int *)(iVar2 + 0x4c) == 1) {
      grim_jpg_marker_validate_sof();
    }
    *(uint *)(iVar2 + 0x40) = *(uint *)(iVar2 + 0x40) ^ 1;
    *(undefined1 *)(iVar2 + 0x30) = 0;
    *puVar1 = *(int *)(param_1 + 0x114) + 1;
    *(int *)(iVar2 + 0x48) = *(int *)(param_1 + 0x114) + 2;
    *(undefined4 *)(iVar2 + 0x44) = 2;
  }
  return;
}



/* grim_jpg_marker_read_tables @ 1002ebca */

void __cdecl grim_jpg_marker_read_tables(int *param_1,char param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  
  piVar1 = param_1;
  puVar2 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x50);
  param_1[0x60] = (int)puVar2;
  *puVar2 = &LAB_1002eb62;
  if (param_2 != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 4;
    (**(code **)*param_1)(param_1);
  }
  if (*(char *)(param_1[0x67] + 8) == '\0') {
    iVar4 = param_1[0x45];
  }
  else {
    if (param_1[0x45] < 2) {
      *(undefined4 *)(*param_1 + 0x14) = 0x2e;
      (**(code **)*param_1)(param_1);
    }
    grim_jpg_bit_read_n_bytes();
    iVar4 = param_1[0x45] + 2;
  }
  param_1 = (int *)0x0;
  if (0 < piVar1[8]) {
    piVar5 = (int *)(piVar1[0x31] + 0x24);
    puVar2 = puVar2 + 2;
    do {
      uVar3 = (**(code **)(piVar1[1] + 8))
                        (piVar1,1,piVar5[-2] * *piVar5,
                         ((piVar5[-6] * *piVar5) / piVar1[0x45]) * iVar4);
      param_1 = (int *)((int)param_1 + 1);
      *puVar2 = uVar3;
      puVar2 = puVar2 + 1;
      piVar5 = piVar5 + 0x15;
    } while ((int)param_1 < piVar1[8]);
  }
  return;
}



/* grim_jpg_segment_length_validate @ 1002ec9d */

/* [binja] void* __fastcall sub_1002ec9d(void* arg1) */

void * __fastcall grim_jpg_segment_length_validate(void *arg1)

{
  void *pvVar1;
  undefined4 uVar2;
  
  pvVar1 = *(void **)((int)arg1 + 0x184);
  if (*(int *)((int)arg1 + 0x120) < 2) {
    if (*(uint *)((int)arg1 + 0x80) < *(int *)((int)arg1 + 0x118) - 1U) {
      uVar2 = *(undefined4 *)(*(int *)((int)arg1 + 0x124) + 0xc);
    }
    else {
      uVar2 = *(undefined4 *)(*(int *)((int)arg1 + 0x124) + 0x48);
    }
    *(undefined4 *)((int)pvVar1 + 0x1c) = uVar2;
  }
  else {
    *(undefined4 *)((int)pvVar1 + 0x1c) = 1;
  }
  *(undefined4 *)((int)pvVar1 + 0x14) = 0;
  *(undefined4 *)((int)pvVar1 + 0x18) = 0;
  return pvVar1;
}



/* grim_jpg_marker_read_dht_table @ 1002ecec */

undefined4 __cdecl grim_jpg_marker_read_dht_table(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  code *pcVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  undefined4 uVar13;
  int local_30;
  int *local_28;
  int local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  int local_c;
  
  iVar2 = *(int *)(param_1 + 0x118);
  iVar3 = *(int *)(param_1 + 0x184);
  uVar12 = *(int *)(param_1 + 0x134) - 1;
  iVar10 = *(int *)(iVar3 + 0x18);
  do {
    if (*(int *)(iVar3 + 0x1c) <= iVar10) {
      *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 1;
      puVar1 = (uint *)(param_1 + 0x80);
      *puVar1 = *puVar1 + 1;
      if (*puVar1 < *(uint *)(param_1 + 0x118)) {
        grim_jpg_segment_length_validate((void *)param_1);
        uVar13 = 3;
      }
      else {
        (**(code **)(*(int *)(param_1 + 0x18c) + 0xc))(param_1);
        uVar13 = 4;
      }
      return uVar13;
    }
    for (uVar4 = *(uint *)(iVar3 + 0x14); uVar4 <= uVar12; uVar4 = uVar4 + 1) {
      memzero(*(void **)(iVar3 + 0x20),*(int *)(param_1 + 0x13c) << 7);
      cVar8 = (**(code **)(*(int *)(param_1 + 0x194) + 4))(param_1,iVar3 + 0x20);
      if (cVar8 == '\0') {
        *(int *)(iVar3 + 0x18) = iVar10;
        *(uint *)(iVar3 + 0x14) = uVar4;
        return 0;
      }
      iVar9 = 0;
      local_1c = 0;
      local_10 = 0;
      if (0 < *(int *)(param_1 + 0x120)) {
        local_28 = (int *)(param_1 + 0x124);
        do {
          iVar5 = *local_28;
          if (*(char *)(iVar5 + 0x30) == '\0') {
            iVar9 = iVar9 + *(int *)(iVar5 + 0x3c);
            local_1c = iVar9;
          }
          else {
            pcVar6 = *(code **)(*(int *)(param_1 + 0x198) + 4 + *(int *)(iVar5 + 4) * 4);
            if (uVar4 < uVar12) {
              iVar11 = *(int *)(iVar5 + 0x34);
            }
            else {
              iVar11 = *(int *)(iVar5 + 0x44);
            }
            iVar7 = *(int *)(iVar5 + 0x40);
            local_c = 0;
            local_20 = *(int *)(param_2 + local_10 * 4) + *(int *)(iVar5 + 0x24) * iVar10 * 4;
            if (0 < *(int *)(iVar5 + 0x38)) {
              do {
                if (((*(uint *)(param_1 + 0x80) < iVar2 - 1U) ||
                    (local_c + iVar10 < *(int *)(iVar5 + 0x48))) && (0 < iVar11)) {
                  local_18 = (undefined4 *)(iVar3 + 0x20 + iVar9 * 4);
                  local_30 = iVar11;
                  local_14 = iVar7 * uVar4;
                  do {
                    (*pcVar6)(param_1,iVar5,*local_18,local_20,local_14);
                    local_14 = local_14 + *(int *)(iVar5 + 0x24);
                    local_18 = local_18 + 1;
                    local_30 = local_30 + -1;
                    iVar9 = local_1c;
                  } while (local_30 != 0);
                }
                iVar9 = iVar9 + *(int *)(iVar5 + 0x34);
                local_c = local_c + 1;
                local_20 = local_20 + *(int *)(iVar5 + 0x24) * 4;
                local_1c = iVar9;
              } while (local_c < *(int *)(iVar5 + 0x38));
            }
          }
          local_10 = local_10 + 1;
          local_28 = local_28 + 1;
        } while (local_10 < *(int *)(param_1 + 0x120));
      }
    }
    *(undefined4 *)(iVar3 + 0x14) = 0;
    iVar10 = iVar10 + 1;
  } while( true );
}



/* grim_jpg_marker_read_dqt_table @ 1002eec9 */

undefined4 __cdecl grim_jpg_marker_read_dqt_table(int param_1)

{
  uint *puVar1;
  int iVar2;
  int arg1;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int aiStack_38 [4];
  int *local_28;
  int local_24;
  uint local_20;
  int *local_1c;
  int local_18;
  int *local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  arg1 = param_1;
  param_1 = 0;
  iVar2 = *(int *)(arg1 + 0x184);
  if (0 < *(int *)(arg1 + 0x120)) {
    local_8 = (int *)(arg1 + 0x124);
    do {
      iVar4 = *(int *)(*local_8 + 0xc);
      iVar4 = (**(code **)(*(int *)(arg1 + 4) + 0x20))
                        (arg1,*(undefined4 *)(iVar2 + 0x48 + *(int *)(*local_8 + 4) * 4),
                         *(int *)(arg1 + 0x80) * iVar4,iVar4,1);
      local_8 = local_8 + 1;
      aiStack_38[param_1] = iVar4;
      param_1 = param_1 + 1;
    } while (param_1 < *(int *)(arg1 + 0x120));
  }
  local_8 = *(int **)(iVar2 + 0x18);
  do {
    if (*(int *)(iVar2 + 0x1c) <= (int)local_8) {
      puVar1 = (uint *)(arg1 + 0x80);
      *puVar1 = *puVar1 + 1;
      if (*puVar1 < *(uint *)(arg1 + 0x118)) {
        grim_jpg_segment_length_validate((void *)arg1);
        uVar8 = 3;
      }
      else {
        (**(code **)(*(int *)(arg1 + 0x18c) + 0xc))(arg1);
        uVar8 = 4;
      }
      return uVar8;
    }
    uVar7 = *(uint *)(iVar2 + 0x14);
    local_20 = uVar7;
    if (uVar7 < *(uint *)(arg1 + 0x134)) {
      do {
        local_c = 0;
        param_1 = 0;
        if (0 < *(int *)(arg1 + 0x120)) {
          local_1c = (int *)(arg1 + 0x124);
          do {
            iVar4 = *local_1c;
            iVar6 = *(int *)(iVar4 + 0x34);
            local_18 = 0;
            if (0 < *(int *)(iVar4 + 0x38)) {
              local_24 = iVar6 * uVar7 * 0x80;
              local_14 = (int *)(aiStack_38[param_1] + (int)local_8 * 4);
              do {
                iVar5 = *local_14 + local_24;
                local_10 = 0;
                if (0 < iVar6) {
                  local_28 = (int *)(iVar2 + 0x20 + local_c * 4);
                  do {
                    local_c = local_c + 1;
                    *local_28 = iVar5;
                    local_28 = local_28 + 1;
                    iVar5 = iVar5 + 0x80;
                    local_10 = local_10 + 1;
                    iVar6 = *(int *)(iVar4 + 0x34);
                  } while (local_10 < iVar6);
                }
                local_18 = local_18 + 1;
                local_14 = local_14 + 1;
              } while (local_18 < *(int *)(iVar4 + 0x38));
            }
            param_1 = param_1 + 1;
            local_1c = local_1c + 1;
          } while (param_1 < *(int *)(arg1 + 0x120));
        }
        local_20 = uVar7;
        cVar3 = (**(code **)(*(int *)(arg1 + 0x194) + 4))(arg1,iVar2 + 0x20);
        if (cVar3 == '\0') {
          *(int **)(iVar2 + 0x18) = local_8;
          *(uint *)(iVar2 + 0x14) = uVar7;
          return 0;
        }
        uVar7 = uVar7 + 1;
        local_20 = uVar7;
      } while (uVar7 < *(uint *)(arg1 + 0x134));
    }
    *(undefined4 *)(iVar2 + 0x14) = 0;
    local_8 = (int *)((int)local_8 + 1);
  } while( true );
}



/* grim_jpg_marker_read_dri_value @ 1002f068 */

int __cdecl grim_jpg_marker_read_dri_value(uint param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  uVar4 = param_1;
  iVar2 = *(int *)(param_1 + 0x118);
  iVar6 = *(int *)(param_1 + 0x184);
  while ((*(int *)(param_1 + 0x7c) < *(int *)(param_1 + 0x84) ||
         ((*(int *)(param_1 + 0x7c) == *(int *)(param_1 + 0x84) &&
          (*(uint *)(param_1 + 0x80) <= *(uint *)(param_1 + 0x88)))))) {
    iVar5 = (*(code *)**(undefined4 **)(param_1 + 0x18c))(param_1);
    if (iVar5 == 0) {
      return 0;
    }
  }
  local_8 = 0;
  iVar5 = *(int *)(param_1 + 0xc4);
  if (0 < *(int *)(param_1 + 0x20)) {
    local_18 = (undefined4 *)(iVar6 + 0x48);
    do {
      if (*(char *)(iVar5 + 0x30) != '\0') {
        iVar6 = (**(code **)(*(int *)(uVar4 + 4) + 0x20))
                          (uVar4,*local_18,*(int *)(uVar4 + 0x88) * *(int *)(iVar5 + 0xc),
                           *(int *)(iVar5 + 0xc),0);
        if (*(uint *)(uVar4 + 0x88) < iVar2 - 1U) {
          param_1 = *(uint *)(iVar5 + 0xc);
        }
        else {
          param_1 = *(uint *)(iVar5 + 0x20) % *(uint *)(iVar5 + 0xc);
          if (param_1 == 0) {
            param_1 = *(uint *)(iVar5 + 0xc);
          }
        }
        pcVar3 = *(code **)(*(int *)(uVar4 + 0x198) + 4 + local_8 * 4);
        local_14 = *(int *)(local_8 * 4 + param_2);
        local_1c = 0;
        if (0 < (int)param_1) {
          uVar7 = *(uint *)(iVar5 + 0x1c);
          do {
            local_c = *(int *)(iVar6 + local_1c * 4);
            iVar8 = 0;
            local_10 = 0;
            if (uVar7 != 0) {
              do {
                (*pcVar3)(uVar4,iVar5,local_c,local_14,iVar8);
                local_c = local_c + 0x80;
                iVar8 = iVar8 + *(int *)(iVar5 + 0x24);
                uVar7 = *(uint *)(iVar5 + 0x1c);
                local_10 = local_10 + 1;
              } while (local_10 < uVar7);
            }
            local_14 = local_14 + *(int *)(iVar5 + 0x24) * 4;
            local_1c = local_1c + 1;
          } while (local_1c < (int)param_1);
        }
      }
      local_8 = local_8 + 1;
      local_18 = local_18 + 1;
      iVar5 = iVar5 + 0x54;
    } while (local_8 < *(int *)(uVar4 + 0x20));
  }
  puVar1 = (uint *)(uVar4 + 0x88);
  *puVar1 = *puVar1 + 1;
  return 4 - (uint)(*puVar1 < *(uint *)(uVar4 + 0x118));
}



/* grim_jpg_marker_read_sos_data @ 1002f1ce */

uint grim_jpg_marker_read_sos_data(void)

{
  int *in_EAX;
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar5;
  int unaff_ESI;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_5;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(unaff_ESI + 0x184);
  local_5 = 0;
  if ((*(char *)(unaff_ESI + 200) == '\0') || (*(int *)(unaff_ESI + 0x8c) == 0)) {
LAB_1002f2ab:
    uVar3 = (uint)in_EAX & 0xffffff00;
  }
  else {
    if (*(int *)(iVar2 + 0x70) == 0) {
      uVar1 = (*(code *)**(undefined4 **)(unaff_ESI + 4))();
      *(undefined4 *)(iVar2 + 0x70) = uVar1;
    }
    local_c = *(int *)(iVar2 + 0x70);
    puVar4 = *(undefined4 **)(unaff_ESI + 0xc4);
    local_14 = 0;
    if (0 < *(int *)(unaff_ESI + 0x20)) {
      puVar4 = puVar4 + 0x13;
      local_10 = 0;
      do {
        in_EAX = (int *)*puVar4;
        if (((((in_EAX == (int *)0x0) || ((short)*in_EAX == 0)) ||
             (*(short *)((int)in_EAX + 2) == 0)) ||
            (((short)in_EAX[4] == 0 || ((short)in_EAX[8] == 0)))) ||
           ((*(short *)((int)in_EAX + 0x12) == 0 ||
            (((short)in_EAX[1] == 0 ||
             (in_EAX = (int *)(*(int *)(unaff_ESI + 0x8c) + local_10), *in_EAX < 0))))))
        goto LAB_1002f2ab;
        iVar5 = local_c - (int)in_EAX;
        iVar2 = 5;
        do {
          in_EAX = in_EAX + 1;
          *(int *)(iVar5 + (int)in_EAX) = *in_EAX;
          if (*in_EAX != 0) {
            local_5 = 1;
          }
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
        local_c = local_c + 0x18;
        local_14 = local_14 + 1;
        local_10 = local_10 + 0x100;
        puVar4 = puVar4 + 0x15;
      } while (local_14 < *(int *)(unaff_ESI + 0x20));
    }
    uVar3 = CONCAT31((int3)((uint)puVar4 >> 8),local_5);
  }
  return uVar3;
}



/* grim_jpg_marker_read_combined @ 1002f7ce */

void __cdecl grim_jpg_marker_read_combined(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 0x184);
  if (*(int *)(iVar1 + 0x10) != 0) {
    if (*(char *)(param_1 + 0x49) != '\0') {
      uVar2 = grim_jpg_marker_read_sos_data();
      if ((char)uVar2 != '\0') {
        *(undefined1 **)(iVar1 + 0xc) = &LAB_1002f2b1;
        goto LAB_1002f7ff;
      }
    }
    *(code **)(iVar1 + 0xc) = grim_jpg_marker_read_dri_value;
  }
LAB_1002f7ff:
  *(undefined4 *)(param_1 + 0x88) = 0;
  return;
}



/* grim_jpg_huff_decoder_setup @ 1002f809 */

void __cdecl grim_jpg_huff_decoder_setup(int param_1,char param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  
  iVar9 = param_1;
  puVar3 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x74);
  *(undefined4 **)(param_1 + 0x184) = puVar3;
  *puVar3 = &LAB_1002ecdc;
  puVar3[2] = grim_jpg_marker_read_combined;
  puVar3[0x1c] = 0;
  if (param_2 == '\0') {
    iVar4 = (**(code **)(*(int *)(param_1 + 4) + 4))(param_1,1,0x500);
    piVar8 = puVar3 + 8;
    iVar9 = 10;
    do {
      *piVar8 = iVar4;
      piVar8 = piVar8 + 1;
      iVar4 = iVar4 + 0x80;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    puVar3[1] = &LAB_1002eec6;
    puVar3[3] = grim_jpg_marker_read_dht_table;
    puVar3[4] = 0;
  }
  else {
    piVar8 = (int *)(param_1 + 0x20);
    piVar1 = (int *)(param_1 + 0xc4);
    param_1 = 0;
    if (0 < *piVar8) {
      piVar8 = (int *)(*piVar1 + 0xc);
      _param_2 = puVar3 + 0x12;
      do {
        iVar4 = *piVar8;
        iVar7 = iVar4;
        if (*(char *)(iVar9 + 200) != '\0') {
          iVar7 = iVar4 * 3;
        }
        iVar2 = *(int *)(iVar9 + 4);
        iVar4 = grim_fpu_set_precision(piVar8[5],iVar4);
        iVar5 = grim_fpu_set_precision(piVar8[4],piVar8[-1]);
        uVar6 = (**(code **)(iVar2 + 0x14))(iVar9,1,1,iVar5,iVar4,iVar7);
        param_1 = param_1 + 1;
        *_param_2 = uVar6;
        piVar8 = piVar8 + 0x15;
        _param_2 = _param_2 + 1;
      } while (param_1 < *(int *)(iVar9 + 0x20));
    }
    puVar3[1] = grim_jpg_marker_read_dqt_table;
    puVar3[3] = grim_jpg_marker_read_dri_value;
    puVar3[4] = puVar3 + 0x12;
  }
  return;
}



/* grim_jpg_make_derived_tbl @ 1002f901 */

void __cdecl grim_jpg_make_derived_tbl(int param_1,int param_2,int *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  int iVar11;
  undefined1 *puVar12;
  int aiStack_520 [257];
  char local_11c [260];
  byte *local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  if (*param_3 == 0) {
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x5d4);
    *param_3 = iVar2;
  }
  iVar2 = *param_3;
  iVar3 = 0;
  *(int *)(iVar2 + 0xd0) = param_2;
  local_8 = 0;
  param_3 = (int *)0x1;
  do {
    uVar7 = (uint)*(byte *)((int)param_3 + param_2);
    local_c = uVar7;
    if (uVar7 != 0) {
      pcVar4 = local_11c + iVar3;
      for (uVar8 = (uint)(*(byte *)((int)param_3 + param_2) >> 2); uVar8 != 0; uVar8 = uVar8 - 1) {
        *(uint *)pcVar4 =
             CONCAT22(CONCAT11((char)param_3,(char)param_3),CONCAT11((char)param_3,(char)param_3));
        pcVar4 = pcVar4 + 4;
      }
      for (uVar8 = uVar7 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
        *pcVar4 = (char)param_3;
        pcVar4 = pcVar4 + 1;
      }
      iVar3 = local_8 + uVar7;
      local_8 = iVar3;
    }
    param_3 = (int *)((int)param_3 + 1);
  } while ((int)param_3 < 0x11);
  local_11c[iVar3] = '\0';
  iVar11 = (int)local_11c[0];
  iVar3 = 0;
  iVar9 = 0;
  if (local_11c[0] != '\0') {
    pcVar4 = local_11c;
    do {
      cVar1 = *pcVar4;
      while (cVar1 == iVar11) {
        cVar1 = local_11c[iVar3 + 1];
        aiStack_520[iVar3] = iVar9;
        iVar3 = iVar3 + 1;
        iVar9 = iVar9 + 1;
      }
      iVar9 = iVar9 << 1;
      pcVar4 = local_11c + iVar3;
      iVar11 = iVar11 + 1;
    } while (*pcVar4 != '\0');
  }
  iVar3 = 0;
  iVar9 = 1;
  piVar5 = (int *)(iVar2 + 0x48);
  do {
    if (*(char *)(iVar9 + param_2) == '\0') {
      *piVar5 = -1;
    }
    else {
      iVar11 = aiStack_520[iVar3];
      piVar5[0x12] = iVar3;
      piVar5[-0x11] = iVar11;
      iVar3 = iVar3 + (uint)*(byte *)(iVar9 + param_2);
      *piVar5 = aiStack_520[iVar3 + -1];
    }
    iVar9 = iVar9 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar9 < 0x11);
  local_8 = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0xfffff;
  puVar6 = (undefined4 *)(iVar2 + 0xd4);
  for (iVar3 = 0x100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  param_3 = (int *)0x1;
  local_10 = 7;
  do {
    local_18 = (byte *)((int)param_3 + param_2);
    local_14 = 1;
    if (*local_18 != 0) {
      iVar3 = 1 << ((byte)local_10 & 0x1f);
      puVar10 = (undefined1 *)(local_8 + 0x11 + param_2);
      do {
        iVar9 = aiStack_520[local_8] << ((byte)local_10 & 0x1f);
        if (0 < iVar3) {
          puVar12 = (undefined1 *)(iVar9 + 0x4d4 + iVar2);
          puVar6 = (undefined4 *)(iVar2 + 0xd4 + iVar9 * 4);
          local_c = iVar3;
          do {
            *puVar6 = param_3;
            puVar6 = puVar6 + 1;
            *puVar12 = *puVar10;
            puVar12 = puVar12 + 1;
            local_c = local_c + -1;
          } while (local_c != 0);
        }
        local_14 = local_14 + 1;
        local_8 = local_8 + 1;
        puVar10 = puVar10 + 1;
      } while (local_14 <= (int)(uint)*local_18);
    }
    param_3 = (int *)((int)param_3 + 1);
    local_10 = local_10 + -1;
  } while (-1 < local_10);
  return;
}



/* grim_jpg_fill_bit_buffer @ 1002faab */

undefined4 __cdecl grim_jpg_fill_bit_buffer(undefined4 *param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = param_1[1];
  pbVar3 = (byte *)*param_1;
  for (; param_3 < 0x19; param_3 = param_3 + 8) {
    if (param_1[2] == 0) {
      if (iVar2 == 0) {
        uVar1 = (**(code **)(*(int *)(param_1[7] + 0x14) + 0xc))(param_1[7]);
        if ((char)uVar1 == '\0') {
LAB_1002fb91:
          return uVar1 & 0xffffff00;
        }
        pbVar3 = (byte *)**(undefined4 **)(param_1[7] + 0x14);
        iVar2 = (*(undefined4 **)(param_1[7] + 0x14))[1];
      }
      uVar1 = (uint)*pbVar3;
      iVar2 = iVar2 + -1;
      pbVar3 = pbVar3 + 1;
      if (uVar1 == 0xff) {
        do {
          if (iVar2 == 0) {
            uVar1 = (**(code **)(*(int *)(param_1[7] + 0x14) + 0xc))(param_1[7]);
            if ((char)uVar1 == '\0') goto LAB_1002fb91;
            pbVar3 = (byte *)**(undefined4 **)(param_1[7] + 0x14);
            iVar2 = (*(undefined4 **)(param_1[7] + 0x14))[1];
          }
          uVar1 = (uint)*pbVar3;
          iVar2 = iVar2 + -1;
          pbVar3 = pbVar3 + 1;
        } while (uVar1 == 0xff);
        if (uVar1 != 0) {
          param_1[2] = uVar1;
          goto LAB_1002fb2f;
        }
        uVar1 = 0xff;
      }
    }
    else {
LAB_1002fb2f:
      if (param_4 <= param_3) break;
      if (*(char *)param_1[8] == '\0') {
        *(undefined4 *)(*(int *)param_1[7] + 0x14) = 0x71;
        (**(code **)(*(int *)param_1[7] + 4))((int *)param_1[7],0xffffffff);
        *(undefined1 *)param_1[8] = 1;
      }
      uVar1 = 0;
    }
    param_2 = param_2 << 8 | uVar1;
  }
  param_1[3] = param_2;
  param_1[6] = param_3;
  *param_1 = pbVar3;
  param_1[1] = iVar2;
  return CONCAT31((int3)((uint)param_3 >> 8),1);
}



/* grim_jpg_decode_symbol @ 1002fb95 */

uint __cdecl grim_jpg_decode_symbol(undefined4 *param_1,uint param_2,int param_3,int param_4,int *param_5)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *local_8;
  
  local_8 = param_5;
  if (param_3 < (int)param_5) {
    uVar1 = grim_jpg_fill_bit_buffer(param_1,param_2,param_3,(int)param_5);
    if ((char)uVar1 == '\0') {
      return 0xffffffff;
    }
    param_2 = param_1[3];
    param_3 = param_1[6];
  }
  iVar2 = param_3 - (int)param_5;
  uVar3 = (int)param_2 >> ((byte)iVar2 & 0x1f) & (1 << ((byte)param_5 & 0x1f)) - 1U;
  param_5 = (int *)(param_4 + 0x44 + (int)param_5 * 4);
  if (*param_5 < (int)uVar3) {
    do {
      if (iVar2 < 1) {
        uVar1 = grim_jpg_fill_bit_buffer(param_1,param_2,iVar2,1);
        if ((char)uVar1 == '\0') {
          return 0xffffffff;
        }
        param_2 = param_1[3];
        iVar2 = param_1[6];
      }
      param_5 = param_5 + 1;
      iVar2 = iVar2 + -1;
      uVar3 = uVar3 << 1 | (int)param_2 >> ((byte)iVar2 & 0x1f) & 1U;
      local_8 = (int *)((int)local_8 + 1);
    } while (*param_5 < (int)uVar3);
  }
  param_1[6] = iVar2;
  param_1[3] = param_2;
  if ((int)local_8 < 0x11) {
    uVar3 = (uint)*(byte *)((*(int *)(param_4 + 0x8c + (int)local_8 * 4) -
                            *(int *)(param_4 + (int)local_8 * 4)) + *(int *)(param_4 + 0xd0) + 0x11
                           + uVar3);
  }
  else {
    *(undefined4 *)(*(int *)param_1[7] + 0x14) = 0x72;
    (**(code **)(*(int *)param_1[7] + 4))((int *)param_1[7],0xffffffff);
    uVar3 = 0;
  }
  return uVar3;
}



/* grim_jpg_restart_mcu @ 1002fc7f */

undefined4 __cdecl grim_jpg_restart_mcu(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar2 = *(int *)(param_1 + 0x194);
  piVar1 = (int *)(*(int *)(param_1 + 400) + 0x58);
  *piVar1 = *piVar1 + *(int *)(iVar2 + 0x14) / 8;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  uVar3 = (**(code **)(*(int *)(param_1 + 400) + 8))(param_1);
  if ((char)uVar3 != '\0') {
    iVar5 = 0;
    if (0 < *(int *)(param_1 + 0x120)) {
      puVar4 = (undefined4 *)(iVar2 + 0x20);
      do {
        *puVar4 = 0;
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar5 < *(int *)(param_1 + 0x120));
    }
    uVar3 = *(undefined4 *)(param_1 + 0xfc);
    *(undefined4 *)(iVar2 + 0x30) = uVar3;
    *(undefined1 *)(iVar2 + 0x18) = 0;
    uVar3 = CONCAT31((int3)((uint)uVar3 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_decode_mcu_ac @ 1002fcdd */

undefined4 __cdecl grim_jpg_decode_mcu_ac(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  uint local_4c;
  int local_40;
  int local_3c;
  int local_38;
  int local_30 [4];
  uint local_20;
  undefined2 *local_1c;
  int local_18;
  uint *local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  iVar1 = *(int *)(param_1 + 0x194);
  if (((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(iVar1 + 0x30) != 0)) ||
     (uVar3 = grim_jpg_restart_mcu(param_1), (char)uVar3 != '\0')) {
    local_58 = **(undefined4 **)(param_1 + 0x14);
    local_54 = (*(undefined4 **)(param_1 + 0x14))[1];
    local_10 = 0;
    local_38 = iVar1 + 0x18;
    local_30[0] = *(int *)(iVar1 + 0x20);
    local_30[1] = *(undefined4 *)(iVar1 + 0x24);
    local_50 = *(undefined4 *)(param_1 + 0x178);
    local_30[2] = *(undefined4 *)(iVar1 + 0x28);
    uVar7 = *(uint *)(iVar1 + 0x10);
    iVar5 = *(int *)(iVar1 + 0x14);
    local_3c = param_1;
    local_30[3] = *(undefined4 *)(iVar1 + 0x2c);
    if (0 < *(int *)(param_1 + 0x13c)) {
      local_14 = (uint *)(param_1 + 0x140);
      do {
        local_1c = *(undefined2 **)(param_2 + local_10 * 4);
        iVar8 = *(int *)(param_1 + 0x124 + *local_14 * 4);
        local_8 = *(int *)(iVar1 + 0x34 + *(int *)(iVar8 + 0x14) * 4);
        local_20 = *local_14;
        local_18 = iVar8;
        local_c = *(int *)(iVar1 + 0x44 + *(int *)(iVar8 + 0x18) * 4);
        if (iVar5 < 8) {
          uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,0);
          if ((char)uVar4 == '\0') goto LAB_100300a6;
          iVar5 = local_40;
          uVar7 = local_4c;
          if (7 < local_40) goto LAB_1002fdb9;
          piVar6 = (int *)0x1;
LAB_1002fde6:
          uVar4 = grim_jpg_decode_symbol(&local_58,uVar7,iVar5,local_8,piVar6);
          iVar5 = local_40;
          uVar7 = local_4c;
          uVar9 = uVar4;
          if ((int)uVar4 < 0) goto LAB_100300a6;
        }
        else {
LAB_1002fdb9:
          uVar4 = (int)uVar7 >> ((char)iVar5 - 8U & 0x1f) & 0xff;
          iVar2 = *(int *)(local_8 + 0xd4 + uVar4 * 4);
          if (iVar2 == 0) {
            piVar6 = (int *)0x9;
            goto LAB_1002fde6;
          }
          iVar5 = iVar5 - iVar2;
          uVar9 = (uint)*(byte *)(uVar4 + 0x4d4 + local_8);
        }
        uVar4 = 0;
        if (uVar9 != 0) {
          if ((iVar5 < (int)uVar9) &&
             (uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,uVar9), iVar5 = local_40, uVar7 = local_4c,
             (char)uVar4 == '\0')) {
LAB_100300a6:
            return uVar4 & 0xffffff00;
          }
          iVar5 = iVar5 - uVar9;
          local_8 = (1 << ((byte)uVar9 & 0x1f)) - 1;
          uVar4 = local_8 & (int)uVar7 >> ((byte)iVar5 & 0x1f);
          iVar8 = local_18;
          if ((int)uVar4 < *(int *)(&grim_jpg_extend_offset + uVar9 * 4)) {
            uVar4 = *(int *)(&grim_jpg_extend_test + uVar9 * 4) + uVar4;
          }
        }
        if (*(char *)(iVar8 + 0x30) == '\0') {
LAB_1002ff95:
          local_8 = 1;
          do {
            if (iVar5 < 8) {
              uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,0);
              if ((char)uVar4 == '\0') goto LAB_100300a6;
              iVar5 = local_40;
              uVar7 = local_4c;
              if (7 < local_40) goto LAB_1002ffcc;
              piVar6 = (int *)0x1;
LAB_1002fff6:
              uVar4 = grim_jpg_decode_symbol(&local_58,uVar7,iVar5,local_c,piVar6);
              iVar5 = local_40;
              uVar7 = local_4c;
              if ((int)uVar4 < 0) goto LAB_100300a6;
            }
            else {
LAB_1002ffcc:
              uVar4 = (int)uVar7 >> ((char)iVar5 - 8U & 0x1f) & 0xff;
              iVar8 = *(int *)(local_c + 0xd4 + uVar4 * 4);
              if (iVar8 == 0) {
                piVar6 = (int *)0x9;
                goto LAB_1002fff6;
              }
              uVar4 = (uint)*(byte *)(uVar4 + 0x4d4 + local_c);
              iVar5 = iVar5 - iVar8;
            }
            uVar9 = uVar4 & 0xf;
            if (uVar9 == 0) {
              if ((int)uVar4 >> 4 != 0xf) break;
              local_8 = local_8 + 0xf;
            }
            else {
              local_8 = local_8 + ((int)uVar4 >> 4);
              if ((iVar5 < (int)uVar9) &&
                 (uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,uVar9), iVar5 = local_40,
                 uVar7 = local_4c, (char)uVar4 == '\0')) goto LAB_100300a6;
              iVar5 = iVar5 - uVar9;
            }
            local_8 = local_8 + 1;
          } while ((int)local_8 < 0x40);
        }
        else {
          piVar6 = local_30 + local_20;
          *piVar6 = *piVar6 + uVar4;
          *local_1c = (short)*piVar6;
          if (*(int *)(iVar8 + 0x24) < 2) goto LAB_1002ff95;
          local_8 = 1;
          do {
            if (iVar5 < 8) {
              uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,0);
              if ((char)uVar4 == '\0') goto LAB_100300a6;
              iVar5 = local_40;
              uVar7 = local_4c;
              if (7 < local_40) goto LAB_1002febd;
              piVar6 = (int *)0x1;
LAB_1002fee7:
              uVar4 = grim_jpg_decode_symbol(&local_58,uVar7,iVar5,local_c,piVar6);
              iVar5 = local_40;
              uVar7 = local_4c;
              if ((int)uVar4 < 0) goto LAB_100300a6;
            }
            else {
LAB_1002febd:
              uVar4 = (int)uVar7 >> ((char)iVar5 - 8U & 0x1f) & 0xff;
              iVar8 = *(int *)(local_c + 0xd4 + uVar4 * 4);
              if (iVar8 == 0) {
                piVar6 = (int *)0x9;
                goto LAB_1002fee7;
              }
              uVar4 = (uint)*(byte *)(uVar4 + 0x4d4 + local_c);
              iVar5 = iVar5 - iVar8;
            }
            uVar9 = uVar4 & 0xf;
            local_20 = uVar9;
            if (uVar9 == 0) {
              if ((int)uVar4 >> 4 != 0xf) break;
              local_8 = local_8 + 0xf;
            }
            else {
              local_8 = local_8 + ((int)uVar4 >> 4);
              if ((iVar5 < (int)uVar9) &&
                 (uVar4 = grim_jpg_fill_bit_buffer(&local_58,uVar7,iVar5,uVar9), iVar5 = local_40,
                 uVar7 = local_4c, (char)uVar4 == '\0')) goto LAB_100300a6;
              iVar5 = iVar5 - uVar9;
              uVar4 = (1 << (sbyte)uVar9) - 1U & (int)uVar7 >> ((byte)iVar5 & 0x1f);
              if ((int)uVar4 < *(int *)(&grim_jpg_extend_offset + local_20 * 4)) {
                uVar4 = *(int *)(&grim_jpg_extend_test + local_20 * 4) + uVar4;
              }
              local_1c[(&grim_jpg_zigzag_order)[local_8]] = (short)uVar4;
            }
            local_8 = local_8 + 1;
          } while ((int)local_8 < 0x40);
        }
        local_10 = local_10 + 1;
        local_14 = local_14 + 1;
      } while (local_10 < *(int *)(param_1 + 0x13c));
    }
    **(undefined4 **)(param_1 + 0x14) = local_58;
    *(undefined4 *)(*(int *)(param_1 + 0x14) + 4) = local_54;
    *(undefined4 *)(param_1 + 0x178) = local_50;
    *(int *)(iVar1 + 0x30) = *(int *)(iVar1 + 0x30) + -1;
    *(int *)(iVar1 + 0x20) = local_30[0];
    *(int *)(iVar1 + 0x24) = local_30[1];
    *(int *)(iVar1 + 0x28) = local_30[2];
    *(int *)(iVar1 + 0x14) = iVar5;
    *(uint *)(iVar1 + 0x10) = uVar7;
    *(int *)(iVar1 + 0x2c) = local_30[3];
    uVar3 = CONCAT31((int3)((uint)iVar5 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_start_pass_huff_decoder @ 100300aa */

void __cdecl grim_jpg_start_pass_huff_decoder(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_c;
  undefined4 *local_8;
  
  piVar4 = param_1;
  iVar1 = param_1[0x65];
  if ((((param_1[0x5a] != 0) || (param_1[0x5b] != 0x3f)) || (param_1[0x5c] != 0)) ||
     (param_1[0x5d] != 0)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x76;
    (**(code **)(*param_1 + 4))(param_1,0xffffffff);
  }
  local_c = 0;
  if (0 < param_1[0x48]) {
    local_8 = (undefined4 *)(iVar1 + 0x20);
    param_1 = param_1 + 0x49;
    do {
      iVar2 = *(int *)(*param_1 + 0x14);
      iVar3 = *(int *)(*param_1 + 0x18);
      if (((iVar2 < 0) || (3 < iVar2)) || (piVar4[iVar2 + 0x28] == 0)) {
        *(undefined4 *)(*piVar4 + 0x14) = 0x31;
        *(int *)(*piVar4 + 0x18) = iVar2;
        (**(code **)*piVar4)(piVar4);
      }
      if (((iVar3 < 0) || (3 < iVar3)) || (piVar4[iVar3 + 0x2c] == 0)) {
        *(undefined4 *)(*piVar4 + 0x14) = 0x31;
        *(int *)(*piVar4 + 0x18) = iVar3;
        (**(code **)*piVar4)(piVar4);
      }
      grim_jpg_make_derived_tbl((int)piVar4,piVar4[iVar2 + 0x28],(int *)(iVar1 + 0x34 + iVar2 * 4));
      grim_jpg_make_derived_tbl((int)piVar4,piVar4[iVar3 + 0x2c],(int *)(iVar1 + 0x44 + iVar3 * 4));
      *local_8 = 0;
      param_1 = param_1 + 1;
      local_8 = local_8 + 1;
      local_c = local_c + 1;
    } while (local_c < piVar4[0x48]);
  }
  *(undefined1 *)(iVar1 + 0x18) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(iVar1 + 8) = 0;
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(int *)(iVar1 + 0x30) = piVar4[0x3f];
  return;
}



/* grim_jpg_huff_decoder_init @ 100301d9 */

void __cdecl grim_jpg_huff_decoder_init(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x58);
  *(undefined4 **)(param_1 + 0x194) = puVar1;
  iVar2 = 4;
  *puVar1 = grim_jpg_start_pass_huff_decoder;
  puVar1[1] = grim_jpg_decode_mcu_ac;
  puVar1 = puVar1 + 0xd;
  do {
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



/* grim_jpg_restart_mcu_dc @ 10030213 */

undefined4 grim_jpg_restart_mcu_dc(void)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_EDI;
  
  iVar2 = *(int *)(unaff_EDI + 0x194);
  piVar1 = (int *)(*(int *)(unaff_EDI + 400) + 0x58);
  *piVar1 = *piVar1 + *(int *)(iVar2 + 0x14) / 8;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  uVar3 = (**(code **)(*(int *)(unaff_EDI + 400) + 8))();
  if ((char)uVar3 != '\0') {
    iVar5 = 0;
    if (0 < *(int *)(unaff_EDI + 0x120)) {
      puVar4 = (undefined4 *)(iVar2 + 0x24);
      do {
        *puVar4 = 0;
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar5 < *(int *)(unaff_EDI + 0x120));
    }
    *(undefined4 *)(iVar2 + 0x20) = 0;
    uVar3 = *(undefined4 *)(unaff_EDI + 0xfc);
    *(undefined4 *)(iVar2 + 0x34) = uVar3;
    *(undefined1 *)(iVar2 + 0x18) = 0;
    uVar3 = CONCAT31((int3)((uint)uVar3 >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_decode_mcu_dc @ 1003026e */

undefined4 __cdecl grim_jpg_decode_mcu_dc(uint param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  uint local_50;
  int local_44;
  uint local_40;
  int local_3c;
  int local_34 [5];
  undefined2 *local_20;
  undefined4 local_1c;
  int local_18;
  int *local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  uVar1 = param_1;
  local_c = *(int *)(param_1 + 0x194);
  local_1c = *(undefined4 *)(param_1 + 0x174);
  if (((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(*(int *)(param_1 + 0x194) + 0x34) != 0)) ||
     (uVar2 = grim_jpg_restart_mcu_dc(), (char)uVar2 != '\0')) {
    iVar5 = local_c;
    local_10 = 0;
    iVar7 = *(int *)(param_1 + 0x13c);
    local_40 = param_1;
    local_5c = **(undefined4 **)(param_1 + 0x14);
    local_58 = (*(undefined4 **)(param_1 + 0x14))[1];
    local_54 = *(undefined4 *)(param_1 + 0x178);
    uVar3 = *(uint *)(local_c + 0x10);
    iVar8 = *(int *)(local_c + 0x14);
    local_3c = local_c + 0x18;
    piVar4 = (int *)(local_c + 0x20);
    piVar10 = local_34;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar10 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar10 = piVar10 + 1;
    }
    if (0 < iVar7) {
      local_14 = (int *)(param_1 + 0x140);
      param_1 = uVar3;
      do {
        local_20 = *(undefined2 **)(param_2 + local_10 * 4);
        local_18 = *local_14;
        iVar7 = *(int *)(iVar5 + 0x38 + *(int *)(*(int *)(uVar1 + 0x124 + *local_14 * 4) + 0x14) * 4
                        );
        if (iVar8 < 8) {
          uVar3 = grim_jpg_fill_bit_buffer(&local_5c,param_1,iVar8,0);
          if ((char)uVar3 == '\0') goto LAB_10030467;
          param_1 = local_50;
          iVar5 = local_c;
          iVar8 = local_44;
          if (7 < local_44) goto LAB_10030352;
          piVar4 = (int *)0x1;
LAB_1003037a:
          uVar3 = grim_jpg_decode_symbol(&local_5c,param_1,iVar8,iVar7,piVar4);
          if ((int)uVar3 < 0) goto LAB_10030467;
          param_1 = local_50;
          iVar5 = local_c;
          iVar8 = local_44;
          uVar9 = uVar3;
        }
        else {
LAB_10030352:
          uVar3 = (int)param_1 >> ((char)iVar8 - 8U & 0x1f) & 0xff;
          iVar6 = *(int *)(iVar7 + 0xd4 + uVar3 * 4);
          if (iVar6 == 0) {
            piVar4 = (int *)0x9;
            goto LAB_1003037a;
          }
          uVar9 = (uint)*(byte *)(uVar3 + 0x4d4 + iVar7);
          iVar8 = iVar8 - iVar6;
        }
        uVar3 = 0;
        if (uVar9 != 0) {
          if (iVar8 < (int)uVar9) {
            uVar3 = grim_jpg_fill_bit_buffer(&local_5c,param_1,iVar8,uVar9);
            if ((char)uVar3 == '\0') {
LAB_10030467:
              return uVar3 & 0xffffff00;
            }
            param_1 = local_50;
            iVar5 = local_c;
            iVar8 = local_44;
          }
          iVar8 = iVar8 - uVar9;
          local_8 = (1 << ((byte)uVar9 & 0x1f)) - 1;
          uVar3 = local_8 & (int)param_1 >> ((byte)iVar8 & 0x1f);
          if ((int)uVar3 < *(int *)(&DAT_1004f490 + uVar9 * 4)) {
            uVar3 = *(int *)(&DAT_1004f4d0 + uVar9 * 4) + uVar3;
          }
        }
        local_14 = local_14 + 1;
        piVar4 = local_34 + local_18 + 1;
        *piVar4 = *piVar4 + uVar3;
        local_10 = local_10 + 1;
        *local_20 = (short)(*piVar4 << ((byte)local_1c & 0x1f));
        uVar3 = param_1;
      } while (local_10 < *(int *)(uVar1 + 0x13c));
    }
    param_1 = uVar3;
    **(undefined4 **)(uVar1 + 0x14) = local_5c;
    *(undefined4 *)(*(int *)(uVar1 + 0x14) + 4) = local_58;
    *(undefined4 *)(uVar1 + 0x178) = local_54;
    *(int *)(iVar5 + 0x34) = *(int *)(iVar5 + 0x34) + -1;
    *(uint *)(iVar5 + 0x10) = param_1;
    *(int *)(iVar5 + 0x14) = iVar8;
    piVar4 = local_34;
    piVar10 = (int *)(iVar5 + 0x20);
    for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar10 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar10 = piVar10 + 1;
    }
    uVar2 = CONCAT31((int3)((uint)iVar5 >> 8),1);
  }
  return uVar2;
}



/* grim_jpg_mcu_decode_progressive_ac @ 1003046b */

undefined4 __cdecl grim_jpg_mcu_decode_progressive_ac(uint param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  int local_34;
  uint local_30;
  int local_2c;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  uint local_10;
  int local_c;
  int local_8;
  
  uVar2 = param_1;
  local_1c = *(int *)(param_1 + 0x16c);
  iVar1 = *(int *)(param_1 + 0x194);
  local_20 = *(undefined4 *)(param_1 + 0x174);
  if (((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(iVar1 + 0x34) != 0)) ||
     (uVar3 = grim_jpg_restart_mcu_dc(), (char)uVar3 != '\0')) {
    if (*(int *)(iVar1 + 0x20) == 0) {
      local_30 = param_1;
      local_4c = **(undefined4 **)(param_1 + 0x14);
      local_48 = (*(undefined4 **)(param_1 + 0x14))[1];
      local_44 = *(undefined4 *)(param_1 + 0x178);
      uVar7 = *(uint *)(iVar1 + 0x10);
      iVar4 = *(int *)(iVar1 + 0x14);
      local_2c = iVar1 + 0x18;
      local_24 = *param_2;
      local_18 = *(int *)(iVar1 + 0x48);
      local_c = 0;
      local_10 = uVar7;
      for (local_8 = *(int *)(param_1 + 0x168); local_8 <= local_1c; local_8 = local_8 + 1) {
        if (iVar4 < 8) {
          param_1 = grim_jpg_fill_bit_buffer(&local_4c,uVar7,iVar4,0);
          if ((char)param_1 == '\0') goto LAB_1003061a;
          local_10 = local_40;
          iVar4 = local_34;
          uVar7 = local_40;
          if (7 < local_34) goto LAB_10030530;
          piVar5 = (int *)0x1;
LAB_10030560:
          param_1 = grim_jpg_decode_symbol(&local_4c,uVar7,iVar4,local_18,piVar5);
          if ((int)param_1 < 0) goto LAB_1003061a;
          local_10 = local_40;
          iVar4 = local_34;
          uVar7 = local_40;
        }
        else {
LAB_10030530:
          uVar6 = (int)uVar7 >> ((char)iVar4 - 8U & 0x1f) & 0xff;
          iVar8 = *(int *)(local_18 + 0xd4 + uVar6 * 4);
          if (iVar8 == 0) {
            piVar5 = (int *)0x9;
            goto LAB_10030560;
          }
          iVar4 = iVar4 - iVar8;
          param_1 = (uint)*(byte *)(uVar6 + 0x4d4 + local_18);
        }
        local_14 = (int)param_1 >> 4;
        uVar6 = param_1 & 0xf;
        if (uVar6 == 0) {
          if (local_14 != 0xf) {
            iVar8 = 1 << ((byte)local_14 & 0x1f);
            local_c = iVar8;
            if (local_14 != 0) {
              if ((iVar4 < local_14) &&
                 (param_1 = grim_jpg_fill_bit_buffer(&local_4c,uVar7,iVar4,local_14), iVar4 = local_34,
                 uVar7 = local_40, (char)param_1 == '\0')) goto LAB_1003061a;
              iVar4 = iVar4 - local_14;
              local_c = local_c + ((int)uVar7 >> ((byte)iVar4 & 0x1f) & iVar8 - 1U);
            }
            local_c = local_c + -1;
            break;
          }
          local_8 = local_8 + 0xf;
        }
        else {
          local_8 = local_8 + local_14;
          if (iVar4 < (int)uVar6) {
            param_1 = grim_jpg_fill_bit_buffer(&local_4c,uVar7,iVar4,uVar6);
            if ((char)param_1 == '\0') {
LAB_1003061a:
              return param_1 & 0xffffff00;
            }
            local_10 = local_40;
            iVar4 = local_34;
            uVar7 = local_40;
          }
          iVar4 = iVar4 - uVar6;
          uVar7 = (1 << (sbyte)uVar6) - 1U & (int)uVar7 >> ((byte)iVar4 & 0x1f);
          if ((int)uVar7 < *(int *)(&DAT_1004f490 + uVar6 * 4)) {
            uVar7 = *(int *)(&DAT_1004f4d0 + uVar6 * 4) + uVar7;
          }
          *(short *)(local_24 + (&grim_jpg_zigzag_order)[local_8] * 2) =
               (short)(uVar7 << ((byte)local_20 & 0x1f));
          uVar7 = local_10;
        }
      }
      **(undefined4 **)(uVar2 + 0x14) = local_4c;
      *(undefined4 *)(*(int *)(uVar2 + 0x14) + 4) = local_48;
      *(undefined4 *)(uVar2 + 0x178) = local_44;
      *(int *)(iVar1 + 0x14) = iVar4;
      *(uint *)(iVar1 + 0x10) = uVar7;
    }
    else {
      local_c = *(int *)(iVar1 + 0x20) + -1;
    }
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + -1;
    *(int *)(iVar1 + 0x20) = local_c;
    uVar3 = CONCAT31((int3)((uint)local_c >> 8),1);
  }
  return uVar3;
}



/* grim_jpg_mcu_decode_progressive_dc @ 10030694 */

uint __cdecl grim_jpg_mcu_decode_progressive_dc(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  int local_18;
  int local_14;
  int local_10;
  int local_8;
  
  iVar4 = param_1;
  iVar2 = *(int *)(param_1 + 0x194);
  local_8 = 1 << ((byte)*(undefined4 *)(param_1 + 0x174) & 0x1f);
  if (((*(int *)(param_1 + 0xfc) == 0) || (*(int *)(iVar2 + 0x34) != 0)) ||
     (uVar5 = grim_jpg_restart_mcu_dc(), (char)uVar5 != '\0')) {
    piVar1 = (int *)(param_1 + 0x13c);
    local_14 = param_1;
    local_30 = **(undefined4 **)(param_1 + 0x14);
    local_2c = (*(undefined4 **)(param_1 + 0x14))[1];
    local_28 = *(undefined4 *)(param_1 + 0x178);
    uVar6 = *(uint *)(iVar2 + 0x10);
    iVar7 = *(int *)(iVar2 + 0x14);
    local_10 = iVar2 + 0x18;
    param_1 = 0;
    if (0 < *piVar1) {
      do {
        puVar3 = *(ushort **)(param_2 + param_1 * 4);
        if ((iVar7 < 1) &&
           (uVar5 = grim_jpg_fill_bit_buffer(&local_30,uVar6,iVar7,1), uVar6 = local_24, iVar7 = local_18,
           (char)uVar5 == '\0')) goto LAB_10030772;
        iVar7 = iVar7 + -1;
        if (((int)uVar6 >> ((byte)iVar7 & 0x1f) & 1U) != 0) {
          *puVar3 = *puVar3 | (ushort)local_8;
        }
        param_1 = param_1 + 1;
      } while (param_1 < *(int *)(iVar4 + 0x13c));
    }
    **(undefined4 **)(iVar4 + 0x14) = local_30;
    *(undefined4 *)(*(int *)(iVar4 + 0x14) + 4) = local_2c;
    *(undefined4 *)(iVar4 + 0x178) = local_28;
    *(int *)(iVar2 + 0x34) = *(int *)(iVar2 + 0x34) + -1;
    *(uint *)(iVar2 + 0x10) = uVar6;
    *(int *)(iVar2 + 0x14) = iVar7;
    uVar5 = CONCAT31((int3)(uVar6 >> 8),1);
  }
  else {
LAB_10030772:
    uVar5 = uVar5 & 0xffffff00;
  }
  return uVar5;
}



/* grim_jpg_mcu_decode_progressive_refine @ 10030776 */

undefined4 __cdecl grim_jpg_mcu_decode_progressive_refine(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int aiStack_158 [64];
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int *local_4c;
  int local_40;
  int *local_3c;
  int local_38;
  uint local_30;
  uint local_2c;
  short *local_28;
  int local_24;
  int local_20;
  uint local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  piVar3 = param_1;
  local_14 = param_1[0x5b];
  iVar1 = param_1[0x65];
  local_2c = 1 << ((byte)param_1[0x5d] & 0x1f);
  local_30 = -1 << ((byte)param_1[0x5d] & 0x1f);
  if (((param_1[0x3f] == 0) || (*(int *)(iVar1 + 0x34) != 0)) ||
     (uVar4 = grim_jpg_restart_mcu_dc(), (char)uVar4 != '\0')) {
    local_1c = 0;
    local_3c = param_1;
    local_58 = *(undefined4 *)param_1[5];
    local_54 = ((undefined4 *)param_1[5])[1];
    local_50 = param_1[0x5e];
    local_38 = iVar1 + 0x18;
    iVar7 = *(int *)(iVar1 + 0x14);
    local_18 = *param_2;
    local_10 = *(int *)(iVar1 + 0x20);
    local_20 = *(int *)(iVar1 + 0x48);
    local_8 = param_1[0x5a];
    param_1 = *(int **)(iVar1 + 0x10);
    if (local_10 == 0) {
      for (; local_8 <= local_14; local_8 = local_8 + 1) {
        if (iVar7 < 8) {
          uVar4 = grim_jpg_fill_bit_buffer(&local_58,(uint)param_1,iVar7,0);
          if ((char)uVar4 == '\0') goto LAB_10030adc;
          param_1 = local_4c;
          iVar7 = local_40;
          if (7 < local_40) goto LAB_1003084f;
          piVar5 = (int *)0x1;
LAB_1003087c:
          local_c = grim_jpg_decode_symbol(&local_58,(uint)param_1,iVar7,local_20,piVar5);
          if ((int)local_c < 0) goto LAB_10030adc;
          param_1 = local_4c;
          iVar7 = local_40;
        }
        else {
LAB_1003084f:
          uVar6 = (int)param_1 >> ((char)iVar7 - 8U & 0x1f) & 0xff;
          iVar2 = *(int *)(local_20 + 0xd4 + uVar6 * 4);
          if (iVar2 == 0) {
            piVar5 = (int *)0x9;
            goto LAB_1003087c;
          }
          local_c = (uint)*(byte *)(uVar6 + 0x4d4 + local_20);
          iVar7 = iVar7 - iVar2;
        }
        local_24 = (int)local_c >> 4;
        local_c = local_c & 0xf;
        if (local_c == 0) {
          uVar6 = 0;
          if (local_24 != 0xf) {
            local_20 = 1 << ((byte)local_24 & 0x1f);
            local_10 = local_20;
            if (local_24 == 0) goto LAB_10030a14;
            if (iVar7 < local_24) {
              uVar4 = grim_jpg_fill_bit_buffer(&local_58,(uint)param_1,iVar7,local_24);
              if ((char)uVar4 == '\0') goto LAB_10030adc;
              param_1 = local_4c;
              iVar7 = local_40;
            }
            iVar7 = iVar7 - local_24;
            local_10 = local_10 + ((int)param_1 >> ((byte)iVar7 & 0x1f) & local_20 - 1U);
            goto LAB_10030a14;
          }
        }
        else {
          if (local_c != 1) {
            *(undefined4 *)(*piVar3 + 0x14) = 0x72;
            (**(code **)(*piVar3 + 4))(piVar3,0xffffffff);
          }
          if (iVar7 < 1) {
            uVar4 = grim_jpg_fill_bit_buffer(&local_58,(uint)param_1,iVar7,1);
            if ((char)uVar4 == '\0') goto LAB_10030adc;
            param_1 = local_4c;
            iVar7 = local_40;
          }
          iVar7 = iVar7 + -1;
          uVar6 = local_2c;
          if (((int)param_1 >> ((byte)iVar7 & 0x1f) & 1U) == 0) {
            uVar6 = local_30;
          }
        }
        do {
          local_c = uVar6;
          local_28 = (short *)(local_18 + (&grim_jpg_zigzag_order)[local_8] * 2);
          if (*local_28 == 0) {
            local_24 = local_24 + -1;
            if (local_24 < 0) break;
          }
          else {
            if (iVar7 < 1) {
              uVar4 = grim_jpg_fill_bit_buffer(&local_58,(uint)param_1,iVar7,1);
              if ((char)uVar4 == '\0') goto LAB_10030adc;
              param_1 = local_4c;
              iVar7 = local_40;
            }
            iVar7 = iVar7 + -1;
            if ((((int)param_1 >> ((byte)iVar7 & 0x1f) & 1U) != 0) &&
               ((local_2c & (int)*local_28) == 0)) {
              uVar6 = local_2c;
              if (*local_28 < 0) {
                uVar6 = local_30;
              }
              *local_28 = *local_28 + (short)uVar6;
            }
          }
          local_8 = local_8 + 1;
          uVar6 = local_c;
        } while (local_8 <= local_14);
        if (local_c != 0) {
          iVar2 = (&grim_jpg_zigzag_order)[local_8];
          *(short *)(local_18 + iVar2 * 2) = (short)local_c;
          piVar5 = aiStack_158 + local_1c;
          local_1c = local_1c + 1;
          *piVar5 = iVar2;
        }
      }
    }
    else {
LAB_10030a14:
      if (local_10 != 0) {
        for (; local_8 <= local_14; local_8 = local_8 + 1) {
          local_28 = (short *)(local_18 + (&grim_jpg_zigzag_order)[local_8] * 2);
          if (*local_28 != 0) {
            if (iVar7 < 1) {
              uVar4 = grim_jpg_fill_bit_buffer(&local_58,(uint)param_1,iVar7,1);
              if ((char)uVar4 == '\0') {
LAB_10030adc:
                for (; 0 < (int)local_1c; local_1c = local_1c - 1) {
                  *(undefined2 *)(local_18 + aiStack_158[local_1c - 1] * 2) = 0;
                }
                return local_1c & 0xffffff00;
              }
              param_1 = local_4c;
              iVar7 = local_40;
            }
            iVar7 = iVar7 + -1;
            if ((((int)param_1 >> ((byte)iVar7 & 0x1f) & 1U) != 0) &&
               ((local_2c & (int)*local_28) == 0)) {
              uVar6 = local_2c;
              if (*local_28 < 0) {
                uVar6 = local_30;
              }
              *local_28 = *local_28 + (short)uVar6;
            }
          }
        }
        local_10 = local_10 + -1;
      }
    }
    *(undefined4 *)piVar3[5] = local_58;
    *(undefined4 *)(piVar3[5] + 4) = local_54;
    piVar3[0x5e] = local_50;
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + -1;
    *(int **)(iVar1 + 0x10) = param_1;
    *(int *)(iVar1 + 0x20) = local_10;
    *(int *)(iVar1 + 0x14) = iVar7;
    uVar4 = CONCAT31((int3)((uint)local_10 >> 8),1);
  }
  return uVar4;
}



/* grim_jpg_mcu_decoder_init @ 10030ae4 */

void __cdecl grim_jpg_mcu_decoder_init(int *param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  undefined4 *local_14;
  int *local_10;
  int local_8;
  
  iVar1 = param_1[0x65];
  bVar7 = param_1[0x5a] != 0;
  bVar3 = false;
  if (bVar7) {
    if ((param_1[0x5b] < param_1[0x5a]) || (0x3f < param_1[0x5b])) {
      bVar3 = true;
    }
    bVar8 = param_1[0x48] == 1;
  }
  else {
    bVar8 = param_1[0x5b] == 0;
  }
  if (!bVar8) {
    bVar3 = true;
  }
  if ((param_1[0x5c] != 0) && (param_1[0x5d] != param_1[0x5c] + -1)) {
    bVar3 = true;
  }
  if (0xd < param_1[0x5d]) {
    bVar3 = true;
  }
  if (bVar3) {
    *(undefined4 *)(*param_1 + 0x14) = 0xe;
    *(int *)(*param_1 + 0x18) = param_1[0x5a];
    *(int *)(*param_1 + 0x1c) = param_1[0x5b];
    *(int *)(*param_1 + 0x20) = param_1[0x5c];
    *(int *)(*param_1 + 0x24) = param_1[0x5d];
    (**(code **)*param_1)(param_1);
  }
  local_8 = 0;
  if (0 < param_1[0x48]) {
    local_10 = param_1 + 0x49;
    do {
      iVar2 = *(int *)(*local_10 + 4);
      piVar5 = (int *)(iVar2 * 0x100 + param_1[0x23]);
      if ((bVar7) && (*piVar5 < 0)) {
        *(undefined4 *)(*param_1 + 0x14) = 0x6f;
        *(int *)(*param_1 + 0x18) = iVar2;
        *(undefined4 *)(*param_1 + 0x1c) = 0;
        (**(code **)(*param_1 + 4))(param_1,0xffffffff);
      }
      for (iVar6 = param_1[0x5a]; iVar6 <= param_1[0x5b]; iVar6 = iVar6 + 1) {
        iVar4 = piVar5[iVar6];
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        if (param_1[0x5c] != iVar4) {
          *(undefined4 *)(*param_1 + 0x14) = 0x6f;
          *(int *)(*param_1 + 0x18) = iVar2;
          *(int *)(*param_1 + 0x1c) = iVar6;
          (**(code **)(*param_1 + 4))(param_1,0xffffffff);
        }
        piVar5[iVar6] = param_1[0x5d];
      }
      local_8 = local_8 + 1;
      local_10 = local_10 + 1;
    } while (local_8 < param_1[0x48]);
  }
  if (param_1[0x5c] == 0) {
    if (bVar7) {
      *(code **)(iVar1 + 4) = grim_jpg_mcu_decode_progressive_ac;
    }
    else {
      *(code **)(iVar1 + 4) = grim_jpg_decode_mcu_dc;
    }
  }
  else if (bVar7) {
    *(code **)(iVar1 + 4) = grim_jpg_mcu_decode_progressive_refine;
  }
  else {
    *(code **)(iVar1 + 4) = grim_jpg_mcu_decode_progressive_dc;
  }
  local_8 = 0;
  if (0 < param_1[0x48]) {
    local_10 = param_1 + 0x49;
    local_14 = (undefined4 *)(iVar1 + 0x24);
    do {
      if (bVar7) {
        iVar2 = *(int *)(*local_10 + 0x18);
        if (((iVar2 < 0) || (3 < iVar2)) || (param_1[iVar2 + 0x2c] == 0)) {
          *(undefined4 *)(*param_1 + 0x14) = 0x31;
          *(int *)(*param_1 + 0x18) = iVar2;
          (**(code **)*param_1)(param_1);
        }
        piVar5 = (int *)(iVar1 + 0x38 + iVar2 * 4);
        grim_jpg_make_derived_tbl((int)param_1,param_1[iVar2 + 0x2c],piVar5);
        *(int *)(iVar1 + 0x48) = *piVar5;
      }
      else if (param_1[0x5c] == 0) {
        iVar2 = *(int *)(*local_10 + 0x14);
        if (((iVar2 < 0) || (3 < iVar2)) || (param_1[iVar2 + 0x28] == 0)) {
          *(undefined4 *)(*param_1 + 0x14) = 0x31;
          *(int *)(*param_1 + 0x18) = iVar2;
          (**(code **)*param_1)(param_1);
        }
        grim_jpg_make_derived_tbl((int)param_1,param_1[iVar2 + 0x28],(int *)(iVar1 + 0x38 + iVar2 * 4));
      }
      local_8 = local_8 + 1;
      local_10 = local_10 + 1;
      *local_14 = 0;
      local_14 = local_14 + 1;
    } while (local_8 < param_1[0x48]);
  }
  *(undefined1 *)(iVar1 + 0x18) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(undefined4 *)(iVar1 + 0x20) = 0;
  *(int *)(iVar1 + 0x34) = param_1[0x3f];
  return;
}



/* grim_jpg_mcu_decoder_start @ 10030d87 */

void __cdecl grim_jpg_mcu_decoder_start(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x50);
  *(undefined4 **)(param_1 + 0x194) = puVar1;
  *puVar1 = grim_jpg_mcu_decoder_init;
  puVar1[0xe] = 0;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  puVar1[0x11] = 0;
  puVar1 = (undefined4 *)
           (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,*(int *)(param_1 + 0x20) << 8);
  iVar3 = 0;
  *(undefined4 **)(param_1 + 0x8c) = puVar1;
  if (0 < *(int *)(param_1 + 0x20)) {
    do {
      iVar3 = iVar3 + 1;
      puVar4 = puVar1;
      for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = 0xffffffff;
        puVar4 = puVar4 + 1;
      }
      puVar1 = puVar1 + 0x40;
    } while (iVar3 < *(int *)(param_1 + 0x20));
  }
  return;
}



/* grim_jpg_scanline_output_setup @ 10030de8 */

void __cdecl grim_jpg_scanline_output_setup(undefined *param_1)

{
  int *piVar1;
  double dVar2;
  undefined *puVar3;
  int iVar4;
  short *psVar5;
  undefined2 *puVar6;
  double *pdVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  int local_10;
  double *local_c;
  int local_8;
  
  puVar3 = param_1;
  piVar10 = (int *)(param_1 + 0x20);
  piVar11 = (int *)(param_1 + 0x198);
  piVar1 = (int *)(param_1 + 0xc4);
  local_8 = 0;
  param_1 = (undefined *)0x0;
  local_10 = 0;
  if (0 < *piVar10) {
    piVar10 = (int *)(*piVar11 + 0x2c);
    piVar11 = (int *)(*piVar1 + 0x24);
    do {
      iVar8 = *piVar11;
      if (iVar8 == 1) {
        param_1 = grim_jpg_output_line_noop;
LAB_10030ea3:
        local_8 = 0;
      }
      else {
        if (iVar8 == 2) {
          param_1 = grim_jpg_quant_prescale;
          goto LAB_10030ea3;
        }
        if (iVar8 == 4) {
          param_1 = grim_jpg_quant_table_build;
          goto LAB_10030ea3;
        }
        if (iVar8 == 8) {
          iVar8 = *(int *)(puVar3 + 0x44);
          if (iVar8 == 0) {
            param_1 = grim_jpg_output_line_islow_setup;
            goto LAB_10030ea3;
          }
          if (iVar8 == 1) {
            param_1 = grim_jpg_output_line_ifast_setup;
            local_8 = 1;
          }
          else {
            if (iVar8 != 2) {
              *(undefined4 *)(*(int *)puVar3 + 0x14) = 0x2f;
              goto LAB_10030e5d;
            }
            param_1 = grim_zlib_inflate_blocks_process;
            local_8 = 2;
          }
        }
        else {
          *(undefined4 *)(*(int *)puVar3 + 0x14) = 6;
          *(int *)(*(int *)puVar3 + 0x18) = *piVar11;
LAB_10030e5d:
          (*(code *)**(undefined4 **)puVar3)(puVar3);
        }
      }
      piVar10[-10] = (int)param_1;
      if ((((char)piVar11[3] != '\0') && (*piVar10 != local_8)) && (iVar8 = piVar11[10], iVar8 != 0)
         ) {
        *piVar10 = local_8;
        if (local_8 == 0) {
          puVar6 = (undefined2 *)piVar11[0xb];
          iVar8 = iVar8 - (int)puVar6;
          iVar9 = 0x40;
          do {
            *puVar6 = *(undefined2 *)(iVar8 + (int)puVar6);
            puVar6 = puVar6 + 1;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
        else if (local_8 == 1) {
          iVar9 = piVar11[0xb];
          psVar5 = &DAT_1004f510;
          do {
            *(short *)(iVar9 + -0x1004f510 + (int)psVar5) =
                 (short)((int)*(short *)(iVar8 + -0x1004f510 + (int)psVar5) * (int)*psVar5 + 0x800
                        >> 0xc);
            psVar5 = psVar5 + 1;
          } while ((int)psVar5 < 0x1004f590);
        }
        else if (local_8 == 2) {
          iVar9 = piVar11[0xb];
          iVar4 = 0;
          local_c = (double *)&DAT_1004f590;
          do {
            pdVar7 = (double *)&DAT_1004f590;
            do {
              dVar2 = *pdVar7;
              pdVar7 = pdVar7 + 1;
              *(float *)(iVar9 + iVar4 * 4) =
                   (float)*(ushort *)(iVar8 + iVar4 * 2) * (float)dVar2 * (float)*local_c;
              iVar4 = iVar4 + 1;
            } while ((int)pdVar7 < 0x1004f5d0);
            local_c = local_c + 1;
          } while ((int)local_c < 0x1004f5d0);
        }
        else {
          *(undefined4 *)(*(int *)puVar3 + 0x14) = 0x2f;
          (*(code *)**(undefined4 **)puVar3)(puVar3);
        }
      }
      local_10 = local_10 + 1;
      piVar10 = piVar10 + 1;
      piVar11 = piVar11 + 0x15;
    } while (local_10 < *(int *)(puVar3 + 0x20));
  }
  return;
}



/* grim_jpg_scanline_output_start @ 10030f9f */

void __cdecl grim_jpg_scanline_output_start(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_8;
  
  puVar1 = param_1;
  puVar2 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x54);
  local_8 = 0;
  param_1[0x66] = puVar2;
  *puVar2 = grim_jpg_scanline_output_setup;
  if (0 < (int)param_1[8]) {
    puVar2 = puVar2 + 0xb;
    param_1 = (undefined4 *)(param_1[0x31] + 0x50);
    do {
      puVar3 = (undefined4 *)(**(code **)puVar1[1])(puVar1,1,0x100);
      *param_1 = puVar3;
      for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      *puVar2 = 0xffffffff;
      local_8 = local_8 + 1;
      puVar2 = puVar2 + 1;
      param_1 = param_1 + 0x15;
    } while (local_8 < (int)puVar1[8]);
  }
  return;
}



/* grim_jpg_coeff_block_zero @ 10031013 */

void __cdecl
grim_jpg_coeff_block_zero(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
            int *param_6,int param_7)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  piVar3 = param_6;
  iVar2 = param_1;
  iVar1 = *(int *)(param_1 + 0x188);
  uVar4 = param_7 - *param_6;
  if (*(uint *)(iVar1 + 0x10) < (uint)(param_7 - *param_6)) {
    uVar4 = *(uint *)(iVar1 + 0x10);
  }
  param_1 = 0;
  (**(code **)(*(int *)(iVar2 + 0x19c) + 4))
            (iVar2,param_2,param_3,param_4,*(undefined4 *)(iVar1 + 0xc),&param_1,uVar4);
  (**(code **)(*(int *)(iVar2 + 0x1a4) + 4))
            (iVar2,*(undefined4 *)(iVar1 + 0xc),param_5 + *piVar3 * 4,param_1);
  *piVar3 = *piVar3 + param_1;
  return;
}



/* grim_jpg_coeff_block_copy @ 10031078 */

/* [binja] int32_t sub_10031078(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t*
   arg5) */

int __cdecl grim_jpg_coeff_block_copy(int arg1,int arg2,int arg3,int arg4,int *arg5)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int *in_stack_00000018;
  
  iVar2 = *(int *)(arg1 + 0x188);
  puVar1 = (uint *)(iVar2 + 0x18);
  if (*puVar1 == 0) {
    uVar4 = (**(code **)(*(int *)(arg1 + 4) + 0x1c))
                      (arg1,*(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0x14),
                       *(undefined4 *)(iVar2 + 0x10),1);
    *(undefined4 *)(iVar2 + 0xc) = uVar4;
  }
  uVar3 = *puVar1;
  (**(code **)(*(int *)(arg1 + 0x19c) + 4))
            (arg1,arg2,arg3,arg4,*(undefined4 *)(iVar2 + 0xc),puVar1,*(undefined4 *)(iVar2 + 0x10));
  if (uVar3 < *puVar1) {
    iVar5 = *puVar1 - uVar3;
    (**(code **)(*(int *)(arg1 + 0x1a4) + 4))(arg1,*(int *)(iVar2 + 0xc) + uVar3 * 4,0,iVar5);
    *in_stack_00000018 = *in_stack_00000018 + iVar5;
  }
  uVar3 = *(uint *)(iVar2 + 0x10);
  if (uVar3 <= *puVar1) {
    *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + uVar3;
    *puVar1 = 0;
  }
  return uVar3;
}



/* grim_jpg_coeff_block_dequant @ 10031108 */

/* [binja] int32_t sub_10031108(void* arg1, int32_t arg2, int32_t* arg3, int32_t arg4) */

int __cdecl grim_jpg_coeff_block_dequant(void *arg1,int arg2,int *arg3,int arg4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int in_stack_00000014;
  int *in_stack_00000018;
  int in_stack_0000001c;
  
  iVar1 = *(int *)((int)arg1 + 0x188);
  if (*(int *)(iVar1 + 0x18) == 0) {
    uVar2 = (**(code **)(*(int *)((int)arg1 + 4) + 0x1c))
                      (arg1,*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x14),
                       *(undefined4 *)(iVar1 + 0x10),0);
    *(undefined4 *)(iVar1 + 0xc) = uVar2;
  }
  uVar4 = *(int *)(iVar1 + 0x10) - *(int *)(iVar1 + 0x18);
  uVar3 = in_stack_0000001c - *in_stack_00000018;
  if (uVar3 < uVar4) {
    uVar4 = uVar3;
  }
  uVar3 = *(int *)((int)arg1 + 0x60) - *(int *)(iVar1 + 0x14);
  if (uVar3 < uVar4) {
    uVar4 = uVar3;
  }
  (**(code **)(*(int *)((int)arg1 + 0x1a4) + 4))
            (arg1,*(int *)(iVar1 + 0xc) + *(int *)(iVar1 + 0x18) * 4,
             in_stack_00000014 + *in_stack_00000018 * 4,uVar4);
  *in_stack_00000018 = *in_stack_00000018 + uVar4;
  *(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + uVar4;
  uVar4 = *(uint *)(iVar1 + 0x10);
  if (uVar4 <= *(uint *)(iVar1 + 0x18)) {
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + uVar4;
    *(undefined4 *)(iVar1 + 0x18) = 0;
  }
  return uVar4;
}



/* grim_jpg_coeff_block_to_samples @ 1003123a */

void __cdecl grim_jpg_coeff_block_to_samples(int param_1,char param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  puVar2 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x1c);
  *(undefined4 **)(param_1 + 0x188) = puVar2;
  *puVar2 = &LAB_10031194;
  puVar2[2] = 0;
  puVar2[3] = 0;
  if (*(char *)(param_1 + 0x4a) != '\0') {
    iVar5 = *(int *)(param_1 + 0x110);
    puVar2[4] = iVar5;
    if (param_2 == '\0') {
      uVar4 = (**(code **)(*(int *)(param_1 + 4) + 8))
                        (param_1,1,*(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c),iVar5);
      puVar2[3] = uVar4;
    }
    else {
      iVar1 = *(int *)(param_1 + 4);
      iVar3 = grim_fpu_set_precision(*(int *)(param_1 + 0x60),iVar5);
      uVar4 = (**(code **)(iVar1 + 0x10))
                        (param_1,1,0,*(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c),iVar3,iVar5)
      ;
      puVar2[2] = uVar4;
    }
  }
  return;
}



/* grim_jpg_coeff_multiply_add @ 100312d7 */

/* [binja] int32_t* sub_100312d7(void* arg1, int32_t arg2, int32_t* arg3, int32_t arg4, int32_t*
   arg5, int32_t arg6) */

int * __cdecl grim_jpg_coeff_multiply_add(void *arg1,int arg2,int *arg3,int arg4,int *arg5,int arg6)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  int in_stack_0000001c;
  int local_8;
  
  pvVar3 = arg1;
  iVar2 = *(int *)((int)arg1 + 0x19c);
  if (*(int *)((int)arg1 + 0x110) <= *(int *)(iVar2 + 0x5c)) {
    arg1 = (void *)0x0;
    local_8 = *(int *)((int)pvVar3 + 0xc4);
    if (0 < *(int *)((int)pvVar3 + 0x20)) {
      iVar4 = iVar2 + 0xc;
      do {
        (**(code **)(iVar4 + 0x28))
                  (pvVar3,local_8,
                   *(int *)(arg2 + (int)arg1 * 4) + *(int *)(iVar4 + 0x58) * *arg3 * 4,iVar4);
        local_8 = local_8 + 0x54;
        arg1 = (void *)((int)arg1 + 1);
        iVar4 = iVar4 + 4;
      } while ((int)arg1 < *(int *)((int)pvVar3 + 0x20));
    }
    *(undefined4 *)(iVar2 + 0x5c) = 0;
  }
  uVar5 = *(int *)((int)pvVar3 + 0x110) - *(int *)(iVar2 + 0x5c);
  if (*(uint *)(iVar2 + 0x60) < uVar5) {
    uVar5 = *(uint *)(iVar2 + 0x60);
  }
  uVar1 = in_stack_0000001c - *(int *)arg6;
  if (uVar1 < uVar5) {
    uVar5 = uVar1;
  }
  (**(code **)(*(int *)((int)pvVar3 + 0x1a0) + 4))
            (pvVar3,iVar2 + 0xc,*(undefined4 *)(iVar2 + 0x5c),arg5 + *(int *)arg6,uVar5);
  *(uint *)arg6 = *(int *)arg6 + uVar5;
  *(int *)(iVar2 + 0x60) = *(int *)(iVar2 + 0x60) - uVar5;
  *(int *)(iVar2 + 0x5c) = *(int *)(iVar2 + 0x5c) + uVar5;
  if (*(int *)((int)pvVar3 + 0x110) <= *(int *)(iVar2 + 0x5c)) {
    *arg3 = *arg3 + 1;
    arg6 = (int)arg3;
  }
  return (int *)arg6;
}



/* grim_jpg_coeff_apply_quant_scale @ 100313b0 */

void __cdecl grim_jpg_coeff_apply_quant_scale(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined1 *puVar10;
  undefined4 *puVar11;
  int local_c;
  
  iVar3 = *param_4;
  iVar5 = *(int *)(param_1 + 0x19c) + param_2[1];
  bVar1 = *(byte *)(iVar5 + 0x8c);
  uVar7 = (uint)bVar1;
  uVar6 = (uint)*(byte *)(iVar5 + 0x96);
  local_c = 0;
  if (0 < *(int *)(param_1 + 0x110)) {
    param_2 = param_3;
    do {
      puVar10 = (undefined1 *)*param_2;
      puVar4 = *(undefined4 **)(iVar3 + local_c * 4);
      puVar8 = (undefined4 *)(*(int *)(param_1 + 0x5c) + (int)puVar4);
      while (puVar4 < puVar8) {
        uVar2 = *puVar10;
        puVar10 = puVar10 + 1;
        if (uVar7 != 0) {
          puVar11 = puVar4;
          for (uVar9 = (uint)(bVar1 >> 2); uVar9 != 0; uVar9 = uVar9 - 1) {
            *puVar11 = CONCAT22(CONCAT11(uVar2,uVar2),CONCAT11(uVar2,uVar2));
            puVar11 = puVar11 + 1;
          }
          for (uVar9 = uVar7 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined1 *)puVar11 = uVar2;
            puVar11 = (undefined4 *)((int)puVar11 + 1);
          }
          puVar4 = (undefined4 *)((int)puVar4 + uVar7);
        }
      }
      if (1 < uVar6) {
        grim_fpu_set_round_and_precision(iVar3,local_c,iVar3,local_c + 1,uVar6 - 1,*(uint *)(param_1 + 0x5c));
      }
      local_c = local_c + uVar6;
      param_2 = param_2 + 1;
    } while (local_c < *(int *)(param_1 + 0x110));
  }
  return;
}



/* grim_jpg_coeff_clamp @ 1003148d */

/* [binja] int32_t* sub_1003148d(int32_t* arg1, int32_t arg2, int32_t* arg3) */

int * __cdecl grim_jpg_coeff_clamp(int *arg1,int arg2,int *arg3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int *piVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  int *in_stack_00000010;
  
  piVar3 = in_stack_00000010;
  in_stack_00000010 = (int *)0x0;
  puVar6 = (undefined4 *)*piVar3;
  if (0 < arg1[0x44]) {
    iVar5 = (int)arg3 - (int)puVar6;
    do {
      puVar2 = (undefined1 *)*puVar6;
      puVar7 = *(undefined1 **)(iVar5 + (int)puVar6);
      puVar4 = puVar2 + arg1[0x17];
      for (; puVar2 < puVar4; puVar2 = puVar2 + 2) {
        uVar1 = *puVar7;
        puVar7 = puVar7 + 1;
        *puVar2 = uVar1;
        puVar2[1] = uVar1;
      }
      piVar3 = (int *)((int)in_stack_00000010 + 1);
      puVar6 = puVar6 + 1;
      in_stack_00000010 = piVar3;
    } while ((int)piVar3 < arg1[0x44]);
  }
  return piVar3;
}



/* grim_jpg_coeff_inverse_scale @ 100314e4 */

/* [binja] int32_t* sub_100314e4(void* arg1, int32_t* arg2, int32_t* arg3) */

int * __cdecl grim_jpg_coeff_inverse_scale(void *arg1,int *arg2,int *arg3)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 *puVar3;
  int *piVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  int iVar7;
  int *in_stack_00000010;
  
  iVar2 = *in_stack_00000010;
  iVar7 = 0;
  piVar4 = in_stack_00000010;
  if (0 < *(int *)((int)arg1 + 0x110)) {
    in_stack_00000010 = arg3;
    do {
      puVar6 = (undefined1 *)*in_stack_00000010;
      puVar5 = *(undefined1 **)(iVar2 + iVar7 * 4);
      puVar3 = puVar5 + *(int *)((int)arg1 + 0x5c);
      for (; puVar5 < puVar3; puVar5 = puVar5 + 2) {
        uVar1 = *puVar6;
        puVar6 = puVar6 + 1;
        *puVar5 = uVar1;
        puVar5[1] = uVar1;
      }
      piVar4 = (int *)grim_fpu_set_round_and_precision(iVar2,iVar7,iVar2,iVar7 + 1,1,*(uint *)((int)arg1 + 0x5c));
      in_stack_00000010 = in_stack_00000010 + 1;
      iVar7 = iVar7 + 2;
    } while (iVar7 < *(int *)((int)arg1 + 0x110));
  }
  return piVar4;
}



/* grim_jpg_coeff_pack_output @ 1003154e */

void __cdecl grim_jpg_coeff_pack_output(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  puVar7 = param_4;
  param_4 = (undefined4 *)0x0;
  puVar7 = (undefined4 *)*puVar7;
  if (0 < *(int *)(param_1 + 0x110)) {
    iVar6 = param_3 - (int)puVar7;
    do {
      pbVar4 = *(byte **)(iVar6 + (int)puVar7);
      bVar2 = *pbVar4;
      pbVar3 = (byte *)*puVar7;
      *pbVar3 = bVar2;
      pbVar4 = pbVar4 + 1;
      pbVar3[1] = (byte)((int)((uint)bVar2 * 3 + 2 + (uint)*pbVar4) >> 2);
      for (iVar5 = *(int *)(param_2 + 0x28) + -2; pbVar3 = pbVar3 + 2, iVar5 != 0;
          iVar5 = iVar5 + -1) {
        bVar2 = *pbVar4;
        pbVar1 = pbVar4 + -1;
        pbVar4 = pbVar4 + 1;
        *pbVar3 = (byte)((int)(*pbVar1 + 1 + (uint)bVar2 * 3) >> 2);
        pbVar3[1] = (byte)((int)(*pbVar4 + 2 + (uint)bVar2 * 3) >> 2);
      }
      bVar2 = *pbVar4;
      param_4 = (undefined4 *)((int)param_4 + 1);
      *pbVar3 = (byte)((int)(pbVar4[-1] + 1 + (uint)bVar2 * 3) >> 2);
      pbVar3[1] = bVar2;
      puVar7 = puVar7 + 1;
    } while ((int)param_4 < *(int *)(param_1 + 0x110));
  }
  return;
}



/* grim_jpg_coeff_dequant_and_scale @ 100315f2 */

void __cdecl grim_jpg_coeff_dequant_and_scale(int param_1,int param_2,undefined4 *param_3,int *param_4)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  int local_8;
  
  iVar1 = *param_4;
  local_8 = 0;
  if (0 < *(int *)(param_1 + 0x110)) {
    do {
      param_4 = (int *)0x0;
      do {
        pbVar6 = (byte *)*param_3;
        if (param_4 == (int *)0x0) {
          pbVar8 = (byte *)param_3[-1];
        }
        else {
          pbVar8 = (byte *)param_3[1];
        }
        puVar2 = *(undefined1 **)(iVar1 + local_8 * 4);
        local_8 = local_8 + 1;
        iVar5 = (uint)*pbVar6 * 3 + (uint)*pbVar8;
        iVar3 = (uint)pbVar6[1] * 3 + (uint)pbVar8[1];
        *puVar2 = (char)(iVar5 * 4 + 8 >> 4);
        pbVar8 = pbVar8 + 2;
        pbVar6 = pbVar6 + 2;
        puVar2[1] = (char)(iVar5 * 3 + 7 + iVar3 >> 4);
        for (iVar7 = *(int *)(param_2 + 0x28) + -2; puVar2 = puVar2 + 2, iVar7 != 0;
            iVar7 = iVar7 + -1) {
          iVar4 = (uint)*pbVar6 * 3 + (uint)*pbVar8;
          *puVar2 = (char)(iVar3 * 3 + 8 + iVar5 >> 4);
          pbVar8 = pbVar8 + 1;
          pbVar6 = pbVar6 + 1;
          puVar2[1] = (char)(iVar3 * 3 + 7 + iVar4 >> 4);
          iVar5 = iVar3;
          iVar3 = iVar4;
        }
        param_4 = (int *)((int)param_4 + 1);
        *puVar2 = (char)(iVar3 * 3 + 8 + iVar5 >> 4);
        puVar2[1] = (char)(iVar3 * 4 + 7 >> 4);
      } while ((int)param_4 < 2);
      param_3 = param_3 + 1;
    } while (local_8 < *(int *)(param_1 + 0x110));
  }
  return;
}



/* grim_jpg_coeff_pipeline_setup @ 100316f9 */

void __cdecl grim_jpg_coeff_pipeline_setup(int *param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int *piVar8;
  int iVar9;
  undefined1 local_10;
  int local_c;
  
  puVar3 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0xa0);
  param_1[0x67] = (int)puVar3;
  *(undefined1 *)(puVar3 + 2) = 0;
  *puVar3 = &LAB_100312bd;
  puVar3[1] = grim_jpg_coeff_multiply_add;
  if ((char)param_1[0x42] != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x17;
    (**(code **)*param_1)(param_1);
  }
  if (((char)param_1[0x12] == '\0') || (param_1[0x45] < 2)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  local_c = 0;
  if (0 < param_1[8]) {
    puVar7 = puVar3 + 0xd;
    piVar8 = (int *)(param_1[0x31] + 0x24);
    do {
      iVar4 = (piVar8[-7] * *piVar8) / param_1[0x45];
      iVar5 = (piVar8[-6] * *piVar8) / param_1[0x45];
      iVar9 = param_1[0x44];
      iVar1 = param_1[0x43];
      puVar7[0xc] = iVar5;
      if ((char)piVar8[3] == '\0') {
        *puVar7 = &LAB_100313a8;
      }
      else if ((iVar4 == iVar1) && (iVar5 == iVar9)) {
        *puVar7 = &LAB_1003139d;
      }
      else {
        if (iVar4 * 2 == iVar1) {
          if (iVar5 == iVar9) {
            if ((bVar2) && (2 < (uint)piVar8[1])) {
              *puVar7 = grim_jpg_coeff_pack_output;
            }
            else {
              *puVar7 = grim_jpg_coeff_clamp;
            }
          }
          else {
            if ((iVar4 * 2 != iVar1) || (iVar5 * 2 != iVar9)) goto LAB_1003182e;
            if ((bVar2) && (2 < (uint)piVar8[1])) {
              *puVar7 = grim_jpg_coeff_dequant_and_scale;
              *(undefined1 *)(puVar3 + 2) = 1;
            }
            else {
              *puVar7 = grim_jpg_coeff_inverse_scale;
            }
          }
        }
        else {
LAB_1003182e:
          if ((iVar1 % iVar4 == 0) && (iVar9 % iVar5 == 0)) {
            local_10 = (undefined1)(iVar1 / iVar4);
            *puVar7 = grim_jpg_coeff_apply_quant_scale;
            *(undefined1 *)(local_c + 0x8c + (int)puVar3) = local_10;
            *(char *)(local_c + 0x96 + (int)puVar3) = (char)(iVar9 / iVar5);
          }
          else {
            *(undefined4 *)(*param_1 + 0x14) = 0x25;
            (**(code **)*param_1)(param_1);
          }
        }
        iVar9 = param_1[0x44];
        iVar1 = param_1[1];
        iVar4 = grim_fpu_set_precision(param_1[0x17],param_1[0x43]);
        uVar6 = (**(code **)(iVar1 + 8))(param_1,1,iVar4,iVar9);
        puVar7[-10] = uVar6;
      }
      local_c = local_c + 1;
      puVar7 = puVar7 + 1;
      piVar8 = piVar8 + 0x15;
    } while (local_c < param_1[8]);
  }
  return;
}



/* grim_jpg_coeff_row_process_a @ 100318ba */

void grim_jpg_coeff_row_process_a(void)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = *(int *)(in_EAX + 0x1a0);
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 8) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0xc) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x10) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  iVar3 = 0;
  iVar5 = 0x5b6900;
  local_c = -0xe25100;
  local_8 = -0xb2f480;
  iVar4 = 0x2c8d00;
  do {
    *(int *)(iVar3 + *(int *)(iVar1 + 8)) = local_8 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0xc)) = local_c >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x10)) = iVar5;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x14)) = iVar4;
    iVar4 = iVar4 + -0x581a;
    iVar5 = iVar5 + -0xb6d2;
    iVar3 = iVar3 + 4;
    local_c = local_c + 0x1c5a2;
    local_8 = local_8 + 0x166e9;
  } while (-0x2b34e7 < iVar4);
  return;
}



/* grim_jpg_coeff_row_process_b @ 1003196a */

void __cdecl grim_jpg_coeff_row_process_b(int param_1,int param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x20);
  iVar3 = *(int *)(param_1 + 0x5c);
  if (-1 < param_5 + -1) {
    iVar7 = param_3 << 2;
    local_8 = param_5;
    do {
      iVar6 = 0;
      if (0 < iVar2) {
        do {
          puVar5 = *(undefined1 **)(iVar7 + *(int *)(param_2 + iVar6 * 4));
          puVar4 = (undefined1 *)(*param_4 + iVar6);
          for (iVar1 = iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar4 = *puVar5;
            puVar4 = puVar4 + iVar2;
            puVar5 = puVar5 + 1;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar2);
      }
      iVar7 = iVar7 + 4;
      param_4 = param_4 + 1;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  return;
}



/* grim_jpg_coeff_row_prescale @ 100319d5 */

void __cdecl grim_jpg_coeff_row_prescale(int param_1,int *param_2,int param_3,int param_4,int param_5)

{
  grim_fpu_set_round_and_precision(*param_2,param_3,param_4,0,param_5,*(uint *)(param_1 + 0x5c));
  return;
}



/* grim_jpg_coeff_row_postscale @ 100319f8 */

void __cdecl grim_jpg_coeff_row_postscale(int param_1,int *param_2,int param_3,undefined4 *param_4,int param_5)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined1 *puVar12;
  byte *pbVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int local_c;
  int local_8;
  
  iVar6 = *(int *)(param_1 + 0x1a0);
  iVar7 = *(int *)(param_1 + 0x5c);
  iVar8 = *(int *)(param_1 + 0x11c);
  iVar9 = *(int *)(iVar6 + 8);
  iVar10 = *(int *)(iVar6 + 0xc);
  iVar11 = *(int *)(iVar6 + 0x10);
  iVar6 = *(int *)(iVar6 + 0x14);
  if (-1 < param_5 + -1) {
    iVar14 = param_3 << 2;
    local_c = param_5;
    do {
      piVar1 = (int *)(iVar14 + *param_2);
      pbVar13 = *(byte **)(iVar14 + param_2[1]);
      piVar2 = (int *)(iVar14 + param_2[2]);
      piVar3 = (int *)(iVar14 + param_2[3]);
      iVar14 = iVar14 + 4;
      if (iVar7 != 0) {
        iVar17 = *piVar1 - (int)pbVar13;
        iVar18 = *piVar2 - (int)pbVar13;
        iVar15 = *piVar3 - (int)pbVar13;
        puVar12 = (undefined1 *)*param_4;
        local_8 = iVar7;
        do {
          uVar16 = (uint)pbVar13[iVar17];
          bVar4 = *pbVar13;
          bVar5 = pbVar13[iVar18];
          *puVar12 = *(undefined1 *)(((iVar8 - *(int *)((uint)bVar5 * 4 + iVar9)) - uVar16) + 0xff);
          puVar12[1] = *(undefined1 *)
                        (((iVar8 - (*(int *)((uint)bVar4 * 4 + iVar6) +
                                    *(int *)((uint)bVar5 * 4 + iVar11) >> 0x10)) - uVar16) + 0xff);
          puVar12[2] = *(undefined1 *)
                        (((iVar8 - *(int *)((uint)bVar4 * 4 + iVar10)) - uVar16) + 0xff);
          puVar12[3] = pbVar13[iVar15];
          pbVar13 = pbVar13 + 1;
          local_8 = local_8 + -1;
          puVar12 = puVar12 + 4;
        } while (local_8 != 0);
      }
      local_c = local_c + -1;
      param_4 = param_4 + 1;
    } while (local_c != 0);
  }
  return;
}



/* grim_jpg_coeff_row_accumulate @ 10031b2a */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
grim_jpg_coeff_row_accumulate(uint param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,uint *param_5)

{
  undefined4 uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  ushort uVar6;
  undefined7 uVar7;
  uint uVar8;
  byte bVar9;
  undefined2 uVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  undefined2 uVar15;
  undefined8 uVar14;
  uint uVar16;
  undefined2 uVar21;
  undefined8 uVar17;
  undefined2 uVar20;
  undefined2 uVar22;
  undefined8 uVar18;
  ulonglong uVar19;
  undefined8 uVar23;
  undefined2 uVar25;
  undefined2 uVar26;
  undefined8 uVar24;
  undefined8 uVar27;
  
  uVar8 = param_1 >> 2;
  do {
    uVar12 = *param_2;
    uVar1 = *param_3;
    uVar6 = (ushort)(((uint7)(byte)((uint)uVar12 >> 0x18) << 0x30) >> 0x28);
    uVar7 = CONCAT25(uVar6,CONCAT14((char)((uint)uVar12 >> 0x10),uVar12));
    uVar19 = (ulonglong)
             CONCAT41((int)(CONCAT34((int3)((uint7)uVar7 >> 0x20),uVar12) >> 0x18),
                      (char)((uint)uVar12 >> 8)) & 0xffffffff00ff;
    bVar9 = (byte)uVar12;
    uVar12 = *param_4;
    uVar13 = psubsw((ulonglong)
                    CONCAT52((int5)(CONCAT43((int)(CONCAT34((int3)(CONCAT25((short)(((uint7)(byte)((
                                                  uint)uVar1 >> 0x18) << 0x30) >> 0x28),
                                                  CONCAT14((char)((uint)uVar1 >> 0x10),uVar1)) >>
                                                  0x20),uVar1) >> 0x18),
                                             CONCAT12((char)((uint)uVar1 >> 8),(short)uVar1)) >>
                                   0x10),(short)uVar1) & 0xffffffff00ff00ff,_DAT_10055840);
    uVar17 = psubsw((ulonglong)
                    CONCAT52(CONCAT41((int)(CONCAT34((int3)(CONCAT25((short)(((uint7)(byte)((uint)
                                                  uVar12 >> 0x18) << 0x30) >> 0x28),
                                                  CONCAT14((char)((uint)uVar12 >> 0x10),uVar12)) >>
                                                  0x20),uVar12) >> 0x18),(char)((uint)uVar12 >> 8)),
                             (ushort)(byte)uVar12) & 0xffffffff00ffffff,_DAT_10055840);
    uVar20 = (undefined2)((ulonglong)uVar17 >> 0x10);
    uVar15 = (undefined2)((ulonglong)uVar13 >> 0x10);
    uVar14 = pmaddwd(CONCAT44(CONCAT22(uVar20,uVar15),CONCAT22((short)uVar17,(short)uVar13)),
                     _DAT_10055848);
    uVar11 = psllw(CONCAT62((int6)uVar19,(ushort)bVar9),8);
    uVar25 = (undefined2)((ulonglong)uVar13 >> 0x20);
    uVar21 = (undefined2)((ulonglong)uVar17 >> 0x20);
    uVar26 = (undefined2)((ulonglong)uVar13 >> 0x30);
    uVar22 = (undefined2)((ulonglong)uVar17 >> 0x30);
    uVar24 = pmaddwd(CONCAT26(uVar22,CONCAT24(uVar26,CONCAT22(uVar21,uVar25))),_DAT_10055848);
    uVar10 = (undefined2)uVar19;
    uVar17 = pmaddwd(CONCAT44(CONCAT22(uVar10,uVar20),(uint)CONCAT12(bVar9,(short)uVar17)),
                     _DAT_10055850);
    uVar23 = pmaddwd(CONCAT44(CONCAT22(uVar10,uVar15),(uint)CONCAT12(bVar9,(short)uVar13)),
                     _DAT_10055858);
    uVar10 = (undefined2)((uint7)uVar7 >> 0x20);
    uVar6 = uVar6 >> 8;
    uVar27 = pmaddwd(CONCAT26(uVar6,CONCAT24(uVar26,CONCAT22(uVar10,uVar25))),_DAT_10055858);
    uVar13 = pmaddwd(CONCAT26(uVar6,CONCAT24(uVar22,CONCAT22(uVar10,uVar21))),_DAT_10055850);
    uVar18 = packssdw(CONCAT44((int)((int)uVar14 + (uint)(ushort)uVar11) >> 8,(int)uVar17 >> 8),
                      CONCAT44(DAT_1005dba0,(int)uVar23 >> 8));
    uVar17 = packssdw(CONCAT44((int)((int)((ulonglong)uVar14 >> 0x20) +
                                    (uint)(ushort)((ulonglong)uVar11 >> 0x10)) >> 8,
                               (int)((longlong)uVar17 >> 0x28)),
                      CONCAT44(DAT_1005dba4,(int)((longlong)uVar23 >> 0x28)));
    sVar2 = (short)uVar18;
    sVar3 = (short)((ulonglong)uVar18 >> 0x10);
    sVar4 = (short)((ulonglong)uVar18 >> 0x20);
    sVar5 = (short)((ulonglong)uVar18 >> 0x30);
    uVar16 = CONCAT13((0 < sVar5) * (sVar5 < 0x100) * (char)((ulonglong)uVar18 >> 0x30) -
                      (0xff < sVar5),
                      CONCAT12((0 < sVar4) * (sVar4 < 0x100) * (char)((ulonglong)uVar18 >> 0x20) -
                               (0xff < sVar4),
                               CONCAT11((0 < sVar3) * (sVar3 < 0x100) *
                                        (char)((ulonglong)uVar18 >> 0x10) - (0xff < sVar3),
                                        (0 < sVar2) * (sVar2 < 0x100) * (char)uVar18 -
                                        (0xff < sVar2))));
    sVar2 = (short)uVar17;
    sVar3 = (short)((ulonglong)uVar17 >> 0x10);
    sVar4 = (short)((ulonglong)uVar17 >> 0x20);
    uVar14 = packssdw(CONCAT44((int)((int)uVar24 + (uint)(ushort)((ulonglong)uVar11 >> 0x20)) >> 8,
                               (int)uVar13 >> 8),CONCAT44(DAT_1005dba0,(int)uVar27 >> 8));
    uVar19 = CONCAT16((0 < sVar4) * (sVar4 < 0x100) * (char)((ulonglong)uVar17 >> 0x20) -
                      (0xff < sVar4),
                      CONCAT15((0 < sVar3) * (sVar3 < 0x100) * (char)((ulonglong)uVar17 >> 0x10) -
                               (0xff < sVar3),
                               CONCAT14((0 < sVar2) * (sVar2 < 0x100) * (char)uVar17 -
                                        (0xff < sVar2),uVar16))) & _DAT_10055860;
    uVar11 = packssdw(CONCAT44((int)((int)((ulonglong)uVar24 >> 0x20) +
                                    (uint)(ushort)((ulonglong)uVar11 >> 0x30)) >> 8,
                               (int)((longlong)uVar13 >> 0x28)),
                      CONCAT44(DAT_1005dba4,(int)((longlong)uVar27 >> 0x28)));
    sVar2 = (short)uVar14;
    sVar3 = (short)((ulonglong)uVar14 >> 0x10);
    uVar10 = CONCAT11((0 < sVar3) * (sVar3 < 0x100) * (char)((ulonglong)uVar14 >> 0x10) -
                      (0xff < sVar3),(0 < sVar2) * (sVar2 < 0x100) * (char)uVar14 - (0xff < sVar2));
    sVar2 = (short)((ulonglong)uVar14 >> 0x20);
    sVar3 = (short)((ulonglong)uVar14 >> 0x30);
    uVar12 = CONCAT13((0 < sVar3) * (sVar3 < 0x100) * (char)((ulonglong)uVar14 >> 0x30) -
                      (0xff < sVar3),
                      CONCAT12((0 < sVar2) * (sVar2 < 0x100) * (char)((ulonglong)uVar14 >> 0x20) -
                               (0xff < sVar2),uVar10));
    sVar2 = (short)uVar11;
    sVar3 = (short)((ulonglong)uVar11 >> 0x10);
    sVar4 = (short)((ulonglong)uVar11 >> 0x20);
    param_2 = param_2 + 1;
    *param_5 = uVar16 | (uint)(uVar19 >> 8);
    param_4 = param_4 + 1;
    param_5[1] = CONCAT22(uVar10,(short)(uVar19 >> 0x28));
    param_3 = param_3 + 1;
    param_5[2] = (uint)(CONCAT16((0 < sVar4) * (sVar4 < 0x100) * (char)((ulonglong)uVar11 >> 0x20) -
                                 (0xff < sVar4),
                                 CONCAT15((0 < sVar3) * (sVar3 < 0x100) *
                                          (char)((ulonglong)uVar11 >> 0x10) - (0xff < sVar3),
                                          CONCAT14((0 < sVar2) * (sVar2 < 0x100) * (char)uVar11 -
                                                   (0xff < sVar2),uVar12))) >> 0x18) |
                 (uint)(((ulonglong)(ushort)((uint)uVar12 >> 0x10) << 0x30) >> 0x30);
    uVar8 = uVar8 - 1;
    param_5 = param_5 + 3;
  } while (uVar8 != 0);
  return;
}



/* grim_jpg_idct_prepare @ 10031c66 */

void __cdecl grim_jpg_idct_prepare(int param_1,int *param_2,int param_3,undefined4 *param_4,int param_5)

{
  int *piVar1;
  int *piVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  uint *puVar14;
  int iVar15;
  byte *pbVar16;
  undefined1 *puVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  uint local_1c;
  int local_18;
  
  iVar5 = *(int *)(param_1 + 0x1a0);
  iVar6 = *(int *)(param_1 + 0x11c);
  uVar7 = *(uint *)(param_1 + 0x5c);
  iVar8 = *(int *)(iVar5 + 8);
  iVar9 = *(int *)(iVar5 + 0xc);
  iVar10 = *(int *)(iVar5 + 0x10);
  iVar5 = *(int *)(iVar5 + 0x14);
  uVar21 = uVar7 & 0xfffffff8;
  if (grim_jpg_idct_mode == '\0') {
    if (-1 < param_5 + -1) {
      iVar15 = param_3 << 2;
      local_18 = param_5;
      do {
        piVar1 = (int *)(iVar15 + *param_2);
        pbVar16 = *(byte **)(iVar15 + param_2[1]);
        piVar2 = (int *)(iVar15 + param_2[2]);
        iVar15 = iVar15 + 4;
        if (uVar7 != 0) {
          iVar19 = *piVar1 - (int)pbVar16;
          iVar20 = *piVar2 - (int)pbVar16;
          puVar17 = (undefined1 *)*param_4;
          local_1c = uVar7;
          do {
            bVar3 = pbVar16[iVar20];
            uVar21 = (uint)pbVar16[iVar19];
            bVar4 = *pbVar16;
            *puVar17 = *(undefined1 *)(*(int *)((uint)bVar3 * 4 + iVar8) + uVar21 + iVar6);
            puVar17[1] = *(undefined1 *)
                          ((*(int *)((uint)bVar4 * 4 + iVar5) + *(int *)((uint)bVar3 * 4 + iVar10)
                           >> 0x10) + uVar21 + iVar6);
            pbVar16 = pbVar16 + 1;
            local_1c = local_1c - 1;
            puVar17[2] = *(undefined1 *)(*(int *)((uint)bVar4 * 4 + iVar9) + uVar21 + iVar6);
            puVar17 = puVar17 + 3;
          } while (local_1c != 0);
        }
        local_18 = local_18 + -1;
        param_4 = param_4 + 1;
      } while (local_18 != 0);
    }
  }
  else if (-1 < param_5 + -1) {
    iVar15 = param_3 << 2;
    local_1c = param_5;
    do {
      puVar11 = *(undefined4 **)(iVar15 + *param_2);
      puVar12 = *(undefined4 **)(iVar15 + param_2[1]);
      puVar13 = *(undefined4 **)(iVar15 + param_2[2]);
      iVar15 = iVar15 + 4;
      puVar14 = (uint *)*param_4;
      grim_jpg_coeff_row_accumulate(uVar21,puVar11,puVar12,puVar13,puVar14);
      if (uVar21 < uVar7) {
        pbVar16 = (byte *)((int)puVar12 + uVar21);
        local_18 = uVar7 - uVar21;
        puVar17 = (undefined1 *)((int)puVar14 + uVar21 * 3);
        do {
          bVar3 = pbVar16[(int)puVar13 - (int)puVar12];
          uVar18 = (uint)pbVar16[(int)puVar11 - (int)puVar12];
          bVar4 = *pbVar16;
          *puVar17 = *(undefined1 *)(*(int *)((uint)bVar3 * 4 + iVar8) + uVar18 + iVar6);
          puVar17[1] = *(undefined1 *)
                        ((*(int *)((uint)bVar4 * 4 + iVar5) + *(int *)((uint)bVar3 * 4 + iVar10) >>
                         0x10) + uVar18 + iVar6);
          pbVar16 = pbVar16 + 1;
          local_18 = local_18 + -1;
          puVar17[2] = *(undefined1 *)(*(int *)((uint)bVar4 * 4 + iVar9) + uVar18 + iVar6);
          puVar17 = puVar17 + 3;
        } while (local_18 != 0);
      }
      local_1c = local_1c + -1;
      param_4 = param_4 + 1;
    } while (local_1c != 0);
  }
  return;
}



/* grim_jpg_coeff_transform_setup @ 10031e84 */

void __cdecl grim_jpg_coeff_transform_setup(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x18);
  param_1[0x68] = (int)puVar1;
  *puVar1 = &grim_jpg_error_handler;
  iVar2 = param_1[9];
  if (iVar2 == 1) {
    bVar4 = param_1[8] == 1;
LAB_10031ed3:
    if (!bVar4) {
LAB_10031ed5:
      *(undefined4 *)(*param_1 + 0x14) = 8;
      (**(code **)*param_1)(param_1);
    }
  }
  else {
    if (1 < iVar2) {
      if (iVar2 < 4) {
        bVar4 = param_1[8] == 3;
      }
      else {
        if (5 < iVar2) goto LAB_10031ec9;
        bVar4 = param_1[8] == 4;
      }
      goto LAB_10031ed3;
    }
LAB_10031ec9:
    if (param_1[8] < 1) goto LAB_10031ed5;
  }
  iVar2 = param_1[10];
  if (iVar2 == 1) {
    iVar2 = 1;
    param_1[0x19] = 1;
    if ((param_1[9] == 1) || (param_1[9] == 3)) {
      puVar1[1] = grim_jpg_coeff_row_prescale;
      if (1 < param_1[8]) {
        iVar3 = 0x54;
        do {
          *(undefined1 *)(param_1[0x31] + 0x30 + iVar3) = 0;
          iVar2 = iVar2 + 1;
          iVar3 = iVar3 + 0x54;
        } while (iVar2 < param_1[8]);
      }
      goto LAB_10031f8c;
    }
  }
  else if (iVar2 == 2) {
    param_1[0x19] = 3;
    if (param_1[9] == 3) {
      puVar1[1] = grim_jpg_idct_prepare;
      goto LAB_10031f3f;
    }
    bVar4 = param_1[9] == 2;
LAB_10031f4b:
    if (bVar4) goto LAB_10031f4d;
  }
  else {
    if (iVar2 == 4) {
      param_1[0x19] = 4;
      if (param_1[9] != 5) {
        bVar4 = param_1[9] == 4;
        goto LAB_10031f4b;
      }
      puVar1[1] = grim_jpg_coeff_row_postscale;
LAB_10031f3f:
      grim_jpg_coeff_row_process_a();
      goto LAB_10031f8c;
    }
    if (iVar2 == param_1[9]) {
      param_1[0x19] = param_1[8];
LAB_10031f4d:
      puVar1[1] = grim_jpg_coeff_row_process_b;
      goto LAB_10031f8c;
    }
  }
  *(undefined4 *)(*param_1 + 0x14) = 0x19;
  (**(code **)*param_1)(param_1);
LAB_10031f8c:
  if (*(char *)((int)param_1 + 0x4a) == '\0') {
    param_1[0x1a] = param_1[0x19];
  }
  else {
    param_1[0x1a] = 1;
  }
  return;
}



/* grim_jpg_coeff_col_process_a @ 10031fa5 */

void grim_jpg_coeff_col_process_a(void)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = *(int *)(in_EAX + 0x19c);
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x10) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x18) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  *(undefined4 *)(iVar1 + 0x1c) = uVar2;
  iVar3 = 0;
  iVar5 = 0x5b6900;
  local_c = -0xe25100;
  local_8 = -0xb2f480;
  iVar4 = 0x2c8d00;
  do {
    *(int *)(iVar3 + *(int *)(iVar1 + 0x10)) = local_8 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x14)) = local_c >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x18)) = iVar5;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x1c)) = iVar4;
    iVar4 = iVar4 + -0x581a;
    iVar5 = iVar5 + -0xb6d2;
    iVar3 = iVar3 + 4;
    local_c = local_c + 0x1c5a2;
    local_8 = local_8 + 0x166e9;
  } while (-0x2b34e7 < iVar4);
  return;
}



/* grim_jpg_coeff_col_prescale @ 1003206a */

void __cdecl
grim_jpg_coeff_col_prescale(int param_1,undefined4 param_2,int *param_3,undefined4 param_4,int param_5,int *param_6
            ,int param_7)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar3 = *(int *)(param_1 + 0x19c);
  if (*(char *)(iVar3 + 0x24) == '\0') {
    uVar4 = 2;
    if (*(uint *)(iVar3 + 0x2c) < 2) {
      uVar4 = *(uint *)(iVar3 + 0x2c);
    }
    uVar2 = param_7 - *param_6;
    if (uVar2 < uVar4) {
      uVar4 = uVar2;
    }
    puVar1 = (undefined4 *)(param_5 + *param_6 * 4);
    local_c = *puVar1;
    if (uVar4 < 2) {
      local_8 = *(undefined4 *)(iVar3 + 0x20);
      *(undefined1 *)(iVar3 + 0x24) = 1;
    }
    else {
      local_8 = puVar1[1];
    }
    (**(code **)(iVar3 + 0xc))(param_1,param_2,*param_3,&local_c);
  }
  else {
    uVar4 = 1;
    grim_fpu_set_round_and_precision(iVar3 + 0x20,0,param_5 + *param_6 * 4,0,1,*(uint *)(iVar3 + 0x28));
    *(undefined1 *)(iVar3 + 0x24) = 0;
  }
  *param_6 = *param_6 + uVar4;
  *(int *)(iVar3 + 0x2c) = *(int *)(iVar3 + 0x2c) - uVar4;
  if (*(char *)(iVar3 + 0x24) == '\0') {
    *param_3 = *param_3 + 1;
  }
  return;
}



/* grim_jpg_coeff_col_init @ 10032110 */

/* [binja] int32_t sub_10032110(void* arg1, int32_t arg2, int32_t* arg3, int32_t arg4, int32_t*
   arg5) */

int __cdecl grim_jpg_coeff_col_init(void *arg1,int arg2,int *arg3,int arg4,int *arg5)

{
  int iVar1;
  int *in_stack_00000018;
  
  iVar1 = (**(code **)(*(int *)((int)arg1 + 0x19c) + 0xc))
                    (arg1,arg2,*arg3,arg5 + *in_stack_00000018);
  *in_stack_00000018 = *in_stack_00000018 + 1;
  *arg3 = *arg3 + 1;
  return iVar1;
}



/* grim_jpg_coeff_col_accumulate_a @ 10032141 */

void __cdecl grim_jpg_coeff_col_accumulate_a(int param_1,int *param_2,int param_3,undefined4 *param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined1 *puVar11;
  byte *pbVar12;
  uint uVar13;
  uint uVar14;
  byte *pbVar15;
  int iVar16;
  byte *pbVar17;
  
  iVar3 = *(int *)(param_1 + 0x19c);
  iVar4 = *(int *)(iVar3 + 0x10);
  iVar5 = *(int *)(param_1 + 0x11c);
  iVar6 = *(int *)(iVar3 + 0x14);
  iVar7 = *(int *)(iVar3 + 0x18);
  iVar3 = *(int *)(iVar3 + 0x1c);
  iVar10 = param_3 * 4;
  pbVar17 = *(byte **)(iVar10 + *param_2);
  pbVar12 = *(byte **)(iVar10 + param_2[1]);
  pbVar15 = *(byte **)(iVar10 + param_2[2]);
  puVar11 = (undefined1 *)*param_4;
  for (uVar14 = *(uint *)(param_1 + 0x5c) >> 1; uVar14 != 0; uVar14 = uVar14 - 1) {
    bVar1 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    bVar2 = *pbVar15;
    pbVar15 = pbVar15 + 1;
    iVar10 = *(int *)((uint)bVar2 * 4 + iVar4);
    iVar16 = *(int *)((uint)bVar1 * 4 + iVar3);
    iVar8 = *(int *)((uint)bVar2 * 4 + iVar7);
    iVar9 = *(int *)((uint)bVar1 * 4 + iVar6);
    uVar13 = (uint)*pbVar17;
    *puVar11 = *(undefined1 *)(iVar10 + uVar13 + iVar5);
    iVar16 = iVar16 + iVar8 >> 0x10;
    puVar11[1] = *(undefined1 *)(uVar13 + iVar16 + iVar5);
    puVar11[2] = *(undefined1 *)(uVar13 + iVar9 + iVar5);
    uVar13 = (uint)pbVar17[1];
    puVar11[3] = *(undefined1 *)(iVar10 + uVar13 + iVar5);
    puVar11[4] = *(undefined1 *)(iVar16 + uVar13 + iVar5);
    puVar11[5] = *(undefined1 *)(uVar13 + iVar9 + iVar5);
    pbVar17 = pbVar17 + 2;
    puVar11 = puVar11 + 6;
  }
  if ((*(byte *)(param_1 + 0x5c) & 1) != 0) {
    uVar14 = (uint)*pbVar17;
    iVar3 = *(int *)((uint)*pbVar12 * 4 + iVar3);
    iVar7 = *(int *)((uint)*pbVar15 * 4 + iVar7);
    iVar6 = *(int *)((uint)*pbVar12 * 4 + iVar6);
    *puVar11 = *(undefined1 *)(*(int *)((uint)*pbVar15 * 4 + iVar4) + uVar14 + iVar5);
    puVar11[1] = *(undefined1 *)(uVar14 + (iVar3 + iVar7 >> 0x10) + iVar5);
    puVar11[2] = *(undefined1 *)(uVar14 + iVar6 + iVar5);
  }
  return;
}



/* grim_jpg_coeff_col_accumulate_b @ 10032297 */

void __cdecl grim_jpg_coeff_col_accumulate_b(int param_1,int *param_2,int param_3,undefined4 *param_4)

{
  undefined4 *puVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 *puVar13;
  byte *pbVar14;
  uint uVar15;
  uint uVar16;
  undefined1 *puVar17;
  byte *pbVar18;
  int iVar19;
  int iVar20;
  
  iVar20 = *(int *)(param_1 + 0x19c);
  iVar4 = *(int *)(iVar20 + 0x10);
  iVar5 = *(int *)(param_1 + 0x11c);
  iVar6 = *(int *)(iVar20 + 0x14);
  iVar7 = *(int *)(iVar20 + 0x18);
  iVar20 = *(int *)(iVar20 + 0x1c);
  puVar1 = (undefined4 *)(*param_2 + param_3 * 8);
  pbVar8 = (byte *)*puVar1;
  pbVar9 = (byte *)puVar1[1];
  pbVar14 = *(byte **)(param_3 * 4 + param_2[1]);
  pbVar18 = *(byte **)(param_3 * 4 + param_2[2]);
  puVar13 = (undefined1 *)*param_4;
  puVar17 = (undefined1 *)param_4[1];
  for (uVar16 = *(uint *)(param_1 + 0x5c) >> 1; uVar16 != 0; uVar16 = uVar16 - 1) {
    bVar2 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    bVar3 = *pbVar18;
    pbVar18 = pbVar18 + 1;
    iVar10 = *(int *)((uint)bVar3 * 4 + iVar4);
    iVar19 = *(int *)((uint)bVar2 * 4 + iVar20);
    iVar11 = *(int *)((uint)bVar3 * 4 + iVar7);
    iVar12 = *(int *)((uint)bVar2 * 4 + iVar6);
    uVar15 = (uint)*pbVar8;
    *puVar13 = *(undefined1 *)(iVar10 + uVar15 + iVar5);
    iVar19 = iVar19 + iVar11 >> 0x10;
    puVar13[1] = *(undefined1 *)(uVar15 + iVar19 + iVar5);
    puVar13[2] = *(undefined1 *)(uVar15 + iVar12 + iVar5);
    uVar15 = (uint)pbVar8[1];
    puVar13[3] = *(undefined1 *)(iVar10 + uVar15 + iVar5);
    puVar13[4] = *(undefined1 *)(uVar15 + iVar19 + iVar5);
    puVar13[5] = *(undefined1 *)(uVar15 + iVar12 + iVar5);
    uVar15 = (uint)*pbVar9;
    pbVar8 = pbVar8 + 2;
    *puVar17 = *(undefined1 *)(iVar10 + uVar15 + iVar5);
    puVar17[1] = *(undefined1 *)(uVar15 + iVar19 + iVar5);
    puVar17[2] = *(undefined1 *)(uVar15 + iVar12 + iVar5);
    puVar13 = puVar13 + 6;
    uVar15 = (uint)pbVar9[1];
    pbVar9 = pbVar9 + 2;
    puVar17[3] = *(undefined1 *)(iVar10 + uVar15 + iVar5);
    puVar17[4] = *(undefined1 *)(iVar19 + uVar15 + iVar5);
    puVar17[5] = *(undefined1 *)(uVar15 + iVar12 + iVar5);
    puVar17 = puVar17 + 6;
  }
  if ((*(byte *)(param_1 + 0x5c) & 1) != 0) {
    iVar4 = *(int *)((uint)*pbVar18 * 4 + iVar4);
    iVar20 = *(int *)((uint)*pbVar14 * 4 + iVar20);
    iVar7 = *(int *)((uint)*pbVar18 * 4 + iVar7);
    iVar6 = *(int *)((uint)*pbVar14 * 4 + iVar6);
    uVar16 = (uint)*pbVar8;
    *puVar13 = *(undefined1 *)(iVar4 + uVar16 + iVar5);
    iVar20 = iVar20 + iVar7 >> 0x10;
    puVar13[1] = *(undefined1 *)(uVar16 + iVar20 + iVar5);
    puVar13[2] = *(undefined1 *)(uVar16 + iVar6 + iVar5);
    uVar16 = (uint)*pbVar9;
    *puVar17 = *(undefined1 *)(iVar4 + uVar16 + iVar5);
    puVar17[1] = *(undefined1 *)(uVar16 + iVar20 + iVar5);
    puVar17[2] = *(undefined1 *)(uVar16 + iVar6 + iVar5);
  }
  return;
}



/* grim_jpg_coeff_col_transform_setup @ 1003247d */

void __cdecl grim_jpg_coeff_col_transform_setup(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x30);
  *(undefined4 **)(param_1 + 0x19c) = puVar1;
  *(undefined1 *)(puVar1 + 2) = 0;
  *puVar1 = &LAB_10032055;
  puVar1[10] = *(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c);
  if (*(int *)(param_1 + 0x110) == 2) {
    puVar1[1] = grim_jpg_coeff_col_prescale;
    puVar1[3] = grim_jpg_coeff_col_accumulate_b;
    uVar2 = (**(code **)(*(int *)(param_1 + 4) + 4))(param_1,1,puVar1[10]);
    puVar1[8] = uVar2;
  }
  else {
    puVar1[8] = 0;
    puVar1[1] = grim_jpg_coeff_col_init;
    puVar1[3] = grim_jpg_coeff_col_accumulate_a;
  }
  grim_jpg_coeff_col_process_a();
  return;
}



/* grim_jpg_coeff_merge_a @ 100324f2 */

/* [binja] int16_t* sub_100324f2(int16_t* arg1, int16_t* arg2, int32_t arg3) */

short * __cdecl grim_jpg_coeff_merge_a(short *arg1,short *arg2,int arg3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int in_stack_00000010;
  
  iVar2 = *(int *)(arg1 + 0x2e);
  iVar3 = *(int *)(*(int *)(arg1 + 0xd2) + 0x18);
  iVar5 = 0;
  if (0 < in_stack_00000010) {
    do {
      pbVar4 = *(byte **)(arg2 + iVar5 * 2);
      arg1 = arg2;
      for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 + -1) {
        arg1 = (short *)(*(int *)(iVar3 + (uint)(*pbVar4 >> 3) * 4) +
                        ((uint)(pbVar4[1] >> 2) * 0x20 + (uint)(pbVar4[2] >> 3)) * 2);
        *arg1 = *arg1 + 1;
        if (*arg1 == 0) {
          *arg1 = -1;
        }
        pbVar4 = pbVar4 + 3;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < in_stack_00000010);
  }
  return arg1;
}



/* grim_jpg_coeff_merge_b @ 1003255e */

void grim_jpg_coeff_merge_b(void)

{
  short sVar1;
  int iVar2;
  int in_EAX;
  short *psVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  int *unaff_ESI;
  int iVar7;
  int local_2c;
  int local_24;
  short *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_24 = unaff_ESI[3];
  iVar2 = *(int *)(*(int *)(in_EAX + 0x1a4) + 0x18);
  local_1c = *unaff_ESI;
  local_10 = unaff_ESI[4];
  local_14 = unaff_ESI[1];
  local_2c = unaff_ESI[2];
  local_18 = unaff_ESI[5];
  iVar5 = local_1c;
  if (local_1c < local_14) {
    do {
      if (local_2c <= local_24) {
        psVar4 = (short *)(*(int *)(iVar2 + iVar5 * 4) + (local_2c * 0x20 + local_10) * 2);
        iVar6 = local_10;
        local_c = local_2c;
        psVar3 = psVar4;
        do {
          for (; iVar6 <= local_18; iVar6 = iVar6 + 1) {
            sVar1 = *psVar4;
            psVar4 = psVar4 + 1;
            if (sVar1 != 0) {
              *unaff_ESI = iVar5;
              local_1c = iVar5;
              goto LAB_100325fc;
            }
          }
          local_c = local_c + 1;
          psVar4 = psVar3 + 0x20;
          iVar6 = local_10;
          psVar3 = psVar4;
        } while (local_c <= local_24);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 <= local_14);
LAB_100325fc:
    iVar5 = local_14;
    if (local_1c < local_14) {
      do {
        if (local_2c <= local_24) {
          psVar4 = (short *)(*(int *)(iVar2 + iVar5 * 4) + (local_2c * 0x20 + local_10) * 2);
          iVar6 = local_10;
          local_c = local_2c;
          psVar3 = psVar4;
          do {
            for (; iVar6 <= local_18; iVar6 = iVar6 + 1) {
              sVar1 = *psVar4;
              psVar4 = psVar4 + 1;
              if (sVar1 != 0) {
                unaff_ESI[1] = iVar5;
                local_14 = iVar5;
                goto LAB_10032664;
              }
            }
            local_c = local_c + 1;
            psVar4 = psVar3 + 0x20;
            iVar6 = local_10;
            psVar3 = psVar4;
          } while (local_c <= local_24);
        }
        iVar5 = iVar5 + -1;
      } while (local_1c <= iVar5);
    }
  }
LAB_10032664:
  if (local_2c < local_24) {
    iVar6 = (local_2c * 0x20 + local_10) * 2;
    iVar5 = local_1c;
    local_c = local_2c;
    do {
      for (; iVar5 <= local_14; iVar5 = iVar5 + 1) {
        psVar4 = (short *)(*(int *)(iVar2 + iVar5 * 4) + iVar6);
        for (iVar7 = local_10; iVar7 <= local_18; iVar7 = iVar7 + 1) {
          sVar1 = *psVar4;
          psVar4 = psVar4 + 1;
          if (sVar1 != 0) {
            local_2c = local_c;
            unaff_ESI[2] = local_c;
            goto LAB_100326d1;
          }
        }
      }
      local_c = local_c + 1;
      iVar6 = iVar6 + 0x40;
      iVar5 = local_1c;
    } while (local_c <= local_24);
LAB_100326d1:
    if (local_2c < local_24) {
      iVar6 = (local_24 * 0x20 + local_10) * 2;
      iVar5 = local_1c;
      local_c = local_24;
      do {
        for (; iVar5 <= local_14; iVar5 = iVar5 + 1) {
          psVar4 = (short *)(*(int *)(iVar2 + iVar5 * 4) + iVar6);
          for (iVar7 = local_10; iVar7 <= local_18; iVar7 = iVar7 + 1) {
            sVar1 = *psVar4;
            psVar4 = psVar4 + 1;
            if (sVar1 != 0) {
              local_24 = local_c;
              unaff_ESI[3] = local_c;
              goto LAB_1003273d;
            }
          }
        }
        local_c = local_c + -1;
        iVar6 = iVar6 + -0x40;
        iVar5 = local_1c;
      } while (local_2c <= local_c);
    }
  }
LAB_1003273d:
  local_8 = local_10;
  if (local_10 < local_18) {
    do {
      local_20 = (short *)local_1c;
      if (local_1c <= local_14) {
        do {
          psVar4 = (short *)(*(int *)(iVar2 + (int)local_20 * 4) + (local_2c * 0x20 + local_8) * 2);
          for (iVar5 = local_2c; iVar5 <= local_24; iVar5 = iVar5 + 1) {
            if (*psVar4 != 0) {
              local_10 = local_8;
              unaff_ESI[4] = local_8;
              goto LAB_100327a1;
            }
            psVar4 = psVar4 + 0x20;
          }
          local_20 = (short *)((int)local_20 + 1);
        } while ((int)local_20 <= local_14);
      }
      local_8 = local_8 + 1;
    } while (local_8 <= local_18);
LAB_100327a1:
    local_8 = local_18;
    if (local_10 < local_18) {
      do {
        local_20 = (short *)local_1c;
        if (local_1c <= local_14) {
          do {
            psVar4 = (short *)(*(int *)(iVar2 + (int)local_20 * 4) + (local_2c * 0x20 + local_8) * 2
                              );
            for (iVar5 = local_2c; iVar5 <= local_24; iVar5 = iVar5 + 1) {
              if (*psVar4 != 0) {
                local_18 = local_8;
                unaff_ESI[5] = local_8;
                goto LAB_10032801;
              }
              psVar4 = psVar4 + 0x20;
            }
            local_20 = (short *)((int)local_20 + 1);
          } while ((int)local_20 <= local_14);
        }
        local_8 = local_8 + -1;
      } while (local_10 <= local_8);
    }
  }
LAB_10032801:
  iVar7 = (local_18 - local_10) * 8;
  iVar5 = (local_24 - local_2c) * 0xc;
  iVar6 = (local_14 - local_1c) * 0x10;
  local_c = 0;
  unaff_ESI[6] = iVar7 * iVar7 + iVar5 * iVar5 + iVar6 * iVar6;
  for (iVar5 = local_1c; iVar5 <= local_14; iVar5 = iVar5 + 1) {
    if (local_2c <= local_24) {
      psVar4 = (short *)(*(int *)(iVar2 + iVar5 * 4) + (local_2c * 0x20 + local_10) * 2);
      iVar6 = (local_24 - local_2c) + 1;
      do {
        if (local_10 <= local_18) {
          local_1c = (local_18 - local_10) + 1;
          local_20 = psVar4;
          do {
            if (*local_20 != 0) {
              local_c = local_c + 1;
            }
            local_20 = local_20 + 1;
            local_1c = local_1c + -1;
          } while (local_1c != 0);
        }
        psVar4 = psVar4 + 0x20;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  unaff_ESI[7] = local_c;
  return;
}



/* grim_jpg_coeff_merge_c @ 10032896 */

void __cdecl grim_jpg_coeff_merge_c(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int local_c;
  int local_8;
  
  if (param_3 < param_4) {
    local_8 = param_3 * 2;
    piVar6 = (int *)(param_3 * 0x20 + 0xc + param_2);
    do {
      piVar5 = (int *)0x0;
      iVar4 = 0;
      local_c = param_3;
      if (param_4 < local_8) {
        if (0 < local_8) {
          piVar1 = (int *)(param_2 + 0x18);
          do {
            if (iVar4 < *piVar1) {
              piVar5 = piVar1 + -6;
              iVar4 = *piVar1;
            }
            piVar1 = piVar1 + 8;
            local_c = local_c + -1;
          } while (local_c != 0);
        }
      }
      else if (0 < local_8) {
        piVar1 = (int *)(param_2 + 0x1c);
        do {
          if ((iVar4 < *piVar1) && (0 < piVar1[-1])) {
            piVar5 = piVar1 + -7;
            iVar4 = *piVar1;
          }
          piVar1 = piVar1 + 8;
          local_c = local_c + -1;
        } while (local_c != 0);
      }
      if (piVar5 == (int *)0x0) {
        return;
      }
      piVar6[-2] = piVar5[1];
      *piVar6 = piVar5[3];
      piVar6[2] = piVar5[5];
      piVar6[-3] = *piVar5;
      piVar6[-1] = piVar5[2];
      piVar6[1] = piVar5[4];
      iVar2 = (piVar5[1] - *piVar5) * 0x10;
      iVar4 = (piVar5[3] - piVar5[2]) * 0xc;
      cVar3 = iVar2 <= iVar4;
      if (!(bool)cVar3) {
        iVar4 = iVar2;
      }
      if (iVar4 < (piVar5[5] - piVar5[4]) * 8) {
        cVar3 = '\x02';
      }
      if (cVar3 == '\0') {
        iVar4 = (piVar5[1] + *piVar5) / 2;
        piVar5[1] = iVar4;
        piVar6[-3] = iVar4 + 1;
      }
      else if (cVar3 == '\x01') {
        iVar4 = (piVar5[3] + piVar5[2]) / 2;
        piVar5[3] = iVar4;
        piVar6[-1] = iVar4 + 1;
      }
      else if (cVar3 == '\x02') {
        iVar4 = (piVar5[5] + piVar5[4]) / 2;
        piVar5[5] = iVar4;
        piVar6[1] = iVar4 + 1;
      }
      grim_jpg_coeff_merge_b();
      grim_jpg_coeff_merge_b();
      local_8 = local_8 + 2;
      param_3 = param_3 + 1;
      piVar6 = piVar6 + 8;
    } while (param_3 < param_4);
  }
  return;
}



/* grim_jpg_coeff_merge_d @ 100329e9 */

void __cdecl grim_jpg_coeff_merge_d(int param_1)

{
  int iVar1;
  int *in_EAX;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  int iVar4;
  uint uVar5;
  int local_38;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  ushort *local_10;
  int local_c;
  ushort *local_8;
  
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  local_28 = 0;
  iVar3 = in_EAX[2];
  iVar1 = in_EAX[4];
  iVar2 = *in_EAX;
  if (iVar2 <= in_EAX[1]) {
    local_18 = iVar2 * 8 + 4;
    do {
      if (iVar3 <= in_EAX[3]) {
        local_14 = iVar3 * 4 + 2;
        local_10 = (ushort *)
                   (*(int *)(*(int *)(*(int *)(unaff_ESI + 0x1a4) + 0x18) + iVar2 * 4) +
                   (iVar3 * 0x20 + iVar1) * 2);
        iVar4 = (in_EAX[3] - iVar3) + 1;
        do {
          local_8 = local_10;
          if (iVar1 <= in_EAX[5]) {
            local_c = iVar1 * 8 + 4;
            local_38 = (in_EAX[5] - iVar1) + 1;
            do {
              uVar5 = (uint)*local_8;
              local_8 = local_8 + 1;
              if (uVar5 != 0) {
                local_1c = local_1c + uVar5;
                local_24 = local_24 + local_14 * uVar5;
                local_20 = local_20 + local_18 * uVar5;
                local_28 = local_28 + local_c * uVar5;
              }
              local_c = local_c + 8;
              local_38 = local_38 + -1;
            } while (local_38 != 0);
          }
          local_10 = local_10 + 0x20;
          local_14 = local_14 + 4;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      local_18 = local_18 + 8;
      iVar2 = iVar2 + 1;
    } while (iVar2 <= in_EAX[1]);
  }
  iVar3 = local_1c >> 1;
  *(char *)(param_1 + **(int **)(unaff_ESI + 0x74)) = (char)((local_20 + iVar3) / local_1c);
  *(char *)(param_1 + *(int *)(*(int *)(unaff_ESI + 0x74) + 4)) =
       (char)((local_24 + iVar3) / local_1c);
  *(char *)(param_1 + *(int *)(*(int *)(unaff_ESI + 0x74) + 8)) =
       (char)((local_28 + iVar3) / local_1c);
  return;
}



/* grim_jpg_coeff_merge_e @ 10032b21 */

void __cdecl grim_jpg_coeff_merge_e(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *unaff_EDI;
  
  puVar1 = (undefined4 *)(**(code **)unaff_EDI[1])();
  puVar1[1] = 0x1f;
  puVar1[5] = 0x1f;
  *puVar1 = 0;
  puVar1[2] = 0;
  puVar1[3] = 0x3f;
  puVar1[4] = 0;
  grim_jpg_coeff_merge_b();
  iVar2 = grim_jpg_coeff_merge_c(unaff_EDI,(int)puVar1,1,param_1);
  param_1 = 0;
  if (0 < iVar2) {
    do {
      grim_jpg_coeff_merge_d(param_1);
      param_1 = param_1 + 1;
    } while (param_1 < iVar2);
  }
  unaff_EDI[0x1c] = iVar2;
  *(undefined4 *)(*unaff_EDI + 0x14) = 0x5f;
  *(int *)(*unaff_EDI + 0x18) = iVar2;
  (**(code **)(*unaff_EDI + 4))();
  return;
}



/* grim_jpg_coeff_merge_f @ 10032bae */

void __cdecl grim_jpg_coeff_merge_f(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_EDI;
  int aiStack_42c [256];
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_1c = param_1 * 2 + 0x18 >> 1;
  local_24 = unaff_EDI * 2 + 0x1c >> 1;
  local_10 = *(int *)(in_EAX + 0x70);
  local_28 = param_2 * 2 + 0x18 >> 1;
  local_c = 0x7fffffff;
  if (0 < *(int *)(in_EAX + 0x70)) {
    piVar1 = *(int **)(in_EAX + 0x74);
    local_2c = *piVar1;
    local_14 = piVar1[1];
    local_18 = piVar1[2];
    do {
      iVar6 = local_c;
      uVar3 = (uint)*(byte *)(local_2c + local_8);
      iVar4 = param_1 + 0x18;
      if ((int)uVar3 < param_1) {
        iVar7 = (uVar3 - param_1) * 2;
        iVar7 = iVar7 * iVar7;
LAB_10032c66:
        iVar5 = iVar4;
      }
      else {
        iVar5 = param_1;
        if (iVar4 < (int)uVar3) {
          iVar7 = (uVar3 - iVar4) * 2;
          iVar7 = iVar7 * iVar7;
        }
        else {
          iVar7 = 0;
          if ((int)uVar3 <= local_1c) goto LAB_10032c66;
        }
      }
      iVar4 = (uVar3 - iVar5) * 2;
      uVar3 = (uint)*(byte *)(local_14 + local_8);
      if ((int)uVar3 < unaff_EDI) {
        iVar5 = (uVar3 - unaff_EDI) * 3;
        iVar7 = iVar7 + iVar5 * iVar5;
        iVar5 = uVar3 - (unaff_EDI + 0x1c);
      }
      else {
        if (unaff_EDI + 0x1c < (int)uVar3) {
          iVar5 = (uVar3 - (unaff_EDI + 0x1c)) * 3;
          iVar7 = iVar7 + iVar5 * iVar5;
        }
        else if ((int)uVar3 <= local_24) {
          iVar5 = uVar3 - (unaff_EDI + 0x1c);
          goto LAB_10032c87;
        }
        iVar5 = uVar3 - unaff_EDI;
      }
LAB_10032c87:
      uVar3 = (uint)*(byte *)(local_18 + local_8);
      if ((int)uVar3 < param_2) {
        iVar7 = iVar7 + (uVar3 - param_2) * (uVar3 - param_2);
LAB_10032d2a:
        iVar2 = param_2 + 0x18;
      }
      else {
        local_20 = param_2 + 0x18;
        iVar2 = param_2;
        if (local_20 < (int)uVar3) {
          iVar7 = iVar7 + (uVar3 - local_20) * (uVar3 - local_20);
        }
        else if ((int)uVar3 <= local_28) goto LAB_10032d2a;
      }
      iVar4 = iVar4 * iVar4 + iVar5 * 3 * iVar5 * 3 + (uVar3 - iVar2) * (uVar3 - iVar2);
      aiStack_42c[local_8] = iVar7;
      if (iVar4 < iVar6) {
        local_c = iVar4;
      }
      local_8 = local_8 + 1;
    } while (local_8 < local_10);
  }
  iVar6 = 0;
  iVar4 = 0;
  if (0 < local_10) {
    do {
      if (aiStack_42c[iVar6] <= local_c) {
        *(char *)(iVar4 + param_3) = (char)iVar6;
        iVar4 = iVar4 + 1;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < local_10);
  }
  return;
}



/* grim_jpg_coeff_output_clamp @ 10032d2e */

void __cdecl
grim_jpg_coeff_output_clamp(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,byte *param_7)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int local_22c [128];
  int local_2c;
  int local_28;
  int local_24;
  byte *local_20;
  int local_1c;
  int local_18;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  piVar7 = local_22c;
  for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar7 = 0x7fffffff;
    piVar7 = piVar7 + 1;
  }
  if (0 < param_5) {
    do {
      bVar1 = *(byte *)(local_c + param_6);
      uVar6 = (uint)bVar1;
      piVar7 = *(int **)(param_1 + 0x74);
      iVar2 = param_3 - (uint)*(byte *)(piVar7[1] + uVar6);
      iVar3 = iVar2 * 3;
      iVar5 = param_4 - (uint)*(byte *)(piVar7[2] + uVar6);
      iVar4 = (param_2 - (uint)*(byte *)(uVar6 + *piVar7)) * 2;
      iVar3 = iVar5 * iVar5 + iVar3 * iVar3 + iVar4 * iVar4;
      local_14 = local_22c;
      local_8 = (iVar4 + 8) * 0x20;
      local_20 = param_7;
      local_28 = 4;
      do {
        local_2c = 8;
        local_1c = iVar3;
        local_10 = (iVar2 * 9 + 0x12) * 8;
        do {
          local_24 = 4;
          iVar4 = local_1c;
          local_18 = (iVar5 + 4) * 0x10;
          do {
            if (iVar4 < *local_14) {
              *local_14 = iVar4;
              *local_20 = bVar1;
            }
            iVar4 = iVar4 + local_18;
            local_18 = local_18 + 0x80;
            local_14 = local_14 + 1;
            local_20 = local_20 + 1;
            local_24 = local_24 + -1;
          } while (local_24 != 0);
          local_1c = local_1c + local_10;
          local_10 = local_10 + 0x120;
          local_2c = local_2c + -1;
        } while (local_2c != 0);
        iVar3 = iVar3 + local_8;
        local_8 = local_8 + 0x200;
        local_28 = local_28 + -1;
      } while (local_28 != 0);
      local_c = local_c + 1;
    } while (local_c < param_5);
  }
  return;
}



/* grim_jpg_coeff_final_transform @ 10032e48 */

void __cdecl grim_jpg_coeff_final_transform(int param_1,int param_2,int param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  short *psVar3;
  int *piVar4;
  byte *pbVar5;
  int iVar6;
  undefined1 local_18c [256];
  byte local_8c [128];
  int local_c;
  int local_8;
  
  iVar1 = param_3 >> 2;
  local_8 = *(int *)(*(int *)(param_1 + 0x1a4) + 0x18);
  local_c = iVar1 * 0x20 + 4;
  iVar6 = (param_2 >> 2) * 0x20 + 4;
  iVar2 = grim_jpg_coeff_merge_f(iVar6,local_c,(int)local_18c);
  grim_jpg_coeff_output_clamp(param_1,iVar6,(in_EAX >> 3) * 0x20 + 2,local_c,iVar2,(int)local_18c,local_8c);
  pbVar5 = local_8c;
  piVar4 = (int *)(local_8 + (param_2 >> 2) * 0x10);
  param_2 = 4;
  do {
    param_3 = 8;
    iVar2 = ((in_EAX >> 3) * 0x100 + iVar1 * 4) * 2;
    do {
      psVar3 = (short *)(*piVar4 + iVar2);
      iVar6 = 4;
      do {
        *psVar3 = *pbVar5 + 1;
        psVar3 = psVar3 + 1;
        pbVar5 = pbVar5 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      iVar2 = iVar2 + 0x40;
      param_3 = param_3 + -1;
    } while (param_3 != 0);
    piVar4 = piVar4 + 1;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}



/* grim_jpg_coeff_final_clamp @ 10032f18 */

void __cdecl grim_jpg_coeff_final_clamp(int param_1,int param_2,int *param_3,int param_4)

{
  short *psVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  byte *pbVar7;
  byte *pbVar8;
  int local_10;
  int *local_8;
  
  iVar4 = *(int *)(*(int *)(param_1 + 0x1a4) + 0x18);
  iVar5 = *(int *)(param_1 + 0x5c);
  if (0 < param_4) {
    local_8 = param_3;
    local_10 = param_4;
    do {
      pbVar8 = *(byte **)((param_2 - (int)param_3) + (int)local_8);
      pcVar6 = (char *)*local_8;
      for (iVar2 = iVar5; iVar2 != 0; iVar2 = iVar2 + -1) {
        bVar3 = *pbVar8;
        pbVar7 = pbVar8 + 2;
        psVar1 = (short *)(*(int *)(iVar4 + (uint)(bVar3 >> 3) * 4) +
                          ((uint)(pbVar8[1] >> 2) * 0x20 + (uint)(*pbVar7 >> 3)) * 2);
        pbVar8 = pbVar8 + 3;
        if (*psVar1 == 0) {
          grim_jpg_coeff_final_transform(param_1,(uint)(bVar3 >> 3),(uint)(*pbVar7 >> 3));
        }
        *pcVar6 = (char)*psVar1 + -1;
        pcVar6 = pcVar6 + 1;
      }
      local_8 = local_8 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return;
}



/* grim_jpg_coeff_final_output @ 10032fc1 */

void __cdecl grim_jpg_coeff_final_output(int param_1,int param_2,int *param_3,int param_4)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte *pbVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  short *psVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  int local_48;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  undefined1 *local_14;
  int local_8;
  
  iVar3 = *(int *)(param_1 + 0x1a4);
  iVar4 = *(int *)(iVar3 + 0x18);
  iVar5 = *(int *)(param_1 + 0x11c);
  iVar6 = *(int *)(iVar3 + 0x28);
  iVar7 = *(int *)(param_1 + 0x5c);
  piVar8 = *(int **)(param_1 + 0x74);
  iVar9 = *piVar8;
  iVar10 = piVar8[1];
  iVar11 = piVar8[2];
  if (0 < param_4) {
    local_28 = param_3;
    local_48 = param_4;
    do {
      pbVar12 = *(byte **)((param_2 - (int)param_3) + (int)local_28);
      local_14 = (undefined1 *)*local_28;
      if (*(char *)(iVar3 + 0x24) == '\0') {
        psVar18 = *(short **)(iVar3 + 0x20);
        local_3c = 1;
        local_8 = 3;
        *(undefined1 *)(iVar3 + 0x24) = 1;
      }
      else {
        local_3c = -1;
        *(undefined1 *)(iVar3 + 0x24) = 0;
        pbVar12 = pbVar12 + iVar7 * 3 + -3;
        local_14 = local_14 + iVar7 + -1;
        psVar18 = (short *)(*(int *)(iVar3 + 0x20) + (iVar7 * 3 + 3) * 2);
        local_8 = -3;
      }
      iVar15 = 0;
      local_24 = 0;
      local_24._0_2_ = 0;
      local_20 = 0;
      local_20._0_2_ = 0;
      local_1c = 0;
      local_1c._0_2_ = 0;
      iVar19 = 0;
      param_4 = 0;
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      for (iVar2 = iVar7; iVar2 != 0; iVar2 = iVar2 + -1) {
        uVar20 = (uint)*(byte *)(*(int *)(iVar6 + (psVar18[local_8] + 8 + iVar19 >> 4) * 4) +
                                 (uint)*pbVar12 + iVar5);
        uVar16 = (uint)*(byte *)(*(int *)(iVar6 + (psVar18[local_8 + 1] + 8 + iVar15 >> 4) * 4) +
                                 (uint)pbVar12[1] + iVar5);
        uVar13 = (uint)*(byte *)(*(int *)(iVar6 + (psVar18[local_8 + 2] + 8 + param_4 >> 4) * 4) +
                                 (uint)pbVar12[2] + iVar5);
        iVar19 = (int)uVar13 >> 3;
        iVar15 = (int)uVar20 >> 3;
        puVar1 = (ushort *)(*(int *)(iVar4 + iVar15 * 4) + (((int)uVar16 >> 2) * 0x20 + iVar19) * 2)
        ;
        if (*puVar1 == 0) {
          grim_jpg_coeff_final_transform(param_1,iVar15,iVar19);
        }
        iVar19 = *puVar1 - 1;
        *local_14 = (char)iVar19;
        iVar21 = uVar20 - *(byte *)(iVar19 + iVar9);
        iVar17 = uVar16 - *(byte *)(iVar19 + iVar10);
        iVar14 = uVar13 - *(byte *)(iVar19 + iVar11);
        *psVar18 = (short)local_1c + (short)iVar21 * 3;
        local_1c = local_30 + iVar21 * 5;
        iVar19 = iVar21 * 7;
        psVar18[1] = (short)local_20 + (short)iVar17 * 3;
        local_20 = local_34 + iVar17 * 5;
        iVar15 = iVar17 * 7;
        psVar18[2] = (short)local_24 + (short)iVar14 * 3;
        local_24 = local_38 + iVar14 * 5;
        param_4 = iVar14 * 7;
        pbVar12 = pbVar12 + local_8;
        local_14 = local_14 + local_3c;
        psVar18 = psVar18 + local_8;
        local_38 = iVar14;
        local_34 = iVar17;
        local_30 = iVar21;
      }
      local_28 = local_28 + 1;
      local_48 = local_48 + -1;
      *psVar18 = (short)local_1c;
      psVar18[1] = (short)local_20;
      psVar18[2] = (short)local_24;
    } while (local_48 != 0);
  }
  return;
}



/* grim_jpg_coeff_range_check @ 1003322f */

void grim_jpg_coeff_range_check(void)

{
  int in_EAX;
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  iVar4 = *(int *)(in_EAX + 0x1a4);
  iVar1 = (*(code *)**(undefined4 **)(in_EAX + 4))();
  piVar2 = (int *)(iVar1 + 0x3fc);
  *(int **)(iVar4 + 0x28) = piVar2;
  iVar4 = 0;
  uVar3 = 0;
  iVar1 = 0;
  piVar5 = piVar2;
  do {
    piVar2[uVar3] = iVar4;
    *piVar5 = iVar1;
    uVar3 = uVar3 + 1;
    piVar5 = piVar5 + -1;
    iVar4 = iVar4 + 1;
    iVar1 = iVar1 + -1;
  } while ((int)uVar3 < 0x10);
  if ((int)uVar3 < 0x30) {
    piVar5 = piVar2 + -uVar3;
    do {
      piVar2[uVar3] = iVar4;
      *piVar5 = -iVar4;
      uVar3 = uVar3 + 1;
      piVar5 = piVar5 + -1;
      iVar4 = iVar4 + (~uVar3 & 1);
    } while ((int)uVar3 < 0x30);
  }
  if ((int)uVar3 < 0x100) {
    piVar5 = piVar2 + -uVar3;
    do {
      piVar2[uVar3] = iVar4;
      *piVar5 = -iVar4;
      uVar3 = uVar3 + 1;
      piVar5 = piVar5 + -1;
    } while ((int)uVar3 < 0x100);
  }
  return;
}



/* grim_jpg_coeff_quantize_pass @ 100332e1 */

void __cdecl grim_jpg_coeff_quantize_pass(int *param_1,char param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint size;
  int iVar4;
  
  iVar1 = param_1[0x69];
  iVar2 = *(int *)(iVar1 + 0x18);
  if (param_1[0x13] != 0) {
    param_1[0x13] = 2;
  }
  if (param_2 == '\0') {
    if (param_1[0x13] == 2) {
      *(code **)(iVar1 + 4) = grim_jpg_coeff_final_output;
    }
    else {
      *(code **)(iVar1 + 4) = grim_jpg_coeff_final_clamp;
    }
    *(undefined **)(iVar1 + 8) = &grim_jpg_error_handler;
    iVar4 = param_1[0x1c];
    if (iVar4 < 1) {
      *(undefined4 *)(*param_1 + 0x14) = 0x37;
      *(undefined4 *)(*param_1 + 0x18) = 1;
      (**(code **)*param_1)(param_1);
    }
    if (0x100 < iVar4) {
      *(undefined4 *)(*param_1 + 0x14) = 0x38;
      *(undefined4 *)(*param_1 + 0x18) = 0x100;
      (**(code **)*param_1)(param_1);
    }
    if (param_1[0x13] == 2) {
      size = (param_1[0x17] + 2) * 6;
      if (*(int *)(iVar1 + 0x20) == 0) {
        uVar3 = (**(code **)(param_1[1] + 4))(param_1,1,size);
        *(undefined4 *)(iVar1 + 0x20) = uVar3;
      }
      memzero(*(void **)(iVar1 + 0x20),size);
      if (*(int *)(iVar1 + 0x28) == 0) {
        grim_jpg_coeff_range_check();
      }
      *(undefined1 *)(iVar1 + 0x24) = 0;
    }
  }
  else {
    *(code **)(iVar1 + 4) = grim_jpg_coeff_merge_a;
    *(undefined1 **)(iVar1 + 8) = &LAB_100332bf;
    *(undefined1 *)(iVar1 + 0x1c) = 1;
  }
  if (*(char *)(iVar1 + 0x1c) != '\0') {
    iVar4 = 0;
    do {
      memzero(*(void **)(iVar2 + iVar4 * 4),0x1000);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x20);
    *(undefined1 *)(iVar1 + 0x1c) = 0;
  }
  return;
}



/* grim_jpg_coeff_quantize_and_pack @ 100333f2 */

void __cdecl grim_jpg_coeff_quantize_and_pack(int *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x2c);
  param_1[0x69] = (int)puVar1;
  iVar3 = 0;
  *puVar1 = grim_jpg_coeff_quantize_pass;
  puVar1[3] = &LAB_100333e3;
  puVar1[8] = 0;
  puVar1[10] = 0;
  if (param_1[0x19] != 3) {
    *(undefined4 *)(*param_1 + 0x14) = 0x2e;
    (**(code **)*param_1)(param_1);
  }
  uVar2 = (**(code **)param_1[1])(param_1,1,0x80);
  puVar1[6] = uVar2;
  do {
    uVar2 = (**(code **)(param_1[1] + 4))(param_1,1,0x1000);
    *(undefined4 *)(puVar1[6] + iVar3) = uVar2;
    iVar3 = iVar3 + 4;
  } while (iVar3 < 0x80);
  *(undefined1 *)(puVar1 + 7) = 1;
  if (*(char *)((int)param_1 + 0x5a) == '\0') {
    puVar1[4] = 0;
  }
  else {
    iVar3 = param_1[0x15];
    if (iVar3 < 8) {
      *(undefined4 *)(*param_1 + 0x14) = 0x37;
      *(undefined4 *)(*param_1 + 0x18) = 8;
      (**(code **)*param_1)(param_1);
    }
    if (0x100 < iVar3) {
      *(undefined4 *)(*param_1 + 0x14) = 0x38;
      *(undefined4 *)(*param_1 + 0x18) = 0x100;
      (**(code **)*param_1)(param_1);
    }
    uVar2 = (**(code **)(param_1[1] + 8))(param_1,1,iVar3,3);
    puVar1[4] = uVar2;
    puVar1[5] = iVar3;
  }
  if (param_1[0x13] != 0) {
    param_1[0x13] = 2;
  }
  if (param_1[0x13] == 2) {
    uVar2 = (**(code **)(param_1[1] + 4))(param_1,1,(param_1[0x17] + 2) * 6);
    puVar1[8] = uVar2;
    grim_jpg_coeff_range_check();
    return;
  }
  return;
}



/* grim_jpg_start_decompress_full @ 10033505 */

int __cdecl grim_jpg_start_decompress_full(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_10;
  int local_c;
  
  iVar1 = param_1[0x15];
  iVar2 = param_1[0x19];
  iVar7 = 1;
  do {
    iVar5 = iVar7;
    iVar7 = iVar5 + 1;
    iVar4 = iVar7;
    if (1 < iVar2) {
      iVar6 = iVar2 + -1;
      do {
        iVar4 = iVar4 * iVar7;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  } while (iVar4 <= iVar1);
  if (iVar5 < 2) {
    *(undefined4 *)(*param_1 + 0x14) = 0x37;
    *(int *)(*param_1 + 0x18) = iVar4;
    (**(code **)*param_1)(param_1);
  }
  local_10 = 1;
  iVar7 = iVar2;
  piVar8 = param_2;
  if (0 < iVar2) {
    for (; iVar4 = iVar2, iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar8 = iVar5;
      piVar8 = piVar8 + 1;
    }
    do {
      local_10 = local_10 * iVar5;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  do {
    bVar3 = false;
    local_c = 0;
    if (iVar2 < 1) {
      return local_10;
    }
    do {
      iVar7 = local_c;
      if (param_1[10] == 2) {
        iVar7 = *(int *)(&DAT_1004f6d0 + local_c * 4);
      }
      iVar5 = param_2[iVar7];
      iVar4 = iVar5 + 1;
      iVar5 = (local_10 / iVar5) * iVar4;
      if (iVar5 - iVar1 != 0 && iVar1 <= iVar5) break;
      local_c = local_c + 1;
      param_2[iVar7] = iVar4;
      bVar3 = true;
      local_10 = iVar5;
    } while (local_c < iVar2);
    if (!bVar3) {
      return local_10;
    }
  } while( true );
}



/* grim_jpg_dequant_init @ 100335d0 */

void grim_jpg_dequant_init(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *unaff_ESI;
  int iVar8;
  undefined1 local_34;
  int local_28;
  int local_24;
  int *local_20;
  int *local_1c;
  int local_18;
  int local_14;
  int local_8;
  
  iVar2 = unaff_ESI[0x69];
  local_1c = (int *)(iVar2 + 0x20);
  iVar3 = grim_jpg_start_decompress_full(unaff_ESI,local_1c);
  iVar5 = *unaff_ESI;
  if (unaff_ESI[0x19] == 3) {
    *(int *)(iVar5 + 0x18) = iVar3;
    *(int *)(iVar5 + 0x1c) = *local_1c;
    *(undefined4 *)(iVar5 + 0x20) = *(undefined4 *)(iVar2 + 0x24);
    *(undefined4 *)(iVar5 + 0x24) = *(undefined4 *)(iVar2 + 0x28);
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x5d;
  }
  else {
    *(undefined4 *)(iVar5 + 0x14) = 0x5e;
    *(int *)(*unaff_ESI + 0x18) = iVar3;
  }
  (**(code **)(*unaff_ESI + 4))();
  piVar4 = (int *)(**(code **)(unaff_ESI[1] + 8))();
  local_24 = 0;
  local_20 = piVar4;
  local_18 = iVar3;
  if (0 < unaff_ESI[0x19]) {
    do {
      local_28 = *local_1c;
      iVar5 = local_18 / local_28;
      iVar8 = 0;
      if (0 < local_28) {
        iVar1 = local_28 + -1;
        local_14 = 0;
        do {
          for (iVar7 = local_14; iVar7 < iVar3; iVar7 = iVar7 + local_18) {
            local_8 = 0;
            if (0 < iVar5) {
              do {
                iVar6 = *local_20 + local_8;
                local_34 = (undefined1)((iVar1 / 2 + iVar8) / iVar1);
                local_8 = local_8 + 1;
                *(undefined1 *)(iVar6 + iVar7) = local_34;
              } while (local_8 < iVar5);
            }
          }
          local_14 = local_14 + iVar5;
          iVar8 = iVar8 + 0xff;
          local_28 = local_28 + -1;
        } while (local_28 != 0);
      }
      local_24 = local_24 + 1;
      local_1c = local_1c + 1;
      local_20 = local_20 + 1;
      local_18 = iVar5;
    } while (local_24 < unaff_ESI[0x19]);
  }
  *(int *)(iVar2 + 0x14) = iVar3;
  *(int **)(iVar2 + 0x10) = piVar4;
  return;
}



/* grim_jpg_color_convert_init @ 100336fd */

void __cdecl grim_jpg_color_convert_init(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  int local_1c;
  char local_18;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x1a4);
  if (*(int *)(param_1 + 0x4c) == 1) {
    local_10 = 0x1fe;
    *(undefined1 *)(iVar2 + 0x1c) = 1;
  }
  else {
    local_10 = 0;
    *(undefined1 *)(iVar2 + 0x1c) = 0;
  }
  uVar4 = (**(code **)(*(int *)(param_1 + 4) + 8))
                    (param_1,1,local_10 + 0x100,*(undefined4 *)(param_1 + 100));
  *(undefined4 *)(iVar2 + 0x18) = uVar4;
  iVar5 = *(int *)(iVar2 + 0x14);
  local_1c = 0;
  if (0 < *(int *)(param_1 + 100)) {
    local_14 = (int *)(iVar2 + 0x20);
    do {
      iVar9 = *local_14;
      iVar5 = iVar5 / iVar9;
      if (local_10 != 0) {
        piVar1 = (int *)(*(int *)(iVar2 + 0x18) + local_1c * 4);
        *piVar1 = *piVar1 + 0xff;
      }
      puVar3 = *(undefined1 **)(*(int *)(iVar2 + 0x18) + local_1c * 4);
      iVar6 = (iVar9 + 0xfe) / (iVar9 * 2 + -2);
      local_c = 0;
      local_8 = 0;
      do {
        if (iVar6 < local_8) {
          iVar7 = local_c * 0x1fe;
          do {
            iVar6 = (iVar7 + 0x2fc + iVar9) / (iVar9 * 2 + -2);
            local_c = local_c + 1;
            iVar7 = iVar7 + 0x1fe;
          } while (iVar6 < local_8);
        }
        local_18 = (char)iVar5;
        iVar7 = local_8 + 1;
        puVar3[local_8] = (char)local_c * local_18;
        local_8 = iVar7;
      } while (iVar7 < 0x100);
      if (local_10 != 0) {
        iVar9 = 1;
        puVar8 = puVar3;
        do {
          puVar8 = puVar8 + -1;
          *puVar8 = *puVar3;
          (puVar3 + 0xff)[iVar9] = puVar3[0xff];
          iVar9 = iVar9 + 1;
        } while (iVar9 < 0x100);
      }
      local_14 = local_14 + 1;
      local_1c = local_1c + 1;
    } while (local_1c < *(int *)(param_1 + 100));
  }
  return;
}



/* grim_jpg_dequant_table_init @ 10033828 */

void grim_jpg_dequant_table_init(void)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int unaff_EDI;
  undefined1 *local_c;
  int local_8;
  
  iVar2 = *(int *)(unaff_EDI + 0x1a4);
  local_8 = 0;
  if (0 < *(int *)(unaff_EDI + 100)) {
    piVar6 = (int *)(iVar2 + 0x34);
    do {
      iVar3 = piVar6[-5];
      iVar4 = 0;
      if (0 < local_8) {
        piVar5 = (int *)(iVar2 + 0x20);
        do {
          if (iVar3 == *piVar5) {
            piVar5 = *(int **)(iVar2 + 0x34 + iVar4 * 4);
            if (piVar5 != (int *)0x0) goto LAB_100338d2;
            break;
          }
          iVar4 = iVar4 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar4 < local_8);
      }
      piVar5 = (int *)(*(code *)**(undefined4 **)(unaff_EDI + 4))();
      local_c = &grim_jpg_dequant_dither;
      piVar7 = piVar5;
      do {
        iVar4 = 0;
        do {
          pbVar1 = local_c + iVar4;
          iVar4 = iVar4 + 1;
          *piVar7 = (int)((uint)*pbVar1 * -0x1fe + 0xfe01) / (iVar3 * 0x200 + -0x200);
          piVar7 = piVar7 + 1;
        } while (iVar4 < 0x10);
        local_c = local_c + 0x10;
      } while ((int)local_c < 0x1004f6d0);
LAB_100338d2:
      local_8 = local_8 + 1;
      *piVar6 = (int)piVar5;
      piVar6 = piVar6 + 1;
    } while (local_8 < *(int *)(unaff_EDI + 100));
  }
  return;
}



/* grim_jpg_upsample_grayscale @ 100338ed */

void __cdecl grim_jpg_upsample_grayscale(int param_1,int param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  int local_c;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0x1a4) + 0x18);
  iVar3 = *(int *)(param_1 + 0x5c);
  iVar4 = *(int *)(param_1 + 100);
  if (0 < param_4) {
    iVar8 = param_2 - (int)param_3;
    local_c = param_4;
    do {
      pbVar6 = *(byte **)(iVar8 + (int)param_3);
      puVar5 = (undefined1 *)*param_3;
      for (iVar1 = iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
        param_1 = 0;
        param_1._0_1_ = 0;
        iVar7 = 0;
        if (0 < iVar4) {
          do {
            param_1 = param_1 + (uint)*(byte *)(*(int *)(iVar2 + iVar7 * 4) + (uint)*pbVar6);
            pbVar6 = pbVar6 + 1;
            iVar7 = iVar7 + 1;
          } while (iVar7 < iVar4);
        }
        *puVar5 = (undefined1)param_1;
        puVar5 = puVar5 + 1;
      }
      param_3 = param_3 + 1;
      local_c = local_c + -1;
    } while (local_c != 0);
  }
  return;
}



/* grim_jpg_upsample_rgb @ 10033975 */

void __cdecl grim_jpg_upsample_rgb(int param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  char *pcVar12;
  
  piVar3 = *(int **)(*(int *)(param_1 + 0x1a4) + 0x18);
  iVar4 = *piVar3;
  iVar5 = piVar3[1];
  iVar6 = piVar3[2];
  iVar7 = *(int *)(param_1 + 0x5c);
  if (0 < param_4) {
    iVar8 = param_2 - (int)param_3;
    do {
      pbVar11 = *(byte **)(iVar8 + (int)param_3);
      pcVar12 = (char *)*param_3;
      for (iVar1 = iVar7; iVar1 != 0; iVar1 = iVar1 + -1) {
        bVar2 = *pbVar11;
        pbVar9 = pbVar11 + 1;
        pbVar10 = pbVar11 + 2;
        pbVar11 = pbVar11 + 3;
        *pcVar12 = *(char *)((uint)bVar2 + iVar4) + *(char *)((uint)*pbVar9 + iVar5) +
                   *(char *)((uint)*pbVar10 + iVar6);
        pcVar12 = pcVar12 + 1;
      }
      param_3 = param_3 + 1;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}



/* grim_jpg_upsample_multichannel @ 10033a02 */

void __cdecl grim_jpg_upsample_multichannel(int param_1,int param_2,undefined4 *param_3,uint param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint size;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  char *pcVar10;
  uint local_1c;
  int *local_8;
  
  iVar3 = *(int *)(param_1 + 100);
  iVar4 = *(int *)(param_1 + 0x1a4);
  size = *(uint *)(param_1 + 0x5c);
  if (0 < (int)param_4) {
    iVar9 = param_2 - (int)param_3;
    local_1c = param_4;
    do {
      memzero((void *)*param_3,size);
      iVar5 = *(int *)(iVar4 + 0x30);
      param_1 = 0;
      if (0 < iVar3) {
        local_8 = (int *)(iVar4 + 0x34);
        do {
          param_4 = 0;
          pcVar10 = (char *)*param_3;
          pbVar8 = (byte *)(*(int *)(iVar9 + (int)param_3) + param_1);
          iVar6 = *(int *)(*(int *)(iVar4 + 0x18) + param_1 * 4);
          iVar7 = *local_8;
          for (uVar1 = size; uVar1 != 0; uVar1 = uVar1 - 1) {
            bVar2 = *pbVar8;
            pbVar8 = pbVar8 + iVar3;
            *pcVar10 = *pcVar10 +
                       *(char *)(*(int *)(iVar7 + iVar5 * 0x40 + param_4 * 4) + (uint)bVar2 + iVar6)
            ;
            pcVar10 = pcVar10 + 1;
            param_4 = param_4 + 1 & 0xf;
          }
          param_1 = param_1 + 1;
          local_8 = local_8 + 1;
        } while (param_1 < iVar3);
      }
      param_3 = param_3 + 1;
      local_1c = local_1c - 1;
      *(uint *)(iVar4 + 0x30) = iVar5 + 1U & 0xf;
    } while (local_1c != 0);
  }
  return;
}



/* grim_jpg_upsample_rgb_ordered @ 10033aed */

void __cdecl grim_jpg_upsample_rgb_ordered(uint param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  byte *pbVar13;
  int iVar14;
  int local_14;
  int *local_c;
  
  iVar2 = *(int *)(param_1 + 0x1a4);
  piVar3 = *(int **)(iVar2 + 0x18);
  iVar4 = *piVar3;
  iVar5 = piVar3[1];
  iVar6 = piVar3[2];
  iVar7 = *(int *)(param_1 + 0x5c);
  if (0 < param_4) {
    local_c = param_3;
    local_14 = param_4;
    do {
      pbVar13 = *(byte **)((param_2 - (int)param_3) + (int)local_c);
      pcVar8 = (char *)*local_c;
      iVar9 = *(int *)(iVar2 + 0x30);
      iVar10 = *(int *)(iVar2 + 0x34);
      iVar11 = *(int *)(iVar2 + 0x3c);
      param_1 = 0;
      iVar14 = iVar9 * 0x40;
      iVar12 = *(int *)(iVar2 + 0x38);
      for (iVar1 = iVar7; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pcVar8 = *(char *)(*(int *)(iVar10 + iVar14 + param_1 * 4) + (uint)*pbVar13 + iVar4) +
                  *(char *)(*(int *)(iVar12 + iVar14 + param_1 * 4) + (uint)pbVar13[1] + iVar5) +
                  *(char *)(*(int *)(iVar11 + iVar14 + param_1 * 4) + (uint)pbVar13[2] + iVar6);
        pbVar13 = pbVar13 + 3;
        pcVar8 = pcVar8 + 1;
        param_1 = param_1 + 1 & 0xf;
      }
      local_c = local_c + 1;
      local_14 = local_14 + -1;
      *(uint *)(iVar2 + 0x30) = iVar9 + 1U & 0xf;
    } while (local_14 != 0);
  }
  return;
}



/* grim_jpg_upsample_dither @ 10033bec */

void __cdecl grim_jpg_upsample_dither(int param_1,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  uint size;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  short *psVar11;
  char *pcVar12;
  byte *pbVar13;
  undefined4 *local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int *local_c;
  
  local_28 = param_4;
  iVar3 = *(int *)(param_1 + 100);
  size = *(uint *)(param_1 + 0x5c);
  iVar4 = *(int *)(param_1 + 0x1a4);
  iVar5 = *(int *)(param_1 + 0x11c);
  if (0 < (int)param_4) {
    param_4 = param_3;
    do {
      memzero((void *)*param_4,size);
      param_1 = 0;
      if (0 < iVar3) {
        local_c = (int *)(iVar4 + 0x44);
        do {
          pbVar13 = (byte *)(*(int *)((param_2 - (int)param_3) + (int)param_4) + param_1);
          pcVar12 = (char *)*param_4;
          if (*(char *)(iVar4 + 0x54) == '\0') {
            psVar11 = (short *)*local_c;
            local_14 = 1;
            local_20 = iVar3;
          }
          else {
            local_14 = -1;
            pcVar12 = pcVar12 + (size - 1);
            pbVar13 = pbVar13 + (size - 1) * iVar3;
            psVar11 = (short *)(*local_c + 2 + size * 2);
            local_20 = -iVar3;
          }
          iVar6 = *(int *)(param_1 * 4 + *(int *)(iVar4 + 0x18));
          iVar7 = *(int *)(param_1 * 4 + *(int *)(iVar4 + 0x10));
          iVar8 = 0;
          local_18 = 0;
          local_18._0_2_ = 0;
          local_1c = 0;
          for (uVar1 = size; uVar1 != 0; uVar1 = uVar1 - 1) {
            uVar9 = (uint)*(byte *)((uint)*pbVar13 + iVar5 + (psVar11[local_14] + 8 + iVar8 >> 4));
            bVar2 = *(byte *)(uVar9 + iVar6);
            *pcVar12 = *pcVar12 + bVar2;
            pbVar13 = pbVar13 + local_20;
            pcVar12 = pcVar12 + local_14;
            iVar10 = uVar9 - *(byte *)((uint)bVar2 + iVar7);
            *psVar11 = (short)local_18 + (short)iVar10 * 3;
            local_18 = local_1c + iVar10 * 5;
            iVar8 = iVar10 * 7;
            psVar11 = psVar11 + local_14;
            local_1c = iVar10;
          }
          param_1 = param_1 + 1;
          local_c = local_c + 1;
          *psVar11 = (short)local_18;
        } while (param_1 < iVar3);
      }
      param_4 = param_4 + 1;
      local_28 = (undefined4 *)((int)local_28 + -1);
      *(bool *)(iVar4 + 0x54) = *(char *)(iVar4 + 0x54) == '\0';
    } while (local_28 != (undefined4 *)0x0);
  }
  return;
}



/* grim_jpg_dither_table_alloc @ 10033d70 */

void grim_jpg_dither_table_alloc(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int unaff_ESI;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(int *)(unaff_ESI + 100)) {
    puVar2 = (undefined4 *)(*(int *)(unaff_ESI + 0x1a4) + 0x44);
    do {
      uVar1 = (**(code **)(*(int *)(unaff_ESI + 4) + 4))();
      *puVar2 = uVar1;
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < *(int *)(unaff_ESI + 100));
  }
  return;
}



/* grim_jpg_cquantize_start @ 10033da6 */

void __cdecl grim_jpg_cquantize_start(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = param_1[0x69];
  param_1[0x1d] = *(int *)(iVar1 + 0x10);
  param_1[0x1c] = *(int *)(iVar1 + 0x14);
  iVar3 = param_1[0x13];
  if (iVar3 == 0) {
    if (param_1[0x19] == 3) {
      *(code **)(iVar1 + 4) = grim_jpg_upsample_rgb;
    }
    else {
      *(code **)(iVar1 + 4) = grim_jpg_upsample_grayscale;
    }
  }
  else if (iVar3 == 1) {
    if (param_1[0x19] == 3) {
      *(code **)(iVar1 + 4) = grim_jpg_upsample_rgb_ordered;
    }
    else {
      *(code **)(iVar1 + 4) = grim_jpg_upsample_multichannel;
    }
    *(undefined4 *)(iVar1 + 0x30) = 0;
    if (*(char *)(iVar1 + 0x1c) == '\0') {
      grim_jpg_color_convert_init((int)param_1);
    }
    if (*(int *)(iVar1 + 0x34) == 0) {
      grim_jpg_dequant_table_init();
    }
  }
  else if (iVar3 == 2) {
    *(undefined1 *)(iVar1 + 0x54) = 0;
    piVar2 = (int *)(iVar1 + 0x44);
    *(code **)(iVar1 + 4) = grim_jpg_upsample_dither;
    if (*piVar2 == 0) {
      grim_jpg_dither_table_alloc();
    }
    iVar1 = param_1[0x17];
    iVar3 = 0;
    if (0 < param_1[0x19]) {
      do {
        memzero((void *)*piVar2,iVar1 * 2 + 4);
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar3 < param_1[0x19]);
    }
  }
  else {
    *(undefined4 *)(*param_1 + 0x14) = 0x2f;
    (**(code **)*param_1)(param_1);
  }
  return;
}



/* grim_jpg_cquantize_init @ 10033e84 */

void __cdecl grim_jpg_cquantize_init(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x58);
  param_1[0x69] = (int)puVar1;
  puVar1[0x11] = 0;
  puVar1[0xd] = 0;
  *puVar1 = grim_jpg_cquantize_start;
  puVar1[2] = &grim_jpg_error_handler;
  puVar1[3] = &LAB_10033e70;
  if (4 < param_1[0x19]) {
    *(undefined4 *)(*param_1 + 0x14) = 0x36;
    *(undefined4 *)(*param_1 + 0x18) = 4;
    (**(code **)*param_1)(param_1);
  }
  if (0x100 < param_1[0x15]) {
    *(undefined4 *)(*param_1 + 0x14) = 0x38;
    *(undefined4 *)(*param_1 + 0x18) = 0x100;
    (**(code **)*param_1)(param_1);
  }
  grim_jpg_dequant_init();
  grim_jpg_color_convert_init((int)param_1);
  if (param_1[0x13] == 2) {
    grim_jpg_dither_table_alloc();
  }
  return;
}



/* grim_jpg_idct_4x4_islow @ 10034900 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl grim_jpg_idct_4x4_islow(uint *param_1,uint *param_2,uint *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  uint uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  uint uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  
  fVar6 = (float)(*param_1 & _DAT_10055b60);
  fVar10 = (float)(param_1[1] & uRam10055b64);
  fVar14 = (float)(param_1[2] & uRam10055b68);
  fVar18 = (float)(param_1[3] & uRam10055b6c);
  uVar22 = param_1[1] & uRam10055b54;
  uVar23 = param_1[2] & uRam10055b58;
  uVar24 = param_1[3] & uRam10055b5c;
  fVar7 = fVar6 * _DAT_10055b40 + _DAT_10055af0;
  fVar11 = fVar10 * fRam10055b44 + fRam10055af4;
  fVar15 = fVar14 * fRam10055b48 + fRam10055af8;
  fVar19 = fVar18 * fRam10055b4c + fRam10055afc;
  fVar8 = fVar7 - _DAT_10055af0;
  fVar12 = fVar11 - fRam10055af4;
  fVar16 = fVar15 - fRam10055af8;
  fVar20 = fVar19 - fRam10055afc;
  fVar6 = (((fVar6 - _DAT_10055b30 * fVar8) - _DAT_10055b20 * fVar8) - _DAT_10055b10 * fVar8) -
          _DAT_10055b00 * fVar8;
  fVar8 = (((fVar10 - fRam10055b34 * fVar12) - fRam10055b24 * fVar12) - fRam10055b14 * fVar12) -
          fRam10055b04 * fVar12;
  fVar10 = (((fVar14 - fRam10055b38 * fVar16) - fRam10055b28 * fVar16) - fRam10055b18 * fVar16) -
           fRam10055b08 * fVar16;
  fVar12 = (((fVar18 - fRam10055b3c * fVar20) - fRam10055b2c * fVar20) - fRam10055b1c * fVar20) -
           fRam10055b0c * fVar20;
  fVar14 = fVar6 * fVar6;
  fVar16 = fVar8 * fVar8;
  fVar18 = fVar10 * fVar10;
  fVar20 = fVar12 * fVar12;
  uVar25 = (uint)fVar7 & _DAT_10055ac0;
  uVar26 = (uint)fVar11 & uRam10055ac4;
  uVar27 = (uint)fVar15 & uRam10055ac8;
  uVar28 = (uint)fVar19 & uRam10055acc;
  uVar9 = uVar25 & _DAT_10055ab0;
  uVar13 = uVar26 & uRam10055ab4;
  uVar17 = uVar27 & uRam10055ab8;
  uVar21 = uVar28 & uRam10055abc;
  uVar1 = uVar26 - uVar13 & _DAT_10055aa0;
  uVar2 = uVar27 - uVar17 & _DAT_10055aa0;
  uVar3 = uVar28 - uVar21 & _DAT_10055aa0;
  uVar4 = uVar25 + uVar9 & _DAT_10055aa0;
  uVar26 = uVar26 + uVar13 & _DAT_10055aa0;
  uVar27 = uVar27 + uVar17 & _DAT_10055aa0;
  uVar28 = uVar28 + uVar21 & _DAT_10055aa0;
  uVar5 = -(uint)((float)(uVar9 << 0x1e) != 0.0);
  uVar13 = -(uint)((float)(uVar13 << 0x1e) != 0.0);
  uVar17 = -(uint)((float)(uVar17 << 0x1e) != 0.0);
  uVar21 = -(uint)((float)(uVar21 << 0x1e) != 0.0);
  fVar6 = (((_DAT_10055ae0 * fVar14 + _DAT_10055a90) * fVar14 + _DAT_10055a70) * fVar14 +
          _DAT_10055a50) * fVar6;
  fVar8 = (((fRam10055ae4 * fVar16 + fRam10055a94) * fVar16 + fRam10055a74) * fVar16 + fRam10055a54)
          * fVar8;
  fVar10 = (((fRam10055ae8 * fVar18 + fRam10055a98) * fVar18 + fRam10055a78) * fVar18 + fRam10055a58
           ) * fVar10;
  fVar12 = (((fRam10055aec * fVar20 + fRam10055a9c) * fVar20 + fRam10055a7c) * fVar20 + fRam10055a5c
           ) * fVar12;
  fVar7 = (((_DAT_10055ad0 * fVar14 + _DAT_10055a80) * fVar14 + _DAT_10055a60) * fVar14 +
          _DAT_10055a40) * fVar14 + _DAT_10055a30;
  fVar11 = (((fRam10055ad4 * fVar16 + fRam10055a84) * fVar16 + fRam10055a64) * fVar16 + fRam10055a44
           ) * fVar16 + fRam10055a34;
  fVar14 = (((fRam10055ad8 * fVar18 + fRam10055a88) * fVar18 + fRam10055a68) * fVar18 + fRam10055a48
           ) * fVar18 + fRam10055a38;
  fVar15 = (((fRam10055adc * fVar20 + fRam10055a8c) * fVar20 + fRam10055a6c) * fVar20 + fRam10055a4c
           ) * fVar20 + fRam10055a3c;
  *param_2 = (~uVar5 & (uint)fVar6 | uVar5 & (uint)fVar7) ^
             (uVar25 - uVar9 & _DAT_10055aa0) << 0x1e ^ *param_1 & _DAT_10055b50;
  param_2[1] = (~uVar13 & (uint)fVar8 | uVar13 & (uint)fVar11) ^ uVar1 << 0x1e ^ uVar22;
  param_2[2] = (~uVar17 & (uint)fVar10 | uVar17 & (uint)fVar14) ^ uVar2 << 0x1e ^ uVar23;
  param_2[3] = (~uVar21 & (uint)fVar12 | uVar21 & (uint)fVar15) ^ uVar3 << 0x1e ^ uVar24;
  *param_3 = (uVar5 & (uint)fVar6 | ~uVar5 & (uint)fVar7) ^ uVar4 << 0x1e;
  param_3[1] = (uVar13 & (uint)fVar8 | ~uVar13 & (uint)fVar11) ^ uVar26 << 0x1e;
  param_3[2] = (uVar17 & (uint)fVar10 | ~uVar17 & (uint)fVar14) ^ uVar27 << 0x1e;
  param_3[3] = (uVar21 & (uint)fVar12 | ~uVar21 & (uint)fVar15) ^ uVar28 << 0x1e;
  return;
}



/* grim_jpg_idct_4x4_ifast_noop @ 10034af0 */

void grim_jpg_idct_4x4_ifast_noop(void)

{
  return;
}



/* grim_jpg_idct_2x2_islow @ 10034be0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl grim_jpg_idct_2x2_islow(uint *param_1,uint *param_2,uint *param_3)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  float fVar16;
  float fVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  float fVar25;
  float fVar26;
  uint uVar27;
  uint uVar28;
  
  fVar16 = (float)(*param_1 & _DAT_10055d80);
  fVar17 = (float)(param_1[1] & uRam10055d84);
  fVar25 = (float)(param_1[2] & uRam10055d88);
  fVar26 = (float)(param_1[3] & uRam10055d8c);
  uVar13 = param_1[1] & uRam10055d74;
  uVar14 = param_1[2] & uRam10055d78;
  uVar15 = param_1[3] & uRam10055d7c;
  fVar1 = fVar16 * _DAT_10055d60 + _DAT_10055d10;
  fVar4 = fVar17 * fRam10055d64 + fRam10055d14;
  fVar7 = fVar25 * fRam10055d68 + fRam10055d18;
  fVar10 = fVar26 * fRam10055d6c + fRam10055d1c;
  fVar2 = fVar1 - _DAT_10055d10;
  fVar5 = fVar4 - fRam10055d14;
  fVar8 = fVar7 - fRam10055d18;
  fVar11 = fVar10 - fRam10055d1c;
  fVar16 = (((fVar16 - _DAT_10055d50 * fVar2) - _DAT_10055d40 * fVar2) - _DAT_10055d30 * fVar2) -
           _DAT_10055d20 * fVar2;
  fVar2 = (((fVar17 - fRam10055d54 * fVar5) - fRam10055d44 * fVar5) - fRam10055d34 * fVar5) -
          fRam10055d24 * fVar5;
  fVar17 = (((fVar25 - fRam10055d58 * fVar8) - fRam10055d48 * fVar8) - fRam10055d38 * fVar8) -
           fRam10055d28 * fVar8;
  fVar5 = (((fVar26 - fRam10055d5c * fVar11) - fRam10055d4c * fVar11) - fRam10055d3c * fVar11) -
          fRam10055d2c * fVar11;
  fVar25 = fVar16 * fVar16;
  fVar8 = fVar2 * fVar2;
  fVar26 = fVar17 * fVar17;
  fVar11 = fVar5 * fVar5;
  uVar18 = (uint)fVar1 & _DAT_10055ce0;
  uVar19 = (uint)fVar4 & uRam10055ce4;
  uVar21 = (uint)fVar7 & uRam10055ce8;
  uVar23 = (uint)fVar10 & uRam10055cec;
  uVar3 = uVar18 & _DAT_10055cd0;
  uVar6 = uVar19 & uRam10055cd4;
  uVar9 = uVar21 & uRam10055cd8;
  uVar12 = uVar23 & uRam10055cdc;
  uVar20 = uVar19 - uVar6 & uRam10055cc4;
  uVar22 = uVar21 - uVar9 & uRam10055cc8;
  uVar24 = uVar23 - uVar12 & uRam10055ccc;
  uVar27 = uVar18 + uVar3 & _DAT_10055cc0;
  uVar28 = uVar19 + uVar6 & uRam10055cc4;
  uVar21 = uVar21 + uVar9 & uRam10055cc8;
  uVar23 = uVar23 + uVar12 & uRam10055ccc;
  uVar19 = -(uint)((float)(uVar3 << 0x1e) != 0.0);
  uVar6 = -(uint)((float)(uVar6 << 0x1e) != 0.0);
  uVar9 = -(uint)((float)(uVar9 << 0x1e) != 0.0);
  uVar12 = -(uint)((float)(uVar12 << 0x1e) != 0.0);
  fVar16 = (((_DAT_10055d00 * fVar25 + _DAT_10055cb0) * fVar25 + _DAT_10055c90) * fVar25 +
           _DAT_10055c70) * fVar16;
  fVar2 = (((fRam10055d04 * fVar8 + fRam10055cb4) * fVar8 + fRam10055c94) * fVar8 + fRam10055c74) *
          fVar2;
  fVar17 = (((fRam10055d08 * fVar26 + fRam10055cb8) * fVar26 + fRam10055c98) * fVar26 + fRam10055c78
           ) * fVar17;
  fVar5 = (((fRam10055d0c * fVar11 + fRam10055cbc) * fVar11 + fRam10055c9c) * fVar11 + fRam10055c7c)
          * fVar5;
  fVar1 = (((_DAT_10055cf0 * fVar25 + _DAT_10055ca0) * fVar25 + _DAT_10055c80) * fVar25 +
          _DAT_10055c60) * fVar25 + _DAT_10055c50;
  fVar4 = (((fRam10055cf4 * fVar8 + fRam10055ca4) * fVar8 + fRam10055c84) * fVar8 + fRam10055c64) *
          fVar8 + fRam10055c54;
  fVar25 = (((fRam10055cf8 * fVar26 + fRam10055ca8) * fVar26 + fRam10055c88) * fVar26 + fRam10055c68
           ) * fVar26 + fRam10055c58;
  fVar7 = (((fRam10055cfc * fVar11 + fRam10055cac) * fVar11 + fRam10055c8c) * fVar11 + fRam10055c6c)
          * fVar11 + fRam10055c5c;
  *param_2 = (~uVar19 & (uint)fVar16 | uVar19 & (uint)fVar1) ^
             (uVar18 - uVar3 & _DAT_10055cc0) << 0x1e ^ *param_1 & _DAT_10055d70;
  param_2[1] = (~uVar6 & (uint)fVar2 | uVar6 & (uint)fVar4) ^ uVar20 << 0x1e ^ uVar13;
  param_2[2] = (~uVar9 & (uint)fVar17 | uVar9 & (uint)fVar25) ^ uVar22 << 0x1e ^ uVar14;
  param_2[3] = (~uVar12 & (uint)fVar5 | uVar12 & (uint)fVar7) ^ uVar24 << 0x1e ^ uVar15;
  *param_3 = (uVar19 & (uint)fVar16 | ~uVar19 & (uint)fVar1) ^ uVar27 << 0x1e;
  param_3[1] = (uVar6 & (uint)fVar2 | ~uVar6 & (uint)fVar4) ^ uVar28 << 0x1e;
  param_3[2] = (uVar9 & (uint)fVar17 | ~uVar9 & (uint)fVar25) ^ uVar21 << 0x1e;
  param_3[3] = (uVar12 & (uint)fVar5 | ~uVar12 & (uint)fVar7) ^ uVar23 << 0x1e;
  return;
}



/* grim_jpg_idct_descale_round @ 10034e00 */

ulonglong grim_jpg_idct_descale_round(void)

{
  ulonglong in_MM0;
  ulonglong uVar1;
  undefined8 uVar2;
  ulonglong in_MM1;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  uint uVar7;
  uint uVar8;
  ulonglong uVar9;
  
  uVar9 = (DAT_10055e58 & in_MM0) >> 1 | DAT_10055e58 & in_MM1;
  uVar3 = in_MM1 & DAT_10055e5c;
  uVar1 = in_MM0 & DAT_10055e5c;
  uVar2 = PackedFloatingMAX(uVar1,uVar3);
  uVar7 = (uint)((int)uVar1 < (int)uVar3) * -0x80000000;
  uVar4 = PackedFloatingMIN(uVar3,uVar1);
  uVar5 = FloatingReciprocalAprox(uVar1,uVar2);
  uVar2 = PackedFloatingReciprocalIter1(uVar2,uVar5);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar5);
  uVar2 = PackedFloatingMUL(uVar2,uVar4);
  uVar4 = PackedFloatingMUL(uVar2,uVar2);
  uVar5 = PackedFloatingADD((ulonglong)DAT_10055e90,uVar4);
  uVar6 = PackedFloatingMUL((ulonglong)DAT_10055e9c,uVar4);
  uVar5 = PackedFloatingMUL(uVar5,uVar4);
  uVar6 = PackedFloatingADD(uVar6,(ulonglong)DAT_10055e98);
  uVar5 = PackedFloatingADD(uVar5,(ulonglong)DAT_10055e8c);
  uVar6 = PackedFloatingMUL(uVar6,uVar4);
  uVar5 = PackedFloatingMUL(uVar5,uVar4);
  uVar6 = PackedFloatingADD(uVar6,(ulonglong)DAT_10055e94);
  uVar5 = PackedFloatingADD(uVar5,(ulonglong)DAT_10055e88);
  uVar4 = PackedFloatingMUL(uVar4,uVar6);
  uVar4 = PackedFloatingMUL(uVar4,uVar2);
  uVar6 = FloatingReciprocalAprox((ulonglong)DAT_10055e94,uVar5);
  uVar8 = (int)uVar9 << 1;
  uVar5 = PackedFloatingReciprocalIter1(uVar5,uVar6);
  uVar5 = PackedFloatingReciprocalIter2(uVar5,uVar6);
  uVar4 = PackedFloatingMUL(uVar4,uVar5);
  uVar1 = PackedFloatingADD(uVar4,uVar2);
  uVar2 = PackedFloatingSUB(~(ulonglong)(uint)((int)uVar7 >> 0x1f) &
                            (ulonglong)(uVar8 ^ DAT_10055eb8),(ulonglong)DAT_10055eb8);
  uVar1 = PackedFloatingADD(uVar1 | uVar8 ^ uVar7,uVar2);
  return uVar1 | DAT_10055e58 & uVar9;
}



/* grim_jpg_idct_descale_trunc @ 10034f00 */

ulonglong grim_jpg_idct_descale_trunc(void)

{
  uint uVar1;
  ulonglong in_MM0;
  ulonglong uVar2;
  undefined8 uVar3;
  uint uVar4;
  uint uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  ulonglong uVar5;
  
  uVar2 = in_MM0 & DAT_10055e5c;
  uVar6 = -(uint)(DAT_10055e68 < (int)uVar2);
  uVar3 = PackedFloatingMUL(uVar2,(ulonglong)DAT_10055e6c);
  uVar3 = PackedFloatingSUBR(uVar3,(ulonglong)DAT_10055e6c);
  uVar7 = PackedFloatingReciprocalSQRAprox((ulonglong)DAT_10055e5c,uVar3);
  uVar8 = PackedFloatingMUL(uVar7,uVar7);
  uVar1 = (uint)((int)uVar2 < DAT_10055ea0);
  uVar4 = -uVar1;
  uVar5 = (ulonglong)uVar4;
  uVar8 = PackedFloatingReciprocalSQRIter1(uVar8,uVar3);
  uVar7 = PackedFloatingReciprocalIter2(uVar8,uVar7);
  uVar9 = PackedFloatingMUL(uVar7,uVar3);
  uVar2 = ~uVar5 & uVar9 | uVar2 & uVar4;
  uVar3 = PackedFloatingMUL(uVar2,uVar2);
  uVar8 = PackedFloatingMUL((ulonglong)DAT_10055ea8,uVar3);
  uVar7 = PackedFloatingADD((ulonglong)DAT_10055eb0,uVar3);
  uVar8 = PackedFloatingADD(uVar8,(ulonglong)DAT_10055ea4);
  uVar8 = PackedFloatingMUL(uVar8,uVar3);
  uVar3 = PackedFloatingMUL(uVar3,uVar7);
  uVar3 = PackedFloatingADD(uVar3,(ulonglong)DAT_10055eac);
  uVar8 = PackedFloatingMUL(uVar8,uVar2);
  uVar7 = FloatingReciprocalAprox(uVar7,uVar3);
  uVar3 = PackedFloatingReciprocalIter1(uVar3,uVar7);
  uVar3 = PackedFloatingReciprocalIter2(uVar3,uVar7);
  uVar3 = PackedFloatingMUL(uVar3,uVar8);
  uVar2 = PackedFloatingADD(uVar2,uVar3);
  uVar3 = PackedFloatingADD(~uVar5 & (ulonglong)DAT_10055eb8 ^ DAT_10055e58 & in_MM0,
                            (ulonglong)DAT_10055eb4);
  uVar2 = PackedFloatingADD(uVar2,~uVar5 & uVar2);
  uVar2 = PackedFloatingADD(uVar3,uVar2 | (ulonglong)(uVar1 * -0x80000000) ^ DAT_10055e58 & in_MM0);
  return (ulonglong)(DAT_10055e74 & uVar6) | ~(ulonglong)uVar6 & uVar2;
}



/* grim_jpg_idct_coeff_butterfly_a @ 100354e0 */

ulonglong grim_jpg_idct_coeff_butterfly_a(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  ulonglong in_MM0;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  
  uVar1 = (uint)in_MM0;
  if ((int)(uVar1 ^ uVar1 & 0x80000000) < DAT_10055f14) {
    uVar5 = PackedFloatingMUL(in_MM0 & DAT_10055e5c,(ulonglong)DAT_10055f10);
    uVar4 = PackedFloatingToIntDwordConv(uVar5,uVar5);
    uVar2 = (uint)uVar4;
    uVar5 = PackedIntToFloatingDwordConv(uVar4,uVar4);
    uVar5 = PackedFloatingMUL(CONCAT44((int)uVar5,(int)uVar5),DAT_10055e20);
    uVar7 = PackedFloatingADD(in_MM0 & DAT_10055e5c,uVar5);
    uVar6 = (undefined4)((ulonglong)uVar5 >> 0x20);
    uVar5 = PackedFloatingADD(uVar7,CONCAT44(uVar6,uVar6));
    uVar5 = CONCAT44((int)uVar5,(int)uVar5);
    if ((uVar4 & 1) != 0) {
      uVar5 = PackedFloatingSUBR(uVar5,DAT_10055e30);
    }
    iVar3 = (uVar1 >> 0x1f ^ uVar2 >> 2) << 0x1f;
    uVar7 = PackedFloatingMUL(uVar5,uVar5);
    uVar9 = PackedFloatingMUL(DAT_10055e28,uVar7);
    uVar8 = PackedFloatingMUL(DAT_10055e38,uVar7);
    uVar10 = PackedFloatingADD(uVar9,DAT_10055dd8);
    uVar9 = PackedFloatingMUL(DAT_10055e40,uVar7);
    uVar8 = PackedFloatingMUL(uVar10,uVar8);
    uVar10 = PackedFloatingADD(uVar8,DAT_10055dd8);
    uVar8 = PackedFloatingMUL(DAT_10055e48,uVar7);
    uVar7 = PackedFloatingMUL(uVar9,uVar10);
    uVar7 = PackedFloatingADD(uVar7,DAT_10055dd8);
    uVar7 = PackedFloatingMUL(uVar7,CONCAT44((int)DAT_10055dd8,(int)uVar8));
    uVar7 = PackedFloatingADD(uVar7,DAT_10055dd8 >> 0x20);
    uVar4 = PackedFloatingMUL(uVar7,CONCAT44((int)uVar5,(int)DAT_10055dd8));
    if (((uVar2 ^ uVar2 >> 1) & 1) != 0) {
      uVar4 = CONCAT44((int)uVar4,(int)(uVar4 >> 0x20));
    }
    uVar4 = CONCAT44(iVar3,iVar3) ^ uVar4 ^ (uVar1 & 0x80000000 ^ (uVar2 >> 1) << 0x1f);
  }
  else {
    uVar4 = (ulonglong)DAT_10055e68;
  }
  return uVar4;
}



/* grim_jpg_idct_coeff_butterfly_b @ 10035600 */

void grim_jpg_idct_coeff_butterfly_b(void)

{
  ulonglong in_MM0;
  undefined8 uVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if ((int)((uint)in_MM0 ^ (uint)in_MM0 & 0x80000000) < DAT_10055f14) {
    uVar1 = PackedFloatingMUL(in_MM0 & DAT_10055e5c,(ulonglong)DAT_10055f10);
    uVar2 = PackedFloatingToIntDwordConv(uVar1,uVar1);
    uVar1 = PackedIntToFloatingDwordConv(uVar2,uVar2);
    uVar1 = PackedFloatingMUL(CONCAT44((int)uVar1,(int)uVar1),DAT_10055e20);
    uVar4 = PackedFloatingADD(in_MM0 & DAT_10055e5c,uVar1);
    uVar3 = (undefined4)((ulonglong)uVar1 >> 0x20);
    uVar1 = PackedFloatingADD(uVar4,CONCAT44(uVar3,uVar3));
    uVar1 = CONCAT44((int)uVar1,(int)uVar1);
    if ((uVar2 & 1) != 0) {
      uVar1 = PackedFloatingSUBR(uVar1,DAT_10055e30);
    }
    uVar4 = PackedFloatingMUL(uVar1,uVar1);
    uVar6 = PackedFloatingMUL(DAT_10055e28,uVar4);
    uVar5 = PackedFloatingMUL(DAT_10055e38,uVar4);
    uVar7 = PackedFloatingADD(uVar6,DAT_10055dd8);
    uVar6 = PackedFloatingMUL(DAT_10055e40,uVar4);
    uVar5 = PackedFloatingMUL(uVar7,uVar5);
    uVar7 = PackedFloatingADD(uVar5,DAT_10055dd8);
    uVar5 = PackedFloatingMUL(DAT_10055e48,uVar4);
    uVar4 = PackedFloatingMUL(uVar6,uVar7);
    uVar4 = PackedFloatingADD(uVar4,DAT_10055dd8);
    uVar4 = PackedFloatingMUL(uVar4,CONCAT44((int)DAT_10055dd8,(int)uVar5));
    uVar4 = PackedFloatingADD(uVar4,DAT_10055dd8 >> 0x20);
    PackedFloatingMUL(uVar4,CONCAT44((int)uVar1,(int)DAT_10055dd8));
  }
  return;
}



/* grim_jpg_quant_table_build @ 100359f8 */

void __cdecl grim_jpg_quant_table_build(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined1 *puVar5;
  short *psVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  undefined1 uVar10;
  ushort *puVar11;
  int iVar12;
  int local_9c;
  int local_98;
  int local_94;
  int local_90 [3];
  int local_84;
  int local_80 [25];
  uint local_1c;
  ushort *local_18;
  int *local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  iVar8 = *(int *)(param_1 + 0x11c) + 0x80;
  puVar11 = (ushort *)(param_3 + 0x60);
  piVar7 = local_80 + 1;
  local_10 = iVar8;
  param_1 = 8;
  psVar6 = (short *)(*(int *)(param_2 + 0x50) + 0x60);
  do {
    if (param_1 != 4) {
      uVar1 = *puVar11;
      uVar2 = puVar11[-0x18];
      local_8 = CONCAT22(local_8._2_2_,uVar2);
      uVar3 = puVar11[-0x28];
      local_1c = (uint)uVar1;
      local_c = (uint)uVar3;
      if (((((uVar1 == 0 && uVar3 == 0) && uVar2 == 0) && puVar11[-8] == 0) && puVar11[8] == 0) &&
          puVar11[-0x20] == 0) {
        iVar4 = (int)psVar6[-0x30] * (int)(short)puVar11[-0x30] * 4;
        piVar7[-8] = iVar4;
        *piVar7 = iVar4;
        piVar7[0x10] = iVar4;
      }
      else {
        iVar12 = (short)(psVar6[-0x20] * puVar11[-0x20]) * 0x3b21 +
                 (short)(*psVar6 * uVar1) * -0x187e;
        iVar4 = (int)psVar6[-0x30] * (int)(short)puVar11[-0x30] * 0x4000;
        iVar8 = iVar12 + iVar4;
        iVar4 = iVar4 - iVar12;
        param_2._0_2_ = psVar6[-8] * puVar11[-8];
        param_3._0_2_ = psVar6[-0x18] * uVar2;
        local_c = (int)psVar6[-0x28] * (int)(short)uVar3;
        local_c._0_2_ = (short)((int)psVar6[-0x28] * (int)(short)uVar3);
        local_8 = (int)(short)local_c;
        iVar12 = (int)(short)(psVar6[8] * puVar11[8]);
        iVar9 = (short)param_2 * 0x2e75 + local_8 * 0x21f9 + iVar12 * -0x6c2 +
                (short)param_3 * -0x4587;
        iVar12 = (short)param_3 * 0x1ccd + (short)param_2 * -0x133e + iVar12 * -0x1050 +
                 local_8 * 0x5203;
        local_18 = puVar11;
        piVar7[-8] = iVar8 + 0x800 + iVar12 >> 0xc;
        piVar7[0x10] = (iVar8 - iVar12) + 0x800 >> 0xc;
        iVar8 = local_10;
        *piVar7 = iVar4 + 0x800 + iVar9 >> 0xc;
        iVar4 = (iVar4 - iVar9) + 0x800 >> 0xc;
        puVar11 = local_18;
      }
      piVar7[8] = iVar4;
    }
    puVar11 = puVar11 + 1;
    piVar7 = piVar7 + 1;
    psVar6 = psVar6 + 1;
    param_1 = param_1 + -1;
    local_18 = puVar11;
    local_14 = piVar7;
  } while (0 < param_1);
  param_1 = 0;
  piVar7 = &local_9c;
  do {
    puVar5 = (undefined1 *)(*(int *)(param_4 + param_1 * 4) + param_5);
    if (((((piVar7[1] == 0 && piVar7[3] == 0) && piVar7[5] == 0) && piVar7[7] == 0) &&
        piVar7[6] == 0) && piVar7[2] == 0) {
      uVar10 = *(undefined1 *)((*piVar7 + 0x10 >> 5 & 0x3ffU) + iVar8);
      *puVar5 = uVar10;
      puVar5[1] = uVar10;
      puVar5[3] = uVar10;
    }
    else {
      iVar4 = (short)piVar7[2] * 0x3b21 + (short)piVar7[6] * -0x187e;
      iVar8 = iVar4 + *piVar7 * 0x4000;
      local_c = *piVar7 * 0x4000 - iVar4;
      iVar4 = (int)(short)piVar7[5];
      local_8 = (int)(short)piVar7[1];
      iVar12 = iVar4 * 0x2e75 + local_8 * 0x21f9 + (short)piVar7[7] * -0x6c2 +
               (short)piVar7[3] * -0x4587;
      iVar4 = (short)piVar7[3] * 0x1ccd + iVar4 * -0x133e + (short)piVar7[7] * -0x1050 +
              local_8 * 0x5203;
      *puVar5 = *(undefined1 *)((iVar8 + 0x40000 + iVar4 >> 0x13 & 0x3ffU) + local_10);
      puVar5[3] = *(undefined1 *)(((iVar8 - iVar4) + 0x40000 >> 0x13 & 0x3ffU) + local_10);
      puVar5[1] = *(undefined1 *)(((int)(local_c + 0x40000 + iVar12) >> 0x13 & 0x3ffU) + local_10);
      uVar10 = *(undefined1 *)(((int)((local_c - iVar12) + 0x40000) >> 0x13 & 0x3ffU) + local_10);
      iVar8 = local_10;
    }
    piVar7 = piVar7 + 8;
    param_1 = param_1 + 1;
    puVar5[2] = uVar10;
  } while (param_1 < 4);
  return;
}



/* grim_jpg_quant_prescale @ 10035d0d */

void __cdecl grim_jpg_quant_prescale(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  undefined1 uVar3;
  short *psVar4;
  int iVar5;
  short *psVar6;
  undefined1 *puVar7;
  int local_4c;
  int local_48 [2];
  int local_40 [2];
  int local_38 [2];
  int local_30 [9];
  int local_c;
  int *local_8;
  
  iVar5 = *(int *)(param_1 + 0x11c) + 0x80;
  piVar2 = &local_4c;
  psVar6 = (short *)(param_3 + 0x30);
  local_c = iVar5;
  param_1 = 8;
  psVar4 = (short *)(*(int *)(param_2 + 0x50) + 0x30);
  do {
    if (((param_1 != 6) && (param_1 != 4)) && (param_1 != 2)) {
      if (((psVar6[0x20] == 0 && psVar6[0x10] == 0) && psVar6[-0x10] == 0) && *psVar6 == 0) {
        iVar1 = (int)psVar4[-0x18] * (int)psVar6[-0x18] * 4;
        *piVar2 = iVar1;
      }
      else {
        iVar5 = (int)psVar4[-0x18] * (int)psVar6[-0x18] * 0x8000;
        iVar1 = (short)(psVar4[0x10] * psVar6[0x10]) * 0x1b37 +
                (short)(psVar4[0x20] * psVar6[0x20]) * -0x1712 +
                (short)(psVar4[-0x10] * psVar6[-0x10]) * 0x73fc +
                (short)(*psVar4 * *psVar6) * -0x28ba;
        *piVar2 = iVar1 + 0x1000 + iVar5 >> 0xd;
        iVar1 = (iVar5 - iVar1) + 0x1000 >> 0xd;
        iVar5 = local_c;
      }
      piVar2[8] = iVar1;
    }
    psVar6 = psVar6 + 1;
    piVar2 = piVar2 + 1;
    psVar4 = psVar4 + 1;
    param_1 = param_1 + -1;
    local_8 = piVar2;
  } while (0 < param_1);
  param_1 = 0;
  piVar2 = &local_4c;
  do {
    puVar7 = (undefined1 *)(*(int *)(param_4 + param_1 * 4) + param_5);
    if (((piVar2[7] == 0 && piVar2[3] == 0) && piVar2[1] == 0) && piVar2[5] == 0) {
      uVar3 = *(undefined1 *)((*piVar2 + 0x10 >> 5 & 0x3ffU) + iVar5);
      *puVar7 = uVar3;
    }
    else {
      iVar5 = *piVar2 * 0x8000;
      iVar1 = (short)piVar2[3] * -0x28ba + (short)piVar2[7] * -0x1712 + (short)piVar2[1] * 0x73fc +
              (short)piVar2[5] * 0x1b37;
      *puVar7 = *(undefined1 *)((iVar1 + 0x80000 + iVar5 >> 0x14 & 0x3ffU) + local_c);
      uVar3 = *(undefined1 *)(((iVar5 - iVar1) + 0x80000 >> 0x14 & 0x3ffU) + local_c);
      iVar5 = local_c;
    }
    piVar2 = piVar2 + 8;
    param_1 = param_1 + 1;
    puVar7[1] = uVar3;
  } while (param_1 < 2);
  return;
}



/* grim_jpg_output_line_noop @ 10035ecb */

void __cdecl grim_jpg_output_line_noop(int param_1,int param_2,short *param_3,int *param_4,int param_5)

{
  *(undefined1 *)(param_5 + *param_4) =
       *(undefined1 *)
        (((int)**(short **)(param_2 + 0x50) * (int)*param_3 + 4 >> 3 & 0x3ffU) + 0x80 +
        *(int *)(param_1 + 0x11c));
  return;
}



/* grim_jpg_output_line_islow_setup @ 10035f08 */

void __cdecl grim_jpg_output_line_islow_setup(int param_1,int param_2,short *param_3,int param_4,int param_5)

{
  int iVar1;
  int aiStack_90 [35];
  
  iVar1 = *(int *)(param_1 + 0x11c) + 0x80;
  if (grim_jpg_idct_mode == '\0') {
    grim_jpg_idct_8x8_islow_col(param_3,*(short **)(param_2 + 0x50),aiStack_90,param_4,param_5,iVar1);
  }
  else {
    grim_jpg_idct_8x8_islow_row((undefined8 *)param_3,(undefined8 *)*(short **)(param_2 + 0x50),
                 (undefined8 *)aiStack_90,param_4,param_5,iVar1);
  }
  return;
}



/* grim_jpg_output_line_ifast_setup @ 10035f54 */

void __cdecl grim_jpg_output_line_ifast_setup(int param_1,int param_2,short *param_3,int *param_4,int param_5)

{
  int iVar1;
  short asStack_90 [70];
  
  iVar1 = *(int *)(param_1 + 0x11c) + 0x80;
  if (grim_jpg_idct_mode == '\0') {
    grim_jpg_idct_8x8_ifast_col(param_3,asStack_90,*(short **)(param_2 + 0x50),(int)param_4,param_5,iVar1);
  }
  else {
    grim_jpg_idct_8x8_ifast_row((undefined8 *)param_3,(undefined8 *)asStack_90,
                 (undefined8 *)*(short **)(param_2 + 0x50),param_4,param_5,iVar1);
  }
  return;
}



/* grim_jpg_idct_8x8_islow_col @ 10036f75 */

void __cdecl
grim_jpg_idct_8x8_islow_col(short *param_1,short *param_2,int *param_3,int param_4,int param_5,int param_6)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  undefined4 *puVar19;
  short *local_48;
  short *local_44;
  int *local_40;
  int local_3c;
  int local_8;
  
  local_48 = param_1;
  local_44 = param_2;
  local_40 = param_3;
  local_3c = 8;
  do {
    iVar15 = ((int)local_48[0x10] * (int)local_44[0x10] + (int)local_48[0x30] * (int)local_44[0x30])
             * 0x1151;
    iVar8 = (int)local_48[0x30] * (int)local_44[0x30] * -0x3b21 + iVar15;
    iVar15 = (int)local_48[0x10] * (int)local_44[0x10] * 0x187e + iVar15;
    iVar9 = ((int)local_48[0x20] * (int)local_44[0x20] + (int)*local_48 * (int)*local_44) * 0x2000;
    iVar5 = ((int)*local_48 * (int)*local_44 - (int)local_48[0x20] * (int)local_44[0x20]) * 0x2000;
    iVar10 = iVar9 + iVar15;
    iVar6 = iVar5 + iVar8;
    iVar9 = iVar9 - iVar15;
    iVar5 = iVar5 - iVar8;
    iVar15 = (int)local_48[0x38] * (int)local_44[0x38];
    iVar11 = (int)local_48[0x18] * (int)local_44[0x18];
    iVar16 = (int)local_48[8] * (int)local_44[8];
    iVar8 = (int)local_48[0x28] * (int)local_44[0x28];
    iVar7 = (iVar15 + iVar16) * -0x1ccd;
    iVar13 = (iVar8 + iVar11) * -0x5203;
    iVar17 = (iVar15 + iVar11 + iVar8 + iVar16) * 0x25a1;
    iVar12 = (iVar15 + iVar11) * -0x3ec5 + iVar17;
    iVar17 = (iVar8 + iVar16) * -0xc7c + iVar17;
    iVar15 = iVar7 + iVar12 + iVar15 * 0x98e;
    iVar14 = iVar13 + iVar17 + iVar8 * 0x41b3;
    iVar8 = iVar12 + iVar13 + iVar11 * 0x6254;
    iVar7 = iVar7 + iVar17 + iVar16 * 0x300b;
    local_40[0x20] = (iVar9 - iVar15) + 0x400 >> 0xb;
    local_40[0x18] = iVar15 + iVar9 + 0x400 >> 0xb;
    local_40[0x28] = (iVar5 - iVar14) + 0x400 >> 0xb;
    local_40[0x30] = (iVar6 - iVar8) + 0x400 >> 0xb;
    local_40[0x10] = iVar14 + iVar5 + 0x400 >> 0xb;
    local_40[8] = iVar8 + iVar6 + 0x400 >> 0xb;
    local_40[0x38] = (iVar10 - iVar7) + 0x400 >> 0xb;
    *local_40 = iVar10 + iVar7 + 0x400 >> 0xb;
    local_48 = local_48 + 1;
    local_40 = local_40 + 1;
    local_44 = local_44 + 1;
    local_3c = local_3c + -1;
  } while (local_3c != 0);
  local_3c = 8;
  local_8 = 0;
  local_40 = param_3;
  do {
    piVar18 = (int *)(param_4 + local_8);
    local_8 = local_8 + 4;
    puVar19 = (undefined4 *)(*piVar18 + param_5);
    iVar15 = (local_40[2] + local_40[6]) * 0x1151;
    iVar5 = local_40[6] * -0x3b21 + iVar15;
    iVar15 = local_40[2] * 0x187e + iVar15;
    iVar11 = (local_40[4] + *local_40) * 0x2000;
    iVar7 = (*local_40 - local_40[4]) * 0x2000;
    iVar12 = iVar11 + iVar15;
    iVar9 = iVar7 + iVar5;
    iVar11 = iVar11 - iVar15;
    iVar7 = iVar7 - iVar5;
    iVar15 = local_40[7];
    iVar5 = local_40[3];
    iVar6 = local_40[1];
    iVar8 = local_40[5];
    iVar10 = (iVar15 + iVar6) * -0x1ccd;
    iVar14 = (iVar8 + iVar5) * -0x5203;
    iVar16 = (iVar15 + iVar5 + iVar8 + iVar6) * 0x25a1;
    iVar13 = (iVar15 + iVar5) * -0x3ec5 + iVar16;
    iVar16 = (iVar8 + iVar6) * -0xc7c + iVar16;
    iVar15 = iVar10 + iVar13 + iVar15 * 0x98e;
    iVar8 = iVar14 + iVar16 + iVar8 * 0x41b3;
    iVar5 = iVar13 + iVar14 + iVar5 * 0x6254;
    iVar6 = iVar10 + iVar16 + iVar6 * 0x300b;
    uVar1 = *(undefined1 *)(param_6 + ((iVar12 - iVar6) + 0x20000 >> 0x12 & 0x3ffU));
    uVar2 = *(undefined1 *)(param_6 + ((iVar9 - iVar5) + 0x20000 >> 0x12 & 0x3ffU));
    uVar3 = *(undefined1 *)(param_6 + ((iVar7 - iVar8) + 0x20000 >> 0x12 & 0x3ffU));
    uVar4 = *(undefined1 *)(param_6 + ((iVar11 - iVar15) + 0x20000 >> 0x12 & 0x3ffU));
    *puVar19 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)
                                           (param_6 + (iVar11 + iVar15 + 0x20000 >> 0x12 & 0x3ffU)),
                                          *(undefined1 *)
                                           (param_6 + (iVar7 + iVar8 + 0x20000 >> 0x12 & 0x3ffU))),
                                 *(undefined1 *)
                                  (param_6 + (iVar9 + iVar5 + 0x20000 >> 0x12 & 0x3ffU))),
                        *(undefined1 *)(param_6 + (iVar12 + iVar6 + 0x20000 >> 0x12 & 0x3ffU)));
    puVar19[1] = CONCAT31(CONCAT21(CONCAT11(uVar1,uVar2),uVar3),uVar4);
    local_40 = local_40 + 8;
    local_3c = local_3c + -1;
  } while (local_3c != 0);
  return;
}



/* grim_jpg_idct_8x8_islow_row @ 100373d7 */

void __cdecl
grim_jpg_idct_8x8_islow_row(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4,int param_5,
            int param_6)

{
  undefined2 uVar1;
  int *piVar2;
  short sVar3;
  int iVar4;
  short sVar6;
  short sVar7;
  short sVar10;
  undefined8 uVar5;
  int iVar8;
  int iVar9;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  short sVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  short sVar24;
  short sVar25;
  short sVar29;
  ulonglong uVar21;
  int iVar26;
  int iVar27;
  ulonglong uVar22;
  ulonglong uVar23;
  int iVar28;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  ulonglong uVar34;
  int iVar38;
  int iVar39;
  ulonglong uVar35;
  ulonglong uVar36;
  int iVar40;
  ulonglong uVar37;
  short sVar41;
  int iVar42;
  int iVar43;
  int iVar44;
  short sVar50;
  undefined8 uVar45;
  short sVar49;
  int iVar51;
  int iVar52;
  short sVar54;
  ulonglong uVar47;
  int iVar53;
  undefined8 uVar48;
  int iVar55;
  int iVar56;
  int iVar57;
  undefined8 uVar58;
  int iVar60;
  int iVar61;
  int iVar62;
  undefined8 uVar59;
  short sVar63;
  int iVar64;
  short sVar67;
  short sVar68;
  undefined8 uVar65;
  int iVar69;
  short sVar70;
  int iVar71;
  int iVar72;
  ulonglong uVar73;
  int iVar74;
  int iVar75;
  undefined8 *local_18;
  undefined8 *local_14;
  undefined8 *local_10;
  int local_c;
  int local_8;
  ulonglong uVar46;
  ulonglong uVar66;
  
  local_18 = param_1;
  local_10 = param_2;
  local_8 = 2;
  local_14 = param_3;
  do {
    uVar5 = local_18[4];
    uVar45 = local_10[4];
    uVar58 = local_18[0xc];
    sVar3 = (short)uVar5 * (short)uVar45;
    sVar6 = (short)((ulonglong)uVar5 >> 0x10) * (short)((ulonglong)uVar45 >> 0x10);
    sVar7 = (short)((ulonglong)uVar5 >> 0x20) * (short)((ulonglong)uVar45 >> 0x20);
    sVar10 = (short)((ulonglong)uVar5 >> 0x30) * (short)((ulonglong)uVar45 >> 0x30);
    uVar37 = CONCAT26(sVar10,CONCAT24(sVar7,CONCAT22(sVar6,sVar3)));
    uVar5 = local_10[0xc];
    sVar17 = (short)uVar58 * (short)uVar5;
    sVar24 = (short)((ulonglong)uVar58 >> 0x10) * (short)((ulonglong)uVar5 >> 0x10);
    sVar25 = (short)((ulonglong)uVar58 >> 0x20) * (short)((ulonglong)uVar5 >> 0x20);
    sVar29 = (short)((ulonglong)uVar58 >> 0x30) * (short)((ulonglong)uVar5 >> 0x30);
    uVar34 = CONCAT26(sVar29,CONCAT24(sVar25,CONCAT22(sVar24,sVar17)));
    uVar45 = pmaddwd(uVar37,0x187e0000187e);
    uVar58 = pmaddwd(uVar37 >> 0x10,0x187e0000187e);
    uVar37 = CONCAT26(sVar10 + sVar29,
                      CONCAT24(sVar7 + sVar25,CONCAT22(sVar6 + sVar24,sVar3 + sVar17)));
    uVar21 = pmaddwd(uVar34,0x3b2100003b21);
    uVar34 = pmaddwd(uVar34 >> 0x10,0x3b2100003b21);
    uVar5 = pmaddwd(uVar37,0x115100001151);
    uVar65 = pmaddwd(uVar37 >> 0x10,0x115100001151);
    iVar18 = (int)(uVar21 ^ 0xffffffffffffffff) + 1 + (int)uVar5;
    iVar51 = (int)((ulonglong)uVar5 >> 0x20);
    iVar26 = (int)((uVar21 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar51;
    iVar42 = (int)uVar45 + (int)uVar5;
    iVar51 = (int)((ulonglong)uVar45 >> 0x20) + iVar51;
    uVar5 = *local_18;
    iVar30 = (int)(uVar34 ^ 0xffffffffffffffff) + 1 + (int)uVar65;
    iVar60 = (int)((ulonglong)uVar65 >> 0x20);
    iVar38 = (int)((uVar34 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar60;
    uVar45 = *local_10;
    iVar55 = (int)uVar58 + (int)uVar65;
    iVar60 = (int)((ulonglong)uVar58 >> 0x20) + iVar60;
    uVar58 = local_18[8];
    sVar3 = (short)uVar5 * (short)uVar45;
    sVar6 = (short)((ulonglong)uVar5 >> 0x10) * (short)((ulonglong)uVar45 >> 0x10);
    sVar7 = (short)((ulonglong)uVar5 >> 0x20) * (short)((ulonglong)uVar45 >> 0x20);
    sVar10 = (short)((ulonglong)uVar5 >> 0x30) * (short)((ulonglong)uVar45 >> 0x30);
    uVar5 = local_10[8];
    sVar17 = (short)uVar58 * (short)uVar5;
    sVar24 = (short)((ulonglong)uVar58 >> 0x10) * (short)((ulonglong)uVar5 >> 0x10);
    sVar25 = (short)((ulonglong)uVar58 >> 0x20) * (short)((ulonglong)uVar5 >> 0x20);
    sVar29 = (short)((ulonglong)uVar58 >> 0x30) * (short)((ulonglong)uVar5 >> 0x30);
    uVar37 = CONCAT26(sVar10 + sVar29,
                      CONCAT24(sVar7 + sVar25,CONCAT22(sVar6 + sVar24,sVar3 + sVar17)));
    uVar34 = CONCAT26(sVar10 - sVar29,
                      CONCAT24(sVar7 - sVar25,CONCAT22(sVar6 - sVar24,sVar3 - sVar17)));
    uVar5 = pmaddwd(uVar37,0x100000001);
    uVar65 = pmaddwd(uVar37 >> 0x10,0x100000001);
    uVar45 = pmaddwd(uVar34,0x100000001);
    uVar58 = pmaddwd(uVar34 >> 0x10,0x100000001);
    iVar4 = (int)uVar5 * 0x2000;
    iVar8 = (int)((ulonglong)uVar5 >> 0x20) * 0x2000;
    iVar64 = (int)uVar65 * 0x2000;
    iVar69 = (int)((ulonglong)uVar65 >> 0x20) * 0x2000;
    iVar43 = iVar42 + iVar4;
    iVar52 = iVar51 + iVar8;
    iVar4 = iVar4 - iVar42;
    iVar8 = iVar8 - iVar51;
    iVar19 = (int)uVar58 * 0x2000;
    iVar27 = (int)((ulonglong)uVar58 >> 0x20) * 0x2000;
    iVar56 = iVar55 + iVar64;
    iVar61 = iVar60 + iVar69;
    iVar64 = iVar64 - iVar55;
    iVar69 = iVar69 - iVar60;
    iVar31 = iVar30 + iVar19;
    iVar39 = iVar38 + iVar27;
    iVar11 = (int)uVar45 * 0x2000;
    iVar14 = (int)((ulonglong)uVar45 >> 0x20) * 0x2000;
    iVar19 = iVar19 - iVar30;
    iVar27 = iVar27 - iVar38;
    uVar5 = local_18[2];
    iVar30 = iVar18 + iVar11;
    iVar55 = iVar26 + iVar14;
    uVar45 = local_10[2];
    iVar11 = iVar11 - iVar18;
    iVar14 = iVar14 - iVar26;
    uVar58 = local_18[0xe];
    sVar63 = (short)uVar5 * (short)uVar45;
    sVar67 = (short)((ulonglong)uVar5 >> 0x10) * (short)((ulonglong)uVar45 >> 0x10);
    sVar68 = (short)((ulonglong)uVar5 >> 0x20) * (short)((ulonglong)uVar45 >> 0x20);
    sVar70 = (short)((ulonglong)uVar5 >> 0x30) * (short)((ulonglong)uVar45 >> 0x30);
    uVar66 = CONCAT26(sVar70,CONCAT24(sVar68,CONCAT22(sVar67,sVar63)));
    uVar5 = local_10[0xe];
    uVar45 = local_18[10];
    sVar3 = (short)uVar58 * (short)uVar5;
    sVar6 = (short)((ulonglong)uVar58 >> 0x10) * (short)((ulonglong)uVar5 >> 0x10);
    sVar7 = (short)((ulonglong)uVar58 >> 0x20) * (short)((ulonglong)uVar5 >> 0x20);
    sVar10 = (short)((ulonglong)uVar58 >> 0x30) * (short)((ulonglong)uVar5 >> 0x30);
    uVar37 = CONCAT26(sVar10,CONCAT24(sVar7,CONCAT22(sVar6,sVar3)));
    uVar5 = local_10[10];
    uVar58 = local_18[6];
    sVar17 = (short)uVar45 * (short)uVar5;
    sVar24 = (short)((ulonglong)uVar45 >> 0x10) * (short)((ulonglong)uVar5 >> 0x10);
    sVar25 = (short)((ulonglong)uVar45 >> 0x20) * (short)((ulonglong)uVar5 >> 0x20);
    sVar29 = (short)((ulonglong)uVar45 >> 0x30) * (short)((ulonglong)uVar5 >> 0x30);
    uVar22 = CONCAT26(sVar29,CONCAT24(sVar25,CONCAT22(sVar24,sVar17)));
    uVar5 = local_10[6];
    sVar41 = (short)uVar58 * (short)uVar5;
    sVar49 = (short)((ulonglong)uVar58 >> 0x10) * (short)((ulonglong)uVar5 >> 0x10);
    sVar50 = (short)((ulonglong)uVar58 >> 0x20) * (short)((ulonglong)uVar5 >> 0x20);
    sVar54 = (short)((ulonglong)uVar58 >> 0x30) * (short)((ulonglong)uVar5 >> 0x30);
    uVar46 = CONCAT26(sVar54,CONCAT24(sVar50,CONCAT22(sVar49,sVar41)));
    uVar34 = CONCAT26(sVar10 + sVar70,
                      CONCAT24(sVar7 + sVar68,CONCAT22(sVar6 + sVar67,sVar3 + sVar63)));
    uVar47 = CONCAT26(sVar29 + sVar54,
                      CONCAT24(sVar25 + sVar50,CONCAT22(sVar24 + sVar49,sVar17 + sVar41)));
    uVar36 = CONCAT26(sVar10 + sVar54,
                      CONCAT24(sVar7 + sVar50,CONCAT22(sVar6 + sVar49,sVar3 + sVar41)));
    uVar35 = CONCAT26(sVar29 + sVar70,
                      CONCAT24(sVar25 + sVar68,CONCAT22(sVar24 + sVar67,sVar17 + sVar63)));
    uVar23 = CONCAT26(sVar10 + sVar54 + sVar29 + sVar70,
                      CONCAT24(sVar7 + sVar50 + sVar25 + sVar68,
                               CONCAT22(sVar6 + sVar49 + sVar24 + sVar67,
                                        sVar3 + sVar41 + sVar17 + sVar63)));
    uVar5 = pmaddwd(uVar23,0x25a1000025a1);
    uVar21 = pmaddwd(uVar34,0x1ccd00001ccd);
    uVar45 = pmaddwd(uVar23 >> 0x10,0x25a1000025a1);
    iVar26 = (int)(uVar21 ^ 0xffffffffffffffff) + 1;
    iVar60 = (int)((uVar21 ^ 0xffffffffffffffff) >> 0x20) + 1;
    uVar23 = pmaddwd(uVar47,0x520300005203);
    uVar47 = pmaddwd(uVar47 >> 0x10,0x520300005203);
    uVar73 = pmaddwd(uVar34 >> 0x10,0x1ccd00001ccd);
    uVar21 = pmaddwd(uVar36,0x3ec500003ec5);
    iVar20 = (int)(uVar23 ^ 0xffffffffffffffff) + 1;
    iVar28 = (int)((uVar23 ^ 0xffffffffffffffff) >> 0x20) + 1;
    uVar23 = pmaddwd(uVar36 >> 0x10,0x3ec500003ec5);
    uVar36 = pmaddwd(uVar35,0xc7c00000c7c);
    iVar44 = (int)(uVar47 ^ 0xffffffffffffffff) + 1;
    iVar53 = (int)((uVar47 ^ 0xffffffffffffffff) >> 0x20) + 1;
    uVar34 = pmaddwd(uVar35 >> 0x10,0xc7c00000c7c);
    iVar71 = (int)(uVar73 ^ 0xffffffffffffffff) + 1;
    iVar74 = (int)((uVar73 ^ 0xffffffffffffffff) >> 0x20) + 1;
    iVar12 = (int)(uVar21 ^ 0xffffffffffffffff) + 1 + (int)uVar5;
    iVar51 = (int)((ulonglong)uVar5 >> 0x20);
    iVar15 = (int)((uVar21 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar51;
    iVar57 = (int)(uVar23 ^ 0xffffffffffffffff) + 1 + (int)uVar45;
    iVar18 = (int)((ulonglong)uVar45 >> 0x20);
    iVar62 = (int)((uVar23 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar18;
    iVar32 = (int)(uVar36 ^ 0xffffffffffffffff) + 1 + (int)uVar5;
    iVar51 = (int)((uVar36 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar51;
    iVar38 = (int)(uVar34 ^ 0xffffffffffffffff) + 1 + (int)uVar45;
    iVar18 = (int)((uVar34 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar18;
    uVar5 = pmaddwd(uVar37,0x98e0000098e);
    uVar45 = pmaddwd(uVar37 >> 0x10,0x98e0000098e);
    uVar65 = pmaddwd(uVar22,0x41b3000041b3);
    uVar58 = pmaddwd(uVar22 >> 0x10,0x41b3000041b3);
    uVar59 = pmaddwd(uVar46,0x625400006254);
    uVar48 = pmaddwd(uVar46 >> 0x10,0x625400006254);
    iVar42 = (int)uVar5 + iVar26 + iVar12;
    iVar9 = (int)((ulonglong)uVar5 >> 0x20) + iVar60 + iVar15;
    iVar13 = (int)uVar45 + iVar71 + iVar57;
    iVar16 = (int)((ulonglong)uVar45 >> 0x20) + iVar74 + iVar62;
    uVar45 = pmaddwd(uVar66,0x300b0000300b);
    iVar33 = (int)uVar65 + iVar20 + iVar32;
    iVar40 = (int)((ulonglong)uVar65 >> 0x20) + iVar28 + iVar51;
    uVar5 = pmaddwd(uVar66 >> 0x10,0x300b0000300b);
    iVar72 = (int)uVar45 + iVar32 + iVar26;
    iVar75 = (int)((ulonglong)uVar45 >> 0x20) + iVar51 + iVar60;
    iVar32 = (int)uVar5 + iVar38 + iVar71;
    iVar71 = (int)((ulonglong)uVar5 >> 0x20) + iVar18 + iVar74;
    iVar51 = (int)uVar58 + iVar44 + iVar38;
    iVar18 = (int)((ulonglong)uVar58 >> 0x20) + iVar53 + iVar18;
    iVar60 = (int)uVar59 + iVar12 + iVar20;
    iVar12 = (int)((ulonglong)uVar59 >> 0x20) + iVar15 + iVar28;
    iVar26 = (int)uVar48 + iVar57 + iVar44;
    iVar38 = (int)((ulonglong)uVar48 >> 0x20) + iVar62 + iVar53;
    local_14[0xe] =
         CONCAT44(CONCAT22((short)((iVar61 - iVar71) + 0x400 >> 0xb),
                           (short)((iVar52 - iVar75) + 0x400 >> 0xb)),
                  CONCAT22((short)((iVar56 - iVar32) + 0x400 >> 0xb),
                           (short)((iVar43 - iVar72) + 0x400 >> 0xb)));
    *local_14 = CONCAT44(CONCAT22((short)(iVar71 + iVar61 + 0x400 >> 0xb),
                                  (short)(iVar75 + iVar52 + 0x400 >> 0xb)),
                         CONCAT22((short)(iVar32 + iVar56 + 0x400 >> 0xb),
                                  (short)(iVar72 + iVar43 + 0x400 >> 0xb)));
    local_14[0xc] =
         CONCAT44(CONCAT22((short)((iVar39 - iVar38) + 0x400 >> 0xb),
                           (short)((iVar55 - iVar12) + 0x400 >> 0xb)),
                  CONCAT22((short)((iVar31 - iVar26) + 0x400 >> 0xb),
                           (short)((iVar30 - iVar60) + 0x400 >> 0xb)));
    local_14[2] = CONCAT44(CONCAT22((short)(iVar38 + iVar39 + 0x400 >> 0xb),
                                    (short)(iVar12 + iVar55 + 0x400 >> 0xb)),
                           CONCAT22((short)(iVar26 + iVar31 + 0x400 >> 0xb),
                                    (short)(iVar60 + iVar30 + 0x400 >> 0xb)));
    local_14[4] = CONCAT44(CONCAT22((short)(iVar27 + iVar18 + 0x400 >> 0xb),
                                    (short)(iVar14 + iVar40 + 0x400 >> 0xb)),
                           CONCAT22((short)(iVar19 + iVar51 + 0x400 >> 0xb),
                                    (short)(iVar11 + iVar33 + 0x400 >> 0xb)));
    local_14[10] = CONCAT44(CONCAT22((short)((iVar27 - iVar18) + 0x400 >> 0xb),
                                     (short)((iVar14 - iVar40) + 0x400 >> 0xb)),
                            CONCAT22((short)((iVar19 - iVar51) + 0x400 >> 0xb),
                                     (short)((iVar11 - iVar33) + 0x400 >> 0xb)));
    local_14[6] = CONCAT44(CONCAT22((short)(iVar69 + iVar16 + 0x400 >> 0xb),
                                    (short)(iVar8 + iVar9 + 0x400 >> 0xb)),
                           CONCAT22((short)(iVar64 + iVar13 + 0x400 >> 0xb),
                                    (short)(iVar4 + iVar42 + 0x400 >> 0xb)));
    local_18 = local_18 + 1;
    local_10 = local_10 + 1;
    local_14[8] = CONCAT44(CONCAT22((short)((iVar69 - iVar16) + 0x400 >> 0xb),
                                    (short)((iVar8 - iVar9) + 0x400 >> 0xb)),
                           CONCAT22((short)((iVar64 - iVar13) + 0x400 >> 0xb),
                                    (short)((iVar4 - iVar42) + 0x400 >> 0xb)));
    local_14 = local_14 + 1;
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  local_8 = 8;
  local_14 = param_3;
  local_c = 0;
  do {
    uVar5 = *local_14;
    uVar45 = local_14[1];
    sVar3 = (short)uVar45;
    sVar17 = (short)uVar5;
    sVar6 = (short)((ulonglong)uVar45 >> 0x10);
    sVar24 = (short)((ulonglong)uVar5 >> 0x10);
    iVar51 = CONCAT22(sVar24 + sVar6,sVar17 + sVar3);
    sVar7 = (short)((ulonglong)uVar45 >> 0x20);
    sVar25 = (short)((ulonglong)uVar5 >> 0x20);
    sVar29 = (short)((ulonglong)uVar5 >> 0x30);
    sVar10 = (short)((ulonglong)uVar45 >> 0x30);
    uVar65 = pmaddwd(CONCAT44((int)((ulonglong)uVar45 >> 0x20),(int)((ulonglong)uVar5 >> 0x20)),
                     0x3b210000187e);
    uVar58 = pmaddwd(CONCAT26(sVar29 + sVar10,CONCAT24(sVar25 + sVar7,iVar51)),0x115100000000);
    iVar18 = (int)((ulonglong)uVar58 >> 0x20);
    iVar26 = (iVar51 << 0x10) >> 3;
    iVar42 = (int)((uint)(ushort)(sVar17 - sVar3) << 0x10) >> 3;
    iVar51 = (int)uVar65 + iVar18;
    iVar18 = ((uint)((ulonglong)uVar65 >> 0x20) ^ 0xffffffff) + 1 + iVar18;
    sVar41 = sVar17 + sVar3;
    sVar49 = sVar24 + sVar6;
    iVar38 = iVar26 + iVar51;
    iVar8 = iVar42 + iVar18;
    iVar26 = iVar26 - iVar51;
    iVar42 = iVar42 - iVar18;
    uVar5 = pmaddwd(uVar5,0x62540000300b0000);
    uVar58 = pmaddwd(CONCAT26(sVar49 + sVar29 + sVar10,
                              CONCAT24(sVar41 + sVar25 + sVar7,CONCAT22(sVar49 * 2,sVar41 * 2))),
                     0x25a1000000000000);
    uVar37 = pmaddwd(CONCAT26(sVar29 + sVar10,CONCAT24(sVar25 + sVar7,CONCAT22(sVar49,sVar41))),
                     0x3ec500000c7c0000);
    uVar34 = pmaddwd(CONCAT26(sVar24 + sVar10,
                              CONCAT24(sVar17 + sVar7,CONCAT22(sVar29 + sVar6,sVar25 + sVar3))),
                     0x1ccd000052030000);
    uVar45 = pmaddwd(uVar45,0x98e000041b30000);
    iVar18 = (int)((ulonglong)uVar58 >> 0x20);
    iVar55 = (int)(uVar34 ^ 0xffffffffffffffff) + 1;
    iVar60 = (int)((uVar34 ^ 0xffffffffffffffff) >> 0x20) + 1;
    iVar51 = (int)(uVar37 ^ 0xffffffffffffffff) + 1 + iVar18;
    iVar18 = (int)((uVar37 ^ 0xffffffffffffffff) >> 0x20) + 1 + iVar18;
    iVar4 = (int)uVar45 + iVar55 + iVar51;
    iVar30 = (int)((ulonglong)uVar45 >> 0x20) + iVar60 + iVar18;
    iVar51 = (int)uVar5 + iVar60 + iVar51;
    iVar18 = (int)((ulonglong)uVar5 >> 0x20) + iVar55 + iVar18;
    uVar34 = CONCAT44(iVar4 + iVar42 + 0x20000 >> 0x12,iVar30 + iVar26 + 0x20000 >> 0x12) &
             0x3ff000003ff;
    piVar2 = (int *)(param_4 + local_c);
    uVar37 = CONCAT44(iVar18 + iVar8 + 0x20000 >> 0x12,iVar51 + iVar38 + 0x20000 >> 0x12) &
             0x3ff000003ff;
    uVar1 = CONCAT11(*(undefined1 *)(param_6 + (int)uVar34),
                     *(undefined1 *)(param_6 + (int)(uVar34 >> 0x20)));
    local_c = local_c + 4;
    uVar21 = CONCAT44((iVar8 - iVar18) + 0x20000 >> 0x12,(iVar38 - iVar51) + 0x20000 >> 0x12) &
             0x3ff000003ff;
    uVar34 = CONCAT44((iVar42 - iVar4) + 0x20000 >> 0x12,(iVar26 - iVar30) + 0x20000 >> 0x12) &
             0x3ff000003ff;
    local_14 = local_14 + 2;
    *(ulonglong *)(*piVar2 + param_5) =
         CONCAT44(CONCAT22((short)CONCAT31(CONCAT21(uVar1,*(undefined1 *)(param_6 + (int)uVar21)),
                                           *(undefined1 *)(param_6 + (int)(uVar21 >> 0x20))),
                           CONCAT11(*(undefined1 *)(param_6 + (int)(uVar34 >> 0x20)),
                                    *(undefined1 *)(param_6 + (int)uVar34))),
                  CONCAT22(uVar1,CONCAT11(*(undefined1 *)(param_6 + (int)(uVar37 >> 0x20)),
                                          *(undefined1 *)(param_6 + (int)uVar37))));
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  return;
}



/* grim_jpg_idct_8x8_ifast_col @ 10037a8f */

void __cdecl
grim_jpg_idct_8x8_ifast_col(short *param_1,short *param_2,short *param_3,int param_4,int param_5,int param_6)

{
  short sVar1;
  undefined1 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  undefined1 *puVar12;
  short *local_30;
  short *local_2c;
  short *local_28;
  int local_24;
  short local_20;
  
  local_30 = param_1;
  local_2c = param_3;
  local_28 = param_2;
  local_20 = 8;
  do {
    sVar3 = *local_30 * *local_2c + local_30[0x20] * local_2c[0x20];
    sVar1 = *local_30 * *local_2c - local_30[0x20] * local_2c[0x20];
    sVar8 = local_30[0x10] * local_2c[0x10] + local_30[0x30] * local_2c[0x30];
    sVar4 = sVar3 + sVar8;
    sVar3 = sVar3 - sVar8;
    sVar8 = (short)((uint)((short)(local_30[0x10] * local_2c[0x10] - local_30[0x30] * local_2c[0x30]
                                  ) * 0x16a) >> 8) - sVar8;
    sVar5 = sVar1 + sVar8;
    sVar1 = sVar1 - sVar8;
    sVar6 = local_30[8] * local_2c[8] + local_30[0x38] * local_2c[0x38];
    sVar8 = local_30[8] * local_2c[8] - local_30[0x38] * local_2c[0x38];
    sVar9 = local_30[0x28] * local_2c[0x28] + local_30[0x18] * local_2c[0x18];
    sVar10 = local_30[0x28] * local_2c[0x28] - local_30[0x18] * local_2c[0x18];
    sVar7 = sVar6 + sVar9;
    sVar11 = (short)((uint)((short)(sVar10 + sVar8) * 0x1d9) >> 8);
    sVar10 = ((short)((uint)(sVar10 * -0x29d) >> 8) + sVar11) - sVar7;
    sVar6 = (short)((uint)((short)(sVar6 - sVar9) * 0x16a) >> 8) - sVar10;
    sVar8 = ((short)((uint)(sVar8 * 0x115) >> 8) - sVar11) + sVar6;
    *local_28 = sVar7 + sVar4;
    local_28[0x38] = sVar4 - sVar7;
    local_28[8] = sVar10 + sVar5;
    local_28[0x30] = sVar5 - sVar10;
    local_28[0x10] = sVar6 + sVar1;
    local_28[0x28] = sVar1 - sVar6;
    local_28[0x20] = sVar8 + sVar3;
    local_28[0x18] = sVar3 - sVar8;
    local_30 = local_30 + 1;
    local_2c = local_2c + 1;
    local_28 = local_28 + 1;
    local_20 = local_20 + -1;
  } while (local_20 != 0);
  local_24 = 0;
  local_20 = 8;
  local_28 = param_2;
  do {
    puVar12 = (undefined1 *)(*(int *)(param_4 + local_24) + param_5);
    local_24 = local_24 + 4;
    sVar3 = *local_28 + local_28[4];
    sVar1 = *local_28 - local_28[4];
    sVar8 = local_28[2] + local_28[6];
    sVar4 = sVar3 + sVar8;
    sVar3 = sVar3 - sVar8;
    sVar8 = (short)((uint)((short)(local_28[2] - local_28[6]) * 0x16a) >> 8) - sVar8;
    sVar5 = sVar1 + sVar8;
    sVar1 = sVar1 - sVar8;
    sVar6 = local_28[1] + local_28[7];
    sVar8 = local_28[1] - local_28[7];
    sVar9 = local_28[5] + local_28[3];
    sVar10 = local_28[5] - local_28[3];
    sVar7 = sVar6 + sVar9;
    sVar11 = (short)((uint)((short)(sVar10 + sVar8) * 0x1d9) >> 8);
    sVar10 = ((short)((uint)(sVar10 * -0x29d) >> 8) + sVar11) - sVar7;
    sVar6 = (short)((uint)((short)(sVar6 - sVar9) * 0x16a) >> 8) - sVar10;
    sVar8 = ((short)((uint)(sVar8 * 0x115) >> 8) - sVar11) + sVar6;
    uVar2 = *(undefined1 *)(param_6 + ((ushort)((short)(sVar4 - sVar7) >> 5) & 0x3ff));
    *puVar12 = *(undefined1 *)(param_6 + ((ushort)((short)(sVar7 + sVar4) >> 5) & 0x3ff));
    puVar12[7] = uVar2;
    uVar2 = *(undefined1 *)(param_6 + ((ushort)((short)(sVar5 - sVar10) >> 5) & 0x3ff));
    puVar12[1] = *(undefined1 *)(param_6 + ((ushort)((short)(sVar10 + sVar5) >> 5) & 0x3ff));
    puVar12[6] = uVar2;
    uVar2 = *(undefined1 *)(param_6 + ((ushort)((short)(sVar1 - sVar6) >> 5) & 0x3ff));
    puVar12[2] = *(undefined1 *)(param_6 + ((ushort)((short)(sVar6 + sVar1) >> 5) & 0x3ff));
    puVar12[5] = uVar2;
    uVar2 = *(undefined1 *)(param_6 + ((ushort)((short)(sVar3 - sVar8) >> 5) & 0x3ff));
    puVar12[4] = *(undefined1 *)(param_6 + ((ushort)((short)(sVar8 + sVar3) >> 5) & 0x3ff));
    puVar12[3] = uVar2;
    local_28 = local_28 + 8;
    local_20 = local_20 + -1;
  } while (local_20 != 0);
  return;
}



/* grim_jpg_idct_8x8_ifast_row @ 10037dea */

void __cdecl
grim_jpg_idct_8x8_ifast_row(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int *param_4,int param_5,
            int param_6)

{
  undefined8 uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined1 *puVar4;
  short sVar5;
  undefined4 uVar6;
  undefined6 uVar7;
  short sVar9;
  short sVar10;
  ushort uVar11;
  short sVar12;
  undefined8 uVar8;
  short sVar13;
  short sVar16;
  short sVar17;
  short sVar18;
  short sVar19;
  undefined8 uVar14;
  undefined8 uVar15;
  short sVar20;
  undefined4 uVar21;
  short sVar22;
  short sVar23;
  short sVar24;
  short sVar25;
  short sVar26;
  short sVar27;
  short sVar28;
  short sVar29;
  short sVar30;
  undefined4 uVar31;
  undefined8 uVar32;
  short sVar33;
  short sVar34;
  short sVar35;
  short sVar36;
  short sVar37;
  short sVar38;
  short sVar39;
  short sVar41;
  undefined8 uVar40;
  short sVar42;
  short sVar43;
  ushort uVar45;
  undefined8 uVar44;
  
  uVar14 = param_1[0xc];
  uVar40 = param_3[0xc];
  sVar5 = (short)uVar14 * (short)uVar40;
  sVar9 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar10 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar12 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[4];
  uVar40 = param_3[4];
  sVar13 = (short)uVar14 * (short)uVar40;
  sVar16 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar18 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar19 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = *param_1;
  uVar40 = *param_3;
  sVar24 = (short)uVar14 * (short)uVar40;
  sVar25 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar27 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar29 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[8];
  uVar40 = param_3[8];
  sVar33 = (short)uVar14 * (short)uVar40;
  sVar34 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar35 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar36 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar17 = sVar16 - sVar9;
  sVar20 = sVar13 + sVar5;
  sVar16 = sVar16 + sVar9;
  sVar22 = sVar18 + sVar10;
  sVar23 = sVar19 + sVar12;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar17,CONCAT22(sVar17,sVar13 - sVar5)) & 0xffffffff0000ffff,
                   0x16a0000016a);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar19 - sVar12,(uint)(ushort)(sVar18 - sVar10)),
                   0x16a0000016a);
  sVar19 = sVar24 + sVar33;
  sVar26 = sVar25 + sVar34;
  sVar28 = sVar27 + sVar35;
  sVar30 = sVar29 + sVar36;
  sVar24 = sVar24 - sVar33;
  sVar25 = sVar25 - sVar34;
  sVar27 = sVar27 - sVar35;
  sVar29 = sVar29 - sVar36;
  uVar14 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar5 = (short)uVar14 - sVar20;
  sVar9 = (short)((ulonglong)uVar14 >> 0x10) - sVar16;
  sVar10 = (short)((ulonglong)uVar14 >> 0x20) - sVar22;
  sVar12 = (short)((ulonglong)uVar14 >> 0x30) - sVar23;
  param_2[4] = CONCAT26(sVar30 + sVar23,
                        CONCAT24(sVar28 + sVar22,CONCAT22(sVar26 + sVar16,sVar19 + sVar20)));
  param_2[0xc] = CONCAT26(sVar12 + sVar29,
                          CONCAT24(sVar10 + sVar27,CONCAT22(sVar9 + sVar25,sVar5 + sVar24)));
  sVar19 = sVar19 - sVar20;
  sVar26 = sVar26 - sVar16;
  sVar28 = sVar28 - sVar22;
  sVar30 = sVar30 - sVar23;
  *param_2 = CONCAT26(sVar29 - sVar12,
                      CONCAT24(sVar27 - sVar10,CONCAT22(sVar25 - sVar9,sVar24 - sVar5)));
  uVar14 = param_1[10];
  uVar40 = param_3[10];
  sVar18 = (short)uVar14 * (short)uVar40;
  sVar20 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar22 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar23 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[6];
  uVar40 = param_3[6];
  sVar5 = (short)uVar14 * (short)uVar40;
  sVar10 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar13 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar16 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[2];
  uVar40 = param_3[2];
  sVar9 = (short)uVar14 * (short)uVar40;
  sVar12 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar33 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar17 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar34 = sVar18 - sVar5;
  sVar35 = sVar20 - sVar10;
  uVar45 = sVar22 - sVar13;
  sVar36 = sVar23 - sVar16;
  uVar14 = param_1[0xe];
  uVar40 = param_3[0xe];
  sVar24 = (short)uVar14 * (short)uVar40;
  sVar25 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar27 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar29 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar18 = sVar18 + sVar5;
  sVar20 = sVar20 + sVar10;
  sVar22 = sVar22 + sVar13;
  sVar23 = sVar23 + sVar16;
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar35,CONCAT22(sVar35,sVar34)) & 0xffffffff0000ffff,
                   0xfd630000fd63);
  sVar10 = sVar9 + sVar24;
  sVar5 = sVar12 + sVar25;
  sVar13 = sVar33 + sVar27;
  sVar16 = sVar17 + sVar29;
  sVar9 = sVar9 - sVar24;
  sVar12 = sVar12 - sVar25;
  uVar11 = sVar33 - sVar27;
  sVar17 = sVar17 - sVar29;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar36,(uint)uVar45),0xfd630000fd63);
  uVar44 = packssdw(CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar12,CONCAT22(sVar12,sVar9)) & 0xffffffff0000ffff,
                   0x11500000115);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar17,(uint)uVar11),0x11500000115);
  uVar8 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                   CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar35 + sVar12,CONCAT22(sVar35 + sVar12,sVar34 + sVar9)) &
                   0xffffffff0000ffff,0x1d9000001d9);
  sVar25 = sVar10 + sVar18;
  sVar27 = sVar5 + sVar20;
  sVar29 = sVar13 + sVar22;
  sVar33 = sVar16 + sVar23;
  sVar5 = sVar5 - sVar20;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar36 + sVar17,(uint)(ushort)(uVar45 + uVar11)),
                   0x1d9000001d9);
  uVar32 = pmaddwd((ulonglong)CONCAT24(sVar5,CONCAT22(sVar5,sVar10 - sVar18)) & 0xffffffff0000ffff,
                   0x16a0000016a);
  uVar15 = packssdw(CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar16 - sVar23,(uint)(ushort)(sVar13 - sVar22)),
                   0x16a0000016a);
  sVar9 = (short)((ulonglong)uVar15 >> 0x10);
  sVar10 = (short)((ulonglong)uVar15 >> 0x20);
  sVar12 = (short)((ulonglong)uVar15 >> 0x30);
  uVar14 = param_2[4];
  uVar32 = packssdw(CONCAT44((int)((longlong)uVar32 >> 0x28),(int)uVar32 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar13 = ((short)uVar15 + (short)uVar44) - sVar25;
  sVar16 = (sVar9 + (short)((ulonglong)uVar44 >> 0x10)) - sVar27;
  sVar17 = (sVar10 + (short)((ulonglong)uVar44 >> 0x20)) - sVar29;
  sVar18 = (sVar12 + (short)((ulonglong)uVar44 >> 0x30)) - sVar33;
  uVar40 = param_2[0xc];
  sVar20 = (short)uVar32 - sVar13;
  sVar22 = (short)((ulonglong)uVar32 >> 0x10) - sVar16;
  sVar23 = (short)((ulonglong)uVar32 >> 0x20) - sVar17;
  sVar24 = (short)((ulonglong)uVar32 >> 0x30) - sVar18;
  sVar5 = ((short)uVar8 - (short)uVar15) + sVar20;
  sVar9 = ((short)((ulonglong)uVar8 >> 0x10) - sVar9) + sVar22;
  sVar10 = ((short)((ulonglong)uVar8 >> 0x20) - sVar10) + sVar23;
  sVar12 = ((short)((ulonglong)uVar8 >> 0x30) - sVar12) + sVar24;
  param_2[8] = CONCAT26(sVar30 + sVar12,
                        CONCAT24(sVar28 + sVar10,CONCAT22(sVar26 + sVar9,sVar19 + sVar5)));
  sVar34 = (short)((ulonglong)uVar14 >> 0x10);
  sVar35 = (short)((ulonglong)uVar14 >> 0x20);
  sVar36 = (short)((ulonglong)uVar14 >> 0x30);
  param_2[6] = CONCAT26(sVar30 - sVar12,
                        CONCAT24(sVar28 - sVar10,CONCAT22(sVar26 - sVar9,sVar19 - sVar5)));
  uVar8 = *param_2;
  *param_2 = CONCAT26(sVar36 + sVar33,
                      CONCAT24(sVar35 + sVar29,CONCAT22(sVar34 + sVar27,(short)uVar14 + sVar25)));
  sVar5 = (short)((ulonglong)uVar40 >> 0x10);
  sVar9 = (short)((ulonglong)uVar40 >> 0x20);
  sVar10 = (short)((ulonglong)uVar40 >> 0x30);
  param_2[0xe] = CONCAT26(sVar36 - sVar33,
                          CONCAT24(sVar35 - sVar29,CONCAT22(sVar34 - sVar27,(short)uVar14 - sVar25))
                         );
  param_2[2] = CONCAT26(sVar10 + sVar18,
                        CONCAT24(sVar9 + sVar17,CONCAT22(sVar5 + sVar16,(short)uVar40 + sVar13)));
  param_2[0xc] = CONCAT26(sVar10 - sVar18,
                          CONCAT24(sVar9 - sVar17,CONCAT22(sVar5 - sVar16,(short)uVar40 - sVar13)));
  sVar9 = (short)((ulonglong)uVar8 >> 0x10);
  sVar16 = (short)((ulonglong)uVar8 >> 0x20);
  sVar17 = (short)((ulonglong)uVar8 >> 0x30);
  uVar14 = param_1[5];
  uVar40 = param_3[5];
  sVar5 = (short)uVar14 * (short)uVar40;
  sVar12 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar10 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar13 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  param_2[4] = CONCAT26(sVar17 + sVar24,
                        CONCAT24(sVar16 + sVar23,CONCAT22(sVar9 + sVar22,(short)uVar8 + sVar20)));
  param_2[10] = CONCAT26(sVar17 - sVar24,
                         CONCAT24(sVar16 - sVar23,CONCAT22(sVar9 - sVar22,(short)uVar8 - sVar20)));
  uVar14 = param_1[0xd];
  uVar40 = param_3[0xd];
  sVar17 = (short)uVar14 * (short)uVar40;
  sVar22 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar25 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar27 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[1];
  uVar40 = param_3[1];
  sVar24 = (short)uVar14 * (short)uVar40;
  sVar26 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar28 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar30 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[9];
  sVar9 = sVar12 - sVar22;
  uVar40 = param_3[9];
  sVar16 = (short)uVar14 * (short)uVar40;
  sVar18 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar19 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar34 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar20 = sVar5 + sVar17;
  sVar12 = sVar12 + sVar22;
  sVar22 = sVar10 + sVar25;
  sVar23 = sVar13 + sVar27;
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar9,CONCAT22(sVar9,sVar5 - sVar17)) & 0xffffffff0000ffff,
                  0x16a0000016a);
  uVar14 = param_1[0xb];
  uVar15 = pmaddwd((ulonglong)CONCAT24(sVar13 - sVar27,(uint)(ushort)(sVar10 - sVar25)),
                   0x16a0000016a);
  uVar40 = param_3[0xb];
  sVar5 = (short)uVar14 * (short)uVar40;
  sVar10 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar13 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar17 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = packssdw(CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8),
                    CONCAT44((int)((longlong)uVar15 >> 0x28),(int)uVar15 >> 8));
  sVar25 = sVar24 + sVar16;
  sVar27 = sVar26 + sVar18;
  sVar29 = sVar28 + sVar19;
  sVar33 = sVar30 + sVar34;
  sVar24 = sVar24 - sVar16;
  sVar26 = sVar26 - sVar18;
  sVar28 = sVar28 - sVar19;
  sVar30 = sVar30 - sVar34;
  sVar9 = (short)uVar14 - sVar20;
  sVar16 = (short)((ulonglong)uVar14 >> 0x10) - sVar12;
  sVar18 = (short)((ulonglong)uVar14 >> 0x20) - sVar22;
  sVar19 = (short)((ulonglong)uVar14 >> 0x30) - sVar23;
  uVar14 = param_1[7];
  param_2[5] = CONCAT26(sVar33 + sVar23,
                        CONCAT24(sVar29 + sVar22,CONCAT22(sVar27 + sVar12,sVar25 + sVar20)));
  uVar40 = param_3[7];
  sVar34 = (short)uVar14 * (short)uVar40;
  sVar35 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar36 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar42 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar25 = sVar25 - sVar20;
  sVar27 = sVar27 - sVar12;
  sVar29 = sVar29 - sVar22;
  sVar33 = sVar33 - sVar23;
  param_2[0xd] = CONCAT26(sVar30 + sVar19,
                          CONCAT24(sVar28 + sVar18,CONCAT22(sVar26 + sVar16,sVar24 + sVar9)));
  param_2[9] = CONCAT26(sVar30 - sVar19,
                        CONCAT24(sVar28 - sVar18,CONCAT22(sVar26 - sVar16,sVar24 - sVar9)));
  sVar9 = sVar5 + sVar34;
  sVar12 = sVar10 + sVar35;
  sVar16 = sVar13 + sVar36;
  sVar18 = sVar17 + sVar42;
  uVar14 = param_1[0xf];
  sVar5 = sVar5 - sVar34;
  sVar10 = sVar10 - sVar35;
  uVar11 = sVar13 - sVar36;
  sVar17 = sVar17 - sVar42;
  uVar40 = param_3[0xf];
  sVar13 = (short)uVar14 * (short)uVar40;
  sVar19 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar22 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar23 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  uVar14 = param_1[3];
  uVar40 = param_3[3];
  sVar24 = (short)uVar14 * (short)uVar40;
  sVar28 = (short)((ulonglong)uVar14 >> 0x10) * (short)((ulonglong)uVar40 >> 0x10);
  sVar30 = (short)((ulonglong)uVar14 >> 0x20) * (short)((ulonglong)uVar40 >> 0x20);
  sVar37 = (short)((ulonglong)uVar14 >> 0x30) * (short)((ulonglong)uVar40 >> 0x30);
  sVar26 = sVar24 + sVar13;
  sVar20 = sVar28 + sVar19;
  sVar34 = sVar30 + sVar22;
  sVar38 = sVar37 + sVar23;
  sVar24 = sVar24 - sVar13;
  sVar28 = sVar28 - sVar19;
  uVar45 = sVar30 - sVar22;
  sVar37 = sVar37 - sVar23;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar10,CONCAT22(sVar10,sVar5)) & 0xffffffff0000ffff,
                   0xfd630000fd63);
  sVar35 = sVar26 + sVar9;
  sVar36 = sVar20 + sVar12;
  sVar42 = sVar34 + sVar16;
  sVar39 = sVar38 + sVar18;
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar17,(uint)uVar11),0xfd630000fd63);
  sVar20 = sVar20 - sVar12;
  uVar40 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar20,CONCAT22(sVar20,sVar26 - sVar9)) & 0xffffffff0000ffff,
                  0x16a0000016a);
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar38 - sVar18,(uint)(ushort)(sVar34 - sVar16)),
                   0x16a0000016a);
  uVar15 = packssdw(CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar10 + sVar28,CONCAT22(sVar10 + sVar28,sVar5 + sVar24)) &
                   0xffffffff0000ffff,0x1d9000001d9);
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar17 + sVar37,(uint)(ushort)(uVar11 + uVar45)),0x1d9000001d9
                 );
  uVar8 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                   CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8));
  uVar32 = pmaddwd((ulonglong)CONCAT24(sVar28,CONCAT22(sVar28,sVar24)) & 0xffffffff0000ffff,
                   0x11500000115);
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar37,(uint)uVar45),0x11500000115);
  uVar32 = packssdw(CONCAT44((int)((longlong)uVar32 >> 0x28),(int)uVar32 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar14 = param_2[5];
  sVar9 = (short)((ulonglong)uVar8 >> 0x10);
  sVar12 = (short)((ulonglong)uVar8 >> 0x20);
  sVar16 = (short)((ulonglong)uVar8 >> 0x30);
  sVar17 = ((short)uVar8 + (short)uVar40) - sVar35;
  sVar18 = (sVar9 + (short)((ulonglong)uVar40 >> 0x10)) - sVar36;
  sVar20 = (sVar12 + (short)((ulonglong)uVar40 >> 0x20)) - sVar42;
  sVar23 = (sVar16 + (short)((ulonglong)uVar40 >> 0x30)) - sVar39;
  sVar26 = (short)uVar15 - sVar17;
  sVar28 = (short)((ulonglong)uVar15 >> 0x10) - sVar18;
  sVar30 = (short)((ulonglong)uVar15 >> 0x20) - sVar20;
  sVar34 = (short)((ulonglong)uVar15 >> 0x30) - sVar23;
  sVar5 = (short)((ulonglong)uVar14 >> 0x10);
  sVar10 = (short)((ulonglong)uVar14 >> 0x20);
  sVar13 = (short)((ulonglong)uVar14 >> 0x30);
  uVar40 = param_2[0xd];
  sVar37 = ((short)uVar32 - (short)uVar8) + sVar26;
  sVar38 = ((short)((ulonglong)uVar32 >> 0x10) - sVar9) + sVar28;
  sVar41 = ((short)((ulonglong)uVar32 >> 0x20) - sVar12) + sVar30;
  sVar43 = ((short)((ulonglong)uVar32 >> 0x30) - sVar16) + sVar34;
  param_2[1] = CONCAT26(sVar13 + sVar39,
                        CONCAT24(sVar10 + sVar42,CONCAT22(sVar5 + sVar36,(short)uVar14 + sVar35)));
  uVar8 = param_2[9];
  param_2[7] = CONCAT26(sVar33 - sVar43,
                        CONCAT24(sVar29 - sVar41,CONCAT22(sVar27 - sVar38,sVar25 - sVar37)));
  sVar19 = (short)((ulonglong)uVar40 >> 0x10);
  sVar22 = (short)((ulonglong)uVar40 >> 0x20);
  sVar24 = (short)((ulonglong)uVar40 >> 0x30);
  param_2[3] = CONCAT26(sVar24 + sVar23,
                        CONCAT24(sVar22 + sVar20,CONCAT22(sVar19 + sVar18,(short)uVar40 + sVar17)));
  sVar9 = (short)((ulonglong)uVar8 >> 0x10);
  sVar12 = (short)((ulonglong)uVar8 >> 0x20);
  sVar16 = (short)((ulonglong)uVar8 >> 0x30);
  param_2[5] = CONCAT26(sVar16 + sVar34,
                        CONCAT24(sVar12 + sVar30,CONCAT22(sVar9 + sVar28,(short)uVar8 + sVar26)));
  uVar6 = CONCAT22(sVar12 - sVar30,sVar29 + sVar41);
  uVar15 = *param_2;
  uVar32 = param_2[2];
  uVar21 = CONCAT22(sVar10 - sVar42,sVar22 - sVar20);
  param_2[9] = CONCAT44(CONCAT22((short)uVar14 - sVar35,(short)uVar40 - sVar17),
                        CONCAT22((short)uVar8 - sVar26,sVar25 + sVar37));
  param_2[0xb] = CONCAT44(CONCAT22(sVar5 - sVar36,sVar19 - sVar18),
                          CONCAT22(sVar9 - sVar28,sVar27 + sVar38));
  param_2[0xd] = CONCAT44(uVar21,uVar6);
  param_2[0xf] = CONCAT44((int)(CONCAT26(sVar13 - sVar39,CONCAT24(sVar24 - sVar23,uVar21)) >> 0x20),
                          (int)(CONCAT26(sVar16 - sVar34,CONCAT24(sVar33 + sVar43,uVar6)) >> 0x20));
  uVar21 = CONCAT22((short)((ulonglong)uVar32 >> 0x20),(short)((ulonglong)uVar15 >> 0x20));
  uVar14 = param_2[4];
  uVar40 = param_2[6];
  uVar6 = CONCAT22((short)((ulonglong)uVar40 >> 0x20),(short)((ulonglong)uVar14 >> 0x20));
  *param_2 = CONCAT44(CONCAT22((short)uVar40,(short)uVar14),CONCAT22((short)uVar32,(short)uVar15));
  param_2[2] = CONCAT44(CONCAT22((short)((ulonglong)uVar40 >> 0x10),
                                 (short)((ulonglong)uVar14 >> 0x10)),
                        CONCAT22((short)((ulonglong)uVar32 >> 0x10),
                                 (short)((ulonglong)uVar15 >> 0x10)));
  param_2[4] = CONCAT44(uVar6,uVar21);
  param_2[6] = CONCAT44((int)(CONCAT26((short)((ulonglong)uVar40 >> 0x30),
                                       CONCAT24((short)((ulonglong)uVar14 >> 0x30),uVar6)) >> 0x20),
                        (int)(CONCAT26((short)((ulonglong)uVar32 >> 0x30),
                                       CONCAT24((short)((ulonglong)uVar15 >> 0x30),uVar21)) >> 0x20)
                       );
  uVar14 = param_2[1];
  uVar40 = param_2[3];
  uVar8 = param_2[5];
  uVar21 = CONCAT22((short)((ulonglong)uVar40 >> 0x20),(short)((ulonglong)uVar14 >> 0x20));
  uVar15 = param_2[7];
  uVar31 = CONCAT22((short)((ulonglong)uVar15 >> 0x20),(short)((ulonglong)uVar8 >> 0x20));
  uVar32 = param_2[8];
  param_2[8] = CONCAT44(CONCAT22((short)uVar15,(short)uVar8),CONCAT22((short)uVar40,(short)uVar14));
  uVar44 = param_2[10];
  param_2[10] = CONCAT44(CONCAT22((short)((ulonglong)uVar15 >> 0x10),
                                  (short)((ulonglong)uVar8 >> 0x10)),
                         CONCAT22((short)((ulonglong)uVar40 >> 0x10),
                                  (short)((ulonglong)uVar14 >> 0x10)));
  uVar1 = param_2[0xc];
  uVar6 = CONCAT22((short)((ulonglong)uVar44 >> 0x20),(short)((ulonglong)uVar32 >> 0x20));
  uVar2 = param_2[0xe];
  param_2[0xc] = CONCAT44(uVar31,uVar21);
  param_2[0xe] = CONCAT44((int)(CONCAT26((short)((ulonglong)uVar15 >> 0x30),
                                         CONCAT24((short)((ulonglong)uVar8 >> 0x30),uVar31)) >> 0x20
                               ),(int)(CONCAT26((short)((ulonglong)uVar40 >> 0x30),
                                                CONCAT24((short)((ulonglong)uVar14 >> 0x30),uVar21))
                                      >> 0x20));
  uVar21 = CONCAT22((short)((ulonglong)uVar2 >> 0x20),(short)((ulonglong)uVar1 >> 0x20));
  param_2[1] = CONCAT44(CONCAT22((short)uVar2,(short)uVar1),CONCAT22((short)uVar44,(short)uVar32));
  param_2[3] = CONCAT44(CONCAT22((short)((ulonglong)uVar2 >> 0x10),(short)((ulonglong)uVar1 >> 0x10)
                                ),
                        CONCAT22((short)((ulonglong)uVar44 >> 0x10),
                                 (short)((ulonglong)uVar32 >> 0x10)));
  param_2[5] = CONCAT44(uVar21,uVar6);
  param_2[7] = CONCAT44((int)(CONCAT26((short)((ulonglong)uVar2 >> 0x30),
                                       CONCAT24((short)((ulonglong)uVar1 >> 0x30),uVar21)) >> 0x20),
                        (int)(CONCAT26((short)((ulonglong)uVar44 >> 0x30),
                                       CONCAT24((short)((ulonglong)uVar32 >> 0x30),uVar6)) >> 0x20))
  ;
  uVar14 = param_2[0xc];
  uVar40 = param_2[4];
  uVar8 = *param_2;
  uVar15 = param_2[8];
  sVar5 = (short)((ulonglong)uVar14 >> 0x10);
  sVar13 = (short)((ulonglong)uVar40 >> 0x10);
  sVar12 = sVar13 - sVar5;
  sVar9 = (short)((ulonglong)uVar14 >> 0x20);
  sVar16 = (short)((ulonglong)uVar40 >> 0x20);
  sVar17 = (short)((ulonglong)uVar40 >> 0x30);
  sVar10 = (short)((ulonglong)uVar14 >> 0x30);
  sVar18 = (short)uVar40 + (short)uVar14;
  sVar13 = sVar13 + sVar5;
  sVar19 = sVar16 + sVar9;
  sVar20 = sVar17 + sVar10;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar12,CONCAT22(sVar12,(short)uVar40 - (short)uVar14)) &
                   0xffffffff0000ffff,0x16a0000016a);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar17 - sVar10,(uint)(ushort)(sVar16 - sVar9)),0x16a0000016a
                  );
  uVar14 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar22 = (short)uVar8 + (short)uVar15;
  sVar16 = (short)((ulonglong)uVar8 >> 0x10);
  sVar5 = (short)((ulonglong)uVar15 >> 0x10);
  sVar23 = sVar16 + sVar5;
  sVar17 = (short)((ulonglong)uVar8 >> 0x20);
  sVar26 = (short)((ulonglong)uVar8 >> 0x30);
  sVar9 = (short)((ulonglong)uVar15 >> 0x20);
  sVar24 = sVar17 + sVar9;
  sVar10 = (short)((ulonglong)uVar15 >> 0x30);
  sVar25 = sVar26 + sVar10;
  sVar27 = (short)uVar8 - (short)uVar15;
  sVar16 = sVar16 - sVar5;
  sVar17 = sVar17 - sVar9;
  sVar26 = sVar26 - sVar10;
  sVar5 = (short)uVar14 - sVar18;
  sVar9 = (short)((ulonglong)uVar14 >> 0x10) - sVar13;
  sVar10 = (short)((ulonglong)uVar14 >> 0x20) - sVar19;
  sVar12 = (short)((ulonglong)uVar14 >> 0x30) - sVar20;
  param_2[4] = CONCAT26(sVar25 + sVar20,
                        CONCAT24(sVar24 + sVar19,CONCAT22(sVar23 + sVar13,sVar22 + sVar18)));
  param_2[0xc] = CONCAT26(sVar12 + sVar26,
                          CONCAT24(sVar10 + sVar17,CONCAT22(sVar9 + sVar16,sVar5 + sVar27)));
  sVar22 = sVar22 - sVar18;
  sVar23 = sVar23 - sVar13;
  sVar24 = sVar24 - sVar19;
  sVar25 = sVar25 - sVar20;
  *param_2 = CONCAT26(sVar26 - sVar12,
                      CONCAT24(sVar17 - sVar10,CONCAT22(sVar16 - sVar9,sVar27 - sVar5)));
  uVar14 = param_2[10];
  uVar40 = param_2[6];
  uVar8 = param_2[2];
  sVar42 = (short)uVar14 - (short)uVar40;
  sVar5 = (short)((ulonglong)uVar40 >> 0x10);
  sVar12 = (short)((ulonglong)uVar14 >> 0x10);
  sVar37 = sVar12 - sVar5;
  sVar9 = (short)((ulonglong)uVar40 >> 0x20);
  sVar20 = (short)((ulonglong)uVar14 >> 0x20);
  sVar26 = (short)((ulonglong)uVar14 >> 0x30);
  uVar45 = sVar20 - sVar9;
  sVar10 = (short)((ulonglong)uVar40 >> 0x30);
  sVar38 = sVar26 - sVar10;
  uVar15 = param_2[0xe];
  sVar19 = (short)uVar14 + (short)uVar40;
  sVar12 = sVar12 + sVar5;
  sVar20 = sVar20 + sVar9;
  sVar26 = sVar26 + sVar10;
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar37,CONCAT22(sVar37,sVar42)) & 0xffffffff0000ffff,
                   0xfd630000fd63);
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar38,(uint)uVar45),0xfd630000fd63);
  uVar32 = packssdw(CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  sVar28 = (short)uVar8 + (short)uVar15;
  sVar13 = (short)((ulonglong)uVar15 >> 0x10);
  sVar9 = (short)((ulonglong)uVar8 >> 0x10);
  sVar27 = sVar9 + sVar13;
  sVar16 = (short)((ulonglong)uVar15 >> 0x20);
  sVar18 = (short)((ulonglong)uVar8 >> 0x20);
  sVar10 = (short)((ulonglong)uVar8 >> 0x30);
  sVar33 = sVar18 + sVar16;
  sVar17 = (short)((ulonglong)uVar15 >> 0x30);
  sVar35 = sVar10 + sVar17;
  sVar5 = (short)uVar8 - (short)uVar15;
  sVar9 = sVar9 - sVar13;
  uVar11 = sVar18 - sVar16;
  sVar10 = sVar10 - sVar17;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar9,CONCAT22(sVar9,sVar5)) & 0xffffffff0000ffff,
                   0x11500000115);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar10,(uint)uVar11),0x11500000115);
  uVar8 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                   CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar29 = sVar28 + sVar19;
  sVar30 = sVar27 + sVar12;
  sVar34 = sVar33 + sVar20;
  sVar36 = sVar35 + sVar26;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar37 + sVar9,CONCAT22(sVar37 + sVar9,sVar42 + sVar5)) &
                   0xffffffff0000ffff,0x1d9000001d9);
  sVar27 = sVar27 - sVar12;
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar38 + sVar10,(uint)(ushort)(uVar45 + uVar11)),
                   0x1d9000001d9);
  uVar15 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar9 = (short)((ulonglong)uVar15 >> 0x10);
  sVar10 = (short)((ulonglong)uVar15 >> 0x20);
  sVar12 = (short)((ulonglong)uVar15 >> 0x30);
  sVar13 = ((short)uVar15 + (short)uVar32) - sVar29;
  sVar16 = (sVar9 + (short)((ulonglong)uVar32 >> 0x10)) - sVar30;
  sVar17 = (sVar10 + (short)((ulonglong)uVar32 >> 0x20)) - sVar34;
  sVar18 = (sVar12 + (short)((ulonglong)uVar32 >> 0x30)) - sVar36;
  uVar44 = pmaddwd((ulonglong)CONCAT24(sVar27,CONCAT22(sVar27,sVar28 - sVar19)) & 0xffffffff0000ffff
                   ,0x16a0000016a);
  uVar32 = pmaddwd((ulonglong)CONCAT24(sVar35 - sVar26,(uint)(ushort)(sVar33 - sVar20)),
                   0x16a0000016a);
  uVar14 = param_2[0xc];
  uVar40 = param_2[4];
  uVar32 = packssdw(CONCAT44((int)((longlong)uVar44 >> 0x28),(int)uVar44 >> 8),
                    CONCAT44((int)((longlong)uVar32 >> 0x28),(int)uVar32 >> 8));
  sVar19 = (short)uVar32 - sVar13;
  sVar20 = (short)((ulonglong)uVar32 >> 0x10) - sVar16;
  sVar26 = (short)((ulonglong)uVar32 >> 0x20) - sVar17;
  sVar27 = (short)((ulonglong)uVar32 >> 0x30) - sVar18;
  sVar5 = ((short)uVar8 - (short)uVar15) + sVar19;
  sVar9 = ((short)((ulonglong)uVar8 >> 0x10) - sVar9) + sVar20;
  sVar10 = ((short)((ulonglong)uVar8 >> 0x20) - sVar10) + sVar26;
  sVar12 = ((short)((ulonglong)uVar8 >> 0x30) - sVar12) + sVar27;
  param_2[8] = CONCAT26(sVar25 + sVar12,
                        CONCAT24(sVar24 + sVar10,CONCAT22(sVar23 + sVar9,sVar22 + sVar5)));
  sVar28 = (short)((ulonglong)uVar40 >> 0x10);
  sVar33 = (short)((ulonglong)uVar40 >> 0x20);
  sVar35 = (short)((ulonglong)uVar40 >> 0x30);
  param_2[6] = CONCAT26(sVar25 - sVar12,
                        CONCAT24(sVar24 - sVar10,CONCAT22(sVar23 - sVar9,sVar22 - sVar5)));
  uVar8 = *param_2;
  *param_2 = CONCAT26(sVar35 + sVar36,
                      CONCAT24(sVar33 + sVar34,CONCAT22(sVar28 + sVar30,(short)uVar40 + sVar29)));
  sVar5 = (short)((ulonglong)uVar14 >> 0x10);
  sVar9 = (short)((ulonglong)uVar14 >> 0x20);
  sVar10 = (short)((ulonglong)uVar14 >> 0x30);
  param_2[0xe] = CONCAT26(sVar35 - sVar36,
                          CONCAT24(sVar33 - sVar34,CONCAT22(sVar28 - sVar30,(short)uVar40 - sVar29))
                         );
  param_2[2] = CONCAT26(sVar10 + sVar18,
                        CONCAT24(sVar9 + sVar17,CONCAT22(sVar5 + sVar16,(short)uVar14 + sVar13)));
  param_2[0xc] = CONCAT26(sVar10 - sVar18,
                          CONCAT24(sVar9 - sVar17,CONCAT22(sVar5 - sVar16,(short)uVar14 - sVar13)));
  sVar5 = (short)((ulonglong)uVar8 >> 0x10);
  sVar9 = (short)((ulonglong)uVar8 >> 0x20);
  sVar10 = (short)((ulonglong)uVar8 >> 0x30);
  uVar14 = param_2[5];
  param_2[4] = CONCAT26(sVar10 + sVar27,
                        CONCAT24(sVar9 + sVar26,CONCAT22(sVar5 + sVar20,(short)uVar8 + sVar19)));
  param_2[10] = CONCAT26(sVar10 - sVar27,
                         CONCAT24(sVar9 - sVar26,CONCAT22(sVar5 - sVar20,(short)uVar8 - sVar19)));
  uVar40 = param_2[0xd];
  uVar8 = param_2[1];
  sVar9 = (short)((ulonglong)uVar14 >> 0x10);
  sVar13 = (short)((ulonglong)uVar40 >> 0x10);
  sVar5 = sVar9 - sVar13;
  sVar10 = (short)((ulonglong)uVar14 >> 0x20);
  sVar12 = (short)((ulonglong)uVar14 >> 0x30);
  sVar19 = (short)((ulonglong)uVar40 >> 0x20);
  sVar20 = (short)((ulonglong)uVar40 >> 0x30);
  uVar15 = param_2[9];
  sVar16 = (short)uVar14 + (short)uVar40;
  sVar9 = sVar9 + sVar13;
  sVar17 = sVar10 + sVar19;
  sVar18 = sVar12 + sVar20;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar5,CONCAT22(sVar5,(short)uVar14 - (short)uVar40)) &
                   0xffffffff0000ffff,0x16a0000016a);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar12 - sVar20,(uint)(ushort)(sVar10 - sVar19)),
                   0x16a0000016a);
  sVar19 = (short)uVar8 + (short)uVar15;
  sVar22 = (short)((ulonglong)uVar8 >> 0x10);
  sVar5 = (short)((ulonglong)uVar15 >> 0x10);
  sVar20 = sVar22 + sVar5;
  sVar23 = (short)((ulonglong)uVar8 >> 0x20);
  sVar25 = (short)((ulonglong)uVar8 >> 0x30);
  sVar10 = (short)((ulonglong)uVar15 >> 0x20);
  sVar24 = sVar23 + sVar10;
  sVar12 = (short)((ulonglong)uVar15 >> 0x30);
  sVar26 = sVar25 + sVar12;
  sVar27 = (short)uVar8 - (short)uVar15;
  sVar22 = sVar22 - sVar5;
  sVar23 = sVar23 - sVar10;
  sVar25 = sVar25 - sVar12;
  uVar14 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar5 = (short)uVar14 - sVar16;
  sVar10 = (short)((ulonglong)uVar14 >> 0x10) - sVar9;
  sVar12 = (short)((ulonglong)uVar14 >> 0x20) - sVar17;
  sVar13 = (short)((ulonglong)uVar14 >> 0x30) - sVar18;
  param_2[5] = CONCAT26(sVar26 + sVar18,
                        CONCAT24(sVar24 + sVar17,CONCAT22(sVar20 + sVar9,sVar19 + sVar16)));
  param_2[0xd] = CONCAT26(sVar25 + sVar13,
                          CONCAT24(sVar23 + sVar12,CONCAT22(sVar22 + sVar10,sVar27 + sVar5)));
  sVar19 = sVar19 - sVar16;
  sVar20 = sVar20 - sVar9;
  sVar24 = sVar24 - sVar17;
  sVar26 = sVar26 - sVar18;
  param_2[9] = CONCAT26(sVar25 - sVar13,
                        CONCAT24(sVar23 - sVar12,CONCAT22(sVar22 - sVar10,sVar27 - sVar5)));
  uVar14 = param_2[0xb];
  uVar40 = param_2[7];
  uVar8 = param_2[0xf];
  uVar15 = param_2[3];
  sVar5 = (short)uVar14 + (short)uVar40;
  sVar10 = (short)((ulonglong)uVar14 >> 0x10);
  sVar22 = (short)((ulonglong)uVar40 >> 0x10);
  sVar9 = sVar10 + sVar22;
  sVar13 = (short)((ulonglong)uVar14 >> 0x20);
  sVar16 = (short)((ulonglong)uVar14 >> 0x30);
  sVar23 = (short)((ulonglong)uVar40 >> 0x20);
  sVar12 = sVar13 + sVar23;
  sVar25 = (short)((ulonglong)uVar40 >> 0x30);
  sVar17 = sVar16 + sVar25;
  sVar18 = (short)uVar14 - (short)uVar40;
  sVar10 = sVar10 - sVar22;
  uVar11 = sVar13 - sVar23;
  sVar16 = sVar16 - sVar25;
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar10,CONCAT22(sVar10,sVar18)) & 0xffffffff0000ffff,
                   0xfd630000fd63);
  uVar40 = pmaddwd((ulonglong)CONCAT24(sVar16,(uint)uVar11),0xfd630000fd63);
  sVar27 = (short)uVar15 + (short)uVar8;
  sVar13 = (short)((ulonglong)uVar8 >> 0x10);
  sVar28 = (short)((ulonglong)uVar15 >> 0x10);
  sVar22 = sVar28 + sVar13;
  sVar23 = (short)((ulonglong)uVar8 >> 0x20);
  sVar30 = (short)((ulonglong)uVar15 >> 0x20);
  sVar34 = (short)((ulonglong)uVar15 >> 0x30);
  sVar29 = sVar30 + sVar23;
  sVar25 = (short)((ulonglong)uVar8 >> 0x30);
  sVar33 = sVar34 + sVar25;
  sVar38 = (short)uVar15 - (short)uVar8;
  sVar28 = sVar28 - sVar13;
  uVar45 = sVar30 - sVar23;
  sVar34 = sVar34 - sVar25;
  sVar35 = sVar27 + sVar5;
  sVar36 = sVar22 + sVar9;
  sVar42 = sVar29 + sVar12;
  sVar37 = sVar33 + sVar17;
  uVar40 = packssdw(CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8),
                    CONCAT44((int)((longlong)uVar40 >> 0x28),(int)uVar40 >> 8));
  sVar22 = sVar22 - sVar9;
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar22,CONCAT22(sVar22,sVar27 - sVar5)) & 0xffffffff0000ffff,
                  0x16a0000016a);
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar33 - sVar17,(uint)(ushort)(sVar29 - sVar12)),
                   0x16a0000016a);
  uVar32 = packssdw(CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar10 + sVar28,CONCAT22(sVar10 + sVar28,sVar18 + sVar38)) &
                  0xffffffff0000ffff,0x1d9000001d9);
  uVar14 = pmaddwd((ulonglong)CONCAT24(sVar16 + sVar34,(uint)(ushort)(uVar11 + uVar45)),
                   0x1d9000001d9);
  uVar15 = packssdw(CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8),
                    CONCAT44((int)((longlong)uVar14 >> 0x28),(int)uVar14 >> 8));
  uVar44 = pmaddwd((ulonglong)CONCAT24(sVar28,CONCAT22(sVar28,sVar38)) & 0xffffffff0000ffff,
                   0x11500000115);
  uVar8 = pmaddwd((ulonglong)CONCAT24(sVar34,(uint)uVar45),0x11500000115);
  uVar14 = param_2[5];
  uVar8 = packssdw(CONCAT44((int)((longlong)uVar44 >> 0x28),(int)uVar44 >> 8),
                   CONCAT44((int)((longlong)uVar8 >> 0x28),(int)uVar8 >> 8));
  sVar9 = (short)((ulonglong)uVar15 >> 0x10);
  sVar12 = (short)((ulonglong)uVar15 >> 0x20);
  sVar16 = (short)((ulonglong)uVar15 >> 0x30);
  sVar17 = ((short)uVar15 + (short)uVar40) - sVar35;
  sVar18 = (sVar9 + (short)((ulonglong)uVar40 >> 0x10)) - sVar36;
  sVar23 = (sVar12 + (short)((ulonglong)uVar40 >> 0x20)) - sVar42;
  sVar27 = (sVar16 + (short)((ulonglong)uVar40 >> 0x30)) - sVar37;
  sVar29 = (short)uVar32 - sVar17;
  sVar30 = (short)((ulonglong)uVar32 >> 0x10) - sVar18;
  sVar33 = (short)((ulonglong)uVar32 >> 0x20) - sVar23;
  sVar34 = (short)((ulonglong)uVar32 >> 0x30) - sVar27;
  sVar5 = (short)((ulonglong)uVar14 >> 0x10);
  sVar10 = (short)((ulonglong)uVar14 >> 0x20);
  sVar13 = (short)((ulonglong)uVar14 >> 0x30);
  uVar40 = param_2[0xd];
  sVar38 = ((short)uVar8 - (short)uVar15) + sVar29;
  sVar39 = ((short)((ulonglong)uVar8 >> 0x10) - sVar9) + sVar30;
  sVar41 = ((short)((ulonglong)uVar8 >> 0x20) - sVar12) + sVar33;
  sVar43 = ((short)((ulonglong)uVar8 >> 0x30) - sVar16) + sVar34;
  param_2[1] = CONCAT26(sVar13 + sVar37,
                        CONCAT24(sVar10 + sVar42,CONCAT22(sVar5 + sVar36,(short)uVar14 + sVar35)));
  uVar8 = param_2[9];
  param_2[7] = CONCAT26(sVar26 - sVar43,
                        CONCAT24(sVar24 - sVar41,CONCAT22(sVar20 - sVar39,sVar19 - sVar38)));
  sVar22 = (short)((ulonglong)uVar40 >> 0x10);
  sVar25 = (short)((ulonglong)uVar40 >> 0x20);
  sVar28 = (short)((ulonglong)uVar40 >> 0x30);
  param_2[3] = CONCAT26(sVar28 + sVar27,
                        CONCAT24(sVar25 + sVar23,CONCAT22(sVar22 + sVar18,(short)uVar40 + sVar17)));
  sVar9 = (short)((ulonglong)uVar8 >> 0x10);
  sVar12 = (short)((ulonglong)uVar8 >> 0x20);
  sVar16 = (short)((ulonglong)uVar8 >> 0x30);
  param_2[5] = CONCAT26(sVar16 + sVar34,
                        CONCAT24(sVar12 + sVar33,CONCAT22(sVar9 + sVar30,(short)uVar8 + sVar29)));
  iVar3 = param_4[4] + param_5;
  uVar15 = *param_2;
  uVar32 = param_2[2];
  uVar11 = (ushort)(sVar19 + sVar38) >> 5;
  uVar7 = CONCAT24((ushort)((short)uVar40 - sVar17) >> 5,
                   CONCAT22((ushort)((short)uVar8 - sVar29) >> 5,uVar11));
  uVar45 = (ushort)((short)uVar14 - sVar35) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[5] + param_5;
  uVar11 = (ushort)(sVar20 + sVar39) >> 5;
  uVar7 = CONCAT24((ushort)(sVar22 - sVar18) >> 5,CONCAT22((ushort)(sVar9 - sVar30) >> 5,uVar11));
  uVar45 = (ushort)(sVar5 - sVar36) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[6] + param_5;
  uVar11 = (ushort)(sVar24 + sVar41) >> 5;
  uVar7 = CONCAT24((ushort)(sVar25 - sVar23) >> 5,CONCAT22((ushort)(sVar12 - sVar33) >> 5,uVar11));
  uVar45 = (ushort)(sVar10 - sVar42) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[7] + param_5;
  uVar11 = (ushort)(sVar26 + sVar43) >> 5;
  uVar7 = CONCAT24((ushort)(sVar28 - sVar27) >> 5,CONCAT22((ushort)(sVar16 - sVar34) >> 5,uVar11));
  uVar45 = (ushort)(sVar13 - sVar37) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(*param_4 + param_5);
  uVar14 = param_2[6];
  uVar40 = param_2[4];
  uVar11 = (ushort)uVar15 >> 5;
  uVar7 = CONCAT24((ushort)uVar40 >> 5,CONCAT22((ushort)uVar32 >> 5,uVar11));
  uVar45 = (ushort)uVar14 >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[1] + param_5);
  uVar11 = (ushort)((ulonglong)uVar15 >> 0x10) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar40 >> 0x10) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar32 >> 0x10) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar14 >> 0x10) >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[2] + param_5);
  uVar11 = (ushort)((ulonglong)uVar15 >> 0x20) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar40 >> 0x20) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar32 >> 0x20) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar14 >> 0x20) >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[3] + param_5);
  uVar11 = (ushort)((ulonglong)uVar15 >> 0x35);
  uVar7 = CONCAT24((ushort)((ulonglong)uVar40 >> 0x35),
                   CONCAT22((ushort)((ulonglong)uVar32 >> 0x35),uVar11));
  uVar45 = (ushort)((ulonglong)uVar14 >> 0x35);
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[4] + param_5);
  uVar14 = param_2[1];
  uVar40 = param_2[3];
  uVar8 = param_2[5];
  uVar15 = param_2[7];
  uVar32 = param_2[8];
  uVar11 = (ushort)uVar14 >> 5;
  uVar7 = CONCAT24((ushort)uVar8 >> 5,CONCAT22((ushort)uVar40 >> 5,uVar11));
  uVar45 = (ushort)uVar15 >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[5] + param_5);
  uVar44 = param_2[10];
  uVar11 = (ushort)((ulonglong)uVar14 >> 0x10) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar8 >> 0x10) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar40 >> 0x10) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar15 >> 0x10) >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[6] + param_5);
  uVar1 = param_2[0xc];
  uVar2 = param_2[0xe];
  uVar11 = (ushort)((ulonglong)uVar14 >> 0x20) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar8 >> 0x20) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar40 >> 0x20) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar15 >> 0x20) >> 5;
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  puVar4 = (undefined1 *)(param_4[7] + param_5);
  uVar11 = (ushort)((ulonglong)uVar14 >> 0x35);
  uVar7 = CONCAT24((ushort)((ulonglong)uVar8 >> 0x35),
                   CONCAT22((ushort)((ulonglong)uVar40 >> 0x35),uVar11));
  uVar45 = (ushort)((ulonglong)uVar15 >> 0x35);
  *puVar4 = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  puVar4[1] = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  puVar4[2] = *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  puVar4[3] = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = *param_4 + param_5;
  uVar11 = (ushort)uVar32 >> 5;
  uVar7 = CONCAT24((ushort)uVar1 >> 5,CONCAT22((ushort)uVar44 >> 5,uVar11));
  uVar45 = (ushort)uVar2 >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[1] + param_5;
  uVar11 = (ushort)((ulonglong)uVar32 >> 0x10) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar1 >> 0x10) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar44 >> 0x10) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar2 >> 0x10) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[2] + param_5;
  uVar11 = (ushort)((ulonglong)uVar32 >> 0x20) >> 5;
  uVar7 = CONCAT24((ushort)((ulonglong)uVar1 >> 0x20) >> 5,
                   CONCAT22((ushort)((ulonglong)uVar44 >> 0x20) >> 5,uVar11));
  uVar45 = (ushort)((ulonglong)uVar2 >> 0x20) >> 5;
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  iVar3 = param_4[3] + param_5;
  uVar11 = (ushort)((ulonglong)uVar32 >> 0x35);
  uVar7 = CONCAT24((ushort)((ulonglong)uVar1 >> 0x35),
                   CONCAT22((ushort)((ulonglong)uVar44 >> 0x35),uVar11));
  uVar45 = (ushort)((ulonglong)uVar2 >> 0x35);
  *(undefined1 *)(iVar3 + 4) = *(undefined1 *)(param_6 + (uVar11 & 0x3ff));
  *(undefined1 *)(iVar3 + 5) = *(undefined1 *)(param_6 + ((uint)((uint6)uVar7 >> 0x10) & 0x3ff));
  *(undefined1 *)(iVar3 + 6) =
       *(undefined1 *)(param_6 + ((uint)(CONCAT26(uVar45,uVar7) >> 0x20) & 0x3ff));
  *(undefined1 *)(iVar3 + 7) = *(undefined1 *)(param_6 + (uVar45 & 0x3ff));
  return;
}



/* grim_jpg_read_dht @ 1003c950 */

uint __cdecl grim_jpg_read_dht(int *param_1)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  int *piVar11;
  undefined4 *puVar12;
  int iStack_128;
  int iStack_120;
  byte abStack_118 [20];
  uint uStack_104;
  byte abStack_100 [256];
  
  puVar3 = (undefined4 *)param_1[5];
  puVar7 = (undefined1 *)*puVar3;
  iStack_128 = puVar3[1];
  if (iStack_128 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003cc8c;
    iStack_128 = puVar3[1];
    puVar7 = (undefined1 *)*puVar3;
  }
  uVar1 = *puVar7;
  iStack_128 = iStack_128 + -1;
  puVar7 = puVar7 + 1;
  if (iStack_128 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') {
LAB_1003cc8c:
      return uVar4 & 0xffffff00;
    }
    iStack_128 = puVar3[1];
    puVar7 = (undefined1 *)*puVar3;
  }
  iStack_128 = iStack_128 + -1;
  iVar5 = CONCAT11(uVar1,*puVar7) - 2;
  pbVar8 = puVar7 + 1;
  do {
    if (iVar5 < 1) {
      puVar3[1] = iStack_128;
      *puVar3 = pbVar8;
      return CONCAT31((int3)((uint)iVar5 >> 8),1);
    }
    if (iStack_128 == 0) {
      uVar4 = (*(code *)puVar3[3])(param_1);
      if ((char)uVar4 == '\0') goto LAB_1003cc8c;
      iStack_128 = puVar3[1];
      pbVar8 = (byte *)*puVar3;
    }
    uStack_104 = (uint)*pbVar8;
    *(undefined4 *)(*param_1 + 0x14) = 0x4f;
    iStack_128 = iStack_128 + -1;
    pbVar8 = pbVar8 + 1;
    *(uint *)(*param_1 + 0x18) = uStack_104;
    (**(code **)(*param_1 + 4))(param_1,1);
    abStack_118[0] = 0;
    iStack_120 = 0;
    iVar9 = 1;
    do {
      if (iStack_128 == 0) {
        uVar4 = (*(code *)puVar3[3])(param_1);
        if ((char)uVar4 == '\0') goto LAB_1003cc8c;
        iStack_128 = puVar3[1];
        pbVar8 = (byte *)*puVar3;
      }
      bVar2 = *pbVar8;
      abStack_118[iVar9] = bVar2;
      iStack_128 = iStack_128 + -1;
      pbVar8 = pbVar8 + 1;
      iVar6 = iStack_120 + (uint)bVar2;
      iVar9 = iVar9 + 1;
      iStack_120 = iVar6;
    } while (iVar9 < 0x11);
    iVar9 = *param_1;
    *(uint *)(iVar9 + 0x18) =
         CONCAT12(abStack_118[3],CONCAT11(abStack_118[2],abStack_118[1])) & 0xff;
    *(uint *)(iVar9 + 0x1c) =
         CONCAT12(abStack_118[4],CONCAT11(abStack_118[3],abStack_118[2])) & 0xff;
    *(uint *)(iVar9 + 0x20) =
         CONCAT12(abStack_118[5],CONCAT11(abStack_118[4],abStack_118[3])) & 0xff;
    *(uint *)(iVar9 + 0x24) =
         CONCAT12(abStack_118[6],CONCAT11(abStack_118[5],abStack_118[4])) & 0xff;
    *(uint *)(iVar9 + 0x28) =
         CONCAT12(abStack_118[7],CONCAT11(abStack_118[6],abStack_118[5])) & 0xff;
    *(uint *)(iVar9 + 0x2c) =
         CONCAT12(abStack_118[8],CONCAT11(abStack_118[7],abStack_118[6])) & 0xff;
    *(uint *)(iVar9 + 0x30) =
         CONCAT12(abStack_118[9],CONCAT11(abStack_118[8],abStack_118[7])) & 0xff;
    *(uint *)(iVar9 + 0x34) =
         CONCAT12(abStack_118[10],CONCAT11(abStack_118[9],abStack_118[8])) & 0xff;
    *(undefined4 *)(*param_1 + 0x14) = 0x55;
    (**(code **)(*param_1 + 4))(param_1,2);
    iVar9 = *param_1;
    *(uint *)(iVar9 + 0x18) =
         CONCAT12(abStack_118[0xb],CONCAT11(abStack_118[10],abStack_118[9])) & 0xff;
    *(uint *)(iVar9 + 0x1c) =
         CONCAT12(abStack_118[0xc],CONCAT11(abStack_118[0xb],abStack_118[10])) & 0xff;
    *(uint *)(iVar9 + 0x20) =
         CONCAT12(abStack_118[0xd],CONCAT11(abStack_118[0xc],abStack_118[0xb])) & 0xff;
    *(uint *)(iVar9 + 0x24) =
         CONCAT12(abStack_118[0xe],CONCAT11(abStack_118[0xd],abStack_118[0xc])) & 0xff;
    *(uint *)(iVar9 + 0x28) =
         CONCAT12(abStack_118[0xf],CONCAT11(abStack_118[0xe],abStack_118[0xd])) & 0xff;
    *(uint *)(iVar9 + 0x2c) =
         CONCAT12(abStack_118[0x10],CONCAT11(abStack_118[0xf],abStack_118[0xe])) & 0xff;
    *(uint *)(iVar9 + 0x30) = CONCAT11(abStack_118[0x10],abStack_118[0xf]) & 0xff;
    *(uint *)(iVar9 + 0x34) = (uint)abStack_118[0x10];
    *(undefined4 *)(*param_1 + 0x14) = 0x55;
    (**(code **)(*param_1 + 4))(param_1,2);
    if ((0x100 < iVar6) || (iVar5 + -0x11 < iVar6)) {
      *(undefined4 *)(*param_1 + 0x14) = 0x1c;
      (**(code **)*param_1)(param_1);
    }
    iStack_120 = 0;
    if (0 < iVar6) {
      do {
        if (iStack_128 == 0) {
          uVar4 = (*(code *)puVar3[3])(param_1);
          if ((char)uVar4 == '\0') goto LAB_1003cc8c;
          iStack_128 = puVar3[1];
          pbVar8 = (byte *)*puVar3;
        }
        bVar2 = *pbVar8;
        iStack_128 = iStack_128 + -1;
        pbVar8 = pbVar8 + 1;
        abStack_100[iStack_120] = bVar2;
        iStack_120 = iStack_120 + 1;
      } while (iStack_120 < iVar6);
    }
    iVar5 = (iVar5 + -0x11) - iVar6;
    if ((uStack_104 & 0x10) == 0) {
      iVar9 = uStack_104 + 0x28;
      uVar4 = uStack_104;
    }
    else {
      iVar9 = uStack_104 + 0x1c;
      uVar4 = uStack_104 - 0x10;
    }
    piVar11 = param_1 + iVar9;
    if (((int)uVar4 < 0) || (3 < (int)uVar4)) {
      *(undefined4 *)(*param_1 + 0x14) = 0x1d;
      *(uint *)(*param_1 + 0x18) = uVar4;
      (**(code **)*param_1)(param_1);
    }
    if (*piVar11 == 0) {
      iVar9 = grim_jpg_marker_get_length((int)param_1);
      *piVar11 = iVar9;
    }
    puVar12 = (undefined4 *)*piVar11;
    *puVar12 = CONCAT13(abStack_118[3],
                        CONCAT12(abStack_118[2],CONCAT11(abStack_118[1],abStack_118[0])));
    puVar12[1] = CONCAT13(abStack_118[7],
                          CONCAT12(abStack_118[6],CONCAT11(abStack_118[5],abStack_118[4])));
    puVar12[2] = CONCAT13(abStack_118[0xb],
                          CONCAT12(abStack_118[10],CONCAT11(abStack_118[9],abStack_118[8])));
    puVar12[3] = CONCAT13(abStack_118[0xf],
                          CONCAT12(abStack_118[0xe],CONCAT11(abStack_118[0xd],abStack_118[0xc])));
    *(byte *)(puVar12 + 4) = abStack_118[0x10];
    pbVar10 = abStack_100;
    puVar12 = (undefined4 *)(*piVar11 + 0x11);
    for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar12 = *(undefined4 *)pbVar10;
      pbVar10 = pbVar10 + 4;
      puVar12 = puVar12 + 1;
    }
  } while( true );
}



/* grim_jpg_read_dqt @ 1003cca0 */

uint __cdecl grim_jpg_read_dqt(int *param_1)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined1 *puVar10;
  byte *pbVar11;
  int iVar12;
  ushort *puVar13;
  int *piStack_c;
  
  puVar3 = (undefined4 *)param_1[5];
  iVar12 = puVar3[1];
  puVar10 = (undefined1 *)*puVar3;
  if (iVar12 == 0) {
    uVar7 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar7 == '\0') goto LAB_1003cf06;
    puVar10 = (undefined1 *)*puVar3;
    iVar12 = puVar3[1];
  }
  uVar1 = *puVar10;
  iVar12 = iVar12 + -1;
  puVar10 = puVar10 + 1;
  if (iVar12 == 0) {
    uVar7 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar7 == '\0') {
LAB_1003cf06:
      return uVar7 & 0xffffff00;
    }
    puVar10 = (undefined1 *)*puVar3;
    iVar12 = puVar3[1];
  }
  iVar12 = iVar12 + -1;
  pbVar11 = puVar10 + 1;
  iVar9 = CONCAT11(uVar1,*puVar10) - 2;
  do {
    iVar5 = iVar9;
    if (iVar5 < 1) {
      *puVar3 = pbVar11;
      puVar3[1] = iVar12;
      return CONCAT31((int3)((uint)iVar5 >> 8),1);
    }
    if (iVar12 == 0) {
      uVar7 = (*(code *)puVar3[3])(param_1);
      if ((char)uVar7 == '\0') goto LAB_1003cf06;
      pbVar11 = (byte *)*puVar3;
      iVar12 = puVar3[1];
    }
    bVar2 = *pbVar11;
    *(undefined4 *)(*param_1 + 0x14) = 0x50;
    iVar12 = iVar12 + -1;
    pbVar11 = pbVar11 + 1;
    uVar7 = bVar2 & 0xf;
    *(uint *)(*param_1 + 0x18) = uVar7;
    iVar8 = (int)(uint)bVar2 >> 4;
    *(int *)(*param_1 + 0x1c) = iVar8;
    (**(code **)(*param_1 + 4))(param_1,1);
    if (3 < uVar7) {
      *(undefined4 *)(*param_1 + 0x14) = 0x1e;
      *(uint *)(*param_1 + 0x18) = uVar7;
      (**(code **)*param_1)(param_1);
    }
    if (param_1[uVar7 + 0x24] == 0) {
      iVar9 = grim_jpg_marker_skip((int)param_1);
      param_1[uVar7 + 0x24] = iVar9;
    }
    iVar9 = param_1[uVar7 + 0x24];
    piStack_c = (int *)&grim_jpg_zigzag_order;
    do {
      if (iVar8 == 0) {
        if (iVar12 == 0) {
          uVar7 = (*(code *)puVar3[3])(param_1);
          if ((char)uVar7 == '\0') goto LAB_1003cf06;
          pbVar11 = (byte *)*puVar3;
          iVar12 = puVar3[1];
        }
        uVar6 = (ushort)*pbVar11;
      }
      else {
        if (iVar12 == 0) {
          uVar7 = (*(code *)puVar3[3])(param_1);
          if ((char)uVar7 == '\0') goto LAB_1003cf06;
          pbVar11 = (byte *)*puVar3;
          iVar12 = puVar3[1];
        }
        bVar2 = *pbVar11;
        iVar12 = iVar12 + -1;
        pbVar11 = pbVar11 + 1;
        if (iVar12 == 0) {
          uVar7 = (*(code *)puVar3[3])(param_1);
          if ((char)uVar7 == '\0') goto LAB_1003cf06;
          pbVar11 = (byte *)*puVar3;
          iVar12 = puVar3[1];
        }
        uVar6 = (ushort)bVar2 * 0x100 + (ushort)*pbVar11;
      }
      iVar12 = iVar12 + -1;
      pbVar11 = pbVar11 + 1;
      iVar4 = *piStack_c;
      piStack_c = piStack_c + 1;
      *(ushort *)(iVar9 + iVar4 * 2) = uVar6;
    } while ((int)piStack_c < 0x10050650);
    if (1 < *(int *)(*param_1 + 0x68)) {
      puVar13 = (ushort *)(iVar9 + 4);
      piStack_c = (int *)0x8;
      do {
        iVar9 = *param_1;
        *(uint *)(iVar9 + 0x18) = (uint)puVar13[-2];
        *(uint *)(iVar9 + 0x1c) = (uint)puVar13[-1];
        *(uint *)(iVar9 + 0x20) = (uint)*puVar13;
        *(uint *)(iVar9 + 0x24) = (uint)puVar13[1];
        *(uint *)(iVar9 + 0x28) = (uint)puVar13[2];
        *(uint *)(iVar9 + 0x2c) = (uint)puVar13[3];
        *(uint *)(iVar9 + 0x30) = (uint)puVar13[4];
        *(uint *)(iVar9 + 0x34) = (uint)puVar13[5];
        *(undefined4 *)(*param_1 + 0x14) = 0x5c;
        (**(code **)(*param_1 + 4))(param_1,2);
        puVar13 = puVar13 + 8;
        piStack_c = (int *)((int)piStack_c + -1);
      } while (piStack_c != (int *)0x0);
    }
    iVar9 = iVar5 + -0x41;
    if (iVar8 != 0) {
      iVar9 = iVar5 + -0x81;
    }
  } while( true );
}



/* grim_jpg_read_dri @ 1003cf10 */

undefined4 __cdecl grim_jpg_read_dri(int *param_1)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  byte *pbVar8;
  int iVar9;
  
  puVar3 = (undefined4 *)param_1[5];
  puVar7 = (undefined1 *)*puVar3;
  iVar9 = puVar3[1];
  if (iVar9 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003cff6;
    puVar7 = (undefined1 *)*puVar3;
    iVar9 = puVar3[1];
  }
  uVar1 = *puVar7;
  iVar9 = iVar9 + -1;
  puVar7 = puVar7 + 1;
  if (iVar9 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003cff6;
    puVar7 = (undefined1 *)*puVar3;
    iVar9 = puVar3[1];
  }
  iVar9 = iVar9 + -1;
  pbVar8 = puVar7 + 1;
  if (CONCAT11(uVar1,*puVar7) != 4) {
    *(undefined4 *)(*param_1 + 0x14) = 9;
    (**(code **)*param_1)(param_1);
  }
  if (iVar9 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003cff6;
    pbVar8 = (byte *)*puVar3;
    iVar9 = puVar3[1];
  }
  bVar2 = *pbVar8;
  iVar9 = iVar9 + -1;
  pbVar8 = pbVar8 + 1;
  if (iVar9 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') {
LAB_1003cff6:
      return uVar4 & 0xffffff00;
    }
    pbVar8 = (byte *)*puVar3;
    iVar9 = puVar3[1];
  }
  iVar5 = (uint)bVar2 * 0x100 + (uint)*pbVar8;
  *(undefined4 *)(*param_1 + 0x14) = 0x51;
  *(int *)(*param_1 + 0x18) = iVar5;
  uVar6 = (**(code **)(*param_1 + 4))(param_1,1);
  param_1[0x3f] = iVar5;
  puVar3[1] = iVar9 + -1;
  *puVar3 = pbVar8 + 1;
  return CONCAT31((int3)((uint)uVar6 >> 8),1);
}



/* grim_jpg_mem_pool_init @ 1003d0d0 */

/* [binja] char* __fastcall sub_1003d0d0(int32_t arg1) */

char * __cdecl grim_jpg_mem_pool_init(int arg1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char *_Src;
  char *pcVar4;
  int iVar5;
  int local_4;
  
  iVar1 = arg1;
  *(undefined4 *)(arg1 + 4) = 0;
  local_4 = grim_jpg_data_src_check();
  puVar2 = operator_new(0x50);
  if (puVar2 == (undefined4 *)0x0) {
    iVar5 = iVar1;
    grim_noop();
    *(undefined4 *)(*(int *)iVar1 + 0x14) = 0x35;
    *(undefined4 *)(*(int *)iVar1 + 0x18) = 0;
    (*(code *)**(undefined4 **)iVar1)(iVar1,iVar5);
  }
  *puVar2 = grim_jpg_mem_pool_alloc;
  puVar2[1] = grim_jpg_mem_pool_free;
  puVar2[2] = grim_jpg_mem_pool_alloc_zeroed;
  puVar2[3] = grim_jpg_mem_pool_realloc;
  puVar2[4] = grim_jpg_mem_pool_alloc_small;
  puVar2[5] = grim_jpg_mem_pool_alloc_array;
  puVar2[6] = &LAB_1003d660;
  puVar2[7] = &LAB_1003d7e0;
  puVar2[8] = &LAB_1003d9d0;
  puVar2[9] = grim_jpg_mem_pool_destroy;
  puVar2[10] = &LAB_1003dcc0;
  puVar2[0xb] = local_4;
  puVar3 = puVar2 + 0xf;
  iVar5 = 2;
  do {
    puVar3[-2] = 0;
    *puVar3 = 0;
    puVar3 = puVar3 + -1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  puVar2[0x10] = 0;
  puVar2[0x11] = 0;
  puVar2[0x12] = 0x50;
  *(undefined4 **)(iVar1 + 4) = puVar2;
  _Src = getenv(s_JPEGMEM_10058204);
  pcVar4 = (char *)0x0;
  if (_Src != (char *)0x0) {
    arg1 = CONCAT31(arg1._1_3_,0x78);
    pcVar4 = (char *)sscanf(_Src,s__ld_c_100581fc,&local_4,&arg1);
    if (0 < (int)pcVar4) {
      if (((char)arg1 == 'm') || ((char)arg1 == 'M')) {
        puVar2[0xb] = (char *)(local_4 * 1000000);
        return (char *)(local_4 * 1000000);
      }
      pcVar4 = (char *)(local_4 * 1000);
      puVar2[0xb] = pcVar4;
    }
  }
  return pcVar4;
}



/* grim_jpg_mem_pool_alloc @ 1003d210 */

int __cdecl grim_jpg_mem_pool_alloc(int *param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  
  iVar1 = param_1[1];
  if (0xffe0 < param_3) {
    *(undefined4 *)(*param_1 + 0x14) = 0x35;
    *(undefined4 *)(*param_1 + 0x18) = 1;
    (**(code **)*param_1)(param_1);
  }
  if ((param_3 & 7) != 0) {
    param_3 = param_3 + (8 - (param_3 & 7));
  }
  if ((param_2 < 0) || (1 < param_2)) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  puVar3 = *(undefined4 **)(iVar1 + 0x30 + param_2 * 4);
  puVar2 = (undefined4 *)0x0;
  do {
    puVar4 = puVar3;
    if (puVar4 == (undefined4 *)0x0) {
LAB_1003d2a1:
      iVar6 = param_3 + 0x10;
      if (puVar2 == (undefined4 *)0x0) {
        uVar5 = *(uint *)(&DAT_10050540 + param_2 * 4);
      }
      else {
        uVar5 = *(uint *)(&DAT_10050548 + param_2 * 4);
      }
      if (0xfff0U - iVar6 < uVar5) {
        uVar5 = 0xfff0U - iVar6;
      }
      puVar4 = operator_new(uVar5 + iVar6);
      while (puVar4 == (undefined4 *)0x0) {
        uVar5 = uVar5 >> 1;
        if (uVar5 < 0x32) {
          *(undefined4 *)(*param_1 + 0x14) = 0x35;
          *(undefined4 *)(*param_1 + 0x18) = 2;
          (**(code **)*param_1)(param_1);
        }
        puVar4 = operator_new(uVar5 + iVar6);
      }
      *(uint *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) + uVar5 + iVar6;
      *puVar4 = 0;
      puVar4[1] = 0;
      puVar4[2] = uVar5 + param_3;
      if (puVar2 == (undefined4 *)0x0) {
        *(undefined4 **)(iVar1 + 0x30 + param_2 * 4) = puVar4;
      }
      else {
        *puVar2 = puVar4;
      }
LAB_1003d340:
      iVar1 = puVar4[1];
      puVar4[1] = iVar1 + param_3;
      puVar4[2] = puVar4[2] - param_3;
      return iVar1 + 0x10 + (int)puVar4;
    }
    if (param_3 <= (uint)puVar4[2]) {
      if (puVar4 != (undefined4 *)0x0) goto LAB_1003d340;
      goto LAB_1003d2a1;
    }
    puVar3 = (undefined4 *)*puVar4;
    puVar2 = puVar4;
  } while( true );
}



/* grim_jpg_mem_pool_free @ 1003d360 */

undefined4 * __cdecl grim_jpg_mem_pool_free(int *param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = param_1[1];
  if (0xffe0 < param_3) {
    *(undefined4 *)(*param_1 + 0x14) = 0x35;
    *(undefined4 *)(*param_1 + 0x18) = 3;
    (**(code **)*param_1)(param_1);
  }
  if ((param_3 & 7) != 0) {
    param_3 = param_3 + (8 - (param_3 & 7));
  }
  if ((param_2 < 0) || (1 < param_2)) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  puVar3 = operator_new(param_3 + 0x10);
  if (puVar3 == (undefined4 *)0x0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x35;
    *(undefined4 *)(*param_1 + 0x18) = 4;
    (**(code **)*param_1)(param_1);
  }
  *(uint *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) + param_3 + 0x10;
  uVar2 = *(undefined4 *)(iVar1 + 0x38 + param_2 * 4);
  puVar3[1] = param_3;
  *puVar3 = uVar2;
  puVar3[2] = 0;
  *(undefined4 **)(iVar1 + 0x38 + param_2 * 4) = puVar3;
  return puVar3 + 4;
}



/* grim_jpg_mem_pool_alloc_zeroed @ 1003d420 */

int __cdecl grim_jpg_mem_pool_alloc_zeroed(int *param_1,int param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = (uint)(0xffe0 / (ulonglong)param_3);
  iVar2 = param_1[1];
  if (uVar1 == 0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x45;
    (**(code **)*param_1)(param_1);
  }
  if ((int)param_4 <= (int)uVar1) {
    uVar1 = param_4;
  }
  *(uint *)(iVar2 + 0x4c) = uVar1;
  iVar2 = grim_jpg_mem_pool_alloc(param_1,param_2,param_4 * 4);
  uVar6 = 0;
  if (param_4 != 0) {
    do {
      if (param_4 - uVar6 <= uVar1) {
        uVar1 = param_4 - uVar6;
      }
      puVar3 = grim_jpg_mem_pool_free(param_1,param_2,uVar1 * param_3);
      if (uVar1 != 0) {
        puVar4 = (undefined4 *)(iVar2 + uVar6 * 4);
        uVar6 = uVar6 + uVar1;
        uVar5 = uVar1;
        do {
          *puVar4 = puVar3;
          puVar4 = puVar4 + 1;
          puVar3 = (undefined4 *)((int)puVar3 + param_3);
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    } while (uVar6 < param_4);
  }
  return iVar2;
}



/* grim_jpg_mem_pool_realloc @ 1003d4d0 */

int __cdecl grim_jpg_mem_pool_realloc(int *param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = (uint)(0xffe0 / (ulonglong)(uint)(param_3 * 0x80));
  iVar2 = param_1[1];
  if (uVar1 == 0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x45;
    (**(code **)*param_1)(param_1);
  }
  if ((int)param_4 <= (int)uVar1) {
    uVar1 = param_4;
  }
  *(uint *)(iVar2 + 0x4c) = uVar1;
  iVar2 = grim_jpg_mem_pool_alloc(param_1,param_2,param_4 * 4);
  uVar6 = 0;
  if (param_4 != 0) {
    do {
      if (param_4 - uVar6 <= uVar1) {
        uVar1 = param_4 - uVar6;
      }
      puVar3 = grim_jpg_mem_pool_free(param_1,param_2,uVar1 * param_3 * 0x80);
      if (uVar1 != 0) {
        puVar4 = (undefined4 *)(iVar2 + uVar6 * 4);
        uVar6 = uVar6 + uVar1;
        uVar5 = uVar1;
        do {
          *puVar4 = puVar3;
          puVar4 = puVar4 + 1;
          puVar3 = puVar3 + param_3 * 0x20;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    } while (uVar6 < param_4);
  }
  return iVar2;
}



/* grim_jpg_mem_pool_alloc_small @ 1003d580 */

void __cdecl
grim_jpg_mem_pool_alloc_small(int *param_1,int param_2,undefined1 param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = param_1[1];
  if (param_2 != 1) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  puVar2 = (undefined4 *)grim_jpg_mem_pool_alloc(param_1,param_2,0x78);
  puVar2[1] = param_5;
  puVar2[2] = param_4;
  *puVar2 = 0;
  puVar2[3] = param_6;
  *(undefined1 *)(puVar2 + 8) = param_3;
  *(undefined1 *)((int)puVar2 + 0x22) = 0;
  puVar2[9] = *(undefined4 *)(iVar1 + 0x40);
  *(undefined4 **)(iVar1 + 0x40) = puVar2;
  return;
}



/* grim_jpg_mem_pool_alloc_array @ 1003d5f0 */

void __cdecl
grim_jpg_mem_pool_alloc_array(int *param_1,int param_2,undefined1 param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = param_1[1];
  if (param_2 != 1) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  puVar2 = (undefined4 *)grim_jpg_mem_pool_alloc(param_1,param_2,0x78);
  puVar2[1] = param_5;
  puVar2[2] = param_4;
  *puVar2 = 0;
  puVar2[3] = param_6;
  *(undefined1 *)(puVar2 + 8) = param_3;
  *(undefined1 *)((int)puVar2 + 0x22) = 0;
  puVar2[9] = *(undefined4 *)(iVar1 + 0x44);
  *(undefined4 **)(iVar1 + 0x44) = puVar2;
  return;
}



/* grim_jpg_mem_pool_cleanup_a @ 1003d930 */

/* [binja] int32_t sub_1003d930(int32_t* arg1) */

int __cdecl grim_jpg_mem_pool_cleanup_a(int *arg1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *in_stack_00000008;
  char in_stack_0000000c;
  
  iVar1 = in_stack_00000008[2];
  iVar3 = in_stack_00000008[4];
  iVar4 = in_stack_00000008[6] * iVar1;
  iVar5 = 0;
  if (0 < iVar3) {
    do {
      iVar2 = iVar3 - iVar5;
      if (in_stack_00000008[5] < iVar3 - iVar5) {
        iVar2 = in_stack_00000008[5];
      }
      iVar3 = in_stack_00000008[7] - (in_stack_00000008[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      iVar3 = in_stack_00000008[1] - (in_stack_00000008[6] + iVar5);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      if (iVar2 < 1) {
        return iVar2;
      }
      iVar2 = iVar2 * iVar1;
      if (in_stack_0000000c == '\0') {
        (*(code *)in_stack_00000008[10])
                  (arg1,in_stack_00000008 + 10,*(undefined4 *)(*in_stack_00000008 + iVar5 * 4),iVar4
                   ,iVar2);
      }
      else {
        (*(code *)in_stack_00000008[0xb])
                  (arg1,in_stack_00000008 + 10,*(undefined4 *)(*in_stack_00000008 + iVar5 * 4),iVar4
                   ,iVar2);
      }
      iVar3 = in_stack_00000008[4];
      iVar5 = iVar5 + in_stack_00000008[5];
      iVar4 = iVar4 + iVar2;
    } while (iVar5 < iVar3);
  }
  return iVar3;
}



/* grim_jpg_mem_pool_cleanup_b @ 1003db20 */

/* [binja] int32_t sub_1003db20(int32_t arg1) */

int __cdecl grim_jpg_mem_pool_cleanup_b(int arg1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *in_stack_00000008;
  char in_stack_0000000c;
  
  iVar1 = in_stack_00000008[2];
  iVar3 = in_stack_00000008[4];
  iVar4 = iVar1 * 0x80 * in_stack_00000008[6];
  iVar5 = 0;
  if (0 < iVar3) {
    do {
      iVar2 = iVar3 - iVar5;
      if (in_stack_00000008[5] < iVar3 - iVar5) {
        iVar2 = in_stack_00000008[5];
      }
      iVar3 = in_stack_00000008[7] - (iVar5 + in_stack_00000008[6]);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      iVar3 = in_stack_00000008[1] - (iVar5 + in_stack_00000008[6]);
      if (iVar3 <= iVar2) {
        iVar2 = iVar3;
      }
      if (iVar2 < 1) {
        return iVar2;
      }
      iVar2 = iVar2 * iVar1 * 0x80;
      if (in_stack_0000000c == '\0') {
        (*(code *)in_stack_00000008[10])
                  (arg1,in_stack_00000008 + 10,*(undefined4 *)(*in_stack_00000008 + iVar5 * 4),iVar4
                   ,iVar2);
      }
      else {
        (*(code *)in_stack_00000008[0xb])
                  (arg1,in_stack_00000008 + 10,*(undefined4 *)(*in_stack_00000008 + iVar5 * 4),iVar4
                   ,iVar2);
      }
      iVar3 = in_stack_00000008[4];
      iVar5 = iVar5 + in_stack_00000008[5];
      iVar4 = iVar4 + iVar2;
    } while (iVar5 < iVar3);
  }
  return iVar3;
}



/* grim_jpg_mem_pool_destroy @ 1003dbc0 */

void __cdecl grim_jpg_mem_pool_destroy(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = param_1[1];
  if ((param_2 < 0) || (1 < param_2)) {
    *(undefined4 *)(*param_1 + 0x14) = 0xc;
    *(int *)(*param_1 + 0x18) = param_2;
    (**(code **)*param_1)(param_1);
  }
  if (param_2 == 1) {
    for (iVar2 = *(int *)(iVar1 + 0x40); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x24)) {
      if (*(char *)(iVar2 + 0x22) != '\0') {
        *(undefined1 *)(iVar2 + 0x22) = 0;
        (**(code **)(iVar2 + 0x30))(param_1,iVar2 + 0x28);
      }
    }
    iVar2 = *(int *)(iVar1 + 0x44);
    *(undefined4 *)(iVar1 + 0x40) = 0;
    for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x24)) {
      if (*(char *)(iVar2 + 0x22) != '\0') {
        *(undefined1 *)(iVar2 + 0x22) = 0;
        (**(code **)(iVar2 + 0x30))(param_1,iVar2 + 0x28);
      }
    }
    *(undefined4 *)(iVar1 + 0x44) = 0;
  }
  puVar3 = *(undefined4 **)(iVar1 + 0x38 + param_2 * 4);
  *(undefined4 *)(iVar1 + 0x38 + param_2 * 4) = 0;
  while (puVar3 != (undefined4 *)0x0) {
    iVar2 = puVar3[2];
    iVar4 = puVar3[1];
    puVar5 = (undefined4 *)*puVar3;
    if (puVar3 != (undefined4 *)0x0) {
      operator_delete(puVar3);
    }
    *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) - (iVar2 + 0x10 + iVar4);
    puVar3 = puVar5;
  }
  puVar3 = *(undefined4 **)(iVar1 + 0x30 + param_2 * 4);
  *(undefined4 *)(iVar1 + 0x30 + param_2 * 4) = 0;
  while (puVar3 != (undefined4 *)0x0) {
    iVar2 = puVar3[2];
    iVar4 = puVar3[1];
    puVar5 = (undefined4 *)*puVar3;
    if (puVar3 != (undefined4 *)0x0) {
      operator_delete(puVar3);
    }
    *(int *)(iVar1 + 0x48) = *(int *)(iVar1 + 0x48) - (iVar2 + 0x10 + iVar4);
    puVar3 = puVar5;
  }
  return;
}



/* grim_jpg_mem_zero_block @ 1003dd30 */

void __cdecl grim_jpg_mem_zero_block(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(*(int *)(param_1 + 4) + 0x28))(param_1);
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}



/* grim_jpg_marker_skip @ 1003dd50 */

void __cdecl grim_jpg_marker_skip(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x82);
  *(undefined1 *)(iVar1 + 0x80) = 0;
  return;
}



/* grim_jpg_marker_get_length @ 1003dd70 */

void __cdecl grim_jpg_marker_get_length(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x112);
  *(undefined1 *)(iVar1 + 0x111) = 0;
  return;
}



/* grim_jpg_input_controller_init @ 1003dd90 */

void __cdecl grim_jpg_input_controller_init(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  
  piVar2 = param_1;
  if (param_1[4] != 0xca) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  iVar3 = param_1[0xb];
  uVar5 = param_1[0xc];
  if ((uint)(iVar3 * 8) < uVar5 || iVar3 * 8 - uVar5 == 0) {
    iVar3 = grim_jpg_noop_method(param_1[6],8);
    param_1[0x17] = iVar3;
    iVar3 = grim_jpg_noop_method(param_1[7],8);
    param_1[0x18] = iVar3;
    param_1[0x45] = 1;
  }
  else if ((uint)(iVar3 * 4) < uVar5 || iVar3 * 4 - uVar5 == 0) {
    iVar3 = grim_jpg_noop_method(param_1[6],4);
    param_1[0x17] = iVar3;
    iVar3 = grim_jpg_noop_method(param_1[7],4);
    param_1[0x18] = iVar3;
    param_1[0x45] = 2;
  }
  else if (uVar5 < (uint)(iVar3 * 2)) {
    param_1[0x17] = param_1[6];
    param_1[0x18] = param_1[7];
    param_1[0x45] = 8;
  }
  else {
    iVar3 = grim_jpg_noop_method(param_1[6],2);
    param_1[0x17] = iVar3;
    iVar3 = grim_jpg_noop_method(param_1[7],2);
    param_1[0x18] = iVar3;
    param_1[0x45] = 4;
  }
  piVar6 = param_1 + 8;
  piVar1 = param_1 + 0x31;
  param_1 = (int *)0x0;
  if (0 < *piVar6) {
    piVar6 = (int *)(*piVar1 + 0xc);
    do {
      iVar3 = piVar2[0x45];
      iVar4 = iVar3;
      if (iVar3 < 8) {
        do {
          iVar7 = piVar6[-1] * iVar4 * 2;
          if ((iVar7 - piVar2[0x43] * iVar3 != 0 && piVar2[0x43] * iVar3 <= iVar7) ||
             (iVar7 = *piVar6 * iVar4 * 2,
             iVar7 - piVar2[0x44] * iVar3 != 0 && piVar2[0x44] * iVar3 <= iVar7)) break;
          iVar4 = iVar4 * 2;
        } while (iVar4 < 8);
      }
      piVar6[6] = iVar4;
      param_1 = (int *)((int)param_1 + 1);
      piVar6 = piVar6 + 0x15;
    } while ((int)param_1 < piVar2[8]);
  }
  iVar3 = 0;
  if (0 < piVar2[8]) {
    piVar6 = (int *)(piVar2[0x31] + 0x24);
    do {
      iVar4 = grim_jpg_noop_method(piVar6[-7] * *piVar6 * piVar2[6],piVar2[0x43] << 3);
      piVar6[1] = iVar4;
      iVar4 = grim_jpg_noop_method(piVar6[-6] * *piVar6 * piVar2[7],piVar2[0x44] << 3);
      piVar6[2] = iVar4;
      iVar3 = iVar3 + 1;
      piVar6 = piVar6 + 0x15;
    } while (iVar3 < piVar2[8]);
  }
  switch(piVar2[10]) {
  case 1:
    piVar2[0x19] = 1;
    break;
  case 2:
  case 3:
    piVar2[0x19] = 3;
    break;
  case 4:
  case 5:
    piVar2[0x19] = 4;
    break;
  default:
    piVar2[0x19] = piVar2[8];
  }
  iVar3 = 1;
  if (*(char *)((int)piVar2 + 0x4a) == '\0') {
    iVar3 = piVar2[0x19];
  }
  piVar2[0x1a] = iVar3;
  uVar5 = grim_jpg_input_consume_markers((int)piVar2);
  if ((char)uVar5 == '\0') {
    piVar2[0x1b] = 1;
    return;
  }
  piVar2[0x1b] = piVar2[0x44];
  return;
}



/* grim_jpg_input_consume_markers @ 1003dfb0 */

uint __cdecl grim_jpg_input_consume_markers(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 in_EAX;
  undefined3 uVar4;
  uint uVar3;
  
  uVar4 = (undefined3)((uint)in_EAX >> 8);
  uVar3 = CONCAT31(uVar4,*(char *)(param_1 + 0x48));
  if (((((*(char *)(param_1 + 0x48) != '\0') ||
        (uVar3 = CONCAT31(uVar4,*(char *)(param_1 + 0x108)), *(char *)(param_1 + 0x108) != '\0')) ||
       (uVar3 = 0, *(int *)(param_1 + 0x24) != 3)) ||
      (((*(int *)(param_1 + 0x20) != 3 || (*(int *)(param_1 + 0x28) != 2)) ||
       ((*(int *)(param_1 + 100) != 3 ||
        ((iVar1 = *(int *)(param_1 + 0xc4), *(int *)(iVar1 + 8) != 2 ||
         (uVar3 = 1, *(int *)(iVar1 + 0x5c) != 1)))))))) ||
     ((*(int *)(iVar1 + 0xb0) != 1 ||
      (((((2 < *(int *)(iVar1 + 0xc) || (*(int *)(iVar1 + 0x60) != 1)) ||
         (*(int *)(iVar1 + 0xb4) != 1)) ||
        ((iVar2 = *(int *)(param_1 + 0x114), *(int *)(iVar1 + 0x24) != iVar2 ||
         (*(int *)(iVar1 + 0x78) != iVar2)))) || (*(int *)(iVar1 + 0xcc) != iVar2)))))) {
    uVar3 = uVar3 & 0xffffff00;
  }
  return uVar3;
}



/* grim_jpg_input_fill_buffer @ 1003e2d0 */

void __cdecl grim_jpg_input_fill_buffer(int *param_1)

{
  int iVar1;
  
  iVar1 = param_1[0x5f];
  if (*(char *)(iVar1 + 8) == '\0') {
    if ((*(char *)((int)param_1 + 0x4a) != '\0') && (param_1[0x1d] == 0)) {
      if (((char)param_1[0x14] == '\0') || (*(char *)((int)param_1 + 0x5a) == '\0')) {
        if ((char)param_1[0x16] == '\0') {
          *(undefined4 *)(*param_1 + 0x14) = 0x2d;
          (**(code **)*param_1)(param_1);
        }
        else {
          param_1[0x69] = *(int *)(iVar1 + 0x14);
        }
      }
      else {
        param_1[0x69] = *(int *)(iVar1 + 0x18);
        *(undefined1 *)(iVar1 + 8) = 1;
      }
    }
    (**(code **)param_1[0x66])(param_1);
    (**(code **)(param_1[0x61] + 8))(param_1);
    if (*(char *)((int)param_1 + 0x41) == '\0') {
      if (*(char *)(iVar1 + 0x10) == '\0') {
        (**(code **)param_1[0x68])(param_1);
      }
      (**(code **)param_1[0x67])(param_1);
      if (*(char *)((int)param_1 + 0x4a) != '\0') {
        (**(code **)param_1[0x69])(param_1,*(undefined1 *)(iVar1 + 8));
      }
      (**(code **)param_1[0x62])(param_1,-(*(char *)(iVar1 + 8) != '\0') & 3);
      (**(code **)param_1[0x60])(param_1,0);
    }
  }
  else {
    *(undefined1 *)(iVar1 + 8) = 0;
    (**(code **)param_1[0x69])(param_1,0);
    (**(code **)param_1[0x62])(param_1,2);
    (**(code **)param_1[0x60])(param_1,2);
  }
  if (param_1[2] != 0) {
    *(undefined4 *)(param_1[2] + 0xc) = *(undefined4 *)(iVar1 + 0xc);
    *(uint *)(param_1[2] + 0x10) = (*(char *)(iVar1 + 8) != '\0') + 1 + *(int *)(iVar1 + 0xc);
    if (((char)param_1[0x10] != '\0') && (*(char *)(param_1[99] + 0x11) == '\0')) {
      *(uint *)(param_1[2] + 0x10) =
           *(int *)(param_1[2] + 0x10) + (*(char *)((int)param_1 + 0x5a) != '\0') + 1;
    }
  }
  return;
}



/* grim_jpg_noop_method @ 1003e460 */

int __cdecl grim_jpg_noop_method(int param_1,int param_2)

{
  return (param_1 + -1 + param_2) / param_2;
}



/* grim_jpg_data_src_init @ 1003e470 */

int __cdecl grim_jpg_data_src_init(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -1 + param_2;
  return iVar1 - iVar1 % param_2;
}



/* grim_jpg_data_src_fill_buffer @ 1003e490 */

void __cdecl grim_jpg_data_src_fill_buffer(int param_1,int param_2,int param_3,int param_4,int param_5,uint param_6)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar1 = (undefined4 *)(param_1 + param_2 * 4);
  puVar3 = (undefined4 *)(param_3 + param_4 * 4);
  if (0 < param_5) {
    do {
      puVar4 = (undefined4 *)*puVar1;
      puVar5 = (undefined4 *)*puVar3;
      for (uVar2 = param_6 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
      param_5 = param_5 + -1;
      for (uVar2 = param_6 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    } while (param_5 != 0);
  }
  return;
}



/* grim_jpg_data_src_skip @ 1003e4e0 */

void __cdecl grim_jpg_data_src_skip(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  for (uVar1 = (uint)(param_3 << 7) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_2 = *param_1;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)param_2 = *(undefined1 *)param_1;
    param_1 = (undefined4 *)((int)param_1 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
  }
  return;
}



/* grim_jpg_data_src_term @ 1003e510 */

void __cdecl grim_jpg_data_src_term(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  
  for (uVar1 = param_2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  for (uVar1 = param_2 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)param_1 = 0;
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}



/* grim_jpg_data_src_reset @ 1003e530 */

/* [binja] int32_t sub_1003e530(int32_t arg1) __pure */

int __cdecl grim_jpg_data_src_reset(int arg1)

{
  int in_stack_0000000c;
  
  return in_stack_0000000c;
}



/* grim_jpg_data_src_rewind @ 1003e540 */

void __cdecl grim_jpg_data_src_rewind(int *param_1)

{
  *(undefined4 *)(*param_1 + 0x14) = 0x30;
  (**(code **)*param_1)(param_1);
  return;
}



/* grim_jpg_data_src_check @ 1003e560 */

undefined4 grim_jpg_data_src_check(void)

{
  return 0;
}



/* grim_jpg_data_src_setup @ 1003e570 */

void __cdecl grim_jpg_data_src_setup(int *param_1,char param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  
  puVar2 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x50);
  param_1[0x60] = (int)puVar2;
  *puVar2 = &LAB_1003e6f0;
  if (param_2 != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 4;
    (**(code **)*param_1)(param_1);
  }
  if (*(char *)(param_1[0x67] + 8) == '\0') {
    _param_2 = param_1[0x45];
  }
  else {
    if (param_1[0x45] < 2) {
      *(undefined4 *)(*param_1 + 0x14) = 0x2e;
      (**(code **)*param_1)(param_1);
    }
    iVar8 = param_1[0x60];
    iVar1 = param_1[0x45];
    iVar3 = (**(code **)param_1[1])(param_1,1,param_1[8] << 3);
    *(int *)(iVar8 + 0x38) = iVar3;
    *(int *)(iVar8 + 0x3c) = iVar3 + param_1[8] * 4;
    iVar3 = 0;
    if (0 < param_1[8]) {
      piVar7 = (int *)(param_1[0x31] + 0xc);
      do {
        iVar4 = (piVar7[6] * *piVar7) / param_1[0x45];
        iVar9 = (iVar1 + 4) * iVar4;
        iVar5 = (**(code **)param_1[1])(param_1,1,iVar9 * 8);
        iVar5 = iVar5 + iVar4 * 4;
        *(int *)(*(int *)(iVar8 + 0x38) + iVar3 * 4) = iVar5;
        *(int *)(*(int *)(iVar8 + 0x3c) + iVar3 * 4) = iVar5 + iVar9 * 4;
        iVar3 = iVar3 + 1;
        piVar7 = piVar7 + 0x15;
      } while (iVar3 < param_1[8]);
    }
    _param_2 = param_1[0x45] + 2;
  }
  iVar8 = 0;
  if (0 < param_1[8]) {
    piVar7 = (int *)(param_1[0x31] + 0x24);
    puVar2 = puVar2 + 2;
    do {
      uVar6 = (**(code **)(param_1[1] + 8))
                        (param_1,1,piVar7[-2] * *piVar7,
                         ((piVar7[-6] * *piVar7) / param_1[0x45]) * _param_2);
      *puVar2 = uVar6;
      iVar8 = iVar8 + 1;
      puVar2 = puVar2 + 1;
      piVar7 = piVar7 + 0x15;
    } while (iVar8 < param_1[8]);
  }
  return;
}



/* grim_jpg_output_init @ 1003e8c0 */

void __cdecl grim_jpg_output_init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_1 + 0x180);
  if (*(char *)(iVar2 + 0x30) == '\0') {
    iVar4 = (**(code **)(*(int *)(param_1 + 0x184) + 0xc))(param_1,iVar2 + 8);
    if (iVar4 == 0) {
      return;
    }
    *(undefined1 *)(iVar2 + 0x30) = 1;
  }
  uVar3 = *(uint *)(param_1 + 0x114);
  puVar1 = (uint *)(iVar2 + 0x34);
  (**(code **)(*(int *)(param_1 + 0x188) + 4))
            (param_1,iVar2 + 8,puVar1,uVar3,param_2,param_3,param_4);
  if (uVar3 <= *puVar1) {
    *(undefined1 *)(iVar2 + 0x30) = 0;
    *puVar1 = 0;
  }
  return;
}


