/* grim_format_info_lookup @ 1000aaa6 */

/* returns pointer to the D3D format descriptor entry (fallbacks to default) */

int * __cdecl grim_format_info_lookup(int format)

{
  int *piVar1;
  
  piVar1 = &grim_format_info_table;
  while( true ) {
    if (grim_format_info_table_end <= piVar1) {
      return &grim_format_info_rgb565;
    }
    if (format == *piVar1) break;
    piVar1 = piVar1 + 9;
  }
  return piVar1;
}



/* grim_format_compare @ 1000aaca */

/* [binja] int32_t __fastcall sub_1000aaca(void* arg1, int32_t arg2) */

int __fastcall grim_format_compare(void *arg1,int arg2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint local_8;
  
  uVar3 = 0;
  if (*(int *)(&grim_format_compat_table + (*(int *)((int)arg1 + 4) * 5 + *(int *)(arg2 + 4)) * 4) != 0) {
    local_8 = 0;
    puVar5 = (uint *)((int)arg1 + 0xc);
    iVar4 = 5;
    do {
      uVar1 = *puVar5;
      if (uVar1 != 0) {
        local_8 = local_8 + 1;
      }
      uVar2 = *(uint *)((arg2 - (int)arg1) + (int)puVar5);
      if (uVar1 < uVar2) {
        if (uVar1 == 0) {
          uVar3 = uVar3 + 0x100;
        }
        else {
          uVar3 = uVar3 + (uVar2 - uVar1);
        }
      }
      else if (uVar2 < uVar1) {
        if (uVar2 == 0) {
          uVar3 = uVar3 + 0x1000000;
        }
        else {
          uVar3 = uVar3 + (uVar1 - uVar2) * 0x10000;
        }
      }
      puVar5 = puVar5 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    if (local_8 != uVar3 >> 0x18) {
      return uVar3;
    }
  }
  return -1;
}



/* grim_format_find_best @ 1000ab3f */

int __cdecl grim_format_find_best(int *param_1,int param_2,int *param_3)

{
  int *arg2;
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = 0xffffffff;
  piVar3 = &grim_format_info_rgb565;
  do {
    if (*param_1 == 0) {
      return *piVar3;
    }
    arg2 = grim_format_info_lookup(*param_1);
    if ((*arg2 != 0) && ((arg2[1] != 1 || (param_2 != 0)))) {
      if (*param_3 == *arg2) {
        return *param_3;
      }
      uVar1 = grim_format_compare(param_3,(int)arg2);
      if (((uVar1 != 0xffffffff) && (uVar1 <= uVar2)) &&
         ((uVar1 != uVar2 || ((uint)arg2[2] < (uint)piVar3[2])))) {
        uVar2 = uVar1;
        piVar3 = arg2;
      }
    }
    param_1 = param_1 + 1;
  } while( true );
}



/* grim_format_find_supported @ 1000abad */

int __cdecl grim_format_find_supported(int *param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int *arg2;
  int *piVar4;
  int *piVar5;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined1 local_18 [12];
  undefined4 local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  grim_d3d_debug_set_mute(1);
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 0x18))(param_1,&local_8);
    (**(code **)(*param_1 + 0x1c))(param_1,&local_ec);
    (**(code **)(*param_1 + 0x20))(param_1,local_18);
  }
  uVar3 = 0xffffffff;
  arg2 = &grim_format_info_table;
  piVar5 = &grim_format_info_rgb565;
  piVar4 = &grim_format_info_rgb565;
  if (&grim_format_info_table < grim_format_info_table_end) {
    do {
      piVar5 = piVar4;
      if ((*arg2 != 0) &&
         ((param_1 == (int *)0x0 ||
          (iVar1 = (**(code **)(*local_8 + 0x28))
                             (local_8,local_e8,local_ec,local_c,param_2,param_3,*arg2), -1 < iVar1))
         )) {
        piVar5 = arg2;
        if (*param_4 == *arg2) break;
        piVar5 = piVar4;
        if ((((arg2[8] != 0) && (uVar2 = grim_format_compare(param_4,(int)arg2), uVar2 != 0xffffffff)) &&
            (uVar2 <= uVar3)) && ((uVar2 != uVar3 || ((uint)arg2[2] < (uint)piVar4[2])))) {
          uVar3 = uVar2;
          piVar5 = arg2;
        }
      }
      arg2 = arg2 + 9;
      piVar4 = piVar5;
    } while (arg2 < grim_format_info_table_end);
  }
  if (local_8 != (int *)0x0) {
    (**(code **)(*local_8 + 8))(local_8);
    local_8 = (int *)0x0;
  }
  grim_d3d_debug_set_mute(0);
  return *piVar5;
}



/* grim_format_convert_fourcc @ 1000ac8f */

int __cdecl grim_format_convert_fourcc(int param_1)

{
  if (param_1 == 0x36314c20) {
    return 0x32;
  }
  if (param_1 == 0x36314c41) {
    return 0x33;
  }
  if (param_1 == 0x36315220) {
    return 0x14;
  }
  if (param_1 != 0x36315241) {
    return param_1;
  }
  return 0x15;
}



/* grim_pixel_noop @ 10016c3b */

void grim_pixel_noop(void)

{
  return;
}



/* grim_pixel_format_convert_surface @ 10016c3c */

/* [binja] int32_t __fastcall sub_10016c3c(void*** arg1) */

int grim_pixel_format_convert_surface(void ***arg1)

{
  int extraout_EAX;
  undefined4 *this;
  uint uVar1;
  int unaff_EBP;
  uint uVar2;
  
  seh_prolog();
  *(undefined4 **)(unaff_EBP + -0x14) = this;
  *this = &PTR_FUN_1004caf8;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if ((this[0x42f] != 0) && (this[0x430] != 0)) {
    uVar1 = this[0x427];
    uVar2 = this[0x428];
    *(undefined4 *)(unaff_EBP + -0x10) = this[0x430];
    if (uVar1 < uVar2) {
      do {
        for (uVar2 = this[0x424]; uVar2 < (uint)this[0x426]; uVar2 = uVar2 + 4) {
          operator_delete(*(void **)(*(int *)(unaff_EBP + -0x10) + 4));
          *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 8;
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < (uint)this[0x428]);
    }
  }
  operator_delete((void *)this[0x42e]);
  operator_delete((void *)this[0x430]);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_vertex_space_converter_destroy(this);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return extraout_EAX;
}



/* grim_pixel_format_write_dxt_cache @ 10016cdc */

/* writes RGBA floats into the DXT block cache and encodes when block data is complete */

void grim_pixel_format_write_dxt_cache(void *this,uint x,uint y,float *pixels)

{
  int iVar1;
  undefined4 *puVar2;
  void *pvVar3;
  float *pfVar4;
  void *this_00;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int unaff_EBP;
  uint uVar9;
  undefined4 *puVar10;
  uint *puVar11;
  
  seh_prolog();
  uVar9 = *(int *)(unaff_EBP + 8) + *(int *)((int)this_00 + 0x1034);
  *(int *)(unaff_EBP + 0xc) = *(int *)(unaff_EBP + 0xc) + *(int *)((int)this_00 + 0x1040);
  iVar6 = *(int *)((int)this_00 + 0x10c0);
  *(uint *)(unaff_EBP + 8) = uVar9;
  if (iVar6 == 0) {
    puVar2 = operator_new(*(int *)((int)this_00 + 0x10a8) * *(int *)((int)this_00 + 0x10ac) * 8);
    *(undefined4 **)((int)this_00 + 0x10c0) = puVar2;
    if (puVar2 == (undefined4 *)0x0) goto LAB_100170c5;
    for (uVar5 = (uint)(*(int *)((int)this_00 + 0x10a8) * *(int *)((int)this_00 + 0x10ac) * 8) >> 2;
        uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined1 *)puVar2 = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
  }
  puVar11 = (uint *)(*(int *)((int)this_00 + 0x10c0) +
                    ((*(int *)(unaff_EBP + 0xc) - *(int *)((int)this_00 + 0x109c)) *
                     *(int *)((int)this_00 + 0x10a8) +
                    (uVar9 - *(int *)((int)this_00 + 0x1090) >> 2)) * 8);
  uVar5 = puVar11[1];
  *(uint **)(unaff_EBP + -0x10) = puVar11;
  if (uVar5 == 0) {
    iVar6 = *(int *)((int)this_00 + 0x10a4);
    *(int *)(unaff_EBP + -0x18) = iVar6 << 4;
    pvVar3 = operator_new(iVar6 << 8);
    *(void **)(unaff_EBP + -0x14) = pvVar3;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar3 == (void *)0x0) {
      uVar5 = 0;
    }
    else {
      _vector_constructor_iterator_
                (pvVar3,0x10,*(int *)(unaff_EBP + -0x18),(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      uVar5 = *(uint *)(unaff_EBP + -0x14);
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    puVar11[1] = uVar5;
    if (uVar5 == 0) goto LAB_100170c5;
    *puVar11 = 0;
    *(int *)((int)this_00 + 0x10bc) = *(int *)((int)this_00 + 0x10bc) + 1;
  }
  if (*puVar11 == 0) {
    uVar5 = 4;
    if (3 < *(uint *)((int)this_00 + 0x103c)) {
      uVar5 = *(uint *)((int)this_00 + 0x103c);
    }
    if (((uVar9 & 3) < *(uint *)((int)this_00 + 0x1034)) || (uVar5 < (uVar9 & 3) + 4)) {
      uVar5 = *(uint *)((int)this_00 + 0x108c);
      iVar6 = (uVar9 >> 2) * *(int *)((int)this_00 + 0x1050) +
              (uVar5 >> 2) * *(int *)((int)this_00 + 0x1080) +
              *(int *)((int)this_00 + 0x1054) * *(int *)(unaff_EBP + 0xc) +
              *(int *)((int)this_00 + 0x18);
      *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 4);
      *(uint *)(unaff_EBP + -0x18) = uVar5;
      while (uVar5 < *(uint *)((int)this_00 + 0x1094)) {
        (**(code **)((int)this_00 + 0x1084))(*(undefined4 *)(unaff_EBP + -0x14),iVar6);
        iVar6 = iVar6 + *(int *)((int)this_00 + 0x1080);
        *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 0x100;
        *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x18) + 4;
        uVar5 = *(uint *)(unaff_EBP + -0x18);
      }
      puVar11 = *(uint **)(unaff_EBP + -0x10);
    }
    else {
      uVar5 = *(uint *)((int)this_00 + 0x1038);
      *(undefined4 *)(unaff_EBP + -0x18) = 4;
      if (3 < uVar5) {
        *(uint *)(unaff_EBP + -0x18) = uVar5;
      }
      if (*(uint *)((int)this_00 + 0x108c) < *(uint *)((int)this_00 + 0x1030)) {
        (**(code **)((int)this_00 + 0x1084))
                  (puVar11[1],
                   (*(uint *)((int)this_00 + 0x108c) >> 2) * *(int *)((int)this_00 + 0x1080) +
                   (uVar9 >> 2) * *(int *)((int)this_00 + 0x1050) +
                   *(int *)((int)this_00 + 0x1054) * *(int *)(unaff_EBP + 0xc) +
                   *(int *)((int)this_00 + 0x18));
      }
      if (*(uint *)(unaff_EBP + -0x18) < *(uint *)((int)this_00 + 0x1094)) {
        (**(code **)((int)this_00 + 0x1084))
                  (puVar11[1],
                   (*(uint *)((int)this_00 + 0x1094) - 4 >> 2) * *(int *)((int)this_00 + 0x1080) +
                   (uVar9 >> 2) * *(int *)((int)this_00 + 0x1050) +
                   *(int *)((int)this_00 + 0x1054) * *(int *)(unaff_EBP + 0xc) +
                   *(int *)((int)this_00 + 0x18));
      }
    }
  }
  if (*(int *)((int)this_00 + 0x1048) != 0) {
    pfVar4 = grim_convert_vertex_space(this_00,*(float **)(unaff_EBP + 0x10));
    *(float **)(unaff_EBP + 0x10) = pfVar4;
  }
  uVar5 = *(int *)((int)this_00 + 0x1030) - *(int *)((int)this_00 + 0x108c);
  iVar6 = *(int *)((int)this_00 + 0x1090);
  uVar7 = *(int *)((int)this_00 + 0x1058) + uVar5;
  if (uVar5 < uVar7) {
    do {
      puVar10 = (undefined4 *)
                (((uVar5 & 0xfffffffc | uVar9 - iVar6 & 3) << 2 | uVar5 & 3) * 0x10 +
                *(int *)(*(int *)(unaff_EBP + -0x10) + 4));
      puVar2 = *(undefined4 **)(unaff_EBP + 0x10);
      *(int *)(unaff_EBP + 0x10) = *(int *)(unaff_EBP + 0x10) + 0x10;
      *puVar10 = *puVar2;
      puVar10[1] = puVar2[1];
      puVar10[2] = puVar2[2];
      uVar5 = uVar5 + 1;
      puVar10[3] = puVar2[3];
    } while (uVar5 < uVar7);
    uVar9 = *(uint *)(unaff_EBP + 8);
    puVar11 = *(uint **)(unaff_EBP + -0x10);
  }
  uVar5 = uVar9 - *(int *)((int)this_00 + 0x1090) & 3;
  if (*(int *)((int)this_00 + 0x1074) == 0) {
    *puVar11 = *puVar11 | 1 << (sbyte)uVar5;
  }
  else {
    *(undefined4 *)(unaff_EBP + 0x10) = 0;
    do {
      if ((*(uint *)((int)this_00 + 0x107c) & *(uint *)(unaff_EBP + 0x10)) == uVar5) {
        *puVar11 = *puVar11 | 1 << ((byte)*(undefined4 *)(unaff_EBP + 0x10) & 0x1f);
      }
      *(int *)(unaff_EBP + 0x10) = *(int *)(unaff_EBP + 0x10) + 1;
    } while (*(uint *)(unaff_EBP + 0x10) < 4);
  }
  if (*puVar11 == 0xf) {
    uVar5 = *(uint *)((int)this_00 + 0x108c);
    iVar6 = (uVar9 >> 2) * *(int *)((int)this_00 + 0x1050) +
            (uVar5 >> 2) * *(int *)((int)this_00 + 0x1080) +
            *(int *)((int)this_00 + 0x1054) * *(int *)(unaff_EBP + 0xc) +
            *(int *)((int)this_00 + 0x18);
    *(uint *)(unaff_EBP + 0xc) = puVar11[1];
    *(uint *)(unaff_EBP + -0x18) = uVar5;
    while (uVar9 = *(uint *)((int)this_00 + 0x1094), *(int *)(unaff_EBP + -0x14) = iVar6,
          uVar5 < uVar9) {
      uVar9 = 0;
      if (*(int *)((int)this_00 + 0x1074) != 0) {
        uVar8 = *(undefined4 *)(unaff_EBP + 0xc);
        do {
          *(undefined4 *)(unaff_EBP + 0x10) = 0;
          iVar6 = uVar9 << 2;
          *(undefined4 *)(unaff_EBP + 8) = uVar8;
          do {
            iVar1 = (*(uint *)(unaff_EBP + 0x10) & *(uint *)((int)this_00 + 0x1078)) +
                    (*(uint *)((int)this_00 + 0x107c) & uVar9) * 4;
            if (iVar6 != iVar1) {
              puVar2 = *(undefined4 **)(unaff_EBP + 8);
              puVar10 = (undefined4 *)(iVar1 * 0x10 + *(int *)(unaff_EBP + 0xc));
              *puVar2 = *puVar10;
              puVar2[1] = puVar10[1];
              puVar2[2] = puVar10[2];
              puVar2[3] = puVar10[3];
              puVar11 = *(uint **)(unaff_EBP + -0x10);
            }
            *(int *)(unaff_EBP + 0x10) = *(int *)(unaff_EBP + 0x10) + 1;
            *(int *)(unaff_EBP + 8) = *(int *)(unaff_EBP + 8) + 0x10;
            iVar6 = iVar6 + 1;
          } while (*(uint *)(unaff_EBP + 0x10) < 4);
          uVar8 = *(undefined4 *)(unaff_EBP + 8);
          uVar9 = uVar9 + 1;
        } while (uVar9 < 4);
      }
      iVar6 = *(int *)(unaff_EBP + -0x14);
      (**(code **)((int)this_00 + 0x1088))(iVar6,*(undefined4 *)(unaff_EBP + 0xc));
      iVar6 = iVar6 + *(int *)((int)this_00 + 0x1080);
      *(int *)(unaff_EBP + 0xc) = *(int *)(unaff_EBP + 0xc) + 0x100;
      *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x18) + 4;
      uVar5 = *(uint *)(unaff_EBP + -0x18);
    }
    if (((puVar11 + 2 <
          (uint *)(*(int *)((int)this_00 + 0x10c0) +
                  *(int *)((int)this_00 + 0x10ac) * *(int *)((int)this_00 + 0x10a8) * 8)) &&
        (puVar11[2] == 0)) && (puVar11[3] == 0)) {
      puVar11[3] = puVar11[1];
      puVar11[1] = 0;
    }
    else {
      operator_delete((void *)puVar11[1]);
      *(int *)((int)this_00 + 0x10bc) = *(int *)((int)this_00 + 0x10bc) + -1;
    }
    puVar11[1] = 0;
  }
LAB_100170c5:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



/* grim_pixel_format_init @ 100170f9 */

/* initializes format descriptor, bytes-per-pixel, palette expansion, and coordinate mode */

void * __thiscall grim_pixel_format_init(void *this,uint *desc,uint bits_per_pixel,uint coord_mode)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  float *pfVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  
  *(undefined ***)this = &PTR_FUN_1004cae4;
  _vector_constructor_iterator_
            ((void *)((int)this + 0x30),0x10,0x100,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
  *(uint *)((int)this + 0x18) = *desc;
  *(uint *)((int)this + 4) = desc[1];
  *(uint *)((int)this + 0x1050) = desc[2];
  *(uint *)((int)this + 0x1054) = desc[3];
  puVar6 = desc + 10;
  puVar9 = (uint *)((int)this + 0x1030);
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar9 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar9 = puVar9 + 1;
  }
  puVar3 = &DAT_10054418;
  if (desc[0x10] == 0) {
    puVar3 = &DAT_10054398;
  }
  *(undefined **)((int)this + 0x2c) = puVar3;
  *(uint *)((int)this + 0x1068) = bits_per_pixel >> 3;
  *(undefined4 *)((int)this + 0x1048) = 0;
  *(undefined4 *)((int)this + 0x104c) = 0;
  *(uint *)((int)this + 0xc) = (uint)(bits_per_pixel != 0);
  *(uint *)((int)this + 8) = coord_mode;
  uVar7 = desc[0x11];
  *(uint *)((int)this + 0x10) = uVar7;
  if (uVar7 != 0) {
    uVar7 = desc[0x11];
    *(float *)((int)this + 0x1c) = (float)(uVar7 >> 0x10 & 0xff) * 0.003921569;
    *(float *)((int)this + 0x20) = (float)(uVar7 >> 8 & 0xff) * 0.003921569;
    *(float *)((int)this + 0x24) = (float)(uVar7 & 0xff) * 0.003921569;
    *(float *)((int)this + 0x28) = (float)(uVar7 >> 0x18) * 0.003921569;
  }
  if ((*(int *)((int)this + 4) == 0x29) || (*(int *)((int)this + 4) == 0x28)) {
    *(undefined4 *)((int)this + 0x14) = 1;
    if (desc[0x12] == 0) {
      iVar2 = 0x100;
      puVar1 = (undefined4 *)((int)this + 0x38);
      do {
        puVar1[1] = 0x3f800000;
        *puVar1 = 0x3f800000;
        iVar2 = iVar2 + -1;
        puVar1[-1] = 0x3f800000;
        puVar1[-2] = 0x3f800000;
        puVar1 = puVar1 + 4;
      } while (iVar2 != 0);
    }
    else {
      pfVar4 = (float *)((int)this + 0x34);
      uVar7 = 0;
      do {
        uVar8 = uVar7 + 4;
        pfVar4[-1] = (float)*(byte *)(uVar7 + desc[0x12]) * 0.003921569;
        *pfVar4 = (float)*(byte *)(uVar7 + 1 + desc[0x12]) * 0.003921569;
        pfVar4[1] = (float)*(byte *)(uVar7 + 2 + desc[0x12]) * 0.003921569;
        pfVar4[2] = (float)*(byte *)(uVar7 + 3 + desc[0x12]) * 0.003921569;
        pfVar4 = pfVar4 + 4;
        uVar7 = uVar8;
      } while (uVar8 < 0x400);
    }
  }
  else {
    *(undefined4 *)((int)this + 0x14) = 0;
  }
  *(int *)((int)this + 0x105c) = *(int *)((int)this + 0x103c) - *(int *)((int)this + 0x1034);
  iVar2 = *(int *)((int)this + 0x1030);
  iVar5 = *(int *)((int)this + 0x1038) - iVar2;
  *(int *)((int)this + 0x1060) = *(int *)((int)this + 0x1044) - *(int *)((int)this + 0x1040);
  *(int *)((int)this + 0x1058) = iVar5;
  *(int *)((int)this + 0x1064) = *(int *)((int)this + 0x1068) * iVar5;
  if (*(int *)((int)this + 0xc) != 0) {
    *(int *)((int)this + 0x18) =
         *(int *)((int)this + 0x18) +
         *(int *)((int)this + 0x1068) * iVar2 +
         *(int *)((int)this + 0x1050) * *(int *)((int)this + 0x1034) +
         *(int *)((int)this + 0x1054) * *(int *)((int)this + 0x1040);
    *(undefined4 *)((int)this + 0x1038) = *(undefined4 *)((int)this + 0x1058);
    *(undefined4 *)((int)this + 0x103c) = *(undefined4 *)((int)this + 0x105c);
    *(int *)((int)this + 0x1030) = 0;
    *(undefined4 *)((int)this + 0x1034) = 0;
    *(undefined4 *)((int)this + 0x1040) = 0;
    *(undefined4 *)((int)this + 0x1044) = *(undefined4 *)((int)this + 0x1060);
  }
  return this;
}



