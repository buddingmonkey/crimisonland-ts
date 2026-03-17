/* gameplay_render_world @ 00405960 */

/* world render pass: updates gameplay fade and draws fx queue, creatures, players, projectiles,
   bonuses */

void gameplay_render_world(void)

{
  int player_index;
  int *piVar1;
  
  ui_transition_alpha = (float)ui_elements_timeline / (float)(ui_timeline_target_end - ui_timeline_target_start);
  if (quest_unlock_index_full < 0x28) {
    if (player_state_table.weapon_id == 0x1d) {
      weapon_assign_player(0,1);
    }
    if (player2_weapon_id == 0x1d) {
      weapon_assign_player(1,1);
    }
  }
  player_index = 0;
  piVar1 = &player_state_table.weapon_id;
  do {
    if ((*piVar1 == 0x19) && (player_last_weapon_id != 0x19)) {
      weapon_assign_player(player_index,1);
    }
    if ((*piVar1 == 0x18) && (player_last_weapon_id != 0x18)) {
      weapon_assign_player(player_index,1);
    }
    piVar1 = piVar1 + 0xd8;
    player_index = player_index + 1;
  } while ((int)piVar1 < 0x491230);
  if (ui_state_init_flag == '\0') {
    if (((game_state_id == 9) || (game_state_id == 6)) ||
       ((((game_state_id == 8 || ((game_state_id == 0xc || (game_state_id == 7)))) &&
         (ui_transition_direction != '\0')) ||
        ((((game_state_pending == 9 || (game_state_pending == 6)) || (game_state_pending == 5)) ||
         ((game_state_pending == 2 || (game_state_pending == 3)))))))) {
LAB_00405a7f:
      ui_transition_alpha = 1.0;
      goto LAB_00405a89;
    }
    if (game_state_id != 5) {
      if (((game_state_id != 2) && (game_state_id != 3)) &&
         ((game_state_pending != 0x15 &&
          (((game_state_pending != 7 && (game_state_pending != 8)) && (game_state_pending != 0xc))))
         )) goto LAB_00405a89;
      goto LAB_00405a7f;
    }
    if (game_state_pending != 0) goto LAB_00405a7f;
  }
  else {
LAB_00405a89:
    if ((game_state_id != 5) || (game_state_pending != 0)) goto LAB_00405ab3;
  }
  ui_transition_alpha = (float)ui_elements_timeline / (float)(ui_timeline_target_end - ui_timeline_target_start);
LAB_00405ab3:
  if (ui_transition_alpha <= 1.0) {
    if (ui_transition_alpha < 0.0) {
      ui_transition_alpha = 0.0;
    }
  }
  else {
    ui_transition_alpha = 1.0;
  }
  fx_queue_render();
  terrain_render();
  render_overlay_player_index = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    do {
      if ((&player_state_table)[render_overlay_player_index].health <= 0.0) {
        player_render_overlays();
      }
      render_overlay_player_index = render_overlay_player_index + 1;
    } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
  }
  creature_render_all();
  render_overlay_player_index = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    do {
      if (0.0 < (&player_state_table)[render_overlay_player_index].health) {
        player_render_overlays();
      }
      render_overlay_player_index = render_overlay_player_index + 1;
    } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
  }
  projectile_render();
  bonus_render();
  if (0.0 < screen_fade_alpha) {
    (*grim_interface_ptr->vtable->grim_draw_fullscreen_color)(0.0,0.0,0.0,screen_fade_alpha);
  }
  return;
}



/* game_update_victory_screen @ 00406350 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_406350() */

int game_update_victory_screen(void)

{
  int extraout_EAX;
  IGrim2D_vtbl *pIVar1;
  char *pcVar2;
  float fVar3;
  float fVar4;
  
  gameplay_render_world();
  ui_elements_update_and_render();
  fVar4 = 1.0;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  if (ui_screen_phase == -1) {
    ui_screen_phase = 0;
  }
  fVar3 = 0.8;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f4ccccd);
  if (config_blob.hardcore == '\0') {
    pcVar2 = s_Congratulations__004722c8;
  }
  else {
    pcVar2 = s_Incredible__004722b8;
  }
  (*grim_interface_ptr->vtable->grim_draw_text_mono_fmt)(grim_interface_ptr,fVar3,fVar4,pcVar2);
  fVar4 = 0.5;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  if (config_blob.hardcore == '\0') {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_You_ve_completed_all_the_levels_b_00472288);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_isn_t_over_yet__With_all_of_the_u_00472258);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_and_weapons_your_Survival_is_jus_00472228);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_You_can_also_replay_the_quests_i_004721fc);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_As_an_additional_reward_for_your_004721d0);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_playing__a_completely_new_and_di_004721a0);
    pcVar2 = s_mode_is_unlocked_for_you__Typ_o__00472174;
    pIVar1 = grim_interface_ptr->vtable;
  }
  else {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_You_ve_done_the_thing_we_all_tho_00472148);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_virtually_impossible__To_reward_y_00472120);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_efforts_a_new_weapon_has_been_un_004720f8);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,s_for_you__Splitter_Gun__004720e0);
    fVar3 = fVar3 + 14.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fVar4,fVar3,&s_empty_string);
    pcVar2 = &s_empty_string;
    pIVar1 = grim_interface_ptr->vtable;
  }
  fVar3 = fVar3 + 14.0;
  (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar4,fVar3,pcVar2);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,fVar4,fVar3 + 14.0 + 8.0,s_Good_luck_with_your_battles__tro_004720b8
            );
  if ((game_completed_screen_flags & 1) == 0) {
    game_completed_screen_flags = game_completed_screen_flags | 1;
    DAT_0047f5e6 = 1;
    DAT_0047f5f5 = 0;
    DAT_0047f5f4 = 0;
    config_save_path_ext = 0x3f800000;
    config_save_path_end = 0;
    config_save_path_base = (char *)0x0;
    DAT_0047f5e4 = 0;
    ui_button_restart_clicked = '\0';
    config_save_path_mid = 0;
    crt_atexit(&DAT_00406ae0);
  }
  config_save_path_base = s_Survival_004720ac;
  if ((game_completed_screen_flags & 2) == 0) {
    game_completed_screen_flags = game_completed_screen_flags | 2;
    DAT_00480286 = 1;
    DAT_00480295 = 0;
    DAT_00480294 = 0;
    ui_btn_rush_scale = 0x3f800000;
    ui_btn_rush_alpha = 0;
    ui_btn_rush_label = (char *)0x0;
    DAT_00480284 = 0;
    ui_button_continue_clicked = '\0';
    ui_btn_rush_anim_t = 0;
    crt_atexit(&DAT_00406ad0);
  }
  ui_btn_rush_label = s_Rush_004720a0;
  if ((game_completed_screen_flags & 4) == 0) {
    game_completed_screen_flags = game_completed_screen_flags | 4;
    DAT_0048032e = 1;
    DAT_0048033d = 0;
    DAT_0048033c = 0;
    _DAT_00480338 = 0x3f800000;
    ui_btn_typo_alpha = 0;
    ui_btn_typo_shooter_label = (char *)0x0;
    DAT_0048032c = 0;
    ui_button_highscores_clicked = '\0';
    ui_btn_typo_anim_t = 0;
    crt_atexit(&DAT_00406ac0);
  }
  ui_btn_typo_shooter_label = s_Typ_o_Shooter_00472090;
  if ((game_completed_screen_flags & 8) == 0) {
    game_completed_screen_flags = game_completed_screen_flags | 8;
    DAT_0048026e = 1;
    DAT_0048027d = 0;
    DAT_0048027c = 0;
    _ui_button_main_menu_alpha = 0x3f800000;
    _ui_button_main_menu_field_c = 0;
    _ui_button_main_menu = (char *)0x0;
    ui_button_main_menu_field_4 = 0;
    ui_button_main_menu_clicked = '\0';
    _ui_button_main_menu_field_8 = 0;
    crt_atexit(&ui_button_main_menu_atexit);
  }
  _ui_button_main_menu = s_main_menu;
  ui_button_update((float *)&stack0xffffffc0,(ui_button_t *)&ui_button_restart);
  ui_button_update((float *)&stack0xffffffc0,(ui_button_t *)&ui_button_continue);
  ui_button_update((float *)&stack0xffffffc0,(ui_button_t *)&ui_button_highscores);
  ui_button_update((float *)&stack0xffffffc0,(ui_button_t *)&DAT_00480268);
  if (ui_button_continue_clicked != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 9;
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    config_blob.reserved0[0x18] = '\x02';
    config_blob.reserved0[0x19] = '\0';
    config_blob.reserved0[0x1a] = '\0';
    config_blob.reserved0[0x1b] = '\0';
  }
  if (ui_button_restart_clicked != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 9;
    config_blob.reserved0[0x18] = '\x01';
    config_blob.reserved0[0x19] = '\0';
    config_blob.reserved0[0x1a] = '\0';
    config_blob.reserved0[0x1b] = '\0';
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
  }
  if (ui_button_highscores_clicked != '\0') {
    render_pass_mode = 0;
    ui_transition_direction = 0;
    game_state_pending = 0x12;
    config_blob.reserved0[0x18] = '\x04';
    config_blob.reserved0[0x19] = '\0';
    config_blob.reserved0[0x1a] = '\0';
    config_blob.reserved0[0x1b] = '\0';
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    screen_fade_in_flag = 1;
  }
  if (ui_button_main_menu_clicked != '\0') {
    sfx_mute_all(music_track_extra_0);
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_crimson_theme_id);
    ui_transition_direction = 0;
    game_state_pending = 0;
    ui_sign_crimson_update_disabled = 0;
  }
  ui_cursor_render();
  return extraout_EAX;
}



/* game_update_generic_menu @ 00406af0 */

/* [binja] int32_t sub_406af0() */

int game_update_generic_menu(void)

{
  int extraout_EAX;
  
  if ((render_pass_mode == '\0') && (game_state_id != 5)) {
    terrain_render();
  }
  else {
    gameplay_render_world();
  }
  (*grim_interface_ptr->vtable->grim_draw_fullscreen_color)(0.0,0.0,0.0,screen_fade_alpha);
  ui_elements_update_and_render();
  perk_prompt_update_and_render();
  ui_cursor_render();
  return extraout_EAX;
}



/* gameplay_update_and_render @ 0040aab0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* main gameplay frame loop for state 9 (timers, updates, renders, UI) */

