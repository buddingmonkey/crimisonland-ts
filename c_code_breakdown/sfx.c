/* sfx_entry_init @ 0043b810 */

/* [binja] void* __fastcall sub_43b810(void* arg1) */

void * __fastcall sfx_entry_init(void *arg1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0x10;
  *(undefined4 *)((int)arg1 + 0x80) = 0;
  *(undefined4 *)((int)arg1 + 0x7c) = 0;
  *(undefined4 *)((int)arg1 + 0x78) = 0;
  *(undefined4 *)((int)arg1 + 0x74) = 0;
  *(undefined4 *)((int)arg1 + 0x14) = 0;
  *(undefined4 *)((int)arg1 + 0x18) = 0;
  *(undefined4 *)((int)arg1 + 0x1c) = 0;
  *(undefined4 *)((int)arg1 + 0x20) = 0xbf800000;
  puVar1 = (undefined4 *)((int)arg1 + 0x60);
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return arg1;
}



/* sfx_entry_load_ogg @ 0043bcf0 */

/* loads an OGG sample into an sfx entry */

int __cdecl sfx_entry_load_ogg(void *entry,byte *path)

{
  FILE *pFVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  uint unaff_EDI;
  char *dst;
  void *local_314;
  undefined1 local_310 [740];
  uint local_2c;
  uint local_1c;
  int local_18;
  
  iVar2 = resource_open_read(path,(int *)&local_314);
  pFVar1 = resource_fp;
  if ((char)iVar2 == '\0') {
    return iVar2;
  }
  pvVar3 = operator_new((int)local_314 + 8);
  crt_fread((char *)((int)pvVar3 + 8),(uint)local_314,1,(int *)pFVar1);
  resource_close();
  iVar2 = vorbis_mem_open(local_310,pvVar3,local_314,unaff_EDI);
  if ((char)iVar2 != '\0') {
    *(undefined4 *)entry = 0;
    *(undefined4 *)((int)entry + 4) = 0;
    *(undefined4 *)((int)entry + 8) = 0;
    *(undefined4 *)((int)entry + 0xc) = 0;
    *(undefined2 *)((int)entry + 0x10) = 0;
    *(short *)((int)entry + 2) = (short)local_1c;
    *(undefined2 *)entry = 1;
    uVar4 = (int)((local_1c & 0xffff) * 0x10) >> 3;
    *(short *)((int)entry + 0xc) = (short)uVar4;
    *(uint *)((int)entry + 8) = (uVar4 & 0xffff) * local_18;
    *(int *)((int)entry + 4) = local_18;
    *(undefined2 *)((int)entry + 0xe) = 0x10;
    *(undefined2 *)((int)entry + 0x10) = 0;
    *(uint *)((int)entry + 0x18) = local_2c;
    pvVar3 = operator_new(local_2c);
    dst = *(char **)((int)entry + 0x18);
    *(void **)((int)entry + 0x14) = pvVar3;
    iVar2 = 1;
    while ((dst != (char *)0x0 && (iVar2 != 0))) {
      iVar2 = vorbis_read_pcm16(local_310,
                                (void *)((*(int *)((int)entry + 0x18) - (int)dst) +
                                        *(int *)((int)entry + 0x14)),dst,unaff_EDI);
      dst = dst + -iVar2;
    }
    vorbis_mem_close(local_310);
    iVar2 = sfx_entry_create_buffers((int)entry);
    return CONCAT31((int3)((uint)iVar2 >> 8),(char)iVar2 != '\0');
  }
  return iVar2;
}



/* sfx_entry_seek @ 0043be20 */

/* seeks streaming sfx data and resets playback cursors */

void __cdecl sfx_entry_seek(int entry,int sample_offset)

