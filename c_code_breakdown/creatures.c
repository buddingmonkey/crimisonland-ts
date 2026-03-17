/* survival_spawn_creature @ 00407510 */

/* spawns a creature at the given position, selecting type/stats based on DAT_0049095c */

void __cdecl survival_spawn_creature(float *pos)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  
  iVar3 = creature_alloc_slot();
  (&creature_pool)[iVar3].pos_x = *pos;
  (&creature_pool)[iVar3].pos_y = pos[1];
  (&creature_pool)[iVar3].collision_flag = '\0';
  (&creature_pool)[iVar3].collision_timer = 0.0;
  (&creature_pool)[iVar3].ai_mode = 0;
  iVar4 = crt_rand();
  iVar4 = iVar4 % 10;
  if (player_state_table.experience < 12000) {
    if (iVar4 < 9) {
      (&creature_pool)[iVar3].type_id = 2;
    }
    else {
      (&creature_pool)[iVar3].type_id = 3;
    }
  }
  else if (player_state_table.experience < 25000) {
    if (iVar4 < 4) {
      (&creature_pool)[iVar3].type_id = 0;
    }
    else {
      (&creature_pool)[iVar3].type_id = 3;
    }
    if (8 < iVar4) {
      (&creature_pool)[iVar3].type_id = 2;
    }
  }
  else if (player_state_table.experience < 42000) {
    if (iVar4 < 5) {
      (&creature_pool)[iVar3].type_id = 2;
    }
    else {
      uVar5 = crt_rand();
      uVar5 = uVar5 & 0x80000001;
      if ((int)uVar5 < 0) {
        uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
      }
      (&creature_pool)[iVar3].type_id = uVar5 + 3;
    }
  }
  else if (player_state_table.experience < 50000) {
    (&creature_pool)[iVar3].type_id = 2;
  }
  else if (player_state_table.experience < 90000) {
    (&creature_pool)[iVar3].type_id = 4;
  }
  else {
    if (109999 < player_state_table.experience) {
      if (iVar4 < 6) {
        (&creature_pool)[iVar3].type_id = 2;
        goto LAB_00407611;
      }
      if (iVar4 < 9) {
        (&creature_pool)[iVar3].type_id = 4;
        goto LAB_00407611;
      }
    }
    (&creature_pool)[iVar3].type_id = 0;
  }
LAB_00407611:
  iVar4 = crt_rand();
  if (((byte)iVar4 & 0x1f) == 2) {
    (&creature_pool)[iVar3].type_id = 3;
  }
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].active = '\x01';
  *(undefined1 *)&(&creature_pool)[iVar3].force_target = 0;
  (&creature_pool)[iVar3].hitbox_size = 16.0;
  (&creature_pool)[iVar3].vel_x = 0.0;
  (&creature_pool)[iVar3].vel_y = 0.0;
  (&creature_pool)[iVar3].size = (float)(iVar4 % 0x14 + 0x2c);
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].heading = (float)(iVar4 % 0x13a) * 0.01;
  iVar4 = (&creature_pool)[iVar3].type_id;
  (&creature_pool)[iVar3].move_speed = (float)(player_state_table.experience / 4000) * 0.045 + 0.9;
  if (iVar4 == 3) {
    fVar1 = (&creature_pool)[iVar3].move_speed;
    (&creature_pool)[iVar3].flags = (&creature_pool)[iVar3].flags | 0x80;
    (&creature_pool)[iVar3].move_speed = fVar1 * 1.3;
  }
  uVar5 = crt_rand();
  iVar4 = (&creature_pool)[iVar3].type_id;
  (&creature_pool)[iVar3].health =
       (float)player_state_table.experience * 0.00125 + (float)(uVar5 & 0xf) + 52.0;
  if (iVar4 == 0) {
    fVar1 = (&creature_pool)[iVar3].move_speed * 0.6;
    (&creature_pool)[iVar3].move_speed = fVar1;
    if (fVar1 < 1.3) {
      (&creature_pool)[iVar3].move_speed = 1.3;
    }
    (&creature_pool)[iVar3].health = (&creature_pool)[iVar3].health * 1.5;
  }
  if (3.5 < (&creature_pool)[iVar3].move_speed) {
    (&creature_pool)[iVar3].move_speed = 3.5;
  }
  (&creature_pool)[iVar3].attack_cooldown = 0.0;
  (&creature_pool)[iVar3].reward_value = 0.0;
  if (player_state_table.experience < 50000) {
    (&creature_pool)[iVar3].tint_r =
         1.0 - 1.0 / ((float)(player_state_table.experience / 1000) + 10.0);
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].tint_g =
         ((float)(iVar4 % 10) * 0.01 + 0.9) -
         1.0 / ((float)(player_state_table.experience / 10000) + 10.0);
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].tint_b = (float)(iVar4 % 10) * 0.01 + 0.7;
  }
  else if (player_state_table.experience < 100000) {
    (&creature_pool)[iVar3].tint_r =
         0.9 - 1.0 / ((float)(player_state_table.experience / 1000) + 10.0);
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].tint_g =
         ((float)(iVar4 % 10) * 0.01 + 0.8) -
         1.0 / ((float)(player_state_table.experience / 10000) + 10.0);
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].tint_b =
         (float)(player_state_table.experience + -50000) * 6e-06 + (float)(iVar4 % 10) * 0.01 + 0.7;
  }
  else {
    (&creature_pool)[iVar3].tint_r =
         1.0 - 1.0 / ((float)(player_state_table.experience / 1000) + 10.0);
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].tint_g =
         ((float)(iVar4 % 10) * 0.01 + 0.9) -
         1.0 / ((float)(player_state_table.experience / 10000) + 10.0);
    iVar4 = crt_rand();
    fVar1 = ((float)(iVar4 % 10) * 0.01 + 1.0) -
            (float)(player_state_table.experience + -100000) * 3e-06;
    (&creature_pool)[iVar3].tint_b = fVar1;
    if (fVar1 < 0.5) {
      (&creature_pool)[iVar3].tint_b = 0.5;
    }
  }
  pfVar6 = &(&creature_pool)[iVar3].tint_r;
  fVar1 = (&creature_pool)[iVar3].size;
  (&creature_pool)[iVar3].tint_a = 1.0;
  (&creature_pool)[iVar3].contact_damage = fVar1 * 0.0952381;
  if ((&creature_pool)[iVar3].reward_value == 0.0) {
    iVar4 = crt_rand();
    (&creature_pool)[iVar3].reward_value =
         (&creature_pool)[iVar3].health * 0.4 +
         (&creature_pool)[iVar3].contact_damage * 0.8 +
         (&creature_pool)[iVar3].move_speed * 5.0 + (float)(iVar4 % 10 + 10);
  }
  iVar4 = crt_rand();
  if (iVar4 % 0xb4 < 2) {
    *pfVar6 = 0.9;
    (&creature_pool)[iVar3].health = 65.0;
    (&creature_pool)[iVar3].tint_g = 0.4;
    (&creature_pool)[iVar3].reward_value = 320.0;
    (&creature_pool)[iVar3].tint_b = 0.4;
    (&creature_pool)[iVar3].tint_a = 1.0;
  }
  else {
    iVar4 = crt_rand();
    if (iVar4 % 0xf0 < 2) {
      *pfVar6 = 0.4;
      (&creature_pool)[iVar3].health = 85.0;
      (&creature_pool)[iVar3].tint_g = 0.9;
      (&creature_pool)[iVar3].reward_value = 420.0;
      (&creature_pool)[iVar3].tint_b = 0.4;
      (&creature_pool)[iVar3].tint_a = 1.0;
    }
    else {
      iVar4 = crt_rand();
      if (iVar4 % 0x168 < 2) {
        *pfVar6 = 0.4;
        (&creature_pool)[iVar3].health = 125.0;
        (&creature_pool)[iVar3].tint_g = 0.4;
        (&creature_pool)[iVar3].reward_value = 520.0;
        (&creature_pool)[iVar3].tint_b = 0.9;
        (&creature_pool)[iVar3].tint_a = 1.0;
      }
    }
  }
  iVar4 = crt_rand();
  if (iVar4 % 0x528 < 4) {
    fVar1 = (&creature_pool)[iVar3].health;
    *pfVar6 = 0.84;
    (&creature_pool)[iVar3].health = fVar1 + 230.0;
    (&creature_pool)[iVar3].tint_g = 0.24;
    (&creature_pool)[iVar3].size = 80.0;
    (&creature_pool)[iVar3].tint_b = 0.89;
    (&creature_pool)[iVar3].reward_value = 600.0;
    (&creature_pool)[iVar3].tint_a = 1.0;
  }
  else {
    iVar4 = crt_rand();
    if (iVar4 % 0x654 < 4) {
      fVar1 = (&creature_pool)[iVar3].health;
      *pfVar6 = 0.94;
      (&creature_pool)[iVar3].health = fVar1 + 2230.0;
      (&creature_pool)[iVar3].tint_g = 0.84;
      (&creature_pool)[iVar3].size = 85.0;
      (&creature_pool)[iVar3].tint_b = 0.29;
      (&creature_pool)[iVar3].reward_value = 900.0;
      (&creature_pool)[iVar3].tint_a = 1.0;
    }
  }
  fVar1 = (&creature_pool)[iVar3].reward_value;
  fVar2 = (&creature_pool)[iVar3].health;
  (&creature_pool)[iVar3].state_flag = '\x01';
  (&creature_pool)[iVar3].max_health = fVar2;
  (&creature_pool)[iVar3].reward_value = fVar1 * 0.8;
  if (0.0 <= *pfVar6) {
    if (1.0 < *pfVar6) {
      *pfVar6 = 1.0;
    }
  }
  else {
    *pfVar6 = 0.0;
  }
  if (0.0 <= (&creature_pool)[iVar3].tint_g) {
    if (1.0 < (&creature_pool)[iVar3].tint_g) {
      (&creature_pool)[iVar3].tint_g = 1.0;
    }
  }
  else {
    (&creature_pool)[iVar3].tint_g = 0.0;
  }
  if (0.0 <= (&creature_pool)[iVar3].tint_b) {
    if (1.0 < (&creature_pool)[iVar3].tint_b) {
      (&creature_pool)[iVar3].tint_b = 1.0;
    }
  }
  else {
    (&creature_pool)[iVar3].tint_b = 0.0;
  }
  if ((&creature_pool)[iVar3].tint_a < 0.0) {
    (&creature_pool)[iVar3].tint_a = 0.0;
    return;
  }
  if (1.0 < (&creature_pool)[iVar3].tint_a) {
    (&creature_pool)[iVar3].tint_a = 1.0;
  }
  return;
}



/* creature_render_type @ 00418b60 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* renders active creatures matching type_id using 8x8 atlases and animation strips */

void __cdecl creature_render_type(int type_id)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int frame;
  IGrim2D_vtbl *pIVar4;
  float fVar5;
  float *pfVar6;
  longlong lVar7;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_24;
  float fStack_20;
  
  (*grim_interface_ptr->vtable->grim_bind_texture)((&creature_type_table)[type_id].texture_handle,0)
  ;
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,1.0,1.0);
  fVar5 = (float)type_id;
  if ((config_blob.reserved0[0xe] != '\0') &&
     (iVar2 = perk_count_get(perk_id_monster_vision), iVar2 == 0)) {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,1);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    pfVar6 = &creature_pool.hitbox_size;
    do {
      if ((((creature_t *)(pfVar6 + -4))->active != '\0') && (pfVar6[0x17] == fVar5)) {
        fVar5 = pfVar6[0x1f];
        fStack_38 = pfVar6[0xb];
        fStack_34 = pfVar6[0xc];
        fStack_30 = pfVar6[0xd];
        fStack_2c = pfVar6[0xe] * 0.4;
        if ((((uint)fVar5 & 4) == 0) || (((uint)fVar5 & 0x40) != 0)) {
          if (16.0 <= *pfVar6) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
            if ((((&creature_type_table)[type_id].anim_flags & 1) != 0) && (0xf < iVar2)) {
              iVar2 = 0x1f - iVar2;
            }
          }
          else if (0.0 <= *pfVar6) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
          }
          else {
            iVar2 = (&creature_type_table)[type_id].base_frame + 0xf;
            fStack_2c = *pfVar6 * 0.5 + fStack_2c;
            if (fStack_2c < 0.0) {
              fStack_2c = 0.0;
            }
          }
          if (((uint)fVar5 & 0x10) != 0) {
            iVar2 = iVar2 + 0x20;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(8,iVar2);
        }
        else {
          lVar7 = __ftol();
          uVar3 = (uint)lVar7 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          if (7 < (int)uVar3) {
            uVar3 = 0xf - uVar3;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)
                    (8,(&creature_type_table)[type_id].base_frame + 0x10 + uVar3);
          if ((*pfVar6 < 0.0) && (fStack_2c = *pfVar6 * 0.1 + fStack_2c, fStack_2c < 0.0)) {
            fStack_2c = 0.0;
          }
        }
        fStack_2c = fStack_2c * fStack_20;
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_38);
        (*grim_interface_ptr->vtable->grim_set_rotation)(pfVar6[7] - 1.5707964);
        fVar5 = pfVar6[9] * 0.5 + 0.7;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + pfVar6[1]) - fVar5,(camera_offset_y + pfVar6[2]) - fVar5,
                   pfVar6[9] * 1.07,pfVar6[9] * 1.07);
        fVar5 = fStack_24;
      }
      pfVar6 = pfVar6 + 0x26;
    } while ((int)pfVar6 < 0x4aa348);
    (*grim_interface_ptr->vtable->grim_end_batch)();
  }
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  (*grim_interface_ptr->vtable->grim_begin_batch)();
  if (bonus_energizer_timer <= 0.0) {
    iVar2 = 0x49bfcc;
    do {
      if ((*(char *)(iVar2 + -0x94) != '\0') && (*(float *)(iVar2 + -0x28) == fStack_24)) {
        uVar3 = *(uint *)(iVar2 + -8);
        fStack_38 = *(float *)(iVar2 + -0x58);
        fStack_34 = *(float *)(iVar2 + -0x54);
        fStack_30 = *(float *)(iVar2 + -0x50);
        fStack_2c = *(float *)(iVar2 + -0x4c);
        if (((uVar3 & 4) == 0) || ((uVar3 & 0x40) != 0)) {
          if (16.0 <= *(float *)(iVar2 + -0x84)) {
            lVar7 = __ftol();
            frame = (int)lVar7;
            if ((((&creature_type_table)[type_id].anim_flags & 1) != 0) && (0xf < frame)) {
              frame = 0x1f - frame;
            }
          }
          else if (0.0 <= *(float *)(iVar2 + -0x84)) {
            lVar7 = __ftol();
            frame = (int)lVar7;
          }
          else {
            frame = (&creature_type_table)[type_id].base_frame + 0xf;
            fStack_2c = *(float *)(iVar2 + -0x84) * 0.1 + fStack_2c;
            if (fStack_2c < 0.0) {
              fStack_2c = 0.0;
            }
          }
          if ((uVar3 & 0x10) != 0) {
            frame = frame + 0x20;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(8,frame);
        }
        else {
          lVar7 = __ftol();
          uVar3 = (uint)lVar7 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          if (7 < (int)uVar3) {
            uVar3 = 0xf - uVar3;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)
                    (8,(&creature_type_table)[type_id].base_frame + 0x10 + uVar3);
          if ((*(float *)(iVar2 + -0x84) < 0.0) &&
             (fStack_2c = *(float *)(iVar2 + -0x84) * 0.1 + fStack_2c, fStack_2c < 0.0)) {
            fStack_2c = 0.0;
          }
        }
        fStack_2c = fStack_2c * fStack_20;
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_38);
        (*grim_interface_ptr->vtable->grim_set_rotation)(*(float *)(iVar2 + -0x68) - 1.5707964);
        fVar5 = *(float *)(iVar2 + -0x60) * 0.5;
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + *(float *)(iVar2 + -0x80)) - fVar5,
                   (camera_offset_y + *(float *)(iVar2 + -0x7c)) - fVar5,*(float *)(iVar2 + -0x60),
                   *(float *)(iVar2 + -0x60));
        if ((*(float *)(iVar2 + -0x84) < -10.0) &&
           (*(undefined1 *)(iVar2 + -0x94) = 0, (*(byte *)(iVar2 + -8) & 4) != 0)) {
          (&creature_spawn_slot_table)[*(int *)(iVar2 + -0x1c)].owner = (creature_t *)0x0;
        }
      }
      iVar2 = iVar2 + 0x98;
    } while (iVar2 < 0x4aa3cc);
  }
  else {
    pfVar6 = &creature_pool.max_health;
    do {
      if ((((creature_t *)(pfVar6 + -10))->active != '\0') && (pfVar6[0x11] == fVar5)) {
        if (500.0 <= *pfVar6) {
          fStack_38 = pfVar6[5];
          fStack_34 = pfVar6[6];
          fStack_30 = pfVar6[7];
          fStack_2c = pfVar6[8];
        }
        else {
          fStack_2c = bonus_energizer_timer;
          if (1.0 <= bonus_energizer_timer) {
            fStack_2c = 1.0;
          }
          fVar1 = 1.0 - fStack_2c;
          fStack_38 = fVar1 * pfVar6[5] + fStack_2c * 0.5;
          fStack_34 = fVar1 * pfVar6[6] + fStack_2c * 0.5;
          fStack_30 = fVar1 * pfVar6[7] + fStack_2c;
          fStack_2c = fVar1 * pfVar6[8] + fStack_2c;
        }
        fVar1 = pfVar6[0x19];
        if ((((uint)fVar1 & 4) == 0) || (((uint)fVar1 & 0x40) != 0)) {
          if (16.0 <= pfVar6[-6]) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
            if ((((&creature_type_table)[type_id].anim_flags & 1) != 0) && (0xf < iVar2)) {
              iVar2 = 0x1f - iVar2;
            }
          }
          else if (0.0 <= pfVar6[-6]) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
          }
          else {
            iVar2 = (&creature_type_table)[type_id].base_frame + 0xf;
            fStack_2c = pfVar6[-6] * 0.1 + fStack_2c;
            if (fStack_2c < 0.0) {
              fStack_2c = 0.0;
            }
          }
          if (((uint)fVar1 & 0x10) != 0) {
            iVar2 = iVar2 + 0x20;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)(8,iVar2);
        }
        else {
          lVar7 = __ftol();
          uVar3 = (uint)lVar7 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          if (7 < (int)uVar3) {
            uVar3 = 0xf - uVar3;
          }
          (*grim_interface_ptr->vtable->grim_set_atlas_frame)
                    (8,(&creature_type_table)[type_id].base_frame + 0x10 + uVar3);
          if ((pfVar6[-6] < 0.0) && (fStack_2c = pfVar6[-6] * 0.1 + fStack_2c, fStack_2c < 0.0)) {
            fStack_2c = 0.0;
          }
        }
        fStack_2c = fStack_2c * fStack_20;
        (*grim_interface_ptr->vtable->grim_set_color_ptr)(&fStack_38);
        (*grim_interface_ptr->vtable->grim_set_rotation)(pfVar6[1] - 1.5707964);
        (*grim_interface_ptr->vtable->grim_draw_quad)
                  ((camera_offset_x + pfVar6[-5]) - pfVar6[3] * 0.5,
                   (camera_offset_y + pfVar6[-4]) - pfVar6[3] * 0.5,pfVar6[3],pfVar6[3]);
        if ((pfVar6[-6] < -10.0) &&
           (iVar2 = (int)pfVar6[0x19], ((creature_t *)(pfVar6 + -10))->active = '\0',
           (iVar2 & 4) != 0)) {
          (&creature_spawn_slot_table)[(int)pfVar6[0x14]].owner = (creature_t *)0x0;
        }
      }
      pfVar6 = pfVar6 + 0x26;
    } while ((int)pfVar6 < 0x4aa360);
  }
  (*grim_interface_ptr->vtable->grim_end_batch)();
  if (config_blob.fx_toggle != '\0') {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,2);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    pfVar6 = &creature_pool.hitbox_size;
    do {
      if (((((creature_t *)(pfVar6 + -4))->active != '\0') && (pfVar6[0x17] == fStack_38)) &&
         (0.0 < pfVar6[10])) {
        fVar5 = pfVar6[0x1f];
        if ((((uint)fVar5 & 4) == 0) || (((uint)fVar5 & 0x40) != 0)) {
          if (16.0 <= *pfVar6) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
            if ((((&creature_type_table)[type_id].anim_flags & 1) != 0) && (0xf < iVar2)) {
              iVar2 = 0x1f - iVar2;
            }
            if (((uint)fVar5 & 0x10) != 0) {
              iVar2 = iVar2 + 0x20;
            }
          }
          else if (0.0 <= *pfVar6) {
            lVar7 = __ftol();
            iVar2 = (int)lVar7;
          }
          else {
            iVar2 = (&creature_type_table)[type_id].base_frame + 0xf;
          }
          pIVar4 = grim_interface_ptr->vtable;
        }
        else {
          lVar7 = __ftol();
          uVar3 = (uint)lVar7 & 0x8000000f;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
          }
          if (7 < (int)uVar3) {
            uVar3 = 0xf - uVar3;
          }
          pIVar4 = grim_interface_ptr->vtable;
          iVar2 = (&creature_type_table)[type_id].base_frame + 0x10 + uVar3;
        }
        (*pIVar4->grim_set_atlas_frame)(8,iVar2);
        (*grim_interface_ptr->vtable->grim_set_color_ptr)((float *)&stack0xffffffb4);
        (*grim_interface_ptr->vtable->grim_set_rotation)(pfVar6[7] - 1.5707964);
        fVar1 = (camera_offset_x + pfVar6[1]) - pfVar6[9] * 0.5;
        fVar5 = (camera_offset_y + pfVar6[2]) - pfVar6[9] * 0.5;
        (*grim_interface_ptr->vtable->grim_draw_quad)(fVar1,fVar5,pfVar6[9],pfVar6[9]);
        (*grim_interface_ptr->vtable->grim_draw_quad)(fVar1,fVar5,pfVar6[9],pfVar6[9]);
      }
      pfVar6 = pfVar6 + 0x26;
    } while ((int)pfVar6 < 0x4aa348);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
  }
  return;
}



