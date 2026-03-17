/* grim_mipmap_blit_2d @ 1000bbfc */

/* [binja] int32_t __stdcall sub_1000bbfc(int32_t* arg1, int32_t* arg2, int32_t* arg3, int32_t*
   arg4, int32_t* arg5, int32_t arg6, int32_t arg7) */

int grim_mipmap_blit_2d(int *arg1,int *arg2,int *arg3,int *arg4,int *arg5,int arg6,int arg7)

{
  int *arg2_00;
  int iVar1;
  int *piVar2;
  int unaff_EDI;
  int *piVar3;
  bool bVar4;
  int in_stack_00000020;
  int local_a0;
  int local_9c;
  int local_98;
  int local_78 [9];
  undefined1 local_54 [24];
  int local_3c;
  int local_38;
  int local_34 [4];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  grim_zip_reader_init(local_34);
  arg2_00 = arg4;
  if (arg1 == (int *)0x0) {
    iVar1 = -0x7789f794;
    goto LAB_1000bd90;
  }
  if (arg4 == (int *)0x0) {
    iVar1 = -0x7789f794;
    goto LAB_1000bd90;
  }
  if (((arg7 & 0xffffU) == 5) || (in_stack_00000020 != 0)) {
LAB_1000bd39:
    iVar1 = 1;
    if (arg1 == arg2_00) {
      iVar1 = 0x10001;
    }
    iVar1 = grim_zip_read_header(local_34,(char *)&local_a0,arg2_00,arg5,arg6,(int *)0x0,iVar1,unaff_EDI);
    if ((iVar1 < 0) ||
       (iVar1 = grim_image_load_from_memory(arg1,(int)arg2,arg3,local_a0,local_9c,local_98,(int)arg5,local_78,arg7,
                             in_stack_00000020), iVar1 < 0)) goto LAB_1000bd90;
  }
  else {
    if (arg2 != arg5) {
      if ((arg2 != (int *)0x0) && (arg5 != (int *)0x0)) {
        iVar1 = 0x100;
        bVar4 = true;
        piVar2 = arg2;
        piVar3 = arg5;
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar4 = *piVar2 == *piVar3;
          piVar2 = piVar2 + 1;
          piVar3 = piVar3 + 1;
        } while (bVar4);
        if (bVar4) goto LAB_1000bc77;
      }
      goto LAB_1000bd39;
    }
LAB_1000bc77:
    if (arg3 == (int *)0x0) {
      (**(code **)(*arg1 + 0x20))(arg1,local_54);
      local_14 = 0;
      local_10 = 0;
      local_c = local_3c;
      local_8 = local_38;
    }
    else {
      local_14 = *arg3;
      local_10 = arg3[1];
      local_c = arg3[2];
      local_8 = arg3[3];
    }
    if (arg6 == 0) {
      (**(code **)(*arg2_00 + 0x20))(arg2_00,local_54);
      local_24 = 0;
      local_20 = 0;
      local_1c = local_3c;
      local_18 = local_38;
    }
    else {
      local_24 = *(int *)arg6;
      local_20 = *(int *)(arg6 + 4);
      local_1c = *(int *)(arg6 + 8);
      local_18 = *(int *)(arg6 + 0xc);
    }
    if ((local_c - local_14 != local_1c - local_24) || (local_8 - local_10 != local_18 - local_20))
    goto LAB_1000bd39;
    (**(code **)(*arg2_00 + 0xc))(arg2_00,&arg4);
    grim_d3d_debug_set_mute(1);
    iVar1 = (**(code **)(*arg4 + 0x70))(arg4,arg2_00,&local_24,1,arg1,&local_14);
    grim_d3d_debug_set_mute(0);
    (**(code **)(*arg4 + 8))(arg4);
    if (iVar1 < 0) goto LAB_1000bd39;
  }
  iVar1 = 0;
LAB_1000bd90:
  grim_zip_reader_close((char *)local_34);
  return iVar1;
}



/* grim_mipmap_blit_3d @ 1000bda2 */

/* [binja] int32_t __stdcall sub_1000bda2(int32_t* arg1, int32_t arg2, int32_t arg3, int32_t* arg4,
   int32_t arg5, int32_t arg6, int32_t arg7, int32_t arg8) */

int grim_mipmap_blit_3d(int *arg1,int arg2,int arg3,int *arg4,int arg5,int arg6,int arg7,int arg8)

{
  int iVar1;
  int unaff_ESI;
  int iVar2;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 local_2c [36];
  int local_8;
  
  grim_zip_buffer_init(&local_8);
  if ((arg1 == (int *)0x0) || (arg4 == (int *)0x0)) {
    iVar2 = -0x7789f794;
  }
  else {
    iVar1 = 1;
    if (arg1 == arg4) {
      iVar1 = 0x10001;
    }
    iVar1 = grim_zip_read_entry(&local_8,&local_54,arg4,(int *)arg5,arg6,0,iVar1,unaff_ESI);
    if (-1 < iVar1) {
      iVar1 = grim_image_load_from_file_ex(arg1,arg2,arg3,local_54,local_50,local_4c,local_48,arg5,(int)local_2c,
                           arg7,arg8);
      iVar2 = 0;
      if (-1 < iVar1) goto LAB_1000be19;
    }
    iVar2 = iVar1;
  }
LAB_1000be19:
  thunk_grim_zip_buffer_free(&local_8);
  return iVar2;
}



/* grim_mipmap_create @ 1000c1e8 */

/* [binja] void* __stdcall sub_1000c1e8(int32_t arg1, int32_t arg2, int32_t* arg3, int32_t arg4) */

void * grim_mipmap_create(int arg1,int arg2,int *arg3,int arg4)

{
  void *pvVar1;
  
  pvVar1 = (void *)grim_texture_create_ex();
  return pvVar1;
}



/* grim_mipmap_generate @ 1000c205 */

/* [binja] int32_t __stdcall sub_1000c205(int32_t* arg1, int32_t* arg2, int32_t arg3, int32_t arg4)
    */

int grim_mipmap_generate(int *arg1,int *arg2,int arg3,int arg4)

{
  int *piVar1;
  int iVar2;
  int **ppiVar3;
  uint uVar4;
  bool bVar5;
  undefined1 local_68 [20];
  uint local_54;
  uint local_50;
  uint local_4c;
  undefined1 local_48 [24];
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int *local_1c;
  uint local_18;
  int local_14;
  int *local_10;
  int *local_c;
  int *local_8;
  
  piVar1 = arg1;
  if ((arg1 == (int *)0x0) ||
     (((local_14 = (**(code **)(*arg1 + 0x28))(arg1), local_14 != 3 && (local_14 != 4)) &&
      (local_14 != 5)))) {
    return -0x7789f794;
  }
  local_1c = piVar1;
  iVar2 = 5;
  if (arg4 != -1) goto LAB_1000c2a7;
  if (local_14 == 3) {
    (**(code **)(*piVar1 + 0x38))(piVar1,0,local_48);
    if (((local_30 & local_30 - 1) == 0) && (arg4 = iVar2, (local_2c & local_2c - 1) == 0))
    goto LAB_1000c2a7;
    arg4 = 0;
LAB_1000c2f6:
    bVar5 = arg4 != 0;
    arg4 = iVar2;
    if (bVar5) goto LAB_1000c2a7;
  }
  else {
    if (local_14 == 4) {
      (**(code **)(*piVar1 + 0x38))(piVar1,0,local_68);
      if ((local_54 & local_54 - 1) != 0) goto LAB_1000c2a0;
      local_30 = local_50 & local_50 - 1;
    }
    else {
      if (local_14 != 5) goto LAB_1000c2f6;
      (**(code **)(*piVar1 + 0x38))(piVar1,0,local_48);
      local_30 = local_30 & local_30 - 1;
      local_4c = local_2c;
    }
    if ((local_30 == 0) && (arg4 = iVar2, (local_4c & local_4c - 1) == 0)) goto LAB_1000c2a7;
  }
LAB_1000c2a0:
  arg4 = 0x80004;
LAB_1000c2a7:
  if (local_14 == 5) {
    arg4 = arg4 | 0x70000;
  }
  local_24 = (**(code **)(*piVar1 + 0x34))(piVar1);
  if (arg3 == -1) {
    arg3 = 0;
  }
  if ((uint)arg3 < local_24) {
    arg1 = (int *)0x0;
    local_c = (int *)0x0;
    local_8 = (int *)0x0;
    local_10 = (int *)0x0;
    local_28 = ((local_14 != 5) - 1 & 5) + 1;
    if (((arg4 & 0xffU) == 2) || (local_20 = 0, (arg4 & 0xffU) == 5)) {
      local_20 = 1;
    }
    local_18 = 0;
    iVar2 = arg4;
    if (local_28 != 0) {
      do {
        if (local_14 == 3) {
          ppiVar3 = &arg1;
LAB_1000c370:
          iVar2 = (**(code **)(*local_1c + 0x3c))(local_1c,arg3,ppiVar3);
        }
        else {
          if (local_14 == 4) {
            ppiVar3 = &local_c;
            goto LAB_1000c370;
          }
          if (local_14 == 5) {
            iVar2 = (**(code **)(*local_1c + 0x3c))(local_1c,local_18,arg3,&arg1);
          }
        }
        uVar4 = arg3;
        if (iVar2 < 0) goto LAB_1000c4a3;
LAB_1000c468:
        uVar4 = uVar4 + 1;
        if (uVar4 < local_24) {
          if (local_14 == 3) {
            ppiVar3 = &local_8;
LAB_1000c3b8:
            iVar2 = (**(code **)(*local_1c + 0x3c))(local_1c,uVar4,ppiVar3);
          }
          else {
            if (local_14 == 4) {
              ppiVar3 = &local_10;
              goto LAB_1000c3b8;
            }
            if (local_14 == 5) {
              iVar2 = (**(code **)(*local_1c + 0x3c))(local_1c,local_18,uVar4,&local_8);
            }
          }
          if (-1 < iVar2) {
            if (local_14 == 3) {
LAB_1000c3db:
              iVar2 = grim_mipmap_blit_2d(local_8,arg2,(int *)0x0,arg1,arg2,0,arg4);
            }
            else if (local_14 == 4) {
              iVar2 = grim_mipmap_blit_3d(local_10,(int)arg2,0,local_c,(int)arg2,0,arg4,0);
            }
            else if (local_14 == 5) goto LAB_1000c3db;
            if (-1 < iVar2) {
              if (local_20 == 0) goto LAB_1000c448;
              if (arg1 != (int *)0x0) {
                (**(code **)(*arg1 + 8))(arg1);
                arg1 = (int *)0x0;
              }
              if (local_c != (int *)0x0) {
                (**(code **)(*local_c + 8))(local_c);
              }
              arg1 = local_8;
              local_8 = (int *)0x0;
              local_c = local_10;
              goto LAB_1000c465;
            }
          }
          goto LAB_1000c4a3;
        }
        if (arg1 != (int *)0x0) {
          (**(code **)(*arg1 + 8))(arg1);
          arg1 = (int *)0x0;
        }
        if (local_c != (int *)0x0) {
          (**(code **)(*local_c + 8))(local_c);
          local_c = (int *)0x0;
        }
        local_18 = local_18 + 1;
      } while (local_18 < local_28);
    }
    iVar2 = 0;
LAB_1000c4a3:
    if (arg1 != (int *)0x0) {
      (**(code **)(*arg1 + 8))(arg1);
      arg1 = (int *)0x0;
    }
    if (local_c != (int *)0x0) {
      (**(code **)(*local_c + 8))(local_c);
      local_c = (int *)0x0;
    }
    if (local_8 != (int *)0x0) {
      (**(code **)(*local_8 + 8))(local_8);
      local_8 = (int *)0x0;
    }
    if (local_10 != (int *)0x0) {
      (**(code **)(*local_10 + 8))(local_10);
    }
  }
  else {
    iVar2 = -0x7789f794;
  }
  return iVar2;
LAB_1000c448:
  if (local_8 != (int *)0x0) {
    (**(code **)(*local_8 + 8))(local_8);
    local_8 = (int *)0x0;
  }
  if (local_10 != (int *)0x0) {
    (**(code **)(*local_10 + 8))(local_10);
LAB_1000c465:
    local_10 = (int *)0x0;
  }
  goto LAB_1000c468;
}



/* grim_mipmap_copy_dxt @ 10013007 */

/* [binja] int32_t __fastcall sub_10013007(int32_t* arg1) */

int __fastcall grim_mipmap_copy_dxt(int *arg1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iStack_2c;
  uint local_14;
  undefined4 *local_10;
  uint local_c;
  undefined4 *local_8;
  
  iVar4 = *arg1;
  if (((*(uint *)(iVar4 + 0x103c) | *(uint *)(iVar4 + 0x1038) | *(uint *)(iVar4 + 0x1030) |
       *(uint *)(iVar4 + 0x1034)) & 3) != 0) {
    return -0x7fffbffb;
  }
  iVar1 = arg1[1];
  if (((*(uint *)(iVar1 + 0x103c) | *(uint *)(iVar1 + 0x1038) | *(uint *)(iVar1 + 0x1030) |
       *(uint *)(iVar1 + 0x1034)) & 3) == 0) {
    iVar2 = *(int *)(iVar1 + 4);
    if (iVar2 == 0x31545844) {
      iStack_2c = 8;
    }
    else {
      if ((((iVar2 != 0x32545844) && (iVar2 != 0x33545844)) && (iVar2 != 0x34545844)) &&
         (iVar2 != 0x35545844)) goto LAB_1001306a;
      iStack_2c = 0x10;
    }
    uVar3 = *(uint *)(iVar1 + 0x1058);
    local_10 = (undefined4 *)
               ((*(uint *)(iVar1 + 0x1034) >> 2) * *(int *)(iVar1 + 0x1050) +
                *(int *)(iVar1 + 0x1054) * *(int *)(iVar1 + 0x1040) +
                (*(uint *)(iVar1 + 0x1030) >> 2) * iStack_2c + *(int *)(iVar1 + 0x18));
    local_14 = 0;
    puVar7 = (undefined4 *)
             ((*(uint *)(iVar4 + 0x1034) >> 2) * *(int *)(iVar4 + 0x1050) +
              *(int *)(iVar4 + 0x1054) * *(int *)(iVar4 + 0x1040) +
              (*(uint *)(iVar4 + 0x1030) >> 2) * iStack_2c + *(int *)(iVar4 + 0x18));
    if (*(int *)(iVar1 + 0x1060) != 0) {
      uVar5 = *(uint *)(iVar1 + 0x105c);
      do {
        local_c = 0;
        puVar6 = local_10;
        local_8 = puVar7;
        if (uVar5 != 0) {
          do {
            local_c = local_c + 4;
            puVar8 = local_8;
            puVar9 = puVar6;
            for (uVar5 = (uVar3 >> 2) * iStack_2c >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
              *puVar9 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar9 = puVar9 + 1;
            }
            for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
              *(undefined1 *)puVar9 = *(undefined1 *)puVar8;
              puVar8 = (undefined4 *)((int)puVar8 + 1);
              puVar9 = (undefined4 *)((int)puVar9 + 1);
            }
            puVar6 = (undefined4 *)((int)puVar6 + *(int *)(arg1[1] + 0x1050));
            uVar5 = *(uint *)(arg1[1] + 0x105c);
            local_8 = (undefined4 *)((int)local_8 + *(int *)(*arg1 + 0x1050));
          } while (local_c < uVar5);
        }
        local_10 = (undefined4 *)((int)local_10 + *(int *)(arg1[1] + 0x1054));
        puVar7 = (undefined4 *)((int)puVar7 + *(int *)(*arg1 + 0x1054));
        local_14 = local_14 + 1;
      } while (local_14 < *(uint *)(arg1[1] + 0x1060));
    }
    iVar4 = 0;
  }
  else {
LAB_1001306a:
    iVar4 = -0x7fffbffb;
  }
  return iVar4;
}



/* grim_mipmap_box_filter_bgra @ 10013195 */

undefined4 __cdecl
grim_mipmap_box_filter_bgra(uint *param_1,uint param_2,int param_3,uint param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int local_18;
  uint *local_c;
  
  uVar5 = param_4 * param_5 + param_2;
  if (param_2 < uVar5) {
    param_4 = param_2 + param_3 * 4;
    do {
      local_c = param_1;
      if (param_2 < param_4) {
        puVar6 = (uint *)(param_2 + 4);
        local_18 = ((param_4 - param_2) - 1 >> 3) + 1;
        do {
          uVar1 = *(uint *)((int)puVar6 + param_5);
          uVar2 = *(uint *)(param_5 + -4 + (int)puVar6);
          uVar3 = *puVar6;
          uVar4 = puVar6[-1];
          *local_c = ((uVar4 >> 2 & 0xffc03fc0) + (uVar2 >> 2 & 0xffc03fc0) +
                      (uVar1 >> 2 & 0xffc03fc0) + -0x7fff80 + (uVar3 >> 2 & 0xffc03fc0) ^
                     (uVar4 & 0xff00ff) + (uVar2 & 0xff00ff) + (uVar1 & 0xff00ff) + 0x20002 +
                     (uVar3 & 0xff00ff) >> 2) & 0xff00ff ^
                     (uVar4 >> 2 & 0x3fc03fc0) + (uVar2 >> 2 & 0x3fc03fc0) +
                     (uVar1 >> 2 & 0x3fc03fc0) + 0x800080 + (uVar3 >> 2 & 0x3fc03fc0);
          puVar6 = puVar6 + 2;
          local_18 = local_18 + -1;
          local_c = local_c + 1;
        } while (local_18 != 0);
      }
      param_1 = (uint *)((int)param_1 + param_6);
      param_4 = param_4 + param_5 * 2;
      param_2 = param_2 + param_5 * 2;
    } while (param_2 < uVar5);
  }
  return 0;
}



/* grim_mipmap_downsample_dispatch @ 100132bb */

/* [binja] int32_t __fastcall sub_100132bb(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_dispatch(int *arg1)

{
  int iVar1;
  
  iVar1 = *arg1;
  iVar1 = (*(code *)grim_mipmap_filter_func)
                    (*(undefined4 *)(arg1[1] + 0x18),*(undefined4 *)(iVar1 + 0x18),
                     *(undefined4 *)(iVar1 + 0x1058),*(undefined4 *)(iVar1 + 0x105c),
                     *(undefined4 *)(iVar1 + 0x1050),*(undefined4 *)(arg1[1] + 0x1050));
  return iVar1;
}



/* grim_mipmap_box_filter_rgb @ 100132ec */

undefined4 __cdecl
grim_mipmap_box_filter_rgb(uint *param_1,uint param_2,int param_3,uint param_4,int param_5,int param_6)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  int local_14;
  uint *local_8;
  
  uVar5 = param_4 * param_5 + param_2;
  if (param_2 < uVar5) {
    param_4 = param_2 + param_3 * 4;
    do {
      local_8 = param_1;
      if (param_2 < param_4) {
        local_14 = ((param_4 - param_2) - 1 >> 3) + 1;
        puVar6 = (uint *)(param_2 + 4);
        do {
          puVar2 = (uint *)((int)puVar6 + param_5);
          uVar3 = *puVar6;
          uVar4 = *(uint *)(param_5 + -4 + (int)puVar6);
          puVar1 = puVar6 + -1;
          puVar6 = puVar6 + 2;
          local_14 = local_14 + -1;
          *local_8 = ((*puVar1 & 0xff00ff) + (uVar4 & 0xff00ff) + (*puVar2 & 0xff00ff) + 0x20002 +
                      (uVar3 & 0xff00ff) & 0x3fc03fc |
                     (*puVar1 & 0xff00) + (uVar4 & 0xff00) + (*puVar2 & 0xff00) + 0x200 +
                     (uVar3 & 0xff00) & 0x3fc00) >> 2;
          local_8 = local_8 + 1;
        } while (local_14 != 0);
      }
      param_1 = (uint *)((int)param_1 + param_6);
      param_4 = param_4 + param_5 * 2;
      param_2 = param_2 + param_5 * 2;
    } while (param_2 < uVar5);
  }
  return 0;
}



/* grim_mipmap_box_filter_mmx @ 100133d4 */

undefined4 __cdecl
grim_mipmap_box_filter_mmx(uint *param_1,undefined8 *param_2,uint param_3,uint param_4,int param_5,int param_6)

