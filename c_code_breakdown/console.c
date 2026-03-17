/* console_input_clear @ 00401030 */

/* clears console input buffer */

void console_input_clear(void)

{
  console_input_ready = 0;
  console_input_cursor = 0;
  console_input_buf._0_1_ = 0;
  return;
}



/* console_input_buffer @ 00401050 */

/* returns console input buffer pointer */

char * console_input_buffer(void)

{
  return (char *)&console_input_buf;
}



/* console_input_poll @ 00401060 */

/* polls text input and updates console buffer */

int console_input_poll(void)

{
  int iVar1;
  
  iVar1 = (*grim_interface_ptr->vtable->grim_get_key_char)();
  if (console_input_enabled != '\0') {
    if ((iVar1 != 0) && (console_input_ready == '\0')) {
      if (iVar1 == 0xd) {
        console_input_ready = '\x01';
        *(undefined1 *)((int)&console_input_buf + console_input_cursor) = 0;
        console_input_cursor = console_input_cursor + 1;
        return 0;
      }
      if (iVar1 == 8) {
        if (0 < console_input_cursor) {
          console_input_cursor = console_input_cursor + -1;
        }
        *(undefined1 *)((int)&console_input_buf + console_input_cursor) = 0;
        return 0;
      }
      *(char *)((int)&console_input_buf + console_input_cursor) = (char)iVar1;
      iVar1 = console_input_cursor + 1;
      if (0x3ff < console_input_cursor + 1) {
        iVar1 = console_input_cursor;
      }
      console_input_cursor = iVar1;
      *(undefined1 *)((int)&console_input_buf + iVar1) = 0;
    }
    iVar1 = 0;
  }
  return iVar1;
}



/* callback_iterator @ 004010f0 */

/* [binja] int32_t __stdcall sub_4010f0(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) */

int callback_iterator(int arg1,int arg2,int arg3,int arg4)

{
  int iVar1;
  
  iVar1 = arg3 + -1;
  if (-1 < iVar1) {
    do {
      iVar1 = (*(code *)arg4)();
      arg3 = arg3 + -1;
    } while (arg3 != 0);
  }
  return iVar1;
}



/* console_cmd_arg_get @ 00401120 */

/* returns console token N (1..argc-1); returns empty string if out of range */

char * __cdecl console_cmd_arg_get(int index)

{
  if (((0 < console_cmd_argc) && (0 < index)) && (index < console_cmd_argc)) {
    return (&console_cmd_name)[index];
  }
  return PTR_s_empty_string_00471158;
}



/* console_cmd_argc_get @ 00401150 */

/* returns current console token count (argc; includes the command token at index 0) */

int console_cmd_argc_get(void)

{
  return console_cmd_argc;
}



/* console_global_init @ 00401170 */

/* [binja] int32_t sub_401170() */

int console_global_init(void)

{
  int *piVar1;
  
  piVar1 = console_init(&console_log_queue);
  return (int)piVar1;
}



/* console_atexit_register @ 00401180 */

/* [binja] int32_t sub_401180() */

int console_atexit_register(void)

{
  int iVar1;
  
  iVar1 = crt_atexit(&LAB_00401190);
  return iVar1;
}



/* console_clear_log @ 004011a0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* clears console log history and resets scroll state (clear command handler) */

void console_clear_log(void)

{
  undefined4 *ptr;
  
  ptr = console_log_head;
  if (console_log_head != (undefined4 *)0x0) {
    if ((void *)*console_log_head != (void *)0x0) {
      crt_free((void *)*console_log_head);
    }
    *ptr = 0;
    if ((void *)ptr[1] != (void *)0x0) {
      console_log_node_free((void *)ptr[1],'\x01');
    }
    ptr[1] = 0;
    crt_free(ptr);
  }
  console_log_head = (undefined4 *)0x0;
  crt_time_dst_flag_a = 0;
  crt_time_dst_flag_b = 0;
  return;
}



/* console_log_node_free @ 004011f0 */

/* frees a console log node (text + next chain) and optionally frees the node */

void __thiscall console_log_node_free(void *this,char free_self)

{
  if (*(void **)this != (void *)0x0) {
    crt_free(*(void **)this);
  }
  *(undefined4 *)this = 0;
  if (*(void **)((int)this + 4) != (void *)0x0) {
    console_log_node_free(*(void **)((int)this + 4),'\x01');
  }
  *(undefined4 *)((int)this + 4) = 0;
  if ((free_self & 1U) != 0) {
    crt_free(this);
  }
  return;
}



/* console_cmd_quit @ 00401240 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* sets the quit/exit flag (quit command handler) */

void console_cmd_quit(void)

{
  game_quit_flag = 1;
  return;
}



/* console_cmd_exec @ 00401250 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* executes a script file via console_exec_line (exec command handler) */

void console_cmd_exec(void)

{
  FILE *fp;
  char *pcVar1;
  
  if (console_cmd_argc != 2) {
    console_printf(&console_log_queue,s_exec_<script>_0047118c);
    return;
  }
  fp = (FILE *)crt_fopen(console_cmd_arg1,&DAT_00471160);
  if (fp != (FILE *)0x0) {
    console_printf(&console_log_queue,s_Executing___s__00471164,console_cmd_arg1);
    pcVar1 = crt_fgets(&config_file_line_buffer,0x1ff,(undefined4 *)fp);
    while (pcVar1 != (char *)0x0) {
      pcVar1 = _strchr(&config_file_line_buffer,10);
      if (pcVar1 != (char *)0x0) {
        *pcVar1 = '\0';
      }
      DAT_0047ea47 = 0;
      if ((((config_file_line_buffer != '/') && (DAT_0047e849 != '/')) && (config_file_line_buffer != '\n')) &&
         ((config_file_line_buffer != '\0' && (config_file_line_buffer != '#')))) {
        console_exec_line(&console_log_queue,&config_file_line_buffer);
      }
      pcVar1 = crt_fgets(&config_file_line_buffer,0x1ff,(undefined4 *)fp);
    }
    crt_fclose(fp);
    return;
  }
  console_printf(&console_log_queue,s_Cannot_open_file___s__00471174,console_cmd_arg1);
  return;
}



/* console_cmd_extend @ 00401340 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* extends console height (extendconsole command handler) */

void console_cmd_extend(void)

{
  longlong lVar1;
  
  lVar1 = __ftol();
  console_height_px = (int)lVar1;
  return;
}



/* console_cmd_minimize @ 00401360 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* minimizes console height (minimizeconsole command handler) */

void console_cmd_minimize(void)

{
  console_height_px = 300;
  return;
}



/* console_cmdlist @ 00401370 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* prints registered command names and a count (cmdlist command handler) */

void console_cmdlist(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = console_command_list_head; puVar1 != (undefined4 *)0x0;
      puVar1 = (undefined4 *)puVar1[1]) {
    console_printf(&console_log_queue,&DAT_004711ac,*puVar1);
    iVar2 = iVar2 + 1;
  }
  console_printf(&console_log_queue,s__i_commands_0047119c,iVar2);
  return;
}



/* console_vars @ 004013c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* prints registered cvar names and a count (vars command handler) */

void console_vars(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = console_log_queue; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)puVar1[1]) {
    console_printf(&console_log_queue,&DAT_004711ac,*puVar1);
    iVar2 = iVar2 + 1;
  }
  console_printf(&console_log_queue,s__i_variables_004711b0,iVar2);
  return;
}



/* console_echo @ 00401410 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* toggles echo on/off or prints args back into the console (echo command handler) */

