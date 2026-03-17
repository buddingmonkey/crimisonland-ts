/* fpu_set_round_trunc @ 100170d6 */

/* sets x87 rounding mode to truncate; saves control word in grim_fpu_control_word */

void __fastcall fpu_set_round_trunc(void)

{
  undefined4 in_ECX;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)in_ECX >> 0x10),in_FPUControlWord);
  grim_fpu_control_word = local_8;
  return;
}



/* grim_cpuid_check_3dnow @ 1001bff7 */

/* WARNING: Removing unreachable block (ram,0x1001c016) */
/* WARNING: Removing unreachable block (ram,0x1001c008) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* [binja] int32_t __fastcall sub_1001bff7(int32_t arg1) */

int __fastcall grim_cpuid_check_3dnow(int arg1)

{
  uint *puVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  puVar1 = (uint *)cpuid(0x80000000);
  if (0x80000000 < *puVar1) {
    iVar2 = cpuid(0x80000001);
    local_8 = (uint)((*(uint *)(iVar2 + 8) & 0x80000000) != 0);
  }
  return local_8;
}



/* grim_cpuid_check_features @ 1001c02f */

/* WARNING: Removing unreachable block (ram,0x1001c059) */
/* [binja] int32_t __fastcall sub_1001c02f(int32_t arg1) */

int grim_cpuid_check_features(int arg1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int unaff_EBP;
  
  seh_prolog();
  *(undefined1 **)(unaff_EBP + -0x10) = &stack0xffffffc4;
  *(undefined4 *)(unaff_EBP + -0x14) = 0;
  builtin_strncpy((char *)(unaff_EBP + -0x24),"Genu",4);
  builtin_strncpy((char *)(unaff_EBP + -0x20),"ineI",4);
  builtin_strncpy((char *)(unaff_EBP + -0x1c),"ntel",4);
  *(char *)(unaff_EBP + -0x18) = '\0';
  *(undefined4 *)(unaff_EBP + -4) = 0;
  puVar1 = (undefined4 *)cpuid_basic_info(0);
  uVar5 = puVar1[1];
  uVar4 = puVar1[2];
  uVar3 = puVar1[3];
  *(undefined4 *)(unaff_EBP + -0x2c) = *puVar1;
  *(undefined4 *)(unaff_EBP + -0x38) = uVar5;
  *(undefined4 *)(unaff_EBP + -0x34) = uVar4;
  *(undefined4 *)(unaff_EBP + -0x30) = uVar3;
  iVar2 = grim_cpuid_extended_features();
  return iVar2;
}



/* grim_cpuid_extended_features @ 1001c075 */

/* WARNING: Removing unreachable block (ram,0x1001c090) */

undefined4 grim_cpuid_extended_features(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + -0x2c) == 0) {
    uVar2 = *(undefined4 *)(unaff_EBP + -0x14);
  }
  else {
    puVar1 = (undefined4 *)cpuid_Version_info(1);
    uVar2 = puVar1[2];
    *(undefined4 *)(unaff_EBP + -0x2c) = *puVar1;
    *(undefined4 *)(unaff_EBP + -0x28) = uVar2;
    if ((*(uint *)(unaff_EBP + -0x28) & 0x2000000) != 0) {
      *(uint *)(unaff_EBP + -0x14) = *(uint *)(unaff_EBP + -0x14) | 4;
    }
    if ((*(uint *)(unaff_EBP + -0x28) & 0x4000000) != 0) {
      *(uint *)(unaff_EBP + -0x14) = *(uint *)(unaff_EBP + -0x14) | 8;
    }
    uVar2 = *(undefined4 *)(unaff_EBP + -0x14);
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return uVar2;
}



/* grim_is_processor_feature_present @ 1001c0d4 */

uint __cdecl grim_is_processor_feature_present(DWORD param_1)