void gameplay_update_and_render(void)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  longlong lVar4;
  float local_8;
  float fStack_4;
  
  fVar1 = frame_dt;
  if (time_scale_active != '\0') {
    time_scale_factor = 0.3;
    if (bonus_reflex_boost_timer < 1.0) {
      time_scale_factor = (1.0 - bonus_reflex_boost_timer) * 0.7 + 0.3;
    }
    frame_dt = time_scale_factor * frame_dt;
    lVar4 = __ftol();
    frame_dt_ms = (int)lVar4;
  }
  if (demo_mode_active == '\0') {
    iVar2 = game_is_full_version();
    if (((char)iVar2 == '\0') && (config_blob.reserved0._24_4_ != 8)) {
      game_status_blob.game_sequence_id = game_sequence_get();
      if ((int)game_status_blob.game_sequence_id < 0x249f01) {
        if (demo_trial_elapsed_ms < 1) {
          if (config_blob.reserved0._24_4_ != 3) goto LAB_0040abea;
        }
        else if ((config_blob.reserved0._24_4_ != 3) ||
                (local_8 = (float)(demo_trial_elapsed_ms / 1000),
                5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040abae;
        if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
        goto LAB_0040abea;
      }
LAB_0040abae:
      frame_dt_ms = 0;
      frame_dt = 0.0;
      goto LAB_0040abf9;
    }
LAB_0040abea:
    if (game_paused_flag != '\0') goto LAB_0040abae;
LAB_0040ac01:
    if (console_open_flag == '\0') {
      perks_update_effects();
    }
  }
  else {
LAB_0040abf9:
    if (game_paused_flag == '\0') goto LAB_0040ac01;
  }
  effects_update();
  if (((demo_mode_active == '\0') && (iVar2 = game_is_full_version(), (char)iVar2 == '\0')) &&
     (config_blob.reserved0._24_4_ != 8)) {
    game_status_blob.game_sequence_id = game_sequence_get();
    if ((int)game_status_blob.game_sequence_id < 0x249f01) {
      if (demo_trial_elapsed_ms < 1) {
        if (config_blob.reserved0._24_4_ != 3) goto LAB_0040aca0;
      }
      else if ((config_blob.reserved0._24_4_ != 3) ||
              (local_8 = (float)(demo_trial_elapsed_ms / 1000),
              5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040acbb;
      if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
      goto LAB_0040aca0;
    }
  }
  else {
LAB_0040aca0:
    if ((game_paused_flag == '\0') && (game_state_id == 9)) {
      creature_update_all();
      projectile_update();
    }
  }
LAB_0040acbb:
  if (((demo_mode_active == '\0') && (iVar2 = game_is_full_version(), (char)iVar2 == '\0')) &&
     (config_blob.reserved0._24_4_ != 8)) {
    game_status_blob.game_sequence_id = game_sequence_get();
    if ((int)game_status_blob.game_sequence_id < 0x249f01) {
      if (demo_trial_elapsed_ms < 1) {
        if (config_blob.reserved0._24_4_ != 3) goto LAB_0040ad54;
      }
      else if ((config_blob.reserved0._24_4_ != 3) ||
              (local_8 = (float)(demo_trial_elapsed_ms / 1000),
              5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040ad8e;
      if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
      goto LAB_0040ad54;
    }
  }
  else {
LAB_0040ad54:
    if ((game_paused_flag == '\0') &&
       ((game_state_id == 9 &&
        (render_overlay_player_index = 0, 0 < (int)config_blob.reserved0._20_4_)))) {
      do {
        player_update();
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
    }
  }
LAB_0040ad8e:
  render_overlay_player_index = 0;
  if (config_blob.reserved0._24_4_ == 1) {
    survival_update();
  }
  if (config_blob.reserved0._24_4_ == 2) {
    rush_mode_update();
  }
  if (config_blob.reserved0._24_4_ == 3) {
    quest_mode_update();
  }
  highscore_active_record.score_xp = player_state_table.experience;
  if ((console_open_flag == '\0') && (game_paused_flag == '\0')) {
    if (0.0 < bonus_weapon_power_up_timer) {
      bonus_weapon_power_up_timer = bonus_weapon_power_up_timer - frame_dt;
    }
    if (0.0 < bonus_energizer_timer) {
      bonus_energizer_timer = bonus_energizer_timer - frame_dt;
    }
    time_scale_active = 0.0 < bonus_reflex_boost_timer;
    if ((bool)time_scale_active) {
      bonus_reflex_boost_timer = bonus_reflex_boost_timer - frame_dt;
    }
    highscore_active_record.survival_elapsed_ms =
         highscore_active_record.survival_elapsed_ms + frame_dt_ms;
    (&weapon_usage_time)[player_state_table.weapon_id] =
         (&weapon_usage_time)[player_state_table.weapon_id] + frame_dt_ms;
  }
  camera_update();
  gameplay_render_world();
  if (config_blob.reserved0._24_4_ == 8) {
    tutorial_timeline_update();
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  if (demo_mode_active == '\0') {
    if (((player_state_table.health <= 0.0) && (player_state_table.death_timer < 0.0)) &&
       ((config_blob.reserved0._20_4_ == 1 ||
        ((player2_health <= 0.0 && (_player2_death_timer < 0.0)))))) {
      render_pass_mode = 0;
      ui_transition_direction = 0;
      game_state_pending = (-(uint)(config_blob.reserved0._24_4_ != 3) & 0xfffffffb) + 0xc;
      (*grim_interface_ptr->vtable->grim_flush_input)();
      console_input_poll();
      sfx_mute_all(music_track_extra_0);
      sfx_mute_all(music_track_crimson_theme_id);
      sfx_mute_all(music_track_shortie_monk_id);
      sfx_play_exclusive(music_track_shortie_monk_id);
    }
  }
  else {
    pfVar3 = &player_state_table.health;
    do {
      *pfVar3 = 100.0;
      pfVar3 = pfVar3 + 0xd8;
    } while ((int)pfVar3 < 0x490f94);
  }
  if (config_blob.reserved0._24_4_ != 2) {
    crt_ci_pow();
    lVar4 = __ftol();
    if (1000 - (int)lVar4 < player_state_table.experience) {
      perk_pending_count = perk_pending_count + 1;
      config_blob.perk_prompt_counter = config_blob.perk_prompt_counter + 1;
      if (0x32 < config_blob.perk_prompt_counter) {
        config_blob.perk_prompt_counter = 0;
        config_blob.full_version = '\0';
      }
      sfx_play(sfx_ui_levelup);
      player_state_table.level = player_state_table.level + 1;
    }
  }
  if ((console_open_flag == '\0') && (game_paused_flag == '\0')) {
    if (perk_prompt_hover_active == '\0') {
      iVar2 = -frame_dt_ms;
    }
    else {
      iVar2 = frame_dt_ms * 3;
    }
    perk_prompt_pulse = perk_prompt_pulse + iVar2 * 2;
    if (perk_prompt_pulse < 0) {
      perk_prompt_pulse = 0;
    }
    else if (1000 < perk_prompt_pulse) {
      perk_prompt_pulse = 1000;
    }
  }
  if (((((demo_mode_active == '\0') && (game_paused_flag == '\0')) && (mouse_button_down == '\0'))
      && ((config_blob.reserved0._24_4_ != 2 && (0 < perk_pending_count)))) &&
     ((0.0 < player_state_table.health ||
      ((config_blob.reserved0._20_4_ == 2 && (0.0 < player2_health)))))) {
    local_8 = ui_mouse_x - _perk_prompt_origin_x;
    fStack_4 = ui_mouse_y - _perk_prompt_origin_y;
    if (game_state_pending != 6) {
      iVar2 = (*grim_interface_ptr->vtable->grim_is_key_active)(config_blob.key_pick_perk);
      if ((((char)iVar2 == '\0') &&
          (iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x39), (char)iVar2 == '\0'))
         && (iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x4e), (char)iVar2 == '\0')
         ) {
        if (((local_8 <= perk_prompt_bounds_min_x) || (fStack_4 <= perk_prompt_bounds_min_y)) ||
           ((_perk_prompt_bounds_max_x <= local_8 || (_perk_prompt_bounds_max_y <= fStack_4)))) {
          perk_prompt_hover_active = '\0';
        }
        else {
          perk_prompt_hover_active = '\x01';
          iVar2 = input_primary_just_pressed();
          if ((char)iVar2 != '\0') goto joined_r0x0040b1bc;
        }
      }
      else {
        perk_prompt_pulse = 1000;
joined_r0x0040b1bc:
        if (perk_choices_dirty != '\0') {
          perks_generate_choices();
          perk_choices_dirty = '\0';
        }
        game_state_set(6);
      }
    }
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_is_mouse_button_down)(0);
  mouse_button_down = (char)iVar2 != '\0';
  bonus_update();
  frame_dt = fVar1;
  lVar4 = __ftol();
  frame_dt_ms = (int)lVar4;
  if (((demo_mode_active == '\0') && (perk_prompt_update_and_render(), demo_mode_active == '\0')) &&
     ((iVar2 = game_is_full_version(), (char)iVar2 == '\0' && (config_blob.reserved0._24_4_ != 8))))
  {
    game_status_blob.game_sequence_id = game_sequence_get();
    if ((int)game_status_blob.game_sequence_id < 0x249f01) {
      if (demo_trial_elapsed_ms < 1) {
        if (config_blob.reserved0._24_4_ != 3) goto LAB_0040b2ad;
      }
      else if ((config_blob.reserved0._24_4_ != 3) ||
              (local_8 = (float)(demo_trial_elapsed_ms / 1000),
              5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040b2b2;
      if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
      goto LAB_0040b2ad;
    }
  }
  else {
LAB_0040b2ad:
    ui_render_aim_indicators();
  }
LAB_0040b2b2:
  hud_update_and_render();
  ui_elements_update_and_render();
  iVar2 = game_is_full_version();
  if ((char)iVar2 == '\0') {
    if (((demo_mode_active == '\0') && (iVar2 = game_is_full_version(), (char)iVar2 == '\0')) &&
       (config_blob.reserved0._24_4_ != 8)) {
      game_status_blob.game_sequence_id = game_sequence_get();
      if ((int)game_status_blob.game_sequence_id < 0x249f01) {
        if (demo_trial_elapsed_ms < 1) {
          if (config_blob.reserved0._24_4_ != 3) goto LAB_0040b3bd;
        }
        else if ((config_blob.reserved0._24_4_ != 3) ||
                (local_8 = (float)(demo_trial_elapsed_ms / 1000),
                5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040b35f;
        if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
        goto LAB_0040b3bd;
      }
LAB_0040b35f:
      trial_overlay_fade_timer = trial_overlay_fade_timer + frame_dt_ms;
      local_8 = (float)config_blob.screen_width * 0.5 - 256.0;
      fStack_4 = (float)config_blob.screen_height * 0.5 - 128.0;
      demo_trial_overlay_render(&local_8,1.0);
      game_loading_flag = 1;
    }
    else {
LAB_0040b3bd:
      trial_overlay_fade_timer = trial_overlay_fade_timer - frame_dt_ms;
      game_loading_flag = 0;
    }
    if (trial_overlay_fade_timer < 0) {
      trial_overlay_fade_timer = 0;
    }
    else if (1000 < trial_overlay_fade_timer) {
      trial_overlay_fade_timer = 1000;
    }
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x3b);
  if ((char)iVar2 != '\0') {
    game_paused_flag = game_paused_flag == '\0';
  }
  iVar2 = game_is_full_version();
  if (((char)iVar2 == '\0') && (config_blob.reserved0._24_4_ != 8)) {
    game_status_blob.game_sequence_id = game_sequence_get();
    if ((int)game_status_blob.game_sequence_id < 0x249f01) {
      if (demo_trial_elapsed_ms < 1) {
        if (config_blob.reserved0._24_4_ != 3) goto LAB_0040b4bc;
      }
      else if ((config_blob.reserved0._24_4_ != 3) ||
              (local_8 = (float)(demo_trial_elapsed_ms / 1000),
              5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040b494;
      if ((game_state_id != 9) || ((quest_stage_major < 2 && (quest_stage_minor < 0xb))))
      goto LAB_0040b4bc;
    }
LAB_0040b494:
    game_paused_flag = '\0';
LAB_0040b49a:
    pause_overlay_fade_timer = pause_overlay_fade_timer + frame_dt_ms * -4;
  }
  else {
LAB_0040b4bc:
    if (game_paused_flag == '\0') goto LAB_0040b49a;
    pause_overlay_fade_timer = pause_overlay_fade_timer + frame_dt_ms * 2;
  }
  if (pause_overlay_fade_timer < 0) {
    pause_overlay_fade_timer = 0;
  }
  else {
    if (pause_overlay_fade_timer < 0x3e9) {
      if (pause_overlay_fade_timer < 1) goto LAB_0040b52d;
    }
    else {
      pause_overlay_fade_timer = 1000;
    }
    local_8 = (float)config_blob.screen_width * 0.5 - 256.0;
    fStack_4 = (float)config_blob.screen_height * 0.5 - 128.0;
    ui_render_keybind_help(&local_8,(float)pause_overlay_fade_timer * 0.001);
  }
LAB_0040b52d:
  iVar2 = game_is_full_version();
  if ((char)iVar2 != '\0') {
    return;
  }
  if (config_blob.reserved0._24_4_ == 8) {
    return;
  }
  game_status_blob.game_sequence_id = game_sequence_get();
  if ((int)game_status_blob.game_sequence_id < 0x249f01) {
    if (demo_trial_elapsed_ms < 1) {
      if (config_blob.reserved0._24_4_ != 3) {
        return;
      }
    }
    else if ((config_blob.reserved0._24_4_ != 3) ||
            (local_8 = (float)(demo_trial_elapsed_ms / 1000),
            5.0 < (float)(int)local_8 * 0.016666668)) goto LAB_0040b5b4;
    if (game_state_id != 9) {
      return;
    }
    if ((quest_stage_major < 2) && (quest_stage_minor < 0xb)) {
      return;
    }
  }
LAB_0040b5b4:
  if (demo_mode_active == '\0') {
    ui_cursor_render();
  }
  return;
}



/* game_over_screen_update @ 0040ffc0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* game over flow: high score entry, results text, and navigation buttons */

void game_over_screen_update(void)

{
  char cVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  char *pcVar8;
  highscore_record_t *phVar9;
  undefined4 *puVar10;
  char *pcVar11;
  highscore_record_t *phVar12;
  longlong lVar13;
  int y;
  int w;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (((byte)game_over_screen_flags & 1) == 0) {
    game_over_screen_flags._0_1_ = (byte)game_over_screen_flags | 1;
    DAT_004825ae = 1;
    DAT_004825bd = 0;
    DAT_004825bc = 0;
    _DAT_004825b8 = 0x3f800000;
    _DAT_004825b4 = 0;
    highscore_confirm_button_ptr = (undefined *)0x0;
    DAT_004825ac = 0;
    highscore_submit_flag = '\0';
    _DAT_004825b0 = 0;
    crt_atexit(&DAT_004107d0);
  }
  if (((byte)game_over_screen_flags & 2) == 0) {
    game_over_screen_flags._0_1_ = (byte)game_over_screen_flags | 2;
    _DAT_004825a0 = 0x3f800000;
    highscore_name_buffer_ptr = &highscore_name_input_buf;
    highscore_name_length = 0;
    highscore_max_name_length = 0x18;
    highscore_input_width = 0x60;
    crt_atexit(&DAT_004107c0);
  }
  bonus_reflex_boost_timer = 0;
  if ((ui_transition_direction != '\0') && (highscore_return_latch != '\0')) {
    highscore_return_latch = '\0';
    ui_screen_phase = 1;
  }
  if ((((game_state_id == 7) && (game_state_pending == 0x19)) && (ui_transition_direction != '\0'))
     && (iVar3 = sfx_is_unmuted(music_track_shortie_monk_id), (char)iVar3 == '\0')) {
    sfx_play_exclusive(music_track_shortie_monk_id);
  }
  gameplay_render_world();
  ui_elements_update_and_render();
  perk_prompt_update_and_render();
  local_4 = _DAT_0048cc64 + DAT_0048cc88;
  local_10 = menu_survival_y_base + menu_survival_y_scroll + 180.0;
  fVar2 = local_4 + 40.0;
  w = 0x40;
  local_18 = (_DAT_0048cc50 + local_10 + 44.0) - 10.0;
  y = 0x100;
  iVar3 = crt_lowio_handles;
  local_14 = fVar2;
  local_c = fVar2;
  local_8 = local_18;
  lVar13 = __ftol();
  iVar6 = (int)lVar13;
  lVar13 = __ftol();
  ui_draw_textured_quad((int)lVar13,iVar6,y,w,iVar3);
  if (ui_screen_phase == -1) {
    highscore_load_table();
    highscore_current_rank = highscore_rank_index();
    highscore_active_record.game_mode_id = config_blob.reserved0[0x18];
    (*grim_interface_ptr->vtable->grim_flush_input)();
    console_input_poll();
    (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
    if (highscore_current_rank < 100) {
      uVar4 = 0xffffffff;
      ui_screen_phase = 0;
      phVar12 = &highscore_active_record;
      do {
        phVar9 = phVar12;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        phVar9 = (highscore_record_t *)(phVar12->player_name + 1);
        pcVar8 = phVar12->player_name;
        phVar12 = phVar9;
      } while (*pcVar8 != '\0');
      uVar4 = ~uVar4;
      highscore_max_name_length = 0x14;
      highscore_name_buffer_ptr = &highscore_name_input_buf;
      puVar7 = (undefined4 *)((int)phVar9 - uVar4);
      puVar10 = &highscore_name_input_buf;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar10 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar10 = puVar10 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar10 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      uVar4 = 0xffffffff;
      phVar12 = &highscore_active_record;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar8 = phVar12->player_name;
        phVar12 = (highscore_record_t *)(phVar12->player_name + 1);
      } while (*pcVar8 != '\0');
      highscore_name_length = ~uVar4 - 1;
LAB_00410232:
      local_18 = local_18 + 8.0;
      ui_text_alpha = 0x3f800000;
      local_14 = local_14 + 84.0;
      (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_18 + 42.0,local_14,s_State_your_name__trooper__00473190);
      local_14 = local_14 + 40.0;
      ui_text_alpha = 0x3f333333;
      highscore_confirm_button_ptr = &DAT_0047318c;
      local_10 = local_18 + 170.0;
      local_c = local_14 - 8.0;
      ui_button_update(&local_10,(ui_button_t *)&DAT_004825a8);
      highscore_input_width = 0xa6;
      iVar3 = ui_text_input_update(&local_18,(int *)&DAT_00482590);
      if (((char)iVar3 != '\0') || (highscore_submit_flag != '\0')) {
        uVar4 = 0xffffffff;
        iVar3 = 0;
        pcVar8 = (char *)&highscore_name_input_buf;
        do {
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar1 != '\0');
        iVar6 = ~uVar4 - 1;
        if (0 < iVar6) {
          if (0 < iVar6) {
            do {
              if (*(char *)((int)&highscore_name_input_buf + iVar3) != ' ') break;
              iVar3 = iVar3 + 1;
            } while (iVar3 < iVar6);
          }
          if (*(char *)((int)&highscore_name_input_buf + iVar3) != '\0') {
            ui_screen_phase = 1;
            sfx_play(sfx_ui_typeenter);
            phVar12 = &highscore_active_record;
            for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
              phVar12->player_name[0] = '\0';
              phVar12->player_name[1] = '\0';
              phVar12->player_name[2] = '\0';
              phVar12->player_name[3] = '\0';
              phVar12 = (highscore_record_t *)(phVar12->player_name + 4);
            }
            uVar4 = 0xffffffff;
            pcVar8 = (char *)&highscore_name_input_buf;
            do {
              pcVar11 = pcVar8;
              if (uVar4 == 0) break;
              uVar4 = uVar4 - 1;
              pcVar11 = pcVar8 + 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar11;
            } while (cVar1 != '\0');
            uVar4 = ~uVar4;
            highscore_name_buffer_ptr = &highscore_name_input_buf;
            pcVar8 = pcVar11 + -uVar4;
            phVar12 = &highscore_active_record;
            for (uVar5 = uVar4 >> 2; iVar3 = highscore_name_length, uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined4 *)phVar12->player_name = *(undefined4 *)pcVar8;
              pcVar8 = pcVar8 + 4;
              phVar12 = (highscore_record_t *)(phVar12->player_name + 4);
            }
            player_name_length = highscore_name_length;
            for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
              phVar12->player_name[0] = *pcVar8;
              pcVar8 = pcVar8 + 1;
              phVar12 = (highscore_record_t *)(phVar12->player_name + 1);
            }
            highscore_active_record.player_name[iVar3] = '\0';
            highscore_save_active();
            highscore_load_table();
            goto LAB_004103c2;
          }
        }
        highscore_submit_flag = '\0';
        sfx_play(sfx_shock_hit_01);
      }
LAB_004103c2:
      local_14 = local_14 + 60.0;
      (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
      if (highscore_current_rank < 100) {
        local_10 = local_18 + 16.0;
        local_c = local_14 + 16.0;
        ui_text_input_render(&local_10,6.652423e-39,1.0);
        ui_cursor_render();
        return;
      }
      goto LAB_00410782;
    }
    ui_screen_phase = 1;
  }
  else {
    if (ui_screen_phase == 0) goto LAB_00410232;
    if (ui_screen_phase != 1) goto LAB_00410782;
  }
  local_18 = local_8 + 30.0;
  highscore_name_buffer_ptr = &highscore_name_input_buf;
  if (highscore_current_rank < 100) {
    local_14 = fVar2 + 64.0;
  }
  else {
    local_14 = fVar2 + 62.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_18 + 8.0,local_14,s_Score_too_low_for_top_d__00473170,100);
    local_14 = local_14 + 6.0;
  }
  local_10 = local_18;
  local_c = local_14 + 16.0;
  ui_text_input_render(&local_10,6.652423e-39,1.0);
  local_14 = local_14 + 146.0;
  if (((byte)game_over_screen_flags & 4) == 0) {
    game_over_screen_flags._0_1_ = (byte)game_over_screen_flags | 4;
    DAT_0048250e = 1;
    DAT_0048251d = 0;
    DAT_0048251c = 0;
    _DAT_00482518 = 0x3f800000;
    _DAT_00482514 = 0;
    _DAT_00482508 = (char *)0x0;
    DAT_0048250c = 0;
    highscore_btn_submit_a = '\0';
    _DAT_00482510 = 0;
    crt_atexit(&DAT_004107b0);
  }
  _DAT_00482508 = s_Play_Again_00473164;
  if (((byte)game_over_screen_flags & 8) == 0) {
    game_over_screen_flags._0_1_ = (byte)game_over_screen_flags | 8;
    DAT_00482556 = 1;
    DAT_00482565 = 0;
    DAT_00482564 = 0;
    _DAT_00482560 = 0x3f800000;
    _DAT_0048255c = 0;
    highscore_btn_scores_label_a = (char *)0x0;
    DAT_00482554 = 0;
    highscore_submit_flag = '\0';
    _DAT_00482558 = 0;
    crt_atexit(&DAT_004107a0);
  }
  highscore_btn_scores_label_a = s_High_scores_00473158;
  if (((byte)game_over_screen_flags & 0x10) == 0) {
    game_over_screen_flags._0_1_ = (byte)game_over_screen_flags | 0x10;
    DAT_0048253e = 1;
    DAT_0048254d = 0;
    DAT_0048254c = 0;
    _DAT_00482548 = 0x3f800000;
    _DAT_00482544 = 0;
    highscore_btn_menu_label_a = (char *)0x0;
    DAT_0048253c = 0;
    return_to_menu_flag = '\0';
    _DAT_00482540 = 0;
    crt_atexit(&DAT_00410790);
  }
  highscore_btn_menu_label_a = s_main_menu;
  local_18 = (local_18 - 4.0) + 26.0;
  ui_button_update(&local_18,(ui_button_t *)&DAT_00482508);
  local_14 = local_14 + 32.0;
  ui_button_update(&local_18,(ui_button_t *)&DAT_00482550);
  local_14 = local_14 + 32.0;
  ui_button_update(&local_18,(ui_button_t *)&DAT_00482538);
  local_14 = local_14 + 32.0;
  if (highscore_btn_submit_a != '\0') {
    ui_transition_direction = '\0';
    game_state_pending = 9;
    if (config_blob.reserved0._24_4_ == 4) {
      game_state_pending = 0x12;
    }
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
  }
  if (highscore_submit_flag != '\0') {
    highscore_key_config._0_1_ = config_blob.reserved0[0x18];
    highscore_key_config._1_1_ = config_blob.reserved0[0x19];
    highscore_key_config._2_1_ = config_blob.reserved0[0x1a];
    highscore_key_config._3_1_ = config_blob.reserved0[0x1b];
    highscore_return_latch = '\x01';
    highscore_quest_major = quest_stage_major;
    highscore_quest_minor = quest_stage_minor;
    highscore_hardcore_flag = config_blob.hardcore;
    ui_transition_direction = '\0';
    game_state_pending = 0xe;
  }
  if (return_to_menu_flag != '\0') {
    sfx_mute_all(music_track_extra_0);
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_crimson_theme_id);
    ui_transition_direction = '\0';
    game_state_pending = 0;
    ui_sign_crimson_update_disabled = 0;
  }
LAB_00410782:
  ui_cursor_render();
  return;
}



/* game_state_reset_all @ 004120b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4120b0() */

int game_state_reset_all(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  highscore_record_t *phVar7;
  
  phVar7 = &highscore_active_record;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    phVar7->player_name[0] = '\0';
    phVar7->player_name[1] = '\0';
    phVar7->player_name[2] = '\0';
    phVar7->player_name[3] = '\0';
    phVar7 = (highscore_record_t *)(phVar7->player_name + 4);
  }
  uVar3 = 0xffffffff;
  pcVar5 = &default_player_name;
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  phVar7 = &highscore_active_record;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)phVar7->player_name = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    phVar7 = (highscore_record_t *)(phVar7->player_name + 4);
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    phVar7->player_name[0] = *pcVar5;
    pcVar5 = pcVar5 + 1;
    phVar7 = (highscore_record_t *)(phVar7->player_name + 1);
  }
  highscore_active_record.flags = '\0';
  highscore_active_record.sentinel_pipe = '|';
  highscore_active_record.sentinel_ff = 0xff;
  uVar3 = crt_rand();
  uVar3 = uVar3 & 0xfee050f;
  highscore_active_record.reserved0[0] = (char)uVar3;
  highscore_active_record.reserved0[1] = (char)(uVar3 >> 8);
  highscore_active_record.reserved0[2] = (char)(uVar3 >> 0x10);
  highscore_active_record.reserved0[3] = (char)(uVar3 >> 0x18);
  bonus_energizer_timer = 0;
  survival_spawn_stage = 0;
  survival_mode_wave = 0;
  quest_fail_retry_count = 0;
  demo_mode_active = 0;
  full_version_ui_adjusted = 0;
  quest_unlock_index = 0;
  creature_active_count = 0;
  gameplay_elapsed_ms = 0;
  quest_transition_timer_ms = -1;
  quest_stage_major = 1;
  quest_stage_minor = 1;
  return 1;
}



/* game_mode_label @ 00412960 */

/* returns a display label for the current game mode */

char * game_mode_label(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (config_blob.reserved0._24_4_ == 2) {
    pcVar4 = &DAT_00473614;
  }
  else {
    if (config_blob.reserved0._24_4_ == 1) {
      uVar2 = 0xffffffff;
      pcVar4 = s_Survival_004720ac;
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
      pcVar5 = (char *)&game_mode_name_buffer;
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
      return (char *)&game_mode_name_buffer;
    }
    if (config_blob.reserved0._24_4_ == 3) {
      pcVar4 = s_Quests_0047360c;
    }
    else {
      if (config_blob.reserved0._24_4_ == 4) {
        uVar2 = 0xffffffff;
        pcVar4 = s_Typ_o_Shooter_00472090;
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
        pcVar5 = (char *)&game_mode_name_buffer;
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
        return (char *)&game_mode_name_buffer;
      }
      pcVar4 = s_unknown_label;
    }
  }
  uVar2 = 0xffffffff;
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
  pcVar5 = (char *)&game_mode_name_buffer;
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
  return (char *)&game_mode_name_buffer;
}



/* game_sequence_load @ 00412a10 */

/* reads the sequence value from registry */

void game_sequence_load(void)

{
  LONG LVar1;
  HKEY local_8;
  uint local_4;
  
  LVar1 = RegCreateKeyExA((HKEY)0x80000002,(LPCSTR)&reg_key_path,0,(LPSTR)0x0,0,0xf003f,
                          (LPSECURITY_ATTRIBUTES)0x0,(PHKEY)&local_8,(LPDWORD)0x0);
  if (LVar1 == 0) {
    reg_read_dword_default(local_8,s_sequence_0047361c,&local_4,0);
    if (game_status_blob.game_sequence_id < local_4) {
      game_status_blob.game_sequence_id = local_4;
    }
    RegCloseKey((HKEY)local_8);
  }
  return;
}



/* game_save_status @ 00412a80 */

/* writes registry state and saves status file */

void game_save_status(void)

{
  char cVar1;
  LONG LVar2;
  char *pcVar3;
  FILE *fp;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  HKEY local_8;
  int local_4;
  
  LVar2 = RegCreateKeyExA((HKEY)0x80000002,(LPCSTR)&reg_key_path,0,(LPSTR)0x0,0,0xf003f,
                          (LPSECURITY_ATTRIBUTES)0x0,(PHKEY)&local_8,(LPDWORD)0x0);
  uVar7 = game_status_blob.game_sequence_id;
  if (LVar2 == 0) {
    reg_write_dword(local_8,s_sequence_0047361c,game_status_blob.game_sequence_id);
    reg_write_dword(local_8,s_dataPathId_0047367c,uVar7 * 0xd + 3 >> 1);
    reg_write_dword(local_8,s_transferFailed_0047366c,0);
    RegCloseKey((HKEY)local_8);
  }
  pcVar8 = &file_mode_write_binary;
  pcVar3 = game_build_path(game_status_filename);
  fp = (FILE *)crt_fopen(pcVar3,pcVar8);
  if (fp != (FILE *)0x0) {
    game_status_blob.quest_unlock_index = (ushort)quest_unlock_index;
    local_4 = 0;
    iVar5 = 0;
    game_status_blob.quest_unlock_index_full = (ushort)quest_unlock_index_full;
    uVar7 = 0;
    do {
      cVar1 = *(char *)((int)game_status_blob.weapon_usage_counts + iVar5 + -4);
      iVar6 = (cVar1 * 7 + iVar5) * (int)cVar1 + uVar7;
      cVar4 = (char)iVar5;
      uVar7 = uVar7 + 0x6f;
      local_4 = local_4 + 0xd + iVar6;
      *(char *)((int)game_status_blob.weapon_usage_counts + iVar5 + -4) =
           ((cVar4 * '\a' + '\x0f') * cVar4 + '\x03') * cVar4 + cVar1 + 'o';
      iVar5 = iVar5 + 1;
    } while (uVar7 < 0x10b18);
    crt_fwrite((char *)&game_status_blob,0x268,1,(int *)fp);
    crt_fwrite((char *)&local_4,4,1,(int *)fp);
    crt_fclose(fp);
    if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
      console_printf(&console_log_queue,s_GAME_SaveStatus_OK__00473644);
    }
    game_load_status();
    game_sequence_load();
    game_sequence_load();
    return;
  }
  console_printf(&console_log_queue,s_GAME_SaveStatus_FAILED__00473628);
  game_sequence_load();
  return;
}



/* game_load_status @ 00412c10 */

/* loads status file; regenerates on failure */

void game_load_status(void)

{
  char cVar1;
  char *pcVar2;
  FILE *fp;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  int local_4;
  
  pcVar7 = &file_mode_read_binary;
  pcVar2 = game_build_path(game_status_filename);
  fp = (FILE *)crt_fopen(pcVar2,pcVar7);
  uVar6 = 0;
  if (fp == (FILE *)0x0) {
    console_printf(&console_log_queue,s_game_load_status_failed);
    console_printf(&console_log_queue,s_generating_new_file);
    game_status_blob.quest_unlock_index = 0;
    game_status_blob.quest_unlock_index_full = 0;
    game_sequence_load();
    game_save_status();
    game_sequence_load();
  }
  else {
    crt_fseek((int *)fp,0,2);
    iVar3 = crt_ftell((char *)fp);
    if (iVar3 != 0x26c) {
      crt_fclose(fp);
      console_printf(&console_log_queue,s_game_load_status_invalid_file);
      game_sequence_load();
      return;
    }
    crt_fseek((int *)fp,0,0);
    crt_fread((char *)&game_status_blob,0x268,1,(int *)fp);
    local_4 = 0;
    crt_fread((char *)&local_4,4,1,(int *)fp);
    iVar3 = 0;
    iVar4 = 0;
    do {
      cVar1 = (char)iVar4;
      cVar1 = *(char *)((int)game_status_blob.weapon_usage_counts + iVar4 + -4) +
              (-0x6f - ((cVar1 * '\a' + '\x0f') * cVar1 + '\x03') * cVar1);
      *(char *)((int)game_status_blob.weapon_usage_counts + iVar4 + -4) = cVar1;
      iVar5 = (cVar1 * 7 + iVar4) * (int)cVar1 + uVar6;
      uVar6 = uVar6 + 0x6f;
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0xd + iVar5;
    } while (uVar6 < 0x10b18);
    if (iVar3 != local_4) {
      crt_fclose(fp);
      console_printf(&console_log_queue,s_game_load_status_checksum_failed);
      game_sequence_load();
      return;
    }
    quest_unlock_index_full = (uint)game_status_blob._0_4_ >> 0x10;
    quest_unlock_index = game_status_blob._0_4_ & 0xffff;
    crt_fclose(fp);
    if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
      console_printf(&console_log_queue,s_game_load_status_ok);
      return;
    }
  }
  return;
}



/* gameplay_reset_state @ 00412dc0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* resets gameplay/session globals, pools, and availability tables */

void gameplay_reset_state(void)

{
  undefined4 uVar1;
  bonus_hud_slot_slide_x_block_t *pbVar2;
  uint uVar3;
  float *pfVar4;
  bonus_entry_t *pbVar5;
  projectile_t *ppVar6;
  sprite_effect_t *psVar7;
  secondary_projectile_t *psVar8;
  int iVar9;
  creature_spawn_slot_t *pcVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  undefined4 *puVar14;
  
  pbVar2 = &bonus_hud_slot_table[0].slide;
  player_render_disabled_flag = 0;
  do {
    pbVar2->field_0x1c = 5.0;
    *(undefined1 *)((int)(pbVar2 + -1) + 0x18) = 0;
    pbVar2->slide_x = 0.0;
    pbVar2->icon_id = 1;
    pbVar2->label = s_empty_slot;
    pbVar2->field_0x08 = 1.0;
    pbVar2 = (bonus_hud_slot_slide_x_block_t *)((int)(pbVar2 + 1) + 4);
  } while ((int)pbVar2 < 0x48f78c);
  quest_spawn_timeline = 0;
  shock_chain_links_left = 0;
  player_last_weapon_id = 1;
  creature_spawned_count = 0;
  survival_recent_death_count = 0;
  survival_reward_damage_seen = 0;
  survival_reward_fire_seen = 0;
  tutorial_init_flag = 1;
  survival_reward_handout_enabled = 1;
  tutorial_stage_index = 0xffffffff;
  tutorial_stage_timer = 0;
  tutorial_stage_transition_timer = 0xfffffc18;
  quest_transition_timer_ms = -1;
  bonus_double_xp_timer = 0;
  survival_spawn_stage = 0;
  camera_shake_pulses = 0;
  bonus_reset_availability();
  creature_type_table_init_count = 6;
  creature_type_table.texture_handle =
       (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_creature_zombie);
  creature_type_table.sfx_bank_b[0] = sfx_zombie_attack_01;
  creature_type_table.sfx_bank_b[1] = sfx_zombie_attack_02;
  creature_type_table.sfx_bank_a[0] = sfx_zombie_die_01;
  creature_type_table.sfx_bank_a[1] = sfx_zombie_die_02;
  creature_type_table.field_0x20 = 1.0;
  creature_type_table.anim_rate = 1.2;
  creature_type_table.sfx_bank_a[2] = sfx_zombie_die_03;
  creature_type_table.sfx_bank_a[3] = sfx_zombie_die_04;
  creature_type_table.base_frame = 0x20;
  creature_type_table.corpse_frame = 0;
  creature_type_lizard_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_creature_lizard);
  creature_type_lizard_sfx_attack_02 = sfx_lizard_attack_02;
  creature_type_lizard_sfx_attack_01 = sfx_lizard_attack_01;
  creature_type_lizard_sfx_die_01 = sfx_lizard_die_01;
  creature_type_lizard_sfx_die_03 = sfx_lizard_die_03;
  creature_type_lizard_field_0x20 = 0x3f800000;
  creature_type_lizard_anim_rate = 0x3fcccccd;
  creature_type_lizard_sfx_die_02 = sfx_lizard_die_02;
  creature_type_lizard_sfx_die_04 = sfx_lizard_die_04;
  creature_type_lizard_anim_flags = 1;
  creature_type_lizard_base_frame = 0x10;
  creature_type_lizard_corpse_frame = 3;
  creature_type_spider_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_creature_spider);
  creature_type_spider_sfx_attack_01 = sfx_spider_attack_01;
  creature_type_spider_sfx_attack_02 = sfx_spider_attack_02;
  creature_type_spider_field_0x20 = 0x3f800000;
  creature_type_spider_anim_rate = 0x3fc00000;
  creature_type_spider_sfx_die_01 = sfx_spider_die_01;
  creature_type_spider_sfx_die_02 = sfx_spider_die_02;
  creature_type_spider_sfx_die_03 = sfx_spider_die_03;
  creature_type_spider_sfx_die_04 = sfx_spider_die_04;
  creature_type_spider2_anim_flags = 1;
  creature_type_spider2_base_frame = 0x10;
  creature_type_spider2_corpse_frame = 1;
  creature_type_spider2_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_spider_sp2_0047373c);
  creature_type_spider2_sfx_attack_02 = sfx_spider_attack_02;
  creature_type_spider2_sfx_attack_01 = sfx_spider_attack_01;
  creature_type_spider2_sfx_die_01 = sfx_spider_die_01;
  creature_type_spider2_sfx_die_03 = sfx_spider_die_03;
  creature_type_spider2_field_0x20 = 0x3f800000;
  creature_type_spider2_anim_rate = 0x3fc00000;
  creature_type_spider2_sfx_die_02 = sfx_spider_die_02;
  creature_type_spider2_sfx_die_04 = sfx_spider_die_04;
  creature_type_trooper_anim_flags = 1;
  creature_type_trooper_base_frame = 0x10;
  creature_type_trooper_corpse_frame = 2;
  credits_secret_gems_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_alien_00473734);
  creature_type_alien_sfx_attack_01 = sfx_alien_attack_01;
  creature_type_alien_sfx_attack_02 = sfx_alien_attack_02;
  creature_type_alien_sfx_die_01 = sfx_alien_die_01;
  creature_type_alien_sfx_die_02 = sfx_alien_die_02;
  creature_type_alien_sfx_die_03 = sfx_alien_die_03;
  creature_type_alien_sfx_die_04 = sfx_alien_die_04;
  creature_type_trooper_sfx_die_01 = sfx_trooper_die_01;
  creature_type_alien_field_0x20 = 0x3f800000;
  creature_type_alien_anim_rate = 0x3faccccd;
  creature_type_alien_variant_id = 0;
  creature_type_alien_base_frame = 0x20;
  creature_type_alien_corpse_frame = 4;
  creature_type_trooper_sfx_die_02 = sfx_trooper_die_02;
  creature_type_trooper_sfx_die_03 = sfx_trooper_die_03;
  creature_type_trooper_variant_id = 7;
  player_sprite_texture_id = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_trooper_0047372c);
  camera_offset_x = (float)terrain_texture_width * 0.5;
  perk_choices_dirty = 1;
  bonus_spawn_guard = 0;
  puVar14 = &weapon_usage_time;
  for (iVar11 = 0x40; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  camera_offset_y = (float)terrain_texture_height * 0.5;
  weapon_table_init();
  weapon_refresh_available();
  perks_rebuild_available();
  effect_defaults_reset();
  perk_pending_count = 0;
  survival_spawn_cooldown = 0;
  creatures_any_active_flag = 0;
  time_scale_active = 0;
  time_scale_factor = 0x3f800000;
  bonus_reflex_boost_timer = 0;
  bonus_weapon_power_up_timer = 0;
  bonus_energizer_timer = 0;
  plaguebearer_infection_count = 0;
  doctor_perk_target_creature = 0xffffffff;
  highscore_active_record.full_version_marker = '\0';
  highscore_active_record.survival_elapsed_ms = 0;
  highscore_active_record.score_xp = 0;
  highscore_active_record.quest_stage_minor = '\0';
  highscore_active_record.quest_stage_major = '\0';
  highscore_active_record.game_mode_id = '\0';
  highscore_active_record.most_used_weapon_id = '\0';
  highscore_active_record.creature_kill_count = 0;
  highscore_active_record.shots_hit = 0;
  highscore_active_record.shots_fired = 0;
  highscore_active_record.date_checksum = '\0';
  highscore_active_record.year_offset = '\0';
  highscore_active_record.month = '\0';
  highscore_active_record.day = '\0';
  highscore_active_record.flags = '\0';
  uVar3 = crt_rand();
  highscore_active_record.reserved0._0_4_ = uVar3 & 0xfee050f;
  fx_queue_ground_count = 0;
  bonus_freeze_timer = 0;
  jinxed_effect_cooldown = 0;
  crt_newmode = 0xbf800000;
  perk_prompt_timer = 0;
  projectile_reset_pools();
  player_reset_all();
  player_aux_timer = 0;
  hud_kill_count_display = 0;
  pfVar4 = &player_state_table.low_health_timer;
  do {
    pfVar4[5] = -1.0;
    pfVar4[6] = -1.0;
    *pfVar4 = 100.0;
    pfVar4[3] = 0.0;
    pfVar4 = pfVar4 + 0xd8;
  } while ((int)pfVar4 < 0x491280);
  pbVar5 = bonus_pool;
  do {
    pbVar5->bonus_id = BONUS_ID_NONE;
    pbVar5 = pbVar5 + 1;
  } while ((int)pbVar5 < 0x482b08);
  ppVar6 = projectile_pool;
  do {
    ppVar6->active = '\0';
    ppVar6 = ppVar6 + 1;
  } while ((int)ppVar6 < 0x493eb8);
  psVar7 = &sprite_effect_pool;
  do {
    *(undefined1 *)&psVar7->active = 0;
    psVar7 = psVar7 + 1;
  } while ((int)psVar7 < 0x49aa20);
  psVar8 = secondary_projectile_pool;
  do {
    psVar8->active = '\0';
    psVar8 = psVar8 + 1;
  } while ((int)psVar8 < 0x4965d8);
  iVar11 = 0;
  piVar12 = &creature_pool.target_player;
  do {
    uVar1 = config_blob.reserved0._20_4_;
    piVar12[-0xe] = 0;
    ((creature_t *)(piVar12 + -0x1c))->active = '\0';
    if (uVar1 == 0) {
      *(undefined1 *)piVar12 = 0;
    }
    else {
      *(char *)piVar12 = (char)(iVar11 % (int)uVar1);
    }
    *(uchar *)(piVar12 + -0x1a) = '\x01';
    piVar12[7] = 0;
    iVar9 = crt_rand();
    piVar13 = piVar12 + 0x26;
    iVar11 = iVar11 + 1;
    piVar12[9] = (int)(float)(iVar9 % 0x1f);
    piVar12 = piVar13;
  } while ((int)piVar13 < 0x4aa3a8);
  pcVar10 = &creature_spawn_slot_table;
  do {
    pcVar10->owner = (creature_t *)0x0;
    pcVar10 = pcVar10 + 1;
  } while ((int)pcVar10 < 0x4852d0);
  fx_queue_rotated = 0;
  fx_queue_count = 0;
  highscore_active_record.full_version_marker = '\0';
  highscore_active_record.survival_elapsed_ms = 0;
  highscore_active_record.score_xp = 0;
  highscore_active_record.quest_stage_minor = '\0';
  highscore_active_record.quest_stage_major = '\0';
  highscore_active_record.game_mode_id = '\0';
  highscore_active_record.most_used_weapon_id = '\0';
  highscore_active_record.creature_kill_count = 0;
  highscore_active_record.shots_hit = 0;
  highscore_active_record.shots_fired = 0;
  highscore_active_record.date_checksum = '\0';
  highscore_active_record.year_offset = '\0';
  highscore_active_record.month = '\0';
  highscore_active_record.day = '\0';
  highscore_active_record.flags = '\0';
  uVar3 = crt_rand();
  highscore_active_record.reserved0._0_4_ = uVar3 & 0xfee050f;
  terrain_generate_random();
  return;
}