/* grim_pixel_write_row_dispatch @ 100173dc */

/* [binja] int32_t __fastcall sub_100173dc(int32_t* arg1) */

int __fastcall grim_pixel_write_row_dispatch(int *arg1)

{
  int *piVar1;
  int *piVar2;
  undefined1 local_28 [8];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = arg1[0x416];
  local_14 = arg1[0x419];
  local_18 = arg1[6];
  local_1c = arg1[0xb];
  local_20 = arg1[4];
  arg1[0x419] = arg1[0x41a];
  arg1[0x416] = 1;
  arg1[6] = (int)local_28;
  arg1[0xb] = (int)&DAT_10054398;
  arg1[4] = 0;
  if (arg1[2] != 1) {
    piVar1 = arg1 + 0x412;
    local_8 = *piVar1;
    piVar2 = arg1 + 0x413;
    local_c = *piVar2;
    *piVar1 = 1;
    *piVar2 = (int)(arg1 + 7);
    grim_convert_vertex_space(arg1,(float *)(arg1 + 7));
    *piVar1 = local_8;
    *piVar2 = local_c;
  }
  (**(code **)(*arg1 + 8))(0,0,arg1 + 7);
  (**(code **)(*arg1 + 4))(0,0,arg1 + 7);
  arg1[0x416] = local_10;
  arg1[0x419] = local_14;
  arg1[6] = local_18;
  arg1[0xb] = local_1c;
  arg1[4] = local_20;
  return local_20;
}



/* grim_write_row_rgb24_dither @ 10017518 */

/* [binja] int16_t __thiscall sub_10017518(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_rgb24_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined1 *extraout_EDX;
  undefined1 *puVar4;
  uint uVar5;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  iVar3 = 0;
  uVar5 = 0;
  puVar4 = extraout_EDX;
  if (*(int *)((int)this + 0x1058) != 0) {
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar5 & 3) * 4);
      *puVar4 = (char)(int)ROUND(*(float *)(iVar3 + 8 + arg3) * 255.0 + fVar1);
      puVar4[1] = (char)(int)ROUND(*(float *)(iVar3 + 4 + arg3) * 255.0 + fVar1);
      puVar4[2] = (char)(int)ROUND(*(float *)(iVar3 + arg3) * 255.0 + fVar1);
      puVar4 = puVar4 + 3;
      uVar5 = uVar5 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar5 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_argb32_dither @ 10017604 */

/* [binja] int16_t __thiscall sub_10017604(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_argb32_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  uint *extraout_EDX;
  uint *puVar8;
  uint uVar9;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar9 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar8 = extraout_EDX;
    do {
      fVar5 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar9 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar3 = iVar7 + 8;
      iVar4 = iVar7 + 0xc;
      iVar7 = iVar7 + 0x10;
      *puVar8 = (((int)ROUND(*(float *)(iVar4 + arg3) * 255.0 + fVar5) << 8 |
                 (int)ROUND(*pfVar1 * 255.0 + fVar5)) << 8 |
                (int)ROUND(*(float *)(iVar2 + arg3) * 255.0 + fVar5)) << 8 |
                (int)ROUND(*(float *)(iVar3 + arg3) * 255.0 + fVar5);
      puVar8 = puVar8 + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_xrgb32_dither @ 10017727 */

/* [binja] int16_t __thiscall sub_10017727(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_xrgb32_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint *extraout_EDX;
  uint *puVar7;
  uint uVar8;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar5 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar8 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    puVar7 = extraout_EDX;
    do {
      fVar4 = *(float *)(iVar5 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar8 & 3) * 4);
      pfVar1 = (float *)(iVar6 + arg3);
      iVar2 = iVar6 + 4;
      iVar3 = iVar6 + 8;
      iVar6 = iVar6 + 0x10;
      *puVar7 = ((int)ROUND(*pfVar1 * 255.0 + fVar4) << 8 |
                (int)ROUND(*(float *)(iVar2 + arg3) * 255.0 + fVar4)) << 8 |
                (int)ROUND(*(float *)(iVar3 + arg3) * 255.0 + fVar4);
      puVar7 = puVar7 + 1;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_r5g6b5_dither @ 10017828 */

/* [binja] int16_t __thiscall sub_10017828(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_r5g6b5_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  ushort *extraout_EDX;
  ushort *puVar7;
  uint uVar8;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar5 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar8 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    puVar7 = extraout_EDX;
    do {
      fVar4 = *(float *)(iVar5 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar8 & 3) * 4);
      pfVar1 = (float *)(iVar6 + arg3);
      iVar2 = iVar6 + 4;
      iVar3 = iVar6 + 8;
      iVar6 = iVar6 + 0x10;
      *puVar7 = (ushort)(((int)ROUND(*pfVar1 * 31.0 + fVar4) << 6 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 63.0 + fVar4)) << 5) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 31.0 + fVar4);
      puVar7 = puVar7 + 1;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_x1r5g5b5_dither @ 10017929 */

/* [binja] int16_t __thiscall sub_10017929(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_x1r5g5b5_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  ushort *extraout_EDX;
  ushort *puVar7;
  uint uVar8;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar5 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar8 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    puVar7 = extraout_EDX;
    do {
      fVar4 = *(float *)(iVar5 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar8 & 3) * 4);
      pfVar1 = (float *)(iVar6 + arg3);
      iVar2 = iVar6 + 4;
      iVar3 = iVar6 + 8;
      iVar6 = iVar6 + 0x10;
      *puVar7 = (ushort)(((int)ROUND(*pfVar1 * 31.0 + fVar4) << 5 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 31.0 + fVar4)) << 5) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 31.0 + fVar4);
      puVar7 = puVar7 + 1;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_a1r5g5b5_dither @ 10017a2a */

/* [binja] int16_t __thiscall sub_10017a2a(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_a1r5g5b5_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  ushort *extraout_EDX;
  ushort *puVar8;
  uint uVar9;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar9 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar8 = extraout_EDX;
    do {
      fVar5 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar9 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar3 = iVar7 + 8;
      iVar4 = iVar7 + 0xc;
      iVar7 = iVar7 + 0x10;
      *puVar8 = (ushort)((((int)ROUND(fVar5 + *(float *)(iVar4 + arg3)) << 5 |
                          (int)ROUND(*pfVar1 * 31.0 + fVar5)) << 5 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 31.0 + fVar5)) << 5) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 31.0 + fVar5);
      puVar8 = puVar8 + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_a4r4g4b4_dither @ 10017b47 */

/* [binja] int16_t __thiscall sub_10017b47(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_a4r4g4b4_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  ushort *extraout_EDX;
  ushort *puVar8;
  uint uVar9;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar9 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar8 = extraout_EDX;
    do {
      fVar5 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar9 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar3 = iVar7 + 8;
      iVar4 = iVar7 + 0xc;
      iVar7 = iVar7 + 0x10;
      *puVar8 = (ushort)((((int)ROUND(*(float *)(iVar4 + arg3) * 15.0 + fVar5) << 4 |
                          (int)ROUND(*pfVar1 * 15.0 + fVar5)) << 4 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 15.0 + fVar5)) << 4) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 15.0 + fVar5);
      puVar8 = puVar8 + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_r3g3b2_dither @ 10017c6a */

/* [binja] int16_t __thiscall sub_10017c6a(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_r3g3b2_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  byte *extraout_EDX;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  byte local_20;
  
  uVar7 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar4 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    pbVar5 = extraout_EDX;
    do {
      fVar3 = *(float *)(iVar4 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar7 & 3) * 4);
      pfVar1 = (float *)(iVar6 + arg3);
      iVar2 = iVar6 + 8;
      local_20 = (byte)(int)ROUND(*(float *)(iVar6 + 4 + arg3) * 7.0 + fVar3);
      iVar6 = iVar6 + 0x10;
      *pbVar5 = ((char)(int)ROUND(*pfVar1 * 7.0 + fVar3) << 3 | local_20) << 2 |
                (byte)(int)ROUND(*(float *)(iVar2 + arg3) * 3.0 + fVar3);
      pbVar5 = pbVar5 + 1;
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_a8_dither @ 10017d68 */

