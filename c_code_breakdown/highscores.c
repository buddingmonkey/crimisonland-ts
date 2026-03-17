/* highscore_init_sentinels @ 00412360 */

/* [binja] int32_t sub_412360() */

int highscore_init_sentinels(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uchar *puVar6;
  char *pcVar7;
  char *pcVar8;
  highscore_record_t *phVar9;
  
  puVar6 = &highscore_table.sentinel_pipe;
  iVar5 = 100;
  do {
    phVar9 = (highscore_record_t *)(puVar6 + -0x46);
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      phVar9->player_name[0] = '\0';
      phVar9->player_name[1] = '\0';
      phVar9->player_name[2] = '\0';
      phVar9->player_name[3] = '\0';
      phVar9 = (highscore_record_t *)(phVar9->player_name + 4);
    }
    uVar3 = 0xffffffff;
    pcVar7 = &default_player_name;
    do {
      pcVar8 = pcVar7;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar8 = pcVar7 + 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar7 = pcVar8 + -uVar3;
    phVar9 = (highscore_record_t *)(puVar6 + -0x46);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)phVar9->player_name = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      phVar9 = (highscore_record_t *)(phVar9->player_name + 4);
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      phVar9->player_name[0] = *pcVar7;
      pcVar7 = pcVar7 + 1;
      phVar9 = (highscore_record_t *)(phVar9->player_name + 1);
    }
    puVar6[-2] = '\0';
    *puVar6 = '|';
    puVar6[1] = 0xff;
    uVar3 = crt_rand();
    *(uint *)(puVar6 + -0xe) = uVar3 & 0xfee050f;
    puVar6 = puVar6 + 0x48;
    iVar5 = iVar5 + -1;
    if (iVar5 == 0) {
      return uVar3 & 0xfee050f;
    }
  } while( true );
}



/* highscore_date_checksum @ 0043a950 */

/* computes a week-of-year style checksum for high score validation */

int __cdecl highscore_date_checksum(int year,int month,int day)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (0xe - month) / 0xc;
  iVar2 = (year - iVar1) + 0x12c0;
  iVar1 = ((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) + -0x7d2d +
          day + ((iVar2 / 400 + ((month + iVar1 * 0xc) * 0x99 + -0x1c9) / 5 + iVar2 * 0x16d) -
                iVar2 / 100);
  iVar2 = ((((iVar1 - iVar1 % 7) + 0x7bfd) % 0x23ab1) % 0x8eac) % 0x5b5;
  iVar1 = iVar2 / 0x5b4;
  return ((iVar2 - iVar1) % 0x16d + iVar1) / 7 + 1;
}



/* highscore_read_record @ 0043ab10 */

/* reads and validates a high score record from a file */

char * __cdecl highscore_read_record(char *param_1,int *param_2)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int local_4;
  
  iVar3 = 0;
  local_4 = 0;
  crt_fread(param_1,0x48,1,param_2);
  if ((*(byte *)(param_2 + 3) & 0x10) != 0) {
    return (char *)0x0;
  }
  crt_fread((char *)&local_4,4,1,param_2);
  uVar1 = 0;
  do {
    param_1[uVar1] = param_1[uVar1] + (-6 - ((char)uVar1 * '\x05' + '\x01') * (char)uVar1);
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x48);
  iVar4 = 0x48;
  pcVar2 = param_1;
  do {
    iVar3 = iVar3 + (int)(pcVar2 + (3 - (int)param_1)) * (int)*pcVar2 * 7;
    pcVar2 = pcVar2 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if (local_4 != iVar3) {
    param_1[0x1f] = '\0';
    console_printf(&console_log_queue,s_WARN__checksum_failure_on_score_b_00477b40,param_1);
    return (char *)0x0;
  }
  return param_1;
}



/* highscore_record_equals @ 0043abd0 */

/* compares high score record metadata and name for equality */

int __cdecl highscore_record_equals(byte *left,byte *right)