void console_echo(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  byte *pbVar5;
  int index;
  bool bVar6;
  
  iVar2 = console_cmd_argc_get();
  if (iVar2 == 2) {
    pbVar3 = (byte *)console_cmd_arg_get(1);
    pbVar5 = &DAT_004711cc;
    do {
      bVar1 = *pbVar5;
      bVar6 = bVar1 < *pbVar3;
      if (bVar1 != *pbVar3) {
LAB_00401455:
        iVar2 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_0040145a;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar6 = bVar1 < pbVar3[1];
      if (bVar1 != pbVar3[1]) goto LAB_00401455;
      pbVar5 = pbVar5 + 2;
      pbVar3 = pbVar3 + 2;
    } while (bVar1 != 0);
    iVar2 = 0;
LAB_0040145a:
    if (iVar2 == 0) {
      console_echo_enabled = 0;
      return;
    }
  }
  iVar2 = console_cmd_argc_get();
  if (iVar2 == 2) {
    pbVar3 = (byte *)console_cmd_arg_get(1);
    pbVar5 = &DAT_004711c8;
    do {
      bVar1 = *pbVar5;
      bVar6 = bVar1 < *pbVar3;
      if (bVar1 != *pbVar3) {
LAB_004014a9:
        iVar2 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004014ae;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar5[1];
      bVar6 = bVar1 < pbVar3[1];
      if (bVar1 != pbVar3[1]) goto LAB_004014a9;
      pbVar5 = pbVar5 + 2;
      pbVar3 = pbVar3 + 2;
    } while (bVar1 != 0);
    iVar2 = 0;
LAB_004014ae:
    if (iVar2 == 0) {
      console_echo_enabled = 1;
      return;
    }
  }
  index = 1;
  iVar2 = console_cmd_argc_get();
  if (1 < iVar2) {
    do {
      pcVar4 = console_cmd_arg_get(index);
      console_printf(&console_log_queue,&DAT_004711c4,pcVar4);
      index = index + 1;
      iVar2 = console_cmd_argc_get();
    } while (index < iVar2);
  }
  console_printf(&console_log_queue,&console_empty_line_str);
  return;
}



/* console_cmd_set @ 00401510 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* sets a cvar from tokens (set command handler) */

void console_cmd_set(void)

{
  undefined4 *puVar1;
  
  if (console_cmd_argc != 3) {
    console_printf(&console_log_queue,s_set_<var>_<value>_004711e4);
    return;
  }
  puVar1 = console_register_cvar(&console_log_queue,console_cmd_arg1,console_cmd_arg2);
  console_printf(&console_log_queue,s___s__set_to___s__004711d0,*puVar1,puVar1[4]);
  return;
}



/* console_init @ 00401560 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* initializes the console state, registers core commands/cvars, and seeds prompt/version strings */

int * __fastcall console_init(int *console_state)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  *(undefined1 *)(console_state + 3) = 1;
  console_state[6] = 300;
  console_state[7] = -0x3c6a0000;
  console_state[9] = 0;
  console_state[2] = 0;
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    pcVar2 = strdup_malloc(s_version_00471264);
    *puVar1 = pcVar2;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
  }
  *console_state = (int)puVar1;
  puVar1[3] = 0x3f800000;
  pcVar2 = strdup_malloc(&DAT_00471260);
  *(char **)(*console_state + 0x10) = pcVar2;
  *(undefined4 *)(*console_state + 0x14) = 1;
  cvar_mono_font_ptr = console_register_cvar(console_state,s_con_monoFont_0047124c,&cvar_default_value_b);
  crt_time_zone_name_buf = 0;
  crt_time_zone_name_buf_1 = 0;
  crt_time_zone_name_buf_2 = 0;
  crt_time_zone_name_buf_3 = 0;
  console_cmd_argc = 0;
  console_register_command(console_state,console_cmd_cmdlist,console_cmdlist);
  console_register_command(console_state,&console_cmd_vars,console_vars);
  console_register_command(console_state,&console_cmd_echo,console_echo);
  console_register_command(console_state,&console_cmd_set,console_cmd_set);
  console_register_command(console_state,&console_cmd_quit,console_cmd_quit);
  console_register_command(console_state,console_cmd_clear,console_clear_log);
  console_register_command(console_state,console_cmd_extend,console_cmd_extend);
  console_register_command(console_state,console_cmd_minimize,console_cmd_minimize);
  console_register_command(console_state,&console_cmd_exec,console_cmd_exec);
  puVar1 = operator_new(8);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[1] = 0;
    *puVar1 = 0;
  }
  console_state[4] = (int)puVar1;
  pcVar2 = strdup_malloc(&s_empty_string);
  *(char **)console_state[4] = pcVar2;
  console_state[5] = 0;
  return console_state;
}



/* console_destroy @ 004016e0 */

/* [binja] void __fastcall sub_4016e0(int32_t* arg1) */

void __fastcall console_destroy(int *arg1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)arg1[2];
  if (puVar1 != (undefined4 *)0x0) {
    if ((void *)*puVar1 != (void *)0x0) {
      crt_free((void *)*puVar1);
    }
    *puVar1 = 0;
    if ((void *)puVar1[1] != (void *)0x0) {
      console_log_node_free((void *)puVar1[1],'\x01');
    }
    puVar1[1] = 0;
    crt_free(puVar1);
  }
  puVar1 = (undefined4 *)*arg1;
  arg1[2] = 0;
  if (puVar1 != (undefined4 *)0x0) {
    if ((void *)*puVar1 != (void *)0x0) {
      crt_free((void *)*puVar1);
    }
    *puVar1 = 0;
    crt_free(puVar1);
  }
  puVar1 = (undefined4 *)arg1[1];
  *arg1 = 0;
  if (puVar1 != (undefined4 *)0x0) {
    if ((void *)*puVar1 != (void *)0x0) {
      crt_free((void *)*puVar1);
    }
    *puVar1 = 0;
    crt_free(puVar1);
  }
  puVar1 = (undefined4 *)arg1[4];
  arg1[1] = 0;
  if (puVar1 != (undefined4 *)0x0) {
    if ((void *)*puVar1 != (void *)0x0) {
      crt_free((void *)*puVar1);
    }
    *puVar1 = 0;
    if ((void *)puVar1[1] != (void *)0x0) {
      console_log_node_free((void *)puVar1[1],'\x01');
    }
    puVar1[1] = 0;
    crt_free(puVar1);
  }
  arg1[4] = 0;
  return;
}



/* console_push_line @ 004017a0 */

/* pushes line into console queue */

char __thiscall console_push_line(void *this,char *line)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  char *pcVar5;
  uint uVar6;
  
  uVar6 = (uint)*(byte *)((int)this + 0xc);
  if (*(byte *)((int)this + 0xc) != 0) {
    if (*(int *)((int)this + 0x20) == 0x1000) {
      iVar1 = *(int *)(*(int *)((int)this + 8) + 4);
      iVar2 = *(int *)(iVar1 + 4);
      iVar3 = *(int *)((int)this + 8);
      while (iVar2 != 0) {
        iVar2 = *(int *)(*(int *)(iVar1 + 4) + 4);
        iVar3 = iVar1;
        iVar1 = *(int *)(iVar1 + 4);
      }
      puVar4 = *(undefined4 **)(iVar3 + 4);
      if (puVar4 != (undefined4 *)0x0) {
        if ((void *)*puVar4 != (void *)0x0) {
          crt_free((void *)*puVar4);
        }
        *puVar4 = 0;
        if ((void *)puVar4[1] != (void *)0x0) {
          console_log_node_free((void *)puVar4[1],'\x01');
        }
        puVar4[1] = 0;
        crt_free(puVar4);
      }
      *(undefined4 *)(iVar3 + 4) = 0;
      *(int *)((int)this + 0x20) = *(int *)((int)this + 0x20) + -1;
    }
    puVar4 = operator_new(8);
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = (undefined4 *)0x0;
    }
    else {
      puVar4[1] = 0;
      *puVar4 = 0;
    }
    pcVar5 = strdup_malloc(line);
    *puVar4 = pcVar5;
    puVar4[1] = *(undefined4 *)((int)this + 8);
    uVar6 = *(int *)((int)this + 0x20) + 1;
    *(undefined4 **)((int)this + 8) = puVar4;
    *(uint *)((int)this + 0x20) = uVar6;
  }
  return (char)uVar6;
}



/* console_printf @ 00401870 */

/* formats then pushes line */

char __cdecl console_printf(void *console_state,char *fmt,...)

{
  char cVar1;
  
  cVar1 = '\0';
  if (*(char *)((int)console_state + 0xc) != '\0') {
    crt_vsprintf(&console_printf_buffer,fmt,&stack0x0000000c);
    cVar1 = console_push_line(console_state,&console_printf_buffer);
  }
  return cVar1;
}



/* console_set_open @ 004018b0 */

/* sets console_open_flag (console_state+0x28) and console_input_enabled (0x0047f4d4); flushes input
   via Grim2D vtable +0x4c */

void __thiscall console_set_open(void *this,char open)

{
  *(char *)((int)this + 0x28) = open;
  console_input_enabled = open;
  (*grim_interface_ptr->vtable->grim_flush_input)();
  return;
}



/* console_history_apply @ 004018d0 */

/* loads a history entry into the input buffer (used by Up/Down navigation) */

