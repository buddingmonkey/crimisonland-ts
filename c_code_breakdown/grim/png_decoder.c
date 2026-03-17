/* grim_png_stream_init @ 10009a50 */

void __cdecl grim_png_stream_init(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  param_1[1] = 0;
  if (param_2 != 0x3d) {
    *(undefined4 *)(*param_1 + 0x14) = 10;
    *(undefined4 *)(*param_1 + 0x18) = 0x3d;
    *(int *)(*param_1 + 0x1c) = param_2;
    (**(code **)*param_1)(param_1);
  }
  if (param_3 != 0x1a8) {
    *(undefined4 *)(*param_1 + 0x14) = 0x13;
    *(undefined4 *)(*param_1 + 0x18) = 0x1a8;
    *(int *)(*param_1 + 0x1c) = param_3;
    (**(code **)*param_1)(param_1);
  }
  iVar3 = *param_1;
  piVar1 = param_1;
  for (iVar2 = 0x6a; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
  }
  *param_1 = iVar3;
  *(undefined1 *)(param_1 + 3) = 1;
  grim_jpg_mem_pool_init((int)param_1);
  param_1[2] = 0;
  param_1[5] = 0;
  param_1[0x24] = 0;
  iVar3 = 4;
  param_1[0x25] = 0;
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  piVar1 = param_1 + 0x2c;
  do {
    piVar1[-4] = 0;
    *piVar1 = 0;
    piVar1 = piVar1 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  grim_png_decompress_start((int)param_1);
  grim_png_decompress_setup((int)param_1);
  param_1[4] = 200;
  return;
}



/* grim_png_stream_destroy @ 10009b20 */

void __cdecl grim_png_stream_destroy(int param_1)

{
  grim_jpg_mem_zero_block(param_1);
  return;
}



/* grim_png_stream_set_transforms @ 10009b30 */

int __cdecl grim_png_stream_set_transforms(int *param_1,char param_2)

{
  int iVar1;
  
  if ((param_1[4] != 200) && (param_1[4] != 0xc9)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  iVar1 = grim_png_read_state_machine(param_1);
  if (iVar1 == 1) {
    iVar1 = 1;
  }
  else if (iVar1 == 2) {
    if (param_2 != '\0') {
      *(undefined4 *)(*param_1 + 0x14) = 0x32;
      (**(code **)*param_1)(param_1);
    }
    grim_render_context_destroy((int)param_1);
    return 2;
  }
  return iVar1;
}



/* grim_png_read_state_machine @ 10009ba0 */

int __cdecl grim_png_read_state_machine(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  switch(param_1[4]) {
  case 200:
    (**(code **)(param_1[99] + 4))(param_1);
    (**(code **)(param_1[5] + 8))(param_1);
    param_1[4] = 0xc9;
  case 0xc9:
    iVar1 = (**(code **)param_1[99])(param_1);
    if (iVar1 == 1) {
      grim_png_read_header(param_1);
      param_1[4] = 0xca;
      return 1;
    }
    break;
  case 0xca:
    return 1;
  case 0xcb:
  case 0xcc:
  case 0xcd:
  case 0xce:
  case 0xcf:
  case 0xd0:
  case 0xd2:
    iVar1 = (**(code **)param_1[99])(param_1);
    return iVar1;
  default:
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  return iVar1;
}



/* grim_png_read_header @ 10009c60 */

void __cdecl grim_png_read_header(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = param_1[8];
  if (iVar1 == 1) {
    param_1[9] = 1;
    param_1[10] = 1;
    goto LAB_10009daf;
  }
  if (iVar1 != 3) {
    if (iVar1 == 4) {
      if ((*(char *)((int)param_1 + 0x106) == '\0') || (*(char *)((int)param_1 + 0x107) == '\0')) {
        param_1[9] = 4;
        param_1[10] = 4;
      }
      else {
        if (*(char *)((int)param_1 + 0x107) != '\x02') {
          *(undefined4 *)(*param_1 + 0x14) = 0x6e;
          *(uint *)(*param_1 + 0x18) = (uint)*(byte *)((int)param_1 + 0x107);
          (**(code **)(*param_1 + 4))(param_1,0xffffffff);
        }
        param_1[9] = 5;
        param_1[10] = 4;
      }
    }
    else {
      param_1[9] = 0;
      param_1[10] = 0;
    }
    goto LAB_10009daf;
  }
  if ((char)param_1[0x40] == '\0') {
    if (*(char *)((int)param_1 + 0x106) == '\0') {
      piVar2 = (int *)param_1[0x31];
      iVar1 = *piVar2;
      iVar3 = piVar2[0x15];
      iVar4 = piVar2[0x2a];
      if (iVar1 == 1) {
        if ((iVar3 == 2) && (iVar4 == 3)) {
          param_1[9] = 3;
          param_1[10] = 2;
          goto LAB_10009daf;
        }
      }
      else if (((iVar1 == 0x52) && (iVar3 == 0x47)) && (iVar4 == 0x42)) goto LAB_10009d62;
      iVar5 = *param_1;
      *(int *)(iVar5 + 0x18) = iVar1;
      *(int *)(iVar5 + 0x1c) = iVar3;
      *(int *)(iVar5 + 0x20) = iVar4;
      *(undefined4 *)(*param_1 + 0x14) = 0x6b;
      (**(code **)(*param_1 + 4))(param_1,1);
    }
    else {
      if (*(char *)((int)param_1 + 0x107) == '\0') {
LAB_10009d62:
        param_1[9] = 2;
        param_1[10] = 2;
        goto LAB_10009daf;
      }
      if (*(char *)((int)param_1 + 0x107) != '\x01') {
        *(undefined4 *)(*param_1 + 0x14) = 0x6e;
        *(uint *)(*param_1 + 0x18) = (uint)*(byte *)((int)param_1 + 0x107);
        (**(code **)(*param_1 + 4))(param_1,0xffffffff);
      }
    }
  }
  param_1[9] = 3;
  param_1[10] = 2;
LAB_10009daf:
  param_1[0xe] = 0;
  param_1[0xb] = 1;
  param_1[0xc] = 1;
  param_1[0xf] = 0x3ff00000;
  *(undefined1 *)(param_1 + 0x10) = 0;
  *(undefined1 *)((int)param_1 + 0x41) = 0;
  param_1[0x11] = 0;
  *(undefined1 *)(param_1 + 0x12) = 1;
  *(undefined1 *)((int)param_1 + 0x49) = 1;
  *(undefined1 *)((int)param_1 + 0x4a) = 0;
  param_1[0x13] = 2;
  *(undefined1 *)(param_1 + 0x14) = 1;
  param_1[0x15] = 0x100;
  param_1[0x1d] = 0;
  *(undefined1 *)(param_1 + 0x16) = 0;
  *(undefined1 *)((int)param_1 + 0x59) = 0;
  *(undefined1 *)((int)param_1 + 0x5a) = 0;
  return;
}



/* grim_png_read_finish @ 10009e00 */

undefined4 __cdecl grim_png_read_finish(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = param_1[4];
  if (((iVar3 == 0xcd) || (iVar3 == 0xce)) && ((char)param_1[0x10] == '\0')) {
    if ((uint)param_1[0x1e] < (uint)param_1[0x18]) {
      *(undefined4 *)(*param_1 + 0x14) = 0x42;
      (**(code **)*param_1)(param_1);
    }
    (**(code **)(param_1[0x5f] + 4))(param_1);
    param_1[4] = 0xd2;
  }
  else if (iVar3 == 0xcf) {
    param_1[4] = 0xd2;
  }
  else if (iVar3 != 0xd2) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  puVar2 = (undefined4 *)param_1[99];
  cVar1 = *(char *)((int)puVar2 + 0x11);
  while( true ) {
    if (cVar1 != '\0') {
      (**(code **)(param_1[5] + 0x18))(param_1);
      uVar4 = grim_render_context_destroy((int)param_1);
      return CONCAT31((int3)((uint)uVar4 >> 8),1);
    }
    iVar3 = (*(code *)*puVar2)(param_1);
    if (iVar3 == 0) break;
    puVar2 = (undefined4 *)param_1[99];
    cVar1 = *(char *)((int)puVar2 + 0x11);
  }
  return 0;
}



/* grim_png_read_data @ 10009ec0 */

uint __cdecl grim_png_read_data(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  if (param_1[4] == 0xca) {
    uVar2 = grim_render_update_state(param_1);
    if ((char)param_1[0x10] != '\0') {
      param_1[4] = 0xcf;
      return CONCAT31((int3)((uint)uVar2 >> 8),1);
    }
    param_1[4] = 0xcb;
  }
  if (param_1[4] == 0xcb) {
    if (*(char *)(param_1[99] + 0x10) != '\0') {
      while( true ) {
        if ((undefined4 *)param_1[2] != (undefined4 *)0x0) {
          (**(code **)param_1[2])(param_1);
        }
        iVar3 = (**(code **)param_1[99])(param_1);
        if (iVar3 == 0) {
          return 0;
        }
        if (iVar3 == 2) break;
        iVar1 = param_1[2];
        if ((iVar1 != 0) && ((iVar3 == 3 || (iVar3 == 1)))) {
          *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
          iVar3 = param_1[2];
          if (*(int *)(iVar3 + 8) <= *(int *)(iVar3 + 4)) {
            *(int *)(iVar3 + 8) = param_1[0x46] + *(int *)(iVar3 + 8);
          }
        }
      }
    }
    param_1[0x21] = param_1[0x1f];
    uVar4 = grim_png_read_rows((int)param_1);
    return uVar4;
  }
  if (param_1[4] != 0xcc) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  uVar4 = grim_png_read_rows((int)param_1);
  return uVar4;
}



/* grim_png_read_rows @ 10009fa0 */

uint __cdecl grim_png_read_rows(int param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x10) != 0xcc) {
    (*(code *)**(undefined4 **)(param_1 + 0x17c))(param_1);
    *(undefined4 *)(param_1 + 0x78) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0xcc;
  }
  if (*(char *)(*(int *)(param_1 + 0x17c) + 8) != '\0') {
    puVar1 = (uint *)(param_1 + 0x78);
    do {
      uVar3 = *puVar1;
      if (uVar3 < *(uint *)(param_1 + 0x60)) {
        do {
          if (*(int *)(param_1 + 8) != 0) {
            *(uint *)(*(int *)(param_1 + 8) + 4) = uVar3;
            *(undefined4 *)(*(int *)(param_1 + 8) + 8) = *(undefined4 *)(param_1 + 0x60);
            (*(code *)**(undefined4 **)(param_1 + 8))(param_1);
          }
          uVar2 = *puVar1;
          (**(code **)(*(int *)(param_1 + 0x180) + 4))(param_1,0,puVar1,0);
          uVar3 = *puVar1;
          if (uVar3 == uVar2) {
            return uVar3 & 0xffffff00;
          }
        } while (uVar3 < *(uint *)(param_1 + 0x60));
      }
      (**(code **)(*(int *)(param_1 + 0x17c) + 4))(param_1);
      (*(code *)**(undefined4 **)(param_1 + 0x17c))(param_1);
      *puVar1 = 0;
    } while (*(char *)(*(int *)(param_1 + 0x17c) + 8) != '\0');
  }
  iVar4 = (*(char *)(param_1 + 0x41) != '\0') + 0xcd;
  *(int *)(param_1 + 0x10) = iVar4;
  return CONCAT31((int3)((uint)iVar4 >> 8),1);
}



/* grim_png_read_chunk @ 1000a070 */

int __cdecl grim_png_read_chunk(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  
  piVar1 = param_1;
  if (param_1[4] != 0xcd) {
    *(undefined4 *)(*param_1 + 0x14) = 0x12;
    *(int *)(*param_1 + 0x18) = param_1[4];
    (**(code **)*param_1)(param_1);
  }
  if ((uint)piVar1[0x18] <= (uint)piVar1[0x1e]) {
    *(undefined4 *)(*piVar1 + 0x14) = 0x77;
    (**(code **)(*piVar1 + 4))(piVar1,0xffffffff);
    return 0;
  }
  if (piVar1[2] != 0) {
    *(int *)(piVar1[2] + 4) = piVar1[0x1e];
    *(int *)(piVar1[2] + 8) = piVar1[0x18];
    (**(code **)piVar1[2])(piVar1);
  }
  param_1 = (int *)0x0;
  (**(code **)(piVar1[0x60] + 4))(piVar1,param_2,&param_1,param_3);
  piVar1[0x1e] = piVar1[0x1e] + (int)param_1;
  return (int)param_1;
}



/* grim_png_error_handler @ 1001e073 */

void __thiscall grim_png_error_handler(void *this,int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar3 = 0;
  iVar6 = 0;
  do {
    bVar2 = *(byte *)(param_1 + 0x10c + iVar6);
    uVar5 = (uint)bVar2;
    iVar6 = iVar6 + 1;
    if (((uVar5 < 0x29) || (0x7a < uVar5)) || ((0x5a < uVar5 && (uVar5 < 0x61)))) {
      *(undefined1 *)(iVar3 + (int)this) = 0x5b;
      *(char *)(iVar3 + 1 + (int)this) = "0123456789ABCDEF1.0.5"[(int)uVar5 >> 4];
      *(char *)(iVar3 + 2 + (int)this) = "0123456789ABCDEF1.0.5"[uVar5 & 0xf];
      iVar4 = iVar3 + 3;
      *(undefined1 *)(iVar4 + (int)this) = 0x5d;
    }
    else {
      *(byte *)(iVar3 + (int)this) = bVar2;
      iVar4 = iVar3;
    }
    iVar3 = iVar4 + 1;
  } while (iVar6 < 4);
  if (param_2 == (undefined4 *)0x0) {
    *(undefined1 *)(iVar3 + (int)this) = 0;
  }
  else {
    *(undefined1 *)(iVar3 + (int)this) = 0x3a;
    *(undefined1 *)(iVar4 + 2 + (int)this) = 0x20;
    puVar1 = (undefined4 *)(iVar4 + 3 + (int)this);
    puVar7 = puVar1;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar7 = *param_2;
      param_2 = param_2 + 1;
      puVar7 = puVar7 + 1;
    }
    *(undefined1 *)((int)puVar1 + 0x3f) = 0;
  }
  return;
}



/* grim_png_warning_handler @ 1001e0fa */

void __cdecl grim_png_warning_handler(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x40) = param_3;
  *(undefined4 *)(param_1 + 0x44) = param_4;
  return;
}



/* png_error @ 1001e114 */

/* png error handler: call error_fn then longjmp */

void png_error(png_structp png_ptr,char *msg)

{
  if (png_ptr->error_fn != (png_error_ptr)0x0) {
    (*png_ptr->error_fn)(png_ptr,msg);
  }
                    /* WARNING: Subroutine does not return */
  longjmp((int *)png_ptr,1);
}



/* png_warning @ 1001e132 */

/* png warning handler: call warning_fn */

void __cdecl png_warning(png_structp png_ptr,char *msg)

{
  if (png_ptr->warning_fn != (png_error_ptr)0x0) {
    (*png_ptr->warning_fn)(png_ptr,msg);
  }
  return;
}



/* grim_png_error_raise @ 1001e147 */

void __cdecl grim_png_error_raise(png_structp png_ptr,undefined4 *param_2)

{
  char local_54 [80];
  
  grim_png_error_handler(local_54,(int)png_ptr,param_2);
  png_error(png_ptr,local_54);
  return;
}



/* grim_png_create_read_struct_full @ 1001e16c */

void __cdecl grim_png_create_read_struct_full(png_structp png_ptr,undefined4 *param_2)

{
  char local_54 [80];
  
  grim_png_error_handler(local_54,(int)png_ptr,param_2);
  png_warning(png_ptr,local_54);
  return;
}



/* png_create_read_struct @ 1001e191 */

/* allocates png_struct, initializes zlib stream, checks version; error_fn/warn_fn are png_error_ptr
   callbacks */

png_structp __cdecl
png_create_read_struct(char *user_png_ver,png_voidp error_ptr,void *error_fn,void *warn_fn)

{
  png_structp png_ptr;
  int iVar1;
  png_bytep ppVar2;
  char *msg;
  
  png_ptr = (png_structp)grim_png_memory_alloc(1);
  if (png_ptr == (png_structp)0x0) {
    return (png_structp)0x0;
  }
  iVar1 = setjmp3(png_ptr,0);
  if (iVar1 != 0) {
    png_free(png_ptr,png_ptr->zbuf);
    png_free_ptr(png_ptr);
    return (png_structp)0x0;
  }
  grim_png_warning_handler((int)png_ptr,error_ptr,error_fn,warn_fn);
  if ((user_png_ver == (char *)0x0) || (*user_png_ver != '1')) {
    png_error(png_ptr,"Incompatible libpng version in application and library");
  }
  png_ptr->zbuf_size = 0x2000;
  ppVar2 = png_malloc(png_ptr,0x2000);
  png_ptr->zbuf = ppVar2;
  (png_ptr->zstream).words[8] = (png_uint_32)grim_png_calloc;
  (png_ptr->zstream).words[9] = (png_uint_32)png_free_thunk;
  (png_ptr->zstream).words[10] = (png_uint_32)png_ptr;
  iVar1 = inflateInit_((z_streamp)&png_ptr->zstream,"1.1.3",0x38);
  if (iVar1 == -6) {
    msg = "zlib version error";
  }
  else if ((iVar1 == -4) || (iVar1 == -2)) {
    msg = "zlib memory error";
  }
  else {
    if (iVar1 == 0) goto LAB_1001e270;
    msg = "Unknown zlib error";
  }
  png_error(png_ptr,msg);
LAB_1001e270:
  (png_ptr->zstream).words[3] = (png_uint_32)png_ptr->zbuf;
  (png_ptr->zstream).words[4] = png_ptr->zbuf_size;
  grim_png_set_read_fn(png_ptr,0,0);
  return png_ptr;
}



/* grim_png_read_header_and_validate @ 1001e294 */

void __cdecl grim_png_read_header_and_validate(png_structp png_ptr,uint *param_2)

{
  png_byte *buf;
  png_structp png_ptr_00;
  int iVar1;
  int unaff_EBX;
  uint uVar2;
  uint unaff_EBP;
  png_uint_32 pVar3;
  char *pcVar4;
  
  png_ptr_00 = png_ptr;
  if (png_ptr->sig_bytes < 8) {
    uVar2 = (uint)png_ptr->sig_bytes;
    pVar3 = -uVar2 + 8;
    png_read_data(png_ptr,(png_bytep)(uVar2 + 0x20 + (int)param_2),pVar3);
    png_ptr_00->sig_bytes = '\b';
    iVar1 = grim_png_check_sig((int)(param_2 + 8),uVar2,pVar3);
    if (iVar1 != 0) {
      if ((uVar2 < 4) && (iVar1 = grim_png_check_sig((int)(param_2 + 8),uVar2,-uVar2 + 4), iVar1 != 0)) {
        pcVar4 = "Not a PNG file";
      }
      else {
        pcVar4 = "PNG file corrupted by ASCII conversion";
      }
      png_error(png_ptr_00,pcVar4);
    }
  }
  buf = png_ptr_00->chunk_name;
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          png_read_data(png_ptr_00,(png_bytep)&png_ptr,4);
          pVar3 = png_get_uint_32((png_bytep)&png_ptr);
          png_reset_crc(png_ptr_00);
          png_crc_read(png_ptr_00,buf,4);
          if (*(int *)buf != 0x52444849) break;
          grim_png_read_IHDR(png_ptr_00,param_2,pVar3);
        }
        if (*(int *)buf != 0x45544c50) break;
        grim_png_read_PLTE((void *)0x45544c50,png_ptr_00,(int)param_2,pVar3);
      }
      if (*(int *)buf != 0x444e4549) break;
      grim_png_handle_unknown_chunk(png_ptr_00,param_2,pVar3,unaff_EBX,unaff_EBP);
    }
    if (*(int *)buf == 0x54414449) break;
    if (*(int *)buf == 0x414d4167) {
      grim_png_handle_gama_chunk(png_ptr_00,(int)param_2,pVar3);
    }
    else if (*(int *)buf == 0x42475273) {
      grim_png_handle_srgb_chunk(png_ptr_00,(int)param_2,pVar3);
    }
    else if (*(int *)buf == 0x534e5274) {
      grim_png_handle_text_chunk(png_ptr_00,(int)param_2,pVar3);
    }
    else {
      grim_png_read_chunk_generic(png_ptr_00,(int)param_2,pVar3);
    }
  }
  if ((png_ptr_00->mode & 1) == 0) {
    pcVar4 = "Missing IHDR before IDAT";
  }
  else {
    if ((png_ptr_00->color_type != '\x03') || ((png_ptr_00->mode & 2) != 0)) goto LAB_1001e3f8;
    pcVar4 = "Missing PLTE before IDAT";
  }
  png_error(png_ptr_00,pcVar4);