{
  undefined8 uVar1;
  undefined8 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  uint *puVar11;
  undefined4 uVar12;
  undefined8 *puVar13;
  undefined8 *puVar14;
  undefined8 *puVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  
  if ((param_3 & 3) == 0) {
    puVar13 = (undefined8 *)(param_4 * param_5 + (int)param_2);
    for (; (int)param_2 < (int)puVar13; param_2 = (undefined8 *)((int)param_2 + param_5 * 2)) {
      puVar14 = (undefined8 *)((int)param_2 + param_5);
      puVar11 = param_1;
      puVar15 = param_2;
      while ((int)puVar15 < (int)((int)param_2 + param_3 * 4)) {
        uVar16 = *puVar15;
        uVar17 = *puVar14;
        uVar1 = puVar15[1];
        uVar2 = puVar14[1];
        puVar15 = puVar15 + 2;
        puVar14 = puVar14 + 2;
        uVar16 = psraw(CONCAT26((ushort)(byte)((ulonglong)uVar16 >> 0x18) +
                                (ushort)(byte)((ulonglong)uVar16 >> 0x38) +
                                (ushort)(byte)((ulonglong)uVar17 >> 0x18) +
                                (ushort)(byte)((ulonglong)uVar17 >> 0x38) + 2,
                                CONCAT24((ushort)(byte)((ulonglong)uVar16 >> 0x10) +
                                         (ushort)(byte)((ulonglong)uVar16 >> 0x30) +
                                         (ushort)(byte)((ulonglong)uVar17 >> 0x10) +
                                         (ushort)(byte)((ulonglong)uVar17 >> 0x30) + 2,
                                         CONCAT22((ushort)(byte)((ulonglong)uVar16 >> 8) +
                                                  (ushort)(byte)((ulonglong)uVar16 >> 0x28) +
                                                  (ushort)(byte)((ulonglong)uVar17 >> 8) +
                                                  (ushort)(byte)((ulonglong)uVar17 >> 0x28) + 2,
                                                  (ushort)(byte)uVar16 +
                                                  (ushort)(byte)((ulonglong)uVar16 >> 0x20) +
                                                  (ushort)(byte)uVar17 +
                                                  (ushort)(byte)((ulonglong)uVar17 >> 0x20) + 2))),2
                      );
        uVar17 = psraw(CONCAT26((ushort)(byte)((ulonglong)uVar1 >> 0x18) +
                                (ushort)(byte)((ulonglong)uVar1 >> 0x38) +
                                (ushort)(byte)((ulonglong)uVar2 >> 0x18) +
                                (ushort)(byte)((ulonglong)uVar2 >> 0x38) + 2,
                                CONCAT24((ushort)(byte)((ulonglong)uVar1 >> 0x10) +
                                         (ushort)(byte)((ulonglong)uVar1 >> 0x30) +
                                         (ushort)(byte)((ulonglong)uVar2 >> 0x10) +
                                         (ushort)(byte)((ulonglong)uVar2 >> 0x30) + 2,
                                         CONCAT22((ushort)(byte)((ulonglong)uVar1 >> 8) +
                                                  (ushort)(byte)((ulonglong)uVar1 >> 0x28) +
                                                  (ushort)(byte)((ulonglong)uVar2 >> 8) +
                                                  (ushort)(byte)((ulonglong)uVar2 >> 0x28) + 2,
                                                  (ushort)(byte)uVar1 +
                                                  (ushort)(byte)((ulonglong)uVar1 >> 0x20) +
                                                  (ushort)(byte)uVar2 +
                                                  (ushort)(byte)((ulonglong)uVar2 >> 0x20) + 2))),2)
        ;
        sVar3 = (short)uVar16;
        sVar4 = (short)((ulonglong)uVar16 >> 0x10);
        sVar5 = (short)((ulonglong)uVar16 >> 0x20);
        sVar6 = (short)((ulonglong)uVar16 >> 0x30);
        sVar7 = (short)uVar17;
        sVar8 = (short)((ulonglong)uVar17 >> 0x10);
        sVar9 = (short)((ulonglong)uVar17 >> 0x20);
        sVar10 = (short)((ulonglong)uVar17 >> 0x30);
        *(ulonglong *)puVar11 =
             CONCAT17((0 < sVar10) * (sVar10 < 0x100) * (char)((ulonglong)uVar17 >> 0x30) -
                      (0xff < sVar10),
                      CONCAT16((0 < sVar9) * (sVar9 < 0x100) * (char)((ulonglong)uVar17 >> 0x20) -
                               (0xff < sVar9),
                               CONCAT15((0 < sVar8) * (sVar8 < 0x100) *
                                        (char)((ulonglong)uVar17 >> 0x10) - (0xff < sVar8),
                                        CONCAT14((0 < sVar7) * (sVar7 < 0x100) * (char)uVar17 -
                                                 (0xff < sVar7),
                                                 CONCAT13((0 < sVar6) * (sVar6 < 0x100) *
                                                          (char)((ulonglong)uVar16 >> 0x30) -
                                                          (0xff < sVar6),
                                                          CONCAT12((0 < sVar5) * (sVar5 < 0x100) *
                                                                   (char)((ulonglong)uVar16 >> 0x20)
                                                                   - (0xff < sVar5),
                                                                   CONCAT11((0 < sVar4) *
                                                                            (sVar4 < 0x100) *
                                                                            (char)((ulonglong)uVar16
                                                                                  >> 0x10) -
                                                                            (0xff < sVar4),
                                                                            (0 < sVar3) *
                                                                            (sVar3 < 0x100) *
                                                                            (char)uVar16 -
                                                                            (0xff < sVar3))))))));
        puVar11 = puVar11 + 2;
      }
      param_1 = (uint *)((int)param_1 + param_6);
    }
    return 0;
  }
  uVar12 = grim_mipmap_box_filter_bgra(param_1,(uint)param_2,param_3,param_4,param_5,param_6);
  return uVar12;
}



/* grim_mipmap_select_filter @ 100134ea */

void grim_mipmap_select_filter(void)

{
  int iVar1;
  
  iVar1 = grim_jpg_start_decompress();
  if (iVar1 == 0) {
    grim_mipmap_filter_func = grim_mipmap_box_filter_bgra;
    grim_mipmap_filter_func_2 = grim_mipmap_box_filter_rgb;
  }
  else {
    grim_mipmap_filter_func = grim_mipmap_box_filter_mmx;
    grim_mipmap_filter_func_2 = grim_mipmap_box_filter_mmx;
  }
                    /* WARNING: Could not recover jumptable at 0x1001351c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)grim_mipmap_filter_func)();
  return;
}



/* grim_mipmap_select_filter_2 @ 10013522 */

void grim_mipmap_select_filter_2(void)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  
  iVar1 = grim_jpg_start_decompress();
  if (iVar1 == 0) {
    grim_mipmap_filter_func = grim_mipmap_box_filter_bgra;
    UNRECOVERED_JUMPTABLE = grim_mipmap_box_filter_rgb;
  }
  else {
    UNRECOVERED_JUMPTABLE = grim_mipmap_box_filter_mmx;
    grim_mipmap_filter_func = grim_mipmap_box_filter_mmx;
  }
  grim_mipmap_filter_func_2 = UNRECOVERED_JUMPTABLE;
                    /* WARNING: Could not recover jumptable at 0x1001354f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* grim_mipmap_downsample_2 @ 10013551 */

/* [binja] int32_t __fastcall sub_10013551(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_2(int *arg1)

{
  int iVar1;
  
  iVar1 = *arg1;
  iVar1 = (*(code *)grim_mipmap_filter_func_2)
                    (*(undefined4 *)(arg1[1] + 0x18),*(undefined4 *)(iVar1 + 0x18),
                     *(undefined4 *)(iVar1 + 0x1058),*(undefined4 *)(iVar1 + 0x105c),
                     *(undefined4 *)(iVar1 + 0x1050),*(undefined4 *)(arg1[1] + 0x1050));
  return iVar1;
}



/* grim_mipmap_downsample_argb_2x2 @ 10013582 */

/* [binja] int32_t __fastcall sub_10013582(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_argb_2x2(int *arg1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  
  puVar5 = *(ushort **)(arg1[1] + 0x18);
  iVar6 = *arg1;
  iVar7 = *(int *)(iVar6 + 0x1050);
  puVar8 = *(ushort **)(iVar6 + 0x18);
  puVar11 = (ushort *)(*(int *)(iVar6 + 0x105c) * iVar7 + (int)puVar8);
  for (; puVar8 < puVar11; puVar8 = puVar8 + iVar7) {
    iVar6 = *(int *)(iVar6 + 0x1058);
    puVar12 = (ushort *)(iVar7 + (int)puVar8);
    puVar9 = puVar5;
    for (puVar10 = puVar8; puVar10 < puVar8 + iVar6; puVar10 = puVar10 + 2) {
      uVar1 = *puVar10;
      uVar2 = puVar10[1];
      uVar3 = puVar12[1];
      uVar4 = *puVar12;
      *puVar9 = ((ushort)((uint)(uVar3 & 0xf81f) + (uint)(uVar1 & 0xf81f) + (uint)(uVar4 & 0xf81f) +
                          0x1002 + (uint)(uVar2 & 0xf81f) >> 2) ^
                (ushort)((uVar2 & 0xffff07e0) + 0x40 +
                         (uVar3 & 0xffff07e0) + (uVar1 & 0xffff07e0) + (uVar4 & 0xffff07e0) >> 2)) &
                0x7e0 ^ (ushort)((uVar3 & 0xf81f) + (uVar1 & 0xf81f) + (uVar4 & 0xf81f) + 0x1002 +
                                 (uVar2 & 0xf81f) >> 2);
      puVar12 = puVar12 + 2;
      puVar9 = puVar9 + 1;
    }
    puVar5 = (ushort *)((int)puVar5 + *(int *)(arg1[1] + 0x1050));
    iVar6 = *arg1;
    iVar7 = *(int *)(iVar6 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_rgb_2x2 @ 100136d2 */

/* [binja] int32_t __fastcall sub_100136d2(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_rgb_2x2(int *arg1)

{
  ushort *puVar1;
  ushort uVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  ushort *puVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  
  puVar3 = *(ushort **)(arg1[1] + 0x18);
  iVar4 = *arg1;
  iVar5 = *(int *)(iVar4 + 0x1050);
  puVar6 = *(ushort **)(iVar4 + 0x18);
  puVar8 = (ushort *)(*(int *)(iVar4 + 0x105c) * iVar5 + (int)puVar6);
  for (; puVar6 < puVar8; puVar6 = puVar6 + iVar5) {
    iVar4 = *(int *)(iVar4 + 0x1058);
    puVar9 = (ushort *)(iVar5 + (int)puVar6);
    puVar7 = puVar3;
    for (puVar10 = puVar6; puVar10 < puVar6 + iVar4; puVar10 = puVar10 + 2) {
      puVar1 = puVar9 + 1;
      uVar2 = *puVar9;
      puVar9 = puVar9 + 2;
      *puVar7 = (ushort)((puVar10[1] & 0xffff03e0) + 0x40 +
                         (*puVar1 & 0xffff03e0) + (*puVar10 & 0xffff03e0) + (uVar2 & 0xffff03e0) >>
                        2) & 0x3e0 |
                (ushort)((*puVar1 & 0x7c1f) + (*puVar10 & 0x7c1f) + (uVar2 & 0x7c1f) + 0x802 +
                         (puVar10[1] & 0x7c1f) >> 2) & 0x7c1f;
      puVar7 = puVar7 + 1;
    }
    puVar3 = (ushort *)((int)puVar3 + *(int *)(arg1[1] + 0x1050));
    iVar4 = *arg1;
    iVar5 = *(int *)(iVar4 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_a8r8g8b8 @ 100137f6 */

/* [binja] int32_t __fastcall sub_100137f6(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_a8r8g8b8(int *arg1)

{
  ushort *puVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  ushort *puVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  uint uVar10;
  ushort *puVar11;
  uint uVar12;
  
  puVar1 = *(ushort **)(arg1[1] + 0x18);
  iVar2 = *arg1;
  puVar3 = *(ushort **)(iVar2 + 0x18);
  iVar4 = *(int *)(iVar2 + 0x1050);
  puVar9 = (ushort *)(*(int *)(iVar2 + 0x105c) * iVar4 + (int)puVar3);
  for (; puVar3 < puVar9; puVar3 = puVar3 + iVar4) {
    iVar2 = *(int *)(iVar2 + 0x1058);
    puVar11 = (ushort *)(iVar4 + (int)puVar3);
    puVar5 = puVar1;
    for (puVar8 = puVar3; puVar8 < puVar3 + iVar2; puVar8 = puVar8 + 2) {
      uVar6 = (uint)*puVar8;
      uVar10 = (uint)puVar8[1];
      uVar7 = (uint)puVar11[1];
      uVar12 = (uint)*puVar11;
      *puVar5 = ((ushort)((uVar7 & 0x83e0) + (uVar6 & 0x83e0) + (uVar12 & 0x83e0) + 0x10040 +
                          (uVar10 & 0x83e0) >> 2) ^
                (ushort)((uVar10 & 0x7c1f) + 0x802 +
                         (uVar7 & 0x7c1f) + (uVar6 & 0x7c1f) + (uVar12 & 0x7c1f) >> 2)) & 0x7c1f ^
                (ushort)((uVar7 & 0x83e0) + (uVar6 & 0x83e0) + (uVar12 & 0x83e0) + 0x10040 +
                         (uVar10 & 0x83e0) >> 2);
      puVar11 = puVar11 + 2;
      puVar5 = puVar5 + 1;
    }
    puVar1 = (ushort *)((int)puVar1 + *(int *)(arg1[1] + 0x1050));
    iVar2 = *arg1;
    iVar4 = *(int *)(iVar2 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_x8r8g8b8 @ 10013945 */

/* [binja] int32_t __fastcall sub_10013945(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_x8r8g8b8(int *arg1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  
  puVar5 = *(ushort **)(arg1[1] + 0x18);
  iVar6 = *arg1;
  iVar7 = *(int *)(iVar6 + 0x1050);
  puVar8 = *(ushort **)(iVar6 + 0x18);
  puVar11 = (ushort *)(*(int *)(iVar6 + 0x105c) * iVar7 + (int)puVar8);
  for (; puVar8 < puVar11; puVar8 = puVar8 + iVar7) {
    iVar6 = *(int *)(iVar6 + 0x1058);
    puVar12 = (ushort *)(iVar7 + (int)puVar8);
    puVar9 = puVar5;
    for (puVar10 = puVar8; puVar10 < puVar8 + iVar6; puVar10 = puVar10 + 2) {
      uVar1 = *puVar10;
      uVar2 = puVar10[1];
      uVar3 = puVar12[1];
      uVar4 = *puVar12;
      *puVar9 = ((ushort)((uint)(uVar3 & 0xf0f0) + (uint)(uVar1 & 0xf0f0) + (uint)(uVar4 & 0xf0f0) +
                          0x2020 + (uint)(uVar2 & 0xf0f0) >> 2) ^
                (ushort)((uVar2 & 0xffff0f0f) + 0x202 +
                         (uVar3 & 0xffff0f0f) + (uVar1 & 0xffff0f0f) + (uVar4 & 0xffff0f0f) >> 2)) &
                0xf0f ^ (ushort)((uVar3 & 0xf0f0) + (uVar1 & 0xf0f0) + (uVar4 & 0xf0f0) + 0x2020 +
                                 (uVar2 & 0xf0f0) >> 2);
      puVar12 = puVar12 + 2;
      puVar9 = puVar9 + 1;
    }
    puVar5 = (ushort *)((int)puVar5 + *(int *)(arg1[1] + 0x1050));
    iVar6 = *arg1;
    iVar7 = *(int *)(iVar6 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_r5g6b5 @ 10013a98 */

/* [binja] int32_t __fastcall sub_10013a98(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_r5g6b5(int *arg1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  
  iVar5 = *arg1;
  pbVar10 = *(byte **)(arg1[1] + 0x18);
  pbVar6 = *(byte **)(iVar5 + 0x18);
  iVar7 = *(int *)(iVar5 + 0x1050);
  pbVar11 = pbVar6 + *(int *)(iVar5 + 0x105c) * iVar7;
  for (; pbVar6 < pbVar11; pbVar6 = pbVar6 + iVar7 * 2) {
    iVar5 = *(int *)(iVar5 + 0x1058);
    pbVar12 = pbVar6 + iVar7;
    pbVar8 = pbVar10;
    for (pbVar9 = pbVar6; pbVar9 < pbVar6 + iVar5; pbVar9 = pbVar9 + 2) {
      bVar1 = *pbVar9;
      bVar2 = pbVar9[1];
      bVar3 = pbVar12[1];
      bVar4 = *pbVar12;
      pbVar12 = pbVar12 + 2;
      *pbVar8 = ((byte)((bVar3 & 0x1c) + (bVar1 & 0x1c) + (bVar4 & 0x1c) + 8 + (bVar2 & 0x1c) >> 2)
                ^ (byte)((bVar3 & 0xffff00e3) + (bVar1 & 0xffff00e3) + (bVar4 & 0xffff00e3) + 0x42 +
                         (bVar2 & 0xffff00e3) >> 2)) & 0x1c ^
                (byte)((uint)(bVar3 & 0xe3) + (uint)(bVar1 & 0xe3) + (uint)(bVar4 & 0xe3) + 0x42 +
                       (uint)(bVar2 & 0xe3) >> 2);
      pbVar8 = pbVar8 + 1;
    }
    pbVar10 = pbVar10 + *(int *)(arg1[1] + 0x1050);
    iVar5 = *arg1;
    iVar7 = *(int *)(iVar5 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_a1r5g5b5 @ 10013bd7 */

/* [binja] int32_t __fastcall sub_10013bd7(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_a1r5g5b5(int *arg1)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  undefined1 *local_c;
  
  puVar4 = *(undefined1 **)(arg1[1] + 0x18);
  iVar2 = *arg1;
  pbVar3 = *(byte **)(iVar2 + 0x18);
  iVar7 = *(int *)(iVar2 + 0x1050);
  pbVar5 = pbVar3 + *(int *)(iVar2 + 0x105c) * iVar7;
  for (; pbVar3 < pbVar5; pbVar3 = pbVar3 + iVar7 * 2) {
    iVar2 = *(int *)(iVar2 + 0x1058);
    pbVar6 = pbVar3 + iVar7;
    local_c = puVar4;
    for (pbVar1 = pbVar3; pbVar1 < pbVar3 + iVar2; pbVar1 = pbVar1 + 2) {
      *local_c = (char)((uint)pbVar6[1] + (uint)pbVar1[1] + (uint)*pbVar6 + 2 + (uint)*pbVar1 >> 2);
      pbVar6 = pbVar6 + 2;
      local_c = local_c + 1;
    }
    puVar4 = puVar4 + *(int *)(arg1[1] + 0x1050);
    iVar2 = *arg1;
    iVar7 = *(int *)(iVar2 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_x1r5g5b5 @ 10013c72 */

/* [binja] int32_t __fastcall sub_10013c72(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_x1r5g5b5(int *arg1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  
  iVar5 = *arg1;
  puVar6 = *(ushort **)(arg1[1] + 0x18);
  iVar7 = *(int *)(iVar5 + 0x1050);
  puVar8 = *(ushort **)(iVar5 + 0x18);
  puVar12 = (ushort *)(*(int *)(iVar5 + 0x105c) * iVar7 + (int)puVar8);
  for (; puVar8 < puVar12; puVar8 = puVar8 + iVar7) {
    iVar5 = *(int *)(iVar5 + 0x1058);
    puVar11 = (ushort *)(iVar7 + (int)puVar8);
    puVar9 = puVar6;
    for (puVar10 = puVar8; puVar10 < puVar8 + iVar5; puVar10 = puVar10 + 2) {
      uVar1 = *puVar10;
      uVar2 = puVar10[1];
      uVar3 = puVar11[1];
      uVar4 = *puVar11;
      puVar11 = puVar11 + 2;
      *puVar9 = (byte)((byte)((uint)(uVar3 & 0xe3) + (uint)(uVar1 & 0xe3) + (uint)(uVar4 & 0xe3) +
                              0x42 + (uint)(uVar2 & 0xe3) >> 2) ^
                      (byte)((uint)(uVar3 & 0xff1c) + (uVar1 & 0xffffff1c) + (uint)(uVar4 & 0xff1c)
                             + 0x208 + (uint)(uVar2 & 0xff1c) >> 2)) & 0xe3 ^
                (ushort)((uVar3 & 0xff1c) + (uVar1 & 0xff1c) + (uVar4 & 0xff1c) + 0x208 +
                         (uVar2 & 0xff1c) >> 2);
      puVar9 = puVar9 + 1;
    }
    puVar6 = (ushort *)((int)puVar6 + *(int *)(arg1[1] + 0x1050));
    iVar5 = *arg1;
    iVar7 = *(int *)(iVar5 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_a4r4g4b4 @ 10013dbe */

/* [binja] int32_t __fastcall sub_10013dbe(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_a4r4g4b4(int *arg1)

{
  ushort *puVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  ushort *puVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  
  puVar9 = *(ushort **)(arg1[1] + 0x18);
  iVar3 = *arg1;
  puVar4 = *(ushort **)(iVar3 + 0x18);
  iVar5 = *(int *)(iVar3 + 0x1050);
  puVar7 = (ushort *)(*(int *)(iVar3 + 0x105c) * iVar5 + (int)puVar4);
  for (; puVar4 < puVar7; puVar4 = puVar4 + iVar5) {
    iVar3 = *(int *)(iVar3 + 0x1058);
    puVar10 = (ushort *)(iVar5 + (int)puVar4);
    puVar6 = puVar9;
    for (puVar8 = puVar4; puVar8 < puVar4 + iVar3; puVar8 = puVar8 + 2) {
      puVar1 = puVar10 + 1;
      uVar2 = *puVar10;
      puVar10 = puVar10 + 2;
      *puVar6 = (ushort)((*puVar1 & 0xffff00f0) + (*puVar8 & 0xffff00f0) + (uVar2 & 0xffff00f0) +
                         0x20 + (puVar8[1] & 0xffff00f0) >> 2) & 0xf0 |
                (ushort)((uint)(*puVar1 & 0xf0f) + (uint)(*puVar8 & 0xf0f) + (uint)(uVar2 & 0xf0f) +
                         0x202 + (uint)(puVar8[1] & 0xf0f) >> 2) & 0xf0f;
      puVar6 = puVar6 + 1;
    }
    puVar9 = (ushort *)((int)puVar9 + *(int *)(arg1[1] + 0x1050));
    iVar3 = *arg1;
    iVar5 = *(int *)(iVar3 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_x4r4g4b4 @ 10013edf */

/* [binja] int32_t __fastcall sub_10013edf(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_x4r4g4b4(int *arg1)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  
  iVar5 = *arg1;
  puVar6 = *(ushort **)(arg1[1] + 0x18);
  iVar7 = *(int *)(iVar5 + 0x1050);
  puVar8 = *(ushort **)(iVar5 + 0x18);
  puVar12 = (ushort *)(*(int *)(iVar5 + 0x105c) * iVar7 + (int)puVar8);
  for (; puVar8 < puVar12; puVar8 = puVar8 + iVar7) {
    iVar5 = *(int *)(iVar5 + 0x1058);
    puVar11 = (ushort *)(iVar7 + (int)puVar8);
    puVar9 = puVar6;
    for (puVar10 = puVar8; puVar10 < puVar8 + iVar5; puVar10 = puVar10 + 2) {
      uVar1 = *puVar10;
      uVar2 = puVar10[1];
      uVar3 = puVar11[1];
      uVar4 = *puVar11;
      puVar11 = puVar11 + 2;
      *puVar9 = (ushort)(byte)((byte)((uint)(uVar3 & 0xff) + (uint)(uVar1 & 0xff) +
                                      (uint)(uVar4 & 0xff) + 2 + (uint)(uVar2 & 0xff) >> 2) ^
                              (byte)((uint)(uVar3 & 0xff00) + (uVar1 & 0xffffff00) +
                                     (uint)(uVar4 & 0xff00) + 0x200 + (uint)(uVar2 & 0xff00) >> 2))
                ^ (ushort)((uVar3 & 0xff00) + (uVar1 & 0xff00) + (uVar4 & 0xff00) + 0x200 +
                           (uVar2 & 0xff00) >> 2);
      puVar9 = puVar9 + 1;
    }
    puVar6 = (ushort *)((int)puVar6 + *(int *)(arg1[1] + 0x1050));
    iVar5 = *arg1;
    iVar7 = *(int *)(iVar5 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_a8r3g3b2 @ 1001402b */

/* [binja] int32_t __fastcall sub_1001402b(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_a8r3g3b2(int *arg1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  
  iVar5 = *arg1;
  pbVar10 = *(byte **)(arg1[1] + 0x18);
  pbVar6 = *(byte **)(iVar5 + 0x18);
  iVar7 = *(int *)(iVar5 + 0x1050);
  pbVar11 = pbVar6 + *(int *)(iVar5 + 0x105c) * iVar7;
  for (; pbVar6 < pbVar11; pbVar6 = pbVar6 + iVar7 * 2) {
    iVar5 = *(int *)(iVar5 + 0x1058);
    pbVar12 = pbVar6 + iVar7;
    pbVar8 = pbVar10;
    for (pbVar9 = pbVar6; pbVar9 < pbVar6 + iVar5; pbVar9 = pbVar9 + 2) {
      bVar1 = *pbVar9;
      bVar2 = pbVar9[1];
      bVar3 = pbVar12[1];
      bVar4 = *pbVar12;
      pbVar12 = pbVar12 + 2;
      *pbVar8 = ((byte)((bVar3 & 0xf) + (bVar1 & 0xf) + (bVar4 & 0xf) + 2 + (bVar2 & 0xf) >> 2) ^
                (byte)((bVar3 & 0xffff00f0) + (bVar1 & 0xffff00f0) + (bVar4 & 0xffff00f0) + 0x20 +
                       (bVar2 & 0xffff00f0) >> 2)) & 0xf ^
                (byte)((uint)(bVar3 & 0xf0) + (uint)(bVar1 & 0xf0) + (uint)(bVar4 & 0xf0) + 0x20 +
                       (uint)(bVar2 & 0xf0) >> 2);
      pbVar8 = pbVar8 + 1;
    }
    pbVar10 = pbVar10 + *(int *)(arg1[1] + 0x1050);
    iVar5 = *arg1;
    iVar7 = *(int *)(iVar5 + 0x1050);
  }
  return 0;
}



/* grim_mipmap_downsample_dxt @ 1001416a */

/* [binja] int32_t __fastcall sub_1001416a(int32_t* arg1) */

int __fastcall grim_mipmap_downsample_dxt(int *arg1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 *puVar11;
  bool bVar12;
  uint local_14;
  uint local_10;
  uint local_8;
  
  iVar2 = arg1[1];
  iVar1 = *arg1;
  if (*(int *)(iVar2 + 4) != *(int *)(iVar1 + 4)) {
    return -0x7fffbffb;
  }
  if ((((*(int *)(iVar1 + 0x10) == 0) && (*(int *)(iVar2 + 0x1058) == *(int *)(iVar1 + 0x1058))) &&
      (local_14 = *(uint *)(iVar2 + 0x105c), local_14 == *(uint *)(iVar1 + 0x105c))) &&
     (*(int *)(iVar2 + 0x1060) == *(int *)(iVar1 + 0x1060))) {
    if (*(int *)(iVar2 + 0xc) == 0) {
      iVar1 = grim_mipmap_copy_dxt(arg1);
      return iVar1;
    }
    if (*(int *)(iVar2 + 0x14) != 0) {
      if ((int *)(iVar2 + 0x30) != (int *)(iVar1 + 0x30)) {
        iVar3 = 0x100;
        bVar12 = true;
        piVar8 = (int *)(iVar2 + 0x30);
        piVar10 = (int *)(iVar1 + 0x30);
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar12 = *piVar8 == *piVar10;
          piVar8 = piVar8 + 1;
          piVar10 = piVar10 + 1;
        } while (bVar12);
        if (!bVar12) goto LAB_10014298;
      }
    }
    local_8 = 0;
    if (*(int *)(iVar2 + 0x1060) != 0) {
      do {
        puVar6 = (undefined4 *)(*(int *)(iVar2 + 0x1054) * local_8 + *(int *)(iVar2 + 0x18));
        puVar7 = (undefined4 *)(*(int *)(*arg1 + 0x1054) * local_8 + *(int *)(*arg1 + 0x18));
        local_10 = 0;
        if (local_14 != 0) {
          do {
            uVar5 = *(uint *)(iVar2 + 0x1064);
            puVar9 = puVar7;
            puVar11 = puVar6;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *puVar11 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar11 = puVar11 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
              puVar9 = (undefined4 *)((int)puVar9 + 1);
              puVar11 = (undefined4 *)((int)puVar11 + 1);
            }
            iVar2 = arg1[1];
            puVar7 = (undefined4 *)((int)puVar7 + *(int *)(*arg1 + 0x1050));
            puVar6 = (undefined4 *)((int)puVar6 + *(int *)(iVar2 + 0x1050));
            local_14 = *(uint *)(iVar2 + 0x105c);
            local_10 = local_10 + 1;
          } while (local_10 < local_14);
        }
        local_8 = local_8 + 1;
        iVar2 = arg1[1];
      } while (local_8 < *(uint *)(iVar2 + 0x1060));
    }
    iVar1 = 0;
  }
  else {
LAB_10014298:
    iVar1 = -0x7fffbffb;
  }
  return iVar1;
}