{
  int *sample_offset_00;
  
  if (*(int *)(entry + 0x74) != 0) {
    sample_offset_00 = *(int **)(entry + 0x24);
    (**(code **)(*sample_offset_00 + 0x34))(sample_offset_00,sample_offset);
    vorbis_pcm_seek(*(void **)(entry + 0x74),(void *)sample_offset,(uint)sample_offset_00);
    *(undefined4 *)(entry + 0x1c) = 0;
    *(undefined4 *)(entry + 0x78) = 0;
    *(undefined4 *)(entry + 0x7c) = 0;
    *(undefined4 *)(entry + 0x80) = 0;
  }
  return;
}



/* sfx_entry_start_playback @ 0043be60 */

/* selects a voice/buffer and starts playback */

int __cdecl sfx_entry_start_playback(int entry)

{
  int *piVar1;
  int entry_00;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  entry_00 = entry;
  if (entry == 0) {
    return -1;
  }
  piVar3 = (int *)(entry + 0x24);
  iVar2 = dsound_restore_buffer(*(void **)(entry + 0x24));
  if ((char)iVar2 != '\0') {
    if (*(int *)(entry_00 + 0x74) != 0) goto LAB_0043be9c;
    sfx_entry_upload_buffer(entry_00);
  }
  if (*(int *)(entry_00 + 0x74) == 0) {
    uVar4 = 0;
    do {
      piVar1 = (int *)*piVar3;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x24))(piVar1,&entry);
        if ((entry & 1U) == 0) goto LAB_0043bf10;
      }
      uVar4 = uVar4 + 1;
      piVar3 = piVar3 + 1;
    } while ((int)uVar4 < 0x10);
    uVar4 = crt_rand();
    uVar4 = uVar4 & 0x8000000f;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffff0) + 1;
    }
    piVar3 = *(int **)(entry_00 + 0x24 + uVar4 * 4);
    (**(code **)(*piVar3 + 0x48))(piVar3);
LAB_0043bf10:
    piVar3 = *(int **)(entry_00 + 0x24 + uVar4 * 4);
    (**(code **)(*piVar3 + 0x44))(piVar3,sfx_rate_scale);
    piVar3 = *(int **)(entry_00 + 0x24 + uVar4 * 4);
    (**(code **)(*piVar3 + 0x30))(piVar3,0,0,0);
    return uVar4;
  }
LAB_0043be9c:
  sfx_entry_seek(entry_00,0);
  music_stream_fill(entry_00);
  music_stream_fill(entry_00);
  music_stream_fill(entry_00);
  (**(code **)(*(int *)*piVar3 + 0x30))((int *)*piVar3,0,0,1);
  return 0;
}



/* sfx_entry_resume @ 0043bf40 */

/* restarts playback for a streaming entry */

void __cdecl sfx_entry_resume(int entry)

{
  if (*(int *)(entry + 0x74) != 0) {
    (**(code **)(**(int **)(entry + 0x24) + 0x30))(*(int **)(entry + 0x24),0,0,1);
  }
  return;
}



/* sfx_entry_stop @ 0043bf60 */

/* stops playback for all voices */

void __cdecl sfx_entry_stop(int entry)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  if (entry != 0) {
    if (*(int *)(entry + 0x74) == 0) {
      piVar2 = (int *)(entry + 0x24);
      iVar3 = 0x10;
      do {
        piVar1 = (int *)*piVar2;
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 0x48))(piVar1);
        }
        piVar2 = piVar2 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    else {
      piVar2 = *(int **)(entry + 0x24);
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x48))(piVar2);
        return;
      }
    }
  }
  return;
}



/* sfx_entry_set_volume @ 0043bfa0 */

/* sets the volume for active voices */

void __cdecl sfx_entry_set_volume(int entry,float volume)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  longlong lVar6;
  
  fVar3 = (volume + 2.0) * 0.33333334;
  if ((*(int *)(entry + 0x74) == 0) || (*(float *)(entry + 0x20) != fVar3)) {
    iVar4 = 0;
    *(float *)(entry + 0x20) = fVar3;
    piVar5 = (int *)(entry + 0x24);
    do {
      piVar1 = (int *)*piVar5;
      if (piVar1 != (int *)0x0) {
        iVar2 = *piVar1;
        lVar6 = __ftol();
        (**(code **)(iVar2 + 0x3c))(piVar1,(int)lVar6);
        if (*(int *)(entry + 0x74) != 0) {
          return;
        }
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar4 < 0x10);
  }
  return;
}