LAB_1001e3f8:
  png_ptr_00->mode = png_ptr_00->mode | 4;
  png_ptr_00->crc = pVar3;
  return;
}



/* grim_png_read_row_cleanup @ 1001e407 */

void __cdecl grim_png_read_row_cleanup(png_structp png_ptr,int *param_2)

{
  if ((png_ptr->flags & 0x40) == 0) {
    grim_png_read_start(png_ptr);
  }
  grim_png_read_update_info((int)png_ptr,param_2);
  return;
}



/* grim_png_read_rows_internal @ 1001e427 */

void __thiscall grim_png_read_rows_internal(void *this,png_structp png_ptr,byte *param_2,byte *param_3)

{
  png_uint_32 *ppVar1;
  png_byte pVar2;
  byte bVar3;
  uint uVar4;
  png_bytep buf;
  png_structp png_ptr_00;
  png_uint_32 pVar5;
  int iVar6;
  char *msg;
  png_structp extraout_ECX;
  uint uVar7;
  png_structp extraout_ECX_00;
  png_structp this_00;
  png_structp extraout_ECX_01;
  png_structp extraout_ECX_02;
  png_structp extraout_ECX_03;
  png_structp extraout_ECX_04;
  bool bVar8;
  byte *pbVar9;
  
  png_ptr_00 = png_ptr;
  if ((png_ptr->flags & 0x40) == 0) {
    this = png_ptr;
    grim_png_read_start(png_ptr);
  }
  if ((png_ptr_00->interlaced != '\0') && ((png_ptr_00->transformations & 2) != 0)) {
    pVar2 = png_ptr_00->pass;
    if (pVar2 == '\0') {
      if (((uint)png_ptr_00->prev_row & 7) != 0) {
        bVar8 = param_3 == (byte *)0x0;
LAB_1001e539:
        if (bVar8) goto LAB_1001e48f;
        uVar7 = 0xff;
LAB_1001e544:
        grim_png_unfilter_row((int)png_ptr_00,param_3,uVar7);
        this = extraout_ECX;
LAB_1001e48f:
        grim_png_handle_idat_chunk(this,(int *)png_ptr_00);
        return;
      }
    }
    else if (pVar2 == '\x01') {
      if ((((uint)png_ptr_00->prev_row & 7) != 0) || (png_ptr_00->width < 5)) {
        if (param_3 == (byte *)0x0) goto LAB_1001e48f;
        uVar7 = 0xf;
        goto LAB_1001e544;
      }
    }
    else if (pVar2 == '\x02') {
      this = (void *)((uint)png_ptr_00->prev_row & 0xffffff07);
      if ((char)this != '\x04') {
        if (param_3 == (byte *)0x0) goto LAB_1001e48f;
        bVar8 = ((uint)png_ptr_00->prev_row & 4) == 0;
        goto LAB_1001e539;
      }
    }
    else if (pVar2 == '\x03') {
      if ((((uint)png_ptr_00->prev_row & 3) != 0) || (png_ptr_00->width < 3)) {
        if (param_3 == (byte *)0x0) goto LAB_1001e48f;
        uVar7 = 0x33;
        goto LAB_1001e544;
      }
    }
    else if (pVar2 == '\x04') {
      this = (void *)((uint)png_ptr_00->prev_row & 0xffffff03);
      if ((char)this != '\x02') {
        if (param_3 == (byte *)0x0) goto LAB_1001e48f;
        bVar8 = ((uint)png_ptr_00->prev_row & 2) == 0;
        goto LAB_1001e539;
      }
    }
    else if (pVar2 == '\x05') {
      if ((((uint)png_ptr_00->prev_row & 1) != 0) || (png_ptr_00->width < 2)) {
        if (param_3 == (byte *)0x0) goto LAB_1001e48f;
        uVar7 = 0x55;
        goto LAB_1001e544;
      }
    }
    else if ((pVar2 == '\x06') && (((uint)png_ptr_00->prev_row & 1) == 0)) goto LAB_1001e48f;
  }
  if ((png_ptr_00->mode & 4) == 0) {
    png_error(png_ptr_00,"Invalid attempt to read row data");
  }
  (png_ptr_00->zstream).words[3] = (png_uint_32)png_ptr_00->sub_row;
  (png_ptr_00->zstream).words[4] = png_ptr_00->iwidth;
  do {
    if ((png_ptr_00->zstream).words[1] == 0) {
      if (png_ptr_00->crc == 0) {
        do {
          png_crc_finish(png_ptr_00,0);
          png_read_data(png_ptr_00,(png_bytep)&png_ptr,4);
          pVar5 = png_get_uint_32((png_bytep)&png_ptr);
          png_ptr_00->crc = pVar5;
          png_reset_crc(png_ptr_00);
          png_crc_read(png_ptr_00,png_ptr_00->chunk_name,4);
          if (*(int *)png_ptr_00->chunk_name != 0x54414449) {
            png_error(png_ptr_00,"Not enough image data");
          }
        } while (png_ptr_00->crc == 0);
      }
      uVar7 = png_ptr_00->zbuf_size;
      uVar4 = png_ptr_00->crc;
      buf = png_ptr_00->zbuf;
      (png_ptr_00->zstream).words[1] = uVar7;
      (png_ptr_00->zstream).words[0] = (png_uint_32)buf;
      if (uVar4 < uVar7) {
        (png_ptr_00->zstream).words[1] = uVar4;
      }
      png_crc_read(png_ptr_00,buf,(png_ptr_00->zstream).words[1]);
      png_ptr_00->crc = png_ptr_00->crc - (png_ptr_00->zstream).words[1];
    }
    iVar6 = inflate((z_streamp)&png_ptr_00->zstream,1);
    if (iVar6 == 1) {
      if ((((png_ptr_00->zstream).words[4] != 0) || ((png_ptr_00->zstream).words[1] != 0)) ||
         (png_ptr_00->crc != 0)) {
        png_error(png_ptr_00,"Extra compressed data");
      }
      png_ptr_00->mode = png_ptr_00->mode | 8;
      png_ptr_00->flags = png_ptr_00->flags | 0x20;
      break;
    }
    if (iVar6 != 0) {
      msg = (char *)(png_ptr_00->zstream).words[6];
      if (msg == (char *)0x0) {
        msg = "Decompression error";
      }
      png_error(png_ptr_00,msg);
    }
  } while ((png_ptr_00->zstream).words[4] != 0);
  pVar2 = png_ptr_00->color_type;
  *(png_byte *)((int)&png_ptr_00->idat_size + 2) = png_ptr_00->channels;
  *(png_byte *)((int)&png_ptr_00->idat_size + 1) = png_ptr_00->bit_depth;
  bVar3 = png_ptr_00->pixel_depth;
  *(byte *)((int)&png_ptr_00->idat_size + 3) = bVar3;
  *(png_byte *)&png_ptr_00->idat_size = pVar2;
  uVar7 = (uint)bVar3 * png_ptr_00->row_number + 7 >> 3;
  ppVar1 = &(png_ptr_00->row_info).rowbytes;
  *ppVar1 = png_ptr_00->row_number;
  pbVar9 = png_ptr_00->sub_row;
  (png_ptr_00->row_info).color_type = (char)uVar7;
  (png_ptr_00->row_info).bit_depth = (char)(uVar7 >> 8);
  (png_ptr_00->row_info).channels = (char)(uVar7 >> 0x10);
  (png_ptr_00->row_info).pixel_depth = (char)(uVar7 >> 0x18);
  grim_png_process_idat(png_ptr_00,(int)ppVar1,pbVar9 + 1,png_ptr_00->row_buf + 1,(uint)*pbVar9);
  grim_png_crc_init((int)png_ptr_00,(int)png_ptr_00->row_buf,(int)png_ptr_00->sub_row);
  this_00 = extraout_ECX_00;
  if (png_ptr_00->transformations != 0) {
    this_00 = png_ptr_00;
    grim_png_do_transformations(png_ptr_00);
  }
  if ((png_ptr_00->interlaced == '\0') || ((png_ptr_00->transformations & 2) == 0)) {
    if (param_2 != (byte *)0x0) {
      grim_png_unfilter_row((int)png_ptr_00,param_2,0xff);
      this_00 = extraout_ECX_03;
    }
    if (param_3 == (byte *)0x0) goto LAB_1001e7a4;
    uVar7 = 0xff;
    pbVar9 = param_3;
  }
  else {
    bVar3 = png_ptr_00->pass;
    this_00 = (png_structp)CONCAT31((int3)((uint)this_00 >> 8),bVar3);
    if (bVar3 < 6) {
      grim_png_deinterlace_row(ppVar1,(int *)(png_ptr_00->sub_row + 1),(uint)bVar3);
      this_00 = extraout_ECX_01;
    }
    if (param_3 != (byte *)0x0) {
      grim_png_unfilter_row((int)png_ptr_00,param_3,*(uint *)(&DAT_1004e1f8 + (uint)png_ptr_00->pass * 4));
      this_00 = extraout_ECX_02;
    }
    if (param_2 == (byte *)0x0) goto LAB_1001e7a4;
    uVar7 = *(uint *)(&DAT_1004e1dc + (uint)png_ptr_00->pass * 4);
    pbVar9 = param_2;
  }
  grim_png_unfilter_row((int)png_ptr_00,pbVar9,uVar7);
  this_00 = extraout_ECX_04;
LAB_1001e7a4:
  grim_png_handle_idat_chunk(this_00,(int *)png_ptr_00);
  if (png_ptr_00[1].write_data_fn != (png_rw_ptr)0x0) {
    (*png_ptr_00[1].write_data_fn)(png_ptr_00,png_ptr_00->prev_row,(png_uint_32)png_ptr_00->pass);
  }
  return;
}



/* grim_png_read_rows_with_transform @ 1001e7ce */

void __cdecl grim_png_read_rows_with_transform(png_structp png_ptr,undefined4 *param_2)

{
  png_uint_32 pVar1;
  png_uint_32 pVar2;
  undefined4 *puVar3;
  png_structp extraout_ECX;
  png_structp this;
  undefined4 local_8;
  
  this = png_ptr;
  local_8 = grim_png_set_bgr((int)png_ptr);
  pVar1 = png_ptr->height;
  png_ptr->num_rows = pVar1;
  pVar2 = pVar1;
  puVar3 = param_2;
  if (0 < local_8) {
    do {
      for (; pVar2 != 0; pVar2 = pVar2 - 1) {
        grim_png_read_rows_internal(this,png_ptr,(byte *)*puVar3,(byte *)0x0);
        puVar3 = puVar3 + 1;
        this = extraout_ECX;
      }
      local_8 = local_8 + -1;
      pVar2 = pVar1;
      puVar3 = param_2;
    } while (local_8 != 0);
  }
  return;
}



/* grim_png_destroy_read_struct @ 1001e81b */

void __cdecl grim_png_destroy_read_struct(png_structp png_ptr,undefined4 *param_2,undefined4 *param_3)

{
  png_voidp pvVar1;
  png_error_ptr ppVar2;
  png_error_ptr ppVar3;
  int iVar4;
  png_structp ppVar5;
  png_uint_32 *ppVar6;
  int iVar7;
  png_uint_32 local_44 [16];
  
  iVar7 = 0;
  if (param_2 != (undefined4 *)0x0) {
    grim_png_info_init((int)png_ptr);
  }
  if (param_3 != (undefined4 *)0x0) {
    grim_png_info_init((int)png_ptr);
  }
  png_free(png_ptr,png_ptr->zbuf);
  png_free(png_ptr,png_ptr->sub_row);
  png_free(png_ptr,png_ptr->row_buf);
  png_free(png_ptr,png_ptr[1].io_ptr);
  png_free(png_ptr,(void *)png_ptr[1].mode);
  png_free(png_ptr,(void *)png_ptr[1].jmpbuf[6]);
  if ((png_ptr->flags & 0x1000) != 0) {
    png_free_thunk(png_ptr,*(void **)&png_ptr->num_palette);
  }
  if ((png_ptr->flags & 0x2000) != 0) {
    png_free(png_ptr,(void *)png_ptr[1].jmpbuf[0xf]);
  }
  if (png_ptr[1].jmpbuf[9] != 0) {
    iVar4 = 1 << (8U - (char)png_ptr[1].jmpbuf[3] & 0x1f);
    if (0 < iVar4) {
      do {
        png_free(png_ptr,*(void **)(png_ptr[1].jmpbuf[9] + iVar7 * 4));
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar4);
    }
    png_free(png_ptr,(void *)png_ptr[1].jmpbuf[9]);
  }
  inflateEnd((z_streamp)&png_ptr->zstream);
  pvVar1 = png_ptr->error_ptr;
  ppVar2 = png_ptr->error_fn;
  ppVar5 = png_ptr;
  ppVar6 = local_44;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *ppVar6 = ppVar5->jmpbuf[0];
    ppVar5 = (png_structp)(ppVar5->jmpbuf + 1);
    ppVar6 = ppVar6 + 1;
  }
  ppVar3 = png_ptr->warning_fn;
  ppVar5 = png_ptr;
  for (iVar7 = 0x67; iVar7 != 0; iVar7 = iVar7 + -1) {
    ppVar5->jmpbuf[0] = 0;
    ppVar5 = (png_structp)(ppVar5->jmpbuf + 1);
  }
  png_ptr->warning_fn = ppVar3;
  ppVar6 = local_44;
  ppVar5 = png_ptr;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    ppVar5->jmpbuf[0] = *ppVar6;
    ppVar6 = ppVar6 + 1;
    ppVar5 = (png_structp)(ppVar5->jmpbuf + 1);
  }
  png_ptr->error_fn = ppVar2;
  png_ptr->error_ptr = pvVar1;
  return;
}



/* grim_png_destroy_info_struct @ 1001e93e */

void __cdecl grim_png_destroy_info_struct(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *ptr;
  undefined4 local_c;
  undefined4 local_8;
  
  ptr = (undefined4 *)0x0;
  local_8 = (png_structp)0x0;
  local_c = (undefined4 *)0x0;
  if (param_1 != (undefined4 *)0x0) {
    local_8 = (png_structp)*param_1;
  }
  if (param_2 != (undefined4 *)0x0) {
    ptr = (undefined4 *)*param_2;
  }
  if (param_3 != (undefined4 *)0x0) {
    local_c = (undefined4 *)*param_3;
  }
  if (local_8 != (png_structp)0x0) {
    grim_png_destroy_read_struct(local_8,ptr,local_c);
  }
  if (ptr != (undefined4 *)0x0) {
    png_free_ptr(ptr);
    *param_2 = 0;
  }
  if (local_c != (undefined4 *)0x0) {
    png_free_ptr(local_c);
    *param_3 = 0;
  }
  if (local_8 != (png_structp)0x0) {
    png_free_ptr(local_8);
    *param_1 = 0;
  }
  return;
}



/* grim_png_get_bit_depth @ 1001e9bf */

uint __cdecl grim_png_get_bit_depth(int param_1,int param_2,uint param_3)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    return *(uint *)(param_2 + 8) & param_3;
  }
  return 0;
}



/* grim_png_get_color_type @ 1001e9d9 */

undefined4 __cdecl grim_png_get_color_type(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    return *(undefined4 *)(param_2 + 0xc);
  }
  return 0;
}



/* grim_png_get_interlace_type @ 1001e9ef */

undefined1 __cdecl grim_png_get_interlace_type(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    return *(undefined1 *)(param_2 + 0x1d);
  }
  return 0;
}



/* grim_png_get_channels @ 1001ea05 */

undefined4 __cdecl grim_png_get_channels(int param_1,int param_2,double *param_3)

{
  if ((((param_1 != 0) && (param_2 != 0)) && ((*(byte *)(param_2 + 8) & 1) != 0)) &&
     (param_3 != (double *)0x0)) {
    *param_3 = (double)*(float *)(param_2 + 0x28);
    return 1;
  }
  return 0;
}



/* grim_png_get_rowbytes @ 1001ea2e */

undefined4 __cdecl grim_png_get_rowbytes(int param_1,int param_2,uint *param_3)

{
  if ((((param_1 != 0) && (param_2 != 0)) && ((*(uint *)(param_2 + 8) & 0x800) != 0)) &&
     (param_3 != (uint *)0x0)) {
    *param_3 = (uint)*(byte *)(param_2 + 0x2c);
    return 0x800;
  }
  return 0;
}



/* grim_png_set_strip_16 @ 1001ea59 */

undefined4 __cdecl
grim_png_set_strip_16(png_structp png_ptr,uint *param_2,uint *param_3,uint *param_4,uint *param_5,
            uint *param_6,uint *param_7,uint *param_8,uint *param_9)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if ((((png_ptr == (png_structp)0x0) || (param_2 == (uint *)0x0)) || (param_3 == (uint *)0x0)) ||
     (((param_4 == (uint *)0x0 || (param_5 == (uint *)0x0)) || (param_6 == (uint *)0x0)))) {
    uVar3 = 0;
  }
  else {
    *param_3 = *param_2;
    *param_4 = param_2[1];
    *param_5 = (uint)(byte)param_2[6];
    *param_6 = (uint)*(byte *)((int)param_2 + 0x19);
    if (param_8 != (uint *)0x0) {
      *param_8 = (uint)*(byte *)((int)param_2 + 0x1a);
    }
    if (param_9 != (uint *)0x0) {
      *param_9 = (uint)*(byte *)((int)param_2 + 0x1b);
    }
    if (param_7 != (uint *)0x0) {
      *param_7 = (uint)(byte)param_2[7];
    }
    uVar1 = *param_6;
    if (uVar1 == 3) {
      uVar2 = 1;
    }
    else {
      uVar2 = (int)(char)uVar1 & 2U | 1;
    }
    if ((uVar1 & 4) != 0) {
      uVar2 = uVar2 + 1;
    }
    if ((uint)(0x7fffffff / (ulonglong)(uint)((int)(*param_5 * uVar2 + 7) >> 3)) < *param_3) {
      png_warning(png_ptr,"Width too large for libpng to process image data.");
    }
    uVar3 = 1;
  }
  return uVar3;
}



/* grim_png_set_packing @ 1001eb2a */

undefined4 __cdecl grim_png_set_packing(int param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  if ((((param_1 != 0) && (param_2 != 0)) && ((*(byte *)(param_2 + 8) & 8) != 0)) &&
     (param_3 != (undefined4 *)0x0)) {
    *param_3 = *(undefined4 *)(param_2 + 0x10);
    *param_4 = (uint)*(ushort *)(param_2 + 0x14);
    return 8;
  }
  return 0;
}



/* grim_png_set_gray_to_rgb @ 1001eb5d */

undefined4 __cdecl
grim_png_set_gray_to_rgb(int param_1,int param_2,undefined4 *param_3,uint *param_4,int *param_5)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (((param_1 != 0) && (param_2 != 0)) && ((*(byte *)(param_2 + 8) & 0x10) != 0)) {
    if (*(char *)(param_2 + 0x19) == '\x03') {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = *(undefined4 *)(param_2 + 0x30);
        uVar1 = 0x10;
      }
      if (param_5 != (int *)0x0) {
        *param_5 = param_2 + 0x34;
      }
    }
    else {
      if (param_5 != (int *)0x0) {
        *param_5 = param_2 + 0x34;
        uVar1 = 0x10;
      }
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = 0;
      }
    }
    if (param_4 != (uint *)0x0) {
      *param_4 = (uint)*(ushort *)(param_2 + 0x16);
      uVar1 = 0x10;
    }
  }
  return uVar1;
}



/* grim_png_get_valid @ 1001ebc4 */

void __cdecl grim_png_get_valid(int param_1)

{
  *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 1;
  return;
}



/* grim_png_get_image_width @ 1001ebcd */

void __cdecl grim_png_get_image_width(int param_1)

{
  if (*(char *)(param_1 + 0x117) == '\x10') {
    *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 0x10;
  }
  return;
}



/* grim_png_get_image_height @ 1001ebdf */

void __cdecl grim_png_get_image_height(int param_1)

{
  if (*(byte *)(param_1 + 0x117) < 8) {
    *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 4;
    *(undefined1 *)(param_1 + 0x118) = 8;
  }
  return;
}



/* grim_png_set_bgr @ 1001ebf8 */

undefined4 __cdecl grim_png_set_bgr(int param_1)

{
  if (*(char *)(param_1 + 0x113) != '\0') {
    *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 2;
    return 7;
  }
  return 1;
}



/* grim_png_do_read_transformations @ 1001ec11 */

void __cdecl grim_png_do_read_transformations(int param_1,byte param_2,int param_3)

{
  *(byte *)(param_1 + 0x61) = *(byte *)(param_1 + 0x61) | 0x80;
  *(ushort *)(param_1 + 0x11e) = (ushort)param_2;
  if (param_3 == 1) {
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) | 0x80;
  }
  else {
    *(byte *)(param_1 + 0x5c) = *(byte *)(param_1 + 0x5c) & 0x7f;
  }
  if (*(char *)(param_1 + 0x116) == '\x02') {
    *(undefined1 *)(param_1 + 0x11b) = 4;
  }
  if ((*(char *)(param_1 + 0x116) == '\0') && (7 < *(byte *)(param_1 + 0x117))) {
    *(undefined1 *)(param_1 + 0x11b) = 2;
  }
  return;
}



