/* texture_get_or_load @ 0042a670 */

/* lookup texture handle; load if missing (name + path) */

int __cdecl texture_get_or_load(char *name,char *path)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(name);
  if (iVar1 == -1) {
    iVar1 = (*grim_interface_ptr->vtable->grim_load_texture)(name,name);
    if ((char)iVar1 != '\0') {
      if (*(float *)((int)cv_silentloads + 0xc) == 0.0) {
        console_printf(&console_log_queue,s_loading_texture_ok,name);
      }
      iVar1 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(name);
      return iVar1;
    }
    console_printf(&console_log_queue,s_loading_texture_failed,name);
    iVar1 = -1;
  }
  return iVar1;
}



/* texture_get_or_load_alt @ 0042a700 */

/* duplicate of texture_get_or_load (callers are mostly .jaz assets) */

int __cdecl texture_get_or_load_alt(char *name,char *path)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(name);
  if (iVar1 == -1) {
    iVar1 = (*grim_interface_ptr->vtable->grim_load_texture)(name,name);
    if ((char)iVar1 != '\0') {
      if (*(float *)((int)cv_silentloads + 0xc) == 0.0) {
        console_printf(&console_log_queue,s_loading_texture_ok,name);
      }
      iVar1 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(name);
      return iVar1;
    }
    console_printf(&console_log_queue,s_loading_texture_failed,name);
    iVar1 = -1;
  }
  return iVar1;
}



/* render_state_push @ 0043aa60 */

undefined4 render_state_push(void)

{
  int iVar1;
  uint3 extraout_var;
  
  iVar1 = game_is_full_version();
  if ((char)iVar1 == '\0') {
    console_printf(&console_log_queue,s___Potentially_illegal_score_dete_00477b16 + 2);
    iVar1 = (uint)extraout_var << 8;
  }
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}



/* render_state_pop @ 0043aa90 */

/* [binja] void* sub_43aa90(void* arg1, void* arg2) */

void * __cdecl render_state_pop(void *arg1,void *arg2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar2 = 0xffffffff;
  pcVar4 = arg1;
  do {
    pcVar5 = pcVar4;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar5 = pcVar4 + 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar5;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar4 = pcVar5 + -uVar2;
  pcVar5 = arg2;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar5 = pcVar5 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar5 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  }
  *(undefined4 *)((int)arg2 + 0x20) = *(undefined4 *)((int)arg1 + 0x20);
  *(undefined4 *)((int)arg2 + 0x24) = *(undefined4 *)((int)arg1 + 0x24);
  *(undefined1 *)((int)arg2 + 0x28) = *(undefined1 *)((int)arg1 + 0x28);
  *(undefined1 *)((int)arg2 + 0x29) = *(undefined1 *)((int)arg1 + 0x29);
  *(undefined1 *)((int)arg2 + 0x2a) = *(undefined1 *)((int)arg1 + 0x2a);
  *(undefined1 *)((int)arg2 + 0x2b) = *(undefined1 *)((int)arg1 + 0x2b);
  *(undefined4 *)((int)arg2 + 0x2c) = *(undefined4 *)((int)arg1 + 0x2c);
  *(undefined4 *)((int)arg2 + 0x34) = *(undefined4 *)((int)arg1 + 0x34);
  *(undefined4 *)((int)arg2 + 0x30) = *(undefined4 *)((int)arg1 + 0x30);
  *(undefined4 *)((int)arg2 + 0x38) = *(undefined4 *)((int)arg1 + 0x38);
  *(undefined4 *)((int)arg2 + 0x3c) = 0;
  return arg2;
}



/* buffer_reader_init @ 0043b850 */

/* initializes the buffer reader cursor and length */

void __cdecl buffer_reader_init(void *data,int size)

{
  buffer_reader_data = data;
  buffer_reader_size = size;
  buffer_reader_offset = 0;
  return;
}



/* buffer_reader_seek @ 0043b870 */

/* sets the buffer reader cursor */

void __cdecl buffer_reader_seek(int offset)

{
  buffer_reader_offset = offset;
  return;
}



/* buffer_reader_read_u16 @ 0043b880 */

/* reads a little-endian u16 from the buffer */

int buffer_reader_read_u16(void)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)(buffer_reader_offset + (int)buffer_reader_data);
  buffer_reader_offset = buffer_reader_offset + 2;
  return CONCAT22((short)((uint)buffer_reader_data >> 0x10),*puVar1);
}



/* buffer_reader_read_u32 @ 0043b8a0 */

/* reads a little-endian u32 from the buffer */

uint buffer_reader_read_u32(void)

{
  uint *puVar1;
  
  puVar1 = (uint *)(buffer_reader_offset + (int)buffer_reader_data);
  buffer_reader_offset = buffer_reader_offset + 4;
  return *puVar1;
}



/* buffer_reader_skip @ 0043b8c0 */

/* advances the buffer reader cursor */

void __cdecl buffer_reader_skip(int count)

{
  buffer_reader_offset = buffer_reader_offset + count;
  return;
}



/* buffer_reader_find_tag @ 0043b8e0 */

/* searches the buffer for a tag and updates the cursor */

int __cdecl buffer_reader_find_tag(char *tag,int tag_len)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < buffer_reader_size) {
    do {
      iVar1 = 0;
      if (0 < tag_len) {
        do {
          if (*(char *)((int)buffer_reader_data + iVar1 + iVar2) != tag[iVar1]) break;
          iVar1 = iVar1 + 1;
        } while (iVar1 < tag_len);
      }
      if (iVar1 == tag_len) {
        buffer_reader_offset = iVar2 + tag_len;
        return CONCAT31((int3)((uint)iVar1 >> 8),1);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < buffer_reader_size);
  }
  return buffer_reader_size & 0xffffff00;
}



/* resource_pack_read_cstring @ 0043b940 */

/* reads a NUL-terminated pack entry name into resource_pack_entry_name_buf */

uint __cdecl resource_pack_read_cstring(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  bVar1 = *(byte *)(param_1 + 3);
  while (((bVar1 & 0x10) == 0 && (uVar2 = crt_getc(param_1), uVar2 != 0))) {
    (&resource_pack_entry_name_buf)[iVar3] = (char)uVar2;
    bVar1 = *(byte *)(param_1 + 3);
    iVar3 = iVar3 + 1;
  }
  (&resource_pack_entry_name_buf)[iVar3] = 0;
  return (uint)~param_1[3] >> 4 & 1;
}



/* resource_pack_set @ 0043b980 */

/* validates and sets the active resource pack path */

int __cdecl resource_pack_set(char *path)

{
  char cVar1;
  FILE *fp;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  fp = (FILE *)crt_fopen(path,&file_mode_read_binary);
  if (fp == (FILE *)0x0) {
    resource_pack_path._0_1_ = 0;
    resource_pack_enabled = 0;
    return 0;
  }
  uVar3 = 0xffffffff;
  do {
    pcVar5 = path;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar5 = path + 1;
    cVar1 = *path;
    path = pcVar5;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar5 + -uVar3;
  pcVar6 = (char *)&resource_pack_path;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  resource_pack_enabled = 1;
  iVar2 = crt_fclose(fp);
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}



/* resource_open_read @ 0043b9e0 */

/* opens a resource from the active pack or filesystem and returns its size */

int __cdecl resource_open_read(byte *path,int *size_out)

{
  int *piVar1;
  char cVar2;
  FILE *fp;
  uint uVar3;
  int iVar4;
  
  piVar1 = size_out;
  if (resource_pack_enabled != '\0') {
    fp = (FILE *)crt_fopen((LPCSTR)&resource_pack_path,&file_mode_read_binary);
    resource_fp = (FILE *)fp;
    if (fp == (FILE *)0x0) {
      return 0;
    }
    crt_fseek((int *)fp,4,0);
    uVar3 = resource_pack_read_cstring((undefined4 *)fp);
    cVar2 = (char)uVar3;
    while (cVar2 != '\0') {
      crt_fread((char *)&size_out,4,1,(int *)fp);
      *piVar1 = (int)size_out;
      uVar3 = string_compare_nocase(size_out,&resource_pack_entry_name_buf,path);
      iVar4 = 0;
      if (uVar3 == 0) goto LAB_0043bac3;
      crt_fseek((int *)fp,(int)size_out,1);
      uVar3 = resource_pack_read_cstring((undefined4 *)fp);
      cVar2 = (char)uVar3;
    }
    crt_fclose(fp);
  }
  resource_fp = (FILE *)crt_fopen((LPCSTR)path,&file_mode_read_binary);
  if (resource_fp == (FILE *)0x0) {
    return 0;
  }
  crt_fseek((int *)resource_fp,0,2);
  iVar4 = crt_ftell((char *)resource_fp);
  *piVar1 = iVar4;
  iVar4 = crt_fseek((int *)resource_fp,0,0);
LAB_0043bac3:
  return CONCAT31((int3)((uint)iVar4 >> 8),1);
}



/* resource_close @ 0043bad0 */

/* closes the current resource file handle */

void resource_close(void)

{
  if (resource_fp != (FILE *)0x0) {
    crt_fclose((FILE *)resource_fp);
  }
  return;
}



/* dsound_init @ 0043baf0 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* initializes DirectSound and the primary buffer */

int __cdecl dsound_init(void *hwnd,uint coop_level)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 uStack_54;
  undefined4 auStack_30 [4];
  undefined4 uStack_20;
  short sStack_10;
  ushort uStack_8;
  
  if (dsound_iface != (int *)0x0) {
    (**(code **)(*dsound_iface + 8))();
  }
  dsound_iface = (int *)0x0;
  uVar1 = DirectSoundCreate8((LPCGUID)0x0,(LPDIRECTSOUND8 *)&dsound_iface,(LPUNKNOWN)0x0);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  uVar1 = (**(code **)(*dsound_iface + 0x18))();
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  puVar4 = auStack_30;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  uStack_54 = 0;
  auStack_30[0] = 0x24;
  auStack_30[1] = 1;
  auStack_30[2] = 0;
  uStack_20 = 0;
  uVar1 = (**(code **)(*dsound_iface + 0xc))(dsound_iface,auStack_30);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  uStack_54 = CONCAT22(sStack_10,1);
  piVar5 = &uStack_54;
  uVar1 = (**(code **)(CONCAT22(uStack_8,(uStack_8 >> 3) * sStack_10) + 0x38))(&stack0xffffffb8);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  uVar2 = 0;
  if (piVar5 != (int *)0x0) {
    uVar2 = (**(code **)(*piVar5 + 8))(piVar5);
  }
  return CONCAT31((int3)((uint)uVar2 >> 8),1);
}



/* dsound_shutdown @ 0043bc20 */

/* releases the DirectSound interface */

void dsound_shutdown(void)

{
  if (dsound_iface != (int *)0x0) {
    (**(code **)(*dsound_iface + 8))(dsound_iface);
  }
  dsound_iface = (int *)0x0;
  return;
}



/* dsound_restore_buffer @ 0043bc40 */

/* restores a lost DirectSound buffer */

int __cdecl dsound_restore_buffer(void *buffer)

