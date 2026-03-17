/* grim_draw_text_mono @ 100092b0 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* WARNING: Enum "_D3DFORMAT": Some values do not have unique names */
/* Grim2D vtable 0x13c: fixed 16px mono text */

void grim_draw_text_mono(float x,float y,char *text)

{
  char cVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  int *in_ECX;
  uint uVar10;
  float fVar11;
  char *pcVar12;
  float unaff_retaddr;
  float fVar13;
  float fVar14;
  float fStack_5c;
  int iStack_58;
  float fStack_44;
  
  if ((grim_render_disabled == '\0') && (text != (char *)0x0)) {
    if (grim_font_texture_bound == '\0') {
      (*grim_d3d_device->lpVtbl->SetTexture)(grim_d3d_device,0,grim_font_texture);
    }
    fStack_44 = y;
    fVar14 = 0.0;
    (**(code **)(*in_ECX + 0xfc))(0);
    (**(code **)(*in_ECX + 0xe8))();
    fVar2 = fStack_5c * 32.0;
    uVar10 = 0xffffffff;
    pcVar12 = text;
    do {
      if (uVar10 == 0) break;
      uVar10 = uVar10 - 1;
      cVar1 = *pcVar12;
      pcVar12 = pcVar12 + 1;
    } while (cVar1 != '\0');
    fVar3 = fStack_5c * 16.0;
    bVar4 = false;
    iStack_58 = 0;
    if (0 < (int)(~uVar10 - 1)) {
      do {
        fVar7 = DAT_1005b644;
        fVar6 = DAT_1005b640;
        fVar13 = DAT_1005b5d4;
        fVar5 = DAT_1005b5d0;
        cVar1 = text[iStack_58];
        fVar11 = unaff_retaddr;
        fVar8 = unaff_retaddr;
        if (cVar1 != '\n') {
          if (cVar1 == -0x59) {
            bVar4 = true;
            fVar11 = x;
            fVar8 = fStack_44;
          }
          else {
            if (cVar1 == -0x1b) {
              fStack_44 = fStack_44 + fVar3;
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b5d0,DAT_1005b5d4,DAT_1005b5d0 + 0.0625,DAT_1005b5d4 + 0.0625);
              (**(code **)(*in_ECX + 0x11c))(fVar5,fVar13 + 1.0,fVar2,fVar2);
              fVar14 = DAT_1005b43c;
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b438,DAT_1005b43c,DAT_1005b438 + 0.0625,DAT_1005b43c + 0.0625);
              iVar9 = *in_ECX;
              fVar13 = fVar14 - 6.0;
              x = fVar5;
            }
            else if (cVar1 == -0x1c) {
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b5d0,DAT_1005b5d4,DAT_1005b5d0 + 0.0625,DAT_1005b5d4 + 0.0625);
              (**(code **)(*in_ECX + 0x11c))(fVar5,fVar13 + 1.0,fVar2,fVar2);
              fStack_44 = DAT_1005b3d8 + 0.0625;
              fVar13 = DAT_1005b3dc;
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b3d8,DAT_1005b3dc,fStack_44,DAT_1005b3dc + 0.0625);
              iVar9 = *in_ECX;
              x = fVar5;
              fVar14 = fVar13;
            }
            else if (cVar1 == -10) {
              fStack_44 = fStack_44 + fVar3;
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b640,DAT_1005b644,DAT_1005b640 + 0.0625,DAT_1005b644 + 0.0625);
              (**(code **)(*in_ECX + 0x11c))(fVar6,fVar7 + 1.0,fVar2,fVar2);
              fVar13 = DAT_1005b3dc;
              (**(code **)(*in_ECX + 0x100))
                        (DAT_1005b3d8,DAT_1005b3dc,DAT_1005b3d8 + 0.0625,DAT_1005b3dc + 0.0625);
              iVar9 = *in_ECX;
              x = fVar6;
              fVar14 = fVar13;
            }
            else {
              if (bVar4) {
                bVar4 = false;
              }
              else {
                x = fStack_44 + fVar3;
                fStack_44 = x;
              }
              (**(code **)(*in_ECX + 0x100))
                        ((&grim_font2_uv_u)[cVar1 * 2],(&grim_font2_uv_v)[cVar1 * 2],
                         (float)(&grim_font2_uv_u)[cVar1 * 2] + 0.0625,
                         (float)(&grim_font2_uv_v)[cVar1 * 2] + 0.0625);
              iVar9 = *in_ECX;
              fVar13 = fVar14 + 1.0;
            }
            (**(code **)(iVar9 + 0x11c))(x,fVar13,fVar2,fVar2);
            fVar11 = x;
            fVar8 = fStack_44;
          }
        }
        fStack_44 = fVar8;
        iStack_58 = iStack_58 + 1;
        text = (char *)y;
        x = fVar11;
      } while (iStack_58 < (int)(~uVar10 - 1));
    }
    (**(code **)(*in_ECX + 0xf0))();
  }
  return;
}



