/* ui_render_loading @ 00402d50 */

/* [binja] int32_t sub_402d50() */

int ui_render_loading(void)

{
  IGrim2D_vtbl *pIVar1;
  int iVar2;
  undefined4 uVar3;
  float y;
  char *text;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  uStack_24 = 0;
  fStack_2c = (float)(config_blob.screen_width / 2 + -0x6e);
  fStack_28 = (float)(config_blob.screen_height / 2 + -0x1e);
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&fStack_2c,220.0,60.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  fStack_2c = (float)(config_blob.screen_height / 2 + -0x1e);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)((float *)&stack0xffffffd0,220.0,60.0);
  pIVar1 = grim_interface_ptr->vtable;
  text = s_Please_wait____00471444;
  y = (float)(config_blob.screen_height / 2 + -8);
  iVar2 = (*pIVar1->grim_measure_text_width)(s_Please_wait____00471444);
  uVar3 = 0x402ead;
  (*pIVar1->grim_draw_text_small)((float)(config_blob.screen_width / 2 - iVar2 / 2),y,text);
  iVar2 = (*grim_interface_ptr->vtable->grim_set_config_var)
                    (0x36,CONCAT31((int3)((uint)uVar3 >> 8),1));
  return iVar2;
}



/* ui_hit_test_rect @ 00403430 */

/* [binja] int32_t sub_403430(float* arg1, int32_t arg2, int32_t arg3) */

int __cdecl ui_hit_test_rect(float *arg1,int arg2,int arg3)

{
  if ((((*arg1 - 10.0 < ui_mouse_x) && (arg1[1] - 2.0 < ui_mouse_y)) &&
      (ui_mouse_x < (float)arg3 + *arg1)) &&
     ((ui_mouse_y < (float)arg2 + arg1[1] && (ui_mouse_blocked == '\0')))) {
    return 1;
  }
  return 0;
}



/* ui_mouse_inside_rect @ 004034a0 */

/* returns 1 when the mouse is inside the rect and mouse capture is clear */

int __cdecl ui_mouse_inside_rect(float *xy,int h,int w)

{
  if ((((*xy < ui_mouse_x) && (xy[1] < ui_mouse_y)) && (ui_mouse_x < (float)w + *xy)) &&
     ((ui_mouse_y < (float)h + xy[1] && (ui_mouse_blocked == '\0')))) {
    return 1;
  }
  return 0;
}



/* ui_render_keybind_help @ 00405160 */

/* renders the in-game key bindings help overlay */

void __cdecl ui_render_keybind_help(float *xy,float alpha)

{
  IGrim2D_vtbl *pIVar1;
  char *pcVar2;
  float fVar3;
  float x;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(xy,512.0,256.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)xy);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(xy,512.0,256.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f4ccccd);
  (*grim_interface_ptr->vtable->grim_draw_text_mono_fmt)
            (grim_interface_ptr,*xy + 16.0,xy[1] + 16.0,s_key_info_00471ffc);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)xy);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  x = *xy + 32.0;
  fVar3 = xy[1] + 50.0;
  fVar5 = x;
  fVar6 = fVar3;
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,x,fVar3,s_Level_Up__00471ff0);
  fVar7 = fVar5 + 128.0;
  pIVar1 = grim_interface_ptr->vtable;
  pcVar2 = input_key_name(config_blob.key_pick_perk);
  (*pIVar1->grim_draw_text_small_fmt)
            (grim_interface_ptr,fVar7,fVar3,s__s_or_SPACE_BAR_or_KeyPadAdd_00471fd0,pcVar2);
  fVar6 = fVar6 + 18.0;
  fVar3 = fVar6;
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,x,fVar6,s_Reload__00471fc8);
  pIVar1 = grim_interface_ptr->vtable;
  pcVar2 = input_key_name(config_blob.key_reload);
  (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar7,fVar6,&s_fmt_percent_s,pcVar2);
  fVar3 = fVar3 + 18.0 + 20.0;
  fVar7 = fVar3;
  iVar8 = 0;
  do {
    if (iVar8 == 1) {
      x = fVar5 + 256.0;
      fVar5 = x;
    }
    iVar4 = iVar8 + 1;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar3,s_Player__d_00471fb8,iVar4);
    fVar7 = fVar7 + 22.0;
    fVar3 = fVar7;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar7,&DAT_00471fb4);
    fVar6 = fVar5 + 64.0;
    pIVar1 = grim_interface_ptr->vtable;
    pcVar2 = input_key_name(config_blob.keybinds_p1[iVar8 * 5]);
    (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar6,fVar7,&s_fmt_percent_s,pcVar2);
    fVar3 = fVar3 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar3,s_Down__00471fac);
    pIVar1 = grim_interface_ptr->vtable;
    pcVar2 = input_key_name(config_blob.keybinds_p1[iVar8 * 5 + 1]);
    (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar6,fVar3,&s_fmt_percent_s,pcVar2);
    fVar3 = fVar3 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar3,s_Left__00471fa4);
    pIVar1 = grim_interface_ptr->vtable;
    pcVar2 = input_key_name(config_blob.keybinds_p1[iVar8 * 5 + 2]);
    (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar6,fVar3,&s_fmt_percent_s,pcVar2);
    fVar3 = fVar3 + 16.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar3,s_Right__00471f9c);
    pIVar1 = grim_interface_ptr->vtable;
    pcVar2 = input_key_name(config_blob.keybinds_p1[iVar8 * 5 + 3]);
    (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar6,fVar3,&s_fmt_percent_s,pcVar2);
    fVar3 = fVar3 + 16.0;
    fVar7 = fVar3;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,x,fVar3,s_Fire__00471f94);
    pIVar1 = grim_interface_ptr->vtable;
    pcVar2 = input_key_name(config_blob.keybinds_p1[iVar8 * 5 + 4]);
    (*pIVar1->grim_draw_text_small_fmt)(grim_interface_ptr,fVar6,fVar3,&s_fmt_percent_s,pcVar2);
    if (iVar8 == 0) {
      fVar3 = fVar7 - 94.0;
      fVar7 = fVar3;
    }
    iVar8 = iVar4;
  } while (iVar4 < 2);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,fVar5 - 20.0,fVar7 + 32.0,s_Press_F1_to_return_to_game_00471f78);
  return;
}



/* format_ordinal @ 00406180 */

/* formats an integer as an English ordinal (e.g. 1st/2nd/3rd/4th) into a global scratch buffer */

char * format_ordinal(int n)

{
  int iVar1;
  undefined *puVar2;
  
  if ((n < 8) || (0x14 < n)) {
    iVar1 = n % 10;
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        puVar2 = &s_ordinal_st;
        goto LAB_004061c7;
      }
      if (iVar1 == 2) {
        puVar2 = &s_ordinal_nd;
        goto LAB_004061c7;
      }
      if (iVar1 == 3) {
        puVar2 = &s_ordinal_rd;
        goto LAB_004061c7;
      }
    }
  }
  puVar2 = &s_ordinal_th;
LAB_004061c7:
  crt_sprintf(&ordinal_scratch_buffer,&s_ordinal_format,n,puVar2);
  return &ordinal_scratch_buffer;
}



/* ui_draw_clock_gauge @ 004061e0 */

/* draws the 32x32 clock gauge at the current transform */

void ui_draw_clock_gauge(void)

{
  float unaff_EBX;
  int unaff_EDI;
  int iVar1;
  int iStack_10;
  
  iVar1 = 1;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_table_texture,0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,unaff_EBX);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)((float)iStack_10,(float)unaff_EDI,32.0,32.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_hands_texture,0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_set_rotation)((float)(iVar1 / 1000) * 0.10471976);
  (*grim_interface_ptr->vtable->grim_draw_quad)((float)iStack_10,(float)unaff_EDI,32.0,32.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  return;
}



/* ui_draw_clock_gauge_at @ 0040a4c0 */

/* draws the clock gauge at a position when progress > 0 */

void __cdecl ui_draw_clock_gauge_at(float *xy,float radius,float progress)

{
  if (0.0 < progress) {
    __ftol();
    __ftol();
    __ftol();
    ui_draw_clock_gauge();
  }
  return;
}



/* ui_render_aim_indicators @ 0040a510 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders aim reticles, reload gauges, and player HUD indicators */

void ui_render_aim_indicators(void)

{
  IGrim2D_vtbl *pIVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float a;
  float fStack_60;
  
  if (demo_mode_active == '\0') {
    if ((overlay_atexit_init_flags & 1) == 0) {
      overlay_atexit_init_flags = overlay_atexit_init_flags | 1;
      crt_atexit(&DAT_0040aaa0);
    }
    if ((overlay_atexit_init_flags & 2) == 0) {
      overlay_atexit_init_flags = overlay_atexit_init_flags | 2;
      crt_atexit(&DAT_0040aa90);
    }
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    render_overlay_player_index = 0;
    iVar2 = config_blob.reserved0._20_4_;
    if (0 < (int)config_blob.reserved0._20_4_) {
      do {
        if (0.0 < (&player_state_table)[render_overlay_player_index].health) {
          fVar5 = (&player_state_table)[render_overlay_player_index].aim_x -
                  (&player_state_table)[render_overlay_player_index].pos_x;
          fVar6 = (&player_state_table)[render_overlay_player_index].aim_y -
                  (&player_state_table)[render_overlay_player_index].pos_y;
          fStack_60 = SQRT(fVar5 * fVar5 + fVar6 * fVar6) *
                      (&player_state_table)[render_overlay_player_index].spread_heat * 0.5;
          if (fStack_60 < 6.0) {
            fStack_60 = 6.0;
          }
          (*grim_interface_ptr->vtable->grim_set_uv)(0.5,0.5,0.5,0.5);
          (*grim_interface_ptr->vtable->grim_set_color)(0.0,0.0,0.1,0.3);
          aim_screen_x = camera_offset_x + (&player_state_table)[render_overlay_player_index].aim_x
          ;
          aim_screen_y = camera_offset_y + (&player_state_table)[render_overlay_player_index].aim_y
          ;
          (*grim_interface_ptr->vtable->grim_draw_circle_filled)
                    (aim_screen_x,aim_screen_y,fStack_60);
          (*grim_interface_ptr->vtable->grim_bind_texture)(bullet_trail_texture,0);
          (*grim_interface_ptr->vtable->grim_set_uv)(0.5,0.0,0.5,1.0);
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.55);
          (*grim_interface_ptr->vtable->grim_draw_circle_outline)
                    (aim_screen_x,aim_screen_y,fStack_60);
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.7,0.1,0.8);
          aim_screen_x = camera_offset_x + (&player_state_table)[render_overlay_player_index].aim_x
          ;
          aim_screen_y = camera_offset_y + (&player_state_table)[render_overlay_player_index].aim_y
          ;
          ui_draw_clock_gauge_at
                    (&aim_screen_x,48.0,
                     (&player_state_table)[render_overlay_player_index].reload_timer /
                     (&player_state_table)[render_overlay_player_index].reload_timer_max);
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.7);
          iVar2 = config_blob.reserved0._20_4_;
        }
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < iVar2);
    }
    render_overlay_player_index = 0;
    if (0 < iVar2) {
      do {
        if ((0.0 < (&player_state_table)[render_overlay_player_index].health) &&
           (config_blob.reserved0[render_overlay_player_index + 4] != '\0')) {
          (*grim_interface_ptr->vtable->grim_set_rotation)
                    ((&player_state_table)[render_overlay_player_index].heading);
          (*grim_interface_ptr->vtable->grim_bind_texture)(texture_arrow_id,0);
          (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
          if (config_blob.reserved0._20_4_ == 2) {
            if (render_overlay_player_index == 0) {
              pIVar1 = grim_interface_ptr->vtable;
              a = 0.6;
              fVar6 = 0.9;
              fVar5 = 0.8;
              goto LAB_0040a8dc;
            }
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.9,0.8,0.6);
          }
          else {
            a = 0.3;
            fVar6 = 1.0;
            pIVar1 = grim_interface_ptr->vtable;
            fVar5 = 1.0;
LAB_0040a8dc:
            (*pIVar1->grim_set_color)(fVar5,fVar6,1.0,a);
          }
          (*grim_interface_ptr->vtable->grim_begin_batch)();
          if (*(int *)(config_blob.reserved0 + render_overlay_player_index * 4 + 0x1c) == 4) {
            fVar5 = camera_offset_x +
                    (&player_state_table)[render_overlay_player_index].move_target_x;
            aim_screen_y = (camera_offset_y +
                           (&player_state_table)[render_overlay_player_index].move_target_y) - 16.0;
          }
          else {
            fVar3 = (float10)(&player_state_table)[render_overlay_player_index].heading -
                    (float10)1.5707964;
            fVar4 = (float10)fcos(fVar3);
            fVar3 = (float10)fsin(fVar3);
            fVar5 = camera_offset_x + (&player_state_table)[render_overlay_player_index].pos_x +
                    (float)fVar4 * 60.0;
            aim_screen_y = (float)((fVar3 * (float10)60.0 +
                                   (float10)(camera_offset_y +
                                            (&player_state_table)[render_overlay_player_index].pos_y
                                            )) - (float10)16.0);
          }
          aim_screen_x = fVar5 - 16.0;
          (*grim_interface_ptr->vtable->grim_draw_quad)(aim_screen_x,aim_screen_y,32.0,32.0);
          (*grim_interface_ptr->vtable->grim_end_batch)();
          iVar2 = config_blob.reserved0._20_4_;
        }
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < iVar2);
    }
    render_overlay_player_index = 0;
    if (0 < iVar2) {
      do {
        if (0.0 < (&player_state_table)[render_overlay_player_index].health) {
          ui_render_aim_enhancement();
          iVar2 = config_blob.reserved0._20_4_;
        }
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < iVar2);
    }
    render_overlay_player_index = 0;
  }
  return;
}



/* format_time_seconds @ 0040ff50 */

/* [binja] int32_t sub_40ff50(int32_t arg1) */

int __cdecl format_time_seconds(int arg1)

{
  int iVar1;
  
  iVar1 = arg1 % 0x3c;
  if (iVar1 < 10) {
    crt_sprintf(&highscore_name_input_b,s__d_0_d_00473150,arg1 / 0x3c,iVar1);
    return 0x482624;
  }
  crt_sprintf(&highscore_name_input_b,s__d__d_00473148,arg1 / 0x3c,iVar1);
  return 0x482624;
}



/* ui_page_panels_init @ 00417690 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_417690() */

int ui_page_panels_init(void)