/* creature_render_all @ 00419680 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* creature render pass: overlays + per-type draws via creature_render_type */

void creature_render_all(void)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fStack_30;
  
  if ((((0.0 < ui_transition_alpha) && (game_state_id != 0x14)) && (game_state_id != 0x16)) &&
     ((game_state_prev != 0x14 && (game_state_prev != 0x16)))) {
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
    effect_select_texture(0x10);
    (*grim_interface_ptr->vtable->grim_set_color)(0.0,0.0,0.0,1.0);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    (*grim_interface_ptr->vtable->grim_begin_batch)();
    pfVar2 = &creature_pool.hitbox_size;
    do {
      if (((creature_t *)(pfVar2 + -4))->active != '\0') {
        iVar1 = perk_count_get(perk_id_monster_vision);
        if (iVar1 != 0) {
          if ((0.0 <= *pfVar2) || (fVar4 = (*pfVar2 + 10.0) * 0.1, 1.0 < fVar4)) {
            fVar4 = 1.0;
          }
          else if (fVar4 < 0.0) {
            fVar4 = 0.0;
          }
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,0.0,fVar4 * fStack_30);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pfVar2[1]) - 45.0,(camera_offset_y + pfVar2[2]) - 45.0,
                     90.0,90.0);
        }
        if (*(uchar *)((int)pfVar2 + -7) != '\0') {
          if (0.0 <= *pfVar2) {
            fVar4 = 1.0;
          }
          else {
            fVar4 = (*pfVar2 + 10.0) * 0.1;
          }
          (*grim_interface_ptr->vtable->grim_set_color)(0.0,0.0,0.0,fVar4 * fStack_30);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pfVar2[1]) - 40.0,(camera_offset_y + pfVar2[2]) - 40.0,
                     80.0,80.0);
        }
        if (((uint)pfVar2[0x1f] & 1) != 0) {
          if (0.0 <= *pfVar2) {
            fVar4 = 1.0;
          }
          else {
            fVar4 = (*pfVar2 + 10.0) * 0.1;
          }
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.0,0.0,fVar4 * fStack_30);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pfVar2[1]) - 30.0,(camera_offset_y + pfVar2[2]) - 30.0,
                     60.0,60.0);
        }
      }
      pfVar2 = pfVar2 + 0x26;
    } while ((int)pfVar2 < 0x4aa348);
    (*grim_interface_ptr->vtable->grim_end_batch)();
    creature_render_type(0);
    fVar4 = fStack_30;
    creature_render_type(3);
    creature_render_type(4);
    fVar3 = 2.8026e-45;
    creature_render_type(2);
    creature_render_type(1);
    if (0.0 < bonus_freeze_timer) {
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5,fVar4);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6,fVar3,fStack_30);
      (*grim_interface_ptr->vtable->grim_bind_texture)(particles_texture,0);
      effect_select_texture(0xe);
      (*grim_interface_ptr->vtable->grim_set_color)(0.0,0.0,0.0,1.0);
      (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
      fVar4 = 1.0;
      if (bonus_freeze_timer < 1.0) {
        if (bonus_freeze_timer <= 1.0) {
          fVar4 = bonus_freeze_timer;
          if (bonus_freeze_timer < 0.0) {
            fVar4 = 0.0;
          }
        }
        else {
          fVar4 = 1.0;
        }
      }
      fVar4 = fVar4 * fVar3 * 0.7;
      (*grim_interface_ptr->vtable->grim_begin_batch)();
      iVar1 = 0;
      pfVar2 = &creature_pool.size;
      do {
        if (((creature_t *)(pfVar2 + -0xd))->active != '\0') {
          (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fVar4);
          (*grim_interface_ptr->vtable->grim_set_rotation)((float)iVar1 * 0.01 + pfVar2[-2]);
          (*grim_interface_ptr->vtable->grim_draw_quad)
                    ((camera_offset_x + pfVar2[-8]) - *pfVar2 * 0.5,
                     (camera_offset_y + pfVar2[-7]) - *pfVar2 * 0.5,*pfVar2,*pfVar2);
        }
        pfVar2 = pfVar2 + 0x26;
        iVar1 = iVar1 + 1;
      } while ((int)pfVar2 < 0x4aa36c);
      (*grim_interface_ptr->vtable->grim_end_batch)();
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x13,5);
      (*grim_interface_ptr->vtable->grim_set_config_var)(0x14,6);
    }
    (*grim_interface_ptr->vtable->grim_set_color)(0.0,1.0,1.0,1.0);
  }
  return;
}



/* creature_handle_death @ 0041e910 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* death handler: bonus spawns, split-on-death, score, and cleanup */

void __cdecl creature_handle_death(int creature_id,bool keep_corpse)