/* sfx_entry_load_wav @ 0043c020 */

/* loads a WAV sample into an sfx entry */

int __cdecl sfx_entry_load_wav(void *entry,byte *path)

{
  int iVar1;
  uint extraout_EAX;
  uint local_4;
  
  iVar1 = resource_read_alloc(path,&path,&local_4);
  if ((char)iVar1 == '\0') {
    return iVar1;
  }
  iVar1 = wav_parse_into_entry(entry,path,local_4);
  if ((char)iVar1 == '\0') {
    crt_free(path);
    return extraout_EAX & 0xffffff00;
  }
  crt_free(path);
  iVar1 = sfx_entry_create_buffers((int)entry);
  return CONCAT31((int3)((uint)iVar1 >> 8),(char)iVar1 != '\0');
}



/* sfx_release_entry @ 0043c090 */

/* frees a sound entry (sample/voices) */

void __cdecl sfx_release_entry(int entry)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if (*(void **)(entry + 0x74) != (void *)0x0) {
    vorbis_mem_close(*(void **)(entry + 0x74));
    crt_free(*(void **)(entry + 0x74));
    piVar3 = *(int **)(entry + 0x24);
    *(undefined4 *)(entry + 0x74) = 0;
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 8))(piVar3);
    }
    *(undefined4 *)(entry + 0x24) = 0;
    crt_free(*(void **)(entry + 0x14));
    *(undefined4 *)(entry + 0x14) = 0;
    return;
  }
  piVar3 = (int *)(entry + 0x60);
  iVar2 = 0x10;
  do {
    piVar1 = (int *)*piVar3;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    *piVar3 = 0;
    piVar3 = piVar3 + -1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  crt_free(*(void **)(entry + 0x14));
  *(undefined4 *)(entry + 0x14) = 0;
  return;
}



/* sfx_entry_upload_buffer @ 0043c230 */

/* uploads PCM data into a DirectSound buffer */

int __cdecl sfx_entry_upload_buffer(int entry)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined1 local_4 [4];
  
  iVar1 = entry;
  piVar8 = &entry;
  uVar7 = 0;
  iVar2 = (**(code **)(**(int **)(entry + 0x24) + 0x2c))
                    (*(int **)(entry + 0x24),0,*(undefined4 *)(entry + 0x18),piVar8,local_4,0,0,0);
  if ((iVar2 < 0) && (iVar2 == -0x7787ff6a)) {
    iVar2 = dsound_restore_buffer(*(void **)(iVar1 + 0x24));
    if ((char)iVar2 == '\0') {
      return iVar2;
    }
  }
  uVar4 = *(uint *)(iVar1 + 0x18);
  piVar5 = *(int **)(iVar1 + 0x14);
  piVar6 = piVar8;
  for (uVar3 = uVar4 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *piVar6 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar6 = piVar6 + 1;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)piVar6 = (char)*piVar5;
    piVar5 = (int *)((int)piVar5 + 1);
    piVar6 = (int *)((int)piVar6 + 1);
  }
  uVar7 = (**(code **)(**(int **)(iVar1 + 0x24) + 0x4c))(*(int **)(iVar1 + 0x24),piVar8,uVar7,0,0);
  return CONCAT31((int3)((uint)uVar7 >> 8),1);
}



/* sfx_entry_create_buffers @ 0043c2b0 */

/* creates DirectSound buffers for an sfx entry */