{
  byte bVar1;
  uint3 uVar3;
  int iVar2;
  bool bVar4;
  
  uVar3 = (uint3)((uint)left >> 8);
  if (*(int *)(left + 0x24) != *(int *)(right + 0x24)) {
    return (uint)uVar3 << 8;
  }
  if (*(int *)(left + 0x20) != *(int *)(right + 0x20)) {
    return (uint)uVar3 << 8;
  }
  if (left[0x28] != right[0x28]) {
    return (uint)uVar3 << 8;
  }
  if (*(int *)(left + 0x34) != *(int *)(right + 0x34)) {
    return (uint)uVar3 << 8;
  }
  if (*(int *)(left + 0x30) != *(int *)(right + 0x30)) {
    return (uint)uVar3 << 8;
  }
  if (*(int *)(left + 0x2c) != *(int *)(right + 0x2c)) {
    return (uint)uVar3 << 8;
  }
  while( true ) {
    bVar1 = *left;
    bVar4 = bVar1 < *right;
    if (bVar1 != *right) break;
    if (bVar1 == 0) {
      return 1;
    }
    bVar1 = left[1];
    bVar4 = bVar1 < right[1];
    if (bVar1 != right[1]) break;
    left = left + 2;
    right = right + 2;
    if (bVar1 == 0) {
      return 1;
    }
  }
  iVar2 = (1 - (uint)bVar4) - (uint)(bVar4 != 0);
  return CONCAT31((int3)((uint)iVar2 >> 8),iVar2 == 0);
}



/* highscore_update_record @ 0043ac70 */

/* updates a matching record in the high score file when allowed */

int __cdecl highscore_update_record(char *path,byte *record)

{
  char cVar1;
  byte bVar2;
  FILE *fp;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  char *pcVar8;
  byte *pbVar9;
  byte local_48 [56];
  uint local_10;
  byte local_4;
  undefined1 local_2;
  undefined1 local_1;
  
  pbVar7 = local_48;
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    pbVar7[0] = 0;
    pbVar7[1] = 0;
    pbVar7[2] = 0;
    pbVar7[3] = 0;
    pbVar7 = pbVar7 + 4;
  }
  uVar5 = 0xffffffff;
  pcVar3 = &default_player_name;
  do {
    pcVar8 = pcVar3;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pbVar7 = (byte *)(pcVar8 + -uVar5);
  pbVar9 = local_48;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pbVar9 = *(undefined4 *)pbVar7;
    pbVar7 = pbVar7 + 4;
    pbVar9 = pbVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pbVar9 = *pbVar7;
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar9 + 1;
  }
  local_4 = 0;
  local_2 = 0x7c;
  local_1 = 0xff;
  local_10 = crt_rand();
  local_10 = local_10 & 0xfee050f;
  fp = (FILE *)crt_fopen(path,&DAT_00477b68);
  uVar5 = 0;
  if (fp != (FILE *)0x0) {
    bVar2 = (byte)fp->_flag;
    while ((bVar2 & 0x10) == 0) {
      pcVar3 = highscore_read_record((char *)local_48,(int *)fp);
      if ((pcVar3 != (char *)0x0) &&
         (iVar4 = highscore_record_equals(record,local_48), (char)iVar4 != '\0')) {
        if ((local_4 & 2) != 0) {
          iVar4 = crt_fclose(fp);
          return CONCAT31((int3)((uint)iVar4 >> 8),1);
        }
        if (local_4 == 0) {
          record[0x44] = 2;
        }
        crt_fseek((int *)fp,-0x4c,1);
        highscore_write_record((undefined4 *)record,(int *)fp);
        crt_fflush((int *)fp);
        iVar4 = crt_fclose(fp);
        return CONCAT31((int3)((uint)iVar4 >> 8),1);
      }
      bVar2 = (byte)fp->_flag;
    }
    crt_fflush((int *)fp);
    uVar5 = crt_fclose(fp);
  }
  return uVar5 & 0xffffff00;
}



