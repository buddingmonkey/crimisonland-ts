/* grim_vertex_space_converter_destroy @ 1001692e */

/* frees the converted vertex buffer at this+0x104c */

void __fastcall grim_vertex_space_converter_destroy(void *this)

{
  *(undefined ***)this = &PTR_FUN_1004cae4;
  operator_delete(*(void **)((int)this + 0x104c));
  return;
}



/* grim_convert_vertex_space @ 10016944 */

/* converts vec4 coordinates between space modes (1/2/3), writes to this+0x104c, returns the output
   buffer */

float * __thiscall grim_convert_vertex_space(void *this,float *src)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = *(int *)((int)this + 8);
  if (iVar3 == 1) {
    if (*(int *)((int)this + 0x1048) == 2) {
      uVar4 = 0;
      if (*(int *)((int)this + 0x1058) != 0) {
        pfVar2 = src + 2;
        iVar3 = 0;
        do {
          uVar4 = uVar4 + 1;
          *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = (pfVar2[-2] + 1.0) * 0.5;
          *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = (pfVar2[-1] + 1.0) * 0.5;
          *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = (*pfVar2 + 1.0) * 0.5;
          *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = pfVar2[1];
          pfVar2 = pfVar2 + 4;
          iVar3 = iVar3 + 0x10;
        } while (uVar4 < *(uint *)((int)this + 0x1058));
      }
    }
    else if ((*(int *)((int)this + 0x1048) == 3) && (uVar4 = 0, *(int *)((int)this + 0x1058) != 0))
    {
      pfVar2 = src + 2;
      iVar3 = 0;
      do {
        uVar4 = uVar4 + 1;
        *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = (pfVar2[-2] + 1.0) * 0.5;
        *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = (pfVar2[-1] + 1.0) * 0.5;
        *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = (*pfVar2 + 1.0) * 0.5;
        *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = (pfVar2[1] + 1.0) * 0.5;
        pfVar2 = pfVar2 + 4;
        iVar3 = iVar3 + 0x10;
      } while (uVar4 < *(uint *)((int)this + 0x1058));
    }
  }
  else if (iVar3 == 2) {
    if (*(int *)((int)this + 0x1048) == 1) {
      uVar4 = 0;
      if (*(int *)((int)this + 0x1058) != 0) {
        pfVar2 = src + 2;
        iVar3 = 0;
        do {
          uVar4 = uVar4 + 1;
          *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = pfVar2[-2] * 2.0 - 1.0;
          *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = pfVar2[-1] * 2.0 - 1.0;
          *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = *pfVar2 * 2.0 - 1.0;
          *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = pfVar2[1];
          pfVar2 = pfVar2 + 4;
          iVar3 = iVar3 + 0x10;
        } while (uVar4 < *(uint *)((int)this + 0x1058));
      }
    }
    else if ((*(int *)((int)this + 0x1048) == 3) && (uVar4 = 0, *(int *)((int)this + 0x1058) != 0))
    {
      pfVar2 = src + 2;
      iVar3 = 0;
      do {
        *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = pfVar2[-2];
        uVar4 = uVar4 + 1;
        *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = pfVar2[-1];
        *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = *pfVar2;
        pfVar1 = pfVar2 + 1;
        pfVar2 = pfVar2 + 4;
        *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = (*pfVar1 + 1.0) * 0.5;
        iVar3 = iVar3 + 0x10;
      } while (uVar4 < *(uint *)((int)this + 0x1058));
    }
  }
  else if (iVar3 == 3) {
    if (*(int *)((int)this + 0x1048) == 1) {
      uVar4 = 0;
      if (*(int *)((int)this + 0x1058) != 0) {
        pfVar2 = src + 2;
        iVar3 = 0;
        do {
          uVar4 = uVar4 + 1;
          *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = pfVar2[-2] * 2.0 - 1.0;
          *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = pfVar2[-1] * 2.0 - 1.0;
          *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = *pfVar2 * 2.0 - 1.0;
          *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = pfVar2[1] * 2.0 - 1.0;
          pfVar2 = pfVar2 + 4;
          iVar3 = iVar3 + 0x10;
        } while (uVar4 < *(uint *)((int)this + 0x1058));
      }
    }
    else if ((*(int *)((int)this + 0x1048) == 2) && (uVar4 = 0, *(int *)((int)this + 0x1058) != 0))
    {
      pfVar2 = src + 2;
      iVar3 = 0;
      do {
        *(float *)(iVar3 + *(int *)((int)this + 0x104c)) = pfVar2[-2];
        uVar4 = uVar4 + 1;
        *(float *)(iVar3 + 4 + *(int *)((int)this + 0x104c)) = pfVar2[-1];
        *(float *)(iVar3 + 8 + *(int *)((int)this + 0x104c)) = *pfVar2;
        pfVar1 = pfVar2 + 1;
        pfVar2 = pfVar2 + 4;
        *(float *)(iVar3 + 0xc + *(int *)((int)this + 0x104c)) = (*pfVar1 + *pfVar1) - 1.0;
        iVar3 = iVar3 + 0x10;
      } while (uVar4 < *(uint *)((int)this + 0x1058));
    }
  }
  return *(float **)((int)this + 0x104c);
}