void __fastcall console_history_apply(int console_state)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  
  iVar7 = 0;
  iVar1 = *(int *)(console_state + 0x14) + -1;
  puVar3 = *(undefined4 **)(console_state + 0x10);
  puVar4 = *(undefined4 **)(console_state + 0x10);
  if (0 < iVar1) {
    do {
      puVar4 = (undefined4 *)puVar3[1];
      if (puVar4 == (undefined4 *)0x0) {
        *(int *)(console_state + 0x14) = iVar7;
        puVar4 = puVar3;
        break;
      }
      iVar7 = iVar7 + 1;
      puVar3 = puVar4;
    } while (iVar7 < iVar1);
  }
  uVar5 = 0xffffffff;
  pcVar8 = (char *)*puVar4;
  do {
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar2 != '\0');
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  pcVar9 = (char *)&console_input_buf;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  uVar5 = 0xffffffff;
  pcVar8 = (char *)&console_input_buf;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar2 != '\0');
  console_input_cursor = ~uVar5 - 1;
  console_input_ready = 0;
  return;
}



/* console_exec_line @ 00401940 */

/* executes a console command or cvar assignment from a line */

char __thiscall console_exec_line(void *this,char *line)

{
  char cVar1;
  undefined4 *puVar2;
  void *pvVar3;
  char *pcVar4;
  float fVar5;
  
  console_tokenize_line(line);
  if (console_cmd_argc != 0) {
    puVar2 = console_cvar_find(this,console_cmd_name);
    pvVar3 = console_command_find(this,console_cmd_name);
    if (puVar2 == (undefined4 *)0x0) {
      if (pvVar3 == (void *)0x0) {
        cVar1 = console_printf(this,s_Unknown_command___s__0047126c);
        return cVar1;
      }
      cVar1 = (**(code **)((int)pvVar3 + 8))();
      return cVar1;
    }
    if (console_cmd_argc == 2) {
      if ((void *)puVar2[4] != (void *)0x0) {
        crt_free((void *)puVar2[4]);
      }
      puVar2[4] = 0;
      pcVar4 = strdup_malloc(console_cmd_arg1);
      puVar2[4] = pcVar4;
      fVar5 = crt_atof_l(console_cmd_arg1,console_cmd_arg1);
      puVar2[3] = fVar5;
      if (*(char *)((int)this + 0xc) != '\0') {
        cVar1 = console_printf(this,s___s__set_to___s____ff__00471298,*puVar2,puVar2[4],
                               (double)fVar5);
        return cVar1;
      }
    }
    else if (*(char *)((int)this + 0xc) != '\0') {
      cVar1 = console_printf(this,s___s__is___s____ff__00471284,*puVar2,puVar2[4],
                             (double)(float)puVar2[3]);
      return cVar1;
    }
  }
  return '\0';
}



/* console_update @ 00401a40 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* console update loop: input polling, history, autocomplete, and key handling */

void __fastcall console_update(int console_state)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  bool bVar12;
  float10 fVar13;
  
  if (*(char *)(console_state + 0x28) == '\0') {
    console_slide_anim_t = frame_dt_stored * 3.5 + console_slide_anim_t;
    if (1.0 < console_slide_anim_t) {
      console_slide_anim_t = 1.0;
    }
    fVar13 = (float10)fsin(((float10)1.0 - (float10)console_slide_anim_t) * (float10)1.5707964);
    *(float *)(console_state + 0x1c) =
         (float)(fVar13 * (float10)*(int *)(console_state + 0x18) -
                (float10)*(int *)(console_state + 0x18));
    return;
  }
  console_slide_anim_t = console_slide_anim_t - frame_dt_stored * 3.5;
  if (console_slide_anim_t < 0.0) {
    console_slide_anim_t = 0.0;
  }
  fVar13 = (float10)fsin(((float10)1.0 - (float10)console_slide_anim_t) * (float10)1.5707964);
  *(float *)(console_state + 0x1c) =
       (float)(fVar13 * (float10)*(int *)(console_state + 0x18) -
              (float10)*(int *)(console_state + 0x18));
  console_input_poll();
  iVar3 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x1d);
  if ((char)iVar3 == '\0') {
    iVar3 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x9d);
    if ((char)iVar3 != '\0') goto LAB_00401ac4;
LAB_00401add:
    iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(200);
    if ((char)iVar3 != '\0') {
      *(int *)(console_state + 0x14) = *(int *)(console_state + 0x14) + 1;
      console_history_apply(console_state);
    }
  }
  else {
LAB_00401ac4:
    iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(200);
    if ((char)iVar3 == '\0') goto LAB_00401add;
    *(int *)(console_state + 0x24) = *(int *)(console_state + 0x24) + 1;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x1d);
  if ((char)iVar3 == '\0') {
    iVar3 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x9d);
    if ((char)iVar3 != '\0') goto LAB_00401b24;