{
  void *pvVar1;
  uint in_EAX;
  int iVar2;
  undefined4 extraout_EAX;
  uint unaff_ESI;
  
  pvVar1 = buffer;
  if (((buffer != (void *)0x0) &&
      (in_EAX = (**(code **)(*(int *)buffer + 0x24))(buffer,&buffer), -1 < (int)in_EAX)) &&
     ((unaff_ESI & 2) != 0)) {
    do {
      while (iVar2 = (**(code **)(*(int *)pvVar1 + 0x50))(pvVar1), iVar2 == -0x7787ff6a) {
        Sleep(10);
      }
    } while (iVar2 != 0);
    OutputDebugStringA(s_snd_buffer_restored);
    return CONCAT31((int3)((uint)extraout_EAX >> 8),1);
  }
  return in_EAX & 0xffffff00;
}



/* resource_read_alloc @ 0043bca0 */

/* reads a resource into a newly allocated buffer */

int __cdecl resource_read_alloc(byte *path,void **out_data,uint *out_size)

{
  FILE *pFVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = resource_open_read(path,(int *)out_size);
  pFVar1 = resource_fp;
  if ((char)iVar2 == '\0') {
    return iVar2;
  }
  pcVar3 = operator_new(*out_size);
  crt_fread(pcVar3,*out_size,1,(int *)pFVar1);
  resource_close();
  *out_data = pcVar3;
  return CONCAT31((int3)((uint)out_data >> 8),1);
}



/* wav_parse_into_entry @ 0043c110 */

/* parses WAV data into an entry and copies PCM */

int __cdecl wav_parse_into_entry(void *entry,void *data,int size)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  *(undefined4 *)entry = 0;
  *(undefined4 *)((int)entry + 4) = 0;
  *(undefined4 *)((int)entry + 8) = 0;
  *(undefined4 *)((int)entry + 0xc) = 0;
  *(undefined2 *)((int)entry + 0x10) = 0;
  *(undefined2 *)entry = 1;
  *(undefined2 *)((int)entry + 2) = 1;
  *(undefined2 *)((int)entry + 0xe) = 0x10;
  *(undefined4 *)((int)entry + 4) = 0x5622;
  *(undefined2 *)((int)entry + 0xc) = 2;
  *(undefined2 *)((int)entry + 0x10) = 0;
  *(undefined4 *)((int)entry + 8) = 0xac44;
  buffer_reader_init(data,size);
  buffer_reader_seek(0);
  iVar1 = buffer_reader_find_tag(&DAT_00477c98,4);
  if ((char)iVar1 == '\0') {
    return iVar1;
  }
  buffer_reader_skip(4);
  buffer_reader_skip(2);
  iVar1 = buffer_reader_read_u16();
  *(short *)((int)entry + 2) = (short)iVar1;
  uVar2 = buffer_reader_read_u32();
  *(uint *)((int)entry + 4) = uVar2;
  buffer_reader_skip(6);
  uVar2 = buffer_reader_read_u16();
  *(short *)((int)entry + 0xe) = (short)uVar2;
  iVar1 = (uint)*(ushort *)((int)entry + 2) * (uVar2 & 0xffff);
  *(undefined2 *)((int)entry + 0x10) = 0;
  uVar2 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
  *(short *)((int)entry + 0xc) = (short)uVar2;
  *(uint *)((int)entry + 8) = (uVar2 & 0xffff) * *(int *)((int)entry + 4);
  buffer_reader_find_tag(&DAT_00477c90,4);
  uVar2 = buffer_reader_read_u32();
  *(uint *)((int)entry + 0x18) = uVar2;
  puVar3 = operator_new(uVar2);
  *(undefined4 **)((int)entry + 0x14) = puVar3;
  puVar5 = (undefined4 *)(buffer_reader_offset + (int)data);
  for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar3 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  return CONCAT31((int3)(uVar2 >> 8),1);
}



/* music_entry_load_ogg @ 0043c3a0 */

/* loads an OGG stream into a music entry */

int __cdecl music_entry_load_ogg(void *entry,byte *path)

{
  ushort uVar1;
  FILE *pFVar2;
  int iVar3;
  void *stream;
  void *this;
  uint uVar4;
  undefined4 *puVar5;
  uint3 uVar6;
  uint uVar7;
  uint unaff_EDI;
  undefined4 local_24 [4];
  void *local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar3 = resource_open_read(path,(int *)&path);
  pFVar2 = resource_fp;
  if ((char)iVar3 == '\0') {
    return iVar3;
  }
  stream = operator_new((uint)(path + 8));
  crt_fread((char *)((int)stream + 8),(uint)path,1,(int *)pFVar2);
  resource_close();
  this = operator_new(0x310);
  *(void **)((int)entry + 0x74) = this;
  iVar3 = vorbis_mem_open(this,stream,path,unaff_EDI);
  if ((char)iVar3 == '\0') {
    return iVar3;
  }
  *(undefined4 *)entry = 0;
  *(undefined4 *)((int)entry + 4) = 0;
  *(undefined4 *)((int)entry + 8) = 0;
  *(undefined4 *)((int)entry + 0xc) = 0;
  *(undefined2 *)((int)entry + 0x10) = 0;
  *(undefined2 *)entry = 1;
  uVar1 = *(ushort *)(*(int *)((int)entry + 0x74) + 0x2f4);
  *(ushort *)((int)entry + 2) = uVar1;
  *(undefined4 *)((int)entry + 4) = *(undefined4 *)(*(int *)((int)entry + 0x74) + 0x2f8);
  *(undefined2 *)((int)entry + 0xe) = 0x10;
  *(undefined2 *)((int)entry + 0x10) = 0;
  uVar4 = (int)((uint)uVar1 * 0x10) >> 3;
  *(short *)((int)entry + 0xc) = (short)uVar4;
  iVar3 = (uVar4 & 0xffff) * *(int *)((int)entry + 4);
  *(int *)((int)entry + 8) = iVar3;
  uVar4 = iVar3 * 2;
  *(uint *)((int)entry + 0x18) = uVar4;
  puVar5 = operator_new(uVar4);
  uVar4 = *(uint *)((int)entry + 0x18);
  *(undefined4 **)((int)entry + 0x14) = puVar5;
  for (uVar7 = uVar4 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  puVar5 = local_24;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_24[2] = *(undefined4 *)((int)entry + 0x18);
  local_10 = 0;
  local_4 = 0;
  local_8 = 0;
  local_24[0] = 0x24;
  local_24[1] = 0x180c0;
  local_c = 0;
  local_14 = entry;
  iVar3 = (**(code **)(*dsound_iface + 0xc))(dsound_iface,local_24,(int)entry + 0x24,0);
  uVar6 = (uint3)((uint)iVar3 >> 8);
  if (iVar3 < 0) {
    return (uint)uVar6 << 8;
  }
  *(undefined4 *)((int)entry + 0x80) = 0;
  return CONCAT31(uVar6,1);
}



/* music_stream_update @ 0043c520 */

/* updates streaming cursor and refills if needed */

void __cdecl music_stream_update(int entry)

{
  int entry_00;
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  entry_00 = entry;
  iVar1 = (**(code **)(**(int **)(entry + 0x24) + 0x10))(*(int **)(entry + 0x24),&entry);
  if (-1 < iVar1) {
    if (*(int *)(entry_00 + 0x78) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(entry_00 + 0x18) - *(int *)(entry_00 + 0x78);
    }
    *(undefined4 *)(entry_00 + 0x78) = 0;
    uVar3 = *(int *)(entry_00 + 0x80) + iVar1;
    *(int *)(entry_00 + 0x7c) = *(int *)(entry_00 + 0x7c) + iVar1;
    *(uint *)(entry_00 + 0x80) = uVar3;
    uVar2 = (int)(*(int *)(entry_00 + 0x18) + (*(int *)(entry_00 + 0x18) >> 0x1f & 3U)) >> 2;
    if (uVar2 < uVar3) {
      *(uint *)(entry_00 + 0x80) = uVar3 - uVar2;
      music_stream_fill(entry_00);
    }
  }
  return;
}



/* music_stream_fill @ 0043c590 */

/* decodes and writes the next music stream chunk */

int __cdecl music_stream_fill(int entry)

{
  int iVar1;
  uint uVar2;
  uint extraout_EAX;
  int iVar3;
  int iVar4;
  char *dst;
  int *bytes;
  
  bytes = *(int **)(entry + 0x24);
  iVar1 = (int)(*(int *)(entry + 0x18) + (*(int *)(entry + 0x18) >> 0x1f & 3U)) >> 2;
  iVar4 = *(int *)(entry + 0x1c);
  uVar2 = (**(code **)(*bytes + 0x2c))();
  if (-1 < (int)uVar2) {
    if (&stack0x00000000 != (undefined1 *)0xc) {
      OutputDebugStringA(s_____SND__Somehow_data_on_the_sec_00477ccc);
      return extraout_EAX & 0xffffff00;
    }
    dst = (char *)0x8;
    do {
      iVar3 = vorbis_read_pcm16(*(void **)(entry + 0x74),(void *)((8 - (int)dst) + iVar1),dst,
                                (int)bytes);
      if (iVar3 < 1) {
        iVar3 = vorbis_read_pcm16(*(void **)(entry + 0x74),(void *)((8 - (int)dst) + iVar1),dst,
                                  (int)bytes);
      }
      dst = dst + -iVar3;
    } while ((0 < (int)dst) && (iVar3 != 0));
    (**(code **)(**(int **)(entry + 0x24) + 0x4c))(*(int **)(entry + 0x24),iVar1,8,0,0);
    iVar4 = iVar4 + *(int *)(entry + 0x1c);
    uVar2 = iVar4 / *(int *)(entry + 0x18);
    *(int *)(entry + 0x1c) = iVar4 % *(int *)(entry + 0x18);
  }
  return uVar2 & 0xffffff00;
}



/* music_load_track @ 0043c8d0 */

/* loads a music track and returns its id */

int __cdecl music_load_track(char *path)

{
  void **ppvVar1;
  int iVar2;
  int iVar3;
  
  sfx_load_counter = sfx_load_counter + 1;
  iVar3 = 0;
  ppvVar1 = &music_entry_table.vorbis_stream;
  while ((ppvVar1[-0x18] != (void *)0x0 || (*ppvVar1 != (void *)0x0))) {
    ppvVar1 = ppvVar1 + 0x21;
    iVar3 = iVar3 + 1;
    if (0x4c84c3 < (int)ppvVar1) {
      return -1;
    }
  }
  if (iVar3 == -1) {
    return -1;
  }
  iVar2 = music_entry_load_ogg(&music_entry_table + iVar3,(byte *)path);
  if ((char)iVar2 == '\0') {
    console_printf(&console_log_queue,s_sfx_tune_failed_fmt,iVar3,path);
    return iVar3;
  }
  console_printf(&console_log_queue,s_sfx_tune_ok_fmt,iVar3,path);
  return iVar3;
}



/* music_queue_track @ 0043c960 */

/* queues a music track id */

void __cdecl music_queue_track(int track_id)

{
  if (-1 < track_id) {
    music_playlist[music_playlist_index] = track_id;
    music_playlist_index = music_playlist_index + 1;
  }
  return;
}



/* music_release_track @ 0043c980 */

/* releases a music track by id */

int __cdecl music_release_track(int track_id)

{
  uint in_EAX;
  undefined4 extraout_EAX;
  
  if (((-1 < track_id) && (track_id < 0x80)) &&
     (in_EAX = track_id * 0x84, (&music_entry_table)[track_id].pcm_data != (void *)0x0)) {
    sfx_release_entry((int)(&music_entry_table + track_id));
    return CONCAT31((int3)((uint)extraout_EAX >> 8),1);
  }
  return in_EAX & 0xffffff00;
}



/* music_release_all @ 0043d0d0 */

/* releases all loaded music tracks */

void music_release_all(void)

{
  char *filename;
  music_entry_t *entry;
  
  if (sfx_unmuted_flag != '\0') {
    entry = &music_entry_table;
    do {
      sfx_release_entry((int)entry);
      entry = entry + 1;
    } while ((int)entry < 0x4c8450);
    console_flush_log(&console_log_queue,filename);
  }
  return;
}



/* ui_focus_set @ 0043d7e0 */

/* sets the active focus candidate; optionally resets the focus timer */

void __cdecl ui_focus_set(int id,char reset_timer)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = ui_focus_index;
  if ((&ui_focus_candidates)[ui_focus_index] != id) {
    if (reset_timer != '\0') {
      ui_focus_timer_ms = 1000;
    }
    iVar2 = 0;
    if (0 < ui_focus_count) {
      piVar3 = &ui_focus_candidates;
      while (iVar1 = iVar2, *piVar3 != id) {
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
        if (ui_focus_count <= iVar2) {
          return;
        }
      }
    }
  }
  ui_focus_index = iVar1;
  return;
}



