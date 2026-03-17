/* dx_get_version @ 0041ccb0 */

/* query DirectX version */

int __cdecl dx_get_version(int *version,char *out,int out_len)

{
  char *dst;
  int size;
  char cVar1;
  int iVar2;
  int local_4;
  
  size = out_len;
  dst = out;
  if (version != (int *)0x0) {
    *version = 0;
  }
  if ((out != (char *)0x0) && (0 < out_len)) {
    *out = '\0';
  }
  out_len = 0;
  local_4 = 0;
  out = (char *)CONCAT31(out._1_3_,0x20);
  iVar2 = quest_file_header_read();
  if (iVar2 < 0) {
    iVar2 = quest_file_data_parse(&out_len,&local_4,(char *)&out);
    if (iVar2 < 0) {
      return -0x7fffbffb;
    }
  }
  iVar2 = crt_tolower((int)(char)out);
  cVar1 = (char)iVar2;
  out = (char *)CONCAT31(out._1_3_,cVar1);
  if (version != (int *)0x0) {
    iVar2 = (out_len * 0x100 + local_4) * 0x100;
    if (('`' < cVar1) && (cVar1 < '{')) {
      iVar2 = iVar2 + -0x60 + (int)cVar1;
    }
    *version = iVar2;
  }
  if ((dst != (char *)0x0) && (0 < size)) {
    if (cVar1 == ' ') {
      crt_snprintf(dst,size,s__d__d_0047381c,out_len,local_4);
      dst[size + -1] = '\0';
      return 0;
    }
    crt_snprintf(dst,size,s__d__d_c_0047389c,out_len,local_4,(int)cVar1);
    dst[size + -1] = '\0';
  }
  return 0;
}



/* audio_find_format @ 0041db50 */

/* [binja] int32_t sub_41db50(uint32_t arg1, int32_t* arg2) */

int __cdecl audio_find_format(uint arg1,int *arg2)

{
  uint lptstrFilename;
  int *piVar1;
  void *lpData;
  WINBOOL WVar2;
  DWORD local_4;
  
  piVar1 = arg2;
  lptstrFilename = arg1;
  if ((arg1 == 0) || (arg2 == (int *)0x0)) {
    return -0x7ff8ffa9;
  }
  arg1 = GetFileVersionInfoSizeA((LPCSTR)arg1,&local_4);
  if (arg1 != 0) {
    lpData = operator_new(arg1);
    if (lpData == (void *)0x0) {
      return -0x7ff8fff2;
    }
    WVar2 = GetFileVersionInfoA((LPCSTR)lptstrFilename,0,arg1,lpData);
    if (WVar2 != 0) {
      arg2 = (int *)0x0;
      WVar2 = VerQueryValueA(lpData,&DAT_004739b8,&arg2,&arg1);
      if ((WVar2 != 0) && (arg2 != (int *)0x0)) {
        piVar1[1] = arg2[2];
        *piVar1 = arg2[3];
        crt_free(lpData);
        return 0;
      }
    }
    crt_free(lpData);
  }
  return -0x7fffbffb;
}



/* audio_create_format @ 0041dc10 */

undefined8 __cdecl audio_create_format(int param_1,uint param_2,int param_3,uint param_4)

{
  return CONCAT44(param_1 << 0x10 | param_2 & 0xffff,param_3 << 0x10 | param_4 & 0xffff);
}



/* audio_init_format @ 0041dc50 */

int __cdecl audio_init_format(uint param_1,uint param_2,uint param_3,uint param_4)

{
  if (param_4 < param_2) {
    return 1;
  }
  if (param_2 < param_4) {
    return -1;
  }
  if (param_3 < param_1) {
    return 1;
  }
  return -(uint)(param_1 < param_3);
}



/* grim_load_interface @ 0041dc80 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* load grim DLL and fetch GRIM_GetInterface */

int __cdecl grim_load_interface(char *dll_name)

