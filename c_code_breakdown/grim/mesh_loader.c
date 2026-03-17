/* grim_mesh_data_parse @ 10010aec */

/* [binja] int32_t __thiscall sub_10010aec(int32_t* arg1, HANDLE arg2) */

int __thiscall grim_mesh_data_parse(void *this,int *arg1,HANDLE arg2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  DWORD nNumberOfBytesToWrite;
  int *piVar7;
  uint uVar8;
  LPCVOID lpBuffer;
  undefined1 local_498 [1024];
  int local_98 [3];
  undefined2 local_8c;
  ushort local_8a;
  undefined4 local_88;
  undefined4 local_80;
  undefined4 local_7c;
  undefined2 local_2c;
  int local_2a;
  undefined2 uStack_26;
  undefined2 uStack_24;
  int local_22;
  LPCVOID local_1c;
  undefined1 local_18 [4];
  uint local_14;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined1 local_d;
  DWORD local_c;
  undefined4 local_8;
  
  local_10 = 0;
  local_f = 0;
  local_e = 0;
  local_d = 0;
  local_8 = 0xff000000;
  local_18[0] = 0;
  local_14 = 0xff000000;
  piVar7 = local_98;
  for (iVar4 = 0x1b; uVar1 = local_8, iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar7 = 0;
    piVar7 = piVar7 + 1;
  }
  iVar4 = *(int *)this;
  local_8._3_1_ = SUB41(uVar1,3);
  local_8._0_3_ = CONCAT12(0xaa,CONCAT11(0x55,(undefined1)local_8));
  local_18[1] = 0x24;
  local_18[2] = 0x49;
  local_18[3] = 0x6d;
  local_14 = CONCAT13(local_14._3_1_,0xdbb692);
  local_c = 0;
  if (iVar4 == 0x14) {
    local_98[0] = 0x28;
    local_8a = 0x18;
  }
  else if (iVar4 == 0x1b) {
    local_98[0] = 0x28;
    local_8a = 8;
    local_c = 0x400;
    uVar5 = 0;
    do {
      uVar3 = local_18[uVar5 >> 5];
      iVar4 = uVar5 * 4;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3fd) = 0;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3fe) = uVar3;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3ff) = local_18[uVar5 >> 2 & 7];
      uVar8 = uVar5 + 1;
      *(undefined1 *)(local_98 + (uVar5 - 0x100)) = *(undefined1 *)((int)&local_8 + (uVar5 & 3));
      uVar5 = uVar8;
    } while (uVar8 < 0x100);
  }
  else if (iVar4 == 0x29) {
    iVar4 = *(int *)((int)this + 8);
    puVar6 = (undefined1 *)(iVar4 + 2);
    local_98[0] = 0x28;
    local_8a = 8;
    local_c = 0x400;
    uVar5 = 0;
    do {
      iVar2 = uVar5 * 4;
      *(undefined1 *)((int)local_98 + iVar2 + -0x3fe) = *(undefined1 *)(iVar4 + iVar2);
      *(undefined1 *)((int)local_98 + iVar2 + -0x3ff) = puVar6[-1];
      uVar3 = *puVar6;
      *(undefined1 *)((int)local_98 + iVar2 + -0x3fd) = 0;
      uVar8 = uVar5 + 1;
      puVar6 = puVar6 + 4;
      *(undefined1 *)(local_98 + (uVar5 - 0x100)) = uVar3;
      uVar5 = uVar8;
    } while (uVar8 < 0x100);
  }
  else {
    if (iVar4 != 0x32) {
      return -0x7fffbffb;
    }
    local_98[0] = 0x28;
    local_8a = 8;
    local_c = 0x400;
    uVar5 = 0;
    do {
      iVar4 = uVar5 * 4;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3fd) = 0;
      uVar3 = (undefined1)uVar5;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3fe) = uVar3;
      *(undefined1 *)((int)local_98 + iVar4 + -0x3ff) = uVar3;
      *(undefined1 *)(local_98 + (uVar5 - 0x100)) = uVar3;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 0x100);
  }
  local_88 = 0;
  local_98[1] = *(int *)((int)this + 0xc);
  local_98[2] = *(int *)((int)this + 0x10);
  local_80 = 0xb12;
  local_7c = 0xb12;
  local_1c = (LPCVOID)(uint)(local_8a >> 3);
  local_8 = local_98[1] * (int)local_1c;
  local_14 = local_8 + 3 & 0xfffffffc;
  local_2a = local_98[2] * local_14 + 0x36 + local_c;
  uStack_26 = 0;
  uStack_24 = 0;
  nNumberOfBytesToWrite = (local_2a + 3U & 0xfffffffc) - local_2a;
  local_2a = nNumberOfBytesToWrite + local_2a;
  local_22 = local_c + 0x36;
  local_8c = 1;
  local_2c = 0x4d42;
  if (arg2 != (HANDLE)0x0) {
    WriteFile(arg1,&local_2c,0xe,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
  }
  WriteFile(arg1,local_98,0x28,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
  if (local_c != 0) {
    WriteFile(arg1,local_498,local_c,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
  }
  local_1c = (LPCVOID)(*(int *)((int)this + 0x1c) * *(int *)((int)this + 0x30) +
                       *(int *)((int)this + 0x18) * (int)local_1c + *(int *)((int)this + 4));
  lpBuffer = (LPCVOID)((*(int *)((int)this + 0x10) + -1) * *(int *)((int)this + 0x30) +
                      (int)local_1c);
  if (local_1c <= lpBuffer) {
    do {
      WriteFile(arg1,lpBuffer,local_8,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
      if (local_8 < local_14) {
        WriteFile(arg1,&local_10,local_14 - local_8,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
      }
      lpBuffer = (LPCVOID)((int)lpBuffer - *(int *)((int)this + 0x30));
    } while (local_1c <= lpBuffer);
  }
  if (nNumberOfBytesToWrite != 0) {
    WriteFile(arg1,&local_10,nNumberOfBytesToWrite,(LPDWORD)&arg2,(LPOVERLAPPED)0x0);
  }
  return 0;
}



/* grim_mesh_load_from_buffer @ 100120d6 */

/* [binja] int32_t __thiscall sub_100120d6(int32_t* arg1, HANDLE arg2) */

int __thiscall grim_mesh_load_from_buffer(void *this,int *arg1,HANDLE arg2)

{
  void *pvVar1;
  int iVar2;
  LPCVOID lpBuffer;
  uint uVar3;
  DWORD nNumberOfBytesToWrite;
  int *piVar4;
  int *piVar5;
  uint *puVar6;
  int *piVar7;
  uint uVar8;
  uint local_98 [5];
  uint local_84;
  int local_80;
  int local_50 [8];
  uint local_30;
  byte local_2b;
  byte local_2a;
  undefined4 local_1c;
  int *local_18;
  uint local_14;
  DWORD local_10;
  int *local_c;
  uint local_8;
  
  local_8 = 0;
  for (pvVar1 = this; pvVar1 != (void *)0x0; pvVar1 = *(void **)((int)pvVar1 + 0x4c)) {
    local_8 = local_8 + 1;
  }
  piVar4 = &DAT_10053ec8;
  if (DAT_10053ec8 != 0) {
    iVar2 = DAT_10053ec8;
    do {
      if (iVar2 == *(int *)this) break;
      piVar4 = piVar4 + 9;
      iVar2 = *piVar4;
    } while (iVar2 != 0);
  }
  if (*piVar4 == 0) {
    iVar2 = -0x7fffbffb;
  }
  else {
    local_18 = this;
    local_c = grim_format_info_lookup(*(int *)this);
    local_14 = (uint)local_c[2] >> 3;
    local_1c = 0x20534444;
    WriteFile(arg1,&local_1c,4,&local_10,(LPOVERLAPPED)0x0);
    puVar6 = local_98;
    for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    local_98[2] = *(undefined4 *)((int)this + 0x10);
    local_98[3] = *(undefined4 *)((int)this + 0xc);
    uVar3 = piVar4[2];
    local_98[0] = 0x7c;
    local_98[1] = 0x1007;
    piVar7 = local_50;
    for (iVar2 = 8; piVar5 = local_18, piVar4 = piVar4 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar7 = *piVar4;
      piVar7 = piVar7 + 1;
    }
    local_30 = 0x1000;
    if ((uVar3 & 3) != 0) {
      local_30 = 0x1002;
    }
    if ((uVar3 & 0x20) != 0) {
      local_30 = local_30 | 0x100;
    }
    if (local_18[0x13] != 0) {
      local_30 = local_30 | 0x400008;
      local_98[1] = 0x21007;
      local_80 = local_8;
    }
    if (local_18[0x14] != 0) {
      local_30 = local_30 | 8;
      local_2b = local_2b | 0xfe;
    }
    if (1 < (uint)local_18[5]) {
      local_98[1] = local_98[1] | 0x800000;
      local_2a = local_2a | 0x20;
      local_84 = local_18[5];
    }
    WriteFile(arg1,local_98,0x7c,&local_10,(LPOVERLAPPED)0x0);
    if (local_c[1] == 1) {
      WriteFile(arg1,(LPCVOID)piVar5[2],0x400,&local_10,(LPOVERLAPPED)0x0);
    }
    local_c = piVar5;
    do {
      for (; piVar5 != (int *)0x0; piVar5 = (int *)piVar5[0x13]) {
        local_8 = 0;
        if (piVar5[5] != 0) {
          uVar3 = piVar5[4];
          do {
            uVar8 = 0;
            if (uVar3 != 0) {
              do {
                iVar2 = *local_18;
                if (iVar2 == 0x31545844) {
                  iVar2 = (piVar5[7] + uVar8 >> 2) * piVar5[0xc] +
                          (piVar5[10] + local_8) * piVar5[0xd] + ((uint)piVar5[6] >> 2) * 8;
                  nNumberOfBytesToWrite = (piVar5[3] + 3U >> 2) << 3;
LAB_10012326:
                  lpBuffer = (LPCVOID)(iVar2 + piVar5[1]);
                  uVar8 = uVar8 + 3;
                }
                else {
                  if (iVar2 == 0x32545844) {
LAB_100122c8:
                    iVar2 = (piVar5[7] + uVar8 >> 2) * piVar5[0xc] +
                            (piVar5[10] + local_8) * piVar5[0xd] + ((uint)piVar5[6] >> 2) * 0x10;
                    nNumberOfBytesToWrite = (piVar5[3] + 3U >> 2) << 4;
                    goto LAB_10012326;
                  }
                  if (iVar2 == 0x32595559) {
LAB_1001229c:
                    lpBuffer = (LPCVOID)((piVar5[7] + uVar8) * piVar5[0xc] +
                                         (piVar5[10] + local_8) * piVar5[0xd] + piVar5[6] * local_14
                                        + piVar5[1]);
                    nNumberOfBytesToWrite = (piVar5[3] + 1U >> 1) << 2;
                  }
                  else {
                    if (((iVar2 == 0x33545844) || (iVar2 == 0x34545844)) || (iVar2 == 0x35545844))
                    goto LAB_100122c8;
                    if (iVar2 == 0x59565955) goto LAB_1001229c;
                    lpBuffer = (LPCVOID)((piVar5[7] + uVar8) * piVar5[0xc] +
                                         (piVar5[10] + local_8) * piVar5[0xd] + piVar5[6] * local_14
                                        + piVar5[1]);
                    nNumberOfBytesToWrite = piVar5[3] * local_14;
                  }
                }
                WriteFile(arg1,lpBuffer,nNumberOfBytesToWrite,&local_10,(LPOVERLAPPED)0x0);
                uVar3 = piVar5[4];
                uVar8 = uVar8 + 1;
              } while (uVar8 < uVar3);
            }
            local_8 = local_8 + 1;
          } while (local_8 < (uint)piVar5[5]);
        }
      }
      piVar5 = (int *)local_c[0x14];
      local_c = piVar5;
    } while (piVar5 != (int *)0x0);
    iVar2 = 0;
  }
  return iVar2;
}



/* grim_mesh_vertex_buffer_alloc @ 1001288a */

/* WARNING: Removing unreachable block (ram,0x100128ff) */

int * __cdecl grim_mesh_vertex_buffer_alloc(uint param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  float local_24;
  uint local_1c;
  float local_18;
  uint local_10;
  float local_c;
  float local_8;
  
  uVar17 = 0;
  if ((param_1 != 0) && (param_2 != 0)) {
    fVar2 = (float)param_2;
    if (param_2 < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar3 = (float)(int)param_1;
    if ((int)param_1 < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
    fVar4 = fVar2 / fVar3;
    uVar14 = 0x10;
    if (param_1 != 0) {
      do {
        iVar9 = ftol();
        uVar17 = uVar17 + 1;
        uVar14 = uVar14 + 0xc + iVar9 * 0x10;
      } while (uVar17 < param_1);
    }
    piVar10 = operator_new(uVar14);
    if (piVar10 != (int *)0x0) {
      iVar9 = 0;
      local_1c = 0;
      iVar16 = 4;
      iVar15 = iVar16;
      if (param_1 != 0) {
        do {
          local_8 = 0.0;
          local_10 = 0;
          fVar5 = (float)(int)local_1c;
          iVar16 = iVar15 + 4;
          if ((int)local_1c < 0) {
            fVar5 = fVar5 + 4.2949673e+09;
          }
          do {
            fVar6 = (float)(int)local_10;
            if ((int)local_10 < 0) {
              fVar6 = fVar6 + 4.2949673e+09;
            }
            fVar6 = (fVar6 + fVar5) - 0.5;
            local_24 = fVar6 * fVar4;
            local_c = fVar4 + local_24;
            if (param_3 == 0) {
              if (local_24 < 0.0) {
                local_24 = 0.0;
              }
              if (fVar2 < local_c) {
                local_c = fVar2;
              }
            }
            floor((double)local_24);
            iVar11 = ftol();
            fVar7 = (float)iVar11;
            if (fVar7 < local_c) {
              iVar12 = iVar11 - param_2;
              do {
                local_18 = fVar7 + 1.0;
                if (iVar11 < 0) {
                  iVar13 = iVar11 + param_2;
                }
                else {
                  iVar13 = iVar12;
                  if (iVar11 < param_2) {
                    iVar13 = iVar11;
                  }
                }
                if (iVar13 != iVar9) {
                  if (1e-05 < local_8) {
                    piVar1 = (int *)(iVar16 + (int)piVar10);
                    *piVar1 = iVar9;
                    iVar16 = iVar16 + 8;
                    piVar1[1] = (int)local_8;
                  }
                  local_8 = 0.0;
                  iVar9 = iVar13;
                }
                if (fVar7 < local_24) {
                  fVar7 = local_24;
                }
                if (local_c < local_18) {
                  local_18 = local_c;
                }
                if (param_3 == 0) {
                  if (0.0 <= fVar6) {
                    if (fVar6 + 1.0 < fVar3) goto LAB_10012ab1;
                    fVar8 = 0.0;
                  }
                  else {
                    fVar8 = 1.0;
                  }
                }
                else {
LAB_10012ab1:
                  fVar8 = (local_18 + fVar7) * (0.5 / fVar4) - fVar6;
                }
                if (local_10 != 0) {
                  fVar8 = 1.0 - fVar8;
                }
                iVar11 = iVar11 + 1;
                iVar12 = iVar12 + 1;
                local_8 = (local_18 - fVar7) * fVar8 + local_8;
                fVar7 = (float)iVar11;
              } while (fVar7 < local_c);
            }
            local_10 = local_10 + 1;
          } while (local_10 < 2);
          if (1e-05 < local_8) {
            piVar1 = (int *)(iVar16 + (int)piVar10);
            iVar16 = iVar16 + 8;
            *piVar1 = iVar9;
            piVar1[1] = (int)local_8;
          }
          local_1c = local_1c + 1;
          *(int *)(iVar15 + (int)piVar10) = iVar16 - iVar15;
          iVar15 = iVar16;
        } while (local_1c < param_1);
      }
      *piVar10 = iVar16;
      return piVar10;
    }
  }
  return (int *)0x0;
}



/* grim_mesh_vertex_buffer_free @ 10012b47 */

/* [binja] int32_t* __thiscall sub_10012b47(int32_t* arg1, char arg2) */

int * __thiscall grim_mesh_vertex_buffer_free(void *this,int *arg1,char arg2)

{
  int *piVar1;
  
  if (((uint)arg1 & 2) == 0) {
    operator_delete(*(void **)this);
    piVar1 = this;
    if (((uint)arg1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    piVar1 = (int *)((int)this + -4);
    grim_crt_buffer_alloc((int)this,0xc,*piVar1,0x10012881);
    if (((uint)arg1 & 1) != 0) {
      operator_delete(piVar1);
    }
  }
  return piVar1;
}



/* grim_mesh_texture_process @ 10012b93 */

/* [binja] int32_t __fastcall sub_10012b93(int32_t* arg1) */

int grim_mesh_texture_process(int *arg1)

{
  int *piVar1;
  float fVar2;
  int *piVar3;
  void *pvVar4;
  int *extraout_ECX;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  float *pfVar9;
  int unaff_EBP;
  undefined4 unaff_EDI;
  undefined4 *puVar10;
  float *pfVar11;
  char arg2;
  
  seh_prolog();
  *(undefined4 *)(unaff_EBP + -0x2c) = 0;
  *(undefined4 *)(unaff_EBP + -0x28) = 0;
  *(undefined4 *)(unaff_EBP + -0x58) = 0;
  *(undefined4 *)(unaff_EBP + -0x20) = 0;
  *(undefined4 *)(unaff_EBP + -0x5c) = 0;
  uVar5 = extraout_ECX[2];
  *(uint *)(unaff_EBP + -0x54) = ~(uVar5 >> 0x12) & 1;
  piVar3 = grim_mesh_vertex_buffer_alloc(*(uint *)(*extraout_ECX + 0x1058),*(int *)(extraout_ECX[1] + 0x1058),
                        ~(uVar5 >> 0x10) & 1);
  arg2 = (char)unaff_EDI;
  *(int **)(unaff_EBP + -0x44) = piVar3;
  if (piVar3 != (int *)0x0) {
    piVar3 = grim_mesh_vertex_buffer_alloc(*(uint *)(*extraout_ECX + 0x105c),*(int *)(extraout_ECX[1] + 0x105c),
                          ~(uVar5 >> 0x11) & 1);
    arg2 = (char)unaff_EDI;
    *(int **)(unaff_EBP + -0x2c) = piVar3;
    if (piVar3 != (int *)0x0) {
      piVar3 = grim_mesh_vertex_buffer_alloc(*(uint *)(*extraout_ECX + 0x1060),*(int *)(extraout_ECX[1] + 0x1060),
                            *(int *)(unaff_EBP + -0x54));
      arg2 = (char)unaff_EDI;
      *(int **)(unaff_EBP + -0x28) = piVar3;
      if (piVar3 != (int *)0x0) {
        *(int *)(unaff_EBP + -0x4c) =
             **(int **)(unaff_EBP + -0x44) + (int)*(int **)(unaff_EBP + -0x44);
        *(int *)(unaff_EBP + -0x50) =
             **(int **)(unaff_EBP + -0x2c) + (int)*(int **)(unaff_EBP + -0x2c);
        *(int *)(unaff_EBP + -0x24) =
             **(int **)(unaff_EBP + -0x28) + (int)*(int **)(unaff_EBP + -0x28);
        iVar6 = *(int *)(extraout_ECX[1] + 0x1060);
        piVar3 = operator_new(iVar6 * 0xc + 4);
        *(int **)(unaff_EBP + -0x54) = piVar3;
        *(undefined4 *)(unaff_EBP + -4) = 0;
        if (piVar3 == (int *)0x0) {
          *(undefined4 *)(unaff_EBP + -0x14) = 0;
          iVar6 = *(int *)(unaff_EBP + -0x14);
        }
        else {
          *piVar3 = iVar6;
          *(int **)(unaff_EBP + -0x58) = piVar3 + 1;
          grim_crt_buffer_alloc_zeroed((int)(piVar3 + 1),0xc,iVar6,0x10012874);
          iVar6 = *(int *)(unaff_EBP + -0x58);
          *(int *)(unaff_EBP + -0x14) = iVar6;
        }
        arg2 = (char)unaff_EDI;
        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
        *(int *)(unaff_EBP + -0x58) = iVar6;
        if (iVar6 != 0) {
          iVar6 = *(int *)(*extraout_ECX + 0x1058);
          pvVar4 = operator_new(iVar6 << 4);
          *(void **)(unaff_EBP + -0x5c) = pvVar4;
          *(undefined4 *)(unaff_EBP + -4) = 1;
          if (pvVar4 == (void *)0x0) {
            *(undefined4 *)(unaff_EBP + -0x1c) = 0;
            iVar6 = *(int *)(unaff_EBP + -0x1c);
          }
          else {
            _vector_constructor_iterator_
                      (pvVar4,0x10,iVar6,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
            iVar6 = *(int *)(unaff_EBP + -0x5c);
            *(int *)(unaff_EBP + -0x1c) = iVar6;
          }
          arg2 = (char)unaff_EDI;
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          *(int *)(unaff_EBP + -0x5c) = iVar6;
          if (iVar6 != 0) {
            piVar3 = (int *)(*(int *)(unaff_EBP + -0x28) + 4);
            piVar8 = piVar3;
            if (piVar3 < *(int **)(unaff_EBP + -0x24)) {
              do {
                piVar7 = (int *)(*piVar8 + (int)piVar8);
                for (piVar8 = piVar8 + 1; piVar8 < piVar7; piVar8 = piVar8 + 2) {
                  piVar1 = (int *)(*(int *)(unaff_EBP + -0x14) + 8 + *piVar8 * 0xc);
                  *piVar1 = *piVar1 + 1;
                }
                piVar8 = piVar7;
              } while (piVar7 < *(int **)(unaff_EBP + -0x24));
            }
            *(undefined4 *)(unaff_EBP + -0x40) = 0;
            if (piVar3 < *(int **)(unaff_EBP + -0x24)) {
              do {
                piVar8 = (int *)(*piVar3 + (int)piVar3);
                piVar7 = piVar3 + 1;
                *(int **)(unaff_EBP + -0x18) = piVar8;
                *(int **)(unaff_EBP + -0x54) = piVar7;
                *(int **)(unaff_EBP + -0x10) = piVar7;
                piVar3 = piVar8;
                if (piVar7 < piVar8) {
                  do {
                    piVar3 = (int *)(*(int *)(unaff_EBP + -0x14) +
                                    **(int **)(unaff_EBP + -0x10) * 0xc);
                    if (*piVar3 == 0) {
                      piVar7 = *(int **)(unaff_EBP + -0x20);
                      if (piVar7 == (int *)0x0) {
                        iVar6 = *(int *)(extraout_ECX[1] + 0x105c) *
                                *(int *)(extraout_ECX[1] + 0x1058);
                        pvVar4 = operator_new(iVar6 * 0x10);
                        *(void **)(unaff_EBP + -0x48) = pvVar4;
                        *(undefined4 *)(unaff_EBP + -4) = 2;
                        if (pvVar4 == (void *)0x0) {
                          iVar6 = 0;
                        }
                        else {
                          _vector_constructor_iterator_
                                    (pvVar4,0x10,iVar6,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
                          iVar6 = *(int *)(unaff_EBP + -0x48);
                        }
                        arg2 = (char)unaff_EDI;
                        *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
                        *piVar3 = iVar6;
                        if (iVar6 == 0) goto LAB_10012fb2;
                        piVar8 = *(int **)(unaff_EBP + -0x18);
                      }
                      else {
                        *piVar3 = *piVar7;
                        *piVar7 = 0;
                        *(int *)(unaff_EBP + -0x20) = piVar7[1];
                      }
                      puVar10 = (undefined4 *)*piVar3;
                      for (uVar5 = (uint)(*(int *)(extraout_ECX[1] + 0x105c) *
                                          *(int *)(extraout_ECX[1] + 0x1058) * 0x10) >> 2;
                          uVar5 != 0; uVar5 = uVar5 - 1) {
                        *puVar10 = 0;
                        puVar10 = puVar10 + 1;
                      }
                      for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
                        *(undefined1 *)puVar10 = 0;
                        puVar10 = (undefined4 *)((int)puVar10 + 1);
                      }
                    }
                    *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 8;
                    piVar3 = piVar8;
                  } while (*(int **)(unaff_EBP + -0x10) < piVar8);
                }
                *(undefined4 *)(unaff_EBP + -0x38) = 0;
                uVar5 = *(int *)(unaff_EBP + -0x2c) + 4;
                *(uint *)(unaff_EBP + -0x3c) = uVar5;
                if (uVar5 < *(uint *)(unaff_EBP + -0x50)) {
                  do {
                    piVar3 = (int *)(**(int **)(unaff_EBP + -0x3c) +
                                    (int)*(int **)(unaff_EBP + -0x3c));
                    iVar6 = *(int *)*extraout_ECX;
                    *(int **)(unaff_EBP + -0x48) = piVar3;
                    (**(code **)(iVar6 + 4))
                              (*(undefined4 *)(unaff_EBP + -0x38),*(undefined4 *)(unaff_EBP + -0x40)
                               ,*(undefined4 *)(unaff_EBP + -0x1c));
                    uVar5 = *(int *)(unaff_EBP + -0x44) + 4;
                    *(uint *)(unaff_EBP + -0x34) = uVar5;
                    if (uVar5 < *(uint *)(unaff_EBP + -0x4c)) {
                      pfVar9 = (float *)(*(int *)(unaff_EBP + -0x1c) + 8);
                      do {
                        uVar5 = **(int **)(unaff_EBP + -0x34) + (int)*(int **)(unaff_EBP + -0x34);
                        piVar8 = *(int **)(unaff_EBP + -0x54);
                        *(uint *)(unaff_EBP + -0x30) = uVar5;
                        for (; *(int **)(unaff_EBP + -0x10) = piVar8,
                            piVar8 < *(int **)(unaff_EBP + -0x18); piVar8 = piVar8 + 2) {
                          piVar7 = (int *)(*(int *)(unaff_EBP + -0x3c) + 4);
                          if (piVar7 < piVar3) {
                            do {
                              iVar6 = *(int *)(extraout_ECX[1] + 0x1058) * *piVar7 * 0x10 +
                                      *(int *)(*(int *)(unaff_EBP + -0x14) + *piVar8 * 0xc);
                              for (piVar3 = (int *)(*(int *)(unaff_EBP + -0x34) + 4);
                                  piVar3 < *(int **)(unaff_EBP + -0x30); piVar3 = piVar3 + 2) {
                                fVar2 = (float)piVar3[1] * (float)piVar7[1] *
                                        *(float *)(*(int *)(unaff_EBP + -0x10) + 4);
                                pfVar11 = (float *)(*piVar3 * 0x10 + iVar6);
                                *pfVar11 = fVar2 * pfVar9[-2] + *pfVar11;
                                pfVar11 = (float *)(*piVar3 * 0x10 + 4 + iVar6);
                                *pfVar11 = fVar2 * pfVar9[-1] + *pfVar11;
                                pfVar11 = (float *)(*piVar3 * 0x10 + 8 + iVar6);
                                *pfVar11 = fVar2 * *pfVar9 + *pfVar11;
                                pfVar11 = (float *)(*piVar3 * 0x10 + 0xc + iVar6);
                                *pfVar11 = fVar2 * pfVar9[1] + *pfVar11;
                              }
                              piVar8 = *(int **)(unaff_EBP + -0x10);
                              piVar7 = piVar7 + 2;
                            } while (piVar7 < *(int **)(unaff_EBP + -0x48));
                            piVar3 = *(int **)(unaff_EBP + -0x48);
                            uVar5 = *(uint *)(unaff_EBP + -0x30);
                          }
                        }
                        pfVar9 = pfVar9 + 4;
                        *(uint *)(unaff_EBP + -0x34) = uVar5;
                      } while (uVar5 < *(uint *)(unaff_EBP + -0x4c));
                    }
                    *(int *)(unaff_EBP + -0x38) = *(int *)(unaff_EBP + -0x38) + 1;
                    *(int **)(unaff_EBP + -0x3c) = piVar3;
                  } while (piVar3 < *(int **)(unaff_EBP + -0x50));
                  piVar3 = *(int **)(unaff_EBP + -0x18);
                }
                for (piVar8 = *(int **)(unaff_EBP + -0x54); arg2 = (char)unaff_EDI, piVar8 < piVar3;
                    piVar8 = piVar8 + 2) {
                  piVar1 = (int *)(*(int *)(unaff_EBP + -0x14) + *piVar8 * 0xc);
                  piVar7 = piVar1 + 2;
                  *piVar7 = *piVar7 + -1;
                  if (*piVar7 == 0) {
                    piVar7 = (int *)extraout_ECX[1];
                    *(undefined4 *)(unaff_EBP + -0x10) = 0;
                    if (piVar7[0x417] != 0) {
                      do {
                        (**(code **)(*piVar7 + 8))
                                  (*(undefined4 *)(unaff_EBP + -0x10),*piVar8,
                                   piVar7[0x416] * *(int *)(unaff_EBP + -0x10) * 0x10 + *piVar1);
                        *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 1;
                        piVar7 = (int *)extraout_ECX[1];
                      } while (*(uint *)(unaff_EBP + -0x10) < (uint)piVar7[0x417]);
                      piVar3 = *(int **)(unaff_EBP + -0x18);
                    }
                    piVar1[1] = *(int *)(unaff_EBP + -0x20);
                    *(int **)(unaff_EBP + -0x20) = piVar1;
                  }
                }
                *(int *)(unaff_EBP + -0x40) = *(int *)(unaff_EBP + -0x40) + 1;
              } while (piVar3 < *(int **)(unaff_EBP + -0x24));
            }
            iVar6 = 0;
            goto LAB_10012fbe;
          }
        }
LAB_10012fb2:
        iVar6 = -0x7ff8fff2;
        goto LAB_10012fbe;
      }
    }
  }
  iVar6 = -0x7fffbffb;
LAB_10012fbe:
  if (*(void **)(unaff_EBP + -0x58) != (void *)0x0) {
    grim_mesh_vertex_buffer_free(*(void **)(unaff_EBP + -0x58),(int *)0x3,arg2);
  }
  operator_delete(*(void **)(unaff_EBP + -0x28));
  operator_delete(*(void **)(unaff_EBP + -0x2c));
  operator_delete(*(void **)(unaff_EBP + -0x44));
  operator_delete(*(void **)(unaff_EBP + -0x5c));
  operator_delete((void *)0x0);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar6;
}



/* grim_mesh_skin_process @ 10014bbc */

/* [binja] int32_t __fastcall sub_10014bbc(int32_t* arg1) */

int grim_mesh_skin_process(int *arg1)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  void *pvVar10;
  int iVar11;
  int *extraout_ECX;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  int unaff_EBP;
  int iVar16;
  
  seh_prolog();
  if ((char)extraout_ECX[2] == '\x05') {
    iVar9 = *extraout_ECX;
    uVar6 = *(uint *)(iVar9 + 0x1058);
    iVar11 = extraout_ECX[1];
    if ((((*(uint *)(iVar11 + 0x1058) == uVar6 >> 1) ||
         ((*(uint *)(iVar11 + 0x1058) == 1 && (uVar6 == 1)))) &&
        ((*(uint *)(iVar11 + 0x105c) == *(uint *)(iVar9 + 0x105c) >> 1 ||
         ((*(uint *)(iVar11 + 0x105c) == 1 && (*(int *)(iVar9 + 0x105c) == 1)))))) &&
       (*(uint *)(iVar11 + 0x1060) == *(uint *)(iVar9 + 0x1060) >> 1)) {
      if ((1 < uVar6) && ((uVar6 & 1) != 0)) {
        *(uint *)(iVar9 + 0x1058) = uVar6 & 0xfffffffe;
        piVar1 = (int *)(*extraout_ECX + 0x1064);
        *piVar1 = *piVar1 - *(int *)(*extraout_ECX + 0x1068);
      }
      uVar6 = *(uint *)(*extraout_ECX + 0x105c);
      if (1 < uVar6) {
        *(uint *)(*extraout_ECX + 0x105c) = uVar6 & 0xfffffffe;
      }
      uVar6 = *(uint *)(*extraout_ECX + 0x1060);
      if (1 < uVar6) {
        *(uint *)(*extraout_ECX + 0x1060) = uVar6 & 0xfffffffe;
      }
      iVar9 = *(int *)(extraout_ECX[1] + 0x1058);
      pvVar10 = operator_new(iVar9 << 4);
      *(void **)(unaff_EBP + -0x14) = pvVar10;
      *(undefined4 *)(unaff_EBP + -4) = 0;
      if (pvVar10 == (void *)0x0) {
        *(undefined4 *)(unaff_EBP + -0x20) = 0;
      }
      else {
        _vector_constructor_iterator_(pvVar10,0x10,iVar9,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
        *(undefined4 *)(unaff_EBP + -0x20) = *(undefined4 *)(unaff_EBP + -0x14);
      }
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      if (*(int *)(unaff_EBP + -0x20) == 0) {
        iVar9 = -0x7ff8fff2;
      }
      else {
        iVar9 = *(int *)(*extraout_ECX + 0x1058);
        if (*(int *)(*extraout_ECX + 0x105c) == 1) {
          pvVar10 = operator_new(iVar9 << 5);
          *(void **)(unaff_EBP + -0x14) = pvVar10;
          *(undefined4 *)(unaff_EBP + -4) = 1;
          if (pvVar10 == (void *)0x0) {
            iVar12 = 0;
          }
          else {
            _vector_constructor_iterator_
                      (pvVar10,0x10,iVar9 << 1,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
            iVar12 = *(int *)(unaff_EBP + -0x14);
          }
          iVar11 = *(int *)(*extraout_ECX + 0x1058);
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          iVar9 = iVar11 * 0x10 + iVar12;
          *(int *)(unaff_EBP + -0x38) = iVar12;
          *(int *)(unaff_EBP + -0x18) = iVar12;
          *(int *)(unaff_EBP + -0x30) = iVar9;
          *(int *)(unaff_EBP + -0x1c) = iVar12;
          *(int *)(unaff_EBP + -0x28) = iVar9;
          iVar16 = iVar9;
        }
        else {
          pvVar10 = operator_new(iVar9 << 6);
          *(void **)(unaff_EBP + -0x14) = pvVar10;
          *(undefined4 *)(unaff_EBP + -4) = 2;
          if (pvVar10 == (void *)0x0) {
            iVar9 = 0;
          }
          else {
            _vector_constructor_iterator_
                      (pvVar10,0x10,iVar9 << 2,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
            iVar9 = *(int *)(unaff_EBP + -0x14);
          }
          iVar11 = *(int *)(*extraout_ECX + 0x1058);
          *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
          *(int *)(unaff_EBP + -0x30) = iVar11 * 0x10 + iVar9;
          iVar16 = *(int *)(unaff_EBP + -0x30);
          *(int *)(unaff_EBP + -0x1c) = iVar11 * 0x20 + iVar9;
          *(int *)(unaff_EBP + -0x28) = iVar11 * 0x30 + iVar9;
          iVar12 = *(int *)(unaff_EBP + -0x1c);
          *(int *)(unaff_EBP + -0x38) = iVar9;
          *(int *)(unaff_EBP + -0x18) = iVar9;
          iVar9 = *(int *)(unaff_EBP + -0x28);
        }
        if (*(int *)(unaff_EBP + -0x38) == 0) {
          iVar9 = -0x7ff8fff2;
        }
        else {
          if (iVar11 == 1) {
            *(int *)(unaff_EBP + -0x3c) = *(int *)(unaff_EBP + -0x18);
            *(int *)(unaff_EBP + -0x40) = iVar16;
          }
          else {
            *(int *)(unaff_EBP + -0x3c) = *(int *)(unaff_EBP + -0x18) + 0x10;
            iVar12 = iVar12 + 0x10;
            *(int *)(unaff_EBP + -0x40) = iVar16 + 0x10;
            iVar9 = iVar9 + 0x10;
          }
          iVar11 = extraout_ECX[1];
          *(undefined4 *)(unaff_EBP + -0x24) = 0;
          iVar7 = *(int *)(iVar11 + 0x1060);
          *(int *)(unaff_EBP + -0x44) = iVar12;
          *(int *)(unaff_EBP + -0x14) = iVar9;
          if (iVar7 != 0) {
            do {
              *(undefined4 *)(unaff_EBP + -0x10) = 0;
              if (*(int *)(iVar11 + 0x105c) != 0) {
                do {
                  iVar9 = *(int *)(unaff_EBP + -0x24) * 2;
                  (**(code **)(*(int *)*extraout_ECX + 4))
                            (*(int *)(unaff_EBP + -0x10) * 2,iVar9,
                             *(undefined4 *)(unaff_EBP + -0x18));
                  if (iVar16 != *(int *)(unaff_EBP + -0x18)) {
                    (**(code **)(*(int *)*extraout_ECX + 4))
                              (*(int *)(unaff_EBP + -0x10) * 2,iVar9 + 1,iVar16);
                  }
                  if (*(int *)(unaff_EBP + -0x1c) != *(int *)(unaff_EBP + -0x18)) {
                    (**(code **)(*(int *)*extraout_ECX + 4))
                              (*(int *)(unaff_EBP + -0x10) * 2 + 1,iVar9,*(int *)(unaff_EBP + -0x1c)
                              );
                  }
                  iVar11 = *(int *)(unaff_EBP + -0x28);
                  if ((iVar11 != iVar16) && (iVar11 != *(int *)(unaff_EBP + -0x1c))) {
                    (**(code **)(*(int *)*extraout_ECX + 4))
                              (*(int *)(unaff_EBP + -0x10) * 2 + 1,iVar9 + 1,iVar11);
                  }
                  iVar9 = extraout_ECX[1];
                  *(undefined4 *)(unaff_EBP + -0x2c) = 0;
                  if (*(int *)(iVar9 + 0x1058) != 0) {
                    *(undefined4 *)(unaff_EBP + -0x34) = *(undefined4 *)(unaff_EBP + -0x20);
                    do {
                      iVar9 = *(int *)(unaff_EBP + -0x2c) * 0x20;
                      pfVar13 = (float *)(*(int *)(unaff_EBP + -0x3c) + iVar9);
                      fVar2 = *pfVar13;
                      pfVar15 = (float *)(*(int *)(unaff_EBP + -0x18) + iVar9);
                      fVar3 = *pfVar15;
                      fVar4 = pfVar13[1];
                      fVar5 = pfVar15[1];
                      *(float *)(unaff_EBP + -0x8c) = pfVar13[2] + pfVar15[2];
                      pfVar14 = (float *)(iVar9 + iVar16);
                      *(float *)(unaff_EBP + -0x88) = pfVar13[3] + pfVar15[3];
                      *(float *)(unaff_EBP + -0xb4) = fVar2 + fVar3 + *pfVar14;
                      fVar2 = pfVar14[1];
                      fVar3 = pfVar14[2];
                      pfVar13 = (float *)(*(int *)(unaff_EBP + -0x40) + iVar9);
                      *(float *)(unaff_EBP + -0xa8) = *(float *)(unaff_EBP + -0x88) + pfVar14[3];
                      *(float *)(unaff_EBP + -0x84) = *(float *)(unaff_EBP + -0xb4) + *pfVar13;
                      *(float *)(unaff_EBP + -0x80) = fVar4 + fVar5 + fVar2 + pfVar13[1];
                      fVar2 = pfVar13[2];
                      fVar4 = pfVar13[3];
                      pfVar14 = (float *)(*(int *)(unaff_EBP + -0x1c) + iVar9);
                      *(float *)(unaff_EBP + -0x54) = *(float *)(unaff_EBP + -0x84) + *pfVar14;
                      *(float *)(unaff_EBP + -0x50) = *(float *)(unaff_EBP + -0x80) + pfVar14[1];
                      *(float *)(unaff_EBP + -0x4c) =
                           *(float *)(unaff_EBP + -0x8c) + fVar3 + fVar2 + pfVar14[2];
                      fVar2 = pfVar14[3];
                      pfVar14 = (float *)(*(int *)(unaff_EBP + -0x44) + iVar9);
                      fVar3 = *pfVar14;
                      *(float *)(unaff_EBP + -0x60) = *(float *)(unaff_EBP + -0x50) + pfVar14[1];
                      *(float *)(unaff_EBP + -0x5c) = *(float *)(unaff_EBP + -0x4c) + pfVar14[2];
                      *(float *)(unaff_EBP + -0x58) =
                           *(float *)(unaff_EBP + -0xa8) + fVar4 + fVar2 + pfVar14[3];
                      pfVar14 = (float *)(*(int *)(unaff_EBP + -0x28) + iVar9);
                      fVar2 = *pfVar14;
                      puVar8 = *(undefined4 **)(unaff_EBP + -0x34);
                      *(int *)(unaff_EBP + -0x34) = *(int *)(unaff_EBP + -0x34) + 0x10;
                      fVar4 = pfVar14[1];
                      *(float *)(unaff_EBP + -0x9c) = *(float *)(unaff_EBP + -0x5c) + pfVar14[2];
                      fVar5 = pfVar14[3];
                      pfVar14 = (float *)(iVar9 + *(int *)(unaff_EBP + -0x14));
                      *(int *)(unaff_EBP + -0x2c) = *(int *)(unaff_EBP + -0x2c) + 1;
                      *(float *)(unaff_EBP + -0x98) = *(float *)(unaff_EBP + -0x58) + fVar5;
                      uVar6 = *(uint *)(unaff_EBP + -0x2c);
                      *(float *)(unaff_EBP + -0xc4) =
                           *(float *)(unaff_EBP + -0x54) + fVar3 + fVar2 + *pfVar14;
                      fVar2 = pfVar14[1];
                      fVar3 = pfVar14[2];
                      *(float *)(unaff_EBP + -0xb8) = *(float *)(unaff_EBP + -0x98) + pfVar14[3];
                      *(float *)(unaff_EBP + -0x74) = *(float *)(unaff_EBP + -0xc4) * 0.125;
                      *(float *)(unaff_EBP + -0x70) =
                           (*(float *)(unaff_EBP + -0x60) + fVar4 + fVar2) * 0.125;
                      *(float *)(unaff_EBP + -0x6c) =
                           (*(float *)(unaff_EBP + -0x9c) + fVar3) * 0.125;
                      *(float *)(unaff_EBP + -0x68) = *(float *)(unaff_EBP + -0xb8) * 0.125;
                      *puVar8 = *(undefined4 *)(unaff_EBP + -0x74);
                      puVar8[1] = *(undefined4 *)(unaff_EBP + -0x70);
                      puVar8[2] = *(undefined4 *)(unaff_EBP + -0x6c);
                      puVar8[3] = *(undefined4 *)(unaff_EBP + -0x68);
                      iVar16 = *(int *)(unaff_EBP + -0x30);
                    } while (uVar6 < *(uint *)(extraout_ECX[1] + 0x1058));
                  }
                  (**(code **)(*(int *)extraout_ECX[1] + 8))
                            (*(undefined4 *)(unaff_EBP + -0x10),*(undefined4 *)(unaff_EBP + -0x24),
                             *(undefined4 *)(unaff_EBP + -0x20));
                  *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 1;
                } while (*(uint *)(unaff_EBP + -0x10) < *(uint *)(extraout_ECX[1] + 0x105c));
              }
              *(int *)(unaff_EBP + -0x24) = *(int *)(unaff_EBP + -0x24) + 1;
              iVar11 = extraout_ECX[1];
            } while (*(uint *)(unaff_EBP + -0x24) < *(uint *)(iVar11 + 0x1060));
          }
          operator_delete(*(void **)(unaff_EBP + -0x38));
          iVar9 = 0;
        }
        operator_delete(*(void **)(unaff_EBP + -0x20));
      }
    }
    else {
      iVar9 = -0x7fffbffb;
    }
  }
  else {
    iVar9 = -0x7fffbffb;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar9;
}



/* grim_model_load_with_mipmaps @ 10015c65 */

/* [binja] int32_t __fastcall sub_10015c65(int32_t* arg1) */

int grim_model_load_with_mipmaps(int *arg1)

{
  int iVar1;
  float fVar2;
  int *piVar3;
  int *piVar4;
  void *pvVar5;
  int *extraout_ECX;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  float *pfVar9;
  int unaff_EBP;
  float *pfVar10;
  int iVar11;
  undefined4 unaff_EDI;
  undefined4 *puVar12;
  char arg2;
  
  seh_prolog();
  iVar11 = extraout_ECX[1];
  iVar1 = *(int *)(iVar11 + 0x1060);
  *(undefined4 *)(unaff_EBP + -0x20) = 0;
  *(undefined4 *)(unaff_EBP + -0x34) = 0;
  *(undefined4 *)(unaff_EBP + -0x18) = 0;
  *(undefined4 *)(unaff_EBP + -0x3c) = 0;
  if ((iVar1 != 1) || (*(int *)(*extraout_ECX + 0x1060) != 1)) {
    iVar11 = -0x7fffbffb;
    goto LAB_10015ff8;
  }
  uVar6 = extraout_ECX[2];
  piVar3 = grim_mesh_vertex_buffer_alloc(*(uint *)(*extraout_ECX + 0x1058),*(int *)(iVar11 + 0x1058),
                        ~(uVar6 >> 0x10) & 1);
  arg2 = (char)unaff_EDI;
  *(int **)(unaff_EBP + -0x38) = piVar3;
  if (piVar3 == (int *)0x0) {
LAB_10015fba:
    iVar11 = -0x7fffbffb;
  }
  else {
    piVar4 = grim_mesh_vertex_buffer_alloc(*(uint *)(*extraout_ECX + 0x105c),*(int *)(extraout_ECX[1] + 0x105c),
                          ~(uVar6 >> 0x11) & 1);
    arg2 = (char)unaff_EDI;
    *(int **)(unaff_EBP + -0x20) = piVar4;
    if (piVar4 == (int *)0x0) goto LAB_10015fba;
    *(int *)(unaff_EBP + -0x2c) = *piVar3 + (int)piVar3;
    piVar4 = (int *)(**(int **)(unaff_EBP + -0x20) + (int)*(int **)(unaff_EBP + -0x20));
    iVar11 = *(int *)(extraout_ECX[1] + 0x105c);
    *(int **)(unaff_EBP + -0x44) = piVar4;
    piVar3 = operator_new(iVar11 * 0xc + 4);
    *(int **)(unaff_EBP + -0x40) = piVar3;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (piVar3 == (int *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x14) = 0;
      iVar11 = *(int *)(unaff_EBP + -0x14);
    }
    else {
      *piVar3 = iVar11;
      *(int **)(unaff_EBP + -0x34) = piVar3 + 1;
      grim_crt_buffer_alloc_zeroed((int)(piVar3 + 1),0xc,iVar11,0x10012874);
      iVar11 = *(int *)(unaff_EBP + -0x34);
      *(int *)(unaff_EBP + -0x14) = iVar11;
    }
    arg2 = (char)unaff_EDI;
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    *(int *)(unaff_EBP + -0x34) = iVar11;
    if (iVar11 == 0) {
LAB_10015fb3:
      iVar11 = -0x7ff8fff2;
    }
    else {
      iVar11 = *(int *)(*extraout_ECX + 0x1058);
      pvVar5 = operator_new(iVar11 << 4);
      *(void **)(unaff_EBP + -0x3c) = pvVar5;
      *(undefined4 *)(unaff_EBP + -4) = 1;
      if (pvVar5 == (void *)0x0) {
        *(undefined4 *)(unaff_EBP + -0x24) = 0;
        iVar11 = *(int *)(unaff_EBP + -0x24);
      }
      else {
        _vector_constructor_iterator_(pvVar5,0x10,iVar11,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
        iVar11 = *(int *)(unaff_EBP + -0x3c);
        *(int *)(unaff_EBP + -0x24) = iVar11;
      }
      arg2 = (char)unaff_EDI;
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      *(int *)(unaff_EBP + -0x3c) = iVar11;
      if (iVar11 == 0) goto LAB_10015fb3;
      piVar3 = (int *)(*(int *)(unaff_EBP + -0x20) + 4);
      *(int **)(unaff_EBP + -0x30) = piVar3;
      while (piVar3 < piVar4) {
        piVar8 = (int *)(*piVar3 + (int)piVar3);
        for (piVar7 = piVar3 + 1; piVar3 = piVar8, piVar7 < piVar8; piVar7 = piVar7 + 2) {
          piVar3 = (int *)(*(int *)(unaff_EBP + -0x14) + 8 + *piVar7 * 0xc);
          *piVar3 = *piVar3 + 1;
        }
      }
      piVar3 = *(int **)(unaff_EBP + -0x30);
      *(undefined4 *)(unaff_EBP + -0x28) = 0;
      if (piVar3 < piVar4) {
        do {
          iVar11 = *piVar3;
          piVar4 = piVar3 + 1;
          *(int **)(unaff_EBP + -0x1c) = (int *)(iVar11 + (int)piVar3);
          *(int **)(unaff_EBP + -0x30) = piVar4;
          piVar3 = (int *)(iVar11 + (int)piVar3);
          while (*(int **)(unaff_EBP + -0x10) = piVar4, piVar4 < piVar3) {
            piVar4 = (int *)(*(int *)(unaff_EBP + -0x14) + *piVar4 * 0xc);
            if (*piVar4 == 0) {
              piVar3 = *(int **)(unaff_EBP + -0x18);
              if (piVar3 == (int *)0x0) {
                iVar11 = *(int *)(extraout_ECX[1] + 0x1058);
                pvVar5 = operator_new(iVar11 << 4);
                *(void **)(unaff_EBP + -0x40) = pvVar5;
                *(undefined4 *)(unaff_EBP + -4) = 2;
                if (pvVar5 == (void *)0x0) {
                  iVar11 = 0;
                }
                else {
                  _vector_constructor_iterator_
                            (pvVar5,0x10,iVar11,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
                  iVar11 = *(int *)(unaff_EBP + -0x40);
                }
                arg2 = (char)unaff_EDI;
                *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
                *piVar4 = iVar11;
                if (iVar11 == 0) goto LAB_10015fb3;
              }
              else {
                *piVar4 = *piVar3;
                *piVar3 = 0;
                *(int *)(unaff_EBP + -0x18) = piVar3[1];
              }
              piVar3 = *(int **)(unaff_EBP + -0x1c);
              puVar12 = (undefined4 *)*piVar4;
              for (uVar6 = (uint)(*(int *)(extraout_ECX[1] + 0x1058) << 4) >> 2; uVar6 != 0;
                  uVar6 = uVar6 - 1) {
                *puVar12 = 0;
                puVar12 = puVar12 + 1;
              }
              for (iVar11 = 0; iVar11 != 0; iVar11 = iVar11 + -1) {
                *(undefined1 *)puVar12 = 0;
                puVar12 = (undefined4 *)((int)puVar12 + 1);
              }
            }
            piVar4 = (int *)(*(int *)(unaff_EBP + -0x10) + 8);
          }
          iVar11 = *(int *)(unaff_EBP + -0x24);
          (**(code **)(*(int *)*extraout_ECX + 4))(*(undefined4 *)(unaff_EBP + -0x28),0,iVar11);
          piVar4 = (int *)(*(int *)(unaff_EBP + -0x38) + 4);
          if (piVar4 < *(int **)(unaff_EBP + -0x2c)) {
            pfVar9 = (float *)(iVar11 + 8);
            do {
              piVar7 = *(int **)(unaff_EBP + -0x30);
              piVar8 = (int *)(*piVar4 + (int)piVar4);
              *(int **)(unaff_EBP + -0x10) = piVar7;
              if (piVar7 < piVar3) {
                *(int **)(unaff_EBP + -0x40) = piVar4 + 1;
                while( true ) {
                  iVar11 = *(int *)(*(int *)(unaff_EBP + -0x14) + *piVar7 * 0xc);
                  piVar4 = *(int **)(unaff_EBP + -0x40);
                  if (piVar4 < piVar8) {
                    do {
                      fVar2 = (float)piVar4[1] * *(float *)(*(int *)(unaff_EBP + -0x10) + 4);
                      pfVar10 = (float *)(*piVar4 * 0x10 + iVar11);
                      *pfVar10 = fVar2 * pfVar9[-2] + *pfVar10;
                      pfVar10 = (float *)(*piVar4 * 0x10 + 4 + iVar11);
                      *pfVar10 = fVar2 * pfVar9[-1] + *pfVar10;
                      pfVar10 = (float *)(*piVar4 * 0x10 + 8 + iVar11);
                      *pfVar10 = fVar2 * *pfVar9 + *pfVar10;
                      pfVar10 = (float *)(*piVar4 * 0x10 + 0xc + iVar11);
                      piVar4 = piVar4 + 2;
                      *pfVar10 = fVar2 * pfVar9[1] + *pfVar10;
                    } while (piVar4 < piVar8);
                    piVar3 = *(int **)(unaff_EBP + -0x1c);
                  }
                  *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 8;
                  if (piVar3 <= *(int **)(unaff_EBP + -0x10)) break;
                  piVar7 = *(int **)(unaff_EBP + -0x10);
                }
              }
              pfVar9 = pfVar9 + 4;
              piVar4 = piVar8;
            } while (piVar8 < *(int **)(unaff_EBP + -0x2c));
          }
          piVar4 = *(int **)(unaff_EBP + -0x30);
          if (piVar4 < piVar3) {
            do {
              puVar12 = (undefined4 *)(*(int *)(unaff_EBP + -0x14) + *piVar4 * 0xc);
              piVar3 = puVar12 + 2;
              *piVar3 = *piVar3 + -1;
              if (*piVar3 == 0) {
                (**(code **)(*(int *)extraout_ECX[1] + 8))(*piVar4,0,*puVar12);
                puVar12[1] = *(undefined4 *)(unaff_EBP + -0x18);
                *(undefined4 **)(unaff_EBP + -0x18) = puVar12;
              }
              piVar4 = piVar4 + 2;
            } while (piVar4 < *(int **)(unaff_EBP + -0x1c));
            piVar3 = *(int **)(unaff_EBP + -0x1c);
          }
          arg2 = (char)unaff_EDI;
          *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x28) + 1;
        } while (piVar3 < *(int **)(unaff_EBP + -0x44));
      }
      iVar11 = 0;
    }
  }
  if (*(void **)(unaff_EBP + -0x34) != (void *)0x0) {
    grim_mesh_vertex_buffer_free(*(void **)(unaff_EBP + -0x34),(int *)0x3,arg2);
  }
  operator_delete(*(void **)(unaff_EBP + -0x20));
  operator_delete(*(void **)(unaff_EBP + -0x38));
  operator_delete(*(void **)(unaff_EBP + -0x3c));
  operator_delete((void *)0x0);
LAB_10015ff8:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar11;
}



/* grim_model_load_from_zip @ 10016131 */

/* [binja] int32_t __fastcall sub_10016131(char* arg1) */

int __fastcall grim_model_load_from_zip(char *arg1)

{
  int *piVar1;
  
  piVar1 = *(int **)(arg1 + 8);
  if ((piVar1 != (int *)0x0) || (piVar1 = *(int **)(arg1 + 4), piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x28))(piVar1);
  }
  if ((((*(int *)(arg1 + 4) != 0) && (*(int *)(arg1 + 8) != 0)) &&
      (piVar1 = *(int **)(arg1 + 0xc), piVar1 != (int *)0x0)) && ((*arg1 & 1U) == 0)) {
    (**(code **)(*piVar1 + 0x70))(piVar1,*(int *)(arg1 + 8),0,0,*(int *)(arg1 + 4),0);
  }
  piVar1 = *(int **)(arg1 + 8);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    arg1[8] = '\0';
    arg1[9] = '\0';
    arg1[10] = '\0';
    arg1[0xb] = '\0';
  }
  piVar1 = *(int **)(arg1 + 0xc);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    arg1[0xc] = '\0';
    arg1[0xd] = '\0';
    arg1[0xe] = '\0';
    arg1[0xf] = '\0';
  }
  arg1[4] = '\0';
  arg1[5] = '\0';
  arg1[6] = '\0';
  arg1[7] = '\0';
  return 0;
}



/* grim_mesh_converter_destroy @ 10017345 */

/* [binja] void*** __thiscall sub_10017345(void*** arg1, char arg2) */

void *** __thiscall grim_mesh_converter_destroy(void *this,void ***arg1,char arg2)

{
  grim_vertex_space_converter_destroy(this);
  if (((uint)arg1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}



/* grim_mesh_converter_alloc @ 10017361 */

/* [binja] int32_t __thiscall sub_10017361(void* arg1, void* arg2) */

int grim_mesh_converter_alloc(void *arg1,void *arg2)

{
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  int extraout_ECX;
  int unaff_EBP;
  
  seh_prolog();
  if (*(int *)(extraout_ECX + 8) != *(int *)(*(int *)(unaff_EBP + 8) + 8)) {
    iVar3 = *(int *)(extraout_ECX + 0x1058);
    pvVar1 = operator_new(iVar3 << 4);
    *(void **)(unaff_EBP + -0x10) = pvVar1;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    pvVar2 = (void *)0x0;
    if (pvVar1 != (void *)0x0) {
      _vector_constructor_iterator_(pvVar1,0x10,iVar3,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      pvVar2 = pvVar1;
    }
    *(void **)(extraout_ECX + 0x104c) = pvVar2;
    if (pvVar2 == (void *)0x0) {
      iVar3 = -0x7ff8fff2;
      goto LAB_100173cd;
    }
    *(undefined4 *)(extraout_ECX + 0x1048) = *(undefined4 *)(*(int *)(unaff_EBP + 8) + 8);
  }
  iVar3 = 0;
LAB_100173cd:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar3;
}


