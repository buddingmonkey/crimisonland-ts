/* demo_setup_variant_0 @ 00402ed0 */

/* demo setup 0: 2P, spawns template 0x38 grid, assigns weapon 0xb */

void demo_setup_variant_0(void)

{
  uint uVar1;
  uint uVar2;
  int local_1c;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  config_blob.reserved0[0x14] = '\x02';
  config_blob.reserved0[0x15] = '\0';
  config_blob.reserved0[0x16] = '\0';
  config_blob.reserved0[0x17] = '\0';
  demo_time_limit_ms = 4000;
  uVar2 = 0;
  local_1c = 0x100;
  do {
    uVar1 = uVar2 & 0x80000001;
    if ((int)uVar1 < 0) {
      uVar1 = (uVar1 - 1 | 0xfffffffe) + 1;
    }
    local_10 = (float)(int)((uVar1 + 2) * 0x40);
    local_c = (float)local_1c;
    creature_spawn_template(0x38,&local_10,-100.0);
    local_8 = (float)(int)(uVar1 * 0x40 + 0x31e);
    local_4 = (float)local_1c;
    creature_spawn_template(0x38,&local_8,-100.0);
    local_1c = local_1c + 0x50;
    uVar2 = uVar2 + 1;
  } while (local_1c < 0x6a0);
  player_state_table.pos_x = 448.0;
  player_state_table.pos_y = 384.0;
  player2_pos_x = 0x44088000;
  player2_pos_y = 0x44238000;
  weapon_assign_player(0,0xb);
  weapon_assign_player(1,0xb);
  return;
}



/* demo_setup_variant_2 @ 00402fe0 */

/* demo setup 2: 1P, spawns template 0x41 columns, assigns weapon 0x15 */

void demo_setup_variant_2(void)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  int local_28;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  config_blob.reserved0[0x14] = '\x01';
  config_blob.reserved0[0x15] = '\0';
  config_blob.reserved0[0x16] = '\0';
  config_blob.reserved0[0x17] = '\0';
  demo_time_limit_ms = 5000;
  uVar2 = 0;
  local_28 = 0x80;
  do {
    uVar3 = uVar2 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    local_20 = (float)(int)(uVar3 * 0x40 + 0x20);
    fVar1 = (float)local_28;
    local_1c = fVar1;
    creature_spawn_template(0x41,&local_20,-100.0);
    local_18 = (float)(int)((uVar3 + 2) * 0x40);
    local_14 = fVar1;
    creature_spawn_template(0x41,&local_18,-100.0);
    local_10 = (float)(int)(uVar3 * 0x40 + -0x40);
    local_c = fVar1;
    creature_spawn_template(0x41,&local_10,-100.0);
    local_8 = (float)(int)((uVar3 + 0xc) * 0x40);
    local_4 = fVar1;
    creature_spawn_template(0x41,&local_8,-100.0);
    local_28 = local_28 + 0x3c;
    uVar2 = uVar2 + 1;
  } while (local_28 < 0x350);
  weapon_assign_player(0,0x15);
  return;
}



/* demo_setup_variant_1 @ 004030f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* demo setup 1: 2P, terrain preset game_level_score_table, templates 0x34/0x35, weapon 5, power-up timer */