/* game_sequence_get @ 0041df60 */

/* returns the saved game_sequence_id */

int game_sequence_get(void)

{
  return game_status_blob.game_sequence_id;
}



/* init_audio_and_terrain @ 0042a9f0 */

/* sound init + terrain texture setup */

void init_audio_and_terrain(void)

{
  IGrim2D_vtbl *pIVar1;
  undefined4 uVar2;
  int iVar3;
  char *extraout_EDX;
  char *extraout_EDX_00;
  char *extraout_EDX_01;
  longlong lVar4;
  char *pcVar5;
  
  console_printf(&console_log_queue,s_Init_Grim_successful__00474114);
  console_printf(&console_log_queue,&console_empty_line_str);
  console_printf(&console_log_queue,s________________________004740fc);
  console_printf(&console_log_queue,s___Sound_init___________004740e4);
  console_printf(&console_log_queue,s________________________004740fc);
  if (crt_fmode == '\0') {
    iVar3 = sfx_system_init();
    if ((char)iVar3 == '\0') {
      crt_fmode = '\x01';
    }
  }
  else {
    console_printf(&console_log_queue,s____no_sounds_selected_004740cc);
  }
  console_printf(&console_log_queue,&console_empty_line_str);
  terrain_texture_width = 0x400;
  terrain_texture_height = 0x400;
  if (0.5 <= (float)config_blob.reserved0._112_4_) {
    if (4.0 < (float)config_blob.reserved0._112_4_) {
      config_blob.reserved0[0x70] = '\0';
      config_blob.reserved0[0x71] = '\0';
      config_blob.reserved0[0x72] = 0x80;
      config_blob.reserved0[0x73] = '@';
    }
  }
  else {
    config_blob.reserved0[0x70] = '\0';
    config_blob.reserved0[0x71] = '\0';
    config_blob.reserved0[0x72] = '\0';
    config_blob.reserved0[0x73] = '?';
  }
  if (terrain_texture_failed == '\0') {
    lVar4 = __ftol();
    iVar3 = (*grim_interface_ptr->vtable->grim_create_texture)
                      (s_ground_004740c4,(int)lVar4,(int)lVar4);
    uVar2 = config_blob.reserved0._112_4_;
    pcVar5 = extraout_EDX;
    if ((char)iVar3 == '\0') {
      config_blob.reserved0._112_4_ =
           (float)config_blob.reserved0._112_4_ + (float)config_blob.reserved0._112_4_;
      pIVar1 = grim_interface_ptr->vtable;
      lVar4 = __ftol();
      iVar3 = (int)lVar4;
      lVar4 = __ftol();
      iVar3 = (*pIVar1->grim_create_texture)(s_ground_004740c4,(int)lVar4,iVar3);
      if ((char)iVar3 == '\0') {
        terrain_texture_failed = '\x01';
        config_blob.reserved0._112_4_ = uVar2;
        console_printf(&console_log_queue,s_Failed_to_create_terrain_texture_004740a0);
        pcVar5 = s___>_entering_safemode__00474088;
      }
      else {
        pcVar5 = s_Created_terrain_texture__0047406c;
      }
      console_printf(&console_log_queue,pcVar5);
      pcVar5 = extraout_EDX_00;
    }
    if (terrain_texture_failed == '\0') goto LAB_0042abbf;
  }
  console_printf(&console_log_queue,s_Running_in_safemode__using_stati_00474034);
  pcVar5 = extraout_EDX_01;
LAB_0042abbf:
  console_flush_log(&console_log_queue,pcVar5);
  return;
}