{
  float *pos;
  creature_t *pcVar1;
  uchar uVar2;
  uchar uVar3;
  uchar uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  creature_t *pcVar8;
  creature_t *pcVar9;
  longlong lVar10;
  
  pcVar1 = &creature_pool + creature_id;
  if (((&creature_pool)[creature_id].flags & 0x400U) != 0) {
    bonus_spawn_at(&(&creature_pool)[creature_id].pos_x,
                   (int)(short)(&creature_pool)[creature_id].link_index,
                   (int)*(short *)((int)&(&creature_pool)[creature_id].link_index + 2));
  }
  if (survival_recent_death_count < 6) {
    if (survival_recent_death_count < 3) {
      (&survival_recent_death_pos)[survival_recent_death_count].x =
           (&creature_pool)[creature_id].pos_x;
      (&survival_recent_death_pos)[survival_recent_death_count].y =
           (&creature_pool)[creature_id].pos_y;
    }
    survival_recent_death_count = survival_recent_death_count + 1;
    if (survival_recent_death_count == 3) {
      survival_reward_fire_seen = 0;
      survival_reward_handout_enabled = 0;
    }
  }
  if (pcVar1->active != '\0') {
    if (((&creature_pool)[creature_id].flags & 4) != 0) {
      (&creature_spawn_slot_table)[(&creature_pool)[creature_id].link_index].owner =
           (creature_t *)0x0;
    }
    if ((((&creature_pool)[creature_id].flags & 8) != 0) &&
       (35.0 < (&creature_pool)[creature_id].size)) {
      iVar5 = creature_alloc_slot();
      pcVar8 = pcVar1;
      pcVar9 = &creature_pool + iVar5;
      for (iVar7 = 0x26; iVar7 != 0; iVar7 = iVar7 + -1) {
        uVar2 = pcVar8->_pad0[0];
        uVar3 = pcVar8->_pad0[1];
        uVar4 = pcVar8->_pad0[2];
        pcVar9->active = pcVar8->active;
        pcVar9->_pad0[0] = uVar2;
        pcVar9->_pad0[1] = uVar3;
        pcVar9->_pad0[2] = uVar4;
        pcVar8 = (creature_t *)&pcVar8->phase_seed;
        pcVar9 = (creature_t *)&pcVar9->phase_seed;
      }
      uVar6 = crt_rand();
      (&creature_pool)[iVar5].phase_seed = (float)(uVar6 & 0xff);
      (&creature_pool)[iVar5].heading = (&creature_pool)[creature_id].heading - 1.5707964;
      (&creature_pool)[iVar5].health = (&creature_pool)[creature_id].max_health * 0.25;
      (&creature_pool)[iVar5].reward_value = (&creature_pool)[iVar5].reward_value * 0.6666667;
      (&creature_pool)[iVar5].size = (&creature_pool)[iVar5].size - 8.0;
      (&creature_pool)[iVar5].move_speed = (&creature_pool)[iVar5].move_speed + 0.1;
      (&creature_pool)[iVar5].contact_damage = (&creature_pool)[iVar5].contact_damage * 0.7;
      (&creature_pool)[iVar5].hitbox_size = 16.0;
      iVar5 = creature_alloc_slot();
      pcVar8 = pcVar1;
      pcVar9 = &creature_pool + iVar5;
      for (iVar7 = 0x26; iVar7 != 0; iVar7 = iVar7 + -1) {
        uVar2 = pcVar8->_pad0[0];
        uVar3 = pcVar8->_pad0[1];
        uVar4 = pcVar8->_pad0[2];
        pcVar9->active = pcVar8->active;
        pcVar9->_pad0[0] = uVar2;
        pcVar9->_pad0[1] = uVar3;
        pcVar9->_pad0[2] = uVar4;
        pcVar8 = (creature_t *)&pcVar8->phase_seed;
        pcVar9 = (creature_t *)&pcVar9->phase_seed;
      }
      uVar6 = crt_rand();
      (&creature_pool)[iVar5].phase_seed = (float)(uVar6 & 0xff);
      (&creature_pool)[iVar5].heading = (&creature_pool)[creature_id].heading + 1.5707964;
      (&creature_pool)[iVar5].health = (&creature_pool)[creature_id].max_health * 0.25;
      (&creature_pool)[iVar5].size = (&creature_pool)[iVar5].size - 8.0;
      (&creature_pool)[iVar5].move_speed = (&creature_pool)[iVar5].move_speed + 0.1;
      (&creature_pool)[iVar5].reward_value = (&creature_pool)[iVar5].reward_value * 0.6666667;
      (&creature_pool)[iVar5].hitbox_size = 16.0;
      (&creature_pool)[iVar5].contact_damage = (&creature_pool)[iVar5].contact_damage * 0.7;
      effect_spawn_burst(&(&creature_pool)[creature_id].pos_x,8);
    }
    if (keep_corpse) {
      (&creature_pool)[creature_id].hitbox_size =
           (&creature_pool)[creature_id].hitbox_size - frame_dt;
    }
    else {
      pcVar1->active = '\0';
    }
    iVar5 = perk_id_bloody_mess_quick_learner;
    if (player_state_table.perk_counts[perk_id_bloody_mess_quick_learner] < 1) {
      lVar10 = __ftol();
      player_state_table.experience = (int)lVar10;
    }
    else {
      lVar10 = __ftol();
      player_state_table.experience = player_state_table.experience + (int)lVar10;
    }
    if (0.0 < bonus_double_xp_timer) {
      if (player_state_table.perk_counts[iVar5] < 1) {
        lVar10 = __ftol();
        player_state_table.experience = (int)lVar10;
      }
      else {
        lVar10 = __ftol();
        player_state_table.experience = player_state_table.experience + (int)lVar10;
      }
    }
    if (bonus_spawn_guard == '\0') {
      bonus_try_spawn_on_kill(&(&creature_pool)[creature_id].pos_x);
    }
    if (0.0 < bonus_freeze_timer) {
      pos = &(&creature_pool)[creature_id].pos_x;
      iVar5 = 8;
      do {
        iVar7 = crt_rand();
        effect_spawn_freeze_shard(pos,(float)(iVar7 % 0x264) * 0.01);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar5 = crt_rand();
      effect_spawn_freeze_shatter(pos,(float)(iVar5 % 0x264) * 0.01);
      highscore_active_record.creature_kill_count = highscore_active_record.creature_kill_count + 1;
      pcVar1->active = '\0';
      fx_queue_add_random(pos);
    }
  }
  return;
}



/* creature_find_nearest @ 00420040 */

/* returns nearest creature index; uses hitbox-size sentinel when exclude_id == -1 */

int __cdecl creature_find_nearest(float *pos,int exclude_id,float min_dist)

{
  float fVar1;
  float fVar2;
  float fVar3;
  creature_t *pcVar4;
  int iVar5;
  int iVar6;
  
  fVar1 = 1e+06;
  iVar6 = 0;
  if (exclude_id == -1) {
    iVar5 = 0;
    pcVar4 = &creature_pool;
    do {
      if (((pcVar4->active != '\0') && (pcVar4->hitbox_size == 16.0)) &&
         (fVar2 = *pos - pcVar4->pos_x, fVar3 = pos[1] - pcVar4->pos_y,
         fVar2 = SQRT(fVar3 * fVar3 + fVar2 * fVar2), fVar2 < fVar1)) {
        iVar6 = iVar5;
        fVar1 = fVar2;
      }
      pcVar4 = pcVar4 + 1;
      iVar5 = iVar5 + 1;
    } while ((int)pcVar4 < 0x4aa338);
    return iVar6;
  }
  iVar5 = 0;
  pcVar4 = &creature_pool;
  do {
    if ((((pcVar4->active != '\0') && (iVar5 != exclude_id)) &&
        (fVar2 = *pos - pcVar4->pos_x, fVar3 = pos[1] - pcVar4->pos_y,
        fVar2 = SQRT(fVar2 * fVar2 + fVar3 * fVar3), min_dist < fVar2)) && (fVar2 < fVar1)) {
      iVar6 = iVar5;
      fVar1 = fVar2;
    }
    pcVar4 = pcVar4 + 1;
    iVar5 = iVar5 + 1;
  } while ((int)pcVar4 < 0x4aa338);
  return iVar6;
}



/* creatures_apply_radius_damage @ 00420600 */

/* applies damage to creatures within radius using creature_apply_damage */

void __cdecl creatures_apply_radius_damage(float *pos,float radius,float damage,int damage_type)

{
  float fVar1;
  float fVar2;
  creature_t *pcVar3;
  int creature_id;
  float local_8 [2];
  
  local_8[0] = 0.0;
  local_8[1] = 0.0;
  creature_id = 0;
  pcVar3 = &creature_pool;
  do {
    if (((pcVar3->active != '\0') &&
        (fVar1 = pcVar3->pos_x - *pos, fVar2 = pcVar3->pos_y - pos[1],
        SQRT(fVar2 * fVar2 + fVar1 * fVar1) - radius < pcVar3->size * 0.14285715 + 3.0)) &&
       (5.0 < pcVar3->hitbox_size)) {
      creature_apply_damage(creature_id,damage,damage_type,local_8);
    }
    pcVar3 = pcVar3 + 1;
    creature_id = creature_id + 1;
  } while ((int)pcVar3 < 0x4aa338);
  return;
}



/* creature_find_in_radius @ 004206a0 */

/* returns the first creature index in range, or -1 */

int __cdecl creature_find_in_radius(float *pos,float radius,int start_index)

{
  float fVar1;
  float fVar2;
  creature_t *pcVar3;
  
  if (start_index < 0x180) {
    pcVar3 = &creature_pool + start_index;
    do {
      if (pcVar3->active != '\0') {
        fVar1 = pcVar3->pos_x - *pos;
        fVar2 = pcVar3->pos_y - pos[1];
        if (SQRT(fVar2 * fVar2 + fVar1 * fVar1) - radius < pcVar3->size * 0.14285715 + 3.0) {
          if (5.0 < pcVar3->hitbox_size) {
            return start_index;
          }
        }
      }
      pcVar3 = pcVar3 + 1;
      start_index = start_index + 1;
    } while ((int)pcVar3 < 0x4aa338);
  }
  return -1;
}



/* creature_apply_damage @ 004207c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* applies damage + impulse, handles death side effects; returns 1 when killed */

int __cdecl creature_apply_damage(int creature_id,float damage,int damage_type,float *impulse)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  
  (&creature_pool)[creature_id].hit_flash_timer = 0.2;
  if (damage_type == 1) {
    iVar2 = perk_count_get(perk_id_uranium_filled_bullets);
    if (iVar2 != 0) {
      damage = damage + damage;
    }
    iVar2 = perk_count_get(perk_id_living_fortress);
    if ((iVar2 != 0) && (0 < (int)config_blob.reserved0._20_4_)) {
      pfVar5 = &player_state_table.living_fortress_timer;
      iVar2 = config_blob.reserved0._20_4_;
      do {
        if (0.0 < pfVar5[-0x20]) {
          damage = (*pfVar5 * 0.05 + 1.0) * damage;
        }
        pfVar5 = pfVar5 + 0xd8;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar2 = perk_count_get(perk_id_barrel_greaser);
    if (iVar2 != 0) {
      damage = damage * 1.4;
    }
    iVar2 = perk_count_get(perk_id_doctor);
    if (iVar2 != 0) {
      damage = damage * 1.2;
    }
    if (((&creature_pool)[creature_id].flags & 4) == 0) {
      uVar3 = crt_rand();
      fVar1 = ((float)(int)((uVar3 & 0x7f) - 0x40) * 0.002) /
              ((&creature_pool)[creature_id].size * 0.025);
      if (1.5707964 < fVar1) {
        fVar1 = 1.5707964;
      }
      (&creature_pool)[creature_id].heading = fVar1 + (&creature_pool)[creature_id].heading;
    }
  }
  else if ((damage_type == 7) && (iVar2 = perk_count_get(perk_id_ion_gun_master), iVar2 != 0)) {
    damage = damage * 1.2;
  }
  if ((&creature_pool)[creature_id].health <= 0.0) {
    (&creature_pool)[creature_id].hitbox_size =
         (&creature_pool)[creature_id].hitbox_size - frame_dt * 15.0;
  }
  else {
    if ((damage_type == 4) && (iVar2 = perk_count_get(perk_id_pyromaniac), iVar2 != 0)) {
      damage = damage * 1.5;
      crt_rand();
    }
    (&creature_pool)[creature_id].health = (&creature_pool)[creature_id].health - damage;
    (&creature_pool)[creature_id].vel_x = (&creature_pool)[creature_id].vel_x - *impulse;
    (&creature_pool)[creature_id].vel_y = (&creature_pool)[creature_id].vel_y - impulse[1];
    if ((&creature_pool)[creature_id].health <= 0.0) {
      (&creature_pool)[creature_id].hitbox_size =
           (&creature_pool)[creature_id].hitbox_size - frame_dt;
      creature_handle_death(creature_id,true);
      fVar1 = impulse[1];
      (&creature_pool)[creature_id].vel_x =
           (&creature_pool)[creature_id].vel_x - (*impulse + *impulse);
      (&creature_pool)[creature_id].vel_y = (&creature_pool)[creature_id].vel_y - (fVar1 + fVar1);
      if (((&creature_pool)[creature_id].flags & 0x10) == 0) {
        uVar3 = crt_rand();
        uVar3 = uVar3 & 0x80000003;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
        }
        sfx_play_panned((float)(&creature_type_table)[(&creature_pool)[creature_id].type_id].
                               sfx_bank_a[uVar3]);
      }
      else {
        effect_template_color_r = 0x3f4ccccd;
        effect_template_flags = 0x1d;
        effect_template_color_g = 0x3f4ccccd;
        effect_template_color_b = 0x3e99999a;
        effect_template_color_a = 0x3f000000;
        effect_template_lifetime = 0x3f333333;
        effect_template_half_width = 0x42100000;
        effect_template_half_height = 0x42100000;
        iVar2 = 5;
        do {
          uVar3 = crt_rand();
          effect_template_rotation = (float)(uVar3 & 0x7f) * 0.049087387;
          uVar3 = crt_rand();
          effect_template_vel_x = (float)(int)((uVar3 & 0x7f) - 0x40);
          uVar3 = crt_rand();
          effect_template_vel_y = (float)(int)((uVar3 & 0x7f) - 0x40);
          iVar4 = crt_rand();
          effect_template_scale_step = (float)(iVar4 % 0x8c) * 0.01 + 0.3;
          effect_spawn(0,&(&creature_pool)[creature_id].pos_x);
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
    }
  }
  if (0.0 < (&creature_pool)[creature_id].health) {
    return 0;
  }
  return 1;
}



/* creature_check_collision_radius @ 00425d80 */

int __cdecl creature_check_collision_radius(int param_1)

{
  float fVar1;
  float fVar2;
  creature_t *pcVar3;
  int iVar4;
  
  iVar4 = 0;
  pcVar3 = &creature_pool;
  do {
    if (pcVar3->active != '\0') {
      fVar1 = pcVar3->pos_x - (&creature_pool)[param_1].pos_x;
      fVar2 = pcVar3->pos_y - (&creature_pool)[param_1].pos_y;
      if (SQRT(fVar2 * fVar2 + fVar1 * fVar1) < 45.0) {
        if (((&creature_pool)[iVar4].collision_flag != '\0') &&
           ((&creature_pool)[param_1].health < 150.0)) {
          (&creature_pool)[param_1].collision_flag = '\x01';
        }
        if (((&creature_pool)[param_1].collision_flag != '\0') &&
           ((&creature_pool)[iVar4].health < 150.0)) {
          (&creature_pool)[iVar4].collision_flag = '\x01';
        }
        return iVar4;
      }
    }
    pcVar3 = pcVar3 + 1;
    iVar4 = iVar4 + 1;
  } while ((int)pcVar3 < 0x4aa338);
  return 0;
}



/* creature_update_all @ 00426220 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* primary creature update loop: AI, movement, attacks, and animation phase */

void creature_update_all(void)

{
  float *pfVar1;
  uchar *puVar2;
  float *pfVar3;
  int *piVar4;
  int iVar5;
  float fVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  char cVar10;
  float10 fVar11;
  float10 fVar12;
  longlong lVar13;
  float *pfVar14;
  float fVar15;
  float *pfVar16;
  float fVar17;
  int local_7c;
  float local_78;
  float local_70;
  float local_6c;
  float local_60;
  float local_50 [12];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_8;
  
  creature_update_tick = creature_update_tick + 1;
  creature_active_count = 0;
  local_7c = 0;
  do {
    if ((&creature_pool)[local_7c].active != '\0') {
      creature_active_count = creature_active_count + 1;
      if (0.0 < (&creature_pool)[local_7c].hit_flash_timer) {
        (&creature_pool)[local_7c].hit_flash_timer =
             (&creature_pool)[local_7c].hit_flash_timer - frame_dt;
      }
      if (bonus_freeze_timer <= 0.0) {
        pfVar14 = &(&creature_pool)[local_7c].health;
        if (((&creature_pool)[local_7c].health <= 0.0) &&
           ((&creature_pool)[local_7c].hitbox_size == 16.0)) {
          (&creature_pool)[local_7c].hitbox_size = (&creature_pool)[local_7c].hitbox_size - frame_dt
          ;
        }
        if (((&creature_pool)[local_7c].flags & 2U) == 0) {
          if (((&creature_pool)[local_7c].flags & 1U) != 0) {
            fVar17 = frame_dt * 60.0;
            pfVar16 = local_50 + 2;
            local_50[2] = 0.0;
            local_50[3] = 0.0;
            goto LAB_0042634c;
          }
        }
        else {
          fVar17 = frame_dt * 180.0;
          pfVar16 = local_50;
          local_50[0] = 0.0;
          local_50[1] = 0.0;
LAB_0042634c:
          creature_apply_damage(local_7c,fVar17,0,pfVar16);
        }
        if (((&creature_pool)[local_7c].flags & 0x80) != 0) {
          iVar7 = (&creature_pool)[local_7c].link_index;
          if (iVar7 < 0) {
            iVar7 = iVar7 + frame_dt_ms;
            (&creature_pool)[local_7c].link_index = iVar7;
            if (-1 < iVar7) {
              uVar8 = crt_rand();
              (&creature_pool)[local_7c].ai_mode = 7;
              (&creature_pool)[local_7c].link_index = (uVar8 & 0x1ff) + 500;
            }
          }
          else {
            iVar7 = iVar7 - frame_dt_ms;
            (&creature_pool)[local_7c].link_index = iVar7;
            if (iVar7 < 1) {
              uVar8 = crt_rand();
              (&creature_pool)[local_7c].link_index = -700 - (uVar8 & 0x3ff);
            }
          }
        }
        if ((*pfVar14 <= 0.0) && ((&creature_pool)[local_7c].hitbox_size == 16.0)) {
          (&creature_pool)[local_7c].hitbox_size = (&creature_pool)[local_7c].hitbox_size - frame_dt
          ;
        }
        cVar10 = (char)(&creature_pool)[local_7c].target_player;
        iVar7 = (int)cVar10;
        pfVar16 = &(&creature_pool)[local_7c].pos_x;
        iVar9 = iVar7 * 0x360;
        fVar17 = (&player_state_table)[iVar7].pos_x - *pfVar16;
        fVar15 = (&player_state_table)[iVar7].pos_y - (&creature_pool)[local_7c].pos_y;
        local_78 = SQRT(fVar15 * fVar15 + fVar17 * fVar17);
        if (creature_update_tick % 0x46 != 0) {
          if (config_blob.reserved0._20_4_ == 2) {
            if ((0.0 < (float)(&player2_health)[iVar7 * -0xd8]) &&
               (fVar17 = (float)(&player2_pos_y)[iVar7 * -0xd8] - (&creature_pool)[local_7c].pos_y,
               local_6c = SQRT(fVar17 * fVar17 +
                               ((float)(&player2_pos_x)[iVar7 * -0xd8] - *pfVar16) *
                               ((float)(&player2_pos_x)[iVar7 * -0xd8] - *pfVar16)),
               local_6c < local_78)) {
              *(char *)&(&creature_pool)[local_7c].target_player = '\x01' - cVar10;
              local_78 = local_6c;
            }
          }
          else {
            fVar17 = player_state_table.pos_y - (&creature_pool)[local_7c].pos_y;
            local_6c = SQRT(fVar17 * fVar17 +
                            (player_state_table.pos_x - *pfVar16) *
                            (player_state_table.pos_x - *pfVar16));
          }
          cVar10 = (char)(&creature_pool)[local_7c].target_player;
          iVar7 = (int)cVar10;
          iVar9 = iVar7 * 0x360;
          fVar17 = player_state_table.pos_x -
                   (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_x;
          fVar15 = player_state_table.pos_y -
                   (&creature_pool)[(&player_state_table)[iVar7].auto_target].pos_y;
          if (local_6c < SQRT(fVar15 * fVar15 + fVar17 * fVar17)) {
            (&player_state_table)[iVar7].auto_target = local_7c;
          }
        }
        if (*(float *)(player_state_table._pad0 + iVar9 + -0x14) <= 0.0) {
          *(char *)&(&creature_pool)[local_7c].target_player = '\x01' - cVar10;
        }
        pfVar1 = &(&creature_pool)[local_7c].hitbox_size;
        if ((&creature_pool)[local_7c].hitbox_size == 16.0) {
          puVar2 = &(&creature_pool)[local_7c].collision_flag;
          if ((&creature_pool)[local_7c].collision_flag != '\0') {
            fVar17 = (&creature_pool)[local_7c].collision_timer - frame_dt;
            (&creature_pool)[local_7c].collision_timer = fVar17;
            if (fVar17 < 0.0) {
              (&creature_pool)[local_7c].state_flag = '\x01';
              (&creature_pool)[local_7c].collision_timer = fVar17 + 0.5;
              fVar17 = *pfVar14;
              *pfVar14 = fVar17 - 15.0;
              if (fVar17 - 15.0 < 0.0) {
                plaguebearer_infection_count = plaguebearer_infection_count + 1;
                creature_handle_death(local_7c,true);
                uVar8 = crt_rand();
                uVar8 = uVar8 & 0x80000001;
                if ((int)uVar8 < 0) {
                  uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
                }
                sfx_play_panned((float)(&creature_type_table)[(&creature_pool)[local_7c].type_id].
                                       sfx_bank_b[uVar8]);
              }
              fx_queue_add_random(pfVar16);
            }
          }
          iVar7 = player_state_table.evil_eyes_target_creature;
          fVar17 = (&creature_pool)[local_7c].phase_seed;
          *(undefined1 *)&(&creature_pool)[local_7c].force_target = 0;
          local_70 = 1.0;
          fVar17 = (float)(int)fVar17 * 3.7 * 3.1415927;
          if (local_7c != iVar7) {
            iVar7 = (&creature_pool)[local_7c].ai_mode;
            if (iVar7 == 0) {
              iVar7 = (int)(char)(&creature_pool)[local_7c].target_player;
              if (800.0 < local_78) {
LAB_0042676e:
                fVar15 = (&player_state_table)[iVar7].pos_y;
                (&creature_pool)[local_7c].target_x = (&player_state_table)[iVar7].pos_x;
                (&creature_pool)[local_7c].target_y = fVar15;
              }
              else {
                fVar11 = (float10)fcos((float10)fVar17);
                (&creature_pool)[local_7c].target_x =
                     (float)(fVar11 * (float10)local_78 * (float10)0.85 +
                            (float10)(&player_state_table)[iVar7].pos_x);
                fVar11 = (float10)fsin((float10)fVar17);
                (&creature_pool)[local_7c].target_y =
                     (float)(fVar11 * (float10)local_78 * (float10)0.85 +
                            (float10)(&player_state_table)[iVar7].pos_y);
              }
            }
            else if (iVar7 == 8) {
              fVar11 = (float10)fcos((float10)fVar17);
              cVar10 = (char)(&creature_pool)[local_7c].target_player;
              (&creature_pool)[local_7c].target_x =
                   (float)(fVar11 * (float10)local_78 * (float10)0.9 +
                          (float10)(&player_state_table)[cVar10].pos_x);
              fVar11 = (float10)fsin((float10)fVar17);
              (&creature_pool)[local_7c].target_y =
                   (float)(fVar11 * (float10)local_78 * (float10)0.9 +
                          (float10)(&player_state_table)[cVar10].pos_y);
            }
            else if (iVar7 == 1) {
              iVar7 = (int)(char)(&creature_pool)[local_7c].target_player;
              if (800.0 < local_78) goto LAB_0042676e;
              fVar11 = (float10)fcos((float10)fVar17);
              (&creature_pool)[local_7c].target_x =
                   (float)(fVar11 * (float10)local_78 * (float10)0.55 +
                          (float10)(&player_state_table)[iVar7].pos_x);
              fVar11 = (float10)fsin((float10)fVar17);
              (&creature_pool)[local_7c].target_y =
                   (float)(fVar11 * (float10)local_78 * (float10)0.55 +
                          (float10)(&player_state_table)[iVar7].pos_y);
            }
            else if (iVar7 == 3) {
              iVar7 = (&creature_pool)[local_7c].link_index;
              if ((&creature_pool)[iVar7].health <= 0.0) {
                (&creature_pool)[local_7c].ai_mode = 0;
              }
              else {
                (&creature_pool)[local_7c].target_x =
                     (&creature_pool)[iVar7].pos_x + (&creature_pool)[local_7c].target_offset_x;
                (&creature_pool)[local_7c].target_y =
                     (&creature_pool)[iVar7].pos_y + (&creature_pool)[local_7c].target_offset_y;
              }
            }
            else if (iVar7 == 5) {
              iVar7 = (&creature_pool)[local_7c].link_index;
              if ((&creature_pool)[iVar7].health <= 0.0) {
                (&creature_pool)[local_7c].ai_mode = 0;
                local_50[4] = 0.0;
                local_50[5] = 0.0;
                creature_apply_damage(local_7c,1000.0,1,local_50 + 4);
              }
              else {
                (&creature_pool)[local_7c].target_x =
                     (&creature_pool)[iVar7].pos_x + (&creature_pool)[local_7c].target_offset_x;
                (&creature_pool)[local_7c].target_y =
                     (&creature_pool)[iVar7].pos_y + (&creature_pool)[local_7c].target_offset_y;
                fVar15 = (&creature_pool)[local_7c].target_x - *pfVar16;
                fVar6 = (&creature_pool)[local_7c].target_y - (&creature_pool)[local_7c].pos_y;
                fVar15 = SQRT(fVar15 * fVar15 + fVar6 * fVar6);
                if (fVar15 <= 64.0) {
                  local_70 = fVar15 * 0.015625;
                }
              }
            }
            iVar7 = (&creature_pool)[local_7c].ai_mode;
            if (iVar7 == 4) {
              if ((&creature_pool)[(&creature_pool)[local_7c].link_index].health <= 0.0) {
                (&creature_pool)[local_7c].ai_mode = 0;
                local_50[6] = 0.0;
                local_50[7] = 0.0;
                creature_apply_damage(local_7c,1000.0,1,local_50 + 6);
              }
              else {
                cVar10 = (char)(&creature_pool)[local_7c].target_player;
                if (local_78 <= 800.0) {
                  fVar11 = (float10)fcos((float10)fVar17);
                  (&creature_pool)[local_7c].target_x =
                       (float)(fVar11 * (float10)local_78 * (float10)0.85 +
                              (float10)(&player_state_table)[cVar10].pos_x);
                  fVar11 = (float10)fsin((float10)fVar17);
                  (&creature_pool)[local_7c].target_y =
                       (float)(fVar11 * (float10)local_78 * (float10)0.85 +
                              (float10)(&player_state_table)[cVar10].pos_y);
                }
                else {
                  fVar17 = (&player_state_table)[cVar10].pos_y;
                  (&creature_pool)[local_7c].target_x = (&player_state_table)[cVar10].pos_x;
                  (&creature_pool)[local_7c].target_y = fVar17;
                }
              }
            }
            else if (iVar7 == 7) {
              uVar8 = (&creature_pool)[local_7c].flags & 0x80;
              if ((uVar8 == 0) || ((&creature_pool)[local_7c].link_index < 1)) {
                if (((&creature_pool)[local_7c].orbit_radius.radius <= 0.0) || (uVar8 != 0)) {
LAB_00426ac8:
                  (&creature_pool)[local_7c].ai_mode = 0;
                }
                else {
                  fVar15 = (&creature_pool)[local_7c].orbit_radius.radius - frame_dt;
                  fVar17 = (&creature_pool)[local_7c].pos_y;
                  (&creature_pool)[local_7c].target_x = *pfVar16;
                  (&creature_pool)[local_7c].target_y = fVar17;
                  (&creature_pool)[local_7c].orbit_radius.radius = fVar15;
                }
              }
              else {
                fVar17 = (&creature_pool)[local_7c].pos_y;
                (&creature_pool)[local_7c].target_x = *pfVar16;
                (&creature_pool)[local_7c].target_y = fVar17;
              }
            }
            else if (iVar7 == 6) {
              iVar7 = (&creature_pool)[local_7c].link_index;
              if ((&creature_pool)[iVar7].health <= 0.0) goto LAB_00426ac8;
              fVar11 = (float10)(&creature_pool)[local_7c].orbit_angle +
                       (float10)(&creature_pool)[local_7c].heading;
              fVar12 = (float10)fcos(fVar11);
              (&creature_pool)[local_7c].target_x =
                   (float)(fVar12 * (float10)(&creature_pool)[local_7c].orbit_radius.radius +
                          (float10)(&creature_pool)[iVar7].pos_x);
              fVar11 = (float10)fsin(fVar11);
              (&creature_pool)[local_7c].target_y =
                   (float)(fVar11 * (float10)(&creature_pool)[local_7c].orbit_radius.radius +
                          (float10)(&creature_pool)[iVar7].pos_y);
            }
            fVar17 = (&creature_pool)[local_7c].target_x - *pfVar16;
            fVar15 = (&creature_pool)[local_7c].target_y - (&creature_pool)[local_7c].pos_y;
            if (SQRT(fVar17 * fVar17 + fVar15 * fVar15) < 40.0) {
              *(undefined1 *)&(&creature_pool)[local_7c].force_target = 1;
            }
            fVar17 = (&creature_pool)[local_7c].target_x - *pfVar16;
            fVar15 = (&creature_pool)[local_7c].target_y - (&creature_pool)[local_7c].pos_y;
            if (400.0 < SQRT(fVar17 * fVar17 + fVar15 * fVar15)) {
              *(undefined1 *)&(&creature_pool)[local_7c].force_target = 1;
            }
            if (((char)(&creature_pool)[local_7c].force_target != '\0') ||
               ((&creature_pool)[local_7c].ai_mode == 2)) {
              cVar10 = (char)(&creature_pool)[local_7c].target_player;
              (&creature_pool)[local_7c].target_x = (&player_state_table)[cVar10].pos_x;
              (&creature_pool)[local_7c].target_y = (&player_state_table)[cVar10].pos_y;
            }
            fVar11 = (float10)fpatan((float10)(&creature_pool)[local_7c].target_y -
                                     (float10)(&creature_pool)[local_7c].pos_y,
                                     (float10)(&creature_pool)[local_7c].target_x -
                                     (float10)*pfVar16);
            (&creature_pool)[local_7c].target_heading = (float)(fVar11 + (float10)1.5707964);
            if (((0.0 < bonus_energizer_timer) && ((&creature_pool)[local_7c].max_health < 500.0))
               || (*puVar2 != '\0')) {
              (&creature_pool)[local_7c].target_heading =
                   (float)(fVar11 + (float10)1.5707964 + (float10)3.1415927);
            }
            uVar8 = (&creature_pool)[local_7c].flags;
            if ((uVar8 & 4) == 0) {
              if ((&creature_pool)[local_7c].ai_mode != 7) {
                angle_approach(&(&creature_pool)[local_7c].heading,
                               (&creature_pool)[local_7c].target_heading,
                               (&creature_pool)[local_7c].move_speed * 0.33333334 * 4.0);
                fVar11 = (float10)(&creature_pool)[local_7c].heading - (float10)1.5707964;
                fVar12 = (float10)fcos(fVar11);
                (&creature_pool)[local_7c].vel_x =
                     (float)(fVar12 * (float10)frame_dt * (float10)local_70 *
                             (float10)(&creature_pool)[local_7c].move_speed * (float10)30.0);
                fVar11 = (float10)fsin(fVar11);
                (&creature_pool)[local_7c].vel_y =
                     (float)(fVar11 * (float10)frame_dt * (float10)local_70 *
                             (float10)(&creature_pool)[local_7c].move_speed * (float10)30.0);
                vec2_add_inplace(local_7c,pfVar16,&(&creature_pool)[local_7c].vel_x);
              }
            }
            else {
              if (*pfVar16 < (&creature_pool)[local_7c].size) {
                *pfVar16 = (&creature_pool)[local_7c].size;
              }
              if ((&creature_pool)[local_7c].pos_y < (&creature_pool)[local_7c].size) {
                (&creature_pool)[local_7c].pos_y = (&creature_pool)[local_7c].size;
              }
              fVar17 = 1024.0 - (&creature_pool)[local_7c].size;
              if (fVar17 < *pfVar16) {
                *pfVar16 = fVar17;
              }
              if (fVar17 < (&creature_pool)[local_7c].pos_y) {
                (&creature_pool)[local_7c].pos_y = fVar17;
              }
              if ((uVar8 & 0x40) == 0) {
                (&creature_pool)[local_7c].vel_y = 0.0;
                (&creature_pool)[local_7c].vel_x = 0.0;
              }
              else {
                angle_approach(&(&creature_pool)[local_7c].heading,
                               (&creature_pool)[local_7c].target_heading,
                               (&creature_pool)[local_7c].move_speed * 0.33333334 * 4.0);
                fVar11 = (float10)(&creature_pool)[local_7c].heading - (float10)1.5707964;
                fVar12 = (float10)fcos(fVar11);
                (&creature_pool)[local_7c].vel_x =
                     (float)(fVar12 * (float10)frame_dt * (float10)local_70 *
                             (float10)(&creature_pool)[local_7c].move_speed * (float10)30.0);
                fVar11 = (float10)fsin(fVar11);
                (&creature_pool)[local_7c].vel_y =
                     (float)(fVar11 * (float10)frame_dt * (float10)local_70 *
                             (float10)(&creature_pool)[local_7c].move_speed * (float10)30.0);
                vec2_add_inplace(local_7c,pfVar16,&(&creature_pool)[local_7c].vel_x);
              }
              iVar7 = (&creature_pool)[local_7c].link_index;
              fVar17 = (&creature_spawn_slot_table)[iVar7].timer_s - frame_dt;
              (&creature_spawn_slot_table)[iVar7].timer_s = fVar17;
              if (fVar17 < 0.0) {
                iVar9 = (&creature_spawn_slot_table)[iVar7].count;
                iVar5 = (&creature_spawn_slot_table)[iVar7].limit;
                (&creature_spawn_slot_table)[iVar7].timer_s =
                     fVar17 + (&creature_spawn_slot_table)[iVar7].interval_s;
                if (iVar9 < iVar5) {
                  (&creature_spawn_slot_table)[iVar7].count = iVar9 + 1;
                  creature_spawn_template
                            ((&creature_spawn_slot_table)[iVar7].template_id,pfVar16,-100.0);
                }
              }
            }
            iVar7 = perk_count_get(perk_id_plaguebearer);
            if ((iVar7 != 0) && (plaguebearer_infection_count < 0x3c)) {
              creature_check_collision_radius(local_7c);
            }
            fVar17 = 30.0 / (&creature_pool)[local_7c].size;
            if ((((&creature_pool)[local_7c].flags & 4U) == 0) ||
               (((&creature_pool)[local_7c].flags & 0x40U) != 0)) {
              if ((&creature_pool)[local_7c].ai_mode != 7) {
                fVar17 = (&creature_type_table)[(&creature_pool)[local_7c].type_id].anim_rate *
                         (&creature_pool)[local_7c].move_speed * frame_dt * fVar17 * local_70 * 25.0
                         + (&creature_pool)[local_7c].anim_phase;
                (&creature_pool)[local_7c].anim_phase = fVar17;
                while (31.0 < fVar17) {
                  fVar17 = (&creature_pool)[local_7c].anim_phase - 31.0;
                  (&creature_pool)[local_7c].anim_phase = fVar17;
                }
              }
            }
            else {
              fVar17 = (&creature_type_table)[(&creature_pool)[local_7c].type_id].anim_rate *
                       (&creature_pool)[local_7c].move_speed * frame_dt * fVar17 * local_70 * 22.0 +
                       (&creature_pool)[local_7c].anim_phase;
              (&creature_pool)[local_7c].anim_phase = fVar17;
              if (15.0 < fVar17) {
                fVar17 = (&creature_pool)[local_7c].anim_phase;
                do {
                  fVar17 = fVar17 - 15.0;
                } while (15.0 < fVar17);
                (&creature_pool)[local_7c].anim_phase = fVar17;
              }
            }
            pfVar3 = &(&creature_pool)[local_7c].attack_cooldown;
            if ((&creature_pool)[local_7c].attack_cooldown <= 0.0) {
              *pfVar3 = 0.0;
            }
            else {
              *pfVar3 = *pfVar3 - frame_dt;
            }
            cVar10 = (char)(&creature_pool)[local_7c].target_player;
            piVar4 = &(&creature_pool)[local_7c].target_player;
            fVar17 = *pfVar16 - (&player_state_table)[cVar10].pos_x;
            fVar15 = (&creature_pool)[local_7c].pos_y - (&player_state_table)[cVar10].pos_y;
            fVar17 = SQRT(fVar17 * fVar17 + fVar15 * fVar15);
            if ((((fVar17 < 100.0) && (iVar7 = perk_count_get(perk_id_radioactive), iVar7 != 0)) &&
                (fVar15 = (&creature_pool)[local_7c].collision_timer - frame_dt * 1.5,
                (&creature_pool)[local_7c].collision_timer = fVar15, fVar15 < 0.0)) &&
               (0.0 < *pfVar14)) {
              (&creature_pool)[local_7c].collision_timer = 0.5;
              (&creature_pool)[local_7c].state_flag = '\x01';
              fVar15 = *pfVar14 - (100.0 - fVar17) * 0.3;
              *pfVar14 = fVar15;
              if (fVar15 < 0.0) {
                if ((&creature_pool)[local_7c].type_id == 1) {
                  *pfVar14 = 1.0;
                }
                else {
                  lVar13 = __ftol();
                  player_state_table.experience = (int)lVar13;
                  *pfVar1 = *pfVar1 - frame_dt;
                }
              }
              fx_queue_add_random(pfVar16);
            }
            if (64.0 < fVar17) {
              if ((((&creature_pool)[local_7c].flags & 0x10) != 0) && (*pfVar3 <= 0.0)) {
                projectile_spawn(pfVar16,(&creature_pool)[local_7c].heading,
                                 PROJECTILE_TYPE_PLASMA_RIFLE,local_7c);
                fVar15 = sfx_shock_fire;
                *pfVar3 = *pfVar3 + 1.0;
                sfx_play_panned(fVar15);
              }
              if ((((&creature_pool)[local_7c].flags & 0x100U) != 0) && (*pfVar3 <= 0.0)) {
                projectile_spawn(pfVar16,(&creature_pool)[local_7c].heading,
                                 (&creature_pool)[local_7c].orbit_radius.projectile_type,local_7c);
                uVar8 = crt_rand();
                fVar15 = sfx_plasmaminigun_fire;
                local_60 = (float)(uVar8 & 3);
                *pfVar3 = (float)(int)local_60 * 0.1 + (&creature_pool)[local_7c].orbit_angle +
                          *pfVar3;
                sfx_play_panned(fVar15);
              }
            }
            if (fVar17 < 20.0) {
              *pfVar16 = *pfVar16 - (&creature_pool)[local_7c].vel_x;
              (&creature_pool)[local_7c].pos_y =
                   (&creature_pool)[local_7c].pos_y - (&creature_pool)[local_7c].vel_y;
              if (((&creature_pool)[local_7c].max_health < 380.0) && (0.0 < bonus_energizer_timer))
              {
                lVar13 = __ftol();
                player_state_table.experience = (int)lVar13;
                effect_spawn_burst(pfVar16,6);
                sfx_play_panned(sfx_ui_bonus);
                bonus_spawn_guard = 1;
                creature_handle_death(local_7c,false);
                bonus_spawn_guard = 0;
              }
            }
            if (16.0 < (&creature_pool)[local_7c].size) {
              if (30.0 <= fVar17) goto LAB_004276d6;
              if ((0.0 < (&player_state_table)[(char)*piVar4].health) &&
                 (bonus_energizer_timer <= 0.0)) {
                if (*pfVar3 <= 0.0) {
                  uVar8 = crt_rand();
                  uVar8 = uVar8 & 0x80000001;
                  if ((int)uVar8 < 0) {
                    uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
                  }
                  sfx_play_panned((float)(&creature_type_table)[(&creature_pool)[local_7c].type_id].
                                         sfx_bank_b[uVar8]);
                  iVar7 = perk_count_get(perk_id_mr_melee);
                  if (iVar7 != 0) {
                    local_50[8] = 0.0;
                    local_50[9] = 0.0;
                    creature_apply_damage(local_7c,25.0,2,local_50 + 8);
                  }
                  if ((&player_state_table)[(char)*piVar4].shield_timer <= 0.0) {
                    iVar7 = perk_count_get(perk_id_toxic_avenger);
                    if (iVar7 == 0) {
                      iVar7 = perk_count_get(perk_id_veins_of_poison);
                      if (iVar7 == 0) goto LAB_0042733a;
                      uVar8 = (&creature_pool)[local_7c].flags | 1;
                    }
                    else {
                      uVar8 = (&creature_pool)[local_7c].flags | 3;
                    }
                    (&creature_pool)[local_7c].flags = uVar8;
                  }
LAB_0042733a:
                  player_take_damage((int)(char)*piVar4,(&creature_pool)[local_7c].contact_damage);
                  player_aim_update_thunk();
                  local_50[9] = (float)puVar2 * 3.0 + (&player_state_table)[(char)*piVar4].pos_y;
                  local_50[8] = local_60 * 3.0 + (&player_state_table)[(char)*piVar4].pos_x;
                  fx_queue_add_random(local_50 + 8);
                  *pfVar3 = *pfVar3 + 1.0;
                }
                if ((((&player_plaguebearer_active)[(char)*piVar4 * 0x360] != '\0') &&
                    (*pfVar14 < 150.0)) && (plaguebearer_infection_count < 0x32)) {
                  *puVar2 = '\x01';
                }
              }
            }
            if ((fVar17 < 30.0) && ((&creature_pool)[local_7c].size <= 30.0)) {
              *pfVar14 = 0.0;
              *pfVar1 = *pfVar1 - frame_dt;
            }
          }
        }
        else if (*pfVar1 <= 0.0) {
          *pfVar1 = *pfVar1 - frame_dt * 20.0;
        }
        else {
          fVar17 = *pfVar1 - frame_dt * 28.0;
          *pfVar1 = fVar17;
          if (0.0 < fVar17) {
            if ((((&creature_pool)[local_7c].flags & 4U) == 0) ||
               (((&creature_pool)[local_7c].flags & 0x40U) != 0)) {
              fVar11 = (float10)(&creature_pool)[local_7c].heading - (float10)1.5707964;
              fVar12 = (float10)fcos(fVar11);
              (&creature_pool)[local_7c].vel_x =
                   (float)(fVar12 * (float10)fVar17 * (float10)frame_dt * (float10)9.0);
              fVar11 = (float10)fsin(fVar11);
              (&creature_pool)[local_7c].vel_y =
                   (float)(fVar11 * (float10)fVar17 * (float10)frame_dt * (float10)9.0);
              *pfVar16 = *pfVar16 - (&creature_pool)[local_7c].vel_x;
              (&creature_pool)[local_7c].pos_y =
                   (&creature_pool)[local_7c].pos_y - (&creature_pool)[local_7c].vel_y;
            }
            else {
              (&creature_pool)[local_7c].vel_x = 0.0;
              (&creature_pool)[local_7c].vel_y = 0.0;
            }
          }
          else {
            if (config_blob.fx_toggle == '\0') {
              if ((((&creature_pool)[local_7c].flags & 4U) == 0) ||
                 (((&creature_pool)[local_7c].flags & 0x40U) != 0)) {
                local_8 = (&creature_pool)[local_7c].size * 0.5;
                iVar7 = (&creature_pool)[local_7c].type_id;
                fVar17 = (&creature_pool)[local_7c].size;
                fVar15 = (&creature_pool)[local_7c].heading;
                local_18 = *pfVar16 - local_8;
                pfVar14 = &local_18;
                local_14 = (&creature_pool)[local_7c].pos_y - local_8;
              }
              else {
                local_10 = (&creature_pool)[local_7c].size * 0.5;
                fVar17 = (&creature_pool)[local_7c].size;
                fVar15 = (&creature_pool)[local_7c].heading;
                iVar7 = 7;
                local_20 = *pfVar16 - local_10;
                pfVar14 = &local_20;
                local_1c = (&creature_pool)[local_7c].pos_y - local_10;
              }
              iVar7 = fx_queue_add_rotated
                                (pfVar14,&(&creature_pool)[local_7c].tint_r,fVar15,fVar17,iVar7);
              if ((char)iVar7 == '\0') {
                *pfVar1 = 0.001;
                goto LAB_004276d6;
              }
            }
            highscore_active_record.creature_kill_count =
                 highscore_active_record.creature_kill_count + 1;
            if ((config_blob.fx_toggle == '\0') && (((&creature_pool)[local_7c].flags & 4) != 0)) {
              iVar7 = 8;
              do {
                fVar17 = 0.0;
                iVar9 = crt_rand();
                effect_spawn_blood_splatter(pfVar16,(float)(iVar9 % 0x264) * 0.01,fVar17);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              iVar7 = 6;
              do {
                fVar17 = -0.07;
                iVar9 = crt_rand();
                effect_spawn_blood_splatter(pfVar16,(float)(iVar9 % 0x264) * 0.01,fVar17);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
              iVar7 = 5;
              do {
                fVar17 = -0.12;
                iVar9 = crt_rand();
                effect_spawn_blood_splatter(pfVar16,(float)(iVar9 % 0x264) * 0.01,fVar17);
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
            if (*(float *)((int)cv_bodiesFade + 0xc) == 0.0) {
              (&creature_pool)[local_7c].active = '\0';
            }
          }
        }
      }
    }
LAB_004276d6:
    local_7c = local_7c + 1;
    if (0x17f < local_7c) {
      return;
    }
  } while( true );
}



/* creature_alloc_slot @ 00428140 */

/* finds a free creature entry in DAT_0049bf38 and seeds defaults */

int creature_alloc_slot(void)

{
  creature_t *pcVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  pcVar1 = &creature_pool;
  do {
    if (pcVar1->active == '\0') {
      (&creature_pool)[iVar3].flags = 0;
      uVar2 = crt_rand();
      (&creature_pool)[iVar3].phase_seed = (float)(uVar2 & 0x17f);
      pcVar1 = &creature_pool + iVar3;
      pcVar1->_pad3[0] = '\0';
      pcVar1->_pad3[1] = '\0';
      pcVar1->_pad3[2] = '\0';
      pcVar1->_pad3[3] = '\0';
      (&creature_pool)[iVar3].anim_phase = 0.0;
      creature_spawned_count = creature_spawned_count + 1;
      return iVar3;
    }
    pcVar1 = pcVar1 + 1;
    iVar3 = iVar3 + 1;
  } while ((int)pcVar1 < 0x4aa338);
  if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
    console_printf(&console_log_queue,s_No_free_creatures_to_spawn__00473e6c);
  }
  return 0x180;
}



/* creature_reset_all @ 004281e0 */

/* [binja] void* sub_4281e0() */

void * creature_reset_all(void)

{
  int *piVar1;
  
  piVar1 = &creature_pool.flags;
  do {
    ((creature_t *)(piVar1 + -0x23))->active = 0;
    if ((*piVar1 & 4) != 0) {
      (&creature_spawn_slot_table)[piVar1[-5]].owner = (creature_t *)0x0;
    }
    piVar1 = piVar1 + 0x26;
  } while ((int)piVar1 < 0x4aa3c4);
  return piVar1;
}



/* creatures_none_active @ 00428210 */

/* returns low byte 1 when no active creature entries exist (0 otherwise); sets DAT_0048700c */

uint creatures_none_active(void)

{
  creature_t *pcVar1;
  
  pcVar1 = &creature_pool;
  do {
    if (pcVar1->active != '\0') {
      creatures_any_active_flag = 0;
      return (uint)pcVar1 & 0xffffff00;
    }
    pcVar1 = pcVar1 + 1;
  } while ((int)pcVar1 < 0x4aa338);
  creatures_any_active_flag = 1;
  return CONCAT31((int3)((uint)pcVar1 >> 8),1);
}



/* creature_spawn @ 00428240 */

/* allocates a creature slot and seeds position, type, and tint defaults */

int __cdecl creature_spawn(float *pos,float *tint_rgba,int type_id)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = creature_alloc_slot();
  (&creature_pool)[iVar3].pos_x = *pos;
  (&creature_pool)[iVar3].pos_y = pos[1];
  (&creature_pool)[iVar3].type_id = type_id;
  (&creature_pool)[iVar3].ai_mode = 0;
  (&creature_pool)[iVar3].collision_flag = '\0';
  (&creature_pool)[iVar3].collision_timer = 0.0;
  (&creature_pool)[iVar3].active = '\x01';
  *(undefined1 *)&(&creature_pool)[iVar3].force_target = 0;
  (&creature_pool)[iVar3].state_flag = '\x01';
  (&creature_pool)[iVar3].hitbox_size = 16.0;
  fVar1 = (float)(int)highscore_active_record.survival_elapsed_ms;
  (&creature_pool)[iVar3].vel_x = 0.0;
  (&creature_pool)[iVar3].vel_y = 0.0;
  (&creature_pool)[iVar3].health = fVar1 * 0.000100000005 + 10.0;
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].heading = (float)(iVar4 % 0x13a) * 0.01;
  (&creature_pool)[iVar3].move_speed =
       (float)(int)highscore_active_record.survival_elapsed_ms * 1.0000001e-05 + 2.5;
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].attack_cooldown = 0.0;
  (&creature_pool)[iVar3].reward_value = (float)(iVar4 % 0x1e + 0x8c);
  (&creature_pool)[iVar3].tint_r = *tint_rgba;
  (&creature_pool)[iVar3].tint_g = tint_rgba[1];
  (&creature_pool)[iVar3].tint_b = tint_rgba[2];
  fVar1 = (&creature_pool)[iVar3].health;
  (&creature_pool)[iVar3].tint_a = tint_rgba[3];
  fVar2 = (float)(int)highscore_active_record.survival_elapsed_ms;
  (&creature_pool)[iVar3].contact_damage = 4.0;
  (&creature_pool)[iVar3].max_health = fVar1;
  (&creature_pool)[iVar3].size = fVar2 * 1.0000001e-05 + 47.0;
  return iVar3;
}



/* creature_spawn_slot_alloc @ 00430ad0 */

/* returns first free spawn slot index (creature_spawn_slot_table[i].owner == NULL); returns 0x1f if
   none free */

int creature_spawn_slot_alloc(void)

{
  int iVar1;
  creature_spawn_slot_t *pcVar2;
  
  iVar1 = 0;
  pcVar2 = &creature_spawn_slot_table;
  do {
    if (pcVar2->owner == (creature_t *)0x0) {
      return iVar1;
    }
    pcVar2 = pcVar2 + 1;
    iVar1 = iVar1 + 1;
  } while ((int)pcVar2 < 0x4852d0);
  return 0x1f;
}



/* creature_spawn_template @ 00430af0 */

/* spawns creature(s) from template id; heading -100 uses a random heading */

void * __cdecl creature_spawn_template(int template_id,float *pos,float heading)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  creature_t *pcVar10;
  float10 fVar11;
  float10 fVar12;
  int local_48;
  float local_4;
  
  pfVar5 = pos;
  iVar6 = creature_alloc_slot();
  if (heading == -100.0) {
    iVar7 = crt_rand();
    heading = (float)(iVar7 % 0x274) * 0.01;
  }
  pcVar10 = &creature_pool + iVar6;
  (&creature_pool)[iVar6].ai_mode = 0;
  (&creature_pool)[iVar6].pos_x = *pos;
  fVar4 = pos[1];
  (&creature_pool)[iVar6].vel_x = 0.0;
  (&creature_pool)[iVar6].pos_y = fVar4;
  (&creature_pool)[iVar6].collision_flag = '\0';
  (&creature_pool)[iVar6].collision_timer = 0.0;
  pcVar10->active = '\x01';
  *(undefined1 *)&(&creature_pool)[iVar6].force_target = 0;
  (&creature_pool)[iVar6].state_flag = '\x01';
  (&creature_pool)[iVar6].hitbox_size = 16.0;
  (&creature_pool)[iVar6].vel_y = 0.0;
  iVar7 = crt_rand();
  (&creature_pool)[iVar6].attack_cooldown = 0.0;
  (&creature_pool)[iVar6].heading = (float)(iVar7 % 0x13a) * 0.01;
  if (template_id == 0x12) {
    (&creature_pool)[iVar6].tint_r = 0.65;
    (&creature_pool)[iVar6].type_id = 2;
    (&creature_pool)[iVar6].tint_g = 0.85;
    (&creature_pool)[iVar6].health = 200.0;
    (&creature_pool)[iVar6].move_speed = 2.2;
    (&creature_pool)[iVar6].tint_b = 0.97;
    (&creature_pool)[iVar6].reward_value = 600.0;
    (&creature_pool)[iVar6].size = 55.0;
    (&creature_pool)[iVar6].tint_a = 1.0;
    (&creature_pool)[iVar6].contact_damage = 14.0;
    (&creature_pool)[iVar6].max_health = 200.0;
    pos = (float *)0x0;
    do {
      iVar7 = creature_alloc_slot();
      fVar11 = (float10)fcos((float10)(int)pos * (float10)0.7853982);
      pcVar10 = &creature_pool + iVar7;
      (&creature_pool)[iVar7].ai_mode = 3;
      (&creature_pool)[iVar7].link_index = iVar6;
      (&creature_pool)[iVar7].target_offset_x = (float)(fVar11 * (float10)100.0);
      fVar11 = (float10)fsin((float10)(int)pos * (float10)0.7853982);
      (&creature_pool)[iVar7].target_offset_y = (float)(fVar11 * (float10)100.0);
      (&creature_pool)[iVar7].pos_x = *pfVar5;
      (&creature_pool)[iVar7].pos_y = pfVar5[1];
      (&creature_pool)[iVar7].vel_x = 0.0;
      (&creature_pool)[iVar7].vel_y = 0.0;
      (&creature_pool)[iVar7].collision_flag = '\0';
      (&creature_pool)[iVar7].tint_r = 0.32000002;
      (&creature_pool)[iVar7].health = 40.0;
      (&creature_pool)[iVar7].max_health = 40.0;
      (&creature_pool)[iVar7].tint_g = 0.58800006;
      pos = (float *)((int)pos + 1);
      (&creature_pool)[iVar7].tint_b = 0.426;
      (&creature_pool)[iVar7].collision_timer = 0.0;
      pcVar10->active = '\x01';
      (&creature_pool)[iVar7].state_flag = '\x01';
      (&creature_pool)[iVar7].hitbox_size = 16.0;
      (&creature_pool)[iVar7].attack_cooldown = 0.0;
      (&creature_pool)[iVar7].type_id = 2;
      (&creature_pool)[iVar7].move_speed = 2.4;
      (&creature_pool)[iVar7].reward_value = 60.0;
      (&creature_pool)[iVar7].tint_a = 1.0;
      (&creature_pool)[iVar7].size = 50.0;
      (&creature_pool)[iVar7].contact_damage = 4.0;
    } while ((int)pos < 8);
  }
  else if (template_id == 0x19) {
    (&creature_pool)[iVar6].tint_r = 0.95;
    (&creature_pool)[iVar6].type_id = 2;
    (&creature_pool)[iVar6].tint_g = 0.55;
    (&creature_pool)[iVar6].health = 50.0;
    (&creature_pool)[iVar6].move_speed = 3.8;
    (&creature_pool)[iVar6].tint_b = 0.37;
    (&creature_pool)[iVar6].reward_value = 300.0;
    (&creature_pool)[iVar6].size = 55.0;
    (&creature_pool)[iVar6].tint_a = 1.0;
    (&creature_pool)[iVar6].contact_damage = 40.0;
    (&creature_pool)[iVar6].max_health = 50.0;
    pos = (float *)0x0;
    do {
      iVar7 = creature_alloc_slot();
      fVar11 = (float10)fcos((float10)(int)pos * (float10)1.2566371);
      pcVar10 = &creature_pool + iVar7;
      (&creature_pool)[iVar7].ai_mode = 5;
      (&creature_pool)[iVar7].link_index = iVar6;
      (&creature_pool)[iVar7].target_offset_x = (float)(fVar11 * (float10)110.0);
      fVar11 = (float10)fsin((float10)(int)pos * (float10)1.2566371);
      (&creature_pool)[iVar7].target_offset_y = (float)(fVar11 * (float10)110.0);
      fVar4 = (&creature_pool)[iVar7].target_offset_x;
      fVar1 = *pfVar5;
      fVar2 = (&creature_pool)[iVar7].target_offset_y;
      fVar3 = pfVar5[1];
      (&creature_pool)[iVar7].vel_x = 0.0;
      (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
      (&creature_pool)[iVar7].vel_y = 0.0;
      (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
      (&creature_pool)[iVar7].health = 220.0;
      (&creature_pool)[iVar7].max_health = 220.0;
      (&creature_pool)[iVar7].tint_r = 0.7125;
      pos = (float *)((int)pos + 1);
      (&creature_pool)[iVar7].tint_g = 0.41250002;
      (&creature_pool)[iVar7].collision_flag = '\0';
      (&creature_pool)[iVar7].tint_b = 0.2775;
      (&creature_pool)[iVar7].collision_timer = 0.0;
      pcVar10->active = '\x01';
      (&creature_pool)[iVar7].state_flag = '\x01';
      (&creature_pool)[iVar7].hitbox_size = 16.0;
      (&creature_pool)[iVar7].attack_cooldown = 0.0;
      (&creature_pool)[iVar7].type_id = 2;
      (&creature_pool)[iVar7].move_speed = 3.8;
      (&creature_pool)[iVar7].reward_value = 60.0;
      (&creature_pool)[iVar7].tint_a = 0.6;
      (&creature_pool)[iVar7].size = 50.0;
      (&creature_pool)[iVar7].contact_damage = 35.0;
    } while ((int)pos < 5);
  }
  else {
    if (template_id == 0x11) {
      (&creature_pool)[iVar6].type_id = 1;
      (&creature_pool)[iVar6].pos_x = *pos;
      (&creature_pool)[iVar6].pos_y = pos[1];
      (&creature_pool)[iVar6].ai_mode = 1;
      (&creature_pool)[iVar6].tint_r = 0.99;
      (&creature_pool)[iVar6].tint_g = 0.99;
      (&creature_pool)[iVar6].health = 1500.0;
      (&creature_pool)[iVar6].move_speed = 2.1;
      (&creature_pool)[iVar6].tint_b = 0.21;
      (&creature_pool)[iVar6].reward_value = 1000.0;
      (&creature_pool)[iVar6].size = 69.0;
      (&creature_pool)[iVar6].tint_a = 1.0;
      (&creature_pool)[iVar6].contact_damage = 150.0;
      (&creature_pool)[iVar6].max_health = 1500.0;
      local_48 = 2;
      pos = (float *)0xffffff00;
      iVar7 = iVar6;
      do {
        iVar8 = creature_alloc_slot();
        (&creature_pool)[iVar8].target_offset_x = (float)(int)pos;
        pcVar10 = &creature_pool + iVar8;
        (&creature_pool)[iVar8].ai_mode = 3;
        (&creature_pool)[iVar8].link_index = iVar7;
        (&creature_pool)[iVar8].target_offset_y = -256.0;
        fVar11 = (float10)fcos((float10)local_48 * (float10)0.3926991);
        fVar12 = (float10)fsin((float10)local_48 * (float10)0.3926991);
        fVar4 = pfVar5[1];
        (&creature_pool)[iVar8].pos_x = (float)fVar11 * 256.0 + *pfVar5;
        (&creature_pool)[iVar8].vel_x = 0.0;
        (&creature_pool)[iVar8].tint_r = 0.6;
        (&creature_pool)[iVar8].pos_y = (float)(fVar12 * (float10)256.0 + (float10)fVar4);
        (&creature_pool)[iVar8].tint_g = 0.6;
        (&creature_pool)[iVar8].vel_y = 0.0;
        (&creature_pool)[iVar8].tint_b = 0.31;
        (&creature_pool)[iVar8].health = 60.0;
        (&creature_pool)[iVar8].reward_value = 60.0;
        (&creature_pool)[iVar8].max_health = 60.0;
        (&creature_pool)[iVar8].tint_a = 1.0;
        pos = pos + 0x10;
        local_48 = local_48 + 2;
        (&creature_pool)[iVar8].collision_flag = '\0';
        (&creature_pool)[iVar8].collision_timer = 0.0;
        pcVar10->active = '\x01';
        (&creature_pool)[iVar8].state_flag = '\x01';
        (&creature_pool)[iVar8].hitbox_size = 16.0;
        (&creature_pool)[iVar8].attack_cooldown = 0.0;
        (&creature_pool)[iVar8].type_id = 1;
        (&creature_pool)[iVar8].move_speed = 2.4;
        (&creature_pool)[iVar8].size = 50.0;
        (&creature_pool)[iVar8].contact_damage = 14.0;
        iVar7 = iVar8;
      } while ((int)pos < 0);
    }
    else {
      if (template_id != 0x13) {
        if (template_id == 0x14) {
          (&creature_pool)[iVar6].type_id = 2;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].ai_mode = 2;
          (&creature_pool)[iVar6].tint_r = 0.7;
          (&creature_pool)[iVar6].tint_g = 0.8;
          (&creature_pool)[iVar6].health = 1500.0;
          (&creature_pool)[iVar6].move_speed = 2.0;
          (&creature_pool)[iVar6].tint_b = 0.31;
          (&creature_pool)[iVar6].reward_value = 600.0;
          (&creature_pool)[iVar6].size = 50.0;
          (&creature_pool)[iVar6].tint_a = 1.0;
          (&creature_pool)[iVar6].contact_damage = 40.0;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].max_health = 1500.0;
          local_48 = 0;
          do {
            pos = (float *)0x80;
            do {
              iVar7 = creature_alloc_slot();
              (&creature_pool)[iVar7].target_offset_y = (float)(int)pos;
              pcVar10 = &creature_pool + iVar7;
              (&creature_pool)[iVar7].ai_mode = 5;
              (&creature_pool)[iVar7].heading = 0.0;
              (&creature_pool)[iVar7].anim_phase = 0.0;
              (&creature_pool)[iVar7].link_index = iVar6;
              (&creature_pool)[iVar7].target_offset_x = (float)local_48;
              fVar4 = *pfVar5;
              fVar1 = (&creature_pool)[iVar7].target_offset_x;
              fVar2 = (&creature_pool)[iVar7].target_offset_y;
              fVar3 = pfVar5[1];
              (&creature_pool)[iVar7].vel_x = 0.0;
              (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
              (&creature_pool)[iVar7].vel_y = 0.0;
              (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
              (&creature_pool)[iVar7].tint_r = 0.4;
              (&creature_pool)[iVar7].health = 40.0;
              (&creature_pool)[iVar7].max_health = 40.0;
              (&creature_pool)[iVar7].tint_g = 0.7;
              pos = pos + 0x10;
              (&creature_pool)[iVar7].tint_b = 0.11;
              (&creature_pool)[iVar7].collision_flag = '\0';
              (&creature_pool)[iVar7].collision_timer = 0.0;
              pcVar10->active = '\x01';
              (&creature_pool)[iVar7].state_flag = '\x01';
              (&creature_pool)[iVar7].hitbox_size = 16.0;
              (&creature_pool)[iVar7].attack_cooldown = 0.0;
              (&creature_pool)[iVar7].type_id = 2;
              (&creature_pool)[iVar7].move_speed = 2.0;
              (&creature_pool)[iVar7].reward_value = 60.0;
              (&creature_pool)[iVar7].tint_a = 1.0;
              (&creature_pool)[iVar7].size = 50.0;
              (&creature_pool)[iVar7].contact_damage = 4.0;
            } while ((int)pos < 0x101);
            local_48 = local_48 + -0x40;
          } while (-0x240 < local_48);
        }
        else if (template_id == 0x15) {
          (&creature_pool)[iVar6].type_id = 2;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].ai_mode = 2;
          (&creature_pool)[iVar6].tint_r = 1.0;
          (&creature_pool)[iVar6].tint_g = 1.0;
          (&creature_pool)[iVar6].health = 1500.0;
          (&creature_pool)[iVar6].move_speed = 2.0;
          (&creature_pool)[iVar6].tint_b = 1.0;
          (&creature_pool)[iVar6].reward_value = 600.0;
          (&creature_pool)[iVar6].size = 60.0;
          (&creature_pool)[iVar6].tint_a = 1.0;
          (&creature_pool)[iVar6].contact_damage = 40.0;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].max_health = 1500.0;
          local_48 = 0;
          do {
            pos = (float *)0x80;
            do {
              iVar7 = creature_alloc_slot();
              (&creature_pool)[iVar7].target_offset_y = (float)(int)pos;
              pcVar10 = &creature_pool + iVar7;
              (&creature_pool)[iVar7].ai_mode = 4;
              (&creature_pool)[iVar7].heading = 0.0;
              (&creature_pool)[iVar7].anim_phase = 0.0;
              (&creature_pool)[iVar7].link_index = iVar6;
              (&creature_pool)[iVar7].target_offset_x = (float)local_48;
              fVar4 = *pfVar5;
              fVar1 = (&creature_pool)[iVar7].target_offset_x;
              fVar2 = (&creature_pool)[iVar7].target_offset_y;
              fVar3 = pfVar5[1];
              (&creature_pool)[iVar7].vel_x = 0.0;
              (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
              (&creature_pool)[iVar7].vel_y = 0.0;
              (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
              (&creature_pool)[iVar7].health = 40.0;
              (&creature_pool)[iVar7].max_health = 40.0;
              (&creature_pool)[iVar7].tint_r = 0.4;
              pos = pos + 0x10;
              (&creature_pool)[iVar7].tint_g = 0.7;
              (&creature_pool)[iVar7].collision_flag = '\0';
              (&creature_pool)[iVar7].tint_b = 0.11;
              (&creature_pool)[iVar7].collision_timer = 0.0;
              pcVar10->active = '\x01';
              (&creature_pool)[iVar7].state_flag = '\x01';
              (&creature_pool)[iVar7].hitbox_size = 16.0;
              (&creature_pool)[iVar7].attack_cooldown = 0.0;
              (&creature_pool)[iVar7].type_id = 2;
              (&creature_pool)[iVar7].move_speed = 2.0;
              (&creature_pool)[iVar7].reward_value = 60.0;
              (&creature_pool)[iVar7].tint_a = 1.0;
              (&creature_pool)[iVar7].size = 50.0;
              (&creature_pool)[iVar7].contact_damage = 4.0;
            } while ((int)pos < 0x101);
            local_48 = local_48 + -0x40;
          } while (-0x240 < local_48);
        }
        else if (template_id == 0x17) {
          (&creature_pool)[iVar6].type_id = 3;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].tint_r = 1.0;
          (&creature_pool)[iVar6].tint_g = 1.0;
          (&creature_pool)[iVar6].ai_mode = 2;
          (&creature_pool)[iVar6].health = 1500.0;
          (&creature_pool)[iVar6].tint_b = 1.0;
          (&creature_pool)[iVar6].move_speed = 2.0;
          (&creature_pool)[iVar6].reward_value = 600.0;
          (&creature_pool)[iVar6].tint_a = 1.0;
          (&creature_pool)[iVar6].size = 60.0;
          (&creature_pool)[iVar6].contact_damage = 40.0;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].max_health = 1500.0;
          local_48 = 0;
          do {
            pos = (float *)0x80;
            do {
              iVar7 = creature_alloc_slot();
              (&creature_pool)[iVar7].target_offset_y = (float)(int)pos;
              pcVar10 = &creature_pool + iVar7;
              (&creature_pool)[iVar7].ai_mode = 4;
              (&creature_pool)[iVar7].heading = 0.0;
              (&creature_pool)[iVar7].anim_phase = 0.0;
              (&creature_pool)[iVar7].link_index = iVar6;
              (&creature_pool)[iVar7].target_offset_x = (float)local_48;
              fVar4 = (&creature_pool)[iVar7].target_offset_x;
              fVar1 = *pfVar5;
              fVar2 = (&creature_pool)[iVar7].target_offset_y;
              fVar3 = pfVar5[1];
              (&creature_pool)[iVar7].vel_x = 0.0;
              (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
              (&creature_pool)[iVar7].vel_y = 0.0;
              (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
              (&creature_pool)[iVar7].health = 40.0;
              (&creature_pool)[iVar7].max_health = 40.0;
              (&creature_pool)[iVar7].tint_r = 0.4;
              pos = pos + 0x10;
              (&creature_pool)[iVar7].tint_g = 0.7;
              (&creature_pool)[iVar7].collision_flag = '\0';
              (&creature_pool)[iVar7].tint_b = 0.11;
              (&creature_pool)[iVar7].collision_timer = 0.0;
              pcVar10->active = '\x01';
              (&creature_pool)[iVar7].state_flag = '\x01';
              (&creature_pool)[iVar7].hitbox_size = 16.0;
              (&creature_pool)[iVar7].attack_cooldown = 0.0;
              (&creature_pool)[iVar7].type_id = 3;
              (&creature_pool)[iVar7].move_speed = 2.0;
              (&creature_pool)[iVar7].reward_value = 60.0;
              (&creature_pool)[iVar7].tint_a = 1.0;
              (&creature_pool)[iVar7].size = 50.0;
              (&creature_pool)[iVar7].contact_damage = 4.0;
            } while ((int)pos < 0x101);
            local_48 = local_48 + -0x40;
          } while (-0x240 < local_48);
        }
        else if (template_id == 0x16) {
          (&creature_pool)[iVar6].type_id = 1;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].tint_r = 1.0;
          (&creature_pool)[iVar6].tint_g = 1.0;
          (&creature_pool)[iVar6].ai_mode = 2;
          (&creature_pool)[iVar6].health = 1500.0;
          (&creature_pool)[iVar6].tint_b = 1.0;
          (&creature_pool)[iVar6].move_speed = 2.0;
          (&creature_pool)[iVar6].reward_value = 600.0;
          (&creature_pool)[iVar6].tint_a = 1.0;
          (&creature_pool)[iVar6].size = 64.0;
          (&creature_pool)[iVar6].contact_damage = 40.0;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].max_health = 1500.0;
          local_48 = 0;
          do {
            pos = (float *)0x80;
            do {
              iVar7 = creature_alloc_slot();
              (&creature_pool)[iVar7].target_offset_y = (float)(int)pos;
              pcVar10 = &creature_pool + iVar7;
              (&creature_pool)[iVar7].ai_mode = 4;
              (&creature_pool)[iVar7].heading = 0.0;
              (&creature_pool)[iVar7].anim_phase = 0.0;
              (&creature_pool)[iVar7].link_index = iVar6;
              (&creature_pool)[iVar7].target_offset_x = (float)local_48;
              fVar4 = (&creature_pool)[iVar7].target_offset_x;
              fVar1 = *pfVar5;
              fVar2 = (&creature_pool)[iVar7].target_offset_y;
              fVar3 = pfVar5[1];
              (&creature_pool)[iVar7].vel_x = 0.0;
              (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
              (&creature_pool)[iVar7].vel_y = 0.0;
              (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
              (&creature_pool)[iVar7].health = 40.0;
              (&creature_pool)[iVar7].max_health = 40.0;
              (&creature_pool)[iVar7].tint_r = 0.4;
              pos = pos + 0x10;
              (&creature_pool)[iVar7].tint_g = 0.7;
              (&creature_pool)[iVar7].collision_flag = '\0';
              (&creature_pool)[iVar7].tint_b = 0.11;
              (&creature_pool)[iVar7].collision_timer = 0.0;
              pcVar10->active = '\x01';
              (&creature_pool)[iVar7].state_flag = '\x01';
              (&creature_pool)[iVar7].hitbox_size = 16.0;
              (&creature_pool)[iVar7].attack_cooldown = 0.0;
              (&creature_pool)[iVar7].type_id = 1;
              (&creature_pool)[iVar7].move_speed = 2.0;
              (&creature_pool)[iVar7].reward_value = 60.0;
              (&creature_pool)[iVar7].tint_a = 1.0;
              (&creature_pool)[iVar7].size = 60.0;
              (&creature_pool)[iVar7].contact_damage = 4.0;
            } while ((int)pos < 0x101);
            local_48 = local_48 + -0x40;
          } while (-0x240 < local_48);
        }
        else {
          if (template_id != 0xf) {
            if (template_id == 0x18) {
              (&creature_pool)[iVar6].type_id = 2;
              (&creature_pool)[iVar6].pos_x = *pos;
              fVar4 = pos[1];
              (&creature_pool)[iVar6].ai_mode = 2;
              (&creature_pool)[iVar6].tint_r = 0.7;
              (&creature_pool)[iVar6].pos_y = fVar4;
              (&creature_pool)[iVar6].tint_g = 0.8;
              (&creature_pool)[iVar6].health = 500.0;
              (&creature_pool)[iVar6].move_speed = 2.0;
              (&creature_pool)[iVar6].tint_b = 0.31;
              (&creature_pool)[iVar6].reward_value = 600.0;
              (&creature_pool)[iVar6].tint_a = 1.0;
              (&creature_pool)[iVar6].size = 40.0;
              (&creature_pool)[iVar6].contact_damage = 40.0;
              (&creature_pool)[iVar6].pos_x = *pos;
              (&creature_pool)[iVar6].pos_y = pos[1];
              (&creature_pool)[iVar6].max_health = 500.0;
              local_48 = 0;
              do {
                pos = (float *)0x80;
                do {
                  iVar7 = creature_alloc_slot();
                  (&creature_pool)[iVar7].target_offset_y = (float)(int)pos;
                  pcVar10 = &creature_pool + iVar7;
                  (&creature_pool)[iVar7].ai_mode = 3;
                  (&creature_pool)[iVar7].heading = 0.0;
                  (&creature_pool)[iVar7].anim_phase = 0.0;
                  (&creature_pool)[iVar7].link_index = iVar6;
                  (&creature_pool)[iVar7].target_offset_x = (float)local_48;
                  fVar4 = (&creature_pool)[iVar7].target_offset_x;
                  fVar1 = *pfVar5;
                  fVar2 = (&creature_pool)[iVar7].target_offset_y;
                  fVar3 = pfVar5[1];
                  (&creature_pool)[iVar7].vel_x = 0.0;
                  (&creature_pool)[iVar7].pos_x = fVar4 + fVar1;
                  (&creature_pool)[iVar7].vel_y = 0.0;
                  (&creature_pool)[iVar7].pos_y = fVar2 + fVar3;
                  (&creature_pool)[iVar7].health = 260.0;
                  (&creature_pool)[iVar7].max_health = 260.0;
                  (&creature_pool)[iVar7].tint_r = 0.7125;
                  pos = pos + 0x10;
                  (&creature_pool)[iVar7].tint_g = 0.41250002;
                  (&creature_pool)[iVar7].collision_flag = '\0';
                  (&creature_pool)[iVar7].tint_b = 0.2775;
                  (&creature_pool)[iVar7].collision_timer = 0.0;
                  pcVar10->active = '\x01';
                  (&creature_pool)[iVar7].state_flag = '\x01';
                  (&creature_pool)[iVar7].hitbox_size = 16.0;
                  (&creature_pool)[iVar7].attack_cooldown = 0.0;
                  (&creature_pool)[iVar7].type_id = 2;
                  (&creature_pool)[iVar7].move_speed = 3.8;
                  (&creature_pool)[iVar7].reward_value = 60.0;
                  (&creature_pool)[iVar7].tint_a = 0.6;
                  (&creature_pool)[iVar7].size = 50.0;
                  (&creature_pool)[iVar7].contact_damage = 35.0;
                } while ((int)pos < 0x101);
                local_48 = local_48 + -0x40;
              } while (-0x240 < local_48);
              goto LAB_004310b8;
            }
            if (template_id == 1) {
              (&creature_pool)[iVar6].type_id = 4;
              (&creature_pool)[iVar6].flags = 8;
              (&creature_pool)[iVar6].size = 80.0;
              (&creature_pool)[iVar6].health = 400.0;
              (&creature_pool)[iVar6].move_speed = 2.0;
              (&creature_pool)[iVar6].reward_value = 1000.0;
              (&creature_pool)[iVar6].tint_a = 1.0;
              (&creature_pool)[iVar6].tint_r = 0.8;
              (&creature_pool)[iVar6].tint_g = 0.7;
              (&creature_pool)[iVar6].tint_b = 0.4;
              (&creature_pool)[iVar6].contact_damage = 17.0;
              goto LAB_004310b8;
            }
            if (template_id == 10) {
              (&creature_pool)[iVar6].type_id = 2;
              (&creature_pool)[iVar6].flags = 4;
              iVar7 = creature_spawn_slot_alloc();
              (&creature_pool)[iVar6].link_index = iVar7;
              (&creature_spawn_slot_table)[iVar7].timer_s = 2.0;
              (&creature_spawn_slot_table)[iVar7].count = 0;
              (&creature_spawn_slot_table)[iVar7].limit = 100;
              (&creature_spawn_slot_table)[iVar7].interval_s = 5.0;
              (&creature_spawn_slot_table)[iVar7].template_id = 0x32;
              (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
              (&creature_pool)[iVar6].size = 55.0;
              (&creature_pool)[iVar6].health = 1000.0;
              (&creature_pool)[iVar6].move_speed = 1.5;
              (&creature_pool)[iVar6].reward_value = 3000.0;
              (&creature_pool)[iVar6].tint_a = 1.0;
              (&creature_pool)[iVar6].tint_r = 0.8;
              (&creature_pool)[iVar6].tint_g = 0.7;
              (&creature_pool)[iVar6].tint_b = 0.4;
              (&creature_pool)[iVar6].contact_damage = 0.0;
              goto LAB_004310b8;
            }
            if (template_id == 0xb) {
              (&creature_pool)[iVar6].type_id = 2;
              (&creature_pool)[iVar6].flags = 4;
              iVar7 = creature_spawn_slot_alloc();
              (&creature_pool)[iVar6].link_index = iVar7;
              (&creature_spawn_slot_table)[iVar7].timer_s = 2.0;
              (&creature_spawn_slot_table)[iVar7].count = 0;
              (&creature_spawn_slot_table)[iVar7].limit = 100;
              (&creature_spawn_slot_table)[iVar7].interval_s = 6.0;
              (&creature_spawn_slot_table)[iVar7].template_id = 0x3c;
              (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
              (&creature_pool)[iVar6].size = 65.0;
              (&creature_pool)[iVar6].health = 3500.0;
              (&creature_pool)[iVar6].move_speed = 1.5;
              (&creature_pool)[iVar6].reward_value = 5000.0;
              (&creature_pool)[iVar6].tint_a = 1.0;
              (&creature_pool)[iVar6].tint_r = 0.9;
              (&creature_pool)[iVar6].tint_g = 0.1;
              (&creature_pool)[iVar6].tint_b = 0.1;
              (&creature_pool)[iVar6].contact_damage = 0.0;
              goto LAB_004310b8;
            }
            if (template_id == 0x10) {
              (&creature_pool)[iVar6].type_id = 2;
              (&creature_pool)[iVar6].flags = 4;
              iVar7 = creature_spawn_slot_alloc();
              (&creature_pool)[iVar6].link_index = iVar7;
              (&creature_spawn_slot_table)[iVar7].timer_s = 1.5;
              (&creature_spawn_slot_table)[iVar7].count = 0;
              (&creature_spawn_slot_table)[iVar7].limit = 100;
              (&creature_spawn_slot_table)[iVar7].interval_s = 2.3;
              (&creature_spawn_slot_table)[iVar7].template_id = 0x32;
              (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
              (&creature_pool)[iVar6].size = 32.0;
              (&creature_pool)[iVar6].health = 50.0;
              (&creature_pool)[iVar6].move_speed = 2.8;
              (&creature_pool)[iVar6].reward_value = 800.0;
            }
            else {
              if (template_id == 0xe) {
                (&creature_pool)[iVar6].type_id = 2;
                (&creature_pool)[iVar6].flags = 4;
                iVar7 = creature_spawn_slot_alloc();
                (&creature_pool)[iVar6].link_index = iVar7;
                pos = (float *)0x0;
                (&creature_spawn_slot_table)[iVar7].timer_s = 1.5;
                (&creature_spawn_slot_table)[iVar7].count = 0;
                (&creature_spawn_slot_table)[iVar7].limit = 0x40;
                (&creature_spawn_slot_table)[iVar7].interval_s = 1.05;
                (&creature_spawn_slot_table)[iVar7].template_id = 0x1c;
                (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                (&creature_pool)[iVar6].size = 32.0;
                (&creature_pool)[iVar6].health = 50.0;
                (&creature_pool)[iVar6].move_speed = 2.8;
                (&creature_pool)[iVar6].reward_value = 5000.0;
                (&creature_pool)[iVar6].tint_a = 1.0;
                (&creature_pool)[iVar6].tint_r = 0.9;
                (&creature_pool)[iVar6].tint_g = 0.8;
                (&creature_pool)[iVar6].tint_b = 0.4;
                (&creature_pool)[iVar6].contact_damage = 0.0;
                do {
                  iVar7 = creature_alloc_slot();
                  fVar11 = (float10)fcos((float10)(int)pos * (float10)0.2617994);
                  pcVar10 = &creature_pool + iVar7;
                  (&creature_pool)[iVar7].ai_mode = 3;
                  (&creature_pool)[iVar7].heading = 0.0;
                  (&creature_pool)[iVar7].anim_phase = 0.0;
                  (&creature_pool)[iVar7].link_index = iVar6;
                  (&creature_pool)[iVar7].target_offset_x = (float)(fVar11 * (float10)100.0);
                  fVar11 = (float10)fsin((float10)(int)pos * (float10)0.2617994);
                  (&creature_pool)[iVar7].target_offset_y = (float)(fVar11 * (float10)100.0);
                  (&creature_pool)[iVar7].pos_x = *pfVar5;
                  (&creature_pool)[iVar7].pos_y = pfVar5[1];
                  (&creature_pool)[iVar7].vel_x = 0.0;
                  (&creature_pool)[iVar7].vel_y = 0.0;
                  (&creature_pool)[iVar7].collision_flag = '\0';
                  (&creature_pool)[iVar7].tint_r = 1.0;
                  (&creature_pool)[iVar7].health = 40.0;
                  (&creature_pool)[iVar7].max_health = 40.0;
                  (&creature_pool)[iVar7].tint_g = 0.3;
                  pos = (float *)((int)pos + 1);
                  (&creature_pool)[iVar7].tint_b = 0.3;
                  (&creature_pool)[iVar7].collision_timer = 0.0;
                  pcVar10->active = '\x01';
                  (&creature_pool)[iVar7].state_flag = '\x01';
                  (&creature_pool)[iVar7].hitbox_size = 16.0;
                  (&creature_pool)[iVar7].attack_cooldown = 0.0;
                  (&creature_pool)[iVar7].type_id = 2;
                  (&creature_pool)[iVar7].move_speed = 4.0;
                  (&creature_pool)[iVar7].reward_value = 350.0;
                  (&creature_pool)[iVar7].tint_a = 1.0;
                  (&creature_pool)[iVar7].size = 35.0;
                  (&creature_pool)[iVar7].contact_damage = 30.0;
                } while ((int)pos < 0x18);
                goto LAB_004310b8;
              }
              if (template_id == 0xc) {
                (&creature_pool)[iVar6].type_id = 2;
                (&creature_pool)[iVar6].flags = 4;
                iVar7 = creature_spawn_slot_alloc();
                (&creature_pool)[iVar6].link_index = iVar7;
                (&creature_spawn_slot_table)[iVar7].timer_s = 1.5;
                (&creature_spawn_slot_table)[iVar7].count = 0;
                (&creature_spawn_slot_table)[iVar7].limit = 100;
                (&creature_spawn_slot_table)[iVar7].interval_s = 2.0;
                (&creature_spawn_slot_table)[iVar7].template_id = 0x31;
                (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                (&creature_pool)[iVar6].size = 32.0;
                (&creature_pool)[iVar6].health = 50.0;
                (&creature_pool)[iVar6].move_speed = 2.8;
                (&creature_pool)[iVar6].reward_value = 1000.0;
              }
              else {
                if (template_id != 0xd) {
                  if (template_id == 9) {
                    (&creature_pool)[iVar6].type_id = 2;
                    (&creature_pool)[iVar6].flags = 4;
                    iVar7 = creature_spawn_slot_alloc();
                    (&creature_pool)[iVar6].link_index = iVar7;
                    (&creature_spawn_slot_table)[iVar7].timer_s = 1.0;
                    (&creature_spawn_slot_table)[iVar7].count = 0;
                    (&creature_spawn_slot_table)[iVar7].limit = 0x10;
                    (&creature_spawn_slot_table)[iVar7].interval_s = 2.0;
                    (&creature_spawn_slot_table)[iVar7].template_id = 0x1d;
                    (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                    (&creature_pool)[iVar6].size = 40.0;
                    (&creature_pool)[iVar6].health = 450.0;
                    (&creature_pool)[iVar6].move_speed = 2.0;
                    (&creature_pool)[iVar6].reward_value = 1000.0;
                    (&creature_pool)[iVar6].tint_a = 1.0;
                    (&creature_pool)[iVar6].tint_r = 1.0;
                    (&creature_pool)[iVar6].tint_g = 1.0;
                    (&creature_pool)[iVar6].tint_b = 1.0;
                    (&creature_pool)[iVar6].contact_damage = 0.0;
                    goto LAB_004310b8;
                  }
                  if (template_id == 7) {
                    (&creature_pool)[iVar6].type_id = 2;
                    (&creature_pool)[iVar6].flags = 4;
                    iVar7 = creature_spawn_slot_alloc();
                    (&creature_pool)[iVar6].link_index = iVar7;
                    (&creature_spawn_slot_table)[iVar7].timer_s = 1.0;
                    (&creature_spawn_slot_table)[iVar7].count = 0;
                    (&creature_spawn_slot_table)[iVar7].limit = 100;
                    (&creature_spawn_slot_table)[iVar7].interval_s = 2.2;
                  }
                  else {
                    if (template_id != 8) {
                      if (template_id == 0x1a) {
                        (&creature_pool)[iVar6].type_id = 2;
                        (&creature_pool)[iVar6].size = 50.0;
                        (&creature_pool)[iVar6].ai_mode = 1;
                        (&creature_pool)[iVar6].health = 50.0;
                        (&creature_pool)[iVar6].move_speed = 2.4;
                        (&creature_pool)[iVar6].reward_value = 125.0;
                        (&creature_pool)[iVar6].tint_a = 1.0;
                        iVar7 = crt_rand();
                        fVar4 = (float)(iVar7 % 0x28);
                      }
                      else if (template_id == 0x1b) {
                        (&creature_pool)[iVar6].type_id = 3;
                        (&creature_pool)[iVar6].size = 50.0;
                        (&creature_pool)[iVar6].ai_mode = 1;
                        (&creature_pool)[iVar6].health = 40.0;
                        (&creature_pool)[iVar6].move_speed = 2.4;
                        (&creature_pool)[iVar6].reward_value = 125.0;
                        (&creature_pool)[iVar6].tint_a = 1.0;
                        iVar7 = crt_rand();
                        fVar4 = (float)(iVar7 % 0x28);
                      }
                      else {
                        if (template_id != 0x1c) {
                          if (template_id == 0x41) {
                            (&creature_pool)[iVar6].type_id = 0;
                            iVar7 = crt_rand();
                            (&creature_pool)[iVar6].tint_a = 1.0;
                            fVar4 = (float)(iVar7 % 0x1e + 0x28);
                            (&creature_pool)[iVar6].size = fVar4;
                            (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 10.0;
                            (&creature_pool)[iVar6].move_speed = fVar4 * 0.0025 + 0.9;
                            (&creature_pool)[iVar6].reward_value = fVar4 + fVar4 + 50.0;
                            iVar7 = crt_rand();
                            fVar4 = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                            (&creature_pool)[iVar6].tint_r = fVar4;
                            (&creature_pool)[iVar6].tint_g = fVar4;
                            (&creature_pool)[iVar6].tint_b = fVar4;
                            iVar7 = crt_rand();
                            (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                            goto LAB_004310b8;
                          }
                          if (template_id == 0x31) {
                            (&creature_pool)[iVar6].type_id = 1;
                            iVar7 = crt_rand();
                            fVar4 = (float)(iVar7 % 0x1e + 0x28);
                            (&creature_pool)[iVar6].size = fVar4;
                            (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 10.0;
                            iVar7 = crt_rand();
                            (&creature_pool)[iVar6].tint_a = 1.0;
                            (&creature_pool)[iVar6].move_speed = (float)(iVar7 % 0x12) * 0.1 + 1.1;
                            (&creature_pool)[iVar6].reward_value =
                                 (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size + 50.0;
                            iVar7 = crt_rand();
                            (&creature_pool)[iVar6].tint_b = 0.38;
                            fVar4 = (float)(iVar7 % 0x1e) * 0.01 + 0.6;
                            (&creature_pool)[iVar6].tint_r = fVar4;
                            (&creature_pool)[iVar6].tint_g = fVar4;
                          }
                          else {
                            if (template_id != 0x32) {
                              if (template_id == 0x33) {
                                (&creature_pool)[iVar6].type_id = 3;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0xf + 0x2d);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = 0.5;
                                (&creature_pool)[iVar6].tint_b = 0.5;
                                (&creature_pool)[iVar6].tint_r = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x34) {
                                (&creature_pool)[iVar6].type_id = 3;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x14 + 0x28);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = 0.5;
                                (&creature_pool)[iVar6].tint_b = 0.5;
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x20) {
                                (&creature_pool)[iVar6].type_id = 2;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x1e + 0x28);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_r = 0.3;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = 0.3;
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 3) {
                                (&creature_pool)[iVar6].type_id = 3;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0xf + 0x26);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_r = 0.6;
                                (&creature_pool)[iVar6].tint_g = 0.6;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x19) * 0.01 + 0.8;
                                if (0.0 <= (&creature_pool)[iVar6].tint_r) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_r) {
                                    (&creature_pool)[iVar6].tint_r = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_r = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_g) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_g) {
                                    (&creature_pool)[iVar6].tint_g = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_g = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_b) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_b) {
                                    (&creature_pool)[iVar6].tint_b = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_b = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_a) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_a) {
                                    (&creature_pool)[iVar6].tint_a = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_a = 0.0;
                                }
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 5) {
                                (&creature_pool)[iVar6].type_id = 4;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0xf + 0x26);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_r = 0.6;
                                (&creature_pool)[iVar6].tint_g = 0.6;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x19) * 0.01 + 0.8;
                                if (0.0 <= (&creature_pool)[iVar6].tint_r) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_r) {
                                    (&creature_pool)[iVar6].tint_r = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_r = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_g) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_g) {
                                    (&creature_pool)[iVar6].tint_g = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_g = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_b) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_b) {
                                    (&creature_pool)[iVar6].tint_b = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_b = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_a) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_a) {
                                    (&creature_pool)[iVar6].tint_a = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_a = 0.0;
                                }
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 4) {
                                (&creature_pool)[iVar6].type_id = 1;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0xf + 0x26);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_r = 0.67;
                                (&creature_pool)[iVar6].tint_g = 0.67;
                                (&creature_pool)[iVar6].tint_b = 1.0;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 6) {
                                (&creature_pool)[iVar6].type_id = 2;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0xf + 0x26);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_r = 0.6;
                                (&creature_pool)[iVar6].tint_g = 0.6;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x19) * 0.01 + 0.8;
                                if (0.0 <= (&creature_pool)[iVar6].tint_r) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_r) {
                                    (&creature_pool)[iVar6].tint_r = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_r = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_g) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_g) {
                                    (&creature_pool)[iVar6].tint_g = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_g = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_b) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_b) {
                                    (&creature_pool)[iVar6].tint_b = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_b = 0.0;
                                }
                                if (0.0 <= (&creature_pool)[iVar6].tint_a) {
                                  if (1.0 < (&creature_pool)[iVar6].tint_a) {
                                    (&creature_pool)[iVar6].tint_a = 1.0;
                                  }
                                }
                                else {
                                  (&creature_pool)[iVar6].tint_a = 0.0;
                                }
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x35) {
                                (&creature_pool)[iVar6].type_id = 4;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 10 + 0x1e);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].tint_b = 0.8;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = 0.8;
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x14) * 0.01 + 0.8;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x2e) {
                                (&creature_pool)[iVar6].type_id = 1;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x1e + 0x28);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 20.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x12) * 0.1 + 1.1;
                                (&creature_pool)[iVar6].reward_value =
                                     (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size +
                                     50.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x36) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].size = 50.0;
                                (&creature_pool)[iVar6].ai_mode = 7;
                                (&creature_pool)[iVar6].orbit_radius.projectile_type = 0x3fc00000;
                                (&creature_pool)[iVar6].health = 10.0;
                                (&creature_pool)[iVar6].move_speed = 1.8;
                                (&creature_pool)[iVar6].reward_value = 150.0;
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 5) * 0.01 + 0.65;
                                (&creature_pool)[iVar6].tint_r = 0.65;
                                (&creature_pool)[iVar6].tint_b = 0.95;
                                (&creature_pool)[iVar6].contact_damage = 40.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x1d) {
                                (&creature_pool)[iVar6].type_id = 2;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x14 + 0x23);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 1.1428572 + 10.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0xf) * 0.1 + 1.1;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].reward_value = (float)(iVar7 % 100 + 0x32);
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x32) * 0.01 + 0.5;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 10) + 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x1e) {
                                (&creature_pool)[iVar6].type_id = 2;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x1e + 0x23);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 2.2857144 + 10.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x11) * 0.1 + 1.5;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].reward_value = (float)(iVar7 % 200 + 0x32);
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x32) * 0.01 + 0.5;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 0x1e) + 4.0
                                ;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x1f) {
                                (&creature_pool)[iVar6].type_id = 2;
                                iVar7 = crt_rand();
                                fVar4 = (float)(iVar7 % 0x1e + 0x2d);
                                (&creature_pool)[iVar6].size = fVar4;
                                (&creature_pool)[iVar6].health = fVar4 * 3.7142856 + 30.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].move_speed =
                                     (float)(iVar7 % 0x15) * 0.1 + 1.6;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].reward_value = (float)(iVar7 % 200 + 0x50);
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_r = (float)(iVar7 % 0x32) * 0.01 + 0.5;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_g = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].tint_b = (float)(iVar7 % 0x32) * 0.001 + 0.6
                                ;
                                iVar7 = crt_rand();
                                (&creature_pool)[iVar6].contact_damage = (float)(iVar7 % 0x23) + 8.0
                                ;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x24) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 20.0;
                                (&creature_pool)[iVar6].move_speed = 2.0;
                                (&creature_pool)[iVar6].reward_value = 110.0;
                                (&creature_pool)[iVar6].tint_r = 0.1;
                                (&creature_pool)[iVar6].tint_g = 0.7;
                                (&creature_pool)[iVar6].tint_b = 0.11;
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].size = 50.0;
                                (&creature_pool)[iVar6].contact_damage = 4.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x25) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 25.0;
                                (&creature_pool)[iVar6].move_speed = 2.5;
                                (&creature_pool)[iVar6].reward_value = 125.0;
                                (&creature_pool)[iVar6].tint_r = 0.1;
                                (&creature_pool)[iVar6].tint_g = 0.8;
                                (&creature_pool)[iVar6].tint_b = 0.11;
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].size = 30.0;
                                (&creature_pool)[iVar6].contact_damage = 3.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x26) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 50.0;
                                (&creature_pool)[iVar6].move_speed = 2.2;
                                (&creature_pool)[iVar6].reward_value = 125.0;
                                (&creature_pool)[iVar6].tint_r = 0.6;
                                (&creature_pool)[iVar6].tint_g = 0.8;
                                (&creature_pool)[iVar6].tint_b = 0.6;
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                (&creature_pool)[iVar6].size = 45.0;
                                (&creature_pool)[iVar6].contact_damage = 10.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x27) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 50.0;
                                (&creature_pool)[iVar6].move_speed = 2.1;
                                (&creature_pool)[iVar6].flags = 0x400;
                                (&creature_pool)[iVar6].reward_value = 125.0;
                                (&creature_pool)[iVar6].tint_r = 1.0;
                                (&creature_pool)[iVar6].tint_g = 0.8;
                                (&creature_pool)[iVar6].tint_b = 0.1;
                                (&creature_pool)[iVar6].tint_a = 1.0;
                                *(undefined2 *)&(&creature_pool)[iVar6].link_index = 3;
                                *(undefined2 *)((int)&(&creature_pool)[iVar6].link_index + 2) = 5;
                                (&creature_pool)[iVar6].size = 45.0;
                                (&creature_pool)[iVar6].contact_damage = 10.0;
                                goto LAB_004310b8;
                              }
                              if (template_id == 0x21) {
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 53.0;
                                (&creature_pool)[iVar6].move_speed = 1.7;
                                (&creature_pool)[iVar6].reward_value = 120.0;
                                (&creature_pool)[iVar6].tint_r = 0.7;
                                (&creature_pool)[iVar6].tint_g = 0.1;
                                (&creature_pool)[iVar6].tint_b = 0.51;
                                local_4 = 0.5;
                              }
                              else {
                                if (template_id == 0x22) {
                                  (&creature_pool)[iVar6].type_id = 2;
                                  (&creature_pool)[iVar6].health = 25.0;
                                  (&creature_pool)[iVar6].move_speed = 1.7;
                                  (&creature_pool)[iVar6].reward_value = 150.0;
                                  (&creature_pool)[iVar6].tint_r = 0.1;
                                  (&creature_pool)[iVar6].tint_g = 0.7;
                                  (&creature_pool)[iVar6].tint_b = 0.51;
                                  (&creature_pool)[iVar6].tint_a = 0.05;
                                  (&creature_pool)[iVar6].size = 50.0;
                                  (&creature_pool)[iVar6].contact_damage = 8.0;
                                  goto LAB_004310b8;
                                }
                                if (template_id == 0x23) {
                                  (&creature_pool)[iVar6].type_id = 2;
                                  (&creature_pool)[iVar6].health = 5.0;
                                  (&creature_pool)[iVar6].move_speed = 1.7;
                                  (&creature_pool)[iVar6].reward_value = 180.0;
                                  (&creature_pool)[iVar6].tint_r = 0.1;
                                  (&creature_pool)[iVar6].tint_g = 0.7;
                                  (&creature_pool)[iVar6].tint_b = 0.51;
                                  (&creature_pool)[iVar6].tint_a = 0.04;
                                  (&creature_pool)[iVar6].size = 45.0;
                                  (&creature_pool)[iVar6].contact_damage = 8.0;
                                  goto LAB_004310b8;
                                }
                                if (template_id != 0x28) {
                                  if (template_id == 0x29) {
                                    (&creature_pool)[iVar6].type_id = 2;
                                    (&creature_pool)[iVar6].health = 800.0;
                                    (&creature_pool)[iVar6].move_speed = 2.5;
                                    (&creature_pool)[iVar6].reward_value = 450.0;
                                    (&creature_pool)[iVar6].tint_r = 0.8;
                                    (&creature_pool)[iVar6].tint_g = 0.8;
                                    (&creature_pool)[iVar6].tint_b = 0.8;
                                    (&creature_pool)[iVar6].tint_a = 1.0;
                                    (&creature_pool)[iVar6].size = 70.0;
                                    (&creature_pool)[iVar6].contact_damage = 20.0;
                                    goto LAB_004310b8;
                                  }
                                  if (template_id == 0x2a) {
                                    (&creature_pool)[iVar6].type_id = 2;
                                    (&creature_pool)[iVar6].health = 50.0;
                                    (&creature_pool)[iVar6].move_speed = 3.1;
                                    (&creature_pool)[iVar6].reward_value = 300.0;
                                    (&creature_pool)[iVar6].tint_r = 0.3;
                                    (&creature_pool)[iVar6].tint_g = 0.3;
                                    (&creature_pool)[iVar6].tint_b = 0.3;
                                    (&creature_pool)[iVar6].tint_a = 1.0;
                                    (&creature_pool)[iVar6].size = 60.0;
                                    (&creature_pool)[iVar6].contact_damage = 8.0;
                                    goto LAB_004310b8;
                                  }
                                  if (template_id == 0x2b) {
                                    (&creature_pool)[iVar6].type_id = 2;
                                    (&creature_pool)[iVar6].health = 30.0;
                                    (&creature_pool)[iVar6].move_speed = 3.6;
                                    (&creature_pool)[iVar6].reward_value = 450.0;
                                    (&creature_pool)[iVar6].tint_r = 1.0;
                                    (&creature_pool)[iVar6].tint_g = 0.3;
                                    (&creature_pool)[iVar6].tint_b = 0.3;
                                  }
                                  else {
                                    if (template_id == 0x2c) {
                                      (&creature_pool)[iVar6].type_id = 2;
                                      (&creature_pool)[iVar6].health = 3800.0;
                                      (&creature_pool)[iVar6].move_speed = 2.0;
                                      (&creature_pool)[iVar6].reward_value = 1500.0;
                                      (&creature_pool)[iVar6].tint_r = 0.85;
                                      (&creature_pool)[iVar6].tint_g = 0.2;
                                      (&creature_pool)[iVar6].tint_b = 0.2;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 80.0;
                                      (&creature_pool)[iVar6].contact_damage = 40.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x2d) {
                                      (&creature_pool)[iVar6].type_id = 2;
                                      (&creature_pool)[iVar6].health = 45.0;
                                      (&creature_pool)[iVar6].move_speed = 3.1;
                                      (&creature_pool)[iVar6].reward_value = 200.0;
                                      (&creature_pool)[iVar6].tint_r = 0.0;
                                      (&creature_pool)[iVar6].tint_g = 0.9;
                                      (&creature_pool)[iVar6].tint_b = 0.8;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 38.0;
                                      (&creature_pool)[iVar6].contact_damage = 3.0;
                                      (&creature_pool)[iVar6].ai_mode = 2;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x2f) {
                                      (&creature_pool)[iVar6].type_id = 1;
                                      (&creature_pool)[iVar6].health = 20.0;
                                      (&creature_pool)[iVar6].move_speed = 2.5;
                                      (&creature_pool)[iVar6].reward_value = 150.0;
                                      (&creature_pool)[iVar6].tint_r = 0.8;
                                      (&creature_pool)[iVar6].tint_g = 0.8;
                                      (&creature_pool)[iVar6].tint_b = 0.8;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 45.0;
                                      (&creature_pool)[iVar6].contact_damage = 4.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x30) {
                                      (&creature_pool)[iVar6].type_id = 1;
                                      (&creature_pool)[iVar6].health = 1000.0;
                                      (&creature_pool)[iVar6].move_speed = 2.0;
                                      (&creature_pool)[iVar6].reward_value = 400.0;
                                      (&creature_pool)[iVar6].tint_r = 0.9;
                                      (&creature_pool)[iVar6].tint_g = 0.8;
                                      (&creature_pool)[iVar6].tint_b = 0.1;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 65.0;
                                      (&creature_pool)[iVar6].contact_damage = 10.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x3b) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].health = 1200.0;
                                      (&creature_pool)[iVar6].move_speed = 2.0;
                                      (&creature_pool)[iVar6].reward_value = 4000.0;
                                      (&creature_pool)[iVar6].tint_r = 0.9;
                                      (&creature_pool)[iVar6].tint_g = 0.0;
                                      (&creature_pool)[iVar6].tint_b = 0.0;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 70.0;
                                      (&creature_pool)[iVar6].contact_damage = 20.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x3c) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].flags = 0x100;
                                      (&creature_pool)[iVar6].orbit_angle = 0.4;
                                      (&creature_pool)[iVar6].orbit_radius.projectile_type =
                                           PROJECTILE_TYPE_SPIDER_PLASMA;
                                      (&creature_pool)[iVar6].health = 200.0;
                                      (&creature_pool)[iVar6].move_speed = 2.0;
                                      (&creature_pool)[iVar6].reward_value = 200.0;
                                      (&creature_pool)[iVar6].tint_r = 0.9;
                                      (&creature_pool)[iVar6].tint_g = 0.1;
                                      (&creature_pool)[iVar6].tint_b = 0.1;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 40.0;
                                      (&creature_pool)[iVar6].contact_damage = 20.0;
                                      (&creature_pool)[iVar6].ai_mode = 2;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x3d) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].health = 70.0;
                                      (&creature_pool)[iVar6].move_speed = 2.6;
                                      (&creature_pool)[iVar6].reward_value = 120.0;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      iVar7 = crt_rand();
                                      fVar4 = (float)(iVar7 % 0x14) * 0.01 + 0.8;
                                      (&creature_pool)[iVar6].tint_r = fVar4;
                                      (&creature_pool)[iVar6].tint_b = fVar4;
                                      (&creature_pool)[iVar6].tint_g = fVar4;
                                      iVar7 = crt_rand();
                                      fVar4 = (float)(iVar7 % 7 + 0x2d);
                                      (&creature_pool)[iVar6].size = fVar4;
                                      (&creature_pool)[iVar6].contact_damage = fVar4 * 0.22;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x3e) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].health = 1000.0;
                                      (&creature_pool)[iVar6].move_speed = 2.8;
                                      (&creature_pool)[iVar6].reward_value = 500.0;
                                      (&creature_pool)[iVar6].tint_r = 1.0;
                                      (&creature_pool)[iVar6].tint_g = 1.0;
                                      (&creature_pool)[iVar6].tint_b = 1.0;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 64.0;
                                      (&creature_pool)[iVar6].contact_damage = 40.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0) {
                                      (&creature_pool)[iVar6].type_id = 0;
                                      (&creature_pool)[iVar6].flags = 0x44;
                                      (&creature_pool)[iVar6].health = 8500.0;
                                      (&creature_pool)[iVar6].move_speed = 1.3;
                                      (&creature_pool)[iVar6].reward_value = 6600.0;
                                      (&creature_pool)[iVar6].tint_r = 0.6;
                                      (&creature_pool)[iVar6].tint_g = 0.6;
                                      (&creature_pool)[iVar6].tint_b = 1.0;
                                      (&creature_pool)[iVar6].tint_a = 0.8;
                                      (&creature_pool)[iVar6].size = 64.0;
                                      (&creature_pool)[iVar6].contact_damage = 50.0;
                                      iVar7 = creature_spawn_slot_alloc();
                                      (&creature_pool)[iVar6].link_index = iVar7;
                                      (&creature_spawn_slot_table)[iVar7].timer_s = 1.0;
                                      (&creature_spawn_slot_table)[iVar7].count = 0;
                                      (&creature_spawn_slot_table)[iVar7].limit = 0x32c;
                                      (&creature_spawn_slot_table)[iVar7].interval_s = 0.7;
                                      (&creature_spawn_slot_table)[iVar7].template_id = 0x41;
                                      (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x38) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].flags = 0x80;
                                      (&creature_pool)[iVar6].link_index = 0;
                                      (&creature_pool)[iVar6].health = 50.0;
                                      (&creature_pool)[iVar6].move_speed = 4.8;
                                      (&creature_pool)[iVar6].reward_value = 433.0;
                                      (&creature_pool)[iVar6].tint_r = 1.0;
                                      (&creature_pool)[iVar6].tint_g = 0.75;
                                      (&creature_pool)[iVar6].tint_b = 0.1;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      uVar9 = crt_rand();
                                      uVar9 = uVar9 & 0x80000003;
                                      if ((int)uVar9 < 0) {
                                        uVar9 = (uVar9 - 1 | 0xfffffffc) + 1;
                                      }
                                      (&creature_pool)[iVar6].size = (float)(int)(uVar9 + 0x29);
                                      (&creature_pool)[iVar6].contact_damage = 10.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x37) {
                                      (&creature_pool)[iVar6].type_id = 4;
                                      (&creature_pool)[iVar6].flags = 0x100;
                                      (&creature_pool)[iVar6].link_index = 0;
                                      (&creature_pool)[iVar6].health = 50.0;
                                      (&creature_pool)[iVar6].move_speed = 3.2;
                                      (&creature_pool)[iVar6].reward_value = 433.0;
                                      (&creature_pool)[iVar6].tint_r = 1.0;
                                      (&creature_pool)[iVar6].tint_g = 0.75;
                                      (&creature_pool)[iVar6].tint_b = 0.1;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      uVar9 = crt_rand();
                                      uVar9 = uVar9 & 0x80000003;
                                      if ((int)uVar9 < 0) {
                                        uVar9 = (uVar9 - 1 | 0xfffffffc) + 1;
                                      }
                                      (&creature_pool)[iVar6].size = (float)(int)(uVar9 + 0x29);
                                      (&creature_pool)[iVar6].contact_damage = 10.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x39) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].flags = 0x80;
                                      (&creature_pool)[iVar6].link_index = 0;
                                      (&creature_pool)[iVar6].health = 4.0;
                                      (&creature_pool)[iVar6].move_speed = 4.8;
                                      (&creature_pool)[iVar6].reward_value = 50.0;
                                      (&creature_pool)[iVar6].tint_r = 0.8;
                                      (&creature_pool)[iVar6].tint_g = 0.65;
                                      (&creature_pool)[iVar6].tint_b = 0.1;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      uVar9 = crt_rand();
                                      uVar9 = uVar9 & 0x80000003;
                                      if ((int)uVar9 < 0) {
                                        uVar9 = (uVar9 - 1 | 0xfffffffc) + 1;
                                      }
                                      (&creature_pool)[iVar6].size = (float)(int)(uVar9 + 0x1a);
                                      (&creature_pool)[iVar6].contact_damage = 10.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id == 0x3a) {
                                      (&creature_pool)[iVar6].type_id = 3;
                                      (&creature_pool)[iVar6].flags = 0x10;
                                      (&creature_pool)[iVar6].orbit_angle = 0.9;
                                      (&creature_pool)[iVar6].orbit_radius.projectile_type =
                                           PROJECTILE_TYPE_PLASMA_RIFLE;
                                      (&creature_pool)[iVar6].health = 4500.0;
                                      (&creature_pool)[iVar6].move_speed = 2.0;
                                      (&creature_pool)[iVar6].reward_value = 4500.0;
                                      (&creature_pool)[iVar6].tint_r = 1.0;
                                      (&creature_pool)[iVar6].tint_g = 1.0;
                                      (&creature_pool)[iVar6].tint_b = 1.0;
                                      (&creature_pool)[iVar6].tint_a = 1.0;
                                      (&creature_pool)[iVar6].size = 64.0;
                                      (&creature_pool)[iVar6].contact_damage = 50.0;
                                      goto LAB_004310b8;
                                    }
                                    if (template_id != 0x3f) {
                                      if (template_id == 0x40) {
                                        (&creature_pool)[iVar6].type_id = 3;
                                        (&creature_pool)[iVar6].health = 70.0;
                                        (&creature_pool)[iVar6].move_speed = 2.2;
                                        (&creature_pool)[iVar6].reward_value = 160.0;
                                        (&creature_pool)[iVar6].tint_r = 0.5;
                                        (&creature_pool)[iVar6].tint_g = 0.6;
                                        (&creature_pool)[iVar6].tint_b = 0.9;
                                        (&creature_pool)[iVar6].tint_a = 1.0;
                                        (&creature_pool)[iVar6].size = 45.0;
                                        (&creature_pool)[iVar6].contact_damage = 5.0;
                                        goto LAB_004310b8;
                                      }
                                      if (template_id == 0x42) {
                                        (&creature_pool)[iVar6].type_id = 0;
                                        (&creature_pool)[iVar6].health = 200.0;
                                        (&creature_pool)[iVar6].move_speed = 1.7;
                                        (&creature_pool)[iVar6].reward_value = 160.0;
                                        (&creature_pool)[iVar6].tint_r = 0.9;
                                        (&creature_pool)[iVar6].tint_g = 0.9;
                                        (&creature_pool)[iVar6].tint_b = 0.9;
                                        (&creature_pool)[iVar6].tint_a = 1.0;
                                        (&creature_pool)[iVar6].size = 45.0;
                                        (&creature_pool)[iVar6].contact_damage = 15.0;
                                        goto LAB_004310b8;
                                      }
                                      if (template_id == 0x43) {
                                        (&creature_pool)[iVar6].type_id = 0;
                                        (&creature_pool)[iVar6].health = 2000.0;
                                        (&creature_pool)[iVar6].move_speed = 2.1;
                                        (&creature_pool)[iVar6].reward_value = 460.0;
                                        (&creature_pool)[iVar6].tint_r = 0.2;
                                        (&creature_pool)[iVar6].tint_g = 0.6;
                                        (&creature_pool)[iVar6].tint_b = 0.1;
                                        (&creature_pool)[iVar6].tint_a = 1.0;
                                        (&creature_pool)[iVar6].size = 70.0;
                                        (&creature_pool)[iVar6].contact_damage = 15.0;
                                        goto LAB_004310b8;
                                      }
                                      goto LAB_00431094;
                                    }
                                    (&creature_pool)[iVar6].type_id = 3;
                                    (&creature_pool)[iVar6].health = 200.0;
                                    (&creature_pool)[iVar6].move_speed = 2.3;
                                    (&creature_pool)[iVar6].reward_value = 210.0;
                                    (&creature_pool)[iVar6].tint_r = 0.7;
                                    (&creature_pool)[iVar6].tint_g = 0.4;
                                    (&creature_pool)[iVar6].tint_b = 0.1;
                                  }
                                  (&creature_pool)[iVar6].tint_a = 1.0;
                                  (&creature_pool)[iVar6].size = 35.0;
                                  (&creature_pool)[iVar6].contact_damage = 20.0;
                                  goto LAB_004310b8;
                                }
                                (&creature_pool)[iVar6].type_id = 2;
                                (&creature_pool)[iVar6].health = 50.0;
                                (&creature_pool)[iVar6].move_speed = 1.7;
                                (&creature_pool)[iVar6].reward_value = 150.0;
                                (&creature_pool)[iVar6].tint_r = 0.7;
                                local_4 = 1.0;
                                (&creature_pool)[iVar6].tint_g = 0.1;
                                (&creature_pool)[iVar6].tint_b = 0.51;
                              }
                              (&creature_pool)[iVar6].tint_a = local_4;
                              (&creature_pool)[iVar6].size = 55.0;
                              (&creature_pool)[iVar6].contact_damage = 8.0;
                              goto LAB_004310b8;
                            }
                            (&creature_pool)[iVar6].type_id = 3;
                            iVar7 = crt_rand();
                            fVar4 = (float)(iVar7 % 0x19 + 0x28);
                            (&creature_pool)[iVar6].size = fVar4;
                            (&creature_pool)[iVar6].health = fVar4 + 10.0;
                            iVar7 = crt_rand();
                            (&creature_pool)[iVar6].tint_a = 1.0;
                            (&creature_pool)[iVar6].move_speed = (float)(iVar7 % 0x11) * 0.1 + 1.1;
                            (&creature_pool)[iVar6].reward_value =
                                 (&creature_pool)[iVar6].size + (&creature_pool)[iVar6].size + 50.0;
                            iVar7 = crt_rand();
                            fVar4 = (float)(iVar7 % 0x28) * 0.01 + 0.6;
                            (&creature_pool)[iVar6].tint_r = fVar4;
                            (&creature_pool)[iVar6].tint_g = fVar4;
                            (&creature_pool)[iVar6].tint_b = fVar4;
                          }
                          (&creature_pool)[iVar6].contact_damage =
                               (&creature_pool)[iVar6].size * 0.14 + 4.0;
                          goto LAB_004310b8;
                        }
                        (&creature_pool)[iVar6].type_id = 1;
                        (&creature_pool)[iVar6].size = 50.0;
                        (&creature_pool)[iVar6].ai_mode = 1;
                        (&creature_pool)[iVar6].health = 50.0;
                        (&creature_pool)[iVar6].move_speed = 2.4;
                        (&creature_pool)[iVar6].reward_value = 125.0;
                        (&creature_pool)[iVar6].tint_a = 1.0;
                        iVar7 = crt_rand();
                        fVar4 = (float)(iVar7 % 0x28);
                      }
                      fVar4 = fVar4 * 0.01 + 0.5;
                      (&creature_pool)[iVar6].tint_r = fVar4;
                      (&creature_pool)[iVar6].tint_g = fVar4;
                      (&creature_pool)[iVar6].tint_b = 1.0;
                      (&creature_pool)[iVar6].contact_damage = 5.0;
                      goto LAB_004310b8;
                    }
                    (&creature_pool)[iVar6].type_id = 2;
                    (&creature_pool)[iVar6].flags = 4;
                    iVar7 = creature_spawn_slot_alloc();
                    (&creature_pool)[iVar6].link_index = iVar7;
                    (&creature_spawn_slot_table)[iVar7].timer_s = 1.0;
                    (&creature_spawn_slot_table)[iVar7].count = 0;
                    (&creature_spawn_slot_table)[iVar7].limit = 100;
                    (&creature_spawn_slot_table)[iVar7].interval_s = 2.8;
                  }
                  (&creature_spawn_slot_table)[iVar7].template_id = 0x1d;
                  (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                  (&creature_pool)[iVar6].size = 50.0;
                  (&creature_pool)[iVar6].health = 1000.0;
                  (&creature_pool)[iVar6].move_speed = 2.0;
                  (&creature_pool)[iVar6].reward_value = 3000.0;
                  (&creature_pool)[iVar6].tint_a = 1.0;
                  (&creature_pool)[iVar6].tint_r = 1.0;
                  (&creature_pool)[iVar6].tint_g = 1.0;
                  (&creature_pool)[iVar6].tint_b = 1.0;
                  (&creature_pool)[iVar6].contact_damage = 0.0;
                  goto LAB_004310b8;
                }
                (&creature_pool)[iVar6].type_id = 2;
                (&creature_pool)[iVar6].flags = 4;
                iVar7 = creature_spawn_slot_alloc();
                (&creature_pool)[iVar6].link_index = iVar7;
                (&creature_spawn_slot_table)[iVar7].timer_s = 2.0;
                (&creature_spawn_slot_table)[iVar7].count = 0;
                (&creature_spawn_slot_table)[iVar7].limit = 100;
                (&creature_spawn_slot_table)[iVar7].interval_s = 6.0;
                (&creature_spawn_slot_table)[iVar7].template_id = 0x31;
                (&creature_spawn_slot_table)[iVar7].owner = pcVar10;
                (&creature_pool)[iVar6].size = 32.0;
                (&creature_pool)[iVar6].health = 50.0;
                (&creature_pool)[iVar6].move_speed = 1.3;
                (&creature_pool)[iVar6].reward_value = 1000.0;
              }
            }
            (&creature_pool)[iVar6].tint_a = 1.0;
            (&creature_pool)[iVar6].tint_r = 0.9;
            (&creature_pool)[iVar6].tint_g = 0.8;
            (&creature_pool)[iVar6].tint_b = 0.4;
            (&creature_pool)[iVar6].contact_damage = 0.0;
            goto LAB_004310b8;
          }
          (&creature_pool)[iVar6].type_id = 2;
          (&creature_pool)[iVar6].pos_x = *pos;
          (&creature_pool)[iVar6].pos_y = pos[1];
          (&creature_pool)[iVar6].type_id = 2;
          (&creature_pool)[iVar6].tint_r = 0.66499996;
          (&creature_pool)[iVar6].tint_g = 0.385;
          (&creature_pool)[iVar6].ai_mode = 0;
          (&creature_pool)[iVar6].health = 20.0;
          (&creature_pool)[iVar6].tint_b = 0.259;
          (&creature_pool)[iVar6].move_speed = 2.9;
          (&creature_pool)[iVar6].reward_value = 60.0;
          (&creature_pool)[iVar6].tint_a = 0.56;
          (&creature_pool)[iVar6].size = 50.0;
          (&creature_pool)[iVar6].contact_damage = 35.0;
          (&creature_pool)[iVar6].max_health = 20.0;
        }
        goto LAB_00431094;
      }
      (&creature_pool)[iVar6].type_id = 2;
      iVar7 = terrain_texture_height / 2;
      (&creature_pool)[iVar6].ai_mode = 2;
      (&creature_pool)[iVar6].pos_x = -10.0;
      fVar11 = (float10)fcos((float10)0.0);
      (&creature_pool)[iVar6].tint_r = 0.6;
      (&creature_pool)[iVar6].pos_y = (float)iVar7;
      (&creature_pool)[iVar6].tint_g = 0.8;
      (&creature_pool)[iVar6].tint_b = 0.91;
      (&creature_pool)[iVar6].health = 200.0;
      (&creature_pool)[iVar6].move_speed = 2.0;
      (&creature_pool)[iVar6].reward_value = 600.0;
      (&creature_pool)[iVar6].tint_a = 1.0;
      (&creature_pool)[iVar6].size = 40.0;
      (&creature_pool)[iVar6].contact_damage = 20.0;
      pos = (float *)0x2;
      fVar12 = (float10)fsin((float10)0.0);
      fVar4 = *pfVar5;
      fVar1 = pfVar5[1];
      (&creature_pool)[iVar6].max_health = 200.0;
      (&creature_pool)[iVar6].pos_x = (float)(fVar11 * (float10)256.0 + (float10)fVar4);
      (&creature_pool)[iVar6].ai_mode = 6;
      (&creature_pool)[iVar6].pos_y = (float)fVar12 * 256.0 + fVar1;
      iVar7 = iVar6;
      do {
        iVar8 = creature_alloc_slot();
        fVar11 = (float10)fcos((float10)(int)pos * (float10)0.34906587);
        pcVar10 = &creature_pool + iVar8;
        (&creature_pool)[iVar8].ai_mode = 6;
        (&creature_pool)[iVar8].link_index = iVar7;
        (&creature_pool)[iVar8].orbit_angle = 3.1415927;
        (&creature_pool)[iVar8].orbit_radius.projectile_type = 0x41200000;
        fVar12 = (float10)fsin((float10)(int)pos * (float10)0.34906587);
        fVar4 = pfVar5[1];
        (&creature_pool)[iVar8].pos_x = (float)fVar11 * 256.0 + *pfVar5;
        (&creature_pool)[iVar8].vel_x = 0.0;
        (&creature_pool)[iVar8].health = 60.0;
        (&creature_pool)[iVar8].pos_y = (float)(fVar12 * (float10)256.0 + (float10)fVar4);
        (&creature_pool)[iVar8].vel_y = 0.0;
        (&creature_pool)[iVar8].reward_value = 60.0;
        (&creature_pool)[iVar8].max_health = 60.0;
        (&creature_pool)[iVar8].tint_r = 0.4;
        pos = (float *)((int)pos + 2);
        (&creature_pool)[iVar8].tint_g = 0.7;
        (&creature_pool)[iVar8].collision_flag = '\0';
        (&creature_pool)[iVar8].tint_b = 0.11;
        (&creature_pool)[iVar8].collision_timer = 0.0;
        pcVar10->active = '\x01';
        (&creature_pool)[iVar8].tint_a = 1.0;
        (&creature_pool)[iVar8].state_flag = '\x01';
        (&creature_pool)[iVar8].hitbox_size = 16.0;
        (&creature_pool)[iVar8].attack_cooldown = 0.0;
        (&creature_pool)[iVar8].type_id = 2;
        (&creature_pool)[iVar8].move_speed = 2.0;
        (&creature_pool)[iVar8].size = 50.0;
        (&creature_pool)[iVar8].contact_damage = 4.0;
        iVar7 = iVar8;
      } while ((int)pos < 0x16);
    }
    (&creature_pool)[iVar6].link_index = iVar8;
  }
