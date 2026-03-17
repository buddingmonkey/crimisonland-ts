/* cpu_detect_intel @ 0045657a */

/* WARNING: Removing unreachable block (ram,0x004565a4) */

void cpu_detect_intel(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int unaff_EBP;
  
  FUN_004636c8();
  *(undefined1 **)(unaff_EBP + -0x10) = &stack0xffffffc4;
  *(undefined4 *)(unaff_EBP + -0x14) = 0;
  builtin_strncpy((char *)(unaff_EBP + -0x24),"Genu",4);
  builtin_strncpy((char *)(unaff_EBP + -0x20),"ineI",4);
  builtin_strncpy((char *)(unaff_EBP + -0x1c),"ntel",4);
  *(char *)(unaff_EBP + -0x18) = '\0';
  *(undefined4 *)(unaff_EBP + -4) = 0;
  puVar1 = (undefined4 *)cpuid_basic_info(0);
  uVar4 = puVar1[1];
  uVar3 = puVar1[2];
  uVar2 = puVar1[3];
  *(undefined4 *)(unaff_EBP + -0x2c) = *puVar1;
  *(undefined4 *)(unaff_EBP + -0x38) = uVar4;
  *(undefined4 *)(unaff_EBP + -0x34) = uVar3;
  *(undefined4 *)(unaff_EBP + -0x30) = uVar2;
  FUN_004565c0();
  return;
}



/* FUN_00459536 @ 00459536 */

ulonglong FUN_00459536(undefined8 *param_1,undefined8 *param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  int iVar2;
  undefined8 extraout_MM0;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  
  uVar4 = *param_1;
  uVar1 = param_1[1];
  uVar5 = PackedFloatingMUL(uVar4,uVar4);
  uVar3 = PackedFloatingMUL(uVar1,uVar1);
  uVar5 = PackedFloatingADD(uVar5,uVar3);
  uVar5 = PackedFloatingAccumulate(uVar5,uVar5);
  uVar6 = PackedFloatingCompareGE(0x80000000800000,uVar5);
  uVar3 = PackedFloatingReciprocalSQRAprox(uVar3,uVar5);
  iVar2 = (int)uVar6;
  if (iVar2 == 0) {
    uVar6 = PackedFloatingMUL(uVar3,uVar3);
    if (param_2 != (undefined8 *)0x0) {
      uVar5 = PackedFloatingReciprocalSQRIter1(uVar6,uVar5);
      uVar3 = PackedFloatingReciprocalIter2(uVar5,uVar3);
      uVar5 = PackedFloatingMUL(uVar4,uVar3);
      uVar4 = PackedFloatingMUL(uVar3,uVar1);
      *param_2 = uVar5;
      *(int *)(param_2 + 1) = (int)uVar4;
    }
    uVar7 = CONCAT44(param_2,iVar2);
    if (param_3 != (undefined4 *)0x0) {
      uVar7 = math_acos_packed();
      uVar4 = PackedFloatingMUL(extraout_MM0,0x4000000040000000);
      *param_3 = (int)uVar4;
    }
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      *(undefined8 *)((int)param_2 + 4) = 0;
      *(undefined4 *)param_2 = 0x3f800000;
    }
    uVar7 = CONCAT44(param_2,iVar2);
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
      uVar7 = CONCAT44(param_2,iVar2);
    }
  }
  FastExitMediaState();
  return uVar7;
}



/* FUN_00459adf @ 00459adf */

void FUN_00459adf(undefined8 *param_1,ulonglong *param_2,uint param_3)

{
  undefined8 extraout_MM0;
  undefined8 uVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined8 local_18;
  uint local_10;
  
  FastExitMediaState();
  quat_normalize_simd(&local_18,param_2);
  PackedFloatingMUL((ulonglong)param_3,0x3f0000003f000000);
  math_sincos_packed();
  uVar3 = (undefined4)((ulonglong)extraout_MM0 >> 0x20);
  uVar2 = CONCAT44(uVar3,uVar3);
  uVar1 = PackedFloatingMUL(local_18,uVar2);
  uVar2 = PackedFloatingMUL((ulonglong)local_10,uVar2);
  *param_1 = uVar1;
  param_1[1] = CONCAT44((int)extraout_MM0,(int)uVar2);
  FastExitMediaState();
  return;
}



/* FUN_00459c82 @ 00459c82 */

undefined8 *
FUN_00459c82(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
            uint param_5,uint param_6)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 in_MM2;
  undefined8 uVar3;
  undefined8 local_28 [2];
  undefined8 local_18 [2];
  
  FastExitMediaState();
  uVar1 = PackedFloatingADD((ulonglong)param_5,(ulonglong)param_6);
  vec3_slerp(local_28,param_2,param_3,(uint)uVar1);
  vec3_slerp(local_18,param_2,param_4,(uint)uVar1);
  uVar3 = FloatingReciprocalAprox(in_MM2,uVar1 & 0xffffffff);
  uVar2 = PackedFloatingReciprocalIter1(uVar1 & 0xffffffff,uVar3);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar3);
  uVar2 = PackedFloatingMUL(uVar2,(ulonglong)param_6);
  vec3_slerp(param_1,local_28,local_18,(uint)uVar2);
  FastExitMediaState();
  return param_1;
}



/* FUN_00459d0f @ 00459d0f */

void FUN_00459d0f(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
                 undefined8 *param_5,uint param_6)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 local_20 [2];
  undefined8 local_10 [2];
  
  vec3_slerp(local_20,param_2,param_5,param_6);
  vec3_slerp(local_10,param_3,param_4,param_6);
  uVar1 = (ulonglong)param_6;
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar2 = PackedFloatingSUB(uVar1,uVar2);
  uVar2 = PackedFloatingMUL(uVar2,0x4000000040000000);
  vec3_slerp(param_1,local_20,local_10,(uint)uVar2);
  FastExitMediaState();
  return;
}



/* FUN_00459e05 @ 00459e05 */

void FUN_00459e05(undefined8 *param_1,undefined8 *param_2)

{
  undefined4 extraout_MM0_Da;
  ulonglong extraout_MM0;
  undefined8 uVar1;
  ulonglong uVar2;
  undefined4 uVar4;
  undefined8 uVar3;
  undefined8 in_MM4;
  undefined8 uVar5;
  
  FastExitMediaState();
  uVar1 = *param_2;
  uVar2 = param_2[1];
  uVar4 = (undefined4)(uVar2 >> 0x20);
  uVar3 = PackedFloatingCompareGE(CONCAT44(uVar4,uVar4),0x3f8000003f800000);
  if ((int)uVar3 == 0) {
    math_acos_packed();
    math_sin_packed();
    uVar3 = PackedFloatingCompareGE(extraout_MM0 & 0x7fffffff7fffffff,0x3400000034000000);
    uVar1 = *param_2;
    uVar2 = param_2[1];
    if ((int)uVar3 != 0) {
      uVar5 = FloatingReciprocalAprox(in_MM4,extraout_MM0);
      uVar3 = PackedFloatingReciprocalIter1(extraout_MM0,uVar5);
      uVar3 = PackedFloatingReciprocalIter2(uVar3,uVar5);
      uVar3 = PackedFloatingMUL(CONCAT44(extraout_MM0_Da,extraout_MM0_Da),uVar3);
      uVar1 = PackedFloatingMUL(uVar1,uVar3);
      uVar2 = PackedFloatingMUL(uVar2,uVar3);
    }
  }
  *param_1 = uVar1;
  param_1[1] = uVar2 & 0xffffffff;
  FastExitMediaState();
  return;
}



/* FUN_00459f51 @ 00459f51 */

void FUN_00459f51(undefined8 *param_1,undefined8 *param_2,ulonglong *param_3,ulonglong *param_4,
                 ulonglong *param_5,ulonglong *param_6,ulonglong *param_7)

