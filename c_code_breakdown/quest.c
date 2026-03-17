/* quest_mode_update @ 004070e0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* quest mode update: spawn timeline, stage completion, and transitions */

void quest_mode_update(void)

{
  uint uVar1;
  int iVar2;
  
  if ((console_open_flag != '\0') || (render_pass_mode == '\0')) goto LAB_00407129;
  uVar1 = creatures_none_active();
  if ((char)uVar1 == '\0') {
LAB_00407104:
    quest_spawn_timeline = quest_spawn_timeline + frame_dt_ms;
  }
  else {
    iVar2 = quest_spawn_table_empty();
    if ((char)iVar2 == '\0') goto LAB_00407104;
  }
  quest_elapsed_timer_ms = quest_elapsed_timer_ms + frame_dt_ms;
LAB_00407129:
  quest_spawn_timeline_update();
  if (demo_mode_active == '\0') {
    uVar1 = creatures_none_active();
    if ((char)uVar1 != '\0') {
      iVar2 = quest_spawn_table_empty();
      if ((char)iVar2 != '\0') {
        bonus_reflex_boost_timer = 0;
        if (quest_transition_timer_ms < 0) {
          sfx_mute_all(music_track_extra_0);
          iVar2 = quest_stage_minor + quest_stage_major * 10;
          game_status_blob.quest_play_counts[iVar2 + 0x28] =
               game_status_blob.quest_play_counts[iVar2 + 0x28] + 1;
          quest_transition_timer_ms = frame_dt_ms;
          return;
        }
        if ((800 < quest_transition_timer_ms) && (quest_transition_timer_ms < 0x353)) {
          sfx_play(sfx_questhit);
          quest_transition_timer_ms = frame_dt_ms + 0x353;
          return;
        }
        if ((2000 < quest_transition_timer_ms) && (quest_transition_timer_ms < 0x803)) {
          quest_transition_timer_ms = 0x803;
          sfx_play_exclusive(music_track_crimsonquest_id);
          quest_transition_timer_ms = quest_transition_timer_ms + frame_dt_ms;
          sfx_volume_table[music_track_crimsonquest_id] = 0.0;
          return;
        }
        if (0x9c4 < quest_transition_timer_ms) {
          iVar2 = quest_stage_minor + -10 + quest_stage_major * 10;
          if (quest_unlock_index < iVar2) {
            quest_unlock_index = iVar2;
          }
          if ((config_blob.hardcore != '\0') && (quest_unlock_index_full < iVar2)) {
            quest_unlock_index_full = iVar2;
          }
          game_save_status();
          game_state_pending = 8;
          ui_transition_direction = 0;
          (*grim_interface_ptr->vtable->grim_flush_input)();
          console_input_poll();
          highscore_active_record.score_xp = 0;
        }
        quest_transition_timer_ms = quest_transition_timer_ms + frame_dt_ms;
      }
    }
  }
  return;
}



/* quest_failed_screen_update @ 004107e0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* quest failure screen: retry options and navigation */

void quest_failed_screen_update(void)

{
  float fVar1;
  int iVar2;
  int x;
  IGrim2D_vtbl *pIVar3;
  longlong lVar4;
  int y;
  int w;
  char *text;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  bonus_reflex_boost_timer = 0;
  if ((((game_state_id == 0xc) && (game_state_pending == 0x19)) && (ui_transition_direction != '\0')
      ) && (iVar2 = sfx_is_unmuted(music_track_shortie_monk_id), (char)iVar2 == '\0')) {
    sfx_play_exclusive(music_track_shortie_monk_id);
  }
  gameplay_render_world();
  ui_elements_update_and_render();
  perk_prompt_update_and_render();
  local_4 = quest_results_pos_y + quest_panel_offset_x;
  local_10 = quest_panel_offset_y + quest_results_pos_x + 180.0;
  fVar1 = local_4 + 40.0;
  w = 0x40;
  local_18 = (quest_results_offset_y + local_10 + 44.0) - 10.0;
  y = 0x100;
  iVar2 = crt_lowio_handles;
  local_14 = fVar1;
  local_c = fVar1;
  local_8 = local_18;
  lVar4 = __ftol();
  x = (int)lVar4;
  lVar4 = __ftol();
  ui_draw_textured_quad((int)lVar4,x,y,w,iVar2);
  if (ui_screen_phase == -1) {
    highscore_load_table();
    highscore_rank_result = highscore_rank_index();
    highscore_active_record.game_mode_id = config_blob.reserved0[0x18];
    (*grim_interface_ptr->vtable->grim_flush_input)();
    console_input_poll();
    (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
    ui_screen_phase = 0;
  }
  else if (ui_screen_phase != 0) goto LAB_00410cc1;
  local_18 = local_8 + 30.0;
  local_14 = fVar1 + 70.0 + 16.0;
  switch(quest_fail_retry_count) {
  default:
    text = s_Quest_failed__try_again__004731bc;
    pIVar3 = grim_interface_ptr->vtable;
    break;
  case 1:
    text = s_You_didn_t_make_it__do_try_again_00473244;
    pIVar3 = grim_interface_ptr->vtable;
    break;
  case 2:
    text = s_Third_time_no_good__00473230;
    pIVar3 = grim_interface_ptr->vtable;
    break;
  case 3:
    text = s_No_luck_this_time__have_another_g_0047320c;
    pIVar3 = grim_interface_ptr->vtable;
    break;
  case 4:
    text = s_Persistence_will_be_rewared__004731ec;
    pIVar3 = grim_interface_ptr->vtable;
    break;
  case 5:
    text = s_Try_one_more_time__004731d8;
    pIVar3 = grim_interface_ptr->vtable;
  }
  (*pIVar3->grim_draw_text_small)(local_18,local_14,text);
  local_14 = local_14 + 16.0;
  local_18 = local_18 + 6.0;
  local_10 = local_18 + 4.0;
  local_c = local_14 + 10.0;
  ui_text_input_render(&local_10,6.652423e-39,1.0);
  local_14 = local_14 + 98.0;
  local_18 = local_18 + 16.0;
  if ((ui_fail_screen_init_flags & 1) == 0) {
    ui_fail_screen_init_flags = ui_fail_screen_init_flags | 1;
    DAT_00482686 = 1;
    DAT_00482695 = 0;
    DAT_00482694 = 0;
    _DAT_00482690 = 0x3f800000;
    _DAT_0048268c = 0;
    _DAT_00482680 = (char *)0x0;
    DAT_00482684 = 0;
    ui_fail_retry_clicked = '\0';
    _DAT_00482688 = 0;
    crt_atexit(&DAT_00410d10);
  }
  _DAT_00482680 = s_Play_Again_00473164;
  if ((ui_fail_screen_init_flags & 2) == 0) {
    ui_fail_screen_init_flags = ui_fail_screen_init_flags | 2;
    DAT_0048269e = 1;
    DAT_004826ad = 0;
    ui_fail_button_focus_idx = 0;
    ui_fail_button_alpha = 0x3f800000;
    ui_fail_button_counter = 0;
    ui_fail_play_another_label = (char *)0x0;
    ui_fail_button_padding_a = 0;
    ui_fail_play_another_clicked = '\0';
    ui_fail_button_timer = 0;
    crt_atexit(&DAT_00410d00);
  }
  ui_fail_play_another_label = s_Play_Another;
  if ((ui_fail_screen_init_flags & 4) == 0) {
    ui_fail_screen_init_flags = ui_fail_screen_init_flags | 4;
    ui_fail_menu_button_enabled = 1;
    ui_fail_menu_button_visible = 0;
    ui_fail_menu_button_focus = 0;
    ui_fail_menu_button_alpha = 0x3f800000;
    ui_fail_menu_button_hover = 0;
    ui_fail_main_menu_label = (char *)0x0;
    ui_fail_menu_button_padding_a = 0;
    ui_fail_main_menu_clicked = '\0';
    ui_fail_menu_button_timer = 0;
    crt_atexit(&DAT_00410cf0);
  }
  ui_fail_main_menu_label = s_main_menu;
  ui_button_update(&local_18,(ui_button_t *)&ui_fail_retry_button);
  local_14 = local_14 + 32.0;
  ui_button_update(&local_18,(ui_button_t *)&ui_fail_play_another_button);
  local_14 = local_14 + 32.0;
  ui_button_update(&local_18,(ui_button_t *)&ui_fail_main_menu_button);
  local_14 = local_14 + 32.0;
  if (ui_fail_retry_clicked != '\0') {
    quest_fail_retry_count = quest_fail_retry_count + 1;
    ui_transition_direction = '\0';
    game_state_pending = 9;
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    render_pass_mode = 0;
  }
  if (ui_fail_play_another_clicked != '\0') {
    quest_fail_retry_count = 0;
    ui_transition_direction = '\0';
    game_state_pending = 0xb;
    ui_sign_crimson_update_disabled = 0;
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    sfx_play_exclusive(music_track_crimson_theme_id);
  }
  if (ui_fail_main_menu_clicked != '\0') {
    quest_fail_retry_count = 0;
    sfx_mute_all(music_track_extra_0);
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_crimson_theme_id);
    ui_transition_direction = '\0';
    game_state_pending = 0;
    ui_sign_crimson_update_disabled = 0;
  }
LAB_00410cc1:
  ui_cursor_render();
  return;
}



/* quest_results_screen_update @ 00410d20 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* quest/campaign results screen: final time, perk bonus, high score entry, and buttons */

void quest_results_screen_update(void)

{
  char cVar1;
  IGrim2D_vtbl *pIVar2;
  float fVar3;
  float a;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  highscore_record_t *phVar10;
  undefined4 *puVar11;
  char *pcVar12;
  highscore_record_t *phVar13;
  longlong lVar14;
  int y;
  int w;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  bonus_reflex_boost_timer = 0;
  quest_fail_retry_count = 0;
  if ((((game_state_id == 8) && (game_state_pending == 0x19)) && (ui_transition_direction != '\0'))
     && (iVar4 = sfx_is_unmuted(music_track_shortie_monk_id), (char)iVar4 == '\0')) {
    sfx_play_exclusive(music_track_crimsonquest_id);
  }
  gameplay_render_world();
  ui_elements_update_and_render();
  if (((byte)quest_results_screen_flags & 1) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 1;
    quest_results_button_active = 1;
    quest_results_unlock_shown = 0;
    quest_results_anim_done = 0;
    quest_results_alpha = 1.0;
    quest_results_phase = 0;
    quest_results_callback = (undefined *)0x0;
    quest_results_slot_id = 0;
    quest_results_slot_active = '\0';
    quest_results_timer = 0;
    crt_atexit(&DAT_00412070);
  }
  if (((byte)quest_results_screen_flags & 2) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 2;
    quest_back_button_alpha = 1.0;
    quest_back_button_text = &s_quest_back_button_default;
    quest_back_button_state = 0;
    quest_back_button_width = 0x18;
    quest_back_button_height = 0x60;
    crt_atexit(&DAT_00412060);
  }
  local_4 = quest_results_pos_y + quest_panel_offset_x;
  w = 0x40;
  y = 0x100;
  local_18 = quest_panel_offset_y + quest_results_pos_x + 180.0;
  local_14 = local_4 + 40.0;
  local_10 = local_18 + quest_results_offset_y + 40.0;
  iVar4 = texture_quest_panel_id;
  local_c = local_14;
  lVar14 = __ftol();
  iVar8 = (int)lVar14;
  lVar14 = __ftol();
  ui_draw_textured_quad((int)lVar14,iVar8,y,w,iVar4);
  fVar3 = local_c + 56.0;
  local_8 = local_10;
  local_c = fVar3;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  if (((game_state_prev == 0xe) && (ui_transition_direction != '\0')) &&
     (highscore_return_latch != '\0')) {
    highscore_return_latch = '\0';
    ui_screen_phase = 2;
  }
  else {
    if (ui_screen_phase == -2) {
      iVar4 = quest_stage_minor + -0xb + quest_stage_major * 10;
      quest_unlock_weapon_id = (&quest_selected_meta)[iVar4].unlock_weapon_id;
      quest_unlock_perk_id = (&quest_selected_meta)[iVar4].unlock_perk_id;
      lVar14 = __ftol();
      local_18 = (float)lVar14;
      player_state_table.health = (float)(int)local_18;
      lVar14 = __ftol();
      iVar4 = (int)lVar14;
      if (config_blob.reserved0._20_4_ == 2) {
        quest_results_damage_total = iVar4;
        lVar14 = __ftol();
        iVar4 = iVar4 + (int)lVar14;
      }
      quest_results_final_score = (quest_spawn_timeline + perk_pending_count * -1000) - iVar4;
      highscore_active_record.survival_elapsed_ms = quest_results_final_score;
      if (quest_results_final_score == 0) {
        highscore_active_record.survival_elapsed_ms = 1;
      }
      quest_results_anim_timer = 0;
      quest_results_damage_total = iVar4;
      highscore_record_init();
      quest_results_animation_delay = 700;
      ui_screen_phase = ui_screen_phase + 1;
      quest_results_time_display = 0;
      quest_results_damage_display = 0;
      quest_results_perks_display = 0;
      quest_results_step = 0;
      quest_results_score_display = 0;
    }
    if (ui_screen_phase == -1) {
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
      local_c = local_c + 40.0;
      quest_results_animation_delay = quest_results_animation_delay - frame_dt_ms;
      if (quest_results_animation_delay < 1) {
        if (quest_results_step < 3) {
          if (quest_results_step == 0) {
            quest_results_time_display = quest_results_time_display + 2000;
            quest_results_animation_delay = 0x28;
            sfx_play(sfx_ui_clink_01);
            quest_results_score_display = quest_results_time_display;
            if (quest_spawn_timeline <= (int)quest_results_time_display) {
              quest_results_step = quest_results_step + 1;
              quest_results_time_display = quest_spawn_timeline;
              quest_results_score_display = quest_results_time_display;
            }
          }
          else if (quest_results_step == 1) {
            quest_results_damage_display = quest_results_damage_display + 1000;
            quest_results_animation_delay = 0x96;
            sfx_play(sfx_ui_clink_01);
            quest_results_score_display = quest_results_score_display - 1000;
            if (quest_results_damage_total <= quest_results_damage_display) {
              quest_results_damage_display = quest_results_damage_total;
              quest_results_step = quest_results_step + 1;
            }
          }
          else if (quest_results_step == 2) {
            quest_results_perks_display = quest_results_perks_display + 1;
            quest_results_animation_delay = 300;
            sfx_play(sfx_ui_clink_01);
            quest_results_score_display = quest_results_score_display - 1000;
            if (perk_pending_count <= quest_results_perks_display) {
              quest_results_perks_display = perk_pending_count;
              quest_results_step = quest_results_step + 1;
              quest_results_animation_delay = 1000;
              highscore_active_record.survival_elapsed_ms = quest_results_final_score;
              quest_results_score_display = quest_results_final_score;
            }
          }
        }
        else if (quest_results_step == 3) {
          quest_results_animation_delay = 0x32;
          quest_results_anim_timer = quest_results_anim_timer + 1;
        }
      }
      local_18 = 1.0 - (float)quest_results_anim_timer * 0.1;
      if (0.0 <= local_18) {
        if (1.0 < local_18) {
          local_18 = 1.0;
        }
      }
      else {
        local_18 = 0.0;
      }
      fVar3 = local_18;
      local_10 = local_10 + 32.0;
      local_c = local_c + 20.0;
      if (quest_results_step == 0) {
        (*grim_interface_ptr->vtable->grim_set_color)(0.1,0.8,0.1,local_18);
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,local_18 * 0.4);
      }
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10,local_c,s_Base_Time__004732f4);
      pIVar2 = grim_interface_ptr->vtable;
      iVar4 = format_time_seconds((int)quest_results_time_display / 1000);
      (*pIVar2->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10 + 132.0,local_c,&s_fmt_percent_s,iVar4);
      local_c = local_c + 20.0;
      if (quest_results_step == 1) {
        (*grim_interface_ptr->vtable->grim_set_color)(0.1,0.8,0.1,fVar3);
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,local_18 * 0.4);
      }
      if (quest_results_step < 1) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,local_18 * 0.2);
      }
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10,local_c,s_Life_Bonus__004732e8);
      pIVar2 = grim_interface_ptr->vtable;
      iVar4 = format_time_seconds(quest_results_damage_display / 1000);
      (*pIVar2->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10 + 132.0,local_c,&s_fmt_percent_s,iVar4);
      local_c = local_c + 20.0;
      if (quest_results_step == 2) {
        (*grim_interface_ptr->vtable->grim_set_color)(0.1,0.8,0.1,fVar3);
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,local_18 * 0.4);
      }
      if (quest_results_step < 2) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,local_18 * 0.2);
      }
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10,local_c,s_Unpicked_Perk_Bonus__004732d0);
      pIVar2 = grim_interface_ptr->vtable;
      iVar4 = format_time_seconds(quest_results_perks_display);
      (*pIVar2->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10 + 132.0,local_c,&s_fmt_percent_s,iVar4);
      local_c = local_c + 20.0;
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar3);
      local_18 = local_10 - 4.0;
      local_14 = local_c + 1.0;
      (*grim_interface_ptr->vtable->grim_draw_rect_outline)(&local_18,168.0,1.0);
      local_c = local_c + 8.0;
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10,local_c,s_Final_Time__004732c4);
      pIVar2 = grim_interface_ptr->vtable;
      iVar4 = format_time_seconds((int)quest_results_score_display / 1000);
      (*pIVar2->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10 + 132.0,local_c,&s_fmt_percent_s,iVar4);
      local_c = local_c + 20.0;
      (*grim_interface_ptr->vtable->grim_flush_input)();
      (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
      if ((ui_screen_phase == -1) &&
         ((iVar4 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x39), (char)iVar4 != '\0' ||
          (iVar4 = input_primary_just_pressed(), (char)iVar4 != '\0')))) {
        ui_screen_phase = ui_screen_phase + 1;
        perk_prompt_update_and_render();
        ui_cursor_render();
        return;
      }
      if (10 < quest_results_anim_timer) {
        quest_results_anim_timer = 0;
        ui_screen_phase = ui_screen_phase + 1;
        perk_prompt_update_and_render();
        ui_cursor_render();
        return;
      }
      goto LAB_00412007;
    }
    if (ui_screen_phase == 0) {
      highscore_load_table();
      highscore_rank_result = highscore_rank_index();
      (*grim_interface_ptr->vtable->grim_flush_input)();
      (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
      if (99 < highscore_rank_result) {
        quest_back_button_state = 0;
        quest_back_button_width = 0;
        quest_back_button_text = &s_quest_back_button_default;
        ui_screen_phase = 2;
        perk_prompt_update_and_render();
        ui_cursor_render();
        return;
      }
      uVar6 = 0xffffffff;
      quest_back_button_width = 0x14;
      phVar13 = &highscore_active_record;
      do {
        phVar10 = phVar13;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        phVar10 = (highscore_record_t *)(phVar13->player_name + 1);
        pcVar5 = phVar13->player_name;
        phVar13 = phVar10;
      } while (*pcVar5 != '\0');
      uVar6 = ~uVar6;
      quest_back_button_text = &s_quest_back_button_default;
      ui_screen_phase = 1;
      puVar9 = (undefined4 *)((int)phVar10 - uVar6);
      puVar11 = (undefined4 *)&s_quest_back_button_default;
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *puVar11 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar11 = puVar11 + 1;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar11 = *(undefined1 *)puVar9;
        puVar9 = (undefined4 *)((int)puVar9 + 1);
        puVar11 = (undefined4 *)((int)puVar11 + 1);
      }
      uVar6 = 0xffffffff;
      phVar13 = &highscore_active_record;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pcVar5 = phVar13->player_name;
        phVar13 = (highscore_record_t *)(phVar13->player_name + 1);
      } while (*pcVar5 != '\0');
      quest_back_button_state = ~uVar6 - 1;
      perk_prompt_update_and_render();
      ui_cursor_render();
      return;
    }
    if (ui_screen_phase == 1) {
      if (quest_results_anim_timer < 500) {
        quest_results_anim_timer = quest_results_anim_timer + frame_dt_ms;
      }
      else {
        quest_results_anim_timer = 500;
      }
      ui_text_alpha = (float)quest_results_anim_timer * 0.002;
      local_c = local_c + 22.0;
      local_18 = ui_text_alpha;
      (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_10 + 42.0,local_c,s_State_your_name_trooper__004732a8);
      local_c = local_c + 32.0;
      ui_text_alpha = 0.7;
      local_8 = local_10 + 170.0;
      quest_back_button_height = 0xa6;
      quest_back_button_alpha = local_18;
      quest_results_callback = &DAT_0047318c;
      quest_results_alpha = local_18;
      local_4 = local_c - 8.0;
      ui_button_update(&local_8,(ui_button_t *)&DAT_00482520);
      iVar4 = ui_text_input_update(&local_10,(int *)&DAT_004826e8);
      if (((char)iVar4 != '\0') || (quest_results_slot_active != '\0')) {
        uVar6 = 0xffffffff;
        iVar4 = 0;
        pcVar5 = &s_quest_back_button_default;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        iVar8 = ~uVar6 - 1;
        if (0 < iVar8) {
          if (0 < iVar8) {
            do {
              if ((&s_quest_back_button_default)[iVar4] != ' ') break;
              iVar4 = iVar4 + 1;
            } while (iVar4 < iVar8);
          }
          if ((&s_quest_back_button_default)[iVar4] != '\0') {
            ui_screen_phase = 2;
            sfx_play(sfx_ui_typeenter);
            iVar4 = quest_back_button_state;
            uVar6 = 0xffffffff;
            pcVar5 = &s_quest_back_button_default;
            do {
              pcVar12 = pcVar5;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar12 = pcVar5 + 1;
              cVar1 = *pcVar5;
              pcVar5 = pcVar12;
            } while (cVar1 != '\0');
            uVar6 = ~uVar6;
            player_name_length = quest_back_button_state;
            pcVar5 = pcVar12 + -uVar6;
            phVar13 = &highscore_active_record;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)phVar13->player_name = *(undefined4 *)pcVar5;
              pcVar5 = pcVar5 + 4;
              phVar13 = (highscore_record_t *)(phVar13->player_name + 4);
            }
            quest_back_button_state = 0;
            quest_back_button_width = 0;
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              phVar13->player_name[0] = *pcVar5;
              pcVar5 = pcVar5 + 1;
              phVar13 = (highscore_record_t *)(phVar13->player_name + 1);
            }
            highscore_active_record.player_name[iVar4] = '\0';
            quest_back_button_text = &s_quest_back_button_default;
            highscore_save_active();
            highscore_load_table();
            goto LAB_00411906;
          }
        }
        quest_results_slot_active = '\0';
        sfx_play(sfx_shock_hit_01);
      }
