/* float_near_equal @ 1000cbff */

/* returns 1 when |a-b| < 1.1920929e-07 (FLT_EPSILON) */

int __cdecl float_near_equal(float a,float b)

{
  float fVar1;
  
  fVar1 = a - b;
  if ((!NAN(fVar1) && -1.1920929e-07 < fVar1 != (fVar1 == -1.1920929e-07)) &&
     (fVar1 < 1.1920929e-07 != (fVar1 == 1.1920929e-07))) {
    return 1;
  }
  return 0;
}



/* grim_vec2_normalize @ 1000cc2c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_vec2_normalize(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000cc33. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053d10)();
  return;
}



/* grim_math_dispatch_init @ 1000e568 */

/* [binja] float* __stdcall sub_1000e568(float* arg1, float arg2, float* arg3, int32_t arg4, float*
   arg5) */

float * grim_math_dispatch_init(float *arg1,float arg2,float *arg3,int arg4,float *arg5)

{
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
  *arg1 = arg2;
  arg1[5] = arg2;
  arg1[10] = arg2;
  arg1[0xf] = 1.0;
  if (arg4 != 0) {
    thunk_matrix_scale();
    if (arg3 == (float *)0x0) {
      thunk_matrix_rotate();
    }
    else {
      arg1[0xc] = arg1[0xc] - *arg3;
      arg1[0xd] = arg1[0xd] - arg3[1];
      arg1[0xe] = arg1[0xe] - arg3[2];
      thunk_matrix_rotate();
      arg1[0xc] = *arg3 + arg1[0xc];
      arg1[0xd] = arg1[0xd] + arg3[1];
      arg1[0xe] = arg3[2] + arg1[0xe];
    }
  }
  if (arg5 != (float *)0x0) {
    arg1[0xc] = *arg5 + arg1[0xc];
    arg1[0xd] = arg5[1] + arg1[0xd];
    arg1[0xe] = arg5[2] + arg1[0xe];
  }
  return arg1;
}



/* grim_quaternion_from_axis_angle_dispatch @ 1000e853 */

/* [binja] int32_t __stdcall sub_1000e853(int32_t arg1, float arg2) */

int grim_quaternion_from_axis_angle_dispatch(int arg1,float arg2)

{
  int iVar1;
  undefined4 in_stack_0000000c;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)grim_pfn_quat_from_axis)(arg1,arg2,in_stack_0000000c);
  return iVar1;
}



/* grim_quaternion_from_axis_angle @ 1000e873 */

/* [binja] float* __stdcall sub_1000e873(float arg1, float arg2, float arg3) */

float * grim_quaternion_from_axis_angle(float arg1,float arg2,float arg3)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  thunk_vec3_normalize();
  fVar2 = (float10)fcos((float10)(arg3 * 0.5));
  fVar3 = (float10)fsin((float10)(arg3 * 0.5));
  *(float *)((int)arg1 + 0xc) = (float)fVar2;
  fVar1 = (float)fVar3;
  *(float *)arg1 = local_18 * fVar1;
  *(float *)((int)arg1 + 4) = local_14 * fVar1;
  *(float *)((int)arg1 + 8) = local_10 * fVar1;
  return (float *)arg1;
}



/* grim_quaternion_mul_dispatch @ 1000e8cf */

/* [binja] int32_t __stdcall sub_1000e8cf(float arg1, float arg2, float arg3) */

int grim_quaternion_mul_dispatch(float arg1,float arg2,float arg3)

{
  int iVar1;
  undefined4 in_stack_00000010;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)grim_pfn_quat_mul)(arg1,arg2,arg3,in_stack_00000010);
  return iVar1;
}



/* grim_matrix_mul_dispatch @ 1000e9dc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_matrix_mul_dispatch(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000e9e3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053ca4)();
  return;
}



/* grim_matrix_transform_vec3_dispatch @ 1000eb4b */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_matrix_transform_vec3_dispatch(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000eb52. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053d08)();
  return;
}



/* grim_matrix_inverse_dispatch @ 1000ec12 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_matrix_inverse_dispatch(void)

{
                    /* WARNING: Could not recover jumptable at 0x1000ec12. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053d34)();
  return;
}



/* grim_matrix_transpose_dispatch @ 1000ec96 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_matrix_transpose_dispatch(void)

{
                    /* WARNING: Could not recover jumptable at 0x1000ec96. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053d38)();
  return;
}



/* grim_quaternion_multiply @ 1000ed37 */

/* [binja] int32_t __stdcall sub_1000ed37(int32_t arg1, int32_t arg2, float arg3) */

int grim_quaternion_multiply(int arg1,int arg2,float arg3)

