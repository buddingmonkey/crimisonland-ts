/* weapon_table_entry @ 0041fc60 */

/* returns the entry base (&DAT_004d7a2c + weapon_id * 0x1f) */

char * __cdecl weapon_table_entry(int weapon_id)

{
  return (&weapon_table)[weapon_id].name;
}



/* weapon_table_init @ 004519b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* initializes the weapon stats table at DAT_004d7a28 */

void weapon_table_init(void)

{
  int iVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  
  iVar4 = 0;
  piVar3 = &weapon_table.pellet_count;
  do {
    iVar1 = iVar4 + -1;
    iVar4 = iVar4 + 1;
    piVar3[-4] = iVar1;
    *piVar3 = 1;
    piVar3 = piVar3 + 0x1f;
  } while ((int)piVar3 < 0x4d99a0);
  uVar5 = 0xffffffff;
  weapon_table.hud_icon_id = 0;
  pcVar7 = s_Fire_bullets_0047958c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d7ef4 = 0x41f00000;
  _DAT_004d7fec = 0x420c0000;
  _DAT_004d84c4 = 0x41700000;
  _DAT_004d8540 = 0x41a00000;
  _DAT_004d85bc = 0x41200000;
  _DAT_004d8828 = 0x41200000;
  _DAT_004d83cc = 0x41a00000;
  _DAT_004d7d80 = 0x43570000;
  _DAT_004d8e74 = 0x41700000;
  _DAT_004d8f6c = 0x41200000;
  _DAT_004d7c0c = 0x42700000;
  DAT_004d7b14 = 0x425c0000;
  _DAT_004d7b90 = 0x42480000;
  _DAT_004d86b4 = 0x41a00000;
  _DAT_004d86b8 = 0x41300000;
  DAT_004d9064 = 0x42700000;
  _DAT_004d9068 = 0x3e800000;
  _DAT_004d8730 = 0x41200000;
  _DAT_004d8734 = 0x3f000000;
  _DAT_004d7ef8 = 0x40a00000;
  _DAT_004d7ff0 = 0x40066666;
  _DAT_004d84c8 = 0x40400000;
  _DAT_004d8544 = 0x3fb33333;
  _DAT_004d85c0 = 0x4185999a;
  _DAT_004d882c = 0x41e00000;
  _DAT_004d83d0 = 0x3f800000;
  _DAT_004d8e78 = 0;
  _DAT_004d7c10 = 0x3f99999a;
  DAT_004d7b18 = 0x40833333;
  _DAT_004d863c = 0;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8ff8;
  for (uVar6 = uVar5 >> 2; _DAT_004d7b7c = sfx_autorifle_fire, uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; _DAT_004d7b08 = sfx_pistol_reload, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Pistol_00479584;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d9060 = 1;
  _DAT_004d903c = 0x70;
  weapon_default_shot_cooldown_single = 0x3e0f5c29;
  _DAT_004d9044 = 0x3f99999a;
  weapon_default_reload_delay = 0x3e6147ae;
  sfx_player_fire_reload_a = _DAT_004d7b7c;
  _DAT_004d9058 = sfx_pistol_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7aa8;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  DAT_004d7b10 = 5;
  weapon_default_clip_size = 0xc;
  _DAT_004d7af0 = 0x3f3631f9;
  weapon_default_reload_time = 0x3f99999a;
  _DAT_004d7af8 = 0x3e6147ae;
  _DAT_004d7b00 = sfx_pistol_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Assault_Rifle_00479574;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7b24;
  for (uVar6 = uVar5 >> 2; sfx_reload_default = sfx_shotgun_reload, uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; weapon_default_sfx_reload = sfx_autorifle_reload, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = &DAT_0047956c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d7b8c = 1;
  _DAT_004d7b68 = 0x19;
  _DAT_004d7b6c = 0x3def9db2;
  _DAT_004d7b70 = 0x3f99999a;
  _DAT_004d7b74 = 0x3db851ec;
  _DAT_004d7b84 = sfx_autorifle_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7ba0;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; _DAT_004d8434 = sfx_shotgun_fire, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d7be4 = 0xc;
  _DAT_004d7c14 = 0xc;
  uVar5 = 0xffffffff;
  _DAT_004d7c08 = 1;
  pcVar7 = s_Sawed_off_Shotgun_00479558;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  _DAT_004d7be8 = 0x3f59999a;
  uVar5 = ~uVar5;
  _DAT_004d7bec = 0x3ff33333;
  _DAT_004d7bf0 = 0x3e8a3d71;
  _DAT_004d7bf8 = sfx_shotgun_fire;
  _DAT_004d7c00 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7c1c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d7c60 = 0xc;
  _DAT_004d7c90 = 0xc;
  uVar5 = 0xffffffff;
  _DAT_004d7c84 = 1;
  pcVar7 = s_Jackhammer_0047954c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d7c64 = 0x3f5eb852;
  _DAT_004d7c68 = 0x3ff33333;
  _DAT_004d7c6c = 0x3e051eb8;
  _DAT_004d7c74 = _DAT_004d8434;
  _DAT_004d7c7c = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d83dc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Submachine_Gun_0047953c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8444 = 1;
  _DAT_004d8420 = 0x10;
  _DAT_004d8424 = 0x3e0f5c29;
  _DAT_004d8428 = 0x40400000;
  _DAT_004d842c = 0x3e23d70a;
  _DAT_004d8450 = 4;
  _DAT_004d843c = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7c98;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d7cf0 = sfx_hrpm_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Flamethrower_0047952c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d7d00 = 5;
  _DAT_004d7cdc = 0x1e;
  _DAT_004d7ce0 = 0x3db476b0;
  _DAT_004d7ce4 = 0x3f99999a;
  _DAT_004d7ce8 = 0x3da7ef9e;
  _DAT_004d7cf8 = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7e0c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d7e64 = sfx_flamer_fire_01;
  uVar5 = 0xffffffff;
  pcVar7 = s_Plasma_Rifle_0047951c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d7e74 = 8;
  _DAT_004d7e68 = 2;
  _DAT_004d7e50 = 0x1e;
  _DAT_004d7e54 = 0x3c04ec63;
  _DAT_004d7e58 = 0x40000000;
  _DAT_004d7e5c = 0x3c75c28f;
  _DAT_004d7e08 = 1;
  _DAT_004d7e6c = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7e88;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d7ecc = 0x14;
  _DAT_004d7ee0 = sfx_shock_fire;
  uVar5 = 0xffffffff;
  _DAT_004d7ed0 = 0x3e94e545;
  _DAT_004d7ed4 = 0x3f99999a;
  _DAT_004d7ed8 = 0x3e3a5e35;
  _DAT_004d7ee8 = weapon_default_sfx_reload;
  pcVar7 = s_Multi_Plasma_0047950c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7f04;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_plasma_minigun_sfx_fire = sfx_shock_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Plasma_Minigun_004794fc;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_plasma_minigun_clip = 8;
  weapon_plasma_minigun_fire_rate = 0x3f1eed84;
  weapon_plasma_minigun_damage = 0x3fb33333;
  weapon_plasma_minigun_spread = 0x3ea3d70a;
  weapon_plasma_minigun_type = 3;
  weapon_plasma_minigun_sfx_reload = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7f80;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  sfx_player_fire_reload_b = sfx_plasmaminigun_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Gauss_Gun_004794f0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_gauss_gun_clip = 0x1e;
  weapon_gauss_gun_fire_rate = 0x3de147ae;
  weapon_gauss_gun_damage = 0x3fa66666;
  weapon_gauss_gun_spread = 0x3dc6a7f0;
  weapon_gauss_gun_sfx_reload = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7d14;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_gauss_gun_sfx_fire = sfx_gauss_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Rocket_Launcher_004794e0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_rocket_launcher_type = 1;
  weapon_rocket_launcher_clip = 6;
  weapon_rocket_launcher_fire_rate = 0x3f19999a;
  weapon_rocket_launcher_damage = 0x3fcccccd;
  weapon_rocket_launcher_spread = 0x3ed70a3d;
  weapon_rocket_launcher_sfx_reload = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7ffc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_seeker_rockets_clip = 8;
  weapon_seeker_rockets_type = 5;
  weapon_seeker_rockets_fire_rate = 0x3f3da5d6;
  weapon_seeker_rockets_damage = 0x3f99999a;
  weapon_seeker_rockets_spread = 0x3ed70a3d;
  weapon_seeker_rockets_sfx_fire = sfx_rocket_fire;
  weapon_seeker_rockets_sfx_reload = sfx_autorifle_reload_alt;
  uVar5 = 0xffffffff;
  weapon_pistol_type = 2;
  pcVar7 = s_Seeker_Rockets_004794d0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8078;
  for (uVar6 = uVar5 >> 2; weapon_mean_minigun_sfx_reload = sfx_autorifle_reload_alt, uVar6 != 0; uVar6 = uVar6 - 1)
  {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_mean_minigun_sfx_fire = sfx_rocket_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Mean_Minigun_004794c0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_mean_minigun_clip = 8;
  weapon_mean_minigun_type = 8;
  weapon_mean_minigun_fire_rate = 0x3e9f22b6;
  weapon_mean_minigun_damage = 0x3f99999a;
  weapon_mean_minigun_spread = 0x3ea3d70a;
  weapon_mean_minigun_type = 2;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d7d90;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_plasma_shotgun_sfx_fire = sfx_autorifle_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Plasma_Shotgun_004794b0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_plasma_shotgun_type = 3;
  weapon_plasma_shotgun_clip = 0x78;
  weapon_plasma_shotgun_fire_rate = 0x3db851ec;
  weapon_plasma_shotgun_damage = 0x40800000;
  weapon_plasma_shotgun_spread = 0x3d7df3b6;
  _DAT_004d7df0 = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d80f4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_blow_torch_sfx_fire = sfx_plasmashotgun_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Blow_Torch_004794a4;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_blow_torch_type = 8;
  weapon_blow_torch_fire_rate = 0x3ef5c28f;
  weapon_blow_torch_damage = 0x40466666;
  weapon_blow_torch_spread = 0x3de147ae;
  weapon_blow_torch_clip = 0xe;
  _DAT_004d8154 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8170;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_hr_flamer_sfx_fire = sfx_flamer_fire_01;
  uVar5 = 0xffffffff;
  pcVar7 = s_HR_Flamer_00479498;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_hr_flamer_type = 8;
  weapon_hr_flamer_mode = 2;
  weapon_hr_flamer_clip = 0x1e;
  weapon_hr_flamer_fire_rate = 0x3bc84f90;
  weapon_hr_flamer_damage = 0x3fc00000;
  weapon_hr_flamer_spread = 0x3c23d70a;
  weapon_blow_torch_mode = 1;
  _DAT_004d81d0 = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d81ec;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8244 = sfx_flamer_fire_01;
  uVar5 = 0xffffffff;
  pcVar7 = s_Mini_Rocket_Swarmers_00479480;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8254 = 8;
  _DAT_004d8248 = 2;
  _DAT_004d8230 = 0x1e;
  _DAT_004d8234 = 0x3c0b4396;
  _DAT_004d8238 = 0x3fe66666;
  _DAT_004d823c = 0x3c23d70a;
  _DAT_004d81e8 = 1;
  _DAT_004d824c = weapon_default_sfx_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8268;
  for (uVar6 = uVar5 >> 2; _DAT_004d82c8 = sfx_autorifle_reload_alt, uVar6 != 0; uVar6 = uVar6 - 1)
  {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d82c0 = sfx_rocket_fire;

  /* ======================================================================
   * DECOMPILER MISATTRIBUTION WARNING — Weapons 18-23
   *
   * Weapon table layout: base=0x004d7a28, struct_size=0x7C (124 bytes)
   * shot_cooldown at struct offset 0x4C, damage at 0x50, spread at 0x54
   *
   * The decompiler named globals based on proximity to the NEXT weapon's
   * name string copy, but the globals are at the PREVIOUS weapon's struct
   * addresses. This causes a systematic off-by-one error.
   *
   * Pattern: Named globals between weapon N's name copy and weapon (N+1)'s
   *          name copy belong to weapon N's struct.
   * ====================================================================== */

  uVar5 = 0xffffffff;
  pcVar7 = s_Rocket_Minigun_00479470;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  /* --- W18 Rocket Minigun struct (base 0x004d82E0) --- */
  _DAT_004d82d0 = 8;       /* pellet_count (unused — handler fires 1) */
  _DAT_004d82ac = 5;       /* clip_size */
  _DAT_004d82b0 = 0x3fe66666; /* shot_cooldown = 1.8 (WRONG — see below) */
  weapon_autogun_damage = 0x3fe66666; /* W18 damage_scale = 1.8 */
  weapon_autogun_spread = 0x3df5c28f; /* W18 spread = 0.12 */
  weapon_autogun_projectile_type = 2;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d82e4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  /* --- MISATTRIBUTED: weapon_pulse_gun_* globals are actually W18 Rocket Minigun --- */
  /* These addresses fall within W18's struct (0x004d82E0), NOT Pulse Gun (W19). */
  weapon_pulse_gun_type = 8;          /* W18 weapon_type (misnamed) */
  weapon_pulse_gun_clip = 0x10;       /* W18 clip_size = 16 (misnamed) */
  weapon_pulse_gun_fire_rate = 0x3df5c28f; /* W18 shot_cooldown = 0.12 (misnamed) */
  weapon_pulse_gun_sfx_fire = sfx_rocketmini_fire; /* W18 sfx_fire (misnamed) */
  weapon_pulse_gun_sfx_reload = sfx_autorifle_reload_alt; /* W18 sfx_reload (misnamed) */
  uVar5 = 0xffffffff;
  weapon_pulse_gun_damage = 0x3fe66666; /* W18 damage_scale = 1.8 (misnamed) */
  pcVar7 = s_Pulse_Gun_00479464;       /* <-- W19 Pulse Gun name string copy starts here */
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_pulse_gun_spread = 0x3df5c28f; /* W18 spread = 0.12 (misnamed) */
  weapon_nexgun_projectile_type = 2;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8360;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; sfx_shock_reload = sfx_shock_reload, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  /* --- MISATTRIBUTED: weapon_ion_rifle_* globals are actually W19 Pulse Gun --- */
  /* These addresses fall within W19's struct (0x004d835C), NOT Ion Rifle (W21). */
  weapon_ion_rifle_sfx_fire = sfx_pulse_fire; /* W19 sfx_fire (misnamed) */
  uVar5 = 0xffffffff;
  pcVar7 = s_Ion_Rifle_00479458;       /* <-- W21 Ion Rifle name string copy starts here */
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_ion_rifle_type = 8;           /* W19 weapon_type (misnamed) */
  weapon_ion_rifle_clip = 0x10;        /* W19 clip_size = 16 (misnamed) */
  weapon_ion_rifle_fire_rate = 0x3dcccccd; /* W19 shot_cooldown = 0.1 (misnamed) */
  weapon_ion_rifle_damage = 0x3dcccccd;    /* W19 damage_scale = 0.1 (misnamed) */
  weapon_ion_rifle_spread = 0;             /* W19 spread = 0.0 (misnamed) */
  weapon_pulse_gun_projectile_type = 3;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8458;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  /* --- MISATTRIBUTED: weapon_ion_minigun_* globals are actually W21 Ion Rifle --- */
  /* These addresses fall within W21's struct (0x004d8454), NOT Ion Minigun (W22). */
  weapon_ion_minigun_sfx_fire = sfx_shock_fire_alt; /* W21 sfx_fire (misnamed) */
  uVar5 = 0xffffffff;
  pcVar7 = s_Ion_Minigun_0047944c;     /* <-- W22 Ion Minigun name string copy starts here */
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_ion_minigun_type = 8;          /* W21 weapon_type (misnamed) */
  weapon_ion_minigun_clip = 8;          /* W21 clip_size = 8 (misnamed) */
  weapon_ion_minigun_fire_rate = 0x3ecccccd; /* W21 shot_cooldown = 0.4 (misnamed) */
  weapon_ion_minigun_damage = 0x3faccccd;    /* W21 damage_scale = 1.35 (misnamed) */
  weapon_ion_minigun_spread = 0x3de56042;    /* W21 spread = 0.112 (misnamed) */
  weapon_ion_minigun_projectile_type = 4;
  weapon_ion_minigun_sfx_reload = sfx_shock_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d84d4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  /* --- MISATTRIBUTED: weapon_ion_cannon_* globals are actually W22 Ion Minigun --- */
  /* These addresses fall within W22's struct (0x004d84D0), NOT Ion Cannon (W23). */
  weapon_ion_cannon_sfx_fire = sfx_shockminigun_fire; /* W22 sfx_fire (misnamed) */
  uVar5 = 0xffffffff;
  weapon_ion_cannon_type = 8;           /* W22 weapon_type (misnamed) */
  weapon_ion_cannon_clip = 0x14;        /* W22 clip_size = 20 (misnamed) */
  weapon_ion_cannon_fire_rate = 0x3dcccccd; /* W22 shot_cooldown = 0.1 (misnamed) */
  weapon_ion_cannon_damage = 0x3fe66666;    /* W22 damage_scale = 1.8 (misnamed) */
  weapon_ion_cannon_spread = 0x3db851ec;    /* W22 spread = 0.09 (misnamed) */
  weapon_ion_cannon_projectile_type = 4;
  weapon_ion_cannon_sfx_reload = sfx_shock_reload;
  pcVar7 = s_Ion_Cannon_00479440;      /* <-- W23 Ion Cannon name string copy starts here */
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8550;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  /* --- W23 Ion Cannon — values from verified _DAT_ at struct 0x004d854C --- */
  /* _DAT_004d8598 = 0x3f800000 (shot_cooldown = 1.0) */
  /* _DAT_004d859c = 0x40400000 (damage_scale = 3.0) */
  /* _DAT_004d85a0 = 0x3f2e147b (spread = 0.68) */
  _DAT_004d85a8 = sfx_shock_fire_alt;  /* W23 sfx_fire */
  uVar5 = 0xffffffff;
  pcVar7 = s_Ion_Shotgun_00479434;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_ion_shotgun_clip = 3;
  _DAT_004d8598 = 0x3f800000;
  _DAT_004d859c = 0x40400000;
  _DAT_004d85a0 = 0x3f2e147b;
  _DAT_004d854c = 4;
  _DAT_004d85b0 = sfx_shock_reload;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8930;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8988 = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  pcVar7 = s_Gauss_Shotgun_00479424;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8998 = 1;
  _DAT_004d8974 = 10;
  _DAT_004d8978 = 0x3f59999a;
  _DAT_004d897c = 0x3ff33333;
  _DAT_004d8980 = 0x3e8a3d71;
  _DAT_004d89a4 = 8;
  _DAT_004d892c = 4;
  _DAT_004d8990 = sfx_shock_reload;
  _DAT_004d8994 = 0x1f;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d88b4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d890c = sfx_gauss_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Plasma_Cannon_00479414;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d891c = 1;
  _DAT_004d88f8 = 4;
  _DAT_004d88fc = 0x3f866666;
  _DAT_004d8900 = 0x40066666;
  _DAT_004d8904 = 0x3e8a3d71;
  _DAT_004d88b0 = 0;
  _DAT_004d8914 = sfx_reload_default;
  _DAT_004d8918 = 0x1e;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d87bc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8814 = sfx_shock_fire;
  uVar5 = 0xffffffff;
  _DAT_004d8800 = 3;
  pcVar7 = s_Evil_Scythe_00479408;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8804 = 0x3f666666;
  _DAT_004d8808 = 0x402ccccd;
  _DAT_004d880c = 0x3f19999a;
  _DAT_004d881c = sfx_shock_reload;
  _DAT_004d8820 = 0x19;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8740;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8798 = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  pcVar7 = s_Flameburst_004793fc;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8784 = 3;
  _DAT_004d8788 = 0x3f800000;
  _DAT_004d878c = 0x40400000;
  _DAT_004d8790 = 0x3f2e147b;
  _DAT_004d873c = 4;
  _DAT_004d87a0 = sfx_shock_reload;
  _DAT_004d87a4 = 0x19;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d89ac;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8a04 = sfx_flamer_fire_01;
  uVar5 = 0xffffffff;
  pcVar7 = &DAT_004793f4;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d89f0 = 0x3c;
  _DAT_004d89f4 = 0x3ca3d70a;
  _DAT_004d89f8 = 0x40400000;
  _DAT_004d89fc = 0x3e3851ec;
  _DAT_004d89a8 = 4;
  _DAT_004d8a0c = sfx_shock_reload;
  _DAT_004d8a10 = 0x1d;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8a28;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8a80 = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  _DAT_004d8a6c = 0xc;
  _DAT_004d8a70 = 0x3f333333;
  _DAT_004d8a74 = 0x40000000;
  _DAT_004d8a78 = 0x3ec28f5c;
  _DAT_004d8a24 = 4;
  _DAT_004d8a88 = sfx_shock_reload;
  _DAT_004d8a8c = 0x1e;
  pcVar7 = s_Splitter_Gun_004793e4;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8838;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8890 = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  pcVar7 = s_Shrinkifier_5k_004793d4;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d887c = 6;
  _DAT_004d8880 = 0x3f333333;
  _DAT_004d8884 = 0x400ccccd;
  _DAT_004d8888 = 0x3e8f5c29;
  _DAT_004d8834 = 0;
  _DAT_004d8898 = sfx_shock_reload;
  _DAT_004d88a8 = 0x40c00000;
  _DAT_004d88a4 = 0x41f00000;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d85cc;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d8624 = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  pcVar7 = s_Blade_Gun_004793c8;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_plasma_cannon_type = 8;
  weapon_plasma_cannon_clip = 8;
  weapon_plasma_cannon_fire_rate = 0x3e570a3d;
  weapon_plasma_cannon_damage = 0x3f9c28f6;
  weapon_plasma_cannon_spread = 0x3d23d70a;
  weapon_plasma_cannon_sfx_reload = sfx_shock_reload;
  weapon_plasma_cannon_projectile_type = 0x17;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8648;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_plasma_cannon_sfx_fire = sfx_shock_fire_alt;
  uVar5 = 0xffffffff;
  pcVar7 = s_Plague_Sphreader_Gun_004793b0;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_plague_spreader_type = 8;
  weapon_plague_spreader_clip = 6;
  weapon_plague_spreader_fire_rate = 0x3eb33333;
  weapon_plague_spreader_damage = 0x40600000;
  weapon_plague_spreader_spread = 0x3d23d70a;
  weapon_plague_spreader_projectile_type = 0x18;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8e08;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; sfx_bloodspill_01 = sfx_bloodspill_01, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  weapon_rainbow_gun_type = 8;
  uVar5 = 0xffffffff;
  pcVar7 = s_Rainbow_Gun_004793a4;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_rainbow_gun_clip = 5;
  weapon_rainbow_gun_fire_rate = 0x3e4ccccd;
  weapon_rainbow_gun_damage = 0x3f99999a;
  weapon_rainbow_gun_spread = 0x3d23d70a;
  weapon_rainbow_gun_sfx_fire = sfx_bloodspill_01;
  weapon_rainbow_gun_sfx_reload = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8f00;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Grim_Weapon_00479398;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_grim_type = 8;
  weapon_grim_clip = 10;
  weapon_grim_fire_rate = 0x3e4ccccd;
  weapon_grim_damage = 0x3f99999a;
  weapon_grim_spread = 0x3db851ec;
  weapon_grim_sfx_fire = sfx_bloodspill_01;
  weapon_grim_sfx_reload = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8f7c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Bubblegun_0047938c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  weapon_bubblegun_clip = 3;
  weapon_bubblegun_fire_rate = 0x3f000000;
  weapon_bubblegun_damage = 0x3f99999a;
  weapon_bubblegun_spread = 0x3ecccccd;
  weapon_bubblegun_sfx_fire = sfx_bloodspill_01;
  weapon_bubblegun_sfx_reload = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d8e84;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Spider_Plasma_0047937c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d8eec = 8;
  _DAT_004d8ec8 = 0xf;
  _DAT_004d8ecc = 0x3e252bd4;
  _DAT_004d8ed0 = 0x3f99999a;
  _DAT_004d8ed4 = 0x3d4ccccd;
  _DAT_004d8edc = sfx_bloodspill_01;
  _DAT_004d8ee4 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d86c4;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Transmutator_0047936c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d872c = 8;
  _DAT_004d8708 = 5;
  _DAT_004d870c = 0x3e4ccccd;
  _DAT_004d8710 = 0x3f99999a;
  _DAT_004d8714 = 0x3d23d70a;
  _DAT_004d871c = sfx_bloodspill_01;
  _DAT_004d8724 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d9264;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; _DAT_004d93b4 = sfx_explosion_large, uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s_Blaster_R_300_0047935c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d92cc = 9;
  _DAT_004d92a8 = 0x32;
  _DAT_004d92ac = 0x3d23d70a;
  _DAT_004d92b0 = 0x40a00000;
  _DAT_004d92b4 = 0x3d23d70a;
  _DAT_004d92c4 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d92e0;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d9338 = sfx_shock_fire;
  uVar5 = 0xffffffff;
  pcVar7 = s_Nuke_Launcher_0047934c;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d9348 = 9;
  _DAT_004d9324 = 0x14;
  _DAT_004d9328 = 0x3da3d70a;
  _DAT_004d932c = 0x40000000;
  _DAT_004d9330 = 0x3d4ccccd;
  _DAT_004d9340 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d93d8;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar7 = s___Lighting_Rifle_0047933a + 2;
  do {
    pcVar8 = pcVar7;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar7 + 1;
    cVar2 = *pcVar7;
    pcVar7 = pcVar8;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  _DAT_004d9440 = 8;
  _DAT_004d941c = 1;
  _DAT_004d9420 = 0x40800000;
  _DAT_004d9424 = 0x41000000;
  _DAT_004d9428 = 0x3f800000;
  _DAT_004d9430 = _DAT_004d93b4;
  _DAT_004d9438 = sfx_reload_default;
  pcVar7 = pcVar8 + -uVar5;
  pcVar8 = (char *)&DAT_004d935c;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  }
  _DAT_004d93c4 = 8;
  _DAT_004d93a0 = 500;
  _DAT_004d93a4 = 0x40800000;
  _DAT_004d93a8 = 0x41000000;
  _DAT_004d93ac = 0x3f800000;
  return;
}



/* weapon_pick_random_available @ 00452cd0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* selects a random weapon id that is marked available */

int weapon_pick_random_available(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  do {
    iVar1 = crt_rand();
    iVar3 = iVar1 % 0x21 + 1;
    if (game_status_blob.weapon_usage_counts[iVar1 % 0x21 + 1] != 0) {
      uVar2 = crt_rand();
      if ((uVar2 & 1) == 0) {
        iVar1 = crt_rand();
        iVar3 = iVar1 % 0x21 + 1;
      }
    }
  } while (((&weapon_table)[iVar3].unlocked == '\0') ||
          ((((config_blob.reserved0._24_4_ == 3 && (quest_stage_major == 5)) &&
            (quest_stage_minor == 10)) && (iVar3 == 0x17))));
  return iVar3;
}



/* weapon_assign_player @ 00452d40 */

/* assigns a weapon to a player and resets ammo timers */

void __cdecl weapon_assign_player(int player_index,int weapon_id)

{
  float sfx_id;
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = weapon_id;
  if (demo_mode_active == '\0') {
    game_status_blob.weapon_usage_counts[weapon_id] =
         game_status_blob.weapon_usage_counts[weapon_id] + 1;
  }
  (&player_state_table)[player_index].weapon_id = weapon_id;
  iVar2 = perk_id_ammo_maniac;
  (&player_state_table)[player_index].clip_size = (int)(float)(&weapon_table)[weapon_id].clip_size;
  iVar2 = perk_count_get(iVar2);
  if (iVar2 != 0) {
    lVar3 = __ftol();
    weapon_id = (int)lVar3;
    if (weapon_id < 2) {
      weapon_id = 1;
    }
    (&player_state_table)[player_index].clip_size =
         (int)((float)weapon_id + (float)(&player_state_table)[player_index].clip_size);
  }
  iVar2 = perk_count_get(perk_id_my_favourite_weapon);
  if (iVar2 != 0) {
    (&player_state_table)[player_index].clip_size =
         (int)((float)(&player_state_table)[player_index].clip_size + 2.0);
  }
  sfx_id = (float)(&weapon_table)[iVar1].reload_sfx_id;
  (&player_state_table)[player_index].ammo = (&player_state_table)[player_index].clip_size;
  (&player_state_table)[player_index].weapon_reset_latch = 0;
  (&player_state_table)[player_index].shot_cooldown = 0.0;
  (&player_state_table)[player_index].reload_timer = 0.0;
  (&player_aux_timer)[player_index] = 0x40000000;
  sfx_play_panned(sfx_id);
  return;
}



/* weapon_refresh_available @ 00452e40 */

/* rebuilds availability flags from the unlock list */

void weapon_refresh_available(void)

{
  int iVar1;
  uchar *puVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  puVar2 = &weapon_table.unlocked;
  do {
    *puVar2 = '\0';
    iVar3 = quest_unlock_index;
    puVar2 = puVar2 + 0x7c;
  } while ((int)puVar2 < 0x4d996c);
  iVar5 = 0;
  weapon_pistol_unlocked = 1;
  if (0 < quest_unlock_index) {
    piVar4 = &quest_selected_meta.unlock_weapon_id;
    do {
      if (0x484feb < (int)piVar4) break;
      iVar1 = *piVar4;
      piVar4 = piVar4 + 0xb;
      iVar5 = iVar5 + 1;
      (&weapon_table)[iVar1].unlocked = '\x01';
    } while (iVar5 < iVar3);
  }
  if (config_blob.reserved0._24_4_ == 1) {
    weapon_shotgun_unlocked = 1;
    weapon_smg_unlocked = 1;
    weapon_assault_rifle_unlocked = 1;
  }
  iVar3 = game_is_full_version();
  if ((uchar)iVar3 == '\0') {
    quest_unlock_index_full = 0;
    weapon_table.unlocked = (uchar)iVar3;
    return;
  }
  if (0x27 < quest_unlock_index_full) {
    weapon_splitter_unlocked = 1;
  }
  weapon_table.unlocked = '\0';
  return;
}