void demo_setup_variant_1(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  config_blob.reserved0[0x14] = '\x02';
  config_blob.reserved0[0x15] = '\0';
  config_blob.reserved0[0x16] = '\0';
  config_blob.reserved0[0x17] = '\0';
  terrain_generate(&game_level_score_table);
  demo_time_limit_ms = 5000;
  iVar3 = 0;
  do {
    iVar1 = crt_rand();
    iVar2 = crt_rand();
    local_c = (float)(iVar2 % 899 + 0x40);
    local_10 = (float)(iVar1 % 200 + 0x20);
    creature_spawn_template(0x34,&local_10,-100.0);
    if (iVar3 % 3 != 0) {
      iVar1 = crt_rand();
      iVar2 = crt_rand();
      local_4 = (float)(iVar2 % 899 + 0x40);
      local_8 = (float)(iVar1 % 0x1e + 0x20);
      creature_spawn_template(0x35,&local_8,-100.0);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x14);
  player_state_table.pos_x = 490.0;
  player_state_table.pos_y = 448.0;
  player2_pos_x = 0x43f00000;
  player2_pos_y = 0x44100000;
  weapon_assign_player(0,5);
  weapon_assign_player(1,5);
  bonus_weapon_power_up_timer = 0x41700000;
  return;
}



/* demo_setup_variant_3 @ 00403250 */

/* demo setup 3: 1P, quest-selected terrain, templates 0x24/0x25, weapon 0x12 */

void demo_setup_variant_3(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  config_blob.reserved0[0x14] = '\x01';
  config_blob.reserved0[0x15] = '\0';
  config_blob.reserved0[0x16] = '\0';
  config_blob.reserved0[0x17] = '\0';
  terrain_generate(&quest_selected_meta);
  demo_time_limit_ms = 4000;
  iVar3 = 0;
  do {
    iVar1 = crt_rand();
    iVar2 = crt_rand();
    local_c = (float)(iVar2 % 899 + 0x40);
    local_10 = (float)(iVar1 % 200 + 0x20);
    creature_spawn_template(0x24,&local_10,0.0);
    if (iVar3 % 3 != 0) {
      iVar1 = crt_rand();
      iVar2 = crt_rand();
      local_4 = (float)(iVar2 % 899 + 0x40);
      local_8 = (float)(iVar1 % 0x1e + 0x20);
      creature_spawn_template(0x25,&local_8,0.0);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x14);
  player_state_table.pos_x = 512.0;
  player_state_table.pos_y = 512.0;
  weapon_assign_player(0,0x12);
  return;
}



/* demo_purchase_interstitial_begin @ 00403370 */

/* demo setup: activates the purchase/upsell interstitial (sets demo_time_limit_ms=10000 and
   demo_purchase_screen_active=1) */

void demo_purchase_interstitial_begin(void)

{
  demo_time_limit_ms = 10000;
  demo_purchase_screen_active = 1;
  return;
}



/* demo_mode_start @ 00403390 */

/* starts demo mode and cycles the demo setup */

int demo_mode_start(void)

{
  int iVar1;
  
  if (game_state_id != 9) {
    game_state_set(9);
  }
  demo_purchase_screen_active = 0;
  demo_mode_active = 1;
  gameplay_reset_state();
  config_blob.reserved0[0x18] = '\x01';
  config_blob.reserved0[0x19] = '\0';
  config_blob.reserved0[0x1a] = '\0';
  config_blob.reserved0[0x1b] = '\0';
  if (demo_variant_index == 0) {
    demo_setup_variant_0();
  }
  else if (demo_variant_index == 1) {
    demo_setup_variant_1();
  }
  else if (demo_variant_index == 2) {
    demo_setup_variant_2();
  }
  else if (demo_variant_index == 3) {
    demo_setup_variant_3();
  }
  else if (demo_variant_index == 4) {
    demo_setup_variant_0();
  }
  else {
    demo_purchase_interstitial_begin();
  }
  iVar1 = demo_variant_index + 1;
  quest_spawn_timeline = 0;
  screen_fade_in_flag = 0;
  demo_variant_index = iVar1 % 6;
  return iVar1 / 6;
}



/* demo_trial_overlay_render @ 004047c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the demo trial warning panel and remaining time message */

void __cdecl demo_trial_overlay_render(float *xy,float alpha)

{
  IGrim2D_vtbl *pIVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  float fVar7;
  char acStack_118 [8];
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  float local_104;
  char acStack_98 [152];
  
  local_104 = alpha * 0.8;
  game_loading_flag = 1;
  local_110 = 0;
  local_10c = 0;
  local_108 = 0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(xy,512.0,256.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)xy);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(xy,512.0,256.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  fVar7 = 0.0;
  pIVar1 = grim_interface_ptr->vtable;
  iVar3 = (*pIVar1->grim_get_texture_handle)(s_cl_logo_00471f70);
  (*pIVar1->grim_bind_texture)(iVar3,(int)fVar7);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)(*xy + 72.0,xy[1] + 22.0,371.2,46.4);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 131.0,xy[1] + 9.0,s_You_ve_been_playing_the_Demo_ver_00471f48)
  ;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)xy);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  fVar7 = *xy + 26.0;
  fVar2 = xy[1] + 80.0;
  iVar3 = trial_time_limit_ms_get();
  iVar3 = iVar3 - game_status_blob.game_sequence_id;
  if (0 < demo_trial_elapsed_ms) {
    iVar3 = 300000 - demo_trial_elapsed_ms;
  }
  iVar5 = (iVar3 / 1000) / 0x3c;
  iVar4 = (int)((ulonglong)((longlong)iVar5 * 0x77777777) >> 0x20) - iVar5;
  iVar5 = iVar5 + ((iVar4 >> 5) - (iVar4 >> 0x1f)) * 0x3c;
  iVar4 = iVar3 / 1000 + iVar5 * -0x3c;
  iVar3 = (iVar3 + (iVar5 * 0x3c + iVar4) * -1000) / 10;
  if (iVar5 < 0) {
    iVar4 = 0;
    iVar3 = 0;
    pcVar6 = &s_int_format_0d;
    iVar5 = 0;
  }
  else if (iVar4 < 10) {
    pcVar6 = &s_int_format_0d;
  }
  else {
    pcVar6 = &s_int_format;
  }
  crt_sprintf(acStack_98,pcVar6,iVar4);
  if (iVar3 < 10) {
    pcVar6 = s_time_fmt_0d;
  }
  else {
    pcVar6 = s_time_fmt_dd;
  }
  crt_sprintf(acStack_118,pcVar6,iVar5,acStack_98,iVar3);
  iVar3 = game_is_full_version();
  if ((((char)iVar3 == '\0') && (config_blob.reserved0._24_4_ != 8)) &&
     (game_status_blob.game_sequence_id = game_sequence_get(),
     (int)game_status_blob.game_sequence_id < 0x249f01)) {
    if (demo_trial_elapsed_ms < 1) {
      if (config_blob.reserved0._24_4_ == 3) goto LAB_00404b1b;
    }
    else if ((config_blob.reserved0._24_4_ == 3) &&
            ((float)(demo_trial_elapsed_ms / 1000) * 0.016666668 <= 5.0)) {
LAB_00404b1b:
      if ((game_state_id == 9) && ((1 < quest_stage_major || (10 < quest_stage_minor)))) {
        fVar2 = fVar2 - 6.0;
        if (demo_trial_elapsed_ms < 1) {
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,fVar7,fVar2,s_You_ve_completed_all_Quest_mode_l_00471ee0);
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,fVar7,fVar2 + 18.0,
                     s_However__you_still_have__s_time_l_00471e94,acStack_118);
          fVar2 = fVar2 + 18.0 + 18.0;
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,fVar7,fVar2,&s_empty_string);
          fVar2 = fVar2 + 14.0;
        }
        else {
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,fVar7,fVar2 + 6.0,
                     s_You_ve_completed_all_Quest_mode_l_00471ee0);
          fVar2 = fVar2 + 6.0 + 18.0;
        }
        (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                  (grim_interface_ptr,fVar7,fVar2,s_If_you_would_like_to_have_unlimi_00471e48);
        (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                  (grim_interface_ptr,fVar7,fVar2 + 18.0,s_please_upgrade_to_the_full_versi_00471e14
                  );
        fVar2 = fVar2 + 18.0 + 22.0;
        (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                  (grim_interface_ptr,fVar7,fVar2,s_The_full_version_features_unrest_00471ddc);
        fVar2 = fVar2 + 18.0;
        (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                  (grim_interface_ptr,fVar7,fVar2,s_game_modes_and_be_able_to_post_y_00471d94);
        fVar2 = fVar2 + 18.0;
        goto LAB_00404ee5;
      }
    }
  }
  if ((iVar5 < 1) && (iVar4 < 1)) {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_Trial_time_is_up__If_you_would_l_00471d44);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2 + 18.0,s_all_features__please_upgrade_to_t_00471cf4);
    fVar2 = fVar2 + 18.0 + 18.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_is_very_easy_and_takes_just_minu_00471ccc);
    fVar2 = fVar2 + 24.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_Buy_the_full_version_to_gain_unr_00471c90);
    fVar2 = fVar2 + 18.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_game_modes_and_be_able_to_post_y_00471d94);
    fVar2 = fVar2 + 18.0;
  }
  else {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2 - 7.0,s_You_have_used_up_your_play_time_i_00471c48,
               acStack_118);
    fVar2 = (fVar2 - 7.0) + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_have__s_time_left_to_play_Quest_m_00471c14,
               acStack_118);
    fVar2 = fVar2 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_If_you_would_like_to_have_unlimi_00471e48);
    fVar2 = fVar2 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_please_upgrade_to_the_full_versi_00471bc4);
    fVar2 = fVar2 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_and_takes_just_minutes__00471ba8);
    fVar2 = fVar2 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_Buy_the_full_version_to_gain_unr_00471c90);
    fVar2 = fVar2 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar7,fVar2,s_game_modes_and_be_able_to_post_y_00471d94);
    fVar2 = fVar2 + 16.0;
  }