LAB_00411906:
      local_c = local_c + 30.0;
      (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
      local_8 = local_10 + 26.0;
      local_4 = local_c + 16.0;
      ui_text_input_render(&local_8,6.652423e-39,local_18);
      perk_prompt_update_and_render();
      ui_cursor_render();
      return;
    }
    if (ui_screen_phase != 2) goto LAB_00412007;
  }
  if (quest_results_anim_timer < 500) {
    quest_results_anim_timer = quest_results_anim_timer + frame_dt_ms;
  }
  else {
    quest_results_anim_timer = 500;
  }
  a = (float)quest_results_anim_timer * 0.002;
  local_10 = local_8 + 30.0;
  local_18 = a;
  local_c = fVar3;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
  if (99 < highscore_rank_result) {
    local_c = local_c + 6.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_10 + 8.0,local_c,s_Score_too_low_for_top_d__00473170,100);
    local_c = local_c + 6.0;
  }
  local_8 = local_10;
  local_4 = local_c + 16.0;
  ui_text_input_render(&local_8,6.652423e-39,a);
  local_c = local_c + 78.0 + 6.0;
  if (quest_unlock_weapon_id != 0) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_10,local_c + 1.0,s_Weapon_unlocked__00473294);
    local_c = local_c + 14.0;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.9);
    pIVar2 = grim_interface_ptr->vtable;
    pcVar5 = weapon_table_entry((&quest_selected_meta)
                                [quest_stage_minor + -0xb + quest_stage_major * 10].
                                unlock_weapon_id);
    (*pIVar2->grim_draw_text_small_fmt)(grim_interface_ptr,local_10,local_c,&s_fmt_percent_s,pcVar5)
    ;
    local_c = local_c + 16.0;
  }
  if (quest_unlock_perk_id != perk_id_antiperk) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_10,local_c + 1.0,s_Perk_unlocked__00473284);
    local_c = local_c + 14.0;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.9);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_10,local_c,&s_fmt_percent_s,
               (&perk_meta_table)
               [(&quest_selected_meta)[quest_stage_minor + -0xb + quest_stage_major * 10].
                unlock_perk_id].name);
    local_c = local_c + 16.0;
  }
  if (((byte)quest_results_screen_flags & 4) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 4;
    DAT_004825c6 = 1;
    DAT_004825d5 = 0;
    DAT_004825d4 = 0;
    _DAT_004825d0 = 1.0;
    _DAT_004825cc = 0;
    ui_screen_state_flags = (char *)0x0;
    DAT_004825c4 = 0;
    highscore_btn_scores_b_en = '\0';
    _DAT_004825c8 = 0;
    crt_atexit(&DAT_00412050);
  }
  ui_screen_state_flags = s_Play_Next_00473278;
  if (((byte)quest_results_screen_flags & 8) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 8;
    DAT_0048260e = 1;
    DAT_0048261d = 0;
    DAT_0048261c = 0;
    _DAT_00482618 = 1.0;
    _DAT_00482614 = 0;
    _DAT_00482608 = (char *)0x0;
    DAT_0048260c = 0;
    highscore_btn_submit_b = '\0';
    _DAT_00482610 = 0;
    crt_atexit(&DAT_00412040);
  }
  _DAT_00482608 = s_Play_Again_00473164;
  if (((byte)quest_results_screen_flags & 0x10) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 0x10;
    DAT_0048266e = 1;
    DAT_0048267d = 0;
    DAT_0048267c = 0;
    _DAT_00482678 = 1.0;
    _DAT_00482674 = 0;
    highscore_btn_scores_label_b = (char *)0x0;
    DAT_0048266c = 0;
    highscore_btn_a_enabled = '\0';
    _DAT_00482670 = 0;
    crt_atexit(&DAT_00412030);
  }
  highscore_btn_scores_label_b = s_High_scores_00473158;
  if (((byte)quest_results_screen_flags & 0x20) == 0) {
    quest_results_screen_flags._0_1_ = (byte)quest_results_screen_flags | 0x20;
    DAT_004826b6 = 1;
    DAT_004826c5 = 0;
    DAT_004826c4 = 0;
    _DAT_004826c0 = 1.0;
    _DAT_004826bc = 0;
    highscore_btn_menu_label_b = (char *)0x0;
    DAT_004826b4 = 0;
    highscore_btn_b_enabled = '\0';
    _DAT_004826b8 = 0;
    crt_atexit(&DAT_00412020);
  }
  local_c = local_c + 6.0;
  highscore_btn_menu_label_b = s_main_menu;
  if ((quest_stage_major == 5) && (quest_stage_minor == 10)) {
    ui_screen_state_flags = s_Show_End_Note_00473268;
  }
  local_10 = local_10 + 20.0;
  _DAT_00482678 = local_18;
  _DAT_004825d0 = local_18;
  _DAT_00482618 = local_18;
  _DAT_004826c0 = local_18;
  ui_button_update(&local_10,(ui_button_t *)&DAT_004825c0);
  local_c = local_c + 32.0;
  ui_button_update(&local_10,(ui_button_t *)&DAT_00482608);
  local_c = local_c + 32.0;
  ui_button_update(&local_10,(ui_button_t *)&DAT_00482668);
  local_c = local_c + 32.0;
  ui_button_update(&local_10,(ui_button_t *)&DAT_004826b0);
  local_c = local_c + 32.0;
  if (highscore_btn_scores_b_en != '\0') {
    if ((quest_stage_major == 5) && (quest_stage_minor == 10)) {
      render_pass_mode = 0;
      game_state_pending = 0x15;
      ui_transition_direction = '\0';
    }
    else {
      sfx_mute_all(music_track_extra_0);
      sfx_mute_all(music_track_crimson_theme_id);
      sfx_mute_all(music_track_shortie_monk_id);
      quest_stage_minor = quest_stage_minor + 1;
      ui_transition_direction = '\0';
      game_state_pending = 9;
      render_pass_mode = 0;
    }
  }
  if (highscore_btn_submit_b != '\0') {
    ui_transition_direction = '\0';
    game_state_pending = 9;
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_mute_all(music_track_extra_0);
    render_pass_mode = 0;
  }
  if (highscore_btn_a_enabled != '\0') {
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
  if (highscore_btn_b_enabled != '\0') {
    sfx_mute_all(music_track_extra_0);
    sfx_mute_all(music_track_crimson_theme_id);
    sfx_mute_all(music_track_shortie_monk_id);
    sfx_play_exclusive(music_track_crimson_theme_id);
    ui_transition_direction = '\0';
    game_state_pending = 0;
    ui_sign_crimson_update_disabled = 0;
  }
LAB_00412007:
  perk_prompt_update_and_render();
  ui_cursor_render();
  return;
}



/* quest_meta_init @ 00412190 */

/* [binja] int32_t sub_412190() */

int quest_meta_init(void)

{
  int extraout_EAX;
  
  crt_ehvec_ctor(&quest_selected_meta,0x2c,0x32,&LAB_004121b0,&LAB_004121e0);
  return extraout_EAX;
}



/* quest_file_header_read @ 0041cdb0 */

/* WARNING: Removing unreachable block (ram,0x0041ce9f) */
/* WARNING: Removing unreachable block (ram,0x0041cea7) */
/* WARNING: Removing unreachable block (ram,0x0041cead) */
/* WARNING: Removing unreachable block (ram,0x0041cf52) */
/* WARNING: Removing unreachable block (ram,0x0041cf5a) */
/* WARNING: Enum "tagCALLCONV": Some values do not have unique names */

int quest_file_header_read(void)

{
  HRESULT HVar1;
  HRESULT HVar2;
  int iVar3;
  char cVar4;
  int *unaff_EDI;
  undefined4 uStack_74;
  int *piVar5;
  wchar_t *pwStack_64;
  wchar_t *pwStack_60;
  undefined2 uVar6;
  undefined4 uVar7;
  undefined4 lpWideCharStr;
  undefined2 uVar8;
  undefined4 local_3c;
  undefined4 uStack_38;
  _union_2156 local_34;
  undefined4 *puStack_24;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  HVar1 = CoInitialize((LPVOID)0x0);
  local_34._0_4_ = (wchar_t *)0x0;
  local_3c = (uint)(-1 < HVar1) << 0x18;
  HVar2 = CoCreateInstance((IID *)&DAT_0046f5c8,(LPUNKNOWN)0x0,1,(IID *)&DAT_0046f5b8,
                           (LPVOID *)&local_34);
  if (HVar2 < 0) {
    cVar4 = '\0';
  }
  else {
    local_10 = 0x10;
    local_c = 0x6f;
    local_8 = 0;
    local_4 = 0;
    uVar7 = local_34._0_4_;
    iVar3 = (**(code **)(*(int *)local_34._0_4_ + 0xc))();
    if (-1 < iVar3) {
      uStack_38 = (int *)0x0;
      iVar3 = (**(code **)(*(int *)local_3c + 0x10))();
      if (-1 < iVar3) {
        lpWideCharStr = &stack0xffffffc0;
        iVar3 = (**(code **)(iRam00000000 + 0x14))();
        if (iVar3 < 0) {
          cVar4 = (char)lpWideCharStr;
          pwStack_60 = (wchar_t *)0x41cf96;
          (**(code **)(*unaff_EDI + 8))();
          pwStack_60 = (wchar_t *)uVar7;
          pwStack_64 = (wchar_t *)0x41cfa0;
          (**(code **)(*(int *)pwStack_60 + 8))();
        }
        else {
          pwStack_60 = (wchar_t *)0x41ce7f;
          pwStack_64 = (wchar_t *)uVar7;
          VariantInit((VARIANTARG *)&local_34.field0);
          pwStack_60 = u_dwDirectXVersionMajor_00473900;
          uVar7 = pwStack_64;
          (**(code **)(*(int *)pwStack_64 + 0x20))();
          uVar8 = (undefined2)uVar7;
          VariantClear((VARIANTARG *)&stack0xffffffc0);
          piVar5 = (int *)&stack0xffffffc0;
          uVar7 = uStack_38;
          iVar3 = (**(code **)(*(int *)uStack_38 + 0x20))();
          uVar6 = (undefined2)uVar7;
          if (((-1 < iVar3) && (uVar8 == 0x13)) && (puStack_24 != (undefined4 *)0x0)) {
            *puStack_24 = unaff_EDI;
          }
          VariantClear((VARIANTARG *)&stack0xffffffb4);
          iVar3 = (**(code **)(*(int *)pwStack_64 + 0x20))
                            (pwStack_64,u_szDirectXVersionLetter_004738a4,&stack0xffffffb4);
          uStack_74 = uStack_38;
          if (((-1 < iVar3) && (uVar6 == 8)) && ((LPCWCH)lpWideCharStr != (LPCWCH)0x0)) {
            WideCharToMultiByte(0,0,(LPCWCH)lpWideCharStr,-1,(LPSTR)&pwStack_64,10,(LPCCH)0x0,
                                (LPBOOL)0x0);
            if ((undefined1 *)local_34._8_4_ != (undefined1 *)0x0) {
              *(undefined1 *)local_34._8_4_ = pwStack_64._0_1_;
            }
            uStack_74._3_1_ = (undefined1)((uint)uStack_38 >> 0x18);
            uStack_74._0_3_ = CONCAT12(1,(short)uStack_38);
          }
          VariantClear((VARIANTARG *)&stack0xffffffa8);
          cVar4 = (char)uStack_74;
          (**(code **)(u_dwDirectXVersionMinor_004738d4._0_4_ + 8))
                    (u_dwDirectXVersionMinor_004738d4);
          (**(code **)(*piVar5 + 8))(piVar5);
          (**(code **)(*(int *)uStack_74 + 8))(uStack_74);
        }
        goto LAB_0041cfb6;
      }
    }
    cVar4 = (char)unaff_EDI;
    (**(code **)(*(int *)local_3c + 8))();
  }
LAB_0041cfb6:
  if (-1 < HVar1) {
    CoUninitialize();
  }
  return (-(uint)(cVar4 != '\0') & 0x7fffbffb) + 0x80004005;
}



/* quest_file_data_parse @ 0041cfe0 */

/* [binja] int32_t sub_41cfe0(int32_t* arg1, int32_t* arg2, char* arg3) */

int __cdecl quest_file_data_parse(int *arg1,int *arg2,char *arg3)