/* load_textures_step @ 0042abd0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* stage-based texture loading (advances DAT_004aaf88) */

int load_textures_step(void)

{
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 extraout_EDX_08;
  int iVar3;
  int iVar4;
  char *unaff_retaddr;
  char *pcVar1;
  char *pcVar2;
  
  if (startup_texture_load_stage == 0) {
    texture_get_or_load(s_GRIM_Font2_004745d8,s_load_smallWhite_tga_004745e4);
    texture_get_or_load(s_trooper_0047372c,s_game_trooper_jaz_004745c4);
    texture_get_or_load(s_creature_zombie,s_game_zombie_jaz_004745b4);
    texture_get_or_load(s_creature_spider,s_game_spider_sp1_jaz_004745a0);
    texture_get_or_load(s_spider_sp2_0047373c,s_game_spider_sp2_jaz_0047458c);
    texture_get_or_load(s_alien_00473734,s_game_alien_jaz_0047457c);
    texture_get_or_load(s_creature_lizard,s_game_lizard_jaz_0047456c);
    in_EDX = extraout_EDX;
  }
  if (startup_texture_load_stage == 1) {
    texture_arrow_id = texture_get_or_load(s_arrow_00474554,s_load_arrow_tga_0047455c);
    texture_get_or_load(s_bullet_i_00474534,s_load_bullet16_tga_00474540);
    bullet_trail_texture =
         texture_get_or_load(s_bulletTrail_00474510,s_load_bulletTrail_tga_0047451c);
    texture_get_or_load(s_bodyset_004744f4,s_game_bodyset_jaz_004744fc);
    bodyset_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_bodyset_004744f4);
    projectile_texture = texture_get_or_load(s_projs_004744dc,s_game_projs_jaz_004744e4);
    in_EDX = extraout_EDX_00;
  }
  if (startup_texture_load_stage == 2) {
    texture_get_or_load(s_ui_iconAim_004744bc,s_ui_ui_iconAim_jaz_004744c8);
    texture_get_or_load(s_ui_buttonSm_00474498,s_ui_ui_button_64x32_jaz_004744a4);
    texture_get_or_load(s_ui_buttonMd_00474474,s_ui_ui_button_128x32_jaz_00474480);
    texture_get_or_load(s_ui_checkOn_00474454,s_ui_ui_checkOn_jaz_00474460);
    texture_get_or_load(s_ui_checkOff_00474434,s_ui_ui_checkOff_jaz_00474440);
    texture_get_or_load(s_ui_rectOff,s_ui_ui_rectOff_jaz_00474420);
    texture_get_or_load(s_ui_rectOn,s_ui_ui_rectOn_jaz_00474400);
    texture_get_or_load(s_bonuses_004743d8,s_game_bonuses_jaz_004743e0);
    in_EDX = extraout_EDX_01;
  }
  if (startup_texture_load_stage == 3) {
    pcVar2 = s_ui_ind_bullet_jaz;
    texture_get_or_load_alt(s_ui_ind_bullet_jaz,unaff_retaddr);
    pcVar1 = s_ui_ind_rocket_jaz;
    texture_get_or_load_alt(s_ui_ind_rocket_jaz,pcVar2);
    pcVar2 = s_ui_ind_electric_jaz;
    texture_get_or_load_alt(s_ui_ind_electric_jaz,pcVar1);
    texture_get_or_load_alt(s_ui_ind_fire_jaz,pcVar2);
    bonus_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_bonuses_004743d8);
    particles_texture = texture_get_or_load_alt(s_game_particles_jaz_004743c4,unaff_retaddr);
    in_EDX = extraout_EDX_02;
  }
  if (startup_texture_load_stage == 4) {
    pcVar1 = s_ui_ui_indLife_jaz_004743b0;
    texture_life_id = texture_get_or_load_alt(s_ui_ui_indLife_jaz_004743b0,unaff_retaddr);
    pcVar2 = s_ui_ui_indPanel_jaz_0047439c;
    texture_panel_id = texture_get_or_load_alt(s_ui_ui_indPanel_jaz_0047439c,pcVar1);
    pcVar1 = s_ui_ui_arrow_jaz_0047438c;
    texture_arrow_alt_id = texture_get_or_load_alt(s_ui_ui_arrow_jaz_0047438c,pcVar2);
    pcVar2 = s_ui_ui_cursor_jaz_00474378;
    texture_cursor_id = texture_get_or_load_alt(s_ui_ui_cursor_jaz_00474378,pcVar1);
    texture_aim_id = texture_get_or_load_alt(s_ui_ui_aim_jaz_00474368,pcVar2);
    in_EDX = extraout_EDX_03;
  }
  if (startup_texture_load_stage == 5) {
    if (terrain_texture_failed == '\0') {
      pcVar2 = s_ter_ter_q1_base_jaz_00474354;
      terrain_texture_handles =
           texture_get_or_load_alt(s_ter_ter_q1_base_jaz_00474354,unaff_retaddr);
      pcVar1 = s_ter_ter_q1_tex1_jaz_00474340;
      terrain_texture_q1_tex1 = texture_get_or_load_alt(s_ter_ter_q1_tex1_jaz_00474340,pcVar2);
      pcVar2 = s_ter_ter_q2_base_jaz_0047432c;
      terrain_texture_q2_base = texture_get_or_load_alt(s_ter_ter_q2_base_jaz_0047432c,pcVar1);
      pcVar1 = s_ter_ter_q2_tex1_jaz_00474318;
      terrain_texture_q2_tex1 = texture_get_or_load_alt(s_ter_ter_q2_tex1_jaz_00474318,pcVar2);
      pcVar2 = s_ter_ter_q3_base_jaz_00474304;
      terrain_texture_q3_base = texture_get_or_load_alt(s_ter_ter_q3_base_jaz_00474304,pcVar1);
      pcVar1 = s_ter_ter_q3_tex1_jaz_004742f0;
      terrain_texture_q3_tex1 = texture_get_or_load_alt(s_ter_ter_q3_tex1_jaz_004742f0,pcVar2);
      pcVar2 = s_ter_ter_q4_base_jaz_004742dc;
      terrain_texture_q4_base = texture_get_or_load_alt(s_ter_ter_q4_base_jaz_004742dc,pcVar1);
      terrain_texture_q4_tex1 = texture_get_or_load_alt(s_ter_ter_q4_tex1_jaz_004742c8,pcVar2);
      in_EDX = extraout_EDX_04;
    }
    else {
      pcVar2 = s_ter_fb_q1_jaz_004742b8;
      terrain_texture_handles = texture_get_or_load_alt(s_ter_fb_q1_jaz_004742b8,unaff_retaddr);
      pcVar1 = s_ter_fb_q2_jaz_004742a8;
      terrain_texture_q1_tex1 = texture_get_or_load_alt(s_ter_fb_q2_jaz_004742a8,pcVar2);
      pcVar2 = s_ter_fb_q3_jaz_00474298;
      terrain_texture_q2_base = texture_get_or_load_alt(s_ter_fb_q3_jaz_00474298,pcVar1);
      terrain_texture_q2_tex1 = texture_get_or_load_alt(s_ter_fb_q4_jaz_00474288,pcVar2);
      terrain_render_target = terrain_texture_handles;
      in_EDX = extraout_EDX_05;
    }
  }
  if (startup_texture_load_stage == 6) {
    pcVar1 = s_ui_ui_textLevComp_jaz_00474270;
    texture_level_complete_id = texture_get_or_load_alt(s_ui_ui_textLevComp_jaz_00474270,unaff_retaddr);
    pcVar2 = s_ui_ui_textQuest_jaz_0047425c;
    tex_quest_text = texture_get_or_load_alt(s_ui_ui_textQuest_jaz_0047425c,pcVar1);
    pcVar1 = s_ui_ui_num1_jaz_0047424c;
    tex_quest_num1 = texture_get_or_load_alt(s_ui_ui_num1_jaz_0047424c,pcVar2);
    pcVar2 = s_ui_ui_num2_jaz_0047423c;
    tex_quest_num2 = texture_get_or_load_alt(s_ui_ui_num2_jaz_0047423c,pcVar1);
    pcVar1 = s_ui_ui_num3_jaz_0047422c;
    tex_quest_num3 = texture_get_or_load_alt(s_ui_ui_num3_jaz_0047422c,pcVar2);
    pcVar2 = s_ui_ui_num4_jaz_0047421c;
    tex_quest_num4 = texture_get_or_load_alt(s_ui_ui_num4_jaz_0047421c,pcVar1);
    tex_quest_num5 = texture_get_or_load_alt(s_ui_ui_num5_jaz_0047420c,pcVar2);
    in_EDX = extraout_EDX_06;
  }
  if (startup_texture_load_stage == 7) {
    ui_weapon_icons_texture = texture_get_or_load(s_ui_wicons_004741ec,s_ui_ui_wicons_jaz_004741f8);
    texture_get_or_load(s_iGameUI_texture_name,s_ui_ui_gameTop_jaz_004741d8);
    pcVar1 = s_iHeart_texture_name;
    texture_get_or_load(s_iHeart_texture_name,s_ui_ui_lifeHeart_jaz_004741c4);
    pcVar2 = s_ui_ui_clockTable_jaz_004741ac;
    ui_clock_table_texture = texture_get_or_load_alt(s_ui_ui_clockTable_jaz_004741ac,pcVar1);
    ui_clock_hands_texture = texture_get_or_load_alt(s_ui_ui_clockPointer_jaz_00474194,pcVar2);
    in_EDX = extraout_EDX_07;
  }
  _iVar3 = CONCAT44(in_EDX,terrain_render_target);
  if (startup_texture_load_stage == 8) {
    tex_muzzle_flash = texture_get_or_load_alt(s_game_muzzleFlash_jaz_0047417c,unaff_retaddr);
    texture_get_or_load(s_ui_dropOn_00474158,s_ui_ui_dropDownOn_jaz_00474164);
    texture_get_or_load(s_ui_dropOff_00474134,s_ui_ui_dropDownOff_jaz_00474140);
    _iVar3 = CONCAT44(extraout_EDX_08,terrain_render_target);
    if (terrain_texture_failed == '\0') {
      _iVar3 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_ground_004740c4);
    }
  }
  terrain_render_target = (int)_iVar3;
  if (startup_texture_load_stage == 9) {
    game_state_id = 0;
    projectile_bullet_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_bullet_i_00474534);
    _iVar4 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_aim64_0047412c);
    _iVar3 = CONCAT44((int)((ulonglong)_iVar4 >> 0x20),terrain_render_target);
    _DAT_00496698 = (int)_iVar4;
    crt_app_type = 1;
  }
  terrain_render_target = (int)_iVar3;
  startup_texture_load_stage = startup_texture_load_stage + 1;
  DAT_00473a5c = 0xb;
  console_flush_log(&console_log_queue,(char *)((ulonglong)_iVar3 >> 0x20));
  return (uint)(10 < startup_texture_load_stage);
}