/* highscore_write_record @ 0043ad70 */

/* writes a high score record with date + checksum */

void __cdecl highscore_write_record(undefined4 *param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  int local_4c;
  char local_48 [56];
  uint local_10;
  undefined1 local_4;
  undefined1 local_2;
  undefined1 local_1;
  
  local_4c = 0;
  GetLocalTime((LPSYSTEMTIME)&local_system_time);
  pcVar5 = local_48;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    pcVar5[0] = '\0';
    pcVar5[1] = '\0';
    pcVar5[2] = '\0';
    pcVar5[3] = '\0';
    pcVar5 = pcVar5 + 4;
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
  pcVar6 = local_48;
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
  local_4 = 0;
  local_2 = 0x7c;
  local_1 = 0xff;
  uVar3 = crt_rand();
  local_10 = uVar3 & 0xfee050f;
  if (*(char *)(param_1 + 0x10) == '\0') {
    *(undefined1 *)(param_1 + 0x10) = (undefined1)local_system_day;
    *(undefined1 *)((int)param_1 + 0x42) = local_system_time._2_1_;
    *(char *)((int)param_1 + 0x43) = (char)local_system_time + '0';
    iVar2 = highscore_date_checksum
                      (local_system_time & 0xffff,local_system_time >> 0x10,(uint)local_system_day);
    *(char *)((int)param_1 + 0x41) = (char)iVar2;
  }
  pcVar5 = local_48;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined4 *)pcVar5 = *param_1;
    param_1 = param_1 + 1;
    pcVar5 = pcVar5 + 4;
  }
  uVar3 = 0;
  do {
    local_4c = local_4c + (int)(local_48 + uVar3 + (3 - (int)local_48)) * (int)local_48[uVar3] * 7;
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x48);
  uVar3 = 0;
  do {
    local_48[uVar3] = local_48[uVar3] + ((char)uVar3 * '\x05' + '\x01') * (char)uVar3 + '\x06';
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x48);
  crt_fwrite(local_48,0x48,1,param_2);
  crt_fwrite((char *)&local_4c,4,1,param_2);
  return;
}



/* highscore_compare_survival_score_desc @ 0043aeb0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qsort comparator used by highscore_load_table() for survival mode; sorts descending by dword at
   offset 0x24 */

int highscore_compare_survival_score_desc(void *a,void *b)

{
  if (*(int *)((int)b + 0x24) < *(int *)((int)a + 0x24)) {
    return -1;
  }
  return (uint)(*(int *)((int)a + 0x24) < *(int *)((int)b + 0x24));
}



/* highscore_compare_rush_field32_desc @ 0043aed0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qsort comparator used by highscore_load_table() for rush mode; sorts descending by dword at
   offset 0x20 */

int highscore_compare_rush_field32_desc(void *a,void *b)

{
  if (*(int *)((int)b + 0x20) < *(int *)((int)a + 0x20)) {
    return -1;
  }
  return (uint)(*(int *)((int)a + 0x20) < *(int *)((int)b + 0x20));
}



/* highscore_compare_quest_field32_asc_nonzero_first @ 0043aef0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* qsort comparator used by highscore_load_table() for quest mode; sorts ascending by dword at
   offset 0x20, treating 0 as "missing" (sorted last) */

int highscore_compare_quest_field32_asc_nonzero_first(void *a,void *b)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)((int)a + 0x20);
  if (iVar1 == 0) {
    return 1;
  }
  iVar2 = *(int *)((int)b + 0x20);
  if (iVar2 == 0) {
    return -1;
  }
  if (iVar2 < iVar1) {
    return 1;
  }
  return (iVar2 <= iVar1) - 1;
}



/* highscore_find_name_entry @ 0043af30 */

/* finds a matching name entry in the loaded high score table */

