/* grim_is_texture_format_supported @ 100047f0 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* checks device support for a texture format */

int __cdecl grim_is_texture_format_supported(uint format)

{
  HRESULT HVar1;
  
  HVar1 = (*grim_d3d8->lpVtbl->CheckDeviceFormat)
                    (grim_d3d8,grim_adapter_index,grim_device_type,grim_texture_format,0,D3DRTYPE_TEXTURE,
                     format);
  return CONCAT31((int3)((uint)HVar1 >> 8),-1 < HVar1);
}



/* grim_select_texture_format @ 10004830 */

/* chooses the first supported texture format */

int grim_select_texture_format(void)

{
  int iVar1;
  uint3 uVar2;
  
  iVar1 = grim_is_texture_format_supported(0x15);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x15;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x33545844);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x33545844;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x1a);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x1a;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x19);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x19;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x14);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x14;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x16);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x16;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x14);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x14;
    return CONCAT31((int3)((uint)iVar1 >> 8),1);
  }
  iVar1 = grim_is_texture_format_supported(0x17);
  uVar2 = (uint3)((uint)iVar1 >> 8);
  if ((char)iVar1 != '\0') {
    grim_preferred_texture_format = 0x17;
    return CONCAT31(uVar2,1);
  }
  grim_error_text = s_D3D__No_supported_texture_format_10053af4;
  return (uint)uVar2 << 8;
}



/* grim_texture_init @ 10004a50 */

/* allocates/copies texture name and zeroes fields */

void * __thiscall grim_texture_init(void *this,void *texture,char *name)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  
  uVar3 = 0xffffffff;
  pcVar2 = texture;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = operator_new(~uVar3);
  uVar3 = 0xffffffff;
  *(char **)this = pcVar2;
  do {
    pcVar5 = texture;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = (char *)((int)texture + 1);
    cVar1 = *(char *)texture;
    texture = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar2 = pcVar2 + 1;
  }
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined1 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  return this;
}



/* grim_texture_release @ 10004ab0 */

/* releases COM objects and frees texture name */

void __fastcall grim_texture_release(void *texture)

{
  int *piVar1;
  
  piVar1 = *(int **)((int)texture + 4);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  piVar1 = *(int **)((int)texture + 0x14);
  *(undefined4 *)((int)texture + 4) = 0;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
  }
  *(undefined4 *)((int)texture + 0x14) = 0;
  if (*(void **)texture != (void *)0x0) {
    operator_delete(*(void **)texture);
  }
  *(undefined4 *)texture = 0;
  return;
}



/* grim_texture_extension_match @ 10004b00 */

bool __cdecl grim_texture_extension_match(char *param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar2 = 0xffffffff;
  pcVar4 = param_1;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  uVar3 = 0xffffffff;
  pcVar4 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  if ((-1 < (int)(uVar2 - 4)) && (-1 < (int)(uVar3 - 4))) {
    if ((param_1[uVar2 - 4] == param_2[uVar3 - 4]) && (param_1[uVar2 - 3] == param_2[uVar3 - 3])) {
      return param_1[uVar2 - 2] == param_2[uVar3 - 2];
    }
  }
  return false;
}



/* grim_texture_load_lzma_png @ 10004b70 */

/* [binja] char* sub_10004b70(char* arg1, void** arg2, int32_t* arg3, int32_t* arg4) */

char * __cdecl grim_texture_load_lzma_png(char *arg1,void **arg2,int *arg3,int *arg4)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint *in_stack_00000014;
  undefined *local_2a4 [33];
  undefined1 local_220 [64];
  int local_1e0;
  int local_1dc;
  int local_184;
  uint local_180;
  int local_178;
  uint local_168;
  uint local_38;
  uint local_34;
  int *local_30;
  char *local_2c;
  int local_28;
  int local_24;
  int *local_20;
  uint local_1c;
  char *local_18;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_1004b7e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  grim_identity_int((int)local_14);
  local_8 = 0;
  local_18 = (char *)0x0;
  local_20 = (int *)grim_lzma_decompress_auto(arg1,&local_38);
  *arg4 = 0;
  *in_stack_00000014 = 0;
  local_28 = *local_20;
  local_30 = local_20 + 1;
  if (local_30 != (int *)0x0) {
    local_1e0 = grim_png_decompress_init(local_2a4);
    local_2a4[0] = &DAT_10004e90;
    iVar2 = setjmp3(local_220,3,&DAT_1000a8ee,local_8,&FuncInfo_100516e8);
    if (iVar2 == 0) {
      grim_png_stream_init(&local_1e0,0x3d,0x1a8);
      grim_png_data_stream_init((int)&local_1e0,local_30,local_28);
      grim_png_stream_set_transforms(&local_1e0,'\x01');
      grim_png_read_data(&local_1e0);
      uVar7 = local_180 * local_184 * 4 + 0x12;
      *arg3 = uVar7;
      pcVar3 = operator_new(uVar7);
      if (pcVar3 != (char *)0x0) {
        *arg4 = local_184;
        *in_stack_00000014 = local_180;
        local_18 = pcVar3 + 0x12;
        piVar4 = (int *)(**(code **)(local_1dc + 8))(&local_1e0,1,local_178 * local_184,1);
        if (local_168 < local_180) {
          do {
            grim_png_read_chunk(&local_1e0,piVar4,1);
            uVar7 = 0;
            if (*arg4 != 0) {
              iVar2 = 0;
              pcVar5 = pcVar3 + 0x12 + (*in_stack_00000014 - local_168) * *arg4 * 4 + 2;
              do {
                pcVar5[1] = -1;
                uVar7 = uVar7 + 1;
                pcVar1 = (char *)(*piVar4 + iVar2);
                iVar2 = iVar2 + 3;
                *pcVar5 = *pcVar1;
                pcVar5[-1] = *(char *)(*piVar4 + -2 + iVar2);
                pcVar5[-2] = *(char *)(*piVar4 + -1 + iVar2);
                pcVar5 = pcVar5 + 4;
              } while (uVar7 < (uint)*arg4);
            }
          } while (local_168 < local_180);
        }
        local_18 = pcVar3;
        grim_png_read_finish(&local_1e0);
        grim_png_stream_destroy((int)&local_1e0);
        *pcVar3 = '\0';
        pcVar3[1] = '\0';
        pcVar3[2] = '\x02';
        pcVar3[3] = '\0';
        pcVar3[4] = '\0';
        pcVar3[5] = '\0';
        pcVar3[6] = '\0';
        pcVar3[7] = '\0';
        pcVar3[8] = '\0';
        pcVar3[9] = '\0';
        pcVar3[10] = '\0';
        pcVar3[0xb] = '\0';
        *(short *)(pcVar3 + 0xc) = (short)*arg4;
        *(short *)(pcVar3 + 0xe) = (short)*in_stack_00000014;
        local_1c = (uint)*(ushort *)(pcVar3 + 0xe);
        uVar7 = 0;
        local_2c = (char *)(local_28 + 4 + (int)local_20);
        pcVar3[0x10] = ' ';
        pcVar3[0x11] = '\b';
        local_24 = 0;
        iVar2 = 0;
        while (local_1c = local_1c - 1, -1 < (int)local_1c) {
          iVar8 = 0;
          uVar6 = (uint)*(ushort *)(pcVar3 + 0xc);
          if (uVar6 != 0) {
            do {
              if ((int)uVar7 < 1) {
                uVar7 = (uint)(byte)local_2c[iVar2];
                local_24 = iVar2 + 2;
                local_34 = (uint)(byte)local_2c[iVar2 + 1];
                iVar8 = iVar8 + -1;
              }
              else {
                uVar7 = uVar7 - 1;
                pcVar3[(uVar6 * local_1c + iVar8) * 4 + 0x15] = (char)local_34;
              }
              iVar8 = iVar8 + 1;
              uVar6 = (uint)*(ushort *)(pcVar3 + 0xc);
              iVar2 = local_24;
            } while (iVar8 < (int)uVar6);
          }
        }
        if (local_20 != (int *)0x0) {
          operator_delete(local_20);
        }
        local_8 = 0xffffffff;
        grim_noop();
        ExceptionList = local_10;
        return pcVar3;
      }
      local_18 = pcVar3;
      grim_png_stream_destroy((int)&local_1e0);
    }
    else {
      grim_png_stream_destroy((int)&local_1e0);
      if (local_18 != (char *)0x0) {
        operator_delete(local_18);
      }
    }
  }
  local_8 = 0xffffffff;
  grim_noop();
  ExceptionList = local_10;
  return (char *)0x0;
}