{
  char cVar1;
  FARPROC pFVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  ui_weapon_select_idx = LoadLibraryA(dll_name);
  if (ui_weapon_select_idx == (HMODULE)0x0) {
    return 0;
  }
  pFVar2 = GetProcAddress(ui_weapon_select_idx,s_GRIM__GetInterface_004739bc);
  uVar4 = 0xffffffff;
  do {
    pcVar6 = dll_name;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar6 = dll_name + 1;
    cVar1 = *dll_name;
    dll_name = pcVar6;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar6 + -uVar4;
  pcVar7 = (char *)&DAT_00490308;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar7 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar7 = pcVar7 + 1;
  }
  if (pFVar2 == (FARPROC)0x0) {
    return 0;
  }
  iVar3 = (*pFVar2)();
  return iVar3;
}



/* vorbis_mem_read @ 0041dce0 */

/* ov_open_callbacks read hook for memory-backed OGG data */

uint __cdecl vorbis_mem_read(void *dst,uint size,uint count,void *datasource)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if (*(uint *)((int)datasource + -8) <= *(uint *)((int)datasource + -4)) {
    *(undefined4 *)((int)datasource + -4) = 0;
  }
  iVar1 = *(int *)((int)datasource + -4);
  uVar4 = size * count;
  uVar2 = uVar4;
  if (*(uint *)((int)datasource + -8) < uVar4 + iVar1) {
    uVar2 = *(uint *)((int)datasource + -8) - iVar1;
  }
  puVar5 = (undefined4 *)(iVar1 + (int)datasource);
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)dst = *puVar5;
    puVar5 = puVar5 + 1;
    dst = (undefined4 *)((int)dst + 4);
  }
  for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined1 *)dst = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    dst = (undefined4 *)((int)dst + 1);
  }
  *(uint *)((int)datasource + -4) = *(int *)((int)datasource + -4) + uVar4;
  return uVar2;
}



/* vorbis_mem_tell @ 0041dda0 */

/* ov_open_callbacks tell hook (returns current offset) */

int __cdecl vorbis_mem_tell(void *datasource)

{
  return *(int *)((int)datasource + -4);
}



/* vorbis_pcm_seek @ 0041ddb0 */

/* wrapper around ov_pcm_seek for memory stream */

int __thiscall vorbis_pcm_seek(void *this,void *stream,uint sample_offset)

{
  int iVar1;
  uint unaff_retaddr;
  
  iVar1 = ov_pcm_seek((OggVorbis_File *)((int)this + 0x10),(ulonglong)unaff_retaddr << 0x20);
  return iVar1;
}



/* vorbis_mem_open @ 0041ddd0 */

/* open OGG/Vorbis data from a memory buffer (sets callbacks) */

int __thiscall vorbis_mem_open(void *this,void *stream,void *buffer,uint size)

{
  OggVorbis_File *vf;
  int iVar1;
  uint uVar2;
  vorbis_info *pvVar3;
  int *piVar4;
  ogg_int64_t oVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  *(code **)this = vorbis_mem_read;
  *(undefined1 **)((int)this + 4) = &LAB_0041dd40;
  *(undefined1 **)((int)this + 8) = &LAB_0041dd90;
  *(code **)((int)this + 0xc) = vorbis_mem_tell;
  *(undefined4 *)((int)this + 0x2e0) = 0;
  *(void **)((int)this + 0x2ec) = stream;
  *(void **)stream = buffer;
  *(undefined4 *)(*(int *)((int)this + 0x2ec) + 4) = 0;
  vf = (OggVorbis_File *)((int)this + 0x10);
  iVar1 = ov_open_callbacks((void *)(*(int *)((int)this + 0x2ec) + 8),vf,(char *)0x0,0,
                            *(ov_callbacks *)this);
  if (iVar1 < 0) {
    uVar2 = console_error_display((byte *)s_Input_does_not_appear_to_be_an_O_004739d0);
    return uVar2 & 0xffffff00;
  }
  pvVar3 = ov_info(vf,-1);
  piVar4 = (int *)((int)this + 0x2f0);
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar4 = pvVar3->version;
    pvVar3 = (vorbis_info *)&pvVar3->channels;
    piVar4 = piVar4 + 1;
  }
  oVar5 = ov_pcm_total(vf,-1);
  lVar6 = __allmul((uint)oVar5,(int)((ulonglong)oVar5 >> 0x20),*(uint *)((int)this + 0x2f4),
                   (int)*(uint *)((int)this + 0x2f4) >> 0x1f);
  lVar6 = __allmul((uint)lVar6,(int)((ulonglong)lVar6 >> 0x20),0x10,0);
  uVar7 = __alldiv((uint)lVar6,(uint)((ulonglong)lVar6 >> 0x20),8,0);
  *(int *)((int)this + 0x2e4) = (int)uVar7;
  iVar1 = vorbis_mem_tell((void *)(*(int *)((int)this + 0x2ec) + 8));
  *(int *)((int)this + 0x2e8) = iVar1;
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}