/* grim_mipmap_level_create_generic @ 100142a2 */

/* [binja] int32_t __fastcall sub_100142a2(int32_t* arg1) */

int grim_mipmap_level_create_generic(int *arg1)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  int iVar5;
  int *extraout_ECX;
  uint uVar6;
  int unaff_EBP;
  uint uVar7;
  
  seh_prolog();
  iVar5 = extraout_ECX[1];
  iVar1 = *extraout_ECX;
  iVar2 = *(int *)(iVar5 + 0x1058);
  if (((iVar2 == *(int *)(iVar1 + 0x1058)) && (*(int *)(iVar5 + 0x105c) == *(int *)(iVar1 + 0x105c))
      ) && (*(int *)(iVar5 + 0x1060) == *(int *)(iVar1 + 0x1060))) {
    pvVar3 = operator_new(iVar2 << 4);
    *(void **)(unaff_EBP + -0x10) = pvVar3;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar3 == (void *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x10) = 0;
    }
    else {
      _vector_constructor_iterator_(pvVar3,0x10,iVar2,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      *(void **)(unaff_EBP + -0x10) = pvVar3;
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    uVar6 = 0;
    if (*(int *)(unaff_EBP + -0x10) != 0) {
      if (*(int *)(extraout_ECX[1] + 0x1060) != 0) {
        uVar4 = *(uint *)(extraout_ECX[1] + 0x105c);
        do {
          uVar7 = 0;
          if (uVar4 != 0) {
            do {
              (**(code **)(*(int *)*extraout_ECX + 4))
                        (uVar7,uVar6,*(undefined4 *)(unaff_EBP + -0x10));
              (**(code **)(*(int *)extraout_ECX[1] + 8))
                        (uVar7,uVar6,*(undefined4 *)(unaff_EBP + -0x10));
              uVar4 = *(uint *)(extraout_ECX[1] + 0x105c);
              uVar7 = uVar7 + 1;
            } while (uVar7 < uVar4);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < *(uint *)(extraout_ECX[1] + 0x1060));
      }
      operator_delete(*(void **)(unaff_EBP + -0x10));
      iVar5 = 0;
      goto LAB_10014384;
    }
  }
  iVar5 = -0x7fffbffb;
LAB_10014384:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar5;
}



/* grim_mipmap_chain_create_and_fill @ 10014393 */

/* [binja] int32_t __fastcall sub_10014393(int32_t* arg1) */

int grim_mipmap_chain_create_and_fill(int *arg1)

{
  int iVar1;
  void *pvVar2;
  int *extraout_ECX;
  int iVar3;
  int *piVar4;
  int unaff_EBP;
  uint uVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  
  seh_prolog();
  if ((char)extraout_ECX[2] == '\x01') {
    iVar1 = extraout_ECX[1];
    iVar3 = *extraout_ECX;
    uVar5 = *(uint *)(iVar1 + 0x1058);
    uVar7 = *(uint *)(iVar3 + 0x1058);
    *(uint *)(unaff_EBP + -0x18) = uVar5;
    if (uVar5 <= uVar7) {
      *(uint *)(unaff_EBP + -0x18) = uVar7;
    }
    uVar5 = *(uint *)(iVar1 + 0x105c);
    uVar7 = *(uint *)(iVar3 + 0x105c);
    *(uint *)(unaff_EBP + -0x20) = uVar5;
    if (uVar7 <= uVar5) {
      *(uint *)(unaff_EBP + -0x20) = uVar7;
    }
    uVar5 = *(uint *)(iVar1 + 0x1060);
    uVar7 = *(uint *)(iVar3 + 0x1060);
    *(uint *)(unaff_EBP + -0x1c) = uVar5;
    if (uVar7 <= uVar5) {
      *(uint *)(unaff_EBP + -0x1c) = uVar7;
    }
    uVar5 = *(int *)(unaff_EBP + -0x18) << 4;
    pvVar2 = operator_new(uVar5);
    *(void **)(unaff_EBP + -0x14) = pvVar2;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar2 == (void *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x10) = 0;
    }
    else {
      _vector_constructor_iterator_
                (pvVar2,0x10,*(int *)(unaff_EBP + -0x18),(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      *(undefined4 *)(unaff_EBP + -0x10) = *(undefined4 *)(unaff_EBP + -0x14);
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    if (*(int *)(unaff_EBP + -0x10) == 0) {
      iVar1 = -0x7fffbffb;
    }
    else {
      iVar1 = *(int *)(extraout_ECX[1] + 0x1058);
      *(int *)(unaff_EBP + -0x18) = iVar1;
      pvVar2 = operator_new(iVar1 << 4);
      *(void **)(unaff_EBP + -0x14) = pvVar2;
      *(undefined4 *)(unaff_EBP + -4) = 1;
      if (pvVar2 == (void *)0x0) {
        *(undefined4 *)(unaff_EBP + -0x18) = 0;
      }
      else {
        _vector_constructor_iterator_
                  (pvVar2,0x10,*(int *)(unaff_EBP + -0x18),(_func_void_ptr_void_ptr *)&LAB_1000ae4f)
        ;
        *(undefined4 *)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + -0x14);
      }
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      if (*(int *)(unaff_EBP + -0x18) == 0) {
        operator_delete(*(void **)(unaff_EBP + -0x10));
        iVar1 = -0x7fffbffb;
      }
      else {
        iVar1 = *(int *)(unaff_EBP + -0x1c);
        *(undefined4 *)(unaff_EBP + -0x14) = 0;
        puVar6 = *(undefined4 **)(unaff_EBP + -0x10);
        for (uVar5 = uVar5 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar6 = 0;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        puVar6 = *(undefined4 **)(unaff_EBP + -0x18);
        for (uVar5 = (uint)(*(int *)(extraout_ECX[1] + 0x1058) << 4) >> 2; uVar5 != 0;
            uVar5 = uVar5 - 1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
          *(undefined1 *)puVar6 = 0;
          puVar6 = (undefined4 *)((int)puVar6 + 1);
        }
        uVar5 = 0;
        if (iVar1 != 0) {
          do {
            uVar5 = *(uint *)(unaff_EBP + -0x20);
            uVar7 = 0;
            if (uVar5 != 0) {
              do {
                (**(code **)(*(int *)*extraout_ECX + 4))
                          (uVar7,*(undefined4 *)(unaff_EBP + -0x14),
                           *(undefined4 *)(unaff_EBP + -0x10));
                (**(code **)(*(int *)extraout_ECX[1] + 8))
                          (uVar7,*(undefined4 *)(unaff_EBP + -0x14),
                           *(undefined4 *)(unaff_EBP + -0x10));
                uVar7 = uVar7 + 1;
              } while (uVar7 < uVar5);
            }
            piVar4 = (int *)extraout_ECX[1];
            if (uVar5 < (uint)piVar4[0x417]) {
              do {
                (**(code **)(*piVar4 + 8))
                          (uVar5,*(undefined4 *)(unaff_EBP + -0x14),
                           *(undefined4 *)(unaff_EBP + -0x18));
                piVar4 = (int *)extraout_ECX[1];
                uVar5 = uVar5 + 1;
              } while (uVar5 < (uint)piVar4[0x417]);
            }
            uVar5 = *(uint *)(unaff_EBP + -0x1c);
            *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 1;
          } while (*(uint *)(unaff_EBP + -0x14) < uVar5);
        }
        piVar4 = (int *)extraout_ECX[1];
        if (uVar5 < (uint)piVar4[0x418]) {
          uVar7 = piVar4[0x417];
          do {
            uVar8 = 0;
            if (uVar7 != 0) {
              do {
                (**(code **)(*piVar4 + 8))(uVar8,uVar5,*(undefined4 *)(unaff_EBP + -0x18));
                piVar4 = (int *)extraout_ECX[1];
                uVar7 = piVar4[0x417];
                uVar8 = uVar8 + 1;
              } while (uVar8 < uVar7);
            }
            piVar4 = (int *)extraout_ECX[1];
            uVar5 = uVar5 + 1;
          } while (uVar5 < (uint)piVar4[0x418]);
        }
        operator_delete(*(void **)(unaff_EBP + -0x10));
        operator_delete(*(void **)(unaff_EBP + -0x18));
        iVar1 = 0;
      }
    }
  }
  else {
    iVar1 = -0x7fffbffb;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar1;
}



/* grim_mipmap_chain_create_dxt @ 10014595 */

/* [binja] int32_t __fastcall sub_10014595(int32_t* arg1) */

int grim_mipmap_chain_create_dxt(int *arg1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  void *pvVar5;
  undefined4 *puVar6;
  int *extraout_ECX;
  int unaff_EBP;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  
  seh_prolog();
  if ((char)extraout_ECX[2] == '\x02') {
    iVar4 = *(int *)(*extraout_ECX + 0x1058);
    pvVar5 = operator_new(iVar4 << 4);
    *(void **)(unaff_EBP + -0x30) = pvVar5;
    *(undefined4 *)(unaff_EBP + -4) = 0;
    if (pvVar5 == (void *)0x0) {
      *(undefined4 *)(unaff_EBP + -0x10) = 0;
    }
    else {
      _vector_constructor_iterator_(pvVar5,0x10,iVar4,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
      *(undefined4 *)(unaff_EBP + -0x10) = *(undefined4 *)(unaff_EBP + -0x30);
    }
    *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
    if (*(int *)(unaff_EBP + -0x10) == 0) {
      iVar4 = -0x7ff8fff2;
    }
    else {
      iVar4 = *(int *)(extraout_ECX[1] + 0x1058);
      pvVar5 = operator_new(iVar4 << 4);
      *(void **)(unaff_EBP + -0x30) = pvVar5;
      *(undefined4 *)(unaff_EBP + -4) = 1;
      if (pvVar5 == (void *)0x0) {
        *(undefined4 *)(unaff_EBP + -0x14) = 0;
      }
      else {
        _vector_constructor_iterator_(pvVar5,0x10,iVar4,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
        *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x30);
      }
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      if (*(int *)(unaff_EBP + -0x14) == 0) {
        operator_delete(*(void **)(unaff_EBP + -0x10));
        iVar4 = -0x7ff8fff2;
      }
      else {
        iVar4 = *extraout_ECX;
        iVar1 = extraout_ECX[1];
        iVar2 = *(int *)(iVar4 + 0x1058);
        uVar7 = *(uint *)(iVar1 + 0x1058);
        uVar9 = *(uint *)(iVar1 + 0x105c);
        uVar3 = *(uint *)(iVar1 + 0x1060);
        *(undefined4 *)(unaff_EBP + -0x28) = 0;
        *(undefined4 *)(unaff_EBP + -0x1c) = 0;
        *(uint *)(unaff_EBP + -0x34) = (uint)(iVar2 << 0x10) / uVar7;
        *(uint *)(unaff_EBP + -0x38) = (uint)(*(int *)(iVar4 + 0x105c) << 0x10) / uVar9;
        *(uint *)(unaff_EBP + -0x3c) = (uint)(*(int *)(iVar4 + 0x1060) << 0x10) / uVar3;
        if (uVar3 != 0) {
          do {
            *(undefined4 *)(unaff_EBP + -0x2c) = 0xffffffff;
            uVar7 = 0;
            *(undefined4 *)(unaff_EBP + -0x30) = 0;
            *(undefined4 *)(unaff_EBP + -0x18) = 0;
            if (uVar9 != 0) {
              do {
                *(undefined4 *)(unaff_EBP + -0x20) = 0;
                *(undefined4 *)(unaff_EBP + -0x24) = 0;
                if (((*(uint *)(unaff_EBP + -0x2c) ^ uVar7) & 0xffff0000) != 0) {
                  (**(code **)(*(int *)*extraout_ECX + 4))
                            (uVar7 >> 0x10,*(uint *)(unaff_EBP + -0x28) >> 0x10,
                             *(undefined4 *)(unaff_EBP + -0x10));
                  *(uint *)(unaff_EBP + -0x2c) = uVar7;
                }
                if (*(int *)(extraout_ECX[1] + 0x1058) != 0) {
                  puVar6 = *(undefined4 **)(unaff_EBP + -0x14);
                  do {
                    uVar7 = *(uint *)(unaff_EBP + -0x20);
                    *(int *)(unaff_EBP + -0x20) =
                         *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + -0x34);
                    puVar8 = (undefined4 *)((uVar7 >> 0x10) * 0x10 + *(int *)(unaff_EBP + -0x10));
                    *(int *)(unaff_EBP + -0x24) = *(int *)(unaff_EBP + -0x24) + 1;
                    uVar7 = *(uint *)(unaff_EBP + -0x24);
                    *puVar6 = *puVar8;
                    puVar6[1] = puVar8[1];
                    puVar6[2] = puVar8[2];
                    puVar6[3] = puVar8[3];
                    puVar6 = puVar6 + 4;
                  } while (uVar7 < *(uint *)(extraout_ECX[1] + 0x1058));
                }
                (**(code **)(*(int *)extraout_ECX[1] + 8))
                          (*(undefined4 *)(unaff_EBP + -0x18),*(undefined4 *)(unaff_EBP + -0x1c),
                           *(undefined4 *)(unaff_EBP + -0x14));
                uVar7 = *(int *)(unaff_EBP + -0x30) + *(int *)(unaff_EBP + -0x38);
                iVar4 = extraout_ECX[1];
                *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x18) + 1;
                uVar9 = *(uint *)(iVar4 + 0x105c);
                *(uint *)(unaff_EBP + -0x30) = uVar7;
              } while (*(uint *)(unaff_EBP + -0x18) < uVar9);
            }
            *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x28) + *(int *)(unaff_EBP + -0x3c);
            *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + -0x1c) + 1;
          } while (*(uint *)(unaff_EBP + -0x1c) < *(uint *)(extraout_ECX[1] + 0x1060));
        }
        operator_delete(*(void **)(unaff_EBP + -0x10));
        operator_delete(*(void **)(unaff_EBP + -0x14));
        iVar4 = 0;
      }
    }
  }
  else {
    iVar4 = -0x7fffbffb;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar4;
}



/* grim_mipmap_format_dispatch @ 10014799 */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* [binja] int32_t __fastcall sub_10014799(int32_t* arg1) */

int grim_mipmap_format_dispatch(int *arg1)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  void *pvVar9;
  float *pfVar10;
  float *pfVar11;
  int *arg1_00;
  float *pfVar12;
  uint uVar13;
  int unaff_EBP;
  
  seh_prolog();
  if ((char)arg1_00[2] != '\x05') {
    iVar8 = -0x7fffbffb;
    goto LAB_10014b8f;
  }
  iVar8 = *arg1_00;
  uVar13 = *(uint *)(iVar8 + 0x1058);
  iVar6 = arg1_00[1];
  if ((((*(uint *)(iVar6 + 0x1058) != uVar13 >> 1) &&
       ((*(uint *)(iVar6 + 0x1058) != 1 || (uVar13 != 1)))) ||
      ((*(uint *)(iVar6 + 0x105c) != *(uint *)(iVar8 + 0x105c) >> 1 &&
       ((*(uint *)(iVar6 + 0x105c) != 1 || (*(int *)(iVar8 + 0x105c) != 1)))))) ||
     ((*(int *)(iVar6 + 0x1060) != 1 || (*(int *)(iVar8 + 0x1060) != 1)))) {
    iVar8 = -0x7fffbffb;
    goto LAB_10014b8f;
  }
  if ((1 < uVar13) && ((uVar13 & 1) != 0)) {
    *(uint *)(iVar8 + 0x1058) = uVar13 & 0xfffffffe;
    piVar1 = (int *)(*arg1_00 + 0x1064);
    *piVar1 = *piVar1 - *(int *)(*arg1_00 + 0x1068);
  }
  uVar13 = *(uint *)(*arg1_00 + 0x105c);
  if (1 < uVar13) {
    *(uint *)(*arg1_00 + 0x105c) = uVar13 & 0xfffffffe;
  }
  if ((*(byte *)((int)arg1_00 + 10) & 8) == 0) {
    iVar8 = *arg1_00;
    iVar6 = *(int *)(iVar8 + 4);
    if (((iVar6 == *(int *)(arg1_00[1] + 4)) && (1 < *(uint *)(iVar8 + 0x1058))) &&
       (1 < *(uint *)(iVar8 + 0x105c))) {
      if (iVar6 < 0x1d) {
        if (iVar6 == 0x1c) {
LAB_10014914:
          iVar8 = grim_mipmap_downsample_a1r5g5b5(arg1_00);
        }
        else {
          switch(iVar6) {
          default:
            goto switchD_100148a1_caseD_14;
          case 0x15:
            iVar8 = grim_mipmap_downsample_dispatch(arg1_00);
            break;
          case 0x16:
            iVar8 = grim_mipmap_downsample_2(arg1_00);
            break;
          case 0x17:
            iVar8 = grim_mipmap_downsample_argb_2x2(arg1_00);
            break;
          case 0x18:
            iVar8 = grim_mipmap_downsample_rgb_2x2(arg1_00);
            break;
          case 0x19:
            iVar8 = grim_mipmap_downsample_a8r8g8b8(arg1_00);
            break;
          case 0x1a:
            iVar8 = grim_mipmap_downsample_x8r8g8b8(arg1_00);
            break;
          case 0x1b:
            iVar8 = grim_mipmap_downsample_r5g6b5(arg1_00);
          }
        }
      }
      else if (iVar6 == 0x1d) {
        iVar8 = grim_mipmap_downsample_x1r5g5b5(arg1_00);
      }
      else if (iVar6 == 0x1e) {
        iVar8 = grim_mipmap_downsample_a4r4g4b4(arg1_00);
      }
      else {
        if ((iVar6 == 0x28) || (iVar6 == 0x29)) goto switchD_100148a1_caseD_14;
        if (iVar6 == 0x32) goto LAB_10014914;
        if (iVar6 == 0x33) {
          iVar8 = grim_mipmap_downsample_x4r4g4b4(arg1_00);
        }
        else {
          if (iVar6 != 0x34) goto switchD_100148a1_caseD_14;
          iVar8 = grim_mipmap_downsample_a8r3g3b2(arg1_00);
        }
      }
      if (-1 < iVar8) {
        iVar8 = 0;
        goto LAB_10014b8f;
      }
    }
  }
switchD_100148a1_caseD_14:
  iVar8 = *(int *)(arg1_00[1] + 0x1058);
  pvVar9 = operator_new(iVar8 << 4);
  *(void **)(unaff_EBP + -0x2c) = pvVar9;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if (pvVar9 == (void *)0x0) {
    *(undefined4 *)(unaff_EBP + -0x1c) = 0;
  }
  else {
    _vector_constructor_iterator_(pvVar9,0x10,iVar8,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
    *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(unaff_EBP + -0x2c);
  }
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    iVar8 = -0x7ff8fff2;
  }
  else {
    iVar8 = *(int *)(*arg1_00 + 0x1058);
    if (*(int *)(*arg1_00 + 0x105c) == 1) {
      pvVar9 = operator_new(iVar8 << 4);
      *(void **)(unaff_EBP + -0x2c) = pvVar9;
      *(undefined4 *)(unaff_EBP + -4) = 1;
      if (pvVar9 == (void *)0x0) {
        iVar8 = 0;
      }
      else {
        _vector_constructor_iterator_(pvVar9,0x10,iVar8,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
        iVar8 = *(int *)(unaff_EBP + -0x2c);
      }
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      *(int *)(unaff_EBP + -0x24) = iVar8;
      *(int *)(unaff_EBP + -0x14) = iVar8;
    }
    else {
      pvVar9 = operator_new(iVar8 << 5);
      *(void **)(unaff_EBP + -0x2c) = pvVar9;
      *(undefined4 *)(unaff_EBP + -4) = 2;
      if (pvVar9 == (void *)0x0) {
        iVar8 = 0;
      }
      else {
        _vector_constructor_iterator_
                  (pvVar9,0x10,iVar8 << 1,(_func_void_ptr_void_ptr *)&LAB_1000ae4f);
        iVar8 = *(int *)(unaff_EBP + -0x2c);
      }
      iVar6 = *(int *)(*arg1_00 + 0x1058);
      *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
      *(int *)(unaff_EBP + -0x24) = iVar8;
      *(int *)(unaff_EBP + -0x14) = iVar8;
      iVar8 = iVar6 * 0x10 + iVar8;
    }
    *(int *)(unaff_EBP + -0x10) = iVar8;
    if (*(int *)(unaff_EBP + -0x24) == 0) {
      iVar8 = -0x7ff8fff2;
    }
    else {
      if (*(int *)(*arg1_00 + 0x1058) == 1) {
        *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x14);
        iVar8 = *(int *)(unaff_EBP + -0x10);
      }
      else {
        *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x14) + 0x10;
        iVar8 = *(int *)(unaff_EBP + -0x10) + 0x10;
      }
      *(int *)(unaff_EBP + -0x2c) = iVar8;
      iVar8 = *(int *)(arg1_00[1] + 0x105c);
      *(undefined4 *)(unaff_EBP + -0x18) = 0;
      if (iVar8 != 0) {
        do {
          iVar8 = *(int *)(unaff_EBP + -0x14);
          iVar6 = *(int *)(unaff_EBP + -0x18) * 2;
          (**(code **)(*(int *)*arg1_00 + 4))(iVar6,0,iVar8);
          if (*(int *)(unaff_EBP + -0x10) != iVar8) {
            (**(code **)(*(int *)*arg1_00 + 4))(iVar6 + 1,0,*(undefined4 *)(unaff_EBP + -0x10));
          }
          uVar13 = 0;
          if (*(int *)(arg1_00[1] + 0x1058) != 0) {
            *(undefined4 *)(unaff_EBP + -0x20) = *(undefined4 *)(unaff_EBP + -0x1c);
            do {
              iVar8 = uVar13 * 0x20;
              pfVar10 = (float *)(*(int *)(unaff_EBP + -0x28) + iVar8);
              fVar2 = *pfVar10;
              pfVar12 = (float *)(*(int *)(unaff_EBP + -0x14) + iVar8);
              fVar3 = *pfVar12;
              puVar7 = *(undefined4 **)(unaff_EBP + -0x20);
              fVar4 = pfVar10[1];
              *(int *)(unaff_EBP + -0x20) = *(int *)(unaff_EBP + -0x20) + 0x10;
              fVar5 = pfVar12[1];
              *(float *)(unaff_EBP + -0x44) = pfVar10[2] + pfVar12[2];
              pfVar11 = (float *)(*(int *)(unaff_EBP + -0x10) + iVar8);
              *(float *)(unaff_EBP + -0x40) = pfVar10[3] + pfVar12[3];
              *(float *)(unaff_EBP + -0x5c) = fVar2 + fVar3 + *pfVar11;
              fVar2 = pfVar11[1];
              fVar3 = pfVar11[2];
              pfVar10 = (float *)(*(int *)(unaff_EBP + -0x2c) + iVar8);
              *(float *)(unaff_EBP + -0x50) = *(float *)(unaff_EBP + -0x40) + pfVar11[3];
              uVar13 = uVar13 + 1;
              *(float *)(unaff_EBP + -0x6c) = *(float *)(unaff_EBP + -0x5c) + *pfVar10;
              *(float *)(unaff_EBP + -0x68) = fVar4 + fVar5 + fVar2 + pfVar10[1];
              fVar2 = pfVar10[2];
              fVar4 = pfVar10[3];
              *(float *)(unaff_EBP + -0x3c) = *(float *)(unaff_EBP + -0x6c) * 0.25;
              *(float *)(unaff_EBP + -0x38) = *(float *)(unaff_EBP + -0x68) * 0.25;
              *(float *)(unaff_EBP + -0x34) = (*(float *)(unaff_EBP + -0x44) + fVar3 + fVar2) * 0.25
              ;
              *(float *)(unaff_EBP + -0x30) = (*(float *)(unaff_EBP + -0x50) + fVar4) * 0.25;
              *puVar7 = *(undefined4 *)(unaff_EBP + -0x3c);
              puVar7[1] = *(undefined4 *)(unaff_EBP + -0x38);
              puVar7[2] = *(undefined4 *)(unaff_EBP + -0x34);
              puVar7[3] = *(undefined4 *)(unaff_EBP + -0x30);
            } while (uVar13 < *(uint *)(arg1_00[1] + 0x1058));
          }
          (**(code **)(*(int *)arg1_00[1] + 8))
                    (*(undefined4 *)(unaff_EBP + -0x18),0,*(undefined4 *)(unaff_EBP + -0x1c));
          *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x18) + 1;
        } while (*(uint *)(unaff_EBP + -0x18) < *(uint *)(arg1_00[1] + 0x105c));
      }
      operator_delete(*(void **)(unaff_EBP + -0x24));
      iVar8 = 0;
    }
    operator_delete(*(void **)(unaff_EBP + -0x1c));
  }
