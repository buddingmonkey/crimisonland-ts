/* heading_normalize_or_calc @ 00413540 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl heading_normalize_or_calc(float param_1)

{
  float fVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  iVar2 = render_overlay_player_index;
  fVar1 = (&player_state_table)[render_overlay_player_index].heading;
  while (fVar1 < 0.0) {
    fVar1 = (&player_state_table)[iVar2].heading + 6.2831855;
    (&player_state_table)[iVar2].heading = fVar1;
  }
  fVar1 = (&player_state_table)[iVar2].heading;
  while (6.2831855 < fVar1) {
    fVar1 = (&player_state_table)[iVar2].heading - 6.2831855;
    (&player_state_table)[iVar2].heading = fVar1;
  }
  fVar3 = ABS(param_1 - (&player_state_table)[iVar2].heading);
  fVar1 = (&player_state_table)[iVar2].heading;
  if ((&player_state_table)[iVar2].heading < param_1) {
    fVar1 = param_1;
  }
  fVar4 = (&player_state_table)[iVar2].heading;
  if (param_1 < (&player_state_table)[iVar2].heading) {
    fVar4 = param_1;
  }
  fVar4 = ABS((6.2831855 - fVar1) + fVar4);
  fVar1 = fVar4;
  if (fVar3 < fVar4) {
    fVar1 = fVar3;
  }
  if (fVar3 <= fVar4) {
    if ((&player_state_table)[iVar2].heading < param_1) {
      player_turn_speed_accumulated = frame_dt * fVar1 * 5.0;
      goto LAB_00413686;
    }
  }
  else if (param_1 < (&player_state_table)[iVar2].heading) {
    player_turn_speed_accumulated = frame_dt * fVar1 * 5.0;
    goto LAB_00413686;
  }
  player_turn_speed_accumulated = frame_dt * fVar1 * -5.0;
LAB_00413686:
  (&player_state_table)[iVar2].heading = player_turn_speed_accumulated + (&player_state_table)[iVar2].heading;
  return;
}



/* vec2_sub @ 00417640 */

/* [binja] float* __thiscall sub_417640(float* arg1, float* arg2, float* arg3) */

float * __thiscall vec2_sub(void *this,float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)((int)this + 4);
  fVar2 = arg2[1];
  *arg1 = *(float *)this - *arg2;
  arg1[1] = fVar1 - fVar2;
  return arg1;
}



/* vec2_length @ 00417660 */

/* returns sqrt(x*x + y*y) for a 2-float vector */

float __cdecl vec2_length(float *v)

{
  return SQRT(v[1] * v[1] + *v * *v);
}



/* vec2_add @ 0041e270 */

/* [binja] int32_t sub_41e270(float* arg1, float* arg2) */

int __cdecl vec2_add(float *arg1,float *arg2)

{
  *arg1 = *arg1 + *arg2;
  arg1[1] = arg2[1] + arg1[1];
  return 0;
}



/* vec2_add_inplace @ 0041e400 */

/* adds delta XY into pos; unused param_1 in decompile */

void __cdecl vec2_add_inplace(int unused,float *pos,float *delta)

{
  *pos = *pos + *delta;
  pos[1] = delta[1] + pos[1];
  return;
}



/* angle_approach @ 0041f430 */

/* wraps angle into [0,2pi] and steps toward target using shortest arc */

void __cdecl angle_approach(float *angle,float target,float rate)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = *angle;
  while (fVar1 < 0.0) {
    fVar1 = *angle + 6.2831855;
    *angle = fVar1;
  }
  fVar1 = *angle;
  while (6.2831855 < fVar1) {
    fVar1 = *angle - 6.2831855;
    *angle = fVar1;
  }
  fVar2 = ABS(target - *angle);
  fVar1 = *angle;
  if (*angle < target) {
    fVar1 = target;
  }
  fVar3 = *angle;
  if (target < *angle) {
    fVar3 = target;
  }
  fVar3 = ABS((6.2831855 - fVar1) + fVar3);
  fVar1 = fVar3;
  if (fVar2 < fVar3) {
    fVar1 = fVar2;
  }
  if (1.0 < fVar1) {
    fVar1 = 1.0;
  }
  if (fVar2 <= fVar3) {
    fVar1 = frame_dt * fVar1 * rate;
    if (*angle < target) {
      *angle = fVar1 + *angle;
      return;
    }
  }
  else {
    fVar1 = frame_dt * fVar1 * rate;
    if (target < *angle) {
      *angle = fVar1 + *angle;
      return;
    }
  }
  *angle = *angle - fVar1;
  return;
}



/* vec2_add_offset @ 0044ecf0 */

/* [binja] float* __thiscall sub_44ecf0(float* arg1, float* arg2, float* arg3) */

float * __thiscall vec2_add_offset(void *this,float *arg1,float *arg2,float *arg3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = arg2[1];
  fVar2 = *(float *)((int)this + 4);
  *arg1 = *arg2 + *(float *)this;
  arg1[1] = fVar1 + fVar2;
  return arg1;
}



/* float_near_equal @ 00452ef0 */

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



/* FUN_00452f1d @ 00452f1d */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_452f1d() */

int FUN_00452f1d(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00452f24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x20)();
  return iVar1;
}



/* FUN_00452f30 @ 00452f30 */

void FUN_00452f30(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_004795e4)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_00452f5a @ 00452f5a */

void FUN_00452f5a(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar3 = (fVar2 - (fVar1 + fVar1)) + param_6;
  fVar4 = fVar1 * 3.0 - (fVar2 + fVar2);
  *param_1 = (fVar2 - fVar1) * *param_5 + fVar4 * *param_4 + fVar3 * *param_3 + fVar5 * *param_2;
  param_1[1] = fVar5 * param_2[1] +
               fVar3 * param_3[1] + fVar4 * param_4[1] + (fVar2 - fVar1) * param_5[1];
  return;
}