/* grim_texture_load_file @ 10004ec0 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* loads texture data from file path */

int __thiscall grim_texture_load_file(void *this,void *texture,ushort *path)

{
  undefined4 *arg14;
  bool bVar1;
  uint in_EAX;
  void **arg2;
  FILE *_File;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint3 uVar5;
  char *pcVar6;
  bool bVar7;
  int iStack_2c;
  void *local_28;
  undefined4 uStack_24;
  int *piStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  
  if (texture == (void *)0x0) {
    return in_EAX & 0xffffff00;
  }
  piVar3 = *(int **)((int)this + 4);
  arg14 = (undefined4 *)((int)this + 4);
  local_28 = this;
  if (piVar3 != (int *)0x0) {
    (**(code **)(*piVar3 + 8))(piVar3);
  }
  *arg14 = 0;
  pcVar6 = (char *)0x0;
  bVar7 = false;
  if (grim_string_table_loaded != '\0') {
    pcVar6 = (char *)grim_string_table_lookup_str(texture);
    bVar7 = pcVar6 != (char *)0x0;
  }
  bVar1 = grim_texture_extension_match(texture,&DAT_10053b20);
  if (!bVar1) {
    if ((grim_string_table_loaded != '\0') && (bVar7)) {
      piVar3 = (int *)grim_string_table_lookup_int(texture);
      iVar4 = grim_texture_create_from_memory((int **)grim_d3d_device,pcVar6,piVar3,-1,-1,1,0,
                           grim_preferred_texture_format,1,-1,(int **)0xffffffff,0,(int)&uStack_1c,0
                           ,(int)arg14);
      uVar5 = (uint3)((uint)iVar4 >> 8);
      if (-1 < iVar4) {
        *(undefined4 *)((int)this + 0xc) = uStack_1c;
        *(undefined4 *)((int)this + 0x10) = uStack_18;
        return CONCAT31(uVar5,1);
      }
      *arg14 = 0;
      return (uint)uVar5 << 8;
    }
    uVar2 = grim_d3d_texture_create_from_file((int **)grim_d3d_device,texture,-1,-1,1,0,grim_preferred_texture_format,1,
                         -1,(int **)0xffffffff,0,(int)&uStack_1c,0,(int)arg14);
    if (-1 < (int)uVar2) {
      *(undefined4 *)((int)this + 0xc) = uStack_1c;
      *(undefined4 *)((int)this + 0x10) = uStack_18;
      return CONCAT31((int3)((uint)uStack_1c >> 8),1);
    }
    *arg14 = 0;
    return uVar2 & 0xffffff00;
  }
  if ((grim_string_table_loaded == '\0') || (!bVar7)) {
    _File = fopen(texture,s_file_mode_read_binary);
    if (_File == (FILE *)0x0) {
      return 0;
    }
    fseek(_File,0,2);
    arg2 = (void **)ftell(_File);
    fseek(_File,0,0);
    pcVar6 = operator_new((uint)arg2);
    fread(pcVar6,(size_t)arg2,1,_File);
    fclose(_File);
  }
  else {
    arg2 = (void **)grim_string_table_lookup_int(texture);
  }
  pcVar6 = grim_texture_load_lzma_png(pcVar6,arg2,(int *)&piStack_20,&iStack_2c);
  uVar2 = 0;
  if (pcVar6 != (char *)0x0) {
    *(int *)((int)local_28 + 0xc) = iStack_2c;
    *(undefined4 *)((int)local_28 + 0x10) = uStack_24;
    uVar2 = grim_texture_create_from_memory((int **)grim_d3d_device,pcVar6,piStack_20,-1,-1,1,0,
                         grim_preferred_texture_format,1,-1,(int **)0xffffffff,0,(int)&uStack_1c,0,
                         (int)arg14);
    if ((int)uVar2 < 0) {
      *arg14 = 0;
      return uVar2 & 0xffffff00;
    }
  }
  return CONCAT31((int3)(uVar2 >> 8),1);
}



/* grim_texture_name_equals @ 10005110 */

/* compares stored texture name */

int __thiscall grim_texture_name_equals(void *this,void *texture,char *name)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  bool bVar4;
  
  pbVar2 = *(byte **)this;
  if ((pbVar2 == (byte *)0x0) || (texture == (void *)0x0)) {
    return (uint)pbVar2 & 0xffffff00;
  }
  while( true ) {
    bVar1 = *pbVar2;
    bVar4 = bVar1 < *(byte *)texture;
    if (bVar1 != *(byte *)texture) break;
    if (bVar1 == 0) {
      return 1;
    }
    bVar1 = pbVar2[1];
    bVar4 = bVar1 < *(byte *)((int)texture + 1);
    if (bVar1 != *(byte *)((int)texture + 1)) break;
    pbVar2 = pbVar2 + 2;
    texture = (void *)((int)texture + 2);
    if (bVar1 == 0) {
      return 1;
    }
  }
  iVar3 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
  return CONCAT31((int3)((uint)iVar3 >> 8),iVar3 == 0);
}



/* grim_find_texture_by_name @ 10005170 */

/* returns texture handle index for name */

int __cdecl grim_find_texture_by_name(char *name)

{
  int iVar1;
  int iVar2;
  char *unaff_EDI;
  undefined4 *puVar3;
  
  iVar2 = 0;
  if (0 < grim_texture_slot_max_index + 1) {
    puVar3 = &grim_texture_slots;
    do {
      if ((void *)*puVar3 != (void *)0x0) {
        iVar1 = grim_texture_name_equals((void *)*puVar3,name,unaff_EDI);
        if ((char)iVar1 != '\0') {
          return iVar2;
        }
      }
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < grim_texture_slot_max_index + 1);
  }
  return -1;
}



/* grim_find_free_texture_slot @ 100051c0 */

/* finds the first free texture slot */

int grim_find_free_texture_slot(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &grim_texture_slots;
  do {
    if (*piVar2 == 0) {
      return iVar1;
    }
    piVar2 = piVar2 + 1;
    iVar1 = iVar1 + 1;
  } while ((int)piVar2 < 0x1005d804);
  return -1;
}



/* grim_load_texture_internal @ 100051e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* allocates texture slot and loads file */

int grim_load_texture_internal(char *name,ushort *path)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;
  uint extraout_EAX;
  ushort *unaff_EDI;
  void *local_c;
  undefined *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &DAT_1004b80b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar2 = grim_find_free_texture_slot();
  if (iVar2 == -1) {
    grim_error_text = s_error_texture_slots_full;
    ExceptionList = local_c;
    return -0x100;
  }
  uVar3 = grim_find_texture_by_name(name);
  if (uVar3 != 0xffffffff) {
    grim_error_text = s_error_texture_slot_not_free;
    ExceptionList = local_c;
    return uVar3 & 0xffffff00;
  }
  pvVar4 = operator_new(0x18);
  local_4 = 0;
  if (pvVar4 == (void *)0x0) {
    pvVar4 = (void *)0x0;
  }
  else {
    pvVar4 = grim_texture_init(pvVar4,name,(char *)unaff_EDI);
  }
  local_4 = 0xffffffff;
  uVar3 = grim_texture_load_file(pvVar4,path,unaff_EDI);
  iVar1 = grim_texture_slot_max_index;
  if ((char)uVar3 == '\0') {
    grim_error_text = s_error_texture_load_fail;
    if (pvVar4 != (void *)0x0) {
      grim_texture_release(pvVar4);
      operator_delete(pvVar4);
      uVar3 = extraout_EAX;
    }
    ExceptionList = local_c;
    return uVar3 & 0xffffff00;
  }
  (&grim_texture_slots)[iVar2] = pvVar4;
  if (iVar1 < iVar2) {
    grim_texture_slot_max_index = iVar2;
  }
  ExceptionList = local_c;
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}



