/* credits_line_set @ 0040d000 */

/* stores a credits line string + flags into the credits line table */

void __cdecl credits_line_set(int index,char *text,int flags)

{
  char *pcVar1;
  
  credits_line_table[index].flags = flags;
  if (credits_line_table[index].text != (char *)0x0) {
    crt_free(credits_line_table[index].text);
  }
  pcVar1 = strdup_malloc(text);
  credits_line_table[index].text = pcVar1;
  credits_line_count = index;
  return;
}



/* credits_line_clear_flag @ 0040d040 */

/* walks backward to find the last line with flag 0x4 and clears it (penalty for wrong click; plays
   sfx) */

void __cdecl credits_line_clear_flag(int index)

{
  int *piVar1;
  
  if (-1 < index) {
    piVar1 = &credits_line_table[index].flags;
    while ((*piVar1 & 4) == 0) {
      index = index + -1;
      piVar1 = piVar1 + -2;
      if (index < 0) {
        return;
      }
    }
    credits_line_table[index].flags = credits_line_table[index].flags & 0xfffffffb;
    sfx_play(sfx_trooper_inpain_01);
  }
  return;
}



/* credits_build_lines @ 0040d090 */

/* populates credits line table with headings, names, and hint lines */

void credits_build_lines(void)

{
  credits_line_set(0,&s_empty_string,0);
  credits_line_set(1,s_Crimsonland_00472d5c,1);
  credits_line_set(2,&s_empty_string,0);
  credits_line_set(3,&s_empty_string,0);
  credits_line_set(4,s_Game_Design__00472d4c,1);
  credits_line_set(5,s_Tero_Alatalo_00472d3c,0);
  credits_line_set(6,&s_empty_string,0);
  credits_line_set(7,s_Programming__00472d2c,1);
  credits_line_set(8,s_Tero_Alatalo_00472d3c,0);
  credits_line_set(9,&s_empty_string,0);
  credits_line_set(10,s_Producer__00472d20,1);
  credits_line_set(0xb,s_Zach_Young_00472d14,0);
  credits_line_set(0xc,&s_empty_string,0);
  credits_line_set(0xd,s_2D_Art__00472d0c,1);
  credits_line_set(0xe,s_Tero_Alatalo_00472d3c,0);
  credits_line_set(0xf,&s_empty_string,0);
  credits_line_set(0x10,s_3D_Modelling__00472cfc,1);
  credits_line_set(0x11,s_Tero_Alatalo_00472d3c,0);
  credits_line_set(0x12,s_Timo_Palonen_00472cec,0);
  credits_line_set(0x13,&s_empty_string,0);
  credits_line_set(0x14,s_Music__00472ce4,1);
  credits_line_set(0x15,&s_game_label_a,0);
  credits_line_set(0x16,s_Ville_Eriksson_00472cbc,0);
  credits_line_set(0x17,&s_empty_string,0);
  credits_line_set(0x18,s_Sound_Effects__00472cac,1);
  credits_line_set(0x19,s_Ion_Hardie_00472ca0,0);
  credits_line_set(0x1a,s_Tero_Alatalo_00472d3c,0);
  credits_line_set(0x1b,&s_game_label_a,0);
  credits_line_set(0x1c,s_Ville_Eriksson_00472cbc,0);
  credits_line_set(0x1d,&s_empty_string,0);
  credits_line_set(0x1e,s_Manual__00472c98,1);
  credits_line_set(0x1f,s_Miikka_Kulmala_00472c88,0);
  credits_line_set(0x20,s_Zach_Young_00472d14,0);
  credits_line_set(0x21,&s_empty_string,0);
  credits_line_set(0x22,s_Special_thanks_to__00472c74,1);
  credits_line_set(0x23,&DAT_00472c58,0);
  credits_line_set(0x24,s_Peter_Hajba___Remedy_00472c40,0);
  credits_line_set(0x25,&s_empty_string,0);
  credits_line_set(0x26,s_Play_testers__00472c30,1);
  credits_line_set(0x27,s_Avraham_Petrosyan_00472c1c,0);
  credits_line_set(0x28,s_Bryce_Baker_00472c10,0);
  credits_line_set(0x29,s_Dan_Ruskin_00472c04,0);
  credits_line_set(0x2a,s_Dirk_Bunk_00472bf8,0);
  credits_line_set(0x2b,s_Eric_Dallaire_00472be8,0);
  credits_line_set(0x2c,s_Erik_Van_Pelt_00472bd8,0);
  credits_line_set(0x2d,s_Ernie_Ramirez_00472bc8,0);
  credits_line_set(0x2e,s_Ion_Hardie_00472ca0,0);
  credits_line_set(0x2f,s_James_C__Smith_00472bb8,0);
  credits_line_set(0x30,s_Jarkko_Forsbacka_00472ba4,0);
  credits_line_set(0x31,s_Jeff_McAteer_00472b94,0);
  credits_line_set(0x32,s_Juha_Alatalo_00472b84,0);
  credits_line_set(0x33,s_Kalle_Hahl_00472b78,0);
  credits_line_set(0x34,s_Lars_Brubaker_00472b68,0);
  credits_line_set(0x35,s_Lee_Cooper_00472b5c,0);
  credits_line_set(0x36,s_Markus_Lassila_00472b4c,0);
  credits_line_set(0x37,s_Matti_Alanen_00472b3c,0);
  credits_line_set(0x38,s_Miikka_Kulmala_00472c88,0);
  credits_line_set(0x39,s_Mika_Alatalo_00472b2c,0);
  credits_line_set(0x3a,s_Mike_Colonnese_00472b1c,0);
  credits_line_set(0x3b,s_Simon_Hallam_00472b0c,0);
  credits_line_set(0x3c,s_Toni_Nurminen_00472afc,0);
  credits_line_set(0x3d,&s_game_label_a,0);
  credits_line_set(0x3e,s_Ville_Eriksson_00472cbc,0);
  credits_line_set(0x3f,&DAT_00472aec,0);
  credits_line_set(0x40,s_Zach_Young_00472d14,0);
  credits_line_set(0x41,&s_empty_string,0);
  credits_line_set(0x42,s_Greeting_to__00472adc,0);
  credits_line_set(0x42,s_Chaos__00472ad4,0);
  credits_line_set(0x42,s_Matricks_00472ac8,0);
  credits_line_set(0x42,s_Muzzy_00472ac0,0);
  credits_line_set(0x42,&s_empty_string,0);
  credits_line_set(0x43,&s_empty_string,0);
  credits_line_set(0x44,s_2003__c__10tons_entertainment_00472aa0,0);
  credits_line_set(0x45,s_10tons_logo_by_00472a90,0);
  credits_line_set(0x46,s_Pasi_Heinonen_00472a80,0);
  credits_line_set(0x47,&s_empty_string,0);
  credits_line_set(0x48,&s_empty_string,0);
  credits_line_set(0x49,&s_empty_string,0);
  credits_line_set(0x4a,s_Uses_Vorbis_Audio_Decompression_00472a60,0);
  credits_line_set(0x4b,s_2003__c__Xiph_Org_Foundation_00472a40,0);
  credits_line_set(0x4c,s__see_vorbis_txt__00472a2c,0);
  credits_line_set(0x4d,&s_empty_string,0);
  credits_line_set(0x4e,&s_empty_string,0);
  credits_line_set(0x4f,&s_empty_string,0);
  credits_line_set(0x50,&s_empty_string,0);
  credits_line_set(0x51,&s_empty_string,0);
  credits_line_set(0x52,&s_empty_string,0);
  credits_line_set(0x53,&s_empty_string,0);
  credits_secret_line_base_index = 0x54;
  credits_line_set(0x54,&s_empty_string,0);
  credits_line_set(0x55,&s_empty_string,0);
  credits_line_set(0x56,&s_empty_string,0);
  credits_line_set(0x57,s_You_can_stop_watching_now__00472a10,0);
  credits_line_set(0x58,&s_empty_string,0);
  credits_line_set(0x59,&s_empty_string,0);
  credits_line_set(0x5a,&s_empty_string,0);
  credits_line_set(0x5b,&s_empty_string,0);
  credits_line_set(0x5c,&s_empty_string,0);
  credits_line_set(0x5d,&s_empty_string,0);
  credits_line_set(0x5e,&s_empty_string,0);
  credits_line_set(0x5f,&s_empty_string,0);
  credits_line_set(0x60,&s_empty_string,0);
  credits_line_set(0x61,&s_empty_string,0);
  credits_line_set(0x62,&s_empty_string,0);
  credits_line_set(99,&s_empty_string,0);
  credits_line_set(100,&s_empty_string,0);
  credits_line_set(0x65,&s_empty_string,0);
  credits_line_set(0x66,&s_empty_string,0);
  credits_line_set(0x67,&s_empty_string,0);
  credits_line_set(0x68,&s_empty_string,0);
  credits_line_set(0x69,&s_empty_string,0);
  credits_line_set(0x6a,&s_empty_string,0);
  credits_line_set(0x6b,&s_empty_string,0);
  credits_line_set(0x6c,&s_empty_string,0);
  credits_line_set(0x6d,&s_empty_string,0);
  credits_line_set(0x6e,&s_empty_string,0);
  credits_line_set(0x6f,&s_empty_string,0);
  credits_line_set(0x70,&s_empty_string,0);
  credits_line_set(0x71,&s_empty_string,0);
  credits_line_set(0x72,&s_empty_string,0);
  credits_line_set(0x73,&s_empty_string,0);
  credits_line_set(0x74,&s_empty_string,0);
  credits_line_set(0x75,&s_empty_string,0);
  credits_line_set(0x76,&s_empty_string,0);
  credits_line_set(0x77,s_Click_the_ones_with_the_round_on_004729ec,0);
  credits_line_set(0x78,s____and_be_patient___004729d6 + 2,0);
  credits_line_set(0x79,&s_empty_string,0);
  credits_line_set(0x7a,&s_empty_string,0);
  credits_line_set(0x7b,&s_empty_string,0);
  credits_line_set(0x7c,&s_empty_string,0);
  credits_line_set(0x7d,&s_empty_string,0);
  return;
}



