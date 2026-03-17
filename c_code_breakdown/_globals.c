/* ============================================================================
 * RENAMED DECOMPILED C CODE - Sixty-fifth Pass
 * 
 * This file has been processed to rename variables, functions, and constants
 * to more readable names based on:
 * 1. C_CODE_PORTING_TRACKER.md documentation
 * 2. Decompiler function comments
 * 3. Code patterns and context
 *
 * Renames applied:
 * Pass 1:
 * - Removed leading underscores from global variables
 * - Fixed typos (e.g., perk_id_fire_caugh -> perk_id_fire_cough)
 * - Named functions based on decompiler comments
 * Pass 2:
 * - Named DAT_ globals based on usage context (quest results, HUD, camera)
 * - Named FUN_ functions based on behavior analysis
 * - Cleaned up remaining underscore-prefixed globals
 * Pass 3:
 * - Named game state management (game_state_set, ui_elements_reset_state)
 * - Named audio system (audio_suspend_flag, audio_resume_all)
 * - Named terrain system (terrain_generate, terrain_generate_random)
 * - Named UI/mouse input (ui_mouse_x, gamepad_active_flag)
 * - Named texture handles (texture_cursor_id, texture_aim_id, etc)
 * - Named quest results layout (quest_results_*, quest_back_button_*)
 * - Named perk selection screen (perk_screen_*, perk_color_*)
 * Pass 4:
 * - Named vec2 math (vec2_add)
 * - Named audio format functions (audio_find_format, audio_create_format)
 * - Named trial time limit (trial_time_limit_ms_get)
 * - Named UI quit button elements (ui_quit_button_*)
 * - Named UI element pointer table (ui_element_ptr_table)
 * - Named console error display (console_error_display)
 * Pass 5:
 * - Named spline interpolation (vec2_bilinear_interp, vec3_hermite_spline, vec3_catmull_rom_spline)
 * - Named renderer dispatch functions (renderer_dispatch_*, renderer_vtable_func_*)
 * Pass 6:
 * - Named highscore system (highscore_current_rank, highscore_name_input_buf)
 * - Named UI button textures (ui_button_small_texture, ui_button_medium_texture)
 * - Named player aim update (player_aim_update_thunk, heading_normalize_or_calc)
 * - Named perk effect targets (doctor_perk_target_creature, jinxed_effect_cooldown)
 * - Named experience timer (lean_mean_exp_timer)
 * Pass 7:
 * - Named vector math (vec3_normalize, mat4_multiply)
 * - Named renderer SSE setup (renderer_sse_vtable_setup, cpu_features_get)
 * - Named texture strings (s_iGameUI_texture_name, s_iHeart_texture_name)
 * - Named CRT stdio structs (crt_stdout_struct, crt_stderr_struct)
 * Pass 8:
 * - Named player weapon (player_last_weapon_id)
 * - Named tutorial hint flags (tutorial_hint_shown_flag, tutorial_hint_pos_*)
 * Pass 9:
 * - Named player state aux (player_state_aux_counter)
 * - Named weapon defaults (weapon_default_clip_size, weapon_default_reload_time)
 * - Named effect UV table (effect_uv_16x16_table)
 * - Named screen size (screen_height_f)
 * - Named key char count (key_char_count, key_char_buffer_size)
 * - Named browser navigation (browser_open_result, browser_url_ptr, browser_open_pending)
 * - Named screen mode setting (screen_mode_setting)
 * - Named allocated memory (allocated_memory_ptr)
 * Pass 10:
 * - Named shareware buttons (shareware_buy_button, shareware_continue_button)
 * - Named main menu callback (main_menu_version_callback)
 * - Named bonus meta constructors (bonus_meta_table_ctor, bonus_meta_entry_dtor)
 * - Named atexit registers (bonus_meta_table_atexit_register, projectile_meta_table_atexit_register)
 * Pass 11:
 * - Named resource pack (resource_pack_entry_name_buf, resource_pack_path)
 * - Named string compare (string_compare_nocase)
 * - Named UI profile menu (ui_profile_init_flags, ui_profile_list_*, profile_name_*)
 * - Named UI profile buttons (ui_update_button_*, ui_profile_delete_*, ui_profile_add_*)
 * - Named weapon table entries (weapon_*_type, weapon_*_clip, weapon_*_sfx_*, weapon_*_fire_rate, etc)
 * - Named profile screen state (profile_screen_add_mode, profile_screen_selection_idx)
 * Pass 12:
 * - Named mod API strings (s_grimgfx, s_grimsfx, s_IDirect3D8)
 * - Named mod API printf buffer (mod_api_printf_buf)
 * - Named joystick input strings (s_Joys*, s_JoyAxis*)
 * Pass 13:
 * - Named UI slider function (ui_slider_update_and_draw)
 * - Named UI rect textures (ui_rect_on_texture_id, ui_rect_off_texture_id, s_ui_rectOn, s_ui_rectOff)
 * - Named UI tab key flag (ui_tab_key_disabled)
 * - Named UI menu initialized flags (ui_main_menu_initialized, ui_gameplay_menu_initialized)
 * Pass 14:
 * - Named player render disabled flag (player_render_disabled_flag)
 * - Named player sprite texture (player_sprite_texture_id)
 * - Named secondary effect UV tables (effect_uv8_secondary_u, effect_uv8_secondary_v)
 * Pass 15:
 * - Named UI fail screen buttons (ui_fail_retry_*, ui_fail_play_another_*, ui_fail_main_menu_*)
 * - Named UI fail screen init flags (ui_fail_screen_init_flags)
 * - Named menu strings (s_Play_Another, s_main_menu)
 * Pass 16:
 * - Named effect FX functions (fx_spawn_electric_arc, fx_spawn_plasma_explosion, fx_spawn_shockwave)
 * - Named sprite effect UV (sprite_effect_uv_u, sprite_effect_uv_v)
 * - Named bonus animation timer (bonus_animation_timer)
 * - Named projectile bullet texture (projectile_bullet_texture)
 * - Named texture loading strings (s_loading_texture_ok, s_loading_texture_failed)
 * - Named audio strings (s_audio_restored, s_audio_suspended)
 * - Named bonus label buffer (bonus_label_buffer, bonus_points_format_prefix)
 * Pass 17:
 * - Named perk cooldown thresholds (man_bomb_cooldown_threshold, fire_cough_cooldown_threshold, hot_tempered_cooldown_threshold)
 * - Named player turn speed (player_turn_speed_accumulated)
 * - Named movement timers (movement_decay_rate, movement_boost_timer)
 * - Named SFX identifiers (sfx_player_fire_reload_a/b, weapon_default_shot_cooldown_single, weapon_default_reload_delay)
 * - Named default string (s_default)
 * Pass 18:
 * - Named effect UV steps (effect_uv_step_16, effect_uv_step_8, effect_uv_step_4, effect_uv_step_2)
 * - Named fx spawn fire particles (fx_spawn_fire_particles)
 * - Named effect spawn skip counter (effect_spawn_skip_counter)
 * - Named effect dummy entry (effect_dummy_entry)
 * Pass 19:
 * - Named perk bloody mess pointers (perk_bloody_mess_name_ptr, perk_bloody_mess_name_fx_ptr, perk_bloody_mess_desc_fx_ptr)
 * - Named perk init counter (perk_init_counter)
 * Pass 20:
 * - Named renderer backend vtable ptr (renderer_backend_vtable_ptr)
 * - Named quaternion slerp internal (quat_slerp_internal)
 * - Named renderer init backend 1 (renderer_init_backend_1)
 * - Named vec2 normalize stdcall (vec2_normalize_stdcall)
 * - Named mat4 transform vec4/vec2 (mat4_transform_vec4, mat4_transform_vec2)
 * Pass 21 (Player Controller Focus):
 * - Named weapon swap cooldown (weapon_swap_cooldown_ms)
 * - Named HUD flags (hud_show_ammo_icon, hud_show_experience_bar, hud_show_timer)
 * - Named creature type table entries for lizard (texture, sfx, anim)
 * - Named creature type table entries for spider (texture, sfx, anim)
 * - Named tutorial init flag (tutorial_init_flag)
 * - Named creature type table init count (creature_type_table_init_count)
 * - Named UI timeline targets (ui_timeline_target_end, ui_timeline_target_start)
 * - Named bonus labels and icons (s_bonus_*, bonus_*_name, bonus_*_icon_id)
 * - Named game status strings (s_game_load_status_*)
 * - Named creature strings (s_creature_zombie, s_creature_lizard, s_creature_spider)
 * Pass 22 (Collision and Console):
 * - Named console command strings (s_cmd_loadtexture_usage, s_cmd_setresourcepaq_usage)
 * - Named file format strings (s_file_not_found_fmt, s_set_resource_paq_fmt)
 * - Named dinput DLL path (s_dinput_dll_path)
 * Pass 23 (Player Controller Verification):
 * - Verified player controller functions (player_apply_move_with_spawn_avoidance, player_start_reload)
 * - Verified input functions (input_primary_just_pressed, player_aim_update_thunk)
 * - Verified time scale variables (time_scale_active, time_scale_factor)
 * - Verified perk cooldown thresholds (man_bomb_cooldown_threshold, fire_cough_cooldown_threshold)
 * - All player controller core symbols already correctly named from prior passes
 * Pass 24 (Creature AI Focus):
 * - Named highscore init flag (highscore_init_flag)
 * - Named file mode append binary (file_mode_append_binary)
 * - Named score/SFX strings (s_unexpected_sc_null, s_scores_dir, s_unable_to_save_score, s_snd_buffer_restored)
 * - Verified creature pool fields (type_id, health, ai_mode, link_index, target_offset_x/y, vel_x/y, etc.)
 * - Verified quest build functions (quest_build_nagolipoli, quest_build_the_annihilation, etc.)
 * Pass 25 (Creature AI and UI Systems):
 * - Named creature_name_buffer, ui_update_button_init_flag, ui_update_button_reserved
 * - Named UI screen flags (ui_credits_active_flag, ui_menu_active_flag_b, ui_splash_skip_flag, etc.)
 * - Named creature name functions (creature_name_get_part, creature_unique_name_get)
 * - Named UI stats/weapon strings and format strings
 * Pass 26 (Audio Systems):
 * - Named sfx_load_counter, music_playlist_index
 * - Named SFX/music format strings (s_sfx_sample_ok_fmt, s_sfx_tune_ok_fmt, etc.)
 * - Named music path strings (s_music_paq_path, s_music_intro_path, s_music_crimson_theme_path, etc.)
 * - Verified SFX entry functions, music track functions, audio init
 * Pass 27 (Audio Systems Part 2):
 * - Named SFX init/shutdown strings (s_init_sfx_done, s_sfx_shutdown, s_sfx_released, s_snd_detected_hearable)
 * - Verified SFX playback functions (sfx_play, sfx_play_panned, sfx_play_exclusive, sfx_mute_all)
 * - Verified audio channel control (audio_suspend_channels, audio_resume_channels, sfx_is_unmuted)
 * Pass 28 (Resource and Buffer Functions):
 * - Named sfx_entry_init (sfx_entry_deinit)
 * - Named highscore cache path buffers (highscore_cache_path_buf, highscore_named_cache_buf, etc.)
 * - Named path format strings (s_opening_named_cache_fmt, s_opening_path_fmt)
 * - Verified resource pack/buffer reader functions
 * Pass 29 (Menu Systems):
 * - Named ui_menu_element_ptr_table, input_get_active_axis, vec2_add_offset, ui_element_init_defaults
 * - Named input scheme strings (s_input_scheme_relative, s_input_scheme_static, etc.)
 * - Named s_elem_null_error, s_unknown_label
 * - Verified UI menu layout, element, focus, profile, and screen state functions
 * Pass 30 (Menu Systems Part 2):
 * - Named creature name part strings (s_creature_name_part_00 through _20)
 * - Verified game_state_set, ui_elements_reset_state, mods_any_available
 * - Verified UI button/element flags, main menu callbacks, quest build functions
 * Pass 31 (Visual Effects and Particles):
 * - Named loading_flag_a/b/c, credits_line_count
 * - Verified FX spawn functions (electric_arc, plasma_explosion, fire_particles, shockwave)
 * - Verified effects_update/render, effect_spawn/free, effect_template_* variables
 * - Verified creature damage/death functions, perk modifiers
 * Pass 32 (Perk Metadata):
 * - Named 37 _DAT_ perk name/desc pointers (_perk_sharpshooter_name, etc.)
 * - Named perk_bloody_mess_desc_ptr, perk_instant_winner_flags, perk_unlock_table_ptr
 * - Named s_perk_randomizer_failed string
 * - Verified perk_can_offer, perk_select_random, perks_rebuild_available
 * Pass 33 (Menus and HUD):
 * - Named bonus_hud_add_slot (FUN_0041a810)
 * - Named UI rotation matrix elements (_ui_rotation_cos, _ui_rotation_sin, etc.)
 * - Named bonus_hud_slot_table_end_ptr
 * - Verified ui_element_*, ui_draw_progress_bar, bonus_hud_slot_update_and_render
 * Pass 34 (HUD Rendering):
 * - Named UI indicator strings (s_ui_ind_fire/bullet/rocket/electric_jaz)
 * - Named HUD format strings (s_hud_exp_format, s_int_format, s_extra_ammo_format)
 * - Verified hud_update_and_render, HUD show flags, texture IDs, timeline targets
 * Pass 35 (Bonus HUD and UI):
 * - Named bonus_weapon_power_up_name/icon_id, bonus_speed_icon_id
 * - Verified bonus pickup handling, effect spawn functions, tutorial symbols
 * - Verified shock_chain/fireblast handling, creature spawn functions
 * Pass 36 (Broad Comprehensive):
 * - Named 35+ UI button structures (ui_button_cancel/select/main_menu/restart/continue/highscores)
 * - Named ordinal format strings and scratch buffer
 * - Named perk choice clicked flags, clock gauge textures
 * - Verified game update screen functions, perk effects, screen rendering
 * Pass 37 (Broad Comprehensive 2):
 * - Named joystick_pov_check_up/down functions
 * - Verified fx_queue_add, fx_spawn_secondary_projectile, projectile_spawn/reset_pools
 * - Verified player_apply_move_with_spawn_avoidance, vec2_add_inplace
 * Pass 38 (Broad Comprehensive 3):
 * - Named perk_choice_slot_1-6 DAT symbols
 * - Named perk_id_unknown_deprecated, credits_secret_gems_texture
 * - Named time format strings, int_format_0d
 * - Verified demo_trial_overlay_render, credits_secret game, sprite_effect_pool
 * Pass 39 (Broad Comprehensive 4):
 * - Named 12 UI element DAT/_DAT symbols (ui_element_back_button, ui_credits_*)
 * - Named ui_back_button_callback function
 * - Verified weapon_table_init, ui_element_init_defaults, ui_element_layout_calc
 * Pass 40 (Broad Comprehensive 5):
 * - Named format_time_seconds function (FUN_0040ff50)
 * - Named highscore_rank_result, s_quest_back_button_default, reg_key_path
 * - Verified quest_results_* animation, game_save/load_status, highscore functions
 * Pass 41 (Broad Comprehensive 6):
 * - Named creature_reset_all function (FUN_004281e0)
 * - Verified creature_alloc_slot, creature_spawn, creatures_none_active
 * - Verified console command handlers, player_render_overlays
 * Pass 42 (Broad Comprehensive 7):
 * - Named plugin_frame_update/plugin_pre_init functions
 * - Named credits_screen_init_flags, demo_purchase_init_flags, plugin_active_flag
 * - Named credits_scroll_top/bottom_index, _credits_scroll_time
 * Pass 43 (Broad Comprehensive 8):
 * - Named date_format_month_day, ui_stats_render_row functions
 * - Named ui_stats_text_buffer, creature_unique_name_count/table
 * - Named s_name_double_fmt, verified creature naming functions
 * Pass 44 (Broad Comprehensive 9):
 * - Named tutorial_ui_init_flags
 * - Verified tutorial_timeline_update, ui_button_table_b/c, ui_button_update
 * - Verified player_state_table fields, creature_pool fields
 * Pass 45 (Broad Comprehensive 10):
 * - Named 7 renderer dispatch wrapper functions (FUN_00453xxx, FUN_00454xxx)
 * - Named matrix_build_rotation_x function
 * - Verified quest database init, quest_meta_cursor, quest builders
 * Pass 46 (Broad Comprehensive 11):
 * - Named 8 more renderer dispatch wrappers (FUN_00454xxx, FUN_00455xxx)
 * - Named quat_slerp_squad, quat_slerp_weighted quaternion functions
 * - Named renderer_3dnow/sse2_vtable_setup, renderer_mode_id
 * Pass 47 (Broad Comprehensive 12):
 * - Named 5 SIMD matrix/quaternion functions (mat4x4_identity, mat3x3_from_euler/axis_angle)
 * - Named mat_transform_compose_simd, quat_normalize_simd
 * - Verified PackedFloating*, math_*_packed functions
 * Pass 48 (Broad Comprehensive 13):
 * - Named vec_unproject_simd, mat4_invert_simd
 * - Verified perks_init_database, perk_meta_table, perk_id_* symbols
 * - Verified creature spawn/alloc functions
 * Pass 49 (Broad Comprehensive 14):
 * - Verified console_cmd_* handlers (load_texture, set_resource_paq, open_url)
 * - Verified creature_spawn, creatures_none_active functions
 * - Verified fx_queue_rotated, fx_rotated_* symbols
 * Pass 50 (Broad Comprehensive 15):
 * - Named 20 weapon stat _DAT_ symbols (plasma_minigun, gauss_gun, rocket_launcher, mean_minigun)
 * - Weapon stats: clip, fire_rate, damage, spread, sfx_fire, sfx_reload, type
 * Pass 51 (Broad Comprehensive 16):
 * - Named 35 weapon stat _DAT_ symbols (pulse_gun, ion_rifle, ion_minigun, ion_cannon, ion_shotgun)
 * - Named sfx_shock_reload, weapon_autogun/nexgun symbols
 * Pass 52 (Broad Comprehensive 17):
 * - Named 36 weapon stat _DAT_ symbols (plasma_cannon, plague_spreader, rainbow_gun, grim, bubblegun)
 * - Named weapon_*_unlocked DAT symbols, sfx_bloodspill_01, sfx_reload_default
 * Pass 53 (Broad Comprehensive 18):
 * - Named game_state_reset_all, survival_mode_wave
 * - Verified highscore_init_sentinels, player_update, quest_meta_init
 * - Verified player_aim_screen_x/y, ui_mouse_x/y, bonus_weapon_power_up_timer
 * Pass 54 (Broad Comprehensive 19):
 * - Verified vorbis_read_pcm16, audio_find/create/init_format
 * - Verified game_is_full_version, trial_time_limit_ms_get, game_sequence_get
 * - Verified vec2_add/add_inplace, player_apply_move_with_spawn_avoidance
 * Pass 55 (Broad Comprehensive 20):
 * - Named 14 month_name_ptr_* DAT symbols, ui_date_format_buffer
 * - Named ui_text_render_color_r/g/b/a, ui_text_color_g/b
 * - Verified ui_checkbox/scrollbar_update, ui_text_input_render, ui_stats_*
 * Pass 56 (Broad Comprehensive 21):
 * - Named ui_menu_main_click_credits, ui_menu_main_click_quit
 * - Named shots_hit_count, shots_fired_count
 * - Verified input_any_key_pressed, creature_spawn_tinted, gameplay_render_world
 * Pass 57 (Broad Comprehensive 22):
 * - Named vec2_normalize_simd, color_blend_multiply
 * - Named crt_locale_type
 * - Verified vec_unproject_simd, mat4x4_identity_simd, CRT file functions
 * Pass 58 (Broad Comprehensive 23):
 * - Named 15 credits_* DAT symbols (back_button_enable/state, secret_*, screen_alpha/timer)
 * - Verified credits_screen_update, mods_any_available, mod_load_mod
 * Pass 59 (Broad Comprehensive 24):
 * - Named 17 CRT functions (crt_stream_getc, crt_va_arg_int, crt_strtol, vec3_slerp, etc.)
 * - Named 25 CRT data symbols (crt_sbh_*, crt_locale_id, crt_lock_count, etc.)
 * - Named 20 game state vars (mod_gfx_batch_active, trial/pause_overlay_fade_timer, etc.)
 * - Named creature_name_input_buffer/cursor, highscore_*, quest_elapsed_timer_ms
 * Pass 60 (Broad Comprehensive 25):
 * - Named 30 CRT functions (crt_is_valid_read/write/code_ptr, crt_ungetc, crt_mbtowc_*, etc.)
 * - Named 35 CRT data (time/calendar tables, TLS, SIMD constants, file I/O)
 * - Named 10 game state vars (ui_screen_update_callback, weapon_default_sfx_reload, etc.)
 * - Named console_slide_anim_t, cvar_mono_font_ptr, crt_mbcs_initialized
 * Pass 61 (Broad Comprehensive 26):
 * - Named 40 CRT functions (crt_getenv, crt_environ_*, crt_wctomb_*, crt_write/read_internal)
 * - Named 30 CRT data (time/calendar arrays, locale, MBCS, file I/O tables)
 * - Named math funcs (mat4x4_transform_vec2, cpu_detect_intel, renderer_dispatch_*)
 * - Named UI state vars (ui_screen_state_flags, ui_menu_anim_timer, etc.)
 * Pass 62 (Game-Focused - Menus, HUD, Weapons):
 * - Named 45 bonus HUD item fields (name/desc/icon_id/priority for all bonus types)
 * - Named 8 quest HUD textures (tex_quest_text/num1-5, tex_muzzle_flash)
 * - Named 12 perk/weapon select UI state vars (anim timers, progress, offsets)
 * - Named 8 menu/highscore/UI button labels, camera follow, progress bar color
 * Pass 63 (Broad Comprehensive 28):
 * - Named 9 CRT timezone fields (crt_tz_info_bias, crt_tz_std/dst_month/day/bias)
 * - Named 8 menu screen layouts (menu_screen_main/options/credits/quest/survival/etc.)
 * - Named 12 menu Y position lists, 10 SIMD math constants
 * - Named FX queue pools, game state (creature_search, perk_table_initialized)
 * Pass 64 (Quests, Enemies, AI):
 * - Named 12 spider_sp2 creature type fields (texture, sfx_die/attack, anim_flags/rate)
 * - Named 11 alien creature type fields (sfx_die/attack, anim_rate, base_frame)
 * - Named 7 trooper creature type fields (sfx_die, anim_flags, base_frame)
 * - Named 6 perk entry fields, 5 menu layout pointers, quest/wave state
 * Pass 65 (Broad Comprehensive 29):
 * - Named 40 SIMD sincos polynomial coefficients (Chebyshev approximation tables)
 * - Named 15 math/renderer functions (mat4x4_rotate_y/z, vec3_set, simd_sincos_packed)
 * - Named 10 game functions (creature_apply_damage, quest_file_*, render_state_push/pop)
 * - Named 8 UI page panel counts, 9 renderer vtable pointers, TLS/timezone data
 *
 * Original file: crimsonland.exe_decompiled.c
 * Generated by: rename_c_variables.py
 * ============================================================================ */

/* Decompiled from: crimsonland.exe */