/* grim_string_table_load @ 10005a40 */

uint __cdecl grim_string_table_load(char *param_1)

{
  FILE *_File;
  uint extraout_EAX;
  uint uVar1;
  int iVar2;
  
  _File = fopen(param_1,s_file_mode_read_binary);
  if (_File == (FILE *)0x0) {
    grim_string_table_loaded = 0;
    uVar1 = 0;
    if (grim_string_table_data != (void *)0x0) {
      operator_delete(grim_string_table_data);
      uVar1 = extraout_EAX;
    }
    grim_string_table_data = (void *)0x0;
    return uVar1 & 0xffffff00;
  }
  fseek(_File,0,2);
  grim_string_table_size = ftell(_File);
  fseek(_File,0,0);
  grim_string_table_data = operator_new(grim_string_table_size + 1);
  fread(grim_string_table_data,grim_string_table_size,1,_File);
  iVar2 = fclose(_File);
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}



/* grim_string_table_lookup_str @ 10005ae0 */

int __cdecl grim_string_table_lookup_str(byte *param_1)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  bool bVar10;
  
  uVar5 = 0xffffffff;
  pcVar9 = grim_string_table_marker;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  do {
    if (grim_string_table_size <= (int)uVar5) {
      return 0;
    }
    pbVar3 = (byte *)(grim_string_table_data + uVar5);
    uVar6 = 0xffffffff;
    pbVar8 = pbVar3;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    } while (bVar2 != 0);
    iVar7 = ~uVar6 - 1;
    pbVar8 = param_1;
    do {
      bVar2 = *pbVar3;
      bVar10 = bVar2 < *pbVar8;
      if (bVar2 != *pbVar8) {
LAB_10005b41:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_10005b46;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar3[1];
      bVar10 = bVar2 < pbVar8[1];
      if (bVar2 != pbVar8[1]) goto LAB_10005b41;
      pbVar3 = pbVar3 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar2 != 0);
    iVar4 = 0;
LAB_10005b46:
    if (iVar4 == 0) {
      return grim_string_table_data + iVar7 + 5 + uVar5;
    }
    uVar5 = *(int *)(grim_string_table_data + iVar7 + 1 + uVar5) + iVar7 + 5 + uVar5;
  } while( true );
}



/* grim_string_table_lookup_int @ 10005b80 */

undefined4 __cdecl grim_string_table_lookup_int(byte *param_1)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  bool bVar10;
  
  uVar5 = 0xffffffff;
  pcVar9 = grim_string_table_marker;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  do {
    if (grim_string_table_size <= (int)uVar5) {
      return 0;
    }
    pbVar3 = (byte *)(grim_string_table_data + uVar5);
    uVar6 = 0xffffffff;
    pbVar8 = pbVar3;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      bVar2 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    } while (bVar2 != 0);
    iVar7 = ~uVar6 - 1;
    pbVar8 = param_1;
    do {
      bVar2 = *pbVar3;
      bVar10 = bVar2 < *pbVar8;
      if (bVar2 != *pbVar8) {
LAB_10005be1:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_10005be6;
      }
      if (bVar2 == 0) break;
      bVar2 = pbVar3[1];
      bVar10 = bVar2 < pbVar8[1];
      if (bVar2 != pbVar8[1]) goto LAB_10005be1;
      pbVar3 = pbVar3 + 2;
      pbVar8 = pbVar8 + 2;
    } while (bVar2 != 0);
    iVar4 = 0;
LAB_10005be6:
    if (iVar4 == 0) {
      return *(undefined4 *)(grim_string_table_data + iVar7 + 1 + uVar5);
    }
    uVar5 = *(int *)(grim_string_table_data + iVar7 + 1 + uVar5) + iVar7 + 5 + uVar5;
  } while( true );
}



/* grim_set_texture_stage_ops @ 10006030 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* sets D3D texture stage states for a small set of blend modes (mode 0..3) */

uint __cdecl grim_set_texture_stage_ops(uint mode)

{
  HRESULT HVar1;
  
  switch(mode) {
  case 0:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,3);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,3);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 1:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 2:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG2,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAARG2,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 3:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,7);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,7);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG2,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,4);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAARG2,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 4:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,0x18);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,3);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 5:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,0x18);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG2,0);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  case 6:
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLOROP,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,0,D3DTSS_ALPHAOP,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLOROP,0x18);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG1,2);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_COLORARG2,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,1,D3DTSS_ALPHAOP,1);
    (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_COLOROP,1);
    HVar1 = (*grim_d3d_device->lpVtbl->SetTextureStageState)(grim_d3d_device,2,D3DTSS_ALPHAOP,1);
    return CONCAT31((int3)((uint)HVar1 >> 8),1);
  default:
    return mode & 0xffffff00;
  }
}



/* grim_create_texture @ 100075d0 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xac: create blank texture in a free slot */

int grim_create_texture(char *name,int width,int height)

{
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  void *unaff_EDI;
  LPDIRECT3DDEVICE8 name_00;
  undefined4 uVar4;
  void *pvVar5;
  IDirect3DTexture8 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_1004b82b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  uVar1 = grim_find_free_texture_slot();
  if ((int)uVar1 < 0) {
    ExceptionList = local_c;
    return uVar1 & 0xffffff00;
  }
  pvVar5 = (void *)0x1;
  uVar4 = 1;
  name_00 = grim_d3d_device;
  uVar2 = (*grim_d3d_device->lpVtbl->CreateTexture)
                    (grim_d3d_device,width,height,1,1,grim_texture_format,D3DPOOL_DEFAULT,&local_10)
  ;
  if ((int)uVar2 < 0) {
    grim_error_text = s_D3D__Could_not_create_a_texture__10053c18;
    ExceptionList = pvVar5;
    return uVar2 & 0xffffff00;
  }
  pvVar3 = operator_new(0x18);
  if (pvVar3 == (void *)0x0) {
    pvVar3 = (void *)0x0;
  }
  else {
    pvVar3 = grim_texture_init(pvVar3,unaff_EDI,(char *)name_00);
  }
  (&grim_texture_slots)[uVar1] = pvVar3;
  *(undefined4 *)((int)pvVar3 + 4) = uVar4;
  *(undefined1 *)((&grim_texture_slots)[uVar1] + 8) = 1;
  *(int *)((&grim_texture_slots)[uVar1] + 0xc) = width;
  *(int *)((&grim_texture_slots)[uVar1] + 0x10) = height;
  uVar2 = grim_texture_slot_max_index;
  if ((int)grim_texture_slot_max_index < (int)uVar1) {
    grim_texture_slot_max_index = uVar1;
  }
  ExceptionList = pvVar5;
  return CONCAT31((int3)(uVar2 >> 8),1);
}



/* grim_load_texture @ 100076e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xb4 (provisional) */

int grim_load_texture(char *name,char *path)

{
  int iVar1;
  
  iVar1 = grim_load_texture_internal(name,(ushort *)path);
  return iVar1;
}



/* grim_destroy_texture @ 10007700 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xbc (provisional): release texture handle */

void grim_destroy_texture(int handle)

{
  void *texture;
  int iVar1;
  bool bVar2;
  
  texture = (void *)(&grim_texture_slots)[handle];
  if (texture != (void *)0x0) {
    grim_texture_release(texture);
    operator_delete(texture);
    iVar1 = grim_texture_slot_max_index;
    bVar2 = handle == grim_texture_slot_max_index;
    (&grim_texture_slots)[handle] = 0;
    if (bVar2) {
      grim_texture_slot_max_index = iVar1 + -1;
    }
  }
  return;
}



