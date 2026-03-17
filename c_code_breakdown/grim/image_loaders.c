/* grim_image_load_from_memory @ 1000acc0 */

/* [binja] int32_t __stdcall sub_1000acc0(int32_t* arg1, int32_t arg2, int32_t* arg3, int32_t arg4,
   int32_t arg5, int32_t arg6, int32_t arg7, int32_t* arg8, int32_t arg9, int32_t arg10) */

int grim_image_load_from_memory(int *arg1,int arg2,int *arg3,int arg4,int arg5,int arg6,int arg7,int *arg8,int arg9
                ,int arg10)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  int *piVar3;
  int unaff_EDI;
  int *piVar4;
  int local_b8 [19];
  void **local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  int local_5c [4];
  undefined4 local_4c;
  undefined4 local_48;
  int local_44 [7];
  int local_28;
  int local_24;
  int local_20 [4];
  int local_10 [3];
  
  grim_alloc_context_init(local_10);
  grim_zip_reader_init(local_20);
  if (arg1 == (int *)0x0) {
    iVar2 = -0x7789f794;
  }
  else if ((arg4 == 0) || (arg8 == (int *)0x0)) {
    iVar2 = -0x7789f794;
  }
  else {
    if (arg9 == -1) {
      arg9 = 0x80004;
    }
    iVar1 = grim_zip_read_header(local_20,(char *)local_b8,arg1,(int *)arg2,(int)arg3,(int *)0x0,0,unaff_ESI
                        );
    if (-1 < iVar1) {
      local_68 = arg5;
      local_6c = (void **)arg4;
      local_64 = arg6;
      local_60 = 0;
      local_5c[0] = *arg8;
      local_5c[1] = arg8[1];
      local_5c[2] = arg8[2];
      local_5c[3] = arg8[3];
      local_4c = 0;
      local_48 = 1;
      piVar3 = local_5c;
      piVar4 = local_44;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar4 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      }
      local_28 = arg10;
      local_24 = arg7;
      iVar1 = grim_zip_decompress(local_10,local_b8,&local_6c,(void ***)arg9,unaff_EDI);
      iVar2 = 0;
      if (-1 < iVar1) goto LAB_1000ad85;
    }
    iVar2 = iVar1;
  }
LAB_1000ad85:
  grim_zip_reader_close((char *)local_20);
  grim_alloc_context_free(local_10);
  return iVar2;
}



/* grim_image_get_info @ 1000ad9f */

/* [binja] int32_t sub_1000ad9f(int32_t arg1, int32_t arg2, int32_t* arg3, int32_t arg4, int32_t*
   arg5, int32_t* arg6) */

int grim_image_get_info(int arg1,int arg2,int *arg3,int arg4,int *arg5,int *arg6)

{
  int unaff_EBP;
  int *unaff_ESI;
  int iVar1;
  
  seh_prolog();
  grim_file_stream_init((int *)(unaff_EBP + -0x70));
  *(undefined4 *)(unaff_EBP + -4) = 0;
  grim_zip_reader_init((int *)(unaff_EBP + -0x1c));
  *(undefined1 *)(unaff_EBP + -4) = 1;
  if ((*(int *)(unaff_EBP + 8) == 0) || (*(int *)(unaff_EBP + 0x10) == 0)) {
    iVar1 = -0x7789f794;
  }
  else {
    iVar1 = grim_zip_read_header((void *)(unaff_EBP + -0x1c),(char *)(unaff_EBP + -0xbc),
                         *(int **)(unaff_EBP + 0x10),*(int **)(unaff_EBP + 0x14),
                         *(int *)(unaff_EBP + 0x18),(int *)0x0,1,(int)unaff_ESI);
    if (((-1 < iVar1) &&
        (iVar1 = grim_file_stream_read_header((void *)(unaff_EBP + -0x70),(int *)(unaff_EBP + -0xbc),unaff_ESI),
        -1 < iVar1)) &&
       (iVar1 = grim_alloc_block(*(int **)(unaff_EBP + 8),*(int *)(unaff_EBP + 0xc),
                             *(int *)(unaff_EBP + 0x1c),unaff_ESI), -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  *(undefined1 *)(unaff_EBP + -4) = 0;
  grim_zip_reader_close((char *)(unaff_EBP + -0x1c));
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_file_stream_close((void *)(unaff_EBP + -0x70));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar1;
}



/* grim_image_get_info_simple @ 1000ae52 */

/* [binja] int32_t __stdcall sub_1000ae52(int32_t arg1, int32_t arg2, int32_t* arg3, int32_t arg4,
   int32_t* arg5) */

int grim_image_get_info_simple(int arg1,int arg2,int *arg3,int arg4,int *arg5)

{
  int iVar1;
  
  iVar1 = grim_image_get_info(arg1,arg2,arg3,arg4,arg5,(int *)0x0);
  return iVar1;
}



/* grim_image_load_from_file_ex @ 1000ae72 */

/* [binja] int32_t __stdcall sub_1000ae72(int32_t* arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8, int32_t arg9, int32_t arg10, int32_t
   arg11) */

int grim_image_load_from_file_ex(int *arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7,int arg8,int arg9,
                int arg10,int arg11)

{
  int unaff_ESI;
  int iVar1;
  undefined4 *puVar2;
  int unaff_EDI;
  undefined4 *puVar3;
  int local_ac [19];
  void **local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50 [6];
  undefined4 local_38 [7];
  int local_1c;
  int local_18;
  int local_14 [3];
  int local_8;
  
  grim_alloc_context_init(local_14);
  grim_zip_buffer_init(&local_8);
  if (((arg1 == (int *)0x0) || (arg4 == 0)) || (arg9 == 0)) {
    iVar1 = -0x7789f794;
  }
  else {
    if (arg10 == -1) {
      arg10 = 0x80004;
    }
    iVar1 = grim_zip_read_entry(&local_8,local_ac,arg1,(int *)arg2,arg3,0,0,unaff_ESI);
    if (-1 < iVar1) {
      local_5c = arg5;
      local_58 = arg6;
      local_60 = (void **)arg4;
      local_54 = arg7;
      puVar2 = (undefined4 *)arg9;
      puVar3 = local_50;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = local_38;
      for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = *(undefined4 *)arg9;
        arg9 = (int)(arg9 + 4);
        puVar2 = puVar2 + 1;
      }
      local_1c = arg11;
      local_18 = arg8;
      iVar1 = grim_zip_decompress(local_14,local_ac,&local_60,(void ***)arg10,unaff_EDI);
      if (-1 < iVar1) {
        iVar1 = 0;
      }
    }
  }
  thunk_grim_zip_buffer_free(&local_8);
  grim_alloc_context_free(local_14);
  return iVar1;
}



/* grim_image_check_dimensions @ 1000af45 */

undefined4 __fastcall
grim_image_check_dimensions(undefined4 param_1,uint param_2,int *param_3,uint *param_4,uint *param_5,uint *param_6,
            uint *param_7,int *param_8,int param_9,int param_10)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined1 local_e0 [60];
  uint local_a4;
  int *local_88;
  int *local_84;
  int *local_80;
  int local_78;
  int local_c;
  int *local_8;
  
  piVar4 = param_3;
  if (param_3 == (int *)0x0) {
    return 0x8876086c;
  }
  if (param_2 == 0xffffffff) {
    param_2 = 0;
  }
  if (param_2 != (param_2 & 0x20b)) {
    return 0x8876086c;
  }
  if ((((param_9 != 0) && (param_9 != 1)) && (param_9 != 2)) && (param_9 != 3)) {
    return 0x8876086c;
  }
  if (param_8 == (int *)0x0) {
    local_c = 0;
  }
  else {
    local_c = *param_8;
  }
  if (param_9 == 3) {
    if (local_c == 0) {
      local_c = 0x15;
    }
  }
  else {
    piVar2 = grim_format_info_lookup(local_c);
    local_c = grim_format_find_supported(param_3,param_2,param_10,piVar2);
    if (local_c == 0) {
      return 0x8876086a;
    }
  }
  if (param_4 == (uint *)0x0) {
    param_3 = (int *)0xffffffff;
  }
  else {
    param_3 = (int *)*param_4;
  }
  if (param_5 == (uint *)0x0) {
    piVar2 = (int *)0xffffffff;
  }
  else {
    piVar2 = (int *)*param_5;
  }
  if (param_6 == (uint *)0x0) {
    local_8 = (int *)0xffffffff;
  }
  else {
    local_8 = (int *)*param_6;
  }
  if (param_3 == (int *)0xffffffff) {
    param_3 = piVar2;
    if (piVar2 != (int *)0xffffffff) goto LAB_1000b030;
    piVar2 = (int *)0x100;
    param_3 = (int *)0x100;
  }
  else {
    if (piVar2 == (int *)0xffffffff) {
      piVar2 = param_3;
    }
LAB_1000b030:
    if (param_3 == (int *)0x0) {
      param_3 = (int *)0x1;
    }
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x1;
    }
  }
  piVar5 = param_3;
  if ((param_10 == 5) && (piVar5 = piVar2, piVar2 < param_3)) {
    piVar2 = param_3;
    piVar5 = param_3;
  }
  param_3 = piVar5;
  if ((local_8 == (int *)0xffffffff) || (local_8 == (int *)0x0)) {
    local_8 = (int *)0x1;
  }
  piVar5 = piVar2;
  if (param_9 == 3) goto LAB_1000b141;
  (**(code **)(*piVar4 + 0x1c))(piVar4,local_e0);
  if (param_10 == 4) {
    if (local_80 < local_8) {
      local_8 = local_80;
    }
    if (local_80 < param_3) {
      param_3 = local_80;
    }
LAB_1000b0d9:
    if (local_80 < piVar2) {
      piVar2 = local_80;
    }
  }
  else {
    if (local_88 < param_3) {
      param_3 = local_88;
    }
    if (local_84 < piVar2) {
      piVar2 = local_84;
    }
    if (param_10 == 3) {
      if ((local_a4 & 0x20) != 0) {
        local_78 = 1;
      }
      if (local_78 != 0) {
        if ((int *)(local_78 * (int)piVar2) < param_3) {
          param_3 = (int *)(local_78 * (int)piVar2);
        }
        local_80 = (int *)(local_78 * (int)param_3);
        goto LAB_1000b0d9;
      }
    }
  }
  piVar1 = local_8;
  piVar4 = param_3;
  if (param_10 == 3) {
    piVar3 = (int *)0x2;
  }
  else if (param_10 == 4) {
    piVar3 = (int *)0x40000;
  }
  else {
    piVar3 = param_3;
    if (param_10 == 5) {
      piVar3 = (int *)0x20000;
    }
  }
  piVar5 = piVar2;
  if ((local_a4 & (uint)piVar3) != 0) {
    piVar5 = (int *)0x1;
    param_3 = (int *)0x1;
    if ((int *)0x1 < piVar4) {
      do {
        param_3 = (int *)((int)param_3 << 1);
      } while (param_3 < piVar4);
    }
    if ((int *)0x1 < piVar2) {
      do {
        piVar5 = (int *)((int)piVar5 << 1);
      } while (piVar5 < piVar2);
    }
    local_8 = (int *)0x1;
    if ((int *)0x1 < piVar1) {
      do {
        local_8 = (int *)((int)local_8 << 1);
      } while (local_8 < piVar1);
    }
  }
LAB_1000b141:
  if ((((local_c == 0x31545844) || (local_c == 0x32545844)) || (local_c == 0x33545844)) ||
     ((local_c == 0x34545844 || (local_c == 0x35545844)))) {
    param_3 = (int *)((int)param_3 + 3U & 0xfffffffc);
    piVar5 = (int *)((int)piVar5 + 3U & 0xfffffffc);
  }
  if (param_10 == 3) {
    piVar4 = (int *)0x4000;
  }
  else if (param_10 == 4) {
    piVar4 = (int *)0x8000;
  }
  else {
    piVar4 = param_3;
    if (param_10 == 5) {
      piVar4 = (int *)0x10000;
    }
  }
  if (param_7 == (uint *)0x0) {
    uVar9 = 0xffffffff;
  }
  else {
    uVar9 = *param_7;
  }
  if ((param_9 == 3) ||
     (((local_a4 & (uint)piVar4) != 0 &&
      (((local_a4 & 0x100) == 0 ||
       (((((uint)param_3 & (int)param_3 - 1U) == 0 && (((uint)piVar5 & (int)piVar5 - 1U) == 0)) &&
        (((uint)local_8 & (int)local_8 - 1U) == 0)))))))) {
    uVar8 = 0;
    for (piVar4 = param_3; piVar4 != (int *)0x0; piVar4 = (int *)((uint)piVar4 >> 1)) {
      uVar8 = uVar8 + 1;
    }
    uVar6 = 0;
    for (piVar4 = piVar5; piVar4 != (int *)0x0; piVar4 = (int *)((uint)piVar4 >> 1)) {
      uVar6 = uVar6 + 1;
    }
    uVar7 = 0;
    for (piVar4 = local_8; piVar4 != (int *)0x0; piVar4 = (int *)((uint)piVar4 >> 1)) {
      uVar7 = uVar7 + 1;
    }
    if (uVar8 <= uVar6) {
      uVar8 = uVar6;
    }
    if ((param_10 == 4) && (uVar8 < uVar7)) {
      uVar8 = uVar7;
    }
    if ((uVar8 < uVar9) || (uVar9 == 0)) {
      uVar9 = uVar8;
    }
  }
  else {
    uVar9 = 1;
  }
  if (param_4 != (uint *)0x0) {
    *param_4 = (uint)param_3;
  }
  if (param_5 != (uint *)0x0) {
    *param_5 = (uint)piVar5;
  }
  if (param_6 != (uint *)0x0) {
    *param_6 = (uint)local_8;
  }
  if (param_7 != (uint *)0x0) {
    *param_7 = uVar9;
  }
  if (param_8 != (int *)0x0) {
    *param_8 = local_c;
  }
  return 0;
}