{
  WINBOOL WVar1;
  uint uVar2;
  int iVar3;
  int arg1;
  int unaff_EDI;
  _OSVERSIONINFOA *p_Var4;
  _OSVERSIONINFOA local_9c;
  char local_5;
  
  p_Var4 = &local_9c;
  for (iVar3 = 0x25; iVar3 != 0; iVar3 = iVar3 + -1) {
    p_Var4->dwOSVersionInfoSize = 0;
    p_Var4 = (_OSVERSIONINFOA *)&p_Var4->dwMajorVersion;
  }
  local_5 = '\0';
  local_9c.dwOSVersionInfoSize = 0x94;
  WVar1 = GetVersionExA(&local_9c);
  if (WVar1 == 0) {
    local_5 = '\x01';
  }
  if (local_9c.dwPlatformId == 1) {
    if ((local_9c.dwMajorVersion < 5) &&
       (((local_9c.dwMajorVersion != 4 || (local_9c.dwMinorVersion < 10)) ||
        ((ushort)local_9c.dwBuildNumber < 0x55d)))) {
      local_5 = '\x01';
    }
  }
  else {
    if (local_9c.dwPlatformId != 2) {
      return 0;
    }
    if (WVar1 != 0) {
      if (param_1 != 10) {
        uVar2 = IsProcessorFeaturePresent(param_1);
        return uVar2;
      }
      goto LAB_1001c179;
    }
  }
  if (param_1 == 6) {
    if (local_5 == '\0') {
      uVar2 = grim_cpuid_check_features(unaff_EDI);
      return uVar2 & 4;
    }
  }
  else {
    if (param_1 == 7) {
      uVar2 = grim_cpuid_check_3dnow(arg1);
      return uVar2;
    }
    if ((param_1 == 10) && (local_5 == '\0')) {
LAB_1001c179:
      uVar2 = grim_cpuid_check_features(unaff_EDI);
      return uVar2 & 8;
    }
  }
  return 0;
}



/* fpu_save_control_word @ 10020708 */

/* captures x87 FPU control word into DAT_1005db70 (used by DXT encode helpers) */

void __fastcall fpu_save_control_word(void)

{
  undefined4 in_ECX;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)in_ECX >> 0x10),in_FPUControlWord);
  fpu_control_word_saved_dxt = local_8;
  return;
}



/* grim_sse_math_init @ 100221d0 */

void __cdecl grim_sse_math_init(undefined4 *param_1)

{
  param_1[0x1c] = &LAB_10026970;
  *param_1 = grim_dxt1_color_lerp_2_3;
  param_1[0xd] = &LAB_100266f0;
  param_1[0x1b] = &LAB_100267e0;
  param_1[0xb] = &LAB_100278b0;
  param_1[0x30] = &LAB_100265d0;
  param_1[0x2f] = &LAB_100261f0;
  param_1[0x11] = &LAB_10026490;
  param_1[0x36] = &LAB_10026580;
  param_1[0x35] = &LAB_10026280;
  param_1[0x34] = &LAB_100263f0;
  param_1[0x33] = &LAB_10026520;
  param_1[0x32] = &LAB_10026130;
  param_1[0x31] = &LAB_10026330;
  param_1[0x12] = &LAB_100272d0;
  param_1[0x16] = &LAB_10026630;
  param_1[0x19] = &LAB_10026d10;
  param_1[0x18] = &LAB_10026bf0;
  param_1[0x13] = &LAB_10026a50;
  param_1[0x2c] = &LAB_10026b80;
  param_1[0x14] = &LAB_10026ae0;
  param_1[0x10] = &LAB_10025fe0;
  param_1[0x15] = &LAB_10025f00;
  param_1[8] = &LAB_10026090;
  param_1[7] = &LAB_10025e30;
  param_1[10] = &LAB_10026f60;
  param_1[9] = grim_dxt1_color_lerp_1_2;
  param_1[6] = &LAB_10026de0;
  param_1[5] = &LAB_10025ca0;
  param_1[4] = &LAB_10027590;
  param_1[3] = &LAB_10025ce0;
  param_1[2] = &LAB_10027060;
  param_1[1] = &LAB_10026ea0;
  return;
}



/* grim_sse2_math_init @ 100222e0 */

void __cdecl grim_sse2_math_init(undefined4 *param_1)