/* credits_screen_update @ 0040d800 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* credits screen update/render loop; clicks flag lines containing 'o' (lowercase) and misclicks
   clear the last flagged line; when all 'o' lines are flagged, sets DAT_004811c4 and injects secret
   lines at DAT_004811bc; Secret button sets game_state_pending=0x1a (AlienZooKeeper) */

void credits_screen_update(void)

{
  uint uVar1;
  float y;
  float fVar2;
  int iVar3;
  int w;
  int iVar4;
  char *pcVar5;
  IGrim2D_vtbl *pIVar6;
  int index;
  credits_line_t *pcVar7;
  longlong lVar8;
  float r;
  float fVar9;
  float b;
  float fStack_28;
  int iStack_24;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  if ((credits_screen_init_flags & 1) == 0) {
    credits_screen_init_flags = credits_screen_init_flags | 1;
    credits_back_button_enable = 1;
    credits_screen_state1 = 0;
    credits_screen_state2 = 0;
    credits_screen_alpha = 0x3f800000;
    credits_screen_timer = 0;
    _credits_back_button = (undefined *)0x0;
    credits_back_button_state = 0;
    credits_back_button_clicked = '\0';
    credits_back_button_hover = 0;
    crt_atexit(&DAT_0040df60);
  }
  if ((credits_screen_init_flags & 2) == 0) {
    credits_screen_init_flags = credits_screen_init_flags | 2;
    credits_secret_button_enable = 1;
    credits_secret_state1 = 0;
    credits_secret_state2 = 0;
    credits_secret_alpha = 0x3f800000;
    credits_secret_timer = 0;
    _credits_secret_button = (char *)0x0;
    credits_secret_button_state = 0;
    credits_secret_button_clicked = '\0';
    credits_secret_hover = 0;
    crt_atexit(&DAT_0040df50);
  }
  fStack_4 = ui_menu_fade_alpha + ui_menu_item_y_spacing;
  _credits_secret_button = menu_label_secret;
  fStack_c = fStack_4 + 40.0 + 10.0;
  fStack_10 = ((ui_menu_item_y_base + ui_menu_anim_timer + 300.0 + ui_menu_scroll_offset + 48.0) - 110.0) - 40.0;
  if (ui_screen_phase == 0) {
    ui_screen_phase = 1;
    credits_build_lines();
    _credits_scroll_time = 0.0;
    credits_scroll_top_index = 0;
  }
  else if (ui_screen_phase == 1) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    if (credits_line_count + 2 < credits_scroll_top_index) {
      _credits_scroll_time = 0.0;
      credits_scroll_top_index = 0;
    }
    fStack_c = fStack_c - 4.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fStack_10 + 4.0,fStack_c,menu_label_credits);
    fStack_c = (fStack_c + 20.0) - 6.0;
    _credits_scroll_time = frame_dt + _credits_scroll_time;
    lVar8 = __ftol();
    credits_scroll_top_index = (int)lVar8 + -0xf;
    credits_scroll_bottom_index = (int)lVar8 + 1;
    if (credits_line_count < credits_scroll_bottom_index) {
      credits_scroll_bottom_index = credits_line_count;
    }
    for (fVar2 = _credits_scroll_time * 16.0; 16.0 < fVar2; fVar2 = fVar2 - 16.0) {
    }
    iVar3 = 0;
    if (credits_scroll_bottom_index != credits_scroll_top_index && -1 < credits_scroll_bottom_index - credits_scroll_top_index) {
      iStack_24 = 0;
      do {
        index = credits_scroll_top_index + iVar3;
        if (index < 0) {
          index = 0;
        }
        w = (*grim_interface_ptr->vtable->grim_measure_text_width)(credits_line_table[index].text);
        y = ((float)iStack_24 + fStack_c) - fVar2;
        fVar9 = (fStack_c - 16.0) + 24.0;
        if (fVar9 <= y) {
          fVar9 = ((float)(((credits_scroll_bottom_index - credits_scroll_top_index) + -1) * 0x10) + fStack_c) - 24.0;
          if (fVar9 < y) {
            fStack_28 = (fVar9 - y) * 0.041666668 + 1.0;
            goto LAB_0040db8e;
          }
          fStack_28 = 1.0;
        }
        else {
          fStack_28 = 1.0 - (fVar9 - y) * 0.041666668;
LAB_0040db8e:
          if (fStack_28 <= 1.0) {
            if (fStack_28 < 0.0) {
              fStack_28 = 0.0;
            }
          }
          else {
            fStack_28 = 1.0;
          }
        }
        fStack_8 = (fStack_10 + 140.0) - (float)(w / 2);
        fStack_4 = y;
        iVar4 = ui_mouse_inside_rect(&fStack_8,0x10,w);
        if (((char)iVar4 != '\0') && (iVar4 = input_primary_just_pressed(), (char)iVar4 != '\0')) {
          pcVar5 = _strchr(credits_line_table[index].text,0x6f);
          if (pcVar5 == (char *)0x0) {
            credits_line_clear_flag(index);
          }
          else {
            if ((credits_line_table[index].flags & 4) == 0) {
              sfx_play(sfx_ui_bonus);
            }
            credits_line_table[index].flags = credits_line_table[index].flags | 4;
          }
        }
        uVar1 = credits_line_table[index].flags;
        if ((uVar1 & 4) == 0) {
          pIVar6 = grim_interface_ptr->vtable;
          if ((uVar1 & 1) == 0) {
            fVar9 = 0.5;
            goto LAB_0040dcc6;
          }
          b = 1.0;
          fVar9 = 1.0;
          r = 1.0;
        }
        else {
          pIVar6 = grim_interface_ptr->vtable;
          if ((uVar1 & 1) == 0) {
            fVar9 = 0.7;
LAB_0040dcc6:
            b = 0.7;
            r = 0.4;
          }
          else {
            b = 0.9;
            fVar9 = 1.0;
            r = 0.9;
          }
        }
        (*pIVar6->grim_set_color)(r,fVar9,b,fStack_28);
        (*grim_interface_ptr->vtable->grim_draw_text_small)
                  ((fStack_10 + 140.0) - (float)(w / 2),y,credits_line_table[index].text);
        iVar3 = iVar3 + 1;
        iStack_24 = iStack_24 + 0x10;
      } while (iVar3 < credits_scroll_bottom_index - credits_scroll_top_index);
    }
    fStack_10 = fStack_10 + 100.0;
    _credits_back_button = &DAT_00472e80;
    fStack_c = fStack_c + 250.0;
    ui_button_update(&fStack_10,(ui_button_t *)&credits_back_button);
    pcVar7 = credits_line_table;
    do {
      if (((pcVar7->text != (char *)0x0) &&
          (pcVar5 = _strchr(pcVar7->text,0x6f), pcVar5 != (char *)0x0)) &&
         ((pcVar7->flags & 4) == 0)) goto LAB_0040d970;
      iVar3 = credits_secret_line_base_index;
      pcVar7 = pcVar7 + 1;
    } while ((int)pcVar7 < 0x481180);
    if (credits_secret_unlock_flag == '\0') {
      credits_secret_unlock_flag = '\x01';
      credits_line_table[credits_secret_line_base_index].flags =
           credits_line_table[credits_secret_line_base_index].flags | 4;
      credits_line_table[iVar3 + 1].flags = credits_line_table[iVar3 + 1].flags | 4;
      credits_line_table[iVar3 + 2].flags = credits_line_table[iVar3 + 2].flags | 4;
      credits_line_table[iVar3 + 3].flags = credits_line_table[iVar3 + 3].flags | 4;
      credits_line_table[iVar3 + 4].flags = credits_line_table[iVar3 + 4].flags | 4;
      credits_line_table[iVar3 + 5].flags = credits_line_table[iVar3 + 5].flags | 4;
      credits_line_table[iVar3 + 6].flags = credits_line_table[iVar3 + 6].flags | 4;
      credits_line_table[iVar3 + 7].flags = credits_line_table[iVar3 + 7].flags | 4;
      credits_line_table[iVar3 + 8].flags = credits_line_table[iVar3 + 8].flags | 4;
      credits_line_table[iVar3 + 9].flags = credits_line_table[iVar3 + 9].flags | 4;
      pcVar5 = strdup_malloc(s_Inside_Dead_Let_Mighty_Blood_00472e60);
      credits_line_table[iVar3].text = pcVar5;
      pcVar5 = strdup_malloc(s_Do_Firepower_See_Mark_Of_00472e44);
      credits_line_table[iVar3 + 1].text = pcVar5;
      pcVar5 = strdup_malloc(s_The_Sacrifice_Old_Center_00472e28);
      credits_line_table[iVar3 + 2].text = pcVar5;
      pcVar5 = strdup_malloc(s_Yourself_Ground_First_For_00472e0c);
      credits_line_table[iVar3 + 3].text = pcVar5;
      pcVar5 = strdup_malloc(s_Triangle_Cube_Last_Not_Flee_00472df0);
      credits_line_table[iVar3 + 4].text = pcVar5;
      pcVar5 = strdup_malloc(s_0001001110000010101110011_00472dd4);
      credits_line_table[iVar3 + 5].text = pcVar5;
      pcVar5 = strdup_malloc(s_0101001011100010010101100_00472db8);
      credits_line_table[iVar3 + 6].text = pcVar5;
      pcVar5 = strdup_malloc(s_011111001000111_00472da8);
      credits_line_table[iVar3 + 7].text = pcVar5;
      pcVar5 = strdup_malloc(s__4_bits_for_index__<__OOOPS_I_me_00472d7c);
      credits_line_table[iVar3 + 8].text = pcVar5;
      crt_free(credits_line_table[iVar3 + 9].text);
      pcVar5 = strdup_malloc(s__4_bits_for_index__00472d68);
      credits_line_table[iVar3 + 9].text = pcVar5;
    }
    fStack_8 = fStack_10 + 94.0;
    fStack_4 = fStack_c;
    ui_button_update(&fStack_8,(ui_button_t *)&credits_secret_button);
  }