LAB_00401b3d:
    iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd0);
    if ((char)iVar3 != '\0') {
      iVar3 = *(int *)(console_state + 0x14) + -1;
      *(int *)(console_state + 0x14) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(console_state + 0x14) = 0;
      }
      console_history_apply(console_state);
    }
  }
  else {
LAB_00401b24:
    iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd0);
    if ((char)iVar3 == '\0') goto LAB_00401b3d;
    *(int *)(console_state + 0x24) = *(int *)(console_state + 0x24) + -1;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xcb);
  if (((char)iVar3 != '\0') &&
     (console_input_cursor = console_input_cursor + -1, console_input_cursor < 0)) {
    console_input_cursor = 0;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xcd);
  if ((char)iVar3 != '\0') {
    uVar7 = 0xffffffff;
    console_input_cursor = console_input_cursor + 1;
    pcVar4 = (char *)&console_input_buf;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    if ((int)(~uVar7 - 1) < console_input_cursor) {
      uVar7 = 0xffffffff;
      pcVar4 = (char *)&console_input_buf;
      do {
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      console_input_cursor = ~uVar7 - 1;
    }
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xc9);
  if ((char)iVar3 != '\0') {
    *(int *)(console_state + 0x24) = *(int *)(console_state + 0x24) + 2;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xd1);
  if (((char)iVar3 != '\0') &&
     (iVar3 = *(int *)(console_state + 0x24) + -2, *(int *)(console_state + 0x24) = iVar3, iVar3 < 0
     )) {
    *(undefined4 *)(console_state + 0x24) = 0;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(199);
  if ((char)iVar3 != '\0') {
    *(int *)(console_state + 0x24) = *(int *)(console_state + 0x24) + 0x14;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xcf);
  if ((char)iVar3 != '\0') {
    *(undefined4 *)(console_state + 0x24) = 0;
  }
  iVar3 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0xf);
  if ((char)iVar3 != '\0') {
    pcVar4 = console_input_buffer();
    console_tokenize_line(pcVar4);
    pcVar4 = console_input_buffer();
    pcVar4 = console_cvar_autocomplete((void *)console_state,pcVar4);
    if (pcVar4 == (char *)0x0) {
      pcVar4 = console_input_buffer();
      pcVar4 = console_command_autocomplete((void *)console_state,pcVar4);
      if (pcVar4 == (char *)0x0) goto LAB_00401cb5;
    }
    uVar7 = 0xffffffff;
    pcVar10 = pcVar4;
    do {
      pcVar11 = pcVar10;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar11 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    pcVar10 = pcVar11 + -uVar7;
    pcVar11 = (char *)&console_input_buf;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
    uVar7 = 0xffffffff;
    do {
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    console_input_cursor = ~uVar7 - 1;
  }
LAB_00401cb5:
  if (console_input_ready == '\0') {
    console_input_buffer();
    (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
    return;
  }
  pbVar5 = (byte *)console_input_buffer();
  pbVar9 = (byte *)**(undefined4 **)(console_state + 0x10);
  do {
    bVar2 = *pbVar9;
    bVar12 = bVar2 < *pbVar5;
    if (bVar2 != *pbVar5) {
LAB_00401cf1:
      iVar3 = (1 - (uint)bVar12) - (uint)(bVar12 != 0);
      goto LAB_00401cf6;
    }
    if (bVar2 == 0) break;
    bVar2 = pbVar9[1];
    bVar12 = bVar2 < pbVar5[1];
    if (bVar2 != pbVar5[1]) goto LAB_00401cf1;
    pbVar9 = pbVar9 + 2;
    pbVar5 = pbVar5 + 2;
  } while (bVar2 != 0);
  iVar3 = 0;
LAB_00401cf6:
  if (iVar3 != 0) {
    puVar6 = operator_new(8);
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      puVar6[1] = 0;
      *puVar6 = 0;
    }
    pcVar4 = console_input_buffer();
    pcVar4 = strdup_malloc(pcVar4);
    *puVar6 = pcVar4;
    puVar6[1] = *(undefined4 *)(console_state + 0x10);
    *(undefined4 **)(console_state + 0x10) = puVar6;
  }
  *(undefined4 *)(console_state + 0x14) = 0;
  pcVar4 = console_input_buffer();
  console_printf(&console_log_queue,s_>__s_004712b0,pcVar4);
  pcVar4 = console_input_buffer();
  console_exec_line((void *)console_state,pcVar4);
  console_input_clear();
  (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x1c);
  return;
}



/* console_render @ 00401dd0 */

/* [binja] int32_t __fastcall sub_401dd0(void* arg1) */

int __fastcall console_render(void *arg1)

{
  IGrim2D_vtbl *pIVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  float10 extraout_ST0;
  float10 fVar8;
  float fVar9;
  char *text;
  float fStack_4c;
  undefined4 *puVar10;
  undefined4 *puVar11;
  float local_1c;
  float local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar5 = *(int *)((int)arg1 + 0x18);
  local_18 = (float)-iVar5;
  fVar2 = (float)(int)local_18;
  fVar9 = *(float *)((int)arg1 + 0x1c);
  iVar3 = CONCAT22((short)((uint)local_18 >> 0x10),
                   (ushort)(fVar2 < fVar9) << 8 | (ushort)(NAN(fVar2) || NAN(fVar9)) << 10 |
                   (ushort)(fVar2 == fVar9) << 0xe);
  if (fVar2 < fVar9) {
    puVar7 = *(undefined4 **)((int)arg1 + 8);
    iVar3 = ((int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4) + -2;
    if (*(int *)((int)arg1 + 0x20) <= iVar3) {
      iVar3 = *(int *)((int)arg1 + 0x20);
    }
    local_1c = ((float)iVar5 + *(float *)((int)arg1 + 0x1c)) / (float)iVar5;
    if (local_1c <= 1.0) {
      if (local_1c < 0.0) {
        local_1c = 0.0;
      }
    }
    else {
      local_1c = 1.0;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(0.6,0.6,0.6,local_1c);
    (*grim_interface_ptr->vtable->grim_set_rotation)(0.0);
    uStack_14 = *(undefined4 *)((int)arg1 + 0x1c);
    fStack_4 = local_1c;
    puVar11 = &uStack_10;
    uStack_10 = 0x3e100000;
    uStack_c = 0x3e400000;
    fStack_8 = 0.2890625;
    local_18 = 0.0;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)
              (&local_18,screen_width_f,(float)*(int *)((int)arg1 + 0x18));
    (*grim_interface_ptr->vtable->grim_set_color)
              (0.1,0.6,1.0,
               ((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) /
               (float)*(int *)((int)arg1 + 0x18));
    puVar10 = &uStack_14;
    local_18 = (float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c);
    uStack_14 = 0x3e600000;
    uStack_10 = 0x3e880000;
    uStack_c = 0x3ebc0000;
    local_1c = 0.0;
    fStack_8 = local_18 / (float)*(int *)((int)arg1 + 0x18);
    local_18 = local_18 - 4.0;
    (*grim_interface_ptr->vtable->grim_draw_rect_filled)(&local_1c,screen_width_f,4.0);
    (*grim_interface_ptr->vtable->grim_end_batch)(puVar10,puVar11);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
    (*grim_interface_ptr->vtable->grim_set_color)
              (1.0,1.0,1.0,
               (((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) /
               (float)*(int *)((int)arg1 + 0x18)) * 0.3);
    (*grim_interface_ptr->vtable->grim_draw_text_small)
              (screen_width_f - 210.0,
               ((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) - 18.0,
               s_Crimsonland_1_9_93_004712c4);
    (*grim_interface_ptr->vtable->grim_set_color)
              (1.0,1.0,1.0,
               (((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) /
               (float)*(int *)((int)arg1 + 0x18)) * 0.5);
    (*grim_interface_ptr->vtable->grim_set_color)
              (1.0,1.0,1.0,
               ((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) /
               (float)*(int *)((int)arg1 + 0x18));
    if (*(float *)(cvar_mono_font_ptr + 0xc) == 0.0) {
      pIVar1 = grim_interface_ptr->vtable;
      pcVar4 = console_input_buffer();
      (*pIVar1->grim_draw_text_small_fmt)
                (grim_interface_ptr,10.0,(float)((iVar3 + 1) * 0x10) + *(float *)((int)arg1 + 0x1c),
                 &s_creature_name_font_spec,pcVar4);
    }
    else {
      fVar9 = (float)((iVar3 + 1) * 0x10);
      (*grim_interface_ptr->vtable->grim_draw_text_mono)
                (10.0,fVar9 + *(float *)((int)arg1 + 0x1c),&console_prompt_string);
      pIVar1 = grim_interface_ptr->vtable;
      pcVar4 = console_input_buffer();
      (*pIVar1->grim_draw_text_mono)(26.0,fVar9 + *(float *)((int)arg1 + 0x1c),pcVar4);
    }
    (*grim_interface_ptr->vtable->grim_set_color)
              (0.6,0.6,0.7,
               ((float)*(int *)((int)arg1 + 0x18) + *(float *)((int)arg1 + 0x1c)) /
               (float)*(int *)((int)arg1 + 0x18));
    for (iVar5 = *(int *)((int)arg1 + 0x24); 0 < iVar5; iVar5 = iVar5 + -1) {
      if (puVar7 == (undefined4 *)0x0) goto LAB_004021ca;
      puVar7 = (undefined4 *)puVar7[1];
    }
    if (puVar7 != (undefined4 *)0x0) {
      iVar5 = iVar3 << 4;
      do {
        if (iVar3 < 0) break;
        fVar9 = (float)iVar5 + *(float *)((int)arg1 + 0x1c);
        if (*(float *)(cvar_mono_font_ptr + 0xc) == 0.0) {
          (*grim_interface_ptr->vtable->grim_draw_text_small)(10.0,fVar9,(char *)*puVar7);
        }
        else {
          (*grim_interface_ptr->vtable->grim_draw_text_mono)(10.0,fVar9,(char *)*puVar7);
        }
        puVar7 = (undefined4 *)puVar7[1];
        iVar3 = iVar3 + -1;
        iVar5 = iVar5 + -0x10;
      } while (puVar7 != (undefined4 *)0x0);
    }
LAB_004021ca:
    iVar5 = *(int *)((int)arg1 + 0x18);
    iVar6 = ((int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4) + -2;
    iVar3 = *(int *)((int)arg1 + 0x20);
    if (iVar6 < *(int *)((int)arg1 + 0x20)) {
      iVar3 = iVar6;
    }
    fsin((float10)game_time_s * (float10)3.0);
    crt_ci_pow();
    fVar8 = extraout_ST0;
    if (extraout_ST0 < (float10)0.2) {
      fVar8 = (float10)0.2;
    }
    fStack_4c = (float)((((float10)iVar5 + (float10)*(float *)((int)arg1 + 0x1c)) / (float10)iVar5)
                       * fVar8);
    if (fStack_4c <= 1.0) {
      if (fStack_4c < 0.0) {
        fStack_4c = 0.0;
      }
    }
    else {
      fStack_4c = 1.0;
    }
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,fStack_4c);
    if (*(float *)(cvar_mono_font_ptr + 0xc) == 0.0) {
      pIVar1 = grim_interface_ptr->vtable;
      text = &console_cmd_table_entry;
      fVar9 = (float)((iVar3 + 1) * 0x10) + *(float *)((int)arg1 + 0x1c) + 2.0;
      pcVar4 = console_input_buffer();
      iVar5 = (*pIVar1->grim_measure_text_width)(pcVar4);
      (*pIVar1->grim_draw_text_small)((float)iVar5 + 16.0,fVar9,text);
    }
    else {
      (*grim_interface_ptr->vtable->grim_draw_text_mono)
                ((float)(console_input_cursor << 3) + 26.0,
                 (float)((iVar3 + 1) * 0x10) + *(float *)((int)arg1 + 0x1c) + 2.0,&console_cmd_table_entry);
    }
    iVar3 = (*grim_interface_ptr->vtable->grim_set_config_var)(0x15,2);
  }
  return iVar3;
}



/* console_register_cvar @ 00402350 */

/* registers or updates a console cvar entry (stores string + float value) */

void * __thiscall console_register_cvar(void *this,char *name,char *value)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  char *pcVar4;
  undefined4 *puVar5;
  void *this_00;
  float fVar6;
  
  pvVar3 = console_cvar_find(this,name);
  if (pvVar3 != (void *)0x0) {
    if (*(void **)((int)pvVar3 + 0x10) != (void *)0x0) {
      crt_free(*(void **)((int)pvVar3 + 0x10));
    }
    *(undefined4 *)((int)pvVar3 + 0x10) = 0;
    pcVar4 = strdup_malloc(value);
    *(char **)((int)pvVar3 + 0x10) = pcVar4;
    fVar6 = crt_atof_l(this_00,value);
    *(float *)((int)pvVar3 + 0xc) = fVar6;
    return pvVar3;
  }
  iVar1 = *(int *)this;
  if (iVar1 == 0) {
    puVar5 = operator_new(0x24);
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      puVar5[6] = 0;
      puVar5[7] = 0;
      puVar5[8] = 0;
      pcVar4 = strdup_malloc(name);
      *puVar5 = pcVar4;
      puVar5[1] = 0;
      puVar5[2] = 0;
      puVar5[3] = 0;
      puVar5[4] = 0;
      puVar5[5] = 0;
    }
    *(undefined4 **)this = puVar5;
    pcVar4 = strdup_malloc(value);
    pvVar3 = *(void **)this;
    *(char **)((int)pvVar3 + 0x10) = pcVar4;
    fVar6 = crt_atof_l(pvVar3,value);
    *(float *)(*(int *)this + 0xc) = fVar6;
    return *(void **)this;
  }
  for (iVar2 = *(int *)(iVar1 + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    iVar1 = iVar2;
  }
  puVar5 = operator_new(0x24);
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0;
    pcVar4 = strdup_malloc(name);
    *puVar5 = pcVar4;
    puVar5[1] = 0;
    puVar5[2] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
  }
  *(undefined4 **)(iVar1 + 4) = puVar5;
  pcVar4 = strdup_malloc(value);
  pvVar3 = *(void **)(iVar1 + 4);
  *(char **)((int)pvVar3 + 0x10) = pcVar4;
  fVar6 = crt_atof_l(pvVar3,value);
  *(float *)(*(int *)(iVar1 + 4) + 0xc) = fVar6;
  return *(void **)(iVar1 + 4);
}



/* console_cvar_find @ 00402480 */

/* finds a cvar entry by name */

void * __thiscall console_cvar_find(void *this,char *name)

{
  byte bVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  puVar2 = *(undefined4 **)this;
  do {
    if (puVar2 == (undefined4 *)0x0) {
      return (void *)0x0;
    }
    pbVar5 = (byte *)*puVar2;
    pbVar3 = (byte *)name;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004024ba:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004024bf;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004024ba;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004024bf:
    if (iVar4 == 0) {
      return puVar2;
    }
    puVar2 = (undefined4 *)puVar2[1];
  } while( true );
}



/* console_cvar_unregister @ 004024e0 */

/* removes a cvar entry by name */

char __thiscall console_cvar_unregister(void *this,char *name)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  
  pvVar3 = console_cvar_find(this,name);
  if (pvVar3 != (void *)0x0) {
    pvVar1 = *(void **)this;
    if (pvVar3 == pvVar1) {
      *(undefined4 *)this = *(undefined4 *)((int)pvVar1 + 4);
      return '\x01';
    }
    while (pvVar2 = pvVar1, pvVar2 != (void *)0x0) {
      pvVar1 = *(void **)((int)pvVar2 + 4);
      if (*(void **)((int)pvVar2 + 4) == pvVar3) {
        *(undefined4 *)((int)pvVar2 + 4) = *(undefined4 *)(*(int *)((int)pvVar2 + 4) + 4);
        return '\x01';
      }
    }
  }
  return '\0';
}



/* console_command_unregister @ 00402530 */

/* removes a console command entry by name */

char __thiscall console_command_unregister(void *this,char *name)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  
  pvVar3 = console_command_find(this,name);
  if (pvVar3 != (void *)0x0) {
    pvVar1 = *(void **)((int)this + 4);
    if (pvVar3 == pvVar1) {
      *(undefined4 *)((int)this + 4) = *(undefined4 *)((int)pvVar1 + 4);
      return '\x01';
    }
    while (pvVar2 = pvVar1, pvVar2 != (void *)0x0) {
      pvVar1 = *(void **)((int)pvVar2 + 4);
      if (*(void **)((int)pvVar2 + 4) == pvVar3) {
        *(undefined4 *)((int)pvVar2 + 4) = *(undefined4 *)(*(int *)((int)pvVar2 + 4) + 4);
        return '\x01';
      }
    }
  }
  return '\0';
}



/* console_tokenize_line @ 00402580 */

/* splits a console line into tokens */

void console_tokenize_line(char *line)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  char **ppcVar5;
  char *pcVar6;
  int iVar7;
  
  console_cmd_argc = 0;
  iVar7 = console_cmd_argc;
  if (line != (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar2 = line;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (((~uVar3 - 1 < 2) || (*line != '/')) || (line[1] != '/')) {
      uVar3 = 0xffffffff;
      do {
        pcVar2 = line;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar2 = line + 1;
        cVar1 = *line;
        line = pcVar2;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      pcVar2 = pcVar2 + -uVar3;
      pcVar6 = (char *)&crt_time_zone_name_buf;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar6 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar6 = pcVar6 + 1;
      }
      pcVar2 = crt_strtok((char *)&crt_time_zone_name_buf,&DAT_004712d8);
      iVar7 = console_cmd_argc;
      if (pcVar2 != (char *)0x0) {
        iVar7 = 1;
        ppcVar5 = &console_cmd_arg1;
        console_cmd_name = pcVar2;
        while (pcVar2 = crt_strtok((char *)0x0,&DAT_004712d8), pcVar2 != (char *)0x0) {
          *ppcVar5 = pcVar2;
          iVar7 = iVar7 + 1;
          ppcVar5 = ppcVar5 + 1;
        }
      }
    }
  }
  console_cmd_argc = iVar7;
  return;
}



/* console_cvar_autocomplete @ 00402630 */

/* returns exact or prefix-matched cvar name */

char * __thiscall console_cvar_autocomplete(void *this,char *prefix)

{
  char cVar1;
  byte bVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  char *pcVar9;
  bool bVar10;
  
  uVar6 = 0xffffffff;
  pcVar9 = prefix;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (~uVar6 - 1 != 0) {
    puVar8 = *(undefined4 **)this;
    for (puVar3 = puVar8; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)puVar3[1]) {
      pbVar7 = (byte *)*puVar3;
      pbVar4 = (byte *)prefix;
      do {
        bVar2 = *pbVar4;
        bVar10 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_0040267e:
          iVar5 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00402683;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar4[1];
        bVar10 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_0040267e;
        pbVar4 = pbVar4 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar2 != 0);
      iVar5 = 0;
LAB_00402683:
      if (iVar5 == 0) {
        return (char *)*puVar3;
      }
    }
    if (puVar8 != (undefined4 *)0x0) {
      do {
        iVar5 = _strncmp(prefix,(char *)*puVar8,~uVar6 - 1);
        if (iVar5 == 0) {
          return (char *)*puVar8;
        }
        puVar8 = (undefined4 *)puVar8[1];
      } while (puVar8 != (undefined4 *)0x0);
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}



/* console_register_command @ 004026e0 */

/* registers a console command and handler */

void __thiscall console_register_command(void *this,char *name,void *handler)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  
  puVar3 = operator_new(0xc);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    pcVar4 = strdup_malloc(name);
    *puVar3 = pcVar4;
    puVar3[1] = 0;
    puVar3[2] = 0;
  }
  puVar3[2] = handler;
  iVar1 = *(int *)((int)this + 4);
  if (iVar1 != 0) {
    for (iVar2 = *(int *)(iVar1 + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
      iVar1 = iVar2;
    }
    *(undefined4 **)(iVar1 + 4) = puVar3;
    return;
  }
  *(undefined4 **)((int)this + 4) = puVar3;
  return;
}



/* console_command_find @ 00402750 */

/* finds a console command entry by name */

void * __thiscall console_command_find(void *this,char *name)

{
  byte bVar1;
  undefined4 *puVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  puVar2 = *(undefined4 **)((int)this + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      return (void *)0x0;
    }
    pbVar5 = (byte *)*puVar2;
    pbVar3 = (byte *)name;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_0040278b:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_00402790;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_0040278b;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00402790:
    if (iVar4 == 0) {
      return puVar2;
    }
    puVar2 = (undefined4 *)puVar2[1];
  } while( true );
}



/* console_command_autocomplete @ 004027b0 */

/* returns exact or prefix-matched command name */

char * __thiscall console_command_autocomplete(void *this,char *prefix)

{
  char cVar1;
  byte bVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  char *pcVar9;
  bool bVar10;
  
  uVar6 = 0xffffffff;
  pcVar9 = prefix;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  if (~uVar6 - 1 != 0) {
    puVar8 = *(undefined4 **)((int)this + 4);
    for (puVar3 = puVar8; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)puVar3[1]) {
      pbVar7 = (byte *)*puVar3;
      pbVar4 = (byte *)prefix;
      do {
        bVar2 = *pbVar4;
        bVar10 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_004027ff:
          iVar5 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
          goto LAB_00402804;
        }
        if (bVar2 == 0) break;
        bVar2 = pbVar4[1];
        bVar10 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_004027ff;
        pbVar4 = pbVar4 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar2 != 0);
      iVar5 = 0;
LAB_00402804:
      if (iVar5 == 0) {
        return (char *)*puVar3;
      }
    }
    if (puVar8 != (undefined4 *)0x0) {
      do {
        iVar5 = _strncmp(prefix,(char *)*puVar8,~uVar6 - 1);
        if (iVar5 == 0) {
          return (char *)*puVar8;
        }
        puVar8 = (undefined4 *)puVar8[1];
      } while (puVar8 != (undefined4 *)0x0);
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}



/* console_flush_log @ 00402860 */

/* flushes console lines to the log file */

int __fastcall console_flush_log(void *console_state,char *filename)

{
  char cVar1;
  char *pcVar2;
  FILE *fp;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *in_stack_00000004;
  char *pcVar7;
  
  pcVar7 = &DAT_004712dc;
  pcVar2 = game_build_path(in_stack_00000004);
  fp = (FILE *)crt_fopen(pcVar2,pcVar7);
  if (fp == (FILE *)0x0) {
    return 0;
  }
  iVar4 = *(int *)((int)console_state + 0x20);
  do {
    iVar4 = iVar4 + -1;
    if (iVar4 < 0) {
      crt_fflush((int *)fp);
      iVar4 = crt_fclose(fp);
      return CONCAT31((int3)((uint)iVar4 >> 8),1);
    }
    puVar3 = *(undefined4 **)((int)console_state + 8);
    iVar5 = iVar4;
    if (0 < iVar4) {
      do {
        puVar3 = (undefined4 *)puVar3[1];
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    uVar6 = 0xffffffff;
    pcVar2 = (char *)*puVar3;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    crt_fwrite((char *)*puVar3,~uVar6 - 1,1,(int *)fp);
  } while( true );
}



/* console_hotkey_update @ 0040c1c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* per-frame input/update function; contains console hotkey block (DIK_GRAVE) at 0x0040c360 and
   DIK_F12 check; entry identified via WinDbg */

void console_hotkey_update(void)

{
  IGrim2D_vtbl *pIVar1;
  int iVar2;
  char *pcVar3;
  FILE *fp;
  float *pfVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  float10 extraout_ST0_05;
  float10 extraout_ST0_06;
  float10 extraout_ST0_07;
  longlong lVar8;
  float y;
  float fVar9;
  uint in_stack_ffffffc0;
  float fStack_20;
  float fStack_1c;
  uint auStack_10 [4];
  
  (*grim_interface_ptr->vtable->grim_get_frame_dt)();
  frame_dt = (float)extraout_ST0;
  if (quest_unlock_index < 0x28) {
    config_blob.hardcore = '\0';
  }
  iVar2 = game_is_full_version();
  if ((char)iVar2 == '\0') {
    if ((int)game_status_blob.game_sequence_id < 0) {
      game_status_blob.game_sequence_id = 1200000;
    }
    game_status_blob.game_sequence_id = game_sequence_get();
    config_blob.hardcore = '\0';
  }
  iVar2 = game_is_full_version();
  if ((char)iVar2 != '\0') {
    main_menu_version_callback = &LAB_00447350;
    shareware_offer_seen_latch = '\0';
  }
  if ((full_version_ui_adjusted == '\0') && (iVar2 = game_is_full_version(), (char)iVar2 != '\0')) {
    main_menu_button_y_offset = main_menu_button_y_offset + 60.0;
    main_menu_button_x_cached = main_menu_start_x;
    main_menu_button_y_cached = main_menu_start_y;
    full_version_ui_adjusted = '\x01';
    ui_button_visible_flag = 0;
    main_menu_button_spacing = main_menu_button_spacing - 20.0;
  }
  if ((audio_suspend_flag == '\0') &&
     (pcVar3 = (char *)(*grim_interface_ptr->vtable->grim_get_config_var)(auStack_10,0x57),
     *pcVar3 != '\0')) {
    if ((render_pass_mode == '\0') || (config_blob.reserved0._24_4_ != 3)) {
      terrain_generate_random();
    }
    else {
      uVar6 = quest_stage_minor - 1;
      uVar7 = quest_stage_major - 1;
      if (9 < (int)uVar6) {
        uVar6 = uVar6 % 10;
      }
      if (3 < (int)uVar7) {
        uVar7 = uVar7 + (uVar7 >> 2) * -4;
      }
      terrain_generate(&quest_selected_meta + uVar7 + uVar6 * 10);
    }
    (*grim_interface_ptr->vtable->grim_set_config_var)(0x57,in_stack_ffffffc0 & 0xffffff00);
  }
  iVar2 = game_is_full_version();
  if (((char)iVar2 == '\0') && (10 < quest_unlock_index)) {
    quest_unlock_index = 10;
  }
  if (audio_suspend_flag != '\0') {
    audio_resume_all();
    return;
  }
  game_time_ms = game_time_ms + frame_dt_ms;
  iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x29);
  if ((char)iVar2 != '\0') {
    console_set_open(&console_log_queue,console_open_flag == '\0');
  }
  console_update(0x47eea0);
  iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(0x58);
  if ((char)iVar2 != '\0') {
    do {
      if (screenshot_counter < 10) {
        pcVar3 = s_shot_00_d_bmp_004729b8;
      }
      else if (screenshot_counter < 100) {
        pcVar3 = s_shot_0_d_bmp_004729a8;
      }
      else {
        pcVar3 = s_shot__d_bmp_0047299c;
      }
      crt_sprintf(&config_file_path_buffer,pcVar3);
      fp = (FILE *)crt_fopen(&config_file_path_buffer,&file_mode_read_binary);
      if (fp != (FILE *)0x0) {
        crt_fclose(fp);
      }
      screenshot_counter = screenshot_counter + 1;
    } while (fp != (FILE *)0x0);
    (*grim_interface_ptr->vtable->grim_check_device)();
  }
  if ((demo_mode_active == '\0') && (game_loading_flag == '\0')) {
    game_status_blob.game_sequence_id = game_sequence_get();
    iVar2 = game_state_id;
    if ((console_open_flag == '\0') && ((render_pass_mode != '\0' && (game_state_id == 9)))) {
      lVar8 = __ftol();
      game_status_blob.game_sequence_id = game_status_blob.game_sequence_id + (int)lVar8;
    }
    if ((demo_trial_elapsed_ms < 1) || (console_open_flag != '\0')) goto LAB_0040c4b7;
    if (render_pass_mode != '\0') {
      if ((iVar2 == 9) && (config_blob.reserved0._24_4_ != 8)) {
        lVar8 = __ftol();
        demo_trial_elapsed_ms = demo_trial_elapsed_ms + (int)lVar8;
      }
      goto LAB_0040c4b7;
    }
  }
  else {
LAB_0040c4b7:
    if (((render_pass_mode != '\0') && (iVar2 = perk_count_get(perk_id_reflex_boosted), iVar2 != 0))
       && (game_state_id == 9)) {
      frame_dt = frame_dt * 0.9;
    }
  }
  game_time_s = game_time_s + frame_dt;
  frame_dt_stored = frame_dt;
  lVar8 = __ftol();
  frame_dt_ms = (int)lVar8;
  if (((console_open_flag == '\0') && (render_pass_mode != '\0')) &&
     ((game_state_id == 9 && (config_blob.reserved0._24_4_ != 8)))) {
    gameplay_elapsed_ms = gameplay_elapsed_ms + frame_dt_ms;
  }
  if (screen_fade_in_flag == '\0') {
    screen_fade_alpha = screen_fade_alpha - (frame_dt + frame_dt);
  }
  else {
    screen_fade_alpha = frame_dt * 10.0 + screen_fade_alpha;
  }
  if (0.0 <= screen_fade_alpha) {
    if (1.0 < screen_fade_alpha) {
      screen_fade_alpha = 1.0;
    }
  }
  else {
    screen_fade_alpha = 0.0;
  }
  if (console_open_flag != '\0') {
    frame_dt = 0.0;
  }
  (*grim_interface_ptr->vtable->grim_get_mouse_dx)();
  if ((extraout_ST0_00 == (float10)0.0) ||
     ((*grim_interface_ptr->vtable->grim_get_mouse_dy)(), extraout_ST0_01 == (float10)0.0)) {
    mouse_moved_flag = 0;
  }
  else {
    mouse_moved_flag = 1;
    ui_mouse_blocked = 0;
    gamepad_active_flag = 0;
  }
  fStack_20 = 0.0;
  fStack_1c = 0.0;
  (*grim_interface_ptr->vtable->grim_get_config_float)(player_state_table.input.axis_aim_x);
  fVar9 = (float)extraout_ST0_02;
  (*grim_interface_ptr->vtable->grim_get_config_float)(player_state_table.input.axis_aim_y);
  if ((float10)0.2 < SQRT((float10)fVar9 * (float10)fVar9 + extraout_ST0_03 * extraout_ST0_03)) {
    fStack_1c = (float)extraout_ST0_03;
    fStack_20 = fVar9;
  }
  (*grim_interface_ptr->vtable->grim_get_config_float)(player_state_table.input.axis_move_x);
  fVar9 = (float)extraout_ST0_04;
  (*grim_interface_ptr->vtable->grim_get_config_float)(player_state_table.input.axis_move_y);
  if ((float10)0.2 < SQRT((float10)fVar9 * (float10)fVar9 + extraout_ST0_05 * extraout_ST0_05)) {
    fStack_20 = fStack_20 + fVar9;
    fStack_1c = (float)((float10)fStack_1c + extraout_ST0_05);
  }
  if (0.2 < SQRT(fStack_20 * fStack_20 + fStack_1c * fStack_1c)) {
    gamepad_active_flag = 1;
  }
  if (game_state_id == 9) {
    gamepad_active_flag = 0;
LAB_0040c71b:
    (*grim_interface_ptr->vtable->grim_get_mouse_dx)();
    ui_mouse_x = (float)(extraout_ST0_06 * (float10)(float)config_blob.reserved8 +
                         extraout_ST0_06 * (float10)(float)config_blob.reserved8 +
                        (float10)ui_mouse_x);
    (*grim_interface_ptr->vtable->grim_get_mouse_dy)();
    pfVar4 = (float *)&player_aim_screen_x;
    ui_mouse_y = (float)(extraout_ST0_07 * (float10)(float)config_blob.reserved8 +
                         extraout_ST0_07 * (float10)(float)config_blob.reserved8 +
                        (float10)ui_mouse_y);
    do {
      *pfVar4 = ui_mouse_x;
      pfVar4[1] = ui_mouse_y;
      pfVar4 = pfVar4 + 2;
    } while ((int)pfVar4 < 0x487204);
  }
  else {
    if (gamepad_active_flag != 1) goto LAB_0040c71b;
    ui_mouse_x = (float)config_blob.reserved8 * frame_dt * fStack_20 * 540.0 + ui_mouse_x;
    ui_mouse_y = (float)config_blob.reserved8 * frame_dt * fStack_1c * 540.0 + ui_mouse_y;
  }
  if (ui_mouse_x < 0.0) {
    ui_mouse_x = 0.0;
  }
  if (ui_mouse_y < 0.0) {
    ui_mouse_y = 0.0;
  }
  if ((float)(config_blob.screen_width + -1) < ui_mouse_x) {
    ui_mouse_x = (float)(config_blob.screen_width + -1);
  }
  if ((float)(config_blob.screen_height + -1) < ui_mouse_y) {
    ui_mouse_y = (float)(config_blob.screen_height + -1);
  }
  if ((game_state_id == 0x16) || (ui_splash_skip_flag != '\0')) {
    plugin_frame_update();
  }
  else if (game_state_id == 9) {
    if (demo_purchase_screen_active == '\0') {
      gameplay_update_and_render();
    }
    else {
      (*grim_interface_ptr->vtable->grim_clear_color)(0.0,0.0,0.0,0.0);
    }
    if (demo_mode_active != '\0') {
LAB_0040c8a0:
      demo_purchase_screen_update();
    }
    if (audio_suspend_flag != '\0') {
      return;
    }
  }
  else {
    if (game_state_id == 0x18) {
      gameplay_update_and_render();
      goto LAB_0040c8a0;
    }
    if (game_state_id == 6) {
      perk_selection_screen_update();
    }
    else if (game_state_id == 7) {
      game_over_screen_update();
    }
    else if (game_state_id == 8) {
      quest_results_screen_update();
    }
    else if (game_state_id == 0xc) {
      quest_failed_screen_update();
    }
    else if (game_state_id == 0x12) {
      survival_gameplay_update_and_render();
    }
    else if (game_state_id == 0x15) {
      game_update_victory_screen();
    }
    else {
      demo_purchase_screen_active = '\0';
      game_update_generic_menu();
    }
  }
  (*grim_interface_ptr->vtable->grim_set_uv)(0.0,0.0,2.0,1.0);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3f000000);
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3ecccccd);
  iVar2 = game_is_full_version();
  if ((char)iVar2 == '\0') {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,0.3,0.3,0.6);
  }
  fVar9 = 0.45;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x18,0x3ee66666);
  if (*(float *)((int)cv_showFPS + 0xc) != 0.0) {
    (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
    (*grim_interface_ptr->vtable->grim_get_fps)();
    lVar8 = __ftol();
    pIVar1 = grim_interface_ptr->vtable;
    if ((int)lVar8 < 400) {
      (*pIVar1->grim_get_fps)();
      lVar8 = __ftol();
      uVar5 = (undefined4)lVar8;
      pcVar3 = &s_int_format;
      iVar2 = config_blob.screen_width + -0x2d;
    }
    else {
      (*pIVar1->grim_get_fps)();
      lVar8 = __ftol();
      uVar5 = (undefined4)lVar8;
      pcVar3 = &s_empty_string;
      iVar2 = config_blob.screen_width + -0x33;
    }
    (*pIVar1->grim_draw_text_small_fmt)
              (grim_interface_ptr,(float)iVar2,(float)(config_blob.screen_height + -0x18),pcVar3,
               uVar5);
  }
  (*grim_interface_ptr->vtable->grim_set_color)(1.0,1.0,1.0,0.6);
  console_render(&console_log_queue);
  crt_rand();
  audio_update();
  iVar2 = (*grim_interface_ptr->vtable->grim_was_key_pressed)(1);
  if ((((char)iVar2 != '\0') && ((render_pass_mode != '\0' || (game_state_id == 0x16)))) &&
     ((game_state_id == 9 || ((game_state_id == 0x16 || (game_state_id == 0x12)))))) {
    ui_transition_direction = 0;
    game_state_pending = 5;
    if (plugin_interface_ptr != (mod_interface_t *)0x0) {
      (plugin_interface_ptr->parms).fields.onPause = '\x01';
    }
  }
  if (easter_egg_random_seed == 0xffffffff) {
    uVar6 = crt_rand();
    easter_egg_random_seed = uVar6 & 0x8000001f;
    if ((int)easter_egg_random_seed < 0) {
      easter_egg_random_seed = (easter_egg_random_seed - 1 | 0xffffffe0) + 1;
    }
  }
  if ((((game_state_id == 4) && (render_pass_mode == '\0')) && (local_system_time._2_2_ == 3)) &&
     ((local_system_day == 3 && (easter_egg_random_seed == 3)))) {
    easter_egg_random_seed = 0xffffffff;
    (*grim_interface_ptr->vtable->grim_set_color)(0.2,1.0,0.6,0.5);
    pcVar3 = s_Orbes_Volantes_Exstare_00472978;
    y = 5.0;
    pIVar1 = grim_interface_ptr->vtable;
    uVar6 = crt_rand();
    uVar6 = uVar6 & 0x8000003f;
    if ((int)uVar6 < 0) {
      uVar6 = (uVar6 - 1 | 0xffffffc0) + 1;
    }
    (*pIVar1->grim_draw_text_small)((float)(int)(uVar6 + 0x10),y,pcVar3);
  }
  iVar2 = game_is_full_version();
  if ((char)iVar2 == '\0') {
    if (demo_mode_active == '\0') {
      trial_time_limit_ms_get();
      (*grim_interface_ptr->vtable->grim_draw_rect_filled)
                ((float *)&stack0xffffffac,(float)config_blob.screen_width,8.0);
      (*grim_interface_ptr->vtable->grim_draw_rect_filled)
                ((float *)&stack0xffffffa8,(float)(config_blob.screen_width + -4) * fVar9,3.0);
      goto LAB_0040cd14;
    }
LAB_0040cd20:
    if (game_state_pending == 0) {
      iVar2 = ui_elements_max_timeline();
      if (iVar2 == 0) {
        fVar9 = 1.0;
      }
      else {
        fVar9 = 1.0 - (float)ui_elements_timeline / (float)iVar2;
      }
      fVar9 = fVar9 * fVar9;
      if (game_state_prev == 0x18) {
        fVar9 = 1.0 - fVar9;
        demo_purchase_screen_active = '\0';
      }
      if (0.0 <= fVar9) {
        if (1.0 < fVar9) {
          fVar9 = 1.0;
        }
      }
      else {
        fVar9 = 0.0;
      }
      (*grim_interface_ptr->vtable->grim_draw_fullscreen_color)(0.0,0.0,0.0,fVar9);
    }
  }
  else {
LAB_0040cd14:
    if (demo_mode_active != '\0') goto LAB_0040cd20;
  }
  if (game_state_pending == 10) {
    iVar2 = ui_elements_max_timeline();
    if (iVar2 == 0) {
      fVar9 = 1.0;
    }
    else {
      fVar9 = 1.0 - (float)ui_elements_timeline / (float)iVar2;
    }
    if (game_state_prev == 0x16) {
      fVar9 = 1.0 - fVar9;
    }
    if (0.0 <= fVar9) {
      if (1.0 < fVar9) {
        fVar9 = 1.0;
      }
    }
    else {
      fVar9 = 0.0;
    }
    (*grim_interface_ptr->vtable->grim_draw_fullscreen_color)(0.0,0.0,0.0,fVar9);
  }
  iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x10);
  if (((char)iVar2 == '\0') ||
     (iVar2 = (*grim_interface_ptr->vtable->grim_is_key_down)(0x38), (char)iVar2 == '\0')) {
    if (game_quit_flag == '\0') goto LAB_0040cf06;
  }
  else {
    game_quit_flag = '\x01';
  }
  iVar2 = game_is_full_version();
  if ((char)iVar2 != '\0') {
    config_sync_from_grim();
    return;
  }
  if (shareware_offer_seen_latch != '\0') {
    return;
  }
  iVar2 = game_is_full_version();
  if ((char)iVar2 != '\0') {
    return;
  }
  config_sync_from_grim();
  demo_mode_start();
  sfx_mute_all(music_track_crimson_theme_id);
  sfx_mute_all(music_track_extra_0);
  sfx_mute_all(music_track_intro_id);
  sfx_play_exclusive(music_track_shortie_monk_id);
  game_quit_flag = '\0';
  shareware_offer_seen_latch = '\x01';
LAB_0040cf06:
  if (loading_flag_a != '\0') {
    loading_flag_a = '\0';
    ui_render_loading();
    ui_render_loading();
    audio_suspend_all();
    game_is_full_version();
  }
  if (loading_flag_b != '\0') {
    loading_flag_b = '\0';
    ui_render_loading();
    ui_render_loading();
    audio_suspend_all();
    game_is_full_version();
  }
  if (loading_flag_c != '\0') {
    loading_flag_c = '\0';
    ui_render_loading();
    ui_render_loading();
    audio_suspend_all();
    game_is_full_version();
  }
  if ((((browser_open_result == 0) && (browser_open_pending != '\0')) && (browser_url_ptr != 0)) &&
     ((game_state_id != 0xe || (ui_update_button_clicked != '\0')))) {
    Sleep(100);
    return;
  }
  return;
}