{
  param_1[0x1c] = &LAB_10027c00;
  *param_1 = grim_dxt1_color_lerp_2_3;
  param_1[0xd] = &LAB_10027980;
  param_1[0x1b] = &LAB_10027a70;
  param_1[0xb] = &LAB_100278b0;
  param_1[0x30] = &LAB_100265d0;
  param_1[0x2f] = &LAB_100261f0;
  param_1[0x11] = &LAB_10026490;
  param_1[0x36] = &LAB_10026580;
  param_1[0x35] = &LAB_10026280;
  param_1[0x34] = &LAB_100263f0;
  param_1[0x33] = &LAB_10026520;
  param_1[0x32] = &LAB_10026130;
  param_1[0x31] = &LAB_10026330;
  param_1[0x12] = &LAB_100272d0;
  param_1[0x16] = &LAB_10026630;
  param_1[0x19] = &LAB_10027e00;
  param_1[0x18] = &LAB_10027ce0;
  param_1[0x1f] = &LAB_10027820;
  param_1[0x1e] = &LAB_100277a0;
  param_1[0x13] = &LAB_10026a50;
  param_1[0x14] = &LAB_10026ae0;
  param_1[0x10] = &LAB_100276f0;
  param_1[0x15] = &LAB_100271f0;
  param_1[8] = &LAB_10026090;
  param_1[7] = &LAB_10027120;
  param_1[10] = &LAB_10026f60;
  param_1[9] = grim_dxt1_color_lerp_1_2;
  param_1[6] = &LAB_10026de0;
  param_1[5] = &LAB_10025ca0;
  param_1[4] = &LAB_10027590;
  param_1[3] = &LAB_10025ce0;
  param_1[2] = &LAB_10027060;
  param_1[1] = &LAB_10026ea0;
  return;
}



/* grim_init_mmx_sse_functions @ 100224c5 */

/* fills a function pointer table with MMX/SSE implementations based on CPUID */

void __cdecl grim_init_mmx_sse_functions(undefined4 *table)

{
  ulonglong uVar1;
  
  uVar1 = grim_dxt_color_block_optimize();
  if (((uVar1 & 0x20) != 0) && ((char)uVar1 < '\0')) {
    *table = &LAB_1002dca8;
    table[1] = &LAB_1002d1ea;
    table[2] = &LAB_1002df69;
    table[3] = &LAB_1002943a;
    table[5] = &LAB_1002dcfd;
    table[6] = &LAB_1002d25b;
    table[7] = grim_dxt_color_distance_calc;
    table[8] = &LAB_1002dfeb;
    table[9] = &LAB_1002dd36;
    table[10] = &LAB_1002d7a2;
    table[0xb] = &LAB_1002966c;
    table[0xc] = &LAB_1002e393;
    table[0xd] = &LAB_1002e3d6;
    table[0xe] = grim_jpg_huff_tree_optimize;
    table[0xf] = &LAB_1002d92f;
    table[0x10] = &LAB_1002e04a;
    table[0x11] = &LAB_1002dd9a;
    table[0x12] = &LAB_1002d1ce;
    table[0x13] = &LAB_10027ed0;
    table[0x14] = &LAB_10027f69;
    table[0x15] = grim_jpg_marker_read_sos;
    table[0x16] = &LAB_1002e4ba;
    table[0x17] = grim_dxt_color_endpoint_refine;
    table[0x18] = &LAB_10028079;
    table[0x19] = &LAB_100284aa;
    table[0x1a] = &LAB_1002973b;
    table[0x1b] = &LAB_1002978b;
    table[0x1c] = &LAB_10029876;
    table[0x1d] = grim_dxt_color_quantize_2bit;
    table[0x1e] = &LAB_10029952;
    table[0x1f] = &LAB_100299b5;
    table[0x20] = &LAB_10029a13;
    table[0x21] = &LAB_10029a6c;
    table[0x22] = &LAB_1002e5dc;
    table[0x23] = grim_dxt_color_match_block;
    table[0x24] = grim_dxt_color_match_2bit_a;
    table[0x25] = &LAB_10029ab3;
    table[0x26] = &LAB_10029b5b;
    table[0x27] = grim_dxt_alpha_block_compress;
    table[0x28] = grim_dxt_alpha_endpoint_refine;
    table[0x29] = &LAB_1002b01f;
    table[0x2a] = grim_dxt_alpha_quantize;
    table[0x2b] = grim_dxt_color_match_2bit_b;
    table[0x2c] = &LAB_10028831;
    table[0x36] = &LAB_1002e17c;
    table[0x33] = &LAB_1002d321;
    table[0x30] = &LAB_1002de32;
    table[0x2e] = &LAB_1002de7b;
    table[0x34] = &LAB_1002e1ed;
    table[0x31] = &LAB_1002d392;
    table[0x37] = grim_dxt_color_endpoint_pick;
    table[0x38] = &LAB_1002893c;
    table[0x35] = &LAB_1002e2b5;
    table[0x2f] = &LAB_1002debe;
    table[0x32] = &LAB_1002d466;
    table[4] = &LAB_1002caa2;
    table[0x2d] = grim_dxt_color_cluster_fit;
    if (((uVar1 & 0x100) != 0) && ((uVar1 & 0x200) != 0)) {
      table[0xf] = grim_jpg_huff_tree_init;
      table[0x12] = grim_jpg_huff_table_build;
      table[0x26] = &LAB_10029c2d;
      table[0x27] = grim_dxt_alpha_cluster_fit;
      table[0x18] = &LAB_10028295;
    }
  }
  return;
}