LAB_00431094:
  pcVar10->type_id = 2;
  pcVar10->health = 20.0;
  console_printf(&console_log_queue,s_Unhandled_creatureType__00477758);
LAB_004310b8:
  if ((((demo_mode_active == '\0') && (0.0 < pcVar10->pos_x)) &&
      (pcVar10->pos_x < (float)terrain_texture_width)) &&
     ((0.0 < pcVar10->pos_y && (pcVar10->pos_y < (float)terrain_texture_height)))) {
    effect_spawn_burst(&pcVar10->pos_x,8);
  }
  pcVar10->max_health = pcVar10->health;
  uVar9 = pcVar10->flags;
  if ((((uVar9 & 0x10) == 0) && (pcVar10->type_id == 3)) && ((uVar9 & 0x80) == 0)) {
    pcVar10->flags = uVar9 | 0x80;
    pcVar10->link_index = 0;
    pcVar10->move_speed = pcVar10->move_speed * 1.2;
  }
  if ((template_id == 0x38) && (config_blob.hardcore != '\0')) {
    pcVar10->move_speed = pcVar10->move_speed * 0.7;
  }
  pcVar10->heading = heading;
  if ((config_blob.hardcore == '\0') &&
     (((pcVar10->flags & 4) == 0 ||
      ((&creature_spawn_slot_table)[pcVar10->link_index].interval_s =
            (&creature_spawn_slot_table)[pcVar10->link_index].interval_s + 0.2,
      config_blob.hardcore == '\0')))) {
    if (0 < quest_fail_retry_count) {
      switch(quest_fail_retry_count) {
      case 1:
        pcVar10->reward_value = pcVar10->reward_value * 0.9;
        pcVar10->move_speed = pcVar10->move_speed * 0.95;
        pcVar10->contact_damage = pcVar10->contact_damage * 0.95;
        fVar4 = pcVar10->health * 0.95;
        break;
      case 2:
        pcVar10->reward_value = pcVar10->reward_value * 0.85;
        pcVar10->move_speed = pcVar10->move_speed * 0.9;
        pcVar10->contact_damage = pcVar10->contact_damage * 0.9;
        fVar4 = pcVar10->health * 0.9;
        break;
      case 3:
        pcVar10->reward_value = pcVar10->reward_value * 0.85;
        pcVar10->move_speed = pcVar10->move_speed * 0.8;
        pcVar10->contact_damage = pcVar10->contact_damage * 0.8;
        fVar4 = pcVar10->health * 0.8;
        break;
      case 4:
        pcVar10->reward_value = pcVar10->reward_value * 0.8;
        pcVar10->move_speed = pcVar10->move_speed * 0.7;
        pcVar10->contact_damage = pcVar10->contact_damage * 0.7;
        fVar4 = pcVar10->health * 0.7;
        break;
      default:
        pcVar10->reward_value = pcVar10->reward_value * 0.8;
        pcVar10->move_speed = pcVar10->move_speed * 0.6;
        pcVar10->contact_damage = pcVar10->contact_damage * 0.5;
        fVar4 = pcVar10->health * 0.5;
      }
      pcVar10->health = fVar4;
      if ((pcVar10->flags & 4) != 0) {
        fVar4 = (float)quest_fail_retry_count * 0.35;
        if (3.0 < fVar4) {
          fVar4 = 3.0;
        }
        (&creature_spawn_slot_table)[pcVar10->link_index].interval_s =
             fVar4 + (&creature_spawn_slot_table)[pcVar10->link_index].interval_s;
      }
    }
  }
  else {
    quest_fail_retry_count = 0;
    pcVar10->move_speed = pcVar10->move_speed * 1.05;
    pcVar10->contact_damage = pcVar10->contact_damage * 1.4;
    pcVar10->health = pcVar10->health * 1.2;
    if ((pcVar10->flags & 4) != 0) {
      iVar6 = pcVar10->link_index;
      fVar4 = (&creature_spawn_slot_table)[iVar6].interval_s - 0.2;
      (&creature_spawn_slot_table)[iVar6].interval_s = fVar4;
      if (fVar4 < 0.1) {
        (&creature_spawn_slot_table)[iVar6].interval_s = 0.1;
        return pcVar10;
      }
    }
  }
  return pcVar10;
}