/* FUN_00452fe8 @ 00452fe8 */

void FUN_00452fe8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_0047965c)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* FUN_00453012 @ 00453012 */

void FUN_00453012(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - param_6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + param_6;
  *param_1 = ((fVar2 - fVar1) * *param_5 + fVar3 * *param_4 + fVar4 * *param_3 + fVar5 * *param_2) *
             0.5;
  param_1[1] = (fVar5 * param_2[1] +
               fVar4 * param_3[1] + fVar3 * param_4[1] + (fVar2 - fVar1) * param_5[1]) * 0.5;
  return;
}



/* vec2_bilinear_interp @ 004530f0 */

void vec2_bilinear_interp(float *param_1,float *param_2,float *param_3,float *param_4,float param_5,
                 float param_6)

{
  *param_1 = (*param_4 - *param_2) * param_6 + (*param_3 - *param_2) * param_5 + *param_2;
  param_1[1] = (param_4[1] - param_2[1]) * param_6 + (param_3[1] - param_2[1]) * param_5 +
               param_2[1];
  return;
}



/* vec3_hermite_spline @ 00453197 */

void vec3_hermite_spline(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar3 = (fVar2 - (fVar1 + fVar1)) + param_6;
  fVar4 = fVar1 * 3.0 - (fVar2 + fVar2);
  fVar2 = fVar2 - fVar1;
  *param_1 = fVar2 * *param_5 + fVar4 * *param_4 + fVar3 * *param_3 + fVar5 * *param_2;
  param_1[1] = fVar5 * param_2[1] + fVar3 * param_3[1] + fVar4 * param_4[1] + fVar2 * param_5[1];
  param_1[2] = fVar5 * param_2[2] + fVar3 * param_3[2] + fVar4 * param_4[2] + fVar2 * param_5[2];
  return;
}



/* vec3_catmull_rom_spline @ 0045326f */

void vec3_catmull_rom_spline(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - param_6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + param_6;
  fVar2 = fVar2 - fVar1;
  *param_1 = (fVar2 * *param_5 + fVar3 * *param_4 + fVar4 * *param_3 + fVar5 * *param_2) * 0.5;
  param_1[1] = (fVar5 * param_2[1] + fVar4 * param_3[1] + fVar3 * param_4[1] + fVar2 * param_5[1]) *
               0.5;
  param_1[2] = (fVar5 * param_2[2] + fVar4 * param_3[2] + fVar3 * param_4[2] + fVar2 * param_5[2]) *
               0.5;
  return;
}



/* vec3_bilinear_interp @ 0045336f */

void vec3_bilinear_interp(float *param_1,float *param_2,float *param_3,float *param_4,float param_5,
                 float param_6)

{
  *param_1 = (*param_4 - *param_2) * param_6 + (*param_3 - *param_2) * param_5 + *param_2;
  param_1[1] = (param_4[1] - param_2[1]) * param_6 + (param_3[1] - param_2[1]) * param_5 +
               param_2[1];
  param_1[2] = (param_4[2] - param_2[2]) * param_6 + (param_3[2] - param_2[2]) * param_5 +
               param_2[2];
  return;
}



/* mat4x4_lerp @ 00453640 */

void mat4x4_lerp(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = ((fVar2 + fVar2) - fVar1 * 3.0) + 1.0;
  fVar4 = (fVar2 - (fVar1 + fVar1)) + param_6;
  fVar3 = fVar1 * 3.0 - (fVar2 + fVar2);
  fVar2 = fVar2 - fVar1;
  *param_1 = fVar2 * *param_5 + fVar3 * *param_4 + fVar4 * *param_3 + fVar5 * *param_2;
  param_1[1] = fVar5 * param_2[1] + fVar4 * param_3[1] + fVar3 * param_4[1] + fVar2 * param_5[1];
  param_1[2] = fVar5 * param_2[2] + fVar4 * param_3[2] + fVar3 * param_4[2] + fVar2 * param_5[2];
  param_1[3] = fVar5 * param_2[3] + fVar4 * param_3[3] + fVar3 * param_4[3] + fVar2 * param_5[3];
  return;
}



/* mat4x4_build_from_axes @ 0045373b */

void mat4x4_build_from_axes(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                 float param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = param_6 * param_6;
  fVar2 = param_6 * fVar1;
  fVar5 = (fVar1 * 2.0 - fVar2) - param_6;
  fVar4 = (fVar2 * 3.0 - fVar1 * 5.0) + 2.0;
  fVar3 = (fVar1 * 4.0 - fVar2 * 3.0) + param_6;
  fVar2 = fVar2 - fVar1;
  *param_1 = (fVar2 * *param_5 + fVar3 * *param_4 + fVar4 * *param_3 + fVar5 * *param_2) * 0.5;
  param_1[1] = (fVar5 * param_2[1] + fVar4 * param_3[1] + fVar3 * param_4[1] + fVar2 * param_5[1]) *
               0.5;
  param_1[2] = (fVar5 * param_2[2] + fVar4 * param_3[2] + fVar3 * param_4[2] + fVar2 * param_5[2]) *
               0.5;
  param_1[3] = (fVar5 * param_2[3] + fVar4 * param_3[3] + fVar3 * param_4[3] + fVar2 * param_5[3]) *
               0.5;
  return;
}



/* mat4x4_set_translation @ 0045385d */

void mat4x4_set_translation(float *param_1,float *param_2,float *param_3,float *param_4,float param_5,
                 float param_6)

{
  *param_1 = (*param_4 - *param_2) * param_6 + (*param_3 - *param_2) * param_5 + *param_2;
  param_1[1] = (param_4[1] - param_2[1]) * param_6 + (param_3[1] - param_2[1]) * param_5 +
               param_2[1];
  param_1[2] = (param_4[2] - param_2[2]) * param_6 + (param_3[2] - param_2[2]) * param_5 +
               param_2[2];
  param_1[3] = (param_4[3] - param_2[3]) * param_6 + (param_3[3] - param_2[3]) * param_5 +
               param_2[3];
  return;
}