LAB_10014b8f:
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar8;
}



/* grim_apply_color_key @ 100174a8 */

/* zeroes RGBA pixels that match the current color key */

void __thiscall grim_apply_color_key(void *this,float *pixels)

{
  int iVar1;
  float *pfVar2;
  
  if (pixels < pixels + *(int *)((int)this + 0x1058) * 4) {
    iVar1 = ((uint)((int)(pixels + *(int *)((int)this + 0x1058) * 4) + (-1 - (int)pixels)) >> 4) + 1
    ;
    pfVar2 = pixels + 2;
    do {
      if ((((pfVar2[-2] == *(float *)((int)this + 0x1c)) &&
           (pfVar2[-1] == *(float *)((int)this + 0x20))) &&
          (*pfVar2 == *(float *)((int)this + 0x24))) && (pfVar2[1] == *(float *)((int)this + 0x28)))
      {
        pfVar2[1] = 0.0;
        *pfVar2 = 0.0;
        pfVar2[-1] = 0.0;
        pfVar2[-2] = 0.0;
      }
      pfVar2 = pfVar2 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}



/* grim_dxt_encoder_core @ 1001fc1f */

void __cdecl grim_dxt_encoder_core(int *param_1,byte *param_2,int param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  cVar1 = (char)param_1[2];
  iVar5 = *param_1;
  if (((cVar1 == '\x02') && (param_3 != 0)) &&
     (iVar3 = iVar5, pbVar4 = param_2, *(char *)((int)param_1 + 9) == '\b')) {
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      bVar2 = *param_2;
      pbVar6 = param_2 + 1;
      pbVar7 = param_2 + 2;
      param_2 = param_2 + 3;
      *pbVar4 = *(byte *)((((bVar2 & 0xf8) << 5 | *pbVar6 & 0xf8) << 2 | (int)(uint)*pbVar7 >> 3) +
                         param_3);
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    if (((cVar1 != '\x06') || (param_3 == 0)) ||
       (iVar3 = iVar5, pbVar4 = param_2, *(char *)((int)param_1 + 9) != '\b')) {
      if (cVar1 != '\x03') {
        return;
      }
      if (param_4 == 0) {
        return;
      }
      if (*(char *)((int)param_1 + 9) != '\b') {
        return;
      }
      for (; iVar5 != 0; iVar5 = iVar5 + -1) {
        *param_2 = *(byte *)((uint)*param_2 + param_4);
        param_2 = param_2 + 1;
      }
      return;
    }
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      bVar2 = *param_2;
      pbVar6 = param_2 + 1;
      pbVar7 = param_2 + 2;
      param_2 = param_2 + 4;
      *pbVar4 = *(byte *)((((bVar2 & 0xf8) << 5 | *pbVar6 & 0xf8) << 2 | (int)(uint)*pbVar7 >> 3) +
                         param_3);
      pbVar4 = pbVar4 + 1;
    }
  }
  *(byte *)((int)param_1 + 0xb) = *(byte *)((int)param_1 + 9);
  *(undefined1 *)(param_1 + 2) = 3;
  *(undefined1 *)((int)param_1 + 10) = 1;
  param_1[1] = (uint)*(byte *)((int)param_1 + 9) * iVar5 + 7 >> 3;
  return;
}



/* grim_dxt_decode_rgb565 @ 1002060e */

/* unpacks RGB565 into RGBA floats (alpha=1) */

void __fastcall grim_dxt_decode_rgb565(float *out_rgba,uint rgb565)

{
  float *in_EAX;
  
  *in_EAX = (float)((uint)out_rgba >> 0xb & 0x1f) * 0.032258064;
  in_EAX[1] = (float)((uint)out_rgba >> 5 & 0x3f) * 0.015873017;
  in_EAX[2] = (float)((uint)out_rgba & 0x1f) * 0.032258064;
  in_EAX[3] = 1.0;
  return;
}



/* grim_dxt_unpremultiply_rgba_block @ 1002065a */

/* divides rgb by alpha for a 4x4 RGBA block */

int __fastcall grim_dxt_unpremultiply_rgba_block(float *rgba)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = 0x10;
  do {
    if (rgba[3] == 0.0) {
      *rgba = 0.0;
      rgba[1] = 0.0;
      fVar1 = 0.0;
LAB_100206cc:
      rgba[2] = fVar1;
    }
    else if (rgba[3] < 1.0) {
      fVar1 = 1.0 / rgba[3];
      if (rgba[3] <= *rgba) {
        fVar2 = 1.0;
      }
      else {
        fVar2 = fVar1 * *rgba;
      }
      *rgba = fVar2;
      if (rgba[3] <= rgba[1]) {
        fVar2 = 1.0;
      }
      else {
        fVar2 = fVar1 * rgba[1];
      }
      rgba[1] = fVar2;
      if (rgba[3] <= rgba[2]) {
        fVar1 = 1.0;
      }
      else {
        fVar1 = fVar1 * rgba[2];
      }
      goto LAB_100206cc;
    }
    rgba = rgba + 4;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return 0;
    }
  } while( true );
}



/* grim_dxt_premultiply_rgba_block @ 100206d8 */

/* multiplies rgb by alpha for a 4x4 RGBA block */

int __fastcall grim_dxt_premultiply_rgba_block(float *out_rgba)

{
  float *in_EAX;
  int iVar1;
  
  iVar1 = 0x10;
  do {
    *out_rgba = in_EAX[3] * *in_EAX;
    iVar1 = iVar1 + -1;
    out_rgba[1] = in_EAX[1] * in_EAX[3];
    out_rgba[2] = in_EAX[2] * in_EAX[3];
    out_rgba[3] = in_EAX[3];
    in_EAX = in_EAX + 4;
    out_rgba = out_rgba + 4;
  } while (iVar1 != 0);
  return 0;
}



/* grim_dxt_pack_rgb565 @ 1002072b */

/* clamps rgb floats and packs into RGB565 */

uint __fastcall grim_dxt_pack_rgb565(float *rgb)

{
  float local_1c;
  float local_18;
  float local_14;
  
  if (0.0 <= *rgb) {
    if (1.0 < *rgb) {
      local_1c = 1.0;
    }
    else {
      local_1c = *rgb;
    }
  }
  else {
    local_1c = 0.0;
  }
  if (0.0 <= rgb[1]) {
    if (1.0 < rgb[1]) {
      local_18 = 1.0;
    }
    else {
      local_18 = rgb[1];
    }
  }
  else {
    local_18 = 0.0;
  }
  if (0.0 <= rgb[2]) {
    if (rgb[2] <= 1.0) {
      local_14 = rgb[2];
    }
    else {
      local_14 = 1.0;
    }
  }
  else {
    local_14 = 0.0;
  }
  fpu_save_control_word();
  return ((int)ROUND(local_1c * 31.0 + 0.5) << 6 | (int)ROUND(local_18 * 63.0 + 0.5)) << 5 |
         (int)ROUND(local_14 * 31.0 + 0.5);
}



/* grim_dxt5_optimize_alpha_endpoints @ 10020825 */

/* iteratively chooses DXT5 alpha endpoints for 6/8-alpha modes */

void __cdecl
grim_dxt5_optimize_alpha_endpoints(float *min_out,float *max_out,float *alphas,uint mode)