/* grim_image_validate_dimensions @ 1000b26f */

/* [binja] int32_t __stdcall sub_1000b26f(int32_t** arg1, int32_t* arg2, int32_t* arg3, int32_t*
   arg4, int32_t arg5, int32_t arg6, int32_t arg7) */

int __thiscall
grim_image_validate_dimensions(void *this,int **arg1,int *arg2,int *arg3,int *arg4,int arg5,int arg6,int arg7)

{
  int iVar1;
  
  iVar1 = grim_image_check_dimensions(this,arg5,(int *)arg1,(uint *)arg2,(uint *)arg3,(uint *)0x0,(uint *)arg4,
                       (int *)arg6,arg7,3);
  return iVar1;
}



/* grim_image_load_from_zip @ 1000b297 */

/* [binja] int32_t __stdcall sub_1000b297(int32_t** arg1, int32_t arg2, int32_t arg3, int32_t arg4)
    */

int __thiscall grim_image_load_from_zip(void *this,int **arg1,int arg2,int arg3,int arg4)

{
  int iVar1;
  int arg5;
  int in_stack_00000014;
  undefined4 in_stack_00000018;
  int in_stack_0000001c;
  int in_stack_00000020;
  
  if ((arg1 == (int **)0x0) || (in_stack_00000020 == 0)) {
    iVar1 = -0x7789f794;
  }
  else {
    arg5 = in_stack_00000014;
    if (in_stack_00000014 == -1) {
      arg5 = 0;
    }
    iVar1 = grim_image_validate_dimensions(this,arg1,&arg2,&arg3,&arg4,arg5,(int)&stack0x00000018,in_stack_0000001c);
    if ((-1 < iVar1) &&
       (iVar1 = (*(code *)(*arg1)[0x14])
                          (arg1,arg2,arg3,arg4,arg5,in_stack_00000018,in_stack_0000001c,
                           in_stack_00000020), -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  return iVar1;
}



/* grim_image_header_parse @ 1000b3b5 */

float10 __fastcall grim_image_header_parse(int param_1)

{
  float *in_EAX;
  
  if (param_1 == 1) {
    return (float10)*in_EAX;
  }
  if (param_1 == 2) {
    return (float10)in_EAX[2];
  }
  if (param_1 == 4) {
    return (float10)in_EAX[1];
  }
  if (param_1 != 8) {
    if (param_1 != 0x10) {
      return (float10)0.0;
    }
    return (float10)*in_EAX * (float10)0.2125 +
           (float10)in_EAX[1] * (float10)0.7154 + (float10)in_EAX[2] * (float10)0.0721;
  }
  return (float10)in_EAX[3];
}



/* grim_image_load_from_stream @ 1000b3fe */

/* [binja] int32_t __stdcall sub_1000b3fe(int32_t* arg1, int32_t* arg2, int32_t arg3, int32_t arg4,
   float arg5) */

int grim_image_load_from_stream(int *arg1,int *arg2,int arg3,int arg4,float arg5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  float *pfVar8;
  float *extraout_EDX;
  float *pfVar9;
  int extraout_EDX_00;
  float *extraout_EDX_01;
  int iVar10;
  int unaff_ESI;
  int iVar11;
  float10 fVar12;
  float in_stack_00000018;
  uint local_1a0 [19];
  uint local_154 [19];
  int local_108 [6];
  int local_f0;
  uint local_ec;
  int local_e8 [4];
  int local_d8 [4];
  undefined1 local_c8 [24];
  int local_b0;
  float local_a8 [8];
  float local_88;
  float local_84;
  float local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  int local_70 [6];
  int local_58;
  uint local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint local_44;
  void *local_40;
  void *local_3c;
  int *local_38;
  float local_34;
  int *local_30;
  void *local_2c;
  void *local_28;
  float *local_24;
  float *local_20;
  int *local_1c;
  int *local_18;
  float local_14;
  uint local_10;
  float *local_c;
  uint local_8;
  
  local_30 = (int *)0x0;
  local_38 = (int *)0x0;
  local_18 = (int *)0x0;
  local_1c = (int *)0x0;
  grim_zip_reader_init(local_d8);
  grim_zip_reader_init(local_e8);
  if (arg1 == (int *)0x0) {
    iVar10 = -0x7789f794;
    goto LAB_1000bbde;
  }
  if (arg2 != (int *)0x0) {
    if (arg4 == -1) {
      arg4 = 0;
    }
    if ((arg4 & 0xffe4ffffU) == 0) {
      if (arg5 == -NAN) {
        arg5 = 1.4013e-45;
      }
      if ((arg5 != 0.0) &&
         (((((uint)arg5 < 3 || (arg5 == 5.60519e-45)) || (arg5 == 1.12104e-44)) ||
          (arg5 == 2.24208e-44)))) {
        iVar10 = (**(code **)(*arg1 + 0x38))(arg1,0,local_108);
        if ((iVar10 < 0) || (iVar10 = (**(code **)(*arg2 + 0x38))(arg2,0,local_70), iVar10 < 0)) {
          iVar10 = -0x7fffbffb;
          goto LAB_1000bbde;
        }
        piVar5 = grim_format_info_lookup(local_70[0]);
        piVar6 = grim_format_info_lookup(local_108[0]);
        if ((((*piVar5 != 0) && (*piVar6 != 0)) &&
            ((((iVar10 = piVar5[1], iVar10 == 0 || (iVar10 == 1)) ||
              ((iVar10 == 2 || (iVar10 == 4)))) &&
             ((((piVar6[1] == 0 && (1 < (uint)piVar6[5])) && (1 < (uint)piVar6[6])) &&
              ((1 < (uint)piVar6[7] && (local_58 == local_f0)))))))) && (local_54 == local_ec)) {
          uVar7 = (**(code **)(*arg2 + 0x34))(arg2);
          local_44 = (**(code **)(*arg1 + 0x34))(arg1);
          if (uVar7 == local_44) {
            iVar10 = (**(code **)(*arg1 + 0x38))(arg1,0,local_c8);
            iVar11 = local_b0;
            if (-1 < iVar10) {
              local_28 = operator_new(local_b0 << 4);
              if (local_28 == (void *)0x0) {
                local_28 = (void *)0x0;
              }
              else {
                _vector_constructor_iterator_
                          (local_28,0x10,iVar11,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
              }
              iVar10 = local_b0;
              local_3c = operator_new(local_b0 << 4);
              if (local_3c == (void *)0x0) {
                local_3c = (void *)0x0;
              }
              else {
                _vector_constructor_iterator_
                          (local_3c,0x10,iVar10,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
              }
              iVar10 = local_b0;
              local_40 = operator_new(local_b0 << 4);
              if (local_40 == (void *)0x0) {
                local_40 = (void *)0x0;
              }
              else {
                _vector_constructor_iterator_
                          (local_40,0x10,iVar10,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
              }
              iVar10 = local_b0;
              local_2c = operator_new(local_b0 << 4);
              if (local_2c == (void *)0x0) {
                local_2c = (void *)0x0;
              }
              else {
                _vector_constructor_iterator_
                          (local_2c,0x10,iVar10,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
              }
              local_20 = operator_new(local_b0 * 4 + 8);
              local_c = operator_new(local_b0 * 4 + 8);
              local_24 = operator_new(local_b0 * 4 + 8);
              if ((((local_3c == (void *)0x0) || (local_40 == (void *)0x0)) ||
                  ((local_2c == (void *)0x0 ||
                   (((local_28 == (void *)0x0 || (local_20 == (float *)0x0)) ||
                    (local_c == (float *)0x0)))))) || (local_24 == (float *)0x0)) {
                iVar10 = -0x7ff8fff2;
LAB_1000bb62:
                piVar5 = local_38;
                if (local_30 != (int *)0x0) {
                  (**(code **)*local_30)(1);
                }
                if (piVar5 != (int *)0x0) {
                  (**(code **)*piVar5)(1);
                }
              }
              else {
                local_10 = 0;
                if (local_44 != 0) {
                  do {
                    (**(code **)(*arg1 + 0x3c))(arg1,local_10,&local_1c);
                    (**(code **)(*arg2 + 0x3c))(arg2,local_10,&local_18);
                    if (local_10 == 0) {
                      iVar10 = 0x20000;
                    }
                    else {
                      iVar10 = 0;
                    }
                    iVar10 = grim_zip_read_header(local_d8,(char *)local_1a0,local_1c,(int *)0x0,0,
                                          (int *)0x0,iVar10,unaff_ESI);
                    if (iVar10 < 0) goto LAB_1000bb7b;
                    if (arg1 == arg2) {
                      iVar10 = 0x10001;
                    }
                    else {
                      iVar10 = 1;
                    }
                    iVar10 = grim_zip_read_header(local_e8,(char *)local_154,local_18,(int *)0x0,0,
                                          (int *)0x0,iVar10,unaff_ESI);
                    if (((iVar10 < 0) ||
                        (iVar10 = (**(code **)(*arg1 + 0x38))(arg1,local_10,local_108), iVar10 < 0))
                       || (iVar10 = (**(code **)(*arg2 + 0x38))(arg2,local_10,local_70), iVar10 < 0)
                       ) goto LAB_1000bb7b;
                    piVar5 = grim_pixel_format_create(local_154);
                    local_30 = piVar5;
                    local_38 = grim_pixel_format_create(local_1a0);
                    if ((piVar5 == (int *)0x0) || (local_38 == (int *)0x0)) {
                      iVar10 = -0x7fffbffb;
                      goto LAB_1000bb62;
                    }
                    (**(code **)(*piVar5 + 4))(local_54 - 1,0,local_28);
                    (**(code **)(*piVar5 + 4))(0,0,local_3c);
                    fVar12 = grim_image_header_parse((int)arg5);
                    pfVar9 = local_20;
                    *local_20 = (float)fVar12;
                    fVar12 = grim_image_header_parse((int)arg5);
                    *local_c = (float)fVar12;
                    fVar12 = grim_image_header_parse((int)arg5);
                    pfVar9[local_58 + 1] = (float)fVar12;
                    fVar12 = grim_image_header_parse((int)arg5);
                    extraout_EDX[local_58 + 1] = (float)fVar12;
                    local_8 = 0;
                    if (0 < local_58) {
                      pfVar8 = extraout_EDX;
                      do {
                        pfVar8 = pfVar8 + 1;
                        fVar12 = grim_image_header_parse((int)arg5);
                        *(float *)(((int)pfVar9 - (int)extraout_EDX) + (int)pfVar8) = (float)fVar12;
                        fVar12 = grim_image_header_parse((int)arg5);
                        *pfVar8 = (float)fVar12;
                        local_8 = local_8 + 1;
                      } while ((int)local_8 < local_58);
                    }
                    local_8 = 0;
                    if (0 < (int)local_54) {
                      do {
                        local_78 = local_8 + 1;
                        pfVar9 = (float *)(local_78 % local_54);
                        (**(code **)(*local_30 + 4))(pfVar9,0,local_40);
                        fVar12 = grim_image_header_parse((int)arg5);
                        *local_24 = (float)fVar12;
                        fVar12 = grim_image_header_parse((int)arg5);
                        iVar10 = 0;
                        *(float *)(extraout_EDX_00 + 4 + local_58 * 4) = (float)fVar12;
                        iVar11 = 0;
                        if (0 < local_58) {
                          do {
                            fVar12 = grim_image_header_parse((int)arg5);
                            *extraout_EDX_01 = (float)fVar12;
                            iVar11 = iVar11 + 1;
                          } while (iVar11 < local_58);
                          if (0 < local_58) {
                            local_74 = arg4 & 0x100000;
                            local_80 = 1.0;
                            local_7c = arg4 & 0x80000;
                            do {
                              iVar11 = 0;
                              local_14 = 0.0;
                              if ((iVar10 != 0) || ((arg4 & 0x10000U) == 0)) {
                                local_14 = local_c[iVar10 + 1] + local_c[iVar10];
                                iVar11 = 1;
                              }
                              if ((iVar10 < local_58 + -1) || ((arg4 & 0x10000U) == 0)) {
                                iVar11 = iVar11 + 1;
                                local_14 = local_14 - (local_c[iVar10 + 2] + local_c[iVar10 + 1]);
                              }
                              local_14 = local_14 * in_stack_00000018;
                              if (iVar11 != 1) {
                                local_14 = local_14 * 0.5;
                              }
                              iVar11 = 0;
                              local_34 = 0.0;
                              if ((local_8 != 0) || ((arg4 & 0x20000U) == 0)) {
                                local_34 = local_c[iVar10 + 1] + local_20[iVar10 + 1];
                                iVar11 = 1;
                              }
                              if (((int)local_8 < (int)(local_54 - 1)) || ((arg4 & 0x20000U) == 0))
                              {
                                iVar11 = iVar11 + 1;
                                local_34 = local_34 - (local_24[iVar10 + 1] + local_c[iVar10 + 1]);
                              }
                              if (iVar11 == 1) {
                                fVar1 = local_34 * in_stack_00000018;
                              }
                              else {
                                fVar1 = local_34 * in_stack_00000018 * 0.5;
                              }
                              pfVar9 = &local_50;
                              local_88 = fVar1 * 0.0 - local_14 * -1.0;
                              local_84 = local_14 * 0.0 - fVar1 * -1.0;
                              local_48 = local_80;
                              local_50 = local_88;
                              local_4c = local_84;
                              thunk_vec3_normalize();
                              local_14 = 1.0;
                              if (local_74 != 0) {
                                local_a8[0] = local_20[iVar10];
                                local_a8[1] = local_20[iVar10 + 1];
                                local_a8[2] = local_20[iVar10 + 2];
                                local_a8[4] = local_c[iVar10 + 2];
                                local_a8[3] = local_c[iVar10];
                                local_a8[7] = local_24[iVar10 + 2];
                                local_a8[5] = local_24[iVar10];
                                fVar3 = 0.0;
                                fVar1 = (local_c + iVar10)[1];
                                local_a8[6] = local_24[iVar10 + 1];
                                iVar11 = 0;
                                do {
                                  pfVar8 = local_a8 + iVar11;
                                  fVar2 = *pfVar8 - fVar1;
                                  *pfVar8 = fVar2;
                                  if (fVar2 < 0.0) {
                                    *pfVar8 = 0.0;
                                  }
                                  iVar11 = iVar11 + 1;
                                  fVar3 = fVar3 + *pfVar8;
                                } while (iVar11 < 8);
                                fVar1 = fVar3 * in_stack_00000018 * 0.125;
                                if (0.0 < fVar1) {
                                  local_14 = SQRT(fVar1 * fVar1 + 1.0);
                                  local_14 = (local_14 - fVar1) / local_14;
                                }
                              }
                              pfVar8 = (float *)(iVar10 * 0x10 + (int)local_2c);
                              if (local_7c == 0) {
                                *pfVar8 = (local_50 + 1.0) * 0.5;
                                pfVar8[1] = (local_4c + 1.0) * 0.5;
                                fVar1 = (local_48 + 1.0) * 0.5;
                              }
                              else {
                                *pfVar8 = 0.5 - local_50 * 0.5;
                                pfVar8[1] = 0.5 - local_4c * 0.5;
                                fVar1 = 0.5 - local_48 * 0.5;
                              }
                              iVar10 = iVar10 + 1;
                              pfVar8[2] = fVar1;
                              pfVar8[3] = local_14;
                            } while (iVar10 < local_58);
                          }
                        }
                        (**(code **)(*local_38 + 8))(local_8,0,local_2c,pfVar9);
                        pfVar8 = local_20;
                        pfVar4 = local_24;
                        pfVar9 = local_c;
                        local_20 = local_c;
                        local_c = local_24;
                        local_24 = pfVar8;
                        local_8 = local_78;
                      } while ((int)local_78 < (int)local_54);
                    }
                    (**(code **)*local_30)(1);
                    (**(code **)*local_38)(1);
                    if (local_18 != (int *)0x0) {
                      (**(code **)(*local_18 + 8))(local_18);
                      local_18 = (int *)0x0;
                    }
                    if (local_1c != (int *)0x0) {
                      (**(code **)(*local_1c + 8))(local_1c);
                      local_1c = (int *)0x0;
                    }
                    local_10 = local_10 + 1;
                  } while (local_10 < local_44);
                }
                iVar10 = 0;
              }
LAB_1000bb7b:
              if (local_18 != (int *)0x0) {
                (**(code **)(*local_18 + 8))(local_18);
                local_18 = (int *)0x0;
              }
              if (local_1c != (int *)0x0) {
                (**(code **)(*local_1c + 8))(local_1c);
                local_1c = (int *)0x0;
              }
              operator_delete(local_28);
              operator_delete(local_3c);
              operator_delete(local_40);
              operator_delete(local_2c);
              operator_delete(local_20);
              operator_delete(local_c);
              operator_delete(local_24);
            }
            goto LAB_1000bbde;
          }
        }
      }
    }
  }
  iVar10 = -0x7789f794;
LAB_1000bbde:
  grim_zip_reader_close((char *)local_e8);
  grim_zip_reader_close((char *)local_d8);
  return iVar10;
}



/* grim_image_blit_convert @ 1000f5a9 */

/* [binja] float* __stdcall sub_1000f5a9(float* arg1, int32_t arg2, int32_t* arg3, int32_t* arg4,
   int32_t* arg5, int32_t* arg6) */

float * grim_image_blit_convert(float *arg1,int arg2,int *arg3,int *arg4,int *arg5,int *arg6)

{
  float fVar1;
  float fVar2;
  
  switch(((arg6 != (int *)0x0) << 1 | arg5 != (int *)0x0) << 1 | arg4 != (int *)0x0) {
  case '\0':
    break;
  case '\x01':
    break;
  case '\x02':
    break;
  case '\x03':
    goto code_r0x1000f67a;
  case '\x04':
    break;
  case '\x05':
    goto code_r0x1000f67a;
  case '\x06':
    goto code_r0x1000f67a;
  case '\a':
    thunk_matrix_rotate();
code_r0x1000f67a:
    thunk_matrix_rotate();
  }
  thunk_grim_d3d_set_z_enable();
  if (arg3 != (int *)0x0) {
    fVar2 = (float)arg3[2];
    if (arg3[2] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar1 = (float)*arg3;
    if (*arg3 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    *arg1 = fVar1 + fVar2 * (*arg1 + 1.0) * 0.5;
    fVar2 = (float)arg3[3];
    if (arg3[3] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar1 = (float)arg3[1];
    if (arg3[1] < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    arg1[1] = fVar1 + fVar2 * (1.0 - arg1[1]) * 0.5;
    arg1[2] = ((float)arg3[5] - (float)arg3[4]) * arg1[2] + (float)arg3[4];
  }
  return arg1;
}



/* grim_image_blit_dxt @ 1000f8dc */

/* [binja] float* __stdcall sub_1000f8dc(float* arg1, float arg2) */

float * grim_image_blit_dxt(float *arg1,float arg2)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  fVar2 = *(float *)((int)arg2 + 0xc) * *(float *)((int)arg2 + 0xc) +
          *(float *)((int)arg2 + 8) * *(float *)((int)arg2 + 8) +
          *(float *)((int)arg2 + 4) * *(float *)((int)arg2 + 4) + *(float *)arg2 * *(float *)arg2;
  iVar3 = float_near_equal(fVar2,1.0);
  if (iVar3 == 0) {
    if (fVar2 <= 1.1754944e-38) {
      *arg1 = 0.0;
      arg1[1] = 0.0;
      arg1[2] = 0.0;
      arg1[3] = 0.0;
      return arg1;
    }
    fVar2 = 1.0 / SQRT(fVar2);
    local_14 = fVar2 * *(float *)arg2;
    local_10 = fVar2 * *(float *)((int)arg2 + 4);
    local_c = fVar2 * *(float *)((int)arg2 + 8);
    pfVar1 = (float *)((int)arg2 + 0xc);
    arg2 = (float)&local_14;
    local_8 = fVar2 * *pfVar1;
  }
  else if (arg1 == (float *)arg2) {
    return arg1;
  }
  *arg1 = *(float *)arg2;
  arg1[1] = *(float *)((int)arg2 + 4);
  arg1[2] = *(float *)((int)arg2 + 8);
  arg1[3] = *(float *)((int)arg2 + 0xc);
  return arg1;
}



/* grim_image_blit_dispatch @ 1000f995 */

/* [binja] int32_t __stdcall sub_1000f995(int32_t arg1, float arg2, float arg3, float arg4) */

int grim_image_blit_dispatch(int arg1,float arg2,float arg3,float arg4)

{
  undefined1 local_14 [16];
  
  thunk_FUN_1000e8cf((float)local_14,arg2,arg3);
  thunk_matrix_scale();
  return arg1;
}



/* grim_image_surface_lock_and_blit @ 1000f9ce */

/* [binja] float* __stdcall sub_1000f9ce(float* arg1, float* arg2, void* arg3, int32_t* arg4, float*
   arg5, int32_t arg6, float* arg7) */

float * grim_image_surface_lock_and_blit(float *arg1,float *arg2,void *arg3,int *arg4,float *arg5,int arg6,float *arg7)

{
  float fVar1;
  
  if (arg4 == (int *)0x0) {
    arg1[0xe] = 0.0;
    arg1[0xd] = 0.0;
    arg1[0xc] = 0.0;
    arg1[0xb] = 0.0;
    arg1[9] = 0.0;
    arg1[8] = 0.0;
    arg1[7] = 0.0;
    arg1[6] = 0.0;
    arg1[4] = 0.0;
    arg1[3] = 0.0;
    arg1[2] = 0.0;
    arg1[1] = 0.0;
    arg1[0xf] = 1.0;
    arg1[10] = 1.0;
    arg1[5] = 1.0;
    *arg1 = 1.0;
  }
  else if (arg3 == (void *)0x0) {
    arg1[0xe] = 0.0;
    arg1[0xd] = 0.0;
    arg1[0xc] = 0.0;
    arg1[0xb] = 0.0;
    arg1[9] = 0.0;
    arg1[8] = 0.0;
    arg1[7] = 0.0;
    arg1[6] = 0.0;
    arg1[4] = 0.0;
    arg1[3] = 0.0;
    arg1[2] = 0.0;
    arg1[1] = 0.0;
    *arg1 = (float)*arg4;
    arg1[5] = (float)arg4[1];
    fVar1 = (float)arg4[2];
    arg1[0xf] = 1.0;
    arg1[10] = fVar1;
  }
  else {
    thunk_matrix_scale();
    if (arg2 == (float *)0x0) {
      thunk_grim_d3d_set_dither_enable();
      thunk_matrix_rotate();
      thunk_matrix_rotate();
    }
    else {
      thunk_grim_d3d_set_dither_enable();
      arg1[0xe] = 0.0;
      arg1[0xd] = 0.0;
      arg1[0xc] = 0.0;
      arg1[0xb] = 0.0;
      arg1[9] = 0.0;
      arg1[8] = 0.0;
      arg1[7] = 0.0;
      arg1[6] = 0.0;
      arg1[4] = 0.0;
      arg1[3] = 0.0;
      arg1[2] = 0.0;
      arg1[1] = 0.0;
      arg1[0xf] = 1.0;
      arg1[10] = 1.0;
      arg1[5] = 1.0;
      *arg1 = 1.0;
      arg1[0xc] = -*arg2;
      arg1[0xd] = -arg2[1];
      arg1[0xe] = -arg2[2];
      thunk_matrix_rotate();
      thunk_matrix_rotate();
      thunk_matrix_rotate();
      arg1[0xc] = arg1[0xc] + *arg2;
      arg1[0xd] = arg2[1] + arg1[0xd];
      arg1[0xe] = arg1[0xe] + arg2[2];
    }
  }
  if (arg6 != 0) {
    thunk_matrix_scale();
    if (arg5 == (float *)0x0) {
      thunk_matrix_rotate();
    }
    else {
      arg1[0xc] = arg1[0xc] - *arg5;
      arg1[0xd] = arg1[0xd] - arg5[1];
      arg1[0xe] = arg1[0xe] - arg5[2];
      thunk_matrix_rotate();
      arg1[0xc] = arg1[0xc] + *arg5;
      arg1[0xd] = arg1[0xd] + arg5[1];
      arg1[0xe] = arg1[0xe] + arg5[2];
    }
  }
  if (arg7 != (float *)0x0) {
    arg1[0xc] = arg1[0xc] + *arg7;
    arg1[0xd] = arg7[1] + arg1[0xd];
    arg1[0xe] = arg7[2] + arg1[0xe];
  }
  return arg1;
}



/* grim_image_create_mipmap_chain @ 1000fc82 */

/* [binja] float* __stdcall sub_1000fc82(float* arg1, float* arg2, int32_t arg3) */

float * grim_image_create_mipmap_chain(float *arg1,float *arg2,int arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  thunk_FUN_1000ef90();
  fVar1 = local_c * arg2[2] + local_8 * arg2[3] + local_14 * *arg2 + local_10 * arg2[1];
  fVar4 = -local_14;
  fVar3 = -local_10;
  fVar2 = -local_c;
  fVar5 = -local_8;
  *arg1 = fVar4 * *arg2 + fVar1;
  arg1[4] = fVar3 * *arg2;
  arg1[8] = fVar2 * *arg2;
  arg1[0xc] = fVar5 * *arg2;
  arg1[1] = fVar4 * arg2[1];
  arg1[5] = fVar3 * arg2[1] + fVar1;
  arg1[9] = fVar2 * arg2[1];
  arg1[0xd] = fVar5 * arg2[1];
  arg1[2] = fVar4 * arg2[2];
  arg1[6] = fVar3 * arg2[2];
  arg1[10] = fVar2 * arg2[2] + fVar1;
  arg1[0xe] = fVar5 * arg2[2];
  arg1[3] = fVar4 * arg2[3];
  arg1[7] = fVar3 * arg2[3];
  arg1[0xb] = fVar2 * arg2[3];
  arg1[0xf] = fVar5 * arg2[3] + fVar1;
  return arg1;
}



/* grim_image_load_and_create_texture @ 1000fd5c */

/* [binja] float* __stdcall sub_1000fd5c(float* arg1, float arg2) */

float * grim_image_load_and_create_texture(float *arg1,float arg2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  thunk_FUN_1000ef90();
  fVar1 = local_14 * -2.0;
  fVar3 = local_10 * -2.0;
  fVar2 = local_c * -2.0;
  *arg1 = local_14 * fVar1 + 1.0;
  arg1[1] = fVar3 * local_14;
  arg1[2] = fVar2 * local_14;
  arg1[3] = 0.0;
  arg1[4] = local_10 * fVar1;
  arg1[5] = local_10 * fVar3 + 1.0;
  arg1[6] = fVar2 * local_10;
  arg1[7] = 0.0;
  arg1[8] = local_c * fVar1;
  arg1[9] = local_c * fVar3;
  arg1[10] = local_c * fVar2 + 1.0;
  arg1[0xb] = 0.0;
  arg1[0xc] = local_8 * fVar1;
  arg1[0xd] = local_8 * fVar3;
  arg1[0xe] = local_8 * fVar2;
  arg1[0xf] = 1.0;
  return arg1;
}



/* grim_bmp_header_parse @ 100102f7 */

/* [binja] void* __thiscall sub_100102f7(void* arg1, char arg2) */

void * __thiscall grim_bmp_header_parse(void *this,void *arg1,char arg2)

{
  grim_file_stream_close(this);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}



/* grim_bmp_pixel_data_decode @ 100103d6 */

/* [binja] int32_t __thiscall sub_100103d6(int32_t* arg1, void* arg2, void* arg3) */

int __thiscall grim_bmp_pixel_data_decode(void *this,int *arg1,void *arg2,void *arg3)

{
  void *pvVar1;
  byte bVar2;
  ushort uVar3;
  int *piVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *pvVar9;
  undefined1 *puVar10;
  int *piVar11;
  uint uVar12;
  byte *pbVar13;
  byte *pbVar14;
  int iVar15;
  uint uVar16;
  int *piVar17;
  byte *pbVar18;
  byte *pbVar19;
  int *piVar20;
  byte *pbVar21;
  byte *pbVar22;
  byte *pbVar23;
  byte *pbVar24;
  int local_1c;
  byte *local_14;
  
  piVar17 = arg1;
  if (arg2 < (void *)0x28) {
    return -0x7fffbffb;
  }
  uVar12 = *arg1;
  if (uVar12 < 0x28) {
    return -0x7fffbffb;
  }
  piVar4 = (int *)arg1[1];
  iVar6 = arg1[2];
  if (iVar6 < 1) {
    iVar6 = -iVar6;
  }
  uVar3 = *(ushort *)((int)arg1 + 0xe);
  iVar7 = arg1[8];
  if ((uVar3 < 9) && (iVar7 == 0)) {
    iVar7 = 1 << ((byte)uVar3 & 0x1f);
  }
  pvVar1 = (void *)(uVar12 + iVar7 * 4);
  if (arg2 < pvVar1) {
    return -0x7fffbffb;
  }
  if ((short)arg1[3] != 1) {
    return -0x7fffbffb;
  }
  if (((arg1[2] < 0) && (arg1[4] != 0)) && (arg1[4] != 3)) {
    return -0x7fffbffb;
  }
  if ((uint)arg1[4] < 3) {
    arg1 = (int *)(uint)uVar3;
    if (((arg1 == (int *)0x1) || (arg1 == (int *)0x4)) || (arg1 == (int *)0x8)) {
      arg2 = (void *)0x29;
      goto LAB_100106ec;
    }
    if (arg1 == (int *)0x10) goto LAB_100106dc;
    if (arg1 == (int *)0x18) goto LAB_1001058c;
    if (arg1 != (int *)0x20) {
      return -0x7fffbffb;
    }
  }
  else {
    if (arg1[4] != 3) {
      return -0x7fffbfff;
    }
    if (uVar12 < 0x6c) {
      arg2 = (void *)0x0;
      piVar20 = (int *)(uVar12 + (int)arg1);
      iVar7 = piVar20[2];
      iVar15 = piVar20[1];
      iVar8 = *piVar20;
    }
    else {
      arg2 = (void *)arg1[0xd];
      iVar7 = arg1[0xc];
      iVar15 = arg1[0xb];
      iVar8 = arg1[10];
    }
    arg1 = (int *)(uint)*(ushort *)((int)arg1 + 0xe);
    if (arg1 == (int *)0x10) {
      if (iVar7 == 0xff) {
        if (iVar15 != 0xff) {
          return -0x7fffbffb;
        }
        if (iVar8 != 0xff) {
          return -0x7fffbffb;
        }
        if (arg2 != (void *)0xff00) {
          return -0x7fffbffb;
        }
        arg2 = (void *)0x33;
        goto LAB_100106ec;
      }
      if (iVar7 != 0x1f) {
        if (iVar7 == 0xf) {
          if (iVar15 != 0xf0) {
            return -0x7fffbffb;
          }
          if (iVar8 != 0xf00) {
            return -0x7fffbffb;
          }
          if (arg2 == (void *)0xf000) {
            arg2 = (void *)0x1a;
          }
          else {
            if (arg2 != (void *)0x0) {
              return -0x7fffbffb;
            }
            arg2 = (void *)0x1e;
          }
        }
        else {
          if (iVar7 != 3) {
            return -0x7fffbffb;
          }
          if (iVar15 != 0x1c) {
            return -0x7fffbffb;
          }
          if (iVar8 != 0xe0) {
            return -0x7fffbffb;
          }
          if (arg2 != (void *)0xff00) {
            return -0x7fffbffb;
          }
          arg2 = (void *)0x1d;
        }
        goto LAB_100106ec;
      }
      if (iVar15 == 0x7e0) {
        if (iVar8 != 0xf800) {
          return -0x7fffbffb;
        }
        if (arg2 != (void *)0x0) {
          return -0x7fffbffb;
        }
        arg2 = (void *)0x17;
        goto LAB_100106ec;
      }
      if (iVar15 != 0x3e0) {
        return -0x7fffbffb;
      }
      if (iVar8 != 0x7c00) {
        return -0x7fffbffb;
      }
      if (arg2 != (void *)0x0) {
        if (arg2 != (void *)0x8000) {
          return -0x7fffbffb;
        }
        arg2 = (void *)0x19;
        goto LAB_100106ec;
      }
LAB_100106dc:
      arg2 = (void *)0x18;
      goto LAB_100106ec;
    }
    if (arg1 == (int *)0x18) {
      if (iVar7 != 0xff) {
        return -0x7fffbffb;
      }
      if (iVar15 != 0xff00) {
        return -0x7fffbffb;
      }
      if (iVar8 != 0xff0000) {
        return -0x7fffbffb;
      }
      if (arg2 != (void *)0x0) {
        return -0x7fffbffb;
      }
LAB_1001058c:
      arg2 = (void *)0x14;
      goto LAB_100106ec;
    }
    if (arg1 != (int *)0x20) {
      return -0x7fffbffb;
    }
    if (iVar7 != 0xff) {
      if (iVar7 == 0x3ff00000) {
        if (iVar15 != 0xffc00) {
          return -0x7fffbffb;
        }
        if (iVar8 != 0x3ff) {
          return -0x7fffbffb;
        }
        if (arg2 != (void *)0xc0000000) {
          return -0x7fffbffb;
        }
        arg2 = (void *)0x1f;
      }
      else {
        if (iVar7 != 0) {
          return -0x7fffbffb;
        }
        if (iVar15 != -0x10000) {
          return -0x7fffbffb;
        }
        if (iVar8 != 0xffff) {
          return -0x7fffbffb;
        }
        if (arg2 != (void *)0x0) {
          return -0x7fffbffb;
        }
        arg2 = (void *)0x22;
      }
      goto LAB_100106ec;
    }
    if (iVar15 != 0xff00) {
      return -0x7fffbffb;
    }
    if (iVar8 != 0xff0000) {
      return -0x7fffbffb;
    }
    if (arg2 != (void *)0x0) {
      if (arg2 != (void *)0xff000000) {
        return -0x7fffbffb;
      }
      arg2 = (void *)0x15;
      goto LAB_100106ec;
    }
  }
  arg2 = (void *)0x16;
LAB_100106ec:
  if ((*(int *)((int)this + 0x40) != 0) && (arg2 == (void *)0x29)) {
    piVar20 = (int *)piVar17[8];
    if (piVar20 == (int *)0x0) {
      piVar20 = (int *)(1 << ((byte)arg1 & 0x1f));
    }
    *(undefined4 *)((int)this + 0x3c) = 1;
    pvVar9 = operator_new(0x400);
    *(void **)((int)this + 8) = pvVar9;
    if (pvVar9 == (void *)0x0) {
      return -0x7ff8fff2;
    }
    arg1 = (int *)0x0;
    puVar10 = (undefined1 *)(*piVar17 + (int)piVar17);
    if (piVar20 != (int *)0x0) {
      do {
        iVar7 = (int)arg1 * 4;
        *(undefined1 *)(iVar7 + *(int *)((int)this + 8)) = puVar10[2];
        *(undefined1 *)(iVar7 + 1 + *(int *)((int)this + 8)) = puVar10[1];
        *(undefined1 *)(iVar7 + 2 + *(int *)((int)this + 8)) = *puVar10;
        *(undefined1 *)(iVar7 + 3 + *(int *)((int)this + 8)) = 0xff;
        arg1 = (int *)((int)arg1 + 1);
        puVar10 = puVar10 + 4;
      } while (arg1 < piVar20);
    }
    for (; piVar20 < (int *)0x100; piVar20 = (int *)((int)piVar20 + 1)) {
      iVar7 = (int)piVar20 * 4;
      *(undefined1 *)(iVar7 + *(int *)((int)this + 8)) = 0xff;
      *(undefined1 *)(iVar7 + 1 + *(int *)((int)this + 8)) = 0xff;
      *(undefined1 *)(iVar7 + 2 + *(int *)((int)this + 8)) = 0xff;
      *(undefined1 *)(iVar7 + 3 + *(int *)((int)this + 8)) = 0xff;
    }
  }
  uVar3 = *(ushort *)((int)piVar17 + 0xe);
  piVar20 = piVar4;
  if (uVar3 == 1) {
    piVar11 = (int *)((int)piVar4 + 7U >> 3);
  }
  else if (uVar3 == 4) {
    piVar11 = (int *)((int)piVar4 + 1U >> 1);
  }
  else {
    piVar11 = (int *)((uint)(uVar3 >> 3) * (int)piVar4);
    piVar20 = piVar11;
  }
  uVar16 = (int)piVar11 + 3U & 0xfffffffc;
  *(void **)this = arg2;
  uVar12 = (int)piVar20 + 3U & 0xfffffffc;
  *(int **)((int)this + 0xc) = piVar4;
  *(uint *)((int)this + 0x30) = uVar12;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(int *)((int)this + 0x10) = iVar6;
  *(undefined4 *)((int)this + 0x14) = 1;
  if (*(int *)((int)this + 0x40) != 0) {
    if ((piVar17[2] < 0) && (7 < *(ushort *)((int)piVar17 + 0xe))) {
      *(undefined4 *)((int)this + 0x38) = 0;
      *(int *)((int)this + 4) = (int)pvVar1 + (int)piVar17;
    }
    else {
      *(undefined4 *)((int)this + 0x38) = 1;
      pbVar13 = operator_new(uVar12 * iVar6);
      *(byte **)((int)this + 4) = pbVar13;
      if (pbVar13 == (byte *)0x0) {
        return -0x7ff8fff2;
      }
      pbVar18 = (byte *)((int)pvVar1 + (int)piVar17);
      iVar7 = *(int *)((int)this + 0x30);
      pbVar21 = pbVar13;
      local_1c = iVar7;
      if (-1 < piVar17[2]) {
        pbVar21 = pbVar13 + (iVar6 + -1) * iVar7;
        local_1c = -iVar7;
      }
      pbVar14 = pbVar13 + iVar7 * iVar6;
      local_14 = pbVar21;
      if (piVar17[4] == 2) {
        while (pbVar13 <= pbVar21) {
          if (*pbVar18 == 0) {
            bVar5 = pbVar18[1];
            if (bVar5 == 0) {
              pbVar21 = local_14 + -*(int *)((int)this + 0x30);
              local_14 = pbVar21;
            }
            else if (bVar5 == 1) {
              pbVar21 = pbVar13 + -*(int *)((int)this + 0x30);
            }
            else if (bVar5 == 2) {
              pbVar14 = pbVar18 + 3;
              pbVar18 = pbVar18 + 2;
              pbVar21 = pbVar21 + ((uint)*pbVar18 - (uint)*pbVar14 * *(int *)((int)this + 0x30));
            }
            else {
              uVar12 = 0;
              if (bVar5 != 0) {
                do {
                  if ((uVar12 & 1) == 0) {
                    bVar5 = pbVar18[((int)uVar12 >> 1) + 2] >> 4;
                  }
                  else {
                    bVar5 = pbVar18[((int)uVar12 >> 1) + 2] & 0xf;
                  }
                  pbVar21[uVar12] = bVar5;
                  uVar12 = uVar12 + 1;
                } while ((int)uVar12 < (int)(uint)pbVar18[1]);
              }
              pbVar21 = pbVar21 + pbVar18[1];
              pbVar18 = pbVar18 + ((pbVar18[1] >> 1) + 1 & 0xfffffffe);
            }
          }
          else {
            uVar12 = 0;
            if (*pbVar18 != 0) {
              do {
                if ((uVar12 & 1) == 0) {
                  bVar5 = pbVar18[1] >> 4;
                }
                else {
                  bVar5 = pbVar18[1] & 0xf;
                }
                pbVar21[uVar12] = bVar5;
                uVar12 = uVar12 + 1;
              } while ((int)uVar12 < (int)(uint)*pbVar18);
            }
            pbVar21 = pbVar21 + *pbVar18;
          }
          pbVar18 = pbVar18 + 2;
        }
      }
      else if (piVar17[4] == 1) {
        while (pbVar13 <= pbVar21) {
          bVar5 = *pbVar18;
          if (bVar5 == 0) {
            uVar12 = (uint)pbVar18[1];
            if (uVar12 == 0) {
              pbVar21 = local_14 + -*(int *)((int)this + 0x30);
              local_14 = pbVar21;
            }
            else if (uVar12 == 1) {
              pbVar21 = pbVar13 + -*(int *)((int)this + 0x30);
            }
            else {
              if (uVar12 != 2) {
                pbVar14 = pbVar18 + 2;
                pbVar19 = pbVar21;
                for (uVar16 = (uint)(pbVar18[1] >> 2); uVar16 != 0; uVar16 = uVar16 - 1) {
                  *(undefined4 *)pbVar19 = *(undefined4 *)pbVar14;
                  pbVar14 = pbVar14 + 4;
                  pbVar19 = pbVar19 + 4;
                }
                for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *pbVar19 = *pbVar14;
                  pbVar14 = pbVar14 + 1;
                  pbVar19 = pbVar19 + 1;
                }
                uVar12 = (uint)pbVar18[1];
                pbVar18 = pbVar18 + (uVar12 + 1 & 0xfffffffe);
                goto LAB_100109ec;
              }
              pbVar14 = pbVar18 + 3;
              pbVar18 = pbVar18 + 2;
              pbVar21 = pbVar21 + ((uint)*pbVar18 - (uint)*pbVar14 * *(int *)((int)this + 0x30));
            }
          }
          else {
            bVar2 = pbVar18[1];
            pbVar14 = pbVar21;
            for (uVar12 = (uint)(bVar5 >> 2); uVar12 != 0; uVar12 = uVar12 - 1) {
              *(uint *)pbVar14 = CONCAT22(CONCAT11(bVar2,bVar2),CONCAT11(bVar2,bVar2));
              pbVar14 = pbVar14 + 4;
            }
            for (uVar12 = bVar5 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
              *pbVar14 = bVar2;
              pbVar14 = pbVar14 + 1;
            }
            uVar12 = (uint)*pbVar18;
LAB_100109ec:
            pbVar21 = pbVar21 + uVar12;
          }
          pbVar18 = pbVar18 + 2;
        }
      }
      else if (*(short *)((int)piVar17 + 0xe) == 1) {
        for (; (pbVar13 <= pbVar21 && (pbVar21 < pbVar14)); pbVar21 = pbVar21 + local_1c) {
          arg1 = (int *)0x0;
          if (piVar4 != (int *)0x0) {
            do {
              *(byte *)((int)arg1 + (int)pbVar21) =
                   pbVar18[(uint)arg1 >> 3] >> (7 - ((byte)arg1 & 7) & 0x1f) & 1;
              arg1 = (int *)((int)arg1 + 1);
            } while (arg1 < piVar4);
          }
          pbVar18 = pbVar18 + uVar16;
        }
      }
      else if (*(short *)((int)piVar17 + 0xe) == 4) {
        for (; (pbVar13 <= pbVar21 && (pbVar21 < pbVar14)); pbVar21 = pbVar21 + local_1c) {
          piVar17 = (int *)0x0;
          if (piVar4 != (int *)0x0) {
            do {
              if (((uint)piVar17 & 1) == 0) {
                bVar5 = pbVar18[(uint)piVar17 >> 1] >> 4;
              }
              else {
                bVar5 = pbVar18[(uint)piVar17 >> 1] & 0xf;
              }
              *(byte *)((int)piVar17 + (int)pbVar21) = bVar5;
              piVar17 = (int *)((int)piVar17 + 1);
            } while (piVar17 < piVar4);
          }
          pbVar18 = pbVar18 + uVar16;
        }
      }
      else {
        while ((pbVar13 <= pbVar21 && (pbVar21 < pbVar14))) {
          pbVar19 = pbVar18 + uVar16;
          pbVar22 = pbVar21 + local_1c;
          for (uVar12 = (uint)piVar20 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pbVar21 = *(undefined4 *)pbVar18;
            pbVar18 = pbVar18 + 4;
            pbVar21 = pbVar21 + 4;
          }
          pbVar23 = pbVar18;
          pbVar24 = pbVar21;
          for (uVar12 = (uint)piVar20 & 3; pbVar18 = pbVar19, pbVar21 = pbVar22, uVar12 != 0;
              uVar12 = uVar12 - 1) {
            *pbVar24 = *pbVar23;
            pbVar23 = pbVar23 + 1;
            pbVar24 = pbVar24 + 1;
          }
        }
      }
    }
  }
  return 0;
}



/* grim_load_image_jpg @ 10010e13 */

/* [binja] int32_t __thiscall sub_10010e13(int32_t* arg1, int32_t arg2, int32_t arg3) */

int grim_load_image_jpg(int *arg1,int arg2,int arg3)

{
  uint *puVar1;
  int iVar2;
  void *pvVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint *puVar8;
  undefined4 *puVar9;
  code *local_278 [2];
  undefined *local_270;
  undefined1 local_1f4 [64];
  int local_1b4;
  undefined4 *local_1b0;
  undefined4 *local_1a0;
  undefined4 local_170;
  uint local_158;
  uint local_154;
  int local_14c;
  uint local_13c;
  int *local_c;
  undefined4 *local_8;
  
  local_1b4 = grim_jpg_decompress_init(local_278);
  local_278[0] = grim_jpg_error_exit;
  local_270 = &grim_jpg_error_handler;
  iVar2 = setjmp3(local_1f4,0);
  if (iVar2 == 0) {
    grim_jpg_create_decompress(&local_1b4,0x3d,0x1a8);
    local_1a0 = (undefined4 *)(*(code *)*local_1b0)(&local_1b4,0,0x24);
    local_1a0[8] = arg2;
    local_1a0[2] = &grim_jpg_error_handler;
    local_1a0[3] = &LAB_10010ded;
    local_1a0[4] = &LAB_10010e02;
    local_1a0[5] = &LAB_1001dd80;
    local_1a0[6] = &grim_jpg_error_handler;
    local_1a0[1] = 0;
    *local_1a0 = 0;
    local_1a0[7] = arg1;
    grim_jpg_read_header(&local_1b4,'\x01');
    iVar2 = grim_jpg_start_decompress();
    if (iVar2 == 0) {
      local_170 = 1;
    }
    local_270 = &LAB_1001df31;
    grim_jpg_finish_decompress(&local_1b4);
    if (local_14c == 1) {
      *local_c = 0x32;
      local_c[0xc] = local_158;
    }
    else {
      if (local_14c != 3) goto LAB_10010e5e;
      *local_c = 0x16;
      local_c[0xc] = local_158 << 2;
    }
    local_c[0xd] = 0;
    local_c[3] = local_158;
    local_c[4] = local_154;
    local_c[5] = 1;
    if (local_c[0x10] != 0) {
      local_c[0xe] = 1;
      pvVar3 = operator_new(local_c[0xc] * local_154);
      local_c[1] = (int)pvVar3;
      if ((pvVar3 == (void *)0x0) ||
         (local_8 = (undefined4 *)(*(code *)local_1b0[2])(&local_1b4,1,local_158 * local_14c,1),
         local_8 == (undefined4 *)0x0)) {
        iVar2 = -0x7ff8fff2;
        goto LAB_1001106d;
      }
      if (*local_c == 0x32) {
        puVar6 = (undefined4 *)local_c[1];
        if (local_13c < local_154) {
          do {
            grim_jpg_read_scanlines(&local_1b4,local_8,1);
            puVar7 = (undefined4 *)*local_8;
            puVar9 = puVar6;
            for (uVar5 = local_158 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar9 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar9 = puVar9 + 1;
            }
            for (uVar5 = local_158 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
              puVar7 = (undefined4 *)((int)puVar7 + 1);
              puVar9 = (undefined4 *)((int)puVar9 + 1);
            }
            puVar6 = (undefined4 *)((int)puVar6 + local_158);
          } while (local_13c < local_154);
        }
      }
      else if (*local_c == 0x16) {
        puVar8 = (uint *)local_c[1];
        while (local_13c < local_154) {
          grim_jpg_read_scanlines(&local_1b4,local_8,1);
          puVar4 = (undefined1 *)*local_8;
          puVar1 = puVar8 + local_158;
          for (; puVar8 < puVar1; puVar8 = puVar8 + 1) {
            *puVar8 = (uint)CONCAT21(CONCAT11(*puVar4,puVar4[1]),puVar4[2]);
            puVar4 = puVar4 + 3;
          }
        }
      }
      grim_jpg_destroy_decompress(&local_1b4);
    }
    iVar2 = 0;
  }
  else {
LAB_10010e5e:
    iVar2 = -0x7fffbffb;
  }
LAB_1001106d:
  thunk_FUN_10023bc5((int)&local_1b4);
  return iVar2;
}



/* grim_tga_load @ 10011083 */

/* [binja] int32_t __thiscall sub_10011083(int32_t* arg1, void* arg2, int32_t arg3) */

int __thiscall grim_tga_load(void *this,int *arg1,void *arg2,int arg3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  int *piVar7;
  byte bVar8;
  uint uVar9;
  void *pvVar10;
  uint uVar11;
  undefined4 *puVar12;
  void *pvVar13;
  int *piVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint *puVar18;
  uint *puVar19;
  bool bVar20;
  bool bVar21;
  uint local_20;
  uint local_1c;
  uint local_18;
  int local_10;
  uint *local_8;
  
  piVar7 = arg1;
  if (arg2 < (void *)0x12) {
    return -0x7fffbffb;
  }
  if (((((*(byte *)((int)arg1 + 1) & 0xfe) != 0) ||
       (bVar4 = *(byte *)((int)arg1 + 2), (bVar4 & 0xf4) != 0)) || ((short)arg1[3] == 0)) ||
     (*(short *)((int)arg1 + 0xe) == 0)) {
    return -0x7fffbffb;
  }
  uVar9 = (uint)*(byte *)((int)arg1 + 7);
  local_18 = 0;
  if (*(byte *)((int)arg1 + 1) != 0) {
    if (uVar9 == 0xf) {
      local_18 = 0x18;
    }
    else if (uVar9 == 0x10) {
      local_18 = 0x19;
    }
    else if (uVar9 == 0x18) {
      local_18 = 0x14;
    }
    else {
      if (uVar9 != 0x20) {
        return -0x7fffbffb;
      }
      local_18 = 0x15;
    }
  }
  uVar15 = (uint)*(byte *)(arg1 + 4);
  pvVar10 = (void *)(uVar15 + 7 >> 3);
  bVar8 = bVar4 & 3;
  if (bVar8 == 1) {
    if (*(char *)((int)arg1 + 1) == '\0') {
      return -0x7fffbffb;
    }
    if ((char)arg1[4] != '\b') {
      return -0x7fffbffb;
    }
    local_10 = 0x29;
  }
  else if (bVar8 == 2) {
    if (uVar15 == 0xf) {
      local_10 = 0x18;
    }
    else if (uVar15 == 0x10) {
      local_10 = 0x19;
    }
    else if (uVar15 == 0x18) {
      local_10 = 0x14;
    }
    else {
      if (uVar15 != 0x20) {
        return -0x7fffbffb;
      }
      local_10 = 0x15;
    }
  }
  else {
    if (bVar8 != 3) {
      return -0x7fffbffb;
    }
    if ((char)arg1[4] != '\b') {
      return -0x7fffbffb;
    }
    local_10 = 0x32;
  }
  bVar20 = (*(byte *)((int)arg1 + 0x11) & 0x20) != 0x20;
  bVar21 = (*(byte *)((int)arg1 + 0x11) & 0x10) == 0x10;
  uVar11 = (uint)(byte)*arg1;
  if ((int)arg2 - 0x12U < uVar11) {
    return -0x7fffbffb;
  }
  uVar3 = ((int)arg2 - 0x12U) - uVar11;
  local_8 = (uint *)(uVar11 + 0x12 + (int)arg1);
  uVar9 = (uint)*(ushort *)((int)arg1 + 5) * (uVar9 + 7 >> 3);
  if (uVar3 < uVar9) {
    return -0x7fffbffb;
  }
  if ((*(int *)((int)this + 0x40) != 0) && (local_10 == 0x29)) {
    if (0x100 < (uint)*(ushort *)((int)arg1 + 3) + (uint)*(ushort *)((int)arg1 + 5)) {
      return -0x7fffbffb;
    }
    puVar12 = operator_new(0x400);
    *(undefined4 **)((int)this + 8) = puVar12;
    if (puVar12 == (undefined4 *)0x0) {
      return -0x7ff8fff2;
    }
    *(undefined4 *)((int)this + 0x3c) = 1;
    for (iVar16 = 0x100; iVar16 != 0; iVar16 = iVar16 + -1) {
      *puVar12 = 0xffffffff;
      puVar12 = puVar12 + 1;
    }
    puVar1 = (undefined1 *)(*(int *)((int)this + 8) + (uint)*(ushort *)((int)arg1 + 3) * 4);
    puVar2 = puVar1 + (uint)*(ushort *)((int)arg1 + 5) * 4;
    uVar11 = uVar3;
    uVar17 = uVar3;
    arg1 = (int *)local_8;
    for (; puVar1 < puVar2; puVar1 = puVar1 + 4) {
      if (local_18 == 0x14) {
        uVar11 = (uint)*(byte *)((int)arg1 + 2);
        uVar17 = (uint)*(byte *)((int)arg1 + 1);
        local_1c = (uint)(byte)*arg1;
        arg1 = (int *)((int)arg1 + 3);
LAB_10011360:
        local_20 = 0xff;
      }
      else if (local_18 == 0x15) {
        uVar6 = *arg1;
        local_20 = uVar6 >> 0x18;
        uVar17 = uVar6 >> 8 & 0xff;
        uVar11 = uVar6 >> 0x10 & 0xff;
        local_1c = uVar6 & 0xff;
        arg1 = (int *)((uint *)arg1 + 1);
      }
      else {
        if (local_18 == 0x18) {
          uVar5 = (ushort)*arg1;
          uVar11 = uVar5 >> 10 & 0x1f;
          uVar17 = uVar5 >> 5 & 0x1f;
          uVar11 = uVar11 >> 2 | uVar11 << 3;
          uVar17 = uVar17 >> 2 | uVar17 << 3;
          local_1c = (uVar5 & 0x1f) >> 2 | (uVar5 & 0x1f) << 3;
          arg1 = (int *)((int)arg1 + 2);
          goto LAB_10011360;
        }
        if (local_18 == 0x19) {
          uVar5 = (ushort)*arg1;
          local_20 = (uint)(uVar5 >> 0xf) * 0xff;
          uVar11 = uVar5 >> 10 & 0x1f;
          uVar17 = uVar5 >> 5 & 0x1f;
          uVar11 = uVar11 >> 2 | uVar11 << 3;
          uVar17 = uVar17 >> 2 | uVar17 << 3;
          local_1c = (uVar5 & 0x1f) >> 2 | (uVar5 & 0x1f) << 3;
          arg1 = (int *)((int)arg1 + 2);
        }
      }
      puVar1[2] = (char)local_1c;
      puVar1[3] = (undefined1)local_20;
      *puVar1 = (char)uVar11;
      puVar1[1] = (char)uVar17;
    }
  }
  arg2 = (void *)(uVar3 - uVar9);
  local_8 = (uint *)((int)local_8 + uVar9);
  pvVar13 = (void *)((uint)*(ushort *)((int)piVar7 + 0xe) * (uint)*(ushort *)(piVar7 + 3) *
                    (int)pvVar10);
  *(int *)this = local_10;
  *(uint **)((int)this + 4) = local_8;
  *(uint *)((int)this + 0x30) = (uint)*(ushort *)(piVar7 + 3) * (int)pvVar10;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(uint *)((int)this + 0xc) = (uint)*(ushort *)(piVar7 + 3);
  *(uint *)((int)this + 0x10) = (uint)*(ushort *)((int)piVar7 + 0xe);
  *(undefined4 *)((int)this + 0x14) = 1;
  if (*(int *)((int)this + 0x40) != 0) {
    if ((((bVar4 & 8) != 0) || (bVar20)) || (bVar21)) {
      piVar14 = operator_new((uint)pvVar13);
      *(int **)((int)this + 4) = piVar14;
      if (piVar14 == (int *)0x0) {
        return -0x7ff8fff2;
      }
      *(undefined4 *)((int)this + 0x38) = 1;
      if (bVar20) {
        piVar14 = (int *)((*(ushort *)((int)piVar7 + 0xe) - 1) * *(int *)((int)this + 0x30) +
                         (int)piVar14);
      }
      local_18 = 0;
      if (*(short *)((int)piVar7 + 0xe) != 0) {
        do {
          arg1 = piVar14;
          if (bVar21) {
            arg1 = (int *)((*(int *)((int)this + 0x30) - (int)pvVar10) + (int)piVar14);
          }
          uVar9 = (uint)*(ushort *)(piVar7 + 3);
          local_1c = 0;
          if (uVar9 != 0) {
            do {
              if ((bVar4 & 8) == 0) {
                local_20 = 0;
              }
              else {
                if (arg2 == (void *)0x0) {
                  return -0x7fffbffb;
                }
                local_20 = (byte)*local_8 & 0x80;
                uVar9 = ((byte)*local_8 & 0x7f) + 1;
                local_8 = (uint *)((int)local_8 + 1);
                arg2 = (void *)((int)arg2 + -1);
              }
              local_1c = local_1c + uVar9;
              while (uVar9 != 0) {
                uVar9 = uVar9 - 1;
                if (arg2 < pvVar10) {
                  return -0x7fffbffb;
                }
                puVar18 = local_8;
                puVar19 = (uint *)arg1;
                for (uVar11 = uVar15 + 7 >> 5; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *puVar19 = *puVar18;
                  puVar18 = puVar18 + 1;
                  puVar19 = puVar19 + 1;
                }
                for (uVar11 = (uint)pvVar10 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *(byte *)puVar19 = (byte)*puVar18;
                  puVar18 = (uint *)((int)puVar18 + 1);
                  puVar19 = (uint *)((int)puVar19 + 1);
                }
                if (local_20 == 0) {
                  local_8 = (uint *)((int)local_8 + (int)pvVar10);
                  arg2 = (void *)((int)arg2 - (int)pvVar10);
                }
                pvVar13 = pvVar10;
                if (bVar21) {
                  pvVar13 = (void *)-(int)pvVar10;
                }
                arg1 = (int *)((int)arg1 + (int)pvVar13);
              }
              if (local_20 != 0) {
                local_8 = (uint *)((int)local_8 + (int)pvVar10);
                arg2 = (void *)((int)arg2 - (int)pvVar10);
              }
              uVar9 = (uint)*(ushort *)(piVar7 + 3);
            } while (local_1c < uVar9);
          }
          if (bVar20) {
            iVar16 = -*(int *)((int)this + 0x30);
          }
          else {
            iVar16 = *(int *)((int)this + 0x30);
          }
          piVar14 = (int *)((int)piVar14 + iVar16);
          local_18 = local_18 + 1;
        } while (local_18 < *(ushort *)((int)piVar7 + 0xe));
      }
    }
    else {
      if (arg2 < pvVar13) {
        return -0x7fffbffb;
      }
      *(uint **)((int)this + 4) = local_8;
      *(undefined4 *)((int)this + 0x38) = 0;
    }
  }
  return 0;
}



/* grim_load_image_pnm @ 1001152a */

/* [binja] int32_t __thiscall sub_1001152a(int32_t* arg1, char* arg2, int32_t arg3) */

int __thiscall grim_load_image_pnm(void *this,int *arg1,char *arg2,int arg3)

{
  char *pcVar1;
  byte bVar2;
  bool bVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  uint local_18;
  uint *local_14;
  uint local_c;
  int local_8;
  
  if (arg2 < (char *)0x2) {
    return -0x7fffbffb;
  }
  if ((char)*arg1 == 'P') {
    if (*(char *)((int)arg1 + 1) == '3') {
      bVar3 = true;
    }
    else {
      if (*(char *)((int)arg1 + 1) != '6') {
        return -0x7fffbffb;
      }
      bVar3 = false;
    }
    pbVar9 = (byte *)((int)arg1 + 2);
    arg2 = arg2 + -2;
    local_8 = 0;
    local_18 = 0;
    local_c = 0xff;
    pbVar4 = pbVar9;
    while (arg2 != (char *)0x0) {
      uVar8 = 0;
      if ((!bVar3) && (local_8 == 3)) {
        if (0xff < local_c) {
          return -0x7fffbffb;
        }
        if (((char *)0x1 < arg2) && (*pbVar9 == 0xd)) {
          pbVar9 = pbVar9 + 1;
          arg2 = arg2 + -1;
        }
        pcVar1 = arg2 + -1;
        pbVar9 = pbVar9 + 1;
        for (; (pcVar1 != (char *)0x0 && (arg1 < local_14)); arg1 = (int *)((uint *)arg1 + 1)) {
          *arg1 = ((((uint)*pbVar9 * 0xff) / local_c | 0xffffff00) << 8 |
                  ((uint)pbVar9[1] * 0xff) / local_c) << 8 | ((uint)pbVar9[2] * 0xff) / local_c;
          pcVar1 = pcVar1 + -3;
          pbVar9 = pbVar9 + 3;
        }
        return -(uint)((uint *)arg1 != local_14) & 0x80004005;
      }
      iVar7 = isspace((uint)*pbVar9);
      if (iVar7 == 0) {
        if (*pbVar9 == 0x23) {
          for (; (arg2 != (char *)0x0 && (*pbVar9 != 10)); pbVar9 = pbVar9 + 1) {
            arg2 = arg2 + -1;
          }
          goto LAB_100115b4;
        }
        while ((arg2 != (char *)0x0 && (iVar7 = isspace((uint)*pbVar9), iVar7 == 0))) {
          iVar7 = isdigit((uint)*pbVar9);
          if (iVar7 == 0) {
            return -0x7fffbffb;
          }
          bVar2 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          arg2 = arg2 + -1;
          uVar8 = (bVar2 - 0x30) + uVar8 * 10;
          pbVar4 = pbVar9;
        }
        uVar5 = uVar8;
        uVar6 = local_c;
        if (local_8 == 0) {
LAB_100116f9:
          local_c = uVar6;
          local_18 = uVar5;
          if (uVar8 == 0) {
            return -0x7fffbffb;
          }
        }
        else if (local_8 == 1) {
          if (uVar8 == 0) {
            return -0x7fffbffb;
          }
          arg1 = operator_new(uVar8 * local_18 * 4);
          *(int **)((int)this + 4) = arg1;
          if (arg1 == (int *)0x0) {
            return -0x7ff8fff2;
          }
          local_14 = (uint *)(arg1 + uVar8 * local_18);
          *(undefined4 *)((int)this + 0x34) = 0;
          *(undefined4 *)((int)this + 0x38) = 1;
          *(undefined4 *)this = 0x16;
          *(uint *)((int)this + 0x30) = local_18 << 2;
          *(uint *)((int)this + 0xc) = local_18;
          *(uint *)((int)this + 0x10) = uVar8;
          *(undefined4 *)((int)this + 0x14) = 1;
          pbVar9 = pbVar4;
        }
        else {
          uVar5 = local_18;
          uVar6 = uVar8;
          if (local_8 == 2) goto LAB_100116f9;
          if (local_8 == 3) {
            if (local_14 <= arg1) {
              return -0x7fffbffb;
            }
            *arg1 = ((uVar8 * 0xff) / local_c | 0xffffff00) << 0x10;
          }
          else if (local_8 == 4) {
            *arg1 = *arg1 | (uVar8 * 0xff) / local_c << 8;
          }
          else if (local_8 == 5) {
            *arg1 = *arg1 | (uVar8 * 0xff) / local_c;
            arg1 = (int *)((uint *)arg1 + 1);
            if ((uint *)arg1 == local_14) {
              return 0;
            }
            local_8 = 2;
          }
        }
        local_8 = local_8 + 1;
      }
      else {
LAB_100115b4:
        pbVar9 = pbVar9 + 1;
        arg2 = arg2 + -1;
        pbVar4 = pbVar9;
      }
    }
  }
  return -0x7fffbffb;
}



/* grim_load_image_png @ 100117ff */

/* [binja] int32_t __thiscall sub_100117ff(int32_t* arg1, void* arg2, void* arg3) */

int grim_load_image_png(int *arg1,void *arg2,void *arg3)

{
  undefined1 *puVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_158 [256];
  double local_58;
  double local_50;
  int *local_48;
  void *local_44;
  int local_40;
  undefined1 local_3c [4];
  int *local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  undefined4 *local_20;
  uint local_1c;
  int local_18;
  int local_14;
  uint local_10;
  uint *local_c;
  png_structp local_8;
  
  local_8 = (png_structp)0x0;
  local_c = (uint *)0x0;
  local_20 = (undefined4 *)0x0;
  iVar4 = grim_png_check_sig((int)arg1,0,(uint)arg2);
  if (iVar4 != 0) {
    return -0x7fffbffb;
  }
  local_8 = png_create_read_struct("1.0.5",(png_voidp)0x0,&DAT_100117f3,&grim_jpg_error_handler);
  if ((local_8 == (png_structp)0x0) ||
     (local_c = grim_png_create_info_struct((int)local_8), local_c == (uint *)0x0)) goto LAB_10011c62;
  iVar4 = setjmp3(local_8);
  if (iVar4 == 0) {
    local_48 = arg1;
    local_44 = arg2;
    grim_png_set_read_fn(local_8,&local_48,&LAB_100117b0);
    grim_png_read_header_and_validate(local_8,local_c);
    grim_png_set_strip_16(local_8,local_c,&local_34,&local_1c,&local_28,&local_30,(uint *)0x0,(uint *)0x0,
                 (uint *)0x0);
    if (local_30 == 0) {
      *local_38 = 0x32;
    }
    else if (local_30 == 2) {
      *local_38 = 0x14;
    }
    else if (local_30 == 3) {
      *local_38 = 0x29;
    }
    else if (local_30 == 4) {
      *local_38 = 0x33;
    }
    else if (local_30 == 6) {
      *local_38 = 0x15;
    }
    if (local_28 == 0x10) {
      grim_png_get_image_width((int)local_8);
      iVar4 = *local_38;
      if (iVar4 == 0x14) {
        *local_38 = 0x36315220;
      }
      else if (iVar4 == 0x15) {
        *local_38 = 0x36315241;
      }
      else if (iVar4 == 0x32) {
        *local_38 = 0x36314c20;
      }
      else {
        if (iVar4 != 0x33) {
          return -0x7fffbffb;
        }
        *local_38 = 0x36314c41;
      }
    }
    if ((int)local_28 < 8) {
      grim_png_get_image_height((int)local_8);
    }
    if ((local_30 == 0) && ((int)local_28 < 8)) {
      grim_png_set_filler((int)local_8);
    }
    iVar4 = grim_png_get_rowbytes((int)local_8,(int)local_c,(uint *)local_3c);
    if (iVar4 == 0) {
      iVar4 = grim_png_get_channels((int)local_8,(int)local_c,&local_58);
      if (iVar4 != 0) {
        grim_png_set_expand((int)local_8,2.2,local_58);
      }
    }
    else {
      grim_png_set_sRGB((int)local_8,(int)local_c,local_3c[0]);
    }
    if ((*local_38 != 0x29) && (uVar5 = grim_png_get_bit_depth((int)local_8,(int)local_c,0x10), uVar5 != 0)) {
      grim_png_set_filler((int)local_8);
      iVar4 = *local_38;
      if (iVar4 == 0x14) {
        *local_38 = 0x15;
      }
      else if (iVar4 == 0x32) {
        *local_38 = 0x33;
      }
      else if (iVar4 == 0x36314c20) {
        *local_38 = 0x36314c41;
      }
      else if (iVar4 == 0x36315220) {
        *local_38 = 0x36315241;
      }
    }
    iVar4 = *local_38;
    if ((((iVar4 == 0x14) || (iVar4 == 0x36315220)) || (iVar4 == 0x15)) || (iVar4 == 0x36315241)) {
      grim_png_get_valid((int)local_8);
    }
    if (*local_38 == 0x14) {
      grim_png_do_read_transformations((int)local_8,0xff,1);
      *local_38 = 0x16;
    }
    grim_png_read_row_cleanup(local_8,(int *)local_c);
    iVar4 = *local_38;
    uVar5 = 3;
    if (iVar4 < 0x34) {
      if (iVar4 == 0x33) {
LAB_10011ad2:
        local_10 = 2;
        uVar5 = local_10;
      }
      else if (iVar4 != 0x14) {
        if ((iVar4 == 0x15) || (iVar4 == 0x16)) {
LAB_10011ac8:
          uVar5 = 4;
        }
        else if ((iVar4 == 0x29) || (uVar5 = local_10, iVar4 == 0x32)) goto LAB_10011a8e;
      }
    }
    else if (iVar4 == 0x36314c20) {
LAB_10011a8e:
      local_10 = 1;
      uVar5 = local_10;
    }
    else {
      if (iVar4 == 0x36314c41) goto LAB_10011ad2;
      if ((iVar4 != 0x36315220) && (uVar5 = local_10, iVar4 == 0x36315241)) goto LAB_10011ac8;
    }
    local_10 = uVar5;
    bVar2 = grim_png_get_interlace_type((int)local_8,(int)local_c);
    if (local_10 == bVar2) {
      local_38[3] = local_34;
      local_38[4] = local_1c;
      local_38[5] = 1;
      iVar4 = grim_png_get_color_type((int)local_8,(int)local_c);
      local_38[0xc] = iVar4;
      local_38[0xd] = 0;
      if (local_38[0x10] == 0) goto LAB_10011d64;
      pvVar6 = operator_new(iVar4 * local_1c);
      local_38[1] = (int)pvVar6;
      if (pvVar6 != (void *)0x0) {
        local_38[0xe] = 1;
        local_20 = operator_new(local_1c << 2);
        if (local_20 != (undefined4 *)0x0) {
          uVar5 = 0;
          if (local_1c != 0) {
            do {
              local_20[uVar5] = local_38[0xc] * uVar5 + local_38[1];
              uVar5 = uVar5 + 1;
            } while (uVar5 < local_1c);
          }
          grim_png_read_rows_with_transform(local_8,local_20);
          if (*local_38 == 0x29) {
            local_2c = 0;
            local_24 = 0;
            uVar5 = grim_png_get_bit_depth((int)local_8,(int)local_c,8);
            if (uVar5 != 0) {
              grim_png_set_packing((int)local_8,(int)local_c,&local_14,&local_24);
            }
            uVar5 = grim_png_get_bit_depth((int)local_8,(int)local_c,0x10);
            if (uVar5 != 0) {
              grim_png_set_gray_to_rgb((int)local_8,(int)local_c,&local_40,&local_2c,(int *)0x0);
            }
            if (((float)local_8[1].jmpbuf[4] <= 1e-06) || ((float)local_8[1].jmpbuf[5] <= 1e-06)) {
              iVar4 = 0;
              do {
                auStack_158[iVar4] = (char)iVar4;
                iVar4 = iVar4 + 1;
              } while (iVar4 < 0x100);
            }
            else {
              local_18 = 0;
              local_50 = (double)(1.0 / ((float)local_8[1].jmpbuf[5] * (float)local_8[1].jmpbuf[4]))
              ;
              do {
                _CIpow();
                uVar3 = ftol();
                iVar4 = local_18 + 1;
                puVar1 = auStack_158 + local_18;
                local_18 = iVar4;
                *puVar1 = uVar3;
              } while (iVar4 < 0x100);
            }
            pvVar6 = operator_new(0x400);
            local_38[2] = (int)pvVar6;
            if (pvVar6 == (void *)0x0) goto LAB_10011c62;
            iVar4 = 0;
            local_38[0xf] = 1;
            if (0 < (int)local_2c) {
              iVar8 = 0;
              do {
                iVar7 = iVar4 * 4;
                *(undefined1 *)(iVar7 + local_38[2]) = auStack_158[*(byte *)(iVar8 + local_14)];
                *(undefined1 *)(local_38[2] + 1 + iVar7) =
                     auStack_158[*(byte *)(iVar8 + 1 + local_14)];
                *(undefined1 *)(local_38[2] + 2 + iVar7) =
                     auStack_158[*(byte *)(iVar8 + 2 + local_14)];
                puVar1 = (undefined1 *)(iVar4 + local_40);
                iVar4 = iVar4 + 1;
                *(undefined1 *)(local_38[2] + 3 + iVar7) = *puVar1;
                iVar8 = iVar8 + 3;
              } while (iVar4 < (int)local_2c);
            }
            if (iVar4 < (int)local_24) {
              iVar8 = iVar4 * 3;
              do {
                iVar7 = iVar4 * 4;
                *(undefined1 *)(iVar7 + local_38[2]) = auStack_158[*(byte *)(iVar8 + local_14)];
                *(undefined1 *)(local_38[2] + 1 + iVar7) =
                     auStack_158[*(byte *)(iVar8 + 1 + local_14)];
                *(undefined1 *)(local_38[2] + 2 + iVar7) =
                     auStack_158[*(byte *)(iVar8 + 2 + local_14)];
                *(undefined1 *)(local_38[2] + 3 + iVar7) = 0xff;
                iVar4 = iVar4 + 1;
                iVar8 = iVar8 + 3;
              } while (iVar4 < (int)local_24);
            }
            if (iVar4 < 0x100) {
              iVar4 = iVar4 << 2;
              do {
                *(undefined1 *)(iVar4 + local_38[2]) = 0xff;
                *(undefined1 *)(iVar4 + 1 + local_38[2]) = 0xff;
                *(undefined1 *)(iVar4 + 2 + local_38[2]) = 0xff;
                *(undefined1 *)(iVar4 + 3 + local_38[2]) = 0xff;
                iVar4 = iVar4 + 4;
              } while (iVar4 < 0x400);
            }
          }
LAB_10011d64:
          iVar4 = 0;
          goto LAB_10011d66;
        }
      }
LAB_10011c62:
      iVar4 = -0x7ff8fff2;
      goto LAB_10011d66;
    }
  }
  iVar4 = -0x7fffbffb;
LAB_10011d66:
  if (local_8 != (png_structp)0x0) {
    grim_png_destroy_info_struct(&local_8,&local_c,(undefined4 *)0x0);
  }
  if (local_20 != (undefined4 *)0x0) {
    operator_delete(local_20);
  }
  return iVar4;
}



/* grim_load_image_dds @ 10011d95 */

/* [binja] int32_t __thiscall sub_10011d95(int32_t* arg1, uint32_t arg2, int32_t* arg3) */

int __thiscall grim_load_image_dds(void *this,int *arg1,uint arg2,int *arg3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int *piVar10;
  uint uVar11;
  int *local_2c;
  uint local_24;
  int *local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  int *local_8;
  
  if (((arg2 < 4) || (*arg1 != 0x20534444)) || (arg2 - 4 < 0x7c)) {
    return -0x7fffbffb;
  }
  local_8 = arg1 + 0x20;
  *(int *)((int)this + 0xc) = arg1[4];
  *(int *)((int)this + 0x10) = arg1[3];
  if ((*(byte *)((int)arg1 + 10) & 0x80) == 0) {
    iVar1 = 1;
  }
  else {
    iVar1 = arg1[6];
  }
  *(int *)((int)this + 0x14) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)((int)this + 0x14) = 1;
  }
  if ((arg1[0x1c] & 0xfc00U) == 0xfc00) {
    local_18 = 6;
  }
  else {
    if ((arg1[0x1c] & 0xfc00U) != 0) {
      return -0x7fffbffb;
    }
    local_18 = 1;
  }
  local_24 = arg1[7];
  if (local_24 == 0) {
    local_24 = 1;
  }
  piVar10 = &DAT_10053ec8;
  iVar1 = DAT_10053ec8;
  while (iVar1 != 0) {
    if ((arg1[0x13] == 0x20) && (uVar11 = piVar10[2], arg1[0x14] == uVar11)) {
      if ((((((uVar11 & 4) == 0) || (arg1[0x15] == piVar10[3])) &&
           (((uVar11 & 0xc4462) == 0 || (arg1[0x16] == piVar10[4])))) &&
          (((uVar11 & 0xe4040) == 0 || (arg1[0x17] == piVar10[5])))) &&
         (((((uVar11 & 0xc4440) == 0 || (arg1[0x18] == piVar10[6])) &&
           (((uVar11 & 0xc4040) == 0 || (arg1[0x19] == piVar10[7])))) &&
          (((uVar11 & 0x80003) == 0 || (arg1[0x1a] == piVar10[8])))))) break;
    }
    piVar10 = piVar10 + 9;
    iVar1 = *piVar10;
  }
  iVar1 = *piVar10;
  if (iVar1 == 0) {
    return -0x7fffbffb;
  }
  piVar10 = grim_format_info_lookup(iVar1);
  if ((*(byte *)((int)arg1 + 10) & 0x80) == 0) {
    *(uint *)((int)this + 0x44) = (uint)(local_18 == 6) * 2 + 3;
  }
  else {
    *(undefined4 *)((int)this + 0x44) = 4;
  }
  if (piVar10[1] == 1) {
    if (arg2 - 0x80 < 0x400) {
      return -0x7fffbffb;
    }
    arg2 = arg2 - 0x480;
    local_2c = local_8;
    local_8 = arg1 + 0x120;
  }
  else {
    local_2c = (int *)0x0;
    arg2 = arg2 - 0x80;
  }
  local_14 = 0;
  piVar3 = (int *)arg2;
  if (local_18 != 0) {
    do {
      uVar11 = *(uint *)((int)this + 0xc);
      uVar8 = *(uint *)((int)this + 0x10);
      arg1 = *(int **)((int)this + 0x14);
      piVar2 = this;
      if (local_14 != 0) {
        piVar2 = operator_new(0x54);
        if (piVar2 == (int *)0x0) {
          piVar2 = (int *)0x0;
        }
        else {
          piVar2 = grim_file_stream_init(piVar2);
        }
        if (piVar2 == (int *)0x0) {
          return -0x7ff8fff2;
        }
        local_1c[0x14] = (int)piVar2;
      }
      local_10 = 0;
      piVar9 = piVar3;
      if (local_24 != 0) {
        do {
          piVar3 = piVar2;
          if (local_10 != 0) {
            piVar3 = operator_new(0x54);
            if (piVar3 == (int *)0x0) {
              piVar3 = (int *)0x0;
            }
            else {
              piVar3 = grim_file_stream_init(piVar3);
            }
            if (piVar3 == (int *)0x0) {
              return -0x7ff8fff2;
            }
            piVar9[0x13] = (int)piVar3;
          }
          if (iVar1 == 0x31545844) {
            iVar4 = (uVar11 + 3 >> 2) << 3;
LAB_10012032:
            iVar6 = (uVar8 + 3 >> 2) * iVar4;
          }
          else {
            if (iVar1 == 0x32545844) {
LAB_1001201e:
              iVar4 = (uVar11 + 3 >> 2) << 4;
              goto LAB_10012032;
            }
            if (iVar1 == 0x32595559) {
LAB_1001200f:
              iVar4 = (uVar11 + 1 >> 1) << 2;
            }
            else {
              if (((iVar1 == 0x33545844) || (iVar1 == 0x34545844)) || (iVar1 == 0x35545844))
              goto LAB_1001201e;
              if (iVar1 == 0x59565955) goto LAB_1001200f;
              iVar4 = ((uint)piVar10[2] >> 3) * uVar11;
            }
            iVar6 = iVar4 * uVar8;
          }
          piVar3[0xe] = 0;
          piVar3[0xf] = 0;
          uVar7 = iVar6 * (int)arg1;
          *piVar3 = iVar1;
          piVar3[0xc] = iVar4;
          piVar3[1] = (int)local_8;
          piVar3[5] = (int)arg1;
          piVar3[0xd] = iVar6;
          piVar3[3] = uVar11;
          piVar3[4] = uVar8;
          piVar3[2] = (int)local_2c;
          if (arg2 < uVar7) {
            return -0x7fffbffb;
          }
          local_8 = (int *)((int)local_8 + uVar7);
          arg2 = arg2 - uVar7;
          uVar5 = 1;
          uVar7 = uVar5;
          if (uVar11 != 1) {
            uVar7 = uVar11 >> 1;
          }
          if (uVar8 != 1) {
            uVar5 = uVar8 >> 1;
          }
          if (arg1 == (int *)0x1) {
            arg1 = (int *)0x1;
          }
          else {
            arg1 = (int *)((uint)arg1 >> 1);
          }
          local_10 = local_10 + 1;
          uVar8 = uVar5;
          piVar9 = piVar3;
          uVar11 = uVar7;
        } while (local_10 < local_24);
      }
      local_14 = local_14 + 1;
      local_1c = piVar2;
    } while (local_14 < local_18);
  }
  return 0;
}



/* grim_load_image_bmp @ 10012647 */

/* [binja] int32_t __stdcall sub_10012647(int16_t* arg1, void* arg2) */

int __thiscall grim_load_image_bmp(void *this,short *arg1,void *arg2)

{
  int iVar1;
  void *unaff_retaddr;
  
  if (((arg2 < (void *)0xe) || (*arg1 != 0x4d42)) || (arg2 < *(void **)(arg1 + 1))) {
    iVar1 = -0x7fffbffb;
  }
  else {
    iVar1 = grim_bmp_pixel_data_decode(this,(int *)(arg1 + 7),(void *)((int)arg2 + -0xe),unaff_retaddr);
  }
  return iVar1;
}



/* grim_image_detect_format @ 10012677 */

/* [binja] int32_t __thiscall sub_10012677(int32_t* arg1, void* arg2, int32_t* arg3, int32_t* arg4,
   int32_t arg5) */

int __thiscall grim_image_detect_format(void *this,int *arg1,void *arg2,int *arg3,int *arg4,int arg5)

{
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  int *unaff_EDI;
  int *piVar4;
  int local_24 [8];
  
  local_24[0] = 0;
  local_24[1] = 5;
  local_24[2] = 4;
  local_24[3] = 1;
  local_24[4] = 3;
  local_24[5] = 2;
  local_24[6] = 6;
  local_24[7] = 0;
  pvVar2 = arg2;
  do {
    *(int **)((int)this + 0x40) = arg4;
    iVar3 = local_24[local_24[7]];
    *(int *)((int)this + 0x48) = iVar3;
    *(undefined4 *)((int)this + 0x44) = 3;
    if (iVar3 == 0) {
      pvVar2 = (void *)grim_load_image_bmp(this,(short *)arg1,arg2);
    }
    else if (iVar3 == 1) {
      pvVar2 = (void *)grim_load_image_jpg(arg1,(int)arg2,(int)unaff_EDI);
    }
    else if (iVar3 == 2) {
      pvVar2 = (void *)grim_tga_load(this,arg1,arg2,(int)unaff_EDI);
    }
    else if (iVar3 == 3) {
      pvVar2 = (void *)grim_load_image_png(arg1,arg2,unaff_EDI);
    }
    else if (iVar3 == 4) {
      pvVar2 = (void *)grim_load_image_dds(this,arg1,(uint)arg2,unaff_EDI);
    }
    else if (iVar3 == 5) {
      pvVar2 = (void *)grim_load_image_pnm(this,arg1,arg2,(int)unaff_EDI);
    }
    else if (iVar3 == 6) {
      pvVar2 = (void *)grim_bmp_pixel_data_decode(this,arg1,arg2,unaff_EDI);
    }
    if (-1 < (int)pvVar2) break;
    if ((*(void **)((int)this + 4) != (void *)0x0) && (*(int *)((int)this + 0x38) != 0)) {
      operator_delete(*(void **)((int)this + 4));
    }
    if ((*(void **)((int)this + 8) != (void *)0x0) && (*(int *)((int)this + 0x3c) != 0)) {
      operator_delete(*(void **)((int)this + 8));
    }
    if (*(void **)((int)this + 0x4c) != (void *)0x0) {
      grim_bmp_header_parse(*(void **)((int)this + 0x4c),(void *)0x1,(char)unaff_EDI);
    }
    if (*(void **)((int)this + 0x50) != (void *)0x0) {
      grim_bmp_header_parse(*(void **)((int)this + 0x50),(void *)0x1,(char)unaff_EDI);
    }
    local_24[7] = local_24[7] + 1;
    *(undefined4 *)((int)this + 4) = 0;
    *(undefined4 *)((int)this + 8) = 0;
    *(undefined4 *)((int)this + 0x38) = 0;
    *(undefined4 *)((int)this + 0x3c) = 0;
    *(undefined4 *)((int)this + 0x4c) = 0;
    *(undefined4 *)((int)this + 0x50) = 0;
  } while ((uint)local_24[7] < 7);
  iVar3 = 7;
  if (local_24[7] == 7) {
    iVar3 = -0x7789f4a7;
  }
  else {
    piVar4 = arg3;
    pvVar2 = this;
    if (arg3 != (int *)0x0) {
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar4 = 0;
        piVar4 = piVar4 + 1;
      }
      *arg3 = *(int *)((int)this + 0xc);
      arg3[1] = *(int *)((int)this + 0x10);
      arg3[2] = *(int *)((int)this + 0x14);
      arg3[3] = 1;
      iVar3 = grim_format_convert_fourcc(*(int *)this);
      arg3[4] = iVar3;
      arg3[5] = *(int *)((int)this + 0x44);
      arg3[6] = *(int *)((int)this + 0x48);
      for (pvVar1 = this; *(int *)((int)pvVar1 + 0x4c) != 0; pvVar1 = *(void **)((int)pvVar1 + 0x4c)
          ) {
        arg3[3] = arg3[3] + 1;
      }
    }
    do {
      for (; this != (void *)0x0; this = *(void **)((int)this + 0x4c)) {
        *(undefined4 *)((int)this + 0x20) = *(undefined4 *)((int)this + 0xc);
        *(undefined4 *)((int)this + 0x24) = *(undefined4 *)((int)this + 0x10);
        *(undefined4 *)((int)this + 0x18) = 0;
        *(undefined4 *)((int)this + 0x1c) = 0;
        *(undefined4 *)((int)this + 0x28) = 0;
        *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)((int)this + 0x14);
      }
      this = *(void **)((int)pvVar2 + 0x50);
      pvVar2 = this;
    } while (this != (void *)0x0);
    iVar3 = 0;
  }
  return iVar3;
}