{
  undefined4 unaff_ESI;
  undefined4 extraout_MM0_Da;
  undefined4 extraout_MM0_Da_00;
  undefined4 extraout_MM0_Da_01;
  undefined4 extraout_MM0_Da_02;
  undefined8 uVar1;
  ulonglong extraout_MM0;
  ulonglong extraout_MM0_00;
  ulonglong extraout_MM0_01;
  ulonglong extraout_MM0_02;
  ulonglong extraout_MM0_03;
  ulonglong extraout_MM0_04;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  undefined8 uVar14;
  ulonglong local_a8;
  ulonglong local_a0;
  ulonglong local_88;
  ulonglong local_80;
  ulonglong local_78;
  ulonglong local_70;
  undefined4 local_20;
  
  local_a8 = *param_4;
  local_a0 = param_4[1];
  uVar6 = *param_5;
  uVar13 = param_5[1];
  uVar1 = PackedFloatingADD(local_a8,uVar6);
  uVar2 = PackedFloatingADD(local_a0,uVar13);
  uVar4 = PackedFloatingSUB(local_a8,uVar6);
  uVar1 = PackedFloatingMUL(uVar1,uVar1);
  uVar7 = PackedFloatingSUB(local_a0,uVar13);
  uVar2 = PackedFloatingMUL(uVar2,uVar2);
  uVar4 = PackedFloatingMUL(uVar4,uVar4);
  uVar7 = PackedFloatingMUL(uVar7,uVar7);
  uVar1 = PackedFloatingADD(uVar1,uVar2);
  uVar4 = PackedFloatingADD(uVar4,uVar7);
  local_88 = *param_6;
  local_80 = param_6[1];
  uVar9 = PackedFloatingADD(uVar6,local_88);
  uVar11 = PackedFloatingADD(uVar13,local_80);
  uVar2 = PackedFloatingSUB(uVar6,local_88);
  uVar7 = PackedFloatingSUB(uVar13,local_80);
  uVar9 = PackedFloatingMUL(uVar9,uVar9);
  uVar11 = PackedFloatingMUL(uVar11,uVar11);
  uVar2 = PackedFloatingMUL(uVar2,uVar2);
  uVar7 = PackedFloatingMUL(uVar7,uVar7);
  uVar9 = PackedFloatingADD(uVar9,uVar11);
  uVar2 = PackedFloatingADD(uVar2,uVar7);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar9);
  uVar2 = PackedFloatingAccumulate(uVar4,uVar2);
  uVar1 = PackedFloatingCompareGT(uVar2,uVar1);
  uVar5 = packsswb(uVar1,uVar1);
  if ((uVar5 & 1) != 0) {
    local_a8 = *param_4 ^ 0x8000000080000000;
    local_a0 = param_4[1] ^ 0x8000000080000000;
  }
  if ((uVar5 & 0x10000) != 0) {
    local_88 = *param_6 ^ 0x8000000080000000;
    local_80 = param_6[1] ^ 0x8000000080000000;
  }
  local_78 = *param_7;
  uVar5 = param_7[1];
  uVar4 = PackedFloatingADD(local_88,local_78);
  uVar7 = PackedFloatingADD(local_80,uVar5);
  uVar1 = PackedFloatingSUB(local_88,local_78);
  uVar2 = PackedFloatingSUB(local_80,uVar5);
  uVar4 = PackedFloatingMUL(uVar4,uVar4);
  uVar7 = PackedFloatingMUL(uVar7,uVar7);
  uVar1 = PackedFloatingMUL(uVar1,uVar1);
  uVar2 = PackedFloatingMUL(uVar2,uVar2);
  uVar4 = PackedFloatingADD(uVar4,uVar7);
  uVar1 = PackedFloatingADD(uVar1,uVar2);
  uVar2 = PackedFloatingAccumulate(uVar4,uVar4);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar8 = PackedFloatingCompareGT(uVar1,uVar2);
  local_70 = uVar5;
  if ((uVar8 & 1) != 0) {
    local_78 = *param_7 ^ 0x8000000080000000;
    local_70 = param_7[1] ^ 0x8000000080000000;
  }
  uVar1 = PackedFloatingMUL(uVar6,uVar6);
  uVar2 = PackedFloatingMUL(uVar13,uVar13);
  uVar1 = PackedFloatingADD(uVar1,uVar2);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar2 = FloatingReciprocalAprox(uVar5,uVar1);
  uVar5 = PackedFloatingCompareGT(uVar1,0x80000000800000);
  uVar1 = PackedFloatingReciprocalIter1(uVar1,uVar2);
  uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar2);
  uVar2 = PackedFloatingMUL((uVar6 ^ 0x8000000080000000) & uVar5,uVar1);
  uVar9 = PackedFloatingMUL((uVar13 ^ 0x80000000) & uVar5,uVar1);
  uVar8 = CONCAT44((int)local_a8,(int)(local_a8 >> 0x20));
  uVar10 = CONCAT44((int)local_a0,(int)(local_a0 >> 0x20));
  uVar5 = PackedFloatingMUL(local_a8,uVar9);
  uVar1 = PackedFloatingMUL(local_a0,uVar2);
  uVar7 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar2);
  uVar4 = PackedFloatingMUL(uVar8,uVar9);
  uVar1 = PackedFloatingADD(uVar5 ^ 0x80000000,uVar1);
  uVar4 = PackedFloatingSUB(uVar4,uVar7);
  uVar14 = PackedFloatingMUL(uVar10,uVar9);
  uVar4 = PackedFloatingAccumulate(uVar4,uVar1);
  uVar11 = PackedFloatingMUL(uVar8 ^ 0x80000000,uVar2);
  uVar1 = PackedFloatingMUL(local_a8,uVar2);
  uVar7 = PackedFloatingMUL(local_a0 ^ 0x80000000,uVar9);
  uVar11 = PackedFloatingADD(uVar11,uVar14);
  uVar1 = PackedFloatingSUB(uVar7,uVar1);
  uVar8 = PackedFloatingAccumulate(uVar11,uVar1);
  uVar10 = CONCAT44((int)local_88,(int)(local_88 >> 0x20));
  uVar12 = CONCAT44((int)local_80,(int)(local_80 >> 0x20));
  uVar5 = PackedFloatingMUL(local_88,uVar9);
  uVar1 = PackedFloatingMUL(local_80,uVar2);
  uVar11 = PackedFloatingMUL(uVar12 ^ 0x80000000,uVar2);
  uVar7 = PackedFloatingMUL(uVar10,uVar9);
  uVar1 = PackedFloatingADD(uVar5 ^ 0x80000000,uVar1);
  uVar7 = PackedFloatingSUB(uVar7,uVar11);
  uVar14 = PackedFloatingMUL(uVar12,uVar9);
  uVar7 = PackedFloatingAccumulate(uVar7,uVar1);
  uVar11 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar2);
  uVar1 = PackedFloatingMUL(local_88,uVar2);
  uVar2 = PackedFloatingMUL(local_80 ^ 0x80000000,uVar9);
  uVar9 = PackedFloatingADD(uVar11,uVar14);
  uVar1 = PackedFloatingSUB(uVar2,uVar1);
  uVar5 = PackedFloatingAccumulate(uVar9,uVar1);
  uVar3 = (undefined4)(uVar8 >> 0x20);
  uVar2 = PackedFloatingCompareGE(CONCAT44(uVar3,uVar3),0x3f8000003f800000);
  uVar1 = uVar7;
  if ((int)uVar2 == 0) {
    math_acos_packed();
    math_sin_packed();
    uVar2 = PackedFloatingCompareGE(extraout_MM0 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar2 != 0) {
      uVar1 = FloatingReciprocalAprox(uVar1,extraout_MM0);
      uVar2 = PackedFloatingReciprocalIter1(extraout_MM0,uVar1);
      uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar1);
      uVar2 = PackedFloatingMUL(CONCAT44(extraout_MM0_Da,extraout_MM0_Da),uVar2);
      uVar4 = PackedFloatingMUL(uVar4,uVar2);
      uVar8 = PackedFloatingMUL(uVar8,uVar2);
    }
  }
  uVar3 = (undefined4)(uVar5 >> 0x20);
  uVar2 = PackedFloatingCompareGE(CONCAT44(uVar3,uVar3),0x3f8000003f800000);
  if ((int)uVar2 == 0) {
    math_acos_packed();
    math_sin_packed();
    uVar2 = PackedFloatingCompareGE(extraout_MM0_00 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar2 != 0) {
      uVar2 = FloatingReciprocalAprox(uVar1,extraout_MM0_00);
      uVar1 = PackedFloatingReciprocalIter1(extraout_MM0_00,uVar2);
      uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar2);
      uVar1 = PackedFloatingMUL(CONCAT44(extraout_MM0_Da_00,extraout_MM0_Da_00),uVar1);
      uVar7 = PackedFloatingMUL(uVar7,uVar1);
      uVar5 = PackedFloatingMUL(uVar5,uVar1);
    }
  }
  uVar1 = PackedFloatingADD(uVar4,uVar7);
  uVar2 = PackedFloatingADD(uVar8 & 0xffffffff,uVar5 & 0xffffffff);
  uVar1 = PackedFloatingMUL(uVar1,0xbe800000be800000);
  uVar8 = PackedFloatingMUL(uVar2,0xbe800000be800000);
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar8 & 0xffffffff,uVar8 & 0xffffffff);
  uVar2 = PackedFloatingADD(uVar2,uVar4);
  uVar2 = PackedFloatingAccumulate(uVar2,uVar2);
  uVar4 = PackedFloatingReciprocalSQRAprox(uVar4,uVar2);
  uVar7 = PackedFloatingMUL(uVar4,uVar4);
  uVar7 = PackedFloatingReciprocalSQRIter1(uVar7,uVar2);
  uVar4 = PackedFloatingReciprocalIter2(uVar7,uVar4);
  PackedFloatingMUL(uVar2,uVar4);
  math_sincos_packed();
  uVar5 = PackedFloatingCompareGE(extraout_MM0_01 & 0x7fffffffffffffff,0x3400000034000000);
  uVar3 = (undefined4)(extraout_MM0_01 >> 0x20);
  uVar2 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),CONCAT44(unaff_ESI,(int)uVar4));
  local_20 = (undefined4)uVar8;
  if ((uVar5 & 0x100000000) != 0) {
    uVar2 = CONCAT44((int)uVar2,(int)uVar2);
    uVar4 = PackedFloatingMUL(uVar8 & 0xffffffff,uVar2);
    local_20 = (undefined4)uVar4;
    uVar1 = PackedFloatingMUL(uVar1,uVar2);
  }
  uVar8 = CONCAT44((int)extraout_MM0_01,local_20);
  uVar10 = CONCAT44((int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
  uVar12 = CONCAT44(local_20,(int)extraout_MM0_01);
  uVar5 = PackedFloatingMUL(uVar1,uVar13);
  uVar2 = PackedFloatingMUL(uVar8,uVar6);
  uVar7 = PackedFloatingMUL(uVar12 ^ 0x80000000,uVar6);
  uVar4 = PackedFloatingMUL(uVar10,uVar13);
  uVar2 = PackedFloatingADD(uVar5 ^ 0x80000000,uVar2);
  uVar4 = PackedFloatingSUB(uVar4,uVar7);
  uVar9 = PackedFloatingMUL(uVar12,uVar13);
  uVar4 = PackedFloatingAccumulate(uVar4,uVar2);
  uVar7 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar6);
  uVar1 = PackedFloatingMUL(uVar1,uVar6);
  *param_1 = uVar4;
  uVar2 = PackedFloatingMUL(uVar8 ^ 0x80000000,uVar13);
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar1 = PackedFloatingSUB(uVar2,uVar1);
  uVar1 = PackedFloatingAccumulate(uVar7,uVar1);
  param_1[1] = uVar1;
  uVar1 = PackedFloatingMUL(local_88,local_88);
  uVar2 = PackedFloatingMUL(local_80,local_80);
  uVar1 = PackedFloatingADD(uVar1,uVar2);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar2 = FloatingReciprocalAprox(uVar4,uVar1);
  uVar5 = PackedFloatingCompareGT(uVar1,0x80000000800000);
  uVar1 = PackedFloatingReciprocalIter1(uVar1,uVar2);
  uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar2);
  uVar2 = PackedFloatingMUL((local_88 ^ 0x8000000080000000) & uVar5,uVar1);
  uVar9 = PackedFloatingMUL((local_80 ^ 0x80000000) & uVar5,uVar1);
  uVar8 = CONCAT44((int)uVar6,(int)(uVar6 >> 0x20));
  uVar10 = CONCAT44((int)uVar13,(int)(uVar13 >> 0x20));
  uVar5 = PackedFloatingMUL(uVar6,uVar9);
  uVar1 = PackedFloatingMUL(uVar13,uVar2);
  uVar7 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar2);
  uVar4 = PackedFloatingMUL(uVar8,uVar9);
  uVar1 = PackedFloatingADD(uVar5 ^ 0x80000000,uVar1);
  uVar4 = PackedFloatingSUB(uVar4,uVar7);
  uVar14 = PackedFloatingMUL(uVar10,uVar9);
  uVar4 = PackedFloatingAccumulate(uVar4,uVar1);
  uVar11 = PackedFloatingMUL(uVar8 ^ 0x80000000,uVar2);
  uVar1 = PackedFloatingMUL(uVar6,uVar2);
  uVar7 = PackedFloatingMUL(uVar13 ^ 0x80000000,uVar9);
  uVar11 = PackedFloatingADD(uVar11,uVar14);
  uVar1 = PackedFloatingSUB(uVar7,uVar1);
  uVar13 = PackedFloatingAccumulate(uVar11,uVar1);
  uVar5 = CONCAT44((int)local_78,(int)(local_78 >> 0x20));
  uVar8 = CONCAT44((int)local_70,(int)(local_70 >> 0x20));
  uVar6 = PackedFloatingMUL(local_78,uVar9);
  uVar1 = PackedFloatingMUL(local_70,uVar2);
  uVar11 = PackedFloatingMUL(uVar8 ^ 0x80000000,uVar2);
  uVar7 = PackedFloatingMUL(uVar5,uVar9);
  uVar1 = PackedFloatingADD(uVar6 ^ 0x80000000,uVar1);
  uVar7 = PackedFloatingSUB(uVar7,uVar11);
  uVar14 = PackedFloatingMUL(uVar8,uVar9);
  uVar7 = PackedFloatingAccumulate(uVar7,uVar1);
  uVar11 = PackedFloatingMUL(uVar5 ^ 0x80000000,uVar2);
  uVar1 = PackedFloatingMUL(local_78,uVar2);
  uVar2 = PackedFloatingMUL(local_70 ^ 0x80000000,uVar9);
  uVar9 = PackedFloatingADD(uVar11,uVar14);
  uVar1 = PackedFloatingSUB(uVar2,uVar1);
  uVar6 = PackedFloatingAccumulate(uVar9,uVar1);
  uVar3 = (undefined4)(uVar13 >> 0x20);
  uVar2 = PackedFloatingCompareGE(CONCAT44(uVar3,uVar3),0x3f8000003f800000);
  uVar1 = uVar7;
  if ((int)uVar2 == 0) {
    math_acos_packed();
    math_sin_packed();
    uVar2 = PackedFloatingCompareGE(extraout_MM0_02 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar2 != 0) {
      uVar1 = FloatingReciprocalAprox(uVar1,extraout_MM0_02);
      uVar2 = PackedFloatingReciprocalIter1(extraout_MM0_02,uVar1);
      uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar1);
      uVar2 = PackedFloatingMUL(CONCAT44(extraout_MM0_Da_01,extraout_MM0_Da_01),uVar2);
      uVar4 = PackedFloatingMUL(uVar4,uVar2);
      uVar13 = PackedFloatingMUL(uVar13,uVar2);
    }
  }
  uVar3 = (undefined4)(uVar6 >> 0x20);
  uVar2 = PackedFloatingCompareGE(CONCAT44(uVar3,uVar3),0x3f8000003f800000);
  if ((int)uVar2 == 0) {
    math_acos_packed();
    math_sin_packed();
    uVar2 = PackedFloatingCompareGE(extraout_MM0_03 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar2 != 0) {
      uVar2 = FloatingReciprocalAprox(uVar1,extraout_MM0_03);
      uVar1 = PackedFloatingReciprocalIter1(extraout_MM0_03,uVar2);
      uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar2);
      uVar1 = PackedFloatingMUL(CONCAT44(extraout_MM0_Da_02,extraout_MM0_Da_02),uVar1);
      uVar7 = PackedFloatingMUL(uVar7,uVar1);
      uVar6 = PackedFloatingMUL(uVar6,uVar1);
    }
  }
  uVar1 = PackedFloatingADD(uVar4,uVar7);
  uVar2 = PackedFloatingADD(uVar13 & 0xffffffff,uVar6 & 0xffffffff);
  uVar1 = PackedFloatingMUL(uVar1,0xbe800000be800000);
  uVar13 = PackedFloatingMUL(uVar2,0xbe800000be800000);
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar13 & 0xffffffff,uVar13 & 0xffffffff);
  uVar2 = PackedFloatingADD(uVar2,uVar4);
  uVar2 = PackedFloatingAccumulate(uVar2,uVar2);
  uVar4 = PackedFloatingReciprocalSQRAprox(uVar4,uVar2);
  uVar7 = PackedFloatingMUL(uVar4,uVar4);
  uVar7 = PackedFloatingReciprocalSQRIter1(uVar7,uVar2);
  uVar4 = PackedFloatingReciprocalIter2(uVar7,uVar4);
  PackedFloatingMUL(uVar2,uVar4);
  math_sincos_packed();
  uVar6 = PackedFloatingCompareGE(extraout_MM0_04 & 0x7fffffffffffffff,0x3400000034000000);
  uVar3 = (undefined4)(extraout_MM0_04 >> 0x20);
  uVar2 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),CONCAT44(unaff_ESI,(int)uVar4));
  local_20 = (undefined4)uVar13;
  if ((uVar6 & 0x100000000) != 0) {
    uVar2 = CONCAT44((int)uVar2,(int)uVar2);
    uVar4 = PackedFloatingMUL(uVar13 & 0xffffffff,uVar2);
    local_20 = (undefined4)uVar4;
    uVar1 = PackedFloatingMUL(uVar1,uVar2);
  }
  uVar13 = CONCAT44((int)extraout_MM0_04,local_20);
  uVar5 = CONCAT44((int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
  uVar8 = CONCAT44(local_20,(int)extraout_MM0_04);
  uVar6 = PackedFloatingMUL(uVar1,local_80);
  uVar2 = PackedFloatingMUL(uVar13,local_88);
  uVar7 = PackedFloatingMUL(uVar8 ^ 0x80000000,local_88);
  uVar4 = PackedFloatingMUL(uVar5,local_80);
  uVar2 = PackedFloatingADD(uVar6 ^ 0x80000000,uVar2);
  uVar4 = PackedFloatingSUB(uVar4,uVar7);
  uVar7 = PackedFloatingMUL(uVar8,local_80);
  uVar2 = PackedFloatingAccumulate(uVar4,uVar2);
  uVar4 = PackedFloatingMUL(uVar5 ^ 0x80000000,local_88);
  uVar1 = PackedFloatingMUL(uVar1,local_88);
  *param_2 = uVar2;
  uVar2 = PackedFloatingMUL(uVar13 ^ 0x80000000,local_80);
  uVar4 = PackedFloatingADD(uVar4,uVar7);
  uVar1 = PackedFloatingSUB(uVar2,uVar1);
  uVar1 = PackedFloatingAccumulate(uVar4,uVar1);
  param_2[1] = uVar1;
  *param_3 = local_88;
  param_3[1] = local_80;
  FastExitMediaState();
  return;
}



/* FUN_0045b252 @ 0045b252 */

void FUN_0045b252(ulonglong *param_1,undefined8 *param_2,undefined8 *param_3,ulonglong *param_4,
                 undefined8 *param_5,undefined8 *param_6,undefined8 *param_7)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar7;
  ulonglong uVar5;
  ulonglong uVar6;
  undefined8 uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  undefined4 uVar16;
  ulonglong uVar14;
  undefined8 uVar15;
  ulonglong uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  uint uVar24;
  undefined8 uVar22;
  undefined8 uVar23;
  undefined4 uVar25;
  undefined8 uVar26;
  undefined4 uVar29;
  ulonglong uVar27;
  ulonglong uVar28;
  
  if (param_4 == (ulonglong *)0x0) {
    *param_1 = 0x3f800000;
    param_1[1] = 0;
    param_1[2] = 0x3f80000000000000;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0x3f800000;
    param_1[6] = 0;
    param_1[7] = 0x3f80000000000000;
  }
  else if (param_3 == (undefined8 *)0x0) {
    uVar12 = *param_4;
    uVar11 = param_4[1];
    *param_1 = uVar12 & 0xffffffff;
    param_1[1] = 0;
    param_1[2] = uVar12 & 0xffffffff00000000;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = (ulonglong)(uint)uVar11;
    param_1[6] = 0;
    param_1[7] = 0x3f80000000000000;
  }
  else {
    uVar13 = (ulonglong)(uint)param_4[1];
    uVar27 = *param_4 & 0xffffffff;
    uVar17 = *param_4 & 0xffffffff00000000;
    uVar21 = *param_3;
    uVar4 = param_3[1];
    uVar2 = PackedFloatingADD(uVar21,uVar21);
    uVar3 = PackedFloatingADD(uVar4,uVar4);
    uVar7 = (undefined4)((ulonglong)uVar21 >> 0x20);
    uVar16 = (undefined4)((ulonglong)uVar4 >> 0x20);
    uVar26 = CONCAT44(uVar16,uVar16);
    uVar8 = PackedFloatingMUL(uVar21,uVar2);
    uVar21 = CONCAT44((int)uVar2,(int)uVar3);
    uVar18 = PackedFloatingMUL(uVar2,uVar26);
    uVar3 = PackedFloatingMUL(CONCAT44((int)uVar4,(int)uVar4),uVar21);
    uVar4 = PackedFloatingMUL(uVar21,CONCAT44(uVar7,uVar7));
    uVar21 = PackedFloatingMUL(uVar21,uVar26);
    uVar2 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),(int)((ulonglong)uVar4 >> 0x20));
    uVar26 = PackedFloatingADD(CONCAT44((int)uVar3,(int)uVar3),uVar8);
    uVar3 = PackedFloatingAccumulate(uVar8,uVar8);
    uVar21 = CONCAT44((int)((ulonglong)uVar18 >> 0x20),(int)uVar21);
    uVar9 = PackedFloatingSUBR(uVar3,0x3f8000003f800000);
    uVar8 = PackedFloatingSUBR(uVar26,0x3f8000003f800000);
    uVar10 = uVar9 & 0xffffffff;
    uVar3 = PackedFloatingADD(uVar2,uVar21);
    uVar14 = PackedFloatingSUB(uVar2,uVar21);
    uVar5 = PackedFloatingADD(uVar4,uVar18);
    uVar11 = PackedFloatingSUB(uVar4,uVar18);
    uVar28 = uVar5 & 0xffffffff;
    uVar16 = (undefined4)uVar14;
    uVar25 = (undefined4)uVar8;
    uVar4 = CONCAT44(uVar25,uVar16);
    uVar7 = (undefined4)uVar3;
    uVar12 = uVar14 >> 0x20;
    uVar24 = (uint)((ulonglong)uVar3 >> 0x20);
    uVar29 = (undefined4)((ulonglong)uVar8 >> 0x20);
    uVar21 = CONCAT44(uVar7,uVar29);
    uVar2 = CONCAT44((int)uVar11,uVar24);
    uVar1 = (undefined4)(uVar14 >> 0x20);
    if (param_2 == (undefined8 *)0x0) {
      *param_1 = CONCAT44(uVar16,uVar29);
      param_1[2] = CONCAT44(uVar25,uVar7);
      param_1[5] = uVar9 & 0xffffffff;
      param_1[7] = 0x3f80000000000000;
      param_1[4] = CONCAT44((int)uVar5,uVar1);
      param_1[6] = 0;
      param_1[3] = uVar11 & 0xffffffff;
      param_1[1] = (ulonglong)uVar24;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar5;
      param_1[1] = uVar11;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar5;
      param_1[3] = uVar11;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar5;
      param_1[5] = uVar11;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[6] = uVar27;
      param_1[7] = uVar11;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar27;
      param_1[1] = uVar11;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar27;
      param_1[3] = uVar11;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar27;
      param_1[5] = uVar11;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar26 = PackedFloatingMUL(uVar21,uVar3);
      uVar21 = CONCAT44(uVar7,uVar7);
      uVar3 = PackedFloatingMUL(uVar3,uVar12);
      uVar18 = PackedFloatingMUL(uVar4,uVar21);
      uVar4 = CONCAT44(uVar16,uVar16);
      uVar21 = PackedFloatingMUL(uVar21,uVar28);
      uVar26 = PackedFloatingADD(uVar18,uVar26);
      uVar18 = PackedFloatingMUL(uVar2,uVar8);
      uVar2 = PackedFloatingADD(uVar21,uVar3);
      uVar21 = PackedFloatingMUL(uVar8,uVar10);
      uVar3 = PackedFloatingADD(uVar18,uVar26);
      uVar8 = PackedFloatingMUL(0,uVar4);
      uVar21 = PackedFloatingADD(uVar2,uVar21);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      uVar12 = PackedFloatingADD(uVar4,uVar21);
      param_1[6] = uVar11;
      param_1[7] = uVar12;
    }
    else {
      uVar26 = CONCAT44(uVar16,uVar29);
      uVar20 = CONCAT44(uVar25,uVar7);
      uVar9 = uVar9 & 0xffffffff;
      uVar22 = CONCAT44((int)uVar5,uVar1);
      uVar11 = uVar11 & 0xffffffff;
      uVar14 = (ulonglong)uVar24;
      uVar3 = *param_2;
      uVar24 = *(uint *)(param_2 + 1);
      *param_1 = 0x3f800000;
      param_1[1] = 0;
      param_1[2] = 0x3f80000000000000;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0x3f800000;
      uVar6 = PackedFloatingSUB(0x3f80000000000000,(ulonglong)uVar24);
      uVar5 = PackedFloatingSUB(0,uVar3);
      param_1[7] = uVar6;
      param_1[6] = uVar5;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar23 = CONCAT44(uVar1,uVar1);
      uVar15 = PackedFloatingMUL(uVar26,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar18 = PackedFloatingMUL(uVar8,uVar14);
      uVar19 = PackedFloatingMUL(uVar20,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar15 = PackedFloatingADD(uVar19,uVar15);
      uVar19 = PackedFloatingMUL(uVar22,uVar23);
      uVar18 = PackedFloatingADD(uVar3,uVar18);
      uVar3 = PackedFloatingMUL(uVar23,uVar9);
      uVar23 = PackedFloatingADD(uVar19,uVar15);
      uVar15 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar18,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar6 = PackedFloatingADD(uVar15,uVar23);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar6;
      param_1[1] = uVar5;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar23 = CONCAT44(uVar1,uVar1);
      uVar15 = PackedFloatingMUL(uVar26,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar18 = PackedFloatingMUL(uVar8,uVar14);
      uVar19 = PackedFloatingMUL(uVar20,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar15 = PackedFloatingADD(uVar19,uVar15);
      uVar19 = PackedFloatingMUL(uVar22,uVar23);
      uVar18 = PackedFloatingADD(uVar3,uVar18);
      uVar3 = PackedFloatingMUL(uVar23,uVar9);
      uVar23 = PackedFloatingADD(uVar19,uVar15);
      uVar15 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar18,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar6 = PackedFloatingADD(uVar15,uVar23);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar6;
      param_1[3] = uVar5;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar23 = CONCAT44(uVar1,uVar1);
      uVar15 = PackedFloatingMUL(uVar26,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar18 = PackedFloatingMUL(uVar8,uVar14);
      uVar19 = PackedFloatingMUL(uVar20,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar15 = PackedFloatingADD(uVar19,uVar15);
      uVar19 = PackedFloatingMUL(uVar22,uVar23);
      uVar18 = PackedFloatingADD(uVar3,uVar18);
      uVar3 = PackedFloatingMUL(uVar23,uVar9);
      uVar23 = PackedFloatingADD(uVar19,uVar15);
      uVar15 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar18,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar6 = PackedFloatingADD(uVar15,uVar23);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar6;
      param_1[5] = uVar5;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar26,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar14);
      uVar20 = PackedFloatingMUL(uVar20,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar22,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar9);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[6] = uVar5;
      param_1[7] = uVar11;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar5;
      param_1[1] = uVar11;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar5;
      param_1[3] = uVar11;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar5 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar5;
      param_1[5] = uVar11;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar27,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,0);
      uVar20 = PackedFloatingMUL(uVar17,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(0,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar13);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[6] = uVar27;
      param_1[7] = uVar11;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar27;
      param_1[1] = uVar11;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar27;
      param_1[3] = uVar11;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar4,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar28);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar2,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar10);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar27 = PackedFloatingADD(uVar23,uVar18);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar27;
      param_1[5] = uVar11;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar26 = PackedFloatingMUL(uVar21,uVar3);
      uVar21 = CONCAT44(uVar7,uVar7);
      uVar3 = PackedFloatingMUL(uVar3,uVar12);
      uVar18 = PackedFloatingMUL(uVar4,uVar21);
      uVar4 = CONCAT44(uVar16,uVar16);
      uVar21 = PackedFloatingMUL(uVar21,uVar28);
      uVar26 = PackedFloatingADD(uVar18,uVar26);
      uVar18 = PackedFloatingMUL(uVar2,uVar8);
      uVar2 = PackedFloatingADD(uVar21,uVar3);
      uVar21 = PackedFloatingMUL(uVar8,uVar10);
      uVar3 = PackedFloatingADD(uVar18,uVar26);
      uVar8 = PackedFloatingMUL(0,uVar4);
      uVar21 = PackedFloatingADD(uVar2,uVar21);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      uVar12 = PackedFloatingADD(uVar4,uVar21);
      param_1[6] = uVar11;
      param_1[7] = uVar12;
      uVar12 = PackedFloatingADD(*param_2,param_1[6]);
      uVar21 = PackedFloatingADD((ulonglong)*(uint *)(param_2 + 1),(ulonglong)(uint)param_1[7]);
      param_1[6] = uVar12;
      *(int *)(param_1 + 7) = (int)uVar21;
    }
  }
  if (param_6 != (undefined8 *)0x0) {
    uVar21 = *param_6;
    uVar4 = param_6[1];
    uVar2 = PackedFloatingADD(uVar21,uVar21);
    uVar3 = PackedFloatingADD(uVar4,uVar4);
    uVar7 = (undefined4)((ulonglong)uVar21 >> 0x20);
    uVar16 = (undefined4)((ulonglong)uVar4 >> 0x20);
    uVar26 = CONCAT44(uVar16,uVar16);
    uVar8 = PackedFloatingMUL(uVar21,uVar2);
    uVar21 = CONCAT44((int)uVar2,(int)uVar3);
    uVar18 = PackedFloatingMUL(uVar2,uVar26);
    uVar3 = PackedFloatingMUL(CONCAT44((int)uVar4,(int)uVar4),uVar21);
    uVar4 = PackedFloatingMUL(uVar21,CONCAT44(uVar7,uVar7));
    uVar21 = PackedFloatingMUL(uVar21,uVar26);
    uVar2 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),(int)((ulonglong)uVar4 >> 0x20));
    uVar26 = PackedFloatingADD(CONCAT44((int)uVar3,(int)uVar3),uVar8);
    uVar3 = PackedFloatingAccumulate(uVar8,uVar8);
    uVar21 = CONCAT44((int)((ulonglong)uVar18 >> 0x20),(int)uVar21);
    uVar27 = PackedFloatingSUBR(uVar3,0x3f8000003f800000);
    uVar8 = PackedFloatingSUBR(uVar26,0x3f8000003f800000);
    uVar27 = uVar27 & 0xffffffff;
    uVar3 = PackedFloatingADD(uVar2,uVar21);
    uVar12 = PackedFloatingSUB(uVar2,uVar21);
    uVar11 = PackedFloatingADD(uVar4,uVar18);
    uVar4 = PackedFloatingSUB(uVar4,uVar18);
    uVar11 = uVar11 & 0xffffffff;
    uVar2 = CONCAT44((int)uVar8,(int)uVar12);
    uVar12 = uVar12 >> 0x20;
    uVar21 = CONCAT44((int)uVar3,(int)((ulonglong)uVar8 >> 0x20));
    uVar4 = CONCAT44((int)uVar4,(int)((ulonglong)uVar3 >> 0x20));
    if (param_5 == (undefined8 *)0x0) {
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar28;
      param_1[1] = uVar5;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar28;
      param_1[3] = uVar5;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar28;
      param_1[5] = uVar5;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar26 = PackedFloatingMUL(uVar21,uVar3);
      uVar21 = CONCAT44(uVar7,uVar7);
      uVar3 = PackedFloatingMUL(uVar3,uVar12);
      uVar18 = PackedFloatingMUL(uVar2,uVar21);
      uVar2 = CONCAT44(uVar16,uVar16);
      uVar21 = PackedFloatingMUL(uVar21,uVar11);
      uVar26 = PackedFloatingADD(uVar18,uVar26);
      uVar18 = PackedFloatingMUL(uVar4,uVar8);
      uVar4 = PackedFloatingADD(uVar21,uVar3);
      uVar21 = PackedFloatingMUL(uVar8,uVar27);
      uVar3 = PackedFloatingADD(uVar18,uVar26);
      uVar8 = PackedFloatingMUL(0,uVar2);
      uVar21 = PackedFloatingADD(uVar4,uVar21);
      uVar4 = PackedFloatingMUL(uVar2,0x3f80000000000000);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      uVar12 = PackedFloatingADD(uVar4,uVar21);
      param_1[6] = uVar11;
      param_1[7] = uVar12;
    }
    else {
      uVar5 = PackedFloatingSUB(param_1[6],*param_5);
      uVar3 = PackedFloatingSUB((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_5 + 1));
      param_1[6] = uVar5;
      *(int *)(param_1 + 7) = (int)uVar3;
      uVar7 = (undefined4)(*param_1 >> 0x20);
      uVar16 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      *param_1 = uVar28;
      param_1[1] = uVar5;
      uVar7 = (undefined4)(param_1[2] >> 0x20);
      uVar16 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[2] = uVar28;
      param_1[3] = uVar5;
      uVar7 = (undefined4)(param_1[4] >> 0x20);
      uVar16 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar18 = CONCAT44(uVar1,uVar1);
      uVar23 = PackedFloatingMUL(uVar21,uVar8);
      uVar3 = CONCAT44(uVar7,uVar7);
      uVar26 = PackedFloatingMUL(uVar8,uVar12);
      uVar20 = PackedFloatingMUL(uVar2,uVar3);
      uVar8 = CONCAT44(uVar16,uVar16);
      uVar3 = PackedFloatingMUL(uVar3,uVar11);
      uVar23 = PackedFloatingADD(uVar20,uVar23);
      uVar20 = PackedFloatingMUL(uVar4,uVar18);
      uVar26 = PackedFloatingADD(uVar3,uVar26);
      uVar3 = PackedFloatingMUL(uVar18,uVar27);
      uVar18 = PackedFloatingADD(uVar20,uVar23);
      uVar23 = PackedFloatingMUL(0,uVar8);
      uVar3 = PackedFloatingADD(uVar26,uVar3);
      uVar8 = PackedFloatingMUL(uVar8,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar23,uVar18);
      uVar5 = PackedFloatingADD(uVar8,uVar3);
      param_1[4] = uVar28;
      param_1[5] = uVar5;
      uVar7 = (undefined4)(param_1[6] >> 0x20);
      uVar16 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar26 = PackedFloatingMUL(uVar21,uVar3);
      uVar21 = CONCAT44(uVar7,uVar7);
      uVar3 = PackedFloatingMUL(uVar3,uVar12);
      uVar18 = PackedFloatingMUL(uVar2,uVar21);
      uVar2 = CONCAT44(uVar16,uVar16);
      uVar21 = PackedFloatingMUL(uVar21,uVar11);
      uVar26 = PackedFloatingADD(uVar18,uVar26);
      uVar18 = PackedFloatingMUL(uVar4,uVar8);
      uVar4 = PackedFloatingADD(uVar21,uVar3);
      uVar21 = PackedFloatingMUL(uVar8,uVar27);
      uVar3 = PackedFloatingADD(uVar18,uVar26);
      uVar8 = PackedFloatingMUL(0,uVar2);
      uVar21 = PackedFloatingADD(uVar4,uVar21);
      uVar4 = PackedFloatingMUL(uVar2,0x3f80000000000000);
      uVar11 = PackedFloatingADD(uVar8,uVar3);
      uVar12 = PackedFloatingADD(uVar4,uVar21);
      param_1[6] = uVar11;
      param_1[7] = uVar12;
      uVar12 = PackedFloatingADD(param_1[6],*param_5);
      uVar21 = PackedFloatingADD((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_5 + 1));
      param_1[6] = uVar12;
      *(int *)(param_1 + 7) = (int)uVar21;
    }
  }
  if (param_7 != (undefined8 *)0x0) {
    uVar12 = PackedFloatingADD(param_1[6],*param_7);
    uVar21 = PackedFloatingADD((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_7 + 1));
    param_1[6] = uVar12;
    *(int *)(param_1 + 7) = (int)uVar21;
  }
  FastExitMediaState();
  return;
}