/* game_startup_init_prelude @ 0042b090 */

/* prelude called by game_startup_init; handles core init, dates, registry time, and terrain reset
    */

void game_startup_init_prelude(void)

{
  LONG LVar1;
  char *filename;
  HKEY key;
  uint in_stack_ffffffa4;
  undefined4 uStack_58;
  undefined4 in_stack_ffffffe0;
  
  allocated_memory_ptr = strdup_malloc(&s_empty_string);
  (*grim_interface_ptr->vtable->grim_set_config_var)
            (0x12,CONCAT31((int3)((uint)in_stack_ffffffe0 >> 8),1));
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  effect_uv_tables_init();
  console_flush_log(&console_log_queue,filename);
  uStack_58 = 0x42b10a;
  console_printf(&console_log_queue,s_Entering_Crimsonland___0047465c);
  perks_init_database();
  weapon_table_init();
  game_core_init();
  GetLocalTime((LPSYSTEMTIME)&local_system_time);
  if (local_system_time._2_2_ == 9) {
    if (local_system_day != 0xc) goto LAB_0042b17a;
  }
  else if (local_system_time._2_2_ == 0xb) {
    if (local_system_day != 8) goto LAB_0042b17a;
  }
  else if ((local_system_time._2_2_ != 0xc) || (local_system_day != 0x12)) goto LAB_0042b17a;
  crt_debug_flag = 1;
  uStack_58 = 0x42b177;
  texture_get_or_load(s_balloon_00474648,s_balloon_tga_00474650);
LAB_0042b17a:
  crt_debug_flag = 0;
  uStack_58 = 0x42b190;
  console_printf(&console_log_queue,s_Unloaded_resource_paq_00474630);
  key = (HKEY)0x10;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x10,in_stack_ffffffa4);
  uStack_58 = ZEXT24(qpc_timestamp_scratch);
  QueryPerformanceCounter((LARGE_INTEGER *)&stack0xffffffa8);
  crt_srand(uStack_58);
  gameplay_reset_state();
  crt_dowildcard_flag = 1;
  terrain_generate_random();
  crt_dowildcard_flag = 0;
  LVar1 = RegCreateKeyExA((HKEY)0x80000001,s_Software_10tons_entertainment_Cr_00474604,0,(LPSTR)0x0,
                          0,0xf003f,(LPSECURITY_ATTRIBUTES)0x0,(PHKEY)&stack0xffffffa0,(LPDWORD)0x0)
  ;
  if (LVar1 == 0) {
    reg_read_dword_default((HKEY)key,s_timePlayed_004745f8,(uint *)&stack0xffffffa4,0);
    gameplay_elapsed_ms = in_stack_ffffffa4;
    RegCloseKey(key);
  }
  return;
}