/* [binja] int16_t __thiscall sub_10017d68(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_a8_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  int iVar1;
  uint uVar2;
  undefined1 *extraout_EDX;
  undefined1 *puVar3;
  int iVar4;
  
  iVar4 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar1 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar2 = 0;
  puVar3 = extraout_EDX;
  if (*(int *)((int)this + 0x1058) != 0) {
    do {
      *puVar3 = (char)(int)ROUND(*(float *)(iVar4 + 0xc + arg3) * 255.0 +
                                 *(float *)(iVar1 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 +
                                           (uVar2 & 3) * 4));
      puVar3 = puVar3 + 1;
      uVar2 = uVar2 + 1;
      iVar4 = iVar4 + 0x10;
    } while (uVar2 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_a8r3g3b2_dither @ 10017e11 */

/* [binja] int16_t __thiscall sub_10017e11(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_a8r3g3b2_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  ushort *extraout_EDX;
  ushort *puVar8;
  uint uVar9;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar9 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar8 = extraout_EDX;
    do {
      fVar5 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar9 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar3 = iVar7 + 8;
      iVar4 = iVar7 + 0xc;
      iVar7 = iVar7 + 0x10;
      *puVar8 = (ushort)((((int)ROUND(*(float *)(iVar4 + arg3) * 255.0 + fVar5) << 3 |
                          (int)ROUND(*pfVar1 * 7.0 + fVar5)) << 3 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 7.0 + fVar5)) << 2) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 3.0 + fVar5);
      puVar8 = puVar8 + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_write_row_l8_dither @ 10017f34 */

/* [binja] int16_t __thiscall sub_10017f34(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_write_row_l8_dither(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  ushort *extraout_EDX;
  ushort *puVar7;
  uint uVar8;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar5 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar8 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    puVar7 = extraout_EDX;
    do {
      fVar4 = *(float *)(iVar5 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar8 & 3) * 4);
      pfVar1 = (float *)(iVar6 + arg3);
      iVar2 = iVar6 + 4;
      iVar3 = iVar6 + 8;
      iVar6 = iVar6 + 0x10;
      *puVar7 = (ushort)(((int)ROUND(*pfVar1 * 15.0 + fVar4) << 4 |
                         (int)ROUND(*(float *)(iVar2 + arg3) * 15.0 + fVar4)) << 4) |
                (ushort)(int)ROUND(*(float *)(iVar3 + arg3) * 15.0 + fVar4);
      puVar7 = puVar7 + 1;
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_r5g6b5 @ 10018035 */

/* [binja] int16_t __thiscall sub_10018035(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_r5g6b5(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  uint *extraout_EDX;
  uint *puVar8;
  uint uVar9;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar9 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar8 = extraout_EDX;
    do {
      fVar5 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar9 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar3 = iVar7 + 8;
      iVar4 = iVar7 + 0xc;
      iVar7 = iVar7 + 0x10;
      *puVar8 = (((int)ROUND(*(float *)(iVar4 + arg3) * 3.0 + fVar5) << 10 |
                 (int)ROUND(*(float *)(iVar3 + arg3) * 1023.0 + fVar5)) << 10 |
                (int)ROUND(*(float *)(iVar2 + arg3) * 1023.0 + fVar5)) << 10 |
                (int)ROUND(*pfVar1 * 1023.0 + fVar5);
      puVar8 = puVar8 + 1;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_x1r5g5b5 @ 10018158 */

/* [binja] int16_t __thiscall sub_10018158(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_x1r5g5b5(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint *extraout_EDX;
  uint *puVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar3 = 0;
    puVar4 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar5 & 3) * 4);
      *puVar4 = (int)ROUND(*(float *)(iVar3 + 4 + arg3) * 65535.0 + fVar1) << 0x10 |
                (int)ROUND(*(float *)(iVar3 + arg3) * 65535.0 + fVar1);
      puVar4 = puVar4 + 1;
      uVar5 = uVar5 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar5 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a1r5g5b5 @ 10018228 */

/* [binja] int16_t __thiscall sub_10018228(void* arg1, int32_t arg2, int32_t arg3, float* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a1r5g5b5(void *this,void *arg1,int arg2,int arg3,float *arg4)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  ushort *extraout_EDX;
  ushort *puVar6;
  uint uVar7;
  uint local_14;
  int local_10;
  uint local_c;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar7 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    local_10 = 0;
    puVar6 = extraout_EDX;
    do {
      local_14 = 0;
      local_c = 0;
      pfVar5 = (float *)((int)this + 0x38);
      do {
        fVar4 = *(float *)(arg3 + 4) - pfVar5[-1];
        fVar3 = *(float *)(arg3 + 8) - *pfVar5;
        if ((*(float *)arg3 - pfVar5[-2]) * (*(float *)arg3 - pfVar5[-2]) +
            fVar4 * fVar4 + fVar3 * fVar3 < 3.4028235e+38) {
          local_14 = local_c;
        }
        local_c = local_c + 1;
        pfVar5 = pfVar5 + 4;
      } while (local_c < 0x100);
      iVar1 = local_10 + 0xc;
      local_10 = local_10 + 0x10;
      *puVar6 = (ushort)(byte)(int)ROUND(*(float *)(iVar1 + arg3) * 255.0 +
                                         *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4
                                                   + (uVar7 & 3) * 4)) << 8 | (ushort)local_14;
      puVar6 = puVar6 + 1;
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a4r4g4b4 @ 10018340 */

/* [binja] void* __thiscall sub_10018340(void* arg1, void* arg2, float arg3, void* arg4) */

void * __thiscall grim_pixel_convert_a8r8g8b8_to_a4r4g4b4(void *this,void *arg1,void *arg2,float arg3,void *arg4)

{
  void *pvVar1;
  void *extraout_ECX;
  undefined1 *puVar2;
  float fVar3;
  float *pfVar4;
  float *pfVar5;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (float)grim_convert_vertex_space(this,(float *)arg3);
    this = extraout_ECX;
  }
  puVar2 = (undefined1 *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * (int)arg2 +
           *(int *)((int)this + 0x18));
  arg1 = (void *)0x0;
  if (*(int *)((int)this + 0x1058) != 0) {
    pfVar4 = (float *)((int)arg3 + 8);
    do {
      fVar3 = 0.0;
      arg2 = (void *)0x7f7fffff;
      arg3 = 0.0;
      pfVar5 = (float *)((int)this + 0x38);
      do {
        pvVar1 = (void *)((pfVar4[-2] - pfVar5[-2]) * (pfVar4[-2] - pfVar5[-2]) +
                         (pfVar4[-1] - pfVar5[-1]) * (pfVar4[-1] - pfVar5[-1]) +
                         (*pfVar4 - *pfVar5) * (*pfVar4 - *pfVar5) +
                         (pfVar4[1] - pfVar5[1]) * (pfVar4[1] - pfVar5[1]));
        if ((float)pvVar1 < (float)arg2) {
          fVar3 = arg3;
          arg2 = pvVar1;
        }
        arg3 = (float)((int)arg3 + 1);
        pfVar5 = pfVar5 + 4;
      } while ((uint)arg3 < 0x100);
      *puVar2 = SUB41(fVar3,0);
      puVar2 = puVar2 + 1;
      arg3 = (float)((int)arg1 + 1);
      pfVar4 = pfVar4 + 4;
      arg1 = (void *)arg3;
    } while ((uint)arg3 < *(float **)((int)this + 0x1058));
  }
  return (void *)arg3;
}



/* grim_pixel_convert_a8r8g8b8_to_x4r4g4b4 @ 10018405 */

/* [binja] int16_t __thiscall sub_10018405(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_x4r4g4b4(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  undefined1 *extraout_EDX;
  undefined1 *puVar4;
  int iVar5;
  
  iVar5 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar1 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar3 = 0;
  puVar4 = extraout_EDX;
  if (*(int *)((int)this + 0x1058) != 0) {
    do {
      pfVar2 = (float *)(arg3 + iVar5);
      *puVar4 = (char)(int)ROUND(*(float *)(iVar1 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 +
                                           (uVar3 & 3) * 4) +
                                 (*pfVar2 * 0.2125 + pfVar2[1] * 0.7154 + pfVar2[2] * 0.0721) *
                                 255.0);
      puVar4 = puVar4 + 1;
      uVar3 = uVar3 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar3 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_r8g8b8 @ 100184ca */

/* [binja] int16_t __thiscall sub_100184ca(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_r8g8b8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  int iVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  ushort *extraout_EDX;
  ushort *puVar5;
  int iVar6;
  uint uVar7;
  
  uVar7 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar3 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar6 = 0;
    puVar5 = extraout_EDX;
    do {
      fVar2 = *(float *)(iVar3 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar7 & 3) * 4);
      pfVar4 = (float *)(arg3 + iVar6);
      iVar1 = iVar6 + 0xc;
      iVar6 = iVar6 + 0x10;
      *puVar5 = (ushort)(((int)ROUND(*(float *)(iVar1 + arg3) * 255.0 + fVar2) & 0xffU) << 8) |
                (ushort)(int)ROUND((*pfVar4 * 0.2125 + pfVar4[1] * 0.7154 + pfVar4[2] * 0.0721) *
                                   255.0 + fVar2);
      puVar5 = puVar5 + 1;
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a8r3g3b2 @ 100185c0 */

/* [binja] int16_t __thiscall sub_100185c0(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a8r3g3b2(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  byte *extraout_EDX;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  
  uVar6 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar5 = 0;
    pbVar4 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar6 & 3) * 4);
      pfVar3 = (float *)(arg3 + iVar5);
      *pbVar4 = (char)(int)ROUND(*(float *)(iVar5 + 0xc + arg3) * 15.0 + fVar1) << 4 |
                (byte)(int)ROUND((*pfVar3 * 0.2125 + pfVar3[1] * 0.7154 + pfVar3[2] * 0.0721) * 15.0
                                 + fVar1);
      pbVar4 = pbVar4 + 1;
      uVar6 = uVar6 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar6 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_r3g3b2 @ 100186ab */

/* [binja] int16_t __thiscall sub_100186ab(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_r3g3b2(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  undefined2 *extraout_EDX;
  undefined2 *puVar6;
  int iVar7;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar4 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar5 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    puVar6 = extraout_EDX;
    do {
      fVar3 = *(float *)(iVar4 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar5 & 3) * 4);
      pfVar1 = (float *)(iVar7 + arg3);
      iVar2 = iVar7 + 4;
      iVar7 = iVar7 + 0x10;
      *puVar6 = CONCAT11((char)(int)ROUND(*(float *)(iVar2 + arg3) * 128.0 + fVar3),
                         (char)(int)ROUND(*pfVar1 * 128.0 + fVar3));
      puVar6 = puVar6 + 1;
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a8 @ 10018780 */

/* [binja] int16_t __thiscall sub_10018780(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  ushort *extraout_EDX;
  ushort *puVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar5 = 0;
    puVar3 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar4 & 3) * 4);
      *puVar3 = (ushort)(((int)ROUND(*(float *)(iVar5 + 4 + arg3) * 16.0 + fVar1) & 0x1fU |
                         (int)ROUND(*(float *)(iVar5 + 0xc + arg3) * 63.0 + fVar1) << 5) << 5) |
                (ushort)(int)ROUND(*(float *)(iVar5 + arg3) * 16.0 + fVar1) & 0x1f;
      puVar3 = puVar3 + 1;
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar4 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_l8 @ 10018885 */

/* [binja] int16_t __thiscall sub_10018885(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_l8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  uint *extraout_EDX;
  uint *puVar7;
  int iVar8;
  undefined1 local_24;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar5 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar6 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar8 = 0;
    puVar7 = extraout_EDX;
    do {
      fVar4 = *(float *)(iVar5 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar6 & 3) * 4);
      pfVar1 = (float *)(iVar8 + arg3);
      iVar2 = iVar8 + 4;
      iVar3 = iVar8 + 0xc;
      iVar8 = iVar8 + 0x10;
      local_24 = (undefined1)(int)ROUND(*(float *)(iVar2 + arg3) * 128.0 + fVar4);
      *puVar7 = (uint)CONCAT11((char)(int)ROUND(*(float *)(iVar3 + arg3) * 255.0 + fVar4),local_24)
                << 8 | (int)ROUND(*pfVar1 * 128.0 + fVar4) & 0xffU;
      puVar7 = puVar7 + 1;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a8l8 @ 10018990 */

/* [binja] int16_t __thiscall sub_10018990(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a8l8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint *extraout_EDX;
  uint *puVar4;
  uint local_c;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  local_c = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar3 = 0;
    puVar4 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (local_c & 3) * 4);
      *puVar4 = (((int)ROUND(*(float *)(iVar3 + 8 + arg3) * 128.0 + fVar1) & 0xffU |
                 (int)ROUND(*(float *)(iVar3 + 0xc + arg3) * 128.0 + fVar1) << 8) << 8 |
                (int)ROUND(*(float *)(iVar3 + 4 + arg3) * 128.0 + fVar1) & 0xffU) << 8 |
                (int)ROUND(*(float *)(iVar3 + arg3) * 128.0 + fVar1) & 0xffU;
      puVar4 = puVar4 + 1;
      local_c = local_c + 1;
      iVar3 = iVar3 + 0x10;
    } while (local_c < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a4l4 @ 10018aca */

/* [binja] int16_t __thiscall sub_10018aca(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a4l4(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  uint *extraout_EDX;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar5 = 0;
    puVar3 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar4 & 3) * 4);
      *puVar3 = (int)ROUND(*(float *)(iVar5 + 4 + arg3) * 32768.0 + fVar1) << 0x10 |
                (int)ROUND(*(float *)(iVar5 + arg3) * 32768.0 + fVar1) & 0xffffU;
      puVar3 = puVar3 + 1;
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar4 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_p8 @ 10018ba0 */

/* [binja] int16_t __thiscall sub_10018ba0(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_p8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  int iVar3;
  uint *extraout_EDX;
  uint *puVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar3 = 0;
    puVar4 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar5 & 3) * 4);
      *puVar4 = ((int)ROUND(*(float *)(iVar3 + 4 + arg3) * 1024.0 + fVar1) & 0x7ffU |
                (int)ROUND(*(float *)(iVar3 + 8 + arg3) * 1024.0 + fVar1) << 0xb) << 10 |
                (int)ROUND(*(float *)(iVar3 + arg3) * 512.0 + fVar1) & 0x3ffU;
      puVar4 = puVar4 + 1;
      uVar5 = uVar5 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar5 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_a8p8 @ 10018caa */