LAB_00404ee5:
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,fVar7,fVar2,s_it_now__You_ll_have_a_great_time_00471b84);
  if ((purchase_button_init_flags & 1) == 0) {
    purchase_button_init_flags = purchase_button_init_flags | 1;
    ui_button_maybe_later.enabled = '\x01';
    ui_button_maybe_later.force_wide = '\0';
    ui_button_maybe_later.force_small = '\0';
    ui_button_maybe_later.alpha = 1.0;
    ui_button_maybe_later.click_anim = 0;
    ui_button_maybe_later.label = (char *)0x0;
    ui_button_maybe_later.hovered = '\0';
    ui_button_maybe_later.activated = '\0';
    ui_button_maybe_later.hover_anim = 0;
    crt_atexit(&DAT_00405150);
  }
  ui_button_maybe_later.label = s_Maybe_later_00471b78;
  if ((purchase_button_init_flags & 2) == 0) {
    purchase_button_init_flags = purchase_button_init_flags | 2;
    ui_button_table_a.enabled = '\x01';
    ui_button_table_a.force_wide = '\0';
    ui_button_table_a.force_small = '\0';
    ui_button_table_a.alpha = 1.0;
    ui_button_table_a.click_anim = 0;
    ui_button_table_a.label = (char *)0x0;
    ui_button_table_a.hovered = '\0';
    ui_button_table_a.activated = '\0';
    ui_button_table_a.hover_anim = 0;
    crt_atexit(&DAT_00405140);
  }
  ui_button_table_a.label = s_Purchase_00471b6c;
  if ((purchase_button_init_flags & 4) == 0) {
    purchase_button_init_flags = purchase_button_init_flags | 4;
    ui_button_already_paid.enabled = '\x01';
    ui_button_already_paid.force_wide = '\0';
    ui_button_already_paid.force_small = '\0';
    ui_button_already_paid.alpha = 1.0;
    ui_button_already_paid.click_anim = 0;
    ui_button_already_paid.label = (char *)0x0;
    ui_button_already_paid.hovered = '\0';
    ui_button_already_paid.activated = '\0';
    ui_button_already_paid.hover_anim = 0;
    crt_atexit(&DAT_00405130);
  }
  ui_button_already_paid.label = s_Already_paid_00471b5c;
  iVar3 = ui_button_update((float *)&stack0xfffffec4,&ui_button_table_a);
  if ((char)iVar3 != '\0') {
    shareware_offer_seen_latch = 1;
    game_quit_flag = 1;
    ShellExecuteA((HWND)0x0,&DAT_00471b38,s_http___buy_crimsonland_com_00471b40,(LPCSTR)0x0,
                  (LPCSTR)0x0,1);
  }
  iVar3 = ui_button_update((float *)&stack0xfffffed0,&ui_button_maybe_later);
  if ((char)iVar3 != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 0;
    render_pass_mode = 0;
    sfx_mute_all(music_track_intro_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    sfx_play_exclusive(music_track_crimson_theme_id);
  }
  return;
}