{
  undefined *puVar1;
  undefined4 *puVar2;
  ui_element_t *puVar3;
  int iVar4;
  int iVar5;
  
  puVar1 = &ui_page_panel_0_base;
  iVar4 = 8;
  do {
    identity_passthrough(puVar1);
    puVar1 = puVar1 + 0x1c;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar1 = &ui_page_panel_1_base;
  ui_page_panel_0_count = 4;
  iVar4 = 8;
  do {
    identity_passthrough(puVar1);
    puVar1 = puVar1 + 0x1c;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ui_page_panel_1_count = 4;
  puVar1 = &ui_page_panel_2_base;
  iVar4 = 8;
  do {
    identity_passthrough(puVar1);
    puVar1 = puVar1 + 0x1c;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ui_page_panel_2_count = 4;
  puVar2 = &crt_file_buffer_pool;
  iVar4 = 8;
  do {
    identity_passthrough(puVar2);
    puVar2 = puVar2 + 7;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ui_page_panel_3_count = 4;
  puVar3 = &ui_menu_item_element;
  iVar4 = 8;
  do {
    identity_passthrough(puVar3);
    puVar3 = (ui_element_t *)&puVar3->pos_y;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ui_menu_item_element._pad3[0] = '\x04';
  ui_menu_item_element._pad3[1] = '\0';
  ui_menu_item_element._pad3[2] = '\0';
  ui_menu_item_element._pad3[3] = '\0';
  iVar4 = 0x48fc90;
  iVar5 = 8;
  do {
    identity_passthrough(iVar4);
    iVar4 = iVar4 + 0x1c;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  ui_menu_item_element._pad4[0xa8] = '\x04';
  ui_menu_item_element._pad4[0xa9] = '\0';
  ui_menu_item_element._pad4[0xaa] = '\0';
  ui_menu_item_element._pad4[0xab] = '\0';
  callback_iterator(0x48fd78,0x1c,8,0x417a90);
  ui_menu_item_element._pad5[0xac] = '\x04';
  ui_menu_item_element._pad5[0xad] = '\0';
  ui_menu_item_element._pad5[0xae] = '\0';
  ui_menu_item_element._pad5[0xaf] = '\0';
  callback_iterator(0x48fe60,0x1c,8,0x417a90);
  ui_page_panel_4_count = 4;
  callback_iterator(0x48ff48,0x1c,8,0x417a90);
  ui_page_panel_5_count = 4;
  callback_iterator(0x490030,0x1c,8,0x417a90);
  ui_page_panel_6_count = 4;
  callback_iterator(0x490118,0x1c,8,0x417a90);
  ui_page_panel_7_count = 4;
  iVar4 = callback_iterator(0x490200,0x1c,8,0x417a90);
  perk_screen_page_count = 4;
  return iVar4;
}



/* ui_page_set_page_count_a @ 00417aa0 */

/* [binja] void* __fastcall sub_417aa0(void* arg1) */

void * __fastcall ui_page_set_page_count_a(void *arg1)

{
  *(undefined4 *)((int)arg1 + 0xe4) = 4;
  return arg1;
}



/* ui_page_set_page_count_b @ 00417ab0 */

/* [binja] char* __fastcall sub_417ab0(char* arg1) */

char * __fastcall ui_page_set_page_count_b(char *arg1)

{
  arg1[0x120] = '\x04';
  arg1[0x121] = '\0';
  arg1[0x122] = '\0';
  arg1[0x123] = '\0';
  arg1[0x208] = '\x04';
  arg1[0x209] = '\0';
  arg1[0x20a] = '\0';
  arg1[0x20b] = '\0';
  arg1[0x2f0] = '\x04';
  arg1[0x2f1] = '\0';
  arg1[0x2f2] = '\0';
  arg1[0x2f3] = '\0';
  arg1[0x2f8] = '\0';
  arg1[0x2f9] = '\0';
  arg1[0x2fa] = '\0';
  arg1[0x2fb] = '\0';
  arg1[0x314] = '\0';
  arg1[0x38] = '\0';
  arg1[0x39] = '\0';
  arg1[0x3a] = '\0';
  arg1[0x3b] = '\0';
  arg1[0x34] = '\0';
  arg1[0x35] = '\0';
  arg1[0x36] = '\0';
  arg1[0x37] = '\0';
  *arg1 = '\0';
  return arg1;
}



/* ui_draw_textured_quad @ 00417ae0 */

/* binds a texture and draws a screen-space quad */

void ui_draw_textured_quad(int texture_id,int x,int y,int w,int h)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  (*grim_interface_ptr->vtable->grim_bind_texture)(h,0);
  iVar4 = 0x3f800000;
  iVar3 = 0x3f800000;
  iVar2 = 0;
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  iVar1 = 1;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_draw_quad)((float)iVar1,(float)iVar2,(float)iVar3,(float)iVar4)
  ;
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  return;
}



/* ui_element_set_rect @ 00419ba0 */

/* sets element quad vertices/UVs for a size and offset */

void __cdecl ui_element_set_rect(ui_element_t *element,float width,float height,float *offset)

{
  float fVar1;
  float fVar2;
  _func_1 *p_Var3;
  uchar *puVar4;
  int iVar5;
  
  fVar1 = 1.0 / width;
  element->active = '\0';
  element->enabled = '\0';
  element->_pad0[0] = 0x80;
  element->_pad0[1] = '?';
  element->_pad0[2] = '\0';
  element->_pad0[3] = '\0';
  element->_pad0[4] = 0x80;
  element->_pad0[5] = '?';
  p_Var3 = (_func_1 *)(1.0 / height);
  element->pos_y = width - 1.0;
  element->_pad1[0] = '\0';
  element->_pad1[1] = '\0';
  element->_pad1[2] = 0x80;
  element->_pad1[3] = '?';
  element->quad0[6] = 1.0;
  element->quad0[7] = height - 1.0;
  *(float *)element->_pad2 = width - 1.0;
  element->quad0[0] = height - 1.0;
  *(float *)(element->_pad0 + 0x12) = fVar1;
  fVar2 = 1.0 - fVar1;
  element->pos_x = (float)p_Var3;
  *(float *)(element->_pad1 + 0x10) = fVar2;
  element->on_activate = p_Var3;
  element->quad0[0xb] = fVar1;
  element->quad0[4] = fVar2;
  element->quad0[0xc] = fVar2;
  element->quad0[5] = 1.0 - (float)p_Var3;
  iVar5 = 4;
  puVar4 = element->_pad0 + 2;
  do {
    *(float *)(puVar4 + 0xc) = -NAN;
    *(float *)(puVar4 + 4) = 0.5;
    *(float *)(puVar4 + 8) = 1.0;
    iVar5 = iVar5 + -1;
    *(float *)(puVar4 + -4) = *(float *)(puVar4 + -4) + *offset;
    *(float *)puVar4 = *(float *)puVar4 + offset[1];
    puVar4 = puVar4 + 0x1c;
  } while (iVar5 != 0);
  return;
}



/* ui_element_load @ 00419d00 */

/* loads a UI element JAZ asset and logs failures */

void __cdecl ui_element_load(ui_element_t *element,char *jaz_path)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char local_100 [248];
  int iStack_8;
  
  uVar3 = 0xffffffff;
  pcVar5 = jaz_path;
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
  pcVar6 = local_100;
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
  uVar3 = 0xffffffff;
  pcVar5 = jaz_path;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  local_100[~uVar3 - 5] = '\0';
  if (*(float *)((int)cv_silentloads + 0xc) == 0.0) {
    console_printf(&console_log_queue,s_Loading_uiElement__s_004737b4,local_100);
  }
  (*grim_interface_ptr->vtable->grim_load_texture)(local_100,jaz_path);
  iVar2 = (*grim_interface_ptr->vtable->grim_get_texture_handle)(&stack0xfffffef8);
  *(int *)(iStack_8 + 0xe0) = iVar2;
  if (iVar2 == -1) {
    console_printf(&console_log_queue,s___FAILED_Loading_uiElement__s_00473794,&stack0xfffffef4);
  }
  return;
}



/* ui_menu_assets_init @ 00419dd0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* loads menu UI elements and seeds layout copies */

void ui_menu_assets_init(void)

{
  uchar *puVar1;
  int iVar2;
  uchar *puVar3;
  float local_8 [2];
  
  ui_element_load((ui_element_t *)&crt_file_buffer_pool,s_ui_ui_signCrimson_jaz_004737f4);
  local_8[0] = -577.44;
  local_8[1] = -62.0;
  ui_element_set_rect((ui_element_t *)&crt_file_buffer_pool,573.44,143.36,local_8);
  ui_element_load(&ui_menu_item_element,s_ui_ui_menuItem_jaz_004737e0);
  local_8[0] = -72.0;
  local_8[1] = -60.0;
  ui_element_set_rect(&ui_menu_item_element,512.0,64.0,local_8);
  ui_element_load((ui_element_t *)(ui_menu_item_element._pad3 + 4),s_ui_ui_menuPanel_jaz_004737cc);
  local_8[0] = 20.0;
  local_8[1] = -82.0;
  ui_element_set_rect((ui_element_t *)(ui_menu_item_element._pad3 + 4),512.0,256.0,local_8);
  puVar1 = ui_menu_item_element._pad3;
  puVar3 = ui_menu_item_element._pad4 + 0xac;
  for (iVar2 = 0x3a; puVar1 = puVar1 + 4, iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar3 = puVar3 + 4;
  }
  ui_menu_item_element._pad5[0xac] = '\b';
  ui_menu_item_element._pad5[0xad] = '\0';
  ui_menu_item_element._pad5[0xae] = '\0';
  ui_menu_item_element._pad5[0xaf] = '\0';
  puVar1 = ui_menu_item_element._pad5 + 0x1c;
  puVar3 = ui_menu_item_element._pad5 + 0x8c;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar1 = puVar1 + 4;
    puVar3 = puVar3 + 4;
  }
  puVar1 = ui_menu_item_element._pad5;
  puVar3 = ui_menu_item_element._pad5 + 0x70;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar1 = puVar1 + 4;
    puVar3 = puVar3 + 4;
  }
  ui_menu_item_element._pad5._4_4_ = (float)ui_menu_item_element._pad5._4_4_ - 116.0;
  ui_menu_item_element._pad5._32_4_ = (float)ui_menu_item_element._pad5._32_4_ - 116.0;
  ui_menu_item_element._pad5[0x18] = '\0';
  ui_menu_item_element._pad5[0x19] = '\0';
  ui_menu_item_element._pad5[0x1a] = '\x02';
  ui_menu_item_element._pad5[0x1b] = '?';
  ui_menu_item_element._pad5[0x34] = '\0';
  ui_menu_item_element._pad5[0x35] = '\0';
  ui_menu_item_element._pad5[0x36] = '\x02';
  ui_menu_item_element._pad5[0x37] = '?';
  puVar1 = ui_menu_item_element._pad5 + 0x1c;
  puVar3 = ui_menu_item_element._pad5 + 0x38;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar1 = puVar1 + 4;
    puVar3 = puVar3 + 4;
  }
  puVar1 = ui_menu_item_element._pad5;
  puVar3 = ui_menu_item_element._pad5 + 0x54;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar1 = puVar1 + 4;
    puVar3 = puVar3 + 4;
  }
  ui_menu_item_element._pad5._60_4_ = (float)ui_menu_item_element._pad5._60_4_ + 124.0;
  ui_menu_item_element._pad5._88_4_ = (float)ui_menu_item_element._pad5._88_4_ + 124.0;
  ui_menu_item_element._pad5._116_4_ = (float)ui_menu_item_element._pad5._116_4_ + 124.0;
  ui_menu_item_element._pad5[0x50] = '\0';
  ui_menu_item_element._pad5[0x51] = '\0';
  ui_menu_item_element._pad5[0x52] = '\x16';
  ui_menu_item_element._pad5[0x53] = '?';
  ui_menu_item_element._pad5[0x6c] = '\0';
  ui_menu_item_element._pad5[0x6d] = '\0';
  ui_menu_item_element._pad5[0x6e] = '\x16';
  ui_menu_item_element._pad5[0x6f] = '?';
  ui_menu_item_element._pad5._144_4_ = (float)ui_menu_item_element._pad5._144_4_ + 124.0;
  puVar1 = ui_menu_item_element._pad4 + 0xac;
  do {
    *(float *)(puVar1 + 4) = *(float *)(puVar1 + 4);
    puVar3 = puVar1 + 0x1c;
    *(float *)puVar1 = *(float *)puVar1 - 84.0;
    puVar1 = puVar3;
  } while ((int)puVar3 < 0x48fe58);
  puVar1 = ui_menu_item_element._pad4 + 0xac;
  puVar3 = ui_menu_item_element._pad5 + 0xb0;
  for (iVar2 = 0x3a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)puVar3 = *(undefined4 *)puVar1;
    puVar1 = puVar1 + 4;
    puVar3 = puVar3 + 4;
  }
  perk_screen_y_offset = (float)ui_menu_item_element._pad5._60_4_ - 100.0;
  perk_screen_y_offset_b = perk_screen_y_offset_b - 100.0;
  _DAT_0048ff0c = _DAT_0048ff0c - 100.0;
  _DAT_0048ff28 = _DAT_0048ff28 - 100.0;
  ui_menu_layout_init();
  return;
}



/* ui_cursor_render @ 0041a040 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the in-game cursor/crosshair sprites */

void ui_cursor_render(void)