{
  float fVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  float local_54 [6];
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  float local_30;
  float local_2c;
  float local_28;
  uint local_24;
  undefined4 *local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  if (mode == 6) {
    pfVar5 = (float *)&grim_dxt5_alpha_weights_min_6;
    local_20 = &grim_dxt5_alpha_weights_max_6;
  }
  else {
    pfVar5 = (float *)&grim_dxt5_alpha_weights_min_8;
    local_20 = (undefined4 *)&grim_dxt5_alpha_weights_max_8;
  }
  uVar3 = 0;
  local_8 = 1.0;
  local_c = 0.0;
  if (mode == 8) {
    do {
      pfVar2 = alphas + uVar3;
      if (*pfVar2 < local_8) {
        local_8 = *pfVar2;
      }
      if (local_c < *pfVar2) {
        local_c = *pfVar2;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x10);
  }
  else {
    do {
      pfVar2 = alphas + uVar3;
      if ((*pfVar2 < local_8) && (0.0 < *pfVar2)) {
        local_8 = *pfVar2;
      }
      if ((local_c < *pfVar2) && (*pfVar2 < 1.0)) {
        local_c = *pfVar2;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x10);
  }
  uVar3 = mode - 1;
  local_28 = (float)(int)uVar3;
  if ((int)uVar3 < 0) {
    local_28 = local_28 + 4.2949673e+09;
  }
  local_34 = uVar3;
  fpu_save_control_word();
  local_24 = 0;
  while (0.00390625 <= local_c - local_8) {
    local_2c = local_28 / (local_c - local_8);
    if (mode != 0) {
      iVar4 = (int)local_20 - (int)pfVar5;
      pfVar2 = pfVar5;
      uVar6 = mode;
      do {
        *(float *)(((int)local_54 - (int)pfVar5) + (int)pfVar2) =
             local_8 * *pfVar2 + local_c * *(float *)(iVar4 + (int)pfVar2);
        pfVar2 = pfVar2 + 1;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    if (mode == 6) {
      local_3c = 0;
      local_38 = 0x3f800000;
    }
    uVar6 = 0;
    local_10 = 0.0;
    local_14 = 0.0;
    local_18 = 0.0;
    local_1c = 0.0;
    do {
      pfVar2 = alphas + uVar6;
      fVar1 = (*pfVar2 - local_8) * local_2c;
      if (fVar1 < 0.0 == (fVar1 == 0.0)) {
        if (fVar1 < local_28) {
          local_30 = fVar1 + 0.5;
          local_34 = (uint)ROUND(fVar1 + 0.5);
        }
        else {
          local_34 = uVar3;
          if ((mode == 6) && (fVar1 = (local_c + 1.0) * 0.5, fVar1 < *pfVar2 != (fVar1 == *pfVar2)))
          goto LAB_10020a28;
        }
LAB_100209e6:
        if (local_34 < mode) {
          local_10 = (*pfVar2 - local_54[local_34]) * pfVar5[local_34] + local_10;
          local_18 = pfVar5[local_34] * pfVar5[local_34] + local_18;
          local_14 = (*pfVar2 - local_54[local_34]) * (float)local_20[local_34] + local_14;
          fVar1 = (float)local_20[local_34];
          local_1c = fVar1 * fVar1 + local_1c;
        }
      }
      else if ((mode != 6) || (local_8 * 0.5 < *pfVar2)) {
        local_34 = 0;
        goto LAB_100209e6;
      }
LAB_10020a28:
      uVar6 = uVar6 + 1;
    } while (uVar6 < 0x10);
    if (0.0 < local_18) {
      local_8 = local_8 - local_10 / local_18;
    }
    if (0.0 < local_1c) {
      local_c = local_c - local_14 / local_1c;
    }
    fVar1 = local_c;
    if (local_c < local_8) {
      local_c = local_8;
      local_8 = fVar1;
    }
    if (((local_10 * local_10 < 0.015625) && (local_14 * local_14 < 0.015625)) ||
       (local_24 = local_24 + 1, 7 < local_24)) break;
  }
  if (0.0 <= local_8) {
    if (1.0 < local_8) {
      local_8 = 1.0;
    }
  }
  else {
    local_8 = 0.0;
  }
  *min_out = local_8;
  if (0.0 <= local_c) {
    if (1.0 < local_c) {
      local_c = 1.0;
    }
  }
  else {
    local_c = 0.0;
  }
  *max_out = local_c;
  return;
}



/* grim_dxt1_optimize_color_endpoints @ 10020b2a */

/* optimizes DXT1 color endpoints for 3- or 4-color mode */

void __cdecl
grim_dxt1_optimize_color_endpoints(float *min_out,float *max_out,float *rgba,float mode)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  float fVar17;
  float local_c4 [16];
  float *local_84;
  int local_80;
  float local_7c;
  float local_78;
  float local_74;
  float *local_6c;
  undefined4 *local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_34 [6];
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  undefined4 uStack_8;
  
  fVar10 = mode;
  if (mode == 4.2039e-45) {
    local_6c = (float *)&grim_dxt1_color_weights_min_3;
    local_68 = &grim_dxt1_color_weights_max_3;
  }
  else {
    local_6c = (float *)&grim_dxt1_color_weights_min_4;
    local_68 = (undefined4 *)&grim_dxt1_color_weights_max_4;
  }
  local_34[4] = 0.0;
  fVar17 = 0.0;
  local_14 = DAT_100544c0;
  local_10 = DAT_100544c4;
  local_1c = 0.0;
  local_c = DAT_100544c8;
  uStack_8 = DAT_100544cc;
  pfVar11 = rgba + 2;
  iVar12 = 0x10;
  local_84 = pfVar11;
  pfVar13 = pfVar11;
  iVar14 = iVar12;
  do {
    if (pfVar13[-2] < local_14) {
      local_14 = pfVar13[-2];
    }
    if (pfVar13[-1] < local_10) {
      local_10 = pfVar13[-1];
    }
    if (*pfVar13 < local_c) {
      local_c = *pfVar13;
    }
    if (local_34[4] < pfVar13[-2]) {
      local_34[4] = pfVar13[-2];
    }
    if (fVar17 < pfVar13[-1]) {
      fVar17 = pfVar13[-1];
    }
    if (local_1c < *pfVar13) {
      local_1c = *pfVar13;
    }
    fVar4 = local_1c;
    pfVar13 = pfVar13 + 4;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  local_34[5] = fVar17;
  fVar7 = local_34[4] - local_14;
  fVar6 = fVar17 - local_10;
  fVar5 = local_1c - local_c;
  local_48 = fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5;
  if (1.1754944e-38 <= local_48) {
    fVar8 = 1.0 / local_48;
    local_7c = fVar7 * fVar8;
    local_78 = fVar6 * fVar8;
    local_74 = fVar8 * fVar5;
    local_58 = (local_34[4] + local_14) * 0.5;
    local_54 = (fVar17 + local_10) * 0.5;
    local_50 = (local_1c + local_c) * 0.5;
    local_34[3] = 0.0;
    local_34[2] = 0.0;
    local_34[1] = 0.0;
    fVar3 = 0.0;
    do {
      local_44 = (pfVar11[-2] - local_58) * fVar7 * fVar8;
      local_40 = (pfVar11[-1] - local_54) * fVar6 * fVar8;
      fVar2 = *pfVar11;
      pfVar11 = pfVar11 + 4;
      iVar12 = iVar12 + -1;
      fVar2 = (fVar2 - local_50) * fVar8 * fVar5;
      fVar9 = local_40 + fVar2 + local_44;
      fVar3 = fVar9 * fVar9 + fVar3;
      fVar9 = (local_40 + local_44) - fVar2;
      local_34[1] = fVar9 * fVar9 + local_34[1];
      fVar9 = (local_44 - local_40) + fVar2;
      local_34[2] = fVar9 * fVar9 + local_34[2];
      fVar2 = (local_44 - local_40) - fVar2;
      local_34[3] = fVar2 * fVar2 + local_34[3];
    } while (iVar12 != 0);
    local_34[0] = fVar3;
    uVar16 = 0;
    uVar15 = 1;
    do {
      if (fVar3 < local_34[uVar15]) {
        fVar3 = local_34[uVar15];
        uVar16 = uVar15;
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 < 4);
    if ((uVar16 & 2) != 0) {
      local_34[5] = local_10;
      local_10 = fVar17;
    }
    if ((uVar16 & 1) != 0) {
      local_1c = local_c;
      local_c = fVar4;
    }
    if (0.00024414062 <= local_48) {
      local_60 = (float)((int)mode + -1);
      if ((int)mode + -1 < 0) {
        local_60 = local_60 + 4.2949673e+09;
      }
      fpu_save_control_word();
      local_48 = 0.0;
      while( true ) {
        iVar12 = 0x10;
        if (fVar10 != 0.0) {
          pfVar13 = local_c4 + 1;
          iVar14 = (int)local_68 - (int)local_6c;
          pfVar11 = local_6c;
          fVar17 = fVar10;
          do {
            pfVar13[-1] = local_34[4] * *(float *)(iVar14 + (int)pfVar11) + local_14 * *pfVar11;
            *pfVar13 = local_34[5] * *(float *)(iVar14 + (int)pfVar11) + local_10 * *pfVar11;
            fVar4 = *pfVar11;
            pfVar1 = (float *)(iVar14 + (int)pfVar11);
            pfVar11 = pfVar11 + 1;
            pfVar13[1] = local_1c * *pfVar1 + local_c * fVar4;
            pfVar13 = pfVar13 + 4;
            fVar17 = (float)((int)fVar17 + -1);
          } while (fVar17 != 0.0);
        }
        fVar17 = local_34[4] - local_14;
        fVar7 = local_34[5] - local_10;
        fVar6 = local_1c - local_c;
        fVar4 = fVar17 * fVar17 + fVar7 * fVar7 + fVar6 * fVar6;
        if (fVar4 < 0.00024414062) break;
        fVar4 = local_60 / fVar4;
        local_44 = fVar4 * fVar17;
        local_40 = fVar7 * fVar4;
        local_3c = fVar4 * fVar6;
        local_34[2] = 0.0;
        local_34[1] = 0.0;
        local_34[0] = 0.0;
        local_50 = 0.0;
        local_54 = 0.0;
        local_58 = 0.0;
        local_5c = 0.0;
        mode = 0.0;
        pfVar13 = local_84;
        do {
          fVar5 = (*pfVar13 - local_c) * fVar4 * fVar6 +
                  (pfVar13[-2] - local_14) * fVar4 * fVar17 +
                  (pfVar13[-1] - local_10) * fVar7 * fVar4;
          local_64 = fVar5;
          if (fVar5 < local_60) {
            local_64 = fVar5 + 0.5;
            local_80 = (int)ROUND(fVar5 + 0.5);
          }
          else {
            local_80 = (int)fVar10 + -1;
          }
          pfVar11 = pfVar13 + -2;
          local_78 = local_c4[local_80 * 4 + 1] - pfVar13[-1];
          fVar5 = *pfVar13;
          fVar3 = local_6c[local_80] * 0.125;
          pfVar13 = pfVar13 + 4;
          iVar12 = iVar12 + -1;
          fVar8 = (float)local_68[local_80] * 0.125;
          mode = fVar3 * local_6c[local_80] + mode;
          local_58 = fVar3 * (local_c4[local_80 * 4] - *pfVar11) + local_58;
          local_54 = fVar3 * local_78 + local_54;
          local_50 = fVar3 * (local_c4[local_80 * 4 + 2] - fVar5) + local_50;
          local_5c = fVar8 * (float)local_68[local_80] + local_5c;
          local_34[0] = fVar8 * (local_c4[local_80 * 4] - *pfVar11) + local_34[0];
          local_34[1] = local_78 * fVar8 + local_34[1];
          local_34[2] = fVar8 * (local_c4[local_80 * 4 + 2] - fVar5) + local_34[2];
        } while (iVar12 != 0);
        if (0.0 < mode) {
          fVar17 = -1.0 / mode;
          local_14 = local_58 * fVar17 + local_14;
          local_10 = local_54 * fVar17 + local_10;
          local_c = fVar17 * local_50 + local_c;
        }
        if (0.0 < local_5c) {
          local_5c = -1.0 / local_5c;
          local_34[4] = local_34[0] * local_5c + local_34[4];
          local_34[5] = local_34[1] * local_5c + local_34[5];
          local_1c = local_5c * local_34[2] + local_1c;
        }
        if (((((local_58 * local_58 < 1.5258789e-05) && (local_54 * local_54 < 1.5258789e-05)) &&
             (local_50 * local_50 < 1.5258789e-05)) &&
            (((local_34[0] * local_34[0] < 1.5258789e-05 &&
              (local_34[1] * local_34[1] < 1.5258789e-05)) &&
             (local_34[2] * local_34[2] < 1.5258789e-05)))) ||
           (local_48 = (float)((int)local_48 + 1), 7 < (uint)local_48)) break;
      }
      *min_out = local_14;
      min_out[1] = local_10;
      min_out[2] = local_c;
      *max_out = local_34[4];
      max_out[1] = local_34[5];
    }
    else {
      *min_out = local_14;
      min_out[1] = local_10;
      min_out[2] = local_c;
      max_out[1] = local_34[5];
      *max_out = local_34[4];
    }
  }
  else {
    *min_out = local_14;
    min_out[1] = local_10;
    min_out[2] = local_c;
    max_out[1] = fVar17;
    *max_out = local_34[4];
  }
  max_out[2] = local_1c;
  return;
}



/* grim_dxt1_encode_color_block @ 10021095 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* encodes a 4x4 RGBA block into a DXT1 color block (supports 1-bit alpha mode) */

int __cdecl grim_dxt1_encode_color_block(ushort *out_block,float mode)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  float *pfVar4;
  float *out_rgba;
  uint uVar5;
  float extraout_EDX;
  uint rgb565;
  uint rgb565_00;
  float extraout_EDX_00;
  float fVar6;
  uint uVar7;
  ushort uVar8;
  int iVar9;
  ushort uVar10;
  int iVar11;
  float local_2d4 [64];
  float local_1d4;
  float local_1d0;
  undefined1 local_1cc [4];
  undefined1 local_1c8 [4];
  undefined1 local_1c4 [4];
  undefined1 local_1c0 [20];
  undefined1 local_1ac [4];
  undefined1 local_1a8 [4];
  undefined1 local_1a4 [4];
  undefined1 local_1a0 [4];
  undefined1 local_19c [4];
  undefined1 local_198 [4];
  undefined1 local_194 [4];
  float local_190;
  undefined1 local_18c [4];
  undefined1 local_188 [4];
  undefined1 local_184 [4];
  undefined1 local_180 [172];
  float local_d4;
  float local_d0;
  float local_cc;
  int local_c4;
  undefined1 *local_c0;
  undefined1 *local_bc;
  undefined1 *local_b8;
  undefined1 *local_b4;
  undefined1 *local_b0;
  undefined1 *local_ac;
  int local_a8;
  undefined1 *local_a4;
  undefined1 *local_a0;
  float local_9c [4];
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined1 *local_5c;
  undefined1 *local_58;
  undefined1 *local_54;
  undefined1 *local_50;
  float local_4c;
  float local_48;
  float local_44;
  float fStack_40;
  float local_3c;
  float local_38;
  float local_34;
  float *local_2c;
  float *local_28;
  undefined *local_24;
  float local_20;
  float local_1c;
  float local_18;
  float fStack_14;
  float local_10;
  float *local_c;
  float local_8;
  
  if (mode == 0.0) {
    local_10 = 5.60519e-45;
  }
  else {
    iVar9 = 0;
    pfVar4 = (float *)(in_EAX + 0xc);
    iVar11 = 0x10;
    do {
      if (*pfVar4 < 0.5) {
        iVar9 = iVar9 + 1;
      }
      pfVar4 = pfVar4 + 4;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if (iVar9 == 0x10) {
      out_block[1] = 0xffff;
      out_block[2] = 0xffff;
      out_block[3] = 0xffff;
      *out_block = 0;
      return 0;
    }
    local_10 = (float)(4 - (uint)(iVar9 != 0));
  }
  pfVar4 = &local_1d4;
  for (iVar11 = 0x40; iVar11 != 0; iVar11 = iVar11 + -1) {
    *pfVar4 = 0.0;
    pfVar4 = pfVar4 + 1;
  }
  fpu_save_control_word();
  local_58 = local_1cc + -in_EAX;
  local_b8 = local_1c8 + -in_EAX;
  local_c0 = local_1c4 + -in_EAX;
  local_5c = local_1ac + -in_EAX;
  local_b4 = local_1a8 + -in_EAX;
  local_ac = local_1a4 + -in_EAX;
  local_28 = (float *)(local_19c + -in_EAX);
  local_bc = local_198 + -in_EAX;
  local_a4 = local_194 + -in_EAX;
  local_2c = (float *)(local_18c + -in_EAX);
  local_a0 = local_188 + -in_EAX;
  local_b0 = local_184 + -in_EAX;
  pfVar4 = (float *)(in_EAX + 8);
  local_a8 = (int)&local_1d4 - in_EAX;
  uVar7 = 0;
  mode = extraout_EDX;
  do {
    local_20 = *(float *)((int)&local_1d4 + uVar7) + pfVar4[-2];
    fVar6 = pfVar4[-1];
    fVar1 = *(float *)(local_1cc + (uVar7 - 4));
    local_1c = fVar6 + fVar1;
    local_18 = *(float *)(local_a8 + (int)pfVar4) + *pfVar4;
    local_c4 = (int)ROUND(local_20 * 31.0 + 0.5);
    local_24 = (undefined *)((float)local_c4 * 0.032258064);
    *(undefined **)((int)local_2d4 + uVar7) = local_24;
    local_50 = (undefined1 *)(int)ROUND((fVar6 + fVar1) * 63.0 + 0.5);
    local_8 = (float)(int)local_50 * 0.015873017;
    *(float *)((int)local_2d4 + uVar7 + 4) = local_8;
    local_54 = (undefined1 *)(int)ROUND(local_18 * 31.0 + 0.5);
    fVar6 = (float)(int)local_54 * 0.032258064;
    local_c = (float *)((uint)mode & 3);
    *(float *)(((int)local_2d4 - in_EAX) + (int)pfVar4) = fVar6;
    *(undefined4 *)((int)local_2d4 + (4 - in_EAX) + (int)pfVar4) = 0x3f800000;
    fVar3 = local_20 - (float)local_24;
    fVar2 = local_1c - local_8;
    local_38 = fVar2;
    fVar1 = local_18 - fVar6;
    local_34 = fVar1;
    if (((uint)mode & 3) != 3) {
      *(float *)(local_58 + (int)pfVar4) = fVar3 * 0.4375 + *(float *)(local_58 + (int)pfVar4);
      *(float *)(local_b8 + (int)pfVar4) = fVar2 * 0.4375 + *(float *)(local_b8 + (int)pfVar4);
      *(float *)(local_c0 + (int)pfVar4) = fVar1 * 0.4375 + *(float *)(local_c0 + (int)pfVar4);
    }
    if (uVar7 < 0xc0) {
      if (local_c != (float *)0x0) {
        *(float *)(local_5c + (int)pfVar4) = fVar3 * 0.1875 + *(float *)(local_5c + (int)pfVar4);
        *(float *)(local_b4 + (int)pfVar4) = fVar2 * 0.1875 + *(float *)(local_b4 + (int)pfVar4);
        *(float *)(local_ac + (int)pfVar4) = fVar1 * 0.1875 + *(float *)(local_ac + (int)pfVar4);
      }
      *(float *)((int)local_28 + (int)pfVar4) =
           fVar3 * 0.3125 + *(float *)((int)local_28 + (int)pfVar4);
      *(float *)(local_bc + (int)pfVar4) = fVar2 * 0.3125 + *(float *)(local_bc + (int)pfVar4);
      *(float *)(local_a4 + (int)pfVar4) = fVar1 * 0.3125 + *(float *)(local_a4 + (int)pfVar4);
      if (local_c != (float *)0x3) {
        *(float *)((int)local_2c + (int)pfVar4) =
             fVar3 * 0.0625 + *(float *)((int)local_2c + (int)pfVar4);
        *(float *)(local_a0 + (int)pfVar4) = fVar2 * 0.0625 + *(float *)(local_a0 + (int)pfVar4);
        *(float *)(local_b0 + (int)pfVar4) = fVar1 * 0.0625 + *(float *)(local_b0 + (int)pfVar4);
      }
    }
    mode = (float)((int)mode + 1);
    uVar5 = uVar7 + 0x10;
    *(float *)((int)local_2d4 + uVar7) = (float)local_24 * DAT_100544c0;
    *(float *)((int)local_2d4 + uVar7 + 4) = local_8 * DAT_100544c4;
    *(float *)(((int)local_2d4 - in_EAX) + (int)pfVar4) = fVar6 * DAT_100544c8;
    pfVar4 = pfVar4 + 4;
    uVar7 = uVar5;
  } while (uVar5 < 0x100);
  grim_dxt1_optimize_color_endpoints(&local_4c,&local_20,local_2d4,local_10);
  local_d4 = local_4c * _DAT_100544d0;
  local_d0 = local_48 * _DAT_100544d4;
  local_cc = local_44 * _DAT_100544d8;
  local_3c = local_20 * _DAT_100544d0;
  local_38 = local_1c * _DAT_100544d4;
  local_34 = local_18 * _DAT_100544d8;
  pfVar4 = (float *)grim_dxt_pack_rgb565(&local_d4);
  local_28 = pfVar4;
  out_rgba = (float *)grim_dxt_pack_rgb565(&local_3c);
  uVar8 = (ushort)pfVar4;
  uVar10 = (ushort)out_rgba;
  if ((local_10 == 5.60519e-45) && (uVar8 == uVar10)) {
    out_block[2] = 0;
    out_block[3] = 0;
    *out_block = uVar8;
    out_block[1] = uVar10;
  }
  else {
    local_2c = out_rgba;
    grim_dxt_decode_rgb565(pfVar4,rgb565);
    grim_dxt_decode_rgb565(out_rgba,rgb565_00);
    local_4c = local_d4 * DAT_100544c0;
    local_48 = local_d0 * DAT_100544c4;
    local_44 = local_cc * DAT_100544c8;
    local_20 = local_3c * DAT_100544c0;
    local_1c = local_38 * DAT_100544c4;
    local_18 = local_34 * DAT_100544c8;
    if ((local_10 == 4.2039e-45) == uVar8 <= uVar10) {
      *out_block = uVar8;
      out_block[1] = uVar10;
      local_9c[0] = local_4c;
      local_9c[1] = local_48;
      local_9c[2] = local_44;
      local_9c[3] = fStack_40;
      pfVar4 = &local_20;
    }
    else {
      out_block[1] = uVar8;
      *out_block = uVar10;
      local_9c[0] = local_20;
      local_9c[1] = local_1c;
      local_9c[2] = local_18;
      local_9c[3] = fStack_14;
      pfVar4 = &local_4c;
    }
    local_8c = *pfVar4;
    local_88 = pfVar4[1];
    local_84 = pfVar4[2];
    local_80 = pfVar4[3];
    local_20 = *pfVar4 - local_9c[0];
    if (local_10 == 4.2039e-45) {
      local_24 = &grim_dxt1_index_map_3color;
      local_7c = local_20 * 0.5;
      local_78 = (local_88 - local_9c[1]) * 0.5;
      local_74 = (local_84 - local_9c[2]) * 0.5;
      local_70 = (local_80 - local_9c[3]) * 0.5;
    }
    else {
      local_24 = &grim_dxt1_index_map_4color;
      local_7c = local_20 * 0.33333334;
      local_78 = (local_88 - local_9c[1]) * 0.33333334;
      local_74 = (local_84 - local_9c[2]) * 0.33333334;
      local_70 = (local_80 - local_9c[3]) * 0.33333334;
      local_6c = local_20 * 0.6666667 + local_9c[0];
      local_68 = (local_88 - local_9c[1]) * 0.6666667 + local_9c[1];
      local_64 = (local_84 - local_9c[2]) * 0.6666667 + local_9c[2];
      local_60 = (local_80 - local_9c[3]) * 0.6666667 + local_9c[3];
    }
    local_70 = local_70 + local_9c[3];
    local_74 = local_74 + local_9c[2];
    local_78 = local_78 + local_9c[1];
    local_7c = local_7c + local_9c[0];
    mode = local_84 - local_9c[2];
    fVar6 = local_88 - local_9c[1];
    local_8 = (float)((int)local_10 + -1);
    if ((int)local_10 + -1 < 0) {
      local_8 = local_8 + 4.2949673e+09;
    }
    if ((short)local_28 == (short)local_2c) {
      fVar1 = 0.0;
    }
    else {
      fVar1 = local_8 / (local_20 * local_20 + fVar6 * fVar6 + mode * mode);
    }
    local_20 = local_20 * fVar1;
    pfVar4 = &local_1d4;
    for (iVar11 = 0x40; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar4 = 0.0;
      pfVar4 = pfVar4 + 1;
    }
    local_1c = fVar1 * fVar6;
    local_18 = fVar1 * mode;
    fpu_save_control_word();
    local_c = &local_1d4;
    local_2c = (float *)(local_1cc + (-4 - in_EAX));
    local_58 = local_1c0 + -in_EAX;
    local_54 = local_1a0 + -in_EAX;
    iVar11 = (int)local_2d4 + (8 - in_EAX);
    pfVar4 = (float *)(in_EAX + 4);
    local_50 = local_180 + -in_EAX;
    fVar6 = extraout_EDX_00;
    mode = extraout_EDX_00;
    do {
      if ((local_10 != 4.2039e-45) || (0.5 <= pfVar4[2])) {
        local_4c = DAT_100544c0 * pfVar4[-1] + *local_c;
        local_48 = DAT_100544c4 * *pfVar4 + *(float *)((int)pfVar4 + local_a8);
        local_44 = DAT_100544c8 * pfVar4[1] + *(float *)((int)local_2c + (int)pfVar4);
        fVar1 = (local_48 - local_9c[1]) * local_1c +
                (local_44 - local_9c[2]) * local_18 + (local_4c - local_9c[0]) * local_20;
        if (fVar1 < 0.0 == (fVar1 == 0.0)) {
          if (fVar1 < local_8) {
            local_28 = (float *)(fVar1 + 0.5);
            local_5c = (undefined1 *)(int)ROUND(fVar1 + 0.5);
            iVar9 = *(int *)(local_24 + (int)local_5c * 4);
          }
          else {
            iVar9 = 1;
          }
        }
        else {
          iVar9 = 0;
        }
        fVar6 = (float)((uint)fVar6 >> 2 | iVar9 << 0x1e);
        fVar1 = (local_4c - local_9c[iVar9 * 4]) * *(float *)(iVar11 + (int)pfVar4);
        uVar7 = (uint)mode & 3;
        fVar2 = (local_48 - local_9c[iVar9 * 4 + 1]) * *(float *)(iVar11 + (int)pfVar4);
        local_38 = fVar2;
        fVar3 = (local_44 - local_9c[iVar9 * 4 + 2]) * *(float *)(iVar11 + (int)pfVar4);
        local_34 = fVar3;
        if (uVar7 != 3) {
          *(float *)(local_b8 + (int)pfVar4) = fVar1 * 0.4375 + *(float *)(local_b8 + (int)pfVar4);
          *(float *)(local_c0 + (int)pfVar4) = fVar2 * 0.4375 + *(float *)(local_c0 + (int)pfVar4);
          *(float *)(local_58 + (int)pfVar4) = fVar3 * 0.4375 + *(float *)(local_58 + (int)pfVar4);
        }
        if ((uint)mode < 0xc) {
          if (uVar7 != 0) {
            *(float *)(local_b4 + (int)pfVar4) = fVar1 * 0.1875 + *(float *)(local_b4 + (int)pfVar4)
            ;
            *(float *)(local_ac + (int)pfVar4) = fVar2 * 0.1875 + *(float *)(local_ac + (int)pfVar4)
            ;
            *(float *)(local_54 + (int)pfVar4) = fVar3 * 0.1875 + *(float *)(local_54 + (int)pfVar4)
            ;
          }
          *(float *)(local_bc + (int)pfVar4) = fVar1 * 0.3125 + *(float *)(local_bc + (int)pfVar4);
          *(float *)(local_a4 + (int)pfVar4) = fVar2 * 0.3125 + *(float *)(local_a4 + (int)pfVar4);
          *(float *)(((int)&local_190 - in_EAX) + (int)pfVar4) =
               fVar3 * 0.3125 + *(float *)(((int)&local_190 - in_EAX) + (int)pfVar4);
          if (uVar7 != 3) {
            *(float *)(local_a0 + (int)pfVar4) = fVar1 * 0.0625 + *(float *)(local_a0 + (int)pfVar4)
            ;
            *(float *)(local_b0 + (int)pfVar4) =
                 local_38 * 0.0625 + *(float *)(local_b0 + (int)pfVar4);
            *(float *)(local_50 + (int)pfVar4) =
                 local_34 * 0.0625 + *(float *)(local_50 + (int)pfVar4);
          }
        }
      }
      else {
        fVar6 = (float)((uint)fVar6 >> 2 | 0xc0000000);
      }
      mode = (float)((int)mode + 1);
      local_c = local_c + 4;
      pfVar4 = pfVar4 + 4;
    } while ((uint)mode < 0x10);
    *(float *)(out_block + 2) = fVar6;
  }
  return 0;
}



/* grim_dxt1_decode_color_block @ 10021899 */

/* decodes a DXT1 color block into 16 RGBA floats */

int __cdecl grim_dxt1_decode_color_block(float *out_rgba,ushort *block)

{
  float *pfVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  uint in_EDX;
  uint rgb565;
  uint uVar5;
  uint uVar6;
  float local_5c [4];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  
  uVar2 = *block;
  grim_dxt_decode_rgb565((float *)(uint)uVar2,in_EDX);
  uVar3 = block[1];
  grim_dxt_decode_rgb565((float *)(uint)uVar3,rgb565);
  if (uVar3 < uVar2) {
    local_3c = (local_4c - local_5c[0]) * 0.33333334 + local_5c[0];
    local_38 = (local_48 - local_5c[1]) * 0.33333334 + local_5c[1];
    local_8 = local_44 - local_5c[2];
    local_34 = local_8 * 0.33333334 + local_5c[2];
    local_c = local_40 - local_5c[3];
    local_30 = local_c * 0.33333334 + local_5c[3];
    local_2c = (local_4c - local_5c[0]) * 0.6666667 + local_5c[0];
    local_28 = (local_48 - local_5c[1]) * 0.6666667 + local_5c[1];
    local_24 = local_8 * 0.6666667 + local_5c[2];
    local_20 = local_c * 0.6666667 + local_5c[3];
  }
  else {
    local_3c = (local_4c - local_5c[0]) * 0.5 + local_5c[0];
    local_38 = (local_48 - local_5c[1]) * 0.5 + local_5c[1];
    local_34 = (local_44 - local_5c[2]) * 0.5 + local_5c[2];
    local_30 = (local_40 - local_5c[3]) * 0.5 + local_5c[3];
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    local_2c = 0.0;
    local_28 = 0.0;
    local_24 = 0.0;
    local_20 = 0.0;
  }
  uVar6 = *(uint *)(block + 2);
  iVar4 = 0x10;
  do {
    uVar5 = uVar6 & 3;
    *out_rgba = local_5c[uVar5 * 4];
    out_rgba[1] = local_5c[uVar5 * 4 + 1];
    pfVar1 = out_rgba + 3;
    out_rgba[2] = local_5c[uVar5 * 4 + 2];
    out_rgba = out_rgba + 4;
    uVar6 = uVar6 >> 2;
    iVar4 = iVar4 + -1;
    *pfVar1 = local_5c[uVar5 * 4 + 3];
  } while (iVar4 != 0);
  return 0;
}



/* grim_dxt3_decode_block @ 100219d7 */

/* WARNING: Removing unreachable block (ram,0x10021a10) */
/* WARNING: Removing unreachable block (ram,0x10021a3f) */
/* decodes a DXT3 block (explicit alpha + DXT1 color) to RGBA floats */

int __cdecl grim_dxt3_decode_block(float *out_rgba,uint *block)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = grim_dxt1_decode_color_block(out_rgba,(ushort *)(block + 2));
  if (-1 < iVar1) {
    uVar3 = *block;
    iVar1 = 8;
    pfVar2 = out_rgba + 3;
    do {
      uVar4 = uVar3 & 0xf;
      uVar3 = uVar3 >> 4;
      *pfVar2 = (float)uVar4 * 0.06666667;
      pfVar2 = pfVar2 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    uVar3 = block[1];
    iVar1 = 8;
    pfVar2 = out_rgba + 0x23;
    do {
      uVar4 = uVar3 & 0xf;
      uVar3 = uVar3 >> 4;
      *pfVar2 = (float)uVar4 * 0.06666667;
      pfVar2 = pfVar2 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    iVar1 = 0;
  }
  return iVar1;
}



/* grim_dxt5_decode_block @ 10021a5a */

/* decodes a DXT5 block (interpolated alpha + DXT1 color) to RGBA floats */

int __cdecl grim_dxt5_decode_block(float *out_rgba,uchar *block)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  uint uVar6;
  float local_24 [8];
  
  iVar3 = grim_dxt1_decode_color_block(out_rgba,(ushort *)(block + 8));
  if (-1 < iVar3) {
    local_24[0] = (float)*block * 0.003921569;
    local_24[1] = (float)block[1] * 0.003921569;
    if (block[1] < *block) {
      uVar4 = 1;
      do {
        fVar1 = (float)(int)(7 - uVar4);
        if ((int)(7 - uVar4) < 0) {
          fVar1 = fVar1 + 4.2949673e+09;
        }
        fVar2 = (float)(int)uVar4;
        if ((int)uVar4 < 0) {
          fVar2 = fVar2 + 4.2949673e+09;
        }
        uVar4 = uVar4 + 1;
        local_24[uVar4] = (fVar2 * local_24[1] + fVar1 * local_24[0]) * 0.14285715;
      } while (uVar4 < 7);
    }
    else {
      uVar4 = 1;
      do {
        fVar1 = (float)(int)(5 - uVar4);
        if ((int)(5 - uVar4) < 0) {
          fVar1 = fVar1 + 4.2949673e+09;
        }
        fVar2 = (float)(int)uVar4;
        if ((int)uVar4 < 0) {
          fVar2 = fVar2 + 4.2949673e+09;
        }
        uVar4 = uVar4 + 1;
        local_24[uVar4] = (fVar2 * local_24[1] + fVar1 * local_24[0]) * 0.2;
      } while (uVar4 < 5);
      local_24[6] = 0.0;
      local_24[7] = 1.0;
    }
    iVar3 = 8;
    uVar4 = (uint)*(uint3 *)(block + 2);
    pfVar5 = out_rgba + 3;
    do {
      uVar6 = uVar4 & 7;
      uVar4 = uVar4 >> 3;
      *pfVar5 = local_24[uVar6];
      pfVar5 = pfVar5 + 4;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar3 = 8;
    uVar4 = (uint)*(uint3 *)(block + 5);
    pfVar5 = out_rgba + 0x23;
    do {
      uVar6 = uVar4 & 7;
      uVar4 = uVar4 >> 3;
      *pfVar5 = local_24[uVar6];
      pfVar5 = pfVar5 + 4;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar3 = 0;
  }
  return iVar3;
}



/* grim_dxt3_encode_block @ 10021bae */

/* encodes a 4x4 RGBA block into DXT3 (explicit alpha + DXT1 color) */

void __cdecl grim_dxt3_encode_block(uint *out_block,float *rgba)

{
  uint *puVar1;
  float fVar2;
  uint *puVar3;
  int iVar4;
  uint *extraout_EDX;
  uint uVar5;
  float *pfVar6;
  float local_54 [16];
  int local_14;
  int local_10;
  float local_c;
  float *local_8;
  
  puVar3 = out_block;
  *out_block = 0;
  out_block[1] = 0;
  pfVar6 = local_54;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar6 = 0.0;
    pfVar6 = pfVar6 + 1;
  }
  fpu_save_control_word();
  local_8 = rgba + 3;
  out_block = extraout_EDX;
  do {
    local_c = local_54[(int)out_block] + *local_8;
    local_14 = (int)ROUND(local_c * 15.0 + 0.5);
    puVar1 = puVar3 + ((uint)out_block >> 3);
    local_10 = local_14;
    fVar2 = (float)local_14;
    *puVar1 = *puVar1 >> 4 | local_14 << 0x1c;
    if (local_14 < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    uVar5 = (uint)out_block & 3;
    fVar2 = local_c - fVar2 * 0.06666667;
    if (uVar5 != 3) {
      local_54[(int)out_block + 1] = fVar2 * 0.4375 + local_54[(int)out_block + 1];
    }
    if (out_block < (uint *)0xc) {
      if (uVar5 != 0) {
        local_54[(int)out_block + 3] = fVar2 * 0.1875 + local_54[(int)out_block + 3];
      }
      local_54[(int)(out_block + 1)] = fVar2 * 0.3125 + local_54[(int)(out_block + 1)];
      if (uVar5 != 3) {
        local_54[(int)out_block + 5] = fVar2 * 0.0625 + local_54[(int)out_block + 5];
      }
    }
    out_block = (uint *)((int)out_block + 1);
    local_8 = local_8 + 4;
  } while (out_block < (uint *)0x10);
  grim_dxt1_encode_color_block((ushort *)(puVar3 + 2),0.0);
  return;
}



/* grim_dxt5_encode_block @ 10021cc2 */

/* encodes a 4x4 RGBA block into DXT5 (interpolated alpha + DXT1 color) */

int __cdecl grim_dxt5_encode_block(uchar *out_block,float *rgba)

{
  float fVar1;
  float fVar2;
  uchar *puVar3;
  uchar uVar4;
  uint uVar5;
  uchar uVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  float fVar10;
  uint uVar11;
  float *pfVar12;
  float local_a4 [32];
  int local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined *local_14;
  float *local_10;
  float *local_c;
  float local_8;
  
  pfVar9 = rgba + 3;
  local_10 = (float *)*pfVar9;
  pfVar12 = local_a4;
  local_c = local_10;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar12 = 0.0;
    pfVar12 = pfVar12 + 1;
  }
  fpu_save_control_word();
  puVar3 = out_block;
  uVar8 = 0;
  pfVar12 = pfVar9;
  do {
    local_18 = local_a4[uVar8] + *pfVar12;
    local_14 = (undefined *)(int)ROUND(local_18 * 255.0 + 0.5);
    local_8 = (float)local_14;
    fVar10 = (float)(int)local_14 * 0.003921569;
    local_a4[uVar8 + 0x10] = fVar10;
    if ((float)local_c <= fVar10) {
      if ((float)local_10 < fVar10) {
        local_10 = (float *)fVar10;
      }
    }
    else {
      local_c = (float *)fVar10;
    }
    fVar10 = local_18 - fVar10;
    uVar11 = uVar8 & 3;
    if (uVar11 != 3) {
      local_a4[uVar8 + 1] = fVar10 * 0.4375 + local_a4[uVar8 + 1];
    }
    if (uVar8 < 0xc) {
      if (uVar11 != 0) {
        local_a4[uVar8 + 3] = fVar10 * 0.1875 + local_a4[uVar8 + 3];
      }
      local_a4[uVar8 + 4] = fVar10 * 0.3125 + local_a4[uVar8 + 4];
      if (uVar11 != 3) {
        local_a4[uVar8 + 5] = fVar10 * 0.0625 + local_a4[uVar8 + 5];
      }
    }
    uVar8 = uVar8 + 1;
    pfVar12 = pfVar12 + 4;
  } while (uVar8 < 0x10);
  local_8 = fpu_control_word_saved_dxt;
  iVar7 = grim_dxt1_encode_color_block((ushort *)(out_block + 8),0.0);
  if (iVar7 < 0) {
    return iVar7;
  }
  if ((float)local_c == 1.0) {
    *puVar3 = 0xff;
    puVar3[1] = 0xff;
LAB_10021ea4:
    puVar3[2] = '\0';
    puVar3[3] = '\0';
    puVar3[4] = '\0';
    puVar3[5] = '\0';
    puVar3[6] = '\0';
    puVar3[7] = '\0';
  }
  else {
    if (((float)local_c == 0.0) || ((float)local_10 == 1.0)) {
      rgba = (float *)0x6;
      uVar8 = 6;
    }
    else {
      uVar8 = 8;
      rgba = (float *)0x8;
    }
    grim_dxt5_optimize_alpha_endpoints(&local_8,(float *)&out_block,local_a4 + 0x10,uVar8);
    fpu_save_control_word();
    uVar11 = (uint)ROUND(local_8 * 255.0 + 0.5);
    local_8 = (float)(int)ROUND((float)out_block * 255.0 + 0.5);
    fVar10 = (float)(uVar11 & 0xff) * 0.003921569;
    local_a4[0x19] = (float)((uint)local_8 & 0xff) * 0.003921569;
    uVar4 = (uchar)uVar11;
    uVar6 = SUB41(local_8,0);
    if (uVar8 == 8) {
      if (uVar4 == uVar6) {
        *puVar3 = uVar4;
        puVar3[1] = uVar6;
        goto LAB_10021ea4;
      }
LAB_10021f19:
      puVar3[1] = uVar4;
      *puVar3 = uVar6;
      uVar11 = 1;
      do {
        fVar1 = (float)(int)(7 - uVar11);
        if ((int)(7 - uVar11) < 0) {
          fVar1 = fVar1 + 4.2949673e+09;
        }
        fVar2 = (float)(int)uVar11;
        if ((int)uVar11 < 0) {
          fVar2 = fVar2 + 4.2949673e+09;
        }
        uVar5 = uVar11 + 1;
        local_a4[uVar11 + 0x19] = (fVar2 * fVar10 + fVar1 * local_a4[0x19]) * 0.14285715;
        uVar11 = uVar5;
      } while (uVar5 < 7);
      local_14 = &grim_dxt5_alpha_index_map_8;
      local_a4[0x18] = local_a4[0x19];
      local_a4[0x19] = fVar10;
    }
    else {
      if (uVar8 != 6) goto LAB_10021f19;
      *puVar3 = uVar4;
      puVar3[1] = uVar6;
      uVar11 = 1;
      do {
        fVar1 = (float)(int)(5 - uVar11);
        if ((int)(5 - uVar11) < 0) {
          fVar1 = fVar1 + 4.2949673e+09;
        }
        fVar2 = (float)(int)uVar11;
        if ((int)uVar11 < 0) {
          fVar2 = fVar2 + 4.2949673e+09;
        }
        uVar5 = uVar11 + 1;
        local_a4[uVar11 + 0x19] = (fVar2 * local_a4[0x19] + fVar1 * fVar10) * 0.2;
        uVar11 = uVar5;
      } while (uVar5 < 5);
      local_14 = &grim_dxt5_alpha_index_map_6;
      local_a4[0x1e] = 0.0;
      local_a4[0x1f] = 1.0;
      local_a4[0x18] = fVar10;
    }
    out_block = (uchar *)(uVar8 - 1);
    local_1c = (float)(int)out_block;
    if ((int)out_block < 0) {
      local_1c = local_1c + 4.2949673e+09;
    }
    if (local_a4[0x18] == local_a4[0x19]) {
      local_18 = 0.0;
    }
    else {
      local_18 = local_1c / (local_a4[0x19] - local_a4[0x18]);
    }
    pfVar12 = local_a4;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      *pfVar12 = 0.0;
      pfVar12 = pfVar12 + 1;
    }
    fpu_save_control_word();
    local_c = pfVar9;
    fVar10 = 0.0;
    do {
      uVar8 = 0;
      out_block._2_1_ = '\0';
      local_8 = (float)((int)fVar10 + 8U);
      if ((uint)fVar10 < (int)fVar10 + 8U) {
        local_10 = local_c;
        do {
          fVar1 = local_a4[(int)fVar10] + *local_10;
          fVar2 = (fVar1 - local_a4[0x18]) * local_18;
          if (fVar2 < 0.0 == (fVar2 == 0.0)) {
            if (fVar2 < local_1c) {
              local_20 = fVar2 + 0.5;
              local_24 = (int)ROUND(fVar2 + 0.5);
              iVar7 = *(int *)(local_14 + local_24 * 4);
            }
            else if ((rgba == (float *)0x6) &&
                    (fVar2 = (local_a4[0x19] + 1.0) * 0.5, fVar2 < fVar1 != (fVar2 == fVar1))) {
              iVar7 = 7;
            }
            else {
              iVar7 = 1;
            }
          }
          else if ((rgba != (float *)0x6) || (local_a4[0x18] * 0.5 < fVar1)) {
            iVar7 = 0;
          }
          else {
            iVar7 = 6;
          }
          fVar1 = fVar1 - local_a4[iVar7 + 0x18];
          uVar8 = uVar8 >> 3 | iVar7 << 0x15;
          uVar11 = (uint)fVar10 & 3;
          if (uVar11 != 3) {
            local_a4[(int)fVar10 + 1] = fVar1 * 0.4375 + local_a4[(int)fVar10 + 1];
          }
          if ((uint)fVar10 < 0xc) {
            if (uVar11 != 0) {
              local_a4[(int)fVar10 + 3] = fVar1 * 0.1875 + local_a4[(int)fVar10 + 3];
            }
            local_a4[(int)fVar10 + 4] = fVar1 * 0.3125 + local_a4[(int)fVar10 + 4];
            if (uVar11 != 3) {
              local_a4[(int)fVar10 + 5] = fVar1 * 0.0625 + local_a4[(int)fVar10 + 5];
            }
          }
          local_10 = local_10 + 4;
          fVar10 = (float)((int)fVar10 + 1);
        } while ((uint)fVar10 < (uint)local_8);
        out_block._2_1_ = (uchar)(uVar8 >> 0x10);
      }
      local_c = local_c + 0x20;
      puVar3[4] = out_block._2_1_;
      puVar3[2] = (uchar)uVar8;
      puVar3[3] = (uchar)(uVar8 >> 8);
      fVar10 = local_8;
      puVar3 = puVar3 + 3;
    } while ((uint)local_8 < 0x10);
  }
  return 0;
}



/* grim_dxt2_encode_block @ 1002215a */

/* premultiplies RGBA and encodes a DXT3-style block (DXT2) */

int __cdecl grim_dxt2_encode_block(void *out_block)

{
  int iVar1;
  int extraout_EAX;
  float local_104 [64];
  
  iVar1 = grim_dxt_premultiply_rgba_block(local_104);
  if (-1 < iVar1) {
    grim_dxt3_encode_block(out_block,local_104);
    iVar1 = extraout_EAX;
    if (-1 < extraout_EAX) {
      iVar1 = 0;
    }
  }
  return iVar1;
}



/* grim_dxt4_encode_block @ 1002218e */

/* premultiplies RGBA and encodes a DXT5-style block (DXT4) */

int __cdecl grim_dxt4_encode_block(void *out_block)

{
  int iVar1;
  float local_104 [64];
  
  iVar1 = grim_dxt_premultiply_rgba_block(local_104);
  if (-1 < iVar1) {
    iVar1 = grim_dxt5_encode_block(out_block,local_104);
    if (-1 < iVar1) {
      iVar1 = 0;
    }
  }
  return iVar1;
}



/* grim_dxt_color_block_optimize @ 100223f0 */

/* WARNING: Removing unreachable block (ram,0x1002246d) */
/* WARNING: Removing unreachable block (ram,0x1002245b) */
/* WARNING: Removing unreachable block (ram,0x10022440) */
/* WARNING: Removing unreachable block (ram,0x10022424) */
/* WARNING: Removing unreachable block (ram,0x10022419) */

undefined8 grim_dxt_color_block_optimize(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  bool bVar7;
  char local_2c [16];
  int local_1c;
  uint local_18;
  int local_14;
  char cStack_10;
  undefined4 local_c;
  uint local_8;
  
  cStack_10 = '\0';
  builtin_strncpy(local_2c,"AuthenticAMD",0xd);
  cpuid_basic_info(0);
  local_8 = 1;
  piVar6 = (int *)cpuid_basic_info(0);
  local_18 = piVar6[2];
  local_1c = piVar6[1];
  local_14 = piVar6[3];
  if (*piVar6 != 0) {
    puVar1 = (undefined4 *)cpuid_Version_info(1);
    local_c = *puVar1;
    uVar3 = -(uint)((puVar1[2] & 0x800000) != 0) & 0x20;
    local_8 = uVar3 | 3;
    puVar2 = (uint *)cpuid(0x80000000);
    local_18 = puVar2[2];
    if (0x80000000 < *puVar2) {
      iVar4 = cpuid(0x80000001);
      local_18 = *(uint *)(iVar4 + 8);
      local_8 = uVar3 | 7 | -(uint)((local_18 & 0x80000000) != 0) & 0x80;
      bVar7 = local_8 == 0;
      iVar4 = 0xc;
      pcVar5 = local_2c;
      piVar6 = &local_1c;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar7 = *pcVar5 == (char)*piVar6;
        pcVar5 = pcVar5 + 1;
        piVar6 = (int *)((int)piVar6 + 1);
      } while (bVar7);
      if (bVar7) {
        local_8 = local_8 | -(uint)((local_18 & 0x40000000) != 0) & 0x100 |
                  -(uint)((local_18 & 0x400000) != 0) & 0x200;
      }
    }
  }
  return CONCAT44(local_18,local_8);
}



/* grim_crc32 @ 10025aec */

uint __cdecl grim_crc32(uint param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  if (param_2 == (byte *)0x0) {
    return 0;
  }
  uVar2 = ~param_1;
  if (7 < param_3) {
    uVar1 = param_3 >> 3;
    do {
      param_3 = param_3 - 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((*param_2 ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[1] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[2] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[3] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[4] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[5] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = *(uint *)(&DAT_1004ef90 + ((param_2[6] ^ uVar2) & 0xff) * 4) ^ uVar2 >> 8;
      uVar2 = uVar2 >> 8 ^ *(uint *)(&DAT_1004ef90 + ((param_2[7] ^ uVar2) & 0xff) * 4);
      param_2 = param_2 + 8;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  for (; param_3 != 0; param_3 = param_3 - 1) {
    uVar2 = uVar2 >> 8 ^ *(uint *)(&DAT_1004ef90 + ((*param_2 ^ uVar2) & 0xff) * 4);
    param_2 = param_2 + 1;
  }
  return ~uVar2;
}



/* grim_dxt1_color_lerp_2_3 @ 10025c00 */

float * grim_dxt1_color_lerp_2_3(float *param_1,float *param_2,float *param_3)

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



/* grim_dxt1_color_lerp_1_2 @ 10025c40 */

undefined8 * grim_dxt1_color_lerp_1_2(undefined8 *param_1,float *param_2,float *param_3)

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



/* grim_dxt_color_endpoint_refine @ 10027fc6 */

void grim_dxt_color_endpoint_refine(undefined8 *param_1,undefined8 *param_2,undefined4 *param_3)

{
  undefined8 uVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  uVar4 = *param_1;
  uVar1 = param_1[1];
  uVar5 = PackedFloatingMUL(uVar4,uVar4);
  uVar3 = PackedFloatingMUL(uVar1,uVar1);
  uVar5 = PackedFloatingADD(uVar5,uVar3);
  uVar5 = PackedFloatingAccumulate(uVar5,uVar5);
  uVar6 = PackedFloatingCompareGE(0x80000000800000,uVar5);
  uVar3 = PackedFloatingReciprocalSQRAprox(uVar3,uVar5);
  if ((int)uVar6 == 0) {
    uVar6 = PackedFloatingMUL(uVar3,uVar3);
    if (param_2 != (undefined8 *)0x0) {
      uVar5 = PackedFloatingReciprocalSQRIter1(uVar6,uVar5);
      uVar3 = PackedFloatingReciprocalIter2(uVar5,uVar3);
      uVar5 = PackedFloatingMUL(uVar4,uVar3);
      uVar4 = PackedFloatingMUL(uVar3,uVar1);
      *param_2 = uVar5;
      *(int *)(param_2 + 1) = (int)uVar4;
    }
    if (param_3 != (undefined4 *)0x0) {
      uVar2 = grim_jpg_idct_descale_trunc();
      uVar4 = PackedFloatingMUL(uVar2,0x4000000040000000);
      *param_3 = (int)uVar4;
    }
  }
  else {
    if (param_2 != (undefined8 *)0x0) {
      *(undefined8 *)((int)param_2 + 4) = 0;
      *(undefined4 *)param_2 = 0x3f800000;
    }
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = 0;
    }
  }
  FastExitMediaState();
  return;
}



/* grim_dxt_color_quantize_2bit @ 1002856f */

void grim_dxt_color_quantize_2bit(undefined8 *param_1,ulonglong *param_2,uint param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined8 local_18;
  uint local_10;
  
  FastExitMediaState();
  grim_dxt_color_distance_calc(&local_18,param_2);
  PackedFloatingMUL((ulonglong)param_3,0x3f0000003f000000);
  uVar1 = grim_jpg_idct_coeff_butterfly_a();
  uVar4 = (undefined4)(uVar1 >> 0x20);
  uVar3 = CONCAT44(uVar4,uVar4);
  uVar2 = PackedFloatingMUL(local_18,uVar3);
  uVar3 = PackedFloatingMUL((ulonglong)local_10,uVar3);
  *param_1 = uVar2;
  param_1[1] = CONCAT44((int)uVar1,(int)uVar3);
  FastExitMediaState();
  return;
}



/* grim_dxt_color_match_block @ 100285db */

void grim_dxt_color_match_block(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,uint param_4)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 uVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  ulonglong uVar3;
  
  FastExitMediaState();
  uVar4 = PackedFloatingMUL(*param_2,*param_3);
  uVar6 = PackedFloatingMUL(param_2[1],param_3[1]);
  uVar4 = PackedFloatingADD(uVar4,uVar6);
  uVar3 = PackedFloatingSUB(0x3f800000,(ulonglong)param_4);
  uVar1 = (undefined4)uVar3;
  uVar5 = PackedFloatingAccumulate(uVar4,uVar4);
  uVar10 = PackedFloatingCompareGE(0,uVar5);
  uVar11 = uVar10 & 0x8000000080000000;
  uVar5 = uVar5 ^ uVar11;
  uVar6 = PackedFloatingCompareGE(0x3f7fff583f7fff58,uVar5);
  uVar4 = PackedFloatingMUL(uVar5,uVar5);
  uVar4 = PackedFloatingSUBR(uVar4,0x3f8000003f800000);
  if ((int)uVar6 != 0) {
    uVar8 = PackedFloatingReciprocalSQRAprox((ulonglong)param_4,uVar4);
    uVar6 = PackedFloatingMUL(uVar8,uVar8);
    uVar4 = PackedFloatingReciprocalSQRIter1(uVar4,uVar6);
    uVar7 = PackedFloatingReciprocalIter2(uVar4,uVar8);
    uVar4 = FloatingReciprocalAprox(uVar6,uVar7);
    uVar6 = PackedFloatingReciprocalIter1(uVar7,uVar4);
    PackedFloatingReciprocalIter2(uVar6,uVar4);
    uVar5 = grim_jpg_idct_descale_round();
    PackedFloatingMUL(uVar5,(ulonglong)param_4);
    uVar2 = grim_jpg_idct_coeff_butterfly_b();
    PackedFloatingMUL(uVar5 & 0xffffffff,uVar3 & 0xffffffff);
    uVar4 = grim_jpg_idct_coeff_butterfly_b();
    uVar11 = uVar10 & 0x80000000;
    uVar4 = PackedFloatingMUL(uVar4,uVar7 & 0xffffffff);
    uVar1 = (undefined4)uVar4;
    uVar4 = PackedFloatingMUL((ulonglong)uVar2,uVar7 & 0xffffffff);
    param_4 = (uint)uVar4;
  }
  uVar2 = param_4 ^ (uint)uVar11;
  uVar6 = CONCAT44(uVar2,uVar2);
  uVar4 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),*param_2);
  uVar8 = PackedFloatingMUL(uVar6,*param_3);
  uVar9 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),param_2[1]);
  uVar6 = PackedFloatingMUL(uVar6,param_3[1]);
  uVar4 = PackedFloatingADD(uVar4,uVar8);
  uVar6 = PackedFloatingADD(uVar9,uVar6);
  *param_1 = uVar4;
  param_1[1] = uVar6;
  FastExitMediaState();
  return;
}



/* grim_dxt_color_match_2bit_a @ 10028712 */

undefined8 *
grim_dxt_color_match_2bit_a(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
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
  grim_dxt_color_match_block(local_28,param_2,param_3,(uint)uVar1);
  grim_dxt_color_match_block(local_18,param_2,param_4,(uint)uVar1);
  uVar3 = FloatingReciprocalAprox(in_MM2,uVar1 & 0xffffffff);
  uVar2 = PackedFloatingReciprocalIter1(uVar1 & 0xffffffff,uVar3);
  uVar2 = PackedFloatingReciprocalIter2(uVar2,uVar3);
  uVar2 = PackedFloatingMUL(uVar2,(ulonglong)param_6);
  grim_dxt_color_match_block(param_1,local_28,local_18,(uint)uVar2);
  FastExitMediaState();
  return param_1;
}



/* grim_dxt_color_match_2bit_b @ 1002879f */

void grim_dxt_color_match_2bit_b(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
                 undefined8 *param_5,uint param_6)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 local_20 [2];
  undefined8 local_10 [2];
  
  grim_dxt_color_match_block(local_20,param_2,param_5,param_6);
  grim_dxt_color_match_block(local_10,param_3,param_4,param_6);
  uVar1 = (ulonglong)param_6;
  uVar2 = PackedFloatingMUL(uVar1,uVar1);
  uVar2 = PackedFloatingSUB(uVar1,uVar2);
  uVar2 = PackedFloatingMUL(uVar2,0x4000000040000000);
  grim_dxt_color_match_block(param_1,local_20,local_10,(uint)uVar2);
  FastExitMediaState();
  return;
}



/* grim_dxt_color_endpoint_pick @ 10028895 */

void grim_dxt_color_endpoint_pick(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined4 uVar6;
  undefined8 uVar5;
  undefined8 in_MM4;
  undefined8 uVar7;
  
  FastExitMediaState();
  uVar3 = *param_2;
  uVar4 = param_2[1];
  uVar6 = (undefined4)(uVar4 >> 0x20);
  uVar5 = PackedFloatingCompareGE(CONCAT44(uVar6,uVar6),0x3f8000003f800000);
  if ((int)uVar5 == 0) {
    uVar1 = grim_jpg_idct_descale_trunc();
    uVar2 = grim_jpg_idct_coeff_butterfly_b();
    uVar5 = PackedFloatingCompareGE(uVar2 & 0x7fffffff7fffffff,0x3400000034000000);
    uVar3 = *param_2;
    uVar4 = param_2[1];
    if ((int)uVar5 != 0) {
      uVar7 = FloatingReciprocalAprox(in_MM4,uVar2);
      uVar5 = PackedFloatingReciprocalIter1(uVar2,uVar7);
      uVar5 = PackedFloatingReciprocalIter2(uVar5,uVar7);
      uVar5 = PackedFloatingMUL(CONCAT44((int)uVar1,(int)uVar1),uVar5);
      uVar3 = PackedFloatingMUL(uVar3,uVar5);
      uVar4 = PackedFloatingMUL(uVar4,uVar5);
    }
  }
  *param_1 = uVar3;
  param_1[1] = uVar4 & 0xffffffff;
  FastExitMediaState();
  return;
}



/* grim_dxt_color_cluster_fit @ 100289e1 */

void grim_dxt_color_cluster_fit(undefined8 *param_1,undefined8 *param_2,ulonglong *param_3,ulonglong *param_4,
                 ulonglong *param_5,ulonglong *param_6,ulonglong *param_7)

{
  undefined4 unaff_ESI;
  undefined8 uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
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
  uVar8 = *param_5;
  uVar13 = param_5[1];
  uVar1 = PackedFloatingADD(local_a8,uVar8);
  uVar4 = PackedFloatingADD(local_a0,uVar13);
  uVar6 = PackedFloatingSUB(local_a8,uVar8);
  uVar1 = PackedFloatingMUL(uVar1,uVar1);
  uVar9 = PackedFloatingSUB(local_a0,uVar13);
  uVar4 = PackedFloatingMUL(uVar4,uVar4);
  uVar6 = PackedFloatingMUL(uVar6,uVar6);
  uVar9 = PackedFloatingMUL(uVar9,uVar9);
  uVar1 = PackedFloatingADD(uVar1,uVar4);
  uVar6 = PackedFloatingADD(uVar6,uVar9);
  local_88 = *param_6;
  local_80 = param_6[1];
  uVar11 = PackedFloatingADD(uVar8,local_88);
  uVar12 = PackedFloatingADD(uVar13,local_80);
  uVar4 = PackedFloatingSUB(uVar8,local_88);
  uVar9 = PackedFloatingSUB(uVar13,local_80);
  uVar11 = PackedFloatingMUL(uVar11,uVar11);
  uVar12 = PackedFloatingMUL(uVar12,uVar12);
  uVar4 = PackedFloatingMUL(uVar4,uVar4);
  uVar9 = PackedFloatingMUL(uVar9,uVar9);
  uVar11 = PackedFloatingADD(uVar11,uVar12);
  uVar4 = PackedFloatingADD(uVar4,uVar9);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar11);
  uVar4 = PackedFloatingAccumulate(uVar6,uVar4);
  uVar1 = PackedFloatingCompareGT(uVar4,uVar1);
  uVar7 = packsswb(uVar1,uVar1);
  if ((uVar7 & 1) != 0) {
    local_a8 = *param_4 ^ 0x8000000080000000;
    local_a0 = param_4[1] ^ 0x8000000080000000;
  }
  if ((uVar7 & 0x10000) != 0) {
    local_88 = *param_6 ^ 0x8000000080000000;
    local_80 = param_6[1] ^ 0x8000000080000000;
  }
  local_78 = *param_7;
  uVar7 = param_7[1];
  uVar6 = PackedFloatingADD(local_88,local_78);
  uVar9 = PackedFloatingADD(local_80,uVar7);
  uVar1 = PackedFloatingSUB(local_88,local_78);
  uVar4 = PackedFloatingSUB(local_80,uVar7);
  uVar6 = PackedFloatingMUL(uVar6,uVar6);
  uVar9 = PackedFloatingMUL(uVar9,uVar9);
  uVar1 = PackedFloatingMUL(uVar1,uVar1);
  uVar4 = PackedFloatingMUL(uVar4,uVar4);
  uVar6 = PackedFloatingADD(uVar6,uVar9);
  uVar1 = PackedFloatingADD(uVar1,uVar4);
  uVar4 = PackedFloatingAccumulate(uVar6,uVar6);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar10 = PackedFloatingCompareGT(uVar1,uVar4);
  local_70 = uVar7;
  if ((uVar10 & 1) != 0) {
    local_78 = *param_7 ^ 0x8000000080000000;
    local_70 = param_7[1] ^ 0x8000000080000000;
  }
  uVar1 = PackedFloatingMUL(uVar8,uVar8);
  uVar4 = PackedFloatingMUL(uVar13,uVar13);
  uVar1 = PackedFloatingADD(uVar1,uVar4);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar4 = FloatingReciprocalAprox(uVar7,uVar1);
  uVar7 = PackedFloatingCompareGT(uVar1,0x80000000800000);
  uVar1 = PackedFloatingReciprocalIter1(uVar1,uVar4);
  uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar4);
  uVar4 = PackedFloatingMUL((uVar8 ^ 0x8000000080000000) & uVar7,uVar1);
  uVar11 = PackedFloatingMUL((uVar13 ^ 0x80000000) & uVar7,uVar1);
  uVar10 = CONCAT44((int)local_a8,(int)(local_a8 >> 0x20));
  uVar2 = CONCAT44((int)local_a0,(int)(local_a0 >> 0x20));
  uVar7 = PackedFloatingMUL(local_a8,uVar11);
  uVar1 = PackedFloatingMUL(local_a0,uVar4);
  uVar9 = PackedFloatingMUL(uVar2 ^ 0x80000000,uVar4);
  uVar6 = PackedFloatingMUL(uVar10,uVar11);
  uVar1 = PackedFloatingADD(uVar7 ^ 0x80000000,uVar1);
  uVar6 = PackedFloatingSUB(uVar6,uVar9);
  uVar14 = PackedFloatingMUL(uVar2,uVar11);
  uVar6 = PackedFloatingAccumulate(uVar6,uVar1);
  uVar12 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar4);
  uVar1 = PackedFloatingMUL(local_a8,uVar4);
  uVar9 = PackedFloatingMUL(local_a0 ^ 0x80000000,uVar11);
  uVar12 = PackedFloatingADD(uVar12,uVar14);
  uVar1 = PackedFloatingSUB(uVar9,uVar1);
  uVar10 = PackedFloatingAccumulate(uVar12,uVar1);
  uVar2 = CONCAT44((int)local_88,(int)(local_88 >> 0x20));
  uVar3 = CONCAT44((int)local_80,(int)(local_80 >> 0x20));
  uVar7 = PackedFloatingMUL(local_88,uVar11);
  uVar1 = PackedFloatingMUL(local_80,uVar4);
  uVar12 = PackedFloatingMUL(uVar3 ^ 0x80000000,uVar4);
  uVar9 = PackedFloatingMUL(uVar2,uVar11);
  uVar1 = PackedFloatingADD(uVar7 ^ 0x80000000,uVar1);
  uVar9 = PackedFloatingSUB(uVar9,uVar12);
  uVar14 = PackedFloatingMUL(uVar3,uVar11);
  uVar9 = PackedFloatingAccumulate(uVar9,uVar1);
  uVar12 = PackedFloatingMUL(uVar2 ^ 0x80000000,uVar4);
  uVar1 = PackedFloatingMUL(local_88,uVar4);
  uVar4 = PackedFloatingMUL(local_80 ^ 0x80000000,uVar11);
  uVar11 = PackedFloatingADD(uVar12,uVar14);
  uVar1 = PackedFloatingSUB(uVar4,uVar1);
  uVar7 = PackedFloatingAccumulate(uVar11,uVar1);
  uVar5 = (undefined4)(uVar10 >> 0x20);
  uVar4 = PackedFloatingCompareGE(CONCAT44(uVar5,uVar5),0x3f8000003f800000);
  uVar1 = uVar9;
  if ((int)uVar4 == 0) {
    uVar2 = grim_jpg_idct_descale_trunc();
    uVar3 = grim_jpg_idct_coeff_butterfly_b();
    uVar4 = PackedFloatingCompareGE(uVar3 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar4 != 0) {
      uVar1 = FloatingReciprocalAprox(uVar1,uVar3);
      uVar4 = PackedFloatingReciprocalIter1(uVar3,uVar1);
      uVar4 = PackedFloatingReciprocalIter2(uVar4,uVar1);
      uVar4 = PackedFloatingMUL(CONCAT44((int)uVar2,(int)uVar2),uVar4);
      uVar6 = PackedFloatingMUL(uVar6,uVar4);
      uVar10 = PackedFloatingMUL(uVar10,uVar4);
    }
  }
  uVar5 = (undefined4)(uVar7 >> 0x20);
  uVar4 = PackedFloatingCompareGE(CONCAT44(uVar5,uVar5),0x3f8000003f800000);
  if ((int)uVar4 == 0) {
    uVar2 = grim_jpg_idct_descale_trunc();
    uVar3 = grim_jpg_idct_coeff_butterfly_b();
    uVar4 = PackedFloatingCompareGE(uVar3 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar4 != 0) {
      uVar4 = FloatingReciprocalAprox(uVar1,uVar3);
      uVar1 = PackedFloatingReciprocalIter1(uVar3,uVar4);
      uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar4);
      uVar1 = PackedFloatingMUL(CONCAT44((int)uVar2,(int)uVar2),uVar1);
      uVar9 = PackedFloatingMUL(uVar9,uVar1);
      uVar7 = PackedFloatingMUL(uVar7,uVar1);
    }
  }
  uVar1 = PackedFloatingADD(uVar6,uVar9);
  uVar4 = PackedFloatingADD(uVar10 & 0xffffffff,uVar7 & 0xffffffff);
  uVar1 = PackedFloatingMUL(uVar1,0xbe800000be800000);
  uVar2 = PackedFloatingMUL(uVar4,0xbe800000be800000);
  uVar4 = PackedFloatingMUL(uVar1,uVar1);
  uVar6 = PackedFloatingMUL(uVar2 & 0xffffffff,uVar2 & 0xffffffff);
  uVar4 = PackedFloatingADD(uVar4,uVar6);
  uVar4 = PackedFloatingAccumulate(uVar4,uVar4);
  uVar6 = PackedFloatingReciprocalSQRAprox(uVar6,uVar4);
  uVar9 = PackedFloatingMUL(uVar6,uVar6);
  uVar9 = PackedFloatingReciprocalSQRIter1(uVar9,uVar4);
  uVar6 = PackedFloatingReciprocalIter2(uVar9,uVar6);
  PackedFloatingMUL(uVar4,uVar6);
  uVar7 = grim_jpg_idct_coeff_butterfly_a();
  uVar10 = PackedFloatingCompareGE(uVar7 & 0x7fffffffffffffff,0x3400000034000000);
  uVar5 = (undefined4)(uVar7 >> 0x20);
  uVar4 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),CONCAT44(unaff_ESI,(int)uVar6));
  local_20 = (undefined4)uVar2;
  if ((uVar10 & 0x100000000) != 0) {
    uVar4 = CONCAT44((int)uVar4,(int)uVar4);
    uVar6 = PackedFloatingMUL(uVar2 & 0xffffffff,uVar4);
    local_20 = (undefined4)uVar6;
    uVar1 = PackedFloatingMUL(uVar1,uVar4);
  }
  uVar10 = CONCAT44((int)uVar7,local_20);
  uVar2 = CONCAT44((int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
  uVar3 = CONCAT44(local_20,(int)uVar7);
  uVar7 = PackedFloatingMUL(uVar1,uVar13);
  uVar4 = PackedFloatingMUL(uVar10,uVar8);
  uVar9 = PackedFloatingMUL(uVar3 ^ 0x80000000,uVar8);
  uVar6 = PackedFloatingMUL(uVar2,uVar13);
  uVar4 = PackedFloatingADD(uVar7 ^ 0x80000000,uVar4);
  uVar6 = PackedFloatingSUB(uVar6,uVar9);
  uVar11 = PackedFloatingMUL(uVar3,uVar13);
  uVar6 = PackedFloatingAccumulate(uVar6,uVar4);
  uVar9 = PackedFloatingMUL(uVar2 ^ 0x80000000,uVar8);
  uVar1 = PackedFloatingMUL(uVar1,uVar8);
  *param_1 = uVar6;
  uVar4 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar13);
  uVar9 = PackedFloatingADD(uVar9,uVar11);
  uVar1 = PackedFloatingSUB(uVar4,uVar1);
  uVar1 = PackedFloatingAccumulate(uVar9,uVar1);
  param_1[1] = uVar1;
  uVar1 = PackedFloatingMUL(local_88,local_88);
  uVar4 = PackedFloatingMUL(local_80,local_80);
  uVar1 = PackedFloatingADD(uVar1,uVar4);
  uVar1 = PackedFloatingAccumulate(uVar1,uVar1);
  uVar4 = FloatingReciprocalAprox(uVar6,uVar1);
  uVar7 = PackedFloatingCompareGT(uVar1,0x80000000800000);
  uVar1 = PackedFloatingReciprocalIter1(uVar1,uVar4);
  uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar4);
  uVar4 = PackedFloatingMUL((local_88 ^ 0x8000000080000000) & uVar7,uVar1);
  uVar11 = PackedFloatingMUL((local_80 ^ 0x80000000) & uVar7,uVar1);
  uVar10 = CONCAT44((int)uVar8,(int)(uVar8 >> 0x20));
  uVar2 = CONCAT44((int)uVar13,(int)(uVar13 >> 0x20));
  uVar7 = PackedFloatingMUL(uVar8,uVar11);
  uVar1 = PackedFloatingMUL(uVar13,uVar4);
  uVar9 = PackedFloatingMUL(uVar2 ^ 0x80000000,uVar4);
  uVar6 = PackedFloatingMUL(uVar10,uVar11);
  uVar1 = PackedFloatingADD(uVar7 ^ 0x80000000,uVar1);
  uVar6 = PackedFloatingSUB(uVar6,uVar9);
  uVar14 = PackedFloatingMUL(uVar2,uVar11);
  uVar6 = PackedFloatingAccumulate(uVar6,uVar1);
  uVar12 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar4);
  uVar1 = PackedFloatingMUL(uVar8,uVar4);
  uVar9 = PackedFloatingMUL(uVar13 ^ 0x80000000,uVar11);
  uVar12 = PackedFloatingADD(uVar12,uVar14);
  uVar1 = PackedFloatingSUB(uVar9,uVar1);
  uVar13 = PackedFloatingAccumulate(uVar12,uVar1);
  uVar7 = CONCAT44((int)local_78,(int)(local_78 >> 0x20));
  uVar10 = CONCAT44((int)local_70,(int)(local_70 >> 0x20));
  uVar8 = PackedFloatingMUL(local_78,uVar11);
  uVar1 = PackedFloatingMUL(local_70,uVar4);
  uVar12 = PackedFloatingMUL(uVar10 ^ 0x80000000,uVar4);
  uVar9 = PackedFloatingMUL(uVar7,uVar11);
  uVar1 = PackedFloatingADD(uVar8 ^ 0x80000000,uVar1);
  uVar9 = PackedFloatingSUB(uVar9,uVar12);
  uVar14 = PackedFloatingMUL(uVar10,uVar11);
  uVar9 = PackedFloatingAccumulate(uVar9,uVar1);
  uVar12 = PackedFloatingMUL(uVar7 ^ 0x80000000,uVar4);
  uVar1 = PackedFloatingMUL(local_78,uVar4);
  uVar4 = PackedFloatingMUL(local_70 ^ 0x80000000,uVar11);
  uVar11 = PackedFloatingADD(uVar12,uVar14);
  uVar1 = PackedFloatingSUB(uVar4,uVar1);
  uVar8 = PackedFloatingAccumulate(uVar11,uVar1);
  uVar5 = (undefined4)(uVar13 >> 0x20);
  uVar4 = PackedFloatingCompareGE(CONCAT44(uVar5,uVar5),0x3f8000003f800000);
  uVar1 = uVar9;
  if ((int)uVar4 == 0) {
    uVar7 = grim_jpg_idct_descale_trunc();
    uVar10 = grim_jpg_idct_coeff_butterfly_b();
    uVar4 = PackedFloatingCompareGE(uVar10 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar4 != 0) {
      uVar1 = FloatingReciprocalAprox(uVar1,uVar10);
      uVar4 = PackedFloatingReciprocalIter1(uVar10,uVar1);
      uVar4 = PackedFloatingReciprocalIter2(uVar4,uVar1);
      uVar4 = PackedFloatingMUL(CONCAT44((int)uVar7,(int)uVar7),uVar4);
      uVar6 = PackedFloatingMUL(uVar6,uVar4);
      uVar13 = PackedFloatingMUL(uVar13,uVar4);
    }
  }
  uVar5 = (undefined4)(uVar8 >> 0x20);
  uVar4 = PackedFloatingCompareGE(CONCAT44(uVar5,uVar5),0x3f8000003f800000);
  if ((int)uVar4 == 0) {
    uVar7 = grim_jpg_idct_descale_trunc();
    uVar10 = grim_jpg_idct_coeff_butterfly_b();
    uVar4 = PackedFloatingCompareGE(uVar10 & 0x7fffffff7fffffff,0x3400000034000000);
    if ((int)uVar4 != 0) {
      uVar4 = FloatingReciprocalAprox(uVar1,uVar10);
      uVar1 = PackedFloatingReciprocalIter1(uVar10,uVar4);
      uVar1 = PackedFloatingReciprocalIter2(uVar1,uVar4);
      uVar1 = PackedFloatingMUL(CONCAT44((int)uVar7,(int)uVar7),uVar1);
      uVar9 = PackedFloatingMUL(uVar9,uVar1);
      uVar8 = PackedFloatingMUL(uVar8,uVar1);
    }
  }
  uVar1 = PackedFloatingADD(uVar6,uVar9);
  uVar4 = PackedFloatingADD(uVar13 & 0xffffffff,uVar8 & 0xffffffff);
  uVar1 = PackedFloatingMUL(uVar1,0xbe800000be800000);
  uVar7 = PackedFloatingMUL(uVar4,0xbe800000be800000);
  uVar4 = PackedFloatingMUL(uVar1,uVar1);
  uVar6 = PackedFloatingMUL(uVar7 & 0xffffffff,uVar7 & 0xffffffff);
  uVar4 = PackedFloatingADD(uVar4,uVar6);
  uVar4 = PackedFloatingAccumulate(uVar4,uVar4);
  uVar6 = PackedFloatingReciprocalSQRAprox(uVar6,uVar4);
  uVar9 = PackedFloatingMUL(uVar6,uVar6);
  uVar9 = PackedFloatingReciprocalSQRIter1(uVar9,uVar4);
  uVar6 = PackedFloatingReciprocalIter2(uVar9,uVar6);
  PackedFloatingMUL(uVar4,uVar6);
  uVar8 = grim_jpg_idct_coeff_butterfly_a();
  uVar13 = PackedFloatingCompareGE(uVar8 & 0x7fffffffffffffff,0x3400000034000000);
  uVar5 = (undefined4)(uVar8 >> 0x20);
  uVar4 = PackedFloatingMUL(CONCAT44(uVar5,uVar5),CONCAT44(unaff_ESI,(int)uVar6));
  local_20 = (undefined4)uVar7;
  if ((uVar13 & 0x100000000) != 0) {
    uVar4 = CONCAT44((int)uVar4,(int)uVar4);
    uVar6 = PackedFloatingMUL(uVar7 & 0xffffffff,uVar4);
    local_20 = (undefined4)uVar6;
    uVar1 = PackedFloatingMUL(uVar1,uVar4);
  }
  uVar13 = CONCAT44((int)uVar8,local_20);
  uVar7 = CONCAT44((int)uVar1,(int)((ulonglong)uVar1 >> 0x20));
  uVar10 = CONCAT44(local_20,(int)uVar8);
  uVar8 = PackedFloatingMUL(uVar1,local_80);
  uVar4 = PackedFloatingMUL(uVar13,local_88);
  uVar9 = PackedFloatingMUL(uVar10 ^ 0x80000000,local_88);
  uVar6 = PackedFloatingMUL(uVar7,local_80);
  uVar4 = PackedFloatingADD(uVar8 ^ 0x80000000,uVar4);
  uVar6 = PackedFloatingSUB(uVar6,uVar9);
  uVar9 = PackedFloatingMUL(uVar10,local_80);
  uVar4 = PackedFloatingAccumulate(uVar6,uVar4);
  uVar6 = PackedFloatingMUL(uVar7 ^ 0x80000000,local_88);
  uVar1 = PackedFloatingMUL(uVar1,local_88);
  *param_2 = uVar4;
  uVar4 = PackedFloatingMUL(uVar13 ^ 0x80000000,local_80);
  uVar6 = PackedFloatingADD(uVar6,uVar9);
  uVar1 = PackedFloatingSUB(uVar4,uVar1);
  uVar1 = PackedFloatingAccumulate(uVar6,uVar1);
  param_2[1] = uVar1;
  *param_3 = local_88;
  param_3[1] = local_80;
  FastExitMediaState();
  return;
}