/* matrix_build_rotation_x @ 00454433 */

/* [binja] float* __stdcall sub_454433(float* arg1, float arg2) */

float * matrix_build_rotation_x(float *arg1,float arg2)

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



/* mat4x4_rotate_y @ 004544c9 */

/* [binja] float* __stdcall sub_4544c9(float* arg1, float arg2) */

float * mat4x4_rotate_y(float *arg1,float arg2)

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



/* mat4x4_rotate_z @ 00454560 */

/* [binja] float* __stdcall sub_454560(float* arg1, float arg2) */

float * mat4x4_rotate_z(float *arg1,float arg2)

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



/* mat4x4_rotate_axis @ 004545fc */

/* [binja] float* __stdcall sub_4545fc(float* arg1, float arg2, float arg3) */

float * mat4x4_rotate_axis(float *arg1,float arg2,float arg3)

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
  thunk_FUN_0045315a();
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



/* vec3_set @ 004547f3 */

/* [binja] int32_t __stdcall sub_4547f3(float arg1, float arg2, float arg3); wrapper calls
   PTR_FUN_00479640 (idx 0x28) */

float * vec3_set(float *arg1,float arg2,float arg3,float arg4)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479640)(arg1,arg2,arg3,arg4);
  return pfVar1;
}



/* FUN_00454b44 @ 00454b44 */

/* [binja] int32_t __stdcall sub_454b44(int arg1, float arg2); wrapper calls PTR_FUN_00479614 (idx
   0x1d) */

float * FUN_00454b44(float *arg1,float *arg2,float arg3)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479614)(arg1,arg2,arg3);
  return pfVar1;
}



/* FUN_00454b64 @ 00454b64 */

/* [binja] float* __stdcall sub_454b64(float arg1, float arg2, float arg3) */

float * FUN_00454b64(float arg1,float arg2,float arg3)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  thunk_FUN_0045315a();
  fVar2 = (float10)fcos((float10)(arg3 * 0.5));
  fVar3 = (float10)fsin((float10)(arg3 * 0.5));
  *(float *)((int)arg1 + 0xc) = (float)fVar2;
  fVar1 = (float)fVar3;
  *(float *)arg1 = local_18 * fVar1;
  *(float *)((int)arg1 + 4) = local_14 * fVar1;
  *(float *)((int)arg1 + 8) = local_10 * fVar1;
  return (float *)arg1;
}



/* FUN_00454bc0 @ 00454bc0 */

/* [binja] int32_t __stdcall sub_454bc0(float arg1, float arg2, float arg3); wrapper calls
   PTR_FUN_00479604 (idx 0x19) */

float * FUN_00454bc0(float *arg1,float arg2,float arg3,float arg4)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479604)(arg1,arg2,arg3,arg4);
  return pfVar1;
}



/* FUN_00454ccd @ 00454ccd */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_454ccd() */

int FUN_00454ccd(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00454cd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x04)();
  return iVar1;
}



/* quat_slerp_squad @ 0045515f */

float * quat_slerp_squad(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5,
                    float param_6)

{
  float fVar1;
  float local_24 [4];
  float local_14 [4];
  
  quat_slerp_internal(local_24,param_2,param_5,param_6);
  quat_slerp_internal(local_14,param_3,param_4,param_6);
  fVar1 = (1.0 - param_6) * param_6;
  quat_slerp_internal(param_1,local_24,local_14,fVar1 + fVar1);
  return param_1;
}



/* quat_slerp_weighted @ 004551f6 */

undefined4 *
quat_slerp_weighted(undefined4 *param_1,undefined4 *param_2,float *param_3,float *param_4,float param_5,
            float param_6)

{
  float a;
  int iVar1;
  float local_24 [4];
  float local_14 [4];
  
  a = param_5 + param_6;
  iVar1 = float_near_equal(a,0.0);
  if (iVar1 == 0) {
    quat_slerp_internal(local_24,(float *)param_2,param_3,a);
    quat_slerp_internal(local_14,(float *)param_2,param_4,a);
    quat_slerp_internal((float *)param_1,local_24,local_14,param_6 / a);
  }
  else if (param_1 != param_2) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_2[3];
  }
  return param_1;
}



/* vec2_normalize_stdcall @ 00455587 */

/* [binja] int32_t* __stdcall sub_455587(int32_t* arg1, float arg2) */

int * vec2_normalize_stdcall(int *arg1,float arg2)

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



/* mat4_transform_vec4 @ 00455614 */

/* [binja] float* __stdcall sub_455614(float* arg1, float* arg2, float* arg3) */

float * mat4_transform_vec4(float *arg1,float *arg2,float *arg3)

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



/* mat4_transform_vec2 @ 0045567f */

/* [binja] float* __stdcall sub_45567f(float* arg1, float* arg2, float* arg3) */

float * mat4_transform_vec2(float *arg1,float *arg2,float *arg3)

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



/* FUN_004556ff @ 004556ff */

/* [binja] float* __stdcall sub_4556ff(float* arg1, float* arg2, float* arg3) */

float * FUN_004556ff(float *arg1,float *arg2,float *arg3)

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



/* FUN_0045573b @ 0045573b */

/* [binja] float* __stdcall sub_45573b(float* arg1, float arg2) */

float * FUN_0045573b(float *arg1,float arg2)

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



/* FUN_004557db @ 004557db */

/* [binja] float* __stdcall sub_4557db(float* arg1, float* arg2, float* arg3) */

float * FUN_004557db(float *arg1,float *arg2,float *arg3)

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



/* FUN_0045589a @ 0045589a */

float * FUN_0045589a(float *param_1,undefined4 param_2,int *param_3,int param_4,int param_5,
                    int param_6)

