/* grim_lzma_decompress_to_buffer @ 1000a840 */

/* [binja] bool __stdcall sub_1000a840(int32_t* arg1, uint32_t arg2, int32_t arg3, int32_t arg4) */

bool grim_lzma_decompress_to_buffer(int *arg1,uint arg2,int arg3,int arg4)

{
  void *pvVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar2 = arg2;
  pvVar1 = operator_new(arg2);
  *arg1 = (int)pvVar1;
  arg2 = uVar2;
  uVar2 = grim_lzma_decompress(pvVar1,&arg2,arg3,arg4);
  uVar3 = grim_check_valid_pool(uVar2);
  return (char)uVar3 == '\0';
}



/* grim_lzma_decompress_auto @ 1000a880 */

/* [binja] char* __stdcall sub_1000a880(char* arg1, uint32_t* arg2) */

char * grim_lzma_decompress_auto(char *arg1,uint *arg2)

{
  uint arg2_00;
  int arg4;
  char *arg3;
  
  if (*arg1 != '\x01') {
    return (char *)0x0;
  }
  arg2_00 = *(uint *)(arg1 + 5);
  arg4 = *(int *)(arg1 + 1);
  arg3 = arg1 + 9;
  *arg2 = arg2_00;
  arg1 = (char *)0x0;
  grim_lzma_decompress_to_buffer((int *)&arg1,arg2_00,(int)arg3,arg4);
  return arg1;
}



/* grim_zip_decompress @ 10016007 */

/* [binja] int32_t __thiscall sub_10016007(int32_t* arg1, void*** arg2, void*** arg3, int32_t arg4)
    */

int __thiscall grim_zip_decompress(void *this,int *arg1,void ***arg2,void ***arg3,int arg4)

{
  void *pvVar1;
  int iVar2;
  int *unaff_EBX;
  
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)this = 0;
  *(void ****)((int)this + 8) = arg3;
  if (((((uint)arg3 & 0xffff) == 0) || (5 < ((uint)arg3 & 0xffff))) ||
     (((uint)arg3 & 0xfff00000) != 0)) {
    return -0x7789f794;
  }
  arg1[0x10] = (uint)arg3 & 0x80000;
  pvVar1 = grim_pixel_format_create((uint *)arg1);
  *(void **)((int)this + 4) = pvVar1;
  if (pvVar1 != (void *)0x0) {
    pvVar1 = grim_pixel_format_create((uint *)arg2);
    *(void **)this = pvVar1;
    if (pvVar1 != (void *)0x0) {
      iVar2 = grim_mesh_converter_alloc(pvVar1,unaff_EBX);
      if (iVar2 < 0) goto LAB_100160f3;
      iVar2 = grim_mipmap_downsample_dxt(this);
      if ((((-1 < iVar2) || (iVar2 = grim_mipmap_level_create_generic(unaff_EBX), -1 < iVar2)) ||
          ((iVar2 = grim_mipmap_chain_create_and_fill(unaff_EBX), -1 < iVar2 ||
           ((iVar2 = grim_mipmap_chain_create_dxt(unaff_EBX), -1 < iVar2 ||
            (iVar2 = grim_mipmap_format_dispatch(unaff_EBX), -1 < iVar2)))))) ||
         ((iVar2 = grim_mesh_skin_process(unaff_EBX), -1 < iVar2 ||
          ((((iVar2 = grim_skin_blend_2weights(unaff_EBX), -1 < iVar2 ||
             (iVar2 = grim_skin_blend_3weights(unaff_EBX), -1 < iVar2)) ||
            (iVar2 = grim_model_load_with_mipmaps(unaff_EBX), -1 < iVar2)) ||
           (iVar2 = grim_mesh_texture_process(unaff_EBX), -1 < iVar2)))))) {
        iVar2 = 0;
        goto LAB_100160f3;
      }
    }
  }
  iVar2 = -0x7fffbffb;
LAB_100160f3:
  if (*(undefined4 **)((int)this + 4) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)((int)this + 4))(1);
    *(undefined4 *)((int)this + 4) = 0;
  }
  if (*(undefined4 **)this != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)this)(1);
    *(undefined4 *)this = 0;
  }
  return iVar2;
}



/* grim_zip_reader_init @ 10016121 */

/* [binja] int32_t* __fastcall sub_10016121(int32_t* arg1) */

int * __fastcall grim_zip_reader_init(int *arg1)

{
  *arg1 = 0;
  arg1[1] = 0;
  arg1[2] = 0;
  arg1[3] = 0;
  return arg1;
}



/* grim_zip_buffer_init @ 1001619a */

/* [binja] int32_t* __fastcall sub_1001619a(int32_t* arg1) */

int * __fastcall grim_zip_buffer_init(int *arg1)

{
  *arg1 = 0;
  return arg1;
}



/* grim_zip_buffer_free @ 100161a0 */

/* [binja] int32_t __fastcall sub_100161a0(int32_t* arg1) */

int __fastcall grim_zip_buffer_free(int *arg1)

{
  int *piVar1;
  
  piVar1 = (int *)*arg1;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x28))(piVar1);
  }
  *arg1 = 0;
  return 0;
}



/* grim_zip_reader_close @ 100161b6 */

/* [binja] int32_t __fastcall j_sub_10016131(char* arg1) */

int __fastcall grim_zip_reader_close(char *arg1)

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



/* grim_zip_read_header @ 100161bb */

/* WARNING: Type propagation algorithm not settling */
/* [binja] int32_t __thiscall sub_100161bb(char* arg1, int32_t* arg2, int32_t* arg3, int32_t arg4,
   int32_t* arg5, int32_t arg6, int32_t arg7) */

int __thiscall
grim_zip_read_header(void *this,char *arg1,int *arg2,int *arg3,int arg4,int *arg5,int arg6,int arg7)

{
  int *piVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int local_64 [2];
  uint local_5c;
  int local_58;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  int *local_1c;
  int *local_18;
  int *local_14;
  int *local_10;
  uint local_c;
  uint local_8;
  
  local_1c = this;
  grim_model_load_from_zip(this);
  (**(code **)(*arg2 + 0x20))(arg2,local_64);
  if (arg4 == 0) {
    local_2c = local_4c;
    local_28 = local_48;
    local_c = ~arg6 & 1;
    local_34 = 0;
    local_30 = 0;
    bVar2 = false;
  }
  else {
    local_34 = *(uint *)arg4;
    local_30 = *(uint *)(arg4 + 4);
    local_2c = *(uint *)(arg4 + 8);
    local_28 = *(uint *)(arg4 + 0xc);
    if (((((int)local_34 < 0) || (local_4c < local_2c)) || ((int)local_2c < (int)local_34)) ||
       ((((int)local_30 < 0 || (local_48 < local_28)) || ((int)local_28 < (int)local_30)))) {
      return -0x7789f794;
    }
    if (((local_34 != 0) || (local_2c != local_4c)) ||
       ((local_30 != 0 || (bVar2 = false, local_28 != local_48)))) {
      bVar2 = true;
    }
    if (((arg6 & 1U) != 0) || (bVar2)) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  local_8 = arg6 & 0x10000;
  if (local_8 == 0) {
    if ((local_58 == 0) && ((local_5c & 0x200) == 0)) {
      grim_d3d_debug_set_mute(1);
      iVar5 = (**(code **)(*arg2 + 0x1c))(arg2,&DAT_1004e544,&local_18);
      if (iVar5 < 0) {
        local_5c = arg2[4];
        local_8 = ~(local_5c >> 0x1a) & 1;
      }
      else {
        local_8 = 1;
        if (local_18 != (int *)0x0) {
          (**(code **)(*local_18 + 8))(local_18);
          local_18 = (int *)0x0;
        }
      }
      grim_d3d_debug_set_mute(0);
      if (local_8 != 0) goto LAB_100162e3;
    }
    local_14 = arg2;
  }
  else {
LAB_100162e3:
    piVar7 = local_1c;
    if ((((local_64[0] == 0x31545844) || (local_64[0] == 0x32545844)) || (local_64[0] == 0x33545844)
        ) || ((local_64[0] == 0x34545844 ||
              (local_14 = (int *)local_48, uVar6 = local_4c, local_64[0] == 0x35545844)))) {
      local_14 = (int *)(local_48 + 3 & 0xfffffffc);
      uVar6 = local_4c + 3 & 0xfffffffc;
    }
    piVar1 = local_1c + 3;
    (**(code **)(*arg2 + 0xc))(arg2,piVar1);
    piVar7 = piVar7 + 2;
    iVar5 = (**(code **)(*(int *)*piVar1 + 0x6c))((int *)*piVar1,uVar6,local_14,local_64[0],piVar7);
    if (iVar5 < 0) {
      return iVar5;
    }
    if ((local_c == 0) &&
       (iVar5 = (**(code **)(*(int *)*piVar1 + 0x70))((int *)*piVar1,arg2,0,0,*piVar7,0), iVar5 < 0)
       ) {
      return iVar5;
    }
    local_14 = (int *)*piVar7;
  }
  uVar6 = (arg6 & 1U | 0x80) << 4;
  if (((local_c == 0) || (local_8 != 0)) || ((local_5c & 0x200) == 0)) {
LAB_10016400:
    uVar3 = local_44;
    uVar4 = local_40;
    if (bVar2) {
      if ((local_64[0] == 0x31545844) || (local_64[0] == 0x32545844)) {
LAB_10016488:
        local_44 = local_34 & 0xfffffffc;
        local_3c = local_2c + 3 & 0xfffffffc;
        local_40 = local_30 & 0xfffffffc;
        local_38 = local_28 + 3 & 0xfffffffc;
        if (local_8 == 0) {
          if (local_4c < local_3c) {
            local_3c = local_4c;
          }
          if (local_48 < local_38) {
            local_38 = local_48;
          }
joined_r0x100164d3:
          if (((local_44 == 0) && (local_3c == local_4c)) && (local_40 == 0)) {
            uVar3 = 0;
            uVar4 = 0;
            if (local_38 == local_48) goto LAB_100165b3;
          }
        }
        else if (((local_44 == 0) && (local_3c == (local_4c + 3 & 0xfffffffc))) && (local_40 == 0))
        {
          uVar3 = 0;
          uVar4 = 0;
          if (local_38 == (local_48 + 3 & 0xfffffffc)) goto LAB_100165b3;
        }
      }
      else {
        if (local_64[0] == 0x32595559) {
LAB_1001644c:
          local_44 = local_34 & 0xfffffffe;
          local_3c = local_2c + 1 & 0xfffffffe;
          local_40 = local_30;
          local_38 = local_28;
          if (local_4c < local_3c) {
            local_3c = local_4c;
          }
          goto joined_r0x100164d3;
        }
        if (((local_64[0] == 0x33545844) || (local_64[0] == 0x34545844)) ||
           (local_64[0] == 0x35545844)) goto LAB_10016488;
        if (local_64[0] == 0x59565955) goto LAB_1001644c;
        local_44 = local_34;
        local_40 = local_30;
        local_3c = local_2c;
        local_38 = local_28;
      }
      iVar5 = (**(code **)(*local_14 + 0x24))(local_14,&local_24,&local_44,uVar6);
      if (iVar5 < 0) {
        return iVar5;
      }
      local_34 = local_34 - local_44;
      local_2c = local_2c - local_44;
      local_30 = local_30 - local_40;
      local_28 = local_28 - local_40;
      goto LAB_10016511;
    }
  }
  else {
    if ((arg6 & 0x20000U) == 0) {
      grim_d3d_debug_set_mute(1);
      iVar5 = (**(code **)(*arg2 + 0x1c))(arg2,&DAT_1004e534,&local_10);
      if (-1 < iVar5) {
        iVar5 = (**(code **)(*local_10 + 0x34))(local_10);
        if (iVar5 == 1) {
          uVar6 = uVar6 | 0x2000;
          bVar2 = false;
        }
        if (local_10 != (int *)0x0) {
          (**(code **)(*local_10 + 8))(local_10);
          local_10 = (int *)0x0;
        }
      }
      grim_d3d_debug_set_mute(0);
      goto LAB_10016400;
    }
    uVar6 = uVar6 | 0x2000;
    uVar3 = local_44;
    uVar4 = local_40;
  }
LAB_100165b3:
  local_40 = uVar4;
  local_44 = uVar3;
  iVar5 = (**(code **)(*local_14 + 0x24))(local_14,&local_24,0,uVar6);
  if (iVar5 < 0) {
    return iVar5;
  }
LAB_10016511:
  arg1[0xc] = '\0';
  arg1[0xd] = '\0';
  arg1[0xe] = '\0';
  arg1[0xf] = '\0';
  arg1[0x10] = '\0';
  arg1[0x11] = '\0';
  arg1[0x12] = '\0';
  arg1[0x13] = '\0';
  arg1[0x14] = '\0';
  arg1[0x15] = '\0';
  arg1[0x16] = '\0';
  arg1[0x17] = '\0';
  arg1[0x20] = '\0';
  arg1[0x21] = '\0';
  arg1[0x22] = '\0';
  arg1[0x23] = '\0';
  arg1[0x38] = '\0';
  arg1[0x39] = '\0';
  arg1[0x3a] = '\0';
  arg1[0x3b] = '\0';
  *(undefined4 *)arg1 = local_20;
  *(int *)(arg1 + 4) = local_64[0];
  *(uint *)(arg1 + 0x28) = local_34;
  arg1[0x3c] = '\x01';
  arg1[0x3d] = '\0';
  arg1[0x3e] = '\0';
  arg1[0x3f] = '\0';
  arg1[0x40] = '\x01';
  arg1[0x41] = '\0';
  arg1[0x42] = '\0';
  arg1[0x43] = '\0';
  *(undefined4 *)(arg1 + 8) = local_24;
  *(uint *)(arg1 + 0x2c) = local_30;
  *(int **)(arg1 + 0x44) = arg5;
  *(uint *)(arg1 + 0x18) = local_4c;
  *(uint *)(arg1 + 0x30) = local_2c;
  *(int **)(arg1 + 0x48) = arg3;
  *(uint *)(arg1 + 0x1c) = local_48;
  arg1[0x24] = '\x01';
  arg1[0x25] = '\0';
  arg1[0x26] = '\0';
  arg1[0x27] = '\0';
  *(uint *)(arg1 + 0x34) = local_28;
  local_1c[1] = (int)arg2;
  *local_1c = arg6;
  return 0;
}



/* grim_zip_read_entry @ 100165d3 */

/* WARNING: Type propagation algorithm not settling */
/* [binja] int32_t __thiscall sub_100165d3(int32_t* arg1, int32_t* arg2, int32_t* arg3, int32_t
   arg4, int32_t arg5, int32_t arg6, int32_t arg7) */

int __thiscall
grim_zip_read_entry(void *this,int *arg1,int *arg2,int *arg3,int arg4,int arg5,int arg6,int arg7)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  uint *puVar8;
  int local_6c [2];
  uint local_64;
  int local_60;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c [4];
  uint local_3c;
  uint local_38;
  uint local_34 [4];
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 *local_10;
  uint local_c;
  int *local_8;
  
  local_10 = this;
  if (*(int *)this != 0) {
    grim_zip_buffer_free(this);
  }
  (**(code **)(*arg2 + 0x20))(arg2,local_6c);
  if (arg4 == 0) {
    bVar1 = false;
    local_34[2] = local_58;
    local_34[3] = local_54;
    uVar4 = ~arg6 & 1;
    local_34[0] = 0;
    local_34[1] = 0;
    local_24 = 0;
    local_20 = local_50;
  }
  else {
    puVar7 = local_34;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *(uint *)arg4;
      arg4 = (int)(arg4 + 4);
      puVar7 = puVar7 + 1;
    }
    if (local_58 < local_34[2]) {
      return -0x7789f794;
    }
    if (local_34[2] < local_34[0]) {
      return -0x7789f794;
    }
    if (local_54 < local_34[3]) {
      return -0x7789f794;
    }
    if (local_34[3] < local_34[1]) {
      return -0x7789f794;
    }
    if (local_50 < local_20) {
      return -0x7789f794;
    }
    if (local_20 < local_24) {
      return -0x7789f794;
    }
    if (((((local_34[0] != 0) || (local_34[2] != local_58)) || (local_34[1] != 0)) ||
        ((local_34[3] != local_54 || (local_24 != 0)))) || (bVar1 = false, local_20 != local_50)) {
      bVar1 = true;
    }
    if (((arg6 & 1U) != 0) || (bVar1)) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  uVar2 = local_20;
  if ((local_60 == 0) && ((local_64 & 0x200) == 0)) {
    return -0x7789f794;
  }
  uVar6 = (arg6 & 1U | 0x80) << 4;
  local_c = uVar6;
  if ((uVar4 == 0) || ((local_64 & 0x200) == 0)) {
LAB_1001673b:
    if (bVar1) {
      if ((local_6c[0] == 0x31545844) || (local_6c[0] == 0x32545844)) {
LAB_10016806:
        uVar4 = local_34[0] & 0xfffffffc;
        local_4c[2] = local_34[2] + 3 & 0xfffffffc;
        local_4c[3] = local_34[3] + 3 & 0xfffffffc;
        if (local_58 < local_4c[2]) {
          local_4c[2] = local_58;
        }
        uVar3 = local_34[1] & 0xfffffffc;
        uVar6 = local_c;
        if (local_54 < local_4c[3]) {
          local_4c[3] = local_54;
        }
joined_r0x10016850:
        local_3c = local_24;
        local_38 = uVar2;
        if (((uVar4 == 0) && (local_4c[2] == local_58)) &&
           ((uVar3 == 0 && ((local_4c[3] == local_54 && (local_24 == 0)))))) {
          local_4c[1] = 0;
          local_4c[0] = 0;
          if (uVar2 == local_50) goto LAB_10016879;
        }
      }
      else {
        if (local_6c[0] == 0x32595559) {
LAB_1001679c:
          uVar4 = local_34[0] & 0xfffffffe;
          local_4c[2] = local_34[2] + 1 & 0xfffffffe;
          uVar3 = local_34[1];
          local_4c[3] = local_34[3];
          if (local_58 < local_4c[2]) {
            local_4c[2] = local_58;
          }
          goto joined_r0x10016850;
        }
        if (((local_6c[0] == 0x33545844) || (local_6c[0] == 0x34545844)) ||
           (local_6c[0] == 0x35545844)) goto LAB_10016806;
        if (local_6c[0] == 0x59565955) goto LAB_1001679c;
        puVar7 = local_34;
        puVar8 = local_4c;
        for (iVar5 = 6; uVar6 = local_c, uVar4 = local_4c[0], uVar3 = local_4c[1], iVar5 != 0;
            iVar5 = iVar5 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
      }
      local_4c[1] = uVar3;
      local_4c[0] = uVar4;
      iVar5 = (**(code **)(*arg2 + 0x24))(arg2,&local_1c,local_4c,uVar6);
      if (iVar5 < 0) {
        return iVar5;
      }
      local_34[0] = local_34[0] - local_4c[0];
      local_34[2] = local_34[2] - local_4c[0];
      local_34[1] = local_34[1] - local_4c[1];
      local_34[3] = local_34[3] - local_4c[1];
      local_24 = local_24 - local_3c;
      local_20 = uVar2 - local_3c;
      goto LAB_100168c8;
    }
  }
  else {
    if ((arg6 & 0x20000U) == 0) {
      grim_d3d_debug_set_mute(1);
      iVar5 = (**(code **)(*arg2 + 0x1c))(arg2,&DAT_1004e524,&local_8);
      if (-1 < iVar5) {
        iVar5 = (**(code **)(*local_8 + 0x34))(local_8);
        if (iVar5 == 1) {
          uVar6 = uVar6 | 0x2000;
          bVar1 = false;
          local_c = uVar6;
        }
        if (local_8 != (int *)0x0) {
          (**(code **)(*local_8 + 8))(local_8);
          local_8 = (int *)0x0;
        }
      }
      grim_d3d_debug_set_mute(0);
      goto LAB_1001673b;
    }
    uVar6 = uVar6 | 0x2000;
  }
LAB_10016879:
  iVar5 = (**(code **)(*arg2 + 0x24))(arg2,&local_1c,0,uVar6);
  if (iVar5 < 0) {
    return iVar5;
  }
LAB_100168c8:
  *arg1 = local_14;
  arg1[1] = local_6c[0];
  arg1[2] = local_1c;
  arg1[3] = local_18;
  arg1[4] = 0;
  arg1[5] = 0;
  arg1[8] = 0;
  arg1[9] = local_50;
  puVar7 = local_34;
  puVar8 = (uint *)(arg1 + 10);
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  arg1[0x11] = arg5;
  arg1[6] = local_58;
  arg1[0x12] = (int)arg3;
  arg1[7] = local_54;
  arg1[0x10] = 1;
  *local_10 = arg2;
  return 0;
}



/* memzero @ 10022c14 */

/* zero-fill helper (memset to 0) */

void __cdecl memzero(void *dst,uint size)

{
  uint uVar1;
  
  for (uVar1 = size >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined4 *)dst = 0;
    dst = (undefined4 *)((int)dst + 4);
  }
  for (uVar1 = size & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)dst = 0;
    dst = (undefined4 *)((int)dst + 1);
  }
  return;
}



/* grim_zlib_stream_init @ 100241e2 */

void __cdecl grim_zlib_stream_init(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x1c);
  *(undefined4 **)(param_1 + 0x17c) = puVar1;
  *(undefined1 *)(puVar1 + 2) = 0;
  *puVar1 = &LAB_10024094;
  puVar1[1] = &LAB_100241c1;
  grim_jpg_mem_manager_init();
  return;
}



/* inflateReset @ 10024212 */

/* zlib: reset inflate state */

int __cdecl inflateReset(z_streamp strm)

{
  internal_state *piVar1;
  
  if ((strm != (z_streamp)0x0) && (piVar1 = strm->state, piVar1 != (internal_state *)0x0)) {
    strm->total_out = 0;
    strm->total_in = 0;
    strm->msg = (char *)0x0;
    piVar1->dummy = -(uint)(piVar1[3].dummy != 0) & 7;
    inflate_blocks_reset((void *)strm->state[5].dummy,strm,(uLongf *)0x0);
    return 0;
  }
  return -2;
}



/* inflateEnd @ 10024251 */

/* zlib: free inflate state */

int __cdecl inflateEnd(z_streamp strm)

{
  void *s;
  
  if (((strm != (z_streamp)0x0) && (strm->state != (internal_state *)0x0)) &&
     (strm->zfree != (free_func)0x0)) {
    s = (void *)strm->state[5].dummy;
    if (s != (void *)0x0) {
      inflate_blocks_free(s,strm);
    }
    (*strm->zfree)(strm->opaque,strm->state);
    strm->state = (internal_state *)0x0;
    return 0;
  }
  return -2;
}



/* inflateInit2_ @ 1002428f */

/* zlib: init inflate with window bits */

int __cdecl inflateInit2_(z_streamp strm,int windowBits,char *version,int stream_size)

{
  internal_state *piVar1;
  void *pvVar2;
  int iVar3;
  
  if (((version == (char *)0x0) || (*version != '1')) || (stream_size != 0x38)) {
    iVar3 = -6;
  }
  else if (strm == (z_streamp)0x0) {
    iVar3 = -2;
  }
  else {
    strm->msg = (char *)0x0;
    if (strm->zalloc == (alloc_func)0x0) {
      strm->zalloc = zcalloc;
      strm->opaque = (voidpf)0x0;
    }
    if (strm->zfree == (free_func)0x0) {
      strm->zfree = zcfree;
    }
    piVar1 = (*strm->zalloc)(strm->opaque,1,0x18);
    strm->state = piVar1;
    if (piVar1 == (internal_state *)0x0) {
      iVar3 = -4;
    }
    else {
      piVar1[5].dummy = 0;
      strm->state[3].dummy = 0;
      if (windowBits < 0) {
        windowBits = -windowBits;
        strm->state[3].dummy = 1;
      }
      if ((windowBits < 8) || (0xf < windowBits)) {
        iVar3 = -2;
      }
      else {
        strm->state[4].dummy = windowBits;
        pvVar2 = inflate_blocks_new(strm,(void *)(~-(uint)(strm->state[3].dummy != 0) & 0x100347d2),
                                    1 << ((byte)windowBits & 0x1f));
        strm->state[5].dummy = (int)pvVar2;
        if (strm->state[5].dummy != 0) {
          inflateReset(strm);
          return 0;
        }
        iVar3 = -4;
      }
      inflateEnd(strm);
    }
  }
  return iVar3;
}



/* inflateInit_ @ 10024374 */

/* zlib: init inflate (wrapper for inflateInit2_) */

int __cdecl inflateInit_(z_streamp strm,char *version,int stream_size)

{
  int iVar1;
  
  iVar1 = inflateInit2_(strm,0xf,version,stream_size);
  return iVar1;
}



/* inflate @ 1002438b */

/* zlib: inflate compressed data */

int __cdecl inflate(z_streamp strm,int flush)