{
  int iVar1;
  undefined4 in_stack_00000010;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)grim_pfn_quat_mul_2)(arg1,arg2,arg3,in_stack_00000010);
  return iVar1;
}



/* grim_quaternion_multiply_6arg @ 1000ee44 */

/* [binja] int32_t __stdcall sub_1000ee44(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_quaternion_multiply_6arg(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  int iVar1;
  
  grim_select_renderer_backend(1);
  iVar1 = (*(code *)grim_pfn_quat_mul_6)(arg1,arg2,arg3,arg4,arg5,arg6);
  return iVar1;
}



/* grim_quaternion_from_euler @ 1000ee6e */

/* [binja] int32_t __stdcall sub_1000ee6e(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4,
   int32_t arg5, float arg6) */

int grim_quaternion_from_euler(int arg1,int arg2,int arg3,int arg4,int arg5,float arg6)

{
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  thunk_quaternion_mul((int)local_24,arg2,(float)arg5);
  thunk_quaternion_mul((int)local_14,arg3,(float)arg4);
  thunk_quaternion_mul(arg1,(int)local_24,(float)local_14);
  return arg1;
}



/* grim_quaternion_slerp_dispatch @ 1000eec5 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void grim_quaternion_slerp_dispatch(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000eed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_10053d0c)();
  return;
}



/* grim_quaternion_slerp @ 1000ef05 */

/* [binja] int32_t* __stdcall sub_1000ef05(int32_t* arg1, int32_t* arg2, int32_t arg3, int32_t arg4,
   float arg5, float arg6) */

int * grim_quaternion_slerp(int *arg1,int *arg2,int arg3,int arg4,float arg5,float arg6)

{
  int iVar1;
  undefined1 local_24 [16];
  undefined1 local_14 [16];
  
  iVar1 = float_near_equal(arg5 + arg6,0.0);
  if (iVar1 == 0) {
    thunk_quaternion_mul((int)local_24,(int)arg2,(float)arg3);
    thunk_quaternion_mul((int)local_14,(int)arg2,(float)arg4);
    thunk_quaternion_mul((int)arg1,(int)local_24,(float)local_14);
  }
  else if (arg1 != arg2) {
    *arg1 = *arg2;
    arg1[1] = arg2[1];
    arg1[2] = arg2[2];
    arg1[3] = arg2[3];
  }
  return arg1;
}



/* grim_matrix_identity_dispatch @ 1000ef90 */

void grim_matrix_identity_dispatch(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000ef97. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)grim_pfn_matrix_identity)();
  return;
}



/* grim_vec2_normalize @ 1000f296 */

/* [binja] int32_t* __stdcall sub_1000f296(int32_t* arg1, float arg2) */

int * grim_vec2_normalize(int *arg1,float arg2)

{
  float a;
  int iVar1;
  float *extraout_ECX;
  float fVar2;
  
  a = *(float *)((int)arg2 + 4) * *(float *)((int)arg2 + 4) + *(float *)arg2 * *(float *)arg2;
  iVar1 = float_near_equal(a,1.0);
  if (iVar1 == 0) {
    if (a <= 1.1754944e-38) {
      *arg1 = 0;
      arg1[1] = 0;
      return arg1;
    }
    fVar2 = (1.0 / SQRT(a)) * extraout_ECX[1];
    *arg1 = (int)((1.0 / SQRT(a)) * *extraout_ECX);
  }
  else {
    if ((float *)arg1 == extraout_ECX) {
      return arg1;
    }
    *arg1 = (int)*extraout_ECX;
    fVar2 = extraout_ECX[1];
  }
  arg1[1] = (int)fVar2;
  return arg1;
}



/* grim_vec2_transform_full @ 1000f323 */

/* [binja] float* __stdcall sub_1000f323(float* arg1, float* arg2, float* arg3) */

float * grim_vec2_transform_full(float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  fVar1 = arg3[1];
  fVar2 = *arg2;
  fVar3 = arg3[5];
  fVar4 = arg2[1];
  fVar5 = arg3[0xd];
  fVar6 = arg3[2];
  fVar7 = *arg2;
  fVar8 = arg3[6];
  fVar9 = arg2[1];
  fVar10 = arg3[0xe];
  fVar11 = arg3[3];
  fVar12 = *arg2;
  fVar13 = arg3[7];
  fVar14 = arg2[1];
  fVar15 = arg3[0xf];
  *arg1 = *arg2 * *arg3 + arg3[4] * arg2[1] + arg3[0xc];
  arg1[1] = fVar3 * fVar4 + fVar1 * fVar2 + fVar5;
  arg1[2] = fVar8 * fVar9 + fVar6 * fVar7 + fVar10;
  arg1[3] = fVar13 * fVar14 + fVar11 * fVar12 + fVar15;
  return arg1;
}