/* grim_png_do_bgr @ 1001ec5e */

void __cdecl grim_png_do_bgr(int *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  if (*(char *)((int)param_1 + 9) == '\x10') {
    for (iVar2 = (uint)*(byte *)((int)param_1 + 10) * *param_1; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *param_2;
      *param_2 = param_2[1];
      param_2[1] = uVar1;
      param_2 = param_2 + 2;
    }
  }
  return;
}



/* grim_png_do_swap @ 1001ec8b */

void __cdecl grim_png_do_swap(int *param_1,undefined1 *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  bVar1 = *(byte *)(param_1 + 2);
  if ((bVar1 & 2) != 0) {
    iVar4 = *param_1;
    if (*(char *)((int)param_1 + 9) == '\b') {
      if (bVar1 == 2) {
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          uVar2 = *param_2;
          *param_2 = param_2[2];
          param_2[2] = uVar2;
          param_2 = param_2 + 3;
        }
      }
      else if (bVar1 == 6) {
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          uVar2 = *param_2;
          *param_2 = param_2[2];
          param_2[2] = uVar2;
          param_2 = param_2 + 4;
        }
      }
    }
    else if (*(char *)((int)param_1 + 9) == '\x10') {
      if (bVar1 == 2) {
        if (iVar4 != 0) {
          puVar3 = param_2 + 1;
          do {
            uVar2 = puVar3[-1];
            puVar3[-1] = puVar3[3];
            puVar3[3] = uVar2;
            uVar2 = *puVar3;
            *puVar3 = puVar3[4];
            puVar3[4] = uVar2;
            puVar3 = puVar3 + 6;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
      }
      else if ((bVar1 == 6) && (iVar4 != 0)) {
        puVar3 = param_2 + 1;
        do {
          uVar2 = puVar3[-1];
          puVar3[-1] = puVar3[3];
          puVar3[3] = uVar2;
          uVar2 = *puVar3;
          *puVar3 = puVar3[4];
          puVar3[4] = uVar2;
          puVar3 = puVar3 + 8;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
  }
  return;
}



/* grim_png_set_expand @ 1001ed4a */

void __cdecl grim_png_set_expand(int param_1,double param_2,double param_3)

{
  if (0.05 < ABS(param_2 * param_3 - 1.0)) {
    *(byte *)(param_1 + 0x61) = *(byte *)(param_1 + 0x61) | 0x20;
  }
  *(float *)(param_1 + 0x130) = (float)param_3;
  *(float *)(param_1 + 0x134) = (float)param_2;
  return;
}



/* grim_png_set_filler @ 1001ed80 */

void __cdecl grim_png_set_filler(int param_1)

{
  *(byte *)(param_1 + 0x61) = *(byte *)(param_1 + 0x61) | 0x10;
  return;
}



/* grim_png_read_update_info @ 1001ed89 */

void __cdecl grim_png_read_update_info(int param_1,int *param_2)

{
  byte bVar1;
  
  if ((*(byte *)(param_1 + 0x61) & 0x10) == 0) goto LAB_1001edd5;
  if (*(byte *)((int)param_2 + 0x19) == 3) {
    *(char *)((int)param_2 + 0x19) = (*(short *)(param_1 + 0x10a) != 0) * '\x04' + '\x02';
LAB_1001edcd:
    *(undefined1 *)(param_2 + 6) = 8;
  }
  else {
    if (*(short *)(param_1 + 0x10a) != 0) {
      *(byte *)((int)param_2 + 0x19) = *(byte *)((int)param_2 + 0x19) | 4;
    }
    if (*(byte *)(param_2 + 6) < 8) goto LAB_1001edcd;
  }
  *(undefined2 *)((int)param_2 + 0x16) = 0;
LAB_1001edd5:
  if ((*(byte *)(param_1 + 0x61) & 0x20) != 0) {
    param_2[10] = *(int *)(param_1 + 0x130);
  }
  if (((*(byte *)(param_1 + 0x61) & 4) != 0) && ((char)param_2[6] == '\x10')) {
    *(undefined1 *)(param_2 + 6) = 8;
  }
  if (((*(byte *)(param_1 + 0x60) & 0x40) != 0) &&
     ((((*(char *)((int)param_2 + 0x19) == '\x02' || (*(char *)((int)param_2 + 0x19) == '\x06')) &&
       (*(int *)(param_1 + 0x174) != 0)) && ((char)param_2[6] == '\b')))) {
    *(undefined1 *)((int)param_2 + 0x19) = 3;
  }
  if (((*(byte *)(param_1 + 0x60) & 4) != 0) && (*(byte *)(param_2 + 6) < 8)) {
    *(undefined1 *)(param_2 + 6) = 8;
  }
  bVar1 = *(byte *)((int)param_2 + 0x19);
  if ((bVar1 == 3) || ((bVar1 & 2) == 0)) {
    *(undefined1 *)((int)param_2 + 0x1d) = 1;
  }
  else {
    *(undefined1 *)((int)param_2 + 0x1d) = 3;
  }
  if ((bVar1 & 4) != 0) {
    *(char *)((int)param_2 + 0x1d) = *(char *)((int)param_2 + 0x1d) + '\x01';
  }
  if (((*(byte *)(param_1 + 0x61) & 0x80) != 0) && ((bVar1 == 2 || (bVar1 == 0)))) {
    *(char *)((int)param_2 + 0x1d) = *(char *)((int)param_2 + 0x1d) + '\x01';
  }
  bVar1 = (char)param_2[6] * *(char *)((int)param_2 + 0x1d);
  *(byte *)((int)param_2 + 0x1e) = bVar1;
  param_2[3] = (uint)bVar1 * *param_2 + 7 >> 3;
  return;
}



/* grim_png_do_invert @ 1001ee74 */

void __cdecl grim_png_do_invert(int *param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  bVar2 = *(byte *)((int)param_1 + 9);
  if (bVar2 < 8) {
    iVar3 = *param_1;
    if (bVar2 == 1) {
      pbVar5 = (byte *)((iVar3 - 1U >> 3) + param_2);
      pbVar6 = (byte *)(iVar3 + -1 + param_2);
      iVar4 = 7 - (iVar3 - 1U & 7);
      for (iVar1 = iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pbVar6 = *pbVar5 >> ((byte)iVar4 & 0x1f) & 1;
        if (iVar4 == 7) {
          iVar4 = 0;
          pbVar5 = pbVar5 + -1;
        }
        else {
          iVar4 = iVar4 + 1;
        }
        pbVar6 = pbVar6 + -1;
      }
    }
    else if (bVar2 == 2) {
      pbVar5 = (byte *)((iVar3 - 1U >> 2) + param_2);
      pbVar6 = (byte *)(iVar3 + -1 + param_2);
      iVar4 = (iVar3 - 1U & 3) * -2 + 6;
      for (iVar1 = iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pbVar6 = *pbVar5 >> ((byte)iVar4 & 0x1f) & 3;
        if (iVar4 == 6) {
          iVar4 = 0;
          pbVar5 = pbVar5 + -1;
        }
        else {
          iVar4 = iVar4 + 2;
        }
        pbVar6 = pbVar6 + -1;
      }
    }
    else if (bVar2 == 4) {
      pbVar5 = (byte *)((iVar3 - 1U >> 1) + param_2);
      pbVar6 = (byte *)(iVar3 + -1 + param_2);
      iVar4 = (iVar3 - 1U & 1) * -4 + 4;
      for (iVar1 = iVar3; iVar1 != 0; iVar1 = iVar1 + -1) {
        *pbVar6 = *pbVar5 >> ((byte)iVar4 & 0x1f) & 0xf;
        if (iVar4 == 4) {
          iVar4 = 0;
          pbVar5 = pbVar5 + -1;
        }
        else {
          iVar4 = 4;
        }
        pbVar6 = pbVar6 + -1;
      }
    }
    *(undefined1 *)((int)param_1 + 9) = 8;
    *(byte *)((int)param_1 + 0xb) = *(byte *)((int)param_1 + 10) << 3;
    param_1[1] = (uint)*(byte *)((int)param_1 + 10) * iVar3;
  }
  return;
}



/* grim_png_do_shift @ 1001ef84 */

byte * __cdecl grim_png_do_shift(byte *param_1,byte *param_2,byte *param_3)

{
  bool bVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 in_EAX;
  byte *pbVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int local_18 [4];
  byte *local_8;
  
  bVar2 = param_1[8];
  pbVar4 = (byte *)CONCAT31((int3)((uint)in_EAX >> 8),bVar2);
  if (bVar2 != 3) {
    bVar1 = false;
    iVar10 = *(int *)param_1;
    if ((bVar2 & 2) == 0) {
      iVar8 = (uint)param_1[9] - (uint)param_3[3];
      uVar9 = 1;
    }
    else {
      iVar8 = (uint)param_1[9] - (uint)*param_3;
      local_18[1] = (uint)param_1[9] - (uint)param_3[1];
      local_18[2] = (uint)param_1[9] - (uint)param_3[2];
      uVar9 = 3;
    }
    local_18[0] = iVar8;
    pbVar4 = param_3;
    if ((param_1[8] & 4) != 0) {
      pbVar4 = (byte *)((uint)param_1[9] - (uint)param_3[4]);
      local_18[uVar9] = (int)pbVar4;
      uVar9 = uVar9 + 1;
    }
    iVar7 = 0;
    if (uVar9 != 0) {
      do {
        pbVar4 = (byte *)(local_18 + iVar7);
        if (*(int *)pbVar4 < 1) {
          pbVar4[0] = 0;
          pbVar4[1] = 0;
          pbVar4[2] = 0;
          pbVar4[3] = 0;
          iVar8 = local_18[0];
        }
        else {
          bVar1 = true;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < (int)uVar9);
      if (bVar1) {
        uVar5 = (uint)param_1[9];
        if (uVar5 == 2) {
          pbVar4 = param_2;
          for (iVar10 = *(int *)(param_1 + 4); iVar10 != 0; iVar10 = iVar10 + -1) {
            *pbVar4 = *pbVar4 >> 1 & 0x55;
            pbVar4 = pbVar4 + 1;
          }
        }
        else if (uVar5 == 4) {
          bVar6 = (byte)iVar8;
          uVar9 = 0xf0 >> (bVar6 & 0x1f) & 0xfffffff0;
          bVar2 = (byte)uVar9 | (byte)(0xf >> (bVar6 & 0x1f));
          pbVar4 = (byte *)CONCAT31((int3)(uVar9 >> 8),bVar2);
          for (iVar10 = *(int *)(param_1 + 4); iVar10 != 0; iVar10 = iVar10 + -1) {
            *param_2 = *param_2 >> (bVar6 & 0x1f) & bVar2;
            param_2 = param_2 + 1;
          }
        }
        else if (uVar5 == 8) {
          uVar5 = iVar10 * uVar9;
          uVar11 = 0;
          pbVar4 = (byte *)0x0;
          if (uVar5 != 0) {
            do {
              pbVar4 = (byte *)(uVar11 / uVar9);
              *param_2 = *param_2 >> (*(byte *)(local_18 + uVar11 % uVar9) & 0x1f);
              param_2 = param_2 + 1;
              uVar11 = uVar11 + 1;
            } while (uVar11 < uVar5);
          }
        }
        else {
          pbVar4 = (byte *)(uVar5 - 0x10);
          if (pbVar4 == (byte *)0x0) {
            local_8 = (byte *)(iVar10 * uVar9);
            param_1 = (byte *)0x0;
            if (local_8 != (byte *)0x0) {
              do {
                uVar3 = (ushort)((ushort)*param_2 * 0x100 + (ushort)param_2[1]) >>
                        ((byte)(short)local_18[(uint)param_1 % uVar9] & 0x1f);
                *param_2 = (byte)(uVar3 >> 8);
                param_2[1] = (byte)uVar3;
                param_2 = param_2 + 2;
                pbVar4 = param_1 + 1;
                param_1 = pbVar4;
              } while (pbVar4 < local_8);
            }
          }
        }
      }
    }
  }
  return pbVar4;
}



/* grim_png_do_packswap @ 1001f0fb */

void __cdecl grim_png_do_packswap(int *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (*(char *)((int)param_1 + 9) == '\x10') {
    puVar3 = param_2;
    for (iVar2 = (uint)*(byte *)((int)param_1 + 10) * *param_1; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *param_2;
      param_2 = param_2 + 2;
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
    }
    *(undefined1 *)((int)param_1 + 9) = 8;
    *(byte *)((int)param_1 + 0xb) = *(byte *)((int)param_1 + 10) << 3;
    param_1[1] = (uint)*(byte *)((int)param_1 + 10) * *param_1;
  }
  return;
}



/* grim_png_do_filler @ 1001f13f */

void __cdecl grim_png_do_filler(uint *param_1,int param_2,uint param_3,byte param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 uVar6;
  byte bVar7;
  uint uVar8;
  undefined1 *puVar9;
  
  puVar2 = param_1;
  uVar3 = *param_1;
  uVar8 = param_3 >> 8;
  bVar7 = (byte)(param_3 >> 8);
  uVar6 = (undefined1)param_3;
  if ((char)param_1[2] == '\0') {
    if (*(char *)((int)param_1 + 9) == '\b') {
      puVar4 = (undefined1 *)(param_2 + uVar3);
      puVar9 = puVar4 + uVar3;
      uVar8 = uVar3;
      if ((param_4 & 0x80) == 0) {
        for (; uVar8 != 0; uVar8 = uVar8 - 1) {
          puVar4 = puVar4 + -1;
          puVar9[-1] = *puVar4;
          puVar9 = puVar9 + -2;
          *puVar9 = uVar6;
        }
      }
      else {
        if (1 < uVar3) {
          param_1 = (uint *)(uVar3 - 1);
          do {
            puVar4 = puVar4 + -1;
            puVar9[-1] = uVar6;
            puVar9 = puVar9 + -2;
            param_1 = (uint *)((int)param_1 + -1);
            *puVar9 = *puVar4;
          } while (param_1 != (uint *)0x0);
        }
        puVar9[-1] = uVar6;
      }
      *(undefined1 *)((int)puVar2 + 10) = 2;
      *(undefined1 *)((int)puVar2 + 0xb) = 0x10;
      uVar3 = uVar3 * 2;
    }
    else {
      if (*(char *)((int)param_1 + 9) != '\x10') {
        return;
      }
      if ((param_4 & 0x80) == 0) {
        puVar9 = (undefined1 *)(uVar3 + param_2);
        puVar4 = puVar9 + uVar3;
        for (uVar8 = uVar3; uVar8 != 0; uVar8 = uVar8 - 1) {
          puVar5 = puVar9 + -1;
          puVar9 = puVar9 + -2;
          puVar4[-1] = *puVar5;
          puVar4[-2] = *puVar9;
          puVar4[-3] = bVar7;
          puVar4 = puVar4 + -4;
          *puVar4 = uVar6;
        }
      }
      else {
        puVar9 = (undefined1 *)(param_2 + uVar3);
        puVar4 = puVar9 + uVar3;
        if (1 < uVar3) {
          param_3 = uVar3 - 1;
          do {
            puVar4[-1] = (char)uVar8;
            puVar4[-2] = uVar6;
            puVar4[-3] = puVar9[-1];
            puVar9 = puVar9 + -2;
            puVar4 = puVar4 + -4;
            param_3 = param_3 - 1;
            *puVar4 = *puVar9;
            uVar8 = (uint)bVar7;
          } while (param_3 != 0);
        }
        puVar4[-1] = bVar7;
        puVar4[-2] = uVar6;
      }
      *(undefined1 *)((int)param_1 + 10) = 2;
      *(undefined1 *)((int)param_1 + 0xb) = 0x20;
      uVar3 = uVar3 << 2;
    }
  }
  else {
    if ((char)param_1[2] != '\x02') {
      return;
    }
    if (*(char *)((int)param_1 + 9) == '\b') {
      if ((param_4 & 0x80) == 0) {
        puVar9 = (undefined1 *)(param_2 + uVar3 * 3);
        puVar4 = puVar9 + uVar3;
        for (uVar8 = uVar3; uVar8 != 0; uVar8 = uVar8 - 1) {
          puVar4[-1] = puVar9[-1];
          puVar4[-2] = puVar9[-2];
          puVar9 = puVar9 + -3;
          puVar4[-3] = *puVar9;
          puVar4 = puVar4 + -4;
          *puVar4 = uVar6;
        }
      }
      else {
        puVar9 = (undefined1 *)(param_2 + uVar3 * 3);
        puVar4 = puVar9 + uVar3;
        if (1 < uVar3) {
          param_1 = (uint *)(uVar3 - 1);
          do {
            puVar4[-1] = uVar6;
            puVar4[-2] = puVar9[-1];
            puVar5 = puVar9 + -2;
            puVar9 = puVar9 + -3;
            puVar4[-3] = *puVar5;
            puVar4 = puVar4 + -4;
            param_1 = (uint *)((int)param_1 + -1);
            *puVar4 = *puVar9;
          } while (param_1 != (uint *)0x0);
        }
        puVar4[-1] = uVar6;
      }
      *(undefined1 *)((int)puVar2 + 0xb) = 0x20;
      iVar1 = 2;
    }
    else {
      if (*(char *)((int)param_1 + 9) != '\x10') {
        return;
      }
      puVar9 = (undefined1 *)(param_2 + uVar3 * 3);
      puVar4 = puVar9 + uVar3;
      uVar8 = uVar3;
      if ((param_4 & 0x80) == 0) {
        for (; uVar8 != 0; uVar8 = uVar8 - 1) {
          puVar4[-1] = puVar9[-1];
          puVar4[-2] = puVar9[-2];
          puVar4[-3] = puVar9[-3];
          puVar4[-4] = puVar9[-4];
          puVar4[-5] = puVar9[-5];
          puVar9 = puVar9 + -6;
          puVar4[-6] = *puVar9;
          puVar4[-7] = bVar7;
          puVar4 = puVar4 + -8;
          *puVar4 = uVar6;
        }
      }
      else {
        if (1 < uVar3) {
          param_3 = uVar3 - 1;
          do {
            puVar4[-1] = bVar7;
            puVar4[-2] = uVar6;
            puVar4[-3] = puVar9[-1];
            puVar4[-4] = puVar9[-2];
            puVar4[-5] = puVar9[-3];
            puVar4[-6] = puVar9[-4];
            puVar5 = puVar9 + -5;
            puVar9 = puVar9 + -6;
            puVar4[-7] = *puVar5;
            puVar4 = puVar4 + -8;
            param_3 = param_3 - 1;
            *puVar4 = *puVar9;
          } while (param_3 != 0);
        }
        puVar4[-1] = bVar7;
        puVar4[-2] = uVar6;
      }
      *(undefined1 *)((int)param_1 + 0xb) = 0x40;
      iVar1 = 3;
    }
    uVar3 = uVar3 << iVar1;
    *(undefined1 *)((int)puVar2 + 10) = 4;
  }
  puVar2[1] = uVar3;
  return;
}



/* grim_png_do_chop @ 1001f377 */

void __cdecl grim_png_do_chop(int *param_1,byte *param_2,int param_3,int param_4,byte param_5)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int local_c;
  byte *local_8;
  
  bVar1 = *(byte *)((int)param_1 + 9);
  iVar8 = *param_1;
  if (((bVar1 < 9) && (param_3 != 0)) || ((bVar1 == 0x10 && (param_4 != 0)))) {
    cVar2 = (char)param_1[2];
    if (cVar2 == '\0') {
      if ((bVar1 == 2) && (local_8 = param_2, iVar8 != 0)) {
        local_c = (iVar8 - 1U >> 2) + 1;
        do {
          uVar4 = (uint)*local_8;
          uVar6 = uVar4 & 0xc0;
          uVar5 = uVar4 & 3;
          uVar7 = uVar4 & 0xc;
          uVar4 = uVar4 & 0x30;
          local_c = local_c + -1;
          *local_8 = (byte)((byte)(*(byte *)(((uVar7 << 2 | uVar7) << 2 | (int)uVar7 >> 2 | uVar7) +
                                            param_3) & 0xcf |
                                  *(byte *)((((uVar5 << 2 | uVar5) << 2 | uVar5) << 2 | uVar5) +
                                           param_3) >> 2) >> 2 |
                           *(byte *)(((int)((int)uVar4 >> 2 | uVar4) >> 2 | uVar4 << 2 | uVar4) +
                                    param_3) & 0xc3) >> 2 |
                     *(byte *)(((int)((int)((int)uVar6 >> 2 | uVar6) >> 2 | uVar6) >> 2 | uVar6) +
                              param_3) & 0xc0;
          local_8 = local_8 + 1;
        } while (local_c != 0);
      }
      cVar2 = *(char *)((int)param_1 + 9);
      if (cVar2 == '\x04') {
        if (iVar8 != 0) {
          iVar8 = (iVar8 - 1U >> 1) + 1;
          do {
            uVar5 = *param_2 & 0xf0;
            uVar4 = *param_2 & 0xf;
            *param_2 = *(byte *)(((int)uVar5 >> 4 | uVar5) + param_3) & 0xf0 |
                       *(byte *)((uVar4 << 4 | uVar4) + param_3) >> 4;
            param_2 = param_2 + 1;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      else if (cVar2 == '\b') {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *param_2 = *(byte *)((uint)*param_2 + param_3);
          param_2 = param_2 + 1;
        }
      }
      else if (cVar2 == '\x10') {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[1] >> (param_5 & 0x1f)) * 4) +
                   (uint)*param_2 * 2);
          *param_2 = (byte)((ushort)uVar3 >> 8);
          param_2[1] = (byte)uVar3;
          param_2 = param_2 + 2;
        }
      }
    }
    else if (cVar2 == '\x02') {
      if (bVar1 == 8) {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *param_2 = *(byte *)((uint)*param_2 + param_3);
          param_2[1] = *(byte *)((uint)param_2[1] + param_3);
          param_2[2] = *(byte *)((uint)param_2[2] + param_3);
          param_2 = param_2 + 3;
        }
      }
      else {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[1] >> (param_5 & 0x1f)) * 4) +
                   (uint)*param_2 * 2);
          param_2[1] = (byte)uVar3;
          *param_2 = (byte)((ushort)uVar3 >> 8);
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[3] >> (param_5 & 0x1f)) * 4) +
                   (uint)param_2[2] * 2);
          param_2[3] = (byte)uVar3;
          param_2[2] = (byte)((ushort)uVar3 >> 8);
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[5] >> (param_5 & 0x1f)) * 4) +
                   (uint)param_2[4] * 2);
          param_2[4] = (byte)((ushort)uVar3 >> 8);
          param_2[5] = (byte)uVar3;
          param_2 = param_2 + 6;
        }
      }
    }
    else if (cVar2 == '\x04') {
      if (bVar1 == 8) {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *param_2 = *(byte *)((uint)*param_2 + param_3);
          param_2 = param_2 + 2;
        }
      }
      else {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[1] >> (param_5 & 0x1f)) * 4) +
                   (uint)*param_2 * 2);
          *param_2 = (byte)((ushort)uVar3 >> 8);
          param_2[1] = (byte)uVar3;
          param_2 = param_2 + 4;
        }
      }
    }
    else if (cVar2 == '\x06') {
      if (bVar1 == 8) {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          *param_2 = *(byte *)((uint)*param_2 + param_3);
          param_2[1] = *(byte *)((uint)param_2[1] + param_3);
          param_2[2] = *(byte *)((uint)param_2[2] + param_3);
          param_2 = param_2 + 4;
        }
      }
      else {
        for (; iVar8 != 0; iVar8 = iVar8 + -1) {
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[1] >> (param_5 & 0x1f)) * 4) +
                   (uint)*param_2 * 2);
          param_2[1] = (byte)uVar3;
          *param_2 = (byte)((ushort)uVar3 >> 8);
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[3] >> (param_5 & 0x1f)) * 4) +
                   (uint)param_2[2] * 2);
          param_2[3] = (byte)uVar3;
          param_2[2] = (byte)((ushort)uVar3 >> 8);
          uVar3 = *(undefined2 *)
                   (*(int *)(param_4 + (uint)(param_2[5] >> (param_5 & 0x1f)) * 4) +
                   (uint)param_2[4] * 2);
          param_2[4] = (byte)((ushort)uVar3 >> 8);
          param_2[5] = (byte)uVar3;
          param_2 = param_2 + 8;
        }
      }
    }
  }
  return;
}