/* grim_sse_matrix_identity @ 1002290c */

/* [binja] float* __stdcall sub_1002290c(float* arg1, float* arg2) */

float * grim_sse_matrix_identity(float *arg1,float *arg2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float10 fVar5;
  
  fVar5 = (float10)*arg2 * (float10)*arg2 + (float10)arg2[1] * (float10)arg2[1] +
          (float10)arg2[2] * (float10)arg2[2];
  fVar1 = (float)fVar5;
  if (fVar1 == 0.0) {
    ffree(fVar5);
    *arg1 = 0.0;
    arg1[1] = 0.0;
    arg1[2] = 0.0;
  }
  else if ((uint)ABS((float)(fVar5 - (float10)1)) < 0x3727c5ad) {
    if (arg1 != arg2) {
      *arg1 = *arg2;
      arg1[1] = arg2[1];
      arg1[2] = arg2[2];
    }
  }
  else {
    uVar4 = (uint)fVar1 >> 0xc & 0xff8;
    fVar3 = ((float)((uint)fVar1 & 0xffffff | 0x3f000000) * *(float *)(&DAT_100544e0 + uVar4) +
            *(float *)(&DAT_100544e4 + uVar4)) * (float)(0xbeffffffU - (int)fVar1 >> 1 & 0xff800000)
    ;
    fVar1 = arg2[1];
    fVar2 = arg2[2];
    *arg1 = *arg2 * fVar3;
    arg1[1] = fVar1 * fVar3;
    arg1[2] = fVar2 * fVar3;
  }
  return arg1;
}



/* grim_sse_matrix_transpose @ 100229d6 */

/* [binja] int32_t __stdcall sub_100229d6(int32_t arg1, int32_t arg2, void* arg3) */