{
  byte bVar1;
  int iVar2;
  internal_state *piVar3;
  int iVar4;
  
  if (((strm == (z_streamp)0x0) || (piVar3 = strm->state, piVar3 == (internal_state *)0x0)) ||
     (strm->next_in == (Bytef *)0x0)) {
LAB_100245c8:
    return -2;
  }
  iVar2 = -5;
  iVar4 = 0;
  if (flush == 4) {
    iVar4 = iVar2;
  }
LAB_100245bb:
  switch(piVar3->dummy) {
  case 0:
    if (strm->avail_in == 0) {
      return iVar2;
    }
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    strm->state[1].dummy = (uint)*strm->next_in;
    piVar3 = strm->state;
    iVar2 = piVar3[1].dummy;
    strm->next_in = strm->next_in + 1;
    if (((byte)iVar2 & 0xf) == 8) {
      if (((uint)piVar3[1].dummy >> 4) + 8 <= (uint)piVar3[4].dummy) {
        piVar3->dummy = 1;
        iVar2 = iVar4;
        goto switchD_100243c8_caseD_1;
      }
      piVar3->dummy = 0xd;
      strm->msg = "invalid window size";
    }
    else {
      piVar3->dummy = 0xd;
      strm->msg = "unknown compression method";
    }
    goto LAB_100245ae;
  case 1:
switchD_100243c8_caseD_1:
    if (strm->avail_in == 0) {
      return iVar2;
    }
    piVar3 = strm->state;
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    bVar1 = *strm->next_in;
    strm->next_in = strm->next_in + 1;
    if ((piVar3[1].dummy * 0x100 + (uint)bVar1) % 0x1f != 0) {
      piVar3->dummy = 0xd;
      strm->msg = "incorrect header check";
      goto LAB_100245ae;
    }
    if ((bVar1 & 0x20) != 0) {
      strm->state->dummy = 2;
      iVar2 = iVar4;
      goto switchD_100243c8_caseD_2;
    }
    piVar3->dummy = 7;
    iVar2 = iVar4;
    break;
  case 2:
switchD_100243c8_caseD_2:
    if (strm->avail_in == 0) {
      return iVar2;
    }
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    strm->state[2].dummy = (uint)*strm->next_in << 0x18;
    strm->next_in = strm->next_in + 1;
    strm->state->dummy = 3;
    iVar2 = iVar4;
  case 3:
    goto switchD_100243c8_caseD_3;
  case 4:
    goto switchD_100243c8_caseD_4;
  case 5:
    goto switchD_100243c8_caseD_5;
  case 6:
    strm->state->dummy = 0xd;
    strm->msg = "need dictionary";
    strm->state[1].dummy = 0;
    return -2;
  case 7:
    iVar2 = inflate_blocks((void *)strm->state[5].dummy,strm,iVar2);
    if (iVar2 == -3) {
      strm->state->dummy = 0xd;
      strm->state[1].dummy = 0;
      iVar2 = -3;
    }
    else {
      if (iVar2 == 0) {
        iVar2 = iVar4;
      }
      if (iVar2 != 1) {
        return iVar2;
      }
      inflate_blocks_reset((void *)strm->state[5].dummy,strm,(uLongf *)(strm->state + 1));
      piVar3 = strm->state;
      if (piVar3[3].dummy == 0) {
        piVar3->dummy = 8;
        iVar2 = iVar4;
        goto switchD_100243c8_caseD_8;
      }
      piVar3->dummy = 0xc;
      iVar2 = iVar4;
    }
    break;
  case 8:
switchD_100243c8_caseD_8:
    if (strm->avail_in == 0) {
      return iVar2;
    }
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    strm->state[2].dummy = (uint)*strm->next_in << 0x18;
    strm->next_in = strm->next_in + 1;
    strm->state->dummy = 9;
    iVar2 = iVar4;
  case 9:
    if (strm->avail_in == 0) {
      return iVar2;
    }
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in * 0x10000;
    strm->next_in = strm->next_in + 1;
    strm->state->dummy = 10;
    iVar2 = iVar4;
  case 10:
    goto switchD_100243c8_caseD_a;
  case 0xb:
    goto switchD_100243c8_caseD_b;
  case 0xc:
    goto LAB_100245c8;
  case 0xd:
    return -3;
  default:
    goto LAB_100245c8;
  }
LAB_100245b8:
  piVar3 = strm->state;
  goto LAB_100245bb;
switchD_100243c8_caseD_a:
  if (strm->avail_in == 0) {
    return iVar2;
  }
  strm->total_in = strm->total_in + 1;
  strm->avail_in = strm->avail_in - 1;
  strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in * 0x100;
  strm->next_in = strm->next_in + 1;
  strm->state->dummy = 0xb;
  iVar2 = iVar4;
switchD_100243c8_caseD_b:
  if (strm->avail_in == 0) {
    return iVar2;
  }
  strm->total_in = strm->total_in + 1;
  strm->avail_in = strm->avail_in - 1;
  strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in;
  piVar3 = strm->state;
  strm->next_in = strm->next_in + 1;
  if (piVar3[1].dummy == piVar3[2].dummy) {
    strm->state->dummy = 0xc;
LAB_100245c8:
    return 1;
  }
  piVar3->dummy = 0xd;
  strm->msg = "incorrect data check";
LAB_100245ae:
  strm->state[1].dummy = 5;
  iVar2 = iVar4;
  goto LAB_100245b8;
switchD_100243c8_caseD_3:
  if (strm->avail_in == 0) {
    return iVar2;
  }
  strm->total_in = strm->total_in + 1;
  strm->avail_in = strm->avail_in - 1;
  strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in * 0x10000;
  strm->next_in = strm->next_in + 1;
  strm->state->dummy = 4;
  iVar2 = iVar4;
switchD_100243c8_caseD_4:
  if (strm->avail_in == 0) {
    return iVar2;
  }
  strm->total_in = strm->total_in + 1;
  strm->avail_in = strm->avail_in - 1;
  strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in * 0x100;
  strm->next_in = strm->next_in + 1;
  strm->state->dummy = 5;
  iVar2 = iVar4;
switchD_100243c8_caseD_5:
  if (strm->avail_in != 0) {
    strm->total_in = strm->total_in + 1;
    strm->avail_in = strm->avail_in - 1;
    strm->state[2].dummy = strm->state[2].dummy + (uint)*strm->next_in;
    strm->next_in = strm->next_in + 1;
    strm->adler = strm->state[2].dummy;
    strm->state->dummy = 6;
    return 2;
  }
  return iVar2;
}



/* zcfree @ 1002e665 */

/* zlib (internal): default free wrapper */

void __cdecl zcfree(voidpf opaque,voidpf ptr)

{
  free(ptr);
  return;
}



/* inflate_blocks_reset @ 10033f0b */

/* zlib (internal): reset inflate blocks state */

void __cdecl inflate_blocks_reset(void *s,z_streamp z,uLongf *c)

{
  uLong uVar1;
  
  if (c != (uLongf *)0x0) {
    *c = *(uLongf *)((int)s + 0x3c);
  }
  if ((*(int *)s == 4) || (*(int *)s == 5)) {
    (*z->zfree)(z->opaque,*(voidpf *)((int)s + 0xc));
  }
  if (*(int *)s == 6) {
    inflate_codes_free(*(void **)((int)s + 4),z);
  }
  *(undefined4 *)((int)s + 0x34) = *(undefined4 *)((int)s + 0x28);
  *(undefined4 *)((int)s + 0x30) = *(undefined4 *)((int)s + 0x28);
  *(undefined4 *)s = 0;
  *(undefined4 *)((int)s + 0x1c) = 0;
  *(undefined4 *)((int)s + 0x20) = 0;
  if (*(code **)((int)s + 0x38) != (code *)0x0) {
    uVar1 = (**(code **)((int)s + 0x38))(0,0,0);
    *(uLong *)((int)s + 0x3c) = uVar1;
    z->adler = uVar1;
  }
  return;
}



/* inflate_blocks_new @ 10033f76 */

/* zlib (internal): allocate inflate blocks state */

void * __cdecl inflate_blocks_new(z_streamp z,void *check_func,uInt w)

{
  undefined4 *s;
  voidpf pvVar1;
  
  s = (*z->zalloc)(z->opaque,1,0x40);
  if (s != (undefined4 *)0x0) {
    pvVar1 = (*z->zalloc)(z->opaque,8,0x5a0);
    s[9] = pvVar1;
    if (pvVar1 != (voidpf)0x0) {
      pvVar1 = (*z->zalloc)(z->opaque,1,w);
      s[10] = pvVar1;
      if (pvVar1 == (voidpf)0x0) {
        (*z->zfree)(z->opaque,(voidpf)s[9]);
        (*z->zfree)(z->opaque,s);
        return (void *)0x0;
      }
      *s = 0;
      s[0xb] = (int)pvVar1 + w;
      s[0xe] = check_func;
      inflate_blocks_reset(s,z,(uLongf *)0x0);
      return s;
    }
    (*z->zfree)(z->opaque,s);
  }
  return (void *)0x0;
}



/* inflate_blocks @ 10034003 */

/* zlib (internal): process inflate blocks */

int __cdecl inflate_blocks(void *s,z_streamp z,int r)

{
  int *piVar1;
  byte bVar2;
  byte *pbVar3;
  Bytef *pBVar4;
  void *s_00;
  int iVar5;
  uint uVar6;
  voidpf pvVar7;
  byte *pbVar8;
  undefined4 uVar9;
  void *pvVar10;
  byte *pbVar11;
  void *pvStack_38;
  void *pvStack_34;
  byte *pbStack_30;
  uInt uStack_2c;
  uInt uStack_28;
  void *pvStack_24;
  void *pvStack_20;
  byte *pbStack_1c;
  byte *local_18;
  byte *local_14;
  byte *local_10;
  byte *local_c;
  uint local_8;
  
  s_00 = s;
  local_c = (byte *)z->avail_in;
  local_8 = *(uint *)((int)s + 0x20);
  local_10 = *(byte **)((int)s + 0x34);
  if (local_10 < *(byte **)((int)s + 0x30)) {
    local_14 = *(byte **)((int)s + 0x30) + (-1 - (int)local_10);
  }
  else {
    local_14 = (byte *)(*(int *)((int)s + 0x2c) - (int)local_10);
  }
  uVar6 = *(uint *)s;
  s = *(void **)((int)s + 0x1c);
  pbVar11 = z->next_in;
  while (local_18 = pbVar11, uVar6 < 10) {
    switch(*(undefined4 *)(&DAT_10034776 + uVar6 * 4)) {
    case 0x100340aa:
      for (; pbVar11 = local_18, s < (void *)0x3; s = (void *)((int)s + 8)) {
        if (local_c == (byte *)0x0) goto code_r0x100346a3;
        r = 0;
        local_c = local_c + -1;
        local_8 = local_8 | (uint)*local_18 << ((byte)s & 0x1f);
        local_18 = local_18 + 1;
      }
      uVar6 = (local_8 & 7) >> 1;
      *(uint *)((int)s_00 + 0x18) = local_8 & 1;
      if (uVar6 == 0) {
        uVar6 = (int)s - 3U & 7;
        local_8 = (local_8 >> 3) >> (sbyte)uVar6;
        s = (void *)(((int)s - 3U) - uVar6);
        *(undefined4 *)s_00 = 1;
      }
      else if (uVar6 == 1) {
        func_0x10036e31(&uStack_2c,&uStack_28,&pvStack_24,&pvStack_20,z);
        pvVar10 = inflate_codes_new(uStack_2c,uStack_28,pvStack_24,pvStack_20,z);
        *(void **)((int)s_00 + 4) = pvVar10;
        if (pvVar10 == (void *)0x0) goto code_r0x10034717;
        local_8 = local_8 >> 3;
        s = (void *)((int)s + -3);
        *(undefined4 *)s_00 = 6;
      }
      else {
        if (uVar6 == 2) {
          local_8 = local_8 >> 3;
          uVar6 = 3;
          s = (void *)((int)s + -3);
          goto code_r0x10034105;
        }
        if (uVar6 == 3) {
          *(undefined4 *)s_00 = 9;
          z->msg = "invalid block type";
          *(uint *)((int)s_00 + 0x20) = local_8 >> 3;
          s = (void *)((int)s + -3);
          r = -3;
          goto code_r0x10034055;
        }
      }
      break;
    case 0x10034174:
      for (; pbVar11 = local_18, s < (void *)0x20; s = (void *)((int)s + 8)) {
        if (local_c == (byte *)0x0) goto code_r0x100346a3;
        r = 0;
        local_c = local_c + -1;
        local_8 = local_8 | (uint)*local_18 << ((byte)s & 0x1f);
        local_18 = local_18 + 1;
      }
      if (~local_8 >> 0x10 != (local_8 & 0xffff)) {
        *(undefined4 *)s_00 = 9;
        z->msg = "invalid stored block lengths";
        goto code_r0x1003465b;
      }
      *(uint *)((int)s_00 + 4) = local_8 & 0xffff;
      s = (void *)0x0;
      local_8 = 0;
      if (*(int *)((int)s_00 + 4) == 0) goto code_r0x100342b6;
      uVar6 = 2;
code_r0x10034105:
      *(uint *)s_00 = uVar6;
      break;
    case 0x100341d5:
      if (local_c == (byte *)0x0) {
code_r0x100346a3:
        *(uint *)((int)s_00 + 0x20) = local_8;
        *(void **)((int)s_00 + 0x1c) = s;
        z->avail_in = 0;
        goto code_r0x1003405e;
      }
      if (local_14 == (byte *)0x0) {
        local_14 = (byte *)0x0;
        if (local_10 == *(byte **)((int)s_00 + 0x2c)) {
          pbVar8 = *(byte **)((int)s_00 + 0x30);
          pbVar3 = *(byte **)((int)s_00 + 0x28);
          if (pbVar3 != pbVar8) {
            if (pbVar3 < pbVar8) {
              local_14 = pbVar8 + (-1 - (int)pbVar3);
            }
            else {
              local_14 = *(byte **)((int)s_00 + 0x2c) + -(int)pbVar3;
            }
            local_10 = pbVar3;
            if (local_14 != (byte *)0x0) goto code_r0x10034276;
          }
        }
        *(byte **)((int)s_00 + 0x34) = local_10;
        r = inflate_flush(s_00,z,r);
        pbStack_1c = *(byte **)((int)s_00 + 0x30);
        local_10 = *(byte **)((int)s_00 + 0x34);
        if (local_10 < pbStack_1c) {
          local_14 = pbStack_1c + (-1 - (int)local_10);
        }
        else {
          local_14 = (byte *)(*(int *)((int)s_00 + 0x2c) - (int)local_10);
        }
        pbStack_30 = *(byte **)((int)s_00 + 0x2c);
        if (local_10 == pbStack_30) {
          pbVar8 = *(byte **)((int)s_00 + 0x28);
          if (pbVar8 != pbStack_1c) {
            local_10 = pbVar8;
            if (pbVar8 < pbStack_1c) {
              local_14 = pbStack_1c + (-1 - (int)pbVar8);
            }
            else {
              local_14 = pbStack_30 + -(int)pbVar8;
            }
          }
        }
        if (local_14 == (byte *)0x0) {
          *(uint *)((int)s_00 + 0x20) = local_8;
          *(void **)((int)s_00 + 0x1c) = s;
          z->avail_in = (uInt)local_c;
          z->total_in = (uLong)(pbVar11 + (z->total_in - (int)z->next_in));
          goto code_r0x10034068;
        }
      }
code_r0x10034276:
      r = 0;
      pbVar11 = *(byte **)((int)s_00 + 4);
      if (local_c < *(byte **)((int)s_00 + 4)) {
        pbVar11 = local_c;
      }
      if (local_14 < pbVar11) {
        pbVar11 = local_14;
      }
      pbVar8 = local_18 + (int)pbVar11;
      local_c = local_c + -(int)pbVar11;
      pbVar3 = local_10 + (int)pbVar11;
      local_14 = local_14 + -(int)pbVar11;
      for (uVar6 = (uint)pbVar11 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)local_10 = *(undefined4 *)local_18;
        local_18 = local_18 + 4;
        local_10 = local_10 + 4;
      }
      for (uVar6 = (uint)pbVar11 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *local_10 = *local_18;
        local_18 = local_18 + 1;
        local_10 = local_10 + 1;
      }
      piVar1 = (int *)((int)s_00 + 4);
      *piVar1 = *piVar1 - (int)pbVar11;
      local_18 = pbVar8;
      local_10 = pbVar3;
      if (*piVar1 == 0) {
code_r0x100342b6:
        uVar6 = -(uint)(*(int *)((int)s_00 + 0x18) != 0) & 7;
        goto code_r0x10034105;
      }
      break;
    case 0x100342c5:
      for (; s < (void *)0xe; s = (void *)((int)s + 8)) {
        if (local_c == (byte *)0x0) goto code_r0x100346a3;
        r = 0;
        local_c = local_c + -1;
        local_8 = local_8 | (uint)*pbVar11 << ((byte)s & 0x1f);
        pbVar11 = pbVar11 + 1;
      }
      *(uint *)((int)s_00 + 4) = local_8 & 0x3fff;
      if ((0x1d < (local_8 & 0x1f)) || (uVar6 = (local_8 & 0x3fff) >> 5 & 0x1f, 0x1d < uVar6)) {
        *(undefined4 *)s_00 = 9;
        z->msg = "too many length or distance symbols";
        goto code_r0x1003465b;
      }
      pvVar7 = (*z->zalloc)(z->opaque,uVar6 + 0x102 + (local_8 & 0x1f),4);
      *(voidpf *)((int)s_00 + 0xc) = pvVar7;
      if (pvVar7 != (voidpf)0x0) {
        local_8 = local_8 >> 0xe;
        s = (void *)((int)s + -0xe);
        *(undefined4 *)((int)s_00 + 8) = 0;
        *(undefined4 *)s_00 = 4;
        goto code_r0x10034394;
      }
code_r0x10034717:
      r = (int)(byte *)0xfffffffc;
      goto code_r0x1003404c;
    case 0x10034394:
code_r0x10034394:
      while (*(uint *)((int)s_00 + 8) < (*(uint *)((int)s_00 + 4) >> 10) + 4) {
        for (; s < (void *)0x3; s = (void *)((int)s + 8)) {
          if (local_c == (byte *)0x0) goto code_r0x100346a3;
          r = 0;
          local_c = local_c + -1;
          local_8 = local_8 | (uint)*pbVar11 << ((byte)s & 0x1f);
          pbVar11 = pbVar11 + 1;
        }
        *(uint *)(*(int *)((int)s_00 + 0xc) +
                 *(int *)(&UNK_1004f6e0 + *(int *)((int)s_00 + 8) * 4) * 4) = local_8 & 7;
        *(int *)((int)s_00 + 8) = *(int *)((int)s_00 + 8) + 1;
        s = (void *)((int)s + -3);
        local_8 = local_8 >> 3;
      }
      while (*(uint *)((int)s_00 + 8) < 0x13) {
        *(undefined4 *)
         (*(int *)((int)s_00 + 0xc) + *(int *)(&UNK_1004f6e0 + *(int *)((int)s_00 + 8) * 4) * 4) = 0
        ;
        *(int *)((int)s_00 + 8) = *(int *)((int)s_00 + 8) + 1;
      }
      *(uInt *)((int)s_00 + 0x10) = 7;
      local_14 = (byte *)inflate_trees_bits(*(uInt **)((int)s_00 + 0xc),(uInt *)((int)s_00 + 0x10),
                                            (void **)((int)s_00 + 0x14),*(void **)((int)s_00 + 0x24)
                                            ,z);
      if (local_14 == (byte *)0x0) {
        *(undefined4 *)((int)s_00 + 8) = 0;
        *(undefined4 *)s_00 = 5;
        goto code_r0x10034512;
      }
      (*z->zfree)(z->opaque,*(voidpf *)((int)s_00 + 0xc));
      goto code_r0x10034707;
    case 0x10034512:
code_r0x10034512:
      while (*(uint *)((int)s_00 + 8) <
             (*(uint *)((int)s_00 + 4) >> 5 & 0x1f) + 0x102 + (*(uint *)((int)s_00 + 4) & 0x1f)) {
        for (; s < *(void **)((int)s_00 + 0x10); s = (void *)((int)s + 8)) {
          if (local_c == (byte *)0x0) goto code_r0x100346a3;
          r = 0;
          local_c = local_c + -1;
          local_8 = local_8 | (uint)*pbVar11 << ((byte)s & 0x1f);
          pbVar11 = pbVar11 + 1;
        }
        iVar5 = *(int *)((int)s_00 + 0x14) +
                (*(uint *)(&grim_zlib_mask_bits + (int)*(void **)((int)s_00 + 0x10) * 4) & local_8) * 8;
        bVar2 = *(byte *)(iVar5 + 1);
        local_14 = (byte *)(uint)bVar2;
        pbStack_30 = *(byte **)(iVar5 + 4);
        if (pbStack_30 < (byte *)0x10) {
          local_8 = local_8 >> (bVar2 & 0x1f);
          s = (void *)((int)s - (int)local_14);
          *(byte **)(*(int *)((int)s_00 + 0xc) + *(int *)((int)s_00 + 8) * 4) = pbStack_30;
          *(int *)((int)s_00 + 8) = *(int *)((int)s_00 + 8) + 1;
        }
        else {
          if (pbStack_30 == (byte *)0x12) {
            pbVar8 = (byte *)0x7;
          }
          else {
            pbVar8 = pbStack_30 + -0xe;
          }
          local_18 = (byte *)((uint)(pbStack_30 == (byte *)0x12) * 8 + 3);
          for (; s < pbVar8 + (int)local_14; s = (void *)((int)s + 8)) {
            if (local_c == (byte *)0x0) goto code_r0x100346a3;
            r = 0;
            local_c = local_c + -1;
            local_8 = local_8 | (uint)*pbVar11 << ((byte)s & 0x1f);
            pbVar11 = pbVar11 + 1;
          }
          local_8 = local_8 >> (bVar2 & 0x1f);
          local_18 = local_18 + (*(uint *)(&grim_zlib_mask_bits + (int)pbVar8 * 4) & local_8);
          local_8 = local_8 >> ((byte)pbVar8 & 0x1f);
          s = (void *)((int)s - (int)(pbVar8 + (int)local_14));
          iVar5 = *(int *)((int)s_00 + 8);
          if ((byte *)((*(uint *)((int)s_00 + 4) >> 5 & 0x1f) + 0x102 +
                      (*(uint *)((int)s_00 + 4) & 0x1f)) < local_18 + iVar5) {
code_r0x100346bb:
            (*z->zfree)(z->opaque,*(voidpf *)((int)s_00 + 0xc));
            *(undefined4 *)s_00 = 9;
            z->msg = "invalid bit length repeat";
            *(uint *)((int)s_00 + 0x20) = local_8;
            *(void **)((int)s_00 + 0x1c) = s;
            z->avail_in = (uInt)local_c;
            z->total_in = (uLong)(pbVar11 + (z->total_in - (int)z->next_in));
            z->next_in = pbVar11;
            *(byte **)((int)s_00 + 0x34) = local_10;
            iVar5 = inflate_flush(s_00,z,-3);
            return iVar5;
          }
          if (pbStack_30 == (byte *)0x10) {
            if (iVar5 == 0) goto code_r0x100346bb;
            uVar9 = *(undefined4 *)(*(int *)((int)s_00 + 0xc) + -4 + iVar5 * 4);
          }
          else {
            uVar9 = 0;
          }
          do {
            *(undefined4 *)(*(int *)((int)s_00 + 0xc) + iVar5 * 4) = uVar9;
            iVar5 = iVar5 + 1;
            local_18 = local_18 + -1;
          } while (local_18 != (byte *)0x0);
          *(int *)((int)s_00 + 8) = iVar5;
          local_18 = (byte *)0x0;
        }
      }
      *(undefined4 *)((int)s_00 + 0x14) = 0;
      pbStack_1c = (byte *)0x9;
      local_18 = (byte *)0x6;
      local_14 = (byte *)inflate_trees_dynamic
                                   ((*(uint *)((int)s_00 + 4) & 0x1f) + 0x101,
                                    (*(uint *)((int)s_00 + 4) >> 5 & 0x1f) + 1,
                                    *(uInt **)((int)s_00 + 0xc),(uInt *)&pbStack_1c,
                                    (uInt *)&local_18,&pvStack_38,&pvStack_34,
                                    *(void **)((int)s_00 + 0x24),z);
      (*z->zfree)(z->opaque,*(voidpf *)((int)s_00 + 0xc));
      if (local_14 == (byte *)0x0) {
        pvVar10 = inflate_codes_new((uInt)pbStack_1c,(uInt)local_18,pvStack_38,pvStack_34,z);
        if (pvVar10 == (void *)0x0) goto code_r0x10034717;
        *(void **)((int)s_00 + 4) = pvVar10;
        *(undefined4 *)s_00 = 6;
        goto code_r0x100345b3;
      }
code_r0x10034707:
      r = (int)local_14;
      if (local_14 == (byte *)0xfffffffd) {
        *(undefined4 *)s_00 = 9;
      }
      goto code_r0x1003404c;
    case 0x100345b3:
code_r0x100345b3:
      *(uint *)((int)s_00 + 0x20) = local_8;
      *(void **)((int)s_00 + 0x1c) = s;
      z->avail_in = (uInt)local_c;
      z->total_in = (uLong)(pbVar11 + (z->total_in - (int)z->next_in));
      z->next_in = pbVar11;
      *(byte **)((int)s_00 + 0x34) = local_10;
      r = inflate_codes(s_00,z,r);
      if ((byte *)r != (byte *)0x1) goto code_r0x1003406d;
      r = 0;
      inflate_codes_free(*(void **)((int)s_00 + 4),z);
      local_c = (byte *)z->avail_in;
      local_18 = z->next_in;
      local_8 = *(uint *)((int)s_00 + 0x20);
      s = *(void **)((int)s_00 + 0x1c);
      local_10 = *(byte **)((int)s_00 + 0x34);
      if (local_10 < *(byte **)((int)s_00 + 0x30)) {
        local_14 = *(byte **)((int)s_00 + 0x30) + (-1 - (int)local_10);
      }
      else {
        local_14 = (byte *)(*(int *)((int)s_00 + 0x2c) - (int)local_10);
      }
      if (*(int *)((int)s_00 + 0x18) != 0) {
        *(undefined4 *)s_00 = 7;
        goto code_r0x10034724;
      }
      *(undefined4 *)s_00 = 0;
      break;
    case 0x1003465b:
code_r0x1003465b:
      r = (int)(byte *)0xfffffffd;
      goto code_r0x1003404c;
    case 0x10034724:
code_r0x10034724:
      pbVar11 = local_18;
      *(byte **)((int)s_00 + 0x34) = local_10;
      r = inflate_flush(s_00,z,r);
      local_10 = *(byte **)((int)s_00 + 0x34);
      if (*(byte **)((int)s_00 + 0x30) == local_10) {
        *(undefined4 *)s_00 = 8;
        goto code_r0x1003476f;
      }
      *(uint *)((int)s_00 + 0x20) = local_8;
      *(void **)((int)s_00 + 0x1c) = s;
      z->avail_in = (uInt)local_c;
      pBVar4 = z->next_in;
      z->next_in = pbVar11;
      z->total_in = (uLong)(pbVar11 + (z->total_in - (int)pBVar4));
      *(byte **)((int)s_00 + 0x34) = local_10;
      goto code_r0x1003406d;
    case 0x1003476f:
code_r0x1003476f:
      r = (int)(byte *)0x1;
      goto code_r0x1003404c;
    }
    pbVar11 = local_18;
    uVar6 = *(uint *)s_00;
  }
  r = (int)(byte *)0xfffffffe;
code_r0x1003404c:
  *(uint *)((int)s_00 + 0x20) = local_8;
code_r0x10034055:
  *(void **)((int)s_00 + 0x1c) = s;
  z->avail_in = (uInt)local_c;
code_r0x1003405e:
  z->total_in = (uLong)(pbVar11 + (z->total_in - (int)z->next_in));
code_r0x10034068:
  z->next_in = pbVar11;
  *(byte **)((int)s_00 + 0x34) = local_10;
code_r0x1003406d:
  iVar5 = inflate_flush(s_00,z,r);
  return iVar5;
}



/* inflate_blocks_free @ 1003479e */

/* zlib (internal): free inflate blocks state */

void __cdecl inflate_blocks_free(void *s,z_streamp z)

{
  inflate_blocks_reset(s,z,(uLongf *)0x0);
  (*z->zfree)(z->opaque,*(voidpf *)((int)s + 0x28));
  (*z->zfree)(z->opaque,*(voidpf *)((int)s + 0x24));
  (*z->zfree)(z->opaque,s);
  return;
}



/* adler32 @ 100347d2 */

/* zlib: adler32 checksum */

uLong __cdecl adler32(uLong adler,Bytef *buf,uInt len)