byte * __cdecl highscore_find_name_entry(byte *record,int count)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  highscore_record_t *phVar5;
  highscore_record_t *phVar6;
  bool bVar7;
  
  iVar4 = 0;
  if (0 < count) {
    phVar5 = &highscore_table;
    pbVar2 = record;
    phVar6 = phVar5;
LAB_0043af49:
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < (byte)phVar5->player_name[0];
      if (bVar1 == phVar5->player_name[0]) {
        if (bVar1 != 0) {
          bVar1 = pbVar2[1];
          bVar7 = bVar1 < (byte)phVar5->player_name[1];
          if (bVar1 != phVar5->player_name[1]) goto LAB_0043af6d;
          phVar5 = (highscore_record_t *)(phVar5->player_name + 2);
          pbVar2 = pbVar2 + 2;
          if (bVar1 != 0) goto LAB_0043af49;
        }
        iVar3 = 0;
      }
      else {
LAB_0043af6d:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      }
      if (iVar3 == 0) {
        return (byte *)(&highscore_table + iVar4);
      }
      iVar4 = iVar4 + 1;
      phVar5 = phVar6 + 1;
      pbVar2 = record;
      phVar6 = phVar5;
    } while (iVar4 < count);
  }
  return (byte *)0x0;
}



/* highscore_load_table @ 0043afa0 */

/* loads, filters, and sorts the high score table */