int grim_sse_matrix_transpose(int arg1,int arg2,void *arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  undefined4 local_44 [16];
  
  iVar5 = arg1;
  if (arg3 == (void *)arg1) {
    if (arg2 != arg1) {
      iVar7 = -4;
      do {
        iVar6 = -0x10;
        fVar9 = (float10)*(float *)((int)arg3 + iVar7 * 4 + 0x10);
        fVar10 = (float10)*(float *)((int)arg3 + iVar7 * 4 + 0x20);
        fVar11 = (float10)*(float *)((int)arg3 + iVar7 * 4 + 0x30);
        fVar12 = (float10)*(float *)((int)arg3 + iVar7 * 4 + 0x40);
        do {
          *(float *)(arg1 + 0x40 + iVar6 * 4) =
               (float)(fVar12 * (float10)*(float *)(arg2 + 0x4c + iVar6 * 4) +
                       fVar10 * (float10)*(float *)(arg2 + 0x44 + iVar6 * 4) +
                      fVar9 * (float10)*(float *)(arg2 + 0x40 + iVar6 * 4) +
                      fVar11 * (float10)*(float *)(arg2 + 0x48 + iVar6 * 4));
          iVar6 = iVar6 + 4;
        } while (iVar6 != 0);
        ffree(fVar9);
        ffree(fVar10);
        ffree(fVar11);
        ffree(fVar12);
        arg1 = arg1 + 4;
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0);
      return iVar5;
    }
    puVar8 = local_44;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = *(undefined4 *)arg3;
      arg3 = (undefined4 *)((int)arg3 + 4);
      puVar8 = puVar8 + 1;
    }
    arg3 = local_44;
  }
  iVar7 = -4;
  do {
    iVar6 = -4;
    fVar1 = *(float *)arg2;
    fVar2 = *(float *)(arg2 + 4);
    fVar3 = *(float *)(arg2 + 8);
    fVar4 = *(float *)(arg2 + 0xc);
    do {
      *(float *)(arg1 + 0x10 + iVar6 * 4) =
           (float)((float10)fVar4 * (float10)*(float *)((int)arg3 + iVar6 * 4 + 0x40) +
                   (float10)fVar2 * (float10)*(float *)((int)arg3 + iVar6 * 4 + 0x20) +
                  (float10)fVar1 * (float10)*(float *)((int)arg3 + iVar6 * 4 + 0x10) +
                  (float10)fVar3 * (float10)*(float *)((int)arg3 + iVar6 * 4 + 0x30));
      iVar6 = iVar6 + 1;
    } while (iVar6 != 0);
    ffree((float10)fVar1);
    ffree((float10)fVar2);
    ffree((float10)fVar3);
    ffree((float10)fVar4);
    arg2 = arg2 + 0x10;
    arg1 = arg1 + 0x10;
    iVar7 = iVar7 + 1;
  } while (iVar7 != 0);
  return iVar5;
}



/* grim_sse_math_dispatch_setup @ 10022ab9 */

/* [binja] void* __stdcall sub_10022ab9(void* arg1, int32_t arg2, int32_t arg3) */

void * grim_sse_math_dispatch_setup(void *arg1,int arg2,int arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 local_48 [17];
  
  if ((arg1 == (void *)arg2) || (puVar5 = arg1, arg1 == (void *)arg3)) {
    puVar5 = local_48;
  }
  iVar8 = -4;
  do {
    iVar7 = -4;
    pfVar6 = (float *)(puVar5 + iVar8 + 4);
    fVar1 = *(float *)arg2;
    fVar2 = *(float *)(arg2 + 4);
    fVar3 = *(float *)(arg2 + 8);
    fVar4 = *(float *)(arg2 + 0xc);
    do {
      *pfVar6 = (float)((float10)fVar4 * (float10)*(float *)(arg3 + 0x40 + iVar7 * 4) +
                        (float10)fVar2 * (float10)*(float *)(arg3 + 0x20 + iVar7 * 4) +
                       (float10)fVar1 * (float10)*(float *)(arg3 + 0x10 + iVar7 * 4) +
                       (float10)fVar3 * (float10)*(float *)(arg3 + 0x30 + iVar7 * 4));
      pfVar6 = pfVar6 + 4;
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0);
    ffree((float10)fVar1);
    ffree((float10)fVar2);
    ffree((float10)fVar3);
    ffree((float10)fVar4);
    arg2 = arg2 + 0x10;
    iVar8 = iVar8 + 1;
  } while (iVar8 != 0);
  if (puVar5 != arg1) {
    puVar9 = arg1;
    for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar9 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar9 = puVar9 + 1;
    }
  }
  return arg1;
}



/* grim_d3dx_math_init @ 10022b47 */

void __cdecl grim_d3dx_math_init(undefined4 *param_1)

{
  *param_1 = &LAB_100226eb;
  param_1[1] = &LAB_10022789;
  param_1[2] = &LAB_10022873;
  param_1[3] = grim_sse_matrix_transpose;
  param_1[4] = grim_sse_math_dispatch_setup;
  param_1[5] = &LAB_10022754;
  param_1[6] = &LAB_10022814;
  param_1[7] = grim_sse_matrix_identity;
  return;
}