/* ui_focus_update @ 0043d830 */

/* handles menu focus navigation and returns 1 when the given id is focused */

int __cdecl ui_focus_update(int id)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (&ui_focus_candidates)[ui_focus_index];
  if (ui_focus_frame_marker_ms == game_time_ms) {
    if (0x1f < ui_focus_count) {
      ui_focus_count = 0x1f;
    }
    (&ui_focus_candidates)[ui_focus_count] = id;
    ui_focus_count = ui_focus_count + 1;
    return CONCAT31((int3)((uint)ui_focus_count >> 8),id == iVar1);
  }
  ui_focus_timer_ms = ui_focus_timer_ms - frame_dt_ms;
  if (ui_focus_timer_ms < 0) {
    ui_focus_timer_ms = 0;
  }
  if ((ui_tab_key_disabled == '\0') &&
     (iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xf), (char)iVar2 != '\0')) {
    iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x2a);
    if (((char)iVar2 == '\0') &&
       (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x36), (char)iVar2 == '\0')) {
      ui_focus_index = ui_focus_index + 1;
    }
    else {
      ui_focus_index = ui_focus_index + -1;
    }
    ui_focus_timer_ms = 1000;
  }
  if (ui_focus_index < 0) {
    ui_focus_index = ui_focus_count + -1;
  }
  if (ui_focus_count + -1 < ui_focus_index) {
    ui_focus_index = 0;
  }
  ui_focus_frame_marker_ms = game_time_ms;
  ui_focus_candidates = id;
  ui_focus_count = 1;
  return (uint)(id == iVar1);
}



/* ui_focus_draw @ 0043d940 */

/* draws the focus highlight for the active menu item */

void __cdecl ui_focus_draw(float *xy)

{
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  local_10 = 0x3f4ccccd;
  local_4 = (float)ui_focus_timer_ms * 0.00080000004;
  local_c = 0x3f4ccccd;
  local_8 = 0x3f19999a;
  local_18 = *xy;
  local_14 = xy[1] + 4.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_18,6.0,6.0);
  return;
}



/* ui_slider_update_and_draw @ 0043d9b0 */

/* [binja] int32_t sub_43d9b0(int32_t* arg1, int32_t arg2) */

int __cdecl ui_slider_update_and_draw(int *arg1,int arg2)

{
  float y;
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  longlong lVar5;
  float local_10;
  float local_c;
  float local_8;
  
  iVar1 = arg2;
  iVar2 = ui_focus_update(arg2);
  local_8 = (float)*arg1;
  local_10 = (float)*arg1 - 3.0;
  y = (float)arg1[1];
  local_c = (float)arg1[1] - 1.0;
  lVar5 = __ftol();
  iVar3 = ui_mouse_inside_rect(&local_10,0x12,(int)lVar5);
  bVar4 = (char)iVar3 != '\0';
  if (bVar4) {
    ui_focus_set(arg2,'\0');
  }
  if ((char)iVar2 != '\0') {
    local_10 = (float)*arg1 - 16.0;
    local_c = (float)arg1[1];
    ui_focus_draw(&local_10);
    if (*(char *)(arg2 + 0xc) != '\0') {
      iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xcd);
      if ((char)iVar2 != '\0') {
        iVar2 = *(int *)arg2;
        *(int *)arg2 = iVar2 + 1;
        if (*(int *)(arg2 + 4) < iVar2 + 1) {
          *(int *)arg2 = *(int *)(arg2 + 4);
        }
      }
      iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xcb);
      if (((char)iVar2 != '\0') && (iVar2 = *(int *)arg2, *(int *)arg2 = iVar2 + -1, iVar2 + -1 < 0)
         ) {
        *(undefined4 *)arg2 = 0;
      }
    }
  }
  if (bVar4) {
    iVar2 = input_primary_is_down();
    if (((char)iVar2 != '\0') && (*(char *)(arg2 + 0xc) != '\0')) {
      lVar5 = __ftol();
      *(int *)arg2 = (int)lVar5;
      if ((int)lVar5 < *(int *)(arg2 + 8)) {
        *(int *)arg2 = *(int *)(arg2 + 8);
      }
      if (*(int *)(arg2 + 4) < *(int *)arg2) {
        *(int *)arg2 = *(int *)(arg2 + 4);
      }
    }
  }
  if (ui_rect_on_texture_id == -1) {
    ui_rect_on_texture_id = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_ui_rectOn);
  }
  if (ui_rect_off_texture_id == -1) {
    ui_rect_off_texture_id = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_ui_rectOff);
  }
  (*grim_interface_ptr->vtable->grim_bind_texture)(ui_rect_off_texture_id,0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.5);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  iVar2 = 0;
  if (0 < *(int *)(arg2 + 4)) {
    arg2 = 0;
    do {
      (*grim_interface_ptr->vtable->grim_draw_quad)((float)arg2 + local_8,y,8.0,16.0);
      iVar2 = iVar2 + 1;
      arg2 = arg2 + 8;
    } while (iVar2 < *(int *)(iVar1 + 4));
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_end_batch)();
  if (0 < *(int *)iVar1) {
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_rect_on_texture_id,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    iVar2 = 0;
    if (0 < *(int *)iVar1) {
      arg2 = 0;
      do {
        (*grim_interface_ptr->vtable->grim_draw_quad)((float)arg2 + local_8,y,8.0,16.0);
        iVar2 = iVar2 + 1;
        arg2 = arg2 + 8;
      } while (iVar2 < *(int *)iVar1);
    }
    iVar2 = (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  return iVar2;
}



/* ui_checkbox_update @ 0043dc80 */

/* draws a checkbox widget, handles hover/focus, toggles on click */

int __cdecl ui_checkbox_update(float *xy,char *checkbox)

{
  IGrim2D_vtbl *pIVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int handle;
  undefined4 uVar5;
  undefined1 uStack_45;
  char *name;
  float fStack_8;
  float fStack_4;
  
  iVar3 = ui_focus_update((int)checkbox);
  checkbox[2] = '\0';
  if (*(char **)(checkbox + 4) == (char *)0x0) {
    iVar4 = ui_mouse_inside_rect(xy,0x10,0x10);
    cVar2 = (char)iVar4;
  }
  else {
    iVar4 = (*grim_interface_ptr->vtable->grim_measure_text_width)(*(char **)(checkbox + 4));
    iVar4 = ui_mouse_inside_rect(xy,0x10,iVar4 + 0x16);
    cVar2 = (char)iVar4;
  }
  if (cVar2 != '\0') {
    checkbox[2] = '\x01';
  }
  if (checkbox[1] != '\0') {
    checkbox[2] = '\0';
  }
  if (checkbox[2] != '\0') {
    ui_focus_set((int)checkbox,'\0');
  }
  if ((char)iVar3 != '\0') {
    fStack_8 = *xy - 16.0;
    fStack_4 = xy[1];
    ui_focus_draw(&fStack_8);
  }
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  pIVar1 = grim_interface_ptr->vtable;
  iVar4 = 0;
  if (*checkbox == '\0') {
    name = s_ui_checkOff_00474434;
  }
  else {
    name = s_ui_checkOn_00474454;
  }
  handle = (*pIVar1->grim_get_texture_handle)(name);
  (*pIVar1->grim_bind_texture)(handle,iVar4);
  if ((ui_tab_key_disabled == '\0') &&
     ((((char)iVar3 != '\0' &&
       (iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c), (char)iVar3 != '\0')) ||
      ((checkbox[2] != '\0' && (iVar3 = input_primary_just_pressed(), (char)iVar3 != '\0')))))) {
    *checkbox = *checkbox == '\0';
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)(*xy,xy[1],16.0,16.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  if (checkbox[2] == '\0') {
    uVar5 = (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
  }
  else {
    uVar5 = (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  }
  if (*(char **)(checkbox + 4) != (char *)0x0) {
    uVar5 = (*grim_interface_ptr->vtable->grim_draw_text_small)
                      (*xy + 22.0,xy[1] + 1.0,*(char **)(checkbox + 4));
  }
  return CONCAT31((int3)((uint)uVar5 >> 8),uStack_45);
}



/* ui_scrollbar_update @ 0043def0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates and renders a scroll bar (wheel, drag, key input) */

void __cdecl ui_scrollbar_update(float *xy,float *state)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *text;
  float unaff_ESI;
  int iVar7;
  char *pcVar8;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  longlong lVar9;
  undefined4 *h;
  undefined4 *puVar10;
  float *pfVar11;
  float *pfVar12;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float fStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  pfVar12 = xy;
  lVar9 = __ftol();
  *xy = (float)(int)lVar9;
  lVar9 = __ftol();
  xy[1] = (float)(int)lVar9;
  state[1] = -NAN;
  iVar4 = ui_focus_update((int)state);
  xy = (float *)CONCAT31((int3)((ulonglong)lVar9 >> 8),(char)iVar4);
  if ((char)iVar4 != '\0') {
    local_30 = *pfVar12 - 16.0;
    local_2c = pfVar12[1];
    ui_focus_draw(&local_30);
  }
  pfVar11 = &local_30;
  fVar2 = (float)((int)state[3] * 0x10 + 4);
  local_30 = 1.0;
  local_2c = 1.0;
  local_28 = 1.0;
  local_24 = 1.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(pfVar12,250.0,fVar2);
  fStack_34 = *pfVar12 + 1.0;
  puVar10 = &uStack_14;
  uStack_14 = 0;
  local_30 = pfVar12[1] + 1.0;
  fStack_10 = 0.0;
  fStack_c = 0.0;
  fStack_8 = 1.0;
  h = (undefined4 *)((float)xy - 2.0);
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_34,248.0,(float)h);
  if ((int)state[3] < (int)state[0xd]) {
    fStack_38 = *pfVar12 + 240.0;
    h = &uStack_18;
    uStack_18 = 0x3f800000;
    fStack_34 = pfVar12[1];
    uStack_14 = 0x3f800000;
    fStack_10 = 1.0;
    fStack_c = 0.8;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_38,1.0,fVar2);
  }
  (*grim_interface_ptr->vtable->grim_get_mouse_wheel_delta)(h,puVar10,pfVar11);
  if ((float10)0.0 < extraout_ST0) {
    *state = *state - 1.0;
  }
  (*grim_interface_ptr->vtable->grim_get_mouse_wheel_delta)();
  if (extraout_ST0_00 < (float10)0.0) {
    *state = *state + 1.0;
  }
  if (fStack_8._0_1_ != '\0') {
    iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(200);
    if ((char)iVar4 != '\0') {
      *state = *state - 1.0;
    }
    iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd0);
    if ((char)iVar4 != '\0') {
      *state = *state + 1.0;
    }
  }
  iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xc9);
  if ((char)iVar4 != '\0') {
    fStack_8 = (float)((int)state[3] + -1);
    *state = *state - (float)(int)fStack_8;
  }
  iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd1);
  if ((char)iVar4 != '\0') {
    *state = (float)((int)state[3] + -1) + *state;
  }
  fVar2 = state[0xd];
  fVar3 = state[3];
  fStack_40 = (float)((int)fVar2 - (int)fVar3);
  if ((float)(int)fStack_40 < *state) {
    *state = (float)(int)fStack_40;
  }
  if (*state < 0.0) {
    *state = 0.0;
  }
  fStack_8 = fVar2;
  lVar9 = __ftol();
  fStack_40 = (float)lVar9;
  fStack_8 = ((float)(int)fVar3 / (float)(int)fStack_8) * unaff_ESI;
  if (unaff_ESI < fStack_8) {
    fStack_8 = fStack_4 - 3.0;
  }
  local_24 = *pfVar12 + 241.0;
  fStack_20 = (float)(((((float10)fStack_4 - (float10)3.0) - (float10)fStack_8) / extraout_ST0_01) *
                      (float10)(int)fStack_40 + (float10)1.0 + (float10)pfVar12[1]);
  if ((int)fVar3 < (int)fVar2) {
    uStack_1c = 0x3f800000;
    uStack_18 = 0x3f800000;
    uStack_14 = 0x3f800000;
    fStack_10 = 0.8;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_24,8.0,fStack_8 + 1.0);
    fStack_40 = *pfVar12 + 240.0;
    iVar4 = 10;
    fStack_3c = pfVar12[1];
    lVar9 = __ftol();
    iVar4 = ui_mouse_inside_rect(&fStack_40,(int)lVar9,iVar4);
    if ((char)iVar4 == '\0') {
      fStack_40 = local_28 + 1.0;
      fStack_3c = local_24 + 1.0;
      fStack_20 = 0.1;
      uStack_1c = 0x3e4ccccd;
      uStack_18 = 0x3ecccccd;
      uStack_14 = 0x3f800000;
      (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_40,6.0,fStack_c - 1.0);
      iVar4 = input_primary_is_down();
      if ((char)iVar4 == '\0') {
        crt_cmd_show_flag = '\0';
        goto LAB_0043e37f;
      }
    }
    else {
      fStack_40 = local_28 + 1.0;
      fStack_3c = local_24 + 1.0;
      fStack_20 = 0.2;
      uStack_1c = 0x3ecccccd;
      uStack_18 = 0x3f4ccccd;
      uStack_14 = 0x3f800000;
      (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_40,6.0,fStack_c - 1.0);
      crt_cmd_show_flag = '\x01';
      iVar4 = input_primary_just_pressed();
      if ((char)iVar4 != '\0') {
        iVar4 = 8;
        lVar9 = __ftol();
        iVar4 = ui_mouse_inside_rect(&local_2c,(int)lVar9,iVar4);
        if ((char)iVar4 == '\0') {
          crt_startup_info_flags = 0.0;
        }
        else {
          crt_startup_info_flags = (ui_mouse_y - pfVar12[1]) - (*state / (float)(int)state[0xd]) * fStack_c;
        }
      }
    }
    if ((crt_cmd_show_flag != '\0') && (iVar4 = input_primary_is_down(), (char)iVar4 != '\0')) {
      fVar2 = (((ui_mouse_y - pfVar12[1]) - crt_startup_info_flags) / fStack_c) * (float)(int)state[0xd];
      *state = fVar2;
      fStack_10 = (float)((int)state[0xd] - (int)state[3]);
      if (fStack_10 < fVar2) {
        *state = fStack_10;
      }
      if (*state < 0.0) {
        *state = 0.0;
      }
    }
  }