/* grim_get_texture_handle @ 10007740 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xc0: lookup texture handle by name */

int grim_get_texture_handle(char *name)

{
  int iVar1;
  
  iVar1 = grim_find_texture_by_name(name);
  return iVar1;
}



/* grim_validate_texture @ 10007750 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0xb8: validate texture handle/device */

int grim_validate_texture(int handle)

{
  void *pvVar1;
  int in_stack_00000008;
  
  if ((&grim_texture_slots)[handle] == 0) {
    return 0;
  }
  pvVar1 = grim_mipmap_create(in_stack_00000008,2,*(int **)((&grim_texture_slots)[handle] + 4),0);
  return CONCAT31((int3)((uint)pvVar1 >> 8),-1 < (int)pvVar1);
}



/* grim_recreate_texture @ 10007790 */

/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xb0: recreate D3D texture surface */

int grim_recreate_texture(int handle)

{
  uint uVar1;
  int iVar2;
  undefined4 unaff_retaddr;
  
  iVar2 = (&grim_texture_slots)[handle];
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = grim_image_load_from_zip(*(void **)(iVar2 + 0x10),(int **)grim_d3d_device,*(int *)(iVar2 + 0xc),
                       (int)*(void **)(iVar2 + 0x10),1);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  iVar2 = grim_image_load_from_stream((int *)handle,*(int **)((&grim_texture_slots)[handle] + 4),0,0,2.24208e-44);
  if (iVar2 < 0) {
    uVar1 = (**(code **)(*(int *)handle + 8))(handle);
    return uVar1 & 0xffffff00;
  }
  (**(code **)(**(int **)((&grim_texture_slots)[handle] + 4) + 8))
            (*(int **)((&grim_texture_slots)[handle] + 4));
  *(undefined4 *)((&grim_texture_slots)[handle] + 4) = unaff_retaddr;
  return CONCAT31((int3)((uint)unaff_retaddr >> 8),1);
}



/* grim_bind_texture @ 10007830 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0xc4: bind texture handle to stage */

void grim_bind_texture(int handle,int stage)

{
  IDirect3DBaseTexture8 *pTexture;
  
  if (((-1 < handle) && ((&grim_texture_slots)[handle] != 0)) &&
     (pTexture = *(IDirect3DBaseTexture8 **)((&grim_texture_slots)[handle] + 4),
     pTexture != (IDirect3DBaseTexture8 *)0x0)) {
    (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,stage,pTexture);
    _grim_bound_texture_handle = handle;
  }
  return;
}



/* grim_texture_create_ex @ 1000be28 */

undefined4 grim_texture_create_ex(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  int *extraout_ECX;
  uint uVar7;
  int *unaff_EBX;
  uint arg3;
  int unaff_EBP;
  undefined4 uVar8;
  uint *puVar9;
  
  seh_prolog();
  grim_file_stream_init((int *)(unaff_EBP + -0x98));
  *(undefined4 *)(unaff_EBP + -4) = 0;
  if ((*(int *)(unaff_EBP + 8) == 0) || (extraout_ECX == (int *)0x0)) {
    uVar8 = 0x8876086c;
    goto LAB_1000c194;
  }
  iVar2 = (**(code **)(*extraout_ECX + 0x28))(extraout_ECX);
  *(int *)(unaff_EBP + -0x40) = iVar2;
  if (((iVar2 != 3) && (iVar2 != 4)) && (iVar2 != 5)) {
    uVar8 = 0x8876086c;
    goto LAB_1000c194;
  }
  *(int **)(unaff_EBP + -0x24) = extraout_ECX;
  if (*(int *)(unaff_EBP + 0xc) == 4) {
    *(uint *)(unaff_EBP + -0x30) = ((iVar2 != 5) - 1 & 5) + 1;
    iVar3 = (**(code **)(*extraout_ECX + 0x34))(extraout_ECX);
  }
  else {
    iVar3 = 1;
    *(undefined4 *)(unaff_EBP + -0x30) = 1;
  }
  arg3 = iVar3 * *(int *)(unaff_EBP + -0x30);
  puVar9 = (uint *)0x0;
  *(int *)(unaff_EBP + -0x20) = iVar3;
  *(undefined4 *)(unaff_EBP + -0x14) = 0;
  *(undefined4 *)(unaff_EBP + -0x18) = 0;
  *(undefined4 *)(unaff_EBP + -0x2c) = 0;
  *(undefined4 *)(unaff_EBP + -0x34) = 0;
  if (iVar2 == 3) {
LAB_1000becd:
    puVar4 = operator_new(arg3 * 0x10 + 4);
    *(uint **)(unaff_EBP + -0x2c) = puVar4;
    *(undefined1 *)(unaff_EBP + -4) = 1;
    if (puVar4 != (uint *)0x0) {
      puVar9 = puVar4 + 1;
      *puVar4 = arg3;
      grim_crt_buffer_alloc_zeroed((int)puVar9,0x10,arg3,0x10016121);
    }
    *(undefined1 *)(unaff_EBP + -4) = 0;
    *(uint **)(unaff_EBP + -0x2c) = puVar9;
    if (puVar9 != (uint *)0x0) {
      puVar5 = operator_new(arg3 * 4);
      *(undefined4 **)(unaff_EBP + -0x14) = puVar5;
joined_r0x1000bfcb:
      if (puVar5 != (undefined4 *)0x0) {
        for (uVar7 = arg3 & 0x3fffffff; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar5 = 0;
          puVar5 = puVar5 + 1;
        }
        for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined1 *)puVar5 = 0;
          puVar5 = (undefined4 *)((int)puVar5 + 1);
        }
        goto LAB_1000bf39;
      }
    }