/* [binja] int16_t __thiscall sub_10018caa(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_a8p8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint *extraout_EDX;
  uint *puVar5;
  uint local_c;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar3 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  local_c = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar4 = 0;
    puVar5 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar3 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (local_c & 3) * 4);
      fVar2 = *(float *)(iVar4 + 0xc + arg3);
      *puVar5 = (((int)ROUND(*(float *)(iVar4 + 8 + arg3) * 512.0 + fVar1) & 0x3ffU |
                 (int)ROUND(fVar2 + fVar2 + fVar1) << 10) << 10 |
                (int)ROUND(*(float *)(iVar4 + 4 + arg3) * 512.0 + fVar1) & 0x3ffU) << 10 |
                (int)ROUND(*(float *)(iVar4 + arg3) * 512.0 + fVar1) & 0x3ffU;
      puVar5 = puVar5 + 1;
      local_c = local_c + 1;
      iVar4 = iVar4 + 0x10;
    } while (local_c < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_v8u8 @ 10018de0 */

/* [binja] int16_t __thiscall sub_10018de0(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_v8u8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  undefined2 *extraout_EDX;
  undefined2 *puVar4;
  int iVar5;
  
  iVar5 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar1 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar3 = 0;
  puVar4 = extraout_EDX;
  if (*(int *)((int)this + 0x1058) != 0) {
    do {
      pfVar2 = (float *)(arg3 + iVar5);
      *puVar4 = (short)(int)ROUND(*(float *)(iVar1 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 +
                                            (uVar3 & 3) * 4) +
                                  (*pfVar2 * 0.2125 + pfVar2[1] * 0.7154 + pfVar2[2] * 0.0721) *
                                  65535.0);
      puVar4 = puVar4 + 1;
      uVar3 = uVar3 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar3 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_l6v5u5 @ 10018ea7 */

/* [binja] int16_t __thiscall sub_10018ea7(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_l6v5u5(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  undefined2 *extraout_EDX;
  undefined2 *puVar4;
  int iVar5;
  
  iVar5 = 0;
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar1 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar3 = 0;
  puVar4 = extraout_EDX;
  if (*(int *)((int)this + 0x1058) != 0) {
    do {
      pfVar2 = (float *)(arg3 + iVar5);
      *puVar4 = (short)(int)ROUND(*(float *)(iVar1 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 +
                                            (uVar3 & 3) * 4) +
                                  (*pfVar2 * 0.2125 + pfVar2[1] * 0.7154 + pfVar2[2] * 0.0721) *
                                  65535.0);
      puVar4 = puVar4 + 1;
      uVar3 = uVar3 + 1;
      iVar5 = iVar5 + 0x10;
    } while (uVar3 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_x8l8v8u8 @ 10018f6e */

/* [binja] int16_t __thiscall sub_10018f6e(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_x8l8v8u8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  uint *extraout_EDX;
  uint *puVar5;
  uint uVar6;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar6 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar4 = 0;
    puVar5 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar6 & 3) * 4);
      pfVar3 = (float *)(arg3 + iVar4);
      *puVar5 = (int)ROUND(*(float *)(iVar4 + 0xc + arg3) * 65535.0 + fVar1) << 0x10 |
                (int)ROUND((*pfVar3 * 0.2125 + pfVar3[1] * 0.7154 + pfVar3[2] * 0.0721) * 65535.0 +
                           fVar1);
      puVar5 = puVar5 + 1;
      uVar6 = uVar6 + 1;
      iVar4 = iVar4 + 0x10;
    } while (uVar6 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_q8w8v8u8 @ 1001905c */

/* [binja] int16_t __thiscall sub_1001905c(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_q8w8v8u8(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined2 *extraout_EDX;
  undefined2 *puVar4;
  uint uVar5;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  iVar2 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  uVar5 = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar3 = 0;
    puVar4 = extraout_EDX;
    do {
      fVar1 = *(float *)(iVar2 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (uVar5 & 3) * 4);
      *puVar4 = (short)(int)ROUND(*(float *)(iVar3 + 8 + arg3) * 65535.0 + fVar1);
      puVar4[1] = (short)(int)ROUND(*(float *)(iVar3 + 4 + arg3) * 65535.0 + fVar1);
      puVar4[2] = (short)(int)ROUND(*(float *)(iVar3 + arg3) * 65535.0 + fVar1);
      puVar4 = puVar4 + 3;
      uVar5 = uVar5 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar5 < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_pixel_convert_a8r8g8b8_to_v16u16 @ 1001914b */

/* [binja] int16_t __thiscall sub_1001914b(void* arg1, int32_t arg2, int32_t arg3, void* arg4) */

short __thiscall grim_pixel_convert_a8r8g8b8_to_v16u16(void *this,void *arg1,int arg2,int arg3,void *arg4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  uint local_c;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    arg3 = (int)grim_convert_vertex_space(this,(float *)arg3);
  }
  puVar8 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  iVar6 = *(int *)((int)this + 0x2c);
  fpu_set_round_trunc();
  local_c = 0;
  if (*(int *)((int)this + 0x1058) != 0) {
    iVar7 = 0;
    do {
      fVar4 = *(float *)(iVar6 + ((arg2 & 3U) + ((uint)arg1 & 3) * 8) * 4 + (local_c & 3) * 4);
      uVar1 = (uint)ROUND(*(float *)(iVar7 + arg3) * 65535.0 + fVar4);
      uVar2 = (uint)ROUND(*(float *)(iVar7 + 4 + arg3) * 65535.0 + fVar4);
      uVar3 = (uint)ROUND(*(float *)(iVar7 + 8 + arg3) * 65535.0 + fVar4);
      fVar5 = *(float *)(iVar7 + 0xc + arg3);
      *puVar8 = uVar2 << 0x10 | uVar3;
      puVar8[1] = (((int)ROUND(fVar5 * 65535.0 + fVar4) << 0x10 | uVar1) >> 0x10 |
                  (int)uVar2 >> 0x1f) << 0x10 | (uVar1 << 0x10 | uVar2) >> 0x10 | (int)uVar3 >> 0x1f
      ;
      puVar8 = puVar8 + 2;
      local_c = local_c + 1;
      iVar7 = iVar7 + 0x10;
    } while (local_c < *(uint *)((int)this + 0x1058));
  }
  return (short)grim_fpu_control_word;
}



/* grim_colorkey_apply_a8r8g8b8 @ 100192a7 */

/* [binja] void* __thiscall sub_100192a7(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

void * __thiscall grim_colorkey_apply_a8r8g8b8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  byte *extraout_EAX;
  byte *pbVar2;
  
  pbVar1 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar2 = pbVar1 + *(int *)((int)this + 0x1064);
  for (; pbVar1 < pbVar2; pbVar1 = pbVar1 + 3) {
    *(float *)arg3 = (float)pbVar1[2] * 0.003921569;
    *(float *)(arg3 + 4) = (float)pbVar1[1] * 0.003921569;
    *(float *)(arg3 + 8) = (float)*pbVar1 * 0.003921569;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar1 = extraout_EAX;
  }
  return pbVar1;
}



/* grim_colorkey_apply_x8r8g8b8 @ 10019333 */

/* WARNING: Removing unreachable block (ram,0x10019396) */
/* [binja] int32_t* __thiscall sub_10019333(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int * __thiscall grim_colorkey_apply_x8r8g8b8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint *puVar2;
  uint *extraout_EAX;
  
  puVar2 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)*(byte *)((int)puVar2 + 2) * 0.003921569;
    *(float *)(arg3 + 4) = (float)*(byte *)((int)puVar2 + 1) * 0.003921569;
    *(float *)(arg3 + 8) = (float)(*puVar2 & 0xff) * 0.003921569;
    *(float *)(arg3 + 0xc) = (float)*(byte *)((int)puVar2 + 3) * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (int *)puVar2;
}



/* grim_colorkey_apply_r5g6b5 @ 100193d9 */

/* WARNING: Removing unreachable block (ram,0x1001943c) */
/* [binja] void* __thiscall sub_100193d9(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

void * __thiscall grim_colorkey_apply_r5g6b5(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint *puVar2;
  uint *extraout_EAX;
  
  puVar2 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)*(byte *)((int)puVar2 + 2) * 0.003921569;
    *(float *)(arg3 + 4) = (float)*(byte *)((int)puVar2 + 1) * 0.003921569;
    *(float *)(arg3 + 8) = (float)(*puVar2 & 0xff) * 0.003921569;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return puVar2;
}



/* grim_colorkey_apply_x1r5g5b5 @ 10019475 */

/* [binja] int16_t* __thiscall sub_10019475(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

short * __thiscall grim_colorkey_apply_x1r5g5b5(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort *extraout_EAX;
  
  puVar2 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)(*puVar2 >> 0xb) * 0.032258064;
    *(float *)(arg3 + 4) = (float)((*puVar2 & 0x7e0) >> 5) * 0.015873017;
    *(float *)(arg3 + 8) = (float)((byte)*puVar2 & 0x1f) * 0.032258064;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (short *)puVar2;
}



/* grim_colorkey_apply_a1r5g5b5 @ 1001951a */

/* [binja] int16_t* __thiscall sub_1001951a(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

short * __thiscall grim_colorkey_apply_a1r5g5b5(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort *extraout_EAX;
  
  puVar2 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)((*puVar2 & 0x7c00) >> 10) * 0.032258064;
    *(float *)(arg3 + 4) = (float)((*puVar2 & 0x3e0) >> 5) * 0.032258064;
    *(float *)(arg3 + 8) = (float)((byte)*puVar2 & 0x1f) * 0.032258064;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (short *)puVar2;
}



/* grim_colorkey_apply_a4r4g4b4 @ 100195bc */

/* [binja] int16_t* __thiscall sub_100195bc(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

short * __thiscall grim_colorkey_apply_a4r4g4b4(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort *extraout_EAX;
  
  puVar2 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)((*puVar2 & 0x7c00) >> 10) * 0.032258064;
    *(float *)(arg3 + 4) = (float)((*puVar2 & 0x3e0) >> 5) * 0.032258064;
    *(float *)(arg3 + 8) = (float)((byte)*puVar2 & 0x1f) * 0.032258064;
    *(float *)(arg3 + 0xc) = (float)(*puVar2 >> 0xf);
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (short *)puVar2;
}



/* grim_colorkey_apply_x4r4g4b4 @ 1001966c */

/* [binja] void* __thiscall sub_1001966c(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

void * __thiscall grim_colorkey_apply_x4r4g4b4(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort *extraout_EAX;
  
  puVar2 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)(*(byte *)((int)puVar2 + 1) & 0xf) * 0.06666667;
    *(float *)(arg3 + 4) = (float)(byte)((byte)*puVar2 >> 4) * 0.06666667;
    *(float *)(arg3 + 8) = (float)((byte)*puVar2 & 0xf) * 0.06666667;
    *(float *)(arg3 + 0xc) = (float)(*puVar2 >> 0xc) * 0.06666667;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return puVar2;
}



/* grim_colorkey_apply_r8g8b8 @ 1001971b */

/* WARNING: Removing unreachable block (ram,0x10019782) */
/* WARNING: Removing unreachable block (ram,0x10019767) */
/* WARNING: Removing unreachable block (ram,0x1001979e) */
/* WARNING: Removing unreachable block (ram,0x100197b8) */
/* [binja] int32_t* __thiscall sub_1001971b(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int * __thiscall grim_colorkey_apply_r8g8b8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint *puVar2;
  uint *extraout_EAX;
  
  puVar2 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)(*puVar2 & 0x3ff) * 0.0009775171;
    *(float *)(arg3 + 4) = (float)(*puVar2 >> 10 & 0x3ff) * 0.0009775171;
    *(float *)(arg3 + 8) = (float)(*puVar2 >> 0x14 & 0x3ff) * 0.0009775171;
    *(float *)(arg3 + 0xc) = (float)(*puVar2 >> 0x1e) * 0.33333334;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (int *)puVar2;
}



/* grim_colorkey_apply_a8r3g3b2 @ 100197f1 */

/* WARNING: Removing unreachable block (ram,0x10019837) */
/* [binja] int32_t* __thiscall sub_100197f1(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int * __thiscall grim_colorkey_apply_a8r3g3b2(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint *puVar2;
  uint *extraout_EAX;
  
  puVar2 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar2 + *(int *)((int)this + 0x1058);
  for (; puVar2 < puVar1; puVar2 = puVar2 + 1) {
    *(float *)arg3 = (float)(*puVar2 & 0xffff) * 1.5259022e-05;
    *(float *)(arg3 + 4) = (float)*(ushort *)((int)puVar2 + 2) * 1.5259022e-05;
    *(float *)(arg3 + 8) = 1.0;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (int *)puVar2;
}



/* grim_colorkey_apply_r3g3b2 @ 10019883 */

/* [binja] char* __thiscall sub_10019883(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_r3g3b2(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  byte *extraout_EAX;
  byte *pbVar2;
  
  pbVar1 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar2 = pbVar1 + *(int *)((int)this + 0x1058);
  for (; pbVar1 < pbVar2; pbVar1 = pbVar1 + 1) {
    *(float *)arg3 = (float)(*pbVar1 >> 5) * 0.14285715;
    *(float *)(arg3 + 4) = (float)(*pbVar1 >> 2 & 7) * 0.14285715;
    *(float *)(arg3 + 8) = (float)(*pbVar1 & 3) * 0.33333334;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar1 = extraout_EAX;
  }
  return (char *)pbVar1;
}



/* grim_colorkey_apply_a8 @ 10019925 */

/* [binja] char* __thiscall sub_10019925(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_a8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  byte *extraout_EAX;
  byte *pbVar2;
  
  pbVar1 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar2 = pbVar1 + *(int *)((int)this + 0x1058);
  for (; pbVar1 < pbVar2; pbVar1 = pbVar1 + 1) {
    *(undefined4 *)arg3 = 0;
    *(undefined4 *)(arg3 + 4) = 0;
    *(undefined4 *)(arg3 + 8) = 0;
    *(float *)(arg3 + 0xc) = (float)*pbVar1 * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar1 = extraout_EAX;
  }
  return (char *)pbVar1;
}



/* grim_colorkey_apply_l8 @ 10019997 */

/* [binja] char* __thiscall sub_10019997(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_l8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *extraout_EAX;
  
  pbVar2 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar1 = pbVar2 + *(int *)((int)this + 0x1058) * 2;
  for (; pbVar2 < pbVar1; pbVar2 = pbVar2 + 2) {
    *(float *)arg3 = (float)(*pbVar2 >> 5) * 0.14285715;
    *(float *)(arg3 + 4) = (float)(*pbVar2 >> 2 & 7) * 0.14285715;
    *(float *)(arg3 + 8) = (float)(*pbVar2 & 3) * 0.33333334;
    *(float *)(arg3 + 0xc) = (float)pbVar2[1] * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar2 = extraout_EAX;
  }
  return (char *)pbVar2;
}



/* grim_colorkey_apply_a8l8 @ 10019a49 */