/* creature_spawn_tinted @ 00444810 */

/* spawns a creature with tint and default stats */

int __cdecl creature_spawn_tinted(float *pos,float *rgba,int type_id)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = creature_alloc_slot();
  (&creature_pool)[iVar3].pos_x = *pos;
  (&creature_pool)[iVar3].pos_y = pos[1];
  (&creature_pool)[iVar3].active = '\x01';
  (&creature_pool)[iVar3].state_flag = '\x01';
  (&creature_pool)[iVar3].vel_x = 0.0;
  (&creature_pool)[iVar3].ai_mode = 2;
  (&creature_pool)[iVar3].collision_flag = '\0';
  (&creature_pool)[iVar3].collision_timer = 0.0;
  (&creature_pool)[iVar3].type_id = type_id;
  *(undefined1 *)&(&creature_pool)[iVar3].force_target = 0;
  (&creature_pool)[iVar3].hitbox_size = 16.0;
  (&creature_pool)[iVar3].health = 1.0;
  (&creature_pool)[iVar3].vel_y = 0.0;
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].move_speed = 1.7;
  (&creature_pool)[iVar3].reward_value = 1.0;
  (&creature_pool)[iVar3].attack_cooldown = 0.0;
  (&creature_pool)[iVar3].heading = (float)(iVar4 % 0x13a) * 0.01;
  (&creature_pool)[iVar3].tint_r = *rgba;
  (&creature_pool)[iVar3].tint_g = rgba[1];
  (&creature_pool)[iVar3].tint_b = rgba[2];
  (&creature_pool)[iVar3].tint_a = rgba[3];
  iVar4 = crt_rand();
  (&creature_pool)[iVar3].contact_damage = 100.0;
  (&creature_pool)[iVar3].max_health = (&creature_pool)[iVar3].health;
  fVar2 = (float)(iVar4 % 0x14) + 47.0;
  (&creature_pool)[iVar3].size = fVar2;
  if ((type_id != 3) && (type_id != 4)) {
    return iVar3;
  }
  fVar1 = (&creature_pool)[iVar3].move_speed;
  (&creature_pool)[iVar3].flags = (&creature_pool)[iVar3].flags | 0x80;
  (&creature_pool)[iVar3].move_speed = fVar1 * 1.2;
  (&creature_pool)[iVar3].size = fVar2 * 0.8;
  return iVar3;
}



