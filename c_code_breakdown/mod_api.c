/* plugin_pre_init @ 0040b5d0 */

/* [binja] int32_t* sub_40b5d0() */

int * plugin_pre_init(void)

{
  bonus_entry_t *pbVar1;
  projectile_t *ppVar2;
  float *pfVar3;
  
  pbVar1 = bonus_pool;
  do {
    pbVar1->bonus_id = BONUS_ID_NONE;
    pbVar1 = pbVar1 + 1;
  } while ((int)pbVar1 < 0x482b08);
  pfVar3 = &creature_pool.health;
  do {
    ((creature_t *)(pfVar3 + -9))->active = '\0';
    *pfVar3 = -1.0;
    pfVar3 = pfVar3 + 0x26;
  } while ((int)pfVar3 < 0x4aa35c);
  ppVar2 = projectile_pool;
  do {
    ppVar2->active = '\0';
    ppVar2 = ppVar2 + 1;
  } while ((int)ppVar2 < 0x493eb8);
  pfVar3 = &player_state_table.health;
  do {
    *(undefined1 *)(pfVar3 + -9) = 0;
    *pfVar3 = -1.0;
    pfVar3 = pfVar3 + 0xd8;
  } while ((int)pfVar3 < 0x490f94);
  return (int *)pfVar3;
}



/* plugin_frame_update @ 0040b630 */

void plugin_frame_update(void)

{
  uchar uVar1;
  mod_interface_t *unaff_EBX;
  mod_interface_t *unaff_retaddr;
  
  if (plugin_interface_ptr == (mod_interface_t *)0x0) {
    game_state_pending = 0x14;
    ui_transition_direction = '\0';
    ui_elements_update_and_render();
    plugin_active_flag = '\x01';
    return;
  }
  if ((game_state_id == 0x16) && (plugin_active_flag != '\0')) {
    plugin_active_flag = '\0';
    ui_splash_skip_flag = '\0';
    sfx_mute_all(music_track_extra_0);
    plugin_pre_init();
    (*plugin_interface_ptr->vtable->Init)(unaff_EBX);
    (plugin_interface_ptr->parms).fields.onPause = '\0';
  }
  else {
    uVar1 = (*plugin_interface_ptr->vtable->Frame)(frame_dt_ms,(int)unaff_EBX);
    if (uVar1 == '\0') {
      ui_splash_skip_flag = '\0';
      (*plugin_interface_ptr->vtable->Shutdown)(unaff_retaddr);
      sfx_mute_all(music_track_extra_0);
      plugin_interface_ptr = (mod_interface_t *)0x0;
      FreeLibrary((HMODULE)plugin_module_handle);
      plugin_module_handle = (HMODULE)0x0;
      plugin_active_flag = '\x01';
      game_state_pending = 0x14;
      ui_transition_direction = '\0';
    }
    else {
      ui_splash_skip_flag = '\x01';
    }
  }
  ui_elements_update_and_render();
  if (((ui_transition_direction == '\0') && (game_state_id == 0x16)) ||
     ((plugin_interface_ptr != (mod_interface_t *)0x0 &&
      ((ui_splash_skip_flag != '\0' && ((plugin_interface_ptr->parms).fields.drawMouseCursor != '\0'))))))
  {
    ui_cursor_render();
  }
  return;
}



/* mod_api_init @ 0040dfa0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* initializes the mod API context (writes mod_api_context.vtable = &mod_api_vtable at 0x0046f3e4;
   see cl_mod_sdk_v1/ClMod.h) */

void mod_api_init(void)

{
  mod_api_context.vtable = &mod_api_vtable;
  _DAT_00481ae8 = 1;
  return;
}



/* mod_api_core_printf @ 0040e000 */

/* mod API vtable 0x00: clAPI_t::CORE_Printf (writes to OutputDebugStringA) */

void __cdecl mod_api_core_printf(char *fmt,...)

{
  char local_ffc [4092];
  
  crt_vsprintf(local_ffc,fmt,&stack0x00000008);
  OutputDebugStringA(local_ffc);
  return;
}



/* mod_api_core_get_var @ 0040e040 */

/* mod API vtable 0x04: clAPI_t::CORE_GetVar (returns a 3-pointer var_t view:
   id/stringValue/floatValue) */

mod_var_t * mod_api_core_get_var(char *id)

{
  undefined4 *puVar1;
  
  puVar1 = console_cvar_find(&console_log_queue,id);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = console_register_cvar(&console_log_queue,id,&cvar_default_value_b);
  }
  puVar1[8] = puVar1 + 3;
  ((mod_var_t *)(puVar1 + 6))->id = (char *)*puVar1;
  puVar1[7] = puVar1[4];
  return (mod_var_t *)(puVar1 + 6);
}