/* [binja] void* __thiscall sub_10019a49(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

void * __thiscall grim_colorkey_apply_a8l8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *extraout_EAX;
  
  pbVar2 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar1 = pbVar2 + *(int *)((int)this + 0x1058) * 2;
  for (; pbVar2 < pbVar1; pbVar2 = pbVar2 + 2) {
    *(float *)arg3 = (float)(pbVar2[1] & 0xf) * 0.06666667;
    *(float *)(arg3 + 4) = (float)(*pbVar2 >> 4) * 0.06666667;
    *(float *)(arg3 + 8) = (float)(*pbVar2 & 0xf) * 0.06666667;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar2 = extraout_EAX;
  }
  return pbVar2;
}



/* grim_colorkey_apply_a4l4 @ 10019ae8 */

/* [binja] char* __thiscall sub_10019ae8(void* arg1, void* arg2, int32_t arg3, uint32_t arg4) */

char * __thiscall grim_colorkey_apply_a4l4(void *this,void *arg1,void *arg2,int arg3,uint arg4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *extraout_EAX;
  undefined4 *puVar3;
  
  pbVar2 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 +
                    *(int *)((int)this + 0x1054) * (int)arg2 + *(int *)((int)this + 0x18));
  pbVar1 = pbVar2 + *(int *)((int)this + 0x1058) * 2;
  for (; pbVar2 < pbVar1; pbVar2 = pbVar2 + 2) {
    puVar3 = (undefined4 *)((*pbVar2 + 3) * 0x10 + (int)this);
    *(undefined4 *)arg3 = *puVar3;
    *(undefined4 *)(arg3 + 4) = puVar3[1];
    *(undefined4 *)(arg3 + 8) = puVar3[2];
    *(undefined4 *)(arg3 + 0xc) = puVar3[3];
    *(float *)(arg3 + 0xc) = (float)pbVar2[1] * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar2 = extraout_EAX;
  }
  return (char *)pbVar2;
}



/* grim_colorkey_apply_p8 @ 10019bd3 */

/* [binja] char* __thiscall sub_10019bd3(void* arg1, int32_t arg2, int32_t arg3, uint32_t arg4) */

char * __thiscall grim_colorkey_apply_p8(void *this,void *arg1,int arg2,int arg3,uint arg4)

{
  float fVar1;
  byte *pbVar2;
  byte *extraout_EAX;
  byte *pbVar3;
  
  pbVar2 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar3 = pbVar2 + *(int *)((int)this + 0x1058);
  for (; pbVar2 < pbVar3; pbVar2 = pbVar2 + 1) {
    fVar1 = (float)*pbVar2 * 0.003921569;
    *(float *)(arg3 + 8) = fVar1;
    *(float *)(arg3 + 4) = fVar1;
    *(float *)arg3 = fVar1;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar2 = extraout_EAX;
  }
  return (char *)pbVar2;
}



/* grim_colorkey_apply_a8p8 @ 10019c41 */

/* [binja] char* __thiscall sub_10019c41(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_a8p8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  byte *pbVar1;
  float fVar2;
  byte *pbVar3;
  byte *extraout_EAX;
  
  pbVar3 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar1 = pbVar3 + *(int *)((int)this + 0x1058) * 2;
  for (; pbVar3 < pbVar1; pbVar3 = pbVar3 + 2) {
    fVar2 = (float)*pbVar3 * 0.003921569;
    *(float *)(arg3 + 8) = fVar2;
    *(float *)(arg3 + 4) = fVar2;
    *(float *)arg3 = fVar2;
    *(float *)(arg3 + 0xc) = (float)pbVar3[1] * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar3 = extraout_EAX;
  }
  return (char *)pbVar3;
}



/* grim_colorkey_apply_v8u8 @ 10019cca */

/* [binja] char* __thiscall sub_10019cca(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_v8u8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  float fVar1;
  byte *pbVar2;
  byte *extraout_EAX;
  byte *pbVar3;
  
  pbVar2 = (byte *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pbVar3 = pbVar2 + *(int *)((int)this + 0x1058);
  for (; pbVar2 < pbVar3; pbVar2 = pbVar2 + 1) {
    fVar1 = (float)(*pbVar2 & 0xf) * 0.06666667;
    *(float *)(arg3 + 8) = fVar1;
    *(float *)(arg3 + 4) = fVar1;
    *(float *)arg3 = fVar1;
    *(float *)(arg3 + 0xc) = (float)(*pbVar2 >> 4) * 0.06666667;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pbVar2 = extraout_EAX;
  }
  return (char *)pbVar2;
}



/* grim_colorkey_apply_l6v5u5 @ 10019d53 */

/* [binja] char* __thiscall sub_10019d53(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_l6v5u5(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  char *pcVar1;
  char *pcVar2;
  char *extraout_EAX;
  
  pcVar2 = (char *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pcVar1 = pcVar2 + *(int *)((int)this + 0x1058) * 2;
  for (; pcVar2 < pcVar1; pcVar2 = pcVar2 + 2) {
    *(float *)arg3 = (float)(int)*pcVar2 * 0.0078125;
    *(float *)(arg3 + 4) = (float)(int)pcVar2[1] * 0.0078125;
    *(float *)(arg3 + 8) = 0.0;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pcVar2 = extraout_EAX;
  }
  return pcVar2;
}



/* grim_colorkey_apply_x8l8v8u8 @ 10019dd5 */

/* [binja] char* __thiscall sub_10019dd5(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_x8l8v8u8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *extraout_EAX;
  
  puVar3 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058);
  for (; puVar3 < puVar1; puVar3 = puVar3 + 1) {
    uVar2 = *puVar3;
    *(float *)arg3 = (float)(int)((char)((char)*puVar3 << 3) >> 3) * 0.0625;
    *(float *)(arg3 + 4) = (float)(int)((char)((char)(uVar2 >> 5) << 3) >> 3) * 0.0625;
    *(float *)(arg3 + 8) = 0.0;
    *(float *)(arg3 + 0xc) = (float)(*puVar3 >> 10) * 0.015873017;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar3 = extraout_EAX;
  }
  return (char *)puVar3;
}



/* grim_colorkey_apply_q8w8v8u8 @ 10019e86 */

/* [binja] char* __thiscall sub_10019e86(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_q8w8v8u8(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  char *pcVar1;
  char *pcVar2;
  char *extraout_EAX;
  
  pcVar2 = (char *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pcVar1 = pcVar2 + *(int *)((int)this + 0x1058) * 4;
  for (; pcVar2 < pcVar1; pcVar2 = pcVar2 + 4) {
    *(float *)arg3 = (float)(int)*pcVar2 * 0.0078125;
    *(float *)(arg3 + 4) = (float)(int)pcVar2[1] * 0.0078125;
    *(float *)(arg3 + 8) = 0.0;
    *(float *)(arg3 + 0xc) = (float)(byte)pcVar2[2] * 0.003921569;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pcVar2 = extraout_EAX;
  }
  return pcVar2;
}



/* grim_colorkey_apply_v16u16 @ 10019f17 */

/* [binja] char* __thiscall sub_10019f17(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

char * __thiscall grim_colorkey_apply_v16u16(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  char *pcVar1;
  char *pcVar2;
  char *extraout_EAX;
  
  pcVar2 = (char *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  pcVar1 = pcVar2 + *(int *)((int)this + 0x1058) * 4;
  for (; pcVar2 < pcVar1; pcVar2 = pcVar2 + 4) {
    *(float *)arg3 = (float)(int)*pcVar2 * 0.0078125;
    *(float *)(arg3 + 4) = (float)(int)pcVar2[1] * 0.0078125;
    *(float *)(arg3 + 8) = (float)(int)pcVar2[2] * 0.0078125;
    *(float *)(arg3 + 0xc) = (float)(int)pcVar2[3] * 0.0078125;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    pcVar2 = extraout_EAX;
  }
  return pcVar2;
}



/* grim_pixel_format_read_row_dispatch @ 10019fae */

/* [binja] int16_t* __thiscall sub_10019fae(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

short * __thiscall grim_pixel_format_read_row_dispatch(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  short *psVar1;
  short *psVar2;
  short *extraout_EAX;
  
  psVar2 = (short *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2
                    + *(int *)((int)this + 0x18));
  psVar1 = psVar2 + *(int *)((int)this + 0x1058) * 2;
  for (; psVar2 < psVar1; psVar2 = psVar2 + 2) {
    *(float *)arg3 = (float)(int)*psVar2 * 3.0517578e-05;
    *(float *)(arg3 + 4) = (float)(int)psVar2[1] * 3.0517578e-05;
    *(float *)(arg3 + 8) = 0.0;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    psVar2 = extraout_EAX;
  }
  return psVar2;
}



/* grim_pixel_read_row_r10g10b10 @ 1001a031 */

/* [binja] int32_t* __thiscall sub_1001a031(void* arg1, uint32_t arg2, int32_t arg3, int32_t arg4)
    */

int * __thiscall grim_pixel_read_row_r10g10b10(void *this,void *arg1,uint arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint *extraout_EAX;
  
  puVar3 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058);
  for (; puVar3 < puVar1; puVar3 = puVar3 + 1) {
    uVar2 = *puVar3;
    *(float *)arg3 = (float)(int)((short)((short)*puVar3 << 6) >> 6) * 0.001953125;
    *(float *)(arg3 + 4) = (float)(int)((short)((short)(uVar2 >> 10) << 5) >> 5) * 0.0009765625;
    *(float *)(arg3 + 8) = (float)(int)(short)((int)uVar2 >> 0x15) * 0.0009765625;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar3 = extraout_EAX;
  }
  return (int *)puVar3;
}



/* grim_pixel_read_row_a2r10g10b10 @ 1001a0eb */

/* WARNING: Removing unreachable block (ram,0x1001a185) */
/* [binja] int32_t* __thiscall sub_1001a0eb(void* arg1, uint32_t arg2, int32_t arg3, int32_t arg4)
    */

int * __thiscall grim_pixel_read_row_a2r10g10b10(void *this,void *arg1,uint arg2,int arg3,int arg4)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint *extraout_EAX;
  
  puVar3 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058);
  for (; puVar3 < puVar1; puVar3 = puVar3 + 1) {
    uVar2 = *puVar3;
    *(float *)arg3 = (float)(int)((short)((short)*puVar3 << 6) >> 6) * 0.001953125;
    *(float *)(arg3 + 4) = (float)(int)((short)((short)(uVar2 >> 10) << 6) >> 6) * 0.001953125;
    *(float *)(arg3 + 8) = (float)(int)((short)((ushort)(uVar2 >> 0x14) << 6) >> 6) * 0.001953125;
    *(float *)(arg3 + 0xc) = (float)(*puVar3 >> 0x1e) * 0.33333334;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar3 = extraout_EAX;
  }
  return (int *)puVar3;
}



/* grim_pixel_read_row_l16 @ 1001a1be */

/* [binja] int16_t* __thiscall sub_1001a1be(void* arg1, int32_t arg2, int32_t arg3, uint32_t arg4)
    */

short * __thiscall grim_pixel_read_row_l16(void *this,void *arg1,int arg2,int arg3,uint arg4)

{
  ushort *puVar1;
  float fVar2;
  ushort *puVar3;
  ushort *extraout_EAX;
  
  puVar3 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058);
  for (; puVar3 < puVar1; puVar3 = puVar3 + 1) {
    fVar2 = (float)*puVar3 * 1.5259022e-05;
    *(float *)(arg3 + 8) = fVar2;
    *(float *)(arg3 + 4) = fVar2;
    *(float *)arg3 = fVar2;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar3 = extraout_EAX;
  }
  return (short *)puVar3;
}



/* grim_pixel_read_row_g16r16 @ 1001a22e */

/* WARNING: Removing unreachable block (ram,0x1001a274) */
/* [binja] int32_t* __thiscall sub_1001a22e(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int * __thiscall grim_pixel_read_row_g16r16(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  uint *puVar1;
  float fVar2;
  uint *puVar3;
  uint *extraout_EAX;
  
  puVar3 = (uint *)(*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058);
  for (; puVar3 < puVar1; puVar3 = puVar3 + 1) {
    fVar2 = (float)(*puVar3 & 0xffff) * 1.5259022e-05;
    *(float *)(arg3 + 8) = fVar2;
    *(float *)(arg3 + 4) = fVar2;
    *(float *)arg3 = fVar2;
    *(float *)(arg3 + 0xc) = (float)*(ushort *)((int)puVar3 + 2) * 1.5259022e-05;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar3 = extraout_EAX;
  }
  return (int *)puVar3;
}



/* grim_pixel_read_row_r16g16b16 @ 1001a2bc */

/* [binja] void* __thiscall sub_1001a2bc(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

void * __thiscall grim_pixel_read_row_r16g16b16(void *this,void *arg1,int arg2,int arg3,int arg4)

{
  ushort *puVar1;
  ushort *extraout_EAX;
  ushort *puVar2;
  
  puVar1 = (ushort *)
           (*(int *)((int)this + 0x1050) * (int)arg1 + *(int *)((int)this + 0x1054) * arg2 +
           *(int *)((int)this + 0x18));
  puVar2 = (ushort *)(*(int *)((int)this + 0x1064) + (int)puVar1);
  for (; puVar1 < puVar2; puVar1 = puVar1 + 3) {
    *(float *)arg3 = (float)puVar1[2] * 1.5259022e-05;
    *(float *)(arg3 + 4) = (float)puVar1[1] * 1.5259022e-05;
    *(float *)(arg3 + 8) = (float)*puVar1 * 1.5259022e-05;
    *(float *)(arg3 + 0xc) = 1.0;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar1 = extraout_EAX;
  }
  return puVar1;
}



/* grim_pixel_read_row_a16r16g16b16 @ 1001a348 */

/* WARNING: Removing unreachable block (ram,0x1001a3c7) */
/* WARNING: Removing unreachable block (ram,0x1001a3a5) */
/* WARNING: Removing unreachable block (ram,0x1001a3e0) */
/* [binja] uint32_t __thiscall sub_1001a348(uint32_t arg1, uint32_t arg2, int32_t arg3, uint32_t
   arg4) */

uint __thiscall grim_pixel_read_row_a16r16g16b16(void *this,uint arg1,uint arg2,int arg3,uint arg4)