/* mat3x3_from_euler_simd @ 0045c3ea */

void mat3x3_from_euler_simd(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 uVar1;
  undefined8 extraout_MM0;
  undefined8 extraout_MM0_00;
  undefined8 extraout_MM0_01;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  undefined4 uVar8;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  
  PackedFloatingMUL(0x3f0000003f000000,param_3);
  PackedFloatingMUL(0x3f0000003f000000,param_2);
  math_sincos_packed();
  math_sincos_packed();
  math_sincos_packed();
  uVar1 = (undefined4)extraout_MM0_01;
  uVar8 = (undefined4)((ulonglong)extraout_MM0_01 >> 0x20);
  uVar4 = CONCAT44((int)extraout_MM0_00,(int)extraout_MM0_00);
  uVar11 = (undefined4)((ulonglong)extraout_MM0_00 >> 0x20);
  uVar9 = CONCAT44(uVar11,uVar11);
  uVar2 = PackedFloatingMUL(CONCAT44(uVar1,uVar1) ^ 0x8000000000000000,uVar9);
  uVar3 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),uVar4);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar8,uVar8),uVar4);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar8,uVar8) ^ 0x80000000,uVar9);
  uVar12 = CONCAT44((int)extraout_MM0,(int)((ulonglong)extraout_MM0 >> 0x20));
  uVar2 = PackedFloatingMUL(uVar2,extraout_MM0);
  uVar4 = PackedFloatingMUL(uVar3,uVar12);
  uVar3 = PackedFloatingMUL(uVar6,uVar12);
  uVar6 = PackedFloatingMUL(uVar9,extraout_MM0);
  uVar2 = PackedFloatingADD(uVar2,uVar3);
  uVar6 = PackedFloatingADD(uVar4,uVar6);
  uVar4 = PackedFloatingADD(uVar2,uVar2);
  uVar3 = PackedFloatingADD(uVar6,uVar6);
  uVar1 = (undefined4)((ulonglong)uVar2 >> 0x20);
  uVar8 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar12 = CONCAT44(uVar8,uVar8);
  uVar9 = PackedFloatingMUL(uVar2,uVar4);
  uVar2 = CONCAT44((int)uVar4,(int)uVar3);
  uVar10 = PackedFloatingMUL(uVar4,uVar12);
  uVar6 = PackedFloatingMUL(CONCAT44((int)uVar6,(int)uVar6),uVar2);
  uVar4 = PackedFloatingMUL(uVar2,CONCAT44(uVar1,uVar1));
  uVar2 = PackedFloatingMUL(uVar2,uVar12);
  uVar3 = CONCAT44((int)((ulonglong)uVar6 >> 0x20),(int)((ulonglong)uVar4 >> 0x20));
  param_1[6] = 0;
  uVar12 = PackedFloatingADD(CONCAT44((int)uVar6,(int)uVar6),uVar9);
  uVar6 = PackedFloatingAccumulate(uVar9,uVar9);
  uVar2 = CONCAT44((int)((ulonglong)uVar10 >> 0x20),(int)uVar2);
  uVar5 = PackedFloatingSUBR(uVar6,0x3f8000003f800000);
  uVar9 = PackedFloatingSUBR(uVar12,0x3f8000003f800000);
  uVar6 = PackedFloatingADD(uVar3,uVar2);
  param_1[5] = uVar5 & 0xffffffff;
  uVar7 = PackedFloatingSUB(uVar3,uVar2);
  uVar5 = PackedFloatingADD(uVar4,uVar10);
  uVar2 = PackedFloatingSUB(uVar4,uVar10);
  param_1[3] = uVar5 & 0xffffffff;
  param_1[1] = uVar7 >> 0x20;
  param_1[2] = CONCAT44((int)uVar9,(int)uVar7);
  *param_1 = CONCAT44((int)uVar6,(int)((ulonglong)uVar9 >> 0x20));
  param_1[4] = CONCAT44((int)uVar2,(int)((ulonglong)uVar6 >> 0x20));
  param_1[7] = 0x3f80000000000000;
  FastExitMediaState();
  return;
}