/* game_startup_init @ 0042b290 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* startup init: logs, builds perks/weapons, seeds UI/effects, loads registry time; triggers intro
   music then switches to crimson_theme */

void game_startup_init(void)

{
  int handle;
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  IGrim2D_vtbl *pIVar4;
  float10 extraout_ST0;
  longlong lVar5;
  float fVar6;
  char *in_stack_ffffffd8;
  char *pcVar7;
  float fVar8;
  float fVar9;
  
  (*grim_interface_ptr->vtable->grim_get_frame_dt)();
  frame_dt = (float)extraout_ST0;
  if ((float10)0.1 < extraout_ST0) {
    frame_dt = 0.1;
  }
  if (s_game_text_format != '\0') {
    s_game_text_format = '\0';
  }
  if (crt_commode == '\0') {
    load_textures_step();
  }
  if ((s_game_text_format == '\0') && (crt_app_type != '\0')) {
    texture_get_or_load(s_splashReflexive_00474714,s_load_splashReflexive_jpg_00474724);
    in_stack_ffffffd8 = s_splash10Tons_004746ec;
    texture_get_or_load(s_splash10Tons_004746ec,s_load_splash10tons_jaz_004746fc);
    game_startup_init_prelude();
    crt_beginthread(&LAB_0042b250,0,(void *)0x0);
    crt_app_type = '\0';
    crt_commode = '\x01';
    if (0.5 < startup_splash_timer) {
      startup_splash_timer = 0.5;
    }
LAB_0042b35f:
    if ((crt_has_crt_init != '\0') && (crt_env_initialized != '\0')) {
      if (crt_exit_flag < 5) {
        crt_exit_flag = crt_exit_flag + 1;
        Sleep(5);
        (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
        audio_update();
        console_update(0x47eea0);
        console_render(&console_log_queue);
        if (*(float *)((int)cv_showFPS + 0xc) != 0.0) {
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
          (*grim_interface_ptr->vtable->grim_get_fps)();
          lVar5 = __ftol();
          pIVar4 = grim_interface_ptr->vtable;
          if ((int)lVar5 < 400) {
            (*pIVar4->grim_get_fps)();
            __ftol();
            pcVar7 = &s_int_format;
            iVar2 = config_blob.screen_width + -0x2d;
          }
          else {
            (*pIVar4->grim_get_fps)();
            __ftol();
            pcVar7 = &s_empty_string;
            iVar2 = config_blob.screen_width + -0x33;
          }
          (*pIVar4->grim_draw_text_small_fmt)
                    (grim_interface_ptr,(float)iVar2,(float)(config_blob.screen_height + -0x18),
                     pcVar7);
        }
        iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x10);
        if (((char)iVar2 != '\0') &&
           (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x38), (char)iVar2 != '\0')) {
          return;
        }
        return;
      }
      if (14.0 < startup_splash_timer) {
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x2d,(uint)in_stack_ffffffd8);
        pIVar4 = grim_interface_ptr->vtable;
        iVar2 = (*pIVar4->grim_get_texture_handle)(s_splashReflexive_00474714);
        (*pIVar4->grim_destroy_texture)(iVar2);
        pIVar4 = grim_interface_ptr->vtable;
        iVar2 = (*pIVar4->grim_get_texture_handle)(s_splash10Tons_004746ec);
        (*pIVar4->grim_destroy_texture)(iVar2);
        sfx_mute_all(music_track_intro_id);
        iVar2 = game_is_full_version();
        if ((char)iVar2 == '\0') {
          sfx_play_exclusive(music_track_crimsonquest_id);
          demo_mode_start();
        }
        else {
          sfx_play_exclusive(music_track_crimson_theme_id);
        }
        (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
        return;
      }
      iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(1);
      if (((((char)iVar2 != '\0') ||
           (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x39), (char)iVar2 != '\0')) ||
          (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x1c), (char)iVar2 != '\0')) ||
         ((iVar2 = input_primary_just_pressed(), (char)iVar2 != '\0' ||
          (iVar2 = (*grim_interface_ptr->vtable->grim_was_mouse_button_pressed)(1),
          (char)iVar2 != '\0')))) {
        crt_winmain_entered = '\x01';
        goto LAB_0042bd39;
      }
      if (crt_dowildcard_flag != '\0') goto LAB_0042bd39;
      iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x29);
      if ((char)iVar2 != '\0') {
        console_set_open(&console_log_queue,console_open_flag == '\0');
      }
      game_time_s = game_time_s + frame_dt;
      frame_dt_stored = frame_dt;
      (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
      if (DAT_004aaf85 != '\0') {
        iVar2 = sfx_is_unmuted(music_track_intro_id);
        if ((char)iVar2 == '\0') {
          sfx_play_exclusive(music_track_intro_id);
        }
        startup_splash_timer = frame_dt * 1.1 + startup_splash_timer;
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
        startup_splash_timer = startup_splash_timer - 2.0;
        if (crt_winmain_entered != '\0') {
          if ((startup_splash_timer < 1.0) ||
             ((5.0 <= startup_splash_timer &&
              ((startup_splash_timer < 7.0 || (11.0 <= startup_splash_timer)))))) {
            startup_splash_timer = 16.0;
          }
          else {
            startup_splash_timer = frame_dt * 4.0 + startup_splash_timer;
          }
        }
        uVar3 = 0x40;
        iVar2 = 0x40;
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
        (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
        if ((startup_splash_timer <= 1.0) || (5.0 <= startup_splash_timer)) {
          if (6.0 < startup_splash_timer) {
            handle = (*grim_interface_ptr->vtable->grim_get_texture_handle)
                               (s_splashReflexive_00474714);
            uVar3 = 0x100;
            iVar2 = 0x100;
            goto LAB_0042b800;
          }
        }
        else {
          uVar3 = 0x80;
          iVar2 = 0x80;
          handle = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_splash10Tons_004746ec);
LAB_0042b800:
          if (-1 < handle) {
            (*grim_interface_ptr->vtable->grim_bind_texture)(handle,0);
          }
        }
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        if (startup_splash_timer <= 1.0) {
          if (2.0 <= startup_splash_timer) goto LAB_0042b8d9;
          if (4.0 <= startup_splash_timer) goto LAB_0042b97b;
LAB_0042ba4c:
          if (7.0 < startup_splash_timer) {
            if (8.0 <= startup_splash_timer) goto LAB_0042bb08;
            (*grim_interface_ptr->vtable->grim_set_color)
                      (1.0,1.0,1.0,(startup_splash_timer - 6.0) - 1.0);
            fVar9 = (float)iVar2;
            pIVar4 = grim_interface_ptr->vtable;
            fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
            fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
            goto LAB_0042bc9a;
          }
          if (8.0 <= startup_splash_timer) {
LAB_0042bb08:
            if (10.0 <= startup_splash_timer) goto LAB_0042bbaa;
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
            fVar9 = (float)iVar2;
            pIVar4 = grim_interface_ptr->vtable;
            fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
            fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
            goto LAB_0042bc9a;
          }
          if (10.0 <= startup_splash_timer) {
LAB_0042bbaa:
            if (startup_splash_timer < 11.0) {
              fVar9 = 1.0 - ((startup_splash_timer - 6.0) - 4.0);
              if (0.0 <= fVar9) {
                if (1.0 < fVar9) {
                  fVar9 = 1.0;
                }
              }
              else {
                fVar9 = 0.0;
              }
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar9);
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar9);
              fVar9 = (float)iVar2;
              pIVar4 = grim_interface_ptr->vtable;
              fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
              fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
              goto LAB_0042bc9a;
            }
          }
        }
        else {
          if (2.0 <= startup_splash_timer) {
LAB_0042b8d9:
            if (4.0 <= startup_splash_timer) {
LAB_0042b97b:
              if (5.0 <= startup_splash_timer) goto LAB_0042ba4c;
              fVar9 = 1.0 - (startup_splash_timer - 4.0);
              if (0.0 <= fVar9) {
                if (1.0 < fVar9) {
                  fVar9 = 1.0;
                }
              }
              else {
                fVar9 = 0.0;
              }
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar9);
              fVar9 = (float)iVar2;
              pIVar4 = grim_interface_ptr->vtable;
              fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
              fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
            }
            else {
              (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
              fVar9 = (float)iVar2;
              pIVar4 = grim_interface_ptr->vtable;
              fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
              fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
            }
          }
          else {
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,startup_splash_timer - 1.0);
            fVar9 = (float)iVar2;
            pIVar4 = grim_interface_ptr->vtable;
            fVar6 = (float)(int)(config_blob.screen_height / 2 - uVar3 / 2);
            fVar8 = (float)(config_blob.screen_width / 2 + -0x100);
          }