/* vorbis_mem_close @ 0041dee0 */

/* frees memory buffer and ov_clear */

void __fastcall vorbis_mem_close(void *stream)

{
  crt_free(*(void **)((int)stream + 0x2ec));
  ov_clear((OggVorbis_File *)((int)stream + 0x10));
  return;
}



/* vorbis_read_pcm16 @ 0041df00 */

/* decode PCM16 samples via ov_read */

int __thiscall vorbis_read_pcm16(void *this,void *stream,char *dst,int bytes)

{
  uint uVar1;
  
  uVar1 = ov_read((OggVorbis_File *)((int)this + 0x10),stream,(int)dst,0,2,1,
                  (int *)((int)this + 0x2e0));
  if (uVar1 == 0) {
    return 0;
  }
  return uVar1 & ((int)uVar1 < 0) - 1;
}



/* audio_resume_all @ 0042a5f0 */

/* resume active audio channels */

int audio_resume_all(void)

{
  float fVar1;
  int iVar2;
  uint3 extraout_var;
  
  audio_resume_channels();
  fVar1 = *(float *)((int)cv_verbose + 0xc);
  iVar2 = CONCAT22((short)((uint)cv_verbose >> 0x10),
                   (ushort)(fVar1 < 0.0) << 8 | (ushort)NAN(fVar1) << 10 |
                   (ushort)(fVar1 == 0.0) << 0xe);
  if ((fVar1 == 0.0) == 0) {
    console_printf(&console_log_queue,s_audio_restored);
    iVar2 = (uint)extraout_var << 8;
  }
  audio_suspend_flag = 0;
  return CONCAT31((int3)((uint)iVar2 >> 8),1);
}



/* audio_suspend_all @ 0042a630 */

/* suspend active audio channels */

void audio_suspend_all(void)

{
  audio_suspend_channels();
  if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
    console_printf(&console_log_queue,s_audio_suspended);
  }
  audio_suspend_flag = 1;
  return;
}



/* audio_init_music @ 0043c9c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* loads music pack and registers music track ids */

void audio_init_music(void)

{
  int iVar1;
  float *pfVar2;
  char *pcVar3;
  
  if ((config_blob.reserved0[0] == '\0') && (config_blob.reserved0[1] == '\0')) {
    iVar1 = 0x20;
    pcVar3 = sfx_mute_flags;
    while (iVar1 != 0) {
      iVar1 = iVar1 + -1;
      builtin_strncpy(pcVar3,"\x01\x01\x01\x01",4);
      pcVar3 = pcVar3 + 4;
    }
    pfVar2 = sfx_volume_table;
    for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
      *pfVar2 = 0.0;
      pfVar2 = pfVar2 + 1;
    }
    iVar1 = resource_pack_set(s_music_paq_path);
    sfx_resource_loaded = (char)iVar1;
    if (sfx_resource_loaded == '\0') {
      pcVar3 = s_music_paq_not_found;
    }
    else {
      pcVar3 = s_music_paq_loaded;
    }
    console_printf(&console_log_queue,pcVar3);
    music_track_intro_id = music_load_track(s_music_intro_path);
    music_track_shortie_monk_id = music_load_track(s_music_shortie_monk_path);
    console_exec_line(&console_log_queue,s_music_game_tunes_cmd);
    music_track_crimson_theme_id = music_load_track(s_music_crimson_theme_path);
    music_track_crimsonquest_id = music_load_track(s_music_crimsonquest_path);
    music_track_extra_0 = music_track_crimsonquest_id + 1;
    _music_track_extra_1 = music_track_crimsonquest_id + 2;
    sfx_unmuted_flag = 1;
  }
  return;
}



