/* camera_update @ 00409500 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* updates camera offsets and screen shake */

void camera_update(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (camera_shake_timer <= 0.0) {
    camera_shake_offset_x = 0.0;
    camera_shake_offset_y = 0.0;
  }
  else {
    camera_shake_timer = camera_shake_timer - frame_dt * 3.0;
    if (camera_shake_timer < 0.0) {
      camera_shake_pulses = camera_shake_pulses + -1;
      if (camera_shake_pulses < 1) {
        camera_shake_timer = 0.0;
      }
      else {
        camera_shake_timer = 0.1;
        if (time_scale_active != '\0') {
          camera_shake_timer = 0.06;
        }
        iVar1 = crt_rand();
        iVar4 = camera_shake_pulses * 0x3c;
        iVar2 = crt_rand();
        iVar1 = iVar1 % (iVar4 / 0x14) + iVar2 % 10;
        uVar3 = crt_rand();
        if ((uVar3 & 1) == 0) {
          iVar1 = -iVar1;
        }
        camera_shake_offset_x = (float)iVar1;
        iVar1 = crt_rand();
        iVar4 = camera_shake_pulses * 0x3c;
        iVar2 = crt_rand();
        iVar1 = iVar1 % (iVar4 / 0x14) + iVar2 % 10;
        uVar3 = crt_rand();
        if ((uVar3 & 1) == 0) {
          camera_shake_offset_y = (float)-iVar1;
        }
        else {
          camera_shake_offset_y = (float)iVar1;
        }
      }
    }
  }
  if (config_blob.reserved0._20_4_ == 1) {
    camera_offset_x =
         (float)(config_blob.screen_width / 2) -
         (&player_state_table)[render_overlay_player_index].pos_x;
    camera_offset_y =
         (float)(config_blob.screen_height / 2) -
         (&player_state_table)[render_overlay_player_index].pos_y;
    goto LAB_004097e4;
  }
  if (0.0 < player_state_table.health) {
    if (player2_health <= 0.0) goto LAB_00409716;
  }
  else {
    if (0.0 < player2_health) {
      camera_offset_x = (float)(config_blob.screen_width / 2) - player2_pos_x;
      camera_offset_y = (float)(config_blob.screen_height / 2) - player2_pos_y;
      goto LAB_004097e4;
    }
LAB_00409716:
    if (0.0 < player_state_table.health) {
      camera_offset_x = (float)(config_blob.screen_width / 2) - player_state_table.pos_x;
      camera_offset_y = (float)(config_blob.screen_height / 2) - player_state_table.pos_y;
      goto LAB_004097e4;
    }
    if (player2_health <= 0.0) goto LAB_004097e4;
  }
  if (0.0 < player_state_table.health) {
    camera_offset_x =
         (float)(config_blob.screen_width / 2) -
         (player_state_table.pos_x - (player_state_table.pos_x - player2_pos_x) * 0.5);
    camera_offset_y =
         (float)(config_blob.screen_height / 2) -
         (player_state_table.pos_y - (player_state_table.pos_y - player2_pos_y) * 0.5);
  }
LAB_004097e4:
  camera_offset_x = camera_offset_x + camera_shake_offset_x;
  camera_offset_y = camera_offset_y + camera_shake_offset_y;
  if (-1.0 < camera_offset_x) {
    camera_offset_x = -1.0;
  }
  if (-1.0 < camera_offset_y) {
    camera_offset_y = -1.0;
  }
  if (camera_offset_x < (float)(config_blob.screen_width - terrain_texture_width)) {
    camera_offset_x = (float)(config_blob.screen_width - terrain_texture_width);
  }
  if ((float)(config_blob.screen_height - terrain_texture_height) <= camera_offset_y) {
    return;
  }
  camera_offset_y = (float)(config_blob.screen_height - terrain_texture_height);
  return;
}