{
  IGrim2D_vtbl *pIVar1;
  float10 extraout_ST0;
  
  perk_screen_anim_timer_a = frame_dt + perk_screen_anim_timer_a;
  ui_perk_select_idx = frame_dt * 1.1 + ui_perk_select_idx;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
  effect_select_texture(0xd);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  fsin((float10)ui_perk_select_idx);
  pIVar1 = grim_interface_ptr->vtable;
  crt_ci_pow();
  (*pIVar1->grim_set_color)(1.0,1.0,1.0,(float)((extraout_ST0 + (float10)2.0) * (float10)0.32));
  (*grim_interface_ptr->vtable->grim_draw_quad)(ui_mouse_x - 28.0,ui_mouse_y - 28.0,64.0,64.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)(ui_mouse_x - 10.0,ui_mouse_y - 18.0,64.0,64.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)(ui_mouse_x - 18.0,ui_mouse_y - 10.0,64.0,64.0);
  (*grim_interface_ptr->vtable->grim_draw_quad)
            ((ui_mouse_x - 64.0) + 16.0,(ui_mouse_y - 64.0) + 16.0,128.0,128.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_bind_texture)(texture_cursor_id,0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(ui_mouse_x - 2.0,ui_mouse_y - 2.0,32.0,32.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  return;
}



/* ui_render_aim_enhancement @ 0041a320 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the aim enhancement overlay (cv_aimEnhancementFade-driven) */

void ui_render_aim_enhancement(void)

{
  float *pfStack_24;
  
  perk_screen_anim_timer_b = frame_dt + perk_screen_anim_timer_b;
  perk_screen_anim_timer_c = frame_dt * 0.6 + perk_screen_anim_timer_c;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
  effect_select_texture(0xd);
  if (1.0 < *(float *)((int)cv_aimEnhancementFade + 0xc)) {
    *(undefined4 *)((int)cv_aimEnhancementFade + 0xc) = 0x3f800000;
  }
  if (*(float *)((int)cv_aimEnhancementFade + 0xc) < 0.0) {
    *(undefined4 *)((int)cv_aimEnhancementFade + 0xc) = 0;
  }
  (*grim_interface_ptr->vtable->grim_set_color)
            (1.0,1.0,1.0,*(float *)((int)cv_aimEnhancementFade + 0xc));
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(*pfStack_24 - 32.0,pfStack_24[1] - 32.0,64.0,64.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_bind_texture)(texture_aim_id,0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)
            (1.0,1.0,1.0,*(float *)((int)cv_aimEnhancementFade + 0xc));
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(*pfStack_24 - 10.0,pfStack_24[1] - 10.0,20.0,20.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  return;
}



/* ui_elements_update_and_render @ 0041a530 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* advances UI timeline, handles transitions, updates + renders all UI elements */

void ui_elements_update_and_render(void)

{
  int iVar1;
  ui_element_t **ppuVar2;
  float10 fVar3;
  float10 fVar4;
  
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  if (console_open_flag == '\0') {
    iVar1 = frame_dt_ms;
    if (ui_transition_direction == '\0') {
      iVar1 = -frame_dt_ms;
    }
    ui_elements_timeline = ui_elements_timeline + iVar1;
  }
  if (ui_elements_timeline < 0) {
    ui_elements_timeline = 0;
    if ((demo_mode_active != '\0') && (game_state_pending == 0)) {
      terrain_generate_random();
    }
    game_state_set(game_state_pending);
    game_state_pending = 0x19;
  }
  iVar1 = ui_elements_max_timeline();
  if (iVar1 < ui_elements_timeline) {
    if ((game_state_id == 0) && (demo_mode_active != '\0')) {
      demo_mode_active = '\0';
      config_load_presets();
    }
    fVar3 = (float10)fcos((float10)0.0);
    ui_sign_crimson_update_disabled = 1;
    _ui_rotation_cos = (float)fVar3;
    fVar4 = (float10)fsin((float10)0.0);
    _ui_rotation_neg_sin = (float)-fVar4;
    _ui_rotation_sin = (float)fVar4;
    _ui_rotation_cos_b = (float)fVar3;
    ui_elements_timeline = ui_elements_max_timeline();
  }
  if (game_state_id != 9) {
    ppuVar2 = &ui_element_table_start;
    do {
      ui_element_update(*ppuVar2);
      ui_element_render(*ppuVar2);
      ppuVar2 = ppuVar2 + -1;
    } while (0x48f167 < (int)ppuVar2);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    if (game_state_id == 10) {
      game_quit_flag = 1;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  }
  return;
}



/* ui_draw_progress_bar @ 0041a6d0 */

/* draws a filled progress bar with a tinted background */

void __cdecl ui_draw_progress_bar(float *xy,float width,float ratio,float *rgba)

{
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_10 = *rgba * 0.6;
  local_c = rgba[1] * 0.6;
  local_8 = rgba[2] * 0.6;
  local_4 = rgba[3] * 0.4;
  local_18 = *xy;
  local_14 = xy[1];
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_18,width,4.0);
  local_18 = xy[1] + 1.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)
            ((float *)&stack0xffffffe4,((float)xy - 2.0) * width,2.0);
  return;
}



/* ui_render_hud @ 0041aed0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders the in-game HUD (health, weapon icons, player UI) */

void ui_render_hud(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  IGrim2D_vtbl *pIVar5;
  float unaff_EBX;
  int iVar6;
  char *pcVar7;
  float10 extraout_ST0;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  longlong lVar11;
  undefined1 *puVar12;
  float *rgba;
  uint value;
  char *pcVar13;
  float fVar14;
  float in_stack_ffffff8c;
  float fVar15;
  float fVar16;
  int iVar17;
  float a;
  float fVar18;
  int iVar19;
  float fVar20;
  float fVar21;
  float fStack_4c;
  float fStack_2c;
  float fStack_24;
  float fStack_10;
  
  fStack_4c = 6.032119e-39;
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  fVar20 = 2.94273e-44;
  fVar21 = 1.4013e-45;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_10 * 0.7);
  iVar19 = 0;
  pIVar5 = grim_interface_ptr->vtable;
  iVar2 = (*pIVar5->grim_get_texture_handle)(s_iGameUI_texture_name);
  (*pIVar5->grim_bind_texture)(iVar2,iVar19);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.001953125,0.015625,0.9980469,0.984375);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  fVar18 = 512.0;
  a = 0.0;
  (*grim_interface_ptr->vtable->grim_draw_quad)(0.0,0.0,512.0,64.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  if (hud_show_health_icon != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    if (config_blob.reserved0._20_4_ == 1) {
      unaff_EBX = 21.0;
      fStack_2c = 21.0;
    }
    else {
      unaff_EBX = 12.0;
      fStack_2c = 12.0;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_24 * 0.8);
    iVar19 = 0;
    pIVar5 = grim_interface_ptr->vtable;
    iVar2 = (*pIVar5->grim_get_texture_handle)(s_iHeart_texture_name);
    (*pIVar5->grim_bind_texture)(iVar2,iVar19);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.03125,0.03125,0.96875,0.96875);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    fVar21 = 2.0;
    if (config_blob.reserved0._20_4_ == 1) {
      if (player_state_table.health < 30.0) {
        fVar21 = 5.0;
      }
      fsin((float10)game_time_s * (float10)fVar21);
      crt_ci_pow();
      fVar8 = extraout_ST0 * (float10)4.0 + (float10)14.0;
      pIVar5 = grim_interface_ptr->vtable;
      fVar9 = fVar8 + fVar8;
      fVar10 = (float10)fStack_2c - fVar8;
    }
    else {
      if (player_state_table.health < 30.0) {
        fVar21 = 5.0;
      }
      fsin((float10)game_time_s * (float10)fVar21);
      crt_ci_pow();
      fVar8 = (extraout_ST0_00 * (float10)4.0 + (float10)14.0) * (float10)0.5;
      (*grim_interface_ptr->vtable->grim_draw_quad)
                ((float)((float10)27.0 - fVar8),(float)((float10)fStack_2c - fVar8),
                 (float)(fVar8 + fVar8),(float)(fVar8 + fVar8));
      if (30.0 <= player2_health) {
        fVar8 = (float10)fVar21;
      }
      else {
        fVar8 = (float10)5.0;
      }
      fsin((float10)game_time_s * fVar8 + (float10)1.5707964);
      crt_ci_pow();
      pIVar5 = grim_interface_ptr->vtable;
      fVar8 = (extraout_ST0_01 * (float10)4.0 + (float10)14.0) * (float10)0.5;
      fVar9 = fVar8 + fVar8;
      fVar10 = ((float10)fStack_2c - fVar8) + (float10)15.0;
    }
    in_stack_ffffff8c = (float)fVar9;
    fVar20 = in_stack_ffffff8c;
    (*pIVar5->grim_draw_quad)
              ((float)((float10)27.0 - fVar8),(float)fVar10,in_stack_ffffff8c,in_stack_ffffff8c);
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  if (hud_show_weapon_icon != '\0') {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_24 * 0.8);
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_weapon_icons_texture,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    if (config_blob.reserved0._20_4_ == 1) {
      (*grim_interface_ptr->vtable->grim_set_sub_rect)
                (8,2,1,(&weapon_table)[player_state_table.weapon_id].hud_icon_id << 1);
      fVar16 = 32.0;
      fVar15 = 64.0;
      fVar14 = 2.0;
      pIVar5 = grim_interface_ptr->vtable;
    }
    else {
      (*grim_interface_ptr->vtable->grim_set_sub_rect)
                (8,2,1,(&weapon_table)[player_state_table.weapon_id].hud_icon_id << 1);
      (*grim_interface_ptr->vtable->grim_draw_quad)(220.0,4.0,32.0,16.0);
      (*grim_interface_ptr->vtable->grim_set_sub_rect)
                (8,2,1,(&weapon_table)[player2_weapon_id].hud_icon_id << 1);
      fVar16 = 16.0;
      fVar15 = 32.0;
      fVar14 = 20.0;
      pIVar5 = grim_interface_ptr->vtable;
    }
    (*pIVar5->grim_draw_quad)(220.0,fVar14,fVar15,fVar16);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    in_stack_ffffff8c = 1.0;
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  if (hud_show_health_icon != '\0') {
    (*grim_interface_ptr->vtable->grim_bind_texture)((int)texture_life_id,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    if (config_blob.reserved0._20_4_ == 1) {
      fVar14 = 16.0;
    }
    else {
      fVar14 = 6.0;
    }
    render_overlay_player_index = 0;
    if (0 < (int)config_blob.reserved0._20_4_) {
      fVar18 = unaff_EBX * 0.5;
      do {
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,unaff_EBX * 0.5);
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  (64.0,(float)(render_overlay_player_index << 4) + fVar14,120.0,9.0);
        fVar15 = (&player_state_table)[render_overlay_player_index].health * 0.01;
        if (fVar15 <= 1.0) {
          if (fVar15 < 0.0) {
            fVar15 = 0.0;
          }
        }
        else {
          fVar15 = 1.0;
        }
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,unaff_EBX * 0.8);
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,fVar15,1.0);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  (64.0,(float)(render_overlay_player_index << 4) + fVar14,fVar15 * 120.0,9.0);
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  if (hud_show_weapon_icon != '\0') {
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    if (config_blob.reserved0._20_4_ == 1) {
      fStack_4c = 10.0;
      fVar14 = 10.0;
      fVar15 = 300.0;
    }
    else {
      fStack_4c = 4.0;
      fVar14 = 4.0;
      fVar15 = 290.0;
    }
    render_overlay_player_index = 0;
    if (0 < (int)config_blob.reserved0._20_4_) {
      do {
        iVar2 = (&weapon_ammo_class)
                [(&player_state_table)[render_overlay_player_index].weapon_id * 0x1f];
        if (iVar2 == 1) {
          pcVar13 = s_ui_ind_fire_jaz;
          pIVar5 = grim_interface_ptr->vtable;
        }
        else if (iVar2 == 0) {
          pcVar13 = s_ui_ind_bullet_jaz;
          pIVar5 = grim_interface_ptr->vtable;
        }
        else if (iVar2 == 2) {
          pcVar13 = s_ui_ind_rocket_jaz;
          pIVar5 = grim_interface_ptr->vtable;
        }
        else {
          pcVar13 = s_ui_ind_electric_jaz;
          pIVar5 = grim_interface_ptr->vtable;
        }
        fVar16 = 0.0;
        iVar2 = (*pIVar5->grim_get_texture_handle)(pcVar13);
        (*pIVar5->grim_bind_texture)(iVar2,(int)fVar16);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        lVar11 = __ftol();
        iVar2 = (int)lVar11;
        if (0x1e < iVar2) {
          iVar2 = 0x14;
        }
        lVar11 = __ftol();
        iVar19 = (int)lVar11;
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
        iVar6 = 0;
        if (0 < iVar2) {
          iVar17 = 0;
          do {
            fVar16 = unaff_EBX;
            if (iVar19 <= iVar6) {
              fVar16 = unaff_EBX * 0.3;
            }
            (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar16);
            (*grim_interface_ptr->vtable->grim_draw_quad)
                      ((float)iVar17 + fVar15,(float)(render_overlay_player_index * 0xe) + fVar14,
                       6.0,16.0);
            iVar6 = iVar6 + 1;
            iVar17 = iVar17 + 6;
          } while (iVar6 < iVar2);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
        if (iVar2 < iVar19) {
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
          (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
          a = (float)(iVar6 * 6);
          (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                    (grim_interface_ptr,(float)(int)a + fVar20 + 8.0,
                     (float)(render_overlay_player_index * 0xe) + fVar21 + 1.0,&s_extra_ammo_format,
                     iVar19 - iVar2);
        }
        render_overlay_player_index = render_overlay_player_index + 1;
      } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
    }
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  puVar12 = (undefined1 *)0x41b94d;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  iVar2 = 0x4e;
  value = 0x4e;
  if (hud_show_experience_bar != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
    (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    fVar18 = 0.0;
    if (quest_spawn_timeline < 1000) {
      fVar18 = (float)(1000 - quest_spawn_timeline) * -0.128;
    }
    (*grim_interface_ptr->vtable->grim_draw_quad)(fVar18 - 90.0,67.0,182.0,53.0);
    (*grim_interface_ptr->vtable->grim_draw_quad)(-80.0,107.0,182.0,53.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,in_stack_ffffff8c * 0.9);
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_table_texture,0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_draw_quad)(fVar18 + 2.0,78.0,32.0,32.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,in_stack_ffffff8c * 0.9);
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_hands_texture,0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((float)(quest_spawn_timeline / 1000) * 0.10471976);
    (*grim_interface_ptr->vtable->grim_draw_quad)(fVar18 + 2.0,78.0,32.0,32.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
    if ((quest_spawn_timeline / 1000) % 0x3c < 10) {
      pcVar13 = s__d_0_d_00473150;
    }
    else {
      pcVar13 = s__d__d_00473148;
    }
    in_stack_ffffff8c = (float)((quest_spawn_timeline / 1000) / 0x3c);
    fVar21 = fVar21 + 32.0;
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)(grim_interface_ptr,fVar21,86.0,pcVar13);
    fVar14 = 3.36312e-44;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3ee66666);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,18.0,122.0,s_Progress_00473824);
    if ((crt_file_info_table & 1) == 0) {
      crt_file_info_table = crt_file_info_table | 1;
      progress_bar_color_r = 0x3e4ccccd;
      progress_bar_color_g = 0x3f4ccccd;
      progress_bar_color_b = 0x3e99999a;
      progress_bar_color_a = 1.0;
      crt_atexit(&DAT_0041ca80);
    }
    progress_bar_color_a = unaff_EBX * 0.8;
    iVar2 = 0;
    perk_screen_state_flag = 0;
    if (0 < quest_spawn_count) {
      piVar3 = &quest_spawn_table.pos_y_block.heading_block.count;
      iVar19 = quest_spawn_count;
      do {
        iVar6 = *piVar3;
        piVar3 = piVar3 + 6;
        iVar2 = iVar2 + iVar6;
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
    }
    perk_screen_kill_progress = (float)(int)highscore_active_record.creature_kill_count /
                   (float)(creature_spawned_count + iVar2);
    ui_draw_progress_bar((float *)&stack0xffffffbc,70.0,perk_screen_kill_progress,(float *)&DAT_004871a0);
    iVar2 = 0x9e;
    if (quest_elapsed_timer_ms < 500) {
      fVar15 = (float)(quest_elapsed_timer_ms * 2) * 0.001;
LAB_0041bde3:
      if (1.0 < fVar15) {
LAB_0041bdf8:
        fVar15 = 1.0;
      }
    }
    else {
      if (quest_elapsed_timer_ms < 0x5dc) goto LAB_0041bdf8;
      if (quest_elapsed_timer_ms < 2000) {
        fVar15 = 1.0 - (float)(quest_elapsed_timer_ms * 2 + -3000) * 0.001;
        goto LAB_0041bde3;
      }
      fVar15 = 0.0;
    }
    fVar18 = fVar15 * unaff_EBX;
    fVar16 = 1.0;
    value = 0x3f800000;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar18);
    if (0.0 <= fVar15) {
      value = 0x3f4ccccd;
      iVar19 = -1;
      pcVar7 = (&quest_selected_meta)[quest_stage_minor + -0xb + quest_stage_major * 10].name;
      do {
        if (iVar19 == 0) break;
        iVar19 = iVar19 + -1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      if (config_blob.screen_width < 0x281) {
        value = 0x3f400000;
      }
      fVar15 = 3.36312e-44;
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,value);
      (*grim_interface_ptr->vtable->grim_draw_text_mono)
                ((float)(config_blob.screen_width / 2) - (float)(int)fVar20 * fVar14 * 8.0,
                 (float)(config_blob.screen_height / 2 + -0x20),
                 (&quest_selected_meta)[quest_stage_minor + -0xb + quest_stage_major * 10].name);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,(uint)(fVar21 - 0.2));
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar16 * 0.5);
      if (10 < quest_stage_minor) {
        quest_stage_major = quest_stage_major + 1;
        quest_stage_minor = quest_stage_minor + -10;
      }
      crt_sprintf(&bonus_hud_slot_table_end_ptr,s__d__d_0047381c,quest_stage_major,quest_stage_minor);
      puVar12 = &bonus_hud_slot_table_end_ptr;
      uVar4 = 0xffffffff;
      pcVar7 = &bonus_hud_slot_table_end_ptr;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      (*grim_interface_ptr->vtable->grim_draw_text_mono_fmt)
                (grim_interface_ptr,
                 (((float)pcVar13 - (float)(~uVar4 - 1) * fVar15 * 8.0) - fVar15 * 32.0) - 4.0,
                 (fVar15 * 23.36 + (float)(config_blob.screen_height / 2 + -0x20)) - fVar15 * 16.0,
                 &bonus_hud_slot_table_end_ptr);
    }
    if (0 < quest_transition_timer_ms) {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f800000);
      fVar21 = (float)quest_transition_timer_ms * 0.0004 * 0.13 + 0.95;
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,(float)puVar12 * in_stack_ffffff8c);
      (*grim_interface_ptr->vtable->grim_bind_texture)(texture_level_complete_id,0);
      (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
      (*grim_interface_ptr->vtable->grim_draw_quad)
                ((float)(config_blob.screen_width / 2) - fVar21 * 128.0,
                 (float)(config_blob.screen_height / 2) - fVar21 * 16.0,fVar21 * 256.0,fVar21 * 32.0
                );
      (*grim_interface_ptr->vtable->grim_end_batch)();
    }
  }
  if (hud_show_timer != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    fVar21 = in_stack_ffffff8c * 0.9;
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar21);
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_table_texture,0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_draw_quad)(220.0,2.0,32.0,32.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar21);
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_clock_hands_texture,0);
    (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_set_rotation)
              ((float)((int)highscore_active_record.survival_elapsed_ms / 1000) * 0.10471976);
    (*grim_interface_ptr->vtable->grim_draw_quad)(220.0,2.0,32.0,32.0);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    value = 0x3f000000;
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,255.0,10.0,s__d_seconds_00473810,
               (int)highscore_active_record.survival_elapsed_ms / 1000);
  }
  if (hud_show_ammo_icon == '\0') goto LAB_0041c783;
  (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(-68.0,(float)(iVar2 + -0x12),182.0,53.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  if (player_state_table.experience == 0) {
    survival_xp_smoothed = player_state_table.experience;
  }
  else if (survival_xp_smoothed < player_state_table.experience) {
    iVar19 = frame_dt_ms / 2;
    if (iVar19 < 1) {
      iVar19 = 1;
    }
    uVar4 = survival_xp_smoothed - player_state_table.experience >> 0x1f;
    iVar6 = (survival_xp_smoothed - player_state_table.experience ^ uVar4) - uVar4;
    if (1000 < iVar6) {
      iVar19 = iVar19 * (iVar6 / 100);
    }
    survival_xp_smoothed = survival_xp_smoothed + iVar19;
    if (player_state_table.experience < survival_xp_smoothed) {
LAB_0041c5bf:
      survival_xp_smoothed = player_state_table.experience;
    }
  }
  else if (player_state_table.experience < survival_xp_smoothed) {
    iVar19 = frame_dt_ms / 2;
    if (iVar19 < 1) {
      iVar19 = 1;
    }
    uVar4 = survival_xp_smoothed - player_state_table.experience >> 0x1f;
    iVar6 = (survival_xp_smoothed - player_state_table.experience ^ uVar4) - uVar4;
    if (1000 < iVar6) {
      iVar19 = iVar19 * (iVar6 / 100);
    }
    survival_xp_smoothed = survival_xp_smoothed - iVar19;
    if (survival_xp_smoothed < player_state_table.experience) goto LAB_0041c5bf;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c * 0.9);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,4.0,(float)(int)value,&s_hud_exp_format);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,26.0,(float)(iVar2 + -4),&s_int_format,survival_xp_smoothed);
  ui_text_alpha = fVar18;
  (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&ui_text_color_rgba);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,85.0,(float)(iVar2 + 1),&s_int_format,player_state_table.level);
  iVar19 = player_state_table.level;
  ui_text_alpha = 0.7;
  crt_ci_pow();
  lVar11 = __ftol();
  iVar6 = 1000 - (int)lVar11;
  if (iVar19 == 1) {
    iVar6 = 0;
  }
  in_stack_ffffff8c = (float)(iVar2 + 0xd);
  rgba = (float *)&stack0xffffff78;
  crt_ci_pow();
  lVar11 = __ftol();
  ui_draw_progress_bar
            ((float *)&stack0xffffff88,54.0,
             (float)(extraout_ST0_02 / (float10)((1000 - (int)lVar11) - iVar6)),rgba);