{
  char cVar1;
  bool bVar2;
  UINT UVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  undefined8 uVar10;
  uint local_408;
  uint local_404;
  char local_400 [512];
  CHAR local_200 [259];
  undefined1 local_fd;
  
  bVar2 = false;
  UVar3 = GetSystemDirectoryA(local_200,0x104);
  if (UVar3 == 0) goto LAB_0041db13;
  uVar4 = 0xffffffff;
  local_fd = 0;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s_ddraw_dll_path;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,2,0,0x5f);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 1;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    uVar10 = audio_create_format(4,3,0,0x448);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 2;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    uVar10 = audio_create_format(4,4,0,0x44);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 3;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = &DAT_0047399c;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,4,0,0x46);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 3;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = 'a';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s_ddraw_dll_path;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,5,0,0x9b);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 5;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    uVar10 = audio_create_format(4,6,0,0x13e);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 6;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    uVar10 = audio_create_format(4,6,0,0x1b4);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 6;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 1;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = &DAT_00473990;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,6,3,0x206);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 6;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 1;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = 'a';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s_ddraw_dll_path;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,7,0,700);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 7;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s_dinput_dll_path;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(4,7,0,0x2cc);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 7;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = 'a';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s_ddraw_dll_path;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    if (local_404 >> 0x10 == 4) {
      uVar10 = audio_create_format(4,8,0,400);
      iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
      if (iVar6 < 0) goto LAB_0041d692;
LAB_0041d6c4:
      if (arg1 != (int *)0x0) {
        *arg1 = 8;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 0;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    else {
LAB_0041d692:
      if (local_404 >> 0x10 == 5) {
        uVar10 = audio_create_format(5,1,0x8d2,400);
        iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
        if (-1 < iVar6) goto LAB_0041d6c4;
      }
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = &s_ogg_extension;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    if (local_404 >> 0x10 == 4) {
      uVar10 = audio_create_format(4,8,1,0x371);
      iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
      if (iVar6 < 0) goto LAB_0041d79c;
LAB_0041d7d0:
      if (arg1 != (int *)0x0) {
        *arg1 = 8;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 1;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    else {
LAB_0041d79c:
      if (local_404 >> 0x10 == 5) {
        uVar10 = audio_create_format(5,1,0xa28,0x371);
        iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
        if (-1 < iVar6) goto LAB_0041d7d0;
      }
    }
    if (local_404 >> 0x10 == 4) {
      uVar10 = audio_create_format(4,8,1,0x385);
      iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
      if (iVar6 < 0) goto LAB_0041d84c;
LAB_0041d87e:
      if (arg1 != (int *)0x0) {
        *arg1 = 8;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 1;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = 'a';
      }
      bVar2 = true;
    }
    else {
LAB_0041d84c:
      if (local_404 >> 0x10 == 5) {
        uVar10 = audio_create_format(5,1,0xa28,0x385);
        iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
        if (-1 < iVar6) goto LAB_0041d87e;
      }
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = &DAT_00473968;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    uVar10 = audio_create_format(6,3,1,0x375);
    iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
    if (-1 < iVar6) {
      if (arg1 != (int *)0x0) {
        *arg1 = 8;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 1;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = 'b';
      }
      bVar2 = true;
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = s__dpnet_dll_0047395c;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    if (local_404 >> 0x10 == 4) {
      uVar10 = audio_create_format(4,9,0,0x86);
      iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
      if (iVar6 < 0) goto LAB_0041da0b;
LAB_0041da3d:
      if (arg1 != (int *)0x0) {
        *arg1 = 8;
      }
      if (arg2 != (int *)0x0) {
        *arg2 = 2;
      }
      if (arg3 != (char *)0x0) {
        *arg3 = ' ';
      }
      bVar2 = true;
    }
    else {
LAB_0041da0b:
      if (local_404 >> 0x10 == 5) {
        uVar10 = audio_create_format(5,2,0xe5d,0x86);
        iVar6 = audio_init_format(local_408,local_404,(uint)uVar10,(uint)((ulonglong)uVar10 >> 0x20));
        if (-1 < iVar6) goto LAB_0041da3d;
      }
    }
  }
  uVar4 = 0xffffffff;
  pcVar7 = local_200;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = local_400;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar4 = 0xffffffff;
  pcVar7 = &DAT_00473950;
  do {
    pcVar9 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar9 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar9;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  iVar6 = -1;
  pcVar7 = local_400;
  do {
    pcVar8 = pcVar7;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar8 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar1 != '\0');
  pcVar7 = pcVar9 + -uVar4;
  pcVar9 = pcVar8 + -1;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar6 = audio_find_format((uint)local_400,(int *)&local_408);
  if (-1 < iVar6) {
    if (arg1 != (int *)0x0) {
      *arg1 = 9;
    }
    if (arg2 != (int *)0x0) {
      *arg2 = 0;
    }
    if (arg3 == (char *)0x0) {
      return 0;
    }
    *arg3 = ' ';
    return 0;
  }
  if (bVar2) {
    return 0;
  }
LAB_0041db13:
  if (arg1 != (int *)0x0) {
    *arg1 = 0;
  }
  if (arg2 != (int *)0x0) {
    *arg2 = 0;
  }
  if (arg3 != (char *)0x0) {
    *arg3 = ' ';
  }
  return 0;
}



/* quest_meta_init_entry @ 00430a20 */

/* initializes a quest metadata entry (name copy, terrain ids, defaults) and updates
   quest_meta_cursor */

int __cdecl quest_meta_init_entry(quest_meta_t *meta,int tier,int index,char *name)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  
  if (meta->name != (char *)0x0) {
    crt_free(meta->name);
    console_printf(&console_log_queue,s___Quest_overwritten__00477742 + 2);
  }
  pcVar2 = strdup_malloc(name);
  meta->name = pcVar2;
  meta->unlock_perk_id = perk_id_antiperk;
  iVar1 = tier * 2 + -2;
  meta->unlock_weapon_id = 0;
  meta->tier = tier;
  meta->index = index;
  meta->terrain_id = iVar1;
  if (index < 6) {
    meta->terrain_id_b = tier * 2 + -1;
    meta->terrain_id_c = iVar1;
  }
  else {
    meta->terrain_id_b = iVar1;
    meta->terrain_id_c = tier * 2 + -1;
  }
  if (4 < tier) {
    uVar3 = index & 0x80000003;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
    }
    meta->terrain_id = uVar3;
    meta->terrain_id_b = 1;
    meta->terrain_id_c = 3;
    meta->builder = (quest_builder_fn_t)0x5;
  }
  quest_meta_cursor = meta;
  return tier;
}



/* quest_spawn_table_empty @ 00434220 */

/* returns 1 when the quest spawn table has no pending entries */

int quest_spawn_table_empty(void)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = quest_spawn_count - 1;
  if (-1 < (int)uVar1) {
    piVar2 = &(&quest_spawn_table)[uVar1].pos_y_block.heading_block.count;
    do {
      if (0 < *piVar2) {
        return uVar1 & 0xffffff00;
      }
      uVar1 = uVar1 - 1;
      piVar2 = piVar2 + -6;
    } while (-1 < (int)uVar1);
  }
  return CONCAT31((int3)(uVar1 >> 8),1);
}



/* quest_spawn_timeline_update @ 00434250 */

/* WARNING: Type propagation algorithm not settling */
/* updates quest spawn entries based on the quest timer */

void quest_spawn_timeline_update(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  quest_spawn_entry_t *pqVar4;
  int iVar5;
  int local_1c;
  float local_18;
  float local_14;
  float local_8;
  float local_4;
  
  if (creatures_any_active_flag == '\0') {
    crt_locale_lc_handle = 0;
  }
  else {
    crt_locale_lc_handle = crt_locale_lc_handle + frame_dt_ms;
  }
  iVar3 = 0;
  if (0 < quest_spawn_count) {
    piVar1 = &quest_spawn_table.pos_y_block.heading_block.trigger_time_ms;
    do {
      if ((0 < piVar1[1]) &&
         ((*piVar1 < quest_spawn_timeline ||
          (((creatures_any_active_flag != '\0' && (3000 < crt_locale_lc_handle)) &&
           (0x6a4 < quest_spawn_timeline)))))) {
        pqVar4 = &quest_spawn_table + iVar3;
        iVar5 = quest_spawn_count;
        while( true ) {
          uVar2 = 0;
          local_18 = 0.0;
          local_14 = 0.0;
          if (0 < (pqVar4->pos_y_block).heading_block.count) {
            local_1c = 0;
            do {
              if ((pqVar4->pos_x < 0.0) || ((float)terrain_texture_width < pqVar4->pos_x)) {
                local_14 = (float)local_1c;
                if ((uVar2 & 1) != 0) {
                  local_14 = -local_14;
                }
              }
              else {
                local_18 = (float)local_1c;
                if ((uVar2 & 1) != 0) {
                  local_18 = -local_18;
                }
              }
              local_8 = local_18 + pqVar4->pos_x;
              local_4 = local_14 + (pqVar4->pos_y_block).pos_y;
              creature_spawn_template
                        ((pqVar4->pos_y_block).heading_block.template_id,&local_8,
                         (pqVar4->pos_y_block).heading_block.heading);
              uVar2 = uVar2 + 1;
              local_1c = local_1c + 0x28;
              iVar5 = quest_spawn_count;
            } while ((int)uVar2 < (pqVar4->pos_y_block).heading_block.count);
          }
          (pqVar4->pos_y_block).heading_block.count = 0;
          creatures_any_active_flag = '\0';
          if (iVar5 + -1 <= iVar3) break;
          if ((pqVar4->pos_y_block).heading_block.trigger_time_ms !=
              pqVar4[1].pos_y_block.heading_block.trigger_time_ms) {
            creatures_any_active_flag = 0;
            return;
          }
          iVar3 = iVar3 + 1;
          pqVar4 = pqVar4 + 1;
        }
        creatures_any_active_flag = 0;
        return;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 6;
    } while (iVar3 < quest_spawn_count);
  }
  return;
}



/* quest_database_advance_slot @ 004343c0 */

/* advances quest database tier/index (wraps every 10) */

void __cdecl quest_database_advance_slot(int *tier,int *index)

{
  int iVar1;
  
  iVar1 = *index;
  *index = iVar1 + 1;
  if (9 < iVar1 + 1) {
    *tier = *tier + 1;
    *index = 0;
  }
  return;
}



/* quest_build_fallback @ 004343e0 */

/* fills a default quest spawn table when no quest builder is present */

void __cdecl quest_build_fallback(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  
  console_printf(&console_log_queue,s___Generating_a_fallback_quest__00477782 + 2);
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = -50.0;
  (entries->pos_y_block).pos_y = fVar1 * 0.5;
  (entries->pos_y_block).heading_block.template_id = 0x40;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 10;
  fVar1 = (float)terrain_texture_height;
  entries[1].pos_x = -50.0;
  entries[1].pos_y_block.pos_y = fVar1 * 0.5;
  entries[1].pos_y_block.heading_block.template_id = 0x40;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 5000;
  entries[1].pos_y_block.heading_block.count = 0x14;
  *count = 2;
  return;
}



/* quest_build_nagolipoli @ 00434480 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 9 (Nagolipoli) */

void quest_build_nagolipoli(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  float fVar2;
  quest_spawn_entry_pos_y_block_t *pqVar3;
  int iVar4;
  quest_spawn_entry_heading_block_t *pqVar5;
  quest_spawn_entry_t *pqVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  int iStack_20;
  
  pqVar1 = entries;
  iStack_20 = 0;
  pqVar6 = entries;
  do {
    iVar4 = iStack_20;
    pqVar3 = &pqVar6->pos_y_block;
    iVar8 = iStack_20 + 1;
    pqVar6 = (quest_spawn_entry_t *)(pqVar3 + 1);
    fVar11 = (float10)iStack_20 * (float10)0.7853982;
    fVar12 = (float10)fcos(fVar11);
    *(float *)((int)(pqVar3 + -1) + 0x10) = (float)(fVar12 * (float10)128.0);
    fVar12 = (float10)fsin(fVar11);
    pqVar3->pos_y = (float)(fVar12 * (float10)128.0);
    *(float *)((int)(pqVar3 + -1) + 0x10) = *(float *)((int)(pqVar3 + -1) + 0x10) + 512.0;
    pqVar3->pos_y = pqVar3->pos_y + 512.0;
    (pqVar3->heading_block).template_id = 0x40;
    (pqVar3->heading_block).heading = (float)fVar11;
    (pqVar3->heading_block).trigger_time_ms = 2000;
    (pqVar3->heading_block).count = 1;
    iStack_20 = iVar8;
  } while (iVar8 < 8);
  iStack_20 = 0;
  pqVar6 = entries + iVar8;
  do {
    pqVar3 = &pqVar6->pos_y_block;
    fVar11 = (float10)iStack_20;
    pqVar6 = (quest_spawn_entry_t *)(pqVar3 + 1);
    iStack_20 = iStack_20 + 1;
    fVar11 = fVar11 * (float10)0.5235988;
    fVar12 = (float10)fcos(fVar11);
    *(float *)((int)(pqVar3 + -1) + 0x10) = (float)(fVar12 * (float10)178.0);
    fVar12 = (float10)fsin(fVar11);
    pqVar3->pos_y = (float)(fVar12 * (float10)178.0);
    *(float *)((int)(pqVar3 + -1) + 0x10) = *(float *)((int)(pqVar3 + -1) + 0x10) + 512.0;
    pqVar3->pos_y = pqVar3->pos_y + 512.0;
    (pqVar3->heading_block).template_id = 0x40;
    (pqVar3->heading_block).heading = (float)fVar11;
    (pqVar3->heading_block).trigger_time_ms = 8000;
    (pqVar3->heading_block).count = 1;
  } while (iStack_20 < 0xc);
  pqVar6 = entries + iVar4 + 0xd;
  iVar10 = 13000;
  iVar8 = 0;
  iVar4 = iVar4 + 0xd;
  do {
    iVar9 = iVar4;
    iVar7 = iVar8;
    pqVar6->pos_x = -64.0;
    (pqVar6->pos_y_block).pos_y = -64.0;
    (pqVar6->pos_y_block).heading_block.template_id = 0x1c;
    (pqVar6->pos_y_block).heading_block.heading = 1.0471976;
    iVar4 = ((int)(iVar7 + (iVar7 >> 0x1f & 7U)) >> 3) + 1;
    (pqVar6->pos_y_block).heading_block.trigger_time_ms = iVar10;
    (pqVar6->pos_y_block).heading_block.count = iVar4;
    pqVar6[1].pos_x = 1088.0;
    pqVar6[1].pos_y_block.pos_y = -64.0;
    pqVar6[1].pos_y_block.heading_block.template_id = 0x1c;
    pqVar6[1].pos_y_block.heading_block.heading = -1.0471976;
    pqVar6[1].pos_y_block.heading_block.trigger_time_ms = iVar10;
    pqVar6[1].pos_y_block.heading_block.count = iVar4;
    pqVar6[2].pos_x = -64.0;
    pqVar6[2].pos_y_block.pos_y = 1088.0;
    pqVar6[2].pos_y_block.heading_block.template_id = 0x1c;
    pqVar6[2].pos_y_block.heading_block.heading = -1.0471976;
    pqVar6[2].pos_y_block.heading_block.trigger_time_ms = iVar10;
    pqVar6[2].pos_y_block.heading_block.count = iVar4;
    pqVar6[3].pos_x = 1088.0;
    pqVar6[3].pos_y_block.pos_y = 1088.0;
    pqVar6[3].pos_y_block.heading_block.template_id = 0x1c;
    pqVar6[3].pos_y_block.heading_block.heading = 3.926991;
    pqVar6[3].pos_y_block.heading_block.trigger_time_ms = iVar10;
    pqVar6[3].pos_y_block.heading_block.count = iVar4;
    pqVar6 = pqVar6 + 4;
    iVar10 = iVar10 + 800;
    iVar8 = iVar7 + 1;
    iVar4 = iVar9 + 4;
  } while (iVar10 < 0x96c8);
  iStack_20 = 0;
  iVar4 = (iVar7 + 0x97 + iVar8 * 4) * 0xa0;
  pqVar5 = &entries[iVar9 + 4].pos_y_block.heading_block;
  do {
    *(undefined4 *)((int)(pqVar5 + -1) + 8) = 0x42800000;
    *(float *)((int)(pqVar5 + -1) + 0xc) = (float)iStack_20 * 85.333336 + 256.0;
    pqVar5->template_id = 10;
    pqVar5->heading = 0.0;
    pqVar5->trigger_time_ms = iVar4;
    pqVar5->count = 1;
    iStack_20 = iStack_20 + 1;
    iVar4 = iVar4 + 100;
    pqVar5 = (quest_spawn_entry_heading_block_t *)((int)(pqVar5 + 1) + 8);
  } while (iStack_20 < 6);
  iStack_20 = 0;
  pqVar5 = &entries[iVar9 + 10].pos_y_block.heading_block;
  entries = (quest_spawn_entry_t *)(iVar8 * 800 + 25000);
  do {
    fVar2 = (float)iStack_20;
    *(undefined4 *)((int)(pqVar5 + -1) + 8) = 0x44700000;
    iStack_20 = iStack_20 + 1;
    *(float *)((int)(pqVar5 + -1) + 0xc) = fVar2 * 85.333336 + 256.0;
    pqVar5->template_id = 10;
    pqVar5->heading = 0.0;
    pqVar5->trigger_time_ms = (int)entries;
    pqVar5->count = 1;
    entries = (quest_spawn_entry_t *)&entries[4].pos_y_block;
    pqVar5 = (quest_spawn_entry_heading_block_t *)((int)(pqVar5 + 1) + 8);
  } while (iStack_20 < 6);
  pqVar6 = pqVar1 + iVar9 + 0x10;
  pqVar6->pos_x = 512.0;
  (pqVar6->pos_y_block).pos_y = 256.0;
  (pqVar6->pos_y_block).heading_block.template_id = 0xb;
  (pqVar6->pos_y_block).heading_block.heading = 3.1415927;
  iVar4 = (iVar7 + 0xb0 + iVar8 * 4) * 0xa0;
  (pqVar6->pos_y_block).heading_block.trigger_time_ms = iVar4;
  (pqVar6->pos_y_block).heading_block.count = 1;
  pqVar6 = pqVar1 + iVar9 + 0x11;
  pqVar6->pos_x = 512.0;
  (pqVar6->pos_y_block).pos_y = 768.0;
  (pqVar6->pos_y_block).heading_block.template_id = 0xb;
  (pqVar6->pos_y_block).heading_block.heading = 3.1415927;
  (pqVar6->pos_y_block).heading_block.trigger_time_ms = iVar4;
  (pqVar6->pos_y_block).heading_block.count = 1;
  pqVar6 = pqVar1 + iVar9 + 0x12;
  pqVar6->pos_x = 512.0;
  (pqVar6->pos_y_block).pos_y = 1088.0;
  (pqVar6->pos_y_block).heading_block.template_id = 0x1c;
  iVar4 = iVar8 * 800 + 0x6f54;
  (pqVar6->pos_y_block).heading_block.heading = 3.926991;
  (pqVar6->pos_y_block).heading_block.trigger_time_ms = iVar4;
  (pqVar6->pos_y_block).heading_block.count = 8;
  pqVar1 = pqVar1 + iVar9 + 0x13;
  pqVar1->pos_x = 512.0;
  (pqVar1->pos_y_block).pos_y = -64.0;
  (pqVar1->pos_y_block).heading_block.template_id = 0x1c;
  (pqVar1->pos_y_block).heading_block.heading = 3.926991;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar4;
  (pqVar1->pos_y_block).heading_block.count = 8;
  *count = iVar9 + 0x14;
  return;
}



/* quest_build_monster_blues @ 00434860 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 8 (Monster Blues) */

void quest_build_monster_blues(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = -50.0;
  (entries->pos_y_block).pos_y = fVar1 * 0.5;
  (entries->pos_y_block).heading_block.template_id = 4;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 10;
  fVar1 = (float)terrain_texture_height;
  entries[1].pos_x = 1074.0;
  entries[1].pos_y_block.pos_y = fVar1 * 0.5;
  entries[1].pos_y_block.heading_block.template_id = 6;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x1d4c;
  entries[1].pos_y_block.heading_block.count = 10;
  entries[2].pos_x = 512.0;
  entries[2].pos_y_block.pos_y = 1088.0;
  entries[2].pos_y_block.heading_block.template_id = 3;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x445c;
  entries[2].pos_y_block.heading_block.count = 0xc;
  entries[3].pos_x = 512.0;
  entries[3].pos_y_block.pos_y = -64.0;
  entries[3].pos_y_block.heading_block.template_id = 3;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x445c;
  entries[3].pos_y_block.heading_block.count = 0xc;
  uVar5 = 0;
  iVar6 = 0x6b6c;
  piVar4 = &entries[4].pos_y_block.heading_block.template_id;
  do {
    piVar4[-3] = -0x3d800000;
    uVar2 = uVar5 & 0x80000003;
    piVar4[-2] = 0x44000000;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
    }
    if (uVar2 == 0) {
      *piVar4 = 6;
    }
    else {
      *piVar4 = (-(uint)(uVar2 != 1) & 2) + 3;
    }
    piVar4[1] = iVar6;
    iVar6 = iVar6 + 900;
    iVar3 = uVar5 + ((int)uVar5 >> 0x1f & 7U);
    uVar5 = uVar5 + 1;
    piVar4[2] = (iVar3 >> 3) + 2;
    piVar4 = piVar4 + 6;
  } while ((int)uVar5 < 0x40);
  *count = 0x44;
  return;
}



/* quest_build_the_gathering @ 004349c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 10 (The Gathering) */

void quest_build_the_gathering(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 512.0;
  (entries->pos_y_block).heading_block.template_id = 1;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 768.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 1;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x251c;
  entries[1].pos_y_block.heading_block.count = 2;
  entries[2].pos_x = 256.0;
  entries[2].pos_y_block.pos_y = 512.0;
  entries[2].pos_y_block.heading_block.template_id = 0x3a;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x3c8c;
  entries[2].pos_y_block.heading_block.count = 2;
  entries[3].pos_x = 768.0;
  entries[3].pos_y_block.pos_y = 512.0;
  entries[3].pos_y_block.heading_block.template_id = 0x3a;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x5fb4;
  entries[3].pos_y_block.heading_block.count = 2;
  entries[4].pos_x = 256.0;
  entries[4].pos_y_block.pos_y = 512.0;
  entries[4].pos_y_block.heading_block.template_id = 0;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 0x7724;
  entries[4].pos_y_block.heading_block.count = 2;
  entries[5].pos_x = 768.0;
  entries[5].pos_y_block.pos_y = 512.0;
  entries[5].pos_y_block.heading_block.template_id = 0;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 0x9a4c;
  entries[5].pos_y_block.heading_block.count = 2;
  entries[6].pos_x = 64.0;
  entries[6].pos_y_block.pos_y = 64.0;
  entries[6].pos_y_block.heading_block.template_id = 0x3c;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 0xd4e4;
  entries[6].pos_y_block.heading_block.count = 2;
  entries[7].pos_x = 960.0;
  entries[7].pos_y_block.pos_y = 64.0;
  entries[7].pos_y_block.heading_block.template_id = 0x3c;
  entries[7].pos_y_block.heading_block.trigger_time_ms = 0xd4e4;
  entries[7].pos_y_block.heading_block.count = 1;
  entries[8].pos_x = 64.0;
  entries[8].pos_y_block.pos_y = 960.0;
  entries[8].pos_y_block.heading_block.template_id = 0x3c;
  entries[8].pos_y_block.heading_block.trigger_time_ms = 0xd4e4;
  entries[8].pos_y_block.heading_block.count = 2;
  entries[9].pos_x = 960.0;
  entries[9].pos_y_block.pos_y = 960.0;
  entries[9].pos_y_block.heading_block.template_id = 0x3c;
  entries[9].pos_y_block.heading_block.trigger_time_ms = 0xd4e4;
  entries[9].pos_y_block.heading_block.count = 1;
  entries[10].pos_x = -128.0;
  entries[10].pos_y_block.pos_y = 512.0;
  entries[10].pos_y_block.heading_block.template_id = 0x3a;
  entries[10].pos_y_block.heading_block.trigger_time_ms = 0x16184;
  entries[10].pos_y_block.heading_block.count = 6;
  entries[0xb].pos_x = 1152.0;
  entries[0xb].pos_y_block.pos_y = 512.0;
  entries[0xb].pos_y_block.heading_block.template_id = 1;
  entries[0xb].pos_y_block.heading_block.trigger_time_ms = 0x184ac;
  entries[0xb].pos_y_block.heading_block.count = 4;
  entries[0xc].pos_x = 1152.0;
  entries[0xc].pos_y_block.pos_y = 512.0;
  entries[0xc].pos_y_block.heading_block.template_id = 1;
  entries[0xc].pos_y_block.heading_block.trigger_time_ms = 0x1abbc;
  entries[0xc].pos_y_block.heading_block.count = 2;
  *count = 0xd;
  return;
}



/* quest_build_army_of_three @ 00434ca0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 7 (Army of Three) */

void quest_build_army_of_three(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = -64.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0x15;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = -64.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 0x15;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x157c;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = -64.0;
  entries[2].pos_y_block.pos_y = 768.0;
  entries[2].pos_y_block.heading_block.template_id = 0x15;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 15000;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = -64.0;
  entries[3].pos_y_block.pos_y = 768.0;
  entries[3].pos_y_block.heading_block.template_id = 0x17;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x4c2c;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_x = -64.0;
  entries[4].pos_y_block.pos_y = 512.0;
  entries[4].pos_y_block.heading_block.template_id = 0x17;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 0x57e4;
  entries[4].pos_y_block.heading_block.count = 1;
  entries[5].pos_x = -64.0;
  entries[5].pos_y_block.pos_y = 256.0;
  entries[5].pos_y_block.heading_block.template_id = 0x17;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 0x6784;
  entries[5].pos_y_block.heading_block.count = 1;
  entries[6].pos_x = -64.0;
  entries[6].pos_y_block.pos_y = 256.0;
  entries[6].pos_y_block.heading_block.template_id = 0x16;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 0x8aac;
  entries[6].pos_y_block.heading_block.count = 1;
  entries[7].pos_x = -64.0;
  entries[7].pos_y_block.pos_y = 512.0;
  entries[7].pos_y_block.heading_block.template_id = 0x16;
  entries[7].pos_y_block.heading_block.trigger_time_ms = 0x9a4c;
  entries[7].pos_y_block.heading_block.count = 1;
  entries[8].pos_x = -64.0;
  entries[8].pos_y_block.pos_y = 768.0;
  entries[8].pos_y_block.heading_block.template_id = 0x16;
  entries[8].pos_y_block.heading_block.trigger_time_ms = 0xa604;
  entries[8].pos_y_block.heading_block.count = 1;
  entries[9].pos_x = 512.0;
  entries[9].pos_y_block.pos_y = 1152.0;
  entries[9].pos_y_block.heading_block.template_id = 0x15;
  entries[9].pos_y_block.heading_block.trigger_time_ms = 0xcd14;
  entries[9].pos_y_block.heading_block.count = 3;
  entries[10].pos_x = 512.0;
  entries[10].pos_y_block.pos_y = -256.0;
  entries[10].pos_y_block.heading_block.template_id = 0x17;
  entries[10].pos_y_block.heading_block.trigger_time_ms = 0xdcb4;
  entries[10].pos_y_block.heading_block.count = 3;
  *count = 0xb;
  return;
}



/* quest_build_knee_deep_in_the_dead @ 00434f00 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 5 (Knee-deep in the Dead) */

void quest_build_knee_deep_in_the_dead(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  quest_spawn_entry_t *pqVar2;
  quest_spawn_entry_t *pqVar3;
  quest_spawn_entry_t *pqVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = -50.0;
  (entries->pos_y_block).pos_y = fVar1 * 0.5;
  (entries->pos_y_block).heading_block.template_id = 0x43;
  (entries->pos_y_block).heading_block.trigger_time_ms = 100;
  (entries->pos_y_block).heading_block.count = 1;
  uVar7 = 0;
  iVar8 = 1;
  pqVar4 = entries + 1;
  iVar5 = 500;
  do {
    uVar6 = uVar7 & 0x80000007;
    bVar10 = uVar6 == 0;
    if ((int)uVar6 < 0) {
      bVar10 = (uVar6 - 1 | 0xfffffff8) == 0xffffffff;
    }
    pqVar2 = pqVar4;
    iVar9 = iVar8;
    if (bVar10) {
      fVar1 = (float)terrain_texture_height;
      pqVar4->pos_x = -50.0;
      iVar9 = iVar8 + 1;
      pqVar2 = pqVar4 + 1;
      (pqVar4->pos_y_block).pos_y = fVar1 * 0.5;
      (pqVar4->pos_y_block).heading_block.template_id = 0x43;
      (pqVar4->pos_y_block).heading_block.trigger_time_ms = iVar5 + -2;
      (pqVar4->pos_y_block).heading_block.count = 1;
    }
    fVar1 = (float)terrain_texture_height;
    pqVar2->pos_x = -50.0;
    (pqVar2->pos_y_block).pos_y = fVar1 * 0.5;
    (pqVar2->pos_y_block).heading_block.template_id = 0x41;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar2->pos_y_block).heading_block.count = (0x20 < (int)uVar7) + 1;
    iVar8 = iVar9 + 1;
    pqVar4 = pqVar2 + 1;
    if (0x30d4 < iVar5) {
      fVar1 = (float)terrain_texture_height;
      pqVar4->pos_x = -50.0;
      iVar8 = iVar9 + 2;
      pqVar4 = pqVar2 + 2;
      pqVar2[1].pos_y_block.pos_y = fVar1 * 0.5 + 158.0;
      pqVar2[1].pos_y_block.heading_block.template_id = 0x41;
      pqVar2[1].pos_y_block.heading_block.trigger_time_ms = iVar5 + 500;
      pqVar2[1].pos_y_block.heading_block.count = 1;
    }
    pqVar2 = pqVar4;
    if (0x5fb4 < iVar5) {
      fVar1 = (float)terrain_texture_height;
      pqVar4->pos_x = -50.0;
      iVar8 = iVar8 + 1;
      pqVar2 = pqVar4 + 1;
      (pqVar4->pos_y_block).pos_y = fVar1 * 0.5 - 158.0;
      (pqVar4->pos_y_block).heading_block.template_id = 0x41;
      (pqVar4->pos_y_block).heading_block.trigger_time_ms = iVar5 + 1000;
      (pqVar4->pos_y_block).heading_block.count = 1;
    }
    pqVar3 = pqVar2;
    if (0x8e94 < iVar5) {
      fVar1 = (float)terrain_texture_height;
      pqVar2->pos_x = -50.0;
      iVar8 = iVar8 + 1;
      pqVar3 = pqVar2 + 1;
      (pqVar2->pos_y_block).pos_y = fVar1 * 0.5 - 258.0;
      (pqVar2->pos_y_block).heading_block.template_id = 0x42;
      (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar5 + 0x514;
      (pqVar2->pos_y_block).heading_block.count = 1;
    }
    pqVar4 = pqVar3;
    if (0xbd74 < iVar5) {
      fVar1 = (float)terrain_texture_height;
      pqVar3->pos_x = -50.0;
      iVar8 = iVar8 + 1;
      pqVar4 = pqVar3 + 1;
      (pqVar3->pos_y_block).pos_y = fVar1 * 0.5 + 258.0;
      (pqVar3->pos_y_block).heading_block.template_id = 0x42;
      (pqVar3->pos_y_block).heading_block.trigger_time_ms = iVar5 + 300;
      (pqVar3->pos_y_block).heading_block.count = 1;
    }
    iVar5 = iVar5 + 0x5dc;
    uVar7 = uVar7 + 1;
  } while (iVar5 < 0x178f4);
  *count = iVar8;
  return;
}



/* quest_build_the_gang_wars @ 00435120 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 4 (The Gang Wars) */

void quest_build_the_gang_wars(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = -150.0;
  (entries->pos_y_block).pos_y = fVar1 * 0.5;
  (entries->pos_y_block).heading_block.template_id = 0x12;
  (entries->pos_y_block).heading_block.trigger_time_ms = 100;
  (entries->pos_y_block).heading_block.count = 1;
  fVar1 = (float)terrain_texture_height;
  entries[1].pos_x = 1174.0;
  iVar4 = 10;
  entries[1].pos_y_block.pos_y = fVar1 * 0.5;
  entries[1].pos_y_block.heading_block.template_id = 0x12;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x9c4;
  entries[1].pos_y_block.heading_block.count = 1;
  iVar3 = 0x157c;
  piVar2 = &entries[2].pos_y_block.heading_block.trigger_time_ms;
  do {
    fVar1 = (float)terrain_texture_height;
    piVar2[-4] = 0x4492c000;
    piVar2[-3] = (int)(fVar1 * 0.5);
    piVar2[-1] = 0x12;
    *piVar2 = iVar3;
    piVar2[1] = 2;
    iVar3 = iVar3 + 4000;
    iVar4 = iVar4 + -1;
    piVar2 = piVar2 + 6;
  } while (iVar4 != 0);
  entries[0xc].pos_x = 512.0;
  entries[0xc].pos_y_block.pos_y = 1152.0;
  entries[0xc].pos_y_block.heading_block.template_id = 0x13;
  entries[0xc].pos_y_block.heading_block.trigger_time_ms = 0xc544;
  entries[0xc].pos_y_block.heading_block.count = 1;
  iVar3 = 0xe86c;
  piVar2 = &entries[0xd].pos_y_block.heading_block.trigger_time_ms;
  do {
    fVar1 = (float)terrain_texture_height;
    piVar2[-4] = -0x3cea0000;
    piVar2[-3] = (int)(fVar1 * 0.5);
    piVar2[-1] = 0x12;
    *piVar2 = iVar3;
    piVar2[1] = 2;
    iVar3 = iVar3 + 4000;
    piVar2 = piVar2 + 6;
  } while (iVar3 < 0x184ac);
  entries[0x17].pos_x = 512.0;
  entries[0x17].pos_y_block.pos_y = 1152.0;
  entries[0x17].pos_y_block.heading_block.template_id = 0x13;
  entries[0x17].pos_y_block.heading_block.trigger_time_ms = 0x1a3ec;
  entries[0x17].pos_y_block.heading_block.count = 3;
  *count = 0x18;
  return;
}



/* quest_build_the_fortress @ 004352d0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 3 (The Fortress) */

void quest_build_the_fortress(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  quest_spawn_entry_t *pqVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  pqVar2 = entries;
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = -50.0;
  entries = (quest_spawn_entry_t *)0x200;
  (pqVar2->pos_y_block).pos_y = fVar1 * 0.5;
  (pqVar2->pos_y_block).heading_block.template_id = 0x40;
  (pqVar2->pos_y_block).heading_block.trigger_time_ms = 100;
  (pqVar2->pos_y_block).heading_block.count = 6;
  iVar4 = 0x44c;
  iVar6 = 8;
  piVar3 = &pqVar2[1].pos_y_block.heading_block.trigger_time_ms;
  do {
    piVar3[-4] = 0x44400000;
    piVar3[-3] = (int)((float)(int)entries * 0.125 + 256.0);
    piVar3[-1] = 9;
    *piVar3 = iVar4;
    piVar3[1] = 1;
    iVar4 = iVar4 + 600;
    entries = (quest_spawn_entry_t *)&entries[0x15].pos_y_block.heading_block;
    piVar3 = piVar3 + 6;
  } while (iVar4 < 0x14b4);
  pqVar2[8].pos_x = 128.0;
  pqVar2[8].pos_y_block.pos_y = 512.0;
  pqVar2[8].pos_y_block.heading_block.template_id = 0xe;
  pqVar2[8].pos_y_block.heading_block.trigger_time_ms = 0x1964;
  pqVar2[8].pos_y_block.heading_block.count = 1;
  entries = (quest_spawn_entry_t *)0x180;
  do {
    iVar5 = 1;
    iVar4 = iVar6 * 600 + 0x157c;
    piVar3 = &pqVar2[iVar6].pos_y_block.heading_block.trigger_time_ms;
    do {
      if ((iVar5 != 1) ||
         ((entries != (quest_spawn_entry_t *)0x480 && (entries != (quest_spawn_entry_t *)0x600)))) {
        iVar6 = iVar6 + 1;
        piVar3[-4] = (int)((float)(int)entries * 0.16666667 + 256.0);
        piVar3[-3] = (int)(512.0 - (float)(iVar5 * 0x180) * 0.16666667);
        piVar3[-1] = 10;
        *piVar3 = iVar4;
        piVar3[1] = 1;
        iVar4 = iVar4 + 600;
        piVar3 = piVar3 + 6;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 7);
    entries = entries + 0x10;
  } while ((int)entries < 0x901);
  *count = iVar6;
  return;
}



/* quest_build_cross_fire @ 00435480 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 6 (Cross Fire) */

void quest_build_cross_fire(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  
  fVar1 = (float)terrain_texture_height;
  entries->pos_x = 1074.0;
  (entries->pos_y_block).pos_y = fVar1 * 0.5;
  (entries->pos_y_block).heading_block.template_id = 0x40;
  (entries->pos_y_block).heading_block.trigger_time_ms = 100;
  (entries->pos_y_block).heading_block.count = 6;
  entries[1].pos_x = -40.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 0x3c;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x157c;
  entries[1].pos_y_block.heading_block.count = 4;
  entries[2].pos_x = -40.0;
  entries[2].pos_y_block.pos_y = 512.0;
  entries[2].pos_y_block.heading_block.template_id = 0x3c;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x3c8c;
  entries[2].pos_y_block.heading_block.count = 6;
  entries[3].pos_x = 512.0;
  entries[3].pos_y_block.pos_y = 512.0;
  entries[3].pos_y_block.heading_block.template_id = 1;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x4844;
  entries[3].pos_y_block.heading_block.count = 2;
  entries[4].pos_x = -100.0;
  entries[4].pos_y_block.pos_y = 512.0;
  entries[4].pos_y_block.heading_block.template_id = 0x3c;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 0x639c;
  entries[4].pos_y_block.heading_block.count = 8;
  entries[5].pos_x = 512.0;
  entries[5].pos_y_block.pos_y = 1152.0;
  entries[5].pos_y_block.heading_block.template_id = 0x40;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 26000;
  entries[5].pos_y_block.heading_block.count = 6;
  entries[6].pos_x = 512.0;
  entries[6].pos_y_block.pos_y = -128.0;
  entries[6].pos_y_block.heading_block.template_id = 0x40;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 26000;
  entries[6].pos_y_block.heading_block.count = 6;
  *count = 7;
  return;
}



/* quest_build_the_beating @ 00435610 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 1 (The Beating) */

void quest_build_the_beating(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  quest_spawn_entry_t *pqVar7;
  int iVar8;
  int iVar9;
  
  pqVar1 = entries;
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0x27;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  iVar5 = 10000;
  iVar2 = terrain_texture_height / 2;
  entries[1].pos_x = (float)(terrain_texture_width + 0x20);
  iVar9 = 0x40;
  iVar8 = 8;
  entries[1].pos_y_block.pos_y = (float)iVar2;
  entries[1].pos_y_block.heading_block.template_id = 0x29;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 8000;
  entries[1].pos_y_block.heading_block.count = 3;
  piVar4 = &entries[2].pos_y_block.heading_block.trigger_time_ms;
  do {
    iVar2 = iVar9 + terrain_texture_width;
    iVar9 = iVar9 + 0x20;
    iVar3 = terrain_texture_height / 2;
    piVar4[-4] = (int)(float)iVar2;
    piVar4[-3] = (int)(float)iVar3;
    piVar4[-1] = 0x25;
    *piVar4 = iVar5;
    piVar4[1] = 8;
    iVar5 = iVar5 + 100;
    iVar8 = iVar8 + -1;
    piVar4 = piVar4 + 6;
  } while (iVar8 != 0);
  iVar2 = terrain_texture_height / 2;
  entries[10].pos_x = -32.0;
  iVar5 = 20000;
  pqVar7 = entries + 0xb;
  entries = (quest_spawn_entry_t *)0xffffffc0;
  pqVar1[10].pos_y_block.pos_y = (float)iVar2;
  pqVar1[10].pos_y_block.heading_block.template_id = 0x29;
  pqVar1[10].pos_y_block.heading_block.trigger_time_ms = 18000;
  pqVar1[10].pos_y_block.heading_block.count = 3;
  piVar4 = &(pqVar7->pos_y_block).heading_block.trigger_time_ms;
  do {
    piVar6 = &entries[-2].pos_y_block.heading_block.trigger_time_ms;
    iVar2 = terrain_texture_height / 2;
    piVar4[-4] = (int)(float)(int)entries;
    piVar4[-3] = (int)(float)iVar2;
    piVar4[-1] = 0x25;
    *piVar4 = iVar5;
    piVar4[1] = 8;
    iVar5 = iVar5 + 100;
    piVar4 = piVar4 + 6;
    entries = (quest_spawn_entry_t *)piVar6;
  } while (-0x140 < (int)piVar6);
  iVar2 = 40000;
  entries = (quest_spawn_entry_t *)0xffffffc0;
  piVar4 = &pqVar1[0x13].pos_y_block.heading_block.trigger_time_ms;
  do {
    pqVar7 = (quest_spawn_entry_t *)((int)&entries[-2].pos_y_block.pos_y + 2);
    piVar4[-4] = (int)(float)(terrain_texture_width / 2);
    piVar4[-3] = (int)(float)(int)entries;
    piVar4[-1] = 0xf;
    *piVar4 = iVar2;
    piVar4[1] = 4;
    iVar2 = iVar2 + 100;
    piVar4 = piVar4 + 6;
    entries = pqVar7;
  } while (-0x13c < (int)pqVar7);
  iVar2 = 0;
  iVar5 = 40000;
  piVar4 = &pqVar1[0x19].pos_y_block.heading_block.trigger_time_ms;
  do {
    iVar8 = iVar2 + 0x2c + terrain_texture_width;
    iVar2 = iVar2 + 0x20;
    piVar4[-4] = (int)(float)(terrain_texture_width / 2);
    piVar4[-3] = (int)(float)iVar8;
    piVar4[-1] = 0x12;
    *piVar4 = iVar5;
    piVar4[1] = 2;
    iVar5 = iVar5 + 100;
    piVar4 = piVar4 + 6;
  } while (iVar5 < 0x9e98);
  *count = 0x1f;
  return;
}



/* quest_build_the_spanking_of_the_dead @ 004358a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 5 Quest 2 (The Spanking Of The Dead) */

void quest_build_the_spanking_of_the_dead(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int *piVar2;
  int iVar3;
  quest_spawn_entry_t *pqVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  
  pqVar1 = entries;
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 512.0;
  (entries->pos_y_block).heading_block.template_id = 0x27;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 768.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 0x27;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 500;
  entries[1].pos_y_block.heading_block.count = 1;
  entries = (quest_spawn_entry_t *)0x0;
  iVar3 = 5000;
  piVar2 = &pqVar1[2].pos_y_block.heading_block.template_id;
  do {
    pqVar4 = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
    fVar5 = (float10)(int)entries * (float10)0.33333334;
    fVar6 = (float10)512.0 - (float10)(int)entries * (float10)3.8;
    fVar7 = (float10)fcos(fVar5);
    fVar8 = (float10)fsin(fVar5);
    piVar2[-3] = (int)(float)(fVar7 * fVar6 + (float10)512.0);
    piVar2[-2] = (int)(float)(fVar8 * fVar6 + (float10)512.0);
    ((quest_spawn_entry_heading_block_t *)(piVar2 + -1))->heading = (float)fVar5;
    *piVar2 = 0x41;
    piVar2[1] = iVar3;
    piVar2[2] = 1;
    iVar3 = iVar3 + 300;
    piVar2 = piVar2 + 6;
    entries = pqVar4;
  } while (iVar3 < 0xa988);
  pqVar1[0x82].pos_x = 1280.0;
  pqVar1[0x82].pos_y_block.pos_y = 512.0;
  iVar3 = (int)pqVar4 * 300;
  pqVar1[0x82].pos_y_block.heading_block.template_id = 0x42;
  pqVar1[0x82].pos_y_block.heading_block.trigger_time_ms = iVar3 + 10000;
  pqVar1[0x82].pos_y_block.heading_block.count = 0x10;
  pqVar1[0x83].pos_x = -256.0;
  pqVar1[0x83].pos_y_block.pos_y = 512.0;
  pqVar1[0x83].pos_y_block.heading_block.template_id = 0x42;
  pqVar1[0x83].pos_y_block.heading_block.trigger_time_ms = iVar3 + 20000;
  pqVar1[0x83].pos_y_block.heading_block.count = 0x10;
  *count = 0x84;
  return;
}



/* quest_build_hidden_evil @ 00435a30 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 4 (Hidden Evil) */

void quest_build_hidden_evil(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  
  iVar1 = terrain_texture_height + 0x40;
  entries->pos_x = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).pos_y = (float)iVar1;
  (entries->pos_y_block).heading_block.template_id = 0x21;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 0x32;
  iVar1 = terrain_texture_height + 0x40;
  entries[1].pos_x = (float)(terrain_texture_width / 2);
  entries[1].pos_y_block.pos_y = (float)iVar1;
  entries[1].pos_y_block.heading_block.template_id = 0x22;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 15000;
  entries[1].pos_y_block.heading_block.count = 0x1e;
  iVar1 = terrain_texture_height + 0x40;
  entries[2].pos_x = (float)(terrain_texture_width / 2);
  entries[2].pos_y_block.pos_y = (float)iVar1;
  entries[2].pos_y_block.heading_block.template_id = 0x23;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 25000;
  entries[2].pos_y_block.heading_block.count = 0x14;
  iVar1 = terrain_texture_height + 0x40;
  entries[3].pos_x = (float)(terrain_texture_width / 2);
  entries[3].pos_y_block.pos_y = (float)iVar1;
  entries[3].pos_y_block.heading_block.template_id = 0x23;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 30000;
  entries[3].pos_y_block.heading_block.count = 0x1e;
  iVar1 = terrain_texture_height + 0x40;
  entries[4].pos_x = (float)(terrain_texture_width / 2);
  entries[4].pos_y_block.pos_y = (float)iVar1;
  entries[4].pos_y_block.heading_block.template_id = 0x22;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 35000;
  entries[4].pos_y_block.heading_block.count = 0x1e;
  *count = 5;
  return;
}



/* quest_build_land_hostile @ 00435bd0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 1 (Land Hostile) */

void quest_build_land_hostile(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  
  iVar1 = terrain_texture_height + 0x40;
  entries->pos_x = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).pos_y = (float)iVar1;
  (entries->pos_y_block).heading_block.template_id = 0x26;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = -64.0;
  entries[1].pos_y_block.pos_y = 1088.0;
  entries[1].pos_y_block.heading_block.template_id = 0x26;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x9c4;
  entries[1].pos_y_block.heading_block.count = 2;
  entries[2].pos_x = -64.0;
  entries[2].pos_y_block.pos_y = -64.0;
  entries[2].pos_y_block.heading_block.template_id = 0x26;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x1964;
  entries[2].pos_y_block.heading_block.count = 3;
  entries[3].pos_x = 1088.0;
  entries[3].pos_y_block.pos_y = -64.0;
  entries[3].pos_y_block.heading_block.template_id = 0x26;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x2cec;
  entries[3].pos_y_block.heading_block.count = 4;
  *count = 4;
  return;
}



/* quest_build_minor_alien_breach @ 00435cc0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 2 (Minor Alien Breach) */

void quest_build_minor_alien_breach(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  quest_spawn_entry_t *pqVar2;
  quest_spawn_entry_t *pqVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0x26;
  iVar6 = 2;
  (entries->pos_y_block).heading_block.trigger_time_ms = 1000;
  (entries->pos_y_block).heading_block.count = 2;
  entries[1].pos_x = 256.0;
  entries[1].pos_y_block.pos_y = 128.0;
  entries[1].pos_y_block.heading_block.template_id = 0x26;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x6a4;
  entries[1].pos_y_block.heading_block.count = 2;
  iVar4 = 2;
  pqVar3 = entries + 2;
  do {
    iVar1 = terrain_texture_height / 2;
    pqVar3->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar3->pos_y_block).pos_y = (float)iVar1;
    (pqVar3->pos_y_block).heading_block.template_id = 0x26;
    iVar5 = (iVar4 * 5 + -10) * 0x2d0;
    (pqVar3->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar3->pos_y_block).heading_block.count = 1;
    pqVar2 = pqVar3 + 1;
    iVar1 = iVar6 + 1;
    if (6 < iVar4) {
      iVar1 = terrain_texture_height / 2;
      pqVar3[1].pos_x = (float)(terrain_texture_width + 0x40);
      pqVar3[1].pos_y_block.pos_y = (float)(iVar1 + -0x100);
      pqVar3[1].pos_y_block.heading_block.template_id = 0x26;
      pqVar3[1].pos_y_block.heading_block.trigger_time_ms = iVar5;
      pqVar3[1].pos_y_block.heading_block.count = 1;
      pqVar2 = pqVar3 + 2;
      iVar1 = iVar6 + 2;
    }
    iVar6 = iVar1;
    pqVar3 = pqVar2;
    if (iVar4 == 0xd) {
      iVar1 = terrain_texture_height + 0x40;
      iVar6 = iVar6 + 1;
      pqVar3->pos_x = (float)(terrain_texture_width / 2);
      (pqVar3->pos_y_block).pos_y = (float)iVar1;
      (pqVar3->pos_y_block).heading_block.template_id = 0x29;
      (pqVar3->pos_y_block).heading_block.trigger_time_ms = 0x9ab0;
      (pqVar3->pos_y_block).heading_block.count = 1;
      pqVar2 = pqVar3 + 1;
LAB_00435e39:
      iVar1 = terrain_texture_height / 2;
      pqVar2->pos_x = -64.0;
      iVar6 = iVar6 + 1;
      pqVar3 = pqVar2 + 1;
      (pqVar2->pos_y_block).pos_y = (float)(iVar1 + 0x100);
      (pqVar2->pos_y_block).heading_block.template_id = 0x26;
      (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar5;
      (pqVar2->pos_y_block).heading_block.count = 1;
    }
    else {
      pqVar2 = pqVar3;
      if (10 < iVar4) goto LAB_00435e39;
    }
    iVar4 = iVar4 + 1;
    if (0x11 < iVar4) {
      *count = iVar6;
      return;
    }
  } while( true );
}



/* quest_build_alien_squads @ 00435ea0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 8 (Alien Squads) */

void quest_build_alien_squads(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  
  entries->pos_x = -256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0x12;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = -256.0;
  entries[1].pos_y_block.pos_y = 768.0;
  entries[1].pos_y_block.heading_block.template_id = 0x12;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x9c4;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 768.0;
  entries[2].pos_y_block.pos_y = -256.0;
  entries[2].pos_y_block.heading_block.template_id = 0x12;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x157c;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = 768.0;
  entries[3].pos_y_block.pos_y = 1280.0;
  entries[3].pos_y_block.heading_block.template_id = 0x12;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x2134;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_x = 1280.0;
  entries[4].pos_y_block.pos_y = 1280.0;
  entries[4].pos_y_block.heading_block.template_id = 0x12;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 0x38a4;
  entries[4].pos_y_block.heading_block.count = 1;
  entries[5].pos_x = 1280.0;
  entries[5].pos_y_block.pos_y = 768.0;
  entries[5].pos_y_block.heading_block.template_id = 0x12;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 0x4844;
  entries[5].pos_y_block.heading_block.count = 1;
  entries[6].pos_x = -256.0;
  entries[6].pos_y_block.pos_y = 256.0;
  entries[6].pos_y_block.heading_block.template_id = 0x12;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 25000;
  entries[6].pos_y_block.heading_block.count = 1;
  entries[7].pos_x = -256.0;
  entries[7].pos_y_block.pos_y = 768.0;
  entries[7].pos_y_block.heading_block.template_id = 0x12;
  entries[7].pos_y_block.heading_block.trigger_time_ms = 30000;
  entries[7].pos_y_block.heading_block.count = 1;
  iVar3 = 8;
  pqVar1 = entries + 8;
  iVar2 = 0x8d68;
  do {
    pqVar1->pos_x = -64.0;
    (pqVar1->pos_y_block).pos_y = -64.0;
    (pqVar1->pos_y_block).heading_block.template_id = 0x26;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar2 + -400;
    (pqVar1->pos_y_block).heading_block.count = 1;
    iVar3 = iVar3 + 2;
    pqVar1[1].pos_x = 1088.0;
    pqVar1[1].pos_y_block.pos_y = 1088.0;
    pqVar1[1].pos_y_block.heading_block.template_id = 0x26;
    pqVar1[1].pos_y_block.heading_block.trigger_time_ms = iVar2;
    pqVar1[1].pos_y_block.heading_block.count = 1;
    iVar2 = iVar2 + 0x708;
    pqVar1 = pqVar1 + 2;
  } while (iVar2 < 83000);
  *count = iVar3;
  return;
}



/* quest_build_zombie_masters @ 004360a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 10 (Zombie Masters) */

void quest_build_zombie_masters(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0;
  (entries->pos_y_block).heading_block.trigger_time_ms = 1000;
  (entries->pos_y_block).heading_block.count = config_blob.reserved0._20_4_;
  entries[1].pos_x = 512.0;
  entries[1].pos_y_block.pos_y = 256.0;
  entries[1].pos_y_block.heading_block.template_id = 0;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 6000;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 768.0;
  entries[2].pos_y_block.pos_y = 256.0;
  entries[2].pos_y_block.heading_block.template_id = 0;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 14000;
  entries[2].pos_y_block.heading_block.count = config_blob.reserved0._20_4_;
  entries[3].pos_x = 768.0;
  entries[3].pos_y_block.pos_y = 768.0;
  entries[3].pos_y_block.heading_block.template_id = 0;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 18000;
  entries[3].pos_y_block.heading_block.count = 1;
  *count = 4;
  return;
}



/* quest_build_8_legged_terror @ 00436120 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 10 (8-legged Terror) */

void quest_build_8_legged_terror(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  
  entries->pos_x = (float)(terrain_texture_width + -0x100);
  iVar3 = 1;
  pqVar1 = entries + 1;
  (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).heading_block.template_id = 0x3a;
  (entries->pos_y_block).heading_block.trigger_time_ms = 1000;
  (entries->pos_y_block).heading_block.count = 1;
  iVar2 = 6000;
  do {
    pqVar1->pos_x = -25.0;
    (pqVar1->pos_y_block).pos_y = -25.0;
    (pqVar1->pos_y_block).heading_block.template_id = 0x3d;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar2;
    (pqVar1->pos_y_block).heading_block.count = config_blob.reserved0._20_4_;
    pqVar1[1].pos_x = 1049.0;
    pqVar1[1].pos_y_block.pos_y = -25.0;
    pqVar1[1].pos_y_block.heading_block.template_id = 0x3d;
    pqVar1[1].pos_y_block.heading_block.trigger_time_ms = iVar2;
    pqVar1[1].pos_y_block.heading_block.count = 1;
    pqVar1[2].pos_x = -25.0;
    pqVar1[2].pos_y_block.pos_y = 1049.0;
    pqVar1[2].pos_y_block.heading_block.template_id = 0x3d;
    pqVar1[2].pos_y_block.heading_block.trigger_time_ms = iVar2;
    pqVar1[2].pos_y_block.heading_block.count = config_blob.reserved0._20_4_;
    iVar3 = iVar3 + 4;
    pqVar1[3].pos_x = 1049.0;
    pqVar1[3].pos_y_block.pos_y = 1049.0;
    pqVar1[3].pos_y_block.heading_block.template_id = 0x3d;
    pqVar1[3].pos_y_block.heading_block.trigger_time_ms = iVar2;
    pqVar1[3].pos_y_block.heading_block.count = 1;
    iVar2 = iVar2 + 0x898;
    pqVar1 = pqVar1 + 4;
  } while (iVar2 < 0x8fc0);
  *count = iVar3;
  return;
}



/* quest_build_ghost_patrols @ 00436200 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 9 (Ghost Patrols) */

void quest_build_ghost_patrols(quest_spawn_entry_t *entries,int *count)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  bool bVar5;
  
  iVar2 = 0x9c4;
  entries->pos_x = (float)(terrain_texture_width + 0x80);
  (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).heading_block.template_id = 0x2b;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 2;
  piVar3 = &entries[1].pos_y_block.heading_block.template_id;
  uVar1 = 0;
  do {
    uVar4 = uVar1;
    uVar1 = uVar4 & 0x80000001;
    bVar5 = uVar1 == 0;
    if ((int)uVar1 < 0) {
      bVar5 = (uVar1 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar5) {
      piVar3[-3] = 0xc3000000;
    }
    else {
      piVar3[-3] = 0x44900000;
    }
    uVar1 = uVar4 + 1;
    piVar3[-2] = (int)(float)(terrain_texture_width / 2);
    *piVar3 = 0x19;
    piVar3[1] = iVar2;
    piVar3[2] = 1;
    iVar2 = iVar2 + 0x9c4;
    piVar3 = piVar3 + 6;
  } while (iVar2 < 0x7ef4);
  entries[0xd].pos_x = -264.0;
  entries[0xd].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
  entries[0xd].pos_y_block.heading_block.template_id = 0x2b;
  entries[0xd].pos_y_block.heading_block.trigger_time_ms = uVar1 * 0x9c4 + -0x9c4;
  entries[0xd].pos_y_block.heading_block.count = 1;
  entries[0xe].pos_x = -128.0;
  entries[0xe].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
  entries[0xe].pos_y_block.heading_block.template_id = 0x18;
  entries[0xe].pos_y_block.heading_block.trigger_time_ms = (uVar4 + 0x10 + uVar1 * 4) * 500;
  entries[0xe].pos_y_block.heading_block.count = 1;
  *count = 0xf;
  return;
}



/* quest_build_the_random_factor @ 00436350 */

/* quest builder for Tier 1 Quest 6 (The Random Factor) */

void __cdecl quest_build_the_random_factor(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0x5dc;
  iVar3 = 0;
  do {
    pqVar1 = entries + iVar3;
    pqVar1->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x1d;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = config_blob.reserved0._20_4_ * 2 + 4;
    pqVar1 = entries + iVar3 + 1;
    pqVar1->pos_x = -64.0;
    iVar4 = iVar3 + 2;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x1d;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5 + 200;
    (pqVar1->pos_y_block).heading_block.count = 6;
    iVar2 = crt_rand();
    if (iVar2 % 5 == 3) {
      pqVar1 = entries + iVar4;
      iVar4 = iVar3 + 3;
      pqVar1->pos_x = (float)(terrain_texture_width / 2);
      (pqVar1->pos_y_block).pos_y = 1088.0;
      (pqVar1->pos_y_block).heading_block.template_id = 0x29;
      (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
      (pqVar1->pos_y_block).heading_block.count = config_blob.reserved0._20_4_;
    }
    iVar5 = iVar5 + 10000;
    iVar3 = iVar4;
  } while (iVar5 < 0x18c7c);
  *count = iVar4;
  return;
}



/* quest_build_spider_wave_syndrome @ 00436440 */

/* quest builder for Tier 1 Quest 7 (Spider Wave Syndrome) */

void __cdecl quest_build_spider_wave_syndrome(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0x5dc;
  do {
    pqVar1 = entries + iVar2;
    pqVar1->pos_x = -64.0;
    iVar2 = iVar2 + 1;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x40;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar3;
    iVar3 = iVar3 + 0x157c;
    (pqVar1->pos_y_block).heading_block.count = config_blob.reserved0._20_4_ * 2 + 6;
  } while (iVar3 < 0x18894);
  *count = iVar2;
  return;
}



/* quest_build_nesting_grounds @ 004364a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 9 (Nesting Grounds) */

void quest_build_nesting_grounds(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).pos_y = (float)(terrain_texture_height + 0x40);
  (entries->pos_y_block).heading_block.template_id = 0x1d;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = config_blob.reserved0._20_4_ * 2 + 6;
  entries[1].pos_x = 256.0;
  entries[1].pos_y_block.pos_y = 256.0;
  entries[1].pos_y_block.heading_block.template_id = 9;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 8000;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 512.0;
  entries[2].pos_y_block.pos_y = 512.0;
  entries[2].pos_y_block.heading_block.template_id = 9;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 13000;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = 768.0;
  entries[3].pos_y_block.pos_y = 768.0;
  entries[3].pos_y_block.heading_block.template_id = 9;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 18000;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_x = (float)(terrain_texture_width / 2);
  entries[4].pos_y_block.pos_y = (float)(terrain_texture_height + 0x40);
  entries[4].pos_y_block.heading_block.template_id = 0x1d;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 25000;
  entries[4].pos_y_block.heading_block.count = config_blob.reserved0._20_4_ * 2 + 6;
  entries[5].pos_x = (float)(terrain_texture_width / 2);
  entries[5].pos_y_block.pos_y = (float)(terrain_texture_height + 0x40);
  entries[5].pos_y_block.heading_block.template_id = 0x1d;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 39000;
  entries[5].pos_y_block.heading_block.count = config_blob.reserved0._20_4_ * 3 + 3;
  entries[6].pos_x = 384.0;
  entries[6].pos_y_block.pos_y = 512.0;
  entries[6].pos_y_block.heading_block.template_id = 9;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 0xa08c;
  entries[6].pos_y_block.heading_block.count = 1;
  entries[7].pos_x = 640.0;
  entries[7].pos_y_block.pos_y = 512.0;
  entries[7].pos_y_block.heading_block.template_id = 9;
  entries[7].pos_y_block.heading_block.trigger_time_ms = 0xa474;
  entries[7].pos_y_block.heading_block.count = 1;
  entries[8].pos_x = 512.0;
  entries[8].pos_y_block.pos_y = 640.0;
  entries[8].pos_y_block.heading_block.template_id = 9;
  entries[8].pos_y_block.heading_block.trigger_time_ms = 0xa85c;
  entries[8].pos_y_block.heading_block.count = 1;
  entries[9].pos_x = 512.0;
  entries[9].pos_y_block.pos_y = 512.0;
  entries[9].pos_y_block.heading_block.template_id = 8;
  entries[9].pos_y_block.heading_block.trigger_time_ms = 0xac44;
  entries[9].pos_y_block.heading_block.count = 1;
  entries[10].pos_x = (float)(terrain_texture_width / 2);
  entries[10].pos_y_block.pos_y = (float)(terrain_texture_height + 0x40);
  entries[10].pos_y_block.heading_block.template_id = 0x1e;
  entries[10].pos_y_block.heading_block.trigger_time_ms = 50000;
  entries[10].pos_y_block.heading_block.count = config_blob.reserved0._20_4_ * 2 + 5;
  entries[0xb].pos_x = (float)(terrain_texture_width / 2);
  entries[0xb].pos_y_block.pos_y = (float)(terrain_texture_height + 0x40);
  entries[0xb].pos_y_block.heading_block.template_id = 0x1f;
  entries[0xb].pos_y_block.heading_block.trigger_time_ms = 55000;
  entries[0xb].pos_y_block.heading_block.count = config_blob.reserved0._20_4_ * 2 + 2;
  *count = 0xc;
  return;
}



/* quest_build_alien_dens @ 00436720 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 5 (Alien Dens) */

void quest_build_alien_dens(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 8;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 768.0;
  entries[1].pos_y_block.pos_y = 768.0;
  entries[1].pos_y_block.heading_block.template_id = 8;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 512.0;
  entries[2].pos_y_block.pos_y = 512.0;
  entries[2].pos_y_block.heading_block.template_id = 8;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x5bcc;
  entries[2].pos_y_block.heading_block.count = config_blob.reserved0._20_4_;
  entries[3].pos_x = 256.0;
  entries[3].pos_y_block.pos_y = 768.0;
  entries[3].pos_y_block.heading_block.template_id = 8;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x9664;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_x = 768.0;
  entries[4].pos_y_block.pos_y = 256.0;
  entries[4].pos_y_block.heading_block.template_id = 8;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 0x9664;
  entries[4].pos_y_block.heading_block.count = 1;
  *count = 5;
  return;
}



/* quest_build_arachnoid_farm @ 00436820 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 3 (Arachnoid Farm) */

void quest_build_arachnoid_farm(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iStack_c;
  
  iVar3 = 0;
  iStack_c = 0;
  if (config_blob.reserved0._20_4_ != -4 && -1 < config_blob.reserved0._20_4_ + 4) {
    iVar4 = 500;
    piVar2 = &(entries->pos_y_block).heading_block.trigger_time_ms;
    do {
      iVar3 = iStack_c + 1;
      piVar2[-4] = (int)((float)iStack_c * 102.4 + 256.0);
      piVar2[-3] = 0x43800000;
      piVar2[-1] = 10;
      *piVar2 = iVar4;
      piVar2[1] = 1;
      iVar4 = iVar4 + 500;
      piVar2 = piVar2 + 6;
      iStack_c = iVar3;
    } while (iVar3 < config_blob.reserved0._20_4_ + 4);
  }
  iStack_c = 0;
  if (config_blob.reserved0._20_4_ != -4 && -1 < config_blob.reserved0._20_4_ + 4) {
    iVar4 = 0x2904;
    piVar2 = &entries[iVar3].pos_y_block.heading_block.trigger_time_ms;
    do {
      fVar1 = (float)iStack_c;
      iVar3 = iVar3 + 1;
      iStack_c = iStack_c + 1;
      piVar2[-4] = (int)(fVar1 * 102.4 + 256.0);
      piVar2[-3] = 0x44400000;
      piVar2[-1] = 10;
      *piVar2 = iVar4;
      piVar2[1] = 1;
      iVar4 = iVar4 + 500;
      piVar2 = piVar2 + 6;
    } while (iStack_c < config_blob.reserved0._20_4_ + 4);
  }
  iStack_c = 0;
  if (config_blob.reserved0._20_4_ != -7 && -1 < config_blob.reserved0._20_4_ + 7) {
    iVar4 = 0x9e34;
    piVar2 = &entries[iVar3].pos_y_block.heading_block.trigger_time_ms;
    do {
      fVar1 = (float)iStack_c;
      iVar3 = iVar3 + 1;
      iStack_c = iStack_c + 1;
      piVar2[-4] = (int)(fVar1 * 64.0 + 256.0);
      piVar2[-3] = 0x44000000;
      piVar2[-1] = 0x10;
      *piVar2 = iVar4;
      piVar2[1] = 1;
      iVar4 = iVar4 + 0xdac;
      piVar2 = piVar2 + 6;
    } while (iStack_c < config_blob.reserved0._20_4_ + 7);
    *count = iVar3;
    return;
  }
  *count = iVar3;
  return;
}



/* quest_build_gauntlet @ 004369a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 7 (Gauntlet) */

void quest_build_gauntlet(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  quest_spawn_entry_t *pqVar2;
  int *piVar3;
  quest_spawn_entry_t *pqVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  int iStack_8;
  int iStack_4;
  
  pqVar2 = entries;
  iVar6 = 0;
  iStack_8 = 0;
  if (config_blob.hardcore != '\0') {
    config_blob.reserved0._20_4_ = config_blob.reserved0._20_4_ + 4;
  }
  iStack_4 = config_blob.reserved0._20_4_ + 9;
  if (0 < iStack_4) {
    iVar7 = 0;
    piVar3 = &(entries->pos_y_block).heading_block.template_id;
    do {
      fVar8 = (float10)fcos(((float10)iStack_8 * (float10)6.2831855) / (float10)iStack_4);
      piVar3[-3] = (int)(float)(fVar8 * (float10)158.0 + (float10)512.0);
      iVar6 = iStack_8 + 1;
      fVar8 = (float10)fsin(((float10)iStack_8 * (float10)6.2831855) /
                            (float10)(config_blob.reserved0._20_4_ + 9));
      piVar3[-2] = (int)(float)(fVar8 * (float10)158.0 + (float10)512.0);
      *piVar3 = 10;
      piVar3[1] = iVar7;
      piVar3[2] = 1;
      iVar7 = iVar7 + 200;
      iStack_4 = config_blob.reserved0._20_4_ + 9;
      piVar3 = piVar3 + 6;
      iStack_8 = iVar6;
    } while (iVar6 < iStack_4);
  }
  if (config_blob.reserved0._20_4_ != -9 && -1 < config_blob.reserved0._20_4_ + 9) {
    iVar5 = 4000;
    pqVar4 = entries + iVar6;
    iVar7 = 2;
    do {
      pqVar4->pos_x = (float)(terrain_texture_width + 0x40);
      (pqVar4->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
      (pqVar4->pos_y_block).heading_block.template_id = 0x41;
      (pqVar4->pos_y_block).heading_block.trigger_time_ms = iVar5;
      (pqVar4->pos_y_block).heading_block.count = iVar7;
      pqVar4[1].pos_x = -64.0;
      pqVar4[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
      pqVar4[1].pos_y_block.heading_block.template_id = 0x41;
      pqVar4[1].pos_y_block.heading_block.trigger_time_ms = iVar5;
      pqVar4[1].pos_y_block.heading_block.count = iVar7;
      pqVar4[2].pos_x = (float)(terrain_texture_width / 2);
      pqVar4[2].pos_y_block.pos_y = (float)(terrain_texture_width + 0x40);
      pqVar4[2].pos_y_block.heading_block.template_id = 0x41;
      pqVar4[2].pos_y_block.heading_block.trigger_time_ms = iVar5;
      pqVar4[2].pos_y_block.heading_block.count = iVar7;
      iVar6 = iVar6 + 4;
      pqVar4[3].pos_x = (float)(terrain_texture_width / 2);
      pqVar4[3].pos_y_block.pos_y = -64.0;
      pqVar4[3].pos_y_block.heading_block.template_id = 0x41;
      pqVar4[3].pos_y_block.heading_block.trigger_time_ms = iVar5;
      pqVar4[3].pos_y_block.heading_block.count = iVar7;
      iVar5 = iVar5 + 0x157c;
      iVar1 = iVar7 + -1;
      pqVar4 = pqVar4 + 4;
      iVar7 = iVar7 + 1;
    } while (iVar1 < config_blob.reserved0._20_4_ + 9);
  }
  iStack_4 = config_blob.reserved0._20_4_ + 0x11;
  entries = (quest_spawn_entry_t *)0x0;
  if (0 < iStack_4) {
    iVar7 = 0xa604;
    piVar3 = &pqVar2[iVar6].pos_y_block.heading_block.template_id;
    do {
      fVar8 = (float10)(int)entries;
      fVar9 = (float10)fcos((fVar8 * (float10)6.2831855) / (float10)iStack_4);
      piVar3[-3] = (int)(float)(fVar9 * (float10)258.0 + (float10)512.0);
      iVar6 = iVar6 + 1;
      entries = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
      fVar8 = (float10)fsin((fVar8 * (float10)6.2831855) /
                            (float10)(config_blob.reserved0._20_4_ + 0x11));
      piVar3[-2] = (int)(float)(fVar8 * (float10)258.0 + (float10)512.0);
      *piVar3 = 10;
      piVar3[1] = iVar7;
      piVar3[2] = 1;
      iVar7 = iVar7 + 500;
      iStack_4 = config_blob.reserved0._20_4_ + 0x11;
      piVar3 = piVar3 + 6;
    } while ((int)entries < iStack_4);
  }
  if (config_blob.hardcore == '\0') {
    *count = iVar6;
    return;
  }
  config_blob.reserved0._20_4_ = config_blob.reserved0._20_4_ + -4;
  *count = iVar6;
  return;
}



/* quest_build_syntax_terror @ 00436c10 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 8 (Syntax Terror) */

void quest_build_syntax_terror(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  iVar4 = 0;
  iStack_1c = 0;
  if (config_blob.hardcore != '\0') {
    config_blob.reserved0._20_4_ = config_blob.reserved0._20_4_ + 4;
  }
  iStack_18 = 0;
  iStack_10 = 0x5dc;
  iStack_14 = 0x14c9;
  iVar1 = config_blob.reserved0._20_4_;
  do {
    iVar5 = 0;
    if (iVar1 != -9 && -1 < iVar1 + 9) {
      piVar2 = &entries[iVar4].pos_y_block.heading_block.template_id;
      iVar3 = 0x4c5;
      iVar6 = iStack_10;
      do {
        iVar1 = iVar3 * iVar5;
        piVar2[-3] = (int)(float)(((iVar5 * iVar5 * 0x4c + 0xec) * iVar5 + iStack_14 * iStack_18) %
                                  0x380 + 0x40);
        iVar4 = iStack_1c + 1;
        iVar5 = iVar5 + 1;
        piVar2[-2] = (int)(float)((iVar1 + (iStack_18 * iStack_18 * 0x4c + 0x1b) * iStack_18) %
                                  0x380 + 0x40);
        *piVar2 = 7;
        piVar2[1] = iVar6;
        piVar2[2] = 1;
        iVar6 = iVar6 + 300;
        iVar1 = config_blob.reserved0._20_4_;
        piVar2 = piVar2 + 6;
        iVar3 = iVar3 + 0x15;
        iStack_1c = iVar4;
      } while (iVar5 < config_blob.reserved0._20_4_ + 9);
    }
    iStack_14 = iStack_14 + 0x35;
    iStack_18 = iStack_18 + 1;
    iStack_10 = iStack_10 + 30000;
  } while (iStack_14 < 0x159d);
  if (config_blob.hardcore == '\0') {
    *count = iVar4;
    return;
  }
  config_blob.reserved0._20_4_ = iVar1 + -4;
  *count = iVar4;
  return;
}



/* quest_build_spider_spawns @ 00436d70 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 2 (Spider Spawns) */

void quest_build_spider_spawns(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = 128.0;
  (entries->pos_y_block).pos_y = 128.0;
  (entries->pos_y_block).heading_block.template_id = 0x10;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 896.0;
  entries[1].pos_y_block.pos_y = 896.0;
  entries[1].pos_y_block.heading_block.template_id = 0x10;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 896.0;
  entries[2].pos_y_block.pos_y = 128.0;
  entries[2].pos_y_block.heading_block.template_id = 0x10;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = 128.0;
  entries[3].pos_y_block.pos_y = 896.0;
  entries[3].pos_y_block.heading_block.template_id = 0x10;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_x = -64.0;
  entries[4].pos_y_block.pos_y = 512.0;
  entries[4].pos_y_block.heading_block.template_id = 0x38;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 3000;
  entries[4].pos_y_block.heading_block.count = 2;
  entries[5].pos_x = 512.0;
  entries[5].pos_y_block.pos_y = 512.0;
  entries[5].pos_y_block.heading_block.template_id = 10;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 18000;
  entries[5].pos_y_block.heading_block.count = 1;
  entries[6].pos_x = 448.0;
  entries[6].pos_y_block.pos_y = 448.0;
  entries[6].pos_y_block.heading_block.template_id = 0x10;
  entries[6].pos_y_block.heading_block.trigger_time_ms = 0x5014;
  entries[6].pos_y_block.heading_block.count = 1;
  entries[7].pos_x = 576.0;
  entries[7].pos_y_block.pos_y = 448.0;
  entries[7].pos_y_block.heading_block.template_id = 0x10;
  entries[7].pos_y_block.heading_block.trigger_time_ms = 26000;
  entries[7].pos_y_block.heading_block.count = 1;
  entries[8].pos_x = 1088.0;
  entries[8].pos_y_block.pos_y = 512.0;
  entries[8].pos_y_block.heading_block.template_id = 0x38;
  entries[8].pos_y_block.heading_block.trigger_time_ms = 21000;
  entries[8].pos_y_block.heading_block.count = 2;
  entries[9].pos_x = 576.0;
  entries[9].pos_y_block.pos_y = 576.0;
  entries[9].pos_y_block.heading_block.template_id = 0x10;
  entries[9].pos_y_block.heading_block.trigger_time_ms = 0x7b0c;
  entries[9].pos_y_block.heading_block.count = 1;
  entries[10].pos_x = 448.0;
  entries[10].pos_y_block.pos_y = 576.0;
  entries[10].pos_y_block.heading_block.template_id = 0x10;
  entries[10].pos_y_block.heading_block.trigger_time_ms = 22000;
  entries[10].pos_y_block.heading_block.count = 1;
  *count = 0xb;
  return;
}



/* quest_build_two_fronts @ 00436ee0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 4 (Two Fronts) */

void quest_build_two_fronts(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar3 = 0;
  do {
    entries->pos_x = (float)(terrain_texture_width + 0x40);
    (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (entries->pos_y_block).heading_block.template_id = 0x1a;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar3 * 2000 + 1000;
    (entries->pos_y_block).heading_block.count = 1;
    entries[1].pos_x = -64.0;
    entries[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
    entries[1].pos_y_block.heading_block.template_id = 0x1b;
    entries[1].pos_y_block.heading_block.trigger_time_ms = (iVar3 * 5 + 5) * 400;
    entries[1].pos_y_block.heading_block.count = 1;
    if ((iVar3 == 10) || (pqVar1 = entries + 2, iVar4 = iVar2 + 2, iVar3 == 0x14)) {
      entries[2].pos_x = 256.0;
      iVar4 = iVar3 * 2000 + 0x9c4;
      entries[2].pos_y_block.pos_y = 256.0;
      entries[2].pos_y_block.heading_block.template_id = 10;
      entries[2].pos_y_block.heading_block.trigger_time_ms = iVar4;
      entries[2].pos_y_block.heading_block.count = 1;
      entries[3].pos_x = 768.0;
      entries[3].pos_y_block.pos_y = 768.0;
      entries[3].pos_y_block.heading_block.template_id = 7;
      entries[3].pos_y_block.heading_block.trigger_time_ms = iVar4;
      entries[3].pos_y_block.heading_block.count = 1;
      pqVar1 = entries + 4;
      iVar4 = iVar2 + 4;
    }
    iVar2 = iVar4;
    entries = pqVar1;
    if (iVar3 == 0x1e) {
      entries->pos_x = 768.0;
      (entries->pos_y_block).pos_y = 256.0;
      (entries->pos_y_block).heading_block.template_id = 10;
      (entries->pos_y_block).heading_block.trigger_time_ms = 0xf424;
      (entries->pos_y_block).heading_block.count = 1;
      entries[1].pos_x = 256.0;
      entries[1].pos_y_block.pos_y = 768.0;
      entries[1].pos_y_block.heading_block.template_id = 7;
      entries[1].pos_y_block.heading_block.trigger_time_ms = 0xf424;
      entries[1].pos_y_block.heading_block.count = 1;
      iVar2 = iVar2 + 2;
      entries = entries + 2;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x28);
  *count = iVar2;
  return;
}



/* quest_build_survival_of_the_fastest @ 00437060 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 7 (Survival Of The Fastest) */

void quest_build_survival_of_the_fastest(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  quest_spawn_entry_t *pqVar2;
  int *piVar3;
  int iVar4;
  int iStack_c;
  
  pqVar2 = entries;
  iVar4 = 500;
  iStack_c = 0x100;
  piVar3 = &(entries->pos_y_block).heading_block.trigger_time_ms;
  do {
    fVar1 = (float)iStack_c;
    iStack_c = iStack_c + 0x48;
    piVar3[-4] = (int)fVar1;
    piVar3[-3] = 0x43800000;
    piVar3[-1] = 0x10;
    *piVar3 = iVar4;
    piVar3[1] = 1;
    iVar4 = iVar4 + 900;
    piVar3 = piVar3 + 6;
  } while (iStack_c < 0x2b0);
  iStack_c = 0x170c;
  entries = (quest_spawn_entry_t *)0x100;
  piVar3 = &pqVar2[6].pos_y_block.heading_block.trigger_time_ms;
  do {
    fVar1 = (float)(int)entries;
    entries = entries + 3;
    piVar3[-4] = 0x442c0000;
    piVar3[-3] = (int)fVar1;
    piVar3[-1] = 0x10;
    *piVar3 = iStack_c;
    piVar3[1] = 1;
    iStack_c = iStack_c + 900;
    piVar3 = piVar3 + 6;
  } while ((int)entries < 0x2b0);
  entries = (quest_spawn_entry_t *)0x2b0;
  iVar4 = 4;
  iStack_c = 0x2c24;
  piVar3 = &pqVar2[0xc].pos_y_block.heading_block.trigger_time_ms;
  do {
    piVar3[-4] = (int)(float)(int)entries;
    piVar3[-3] = 0x442c0000;
    piVar3[-1] = 0x10;
    *piVar3 = iStack_c;
    piVar3[1] = 1;
    entries = entries + -3;
    iStack_c = iStack_c + 900;
    iVar4 = iVar4 + -1;
    piVar3 = piVar3 + 6;
  } while (iVar4 != 0);
  entries = (quest_spawn_entry_t *)0x2b0;
  iStack_c = 0x3a34;
  iVar4 = 4;
  piVar3 = &pqVar2[0x10].pos_y_block.heading_block.trigger_time_ms;
  do {
    piVar3[-4] = 0x43c80000;
    piVar3[-3] = (int)(float)(int)entries;
    piVar3[-1] = 0x10;
    *piVar3 = iStack_c;
    piVar3[1] = 1;
    entries = entries + -3;
    iStack_c = iStack_c + 900;
    iVar4 = iVar4 + -1;
    piVar3 = piVar3 + 6;
  } while (iVar4 != 0);
  iStack_c = 0x4844;
  iVar4 = 400;
  piVar3 = &pqVar2[0x14].pos_y_block.heading_block.trigger_time_ms;
  do {
    fVar1 = (float)iVar4;
    iVar4 = iVar4 + 0x48;
    piVar3[-4] = (int)fVar1;
    piVar3[-3] = 0x43c80000;
    piVar3[-1] = 0x10;
    *piVar3 = iStack_c;
    piVar3[1] = 1;
    iStack_c = iStack_c + 900;
    piVar3 = piVar3 + 6;
  } while (iVar4 < 0x220);
  pqVar2[0x16].pos_x = 128.0;
  pqVar2[0x16].pos_y_block.pos_y = 128.0;
  pqVar2[0x16].pos_y_block.heading_block.template_id = 0x10;
  pqVar2[0x16].pos_y_block.heading_block.trigger_time_ms = 0x571c;
  pqVar2[0x16].pos_y_block.heading_block.count = 1;
  pqVar2[0x17].pos_x = 896.0;
  pqVar2[0x17].pos_y_block.pos_y = 128.0;
  pqVar2[0x17].pos_y_block.heading_block.template_id = 7;
  pqVar2[0x17].pos_y_block.heading_block.trigger_time_ms = 0x571c;
  pqVar2[0x17].pos_y_block.heading_block.count = 1;
  pqVar2[0x18].pos_x = 128.0;
  pqVar2[0x18].pos_y_block.pos_y = 896.0;
  pqVar2[0x18].pos_y_block.heading_block.template_id = 7;
  pqVar2[0x18].pos_y_block.heading_block.trigger_time_ms = 0x5eec;
  pqVar2[0x18].pos_y_block.heading_block.count = 1;
  pqVar2[0x19].pos_x = 896.0;
  pqVar2[0x19].pos_y_block.pos_y = 896.0;
  pqVar2[0x19].pos_y_block.heading_block.template_id = 0x10;
  pqVar2[0x19].pos_y_block.heading_block.trigger_time_ms = 0x5eec;
  pqVar2[0x19].pos_y_block.heading_block.count = 1;
  *count = 0x1a;
  return;
}



/* quest_build_spideroids @ 004373c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 10 (Spideroids) */

void quest_build_spideroids(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  
  entries->pos_x = 1088.0;
  (entries->pos_y_block).pos_y = 512.0;
  (entries->pos_y_block).heading_block.template_id = 1;
  (entries->pos_y_block).heading_block.trigger_time_ms = 1000;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = -64.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 1;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 3000;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 1088.0;
  entries[2].pos_y_block.pos_y = 256.0;
  entries[2].pos_y_block.heading_block.template_id = 1;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 6000;
  entries[2].pos_y_block.heading_block.count = 1;
  iVar2 = 3;
  if (config_blob.hardcore != '\0') {
    entries[3].pos_x = 1088.0;
    entries[3].pos_y_block.pos_y = 762.0;
    entries[3].pos_y_block.heading_block.template_id = 1;
    entries[3].pos_y_block.heading_block.trigger_time_ms = 9000;
    entries[3].pos_y_block.heading_block.count = 1;
    entries[4].pos_x = 512.0;
    entries[4].pos_y_block.pos_y = 1088.0;
    entries[4].pos_y_block.heading_block.template_id = 1;
    entries[4].pos_y_block.heading_block.trigger_time_ms = 9000;
    entries[4].pos_y_block.heading_block.count = 1;
    iVar2 = 5;
  }
  if (((int)config_blob.reserved0._20_4_ < 2) && (config_blob.hardcore == '\0')) {
    *count = iVar2;
    return;
  }
  pqVar1 = entries + iVar2;
  pqVar1->pos_x = -64.0;
  (pqVar1->pos_y_block).pos_y = 762.0;
  (pqVar1->pos_y_block).heading_block.template_id = 1;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = 9000;
  (pqVar1->pos_y_block).heading_block.count = 1;
  *count = iVar2 + 1;
  return;
}



/* quest_build_evil_zombies_at_large @ 004374a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 6 (Evil Zombies At Large) */

void quest_build_evil_zombies_at_large(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar4 = 0x5dc;
  iVar3 = 4;
  do {
    entries->pos_x = (float)(terrain_texture_width + 0x40);
    (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (entries->pos_y_block).heading_block.template_id = 0x41;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (entries->pos_y_block).heading_block.count = iVar3;
    entries[1].pos_x = -64.0;
    entries[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
    entries[1].pos_y_block.heading_block.template_id = 0x41;
    entries[1].pos_y_block.heading_block.trigger_time_ms = iVar4;
    entries[1].pos_y_block.heading_block.count = iVar3;
    entries[2].pos_x = (float)(terrain_texture_width / 2);
    entries[2].pos_y_block.pos_y = (float)(terrain_texture_width + 0x40);
    entries[2].pos_y_block.heading_block.template_id = 0x41;
    entries[2].pos_y_block.heading_block.trigger_time_ms = iVar4;
    entries[2].pos_y_block.heading_block.count = iVar3;
    iVar2 = iVar2 + 4;
    entries[3].pos_x = (float)(terrain_texture_width / 2);
    entries[3].pos_y_block.pos_y = -64.0;
    entries[3].pos_y_block.heading_block.template_id = 0x41;
    entries[3].pos_y_block.heading_block.trigger_time_ms = iVar4;
    entries[3].pos_y_block.heading_block.count = iVar3;
    iVar4 = iVar4 + 0x157c;
    iVar1 = iVar3 + -3;
    entries = entries + 4;
    iVar3 = iVar3 + 1;
  } while (iVar1 < 10);
  *count = iVar2;
  return;
}



/* quest_build_everred_pastures @ 004375a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 1 (Everred Pastures) */

void quest_build_everred_pastures(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int iVar2;
  quest_spawn_entry_t *pqVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = 0;
  iVar6 = 0;
  do {
    iVar1 = iVar6 + 1;
    entries->pos_x = (float)(terrain_texture_width + 0x40);
    pqVar3 = entries + 4;
    (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (entries->pos_y_block).heading_block.template_id = 0x32;
    iVar2 = iVar6 * 13000 + 0x5dc;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar2;
    (entries->pos_y_block).heading_block.count = iVar1;
    entries[1].pos_x = -64.0;
    entries[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
    entries[1].pos_y_block.heading_block.template_id = 0x33;
    entries[1].pos_y_block.heading_block.trigger_time_ms = iVar2;
    entries[1].pos_y_block.heading_block.count = iVar1;
    entries[2].pos_x = (float)(terrain_texture_width / 2);
    entries[2].pos_y_block.pos_y = (float)(terrain_texture_width + 0x40);
    entries[2].pos_y_block.heading_block.template_id = 0x34;
    entries[2].pos_y_block.heading_block.trigger_time_ms = iVar2;
    entries[2].pos_y_block.heading_block.count = iVar1;
    iVar5 = iVar4 + 4;
    entries[3].pos_x = (float)(terrain_texture_width / 2);
    entries[3].pos_y_block.pos_y = -64.0;
    entries[3].pos_y_block.heading_block.template_id = 0x35;
    entries[3].pos_y_block.heading_block.trigger_time_ms = iVar2;
    entries[3].pos_y_block.heading_block.count = iVar1;
    if (iVar6 == 3) {
      entries[4].pos_x = (float)(terrain_texture_width / 2);
      entries[4].pos_y_block.pos_y = -64.0;
      entries[4].pos_y_block.heading_block.template_id = 0x1b;
      entries[4].pos_y_block.heading_block.trigger_time_ms = 0x9e34;
      entries[4].pos_y_block.heading_block.count = 8;
      iVar5 = iVar4 + 6;
      pqVar3 = entries + 6;
      entries[5].pos_x = (float)(terrain_texture_width / 2);
      entries[5].pos_y_block.pos_y = 1088.0;
      entries[5].pos_y_block.heading_block.template_id = 0x1b;
      entries[5].pos_y_block.heading_block.trigger_time_ms = 0x9e34;
      entries[5].pos_y_block.heading_block.count = 8;
    }
    entries = pqVar3;
    iVar4 = iVar5;
    iVar6 = iVar1;
  } while (iVar1 < 8);
  *count = iVar5;
  return;
}



/* quest_build_lizard_kings @ 00437710 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 2 (Lizard Kings) */

void quest_build_lizard_kings(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int *piVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  
  pqVar1 = entries;
  entries->pos_x = 1152.0;
  (entries->pos_y_block).pos_y = 512.0;
  iVar3 = 0x5dc;
  (entries->pos_y_block).heading_block.template_id = 0x11;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = -128.0;
  entries[1].pos_y_block.pos_y = 512.0;
  entries[1].pos_y_block.heading_block.template_id = 0x11;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 1152.0;
  entries[2].pos_y_block.pos_y = 896.0;
  entries[2].pos_y_block.heading_block.template_id = 0x11;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[2].pos_y_block.heading_block.count = 1;
  entries = (quest_spawn_entry_t *)0x0;
  piVar2 = &pqVar1[3].pos_y_block.heading_block.template_id;
  do {
    fVar4 = (float10)(int)entries;
    fVar5 = fVar4 * (float10)0.34906587;
    fVar6 = (float10)fcos(fVar5);
    piVar2[-3] = (int)(float)(fVar6 * (float10)256.0 + (float10)512.0);
    fVar5 = (float10)fsin(fVar5);
    piVar2[-2] = (int)(float)(fVar5 * (float10)256.0 + (float10)512.0);
    *piVar2 = 0x31;
    piVar2[1] = iVar3;
    piVar2[2] = 1;
    iVar3 = iVar3 + 900;
    entries = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
    ((quest_spawn_entry_heading_block_t *)(piVar2 + -1))->heading =
         (float)(fVar4 * (float10)-0.34906587);
    piVar2 = piVar2 + 6;
  } while ((int)entries < 0x1c);
  *count = 0x1f;
  return;
}



/* quest_build_sweep_stakes @ 00437810 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 5 (Sweep Stakes) */

void quest_build_sweep_stakes(quest_spawn_entry_trigger_cursor_t *cursor,int *count)

{
  int iVar1;
  quest_spawn_entry_trigger_cursor_t *pqVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  int iStack_18;
  
  iVar3 = 2000;
  iVar4 = 2000;
  cursor = (quest_spawn_entry_trigger_cursor_t *)&(cursor->next).heading;
  do {
    iVar1 = crt_rand();
    iStack_18 = 0x54;
    fVar5 = (float10)(iVar1 % 0x264) * (float10)0.01;
    fVar6 = (float10)fcos(fVar5);
    fVar5 = (float10)fsin(fVar5);
    pqVar2 = cursor;
    do {
      fVar7 = (float10)iStack_18;
      iStack_18 = iStack_18 + 0x2a;
      pqVar2[-1].next.pos_x = (float)(fVar7 * (float10)(float)fVar6) + 512.0;
      pqVar2[-1].next.pos_y = (float)(fVar7 * fVar5 + (float10)512.0);
      pqVar2[-1].next.template_id = 0x36;
      pqVar2->trigger_time_ms = iVar3;
      pqVar2->count = 1;
      fVar7 = (float10)fpatan((float10)pqVar2[-1].next.pos_y - (float10)512.0,
                              (float10)pqVar2[-1].next.pos_x - (float10)512.0);
      pqVar2[-1].next.heading = (float)(fVar7 - (float10)1.5707964);
      pqVar2 = pqVar2 + 1;
    } while (iStack_18 < 0xfc);
    iVar1 = iVar4;
    if (iVar4 < 600) {
      iVar1 = 600;
    }
    iVar4 = iVar4 + -0x50;
    iVar3 = iVar3 + iVar1;
    cursor = cursor + 4;
  } while (0x2d0 < iVar4);
  *count = 0x40;
  return;
}



/* quest_build_deja_vu @ 00437920 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 9 (Deja vu) */

void quest_build_deja_vu(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  int iStack_18;
  
  iVar4 = 2000;
  iStack_18 = 2000;
  piVar3 = &(entries->pos_y_block).heading_block.trigger_time_ms;
  do {
    iVar1 = crt_rand();
    entries = (quest_spawn_entry_t *)0x54;
    fVar5 = (float10)(iVar1 % 0x264) * (float10)0.01;
    fVar6 = (float10)fcos(fVar5);
    fVar5 = (float10)fsin(fVar5);
    piVar2 = piVar3;
    do {
      fVar7 = (float10)(int)entries;
      entries = (quest_spawn_entry_t *)
                ((int)&entries[1].pos_y_block.heading_block.trigger_time_ms + 2);
      piVar2[-4] = (int)((float)(fVar7 * (float10)(float)fVar6) + 512.0);
      piVar2[-3] = (int)(float)(fVar7 * fVar5 + (float10)512.0);
      piVar2[-1] = 0xd;
      *piVar2 = iVar4;
      piVar2[1] = 1;
      piVar2 = piVar2 + 6;
    } while ((int)entries < 0xfc);
    iVar4 = iVar4 + iStack_18;
    iStack_18 = iStack_18 + -0x50;
    piVar3 = piVar3 + 0x18;
  } while (0x230 < iStack_18);
  *count = 0x48;
  return;
}



/* quest_build_target_practice @ 00437a00 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 3 (Target Practice) */

void quest_build_target_practice(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  
  iVar4 = 2000;
  iVar6 = 2000;
  piVar5 = &(entries->pos_y_block).heading_block.trigger_time_ms;
  do {
    iVar2 = crt_rand();
    fVar1 = (float)(iVar2 % 0x264) * 0.01;
    uVar3 = crt_rand();
    uVar3 = uVar3 & 0x80000007;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
    }
    fVar7 = (float10)(int)((uVar3 + 2) * 0x20);
    fVar8 = (float10)fcos((float10)fVar1);
    fVar9 = (float10)fsin((float10)fVar1);
    piVar5[-4] = (int)((float)(fVar8 * fVar7) + 512.0);
    piVar5[-3] = (int)(float)(fVar9 * fVar7 + (float10)512.0);
    piVar5[-1] = 0x36;
    *piVar5 = iVar4;
    piVar5[1] = 1;
    fVar7 = (float10)fpatan((float10)(float)piVar5[-3] - (float10)512.0,
                            (float10)(float)piVar5[-4] - (float10)512.0);
    ((quest_spawn_entry_heading_block_t *)(piVar5 + -2))->heading =
         (float)(fVar7 - (float10)1.5707964);
    iVar2 = iVar6;
    if (iVar6 < 0x44c) {
      iVar2 = 0x44c;
    }
    iVar6 = iVar6 + -0x32;
    iVar4 = iVar4 + iVar2;
    piVar5 = piVar5 + 6;
  } while (500 < iVar6);
  *count = 0x1e;
  return;
}



/* quest_build_major_alien_breach @ 00437af0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 1 (Major Alien Breach) */

void quest_build_major_alien_breach(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar1 = 4000;
  iVar3 = 0;
  do {
    entries->pos_x = 1088.0;
    (entries->pos_y_block).pos_y = 512.0;
    (entries->pos_y_block).heading_block.template_id = 0x20;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar1;
    (entries->pos_y_block).heading_block.count = 2;
    iVar2 = iVar2 + 2;
    entries[1].pos_x = 512.0;
    entries[1].pos_y_block.pos_y = -64.0;
    entries[1].pos_y_block.heading_block.template_id = 0x20;
    entries[1].pos_y_block.heading_block.trigger_time_ms = iVar1;
    entries[1].pos_y_block.heading_block.count = 2;
    iVar1 = iVar1 + (2000 - iVar3);
    entries = entries + 2;
    if (iVar1 < 1000) {
      iVar1 = 1000;
    }
    iVar3 = iVar3 + 0xf;
  } while (iVar3 < 0x5dc);
  *count = iVar2;
  return;
}



/* quest_build_land_of_lizards @ 00437ba0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 2 Quest 8 (Land Of Lizards) */

void quest_build_land_of_lizards(quest_spawn_entry_t *entries,int *count)

{
  entries->pos_x = 256.0;
  (entries->pos_y_block).pos_y = 256.0;
  (entries->pos_y_block).heading_block.template_id = 0xe;
  (entries->pos_y_block).heading_block.trigger_time_ms = 2000;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 768.0;
  entries[1].pos_y_block.pos_y = 256.0;
  entries[1].pos_y_block.heading_block.template_id = 0xe;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 12000;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 256.0;
  entries[2].pos_y_block.pos_y = 768.0;
  entries[2].pos_y_block.heading_block.template_id = 0xe;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 22000;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = 768.0;
  entries[3].pos_y_block.pos_y = 768.0;
  entries[3].pos_y_block.heading_block.template_id = 0xe;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 32000;
  entries[3].pos_y_block.heading_block.count = 1;
  *count = 4;
  return;
}



/* quest_build_the_lizquidation @ 00437c70 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 6 (The Lizquidation) */

void quest_build_the_lizquidation(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  quest_spawn_entry_t *pqVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = 0;
  do {
    iVar1 = iVar5 * 8000 + 0x5dc;
    pqVar2 = entries + iVar3;
    pqVar2->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar2->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar2->pos_y_block).heading_block.template_id = 0x2e;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar1;
    (pqVar2->pos_y_block).heading_block.count = iVar5 + 6;
    pqVar2 = entries + iVar3 + 1;
    pqVar2->pos_x = -64.0;
    iVar4 = iVar3 + 2;
    (pqVar2->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar2->pos_y_block).heading_block.template_id = 0x2e;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar1;
    (pqVar2->pos_y_block).heading_block.count = iVar5 + 6;
    if (iVar5 == 4) {
      pqVar2 = entries + iVar4;
      pqVar2->pos_x = (float)(terrain_texture_width + 0x80);
      iVar4 = iVar3 + 3;
      (pqVar2->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
      (pqVar2->pos_y_block).heading_block.template_id = 0x2b;
      (pqVar2->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
      (pqVar2->pos_y_block).heading_block.count = 2;
    }
    iVar5 = iVar5 + 1;
    iVar3 = iVar4;
  } while (iVar5 < 10);
  *count = iVar4;
  return;
}



/* quest_build_zombie_time @ 00437d70 */

/* quest builder for Tier 4 Quest 2 (Zombie Time) */

void __cdecl quest_build_zombie_time(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0x5dc;
  do {
    pqVar1 = entries + iVar2;
    pqVar1->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x41;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar3;
    (pqVar1->pos_y_block).heading_block.count = 8;
    pqVar1 = entries + iVar2 + 1;
    pqVar1->pos_x = -64.0;
    iVar2 = iVar2 + 2;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x41;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar3;
    iVar3 = iVar3 + 8000;
    (pqVar1->pos_y_block).heading_block.count = 8;
  } while (iVar3 < 0x17cdc);
  *count = iVar2;
  return;
}



/* quest_build_frontline_assault @ 00437e10 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 1 Quest 4 (Frontline Assault) */

void quest_build_frontline_assault(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  iVar6 = 0x9c4;
  iVar4 = 2;
  do {
    entries->pos_x = (float)(terrain_texture_width / 2);
    (entries->pos_y_block).pos_y = 1088.0;
    if (iVar4 < 5) {
      (entries->pos_y_block).heading_block.template_id = 0x26;
    }
    else if (iVar4 < 10) {
      (entries->pos_y_block).heading_block.template_id = 0x1a;
    }
    else {
      (entries->pos_y_block).heading_block.template_id = 0x26;
    }
    iVar2 = iVar4 * iVar6 + -5000;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar2;
    (entries->pos_y_block).heading_block.count = 1;
    pqVar1 = entries + 1;
    iVar3 = iVar5 + 1;
    if (4 < iVar4) {
      entries[1].pos_x = -64.0;
      entries[1].pos_y_block.pos_y = -64.0;
      entries[1].pos_y_block.heading_block.template_id = 0x26;
      entries[1].pos_y_block.heading_block.trigger_time_ms = iVar2;
      entries[1].pos_y_block.heading_block.count = 1;
      pqVar1 = entries + 2;
      iVar3 = iVar5 + 2;
    }
    iVar5 = iVar3;
    entries = pqVar1;
    if (10 < iVar4) {
      entries->pos_x = 1088.0;
      (entries->pos_y_block).pos_y = -64.0;
      (entries->pos_y_block).heading_block.template_id = 0x26;
      (entries->pos_y_block).heading_block.trigger_time_ms = iVar2;
      (entries->pos_y_block).heading_block.count = 1;
      iVar5 = iVar5 + 1;
      entries = entries + 1;
    }
    if (iVar4 == 10) {
      entries->pos_x = 1088.0;
      (entries->pos_y_block).pos_y = 512.0;
      iVar3 = (iVar6 * 5 + -0x9c4) * 2;
      (entries->pos_y_block).heading_block.template_id = 0x29;
      (entries->pos_y_block).heading_block.trigger_time_ms = iVar3;
      (entries->pos_y_block).heading_block.count = 1;
      entries[1].pos_x = -64.0;
      entries[1].pos_y_block.pos_y = 512.0;
      entries[1].pos_y_block.heading_block.template_id = 0x29;
      entries[1].pos_y_block.heading_block.trigger_time_ms = iVar3;
      entries[1].pos_y_block.heading_block.count = 1;
      iVar5 = iVar5 + 2;
      entries = entries + 2;
    }
    iVar6 = iVar6 + -0x32;
    if (iVar6 < 0x708) {
      iVar6 = 0x708;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x16);
  *count = iVar5;
  return;
}



/* quest_build_the_collaboration @ 00437f30 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 4 (The Collaboration) */

void quest_build_the_collaboration(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  
  iVar3 = 0;
  iVar5 = 0x5dc;
  do {
    lVar6 = __ftol();
    iVar2 = (int)lVar6;
    pqVar1 = entries + iVar3;
    pqVar1->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x1a;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = iVar2;
    pqVar1 = entries + iVar3 + 1;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width + 0x40);
    pqVar1->pos_x = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x1b;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = iVar2;
    pqVar1 = entries + iVar3 + 2;
    pqVar1->pos_x = -64.0;
    iVar4 = iVar3 + 3;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x1c;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = iVar2;
    iVar3 = iVar3 + 4;
    pqVar1 = entries + iVar4;
    pqVar1->pos_x = 512.0;
    (pqVar1->pos_y_block).pos_y = -64.0;
    (pqVar1->pos_y_block).heading_block.template_id = 0x41;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    iVar5 = iVar5 + 11000;
    (pqVar1->pos_y_block).heading_block.count = iVar2;
  } while (iVar5 < 0x2b55c);
  *count = iVar3;
  return;
}



/* quest_build_the_blighting @ 00438050 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 1 (The Blighting) */

void quest_build_the_blighting(quest_spawn_entry_t *entries,int *count)

{
  uint uVar1;
  quest_spawn_entry_t *pqVar2;
  quest_spawn_entry_t *pqVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uStack_8;
  
  entries->pos_x = (float)(terrain_texture_width + 0x80);
  iVar5 = 0x1a;
  (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).heading_block.template_id = 0x2b;
  (entries->pos_y_block).heading_block.trigger_time_ms = 0x5dc;
  (entries->pos_y_block).heading_block.count = 2;
  entries[1].pos_x = -128.0;
  entries[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
  entries[1].pos_y_block.heading_block.template_id = 0x2b;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 0x5dc;
  entries[1].pos_y_block.heading_block.count = 2;
  entries[2].pos_y_block.pos_y = 128.0;
  entries[2].pos_x = 896.0;
  entries[2].pos_y_block.heading_block.template_id = 7;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 2000;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_y_block.pos_y = 128.0;
  entries[3].pos_x = 128.0;
  entries[3].pos_y_block.heading_block.template_id = 7;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 2000;
  entries[3].pos_y_block.heading_block.count = 1;
  entries[4].pos_y_block.pos_y = 896.0;
  entries[4].pos_x = 128.0;
  entries[4].pos_y_block.heading_block.template_id = 7;
  entries[4].pos_y_block.heading_block.trigger_time_ms = 2000;
  entries[4].pos_y_block.heading_block.count = 1;
  entries[5].pos_y_block.pos_y = 896.0;
  entries[5].pos_x = 896.0;
  entries[5].pos_y_block.heading_block.template_id = 7;
  entries[5].pos_y_block.heading_block.trigger_time_ms = 2000;
  entries[5].pos_y_block.heading_block.count = 1;
  iVar7 = 6;
  iVar6 = 4000;
  uStack_8 = 0;
  pqVar3 = entries + 6;
  do {
    uVar1 = uStack_8 & 0x80000001;
    if ((int)uVar1 < 0) {
      uVar1 = (uVar1 - 1 | 0xfffffffe) + 1;
    }
    if ((uStack_8 == 2) || (pqVar2 = pqVar3, uStack_8 == 4)) {
      pqVar3->pos_x = -128.0;
      iVar7 = iVar7 + 1;
      pqVar2 = pqVar3 + 1;
      (pqVar3->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
      (pqVar3->pos_y_block).heading_block.template_id = 0x2b;
      (pqVar3->pos_y_block).heading_block.trigger_time_ms = iVar6;
      (pqVar3->pos_y_block).heading_block.count = 4;
    }
    if ((uStack_8 == 3) || (pqVar3 = pqVar2, uStack_8 == 5)) {
      pqVar2->pos_x = 1152.0;
      iVar7 = iVar7 + 1;
      pqVar3 = pqVar2 + 1;
      (pqVar2->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
      (pqVar2->pos_y_block).heading_block.template_id = 0x2b;
      (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar6;
      (pqVar2->pos_y_block).heading_block.count = 4;
    }
    if (uVar1 == 0) {
      iVar5 = 0x1a;
    }
    else if (uVar1 == 1) {
      iVar5 = 0x1c;
    }
    iVar4 = (int)uStack_8 % 5;
    if (iVar4 == 0) {
      pqVar3->pos_x = (float)(terrain_texture_width + 0x40);
      (pqVar3->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
LAB_00438283:
      (pqVar3->pos_y_block).heading_block.template_id = iVar5;
      (pqVar3->pos_y_block).heading_block.trigger_time_ms = iVar6;
      (pqVar3->pos_y_block).heading_block.count = 0xc;
      iVar7 = iVar7 + 1;
      pqVar3 = pqVar3 + 1;
      iVar6 = iVar6 + 15000;
    }
    else {
      if (iVar4 == 1) {
        pqVar3->pos_x = -64.0;
        (pqVar3->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
        goto LAB_00438283;
      }
      if (iVar4 == 2) {
        (pqVar3->pos_y_block).pos_y = (float)(terrain_texture_width + 0x40);
LAB_00438281:
        pqVar3->pos_x = (float)(terrain_texture_width / 2);
        goto LAB_00438283;
      }
      if (iVar4 == 3) {
        (pqVar3->pos_y_block).pos_y = -64.0;
        goto LAB_00438281;
      }
    }
    iVar6 = iVar6 + 1000;
    uStack_8 = uStack_8 + 1;
    if (7 < (int)uStack_8) {
      *count = iVar7;
      return;
    }
  } while( true );
}



/* quest_build_the_annihilation @ 004382c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 9 (The Annihilation) */

void quest_build_the_annihilation(quest_spawn_entry_t *entries,int *count)

{
  int *piVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 500;
  entries->pos_x = 128.0;
  uVar3 = 0;
  iVar5 = 0;
  piVar1 = &entries[1].pos_y_block.heading_block.template_id;
  (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).heading_block.template_id = 0x2b;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 2;
  do {
    piVar1[-2] = (int)(float)(iVar5 / 0xc + 0x80);
    if ((uVar3 & 1) == 0) {
      piVar1[-3] = 0x44500000;
    }
    else {
      piVar1[-3] = 0x44600000;
    }
    *piVar1 = 7;
    piVar1[1] = iVar4;
    piVar1[2] = 1;
    iVar4 = iVar4 + 500;
    iVar5 = iVar5 + 0x300;
    piVar1 = piVar1 + 6;
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 0xc);
  bVar2 = false;
  iVar5 = 0;
  iVar4 = 45000;
  piVar1 = &entries[0xd].pos_y_block.heading_block.template_id;
  do {
    piVar1[-2] = (int)(float)(iVar5 / 0xc + 0x80);
    if (bVar2) {
      piVar1[-3] = 0x44500000;
    }
    else {
      piVar1[-3] = 0x44600000;
    }
    *piVar1 = 7;
    piVar1[1] = iVar4;
    piVar1[2] = 1;
    piVar1 = piVar1 + 6;
    iVar4 = iVar4 + 300;
    bVar2 = (bool)(bVar2 ^ 1);
    iVar5 = iVar5 + 0x300;
  } while (iVar4 < 0xbdd8);
  *count = 0x19;
  return;
}



/* quest_build_the_massacre @ 004383e0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 5 (The Massacre) */

void quest_build_the_massacre(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  
  iVar6 = 0x5dc;
  uVar2 = 0;
  iVar4 = 0;
  do {
    pqVar1 = entries + 1;
    entries->pos_x = (float)(terrain_texture_width + 0x40);
    iVar5 = iVar4 + 1;
    uVar3 = uVar2 & 0x80000001;
    bVar7 = uVar3 == 0;
    (entries->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (entries->pos_y_block).heading_block.template_id = 0x41;
    (entries->pos_y_block).heading_block.trigger_time_ms = iVar6;
    (entries->pos_y_block).heading_block.count = uVar2 + 3;
    if ((int)uVar3 < 0) {
      bVar7 = (uVar3 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar7) {
      pqVar1->pos_x = (float)(terrain_texture_width + 0x80);
      iVar5 = iVar4 + 2;
      pqVar1 = entries + 2;
      entries[1].pos_y_block.pos_y = (float)(terrain_texture_width / 2);
      entries[1].pos_y_block.heading_block.template_id = 0x2b;
      entries[1].pos_y_block.heading_block.trigger_time_ms = iVar6;
      entries[1].pos_y_block.heading_block.count = uVar2 + 1;
    }
    iVar6 = iVar6 + 5000;
    entries = pqVar1;
    uVar2 = uVar2 + 1;
    iVar4 = iVar5;
  } while (iVar6 < 0x1656c);
  *count = iVar5;
  return;
}



/* quest_build_the_killing @ 004384a0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 3 (The Killing) */

void quest_build_the_killing(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  int iVar2;
  int iVar3;
  quest_spawn_entry_t *pqVar4;
  quest_spawn_entry_t *pqVar5;
  int iVar6;
  int iStack_4;
  
  iVar2 = 0;
  iVar6 = 2000;
  iVar3 = 0x1a;
  iStack_4 = 0;
  pqVar5 = entries;
  do {
    crt_rand();
    iVar1 = iStack_4 % 3;
    if (iVar1 == 0) {
      iVar3 = 0x1a;
    }
    else if (iVar1 == 1) {
      iVar3 = 0x1b;
    }
    else if (iVar1 == 2) {
      iVar3 = 0x1c;
    }
    crt_rand();
    iVar1 = iStack_4 % 5;
    pqVar4 = pqVar5;
    if (iVar1 == 0) {
      pqVar5->pos_x = (float)(terrain_texture_width + 0x40);
LAB_00438544:
      entries = (quest_spawn_entry_t *)(terrain_texture_width / 2);
      (pqVar5->pos_y_block).pos_y = (float)(int)entries;
      (pqVar5->pos_y_block).heading_block.template_id = iVar3;
      (pqVar5->pos_y_block).heading_block.trigger_time_ms = iVar6;
      (pqVar5->pos_y_block).heading_block.count = 0xc;
LAB_004386cc:
      iVar2 = iVar2 + 1;
      pqVar5 = pqVar4 + 1;
      iVar6 = iVar6 + 5000;
    }
    else {
      if (iVar1 == 1) {
        pqVar5->pos_x = -64.0;
        goto LAB_00438544;
      }
      if (iVar1 == 2) {
        (pqVar5->pos_y_block).pos_y = (float)(terrain_texture_width + 0x40);
        pqVar5->pos_x = (float)(terrain_texture_width / 2);
        (pqVar5->pos_y_block).heading_block.template_id = iVar3;
        (pqVar5->pos_y_block).heading_block.trigger_time_ms = iVar6;
        (pqVar5->pos_y_block).heading_block.count = 0xc;
        goto LAB_004386cc;
      }
      if (iVar1 == 3) {
        (pqVar5->pos_y_block).pos_y = -64.0;
        pqVar5->pos_x = (float)(terrain_texture_width / 2);
        (pqVar5->pos_y_block).heading_block.template_id = iVar3;
        (pqVar5->pos_y_block).heading_block.trigger_time_ms = iVar6;
        (pqVar5->pos_y_block).heading_block.count = 0xc;
        goto LAB_004386cc;
      }
      if (iVar1 == 4) {
        iVar1 = crt_rand();
        (pqVar5->pos_y_block).pos_y = (float)(iVar1 % 0x300 + 0x80);
        iVar1 = crt_rand();
        pqVar5->pos_x = (float)(iVar1 % 0x300 + 0x80);
        (pqVar5->pos_y_block).heading_block.template_id = 7;
        (pqVar5->pos_y_block).heading_block.trigger_time_ms = iVar6;
        (pqVar5->pos_y_block).heading_block.count = 3;
        iVar1 = crt_rand();
        pqVar5[1].pos_y_block.pos_y = (float)(iVar1 % 0x300 + 0x80);
        iVar1 = crt_rand();
        pqVar4 = pqVar5 + 2;
        iVar2 = iVar2 + 2;
        pqVar5[1].pos_x = (float)(iVar1 % 0x300 + 0x80);
        pqVar5[1].pos_y_block.heading_block.template_id = 7;
        pqVar5[1].pos_y_block.heading_block.trigger_time_ms = iVar6 + 1000;
        pqVar5[1].pos_y_block.heading_block.count = 3;
        iVar1 = crt_rand();
        pqVar5[2].pos_y_block.pos_y = (float)(iVar1 % 0x300 + 0x80);
        iVar1 = crt_rand();
        pqVar4->pos_x = (float)(iVar1 % 0x300 + 0x80);
        pqVar5[2].pos_y_block.heading_block.template_id = 7;
        pqVar5[2].pos_y_block.heading_block.trigger_time_ms = iVar6 + 2000;
        pqVar5[2].pos_y_block.heading_block.count = 3;
        goto LAB_004386cc;
      }
    }
    iVar6 = iVar6 + 1000;
    iStack_4 = iStack_4 + 1;
    if (9 < iStack_4) {
      *count = iVar2;
      return;
    }
  } while( true );
}



/* quest_build_lizard_zombie_pact @ 00438700 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 3 (Lizard Zombie Pact) */

void quest_build_lizard_zombie_pact(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iStack_4;
  
  iVar5 = 0x5dc;
  iStack_4 = 0;
  iVar3 = 0;
  do {
    pqVar1 = entries + iVar3;
    pqVar1->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x41;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = 6;
    pqVar1 = entries + iVar3 + 1;
    pqVar1->pos_x = -64.0;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x41;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
    (pqVar1->pos_y_block).heading_block.count = 6;
    iVar4 = iVar3 + 2;
    if (iStack_4 % 5 == 0) {
      pqVar1 = entries + iVar4;
      iVar2 = iStack_4 / 5;
      pqVar1->pos_x = 356.0;
      (pqVar1->pos_y_block).pos_y = (float)(iVar2 * 0xb4 + 0x100);
      (pqVar1->pos_y_block).heading_block.template_id = 0xc;
      (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
      (pqVar1->pos_y_block).heading_block.count = iVar2 + 1;
      iVar4 = iVar3 + 4;
      pqVar1 = entries + iVar3 + 3;
      pqVar1->pos_x = 356.0;
      (pqVar1->pos_y_block).pos_y = (float)(iVar2 * 0xb4 + 0x180);
      (pqVar1->pos_y_block).heading_block.template_id = 0xc;
      (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
      (pqVar1->pos_y_block).heading_block.count = iVar2 + 2;
    }
    iVar5 = iVar5 + 7000;
    iStack_4 = iStack_4 + 1;
    iVar3 = iVar4;
  } while (iVar5 < 0x1bb5c);
  *count = iVar4;
  return;
}



/* quest_build_lizard_raze @ 00438840 */

/* quest builder for Tier 3 Quest 8 (Lizard Raze) */

void __cdecl quest_build_lizard_raze(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0x5dc;
  iVar2 = 0;
  do {
    iVar3 = iVar2;
    pqVar1 = entries + iVar3;
    pqVar1->pos_x = (float)(terrain_texture_width + 0x40);
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x2e;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (pqVar1->pos_y_block).heading_block.count = 6;
    pqVar1 = entries + iVar3 + 1;
    pqVar1->pos_x = -64.0;
    (pqVar1->pos_y_block).pos_y = (float)(terrain_texture_width / 2);
    (pqVar1->pos_y_block).heading_block.template_id = 0x2e;
    (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar4;
    iVar4 = iVar4 + 6000;
    (pqVar1->pos_y_block).heading_block.count = 6;
    iVar2 = iVar3 + 2;
  } while (iVar4 < 0x1656c);
  pqVar1 = entries + iVar3 + 2;
  pqVar1->pos_x = 128.0;
  (pqVar1->pos_y_block).pos_y = 256.0;
  (pqVar1->pos_y_block).heading_block.template_id = 0xc;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = 10000;
  (pqVar1->pos_y_block).heading_block.count = 1;
  pqVar1 = entries + iVar3 + 3;
  pqVar1->pos_x = 128.0;
  (pqVar1->pos_y_block).pos_y = 384.0;
  (pqVar1->pos_y_block).heading_block.template_id = 0xc;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = 10000;
  (pqVar1->pos_y_block).heading_block.count = 1;
  pqVar1 = entries + iVar3 + 4;
  pqVar1->pos_x = 128.0;
  (pqVar1->pos_y_block).pos_y = 512.0;
  (pqVar1->pos_y_block).heading_block.template_id = 0xc;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = 10000;
  (pqVar1->pos_y_block).heading_block.count = 1;
  *count = iVar3 + 5;
  return;
}



/* quest_build_surrounded_by_reptiles @ 00438940 */

/* quest builder for Tier 3 Quest 5 (Surrounded By Reptiles) */

void __cdecl quest_build_surrounded_by_reptiles(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  quest_spawn_entry_t *pqVar2;
  int iVar3;
  int iVar4;
  int local_4;
  
  iVar3 = 0;
  local_4 = 0;
  iVar4 = 1000;
  pqVar2 = entries;
  do {
    fVar1 = (float)local_4;
    pqVar2->pos_x = 256.0;
    iVar3 = iVar3 + 2;
    local_4 = local_4 + 0x200;
    fVar1 = fVar1 * 0.2 + 256.0;
    (pqVar2->pos_y_block).pos_y = fVar1;
    (pqVar2->pos_y_block).heading_block.template_id = 0xd;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (pqVar2->pos_y_block).heading_block.count = 1;
    pqVar2[1].pos_x = 768.0;
    pqVar2[1].pos_y_block.pos_y = fVar1;
    pqVar2[1].pos_y_block.heading_block.template_id = 0xd;
    pqVar2[1].pos_y_block.heading_block.trigger_time_ms = iVar4;
    pqVar2[1].pos_y_block.heading_block.count = 1;
    iVar4 = iVar4 + 800;
    pqVar2 = pqVar2 + 2;
  } while (iVar4 < 5000);
  local_4 = 0;
  iVar4 = 8000;
  pqVar2 = entries + iVar3;
  do {
    fVar1 = (float)local_4;
    (pqVar2->pos_y_block).pos_y = 256.0;
    iVar3 = iVar3 + 2;
    local_4 = local_4 + 0x200;
    fVar1 = fVar1 * 0.2 + 256.0;
    pqVar2->pos_x = fVar1;
    (pqVar2->pos_y_block).heading_block.template_id = 0xd;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (pqVar2->pos_y_block).heading_block.count = 1;
    pqVar2[1].pos_y_block.pos_y = 768.0;
    pqVar2[1].pos_x = fVar1;
    pqVar2[1].pos_y_block.heading_block.template_id = 0xd;
    pqVar2[1].pos_y_block.heading_block.trigger_time_ms = iVar4;
    pqVar2[1].pos_y_block.heading_block.count = 1;
    iVar4 = iVar4 + 800;
    pqVar2 = pqVar2 + 2;
  } while (iVar4 < 12000);
  *count = iVar3;
  return;
}



/* quest_build_the_unblitzkrieg @ 00438a40 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 6 (The Unblitzkrieg) */

void quest_build_the_unblitzkrieg(quest_spawn_entry_t *entries,int *count)

{
  quest_spawn_entry_t *pqVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  
  iVar5 = 500;
  iVar6 = 0;
  piVar7 = &(entries->pos_y_block).heading_block.template_id;
  uVar3 = 0;
  do {
    uVar8 = uVar3;
    piVar7[-3] = 0x444e0000;
    iVar2 = iVar6 / 10;
    iVar6 = iVar6 + 0x270;
    piVar7[-2] = (int)(float)(iVar2 + 200);
    *piVar7 = (-(uint)((uVar8 & 1) != 0) & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 0x708;
    piVar7 = piVar7 + 6;
    uVar3 = uVar8 + 1;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 1].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = (int)(float)(0x338 - iVar6 / 10);
    piVar7[-2] = 0x444e0000;
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 0x5dc;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  pqVar1 = entries + uVar8 + 0xb;
  bVar4 = 0;
  pqVar1->pos_x = 512.0;
  (pqVar1->pos_y_block).pos_y = 512.0;
  (pqVar1->pos_y_block).heading_block.trigger_time_ms = iVar5;
  (pqVar1->pos_y_block).heading_block.template_id = 7;
  (pqVar1->pos_y_block).heading_block.count = 1;
  piVar7 = &entries[uVar8 + 0xc].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = 0x43480000;
    piVar7[-2] = (int)(float)(0x338 - iVar6 / 10);
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 0x4b0;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 0x16].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = (int)(float)(iVar6 / 10 + 200);
    piVar7[-2] = 0x43480000;
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 800;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 0x20].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = 0x444e0000;
    piVar7[-2] = (int)(float)(iVar6 / 10 + 200);
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 800;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 0x2a].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = (int)(float)(0x338 - iVar6 / 10);
    piVar7[-2] = 0x444e0000;
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 700;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 0x34].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = 0x43480000;
    piVar7[-2] = (int)(float)(0x338 - iVar6 / 10);
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 700;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  iVar6 = 0;
  bVar4 = 0;
  piVar7 = &entries[uVar8 + 0x3e].pos_y_block.heading_block.template_id;
  do {
    piVar7[-3] = (int)(float)(iVar6 / 10 + 200);
    piVar7[-2] = 0x43480000;
    iVar6 = iVar6 + 0x270;
    *piVar7 = (-(uint)bVar4 & 6) + 7;
    piVar7[1] = iVar5;
    piVar7[2] = 1;
    iVar5 = iVar5 + 800;
    bVar4 = bVar4 ^ 1;
    piVar7 = piVar7 + 6;
  } while (iVar6 < 0x1860);
  *count = uVar8 + 0x48;
  return;
}



/* quest_build_the_end_of_all @ 00438e10 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 4 Quest 10 (The End of All) */

void quest_build_the_end_of_all(quest_spawn_entry_t *entries,int *count)

{
  float fVar1;
  bool bVar2;
  quest_spawn_entry_t *pqVar3;
  int *piVar4;
  int iVar5;
  quest_spawn_entry_t *pqVar6;
  int iVar7;
  float10 fVar8;
  float10 fVar9;
  
  pqVar3 = entries;
  entries->pos_x = 128.0;
  (entries->pos_y_block).pos_y = 128.0;
  (entries->pos_y_block).heading_block.template_id = 0x3c;
  (entries->pos_y_block).heading_block.trigger_time_ms = 3000;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_x = 896.0;
  entries[1].pos_y_block.pos_y = 128.0;
  entries[1].pos_y_block.heading_block.template_id = 0x3c;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 6000;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_x = 128.0;
  entries[2].pos_y_block.pos_y = 896.0;
  entries[2].pos_y_block.heading_block.template_id = 0x3c;
  entries[2].pos_y_block.heading_block.trigger_time_ms = 9000;
  entries[2].pos_y_block.heading_block.count = 1;
  entries[3].pos_x = 896.0;
  entries[3].pos_y_block.pos_y = 896.0;
  entries[3].pos_y_block.heading_block.template_id = 0x3c;
  entries[3].pos_y_block.heading_block.trigger_time_ms = 12000;
  entries[3].pos_y_block.heading_block.count = 1;
  entries = (quest_spawn_entry_t *)0x0;
  iVar5 = 13000;
  piVar4 = &pqVar3[4].pos_y_block.heading_block.template_id;
  do {
    pqVar6 = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
    fVar8 = (float10)fcos((float10)(int)entries * (float10)1.0471976);
    piVar4[-3] = (int)(float)(fVar8 * (float10)80.0 + (float10)512.0);
    fVar8 = (float10)fsin((float10)(int)entries * (float10)1.0471976);
    piVar4[-2] = (int)(float)(fVar8 * (float10)80.0 + (float10)512.0);
    *piVar4 = 7;
    piVar4[1] = iVar5;
    piVar4[2] = 1;
    iVar5 = iVar5 + 300;
    piVar4 = piVar4 + 6;
    entries = pqVar6;
  } while (iVar5 < 0x39d0);
  iVar5 = 18000;
  pqVar3[10].pos_x = 512.0;
  pqVar3[10].pos_y_block.pos_y = 512.0;
  pqVar3[10].pos_y_block.heading_block.template_id = 0xb;
  entries = (quest_spawn_entry_t *)0x100;
  pqVar3[10].pos_y_block.heading_block.trigger_time_ms = (int)pqVar6 * 300 + 13000;
  pqVar3[10].pos_y_block.heading_block.count = 1;
  bVar2 = false;
  piVar4 = &pqVar3[0xb].pos_y_block.heading_block.template_id;
  do {
    if (bVar2) {
      piVar4[-3] = 0x44900000;
    }
    else {
      piVar4[-3] = 0xc3000000;
    }
    fVar1 = (float)(int)entries;
    entries = (quest_spawn_entry_t *)&entries[5].pos_y_block.heading_block;
    bVar2 = (bool)(bVar2 ^ 1);
    piVar4[-2] = (int)fVar1;
    *piVar4 = 0x3c;
    piVar4[1] = iVar5;
    piVar4[2] = 2;
    iVar5 = iVar5 + 1000;
    piVar4 = piVar4 + 6;
  } while ((int)entries < 0x300);
  iVar5 = 43000;
  entries = (quest_spawn_entry_t *)0x0;
  iVar7 = 0x15;
  piVar4 = &pqVar3[0xf].pos_y_block.heading_block.template_id;
  do {
    fVar8 = (float10)(int)entries;
    entries = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
    fVar8 = fVar8 * (float10)1.0471976 + (float10)0.5235988;
    fVar9 = (float10)fcos(fVar8);
    piVar4[-3] = (int)(float)(fVar9 * (float10)80.0 + (float10)512.0);
    fVar8 = (float10)fsin(fVar8);
    piVar4[-2] = (int)(float)(fVar8 * (float10)80.0 + (float10)512.0);
    *piVar4 = 7;
    piVar4[1] = iVar5;
    piVar4[2] = 1;
    iVar5 = iVar5 + 300;
    piVar4 = piVar4 + 6;
  } while (iVar5 < 0xaf00);
  if (config_blob.hardcore != '\0') {
    entries = (quest_spawn_entry_t *)0x0;
    iVar5 = 0xf550;
    iVar7 = 0x21;
    piVar4 = &pqVar3[0x15].pos_y_block.heading_block.template_id;
    do {
      fVar8 = (float10)(int)entries;
      entries = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
      fVar8 = (fVar8 + (float10)1.0) * (float10)0.5235988;
      fVar9 = (float10)fcos(fVar8);
      piVar4[-3] = (int)(float)(fVar9 * (float10)180.0 + (float10)512.0);
      fVar8 = (float10)fsin(fVar8);
      piVar4[-2] = (int)(float)(fVar8 * (float10)180.0 + (float10)512.0);
      *piVar4 = 7;
      piVar4[1] = iVar5;
      piVar4[2] = 1;
      iVar5 = iVar5 + 500;
      piVar4 = piVar4 + 6;
    } while (iVar5 < 0x10cc0);
  }
  bVar2 = false;
  iVar5 = 48000;
  entries = (quest_spawn_entry_t *)0x100;
  piVar4 = &pqVar3[iVar7].pos_y_block.heading_block.template_id;
  do {
    if (bVar2) {
      piVar4[-3] = 0x44900000;
    }
    else {
      piVar4[-3] = 0xc3000000;
    }
    fVar1 = (float)(int)entries;
    entries = (quest_spawn_entry_t *)&entries[5].pos_y_block.heading_block;
    bVar2 = (bool)(bVar2 ^ 1);
    piVar4[-2] = (int)fVar1;
    *piVar4 = 0x3c;
    piVar4[1] = iVar5;
    piVar4[2] = 2;
    iVar5 = iVar5 + 1000;
    piVar4 = piVar4 + 6;
  } while ((int)entries < 0x300);
  *count = iVar7 + 4;
  return;
}



/* quest_build_spiders_inc @ 004390d0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* quest builder for Tier 3 Quest 7 (Spiders Inc.) */

void quest_build_spiders_inc(quest_spawn_entry_t *entries,int *count)

{
  int iVar1;
  quest_spawn_entry_t *pqVar2;
  quest_spawn_entry_t *pqVar3;
  int iVar4;
  int iVar5;
  
  pqVar3 = entries;
  (entries->pos_y_block).pos_y = (float)(terrain_texture_width + 0x40);
  entries->pos_x = (float)(terrain_texture_width / 2);
  (entries->pos_y_block).heading_block.template_id = 0x38;
  (entries->pos_y_block).heading_block.trigger_time_ms = 500;
  (entries->pos_y_block).heading_block.count = 1;
  entries[1].pos_y_block.pos_y = (float)(terrain_texture_width + 0x40);
  entries[1].pos_x = (float)(terrain_texture_width / 2 + 0x40);
  entries[1].pos_y_block.heading_block.template_id = 0x38;
  entries[1].pos_y_block.heading_block.trigger_time_ms = 500;
  entries[1].pos_y_block.heading_block.count = 1;
  entries[2].pos_y_block.pos_y = -64.0;
  iVar4 = 17000;
  entries = (quest_spawn_entry_t *)0x0;
  pqVar3[2].pos_x = (float)(terrain_texture_width / 2);
  pqVar3[2].pos_y_block.heading_block.template_id = 0x40;
  pqVar3[2].pos_y_block.heading_block.trigger_time_ms = 500;
  pqVar3[2].pos_y_block.heading_block.count = 4;
  iVar5 = 3;
  do {
    iVar1 = (int)entries / 2 + 3;
    pqVar2 = pqVar3 + iVar5;
    (pqVar2->pos_y_block).pos_y = (float)(terrain_texture_width + 0x40);
    pqVar2->pos_x = (float)(terrain_texture_width / 2);
    (pqVar2->pos_y_block).heading_block.template_id = 0x38;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (pqVar2->pos_y_block).heading_block.count = iVar1;
    pqVar2 = pqVar3 + iVar5 + 1;
    (pqVar2->pos_y_block).pos_y = -64.0;
    iVar5 = iVar5 + 2;
    pqVar2->pos_x = (float)(terrain_texture_width / 2);
    (pqVar2->pos_y_block).heading_block.template_id = 0x38;
    (pqVar2->pos_y_block).heading_block.trigger_time_ms = iVar4;
    (pqVar2->pos_y_block).heading_block.count = iVar1;
    iVar4 = iVar4 + 6000;
    entries = (quest_spawn_entry_t *)((int)&entries->pos_x + 1);
  } while (iVar4 < 0x1a1f8);
  *count = iVar5;
  return;
}



/* quest_database_init @ 00439230 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* builds the quest metadata table and registers quest builders */

void quest_database_init(void)

{
  int local_8;
  int local_4;
  
  local_8 = 0;
  local_4 = 0;
  quest_meta_init_entry(&quest_selected_meta,1,1,s_Land_Hostile_00477adc);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 120000;
  quest_meta_cursor->builder = quest_build_land_hostile;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Minor_Alien_Breach_00477ac8);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 120000;
  quest_meta_cursor->builder = quest_build_minor_alien_breach;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Target_Practice_00477ab8);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 65000;
  quest_meta_cursor->builder = quest_build_target_practice;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Frontline_Assault_00477aa4);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_frontline_assault;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Alien_Dens_00477a98);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_alien_dens;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Random_Factor_00477a84);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_random_factor;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Spider_Wave_Syndrome_00477a6c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 240000;
  quest_meta_cursor->builder = quest_build_spider_wave_syndrome;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Alien_Squads_00477a5c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_alien_squads;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Nesting_Grounds_00477a4c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 240000;
  quest_meta_cursor->builder = quest_build_nesting_grounds;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_8_legged_Terror_00477a3c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 240000;
  quest_meta_cursor->builder = quest_build_8_legged_terror;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Everred_Pastures_00477a28);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_everred_pastures;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Spider_Spawns_00477a18);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_spider_spawns;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Arachnoid_Farm_00477a08);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 240000;
  quest_meta_cursor->builder = quest_build_arachnoid_farm;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Two_Fronts_004779fc);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 240000;
  quest_meta_cursor->builder = quest_build_two_fronts;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Sweep_Stakes_004779ec);
  quest_meta_cursor->start_weapon_id = 6;
  quest_meta_cursor->time_limit_ms = 35000;
  quest_meta_cursor->builder = quest_build_sweep_stakes;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Evil_Zombies_At_Large_004779d4);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_evil_zombies_at_large;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Survival_Of_The_Fastest_004779bc);
  quest_meta_cursor->start_weapon_id = 5;
  quest_meta_cursor->time_limit_ms = 120000;
  quest_meta_cursor->builder = quest_build_survival_of_the_fastest;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Land_Of_Lizards_004779ac);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_land_of_lizards;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Ghost_Patrols_0047799c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_ghost_patrols;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Spideroids_00477990);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 360000;
  quest_meta_cursor->builder = quest_build_spideroids;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Blighting_00477980);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_blighting;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Lizard_Kings_00477970);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 180000;
  quest_meta_cursor->builder = quest_build_lizard_kings;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Killing_00477964);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_killing;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Hidden_Evil_00477958);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_hidden_evil;
  quest_monster_vision_meta = quest_meta_cursor;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Surrounded_By_Reptiles_00477940);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_surrounded_by_reptiles;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Lizquidation_0047792c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_lizquidation;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Spiders_Inc__0047791c);
  quest_meta_cursor->start_weapon_id = 0xb;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_spiders_inc;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Lizard_Raze_00477910);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_lizard_raze;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Deja_vu_00477908);
  quest_meta_cursor->start_weapon_id = 6;
  quest_meta_cursor->time_limit_ms = 120000;
  quest_meta_cursor->builder = quest_build_deja_vu;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Zombie_Masters_004778f8);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_zombie_masters;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Major_Alien_Breach_004778e4);
  quest_meta_cursor->start_weapon_id = 0x12;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_major_alien_breach;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Zombie_Time_004778d8);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_zombie_time;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Lizard_Zombie_Pact_004778c4);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_lizard_zombie_pact;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Collaboration_004778b0);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 360000;
  quest_meta_cursor->builder = quest_build_the_collaboration;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Massacre_004778a0);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_massacre;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Unblitzkrieg_0047788c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 600000;
  quest_meta_cursor->builder = quest_build_the_unblitzkrieg;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Gauntlet_00477880);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_gauntlet;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Syntax_Terror_00477870);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_syntax_terror;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Annihilation_0047785c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 300000;
  quest_meta_cursor->builder = quest_build_the_annihilation;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_End_of_All_0047784c);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_end_of_all;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Beating_00477840);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_beating;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Spanking_Of_The_Dead_00477824);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_spanking_of_the_dead;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Fortress_00477814);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_fortress;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Gang_Wars_00477804);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_gang_wars;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Knee_deep_in_the_Dead_004777ec);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_knee_deep_in_the_dead;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Cross_Fire_004777e0);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_cross_fire;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Army_of_Three_004777d0);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_army_of_three;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Monster_Blues_004777c0);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_monster_blues;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_Nagolipoli_004777b4);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_nagolipoli;
  quest_database_advance_slot(&local_4,&local_8);
  quest_meta_init_entry
            (&quest_selected_meta + local_8 + local_4 * 10,local_4 + 1,local_8 + 1,
             s_The_Gathering_004777a4);
  quest_meta_cursor->start_weapon_id = 1;
  quest_meta_cursor->time_limit_ms = 480000;
  quest_meta_cursor->builder = quest_build_the_gathering;
  quest_database_advance_slot(&local_4,&local_8);
  quest_selected_meta.unlock_weapon_id = 2;
  perk_entry_0_cost = 3;
  perk_entry_0_prereq = 0;
  perk_entry_1_cost = 8;
  _DAT_00484804 = 0;
  _DAT_00484830 = 5;
  _DAT_0048485c = 0;
  _DAT_00484888 = 6;
  _DAT_004848b4 = 0;
  _DAT_004848e0 = 0xc;
  _DAT_0048490c = 0;
  _DAT_00484938 = 9;
  _DAT_00484964 = 0;
  _DAT_00484990 = 0x15;
  _DAT_004849bc = 0;
  _DAT_004849e8 = 7;
  _DAT_00484a14 = 0;
  _DAT_00484a40 = 4;
  _DAT_00484a6c = 0;
  _DAT_00484a98 = 0xb;
  _DAT_00484ac4 = 0;
  _DAT_00484af0 = 10;
  _DAT_00484b1c = 0;
  _DAT_00484b48 = 0xd;
  _DAT_00484b74 = 0;
  _DAT_00484ba0 = 0xf;
  _DAT_00484bcc = 0;
  _DAT_00484bf8 = 0x12;
  _DAT_00484c24 = 0;
  _DAT_00484c50 = 0x14;
  _DAT_00484c7c = 0;
  _DAT_00484ca8 = 0x13;
  _DAT_00484cd4 = 0;
  _DAT_00484d00 = 0xe;
  _DAT_00484d2c = 0;
  _DAT_00484d58 = 0x11;
  _DAT_00484d84 = 0;
  _DAT_00484db0 = 0x16;
  _DAT_00484ddc = 0;
  _DAT_00484e08 = 0x17;
  quest_selected_meta.unlock_perk_id = perk_id_antiperk;
  perk_entry_0_type_id = perk_id_antiperk;
  perk_entry_0_level_req = 0x1c;
  perk_entry_1_type_id = perk_id_antiperk;
  _DAT_00484800 = 0x1d;
  _DAT_0048482c = perk_id_antiperk;
  _DAT_00484858 = 0x1e;
  _DAT_00484884 = perk_id_antiperk;
  _DAT_004848b0 = 0x1f;
  _DAT_004848dc = perk_id_antiperk;
  _DAT_00484908 = 0x20;
  _DAT_00484934 = perk_id_antiperk;
  _DAT_00484960 = 0x21;
  _DAT_0048498c = perk_id_antiperk;
  _DAT_004849b8 = 0x22;
  _DAT_004849e4 = perk_id_antiperk;
  _DAT_00484a10 = 0x23;
  _DAT_00484a3c = perk_id_antiperk;
  _DAT_00484a68 = 0x24;
  _DAT_00484a94 = perk_id_antiperk;
  _DAT_00484ac0 = 0x25;
  _DAT_00484aec = perk_id_antiperk;
  _DAT_00484b18 = 0x26;
  _DAT_00484b44 = perk_id_antiperk;
  _DAT_00484b70 = 0x27;
  _DAT_00484b9c = perk_id_antiperk;
  _DAT_00484bc8 = 0x28;
  _DAT_00484bf4 = perk_id_antiperk;
  _DAT_00484c20 = 0x29;
  _DAT_00484c4c = perk_id_antiperk;
  _DAT_00484c78 = 0x2a;
  _DAT_00484ca4 = perk_id_antiperk;
  _DAT_00484cd0 = 0x2b;
  _DAT_00484cfc = perk_id_antiperk;
  _DAT_00484d28 = 0x2c;
  _DAT_00484d54 = perk_id_antiperk;
  _DAT_00484d80 = 0x2d;
  _DAT_00484dac = perk_id_antiperk;
  _DAT_00484dd8 = 0x2e;
  _DAT_00484e04 = perk_id_antiperk;
  _DAT_00484e34 = 0x1f;
  _DAT_00484e30 = perk_id_antiperk;
  _DAT_00484e60 = 0;
  _DAT_00484e5c = 0x2f;
  _DAT_00484e8c = 0;
  _DAT_00484e88 = 0x30;
  _DAT_00484eb8 = 0x1e;
  _DAT_00484eb4 = perk_id_antiperk;
  _DAT_00484ee4 = 0;
  _DAT_00484ee0 = 0x31;
  _DAT_00484f10 = 0;
  _DAT_00484f0c = 0x32;
  _DAT_00484f3c = 0;
  _DAT_00484f38 = perk_id_antiperk;
  _DAT_00484f68 = 0;
  _DAT_00484f64 = 0x33;
  _DAT_00484f94 = 0;
  _DAT_00484f90 = 0x34;
  _DAT_00484fc0 = 0x1c;
  _DAT_00484fbc = perk_id_antiperk;
  return;
}