/* grim_png_do_expand_palette @ 1001f6c5 */

void __cdecl grim_png_do_expand_palette(uint *param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  
  uVar2 = *param_1;
  if ((char)param_1[2] == '\x03') {
    bVar1 = *(byte *)((int)param_1 + 9);
    if (bVar1 < 8) {
      if (bVar1 == 1) {
        pbVar6 = (byte *)(uVar2 + param_2 + -1);
        iVar3 = 7 - (uVar2 - 1 & 7);
        pbVar5 = (byte *)((uVar2 - 1 >> 3) + param_2);
        for (uVar7 = uVar2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar6 = *pbVar5 >> ((byte)iVar3 & 0x1f) & 1;
          if (iVar3 == 7) {
            iVar3 = 0;
            pbVar5 = pbVar5 + -1;
          }
          else {
            iVar3 = iVar3 + 1;
          }
          pbVar6 = pbVar6 + -1;
        }
      }
      else if (bVar1 == 2) {
        pbVar6 = (byte *)(uVar2 + param_2 + -1);
        iVar3 = (3 - (uVar2 - 1 & 3)) * 2;
        pbVar5 = (byte *)((uVar2 - 1 >> 2) + param_2);
        for (uVar7 = uVar2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar6 = *pbVar5 >> ((byte)iVar3 & 0x1f) & 3;
          if (iVar3 == 6) {
            iVar3 = 0;
            pbVar5 = pbVar5 + -1;
          }
          else {
            iVar3 = iVar3 + 2;
          }
          pbVar6 = pbVar6 + -1;
        }
      }
      else if (bVar1 == 4) {
        pbVar6 = (byte *)(uVar2 + param_2 + -1);
        iVar3 = (uVar2 & 1) << 2;
        pbVar5 = (byte *)((uVar2 - 1 >> 1) + param_2);
        for (uVar7 = uVar2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar6 = *pbVar5 >> ((byte)iVar3 & 0x1f) & 0xf;
          if (iVar3 == 4) {
            iVar3 = 0;
            pbVar5 = pbVar5 + -1;
          }
          else {
            iVar3 = iVar3 + 4;
          }
          pbVar6 = pbVar6 + -1;
        }
      }
      *(undefined1 *)((int)param_1 + 9) = 8;
      *(undefined1 *)((int)param_1 + 0xb) = 8;
      param_1[1] = uVar2;
    }
    if (*(char *)((int)param_1 + 9) == '\b') {
      pbVar6 = (byte *)(uVar2 + param_2 + -1);
      if (param_4 == 0) {
        uVar7 = uVar2 * 3;
        puVar4 = (undefined1 *)((uVar7 - 1) + param_2);
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar4 = *(undefined1 *)((uint)*pbVar6 * 3 + 2 + param_3);
          puVar4[-1] = *(undefined1 *)((uint)*pbVar6 * 3 + 1 + param_3);
          puVar4[-2] = *(undefined1 *)(param_3 + (uint)*pbVar6 * 3);
          puVar4 = puVar4 + -3;
          pbVar6 = pbVar6 + -1;
        }
        *(undefined1 *)((int)param_1 + 0xb) = 0x18;
        *(undefined1 *)(param_1 + 2) = 2;
        *(undefined1 *)((int)param_1 + 10) = 3;
      }
      else {
        uVar7 = uVar2 * 4;
        puVar4 = (undefined1 *)((uVar7 - 1) + param_2);
        for (; uVar2 != 0; uVar2 = uVar2 - 1) {
          if ((int)(uint)*pbVar6 < param_5) {
            *puVar4 = *(undefined1 *)((uint)*pbVar6 + param_4);
          }
          else {
            *puVar4 = 0xff;
          }
          puVar4[-1] = *(undefined1 *)((uint)*pbVar6 * 3 + 2 + param_3);
          puVar4[-2] = *(undefined1 *)((uint)*pbVar6 * 3 + 1 + param_3);
          puVar4[-3] = *(undefined1 *)(param_3 + (uint)*pbVar6 * 3);
          puVar4 = puVar4 + -4;
          pbVar6 = pbVar6 + -1;
        }
        *(undefined1 *)((int)param_1 + 0xb) = 0x20;
        *(undefined1 *)(param_1 + 2) = 6;
        *(undefined1 *)((int)param_1 + 10) = 4;
      }
      *(undefined1 *)((int)param_1 + 9) = 8;
      param_1[1] = uVar7;
    }
  }
  return;
}



/* grim_png_do_expand @ 1001f8cd */

void __cdecl grim_png_do_expand(int *param_1,int param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  byte bVar8;
  ushort uVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  
  iVar2 = *param_1;
  if ((char)param_1[2] == '\0') {
    uVar9 = 0;
    if (param_3 != 0) {
      uVar9 = *(ushort *)(param_3 + 8);
    }
    bVar8 = *(byte *)((int)param_1 + 9);
    if (bVar8 < 8) {
      if (bVar8 == 1) {
        uVar9 = uVar9 * 0xff;
        pcVar1 = (char *)(iVar2 + param_2 + -1);
        iVar4 = 7 - (iVar2 - 1U & 7);
        pbVar5 = (byte *)((iVar2 - 1U >> 3) + param_2);
        for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pcVar1 = -((*pbVar5 >> ((byte)iVar4 & 0x1f) & 1) != 0);
          if (iVar4 == 7) {
            iVar4 = 0;
            pbVar5 = pbVar5 + -1;
          }
          else {
            iVar4 = iVar4 + 1;
          }
          pcVar1 = pcVar1 + -1;
        }
      }
      else if (bVar8 == 2) {
        uVar9 = uVar9 * 0x55;
        pbVar5 = (byte *)(iVar2 + param_2 + -1);
        iVar4 = (3 - (iVar2 - 1U & 3)) * 2;
        pbVar6 = (byte *)((iVar2 - 1U >> 2) + param_2);
        for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
          bVar8 = *pbVar6 >> ((byte)iVar4 & 0x1f) & 3;
          *pbVar5 = ((bVar8 << 2 | bVar8) << 2 | bVar8) << 2 | bVar8;
          if (iVar4 == 6) {
            iVar4 = 0;
            pbVar6 = pbVar6 + -1;
          }
          else {
            iVar4 = iVar4 + 2;
          }
          pbVar5 = pbVar5 + -1;
        }
      }
      else if (bVar8 == 4) {
        uVar9 = uVar9 * 0x11;
        pbVar5 = (byte *)(iVar2 + param_2 + -1);
        pbVar6 = (byte *)((iVar2 - 1U >> 1) + param_2);
        iVar4 = (iVar2 - 1U & 1) * -4 + 4;
        for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
          bVar8 = *pbVar6 >> ((byte)iVar4 & 0x1f) & 0xf;
          *pbVar5 = bVar8 << 4 | bVar8;
          iVar3 = 4;
          if (iVar4 == 4) {
            iVar3 = 0;
            pbVar6 = pbVar6 + -1;
          }
          pbVar5 = pbVar5 + -1;
          iVar4 = iVar3;
        }
      }
      *(undefined1 *)((int)param_1 + 9) = 8;
      *(undefined1 *)((int)param_1 + 0xb) = 8;
      param_1[1] = iVar2;
    }
    if (param_3 == 0) {
      return;
    }
    if (*(char *)((int)param_1 + 9) == '\b') {
      pbVar5 = (byte *)(iVar2 + param_2 + -1);
      puVar10 = (undefined1 *)(param_2 + -1 + iVar2 * 2);
      for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
        if (*pbVar5 == uVar9) {
          *puVar10 = 0;
        }
        else {
          *puVar10 = 0xff;
        }
        puVar10[-1] = *pbVar5;
        puVar10 = puVar10 + -2;
        pbVar5 = pbVar5 + -1;
      }
    }
    else if (*(char *)((int)param_1 + 9) == '\x10') {
      puVar10 = (undefined1 *)(param_1[1] + -1 + param_2);
      puVar11 = (undefined1 *)(param_2 + -1 + param_1[1] * 2);
      for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
        if (CONCAT11(puVar10[-1],*puVar10) == uVar9) {
          *puVar11 = 0;
          puVar11[-1] = 0;
        }
        else {
          *puVar11 = 0xff;
          puVar11[-1] = 0xff;
        }
        puVar11[-2] = *puVar10;
        puVar11[-3] = puVar10[-1];
        puVar11 = puVar11 + -4;
        puVar10 = puVar10 + -2;
      }
    }
    *(undefined1 *)(param_1 + 2) = 4;
    *(undefined1 *)((int)param_1 + 10) = 2;
    bVar8 = *(char *)((int)param_1 + 9) << 1;
  }
  else {
    if ((char)param_1[2] != '\x02') {
      return;
    }
    if (param_3 == 0) {
      return;
    }
    if (*(char *)((int)param_1 + 9) == '\b') {
      pbVar5 = (byte *)(param_1[1] + -1 + param_2);
      puVar10 = (undefined1 *)(param_2 + -1 + iVar2 * 4);
      for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
        if ((((ushort)pbVar5[-2] == *(ushort *)(param_3 + 2)) &&
            ((ushort)pbVar5[-1] == *(ushort *)(param_3 + 4))) &&
           ((ushort)*pbVar5 == *(ushort *)(param_3 + 6))) {
          *puVar10 = 0;
        }
        else {
          *puVar10 = 0xff;
        }
        puVar10[-1] = *pbVar5;
        puVar10[-2] = pbVar5[-1];
        puVar10[-3] = pbVar5[-2];
        puVar10 = puVar10 + -4;
        pbVar5 = pbVar5 + -3;
      }
    }
    else if (*(char *)((int)param_1 + 9) == '\x10') {
      puVar10 = (undefined1 *)(param_1[1] + -1 + param_2);
      puVar11 = (undefined1 *)(param_2 + -1 + iVar2 * 8);
      for (iVar7 = iVar2; iVar7 != 0; iVar7 = iVar7 + -1) {
        if (((CONCAT11(puVar10[-5],puVar10[-4]) == *(short *)(param_3 + 2)) &&
            (CONCAT11(puVar10[-3],puVar10[-2]) == *(short *)(param_3 + 4))) &&
           (CONCAT11(puVar10[-1],*puVar10) == *(short *)(param_3 + 6))) {
          *puVar11 = 0;
          puVar11[-1] = 0;
        }
        else {
          *puVar11 = 0xff;
          puVar11[-1] = 0xff;
        }
        puVar11[-2] = *puVar10;
        puVar11[-3] = puVar10[-1];
        puVar11[-4] = puVar10[-2];
        puVar11[-5] = puVar10[-3];
        puVar11[-6] = puVar10[-4];
        puVar11[-7] = puVar10[-5];
        puVar11 = puVar11 + -8;
        puVar10 = puVar10 + -6;
      }
    }
    *(undefined1 *)(param_1 + 2) = 6;
    *(undefined1 *)((int)param_1 + 10) = 4;
    bVar8 = *(char *)((int)param_1 + 9) << 2;
  }
  *(byte *)((int)param_1 + 0xb) = bVar8;
  param_1[1] = (uint)bVar8 * iVar2 >> 3;
  return;
}



/* grim_png_build_gamma_table @ 1001fd2d */

void __cdecl grim_png_build_gamma_table(png_structp png_ptr)

{
  png_structp ppVar1;
  byte bVar2;
  png_uint_32 pVar3;
  png_structp png_ptr_00;
  undefined1 uVar4;
  undefined2 uVar5;
  void *pvVar6;
  uint uVar7;
  uint uVar8;
  byte bVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  ushort local_10;
  uint local_8;
  
  png_ptr_00 = png_ptr;
  if ((float)png_ptr[1].jmpbuf[4] != 0.0) {
    if (png_ptr->bit_depth < 9) {
      pvVar6 = png_malloc(png_ptr,0x100);
      png_ptr = (png_structp)0x0;
      png_ptr_00[1].jmpbuf[6] = (png_uint_32)pvVar6;
      do {
        _CIpow();
        uVar4 = ftol();
        ppVar1 = (png_structp)((int)png_ptr->jmpbuf + 1);
        *(undefined1 *)((int)png_ptr->jmpbuf + png_ptr_00[1].jmpbuf[6]) = uVar4;
        png_ptr = ppVar1;
      } while ((int)ppVar1 < 0x100);
    }
    else {
      if ((png_ptr->color_type & 2) == 0) {
        local_8 = (uint)*(byte *)((int)png_ptr[1].jmpbuf + 0x33);
      }
      else {
        local_8 = (uint)(byte)png_ptr[1].jmpbuf[0xc];
        uVar10 = (uint)*(byte *)((int)png_ptr[1].jmpbuf + 0x31);
        if (local_8 < uVar10) {
          local_8 = uVar10;
        }
        uVar10 = (uint)*(byte *)((int)png_ptr[1].jmpbuf + 0x32);
        if (local_8 < uVar10) {
          local_8 = uVar10;
        }
      }
      if (local_8 == 0) {
        local_8 = 0;
      }
      else {
        local_8 = 0x10 - local_8;
      }
      if (((png_ptr->transformations & 0x400) != 0) && ((int)local_8 < 5)) {
        local_8 = 5;
      }
      if (8 < (int)local_8) {
        local_8 = 8;
      }
      if ((int)local_8 < 0) {
        local_8 = 0;
      }
      bVar2 = (byte)local_8;
      bVar9 = 8 - bVar2;
      iVar11 = 1 << (bVar9 & 0x1f);
      png_ptr[1].jmpbuf[3] = local_8 & 0xff;
      pvVar6 = png_malloc(png_ptr,iVar11 << 2);
      pVar3 = png_ptr->transformations;
      png_ptr[1].jmpbuf[9] = (png_uint_32)pvVar6;
      png_ptr = (png_structp)0x0;
      if ((pVar3 & 0x480) == 0) {
        if (0 < iVar11) {
          do {
            pvVar6 = png_malloc(png_ptr_00,0x200);
            *(void **)(png_ptr_00[1].jmpbuf[9] + (int)png_ptr * 4) = pvVar6;
            iVar13 = 0;
            do {
              _CIpow();
              uVar5 = ftol();
              *(undefined2 *)(iVar13 + *(int *)(png_ptr_00[1].jmpbuf[9] + (int)png_ptr * 4)) = uVar5
              ;
              iVar13 = iVar13 + 2;
            } while (iVar13 < 0x200);
            png_ptr = (png_structp)((int)png_ptr->jmpbuf + 1);
          } while ((int)png_ptr < iVar11);
        }
      }
      else {
        if (0 < iVar11) {
          do {
            pvVar6 = png_malloc(png_ptr_00,0x200);
            ppVar1 = (png_structp)((int)png_ptr->jmpbuf + 1);
            *(void **)(png_ptr_00[1].jmpbuf[9] + (int)png_ptr * 4) = pvVar6;
            png_ptr = ppVar1;
          } while ((int)ppVar1 < iVar11);
        }
        uVar10 = 0;
        png_ptr = (png_structp)0x0;
        do {
          _CIpow();
          uVar7 = ftol();
          if (uVar10 <= uVar7) {
            local_10 = (ushort)(((uint)png_ptr & 0xff) << 8) | (ushort)png_ptr;
            do {
              uVar12 = uVar10 >> (bVar9 & 0x1f);
              uVar8 = 0xff >> (bVar2 & 0x1f) & uVar10;
              uVar10 = uVar10 + 1;
              *(ushort *)(*(int *)(png_ptr_00[1].jmpbuf[9] + uVar8 * 4) + uVar12 * 2) = local_10;
            } while (uVar10 <= uVar7);
          }
          png_ptr = (png_structp)((int)png_ptr->jmpbuf + 1);
        } while ((int)png_ptr < 0x100);
        if (uVar10 < (uint)(iVar11 << 8)) {
          do {
            *(undefined2 *)
             (*(int *)(png_ptr_00[1].jmpbuf[9] + (0xff >> (bVar2 & 0x1f) & uVar10) * 4) +
             (uVar10 >> (bVar9 & 0x1f)) * 2) = 0xffff;
            uVar10 = uVar10 + 1;
          } while (uVar10 < (uint)(iVar11 << 8));
        }
      }
    }
  }
  return;
}



/* grim_png_apply_gamma_palette @ 10020036 */

void __cdecl grim_png_apply_gamma_palette(png_structp png_ptr)