{
  uint *puVar1;
  uint *puVar2;
  uint *extraout_EAX;
  uint *puVar3;
  ulonglong uVar4;
  
  puVar3 = (uint *)(*(int *)((int)this + 0x1050) * arg1 + *(int *)((int)this + 0x1054) * arg2 +
                   *(int *)((int)this + 0x18));
  puVar1 = puVar3 + *(int *)((int)this + 0x1058) * 2;
  puVar2 = puVar1;
  for (; puVar3 < puVar1; puVar3 = puVar3 + 2) {
    uVar4 = __aullshr(0x20,puVar3[1]);
    *(float *)arg3 = (float)((uint)uVar4 & 0xffff) * 1.5259022e-05;
    *(float *)(arg3 + 4) = (float)(*puVar3 >> 0x10) * 1.5259022e-05;
    *(float *)(arg3 + 8) = (float)(*puVar3 & 0xffff) * 1.5259022e-05;
    puVar2 = (uint *)(uint)*(ushort *)((int)puVar3 + 6);
    *(float *)(arg3 + 0xc) = (float)(int)puVar2 * 1.5259022e-05;
    arg3 = (int)(arg3 + 0x10);
  }
  if (*(int *)((int)this + 0x10) != 0) {
    grim_apply_color_key(this,(float *)(arg3 + *(int *)((int)this + 0x1058) * -4 * 4));
    puVar2 = extraout_EAX;
  }
  return (uint)puVar2;
}



/* grim_pixel_format_ctor_r8g8b8 @ 1001a428 */

/* pixel format ctor for D3DFMT_R8G8B8 */

void * __thiscall grim_pixel_format_ctor_r8g8b8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x18,1);
  *(undefined ***)this = &grim_vtable_pixel_r8g8b8;
  return this;
}



/* grim_pixel_format_init_yuv @ 1001a444 */

/* initializes packed YUV (UYVY/YUY2) cache state and allocates RGB float cache */

void * grim_pixel_format_init_yuv(void *this,uint *desc)

{
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  undefined4 *this_00;
  int iVar4;
  int unaff_EBP;
  
  seh_prolog();
  *(undefined4 **)(unaff_EBP + -0x14) = this_00;
  grim_pixel_format_init(this_00,*(uint **)(unaff_EBP + 8),0,1);
  uVar1 = this_00[0x40c];
  uVar2 = this_00[0x40e] + 1 & 0xfffffffe;
  iVar4 = uVar2 - (uVar1 & 0xfffffffe);
  this_00[0x41e] = uVar2;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *this_00 = &grim_vtable_pixel_yuv;
  this_00[0x41c] = uVar1 & 0xfffffffe;
  this_00[0x41d] = 0;
  this_00[0x420] = 0;
  this_00[0x41f] = 0;
  this_00[0x421] = 0;
  this_00[0x422] = iVar4;
  this_00[0x423] = 0;
  this_00[0x424] = 1;
  pvVar3 = operator_new(iVar4 * 0x10);
  *(void **)(unaff_EBP + -0x10) = pvVar3;
  *(undefined1 *)(unaff_EBP + -4) = 1;
  if (pvVar3 == (void *)0x0) {
    iVar4 = 0;
  }
  else {
    _vector_constructor_iterator_(pvVar3,0x10,iVar4,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
    iVar4 = *(int *)(unaff_EBP + -0x10);
  }
  this_00[0x41b] = iVar4;
  if (iVar4 == 0) {
    this_00[0x424] = 0;
  }
  if (*(int *)(*(int *)(unaff_EBP + 8) + 4) == 0x59565955) {
    this_00[0x425] = 8;
    this_00[0x426] = 0;
  }
  else {
    this_00[0x425] = 0;
    this_00[0x426] = 8;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return this_00;
}



/* grim_pixel_format_ctor_a8r8g8b8 @ 1001a53c */

/* pixel format ctor for D3DFMT_A8R8G8B8 */

void * __thiscall grim_pixel_format_ctor_a8r8g8b8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,1);
  *(undefined ***)this = &grim_vtable_pixel_a8r8g8b8;
  return this;
}



/* grim_pixel_format_ctor_x8r8g8b8 @ 1001a558 */

/* pixel format ctor for D3DFMT_X8R8G8B8 */

void * __thiscall grim_pixel_format_ctor_x8r8g8b8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,1);
  *(undefined ***)this = &grim_vtable_pixel_x8r8g8b8;
  return this;
}



/* grim_pixel_format_ctor_r5g6b5 @ 1001a579 */

/* pixel format ctor for D3DFMT_R5G6B5 */

void * __thiscall grim_pixel_format_ctor_r5g6b5(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &grim_vtable_pixel_r5g6b5;
  return this;
}



/* grim_pixel_format_flush_yuv_cache @ 1001a595 */

/* flushes cached YUV<->RGB conversions back into packed 16-bit storage */

int __fastcall grim_pixel_format_flush_yuv_cache(void *this)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *local_10;
  uint local_c;
  
  if ((*(int *)((int)this + 0x108c) != 0) && (*(int *)((int)this + 0x1090) != 0)) {
    local_c = *(uint *)((int)this + 0x1070);
    local_10 = (ushort *)
               (*(int *)((int)this + 0x1080) * *(int *)((int)this + 0x1054) +
                *(int *)((int)this + 0x1074) * *(int *)((int)this + 0x1050) + local_c * 2 +
               *(int *)((int)this + 0x18));
    pfVar1 = *(float **)((int)this + 0x106c);
    if (local_c < *(uint *)((int)this + 0x1078)) {
      do {
        iVar2 = (int)ROUND(pfVar1[2] * 24.966 + pfVar1[1] * 128.553 + *pfVar1 * 65.481 + 0.5) + 0x10
        ;
        iVar4 = (int)ROUND(pfVar1[5] * 128.553 + pfVar1[6] * 24.966 + pfVar1[4] * 65.481 + 0.5) +
                0x10;
        iVar3 = (int)ROUND(((pfVar1[2] * 112.0 - pfVar1[1] * 74.203) - *pfVar1 * 37.797) + 0.5) +
                0x80;
        iVar5 = (int)ROUND((*pfVar1 * 112.0 - (pfVar1[2] * 18.214 + pfVar1[1] * 93.786)) + 0.5) +
                0x80;
        if (iVar2 < 0) {
          iVar2 = 0;
        }
        else if (0xff < iVar2) {
          iVar2 = 0xff;
        }
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        else if (0xff < iVar4) {
          iVar4 = 0xff;
        }
        if (iVar3 < 0) {
          iVar3 = 0;
        }
        else if (0xff < iVar3) {
          iVar3 = 0xff;
        }
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        else if (0xff < iVar5) {
          iVar5 = 0xff;
        }
        local_c = local_c + 2;
        pfVar1 = pfVar1 + 8;
        *local_10 = (ushort)(iVar2 << ((byte)*(undefined4 *)((int)this + 0x1094) & 0x1f)) |
                    (ushort)(iVar3 << ((byte)*(undefined4 *)((int)this + 0x1098) & 0x1f));
        local_10[1] = (ushort)(iVar4 << ((byte)*(undefined4 *)((int)this + 0x1094) & 0x1f)) |
                      (ushort)(iVar5 << ((byte)*(undefined4 *)((int)this + 0x1098) & 0x1f));
        local_10 = local_10 + 2;
      } while (local_c < *(uint *)((int)this + 0x1078));
    }
    *(undefined4 *)((int)this + 0x108c) = 0;
  }
  return 0;
}



/* grim_pixel_format_ctor_x1r5g5b5 @ 1001a781 */

/* pixel format ctor for D3DFMT_X1R5G5B5 */

void * __thiscall grim_pixel_format_ctor_x1r5g5b5(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &grim_vtable_pixel_x1r5g5b5;
  return this;
}



/* grim_pixel_format_ctor_a1r5g5b5 @ 1001a79d */

/* pixel format ctor for D3DFMT_A1R5G5B5 */

void * __thiscall grim_pixel_format_ctor_a1r5g5b5(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &grim_vtable_pixel_a1r5g5b5;
  return this;
}



/* grim_pixel_format_load_yuv_cache @ 1001a7b9 */

/* loads packed YUV pixels into float cache and converts to RGB */

int __thiscall grim_pixel_format_load_yuv_cache(void *this,uint x,uint y,int load_from_surface)

{
  undefined2 uVar1;
  ushort uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  float *pfVar11;
  ushort *puVar12;
  
  if (*(int *)((int)this + 0x1090) == 0) {
    iVar10 = -0x7ff8fff2;
  }
  else {
    if ((((x < *(uint *)((int)this + 0x1074)) || (*(uint *)((int)this + 0x107c) <= x)) ||
        (y < *(uint *)((int)this + 0x1080))) || (*(uint *)((int)this + 0x1084) <= y)) {
      iVar10 = grim_pixel_format_flush_yuv_cache(this);
      if (iVar10 < 0) {
        return iVar10;
      }
      *(uint *)((int)this + 0x107c) = x + 1;
      *(uint *)((int)this + 0x1074) = x;
      *(uint *)((int)this + 0x1080) = y;
      *(uint *)((int)this + 0x1084) = y + 1;
      if (load_from_surface != 0) {
        load_from_surface = *(uint *)((int)this + 0x1070);
        pfVar11 = *(float **)((int)this + 0x106c);
        puVar12 = (ushort *)
                  (*(int *)((int)this + 0x1050) * x + *(int *)((int)this + 0x1054) * y +
                   load_from_surface * 2 + *(int *)((int)this + 0x18));
        if ((uint)load_from_surface < *(uint *)((int)this + 0x1078)) {
          do {
            uVar1 = *(undefined2 *)((int)this + 0x1094);
            uVar2 = puVar12[1];
            fVar7 = (float)(*puVar12 >> ((byte)*(undefined2 *)((int)this + 0x1098) & 0x1f) & 0xff) -
                    128.0;
            fVar6 = (float)(uVar2 >> ((byte)*(undefined2 *)((int)this + 0x1098) & 0x1f) & 0xff) -
                    128.0;
            fVar3 = fVar6 * 0.00625893;
            fVar5 = ((float)(*puVar12 >> ((byte)*(undefined2 *)((int)this + 0x1094) & 0x1f) & 0xff)
                    - 16.0) * 0.00456621;
            fVar4 = fVar5 + fVar3;
            *pfVar11 = fVar4;
            fVar8 = fVar7 * 0.00153632;
            fVar6 = fVar6 * 0.00318811;
            fVar9 = (fVar5 - fVar8) - fVar6;
            pfVar11[1] = fVar9;
            fVar7 = fVar7 * 0.00791071;
            fVar5 = fVar7 + fVar5;
            pfVar11[2] = fVar5;
            pfVar11[3] = 1.0;
            if (0.0 <= fVar4) {
              if (1.0 < fVar4) {
                fVar4 = 1.0;
              }
            }
            else {
              fVar4 = 0.0;
            }
            *pfVar11 = fVar4;
            if (0.0 <= fVar9) {
              if (1.0 < fVar9) {
                fVar9 = 1.0;
              }
            }
            else {
              fVar9 = 0.0;
            }
            pfVar11[1] = fVar9;
            if (0.0 <= fVar5) {
              if (1.0 < fVar5) {
                fVar5 = 1.0;
              }
            }
            else {
              fVar5 = 0.0;
            }
            pfVar11[2] = fVar5;
            fVar4 = ((float)(uVar2 >> ((byte)uVar1 & 0x1f) & 0xff) - 16.0) * 0.00456621;
            fVar3 = fVar4 + fVar3;
            pfVar11[4] = fVar3;
            fVar6 = (fVar4 - fVar8) - fVar6;
            pfVar11[5] = fVar6;
            fVar4 = fVar4 + fVar7;
            pfVar11[6] = fVar4;
            pfVar11[7] = 1.0;
            if (0.0 <= fVar3) {
              if (1.0 < fVar3) {
                fVar3 = 1.0;
              }
            }
            else {
              fVar3 = 0.0;
            }
            pfVar11[4] = fVar3;
            if (0.0 <= fVar6) {
              if (1.0 < fVar6) {
                fVar6 = 1.0;
              }
            }
            else {
              fVar6 = 0.0;
            }
            pfVar11[5] = fVar6;
            if (0.0 <= fVar4) {
              if (1.0 < fVar4) {
                fVar4 = 1.0;
              }
            }
            else {
              fVar4 = 0.0;
            }
            load_from_surface = load_from_surface + 2;
            pfVar11[6] = fVar4;
            puVar12 = puVar12 + 2;
            pfVar11 = pfVar11 + 8;
          } while ((uint)load_from_surface < *(uint *)((int)this + 0x1078));
        }
      }
    }
    iVar10 = 0;
  }
  return iVar10;
}



/* grim_pixel_format_ctor_a4r4g4b4 @ 1001aa8a */

/* pixel format ctor for D3DFMT_A4R4G4B4 */

void * __thiscall grim_pixel_format_ctor_a4r4g4b4(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cc10;
  return this;
}



/* grim_pixel_format_ctor_r3g3b2 @ 1001aaa6 */

/* pixel format ctor for D3DFMT_R3G3B2 */

void * __thiscall grim_pixel_format_ctor_r3g3b2(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,8,1);
  *(undefined ***)this = &PTR_FUN_1004cc20;
  return this;
}



/* grim_pixel_format_ctor_a8 @ 1001aac2 */

/* pixel format ctor for D3DFMT_A8 */

void * __thiscall grim_pixel_format_ctor_a8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,8,1);
  *(undefined ***)this = &PTR_FUN_1004cc30;
  return this;
}



/* grim_pixel_format_ctor_a8r3g3b2 @ 1001aade */

/* pixel format ctor for D3DFMT_A8R3G3B2 */

void * __thiscall grim_pixel_format_ctor_a8r3g3b2(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cc40;
  return this;
}



/* grim_pixel_format_ctor_x4r4g4b4 @ 1001aafa */

/* pixel format ctor for D3DFMT_X4R4G4B4 */

void * __thiscall grim_pixel_format_ctor_x4r4g4b4(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cc50;
  return this;
}



/* grim_pixel_format_write_yuv_cache @ 1001ab16 */

/* loads YUV cache for coords, copies RGBA floats into cache, marks dirty for flush */

void __thiscall grim_pixel_format_write_yuv_cache(void *this,int x,int y,float *pixels)

{
  int iVar1;
  uint uVar2;
  float *pfVar3;
  
  if (*(int *)((int)this + 0x1048) != 0) {
    pixels = grim_convert_vertex_space(this,pixels);
  }
  iVar1 = grim_pixel_format_load_yuv_cache
                    (this,x + *(int *)((int)this + 0x1034),y + *(int *)((int)this + 0x1040),
                     (uint)(*(int *)((int)this + 0x1088) != *(int *)((int)this + 0x1058)));
  if (-1 < iVar1) {
    pfVar3 = (float *)((*(int *)((int)this + 0x1030) - *(int *)((int)this + 0x1070)) * 0x10 +
                      *(int *)((int)this + 0x106c));
    for (uVar2 = (uint)(*(int *)((int)this + 0x1058) << 4) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pfVar3 = *pixels;
      pixels = pixels + 1;
      pfVar3 = pfVar3 + 1;
    }
    for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined1 *)pfVar3 = *(undefined1 *)pixels;
      pixels = (float *)((int)pixels + 1);
      pfVar3 = (float *)((int)pfVar3 + 1);
    }
    *(undefined4 *)((int)this + 0x108c) = 1;
  }
  return;
}



/* grim_pixel_format_ctor_a2b10g10r10 @ 1001aba3 */