/* mod_api_core_del_var @ 0040e080 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x08: clAPI_t::CORE_DelVar */

uchar mod_api_core_del_var(char *id)

{
  uchar uVar1;
  
  uVar1 = console_cvar_unregister(&console_log_queue,id);
  return uVar1;
}



/* mod_api_core_execute @ 0040e0a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x0c: clAPI_t::CORE_Execute */

void mod_api_core_execute(char *string)

{
  console_exec_line(&console_log_queue,string);
  return;
}



/* mod_api_core_add_command @ 0040e0c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x10: clAPI_t::CORE_AddCommand */

void mod_api_core_add_command(char *id,void *cmd)

{
  console_register_command(&console_log_queue,id,cmd);
  return;
}



/* mod_api_core_del_command @ 0040e0e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x14: clAPI_t::CORE_DelCommand */

uchar mod_api_core_del_command(char *id)

{
  uchar uVar1;
  
  uVar1 = console_command_unregister(&console_log_queue,id);
  return uVar1;
}



/* mod_api_core_get_extension @ 0040e100 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x18: clAPI_t::CORE_GetExtension (handles "grimgfx", "grimsfx", "IDirect3D8") */

void * mod_api_core_get_extension(char *ext)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  char *pcVar5;
  bool bVar6;
  uint auStack_10 [4];
  
  pbVar4 = &s_grimgfx;
  pbVar2 = (byte *)ext;
  do {
    bVar1 = *pbVar2;
    bVar6 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_0040e139:
      iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_0040e13e;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar6 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_0040e139;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0040e13e:
  if (iVar3 == 0) {
    return grim_interface_ptr;
  }
  pbVar4 = &s_grimsfx;
  pbVar2 = (byte *)ext;
  do {
    bVar1 = *pbVar2;
    bVar6 = bVar1 < *pbVar4;
    if (bVar1 != *pbVar4) {
LAB_0040e17f:
      iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_0040e184;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar2[1];
    bVar6 = bVar1 < pbVar4[1];
    if (bVar1 != pbVar4[1]) goto LAB_0040e17f;
    pbVar2 = pbVar2 + 2;
    pbVar4 = pbVar4 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0040e184:
  if (iVar3 != 0) {
    pcVar5 = s_IDirect3D8;
    do {
      bVar1 = *ext;
      bVar6 = bVar1 < (byte)*pcVar5;
      if (bVar1 != *pcVar5) {
LAB_0040e1b7:
        iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_0040e1bc;
      }
      if (bVar1 == 0) break;
      bVar1 = ((byte *)ext)[1];
      bVar6 = bVar1 < ((byte *)pcVar5)[1];
      if (bVar1 != ((byte *)pcVar5)[1]) goto LAB_0040e1b7;
      ext = (char *)((byte *)ext + 2);
      pcVar5 = (char *)((byte *)pcVar5 + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0040e1bc:
    if (iVar3 == 0) {
      iVar3 = (*grim_interface_ptr->vtable->grim_get_config_var)(auStack_10,0x51);
      return *(void **)(iVar3 + 0xc);
    }
  }
  return (void *)0x0;
}



/* mod_api_gfx_clear @ 0040e1f0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x1c: clAPI_t::GFX_Clear (bridges to grim_clear_color) */

void mod_api_gfx_clear(float r,float g,float b,float a)

{
  (*grim_interface_ptr->vtable->grim_clear_color)(r,g,b,a);
  return;
}



/* mod_api_gfx_get_string_width @ 0040e220 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x20: clAPI_t::GFX_GetStringWidth (bridges to grim_measure_text_width) */

int mod_api_gfx_get_string_width(char *string)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_measure_text_width)(string);
  return iVar1;
}



/* mod_api_gfx_printf @ 0040e240 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x24: clAPI_t::GFX_Printf */

void mod_api_gfx_printf(float x,float y,char *fmt,...)

{
  char *in_stack_00000010;
  
  crt_vsprintf(&mod_api_printf_buf,in_stack_00000010,&stack0x00000014);
  (*grim_interface_ptr->vtable->grim_draw_text_small)(y,(float)fmt,&mod_api_printf_buf);
  return;
}



/* mod_api_gfx_load_texture @ 0040e280 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x28: clAPI_t::GFX_LoadTexture (loads under mods\\ and prefixes CLM_) */

int mod_api_gfx_load_texture(char *filename)

{
  int iVar1;
  char acStack_208 [260];
  char acStack_104 [260];
  
  crt_sprintf(acStack_208,s_mods__s_00472f58,filename);
  crt_sprintf(acStack_104,s_CLM__s_00472f50,filename);
  iVar1 = texture_get_or_load(acStack_104,acStack_208);
  return iVar1;
}



/* mod_api_gfx_free_texture @ 0040e2e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x2c: clAPI_t::GFX_FreeTexture (bridges to grim_destroy_texture) */

uchar mod_api_gfx_free_texture(int texId)

{
  (*grim_interface_ptr->vtable->grim_destroy_texture)(texId);
  return '\x01';
}



/* mod_api_gfx_set_texture @ 0040e300 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x30: clAPI_t::GFX_SetTexture (bridges to grim_bind_texture(handle, 0)) */

void mod_api_gfx_set_texture(int texId)

{
  (*grim_interface_ptr->vtable->grim_bind_texture)(texId,0);
  return;
}



/* mod_api_gfx_set_color @ 0040e320 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x3c: clAPI_t::GFX_SetColor (bridges to grim_set_color) */

void mod_api_gfx_set_color(float r,float g,float b,float a)

{
  (*grim_interface_ptr->vtable->grim_set_color)(r,g,b,a);
  return;
}



/* mod_api_gfx_set_subset @ 0040e350 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x40: clAPI_t::GFX_SetSubset (bridges to grim_set_uv) */

void mod_api_gfx_set_subset(float x1,float y1,float x2,float y2)

{
  (*grim_interface_ptr->vtable->grim_set_uv)(x1,y1,x2,y2);
  return;
}



/* mod_api_gfx_set_texture_filter @ 0040e380 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x34: clAPI_t::GFX_SetTextureFilter (bridges to grim_set_config_var(21, filter))
    */

void mod_api_gfx_set_texture_filter(int filter)

{
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,filter);
  return;
}



/* mod_api_gfx_set_blend_mode @ 0040e3a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x38: clAPI_t::GFX_SetBlendMode (bridges to grim_set_config_var(19, src) and (20,
   dst)) */

void mod_api_gfx_set_blend_mode(int src,int dst)

{
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,dst);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,dst);
  return;
}