LAB_0043e37f:
  local_28 = pfVar12[1];
  local_2c = *pfVar12 - 2.0;
  iVar4 = 0;
  if (0 < (int)state[3]) {
    iVar7 = (int)fStack_40 * 4;
    do {
      fVar2 = fStack_40;
      if ((int)state[0xd] <= iVar4) {
        return;
      }
      iVar5 = ui_mouse_inside_rect(&local_2c,0x11,0xf0);
      if ((char)iVar5 == '\0') {
        fStack_8 = 0.9;
        if (state[2] != fVar2) {
          fStack_8 = 0.7;
        }
      }
      else {
        fStack_8 = 1.0;
        state[1] = fVar2;
        iVar5 = input_primary_just_pressed();
        if ((char)iVar5 != '\0') {
          state[2] = fVar2;
        }
      }
      text = *(char **)((int)state[0xc] + iVar7);
      if (*text == '\\') {
        if (text[1] == 'g') {
          (*grim_interface_ptr->vtable->grim_set_color)(0.7,1.0,0.7,fStack_8);
          text = text + 2;
        }
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_8);
      }
      uVar6 = 0xffffffff;
      iVar5 = 0;
      pcVar8 = text;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      uVar6 = ~uVar6;
      fStack_4 = 0.0;
      if (0 < (int)uVar6) {
        pfVar12 = state + 4;
        do {
          if ((text[iVar5] == '\t') || (text[iVar5] == '\0')) {
            text[iVar5] = '\0';
            fStack_3c = (float)((int)*pfVar12 * (int)fStack_4);
            (*grim_interface_ptr->vtable->grim_draw_text_small)
                      ((float)(int)fStack_3c + local_2c + 8.0,local_28 + 2.0,text);
            fStack_4 = (float)((int)fStack_4 + 1);
            pfVar12 = pfVar12 + 1;
            text = text + iVar5 + 1;
            uVar6 = uVar6 - (iVar5 + 1);
            iVar5 = 0;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < (int)uVar6);
      }
      local_28 = local_28 + 16.0;
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + 4;
      fStack_40 = (float)((int)fStack_40 + 1);
    } while (iVar4 < (int)state[3]);
  }
  return;
}



/* ui_list_widget_update @ 0043efc0 */

/* draws a list widget and updates selection/hover state */

int __cdecl ui_list_widget_update(float *xy,char *list)

{
  float *xy_00;
  int iVar1;
  int iVar2;
  int iVar3;
  float unaff_EBX;
  int iVar4;
  IGrim2D_vtbl *pIVar5;
  char unaff_DI;
  int iVar6;
  longlong lVar7;
  float unaff_retaddr;
  char *xy_01;
  char *stage;
  float local_1c;
  float fStack_18;
  float fStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  xy_00 = xy;
  iVar4 = 0;
  iVar1 = ui_focus_update((int)list);
  iVar6 = 0;
  if (0 < *(int *)(list + 0x10)) {
    do {
      iVar2 = (*grim_interface_ptr->vtable->grim_measure_text_width)
                        (*(char **)(*(int *)(list + 0xc) + iVar6 * 4));
      if (iVar4 < iVar2) {
        iVar4 = iVar2;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)(list + 0x10));
  }
  if (*list == '\0') {
    local_1c = 16.0;
    list[0x14] = '\0';
    list[4] = '\0';
    list[5] = '\0';
    list[6] = '\0';
    list[7] = '\0';
    xy = (float *)(float)(iVar4 + 0x30);
  }
  else if (*(int *)(list + 4) < 1) {
    local_1c = 16.0;
    list[0x14] = '\0';
    xy = (float *)(float)(iVar4 + 0x30);
  }
  else {
    local_1c = (float)(*(int *)(list + 0x10) * 0x10 + 0x18);
    lVar7 = __ftol();
    iVar6 = (int)lVar7;
    lVar7 = __ftol();
    iVar6 = ui_mouse_inside_rect(xy,(int)lVar7,iVar6);
    list[0x14] = (char)iVar6;
    xy = (float *)(float)(iVar4 + 0x30);
  }
  if (list[0x14] != '\0') {
    ui_focus_set((int)list,'\0');
  }
  if ((char)iVar1 != '\0') {
    fStack_18 = *xy_00 - 16.0;
    fStack_14 = xy_00[1];
    ui_focus_draw(&fStack_18);
    iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(200);
    if ((char)iVar4 != '\0') {
      if (*(int *)(list + 4) == 0) {
        list[4] = '\x01';
        list[5] = '\0';
        list[6] = '\0';
        list[7] = '\0';
      }
      else {
        iVar4 = *(int *)(list + 0x18);
        *(int *)(list + 0x18) = iVar4 + -1;
        if (iVar4 + -1 < 0) {
          list[0x18] = '\0';
          list[0x19] = '\0';
          list[0x1a] = '\0';
          list[0x1b] = '\0';
        }
      }
    }
    iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd0);
    if ((char)iVar4 != '\0') {
      if (*(int *)(list + 4) == 0) {
        list[4] = '\x01';
        list[5] = '\0';
        list[6] = '\0';
        list[7] = '\0';
      }
      else {
        iVar4 = *(int *)(list + 0x18);
        *(int *)(list + 0x18) = iVar4 + 1;
        if (*(int *)(list + 0x10) + -1 < iVar4 + 1) {
          *(int *)(list + 0x18) = *(int *)(list + 0x10) + -1;
        }
      }
    }
  }
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0x3f800000;
  uStack_4 = 0x3f800000;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(xy_00,(float)xy,local_1c);
  local_1c = *xy_00 + 1.0;
  fStack_18 = xy_00[1] + 1.0;
  fStack_14 = 0.0;
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0x3f800000;
  xy_01 = (char *)&local_1c;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)
            ((float *)xy_01,unaff_retaddr - 2.0,unaff_EBX - 2.0);
  if ((*(int *)(list + 4) < 1) && (list[0x14] == '\0')) {
    stage = s_ui_dropOff_00474134;
    pIVar5 = grim_interface_ptr->vtable;
  }
  else {
    local_1c = xy_00[1] + 15.0;
    fStack_18 = 1.0;
    fStack_14 = 1.0;
    uStack_10 = 0x3f800000;
    uStack_c = 0x3f000000;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)((float *)&stack0xffffffe0,(float)xy,1.0);
    stage = (char *)0x0;
    xy_01 = s_ui_dropOn_00474158;
    pIVar5 = grim_interface_ptr->vtable;
  }
  iVar4 = (*pIVar5->grim_get_texture_handle)(xy_01);
  (*pIVar5->grim_bind_texture)(iVar4,(int)stage);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)
            (((local_1c + *xy_00) - 16.0) - 1.0,xy_00[1],16.0,16.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  iVar4 = -2;
  if (*list != '\0') {
    lVar7 = __ftol();
    iVar1 = ui_hit_test_rect(xy_00,0xe,(int)lVar7);
    if ((char)iVar1 != '\0') {
      iVar4 = -1;
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.95);
      goto LAB_0043f3aa;
    }
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.75);
LAB_0043f3aa:
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy_00 + 4.0,xy_00[1] + 1.0,&s_fmt_percent_s,
             *(undefined4 *)(*(int *)(list + 0xc) + *(int *)(list + 8) * 4));
  if (*(int *)(list + 4) < 1) {
    return iVar4;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
  iVar4 = 0;
  if (0 < *(int *)(list + 0x10)) {
    lVar7 = __ftol();
    iVar1 = (int)lVar7;
    iVar6 = 0;
    do {
      iVar2 = iVar6;
      iVar3 = ui_hit_test_rect((float *)&stack0xffffffbc,0xe,iVar1);
      if ((char)iVar3 == '\0') {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
      }
      else {
        *(int *)(list + 0x18) = iVar4;
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.95);
      }
      if ((unaff_DI != '\0') && (*(int *)(list + 0x18) == iVar4)) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.96);
      }
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,*xy_00 + 4.0,(float)iVar2 + xy_00[1] + 17.0,&s_fmt_percent_s,
                 *(undefined4 *)(*(int *)(list + 0xc) + iVar4 * 4));
      iVar4 = iVar4 + 1;
      iVar6 = iVar6 + 0x10;
    } while (iVar4 < *(int *)(list + 0x10));
  }
  if ((list[0x14] == '\0') && (unaff_DI == '\0')) {
    list[4] = '\0';
    list[5] = '\0';
    list[6] = '\0';
    list[7] = '\0';
  }
  return *(int *)(list + 0x18);
}