/* console_cmd_load_texture @ 0042a780 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for loadtexture; calls texture_get_or_load(name, path) */

void console_cmd_load_texture(void)

{
  int iVar1;
  char *path;
  char *name;
  
  iVar1 = console_cmd_argc_get();
  if (iVar1 != 2) {
    console_printf(&console_log_queue,s_cmd_loadtexture_usage);
    return;
  }
  path = console_cmd_arg_get(2);
  name = console_cmd_arg_get(2);
  texture_get_or_load(name,path);
  return;
}



/* console_cmd_set_resource_paq @ 0042a7c0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for setresourcepaq; validates file and updates Grim config id 0x10 */

void console_cmd_set_resource_paq(void)

{
  int iVar1;
  char *pcVar2;
  FILE *fp;
  uint in_stack_ffffffec;
  char *pcVar3;
  
  iVar1 = console_cmd_argc_get();
  if (iVar1 != 2) {
    console_printf(&console_log_queue,s_cmd_setresourcepaq_usage);
    return;
  }
  pcVar3 = &file_mode_read_binary;
  pcVar2 = console_cmd_arg_get(1);
  fp = (FILE *)crt_fopen(pcVar2,pcVar3);
  if (fp == (FILE *)0x0) {
    pcVar2 = console_cmd_arg_get(1);
    console_printf(&console_log_queue,s_file_not_found_fmt,pcVar2);
    return;
  }
  crt_fclose(fp);
  console_cmd_arg_get(1);
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x10,in_stack_ffffffec);
  pcVar2 = console_cmd_arg_get(1);
  console_printf(&console_log_queue,s_set_resource_paq_fmt,pcVar2);
  return;
}