LAB_1000c1dc:
    *(undefined4 *)(unaff_EBP + -0x10) = 0x8007000e;
  }
  else {
    if (iVar2 == 4) {
      puVar9 = operator_new(arg3 * 4 + 4);
      *(uint **)(unaff_EBP + -0x34) = puVar9;
      *(undefined1 *)(unaff_EBP + -4) = 2;
      if (puVar9 == (uint *)0x0) {
        puVar4 = (uint *)0x0;
      }
      else {
        puVar4 = puVar9 + 1;
        *puVar9 = arg3;
        grim_crt_buffer_alloc_zeroed((int)puVar4,4,arg3,0x1001619a);
      }
      *(undefined1 *)(unaff_EBP + -4) = 0;
      *(uint **)(unaff_EBP + -0x34) = puVar4;
      if (puVar4 != (uint *)0x0) {
        puVar5 = operator_new(arg3 * 4);
        *(undefined4 **)(unaff_EBP + -0x18) = puVar5;
        goto joined_r0x1000bfcb;
      }
      goto LAB_1000c1dc;
    }
    if (iVar2 == 5) goto LAB_1000becd;
LAB_1000bf39:
    *(int *)(unaff_EBP + -0x38) = unaff_EBP + -0x98;
    *(undefined4 *)(unaff_EBP + -0x1c) = 0;
    if (*(int *)(unaff_EBP + -0x30) != 0) {
      *(undefined4 *)(unaff_EBP + -0x3c) = 0;
      do {
        uVar7 = 0;
        if (*(int *)(unaff_EBP + -0x1c) != 0) {
          piVar6 = operator_new(0x54);
          *(int **)(unaff_EBP + -0x28) = piVar6;
          *(undefined1 *)(unaff_EBP + -4) = 3;
          if (piVar6 == (int *)0x0) {
            piVar6 = (int *)0x0;
          }
          else {
            piVar6 = grim_file_stream_init(piVar6);
          }
          *(undefined1 *)(unaff_EBP + -4) = 0;
          if (piVar6 == (int *)0x0) goto LAB_1000c1dc;
          *(int **)(*(int *)(unaff_EBP + -0x38) + 0x50) = piVar6;
          *(int **)(unaff_EBP + -0x38) = piVar6;
        }
        *(undefined4 *)(unaff_EBP + -0x28) = *(undefined4 *)(unaff_EBP + -0x38);
        if (*(int *)(unaff_EBP + -0x20) != 0) {
          do {
            if (uVar7 != 0) {
              piVar6 = operator_new(0x54);
              *(int **)(unaff_EBP + -0x44) = piVar6;
              *(undefined1 *)(unaff_EBP + -4) = 4;
              if (piVar6 == (int *)0x0) {
                piVar6 = (int *)0x0;
              }
              else {
                piVar6 = grim_file_stream_init(piVar6);
              }
              *(undefined1 *)(unaff_EBP + -4) = 0;
              if (piVar6 == (int *)0x0) goto LAB_1000c1dc;
              *(int **)(*(int *)(unaff_EBP + -0x28) + 0x4c) = piVar6;
              *(int **)(unaff_EBP + -0x28) = piVar6;
            }
            iVar2 = *(int *)(unaff_EBP + -0x3c) + uVar7;
            iVar3 = *(int *)(unaff_EBP + -0x40);
            if (iVar3 == 3) {
              iVar3 = *(int *)(unaff_EBP + -0x14);
LAB_1000c06a:
              uVar8 = (**(code **)(**(int **)(unaff_EBP + -0x24) + 0x3c))
                                (*(int **)(unaff_EBP + -0x24),uVar7,iVar3 + iVar2 * 4);
LAB_1000c078:
              *(undefined4 *)(unaff_EBP + -0x10) = uVar8;
            }
            else {
              if (iVar3 == 4) {
                iVar3 = *(int *)(unaff_EBP + -0x18);
                goto LAB_1000c06a;
              }
              if (iVar3 == 5) {
                uVar8 = (**(code **)(**(int **)(unaff_EBP + -0x24) + 0x3c))
                                  (*(int **)(unaff_EBP + -0x24),*(undefined4 *)(unaff_EBP + -0x1c),
                                   uVar7,*(int *)(unaff_EBP + -0x14) + iVar2 * 4);
                goto LAB_1000c078;
              }
            }
            if (*(int *)(unaff_EBP + -0x10) < 0) goto LAB_1000c117;
            iVar3 = *(int *)(unaff_EBP + -0x40);
            if (iVar3 == 3) {
LAB_1000c097:
              iVar2 = grim_zip_read_header((void *)(iVar2 * 0x10 + *(int *)(unaff_EBP + -0x2c)),
                                   (char *)(unaff_EBP + -0xe4),
                                   *(int **)(*(int *)(unaff_EBP + -0x14) + iVar2 * 4),
                                   *(int **)(unaff_EBP + 0x10),0,(int *)0x0,1,(int)unaff_EBX);
LAB_1000c0ba:
              *(int *)(unaff_EBP + -0x10) = iVar2;
            }
            else {
              if (iVar3 == 4) {
                iVar2 = grim_zip_read_entry((void *)(*(int *)(unaff_EBP + -0x34) + iVar2 * 4),
                                     (int *)(unaff_EBP + -0xe4),
                                     *(int **)(iVar2 * 4 + *(int *)(unaff_EBP + -0x18)),
                                     *(int **)(unaff_EBP + 0x10),0,0,1,(int)unaff_EBX);
                goto LAB_1000c0ba;
              }
              if (iVar3 == 5) goto LAB_1000c097;
            }
            if (*(int *)(unaff_EBP + -0x10) < 0) goto LAB_1000c117;
            iVar2 = grim_file_stream_read_header(*(void **)(unaff_EBP + -0x28),(int *)(unaff_EBP + -0xe4),unaff_EBX)
            ;
            *(int *)(unaff_EBP + -0x10) = iVar2;
            if (iVar2 < 0) goto LAB_1000c117;
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(uint *)(unaff_EBP + -0x20));
        }
        *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + -0x1c) + 1;
        *(int *)(unaff_EBP + -0x3c) = *(int *)(unaff_EBP + -0x3c) + *(int *)(unaff_EBP + -0x20);
      } while (*(uint *)(unaff_EBP + -0x1c) < *(uint *)(unaff_EBP + -0x30));
    }
    iVar2 = grim_alloc_block(*(int **)(unaff_EBP + 8),*(int *)(unaff_EBP + 0xc),
                         *(int *)(unaff_EBP + 0x14),unaff_EBX);
    *(int *)(unaff_EBP + -0x10) = iVar2;
    if (-1 < iVar2) {
      *(undefined4 *)(unaff_EBP + -0x10) = 0;
    }
  }
LAB_1000c117:
  uVar7 = 0;
  if (*(CODBCFieldInfo **)(unaff_EBP + -0x2c) != (CODBCFieldInfo *)0x0) {
    CODBCFieldInfo::_vector_deleting_destructor_(*(CODBCFieldInfo **)(unaff_EBP + -0x2c),3);
  }
  if (*(void **)(unaff_EBP + -0x34) != (void *)0x0) {
    FID_conflict__vector_deleting_destructor_(*(void **)(unaff_EBP + -0x34),3);
  }
  if (*(int *)(unaff_EBP + -0x14) != 0) {
    if (arg3 != 0) {
      do {
        piVar6 = (int *)(*(int *)(unaff_EBP + -0x14) + uVar7 * 4);
        piVar1 = (int *)*piVar6;
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *piVar6 = 0;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < arg3);
    }
    operator_delete(*(void **)(unaff_EBP + -0x14));
  }
  uVar7 = 0;
  if (*(int *)(unaff_EBP + -0x18) != 0) {
    if (arg3 != 0) {
      do {
        piVar6 = (int *)(*(int *)(unaff_EBP + -0x18) + uVar7 * 4);
        piVar1 = (int *)*piVar6;
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          *piVar6 = 0;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < arg3);
    }
    operator_delete(*(void **)(unaff_EBP + -0x18));
  }
  uVar8 = *(undefined4 *)(unaff_EBP + -0x10);
LAB_1000c194:
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_file_stream_close((void *)(unaff_EBP + -0x98));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return uVar8;
}



/* grim_texture_load_internal @ 1000c4e9 */

/* [binja] int32_t sub_1000c4e9(int32_t** arg1, void* arg2, int32_t* arg3, int32_t arg4, int32_t
   arg5, int32_t arg6, int32_t arg7, int32_t arg8, void* arg9, int32_t arg10, int32_t arg11,
   int32_t** arg12) */