LAB_0040d970:
  if (credits_back_button_clicked != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 4;
    ui_back_button_callback();
  }
  if (credits_secret_button_clicked != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 0x1a;
    ui_back_button_callback();
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(1);
  if ((char)iVar3 != '\0') {
    ui_transition_direction = 0;
    game_state_pending = 4;
    ui_back_button_callback();
  }
  return;
}



/* credits_secret_match3_find @ 0040f400 */

/* scans a 6x6 board for a 3-in-a-row match; writes start index (row-major; leftmost/topmost) +
   orientation (0=vertical, 1=horizontal) */

uint __cdecl credits_secret_match3_find(int *board,int *out_idx,uchar *out_dir)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_4;
  
  local_4 = 0;
  iVar4 = 2;
  piVar2 = board;
  do {
    iVar3 = 0;
    piVar5 = piVar2;
    do {
      iVar1 = *piVar5;
      if (-1 < iVar1) {
        iVar6 = 1;
        if (board[iVar4 + iVar3 + -1] == iVar1) {
          iVar6 = 2;
        }
        if (board[iVar4 + iVar3] == iVar1) {
          iVar6 = iVar6 + 1;
        }
        if (iVar6 == 3) {
          *out_idx = iVar3 + local_4 * 6;
          *out_dir = '\x01';
          return CONCAT31((int3)((uint)out_dir >> 8),1);
        }
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar3 < 4);
    iVar4 = iVar4 + 6;
    local_4 = local_4 + 1;
    piVar2 = piVar2 + 6;
    if (0x25 < iVar4) {
      iVar4 = 0;
      do {
        iVar3 = 0;
        piVar2 = board;
        do {
          iVar1 = *piVar2;
          if (-1 < iVar1) {
            iVar6 = 1;
            if (piVar2[6] == iVar1) {
              iVar6 = 2;
            }
            if (piVar2[0xc] == iVar1) {
              iVar6 = iVar6 + 1;
            }
            if (iVar6 == 3) {
              *out_idx = iVar4 + iVar3 * 6;
              *out_dir = '\0';
              return CONCAT31((int3)((uint)out_idx >> 8),1);
            }
          }
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 6;
        } while (iVar3 < 4);
        iVar4 = iVar4 + 1;
        board = board + 1;
        if (5 < iVar4) {
          return (uint)piVar2 & 0xffffff00;
        }
      } while( true );
    }
  } while( true );
}