void highscore_load_table(void)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  FILE *fp;
  byte *pbVar4;
  highscore_record_t *phVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uchar *puVar12;
  int iVar13;
  byte *pbVar14;
  char *pcVar15;
  highscore_record_t *phVar16;
  bool bVar17;
  code *cmp;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  byte local_48 [40];
  uint local_20;
  uint local_10;
  byte local_8;
  undefined1 local_7;
  byte bStack_6;
  undefined1 uStack_5;
  byte bStack_4;
  char cStack_3;
  undefined1 uStack_2;
  undefined1 local_1;
  
  pbVar4 = local_48;
  for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1) {
    pbVar4[0] = 0;
    pbVar4[1] = 0;
    pbVar4[2] = 0;
    pbVar4[3] = 0;
    pbVar4 = pbVar4 + 4;
  }
  uVar9 = 0xffffffff;
  pcVar3 = &default_player_name;
  do {
    pcVar6 = pcVar3;
    if (uVar9 == 0) break;
    uVar9 = uVar9 - 1;
    pcVar6 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar6;
  } while (cVar1 != '\0');
  uVar9 = ~uVar9;
  pbVar4 = (byte *)(pcVar6 + -uVar9);
  pbVar14 = local_48;
  for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pbVar14 = *(undefined4 *)pbVar4;
    pbVar4 = pbVar4 + 4;
    pbVar14 = pbVar14 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pbVar14 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    pbVar14 = pbVar14 + 1;
  }
  bStack_4 = 0;
  uStack_2 = 0x7c;
  local_1 = 0xff;
  local_10 = crt_rand();
  local_10 = local_10 & 0xfee050f;
  pcVar3 = highscore_build_path();
  highscore_table_count = 0;
  puVar12 = &highscore_table.sentinel_pipe;
  do {
    phVar16 = (highscore_record_t *)(puVar12 + -0x46);
    for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1) {
      phVar16->player_name[0] = '\0';
      phVar16->player_name[1] = '\0';
      phVar16->player_name[2] = '\0';
      phVar16->player_name[3] = '\0';
      phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
    }
    uVar9 = 0xffffffff;
    pcVar6 = &default_player_name;
    do {
      pcVar15 = pcVar6;
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      pcVar15 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar15;
    } while (cVar1 != '\0');
    uVar9 = ~uVar9;
    pcVar6 = pcVar15 + -uVar9;
    phVar16 = (highscore_record_t *)(puVar12 + -0x46);
    for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)phVar16->player_name = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      phVar16->player_name[0] = *pcVar6;
      pcVar6 = pcVar6 + 1;
      phVar16 = (highscore_record_t *)(phVar16->player_name + 1);
    }
    puVar12[-2] = '\0';
    *puVar12 = '|';
    puVar12[1] = 0xff;
    uVar9 = crt_rand();
    *(uint *)(puVar12 + -0xe) = uVar9 & 0xfee050f;
    puVar12 = puVar12 + 0x48;
  } while ((int)puVar12 < 0x484776);
  iVar8 = 0;
  fp = (FILE *)crt_fopen(pcVar3,&file_mode_read_binary);
  if (fp != (FILE *)0x0) {
    uVar9 = highscore_date_checksum
                      (local_system_time & 0xffff,local_system_time >> 0x10,(uint)local_system_day);
    bVar2 = (byte)fp->_flag;
    while ((bVar2 & 0x10) == 0) {
      pcVar3 = highscore_read_record((char *)local_48,(int *)fp);
      if ((pcVar3 == (char *)0x0) || ((local_20 & 0xff) != config_blob.reserved0._24_4_))
      goto LAB_0043b2ba;
      if (config_blob.reserved0._24_4_ == 3) {
        if (config_blob.hardcore == '\0') {
          if (cStack_3 == '\0') goto LAB_0043b0ff;
        }
        else if (cStack_3 == 'u') goto LAB_0043b0ff;
      }
      else {
LAB_0043b0ff:
        if (((config_blob.score_load_gate != '\0') || ((bStack_4 & 1) == 0)) ||
           ((bStack_4 & 2) != 0)) {
          if (config_blob.reserved0[2] == '\x03') {
            if (((local_system_day == local_8) &&
                ((local_system_time & 0xffff) - 2000 ==
                 (CONCAT12(cStack_3,CONCAT11(bStack_4,uStack_5)) & 0xff))) &&
               (local_system_time._2_2_ == bStack_6)) goto LAB_0043b1df;
          }
          else if (config_blob.reserved0[2] == '\x02') {
            if ((uVar9 == (CONCAT12(uStack_5,CONCAT11(bStack_6,local_7)) & 0xff)) &&
               ((local_system_time & 0xffff) ==
                (CONCAT12(cStack_3,CONCAT11(bStack_4,uStack_5)) & 0xff) + 2000)) {
LAB_0043b1df:
              if ((config_blob.reserved0[3] == '\x01') &&
                 (pbVar4 = highscore_find_name_entry(local_48,iVar8), pbVar4 != (byte *)0x0)) {
                pbVar14 = local_48;
                for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
                  *(undefined4 *)pbVar4 = *(undefined4 *)pbVar14;
                  pbVar14 = pbVar14 + 4;
                  pbVar4 = pbVar4 + 4;
                }
              }
              else if (iVar8 == 99) {
                phVar16 = &highscore_table;
                if (config_blob.reserved0._24_4_ == 2) {
                  phVar5 = (highscore_record_t *)&highscore_table_data;
                  do {
                    if ((int)phVar5->survival_elapsed_ms < (int)phVar16->survival_elapsed_ms) {
                      phVar16 = phVar5;
                    }
                    phVar5 = phVar5 + 1;
                  } while ((int)phVar5 < 0x484730);
                  pbVar4 = local_48;
                  for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
                    *(undefined4 *)phVar16->player_name = *(undefined4 *)pbVar4;
                    pbVar4 = pbVar4 + 4;
                    phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
                  }
                }
                else {
                  phVar5 = (highscore_record_t *)&highscore_table_data;
                  if (config_blob.reserved0._24_4_ == 3) {
                    do {
                      if ((int)phVar16->survival_elapsed_ms < (int)phVar5->survival_elapsed_ms) {
                        phVar16 = phVar5;
                      }
                      phVar5 = phVar5 + 1;
                    } while ((int)phVar5 < 0x484730);
                    pbVar4 = local_48;
                    for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
                      *(undefined4 *)phVar16->player_name = *(undefined4 *)pbVar4;
                      pbVar4 = pbVar4 + 4;
                      phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
                    }
                  }
                  else {
                    do {
                      if ((int)phVar5->score_xp < (int)phVar16->score_xp) {
                        phVar16 = phVar5;
                      }
                      phVar5 = phVar5 + 1;
                    } while ((int)phVar5 < 0x484730);
                    pbVar4 = local_48;
                    for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
                      *(undefined4 *)phVar16->player_name = *(undefined4 *)pbVar4;
                      pbVar4 = pbVar4 + 4;
                      phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
                    }
                  }
                }
              }
              else {
                iVar13 = iVar8 + 1;
                pbVar4 = local_48;
                phVar16 = &highscore_table + iVar8;
                highscore_table_count = iVar13;
                for (iVar11 = 0x12; iVar8 = iVar13, iVar11 != 0; iVar11 = iVar11 + -1) {
                  *(undefined4 *)phVar16->player_name = *(undefined4 *)pbVar4;
                  pbVar4 = pbVar4 + 4;
                  phVar16 = (highscore_record_t *)(phVar16->player_name + 4);
                }
              }
            }
          }
          else if ((config_blob.reserved0[2] != '\x01') ||
                  ((local_system_time._2_2_ == bStack_6 &&
                   ((local_system_time & 0xffff) - 2000 ==
                    (CONCAT12(cStack_3,CONCAT11(bStack_4,uStack_5)) & 0xff))))) goto LAB_0043b1df;
        }
      }