int __cdecl sfx_entry_create_buffers(int entry)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint extraout_EAX;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 local_24 [4];
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar7 = (undefined4 *)(entry + 0x24);
  puVar5 = local_24;
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  local_24[2] = *(undefined4 *)(entry + 0x18);
  local_10 = 0;
  local_8 = 0;
  local_4 = 0;
  local_24[0] = 0x24;
  local_24[1] = 0x80e0;
  local_c = 0;
  local_14 = entry;
  uVar1 = (**(code **)(*dsound_iface + 0xc))(dsound_iface,local_24,puVar7,0);
  if ((int)uVar1 < 0) {
    return uVar1 & 0xffffff00;
  }
  iVar6 = 1;
  iVar4 = entry + 0x28;
  do {
    iVar2 = (**(code **)(*dsound_iface + 0x14))(dsound_iface,*puVar7,iVar4);
    if (iVar2 < 0) {
      OutputDebugStringA(s_snd_duplicate_failed);
      return extraout_EAX & 0xffffff00;
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + 4;
  } while (iVar6 < 0x10);
  sfx_entry_upload_buffer(entry);
  iVar4 = 0;
  do {
    *(undefined1 *)(iVar4 + 100 + entry) = 0;
    (**(code **)(*(int *)*puVar7 + 0x48))((int *)*puVar7);
    uVar3 = (**(code **)(*(int *)*puVar7 + 0x34))((int *)*puVar7,0);
    iVar4 = iVar4 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar4 < 0x10);
  return CONCAT31((int3)((uint)uVar3 >> 8),1);
}



/* sfx_release_sample @ 0043c700 */

/* releases an sfx sample by id */

int __cdecl sfx_release_sample(int sfx_id)

{
  uint in_EAX;
  undefined4 extraout_EAX;
  
  if (((-1 < sfx_id) && (sfx_id < 0x80)) &&
     (in_EAX = sfx_id * 0x84, (&sfx_entry_table)[sfx_id].pcm_data != (void *)0x0)) {
    sfx_release_entry((int)(&sfx_entry_table + sfx_id));
    return CONCAT31((int3)((uint)extraout_EAX >> 8),1);
  }
  return in_EAX & 0xffffff00;
}



/* sfx_load_sample @ 0043c740 */

/* loads an sfx sample and returns its id */

int __cdecl sfx_load_sample(char *path)