{
  uLong uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
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
  int iVar18;
  int iVar19;
  uint uVar20;
  
  uVar4 = adler & 0xffff;
  uVar20 = adler >> 0x10;
  if (buf == (Bytef *)0x0) {
    uVar1 = 1;
  }
  else {
    while (len != 0) {
      uVar3 = 0x15b0;
      if (len < 0x15b0) {
        uVar3 = len;
      }
      len = len - uVar3;
      if (0xf < (int)uVar3) {
        uVar2 = uVar3 >> 4;
        uVar3 = uVar3 + uVar2 * -0x10;
        do {
          iVar5 = uVar4 + *buf;
          iVar6 = iVar5 + (uint)buf[1];
          iVar7 = iVar6 + (uint)buf[2];
          iVar8 = iVar7 + (uint)buf[3];
          iVar9 = iVar8 + (uint)buf[4];
          iVar10 = iVar9 + (uint)buf[5];
          iVar11 = iVar10 + (uint)buf[6];
          iVar12 = iVar11 + (uint)buf[7];
          iVar13 = iVar12 + (uint)buf[8];
          iVar14 = iVar13 + (uint)buf[9];
          iVar15 = iVar14 + (uint)buf[10];
          iVar16 = iVar15 + (uint)buf[0xb];
          iVar17 = iVar16 + (uint)buf[0xc];
          iVar18 = iVar17 + (uint)buf[0xd];
          iVar19 = iVar18 + (uint)buf[0xe];
          uVar4 = iVar19 + (uint)buf[0xf];
          uVar20 = uVar20 + iVar5 + iVar6 + iVar7 + iVar8 + iVar9 + iVar10 + iVar11 + iVar12 +
                   iVar13 + iVar14 + iVar15 + iVar16 + iVar17 + iVar18 + iVar19 + uVar4;
          buf = buf + 0x10;
          uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
      }
      for (; uVar3 != 0; uVar3 = uVar3 - 1) {
        uVar4 = uVar4 + *buf;
        buf = buf + 1;
        uVar20 = uVar20 + uVar4;
      }
      uVar4 = uVar4 % 0xfff1;
      uVar20 = uVar20 % 0xfff1;
    }
    uVar1 = uVar20 << 0x10 | uVar4;
  }
  return uVar1;
}



/* zcalloc @ 100348eb */

/* zlib (internal): default alloc wrapper (calloc) */

voidpf __cdecl zcalloc(voidpf opaque,uInt items,uInt size)

{
  void *pvVar1;
  
  pvVar1 = calloc(items,size);
  return pvVar1;
}



/* grim_zlib_inflate_blocks_process @ 10035fa0 */

void __cdecl grim_zlib_inflate_blocks_process(int param_1,int param_2,short *param_3,int param_4,int param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  undefined1 *puVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 fVar16;
  float10 fVar17;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float local_11c [16];
  float local_dc [8];
  float local_bc [8];
  float local_9c [8];
  float local_7c [8];
  float local_5c [8];
  float local_3c [8];
  float local_1c;
  float local_18;
  int local_14;
  int local_10;
  float local_c;
  float local_8;
  
  fVar11 = (float10)1.4142135;
  fVar12 = (float10)1.847759;
  local_14 = *(int *)(param_1 + 0x11c) + 0x80;
  pfVar9 = *(float **)(param_2 + 0x50);
  pfVar7 = local_11c;
  local_1c = 1.12104e-44;
  do {
    if ((((((param_3[8] == 0 && param_3[0x10] == 0) && param_3[0x18] == 0) && param_3[0x20] == 0) &&
         param_3[0x28] == 0) && param_3[0x30] == 0) && param_3[0x38] == 0) {
      fVar1 = (float)(int)*param_3 * *pfVar9;
      *pfVar7 = fVar1;
      pfVar7[8] = fVar1;
      pfVar7[0x10] = fVar1;
      pfVar7[0x18] = fVar1;
      pfVar7[0x20] = fVar1;
      pfVar7[0x28] = fVar1;
      pfVar7[0x30] = fVar1;
      pfVar7[0x38] = fVar1;
    }
    else {
      fVar2 = (float)(int)param_3[0x30] * pfVar9[0x30];
      fVar1 = (float)((float10)(int)param_3[0x20] * (float10)pfVar9[0x20] +
                     (float10)(int)*param_3 * (float10)*pfVar9);
      fVar13 = (float10)(int)*param_3 * (float10)*pfVar9 -
               (float10)(int)param_3[0x20] * (float10)pfVar9[0x20];
      fVar14 = (float10)fVar2 + (float10)((float)(int)param_3[0x10] * pfVar9[0x10]);
      fVar15 = ((float10)((float)(int)param_3[0x10] * pfVar9[0x10]) - (float10)fVar2) * fVar11 -
               fVar14;
      local_18 = (float)(fVar14 + (float10)fVar1);
      fVar1 = (float)((float10)fVar1 - fVar14);
      fVar2 = (float)(fVar15 + fVar13);
      fVar13 = fVar13 - fVar15;
      fVar14 = (float10)(int)param_3[0x38] * (float10)pfVar9[0x38];
      fVar5 = (float)(int)param_3[0x28] * pfVar9[0x28] + (float)(int)param_3[0x18] * pfVar9[0x18];
      fVar6 = (float)(int)param_3[0x28] * pfVar9[0x28] - (float)(int)param_3[0x18] * pfVar9[0x18];
      fVar3 = (float)(fVar14 + (float10)(int)param_3[8] * (float10)pfVar9[8]);
      fVar14 = (float10)(int)param_3[8] * (float10)pfVar9[8] - fVar14;
      fVar15 = (float10)fVar3 + (float10)fVar5;
      fVar4 = (float)((fVar14 + (float10)fVar6) * fVar12);
      fVar16 = ((float10)fVar4 - (float10)fVar6 * (float10)2.613126) - fVar15;
      fVar17 = ((float10)fVar3 - (float10)fVar5) * fVar11 - fVar16;
      local_8 = (float)fVar17;
      local_c = (float)((fVar14 * (float10)1.0823922 - (float10)fVar4) + fVar17);
      *pfVar7 = (float)(fVar15 + (float10)local_18);
      pfVar7[0x38] = (float)((float10)local_18 - fVar15);
      pfVar7[8] = (float)((float10)fVar2 + fVar16);
      pfVar7[0x30] = (float)((float10)fVar2 - fVar16);
      pfVar7[0x10] = (float)((float10)local_8 + fVar13);
      pfVar7[0x28] = (float)(fVar13 - (float10)local_8);
      pfVar7[0x20] = local_c + fVar1;
      pfVar7[0x18] = fVar1 - local_c;
    }
    pfVar9 = pfVar9 + 1;
    param_3 = param_3 + 1;
    pfVar7 = pfVar7 + 1;
    local_1c = (float)((int)local_1c + -1);
  } while (local_1c != 0.0);
  local_10 = 0;
  pfVar7 = local_11c + 2;
  do {
    puVar10 = (undefined1 *)(*(int *)(param_4 + local_10 * 4) + param_5);
    local_18 = *pfVar7 + pfVar7[4] + pfVar7[2] + pfVar7[-2];
    local_c = (float)((float10)pfVar7[3] + (float10)pfVar7[1]);
    local_8 = pfVar7[5] + pfVar7[-1];
    local_1c = pfVar7[-1] - pfVar7[5];
    fVar12 = ((float10)local_1c + (float10)(pfVar7[3] - pfVar7[1])) * fVar12;
    fVar11 = ((float10)local_8 - (float10)local_c) * fVar11 -
             ((fVar12 - (float10)(pfVar7[3] - pfVar7[1]) * (float10)2.613126) -
             ((float10)pfVar7[3] + (float10)pfVar7[1] + (float10)local_8));
    local_8 = (float)fVar11;
    local_c = (float)(((float10)local_1c * (float10)1.0823922 - fVar12) + fVar11);
    iVar8 = ftol();
    *puVar10 = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[7] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[1] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[6] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[2] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[5] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    puVar10[4] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    iVar8 = ftol();
    pfVar7 = pfVar7 + 8;
    local_10 = local_10 + 1;
    puVar10[3] = *(undefined1 *)((iVar8 + 4 >> 3 & 0x3ffU) + local_14);
    fVar12 = extraout_ST0;
    fVar11 = extraout_ST1;
  } while (local_10 < 8);
  return;
}



/* inflate_codes_new @ 10036381 */

/* zlib (internal): allocate codes state */

void * __cdecl inflate_codes_new(uInt bl,uInt bd,void *tl,void *td,z_streamp z)

{
  undefined4 *puVar1;
  
  puVar1 = (*z->zalloc)(z->opaque,1,0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    *(undefined1 *)(puVar1 + 4) = (undefined1)bl;
    *(undefined1 *)((int)puVar1 + 0x11) = (undefined1)bd;
    puVar1[5] = tl;
    puVar1[6] = td;
  }
  return puVar1;
}



/* inflate_codes @ 100363b5 */

/* zlib (internal): decode codes */

int __cdecl inflate_codes(void *s,z_streamp z,int r)

{
  byte bVar1;
  int *piVar2;
  undefined1 *puVar3;
  Bytef *pBVar4;
  void *s_00;
  z_streamp z_00;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined1 *puStack_18;
  undefined1 *local_10;
  uInt local_c;
  byte *local_8;
  
  z_00 = z;
  s_00 = s;
  local_8 = z->next_in;
  local_c = z->avail_in;
  puVar9 = *(undefined1 **)((int)s + 0x34);
  piVar2 = *(int **)((int)s + 4);
  z = *(z_streamp *)((int)s + 0x20);
  if (puVar9 < *(undefined1 **)((int)s + 0x30)) {
    local_10 = *(undefined1 **)((int)s + 0x30) + (-1 - (int)puVar9);
    s = *(void **)((int)s + 0x1c);
  }
  else {
    local_10 = (undefined1 *)(*(int *)((int)s + 0x2c) - (int)puVar9);
    s = *(void **)((int)s + 0x1c);
  }
  do {
    puVar8 = puVar9;
    switch(*piVar2) {
    case 0:
      if (((undefined1 *)0x101 < local_10) && (9 < local_c)) {
        *(z_streamp *)((int)s_00 + 0x20) = z;
        *(void **)((int)s_00 + 0x1c) = s;
        z_00->avail_in = local_c;
        z_00->total_in = (uLong)(local_8 + (z_00->total_in - (int)z_00->next_in));
        z_00->next_in = local_8;
        *(undefined1 **)((int)s_00 + 0x34) = puVar9;
        r = grim_zlib_inflate_codes_process((uint)*(byte *)(piVar2 + 4),(uint)*(byte *)((int)piVar2 + 0x11),piVar2[5],
                         piVar2[6],(int)s_00,(byte *)z_00);
        puVar9 = *(undefined1 **)((int)s_00 + 0x34);
        local_8 = z_00->next_in;
        local_c = z_00->avail_in;
        z = *(z_streamp *)((int)s_00 + 0x20);
        s = *(void **)((int)s_00 + 0x1c);
        if (puVar9 < *(undefined1 **)((int)s_00 + 0x30)) {
          local_10 = *(undefined1 **)((int)s_00 + 0x30) + (-1 - (int)puVar9);
        }
        else {
          local_10 = (undefined1 *)(*(int *)((int)s_00 + 0x2c) - (int)puVar9);
        }
        if (r != 0) {
          *piVar2 = (uint)(r != 1) * 2 + 7;
          break;
        }
      }
      piVar2[3] = (uint)*(byte *)(piVar2 + 4);
      piVar2[2] = piVar2[5];
      *piVar2 = 1;
    case 1:
      for (; s < (void *)piVar2[3]; s = (void *)((int)s + 8)) {
        if (local_c == 0) goto code_r0x1003687e;
        r = 0;
        local_c = local_c - 1;
        z = (z_streamp)((uint)z | (uint)*local_8 << ((byte)s & 0x1f));
        local_8 = local_8 + 1;
      }
      pbVar5 = (byte *)(piVar2[2] + (*(uint *)(&grim_zlib_mask_bits + piVar2[3] * 4) & (uint)z) * 8);
      z = (z_streamp)((uint)z >> (pbVar5[1] & 0x1f));
      s = (void *)((int)s - (uint)pbVar5[1]);
      bVar1 = *pbVar5;
      uVar7 = (uint)bVar1;
      if (uVar7 == 0) {
        pbVar5 = *(byte **)(pbVar5 + 4);
        *piVar2 = 6;
      }
      else {
        if ((bVar1 & 0x10) != 0) {
          piVar2[2] = uVar7 & 0xf;
          piVar2[1] = *(int *)(pbVar5 + 4);
          *piVar2 = 2;
          break;
        }
        if ((bVar1 & 0x40) != 0) {
          if ((bVar1 & 0x20) == 0) {
            *piVar2 = 9;
            z_00->msg = "invalid literal/length code";
code_r0x1003686b:
            r = -3;
            puVar8 = puVar9;
            goto code_r0x1003682e;
          }
          *piVar2 = 7;
          break;
        }
        piVar2[3] = uVar7;
        pbVar5 = pbVar5 + *(int *)(pbVar5 + 4) * 8;
      }
code_r0x1003663a:
      piVar2[2] = (int)pbVar5;
      break;
    case 2:
      for (; s < (void *)piVar2[2]; s = (void *)((int)s + 8)) {
        if (local_c == 0) goto code_r0x1003687e;
        r = 0;
        local_c = local_c - 1;
        z = (z_streamp)((uint)z | (uint)*local_8 << ((byte)s & 0x1f));
        local_8 = local_8 + 1;
      }
      piVar2[1] = piVar2[1] + (*(uint *)(&grim_zlib_mask_bits + piVar2[2] * 4) & (uint)z);
      z = (z_streamp)((uint)z >> ((byte)piVar2[2] & 0x1f));
      s = (void *)((int)s - piVar2[2]);
      piVar2[3] = (uint)*(byte *)((int)piVar2 + 0x11);
      piVar2[2] = piVar2[6];
      *piVar2 = 3;
    case 3:
      for (; s < (void *)piVar2[3]; s = (void *)((int)s + 8)) {
        if (local_c == 0) goto code_r0x1003687e;
        r = 0;
        local_c = local_c - 1;
        z = (z_streamp)((uint)z | (uint)*local_8 << ((byte)s & 0x1f));
        local_8 = local_8 + 1;
      }
      pbVar5 = (byte *)(piVar2[2] + (*(uint *)(&grim_zlib_mask_bits + piVar2[3] * 4) & (uint)z) * 8);
      z = (z_streamp)((uint)z >> (pbVar5[1] & 0x1f));
      s = (void *)((int)s - (uint)pbVar5[1]);
      bVar1 = *pbVar5;
      if ((bVar1 & 0x10) == 0) {
        if ((bVar1 & 0x40) != 0) {
          *piVar2 = 9;
          z_00->msg = "invalid distance code";
          goto code_r0x1003686b;
        }
        piVar2[3] = (uint)bVar1;
        pbVar5 = pbVar5 + *(int *)(pbVar5 + 4) * 8;
        goto code_r0x1003663a;
      }
      piVar2[2] = bVar1 & 0xf;
      piVar2[3] = *(int *)(pbVar5 + 4);
      *piVar2 = 4;
      break;
    case 4:
      for (; s < (void *)piVar2[2]; s = (void *)((int)s + 8)) {
        if (local_c == 0) goto code_r0x1003687e;
        r = 0;
        local_c = local_c - 1;
        z = (z_streamp)((uint)z | (uint)*local_8 << ((byte)s & 0x1f));
        local_8 = local_8 + 1;
      }
      piVar2[3] = piVar2[3] + (*(uint *)(&grim_zlib_mask_bits + piVar2[2] * 4) & (uint)z);
      z = (z_streamp)((uint)z >> ((byte)piVar2[2] & 0x1f));
      s = (void *)((int)s - piVar2[2]);
      *piVar2 = 5;
    case 5:
      if ((uint)((int)puVar9 - *(int *)((int)s_00 + 0x28)) < (uint)piVar2[3]) {
        iVar6 = (*(int *)((int)s_00 + 0x2c) - *(int *)((int)s_00 + 0x28)) - piVar2[3];
      }
      else {
        iVar6 = -piVar2[3];
      }
      puStack_18 = puVar9 + iVar6;
      while (piVar2[1] != 0) {
        puVar8 = puVar9;
        if (local_10 == (undefined1 *)0x0) {
          if (puVar9 == *(undefined1 **)((int)s_00 + 0x2c)) {
            local_10 = *(undefined1 **)((int)s_00 + 0x30);
            puVar8 = *(undefined1 **)((int)s_00 + 0x28);
            if (local_10 != puVar8) {
              if (puVar8 < local_10) {
                local_10 = local_10 + (-1 - (int)puVar8);
              }
              else {
                local_10 = *(undefined1 **)((int)s_00 + 0x2c) + -(int)puVar8;
              }
              puVar9 = puVar8;
              if (local_10 != (undefined1 *)0x0) goto code_r0x10036751;
            }
          }
          *(undefined1 **)((int)s_00 + 0x34) = puVar9;
          r = inflate_flush(s_00,z_00,r);
          puVar8 = *(undefined1 **)((int)s_00 + 0x34);
          puVar9 = *(undefined1 **)((int)s_00 + 0x30);
          if (puVar8 < puVar9) {
            local_10 = puVar9 + (-1 - (int)puVar8);
          }
          else {
            local_10 = (undefined1 *)(*(int *)((int)s_00 + 0x2c) - (int)puVar8);
          }
          if ((puVar8 == *(undefined1 **)((int)s_00 + 0x2c)) &&
             (puVar3 = *(undefined1 **)((int)s_00 + 0x28), puVar9 != puVar3)) {
            puVar8 = puVar3;
            if (puVar3 < puVar9) {
              local_10 = puVar9 + (-1 - (int)puVar3);
            }
            else {
              local_10 = *(undefined1 **)((int)s_00 + 0x2c) + -(int)puVar3;
            }
          }
          if (local_10 == (undefined1 *)0x0) goto code_r0x1003682e;
        }
code_r0x10036751:
        r = 0;
        *puVar8 = *puStack_18;
        puVar9 = puVar8 + 1;
        puStack_18 = puStack_18 + 1;
        local_10 = local_10 + -1;
        if (puStack_18 == *(undefined1 **)((int)s_00 + 0x2c)) {
          puStack_18 = *(undefined1 **)((int)s_00 + 0x28);
        }
        piVar2[1] = piVar2[1] + -1;
      }
      *piVar2 = 0;
      break;
    case 6:
      if (local_10 != (undefined1 *)0x0) goto code_r0x10036810;
      if (puVar9 == *(undefined1 **)((int)s_00 + 0x2c)) {
        local_10 = *(undefined1 **)((int)s_00 + 0x30);
        puVar8 = *(undefined1 **)((int)s_00 + 0x28);
        if (local_10 != puVar8) {
          if (puVar8 < local_10) {
            local_10 = local_10 + (-1 - (int)puVar8);
          }
          else {
            local_10 = *(undefined1 **)((int)s_00 + 0x2c) + -(int)puVar8;
          }
          puVar9 = puVar8;
          if (local_10 != (undefined1 *)0x0) goto code_r0x10036810;
        }
      }
      *(undefined1 **)((int)s_00 + 0x34) = puVar9;
      r = inflate_flush(s_00,z_00,r);
      puVar8 = *(undefined1 **)((int)s_00 + 0x34);
      puVar9 = *(undefined1 **)((int)s_00 + 0x30);
      if (puVar8 < puVar9) {
        local_10 = puVar9 + (-1 - (int)puVar8);
      }
      else {
        local_10 = (undefined1 *)(*(int *)((int)s_00 + 0x2c) - (int)puVar8);
      }
      if ((puVar8 == *(undefined1 **)((int)s_00 + 0x2c)) &&
         (puVar3 = *(undefined1 **)((int)s_00 + 0x28), puVar9 != puVar3)) {
        puVar8 = puVar3;
        if (puVar3 < puVar9) {
          local_10 = puVar9 + (-1 - (int)puVar3);
        }
        else {
          local_10 = *(undefined1 **)((int)s_00 + 0x2c) + -(int)puVar3;
        }
      }
      if (local_10 == (undefined1 *)0x0) goto code_r0x1003682e;
code_r0x10036810:
      r = 0;
      *puVar8 = (char)piVar2[2];
      puVar9 = puVar8 + 1;
      local_10 = local_10 + -1;
      *piVar2 = 0;
      break;
    case 7:
      if ((void *)0x7 < s) {
        s = (void *)((int)s + -8);
        local_c = local_c + 1;
        local_8 = local_8 + -1;
      }
      *(undefined1 **)((int)s_00 + 0x34) = puVar9;
      r = inflate_flush(s_00,z_00,r);
      puVar9 = *(undefined1 **)((int)s_00 + 0x34);
      if (*(undefined1 **)((int)s_00 + 0x30) == puVar9) {
        *piVar2 = 8;
code_r0x100368ea:
        r = 1;
        puVar8 = puVar9;
code_r0x1003682e:
        *(z_streamp *)((int)s_00 + 0x20) = z;
        *(void **)((int)s_00 + 0x1c) = s;
        z_00->avail_in = local_c;
        puVar9 = puVar8;
code_r0x10036840:
        pBVar4 = z_00->next_in;
        z_00->next_in = local_8;
        z_00->total_in = (uLong)(local_8 + (z_00->total_in - (int)pBVar4));
      }
      else {
        *(z_streamp *)((int)s_00 + 0x20) = z;
        *(void **)((int)s_00 + 0x1c) = s;
        z_00->avail_in = local_c;
        pBVar4 = z_00->next_in;
        z_00->next_in = local_8;
        z_00->total_in = (uLong)(local_8 + (z_00->total_in - (int)pBVar4));
      }
      *(undefined1 **)((int)s_00 + 0x34) = puVar9;
      iVar6 = inflate_flush(s_00,z_00,r);
      return iVar6;
    case 8:
      goto code_r0x100368ea;
    case 9:
      goto code_r0x1003686b;
    default:
      r = -2;
      goto code_r0x1003682e;
    }
  } while( true );
code_r0x1003687e:
  *(z_streamp *)((int)s_00 + 0x20) = z;
  *(void **)((int)s_00 + 0x1c) = s;
  z_00->avail_in = 0;
  goto code_r0x10036840;
}



/* inflate_codes_free @ 10036919 */

/* zlib (internal): free codes state */

void __cdecl inflate_codes_free(void *c,z_streamp z)

{
  (*z->zfree)(z->opaque,c);
  return;
}



/* huft_build @ 1003692a */

/* zlib (internal): build Huffman decoding tables */

int __cdecl huft_build(uInt *b,uInt n,uInt s,uInt *d,uInt *e,void **t,uInt *m,void *hp,uInt *hn)

{
  uint *puVar1;
  uint *in_EAX;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uInt *puVar8;
  uInt uVar9;
  uint uVar10;
  int iVar11;
  byte bVar12;
  int iVar13;
  int local_fc [15];
  uint local_c0 [16];
  uint local_80 [17];
  int local_3c;
  int local_38;
  int local_34;
  uint local_30;
  uInt *local_2c;
  uint *local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_80[0] = 0;
  local_80[1] = 0;
  local_80[2] = 0;
  local_80[3] = 0;
  local_80[4] = 0;
  local_80[5] = 0;
  local_80[6] = 0;
  local_80[7] = 0;
  local_80[8] = 0;
  local_80[9] = 0;
  local_80[10] = 0;
  local_80[0xb] = 0;
  local_80[0xc] = 0;
  local_80[0xd] = 0;
  local_80[0xe] = 0;
  local_80[0xf] = 0;
  puVar8 = b;
  uVar9 = n;
  do {
    local_80[*puVar8] = local_80[*puVar8] + 1;
    puVar8 = puVar8 + 1;
    uVar9 = uVar9 - 1;
  } while (uVar9 != 0);
  if (local_80[0] == n) {
    *t = (void *)0x0;
    *in_EAX = 0;
  }
  else {
    uVar10 = 1;
    local_8 = *in_EAX;
    uVar2 = 0xf;
    do {
      if (local_80[uVar10] != 0) break;
      uVar10 = uVar10 + 1;
    } while (uVar10 < 0x10);
    local_c = uVar10;
    if (*in_EAX < uVar10) {
      local_8 = uVar10;
    }
    do {
      if (local_80[uVar2] != 0) break;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
    local_30 = uVar2;
    if (uVar2 < local_8) {
      local_8 = uVar2;
    }
    *in_EAX = local_8;
    iVar11 = 1 << ((byte)uVar10 & 0x1f);
    for (; uVar10 < uVar2; uVar10 = uVar10 + 1) {
      if ((int)(iVar11 - local_80[uVar10]) < 0) {
        return -3;
      }
      iVar11 = (iVar11 - local_80[uVar10]) * 2;
    }
    uVar10 = local_80[uVar2];
    iVar11 = iVar11 - uVar10;
    local_38 = iVar11;
    if (iVar11 < 0) {
      return -3;
    }
    local_80[uVar2] = uVar10 + iVar11;
    iVar6 = 0;
    iVar3 = uVar2 - 1;
    local_c0[1] = 0;
    if (iVar3 != 0) {
      iVar13 = 0;
      do {
        iVar6 = iVar6 + *(int *)((int)local_80 + iVar13 + 4);
        iVar3 = iVar3 + -1;
        *(int *)((int)local_c0 + iVar13 + 8) = iVar6;
        iVar13 = iVar13 + 4;
      } while (iVar3 != 0);
    }
    uVar10 = 0;
    do {
      iVar3 = local_38;
      uVar9 = *b;
      b = b + 1;
      if (uVar9 != 0) {
        uVar7 = local_c0[uVar9];
        hn[uVar7] = uVar10;
        local_c0[uVar9] = uVar7 + 1;
        iVar11 = iVar3;
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < n);
    uVar2 = local_c0[uVar2];
    local_10 = -1;
    b = hn;
    iVar3 = -local_8;
    local_24 = 0;
    local_c0[0] = 0;
    local_fc[0] = 0;
    local_2c = (uInt *)0x0;
    local_14 = 0;
    if ((int)local_c <= (int)local_30) {
      local_34 = local_c - 1;
      local_28 = local_80 + local_c;
      do {
        local_20 = *local_28;
        uVar9 = local_1c;
        while (local_1c = uVar9, local_20 != 0) {
          local_1c._2_2_ = (undefined2)(uVar9 >> 0x10);
          local_20 = local_20 - 1;
          local_3c = local_8 + iVar3;
          if (local_3c < (int)local_c) {
            local_80[0x10] = iVar3 - local_8;
            do {
              iVar11 = local_10;
              local_10 = local_10 + 1;
              iVar3 = iVar3 + local_8;
              local_80[0x10] = local_80[0x10] + local_8;
              local_3c = local_3c + local_8;
              uVar10 = local_30 - iVar3;
              if (local_8 < local_30 - iVar3) {
                uVar10 = local_8;
              }
              uVar7 = local_c - iVar3;
              uVar4 = 1 << ((byte)uVar7 & 0x1f);
              if ((local_20 + 1 < uVar4) &&
                 (iVar6 = uVar4 + (-1 - local_20), puVar1 = local_28, uVar7 < uVar10)) {
                while (uVar7 = uVar7 + 1, uVar7 < uVar10) {
                  uVar4 = puVar1[1];
                  uVar5 = iVar6 * 2;
                  if (uVar5 < uVar4 || uVar5 - uVar4 == 0) break;
                  iVar6 = uVar5 - uVar4;
                  puVar1 = puVar1 + 1;
                }
              }
              local_14 = 1 << ((byte)uVar7 & 0x1f);
              uVar10 = *(int *)hp + local_14;
              if (0x5a0 < uVar10) {
                return -4;
              }
              local_2c = m + *(int *)hp * 2;
              local_fc[local_10] = (int)(m + *(int *)hp * 2);
              uVar4 = local_24;
              *(uint *)hp = uVar10;
              if (local_10 == 0) {
                *t = local_2c;
              }
              else {
                local_c0[local_10] = local_24;
                local_1c = CONCAT31(CONCAT21(local_1c._2_2_,(undefined1)local_8),(byte)uVar7);
                uVar4 = uVar4 >> ((byte)local_80[0x10] & 0x1f);
                iVar11 = local_fc[iVar11];
                local_18 = ((int)local_2c - iVar11 >> 3) - uVar4;
                *(uInt *)(iVar11 + uVar4 * 8) = local_1c;
                *(uint *)(iVar11 + 4 + uVar4 * 8) = local_18;
              }
              iVar11 = local_38;
            } while (local_3c < (int)local_c);
          }
          bVar12 = (byte)iVar3;
          if (b < hn + uVar2) {
            local_18 = *b;
            if (local_18 < s) {
              local_1c._0_1_ = (local_18 < 0x100) - 1U & 0x60;
            }
            else {
              local_1c._0_1_ = (char)e[local_18 - s] + 0x50;
              local_18 = d[local_18 - s];
            }
            b = b + 1;
          }
          else {
            local_1c._0_1_ = 0xc0;
          }
          local_1c = CONCAT31(CONCAT21(local_1c._2_2_,(char)local_c - bVar12),(byte)local_1c);
          iVar6 = 1 << ((char)local_c - bVar12 & 0x1f);
          uVar10 = local_24 >> (bVar12 & 0x1f);
          if (uVar10 < local_14) {
            puVar8 = local_2c + uVar10 * 2;
            do {
              *puVar8 = local_1c;
              puVar8[1] = local_18;
              uVar10 = uVar10 + iVar6;
              puVar8 = puVar8 + iVar6 * 2;
              iVar11 = local_38;
            } while (uVar10 < local_14);
          }
          uVar10 = 1 << ((byte)local_34 & 0x1f);
          while ((local_24 & uVar10) != 0) {
            local_24 = local_24 ^ uVar10;
            uVar10 = uVar10 >> 1;
          }
          local_24 = local_24 ^ uVar10;
          uVar9 = local_1c;
          if (((1 << (bVar12 & 0x1f)) - 1U & local_24) != local_c0[local_10]) {
            do {
              iVar3 = iVar3 - local_8;
              local_10 = local_10 + -1;
            } while (((1 << ((byte)iVar3 & 0x1f)) - 1U & local_24) != local_c0[local_10]);
          }
        }
        local_c = local_c + 1;
        local_28 = local_28 + 1;
        local_34 = local_34 + 1;
      } while ((int)local_c <= (int)local_30);
    }
    if ((iVar11 != 0) && (local_30 != 1)) {
      return -5;
    }
  }
  return 0;
}



/* inflate_trees_bits @ 10036caf */

/* zlib (internal): build bit length Huffman tree */

int __cdecl inflate_trees_bits(uInt *c,uInt *bb,void **tb,void *hp,z_streamp z)

{
  uInt *hn;
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  hn = (*z->zalloc)(z->opaque,0x13,4);
  if (hn == (uInt *)0x0) {
    iVar1 = -4;
  }
  else {
    iVar1 = huft_build(c,0x13,0x13,(uInt *)0x0,(uInt *)0x0,tb,hp,&local_8,hn);
    if (iVar1 == -3) {
      z->msg = "oversubscribed dynamic bit lengths tree";
    }
    else if ((iVar1 == -5) || (*bb == 0)) {
      z->msg = "incomplete dynamic bit lengths tree";
      iVar1 = -3;
    }
    (*z->zfree)(z->opaque,hn);
  }
  return iVar1;
}



/* inflate_trees_dynamic @ 10036d2e */

/* zlib (internal): build dynamic Huffman trees */

int __cdecl
inflate_trees_dynamic
          (uInt nl,uInt nd,uInt *c,uInt *bl,uInt *bd,void **tl,void **td,void *hp,z_streamp z)

{
  uInt *hn;
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  hn = (*z->zalloc)(z->opaque,0x120,4);
  if (hn == (uInt *)0x0) {
    return -4;
  }
  iVar1 = huft_build(c,nl,0x101,(uInt *)&DAT_1004f868,(uInt *)&DAT_1004f8e8,tl,hp,&local_8,hn);
  if (iVar1 == 0) {
    if (*bl == 0) goto LAB_10036e13;
    iVar1 = huft_build(c + nl,nd,0,(uInt *)&DAT_1004f968,(uInt *)&DAT_1004f9e0,td,hp,&local_8,hn);
    if (iVar1 == 0) {
      if ((*bd != 0) || (nl < 0x102)) {
        iVar1 = 0;
        goto LAB_10036e1f;
      }
LAB_10036df7:
      z->msg = "empty distance tree with lengths";
    }
    else {
      if (iVar1 == -3) {
        z->msg = "oversubscribed distance tree";
        goto LAB_10036e1f;
      }
      if (iVar1 != -5) {
        if (iVar1 == -4) goto LAB_10036e1f;
        goto LAB_10036df7;
      }
      z->msg = "incomplete distance tree";
    }
  }
  else {
    if (iVar1 == -3) {
      z->msg = "oversubscribed literal/length tree";
      goto LAB_10036e1f;
    }
    if (iVar1 == -4) goto LAB_10036e1f;
LAB_10036e13:
    z->msg = "incomplete literal/length tree";
  }
  iVar1 = -3;
LAB_10036e1f:
  (*z->zfree)(z->opaque,hn);
  return iVar1;
}



/* inflate_flush @ 10036e60 */

/* zlib (internal): flush pending output */

int __cdecl inflate_flush(void *s,z_streamp z,int r)

{
  Bytef *pBVar1;
  void *pvVar2;
  uLong uVar3;
  uint uVar4;
  Bytef *pBVar5;
  Bytef *pBVar6;
  uint uVar7;
  Bytef *pBVar8;
  Bytef *local_c;
  
  pvVar2 = s;
  pBVar1 = *(Bytef **)((int)s + 0x30);
  local_c = z->next_out;
  pBVar5 = *(Bytef **)((int)s + 0x34);
  if (pBVar5 < pBVar1) {
    pBVar5 = *(Bytef **)((int)s + 0x2c);
  }
  uVar4 = z->avail_out;
  uVar7 = (int)pBVar5 - (int)pBVar1;
  if (uVar4 < (uint)((int)pBVar5 - (int)pBVar1)) {
    uVar7 = uVar4;
  }
  if ((uVar7 != 0) && (r == -5)) {
    r = 0;
  }
  z->total_out = z->total_out + uVar7;
  z->avail_out = uVar4 - uVar7;
  if (*(code **)((int)s + 0x38) != (code *)0x0) {
    uVar3 = (**(code **)((int)s + 0x38))(*(undefined4 *)((int)s + 0x3c),pBVar1,uVar7);
    *(uLong *)((int)s + 0x3c) = uVar3;
    z->adler = uVar3;
  }
  pBVar5 = pBVar1;
  pBVar6 = local_c;
  for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pBVar6 = *(undefined4 *)pBVar5;
    pBVar5 = pBVar5 + 4;
    pBVar6 = pBVar6 + 4;
  }
  local_c = local_c + uVar7;
  for (uVar4 = uVar7 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pBVar6 = *pBVar5;
    pBVar5 = pBVar5 + 1;
    pBVar6 = pBVar6 + 1;
  }
  pBVar5 = pBVar1 + uVar7;
  if (pBVar1 + uVar7 == *(Bytef **)((int)s + 0x2c)) {
    pBVar1 = *(Bytef **)((int)s + 0x28);
    if (*(Bytef **)((int)s + 0x34) == *(Bytef **)((int)s + 0x2c)) {
      *(Bytef **)((int)s + 0x34) = pBVar1;
    }
    uVar4 = z->avail_out;
    uVar7 = *(int *)((int)s + 0x34) - (int)pBVar1;
    if (uVar4 < uVar7) {
      uVar7 = uVar4;
    }
    if ((uVar7 != 0) && (r == -5)) {
      r = 0;
    }
    z->total_out = z->total_out + uVar7;
    z->avail_out = uVar4 - uVar7;
    if (*(code **)((int)s + 0x38) != (code *)0x0) {
      uVar3 = (**(code **)((int)s + 0x38))(*(undefined4 *)((int)s + 0x3c),pBVar1,uVar7);
      *(uLong *)((int)s + 0x3c) = uVar3;
      z->adler = uVar3;
    }
    pBVar6 = pBVar1;
    pBVar8 = local_c;
    for (uVar4 = uVar7 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pBVar8 = *(undefined4 *)pBVar6;
      pBVar6 = pBVar6 + 4;
      pBVar8 = pBVar8 + 4;
    }
    local_c = local_c + uVar7;
    for (uVar4 = uVar7 & 3; pBVar5 = pBVar1 + uVar7, uVar4 != 0; uVar4 = uVar4 - 1) {
      *pBVar8 = *pBVar6;
      pBVar6 = pBVar6 + 1;
      pBVar8 = pBVar8 + 1;
    }
  }
  s = pBVar5;
  z->next_out = local_c;
  *(void **)((int)pvVar2 + 0x30) = s;
  return r;
}



/* grim_zlib_inflate_codes_process @ 10038bbd */

uint __cdecl
grim_zlib_inflate_codes_process(uint param_1,uint param_2,int param_3,int param_4,int param_5,byte *param_6)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte *local_14;
  uint local_10;
  byte *local_c;
  uint local_8;
  
  pbVar3 = param_6;
  local_c = *(byte **)param_6;
  local_8 = *(uint *)(param_6 + 4);
  param_6 = *(byte **)(param_5 + 0x34);
  uVar9 = *(uint *)(param_5 + 0x1c);
  if (param_6 < *(byte **)(param_5 + 0x30)) {
    local_14 = *(byte **)(param_5 + 0x30) + (-1 - (int)param_6);
  }
  else {
    local_14 = (byte *)(*(int *)(param_5 + 0x2c) - (int)param_6);
  }
  uVar8 = *(uint *)(&grim_zlib_mask_bits + param_1 * 4);
  uVar6 = *(uint *)(&grim_zlib_mask_bits + param_2 * 4);
  param_1 = *(uint *)(param_5 + 0x20);
  do {
    for (; uVar9 < 0x14; uVar9 = uVar9 + 8) {
      local_8 = local_8 - 1;
      param_1 = param_1 | (uint)*local_c << ((byte)uVar9 & 0x1f);
      local_c = local_c + 1;
    }
    pbVar4 = (byte *)(param_3 + (uVar8 & param_1) * 8);
    bVar1 = *pbVar4;
LAB_10038c62:
    uVar7 = (uint)bVar1;
    if (uVar7 != 0) {
      param_1 = param_1 >> (pbVar4[1] & 0x1f);
      uVar9 = uVar9 - pbVar4[1];
      if ((bVar1 & 0x10) != 0) {
        uVar7 = uVar7 & 0xf;
        local_10 = (*(uint *)(&grim_zlib_mask_bits + uVar7 * 4) & param_1) + *(int *)(pbVar4 + 4);
        uVar10 = param_1 >> (sbyte)uVar7;
        for (uVar9 = uVar9 - uVar7; uVar9 < 0xf; uVar9 = uVar9 + 8) {
          local_8 = local_8 - 1;
          uVar10 = uVar10 | (uint)*local_c << ((byte)uVar9 & 0x1f);
          local_c = local_c + 1;
        }
        pbVar4 = (byte *)(param_4 + (uVar6 & uVar10) * 8);
        param_1 = uVar10 >> (pbVar4[1] & 0x1f);
        uVar9 = uVar9 - pbVar4[1];
        while( true ) {
          bVar1 = *pbVar4;
          if ((bVar1 & 0x10) != 0) {
            uVar7 = bVar1 & 0xf;
            for (; uVar9 < uVar7; uVar9 = uVar9 + 8) {
              local_8 = local_8 - 1;
              param_1 = param_1 | (uint)*local_c << ((byte)uVar9 & 0x1f);
              local_c = local_c + 1;
            }
            uVar10 = (*(uint *)(&grim_zlib_mask_bits + uVar7 * 4) & param_1) + *(int *)(pbVar4 + 4);
            local_14 = local_14 + -local_10;
            param_1 = param_1 >> (sbyte)uVar7;
            uVar9 = uVar9 - uVar7;
            if ((uint)((int)param_6 - *(int *)(param_5 + 0x28)) < uVar10) {
              param_2 = (*(int *)(param_5 + 0x28) - (int)param_6) + uVar10;
              pbVar5 = (byte *)(*(int *)(param_5 + 0x2c) - param_2);
              pbVar4 = param_6;
              if (param_2 < local_10) {
                local_10 = local_10 - param_2;
                do {
                  bVar1 = *pbVar5;
                  pbVar4 = param_6 + 1;
                  pbVar5 = pbVar5 + 1;
                  param_2 = param_2 - 1;
                  *param_6 = bVar1;
                  param_6 = pbVar4;
                } while (param_2 != 0);
                pbVar5 = *(byte **)(param_5 + 0x28);
              }
            }
            else {
              pbVar5 = param_6 + -uVar10;
              *param_6 = *pbVar5;
              param_6[1] = pbVar5[1];
              pbVar5 = pbVar5 + 2;
              local_10 = local_10 - 2;
              pbVar4 = param_6 + 2;
            }
            do {
              *pbVar4 = *pbVar5;
              param_6 = pbVar4 + 1;
              pbVar5 = pbVar5 + 1;
              local_10 = local_10 - 1;
              pbVar4 = param_6;
            } while (local_10 != 0);
            goto LAB_10038dc1;
          }
          if ((bVar1 & 0x40) != 0) break;
          pbVar4 = pbVar4 + ((*(uint *)(&grim_zlib_mask_bits + (uint)bVar1 * 4) & param_1) +
                            *(int *)(pbVar4 + 4)) * 8;
          param_1 = param_1 >> (pbVar4[1] & 0x1f);
          uVar9 = uVar9 - pbVar4[1];
        }
        *(char **)(pbVar3 + 0x18) = "invalid distance code";
        uVar8 = *(int *)(pbVar3 + 4) - local_8;
        if (uVar9 >> 3 < *(int *)(pbVar3 + 4) - local_8) {
          uVar8 = uVar9 >> 3;
        }
LAB_10038e3a:
        param_2 = 0xfffffffd;
        goto LAB_10038e41;
      }
      if ((bVar1 & 0x40) == 0) break;
      uVar6 = uVar9 >> 3;
      if ((bVar1 & 0x20) == 0) {
        uVar8 = *(int *)(pbVar3 + 4) - local_8;
        *(char **)(pbVar3 + 0x18) = "invalid literal/length code";
        if (uVar6 < uVar8) {
          uVar8 = uVar6;
        }
        goto LAB_10038e3a;
      }
      uVar8 = *(int *)(pbVar3 + 4) - local_8;
      if (uVar6 < uVar8) {
        uVar8 = uVar6;
      }
      param_2 = 1;
      goto LAB_10038e41;
    }
    param_1 = param_1 >> (pbVar4[1] & 0x1f);
    uVar9 = uVar9 - pbVar4[1];
    local_14 = local_14 + -1;
    *param_6 = pbVar4[4];
    param_6 = param_6 + 1;
LAB_10038dc1:
    if ((local_14 < (byte *)0x102) || (local_8 < 10)) {
      uVar8 = *(int *)(pbVar3 + 4) - local_8;
      if (uVar9 >> 3 < *(int *)(pbVar3 + 4) - local_8) {
        uVar8 = uVar9 >> 3;
      }
      param_2 = 0;
LAB_10038e41:
      *(uint *)(param_5 + 0x20) = param_1;
      *(uint *)(param_5 + 0x1c) = uVar9 + uVar8 * -8;
      *(uint *)(pbVar3 + 4) = uVar8 + local_8;
      iVar2 = *(int *)pbVar3;
      *(uint *)pbVar3 = (int)local_c - uVar8;
      *(uint *)(pbVar3 + 8) = *(int *)(pbVar3 + 8) + (((int)local_c - uVar8) - iVar2);
      *(byte **)(param_5 + 0x34) = param_6;
      return param_2;
    }
  } while( true );
  pbVar4 = pbVar4 + ((*(uint *)(&grim_zlib_mask_bits + uVar7 * 4) & param_1) + *(int *)(pbVar4 + 4)) * 8;
  bVar1 = *pbVar4;
  goto LAB_10038c62;
}



/* grim_zlib_huffman_build_fixed @ 1003fc90 */

void __cdecl grim_zlib_huffman_build_fixed(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  undefined1 *puVar12;
  int local_51c;
  int *piStack_518;
  int iStack_514;
  int iStack_510;
  char local_508 [256];
  int aiStack_408 [258];
  
  if (*param_3 == 0) {
    iVar3 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x5d4);
    *param_3 = iVar3;
  }
  iVar3 = *param_3;
  iVar4 = 0;
  *(int *)(iVar3 + 0xd0) = param_2;
  local_51c = 0;
  iVar7 = 1;
  do {
    bVar1 = *(byte *)(iVar7 + param_2);
    if (bVar1 != 0) {
      cVar2 = (char)iVar7;
      pcVar10 = local_508 + iVar4;
      for (uVar6 = (uint)(bVar1 >> 2); uVar6 != 0; uVar6 = uVar6 - 1) {
        *(uint *)pcVar10 = CONCAT22(CONCAT11(cVar2,cVar2),CONCAT11(cVar2,cVar2));
        pcVar10 = pcVar10 + 4;
      }
      for (uVar6 = bVar1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pcVar10 = cVar2;
        pcVar10 = pcVar10 + 1;
      }
      iVar4 = local_51c + (uint)bVar1;
      local_51c = iVar4;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x11);
  local_508[iVar4] = '\0';
  iVar4 = 0;
  iVar7 = 0;
  iVar9 = (int)local_508[0];
  while (local_508[0] != '\0') {
    if (local_508[iVar7] == iVar9) {
      piVar5 = aiStack_408 + iVar7 + 1;
      do {
        cVar2 = local_508[iVar7 + 1];
        iVar7 = iVar7 + 1;
        *piVar5 = iVar4;
        piVar5 = piVar5 + 1;
        iVar4 = iVar4 + 1;
      } while (cVar2 == iVar9);
    }
    iVar4 = iVar4 << 1;
    iVar9 = iVar9 + 1;
    local_508[0] = local_508[iVar7];
  }
  iVar7 = 0;
  iVar4 = 1;
  piVar5 = (int *)(iVar3 + 0x48);
  do {
    if (*(char *)(iVar4 + param_2) == '\0') {
      *piVar5 = -1;
    }
    else {
      iVar9 = aiStack_408[iVar7 + 1];
      piVar5[0x12] = iVar7;
      piVar5[-0x11] = iVar9;
      iVar7 = iVar7 + (uint)*(byte *)(iVar4 + param_2);
      *piVar5 = aiStack_408[iVar7];
    }
    iVar4 = iVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar4 < 0x11);
  iVar4 = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0xfffff;
  puVar11 = (undefined4 *)(iVar3 + 0xd4);
  for (iVar7 = 0x100; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  local_51c = 0;
  iVar7 = 1;
  iStack_510 = 7;
  do {
    iStack_514 = 1;
    if (*(char *)(param_2 + iVar7) != '\0') {
      puVar12 = (undefined1 *)(iVar4 + 0x11 + param_2);
      piStack_518 = aiStack_408 + iVar4 + 1;
      iVar9 = 1 << ((byte)iStack_510 & 0x1f);
      do {
        iVar4 = *piStack_518 << ((byte)iStack_510 & 0x1f);
        if (0 < iVar9) {
          puVar8 = (undefined1 *)(iVar4 + 0x4d4 + iVar3);
          piVar5 = (int *)(iVar3 + 0xd4 + iVar4 * 4);
          iVar4 = iVar9;
          do {
            *piVar5 = iVar7;
            piVar5 = piVar5 + 1;
            *puVar8 = *puVar12;
            puVar8 = puVar8 + 1;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
        iStack_514 = iStack_514 + 1;
        iVar4 = local_51c + 1;
        piStack_518 = piStack_518 + 1;
        puVar12 = puVar12 + 1;
        local_51c = iVar4;
      } while (iStack_514 <= (int)(uint)*(byte *)(param_2 + iVar7));
    }
    iVar7 = iVar7 + 1;
    iStack_510 = iStack_510 + -1;
  } while (-1 < iStack_510);
  return;
}



/* grim_zlib_huft_free @ 1003fe80 */

undefined4 __cdecl grim_zlib_huft_free(undefined4 *param_1,uint param_2,int param_3,int param_4)

{
  uint in_EAX;
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = param_1[1];
  pbVar3 = (byte *)*param_1;
  for (; param_3 < 0x19; param_3 = param_3 + 8) {
    in_EAX = param_1[2];
    if (in_EAX == 0) {
      if (iVar2 == 0) {
        uVar1 = (**(code **)(*(int *)(param_1[5] + 0x14) + 0xc))(param_1[5]);
        if ((char)uVar1 == '\0') {
LAB_1003ff70:
          return uVar1 & 0xffffff00;
        }
        pbVar3 = (byte *)**(undefined4 **)(param_1[5] + 0x14);
        iVar2 = (*(undefined4 **)(param_1[5] + 0x14))[1];
      }
      in_EAX = (uint)*pbVar3;
      iVar2 = iVar2 + -1;
      pbVar3 = pbVar3 + 1;
      if (in_EAX == 0xff) {
        do {
          if (iVar2 == 0) {
            uVar1 = (**(code **)(*(int *)(param_1[5] + 0x14) + 0xc))(param_1[5]);
            if ((char)uVar1 == '\0') goto LAB_1003ff70;
            pbVar3 = (byte *)**(undefined4 **)(param_1[5] + 0x14);
            iVar2 = (*(undefined4 **)(param_1[5] + 0x14))[1];
          }
          in_EAX = (uint)*pbVar3;
          iVar2 = iVar2 + -1;
          pbVar3 = pbVar3 + 1;
        } while (in_EAX == 0xff);
        if (in_EAX != 0) {
          param_1[2] = in_EAX;
          goto LAB_1003ff11;
        }
        in_EAX = 0xff;
      }
    }
    else {
LAB_1003ff11:
      if (param_4 <= param_3) break;
      if (*(char *)param_1[6] == '\0') {
        *(undefined4 *)(*(int *)param_1[5] + 0x14) = 0x71;
        (**(code **)(*(int *)param_1[5] + 4))((int *)param_1[5],0xffffffff);
        *(undefined1 *)param_1[6] = 1;
      }
      in_EAX = 0;
    }
    param_2 = param_2 << 8 | in_EAX;
  }
  *param_1 = pbVar3;
  param_1[1] = iVar2;
  param_1[4] = param_3;
  param_1[3] = param_2;
  return CONCAT31((int3)(in_EAX >> 8),1);
}



/* grim_zlib_huft_free_all @ 1003ff80 */

uint __cdecl grim_zlib_huft_free_all(undefined4 *param_1,uint param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  if (param_3 < param_5) {
    uVar1 = grim_zlib_huft_free(param_1,param_2,param_3,param_5);
    if ((char)uVar1 == '\0') {
      return 0xffffffff;
    }
    param_2 = param_1[3];
    param_3 = param_1[4];
  }
  iVar2 = param_3 - param_5;
  piVar4 = (int *)(param_4 + 0x44 + param_5 * 4);
  uVar3 = (int)param_2 >> ((byte)iVar2 & 0x1f) & (1 << ((byte)param_5 & 0x1f)) - 1U;
  if (*piVar4 < (int)uVar3) {
    do {
      if (iVar2 < 1) {
        uVar1 = grim_zlib_huft_free(param_1,param_2,iVar2,1);
        if ((char)uVar1 == '\0') {
          return 0xffffffff;
        }
        param_2 = param_1[3];
        iVar2 = param_1[4];
      }
      iVar2 = iVar2 + -1;
      piVar4 = piVar4 + 1;
      uVar3 = uVar3 << 1 | (int)param_2 >> ((byte)iVar2 & 0x1f) & 1U;
      param_5 = param_5 + 1;
    } while (*piVar4 < (int)uVar3);
  }
  param_1[4] = iVar2;
  param_1[3] = param_2;
  if (0x10 < param_5) {
    *(undefined4 *)(*(int *)param_1[5] + 0x14) = 0x72;
    (**(code **)(*(int *)param_1[5] + 4))((int *)param_1[5],0xffffffff);
    return 0;
  }
  return (uint)*(byte *)((*(int *)(param_4 + 0x8c + param_5 * 4) - *(int *)(param_4 + param_5 * 4))
                         + *(int *)(param_4 + 0xd0) + 0x11 + uVar3);
}



/* grim_zlib_inflate_reset @ 10040070 */

void __cdecl grim_zlib_inflate_reset(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x48);
  *(undefined4 **)(param_1 + 0x194) = puVar1;
  *puVar1 = &LAB_100400b0;
  puVar1[1] = &LAB_10040200;
  puVar1 = puVar1 + 10;
  iVar2 = 4;
  do {
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



/* grim_zlib_inflate_codes_init @ 100406a0 */

void __cdecl grim_zlib_inflate_codes_init(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x40);
  *(undefined4 **)(param_1 + 0x194) = puVar1;
  *puVar1 = &LAB_10040710;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1 = (undefined4 *)
           (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,*(int *)(param_1 + 0x20) << 8);
  *(undefined4 **)(param_1 + 0x8c) = puVar1;
  iVar3 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    do {
      puVar4 = puVar1;
      for (iVar2 = 0x40; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = 0xffffffff;
        puVar4 = puVar4 + 1;
      }
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 0x40;
    } while (iVar3 < *(int *)(param_1 + 0x20));
  }
  return;
}



/* grim_zlib_inflate_codes_free_state @ 10041590 */

void __cdecl grim_zlib_inflate_codes_free_state(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  puVar1 = param_1;
  puVar2 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x54);
  param_1[0x66] = puVar2;
  *puVar2 = &LAB_10041610;
  iVar5 = 0;
  if (0 < (int)param_1[8]) {
    param_1 = (undefined4 *)(param_1[0x31] + 0x50);
    puVar2 = puVar2 + 0xb;
    do {
      puVar3 = (undefined4 *)(**(code **)puVar1[1])(puVar1,1,0x100);
      *param_1 = puVar3;
      for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
      *puVar2 = 0xffffffff;
      iVar5 = iVar5 + 1;
      param_1 = param_1 + 0x15;
      puVar2 = puVar2 + 1;
    } while (iVar5 < (int)puVar1[8]);
  }
  return;
}



/* grim_zlib_inflate_blocks_init @ 10041850 */

void __cdecl grim_zlib_inflate_blocks_init(int param_1,char param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  puVar2 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x1c);
  *(undefined4 **)(param_1 + 0x188) = puVar2;
  *puVar2 = &LAB_100418e0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  if (*(char *)(param_1 + 0x4a) != '\0') {
    iVar5 = *(int *)(param_1 + 0x110);
    puVar2[4] = iVar5;
    if (param_2 != '\0') {
      iVar1 = *(int *)(param_1 + 4);
      iVar3 = grim_jpg_data_src_init(*(int *)(param_1 + 0x60),iVar5);
      uVar4 = (**(code **)(iVar1 + 0x10))
                        (param_1,1,0,*(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c),iVar3,iVar5)
      ;
      puVar2[2] = uVar4;
      return;
    }
    uVar4 = (**(code **)(*(int *)(param_1 + 4) + 8))
                      (param_1,1,*(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c),iVar5);
    puVar2[3] = uVar4;
  }
  return;
}



/* grim_zlib_inflate_blocks_free_state @ 10041a60 */

/* [binja] int32_t sub_10041a60(void* arg1, int32_t arg2, int32_t arg3, int32_t arg4, void** arg5)
    */

int __cdecl grim_zlib_inflate_blocks_free_state(void *arg1,int arg2,int arg3,int arg4,void **arg5)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int *in_stack_00000018;
  
  iVar2 = *(int *)((int)arg1 + 0x188);
  puVar1 = (uint *)(iVar2 + 0x18);
  if (*(int *)(iVar2 + 0x18) == 0) {
    uVar4 = (**(code **)(*(int *)((int)arg1 + 4) + 0x1c))
                      (arg1,*(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0x14),
                       *(undefined4 *)(iVar2 + 0x10),1);
    *(undefined4 *)(iVar2 + 0xc) = uVar4;
  }
  uVar3 = *puVar1;
  (**(code **)(*(int *)((int)arg1 + 0x19c) + 4))
            (arg1,arg2,arg3,arg4,*(undefined4 *)(iVar2 + 0xc),puVar1,*(undefined4 *)(iVar2 + 0x10));
  if (uVar3 < *puVar1) {
    iVar5 = *puVar1 - uVar3;
    (**(code **)(*(int *)((int)arg1 + 0x1a4) + 4))(arg1,*(int *)(iVar2 + 0xc) + uVar3 * 4,0,iVar5);
    *in_stack_00000018 = *in_stack_00000018 + iVar5;
  }
  uVar3 = *(uint *)(iVar2 + 0x10);
  if (uVar3 <= *puVar1) {
    *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + uVar3;
    *puVar1 = 0;
  }
  return uVar3;
}