/* mod_api_gfx_begin @ 0040e3e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x44: clAPI_t::GFX_Begin (bridges to grim_begin_batch) */

void mod_api_gfx_begin(void)

{
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  mod_gfx_batch_active = 1;
  return;
}



/* mod_api_gfx_end @ 0040e400 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x48: clAPI_t::GFX_End (bridges to grim_end_batch) */

void mod_api_gfx_end(void)

{
  (*grim_interface_ptr->vtable->grim_end_batch)();
  mod_gfx_batch_active = 0;
  return;
}



/* mod_api_gfx_quad @ 0040e420 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x4c: clAPI_t::GFX_Quad (bridges to grim_draw_quad) */

void mod_api_gfx_quad(float x,float y,float w,float h)

{
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)(x,y,w,h);
  if (mod_gfx_batch_active == '\0') {
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  return;
}



/* mod_api_gfx_quad_rot @ 0040e470 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x50: clAPI_t::GFX_QuadRot */

void mod_api_gfx_quad_rot(float x,float y,float w,float h,float a)

{
  (*grim_interface_ptr->vtable->grim_set_rotation)(a);
  (*grim_interface_ptr->vtable->grim_draw_quad_rotated_matrix)(x,y,w,h);
  if (mod_gfx_batch_active == '\0') {
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  return;
}



/* mod_api_gfx_draw_quads @ 0040e4c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x54: clAPI_t::GFX_DrawQuads */

void mod_api_gfx_draw_quads(mod_vertex2_t *v,int numQuads)

{
  float afStack_8 [2];
  
  if (mod_gfx_batch_active == '\0') {
    (*grim_interface_ptr->vtable->grim_begin_batch)();
  }
  afStack_8[0] = 0.0;
  afStack_8[1] = 0.0;
  (*grim_interface_ptr->vtable->grim_submit_vertices_offset)((float *)v,numQuads,afStack_8);
  if (mod_gfx_batch_active == '\0') {
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  return;
}



/* mod_api_sfx_load_sample @ 0040e530 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x58: clAPI_t::SFX_LoadSample (loads under mods\\) */

int mod_api_sfx_load_sample(char *filename)

{
  int iVar1;
  char acStack_104 [260];
  
  crt_sprintf(acStack_104,s_mods__s_00472f58,filename);
  iVar1 = sfx_load_sample(acStack_104);
  return iVar1;
}



/* mod_api_sfx_free_sample @ 0040e560 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x5c: clAPI_t::SFX_FreeSample */

uchar mod_api_sfx_free_sample(int sfxId)

{
  int iVar1;
  
  iVar1 = sfx_release_sample(sfxId);
  return (uchar)iVar1;
}



/* mod_api_sfx_play_sample @ 0040e570 */

/* mod API vtable 0x60: clAPI_t::SFX_PlaySample */

void mod_api_sfx_play_sample(int sfxId,float pan,float volume)

{
  sfx_play_panned((float)sfxId);
  return;
}



/* mod_api_sfx_load_tune @ 0040e5b0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x64: clAPI_t::SFX_LoadTune (loads under mods\\) */

int mod_api_sfx_load_tune(char *filename)

{
  int iVar1;
  char acStack_104 [260];
  
  crt_sprintf(acStack_104,s_mods__s_00472f58,filename);
  iVar1 = music_load_track(acStack_104);
  return iVar1;
}



/* mod_api_sfx_free_tune @ 0040e5e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x68: clAPI_t::SFX_FreeTune */

uchar mod_api_sfx_free_tune(int tuneId)

{
  int iVar1;
  
  iVar1 = music_release_track(tuneId);
  return (uchar)iVar1;
}



/* mod_api_sfx_play_tune @ 0040e5f0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x6c: clAPI_t::SFX_PlayTune */

void mod_api_sfx_play_tune(int tuneId)

{
  sfx_play_exclusive(tuneId);
  return;
}



/* mod_api_sfx_stop_tune @ 0040e600 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x70: clAPI_t::SFX_StopTune */

void mod_api_sfx_stop_tune(int tuneId)

{
  sfx_mute_all(tuneId);
  return;
}



/* mod_api_inp_get_pressed_char @ 0040e610 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x7c: clAPI_t::INP_GetPressedChar (bridges to grim_get_key_char) */

char mod_api_inp_get_pressed_char(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0040e618. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*grim_interface_ptr->vtable->grim_get_key_char)();
  return (char)iVar1;
}



/* mod_api_inp_get_analog @ 0040e620 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x78: clAPI_t::INP_GetAnalog */

float mod_api_inp_get_analog(int key)

{
  float10 fVar1;
  
  if (key == 0x163) {
    return ui_mouse_x;
  }
  if (key == 0x164) {
    return ui_mouse_y;
  }
  fVar1 = (float10)(*grim_interface_ptr->vtable->grim_get_config_float)(key);
  return (float)fVar1;
}



/* mod_api_inp_key_down @ 0040e660 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x74: clAPI_t::INP_KeyDown (uses grim_is_key_active) */

uchar mod_api_inp_key_down(int key)

{
  int iVar1;
  
  if (key == 1) {
    return '\0';
  }
  iVar1 = (*grim_interface_ptr->vtable->grim_is_key_active)(key);
  return (uchar)iVar1;
}



/* mod_api_inp_get_key_name @ 0040e680 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* mod API vtable 0x80: clAPI_t::INP_GetKeyName */

char * mod_api_inp_get_key_name(int key)

{
  char *pcVar1;
  
  pcVar1 = input_key_name(key);
  return pcVar1;
}



/* mod_api_cl_enter_menu @ 0040e690 */

/* mod API vtable 0x84: clAPI_t::CL_EnterMenu (only handles "game_pause") */

void mod_api_cl_enter_menu(char *menu)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  bool bVar4;
  
  if (menu != (char *)0x0) {
    pcVar2 = s_game_pause_00472f60;
    do {
      bVar1 = *pcVar2;
      bVar4 = bVar1 < (byte)*menu;
      if (bVar1 != *menu) {
LAB_0040e6c7:
        iVar3 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
        goto LAB_0040e6cc;
      }
      if (bVar1 == 0) break;
      bVar1 = ((byte *)pcVar2)[1];
      bVar4 = bVar1 < ((byte *)menu)[1];
      if (bVar1 != ((byte *)menu)[1]) goto LAB_0040e6c7;
      pcVar2 = (char *)((byte *)pcVar2 + 2);
      menu = (char *)((byte *)menu + 2);
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0040e6cc:
    if (iVar3 == 0) {
      if (plugin_interface_ptr != (mod_interface_t *)0x0) {
        (plugin_interface_ptr->parms).fields.onPause = '\x01';
      }
      ui_transition_direction = 0;
      game_state_pending = 5;
    }
  }
  return;
}



/* mod_load_info @ 0040e700 */

/* loads mods\%s, calls CMOD_GetInfo, copies the info struct to DAT_00481c88, and returns it */

void * mod_load_info(void)

{
  FARPROC pFVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  mod_info_t *pmVar5;
  char local_200 [512];
  
  crt_sprintf(local_200,s_mods__s_00472f58);
  console_printf(&console_log_queue,s_CMOD____s__00472fec,local_200);
  plugin_module_handle = (HMODULE)LoadLibraryA(local_200);
  if (plugin_module_handle == (HMODULE)0x0) {
    console_printf(&console_log_queue,s_CMOD__Load_library_failed__00472fd0);
    return (void *)0x0;
  }
  pFVar1 = GetProcAddress((HMODULE)plugin_module_handle,s_CMOD_GetInfo_00472fc0);
  if (pFVar1 != (FARPROC)0x0) {
    if ((game_font_handle & 1) == 0) {
      game_font_handle = game_font_handle | 1;
      mod_info_block.version = 1.0;
      mod_info_block.usesApiVersion = 3;
      pmVar5 = &mod_info_block;
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        pmVar5->name[0] = '\0';
        pmVar5->name[1] = '\0';
        pmVar5->name[2] = '\0';
        pmVar5->name[3] = '\0';
        pmVar5 = (mod_info_t *)(pmVar5->name + 4);
      }
      pcVar4 = mod_info_block.author;
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        pcVar4[0] = '\0';
        pcVar4[1] = '\0';
        pcVar4[2] = '\0';
        pcVar4[3] = '\0';
        pcVar4 = pcVar4 + 4;
      }
      crt_atexit(&DAT_0040e850);
    }
    puVar2 = (undefined4 *)(*pFVar1)();
    if (puVar2 == (undefined4 *)0x0) {
      console_printf(&console_log_queue,s_CMOD__bad_CMOD_GetInfo_function_00472f84);
    }
    else {
      pmVar5 = &mod_info_block;
      for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pmVar5->name = *puVar2;
        puVar2 = puVar2 + 1;
        pmVar5 = (mod_info_t *)(pmVar5->name + 4);
      }
    }
    FreeLibrary((HMODULE)plugin_module_handle);
    console_printf(&console_log_queue,s_CMOD__mod_enum___s__00472f6c,&mod_info_block);
    return &mod_info_block;
  }
  console_printf(&console_log_queue,s_CMOD_GetInfo_failed__00472fa8);
  FreeLibrary((HMODULE)plugin_module_handle);
  return (void *)0x0;
}



