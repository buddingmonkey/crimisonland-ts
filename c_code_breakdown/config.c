/* config_init_defaults @ 004028f0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* initializes default config globals, key bindings, and name slots */

int config_init_defaults(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char (*pacVar7) [27];
  char *pcVar8;
  char (*pacStack_4) [27];
  
  config_blob.reserved0[0x74] = '\0';
  config_blob.reserved0[0x75] = '\0';
  config_blob.reserved0[0x76] = '\0';
  config_blob.reserved0[0x77] = '\0';
  config_blob.reserved0[0x78] = '\0';
  config_blob.reserved0[0x79] = '\0';
  config_blob.reserved0[0x7a] = '\0';
  config_blob.reserved0[0x7b] = '\0';
  config_blob.hardcore = '\0';
  config_blob.full_version = '\x01';
  config_blob.perk_prompt_counter = 0;
  config_blob.reserved8[0] = '\0';
  config_blob.reserved8[1] = '\0';
  config_blob.reserved8[2] = '\0';
  config_blob.reserved8[3] = '?';
  config_blob.reserved6[0] = '\x01';
  config_blob.reserved6[1] = '\0';
  config_blob.reserved6[2] = '\0';
  config_blob.reserved6[3] = '\0';
  config_blob.key_pick_perk = 0x101;
  config_blob.key_reload = 0x102;
  config_blob.reserved7[0] = '\0';
  config_blob.reserved0[0x70] = '\0';
  config_blob.reserved0[0x71] = '\0';
  config_blob.reserved0[0x72] = 0x80;
  config_blob.reserved0[0x73] = '?';
  config_blob.score_load_gate = '\0';
  config_blob.reserved0[0x7c] = '\0';
  iVar4 = 0;
  pacStack_4 = config_blob.saved_names;
  iVar5 = 0x88;
  do {
    uVar2 = 0xffffffff;
    *(int *)(config_blob.reserved0 + iVar5) = iVar4;
    pcVar6 = s_default;
    do {
      pcVar8 = pcVar6;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    iVar5 = iVar5 + 4;
    pcVar6 = pcVar8 + -uVar2;
    pacVar7 = pacStack_4;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)*pacVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pacVar7 = (char (*) [27])(*pacVar7 + 4);
    }
    iVar4 = iVar4 + 1;
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      (*pacVar7)[0] = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pacVar7 = (char (*) [27])(*pacVar7 + 1);
    }
    pacStack_4 = pacStack_4 + 1;
  } while (iVar5 < 0xa8);
  config_blob.reserved0[3] = '\0';
  config_blob.reserved0[2] = '\0';
  pcVar6 = config_blob.player_name;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  uVar2 = 0xffffffff;
  pcVar6 = &default_player_name;
  do {
    pcVar8 = pcVar6;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar6 = pcVar8 + -uVar2;
  pcVar8 = config_blob.player_name;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  config_blob.reserved0[0x84] = '\x01';
  config_blob.reserved0[0x85] = '\0';
  config_blob.reserved0[0x86] = '\0';
  config_blob.reserved0[0x87] = '\0';
  config_blob.reserved0[0x80] = '\0';
  config_blob.reserved0[0x81] = '\0';
  config_blob.reserved0[0x82] = '\0';
  config_blob.reserved0[0x83] = '\0';
  config_blob.reserved0[0] = '\0';
  config_blob.reserved0[1] = '\0';
  config_blob.fx_toggle = '\0';
  config_blob.reserved6[0x10] = '\x01';
  config_blob.reserved1[4] = '\0';
  config_blob.reserved1[5] = '\0';
  config_blob.reserved1[6] = '\0';
  config_blob.reserved1[7] = '\0';
  config_blob.reserved1[8] = '\0';
  config_blob.reserved1[9] = '\0';
  config_blob.reserved1[10] = '\0';
  config_blob.reserved1[0xb] = '\0';
  config_blob.reserved0[0x6c] = '\0';
  config_blob.reserved0[0x6d] = '\0';
  config_blob.reserved0[0x6e] = '\0';
  config_blob.reserved0[0x6f] = '\0';
  config_blob.display_bpp = 0x20;
  config_blob.windowed._0_1_ = 0;
  config_blob.reserved0[0x18] = '\x01';
  config_blob.reserved0[0x19] = '\0';
  config_blob.reserved0[0x1a] = '\0';
  config_blob.reserved0[0x1b] = '\0';
  config_blob.reserved0[0xe] = '\x01';
  config_blob.reserved0[0xf] = '\0';
  config_blob.reserved0[0x10] = '\x01';
  config_blob.reserved0[0x1c] = '\x02';
  config_blob.reserved0[0x1d] = '\0';
  config_blob.reserved0[0x1e] = '\0';
  config_blob.reserved0[0x1f] = '\0';
  config_blob.reserved0[0x20] = '\x02';
  config_blob.reserved0[0x21] = '\0';
  config_blob.reserved0[0x22] = '\0';
  config_blob.reserved0[0x23] = '\0';
  config_blob.reserved0[0x44] = '\0';
  config_blob.reserved0[0x45] = '\0';
  config_blob.reserved0[0x46] = '\0';
  config_blob.reserved0[0x47] = '\0';
  config_blob.reserved0[0x48] = '\0';
  config_blob.reserved0[0x49] = '\0';
  config_blob.reserved0[0x4a] = '\0';
  config_blob.reserved0[0x4b] = '\0';
  config_blob.reserved0[0x11] = '\x01';
  config_blob.reserved0[0x14] = '\x01';
  config_blob.reserved0[0x15] = '\0';
  config_blob.reserved0[0x16] = '\0';
  config_blob.reserved0[0x17] = '\0';
  config_blob.keybinds_p1[3] = 0x20;
  config_blob.detail_preset = 5;
  config_blob.reserved1[0xc] = '(';
  config_blob.reserved1[0xd] = '#';
  config_blob.reserved1[0xe] = '\0';
  config_blob.reserved1[0xf] = '\0';
  config_blob.reserved1[0x10] = 'x';
  config_blob.reserved1[0x11] = 'i';
  config_blob.reserved1[0x12] = '\0';
  config_blob.reserved1[0x13] = '\0';
  config_blob.reserved1[0] = 'd';
  config_blob.reserved1[1] = '\0';
  config_blob.reserved1[2] = '\0';
  config_blob.reserved1[3] = '\0';
  config_blob.screen_width = 800;
  config_blob.screen_height = 600;
  config_blob.sfx_volume = 1.0;
  config_blob.music_volume = 1.0;
  config_blob.keybinds_p1[0] = 0x11;
  config_blob.keybinds_p1[1] = 0x1f;
  config_blob.keybinds_p1[2] = 0x1e;
  config_blob.keybinds_p1[4] = 0x100;
  config_blob.keybinds_p1[5] = 0x17e;
  config_blob.keybinds_p1[6] = 0x17e;
  config_blob.keybinds_p1[7] = 0x10;
  config_blob.keybinds_p1[8] = 0x12;
  config_blob.keybinds_p1[9] = 0x13f;
  config_blob.keybinds_p1[10] = 0x140;
  config_blob.keybinds_p1[0xb] = 0x141;
  config_blob.keybinds_p1[0xc] = 0x153;
  config_blob.reserved2[0] = '~';
  config_blob.reserved2[1] = '\x01';
  config_blob.reserved2[2] = '\0';
  config_blob.reserved2[3] = '\0';
  config_blob.reserved2[4] = '~';
  config_blob.reserved2[5] = '\x01';
  config_blob.reserved2[6] = '\0';
  config_blob.reserved2[7] = '\0';
  config_blob.reserved2[8] = '~';
  config_blob.reserved2[9] = '\x01';
  config_blob.reserved2[10] = '\0';
  config_blob.reserved2[0xb] = '\0';
  config_blob.keybinds_p2[0] = 200;
  config_blob.keybinds_p2[1] = 0xd0;
  config_blob.keybinds_p2[2] = 0xcb;
  config_blob.keybinds_p2[3] = 0xcd;
  config_blob.keybinds_p2[4] = 0x9d;
  config_blob.keybinds_p2[5] = 0x17e;
  config_blob.keybinds_p2[6] = 0x17e;
  config_blob.keybinds_p2[7] = 0xd3;
  config_blob.keybinds_p2[8] = 0xd1;
  config_blob.keybinds_p2[9] = 0x13f;
  config_blob.keybinds_p2[10] = 0x140;
  config_blob.keybinds_p2[0xb] = 0x141;
  config_blob.keybinds_p2[0xc] = 0x153;
  config_blob.reserved3[0] = '~';
  config_blob.reserved3[1] = '\x01';
  config_blob.reserved3[2] = '\0';
  config_blob.reserved3[3] = '\0';
  config_blob.reserved3[4] = '~';
  config_blob.reserved3[5] = '\x01';
  config_blob.reserved3[6] = '\0';
  config_blob.reserved3[7] = '\0';
  config_blob.reserved3[8] = '~';
  config_blob.reserved3[9] = '\x01';
  config_blob.reserved3[10] = '\0';
  config_blob.reserved3[0xb] = '\0';
  config_blob.reserved0[4] = '\x01';
  config_blob.reserved0[5] = '\x01';
  return 0x17e;
}