/* grim_zlib_inflate_blocks_reset_state @ 10041b00 */

/* [binja] int32_t sub_10041b00(void* arg1, int32_t arg2, int32_t* arg3, int32_t arg4) */

int __cdecl grim_zlib_inflate_blocks_reset_state(void *arg1,int arg2,int *arg3,int arg4)

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
  uVar3 = *(uint *)(iVar1 + 0x10);
  uVar4 = *(int *)(iVar1 + 0x18) + uVar4;
  *(uint *)(iVar1 + 0x18) = uVar4;
  if (uVar3 <= uVar4) {
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + uVar3;
    *(undefined4 *)(iVar1 + 0x18) = 0;
  }
  return uVar3;
}



/* grim_zlib_inflate_blocks_sync_point @ 10041ba0 */

void __cdecl grim_zlib_inflate_blocks_sync_point(int *param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  int iStack_c;
  
  puVar3 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0xa0);
  param_1[0x67] = (int)puVar3;
  *puVar3 = &LAB_10041da0;
  puVar3[1] = &LAB_10041dc0;
  *(undefined1 *)(puVar3 + 2) = 0;
  if ((char)param_1[0x42] != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x17;
    (**(code **)*param_1)(param_1);
  }
  if (((char)param_1[0x12] == '\0') || (bVar2 = true, param_1[0x45] < 2)) {
    bVar2 = false;
  }
  iStack_c = 0;
  if (0 < param_1[8]) {
    piVar7 = (int *)(param_1[0x31] + 0x24);
    puVar8 = puVar3 + 0xd;
    do {
      iVar4 = (piVar7[-7] * *piVar7) / param_1[0x45];
      iVar5 = (piVar7[-6] * *piVar7) / param_1[0x45];
      iVar9 = param_1[0x44];
      iVar1 = param_1[0x43];
      puVar8[0xc] = iVar5;
      if ((char)piVar7[3] == '\0') {
        *puVar8 = &LAB_10041ec0;
      }
      else if ((iVar4 == iVar1) && (iVar5 == iVar9)) {
        *puVar8 = &LAB_10041eb0;
      }
      else {
        if (iVar4 * 2 == iVar1) {
          if (iVar5 == iVar9) {
            if ((bVar2) && (2 < (uint)piVar7[1])) {
              *puVar8 = &LAB_100420e0;
            }
            else {
              *puVar8 = &LAB_10041ff0;
            }
          }
          else {
            if ((iVar4 * 2 != iVar1) || (iVar5 * 2 != iVar9)) goto LAB_10041cf5;
            if ((bVar2) && (2 < (uint)piVar7[1])) {
              *puVar8 = &LAB_100421b0;
              *(undefined1 *)(puVar3 + 2) = 1;
            }
            else {
              *puVar8 = &LAB_10042050;
            }
          }
        }
        else {
LAB_10041cf5:
          if ((iVar1 % iVar4 == 0) && (iVar9 % iVar5 == 0)) {
            *puVar8 = &LAB_10041ed0;
            *(char *)(iStack_c + 0x8c + (int)puVar3) = (char)(iVar1 / iVar4);
            *(char *)(iStack_c + 0x96 + (int)puVar3) = (char)(iVar9 / iVar5);
          }
          else {
            *(undefined4 *)(*param_1 + 0x14) = 0x25;
            (**(code **)*param_1)(param_1);
          }
        }
        iVar9 = param_1[0x44];
        iVar1 = param_1[1];
        iVar4 = grim_jpg_data_src_init(param_1[0x17],param_1[0x43]);
        uVar6 = (**(code **)(iVar1 + 8))(param_1,1,iVar4,iVar9);
        puVar8[-10] = uVar6;
      }
      iStack_c = iStack_c + 1;
      puVar8 = puVar8 + 1;
      piVar7 = piVar7 + 0x15;
    } while (iStack_c < param_1[8]);
  }
  return;
}