/* pixel format ctor for D3DFMT_A2B10G10R10 */

void * __thiscall grim_pixel_format_ctor_a2b10g10r10(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,1);
  *(undefined ***)this = &PTR_FUN_1004cc60;
  return this;
}



/* grim_pixel_format_ctor_g16r16 @ 1001ac2e */

/* pixel format ctor for D3DFMT_G16R16 */

void * __thiscall grim_pixel_format_ctor_g16r16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,1);
  *(undefined ***)this = &PTR_FUN_1004cc70;
  return this;
}



/* grim_pixel_format_init_dxt @ 1001ac4a */

/* initializes DXT block-compressed pixel format (DXT1..DXT5) */

void * __thiscall grim_pixel_format_init_dxt(void *this,uint *desc)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar4 = 1;
  grim_pixel_format_init(this,desc,0,1);
  *(undefined ***)this = &PTR_FUN_1004caf8;
  if (desc[6] == 1) {
    *(undefined4 *)((int)this + 0x1078) = 0;
  }
  else if (desc[6] == 2) {
    *(undefined4 *)((int)this + 0x1078) = 1;
  }
  else {
    *(undefined4 *)((int)this + 0x1078) = 3;
  }
  if (desc[7] == 1) {
    *(undefined4 *)((int)this + 0x107c) = 0;
  }
  else if (desc[7] == 2) {
    *(undefined4 *)((int)this + 0x107c) = 1;
  }
  else {
    *(undefined4 *)((int)this + 0x107c) = 3;
  }
  if ((*(int *)((int)this + 0x1078) == 3) && (*(int *)((int)this + 0x107c) == 3)) {
    uVar4 = 0;
  }
  *(undefined4 *)((int)this + 0x1074) = uVar4;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 == 0x31545844) {
    *(undefined4 *)((int)this + 0x1080) = 8;
    *(undefined1 **)((int)this + 0x1088) = &LAB_10021b96;
    *(code **)((int)this + 0x1084) = grim_dxt1_decode_color_block;
  }
  else if (iVar1 == 0x32545844) {
    *(undefined4 *)((int)this + 0x1080) = 0x10;
    *(code **)((int)this + 0x1088) = grim_dxt2_encode_block;
    *(undefined1 **)((int)this + 0x1084) = &grim_dxt2_decode_block;
  }
  else if (iVar1 == 0x33545844) {
    *(undefined4 *)((int)this + 0x1080) = 0x10;
    *(code **)((int)this + 0x1088) = grim_dxt3_encode_block;
    *(code **)((int)this + 0x1084) = grim_dxt3_decode_block;
  }
  else if (iVar1 == 0x34545844) {
    *(undefined4 *)((int)this + 0x1080) = 0x10;
    *(code **)((int)this + 0x1088) = grim_dxt4_encode_block;
    *(undefined1 **)((int)this + 0x1084) = &grim_dxt4_decode_block;
  }
  else if (iVar1 == 0x35545844) {
    *(undefined4 *)((int)this + 0x1080) = 0x10;
    *(code **)((int)this + 0x1088) = grim_dxt5_encode_block;
    *(code **)((int)this + 0x1084) = grim_dxt5_decode_block;
  }
  *(undefined4 *)((int)this + 0x10b0) = 0xffffffff;
  *(undefined4 *)((int)this + 0x10b4) = 0xffffffff;
  *(undefined4 *)((int)this + 0x109c) = *(undefined4 *)((int)this + 0x1040);
  uVar2 = *(int *)((int)this + 0x1038) + 3U & 0xfffffffc;
  uVar6 = *(uint *)((int)this + 0x1030) & 0xfffffffc;
  *(uint *)((int)this + 0x1094) = uVar2;
  uVar5 = *(uint *)((int)this + 0x1034) & 0xfffffffc;
  uVar3 = *(int *)((int)this + 0x103c) + 3U & 0xfffffffc;
  *(uint *)((int)this + 0x1098) = uVar3;
  *(uint *)((int)this + 0x10a4) = uVar2 - uVar6 >> 2;
  *(int *)((int)this + 0x10a0) = *(int *)((int)this + 0x1044);
  *(uint *)((int)this + 0x108c) = uVar6;
  *(undefined4 *)((int)this + 0x10b8) = 0;
  *(undefined4 *)((int)this + 0x10bc) = 0;
  *(undefined4 *)((int)this + 0x10c0) = 0;
  *(uint *)((int)this + 0x1090) = uVar5;
  *(uint *)((int)this + 0x10a8) = uVar3 - uVar5 >> 2;
  *(int *)((int)this + 0x10ac) = *(int *)((int)this + 0x1044) - *(int *)((int)this + 0x1040);
  return this;
}



/* grim_pixel_format_ctor_a8p8 @ 1001ae3c */

/* pixel format ctor for D3DFMT_A8P8 */

void * __thiscall grim_pixel_format_ctor_a8p8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cc80;
  return this;
}



/* grim_pixel_format_write_row_dispatch @ 1001ae58 */

/* [binja] void*** __thiscall sub_1001ae58(void*** arg1, char arg2) */

void *** __thiscall grim_pixel_format_write_row_dispatch(void *this,void ***arg1,char arg2)

{
  grim_vertex_space_converter_destroy(this);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}



/* grim_pixel_format_ctor_p8 @ 1001ae74 */

/* pixel format ctor for D3DFMT_P8 */

void * __thiscall grim_pixel_format_ctor_p8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,8,1);
  *(undefined ***)this = &PTR_FUN_1004cc90;
  return this;
}



/* grim_pixel_format_ctor_l8 @ 1001ae90 */

/* pixel format ctor for D3DFMT_L8 */

void * __thiscall grim_pixel_format_ctor_l8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,8,1);
  *(undefined ***)this = &PTR_FUN_1004cca0;
  return this;
}



/* grim_pixel_format_ctor_a8l8 @ 1001aeac */

/* pixel format ctor for D3DFMT_A8L8 */

void * __thiscall grim_pixel_format_ctor_a8l8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004ccb0;
  return this;
}



/* grim_pixel_format_init_a4l4_surface @ 1001aec8 */

/* [binja] void*** __thiscall sub_1001aec8(void*** arg1, char arg2) */

void *** __thiscall grim_pixel_format_init_a4l4_surface(void *this,void ***arg1,char arg2)

{
  void ***unaff_ESI;
  
  grim_pixel_format_convert_surface(unaff_ESI);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}



/* grim_pixel_format_ctor_a4l4 @ 1001aee4 */

/* pixel format ctor for D3DFMT_A4L4 */

void * __thiscall grim_pixel_format_ctor_a4l4(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,8,1);
  *(undefined ***)this = &PTR_FUN_1004ccc0;
  return this;
}



/* grim_pixel_format_init_bumpmaps @ 1001af00 */

/* [binja] void* __fastcall sub_1001af00(void* arg1) */

void * __fastcall grim_pixel_format_init_bumpmaps(void *arg1)

{
  undefined4 uVar1;
  
  if ((*(int *)((int)arg1 + 4) == 0x32545844) || (*(int *)((int)arg1 + 4) == 0x33545844)) {
    uVar1 = 0x41700000;
  }
  else {
    uVar1 = 0x437f0000;
  }
  *(undefined4 *)((int)arg1 + 0x106c) = uVar1;
  *(float *)((int)arg1 + 0x1070) = 1.0 / *(float *)((int)arg1 + 0x106c);
  *(float *)((int)arg1 + 0x1c) =
       (float)(int)ROUND(*(float *)((int)arg1 + 0x1c) * 31.0 + 0.5) * 0.032258064;
  *(float *)((int)arg1 + 0x20) =
       (float)(int)ROUND(*(float *)((int)arg1 + 0x20) * 63.0 + 0.5) * 0.015873017;
  *(float *)((int)arg1 + 0x24) =
       (float)(int)ROUND(*(float *)((int)arg1 + 0x24) * 31.0 + 0.5) * 0.032258064;
  *(float *)((int)arg1 + 0x28) =
       (float)(int)ROUND(*(float *)((int)arg1 + 0x106c) * *(float *)((int)arg1 + 0x28) + 0.5) *
       *(float *)((int)arg1 + 0x1070);
  return arg1;
}



/* grim_pixel_format_ctor_v8u8 @ 1001b001 */

/* pixel format ctor for D3DFMT_V8U8 */

void * __thiscall grim_pixel_format_ctor_v8u8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,2);
  *(undefined ***)this = &PTR_FUN_1004ccd0;
  return this;
}



/* grim_pixel_format_ctor_l6v5u5 @ 1001b01d */

/* pixel format ctor for D3DFMT_L6V5U5 */

void * __thiscall grim_pixel_format_ctor_l6v5u5(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,2);
  *(undefined ***)this = &PTR_FUN_1004cce0;
  return this;
}



/* grim_pixel_format_ctor_x8l8v8u8 @ 1001b039 */

/* pixel format ctor for D3DFMT_X8L8V8U8 */

void * __thiscall grim_pixel_format_ctor_x8l8v8u8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,2);
  *(undefined ***)this = &PTR_FUN_1004ccf0;
  return this;
}



/* grim_pixel_format_ctor_q8w8v8u8 @ 1001b055 */

/* pixel format ctor for D3DFMT_Q8W8V8U8 */

void * __thiscall grim_pixel_format_ctor_q8w8v8u8(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,3);
  *(undefined ***)this = &PTR_FUN_1004cd00;
  return this;
}



/* grim_pixel_format_ctor_v16u16 @ 1001b071 */

/* pixel format ctor for D3DFMT_V16U16 */

void * __thiscall grim_pixel_format_ctor_v16u16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,2);
  *(undefined ***)this = &PTR_FUN_1004cd10;
  return this;
}



/* grim_pixel_format_ctor_w11v11u10 @ 1001b08d */

/* pixel format ctor for D3DFMT_W11V11U10 */

void * __thiscall grim_pixel_format_ctor_w11v11u10(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,2);
  *(undefined ***)this = &PTR_FUN_1004cd20;
  return this;
}



/* grim_pixel_format_ctor_a2w10v10u10 @ 1001b0a9 */

/* pixel format ctor for D3DFMT_A2W10V10U10 */

void * __thiscall grim_pixel_format_ctor_a2w10v10u10(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,2);
  *(undefined ***)this = &PTR_FUN_1004cd30;
  return this;
}



/* grim_pixel_format_ctor_d16_lockable @ 1001b0c5 */

/* pixel format ctor for D3DFMT_D16_LOCKABLE */

void * __thiscall grim_pixel_format_ctor_d16_lockable(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cd40;
  return this;
}



/* grim_pixel_format_ctor_l16 @ 1001b0e1 */

/* pixel format ctor for FourCC L16 (16-bit luminance) */

void * __thiscall grim_pixel_format_ctor_l16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x10,1);
  *(undefined ***)this = &PTR_FUN_1004cd50;
  return this;
}



/* grim_pixel_format_read_dxt_cache @ 1001b0fd */

/* decodes DXT blocks into cache on demand and copies RGBA floats to output (color key aware) */

void grim_pixel_format_read_dxt_cache(void *this,uint x,uint y,float *out)

{
  undefined4 *puVar1;
  void *pvVar2;
  int extraout_ECX;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint extraout_EDX;
  int iVar6;
  int unaff_EBP;
  int iVar7;
  undefined4 *puVar8;
  
  seh_prolog();
  *(int *)(unaff_EBP + -0x10) = extraout_ECX;
  *(int *)(unaff_EBP + 8) = *(int *)(unaff_EBP + 8) + *(int *)(extraout_ECX + 0x1034);
  *(int *)(unaff_EBP + 0xc) = *(int *)(unaff_EBP + 0xc) + *(int *)(extraout_ECX + 0x1040);
  iVar3 = extraout_ECX;
  if (*(int *)(extraout_ECX + 0x10b8) == 0) {
    iVar3 = *(int *)(extraout_ECX + 0x10a4);
    pvVar2 = operator_new(iVar3 << 8);
    *(void **)(unaff_EBP + -0x24) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar2 == (void *)0x0) {
      pvVar2 = (void *)0x0;
    }
    else {
      _vector_constructor_iterator_(pvVar2,0x10,iVar3 << 4,(_func_void_ptr_void_ptr *)&LAB_1000ae4f)
      ;
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(void **)(*(int *)(unaff_EBP + -0x10) + 0x10b8) = pvVar2;
    if (pvVar2 == (void *)0x0) goto LAB_1001b396;
    iVar3 = *(int *)(unaff_EBP + -0x10);
  }
  uVar4 = *(uint *)(unaff_EBP + 8) & 0xfffffffc;
  if ((uVar4 != *(uint *)(iVar3 + 0x10b0)) ||
     (*(int *)(unaff_EBP + 0xc) != *(int *)(iVar3 + 0x10b4))) {
    *(uint *)(iVar3 + 0x10b0) = uVar4;
    *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x10b4) = *(undefined4 *)(unaff_EBP + 0xc);
    iVar3 = *(int *)(unaff_EBP + -0x10);
    uVar4 = *(uint *)(iVar3 + 0x108c);
    iVar6 = *(int *)(iVar3 + 0x10b8);
    iVar7 = (*(uint *)(iVar3 + 0x10b0) >> 2) * *(int *)(iVar3 + 0x1050) +
            (uVar4 >> 2) * *(int *)(iVar3 + 0x1080) +
            *(int *)(iVar3 + 0x10b4) * *(int *)(iVar3 + 0x1054) + *(int *)(iVar3 + 0x18);
    for (; uVar4 < *(uint *)(iVar3 + 0x1094); uVar4 = uVar4 + 4) {
      (**(code **)(iVar3 + 0x1084))(iVar6,iVar7);
      iVar3 = *(int *)(unaff_EBP + -0x10);
      iVar7 = iVar7 + *(int *)(iVar3 + 0x1080);
      iVar6 = iVar6 + 0x100;
    }
  }
  iVar6 = *(int *)(unaff_EBP + 8);
  iVar7 = *(int *)(iVar3 + 0x1090);
  uVar4 = *(int *)(iVar3 + 0x1030) - *(int *)(iVar3 + 0x108c);
  uVar5 = *(int *)(iVar3 + 0x1058) + uVar4;
  for (; uVar4 < uVar5; uVar4 = uVar4 + 1) {
    puVar1 = *(undefined4 **)(unaff_EBP + 0x10);
    puVar8 = (undefined4 *)
             (((uVar4 & 0xfffffffc | iVar6 - iVar7 & 3U) << 2 | uVar4 & 3) * 0x10 +
             *(int *)(iVar3 + 0x10b8));
    *puVar1 = *puVar8;
    puVar1[1] = puVar8[1];
    puVar1[2] = puVar8[2];
    puVar1[3] = puVar8[3];
    *(int *)(unaff_EBP + 0x10) = *(int *)(unaff_EBP + 0x10) + 0x10;
    iVar3 = *(int *)(unaff_EBP + -0x10);
  }
  if (*(int *)(iVar3 + 0x10) != 0) {
    fpu_set_round_trunc();
    while (*(uint *)(unaff_EBP + 0x10) < extraout_EDX) {
      *(float *)(unaff_EBP + -0x14) = **(float **)(unaff_EBP + 0x10) * 31.0 + 0.5;
      *(int *)(unaff_EBP + -0x18) = (int)ROUND(*(float *)(unaff_EBP + -0x14));
      *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x18);
      *(float *)(unaff_EBP + -0x34) = (float)*(int *)(unaff_EBP + -0x14) * 0.032258064;
      *(float *)(unaff_EBP + -0x14) = *(float *)(*(int *)(unaff_EBP + 0x10) + 4) * 63.0 + 0.5;
      *(int *)(unaff_EBP + -0x1c) = (int)ROUND(*(float *)(unaff_EBP + -0x14));
      *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x1c);
      *(float *)(unaff_EBP + -0x30) = (float)*(int *)(unaff_EBP + -0x14) * 0.015873017;
      *(float *)(unaff_EBP + -0x14) = *(float *)(*(int *)(unaff_EBP + 0x10) + 8) * 31.0 + 0.5;
      *(int *)(unaff_EBP + -0x20) = (int)ROUND(*(float *)(unaff_EBP + -0x14));
      *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x20);
      *(float *)(unaff_EBP + -0x2c) = (float)*(int *)(unaff_EBP + -0x14) * 0.032258064;
      *(float *)(unaff_EBP + -0x14) =
           *(float *)(*(int *)(unaff_EBP + -0x10) + 0x106c) *
           *(float *)(*(int *)(unaff_EBP + 0x10) + 0xc) + 0.5;
      *(int *)(unaff_EBP + -0x24) = (int)ROUND(*(float *)(unaff_EBP + -0x14));
      iVar3 = *(int *)(unaff_EBP + -0x10);
      *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x24);
      if ((((*(float *)(unaff_EBP + -0x34) == *(float *)(iVar3 + 0x1c)) &&
           (*(float *)(unaff_EBP + -0x30) == *(float *)(iVar3 + 0x20))) &&
          (*(float *)(unaff_EBP + -0x2c) == *(float *)(iVar3 + 0x24))) &&
         ((float)*(int *)(unaff_EBP + -0x14) * *(float *)(iVar3 + 0x1070) ==
          *(float *)(iVar3 + 0x28))) {
        puVar1 = *(undefined4 **)(unaff_EBP + 0x10);
        *(undefined4 *)(unaff_EBP + -0x44) = 0;
        *(undefined4 *)(unaff_EBP + -0x40) = 0;
        *(undefined4 *)(unaff_EBP + -0x3c) = 0;
        *(undefined4 *)(unaff_EBP + -0x38) = 0;
        *puVar1 = *(undefined4 *)(unaff_EBP + -0x44);
        puVar1[1] = *(undefined4 *)(unaff_EBP + -0x40);
        puVar1[2] = *(undefined4 *)(unaff_EBP + -0x3c);
        puVar1[3] = *(undefined4 *)(unaff_EBP + -0x38);
      }
      *(int *)(unaff_EBP + 0x10) = *(int *)(unaff_EBP + 0x10) + 0x10;
    }
    *(undefined4 *)(unaff_EBP + -0x24) = grim_fpu_control_word;
  }