LAB_0041c783:
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  iVar2 = 0;
  do {
    bonus_hud_slot_update_and_render((float *)&stack0xffffff7c,iVar2);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  lVar11 = __ftol();
  iVar2 = (int)lVar11 + 1;
  render_overlay_player_index = 0;
  if (0 < (int)config_blob.reserved0._20_4_) {
    iVar19 = (int)lVar11 + -5;
    iVar6 = iVar2;
    iVar17 = iVar19;
    do {
      if (0.0 < (float)(&player_aux_timer)[render_overlay_player_index]) {
        fVar21 = (float)(&player_aux_timer)[render_overlay_player_index];
        if (1.0 <= fVar21) {
          fVar18 = 1.4;
        }
        else {
          fVar18 = 0.5;
        }
        (&player_aux_timer)[render_overlay_player_index] =
             (float)(&player_aux_timer)[render_overlay_player_index] - frame_dt * fVar18;
        if (1.0 < fVar21) {
          fVar21 = 2.0 - fVar21;
        }
        if (fVar21 < 0.0) {
          fVar21 = 0.0;
        }
        fVar21 = fVar21 * in_stack_ffffff8c;
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar21 * 0.8);
        (*grim_interface_ptr->vtable->grim_bind_texture)(texture_panel_id,0);
        (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
        (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        (*grim_interface_ptr->vtable->grim_draw_quad)(-12.0,(float)(iVar19 + -0xc),182.0,53.0);
        (*grim_interface_ptr->vtable->grim_end_batch)();
        (*grim_interface_ptr->vtable->grim_bind_texture)(ui_weapon_icons_texture,0);
        (*grim_interface_ptr->vtable->grim_set_sub_rect)
                  (8,2,1,(&weapon_table)
                         [(&player_state_table)[render_overlay_player_index].weapon_id].hud_icon_id
                         << 1);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        (*grim_interface_ptr->vtable->grim_draw_quad)(105.0,(float)iVar17,60.0,30.0);
        (*grim_interface_ptr->vtable->grim_end_batch)();
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
        (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar21);
        (*grim_interface_ptr->vtable->grim_draw_text_small)
                  (8.0,(float)iVar6,
                   (&weapon_table)[(&player_state_table)[render_overlay_player_index].weapon_id].
                   name);
        iVar2 = iVar2 + 0x20;
        iVar19 = iVar19 + 0x20;
        iVar6 = iVar2;
        iVar17 = iVar19;
      }
      render_overlay_player_index = render_overlay_player_index + 1;
    } while (render_overlay_player_index < (int)config_blob.reserved0._20_4_);
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  render_overlay_player_index = 0;
  return;
}



/* hud_update_and_render @ 0041ca90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates HUD flags/targets and renders the HUD */

void hud_update_and_render(void)

{
  float fVar1;
  float local_28;
  float local_20;
  float local_1c;
  float local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  fVar1 = (float)ui_elements_timeline / (float)(ui_timeline_target_end - ui_timeline_target_start);
  if ((1.0 < fVar1) || (fVar1 == 1.0)) {
    ui_state_init_flag = 0;
  }
  if (doctor_perk_target_creature != -1) {
    local_14 = camera_offset_y + (&creature_pool)[doctor_perk_target_creature].pos_y;
    local_28 = (&creature_pool)[doctor_perk_target_creature].health / (&creature_pool)[doctor_perk_target_creature].max_health;
    if (local_28 <= 1.0) {
      if (local_28 < 0.0) {
        local_28 = 0.0;
      }
    }
    else {
      local_28 = 1.0;
    }
    local_8 = 0x3e4ccccd;
    local_10 = (1.0 - local_28) * 0.9 + 0.1;
    local_4 = 0x3f333333;
    local_c = local_28 * 0.9 + 0.1;
    local_20 = (camera_offset_x + (&creature_pool)[doctor_perk_target_creature].pos_x) - 32.0;
    local_1c = local_14 + 32.0;
    ui_draw_progress_bar(&local_20,64.0,local_28,&local_10);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  }
  if (config_blob.reserved0._24_4_ == 3) {
    hud_show_health_icon = 1;
    hud_show_weapon_icon = 1;
    hud_show_ammo_icon = 1;
    hud_show_experience_bar = 1;
  }
  else {
    if (config_blob.reserved0._24_4_ == 1) {
      hud_show_health_icon = 1;
      hud_show_weapon_icon = 1;
      hud_show_ammo_icon = 1;
    }
    else {
      if (config_blob.reserved0._24_4_ == 2) {
        hud_show_health_icon = 1;
        hud_show_weapon_icon = 0;
        hud_show_ammo_icon = 0;
        hud_show_experience_bar = 0;
        hud_show_timer = 1;
        goto LAB_0041cc88;
      }
      if (config_blob.reserved0._24_4_ == 4) {
        hud_show_health_icon = 1;
        hud_show_weapon_icon = 0;
        hud_show_ammo_icon = 1;
        hud_show_experience_bar = 0;
        hud_show_timer = 1;
        goto LAB_0041cc88;
      }
      hud_show_health_icon = 0;
      hud_show_weapon_icon = 0;
      hud_show_ammo_icon = 0;
    }
    hud_show_experience_bar = 0;
  }
  hud_show_timer = 0;
LAB_0041cc88:
  if (demo_mode_active == '\0') {
    ui_render_hud();
  }
  return;
}



/* wrap_text_to_width_alloc @ 0042fd00 */

/* allocates a wrapped copy of text to fit max_width_px (replaces spaces with '\n' using
   grim_measure_text_width per char) */

char * __thiscall wrap_text_to_width_alloc(void *this,char *text,int max_width_px)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  undefined4 uStack_4;
  
  uVar4 = 0xffffffff;
  pcVar2 = text;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar5 = ~uVar4 - 1;
  uStack_4 = (uint)this & 0xffffff;
  pcVar2 = operator_new(~uVar4);
  uVar4 = 0xffffffff;
  do {
    pcVar7 = text;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = text + 1;
    cVar1 = *text;
    text = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar7 + -uVar4;
  pcVar9 = pcVar2;
  for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar9 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar9 = pcVar9 + 1;
  }
  iVar8 = 0;
  iVar10 = max_width_px;
  if (0 < iVar5) {
    do {
      uStack_4._0_3_ = CONCAT12(pcVar2[iVar8],(undefined2)uStack_4);
      iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)((char *)((int)&uStack_4 + 2));
      iVar10 = iVar10 - iVar3;
      if (iVar10 < 0) {
        do {
          iVar10 = iVar8 + -1;
          iVar8 = iVar8 + -1;
        } while (pcVar2[iVar10] != ' ');
        pcVar2[iVar8] = '\n';
        iVar10 = max_width_px;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar5);
  }
  return pcVar2;
}



/* ui_menu_item_update @ 0043e5e0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* draws a text menu item, updates hover/press state, and returns 1 when activated */

int __cdecl ui_menu_item_update(float *xy,int *item)

{
  int *id;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined3 uVar4;
  longlong lVar5;
  float local_8;
  float local_4;
  
  id = item;
  iVar1 = ui_focus_update((int)item);
  if ((crt_stdio_stream_table & 1) == 0) {
    crt_stdio_stream_table = crt_stdio_stream_table | 1;
    _DAT_004ccd40 = 0x3e8c8c8d;
    _DAT_004ccd44 = 0x3f34b4b5;
    _DAT_004ccd48 = 0x3f70f0f1;
    _DAT_004ccd4c = 0x3f19999a;
    crt_atexit(&DAT_0043e820);
  }
  if ((crt_stdio_stream_table & 2) == 0) {
    crt_stdio_stream_table = crt_stdio_stream_table | 2;
    _DAT_004d0e28 = 0x3e8c8c8d;
    _DAT_004d0e2c = 0x3f34b4b5;
    _DAT_004d0e30 = 0x3f70f0f1;
    _DAT_004d0e34 = 0x3f800000;
    crt_atexit(&DAT_0043e810);
  }
  if ((char)iVar1 != '\0') {
    local_8 = *xy - 16.0;
    local_4 = xy[1];
    ui_focus_draw(&local_8);
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_measure_text_width)((char *)*item);
  item = (int *)(float)iVar2;
  if ((float)item <= 0.0) {
    item = (int *)0x41000000;
  }
  lVar5 = __ftol();
  iVar2 = ui_mouse_inside_rect(xy,0x10,(int)lVar5);
  *(char *)(id + 1) = (char)iVar2;
  if ((char)iVar2 == '\0') {
    (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&DAT_004ccd40);
  }
  else {
    ui_focus_set((int)id,'\0');
    (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&DAT_004d0e28);
  }
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy,xy[1],&s_fmt_percent_s,*id);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  local_8 = *xy;
  local_4 = xy[1] + 13.0;
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(&local_8,(float)item,1.0);
  uVar3 = (*grim_interface_ptr->vtable->grim_end_batch)();
  uVar4 = (undefined3)((uint)uVar3 >> 8);
  if (*(char *)((int)id + 6) == '\0') {
    *(undefined1 *)((int)id + 5) = 0;
    goto LAB_0043e7e0;
  }
  if ((char)iVar1 != '\0') {
    iVar1 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
    if ((char)iVar1 != '\0') {
LAB_0043e7cb:
      uVar4 = 0;
      *(undefined1 *)((int)id + 5) = 1;
      goto LAB_0043e7e0;
    }
    if ((char)id[1] != '\0') {
      iVar1 = input_primary_just_pressed();
      if ((char)iVar1 != '\0') goto LAB_0043e7cb;
    }
  }
  uVar4 = 0;
  *(undefined1 *)((int)id + 5) = 0;
LAB_0043e7e0:
  iVar1 = CONCAT31(uVar4,*(char *)((int)id + 5));
  if (*(char *)((int)id + 5) != '\0') {
    iVar1 = sfx_play(sfx_ui_buttonclick);
  }
  return CONCAT31((int3)((uint)iVar1 >> 8),*(undefined1 *)((int)id + 5));
}



/* ui_button_update @ 0043e830 */

/* draws a UI button, updates hover/press state, and returns 1 when activated */

int __cdecl ui_button_update(float *xy,ui_button_t *button)

{
  float *xy_00;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined3 uVar4;
  IGrim2D_vtbl *pIVar5;
  float unaff_EBP;
  longlong lVar6;
  float y;
  char *fmt;
  float fVar7;
  char *text;
  float fVar8;
  char cVar9;
  float local_18;
  float local_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  xy_00 = xy;
  iVar1 = ui_focus_update((int)button);
  if ((char)iVar1 != '\0') {
    local_18 = *xy - 16.0;
    local_14 = xy[1];
    ui_focus_draw(&local_18);
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_measure_text_width)(button->label);
  if (ui_button_small_texture == -1) {
    ui_button_small_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_ui_buttonSm_00474498);
  }
  if (ui_button_medium_texture == -1) {
    ui_button_medium_texture = (*grim_interface_ptr->vtable->grim_get_texture_handle)(s_ui_buttonMd_00474474);
  }
  if (((float)iVar2 < 40.0) || (xy = (float *)0x43110000, button->force_small != '\0')) {
    xy = (float *)0x42a40000;
  }
  if (button->force_wide != '\0') {
    xy = (float *)0x43110000;
  }
  xy_00[1] = xy_00[1] + 2.0;
  lVar6 = __ftol();
  iVar2 = ui_mouse_inside_rect(xy_00,0x1c,(int)lVar6);
  button->hovered = (uchar)iVar2;
  xy_00[1] = xy_00[1] - 2.0;
  if (button->hovered != '\0') {
    ui_focus_set((int)button,'\0');
  }
  if ((button->enabled == '\0') ||
     ((button->hovered == '\0' && (((char)iVar1 == '\0' || (ui_focus_timer_ms < 0x321)))))) {
    iVar1 = button->hover_anim + frame_dt_ms * -4;
  }
  else {
    iVar1 = button->hover_anim + frame_dt_ms * 6;
  }
  button->hover_anim = iVar1;
  if (0 < button->click_anim) {
    button->click_anim = button->click_anim + frame_dt_ms * -6;
  }
  if (button->click_anim < 0) {
    button->click_anim = 0;
  }
  if (button->hover_anim < 0) {
    button->hover_anim = 0;
  }
  else if (1000 < button->hover_anim) {
    button->hover_anim = 1000;
  }
  fStack_c = 0.5;
  fStack_8 = 0.7;
  fStack_4 = 0.0;
  if (0 < button->click_anim) {
    fVar8 = (float)button->click_anim;
    fStack_c = fVar8 * 0.0005 + 0.5;
    fStack_8 = fVar8 * 0.00070000003 + 0.7;
    if (1.0 < fStack_c) {
      fStack_c = 1.0;
    }
    if (1.0 < fStack_8) {
      fStack_8 = 1.0;
    }
  }
  local_18 = (float)button->hover_anim;
  fStack_10 = fStack_c;
  if (0 < (int)local_18) {
    fStack_4 = (float)(int)local_18 * 0.001 * button->alpha;
    local_18 = *xy_00 + 12.0;
    local_14 = xy_00[1] + 5.0;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_18,(float)xy - 24.0,22.0);
  }
  if ((unaff_EBP < 40.0) || (button->force_small != '\0')) {
    pIVar5 = grim_interface_ptr->vtable;
    iVar1 = ui_button_small_texture;
  }
  else {
    pIVar5 = grim_interface_ptr->vtable;
    iVar1 = ui_button_medium_texture;
  }
  (*pIVar5->grim_bind_texture)(iVar1,0);
  if (button->force_wide != '\0') {
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_button_medium_texture,0);
  }
  cVar9 = '\0';
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,button->alpha);
  fVar8 = 1.4013e-45;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  (*grim_interface_ptr->vtable->grim_draw_quad)(*xy_00,xy_00[1],local_14,32.0);
  (*grim_interface_ptr->vtable->grim_end_batch)();
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  if (button->hovered == '\0') {
    fVar7 = button->alpha * 0.7;
  }
  else {
    fVar7 = button->alpha;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar7);
  text = button->label;
  y = xy_00[1] + 10.0;
  fmt = &s_fmt_percent_s;
  pIVar5 = grim_interface_ptr->vtable;
  fVar7 = *xy_00;
  iVar1 = (*pIVar5->grim_measure_text_width)(text);
  uVar3 = (*pIVar5->grim_draw_text_small_fmt)
                    (grim_interface_ptr,((fVar8 * 0.5 + fVar7) - (float)(iVar1 / 2)) + 1.0,y,fmt,
                     text);
  uVar4 = (undefined3)((uint)uVar3 >> 8);
  if (button->enabled == '\0') {
    button->activated = '\0';
  }
  else if ((cVar9 == '\0') ||
          ((iVar1 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c), (char)iVar1 == '\0'
           && ((button->hovered == '\0' ||
               (iVar1 = input_primary_just_pressed(), (char)iVar1 == '\0')))))) {
    uVar4 = 0;
    button->activated = '\0';
  }
  else {
    uVar4 = 0;
    button->activated = '\x01';
  }
  iVar1 = CONCAT31(uVar4,button->activated);
  if (button->activated != '\0') {
    button->click_anim = 1000;
    iVar1 = sfx_play(sfx_ui_buttonclick);
  }
  return CONCAT31((int3)((uint)iVar1 >> 8),button->activated);
}



/* ui_text_input_update @ 0043ecf0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates a text input field: focus, input polling, sfx, and rendering */