/* mat3x3_from_axis_angle_simd @ 0045cac3 */

void mat3x3_from_axis_angle_simd(undefined8 *param_1,ulonglong *param_2)

{
  undefined8 extraout_MM0;
  undefined8 uVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  ulonglong local_20;
  uint local_18;
  
  local_20 = *param_2;
  local_18 = (uint)param_2[1];
  quat_normalize_simd(&local_20,&local_20);
  math_sincos_packed();
  uVar1 = PackedFloatingSUBR(extraout_MM0,0x3f8000003f800000);
  uVar9 = (undefined4)((ulonglong)extraout_MM0 >> 0x20);
  uVar3 = (ulonglong)local_18;
  uVar4 = PackedFloatingMUL(CONCAT44(local_18,local_18),local_20);
  uVar1 = CONCAT44((int)uVar1,(int)uVar1);
  uVar2 = PackedFloatingMUL(CONCAT44(local_18,(int)(local_20 >> 0x20)),local_20);
  uVar8 = CONCAT44((int)extraout_MM0,(int)extraout_MM0);
  uVar2 = PackedFloatingMUL(uVar2,uVar1);
  uVar4 = PackedFloatingMUL(uVar4,uVar1);
  uVar5 = PackedFloatingMUL(local_20,local_20);
  uVar6 = PackedFloatingMUL(uVar3,uVar3);
  uVar5 = PackedFloatingMUL(uVar5,uVar1);
  uVar1 = PackedFloatingMUL(uVar6,uVar1);
  uVar5 = PackedFloatingADD(uVar5,uVar8);
  uVar7 = PackedFloatingADD(uVar1,uVar8);
  uVar1 = CONCAT44(uVar9,uVar9);
  uVar8 = PackedFloatingMUL(local_20,uVar1);
  uVar1 = PackedFloatingMUL(uVar3,uVar1);
  param_1[6] = 0;
  uVar6 = CONCAT44((int)uVar8,(int)uVar1);
  uVar9 = (undefined4)((ulonglong)uVar8 >> 0x20);
  uVar8 = CONCAT44(uVar9,uVar9);
  param_1[5] = uVar7 & 0xffffffff;
  uVar1 = PackedFloatingSUB(uVar2,uVar6);
  uVar3 = PackedFloatingADD(uVar2,uVar6);
  uVar7 = PackedFloatingSUB(uVar4,uVar8);
  *param_1 = CONCAT44((int)uVar3,(int)uVar5);
  param_1[1] = uVar7 & 0xffffffff;
  uVar8 = PackedFloatingADD(CONCAT44((int)uVar4,(int)uVar4),uVar8);
  param_1[3] = uVar3 >> 0x20;
  param_1[7] = 0x3f80000000000000;
  param_1[4] = CONCAT44((int)((ulonglong)uVar1 >> 0x20),(int)((ulonglong)uVar8 >> 0x20));
  param_1[2] = CONCAT44((int)((ulonglong)uVar5 >> 0x20),(int)uVar1);
  FastExitMediaState();
  return;
}



/* mat_transform_compose_simd @ 0045cbdc */

