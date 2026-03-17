/* perk_prompt_update_and_render @ 00403550 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates perk prompt timer, animates transforms, and renders the prompt text */

void perk_prompt_update_and_render(void)

{
  IGrim2D_vtbl *pIVar1;
  char *pcVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float y;
  char acStack_80 [128];
  
  if ((demo_mode_active == '\0') && (config_blob.reserved0._24_4_ != 2)) {
    if ((perk_pending_count < 1) || (game_state_id != 9)) {
      perk_prompt_timer = perk_prompt_timer - frame_dt_ms;
      if (perk_prompt_timer < 0) {
        perk_prompt_timer = 0;
      }
    }
    else {
      perk_prompt_timer = perk_prompt_timer + frame_dt_ms;
      if (200 < perk_prompt_timer) {
        perk_prompt_timer = 200;
      }
    }
    if ((config_blob.full_version != '\0') && (0 < perk_prompt_timer)) {
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)perk_prompt_timer * 0.005);
      pcVar2 = input_key_name(config_blob.key_pick_perk);
      crt_sprintf(acStack_80,s_Press__s_to_pick_a_perk_00471488,pcVar2);
      y = _perk_prompt_origin_y + 8.0;
      pIVar1 = grim_interface_ptr->vtable;
      pcVar2 = acStack_80;
      iVar3 = (*pIVar1->grim_measure_text_width)(acStack_80);
      (*pIVar1->grim_draw_text_small)((float)((config_blob.screen_width - iVar3) + -0x10),y,pcVar2);
    }
    ui_element_back_button = 1;
    fVar4 = ((float10)1.0 - (float10)perk_prompt_timer * (float10)0.005) * (float10)-1.5707964;
    fVar5 = (float10)fcos(fVar4);
    _perk_prompt_transform_cos = (float)fVar5;
    fVar4 = (float10)fsin((float10)(float)fVar4);
    _perk_prompt_transform_sin_neg = (float)-fVar4;
    _perk_prompt_transform_sin = (float)fVar4;
    _perk_prompt_transform_cos_2 = (float)fVar5;
    ui_element_render((ui_element_t *)&ui_element_back_button);
  }
  return;
}



/* perks_generate_choices @ 004045a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* builds the current perk choice list */

void perks_generate_choices(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar5 = 0;
  puVar6 = &perk_choice_ids;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
LAB_004045be:
  if ((((iVar5 == 0) && (quest_stage_major == quest_monster_vision_meta->tier)) &&
      (quest_stage_minor == quest_monster_vision_meta->index)) &&
     (iVar3 = perk_count_get(perk_id_monster_vision), iVar3 == 0)) {
    iVar5 = 1;
    perk_choice_ids = perk_id_monster_vision;
  }
  iVar3 = 0;
LAB_00404603:
  do {
    iVar3 = iVar3 + 1;
    iVar1 = perk_select_random();
    iVar2 = perk_id_pyromaniac;
    (&perk_choice_ids)[iVar5] = iVar1;
    if (iVar1 == iVar2) {
      if (player_state_table.weapon_id != 8) goto LAB_00404603;
    }
    iVar2 = perk_count_get(perk_id_death_clock);
    if (((iVar2 == 0) ||
        ((((((iVar2 = (&perk_choice_ids)[iVar5], iVar2 != perk_id_jinxed &&
             (iVar2 != perk_id_breathing_room)) &&
            ((iVar2 != perk_id_grim_deal &&
             ((iVar2 != perk_id_highlander && (iVar2 != perk_id_fatal_lottery)))))) &&
           (iVar2 != perk_id_unknown_deprecated)) &&
          (((iVar2 != perk_id_ammunition_within && (iVar2 != perk_id_infernal_contract)) &&
           (iVar2 != perk_id_regeneration)))) &&
         (((iVar2 != perk_id_greater_regeneration && (iVar2 != perk_id_thick_skinned)) &&
          (iVar2 != perk_id_bandage)))))) &&
       ((((iVar2 = (&perk_choice_ids)[iVar5], iVar2 != perk_id_jinxed &&
          (iVar2 != perk_id_ammunition_within)) &&
         ((iVar2 != perk_id_anxious_loader && (iVar2 != perk_id_monster_vision)))) ||
        (iVar2 = crt_rand(), ((byte)iVar2 & 3) != 1)))) {
      if ((10000 < iVar3) && (((&perk_meta_table)[(&perk_choice_ids)[iVar5]].flags & 4) != 0))
      break;
      piVar4 = &perk_choice_ids;
      for (iVar2 = 0; iVar2 < iVar5; iVar2 = iVar2 + 1) {
        if (*piVar4 == (&perk_choice_ids)[iVar5]) goto LAB_00404603;
        piVar4 = piVar4 + 1;
      }
      if (((((&perk_meta_table)[(&perk_choice_ids)[iVar5]].flags & 4) != 0) ||
          (player_state_table.perk_counts[(&perk_choice_ids)[iVar5]] < 1)) || (29999 < iVar3))
      break;
    }
  } while( true );
  if (24999 < iVar3) {
    console_printf(&console_log_queue,s_Perk_Randomizer_failed_to_genera_00471afc);
  }
  iVar5 = iVar5 + 1;
  if (6 < iVar5) {
    if (config_blob.reserved0._24_4_ == 8) {
      perk_choice_ids = perk_id_sharpshooter;
      perk_choice_slot_1 = perk_id_long_distance_runner;
      _perk_choice_slot_2 = perk_id_evil_eyes;
      _perk_choice_slot_3 = perk_id_radioactive;
      _perk_choice_slot_4 = perk_id_fastshot;
      _perk_choice_slot_5 = perk_id_fastshot;
      _perk_choice_slot_6 = perk_id_fastshot;
    }
    return;
  }
  goto LAB_004045be;
}



/* perk_apply @ 004055e0 */

/* applies perk effects and increments perk counter */

void __cdecl perk_apply(int perk_id)