int __cdecl ui_text_input_update(float *xy,int *input_state)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  longlong lVar6;
  undefined4 uVar7;
  undefined1 uVar8;
  float local_18;
  float local_14;
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = ui_focus_update((int)input_state);
  iVar4 = input_state[3];
  lVar6 = __ftol();
  iVar2 = ui_mouse_inside_rect(xy,0x12,(int)lVar6);
  if ((char)iVar2 != '\0') {
    ui_focus_set((int)input_state,'\0');
  }
  if ((char)iVar1 != '\0') {
    local_18 = *xy - 16.0;
    local_14 = xy[1];
    ui_focus_draw(&local_18);
  }
  *(undefined1 *)(*input_state + 1 + input_state[1]) = 0;
  iVar1 = console_input_poll();
  if (iVar1 == 0xd) {
    (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
    (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x9c);
    sfx_play(sfx_ui_typeenter);
  }
  else {
    (*grim_interface_ptr->vtable->grim_set_key_char_buffer)
              ((uchar *)*input_state,input_state + 1,input_state[2]);
    if (iVar1 != 0) {
      uVar3 = crt_rand();
      uVar3 = uVar3 & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      sfx_play(uVar3 + _sfx_ui_typeclick_01);
    }
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_draw_rect_outline)(xy,(float)iVar4,18.0);
  local_18 = *xy + 1.0;
  uVar7 = 0x41800000;
  local_14 = xy[1] + 1.0;
  fStack_10 = 0.0;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_18,(float)iVar4 - 2.0,16.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  iVar4 = 0;
  fStack_10 = (fStack_10 - 8.0) - 2.0;
  while( true ) {
    local_14 = (float)(*grim_interface_ptr->vtable->grim_measure_text_width)
                                ((char *)(*input_state + iVar4));
    uVar8 = (undefined1)((uint)uVar7 >> 0x18);
    if ((float)(int)local_14 <= fStack_10) break;
    iVar4 = iVar4 + 1;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.8);
  (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
            (grim_interface_ptr,*xy + 4.0,xy[1] + 2.0,&s_fmt_percent_s,*input_state + iVar4);
  fStack_10 = 1.0;
  fVar5 = (float10)fsin((float10)game_time_s * (float10)4.0);
  if ((float10)0.0 < fVar5) {
    fStack_10 = 0.4;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_10);
  uVar7 = (*grim_interface_ptr->vtable->grim_draw_rect_outline)((float *)&stack0xffffffd0,1.0,14.0);
  return CONCAT31((int3)((uint)uVar7 >> 8),uVar8);
}



/* ui_text_input_render @ 004413a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders a text input field (focus, text, and caret) */

void __cdecl ui_text_input_render(void *input_state,float y,float alpha)

{
  IGrim2D_vtbl *pIVar1;
  float fVar2;
  IGrim2D *self;
  int iVar3;
  char *pcVar4;
  char *text;
  IGrim2D_vtbl *pIVar5;
  longlong lVar6;
  int in_stack_00000010;
  float fVar7;
  float fVar8;
  float h;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fVar2 = alpha * 0.7;
  ui_text_alpha = 0x3f333333;
  ui_text_render_color_r = ui_text_color_rgba;
  ui_text_render_color_g = ui_text_color_g;
  ui_text_render_color_b = ui_text_color_b;
  ui_text_render_color_a = fVar2;
  iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)((char *)y);
  fStack_c = *(float *)((int)input_state + 4);
  fStack_10 = *(float *)input_state + 4.0;
  if (((game_state_id != 7) && (game_state_id != 8)) && (game_state_id != 0xc)) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,alpha);
    (*grim_interface_ptr->vtable->grim_draw_text_small)(fStack_10,fStack_c,(char *)y);
    (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&crt_sbh_header_pool);
    fStack_4 = fStack_c + 13.0;
    fStack_8 = fStack_10;
    (*grim_interface_ptr->vtable->grim_draw_rect_outline)(&fStack_8,(float)iVar3,1.0);
    if ((*(byte *)((int)y + 0x44) & 2) == 0) {
      if ((*(byte *)((int)y + 0x44) & 1) == 0) {
        (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,alpha * 0.8);
        pcVar4 = s_Local_score_00478974;
        pIVar5 = grim_interface_ptr->vtable;
      }
      else {
        (*grim_interface_ptr->vtable->grim_set_color)(0.7,1.0,0.7,alpha * 0.8);
        pcVar4 = s_Score_from_the_Internet_00478980;
        pIVar5 = grim_interface_ptr->vtable;
      }
      (*pIVar5->grim_draw_text_small_fmt)(grim_interface_ptr,fStack_10,fStack_c + 14.0,pcVar4);
    }
    else {
      (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,alpha * 0.8);
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,fStack_10,fStack_c + 14.0,
                 s_Internet_score_of_local_origin_004789a0);
      (*grim_interface_ptr->vtable->grim_set_color)(0.5,0.5,0.5,alpha * 0.5);
      (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
                (grim_interface_ptr,fStack_10 + 94.0,fStack_c - 12.0,s_uni__d_00478998);
      (*grim_interface_ptr->vtable->grim_set_color)(0.8,0.8,0.8,alpha * 0.8);
    }
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,alpha * 0.8);
    pIVar5 = grim_interface_ptr->vtable;
    pcVar4 = date_format_month_day((uint)*(byte *)((int)y + 0x40),(uint)*(byte *)((int)y + 0x42));
    fVar7 = fStack_c + 15.0 + 13.0;
    pIVar1 = grim_interface_ptr->vtable;
    text = date_format_month_day((uint)*(byte *)((int)y + 0x40),(uint)*(byte *)((int)y + 0x42));
    iVar3 = (*pIVar1->grim_measure_text_width)(text);
    (*pIVar5->grim_draw_text_small)
              ((((fStack_10 + 192.0) - 32.0) - 8.0) - (float)(iVar3 / 2),fVar7,pcVar4);
    fStack_10 = *(float *)input_state + 16.0;
    ui_stats_render_weapon_bar();
    fStack_c = fStack_c + 15.0 + 13.0 + 14.0;
  }
  fVar7 = alpha * 0.8;
  (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar7);
  pIVar5 = grim_interface_ptr->vtable;
  pcVar4 = s_Score_0047896c;
  fVar8 = fStack_c;
  iVar3 = (*pIVar5->grim_measure_text_width)(s_Score_0047896c);
  (*pIVar5->grim_draw_text_small)((fStack_10 + 32.0) - (float)(iVar3 / 2),fVar8,pcVar4);
  if (*(char *)((int)y + 0x28) == '\x02') {
    crt_sprintf(&ui_stats_text_buffer,s___2f_secs_00478960,(double)((float)*(int *)((int)y + 0x20) * 0.001))
    ;
  }
  else if (*(char *)((int)y + 0x28) == '\x03') {
    crt_sprintf(&ui_stats_text_buffer,s___2f_secs_00478960,(double)((float)*(int *)((int)y + 0x20) * 0.001))
    ;
  }
  else {
    crt_sprintf(&ui_stats_text_buffer,&s_int_format);
  }
  (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,1.0,alpha);
  iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)(&ui_stats_text_buffer);
  (*grim_interface_ptr->vtable->grim_draw_text_small)
            ((fStack_10 + 32.0) - (float)(iVar3 / 2),fStack_c + 15.0,&ui_stats_text_buffer);
  if (game_state_id != 0xc) {
    format_ordinal(in_stack_00000010);
    crt_sprintf(&ui_stats_text_buffer,s_Rank___s_00478954);
    iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)(&ui_stats_text_buffer);
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar7);
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              ((fStack_10 + 32.0) - (float)(iVar3 / 2),fStack_c + 30.0,&ui_stats_text_buffer);
  }
  fStack_10 = fStack_10 + 96.0;
  ui_stats_render_row();
  if (*(char *)((int)y + 0x28) == '\x03') {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fStack_10,fStack_c,s_Experience_00478948);
    crt_sprintf(&ui_stats_text_buffer,&s_int_format);
    iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)(&ui_stats_text_buffer);
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar7);
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              ((fStack_10 + 32.0) - (float)(iVar3 / 2),fStack_c + 15.0,&ui_stats_text_buffer);
    ui_stats_hover_time = ui_stats_hover_time - (frame_dt + frame_dt);
  }
  else {
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fStack_10 + 6.0,fStack_c,s_Game_time_0047893c);
    __ftol();
    __ftol();
    ui_draw_clock_gauge();
    if (((ui_mouse_x <= fStack_10 + 8.0) || (fStack_10 + 72.0 <= ui_mouse_x)) ||
       ((ui_mouse_y <= fStack_c + 16.0 || (fStack_c + 45.0 <= ui_mouse_y)))) {
      ui_stats_hover_time = ui_stats_hover_time - (frame_dt + frame_dt);
    }
    else {
      ui_stats_hover_time = frame_dt + frame_dt + ui_stats_hover_time;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar7);
    iVar3 = *(int *)((int)y + 0x20) / 1000;
    if (iVar3 % 0x3c < 10) {
      pcVar4 = s__d_0_d_00473150;
    }
    else {
      pcVar4 = s__d__d_00473148;
    }
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fStack_10 + 40.0,fStack_c + 19.0,pcVar4,iVar3 / 0x3c);
  }
  fStack_c = fStack_c + 52.0;
  fStack_10 = fStack_10 - 96.0;
  if (((ui_screen_phase == 2) && (game_state_id == 8)) ||
     (((game_state_id == 7 || ((game_state_id == 8 || (game_state_id == 0xc)))) &&
      (ui_screen_phase == 0)))) {
    ui_stats_hover_hit_ratio = 0.0;
  }
  else {
    ui_stats_render_weapon_bar();
    (*grim_interface_ptr->vtable->grim_bind_texture)(ui_weapon_icons_texture,0);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
    (*grim_interface_ptr->vtable->grim_set_sub_rect)
              (8,2,1,(&weapon_table)[*(byte *)((int)y + 0x2b)].hud_icon_id << 1);
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,alpha);
    h = 32.0;
    pIVar5 = grim_interface_ptr->vtable;
    fVar8 = 64.0;
    lVar6 = __ftol();
    fVar7 = (float)(int)lVar6;
    lVar6 = __ftol();
    fStack_c = (float)lVar6;
    (*pIVar5->grim_draw_quad)((float)(int)fStack_c,fVar7,fVar8,h);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    if ((((ui_mouse_x <= fStack_10) || (fStack_10 + 64.0 <= ui_mouse_x)) || (ui_mouse_y <= fStack_c)
        ) || (fStack_c + 32.0 <= ui_mouse_y)) {
      ui_stats_hover_weapon = ui_stats_hover_weapon - (frame_dt + frame_dt);
    }
    else {
      ui_stats_hover_weapon = frame_dt + frame_dt + ui_stats_hover_weapon;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar2);
    iVar3 = (*grim_interface_ptr->vtable->grim_measure_text_width)
                      ((&weapon_table)[*(byte *)((int)y + 0x2b)].name);
    fVar7 = (float)(0x20 - iVar3 / 2);
    if (fVar7 < 0.0) {
      fVar7 = 0.0;
    }
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (fVar7 + fStack_10,fStack_c + 32.0,(&weapon_table)[*(byte *)((int)y + 0x2b)].name);
    (*grim_interface_ptr->vtable->grim_draw_text_small_fmt)
              (grim_interface_ptr,fStack_10 + 110.0,fStack_c + 1.0,s_Frags___d_00478930);
    self = grim_interface_ptr;
    pIVar5 = grim_interface_ptr->vtable;
    __ftol();
    (*pIVar5->grim_draw_text_small_fmt)
              (self,fStack_10 + 110.0,(fStack_c + 16.0) - 1.0,s_Hit______d___00478920);
    if (((ui_mouse_x <= fStack_10 + 110.0) || (fStack_10 + 174.0 <= ui_mouse_x)) ||
       ((ui_mouse_y <= (fStack_c + 16.0) - 1.0 || (fStack_c + 32.0 <= ui_mouse_y)))) {
      ui_stats_hover_hit_ratio = ui_stats_hover_hit_ratio - (frame_dt + frame_dt);
    }
    else {
      ui_stats_hover_hit_ratio = frame_dt + frame_dt + ui_stats_hover_hit_ratio;
    }
    fStack_c = fStack_c + 48.0;
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,alpha);
  ui_stats_render_weapon_bar();
  if (ui_stats_hover_weapon <= 1.0) {
    if (ui_stats_hover_weapon < 0.0) {
      ui_stats_hover_weapon = 0.0;
    }
  }
  else {
    ui_stats_hover_weapon = 1.0;
  }
  if (ui_stats_hover_time <= 1.0) {
    if (ui_stats_hover_time < 0.0) {
      ui_stats_hover_time = 0.0;
    }
  }
  else {
    ui_stats_hover_time = 1.0;
  }
  if (ui_stats_hover_hit_ratio <= 1.0) {
    if (ui_stats_hover_hit_ratio < 0.0) {
      ui_stats_hover_hit_ratio = 0.0;
    }
  }
  else {
    ui_stats_hover_hit_ratio = 1.0;
  }
  if (((game_state_id == 7) || (game_state_id == 8)) || (game_state_id == 0xc)) {
    (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar2);
    if (0.5 < ui_stats_hover_weapon) {
      fVar2 = (ui_stats_hover_weapon - 0.5) * alpha;
      (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar2 + fVar2);
      (*grim_interface_ptr->vtable->grim_draw_text_small)
                (fStack_10 - 20.0,fStack_c,s_most_used_weapon);
    }
    if (0.5 < ui_stats_hover_time) {
      fVar2 = (ui_stats_hover_time - 0.5) * alpha;
      (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar2 + fVar2);
      (*grim_interface_ptr->vtable->grim_draw_text_small)
                (fStack_10 + 12.0,fStack_c,s_time_game_lasted);
    }
    if (0.5 < ui_stats_hover_hit_ratio) {
      fVar2 = (ui_stats_hover_hit_ratio - 0.5) * alpha;
      (*grim_interface_ptr->vtable->grim_set_color)(0.9,0.9,0.9,fVar2 + fVar2);
      (*grim_interface_ptr->vtable->grim_draw_text_small)
                (fStack_10 - 22.0,fStack_c,s_shot_bullets_hit);
    }
  }
  return;
}



/* ui_element_update @ 00446900 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates hover/click/animation for a UI element and fires callbacks */

void __cdecl ui_element_update(ui_element_t *element)

{
  uchar uVar1;
  ui_element_t *puVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  ui_element_t *puVar6;
  int iVar7;
  int iVar8;
  ui_element_t **ppuVar9;
  float10 fVar10;
  float10 fVar11;
  
  puVar6 = element;
  if ((element->_pad0[0] == '\0') && (element->active != '\0')) {
    if (((ui_mouse_x <= *(float *)element->_pad1) ||
        (((ui_mouse_y <= *(float *)(element->_pad1 + 4) ||
          (*(float *)(element->_pad1 + 8) <= ui_mouse_x)) ||
         (*(float *)(element->_pad1 + 0xc) <= ui_mouse_y)))) ||
       ((ui_mouse_blocked != '\0' || (ui_tab_key_disabled != '\0')))) {
      element->_pad5[0xec] = '\0';
    }
    else {
      uVar1 = element->enabled;
      element->_pad5[0xec] = '\x01';
      if ((uVar1 != '\0') && (element->on_activate != (_func_1 *)0x0)) {
        _DAT_0048723c = element;
        ui_state_phase = 0;
        ppuVar9 = &ui_element_table_end;
        do {
          puVar2 = *ppuVar9;
          if ((puVar2->enabled != '\0') &&
             ((game_state_id != 0 || (puVar2->on_activate != (_func_1 *)0x0)))) {
            if (element == puVar2) break;
            ui_state_phase = ui_state_phase + 1;
          }
          ppuVar9 = ppuVar9 + 1;
        } while ((int)ppuVar9 < 0x48f20c);
      }
    }
    element->counter_timer = element->counter_timer + frame_dt_ms;
    uVar1 = element->_pad5[0xec];
    if (uVar1 == '\0') {
      element->counter_value = element->counter_value + frame_dt_ms * -2;
    }
    else {
      element->counter_value = element->counter_value + frame_dt_ms * 6;
    }
    if (element->counter_value < 0) {
      element->counter_value = 0;
    }
    if (1000 < element->counter_value) {
      element->counter_value = 1000;
    }
    if ((((element->on_activate != (_func_1 *)0x0) && (0xfe < element->counter_timer)) &&
        (uVar1 != '\0')) && (iVar7 = input_primary_just_pressed(), (char)iVar7 != '\0')) {
      sfx_play(sfx_ui_buttonclick);
      (*element->on_activate)();
    }
    iVar7 = *(int *)(element->_pad0 + 0xe);
    if (ui_elements_timeline < iVar7) {
      iVar3 = *(int *)(element->_pad0 + 0x12);
      if (ui_elements_timeline < iVar3) {
        uVar1 = element[1].active;
        element = (ui_element_t *)0x3fc90fdb;
        fVar4 = puVar6->quad0[0] - puVar6->quad0[7];
        puVar6->_pad0[10] = '\0';
        puVar6->_pad0[0xb] = '\0';
        puVar6->_pad0[0xc] = '\0';
        puVar6->_pad0[0xd] = '\0';
        if (uVar1 == '\0') {
          *(float *)(puVar6->_pad0 + 6) = -ABS(fVar4);
        }
        else {
          *(float *)(puVar6->_pad0 + 6) = ABS(fVar4);
        }
      }
      else {
        iVar8 = ui_elements_timeline - iVar3;
        puVar6->_pad0[10] = '\0';
        puVar6->_pad0[0xb] = '\0';
        puVar6->_pad0[0xc] = '\0';
        puVar6->_pad0[0xd] = '\0';
        fVar5 = (float)(iVar7 - iVar3);
        puVar2 = (ui_element_t *)(1.5707964 - ((float)iVar8 * 1.5707964) / fVar5);
        fVar4 = element->quad0[0] - element->quad0[7];
        if (element[1].active == '\0') {
          *(float *)(element->_pad0 + 6) =
               -((1.0 - ((float)ui_elements_timeline - (float)iVar3) / fVar5) * ABS(fVar4));
          element = puVar2;
        }
        else {
          *(float *)(element->_pad0 + 6) =
               (1.0 - ((float)ui_elements_timeline - (float)iVar3) / fVar5) * ABS(fVar4);
          element = puVar2;
        }
      }
    }
    else {
      if (element->enabled == '\0') {
        sfx_play(sfx_ui_panelclick);
        element->enabled = '\x01';
      }
      if (element->counter_timer < 0x100) {
        element->counter_timer = element->counter_timer + frame_dt_ms;
      }
      puVar6->_pad0[6] = '\0';
      puVar6->_pad0[7] = '\0';
      puVar6->_pad0[8] = '\0';
      puVar6->_pad0[9] = '\0';
      element = (ui_element_t *)0x0;
      puVar6->_pad0[10] = '\0';
      puVar6->_pad0[0xb] = '\0';
      puVar6->_pad0[0xc] = '\0';
      puVar6->_pad0[0xd] = '\0';
    }
    iVar7 = ui_get_element_index(puVar6);
    if (iVar7 == 0) {
      element = (ui_element_t *)-ABS((float)element);
    }
    if ((ui_elements_timeline < *(int *)(puVar6->_pad0 + 0xe)) && (puVar6->enabled != '\0')) {
      puVar6->enabled = '\0';
    }
    fVar10 = (float10)fcos((float10)(float)element);
    puVar6->rot_m00 = (float)fVar10;
    fVar11 = (float10)fsin((float10)(float)element);
    puVar6->rot_m01 = (float)-fVar11;
    puVar6->rot_m10 = (float)fVar11;
    puVar6->rot_m11 = (float)fVar10;
  }
  return;
}