void mat_transform_compose_simd(ulonglong *param_1,undefined8 *param_2,undefined8 *param_3,ulonglong *param_4,
                 undefined8 *param_5,undefined8 *param_6,undefined8 *param_7)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 in_MM2;
  undefined8 uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  uint uVar11;
  ulonglong in_MM3;
  undefined8 uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  ulonglong uVar15;
  ulonglong uVar16;
  ulonglong uVar17;
  undefined8 uVar18;
  ulonglong uVar19;
  undefined8 uVar20;
  ulonglong uVar21;
  ulonglong uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined4 uVar26;
  undefined8 uVar25;
  undefined4 uVar27;
  ulonglong uVar28;
  ulonglong uVar29;
  
  if (param_4 == (ulonglong *)0x0) {
    uVar16 = PackedSwapDWords(in_MM2,0x3f800000);
    *param_1 = 0x3f800000;
    param_1[1] = 0;
    param_1[2] = uVar16;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0x3f800000;
    param_1[6] = 0;
    param_1[7] = uVar16;
  }
  else if (param_3 == (undefined8 *)0x0) {
    in_MM3 = *param_4;
    uVar16 = param_4[1];
    *param_1 = in_MM3 & 0xffffffff;
    param_1[1] = 0;
    param_1[2] = in_MM3 & 0xffffffff00000000;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = (ulonglong)(uint)uVar16;
    param_1[6] = 0;
    param_1[7] = 0x3f80000000000000;
  }
  else {
    uVar16 = *param_4;
    uVar17 = (ulonglong)(uint)param_4[1];
    uVar28 = uVar16 & 0xffffffff;
    uVar21 = uVar16 & 0xffffffff00000000;
    uVar4 = *param_3;
    uVar18 = param_3[1];
    uVar12 = PackedSwapDWords(uVar16,uVar4);
    uVar2 = PackedFloatingADD(uVar4,uVar4);
    uVar7 = PackedFloatingADD(uVar18,uVar18);
    uVar3 = PackedFloatingMUL(uVar2,uVar4);
    uVar8 = PackedFloatingMUL(uVar4,uVar7);
    uVar13 = PackedFloatingMUL(uVar12,uVar7);
    uVar12 = PackedFloatingMUL(uVar7,uVar18);
    uVar2 = PackedFloatingMUL(CONCAT44((int)((ulonglong)uVar18 >> 0x20),
                                       (int)((ulonglong)uVar4 >> 0x20)),
                              CONCAT44((int)uVar7,(int)uVar2));
    uVar4 = PackedFloatingSUBR(uVar3,0x3f8000003f800000);
    uVar14 = PackedFloatingPosNegAccumulate(uVar13,uVar13);
    uVar18 = PackedFloatingAccumulate(uVar3,uVar3);
    uVar3 = PackedFloatingPosNegAccumulate(uVar2,uVar2);
    uVar9 = PackedFloatingPosNegAccumulate(uVar8,uVar8);
    uVar4 = PackedFloatingSUB(uVar4,CONCAT44((int)uVar12,(int)uVar12));
    uVar22 = PackedSwapDWords(uVar12,uVar9);
    uVar19 = PackedFloatingSUBR(uVar18,0x3f8000003f800000);
    uVar2 = CONCAT44((int)uVar14,(int)uVar22);
    uVar10 = uVar9 & 0xffffffff;
    uVar16 = uVar19 >> 0x20;
    uVar5 = (undefined4)((ulonglong)uVar4 >> 0x20);
    uVar26 = (undefined4)((ulonglong)uVar3 >> 0x20);
    uVar18 = CONCAT44(uVar26,uVar5);
    uVar29 = uVar14 >> 0x20;
    uVar6 = (undefined4)uVar4;
    uVar1 = (undefined4)uVar3;
    uVar4 = CONCAT44(uVar6,uVar1);
    uVar27 = (undefined4)(uVar14 >> 0x20);
    uVar11 = (uint)(uVar19 >> 0x20);
    if (param_2 == (undefined8 *)0x0) {
      *param_1 = CONCAT44(uVar1,uVar5);
      param_1[2] = CONCAT44(uVar6,uVar26);
      param_1[5] = (ulonglong)uVar11;
      param_1[7] = 0x3f80000000000000;
      param_1[4] = CONCAT44(uVar27,(int)uVar9);
      param_1[6] = 0;
      param_1[3] = uVar14 & 0xffffffff;
      param_1[1] = uVar22 & 0xffffffff;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar9;
      param_1[1] = uVar14;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar9;
      param_1[3] = uVar14;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar9;
      param_1[5] = uVar14;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[6] = uVar28;
      param_1[7] = uVar14;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar28;
      param_1[1] = uVar14;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar28;
      param_1[3] = uVar14;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar28;
      param_1[5] = uVar14;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar12 = PackedFloatingMUL(uVar18,uVar3);
      uVar18 = CONCAT44(uVar5,uVar5);
      uVar3 = PackedFloatingMUL(uVar3,uVar10);
      uVar8 = PackedFloatingMUL(uVar4,uVar18);
      uVar4 = CONCAT44(uVar6,uVar6);
      uVar18 = PackedFloatingMUL(uVar18,uVar29);
      uVar12 = PackedFloatingADD(uVar8,uVar12);
      uVar8 = PackedFloatingMUL(uVar2,uVar7);
      uVar2 = PackedFloatingADD(uVar18,uVar3);
      uVar18 = PackedFloatingMUL(uVar7,uVar16);
      uVar3 = PackedFloatingADD(uVar8,uVar12);
      uVar7 = PackedFloatingMUL(0,uVar4);
      uVar18 = PackedFloatingADD(uVar2,uVar18);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar16 = PackedFloatingADD(uVar7,uVar3);
      in_MM3 = PackedFloatingADD(uVar4,uVar18);
      param_1[6] = uVar16;
      param_1[7] = in_MM3;
    }
    else {
      uVar12 = CONCAT44(uVar1,uVar5);
      uVar24 = CONCAT44(uVar6,uVar26);
      uVar15 = (ulonglong)uVar11;
      uVar25 = CONCAT44(uVar27,(int)uVar9);
      uVar14 = uVar14 & 0xffffffff;
      uVar22 = uVar22 & 0xffffffff;
      uVar3 = *param_2;
      uVar11 = *(uint *)(param_2 + 1);
      uVar9 = PackedSwapDWords(uVar22,0x3f800000);
      *param_1 = 0x3f800000;
      param_1[1] = 0;
      param_1[2] = uVar9;
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0x3f800000;
      uVar19 = PackedFloatingSUB(uVar9,(ulonglong)uVar11);
      uVar9 = PackedFloatingSUB(0,uVar3);
      param_1[7] = uVar19;
      param_1[6] = uVar9;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar13 = CONCAT44(uVar1,uVar1);
      uVar20 = PackedFloatingMUL(uVar12,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar8 = PackedFloatingMUL(uVar7,uVar22);
      uVar23 = PackedFloatingMUL(uVar24,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar20 = PackedFloatingADD(uVar23,uVar20);
      uVar23 = PackedFloatingMUL(uVar25,uVar13);
      uVar8 = PackedFloatingADD(uVar3,uVar8);
      uVar3 = PackedFloatingMUL(uVar13,uVar15);
      uVar13 = PackedFloatingADD(uVar23,uVar20);
      uVar20 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar8,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar19 = PackedFloatingADD(uVar20,uVar13);
      uVar9 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar19;
      param_1[1] = uVar9;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar13 = CONCAT44(uVar1,uVar1);
      uVar20 = PackedFloatingMUL(uVar12,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar8 = PackedFloatingMUL(uVar7,uVar22);
      uVar23 = PackedFloatingMUL(uVar24,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar20 = PackedFloatingADD(uVar23,uVar20);
      uVar23 = PackedFloatingMUL(uVar25,uVar13);
      uVar8 = PackedFloatingADD(uVar3,uVar8);
      uVar3 = PackedFloatingMUL(uVar13,uVar15);
      uVar13 = PackedFloatingADD(uVar23,uVar20);
      uVar20 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar8,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar19 = PackedFloatingADD(uVar20,uVar13);
      uVar9 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar19;
      param_1[3] = uVar9;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar13 = CONCAT44(uVar1,uVar1);
      uVar20 = PackedFloatingMUL(uVar12,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar8 = PackedFloatingMUL(uVar7,uVar22);
      uVar23 = PackedFloatingMUL(uVar24,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar20 = PackedFloatingADD(uVar23,uVar20);
      uVar23 = PackedFloatingMUL(uVar25,uVar13);
      uVar8 = PackedFloatingADD(uVar3,uVar8);
      uVar3 = PackedFloatingMUL(uVar13,uVar15);
      uVar13 = PackedFloatingADD(uVar23,uVar20);
      uVar20 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar8,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar19 = PackedFloatingADD(uVar20,uVar13);
      uVar9 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar19;
      param_1[5] = uVar9;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar12,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar22);
      uVar24 = PackedFloatingMUL(uVar24,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar25,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar15);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[6] = uVar9;
      param_1[7] = uVar14;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar9;
      param_1[1] = uVar14;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar9;
      param_1[3] = uVar14;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar9;
      param_1[5] = uVar14;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar28,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,0);
      uVar24 = PackedFloatingMUL(uVar21,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,0);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(0,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar17);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[6] = uVar28;
      param_1[7] = uVar14;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar28;
      param_1[1] = uVar14;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar28;
      param_1[3] = uVar14;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar10);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar28 = PackedFloatingADD(uVar13,uVar8);
      uVar14 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar28;
      param_1[5] = uVar14;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar12 = PackedFloatingMUL(uVar18,uVar3);
      uVar18 = CONCAT44(uVar5,uVar5);
      uVar3 = PackedFloatingMUL(uVar3,uVar10);
      uVar8 = PackedFloatingMUL(uVar4,uVar18);
      uVar4 = CONCAT44(uVar6,uVar6);
      uVar18 = PackedFloatingMUL(uVar18,uVar29);
      uVar12 = PackedFloatingADD(uVar8,uVar12);
      uVar8 = PackedFloatingMUL(uVar2,uVar7);
      uVar2 = PackedFloatingADD(uVar18,uVar3);
      uVar18 = PackedFloatingMUL(uVar7,uVar16);
      uVar3 = PackedFloatingADD(uVar8,uVar12);
      uVar7 = PackedFloatingMUL(0,uVar4);
      uVar18 = PackedFloatingADD(uVar2,uVar18);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar29 = PackedFloatingADD(uVar7,uVar3);
      uVar16 = PackedFloatingADD(uVar4,uVar18);
      param_1[6] = uVar29;
      param_1[7] = uVar16;
      in_MM3 = (ulonglong)(uint)param_1[7];
      uVar16 = PackedFloatingADD(*param_2,param_1[6]);
      uVar4 = PackedFloatingADD((ulonglong)*(uint *)(param_2 + 1),in_MM3);
      param_1[6] = uVar16;
      *(int *)(param_1 + 7) = (int)uVar4;
    }
  }
  if (param_6 != (undefined8 *)0x0) {
    uVar4 = *param_6;
    uVar18 = param_6[1];
    uVar12 = PackedSwapDWords(in_MM3,uVar4);
    uVar2 = PackedFloatingADD(uVar4,uVar4);
    uVar7 = PackedFloatingADD(uVar18,uVar18);
    uVar3 = PackedFloatingMUL(uVar2,uVar4);
    uVar8 = PackedFloatingMUL(uVar4,uVar7);
    uVar13 = PackedFloatingMUL(uVar12,uVar7);
    uVar12 = PackedFloatingMUL(uVar7,uVar18);
    uVar2 = PackedFloatingMUL(CONCAT44((int)((ulonglong)uVar18 >> 0x20),
                                       (int)((ulonglong)uVar4 >> 0x20)),
                              CONCAT44((int)uVar7,(int)uVar2));
    uVar4 = PackedFloatingSUBR(uVar3,0x3f8000003f800000);
    uVar29 = PackedFloatingPosNegAccumulate(uVar13,uVar13);
    uVar18 = PackedFloatingAccumulate(uVar3,uVar3);
    uVar3 = PackedFloatingPosNegAccumulate(uVar2,uVar2);
    uVar14 = PackedFloatingPosNegAccumulate(uVar8,uVar8);
    uVar4 = PackedFloatingSUB(uVar4,CONCAT44((int)uVar12,(int)uVar12));
    uVar2 = PackedSwapDWords(uVar12,uVar14);
    uVar16 = PackedFloatingSUBR(uVar18,0x3f8000003f800000);
    uVar2 = CONCAT44((int)uVar29,(int)uVar2);
    uVar14 = uVar14 & 0xffffffff;
    uVar16 = uVar16 >> 0x20;
    uVar18 = CONCAT44((int)((ulonglong)uVar3 >> 0x20),(int)((ulonglong)uVar4 >> 0x20));
    uVar29 = uVar29 >> 0x20;
    uVar4 = CONCAT44((int)uVar4,(int)uVar3);
    if (param_5 == (undefined8 *)0x0) {
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar9;
      param_1[1] = uVar28;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar9;
      param_1[3] = uVar28;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar9;
      param_1[5] = uVar28;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar12 = PackedFloatingMUL(uVar18,uVar3);
      uVar18 = CONCAT44(uVar5,uVar5);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar8 = PackedFloatingMUL(uVar4,uVar18);
      uVar4 = CONCAT44(uVar6,uVar6);
      uVar18 = PackedFloatingMUL(uVar18,uVar29);
      uVar12 = PackedFloatingADD(uVar8,uVar12);
      uVar8 = PackedFloatingMUL(uVar2,uVar7);
      uVar2 = PackedFloatingADD(uVar18,uVar3);
      uVar18 = PackedFloatingMUL(uVar7,uVar16);
      uVar3 = PackedFloatingADD(uVar8,uVar12);
      uVar7 = PackedFloatingMUL(0,uVar4);
      uVar18 = PackedFloatingADD(uVar2,uVar18);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar29 = PackedFloatingADD(uVar7,uVar3);
      uVar16 = PackedFloatingADD(uVar4,uVar18);
      param_1[6] = uVar29;
      param_1[7] = uVar16;
    }
    else {
      uVar28 = PackedFloatingSUB(param_1[6],*param_5);
      uVar3 = PackedFloatingSUB((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_5 + 1));
      param_1[6] = uVar28;
      *(int *)(param_1 + 7) = (int)uVar3;
      uVar5 = (undefined4)(*param_1 >> 0x20);
      uVar6 = (undefined4)(param_1[1] >> 0x20);
      uVar1 = (undefined4)*param_1;
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[1];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      *param_1 = uVar9;
      param_1[1] = uVar28;
      uVar5 = (undefined4)(param_1[2] >> 0x20);
      uVar6 = (undefined4)(param_1[3] >> 0x20);
      uVar1 = (undefined4)param_1[2];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[3];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      param_1[2] = uVar9;
      param_1[3] = uVar28;
      uVar5 = (undefined4)(param_1[4] >> 0x20);
      uVar6 = (undefined4)(param_1[5] >> 0x20);
      uVar1 = (undefined4)param_1[4];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[5];
      uVar8 = CONCAT44(uVar1,uVar1);
      uVar13 = PackedFloatingMUL(uVar18,uVar7);
      uVar3 = CONCAT44(uVar5,uVar5);
      uVar12 = PackedFloatingMUL(uVar7,uVar14);
      uVar24 = PackedFloatingMUL(uVar4,uVar3);
      uVar7 = CONCAT44(uVar6,uVar6);
      uVar3 = PackedFloatingMUL(uVar3,uVar29);
      uVar13 = PackedFloatingADD(uVar24,uVar13);
      uVar24 = PackedFloatingMUL(uVar2,uVar8);
      uVar12 = PackedFloatingADD(uVar3,uVar12);
      uVar3 = PackedFloatingMUL(uVar8,uVar16);
      uVar8 = PackedFloatingADD(uVar24,uVar13);
      uVar13 = PackedFloatingMUL(0,uVar7);
      uVar3 = PackedFloatingADD(uVar12,uVar3);
      uVar7 = PackedFloatingMUL(uVar7,0x3f80000000000000);
      uVar9 = PackedFloatingADD(uVar13,uVar8);
      uVar28 = PackedFloatingADD(uVar7,uVar3);
      param_1[4] = uVar9;
      param_1[5] = uVar28;
      uVar5 = (undefined4)(param_1[6] >> 0x20);
      uVar6 = (undefined4)(param_1[7] >> 0x20);
      uVar1 = (undefined4)param_1[6];
      uVar3 = CONCAT44(uVar1,uVar1);
      uVar1 = (undefined4)param_1[7];
      uVar7 = CONCAT44(uVar1,uVar1);
      uVar12 = PackedFloatingMUL(uVar18,uVar3);
      uVar18 = CONCAT44(uVar5,uVar5);
      uVar3 = PackedFloatingMUL(uVar3,uVar14);
      uVar8 = PackedFloatingMUL(uVar4,uVar18);
      uVar4 = CONCAT44(uVar6,uVar6);
      uVar18 = PackedFloatingMUL(uVar18,uVar29);
      uVar12 = PackedFloatingADD(uVar8,uVar12);
      uVar8 = PackedFloatingMUL(uVar2,uVar7);
      uVar2 = PackedFloatingADD(uVar18,uVar3);
      uVar18 = PackedFloatingMUL(uVar7,uVar16);
      uVar3 = PackedFloatingADD(uVar8,uVar12);
      uVar7 = PackedFloatingMUL(0,uVar4);
      uVar18 = PackedFloatingADD(uVar2,uVar18);
      uVar4 = PackedFloatingMUL(uVar4,0x3f80000000000000);
      uVar29 = PackedFloatingADD(uVar7,uVar3);
      uVar16 = PackedFloatingADD(uVar4,uVar18);
      param_1[6] = uVar29;
      param_1[7] = uVar16;
      uVar16 = PackedFloatingADD(param_1[6],*param_5);
      uVar4 = PackedFloatingADD((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_5 + 1));
      param_1[6] = uVar16;
      *(int *)(param_1 + 7) = (int)uVar4;
    }
  }
  if (param_7 != (undefined8 *)0x0) {
    uVar16 = PackedFloatingADD(param_1[6],*param_7);
    uVar4 = PackedFloatingADD((ulonglong)(uint)param_1[7],(ulonglong)*(uint *)(param_7 + 1));
    param_1[6] = uVar16;
    *(int *)(param_1 + 7) = (int)uVar4;
  }
  FastExitMediaState();
  return;
}



/* mat4_invert_simd @ 0045dd30 */

void mat4_invert_simd(undefined8 *param_1,undefined4 *param_2,undefined8 *param_3)

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



/* mat4_invert @ 0045e40a */

/* inverts a 4x4 matrix; optionally writes determinant */

float * mat4_invert(float *out,float *det_out,float *mat)

{
  float fVar1;
  float *pfVar2;
  undefined4 uVar3;
  undefined4 uVar5;
  undefined8 uVar4;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  undefined4 uVar12;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined4 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined4 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined4 uVar22;
  undefined8 uVar21;
  undefined4 uStack_34;
  
  uVar12 = (undefined4)((ulonglong)*(undefined8 *)mat >> 0x20);
  uVar3 = (undefined4)*(undefined8 *)(mat + 8);
  uVar17 = (undefined4)*(undefined8 *)(mat + 4);
  uVar13 = (undefined4)*(undefined8 *)mat;
  uVar22 = (undefined4)((ulonglong)*(undefined8 *)(mat + 4) >> 0x20);
  uVar5 = (undefined4)((ulonglong)*(undefined8 *)(mat + 8) >> 0x20);
  uVar10 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),CONCAT44(uVar3,uVar17));
  uVar14 = PackedFloatingMUL(CONCAT44(uVar13,uVar13),CONCAT44(uVar5,uVar22));
  uVar15 = PackedFloatingSUB(uVar14,uVar10);
  uVar6 = (undefined4)((ulonglong)*(undefined8 *)(mat + 0xc) >> 0x20);
  uVar9 = (undefined4)*(undefined8 *)(mat + 0xc);
  uVar18 = PackedFloatingMUL(CONCAT44(uVar5,uVar6),CONCAT44(uVar17,uVar13));
  uVar21 = PackedFloatingMUL(CONCAT44(uVar22,uVar12),CONCAT44(uVar3,uVar9));
  uVar10 = PackedFloatingMUL(CONCAT44(uVar3,uVar17),CONCAT44(uVar6,uVar6));
  uVar14 = PackedFloatingMUL(CONCAT44(uVar5,uVar22),CONCAT44(uVar9,uVar9));
  uVar19 = PackedFloatingSUB(uVar18,uVar21);
  uVar18 = PackedFloatingSUBR(uVar14,uVar10);
  uVar10 = *(undefined8 *)(mat + 0xe);
  uVar14 = *(undefined8 *)(mat + 10);
  uVar3 = (undefined4)((ulonglong)uVar19 >> 0x20);
  uVar12 = (undefined4)((ulonglong)uVar18 >> 0x20);
  uVar21 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),uVar10);
  uVar6 = (undefined4)uVar18;
  uVar18 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),*(undefined8 *)(mat + 6));
  uVar7 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),uVar14);
  uVar18 = PackedFloatingADD(uVar21,uVar18);
  uVar4 = PackedFloatingSUB(uVar18,uVar7);
  uVar9 = (undefined4)uVar19;
  uVar5 = (undefined4)((ulonglong)uVar15 >> 0x20);
  uVar21 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),*(undefined8 *)(mat + 2));
  uVar18 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar10);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar9,uVar9),uVar14);
  uVar18 = PackedFloatingSUB(uVar18,uVar7);
  uVar19 = PackedFloatingADD(uVar18,uVar21);
  uVar21 = CONCAT44((int)uVar15,(int)uVar15);
  uVar18 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),*(undefined8 *)(mat + 2));
  uVar10 = PackedFloatingMUL(uVar10,uVar21);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar9,uVar9),*(undefined8 *)(mat + 6));
  uVar10 = PackedFloatingADD(uVar10,uVar18);
  uVar18 = PackedFloatingSUB(uVar10,uVar7);
  uVar10 = PackedFloatingMUL(uVar21,uVar14);
  uVar14 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),*(undefined8 *)(mat + 6));
  uVar21 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),*(undefined8 *)(mat + 2));
  uVar10 = PackedFloatingSUB(uVar10,uVar14);
  uVar15 = PackedFloatingADD(uVar10,uVar21);
  uVar12 = (undefined4)((ulonglong)*(undefined8 *)(mat + 2) >> 0x20);
  uVar3 = (undefined4)*(undefined8 *)(mat + 10);
  uVar17 = (undefined4)*(undefined8 *)(mat + 6);
  uVar13 = (undefined4)*(undefined8 *)(mat + 2);
  uVar22 = (undefined4)((ulonglong)*(undefined8 *)(mat + 6) >> 0x20);
  uVar5 = (undefined4)((ulonglong)*(undefined8 *)(mat + 10) >> 0x20);
  uVar10 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),CONCAT44(uVar3,uVar17));
  uVar14 = PackedFloatingMUL(CONCAT44(uVar13,uVar13),CONCAT44(uVar5,uVar22));
  uVar16 = PackedFloatingSUB(uVar14,uVar10);
  uVar6 = (undefined4)((ulonglong)*(undefined8 *)(mat + 0xe) >> 0x20);
  uVar9 = (undefined4)*(undefined8 *)(mat + 0xe);
  uVar21 = PackedFloatingMUL(CONCAT44(uVar5,uVar6),CONCAT44(uVar17,uVar13));
  uVar7 = PackedFloatingMUL(CONCAT44(uVar22,uVar12),CONCAT44(uVar3,uVar9));
  uVar10 = PackedFloatingMUL(CONCAT44(uVar3,uVar17),CONCAT44(uVar6,uVar6));
  uVar14 = PackedFloatingMUL(CONCAT44(uVar5,uVar22),CONCAT44(uVar9,uVar9));
  uVar20 = PackedFloatingSUB(uVar21,uVar7);
  uVar21 = PackedFloatingSUBR(uVar14,uVar10);
  uVar10 = *(undefined8 *)(mat + 0xc);
  uVar14 = *(undefined8 *)(mat + 8);
  uVar12 = (undefined4)((ulonglong)uVar21 >> 0x20);
  uVar6 = (undefined4)uVar21;
  uVar3 = (undefined4)((ulonglong)uVar20 >> 0x20);
  uVar11 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),*(undefined8 *)(mat + 4));
  uVar21 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),uVar10);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),uVar14);
  uVar21 = PackedFloatingADD(uVar21,uVar11);
  uVar11 = PackedFloatingSUB(uVar21,uVar7);
  uVar9 = (undefined4)uVar20;
  uVar5 = (undefined4)((ulonglong)uVar16 >> 0x20);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar12,uVar12),*(undefined8 *)mat);
  uVar21 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),uVar10);
  uVar20 = PackedFloatingMUL(CONCAT44(uVar9,uVar9),uVar14);
  uVar21 = PackedFloatingSUB(uVar21,uVar20);
  uVar20 = PackedFloatingADD(uVar21,uVar7);
  uVar16 = CONCAT44((int)uVar16,(int)uVar16);
  uVar7 = PackedFloatingMUL(CONCAT44(uVar6,uVar6),*(undefined8 *)mat);
  uVar21 = PackedFloatingMUL(uVar10,uVar16);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar9,uVar9),*(undefined8 *)(mat + 4));
  uVar21 = PackedFloatingADD(uVar21,uVar7);
  uVar21 = PackedFloatingSUB(uVar21,uVar8);
  uVar7 = PackedFloatingMUL(uVar16,uVar14);
  uVar16 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),*(undefined8 *)(mat + 4));
  uVar8 = PackedFloatingMUL(CONCAT44(uVar3,uVar3),*(undefined8 *)mat);
  uVar7 = PackedFloatingSUB(uVar7,uVar16);
  uVar7 = PackedFloatingADD(uVar7,uVar8);
  uVar10 = PackedFloatingMUL(CONCAT44((int)uVar10,(int)uVar14),0xbf8000003f800000);
  uStack_34 = (undefined4)((ulonglong)uVar20 >> 0x20);
  uVar14 = CONCAT44(uStack_34,(int)((ulonglong)uVar11 >> 0x20));
  uVar16 = PackedFloatingMUL(CONCAT44(mat[4],(int)*(undefined8 *)mat),0xbf8000003f800000);
  uVar10 = PackedFloatingMUL(CONCAT44((int)((ulonglong)uVar7 >> 0x20),
                                      (int)((ulonglong)uVar21 >> 0x20)),uVar10);
  uVar16 = PackedFloatingMUL(uVar16,uVar14);
  uVar10 = PackedFloatingADD(uVar10,uVar16);
  uVar10 = PackedFloatingAccumulate(uVar10,uVar10);
  fVar1 = (float)uVar10;
  if (det_out != (float *)0x0) {
    *det_out = fVar1;
  }
  uVar14 = FloatingReciprocalAprox(uVar14,uVar10);
  uVar16 = PackedFloatingCompareEQ(0,uVar10);
  uVar10 = PackedFloatingReciprocalIter1(CONCAT44(fVar1,fVar1),uVar14);
  uVar10 = PackedFloatingReciprocalIter2(uVar10,uVar14);
  uVar14 = PackedFloatingMUL(uVar10,0xbf8000003f800000);
  uVar10 = CONCAT44((int)uVar14,(int)((ulonglong)uVar14 >> 0x20));
  pfVar2 = (float *)uVar16;
  if ((float *)uVar16 == (float *)0x0) {
    uVar11 = PackedFloatingMUL(uVar11,uVar10);
    uVar20 = PackedFloatingMUL(uVar20,uVar14);
    uVar4 = PackedFloatingMUL(uVar4,uVar10);
    uVar19 = PackedFloatingMUL(uVar19,uVar14);
    *(ulonglong *)out = CONCAT44((int)((ulonglong)uVar20 >> 0x20),(int)((ulonglong)uVar11 >> 0x20));
    *(ulonglong *)(out + 4) = CONCAT44((int)uVar20,(int)uVar11);
    *(ulonglong *)(out + 8) =
         CONCAT44((int)((ulonglong)uVar19 >> 0x20),(int)((ulonglong)uVar4 >> 0x20));
    *(ulonglong *)(out + 0xc) = CONCAT44((int)uVar19,(int)uVar4);
    uVar21 = PackedFloatingMUL(uVar21,uVar10);
    uVar7 = PackedFloatingMUL(uVar7,uVar14);
    uVar10 = PackedFloatingMUL(uVar18,uVar10);
    uVar14 = PackedFloatingMUL(uVar15,uVar14);
    *(ulonglong *)(out + 2) =
         CONCAT44((int)((ulonglong)uVar7 >> 0x20),(int)((ulonglong)uVar21 >> 0x20));
    *(ulonglong *)(out + 6) = CONCAT44((int)uVar7,(int)uVar21);
    *(ulonglong *)(out + 10) =
         CONCAT44((int)((ulonglong)uVar14 >> 0x20),(int)((ulonglong)uVar10 >> 0x20));
    *(ulonglong *)(out + 0xe) = CONCAT44((int)uVar14,(int)uVar10);
    pfVar2 = out;
  }
  return pfVar2;
}