{
  float fVar1;
  float fVar2;
  
  switch(((param_6 != 0) << 1 | param_5 != 0) << 1 | param_4 != 0) {
  case '\0':
    break;
  case '\x01':
    break;
  case '\x02':
    break;
  case '\x03':
    goto LAB_0045596b;
  case '\x04':
    break;
  case '\x05':
    goto LAB_0045596b;
  case '\x06':
    goto LAB_0045596b;
  case '\a':
    thunk_renderer_dispatch_call_0x14();
LAB_0045596b:
    thunk_renderer_dispatch_call_0x14();
  }
  thunk_FUN_00453464();
  if (param_3 != (int *)0x0) {
    fVar2 = (float)param_3[2];
    if (param_3[2] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar1 = (float)*param_3;
    if (*param_3 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    *param_1 = fVar1 + fVar2 * (*param_1 + 1.0) * 0.5;
    fVar2 = (float)param_3[3];
    if (param_3[3] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar1 = (float)param_3[1];
    if (param_3[1] < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    param_1[1] = fVar1 + fVar2 * (1.0 - param_1[1]) * 0.5;
    param_1[2] = ((float)param_3[5] - (float)param_3[4]) * param_1[2] + (float)param_3[4];
  }
  return param_1;
}



/* FUN_00455a27 @ 00455a27 */

/* [binja] float* __stdcall sub_455a27(float* arg1, float* arg2, int32_t* arg3, int32_t* arg4,
   int32_t* arg5, int32_t* arg6) */

float * FUN_00455a27(float *arg1,float *arg2,int *arg3,int *arg4,int *arg5,int *arg6)

{
  float fVar1;
  float fVar2;
  
  switch(((arg6 != (int *)0x0) << 1 | arg5 != (int *)0x0) << 1 | arg4 != (int *)0x0) {
  case '\0':
    goto switchD_00455a64_default;
  case '\x01':
    goto LAB_00455b02;
  case '\x02':
    goto LAB_00455b02;
  case '\x03':
    break;
  case '\x04':
    goto LAB_00455b02;
  case '\x05':
    break;
  case '\x06':
    break;
  case '\a':
    thunk_renderer_dispatch_call_0x14();
    break;
  default:
    goto switchD_00455a64_default;
  }
  thunk_renderer_dispatch_call_0x14();
LAB_00455b02:
  thunk_FUN_00453f63();
switchD_00455a64_default:
  if (arg3 != (int *)0x0) {
    fVar1 = (float)*arg3;
    if (*arg3 < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    fVar2 = (float)arg3[2];
    if (arg3[2] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar2 = (*arg2 - fVar1) / fVar2;
    *arg1 = (fVar2 + fVar2) - 1.0;
    fVar1 = (float)arg3[1];
    if (arg3[1] < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    fVar2 = (float)arg3[3];
    if (arg3[3] < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar2 = (arg2[1] - fVar1) / fVar2;
    arg1[1] = -((fVar2 + fVar2) - 1.0);
    arg1[2] = (arg2[2] - (float)arg3[4]) / ((float)arg3[5] - (float)arg3[4]);
  }
  thunk_FUN_00453464();
  return arg1;
}



/* FUN_00455bcd @ 00455bcd */

/* [binja] float* __stdcall sub_455bcd(float* arg1, float arg2) */

float * FUN_00455bcd(float *arg1,float arg2)

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



/* FUN_00455c86 @ 00455c86 */

/* [binja] int32_t __stdcall sub_455c86(int32_t arg1, float arg2, float arg3, float arg4) */

int FUN_00455c86(int arg1,float arg2,float arg3,float arg4)

{
  float local_14 [4];
  
  thunk_FUN_00454bc0(local_14,arg2,arg3,arg4);
  thunk_renderer_dispatch_call_0x20();
  return arg1;
}



/* FUN_00455cbf @ 00455cbf */

undefined4 *
FUN_00455cbf(undefined4 *param_1,float *param_2,int param_3,undefined4 *param_4,float *param_5,
            int param_6,float *param_7)

{
  undefined4 uVar1;
  
  if (param_4 == (undefined4 *)0x0) {
    param_1[0xe] = 0;
    param_1[0xd] = 0;
    param_1[0xc] = 0;
    param_1[0xb] = 0;
    param_1[9] = 0;
    param_1[8] = 0;
    param_1[7] = 0;
    param_1[6] = 0;
    param_1[4] = 0;
    param_1[3] = 0;
    param_1[2] = 0;
    param_1[1] = 0;
    param_1[0xf] = 0x3f800000;
    param_1[10] = 0x3f800000;
    param_1[5] = 0x3f800000;
    *param_1 = 0x3f800000;
  }
  else if (param_3 == 0) {
    param_1[0xe] = 0;
    param_1[0xd] = 0;
    param_1[0xc] = 0;
    param_1[0xb] = 0;
    param_1[9] = 0;
    param_1[8] = 0;
    param_1[7] = 0;
    param_1[6] = 0;
    param_1[4] = 0;
    param_1[3] = 0;
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = *param_4;
    param_1[5] = param_4[1];
    uVar1 = param_4[2];
    param_1[0xf] = 0x3f800000;
    param_1[10] = uVar1;
  }
  else {
    thunk_renderer_dispatch_call_0x20();
    if (param_2 == (float *)0x0) {
      thunk_FUN_00453ca0();
      thunk_renderer_dispatch_call_0x14();
      thunk_renderer_dispatch_call_0x14();
    }
    else {
      thunk_FUN_00453ca0();
      param_1[0xe] = 0;
      param_1[0xd] = 0;
      param_1[0xc] = 0;
      param_1[0xb] = 0;
      param_1[9] = 0;
      param_1[8] = 0;
      param_1[7] = 0;
      param_1[6] = 0;
      param_1[4] = 0;
      param_1[3] = 0;
      param_1[2] = 0;
      param_1[1] = 0;
      param_1[0xf] = 0x3f800000;
      param_1[10] = 0x3f800000;
      param_1[5] = 0x3f800000;
      *param_1 = 0x3f800000;
      param_1[0xc] = -*param_2;
      param_1[0xd] = -param_2[1];
      param_1[0xe] = -param_2[2];
      thunk_renderer_dispatch_call_0x14();
      thunk_renderer_dispatch_call_0x14();
      thunk_renderer_dispatch_call_0x14();
      param_1[0xc] = (float)param_1[0xc] + *param_2;
      param_1[0xd] = param_2[1] + (float)param_1[0xd];
      param_1[0xe] = (float)param_1[0xe] + param_2[2];
    }
  }
  if (param_6 != 0) {
    thunk_renderer_dispatch_call_0x20();
    if (param_5 == (float *)0x0) {
      thunk_renderer_dispatch_call_0x14();
    }
    else {
      param_1[0xc] = (float)param_1[0xc] - *param_5;
      param_1[0xd] = (float)param_1[0xd] - param_5[1];
      param_1[0xe] = (float)param_1[0xe] - param_5[2];
      thunk_renderer_dispatch_call_0x14();
      param_1[0xc] = (float)param_1[0xc] + *param_5;
      param_1[0xd] = (float)param_1[0xd] + param_5[1];
      param_1[0xe] = (float)param_1[0xe] + param_5[2];
    }
  }
  if (param_7 != (float *)0x0) {
    param_1[0xc] = (float)param_1[0xc] + *param_7;
    param_1[0xd] = param_7[1] + (float)param_1[0xd];
    param_1[0xe] = param_7[2] + (float)param_1[0xe];
  }
  return param_1;
}



/* FUN_00455f73 @ 00455f73 */

void FUN_00455f73(float *param_1,float *param_2)

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
  
  thunk_FUN_00455281();
  fVar1 = local_c * param_2[2] + local_8 * param_2[3] + local_14 * *param_2 + local_10 * param_2[1];
  fVar4 = -local_14;
  fVar3 = -local_10;
  fVar2 = -local_c;
  fVar5 = -local_8;
  *param_1 = fVar4 * *param_2 + fVar1;
  param_1[4] = fVar3 * *param_2;
  param_1[8] = fVar2 * *param_2;
  param_1[0xc] = fVar5 * *param_2;
  param_1[1] = fVar4 * param_2[1];
  param_1[5] = fVar3 * param_2[1] + fVar1;
  param_1[9] = fVar2 * param_2[1];
  param_1[0xd] = fVar5 * param_2[1];
  param_1[2] = fVar4 * param_2[2];
  param_1[6] = fVar3 * param_2[2];
  param_1[10] = fVar2 * param_2[2] + fVar1;
  param_1[0xe] = fVar5 * param_2[2];
  param_1[3] = fVar4 * param_2[3];
  param_1[7] = fVar3 * param_2[3];
  param_1[0xb] = fVar2 * param_2[3];
  param_1[0xf] = fVar5 * param_2[3] + fVar1;
  return;
}



/* FUN_0045604d @ 0045604d */

void FUN_0045604d(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  thunk_FUN_00455281();
  fVar1 = local_14 * -2.0;
  fVar3 = local_10 * -2.0;
  fVar2 = local_c * -2.0;
  *param_1 = local_14 * fVar1 + 1.0;
  param_1[1] = fVar3 * local_14;
  param_1[2] = fVar2 * local_14;
  param_1[3] = 0.0;
  param_1[4] = local_10 * fVar1;
  param_1[5] = local_10 * fVar3 + 1.0;
  param_1[6] = fVar2 * local_10;
  param_1[7] = 0.0;
  param_1[8] = local_c * fVar1;
  param_1[9] = local_c * fVar3;
  param_1[10] = local_c * fVar2 + 1.0;
  param_1[0xb] = 0.0;
  param_1[0xc] = local_8 * fVar1;
  param_1[0xd] = local_8 * fVar3;
  param_1[0xe] = local_8 * fVar2;
  param_1[0xf] = 1.0;
  return;
}



/* FUN_004564e6 @ 004564e6 */

undefined4 __cdecl FUN_004564e6(DWORD param_1,LPCSTR param_2,LPBYTE param_3)

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



/* FUN_00456542 @ 00456542 */

/* WARNING: Removing unreachable block (ram,0x00456561) */
/* WARNING: Removing unreachable block (ram,0x00456553) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined8 __fastcall FUN_00456542(undefined4 param_1,undefined4 param_2)

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
  return CONCAT44(param_2,local_8);
}



/* Catch@004565b4 @ 004565b4 */

undefined * Catch_004565b4(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -0x3c) = *(undefined4 *)(unaff_EBP + -0x14);
  return &DAT_004565c6;
}



/* FUN_004565c0 @ 004565c0 */

/* WARNING: Removing unreachable block (ram,0x004565db) */

undefined4 FUN_004565c0(void)

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



/* cpu_features_get @ 004569d0 */

/* WARNING: Removing unreachable block (ram,0x00456a4d) */
/* WARNING: Removing unreachable block (ram,0x00456a3b) */
/* WARNING: Removing unreachable block (ram,0x00456a20) */
/* WARNING: Removing unreachable block (ram,0x00456a04) */
/* WARNING: Removing unreachable block (ram,0x004569f9) */
/* [binja] int32_t sub_4569d0() */

int cpu_features_get(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  int *piVar7;
  bool bVar8;
  char local_2c [16];
  int local_1c;
  int local_18;
  int local_14;
  char cStack_10;
  undefined4 local_c;
  uint local_8;
  
  cStack_10 = '\0';
  builtin_strncpy(local_2c,"AuthenticAMD",0xd);
  cpuid_basic_info(0);
  local_8 = 1;
  piVar7 = (int *)cpuid_basic_info(0);
  local_1c = piVar7[1];
  local_18 = piVar7[2];
  local_14 = piVar7[3];
  if (*piVar7 != 0) {
    puVar1 = (undefined4 *)cpuid_Version_info(1);
    local_c = *puVar1;
    uVar3 = -(uint)((puVar1[2] & 0x800000) != 0) & 0x20;
    local_8 = uVar3 | 3;
    puVar2 = (uint *)cpuid(0x80000000);
    if (0x80000000 < *puVar2) {
      iVar4 = cpuid(0x80000001);
      uVar5 = *(uint *)(iVar4 + 8);
      local_8 = uVar3 | 7 | -(uint)((uVar5 & 0x80000000) != 0) & 0x80;
      bVar8 = local_8 == 0;
      iVar4 = 0xc;
      pcVar6 = local_2c;
      piVar7 = &local_1c;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar8 = *pcVar6 == (char)*piVar7;
        pcVar6 = pcVar6 + 1;
        piVar7 = (int *)((int)piVar7 + 1);
      } while (bVar8);
      if (bVar8) {
        local_8 = local_8 | -(uint)((uVar5 & 0x40000000) != 0) & 0x100 |
                  -(uint)((uVar5 & 0x400000) != 0) & 0x200;
      }
    }
  }
  return local_8;
}



/* vec3_normalize @ 00456eec */

/* [binja] float* __stdcall sub_456eec(float* arg1, float* arg2) */

float * vec3_normalize(float *arg1,float *arg2)

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
    fVar3 = ((float)((uint)fVar1 & 0xffffff | 0x3f000000) * *(float *)(&DAT_00479780 + uVar4) +
            *(float *)(&DAT_00479784 + uVar4)) * (float)(0xbeffffffU - (int)fVar1 >> 1 & 0xff800000)
    ;
    fVar1 = arg2[1];
    fVar2 = arg2[2];
    *arg1 = *arg2 * fVar3;
    arg1[1] = fVar1 * fVar3;
    arg1[2] = fVar2 * fVar3;
  }
  return arg1;
}



/* mat4_multiply @ 00456fb6 */

/* [binja] int32_t __stdcall sub_456fb6(int32_t arg1, int32_t arg2, void* arg3) */

int mat4_multiply(int arg1,int arg2,void *arg3)

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



/* FUN_00457099 @ 00457099 */

/* [binja] void* __stdcall sub_457099(void* arg1, int32_t arg2, int32_t arg3) */

void * FUN_00457099(void *arg1,int arg2,int arg3)

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



/* FUN_00457127 @ 00457127 */

void __cdecl FUN_00457127(undefined4 *param_1)

{
  *param_1 = &LAB_00456ccb;
  param_1[1] = &LAB_00456d69;
  param_1[2] = &LAB_00456e53;
  param_1[3] = mat4_multiply;
  param_1[4] = FUN_00457099;
  param_1[5] = &LAB_00456d34;
  param_1[6] = &LAB_00456df4;
  param_1[7] = vec3_normalize;
  return;
}



/* mat4x4_transform_vec2 @ 00457170 */

float * mat4x4_transform_vec2(float *param_1,float *param_2,float *param_3)

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
  
  fVar3 = param_3[1];
  fVar4 = param_3[2];
  fVar5 = param_3[3];
  fVar1 = *param_2;
  fVar6 = param_3[5];
  fVar7 = param_3[6];
  fVar8 = param_3[7];
  fVar2 = param_2[1];
  fVar9 = param_3[0xd];
  fVar10 = param_3[0xe];
  fVar11 = param_3[0xf];
  *param_1 = fVar1 * *param_3 + param_3[0xc] + fVar2 * param_3[4];
  param_1[1] = fVar1 * fVar3 + fVar9 + fVar2 * fVar6;
  param_1[2] = fVar1 * fVar4 + fVar10 + fVar2 * fVar7;
  param_1[3] = fVar1 * fVar5 + fVar11 + fVar2 * fVar8;
  return param_1;
}



/* mat4x4_transform_vec2_proj @ 004571b0 */

undefined8 * mat4x4_transform_vec2_proj(undefined8 *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  undefined1 in_XMM0 [16];
  undefined1 auVar3 [16];
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar1 = *param_2;
  fVar2 = param_2[1];
  fVar4 = fVar1 * *param_3 + param_3[0xc] + fVar2 * param_3[4];
  fVar5 = fVar1 * param_3[1] + param_3[0xd] + fVar2 * param_3[5];
  fVar6 = fVar1 * param_3[3] + param_3[0xf] + fVar2 * param_3[7];
  auVar3._4_4_ = fVar5;
  auVar3._0_4_ = fVar4;
  auVar3._8_4_ = fVar1 * param_3[2] + param_3[0xe] + fVar2 * param_3[6];
  auVar3._12_4_ = fVar6;
  auVar3 = rcpps(in_XMM0,auVar3);
  fVar6 = auVar3._12_4_ * auVar3._12_4_ * fVar6;
  *param_1 = CONCAT44(fVar5 * fVar6,fVar4 * fVar6);
  return param_1;
}



/* vec3_slerp @ 00459b4b */

void vec3_slerp(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,uint param_4)

{
  undefined4 uVar1;
  uint extraout_MM0_Da;
  ulonglong extraout_MM0;
  undefined8 extraout_MM0_00;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  ulonglong uVar2;
  
  FastExitMediaState();
  uVar3 = PackedFloatingMUL(*param_2,*param_3);
  uVar5 = PackedFloatingMUL(param_2[1],param_3[1]);
  uVar3 = PackedFloatingADD(uVar3,uVar5);
  uVar2 = PackedFloatingSUB(0x3f800000,(ulonglong)param_4);
  uVar1 = (undefined4)uVar2;
  uVar4 = PackedFloatingAccumulate(uVar3,uVar3);
  uVar9 = PackedFloatingCompareGE(0,uVar4);
  uVar10 = uVar9 & 0x8000000080000000;
  uVar4 = uVar4 ^ uVar10;
  uVar5 = PackedFloatingCompareGE(0x3f7fff583f7fff58,uVar4);
  uVar3 = PackedFloatingMUL(uVar4,uVar4);
  uVar3 = PackedFloatingSUBR(uVar3,0x3f8000003f800000);
  if ((int)uVar5 != 0) {
    uVar7 = PackedFloatingReciprocalSQRAprox((ulonglong)param_4,uVar3);
    uVar5 = PackedFloatingMUL(uVar7,uVar7);
    uVar3 = PackedFloatingReciprocalSQRIter1(uVar3,uVar5);
    uVar4 = PackedFloatingReciprocalIter2(uVar3,uVar7);
    uVar3 = FloatingReciprocalAprox(uVar5,uVar4);
    uVar5 = PackedFloatingReciprocalIter1(uVar4,uVar3);
    PackedFloatingReciprocalIter2(uVar5,uVar3);
    math_atan2_packed();
    PackedFloatingMUL(extraout_MM0,(ulonglong)param_4);
    math_sin_packed();
    PackedFloatingMUL(extraout_MM0 & 0xffffffff,uVar2 & 0xffffffff);
    math_sin_packed();
    uVar10 = uVar9 & 0x80000000;
    uVar3 = PackedFloatingMUL(extraout_MM0_00,uVar4 & 0xffffffff);
    uVar1 = (undefined4)uVar3;
    uVar3 = PackedFloatingMUL((ulonglong)extraout_MM0_Da,uVar4 & 0xffffffff);
    param_4 = (uint)uVar3;
  }
  uVar6 = param_4 ^ (uint)uVar10;
  uVar5 = CONCAT44(uVar6,uVar6);
  uVar3 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),*param_2);
  uVar7 = PackedFloatingMUL(uVar5,*param_3);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),param_2[1]);
  uVar5 = PackedFloatingMUL(uVar5,param_3[1]);
  uVar3 = PackedFloatingADD(uVar3,uVar7);
  uVar5 = PackedFloatingADD(uVar8,uVar5);
  *param_1 = uVar3;
  param_1[1] = uVar5;
  FastExitMediaState();
  return;
}