/* grim_dxt_alpha_init_table @ 10029b22 */

void __cdecl grim_dxt_alpha_init_table(undefined8 *param_1)

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



/* grim_dxt_alpha_block_compress @ 10029ce2 */

void grim_dxt_alpha_block_compress(ulonglong *param_1,undefined8 *param_2,undefined8 *param_3,ulonglong *param_4,
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



/* grim_dxt_alpha_endpoint_refine @ 1002ae7a */

void grim_dxt_alpha_endpoint_refine(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 uVar9;
  undefined8 uVar8;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  
  PackedFloatingMUL(0x3f0000003f000000,param_3);
  PackedFloatingMUL(0x3f0000003f000000,param_2);
  uVar2 = grim_jpg_idct_coeff_butterfly_a();
  uVar3 = grim_jpg_idct_coeff_butterfly_a();
  uVar4 = grim_jpg_idct_coeff_butterfly_a();
  uVar1 = (undefined4)uVar4;
  uVar9 = (undefined4)(uVar4 >> 0x20);
  uVar7 = CONCAT44((int)uVar3,(int)uVar3);
  uVar12 = (undefined4)(uVar3 >> 0x20);
  uVar10 = CONCAT44(uVar12,uVar12);
  uVar5 = PackedFloatingMUL(CONCAT44(uVar1,uVar1) ^ 0x8000000000000000,uVar10);
  uVar6 = PackedFloatingMUL(CONCAT44(uVar1,uVar1),uVar7);
  uVar8 = PackedFloatingMUL(CONCAT44(uVar9,uVar9),uVar7);
  uVar10 = PackedFloatingMUL(CONCAT44(uVar9,uVar9) ^ 0x80000000,uVar10);
  uVar13 = CONCAT44((int)uVar2,(int)(uVar2 >> 0x20));
  uVar5 = PackedFloatingMUL(uVar5,uVar2);
  uVar7 = PackedFloatingMUL(uVar6,uVar13);
  uVar6 = PackedFloatingMUL(uVar8,uVar13);
  uVar8 = PackedFloatingMUL(uVar10,uVar2);
  uVar5 = PackedFloatingADD(uVar5,uVar6);
  uVar8 = PackedFloatingADD(uVar7,uVar8);
  uVar7 = PackedFloatingADD(uVar5,uVar5);
  uVar6 = PackedFloatingADD(uVar8,uVar8);
  uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
  uVar9 = (undefined4)((ulonglong)uVar8 >> 0x20);
  uVar13 = CONCAT44(uVar9,uVar9);
  uVar10 = PackedFloatingMUL(uVar5,uVar7);
  uVar5 = CONCAT44((int)uVar7,(int)uVar6);
  uVar11 = PackedFloatingMUL(uVar7,uVar13);
  uVar8 = PackedFloatingMUL(CONCAT44((int)uVar8,(int)uVar8),uVar5);
  uVar7 = PackedFloatingMUL(uVar5,CONCAT44(uVar1,uVar1));
  uVar5 = PackedFloatingMUL(uVar5,uVar13);
  uVar6 = CONCAT44((int)((ulonglong)uVar8 >> 0x20),(int)((ulonglong)uVar7 >> 0x20));
  param_1[6] = 0;
  uVar13 = PackedFloatingADD(CONCAT44((int)uVar8,(int)uVar8),uVar10);
  uVar8 = PackedFloatingAccumulate(uVar10,uVar10);
  uVar5 = CONCAT44((int)((ulonglong)uVar11 >> 0x20),(int)uVar5);
  uVar2 = PackedFloatingSUBR(uVar8,0x3f8000003f800000);
  uVar10 = PackedFloatingSUBR(uVar13,0x3f8000003f800000);
  uVar8 = PackedFloatingADD(uVar6,uVar5);
  param_1[5] = uVar2 & 0xffffffff;
  uVar3 = PackedFloatingSUB(uVar6,uVar5);
  uVar2 = PackedFloatingADD(uVar7,uVar11);
  uVar5 = PackedFloatingSUB(uVar7,uVar11);
  param_1[3] = uVar2 & 0xffffffff;
  param_1[1] = uVar3 >> 0x20;
  param_1[2] = CONCAT44((int)uVar10,(int)uVar3);
  *param_1 = CONCAT44((int)uVar8,(int)((ulonglong)uVar10 >> 0x20));
  param_1[4] = CONCAT44((int)uVar5,(int)((ulonglong)uVar8 >> 0x20));
  param_1[7] = 0x3f80000000000000;
  FastExitMediaState();
  return;
}



/* grim_dxt_alpha_quantize @ 1002b553 */

void grim_dxt_alpha_quantize(undefined8 *param_1,ulonglong *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  ulonglong local_20;
  uint local_18;
  
  local_20 = *param_2;
  local_18 = (uint)param_2[1];
  grim_dxt_color_distance_calc(&local_20,&local_20);
  uVar1 = grim_jpg_idct_coeff_butterfly_a();
  uVar2 = PackedFloatingSUBR(uVar1,0x3f8000003f800000);
  uVar9 = (undefined4)(uVar1 >> 0x20);
  uVar4 = (ulonglong)local_18;
  uVar5 = PackedFloatingMUL(CONCAT44(local_18,local_18),local_20);
  uVar2 = CONCAT44((int)uVar2,(int)uVar2);
  uVar3 = PackedFloatingMUL(CONCAT44(local_18,(int)(local_20 >> 0x20)),local_20);
  uVar8 = CONCAT44((int)uVar1,(int)uVar1);
  uVar3 = PackedFloatingMUL(uVar3,uVar2);
  uVar5 = PackedFloatingMUL(uVar5,uVar2);
  uVar6 = PackedFloatingMUL(local_20,local_20);
  uVar7 = PackedFloatingMUL(uVar4,uVar4);
  uVar6 = PackedFloatingMUL(uVar6,uVar2);
  uVar2 = PackedFloatingMUL(uVar7,uVar2);
  uVar6 = PackedFloatingADD(uVar6,uVar8);
  uVar1 = PackedFloatingADD(uVar2,uVar8);
  uVar2 = CONCAT44(uVar9,uVar9);
  uVar8 = PackedFloatingMUL(local_20,uVar2);
  uVar2 = PackedFloatingMUL(uVar4,uVar2);
  param_1[6] = 0;
  uVar7 = CONCAT44((int)uVar8,(int)uVar2);
  uVar9 = (undefined4)((ulonglong)uVar8 >> 0x20);
  uVar8 = CONCAT44(uVar9,uVar9);
  param_1[5] = uVar1 & 0xffffffff;
  uVar2 = PackedFloatingSUB(uVar3,uVar7);
  uVar1 = PackedFloatingADD(uVar3,uVar7);
  uVar4 = PackedFloatingSUB(uVar5,uVar8);
  *param_1 = CONCAT44((int)uVar1,(int)uVar6);
  param_1[1] = uVar4 & 0xffffffff;
  uVar8 = PackedFloatingADD(CONCAT44((int)uVar5,(int)uVar5),uVar8);
  param_1[3] = uVar1 >> 0x20;
  param_1[7] = 0x3f80000000000000;
  param_1[4] = CONCAT44((int)((ulonglong)uVar2 >> 0x20),(int)((ulonglong)uVar8 >> 0x20));
  param_1[2] = CONCAT44((int)((ulonglong)uVar6 >> 0x20),(int)uVar2);
  FastExitMediaState();
  return;
}



/* grim_dxt_alpha_cluster_fit @ 1002b66c */

void grim_dxt_alpha_cluster_fit(ulonglong *param_1,undefined8 *param_2,undefined8 *param_3,ulonglong *param_4,
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



/* grim_dxt_color_distance_calc @ 1002d2c2 */

void grim_dxt_color_distance_calc(undefined8 *param_1,ulonglong *param_2)

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