/* credits_secret_alien_zookeeper_update @ 0040f4f0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* updates and renders the AlienZooKeeper credits secret; drives match-3 board state and UI */

void credits_secret_alien_zookeeper_update(void)

{
  IGrim2D_vtbl *pIVar1;
  uint uVar2;
  float unaff_EBX;
  int iVar3;
  int *piVar4;
  int *piVar5;
  float10 fVar6;
  float g;
  float b;
  uchar uVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fStack_54;
  float fStack_44;
  float fStack_40;
  
  fVar15 = 1.0;
  fVar14 = 1.0;
  fVar13 = 1.0;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  fVar12 = 0.8;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f4ccccd);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,fStack_44,fStack_40 - 14.0,s_AlienZooKeeper_00473128);
  fVar10 = 0.45;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3ee66666);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,unaff_EBX + 12.0,fStack_54 + 10.0,
             s_a_puzzle_game_unfinished_0047310c);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,unaff_EBX + 18.0,fStack_54 + 23.0,s___or_something_more__004730f4);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.8);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3ed70a3d);
  credits_secret_anim_time_ms = credits_secret_anim_time_ms + frame_dt_ms;
  if (0 < credits_secret_timer_ms) {
    credits_secret_timer_ms = credits_secret_timer_ms - frame_dt_ms;
    if (0 < credits_secret_timer_ms) goto LAB_0040f6cc;
    sfx_play(sfx_trooper_die_01);
  }
  if (credits_secret_timer_ms < 0) {
    credits_secret_timer_ms = 0;
  }