/* mod_load_mod @ 0040e860 */

/* loads mods\%s, calls CMOD_GetMod, wires the mod context (offset +4), and returns the mod
   interface pointer */

void * mod_load_mod(void)

{
  FARPROC pFVar1;
  void *pvVar2;
  char local_200 [512];
  
  crt_sprintf(local_200,s_mods__s_00472f58);
  console_printf(&console_log_queue,s_CMOD____s__00472fec,local_200);
  plugin_module_handle = (HMODULE)LoadLibraryA(local_200);
  if (plugin_module_handle == (HMODULE)0x0) {
    console_printf(&console_log_queue,s_CMOD__Load_library_failed__00472fd0);
    return (void *)0x0;
  }
  pFVar1 = GetProcAddress((HMODULE)plugin_module_handle,s_CMOD_GetMod_00473044);
  if (pFVar1 == (FARPROC)0x0) {
    console_printf(&console_log_queue,s_CMOD__CMOD_GetMod_failed__00473028);
    FreeLibrary((HMODULE)plugin_module_handle);
    return (void *)0x0;
  }
  pvVar2 = (void *)(*pFVar1)();
  if (pvVar2 == (void *)0x0) {
    console_printf(&console_log_queue,s_CMOD__bad_CMOD_GetMod_function_00473008);
  }
  else {
    *(mod_api_t **)((int)pvVar2 + 4) = &mod_api_context;
  }
  console_printf(&console_log_queue,s_CMOD_GetMod_ok_00472ff8);
  return pvVar2;
}



/* mods_any_available @ 0040e940 */

/* returns true if any mods\*.dll exist */

bool mods_any_available(void)

{
  HANDLE handle;
  int iVar1;
  int iVar2;
  uint local_118 [70];
  
  iVar2 = 0;
  handle = crt_findfirst(s_mods___dll_00473050,local_118);
  if ((handle != (HANDLE)0xffffffff) && (&stack0x00000000 != (undefined1 *)0x104)) {
    do {
      iVar2 = iVar2 + 1;
      iVar1 = crt_findnext(handle,local_118);
    } while (iVar1 == 0);
  }
  crt_findclose(handle);
  return iVar2 != 0;
}