{
  byte bVar1;
  void **ppvVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  byte *pbVar7;
  bool bVar8;
  byte local_80 [128];
  
  if (config_blob.reserved0[0] != '\0') {
    return 1;
  }
  iVar6 = 0;
  ppvVar2 = &sfx_entry_table.pcm_data;
  while (*ppvVar2 != (void *)0x0) {
    ppvVar2 = ppvVar2 + 0x21;
    iVar6 = iVar6 + 1;
    if (0x4cc6e3 < (int)ppvVar2) {
      return -1;
    }
  }
  if (iVar6 != -1) {
    pbVar7 = &DAT_00477dd4;
    pbVar3 = (byte *)path;
    do {
      bVar1 = *pbVar3;
      bVar8 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_0043c7c5:
        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_0043c7ca;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar8 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_0043c7c5;
      pbVar3 = pbVar3 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_0043c7ca:
    if (iVar4 == 0) {
      console_printf(&console_log_queue,s_Warning__sample___s__not_accepte_00477db0,path);
      path = s_trooper_inPain_01_ogg_00477d98;
    }
    pcVar5 = _strstr(path,&DAT_00477dd4);
    if (pcVar5 == (char *)0x0) {
      iVar4 = sfx_entry_load_wav(&sfx_entry_table + iVar6,(byte *)path);
      if ((char)iVar4 != '\0') goto LAB_0043c885;
      pcVar5 = s____loading_wav_sample___s__faile_00477d48;
    }
    else {
      if (sfx_resource_loaded == '\0') {
        pcVar5 = s_sfx__s_00477d90;
      }
      else {
        pcVar5 = &s_fmt_percent_s;
      }
      crt_sprintf((char *)local_80,pcVar5,path);
      iVar4 = sfx_entry_load_ogg(&sfx_entry_table + iVar6,local_80);
      if ((char)iVar4 != '\0') {
LAB_0043c885:
        if (*(float *)((int)cv_silentloads + 0xc) == 0.0) {
          console_printf(&console_log_queue,s_sfx_sample_ok_fmt,iVar6,path);
        }
        sfx_load_counter = sfx_load_counter + 1;
        return iVar6;
      }
      pcVar5 = s_ogg_sample_failed_fmt;
    }
    console_printf(&console_log_queue,pcVar5,path);
  }
  return -1;
}



/* sfx_system_init @ 0043cf90 */

/* initializes the Grim SFX system and clears per-sfx state */

int sfx_system_init(void)

{
  undefined4 in_EAX;
  HWND hwnd;
  int iVar1;
  uint3 extraout_var;
  undefined3 extraout_var_00;
  float *pfVar2;
  LPDIRECTSOUNDBUFFER *ppIVar3;
  uint coop_level;
  
  if (config_blob.reserved0[0] != '\0') {
    return CONCAT31((int3)((uint)in_EAX >> 8),1);
  }
  console_printf(&console_log_queue,s_Initializing_Grim_SFX_sound_syst_004785c8);
  coop_level = 2;
  hwnd = GetForegroundWindow();
  iVar1 = dsound_init(hwnd,coop_level);
  if ((char)iVar1 == '\0') {
    console_printf(&console_log_queue,s____FAILED__unable_to_init_Grim_S_00478590);
    config_blob.reserved0[0] = '\x01';
    config_blob.reserved0[1] = '\x01';
    return (uint)extraout_var << 8;
  }
  console_printf(&console_log_queue,s____init_44100_Hz_16_bit_ok_00478574);
  console_printf(&console_log_queue,s____using_DirectSound_output_00478554);
  console_printf(&console_log_queue,s____using_default_speaker_config_00478530);
  console_printf(&console_log_queue,s____saying_hello_to_the_Ogg__00478510);
  pfVar2 = sfx_cooldown_table;
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pfVar2 = 0.0;
    pfVar2 = pfVar2 + 1;
  }
  ppIVar3 = sfx_voice_table;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppIVar3 = (LPDIRECTSOUNDBUFFER)0x0;
    ppIVar3 = ppIVar3 + 1;
  }
  console_printf(&console_log_queue,s_init_sfx_done);
  return CONCAT31(extraout_var_00,1);
}



/* sfx_release_all @ 0043d070 */

/* releases all loaded sfx samples */

void sfx_release_all(void)

{
  char *filename;
  sfx_entry_t *entry;
  
  if (config_blob.reserved0[0] == '\0') {
    entry = &sfx_entry_table;
    do {
      sfx_release_entry((int)entry);
      entry = entry + 1;
    } while ((int)entry < 0x4cc6d0);
    console_printf(&console_log_queue,s_sfx_shutdown);
    console_printf(&console_log_queue,s_sfx_released);
    console_flush_log(&console_log_queue,filename);
  }
  return;
}



/* sfx_play @ 0043d120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* plays a sound effect with centered pan */

int __cdecl sfx_play(int sfx_id)

{
  int iVar1;
  longlong lVar2;
  float unaff_retaddr;
  
  if ((&sfx_entry_table)[sfx_id].pcm_data == (void *)0x0) {
    return -1;
  }
  if (config_blob.reserved0[0] != '\0') {
    return -1;
  }
  if (0.0 < sfx_cooldown_table[sfx_id]) {
    return -1;
  }
  if (bonus_reflex_boost_timer <= 0.0) {
    sfx_rate_scale = 0xac44;
  }
  else if (bonus_reflex_boost_timer <= 1.0) {
    if (bonus_reflex_boost_timer < 1.0) {
      lVar2 = __ftol();
      sfx_rate_scale = (undefined4)lVar2;
    }
  }
  else {
    sfx_rate_scale = 0x5622;
  }
  if ((sfx_id == sfx_flamer_fire_01) || (sfx_id == sfx_flamer_fire_02)) {
    sfx_cooldown_table[sfx_id] = 0.44;
  }
  else {
    sfx_cooldown_table[sfx_id] = 0.05;
  }
  iVar1 = sfx_entry_start_playback((int)(&sfx_entry_table + sfx_id));
  (**(code **)(*(int *)(&sfx_entry_table)[sfx_id].buffers[iVar1] + 0x40))
            ((&sfx_entry_table)[sfx_id].buffers[iVar1],0);
  sfx_entry_set_volume((int)(&sfx_entry_table + sfx_id),config_blob.sfx_volume * unaff_retaddr);
  return sfx_id;
}