/* quat_normalize_simd @ 0045e832 */

void quat_normalize_simd(undefined8 *param_1,ulonglong *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined8 in_MM4;
  undefined8 uVar5;
  ulonglong uVar6;
  
  FastExitMediaState();
  uVar1 = *param_2;
  uVar3 = (ulonglong)(uint)param_2[1];
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar3,uVar3);
  uVar2 = PackedFloatingADD(uVar2,uVar4);
  uVar2 = PackedFloatingAccumulate(uVar2,uVar2);
  uVar5 = PackedFloatingReciprocalSQRAprox(in_MM4,uVar2);
  uVar6 = PackedFloatingCompareGT(uVar2,0x80000000800000);
  uVar4 = PackedFloatingMUL(uVar5,uVar5);
  uVar2 = PackedFloatingReciprocalSQRIter1(uVar2,uVar4);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar5);
  uVar4 = PackedFloatingMUL(uVar1 & uVar6,uVar2);
  uVar2 = PackedFloatingMUL(uVar3 & uVar6,uVar2);
  *param_1 = uVar4;
  *(int *)(param_1 + 1) = (int)uVar2;
  FastExitMediaState();
  return;
}



/* mat4_mul @ 0045eb4b */

/* multiplies two 4x4 matrices (SSE) */

float * mat4_mul(float *out,float *lhs,float *rhs)

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
  
  uVar1 = (undefined4)((ulonglong)*(undefined8 *)lhs >> 0x20);
  uVar2 = (undefined4)((ulonglong)*(undefined8 *)(lhs + 2) >> 0x20);
  uVar3 = (undefined4)*(undefined8 *)lhs;
  uVar6 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)*(undefined8 *)(lhs + 2);
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar7 = PackedFloatingMUL(*(undefined8 *)rhs,uVar6);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar6,*(undefined8 *)(rhs + 2));
  uVar8 = PackedFloatingMUL(*(undefined8 *)(rhs + 4),uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,*(undefined8 *)(rhs + 6));
  uVar7 = PackedFloatingADD(uVar8,uVar7);
  uVar8 = PackedFloatingMUL(*(undefined8 *)(rhs + 8),uVar9);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar9,*(undefined8 *)(rhs + 10));
  uVar9 = PackedFloatingADD(uVar8,uVar7);
  uVar7 = PackedFloatingMUL(*(undefined8 *)(rhs + 0xc),uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,*(undefined8 *)(rhs + 0xe));
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = *(undefined8 *)(lhs + 4);
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = *(undefined8 *)(lhs + 6);
  *(undefined8 *)out = uVar7;
  uVar4 = *(undefined8 *)rhs;
  *(undefined8 *)(out + 2) = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,*(undefined8 *)(rhs + 2));
  uVar9 = PackedFloatingMUL(*(undefined8 *)(rhs + 4),uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,*(undefined8 *)(rhs + 6));
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(*(undefined8 *)(rhs + 8),uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,*(undefined8 *)(rhs + 10));
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(*(undefined8 *)(rhs + 0xc),uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,*(undefined8 *)(rhs + 0xe));
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = *(undefined8 *)(lhs + 8);
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = *(undefined8 *)(lhs + 10);
  *(undefined8 *)(out + 4) = uVar7;
  uVar4 = *(undefined8 *)rhs;
  *(undefined8 *)(out + 6) = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,*(undefined8 *)(rhs + 2));
  uVar9 = PackedFloatingMUL(*(undefined8 *)(rhs + 4),uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,*(undefined8 *)(rhs + 6));
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(*(undefined8 *)(rhs + 8),uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,*(undefined8 *)(rhs + 10));
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(*(undefined8 *)(rhs + 0xc),uVar6);
  uVar4 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,*(undefined8 *)(rhs + 0xe));
  uVar7 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = *(undefined8 *)(lhs + 0xc);
  uVar9 = PackedFloatingADD(uVar6,uVar4);
  uVar6 = *(undefined8 *)(lhs + 0xe);
  *(undefined8 *)(out + 8) = uVar7;
  uVar4 = *(undefined8 *)rhs;
  *(undefined8 *)(out + 10) = uVar9;
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar2 = (undefined4)((ulonglong)uVar6 >> 0x20);
  uVar3 = (undefined4)uVar5;
  uVar9 = CONCAT44(uVar3,uVar3);
  uVar3 = (undefined4)uVar6;
  uVar7 = CONCAT44(uVar3,uVar3);
  uVar8 = PackedFloatingMUL(uVar4,uVar9);
  uVar5 = CONCAT44(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar9,*(undefined8 *)(rhs + 2));
  uVar9 = PackedFloatingMUL(*(undefined8 *)(rhs + 4),uVar5);
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,*(undefined8 *)(rhs + 6));
  uVar9 = PackedFloatingADD(uVar9,uVar8);
  uVar8 = PackedFloatingMUL(*(undefined8 *)(rhs + 8),uVar7);
  uVar4 = PackedFloatingADD(uVar5,uVar4);
  uVar5 = PackedFloatingMUL(uVar7,*(undefined8 *)(rhs + 10));
  uVar9 = PackedFloatingADD(uVar8,uVar9);
  uVar7 = PackedFloatingMUL(*(undefined8 *)(rhs + 0xc),uVar6);
  uVar5 = PackedFloatingADD(uVar4,uVar5);
  uVar6 = PackedFloatingMUL(uVar6,*(undefined8 *)(rhs + 0xe));
  uVar4 = PackedFloatingADD(uVar7,uVar9);
  uVar5 = PackedFloatingADD(uVar6,uVar5);
  *(undefined8 *)(out + 0xc) = uVar4;
  *(undefined8 *)(out + 0xe) = uVar5;
  FastExitMediaState();
  return out;
}