/* game_build_path @ 00402bd0 */

/* builds a game path by combining game_base_path with filename */

char * game_build_path(char *filename)

{
  crt_sprintf(&game_path_buf,s__s__s_00471324,&game_base_path,filename);
  return &game_path_buf;
}



/* register_core_cvars @ 00402c00 */

/* registers built-in cvars */

void register_core_cvars(void)

{
  cv_silentloads = console_register_cvar(&console_log_queue,s_cv_silentloads_00471434,&cvar_default_value_b)
  ;
  cv_terrainFilter =
       console_register_cvar(&console_log_queue,s_cv_terrainFilter_00471420,&cvar_default_value_b);
  cv_bodiesFade = console_register_cvar(&console_log_queue,s_cv_bodiesFade_00471410,&cvar_default_value_b);
  cv_uiTransparency =
       console_register_cvar(&console_log_queue,s_cv_uiTransparency_004713fc,&cvar_default_value_b);
  cv_uiPointFilterPanels =
       console_register_cvar(&console_log_queue,s_cv_uiPointFilterPanels_004713e0,&cvar_default_value);
  cv_enableMousePointAndClickMovement =
       console_register_cvar
                 (&console_log_queue,s_cv_enableMousePointAndClickMovem_004713bc,&cvar_default_value);
  cv_verbose = console_register_cvar(&console_log_queue,s_cv_verbose_004713b0,&cvar_default_value);
  cv_terrainBodiesTransparency =
       console_register_cvar
                 (&console_log_queue,s_cv_terrainBodiesTransparency_00471390,&cvar_default_value);
  cv_uiSmallIndicators =
       console_register_cvar(&console_log_queue,s_cv_uiSmallIndicators_00471378,&cvar_default_value);
  cv_aimEnhancementFade =
       console_register_cvar(&console_log_queue,s_cv_aimEnhancementFade_00471360,&DAT_00471260);
  cv_friendlyFire =
       console_register_cvar(&console_log_queue,s_cv_friendlyFire_00471350,&cvar_default_value);
  cv_showFPS = console_register_cvar(&console_log_queue,s_cv_showFPS_00471344,&cvar_default_value);
  cv_padAimDistMul =
       console_register_cvar(&console_log_queue,s_cv_padAimDistMul_0047132c,&DAT_00471340);
  return;
}