{
  png_byte pVar1;
  ushort uVar2;
  png_structp ppVar3;
  png_structp ppVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int local_8;
  
  ppVar4 = png_ptr;
  pVar1 = png_ptr->color_type;
  if ((png_ptr->transformations & 0x602000) != 0) {
    grim_png_build_gamma_table(png_ptr);
    if (pVar1 == '\x03') {
      uVar7 = (uint)(ushort)png_ptr->chunk_name_pad;
      if (uVar7 != 0) {
        pbVar5 = (byte *)(*(int *)&png_ptr->num_palette + 2);
        do {
          pbVar5[-2] = *(byte *)((uint)pbVar5[-2] + png_ptr[1].jmpbuf[6]);
          pbVar5[-1] = *(byte *)((uint)pbVar5[-1] + png_ptr[1].jmpbuf[6]);
          *pbVar5 = *(byte *)((uint)*pbVar5 + png_ptr[1].jmpbuf[6]);
          pbVar5 = pbVar5 + 3;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
    }
  }
  if (((png_ptr->transformations & 8) != 0) && (pVar1 == '\x03')) {
    ppVar3 = png_ptr + 1;
    iVar8 = 8 - (uint)(byte)png_ptr[1].jmpbuf[0xc];
    png_ptr = (png_structp)(8 - (uint)*(byte *)((int)png_ptr[1].jmpbuf + 0x31));
    local_8 = 8 - (uint)*(byte *)((int)ppVar3->jmpbuf + 0x32);
    if ((iVar8 < 0) || (8 < iVar8)) {
      iVar8 = 0;
    }
    if (((int)png_ptr < 0) || (8 < (int)png_ptr)) {
      png_ptr = (png_structp)0x0;
    }
    if ((local_8 < 0) || (8 < local_8)) {
      local_8 = 0;
    }
    uVar2 = (ushort)ppVar4->chunk_name_pad;
    if (uVar2 != 0) {
      iVar6 = 0;
      uVar7 = (uint)uVar2;
      do {
        pbVar5 = (byte *)(iVar6 + *(int *)&ppVar4->num_palette);
        *pbVar5 = *pbVar5 >> ((byte)iVar8 & 0x1f);
        pbVar5 = (byte *)(iVar6 + 1 + *(int *)&ppVar4->num_palette);
        *pbVar5 = *pbVar5 >> ((byte)png_ptr & 0x1f);
        pbVar5 = (byte *)(iVar6 + 2 + *(int *)&ppVar4->num_palette);
        *pbVar5 = *pbVar5 >> ((byte)local_8 & 0x1f);
        iVar6 = iVar6 + 3;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
  }
  return;
}



/* grim_png_do_transformations @ 10020149 */

void __cdecl grim_png_do_transformations(png_structp png_ptr)

{
  int iVar1;
  int iVar2;
  png_error_ptr *pppVar3;
  
  if (png_ptr->sub_row == (png_bytep)0x0) {
    png_error(png_ptr,"NULL row buffer");
  }
  if ((png_ptr->transformations & 0x1000) != 0) {
    if ((char)png_ptr->idat_size == '\x03') {
      iVar1._0_2_ = png_ptr->num_palette;
      iVar1._2_2_ = png_ptr->num_trans;
      grim_png_do_expand_palette(&(png_ptr->row_info).rowbytes,(int)(png_ptr->sub_row + 1),iVar1,
                   png_ptr[1].jmpbuf[0xf],(uint)*(ushort *)((int)&png_ptr->chunk_name_pad + 2));
    }
    else {
      if (*(short *)((int)&png_ptr->chunk_name_pad + 2) == 0) {
        pppVar3 = (png_error_ptr *)0x0;
      }
      else {
        pppVar3 = &png_ptr[1].error_fn;
      }
      grim_png_do_expand((int *)&(png_ptr->row_info).rowbytes,(int)(png_ptr->sub_row + 1),(int)pppVar3);
    }
  }
  if (((png_ptr->transformations & 0x2000) != 0) && (png_ptr->color_type != '\x03')) {
    grim_png_do_chop((int *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1,png_ptr[1].jmpbuf[6],
                 png_ptr[1].jmpbuf[9],(byte)png_ptr[1].jmpbuf[3]);
  }
  if ((png_ptr->transformations & 0x400) != 0) {
    grim_png_do_packswap((int *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1);
  }
  if ((png_ptr->transformations & 0x40) != 0) {
    grim_dxt_encoder_core((int *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1,(int)png_ptr[1].io_ptr,
                 png_ptr[1].mode);
    iVar2._0_1_ = (png_ptr->row_info).color_type;
    iVar2._1_1_ = (png_ptr->row_info).bit_depth;
    iVar2._2_1_ = (png_ptr->row_info).channels;
    iVar2._3_1_ = (png_ptr->row_info).pixel_depth;
    if (iVar2 == 0) {
      png_error(png_ptr,"png_do_dither returned rowbytes=0");
    }
  }
  if ((png_ptr->transformations & 8) != 0) {
    grim_png_do_shift((byte *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1,
                 (byte *)((int)png_ptr[1].jmpbuf + 0x35));
  }
  if ((png_ptr->transformations & 4) != 0) {
    grim_png_do_invert((int *)&(png_ptr->row_info).rowbytes,(int)(png_ptr->sub_row + 1));
  }
  if ((png_ptr->transformations & 1) != 0) {
    grim_png_do_swap((int *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1);
  }
  if ((png_ptr->transformations & 0x8000) != 0) {
    grim_png_do_filler(&(png_ptr->row_info).rowbytes,(int)(png_ptr->sub_row + 1),
                 (uint)*(ushort *)&png_ptr->field_0x11e,(byte)png_ptr->flags);
  }
  if ((png_ptr->transformations & 0x10) != 0) {
    grim_png_do_bgr((int *)&(png_ptr->row_info).rowbytes,png_ptr->sub_row + 1);
  }
  return;
}



/* grim_png_set_gamma @ 10020301 */

void __cdecl grim_png_set_gamma(int param_1,int param_2,double param_3)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) | 1;
    *(float *)(param_2 + 0x28) = (float)param_3;
  }
  return;
}



/* grim_png_set_IHDR @ 1002031c */

void __cdecl
grim_png_set_IHDR(png_structp png_ptr,uint *param_2,uint param_3,uint param_4,char param_5,byte param_6,
            undefined1 param_7,undefined1 param_8,undefined1 param_9)

{
  byte bVar1;
  
  if ((png_ptr != (png_structp)0x0) && (param_2 != (uint *)0x0)) {
    *(undefined1 *)((int)param_2 + 0x1a) = param_8;
    param_2[1] = param_4;
    *(undefined1 *)((int)param_2 + 0x1b) = param_9;
    *param_2 = param_3;
    *(char *)(param_2 + 6) = param_5;
    *(byte *)((int)param_2 + 0x19) = param_6;
    *(undefined1 *)(param_2 + 7) = param_7;
    if ((param_6 == 3) || ((param_6 & 2) == 0)) {
      *(undefined1 *)((int)param_2 + 0x1d) = 1;
    }
    else {
      *(undefined1 *)((int)param_2 + 0x1d) = 3;
    }
    if ((param_6 & 4) != 0) {
      *(char *)((int)param_2 + 0x1d) = *(char *)((int)param_2 + 0x1d) + '\x01';
    }
    bVar1 = *(char *)((int)param_2 + 0x1d) * param_5;
    *(byte *)((int)param_2 + 0x1e) = bVar1;
    if ((uint)(0x7fffffff / (ulonglong)(uint)((int)(bVar1 + 7) >> 3)) < param_3) {
      png_warning(png_ptr,"Width too large to process image data; rowbytes will overflow.");
      param_2[3] = 0;
    }
    else {
      param_2[3] = bVar1 * param_3 + 7 >> 3;
    }
  }
  return;
}



/* grim_png_set_palette @ 100203bd */

void __cdecl grim_png_set_palette(int param_1,int param_2,undefined4 param_3,undefined2 param_4)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) | 8;
    *(undefined4 *)(param_2 + 0x10) = param_3;
    *(undefined2 *)(param_2 + 0x14) = param_4;
  }
  return;
}



/* grim_png_set_sRGB @ 100203e1 */

void __cdecl grim_png_set_sRGB(int param_1,int param_2,undefined1 param_3)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    *(byte *)(param_2 + 9) = *(byte *)(param_2 + 9) | 8;
    *(undefined1 *)(param_2 + 0x2c) = param_3;
  }
  return;
}



/* grim_png_set_sRGB_and_gamma @ 100203fc */

void __cdecl grim_png_set_sRGB_and_gamma(int param_1,int param_2,undefined1 param_3)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    grim_png_set_sRGB(param_1,param_2,param_3);
    grim_png_set_gamma(param_1,param_2,0.45454999804496765);
  }
  return;
}



/* grim_png_set_text @ 10020435 */

void __cdecl grim_png_set_text(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    if (param_3 != 0) {
      *(int *)(param_2 + 0x30) = param_3;
    }
    if (param_5 != (undefined4 *)0x0) {
      *(undefined4 *)(param_2 + 0x34) = *param_5;
      *(undefined4 *)(param_2 + 0x38) = param_5[1];
      *(undefined2 *)(param_2 + 0x3c) = *(undefined2 *)(param_5 + 2);
      if (param_4 == 0) {
        param_4 = 1;
      }
    }
    *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) | 0x10;
    *(undefined2 *)(param_2 + 0x16) = (undefined2)param_4;
  }
  return;
}



/* png_read_data @ 1002047c */

/* png read callback wrapper (errors if NULL) */

void __cdecl png_read_data(png_structp png_ptr,png_bytep data,png_uint_32 length)

{
  if (png_ptr->read_data_fn != (png_rw_ptr)0x0) {
    (*png_ptr->read_data_fn)(png_ptr,data,length);
    return;
  }
  png_error(png_ptr,"Call to NULL read function");
  return;
}



/* grim_png_set_read_fn @ 100204a4 */

void __cdecl grim_png_set_read_fn(png_structp png_ptr,png_voidp param_2,png_rw_ptr param_3)

{
  png_ptr->io_ptr = param_2;
  png_ptr->read_data_fn = param_3;
  if (png_ptr->write_data_fn != (png_rw_ptr)0x0) {
    png_ptr->write_data_fn = (png_rw_ptr)0x0;
    png_warning(png_ptr,"It\'s an error to set both read_data_fn and write_data_fn in the ");
    png_warning(png_ptr,"same structure.  Resetting write_data_fn to NULL.");
  }
  png_ptr[1].jmpbuf[0] = 0;
  return;
}



/* grim_png_check_sig @ 100204e3 */

int __cdecl grim_png_check_sig(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  bool bVar5;
  bool bVar6;
  
  uVar2 = 8;
  if (((param_3 < 9) && (uVar2 = param_3, param_3 == 0)) || (7 < param_2)) {
    return 0;
  }
  if (8 < param_2 + uVar2) {
    uVar2 = 8 - param_2;
  }
  bVar5 = false;
  iVar1 = 0;
  bVar6 = true;
  pbVar3 = (byte *)(param_1 + param_2);
  pbVar4 = &DAT_1004e51c + param_2;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar5 = *pbVar3 < *pbVar4;
    bVar6 = *pbVar3 == *pbVar4;
    pbVar3 = pbVar3 + 1;
    pbVar4 = pbVar4 + 1;
  } while (bVar6);
  if (!bVar6) {
    iVar1 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
  }
  return iVar1;
}



/* grim_png_calloc @ 1002052b */

undefined4 * __cdecl grim_png_calloc(png_structp png_ptr,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  uVar5 = param_2 * param_3;
  puVar1 = png_malloc(png_ptr,uVar5);
  puVar2 = (undefined4 *)0x0;
  if (puVar1 != (undefined4 *)0x0) {
    puVar6 = puVar1;
    if (0x8000 < uVar5) {
      puVar2 = puVar1;
      for (iVar3 = 0x2000; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      }
      uVar5 = uVar5 - 0x8000;
      puVar6 = puVar1 + 0x2000;
    }
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    for (uVar5 = uVar5 & 3; puVar2 = puVar1, uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
  }
  return puVar2;
}



/* png_reset_crc @ 10020583 */

/* reset png CRC state */

void __cdecl png_reset_crc(png_structp png_ptr)

{
  png_colorp ppVar1;
  
  ppVar1 = (png_colorp)grim_crc32(0,(byte *)0x0,0);
  png_ptr->palette = ppVar1;
  return;
}



/* png_calculate_crc @ 1002059b */

/* update png CRC with buffer */

void __cdecl png_calculate_crc(png_structp png_ptr,png_bytep data,png_uint_32 length)

{
  png_colorp ppVar1;
  
  if ((png_ptr->chunk_name[0] & 0x20) == 0) {
    if ((png_ptr->flags & 0x800) != 0) {
      return;
    }
  }
  else if ((png_ptr->flags & 0x300) == 0x300) {
    return;
  }
  ppVar1 = (png_colorp)grim_crc32((uint)png_ptr->palette,data,length);
  png_ptr->palette = ppVar1;
  return;
}



/* grim_png_info_init @ 100205da */

/* [binja] void sub_100205da(int32_t arg1) */

void __cdecl grim_png_info_init(int arg1)

{
  int iVar1;
  undefined4 *in_stack_00000008;
  
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *in_stack_00000008 = 0;
    in_stack_00000008 = in_stack_00000008 + 1;
  }
  return;
}



/* grim_png_create_info_struct @ 100205e8 */

undefined4 * __cdecl grim_png_create_info_struct(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (param_1 != 0) {
    puVar1 = grim_png_memory_alloc(2);
    if (puVar1 != (undefined4 *)0x0) {
      puVar3 = puVar1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
      }
    }
    return puVar1;
  }
  return (undefined4 *)0x0;
}



/* grim_png_memory_alloc @ 100246f2 */

undefined4 * __cdecl grim_png_memory_alloc(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (param_1 == 2) {
    uVar2 = 0x40;
  }
  else {
    if (param_1 != 1) {
      return (undefined4 *)0x0;
    }
    uVar2 = 0x19c;
  }
  puVar1 = malloc(uVar2);
  if (puVar1 != (undefined4 *)0x0) {
    puVar4 = puVar1;
    for (uVar2 = uVar2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar4 = 0;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
  }
  return puVar1;
}



/* png_free_ptr @ 10024734 */

/* free wrapper for png allocations */

void __cdecl png_free_ptr(void *ptr)

{
  if (ptr != (void *)0x0) {
    free(ptr);
    return;
  }
  return;
}



/* png_malloc @ 10024741 */

/* png malloc wrapper (errors on OOM) */

void * __cdecl png_malloc(png_structp png_ptr,png_uint_32 size)

{
  void *pvVar1;
  
  if ((png_ptr != (png_structp)0x0) && (size != 0)) {
    pvVar1 = malloc(size);
    if (pvVar1 == (void *)0x0) {
      png_error(png_ptr,"Out of Memory");
    }
    return pvVar1;
  }
  return (void *)0x0;
}



/* png_free @ 10024777 */

/* png free callback wrapper */

void __cdecl png_free(png_structp png_ptr,void *ptr)

{
  if ((png_ptr != (png_structp)0x0) && (ptr != (void *)0x0)) {
    free(ptr);
  }
  return;
}



/* grim_png_crc_init @ 10024790 */

/* [binja] int32_t sub_10024790(int32_t arg1, int32_t arg2, int32_t arg3) */

int __cdecl grim_png_crc_init(int arg1,int arg2,int arg3)

{
  uint uVar1;
  undefined4 *puVar2;
  uint in_stack_00000010;
  
  puVar2 = (undefined4 *)arg2;
  for (uVar1 = in_stack_00000010 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *(undefined4 *)arg3;
    arg3 = (int)(arg3 + 4);
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = in_stack_00000010 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = *(undefined1 *)arg3;
    arg3 = (int)(arg3 + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  return arg2;
}



/* grim_png_read_chunk_data @ 100247b3 */

/* [binja] int32_t sub_100247b3(int32_t arg1, char arg2, int32_t arg3) */

int __cdecl grim_png_read_chunk_data(int arg1,char arg2,int arg3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined3 in_stack_00000009;
  uint in_stack_00000010;
  
  puVar2 = _arg2;
  for (uVar1 = in_stack_00000010 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = CONCAT22(CONCAT11((undefined1)arg3,(undefined1)arg3),
                       CONCAT11((undefined1)arg3,(undefined1)arg3));
    puVar2 = puVar2 + 1;
  }
  for (uVar1 = in_stack_00000010 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar2 = (undefined1)arg3;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  return (int)_arg2;
}



/* png_get_uint_32 @ 100247e4 */

/* read big-endian 32-bit value */

png_uint_32 __cdecl png_get_uint_32(png_bytep buf)

{
  return CONCAT31(CONCAT21(CONCAT11(*buf,buf[1]),buf[2]),buf[3]);
}



/* png_crc_read @ 10024807 */

/* read PNG chunk data and update CRC */

void __cdecl png_crc_read(png_structp png_ptr,png_bytep buf,png_uint_32 length)

{
  png_read_data(png_ptr,buf,length);
  png_calculate_crc(png_ptr,buf,length);
  return;
}



/* png_crc_error @ 10024821 */

/* read stored CRC and compare with computed */

int __cdecl png_crc_error(png_structp png_ptr)

{
  bool bVar1;
  png_structp ppVar2;
  png_colorp ppVar3;
  uint uVar4;
  
  ppVar2 = png_ptr;
  bVar1 = true;
  if ((png_ptr->chunk_name[0] & 0x20) == 0) {
    if ((png_ptr->flags & 0x800) == 0) goto LAB_1002484d;
  }
  else if ((png_ptr->flags & 0x300) != 0x300) goto LAB_1002484d;
  bVar1 = false;
LAB_1002484d:
  png_read_data(png_ptr,(png_bytep)&png_ptr,4);
  if (bVar1) {
    ppVar3 = (png_colorp)png_get_uint_32((png_bytep)&png_ptr);
    uVar4 = (uint)(ppVar3 != ppVar2->palette);
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



/* png_check_chunk_name @ 1002487f */

/* validate PNG chunk type characters */

void __cdecl png_check_chunk_name(png_structp png_ptr,png_bytep chunk_name)

{
  byte bVar1;
  
  bVar1 = *chunk_name;
  if (((((((bVar1 < 0x29) || (0x7a < bVar1)) || ((0x5a < bVar1 && (bVar1 < 0x61)))) ||
        ((bVar1 = chunk_name[1], bVar1 < 0x29 || (0x7a < bVar1)))) ||
       ((0x5a < bVar1 && (bVar1 < 0x61)))) ||
      ((((bVar1 = chunk_name[2], bVar1 < 0x29 || (0x7a < bVar1)) ||
        ((0x5a < bVar1 && (bVar1 < 0x61)))) ||
       ((bVar1 = chunk_name[3], bVar1 < 0x29 || (0x7a < bVar1)))))) ||
     ((0x5a < bVar1 && (bVar1 < 0x61)))) {
    grim_png_error_raise(png_ptr,(undefined4 *)"invalid chunk type");
  }
  return;
}



/* grim_png_unfilter_row @ 100248e1 */

void __cdecl grim_png_unfilter_row(int param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint local_c;
  byte local_5;
  
  bVar1 = *(byte *)(param_1 + 0xfb);
  uVar3 = (uint)bVar1;
  if (param_3 == 0xff) {
    uVar3 = uVar3 * *(int *)(param_1 + 0xb8) + 7;
    pbVar5 = (byte *)(*(int *)(param_1 + 0xdc) + 1);
    for (uVar4 = uVar3 >> 5; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)param_2 = *(undefined4 *)pbVar5;
      pbVar5 = pbVar5 + 4;
      param_2 = param_2 + 4;
    }
    for (uVar3 = uVar3 >> 3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *param_2 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      param_2 = param_2 + 1;
    }
  }
  else if (uVar3 == 1) {
    iVar2 = *(int *)(param_1 + 0xb8);
    pbVar5 = (byte *)(*(int *)(param_1 + 0xdc) + 1);
    local_c = 0x80;
    iVar6 = 7;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      if ((local_c & param_3) != 0) {
        bVar1 = (byte)iVar6;
        *param_2 = (byte)(0x7f7f >> (7 - bVar1 & 0x1f)) & *param_2 |
                   (*pbVar5 >> (bVar1 & 0x1f) & 1) << (bVar1 & 0x1f);
      }
      if (iVar6 == 0) {
        pbVar5 = pbVar5 + 1;
        iVar6 = 7;
        param_2 = param_2 + 1;
      }
      else {
        iVar6 = iVar6 + -1;
      }
      if (local_c == 1) {
        local_c = 0x80;
      }
      else {
        local_c = (int)local_c >> 1;
      }
    }
  }
  else if (uVar3 == 2) {
    iVar2 = *(int *)(param_1 + 0xb8);
    pbVar5 = (byte *)(*(int *)(param_1 + 0xdc) + 1);
    local_c = 0x80;
    iVar6 = 6;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      if ((local_c & param_3) != 0) {
        bVar1 = (byte)iVar6;
        *param_2 = (byte)(0x3f3f >> (6 - bVar1 & 0x1f)) & *param_2 |
                   (*pbVar5 >> (bVar1 & 0x1f) & 3) << (bVar1 & 0x1f);
      }
      if (iVar6 == 0) {
        pbVar5 = pbVar5 + 1;
        iVar6 = 6;
        param_2 = param_2 + 1;
      }
      else {
        iVar6 = iVar6 + -2;
      }
      if (local_c == 1) {
        local_c = 0x80;
      }
      else {
        local_c = (int)local_c >> 1;
      }
    }
  }
  else if (uVar3 == 4) {
    iVar2 = *(int *)(param_1 + 0xb8);
    pbVar5 = (byte *)(*(int *)(param_1 + 0xdc) + 1);
    local_c = 0x80;
    iVar6 = 4;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      if ((local_c & param_3) != 0) {
        bVar1 = (byte)iVar6;
        *param_2 = (byte)(0xf0f >> (4 - bVar1 & 0x1f)) & *param_2 |
                   (*pbVar5 >> (bVar1 & 0x1f) & 0xf) << (bVar1 & 0x1f);
      }
      if (iVar6 == 0) {
        pbVar5 = pbVar5 + 1;
        iVar6 = 4;
        param_2 = param_2 + 1;
      }
      else {
        iVar6 = iVar6 + -4;
      }
      if (local_c == 1) {
        local_c = 0x80;
      }
      else {
        local_c = (int)local_c >> 1;
      }
    }
  }
  else {
    iVar2 = *(int *)(param_1 + 0xb8);
    uVar3 = (uint)(bVar1 >> 3);
    pbVar5 = (byte *)(*(int *)(param_1 + 0xdc) + 1);
    local_5 = 0x80;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      if ((local_5 & (byte)param_3) != 0) {
        pbVar7 = pbVar5;
        pbVar8 = param_2;
        for (uVar4 = (uint)(bVar1 >> 5); uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pbVar8 = *(undefined4 *)pbVar7;
          pbVar7 = pbVar7 + 4;
          pbVar8 = pbVar8 + 4;
        }
        for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pbVar8 = *pbVar7;
          pbVar7 = pbVar7 + 1;
          pbVar8 = pbVar8 + 1;
        }
      }
      pbVar5 = pbVar5 + uVar3;
      param_2 = param_2 + uVar3;
      if (local_5 == 1) {
        local_5 = 0x80;
      }
      else {
        local_5 = local_5 >> 1;
      }
    }
  }
  return;
}