/* creature_name_get_part @ 00444f70 */

char * __cdecl creature_name_get_part(char param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0x34;
  if (param_1 == '\0') {
    iVar2 = 0x33;
  }
  iVar1 = crt_rand();
  switch(iVar1 % iVar2) {
  case 0:
    return &s_creature_name_part_00;
  case 1:
    return &s_creature_name_part_01;
  case 2:
    return &s_creature_name_part_02;
  case 3:
    return &s_creature_name_part_03;
  case 4:
    return &s_creature_name_part_04;
  case 5:
    return &s_creature_name_part_05;
  case 6:
    return &s_creature_name_part_06;
  case 7:
    return &s_creature_name_part_07;
  case 8:
    return &s_creature_name_part_08;
  case 9:
    return &s_creature_name_part_09;
  case 10:
    return &s_creature_name_part_10;
  case 0xb:
    return &s_creature_name_part_11;
  case 0xc:
    return &s_creature_name_part_12;
  case 0xd:
    return &s_creature_name_part_13;
  case 0xe:
    return &s_creature_name_part_14;
  case 0xf:
    return &s_creature_name_part_15;
  case 0x10:
    return &s_creature_name_part_16;
  case 0x11:
    return &s_creature_name_part_17;
  case 0x12:
    return &s_creature_name_part_18;
  case 0x13:
    return &s_creature_name_part_19;
  case 0x14:
    return &s_creature_name_part_20;
  case 0x15:
    return &DAT_00478d70;
  case 0x16:
    return &DAT_00478d68;
  case 0x17:
    return &DAT_00478d64;
  case 0x18:
    return s_harry_00478d5c;
  case 0x19:
    return &DAT_00478d58;
  case 0x1a:
    return &DAT_00478d54;
  case 0x1b:
    return &DAT_00478d4c;
  case 0x1c:
    return &DAT_00478d44;
  case 0x1d:
    return &DAT_00478d3c;
  case 0x1e:
    return s_quick_00478d34;
  case 0x1f:
    return s_brown_00478d2c;
  case 0x20:
    return &DAT_00478d28;
  case 0x21:
    return s_jumper_00478d20;
  case 0x22:
    return &DAT_00478d18;
  case 0x23:
    return &DAT_00478d10;
  case 0x24:
    return &DAT_00478d0c;
  case 0x25:
    return &DAT_00478d04;
  case 0x26:
    return s_unique_00478cfc;
  default:
    return &DAT_00478c98;
  case 0x28:
    return &DAT_00478cf4;
  case 0x29:
    return s_sleep_00478cec;
  case 0x2a:
    return &DAT_00478ce4;
  case 0x2b:
    return &DAT_00478cdc;
  case 0x2c:
    return &DAT_00478cd4;
  case 0x2d:
    return s_below_00478ccc;
  case 0x2e:
    return s_scape_00478cc4;
  case 0x2f:
    return &DAT_00478cbc;
  case 0x30:
    return &DAT_00478cb4;
  case 0x31:
    return s_break_00478cac;
  case 0x32:
    return &DAT_00478ca4;
  case 0x33:
    return &DAT_00478ca0;
  }
}