/* game_core_init @ 00403500 */

/* initializes core game systems (quests, effects, UI assets) and sets initial state */

int game_core_init(void)

{
  undefined3 extraout_var;
  
  console_printf(&console_log_queue,s_GDI_initializing_UI_elements__00471468);
  quest_database_init();
  effect_defaults_reset();
  ui_menu_assets_init();
  bonus_metadata_init();
  render_pass_mode = 0;
  game_state_set(0);
  console_printf(&console_log_queue,s_Core_Init_done__00471454);
  return CONCAT31(extraout_var,1);
}



/* config_sync_from_grim @ 0041ec60 */

/* syncs Grim config values into config blob and writes crimson.cfg */

int config_sync_from_grim(void)

{
  char cVar1;
  undefined1 *puVar2;
  int *piVar3;
  uchar *puVar4;
  char *pcVar5;
  FILE *pFVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  highscore_record_t *phVar10;
  highscore_record_t *phVar11;
  uchar *puVar12;
  char *pcVar13;
  char *pcStack_494;
  uint local_490 [4];
  char acStack_480 [14];
  undefined1 uStack_472;
  undefined1 uStack_471;
  undefined1 uStack_470;
  undefined1 uStack_46f;
  undefined4 uStack_46c;
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined4 uStack_460;
  undefined4 uStack_43c;
  undefined4 uStack_438;
  undefined4 uStack_414;
  undefined4 uStack_410;
  char acStack_40c [12];
  undefined4 uStack_400;
  undefined4 uStack_3fc;
  int aiStack_3f8 [8];
  char acStack_3d8 [216];
  char acStack_300 [36];
  undefined4 uStack_2dc;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined4 uStack_2c0;
  undefined1 uStack_2bc;
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined4 uStack_2b0;
  undefined4 uStack_2ac;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined4 uStack_2a0;
  undefined4 uStack_29c;
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined4 uStack_290;
  undefined4 uStack_28c;
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined4 uStack_280;
  undefined4 uStack_27c;
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined4 uStack_270;
  undefined4 uStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined4 uStack_260;
  undefined4 uStack_25c;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined4 uStack_240;
  undefined4 uStack_23c;
  undefined1 uStack_38;
  undefined1 uStack_37;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined1 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  uchar uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar2 = (undefined1 *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,8);
  config_blob.windowed._0_1_ = *puVar2;
  piVar3 = (int *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,0x2b);
  config_blob.display_bpp = *piVar3;
  piVar3 = (int *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,0x29);
  config_blob.screen_width = *piVar3;
  piVar3 = (int *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,0x2a);
  config_blob.screen_height = *piVar3;
  puVar4 = (uchar *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,0x59);
  config_blob.reserved0._112_4_ = *(undefined4 *)puVar4;
  puVar4 = (uchar *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_490,0x54);
  config_blob.player_name_length = player_name_length;
  config_blob.reserved7[0] = *puVar4;
  uVar7 = 0xffffffff;
  phVar10 = &highscore_active_record;
  do {
    phVar11 = phVar10;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    phVar11 = (highscore_record_t *)(phVar10->player_name + 1);
    pcVar5 = phVar10->player_name;
    phVar10 = phVar11;
  } while (*pcVar5 != '\0');
  uVar7 = ~uVar7;
  pcVar5 = (char *)((int)phVar11 - uVar7);
  pcVar13 = config_blob.player_name;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar13 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar13 = pcVar13 + 1;
  }
  if (grim_config_invoked != '\0') {
    pcStack_494 = acStack_3d8;
    acStack_40c[0] = '\0';
    acStack_40c[1] = '\0';
    acStack_40c[2] = '\0';
    acStack_40c[3] = '\0';
    uStack_38 = 0;
    acStack_40c[4] = '\0';
    acStack_40c[5] = '\0';
    acStack_40c[6] = '\0';
    acStack_40c[7] = '\0';
    uStack_37 = 1;
    uStack_34 = 0;
    uStack_c = 0x3f000000;
    uStack_30 = 1;
    uStack_8 = 0x101;
    uStack_4 = 0x102;
    uStack_12 = 0;
    uStack_410 = 0x3f800000;
    uStack_13 = 0;
    acStack_40c[8] = 0;
    iVar9 = 0;
    piVar3 = aiStack_3f8;
    do {
      uVar7 = 0xffffffff;
      *piVar3 = iVar9;
      pcVar5 = s_default;
      do {
        pcVar13 = pcVar5;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar13 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar13;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      piVar3 = piVar3 + 1;
      pcVar5 = pcVar13 + -uVar7;
      pcVar13 = pcStack_494;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar13 = pcVar13 + 4;
      }
      iVar9 = iVar9 + 1;
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar13 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar13 = pcVar13 + 1;
      }
      pcStack_494 = pcStack_494 + 0x1b;
    } while (iVar9 < 8);
    acStack_480[3] = 0;
    acStack_480[2] = 0;
    pcVar5 = acStack_300;
    for (iVar9 = 8; iVar9 != 0; iVar9 = iVar9 + -1) {
      pcVar5[0] = '\0';
      pcVar5[1] = '\0';
      pcVar5[2] = '\0';
      pcVar5[3] = '\0';
      pcVar5 = pcVar5 + 4;
    }
    uVar7 = 0xffffffff;
    pcVar5 = &default_player_name;
    do {
      pcVar13 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar13 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar13;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    pcVar5 = pcVar13 + -uVar7;
    pcVar13 = acStack_300;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar13 = pcVar13 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar13 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar13 = pcVar13 + 1;
    }
    uStack_3fc = 1;
    uStack_20 = 1;
    uStack_2c8 = 0x20;
    uStack_468 = 1;
    uStack_472 = 1;
    uStack_470 = 1;
    uStack_46f = 1;
    uStack_46c = 1;
    uStack_2ac = 0x20;
    uStack_400 = 0;
    uStack_10 = 5;
    acStack_480[0] = '\0';
    acStack_480[1] = 0;
    uStack_14 = '\0';
    uStack_2d8 = 0;
    uStack_2d4 = 0;
    uStack_2d0 = 9000;
    uStack_2cc = 27000;
    uStack_2dc = 100;
    uStack_414 = 0;
    uStack_2c4 = 800;
    uStack_2c0 = 600;
    uStack_2bc = 0;
    uStack_471 = 0;
    uStack_464 = 2;
    uStack_460 = 2;
    uStack_43c = 0;
    uStack_438 = 0;
    uStack_1c = 0x3f800000;
    uStack_18 = 0x3f800000;
    uStack_2b8 = 0x11;
    uStack_2b4 = 0x1f;
    uStack_2b0 = 0x1e;
    uStack_2a8 = 0x100;
    uStack_2a4 = 0x17e;
    uStack_2a0 = 0x17e;
    uStack_29c = 0x10;
    uStack_298 = 0x12;
    uStack_294 = 0x13f;
    uStack_290 = 0x140;
    uStack_28c = 0x141;
    uStack_288 = 0x153;
    uStack_284 = 0x17e;
    uStack_280 = 0x17e;
    uStack_27c = 0x17e;
    uStack_278 = 200;
    uStack_274 = 0xd0;
    uStack_270 = 0xcb;
    uStack_26c = 0xcd;
    uStack_268 = 0x9d;
    uStack_264 = 0x17e;
    uStack_260 = 0x17e;
    uStack_25c = 0xd3;
    pcVar13 = &file_mode_read_binary;
    uStack_258 = 0xd1;
    uStack_254 = 0x13f;
    uStack_250 = 0x140;
    uStack_24c = 0x141;
    uStack_248 = 0x153;
    uStack_244 = 0x17e;
    uStack_240 = 0x17e;
    uStack_23c = 0x17e;
    acStack_480[4] = '\x01';
    acStack_480[5] = '\x01';
    pcVar5 = game_build_path(config_filename);
    pFVar6 = (FILE *)crt_fopen(pcVar5,pcVar13);
    if (pFVar6 != (FILE *)0x0) {
      crt_fseek((int *)pFVar6,0,2);
      iVar9 = crt_ftell((char *)pFVar6);
      if (iVar9 == 0x480) {
        crt_fseek((int *)pFVar6,0,0);
        crt_fread(acStack_480,0x480,1,(int *)pFVar6);
        uVar7 = 0xffffffff;
        pcVar5 = acStack_40c;
        do {
          pcVar13 = pcVar5;
          if (uVar7 == 0) break;
          uVar7 = uVar7 - 1;
          pcVar13 = pcVar5 + 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar13;
        } while (cVar1 != '\0');
        uVar7 = ~uVar7;
        config_blob.fx_toggle = uStack_14;
        puVar4 = (uchar *)(pcVar13 + -uVar7);
        puVar12 = config_blob.reserved0 + 0x74;
        for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
          *(undefined4 *)puVar12 = *(undefined4 *)puVar4;
          puVar4 = puVar4 + 4;
          puVar12 = puVar12 + 4;
        }
        for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar12 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar12 = puVar12 + 1;
        }
      }
      crt_fclose(pFVar6);
    }
  }
  pcVar13 = &file_mode_write_binary;
  pcVar5 = game_build_path(config_filename);
  pFVar6 = (FILE *)crt_fopen(pcVar5,pcVar13);
  iVar9 = 0;
  if (pFVar6 != (FILE *)0x0) {
    crt_fwrite((char *)&config_blob,0x480,1,(int *)pFVar6);
    iVar9 = crt_fclose(pFVar6);
  }
  return CONCAT31((int3)((uint)iVar9 >> 8),1);
}