/* quest_start_selected @ 0043a790 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* resets quest state, selects quest metadata, and runs its builder */

void __cdecl quest_start_selected(int tier,int index)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  creature_reset_all();
  quest_spawn_count = 0;
  quest_spawn_timeline = 0;
  quest_elapsed_timer_ms = 0;
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
  uVar1 = crt_rand();
  highscore_active_record.reserved0._0_4_ = uVar1 & 0xfee050f;
  projectile_reset_pools();
  player_state_table.pos_x = (float)terrain_texture_width * 0.5;
  player_state_table.pos_y = (float)terrain_texture_height * 0.5;
  iVar4 = index + -0xb + tier * 10;
  terrain_generate(&quest_selected_meta + iVar4);
  weapon_assign_player(0,(&quest_selected_meta)[iVar4].start_weapon_id);
  weapon_assign_player(1,(&quest_selected_meta)[iVar4].start_weapon_id);
  console_printf(&console_log_queue,s_Setup_tier__d_quest__d__00477aec,tier,index);
  if ((&quest_selected_meta)[iVar4].builder == (quest_builder_fn_t)0x0) {
    quest_build_fallback(&quest_spawn_table,&quest_spawn_count);
  }
  else {
    (*(&quest_selected_meta)[iVar4].builder)(&quest_spawn_table,&quest_spawn_count);
  }
  iVar6 = 0;
  iVar4 = 0;
  _DAT_00486fd4 = 0;
  quest_active_wave_index = 0;
  if (0 < quest_spawn_count) {
    piVar2 = &quest_spawn_table.pos_y_block.heading_block.count;
    iVar3 = quest_spawn_count;
    do {
      if (((config_blob.hardcore != '\0') && (iVar5 = *piVar2, 1 < iVar5)) && (piVar2[-2] != 0x3c))
      {
        if (piVar2[-2] == 0x2b) {
          iVar5 = iVar5 + 2;
        }
        else {
          iVar5 = iVar5 + 8;
        }
        *piVar2 = iVar5;
      }
      iVar6 = iVar6 + *piVar2;
      if (iVar4 < piVar2[-1]) {
        iVar4 = piVar2[-1];
      }
      piVar2 = piVar2 + 6;
      iVar3 = iVar3 + -1;
      _DAT_00486fd4 = iVar6;
      quest_active_wave_index = iVar4;
    } while (iVar3 != 0);
  }
  return;
}