/* mat4x4_identity_simd @ 0045b092 */

void __cdecl mat4x4_identity_simd(undefined8 *param_1)

{
  *param_1 = 0x3f800000;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0x3f800000;
  param_1[6] = 0;
  param_1[2] = 0x3f80000000000000;
  param_1[7] = 0x3f80000000000000;
  FastExitMediaState();
  return;
}



/* vec3_transform_coord @ 0045eac0 */

/* transforms a vec3 by a matrix and divides by W (perspective) */

float * vec3_transform_coord(float *out,float *vec,float *mat)

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
  uVar1 = (undefined4)*(undefined8 *)vec;
  uVar4 = CONCAT44(uVar1,uVar1);
  uVar1 = (undefined4)((ulonglong)*(undefined8 *)vec >> 0x20);
  uVar7 = CONCAT44(uVar1,uVar1);
  uVar8 = CONCAT44(vec[2],vec[2]);
  uVar2 = PackedFloatingMUL(uVar4,*(undefined8 *)mat);
  uVar3 = PackedFloatingMUL(uVar7,*(undefined8 *)(mat + 4));
  uVar5 = PackedFloatingMUL(uVar8,*(undefined8 *)(mat + 8));
  uVar2 = PackedFloatingADD(uVar2,*(undefined8 *)(mat + 0xc));
  uVar6 = PackedFloatingMUL(uVar4,*(undefined8 *)(mat + 2));
  uVar4 = PackedFloatingADD(uVar3,uVar5);
  uVar3 = PackedFloatingMUL(uVar7,*(undefined8 *)(mat + 6));
  uVar8 = PackedFloatingMUL(uVar8,*(undefined8 *)(mat + 10));
  uVar7 = PackedFloatingADD(uVar6,*(undefined8 *)(mat + 0xe));
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
  *(undefined8 *)out = uVar4;
  out[2] = (float)uVar2;
  FastExitMediaState();
  return out;
}