/* audio_init_sfx @ 0043caa0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* loads sfx pack and registers sound effect ids */

void audio_init_sfx(void)

{
  int iVar1;
  DWORD DVar2;
  DWORD DVar3;
  void **ppvVar4;
  char *fmt;
  
  if (config_blob.reserved0[0] == '\0') {
    iVar1 = resource_pack_set(s_sfx_paq_004784f4);
    sfx_resource_loaded = (char)iVar1;
    if (sfx_resource_loaded == '\0') {
      fmt = s____failed_to_set_sound_resource_p_0047849c;
    }
    else {
      fmt = s____set_sound_resource_paq__sfx_p_004784cc;
    }
    console_printf(&console_log_queue,fmt);
    DVar2 = timeGetTime();
    sfx_trooper_inpain_01 = sfx_load_sample(s_trooper_inPain_01_ogg_00477d98);
    sfx_trooper_inpain_02 = sfx_load_sample(s_trooper_inPain_02_ogg_00478484);
    _sfx_trooper_inpain_03 = sfx_load_sample(s_trooper_inPain_03_ogg_0047846c);
    sfx_trooper_die_01 = sfx_load_sample(s_trooper_die_01_ogg_00478458);
    sfx_trooper_die_02 = sfx_load_sample(s_trooper_die_02_ogg_00478444);
    sfx_trooper_die_03 = sfx_load_sample(s_trooper_die_03_ogg_00478430);
    sfx_zombie_die_01 = sfx_load_sample(s_zombie_die_01_ogg_0047841c);
    sfx_zombie_die_02 = sfx_load_sample(s_zombie_die_02_ogg_00478408);
    sfx_zombie_die_03 = sfx_load_sample(s_zombie_die_03_ogg_004783f4);
    sfx_zombie_die_04 = sfx_load_sample(s_zombie_die_04_ogg_004783e0);
    sfx_zombie_attack_01 = sfx_load_sample(s_zombie_attack_01_ogg_004783c8);
    sfx_zombie_attack_02 = sfx_load_sample(s_zombie_attack_02_ogg_004783b0);
    sfx_alien_die_01 = sfx_load_sample(s_alien_die_01_ogg_0047839c);
    sfx_alien_die_02 = sfx_load_sample(s_alien_die_02_ogg_00478388);
    sfx_alien_die_03 = sfx_load_sample(s_alien_die_03_ogg_00478374);
    sfx_alien_die_04 = sfx_load_sample(s_alien_die_04_ogg_00478360);
    sfx_alien_attack_01 = sfx_load_sample(s_alien_attack_01_ogg_0047834c);
    sfx_alien_attack_02 = sfx_load_sample(s_alien_attack_02_ogg_00478338);
    sfx_lizard_die_01 = sfx_load_sample(s_lizard_die_01_ogg_00478324);
    sfx_lizard_die_02 = sfx_load_sample(s_lizard_die_02_ogg_00478310);
    sfx_lizard_die_03 = sfx_load_sample(s_lizard_die_03_ogg_004782fc);
    sfx_lizard_die_04 = sfx_load_sample(s_lizard_die_04_ogg_004782e8);
    sfx_lizard_attack_01 = sfx_load_sample(s_lizard_attack_01_ogg_004782d0);
    sfx_lizard_attack_02 = sfx_load_sample(s_lizard_attack_02_ogg_004782b8);
    sfx_spider_die_01 = sfx_load_sample(s_spider_die_01_ogg_004782a4);
    sfx_spider_die_02 = sfx_load_sample(s_spider_die_02_ogg_00478290);
    sfx_spider_die_03 = sfx_load_sample(s_spider_die_03_ogg_0047827c);
    sfx_spider_die_04 = sfx_load_sample(s_spider_die_04_ogg_00478268);
    sfx_spider_attack_01 = sfx_load_sample(s_spider_attack_01_ogg_00478250);
    sfx_spider_attack_02 = sfx_load_sample(s_spider_attack_02_ogg_00478238);
    sfx_pistol_fire = sfx_load_sample(s_pistol_fire_ogg_00478228);
    sfx_pistol_reload = sfx_load_sample(s_pistol_reload_ogg_00478214);
    sfx_shotgun_fire = sfx_load_sample(s_shotgun_fire_ogg_00478200);
    sfx_shotgun_reload = sfx_load_sample(s_shotgun_reload_ogg_004781ec);
    sfx_autorifle_fire = sfx_load_sample(s_autorifle_fire_ogg_004781d8);
    sfx_autorifle_reload = sfx_load_sample(s_autorifle_reload_ogg_004781c0);
    sfx_gauss_fire = sfx_load_sample(s_gauss_fire_ogg_004781b0);
    sfx_hrpm_fire = sfx_load_sample(s_hrpm_fire_ogg_004781a0);
    sfx_shock_fire = sfx_load_sample(s_shock_fire_ogg_00478190);
    sfx_plasmaminigun_fire = sfx_load_sample(s_plasmaMinigun_fire_ogg_00478178);
    sfx_plasmashotgun_fire = sfx_load_sample(s_plasmaShotgun_fire_ogg_00478160);
    sfx_pulse_fire = sfx_load_sample(s_pulse_fire_ogg_00478150);
    sfx_flamer_fire_01 = sfx_load_sample(s_flamer_fire_01_ogg_0047813c);
    sfx_flamer_fire_02 = sfx_load_sample(s_flamer_fire_02_ogg_00478128);
    sfx_shock_reload = sfx_load_sample(s_shock_reload_ogg_00478114);
    sfx_shock_fire_alt = sfx_load_sample(s_shock_fire_ogg_00478190);
    sfx_shockminigun_fire = sfx_load_sample(s_shockMinigun_fire_ogg_004780fc);
    sfx_rocket_fire = sfx_load_sample(s_rocket_fire_ogg_004780ec);
    sfx_rocketmini_fire = sfx_load_sample(s_rocketmini_fire_ogg_004780d8);
    sfx_autorifle_reload_alt = sfx_load_sample(s_autorifle_reload_ogg_004781c0);
    sfx_bullet_hit_01 = sfx_load_sample(s_bullet_hit_01_ogg_004780c4);
    _sfx_bullet_hit_02 = sfx_load_sample(s_bullet_hit_02_ogg_004780b0);
    _sfx_bullet_hit_03 = sfx_load_sample(s_bullet_hit_03_ogg_0047809c);
    _sfx_bullet_hit_04 = sfx_load_sample(s_bullet_hit_04_ogg_00478088);
    _sfx_bullet_hit_05 = sfx_load_sample(s_bullet_hit_05_ogg_00478074);
    _sfx_bullet_hit_06 = sfx_load_sample(s_bullet_hit_06_ogg_00478060);
    sfx_shock_hit_01 = sfx_load_sample(s_shock_hit_01_ogg_0047804c);
    sfx_explosion_small = sfx_load_sample(s_explosion_small_ogg_00478038);
    sfx_explosion_medium = sfx_load_sample(s_explosion_medium_ogg_00478020);
    sfx_explosion_large = sfx_load_sample(s_explosion_large_ogg_0047800c);
    sfx_shockwave = sfx_load_sample(s_shockwave_ogg_00477ffc);
    sfx_questhit = sfx_load_sample(s_questHit_ogg_00477fec);
    sfx_ui_bonus = sfx_load_sample(s_ui_bonus_ogg_00477fdc);
    _sfx_trooper_inpain_01_alias_0 = sfx_trooper_inpain_01;
    sfx_trooper_inpain_01_alias_1 = sfx_trooper_inpain_01;
    _sfx_trooper_inpain_01_alias_2 = sfx_trooper_inpain_01;
    sfx_ui_buttonclick = sfx_load_sample(s_ui_buttonClick_ogg_00477fc8);
    sfx_ui_panelclick = sfx_load_sample(s_ui_panelClick_ogg_00477fb4);
    sfx_ui_levelup = sfx_load_sample(s_ui_levelUp_ogg_00477fa4);
    _sfx_ui_typeclick_01 = sfx_load_sample(s_ui_typeClick_01_ogg_00477f90);
    _sfx_ui_typeclick_02 = sfx_load_sample(s_ui_typeClick_02_ogg_00477f7c);
    sfx_ui_typeenter = sfx_load_sample(s_ui_typeEnter_ogg_00477f68);
    sfx_ui_clink_01 = sfx_load_sample(s_ui_clink_01_ogg_00477f58);
    sfx_bloodspill_01 = sfx_load_sample(s_bloodSpill_01_ogg_00477f44);
    _sfx_bloodspill_02 = sfx_load_sample(s_bloodSpill_02_ogg_00477f30);
    DVar3 = timeGetTime();
    iVar1 = 0;
    ppvVar4 = &sfx_entry_table.pcm_data;
    do {
      if (*ppvVar4 == (void *)0x0) break;
      ppvVar4 = ppvVar4 + 0x21;
      iVar1 = iVar1 + 1;
    } while ((int)ppvVar4 < 0x4cc6e4);
    console_printf(&console_log_queue,s__d_samples_loaded_to_sound_libra_00477ef8,iVar1,
                   (double)((float)(int)(DVar3 - DVar2) * 0.001));
  }
  return;
}