/* grim_measure_text_width @ 100096c0 */

/* Grim2D vtable 0x14c: small font width metric (handles newlines) */

int grim_measure_text_width(char *text)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  if (text == (char *)0x0) {
    return 0;
  }
  uVar3 = 0xffffffff;
  iVar2 = 0;
  iVar4 = 0;
  pcVar5 = text;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar6 = 0;
  if (0 < (int)(~uVar3 - 1)) {
    do {
      if (text[iVar6] == 10) {
        if (iVar2 < iVar4) {
          iVar2 = iVar4;
        }
        iVar4 = 0;
      }
      else {
        iVar4 = iVar4 + (uint)*(byte *)((int)&grim_font2_glyph_widths +
                                       (uint)(byte)(&grim_font2_char_map)[(byte)text[iVar6]]);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)(~uVar3 - 1));
    if (iVar2 < iVar4) {
      iVar2 = iVar4;
    }
  }
  return iVar2;
}



/* grim_draw_text_small @ 10009730 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x144: small font draw (GRIM_Font2) */

void grim_draw_text_small(float x,float y,char *text)

{
  char cVar1;
  int *in_ECX;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 unaff_retaddr;
  undefined4 uVar6;
  int iVar7;
  undefined4 uStack_14;
  
  if ((grim_render_disabled == '\0') && (text != (char *)0x0)) {
    ftol();
    ftol();
    if ((grim_font2_texture_handle != -1) ||
       (grim_font2_texture_handle = (**(code **)(*in_ECX + 0xc0))(s_GRIM_Font2_10053c3c),
       grim_font2_texture_handle != -1)) {
      iVar7 = grim_font2_texture_handle;
      (**(code **)(*in_ECX + 0xc4))(grim_font2_texture_handle,0);
      if (DAT_1005ccd8 != 1) {
        (**(code **)(*in_ECX + 0x20))(0x15,1);
      }
      uVar6 = 0;
      (**(code **)(*in_ECX + 0xfc))(0);
      (**(code **)(*in_ECX + 0xe8))();
      uVar2 = 0xffffffff;
      pcVar4 = text;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      iVar5 = 0;
      if (0 < (int)(~uVar2 - 1)) {
        do {
          uVar3 = (uint)(byte)(&grim_font2_char_map)[(byte)text[iVar5]];
          if (text[iVar5] != 10) {
            (**(code **)(*in_ECX + 0x100))
                      ((float)(&grim_font2_uv_u)[uVar3 * 2] + 0.001953125,
                       (float)(&grim_font2_uv_v)[uVar3 * 2] + 0.001953125,
                       ((float)*(byte *)((int)&grim_font2_glyph_widths + uVar3) * 0.00390625 +
                       (float)(&grim_font2_uv_u)[uVar3 * 2] + 0.001953125) - 0.001953125,
                       ((float)(&grim_font2_uv_v)[uVar3 * 2] + 0.001953125 + 0.0625) - 0.001953125);
            (**(code **)(*in_ECX + 0x11c))(uVar6,iVar7,uStack_14,0x41800000);
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < (int)(~uVar2 - 1));
      }
      (**(code **)(*in_ECX + 0xf0))();
      (**(code **)(*in_ECX + 0x20))(0x15,unaff_retaddr);
    }
  }
  return;
}



/* grim_draw_text_mono_fmt @ 10009940 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x140: printf-style wrapper around draw_text_mono (cdecl varargs, explicit self) */

void grim_draw_text_mono_fmt(IGrim2D *self,float x,float y,char *fmt,...)

{
  vsprintf(&grim_printf_buffer,fmt,&stack0x00000014);
  (*self->vtable->grim_draw_text_mono)(x,y,&grim_printf_buffer);
  return;
}



/* grim_draw_text_small_fmt @ 10009980 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Grim2D vtable 0x148: formatted small-font text (cdecl varargs, explicit self; vsprintf + vtable
   0x144) */

void grim_draw_text_small_fmt(IGrim2D *self,float x,float y,char *fmt,...)

{
  vsprintf(&grim_printf_buffer_alt,fmt,&stack0x00000014);
  (*self->vtable->grim_draw_text_small)(x,y,&grim_printf_buffer_alt);
  return;
}