/* vec3_project @ 0045ed17 */

/* projects a vec3 through optional matrices and viewport scale/bias */

float * vec3_project(float *out,float *vec,float *viewport,float *world,float *view,float *proj)

{
  float *mat;
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar6;
  undefined8 uVar5;
  float local_44 [16];
  
  mat = local_44;
  switch(((proj != (float *)0x0) << 1 | view != (float *)0x0) << 1 | world != (float *)0x0) {
  case '\0':
    local_44[0xe] = 0.0;
    local_44[0xd] = 0.0;
    local_44[0xc] = 0.0;
    local_44[0xb] = 0.0;
    local_44[9] = 0.0;
    local_44[8] = 0.0;
    local_44[7] = 0.0;
    local_44[6] = 0.0;
    local_44[4] = 0.0;
    local_44[3] = 0.0;
    local_44[2] = 0.0;
    local_44[1] = 0.0;
    local_44[0xf] = 1.0;
    local_44[10] = 1.0;
    local_44[5] = 1.0;
    local_44[0] = 1.0;
    break;
  case '\x01':
    mat = world;
    break;
  case '\x02':
    mat = view;
    break;
  case '\x03':
    FastExitMediaState();
    mat4_mul(local_44,view,world);
    FastExitMediaState();
    break;
  case '\x04':
    mat = proj;
    break;
  case '\x05':
    FastExitMediaState();
    mat4_mul(local_44,proj,world);
    FastExitMediaState();
    break;
  case '\x06':
    FastExitMediaState();
    mat4_mul(local_44,proj,view);
    FastExitMediaState();
    break;
  case '\a':
    FastExitMediaState();
    mat4_mul(local_44,proj,view);
    mat4_mul(local_44,local_44,world);
    FastExitMediaState();
  }
  vec3_transform_coord(out,vec,mat);
  if (viewport != (float *)0x0) {
    FastExitMediaState();
    uVar2 = *(undefined8 *)(viewport + 4);
    uVar3 = PackedIntToFloatingDwordConv(*(undefined8 *)viewport,*(undefined8 *)viewport);
    uVar4 = PackedIntToFloatingDwordConv
                      (*(undefined8 *)(viewport + 2),*(undefined8 *)(viewport + 2));
    uVar1 = PackedFloatingADD(*(ulonglong *)out ^ 0x8000000000000000,0x3f8000003f800000);
    uVar4 = PackedFloatingMUL(uVar4,0x3f0000003f000000);
    uVar6 = (undefined4)((ulonglong)uVar2 >> 0x20);
    uVar5 = PackedFloatingSUB(CONCAT44(uVar6,uVar6),uVar2);
    uVar1 = PackedFloatingMUL(uVar1,uVar4);
    uVar4 = PackedFloatingMUL((ulonglong)(uint)out[2],uVar5);
    uVar4 = PackedFloatingADD(uVar4,uVar2);
    uVar2 = PackedFloatingADD(uVar1,uVar3);
    *(undefined8 *)out = uVar2;
    out[2] = (float)uVar4;
    FastExitMediaState();
  }
  return out;
}