/* creature_unique_name_get @ 004451b0 */

/* [binja] void* sub_4451b0() */

void * creature_unique_name_get(void)

{
  byte bVar1;
  char *pcVar2;
  highscore_record_t *phVar3;
  int iVar4;
  uint uVar5;
  void *pvVar6;
  void *this;
  void *extraout_ECX;
  uint uVar7;
  int iVar8;
  int iVar9;
  highscore_record_t *phVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  byte *pbVar13;
  highscore_record_t *phVar14;
  undefined4 *puVar15;
  bool bVar16;
  undefined4 *local_8;
  int local_4;
  
  if (creature_search_active == '\0') {
    highscore_load_table();
    iVar9 = 0;
    phVar10 = &highscore_table;
    local_4 = 0;
    local_8 = (undefined4 *)&creature_unique_name_table;
    do {
      pbVar12 = &creature_unique_name_table;
      iVar8 = 0;
      phVar3 = phVar10;
      pbVar13 = pbVar12;
      if (0x4d1228 < (int)local_8) {
LAB_004451ef:
        do {
          bVar1 = phVar3->player_name[0];
          bVar16 = bVar1 < *pbVar12;
          if (bVar1 == *pbVar12) {
            if (bVar1 != 0) {
              bVar1 = phVar3->player_name[1];
              bVar16 = bVar1 < pbVar12[1];
              if (bVar1 != pbVar12[1]) goto LAB_00445213;
              pbVar12 = pbVar12 + 2;
              phVar3 = (highscore_record_t *)(phVar3->player_name + 2);
              if (bVar1 != 0) goto LAB_004451ef;
            }
            iVar4 = 0;
          }
          else {
LAB_00445213:
            iVar4 = (1 - (uint)bVar16) - (uint)(bVar16 != 0);
          }
          iVar9 = local_4;
          if (iVar4 == 0) goto LAB_004452a7;
          iVar8 = iVar8 + 1;
          pbVar12 = pbVar13 + 0x20;
          phVar3 = phVar10;
          pbVar13 = pbVar12;
        } while (iVar8 < local_4);
      }
      uVar5 = 0xffffffff;
      iVar8 = 0;
      phVar3 = phVar10;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar2 = phVar3->player_name;
        phVar3 = (highscore_record_t *)(phVar3->player_name + 1);
      } while (*pcVar2 != '\0');
      pvVar6 = (void *)(~uVar5 - 1);
      this = pvVar6;
      if (0 < (int)pvVar6) {
        do {
          uVar5 = crt_isalpha(this,(int)phVar10->player_name[iVar8]);
          if ((uVar5 == 0) && (phVar10->player_name[iVar8] != '.')) goto LAB_004452a7;
          iVar8 = iVar8 + 1;
          this = extraout_ECX;
        } while (iVar8 < (int)pvVar6);
      }
      uVar5 = 0xffffffff;
      local_4 = iVar9 + 1;
      phVar3 = phVar10;
      do {
        phVar14 = phVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        phVar14 = (highscore_record_t *)(phVar3->player_name + 1);
        pcVar2 = phVar3->player_name;
        phVar3 = phVar14;
      } while (*pcVar2 != '\0');
      uVar5 = ~uVar5;
      puVar11 = (undefined4 *)((int)phVar14 - uVar5);
      puVar15 = local_8;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *puVar15 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar15 = puVar15 + 1;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined1 *)puVar15 = *(undefined1 *)puVar11;
        puVar11 = (undefined4 *)((int)puVar11 + 1);
        puVar15 = (undefined4 *)((int)puVar15 + 1);
      }
      console_printf(&console_log_queue,s_unique_name_fmt,local_4,phVar10);
      iVar9 = local_4;
      local_8 = local_8 + 8;