/* grim_zlib_inflate_process @ 10042310 */

void __cdecl grim_zlib_inflate_process(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x18);
  param_1[0x68] = (int)puVar1;
  *puVar1 = &DAT_1003ab00;
  switch(param_1[9]) {
  case 1:
    if (param_1[8] != 1) {
LAB_1004237b:
      *(undefined4 *)(*param_1 + 0x14) = 8;
      (**(code **)*param_1)(param_1);
    }
    break;
  case 2:
  case 3:
    if (param_1[8] != 3) {
      *(undefined4 *)(*param_1 + 0x14) = 8;
      (**(code **)*param_1)(param_1);
    }
    break;
  case 4:
  case 5:
    if (param_1[8] != 4) {
      *(undefined4 *)(*param_1 + 0x14) = 8;
      (**(code **)*param_1)(param_1);
    }
    break;
  default:
    if (param_1[8] < 1) goto LAB_1004237b;
  }
  iVar2 = param_1[10];
  if (iVar2 == 1) {
    param_1[0x19] = 1;
    if ((param_1[9] == 1) || (param_1[9] == 3)) {
      puVar1[1] = &LAB_10042750;
      iVar2 = 1;
      if (1 < param_1[8]) {
        iVar3 = 0x54;
        do {
          *(undefined1 *)(param_1[0x31] + 0x30 + iVar3) = 0;
          iVar2 = iVar2 + 1;
          iVar3 = iVar3 + 0x54;
        } while (iVar2 < param_1[8]);
      }
      goto LAB_10042498;
    }
  }
  else {
    if (iVar2 == 2) {
      param_1[0x19] = 3;
      if (param_1[9] == 3) {
        puVar1[1] = &LAB_10042590;
        grim_zlib_inflate_sync_check((int)param_1);
      }
      else if (param_1[9] == 2) {
        puVar1[1] = grim_zlib_inflate_sync_search;
      }
      else {
        *(undefined4 *)(*param_1 + 0x14) = 0x19;
        (**(code **)*param_1)(param_1);
      }
      goto LAB_10042498;
    }
    if (iVar2 == 4) {
      param_1[0x19] = 4;
      if (param_1[9] == 5) {
        puVar1[1] = &LAB_10042780;
        grim_zlib_inflate_sync_check((int)param_1);
      }
      else if (param_1[9] == 4) {
        puVar1[1] = grim_zlib_inflate_sync_search;
      }
      else {
        *(undefined4 *)(*param_1 + 0x14) = 0x19;
        (**(code **)*param_1)(param_1);
      }
      goto LAB_10042498;
    }
    if (iVar2 == param_1[9]) {
      param_1[0x19] = param_1[8];
      puVar1[1] = grim_zlib_inflate_sync_search;
      goto LAB_10042498;
    }
  }
  *(undefined4 *)(*param_1 + 0x14) = 0x19;
  (**(code **)*param_1)(param_1);
LAB_10042498:
  if (*(char *)((int)param_1 + 0x4a) == '\0') {
    param_1[0x1a] = param_1[0x19];
    return;
  }
  param_1[0x1a] = 1;
  return;
}



/* grim_zlib_inflate_sync_check @ 100424d0 */

void __cdecl grim_zlib_inflate_sync_check(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = *(int *)(param_1 + 0x1a0);
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar1 + 8) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar1 + 0xc) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar1 + 0x10) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  iVar3 = 0;
  param_1 = 0x5b6900;
  iVar6 = -0xe25100;
  iVar5 = -0xb2f480;
  iVar4 = 0x2c8d00;
  do {
    *(int *)(iVar3 + *(int *)(iVar1 + 8)) = iVar5 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0xc)) = iVar6 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x10)) = param_1;
    *(int *)(iVar3 + *(int *)(iVar1 + 0x14)) = iVar4;
    param_1 = param_1 + -0xb6d2;
    iVar4 = iVar4 + -0x581a;
    iVar5 = iVar5 + 0x166e9;
    iVar6 = iVar6 + 0x1c5a2;
    iVar3 = iVar3 + 4;
  } while (-0x2b34e7 < iVar4);
  return;
}



/* grim_zlib_inflate_sync_search @ 100426c0 */

void __cdecl grim_zlib_inflate_sync_search(int param_1,int *param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = *(int *)(param_1 + 0x20);
  iVar2 = *(int *)(param_1 + 0x5c);
  if (-1 < param_5 + -1) {
    param_1 = param_3 << 2;
    do {
      iVar6 = 0;
      piVar5 = param_2;
      if (0 < iVar1) {
        do {
          puVar4 = *(undefined1 **)(*piVar5 + param_1);
          puVar3 = (undefined1 *)(*param_4 + iVar6);
          for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar3 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar3 = puVar3 + iVar1;
          }
          iVar6 = iVar6 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar6 < iVar1);
      }
      param_1 = param_1 + 4;
      param_4 = param_4 + 1;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
  }
  return;
}



/* grim_zlib_inflate_init_internal @ 100428e0 */

void __cdecl grim_zlib_inflate_init_internal(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x30);
  *(undefined4 **)(param_1 + 0x19c) = puVar1;
  *puVar1 = &LAB_10042a10;
  *(undefined1 *)(puVar1 + 2) = 0;
  iVar4 = *(int *)(param_1 + 100) * *(int *)(param_1 + 0x5c);
  puVar1[10] = iVar4;
  if (*(int *)(param_1 + 0x110) == 2) {
    puVar1[1] = &LAB_10042a30;
    puVar1[3] = &LAB_10042c90;
    uVar2 = (**(code **)(*(int *)(param_1 + 4) + 4))(param_1,1,iVar4);
    puVar1[8] = uVar2;
  }
  else {
    puVar1[1] = &LAB_10042b00;
    puVar1[3] = &LAB_10042b40;
    puVar1[8] = 0;
  }
  iVar4 = *(int *)(param_1 + 0x19c);
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar4 + 0x10) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar4 + 0x14) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar4 + 0x18) = uVar2;
  uVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x400);
  *(undefined4 *)(iVar4 + 0x1c) = uVar2;
  iVar3 = 0;
  param_1 = 0x5b6900;
  iVar7 = -0xe25100;
  iVar6 = -0xb2f480;
  iVar5 = 0x2c8d00;
  do {
    *(int *)(iVar3 + *(int *)(iVar4 + 0x10)) = iVar6 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar4 + 0x14)) = iVar7 >> 0x10;
    *(int *)(iVar3 + *(int *)(iVar4 + 0x18)) = param_1;
    *(int *)(iVar3 + *(int *)(iVar4 + 0x1c)) = iVar5;
    param_1 = param_1 + -0xb6d2;
    iVar5 = iVar5 + -0x581a;
    iVar6 = iVar6 + 0x166e9;
    iVar7 = iVar7 + 0x1c5a2;
    iVar3 = iVar3 + 4;
  } while (-0x2b34e7 < iVar5);
  return;
}



/* grim_zlib_inflate_init2_internal @ 10042ea0 */

void __cdecl grim_zlib_inflate_init2_internal(int *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x2c);
  param_1[0x69] = (int)puVar1;
  *puVar1 = &LAB_10043070;
  puVar1[3] = &LAB_10044200;
  puVar1[8] = 0;
  puVar1[10] = 0;
  if (param_1[0x19] != 3) {
    *(undefined4 *)(*param_1 + 0x14) = 0x2e;
    (**(code **)*param_1)(param_1);
  }
  uVar2 = (**(code **)param_1[1])(param_1,1,0x80);
  puVar1[6] = uVar2;
  iVar3 = 0;
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
    grim_zlib_inflate_reset_internal((int)param_1);
  }
  return;
}



/* grim_zlib_inflate_reset_internal @ 10042fd0 */