/* grim_png_deinterlace_row @ 10024af7 */

void __cdecl grim_png_deinterlace_row(uint *param_1,int *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  byte *pbVar9;
  byte *pbVar10;
  int local_1c [4];
  uint local_c;
  uint local_8;
  
  if ((param_2 != (int *)0x0) && (param_1 != (uint *)0x0)) {
    local_1c[3] = *(int *)(&DAT_1004eaac + param_3 * 4);
    uVar4 = *param_1;
    uVar5 = uVar4 * local_1c[3];
    bVar1 = *(byte *)((int)param_1 + 0xb);
    if (bVar1 == 1) {
      local_1c[2] = 0;
      pbVar10 = (byte *)((uVar4 - 1 >> 3) + (int)param_2);
      pbVar9 = (byte *)((uVar5 - 1 >> 3) + (int)param_2);
      local_c = 7 - (uVar4 - 1 & 7);
      local_8 = 7 - (uVar5 - 1 & 7);
      if (uVar4 != 0) {
        do {
          bVar1 = *pbVar10;
          local_1c[1] = local_1c[3];
          if (0 < local_1c[3]) {
            do {
              *pbVar9 = (byte)(0x7f7f >> (7 - (byte)local_8 & 0x1f)) & *pbVar9 |
                        (bVar1 >> ((byte)local_c & 0x1f) & 1) << ((byte)local_8 & 0x1f);
              if (local_8 == 7) {
                local_8 = 0;
                pbVar9 = pbVar9 + -1;
              }
              else {
                local_8 = local_8 + 1;
              }
              local_1c[1] = local_1c[1] + -1;
            } while (local_1c[1] != 0);
          }
          if (local_c == 7) {
            local_c = 0;
            pbVar10 = pbVar10 + -1;
          }
          else {
            local_c = local_c + 1;
          }
          local_1c[2] = local_1c[2] + 1;
        } while ((uint)local_1c[2] < *param_1);
      }
    }
    else if (bVar1 == 2) {
      local_1c[2] = 0;
      pbVar10 = (byte *)((uVar4 - 1 >> 2) + (int)param_2);
      pbVar9 = (byte *)((uVar5 - 1 >> 2) + (int)param_2);
      local_c = (3 - (uVar4 - 1 & 3)) * 2;
      local_8 = (3 - (uVar5 - 1 & 3)) * 2;
      if (uVar4 != 0) {
        do {
          bVar1 = *pbVar10;
          local_1c[1] = local_1c[3];
          if (0 < local_1c[3]) {
            do {
              *pbVar9 = (byte)(0x3f3f >> (6 - (byte)local_8 & 0x1f)) & *pbVar9 |
                        (bVar1 >> ((byte)local_c & 0x1f) & 3) << ((byte)local_8 & 0x1f);
              if (local_8 == 6) {
                local_8 = 0;
                pbVar9 = pbVar9 + -1;
              }
              else {
                local_8 = local_8 + 2;
              }
              local_1c[1] = local_1c[1] + -1;
            } while (local_1c[1] != 0);
          }
          if (local_c == 6) {
            local_c = 0;
            pbVar10 = pbVar10 + -1;
          }
          else {
            local_c = local_c + 2;
          }
          local_1c[2] = local_1c[2] + 1;
        } while ((uint)local_1c[2] < *param_1);
      }
    }
    else if (bVar1 == 4) {
      local_1c[2] = 0;
      pbVar10 = (byte *)((uVar4 - 1 >> 1) + (int)param_2);
      pbVar9 = (byte *)((uVar5 - 1 >> 1) + (int)param_2);
      local_c = (uVar4 - 1 & 1) * -4 + 4;
      local_8 = (uVar5 - 1 & 1) * -4 + 4;
      if (uVar4 != 0) {
        do {
          bVar1 = *pbVar10;
          local_1c[1] = local_1c[3];
          if (0 < local_1c[3]) {
            do {
              *pbVar9 = (byte)(0xf0f >> (4 - (byte)local_8 & 0x1f)) & *pbVar9 |
                        (bVar1 >> ((byte)local_c & 0x1f) & 0xf) << ((byte)local_8 & 0x1f);
              if (local_8 == 4) {
                local_8 = 0;
                pbVar9 = pbVar9 + -1;
              }
              else {
                local_8 = local_8 + 4;
              }
              local_1c[1] = local_1c[1] + -1;
            } while (local_1c[1] != 0);
          }
          if (local_c == 4) {
            local_c = 0;
            pbVar10 = pbVar10 + -1;
          }
          else {
            local_c = local_c + 4;
          }
          local_1c[2] = local_1c[2] + 1;
        } while ((uint)local_1c[2] < *param_1);
      }
    }
    else {
      local_8 = 0;
      local_c = (uint)(bVar1 >> 3);
      piVar6 = (int *)((uVar4 - 1) * local_c + (int)param_2);
      param_2 = (int *)((uVar5 - 1) * local_c + (int)param_2);
      if (uVar4 != 0) {
        do {
          uVar4 = local_c;
          piVar7 = piVar6;
          piVar8 = local_1c;
          for (uVar3 = local_c >> 2; iVar2 = local_1c[3], uVar3 != 0; uVar3 = uVar3 - 1) {
            *piVar8 = *piVar7;
            piVar7 = piVar7 + 1;
            piVar8 = piVar8 + 1;
          }
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *(char *)piVar8 = (char)*piVar7;
            piVar7 = (int *)((int)piVar7 + 1);
            piVar8 = (int *)((int)piVar8 + 1);
          }
          if (0 < iVar2) {
            local_1c[2] = iVar2;
            do {
              piVar7 = (int *)((int)param_2 - local_c);
              piVar8 = local_1c;
              for (uVar4 = local_c >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                *param_2 = *piVar8;
                piVar8 = piVar8 + 1;
                param_2 = param_2 + 1;
              }
              local_1c[2] = local_1c[2] + -1;
              for (uVar4 = local_c & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *(char *)param_2 = (char)*piVar8;
                piVar8 = (int *)((int)piVar8 + 1);
                param_2 = (int *)((int)param_2 + 1);
              }
              param_2 = piVar7;
            } while (local_1c[2] != 0);
          }
          piVar6 = (int *)((int)piVar6 - local_c);
          local_8 = local_8 + 1;
        } while (local_8 < *param_1);
      }
    }
    *param_1 = uVar5;
    param_1[1] = *(byte *)((int)param_1 + 0xb) * uVar5 + 7 >> 3;
  }
  return;
}



/* grim_png_process_idat @ 10024dc0 */

void __cdecl grim_png_process_idat(png_structp png_ptr,int param_2,byte *param_3,byte *param_4,int param_5)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  int local_c;
  
  if (param_5 != 0) {
    if (param_5 == 1) {
      uVar4 = (int)(*(byte *)(param_2 + 0xb) + 7) >> 3;
      pbVar8 = param_3 + uVar4;
      if (uVar4 < *(uint *)(param_2 + 4)) {
        pbVar11 = pbVar8 + -uVar4;
        iVar6 = *(uint *)(param_2 + 4) - uVar4;
        do {
          *pbVar8 = *pbVar8 + *pbVar11;
          pbVar8 = pbVar8 + 1;
          pbVar11 = pbVar11 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
    }
    else if (param_5 == 2) {
      uVar4 = *(uint *)(param_2 + 4);
      uVar7 = 0;
      if (uVar4 != 0) {
        do {
          *param_3 = *param_3 + param_4[uVar7];
          param_3 = param_3 + 1;
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar4);
      }
    }
    else if (param_5 == 3) {
      iVar6 = (int)(*(byte *)(param_2 + 0xb) + 7) >> 3;
      iVar3 = *(int *)(param_2 + 4) - iVar6;
      pbVar8 = param_3;
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pbVar8 = *pbVar8 + (*param_4 >> 1);
        param_4 = param_4 + 1;
        pbVar8 = pbVar8 + 1;
      }
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pbVar8 = *pbVar8 + (char)(((uint)*param_3 + (uint)*param_4) / 2);
        param_3 = param_3 + 1;
        param_4 = param_4 + 1;
        pbVar8 = pbVar8 + 1;
      }
    }
    else if (param_5 == 4) {
      iVar3 = (int)(*(byte *)(param_2 + 0xb) + 7) >> 3;
      iVar6 = *(int *)(param_2 + 4) - iVar3;
      pbVar8 = param_3;
      pbVar11 = param_4;
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        *pbVar8 = *pbVar8 + *pbVar11;
        pbVar11 = pbVar11 + 1;
        pbVar8 = pbVar8 + 1;
      }
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        bVar5 = *param_3;
        bVar1 = *pbVar11;
        bVar2 = *param_4;
        param_3 = param_3 + 1;
        pbVar11 = pbVar11 + 1;
        param_4 = param_4 + 1;
        iVar3 = (uint)bVar1 - (uint)bVar2;
        iVar9 = (uint)bVar5 - (uint)bVar2;
        local_c = iVar3;
        if (iVar3 < 0) {
          local_c = -iVar3;
        }
        iVar10 = iVar9;
        if (iVar9 < 0) {
          iVar10 = -iVar9;
        }
        iVar3 = iVar3 + iVar9;
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        if (((iVar10 < local_c) || (iVar3 < local_c)) && (bVar5 = bVar1, iVar3 < iVar10)) {
          bVar5 = bVar2;
        }
        *pbVar8 = *pbVar8 + bVar5;
        pbVar8 = pbVar8 + 1;
      }
    }
    else {
      png_warning(png_ptr,"Ignoring bad adaptive filter type");
      *param_3 = 0;
    }
  }
  return;
}



/* grim_png_read_start @ 10024f3b */

void __cdecl grim_png_read_start(png_structp png_ptr)

{
  png_byte pVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  png_bytep ppVar5;
  png_uint_32 pVar6;
  
  (png_ptr->zstream).words[1] = 0;
  grim_png_apply_gamma_palette(png_ptr);
  uVar3 = png_ptr->height;
  if (png_ptr->interlaced == '\0') {
    pVar6 = png_ptr->width;
    png_ptr->num_rows = uVar3;
    png_ptr->row_number = pVar6;
    png_ptr->iwidth = png_ptr->rowbytes + 1;
  }
  else {
    if ((png_ptr->transformations & 2) == 0) {
      uVar3 = uVar3 + 7 >> 3;
    }
    pVar6 = png_ptr->width;
    png_ptr->num_rows = uVar3;
    iVar4 = (uint)png_ptr->pass * 4;
    uVar3 = ((pVar6 - *(int *)(&DAT_1004ea90 + iVar4)) + -1 + *(uint *)(&DAT_1004eaac + iVar4)) /
            *(uint *)(&DAT_1004eaac + iVar4);
    png_ptr->row_number = uVar3;
    png_ptr->iwidth = (png_ptr->pixel_depth * uVar3 + 7 >> 3) + 1;
  }
  uVar3 = (uint)png_ptr->pixel_depth;
  uVar2 = png_ptr->transformations;
  if (((uVar2 & 4) != 0) && (png_ptr->bit_depth < 8)) {
    uVar3 = 8;
  }
  if ((uVar2 & 0x1000) != 0) {
    pVar1 = png_ptr->color_type;
    if (pVar1 == '\x03') {
      uVar3 = (uint)(*(short *)((int)&png_ptr->chunk_name_pad + 2) != 0) * 8 + 0x18;
    }
    else if (pVar1 == '\0') {
      if (uVar3 < 8) {
        uVar3 = 8;
      }
      if (*(short *)((int)&png_ptr->chunk_name_pad + 2) != 0) {
        uVar3 = uVar3 * 2;
      }
    }
    else if ((pVar1 == '\x02') && (*(short *)((int)&png_ptr->chunk_name_pad + 2) != 0)) {
      uVar3 = (uVar3 << 2) / 3;
    }
  }
  if ((char)(uVar2 >> 8) < '\0') {
    pVar1 = png_ptr->color_type;
    if (pVar1 == '\x03') {
      uVar3 = 0x20;
    }
    else if (pVar1 == '\0') {
      uVar3 = ((8 < uVar3) - 1 & 0xfffffff0) + 0x20;
    }
    else if (pVar1 == '\x02') {
      uVar3 = ((0x20 < uVar3) - 1 & 0xffffffe0) + 0x40;
    }
  }
  ppVar5 = png_malloc(png_ptr,((pVar6 + 7 & 0xfffffff8) * uVar3 + 7 >> 3) + 1 +
                              ((int)(uVar3 + 7) >> 3));
  png_ptr->sub_row = ppVar5;
  ppVar5 = png_malloc(png_ptr,png_ptr->rowbytes + 1);
  png_ptr->row_buf = ppVar5;
  grim_png_read_chunk_data((int)png_ptr,(char)ppVar5,0);
  png_ptr->flags = png_ptr->flags | 0x40;
  return;
}



/* png_crc_finish @ 100250d7 */

/* read remaining chunk bytes and check CRC */

int __cdecl png_crc_finish(png_structp png_ptr,png_uint_32 skip)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  
  uVar1 = png_ptr->zbuf_size;
  for (; uVar1 < skip; skip = skip - uVar1) {
    png_crc_read(png_ptr,png_ptr->zbuf,png_ptr->zbuf_size);
  }
  if (skip != 0) {
    png_crc_read(png_ptr,png_ptr->zbuf,skip);
  }
  iVar3 = png_crc_error(png_ptr);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    bVar2 = png_ptr->chunk_name[0] & 0x20;
    if (((bVar2 == 0) || ((png_ptr->flags & 0x200) != 0)) &&
       ((bVar2 != 0 || ((png_ptr->flags & 0x400) == 0)))) {
      grim_png_error_raise(png_ptr,(undefined4 *)"CRC error");
    }
    else {
      grim_png_create_read_struct_full(png_ptr,(undefined4 *)"CRC error");
    }
    iVar3 = 1;
  }
  return iVar3;
}



/* grim_png_read_IHDR @ 10025163 */

void __cdecl grim_png_read_IHDR(png_structp png_ptr,uint *param_2,int param_3)

{
  byte bVar1;
  png_uint_32 pVar2;
  png_uint_32 pVar3;
  png_byte local_20 [4];
  png_byte local_1c [4];
  byte local_18;
  byte local_17;
  byte local_16;
  byte local_15;
  byte local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  if (png_ptr->mode != 0) {
    png_error(png_ptr,"Out of place IHDR");
  }
  if (param_3 != 0xd) {
    png_error(png_ptr,"Invalid IHDR chunk");
  }
  png_ptr->mode = png_ptr->mode | 1;
  png_crc_read(png_ptr,local_20,0xd);
  png_crc_finish(png_ptr,0);
  pVar2 = png_get_uint_32(local_20);
  pVar3 = png_get_uint_32(local_1c);
  local_10 = (uint)local_16;
  local_c = (uint)local_15;
  local_8 = (uint)local_14;
  if ((((pVar2 == 0) || (0x7fffffff < pVar2)) || (pVar3 == 0)) || (0x7fffffff < pVar3)) {
    png_error(png_ptr,"Invalid image size in IHDR");
  }
  if (((local_18 != 1) && (local_18 != 2)) &&
     ((local_18 != 4 && ((local_18 != 8 && (local_18 != 0x10)))))) {
    png_error(png_ptr,"Invalid bit depth in IHDR");
  }
  if (((local_17 == 1) || (local_17 == 5)) || (6 < local_17)) {
    png_error(png_ptr,"Invalid color type in IHDR");
  }
  if (((local_17 == 3) && (8 < local_18)) ||
     (((local_17 == 2 || ((local_17 == 4 || (local_17 == 6)))) && (local_18 < 8)))) {
    png_error(png_ptr,"Invalid color type/bit depth combination in IHDR");
  }
  if (1 < (int)local_8) {
    png_error(png_ptr,"Unknown interlace method in IHDR");
  }
  if (local_10 != 0) {
    png_error(png_ptr,"Unknown compression method in IHDR");
  }
  if (local_c != 0) {
    png_error(png_ptr,"Unknown filter method in IHDR");
  }
  png_ptr->interlaced = (png_byte)local_8;
  png_ptr->width = pVar2;
  png_ptr->height = pVar3;
  png_ptr->bit_depth = local_18;
  png_ptr->color_type = local_17;
  if (local_17 != 0) {
    if (local_17 == 2) {
      png_ptr->channels = '\x03';
      goto LAB_1002531b;
    }
    if (local_17 != 3) {
      if (local_17 == 4) {
        png_ptr->channels = '\x02';
      }
      else if (local_17 == 6) {
        png_ptr->channels = '\x04';
      }
      goto LAB_1002531b;
    }
  }
  png_ptr->channels = '\x01';
LAB_1002531b:
  bVar1 = png_ptr->channels * local_18;
  png_ptr->pixel_depth = bVar1;
  png_ptr->rowbytes = bVar1 * pVar2 + 7 >> 3;
  grim_png_set_IHDR(png_ptr,param_2,pVar2,pVar3,local_18,local_17,(png_byte)local_8,(char)local_10,
               (char)local_c);
  return;
}



/* grim_png_read_PLTE @ 10025359 */

void __thiscall grim_png_read_PLTE(void *this,png_structp png_ptr,int param_2,uint param_3)

{
  byte *pbVar1;
  ushort *puVar2;
  uint uVar3;
  png_structp png_ptr_00;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  png_structp unaff_ESI;
  undefined1 *puVar7;
  char *pcVar8;
  int local_8;
  
  png_ptr_00 = png_ptr;
  uVar3 = png_ptr->mode;
  if ((uVar3 & 1) == 0) {
    pcVar8 = "Missing IHDR before PLTE";
LAB_10025385:
    png_error(png_ptr,pcVar8);
LAB_1002538d:
    png_ptr_00->mode = png_ptr_00->mode | 2;
    if (param_3 % 3 != 0) {
      pcVar8 = "Invalid palette chunk";
      unaff_ESI = png_ptr_00;
      if (png_ptr_00->color_type != '\x03') goto LAB_100253ad;
      png_error(png_ptr_00,"Invalid palette chunk");
    }
    iVar5 = (int)param_3 / 3;
    puVar6 = grim_png_calloc(png_ptr_00,iVar5,3);
    pbVar1 = (byte *)((int)&png_ptr_00->flags + 1);
    *pbVar1 = *pbVar1 | 0x10;
    if (0 < iVar5) {
      puVar7 = (undefined1 *)((int)puVar6 + 2);
      local_8 = iVar5;
      do {
        png_crc_read(png_ptr_00,(png_bytep)&png_ptr,3);
        puVar7[-2] = png_ptr._0_1_;
        puVar7[-1] = png_ptr._1_1_;
        *puVar7 = png_ptr._2_1_;
        puVar7 = puVar7 + 3;
        local_8 = local_8 + -1;
      } while (local_8 != 0);
    }
    png_crc_finish(png_ptr_00,0);
    iVar4 = param_2;
    *(undefined4 **)&png_ptr_00->num_palette = puVar6;
    *(short *)&png_ptr_00->chunk_name_pad = (short)iVar5;
    grim_png_set_palette((int)png_ptr_00,param_2,puVar6,(short)iVar5);
    if ((((png_ptr_00->color_type == '\x03') && (iVar4 != 0)) &&
        ((*(byte *)(iVar4 + 8) & 0x10) != 0)) &&
       (puVar2 = (ushort *)((int)&png_ptr_00->chunk_name_pad + 2),
       (ushort)png_ptr_00->chunk_name_pad < *puVar2)) {
      png_warning(png_ptr_00,"Truncating incorrect tRNS chunk length");
      *puVar2 = (ushort)png_ptr_00->chunk_name_pad;
    }
  }
  else {
    pcVar8 = this;
    if ((uVar3 & 4) == 0) {
      if ((uVar3 & 2) != 0) {
        pcVar8 = "Duplicate PLTE chunk";
        goto LAB_10025385;
      }
      goto LAB_1002538d;
    }
LAB_100253ad:
    png_warning(unaff_ESI,pcVar8);
    png_crc_finish(png_ptr_00,param_3);
  }
  return;
}