int grim_texture_load_internal(int **arg1,void *arg2,int *arg3,int arg4,int arg5,int arg6,int arg7,int arg8,
                void *arg9,int arg10,int arg11,int **arg12)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int *piVar8;
  uint uVar9;
  int unaff_EBP;
  undefined4 *puVar10;
  int *piVar11;
  int unaff_EDI;
  int iVar12;
  undefined4 *puVar13;
  
  seh_prolog();
  piVar8 = *(int **)(unaff_EBP + 0x3c);
  grim_file_stream_init((int *)(unaff_EBP + -0x8c));
  *(undefined4 *)(unaff_EBP + -4) = 0;
  *(undefined4 *)(unaff_EBP + -0x18) = 0;
  *(undefined4 *)(unaff_EBP + -0x14) = 0;
  *(undefined4 *)(unaff_EBP + -0x1c) = 0;
  *(undefined4 *)(unaff_EBP + -0x20) = 0;
  if ((((*(int *)(unaff_EBP + 8) == 0) || (*(int *)(unaff_EBP + 0xc) == 0)) ||
      (*(int *)(unaff_EBP + 0x10) == 0)) || (*(int *)(unaff_EBP + 0x48) == 0)) {
    iVar12 = -0x7789f794;
    goto LAB_1000cb0e;
  }
  if ((piVar8 == (int *)0x0) && (*(int *)(unaff_EBP + 0x44) == -1)) {
    piVar8 = (int *)(unaff_EBP + -0xcc);
  }
  iVar12 = grim_image_detect_format((void *)(unaff_EBP + -0x8c),*(int **)(unaff_EBP + 0xc),
                        *(void **)(unaff_EBP + 0x10),piVar8,(int *)0x1,unaff_EDI);
  if (iVar12 < 0) goto LAB_1000cb0e;
  if (*(int *)(unaff_EBP + 0x44) == -1) {
    *(int *)(unaff_EBP + 0x44) = piVar8[5];
  }
  iVar12 = *(int *)(unaff_EBP + -0x40);
  *(undefined4 *)(unaff_EBP + -0x24) = 1;
  for (; iVar12 != 0; iVar12 = *(int *)(iVar12 + 0x4c)) {
    *(int *)(unaff_EBP + -0x24) = *(int *)(unaff_EBP + -0x24) + 1;
  }
  *(undefined4 *)(unaff_EBP + -0x28) = 1;
  if (*(int *)(unaff_EBP + 0x44) == 5) {
    iVar12 = *(int *)(unaff_EBP + -0x3c);
    if (iVar12 != 0) {
      do {
        iVar12 = *(int *)(iVar12 + 0x50);
        *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x28) + 1;
      } while (iVar12 != 0);
      if (*(int *)(unaff_EBP + -0x28) == 6) goto LAB_1000c5b6;
    }
    iVar12 = -0x7fffbffb;
    goto LAB_1000cb0e;
  }