/* grim_fpu_control_word @ 10022b83 */

int __cdecl grim_fpu_control_word(int param_1,int param_2)

{
  return (param_1 + -1 + param_2) / param_2;
}



/* grim_fpu_set_precision @ 10022b93 */

int __cdecl grim_fpu_set_precision(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -1 + param_2;
  return iVar1 - iVar1 % param_2;
}



/* grim_fpu_set_round_and_precision @ 10022bab */

void __cdecl grim_fpu_set_round_and_precision(int param_1,int param_2,int param_3,int param_4,int param_5,uint param_6)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar1 = (undefined4 *)(param_1 + param_2 * 4);
  puVar3 = (undefined4 *)(param_3 + param_4 * 4);
  if (0 < param_5) {
    param_2 = param_5;
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
      param_2 = param_2 + -1;
      for (uVar2 = param_6 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        puVar5 = (undefined4 *)((int)puVar5 + 1);
      }
    } while (param_2 != 0);
  }
  return;
}



/* grim_sse2_matrix_multiply @ 10022bf2 */

void __cdecl grim_sse2_matrix_multiply(undefined4 *param_1,undefined4 *param_2,int param_3)

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



/* grim_check_sse2_available @ 10022c2f */

/* WARNING: Removing unreachable block (ram,0x10022c4c) */
/* [binja] int32_t __fastcall sub_10022c2f(int32_t arg1) */