LAB_0040f6cc:
  fVar15 = fVar15 + 40.0;
  fVar14 = fVar14 + 22.0;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,fVar14 + 124.0,fVar15 - 16.0,s_score___d_004730e8,
             credits_secret_score);
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)((float *)&stack0xffffff94,192.0,192.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)((float *)&stack0xffffff90,192.0,192.0);
  iVar11 = credits_secret_timer_ms / 100;
  if (0xc0 < iVar11) {
    iVar11 = 0xc0;
  }
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)((float *)&stack0xffffff80,(float)iVar11,6.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)((float *)&stack0xffffff84,192.0,6.0);
  iVar11 = 0;
  iVar3 = 0;
  do {
    iVar8 = 0;
    do {
      if (credits_secret_selected_index == iVar3) {
        fVar10 = (float)iVar11 * 32.0 + fVar13;
        (*grim_interface_ptr->vtable->grim_draw_rect_filled)((float *)&stack0xffffff84,24.0,24.0);
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
        (*grim_interface_ptr->vtable->grim_draw_rect_outline)((float *)&stack0xffffff80,24.0,24.0);
      }
      iVar8 = iVar8 + 1;
      iVar3 = iVar3 + 1;
    } while (iVar8 < 6);
    iVar11 = iVar11 + 1;
  } while (iVar3 < 0x24);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_bind_texture)(credits_secret_gems_texture,0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  fVar15 = 0.0;
  fVar14 = 0.0;
  piVar4 = &credits_secret_board;
  do {
    iVar3 = 0;
    iVar11 = 0;
    do {
      if (*piVar4 != -3) {
        uVar2 = credits_secret_anim_time_ms / 0x32 + *piVar4 * 2 & 0x8000001f;
        if ((int)uVar2 < 0) {
          uVar2 = (uVar2 - 1 | 0xffffffe0) + 1;
        }
        iVar9 = iVar11;
        (*grim_interface_ptr->vtable->grim_set_atlas_frame)(8,uVar2);
        iVar8 = *piVar4;
        if (iVar8 == 0) {
          b = 0.5;
          g = 0.5;
          pIVar1 = grim_interface_ptr->vtable;
LAB_0040fae2:
          (*pIVar1->grim_set_color)(1.0,g,b,1.0);
        }
        else if (iVar8 == 1) {
          (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.5,1.0,1.0);
        }
        else {
          if (iVar8 == 2) {
            b = 1.0;
            g = 0.5;
            pIVar1 = grim_interface_ptr->vtable;
            goto LAB_0040fae2;
          }
          if (iVar8 == 3) {
            (*grim_interface_ptr->vtable->grim_set_color)(0.5,1.0,1.0,1.0);
          }
          else if (iVar8 == 4) {
            b = 0.5;
            g = 1.0;
            pIVar1 = grim_interface_ptr->vtable;
            goto LAB_0040fae2;
          }
        }
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((float)iVar9 + fVar12,(float)(int)fVar15 + fVar13,32.0,32.0);
        if (((0 < credits_secret_timer_ms) &&
            (iVar8 = ui_mouse_inside_rect((float *)&stack0xffffff9c,0x20,0x20), (char)iVar8 != '\0')
            ) && (iVar8 = input_primary_just_pressed(), (char)iVar8 != '\0')) {
          sfx_play(sfx_ui_clink_01);
          if (credits_secret_selected_index == -1) {
            credits_secret_selected_index = (int)fVar14 + iVar3;
          }
          else {
            iVar8 = *piVar4;
            *piVar4 = (&credits_secret_board)[credits_secret_selected_index];
            (&credits_secret_board)[credits_secret_selected_index] = iVar8;
            credits_secret_selected_index = -1;
            iVar8 = 0;
            uVar7 = '\0';
            uVar2 = credits_secret_match3_find
                              (&credits_secret_board,(int *)&stack0xffffff74,&stack0xffffff6b);
            if ((char)uVar2 != '\0') {
              (&credits_secret_board)[iVar8] = 0xfffffffd;
              if (uVar7 == '\0') {
                *(undefined4 *)(&credits_secret_match_mask_v0 + iVar8 * 4) = 0xfffffffd;
                *(undefined4 *)(&credits_secret_match_mask_v1 + iVar8 * 4) = 0xfffffffd;
              }
              else {
                (&credits_secret_match_mask_h0)[iVar8] = 0xfffffffd;
                (&credits_secret_match_mask_h1)[iVar8] = 0xfffffffd;
              }
              credits_secret_score = credits_secret_score + 1;
              sfx_play(sfx_ui_bonus);
              credits_secret_timer_ms = credits_secret_timer_ms + 2000;
            }
          }
        }
      }
      iVar11 = iVar11 + 0x20;
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar11 < 0xc0);
    fVar14 = (float)((int)fVar14 + 6);
    fVar15 = (float)((int)fVar15 + 0x20);
    if (0x481a7b < (int)piVar4) {
      (*grim_interface_ptr->vtable->grim_end_batch)();
      if (credits_secret_timer_ms == 0) {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f800000);
        fVar6 = (float10)fcos((float10)credits_secret_anim_time_ms * (float10)0.005);
        if ((float10)0.0 < fVar6) {
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,fVar10 + 38.0,(fVar14 + 96.0) - 22.0,s_Game_Over_004730dc);
        }
      }
      piVar4 = &credits_secret_board;
      do {
        iVar11 = 6;
        do {
          if (*piVar4 == -1) {
            iVar3 = crt_rand();
            *piVar4 = iVar3 % 5;
          }
          piVar4 = piVar4 + 1;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      } while ((int)piVar4 < 0x481a7c);
      if ((credits_secret_flags & 1) == 0) {
        credits_secret_flags = credits_secret_flags | 1;
        DAT_004819d6 = 1;
        DAT_004819e5 = 0;
        DAT_004819e4 = 0;
        _DAT_004819e0 = 0x3f800000;
        _DAT_004819dc = 0;
        _credits_secret_reset_button = (char *)0x0;
        DAT_004819d4 = 0;
        DAT_004819d5 = 0;
        _DAT_004819d8 = 0;
        crt_atexit(&DAT_0040ff40);
      }
      _credits_secret_reset_button = s_Reset_004730d4;
      iVar11 = ui_button_update((float *)&stack0xffffff9c,
                                (ui_button_t *)&credits_secret_reset_button);
      if ((char)iVar11 != '\0') {
        do {
          piVar4 = &credits_secret_board;
          do {
            iVar11 = 6;
            piVar5 = piVar4;
            do {
              iVar3 = crt_rand();
              piVar4 = piVar5 + 1;
              iVar11 = iVar11 + -1;
              *piVar5 = iVar3 % 5;
              piVar5 = piVar4;
            } while (iVar11 != 0);
          } while ((int)piVar4 < 0x481a7c);
          uVar2 = credits_secret_match3_find
                            (&credits_secret_board,(int *)&stack0xffffff84,&stack0xffffff6b);
        } while ((char)uVar2 != '\0');
        credits_secret_selected_index = -1;
        credits_secret_score = 0;
        credits_secret_timer_ms = 0x2580;
      }
      if ((credits_secret_flags & 2) == 0) {
        credits_secret_flags = credits_secret_flags | 2;
        DAT_00481bc6 = 1;
        DAT_00481bd5 = 0;
        DAT_00481bd4 = 0;
        _DAT_00481bd0 = 0x3f800000;
        _DAT_00481bcc = 0;
        _credits_secret_back_button = (undefined *)0x0;
        DAT_00481bc4 = 0;
        DAT_00481bc5 = 0;
        _DAT_00481bc8 = 0;
        crt_atexit(&DAT_0040ff30);
      }
      _credits_secret_back_button = &DAT_00472e80;
      iVar11 = ui_button_update((float *)&stack0xffffff9c,(ui_button_t *)&credits_secret_back_button
                               );
      if ((char)iVar11 != '\0') {
        ui_transition_direction = 0;
        game_state_pending = 4;
      }
      return;
    }
  } while( true );
}