LAB_1000c5b6:
  if ((*(int *)(unaff_EBP + 0x14) == 0) || (*(int *)(unaff_EBP + 0x14) == -1)) {
    *(undefined4 *)(unaff_EBP + 0x14) = *(undefined4 *)(unaff_EBP + -0x80);
  }
  if ((*(int *)(unaff_EBP + 0x18) == 0) || (*(int *)(unaff_EBP + 0x18) == -1)) {
    *(undefined4 *)(unaff_EBP + 0x18) = *(undefined4 *)(unaff_EBP + -0x7c);
  }
  if ((*(int *)(unaff_EBP + 0x1c) == 0) || (*(int *)(unaff_EBP + 0x1c) == -1)) {
    *(undefined4 *)(unaff_EBP + 0x1c) = *(undefined4 *)(unaff_EBP + -0x78);
  }
  if (*(int *)(unaff_EBP + 0x30) == -1) {
    *(undefined4 *)(unaff_EBP + 0x30) = 0x80004;
  }
  if (*(int *)(unaff_EBP + 0x34) == -1) {
    *(undefined4 *)(unaff_EBP + 0x34) = 5;
  }
  if (*(int *)(unaff_EBP + 0x44) == 5) {
    *(uint *)(unaff_EBP + 0x30) = *(uint *)(unaff_EBP + 0x30) | 0x70000;
    *(uint *)(unaff_EBP + 0x34) = *(uint *)(unaff_EBP + 0x34) | 0x70000;
  }
  if (((*(char *)(unaff_EBP + 0x30) == '\x01') ||
      (uVar7 = *(uint *)(unaff_EBP + 0x34) & 0xff, uVar7 == 2)) ||
     (*(undefined4 *)(unaff_EBP + -0x30) = 0, uVar7 == 5)) {
    *(undefined4 *)(unaff_EBP + -0x30) = 1;
  }
  if (*(int *)(unaff_EBP + 0x28) == 0) {
    iVar12 = *(int *)(unaff_EBP + -0x8c);
    if (*(int *)(unaff_EBP + 0x38) != 0) {
      piVar8 = grim_format_info_lookup(iVar12);
      iVar2 = piVar8[1];
      if ((((iVar2 == 0) || (iVar2 == 1)) || (iVar2 == 2)) && (piVar8[4] == 0)) {
        uVar3 = *(undefined4 *)(unaff_EBP + 0x44);
        uVar4 = *(undefined4 *)(unaff_EBP + 0x24);
        piVar11 = (int *)(unaff_EBP + -0xb0);
        for (iVar12 = 9; iVar12 != 0; iVar12 = iVar12 + -1) {
          *piVar11 = *piVar8;
          piVar8 = piVar8 + 1;
          piVar11 = piVar11 + 1;
        }
        *(undefined4 *)(unaff_EBP + -0xb0) = 0;
        *(undefined4 *)(unaff_EBP + -0xa0) = 1;
        iVar12 = grim_format_find_supported((int *)0x0,uVar4,uVar3,(int *)(unaff_EBP + -0xb0));
        if (iVar12 == 0) {
          iVar12 = *(int *)(unaff_EBP + -0x8c);
        }
      }
    }
    iVar12 = grim_format_convert_fourcc(iVar12);
    *(int *)(unaff_EBP + 0x28) = iVar12;
    if ((*(int *)(unaff_EBP + 0x2c) != 3) && (iVar12 == 0x14)) {
      *(undefined4 *)(unaff_EBP + 0x28) = 0x16;
    }
  }
  iVar12 = *(int *)(unaff_EBP + -0x84);
  if (iVar12 == 0) {
    puVar10 = (undefined4 *)(unaff_EBP + -0x4cc);
    for (iVar12 = 0x100; uVar7 = 0, iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar10 = 0xffffffff;
      puVar10 = puVar10 + 1;
    }
  }
  else {
    uVar9 = *(uint *)(unaff_EBP + 0x38);
    bVar1 = *(byte *)(unaff_EBP + 0x3a);
    uVar7 = 0;
    do {
      uVar5 = *(uint *)(iVar12 + uVar7 * 4);
      *(uint *)(unaff_EBP + -0x4cc + uVar7 * 4) =
           -(uint)(uVar5 != ((uint)bVar1 | (uVar9 & 0xff) << 0x10 | uVar9 & 0xff00ff00)) & uVar5;
      uVar7 = uVar7 + 1;
    } while (uVar7 < 0x100);
    *(undefined4 *)(unaff_EBP + 0x38) = 0;
  }
  if (*(undefined4 **)(unaff_EBP + 0x40) == (undefined4 *)0x0) {
    if (*(int *)(unaff_EBP + 0x28) == 0x28) {
LAB_1000c75c:
      *(undefined4 *)(unaff_EBP + 0x28) = 0x15;
    }
    else if (*(int *)(unaff_EBP + 0x28) == 0x29) {
      *(undefined4 *)(unaff_EBP + 0x28) = 0x16;
      uVar9 = 0;
      do {
        if (*(char *)(unaff_EBP + -0x4c9 + uVar9 * 4) != -1) goto LAB_1000c75c;
        uVar9 = uVar9 + 1;
      } while (uVar9 < 0x100);
    }
  }
  else {
    puVar10 = (undefined4 *)(unaff_EBP + -0x4cc);
    puVar13 = *(undefined4 **)(unaff_EBP + 0x40);
    for (iVar12 = 0x100; iVar12 != 0; iVar12 = iVar12 + -1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    uVar7 = 0;
  }
  if ((*(int *)(unaff_EBP + 0x2c) != 0) ||
     (*(undefined4 *)(unaff_EBP + -0x34) = 1, (*(byte *)(unaff_EBP + 0x25) & 2) != 0)) {
    *(undefined4 *)(unaff_EBP + -0x34) = 0;
  }
  iVar12 = grim_image_check_dimensions(uVar7,*(uint *)(unaff_EBP + 0x24),*(int **)(unaff_EBP + 8),
                        (uint *)(unaff_EBP + 0x14),(uint *)(unaff_EBP + 0x18),
                        (uint *)(unaff_EBP + 0x1c),(uint *)(unaff_EBP + 0x20),
                        (int *)(unaff_EBP + 0x28),*(int *)(unaff_EBP + 0x2c),
                        *(int *)(unaff_EBP + 0x44));
  if (-1 < iVar12) {
    iVar2 = *(int *)(unaff_EBP + 0x44);
    uVar3 = *(undefined4 *)(unaff_EBP + 0x28);
    uVar4 = *(undefined4 *)(unaff_EBP + 0x14);
    if (iVar2 == 3) {
      iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x50))
                         (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x18),
                          *(undefined4 *)(unaff_EBP + 0x20),*(undefined4 *)(unaff_EBP + 0x24),uVar3,
                          *(undefined4 *)(unaff_EBP + 0x2c),unaff_EBP + -0x1c);
    }
    else if (iVar2 == 4) {
      iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x54))
                         (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x18),
                          *(undefined4 *)(unaff_EBP + 0x1c),*(undefined4 *)(unaff_EBP + 0x20),
                          *(undefined4 *)(unaff_EBP + 0x24),uVar3,*(undefined4 *)(unaff_EBP + 0x2c),
                          unaff_EBP + -0x1c);
    }
    else if (iVar2 == 5) {
      iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x58))
                         (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x20),
                          *(undefined4 *)(unaff_EBP + 0x24),uVar3,*(undefined4 *)(unaff_EBP + 0x2c),
                          unaff_EBP + -0x1c);
    }
    if (-1 < iVar12) {
      if (*(int *)(unaff_EBP + -0x34) == 0) {
        piVar8 = *(int **)(unaff_EBP + -0x1c);
      }
      else {
        iVar2 = *(int *)(unaff_EBP + 0x44);
        if (iVar2 == 3) {
          iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x50))
                             (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x18),
                              *(undefined4 *)(unaff_EBP + 0x20),0,uVar3,2,unaff_EBP + -0x20);
        }
        else if (iVar2 == 4) {
          iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x54))
                             (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x18),
                              *(undefined4 *)(unaff_EBP + 0x1c),*(undefined4 *)(unaff_EBP + 0x20),0,
                              uVar3,2,unaff_EBP + -0x20);
        }
        else if (iVar2 == 5) {
          iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x58))
                             (*(int **)(unaff_EBP + 8),uVar4,*(undefined4 *)(unaff_EBP + 0x20),0,
                              uVar3,2,unaff_EBP + -0x20);
        }
        if (iVar12 < 0) goto LAB_1000cacc;
        piVar8 = *(int **)(unaff_EBP + -0x20);
      }
      *(undefined4 *)(unaff_EBP + -0x2c) = 0;
      piVar11 = (int *)(unaff_EBP + -0x8c);
      *(int **)(unaff_EBP + -0x38) = piVar11;
      if (*(int *)(unaff_EBP + -0x28) != 0) {
        do {
          *(undefined4 *)(unaff_EBP + -0x10) = 0;
          if (*(int *)(unaff_EBP + -0x24) != 0) {
            while (*(uint *)(unaff_EBP + -0x10) < *(uint *)(unaff_EBP + 0x20)) {
              iVar2 = *(int *)(unaff_EBP + 0x44);
              if (iVar2 == 3) {
                iVar12 = unaff_EBP + -0x14;
LAB_1000c8eb:
                iVar12 = (**(code **)(*piVar8 + 0x3c))
                                   (piVar8,*(undefined4 *)(unaff_EBP + -0x10),iVar12);
              }
              else {
                if (iVar2 == 4) {
                  iVar12 = unaff_EBP + -0x18;
                  goto LAB_1000c8eb;
                }
                if (iVar2 == 5) {
                  iVar12 = (**(code **)(*piVar8 + 0x3c))
                                     (piVar8,*(undefined4 *)(unaff_EBP + -0x2c),
                                      *(undefined4 *)(unaff_EBP + -0x10),unaff_EBP + -0x14);
                }
              }
              if (iVar12 < 0) goto LAB_1000cacc;
              iVar2 = *(int *)(unaff_EBP + 0x44);
              if (iVar2 == 3) {
LAB_1000c90d:
                iVar12 = grim_image_load_from_memory(*(int **)(unaff_EBP + -0x14),*(int *)(unaff_EBP + 0x40),
                                      (int *)0x0,piVar11[1],*piVar11,piVar11[0xc],unaff_EBP + -0x4cc
                                      ,piVar11 + 6,*(int *)(unaff_EBP + 0x30),
                                      *(int *)(unaff_EBP + 0x38));
              }
              else if (iVar2 == 4) {
                iVar12 = grim_image_load_from_file_ex(*(int **)(unaff_EBP + -0x18),*(int *)(unaff_EBP + 0x40),0,
                                      piVar11[1],*piVar11,piVar11[0xc],piVar11[0xd],
                                      unaff_EBP + -0x4cc,(int)(piVar11 + 6),
                                      *(int *)(unaff_EBP + 0x30),*(int *)(unaff_EBP + 0x38));
              }
              else if (iVar2 == 5) goto LAB_1000c90d;
              if (iVar12 < 0) goto LAB_1000cacc;
              piVar6 = *(int **)(unaff_EBP + -0x18);
              if (piVar6 != (int *)0x0) {
                (**(code **)(*piVar6 + 8))(piVar6);
                *(undefined4 *)(unaff_EBP + -0x18) = 0;
              }
              piVar6 = *(int **)(unaff_EBP + -0x14);
              if (piVar6 != (int *)0x0) {
                (**(code **)(*piVar6 + 8))(piVar6);
                *(undefined4 *)(unaff_EBP + -0x14) = 0;
              }
              *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 1;
              if (*(uint *)(unaff_EBP + -0x24) <= *(uint *)(unaff_EBP + -0x10)) break;
              piVar11 = (int *)piVar11[0x13];
            }
          }
          if ((*(int *)(unaff_EBP + -0x30) == 0) &&
             (*(uint *)(unaff_EBP + -0x10) < *(uint *)(unaff_EBP + 0x20))) {
            do {
              iVar2 = *(int *)(unaff_EBP + 0x44);
              if (iVar2 == 3) {
                iVar12 = unaff_EBP + -0x14;
LAB_1000c9db:
                iVar12 = (**(code **)(*piVar8 + 0x3c))
                                   (piVar8,*(undefined4 *)(unaff_EBP + -0x10),iVar12);
              }
              else {
                if (iVar2 == 4) {
                  iVar12 = unaff_EBP + -0x18;
                  goto LAB_1000c9db;
                }
                if (iVar2 == 5) {
                  iVar12 = (**(code **)(*piVar8 + 0x3c))
                                     (piVar8,*(undefined4 *)(unaff_EBP + -0x2c),
                                      *(undefined4 *)(unaff_EBP + -0x10),unaff_EBP + -0x14);
                }
              }
              if (iVar12 < 0) goto LAB_1000cacc;
              iVar2 = *(int *)(unaff_EBP + 0x44);
              if (iVar2 == 3) {
LAB_1000ca01:
                iVar12 = grim_image_load_from_memory(*(int **)(unaff_EBP + -0x14),*(int *)(unaff_EBP + 0x40),
                                      (int *)0x0,piVar11[1],*piVar11,piVar11[0xc],unaff_EBP + -0x4cc
                                      ,piVar11 + 6,*(int *)(unaff_EBP + 0x30),
                                      *(int *)(unaff_EBP + 0x38));
              }
              else if (iVar2 == 4) {
                iVar12 = grim_image_load_from_file_ex(*(int **)(unaff_EBP + -0x18),*(int *)(unaff_EBP + 0x40),0,
                                      piVar11[1],*piVar11,piVar11[0xc],piVar11[0xd],
                                      unaff_EBP + -0x4cc,(int)(piVar11 + 6),
                                      *(int *)(unaff_EBP + 0x30),*(int *)(unaff_EBP + 0x38));
              }
              else if (iVar2 == 5) goto LAB_1000ca01;
              if (iVar12 < 0) goto LAB_1000cacc;
              piVar6 = *(int **)(unaff_EBP + -0x18);
              if (piVar6 != (int *)0x0) {
                (**(code **)(*piVar6 + 8))(piVar6);
                *(undefined4 *)(unaff_EBP + -0x18) = 0;
              }
              piVar6 = *(int **)(unaff_EBP + -0x14);
              if (piVar6 != (int *)0x0) {
                (**(code **)(*piVar6 + 8))(piVar6);
                *(undefined4 *)(unaff_EBP + -0x14) = 0;
              }
              *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + 1;
            } while (*(uint *)(unaff_EBP + -0x10) < *(uint *)(unaff_EBP + 0x20));
          }
          *(int *)(unaff_EBP + -0x2c) = *(int *)(unaff_EBP + -0x2c) + 1;
          piVar11 = *(int **)(*(int *)(unaff_EBP + -0x38) + 0x50);
          *(int **)(unaff_EBP + -0x38) = piVar11;
        } while (*(uint *)(unaff_EBP + -0x2c) < *(uint *)(unaff_EBP + -0x28));
      }
      if ((((*(int *)(unaff_EBP + -0x30) == 0) ||
           (*(uint *)(unaff_EBP + 0x20) <= *(uint *)(unaff_EBP + -0x24))) ||
          (iVar12 = grim_mipmap_generate(piVar8,(int *)(unaff_EBP + -0x4cc),*(int *)(unaff_EBP + -0x24) + -1
                                 ,*(int *)(unaff_EBP + 0x34)), -1 < iVar12)) &&
         ((*(int *)(unaff_EBP + -0x34) == 0 ||
          (iVar12 = (**(code **)(**(int **)(unaff_EBP + 8) + 0x74))
                              (*(int **)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + -0x20),
                               *(undefined4 *)(unaff_EBP + -0x1c)), -1 < iVar12)))) {
        uVar3 = *(undefined4 *)(unaff_EBP + -0x1c);
        *(undefined4 *)(unaff_EBP + -0x1c) = 0;
        **(undefined4 **)(unaff_EBP + 0x48) = uVar3;
        iVar12 = 0;
      }
    }
  }