LAB_0042bc9a:
          (*pIVar4->grim_draw_quad)(fVar8,fVar6,512.0,fVar9);
        }
        startup_splash_timer = startup_splash_timer + 2.0;
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
        (*grim_interface_ptr->vtable->grim_end_batch)();
        audio_update();
      }
      console_update(0x47eea0);
      console_render(&console_log_queue);
      iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x10);
      if (((char)iVar2 != '\0') &&
         (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x38), (char)iVar2 != '\0')) {
        return;
      }
      if (game_quit_flag != '\0') {
        return;
      }
LAB_0042bd39:
      if (*(float *)((int)cv_showFPS + 0xc) == 0.0) {
        return;
      }
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
      (*grim_interface_ptr->vtable->grim_get_fps)();
      lVar5 = __ftol();
      pIVar4 = grim_interface_ptr->vtable;
      if ((int)lVar5 < 400) {
        (*pIVar4->grim_get_fps)();
        __ftol();
        pcVar7 = &s_int_format;
        iVar2 = config_blob.screen_width + -0x2d;
      }
      else {
        (*pIVar4->grim_get_fps)();
        __ftol();
        pcVar7 = &s_empty_string;
        iVar2 = config_blob.screen_width + -0x33;
      }
      (*pIVar4->grim_draw_text_small_fmt)
                (grim_interface_ptr,(float)iVar2,(float)(config_blob.screen_height + -0x18),pcVar7);
      return;
    }
    if ((crt_commode != '\0') && (crt_has_crt_init != '\0')) {
      startup_splash_timer = startup_splash_timer - frame_dt;
      if (startup_splash_timer < 0.0) {
        startup_splash_timer = 0.0;
        crt_env_initialized = '\x01';
        pIVar4 = grim_interface_ptr->vtable;
        iVar2 = (*pIVar4->grim_get_texture_handle)(s_loading_004746e4);
        (*pIVar4->grim_destroy_texture)(iVar2);
        pIVar4 = grim_interface_ptr->vtable;
        iVar2 = (*pIVar4->grim_get_texture_handle)(s_logo_esrb_004746d8);
        (*pIVar4->grim_destroy_texture)(iVar2);
      }
      goto LAB_0042bea6;
    }
  }
  else if (crt_commode != '\0') goto LAB_0042b35f;
  startup_splash_timer = startup_splash_timer + frame_dt;
LAB_0042bea6:
  (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  fVar9 = startup_splash_timer + startup_splash_timer;
  if (fVar9 <= 1.0) {
    if (fVar9 < 0.0) {
      fVar9 = 0.0;
    }
  }
  else {
    fVar9 = 1.0;
  }
  fVar8 = fVar9;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar9);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  fVar6 = 0.0;
  pIVar4 = grim_interface_ptr->vtable;
  iVar2 = (*pIVar4->grim_get_texture_handle)(s_logo_esrb_004746d8);
  (*pIVar4->grim_bind_texture)(iVar2,(int)fVar6);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)
            ((screen_width_f - 256.0) - 1.0,(screen_height_f - 128.0) - 1.0,256.0,128.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  fVar6 = 0.0;
  pIVar4 = grim_interface_ptr->vtable;
  iVar2 = (*pIVar4->grim_get_texture_handle)(s_loading_004746e4);
  (*pIVar4->grim_bind_texture)(iVar2,(int)fVar6);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)
            (screen_width_f * 0.5 + 128.0,screen_height_f * 0.5 + 16.0,128.0,32.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  pIVar4 = grim_interface_ptr->vtable;
  fVar6 = 0.0;
  iVar2 = (*pIVar4->grim_get_texture_handle)(s_cl_logo_00471f70);
  (*pIVar4->grim_bind_texture)(iVar2,(int)fVar6);
  (*grim_interface_ptr->vtable->grim_draw_quad)
            (screen_width_f * 0.5 - 256.0,screen_height_f * 0.5 - 32.0,512.0,64.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  fVar6 = 1.0;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar9);
  if (*(float *)((int)cv_silentloads + 0xc) == 0.0) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar8 * 0.7);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,screen_width_f * 0.5 - 246.0,screen_height_f * 0.5 + 32.0,
               s_Grim_GFX__d__d_004746c8,startup_texture_load_stage);
    fVar6 = sfx_load_counter;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,screen_width_f * 0.5 - 246.0,screen_height_f * 0.5 + 45.0,
               s_Grim_SFX___d__d_004746b8);
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  ui_text_alpha = fVar6 * 0.7;
  (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)
            ((float *)&stack0xffffffd0,screen_width_f + 8.0,128.0);
  console_update(0x47eea0);
  console_render(&console_log_queue);
  if (*(float *)((int)cv_showFPS + 0xc) != 0.0) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
    (*grim_interface_ptr->vtable->grim_get_fps)();
    lVar5 = __ftol();
    pIVar4 = grim_interface_ptr->vtable;
    if ((int)lVar5 < 400) {
      (*pIVar4->grim_get_fps)();
      lVar5 = __ftol();
      uVar1 = (undefined4)lVar5;
      pcVar7 = &s_int_format;
      iVar2 = config_blob.screen_width + -0x2d;
    }
    else {
      (*pIVar4->grim_get_fps)();
      lVar5 = __ftol();
      uVar1 = (undefined4)lVar5;
      pcVar7 = &s_empty_string;
      iVar2 = config_blob.screen_width + -0x33;
    }
    (*pIVar4->grim_draw_text_small_fmt)
              (grim_interface_ptr,(float)iVar2,(float)(config_blob.screen_height + -0x18),pcVar7,
               uVar1);
  }
  Sleep(0x32);
  return;
}



/* crimsonland_main @ 0042c450 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* primary game init/run/shutdown sequence */

