/* grim_skin_alloc_buffer @ 1001504e */

uint * __cdecl grim_skin_alloc_buffer(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint unaff_EBX;
  uint *puVar7;
  uint unaff_EDI;
  undefined2 in_FPUControlWord;
  double dVar8;
  uint local_8;
  
  puVar4 = operator_new(unaff_EBX << 4);
  if (puVar4 != (uint *)0x0) {
    fVar1 = (float)(int)unaff_EDI;
    if ((int)unaff_EDI < 0) {
      fVar1 = fVar1 + 4.2949673e+09;
    }
    fVar2 = (float)(int)unaff_EBX;
    if ((int)unaff_EBX < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    local_8 = CONCAT22(local_8._2_2_,in_FPUControlWord);
    DAT_1005db68 = local_8;
    local_8 = 0;
    puVar7 = puVar4;
    if (unaff_EBX != 0) {
      do {
        fVar3 = (float)(int)local_8;
        if ((int)local_8 < 0) {
          fVar3 = fVar3 + 4.2949673e+09;
        }
        fVar3 = fVar3 * (fVar1 / fVar2) - 0.5;
        dVar8 = floor((double)fVar3);
        uVar5 = (uint)ROUND((float)dVar8);
        uVar6 = uVar5 + 1;
        if ((int)uVar5 < 0) {
          uVar5 = -(uint)(param_1 != 0) & unaff_EDI - 1;
        }
        if (unaff_EDI <= uVar6) {
          uVar6 = ~-(uint)(param_1 != 0) & unaff_EDI - 1;
        }
        *puVar7 = uVar5;
        puVar7[2] = uVar6;
        local_8 = local_8 + 1;
        fVar3 = 1.0 - (fVar3 - (float)dVar8);
        puVar7[1] = (uint)fVar3;
        puVar7[3] = (uint)(1.0 - fVar3);
        puVar7 = puVar7 + 4;
      } while (local_8 < unaff_EBX);
    }
  }
  return puVar4;
}



/* grim_skin_blend_2weights @ 1001514e */

/* [binja] int32_t __fastcall sub_1001514e(int32_t* arg1) */

int grim_skin_blend_2weights(int *arg1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  undefined4 *puVar13;
  int iVar14;
  uint *puVar15;
  void *pvVar16;
  int *piVar17;
  int *extraout_ECX;
  float *pfVar18;
  int iVar19;
  int unaff_EBP;
  int *piVar20;
  
  seh_prolog();
  *(undefined4 *)(unaff_EBP + -0x14) = 0;
  *(undefined4 *)(unaff_EBP + -0x1c) = 0;
  uVar9 = extraout_ECX[2];
  *(int **)(unaff_EBP + -0x40) = extraout_ECX;
  if ((char)uVar9 != '\x03') {
    iVar14 = -0x7fffbffb;
    goto LAB_10015527;
  }
  *(uint *)(unaff_EBP + -0x10) = ~(uVar9 >> 0x11) & 1;
  puVar15 = grim_skin_alloc_buffer(~(uVar9 >> 0x10) & 1);
  *(uint **)(unaff_EBP + -0x30) = puVar15;
  puVar15 = grim_skin_alloc_buffer(*(int *)(unaff_EBP + -0x10));
  *(uint **)(unaff_EBP + -0x10) = puVar15;
  if ((*(int *)(unaff_EBP + -0x30) == 0) || (puVar15 == (uint *)0x0)) {
LAB_100154fb:
    iVar14 = -0x7ff8fff2;
  }
  else {
    iVar14 = *(int *)(extraout_ECX[1] + 0x1058);
    pvVar16 = operator_new(iVar14 << 4);
    *(void **)(unaff_EBP + -0x14) = pvVar16;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar16 == (void *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x20) = 0;
      iVar14 = *(int *)(unaff_EBP + -0x20);
    }
    else {
      _vector_constructor_iterator_(pvVar16,0x10,iVar14,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      iVar14 = *(int *)(unaff_EBP + -0x14);
      *(int *)(unaff_EBP + -0x20) = iVar14;
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(unaff_EBP + -0x14) = iVar14;
    if (iVar14 == 0) goto LAB_100154fb;
    iVar14 = *(int *)(*extraout_ECX + 0x1058);
    pvVar16 = operator_new(iVar14 << 5);
    *(void **)(unaff_EBP + -0x1c) = pvVar16;
    *(undefined4 *)(unaff_EBP + -4) = 1;
    if (pvVar16 == (void *)0x0) {
      iVar14 = 0;
    }
    else {
      _vector_constructor_iterator_
                (pvVar16,0x10,iVar14 << 1,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      iVar14 = *(int *)(unaff_EBP + -0x1c);
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(unaff_EBP + -0x1c) = iVar14;
    if (iVar14 == 0) goto LAB_100154fb;
    iVar10 = *(int *)(*extraout_ECX + 0x1058);
    *(undefined4 *)(unaff_EBP + -0x28) = 0;
    *(undefined4 *)(unaff_EBP + -0x24) = 0xffffffff;
    *(undefined4 *)(unaff_EBP + -0x18) = 0xffffffff;
    *(int *)(unaff_EBP + -0x2c) = iVar14;
    if (*(int *)(extraout_ECX[1] + 0x105c) != 0) {
      piVar20 = (int *)(*(int *)(unaff_EBP + -0x10) + 8);
      *(int **)(unaff_EBP + -0x38) = piVar20;
      iVar14 = iVar10 * 0x10 + iVar14;
      piVar17 = extraout_ECX;
      do {
        iVar10 = piVar20[-2];
        *(undefined4 *)(unaff_EBP + -0x34) = 0;
        iVar19 = iVar14;
        if (iVar10 != *(int *)(unaff_EBP + -0x24)) {
          iVar11 = *(int *)(unaff_EBP + -0x18);
          if (iVar10 == iVar11) {
            iVar19 = *(int *)(unaff_EBP + -0x2c);
            *(undefined4 *)(unaff_EBP + -0x18) = 0xffffffff;
            *(int *)(unaff_EBP + -0x2c) = iVar14;
            *(int *)(unaff_EBP + -0x24) = iVar11;
          }
          else {
            piVar12 = (int *)*piVar17;
            *(int *)(unaff_EBP + -0x24) = iVar10;
            (**(code **)(*piVar12 + 4))
                      (*(undefined4 *)(unaff_EBP + -0x24),0,*(undefined4 *)(unaff_EBP + -0x2c));
          }
        }
        iVar14 = *piVar20;
        if (iVar14 != *(int *)(unaff_EBP + -0x18)) {
          iVar10 = *(int *)*piVar17;
          *(int *)(unaff_EBP + -0x18) = iVar14;
          (**(code **)(iVar10 + 4))(iVar14,0,iVar19);
        }
        if (*(int *)(piVar17[1] + 0x1058) != 0) {
          piVar17 = (int *)(*(int *)(unaff_EBP + -0x30) + 8);
          *(undefined4 *)(unaff_EBP + -0x3c) = *(undefined4 *)(unaff_EBP + -0x20);
          do {
            iVar14 = *piVar17;
            fVar2 = (float)piVar17[1];
            pfVar1 = (float *)(iVar14 * 0x10 + iVar19);
            *(float *)(unaff_EBP + -0x50) = fVar2 * *pfVar1;
            *(float *)(unaff_EBP + -0x4c) = fVar2 * pfVar1[1];
            *(float *)(unaff_EBP + -0x48) = fVar2 * pfVar1[2];
            fVar3 = pfVar1[3];
            iVar10 = piVar17[-2];
            fVar4 = (float)piVar17[-1];
            pfVar1 = (float *)(iVar10 * 0x10 + iVar19);
            fVar5 = *pfVar1;
            *(float *)(unaff_EBP + -0x9c) = fVar4 * pfVar1[1];
            *(float *)(unaff_EBP + -0x98) = fVar4 * pfVar1[2];
            pfVar18 = (float *)(iVar14 * 0x10 + *(int *)(unaff_EBP + -0x2c));
            *(float *)(unaff_EBP + -0x94) = fVar4 * pfVar1[3];
            *(float *)(unaff_EBP + -0x80) = fVar4 * fVar5 + *(float *)(unaff_EBP + -0x50);
            *(float *)(unaff_EBP + -0x7c) =
                 *(float *)(unaff_EBP + -0x9c) + *(float *)(unaff_EBP + -0x4c);
            *(float *)(unaff_EBP + -0x78) =
                 *(float *)(unaff_EBP + -0x98) + *(float *)(unaff_EBP + -0x48);
            fVar4 = (float)piVar20[1];
            *(float *)(unaff_EBP + -0xb0) = *(float *)(unaff_EBP + -0x80) * fVar4;
            *(float *)(unaff_EBP + -0xac) = *(float *)(unaff_EBP + -0x7c) * fVar4;
            *(float *)(unaff_EBP + -0xa8) = *(float *)(unaff_EBP + -0x78) * fVar4;
            fVar5 = (float)piVar17[1];
            *(float *)(unaff_EBP + -0xc0) = fVar5 * *pfVar18;
            *(float *)(unaff_EBP + -0xbc) = fVar5 * pfVar18[1];
            *(float *)(unaff_EBP + -0xb8) = fVar5 * pfVar18[2];
            fVar6 = pfVar18[3];
            pfVar1 = (float *)(iVar10 * 0x10 + *(int *)(unaff_EBP + -0x2c));
            fVar7 = (float)piVar17[-1];
            piVar17 = piVar17 + 4;
            fVar8 = *pfVar1;
            *(int *)(unaff_EBP + -0x34) = *(int *)(unaff_EBP + -0x34) + 1;
            uVar9 = *(uint *)(unaff_EBP + -0x34);
            *(float *)(unaff_EBP + -0x5c) = fVar7 * pfVar1[1];
            *(float *)(unaff_EBP + -0x58) = fVar7 * pfVar1[2];
            iVar14 = *(int *)(unaff_EBP + -0x40);
            *(float *)(unaff_EBP + -0x54) = fVar7 * pfVar1[3];
            *(float *)(unaff_EBP + -0x70) = fVar7 * fVar8 + *(float *)(unaff_EBP + -0xc0);
            *(float *)(unaff_EBP + -0x6c) =
                 *(float *)(unaff_EBP + -0x5c) + *(float *)(unaff_EBP + -0xbc);
            *(float *)(unaff_EBP + -0x68) =
                 *(float *)(unaff_EBP + -0x58) + *(float *)(unaff_EBP + -0xb8);
            fVar7 = (float)piVar20[-1];
            puVar13 = *(undefined4 **)(unaff_EBP + -0x3c);
            *(int *)(unaff_EBP + -0x3c) = *(int *)(unaff_EBP + -0x3c) + 0x10;
            *(float *)(unaff_EBP + -0x90) = *(float *)(unaff_EBP + -0x70) * fVar7;
            *(float *)(unaff_EBP + -0x8c) = *(float *)(unaff_EBP + -0x6c) * fVar7;
            *(float *)(unaff_EBP + -0x88) = *(float *)(unaff_EBP + -0x68) * fVar7;
            *(float *)(unaff_EBP + -0xd0) =
                 *(float *)(unaff_EBP + -0x90) + *(float *)(unaff_EBP + -0xb0);
            *(float *)(unaff_EBP + -0xcc) =
                 *(float *)(unaff_EBP + -0x8c) + *(float *)(unaff_EBP + -0xac);
            *(float *)(unaff_EBP + -200) =
                 *(float *)(unaff_EBP + -0x88) + *(float *)(unaff_EBP + -0xa8);
            *(float *)(unaff_EBP + -0xc4) =
                 (*(float *)(unaff_EBP + -0x54) + fVar5 * fVar6) * fVar7 +
                 (*(float *)(unaff_EBP + -0x94) + fVar2 * fVar3) * fVar4;
            *puVar13 = *(undefined4 *)(unaff_EBP + -0xd0);
            puVar13[1] = *(undefined4 *)(unaff_EBP + -0xcc);
            puVar13[2] = *(undefined4 *)(unaff_EBP + -200);
            puVar13[3] = *(undefined4 *)(unaff_EBP + -0xc4);
            piVar20 = *(int **)(unaff_EBP + -0x38);
          } while (uVar9 < *(uint *)(*(int *)(iVar14 + 4) + 0x1058));
          piVar17 = *(int **)(unaff_EBP + -0x40);
        }
        (**(code **)(*(int *)piVar17[1] + 8))
                  (*(undefined4 *)(unaff_EBP + -0x28),0,*(undefined4 *)(unaff_EBP + -0x20));
        iVar14 = piVar17[1];
        piVar20 = piVar20 + 4;
        *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x28) + 1;
        uVar9 = *(uint *)(iVar14 + 0x105c);
        *(int **)(unaff_EBP + -0x38) = piVar20;
        iVar14 = iVar19;
      } while (*(uint *)(unaff_EBP + -0x28) < uVar9);
    }
    iVar14 = 0;
  }
  operator_delete(*(void **)(unaff_EBP + -0x30));
  operator_delete(*(void **)(unaff_EBP + -0x10));
  operator_delete(*(void **)(unaff_EBP + -0x14));
  operator_delete(*(void **)(unaff_EBP + -0x1c));
LAB_10015527:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar14;
}



/* grim_skin_blend_3weights @ 10015534 */

/* [binja] int32_t __fastcall sub_10015534(int32_t* arg1) */

int grim_skin_blend_3weights(int *arg1)

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
  uint uVar15;
  int iVar16;
  undefined4 uVar17;
  int *piVar18;
  undefined4 *puVar19;
  int iVar20;
  uint *puVar21;
  void *pvVar22;
  int iVar23;
  int *piVar24;
  int *extraout_ECX;
  int iVar25;
  int *piVar26;
  int unaff_EBP;
  float *pfVar27;
  float *pfVar28;
  int iVar29;
  
  seh_prolog();
  *(undefined4 *)(unaff_EBP + -0x44) = 0;
  *(undefined4 *)(unaff_EBP + -0x30) = 0;
  uVar15 = extraout_ECX[2];
  *(int **)(unaff_EBP + -0x54) = extraout_ECX;
  if ((char)uVar15 != '\x03') {
    iVar20 = -0x7fffbffb;
    goto LAB_10015c58;
  }
  *(uint *)(unaff_EBP + -0x20) = ~(uVar15 >> 0x12) & 1;
  *(uint *)(unaff_EBP + -0x3c) = ~(uVar15 >> 0x11) & 1;
  puVar21 = grim_skin_alloc_buffer(~(uVar15 >> 0x10) & 1);
  *(uint **)(unaff_EBP + -0x48) = puVar21;
  puVar21 = grim_skin_alloc_buffer(*(int *)(unaff_EBP + -0x3c));
  *(uint **)(unaff_EBP + -0x4c) = puVar21;
  puVar21 = grim_skin_alloc_buffer(*(int *)(unaff_EBP + -0x20));
  *(uint **)(unaff_EBP + -0x3c) = puVar21;
  if (((*(int *)(unaff_EBP + -0x48) == 0) || (*(int *)(unaff_EBP + -0x4c) == 0)) ||
     (puVar21 == (uint *)0x0)) {
LAB_10015c24:
    iVar20 = -0x7ff8fff2;
  }
  else {
    iVar20 = *(int *)(extraout_ECX[1] + 0x1058);
    pvVar22 = operator_new(iVar20 << 4);
    *(void **)(unaff_EBP + -0x44) = pvVar22;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar22 == (void *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x34) = 0;
      iVar20 = *(int *)(unaff_EBP + -0x34);
    }
    else {
      _vector_constructor_iterator_(pvVar22,0x10,iVar20,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      iVar20 = *(int *)(unaff_EBP + -0x44);
      *(int *)(unaff_EBP + -0x34) = iVar20;
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(unaff_EBP + -0x44) = iVar20;
    if (iVar20 == 0) goto LAB_10015c24;
    iVar20 = *(int *)(*extraout_ECX + 0x1058);
    pvVar22 = operator_new(iVar20 << 6);
    *(void **)(unaff_EBP + -0x30) = pvVar22;
    *(undefined4 *)(unaff_EBP + -4) = 1;
    if (pvVar22 == (void *)0x0) {
      iVar20 = 0;
    }
    else {
      _vector_constructor_iterator_
                (pvVar22,0x10,iVar20 << 2,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      iVar20 = *(int *)(unaff_EBP + -0x30);
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(unaff_EBP + -0x30) = iVar20;
    if (iVar20 == 0) goto LAB_10015c24;
    iVar25 = *(int *)(*extraout_ECX + 0x1058);
    *(undefined4 *)(unaff_EBP + -0x38) = 0;
    *(int *)(unaff_EBP + -0x1c) = iVar25 * 0x10 + iVar20;
    iVar29 = iVar25 * 0x30 + iVar20;
    *(int *)(unaff_EBP + -0x28) = iVar20;
    iVar23 = extraout_ECX[1];
    iVar16 = *(int *)(iVar23 + 0x1060);
    *(int *)(unaff_EBP + -0x40) = iVar25 * 0x20 + iVar20;
    *(int *)(unaff_EBP + -0x2c) = iVar29;
    if (iVar16 != 0) {
      *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x3c) + 8;
      piVar24 = extraout_ECX;
      do {
        *(undefined4 *)(unaff_EBP + -0x24) = 0;
        *(undefined4 *)(unaff_EBP + -0x18) = 0xffffffff;
        *(undefined4 *)(unaff_EBP + -0x14) = 0xffffffff;
        if (*(int *)(iVar23 + 0x105c) != 0) {
          piVar26 = (int *)(*(int *)(unaff_EBP + -0x4c) + 8);
          do {
            iVar20 = piVar26[-2];
            *(undefined4 *)(unaff_EBP + -0x20) = 0;
            if (iVar20 != *(int *)(unaff_EBP + -0x18)) {
              iVar25 = *(int *)(unaff_EBP + -0x14);
              if (iVar20 == iVar25) {
                *(undefined4 *)(unaff_EBP + -0x14) = 0xffffffff;
                *(int *)(unaff_EBP + -0x18) = iVar25;
                uVar17 = *(undefined4 *)(unaff_EBP + -0x1c);
                *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(unaff_EBP + -0x28);
                iVar20 = *(int *)(unaff_EBP + -0x40);
                *(int *)(unaff_EBP + -0x40) = iVar29;
                *(undefined4 *)(unaff_EBP + -0x28) = uVar17;
                *(int *)(unaff_EBP + -0x2c) = iVar20;
                iVar29 = iVar20;
              }
              else {
                uVar17 = *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + -8);
                piVar18 = (int *)*piVar24;
                *(int *)(unaff_EBP + -0x18) = iVar20;
                (**(code **)(*piVar18 + 4))
                          (*(undefined4 *)(unaff_EBP + -0x18),uVar17,
                           *(undefined4 *)(unaff_EBP + -0x28));
                (**(code **)(*(int *)*piVar24 + 4))
                          (*(undefined4 *)(unaff_EBP + -0x18),**(undefined4 **)(unaff_EBP + -0x10),
                           *(undefined4 *)(unaff_EBP + -0x40));
              }
            }
            if (*piVar26 != *(int *)(unaff_EBP + -0x14)) {
              uVar17 = *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + -8);
              piVar18 = (int *)*piVar24;
              *(int *)(unaff_EBP + -0x14) = *piVar26;
              (**(code **)(*piVar18 + 4))
                        (*(undefined4 *)(unaff_EBP + -0x14),uVar17,
                         *(undefined4 *)(unaff_EBP + -0x1c));
              (**(code **)(*(int *)*piVar24 + 4))
                        (*(undefined4 *)(unaff_EBP + -0x14),**(undefined4 **)(unaff_EBP + -0x10),
                         iVar29);
            }
            if (*(int *)(piVar24[1] + 0x1058) != 0) {
              piVar24 = (int *)(*(int *)(unaff_EBP + -0x48) + 8);
              *(undefined4 *)(unaff_EBP + -0x50) = *(undefined4 *)(unaff_EBP + -0x34);
              do {
                fVar1 = (float)piVar24[1];
                iVar20 = *piVar24 * 0x10;
                pfVar27 = (float *)(iVar20 + iVar29);
                *(float *)(unaff_EBP + -0x114) = fVar1 * *pfVar27;
                *(float *)(unaff_EBP + -0x110) = fVar1 * pfVar27[1];
                *(float *)(unaff_EBP + -0x10c) = fVar1 * pfVar27[2];
                fVar2 = pfVar27[3];
                fVar3 = (float)piVar24[-1];
                iVar25 = piVar24[-2] * 0x10;
                pfVar27 = (float *)(iVar25 + iVar29);
                fVar4 = *pfVar27;
                *(float *)(unaff_EBP + -0x60) = fVar3 * pfVar27[1];
                *(float *)(unaff_EBP + -0x5c) = fVar3 * pfVar27[2];
                pfVar28 = (float *)(iVar20 + *(int *)(unaff_EBP + -0x40));
                *(float *)(unaff_EBP + -0x58) = fVar3 * pfVar27[3];
                *(float *)(unaff_EBP + -0x94) = fVar3 * fVar4 + *(float *)(unaff_EBP + -0x114);
                *(float *)(unaff_EBP + -0x90) =
                     *(float *)(unaff_EBP + -0x60) + *(float *)(unaff_EBP + -0x110);
                *(float *)(unaff_EBP + -0x8c) =
                     *(float *)(unaff_EBP + -0x5c) + *(float *)(unaff_EBP + -0x10c);
                fVar3 = (float)piVar26[1];
                *(float *)(unaff_EBP + -0x174) = *(float *)(unaff_EBP + -0x94) * fVar3;
                *(float *)(unaff_EBP + -0x170) = *(float *)(unaff_EBP + -0x90) * fVar3;
                *(float *)(unaff_EBP + -0x16c) = *(float *)(unaff_EBP + -0x8c) * fVar3;
                fVar4 = (float)piVar24[1];
                *(float *)(unaff_EBP + -0x194) = fVar4 * *pfVar28;
                *(float *)(unaff_EBP + -400) = fVar4 * pfVar28[1];
                *(float *)(unaff_EBP + -0x18c) = fVar4 * pfVar28[2];
                fVar5 = pfVar28[3];
                pfVar27 = (float *)(iVar25 + *(int *)(unaff_EBP + -0x40));
                fVar6 = (float)piVar24[-1];
                fVar7 = *pfVar27;
                *(float *)(unaff_EBP + -0xb0) = fVar6 * pfVar27[1];
                *(float *)(unaff_EBP + -0xac) = fVar6 * pfVar27[2];
                *(float *)(unaff_EBP + -0xa8) = fVar6 * pfVar27[3];
                *(float *)(unaff_EBP + -0x134) = fVar6 * fVar7 + *(float *)(unaff_EBP + -0x194);
                *(float *)(unaff_EBP + -0x130) =
                     *(float *)(unaff_EBP + -0xb0) + *(float *)(unaff_EBP + -400);
                *(float *)(unaff_EBP + -300) =
                     *(float *)(unaff_EBP + -0xac) + *(float *)(unaff_EBP + -0x18c);
                fVar6 = (float)piVar26[-1];
                *(float *)(unaff_EBP + -0xd4) = *(float *)(unaff_EBP + -0x134) * fVar6;
                *(float *)(unaff_EBP + -0xd0) = *(float *)(unaff_EBP + -0x130) * fVar6;
                *(float *)(unaff_EBP + -0xcc) = *(float *)(unaff_EBP + -300) * fVar6;
                *(float *)(unaff_EBP + -0xf4) =
                     *(float *)(unaff_EBP + -0xd4) + *(float *)(unaff_EBP + -0x174);
                *(float *)(unaff_EBP + -0xf0) =
                     *(float *)(unaff_EBP + -0xd0) + *(float *)(unaff_EBP + -0x170);
                *(float *)(unaff_EBP + -0xec) =
                     *(float *)(unaff_EBP + -0xcc) + *(float *)(unaff_EBP + -0x16c);
                fVar7 = *(float *)(*(int *)(unaff_EBP + -0x10) + 4);
                *(float *)(unaff_EBP + -0x184) = *(float *)(unaff_EBP + -0xf4) * fVar7;
                *(float *)(unaff_EBP + -0x180) = *(float *)(unaff_EBP + -0xf0) * fVar7;
                *(float *)(unaff_EBP + -0x17c) = *(float *)(unaff_EBP + -0xec) * fVar7;
                fVar8 = (float)piVar24[1];
                pfVar27 = (float *)(*(int *)(unaff_EBP + -0x1c) + iVar20);
                *(float *)(unaff_EBP + -0x154) = fVar8 * *pfVar27;
                *(float *)(unaff_EBP + -0x150) = fVar8 * pfVar27[1];
                *(float *)(unaff_EBP + -0x14c) = fVar8 * pfVar27[2];
                fVar9 = pfVar27[3];
                fVar10 = (float)piVar24[-1];
                pfVar28 = (float *)(*(int *)(unaff_EBP + -0x1c) + iVar25);
                fVar11 = *pfVar28;
                *(float *)(unaff_EBP + -0x70) = fVar10 * pfVar28[1];
                *(float *)(unaff_EBP + -0x6c) = fVar10 * pfVar28[2];
                pfVar27 = (float *)(iVar20 + *(int *)(unaff_EBP + -0x28));
                *(float *)(unaff_EBP + -0x68) = fVar10 * pfVar28[3];
                *(float *)(unaff_EBP + -0x84) = fVar10 * fVar11 + *(float *)(unaff_EBP + -0x154);
                *(float *)(unaff_EBP + -0x80) =
                     *(float *)(unaff_EBP + -0x70) + *(float *)(unaff_EBP + -0x150);
                *(float *)(unaff_EBP + -0x7c) =
                     *(float *)(unaff_EBP + -0x6c) + *(float *)(unaff_EBP + -0x14c);
                fVar10 = (float)piVar26[1];
                *(float *)(unaff_EBP + -0x124) = *(float *)(unaff_EBP + -0x84) * fVar10;
                *(float *)(unaff_EBP + -0x120) = *(float *)(unaff_EBP + -0x80) * fVar10;
                *(float *)(unaff_EBP + -0x11c) = *(float *)(unaff_EBP + -0x7c) * fVar10;
                fVar11 = (float)piVar24[1];
                *(float *)(unaff_EBP + -0xa4) = fVar11 * *pfVar27;
                *(float *)(unaff_EBP + -0xa0) = fVar11 * pfVar27[1];
                *(float *)(unaff_EBP + -0x9c) = fVar11 * pfVar27[2];
                fVar12 = pfVar27[3];
                fVar13 = (float)piVar24[-1];
                pfVar27 = (float *)(iVar25 + *(int *)(unaff_EBP + -0x28));
                fVar14 = *pfVar27;
                *(float *)(unaff_EBP + -0xc0) = fVar13 * pfVar27[1];
                *(float *)(unaff_EBP + -0xbc) = fVar13 * pfVar27[2];
                *(float *)(unaff_EBP + -0xb8) = fVar13 * pfVar27[3];
                *(float *)(unaff_EBP + -0xe4) = fVar13 * fVar14 + *(float *)(unaff_EBP + -0xa4);
                *(float *)(unaff_EBP + -0xe0) =
                     *(float *)(unaff_EBP + -0xc0) + *(float *)(unaff_EBP + -0xa0);
                *(float *)(unaff_EBP + -0xdc) =
                     *(float *)(unaff_EBP + -0xbc) + *(float *)(unaff_EBP + -0x9c);
                fVar13 = (float)piVar26[-1];
                *(float *)(unaff_EBP + -0x104) = *(float *)(unaff_EBP + -0xe4) * fVar13;
                *(float *)(unaff_EBP + -0x100) = *(float *)(unaff_EBP + -0xe0) * fVar13;
                *(float *)(unaff_EBP + -0xfc) = *(float *)(unaff_EBP + -0xdc) * fVar13;
                *(float *)(unaff_EBP + -0x144) =
                     *(float *)(unaff_EBP + -0x104) + *(float *)(unaff_EBP + -0x124);
                *(float *)(unaff_EBP + -0x140) =
                     *(float *)(unaff_EBP + -0x100) + *(float *)(unaff_EBP + -0x120);
                *(float *)(unaff_EBP + -0x13c) =
                     *(float *)(unaff_EBP + -0xfc) + *(float *)(unaff_EBP + -0x11c);
                fVar14 = *(float *)(*(int *)(unaff_EBP + -0x10) + -4);
                *(float *)(unaff_EBP + -0x164) = *(float *)(unaff_EBP + -0x144) * fVar14;
                *(float *)(unaff_EBP + -0x160) = *(float *)(unaff_EBP + -0x140) * fVar14;
                *(float *)(unaff_EBP + -0x15c) = *(float *)(unaff_EBP + -0x13c) * fVar14;
                puVar19 = *(undefined4 **)(unaff_EBP + -0x50);
                iVar20 = *(int *)(unaff_EBP + -0x54);
                *(int *)(unaff_EBP + -0x50) = *(int *)(unaff_EBP + -0x50) + 0x10;
                *(float *)(unaff_EBP + -0x1a4) =
                     *(float *)(unaff_EBP + -0x164) + *(float *)(unaff_EBP + -0x184);
                piVar24 = piVar24 + 4;
                *(int *)(unaff_EBP + -0x20) = *(int *)(unaff_EBP + -0x20) + 1;
                uVar15 = *(uint *)(unaff_EBP + -0x20);
                *(float *)(unaff_EBP + -0x1a0) =
                     *(float *)(unaff_EBP + -0x160) + *(float *)(unaff_EBP + -0x180);
                *(float *)(unaff_EBP + -0x19c) =
                     *(float *)(unaff_EBP + -0x15c) + *(float *)(unaff_EBP + -0x17c);
                *(float *)(unaff_EBP + -0x198) =
                     ((*(float *)(unaff_EBP + -0xb8) + fVar11 * fVar12) * fVar13 +
                     (*(float *)(unaff_EBP + -0x68) + fVar8 * fVar9) * fVar10) * fVar14 +
                     ((*(float *)(unaff_EBP + -0xa8) + fVar4 * fVar5) * fVar6 +
                     (*(float *)(unaff_EBP + -0x58) + fVar1 * fVar2) * fVar3) * fVar7;
                *puVar19 = *(undefined4 *)(unaff_EBP + -0x1a4);
                puVar19[1] = *(undefined4 *)(unaff_EBP + -0x1a0);
                puVar19[2] = *(undefined4 *)(unaff_EBP + -0x19c);
                puVar19[3] = *(undefined4 *)(unaff_EBP + -0x198);
                iVar29 = *(int *)(unaff_EBP + -0x2c);
              } while (uVar15 < *(uint *)(*(int *)(iVar20 + 4) + 0x1058));
              piVar24 = *(int **)(unaff_EBP + -0x54);
            }
            (**(code **)(*(int *)piVar24[1] + 8))
                      (*(undefined4 *)(unaff_EBP + -0x24),*(undefined4 *)(unaff_EBP + -0x38),
                       *(undefined4 *)(unaff_EBP + -0x34));
            iVar20 = piVar24[1];
            piVar26 = piVar26 + 4;
            *(int *)(unaff_EBP + -0x24) = *(int *)(unaff_EBP + -0x24) + 1;
          } while (*(uint *)(unaff_EBP + -0x24) < *(uint *)(iVar20 + 0x105c));
        }
        *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 0x10;
        *(int *)(unaff_EBP + -0x38) = *(int *)(unaff_EBP + -0x38) + 1;
        iVar23 = piVar24[1];
      } while (*(uint *)(unaff_EBP + -0x38) < *(uint *)(iVar23 + 0x1060));
    }
    iVar20 = 0;
  }
  operator_delete(*(void **)(unaff_EBP + -0x48));
  operator_delete(*(void **)(unaff_EBP + -0x4c));
  operator_delete(*(void **)(unaff_EBP + -0x3c));
  operator_delete(*(void **)(unaff_EBP + -0x44));
  operator_delete(*(void **)(unaff_EBP + -0x30));
LAB_10015c58:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar20;
}