LAB_0043b2ba:
      bVar2 = (byte)fp->_flag;
    }
    crt_fclose(fp);
    if (100 < highscore_table_count) {
      highscore_table_count = 100;
    }
    if (config_blob.reserved0._24_4_ == 2) {
      cmp = highscore_compare_rush_field32_desc;
    }
    else if (config_blob.reserved0._24_4_ == 3) {
      cmp = highscore_compare_quest_field32_asc_nonzero_first;
    }
    else {
      cmp = highscore_compare_survival_score_desc;
    }
    crt_qsort(&highscore_table,100,0x48,cmp);
    if (config_blob.reserved0._128_4_ == 0) {
      local_4c = 0;
      if (0 < highscore_table_count) {
        local_50 = 0;
        iVar8 = highscore_table_count;
        do {
          iVar11 = highscore_table_count;
          if (((highscore_table.reserved0[local_50 + 0xc] & 4) == 0) &&
             ((highscore_table.reserved0[local_50 + 0xc] & 1) != 0)) {
            iVar8 = 0;
            iVar13 = 0;
            local_58 = local_50;
            local_54 = local_4c;
            do {
              pcVar3 = highscore_table.player_name + iVar13;
              if ((highscore_table.reserved0[iVar13 + 0xc] & 1) != 0) {
                pcVar6 = highscore_table.player_name + local_50;
                do {
                  bVar2 = *pcVar6;
                  bVar17 = bVar2 < (byte)*pcVar3;
                  if (bVar2 != *pcVar3) {
LAB_0043b39e:
                    iVar7 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                    goto LAB_0043b3a3;
                  }
                  if (bVar2 == 0) break;
                  bVar2 = pcVar6[1];
                  bVar17 = bVar2 < (byte)pcVar3[1];
                  if (bVar2 != pcVar3[1]) goto LAB_0043b39e;
                  pcVar6 = pcVar6 + 2;
                  pcVar3 = pcVar3 + 2;
                } while (bVar2 != 0);
                iVar7 = 0;
LAB_0043b3a3:
                if (iVar7 == 0) {
                  if (highscore_table.reserved0[local_58 + -0x10] == '\x02') {
                    if (*(int *)(highscore_table.reserved0 + local_58 + -0x18) <
                        *(int *)(highscore_table.reserved0 + iVar13 + -0x18)) {
LAB_0043b3d0:
                      local_58 = iVar13;
                      local_54 = iVar8;
                    }
                  }
                  else if (*(int *)(highscore_table.reserved0 + local_58 + -0x14) <
                           *(int *)(highscore_table.reserved0 + iVar13 + -0x14)) goto LAB_0043b3d0;
                }
              }
              iVar8 = iVar8 + 1;
              iVar13 = iVar13 + 0x48;
            } while (iVar8 < highscore_table_count);
            (&highscore_table)[local_54].flags = (&highscore_table)[local_54].flags | 4;
            iVar8 = iVar11;
          }
          local_4c = local_4c + 1;
          local_50 = local_50 + 0x48;
          if (iVar8 <= local_4c) {
            return;
          }
        } while( true );
      }
    }
    else if (0 < highscore_table_count) {
      puVar12 = &highscore_table.flags;
      iVar8 = highscore_table_count;
      do {
        if ((*puVar12 & 1) != 0) {
          *puVar12 = *puVar12 | 4;
        }
        puVar12 = puVar12 + 0x48;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  return;
}



/* highscore_save_record @ 0043b450 */

/* saves a high score record (updates or appends) */

void __cdecl highscore_save_record(byte *record)

{
  byte bVar1;
  char *path;
  FILE *fp;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  
  path = highscore_build_path();
  if (record == (byte *)0x0) {
    console_printf(&console_log_queue,s_unexpected_sc_null);
    return;
  }
  uVar2 = 0xffffffff;
  pbVar4 = record;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
  } while (bVar1 != 0);
  for (iVar3 = ~uVar2 - 2; (0 < iVar3 && (record[iVar3] == 0x20)); iVar3 = iVar3 + -1) {
    record[iVar3] = 0;
  }
  CreateDirectoryA(s_scores_dir,(LPSECURITY_ATTRIBUTES)0x0);
  if (highscore_init_flag == '\0') {
    highscore_record_init();
  }
  if (((record[0x44] & 1) == 0) ||
     (iVar3 = highscore_update_record(path,record), (char)iVar3 == '\0')) {
    fp = (FILE *)crt_fopen(path,&file_mode_append_binary);
    if (fp == (FILE *)0x0) {
      console_printf(&console_log_queue,s_unable_to_save_score);
      return;
    }
    highscore_write_record((undefined4 *)record,(int *)fp);
    crt_fclose(fp);
  }
  return;
}