/* ui_stats_render_weapon_bar @ 004411c0 */

void ui_stats_render_weapon_bar(void)

{
  float *unaff_retaddr;
  
  (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&crt_sbh_header_pool);
  *unaff_retaddr = *unaff_retaddr - 16.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(unaff_retaddr,192.0,1.0);
  *unaff_retaddr = *unaff_retaddr + 16.0;
  unaff_retaddr[1] = unaff_retaddr[1] + 4.0;
  return;
}



/* ui_stats_render_row @ 00441220 */

void ui_stats_render_row(void)

{
  float *unaff_retaddr;
  
  (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&crt_sbh_header_pool);
  *unaff_retaddr = *unaff_retaddr - 16.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(unaff_retaddr,1.0,48.0);
  *unaff_retaddr = *unaff_retaddr + 16.0;
  return;
}



/* date_format_month_day @ 00441270 */

undefined * __cdecl date_format_month_day(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  
  switch(param_2) {
  case 1:
    puVar1 = &month_name_ptr_feb;
    break;
  case 2:
    puVar1 = &month_name_ptr_mar;
    break;
  case 3:
    puVar1 = &month_name_ptr_apr;
    break;
  case 4:
    puVar1 = &month_name_ptr_may;
    break;
  case 5:
    puVar1 = &month_name_ptr_jun;
    break;
  case 6:
    puVar1 = &month_name_ptr_jul;
    break;
  case 7:
    puVar1 = &month_name_ptr_aug;
    break;
  case 8:
    puVar1 = &month_name_ptr_sep;
    break;
  case 9:
    puVar1 = &month_name_ptr_oct;
    break;
  case 10:
    puVar1 = &month_name_ptr_nov;
    break;
  case 0xb:
    puVar1 = &month_name_ptr_dec;
    break;
  case 0xc:
    puVar1 = &month_name_ptr_13;
    break;
  default:
    puVar1 = &month_name_ptr_default;
  }
  crt_sprintf(&ui_date_format_buffer,s__d___s__d_00478878,param_1,puVar1);
  return &ui_date_format_buffer;
}



/* ui_update_notice_update @ 00442150 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the update-available notice and its button */

void __cdecl ui_update_notice_update(float *xy,float alpha)

{
  undefined4 *puVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  float local_4;
  
  local_4 = alpha * 0.8;
  puVar1 = &local_10;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(xy,266.0,76.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)xy);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(xy,266.0,76.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.2,0.2,1.0);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 12.0,xy[1] + 14.0,s_note_label,puVar1);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.8);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 60.0,xy[1] + 4.0,s_newer_version_available);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 60.0,xy[1] + 18.0,s_game_download_available);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 60.0,xy[1] + 32.0,&s_empty_string);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 60.0,xy[1] + 46.0,&s_empty_string);
  if ((ui_update_button_init_flag & 1) == 0) {
    ui_update_button_init_flag = ui_update_button_init_flag | 1;
    ui_update_button_enabled = 1;
    ui_update_button_visible = 0;
    ui_update_button_focus_idx = 0;
    ui_update_button_alpha = 0x3f800000;
    ui_update_button_hover_time = 0;
    ui_update_button_label = (char *)0x0;
    ui_update_button_reserved = 0;
    ui_update_button_pressed = '\0';
    ui_update_button_counter = 0;
    crt_atexit(&ui_update_button_cleanup_ptr);
  }
  ui_update_button_label = s_get_update_button;
  ui_button_update((float *)&stack0xffffffe4,(ui_button_t *)&ui_update_button_state);
  if (ui_update_button_pressed != '\0') {
    ui_update_button_clicked = 1;
  }
  return;
}



/* ui_profile_menu_update @ 004443c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4443c0(float* arg1, char arg2) */

int __cdecl ui_profile_menu_update(float *arg1,char arg2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint extraout_EAX;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char (*pacVar9) [27];
  char (*pacVar10) [27];
  int local_c;
  float local_8;
  float local_4;
  
  if ((ui_profile_init_flags & 1) == 0) {
    ui_profile_init_flags = ui_profile_init_flags | 1;
    ui_profile_alpha = 0x3f800000;
    ui_profile_list_ptr = &profile_name_buffer;
    ui_profile_list_index = 0;
    ui_profile_entry_size = 0x1b;
    ui_profile_list_height = 0x60;
    crt_atexit(&ui_profile_cleanup_ptr);
  }
  local_c = 0;
  if (0 < (int)config_blob.reserved0._132_4_) {
    piVar4 = &profile_name_ptr_array;
    iVar2 = 0x4803f0;
    local_c._0_1_ = config_blob.reserved0[0x84];
    local_c._1_1_ = config_blob.reserved0[0x85];
    local_c._2_1_ = config_blob.reserved0[0x86];
    local_c._3_1_ = config_blob.reserved0[0x87];
    iVar7 = config_blob.reserved0._132_4_;
    do {
      *piVar4 = iVar2;
      iVar2 = iVar2 + 0x1b;
      piVar4 = piVar4 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  pcVar3 = strdup_malloc(s_<add_new_named_list>_00478c6c);
  (&profile_name_ptr_array)[local_c] = pcVar3;
  if ((ui_profile_init_flags & 2) == 0) {
    ui_profile_init_flags = ui_profile_init_flags | 2;
    ui_profile_add_enabled = 1;
    ui_profile_add_visible = 0;
    ui_profile_add_focus_idx = 0;
    ui_profile_add_alpha = 0x3f800000;
    ui_profile_add_hover_time = 0;
    ui_profile_add_label = (undefined *)0x0;
    ui_profile_add_padding_a = 0;
    ui_profile_add_padding_b = 0;
    ui_profile_add_counter = 0;
    crt_atexit(&DAT_004447f0);
  }
  ui_profile_add_label = &DAT_00478c68;
  if ((ui_profile_init_flags & 4) == 0) {
    ui_profile_init_flags = ui_profile_init_flags | 4;
    ui_profile_delete_enabled = 1;
    ui_profile_delete_visible = 0;
    ui_profile_delete_focus_idx = 0;
    ui_profile_delete_alpha = 0x3f800000;
    ui_profile_delete_hover_time = 0;
    ui_profile_delete_label = (char *)0x0;
    ui_profile_delete_padding_a = 0;
    ui_profile_delete_padding_b = 0;
    ui_profile_delete_counter = 0;
    crt_atexit(&DAT_004447e0);
  }
  ui_profile_delete_label = s_Delete_00478c60;
  ui_profile_list_height = 0xae;
  if (profile_screen_add_mode == '\0') {
    if ((profile_screen_selection_idx != 0) || (config_blob.reserved0._128_4_ == 0)) goto LAB_004446ac;
    local_8 = *arg1;
    local_4 = arg1[1] + 22.0;
    iVar7 = ui_button_update(&local_8,(ui_button_t *)&DAT_004ccb00);
    if ((char)iVar7 == '\0') goto LAB_004446ac;
    uVar5 = 0xffffffff;
    pacVar9 = config_blob.saved_names + config_blob.reserved0._132_4_ + -1;
    do {
      pacVar10 = pacVar9;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pacVar10 = (char (*) [27])(*pacVar9 + 1);
      pcVar3 = *pacVar9;
      pacVar9 = pacVar10;
    } while (*pcVar3 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = (char *)((int)pacVar10 - uVar5);
    pacVar9 = config_blob.saved_names + config_blob.reserved0._128_4_;
    config_blob.reserved0._132_4_ = config_blob.reserved0._132_4_ + -1;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)*pacVar9 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pacVar9 = (char (*) [27])(*pacVar9 + 4);
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      (*pacVar9)[0] = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pacVar9 = (char (*) [27])(*pacVar9 + 1);
    }
    config_blob.reserved0[0x80] = '\0';
    config_blob.reserved0[0x81] = '\0';
    config_blob.reserved0[0x82] = '\0';
    config_blob.reserved0[0x83] = '\0';
  }
  else {
    local_8 = *arg1;
    local_4 = arg1[1] + 29.0;
    iVar7 = ui_text_input_update(&local_8,(int *)&DAT_004d0f28);
    if ((char)iVar7 == '\0') {
      local_8 = *arg1 + 180.0;
      local_4 = arg1[1] + 22.0;
      iVar7 = ui_button_update(&local_8,(ui_button_t *)&DAT_004ccc90);
      if ((char)iVar7 == '\0') goto LAB_004446ac;
    }
    uVar5 = 0xffffffff;
    pcVar3 = &profile_name_buffer;
    do {
      pcVar8 = pcVar3;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar8 = pcVar3 + 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar8;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar3 = pcVar8 + -uVar5;
    pacVar9 = config_blob.saved_names + config_blob.reserved0._132_4_;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)*pacVar9 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pacVar9 = (char (*) [27])(*pacVar9 + 4);
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      (*pacVar9)[0] = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pacVar9 = (char (*) [27])(*pacVar9 + 1);
    }
    config_blob.reserved0[0x80] = config_blob.reserved0[0x84];
    config_blob.reserved0[0x81] = config_blob.reserved0[0x85];
    config_blob.reserved0[0x82] = config_blob.reserved0[0x86];
    config_blob.reserved0[0x83] = config_blob.reserved0[0x87];
    config_blob.reserved0._132_4_ = config_blob.reserved0._132_4_ + 1;
    if (7 < (int)config_blob.reserved0._132_4_) {
      uVar5 = 0xffffffff;
      pcVar3 = &profile_name_buffer;
      do {
        pcVar8 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar8 + -uVar5;
      pacVar9 = config_blob.saved_names + 1;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)*pacVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pacVar9 = (char (*) [27])(*pacVar9 + 4);
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        (*pacVar9)[0] = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pacVar9 = (char (*) [27])(*pacVar9 + 1);
      }
      config_blob.reserved0._132_4_ = config_blob.reserved0._132_4_ + -1;
    }
    profile_name_buffer = 0;
    ui_profile_list_index = 0;
    profile_screen_add_mode = '\0';
  }
  highscore_load_table();