void __cdecl grim_zlib_inflate_reset_internal(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  
  iVar3 = *(int *)(param_1 + 0x1a4);
  iVar1 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x7fc);
  piVar2 = (int *)(iVar1 + 0x3fc);
  iVar6 = 0x10;
  *(int **)(iVar3 + 0x28) = piVar2;
  iVar3 = 0;
  iVar5 = 0;
  uVar4 = 0x10;
  piVar7 = piVar2;
  piVar8 = piVar2;
  do {
    *piVar7 = iVar3;
    *piVar8 = iVar5;
    piVar7 = piVar7 + 1;
    piVar8 = piVar8 + -1;
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + -1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  piVar7 = (int *)(iVar1 + 0x43c);
  piVar8 = (int *)(iVar1 + 0x3bc);
  do {
    *piVar7 = iVar3;
    *piVar8 = -iVar3;
    uVar4 = uVar4 + 1;
    piVar7 = piVar7 + 1;
    piVar8 = piVar8 + -1;
    iVar3 = iVar3 + (~uVar4 & 1);
  } while ((int)uVar4 < 0x30);
  if ((int)uVar4 < 0x100) {
    piVar7 = piVar2 + uVar4;
    piVar2 = piVar2 + -uVar4;
    iVar1 = 0x100 - uVar4;
    do {
      *piVar7 = iVar3;
      *piVar2 = -iVar3;
      piVar7 = piVar7 + 1;
      piVar2 = piVar2 + -1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}



/* grim_zlib_deflate_state_init @ 100432e0 */

void __cdecl grim_zlib_deflate_state_init(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int local_5b0;
  int local_5ac;
  int *local_5a8;
  int local_5a4;
  byte local_580 [128];
  undefined1 local_500 [256];
  int local_400 [256];
  
  iVar9 = *(int *)(*(int *)(param_1 + 0x1a4) + 0x18);
  iVar15 = (param_3 >> 3) * 0x20;
  iVar16 = iVar15 + 2;
  iVar19 = *(int *)(param_1 + 0x70);
  iVar13 = (param_2 >> 2) * 0x20;
  iVar17 = (param_4 >> 2) * 0x20;
  iVar18 = iVar17 + 4;
  iVar14 = iVar13 + 4;
  local_5a4 = 0x7fffffff;
  local_5b0 = 0;
  if (0 < iVar19) {
    local_5a8 = local_400;
    piVar12 = *(int **)(param_1 + 0x74);
    iVar1 = *piVar12;
    iVar2 = piVar12[1];
    iVar3 = piVar12[2];
    do {
      uVar4 = (uint)*(byte *)(iVar1 + local_5b0);
      if ((int)uVar4 < iVar14) {
        iVar10 = (uVar4 - iVar14) * 2;
        iVar10 = iVar10 * iVar10;
        iVar5 = uVar4 - (iVar13 + 0x1c);
      }
      else {
        iVar5 = iVar13 + 0x1c;
        if (iVar5 < (int)uVar4) {
          iVar10 = (uVar4 - iVar5) * 2;
          iVar10 = iVar10 * iVar10;
        }
        else {
          iVar10 = 0;
          if ((int)uVar4 <= iVar13 + 0x1c + iVar14 >> 1) {
            iVar5 = uVar4 - iVar5;
            goto LAB_100433e8;
          }
        }
        iVar5 = uVar4 - iVar14;
      }
LAB_100433e8:
      uVar4 = (uint)*(byte *)(iVar2 + local_5b0);
      if ((int)uVar4 < iVar16) {
        iVar7 = (uVar4 - iVar16) * 3;
        iVar10 = iVar10 + iVar7 * iVar7;
        iVar7 = uVar4 - (iVar15 + 0x1e);
      }
      else {
        iVar7 = iVar15 + 0x1e;
        if (iVar7 < (int)uVar4) {
          iVar7 = (uVar4 - iVar7) * 3;
          iVar10 = iVar10 + iVar7 * iVar7;
        }
        else if ((int)uVar4 <= iVar15 + 0x1e + iVar16 >> 1) {
          iVar7 = uVar4 - iVar7;
          goto LAB_10043434;
        }
        iVar7 = uVar4 - iVar16;
      }
LAB_10043434:
      uVar4 = (uint)*(byte *)(iVar3 + local_5b0);
      if ((int)uVar4 < iVar18) {
        iVar10 = iVar10 + (uVar4 - iVar18) * (uVar4 - iVar18);
        iVar8 = uVar4 - (iVar17 + 0x1c);
      }
      else {
        iVar8 = iVar17 + 0x1c;
        if (iVar8 < (int)uVar4) {
          iVar10 = iVar10 + (uVar4 - iVar8) * (uVar4 - iVar8);
        }
        else if ((int)uVar4 <= iVar17 + 0x1c + iVar18 >> 1) {
          iVar8 = uVar4 - iVar8;
          goto LAB_1004348f;
        }
        iVar8 = uVar4 - iVar18;
      }
LAB_1004348f:
      *local_5a8 = iVar10;
      iVar5 = iVar5 * 2 * iVar5 * 2 + iVar7 * 3 * iVar7 * 3 + iVar8 * iVar8;
      if (iVar5 < local_5a4) {
        local_5a4 = iVar5;
      }
      local_5a8 = local_5a8 + 1;
      local_5b0 = local_5b0 + 1;
    } while (local_5b0 < iVar19);
  }
  local_5ac = 0;
  local_5b0 = 0;
  if (0 < iVar19) {
    local_5a8 = local_400;
    do {
      if (*local_5a8 <= local_5a4) {
        local_500[local_5ac] = (undefined1)local_5b0;
        local_5ac = local_5ac + 1;
      }
      local_5b0 = local_5b0 + 1;
      local_5a8 = local_5a8 + 1;
    } while (local_5b0 < iVar19);
  }
  grim_zlib_deflate_hash_init(param_1,iVar14,iVar16,iVar18,local_5ac,(int)local_500,local_580);
  pbVar11 = local_580;
  piVar12 = (int *)(iVar9 + (param_2 >> 2) * 0x10);
  local_5a4 = 4;
  do {
    iVar9 = ((param_3 >> 3) * 0x100 + (param_4 >> 2) * 4) * 2;
    iVar19 = 8;
    do {
      iVar13 = 4;
      psVar6 = (short *)(*piVar12 + iVar9);
      do {
        *psVar6 = *pbVar11 + 1;
        pbVar11 = pbVar11 + 1;
        iVar13 = iVar13 + -1;
        psVar6 = psVar6 + 1;
      } while (iVar13 != 0);
      iVar9 = iVar9 + 0x40;
      iVar19 = iVar19 + -1;
    } while (iVar19 != 0);
    piVar12 = piVar12 + 1;
    local_5a4 = local_5a4 + -1;
  } while (local_5a4 != 0);
  return;
}



/* grim_zlib_deflate_hash_init @ 100435e0 */

void __cdecl
grim_zlib_deflate_hash_init(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,byte *param_7)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  int *piVar11;
  int local_220;
  int local_218;
  int local_214;
  int local_210;
  int local_20c;
  int local_200 [128];
  
  piVar11 = local_200;
  for (iVar4 = 0x80; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar11 = 0x7fffffff;
    piVar11 = piVar11 + 1;
  }
  local_218 = 0;
  if (0 < param_5) {
    do {
      bVar1 = *(byte *)(local_218 + param_6);
      uVar8 = (uint)bVar1;
      piVar11 = *(int **)(param_1 + 0x74);
      local_220 = 4;
      iVar2 = (param_2 - (uint)*(byte *)(uVar8 + *piVar11)) * 2;
      iVar5 = param_3 - (uint)*(byte *)(piVar11[1] + uVar8);
      iVar4 = iVar5 * 3;
      iVar6 = param_4 - (uint)*(byte *)(piVar11[2] + uVar8);
      iVar4 = iVar6 * iVar6 + iVar4 * iVar4 + iVar2 * iVar2;
      local_20c = (iVar2 + 8) * 0x20;
      piVar11 = local_200;
      pbVar9 = param_7;
      do {
        local_214 = 8;
        iVar2 = iVar4;
        local_210 = (iVar5 * 9 + 0x12) * 8;
        do {
          iVar10 = 4;
          iVar3 = iVar2;
          iVar7 = (iVar6 + 4) * 0x10;
          do {
            if (iVar3 < *piVar11) {
              *piVar11 = iVar3;
              *pbVar9 = bVar1;
            }
            iVar3 = iVar3 + iVar7;
            iVar7 = iVar7 + 0x80;
            piVar11 = piVar11 + 1;
            pbVar9 = pbVar9 + 1;
            iVar10 = iVar10 + -1;
          } while (iVar10 != 0);
          iVar2 = iVar2 + local_210;
          local_210 = local_210 + 0x120;
          local_214 = local_214 + -1;
        } while (local_214 != 0);
        iVar4 = iVar4 + local_20c;
        local_20c = local_20c + 0x200;
        local_220 = local_220 + -1;
      } while (local_220 != 0);
      local_218 = local_218 + 1;
    } while (local_218 < param_5);
  }
  return;
}



/* grim_zlib_deflate_slow @ 10043c40 */

void __cdecl grim_zlib_deflate_slow(int param_1,int *param_2)

{
  short sVar1;
  short *psVar2;
  short *psVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int *local_4;
  
  iVar6 = *(int *)(*(int *)(param_1 + 0x1a4) + 0x18);
  local_1c = param_2[1];
  local_8 = param_2[5];
  local_14 = param_2[4];
  param_1 = param_2[2];
  local_20 = *param_2;
  local_18 = param_2[3];
  if (local_20 < local_1c) {
    if (local_20 <= local_1c) {
      local_4 = (int *)(iVar6 + local_20 * 4);
      local_10 = local_20;
      do {
        if (param_1 <= local_18) {
          psVar2 = (short *)(*local_4 + (param_1 * 0x20 + local_14) * 2);
          iVar8 = local_14;
          iVar7 = param_1;
          psVar3 = psVar2;
          do {
            for (; iVar8 <= local_8; iVar8 = iVar8 + 1) {
              sVar1 = *psVar2;
              psVar2 = psVar2 + 1;
              if (sVar1 != 0) {
                *param_2 = local_10;
                local_20 = local_10;
                goto LAB_10043d0f;
              }
            }
            iVar7 = iVar7 + 1;
            psVar2 = psVar3 + 0x20;
            iVar8 = local_14;
            psVar3 = psVar2;
          } while (iVar7 <= local_18);
        }
        local_10 = local_10 + 1;
        local_4 = local_4 + 1;
      } while (local_10 <= local_1c);
    }
LAB_10043d0f:
    if (local_20 < local_1c) {
      piVar4 = (int *)(iVar6 + local_1c * 4);
      local_10 = local_1c;
      do {
        if (param_1 <= local_18) {
          psVar2 = (short *)(*piVar4 + (param_1 * 0x20 + local_14) * 2);
          iVar8 = local_14;
          iVar7 = param_1;
          psVar3 = psVar2;
          do {
            for (; iVar8 <= local_8; iVar8 = iVar8 + 1) {
              sVar1 = *psVar2;
              psVar2 = psVar2 + 1;
              if (sVar1 != 0) {
                local_1c = local_10;
                param_2[1] = local_10;
                goto LAB_10043d8f;
              }
            }
            iVar7 = iVar7 + 1;
            psVar2 = psVar3 + 0x20;
            iVar8 = local_14;
            psVar3 = psVar2;
          } while (iVar7 <= local_18);
        }
        local_10 = local_10 + -1;
        piVar4 = piVar4 + -1;
      } while (local_20 <= local_10);
    }
  }
LAB_10043d8f:
  if (param_1 < local_18) {
    if (param_1 <= local_18) {
      iVar8 = (param_1 * 0x20 + local_14) * 2;
      local_10 = param_1;
      do {
        if (local_20 <= local_1c) {
          piVar4 = (int *)(iVar6 + local_20 * 4);
          iVar7 = local_20;
          do {
            psVar2 = (short *)(*piVar4 + iVar8);
            for (iVar5 = local_14; iVar5 <= local_8; iVar5 = iVar5 + 1) {
              sVar1 = *psVar2;
              psVar2 = psVar2 + 1;
              if (sVar1 != 0) {
                param_1 = local_10;
                param_2[2] = local_10;
                goto LAB_10043e16;
              }
            }
            iVar7 = iVar7 + 1;
            piVar4 = piVar4 + 1;
          } while (iVar7 <= local_1c);
        }
        local_10 = local_10 + 1;
        iVar8 = iVar8 + 0x40;
      } while (local_10 <= local_18);
    }
LAB_10043e16:
    if (param_1 < local_18) {
      iVar8 = (local_18 * 0x20 + local_14) * 2;
      local_10 = local_18;
      do {
        if (local_20 <= local_1c) {
          piVar4 = (int *)(iVar6 + local_20 * 4);
          iVar7 = local_20;
          do {
            psVar2 = (short *)(iVar8 + *piVar4);
            for (iVar5 = local_14; iVar5 <= local_8; iVar5 = iVar5 + 1) {
              sVar1 = *psVar2;
              psVar2 = psVar2 + 1;
              if (sVar1 != 0) {
                local_18 = local_10;
                param_2[3] = local_10;
                goto LAB_10043e91;
              }
            }
            iVar7 = iVar7 + 1;
            piVar4 = piVar4 + 1;
          } while (iVar7 <= local_1c);
        }
        local_10 = local_10 + -1;
        iVar8 = iVar8 + -0x40;
      } while (param_1 <= local_10);
    }
  }
LAB_10043e91:
  iVar8 = local_14;
  if (local_14 < local_8) {
    for (; iVar8 <= local_8; iVar8 = iVar8 + 1) {
      if (local_20 <= local_1c) {
        piVar4 = (int *)(iVar6 + local_20 * 4);
        iVar7 = local_20;
        do {
          psVar2 = (short *)(*piVar4 + (param_1 * 0x20 + iVar8) * 2);
          for (iVar5 = param_1; iVar5 <= local_18; iVar5 = iVar5 + 1) {
            if (*psVar2 != 0) {
              param_2[4] = iVar8;
              local_14 = iVar8;
              goto LAB_10043f0f;
            }
            psVar2 = psVar2 + 0x20;
          }
          iVar7 = iVar7 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar7 <= local_1c);
      }
    }
LAB_10043f0f:
    iVar8 = local_8;
    if (local_14 < local_8) {
      do {
        if (local_20 <= local_1c) {
          piVar4 = (int *)(iVar6 + local_20 * 4);
          iVar7 = local_20;
          do {
            psVar2 = (short *)((param_1 * 0x20 + iVar8) * 2 + *piVar4);
            for (iVar5 = param_1; iVar5 <= local_18; iVar5 = iVar5 + 1) {
              if (*psVar2 != 0) {
                param_2[5] = iVar8;
                local_8 = iVar8;
                goto LAB_10043f85;
              }
              psVar2 = psVar2 + 0x20;
            }
            iVar7 = iVar7 + 1;
            piVar4 = piVar4 + 1;
          } while (iVar7 <= local_1c);
        }
        iVar8 = iVar8 + -1;
      } while (local_14 <= iVar8);
    }
  }
LAB_10043f85:
  iVar8 = (local_8 - local_14) * 8;
  iVar5 = (local_18 - param_1) * 0xc;
  iVar7 = (local_1c - local_20) * 0x10;
  param_2[6] = iVar8 * iVar8 + iVar5 * iVar5 + iVar7 * iVar7;
  iVar8 = 0;
  if (local_20 <= local_1c) {
    local_4 = (int *)(iVar6 + local_20 * 4);
    local_10 = (local_1c - local_20) + 1;
    do {
      if (param_1 <= local_18) {
        psVar2 = (short *)(*local_4 + (param_1 * 0x20 + local_14) * 2);
        local_c = (local_18 - param_1) + 1;
        do {
          if (local_14 <= local_8) {
            iVar6 = (local_8 - local_14) + 1;
            psVar3 = psVar2;
            do {
              if (*psVar3 != 0) {
                iVar8 = iVar8 + 1;
              }
              psVar3 = psVar3 + 1;
              iVar6 = iVar6 + -1;
            } while (iVar6 != 0);
          }
          psVar2 = psVar2 + 0x20;
          local_c = local_c + -1;
        } while (local_c != 0);
      }
      local_4 = local_4 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
    param_2[7] = iVar8;
    return;
  }
  param_2[7] = 0;
  return;
}



/* grim_zlib_deflate_fast @ 10044070 */

void __cdecl grim_zlib_deflate_fast(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  ushort *puVar10;
  ushort *puVar11;
  int iVar12;
  int iVar13;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_14;
  
  piVar1 = param_2 + 3;
  iVar8 = param_2[4];
  iVar4 = param_2[2];
  piVar2 = param_2 + 1;
  piVar3 = param_2 + 5;
  iVar9 = *param_2;
  iVar13 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (iVar9 <= *piVar2) {
    local_30 = iVar9 * 8 + 4;
    param_2 = (int *)(*(int *)(*(int *)(param_1 + 0x1a4) + 0x18) + iVar9 * 4);
    local_14 = (*piVar2 - iVar9) + 1;
    do {
      if (iVar4 <= *piVar1) {
        puVar10 = (ushort *)(*param_2 + (iVar4 * 0x20 + iVar8) * 2);
        iVar5 = (*piVar1 - iVar4) + 1;
        iVar9 = iVar4 * 4 + 2;
        do {
          if (iVar8 <= *piVar3) {
            iVar7 = iVar8 * 8 + 4;
            iVar12 = (*piVar3 - iVar8) + 1;
            puVar11 = puVar10;
            do {
              uVar6 = (uint)*puVar11;
              puVar11 = puVar11 + 1;
              if (uVar6 != 0) {
                local_2c = local_2c + local_30 * uVar6;
                local_28 = local_28 + iVar9 * uVar6;
                iVar13 = iVar13 + uVar6;
                local_24 = local_24 + iVar7 * uVar6;
              }
              iVar7 = iVar7 + 8;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
          }
          puVar10 = puVar10 + 0x20;
          iVar9 = iVar9 + 4;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      param_2 = param_2 + 1;
      local_30 = local_30 + 8;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
  }
  iVar8 = iVar13 >> 1;
  *(char *)(**(int **)(param_1 + 0x74) + param_3) = (char)((iVar8 + local_2c) / iVar13);
  *(char *)(*(int *)(*(int *)(param_1 + 0x74) + 4) + param_3) = (char)((local_28 + iVar8) / iVar13);
  *(char *)(*(int *)(*(int *)(param_1 + 0x74) + 8) + param_3) = (char)((local_24 + iVar8) / iVar13);
  return;
}



/* grim_zlib_deflate_process @ 10044210 */

void __cdecl grim_zlib_deflate_process(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iStack_28;
  int *piStack_20;
  int iStack_1c;
  int iStack_14;
  
  piVar3 = param_1;
  puVar4 = (undefined4 *)(**(code **)param_1[1])(param_1,1,0x58);
  param_1[0x69] = (int)puVar4;
  *puVar4 = &LAB_10044690;
  puVar4[2] = &DAT_1003ab00;
  puVar4[3] = &LAB_10044e30;
  puVar4[0x11] = 0;
  puVar4[0xd] = 0;
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
  iVar2 = param_1[0x69];
  iVar5 = grim_zlib_deflate_flush(param_1,(int *)(iVar2 + 0x20));
  if (param_1[0x19] == 3) {
    iVar13 = *param_1;
    *(int *)(iVar13 + 0x18) = iVar5;
    *(int *)(iVar13 + 0x1c) = *(int *)(iVar2 + 0x20);
    *(undefined4 *)(iVar13 + 0x20) = *(undefined4 *)(iVar2 + 0x24);
    *(undefined4 *)(iVar13 + 0x24) = *(undefined4 *)(iVar2 + 0x28);
    *(undefined4 *)(*param_1 + 0x14) = 0x5d;
  }
  else {
    *(undefined4 *)(*param_1 + 0x14) = 0x5e;
    *(int *)(*param_1 + 0x18) = iVar5;
  }
  (**(code **)(*param_1 + 4))(param_1,1);
  piVar6 = (int *)(**(code **)(param_1[1] + 8))(param_1,1,iVar5,param_1[0x19]);
  iStack_14 = 0;
  if (0 < param_1[0x19]) {
    piStack_20 = (int *)(iVar2 + 0x20);
    piVar11 = piVar6;
    iVar13 = iVar5;
    do {
      iStack_1c = *piStack_20;
      iVar7 = iVar13 / iStack_1c;
      if (0 < iStack_1c) {
        iVar1 = iStack_1c + -1;
        iStack_28 = 0;
        param_1 = (int *)0x0;
        do {
          for (iVar10 = iStack_28; iVar10 < iVar5; iVar10 = iVar10 + iVar13) {
            iVar9 = 0;
            if (0 < iVar7) {
              do {
                iVar12 = *piVar11 + iVar9;
                iVar9 = iVar9 + 1;
                *(char *)(iVar10 + iVar12) = (char)((iVar1 / 2 + (int)param_1) / iVar1);
              } while (iVar9 < iVar7);
            }
          }
          param_1 = (int *)((int)param_1 + 0xff);
          iStack_28 = iStack_28 + iVar7;
          iStack_1c = iStack_1c + -1;
        } while (iStack_1c != 0);
      }
      piStack_20 = piStack_20 + 1;
      iStack_14 = iStack_14 + 1;
      piVar11 = piVar11 + 1;
      iVar13 = iVar7;
    } while (iStack_14 < piVar3[0x19]);
  }
  *(int **)(iVar2 + 0x10) = piVar6;
  *(int *)(iVar2 + 0x14) = iVar5;
  grim_zlib_deflate_end((int)piVar3);
  if (piVar3[0x13] == 2) {
    iVar2 = piVar3[0x17];
    iVar5 = 0;
    if (0 < piVar3[0x19]) {
      puVar4 = (undefined4 *)(piVar3[0x69] + 0x44);
      do {
        uVar8 = (**(code **)(piVar3[1] + 4))(piVar3,1,iVar2 * 2 + 4);
        *puVar4 = uVar8;
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar5 < piVar3[0x19]);
    }
  }
  return;
}



/* grim_zlib_deflate_flush @ 10044450 */

int __cdecl grim_zlib_deflate_flush(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piStack_c;
  
  iVar2 = param_1[0x19];
  iVar3 = param_1[0x15];
  iVar8 = 1;
  do {
    iVar7 = iVar8;
    iVar8 = iVar7 + 1;
    iVar5 = iVar8;
    if (1 < iVar2) {
      iVar6 = iVar2 + -1;
      do {
        iVar5 = iVar5 * iVar8;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  } while (iVar5 <= iVar3);
  if (iVar7 < 2) {
    *(undefined4 *)(*param_1 + 0x14) = 0x37;
    *(int *)(*param_1 + 0x18) = iVar5;
    (**(code **)*param_1)(param_1);
  }
  iVar5 = 1;
  iVar8 = iVar2;
  piVar9 = param_2;
  if (0 < iVar2) {
    for (; iVar6 = iVar2, iVar8 != 0; iVar8 = iVar8 + -1) {
      *piVar9 = iVar7;
      piVar9 = piVar9 + 1;
    }
    do {
      iVar5 = iVar5 * iVar7;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  do {
    iVar8 = 0;
    bVar4 = false;
    if (iVar2 < 1) {
      return iVar5;
    }
    piStack_c = &DAT_10050950;
    iVar7 = iVar5;
    do {
      iVar6 = iVar8;
      if (param_1[10] == 2) {
        iVar6 = *piStack_c;
      }
      iVar1 = param_2[iVar6] + 1;
      iVar5 = (iVar7 / param_2[iVar6]) * iVar1;
      if (iVar5 - iVar3 != 0 && iVar3 <= iVar5) {
        iVar5 = iVar7;
        if (!bVar4) {
          return iVar7;
        }
        break;
      }
      param_2[iVar6] = iVar1;
      iVar8 = iVar8 + 1;
      piStack_c = piStack_c + 1;
      bVar4 = true;
      iVar7 = iVar5;
    } while (iVar8 < iVar2);
  } while( true );
}



/* grim_zlib_deflate_end @ 10044540 */

void __cdecl grim_zlib_deflate_end(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 *puVar8;
  int iVar9;
  int iVar10;
  int local_18;
  int *piStack_14;
  char cStack_10;
  int iStack_c;
  
  iVar1 = *(int *)(param_1 + 0x1a4);
  if (*(int *)(param_1 + 0x4c) == 1) {
    local_18 = 0x1fe;
    *(undefined1 *)(iVar1 + 0x1c) = 1;
  }
  else {
    local_18 = 0;
    *(undefined1 *)(iVar1 + 0x1c) = 0;
  }
  uVar3 = (**(code **)(*(int *)(param_1 + 4) + 8))
                    (param_1,1,local_18 + 0x100,*(undefined4 *)(param_1 + 100));
  *(undefined4 *)(iVar1 + 0x18) = uVar3;
  iVar4 = *(int *)(iVar1 + 0x14);
  iStack_c = 0;
  if (0 < *(int *)(param_1 + 100)) {
    piStack_14 = (int *)(iVar1 + 0x20);
    do {
      iVar6 = *piStack_14;
      iVar4 = iVar4 / iVar6;
      if (local_18 != 0) {
        *(int *)(*(int *)(iVar1 + 0x18) + iStack_c * 4) =
             *(int *)(*(int *)(iVar1 + 0x18) + iStack_c * 4) + 0xff;
      }
      puVar2 = *(undefined1 **)(*(int *)(iVar1 + 0x18) + iStack_c * 4);
      iVar5 = (iVar6 + 0xfe) / (iVar6 * 2 + -2);
      iVar9 = 0;
      iVar10 = 0;
      do {
        if (iVar5 < iVar10) {
          iVar7 = iVar9 * 0x1fe;
          do {
            iVar5 = (iVar7 + 0x2fc + iVar6) / (iVar6 * 2 + -2);
            iVar9 = iVar9 + 1;
            iVar7 = iVar7 + 0x1fe;
          } while (iVar5 < iVar10);
        }
        cStack_10 = (char)iVar4;
        puVar2[iVar10] = cStack_10 * (char)iVar9;
        iVar10 = iVar10 + 1;
      } while (iVar10 < 0x100);
      if (local_18 != 0) {
        iVar6 = 1;
        puVar8 = puVar2;
        do {
          puVar8 = puVar8 + -1;
          *puVar8 = *puVar2;
          puVar2[iVar6 + 0xff] = puVar2[0xff];
          iVar6 = iVar6 + 1;
        } while (iVar6 < 0x100);
      }
      iStack_c = iStack_c + 1;
      piStack_14 = piStack_14 + 1;
    } while (iStack_c < *(int *)(param_1 + 100));
  }
  return;
}



/* grim_lzma_decompress @ 10046400 */

uint __cdecl grim_lzma_decompress(undefined4 param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  int local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_18;
  undefined4 local_14;
  
  local_34 = param_4;
  local_38 = param_3;
  local_28 = *param_2;
  local_2c = param_1;
  local_18 = 0;
  local_14 = 0;
  uVar1 = grim_zlib_deflate_init_wrapper((int)&local_38,s_1_1_3_1005820c,0x38);
  if (uVar1 == 0) {
    uVar2 = grim_zlib_inflate_main(&local_38,4);
    if (uVar2 == 1) {
      *param_2 = local_24;
      uVar1 = grim_zlib_tree_init((int)&local_38);
    }
    else {
      grim_zlib_tree_init((int)&local_38);
      uVar1 = 0xfffffffb;
      if (uVar2 != 0) {
        return uVar2;
      }
    }
  }
  return uVar1;
}



/* grim_zlib_tree_init @ 100473f0 */

undefined4 __cdecl grim_zlib_tree_init(int param_1)

{
  int *piVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) && (*(int *)(param_1 + 0x24) != 0)) {
    piVar1 = *(int **)(*(int *)(param_1 + 0x1c) + 0x14);
    if (piVar1 != (int *)0x0) {
      grim_zlib_bit_buffer_flush(piVar1,param_1);
    }
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
    return 0;
  }
  return 0xfffffffe;
}



/* grim_zlib_deflate_init @ 10047440 */

undefined4 __cdecl grim_zlib_deflate_init(int param_1,int param_2,char *param_3,int param_4)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (((param_3 == (char *)0x0) || (*param_3 != s_1_1_3_1005820c[0])) || (param_4 != 0x38)) {
    return 0xfffffffa;
  }
  if (param_1 == 0) {
    return 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  if (*(int *)(param_1 + 0x20) == 0) {
    *(code **)(param_1 + 0x20) = grim_zlib_alloc_default;
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    *(code **)(param_1 + 0x24) = grim_zlib_free_default;
  }
  iVar3 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,0x18);
  *(int *)(param_1 + 0x1c) = iVar3;
  if (iVar3 == 0) {
    return 0xfffffffc;
  }
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 0;
  if (param_2 < 0) {
    param_2 = -param_2;
    *(undefined4 *)(*(int *)(param_1 + 0x1c) + 0xc) = 1;
  }
  if ((7 < param_2) && (param_2 < 0x10)) {
    *(int *)(*(int *)(param_1 + 0x1c) + 0x10) = param_2;
    puVar4 = grim_zlib_static_tree_init(param_1,(undefined *)
                                  (~-(uint)(*(int *)(*(int *)(param_1 + 0x1c) + 0xc) != 0) &
                                  0x10049190),1 << ((byte)param_2 & 0x1f));
    *(undefined4 **)(*(int *)(param_1 + 0x1c) + 0x14) = puVar4;
    puVar1 = *(uint **)(param_1 + 0x1c);
    if (puVar1[5] == 0) {
      if ((puVar1 != (uint *)0x0) && (*(code **)(param_1 + 0x24) != (code *)0x0)) {
        (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1);
        *(undefined4 *)(param_1 + 0x1c) = 0;
      }
      return 0xfffffffc;
    }
    if (puVar1 != (uint *)0x0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      *(undefined4 *)(param_1 + 0x18) = 0;
      *puVar1 = -(uint)(puVar1[3] != 0) & 7;
      grim_zlib_bit_buffer_init(*(int **)(*(int *)(param_1 + 0x1c) + 0x14),param_1,(int *)0x0);
    }
    return 0;
  }
  if ((*(int *)(param_1 + 0x1c) != 0) && (*(int *)(param_1 + 0x24) != 0)) {
    piVar2 = *(int **)(*(int *)(param_1 + 0x1c) + 0x14);
    if (piVar2 != (int *)0x0) {
      grim_zlib_bit_buffer_flush(piVar2,param_1);
    }
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  return 0xfffffffe;
}



/* grim_zlib_deflate_init_wrapper @ 100475b0 */

void __cdecl grim_zlib_deflate_init_wrapper(int param_1,char *param_2,int param_3)

{
  grim_zlib_deflate_init(param_1,0xf,param_2,param_3);
  return;
}



/* grim_zlib_inflate_main @ 100475d0 */

uint __cdecl grim_zlib_inflate_main(int *param_1,int param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  if (((param_1 == (int *)0x0) || (param_1[7] == 0)) || (*param_1 == 0)) {
switchD_10047620_default:
    return 0xfffffffe;
  }
  uVar5 = (param_2 != 4) - 1 & 0xfffffffb;
  uVar4 = 0xfffffffb;
  do {
    puVar2 = (undefined4 *)param_1[7];
    switch(*puVar2) {
    case 0:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      puVar2[1] = (uint)*(byte *)*param_1;
      puVar2 = (undefined4 *)param_1[7];
      uVar3 = puVar2[1];
      *param_1 = *param_1 + 1;
      if (((byte)uVar3 & 0xf) != 8) {
        *puVar2 = 0xd;
        param_1[6] = (int)s_unknown_compression_method_1005826c;
        *(undefined4 *)(param_1[7] + 4) = 5;
        uVar4 = uVar5;
        break;
      }
      if ((uint)puVar2[4] < ((uint)puVar2[1] >> 4) + 8) {
        *puVar2 = 0xd;
        param_1[6] = (int)s_invalid_window_size_10058258;
        *(undefined4 *)(param_1[7] + 4) = 5;
        uVar4 = uVar5;
        break;
      }
      *puVar2 = 1;
      uVar4 = uVar5;
    case 1:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      puVar2 = (undefined4 *)param_1[7];
      param_1[2] = param_1[2] + 1;
      bVar1 = *(byte *)*param_1;
      *param_1 = (int)((byte *)*param_1 + 1);
      if ((puVar2[1] * 0x100 + (uint)bVar1) % 0x1f == 0) {
        if ((bVar1 & 0x20) != 0) {
          *(undefined4 *)param_1[7] = 2;
          uVar4 = uVar5;
          goto switchD_10047620_caseD_2;
        }
        *puVar2 = 7;
        uVar4 = uVar5;
      }
      else {
        *puVar2 = 0xd;
        param_1[6] = (int)s_incorrect_header_check_10058240;
        *(undefined4 *)(param_1[7] + 4) = 5;
        uVar4 = uVar5;
      }
      break;
    case 2:
switchD_10047620_caseD_2:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = (uint)*(byte *)*param_1 << 0x18;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 3;
      uVar4 = uVar5;
switchD_10047620_caseD_3:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x10000;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 4;
      uVar4 = uVar5;
switchD_10047620_caseD_4:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x100;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 5;
      uVar4 = uVar5;
switchD_10047620_caseD_5:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
      param_1[0xc] = ((undefined4 *)param_1[7])[2];
      *(undefined4 *)param_1[7] = 6;
      return 2;
    case 3:
      goto switchD_10047620_caseD_3;
    case 4:
      goto switchD_10047620_caseD_4;
    case 5:
      goto switchD_10047620_caseD_5;
    case 6:
      *(undefined4 *)param_1[7] = 0xd;
      param_1[6] = (int)s_need_dictionary_10058218;
      *(undefined4 *)(param_1[7] + 4) = 0;
      return 0xfffffffe;
    case 7:
      uVar4 = grim_zlib_tree_build_and_flush((uint *)puVar2[5],param_1,uVar4);
      if (uVar4 == 0xfffffffd) {
        *(undefined4 *)param_1[7] = 0xd;
        *(undefined4 *)(param_1[7] + 4) = 0;
        uVar4 = 0xfffffffd;
      }
      else {
        if (uVar4 == 0) {
          uVar4 = uVar5;
        }
        if (uVar4 != 1) {
          return uVar4;
        }
        grim_zlib_bit_buffer_init(*(int **)(param_1[7] + 0x14),(int)param_1,(int *)(param_1[7] + 4));
        puVar2 = (undefined4 *)param_1[7];
        if (puVar2[3] == 0) {
          *puVar2 = 8;
          uVar4 = uVar5;
          goto switchD_10047620_caseD_8;
        }
        *puVar2 = 0xc;
        uVar4 = uVar5;
      }
      break;
    case 8:
switchD_10047620_caseD_8:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = (uint)*(byte *)*param_1 << 0x18;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 9;
      uVar4 = uVar5;
switchD_10047620_caseD_9:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x10000;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 10;
      uVar4 = uVar5;
switchD_10047620_caseD_a:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[2] = param_1[2] + 1;
      param_1[1] = param_1[1] + -1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1 * 0x100;
      *param_1 = *param_1 + 1;
      *(undefined4 *)param_1[7] = 0xb;
      uVar4 = uVar5;
switchD_10047620_caseD_b:
      if (param_1[1] == 0) {
        return uVar4;
      }
      param_1[1] = param_1[1] + -1;
      param_1[2] = param_1[2] + 1;
      *(uint *)(param_1[7] + 8) = *(int *)(param_1[7] + 8) + (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
      puVar2 = (undefined4 *)param_1[7];
      if (puVar2[1] == puVar2[2]) {
        *(undefined4 *)param_1[7] = 0xc;
switchD_10047620_caseD_c:
        return 1;
      }
      *puVar2 = 0xd;
      param_1[6] = (int)s_incorrect_data_check_10058228;
      *(undefined4 *)(param_1[7] + 4) = 5;
      uVar4 = uVar5;
      break;
    case 9:
      goto switchD_10047620_caseD_9;
    case 10:
      goto switchD_10047620_caseD_a;
    case 0xb:
      goto switchD_10047620_caseD_b;
    case 0xc:
      goto switchD_10047620_caseD_c;
    case 0xd:
      return 0xfffffffd;
    default:
      goto switchD_10047620_default;
    }
  } while( true );
}



/* grim_zlib_alloc_default @ 10047a00 */

/* [binja] int32_t sub_10047a00(uint32_t arg1, uint32_t arg2) */

int __cdecl grim_zlib_alloc_default(uint arg1,uint arg2)

{
  void *pvVar1;
  size_t in_stack_0000000c;
  
  pvVar1 = calloc(arg2,in_stack_0000000c);
  return (int)pvVar1;
}



/* grim_zlib_free_default @ 10047a20 */

/* [binja] int32_t sub_10047a20(int32_t arg1) */

int __cdecl grim_zlib_free_default(int arg1)

{
  int extraout_EAX;
  void *in_stack_00000008;
  
  free(in_stack_00000008);
  return extraout_EAX;
}



/* grim_zlib_tree_scan @ 10049190 */

uint __cdecl grim_zlib_tree_scan(uint param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
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
  uint uVar18;
  byte *pbVar19;
  uint uVar20;
  
  uVar2 = param_1 & 0xffff;
  uVar20 = param_1 >> 0x10;
  if (param_2 == (byte *)0x0) {
    return 1;
  }
  while (param_3 != 0) {
    uVar1 = param_3;
    if (0x15af < param_3) {
      uVar1 = 0x15b0;
    }
    param_3 = param_3 - uVar1;
    if (0xf < (int)uVar1) {
      uVar18 = uVar1 >> 4;
      uVar1 = uVar1 + uVar18 * -0x10;
      pbVar19 = param_2;
      do {
        param_2 = pbVar19 + 0x10;
        iVar3 = uVar2 + *pbVar19;
        iVar4 = iVar3 + (uint)pbVar19[1];
        iVar5 = iVar4 + (uint)pbVar19[2];
        iVar6 = iVar5 + (uint)pbVar19[3];
        iVar7 = iVar6 + (uint)pbVar19[4];
        iVar8 = iVar7 + (uint)pbVar19[5];
        iVar9 = iVar8 + (uint)pbVar19[6];
        iVar10 = iVar9 + (uint)pbVar19[7];
        iVar11 = iVar10 + (uint)pbVar19[8];
        iVar12 = iVar11 + (uint)pbVar19[9];
        iVar13 = iVar12 + (uint)pbVar19[10];
        iVar14 = iVar13 + (uint)pbVar19[0xb];
        iVar15 = iVar14 + (uint)pbVar19[0xc];
        iVar16 = iVar15 + (uint)pbVar19[0xd];
        iVar17 = iVar16 + (uint)pbVar19[0xe];
        uVar2 = iVar17 + (uint)pbVar19[0xf];
        uVar20 = uVar20 + iVar3 + iVar4 + iVar5 + iVar6 + iVar7 + iVar8 + iVar9 + iVar10 + iVar11 +
                 iVar12 + iVar13 + iVar14 + iVar15 + iVar16 + iVar17 + uVar2;
        uVar18 = uVar18 - 1;
        pbVar19 = param_2;
      } while (uVar18 != 0);
    }
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      uVar2 = uVar2 + *param_2;
      param_2 = param_2 + 1;
      uVar20 = uVar20 + uVar2;
    }
    uVar2 = uVar2 % 0xfff1;
    uVar20 = uVar20 % 0xfff1;
  }
  return uVar20 << 0x10 | uVar2;
}



/* grim_zlib_bit_buffer_init @ 100492c0 */

void __cdecl grim_zlib_bit_buffer_init(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  
  if (param_3 != (int *)0x0) {
    *param_3 = param_1[0xf];
  }
  if ((*param_1 == 4) || (*param_1 == 5)) {
    (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1[3]);
  }
  if (*param_1 == 6) {
    grim_zlib_tree_process(param_1[1],param_2);
  }
  *param_1 = 0;
  param_1[0xd] = param_1[10];
  param_1[0xc] = param_1[10];
  param_1[7] = 0;
  param_1[8] = 0;
  if ((code *)param_1[0xe] != (code *)0x0) {
    iVar1 = (*(code *)param_1[0xe])(0,0,0);
    param_1[0xf] = iVar1;
    *(int *)(param_2 + 0x30) = iVar1;
  }
  return;
}



/* grim_zlib_static_tree_init @ 10049340 */

undefined4 * __cdecl grim_zlib_static_tree_init(int param_1,undefined *param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  puVar1 = (undefined4 *)(**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,0x40);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  iVar2 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),8,0x5a0);
  puVar1[9] = iVar2;
  if (iVar2 == 0) {
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1);
    return (undefined4 *)0x0;
  }
  iVar2 = (**(code **)(param_1 + 0x20))(*(undefined4 *)(param_1 + 0x28),1,param_3);
  puVar1[10] = iVar2;
  if (iVar2 == 0) {
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1[9]);
    (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x28),puVar1);
    return (undefined4 *)0x0;
  }
  *puVar1 = 0;
  puVar1[0xb] = iVar2 + param_3;
  puVar1[0xe] = param_2;
  puVar1[7] = 0;
  puVar1[8] = 0;
  puVar1[0xd] = iVar2;
  puVar1[0xc] = iVar2;
  if (param_2 != (undefined *)0x0) {
    uVar3 = (*(code *)param_2)(0,0,0);
    puVar1[0xf] = uVar3;
    *(undefined4 *)(param_1 + 0x30) = uVar3;
  }
  return puVar1;
}



/* grim_zlib_tree_build_and_flush @ 10049400 */

void __cdecl grim_zlib_tree_build_and_flush(uint *param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  uint uVar10;
  uint *local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint *local_20;
  void *local_1c;
  void *local_18;
  uInt local_14;
  uInt local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  puVar3 = param_1;
  local_30 = (uint *)*param_2;
  local_2c = param_2[1];
  local_28 = param_1[8];
  puVar7 = (uint *)param_1[7];
  puVar8 = (uint *)param_1[0xd];
  if (puVar8 < (uint *)param_1[0xc]) {
    local_24 = (int)param_1[0xc] + (-1 - (int)puVar8);
    param_1 = puVar8;
  }
  else {
    local_24 = param_1[0xb] - (int)puVar8;
    param_1 = puVar8;
  }
switchD_100494b1_default:
  uVar10 = local_28;
  switch(*puVar3) {
  case 0:
    goto switchD_1004944d_caseD_0;
  case 1:
    for (; puVar7 < (uint *)0x20; puVar7 = puVar7 + 2) {
      if (local_2c == 0) {
        puVar3[8] = local_28;
        puVar3[7] = (uint)puVar7;
        iVar5 = *param_2;
        param_2[1] = 0;
        *param_2 = (int)local_30;
        param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
        puVar3[0xd] = (uint)param_1;
        grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
        return;
      }
      param_3 = 0;
      local_2c = local_2c - 1;
      local_28 = local_28 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
      local_30 = (uint *)((int)local_30 + 1);
    }
    uVar10 = local_28 & 0xffff;
    if (~local_28 >> 0x10 != uVar10) {
      *puVar3 = 9;
      param_2[6] = (int)s_invalid_stored_block_lengths_100583a4;
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      iVar5 = *param_2;
      *param_2 = (int)local_30;
      param_2[1] = local_2c;
      param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,-3);
      return;
    }
    puVar7 = (uint *)0x0;
    puVar3[1] = uVar10;
    local_28 = 0;
    if (uVar10 != 0) {
      *puVar3 = 2;
      goto switchD_100494b1_default;
    }
    break;
  case 2:
    if (local_2c == 0) {
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      iVar5 = *param_2;
      *param_2 = (int)local_30;
      param_2[1] = 0;
      param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
      return;
    }
    if (local_24 == 0) {
      if (param_1 == (uint *)puVar3[0xb]) {
        puVar8 = (uint *)puVar3[0xc];
        puVar9 = (uint *)puVar3[10];
        if (puVar8 != puVar9) {
          if (puVar9 < puVar8) {
            local_24 = (int)puVar8 + (-1 - (int)puVar9);
          }
          else {
            local_24 = (int)puVar3[0xb] - (int)puVar9;
          }
          param_1 = puVar9;
          if (local_24 != 0) goto LAB_10049676;
        }
      }
      puVar3[0xd] = (uint)param_1;
      iVar5 = grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
      param_1 = (uint *)puVar3[0xd];
      puVar8 = (uint *)puVar3[0xc];
      if (param_1 < puVar8) {
        local_24 = (int)puVar8 + (-1 - (int)param_1);
      }
      else {
        local_24 = puVar3[0xb] - (int)param_1;
      }
      local_20 = (uint *)puVar3[0xb];
      if ((param_1 == local_20) && (puVar9 = (uint *)puVar3[10], puVar8 != puVar9)) {
        param_1 = puVar9;
        if (puVar9 < puVar8) {
          local_24 = (int)puVar8 + (-1 - (int)puVar9);
        }
        else {
          local_24 = (int)local_20 - (int)puVar9;
        }
      }
      if (local_24 == 0) {
        puVar3[8] = local_28;
        puVar3[7] = (uint)puVar7;
        iVar2 = *param_2;
        param_2[1] = local_2c;
        *param_2 = (int)local_30;
        param_2[2] = (int)((int)local_30 + (param_2[2] - iVar2));
        puVar3[0xd] = (uint)param_1;
        grim_zlib_flush_block((int)puVar3,(int)param_2,iVar5);
        return;
      }
    }
LAB_10049676:
    param_3 = 0;
    uVar10 = puVar3[1];
    if (local_2c < puVar3[1]) {
      uVar10 = local_2c;
    }
    if (local_24 < uVar10) {
      uVar10 = local_24;
    }
    puVar8 = local_30;
    puVar9 = param_1;
    for (uVar4 = uVar10 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    local_24 = local_24 - uVar10;
    for (uVar4 = uVar10 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(byte *)puVar9 = (byte)*puVar8;
      puVar8 = (uint *)((int)puVar8 + 1);
      puVar9 = (uint *)((int)puVar9 + 1);
    }
    local_30 = (uint *)((int)local_30 + uVar10);
    uVar4 = puVar3[1];
    local_2c = local_2c - uVar10;
    param_1 = (uint *)((int)param_1 + uVar10);
    puVar3[1] = uVar4 - uVar10;
    if (uVar4 - uVar10 != 0) goto switchD_100494b1_default;
    break;
  case 3:
    for (; puVar7 < (uint *)0xe; puVar7 = puVar7 + 2) {
      if (local_2c == 0) {
        puVar3[8] = local_28;
        puVar3[7] = (uint)puVar7;
        iVar5 = *param_2;
        *param_2 = (int)local_30;
        param_2[1] = 0;
        param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
        puVar3[0xd] = (uint)param_1;
        grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
        return;
      }
      local_2c = local_2c - 1;
      param_3 = 0;
      local_28 = local_28 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
      local_30 = (uint *)((int)local_30 + 1);
    }
    puVar3[1] = local_28 & 0x3fff;
    if ((0x1d < (local_28 & 0x1f)) || (0x3a0 < (local_28 & 0x3e0))) {
      *puVar3 = 9;
      param_2[6] = (int)s_too_many_length_or_distance_symb_10058380;
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      iVar5 = *param_2;
      param_2[1] = local_2c;
      *param_2 = (int)local_30;
      param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,-3);
      return;
    }
    uVar10 = (*(code *)param_2[8])
                       (param_2[10],((local_28 & 0x3fff) >> 5 & 0x1f) + 0x102 + (local_28 & 0x1f),4)
    ;
    puVar3[3] = uVar10;
    if (uVar10 == 0) {
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      iVar5 = *param_2;
      param_2[1] = local_2c;
      *param_2 = (int)local_30;
      param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,-4);
      return;
    }
    local_28 = local_28 >> 0xe;
    puVar7 = (uint *)((int)puVar7 - 0xe);
    puVar3[2] = 0;
    *puVar3 = 4;
    goto LAB_1004979d;
  case 4:
LAB_1004979d:
    if (puVar3[2] < (puVar3[1] >> 10) + 4) {
      do {
        for (; puVar7 < (uint *)0x3; puVar7 = puVar7 + 2) {
          if (local_2c == 0) {
            puVar3[8] = local_28;
            puVar3[7] = (uint)puVar7;
            iVar5 = *param_2;
            *param_2 = (int)local_30;
            param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
            param_2[1] = 0;
            puVar3[0xd] = (uint)param_1;
            grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
            return;
          }
          local_2c = local_2c - 1;
          param_3 = 0;
          local_28 = local_28 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
          local_30 = (uint *)((int)local_30 + 1);
        }
        uVar10 = local_28 & 7;
        puVar7 = (uint *)((int)puVar7 - 3);
        local_28 = local_28 >> 3;
        *(uint *)(puVar3[3] + *(int *)(&DAT_10051454 + puVar3[2] * 4) * 4) = uVar10;
        uVar10 = puVar3[2];
        puVar3[2] = uVar10 + 1;
      } while (uVar10 + 1 < (puVar3[1] >> 10) + 4);
    }
    uVar10 = puVar3[2];
    while (uVar10 < 0x13) {
      *(undefined4 *)(puVar3[3] + *(int *)(&DAT_10051454 + puVar3[2] * 4) * 4) = 0;
      uVar10 = puVar3[2] + 1;
      puVar3[2] = uVar10;
    }
    puVar3[4] = 7;
    iVar5 = grim_zlib_build_bl_tree((int *)puVar3[3],puVar3 + 4,puVar3 + 5,puVar3[9],(int)param_2);
    uVar10 = local_28;
    if (iVar5 == 0) {
      puVar3[2] = 0;
      *puVar3 = 5;
LAB_10049886:
      if (puVar3[2] < (puVar3[1] >> 5 & 0x1f) + 0x102 + (puVar3[1] & 0x1f)) {
        do {
          for (; puVar7 < (uint *)puVar3[4]; puVar7 = puVar7 + 2) {
            if (local_2c == 0) goto LAB_10049e69;
            local_2c = local_2c - 1;
            param_3 = 0;
            uVar10 = uVar10 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
            local_30 = (uint *)((int)local_30 + 1);
          }
          bVar1 = *(byte *)(puVar3[5] + 1 +
                           (*(uint *)(&DAT_10059608 + (int)puVar3[4] * 4) & uVar10) * 8);
          uVar4 = (uint)bVar1;
          local_c = *(uint *)(puVar3[5] +
                              (*(uint *)(&DAT_10059608 + (int)puVar3[4] * 4) & uVar10) * 8 + 4);
          if (local_c < 0x10) {
            puVar7 = (uint *)((int)puVar7 - uVar4);
            uVar10 = uVar10 >> (bVar1 & 0x1f);
            *(uint *)(puVar3[3] + puVar3[2] * 4) = local_c;
            uVar4 = puVar3[2] + 1;
          }
          else {
            local_24 = 7;
            if (local_c != 0x12) {
              local_24 = local_c - 0xe;
            }
            local_20 = (uint *)(local_24 + uVar4);
            for (; puVar7 < local_20; puVar7 = puVar7 + 2) {
              if (local_2c == 0) {
LAB_10049e69:
                puVar3[8] = uVar10;
                puVar3[7] = (uint)puVar7;
                iVar5 = *param_2;
                *param_2 = (int)local_30;
                param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
                param_2[1] = 0;
                puVar3[0xd] = (uint)param_1;
                grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
                return;
              }
              local_2c = local_2c - 1;
              param_3 = 0;
              uVar10 = uVar10 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
              local_30 = (uint *)((int)local_30 + 1);
            }
            uVar10 = uVar10 >> (bVar1 & 0x1f);
            local_28 = (-(uint)(local_c != 0x12) & 0xfffffff8) + 0xb +
                       (*(uint *)(&DAT_10059608 + local_24 * 4) & uVar10);
            uVar10 = uVar10 >> ((byte)local_24 & 0x1f);
            puVar7 = (uint *)((int)puVar7 - (local_24 + uVar4));
            local_24 = puVar3[2];
            if ((puVar3[1] >> 5 & 0x1f) + 0x102 + (puVar3[1] & 0x1f) < local_28 + local_24) {
LAB_10049ea8:
              (*(code *)param_2[9])(param_2[10],puVar3[3]);
              *puVar3 = 9;
              param_2[6] = (int)s_invalid_bit_length_repeat_10058364;
              puVar3[8] = uVar10;
              puVar3[7] = (uint)puVar7;
              iVar5 = *param_2;
              param_2[1] = local_2c;
              *param_2 = (int)local_30;
              param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
              puVar3[0xd] = (uint)param_1;
              grim_zlib_flush_block((int)puVar3,(int)param_2,-3);
              return;
            }
            uVar4 = local_24;
            if (local_c == 0x10) {
              if (local_24 == 0) goto LAB_10049ea8;
              uVar6 = *(undefined4 *)((puVar3[3] - 4) + local_24 * 4);
            }
            else {
              uVar6 = 0;
            }
            do {
              uVar4 = uVar4 + 1;
              *(undefined4 *)((puVar3[3] - 4) + uVar4 * 4) = uVar6;
              local_28 = local_28 + -1;
            } while (local_28 != 0);
          }
          puVar3[2] = uVar4;
        } while (puVar3[2] < (puVar3[1] >> 5 & 0x1f) + 0x102 + (puVar3[1] & 0x1f));
      }
      puVar3[5] = 0;
      local_20 = (uint *)0x9;
      local_24 = 6;
      local_28 = grim_zlib_inflate_trees_dynamic((puVar3[1] & 0x1f) + 0x101,(puVar3[1] >> 5 & 0x1f) + 1,
                              (int *)puVar3[3],(uint *)&local_20,&local_24,&local_4,&local_8,
                              puVar3[9],(int)param_2);
      (*(code *)param_2[9])(param_2[10],puVar3[3]);
      if (local_28 == 0) {
        uVar4 = grim_zlib_stored_block_header((char)local_20,(char)local_24,local_4,local_8,(int)param_2);
        if (uVar4 == 0) {
          puVar3[8] = uVar10;
          puVar3[7] = (uint)puVar7;
          param_2[1] = local_2c;
          param_2[2] = (int)((int)local_30 + (param_2[2] - *param_2));
          *param_2 = (int)local_30;
          puVar3[0xd] = (uint)param_1;
          grim_zlib_flush_block((int)puVar3,(int)param_2,-4);
          return;
        }
        puVar3[1] = uVar4;
        *puVar3 = 6;
LAB_10049ad6:
        puVar3[8] = uVar10;
        puVar3[7] = (uint)puVar7;
        iVar5 = *param_2;
        param_2[1] = local_2c;
        *param_2 = (int)local_30;
        param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
        puVar3[0xd] = (uint)param_1;
        iVar5 = grim_zlib_block_compress((uint)puVar3,param_2,param_3);
        if (iVar5 == 1) {
          param_3 = 0;
          grim_zlib_tree_process(puVar3[1],(int)param_2);
          local_28 = puVar3[8];
          param_1 = (uint *)puVar3[0xd];
          local_30 = (uint *)*param_2;
          local_2c = param_2[1];
          puVar7 = (uint *)puVar3[7];
          if (param_1 < (uint *)puVar3[0xc]) {
            local_24 = (int)puVar3[0xc] + (-1 - (int)param_1);
          }
          else {
            local_24 = puVar3[0xb] - (int)param_1;
          }
          if (puVar3[6] == 0) {
            *puVar3 = 0;
            goto switchD_100494b1_default;
          }
          *puVar3 = 7;
LAB_10049f98:
          puVar3[0xd] = (uint)param_1;
          iVar5 = grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
          param_1 = (uint *)puVar3[0xd];
          if ((uint *)puVar3[0xc] == param_1) {
            *puVar3 = 8;
LAB_10049fff:
            puVar3[8] = local_28;
            puVar3[7] = (uint)puVar7;
            param_2[1] = local_2c;
            param_2[2] = (int)((int)local_30 + (param_2[2] - *param_2));
            *param_2 = (int)local_30;
            puVar3[0xd] = (uint)param_1;
            grim_zlib_flush_block((int)puVar3,(int)param_2,1);
            return;
          }
          puVar3[7] = (uint)puVar7;
          puVar3[8] = local_28;
          iVar2 = *param_2;
          param_2[1] = local_2c;
          *param_2 = (int)local_30;
          param_2[2] = (int)((int)local_30 + (param_2[2] - iVar2));
          puVar3[0xd] = (uint)param_1;
        }
        grim_zlib_flush_block((int)puVar3,(int)param_2,iVar5);
        return;
      }
    }
    else {
      (*(code *)param_2[9])(param_2[10],puVar3[3]);
      local_28 = iVar5;
    }
    if (local_28 == -3) {
      *puVar3 = 9;
    }
    puVar3[8] = uVar10;
    puVar3[7] = (uint)puVar7;
    iVar5 = *param_2;
    param_2[1] = local_2c;
    *param_2 = (int)local_30;
    param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
    puVar3[0xd] = (uint)param_1;
    grim_zlib_flush_block((int)puVar3,(int)param_2,local_28);
    return;
  case 5:
    goto LAB_10049886;
  case 6:
    goto LAB_10049ad6;
  case 7:
    goto LAB_10049f98;
  case 8:
    goto LAB_10049fff;
  case 9:
    puVar3[8] = local_28;
    puVar3[7] = (uint)puVar7;
    iVar5 = *param_2;
    param_2[1] = local_2c;
    *param_2 = (int)local_30;
    param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
    puVar3[0xd] = (uint)param_1;
    grim_zlib_flush_block((int)puVar3,(int)param_2,-3);
    return;
  default:
    puVar3[8] = local_28;
    puVar3[7] = (uint)puVar7;
    iVar5 = *param_2;
    param_2[1] = local_2c;
    *param_2 = (int)local_30;
    param_2[2] = (int)((int)local_30 + (param_2[2] - iVar5));
    puVar3[0xd] = (uint)param_1;
    grim_zlib_flush_block((int)puVar3,(int)param_2,-2);
    return;
  }
  *puVar3 = -(uint)(puVar3[6] != 0) & 7;
  goto switchD_100494b1_default;
switchD_1004944d_caseD_0:
  for (; puVar7 < (uint *)0x3; puVar7 = puVar7 + 2) {
    if (local_2c == 0) {
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      param_2[1] = 0;
      param_2[2] = (int)((int)local_30 + (param_2[2] - *param_2));
      *param_2 = (int)local_30;
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,param_3);
      return;
    }
    local_2c = local_2c - 1;
    param_3 = 0;
    local_28 = local_28 | (uint)(byte)*local_30 << ((byte)puVar7 & 0x1f);
    local_30 = (uint *)((int)local_30 + 1);
  }
  puVar3[6] = local_28 & 1;
  switch((local_28 & 7) >> 1) {
  case 0:
    *puVar3 = 1;
    uVar10 = (int)puVar7 - 3U & 7;
    local_28 = (local_28 >> 3) >> (sbyte)uVar10;
    puVar7 = (uint *)(((int)puVar7 - 3U) - uVar10);
    break;
  case 1:
    inflate_trees_fixed(&local_10,&local_14,&local_18,&local_1c,(z_streamp)param_2);
    uVar10 = grim_zlib_stored_block_header((char)local_10,(char)local_14,local_18,local_1c,(int)param_2);
    puVar3[1] = uVar10;
    if (uVar10 == 0) {
      puVar3[8] = local_28;
      puVar3[7] = (uint)puVar7;
      param_2[1] = local_2c;
      param_2[2] = (int)((int)local_30 + (param_2[2] - *param_2));
      *param_2 = (int)local_30;
      puVar3[0xd] = (uint)param_1;
      grim_zlib_flush_block((int)puVar3,(int)param_2,-4);
      return;
    }
    local_28 = local_28 >> 3;
    puVar7 = (uint *)((int)puVar7 - 3);
    *puVar3 = 6;
    break;
  case 2:
    local_28 = local_28 >> 3;
    puVar7 = (uint *)((int)puVar7 - 3);
    *puVar3 = 3;
    break;
  case 3:
    *puVar3 = 9;
    param_2[6] = (int)s_invalid_block_type_100583c4;
    puVar3[8] = local_28 >> 3;
    puVar3[7] = (int)puVar7 - 3;
    param_2[1] = local_2c;
    param_2[2] = (int)((int)local_30 + (param_2[2] - *param_2));
    *param_2 = (int)local_30;
    puVar3[0xd] = (uint)param_1;
    grim_zlib_flush_block((int)puVar3,(int)param_2,-3);
    return;
  }
  goto switchD_100494b1_default;
}