/* config_ensure_file @ 0041f130 */

/* creates crimson.cfg when missing (writes default config blob) */

void config_ensure_file(void)

{
  char *pcVar1;
  FILE *pFVar2;
  char *pcVar3;
  
  pcVar3 = &file_mode_read_binary;
  pcVar1 = game_build_path(config_filename);
  pFVar2 = (FILE *)crt_fopen(pcVar1,pcVar3);
  if (pFVar2 != (FILE *)0x0) {
    crt_fclose(pFVar2);
    return;
  }
  pcVar3 = &file_mode_write_binary;
  config_blob.fx_toggle = '\x01';
  pcVar1 = game_build_path(config_filename);
  pFVar2 = (FILE *)crt_fopen(pcVar1,pcVar3);
  if (pFVar2 != (FILE *)0x0) {
    crt_fwrite((char *)&config_blob,0x480,1,(int *)pFVar2);
    crt_fclose(pFVar2);
  }
  return;
}



/* config_load_presets @ 0041f1a0 */

/* loads config presets into globals */

uint config_load_presets(void)

{
  char *pcVar1;
  FILE *fp;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  uint uVar7;
  highscore_record_t *phVar8;
  undefined4 in_stack_ffffff70;
  undefined4 in_stack_ffffffc0;
  undefined4 uVar9;
  char cVar10;
  char *pcVar11;
  
  pcVar11 = &file_mode_read_binary;
  player_state_table.input.move_key_forward = 0x11;
  player_state_table.input.move_key_backward = 0x1f;
  player_state_table.input.turn_key_left = 0x1e;
  player_state_table.input.turn_key_right = 0x20;
  player_state_table.input.fire_key = 0xf;
  player_state_table.input.key_reserved_0 = 0x11;
  player_state_table.input.key_reserved_1 = 0x1f;
  player_state_table.input.aim_key_left = 0x10;
  player_state_table.input.aim_key_right = 0x12;
  player_alt_move_key_forward = 200;
  player_alt_move_key_backward = 0xd0;
  player_alt_turn_key_left = 0xcb;
  player_alt_turn_key_right = 0xcd;
  player_alt_fire_key = 0x9d;
  player_alt_key_reserved_0 = 0x11;
  player_alt_key_reserved_1 = 0x1f;
  player_alt_key_reserved_2 = 0xd3;
  player_alt_key_reserved_3 = 0xc9;
  pcVar1 = game_build_path(config_filename);
  fp = (FILE *)crt_fopen(pcVar1,pcVar11);
  if (fp == (FILE *)0x0) {
    return 0;
  }
  crt_fseek((int *)fp,0,2);
  iVar2 = crt_ftell((char *)fp);
  if (iVar2 != 0x480) {
    crt_fclose(fp);
    uVar3 = config_sync_from_grim();
    return uVar3 & 0xffffff00;
  }
  cVar10 = '\0';
  crt_fseek((int *)fp,0,0);
  crt_fread((char *)&config_blob,0x480,1,(int *)fp);
  uVar9 = 0x41f2ba;
  crt_fclose(fp);
  piVar6 = &player_state_table.input.move_key_backward;
  piVar4 = config_blob.keybinds_p1 + 0xc;
  do {
    piVar5 = piVar4 + 0x10;
    ((player_input_t *)(piVar6 + -1))->move_key_forward = piVar4[-0xc];
    *piVar6 = piVar4[-0xb];
    piVar6[1] = piVar4[-10];
    piVar6[2] = piVar4[-9];
    piVar6[3] = piVar4[-8];
    piVar6[4] = piVar4[-7];
    piVar6[5] = piVar4[-6];
    piVar6[6] = piVar4[-5];
    piVar6[7] = piVar4[-4];
    piVar6[9] = piVar4[-3];
    piVar6[8] = piVar4[-2];
    piVar6[0xb] = piVar4[-1];
    piVar6[10] = *piVar4;
    piVar6 = piVar6 + 0xd8;
    piVar4 = piVar5;
  } while ((int)piVar5 < 0x4805c0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x59,config_blob.reserved0._112_4_);
  if (cVar10 == '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (0x54,CONCAT31((int3)((uint)uVar9 >> 8),config_blob.reserved7[0]));
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (8,CONCAT31((int3)((uint)in_stack_ffffffc0 >> 8),(undefined1)config_blob.windowed));
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x2b,config_blob.display_bpp);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x29,config_blob.screen_width);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x2a,config_blob.screen_height);
    (*grim_interface_ptr->vtable->grim_set_config_var)
              (0x53,CONCAT31((int3)((uint)in_stack_ffffff70 >> 8),config_blob.reserved0[0]));
  }
  uVar3 = 0xffffffff;
  pcVar1 = config_blob.player_name;
  do {
    pcVar11 = pcVar1;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar11 = pcVar1 + 1;
    cVar10 = *pcVar1;
    pcVar1 = pcVar11;
  } while (cVar10 != '\0');
  uVar3 = ~uVar3;
  pcVar1 = pcVar11 + -uVar3;
  phVar8 = &highscore_active_record;
  for (uVar7 = uVar3 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)phVar8->player_name = *(undefined4 *)pcVar1;
    pcVar1 = pcVar1 + 4;
    phVar8 = (highscore_record_t *)(phVar8->player_name + 4);
  }
  for (uVar7 = uVar3 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    phVar8->player_name[0] = *pcVar1;
    pcVar1 = pcVar1 + 1;
    phVar8 = (highscore_record_t *)(phVar8->player_name + 1);
  }
  player_name_length = config_blob.player_name_length;
  config_blob.reserved0[2] = '\0';
  config_blob.reserved0[0x80] = '\0';
  config_blob.reserved0[0x81] = '\0';
  config_blob.reserved0[0x82] = '\0';
  config_blob.reserved0[0x83] = '\0';
  return CONCAT31((int3)(uVar3 >> 8),1);
}