LAB_004452a7:
      phVar10 = phVar10 + 1;
    } while ((int)phVar10 < 0x484730);
    creature_search_active = '\x01';
    creature_unique_name_count = iVar9;
    if (iVar9 == 0) {
      crt_sprintf(&creature_unique_name_table,s_quickbrownfox_placeholder);
    }
  }
  if (creature_unique_name_count < 1) {
    return &creature_unique_name_table;
  }
  iVar9 = crt_rand();
  return &creature_unique_name_table + (iVar9 % creature_unique_name_count) * 0x20;
}



/* creature_is_name_unique @ 00445310 */

/* [binja] int32_t sub_445310(char* arg1, int32_t arg2) */

int __cdecl creature_is_name_unique(char *arg1,int arg2)

{
  byte bVar1;
  int in_EAX;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  creature_t *pcVar6;
  bool bVar7;
  
  iVar3 = 0;
  pbVar4 = &creature_name_buffer;
  pcVar6 = &creature_pool;
  do {
    if ((pcVar6->active != '\0') && (pbVar2 = pbVar4, pbVar5 = (byte *)arg1, iVar3 != arg2)) {
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00445355:
          in_EAX = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_0044535a;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00445355;
        pbVar2 = pbVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      in_EAX = 0;
LAB_0044535a:
      if (in_EAX == 0) {
        return 0;
      }
    }
    pcVar6 = pcVar6 + 1;
    iVar3 = iVar3 + 1;
    pbVar4 = pbVar4 + 0x40;
    if (0x4aa337 < (int)pcVar6) {
      return CONCAT31((int3)((uint)in_EAX >> 8),1);
    }
  } while( true );
}



/* creature_name_assign_random @ 00445380 */

/* builds a randomized creature name string into creature_name_buffer for debug overlays */

void __cdecl creature_name_assign_random(int creature_id)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  char *dst;
  int local_4;
  
  local_4 = 0;
  do {
    if ((int)highscore_active_record.score_xp < 0x79) {
LAB_0044544d:
      if ((((int)highscore_active_record.score_xp < 0x51) ||
          (iVar3 = crt_rand(), 0x4f < iVar3 % 100)) &&
         (((int)highscore_active_record.score_xp < 0x3d || (iVar3 = crt_rand(), 0x27 < iVar3 % 100))
         )) {
        if ((((int)highscore_active_record.score_xp < 0x29) ||
            (iVar3 = crt_rand(), 0x4f < iVar3 % 100)) &&
           (((int)highscore_active_record.score_xp < 0x15 ||
            (iVar3 = crt_rand(), 0x27 < iVar3 % 100)))) {
          dst = &creature_name_buffer + creature_id * 0x40;
          pcVar4 = creature_name_get_part('\0');
          crt_sprintf(dst,&s_fmt_percent_s,pcVar4);
        }
        else {
          dst = &creature_name_buffer + creature_id * 0x40;
          pcVar4 = creature_name_get_part('\0');
          pcVar5 = creature_name_get_part('\x01');
          crt_sprintf(dst,&s_name_double_fmt,pcVar5,pcVar4);
        }
      }
      else {
        dst = &creature_name_buffer + creature_id * 0x40;
        pcVar4 = creature_name_get_part('\0');
        pcVar5 = creature_name_get_part('\0');
        pcVar6 = creature_name_get_part('\x01');
        crt_sprintf(dst,s_name_triple_fmt,pcVar6,pcVar5,pcVar4);
      }
    }
    else {
      iVar3 = crt_rand();
      if (iVar3 % 100 < 10) {
        dst = &creature_name_buffer + creature_id * 0x40;
        pcVar4 = creature_unique_name_get();
        uVar8 = 0xffffffff;
        do {
          pcVar5 = pcVar4;
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          pcVar5 = pcVar4 + 1;
          cVar1 = *pcVar4;
          pcVar4 = pcVar5;
        } while (cVar1 != '\0');
        uVar8 = ~uVar8;
        pcVar4 = pcVar5 + -uVar8;
        pcVar5 = dst;
        for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
          pcVar4 = pcVar4 + 4;
          pcVar5 = pcVar5 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pcVar5 = *pcVar4;
          pcVar4 = pcVar4 + 1;
          pcVar5 = pcVar5 + 1;
        }
      }
      else {
        if (((int)highscore_active_record.score_xp < 0x79) ||
           (iVar3 = crt_rand(), 0x4f < iVar3 % 100)) goto LAB_0044544d;
        dst = &creature_name_buffer + creature_id * 0x40;
        pcVar4 = creature_name_get_part('\0');
        pcVar5 = creature_name_get_part('\0');
        pcVar6 = creature_name_get_part('\0');
        pcVar7 = creature_name_get_part('\x01');
        crt_sprintf(dst,s__s_s_s_s_00478e2c,pcVar7,pcVar6,pcVar5,pcVar4);
      }
    }
    iVar3 = creature_is_name_unique(dst,creature_id);
    if ((char)iVar3 != '\0') {
      uVar8 = 0xffffffff;
      do {
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        cVar1 = *dst;
        dst = dst + 1;
      } while (cVar1 != '\0');
      if ((~uVar8 - 1 < 0x10) || (bVar2 = 99 < local_4, local_4 = local_4 + 1, bVar2)) {
        return;
      }
    }
  } while( true );
}



/* creature_find_by_name @ 00445590 */

/* returns the first creature index whose name matches creature_name_buffer, or -1 */

int __cdecl creature_find_by_name(char *name)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  creature_t *pcVar7;
  bool bVar8;
  
  iVar2 = 0;
  pbVar5 = &creature_name_buffer;
  pcVar7 = &creature_pool;
  do {
    pbVar3 = pbVar5;
    pbVar6 = (byte *)name;
    if (pcVar7->active != '\0') {
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_004455cf:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_004455d4;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_004455cf;
        pbVar3 = pbVar3 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_004455d4:
      if (iVar4 == 0) {
        return iVar2;
      }
    }
    pcVar7 = pcVar7 + 1;
    iVar2 = iVar2 + 1;
    pbVar5 = pbVar5 + 0x40;
    if (0x4aa337 < (int)pcVar7) {
      return -1;
    }
  } while( true );
}



/* creature_name_draw_labels @ 00445600 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* debug overlay: draws creature name labels over world positions */

void creature_name_draw_labels(void)

{
  float fVar1;
  int iVar2;
  float x;
  float *pfVar3;
  char *text;
  float a;
  
  a = 1.0;
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  text = &creature_name_buffer;
  pfVar3 = &creature_pool.hitbox_size;
  do {
    if (((creature_t *)(pfVar3 + -4))->active != '\0') {
      iVar2 = (*grim_interface_ptr->vtable->grim_measure_text_width)(text);
      fVar1 = camera_offset_x + pfVar3[1];
      x = (float)(iVar2 + 8);
      (*grim_interface_ptr->vtable->grim_draw_rect_filled)
                ((float *)&stack0xffffffd4,(float)(int)x,15.0);
      (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,a);
      (*grim_interface_ptr->vtable->grim_draw_text_small)(x,fVar1 - (float)iVar2 * 0.5,text);
    }
    pfVar3 = pfVar3 + 0x26;
    text = text + 0x40;
  } while ((int)pfVar3 < 0x4aa348);
  return;
}