LAB_004446ac:
  if ((ui_profile_init_flags & 8) == 0) {
    ui_profile_init_flags = ui_profile_init_flags | 8;
    crt_exception_nesting = 1;
    _DAT_004d0f00 = 0;
    DAT_004d0efc = 0;
    _DAT_004d0ef0 = 0;
    _DAT_004d0eec = 0;
    _DAT_004d0ef8 = 0;
    _DAT_004d0ef4 = (undefined4 *)0x0;
    crt_atexit(&DAT_004447d0);
  }
  _DAT_004d0ef8 = local_c + 1;
  _DAT_004d0ef4 = &profile_name_ptr_array;
  crt_exception_nesting = arg2;
  crt_exception_filter = config_blob.reserved0[0x80];
  DAT_004d0ef0_1._0_1_ = config_blob.reserved0[0x81];
  DAT_004d0ef0_1._1_1_ = config_blob.reserved0[0x82];
  DAT_004d0ef0_1._2_1_ = config_blob.reserved0[0x83];
  iVar7 = ui_list_widget_update(arg1,&crt_exception_nesting);
  if ((-2 < iVar7) &&
     ((iVar2 = input_primary_just_pressed(), (char)iVar2 != '\0' ||
      (iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c), (char)iVar2 != '\0')))) {
    profile_screen_selection_idx = 1 - profile_screen_selection_idx;
    if (-1 < iVar7) {
      config_blob.reserved0._128_4_ = iVar7;
      _DAT_004d0ef0 = iVar7;
      if (iVar7 != local_c) {
        highscore_load_table();
      }
      DAT_004d1221 = 1;
      DAT_004d1222 = 1;
    }
    profile_screen_add_mode = iVar7 == local_c;
  }
  _DAT_004d0eec = profile_screen_selection_idx;
  crt_free((void *)(&profile_name_ptr_array)[local_c]);
  return extraout_EAX & 0xffffff00;
}



/* ui_back_button_callback @ 00446140 */

void ui_back_button_callback(void)

{
  return;
}



/* ui_get_element_index @ 00446150 */

/* returns index of element in ui_element_table_end list, or -1 */

int __cdecl ui_get_element_index(ui_element_t *element)

{
  int iVar1;
  ui_element_t **ppuVar2;
  
  iVar1 = 0;
  ppuVar2 = &ui_element_table_end;
  do {
    if (element == *ppuVar2) {
      return iVar1;
    }
    ppuVar2 = ppuVar2 + 1;
    iVar1 = iVar1 + 1;
  } while ((int)ppuVar2 < 0x48f20c);
  return -1;
}



/* ui_elements_reset_state @ 00446170 */

/* clears active flags and hover timers on all UI elements */

void ui_elements_reset_state(void)

{
  ui_element_t **ppuVar1;
  ui_element_t **ppuVar2;
  
  ppuVar1 = &ui_element_table_end;
  do {
    ppuVar2 = ppuVar1 + 1;
    (*ppuVar1)->active = '\0';
    (*ppuVar1)->counter_value = 0;
    ppuVar1 = ppuVar2;
  } while ((int)ppuVar2 < 0x48f20c);
  return;
}



/* ui_elements_max_timeline @ 00446190 */

/* returns max timeline value (element +0x10) among active UI elements */

int ui_elements_max_timeline(void)

{
  int iVar1;
  int iVar2;
  ui_element_t **ppuVar3;
  
  iVar2 = 0;
  ppuVar3 = &ui_element_table_end;
  do {
    if (((*ppuVar3)->active != '\0') && (iVar1 = *(int *)((*ppuVar3)->_pad0 + 0xe), iVar2 < iVar1))
    {
      iVar2 = iVar1;
    }
    ppuVar3 = ppuVar3 + 1;
  } while ((int)ppuVar3 < 0x48f20c);
  return iVar2;
}



/* game_state_set @ 004461c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* resets UI state, updates game_state_prev/id, and seeds UI elements for the new state */

void __cdecl game_state_set(int state_id)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  ui_element_t *puVar6;
  float fVar7;
  uint auStack_10 [4];
  
  iVar1 = state_id;
  ui_elements_reset_state();
  game_paused_flag = 0;
  game_state_prev = game_state_id;
  game_state_id = state_id;
  ui_state_phase = 0;
  ui_state_init_flag = 0;
  (*grim_interface_ptr->vtable->grim_flush_input)();
  console_input_poll();
  if (state_id == 0) {
    highscore_return_latch = '\0';
    render_pass_mode = '\0';
    ui_sign_crimson = 1;
    iVar3 = game_is_full_version();
    if ((char)iVar3 != '\0') {
      bVar2 = mods_any_available();
      if (bVar2) {
        ui_button_visible_flag = 1;
      }
    }
    iVar3 = game_is_full_version();
    if ((char)iVar3 == '\0') {
      ui_button_visible_flag = 1;
    }
    else {
      main_menu_version_callback = &LAB_00447350;
    }
    state_id = 0;
    iVar3 = 2;
    do {
      if (iVar3 == 2) {
        iVar4 = game_is_full_version();
        if ((char)iVar4 != '\0') {
          state_id = 4;
        }
      }
      pcVar5 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_10,100);
      if (*pcVar5 == '\0') {
        if (iVar3 == 6) {
          state_id = 6;
        }
        (&ui_element_table_end)[iVar3]->counter_id = ui_button_texture_id;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x14] = '\0';
        puVar6->_pad4[0x15] = '\0';
        puVar6->_pad4[0x16] = '\0';
        puVar6->_pad4[0x17] = '\0';
        *(float *)(puVar6->_pad4 + 0x18) = (float)state_id * 0.125;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x30] = '\0';
        puVar6->_pad4[0x31] = '\0';
        puVar6->_pad4[0x32] = 0x80;
        puVar6->_pad4[0x33] = '?';
        *(float *)(puVar6->_pad4 + 0x34) = (float)state_id * 0.125;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x4c] = '\0';
        puVar6->_pad4[0x4d] = '\0';
        puVar6->_pad4[0x4e] = 0x80;
        puVar6->_pad4[0x4f] = '?';
        fVar7 = (float)(state_id + 1) * 0.125;
        *(float *)(puVar6->_pad4 + 0x50) = fVar7;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x68] = '\0';
        puVar6->_pad4[0x69] = '\0';
        puVar6->_pad4[0x6a] = '\0';
        puVar6->_pad4[0x6b] = '\0';
      }
      else {
        (&ui_element_table_end)[iVar3]->counter_id = ui_button_texture_id;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x14] = '\0';
        puVar6->_pad4[0x15] = '\0';
        puVar6->_pad4[0x16] = '\0';
        puVar6->_pad4[0x17] = '\0';
        *(float *)(puVar6->_pad4 + 0x18) = (float)state_id * 0.125;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x30] = '\0';
        puVar6->_pad4[0x31] = '\0';
        puVar6->_pad4[0x32] = 0x80;
        puVar6->_pad4[0x33] = '?';
        *(float *)(puVar6->_pad4 + 0x34) = (float)state_id * 0.125;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x4c] = '\0';
        puVar6->_pad4[0x4d] = '\0';
        puVar6->_pad4[0x4e] = 0x80;
        puVar6->_pad4[0x4f] = '?';
        fVar7 = (float)(state_id + 1) * 0.125;
        *(float *)(puVar6->_pad4 + 0x50) = fVar7;
        puVar6 = (&ui_element_table_end)[iVar3];
        puVar6->_pad4[0x68] = '\0';
        puVar6->_pad4[0x69] = '\0';
        puVar6->_pad4[0x6a] = '\0';
        puVar6->_pad4[0x6b] = '\0';
      }
      *(float *)(puVar6->_pad4 + 0x6c) = fVar7;
      if (iVar3 == 2) {
        iVar4 = game_is_full_version();
        if ((char)iVar4 != '\0') {
          state_id = 0;
        }
      }
      iVar4 = state_id + 1;
      if (iVar4 == 4) {
        iVar4 = state_id + 2;
      }
      iVar3 = iVar3 + 1;
      state_id = iVar4;
    } while (iVar3 < 8);
    iVar3 = game_is_full_version();
    if ((char)iVar3 == '\0') {
      ui_button_visible_flag = 1;
    }
    ui_elem_flag_a = 1;
    ui_elem_flag_b = 1;
    ui_elem_flag_c = 1;
    ui_elem_flag_d = 1;
    pcVar5 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_10,100);
    if (*pcVar5 == '\0') {
      ui_elem_flag_d = 0;
    }
    ui_main_menu_initialized = 1;
  }
  else if (state_id == 0x16) {
    render_pass_mode = '\0';
    ui_sign_crimson_update_disabled = 0;
  }
  else if (state_id == 9) {
    ui_gameplay_menu_initialized = 1;
    screen_fade_in_flag = 0;
    if (render_pass_mode == '\0') {
      highscore_return_latch = '\0';
      gameplay_reset_state();
      iVar4 = quest_stage_minor;
      iVar3 = quest_stage_major;
      if (config_blob.reserved0._24_4_ == 3) {
        game_status_blob.quest_play_counts[quest_stage_minor + quest_stage_major * 10] =
             game_status_blob.quest_play_counts[quest_stage_minor + quest_stage_major * 10] + 1;
        quest_start_selected(iVar3,iVar4);
        render_pass_mode = '\x01';
        ui_state_init_flag = 1;
      }
      else if (config_blob.reserved0._24_4_ == 2) {
        render_pass_mode = '\x01';
        game_status_blob.mode_play_rush = game_status_blob.mode_play_rush + 1;
        ui_state_init_flag = 1;
      }
      else if (config_blob.reserved0._24_4_ == 1) {
        render_pass_mode = '\x01';
        game_status_blob.mode_play_survival = game_status_blob.mode_play_survival + 1;
        ui_state_init_flag = 1;
      }
      else if (config_blob.reserved0._24_4_ == 4) {
        render_pass_mode = '\x01';
        game_status_blob.mode_play_typo = game_status_blob.mode_play_typo + 1;
        ui_state_init_flag = 1;
      }
      else {
        render_pass_mode = '\x01';
        game_status_blob.mode_play_other = game_status_blob.mode_play_other + 1;
        ui_state_init_flag = 1;
      }
    }
  }
  else if (state_id == 0x12) {
    config_blob.reserved0[0x14] = '\x01';
    config_blob.reserved0[0x15] = '\0';
    config_blob.reserved0[0x16] = '\0';
    config_blob.reserved0[0x17] = '\0';
    creature_name_input_reset = 1;
    ui_gameplay_menu_initialized = 1;
    screen_fade_in_flag = 0;
    if (render_pass_mode == '\0') {
      highscore_return_latch = '\0';
      gameplay_reset_state();
      render_pass_mode = '\x01';
      ui_state_init_flag = 1;
    }
  }
  else if (state_id == 1) {
    ui_sign_crimson = 1;
    menu_screen_options = 1;
    menu_screen_main = 1;
  }
  else if (state_id == 2) {
    if (ui_splash_skip_flag == '\0') {
      ui_sign_crimson = 1;
    }
    menu_screen_extras = 1;
    ui_list_scroll_b = 0xc2680000;
    menu_screen_credits = 1;
    ui_screen_phase = 0;
    ui_list_scroll_a = (((float)config_blob.screen_width * 0.0015625 * 150.0 + 10.0) - 150.0) + 135.0;
  }
  else if (state_id == 4) {
    highscore_return_latch = '\0';
    ui_sign_crimson = 1;
    menu_screen_highscore = 1;
    _DAT_0048e858 = &LAB_0043f550;
  }
  else if (state_id == 0xd) {
    ui_screen_update_callback = ui_back_button_callback;
LAB_00446764:
    ui_credits_active_flag._0_1_ = 1;
    ui_sign_crimson = 1;
    highscore_load_table();
  }
  else if (state_id == 3) {
    ui_sign_crimson = 1;
    ui_list_scroll_b = 0xc3340000;
    menu_screen_quest = 1;
    menu_screen_survival = 1;
    ui_credits_element_start._0_1_ = 1;
    ui_list_scroll_a = ((float)config_blob.screen_width * 0.0015625 * 150.0 - 150.0) + 139.0;
  }
  else if (state_id == 0xe) {
    crt_file_lock_table = 1;
    ui_screen_update_callback = (code *)&LAB_004423d0;
    goto LAB_00446764;
  }
  _DAT_0048a130 = 0;
  if (iVar1 == 0x13) {
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
  }
  else if (iVar1 == 0x1a) {
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
    ui_screen_update_callback = credits_secret_alien_zookeeper_update;
  }
  else if (iVar1 == 0x14) {
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
    ui_screen_update_callback = (code *)&LAB_0040e9a0;
  }
  else if (iVar1 == 0xf) {
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
    crt_file_lock_table = 1;
    ui_screen_update_callback = (code *)&LAB_00440110;
  }
  else if (iVar1 == 0x10) {
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
    crt_file_lock_table = 1;
    ui_screen_update_callback = (code *)&LAB_00440960;
  }
  else if (iVar1 == 0x11) {
    ui_screen_phase = 0;
    ui_sign_crimson = 1;
    ui_credits_active_flag._0_1_ = 1;
    ui_screen_update_callback = credits_screen_update;
  }
  else if (iVar1 == 0xb) {
    ui_sign_crimson = 1;
    ui_menu_active_flag_b = 1;
  }
  else if (iVar1 == 5) {
    if (ui_splash_skip_flag == '\0') {
      ui_sign_crimson = 1;
    }
    ui_sign_crimson_update_disabled = 0;
    ui_menu_options_flags_a = 1;
    ui_menu_options_flags_b = 1;
    ui_menu_options_flags_c = 1;
  }
  else if (iVar1 == 6) {
    ui_menu_game_over_flag = 1;
  }
  else if (iVar1 == 8) {
    ui_menu_highscore_active = 1;
    game_save_status();
    ui_screen_phase = -2;
  }
  else {
    if (iVar1 == 0x15) {
      ui_menu_highscore_active = 1;
    }
    else if (iVar1 == 0xc) {
      ui_menu_highscore_active = 1;
    }
    else {
      if (iVar1 != 7) goto LAB_004468da;
      ui_menu_ingame_flag = 1;
      _DAT_00487260 = 0;
    }
    ui_screen_phase = -1;
  }