/* highscore_save_active @ 0043b510 */

/* saves the active high score record */

void highscore_save_active(void)

{
  highscore_save_record((byte *)&highscore_active_record);
  return;
}



/* highscore_rank_index @ 0043b520 */

/* returns the insert index for the current run in the high score table */

int highscore_rank_index(void)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  iVar2 = highscore_table_count;
  if (config_blob.reserved0._24_4_ == 2) {
    iVar1 = 0;
    if (0 < highscore_table_count) {
      puVar3 = &highscore_table.survival_elapsed_ms;
      while (iVar2 = iVar1, (int)highscore_active_record.survival_elapsed_ms <= (int)*puVar3) {
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 0x12;
        if (highscore_table_count <= iVar1) {
          return highscore_table_count;
        }
      }
    }
  }
  else if (config_blob.reserved0._24_4_ == 3) {
    iVar1 = 0;
    if (0 < highscore_table_count) {
      puVar3 = &highscore_table.survival_elapsed_ms;
      while (iVar2 = iVar1, (int)*puVar3 <= (int)highscore_active_record.survival_elapsed_ms) {
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 0x12;
        if (highscore_table_count <= iVar1) {
          return highscore_table_count;
        }
      }
    }
  }
  else {
    iVar1 = 0;
    if (0 < highscore_table_count) {
      puVar3 = &highscore_table.score_xp;
      do {
        if ((int)*puVar3 < (int)highscore_active_record.score_xp) {
          return iVar1;
        }
        iVar1 = iVar1 + 1;
        puVar3 = puVar3 + 0x12;
      } while (iVar1 < highscore_table_count);
    }
  }
  return iVar2;
}



/* highscore_build_path @ 0043b5b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* builds the high score filename for the current mode */