/* reg_read_dword_default @ 0042a980 */

/* reads a registry DWORD or writes fallback to output */

int __cdecl reg_read_dword_default(HKEY key,char *name,uint *out,uint fallback)

{
  uint *puVar1;
  LONG LVar2;
  DWORD local_4;
  
  puVar1 = out;
  local_4 = 4;
  LVar2 = RegQueryValueExA((HKEY)key,name,(LPDWORD)0x0,(LPDWORD)&out,(LPBYTE)out,&local_4);
  if (LVar2 != 0) {
    *puVar1 = fallback;
  }
  return 0;
}



/* reg_write_dword @ 0042a9c0 */

/* writes a registry DWORD */

int __cdecl reg_write_dword(HKEY key,char *name,uint value)

{
  LONG LVar1;
  
  LVar1 = RegSetValueExA((HKEY)key,name,0,4,(BYTE *)&value,4);
  return -(uint)(LVar1 != 0) & 0x80004005;
}



/* config_apply_detail_preset @ 00447580 */

/* Applies config_detail_preset ("Graphics detail" 1..5) to the config_fx_detail_flag0/1/2 bytes. */

void config_apply_detail_preset(void)

{
  switch(config_blob.detail_preset) {
  case 1:
    config_blob.reserved0[0x11] = '\0';
  case 2:
    config_blob.reserved0[0xe] = '\0';
    config_blob.reserved0[0x10] = '\0';
    return;
  case 3:
  case 4:
  case 5:
    config_blob.reserved0[0x10] = '\x01';
    config_blob.reserved0[0x11] = '\x01';
    config_blob.reserved0[0xe] = '\x01';
  default:
    return;
  }
}