/* console_cmd_tell_time_survived @ 0042a860 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for telltimesurvived; prints survived time in seconds */

void console_cmd_tell_time_survived(void)

{
  longlong lVar1;
  
  lVar1 = __ftol();
  console_printf(&console_log_queue,s_Survived___i_seconds__00473f64,(int)lVar1);
  return;
}



/* console_cmd_open_url @ 0042a890 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for openurl; converts to wide and calls HlinkNavigateString */

void console_cmd_open_url(void)

{
  int iVar1;
  char *pcVar2;
  HRESULT HVar3;
  WCHAR *lpWideCharStr;
  int cchWideChar;
  WCHAR aWStack_208 [260];
  
  lpWideCharStr = aWStack_208;
  iVar1 = console_cmd_argc_get();
  if (iVar1 != 2) {
    console_printf(&console_log_queue,s_openurl_<url>_00473fbc);
    return;
  }
  cchWideChar = 0x104;
  iVar1 = -1;
  pcVar2 = console_cmd_arg_get(1);
  MultiByteToWideChar(0,0,pcVar2,iVar1,lpWideCharStr,cchWideChar);
  HVar3 = HlinkNavigateString((IUnknown *)0x0,aWStack_208);
  if (HVar3 < 0) {
    console_printf(&console_log_queue,s_Failed_to_launch_web_browser__00473f9c);
    return;
  }
  pcVar2 = console_cmd_arg_get(1);
  console_printf(&console_log_queue,s_Launching_web_browser___s____00473f7c,pcVar2);
  return;
}