/* vec_unproject_simd @ 0045f0c5 */

ulonglong *
vec_unproject_simd(ulonglong *param_1,ulonglong *param_2,undefined8 *param_3,undefined8 *param_4,
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
  float local_44 [16];
  
  switch(((param_6 != (undefined8 *)0x0) << 1 | param_5 != (undefined8 *)0x0) << 1 |
         param_4 != (undefined8 *)0x0) {
  case '\0':
    mat4x4_identity_simd((undefined8 *)local_44);
    goto switchD_0045f0fb_default;
  case '\x01':
    param_6 = param_4;
    goto LAB_0045f13f;
  case '\x02':
    param_6 = param_5;
    goto LAB_0045f13f;
  case '\x03':
    param_6 = param_5;
    break;
  case '\x04':
    goto LAB_0045f13f;
  case '\x05':
    break;
  case '\x06':
    param_4 = param_5;
    break;
  case '\a':
    mat4_mul(local_44,(float *)param_6,(float *)param_5);
    param_6 = (undefined8 *)local_44;
    break;
  default:
    goto switchD_0045f0fb_default;
  }
  mat4_mul(local_44,(float *)param_6,(float *)param_4);
  param_6 = (undefined8 *)local_44;
LAB_0045f13f:
  mat4_invert_simd((undefined8 *)local_44,(undefined4 *)0x0,param_6);
switchD_0045f0fb_default:
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
  vec3_transform_coord((float *)param_1,(float *)param_2,local_44);
  return param_1;
}



/* color_blend_multiply @ 0045fbd0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl color_blend_multiply(uint *param_1,uint *param_2,uint *param_3)

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
  
  fVar6 = (float)(*param_1 & simd_sincos_const_g);
  fVar10 = (float)(param_1[1] & uRam0047ada4);
  fVar14 = (float)(param_1[2] & uRam0047ada8);
  fVar18 = (float)(param_1[3] & uRam0047adac);
  uVar22 = param_1[1] & uRam0047ad94;
  uVar23 = param_1[2] & uRam0047ad98;
  uVar24 = param_1[3] & uRam0047ad9c;
  fVar7 = fVar6 * simd_sincos_const_f + simd_sincos_const_a;
  fVar11 = fVar10 * fRam0047ad84 + fRam0047ad34;
  fVar15 = fVar14 * fRam0047ad88 + fRam0047ad38;
  fVar19 = fVar18 * fRam0047ad8c + fRam0047ad3c;
  fVar8 = fVar7 - simd_sincos_const_a;
  fVar12 = fVar11 - fRam0047ad34;
  fVar16 = fVar15 - fRam0047ad38;
  fVar20 = fVar19 - fRam0047ad3c;
  fVar6 = (((fVar6 - simd_sincos_const_e * fVar8) - simd_sincos_const_d * fVar8) - simd_sincos_const_c * fVar8) -
          simd_sincos_const_b * fVar8;
  fVar8 = (((fVar10 - fRam0047ad74 * fVar12) - fRam0047ad64 * fVar12) - fRam0047ad54 * fVar12) -
          fRam0047ad44 * fVar12;
  fVar10 = (((fVar14 - fRam0047ad78 * fVar16) - fRam0047ad68 * fVar16) - fRam0047ad58 * fVar16) -
           fRam0047ad48 * fVar16;
  fVar12 = (((fVar18 - fRam0047ad7c * fVar20) - fRam0047ad6c * fVar20) - fRam0047ad5c * fVar20) -
           fRam0047ad4c * fVar20;
  fVar14 = fVar6 * fVar6;
  fVar16 = fVar8 * fVar8;
  fVar18 = fVar10 * fVar10;
  fVar20 = fVar12 * fVar12;
  uVar25 = (uint)fVar7 & simd_sincos_quadrant_mask;
  uVar26 = (uint)fVar11 & uRam0047ad04;
  uVar27 = (uint)fVar15 & uRam0047ad08;
  uVar28 = (uint)fVar19 & uRam0047ad0c;
  uVar9 = uVar25 & simd_sincos_range_mask;
  uVar13 = uVar26 & uRam0047acf4;
  uVar17 = uVar27 & uRam0047acf8;
  uVar21 = uVar28 & uRam0047acfc;
  uVar1 = uVar26 - uVar13 & simd_mantissa_mask;
  uVar2 = uVar27 - uVar17 & simd_mantissa_mask;
  uVar3 = uVar28 - uVar21 & simd_mantissa_mask;
  uVar4 = uVar25 + uVar9 & simd_mantissa_mask;
  uVar26 = uVar26 + uVar13 & simd_mantissa_mask;
  uVar27 = uVar27 + uVar17 & simd_mantissa_mask;
  uVar28 = uVar28 + uVar21 & simd_mantissa_mask;
  uVar5 = -(uint)((float)(uVar9 << 0x1e) != 0.0);
  uVar13 = -(uint)((float)(uVar13 << 0x1e) != 0.0);
  uVar17 = -(uint)((float)(uVar17 << 0x1e) != 0.0);
  uVar21 = -(uint)((float)(uVar21 << 0x1e) != 0.0);
  fVar6 = (((simd_sin_coeff_s4 * fVar14 + simd_sin_coeff_s3) * fVar14 + simd_sin_coeff_s2) * fVar14 +
          simd_sin_coeff_s1) * fVar6;
  fVar8 = (((fRam0047ad24 * fVar16 + fRam0047acd4) * fVar16 + fRam0047acb4) * fVar16 + fRam0047ac94)
          * fVar8;
  fVar10 = (((fRam0047ad28 * fVar18 + fRam0047acd8) * fVar18 + fRam0047acb8) * fVar18 + fRam0047ac98
           ) * fVar10;
  fVar12 = (((fRam0047ad2c * fVar20 + fRam0047acdc) * fVar20 + fRam0047acbc) * fVar20 + fRam0047ac9c
           ) * fVar12;
  fVar7 = (((simd_cos_coeff_c4 * fVar14 + simd_cos_coeff_c3) * fVar14 + simd_cos_coeff_c2) * fVar14 +
          simd_cos_coeff_c1) * fVar14 + simd_cos_coeff_c0;
  fVar11 = (((fRam0047ad14 * fVar16 + fRam0047acc4) * fVar16 + fRam0047aca4) * fVar16 + fRam0047ac84
           ) * fVar16 + fRam0047ac74;
  fVar14 = (((fRam0047ad18 * fVar18 + fRam0047acc8) * fVar18 + fRam0047aca8) * fVar18 + fRam0047ac88
           ) * fVar18 + fRam0047ac78;
  fVar15 = (((fRam0047ad1c * fVar20 + fRam0047accc) * fVar20 + fRam0047acac) * fVar20 + fRam0047ac8c
           ) * fVar20 + fRam0047ac7c;
  *param_2 = (~uVar5 & (uint)fVar6 | uVar5 & (uint)fVar7) ^
             (uVar25 - uVar9 & simd_mantissa_mask) << 0x1e ^ *param_1 & simd_sincos_sign_mask;
  param_2[1] = (~uVar13 & (uint)fVar8 | uVar13 & (uint)fVar11) ^ uVar1 << 0x1e ^ uVar22;
  param_2[2] = (~uVar17 & (uint)fVar10 | uVar17 & (uint)fVar14) ^ uVar2 << 0x1e ^ uVar23;
  param_2[3] = (~uVar21 & (uint)fVar12 | uVar21 & (uint)fVar15) ^ uVar3 << 0x1e ^ uVar24;
  *param_3 = (uVar5 & (uint)fVar6 | ~uVar5 & (uint)fVar7) ^ uVar4 << 0x1e;
  param_3[1] = (uVar13 & (uint)fVar8 | ~uVar13 & (uint)fVar11) ^ uVar26 << 0x1e;
  param_3[2] = (uVar17 & (uint)fVar10 | ~uVar17 & (uint)fVar14) ^ uVar27 << 0x1e;
  param_3[3] = (uVar21 & (uint)fVar12 | ~uVar21 & (uint)fVar15) ^ uVar28 << 0x1e;
  return;
}



/* simd_noop @ 0045fdc0 */

void simd_noop(void)

{
  return;
}



/* simd_sincos_packed @ 0045feb0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl simd_sincos_packed(uint *param_1,uint *param_2,uint *param_3)

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
  
  fVar16 = (float)(*param_1 & simd_sincos2_coeff_b9);
  fVar17 = (float)(param_1[1] & uRam0047afc4);
  fVar25 = (float)(param_1[2] & uRam0047afc8);
  fVar26 = (float)(param_1[3] & uRam0047afcc);
  uVar13 = param_1[1] & uRam0047afb4;
  uVar14 = param_1[2] & uRam0047afb8;
  uVar15 = param_1[3] & uRam0047afbc;
  fVar1 = fVar16 * simd_sincos2_coeff_b7 + simd_sincos2_coeff_b2;
  fVar4 = fVar17 * fRam0047afa4 + fRam0047af54;
  fVar7 = fVar25 * fRam0047afa8 + fRam0047af58;
  fVar10 = fVar26 * fRam0047afac + fRam0047af5c;
  fVar2 = fVar1 - simd_sincos2_coeff_b2;
  fVar5 = fVar4 - fRam0047af54;
  fVar8 = fVar7 - fRam0047af58;
  fVar11 = fVar10 - fRam0047af5c;
  fVar16 = (((fVar16 - simd_sincos2_coeff_b6 * fVar2) - simd_sincos2_coeff_b5 * fVar2) - simd_sincos2_coeff_b4 * fVar2) -
           simd_sincos2_coeff_b3 * fVar2;
  fVar2 = (((fVar17 - fRam0047af94 * fVar5) - fRam0047af84 * fVar5) - fRam0047af74 * fVar5) -
          fRam0047af64 * fVar5;
  fVar17 = (((fVar25 - fRam0047af98 * fVar8) - fRam0047af88 * fVar8) - fRam0047af78 * fVar8) -
           fRam0047af68 * fVar8;
  fVar5 = (((fVar26 - fRam0047af9c * fVar11) - fRam0047af8c * fVar11) - fRam0047af7c * fVar11) -
          fRam0047af6c * fVar11;
  fVar25 = fVar16 * fVar16;
  fVar8 = fVar2 * fVar2;
  fVar26 = fVar17 * fVar17;
  fVar11 = fVar5 * fVar5;
  uVar18 = (uint)fVar1 & simd_sincos2_coeff_a9;
  uVar19 = (uint)fVar4 & uRam0047af24;
  uVar21 = (uint)fVar7 & uRam0047af28;
  uVar23 = (uint)fVar10 & uRam0047af2c;
  uVar3 = uVar18 & simd_sincos2_coeff_a8;
  uVar6 = uVar19 & uRam0047af14;
  uVar9 = uVar21 & uRam0047af18;
  uVar12 = uVar23 & uRam0047af1c;
  uVar20 = uVar19 - uVar6 & uRam0047af04;
  uVar22 = uVar21 - uVar9 & uRam0047af08;
  uVar24 = uVar23 - uVar12 & uRam0047af0c;
  uVar27 = uVar18 + uVar3 & simd_sincos2_coeff_a7;
  uVar28 = uVar19 + uVar6 & uRam0047af04;
  uVar21 = uVar21 + uVar9 & uRam0047af08;
  uVar23 = uVar23 + uVar12 & uRam0047af0c;
  uVar19 = -(uint)((float)(uVar3 << 0x1e) != 0.0);
  uVar6 = -(uint)((float)(uVar6 << 0x1e) != 0.0);
  uVar9 = -(uint)((float)(uVar9 << 0x1e) != 0.0);
  uVar12 = -(uint)((float)(uVar12 << 0x1e) != 0.0);
  fVar16 = (((simd_sincos2_coeff_b1 * fVar25 + simd_sincos2_coeff_a6) * fVar25 + simd_sincos2_coeff_a4) * fVar25 +
           simd_sincos2_coeff_a2) * fVar16;
  fVar2 = (((fRam0047af44 * fVar8 + fRam0047aef4) * fVar8 + fRam0047aed4) * fVar8 + fRam0047aeb4) *
          fVar2;
  fVar17 = (((fRam0047af48 * fVar26 + fRam0047aef8) * fVar26 + fRam0047aed8) * fVar26 + fRam0047aeb8
           ) * fVar17;
  fVar5 = (((fRam0047af4c * fVar11 + fRam0047aefc) * fVar11 + fRam0047aedc) * fVar11 + fRam0047aebc)
          * fVar5;
  fVar1 = (((simd_sincos2_coeff_b0 * fVar25 + simd_sincos2_coeff_a5) * fVar25 + simd_sincos2_coeff_a3) * fVar25 +
          simd_sincos2_coeff_a1) * fVar25 + simd_sincos2_coeff_a0;
  fVar4 = (((fRam0047af34 * fVar8 + fRam0047aee4) * fVar8 + fRam0047aec4) * fVar8 + fRam0047aea4) *
          fVar8 + fRam0047ae94;
  fVar25 = (((fRam0047af38 * fVar26 + fRam0047aee8) * fVar26 + fRam0047aec8) * fVar26 + fRam0047aea8
           ) * fVar26 + fRam0047ae98;
  fVar7 = (((fRam0047af3c * fVar11 + fRam0047aeec) * fVar11 + fRam0047aecc) * fVar11 + fRam0047aeac)
          * fVar11 + fRam0047ae9c;
  *param_2 = (~uVar19 & (uint)fVar16 | uVar19 & (uint)fVar1) ^
             (uVar18 - uVar3 & simd_sincos2_coeff_a7) << 0x1e ^ *param_1 & simd_sincos2_coeff_b8;
  param_2[1] = (~uVar6 & (uint)fVar2 | uVar6 & (uint)fVar4) ^ uVar20 << 0x1e ^ uVar13;
  param_2[2] = (~uVar9 & (uint)fVar17 | uVar9 & (uint)fVar25) ^ uVar22 << 0x1e ^ uVar14;
  param_2[3] = (~uVar12 & (uint)fVar5 | uVar12 & (uint)fVar7) ^ uVar24 << 0x1e ^ uVar15;
  *param_3 = (uVar19 & (uint)fVar16 | ~uVar19 & (uint)fVar1) ^ uVar27 << 0x1e;
  param_3[1] = (uVar6 & (uint)fVar2 | ~uVar6 & (uint)fVar4) ^ uVar28 << 0x1e;
  param_3[2] = (uVar9 & (uint)fVar17 | ~uVar9 & (uint)fVar25) ^ uVar21 << 0x1e;
  param_3[3] = (uVar12 & (uint)fVar5 | ~uVar12 & (uint)fVar7) ^ uVar23 << 0x1e;
  return;
}



/* math_atan2_packed @ 004600c0 */