int crimsonland_main(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  HRESULT HVar4;
  IDirect3D8 *This;
  char *pcVar5;
  uchar *puVar6;
  float *pfVar7;
  int *piVar8;
  void *pvVar9;
  int *piVar10;
  LONG LVar11;
  uint uVar12;
  int *piVar13;
  char *filename;
  char *filename_00;
  char *filename_01;
  char *extraout_EDX;
  char *extraout_EDX_00;
  char *filename_02;
  char *filename_03;
  char *filename_04;
  char *filename_05;
  char *extraout_EDX_01;
  char *extraout_EDX_02;
  char *extraout_EDX_03;
  char *extraout_EDX_04;
  char *filename_06;
  char *filename_07;
  char *extraout_EDX_05;
  char *extraout_EDX_06;
  char *extraout_EDX_07;
  undefined4 *puVar14;
  LPCCH pCVar15;
  HKEY key;
  undefined4 uVar16;
  uint in_stack_fffffad0;
  undefined4 uStack_52c;
  undefined4 in_stack_fffffb20;
  char *lpCaption;
  UINT uType;
  undefined4 in_stack_fffffb34;
  undefined4 in_stack_fffffb48;
  uint in_stack_fffffb70;
  undefined4 in_stack_fffffb84;
  uint in_stack_fffffb98;
  uint in_stack_fffffbac;
  uint local_420;
  uint auStack_41c [4];
  char local_40c [12];
  WCHAR local_400 [512];
  
  uVar2 = FUN_004623b2((int *)0x0);
  crt_srand(uVar2);
  local_420 = 0;
  iVar3 = dx_get_version((int *)&local_420,local_40c,10);
  if (iVar3 < 0) {
    iVar3 = MessageBoxA((HWND)0x0,s_Unknown_DirectX_version_detected_00474d74,s_Crimsonland_00472d5c
                        ,4);
    if (iVar3 == 7) {
      return 0;
    }
  }
  else if (local_420 < 0x80100) {
    iVar3 = MessageBoxA((HWND)0x0,s_DirectX8_1_or_newer_not_detected_00474e60,s_Crimsonland_00472d5c
                        ,0x23);
    if (iVar3 != 6) {
      return 0;
    }
    MultiByteToWideChar(0,0,s_http___www_microsoft_com_windows_00474e28,-1,local_400,0x104);
    HVar4 = HlinkNavigateString((IUnknown *)0x0,local_400);
    if (-1 < HVar4) {
      return 0;
    }
    MessageBoxA((HWND)0x0,s_Failed_to_launch_web_browser__00474e08,s_Crimsonland_00472d5c,0);
    return 0;
  }
  crt_getcwd(&game_base_path,0x103);
  GetCommandLineA();
  DAT_00473a64 = 0x7b;
  This = Direct3DCreate8(0xdc);
  console_printf(&console_log_queue,s_Crimsonland_00474d64);
  console_printf(&console_log_queue,s_____________00474d54);
  console_printf(&console_log_queue,&console_empty_line_str);
  console_flush_log(&console_log_queue,filename);
  if (This == (IDirect3D8 *)0x0) {
    MessageBoxA((HWND)0x0,s_DirectX8_1_not_detected__Crimson_00474cb8,s_Crimsonland_00472d5c,0);
    return 0;
  }
  (*This->lpVtbl->Release)(This);
  console_printf(&console_log_queue,s_Game_base_path____s__00474ca0);
  console_flush_log(&console_log_queue,filename_00);
  config_ensure_file();
  console_register_command(&console_log_queue,s_setGammaRamp_00474c90,console_cmd_set_gamma_ramp);
  console_register_command
            (&console_log_queue,s_snd_addGameTune_00474c80,console_cmd_snd_add_game_tune);
  console_register_command
            (&console_log_queue,s_generateterrain_00474c70,console_cmd_generate_terrain);
  console_register_command
            (&console_log_queue,s_telltimesurvived_00474c5c,console_cmd_tell_time_survived);
  console_register_command
            (&console_log_queue,s_setresourcepaq_00474c4c,console_cmd_set_resource_paq);
  console_register_command(&console_log_queue,s_loadtexture_00474c40,console_cmd_load_texture);
  console_register_command(&console_log_queue,s_openurl_00474c38,console_cmd_open_url);
  console_register_command
            (&console_log_queue,s_sndfreqadjustment_00474c24,console_cmd_snd_freq_adjustment);
  puVar14 = &reg_key_path;
  for (iVar3 = 0x3f; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined2 *)puVar14 = 0;
  *(undefined1 *)((int)puVar14 + 2) = 0;
  reg_key_path._0_1_ = 0x53;
  reg_key_path._1_1_ = 0x6f;
  reg_key_path._2_1_ = 0x66;
  reg_key_path._3_1_ = 0x74;
  config_file_magic._0_1_ = 0x77;
  config_file_magic._1_1_ = 0x61;
  DAT_004852d6 = 0x72;
  DAT_004852d7 = 0x65;
  DAT_004852d8 = 0x5c;
  DAT_004852d9 = 0x53;
  DAT_004852da = 0x6f;
  DAT_004852db = 99;
  DAT_004852dc = 0x6b;
  grim_interface_ptr = (IGrim2D *)grim_load_interface(s____grim_grSystem_c_Release_grim__00474c00);
  console_printf(&console_log_queue,s________________________004740fc);
  console_printf(&console_log_queue,s_______Grim2D_API_______00474be8);
  console_printf(&console_log_queue,s________________________004740fc);
  console_printf(&console_log_queue,s_Initiating_Grim_00474bd4);
  console_flush_log(&console_log_queue,filename_01);
  DAT_004852e1 = 0x75;
  DAT_004852eb = 0x75;
  DAT_004852dd = 0x65;
  DAT_004852de = 0x74;
  DAT_004852df = 0x50;
  DAT_004852e0 = 0x6c;
  DAT_004852e2 = 0x67;
  DAT_004852e3 = 0x69;
  DAT_004852e4 = 0x6e;
  DAT_004852e5 = 0x73;
  DAT_004852e6 = 0x5c;
  DAT_004852e7 = 0x44;
  DAT_004852e8 = 0x65;
  DAT_004852e9 = 0x66;
  DAT_004852ea = 0x61;
  DAT_004852ec = 0x6c;
  DAT_004852ed = 0x74;
  DAT_004852ee = 0x5c;
  pcVar5 = extraout_EDX;
  if (grim_interface_ptr == (IGrim2D *)0x0) {
    console_printf(&console_log_queue,s____DEV_dll_not_found__trying_to_f_00474ba4);
    grim_interface_ptr = (IGrim2D *)grim_load_interface(s_grim_dll_00474b98);
    pcVar5 = extraout_EDX_00;
  }
  console_flush_log(&console_log_queue,pcVar5);
  if (grim_interface_ptr == grim_interface_ptr + 1) {
    console_printf(&console_log_queue,PTR_DAT_00473a14);
    console_printf(&console_log_queue,PTR_secret_hint_secret_weapons_00473a18);
    console_printf(&console_log_queue,PTR_secret_hint_redistr_build_00473a10);
    console_printf(&console_log_queue,PTR_secret_hint_not_meant_to_see_00473a1c);
    console_printf(&console_log_queue,PTR_secret_hint_alienzookeeper_00473a20);
    console_printf(&console_log_queue,PTR_secret_hint_secret_path_00473a24);
    console_printf(&console_log_queue,PTR_secret_hint_magic_paint_00473a28);
    console_printf(&console_log_queue,PTR_secret_hint_haxx0r_00473a34);
    console_printf(&console_log_queue,PTR_DAT_00473a2c);
  }
  if (grim_interface_ptr == (IGrim2D *)0x0) {
    MessageBoxA((HWND)0x0,s_Grim_dll_is_corrupted_or_missing_00474b10,&DAT_00474b90,0);
    return 0;
  }
  console_printf(&console_log_queue,s____interface_created_00474af8);
  console_printf(&console_log_queue,s____registering_core_variables_00474ad8);
  register_core_cvars();
  if (DAT_00473a64 != 0x7b) {
    grim_interface_ptr = (IGrim2D *)0x0;
  }
  console_flush_log(&console_log_queue,filename_02);
  console_printf(&console_log_queue,s____loading_config_pre_sets_00474abc);
  uVar2 = 0x42c954;
  config_load_presets();
  game_load_status();
  game_sequence_load();
  console_flush_log(&console_log_queue,filename_03);
  console_printf(&console_log_queue,s____invoking_grim_config_00474aa0);
  console_flush_log(&console_log_queue,filename_04);
  iVar3 = (*grim_interface_ptr->vtable->grim_apply_config)();
  grim_config_invoked = 1;
  if ((char)iVar3 == '\0') {
    config_sync_from_grim();
    grim_config_invoked = 0;
    (*grim_interface_ptr->vtable->grim_release)();
    return 0;
  }
  config_sync_from_grim();
  grim_config_invoked = 0;
  config_load_presets();
  console_printf(&console_log_queue,s____setting_system_states_00474a84);
  console_flush_log(&console_log_queue,filename_05);
  pcVar5 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_41c,0x54);
  terrain_texture_failed = *pcVar5;
  puVar6 = (uchar *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_41c,0x53);
  crt_fmode = *puVar6;
  pfVar7 = (float *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_41c,0x59);
  config_blob.reserved0._112_4_ = *pfVar7;
  if (((((float)config_blob.reserved0._112_4_ != 0.5) &&
       ((float)config_blob.reserved0._112_4_ != 1.0)) &&
      ((float)config_blob.reserved0._112_4_ != 2.0)) &&
     ((float)config_blob.reserved0._112_4_ != 4.0)) {
    config_blob.reserved0[0x70] = '\0';
    config_blob.reserved0[0x71] = '\0';
    config_blob.reserved0[0x72] = 0x80;
    config_blob.reserved0[0x73] = '?';
  }
  config_blob.reserved0[0] = crt_fmode;
  pcVar5 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_41c,8);
  config_blob.windowed._0_1_ = *pcVar5;
  if (terrain_texture_failed == '\0') {
    pcVar5 = s____using_PRIMARY_backend_00474a44;
  }
  else {
    pcVar5 = s____using_SAFEMODE_fallback_backe_00474a60;
  }
  console_printf(&console_log_queue,pcVar5);
  pcVar5 = extraout_EDX_01;
  if (grim_interface_ptr == (IGrim2D *)0x0) {
    console_printf(&console_log_queue,s____using_DEVELOPER_backend_00474a28);
    pcVar5 = extraout_EDX_02;
  }
  console_flush_log(&console_log_queue,pcVar5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x2d,uVar2);
  (*grim_interface_ptr->vtable->grim_set_config_var)(5,in_stack_fffffbac);
  (*grim_interface_ptr->vtable->grim_set_config_var)(6,in_stack_fffffb98);
  (*grim_interface_ptr->vtable->grim_set_config_var)
            (0x42,CONCAT31((int3)((uint)in_stack_fffffb84 >> 8),1));
  console_printf(&console_log_queue,s____setting_system_states_00474a84);
  (*grim_interface_ptr->vtable->grim_set_config_var)(7,in_stack_fffffb70);
  piVar8 = (int *)(*grim_interface_ptr->vtable->grim_get_config_var)((uint *)&stack0xfffffb80,0x29);
  config_blob.screen_width = *piVar8;
  piVar8 = (int *)(*grim_interface_ptr->vtable->grim_get_config_var)((uint *)&stack0xfffffb80,0x2a);
  config_blob.screen_height = *piVar8;
  if ((char)config_blob.windowed == '\0') {
    pcVar5 = s____selected_fullscreen_mode__dx__004749d0;
    console_printf(&console_log_queue,s____selected_fullscreen_mode__dx__004749d0);
  }
  else {
    pcVar5 = (char *)&console_log_queue;
    console_printf(&console_log_queue,s____selected_windowed_mode__windo_004749f8);
  }
  screen_mode_setting = config_blob.reserved0[1];
  (*grim_interface_ptr->vtable->grim_set_config_var)(0xb,CONCAT31((int3)((uint)pcVar5 >> 8),1));
  console_printf(&console_log_queue,s____using_keyboard_004749bc);
  (*grim_interface_ptr->vtable->grim_set_config_var)
            (0xc,CONCAT31((int3)((uint)in_stack_fffffb48 >> 8),1));
  console_printf(&console_log_queue,s____using_mouse_004749ac);
  (*grim_interface_ptr->vtable->grim_set_config_var)
            (0xe,CONCAT31((int3)((uint)in_stack_fffffb34 >> 8),1));
  console_printf(&console_log_queue,s____using_joystick_00474998);
  console_printf(&console_log_queue,s____initiating_Grim_system_0047497c);
  iVar3 = (*grim_interface_ptr->vtable->grim_init_system)();
  if ((char)iVar3 == '\0') {
    console_printf(&console_log_queue,s_Critical_failure__00474968);
    uType = 0;
    lpCaption = s_Crimsonland__00474958;
    pcVar5 = (*grim_interface_ptr->vtable->grim_get_error_text)();
    MessageBoxA((HWND)0x0,pcVar5,lpCaption,uType);
    (*grim_interface_ptr->vtable->grim_release)();
    return 0;
  }
  console_exec_line(&console_log_queue,s_exec_autoexec_txt_00474944);
  (*grim_interface_ptr->vtable->grim_set_config_var)
            (0x12,CONCAT31((int3)((uint)in_stack_fffffb20 >> 8),1));
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f800000);
  screen_width_f = (float)config_blob.screen_width;
  screen_height_f = (float)config_blob.screen_height;
  uStack_52c = 0x42cd8d;
  pvVar9 = console_register_cvar(&console_log_queue,s_v_width_00474938,&DAT_00474940);
  *(float *)((int)pvVar9 + 0xc) = (float)config_blob.screen_width;
  uStack_52c = 0x42cdaa;
  pvVar9 = console_register_cvar(&console_log_queue,s_v_height_00474928,&DAT_00474934);
  *(float *)((int)pvVar9 + 0xc) = (float)config_blob.screen_height;
  init_audio_and_terrain();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x10,in_stack_fffffad0);
  console_printf(&console_log_queue,s_Set_resource_paq_to__crimson_paq_004748f8);
  texture_get_or_load(s_backplasma_0047296c,s_load_backplasma_jaz_004748e4);
  texture_get_or_load(s_mockup_00472964,s_load_mockup_jaz_004748d4);
  texture_get_or_load(s_logo_esrb_004746d8,s_load_esrb_mature_jaz_004748bc);
  texture_get_or_load(s_loading_004746e4,s_load_loading_jaz_004748a8);
  texture_get_or_load(s_cl_logo_00471f70,s_load_logo_crimsonland_tga_0047488c);
  uVar16 = 0;
  (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x36,CONCAT31((int3)((uint)uVar16 >> 8),1));
  key = (HKEY)0x0;
  uVar16 = 0;
  (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x36,CONCAT31((int3)((uint)uVar16 >> 8),1));
  (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,1.0);
  uVar2 = key_char_buffer_size;
  key_char_count = 0;
  puVar14 = &key_char_buffer;
  for (uVar12 = key_char_buffer_size >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  for (uVar12 = uVar2 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined1 *)puVar14 = 0;
    puVar14 = (undefined4 *)((int)puVar14 + 1);
  }
  (*grim_interface_ptr->vtable->grim_set_key_char_buffer)
            ((uchar *)&key_char_buffer,(int *)&key_char_count,uVar2);
  config_sync_from_grim();
  piVar13 = &player_state_table.input.move_key_backward;
  piVar8 = config_blob.keybinds_p1 + 0xc;
  do {
    piVar10 = piVar8 + 0x10;
    ((player_input_t *)(piVar13 + -1))->move_key_forward = piVar8[-0xc];
    *piVar13 = piVar8[-0xb];
    piVar13[1] = piVar8[-10];
    piVar13[2] = piVar8[-9];
    piVar13[3] = piVar8[-8];
    piVar13[4] = piVar8[-7];
    piVar13[5] = piVar8[-6];
    piVar13[6] = piVar8[-5];
    piVar13[7] = piVar8[-4];
    piVar13[9] = piVar8[-3];
    piVar13[8] = piVar8[-2];
    piVar13[0xb] = piVar8[-1];
    piVar13[10] = *piVar8;
    piVar13 = piVar13 + 0xd8;
    piVar8 = piVar10;
  } while ((int)piVar10 < 0x4805c0);
  (*grim_interface_ptr->vtable->grim_apply_settings)();
  LVar11 = RegCreateKeyExA((HKEY)0x80000001,s_Software_10tons_entertainment_Cr_00474604,0,(LPSTR)0x0
                           ,0,0xf003f,(LPSECURITY_ATTRIBUTES)0x0,(PHKEY)&stack0xfffffab0,
                           (LPDWORD)0x0);
  if (LVar11 == 0) {
    reg_write_dword((HKEY)key,s_timePlayed_004745f8,gameplay_elapsed_ms);
    RegCloseKey(key);
  }
  else {
    console_printf(&console_log_queue,s_Kameli_was_NOT_hairy__00474874);
  }
  game_save_status();
  console_printf(&console_log_queue,s_Leaving_Crimsonland___0047485c);
  pcVar5 = extraout_EDX_03;
  if (allocated_memory_ptr != (void *)0x0) {
    crt_free(allocated_memory_ptr);
    pcVar5 = extraout_EDX_04;
  }
  console_flush_log(&console_log_queue,pcVar5);
  audio_shutdown_all();
  console_printf(&console_log_queue,s_Shutdown_Grim___00474848);
  (*grim_interface_ptr->vtable->grim_shutdown)();
  console_flush_log(&console_log_queue,filename_06);
  (*grim_interface_ptr->vtable->grim_release)();
  console_printf(&console_log_queue,s_Waving_the_Grim_Reaper_goodbye___00474824);
  console_flush_log(&console_log_queue,filename_07);
  pcVar5 = extraout_EDX_05;
  if (((browser_open_result == 0) && (browser_open_pending != '\0')) && (browser_url_ptr != (LPCCH)0x0)) {
    Sleep(200);
    uStack_52c = uStack_52c & 0xffff0000;
    puVar14 = (undefined4 *)((int)&uStack_52c + 2);
    for (iVar3 = 0xff; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar14 = 0;
      puVar14 = puVar14 + 1;
    }
    *(undefined2 *)puVar14 = 0;
    uVar2 = 0xffffffff;
    pCVar15 = browser_url_ptr;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pCVar15;
      pCVar15 = pCVar15 + 1;
    } while (cVar1 != '\0');
    MultiByteToWideChar(0,1,browser_url_ptr,~uVar2 - 1,(LPWSTR)&uStack_52c,0x1ff);
    HVar4 = HlinkNavigateString((IUnknown *)0x0,(LPCWSTR)&uStack_52c);
    pcVar5 = extraout_EDX_06;
    if (HVar4 < 0) {
      console_printf(&console_log_queue,s_Failed_to_open_browser_at___s___00474800,browser_url_ptr);
      pcVar5 = extraout_EDX_07;
    }
    browser_open_pending = '\0';
  }
  console_flush_log(&console_log_queue,pcVar5);
  return 0;
}