/* sfx_play_panned @ 0043d260 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* plays a sound effect with computed pan */

float __cdecl sfx_play_panned(float sfx_id)

{
  int iVar1;
  int iVar2;
  float10 in_ST0;
  float10 extraout_ST0;
  longlong lVar3;
  
  if ((&sfx_entry_table)[(int)sfx_id].pcm_data == (void *)0x0) {
    return (float)in_ST0;
  }
  if (config_blob.reserved0[0] != '\0') {
    return (float)in_ST0;
  }
  if (0.0 < sfx_cooldown_table[(int)sfx_id]) {
    return (float)in_ST0;
  }
  if (bonus_reflex_boost_timer <= 0.0) {
    sfx_rate_scale = 0xac44;
  }
  else if (bonus_reflex_boost_timer <= 1.0) {
    if (bonus_reflex_boost_timer < 1.0) {
      lVar3 = __ftol();
      sfx_rate_scale = (undefined4)lVar3;
    }
  }
  else {
    sfx_rate_scale = 0x5622;
  }
  if ((sfx_id == sfx_flamer_fire_01) || (sfx_id == sfx_flamer_fire_02)) {
    sfx_cooldown_table[(int)sfx_id] = 0.44;
  }
  else {
    sfx_cooldown_table[(int)sfx_id] = 0.05;
  }
  lVar3 = __ftol();
  iVar2 = (int)lVar3;
  if (iVar2 < -10000) {
    iVar2 = -10000;
  }
  else if (10000 < iVar2) {
    iVar2 = 10000;
  }
  iVar1 = sfx_entry_start_playback((int)(&sfx_entry_table + (int)sfx_id));
  (**(code **)(*(int *)(&sfx_entry_table)[(int)sfx_id].buffers[iVar1] + 0x40))
            ((&sfx_entry_table)[(int)sfx_id].buffers[iVar1],iVar2);
  sfx_entry_set_volume((int)(&sfx_entry_table + (int)sfx_id),config_blob.sfx_volume * sfx_id);
  return (float)extraout_ST0;
}



/* sfx_play_exclusive @ 0043d460 */

/* mutes other sfx ids and ensures the chosen id is audible */

void __cdecl sfx_play_exclusive(int sfx_id)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  if (((sfx_unmuted_flag != '\0') && (config_blob.reserved0[1] == '\0')) &&
     (config_blob.reserved0[0] == '\0')) {
    if (ui_splash_skip_flag == '\0') {
      if (sfx_id == music_track_extra_0) {
        if (music_muted_flag != '\0') {
          return;
        }
        if (music_playlist_index == 0) {
          return;
        }
        iVar2 = crt_rand();
        music_muted_flag = '\x01';
        sfx_id = music_playlist[iVar2 % music_playlist_index];
      }
      else {
        music_muted_flag = '\0';
      }
    }
    iVar2 = 0;
    do {
      if ((iVar2 != sfx_id) && (iVar3 = sfx_is_unmuted(iVar2), (char)iVar3 != '\0')) {
        sfx_mute_all(iVar2);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x80);
    if (sfx_volume_table[sfx_id] <= 0.0) {
      sfx_entry_start_playback((int)(&music_entry_table + sfx_id));
      sfx_entry_set_volume((int)(&music_entry_table + sfx_id),config_blob.music_volume);
      fVar1 = config_blob.music_volume;
      sfx_mute_flags[sfx_id] = '\0';
      sfx_volume_table[sfx_id] = fVar1;
    }
  }
  return;
}