/* demo_purchase_screen_update @ 0040b740 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* demo upsell screen: feature list, purchase link, and exit handling */

void demo_purchase_screen_update(void)

{
  float fVar1;
  char cVar2;
  IGrim2D_vtbl *pIVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  float unaff_EBP;
  float unaff_EDI;
  char *pcVar7;
  float10 fVar8;
  longlong lVar9;
  int iVar10;
  float fVar11;
  int iVar12;
  float fVar13;
  int w;
  float fVar14;
  char *text;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  
  if ((ui_transition_direction != '\0') && (iVar5 = game_is_full_version(), (char)iVar5 != '\0')) {
    ui_transition_direction = '\0';
    game_state_pending = 0;
    demo_mode_active = 1;
    config_load_presets();
    sfx_mute_all(music_track_intro_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_crimson_theme_id);
    ui_elements_update_and_render();
    ui_cursor_render();
    return;
  }
  if ((demo_purchase_screen_active == '\0') &&
     (((iVar5 = input_primary_just_pressed(), (char)iVar5 != '\0' ||
       (iVar5 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(1), (char)iVar5 != '\0')) ||
      (iVar5 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x39), (char)iVar5 != '\0')))) {
    demo_purchase_screen_active = '\x01';
    demo_time_limit_ms = 16000;
  }
  if ((demo_purchase_init_flags & 1) == 0) {
    demo_purchase_init_flags = demo_purchase_init_flags | 1;
    DAT_004802b6 = 1;
    DAT_004802c5 = 0;
    DAT_004802c4 = 0;
    ui_btn_later_scale = 0x3f800000;
    ui_btn_later_alpha = 0;
    ui_btn_maybe_later_label = (char *)0x0;
    DAT_004802b4 = 0;
    DAT_004802b5 = 0;
    ui_btn_later_anim_t = 0;
    crt_atexit(&DAT_0040c1b0);
  }
  ui_btn_maybe_later_label = s_Maybe_later_00471b78;
  if ((demo_purchase_init_flags & 2) == 0) {
    demo_purchase_init_flags = demo_purchase_init_flags | 2;
    DAT_0047f67e = 1;
    DAT_0047f68d = 0;
    DAT_0047f68c = 0;
    game_data_path_c = 0x3f800000;
    game_data_path_b = 0;
    ui_store_button_label = (char *)0x0;
    DAT_0047f67c = 0;
    DAT_0047f67d = 0;
    game_data_path_a = 0;
    crt_atexit(&DAT_0040c1a0);
  }
  ui_store_button_label = s_Purchase_00471b6c;
  fStack_20 = 1.0;
  fStack_2c = (float)quest_spawn_timeline * 0.016;
  if (fStack_2c < 20.0) {
    fStack_20 = fStack_2c * 0.05;
  }
  if (demo_time_limit_ms + -500 < quest_spawn_timeline) {
    fStack_1c = (float)(demo_time_limit_ms - quest_spawn_timeline);
    fStack_20 = (float)(int)fStack_1c * 0.002;
  }
  fVar13 = 1.0;
  fVar14 = fStack_20;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_20);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f4ccccd);
  text = &s_empty_string;
  if (demo_purchase_screen_active == '\0') {
    if (quest_spawn_timeline == 0) {
      demo_upsell_message_index = (demo_upsell_message_index + 1) % 5;
    }
    if (demo_upsell_message_index == 0) {
      text = s_Want_more_Levels__00472780;
    }
    else if (demo_upsell_message_index == 1) {
      text = s_Want_more_Weapons__0047276c;
    }
    else if (demo_upsell_message_index == 2) {
      text = s_Want_more_Perks__00472758;
    }
    else if (demo_upsell_message_index == 3) {
      text = s_Want_unlimited_Play_time__0047273c;
    }
    else if (demo_upsell_message_index == 4) {
      text = s_Want_to_post_your_high_scores__0047271c;
    }
  }
  else {
    ui_pulse_timer_ms = ui_pulse_timer_ms + frame_dt_ms;
    fVar8 = (float10)fsin((float10)(ui_pulse_timer_ms % 1000) * (float10)6.2831855);
    fVar1 = (float)(fVar8 * fVar8);
    (*grim_interface_ptr->vtable->grim_set_color_slot)(0,0.0,0.0,0.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_color_slot)(1,0.0,0.0,0.3,1.0);
    (*grim_interface_ptr->vtable->grim_set_color_slot)(2,0.0,0.4,fVar1 * 0.55,fVar1);
    (*grim_interface_ptr->vtable->grim_set_color_slot)(3,0.0,0.4,0.4,1.0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,0.5,0.5);
    iVar10 = 0;
    pIVar3 = grim_interface_ptr->vtable;
    iVar5 = (*pIVar3->grim_get_texture_handle)(s_backplasma_0047296c);
    (*pIVar3->grim_bind_texture)(iVar5,iVar10);
    (*grim_interface_ptr->vtable->grim_draw_quad)
              (0.0,0.0,(float)config_blob.screen_width,(float)config_blob.screen_height);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    fStack_28 = 0.0;
    if (config_blob.screen_width == 800) {
      fStack_28 = 64.0;
    }
    else if (config_blob.screen_width == 0x400) {
      fStack_28 = 128.0;
    }
    iVar5 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_mockup_00472964);
    w = 0x100;
    iVar10 = config_blob.screen_height / 2 + -0x8c;
    iVar12 = 0x200;
    fStack_1c = (float)(config_blob.screen_width / 2 + -0x80);
    lVar9 = __ftol();
    ui_draw_textured_quad((int)lVar9,iVar10,iVar12,w,iVar5);
    iVar5 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_cl_logo_00471f70);
    iVar12 = 0x40;
    fStack_1c = (float)(config_blob.screen_height / 2 + -200);
    iVar10 = 0x200;
    lVar9 = __ftol();
    ui_draw_textured_quad(config_blob.screen_width / 2 + -0x100,(int)lVar9,iVar10,iVar12,iVar5);
    fVar13 = 1.0;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f19999a);
    fVar14 = (float)(config_blob.screen_height / 2 + -0x68);
    lVar9 = __ftol();
    fVar4 = (float)(int)lVar9;
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar4,fVar14,s_Upgrade_to_the_full_version_of_C_00472930);
    fVar14 = fVar14 + 28.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar4,fVar14,s_Full_version_features__00472918);
    fStack_28 = fVar14 + 15.0;
    fVar11 = 1.0;
    pIVar3 = grim_interface_ptr->vtable;
    fStack_2c = fVar4;
    iVar5 = (*pIVar3->grim_measure_text_width)(s_Full_version_features__00472918);
    (*pIVar3->grim_draw_rect_outline)(&fStack_2c,(float)iVar5,fVar11);
    fVar14 = fVar14 + 22.0;
    fVar11 = (float)((int)lVar9 + 8);
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar11,fVar14,s__Unlimited_Play_Time_in_three_th_004728e4);
    fVar14 = fVar14 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s__The_varied_weapon_arsenal_consi_004728ac);
    fVar14 = fVar14 + 17.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s_weapons_that_allow_you_to_deal_d_00472870);
    fVar14 = fVar14 + 17.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s_fire_and_electricity__00472858);
    fVar14 = fVar14 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s__Over_40_game_altering_Perks__00472838);
    fVar14 = fVar14 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s__40_insane_Levels_that_give_you_00472818);
    fVar14 = fVar14 + 18.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar11,fVar14,s_hours_of_intense_and_fun_gamepla_004727f4);
    fVar14 = fVar14 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar11,fVar14,s__The_ability_to_post_your_high_s_004727c4);
    fVar14 = fVar14 + 22.0 + 22.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar4,fVar14,s_Purchasing_the_game_is_very_easy_00472794);
    fVar14 = fVar14 + 17.0 + 17.0 + 22.0;
    fStack_2c = (float)(config_blob.screen_width / 2 + 0x80);
    fStack_28 = (float)(config_blob.screen_height / 2 + 0x66) + fVar1 * 0.3 + 50.0;
    iVar5 = ui_button_update(&fStack_2c,(ui_button_t *)&shareware_buy_button);
    if ((char)iVar5 != '\0') {
      shareware_offer_seen_latch = '\x01';
      game_quit_flag = 1;
      ShellExecuteA((HWND)0x0,&DAT_00471b38,s_http___buy_crimsonland_com_00471b40,(LPCSTR)0x0,
                    (LPCSTR)0x0,1);
      return;
    }
    fStack_2c = (float)(config_blob.screen_width / 2 + 0x80);
    unaff_EDI = (float)(config_blob.screen_height / 2 + 0x66);
    fStack_28 = (float)(int)unaff_EDI + fVar1 * 0.3 + 90.0;
    iVar5 = ui_button_update(&fStack_2c,(ui_button_t *)&shareware_continue_button);
    if ((char)iVar5 != '\0') {
      if (shareware_offer_seen_latch != '\0') {
        game_quit_flag = 1;
      }
      ui_transition_direction = '\0';
      game_state_pending = 0;
      demo_mode_active = 1;
      if (shareware_offer_seen_latch != '\0') {
        demo_mode_active = 1;
        ui_transition_direction = '\0';
        game_state_pending = 0;
        return;
      }
      config_load_presets();
      sfx_mute_all(music_track_intro_id);
      sfx_mute_all(music_track_crimsonquest_id);
      sfx_play_exclusive(music_track_crimson_theme_id);
      return;
    }
    quest_spawn_timeline = quest_spawn_timeline + frame_dt_ms;
    if (demo_time_limit_ms < quest_spawn_timeline) {
      render_pass_mode = 0;
      demo_mode_start();
    }
    if (demo_purchase_screen_active != '\0') goto LAB_0040c103;
  }
  uVar6 = 0xffffffff;
  pcVar7 = text;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  uStack_24 = 0;
  fStack_20 = 0.0;
  fStack_1c = 0.0;
  fVar1 = (float)(~uVar6 - 1) * 12.8;
  fStack_2c = 60.0;
  fVar4 = ((float)quest_spawn_timeline / (float)demo_time_limit_ms) * fVar1;
  fStack_18 = unaff_EBP * 0.5;
  fStack_28 = (fVar14 + 50.0) - 4.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_2c,fVar1 + 12.0,30.0);
  fStack_1c = fVar4 * 0.8;
  fStack_2c = fVar13 + 72.0;
  fStack_28 = 0.5;
  uStack_24 = 0x3dcccccd;
  fStack_20 = 0.1;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)((float *)&stack0xffffffd0,unaff_EDI,3.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,unaff_EDI);
  (*grim_interface_ptr->vtable->grim_draw_text_mono)(50.0,fVar4,text);
LAB_0040c103:
  ui_elements_update_and_render();
  ui_cursor_render();
  return;
}



/* game_is_full_version @ 0041df40 */

/* returns non-zero when full version/unlimited mode is enabled */

int game_is_full_version(void)

{
  undefined4 in_EAX;
  
  return CONCAT31((int3)((uint)in_EAX >> 8),1);
}



/* trial_time_limit_ms_get @ 0041df50 */

undefined4 trial_time_limit_ms_get(void)

{
  return 2400000;
}