/* console_cmd_snd_freq_adjustment @ 0042a930 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for sndfreqadjustment; toggles DAT_004807a8 and prints status */

void console_cmd_snd_freq_adjustment(void)

{
  config_blob.reserved6[0x10] = config_blob.reserved6[0x10] == '\0';
  if ((bool)config_blob.reserved6[0x10]) {
    console_printf(&console_log_queue,s_Sound_frequency_adjustment_is_no_00473ffc);
    return;
  }
  console_printf(&console_log_queue,s_Sound_frequency_adjustment_is_no_00473fcc);
  return;
}



/* console_cmd_snd_add_game_tune @ 0042c360 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for snd_addGameTune; loads music\%s and queues the track */

void console_cmd_snd_add_game_tune(void)

{
  int iVar1;
  char *pcVar2;
  char acStack_400 [1024];
  
  iVar1 = console_cmd_argc_get();
  if (iVar1 != 2) {
    console_printf(&console_log_queue,s_snd_addGameTune_<tuneName_ogg>_0047474c);
    return;
  }
  pcVar2 = console_cmd_arg_get(1);
  crt_sprintf(acStack_400,s_music__s_00474740,pcVar2);
  iVar1 = music_load_track(acStack_400);
  if (-1 < iVar1) {
    music_queue_track(iVar1);
  }
  return;
}