/* vec3_unproject @ 0045ee9f */

/* unprojects a screen-space vec3 using inverse matrices and viewport */

float * vec3_unproject(float *out,float *vec,float *viewport,float *world,float *view,float *proj)

{
  undefined8 uVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined4 uVar7;
  undefined8 uVar6;
  undefined8 uVar8;
  unkbyte10 in_ST5;
  undefined8 uVar9;
  unkbyte10 in_ST6;
  float local_44 [16];
  
  uVar2 = (undefined8)in_ST5;
  uVar9 = (undefined8)in_ST6;
  switch(((proj != (float *)0x0) << 1 | view != (float *)0x0) << 1 | world != (float *)0x0) {
  case '\0':
    local_44[0xe] = 0.0;
    local_44[0xd] = 0.0;
    local_44[0xc] = 0.0;
    local_44[0xb] = 0.0;
    local_44[9] = 0.0;
    local_44[8] = 0.0;
    local_44[7] = 0.0;
    local_44[6] = 0.0;
    local_44[4] = 0.0;
    local_44[3] = 0.0;
    local_44[2] = 0.0;
    local_44[1] = 0.0;
    local_44[0xf] = 1.0;
    local_44[10] = 1.0;
    local_44[5] = 1.0;
    local_44[0] = 1.0;
    break;
  case '\x01':
    FastExitMediaState();
    mat4_invert(local_44,(float *)0x0,world);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\x02':
    FastExitMediaState();
    mat4_invert(local_44,(float *)0x0,view);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\x03':
    FastExitMediaState();
    mat4_mul(local_44,view,world);
    mat4_invert(local_44,(float *)0x0,local_44);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\x04':
    FastExitMediaState();
    mat4_invert(local_44,(float *)0x0,proj);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\x05':
    FastExitMediaState();
    mat4_mul(local_44,proj,world);
    mat4_invert(local_44,(float *)0x0,local_44);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\x06':
    FastExitMediaState();
    mat4_mul(local_44,proj,view);
    mat4_invert(local_44,(float *)0x0,local_44);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
    break;
  case '\a':
    FastExitMediaState();
    mat4_mul(local_44,proj,view);
    mat4_mul(local_44,local_44,world);
    mat4_invert(local_44,(float *)0x0,local_44);
    uVar2 = (undefined8)in_ST5;
    uVar9 = (undefined8)in_ST6;
    FastExitMediaState();
  }
  if (viewport != (float *)0x0) {
    FastExitMediaState();
    uVar4 = PackedIntToFloatingDwordConv(*(undefined8 *)viewport,*(undefined8 *)viewport);
    uVar1 = *(undefined8 *)(viewport + 4);
    uVar5 = PackedIntToFloatingDwordConv
                      (*(undefined8 *)(viewport + 2),*(undefined8 *)(viewport + 2));
    uVar7 = (undefined4)((ulonglong)uVar5 >> 0x20);
    uVar6 = CONCAT44(uVar7,uVar7);
    uVar8 = FloatingReciprocalAprox(uVar2,uVar5);
    uVar6 = FloatingReciprocalAprox(uVar6,uVar6);
    uVar2 = PackedFloatingSUB(*(undefined8 *)vec,uVar4);
    uVar6 = CONCAT44((int)uVar6,(int)uVar8);
    uVar4 = PackedFloatingReciprocalIter1(uVar5,uVar6);
    uVar4 = PackedFloatingReciprocalIter2(uVar4,uVar6);
    uVar4 = PackedFloatingMUL(uVar4,0x4000000040000000);
    uVar2 = PackedFloatingMUL(uVar2,uVar4);
    uVar7 = (undefined4)((ulonglong)uVar1 >> 0x20);
    uVar3 = PackedFloatingSUB(uVar2,0x3f8000003f800000);
    uVar2 = PackedFloatingSUB(CONCAT44(uVar7,uVar7),uVar1);
    uVar9 = FloatingReciprocalAprox(uVar9,uVar2);
    uVar2 = PackedFloatingReciprocalIter1(uVar2,uVar9);
    uVar9 = PackedFloatingReciprocalIter2(uVar2,uVar9);
    uVar2 = PackedFloatingSUB((ulonglong)(uint)vec[2],uVar1);
    uVar2 = PackedFloatingMUL(uVar2,uVar9);
    *(ulonglong *)out = uVar3 ^ 0x8000000000000000;
    out[2] = (float)uVar2;
    FastExitMediaState();
    vec = out;
  }
  vec3_transform_coord(out,vec,local_44);
  return out;
}



/* vec2_normalize_simd @ 0045fae8 */

void vec2_normalize_simd(undefined8 *param_1,ulonglong *param_2)

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