{
  float fVar1;
  uint uVar2;
  float *pfVar3;
  int iVar4;
  int *piVar5;
  creature_t *pcVar6;
  int iVar7;
  bool bVar8;
  longlong lVar9;
  
  sfx_play(sfx_ui_bonus);
  bVar8 = perk_id == perk_id_instant_winner;
  player_state_table.perk_counts[perk_id] = player_state_table.perk_counts[perk_id] + 1;
  iVar4 = config_blob.reserved0._20_4_;
  if (bVar8) {
    player_state_table.experience = player_state_table.experience + 0x9c4;
  }
  else if (perk_id == perk_id_fatal_lottery) {
    uVar2 = crt_rand();
    iVar4 = config_blob.reserved0._20_4_;
    if ((uVar2 & 1) == 0) {
      player_state_table.experience = player_state_table.experience + 10000;
    }
    else {
      player_state_table.health = -1.0;
    }
  }
  else if (perk_id == perk_id_lifeline_50_50) {
    bVar8 = false;
    pcVar6 = &creature_pool;
    do {
      if ((((bVar8) && (pcVar6->active != '\0')) && (pcVar6->health <= 500.0)) &&
         ((pcVar6->flags & 4) == 0)) {
        pcVar6->active = '\0';
        effect_spawn_burst(&pcVar6->pos_x,4);
      }
      pcVar6 = pcVar6 + 1;
      bVar8 = (bool)(bVar8 ^ 1);
      iVar4 = config_blob.reserved0._20_4_;
    } while ((int)pcVar6 < 0x4aa338);
  }
  else if (perk_id == perk_id_thick_skinned) {
    if (0 < (int)config_blob.reserved0._20_4_) {
      pfVar3 = &player_state_table.health;
      iVar7 = config_blob.reserved0._20_4_;
      do {
        if ((0.0 < *pfVar3) &&
           (fVar1 = *pfVar3 - *pfVar3 * 0.33333334, *pfVar3 = fVar1, fVar1 <= 0.0)) {
          *pfVar3 = 1.0;
        }
        pfVar3 = pfVar3 + 0xd8;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  else if (perk_id == perk_id_breathing_room) {
    if (0 < (int)config_blob.reserved0._20_4_) {
      pfVar3 = &player_state_table.health;
      iVar7 = config_blob.reserved0._20_4_;
      do {
        iVar7 = iVar7 + -1;
        *pfVar3 = *pfVar3 - *pfVar3 * 0.6666667;
        pfVar3 = pfVar3 + 0xd8;
      } while (iVar7 != 0);
    }
    pfVar3 = &creature_pool.hitbox_size;
    do {
      if (((creature_t *)(pfVar3 + -4))->active != '\0') {
        *pfVar3 = *pfVar3 - frame_dt;
      }
      pfVar3 = pfVar3 + 0x26;
    } while ((int)pfVar3 < 0x4aa348);
    bonus_spawn_guard = 0;
  }
  else if (perk_id == perk_id_random_weapon) {
    iVar4 = 0;
    do {
      iVar7 = weapon_pick_random_available();
      iVar4 = iVar4 + 1;
      if ((iVar7 != 1) && (iVar7 != player_state_table.weapon_id)) break;
    } while (iVar4 < 100);
    weapon_assign_player(0,iVar7);
    iVar4 = config_blob.reserved0._20_4_;
  }
  if (perk_id == perk_id_infernal_contract) {
    player_state_table.level = player_state_table.level + 3;
    perk_pending_count = perk_pending_count + 3;
    if (0.0 < player_state_table.health) {
      player_state_table.health = 0.1;
    }
    if (0.0 < player2_health) {
      player2_health = 0.1;
    }
  }
  if (perk_id == perk_id_grim_deal) {
    lVar9 = __ftol();
    player_state_table.health = -1.0;
    player_state_table.experience = player_state_table.experience + (int)lVar9;
  }
  if ((perk_id == perk_id_ammo_maniac) && (iVar7 = 0, 0 < iVar4)) {
    piVar5 = &player_state_table.weapon_id;
    do {
      weapon_assign_player(iVar7,*piVar5);
      iVar7 = iVar7 + 1;
      piVar5 = piVar5 + 0xd8;
      iVar4 = config_blob.reserved0._20_4_;
    } while (iVar7 < (int)config_blob.reserved0._20_4_);
  }
  iVar7 = perk_id_regeneration;
  if (perk_id == perk_id_death_clock) {
    player_state_table.perk_counts[perk_id_greater_regeneration] = 0;
    player_state_table.perk_counts[iVar7] = 0;
    if (0 < iVar4) {
      pfVar3 = &player_state_table.health;
      iVar7 = iVar4;
      do {
        if (0.0 < *pfVar3) {
          *pfVar3 = 100.0;
        }
        pfVar3 = pfVar3 + 0xd8;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  if ((perk_id == perk_id_bandage) && (iVar7 = 0, 0 < iVar4)) {
    pfVar3 = &player_state_table.health;
    do {
      iVar4 = crt_rand();
      fVar1 = ((float)(iVar4 % 0x32) + 1.0) * *pfVar3;
      *pfVar3 = fVar1;
      if (100.0 < fVar1) {
        *pfVar3 = 100.0;
      }
      effect_spawn_burst(pfVar3 + -4,8);
      iVar7 = iVar7 + 1;
      pfVar3 = pfVar3 + 0xd8;
      iVar4 = config_blob.reserved0._20_4_;
    } while (iVar7 < (int)config_blob.reserved0._20_4_);
  }
  if ((perk_id == perk_id_my_favourite_weapon) && (0 < iVar4)) {
    piVar5 = &player_state_table.clip_size;
    do {
      iVar4 = iVar4 + -1;
      *piVar5 = (int)((float)*piVar5 + 2.0);
      piVar5 = piVar5 + 0xd8;
    } while (iVar4 != 0);
  }
  if (perk_id == perk_id_plaguebearer) {
    player_plaguebearer_active = 1;
  }
  return;
}



/* perk_selection_screen_update @ 00405be0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* perk selection screen: list choices, preview text, and selection handling */

void perk_selection_screen_update(void)

{
  int x;
  undefined4 *puVar1;
  int iVar2;
  float unaff_EBX;
  int *piVar3;
  int *item;
  longlong lVar4;
  int y;
  int w;
  char cVar5;
  undefined4 uStack_28;
  uint local_24;
  float local_20;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_4;
  
  gameplay_render_world();
  ui_elements_update_and_render();
  local_4 = perk_screen_pos_y + perk_screen_offset_y;
  local_20 = 19.0;
  uStack_28 = (float)(uint)(uint3)uStack_28;
  local_24 = 5;
  local_14 = local_4 + 40.0;
  local_18 = perk_screen_panel_x + perk_screen_panel_offset_x + perk_screen_panel_y + 180.0 + 44.0;
  local_10 = local_18;
  local_c = local_14;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  w = 0x20;
  y = 0x80;
  iVar2 = texture_perk_frame_id;
  lVar4 = __ftol();
  x = (int)lVar4;
  lVar4 = __ftol();
  ui_draw_textured_quad((int)lVar4,x,y,w,iVar2);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.5);
  if (player_state_table.perk_counts[perk_id_perk_master] < 1) {
    if (0 < player_state_table.perk_counts[perk_id_perk_expert]) {
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,local_18 - 26.0,local_14 - 8.0,
                 s_extra_perk_sponsored_by_the_Perk_00472018);
      local_24 = 6;
    }
  }
  else {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,local_18 - 28.0,local_14 - 8.0,
               s_extra_perks_sponsored_by_the_Per_00472040);
    local_24 = 7;
  }
  if (player_state_table.perk_counts[perk_id_perk_expert] < 1) {
    local_14 = local_14 + 50.0;
  }
  else {
    local_14 = local_14 + 40.0;
    local_20 = 18.0;
  }
  if (((byte)perk_selection_screen_flags & 1) == 0) {
    perk_selection_screen_flags._0_1_ = (byte)perk_selection_screen_flags | 1;
    perk_color_normal_r = 0x3e8c8c8d;
    perk_color_normal_g = 0x3f34b4b5;
    perk_color_normal_b = 0x3f70f0f1;
    perk_color_normal_a = 0x3f19999a;
    crt_atexit(&DAT_00406170);
  }
  if (((byte)perk_selection_screen_flags & 2) == 0) {
    perk_selection_screen_flags._0_1_ = (byte)perk_selection_screen_flags | 2;
    perk_color_hover_r = 0x3e8c8c8d;
    perk_color_hover_g = 0x3f34b4b5;
    perk_color_hover_b = 0x3f70f0f1;
    perk_color_hover_a = 0x3f800000;
    crt_atexit(&DAT_00406160);
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  if (((byte)perk_selection_screen_flags & 4) == 0) {
    perk_selection_screen_flags._0_1_ = (byte)perk_selection_screen_flags | 4;
    iVar2 = 10;
    puVar1 = &DAT_004800b4;
    do {
      *(undefined1 *)((int)puVar1 + -6) = 1;
      *puVar1 = 0x3f800000;
      puVar1[-3] = 0;
      *(undefined1 *)(puVar1 + -2) = 0;
      *(undefined1 *)((int)puVar1 + -7) = 0;
      puVar1[-1] = 0;
      puVar1 = puVar1 + 4;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    crt_atexit(&DAT_00406150);
  }
  iVar2 = 0;
  if (local_24 != 0) {
    item = &DAT_004800a8;
    piVar3 = &perk_choice_ids;
    do {
      *item = (int)(&perk_meta_table)[*piVar3].name;
      ui_menu_item_update(&local_18,item);
      if ((char)item[1] != '\0') {
        uStack_28 = (float)CONCAT13(1,(uint3)uStack_28);
        perk_selection_index = iVar2;
      }
      local_14 = local_14 + local_20;
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
      item = item + 4;
    } while (iVar2 < (int)local_24);
  }
  local_14 = local_14 + 32.0;
  if (5 < local_24) {
    local_14 = local_14 - 20.0;
  }
  local_18 = local_18 - 28.0;
  cVar5 = '?';
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  (*grim_interface_ptr->vtable->grim_draw_text_small)
            (unaff_EBX + 16.0,uStack_28,
             (&perk_meta_table)[(&perk_choice_ids)[perk_selection_index]].description);
  if (((byte)perk_selection_screen_flags & 8) == 0) {
    perk_selection_screen_flags._0_1_ = (byte)perk_selection_screen_flags | 8;
    ui_button_cancel_field_6 = 1;
    ui_button_cancel_clicked = 0;
    ui_button_cancel_hover = 0;
    _ui_button_cancel_alpha = 0x3f800000;
    _ui_button_cancel_field_c = 0;
    ui_btn_cancel_label = (char *)0x0;
    ui_button_cancel_field_4 = 0;
    ui_button_cancel_field_5 = 0;
    _ui_button_cancel_field_8 = 0;
    crt_atexit(&ui_button_cancel_atexit);
  }
  ui_btn_cancel_label = s_cancel;
  if (((byte)perk_selection_screen_flags & 0x10) == 0) {
    perk_selection_screen_flags._0_1_ = (byte)perk_selection_screen_flags | 0x10;
    ui_button_select_field_6 = 1;
    ui_button_select_clicked = 0;
    ui_button_select_hover = 0;
    _ui_button_select_alpha = 0x3f800000;
    _ui_button_select_field_c = 0;
    _DAT_00480820 = (char *)0x0;
    ui_button_select_field_4 = 0;
    ui_button_select_field_5 = 0;
    _ui_button_select_field_8 = 0;
    crt_atexit(&ui_button_select_atexit);
  }
  _DAT_00480820 = s_select;
  iVar2 = ui_button_update((float *)&stack0xffffffcc,(ui_button_t *)&ui_button_cancel);
  if ((char)iVar2 != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 9;
  }
  perk_prompt_update_and_render();
  ui_cursor_render();
  if (((cVar5 != '\0') && (-1 < perk_selection_index)) &&
     ((&perk_choice_clicked_flags)[perk_selection_index * 0x10] != '\0')) {
    sfx_play(sfx_ui_buttonclick);
    perk_apply((&perk_choice_ids)[perk_selection_index]);
    perk_pending_count = perk_pending_count + -1;
    ui_transition_direction = 0;
    game_state_pending = 9;
    perk_choices_dirty = 1;
  }
  return;
}



/* perks_update_effects @ 00406b40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates perk timers/effects (regen, shields, evil eyes, jinxed, bonus timers) */

void perks_update_effects(void)

{
  float *pfVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  undefined4 *puVar6;
  float fVar7;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = perk_count_get(perk_id_regeneration);
  if (((iVar2 != 0) && (uVar3 = crt_rand(), (uVar3 & 1) != 0)) &&
     (iVar2 = config_blob.reserved0._20_4_, 0 < (int)config_blob.reserved0._20_4_)) {
    do {
      if (((player_state_table.health < 100.0) && (0.0 < player_state_table.health)) &&
         (player_state_table.health = player_state_table.health + frame_dt,
         100.0 < player_state_table.health)) {
        player_state_table.health = 100.0;
      }
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  lean_mean_exp_timer = lean_mean_exp_timer - frame_dt;
  if (lean_mean_exp_timer < 0.0) {
    lean_mean_exp_timer = 0.25;
    if (0 < player_state_table.perk_counts[perk_id_lean_mean_exp_machine]) {
      player_state_table.experience =
           player_state_table.experience +
           player_state_table.perk_counts[perk_id_lean_mean_exp_machine] * 10;
    }
  }
  render_overlay_player_index = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    do {
      iVar2 = perk_count_get(perk_id_death_clock);
      if (iVar2 != 0) {
        pfVar1 = &(&player_state_table)[render_overlay_player_index].health;
        if ((&player_state_table)[render_overlay_player_index].health <= 0.0) {
          *pfVar1 = 0.0;
        }
        else {
          *pfVar1 = *pfVar1 - frame_dt * 3.3333333;
        }
      }
      if ((&player_state_table)[render_overlay_player_index].shield_timer <= 0.0) {
        (&player_state_table)[render_overlay_player_index].shield_timer = 0.0;
      }
      else {
        (&player_state_table)[render_overlay_player_index].shield_timer =
             (&player_state_table)[render_overlay_player_index].shield_timer - frame_dt;
      }
      if ((&player_state_table)[render_overlay_player_index].fire_bullets_timer <= 0.0) {
        (&player_state_table)[render_overlay_player_index].fire_bullets_timer = 0.0;
      }
      else {
        (&player_state_table)[render_overlay_player_index].fire_bullets_timer =
             (&player_state_table)[render_overlay_player_index].fire_bullets_timer - frame_dt;
      }
      if ((&player_state_table)[render_overlay_player_index].speed_bonus_timer <= 0.0) {
        (&player_state_table)[render_overlay_player_index].speed_bonus_timer = 0.0;
      }
      else {
        (&player_state_table)[render_overlay_player_index].speed_bonus_timer =
             (&player_state_table)[render_overlay_player_index].speed_bonus_timer - frame_dt;
      }
      render_overlay_player_index = render_overlay_player_index + 1;
    } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
  }
  doctor_perk_target_creature = -1;
  if (((0 < player_state_table.perk_counts[perk_id_doctor]) ||
      (0 < player_state_table.perk_counts[perk_id_pyrokinetic])) ||
     (0 < player_state_table.perk_counts[perk_id_evil_eyes])) {
    player_state_table.evil_eyes_target_creature = -1;
    iVar2 = creature_find_in_radius(&player_state_table.aim_x,12.0,0);
    if (iVar2 != -1) {
      iVar4 = perk_count_get(perk_id_doctor);
      if (iVar4 != 0) {
        doctor_perk_target_creature = iVar2;
      }
      iVar4 = perk_count_get(perk_id_pyrokinetic);
      if (iVar4 != 0) {
        fVar7 = (&creature_pool)[iVar2].collision_timer - frame_dt;
        (&creature_pool)[iVar2].collision_timer = fVar7;
        if (fVar7 < 0.0) {
          (&creature_pool)[iVar2].collision_timer = 0.5;
          pfVar1 = &(&creature_pool)[iVar2].pos_x;
          puVar6 = &local_8;
          fVar7 = 0.8;
          local_8 = 0;
          local_4 = 0;
          iVar4 = crt_rand();
          fx_spawn_particle(pfVar1,(float)(iVar4 % 0x274) * 0.01,puVar6,fVar7);
          puVar6 = &local_8;
          local_8 = 0;
          local_4 = 0;
          fVar7 = 0.6;
          iVar4 = crt_rand();
          fx_spawn_particle(pfVar1,(float)(iVar4 % 0x274) * 0.01,puVar6,fVar7);
          puVar6 = &local_8;
          local_8 = 0;
          local_4 = 0;
          fVar7 = 0.4;
          iVar4 = crt_rand();
          fx_spawn_particle(pfVar1,(float)(iVar4 % 0x274) * 0.01,puVar6,fVar7);
          puVar6 = &local_8;
          local_8 = 0;
          local_4 = 0;
          fVar7 = 0.3;
          iVar4 = crt_rand();
          fx_spawn_particle(pfVar1,(float)(iVar4 % 0x274) * 0.01,puVar6,fVar7);
          puVar6 = &local_8;
          local_8 = 0;
          local_4 = 0;
          fVar7 = 0.2;
          iVar4 = crt_rand();
          fx_spawn_particle(pfVar1,(float)(iVar4 % 0x274) * 0.01,puVar6,fVar7);
          fx_queue_add_random(pfVar1);
        }
      }
      iVar4 = perk_count_get(perk_id_evil_eyes);
      if (iVar4 != 0) {
        player_state_table.evil_eyes_target_creature = iVar2;
      }
    }
  }
  iVar2 = perk_count_get(perk_id_evil_eyes);
  if (iVar2 == 0) {
    player_state_table.evil_eyes_target_creature = -1;
  }
  if (((jinxed_effect_cooldown < 0.0) || (jinxed_effect_cooldown = jinxed_effect_cooldown - frame_dt, jinxed_effect_cooldown < 0.0)) &&
     (0 < player_state_table.perk_counts[perk_id_jinxed])) {
    iVar2 = crt_rand();
    if (iVar2 % 10 == 3) {
      player_state_table.health = player_state_table.health - 5.0;
      fx_queue_add_random(&player_state_table.pos_x);
      fx_queue_add_random(&player_state_table.pos_x);
    }
    iVar2 = crt_rand();
    jinxed_effect_cooldown = (float)(iVar2 % 0x14) * 0.1 + jinxed_effect_cooldown + 2.0;
    if (bonus_freeze_timer <= 0.0) {
      iVar2 = crt_rand();
      render_overlay_player_index = 0;
      iVar2 = iVar2 % 0x17f;
      do {
        if ((&creature_pool)[iVar2].active != '\0') break;
        iVar2 = crt_rand();
        iVar2 = iVar2 % 0x17f;
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < 10);
      render_overlay_player_index = 0;
      if ((&creature_pool)[iVar2].active != '\0') {
        fVar7 = frame_dt * 20.0;
        (&creature_pool)[iVar2].health = -1.0;
        (&creature_pool)[iVar2].hitbox_size = (&creature_pool)[iVar2].hitbox_size - fVar7;
        lVar5 = __ftol();
        player_state_table.experience = (int)lVar5;
        sfx_play_panned(sfx_trooper_inpain_01_alias_1);
      }
    }
  }
  return;
}



/* perk_meta_table_ctor @ 0042faa0 */

/* [binja] int32_t sub_42faa0() */

int perk_meta_table_ctor(void)

{
  int extraout_EAX;
  
  crt_ehvec_ctor(&perk_meta_table,0x14,0x80,&LAB_0042fac0,bonus_meta_entry_dtor);
  return extraout_EAX;
}



/* perk_meta_table_atexit_register @ 0042fae0 */

/* [binja] int32_t sub_42fae0() */

int perk_meta_table_atexit_register(void)

{
  int iVar1;
  
  iVar1 = crt_atexit(&LAB_0042faf0);
  return iVar1;
}



/* perk_can_offer @ 0042fb10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* returns nonzero when perk is eligible for selection */

int __cdecl perk_can_offer(int perk_index)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = config_blob.reserved0._24_4_;
  if (((((config_blob.reserved0._24_4_ != 3) || (config_blob.hardcore == '\0')) ||
       (quest_stage_minor != 10)) ||
      ((quest_stage_major != 2 ||
       (((perk_index != perk_id_poison_bullets && (perk_index != perk_id_veins_of_poison)) &&
        (perk_index != perk_id_plaguebearer)))))) &&
     (((config_blob.reserved0._20_4_ != 2 || (((&perk_meta_table)[perk_index].flags & 2) != 0)) &&
      ((config_blob.reserved0._24_4_ != 3 ||
       (uVar2 = perk_index * 5, ((&perk_meta_table)[perk_index].flags & 1) != 0)))))) {
    iVar1 = (&perk_meta_table)[perk_index].prerequisite;
    if (iVar1 == -1) {
      return -0xff;
    }
    if (0 < player_state_table.perk_counts[iVar1]) {
      return CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
    uVar2 = game_is_full_version();
    if (((((char)uVar2 == '\0') && (perk_index != perk_id_living_fortress)) &&
        (perk_index != perk_id_man_bomb)) && (perk_index != perk_id_fire_cough)) {
      uVar2 = perk_id_tough_reloader;
    }
  }
  return uVar2 & 0xffffff00;
}



/* perk_select_random @ 0042fbd0 */

/* randomly selects an eligible perk index */

int perk_select_random(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  do {
    iVar1 = crt_rand();
    iVar1 = iVar1 % perk_count_total + 1;
    if ((char)(&perk_meta_table)[iVar1].available != '\0') {
      iVar2 = perk_can_offer(iVar1);
      if ((char)iVar2 != '\0') {
        return iVar1;
      }
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x3e9);
  console_printf(&console_log_queue,s_perk_randomizer_failed + 2);
  return perk_id_instant_winner;
}



/* perks_rebuild_available @ 0042fc30 */

/* rebuilds perk availability/unlock flags */

void perks_rebuild_available(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = perk_count_total + 1;
  if (0 < iVar5) {
    piVar3 = &perk_meta_table.available;
    do {
      *(undefined1 *)piVar3 = 0;
      piVar3 = piVar3 + 5;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  iVar5 = perk_id_antiperk;
  puVar4 = &perk_unlock_table_ptr;
  *(undefined1 *)&(&perk_meta_table)[perk_id_antiperk].available = 0;
  do {
    *puVar4 = 1;
    iVar1 = perk_id_fire_cough;
    iVar6 = perk_id_living_fortress;
    iVar2 = quest_unlock_index;
    puVar4 = puVar4 + 0x14;
  } while ((int)puVar4 < 0x4c2e7c);
  *(undefined1 *)&(&perk_meta_table)[perk_id_man_bomb].available = 1;
  *(undefined1 *)&(&perk_meta_table)[iVar6].available = 1;
  *(undefined1 *)&(&perk_meta_table)[iVar1].available = 1;
  *(undefined1 *)&(&perk_meta_table)[perk_id_tough_reloader].available = 1;
  iVar6 = 0;
  if (0 < iVar2) {
    piVar3 = &quest_selected_meta.unlock_perk_id;
    do {
      if (0x484fe7 < (int)piVar3) break;
      iVar1 = *piVar3;
      iVar6 = iVar6 + 1;
      piVar3 = piVar3 + 0xb;
      *(undefined1 *)&(&perk_meta_table)[iVar1].available = 1;
    } while (iVar6 < iVar2);
  }
  *(undefined1 *)&(&perk_meta_table)[iVar5].available = 0;
  return;
}



/* perk_count_get @ 0042fcf0 */

/* returns perk count from DAT_00490968 */

int __cdecl perk_count_get(int perk_id)

{
  return player_state_table.perk_counts[perk_id];
}



/* perks_init_database @ 0042fd90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* builds the perk table (ids, names, descriptions) */

void __fastcall perks_init_database(void)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  void *in_ECX;
  void *this;
  void *this_00;
  void *this_01;
  void *this_02;
  void *this_03;
  char *this_04;
  void *this_05;
  void *this_06;
  void *this_07;
  void *this_08;
  void *this_09;
  void *this_10;
  void *this_11;
  void *this_12;
  void *this_13;
  void *this_14;
  void *this_15;
  void *this_16;
  void *this_17;
  void *this_18;
  void *this_19;
  void *this_20;
  void *this_21;
  void *this_22;
  void *this_23;
  void *this_24;
  void *this_25;
  void *this_26;
  void *this_27;
  void *this_28;
  void *this_29;
  void *this_30;
  void *this_31;
  void *this_32;
  void *this_33;
  void *this_34;
  void *this_35;
  void *this_36;
  void *this_37;
  void *this_38;
  void *this_39;
  void *this_40;
  void *this_41;
  void *this_42;
  void *this_43;
  void *this_44;
  void *this_45;
  void *this_46;
  void *this_47;
  void *this_48;
  void *this_49;
  void *this_50;
  void *this_51;
  void *this_52;
  void *this_53;
  void *this_54;
  void *this_55;
  void *this_56;
  void *this_57;
  void *this_58;
  void *this_59;
  void *this_60;
  void *this_61;
  void *this_62;
  void *this_63;
  void *this_64;
  void *this_65;
  void *this_66;
  void *this_67;
  void *this_68;
  void *this_69;
  void *this_70;
  void *this_71;
  void *this_72;
  void *this_73;
  void *this_74;
  void *this_75;
  void *this_76;
  void *this_77;
  void *this_78;
  void *this_79;
  void *this_80;
  void *this_81;
  void *this_82;
  void *this_83;
  void *this_84;
  void *this_85;
  void *this_86;
  void *this_87;
  void *this_88;
  void *this_89;
  void *this_90;
  void *this_91;
  void *this_92;
  void *this_93;
  void *this_94;
  void *this_95;
  void *this_96;
  void *this_97;
  void *this_98;
  void *this_99;
  void *this_x00100;
  void *this_x00101;
  void *this_x00102;
  void *this_x00103;
  void *this_x00104;
  void *this_x00105;
  void *this_x00106;
  void *this_x00107;
  void *this_x00108;
  void *this_x00109;
  void *this_x00110;
  void *this_x00111;
  void *this_x00112;
  void *this_x00113;
  
  perk_id_antiperk = 0;
  perk_meta_table.name = wrap_text_to_width_alloc(in_ECX,s_AntiPerk_00477728,0x100);
  perk_meta_table.description =
       wrap_text_to_width_alloc(this,s_You_shouldn_t_be_seeing_this___00477708,0x100);
  perk_id_bloody_mess_quick_learner = 1;
  perk_bloody_mess_name_ptr = wrap_text_to_width_alloc(this_00,s_Bloody_Mess_004776fc,0x100);
  perk_bloody_mess_desc_ptr = wrap_text_to_width_alloc(this_01,s_More_the_merrier__More_blood_gua_00477684,0x100)
  ;
  perk_bloody_mess_name_fx_ptr = wrap_text_to_width_alloc(this_02,s_Quick_Learner_00477674,0x100);
  pcVar3 = wrap_text_to_width_alloc(this_03,s_You_learn_things_faster_than_a_r_00477600,0x100);
  pcVar2 = perk_bloody_mess_desc_ptr;
  this_04 = perk_bloody_mess_name_ptr;
  iVar1 = perk_id_bloody_mess_quick_learner;
  perk_bloody_mess_desc_fx_ptr = pcVar3;
  if (config_blob.fx_toggle == '\0') {
    (&perk_meta_table)[perk_id_bloody_mess_quick_learner].name = perk_bloody_mess_name_ptr;
    (&perk_meta_table)[iVar1].description = pcVar2;
  }
  else {
    this_04 = (char *)(perk_id_bloody_mess_quick_learner * 0x14);
    *(char **)(this_04 + 0x4c2c40) = perk_bloody_mess_name_fx_ptr;
    *(char **)(this_04 + 0x4c2c44) = pcVar3;
  }
  perk_id_sharpshooter = 2;
  _perk_sharpshooter_name = wrap_text_to_width_alloc(this_04,s_Sharpshooter_004775f0,0x100);
  _perk_sharpshooter_desc =
       wrap_text_to_width_alloc(this_05,s_Miraculously_your_aiming_improve_00477538,0x100);
  perk_id_fastloader = 3;
  _perk_fastloader_name = wrap_text_to_width_alloc(this_06,s_Fastloader_0047752c,0x100);
  _perk_fastloader_desc =
       wrap_text_to_width_alloc(this_07,s_Man__you_sure_know_how_to_load_a_00477504,0x100);
  perk_id_lean_mean_exp_machine = 4;
  _perk_lean_mean_name = wrap_text_to_width_alloc(this_08,s_Lean_Mean_Exp_Machine_004774ec,0x100);
  _perk_lean_mean_desc =
       wrap_text_to_width_alloc(this_09,s_Why_kill_for_experience_when_you_0047745c,0x100);
  perk_id_long_distance_runner = 5;
  _perk_long_distance_name = wrap_text_to_width_alloc(this_10,s_Long_Distance_Runner_00477444,0x100);
  _perk_long_distance_desc =
       wrap_text_to_width_alloc(this_11,s_You_move_like_a_train_that_has_f_004773a4,0x100);
  perk_id_pyrokinetic = 6;
  _perk_pyrokinetic_name = wrap_text_to_width_alloc(this_12,s_Pyrokinetic_00477398,0x100);
  _perk_pyrokinetic_desc =
       wrap_text_to_width_alloc(this_13,s_You_see_flames_everywhere__Bare_a_0047734c,0x100);
  perk_id_instant_winner = 7;
  _perk_instant_winner_name = wrap_text_to_width_alloc(this_14,s_Instant_Winner_0047733c,0x100);
  _perk_instant_winner_desc =
       wrap_text_to_width_alloc(this_15,s_2500_experience_points__Right_aw_00477300,0x100);
  perk_instant_winner_flags = (void *)((uint)perk_instant_winner_flags | 4);
  perk_id_grim_deal = 8;
  _perk_grim_deal_prereq = 0;
  _perk_grim_deal_name = wrap_text_to_width_alloc(perk_instant_winner_flags,s_Grim_Deal_004772f4,0x100);
  _perk_grim_deal_desc =
       wrap_text_to_width_alloc(this_16,s_I_ll_make_you_a_deal__I_ll_give_y_00477258,0x100);
  perk_id_alternate_weapon = 9;
  _perk_alternate_weapon_flags = 1;
  _perk_alternate_weapon_name = wrap_text_to_width_alloc(this_17,s_Alternate_Weapon_00477244,0x100);
  _perk_alternate_weapon_desc =
       wrap_text_to_width_alloc(this_18,s_Ever_fancied_about_having_two_we_00477140,0x100);
  perk_id_plaguebearer = 10;
  _perk_plaguebearer_name = wrap_text_to_width_alloc(this_19,s_Plaguebearer_00477130,0x100);
  _perk_plaguebearer_desc =
       wrap_text_to_width_alloc(this_20,s_You_carry_a_horrible_disease__Go_004770a4,0x100);
  perk_id_evil_eyes = 0xb;
  _perk_evil_eyes_name = wrap_text_to_width_alloc(this_21,s_Evil_Eyes_00477098,0x100);
  _perk_evil_eyes_desc =
       wrap_text_to_width_alloc(this_22,s_No_living__nor_dead__can_resist_t_0047702c,0x100);
  perk_id_ammo_maniac = 0xc;
  _perk_ammo_maniac_name = wrap_text_to_width_alloc(this_23,s_Ammo_Maniac_00477020,0x100);
  _perk_ammo_maniac_desc =
       wrap_text_to_width_alloc(this_24,s_You_squeeze_and_you_push_and_you_00476f80,0x100);
  perk_id_radioactive = 0xd;
  _perk_radioactive_name = wrap_text_to_width_alloc(this_25,s_Radioactive_00476f74,0x100);
  _perk_radioactive_desc =
       wrap_text_to_width_alloc(this_26,s_You_are_the_Radioactive_man__you_00476eb0,0x100);
  perk_id_fastshot = 0xe;
  _perk_fastshot_name = wrap_text_to_width_alloc(this_27,s_Fastshot_00476ea4,0x100);
  _perk_fastshot_desc =
       wrap_text_to_width_alloc(this_28,s_Funny_how_you_make_your_gun_spit_00476e28,0x100);
  perk_id_fatal_lottery = 0xf;
  _perk_fatal_lottery_flags = 4;
  _perk_fatal_lottery_name = wrap_text_to_width_alloc(this_29,s_Fatal_Lottery_00476e18,0x100);
  _perk_fatal_lottery_desc =
       wrap_text_to_width_alloc(this_30,s_Fifty_fifty_chance_of_dying_OR_g_00476db4,0x100);
  perk_id_random_weapon = 0x10;
  _perk_random_weapon_flags = 5;
  _perk_random_weapon_name = wrap_text_to_width_alloc(this_31,s_Random_Weapon_00476da4,0x100);
  _perk_random_weapon_desc =
       wrap_text_to_width_alloc(this_32,s_Here__have_this_weapon__No_quest_00476d78,0x100);
  perk_id_mr_melee = 0x11;
  _perk_mr_melee_name = wrap_text_to_width_alloc(this_33,s_Mr__Melee_00476d6c,0x100);
  _perk_mr_melee_desc =
       wrap_text_to_width_alloc(this_34,s_You_master_the_art_of_melee_figh_00476cfc,0x100);
  perk_id_anxious_loader = 0x12;
  _perk_anxious_loader_name = wrap_text_to_width_alloc(this_35,s_Anxious_Loader_00476cec,0x100);
  _perk_anxious_loader_desc =
       wrap_text_to_width_alloc(this_36,s_When_you_can_t_stand_waiting_you_00476c5c,0x100);
  perk_id_final_revenge = 0x13;
  _DAT_004c2dc4 = 0;
  _DAT_004c2dbc = wrap_text_to_width_alloc(this_37,s_Final_Revenge_00476c4c,0x100);
  _DAT_004c2dc0 =
       wrap_text_to_width_alloc(this_38,s_Pick_this_and_you_ll_get_your_re_00476c14,0x100);
  perk_id_telekinetic = 0x14;
  _DAT_004c2dd0 = wrap_text_to_width_alloc(this_39,s_Telekinetic_00476c08,0x100);
  _DAT_004c2dd4 =
       wrap_text_to_width_alloc(this_40,s_Picking_up_bonuses_has_never_bee_00476b8c,0x100);
  perk_id_perk_expert = 0x15;
  _DAT_004c2de4 = wrap_text_to_width_alloc(this_41,s_Perk_Expert_00476b80,0x100);
  _DAT_004c2de8 =
       wrap_text_to_width_alloc(this_42,s_You_sure_know_how_to_pick_a_perk_00476acc,0x100);
  perk_id_unstoppable = 0x16;
  _DAT_004c2df8 = wrap_text_to_width_alloc(this_43,s_Unstoppable_00476ac0,0x100);
  _DAT_004c2dfc =
       wrap_text_to_width_alloc(this_44,s_Monsters_can_t_slow_you_down_wit_00476a4c,0x100);
  perk_id_regression_bullets = 0x17;
  _DAT_004c2e0c = wrap_text_to_width_alloc(this_45,s_Regression_Bullets_00476a38,0x100);
  _DAT_004c2e10 =
       wrap_text_to_width_alloc(this_46,s_Attempt_to_shoot_with_an_empty_c_004769c0,0x100);
  perk_id_infernal_contract = 0x18;
  _DAT_004c2e20 = wrap_text_to_width_alloc(this_47,s_Infernal_Contract_004769ac,0x100);
  _DAT_004c2e24 =
       wrap_text_to_width_alloc(this_48,s_In_exchange_for_your_soul__a_dar_004768d0,0x100);
  perk_id_poison_bullets = 0x19;
  _DAT_004c2e34 = wrap_text_to_width_alloc(this_49,s_Poison_Bullets_004768c0,0x100);
  _DAT_004c2e38 =
       wrap_text_to_width_alloc(this_50,s_You_tend_to_explicitly_treat_eac_00476834,0x100);
  perk_id_dodger = (void *)0x1a;
  _DAT_004c2e48 = wrap_text_to_width_alloc(this_51,s_Dodger_0047682c,0x100);
  _DAT_004c2e4c =
       wrap_text_to_width_alloc(this_52,s_It_seems_so_stupid_just_to_take_t_004767b8,0x100);
  perk_id_bonus_magnet = 0x1b;
  _DAT_004c2e5c = wrap_text_to_width_alloc(this_53,s_Bonus_Magnet_004767a8,0x100);
  _DAT_004c2e60 =
       wrap_text_to_width_alloc(this_54,s_You_somehow_seem_to_lure_all_kin_00476758,0x100);
  perk_id_uranium_filled_bullets = 0x1c;
  _DAT_004c2e70 = wrap_text_to_width_alloc(this_55,s_Uranium_Filled_Bullets_00476740,0x100);
  _DAT_004c2e74 =
       wrap_text_to_width_alloc(this_56,s_Your_bullets_have_a_nice_creamy_u_004766d8,0x100);
  perk_id_doctor = 0x1d;
  _DAT_004c2e84 = wrap_text_to_width_alloc(this_57,s_Doctor_004766d0,0x100);
  _DAT_004c2e88 =
       wrap_text_to_width_alloc(this_58,s_With_a_single_glance_you_can_tel_0047660c,0x100);
  perk_id_monster_vision = 0x1e;
  _DAT_004c2e98 = wrap_text_to_width_alloc(this_59,s_Monster_Vision_004765fc,0x100);
  _DAT_004c2e9c =
       wrap_text_to_width_alloc(this_60,s_With_your_newly_enhanced_senses_y_00476598,0x100);
  perk_id_hot_tempered = 0x1f;
  _DAT_004c2eac = wrap_text_to_width_alloc(this_61,s_Hot_Tempered_00476588,0x100);
  _DAT_004c2eb0 =
       wrap_text_to_width_alloc(this_62,s_It_literally_boils_inside_you__T_0047650c,0x100);
  perk_id_bonus_economist = 0x20;
  _DAT_004c2ec0 = wrap_text_to_width_alloc(this_63,s_Bonus_Economist_004764fc,0x100);
  _DAT_004c2ec4 =
       wrap_text_to_width_alloc(this_64,s_Your_bonus_power_ups_last_50__lo_004764bc,0x100);
  perk_init_counter = 0;
  perk_id_thick_skinned = 0x21;
  _DAT_004c2ed4 = wrap_text_to_width_alloc(this_65,s_Thick_Skinned_004764ac,0x100);
  _DAT_004c2ed8 =
       wrap_text_to_width_alloc(this_66,s_Trade_1_3_of_your_health_for_onl_00476464,0x100);
  perk_id_barrel_greaser = 0x22;
  _DAT_004c2ee8 = wrap_text_to_width_alloc(this_67,s_Barrel_Greaser_00476454,0x100);
  _DAT_004c2eec =
       wrap_text_to_width_alloc(this_68,s_After_studying_a_lot_of_physics_a_004763d0,0x100);
  perk_id_ammunition_within = 0x23;
  _DAT_004c2efc = wrap_text_to_width_alloc(this_69,s_Ammunition_Within_004763bc,0x100);
  _DAT_004c2f00 =
       wrap_text_to_width_alloc(this_70,s_Empty_clip_doesn_t_prevent_you_f_00476334,0x100);
  perk_id_veins_of_poison = 0x24;
  _DAT_004c2f10 = wrap_text_to_width_alloc(this_71,s_Veins_of_Poison_00476324,0x100);
  _DAT_004c2f14 =
       wrap_text_to_width_alloc(this_72,s_A_strong_poison_runs_through_you_004762ac,0x100);
  perk_id_toxic_avenger = 0x25;
  _DAT_004c2f24 = wrap_text_to_width_alloc(this_73,s_Toxic_Avenger_0047629c,0x100);
  _DAT_004c2f28 =
       wrap_text_to_width_alloc(this_74,s_You_started_out_just_by_being_po_004761dc,0x100);
  perk_id_regeneration = 0x26;
  _DAT_004c2f34 = perk_id_veins_of_poison;
  _DAT_004c2f38 = wrap_text_to_width_alloc(this_75,s_Regeneration_004761cc,0x100);
  _DAT_004c2f3c =
       wrap_text_to_width_alloc(this_76,s_Your_health_replenishes_but_very_00476188,0x100);
  perk_id_pyromaniac = 0x27;
  _DAT_004c2f4c = wrap_text_to_width_alloc(this_77,s_Pyromaniac_0047617c,0x100);
  _DAT_004c2f50 =
       wrap_text_to_width_alloc(this_78,s_You_just_enjoy_using_fire_as_you_004760fc,0x100);
  perk_id_ninja = 0x28;
  _DAT_004c2f60 = wrap_text_to_width_alloc(this_79,s_Ninja_004760f4,0x100);
  _DAT_004c2f64 =
       wrap_text_to_width_alloc(this_80,s_You_ve_taken_your_dodging_abilit_00476090,0x100);
  _DAT_004c2f70 = perk_id_dodger;
  perk_id_highlander = 0x29;
  _DAT_004c2f7c = 0;
  _DAT_004c2f74 = wrap_text_to_width_alloc(perk_id_dodger,s_Highlander_00476084,0x100);
  _DAT_004c2f78 =
       wrap_text_to_width_alloc(this_81,s_You_are_immortal__Well__almost_i_00475fb8,0x100);
  perk_id_jinxed = 0x2a;
  _DAT_004c2f88 = wrap_text_to_width_alloc(this_82,s_Jinxed_00475fb0,0x100);
  _DAT_004c2f8c =
       wrap_text_to_width_alloc(this_83,s_Things_happen_near_you__Stranges_00475f4c,0x100);
  perk_id_perk_master = 0x2b;
  _DAT_004c2f9c = wrap_text_to_width_alloc(this_84,s_Perk_Master_00475f40,0x100);
  _DAT_004c2fa0 =
       wrap_text_to_width_alloc(this_85,s_Being_the_Perk_Expert_taught_you_00475eb4,0x100);
  _DAT_004c2fac = perk_id_perk_expert;
  perk_id_reflex_boosted = 0x2c;
  _DAT_004c2fb0 = wrap_text_to_width_alloc(this_86,s_Reflex_Boosted_00475ea4,0x100);
  _DAT_004c2fb4 =
       wrap_text_to_width_alloc(this_87,s_To_you_the_world_seems_to_go_on_a_00475e00,0x100);
  perk_id_greater_regeneration = 0x2d;
  _DAT_004c2fc4 = wrap_text_to_width_alloc(this_88,s_Greater_Regeneration_00475de8,0x100);
  _DAT_004c2fc8 =
       wrap_text_to_width_alloc(this_89,s_Your_health_replenishes_faster_t_00475dbc,0x100);
  perk_id_breathing_room = 0x2e;
  _DAT_004c2fd4 = perk_id_regeneration;
  _DAT_004c2fe0 = 2;
  _DAT_004c2fd8 = wrap_text_to_width_alloc(this_90,s_Breathing_Room_00475dac,0x100);
  _DAT_004c2fdc =
       wrap_text_to_width_alloc(this_91,s_Trade_2_3rds_of_your_health_for_t_00475d34,0x100);
  perk_id_death_clock = 0x2f;
  _DAT_004c2fec = wrap_text_to_width_alloc(this_92,s_Death_Clock_00475d28,0x100);
  _DAT_004c2ff0 =
       wrap_text_to_width_alloc(this_93,s_You_die_exactly_in_30_seconds__Y_00475cbc,0x100);
  perk_id_my_favourite_weapon = 0x30;
  _DAT_004c3000 = wrap_text_to_width_alloc(this_94,s_My_Favourite_Weapon_00475ca8,0x100);
  _DAT_004c3004 =
       wrap_text_to_width_alloc(this_95,s_You_ve_grown_very_fond_of_your_p_00475c14,0x100);
  perk_id_bandage = 0x31;
  _DAT_004c3014 = wrap_text_to_width_alloc(this_96,s_Bandage_00475c0c,0x100);
  _DAT_004c3018 =
       wrap_text_to_width_alloc(this_97,s_Here__eat_this_bandage_and_you_l_00475bb0,0x100);
  perk_id_angry_reloader = 0x32;
  _DAT_004c3028 = wrap_text_to_width_alloc(this_98,s_Angry_Reloader_00475ba0,0x100);
  _DAT_004c302c =
       wrap_text_to_width_alloc(this_99,s_You_hate_it_when_you_run_out_of_s_00475ab4,0x100);
  perk_id_ion_gun_master = 0x33;
  _DAT_004c303c = wrap_text_to_width_alloc(this_x00100,s_Ion_Gun_Master_00475aa4,0x100);
  _DAT_004c3040 =
       wrap_text_to_width_alloc(this_x00101,s_You_re_good_with_ion_weapons__Yo_00475a18,0x100);
  perk_id_stationary_reloader = 0x34;
  _DAT_004c3050 = wrap_text_to_width_alloc(this_x00102,s_Stationary_Reloader_00475a04,0x100);
  _DAT_004c3054 =
       wrap_text_to_width_alloc(this_x00103,s_It_s_incredibly_hard_to_reload_y_0047594c,0x100);
  perk_id_man_bomb = 0x35;
  _DAT_004c3064 = wrap_text_to_width_alloc(this_x00104,s_Man_Bomb_00475940,0x100);
  _DAT_004c3068 =
       wrap_text_to_width_alloc(this_x00105,s_You_have_the_ability_to_go_boom_f_004758a8,0x100);
  perk_id_fire_cough = 0x36;
  _DAT_004c3078 = wrap_text_to_width_alloc(this_x00106,s_Fire_Caugh_0047589c,0x100);
  _DAT_004c307c =
       wrap_text_to_width_alloc(this_x00107,s_You_have_a_fireball_stuck_in_you_00475850,0x100);
  perk_id_living_fortress = 0x37;
  _DAT_004c308c = wrap_text_to_width_alloc(this_x00108,s_Living_Fortress_00475840,0x100);
  _DAT_004c3090 =
       wrap_text_to_width_alloc(this_x00109,s_It_comes_a_time_in_each_man_s_li_0047577c,0x100);
  perk_id_tough_reloader = 0x38;
  _DAT_004c30a0 = wrap_text_to_width_alloc(this_x00110,s_Tough_Reloader_0047576c,0x100);
  _DAT_004c30a4 =
       wrap_text_to_width_alloc(this_x00111,s_Damage_received_during_reloading_00475734,0x100);
  perk_id_lifeline_50_50 = 0x39;
  _DAT_004c30b4 = wrap_text_to_width_alloc(this_x00112,s_Lifeline_50_50_00475724,0x100);
  _DAT_004c30b8 =
       wrap_text_to_width_alloc(this_x00113,s_The_computer_removes_half_of_the_004756cc,0x100);
  perk_count_total = 0x39;
  perk_id_unknown_deprecated = 0x3a;
  perks_rebuild_available();
  return;
}