/* audio_shutdown_all @ 0043d110 */

/* shuts down sfx + music systems */

void audio_shutdown_all(void)

{
  sfx_release_all();
  music_release_all();
  dsound_shutdown();
  return;
}



/* audio_update @ 0043d3f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates sfx cooldowns, music streams, and mute fades */

void audio_update(void)

{
  float *pfVar1;
  music_entry_t *entry;
  
  if (config_blob.reserved0[0] == '\0') {
    pfVar1 = sfx_cooldown_table;
    do {
      if (0.0 < *pfVar1) {
        *pfVar1 = *pfVar1 - frame_dt_stored;
      }
      pfVar1 = pfVar1 + 1;
    } while ((int)pfVar1 < 0x4c3e80);
    if (sfx_unmuted_flag != '\0') {
      entry = &music_entry_table;
      do {
        if (entry->vorbis_stream != (void *)0x0) {
          music_stream_update((int)entry);
        }
        entry = entry + 1;
      } while ((int)entry < 0x4c8450);
      sfx_update_mute_fades();
    }
  }
  return;
}



/* audio_suspend_channels @ 0043d730 */

/* iterates channels and suspends playback */

void audio_suspend_channels(void)

{
  music_entry_t *entry;
  
  if (((sfx_unmuted_flag != '\0') && (config_blob.reserved0[1] == '\0')) &&
     (config_blob.reserved0[0] == '\0')) {
    entry = &music_entry_table;
    do {
      sfx_entry_stop((int)entry);
      entry = entry + 1;
    } while ((int)entry < 0x4c8450);
  }
  return;
}



/* audio_resume_channels @ 0043d770 */

/* iterates channels and resumes playback */

void audio_resume_channels(void)

{
  music_entry_t *entry;
  int iVar1;
  
  if (((sfx_unmuted_flag != '\0') && (config_blob.reserved0[1] == '\0')) &&
     (config_blob.reserved0[0] == '\0')) {
    iVar1 = 0;
    entry = &music_entry_table;
    do {
      if (sfx_mute_flags[iVar1] == '\0') {
        sfx_entry_resume((int)entry);
      }
      entry = entry + 1;
      iVar1 = iVar1 + 1;
    } while ((int)entry < 0x4c8450);
  }
  return;
}