/* sfx_mute_all @ 0043d550 */

/* mutes all unmuted sfx ids (recursive) */

void __cdecl sfx_mute_all(int sfx_id)

{
  int iVar1;
  int sfx_id_00;
  
  if (((sfx_unmuted_flag != '\0') && (config_blob.reserved0[1] == '\0')) &&
     (config_blob.reserved0[0] == '\0')) {
    music_muted_flag = 0;
    sfx_id_00 = 0;
    do {
      if (sfx_id_00 != sfx_id) {
        iVar1 = sfx_is_unmuted(sfx_id_00);
        if ((char)iVar1 != '\0') {
          sfx_mute_all(sfx_id_00);
        }
      }
      sfx_id_00 = sfx_id_00 + 1;
    } while (sfx_id_00 < 0x80);
    sfx_mute_flags[sfx_id] = '\x01';
  }
  return;
}



/* sfx_update_mute_fades @ 0043d5b0 */

/* ramps volume up/down based on mute flags */

void sfx_update_mute_fades(void)

{
  float fVar1;
  int iVar2;
  music_entry_t *entry;
  float *pfVar3;
  float volume;
  byte abStack_4 [4];
  
  if ((audio_suspend_flag == '\0') && (sfx_unmuted_flag != '\0')) {
    iVar2 = 0;
    pfVar3 = sfx_volume_table;
    entry = &music_entry_table;
    do {
      if (entry->vorbis_stream != (void *)0x0) {
        if (0.0 < config_blob.music_volume) {
          if (sfx_mute_flags[iVar2] == '\0') {
            (**(code **)(*(int *)entry->buffers[0] + 0x24))(entry->buffers[0],abStack_4);
            if ((abStack_4[0] & 1) == 0) {
              console_printf(&console_log_queue,s_snd_detected_hearable);
              sfx_entry_resume((int)entry);
            }
            goto LAB_0043d63c;
          }
        }
        else {
          (**(code **)(*(int *)entry->buffers[0] + 0x48))(entry->buffers[0]);
LAB_0043d63c:
          fVar1 = config_blob.music_volume;
          if (sfx_mute_flags[iVar2] == '\0') {
            if (config_blob.music_volume <= *pfVar3) {
              if (*pfVar3 <= config_blob.music_volume) goto LAB_0043d709;
              *pfVar3 = config_blob.music_volume;
LAB_0043d6ff:
              volume = fVar1;
            }
            else {
              volume = frame_dt + *pfVar3;
              *pfVar3 = volume;
              fVar1 = config_blob.music_volume;
              if (config_blob.music_volume <= volume) goto LAB_0043d6ff;
            }
            sfx_entry_set_volume((int)entry,volume);
            goto LAB_0043d709;
          }
        }
        if (0.0 < *pfVar3) {
          fVar1 = *pfVar3 - frame_dt * 0.5;
          *pfVar3 = fVar1;
          if (0.0 < fVar1) {
            sfx_entry_set_volume((int)entry,fVar1);
          }
          else {
            sfx_entry_stop((int)entry);
          }
        }
        if (*pfVar3 < 0.0) {
          *pfVar3 = 0.0;
        }
      }
LAB_0043d709:
      entry = entry + 1;
      iVar2 = iVar2 + 1;
      pfVar3 = pfVar3 + 1;
    } while ((int)entry < 0x4c8450);
  }
  return;
}



/* sfx_is_unmuted @ 0043d7c0 */

/* returns nonzero when sfx id is not muted */

int __cdecl sfx_is_unmuted(int sfx_id)

{
  uint in_EAX;
  
  if (sfx_unmuted_flag == '\0') {
    return in_EAX & 0xffffff00;
  }
  return (uint)(sfx_mute_flags[sfx_id] == '\0');
}