/* grim_png_handle_unknown_chunk @ 10025483 */

void __cdecl
grim_png_handle_unknown_chunk(png_structp png_ptr,undefined4 param_2,undefined4 param_3,int param_4,uint param_5)

{
  if ((((png_ptr->mode & 1) == 0) || ((png_ptr->mode & 4) == 0)) &&
     (png_error(png_ptr,"No image in file"), param_4 == 0)) {
    return;
  }
  png_ptr->mode = png_ptr->mode | 0x18;
  if (param_5 != 0) {
    png_warning(png_ptr,"Incorrect IEND chunk length");
  }
  png_crc_finish(png_ptr,param_5);
  return;
}



/* grim_png_handle_gama_chunk @ 100254cd */

void __cdecl grim_png_handle_gama_chunk(png_structp png_ptr,int param_2,uint param_3)

{
  uint uVar1;
  float fVar2;
  png_structp png_ptr_00;
  int iVar3;
  int iVar4;
  png_uint_32 pVar5;
  char *msg;
  
  iVar3 = param_2;
  png_ptr_00 = png_ptr;
  uVar1 = png_ptr->mode;
  if ((uVar1 & 1) == 0) {
    png_error(png_ptr,"Missing IHDR before gAMA");
  }
  else {
    if ((uVar1 & 4) != 0) {
      msg = "Invalid gAMA after IDAT";
      goto LAB_100254fe;
    }
    if ((uVar1 & 2) == 0) {
      if (((param_2 != 0) && ((*(uint *)(param_2 + 8) & 1) != 0)) &&
         ((*(uint *)(param_2 + 8) & 0x800) == 0)) {
        msg = "Duplicate gAMA chunk";
        goto LAB_100254fe;
      }
    }
    else {
      png_warning(png_ptr,"Out of place gAMA chunk");
    }
  }
  if (param_3 == 4) {
    png_crc_read(png_ptr_00,(png_bytep)&png_ptr,4);
    iVar4 = png_crc_finish(png_ptr_00,0);
    if (iVar4 != 0) {
      return;
    }
    pVar5 = png_get_uint_32((png_bytep)&png_ptr);
    if (pVar5 == 0) {
      return;
    }
    if ((*(uint *)(iVar3 + 8) & 0x800) != 0) {
      fVar2 = (float)(int)pVar5;
      if ((int)pVar5 < 0) {
        fVar2 = fVar2 + 4.2949673e+09;
      }
      if (500.0 < ABS(fVar2 - 45455.0)) {
        png_warning(png_ptr_00,"Ignoring incorrect gAMA value when sRGB is also present");
        return;
      }
    }
    fVar2 = (float)(int)pVar5;
    if ((int)pVar5 < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    png_ptr_00[1].jmpbuf[4] = (png_uint_32)(fVar2 * 1e-05);
    grim_png_set_gamma((int)png_ptr_00,iVar3,(double)(fVar2 * 1e-05));
    return;
  }
  msg = "Incorrect gAMA chunk length";
LAB_100254fe:
  png_warning(png_ptr_00,msg);
  png_crc_finish(png_ptr_00,param_3);
  return;
}



/* grim_png_handle_srgb_chunk @ 100255d8 */

void __cdecl grim_png_handle_srgb_chunk(png_structp png_ptr,int param_2,uint param_3)

{
  uint uVar1;
  png_structp png_ptr_00;
  byte bVar2;
  int iVar3;
  char *msg;
  
  png_ptr_00 = png_ptr;
  uVar1 = png_ptr->mode;
  if ((uVar1 & 1) == 0) {
    png_error(png_ptr,"Missing IHDR before sRGB");
  }
  else {
    if ((uVar1 & 4) != 0) {
      msg = "Invalid sRGB after IDAT";
      goto LAB_100255fe;
    }
    if ((uVar1 & 2) == 0) {
      if ((param_2 != 0) && ((*(byte *)(param_2 + 9) & 8) != 0)) {
        msg = "Duplicate sRGB chunk";
        goto LAB_100255fe;
      }
    }
    else {
      png_warning(png_ptr,"Out of place sRGB chunk");
    }
  }
  if (param_3 == 1) {
    png_crc_read(png_ptr_00,(png_bytep)((int)&png_ptr + 3),1);
    iVar3 = png_crc_finish(png_ptr_00,0);
    if (iVar3 != 0) {
      return;
    }
    bVar2 = png_ptr._3_1_;
    if (3 < png_ptr._3_1_) {
      png_warning(png_ptr_00,"Unknown sRGB intent");
      return;
    }
    if (((*(byte *)(param_2 + 8) & 1) != 0) &&
       (500.0 < ABS(((float)png_ptr_00[1].jmpbuf[4] * 100000.0 + 0.5) - 45455.0))) {
      png_warning(png_ptr_00,"Ignoring incorrect gAMA value when sRGB is also present");
    }
    grim_png_set_sRGB_and_gamma((int)png_ptr_00,param_2,bVar2);
    return;
  }
  msg = "Incorrect sRGB chunk length";
LAB_100255fe:
  png_warning(png_ptr_00,msg);
  png_crc_finish(png_ptr_00,param_3);
  return;
}



/* grim_png_handle_text_chunk @ 100256c7 */

void __cdecl grim_png_handle_text_chunk(png_structp png_ptr,int param_2,uint param_3)

{
  byte *pbVar1;
  png_byte pVar2;
  png_bytep buf;
  int iVar3;
  char *pcVar4;
  undefined4 local_c;
  ushort local_8;
  
  if ((png_ptr->mode & 1) == 0) {
    png_error(png_ptr,"Missing IHDR before tRNS");
  }
  else {
    if ((png_ptr->mode & 4) != 0) {
      pcVar4 = "Invalid tRNS after IDAT";
LAB_1002573c:
      png_warning(png_ptr,pcVar4);
      png_crc_finish(png_ptr,param_3);
      return;
    }
    if ((param_2 != 0) && ((*(byte *)(param_2 + 8) & 0x10) != 0)) {
      pcVar4 = "Duplicate tRNS chunk";
      goto LAB_1002573c;
    }
  }
  pVar2 = png_ptr->color_type;
  if (pVar2 == '\x03') {
    if ((png_ptr->mode & 2) == 0) {
      png_warning(png_ptr,"Missing PLTE before tRNS");
LAB_1002570d:
      if (param_3 != 0) {
        buf = png_malloc(png_ptr,param_3);
        pbVar1 = (byte *)((int)&png_ptr->flags + 1);
        *pbVar1 = *pbVar1 | 0x20;
        png_ptr[1].jmpbuf[0xf] = (png_uint_32)buf;
        png_crc_read(png_ptr,buf,param_3);
        *(short *)((int)&png_ptr->chunk_name_pad + 2) = (short)param_3;
        goto LAB_10025833;
      }
      png_warning(png_ptr,"Zero length tRNS chunk");
    }
    else {
      if (param_3 <= (ushort)png_ptr->chunk_name_pad) goto LAB_1002570d;
      png_warning(png_ptr,"Incorrect tRNS chunk length");
    }
LAB_10025870:
    png_crc_finish(png_ptr,param_3);
  }
  else {
    if (pVar2 == '\x02') {
      if (param_3 != 6) {
LAB_100257fe:
        pcVar4 = "Incorrect tRNS chunk length";
LAB_10025867:
        png_warning(png_ptr,pcVar4);
        goto LAB_10025870;
      }
      png_crc_read(png_ptr,(png_bytep)&local_c,6);
      *(short *)((int)&png_ptr[1].error_fn + 2) =
           (short)((local_c & 0xff) * 0x100 + (local_c >> 8 & 0xff));
      *(ushort *)&png_ptr[1].warning_fn = (ushort)local_c._2_1_ * 0x100 + (ushort)local_c._3_1_;
      *(ushort *)((int)&png_ptr[1].warning_fn + 2) = local_8 * 0x100 + (local_8 >> 8);
    }
    else {
      if (pVar2 != '\0') {
        pcVar4 = "tRNS chunk not allowed with alpha channel";
        goto LAB_10025867;
      }
      if (param_3 != 2) goto LAB_100257fe;
      png_crc_read(png_ptr,(png_bytep)&local_c,2);
      *(ushort *)&png_ptr[1].error_ptr = (ushort)local_c * 0x100 + ((ushort)local_c >> 8);
    }
    *(undefined2 *)((int)&png_ptr->chunk_name_pad + 2) = 1;
LAB_10025833:
    iVar3 = png_crc_finish(png_ptr,0);
    if (iVar3 == 0) {
      grim_png_set_text((int)png_ptr,param_2,png_ptr[1].jmpbuf[0xf],
                   (uint)*(ushort *)((int)&png_ptr->chunk_name_pad + 2),&png_ptr[1].error_fn);
    }
  }
  return;
}



/* grim_png_read_chunk_generic @ 1002587e */

void __cdecl grim_png_read_chunk_generic(png_structp png_ptr,int param_2,uint param_3)

{
  png_check_chunk_name(png_ptr,png_ptr->chunk_name);
  if (((png_ptr->chunk_name[0] & 0x20) == 0) &&
     (grim_png_error_raise(png_ptr,(undefined4 *)"unknown critical chunk"), param_2 == 0)) {
    return;
  }
  if ((png_ptr->mode & 4) != 0) {
    png_ptr->mode = png_ptr->mode | 8;
  }
  png_crc_finish(png_ptr,param_3);
  return;
}



/* grim_png_handle_idat_chunk @ 100258c8 */

void __thiscall grim_png_handle_idat_chunk(void *this,int *param_1)

{
  uint *puVar1;
  byte bVar2;
  uint uVar3;
  png_bytep buf;
  int *png_ptr;
  uint uVar4;
  png_uint_32 pVar5;
  char *msg;
  int iVar6;
  void *local_4;
  
  png_ptr = param_1;
  puVar1 = (uint *)(param_1 + 0x35);
  *puVar1 = *puVar1 + 1;
  if ((uint)param_1[0x30] <= *puVar1) {
    local_4 = this;
    if (*(char *)((int)param_1 + 0x113) != '\0') {
      *puVar1 = 0;
      grim_png_read_chunk_data((int)param_1,(char)param_1[0x36],0);
      do {
        *(char *)(png_ptr + 0x45) = (char)png_ptr[0x45] + '\x01';
        bVar2 = *(byte *)(png_ptr + 0x45);
        if (6 < bVar2) goto LAB_10025995;
        iVar6 = (uint)bVar2 * 4;
        uVar4 = ((png_ptr[0x2e] - *(int *)(&DAT_1004ea90 + iVar6)) + -1 +
                *(uint *)(&DAT_1004eaac + iVar6)) / *(uint *)(&DAT_1004eaac + iVar6);
        png_ptr[0x34] = uVar4;
        png_ptr[0x33] = (*(byte *)((int)png_ptr + 0x119) * uVar4 + 7 >> 3) + 1;
      } while (((*(byte *)(png_ptr + 0x18) & 2) == 0) &&
              (png_ptr[0x30] =
                    ((png_ptr[0x2f] - *(int *)(&DAT_1004eac8 + iVar6)) + -1 +
                    *(uint *)(&DAT_1004eae4 + iVar6)) / *(uint *)(&DAT_1004eae4 + iVar6),
              png_ptr[0x34] == 0));
      if (bVar2 < 7) {
        return;
      }
    }
LAB_10025995:
    if ((*(byte *)(png_ptr + 0x17) & 0x20) == 0) {
      png_ptr[0x1c] = (int)&param_1;
      png_ptr[0x1d] = 1;
      while( true ) {
        if (png_ptr[0x1a] == 0) {
          if (png_ptr[0x3f] == 0) {
            do {
              png_crc_finish((png_structp)png_ptr,0);
              png_read_data((png_structp)png_ptr,(png_bytep)&local_4,4);
              pVar5 = png_get_uint_32((png_bytep)&local_4);
              png_ptr[0x3f] = pVar5;
              png_reset_crc((png_structp)png_ptr);
              png_crc_read((png_structp)png_ptr,(png_bytep)(png_ptr + 0x43),4);
              if (png_ptr[0x43] != 0x54414449) {
                png_error((png_structp)png_ptr,"Not enough image data");
              }
            } while (png_ptr[0x3f] == 0);
          }
          uVar4 = png_ptr[0x28];
          uVar3 = png_ptr[0x3f];
          buf = (png_bytep)png_ptr[0x27];
          png_ptr[0x1a] = uVar4;
          ((z_streamp)(png_ptr + 0x19))->next_in = buf;
          if (uVar3 < uVar4) {
            png_ptr[0x1a] = uVar3;
          }
          png_crc_read((png_structp)png_ptr,buf,png_ptr[0x1a]);
          png_ptr[0x3f] = png_ptr[0x3f] - png_ptr[0x1a];
        }
        iVar6 = inflate((z_streamp)(png_ptr + 0x19),1);
        if (iVar6 == 1) break;
        if (iVar6 != 0) {
          msg = (char *)png_ptr[0x1f];
          if (msg == (char *)0x0) {
            msg = "Decompression Error";
          }
          png_error((png_structp)png_ptr,msg);
        }
        if (png_ptr[0x1d] == 0) {
          png_error((png_structp)png_ptr,"Extra compressed data");
        }
      }
      if (((png_ptr[0x1d] == 0) || (png_ptr[0x1a] != 0)) || (png_ptr[0x3f] != 0)) {
        png_error((png_structp)png_ptr,"Extra compressed data");
      }
      png_ptr[0x16] = png_ptr[0x16] | 8;
      png_ptr[0x17] = png_ptr[0x17] | 0x20;
      png_ptr[0x1d] = 0;
    }
    if ((png_ptr[0x3f] != 0) || (png_ptr[0x1a] != 0)) {
      png_error((png_structp)png_ptr,"Extra compression data");
    }
    inflateReset((z_streamp)(png_ptr + 0x19));
    png_ptr[0x16] = png_ptr[0x16] | 8;
  }
  return;
}



/* grim_png_data_stream_init @ 1003a990 */

void __cdecl grim_png_data_stream_init(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x30);
    *(int *)(param_1 + 0x14) = iVar2;
    uVar3 = (*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x1000);
    *(undefined4 *)(iVar2 + 0x28) = uVar3;
  }
  puVar1 = *(undefined4 **)(param_1 + 0x14);
  puVar1[2] = &LAB_1003aa10;
  puVar1[3] = grim_png_data_buffer_fill;
  puVar1[4] = grim_png_data_buffer_refill;
  puVar1[5] = &LAB_1003b560;
  puVar1[6] = &DAT_1003ab00;
  puVar1[7] = param_2;
  puVar1[8] = param_3;
  puVar1[9] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  return;
}



/* grim_png_data_buffer_fill @ 1003aa20 */

undefined4 __cdecl grim_png_data_buffer_fill(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  puVar1 = (undefined4 *)param_1[5];
  iVar2 = puVar1[9];
  if (iVar2 < (int)puVar1[8]) {
    uVar3 = puVar1[8] - iVar2;
    if (0x1000 < (int)uVar3) {
      uVar3 = 0x1000;
    }
    puVar5 = (undefined4 *)(puVar1[7] + iVar2);
    puVar6 = (undefined4 *)puVar1[10];
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    puVar1[9] = puVar1[9] + uVar3;
    puVar1[1] = uVar3;
    *puVar1 = puVar1[10];
    *(undefined1 *)(puVar1 + 0xb) = 0;
    return CONCAT31((int3)(uVar3 >> 8),1);
  }
  if (*(char *)(puVar1 + 0xb) != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x29;
    (**(code **)*param_1)(param_1);
  }
  *(undefined4 *)(*param_1 + 0x14) = 0x74;
  (**(code **)(*param_1 + 4))(param_1,0xffffffff);
  *(undefined1 *)puVar1[10] = 0xff;
  *(undefined1 *)(puVar1[10] + 1) = 0xd9;
  puVar1[1] = 2;
  *puVar1 = puVar1[10];
  *(undefined1 *)(puVar1 + 0xb) = 0;
  return 1;
}



/* grim_png_data_buffer_refill @ 1003aac0 */

void __cdecl grim_png_data_buffer_refill(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)param_1[5];
  if (0 < param_2) {
    iVar2 = piVar1[1];
    if (iVar2 < param_2) {
      do {
        param_2 = param_2 - iVar2;
        grim_png_data_buffer_fill(param_1);
        iVar2 = piVar1[1];
      } while (iVar2 < param_2);
    }
    *piVar1 = *piVar1 + param_2;
    piVar1[1] = piVar1[1] - param_2;
  }
  return;
}



/* grim_png_decompress_init @ 1003ab10 */

void __cdecl grim_png_decompress_init(undefined4 *param_1)

{
  *param_1 = grim_png_decompress_alloc;
  param_1[1] = &LAB_1003abc0;
  param_1[2] = &LAB_1003ab80;
  param_1[3] = &LAB_1003ac00;
  param_1[4] = &LAB_1003acb0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[5] = 0;
  param_1[0x1c] = &PTR_s_Bogus_message_code__d_1005035c;
  param_1[0x1d] = 0x77;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  return;
}



/* grim_png_decompress_alloc @ 1003ab60 */

void __cdecl grim_png_decompress_alloc(int *param_1)

{
  (**(code **)(*param_1 + 8))(param_1);
  grim_jpg_mem_zero_block((int)param_1);
  return;
}



/* grim_png_decompress_setup @ 1003acd0 */

void __cdecl grim_png_decompress_setup(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x18);
  *(undefined4 **)(param_1 + 0x18c) = puVar1;
  *puVar1 = &LAB_1003afc0;
  puVar1[1] = grim_png_interlace_init;
  puVar1[2] = &LAB_1003ad20;
  puVar1[3] = &LAB_1003afa0;
  *(undefined1 *)(puVar1 + 4) = 0;
  *(undefined1 *)((int)puVar1 + 0x11) = 0;
  *(undefined1 *)(puVar1 + 5) = 1;
  return;
}



/* grim_png_palette_expand @ 1003b370 */

uint __cdecl grim_png_palette_expand(int *param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piStack_4;
  
  piVar2 = param_1;
  iVar3 = param_1[0x48];
  if (iVar3 != 1) {
    if ((iVar3 < 1) || (4 < iVar3)) {
      *(undefined4 *)(*param_1 + 0x14) = 0x18;
      *(int *)(*param_1 + 0x18) = param_1[0x48];
      *(undefined4 *)(*param_1 + 0x1c) = 4;
      (**(code **)*param_1)(param_1);
    }
    iVar3 = grim_jpg_noop_method(param_1[6],param_1[0x43] << 3);
    param_1[0x4d] = iVar3;
    iVar3 = grim_jpg_noop_method(param_1[7],param_1[0x44] << 3);
    param_1[0x4e] = iVar3;
    piVar4 = (int *)param_1[0x48];
    param_1[0x4f] = 0;
    param_1 = (int *)0x0;
    if (0 < (int)piVar4) {
      piStack_4 = piVar2 + 0x49;
      do {
        iVar3 = *piStack_4;
        uVar6 = *(uint *)(iVar3 + 8);
        uVar1 = *(uint *)(iVar3 + 0xc);
        *(uint *)(iVar3 + 0x40) = *(int *)(iVar3 + 0x24) * uVar6;
        uVar5 = *(uint *)(iVar3 + 0x1c) % uVar6;
        iVar7 = uVar1 * uVar6;
        *(uint *)(iVar3 + 0x34) = uVar6;
        *(uint *)(iVar3 + 0x38) = uVar1;
        *(int *)(iVar3 + 0x3c) = iVar7;
        if (uVar5 == 0) {
          uVar5 = uVar6;
        }
        *(uint *)(iVar3 + 0x44) = uVar5;
        uVar6 = *(uint *)(iVar3 + 0x20) % uVar1;
        if (uVar6 == 0) {
          uVar6 = uVar1;
        }
        *(uint *)(iVar3 + 0x48) = uVar6;
        if (10 < piVar2[0x4f] + iVar7) {
          *(undefined4 *)(*piVar2 + 0x14) = 0xb;
          (**(code **)*piVar2)(piVar2);
        }
        if (0 < iVar7) {
          do {
            piVar2[piVar2[0x4f] + 0x50] = (int)param_1;
            iVar7 = iVar7 + -1;
            piVar2[0x4f] = piVar2[0x4f] + 1;
          } while (iVar7 != 0);
        }
        piVar4 = (int *)((int)param_1 + 1);
        piStack_4 = piStack_4 + 1;
        param_1 = piVar4;
      } while ((int)piVar4 < piVar2[0x48]);
    }
    return (uint)piVar4;
  }
  iVar3 = param_1[0x49];
  param_1[0x4d] = *(int *)(iVar3 + 0x1c);
  param_1[0x4e] = *(int *)(iVar3 + 0x20);
  uVar6 = *(uint *)(iVar3 + 0xc);
  *(undefined4 *)(iVar3 + 0x40) = *(undefined4 *)(iVar3 + 0x24);
  uVar1 = *(uint *)(iVar3 + 0x20);
  uVar5 = uVar1 % uVar6;
  *(undefined4 *)(iVar3 + 0x34) = 1;
  *(undefined4 *)(iVar3 + 0x38) = 1;
  *(undefined4 *)(iVar3 + 0x3c) = 1;
  *(undefined4 *)(iVar3 + 0x44) = 1;
  if (uVar5 == 0) {
    uVar5 = uVar6;
  }
  *(uint *)(iVar3 + 0x48) = uVar5;
  param_1[0x4f] = 1;
  param_1[0x50] = 0;
  return uVar1 / uVar6;
}