int grim_check_sse2_available(int arg1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  uint uVar4;
  
  uVar4 = (uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
          (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
          (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1) |
          (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
          (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  uVar2 = uVar4 ^ 0x200000;
  uVar3 = 0;
  if (((uint)((uVar2 & 0x4000) != 0) * 0x4000 | (uint)((uVar2 & 0x800) != 0) * 0x800 |
       (uint)((uVar2 & 0x200) != 0) * 0x200 | (uint)((uVar2 & 0x100) != 0) * 0x100 |
       (uint)((uVar2 & 0x80) != 0) * 0x80 | (uint)((uVar2 & 0x40) != 0) * 0x40 |
       (uint)((uVar2 & 0x10) != 0) * 0x10 | (uint)((uVar2 & 4) != 0) * 4 | (uint)((uVar2 & 1) != 0)
       | (uint)((uVar2 & 0x200000) != 0) * 0x200000 | (uint)((uVar2 & 0x40000) != 0) * 0x40000) !=
      uVar4) {
    iVar1 = cpuid_Version_info(1);
    uVar3 = (*(uint *)(iVar1 + 8) & 0x800000) >> 0x17;
  }
  return uVar3;
}



/* grim_fpu_matrix_multiply @ 10022c61 */

void grim_fpu_matrix_multiply(void)

{
  int iVar1;
  int iVar2;
  int *unaff_ESI;
  int *piVar3;
  
  if ((0xffdc < unaff_ESI[7]) || (0xffdc < unaff_ESI[6])) {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x28;
    *(undefined4 *)(*unaff_ESI + 0x18) = 0xffdc;
    (**(code **)*unaff_ESI)();
  }
  if (unaff_ESI[0x30] != 8) {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0xd;
    *(int *)(*unaff_ESI + 0x18) = unaff_ESI[0x30];
    (**(code **)*unaff_ESI)();
  }
  if (10 < unaff_ESI[8]) {
    *(undefined4 *)(*unaff_ESI + 0x14) = 0x18;
    *(int *)(*unaff_ESI + 0x18) = unaff_ESI[8];
    *(undefined4 *)(*unaff_ESI + 0x1c) = 10;
    (**(code **)*unaff_ESI)();
  }
  iVar2 = 0;
  unaff_ESI[0x43] = 1;
  unaff_ESI[0x44] = 1;
  if (0 < unaff_ESI[8]) {
    piVar3 = (int *)(unaff_ESI[0x31] + 0xc);
    do {
      if ((((piVar3[-1] < 1) || (4 < piVar3[-1])) || (*piVar3 < 1)) || (4 < *piVar3)) {
        *(undefined4 *)(*unaff_ESI + 0x14) = 0x10;
        (**(code **)*unaff_ESI)();
      }
      iVar1 = unaff_ESI[0x43];
      if (unaff_ESI[0x43] <= piVar3[-1]) {
        iVar1 = piVar3[-1];
      }
      unaff_ESI[0x43] = iVar1;
      iVar1 = unaff_ESI[0x44];
      if (unaff_ESI[0x44] <= *piVar3) {
        iVar1 = *piVar3;
      }
      iVar2 = iVar2 + 1;
      unaff_ESI[0x44] = iVar1;
      piVar3 = piVar3 + 0x15;
    } while (iVar2 < unaff_ESI[8]);
  }
  iVar2 = 0;
  unaff_ESI[0x45] = 8;
  if (0 < unaff_ESI[8]) {
    piVar3 = (int *)(unaff_ESI[0x31] + 0x1c);
    do {
      piVar3[2] = 8;
      iVar1 = grim_fpu_control_word(piVar3[-5] * unaff_ESI[6],unaff_ESI[0x43] << 3);
      *piVar3 = iVar1;
      iVar1 = grim_fpu_control_word(piVar3[-4] * unaff_ESI[7],unaff_ESI[0x44] << 3);
      piVar3[1] = iVar1;
      iVar1 = grim_fpu_control_word(piVar3[-5] * unaff_ESI[6],unaff_ESI[0x43]);
      piVar3[3] = iVar1;
      iVar1 = grim_fpu_control_word(piVar3[-4] * unaff_ESI[7],unaff_ESI[0x44]);
      piVar3[0xc] = 0;
      piVar3[4] = iVar1;
      *(undefined1 *)(piVar3 + 5) = 1;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0x15;
    } while (iVar2 < unaff_ESI[8]);
  }
  iVar2 = grim_fpu_control_word(unaff_ESI[7],unaff_ESI[0x44] << 3);
  unaff_ESI[0x46] = iVar2;
  if ((unaff_ESI[8] <= unaff_ESI[0x48]) && ((char)unaff_ESI[0x32] == '\0')) {
    *(undefined1 *)(unaff_ESI[99] + 0x10) = 0;
    return;
  }
  *(undefined1 *)(unaff_ESI[99] + 0x10) = 1;
  return;
}



/* grim_fpu_matrix_inverse @ 10022e1c */

uint grim_fpu_matrix_inverse(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *unaff_ESI;
  int iVar5;
  int *local_c;
  uint local_8;
  
  iVar2 = unaff_ESI[0x48];
  if (iVar2 == 1) {
    iVar2 = unaff_ESI[0x49];
    unaff_ESI[0x4d] = *(int *)(iVar2 + 0x1c);
    unaff_ESI[0x4e] = *(int *)(iVar2 + 0x20);
    uVar4 = *(uint *)(iVar2 + 0xc);
    *(undefined4 *)(iVar2 + 0x40) = *(undefined4 *)(iVar2 + 0x24);
    uVar1 = *(uint *)(iVar2 + 0x20) / uVar4;
    uVar3 = *(uint *)(iVar2 + 0x20) % uVar4;
    *(undefined4 *)(iVar2 + 0x34) = 1;
    *(undefined4 *)(iVar2 + 0x38) = 1;
    *(undefined4 *)(iVar2 + 0x3c) = 1;
    *(undefined4 *)(iVar2 + 0x44) = 1;
    if (uVar3 == 0) {
      uVar3 = uVar4;
    }
    *(uint *)(iVar2 + 0x48) = uVar3;
    unaff_ESI[0x50] = 0;
    unaff_ESI[0x4f] = 1;
  }
  else {
    if ((iVar2 < 1) || (4 < iVar2)) {
      *(undefined4 *)(*unaff_ESI + 0x14) = 0x18;
      *(int *)(*unaff_ESI + 0x18) = unaff_ESI[0x48];
      *(undefined4 *)(*unaff_ESI + 0x1c) = 4;
      (**(code **)*unaff_ESI)();
    }
    iVar2 = grim_fpu_control_word(unaff_ESI[6],unaff_ESI[0x43] << 3);
    unaff_ESI[0x4d] = iVar2;
    uVar1 = grim_fpu_control_word(unaff_ESI[7],unaff_ESI[0x44] << 3);
    unaff_ESI[0x4e] = uVar1;
    unaff_ESI[0x4f] = 0;
    local_8 = 0;
    if (0 < unaff_ESI[0x48]) {
      local_c = unaff_ESI + 0x49;
      do {
        iVar2 = *local_c;
        uVar1 = *(uint *)(iVar2 + 8);
        *(uint *)(iVar2 + 0x40) = *(int *)(iVar2 + 0x24) * uVar1;
        uVar4 = *(uint *)(iVar2 + 0x1c) % uVar1;
        *(int *)(iVar2 + 0x38) = *(int *)(iVar2 + 0xc);
        iVar5 = *(int *)(iVar2 + 0xc) * uVar1;
        *(uint *)(iVar2 + 0x34) = uVar1;
        *(int *)(iVar2 + 0x3c) = iVar5;
        if (uVar4 == 0) {
          uVar4 = uVar1;
        }
        *(uint *)(iVar2 + 0x44) = uVar4;
        uVar1 = *(uint *)(iVar2 + 0x20) % *(uint *)(iVar2 + 0xc);
        if (uVar1 == 0) {
          uVar1 = *(uint *)(iVar2 + 0xc);
        }
        *(uint *)(iVar2 + 0x48) = uVar1;
        if (10 < unaff_ESI[0x4f] + iVar5) {
          *(undefined4 *)(*unaff_ESI + 0x14) = 0xb;
          (**(code **)*unaff_ESI)();
        }
        if (0 < iVar5) {
          do {
            unaff_ESI[unaff_ESI[0x4f] + 0x50] = local_8;
            unaff_ESI[0x4f] = unaff_ESI[0x4f] + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
        uVar1 = local_8 + 1;
        local_c = local_c + 1;
        local_8 = uVar1;
      } while ((int)uVar1 < unaff_ESI[0x48]);
    }
  }
  return uVar1;
}



/* grim_fpu_matrix_transform_vec3 @ 10022f92 */

void grim_fpu_matrix_transform_vec3(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int *unaff_EBX;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int local_c;
  int *local_8;
  
  local_c = 0;
  if (0 < unaff_EBX[0x48]) {
    local_8 = unaff_EBX + 0x49;
    do {
      iVar1 = *local_8;
      if (*(int *)(iVar1 + 0x4c) == 0) {
        iVar2 = *(int *)(iVar1 + 0x10);
        if (((iVar2 < 0) || (3 < iVar2)) || (unaff_EBX[iVar2 + 0x24] == 0)) {
          *(undefined4 *)(*unaff_EBX + 0x14) = 0x33;
          *(int *)(*unaff_EBX + 0x18) = iVar2;
          (**(code **)*unaff_EBX)();
        }
        puVar3 = (undefined4 *)(**(code **)unaff_EBX[1])();
        puVar5 = (undefined4 *)unaff_EBX[iVar2 + 0x24];
        puVar6 = puVar3;
        for (iVar4 = 0x20; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        *(undefined2 *)puVar6 = *(undefined2 *)puVar5;
        *(undefined4 **)(iVar1 + 0x4c) = puVar3;
      }
      local_c = local_c + 1;
      local_8 = local_8 + 1;
    } while (local_c < unaff_EBX[0x48]);
  }
  return;
}



/* grim_fpu_matrix_inverse_and_transform @ 10023024 */

void __cdecl grim_fpu_matrix_inverse_and_transform(int param_1)

{
  grim_fpu_matrix_inverse();
  grim_fpu_matrix_transform_vec3();
  (*(code *)**(undefined4 **)(param_1 + 0x194))(param_1);
  (*(code *)**(undefined4 **)(param_1 + 0x184))(param_1);
  **(undefined4 **)(param_1 + 0x18c) = *(undefined4 *)(*(int *)(param_1 + 0x184) + 4);
  return;
}