LAB_004468da:
  if (highscore_return_latch != '\0') {
    ui_sign_crimson = 0;
  }
  ui_elements_timeline = 0;
  ui_transition_direction = 1;
  return;
}



/* renderer_get_vtable_entry @ 00447c90 */

/* [binja] int32_t sub_447c90(int32_t arg1) */

int __cdecl renderer_get_vtable_entry(int arg1)

{
  switch(arg1) {
  case 0:
    return 0x478f10;
  case 1:
    return 0x478ef4;
  case 2:
    return 0x478ee8;
  case 3:
    return 0x478f00;
  case 4:
    return 0x478ed8;
  case 5:
    return 0x478ecc;
  default:
    return 0x4714a0;
  }
}



/* renderer_dispatch_a @ 004530c1 */

void renderer_dispatch_a(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)renderer_vtable_func_a)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_d @ 0045315a */

/* [binja] int32_t sub_45315a() */

int renderer_dispatch_d(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00453161. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)renderer_vtable_func_b)();
  return iVar1;
}



/* renderer_dispatch_b @ 00453245 */

void renderer_dispatch_b(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)renderer_vtable_func_c)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_c @ 00453340 */

void renderer_dispatch_c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)renderer_vtable_func_d)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_call_0x08 @ 00453464 */

/* [binja] int32_t sub_453464() */

int renderer_dispatch_call_0x08(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x0045346b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR_FUN_004795c8)();
  return iVar1;
}



/* renderer_dispatch_call_0x0c @ 004534ea */

/* [binja] int32_t sub_4534ea() */

int renderer_dispatch_call_0x0c(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x004534f5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR_FUN_004795d8)();
  return iVar1;
}



/* renderer_dispatch_mat_lerp @ 00453711 */

void renderer_dispatch_mat_lerp(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_00479674)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_build_axes @ 0045382e */

void renderer_dispatch_build_axes(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_00479678)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_call_0x14 @ 00453a57 */

/* [binja] int32_t sub_453a57() */

int renderer_dispatch_call_0x14(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00453a5e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR_FUN_004795ac)();
  return iVar1;
}



/* renderer_dispatch_call_0x1c @ 00453ca0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_453ca0() */

int renderer_dispatch_call_0x1c(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00453ca7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x10)();
  return iVar1;
}



/* renderer_dispatch_call_0x22 @ 00453f63 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_453f63() */

int renderer_dispatch_call_0x22(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00453f6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x00)();
  return iVar1;
}



/* renderer_dispatch_set_color_ptr @ 00454303 */

/* [binja] int32_t __stdcall sub_454303(float arg1, float arg2, float arg3); wrapper calls
   PTR_FUN_00479624 (idx 0x21) */

float * renderer_dispatch_set_color_ptr(float *arg1,float arg2,float arg3,float arg4)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479624)(arg1,arg2,arg3,arg4);
  return pfVar1;
}



/* renderer_dispatch_draw_rect @ 0045438d */

/* [binja] int32_t __stdcall sub_45438d(float arg1, float arg2, float arg3); wrapper calls
   PTR_FUN_00479608 (idx 0x1a) */

float * renderer_dispatch_draw_rect(float *arg1,float arg2,float arg3,float arg4)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479608)(arg1,arg2,arg3,arg4);
  return pfVar1;
}



/* renderer_dispatch_set_rotation_x @ 00454417 */

/* [binja] int32_t __stdcall sub_454417(float arg1); wrapper calls PTR_FUN_00479618 (idx 0x1e) */

float * renderer_dispatch_set_rotation_x(float *arg1,float arg2)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479618)(arg1,arg2);
  return pfVar1;
}



/* renderer_dispatch_set_rotation_y @ 004544ad */

/* [binja] int32_t __stdcall sub_4544ad(float arg1); wrapper calls PTR_FUN_0047961c (idx 0x1f) */

float * renderer_dispatch_set_rotation_y(float *arg1,float arg2)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_0047961c)(arg1,arg2);
  return pfVar1;
}



/* renderer_dispatch_rotate_y @ 00454544 */

/* [binja] int32_t __stdcall sub_454544(float arg1); wrapper calls PTR_FUN_00479620 (idx 0x20) */

float * renderer_dispatch_rotate_y(float *arg1,float arg2)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479620)(arg1,arg2);
  return pfVar1;
}



/* renderer_dispatch_scale_translate @ 004545dc */

/* [binja] int32_t __stdcall sub_4545dc(int arg1, float arg2); wrapper calls PTR_FUN_00479648 (idx
   0x2a) */

float * renderer_dispatch_scale_translate(float *arg1,float *arg2,float arg3)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_00479648)(arg1,arg2,arg3);
  return pfVar1;
}



/* renderer_dispatch_call_0x20 @ 004546fe */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4546fe() */

int renderer_dispatch_call_0x20(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00454705. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x14)();
  return iVar1;
}



/* renderer_dispatch_get_state @ 00454821 */

/* [binja] int32_t sub_454821() */

int renderer_dispatch_get_state(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x0045482c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)PTR_FUN_0047963c)();
  return iVar1;
}



/* renderer_dispatch_draw_prim @ 00454832 */

void renderer_dispatch_draw_prim(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_00479644)(param_1,param_2,param_3,param_4,param_5);
  return;
}



/* renderer_dispatch_draw_indexed @ 00454859 */

undefined4 *
renderer_dispatch_draw_indexed(undefined4 *param_1,undefined4 param_2,float *param_3,int param_4,float *param_5)

{
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
  *param_1 = param_2;
  param_1[5] = param_2;
  param_1[10] = param_2;
  param_1[0xf] = 0x3f800000;
  if (param_4 != 0) {
    thunk_renderer_dispatch_call_0x20();
    if (param_3 == (float *)0x0) {
      thunk_renderer_dispatch_call_0x14();
    }
    else {
      param_1[0xc] = (float)param_1[0xc] - *param_3;
      param_1[0xd] = (float)param_1[0xd] - param_3[1];
      param_1[0xe] = (float)param_1[0xe] - param_3[2];
      thunk_renderer_dispatch_call_0x14();
      param_1[0xc] = *param_3 + (float)param_1[0xc];
      param_1[0xd] = (float)param_1[0xd] + param_3[1];
      param_1[0xe] = param_3[2] + (float)param_1[0xe];
    }
  }
  if (param_5 != (float *)0x0) {
    param_1[0xc] = *param_5 + (float)param_1[0xc];
    param_1[0xd] = param_5[1] + (float)param_1[0xd];
    param_1[0xe] = param_5[2] + (float)param_1[0xe];
  }
  return param_1;
}