/* grim_zlib_bit_buffer_flush @ 1004a100 */

undefined4 __cdecl grim_zlib_bit_buffer_flush(int *param_1,int param_2)

{
  int iVar1;
  
  if ((*param_1 == 4) || (*param_1 == 5)) {
    (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1[3]);
  }
  if (*param_1 == 6) {
    grim_zlib_tree_process(param_1[1],param_2);
  }
  param_1[0xd] = param_1[10];
  param_1[0xc] = param_1[10];
  *param_1 = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  if ((code *)param_1[0xe] != (code *)0x0) {
    iVar1 = (*(code *)param_1[0xe])(0,0,0);
    param_1[0xf] = iVar1;
    *(int *)(param_2 + 0x30) = iVar1;
  }
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1[10]);
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1[9]);
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1);
  return 0;
}



/* grim_zlib_stored_block_header @ 1004a190 */

void __cdecl
grim_zlib_stored_block_header(undefined1 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,int param_5
            )

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)(param_5 + 0x20))(*(undefined4 *)(param_5 + 0x28),1,0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    *(undefined1 *)(puVar1 + 4) = param_1;
    *(undefined1 *)((int)puVar1 + 0x11) = param_2;
    *puVar1 = 0;
    puVar1[5] = param_3;
    puVar1[6] = param_4;
  }
  return;
}



/* grim_zlib_block_compress @ 1004a1d0 */

void __cdecl grim_zlib_block_compress(uint param_1,int *param_2,int param_3)

{
  byte bVar1;
  int *piVar2;
  undefined1 *puVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  uint uVar10;
  byte *pbVar11;
  undefined1 *local_c;
  byte *local_8;
  undefined1 *local_4;
  
  piVar5 = param_2;
  uVar4 = param_1;
  piVar2 = *(int **)(param_1 + 4);
  pbVar11 = (byte *)*param_2;
  uVar10 = *(uint *)(param_1 + 0x1c);
  puVar9 = *(undefined1 **)(param_1 + 0x34);
  if (puVar9 < *(undefined1 **)(param_1 + 0x30)) {
    local_c = *(undefined1 **)(param_1 + 0x30) + (-1 - (int)puVar9);
    param_1 = *(uint *)(param_1 + 0x20);
    param_2 = (int *)param_2[1];
  }
  else {
    local_c = (undefined1 *)(*(int *)(param_1 + 0x2c) - (int)puVar9);
    param_1 = *(uint *)(param_1 + 0x20);
    param_2 = (int *)param_2[1];
  }
  do {
    switch(*piVar2) {
    case 0:
      if (((undefined1 *)0x101 < local_c) && ((int *)0x9 < param_2)) {
        *(uint *)(uVar4 + 0x20) = param_1;
        *(uint *)(uVar4 + 0x1c) = uVar10;
        iVar6 = *piVar5;
        piVar5[1] = (int)param_2;
        *piVar5 = (int)pbVar11;
        piVar5[2] = (int)(pbVar11 + (piVar5[2] - iVar6));
        *(undefined1 **)(uVar4 + 0x34) = puVar9;
        param_3 = grim_zlib_inflate_fast((uint)*(byte *)(piVar2 + 4),(uint)*(byte *)((int)piVar2 + 0x11),
                               piVar2[5],piVar2[6],uVar4,piVar5);
        param_2 = (int *)piVar5[1];
        param_1 = *(uint *)(uVar4 + 0x20);
        pbVar11 = (byte *)*piVar5;
        uVar10 = *(uint *)(uVar4 + 0x1c);
        puVar9 = *(undefined1 **)(uVar4 + 0x34);
        if (puVar9 < *(undefined1 **)(uVar4 + 0x30)) {
          local_c = *(undefined1 **)(uVar4 + 0x30) + (-1 - (int)puVar9);
        }
        else {
          local_c = (undefined1 *)(*(int *)(uVar4 + 0x2c) - (int)puVar9);
        }
        if (param_3 != 0) {
          *piVar2 = (-(uint)(param_3 != 1) & 2) + 7;
          break;
        }
      }
      *piVar2 = 1;
      piVar2[3] = (uint)*(byte *)(piVar2 + 4);
      piVar2[2] = piVar2[5];
    case 1:
      for (; uVar10 < (uint)piVar2[3]; uVar10 = uVar10 + 8) {
        if (param_2 == (int *)0x0) {
LAB_1004a779:
          *(uint *)(uVar4 + 0x1c) = uVar10;
          *(uint *)(uVar4 + 0x20) = param_1;
          iVar6 = *piVar5;
          piVar5[1] = 0;
          *piVar5 = (int)pbVar11;
          piVar5[2] = (int)(pbVar11 + (piVar5[2] - iVar6));
          *(undefined1 **)(uVar4 + 0x34) = puVar9;
          grim_zlib_flush_block(uVar4,(int)piVar5,param_3);
          return;
        }
        param_2 = (int *)((int)param_2 + -1);
        param_3 = 0;
        param_1 = param_1 | (uint)*pbVar11 << ((byte)uVar10 & 0x1f);
        pbVar11 = pbVar11 + 1;
      }
      local_8 = (byte *)(piVar2[2] + (*(uint *)(&DAT_10059608 + piVar2[3] * 4) & param_1) * 8);
      param_1 = param_1 >> (local_8[1] & 0x1f);
      uVar10 = uVar10 - local_8[1];
      bVar1 = *local_8;
      uVar7 = (uint)bVar1;
      if (uVar7 == 0) {
        piVar2[2] = *(int *)(local_8 + 4);
        *piVar2 = 6;
      }
      else if ((bVar1 & 0x10) == 0) {
        if ((bVar1 & 0x40) == 0) {
LAB_1004a3a4:
          piVar2[3] = uVar7;
          piVar2[2] = (int)(local_8 + *(int *)(local_8 + 4) * 8);
        }
        else {
          if ((bVar1 & 0x20) == 0) {
            *piVar2 = 9;
            piVar5[6] = (int)s_invalid_literal_length_code_100583f0;
LAB_1004a7c5:
            *(uint *)(uVar4 + 0x20) = param_1;
            *(uint *)(uVar4 + 0x1c) = uVar10;
            piVar5[1] = (int)param_2;
            piVar5[2] = (int)(pbVar11 + (piVar5[2] - *piVar5));
            *piVar5 = (int)pbVar11;
            *(undefined1 **)(uVar4 + 0x34) = puVar9;
            grim_zlib_flush_block(uVar4,(int)piVar5,-3);
            return;
          }
          *piVar2 = 7;
        }
      }
      else {
        piVar2[2] = bVar1 & 0xf;
        iVar6 = *(int *)(local_8 + 4);
        *piVar2 = 2;
        piVar2[1] = iVar6;
      }
      break;
    case 2:
      uVar7 = piVar2[2];
      for (; uVar10 < uVar7; uVar10 = uVar10 + 8) {
        if (param_2 == (int *)0x0) goto LAB_1004a779;
        param_2 = (int *)((int)param_2 + -1);
        param_3 = 0;
        param_1 = param_1 | (uint)*pbVar11 << ((byte)uVar10 & 0x1f);
        pbVar11 = pbVar11 + 1;
      }
      piVar2[1] = piVar2[1] + (*(uint *)(&DAT_10059608 + uVar7 * 4) & param_1);
      param_1 = param_1 >> ((byte)uVar7 & 0x1f);
      uVar10 = uVar10 - uVar7;
      *piVar2 = 3;
      piVar2[3] = (uint)*(byte *)((int)piVar2 + 0x11);
      piVar2[2] = piVar2[6];
    case 3:
      for (; uVar10 < (uint)piVar2[3]; uVar10 = uVar10 + 8) {
        if (param_2 == (int *)0x0) goto LAB_1004a779;
        param_2 = (int *)((int)param_2 + -1);
        param_3 = 0;
        param_1 = param_1 | (uint)*pbVar11 << ((byte)uVar10 & 0x1f);
        pbVar11 = pbVar11 + 1;
      }
      local_8 = (byte *)(piVar2[2] + (*(uint *)(&DAT_10059608 + piVar2[3] * 4) & param_1) * 8);
      param_1 = param_1 >> (local_8[1] & 0x1f);
      uVar10 = uVar10 - local_8[1];
      bVar1 = *local_8;
      uVar7 = (uint)bVar1;
      if ((bVar1 & 0x10) == 0) {
        if ((bVar1 & 0x40) != 0) {
          *piVar2 = 9;
          piVar5[6] = (int)s_invalid_distance_code_100583d8;
          goto LAB_1004a7c5;
        }
        goto LAB_1004a3a4;
      }
      piVar2[2] = bVar1 & 0xf;
      iVar6 = *(int *)(local_8 + 4);
      *piVar2 = 4;
      piVar2[3] = iVar6;
      break;
    case 4:
      uVar7 = piVar2[2];
      for (; uVar10 < uVar7; uVar10 = uVar10 + 8) {
        if (param_2 == (int *)0x0) goto LAB_1004a779;
        param_2 = (int *)((int)param_2 + -1);
        param_3 = 0;
        param_1 = param_1 | (uint)*pbVar11 << ((byte)uVar10 & 0x1f);
        pbVar11 = pbVar11 + 1;
      }
      piVar2[3] = piVar2[3] + (*(uint *)(&DAT_10059608 + uVar7 * 4) & param_1);
      param_1 = param_1 >> ((byte)uVar7 & 0x1f);
      uVar10 = uVar10 - uVar7;
      *piVar2 = 5;
    case 5:
      if ((uint)((int)puVar9 - *(int *)(uVar4 + 0x28)) < (uint)piVar2[3]) {
        iVar6 = (*(int *)(uVar4 + 0x2c) - *(int *)(uVar4 + 0x28)) - piVar2[3];
      }
      else {
        iVar6 = -piVar2[3];
      }
      local_4 = puVar9 + iVar6;
      iVar6 = piVar2[1];
      while (iVar6 != 0) {
        puVar8 = puVar9;
        if (local_c == (undefined1 *)0x0) {
          if (puVar9 == *(undefined1 **)(uVar4 + 0x2c)) {
            local_c = *(undefined1 **)(uVar4 + 0x30);
            puVar8 = *(undefined1 **)(uVar4 + 0x28);
            if (local_c != puVar8) {
              if (puVar8 < local_c) {
                local_c = local_c + (-1 - (int)puVar8);
              }
              else {
                local_c = *(undefined1 **)(uVar4 + 0x2c) + -(int)puVar8;
              }
              puVar9 = puVar8;
              if (local_c != (undefined1 *)0x0) goto LAB_1004a65b;
            }
          }
          *(undefined1 **)(uVar4 + 0x34) = puVar9;
          param_3 = grim_zlib_flush_block(uVar4,(int)piVar5,param_3);
          puVar8 = *(undefined1 **)(uVar4 + 0x34);
          puVar9 = *(undefined1 **)(uVar4 + 0x30);
          if (puVar8 < puVar9) {
            local_c = puVar9 + (-1 - (int)puVar8);
          }
          else {
            local_c = (undefined1 *)(*(int *)(uVar4 + 0x2c) - (int)puVar8);
          }
          if ((puVar8 == *(undefined1 **)(uVar4 + 0x2c)) &&
             (puVar3 = *(undefined1 **)(uVar4 + 0x28), puVar9 != puVar3)) {
            puVar8 = puVar3;
            if (puVar3 < puVar9) {
              local_c = puVar9 + (-1 - (int)puVar3);
            }
            else {
              local_c = *(undefined1 **)(uVar4 + 0x2c) + -(int)puVar3;
            }
          }
          if (local_c == (undefined1 *)0x0) goto LAB_1004a7fd;
        }
LAB_1004a65b:
        puVar9 = puVar8 + 1;
        param_3 = 0;
        *puVar8 = *local_4;
        local_4 = local_4 + 1;
        local_c = local_c + -1;
        if (local_4 == *(undefined1 **)(uVar4 + 0x2c)) {
          local_4 = *(undefined1 **)(uVar4 + 0x28);
        }
        iVar6 = piVar2[1] + -1;
        piVar2[1] = iVar6;
      }
      *piVar2 = 0;
      break;
    case 6:
      puVar8 = puVar9;
      if (local_c == (undefined1 *)0x0) {
        if (puVar9 == *(undefined1 **)(uVar4 + 0x2c)) {
          local_c = *(undefined1 **)(uVar4 + 0x30);
          puVar8 = *(undefined1 **)(uVar4 + 0x28);
          if (local_c != puVar8) {
            if (puVar8 < local_c) {
              local_c = local_c + (-1 - (int)puVar8);
            }
            else {
              local_c = *(undefined1 **)(uVar4 + 0x2c) + -(int)puVar8;
            }
            puVar9 = puVar8;
            if (local_c != (undefined1 *)0x0) goto LAB_1004a748;
          }
        }
        *(undefined1 **)(uVar4 + 0x34) = puVar9;
        param_3 = grim_zlib_flush_block(uVar4,(int)piVar5,param_3);
        puVar8 = *(undefined1 **)(uVar4 + 0x34);
        puVar9 = *(undefined1 **)(uVar4 + 0x30);
        if (puVar8 < puVar9) {
          local_c = puVar9 + (-1 - (int)puVar8);
        }
        else {
          local_c = (undefined1 *)(*(int *)(uVar4 + 0x2c) - (int)puVar8);
        }
        if ((puVar8 == *(undefined1 **)(uVar4 + 0x2c)) &&
           (puVar3 = *(undefined1 **)(uVar4 + 0x28), puVar9 != puVar3)) {
          puVar8 = puVar3;
          if (puVar3 < puVar9) {
            local_c = puVar9 + (-1 - (int)puVar3);
          }
          else {
            local_c = *(undefined1 **)(uVar4 + 0x2c) + -(int)puVar3;
          }
        }
        if (local_c == (undefined1 *)0x0) {
LAB_1004a7fd:
          *(uint *)(uVar4 + 0x20) = param_1;
          *(uint *)(uVar4 + 0x1c) = uVar10;
          iVar6 = *piVar5;
          piVar5[1] = (int)param_2;
          *piVar5 = (int)pbVar11;
          piVar5[2] = (int)(pbVar11 + (piVar5[2] - iVar6));
          *(undefined1 **)(uVar4 + 0x34) = puVar8;
          grim_zlib_flush_block(uVar4,(int)piVar5,param_3);
          return;
        }
      }
LAB_1004a748:
      param_3 = 0;
      *puVar8 = (char)piVar2[2];
      puVar9 = puVar8 + 1;
      local_c = local_c + -1;
      *piVar2 = 0;
      break;
    case 7:
      if (7 < uVar10) {
        uVar10 = uVar10 - 8;
        param_2 = (int *)((int)param_2 + 1);
        pbVar11 = pbVar11 + -1;
      }
      *(undefined1 **)(uVar4 + 0x34) = puVar9;
      iVar6 = grim_zlib_flush_block(uVar4,(int)piVar5,param_3);
      puVar9 = *(undefined1 **)(uVar4 + 0x34);
      if (*(undefined1 **)(uVar4 + 0x30) != puVar9) {
        *(uint *)(uVar4 + 0x1c) = uVar10;
        *(uint *)(uVar4 + 0x20) = param_1;
        piVar5[1] = (int)param_2;
        piVar5[2] = (int)(pbVar11 + (piVar5[2] - *piVar5));
        *piVar5 = (int)pbVar11;
        *(undefined1 **)(uVar4 + 0x34) = puVar9;
        grim_zlib_flush_block(uVar4,(int)piVar5,iVar6);
        return;
      }
      *piVar2 = 8;
    case 8:
      goto switchD_1004a21c_caseD_8;
    case 9:
      *(uint *)(uVar4 + 0x20) = param_1;
      *(uint *)(uVar4 + 0x1c) = uVar10;
      piVar5[1] = (int)param_2;
      piVar5[2] = (int)(pbVar11 + (piVar5[2] - *piVar5));
      *piVar5 = (int)pbVar11;
      *(undefined1 **)(uVar4 + 0x34) = puVar9;
      grim_zlib_flush_block(uVar4,(int)piVar5,-3);
      return;
    default:
      *(uint *)(uVar4 + 0x20) = param_1;
      *(uint *)(uVar4 + 0x1c) = uVar10;
      piVar5[1] = (int)param_2;
      piVar5[2] = (int)(pbVar11 + (piVar5[2] - *piVar5));
      *piVar5 = (int)pbVar11;
      *(undefined1 **)(uVar4 + 0x34) = puVar9;
      grim_zlib_flush_block(uVar4,(int)piVar5,-2);
      return;
    }
  } while( true );
switchD_1004a21c_caseD_8:
  *(uint *)(uVar4 + 0x20) = param_1;
  *(uint *)(uVar4 + 0x1c) = uVar10;
  piVar5[1] = (int)param_2;
  piVar5[2] = (int)(pbVar11 + (piVar5[2] - *piVar5));
  *piVar5 = (int)pbVar11;
  *(undefined1 **)(uVar4 + 0x34) = puVar9;
  grim_zlib_flush_block(uVar4,(int)piVar5,1);
  return;
}