LAB_1001b396:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}



/* grim_pixel_format_ctor_al16 @ 1001b3a6 */

/* pixel format ctor for FourCC AL16 */

void * __thiscall grim_pixel_format_ctor_al16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x20,1);
  *(undefined ***)this = &PTR_FUN_1004cd60;
  return this;
}



/* grim_pixel_format_ctor_r16 @ 1001b3c2 */

/* pixel format ctor for FourCC R16 */

void * __thiscall grim_pixel_format_ctor_r16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x30,1);
  *(undefined ***)this = &PTR_FUN_1004cd70;
  return this;
}



/* grim_pixel_format_ctor_ar16 @ 1001b3de */

/* pixel format ctor for FourCC AR16 */

void * __thiscall grim_pixel_format_ctor_ar16(void *this,uint *desc)

{
  grim_pixel_format_init(this,desc,0x40,1);
  *(undefined ***)this = &PTR_FUN_1004cd80;
  return this;
}



/* grim_pixel_format_ctor_dxt1 @ 1001b3fa */

/* pixel format ctor for FourCC DXT1 */

void * __thiscall grim_pixel_format_ctor_dxt1(void *this,uint *desc)

{
  grim_pixel_format_init_dxt(this,desc);
  *(undefined ***)this = &PTR_FUN_1004cd90;
  return this;
}



/* grim_pixel_format_ctor_dxt2 @ 1001b412 */

/* pixel format ctor for FourCC DXT2 */

void * __thiscall grim_pixel_format_ctor_dxt2(void *this,uint *desc)

{
  grim_pixel_format_init_dxt(this,desc);
  *(undefined ***)this = &PTR_FUN_1004cda0;
  return this;
}



/* grim_pixel_format_ctor_dxt3 @ 1001b42a */

/* pixel format ctor for FourCC DXT3 */

void * __thiscall grim_pixel_format_ctor_dxt3(void *this,uint *desc)

{
  grim_pixel_format_init_dxt(this,desc);
  *(undefined ***)this = &PTR_FUN_1004cdb0;
  return this;
}



/* grim_pixel_format_ctor_dxt4 @ 1001b442 */

/* pixel format ctor for FourCC DXT4 */

void * __thiscall grim_pixel_format_ctor_dxt4(void *this,uint *desc)

{
  grim_pixel_format_init_dxt(this,desc);
  *(undefined ***)this = &PTR_FUN_1004cdc0;
  return this;
}



/* grim_pixel_format_ctor_dxt5 @ 1001b45a */

/* pixel format ctor for FourCC DXT5 */

void * __thiscall grim_pixel_format_ctor_dxt5(void *this,uint *desc)

{
  grim_pixel_format_init_dxt(this,desc);
  *(undefined ***)this = &PTR_FUN_1004cdd0;
  return this;
}



/* grim_pixel_format_convert_dispatch @ 1001b472 */

/* [binja] void*** __thiscall sub_1001b472(void*** arg1, char arg2) */

void *** __thiscall grim_pixel_format_convert_dispatch(void *this,void ***arg1,char arg2)

{
  void ***unaff_ESI;
  
  thunk_grim_pixel_format_convert_surface(unaff_ESI);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}



/* grim_pixel_format_create_by_d3dfmt @ 1001b493 */

/* [binja] int32_t __fastcall sub_1001b493(void*** arg1) */

int grim_pixel_format_create_by_d3dfmt(void ***arg1)

{
  int extraout_EAX;
  undefined4 *this;
  int unaff_EBP;
  
  seh_prolog();
  *(undefined4 **)(unaff_EBP + -0x10) = this;
  *this = &grim_vtable_pixel_yuv;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  grim_pixel_format_flush_yuv_cache(this);
  if ((void *)this[0x41b] != (void *)0x0) {
    operator_delete((void *)this[0x41b]);
  }
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_vertex_space_converter_destroy(this);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return extraout_EAX;
}



/* grim_pixel_format_ctor_uyvy @ 1001b4dc */

/* pixel format ctor for FourCC UYVY */

void * __fastcall grim_pixel_format_ctor_uyvy(void *this)

{
  uint *unaff_ESI;
  void *in_stack_00000004;
  
  grim_pixel_format_init_yuv(in_stack_00000004,unaff_ESI);
  *(undefined ***)this = &PTR_FUN_1004cde0;
  return this;
}



/* grim_pixel_format_ctor_yuy2 @ 1001b4f4 */

/* pixel format ctor for FourCC YUY2 */

void * __fastcall grim_pixel_format_ctor_yuy2(void *this)

{
  uint *unaff_ESI;
  void *in_stack_00000004;
  
  grim_pixel_format_init_yuv(in_stack_00000004,unaff_ESI);
  *(undefined ***)this = &PTR_FUN_1004cdf0;
  return this;
}



/* grim_pixel_format_create @ 1001b50c */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* factory: picks pixel format implementation from FourCC/D3DFORMAT */

void * grim_pixel_format_create(uint *desc)

{
  uint *desc_00;
  uint uVar1;
  void *pvVar2;
  int unaff_EBP;
  int *piVar3;
  
  seh_prolog();
  desc_00 = *(uint **)(unaff_EBP + 8);
  uVar1 = desc_00[1];
  piVar3 = (int *)0x0;
  if ((int)uVar1 < 0x31545845) {
    if (uVar1 == 0x31545844) {
      pvVar2 = operator_new(0x10c4);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x20;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_dxt1(pvVar2,desc_00);
    }
    else if ((int)uVar1 < 0x29) {
      if (uVar1 == 0x28) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0xd;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_a8p8(pvVar2,desc_00);
      }
      else {
        switch(uVar1) {
        case 0x14:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 0;
          if (pvVar2 == (void *)0x0) {
LAB_1001bc03:
            piVar3 = (int *)0x0;
          }
          else {
            piVar3 = grim_pixel_format_ctor_r8g8b8(pvVar2,desc_00);
          }
          break;
        case 0x15:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 1;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a8r8g8b8(pvVar2,desc_00);
          break;
        case 0x16:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 2;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_x8r8g8b8(pvVar2,desc_00);
          break;
        case 0x17:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 3;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_r5g6b5(pvVar2,desc_00);
          break;
        case 0x18:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 4;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_x1r5g5b5(pvVar2,desc_00);
          break;
        case 0x19:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 5;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a1r5g5b5(pvVar2,desc_00);
          break;
        case 0x1a:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 6;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a4r4g4b4(pvVar2,desc_00);
          break;
        case 0x1b:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 7;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_r3g3b2(pvVar2,desc_00);
          break;
        case 0x1c:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 8;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a8(pvVar2,desc_00);
          break;
        case 0x1d:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 9;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a8r3g3b2(pvVar2,desc_00);
          break;
        case 0x1e:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 10;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_x4r4g4b4(pvVar2,desc_00);
          break;
        case 0x1f:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 0xb;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_a2b10g10r10(pvVar2,desc_00);
          break;
        default:
          goto switchD_1001b54e_caseD_20;
        case 0x22:
          pvVar2 = operator_new(0x106c);
          *(void **)(unaff_EBP + 8) = pvVar2;
          *(undefined4 *)(unaff_EBP + -4) = 0xc;
          if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
          piVar3 = grim_pixel_format_ctor_g16r16(pvVar2,desc_00);
        }
      }
    }
    else if ((int)uVar1 < 0x3f) {
      if (uVar1 == 0x3e) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0x14;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_x8l8v8u8(pvVar2,desc_00);
      }
      else if (uVar1 == 0x29) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0xe;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_p8(pvVar2,desc_00);
      }
      else if (uVar1 == 0x32) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0xf;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_l8(pvVar2,desc_00);
      }
      else if (uVar1 == 0x33) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0x10;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_a8l8(pvVar2,desc_00);
      }
      else if (uVar1 == 0x34) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0x11;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_a4l4(pvVar2,desc_00);
      }
      else if (uVar1 == 0x3c) {
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0x12;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_v8u8(pvVar2,desc_00);
      }
      else {
        if (uVar1 != 0x3d) goto switchD_1001b54e_caseD_20;
        pvVar2 = operator_new(0x106c);
        *(void **)(unaff_EBP + 8) = pvVar2;
        *(undefined4 *)(unaff_EBP + -4) = 0x13;
        if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
        piVar3 = grim_pixel_format_ctor_l6v5u5(pvVar2,desc_00);
      }
    }
    else if (uVar1 == 0x3f) {
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x15;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_q8w8v8u8(pvVar2,desc_00);
    }
    else if (uVar1 == 0x40) {
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x16;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_v16u16(pvVar2,desc_00);
    }
    else if (uVar1 == 0x41) {
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x17;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_w11v11u10(pvVar2,desc_00);
    }
    else if (uVar1 == 0x43) {
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x18;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_a2w10v10u10(pvVar2,desc_00);
    }
    else {
      if (uVar1 != 0x46) goto switchD_1001b54e_caseD_20;
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x19;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_d16_lockable(pvVar2,desc_00);
    }
  }
  else if ((int)uVar1 < 0x36314c21) {
    if (uVar1 == 0x36314c20) {
      pvVar2 = operator_new(0x106c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x1a;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_l16(pvVar2,desc_00);
    }
    else if (uVar1 == 0x32545844) {
      pvVar2 = operator_new(0x10c4);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x21;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_dxt2(pvVar2,desc_00);
    }
    else if (uVar1 == 0x32595559) {
      pvVar2 = operator_new(0x109c);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x1f;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_yuy2(pvVar2);
    }
    else if (uVar1 == 0x33545844) {
      pvVar2 = operator_new(0x10c4);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x22;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_dxt3(pvVar2,desc_00);
    }
    else if (uVar1 == 0x34545844) {
      pvVar2 = operator_new(0x10c4);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x23;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_dxt4(pvVar2,desc_00);
    }
    else {
      if (uVar1 != 0x35545844) goto switchD_1001b54e_caseD_20;
      pvVar2 = operator_new(0x10c4);
      *(void **)(unaff_EBP + 8) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 0x24;
      if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
      piVar3 = grim_pixel_format_ctor_dxt5(pvVar2,desc_00);
    }
  }
  else if (uVar1 == 0x36314c41) {
    pvVar2 = operator_new(0x106c);
    *(void **)(unaff_EBP + 8) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0x1b;
    if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
    piVar3 = grim_pixel_format_ctor_al16(pvVar2,desc_00);
  }
  else if (uVar1 == 0x36315220) {
    pvVar2 = operator_new(0x106c);
    *(void **)(unaff_EBP + 8) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0x1c;
    if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
    piVar3 = grim_pixel_format_ctor_r16(pvVar2,desc_00);
  }
  else if (uVar1 == 0x36315241) {
    pvVar2 = operator_new(0x106c);
    *(void **)(unaff_EBP + 8) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0x1d;
    if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
    piVar3 = grim_pixel_format_ctor_ar16(pvVar2,desc_00);
  }
  else {
    if (uVar1 != 0x59565955) goto switchD_1001b54e_caseD_20;
    pvVar2 = operator_new(0x109c);
    *(void **)(unaff_EBP + 8) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0x1e;
    if (pvVar2 == (void *)0x0) goto LAB_1001bc03;
    piVar3 = grim_pixel_format_ctor_uyvy(pvVar2);
  }
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if ((piVar3 != (int *)0x0) && (piVar3[4] != 0)) {
    (**(code **)(*piVar3 + 0xc))();
  }
switchD_1001b54e_caseD_20:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return piVar3;
}



/* grim_pixel_format_create_and_convert @ 1001bc84 */

/* [binja] void*** __thiscall sub_1001bc84(void*** arg1, char arg2) */

void *** __thiscall grim_pixel_format_create_and_convert(void *this,void ***arg1,char arg2)

{
  void ***unaff_ESI;
  
  thunk_grim_pixel_format_create_by_d3dfmt(unaff_ESI);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}