/* grim_vec2_transform_perspective @ 1000f38e */

/* [binja] float* __stdcall sub_1000f38e(float* arg1, float* arg2, float* arg3) */

float * grim_vec2_transform_perspective(float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  
  fVar1 = *arg2;
  fVar2 = arg3[1];
  fVar3 = arg2[1];
  fVar4 = arg3[5];
  fVar5 = arg3[0xd];
  fVar6 = arg3[0xf] + arg2[1] * arg3[7] + *arg2 * arg3[3];
  *arg1 = arg3[0xc] + arg2[1] * arg3[4] + *arg2 * *arg3;
  arg1[1] = fVar5 + fVar3 * fVar4 + fVar1 * fVar2;
  iVar7 = float_near_equal(fVar6,1.0);
  if (iVar7 == 0) {
    fVar6 = 1.0 / fVar6;
    *arg1 = fVar6 * *arg1;
    arg1[1] = fVar6 * arg1[1];
  }
  return arg1;
}



/* grim_vec2_transform_linear @ 1000f40e */

/* [binja] float* __stdcall sub_1000f40e(float* arg1, float* arg2, float* arg3) */

float * grim_vec2_transform_linear(float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = arg3[1];
  fVar2 = *arg2;
  fVar3 = arg3[5];
  fVar4 = arg2[1];
  *arg1 = *arg2 * *arg3 + arg3[4] * arg2[1];
  arg1[1] = fVar3 * fVar4 + fVar1 * fVar2;
  return arg1;
}



/* grim_vec3_normalize @ 1000f44a */

/* [binja] float* __stdcall sub_1000f44a(float* arg1, float arg2) */

float * grim_vec3_normalize(float *arg1,float arg2)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  float local_10;
  float local_c;
  float local_8;
  
  fVar2 = *(float *)((int)arg2 + 8) * *(float *)((int)arg2 + 8) +
          *(float *)((int)arg2 + 4) * *(float *)((int)arg2 + 4) + *(float *)arg2 * *(float *)arg2;
  iVar3 = float_near_equal(fVar2,1.0);
  if (iVar3 == 0) {
    if (fVar2 <= 1.1754944e-38) {
      *arg1 = 0.0;
      arg1[1] = 0.0;
      arg1[2] = 0.0;
      return arg1;
    }
    fVar2 = 1.0 / SQRT(fVar2);
    local_10 = fVar2 * *(float *)arg2;
    local_c = fVar2 * *(float *)((int)arg2 + 4);
    pfVar1 = (float *)((int)arg2 + 8);
    arg2 = (float)&local_10;
    local_8 = fVar2 * *pfVar1;
  }
  else if (arg1 == (float *)arg2) {
    return arg1;
  }
  *arg1 = *(float *)arg2;
  arg1[1] = *(float *)((int)arg2 + 4);
  arg1[2] = *(float *)((int)arg2 + 8);
  return arg1;
}



/* grim_vec3_transform_perspective @ 1000f4ea */

/* [binja] float* __stdcall sub_1000f4ea(float* arg1, float* arg2, float* arg3) */

float * grim_vec3_transform_perspective(float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  int iVar16;
  
  fVar1 = *arg2;
  fVar2 = arg3[2];
  fVar3 = *arg2;
  fVar4 = arg3[1];
  fVar5 = arg2[1];
  fVar6 = arg3[6];
  fVar7 = arg2[1];
  fVar8 = arg3[5];
  fVar9 = arg2[2];
  fVar10 = arg3[10];
  fVar11 = arg2[2];
  fVar12 = arg3[9];
  fVar13 = arg3[0xd];
  fVar14 = arg3[0xe];
  fVar15 = arg3[0xf] + arg2[2] * arg3[0xb] + arg2[1] * arg3[7] + *arg2 * arg3[3];
  *arg1 = arg3[0xc] + arg2[2] * arg3[8] + arg2[1] * arg3[4] + *arg2 * *arg3;
  arg1[1] = fVar13 + fVar11 * fVar12 + fVar7 * fVar8 + fVar3 * fVar4;
  arg1[2] = fVar14 + fVar9 * fVar10 + fVar5 * fVar6 + fVar1 * fVar2;
  iVar16 = float_near_equal(fVar15,1.0);
  if (iVar16 == 0) {
    fVar15 = 1.0 / fVar15;
    *arg1 = fVar15 * *arg1;
    arg1[1] = fVar15 * arg1[1];
    arg1[2] = fVar15 * arg1[2];
  }
  return arg1;
}