/* grim_zlib_tree_process @ 1004a980 */

void __cdecl grim_zlib_tree_process(undefined4 param_1,int param_2)

{
  (**(code **)(param_2 + 0x24))(*(undefined4 *)(param_2 + 0x28),param_1);
  return;
}



/* grim_zlib_build_bl_tree @ 1004a9a0 */

int __cdecl grim_zlib_build_bl_tree(int *param_1,uint *param_2,uint *param_3,int param_4,int param_5)

{
  uint *puVar1;
  int iVar2;
  uint local_4;
  
  local_4 = 0;
  puVar1 = (uint *)(**(code **)(param_5 + 0x20))(*(undefined4 *)(param_5 + 0x28),0x13,4);
  if (puVar1 == (uint *)0x0) {
    return -4;
  }
  iVar2 = grim_zlib_huft_build(param_1,0x13,0x13,0,0,param_3,param_2,param_4,&local_4,puVar1);
  if (iVar2 == -3) {
    *(char **)(param_5 + 0x18) = s_zlib_err_oversubscribed_dynamic;
    (**(code **)(param_5 + 0x24))(*(undefined4 *)(param_5 + 0x28),puVar1);
    return -3;
  }
  if ((iVar2 == -5) || (*param_2 == 0)) {
    *(char **)(param_5 + 0x18) = s_zlib_err_incomplete_dynamic;
    iVar2 = -3;
  }
  (**(code **)(param_5 + 0x24))(*(undefined4 *)(param_5 + 0x28),puVar1);
  return iVar2;
}



/* grim_zlib_huft_build @ 1004aa50 */

undefined4 __cdecl
grim_zlib_huft_build(int *param_1,uint param_2,uint param_3,int param_4,int param_5,uint *param_6,
            uint *param_7,int param_8,uint *param_9,uint *param_10)

{
  undefined4 uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  byte bVar16;
  int iVar17;
  uint uVar18;
  uint local_100;
  uint local_fc;
  int local_f8;
  uint *local_f4;
  int local_f0;
  uint *local_e8;
  undefined4 local_e0;
  uint local_dc;
  uint local_d8;
  uint local_d4;
  uint local_d0;
  uint local_bc [47];
  
  uVar18 = 0;
  local_bc[0] = 0;
  local_bc[1] = 0;
  local_bc[2] = 0;
  local_bc[3] = 0;
  local_bc[4] = 0;
  local_bc[5] = 0;
  local_bc[6] = 0;
  local_bc[7] = 0;
  local_bc[8] = 0;
  local_bc[9] = 0;
  local_bc[10] = 0;
  local_bc[0xb] = 0;
  local_bc[0xc] = 0;
  local_bc[0xd] = 0;
  local_bc[0xe] = 0;
  local_bc[0xf] = 0;
  piVar8 = param_1;
  uVar13 = param_2;
  do {
    iVar17 = *piVar8;
    piVar8 = piVar8 + 1;
    uVar13 = uVar13 - 1;
    local_bc[iVar17] = local_bc[iVar17] + 1;
  } while (uVar13 != 0);
  if (local_bc[0] == param_2) {
    *param_6 = 0;
    *param_7 = 0;
  }
  else {
    local_fc = 1;
    puVar7 = local_bc;
    do {
      puVar7 = puVar7 + 1;
      if (*puVar7 != 0) break;
      local_fc = local_fc + 1;
    } while (local_fc < 0x10);
    local_100 = *param_7;
    if (*param_7 < local_fc) {
      local_100 = local_fc;
    }
    uVar13 = 0xf;
    puVar7 = local_bc + 0xf;
    do {
      if (*puVar7 != 0) break;
      uVar13 = uVar13 - 1;
      puVar7 = puVar7 + -1;
    } while (uVar13 != 0);
    if (uVar13 < local_100) {
      local_100 = uVar13;
    }
    *param_7 = local_100;
    iVar17 = 1 << ((byte)local_fc & 0x1f);
    if (local_fc < uVar13) {
      puVar7 = local_bc + local_fc;
      uVar9 = local_fc;
      do {
        uVar6 = *puVar7;
        if ((int)(iVar17 - uVar6) < 0) {
          return 0xfffffffd;
        }
        uVar9 = uVar9 + 1;
        puVar7 = puVar7 + 1;
        iVar17 = (iVar17 - uVar6) * 2;
      } while (uVar9 < uVar13);
    }
    iVar17 = iVar17 - local_bc[uVar13];
    if (iVar17 < 0) {
      return 0xfffffffd;
    }
    local_bc[0x11] = 0;
    local_bc[uVar13] = local_bc[uVar13] + iVar17;
    iVar10 = 0;
    iVar14 = uVar13 - 1;
    if (iVar14 != 0) {
      iVar4 = 0;
      do {
        iVar10 = iVar10 + *(int *)((int)local_bc + iVar4 + 4);
        iVar14 = iVar14 + -1;
        *(int *)((int)local_bc + iVar4 + 0x48) = iVar10;
        iVar4 = iVar4 + 4;
      } while (iVar14 != 0);
    }
    uVar9 = 0;
    do {
      iVar10 = *param_1;
      param_1 = param_1 + 1;
      if (iVar10 != 0) {
        uVar6 = local_bc[iVar10 + 0x10];
        param_10[uVar6] = uVar9;
        local_bc[iVar10 + 0x10] = uVar6 + 1;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < param_2);
    iVar10 = -local_100;
    uVar9 = local_bc[uVar13 + 0x10];
    local_f4 = param_10;
    local_d8 = 0;
    local_bc[0x10] = 0;
    local_f8 = -1;
    local_bc[0x20] = 0;
    local_d0 = 0;
    local_d4 = 0;
    if ((int)local_fc <= (int)uVar13) {
      local_f0 = local_fc - 1;
      local_e8 = local_bc + local_fc;
      do {
        uVar6 = *local_e8;
        uVar1 = local_e0;
        while (uVar6 != 0) {
          uVar15 = uVar6 - 1;
          local_e0._2_2_ = (undefined2)((uint)uVar1 >> 0x10);
          uVar2 = local_e0._2_2_;
          iVar14 = iVar10;
          while (local_e0 = uVar1, iVar14 = iVar14 + local_100, iVar14 < (int)local_fc) {
            iVar10 = iVar10 + local_100;
            uVar18 = uVar13 - iVar10;
            if (local_100 < uVar13 - iVar10) {
              uVar18 = local_100;
            }
            uVar11 = local_fc - iVar10;
            uVar3 = 1 << ((byte)uVar11 & 0x1f);
            if ((uVar6 < uVar3) &&
               (iVar4 = uVar3 + (-1 - uVar15), puVar7 = local_e8, uVar11 < uVar18)) {
              while (uVar11 = uVar11 + 1, uVar11 < uVar18) {
                uVar3 = puVar7[1];
                uVar5 = iVar4 * 2;
                if (uVar5 < uVar3 || uVar5 - uVar3 == 0) break;
                iVar4 = uVar5 - uVar3;
                puVar7 = puVar7 + 1;
              }
            }
            local_d4 = 1 << ((byte)uVar11 & 0x1f);
            uVar18 = *param_9;
            uVar3 = local_d4 + uVar18;
            if (0x5a0 < uVar3) {
              return 0xfffffffc;
            }
            *param_9 = uVar3;
            local_d0 = param_8 + uVar18 * 8;
            local_bc[local_f8 + 0x21] = local_d0;
            if (local_f8 + 1 == 0) {
              *param_6 = local_d0;
            }
            else {
              local_bc[local_f8 + 0x11] = local_d8;
              local_e0._2_2_ = (undefined2)((uint)local_e0 >> 0x10);
              local_e0._0_2_ = CONCAT11((char)local_100,(byte)uVar11);
              uVar11 = local_d8 >> ((char)iVar10 - (char)local_100 & 0x1fU);
              uVar18 = local_bc[local_f8 + 0x20];
              local_dc = ((int)(local_d0 - uVar18) >> 3) - uVar11;
              *(undefined4 *)(uVar18 + uVar11 * 8) = local_e0;
              *(uint *)(uVar18 + 4 + uVar11 * 8) = local_dc;
            }
            uVar18 = local_d8;
            local_f8 = local_f8 + 1;
            uVar1 = local_e0;
            uVar2 = local_e0._2_2_;
          }
          bVar16 = (byte)iVar10;
          if (local_f4 < param_10 + uVar9) {
            local_dc = *local_f4;
            if (local_dc < param_3) {
              local_e0._0_1_ = (-(local_dc < 0x100) & 0xa0U) + 0x60;
            }
            else {
              iVar14 = (local_dc - param_3) * 4;
              local_e0._0_1_ = *(char *)(iVar14 + param_5) + 'P';
              local_dc = *(uint *)(iVar14 + param_4);
            }
            local_f4 = local_f4 + 1;
          }
          else {
            local_e0._0_1_ = -0x40;
          }
          local_e0 = CONCAT31(CONCAT21(uVar2,(char)local_fc - bVar16),(char)local_e0);
          iVar14 = 1 << ((char)local_fc - bVar16 & 0x1f);
          uVar6 = uVar18 >> (bVar16 & 0x1f);
          if (uVar6 < local_d4) {
            puVar12 = (undefined4 *)(local_d0 + uVar6 * 8);
            do {
              uVar6 = uVar6 + iVar14;
              *puVar12 = local_e0;
              puVar12[1] = local_dc;
              puVar12 = puVar12 + iVar14 * 2;
            } while (uVar6 < local_d4);
          }
          uVar11 = 1 << ((byte)local_f0 & 0x1f);
          uVar6 = uVar18 & uVar11;
          while (uVar6 != 0) {
            uVar18 = uVar18 ^ uVar11;
            uVar11 = uVar11 >> 1;
            uVar6 = uVar18 & uVar11;
          }
          uVar18 = uVar18 ^ uVar11;
          puVar7 = local_bc + local_f8 + 0x10;
          uVar6 = uVar15;
          uVar1 = local_e0;
          local_d8 = uVar18;
          if (((1 << (bVar16 & 0x1f)) - 1U & uVar18) != local_bc[local_f8 + 0x10]) {
            do {
              local_f8 = local_f8 + -1;
              iVar10 = iVar10 - local_100;
              puVar7 = puVar7 + -1;
            } while (((1 << ((byte)iVar10 & 0x1f)) - 1U & uVar18) != *puVar7);
          }
        }
        local_e8 = local_e8 + 1;
        local_fc = local_fc + 1;
        local_f0 = local_f0 + 1;
        local_e0 = uVar1;
      } while ((int)local_fc <= (int)uVar13);
    }
    if ((iVar17 != 0) && (uVar13 != 1)) {
      return 0xfffffffb;
    }
  }
  return 0;
}



/* grim_zlib_inflate_trees_dynamic @ 1004af20 */

int __cdecl
grim_zlib_inflate_trees_dynamic(uint param_1,uint param_2,int *param_3,uint *param_4,uint *param_5,uint *param_6,
            uint *param_7,int param_8,int param_9)

{
  uint *puVar1;
  int iVar2;
  uint local_4;
  
  local_4 = 0;
  puVar1 = (uint *)(**(code **)(param_9 + 0x20))(*(undefined4 *)(param_9 + 0x28),0x120,4);
  if (puVar1 == (uint *)0x0) {
    return -4;
  }
  iVar2 = grim_zlib_huft_build(param_3,param_1,0x101,0x100514d0,0x1005154c,param_6,param_4,param_8,&local_4,
                       puVar1);
  if (iVar2 == 0) {
    if (*param_4 != 0) {
      iVar2 = grim_zlib_huft_build(param_3 + param_1,param_2,0,0x100515c8,0x10051640,param_7,param_5,param_8
                           ,&local_4,puVar1);
      if (iVar2 == 0) {
        if ((*param_5 != 0) || (param_1 < 0x102)) {
          (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
          return 0;
        }
      }
      else {
        if (iVar2 == -3) {
          *(char **)(param_9 + 0x18) = s_zlib_err_oversubscribed_distance;
          (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
          return -3;
        }
        if (iVar2 == -5) {
          *(char **)(param_9 + 0x18) = s_zlib_err_incomplete_distance;
          (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
          return -3;
        }
        if (iVar2 == -4) goto LAB_1004b053;
      }
      *(char **)(param_9 + 0x18) = s_zlib_err_empty_distance;
      iVar2 = -3;
LAB_1004b053:
      (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
      return iVar2;
    }
  }
  else {
    if (iVar2 == -3) {
      *(char **)(param_9 + 0x18) = s_zlib_err_oversubscribed_literal;
      (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
      return -3;
    }
    if (iVar2 == -4) goto LAB_1004b096;
  }
  *(char **)(param_9 + 0x18) = s_zlib_err_incomplete_literal;
  iVar2 = -3;
LAB_1004b096:
  (**(code **)(param_9 + 0x24))(*(undefined4 *)(param_9 + 0x28),puVar1);
  return iVar2;
}



/* inflate_trees_fixed @ 1004b0b0 */

/* zlib (internal): return fixed Huffman trees */

int __cdecl inflate_trees_fixed(uInt *bl,uInt *bd,void **tl,void **td,z_streamp z)

{
  *bl = grim_zlib_fixed_bl;
  *bd = grim_zlib_fixed_bd;
  *tl = &grim_zlib_fixed_tl;
  *td = &grim_zlib_fixed_td;
  return 0;
}



/* grim_zlib_flush_block @ 1004b0e0 */

int __cdecl grim_zlib_flush_block(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *local_4;
  
  puVar4 = *(undefined4 **)(param_1 + 0x34);
  puVar6 = *(undefined4 **)(param_1 + 0x30);
  local_4 = *(undefined4 **)(param_2 + 0xc);
  if (puVar4 < puVar6) {
    puVar4 = *(undefined4 **)(param_1 + 0x2c);
  }
  uVar3 = *(uint *)(param_2 + 0x10);
  uVar5 = (int)puVar4 - (int)puVar6;
  if (uVar3 < (uint)((int)puVar4 - (int)puVar6)) {
    uVar5 = uVar3;
  }
  if ((uVar5 != 0) && (param_3 == -5)) {
    param_3 = 0;
  }
  *(uint *)(param_2 + 0x10) = uVar3 - uVar5;
  *(uint *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + uVar5;
  if (*(code **)(param_1 + 0x38) != (code *)0x0) {
    uVar1 = (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),puVar6,uVar5);
    *(undefined4 *)(param_1 + 0x3c) = uVar1;
    *(undefined4 *)(param_2 + 0x30) = uVar1;
  }
  puVar4 = puVar6;
  puVar7 = local_4;
  for (uVar3 = uVar5 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar7 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar7 = puVar7 + 1;
  }
  puVar2 = (undefined1 *)((int)puVar6 + uVar5);
  for (uVar3 = uVar5 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  local_4 = (undefined4 *)((int)local_4 + uVar5);
  if (puVar2 == *(undefined1 **)(param_1 + 0x2c)) {
    puVar4 = *(undefined4 **)(param_1 + 0x28);
    if (*(undefined1 **)(param_1 + 0x34) == *(undefined1 **)(param_1 + 0x2c)) {
      *(undefined4 **)(param_1 + 0x34) = puVar4;
    }
    uVar5 = *(int *)(param_1 + 0x34) - (int)puVar4;
    uVar3 = *(uint *)(param_2 + 0x10);
    if (uVar3 < uVar5) {
      uVar5 = uVar3;
    }
    if ((uVar5 != 0) && (param_3 == -5)) {
      param_3 = 0;
    }
    *(uint *)(param_2 + 0x10) = uVar3 - uVar5;
    *(uint *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + uVar5;
    if (*(code **)(param_1 + 0x38) != (code *)0x0) {
      uVar1 = (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),puVar4,uVar5);
      *(undefined4 *)(param_1 + 0x3c) = uVar1;
      *(undefined4 *)(param_2 + 0x30) = uVar1;
    }
    puVar6 = puVar4;
    puVar7 = local_4;
    for (uVar3 = uVar5 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    local_4 = (undefined4 *)((int)local_4 + uVar5);
    puVar2 = (undefined1 *)((int)puVar4 + uVar5);
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
  }
  *(undefined4 **)(param_2 + 0xc) = local_4;
  *(undefined1 **)(param_1 + 0x30) = puVar2;
  return param_3;
}



/* grim_zlib_inflate_fast @ 1004b220 */

undefined4 __cdecl
grim_zlib_inflate_fast(uint param_1,int param_2,int param_3,int param_4,int param_5,int *param_6)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  int iVar13;
  uint local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  
  local_10 = *(undefined1 **)(param_5 + 0x34);
  uVar7 = *(uint *)(param_5 + 0x20);
  local_14 = param_6[1];
  pbVar10 = (byte *)*param_6;
  uVar3 = *(uint *)(param_5 + 0x1c);
  if (local_10 < *(undefined1 **)(param_5 + 0x30)) {
    local_c = *(undefined1 **)(param_5 + 0x30) + (-1 - (int)local_10);
  }
  else {
    local_c = (undefined1 *)(*(int *)(param_5 + 0x2c) - (int)local_10);
  }
  uVar6 = *(uint *)(&DAT_10059608 + param_1 * 4);
  uVar5 = *(uint *)(&DAT_10059608 + param_2 * 4);
  do {
    for (; uVar3 < 0x14; uVar3 = uVar3 + 8) {
      local_14 = local_14 - 1;
      uVar7 = uVar7 | (uint)*pbVar10 << ((byte)uVar3 & 0x1f);
      pbVar10 = pbVar10 + 1;
    }
    bVar2 = *(byte *)(param_3 + (uVar6 & uVar7) * 8);
    uVar9 = (uint)bVar2;
    iVar13 = param_3 + (uVar6 & uVar7) * 8;
    if (uVar9 == 0) {
LAB_1004b458:
      uVar7 = uVar7 >> (*(byte *)(iVar13 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar13 + 1);
      *local_10 = *(undefined1 *)(iVar13 + 4);
      local_10 = local_10 + 1;
      local_c = local_c + -1;
    }
    else {
      uVar7 = uVar7 >> (*(byte *)(iVar13 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar13 + 1);
      while ((bVar2 & 0x10) == 0) {
        if ((uVar9 & 0x40) != 0) {
          if ((uVar9 & 0x20) != 0) {
            uVar6 = param_6[1] - local_14;
            if (uVar3 >> 3 < param_6[1] - local_14) {
              uVar6 = uVar3 >> 3;
            }
            *(uint *)(param_5 + 0x20) = uVar7;
            *(uint *)(param_5 + 0x1c) = uVar3 + uVar6 * -8;
            iVar13 = *param_6;
            param_6[1] = uVar6 + local_14;
            *param_6 = (int)pbVar10 - uVar6;
            param_6[2] = param_6[2] + (((int)pbVar10 - uVar6) - iVar13);
            *(undefined1 **)(param_5 + 0x34) = local_10;
            return 1;
          }
          uVar5 = param_6[1] - local_14;
          param_6[6] = (int)s_invalid_literal_length_code_100583f0;
          uVar6 = uVar3 >> 3;
          if (uVar3 >> 3 < uVar5) goto LAB_1004b56f;
          goto LAB_1004b571;
        }
        iVar4 = (*(uint *)(&DAT_10059608 + uVar9 * 4) & uVar7) + *(int *)(iVar13 + 4);
        bVar2 = *(byte *)(iVar13 + iVar4 * 8);
        uVar9 = (uint)bVar2;
        iVar13 = iVar13 + iVar4 * 8;
        if (uVar9 == 0) goto LAB_1004b458;
        uVar7 = uVar7 >> (*(byte *)(iVar13 + 1) & 0x1f);
        uVar3 = uVar3 - *(byte *)(iVar13 + 1);
      }
      uVar9 = uVar9 & 0xf;
      param_1 = (*(uint *)(&DAT_10059608 + uVar9 * 4) & uVar7) + *(int *)(iVar13 + 4);
      uVar8 = uVar7 >> (sbyte)uVar9;
      for (uVar3 = uVar3 - uVar9; uVar3 < 0xf; uVar3 = uVar3 + 8) {
        local_14 = local_14 - 1;
        uVar8 = uVar8 | (uint)*pbVar10 << ((byte)uVar3 & 0x1f);
        pbVar10 = pbVar10 + 1;
      }
      iVar13 = param_4 + (uVar5 & uVar8) * 8;
      uVar7 = uVar8 >> (*(byte *)(iVar13 + 1) & 0x1f);
      uVar3 = uVar3 - *(byte *)(iVar13 + 1);
      bVar2 = *(byte *)(param_4 + (uVar5 & uVar8) * 8);
      while ((bVar2 & 0x10) == 0) {
        if ((bVar2 & 0x40) != 0) {
          uVar5 = param_6[1] - local_14;
          param_6[6] = (int)s_invalid_distance_code_100583d8;
          uVar6 = uVar3 >> 3;
          if (uVar3 >> 3 < uVar5) {
LAB_1004b56f:
            uVar5 = uVar6;
          }
LAB_1004b571:
          *(uint *)(param_5 + 0x20) = uVar7;
          *(uint *)(param_5 + 0x1c) = uVar3 + uVar5 * -8;
          iVar13 = *param_6;
          param_6[1] = uVar5 + local_14;
          *param_6 = (int)pbVar10 - uVar5;
          param_6[2] = param_6[2] + (((int)pbVar10 - uVar5) - iVar13);
          *(undefined1 **)(param_5 + 0x34) = local_10;
          return 0xfffffffd;
        }
        iVar4 = (*(uint *)(&DAT_10059608 + (uint)bVar2 * 4) & uVar7) + *(int *)(iVar13 + 4);
        pbVar1 = (byte *)(iVar13 + iVar4 * 8);
        iVar13 = iVar13 + iVar4 * 8;
        uVar7 = uVar7 >> (*(byte *)(iVar13 + 1) & 0x1f);
        uVar3 = uVar3 - *(byte *)(iVar13 + 1);
        bVar2 = *pbVar1;
      }
      uVar9 = bVar2 & 0xf;
      for (; uVar3 < uVar9; uVar3 = uVar3 + 8) {
        local_14 = local_14 - 1;
        uVar7 = uVar7 | (uint)*pbVar10 << ((byte)uVar3 & 0x1f);
        pbVar10 = pbVar10 + 1;
      }
      uVar8 = (*(uint *)(&DAT_10059608 + uVar9 * 4) & uVar7) + *(int *)(iVar13 + 4);
      uVar7 = uVar7 >> (sbyte)uVar9;
      uVar3 = uVar3 - uVar9;
      local_c = local_c + -param_1;
      if ((uint)((int)local_10 - *(int *)(param_5 + 0x28)) < uVar8) {
        uVar8 = (*(int *)(param_5 + 0x28) - (int)local_10) + uVar8;
        puVar12 = (undefined1 *)(*(int *)(param_5 + 0x2c) - uVar8);
        if (uVar8 < param_1) {
          param_1 = param_1 - uVar8;
          do {
            *local_10 = *puVar12;
            local_10 = local_10 + 1;
            puVar12 = puVar12 + 1;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
          puVar12 = *(undefined1 **)(param_5 + 0x28);
        }
      }
      else {
        puVar11 = local_10 + -uVar8;
        *local_10 = *puVar11;
        puVar12 = puVar11 + 2;
        local_10[1] = puVar11[1];
        param_1 = param_1 - 2;
        local_10 = local_10 + 2;
      }
      do {
        *local_10 = *puVar12;
        local_10 = local_10 + 1;
        puVar12 = puVar12 + 1;
        param_1 = param_1 - 1;
      } while (param_1 != 0);
    }
    if ((local_c < (undefined1 *)0x102) || (local_14 < 10)) {
      uVar6 = param_6[1] - local_14;
      if (uVar3 >> 3 < param_6[1] - local_14) {
        uVar6 = uVar3 >> 3;
      }
      *(uint *)(param_5 + 0x20) = uVar7;
      *(uint *)(param_5 + 0x1c) = uVar3 + uVar6 * -8;
      iVar13 = *param_6;
      param_6[1] = uVar6 + local_14;
      *param_6 = (int)pbVar10 - uVar6;
      param_6[2] = param_6[2] + (((int)pbVar10 - uVar6) - iVar13);
      *(undefined1 **)(param_5 + 0x34) = local_10;
      return 0;
    }
  } while( true );
}