/* grim_png_interlace_init @ 1003b520 */

void __cdecl grim_png_interlace_init(int *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)param_1[99];
  *puVar1 = &LAB_1003afc0;
  *(undefined1 *)(puVar1 + 4) = 0;
  *(undefined1 *)((int)puVar1 + 0x11) = 0;
  *(undefined1 *)(puVar1 + 5) = 1;
  (**(code **)(*param_1 + 0x10))(param_1);
  (**(code **)param_1[100])(param_1);
  param_1[0x23] = 0;
  return;
}



/* grim_png_row_filter_apply @ 1003b660 */

uint __cdecl grim_png_row_filter_apply(int *param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  
  puVar2 = (undefined4 *)param_1[5];
  iVar4 = puVar2[1];
  pbVar5 = (byte *)*puVar2;
  do {
    if (iVar4 == 0) {
      uVar3 = (*(code *)puVar2[3])(param_1);
      if ((char)uVar3 == '\0') {
LAB_1003b705:
        return uVar3 & 0xffffff00;
      }
      pbVar5 = (byte *)*puVar2;
      iVar4 = puVar2[1];
    }
    bVar1 = *pbVar5;
    while( true ) {
      pbVar5 = pbVar5 + 1;
      iVar4 = iVar4 + -1;
      if (bVar1 == 0xff) break;
      *(int *)(param_1[100] + 0x58) = *(int *)(param_1[100] + 0x58) + 1;
      *puVar2 = pbVar5;
      puVar2[1] = iVar4;
      if (iVar4 == 0) {
        uVar3 = (*(code *)puVar2[3])(param_1);
        if ((char)uVar3 == '\0') goto LAB_1003b705;
        pbVar5 = (byte *)*puVar2;
        iVar4 = puVar2[1];
      }
      bVar1 = *pbVar5;
    }
    do {
      if (iVar4 == 0) {
        uVar3 = (*(code *)puVar2[3])(param_1);
        if ((char)uVar3 == '\0') goto LAB_1003b705;
        pbVar5 = (byte *)*puVar2;
        iVar4 = puVar2[1];
      }
      uVar3 = (uint)*pbVar5;
      iVar4 = iVar4 + -1;
      pbVar5 = pbVar5 + 1;
    } while (uVar3 == 0xff);
    if (uVar3 != 0) {
      if (*(int *)(param_1[100] + 0x58) != 0) {
        *(undefined4 *)(*param_1 + 0x14) = 0x70;
        *(undefined4 *)(*param_1 + 0x18) = *(undefined4 *)(param_1[100] + 0x58);
        *(uint *)(*param_1 + 0x1c) = uVar3;
        (**(code **)(*param_1 + 4))(param_1,0xffffffff);
        *(undefined4 *)(param_1[100] + 0x58) = 0;
      }
      param_1[0x5e] = uVar3;
      *puVar2 = pbVar5;
      puVar2[1] = iVar4;
      return 1;
    }
    *(int *)(param_1[100] + 0x58) = *(int *)(param_1[100] + 0x58) + 2;
    *puVar2 = pbVar5;
    puVar2[1] = iVar4;
  } while( true );
}



/* grim_png_decompress_start @ 1003b770 */

void __cdecl grim_png_decompress_start(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,0,0x5c);
  *(undefined4 **)(param_1 + 400) = puVar1;
  *puVar1 = &LAB_1003d090;
  *(undefined1 **)(*(int *)(param_1 + 400) + 4) = &LAB_1003bd30;
  *(code **)(*(int *)(param_1 + 400) + 8) = grim_png_filter_dispatch;
  *(code **)(*(int *)(param_1 + 400) + 0xc) = grim_png_row_init;
  iVar2 = 0x10;
  do {
    *(code **)(*(int *)(param_1 + 400) + iVar2) = grim_png_row_init;
    iVar2 = iVar2 + 4;
  } while (iVar2 < 0x50);
  *(undefined1 **)(*(int *)(param_1 + 400) + 0x10) = &LAB_1003b820;
  *(undefined1 **)(*(int *)(param_1 + 400) + 0x48) = &LAB_1003bac0;
  *(undefined4 *)(param_1 + 0xc4) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x178) = 0;
  *(undefined1 *)(*(int *)(param_1 + 400) + 0x50) = 0;
  *(undefined1 *)(*(int *)(param_1 + 400) + 0x51) = 0;
  *(undefined4 *)(*(int *)(param_1 + 400) + 0x58) = 0;
  return;
}



/* grim_png_row_init @ 1003bc90 */

undefined4 __cdecl grim_png_row_init(int *param_1)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  byte *pbVar8;
  
  puVar3 = (undefined4 *)param_1[5];
  iVar7 = puVar3[1];
  pbVar8 = (byte *)*puVar3;
  if (iVar7 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003bd27;
    pbVar8 = (byte *)*puVar3;
    iVar7 = puVar3[1];
  }
  bVar1 = *pbVar8;
  iVar7 = iVar7 + -1;
  pbVar8 = pbVar8 + 1;
  if (iVar7 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') {
LAB_1003bd27:
      return uVar4 & 0xffffff00;
    }
    pbVar8 = (byte *)*puVar3;
    iVar7 = puVar3[1];
  }
  bVar2 = *pbVar8;
  *(undefined4 *)(*param_1 + 0x14) = 0x5a;
  iVar5 = (uint)bVar1 * 0x100 + (uint)bVar2;
  *(int *)(*param_1 + 0x18) = param_1[0x5e];
  *(int *)(*param_1 + 0x1c) = iVar5;
  (**(code **)(*param_1 + 4))(param_1,1);
  *puVar3 = pbVar8 + 1;
  puVar3[1] = iVar7 + -1;
  uVar6 = (**(code **)(param_1[5] + 0x10))(param_1,iVar5 + -2);
  return CONCAT31((int3)((uint)uVar6 >> 8),1);
}



/* grim_png_paeth_predictor @ 1003c320 */

uint __cdecl grim_png_paeth_predictor(int *param_1,undefined1 param_2,undefined1 param_3)

{
  byte bVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  byte *pbVar8;
  byte *pbVar9;
  
  puVar3 = (undefined4 *)param_1[5];
  iVar6 = puVar3[1];
  pbVar8 = (byte *)*puVar3;
  *(undefined1 *)(param_1 + 0x32) = param_2;
  *(undefined1 *)((int)param_1 + 0xc9) = param_3;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar8 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  bVar1 = *pbVar8;
  iVar6 = iVar6 + -1;
  pbVar8 = pbVar8 + 1;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar8 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  bVar2 = *pbVar8;
  iVar6 = iVar6 + -1;
  pbVar8 = pbVar8 + 1;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar8 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar9 = pbVar8 + 1;
  param_1[0x30] = (uint)*pbVar8;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar9 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar8 = pbVar9 + 1;
  param_1[7] = (uint)*pbVar9 << 8;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar8 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar9 = pbVar8 + 1;
  param_1[7] = param_1[7] + (uint)*pbVar8;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar9 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar8 = pbVar9 + 1;
  param_1[6] = (uint)*pbVar9 << 8;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') goto LAB_1003c635;
    pbVar8 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar9 = pbVar8 + 1;
  param_1[6] = param_1[6] + (uint)*pbVar8;
  if (iVar6 == 0) {
    uVar4 = (*(code *)puVar3[3])(param_1);
    if ((char)uVar4 == '\0') {
LAB_1003c635:
      return uVar4 & 0xffffff00;
    }
    pbVar9 = (byte *)*puVar3;
    iVar6 = puVar3[1];
  }
  iVar6 = iVar6 + -1;
  pbVar8 = pbVar9 + 1;
  param_1[8] = (uint)*pbVar9;
  iVar5 = *param_1;
  *(int *)(iVar5 + 0x18) = param_1[0x5e];
  *(int *)(iVar5 + 0x1c) = param_1[6];
  *(int *)(iVar5 + 0x20) = param_1[7];
  *(int *)(iVar5 + 0x24) = param_1[8];
  *(undefined4 *)(*param_1 + 0x14) = 99;
  (**(code **)(*param_1 + 4))(param_1,1);
  if (*(char *)(param_1[100] + 0x51) != '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x39;
    (**(code **)*param_1)(param_1);
  }
  if (((param_1[7] == 0) || (param_1[6] == 0)) || (param_1[8] < 1)) {
    *(undefined4 *)(*param_1 + 0x14) = 0x1f;
    (**(code **)*param_1)(param_1);
  }
  if ((uint)bVar1 * 0x100 + (uint)bVar2 + -8 != param_1[8] * 3) {
    *(undefined4 *)(*param_1 + 0x14) = 9;
    (**(code **)*param_1)(param_1);
  }
  if (param_1[0x31] == 0) {
    iVar5 = (**(code **)param_1[1])(param_1,1,param_1[8] * 0x54);
    param_1[0x31] = iVar5;
  }
  puVar7 = (uint *)param_1[0x31];
  _param_2 = 0;
  if (0 < param_1[8]) {
    do {
      puVar7[1] = _param_2;
      if (iVar6 == 0) {
        uVar4 = (*(code *)puVar3[3])(param_1);
        if ((char)uVar4 == '\0') goto LAB_1003c635;
        pbVar8 = (byte *)*puVar3;
        iVar6 = puVar3[1];
      }
      iVar6 = iVar6 + -1;
      pbVar9 = pbVar8 + 1;
      *puVar7 = (uint)*pbVar8;
      if (iVar6 == 0) {
        uVar4 = (*(code *)puVar3[3])(param_1);
        if ((char)uVar4 == '\0') goto LAB_1003c635;
        pbVar9 = (byte *)*puVar3;
        iVar6 = puVar3[1];
      }
      bVar1 = *pbVar9;
      iVar6 = iVar6 + -1;
      pbVar9 = pbVar9 + 1;
      puVar7[2] = (int)(uint)bVar1 >> 4;
      puVar7[3] = bVar1 & 0xf;
      if (iVar6 == 0) {
        uVar4 = (*(code *)puVar3[3])(param_1);
        if ((char)uVar4 == '\0') goto LAB_1003c635;
        pbVar9 = (byte *)*puVar3;
        iVar6 = puVar3[1];
      }
      iVar6 = iVar6 + -1;
      pbVar8 = pbVar9 + 1;
      puVar7[4] = (uint)*pbVar9;
      iVar5 = *param_1;
      *(uint *)(iVar5 + 0x18) = *puVar7;
      *(uint *)(iVar5 + 0x1c) = puVar7[2];
      *(uint *)(iVar5 + 0x20) = puVar7[3];
      *(uint *)(iVar5 + 0x24) = puVar7[4];
      *(undefined4 *)(*param_1 + 0x14) = 100;
      (**(code **)(*param_1 + 4))(param_1,1);
      _param_2 = _param_2 + 1;
      puVar7 = puVar7 + 0x15;
    } while ((int)_param_2 < param_1[8]);
  }
  *(undefined1 *)(param_1[100] + 0x51) = 1;
  *puVar3 = pbVar8;
  puVar3[1] = iVar6;
  return CONCAT31((int3)((uint)puVar3 >> 8),1);
}



/* grim_png_marker_reader @ 1003c640 */

uint __cdecl grim_png_marker_reader(int *param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  byte *pbVar11;
  uint *puVar12;
  int *piStack_10;
  int iStack_8;
  
  puVar4 = (undefined4 *)param_1[5];
  pbVar10 = (byte *)*puVar4;
  iVar9 = puVar4[1];
  if (*(char *)(param_1[100] + 0x51) == '\0') {
    *(undefined4 *)(*param_1 + 0x14) = 0x3d;
    (**(code **)*param_1)(param_1);
  }
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') goto LAB_1003c944;
    iVar9 = puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  bVar1 = *pbVar10;
  iVar9 = iVar9 + -1;
  pbVar10 = pbVar10 + 1;
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') goto LAB_1003c944;
    iVar9 = puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  bVar2 = *pbVar10;
  iVar9 = iVar9 + -1;
  pbVar10 = pbVar10 + 1;
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') goto LAB_1003c944;
    iVar9 = puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  bVar3 = *pbVar10;
  uVar6 = (uint)bVar3;
  iVar9 = iVar9 + -1;
  pbVar10 = pbVar10 + 1;
  if ((((uint)bVar1 * 0x100 + (uint)bVar2 != uVar6 * 2 + 6) || (bVar3 == 0)) || (4 < bVar3)) {
    *(undefined4 *)(*param_1 + 0x14) = 9;
    (**(code **)*param_1)(param_1);
  }
  *(undefined4 *)(*param_1 + 0x14) = 0x66;
  *(uint *)(*param_1 + 0x18) = uVar6;
  (**(code **)(*param_1 + 4))(param_1,1);
  param_1[0x48] = uVar6;
  iStack_8 = 0;
  if (uVar6 != 0) {
    piStack_10 = param_1 + 0x49;
    do {
      if (iVar9 == 0) {
        uVar5 = (*(code *)puVar4[3])(param_1);
        if ((char)uVar5 == '\0') goto LAB_1003c944;
        iVar9 = puVar4[1];
        pbVar10 = (byte *)*puVar4;
      }
      uVar8 = (uint)*pbVar10;
      iVar9 = iVar9 + -1;
      pbVar10 = pbVar10 + 1;
      if (iVar9 == 0) {
        uVar5 = (*(code *)puVar4[3])(param_1);
        if ((char)uVar5 == '\0') goto LAB_1003c944;
        iVar9 = puVar4[1];
        pbVar10 = (byte *)*puVar4;
      }
      puVar12 = (uint *)param_1[0x31];
      iVar9 = iVar9 + -1;
      bVar1 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      iVar7 = 0;
      if (0 < param_1[8]) {
        do {
          if (uVar8 == *puVar12) goto LAB_1003c7e9;
          iVar7 = iVar7 + 1;
          puVar12 = puVar12 + 0x15;
        } while (iVar7 < param_1[8]);
      }
      *(undefined4 *)(*param_1 + 0x14) = 5;
      *(uint *)(*param_1 + 0x18) = uVar8;
      (**(code **)*param_1)(param_1);
LAB_1003c7e9:
      *piStack_10 = (int)puVar12;
      puVar12[5] = (int)(uint)bVar1 >> 4;
      puVar12[6] = bVar1 & 0xf;
      iVar7 = *param_1;
      *(uint *)(iVar7 + 0x18) = uVar8;
      *(uint *)(iVar7 + 0x1c) = puVar12[5];
      *(uint *)(iVar7 + 0x20) = puVar12[6];
      *(undefined4 *)(*param_1 + 0x14) = 0x67;
      (**(code **)(*param_1 + 4))(param_1,1);
      iStack_8 = iStack_8 + 1;
      piStack_10 = piStack_10 + 1;
    } while (iStack_8 < (int)uVar6);
  }
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') goto LAB_1003c944;
    iVar9 = puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  iVar9 = iVar9 + -1;
  pbVar11 = pbVar10 + 1;
  param_1[0x5a] = (uint)*pbVar10;
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') goto LAB_1003c944;
    iVar9 = puVar4[1];
    pbVar11 = (byte *)*puVar4;
  }
  iVar9 = iVar9 + -1;
  pbVar10 = pbVar11 + 1;
  param_1[0x5b] = (uint)*pbVar11;
  if (iVar9 == 0) {
    uVar5 = (*(code *)puVar4[3])(param_1);
    if ((char)uVar5 == '\0') {
LAB_1003c944:
      return uVar5 & 0xffffff00;
    }
    iVar9 = puVar4[1];
    pbVar10 = (byte *)*puVar4;
  }
  bVar1 = *pbVar10;
  param_1[0x5d] = bVar1 & 0xf;
  iVar7 = *param_1;
  param_1[0x5c] = (int)(uint)bVar1 >> 4;
  *(int *)(iVar7 + 0x18) = param_1[0x5a];
  *(int *)(iVar7 + 0x1c) = param_1[0x5b];
  *(int *)(iVar7 + 0x20) = param_1[0x5c];
  *(int *)(iVar7 + 0x24) = param_1[0x5d];
  *(undefined4 *)(*param_1 + 0x14) = 0x68;
  (**(code **)(*param_1 + 4))(param_1,1);
  *(undefined4 *)(param_1[100] + 0x54) = 0;
  iVar7 = param_1[0x1f];
  param_1[0x1f] = iVar7 + 1;
  *puVar4 = pbVar10 + 1;
  puVar4[1] = iVar9 + -1;
  return CONCAT31((int3)((uint)(iVar7 + 1) >> 8),1);
}



/* grim_png_filter_dispatch @ 1003d000 */

uint __cdecl grim_png_filter_dispatch(int *param_1)

{
  uint uVar1;
  
  if (param_1[0x5e] == 0) {
    uVar1 = grim_png_row_filter_apply(param_1);
    if ((char)uVar1 == '\0') {
      return uVar1;
    }
  }
  if (param_1[0x5e] == *(int *)(param_1[100] + 0x54) + 0xd0) {
    *(undefined4 *)(*param_1 + 0x14) = 0x61;
    *(undefined4 *)(*param_1 + 0x18) = *(undefined4 *)(param_1[100] + 0x54);
    uVar1 = (**(code **)(*param_1 + 4))(param_1,3);
    param_1[0x5e] = 0;
  }
  else {
    uVar1 = (**(code **)(param_1[5] + 0x14))(param_1,*(int *)(param_1[100] + 0x54));
    if ((char)uVar1 == '\0') {
      return uVar1;
    }
  }
  *(uint *)(param_1[100] + 0x54) = *(int *)(param_1[100] + 0x54) + 1U & 7;
  return CONCAT31((int3)(uVar1 >> 8),1);
}



/* grim_png_inflate_init @ 1003ec50 */

void __cdecl grim_png_inflate_init(int param_1,char param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  
  puVar2 = (undefined4 *)(*(code *)**(undefined4 **)(param_1 + 4))(param_1,1,0x74);
  *(undefined4 **)(param_1 + 0x184) = puVar2;
  *puVar2 = &LAB_1003ed60;
  puVar2[2] = &LAB_1003edc0;
  puVar2[0x1c] = 0;
  if (param_2 == '\0') {
    iVar3 = (**(code **)(*(int *)(param_1 + 4) + 4))(param_1,1,0x500);
    piVar8 = puVar2 + 8;
    iVar6 = 10;
    do {
      *piVar8 = iVar3;
      piVar8 = piVar8 + 1;
      iVar3 = iVar3 + 0x80;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    puVar2[4] = 0;
    puVar2[1] = &LAB_1003f1f0;
    puVar2[3] = &LAB_1003ef50;
    return;
  }
  _param_2 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    piVar8 = (int *)(*(int *)(param_1 + 0xc4) + 0xc);
    puVar7 = puVar2 + 0x12;
    do {
      iVar3 = *piVar8;
      iVar6 = iVar3;
      if (*(char *)(param_1 + 200) != '\0') {
        iVar6 = iVar3 * 3;
      }
      iVar1 = *(int *)(param_1 + 4);
      iVar3 = grim_jpg_data_src_init(piVar8[5],iVar3);
      iVar4 = grim_jpg_data_src_init(piVar8[4],piVar8[-1]);
      uVar5 = (**(code **)(iVar1 + 0x14))(param_1,1,1,iVar4,iVar3,iVar6);
      *puVar7 = uVar5;
      _param_2 = _param_2 + 1;
      puVar7 = puVar7 + 1;
      piVar8 = piVar8 + 0x15;
    } while (_param_2 < *(int *)(param_1 + 0x20));
  }
  puVar2[1] = &LAB_1003f200;
  puVar2[3] = &LAB_1003f470;
  puVar2[4] = puVar2 + 0x12;
  return;
}