LAB_1000cacc:
  piVar8 = *(int **)(unaff_EBP + -0x18);
  if (piVar8 != (int *)0x0) {
    (**(code **)(*piVar8 + 8))(piVar8);
    *(undefined4 *)(unaff_EBP + -0x18) = 0;
  }
  piVar8 = *(int **)(unaff_EBP + -0x14);
  if (piVar8 != (int *)0x0) {
    (**(code **)(*piVar8 + 8))(piVar8);
    *(undefined4 *)(unaff_EBP + -0x14) = 0;
  }
  piVar8 = *(int **)(unaff_EBP + -0x1c);
  if (piVar8 != (int *)0x0) {
    (**(code **)(*piVar8 + 8))(piVar8);
    *(undefined4 *)(unaff_EBP + -0x1c) = 0;
  }
  piVar8 = *(int **)(unaff_EBP + -0x20);
  if (piVar8 != (int *)0x0) {
    (**(code **)(*piVar8 + 8))(piVar8);
    *(undefined4 *)(unaff_EBP + -0x20) = 0;
  }
LAB_1000cb0e:
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  grim_file_stream_close((void *)(unaff_EBP + -0x8c));
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return iVar12;
}



/* grim_texture_create_from_memory @ 1000cb5c */

/* [binja] int32_t __stdcall sub_1000cb5c(int32_t** arg1, void* arg2, int32_t* arg3, int32_t arg4,
   int32_t arg5, int32_t arg6, int32_t arg7, void* arg8, int32_t arg9, int32_t arg10, int32_t**
   arg11, int32_t arg12, int32_t arg13, int32_t arg14, int32_t arg15) */

int grim_texture_create_from_memory(int **arg1,void *arg2,int *arg3,int arg4,int arg5,int arg6,int arg7,void *arg8,
                int arg9,int arg10,int **arg11,int arg12,int arg13,int arg14,int arg15)

{
  int iVar1;
  
  iVar1 = grim_texture_load_internal(arg1,arg2,arg3,arg4,arg5,1,arg6,arg7,arg8,arg9,arg10,arg11);
  return iVar1;
}



/* grim_file_stream_init @ 10010285 */

/* [binja] int32_t* __fastcall sub_10010285(int32_t* arg1) */

int * __fastcall grim_file_stream_init(int *arg1)

{
  *arg1 = 0;
  arg1[1] = 0;
  arg1[2] = 0;
  arg1[0xe] = 0;
  arg1[0xf] = 0;
  arg1[0x13] = 0;
  arg1[0x14] = 0;
  return arg1;
}



/* grim_file_stream_close @ 1001029e */

/* [binja] int32_t __fastcall sub_1001029e(void* arg1) */

int __fastcall grim_file_stream_close(void *arg1)

{
  void *pvVar1;
  void *extraout_EAX;
  void *extraout_EAX_00;
  void *extraout_EAX_01;
  void *pvVar2;
  
  if ((*(void **)((int)arg1 + 4) != (void *)0x0) && (*(int *)((int)arg1 + 0x38) != 0)) {
    operator_delete(*(void **)((int)arg1 + 4));
  }
  pvVar2 = *(void **)((int)arg1 + 8);
  if ((pvVar2 != (void *)0x0) && (*(int *)((int)arg1 + 0x3c) != 0)) {
    operator_delete(pvVar2);
    pvVar2 = extraout_EAX;
  }
  pvVar1 = *(void **)((int)arg1 + 0x4c);
  if (pvVar1 != (void *)0x0) {
    grim_file_stream_close(pvVar1);
    operator_delete(pvVar1);
    pvVar2 = extraout_EAX_00;
  }
  pvVar1 = *(void **)((int)arg1 + 0x50);
  if (pvVar1 != (void *)0x0) {
    grim_file_stream_close(pvVar1);
    operator_delete(pvVar1);
    pvVar2 = extraout_EAX_01;
  }
  return (int)pvVar2;
}



/* grim_file_stream_read_header @ 10010313 */

/* [binja] int32_t __thiscall sub_10010313(int32_t* arg1, int32_t* arg2) */

int __thiscall grim_file_stream_read_header(void *this,int *arg1,int *arg2)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  
  if ((*(void **)((int)this + 4) != (void *)0x0) && (*(int *)((int)this + 0x38) != 0)) {
    operator_delete(*(void **)((int)this + 4));
  }
  if ((*(void **)((int)this + 8) != (void *)0x0) && (*(int *)((int)this + 0x3c) != 0)) {
    operator_delete(*(void **)((int)this + 8));
  }
  *(int *)this = arg1[1];
  *(int *)((int)this + 4) = *arg1;
  *(int *)((int)this + 8) = arg1[0x12];
  puVar1 = (uint *)((int)this + 0x18);
  puVar3 = (uint *)(arg1 + 10);
  puVar4 = puVar1;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(int *)((int)this + 0x30) = arg1[2];
  *(int *)((int)this + 0x34) = arg1[3];
  iVar2 = *(int *)this;
  if ((iVar2 == 0x31545844) || (iVar2 == 0x32545844)) {
LAB_100103a7:
    *puVar1 = *puVar1 & 0xfffffffc;
    *(uint *)((int)this + 0x1c) = *(uint *)((int)this + 0x1c) & 0xfffffffc;
  }
  else {
    if (iVar2 != 0x32595559) {
      if (((iVar2 == 0x33545844) || (iVar2 == 0x34545844)) || (iVar2 == 0x35545844))
      goto LAB_100103a7;
      if (iVar2 != 0x59565955) goto LAB_100103ae;
    }
    *puVar1 = *puVar1 & 0xfffffffe;
  }
LAB_100103ae:
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x3c) = 0;
  *(uint *)((int)this + 0xc) = *(int *)((int)this + 0x20) - *puVar1;
  *(int *)((int)this + 0x10) = *(int *)((int)this + 0x24) - *(int *)((int)this + 0x1c);
  *(int *)((int)this + 0x14) = *(int *)((int)this + 0x2c) - *(int *)((int)this + 0x28);
  return 0;
}