/* renderer_dispatch_call_0x2a @ 00454e3c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_454e3c() */

int renderer_dispatch_call_0x2a(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00454e43. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x18)();
  return iVar1;
}



/* renderer_dispatch_call_0x33 @ 00454f03 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_454f03() */

int renderer_dispatch_call_0x33(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00454f03. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x24)();
  return iVar1;
}



/* renderer_dispatch_call_0x34 @ 00454f87 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_454f87() */

int renderer_dispatch_call_0x34(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00454f87. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x28)();
  return iVar1;
}



/* renderer_dispatch_mat_lerp @ 00455028 */

/* [binja] int32_t __stdcall sub_455028(int arg1, int arg2, float arg3); wrapper calls
   PTR_FUN_0047962c (idx 0x23) */

float * renderer_dispatch_mat_lerp(float *arg1,float *arg2,float *arg3,float arg4)

{
  float *pfVar1;
  
  renderer_select_backend(1);
  pfVar1 = (float *)(*(code *)PTR_FUN_0047962c)(arg1,arg2,arg3,arg4);
  return pfVar1;
}



/* renderer_dispatch_call_0x2b @ 00455135 */

void renderer_dispatch_call_0x2b(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  renderer_select_backend(1);
  (*(code *)PTR_FUN_0047964c)(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



/* renderer_dispatch_call_0x2d @ 004551b6 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4551b6() */

int renderer_dispatch_call_0x2d(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x004551c1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*ptr_renderer_fn_0x1c)();
  return iVar1;
}



/* renderer_init_backend_1 @ 00455281 */

/* [binja] int32_t sub_455281() */

int renderer_init_backend_1(void)

{
  int iVar1;
  
  renderer_select_backend(1);
                    /* WARNING: Could not recover jumptable at 0x00455288. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*(code *)renderer_backend_vtable_ptr)();
  return iVar1;
}



/* renderer_select_backend @ 004566d3 */

/* selects renderer table based on config */

int renderer_select_backend(int reset)

{
  uint uVar1;
  int iVar2;
  undefined **ppuVar3;
  undefined **ppuVar4;
  
  if (reset == 0) {
    renderer_mode_id = 0xffff;
    ppuVar3 = &PTR_FUN_00479688;
    ppuVar4 = &PTR_LAB_004795a0;
    for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
      *ppuVar4 = *ppuVar3;
      ppuVar3 = ppuVar3 + 1;
      ppuVar4 = ppuVar4 + 1;
    }
  }
  else if (renderer_mode_id == 0xffff) {
    renderer_mode_id = 0;
    ppuVar3 = &PTR_FUN_00479688;
    ppuVar4 = &PTR_LAB_004795a0;
    for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
      *ppuVar4 = *ppuVar3;
      ppuVar3 = ppuVar3 + 1;
      ppuVar4 = ppuVar4 + 1;
    }
    FUN_00457127(&PTR_LAB_004795a0);
    iVar2 = FUN_004564e6(4,"DisableD3DXPSGP",(LPBYTE)&reset);
    if (iVar2 == 0) {
      reset = 0;
    }
    if (reset != 1) {
      uVar1 = crt_get_os_version_flag(7);
      if (uVar1 == 0) {
        uVar1 = crt_get_os_version_flag(10);
        if (uVar1 == 0) {
          uVar1 = crt_get_os_version_flag(6);
          if (uVar1 != 0) {
            renderer_3dnow_vtable_setup(&PTR_LAB_004795a0);
            renderer_mode_id = 3;
          }
        }
        else {
          renderer_sse2_vtable_setup(&PTR_LAB_004795a0);
          renderer_mode_id = 2;
        }
      }
      else {
        renderer_sse_vtable_setup(&PTR_LAB_004795a0);
        renderer_mode_id = 1;
      }
    }
  }
  return renderer_mode_id;
}



/* renderer_3dnow_vtable_setup @ 004567b0 */

void __cdecl renderer_3dnow_vtable_setup(undefined4 *param_1)

{
  param_1[0x1c] = &LAB_00457e90;
  *param_1 = mat4x4_transform_vec2;
  param_1[0xd] = &LAB_00457c10;
  param_1[0x1b] = &LAB_00457d00;
  param_1[0xb] = &LAB_00458e20;
  param_1[0x30] = &LAB_00457af0;
  param_1[0x2f] = &LAB_00457710;
  param_1[0x11] = &LAB_004579b0;
  param_1[0x36] = &LAB_00457aa0;
  param_1[0x35] = &LAB_004577a0;
  param_1[0x34] = &LAB_00457910;
  param_1[0x33] = &LAB_00457a40;
  param_1[0x32] = &LAB_00457650;
  param_1[0x31] = &LAB_00457850;
  param_1[0x12] = &LAB_00458840;
  param_1[0x16] = &LAB_00457b50;
  param_1[0x19] = &LAB_00458230;
  param_1[0x18] = &LAB_00458110;
  param_1[0x13] = &LAB_00457f70;
  param_1[0x2c] = &LAB_004580a0;
  param_1[0x14] = &LAB_00458000;
  param_1[0x10] = &LAB_00457500;
  param_1[0x15] = &LAB_00457420;
  param_1[8] = &LAB_004575b0;
  param_1[7] = &LAB_00457350;
  param_1[10] = &LAB_00457250;
  param_1[9] = mat4x4_transform_vec2_proj;
  param_1[6] = &LAB_00458300;
  param_1[5] = &LAB_00457210;
  param_1[4] = &LAB_00458b00;
  param_1[3] = &LAB_00458540;
  param_1[2] = &LAB_00458480;
  param_1[1] = &LAB_004583c0;
  return;
}



/* renderer_sse2_vtable_setup @ 004568c0 */

void __cdecl renderer_sse2_vtable_setup(undefined4 *param_1)

{
  param_1[0x1c] = &LAB_00459170;
  *param_1 = mat4x4_transform_vec2;
  param_1[0xd] = &LAB_00458ef0;
  param_1[0x1b] = &LAB_00458fe0;
  param_1[0xb] = &LAB_00458e20;
  param_1[0x30] = &LAB_00457af0;
  param_1[0x2f] = &LAB_00457710;
  param_1[0x11] = &LAB_004579b0;
  param_1[0x36] = &LAB_00457aa0;
  param_1[0x35] = &LAB_004577a0;
  param_1[0x34] = &LAB_00457910;
  param_1[0x33] = &LAB_00457a40;
  param_1[0x32] = &LAB_00457650;
  param_1[0x31] = &LAB_00457850;
  param_1[0x12] = &LAB_00458840;
  param_1[0x16] = &LAB_00457b50;
  param_1[0x19] = &LAB_00459370;
  param_1[0x18] = &LAB_00459250;
  param_1[0x1f] = &LAB_00458d90;
  param_1[0x1e] = &LAB_00458d10;
  param_1[0x13] = &LAB_00457f70;
  param_1[0x14] = &LAB_00458000;
  param_1[0x10] = &LAB_00458c60;
  param_1[0x15] = &LAB_00458760;
  param_1[8] = &LAB_004575b0;
  param_1[7] = &LAB_00458690;
  param_1[10] = &LAB_00457250;
  param_1[9] = mat4x4_transform_vec2_proj;
  param_1[6] = &LAB_00458300;
  param_1[5] = &LAB_00457210;
  param_1[4] = &LAB_00458b00;
  param_1[3] = &LAB_00458540;
  param_1[2] = &LAB_00458480;
  param_1[1] = &LAB_004583c0;
  return;
}



/* renderer_sse_vtable_setup @ 00456aa5 */

void __cdecl renderer_sse_vtable_setup(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = cpu_features_get();
  if (((uVar1 & 0x20) != 0) && ((char)uVar1 < '\0')) {
    *param_1 = &LAB_0045f218;
    param_1[1] = &LAB_0045e75a;
    param_1[2] = &LAB_0045f4d9;
    param_1[3] = &LAB_0045a9aa;
    param_1[5] = &LAB_0045f26d;
    param_1[6] = &LAB_0045e7cb;
    param_1[7] = quat_normalize_simd;
    param_1[8] = &LAB_0045f55b;
    param_1[9] = &LAB_0045f2a6;
    param_1[10] = &LAB_0045ed12;
    param_1[0xb] = &LAB_0045abdc;
    param_1[0xc] = &LAB_0045f903;
    param_1[0xd] = &LAB_0045f946;
    param_1[0xe] = vec3_project;
    param_1[0xf] = vec3_unproject;
    param_1[0x10] = &LAB_0045f5ba;
    param_1[0x11] = &LAB_0045f30a;
    param_1[0x12] = &LAB_0045e73e;
    param_1[0x13] = &LAB_00459440;
    param_1[0x14] = &LAB_004594d9;
    param_1[0x15] = vec2_normalize_simd;
    param_1[0x16] = &LAB_0045fa2a;
    param_1[0x17] = FUN_00459536;
    param_1[0x18] = &LAB_004595e9;
    param_1[0x19] = &LAB_00459a1a;
    param_1[0x1a] = &LAB_0045acab;
    param_1[0x1b] = &LAB_0045acfb;
    param_1[0x1c] = &LAB_0045ade6;
    param_1[0x1d] = FUN_00459adf;
    param_1[0x1e] = &LAB_0045aec2;
    param_1[0x1f] = &LAB_0045af25;
    param_1[0x20] = &LAB_0045af83;
    param_1[0x21] = &LAB_0045afdc;
    param_1[0x22] = &LAB_0045fb4c;
    param_1[0x23] = vec3_slerp;
    param_1[0x24] = FUN_00459c82;
    param_1[0x25] = &LAB_0045b023;
    param_1[0x26] = &LAB_0045b0cb;
    param_1[0x27] = FUN_0045b252;
    param_1[0x28] = mat3x3_from_euler_simd;
    param_1[0x29] = &LAB_0045c58f;
    param_1[0x2a] = mat3x3_from_axis_angle_simd;
    param_1[0x2b] = FUN_00459d0f;
    param_1[0x2c] = &LAB_00459da1;
    param_1[0x36] = &LAB_0045f6ec;
    param_1[0x33] = &LAB_0045e891;
    param_1[0x30] = &LAB_0045f3a2;
    param_1[0x2e] = &LAB_0045f3eb;
    param_1[0x34] = &LAB_0045f75d;
    param_1[0x31] = &LAB_0045e902;
    param_1[0x37] = FUN_00459e05;
    param_1[0x38] = &LAB_00459eac;
    param_1[0x35] = &LAB_0045f825;
    param_1[0x2f] = &LAB_0045f42e;
    param_1[0x32] = &LAB_0045e9d6;
    param_1[4] = &LAB_0045e012;
    param_1[0x2d] = FUN_00459f51;
    if (((uVar1 & 0x100) != 0) && ((uVar1 & 0x200) != 0)) {
      param_1[0xf] = vec_unproject_simd;
      param_1[0x12] = mat4_invert_simd;
      param_1[0x26] = &LAB_0045b19d;
      param_1[0x27] = mat_transform_compose_simd;
      param_1[0x18] = &LAB_00459805;
    }
  }
  return;
}