/* packed atan2 approximation; inputs in MM0/MM1 */

ulonglong math_atan2_packed(void)

{
  undefined4 in_EAX;
  undefined4 in_EDX;
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
  
  uVar3 = in_MM1 & simd_abs_mask;
  uVar1 = in_MM0 & simd_abs_mask;
  uVar2 = PackedFloatingMAX(uVar1,uVar3);
  uVar7 = (uint)((int)uVar1 < (int)uVar3) * -0x80000000;
  uVar4 = PackedFloatingMIN(uVar3,uVar1);
  uVar5 = FloatingReciprocalAprox(uVar1,uVar2);
  uVar2 = PackedFloatingReciprocalIter1(uVar2,uVar5);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar5);
  uVar2 = PackedFloatingMUL(uVar2,uVar4);
  uVar4 = PackedFloatingMUL(uVar2,uVar2);
  uVar5 = PackedFloatingADD((ulonglong)DAT_0047b0d0,uVar4);
  uVar6 = PackedFloatingMUL((ulonglong)DAT_0047b0dc,uVar4);
  uVar5 = PackedFloatingMUL(uVar5,uVar4);
  uVar6 = PackedFloatingADD(uVar6,(ulonglong)DAT_0047b0d8);
  uVar5 = PackedFloatingADD(uVar5,(ulonglong)DAT_0047b0cc);
  uVar6 = PackedFloatingMUL(uVar6,uVar4);
  uVar5 = PackedFloatingMUL(uVar5,uVar4);
  uVar6 = PackedFloatingADD(uVar6,(ulonglong)simd_exp_const);
  uVar5 = PackedFloatingADD(uVar5,(ulonglong)DAT_0047b0c8);
  uVar4 = PackedFloatingMUL(uVar4,uVar6);
  uVar4 = PackedFloatingMUL(uVar4,uVar2);
  uVar6 = FloatingReciprocalAprox((ulonglong)simd_exp_const,uVar5);
  uVar8 = ((uint)((simd_sign_mask & in_MM0) >> 1) | simd_sign_mask & (uint)in_MM1) << 1;
  uVar5 = PackedFloatingReciprocalIter1(uVar5,uVar6);
  uVar5 = PackedFloatingReciprocalIter2(uVar5,uVar6);
  uVar4 = PackedFloatingMUL(uVar4,uVar5);
  uVar1 = PackedFloatingADD(uVar4,uVar2);
  uVar2 = PackedFloatingSUB(~(ulonglong)(uint)((int)uVar7 >> 0x1f) &
                            (ulonglong)(uVar8 ^ simd_special_const),(ulonglong)simd_special_const);
  PackedFloatingADD(uVar1 | uVar8 ^ uVar7,uVar2);
  return CONCAT44(in_EDX,in_EAX);
}



/* math_acos_packed @ 004601c0 */

/* packed acos approximation; input in MM0 */

ulonglong math_acos_packed(void)

{
  uint uVar1;
  undefined4 in_EAX;
  undefined4 in_EDX;
  ulonglong in_MM0;
  ulonglong uVar2;
  undefined8 uVar3;
  uint uVar4;
  undefined8 uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  ulonglong uVar5;
  
  uVar2 = in_MM0 & simd_abs_mask;
  uVar3 = PackedFloatingMUL(uVar2,(ulonglong)simd_trig_const_a);
  uVar3 = PackedFloatingSUBR(uVar3,(ulonglong)simd_trig_const_a);
  uVar6 = PackedFloatingReciprocalSQRAprox((ulonglong)simd_abs_mask,uVar3);
  uVar7 = PackedFloatingMUL(uVar6,uVar6);
  uVar1 = (uint)((int)uVar2 < DAT_0047b0e0);
  uVar4 = -uVar1;
  uVar5 = (ulonglong)uVar4;
  uVar7 = PackedFloatingReciprocalSQRIter1(uVar7,uVar3);
  uVar6 = PackedFloatingReciprocalIter2(uVar7,uVar6);
  uVar8 = PackedFloatingMUL(uVar6,uVar3);
  uVar2 = ~uVar5 & uVar8 | uVar2 & uVar4;
  uVar3 = PackedFloatingMUL(uVar2,uVar2);
  uVar7 = PackedFloatingMUL((ulonglong)DAT_0047b0e8,uVar3);
  uVar6 = PackedFloatingADD((ulonglong)DAT_0047b0f0,uVar3);
  uVar7 = PackedFloatingADD(uVar7,(ulonglong)DAT_0047b0e4);
  uVar7 = PackedFloatingMUL(uVar7,uVar3);
  uVar3 = PackedFloatingMUL(uVar3,uVar6);
  uVar3 = PackedFloatingADD(uVar3,(ulonglong)DAT_0047b0ec);
  uVar7 = PackedFloatingMUL(uVar7,uVar2);
  uVar6 = FloatingReciprocalAprox(uVar6,uVar3);
  uVar3 = PackedFloatingReciprocalIter1(uVar3,uVar6);
  uVar3 = PackedFloatingReciprocalIter2(uVar3,uVar6);
  uVar3 = PackedFloatingMUL(uVar3,uVar7);
  uVar2 = PackedFloatingADD(uVar2,uVar3);
  uVar3 = PackedFloatingADD(~uVar5 & (ulonglong)simd_special_const ^ simd_sign_mask & in_MM0,
                            (ulonglong)DAT_0047b0f4);
  uVar2 = PackedFloatingADD(uVar2,~uVar5 & uVar2);
  PackedFloatingADD(uVar3,uVar2 | (ulonglong)(uVar1 * -0x80000000) ^ simd_sign_mask & in_MM0);
  return CONCAT44(in_EDX,in_EAX);
}



/* math_sincos_packed @ 004607a0 */

/* packed sin/cos approximation for the angle in MM0 */

ulonglong math_sincos_packed(void)

{
  uint uVar1;
  uint uVar2;
  ulonglong in_MM0;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar1 = (uint)in_MM0;
  uVar2 = uVar1 >> 0x1f;
  uVar1 = uVar1 ^ uVar1 & 0x80000000;
  if ((int)uVar1 < simd_recip_const_a) {
    uVar3 = PackedFloatingMUL(in_MM0 & simd_abs_mask,(ulonglong)simd_recip_const_b);
    uVar4 = PackedFloatingToIntDwordConv(uVar3,uVar3);
    uVar3 = PackedIntToFloatingDwordConv(uVar4,uVar4);
    uVar3 = PackedFloatingMUL(CONCAT44((int)uVar3,(int)uVar3),DAT_0047b060);
    uVar6 = PackedFloatingADD(in_MM0 & simd_abs_mask,uVar3);
    uVar5 = (undefined4)((ulonglong)uVar3 >> 0x20);
    uVar3 = PackedFloatingADD(uVar6,CONCAT44(uVar5,uVar5));
    uVar3 = CONCAT44((int)uVar3,(int)uVar3);
    if ((uVar4 & 1) != 0) {
      uVar3 = PackedFloatingSUBR(uVar3,DAT_0047b070);
    }
    uVar2 = (uVar2 ^ (uint)uVar4 >> 2) << 0x1f;
    uVar6 = PackedFloatingMUL(uVar3,uVar3);
    uVar8 = PackedFloatingMUL(DAT_0047b068,uVar6);
    uVar7 = PackedFloatingMUL(DAT_0047b078,uVar6);
    uVar9 = PackedFloatingADD(uVar8,simd_float_const_table);
    uVar8 = PackedFloatingMUL(simd_trig_const_c,uVar6);
    uVar7 = PackedFloatingMUL(uVar9,uVar7);
    uVar9 = PackedFloatingADD(uVar7,simd_float_const_table);
    uVar7 = PackedFloatingMUL(simd_trig_const_b,uVar6);
    uVar6 = PackedFloatingMUL(uVar8,uVar9);
    uVar6 = PackedFloatingADD(uVar6,simd_float_const_table);
    uVar6 = PackedFloatingMUL(uVar6,CONCAT44((int)simd_float_const_table,(int)uVar7));
    uVar6 = PackedFloatingADD(uVar6,simd_float_const_table >> 0x20);
    PackedFloatingMUL(uVar6,CONCAT44((int)uVar3,(int)simd_float_const_table));
  }
  return CONCAT44(uVar2,uVar1);
}



/* math_sin_packed @ 004608c0 */

/* packed sin approximation; input in MM0 */

ulonglong math_sin_packed(void)

{
  uint uVar1;
  uint uVar2;
  ulonglong in_MM0;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar1 = (uint)in_MM0;
  uVar2 = uVar1 >> 0x1f;
  uVar1 = uVar1 ^ uVar1 & 0x80000000;
  if ((int)uVar1 < simd_recip_const_a) {
    uVar3 = PackedFloatingMUL(in_MM0 & simd_abs_mask,(ulonglong)simd_recip_const_b);
    uVar4 = PackedFloatingToIntDwordConv(uVar3,uVar3);
    uVar3 = PackedIntToFloatingDwordConv(uVar4,uVar4);
    uVar3 = PackedFloatingMUL(CONCAT44((int)uVar3,(int)uVar3),DAT_0047b060);
    uVar6 = PackedFloatingADD(in_MM0 & simd_abs_mask,uVar3);
    uVar5 = (undefined4)((ulonglong)uVar3 >> 0x20);
    uVar3 = PackedFloatingADD(uVar6,CONCAT44(uVar5,uVar5));
    uVar3 = CONCAT44((int)uVar3,(int)uVar3);
    if ((uVar4 & 1) != 0) {
      uVar3 = PackedFloatingSUBR(uVar3,DAT_0047b070);
    }
    uVar2 = (uVar2 ^ (uint)uVar4 >> 2) << 0x1f;
    uVar6 = PackedFloatingMUL(uVar3,uVar3);
    uVar8 = PackedFloatingMUL(DAT_0047b068,uVar6);
    uVar7 = PackedFloatingMUL(DAT_0047b078,uVar6);
    uVar9 = PackedFloatingADD(uVar8,simd_float_const_table);
    uVar8 = PackedFloatingMUL(simd_trig_const_c,uVar6);
    uVar7 = PackedFloatingMUL(uVar9,uVar7);
    uVar9 = PackedFloatingADD(uVar7,simd_float_const_table);
    uVar7 = PackedFloatingMUL(simd_trig_const_b,uVar6);
    uVar6 = PackedFloatingMUL(uVar8,uVar9);
    uVar6 = PackedFloatingADD(uVar6,simd_float_const_table);
    uVar6 = PackedFloatingMUL(uVar6,CONCAT44((int)simd_float_const_table,(int)uVar7));
    uVar6 = PackedFloatingADD(uVar6,simd_float_const_table >> 0x20);
    PackedFloatingMUL(uVar6,CONCAT44((int)uVar3,(int)simd_float_const_table));
  }
  return CONCAT44(uVar2,uVar1);
}



/* FUN_00460cb8 @ 00460cb8 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_460cb8() */

int FUN_00460cb8(void)

{
  int iVar1;
  void *extraout_ECX;
  
  FUN_00460cd0();
  _DAT_004d9964 = FUN_00463737();
  iVar1 = FUN_004636e7(extraout_ECX);
  return iVar1;
}



/* FUN_00460ccf @ 00460ccf */

void FUN_00460ccf(void)

{
  return;
}



/* FUN_00460cd0 @ 00460cd0 */

void FUN_00460cd0(void)

{
  PTR_FUN_0047b1ac = &LAB_004637ba;
  PTR_FUN_0047b1a8 = __cfltcvt;
  PTR_FUN_0047b1b0 = __fassign;
  PTR_FUN_0047b1b4 = FUN_00463760;
  PTR_FUN_0047b1b8 = &LAB_00463808;
  PTR_FUN_0047b1bc = __cfltcvt;
  return;
}



/* __fclose_lk @ 00460e8e */

/* Library Function - Single Match
    __fclose_lk
   
   Library: Visual Studio 2003 Release */

undefined4 __cdecl __fclose_lk(FILE *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((param_1->_flag & 0x83) != 0) {
    uVar2 = crt_flushbuf((int *)param_1);
    __freebuf(param_1);
    iVar1 = crt_close(param_1->_file);
    if (iVar1 < 0) {
      uVar2 = 0xffffffff;
    }
    else if (param_1->_tmpfname != (char *)0x0) {
      crt_free_base(param_1->_tmpfname);
      param_1->_tmpfname = (char *)0x0;
    }
  }
  param_1->_flag = 0;
  return uVar2;
}



/* _strchr @ 00460ef0 */

/* Library Function - Single Match
    _strchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strchr(char *_Str,int _Val)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)_Str & 3) != 0) {
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    _Str = (char *)((int)_Str + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)_Str;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)_Val,(char)_Val),CONCAT11((char)_Val,(char)_Val));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((int)_Str + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      _Str = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 3);
    }
    _Str = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}