char * highscore_build_path(void)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined *puVar4;
  
  if (perk_table_initialized == '\0') {
    crt_getcwd(&crt_locale_data_ptr,0x1ff);
    DAT_004c395b = 0;
    perk_table_initialized = '\x01';
  }
  if (config_blob.reserved0._24_4_ == 2) {
    puVar4 = &crt_locale_data_ptr;
    pcVar3 = s__s_scores5_rush_hi_00477c60;
  }
  else if (config_blob.reserved0._24_4_ == 1) {
    puVar4 = &crt_locale_data_ptr;
    pcVar3 = s__s_scores5_survival_hi_00477c48;
  }
  else {
    if (config_blob.reserved0._24_4_ == 3) {
      if (config_blob.hardcore == '\0') {
        crt_sprintf(&highscore_cache_path_buf,s__s_scores5_questhc_d__d_hi_00477c10,&crt_locale_data_ptr,
                    quest_stage_major,quest_stage_minor);
      }
      else {
        crt_sprintf(&highscore_cache_path_buf,s__s_scores5_quest_d__d_hi_00477c2c,&crt_locale_data_ptr,
                    quest_stage_major,quest_stage_minor);
      }
      goto LAB_0043b67f;
    }
    puVar4 = (undefined *)(config_blob.reserved0._128_4_ * 0x1b + 0x4803f0);
    pcVar3 = s_scores5_unknown_hi_00477bfc;
  }
  crt_sprintf(&highscore_cache_path_buf,pcVar3,puVar4);
LAB_0043b67f:
  if (config_blob.reserved0._20_4_ == 2) {
    uVar2 = 0xffffffff;
    pcVar3 = &highscore_cache_path_buf;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    (&highscore_cache_path_suffix0)[uVar2] = 0x5f;
    (&highscore_cache_path_suffix1)[uVar2] = 0x32;
    (&highscore_cache_path_suffix2)[uVar2] = 0x2e;
    (&highscore_cache_path_suffix3)[uVar2] = 0x68;
    (&highscore_cache_path_buf)[uVar2] = 0x69;
    (&highscore_cache_path_suffix4)[uVar2] = 0;
  }
  if (config_blob.reserved0._128_4_ != 0) {
    crt_sprintf(&highscore_named_cache_buf,&s_name_double_fmt,&highscore_cache_path_buf,
                config_blob.reserved0._128_4_ * 0x1b + 0x4803f0);
    console_printf(&console_log_queue,s_opening_named_cache_fmt,&highscore_named_cache_buf);
    return &highscore_named_cache_buf;
  }
  if (*(float *)((int)cv_verbose + 0xc) != 0.0) {
    console_printf(&console_log_queue,s_opening_path_fmt,&highscore_cache_path_buf);
  }
  return &highscore_cache_path_buf;
}



/* highscore_record_init @ 0043b750 */

/* fills the active high score record metadata for the current run */

void highscore_record_init(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 1;
  iVar1 = 1;
  iVar3 = 4;
  do {
    if (*(int *)((int)&weapon_usage_time + iVar3) < (int)(&weapon_usage_time)[iVar1]) {
      iVar3 = iVar1 * 4;
      iVar4 = iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x40);
  highscore_active_record.most_used_weapon_id = (uchar)iVar4;
  if ((int)highscore_active_record.shots_fired < (int)highscore_active_record.shots_hit) {
    highscore_active_record.shots_hit = highscore_active_record.shots_fired;
  }
  highscore_active_record.game_mode_id = config_blob.reserved0[0x18];
  highscore_active_record.quest_stage_major = quest_stage_major;
  highscore_active_record.quest_stage_minor = quest_stage_minor;
  highscore_active_record.flags = '\0';
  uVar2 = crt_rand();
  uVar2 = uVar2 & 0x8fffffff;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xf0000000) + 1;
  }
  highscore_active_record.reserved0._0_4_ = uVar2 + 0x310;
  highscore_active_record.full_version_marker = -(config_blob.hardcore != '\0') & 0x75;
  return;
}