/* ui_element_render @ 00446c40 */

/* updates focus/click handling and renders a UI element */

void __cdecl ui_element_render(ui_element_t *element)

{
  float *pfVar1;
  float *matrix;
  int iVar2;
  int iVar3;
  uchar *puVar4;
  char cVar5;
  float fStack_5c;
  float fStack_58;
  
  cVar5 = '\0';
  if (element->active == '\0') {
    return;
  }
  if ((element->render_scale == 0.0) && (*(float *)((int)cv_uiPointFilterPanels + 0xc) != 0.0)) {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,1);
  }
  if ((element->on_activate != (_func_1 *)0x0) && (element != (ui_element_t *)&ui_element_back_button)) {
    iVar3 = ui_focus_update((int)element);
    cVar5 = (char)iVar3;
    if (((cVar5 != '\0') &&
        (((iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c), (char)iVar3 != '\0' &&
          (console_open_flag == '\0')) && (element->enabled != '\0')))) &&
       (element->on_activate != (_func_1 *)0x0)) {
      (*element->on_activate)();
    }
  }
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
  if (element->counter_id != -1) {
    if ((cVar5 != '\0') && (0 < ui_focus_timer_ms)) {
      element->counter_value = ui_focus_timer_ms;
    }
    if (element->on_activate == (_func_1 *)0x0) {
      puVar4 = element->_pad4 + 0x13;
      iVar3 = 4;
      do {
        *puVar4 = 200;
        puVar4 = puVar4 + 0x1c;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    else {
      iVar3 = 4;
      puVar4 = element->_pad4 + 0x13;
      do {
        iVar2 = element->counter_value * 0x9b;
        iVar3 = iVar3 + -1;
        *puVar4 = (((char)(iVar2 / 1000) + (char)(iVar2 >> 0x1f)) -
                  (char)((longlong)iVar2 * 0x10624dd3 >> 0x3f)) + 'd';
        puVar4 = puVar4 + 0x1c;
      } while (iVar3 != 0);
    }
  }
  fStack_58 = 6.28412e-39;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  if (element->texture_handle != -1) {
    (*grim_interface_ptr->vtable->grim_bind_texture)(element->texture_handle,0);
    if (*(int *)(element->_pad0 + 2) == 0) {
      if (config_blob.reserved0[0xe] != '\0') {
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        pfVar1 = &element->rot_m00;
        (*grim_interface_ptr->vtable->grim_submit_vertices_transform_color)
                  (element->quad0,4,(float *)&stack0xffffff90,pfVar1,(float *)&stack0xffffffb4);
        if (element->quad_mode == 8) {
          (*grim_interface_ptr->vtable->grim_submit_vertices_transform_color)
                    (element->quad1,4,(float *)&stack0xffffff90,pfVar1,(float *)&stack0xffffffb4);
          (*grim_interface_ptr->vtable->grim_submit_vertices_transform_color)
                    (element->quad2,4,(float *)&stack0xffffff90,pfVar1,(float *)&stack0xffffffb4);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
      }
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      matrix = &element->rot_m00;
      pfVar1 = &element->pos_x;
      (*grim_interface_ptr->vtable->grim_submit_vertices_transform)(element->quad0,4,pfVar1,matrix);
      if (element->quad_mode == 8) {
        (*grim_interface_ptr->vtable->grim_submit_vertices_transform)
                  (element->quad1,4,pfVar1,matrix);
        (*grim_interface_ptr->vtable->grim_submit_vertices_transform)
                  (element->quad2,4,pfVar1,matrix);
      }
    }
    else {
      if (*(int *)(element->_pad0 + 2) != 1) goto LAB_00447154;
      if (config_blob.reserved0[0xe] != '\0') {
        (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
        (*grim_interface_ptr->vtable->grim_begin_batch)();
        (*grim_interface_ptr->vtable->grim_submit_vertices_offset_color)
                  (element->quad0,4,(float *)&stack0xffffff90,(float *)&stack0xffffffb4);
        if (element->quad_mode == 8) {
          (*grim_interface_ptr->vtable->grim_submit_vertices_offset_color)
                    (element->quad1,4,(float *)&stack0xffffff90,(float *)&stack0xffffffb4);
          (*grim_interface_ptr->vtable->grim_submit_vertices_offset_color)
                    (element->quad2,4,(float *)&stack0xffffff90,(float *)&stack0xffffffb4);
        }
        (*grim_interface_ptr->vtable->grim_end_batch)();
      }
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      (*grim_interface_ptr->vtable->grim_submit_vertices_offset)
                (element->quad0,4,(float *)&stack0xffffff90);
      if (element->quad_mode == 8) {
        (*grim_interface_ptr->vtable->grim_submit_vertices_offset)
                  (element->quad1,4,(float *)&stack0xffffff90);
        (*grim_interface_ptr->vtable->grim_submit_vertices_offset)
                  (element->quad2,4,(float *)&stack0xffffff90);
      }
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
LAB_00447154:
  if (element->counter_id != -1) {
    (*grim_interface_ptr->vtable->grim_bind_texture)(element->counter_id,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    if (*(int *)(element->_pad0 + 2) == 0) {
      (*grim_interface_ptr->vtable->grim_submit_vertices_transform)
                ((float *)element->_pad4,4,&element->pos_x,&element->rot_m00);
    }
    else {
      fStack_5c = *(float *)(element->_pad0 + 6) + element->pos_x;
      fStack_58 = *(float *)(element->_pad0 + 10) + element->pos_y;
      (*grim_interface_ptr->vtable->grim_submit_vertices_offset)
                ((float *)element->_pad4,4,&fStack_5c);
    }
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
  if ((-1 < element->counter_timer) && (element->counter_timer < 0x100)) {
    iVar3 = 4;
    puVar4 = element->_pad5 + 0x17;
    do {
      puVar4[-0xe8] = 0xff - (char)(element->counter_timer / 2);
      iVar3 = iVar3 + -1;
      *puVar4 = 0xff - (char)(element->counter_timer / 2);
      puVar4 = puVar4 + 0x1c;
    } while (iVar3 != 0);
  }
  if (((element->enabled != '\0') && (element->counter_id != -1)) &&
     (element->on_activate != (_func_1 *)0x0)) {
    (*grim_interface_ptr->vtable->grim_bind_texture)(element->counter_id,0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    (*grim_interface_ptr->vtable->grim_submit_vertices_transform)
              ((float *)element->_pad4,4,&element->pos_x,(float *)&stack0xffffff8c);
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  if (*(code **)element->_pad2 != (code *)0x0) {
    (**(code **)element->_pad2)();
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  return;
}



/* ui_menu_main_click_options @ 00447370 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* main menu OPTIONS click callback (sets ui_transition_direction=0 and game_state_pending=2) */

void ui_menu_main_click_options(void)

{
  ui_transition_direction = 0;
  game_state_pending = 2;
  return;
}



/* ui_menu_main_click_credits @ 004473e0 */

/* [binja] int32_t sub_4473e0() */

int ui_menu_main_click_credits(void)

{
  int in_EAX;
  
  ui_transition_direction = 0;
  game_state_pending = 3;
  return in_EAX;
}



/* ui_menu_main_click_play_game @ 00447400 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* main menu PLAY GAME click callback (sets ui_transition_direction=0 and game_state_pending=1) */

void ui_menu_main_click_play_game(void)

{
  ui_transition_direction = 0;
  game_state_pending = 1;
  return;
}



/* ui_menu_main_click_quit @ 00447420 */

/* [binja] int32_t sub_447420() */

int ui_menu_main_click_quit(void)

{
  undefined4 in_EAX;
  
  ui_transition_direction = 0;
  if (ui_splash_skip_flag != '\0') {
    game_state_pending = 5;
    return CONCAT31((int3)((uint)in_EAX >> 8),ui_splash_skip_flag);
  }
  game_state_pending = -(uint)(render_pass_mode != '\0') & 5;
  return game_state_pending;
}



/* ui_menu_main_click_quit @ 00447450 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* main menu QUIT click callback (clears ui_sign_crimson_update_disabled, sets
   ui_transition_direction=0, game_state_pending=10, mutes music) */

void ui_menu_main_click_quit(void)

{
  game_state_pending = 10;
  ui_sign_crimson_update_disabled = 0;
  ui_transition_direction = 0;
  sfx_mute_all(music_track_crimson_theme_id);
  sfx_mute_all(music_track_extra_0);
  sfx_mute_all(music_track_shortie_monk_id);
  return;
}



/* ui_element_init_defaults @ 0044faa0 */

/* [binja] char* sub_44faa0(char* arg1) */

char * __cdecl ui_element_init_defaults(char *arg1)

{
  char cVar1;
  undefined3 extraout_var;
  
  if (arg1 == (char *)0x0) {
    cVar1 = console_printf(&console_log_queue,s_elem_null_error);
    return (char *)CONCAT31(extraout_var,cVar1);
  }
  arg1[0x11c] = -1;
  arg1[0x11d] = -1;
  arg1[0x11e] = -1;
  arg1[0x11f] = -1;
  arg1[0x204] = -1;
  arg1[0x205] = -1;
  arg1[0x206] = -1;
  arg1[0x207] = -1;
  arg1[0x2ec] = -1;
  arg1[0x2ed] = -1;
  arg1[0x2ee] = -1;
  arg1[0x2ef] = -1;
  arg1[0x20] = '\0';
  arg1[0x21] = '\0';
  arg1[0x22] = 'i';
  arg1[0x23] = 'C';
  arg1[0x24] = '\0';
  arg1[0x25] = '\0';
  arg1[0x26] = -0x20;
  arg1[0x27] = 'A';
  arg1[0x28] = '\0';
  arg1[0x29] = -0x80;
  arg1[0x2a] = -0x29;
  arg1[0x2b] = 'C';
  arg1[0x2fc] = '\0';
  arg1[0x2fd] = '\x01';
  arg1[0x2fe] = '\0';
  arg1[0x2ff] = '\0';
  arg1[0x34] = '\0';
  arg1[0x35] = '\0';
  arg1[0x36] = '\0';
  arg1[0x37] = '\0';
  arg1[0x38] = '\0';
  arg1[0x39] = '\0';
  arg1[0x3a] = '\0';
  arg1[0x3b] = '\0';
  arg1[0x2c] = '\0';
  arg1[0x2d] = '\0';
  arg1[0x2e] = -0x78;
  arg1[0x2f] = 'B';
  arg1[0x300] = '\0';
  arg1[0x301] = '\0';
  arg1[0x302] = '\0';
  arg1[0x303] = '\0';
  *arg1 = '\0';
  arg1[0x30] = '9';
  arg1[0x31] = '\0';
  arg1[0x32] = '\0';
  arg1[0x33] = '\0';
  arg1[0x2f4] = '\0';
  arg1[0x10] = ',';
  arg1[0x11] = '\x01';
  arg1[0x12] = '\0';
  arg1[0x13] = '\0';
  arg1[0x14] = '\0';
  arg1[0x15] = '\0';
  arg1[0x16] = '\0';
  arg1[0x17] = '\0';
  arg1[2] = '\0';
  arg1[4] = '\0';
  arg1[5] = '\0';
  arg1[6] = '\0';
  arg1[7] = '\0';
  return arg1;
}



/* ui_element_layout_calc @ 0044fb50 */

/* [binja] float sub_44fb50(float arg1) */

float __cdecl ui_element_layout_calc(float arg1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 in_ST0;
  
  if (((undefined *)arg1 != &menu_screen_game_over) && ((undefined *)arg1 != &ui_menu_game_over_flag)) {
    *(float *)((int)arg1 + 0x20) =
         *(float *)((int)arg1 + 0x3c) + *(float *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x20);
    *(float *)((int)arg1 + 0x24) =
         *(float *)((int)arg1 + 0x40) + *(float *)((int)arg1 + 0x1c) + *(float *)((int)arg1 + 0x24);
    *(float *)((int)arg1 + 0x28) =
         *(float *)((int)arg1 + 0x3c) + *(float *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x28);
    *(float *)((int)arg1 + 0x2c) =
         *(float *)((int)arg1 + 0x40) + *(float *)((int)arg1 + 0x1c) + *(float *)((int)arg1 + 0x2c);
    *(float *)((int)arg1 + 0x20) = *(float *)((int)arg1 + 0x3c) + *(float *)((int)arg1 + 0x18);
    fVar2 = *(float *)((int)arg1 + 0x74) - *(float *)((int)arg1 + 0x3c);
    *(float *)((int)arg1 + 0x24) = *(float *)((int)arg1 + 0x40) + *(float *)((int)arg1 + 0x1c);
    *(float *)((int)arg1 + 0x20) = fVar2 * 0.54 + *(float *)((int)arg1 + 0x20);
    fVar3 = *(float *)((int)arg1 + 0x78) - *(float *)((int)arg1 + 0x40);
    *(float *)((int)arg1 + 0x24) = fVar3 * 0.28 + *(float *)((int)arg1 + 0x24);
    *(float *)((int)arg1 + 0x28) = *(float *)((int)arg1 + 0x74) + *(float *)((int)arg1 + 0x18);
    *(float *)((int)arg1 + 0x2c) = *(float *)((int)arg1 + 0x78) + *(float *)((int)arg1 + 0x1c);
    *(float *)((int)arg1 + 0x28) = *(float *)((int)arg1 + 0x28) - fVar2 * 0.05;
    *(float *)((int)arg1 + 0x2c) = *(float *)((int)arg1 + 0x2c) - fVar3 * 0.1;
    if ((*(char *)((int)arg1 + 0x314) != '\0') && (iVar5 = 0, 0 < *(int *)((int)arg1 + 0x120))) {
      puVar4 = (undefined4 *)((int)arg1 + 0x6c);
      do {
        uVar1 = puVar4[-7];
        iVar5 = iVar5 + 2;
        puVar4[-7] = *puVar4;
        *puVar4 = uVar1;
        puVar4 = puVar4 + 0xe;
      } while (iVar5 < *(int *)((int)arg1 + 0x120));
    }
  }
  return (float)in_ST0;
}



/* ui_menu_layout_init @ 0044fcb0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* initializes menu UI element layout and text textures */

void ui_menu_layout_init(void)

{
  char *pcVar1;
  int iVar2;
  ui_element_t *puVar3;
  int *piVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  char *unaff_EBX;
  ui_element_t **ppuVar10;
  uchar *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  char *pcVar14;
  int iVar15;
  float fStack_30;
  float fStack_2c;
  float afStack_28 [2];
  uint local_20 [8];
  
  screen_fade_alpha = 0;
  _DAT_00487288 = (float)config_blob.screen_width * 0.0015625;
  _DAT_0048723c = 0;
  screen_fade_in_flag = 0;
  _DAT_0048728c = (float)config_blob.screen_height * 0.0020833334;
  ppuVar10 = &ui_element_table_end;
  for (iVar7 = 0x29; iVar7 != 0; iVar7 = iVar7 + -1) {
    *ppuVar10 = (ui_element_t *)0x0;
    ppuVar10 = ppuVar10 + 1;
  }
  ui_element_table_end = (ui_element_t *)&ui_sign_crimson;
  ui_element_ptr_table = &DAT_004875a8;
  ui_element_ptr_1 = &ui_button_visible_flag;
  _DAT_0048f174 = &ui_elem_flag_a;
  _DAT_0048f178 = &ui_elem_flag_b;
  _DAT_0048f17c = &ui_elem_flag_c;
  pcVar1 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_20,100);
  if (*pcVar1 == '\0') {
    _DAT_0048f184 = &ui_elem_flag_d;
    _DAT_0048f180 = &ui_main_menu_initialized;
  }
  else {
    _DAT_0048f180 = &ui_elem_flag_d;
    _DAT_0048f184 = &ui_main_menu_initialized;
  }
  ui_menu_layout_extras_ptr = &menu_screen_extras;
  ui_menu_layout_c = &menu_screen_credits;
  _DAT_0048f190 = &DAT_00489180;
  ui_menu_layout_options_ptr = &menu_screen_options;
  ui_menu_layout_a = &menu_screen_main;
  _DAT_0048f1a4 = &DAT_0048a410;
  _DAT_0048f1a8 = &DAT_0048a728;
  _DAT_0048f1ac = &DAT_0048aa40;
  _DAT_0048f1b4 = &DAT_0048ad58;
  _DAT_0048f1b8 = &DAT_0048b070;
  _DAT_0048f1bc = &DAT_0048b388;
  ui_menu_element_ptr_table = &DAT_0048b6a0;
  DAT_0048f1c4 = &ui_menu_options_flags_a;
  _DAT_0048f1c8 = &ui_menu_options_flags_b;
  _DAT_0048f1cc = &ui_menu_options_flags_c;
  ui_menu_layout_gameover_ptr = &menu_screen_game_over;
  _DAT_0048f1d4 = &ui_menu_game_over_flag;
  _DAT_0048f1d8 = &ui_gameplay_menu_initialized;
  _DAT_0048f1dc = &DAT_0048c930;
  _DAT_0048f1e0 = &ui_menu_ingame_flag;
  _DAT_0048f19c = &DAT_0048cf60;
  ui_menu_layout_quest_ptr = &menu_screen_quest;
  ui_menu_layout_b = &menu_screen_survival;
  _DAT_0048f188 = &DAT_00489ac8;
  _DAT_0048f18c = &ui_credits_active_flag;
  _DAT_0048f1ec = &crt_file_lock_table;
  _DAT_0048f1f0 = &DAT_0048d8a8;
  _DAT_0048f1f4 = &ui_menu_highscore_active;
  _DAT_0048f1f8 = &DAT_0048ded8;
  _DAT_0048f1fc = &ui_menu_active_flag_b;
  _DAT_0048f200 = &DAT_0048e508;
  ui_menu_layout_highscore_ptr = &menu_screen_highscore;
  ui_element_table_start = (ui_element_t *)&ui_credits_element_start;
  ppuVar10 = &ui_element_table_end;
  do {
    ui_element_init_defaults((char *)*ppuVar10);
    iVar7 = config_blob.screen_width;
    ppuVar10 = ppuVar10 + 1;
  } while ((int)ppuVar10 < 0x48f20c);
  puVar12 = &crt_file_buffer_pool;
  puVar13 = &DAT_004872cc;
  for (iVar8 = 0x3a; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  _DAT_004872a8 = (float)(iVar7 + 4);
  _DAT_004872ac = 0x428c0000;
  if (iVar7 < 0x281) {
    _DAT_004872ac = 0x42700000;
  }
  pcVar14 = s_ui_ui_itemTexts_jaz_00479318;
  ui_button_texture_id = texture_get_or_load_alt(s_ui_ui_itemTexts_jaz_00479318,unaff_EBX);
  pcVar1 = s_ui_ui_textReaper_jaz_00479300;
  crt_lowio_handles = texture_get_or_load_alt(s_ui_ui_textReaper_jaz_00479300,pcVar14);
  pcVar14 = s_ui_ui_textControls_jaz_004792e8;
  tex_controls_text = texture_get_or_load_alt(s_ui_ui_textControls_jaz_004792e8,pcVar1);
  pcVar1 = s_ui_ui_textPickAPerk_jaz_004792d0;
  texture_perk_frame_id = texture_get_or_load_alt(s_ui_ui_textPickAPerk_jaz_004792d0,pcVar14);
  texture_quest_panel_id = texture_get_or_load_alt(s_ui_ui_textWellDone_jaz_004792b8,pcVar1);
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_00488244;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  DAT_00488220 = 0xc2700000;
  DAT_00488224 = 0x43520000;
  afStack_28[0] = 270.0;
  afStack_28[1] = -38.0;
  ui_element_set_rect((ui_element_t *)&DAT_0048832c,124.0,30.0,afStack_28);
  _DAT_00488238 = 0x30;
  main_menu_version_callback = &LAB_0044fc70;
  iVar7 = game_is_full_version();
  if ((char)iVar7 != '\0') {
    main_menu_version_callback = &LAB_00447350;
  }
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_004878fc;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_004878d8 = 0xc2700000;
  _DAT_004878dc = 0x43870000;
  afStack_28[0] = 270.0;
  afStack_28[1] = -38.0;
  ui_element_set_rect((ui_element_t *)&DAT_004879e4,124.0,30.0,afStack_28);
  _DAT_004878f4 = ui_menu_main_click_play_game;
  _DAT_004878f0 = 0x19;
  afStack_28[0] = 270.0;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_00487c14;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_00487bf0 = 0xc2700000;
  _DAT_00487bf4 = 0x43a50000;
  afStack_28[1] = -38.0;
  ui_element_set_rect((ui_element_t *)&ui_element_controls_rect,124.0,30.0,afStack_28);
  _DAT_00487c0c = ui_menu_main_click_options;
  _DAT_00487c08 = 0x18;
  afStack_28[0] = 270.0;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_00487f2c;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_00487f08 = 0xc2700000;
  _DAT_00487f0c = 0x43c30000;
  afStack_28[1] = -38.0;
  ui_element_set_rect((ui_element_t *)&DAT_00488014,124.0,30.0,afStack_28);
  _DAT_00487f24 = &LAB_00447390;
  _DAT_00487f20 = 0x1f;
  iVar7 = 5;
  pcVar1 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)((uint *)afStack_28,100);
  if (*pcVar1 != '\0') {
    puVar3 = &ui_menu_item_element;
    puVar12 = &DAT_0048855c;
    for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar12 = *(undefined4 *)puVar3;
      puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
      puVar12 = puVar12 + 1;
    }
    _DAT_00488538 = 0xc2700000;
    _DAT_0048853c = 0x43e10000;
    fStack_30 = 270.0;
    fStack_2c = -38.0;
    ui_element_set_rect((ui_element_t *)&DAT_00488644,124.0,30.0,&fStack_30);
    _DAT_00488550 = 0x30;
    _DAT_00488554 = &LAB_0044fca0;
    iVar7 = 6;
  }
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_00488874;
  for (iVar8 = 0x3a; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  fStack_30 = 270.0;
  ui_quit_button_x = 0xc2700000;
  ui_quit_button_y = (float)(iVar7 * 0x3c + 0x96);
  fStack_2c = -38.0;
  ui_element_set_rect((ui_element_t *)&ui_quit_button_element,124.0,30.0,&fStack_30);
  ui_quit_button_callback = ui_menu_main_click_quit;
  ui_quit_button_flags = 0x10;
  iVar8 = 2;
  iVar7 = 0;
  do {
    iVar15 = iVar7;
    if ((iVar8 == 2) && (iVar2 = game_is_full_version(), (char)iVar2 != '\0')) {
      iVar7 = 4;
      iVar15 = 4;
    }
    pcVar1 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(local_20,100);
    if (*pcVar1 == '\0') {
      if (iVar8 == 6) {
        iVar7 = 6;
        iVar15 = 6;
      }
      (&ui_element_table_end)[iVar8]->counter_id = ui_button_texture_id;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x14] = '\0';
      puVar3->_pad4[0x15] = '\0';
      puVar3->_pad4[0x16] = '\0';
      puVar3->_pad4[0x17] = '\0';
      *(float *)(puVar3->_pad4 + 0x18) = (float)iVar15 * 0.125;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x30] = '\0';
      puVar3->_pad4[0x31] = '\0';
      puVar3->_pad4[0x32] = 0x80;
      puVar3->_pad4[0x33] = '?';
      *(float *)(puVar3->_pad4 + 0x34) = (float)iVar15 * 0.125;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x4c] = '\0';
      puVar3->_pad4[0x4d] = '\0';
      puVar3->_pad4[0x4e] = 0x80;
      puVar3->_pad4[0x4f] = '?';
      fVar9 = (float)(iVar7 + 1) * 0.125;
      *(float *)(puVar3->_pad4 + 0x50) = fVar9;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x68] = '\0';
      puVar3->_pad4[0x69] = '\0';
      puVar3->_pad4[0x6a] = '\0';
      puVar3->_pad4[0x6b] = '\0';
    }
    else {
      (&ui_element_table_end)[iVar8]->counter_id = ui_button_texture_id;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x14] = '\0';
      puVar3->_pad4[0x15] = '\0';
      puVar3->_pad4[0x16] = '\0';
      puVar3->_pad4[0x17] = '\0';
      fStack_30 = 0.0;
      *(float *)(puVar3->_pad4 + 0x18) = (float)iVar15 * 0.125;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x30] = '\0';
      puVar3->_pad4[0x31] = '\0';
      puVar3->_pad4[0x32] = 0x80;
      puVar3->_pad4[0x33] = '?';
      *(float *)(puVar3->_pad4 + 0x34) = (float)iVar15 * 0.125;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x4c] = '\0';
      puVar3->_pad4[0x4d] = '\0';
      puVar3->_pad4[0x4e] = 0x80;
      puVar3->_pad4[0x4f] = '?';
      fVar9 = (float)(iVar7 + 1) * 0.125;
      *(float *)(puVar3->_pad4 + 0x50) = fVar9;
      puVar3 = (&ui_element_table_end)[iVar8];
      puVar3->_pad4[0x68] = '\0';
      puVar3->_pad4[0x69] = '\0';
      puVar3->_pad4[0x6a] = '\0';
      puVar3->_pad4[0x6b] = '\0';
      fStack_2c = fVar9;
    }
    *(float *)(puVar3->_pad4 + 0x6c) = fVar9;
    if ((iVar8 == 2) && (iVar15 = game_is_full_version(), (char)iVar15 != '\0')) {
      iVar7 = 0;
    }
    iVar15 = iVar7 + 1;
    if (iVar15 == 4) {
      iVar15 = iVar7 + 2;
    }
    iVar8 = iVar8 + 1;
    iVar7 = iVar15;
  } while (iVar8 < 8);
  if (config_blob.screen_width < 0x281) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)((int)ui_element_table_end->quad0 + iVar7);
      *pfVar6 = *(float *)((int)ui_element_table_end->quad0 + iVar7) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      puVar11 = ui_element_table_end->_pad5 + iVar7 + 4;
      *(float *)puVar11 = *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) * 0.8;
      *(float *)(puVar11 + 4) = *(float *)(puVar11 + 4) * 0.8;
      puVar11 = ui_element_table_end->_pad4 + iVar7;
      iVar8 = iVar7 + 0x1c;
      *(float *)puVar11 = *(float *)(ui_element_table_end->_pad4 + iVar7) * 0.8;
      *(float *)(puVar11 + 4) = *(float *)(puVar11 + 4) * 0.8;
      *(float *)((int)ui_element_table_end->quad0 + iVar7) =
           *(float *)((int)ui_element_table_end->quad0 + iVar7) + 10.0;
      *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) =
           *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) + 10.0;
      *(float *)(ui_element_table_end->_pad4 + iVar7) =
           *(float *)(ui_element_table_end->_pad4 + iVar7) + 10.0;
      *(float *)(ui_element_ptr_table + iVar7 + 0x40) = *(float *)(ui_element_ptr_table + iVar7 + 0x40) - 14.0;
      *(float *)(ui_element_ptr_table + iVar7 + 0x210) = *(float *)(ui_element_ptr_table + iVar7 + 0x210) - 14.0;
      *(float *)(ui_element_ptr_table + iVar7 + 0x128) = *(float *)(ui_element_ptr_table + iVar7 + 0x128) - 14.0;
      iVar7 = iVar8;
    } while (iVar8 < 0x70);
  }
  else if ((800 < config_blob.screen_width) && (config_blob.screen_width < 0x401)) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)((int)ui_element_table_end->quad0 + iVar7);
      *pfVar6 = *(float *)((int)ui_element_table_end->quad0 + iVar7) * 1.2;
      pfVar6[1] = pfVar6[1] * 1.2;
      puVar11 = ui_element_table_end->_pad5 + iVar7 + 4;
      *(float *)puVar11 = *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) * 1.2;
      *(float *)(puVar11 + 4) = *(float *)(puVar11 + 4) * 1.2;
      puVar11 = ui_element_table_end->_pad4 + iVar7;
      iVar8 = iVar7 + 0x1c;
      *(float *)puVar11 = *(float *)(ui_element_table_end->_pad4 + iVar7) * 1.2;
      *(float *)(puVar11 + 4) = *(float *)(puVar11 + 4) * 1.2;
      *(float *)((int)ui_element_table_end->quad0 + iVar7) =
           *(float *)((int)ui_element_table_end->quad0 + iVar7) + 10.0;
      *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) =
           *(float *)(ui_element_table_end->_pad5 + iVar7 + 4) + 10.0;
      *(float *)(ui_element_table_end->_pad4 + iVar7) =
           *(float *)(ui_element_table_end->_pad4 + iVar7) + 10.0;
      iVar7 = iVar8;
    } while (iVar8 < 0x70);
  }
  iVar8 = 100;
  piVar4 = (int *)&ui_element_ptr_table;
  iVar7 = -0x14;
  do {
    *(int *)(*piVar4 + 0x14) = *(int *)(*piVar4 + 0x14) + iVar8;
    *(int *)(*piVar4 + 0x10) = *(int *)(*piVar4 + 0x10) + iVar8;
    if (0 < iVar7) {
      *(float *)(*piVar4 + 0x18) = *(float *)(*piVar4 + 0x18) - (float)iVar7;
    }
    iVar7 = iVar7 + 0x14;
    iVar8 = iVar8 + 100;
    piVar4 = piVar4 + 1;
  } while (iVar7 < 0x65);
  iVar7 = game_is_full_version();
  if ((char)iVar7 != '\0') {
    full_version_ui_adjusted = 1;
  }
  puVar11 = ui_menu_item_element._pad3;
  puVar12 = &DAT_00488b8c;
  for (iVar7 = 0x3a; puVar11 = puVar11 + 4, iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar12 = puVar12 + 1;
  }
  _DAT_00488b78 = _DAT_00488b70 + 280.0;
  _DAT_00488b7c = _DAT_00488b74 + 180.0;
  _DAT_00488b68 = 0xc2340000;
  _DAT_00488b6c = 0x43520000;
  _DAT_00488b84 = 0;
  _DAT_00488b88 = &LAB_004475d0;
  _DAT_00488b54 = 1;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_00488ea4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_00488e80 = 0xc25c0000;
  _DAT_00488e84 = 0x43d70000;
  fStack_30 = 270.0;
  fStack_2c = -38.0;
  ui_element_set_rect((ui_element_t *)&crt_stderr_buffer,124.0,30.0,&fStack_30);
  _DAT_0048906c = ui_button_texture_id;
  _DAT_00488fa0 = 0;
  _DAT_00488fa4 = 0x3f600000;
  _DAT_00488fc0 = 0x3f600000;
  _DAT_00488fbc = 0x3f800000;
  _DAT_00488fd8 = 0x3f800000;
  _DAT_00488ff4 = 0;
  _DAT_00488fdc = 0x3f800000;
  _DAT_00488ff8 = 0x3f800000;
  _DAT_00488e9c = ui_menu_main_click_quit;
  _DAT_00488e6c = 1;
  _DAT_00488e98 = 0x30;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_0048b9f4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_0048b9d0 = 0xc2700000;
  _DAT_0048b9d4 = 0x43520000;
  puVar12 = &ui_element_controls_rect;
  puVar13 = &DAT_0048badc;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  menu_y_list_main_a = menu_y_list_main_a + 100;
  menu_y_list_main_b = menu_y_list_main_b + 100;
  _DAT_0048b9ec = ui_menu_main_click_options;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_0048bd0c;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_0048bce8 = 0xc2a00000;
  _DAT_0048bcec = 0x43870000;
  puVar12 = &ui_quit_button_element;
  puVar13 = &DAT_0048bdf4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  _DAT_0048bd04 = &LAB_004474e0;
  menu_y_list_options_a = menu_y_list_options_a + 200;
  menu_y_list_options_b = menu_y_list_options_b + 200;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_0048c024;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_0048c000 = 0xc2c80000;
  _DAT_0048c004 = 0x43a50000;
  puVar12 = &crt_stderr_buffer;
  puVar13 = &DAT_0048c10c;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  menu_y_list_credits_a = menu_y_list_credits_a + 300;
  menu_y_list_credits_b = menu_y_list_credits_b + 300;
  _DAT_0048c318 = 0xc32f0000;
  _DAT_0048c31c = 0x42340000;
  _DAT_0048c01c = &LAB_00447490;
  _DAT_0048c018 = 0x30;
  _DAT_0048c304 = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &perk_screen_panel_offset_x;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  perk_screen_panel_y = 0xc2340000;
  menu_y_list_quest_a = menu_y_list_quest_a + 100;
  perk_screen_pos_y = 0x42dc0000;
  menu_y_list_quest_b = menu_y_list_quest_b + 100;
  _DAT_0048919c = 0x43110000;
  _DAT_0048c61c = 1;
  _DAT_00489198 = 0xc2700000;
  _DAT_00489184 = 1;
  puVar11 = ui_menu_item_element._pad5 + 0xb0;
  puVar12 = &DAT_004894d4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  _DAT_004894b0 = 0xc2340000;
  _DAT_004894b4 = 0x43520000;
  pfVar6 = (float *)&DAT_004895bc;
  do {
    pfVar5 = pfVar6 + 7;
    *pfVar6 = *pfVar6 + 10.0;
    pfVar6[1] = pfVar6[1] + 10.0;
    pfVar6 = pfVar5;
  } while ((int)pfVar5 < 0x48962c);
  _DAT_004894d0 = &LAB_0044ed80;
  _DAT_0048949c = 1;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_004897ec;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_004897cc = 0x43e70000;
  _DAT_004897c8 = 0xc25c0000;
  puVar12 = &crt_stderr_buffer;
  puVar13 = &DAT_004898d4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  _DAT_004897e4 = ui_menu_main_click_quit;
  _DAT_0048c948 = 0xc32f0000;
  _DAT_004897b4 = 1;
  _DAT_004897e0 = 0x30;
  _DAT_0048c94c = 0x42340000;
  _DAT_0048c934 = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &menu_survival_y_base;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  _DAT_0048cc64 = 0x42dc0000;
  menu_survival_y_scroll = 0xc2340000;
  menu_y_list_survival_b = menu_y_list_survival_b + 100;
  menu_y_list_survival_a = menu_y_list_survival_a + 100;
  ui_list_scroll_b = 0xc3340000;
  ui_list_scroll_a = 0x43070000;
  puVar11 = ui_menu_item_element._pad3;
  _DAT_0048cc4c = 1;
  _DAT_0048cf64 = 1;
  puVar12 = &DAT_0048d2b4;
  for (iVar7 = 0x3a; iVar8 = config_blob.screen_width, puVar11 = puVar11 + 4, iVar7 != 0;
      iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar12 = puVar12 + 1;
  }
  _DAT_0048d290 = 0xc3250000;
  if (config_blob.screen_width < 0x281) {
    _DAT_0048d290 = 0xc3370000;
  }
  DAT_0048d294 = 0x43480000;
  _DAT_0048d2b0 = &LAB_00448cd0;
  _DAT_0048d27c = 1;
  puVar3 = &ui_menu_item_element;
  puVar12 = &DAT_0048d5cc;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _DAT_0048d5a8 = 0xc31b0000;
  _DAT_0048d5ac = 0x43d20000;
  puVar12 = &crt_stderr_buffer;
  puVar13 = &DAT_0048d6b4;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  _DAT_0048d8c0 = 0xc32f0000;
  _DAT_0048d8c4 = 0x42340000;
  _DAT_0048d5c4 = ui_menu_main_click_options;
  _DAT_0048d594 = 0;
  _DAT_0048d5c0 = 0x30;
  _DAT_0048d8ac = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &quest_panel_offset_y;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  quest_results_pos_x = 0xc2340000;
  menu_y_list_highscore_a = menu_y_list_highscore_a + 100;
  quest_results_pos_y = 0x42dc0000;
  menu_y_list_highscore_b = menu_y_list_highscore_b + 100;
  _DAT_0048def4 = 0x42f40000;
  _DAT_0048dbc4 = 1;
  _DAT_0048def0 = 0xc3070000;
  _DAT_0048dedc = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &DAT_0048e22c;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  _DAT_0048e20c = 0x43390000;
  _DAT_0048e208 = 0xc0a00000;
  _DAT_0048e524 = 0x42f40000;
  _DAT_0048e228 = &LAB_00447d40;
  _DAT_0048e1f4 = 1;
  _DAT_0048e520 = 0xc3070000;
  _DAT_0048e50c = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &DAT_0048e85c;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  _DAT_0048e83c = 0x43390000;
  _DAT_0048e838 = 0xc0a00000;
  _DAT_0048e824 = 1;
  puVar11 = ui_menu_item_element._pad3;
  ui_perk_screen_x_offset = (float)(iVar8 + -0x15e);
  puVar12 = &DAT_0048a134;
  for (iVar7 = 0x3a; puVar11 = puVar11 + 4, iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar12 = puVar12 + 1;
  }
  _DAT_0048a114 = 0x43480000;
  if (iVar8 < 0x321) {
    if (iVar8 < 0x281) {
      ui_perk_screen_x_offset = ui_perk_screen_x_offset + 10.0;
    }
    else {
      ui_perk_screen_x_offset = ui_perk_screen_x_offset - 30.0;
    }
  }
  else {
    ui_perk_screen_x_offset = ui_perk_screen_x_offset - 65.0;
  }
  _DAT_0048a0fc = 1;
  DAT_0048a40c = 1;
  _DAT_00489ae4 = 0x42f40000;
  _DAT_00489ae0 = 0xc3250000;
  if (iVar8 < 0x281) {
    _DAT_00489ae0 = 0xc3570000;
  }
  _DAT_00489acc = 1;
  puVar11 = ui_menu_item_element._pad4 + 0xac;
  puVar12 = &ui_menu_item_y_base;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar11;
    puVar11 = puVar11 + 4;
    puVar12 = puVar12 + 1;
  }
  fStack_30 = -60.0;
  fStack_2c = 185.0;
  ui_menu_fade_alpha = 0x43390000;
  ui_menu_anim_timer = 0xc20c0000;
  if (iVar8 < 0x281) {
    ui_menu_anim_timer = 0xc2aa0000;
  }
  DAT_00489de4 = 1;
  ui_timeline_target_end = 500;
  piVar4 = (int *)&ui_element_ptr_table;
  iVar7 = -0xb;
  do {
    if (iVar8 < 0x281) {
      fVar9 = (float)iVar7;
      iVar15 = 0;
      do {
        pfVar6 = (float *)(*piVar4 + 0x3c + iVar15);
        *pfVar6 = *(float *)(*piVar4 + 0x3c + iVar15) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        pfVar6 = (float *)(*piVar4 + 0x20c + iVar15);
        *pfVar6 = *(float *)(*piVar4 + 0x20c + iVar15) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        pfVar6 = (float *)(*piVar4 + 0x124 + iVar15);
        *pfVar6 = *(float *)(*piVar4 + 0x124 + iVar15) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        *(float *)(*piVar4 + 0x40 + iVar15) = *(float *)(*piVar4 + 0x40 + iVar15) - fVar9;
        *(float *)(*piVar4 + 0x210 + iVar15) = *(float *)(*piVar4 + 0x210 + iVar15) - fVar9;
        pfVar6 = (float *)(*piVar4 + 0x128 + iVar15);
        pfVar5 = (float *)(*piVar4 + 0x128 + iVar15);
        iVar15 = iVar15 + 0x1c;
        *pfVar5 = *pfVar6 - fVar9;
        iVar8 = config_blob.screen_width;
      } while (iVar15 < 0x70);
    }
    iVar7 = iVar7 + 0xb;
    piVar4 = piVar4 + 1;
  } while (iVar7 < 0x38);
  piVar4 = (int *)&ui_menu_element_ptr_table;
  iVar7 = -5;
  iVar15 = -0xb;
  do {
    if (iVar8 < 0x281) {
      fVar9 = (float)iVar15;
      iVar2 = 0;
      do {
        pfVar6 = (float *)(*piVar4 + 0x3c + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x3c + iVar2) * 0.8;
        pfVar6[1] = pfVar6[1] * 0.8;
        pfVar6 = (float *)(*piVar4 + 0x20c + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x20c + iVar2) * 0.8;
        pfVar6[1] = pfVar6[1] * 0.8;
        pfVar6 = (float *)(*piVar4 + 0x124 + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x124 + iVar2) * 0.8;
        pfVar6[1] = pfVar6[1] * 0.8;
        *(float *)(*piVar4 + 0x40 + iVar2) = *(float *)(*piVar4 + 0x40 + iVar2) - fVar9;
        *(float *)(*piVar4 + 0x210 + iVar2) = *(float *)(*piVar4 + 0x210 + iVar2) - fVar9;
        pfVar6 = (float *)(*piVar4 + 0x128 + iVar2);
        pfVar5 = (float *)(*piVar4 + 0x128 + iVar2);
        iVar2 = iVar2 + 0x1c;
        *pfVar5 = *pfVar6 - fVar9;
        iVar8 = config_blob.screen_width;
      } while (iVar2 < 0x70);
    }
    else if (iVar8 < 0x321) {
      fVar9 = (float)iVar7;
      iVar2 = 0;
      do {
        pfVar6 = (float *)(*piVar4 + 0x3c + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x3c + iVar2) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        pfVar6 = (float *)(*piVar4 + 0x20c + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x20c + iVar2) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        pfVar6 = (float *)(*piVar4 + 0x124 + iVar2);
        *pfVar6 = *(float *)(*piVar4 + 0x124 + iVar2) * 0.9;
        pfVar6[1] = pfVar6[1] * 0.9;
        *(float *)(*piVar4 + 0x40 + iVar2) = *(float *)(*piVar4 + 0x40 + iVar2) - fVar9;
        *(float *)(*piVar4 + 0x210 + iVar2) = *(float *)(*piVar4 + 0x210 + iVar2) - fVar9;
        pfVar6 = (float *)(*piVar4 + 0x128 + iVar2);
        pfVar5 = (float *)(*piVar4 + 0x128 + iVar2);
        iVar2 = iVar2 + 0x1c;
        *pfVar5 = *pfVar6 - fVar9;
        iVar8 = config_blob.screen_width;
      } while (iVar2 < 0x70);
    }
    iVar15 = iVar15 + 0xb;
    iVar7 = iVar7 + 5;
    piVar4 = piVar4 + 1;
  } while (iVar15 < 0x17);
  if (iVar8 < 0x281) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x3c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x20c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x124);
      iVar15 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x124) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      *(float *)(ui_menu_layout_c + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x40) - 11.0;
      *(float *)(ui_menu_layout_c + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x210) - 11.0;
      *(float *)(ui_menu_layout_c + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x128) - 11.0;
      iVar7 = iVar15;
      iVar8 = config_blob.screen_width;
    } while (iVar15 < 0x70);
  }
  else if (iVar8 < 0x321) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x3c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x20c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_c + iVar7 + 0x124);
      iVar15 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_c + iVar7 + 0x124) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      *(float *)(ui_menu_layout_c + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x40) - 3.0;
      *(float *)(ui_menu_layout_c + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x210) - 3.0;
      *(float *)(ui_menu_layout_c + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_c + iVar7 + 0x128) - 3.0;
      iVar7 = iVar15;
      iVar8 = config_blob.screen_width;
    } while (iVar15 < 0x70);
  }
  if (iVar8 < 0x281) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x3c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x20c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x124);
      iVar15 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x124) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      *(float *)(ui_menu_layout_a + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x40) - 11.0;
      *(float *)(ui_menu_layout_a + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x210) - 11.0;
      *(float *)(ui_menu_layout_a + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x128) - 11.0;
      iVar7 = iVar15;
      iVar8 = config_blob.screen_width;
    } while (iVar15 < 0x70);
  }
  else if (iVar8 < 0x321) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x3c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x20c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_a + iVar7 + 0x124);
      iVar15 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_a + iVar7 + 0x124) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      *(float *)(ui_menu_layout_a + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x40) - 3.0;
      *(float *)(ui_menu_layout_a + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x210) - 3.0;
      *(float *)(ui_menu_layout_a + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_a + iVar7 + 0x128) - 3.0;
      iVar7 = iVar15;
      iVar8 = config_blob.screen_width;
    } while (iVar15 < 0x70);
  }
  if (iVar8 < 0x281) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x3c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x20c) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x124);
      iVar8 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x124) * 0.8;
      pfVar6[1] = pfVar6[1] * 0.8;
      *(float *)(ui_menu_layout_b + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x40) - 11.0;
      *(float *)(ui_menu_layout_b + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x210) - 11.0;
      *(float *)(ui_menu_layout_b + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x128) - 11.0;
      iVar7 = iVar8;
    } while (iVar8 < 0x70);
  }
  else if (iVar8 < 0x321) {
    iVar7 = 0;
    do {
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x3c);
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x3c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x20c);
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x20c) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      pfVar6 = (float *)(ui_menu_layout_b + iVar7 + 0x124);
      iVar8 = iVar7 + 0x1c;
      *pfVar6 = *(float *)(ui_menu_layout_b + iVar7 + 0x124) * 0.9;
      pfVar6[1] = pfVar6[1] * 0.9;
      *(float *)(ui_menu_layout_b + iVar7 + 0x40) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x40) - 3.0;
      *(float *)(ui_menu_layout_b + iVar7 + 0x210) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x210) - 3.0;
      *(float *)(ui_menu_layout_b + iVar7 + 0x128) =
           *(float *)(ui_menu_layout_b + iVar7 + 0x128) - 3.0;
      iVar7 = iVar8;
    } while (iVar8 < 0x70);
  }
  ui_element_init_defaults(&ui_element_back_button);
  _ui_element_back_button_callback = ui_back_button_callback;
  puVar3 = &ui_menu_item_element;
  puVar12 = &perk_prompt_bounds_min_x;
  for (iVar7 = 0x3a; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = *(undefined4 *)puVar3;
    puVar3 = (ui_element_t *)(puVar3->_pad0 + 2);
    puVar12 = puVar12 + 1;
  }
  _ui_element_alpha_1 = 0x3f800000;
  _ui_element_field_1 = 0;
  _ui_element_alpha_2 = 0x3f800000;
  _ui_element_field_2 = 0;
  ui_element_load((ui_element_t *)&ui_element_level_up_text,s_ui_ui_textLevelUp_jaz_004792a0);
  fStack_30 = -230.0;
  fStack_2c = -27.0;
  ui_element_set_rect((ui_element_t *)&ui_element_level_up_text,75.0,25.0,&fStack_30);
  pfVar6 = (float *)&ui_element_level_up_text_field_4;
  do {
    pfVar5 = pfVar6 + 7;
    pfVar6[-0x3b] = pfVar6[-0x3b] - 300.0;
    pfVar6[-0x3b] = pfVar6[-0x3b] * 0.75;
    pfVar6[-0x3a] = pfVar6[-0x3a] * 0.75;
    pfVar6[-1] = pfVar6[-1] * 0.85;
    *pfVar6 = *pfVar6 * 0.85;
    pfVar6[-1] = pfVar6[-1] - 46.0;
    *pfVar6 = *pfVar6 - 4.0;
    pfVar6 = pfVar5;
  } while ((int)pfVar5 < 0x48f3a4);
  if (config_blob.screen_width == 0x280) {
    fStack_30 = 690.0;
    fStack_2c = 80.0;
    _perk_prompt_origin_y = 0x42a00000;
  }
  else {
    fStack_2c = 40.0;
    fStack_30 = (float)(config_blob.screen_width + 0x32);
    _perk_prompt_origin_y = 0x42200000;
  }
  piVar4 = (int *)&ui_element_ptr_table;
  _perk_prompt_origin_x = fStack_30;
  do {
    iVar7 = *piVar4;
    piVar4 = piVar4 + 1;
    *(float *)(iVar7 + 0x1c) =
         ((float)config_blob.screen_width * 0.0015625 * 150.0 - 150.0) + *(float *)(iVar7 + 0x1c);
    iVar7 = config_blob.screen_width;
  } while ((int)piVar4 < 0x48f20c);
  _ui_credits_pos_x = (float)(config_blob.screen_width + -0x15e);
  puVar12 = &ui_credits_active_flag;
  puVar13 = &ui_credits_element_start;
  for (iVar8 = 0xc6; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  _ui_credits_pos_y = 0x43480000;
  if (iVar7 < 0x281) {
    _ui_credits_pos_x = _ui_credits_pos_x + 80.0;
    _ui_credits_pos_y = 0x433a0000;
  }
  ui_credits_element_flag_1 = 1;
  ui_credits_element_flag_2 = 1;
  ppuVar10 = &ui_element_table_end;
  do {
    ui_element_layout_calc((float)*ppuVar10);
    ppuVar10 = ppuVar10 + 1;
  } while ((int)ppuVar10 < 0x48f20c);
  return;
}