/* console_cmd_set_gamma_ramp @ 0042c3d0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* console command handler for setGammaRamp; parses float and calls grim_set_config_var(0x1c) */

void console_cmd_set_gamma_ramp(void)

{
  int iVar1;
  char *str;
  void *this;
  float value;
  float fVar2;
  
  iVar1 = console_cmd_argc_get();
  if (iVar1 != 2) {
    console_printf(&console_log_queue,s_setGammaRamp_<scalar_>_0>_004747e4);
    console_printf(&console_log_queue,s_Command_adjusts_gamma_ramp_linea_0047479c);
    return;
  }
  str = console_cmd_arg_get(1);
  value = crt_atof_l(this,str);
  fVar2 = 3.92364e-44;
  (*grim_interface_ptr->vtable->grim_set_config_var)(0x1c,(uint)value);
  console_printf(&console_log_queue,s_Gamma_ramp_regenerated_and_multi_0047476c,(double)fVar2);
  return;
}



/* console_error_display @ 00461fd5 */

int __cdecl console_error_display(byte *param_1)

{
  int iVar1;
  int iVar2;
  
  crt_lock_file2(1,0x47b3f8);
  iVar1 = FUN_004666f5((int *)&crt_stdout_struct);
  iVar2 = crt_output((int *)&crt_stdout_struct,param_1,(undefined4 *)&stack0x00000008);
  FUN_00466782(iVar1,(int *)&crt_stdout_struct);
  crt_unlock_file2(1,0x47b3f8);
  return iVar2;
}


