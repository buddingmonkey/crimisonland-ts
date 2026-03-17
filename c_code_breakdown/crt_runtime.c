/* identity_passthrough @ 00417a90 */

undefined4 __fastcall identity_passthrough(undefined4 param_1)

{
  return param_1;
}



/* crt_get_os_version_flag @ 0045661f */

uint __cdecl crt_get_os_version_flag(DWORD param_1)

{
  WINBOOL WVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  _OSVERSIONINFOA *p_Var4;
  undefined8 uVar5;
  _OSVERSIONINFOA local_9c;
  char local_5;
  
  p_Var4 = &local_9c;
  for (iVar3 = 0x25; iVar3 != 0; iVar3 = iVar3 + -1) {
    p_Var4->dwOSVersionInfoSize = 0;
    p_Var4 = (_OSVERSIONINFOA *)&p_Var4->dwMajorVersion;
  }
  local_5 = '\0';
  local_9c.dwOSVersionInfoSize = 0x94;
  WVar1 = GetVersionExA(&local_9c);
  if (WVar1 == 0) {
    local_5 = '\x01';
  }
  if (local_9c.dwPlatformId == 1) {
    if ((local_9c.dwMajorVersion < 5) &&
       (((local_9c.dwMajorVersion != 4 || (local_9c.dwMinorVersion < 10)) ||
        ((ushort)local_9c.dwBuildNumber < 0x55d)))) {
      local_5 = '\x01';
    }
  }
  else {
    if (local_9c.dwPlatformId != 2) {
      return 0;
    }
    if (WVar1 != 0) {
      if (param_1 != 10) {
        uVar2 = IsProcessorFeaturePresent(param_1);
        return uVar2;
      }
      goto LAB_004566c4;
    }
  }
  if (param_1 == 6) {
    if (local_5 == '\0') {
      uVar2 = cpu_detect_intel();
      return uVar2 & 4;
    }
  }
  else {
    if (param_1 == 7) {
      uVar5 = FUN_00456542(extraout_ECX,extraout_EDX);
      return (uint)uVar5;
    }
    if ((param_1 == 10) && (local_5 == '\0')) {
LAB_004566c4:
      uVar2 = cpu_detect_intel();
      return uVar2 & 8;
    }
  }
  return 0;
}



/* crt_onexit @ 00460d08 */

/* registers an onexit/atexit callback */

void * __cdecl crt_onexit(void *func)

{
  size_t sVar1;
  void *pvVar2;
  
  crt_exit_lock();
  sVar1 = crt_msize(crt_onexit_table_end);
  if (sVar1 < (uint)((int)crt_onexit_table_begin + (4 - (int)crt_onexit_table_end))) {
    sVar1 = crt_msize(crt_onexit_table_end);
    pvVar2 = crt_realloc(crt_onexit_table_end,sVar1 + 0x10);
    if (pvVar2 == (void *)0x0) {
      func = (void *)0x0;
      goto LAB_00460d7d;
    }
    crt_onexit_table_begin =
         (undefined4 *)
         ((int)pvVar2 + ((int)crt_onexit_table_begin - (int)crt_onexit_table_end >> 2) * 4);
    crt_onexit_table_end = pvVar2;
  }
  *crt_onexit_table_begin = func;
  crt_onexit_table_begin = crt_onexit_table_begin + 1;
LAB_00460d7d:
  crt_exit_unlock();
  return func;
}



/* crt_atexit @ 00460d86 */

/* atexit wrapper (returns 0/-1) */

int __cdecl crt_atexit(void *func)

{
  void *pvVar1;
  
  pvVar1 = crt_onexit(func);
  return (pvVar1 != (void *)0x0) - 1;
}



/* crt_free @ 00460dc7 */

/* CRT free wrapper */

void __cdecl crt_free(void *ptr)

{
  crt_free_base(ptr);
  return;
}



/* crt_strtol @ 00460dd2 */

int __thiscall crt_strtol(void *this,byte *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint c;
  byte *pbVar4;
  undefined *puVar5;
  
  while( true ) {
    if (crt_locale_type < 2) {
      uVar1 = (byte)crt_ctype_table[(uint)*param_1 * 2] & 8;
      this = crt_ctype_table;
    }
    else {
      puVar5 = (undefined *)0x8;
      uVar1 = crt_isctype(this,(uint)*param_1,8);
      this = puVar5;
    }
    if (uVar1 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar1 = (uint)*param_1;
  pbVar4 = param_1 + 1;
  if ((uVar1 == 0x2d) || (c = uVar1, uVar1 == 0x2b)) {
    c = (uint)*pbVar4;
    pbVar4 = param_1 + 2;
  }
  iVar3 = 0;
  while( true ) {
    if (crt_locale_type < 2) {
      uVar2 = (byte)crt_ctype_table[c * 2] & 4;
    }
    else {
      puVar5 = (undefined *)0x4;
      uVar2 = crt_isctype(this,c,4);
      this = puVar5;
    }
    if (uVar2 == 0) break;
    iVar3 = (c - 0x30) + iVar3 * 10;
    c = (uint)*pbVar4;
    pbVar4 = pbVar4 + 1;
  }
  if (uVar1 == 0x2d) {
    iVar3 = -iVar3;
  }
  return iVar3;
}



/* crt_fclose @ 00460e5d */

/* fclose wrapper with CRT lock/unlock */

int __cdecl crt_fclose(FILE *fp)

{
  int iVar1;
  
  iVar1 = -1;
  if ((fp->_flag & 0x40) == 0) {
    crt_lock_file((uint)fp);
    iVar1 = __fclose_lk(fp);
    crt_unlock_file((uint)fp);
  }
  else {
    fp->_flag = 0;
  }
  return iVar1;
}



/* crt_fgets @ 00460fac */

/* CRT fgets wrapper with file lock/unlock (reads until newline or size-1) */

char * __cdecl crt_fgets(char *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  uint uVar2;
  char *pcVar3;
  
  if (param_2 < 1) {
    param_1 = (char *)0x0;
  }
  else {
    crt_lock_file((uint)param_3);
    pcVar3 = param_1;
    do {
      param_2 = param_2 + -1;
      if (param_2 == 0) break;
      piVar1 = param_3 + 1;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 < 0) {
        uVar2 = crt_filbuf(param_3);
      }
      else {
        uVar2 = (uint)*(byte *)*param_3;
        *param_3 = (byte *)*param_3 + 1;
      }
      if (uVar2 == 0xffffffff) {
        if (pcVar3 == param_1) {
          param_1 = (char *)0x0;
          goto LAB_00461000;
        }
        break;
      }
      *pcVar3 = (char)uVar2;
      pcVar3 = pcVar3 + 1;
    } while ((char)uVar2 != '\n');
    *pcVar3 = '\0';
LAB_00461000:
    crt_unlock_file((uint)param_3);
  }
  return param_1;
}



/* crt_fsopen @ 0046100e */

/* opens file with explicit share mode (fopen uses share=0x40) */

undefined4 * __cdecl crt_fsopen(LPCSTR param_1,char *param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = crt_getstream();
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  puVar2 = crt_openfile(param_1,param_2,param_3,puVar1);
  crt_unlock_file((uint)puVar1);
  return puVar2;
}



/* crt_fopen @ 0046103f */

/* fopen wrapper (calls crt_fsopen with share=0x40) */

void __cdecl crt_fopen(LPCSTR param_1,char *param_2)

{
  crt_fsopen(param_1,param_2,0x40);
  return;
}



/* __ftol @ 00461054 */

/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong __ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}



/* operator_new @ 0046107b */

/* Library Function - Single Match
    void * __cdecl operator new(unsigned int)
   
   Library: Visual Studio 2003 Release */

void * __cdecl operator_new(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(param_1,1);
  return pvVar1;
}



/* crt_vsprintf @ 00461089 */

/* CRT: format string to buffer */

int __cdecl crt_vsprintf(char *dst,char *fmt,void *args)

{
  int iVar1;
  char *local_24;
  int local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_1c = dst;
  local_24 = dst;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = crt_output((int *)&local_24,(byte *)fmt,args);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    crt_flsbuf(0,(int *)&local_24);
  }
  else {
    *local_24 = '\0';
  }
  return iVar1;
}



/* crt_atof_l @ 004610da */

/* CRT-like parse string to float (atof-style) */

float __thiscall crt_atof_l(void *this,char *str)

{
  uint uVar1;
  int iVar2;
  byte *this_00;
  undefined *puVar3;
  uint local_1c [6];
  
  while( true ) {
    if (crt_locale_type < 2) {
      uVar1 = (byte)crt_ctype_table[(uint)(byte)*str * 2] & 8;
      this = crt_ctype_table;
    }
    else {
      puVar3 = (undefined *)0x8;
      uVar1 = crt_isctype(this,(uint)(byte)*str,8);
      this = puVar3;
    }
    if (uVar1 == 0) break;
    str = (char *)((byte *)str + 1);
  }
  this_00 = (byte *)str;
  _strlen(str);
  iVar2 = FUN_00464be7(this_00,local_1c,(byte *)str);
  return (float)*(double *)(iVar2 + 0x10);
}



/* crt_ci_pow @ 00461140 */

/* x87 helper for pow(base, exp) using ST0/ST1 */

void crt_ci_pow(void)

{
  float10 in_ST0;
  float10 in_ST1;
  
  FUN_00461162(SUB84((double)in_ST1,0),(uint)((ulonglong)(double)in_ST1 >> 0x20),
               SUB84((double)in_ST0,0),(uint)((ulonglong)(double)in_ST0 >> 0x20));
  return;
}



/* FUN_00461335 @ 00461335 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00461335(void)

{
  float10 in_ST0;
  
  if (ROUND(in_ST0) == in_ST0) {
    return;
  }
  return;
}



/* crt_strtok @ 0046135d */

/* CRT: tokenize string, uses TLS for state */

char * __cdecl crt_strtok(char *str,char *delim)

{
  byte bVar1;
  DWORD *pDVar2;
  int iVar3;
  byte *pbVar4;
  byte local_24 [32];
  
  pDVar2 = crt_get_thread_data();
  pbVar4 = local_24;
  for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
    pbVar4[0] = 0;
    pbVar4[1] = 0;
    pbVar4[2] = 0;
    pbVar4[3] = 0;
    pbVar4 = pbVar4 + 4;
  }
  do {
    bVar1 = *delim;
    local_24[bVar1 >> 3] = local_24[bVar1 >> 3] | '\x01' << (bVar1 & 7);
    delim = (char *)((byte *)delim + 1);
  } while (bVar1 != 0);
  if (str == (char *)0x0) {
    str = (char *)pDVar2[6];
  }
  for (; (bVar1 = *str, pbVar4 = (byte *)str, (local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0
         && (bVar1 != 0)); str = (char *)((byte *)str + 1)) {
  }
  do {
    bVar1 = *pbVar4;
    if (bVar1 == 0) {
LAB_004613ec:
      pDVar2[6] = (DWORD)pbVar4;
      return (char *)(-(uint)((byte *)str != pbVar4) & (uint)str);
    }
    if ((local_24[bVar1 >> 3] & (byte)(1 << (bVar1 & 7))) != 0) {
      *pbVar4 = 0;
      pbVar4 = pbVar4 + 1;
      goto LAB_004613ec;
    }
    pbVar4 = pbVar4 + 1;
  } while( true );
}



/* _strncmp @ 00461410 */

/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}



/* crt_fflush @ 00461448 */

/* CRT: fflush wrapper (NULL flushes all) */

int __cdecl crt_fflush(int *param_1)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    iVar1 = crt_flushall(0);
    return iVar1;
  }
  crt_lock_file((uint)param_1);
  iVar1 = crt_fflush_nolock(param_1);
  crt_unlock_file((uint)param_1);
  return iVar1;
}



/* crt_fflush_nolock @ 00461477 */

/* CRT: fflush without lock */

int __cdecl crt_fflush_nolock(int *param_1)

{
  int iVar1;
  
  iVar1 = crt_flushbuf(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((*(byte *)((int)param_1 + 0xd) & 0x40) != 0) {
    iVar1 = crt_commit(param_1[4]);
    return -(uint)(iVar1 != 0);
  }
  return 0;
}



/* crt_flushbuf @ 004614a5 */

/* CRT: flush write buffer */

undefined4 __cdecl crt_flushbuf(int *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint count;
  
  uVar2 = 0;
  if ((((byte)param_1[3] & 3) == 2) && ((param_1[3] & 0x108U) != 0)) {
    count = *param_1 - param_1[2];
    if (0 < (int)count) {
      uVar1 = crt_write(param_1[4],(char *)param_1[2],count);
      if (uVar1 == count) {
        if ((param_1[3] & 0x80U) != 0) {
          param_1[3] = param_1[3] & 0xfffffffd;
        }
      }
      else {
        param_1[3] = param_1[3] | 0x20;
        uVar2 = 0xffffffff;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return uVar2;
}



/* crt_flushall @ 0046150a */

/* CRT: flush all streams (mode 0/1) */

int __cdecl crt_flushall(int mode)

{
  FILE *pFVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  crt_lock(2);
  iVar4 = 0;
  if (0 < crt_stream_count) {
    do {
      pFVar1 = crt_stream_table[iVar4];
      if ((pFVar1 != (FILE *)0x0) && (((byte)pFVar1[0xc] & 0x83) != 0)) {
        crt_lock_file2(iVar4,(int)pFVar1);
        pFVar1 = crt_stream_table[iVar4];
        if ((*(uint *)(pFVar1 + 0xc) & 0x83) != 0) {
          if (mode == 1) {
            iVar2 = crt_fflush_nolock((int *)pFVar1);
            if (iVar2 != -1) {
              iVar3 = iVar3 + 1;
            }
          }
          else if ((mode == 0) && ((*(uint *)(pFVar1 + 0xc) & 2) != 0)) {
            iVar2 = crt_fflush_nolock((int *)pFVar1);
            if (iVar2 == -1) {
              iVar5 = -1;
            }
          }
        }
        crt_unlock_file2(iVar4,(int)crt_stream_table[iVar4]);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < crt_stream_count);
  }
  crt_unlock(2);
  if (mode != 1) {
    iVar3 = iVar5;
  }
  return iVar3;
}



/* crt_fwrite @ 004615ae */

/* fwrite wrapper with CRT lock/unlock */

uint __cdecl crt_fwrite(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  crt_lock_file((uint)param_4);
  uVar1 = crt_fwrite_nolock(param_1,param_2,param_3,param_4);
  crt_unlock_file((uint)param_4);
  return uVar1;
}



/* crt_fwrite_nolock @ 004615dd */

/* fwrite implementation (no locking) */

uint __cdecl crt_fwrite_nolock(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int *size;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  piVar1 = param_4;
  piVar5 = (int *)(param_2 * param_3);
  if (piVar5 == (int *)0x0) {
    param_3 = 0;
  }
  else {
    piVar4 = piVar5;
    if ((*(ushort *)(param_4 + 3) & 0x10c) == 0) {
      param_4 = (int *)0x1000;
    }
    else {
      param_4 = (int *)param_4[6];
    }
    do {
      if (((piVar1[3] & 0x108U) == 0) || (piVar6 = (int *)piVar1[1], piVar6 == (int *)0x0)) {
        if (param_4 <= piVar4) {
          if (((piVar1[3] & 0x108U) != 0) && (iVar2 = crt_flushbuf(piVar1), iVar2 != 0)) {
LAB_004616de:
            return (uint)((int)piVar5 - (int)piVar4) / param_2;
          }
          piVar6 = piVar4;
          if (param_4 != (int *)0x0) {
            piVar6 = (int *)((int)piVar4 - (uint)piVar4 % (uint)param_4);
          }
          size = (int *)crt_write(piVar1[4],param_1,(uint)piVar6);
          if ((size == (int *)0xffffffff) ||
             (piVar4 = (int *)((int)piVar4 - (int)size), size < piVar6)) {
            piVar1[3] = piVar1[3] | 0x20;
            goto LAB_004616de;
          }
          goto LAB_00461695;
        }
        uVar3 = crt_flsbuf((int)*param_1,piVar1);
        if (uVar3 == 0xffffffff) goto LAB_004616de;
        param_1 = param_1 + 1;
        param_4 = (int *)piVar1[6];
        piVar4 = (int *)((int)piVar4 - 1);
        if ((int)param_4 < 1) {
          param_4 = (int *)0x1;
        }
      }
      else {
        size = piVar4;
        if (piVar6 <= piVar4) {
          size = piVar6;
        }
        crt_bufcpy((void *)*piVar1,param_1,(size_t)size);
        piVar1[1] = piVar1[1] - (int)size;
        *piVar1 = *piVar1 + (int)size;
        piVar4 = (int *)((int)piVar4 - (int)size);
LAB_00461695:
        param_1 = param_1 + (int)size;
      }
    } while (piVar4 != (int *)0x0);
  }
  return param_3;
}



/* crt_sprintf @ 004616e7 */

/* sprintf-style formatter (uses CRT output core) */

int __cdecl crt_sprintf(char *dst,char *fmt,...)

{
  int iVar1;
  char *local_24;
  int local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_1c = dst;
  local_24 = dst;
  local_18 = 0x42;
  local_20 = 0x7fffffff;
  iVar1 = crt_output((int *)&local_24,(byte *)fmt,(undefined4 *)&stack0x0000000c);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    crt_flsbuf(0,(int *)&local_24);
  }
  else {
    *local_24 = '\0';
  }
  return iVar1;
}



/* crt_srand @ 00461739 */

/* sets the per-thread RNG seed (srand) */

void __cdecl crt_srand(uint seed)

{
  DWORD *pDVar1;
  
  pDVar1 = crt_get_thread_data();
  pDVar1[5] = seed;
  return;
}



/* crt_rand @ 00461746 */

/* returns a pseudo-random value using the per-thread seed (rand) */

int __cdecl crt_rand(void)

{
  DWORD *pDVar1;
  uint uVar2;
  
  pDVar1 = crt_get_thread_data();
  uVar2 = pDVar1[5] * 0x343fd + 0x269ec3;
  pDVar1[5] = uVar2;
  return uVar2 >> 0x10 & 0x7fff;
}



/* crt_findfirst @ 00461768 */

/* CRT _findfirst wrapper over FindFirstFileA */

HANDLE __cdecl crt_findfirst(char *pattern,uint *finddata)

{
  HANDLE pvVar1;
  DWORD DVar2;
  int *piVar3;
  uint uVar4;
  _WIN32_FIND_DATAA local_144;
  
  pvVar1 = FindFirstFileA(pattern,&local_144);
  if (pvVar1 != (HANDLE)0xffffffff) {
    *finddata = -(uint)(local_144.dwFileAttributes != 0x80) & local_144.dwFileAttributes;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftCreationTime);
    finddata[1] = uVar4;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftLastAccessTime);
    finddata[2] = uVar4;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftLastWriteTime);
    finddata[3] = uVar4;
    finddata[4] = local_144.nFileSizeLow;
    crt_strcpy((char *)(finddata + 5),local_144.cFileName);
    return pvVar1;
  }
  DVar2 = GetLastError();
  if (DVar2 < 2) {
LAB_004617a6:
    piVar3 = crt_errno_ptr();
    *piVar3 = 0x16;
  }
  else {
    if (3 < DVar2) {
      if (DVar2 == 8) {
        piVar3 = crt_errno_ptr();
        *piVar3 = 0xc;
        return (HANDLE)0xffffffff;
      }
      if (DVar2 != 0x12) goto LAB_004617a6;
    }
    piVar3 = crt_errno_ptr();
    *piVar3 = 2;
  }
  return (HANDLE)0xffffffff;
}



/* crt_findnext @ 00461835 */

/* CRT _findnext wrapper over FindNextFileA (returns 0/-1) */

int __cdecl crt_findnext(HANDLE handle,uint *finddata)

{
  WINBOOL WVar1;
  DWORD DVar2;
  int *piVar3;
  uint uVar4;
  _WIN32_FIND_DATAA local_144;
  
  WVar1 = FindNextFileA(handle,&local_144);
  if (WVar1 != 0) {
    *finddata = -(uint)(local_144.dwFileAttributes != 0x80) & local_144.dwFileAttributes;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftCreationTime);
    finddata[1] = uVar4;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftLastAccessTime);
    finddata[2] = uVar4;
    uVar4 = ___timet_from_ft((FILETIME *)&local_144.ftLastWriteTime);
    finddata[3] = uVar4;
    finddata[4] = local_144.nFileSizeLow;
    crt_strcpy((char *)(finddata + 5),local_144.cFileName);
    return 0;
  }
  DVar2 = GetLastError();
  if (DVar2 < 2) {
LAB_0046186f:
    piVar3 = crt_errno_ptr();
    *piVar3 = 0x16;
  }
  else {
    if (3 < DVar2) {
      if (DVar2 == 8) {
        piVar3 = crt_errno_ptr();
        *piVar3 = 0xc;
        return -1;
      }
      if (DVar2 != 0x12) goto LAB_0046186f;
    }
    piVar3 = crt_errno_ptr();
    *piVar3 = 2;
  }
  return -1;
}



/* crt_findclose @ 004618fd */

/* CRT _findclose wrapper over FindClose */

int __cdecl crt_findclose(HANDLE handle)

{
  WINBOOL WVar1;
  int *piVar2;
  
  WVar1 = FindClose(handle);
  if (WVar1 == 0) {
    piVar2 = crt_errno_ptr();
    *piVar2 = 0x16;
    return -1;
  }
  return 0;
}



/* ___timet_from_ft @ 0046191d */

/* Library Function - Single Match
    ___timet_from_ft
   
   Library: Visual Studio 2003 Release */

int __cdecl ___timet_from_ft(FILETIME *param_1)

{
  WINBOOL WVar1;
  long lVar2;
  _SYSTEMTIME local_1c;
  _FILETIME local_c;
  
  if ((param_1->dwLowDateTime != 0) || (param_1->dwHighDateTime != 0)) {
    WVar1 = FileTimeToLocalFileTime((FILETIME *)param_1,&local_c);
    if (WVar1 != 0) {
      WVar1 = FileTimeToSystemTime(&local_c,&local_1c);
      if (WVar1 != 0) {
        lVar2 = crt_mktime((uint)local_1c.wYear,(uint)local_1c.wMonth,(uint)local_1c.wDay,
                           (uint)local_1c.wHour,(uint)local_1c.wMinute,(uint)local_1c.wSecond,-1);
        return lVar2;
      }
    }
  }
  return -1;
}



/* crt_ehvec_ctor @ 00461981 */

/* MSVC __ehvec_ctor: constructs an array; uses dtor to unwind on exception */

void crt_ehvec_ctor(void *ptr,uint size,int count,void *ctor,void *dtor)

{
  int local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046f9e0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  for (local_20 = 0; local_20 < count; local_20 = local_20 + 1) {
    (*ctor)();
  }
  local_8 = 0xffffffff;
  FUN_004619eb();
  ExceptionList = local_14;
  return;
}



/* FUN_004619eb @ 004619eb */

void FUN_004619eb(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x20) == 0) {
    crt_array_unwind(*(void **)(unaff_EBP + 8),*(uint *)(unaff_EBP + 0xc),
                     *(int *)(unaff_EBP + -0x1c),*(void **)(unaff_EBP + 0x18));
  }
  return;
}



/* crt_ehvec_dtor @ 00461a03 */

/* MSVC __ehvec_dtor: destroys an array with exception handling */

void crt_ehvec_dtor(void *ptr,uint size,int count,void *dtor)

{
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046f9f0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  while( true ) {
    count = count + -1;
    if (count < 0) break;
    (*dtor)();
  }
  local_8 = 0xffffffff;
  FUN_00461a6b();
  ExceptionList = local_14;
  return;
}



/* FUN_00461a6b @ 00461a6b */

void FUN_00461a6b(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    crt_array_unwind(*(void **)(unaff_EBP + 8),*(uint *)(unaff_EBP + 0xc),*(int *)(unaff_EBP + 0x10)
                     ,*(void **)(unaff_EBP + 0x14));
  }
  return;
}



/* crt_array_unwind @ 00461a83 */

/* destructor loop used for array unwinding (backward walk) */

void crt_array_unwind(void *ptr,uint size,int count,void *dtor)

{
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046fa00;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &local_14;
  while( true ) {
    count = count + -1;
    if (count < 0) break;
    (*dtor)();
  }
  ExceptionList = local_14;
  return;
}



/* crt_fread @ 00461af7 */

/* fread wrapper with CRT lock/unlock */

uint __cdecl crt_fread(char *param_1,uint param_2,uint param_3,int *param_4)

{
  uint uVar1;
  
  crt_lock_file((uint)param_4);
  uVar1 = crt_fread_nolock(param_1,param_2,param_3,param_4);
  crt_unlock_file((uint)param_4);
  return uVar1;
}



/* crt_fread_nolock @ 00461b26 */

/* fread implementation (no locking) */

uint __cdecl crt_fread_nolock(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  char *size;
  
  piVar1 = param_4;
  pcVar6 = (char *)(param_2 * param_3);
  if (pcVar6 == (char *)0x0) {
    param_3 = 0;
  }
  else {
    pcVar5 = param_1;
    param_1 = pcVar6;
    if ((*(ushort *)(param_4 + 3) & 0x10c) == 0) {
      param_4 = (int *)0x1000;
    }
    else {
      param_4 = (int *)param_4[6];
    }
    do {
      if (((*(ushort *)(piVar1 + 3) & 0x10c) == 0) ||
         (pcVar2 = (char *)piVar1[1], pcVar2 == (char *)0x0)) {
        if (param_1 < param_4) {
          uVar4 = crt_filbuf(piVar1);
          if (uVar4 == 0xffffffff) goto LAB_00461c02;
          *pcVar5 = (char)uVar4;
          param_4 = (int *)piVar1[6];
          pcVar5 = pcVar5 + 1;
          param_1 = param_1 + -1;
        }
        else {
          pcVar2 = param_1;
          if (param_4 != (int *)0x0) {
            pcVar2 = param_1 + -((uint)param_1 % (uint)param_4);
          }
          iVar3 = crt_read(piVar1[4],pcVar5,(uint)pcVar2);
          if (iVar3 == 0) {
            piVar1[3] = piVar1[3] | 0x10;
LAB_00461c02:
            return (uint)((int)pcVar6 - (int)param_1) / param_2;
          }
          if (iVar3 == -1) {
            piVar1[3] = piVar1[3] | 0x20;
            goto LAB_00461c02;
          }
          param_1 = param_1 + -iVar3;
          pcVar5 = pcVar5 + iVar3;
        }
      }
      else {
        size = param_1;
        if (pcVar2 <= param_1) {
          size = pcVar2;
        }
        crt_bufcpy(pcVar5,(void *)*piVar1,(size_t)size);
        param_1 = param_1 + -(int)size;
        piVar1[1] = piVar1[1] - (int)size;
        *piVar1 = (int)(size + *piVar1);
        pcVar5 = pcVar5 + (int)size;
      }
    } while (param_1 != (char *)0x0);
  }
  return param_3;
}



/* crt_ftell @ 00461c0e */

/* CRT: ftell with file lock */

int __cdecl crt_ftell(char *param_1)

{
  int iVar1;
  
  crt_lock_file((uint)param_1);
  iVar1 = crt_ftell_nolock(param_1);
  crt_unlock_file((uint)param_1);
  return iVar1;
}



/* crt_ftell_nolock @ 00461c30 */

/* CRT: ftell without lock */

int __cdecl crt_ftell_nolock(char *param_1)

{
  uint fd;
  uint uVar1;
  byte bVar2;
  int *piVar3;
  char *pcVar4;
  long lVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  int local_c;
  int local_8;
  
  pcVar7 = param_1;
  fd = *(uint *)(param_1 + 0x10);
  if (*(int *)(param_1 + 4) < 0) {
    param_1[4] = '\0';
    param_1[5] = '\0';
    param_1[6] = '\0';
    param_1[7] = '\0';
  }
  local_8 = crt_lseek(fd,0,1);
  if (local_8 < 0) {
LAB_00461cbe:
    local_c = -1;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0xc);
    if ((uVar1 & 0x108) == 0) {
      return local_8 - *(int *)(param_1 + 4);
    }
    pcVar4 = *(char **)param_1;
    pcVar6 = *(char **)(param_1 + 8);
    local_c = (int)pcVar4 - (int)pcVar6;
    if ((uVar1 & 3) == 0) {
      if ((uVar1 & 0x80) == 0) {
        piVar3 = crt_errno_ptr();
        *piVar3 = 0x16;
        goto LAB_00461cbe;
      }
    }
    else {
      pcVar8 = pcVar6;
      if (((uint)(&crt_pioinfo_table)[(int)fd >> 5][(fd & 0x1f) * 9 + 1] & 0x80) != 0) {
        for (; pcVar8 < pcVar4; pcVar8 = pcVar8 + 1) {
          if (*pcVar8 == '\n') {
            local_c = local_c + 1;
          }
        }
      }
    }
    if (local_8 != 0) {
      if ((param_1[0xc] & 1U) != 0) {
        if (*(int *)(param_1 + 4) == 0) {
          local_c = 0;
        }
        else {
          pcVar4 = pcVar4 + (*(int *)(param_1 + 4) - (int)pcVar6);
          if (((uint)(&crt_pioinfo_table)[(int)fd >> 5][(fd & 0x1f) * 9 + 1] & 0x80) != 0) {
            lVar5 = crt_lseek(fd,0,2);
            if (lVar5 == local_8) {
              pcVar6 = *(char **)(param_1 + 8);
              pcVar8 = pcVar4 + (int)pcVar6;
              param_1 = pcVar4;
              for (; pcVar6 < pcVar8; pcVar6 = pcVar6 + 1) {
                if (*pcVar6 == '\n') {
                  param_1 = param_1 + 1;
                }
              }
              bVar2 = pcVar7[0xd] & 0x20;
            }
            else {
              crt_lseek(fd,local_8,0);
              pcVar7 = (char *)0x200;
              if ((((char *)0x200 < pcVar4) || ((*(uint *)(param_1 + 0xc) & 8) == 0)) ||
                 ((*(uint *)(param_1 + 0xc) & 0x400) != 0)) {
                pcVar7 = *(char **)(param_1 + 0x18);
              }
              bVar2 = *(byte *)((&crt_pioinfo_table)[(int)fd >> 5] + (fd & 0x1f) * 9 + 1) & 4;
              param_1 = pcVar7;
            }
            pcVar4 = param_1;
            if (bVar2 != 0) {
              pcVar4 = param_1 + 1;
            }
          }
          param_1 = pcVar4;
          local_8 = local_8 - (int)param_1;
        }
      }
      local_c = local_c + local_8;
    }
  }
  return local_c;
}



/* crt_fseek @ 00461d91 */

/* fseek wrapper with CRT lock/unlock */

int __cdecl crt_fseek(int *param_1,int param_2,DWORD param_3)

{
  int iVar1;
  
  crt_lock_file((uint)param_1);
  iVar1 = crt_fseek_nolock(param_1,param_2,param_3);
  crt_unlock_file((uint)param_1);
  return iVar1;
}



/* crt_fseek_nolock @ 00461dbd */

/* fseek implementation (uses crt_lseek) */

int __cdecl crt_fseek_nolock(int *param_1,int param_2,DWORD param_3)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  int *piVar4;
  
  if (((param_1[3] & 0x83U) == 0) || (((param_3 != 0 && (param_3 != 1)) && (param_3 != 2)))) {
    piVar4 = crt_errno_ptr();
    *piVar4 = 0x16;
    iVar2 = -1;
  }
  else {
    param_1[3] = param_1[3] & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = crt_ftell_nolock((char *)param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    crt_flushbuf(param_1);
    uVar1 = param_1[3];
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        param_1[6] = 0x200;
      }
    }
    else {
      param_1[3] = uVar1 & 0xfffffffc;
    }
    lVar3 = crt_lseek(param_1[4],param_2,param_3);
    iVar2 = (lVar3 != -1) - 1;
  }
  return iVar2;
}



/* crt_snprintf @ 00461e4a */

/* CRT: size-limited sprintf */

int __cdecl crt_snprintf(char *dst,int size,char *fmt,...)

{
  int iVar1;
  char *local_24;
  int local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_1c = dst;
  local_24 = dst;
  local_18 = 0x42;
  local_20 = size;
  iVar1 = crt_output((int *)&local_24,(byte *)fmt,(undefined4 *)&stack0x00000010);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    crt_flsbuf(0,(int *)&local_24);
  }
  else {
    *local_24 = '\0';
  }
  return iVar1;
}



/* crt_tolower @ 00461e9b */

/* CRT: tolower (current locale) */

int __cdecl crt_tolower(int c)

{
  void *extraout_ECX;
  int unaff_EDI;
  bool bVar1;
  void *this;
  
  if (crt_locale_id == 0) {
    if ((0x40 < c) && (c < 0x5b)) {
      return c + 0x20;
    }
  }
  else {
    InterlockedIncrement((LONG *)&crt_lock_count);
    bVar1 = crt_sbh_reserved_a != 0;
    this = extraout_ECX;
    if (bVar1) {
      InterlockedDecrement((LONG *)&crt_lock_count);
      this = (void *)0x13;
      crt_lock(0x13);
    }
    c = crt_tolower_l(this,(void *)c,unaff_EDI);
    if (bVar1) {
      crt_unlock(0x13);
    }
    else {
      InterlockedDecrement((LONG *)&crt_lock_count);
    }
  }
  return c;
}



/* crt_tolower_l @ 00461f0a */

/* CRT: tolower with locale */

int __thiscall crt_tolower_l(void *this,void *locale,int c)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  void *local_8;
  
  pvVar1 = locale;
  if (crt_locale_id == 0) {
    if ((0x40 < (int)locale) && ((int)locale < 0x5b)) {
      pvVar1 = (void *)((int)locale + 0x20);
    }
  }
  else {
    iVar3 = 1;
    local_8 = this;
    if ((int)locale < 0x100) {
      if (crt_locale_type < 2) {
        uVar2 = (byte)crt_ctype_table[(int)locale * 2] & 1;
      }
      else {
        uVar2 = crt_isctype(this,(int)locale,1);
      }
      if (uVar2 == 0) {
        return (int)pvVar1;
      }
    }
    if ((crt_ctype_table[((int)pvVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      locale = (void *)(CONCAT31((int3)((uint)locale >> 8),(char)pvVar1) & 0xffff00ff);
    }
    else {
      uVar2 = (uint)locale >> 0x10;
      locale._0_2_ = CONCAT11((char)pvVar1,(char)((uint)pvVar1 >> 8));
      locale = (void *)(CONCAT22((short)uVar2,locale._0_2_) & 0xff00ffff);
      iVar3 = 2;
    }
    iVar3 = crt_lcmap_string(crt_locale_id,0x100,(char *)&locale,iVar3,(ushort *)&local_8,3,0,1);
    if (iVar3 != 0) {
      if (iVar3 == 1) {
        pvVar1 = (void *)((uint)local_8 & 0xff);
      }
      else {
        pvVar1 = (void *)((uint)local_8 & 0xffff);
      }
    }
  }
  return (int)pvVar1;
}



/* __alldiv @ 00462020 */

/* Library Function - Single Match
    __alldiv
   
   Library: Visual Studio */

undefined8 __alldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar10;
  char cVar11;
  uint uVar9;
  
  cVar11 = (int)param_2 < 0;
  if ((bool)cVar11) {
    bVar10 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uint)bVar10 - param_2;
  }
  if ((int)param_4 < 0) {
    cVar11 = cVar11 + '\x01';
    bVar10 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uint)bVar10 - param_4;
  }
  uVar3 = param_1;
  uVar5 = param_3;
  uVar6 = param_2;
  uVar9 = param_4;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar8 = uVar9 >> 1;
      uVar5 = uVar5 >> 1 | (uint)((uVar9 & 1) != 0) << 0x1f;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar6 & 1) != 0) << 0x1f;
      uVar6 = uVar7;
      uVar9 = uVar8;
    } while (uVar8 != 0);
    uVar1 = CONCAT44(uVar7,uVar3) / (ulonglong)uVar5;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar5 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar5)) ||
       ((param_2 <= uVar5 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  if (cVar11 == '\x01') {
    bVar10 = iVar4 != 0;
    iVar4 = -iVar4;
    uVar3 = -(uint)bVar10 - uVar3;
  }
  return CONCAT44(uVar3,iVar4);
}



/* __allmul @ 004620d0 */

/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}



/* crt_toupper @ 00462104 */

/* CRT: toupper (current locale) */

int __cdecl crt_toupper(int c)

{
  void *extraout_ECX;
  int unaff_EDI;
  bool bVar1;
  void *this;
  
  if (crt_locale_id == 0) {
    if ((0x60 < c) && (c < 0x7b)) {
      return c + -0x20;
    }
  }
  else {
    InterlockedIncrement((LONG *)&crt_lock_count);
    bVar1 = crt_sbh_reserved_a != 0;
    this = extraout_ECX;
    if (bVar1) {
      InterlockedDecrement((LONG *)&crt_lock_count);
      this = (void *)0x13;
      crt_lock(0x13);
    }
    c = crt_toupper_l(this,(void *)c,unaff_EDI);
    if (bVar1) {
      crt_unlock(0x13);
    }
    else {
      InterlockedDecrement((LONG *)&crt_lock_count);
    }
  }
  return c;
}



/* crt_toupper_l @ 00462173 */

/* CRT: toupper with locale */

int __thiscall crt_toupper_l(void *this,void *locale,int c)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  void *local_8;
  
  pvVar1 = locale;
  if (crt_locale_id == 0) {
    if ((0x60 < (int)locale) && ((int)locale < 0x7b)) {
      pvVar1 = (void *)((int)locale - 0x20);
    }
  }
  else {
    local_8 = this;
    if ((int)locale < 0x100) {
      if (crt_locale_type < 2) {
        uVar2 = (byte)crt_ctype_table[(int)locale * 2] & 2;
      }
      else {
        uVar2 = crt_isctype(this,(int)locale,2);
      }
      if (uVar2 == 0) {
        return (int)pvVar1;
      }
    }
    if ((crt_ctype_table[((int)pvVar1 >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      locale = (void *)(CONCAT31((int3)((uint)locale >> 8),(char)pvVar1) & 0xffff00ff);
      iVar3 = 1;
    }
    else {
      uVar2 = (uint)locale >> 0x10;
      locale._0_2_ = CONCAT11((char)pvVar1,(char)((uint)pvVar1 >> 8));
      locale = (void *)(CONCAT22((short)uVar2,locale._0_2_) & 0xff00ffff);
      iVar3 = 2;
    }
    iVar3 = crt_lcmap_string(crt_locale_id,0x200,(char *)&locale,iVar3,(ushort *)&local_8,3,0,1);
    if (iVar3 != 0) {
      if (iVar3 == 1) {
        pvVar1 = (void *)((uint)local_8 & 0xff);
      }
      else {
        pvVar1 = (void *)((uint)local_8 & 0xffff);
      }
    }
  }
  return (int)pvVar1;
}



/* crt_beginthread @ 0046223f */

/* CRT: beginthread (CreateThread wrapper) */

void * __cdecl crt_beginthread(void *start,uint stack_size,void *arg)

{
  void *lpThreadId;
  HANDLE hThread;
  DWORD DVar1;
  
  DVar1 = 0;
  lpThreadId = crt_calloc(1,0x74);
  if (lpThreadId != (void *)0x0) {
    crt_init_thread_data(lpThreadId);
    *(void **)((int)lpThreadId + 0x48) = start;
    *(void **)((int)lpThreadId + 0x4c) = arg;
    hThread = CreateThread((LPSECURITY_ATTRIBUTES)0x0,stack_size,crt_thread_entry,lpThreadId,4,
                           lpThreadId);
    *(HANDLE *)((int)lpThreadId + 4) = hThread;
    if ((hThread != (HANDLE)0x0) && (DVar1 = ResumeThread(hThread), DVar1 != 0xffffffff)) {
      return hThread;
    }
    DVar1 = GetLastError();
  }
  crt_free_base(lpThreadId);
  if (DVar1 != 0) {
    crt_dosmaperr(DVar1);
  }
  return (void *)0xffffffff;
}



/* crt_thread_entry @ 004622b6 */

/* CRT: thread start trampoline */

uint crt_thread_entry(void *thread_data)

{
  LPVOID pvVar1;
  WINBOOL WVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fa10;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  pvVar1 = TlsGetValue(crt_tls_slot_index);
  if (pvVar1 != (LPVOID)0x0) {
    *(undefined4 *)((int)pvVar1 + 0x48) = *(undefined4 *)((int)thread_data + 0x48);
    *(undefined4 *)((int)pvVar1 + 0x4c) = *(undefined4 *)((int)thread_data + 0x4c);
    crt_free_thread_data(thread_data);
    thread_data = pvVar1;
  }
  WVar2 = TlsSetValue(crt_tls_slot_index,thread_data);
  if (WVar2 == 0) {
    __amsg_exit(0x10);
  }
  if (PTR_FUN_0047b164 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0047b164)();
  }
  local_8 = 0;
  (**(code **)((int)thread_data + 0x48))(*(undefined4 *)((int)thread_data + 0x4c));
  crt_endthread();
  ExceptionList = local_14;
  return 0;
}



/* crt_endthread @ 00462373 */

/* CRT: thread cleanup and exit */

void crt_endthread(void)

{
  DWORD *pDVar1;
  
  if (PTR_FUN_0047b168 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0047b168)();
  }
  pDVar1 = crt_get_thread_data();
  if (pDVar1 == (DWORD *)0x0) {
    __amsg_exit(0x10);
  }
  if ((HANDLE)pDVar1[1] != (HANDLE)0xffffffff) {
    CloseHandle((HANDLE)pDVar1[1]);
  }
  crt_free_thread_data((undefined *)pDVar1);
                    /* WARNING: Subroutine does not return */
  ExitThread(0);
}



/* FUN_004623b2 @ 004623b2 */

/* [binja] int32_t sub_4623b2(int32_t* arg1) */

int __cdecl FUN_004623b2(int *arg1)

{
  DWORD DVar1;
  long lVar2;
  _TIME_ZONE_INFORMATION local_d0;
  _SYSTEMTIME local_24;
  _SYSTEMTIME local_14;
  
  GetLocalTime(&local_14);
  GetSystemTime(&local_24);
  if (local_24.wMinute == crt_cached_time._2_2_) {
    if (local_24.wHour == (WORD)crt_cached_time) {
      if (local_24.wDay == crt_time_init_done._2_2_) {
        if (local_24.wMonth == crt_cached_date._2_2_) {
          if (local_24.wYear == (WORD)crt_cached_date) goto LAB_0046245c;
        }
      }
    }
  }
  DVar1 = GetTimeZoneInformation(&local_d0);
  if (DVar1 == 0xffffffff) {
    crt_time_compare_result = -1;
  }
  else if (((DVar1 == 2) && (local_d0.DaylightDate.wMonth != 0)) && (local_d0.DaylightBias != 0)) {
    crt_time_compare_result = 1;
  }
  else {
    crt_time_compare_result = 0;
  }
  crt_cached_date._0_2_ = local_24.wYear;
  crt_cached_date._2_2_ = local_24.wMonth;
  crt_time_init_done._0_2_ = local_24.wDayOfWeek;
  crt_time_init_done._2_2_ = local_24.wDay;
  crt_cached_time._0_2_ = local_24.wHour;
  crt_cached_time._2_2_ = local_24.wMinute;
  crt_cached_seconds_ms._0_2_ = local_24.wSecond;
  crt_cached_seconds_ms._2_2_ = local_24.wMilliseconds;
LAB_0046245c:
  lVar2 = crt_mktime((uint)local_14.wYear,(uint)local_14.wMonth,(uint)local_14.wDay,
                     (uint)local_14.wHour,(uint)local_14.wMinute,(uint)local_14.wSecond,crt_time_compare_result
                    );
  if (arg1 != (int *)0x0) {
    *arg1 = lVar2;
  }
  return lVar2;
}



/* crt_getcwd @ 0046248e */

/* CRT: get current working directory */

char * __cdecl crt_getcwd(char *buf,uint size)

{
  char *pcVar1;
  
  crt_lock(0xc);
  pcVar1 = crt_getdcwd(0,buf,size);
  crt_unlock(0xc);
  return pcVar1;
}



/* crt_getdcwd @ 004624b5 */

/* CRT: get current working directory for drive */

char * __cdecl crt_getdcwd(int drive,char *buf,uint size)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;
  DWORD DVar5;
  uint _Size;
  char *pcVar6;
  CHAR local_10c [260];
  LPSTR local_8;
  
  iVar1 = drive;
  if (drive == 0) {
    DVar5 = GetCurrentDirectoryA(0x104,local_10c);
  }
  else {
    iVar2 = FUN_0046258a(drive);
    if (iVar2 == 0) {
      puVar3 = crt_doserrno_ptr();
      *puVar3 = 0xf;
      piVar4 = crt_errno_ptr();
      *piVar4 = 0xd;
      return (char *)0x0;
    }
    drive = (int)CONCAT12(0x2e,CONCAT11(0x3a,(char)iVar1 + '@'));
    DVar5 = GetFullPathNameA((LPCSTR)&drive,0x104,local_10c,&local_8);
  }
  if ((DVar5 != 0) && (_Size = DVar5 + 1, _Size < 0x105)) {
    if (buf == (char *)0x0) {
      if ((int)_Size <= (int)size) {
        _Size = size;
      }
      pcVar6 = _malloc(_Size);
      if (pcVar6 != (char *)0x0) {
LAB_00462576:
        pcVar6 = crt_strcpy(pcVar6,local_10c);
        return pcVar6;
      }
      piVar4 = crt_errno_ptr();
      *piVar4 = 0xc;
    }
    else {
      pcVar6 = buf;
      if ((int)_Size <= (int)size) goto LAB_00462576;
      piVar4 = crt_errno_ptr();
      *piVar4 = 0x22;
    }
  }
  return (char *)0x0;
}



/* FUN_0046258a @ 0046258a */

/* [binja] int32_t sub_46258a(int32_t arg1) */

int __cdecl FUN_0046258a(int arg1)

{
  char cVar1;
  UINT UVar2;
  
  if (arg1 != 0) {
    cVar1 = (char)arg1;
    arg1 = (int)CONCAT12(0x5c,CONCAT11(0x3a,cVar1 + '@'));
    UVar2 = GetDriveTypeA((LPCSTR)&arg1);
    if ((UVar2 == 0) || (UVar2 == 1)) {
      return 0;
    }
  }
  return 1;
}



/* crt_free_base @ 004625c1 */

/* CRT heap free implementation */

void __cdecl crt_free_base(void *ptr)

{
  char *pcVar1;
  void *local_2c;
  char *local_28;
  uint local_24;
  char *local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fa20;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  if (ptr == (void *)0x0) {
    return;
  }
  if (crt_heap_mode == 3) {
    ExceptionList = &local_14;
    crt_lock(9);
    local_8 = 0;
    local_20 = crt_sbh_find_region(ptr);
    if (local_20 != (char *)0x0) {
      crt_sbh_free_block(local_20,ptr);
    }
    local_8 = 0xffffffff;
    FUN_0046262b();
    pcVar1 = local_20;
  }
  else {
    ExceptionList = &local_14;
    if (crt_heap_mode != 2) goto LAB_0046268d;
    ExceptionList = &local_14;
    crt_lock(9);
    local_8 = 1;
    local_28 = crt_sbh_find_block(ptr,&local_2c,&local_24);
    if (local_28 != (char *)0x0) {
      crt_sbh_decommit_pages(local_2c,local_24,local_28);
    }
    local_8 = 0xffffffff;
    FUN_00462683();
    pcVar1 = local_28;
  }
  if (pcVar1 != (char *)0x0) {
    ExceptionList = local_14;
    return;
  }
LAB_0046268d:
  HeapFree(crt_heap_handle,0,ptr);
  ExceptionList = local_14;
  return;
}



/* FUN_0046262b @ 0046262b */

/* [binja] int32_t sub_46262b() */

int FUN_0046262b(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* FUN_00462683 @ 00462683 */

/* [binja] int32_t sub_462683() */

int FUN_00462683(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* crt_realloc @ 004626aa */

/* CRT: realloc with heap mode handling and new-handler retry */

void * __cdecl crt_realloc(void *ptr,size_t size)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  LPVOID pvVar4;
  byte *arg3;
  void *local_3c;
  uint local_38;
  byte *local_34;
  void **local_30;
  int *local_2c;
  byte *local_28;
  void *local_24;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fa38;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  arg3 = (byte *)0x0;
  if (ptr == (void *)0x0) {
    ExceptionList = &local_14;
    pvVar1 = _malloc(size);
  }
  else {
    if (size == 0) {
      ExceptionList = &local_14;
      crt_free_base(ptr);
    }
    else {
      ExceptionList = &local_14;
      if (crt_heap_mode == 3) {
        do {
          local_28 = (void *)0x0;
          if (size < (void *)0xffffffe1) {
            crt_lock(9);
            local_8 = 0;
            local_2c = crt_sbh_find_region(ptr);
            if (local_2c != (int *)0x0) {
              if (size <= crt_sbh_reserved_b) {
                iVar2 = FUN_00467484(local_2c,ptr,(void *)size);
                if (iVar2 == 0) {
                  local_28 = crt_sbh_alloc(size);
                  if (local_28 != (void *)0x0) {
                    local_24 = (void *)(*(int *)((int)ptr + -4) - 1);
                    pvVar1 = local_24;
                    if (size <= local_24) {
                      pvVar1 = (void *)size;
                    }
                    crt_bufcpy(local_28,ptr,(size_t)pvVar1);
                    local_2c = crt_sbh_find_region(ptr);
                    crt_sbh_free_block(local_2c,ptr);
                  }
                }
                else {
                  local_28 = ptr;
                }
              }
              if (local_28 == (void *)0x0) {
                if ((void *)size == (void *)0x0) {
                  size = 1;
                }
                size = size + 0xf & 0xfffffff0;
                local_28 = HeapAlloc(crt_heap_handle,0,size);
                if (local_28 != (LPVOID)0x0) {
                  local_24 = (void *)(*(int *)((int)ptr + -4) - 1);
                  pvVar1 = local_24;
                  if (size <= local_24) {
                    pvVar1 = (void *)size;
                  }
                  crt_bufcpy(local_28,ptr,(size_t)pvVar1);
                  crt_sbh_free_block(local_2c,ptr);
                }
              }
            }
            local_8 = 0xffffffff;
            FUN_00462835();
            if (local_2c == (int *)0x0) {
              if ((void *)size == (void *)0x0) {
                size = 1;
              }
              size = size + 0xf & 0xfffffff0;
              local_28 = HeapReAlloc(crt_heap_handle,0,ptr,size);
            }
          }
          if (local_28 != (void *)0x0) {
            ExceptionList = local_14;
            return local_28;
          }
          if (crt_nh_malloc_flag == (byte *)0x0) {
            ExceptionList = local_14;
            return (void *)0x0;
          }
          iVar2 = crt_call_new_handler(size);
        } while (iVar2 != 0);
      }
      else {
        ExceptionList = &local_14;
        if (crt_heap_mode == 2) {
          ExceptionList = &local_14;
          if (size < 0xffffffe1) {
            if (size == 0) {
              size = 0x10;
              ExceptionList = &local_14;
            }
            else {
              size = size + 0xf & 0xfffffff0;
              ExceptionList = &local_14;
            }
          }
          do {
            local_28 = arg3;
            if (size < 0xffffffe1) {
              crt_lock(9);
              local_8 = 1;
              arg3 = crt_sbh_find_block(ptr,&local_3c,(uint *)&local_30);
              local_34 = arg3;
              if (arg3 == (byte *)0x0) {
                local_28 = HeapReAlloc(crt_heap_handle,0,ptr,size);
              }
              else {
                if (size < crt_timezone_data_block) {
                  iVar2 = FUN_00467d9e(local_3c,local_30,(char *)arg3,size >> 4);
                  if (iVar2 == 0) {
                    local_28 = crt_sbh_alloc_units(size >> 4);
                    if (local_28 != (byte *)0x0) {
                      local_38 = (uint)*arg3 << 4;
                      uVar3 = local_38;
                      if (size <= local_38) {
                        uVar3 = size;
                      }
                      crt_bufcpy(local_28,ptr,uVar3);
                      crt_sbh_decommit_pages(local_3c,(int)local_30,(char *)arg3);
                    }
                  }
                  else {
                    local_28 = ptr;
                  }
                }
                if ((local_28 == (byte *)0x0) &&
                   (local_28 = HeapAlloc(crt_heap_handle,0,size), local_28 != (byte *)0x0)) {
                  local_38 = (uint)*arg3 << 4;
                  uVar3 = local_38;
                  if (size <= local_38) {
                    uVar3 = size;
                  }
                  crt_bufcpy(local_28,ptr,uVar3);
                  crt_sbh_decommit_pages(local_3c,(int)local_30,(char *)arg3);
                }
              }
              local_8 = 0xffffffff;
              FUN_00462983();
            }
            if (local_28 != arg3) {
              ExceptionList = local_14;
              return local_28;
            }
            if (crt_nh_malloc_flag == arg3) {
              ExceptionList = local_14;
              return local_28;
            }
            iVar2 = crt_call_new_handler(size);
          } while (iVar2 != 0);
        }
        else {
          do {
            pvVar4 = (LPVOID)0x0;
            if (size < 0xffffffe1) {
              if (size == 0) {
                size = 1;
              }
              size = size + 0xf & 0xfffffff0;
              pvVar4 = HeapReAlloc(crt_heap_handle,0,ptr,size);
            }
            if (pvVar4 != (LPVOID)0x0) {
              ExceptionList = local_14;
              return pvVar4;
            }
            if (crt_nh_malloc_flag == (byte *)0x0) {
              ExceptionList = local_14;
              return (void *)0x0;
            }
            iVar2 = crt_call_new_handler(size);
          } while (iVar2 != 0);
        }
      }
    }
    pvVar1 = (void *)0x0;
  }
  ExceptionList = local_14;
  return pvVar1;
}



/* FUN_00462835 @ 00462835 */

/* [binja] int32_t sub_462835() */

int FUN_00462835(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* FUN_00462983 @ 00462983 */

/* [binja] int32_t sub_462983() */

int FUN_00462983(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* _malloc @ 004629d9 */

/* Library Function - Single Match
    _malloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(_Size,crt_nh_malloc_flag);
  return pvVar1;
}



/* __nh_malloc @ 004629eb */

/* Library Function - Single Match
    __nh_malloc
   
   Library: Visual Studio 2003 Release */

void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  void *pvVar1;
  int iVar2;
  
  if (_Size < 0xffffffe1) {
    do {
      pvVar1 = FUN_00462a17(_Size);
      if (pvVar1 != (void *)0x0) {
        return pvVar1;
      }
      if (_NhFlag == 0) {
        return (void *)0x0;
      }
      iVar2 = crt_call_new_handler(_Size);
    } while (iVar2 != 0);
  }
  return (void *)0x0;
}



/* FUN_00462a17 @ 00462a17 */

/* [binja] void* sub_462a17(uint32_t arg1) */

void * __cdecl FUN_00462a17(uint arg1)

{
  void *pvVar1;
  LPVOID pvVar2;
  uint dwBytes;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fa50;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  if (crt_heap_mode == 3) {
    ExceptionList = &local_14;
    if (arg1 <= crt_sbh_reserved_b) {
      ExceptionList = &local_14;
      crt_lock(9);
      local_8 = 0;
      pvVar1 = crt_sbh_alloc(arg1);
      local_8 = 0xffffffff;
      FUN_00462a7e();
      if (pvVar1 != (void *)0x0) {
        ExceptionList = local_14;
        return pvVar1;
      }
    }
  }
  else {
    ExceptionList = &local_14;
    if (crt_heap_mode == 2) {
      if (arg1 == 0) {
        dwBytes = 0x10;
      }
      else {
        dwBytes = arg1 + 0xf & 0xfffffff0;
      }
      ExceptionList = &local_14;
      if (dwBytes <= crt_timezone_data_block) {
        ExceptionList = &local_14;
        crt_lock(9);
        local_8 = 1;
        pvVar1 = crt_sbh_alloc_units(dwBytes >> 4);
        local_8 = 0xffffffff;
        FUN_00462add();
        if (pvVar1 != (void *)0x0) {
          ExceptionList = local_14;
          return pvVar1;
        }
      }
      goto LAB_00462af6;
    }
  }
  if (arg1 == 0) {
    arg1 = 1;
  }
  dwBytes = arg1 + 0xf & 0xfffffff0;
LAB_00462af6:
  pvVar2 = HeapAlloc(crt_heap_handle,0,dwBytes);
  ExceptionList = local_14;
  return pvVar2;
}



/* FUN_00462a7e @ 00462a7e */

/* [binja] int32_t sub_462a7e() */

int FUN_00462a7e(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* FUN_00462add @ 00462add */

/* [binja] int32_t sub_462add() */

int FUN_00462add(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* _strstr @ 00462b20 */

/* Library Function - Single Match
    _strstr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strstr(char *_Str,char *_SubStr)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint *puVar9;
  char *pcVar10;
  
  cVar3 = *_SubStr;
  if (cVar3 == '\0') {
    return _Str;
  }
  if (_SubStr[1] == '\0') {
    while (((uint)_Str & 3) != 0) {
      uVar4 = *(uint *)_Str;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)_Str;
      }
      _Str = (char *)((int)_Str + 1);
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar4 = *(uint *)_Str;
        uVar7 = uVar4 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar6 = uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff;
        puVar9 = (uint *)((int)_Str + 4);
        if (((uVar7 ^ 0xffffffff ^ uVar7 + 0x7efefeff) & 0x81010100) != 0) break;
        _Str = (char *)puVar9;
        if ((uVar6 & 0x81010100) != 0) {
          if ((uVar6 & 0x1010100) != 0) {
            return (char *)0x0;
          }
          if ((uVar4 + 0x7efefeff & 0x80000000) == 0) {
            return (char *)0x0;
          }
        }
      }
      uVar4 = *(uint *)_Str;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)_Str;
      }
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 8);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 1);
      }
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 0x10);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 2);
      }
      if (cVar5 == '\0') break;
      cVar5 = (char)(uVar4 >> 0x18);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 3);
      }
      _Str = (char *)puVar9;
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
    }
    return (char *)0x0;
  }
  do {
    cVar5 = *_Str;
    do {
      while (_Str = _Str + 1, cVar5 != cVar3) {
        if (cVar5 == '\0') {
          return (char *)0x0;
        }
        cVar5 = *_Str;
      }
      cVar5 = *_Str;
      pcVar10 = _Str + 1;
      pcVar8 = _SubStr;
    } while (cVar5 != _SubStr[1]);
    do {
      if (pcVar8[2] == '\0') {
LAB_00462b93:
        return _Str + -1;
      }
      if (*pcVar10 != pcVar8[2]) break;
      pcVar1 = pcVar8 + 3;
      if (*pcVar1 == '\0') goto LAB_00462b93;
      pcVar2 = pcVar10 + 1;
      pcVar8 = pcVar8 + 2;
      pcVar10 = pcVar10 + 2;
    } while (*pcVar1 == *pcVar2);
  } while( true );
}



/* FUN_00462ba0 @ 00462ba0 */

/* [binja] int32_t sub_462ba0(char* arg1, char* arg2) */

int __cdecl FUN_00462ba0(char *arg1,char *arg2)

{
  int iVar1;
  void *this;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  local_18 = 0x49;
  local_1c = arg1;
  local_24 = arg1;
  local_20 = _strlen(arg1);
  iVar1 = FUN_00467e62(this,(int *)&local_24,(byte *)arg2,(undefined4 *)&stack0x0000000c);
  return iVar1;
}



/* crt_qsort @ 00462bd4 */

/* CRT: quicksort with callback (cmp) */

void __cdecl crt_qsort(void *base,size_t num,size_t size,void *cmp)

{
  char *pcVar1;
  uint uVar2;
  char *b;
  int iVar3;
  char *hi;
  char *b_00;
  undefined1 local_fc [120];
  undefined1 local_84 [120];
  char *local_c;
  int local_8;
  
  if ((num < 2) || (size == 0)) {
    return;
  }
  local_8 = 0;
  iVar3 = num - 1;
  num = (size_t)local_fc;
  hi = (char *)(iVar3 * size + (int)base);
  b = base;
  base = local_84;
LAB_00462c13:
  uVar2 = (uint)((int)hi - (int)b) / size + 1;
  if (8 < uVar2) {
    crt_swap(b + (uVar2 >> 1) * size,b,size);
    b_00 = hi + size;
    local_c = b;
LAB_00462c6a:
    local_c = local_c + size;
    if (local_c <= hi) goto code_r0x00462c77;
    goto LAB_00462c82;
  }
  crt_shortsort(b,hi,size,cmp);
  goto LAB_00462c32;
code_r0x00462c77:
  iVar3 = (*cmp)(local_c,b);
  if (iVar3 < 1) goto LAB_00462c6a;
LAB_00462c82:
  do {
    b_00 = b_00 + -size;
    if (b_00 <= b) break;
    iVar3 = (*cmp)(b_00,b);
  } while (-1 < iVar3);
  if (local_c <= b_00) {
    crt_swap(local_c,b_00,size);
    goto LAB_00462c6a;
  }
  crt_swap(b,b_00,size);
  pcVar1 = local_c;
  if ((int)(b_00 + (-1 - (int)b)) < (int)hi - (int)local_c) {
    if (local_c < hi) {
      local_8 = local_8 + 1;
      *(char **)num = local_c;
      *(char **)base = hi;
      base = (void *)((int)base + 4);
      num = num + 4;
    }
    if (b + size < b_00) {
      hi = b_00 + -size;
      goto LAB_00462c13;
    }
  }
  else {
    if (b + size < b_00) {
      local_8 = local_8 + 1;
      *(char **)num = b;
      *(size_t *)base = (int)b_00 - size;
      base = (void *)((int)base + 4);
      num = num + 4;
    }
    b = pcVar1;
    if (pcVar1 < hi) goto LAB_00462c13;
  }
LAB_00462c32:
  local_8 = local_8 + -1;
  num = num - 4;
  base = (void *)((int)base + -4);
  if (local_8 < 0) {
    return;
  }
  hi = *(char **)base;
  b = *(char **)num;
  goto LAB_00462c13;
}



/* crt_shortsort @ 00462d28 */

/* CRT: insertion sort for small arrays (cmp) */

void __cdecl crt_shortsort(char *lo,char *hi,size_t width,void *cmp)

{
  int iVar1;
  char *a;
  char *pcVar2;
  
  for (; a = lo, pcVar2 = lo, lo < hi; hi = hi + -width) {
    while (pcVar2 = pcVar2 + width, pcVar2 <= hi) {
      iVar1 = (*cmp)(pcVar2,a);
      if (0 < iVar1) {
        a = pcVar2;
      }
    }
    crt_swap(a,hi,width);
  }
  return;
}



/* crt_swap @ 00462d76 */

/* CRT: swap elements for qsort */

void __cdecl crt_swap(char *a,char *b,size_t width)

{
  char cVar1;
  
  if (a != b) {
    for (; width != 0; width = width - 1) {
      cVar1 = *a;
      *a = *b;
      a = a + 1;
      *b = cVar1;
      b = b + 1;
    }
  }
  return;
}



/* crt_getc @ 00462da2 */

/* CRT: get character with stream lock */

uint __cdecl crt_getc(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  
  crt_lock_file((uint)param_1);
  piVar1 = param_1 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar2 = crt_filbuf(param_1);
  }
  else {
    uVar2 = (uint)*(byte *)*param_1;
    *param_1 = (byte *)*param_1 + 1;
  }
  crt_unlock_file((uint)param_1);
  return uVar2;
}



/* string_compare_nocase @ 00462de0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __thiscall string_compare_nocase(void *this,byte *param_1,byte *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  void *extraout_ECX;
  void *this_00;
  void *extraout_ECX_00;
  void *locale_00;
  uint c;
  void *locale;
  
  iVar3 = _crt_lock_count;
  if (crt_locale_id == 0) {
    bVar6 = 0xff;
    do {
      do {
        cVar7 = '\0';
        if (bVar6 == 0) goto LAB_00462e2e;
        bVar6 = *param_2;
        param_2 = param_2 + 1;
        bVar5 = *param_1;
        param_1 = param_1 + 1;
      } while (bVar5 == bVar6);
      bVar4 = bVar6 + 0xbf + (-((byte)(bVar6 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar5 = bVar5 + 0xbf;
      bVar6 = bVar5 + (-(bVar5 < 0x1a) & 0x20U) + 0x41;
    } while (bVar6 == bVar4);
    cVar7 = (bVar6 < bVar4) * -2 + '\x01';
LAB_00462e2e:
    locale = (void *)(int)cVar7;
  }
  else {
    LOCK();
    _crt_lock_count = _crt_lock_count + 1;
    UNLOCK();
    bVar1 = 0 < crt_sbh_reserved_a;
    if (bVar1) {
      LOCK();
      UNLOCK();
      _crt_lock_count = iVar3;
      crt_lock(0x13);
      this = extraout_ECX;
    }
    c = (uint)bVar1;
    locale = (void *)0xff;
    locale_00 = (void *)0x0;
    do {
      do {
        if ((char)locale == '\0') goto LAB_00462e8f;
        bVar6 = *param_2;
        locale = (void *)CONCAT31((int3)((uint)locale >> 8),bVar6);
        param_2 = param_2 + 1;
        bVar5 = *param_1;
        locale_00 = (void *)CONCAT31((int3)((uint)locale_00 >> 8),bVar5);
        param_1 = param_1 + 1;
      } while (bVar6 == bVar5);
      locale_00 = (void *)crt_tolower_l(this,locale_00,(int)locale);
      locale = (void *)crt_tolower_l(this_00,locale,c);
      this = extraout_ECX_00;
    } while ((byte)locale_00 == (byte)locale);
    uVar2 = (uint)((byte)locale_00 < (byte)locale);
    locale = (void *)((1 - uVar2) - (uint)(uVar2 != 0));
LAB_00462e8f:
    if (c == 0) {
      LOCK();
      _crt_lock_count = _crt_lock_count + -1;
      UNLOCK();
    }
    else {
      crt_unlock(0x13);
    }
  }
  return (uint)locale;
}



/* crt_run_initializers @ 00462eb0 */

/* invokes CRT initializer function ranges */

void crt_run_initializers(void)

{
  if (PTR_FUN_0047b160 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0047b160)();
  }
  crt_call_fn_range((undefined4 *)&DAT_004710e4,(undefined4 *)&DAT_004710f8);
  crt_call_fn_range((undefined4 *)&DAT_00471000,(undefined4 *)&DAT_004710e0);
  return;
}



/* crt_exit @ 00462edd */

/* CRT exit path (atexit/onexit + ExitProcess) */

void __cdecl crt_exit(uint code)

{
  crt_doexit(code,0,0);
  return;
}



/* __exit @ 00462eee */

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 2003 Release */

void __cdecl __exit(int _Code)

{
  crt_doexit(_Code,1,0);
  return;
}



/* crt_doexit @ 00462eff */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CRT exit worker (atexit/onexit + ExitProcess) */

void __cdecl crt_doexit(uint code,int full,int quick)

{
  HANDLE hProcess;
  undefined4 *puVar1;
  uint uExitCode;
  
  crt_exit_lock();
  if (crt_time_state == 1) {
    uExitCode = code;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_004d99bc = 1;
  DAT_004d99b8 = (undefined1)quick;
  if (full == 0) {
    if ((crt_onexit_table_end != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)(crt_onexit_table_begin - 4), crt_onexit_table_end <= puVar1)) {
      do {
        if ((code *)*puVar1 != (code *)0x0) {
          (*(code *)*puVar1)();
        }
        puVar1 = puVar1 + -1;
      } while (crt_onexit_table_end <= puVar1);
    }
    crt_call_fn_range((undefined4 *)&DAT_004710fc,(undefined4 *)&DAT_00471104);
  }
  crt_call_fn_range((undefined4 *)&DAT_00471108,(undefined4 *)&DAT_00471110);
  if (quick == 0) {
    crt_time_state = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(code);
  }
  crt_exit_unlock();
  return;
}



/* crt_exit_lock @ 00462fa4 */

/* exit lock */

void crt_exit_lock(void)

{
  crt_lock(0xd);
  return;
}



/* crt_exit_unlock @ 00462fad */

/* exit unlock */

void crt_exit_unlock(void)

{
  crt_unlock(0xd);
  return;
}



/* crt_call_fn_range @ 00462fb6 */

/* call function pointers in a range */

void __cdecl crt_call_fn_range(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}



/* crt_isalpha @ 00462fd0 */

/* ctype alpha check (MBCS-aware) */

uint __thiscall crt_isalpha(void *this,int c)

{
  uint uVar1;
  
  if (1 < crt_locale_type) {
    uVar1 = crt_isctype(this,c,0x103);
    return uVar1;
  }
  return *(ushort *)(crt_ctype_table + c * 2) & 0x103;
}



/* crt_isspace @ 00462ffe */

/* ctype space check (MBCS-aware) */

uint __thiscall crt_isspace(void *this,int c)

{
  uint uVar1;
  
  if (1 < crt_locale_type) {
    uVar1 = crt_isctype(this,c,8);
    return uVar1;
  }
  return (byte)crt_ctype_table[c * 2] & 8;
}



/* entry @ 00463026 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  uint code;
  _STARTUPINFOA local_60;
  undefined1 *local_1c;
  _EXCEPTION_POINTERS *local_18;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fa68;
  puStack_10 = &LAB_00465e70;
  pvStack_14 = ExceptionList;
  local_1c = &stack0xffffff88;
  ExceptionList = &pvStack_14;
  DVar1 = GetVersion();
  _DAT_004d9990 = DVar1 >> 8 & 0xff;
  _DAT_004d998c = DVar1 & 0xff;
  _DAT_004d9988 = _DAT_004d998c * 0x100 + _DAT_004d9990;
  _DAT_004d9984 = DVar1 >> 0x10;
  iVar2 = crt_heap_init(1);
  if (iVar2 == 0) {
    crt_thread_data_init(0x1c);
  }
  iVar2 = crt_mt_init();
  if (iVar2 == 0) {
    crt_thread_data_init(0x10);
  }
  local_8 = 0;
  crt_io_init();
  crt_command_line_ptr = GetCommandLineA();
  crt_env_string_copy = crt_get_environment_strings();
  crt_build_argv();
  crt_build_environ();
  crt_run_initializers();
  local_60.dwFlags = 0;
  GetStartupInfoA(&local_60);
  crt_skip_program_name();
  GetModuleHandleA((LPCSTR)0x0);
  code = crimsonland_main();
  crt_exit(code);
  crt_exception_filter(local_18->ExceptionRecord->ExceptionCode,local_18);
  return;
}



/* __amsg_exit @ 0046312e */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl __amsg_exit(int param_1)

{
  if (crt_os_type_flag == 1) {
    crt_runtime_error_banner();
  }
  crt_report_runtime_error(param_1);
  (*(code *)PTR___exit_0047b180)(0xff);
  return;
}



/* crt_thread_data_init @ 00463153 */

void __cdecl crt_thread_data_init(DWORD param_1)

{
  if (crt_os_type_flag == 1) {
    crt_runtime_error_banner();
  }
  crt_report_runtime_error(param_1);
                    /* WARNING: Subroutine does not return */
  ExitProcess(0xff);
}



/* FUN_00463180 @ 00463180 */

void FUN_00463180(void)

{
  float10 in_ST0;
  double dVar1;
  
  dVar1 = (double)in_ST0;
  FUN_004651b8(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  FUN_0046319d(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20));
  return;
}



/* FUN_0046319d @ 0046319d */

void __cdecl FUN_0046319d(int param_1,uint param_2)

{
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUControlWord;
  float10 in_ST0;
  float10 extraout_ST0;
  undefined4 unaff_retaddr;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
      FUN_0046515c();
    }
LAB_0046322c:
    if (crt_time_initialized == 0) {
      __startOneArgErrorHandling(&simd_const_a,0xd,in_FPUControlWord,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      in_EAX = FUN_00465145();
      in_ST0 = extraout_ST0;
    }
    if (in_EAX < 0x3ff00000) {
      fpatan(SQRT(((float10)1 - in_ST0) * ((float10)1 + in_ST0)),in_ST0);
    }
    else if ((0x3ff00000 < in_EAX) || ((param_2 & 0xfffff) != 0 || param_1 != 0)) goto LAB_0046322c;
    if (crt_time_initialized == 0) {
      __math_exit(&simd_const_a,0xd,unaff_retaddr,param_1,param_2);
      return;
    }
  }
  return;
}



/* FUN_0046324b @ 0046324b */

bool __cdecl FUN_0046324b(undefined4 param_1,undefined4 param_2)

{
  return (param_2._2_2_ & 0x7ff0) != 0x7ff0;
}



/* FUN_0046325f @ 0046325f */

int __cdecl FUN_0046325f(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00468f58(param_1,(uint)(CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)
                                                ) >> 0x20));
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        iVar1 = 4;
      }
      else if (iVar1 == 3) {
        iVar1 = 2;
      }
      else {
        iVar1 = 1;
      }
      return iVar1;
    }
    return 0x200;
  }
  if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
}



/* FUN_004632f1 @ 004632f1 */

void FUN_004632f1(undefined *UNRECOVERED_JUMPTABLE)

{
  ExceptionList = *(void **)ExceptionList;
                    /* WARNING: Could not recover jumptable at 0x0046331c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)UNRECOVERED_JUMPTABLE)();
  return;
}



/* crt_cxx_copy_ctor @ 00463325 */

/* [binja] int32_t sub_463325(int32_t arg1, void* const arg2) */

int crt_cxx_copy_ctor(int arg1,void *arg2)

{
  int iVar1;
  
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x0046332a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*arg2)();
  return iVar1;
}



/* FUN_0046332c @ 0046332c */

/* [binja] int32_t sub_46332c(int32_t arg1, void* const arg2) */

int FUN_0046332c(int arg1,void *arg2)

{
  int iVar1;
  
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00463331. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (*arg2)();
  return iVar1;
}



/* crt_cxx_move_ctor @ 00463333 */

/* [binja] struct _EXCEPTION_REGISTRATION_RECORD* __stdcall sub_463333(int32_t arg1,
   EXCEPTION_RECORD* arg2) */

void * crt_cxx_move_ctor(int arg1,void *arg2)

{
  void *pvVar1;
  void *pvVar2;
  
  pvVar1 = ExceptionList;
  RtlUnwind((PVOID)arg1,(PVOID)0x46335b,arg2,(PVOID)0x0);
  *(uint *)((int)arg2 + 4) = *(uint *)((int)arg2 + 4) & 0xfffffffd;
  pvVar2 = ExceptionList;
  *(void **)pvVar1 = ExceptionList;
  ExceptionList = pvVar1;
  return pvVar2;
}



/* FUN_00463382 @ 00463382 */

int __cdecl FUN_00463382(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,void *param_4)

{
  int *in_EAX;
  int iVar1;
  
  iVar1 = crt_cxx_frame_handler(param_1,param_2,param_3,param_4,in_EAX,0,(PVOID)0x0,'\0');
  return iVar1;
}



/* FUN_004633b8 @ 004633b8 */

undefined4 __cdecl
FUN_004633b8(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  void *local_18;
  code *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_10 = param_2;
  local_14 = FUN_0046340c;
  local_8 = param_4 + 1;
  local_c = param_1;
  local_18 = ExceptionList;
  ExceptionList = &local_18;
  uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
  ExceptionList = local_18;
  return uVar1;
}



/* FUN_0046340c @ 0046340c */

/* [binja] int32_t sub_46340c(PEXCEPTION_RECORD arg1, PVOID arg2, DWORD arg3) */

int __cdecl FUN_0046340c(PEXCEPTION_RECORD arg1,PVOID arg2,DWORD arg3)

{
  int iVar1;
  
  iVar1 = crt_cxx_frame_handler
                    (arg1,*(PVOID *)((int)arg2 + 0xc),arg3,(void *)0x0,*(int **)((int)arg2 + 8),
                     *(int *)((int)arg2 + 0x10),arg2,'\0');
  return iVar1;
}



/* FUN_00463431 @ 00463431 */

undefined4 __cdecl
FUN_00463431(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  DWORD *pDVar1;
  undefined4 uVar2;
  undefined4 **ppuVar3;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  code *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_c = &stack0xfffffffc;
  local_10 = &stack0xffffffbc;
  local_28 = FUN_004634e7;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x4634b9;
  local_2c = ExceptionList;
  ExceptionList = &local_2c;
  local_34 = param_1;
  local_30 = param_3;
  ppuVar3 = &local_34;
  uVar2 = *param_1;
  pDVar1 = crt_get_thread_data();
  (*(code *)pDVar1[0x1a])(uVar2,ppuVar3);
  if (local_8 != 0) {
    *local_2c = *(undefined4 *)ExceptionList;
  }
  ExceptionList = local_2c;
  return 0;
}



/* FUN_004634e7 @ 004634e7 */

/* [binja] int32_t sub_4634e7(EXCEPTION_RECORD* arg1, void* arg2, DWORD arg3) */

int __cdecl FUN_004634e7(EXCEPTION_RECORD *arg1,void *arg2,DWORD arg3)

{
  int iVar1;
  
  if ((arg1->ExceptionFlags & 0x66) != 0) {
    *(undefined4 *)((int)arg2 + 0x24) = 1;
    return 1;
  }
  crt_cxx_frame_handler
            (arg1,*(PVOID *)((int)arg2 + 0xc),arg3,(void *)0x0,*(int **)((int)arg2 + 8),
             *(int *)((int)arg2 + 0x10),*(PVOID *)((int)arg2 + 0x14),'\x01');
  if (*(int *)((int)arg2 + 0x24) == 0) {
    crt_cxx_move_ctor((int)arg2,arg1);
  }
                    /* WARNING: Could not recover jumptable at 0x00463551. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (**(code **)((int)arg2 + 0x18))();
  return iVar1;
}



/* crt_cxx_match_handler @ 0046355c */

int __cdecl crt_cxx_match_handler(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = *(uint *)(param_1 + 0xc);
  iVar1 = *(int *)(param_1 + 0x10);
  uVar4 = uVar5;
  uVar3 = uVar5;
  while (uVar2 = uVar4, -1 < param_2) {
    if (uVar5 == 0xffffffff) {
      crt_invalid_parameter_noinfo_noreturn();
    }
    uVar5 = uVar5 - 1;
    if (((*(int *)(iVar1 + 4 + uVar5 * 0x14) < param_3) &&
        (param_3 <= *(int *)(iVar1 + uVar5 * 0x14 + 8))) || (uVar4 = uVar2, uVar5 == 0xffffffff)) {
      param_2 = param_2 + -1;
      uVar4 = uVar5;
      uVar3 = uVar2;
    }
  }
  uVar5 = uVar5 + 1;
  *param_4 = uVar5;
  *param_5 = uVar3;
  if ((*(uint *)(param_1 + 0xc) < uVar3) || (uVar3 < uVar5)) {
    crt_invalid_parameter_noinfo_noreturn();
  }
  return iVar1 + uVar5 * 0x14;
}



/* __global_unwind2 @ 004635d8 */

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x4635f0,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}



/* __local_unwind2 @ 0046361a */

/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_004635f8;
  pvStack_1c = ExceptionList;
  ExceptionList = &pvStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_004636ae();
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  ExceptionList = pvStack_1c;
  return;
}



/* __abnormal_termination @ 00463682 */

/* Library Function - Single Match
    __abnormal_termination
   
   Library: Visual Studio */

int __cdecl __abnormal_termination(void)

{
  int iVar1;
  
  iVar1 = 0;
  if ((*(undefined1 **)((int)ExceptionList + 4) == &LAB_004635f8) &&
     (*(int *)((int)ExceptionList + 8) == *(int *)(*(int *)((int)ExceptionList + 0xc) + 0xc))) {
    iVar1 = 1;
  }
  return iVar1;
}



/* __NLG_Notify1 @ 004636a5 */

/* Library Function - Single Match
    __NLG_Notify1
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __fastcall __NLG_Notify1(undefined4 param_1)

{
  undefined4 in_EAX;
  undefined4 unaff_EBP;
  
  simd_const_c = param_1;
  simd_const_b = in_EAX;
  simd_const_d = unaff_EBP;
  return;
}



/* FUN_004636ae @ 004636ae */

void FUN_004636ae(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  simd_const_c = *(undefined4 *)(unaff_EBP + 8);
  simd_const_b = in_EAX;
  simd_const_d = unaff_EBP;
  return;
}



/* FUN_004636c8 @ 004636c8 */

/* [binja] void* const __EH_prolog() */

void * FUN_004636c8(void)

{
  void *unaff_retaddr;
  undefined1 auStack_c [12];
  
  ExceptionList = auStack_c;
  return unaff_retaddr;
}



/* FUN_004636e7 @ 004636e7 */

void __fastcall FUN_004636e7(void *param_1)

{
  FUN_00469e81(param_1,0x10000,0x30000);
  return;
}



/* FUN_004636f9 @ 004636f9 */

/* WARNING: Removing unreachable block (ram,0x0046372e) */

undefined4 FUN_004636f9(void)

{
  return 0;
}



/* FUN_00463737 @ 00463737 */

/* [binja] int32_t sub_463737() */

int FUN_00463737(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  
  hModule = GetModuleHandleA("KERNEL32");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent");
    if (pFVar1 != (FARPROC)0x0) {
      iVar2 = (*pFVar1)(0);
      return iVar2;
    }
  }
  iVar2 = FUN_004636f9();
  return iVar2;
}



/* FUN_00463760 @ 00463760 */

/* [binja] int32_t sub_463760(char* arg1) */

int __cdecl FUN_00463760(char *arg1)

{
  char cVar1;
  undefined *this;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  
  this = (undefined *)(int)*arg1;
  iVar2 = crt_tolower((int)this);
  if (iVar2 != 0x65) {
    do {
      arg1 = arg1 + 1;
      if (crt_locale_type < 2) {
        uVar3 = (byte)crt_ctype_table[*arg1 * 2] & 4;
        this = crt_ctype_table;
      }
      else {
        puVar4 = (undefined *)0x4;
        uVar3 = crt_isctype(this,(int)*arg1,4);
        this = puVar4;
      }
      iVar2 = 0;
    } while (uVar3 != 0);
  }
  iVar2 = CONCAT31((int3)((uint)iVar2 >> 8),*arg1);
  *arg1 = crt_null_char;
  do {
    arg1 = arg1 + 1;
    cVar1 = *arg1;
    *arg1 = (char)iVar2;
    iVar2 = CONCAT31((int3)((uint)iVar2 >> 8),cVar1);
  } while (*arg1 != '\0');
  return iVar2;
}



/* __fassign @ 00463820 */

/* Library Function - Single Match
    __fassign
   
   Library: Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  void *in_ECX;
  void *local_c;
  void *local_8;
  
  if (flag != 0) {
    local_c = in_ECX;
    local_8 = in_ECX;
    crt_fp_encode_single(in_ECX,(uint *)&local_c,(byte *)number);
    *(void **)argument = local_c;
    *(void **)(argument + 4) = local_8;
    return;
  }
  crt_fp_encode_double(in_ECX,(uint *)&number,(byte *)number);
  *(char **)argument = number;
  return;
}



/* FUN_0046385e @ 0046385e */

undefined1 * __cdecl FUN_0046385e(undefined8 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  uint local_2c [6];
  int local_14 [4];
  
  crt_fp_to_string((double)*param_1,local_14,local_2c);
  crt_fp_round_digits(param_2 + (uint)(0 < param_3) + (uint)(local_14[0] == 0x2d),param_3 + 1,
                      local_14);
  crt_fp_format_exp(param_2,param_3,param_4,local_14,0);
  return param_2;
}



/* crt_fp_format_exp @ 004638bf */

/* CRT: formats floating output in scientific notation (adds decimal/exponent) */

char * __cdecl crt_fp_format_exp(char *dst,int precision,int caps,int *fp_info,int force_decimal)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  if ((char)force_decimal != '\0') {
    crt_str_shift_right(dst + (*fp_info == 0x2d),(uint)(0 < precision));
  }
  pcVar2 = dst;
  if (*fp_info == 0x2d) {
    *dst = '-';
    pcVar2 = dst + 1;
  }
  pcVar1 = pcVar2;
  if (0 < precision) {
    pcVar1 = pcVar2 + 1;
    *pcVar2 = pcVar2[1];
    *pcVar1 = crt_null_char;
  }
  pcVar2 = crt_strcpy(pcVar1 + precision + (uint)((char)force_decimal == '\0'),"e+000");
  if (caps != 0) {
    *pcVar2 = 'E';
  }
  if (*(char *)fp_info[3] != '0') {
    iVar3 = fp_info[1] + -1;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
      pcVar2[1] = '-';
    }
    if (99 < iVar3) {
      pcVar2[2] = pcVar2[2] + (char)(iVar3 / 100);
      iVar3 = iVar3 % 100;
    }
    if (9 < iVar3) {
      pcVar2[3] = pcVar2[3] + (char)(iVar3 / 10);
      iVar3 = iVar3 % 10;
    }
    pcVar2[4] = pcVar2[4] + (char)iVar3;
  }
  return dst;
}



/* FUN_00463981 @ 00463981 */

char * __cdecl FUN_00463981(undefined8 *param_1,char *param_2,size_t param_3)

{
  uint local_2c [6];
  int local_14;
  int local_10;
  
  crt_fp_to_string((double)*param_1,&local_14,local_2c);
  crt_fp_round_digits(param_2 + (local_14 == 0x2d),local_10 + param_3,&local_14);
  crt_fp_format_fixed(param_2,param_3,&local_14,0);
  return param_2;
}



/* crt_fp_format_fixed @ 004639d6 */

/* CRT: formats floating output in fixed notation (adds decimal/zeros) */

char * __cdecl crt_fp_format_fixed(char *dst,size_t precision,int *fp_info,int force_decimal)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = fp_info[1];
  if (((char)force_decimal != '\0') && (iVar1 - 1U == precision)) {
    iVar2 = *fp_info;
    dst[(uint)(iVar2 == 0x2d) + (iVar1 - 1U)] = '0';
    (dst + (uint)(iVar2 == 0x2d) + (iVar1 - 1U))[1] = '\0';
  }
  pcVar3 = dst;
  if (*fp_info == 0x2d) {
    *dst = '-';
    pcVar3 = dst + 1;
  }
  if (fp_info[1] < 1) {
    crt_str_shift_right(pcVar3,1);
    *pcVar3 = '0';
    pcVar3 = pcVar3 + 1;
  }
  else {
    pcVar3 = pcVar3 + fp_info[1];
  }
  if (0 < (int)precision) {
    crt_str_shift_right(pcVar3,1);
    *pcVar3 = crt_null_char;
    iVar1 = fp_info[1];
    if (iVar1 < 0) {
      if (((char)force_decimal != '\0') || (-iVar1 <= (int)precision)) {
        precision = -iVar1;
      }
      crt_str_shift_right(pcVar3 + 1,precision);
      _memset(pcVar3 + 1,0x30,precision);
    }
  }
  return dst;
}



/* FUN_00463a7d @ 00463a7d */

void __cdecl FUN_00463a7d(undefined8 *param_1,char *param_2,size_t param_3,int param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  uint local_2c [6];
  int local_14;
  int local_10;
  
  crt_fp_to_string((double)*param_1,&local_14,local_2c);
  iVar1 = local_10 + -1;
  crt_fp_round_digits(param_2 + (local_14 == 0x2d),param_3,&local_14);
  local_10 = local_10 + -1;
  if ((local_10 < -4) || ((int)param_3 <= local_10)) {
    crt_fp_format_exp(param_2,param_3,param_4,&local_14,1);
  }
  else {
    pcVar2 = param_2 + (local_14 == 0x2d);
    if (iVar1 < local_10) {
      do {
        pcVar3 = pcVar2;
        pcVar2 = pcVar3 + 1;
      } while (*pcVar3 != '\0');
      pcVar3[-1] = '\0';
    }
    crt_fp_format_fixed(param_2,param_3,&local_14,1);
  }
  return;
}



/* __cfltcvt @ 00463b10 */

/* Library Function - Single Match
    __cfltcvt
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  char *pcVar1;
  undefined1 *puVar2;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    puVar2 = FUN_0046385e(arg,buffer,format,precision);
  }
  else {
    if (sizeInBytes == 0x66) {
      pcVar1 = FUN_00463981(arg,buffer,format);
      return (errno_t)pcVar1;
    }
    puVar2 = (undefined1 *)FUN_00463a7d(arg,buffer,format,precision);
  }
  return (errno_t)puVar2;
}



/* crt_str_shift_right @ 00463b61 */

/* CRT: shift string right by count (memmove) */

void __cdecl crt_str_shift_right(char *str,int count)

{
  size_t sVar1;
  
  if (count != 0) {
    sVar1 = _strlen(str);
    crt_memmove(str + count,str,sVar1 + 1);
  }
  return;
}



/* crt_msize @ 00463b86 */

/* CRT: allocation size */

size_t __cdecl crt_msize(void *ptr)

{
  byte *pbVar1;
  SIZE_T SVar2;
  size_t sVar3;
  void *local_30;
  byte *local_2c;
  uint local_28;
  size_t local_24;
  byte *local_20;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fac0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  if (crt_heap_mode == 3) {
    ExceptionList = &local_14;
    crt_lock(9);
    local_8 = 0;
    local_20 = crt_sbh_find_region(ptr);
    if (local_20 != (byte *)0x0) {
      local_24 = *(int *)((int)ptr + -4) - 9;
    }
    sVar3 = local_24;
    local_8 = 0xffffffff;
    FUN_00463bf0();
    pbVar1 = local_20;
  }
  else {
    ExceptionList = &local_14;
    if (crt_heap_mode != 2) goto LAB_00463c44;
    ExceptionList = &local_14;
    crt_lock(9);
    local_8 = 1;
    local_2c = crt_sbh_find_block(ptr,&local_30,&local_28);
    if (local_2c != (byte *)0x0) {
      local_24 = (uint)*local_2c << 4;
    }
    sVar3 = local_24;
    local_8 = 0xffffffff;
    FUN_00463c6b();
    pbVar1 = local_2c;
  }
  if (pbVar1 != (byte *)0x0) {
    ExceptionList = local_14;
    return sVar3;
  }
LAB_00463c44:
  SVar2 = HeapSize(crt_heap_handle,0,ptr);
  ExceptionList = local_14;
  return SVar2;
}



/* FUN_00463bf0 @ 00463bf0 */

/* [binja] int32_t sub_463bf0() */

int FUN_00463bf0(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* FUN_00463c6b @ 00463c6b */

/* [binja] int32_t sub_463c6b() */

int FUN_00463c6b(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* crt_isctype @ 00463c74 */

/* ctype classification (MBCS via GetStringTypeA/W) */

uint __thiscall crt_isctype(void *this,int c,uint mask)

{
  BOOL BVar1;
  int iVar2;
  undefined4 local_8;
  
  if (c + 1U < 0x101) {
    c._2_2_ = *(ushort *)(crt_ctype_table + c * 2);
  }
  else {
    if ((crt_ctype_table[(c >> 8 & 0xffU) * 2 + 1] & 0x80) == 0) {
      local_8 = CONCAT31((int3)((uint)this >> 8),(char)c) & 0xffff00ff;
      iVar2 = 1;
    }
    else {
      local_8._0_2_ = CONCAT11((char)c,(char)((uint)c >> 8));
      local_8 = CONCAT22((short)((uint)this >> 0x10),(undefined2)local_8) & 0xff00ffff;
      iVar2 = 2;
    }
    BVar1 = crt_cxx_throw_exception(1,(LPCSTR)&local_8,iVar2,(LPWORD)((int)&c + 2),0,0,1);
    if (BVar1 == 0) {
      return 0;
    }
  }
  return c._2_2_ & mask;
}



/* crt_lock_file @ 00463da5 */

/* lock a FILE stream (CRT lock or critical section) */

void __cdecl crt_lock_file(uint param_1)

{
  if ((0x47b3d7 < param_1) && (param_1 < 0x47b639)) {
    crt_lock(((int)(param_1 - 0x47b3d8) >> 5) + 0x1c);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}



/* crt_lock_file2 @ 00463dd4 */

/* CRT: lock FILE by index or per-stream critical section */

void __cdecl crt_lock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    crt_lock(param_1 + 0x1c);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}



/* crt_unlock_file @ 00463df7 */

/* unlock a FILE stream (CRT lock or critical section) */

void __cdecl crt_unlock_file(uint param_1)

{
  if ((0x47b3d7 < param_1) && (param_1 < 0x47b639)) {
    crt_unlock(((int)(param_1 - 0x47b3d8) >> 5) + 0x1c);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
  return;
}



/* crt_unlock_file2 @ 00463e26 */

/* CRT: unlock FILE by index or per-stream critical section */

void __cdecl crt_unlock_file2(int param_1,int param_2)

{
  if (param_1 < 0x14) {
    crt_unlock(param_1 + 0x1c);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_2 + 0x20));
  return;
}



/* crt_close @ 00463e49 */

/* CRT: close file handle with lock */

int __cdecl crt_close(int fd)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  
  if (((uint)fd < (uint)crt_nhandle) &&
     (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0)) {
    crt_lock_fh(fd);
    iVar1 = crt_close_nolock(fd);
    crt_unlock_fh(fd);
    return iVar1;
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 9;
  puVar3 = crt_doserrno_ptr();
  *puVar3 = 0;
  return -1;
}



/* crt_close_nolock @ 00463ea6 */

/* CRT: close file handle without lock */

int __cdecl crt_close_nolock(int fd)

{
  void *pvVar1;
  void *pvVar2;
  WINBOOL WVar3;
  DWORD os_error;
  int iVar4;
  
  pvVar1 = crt_get_osfhandle(fd);
  if (pvVar1 != (void *)0xffffffff) {
    if ((fd == 1) || (fd == 2)) {
      pvVar1 = crt_get_osfhandle(2);
      pvVar2 = crt_get_osfhandle(1);
      if (pvVar2 == pvVar1) goto LAB_00463ef4;
    }
    pvVar1 = crt_get_osfhandle(fd);
    WVar3 = CloseHandle(pvVar1);
    if (WVar3 == 0) {
      os_error = GetLastError();
      goto LAB_00463ef6;
    }
  }
LAB_00463ef4:
  os_error = 0;
LAB_00463ef6:
  crt_get_osfhandle(fd);
  *(undefined1 *)((&crt_pioinfo_table)[fd >> 5] + (fd & 0x1fU) * 9 + 1) = 0;
  if (os_error == 0) {
    iVar4 = 0;
  }
  else {
    crt_dosmaperr(os_error);
    iVar4 = -1;
  }
  return iVar4;
}



/* __freebuf @ 00463f29 */

/* Library Function - Single Match
    __freebuf
   
   Library: Visual Studio 2003 Release */

void __cdecl __freebuf(FILE *_File)

{
  if (((_File->_flag & 0x83U) != 0) && ((_File->_flag & 8U) != 0)) {
    crt_free_base(_File->_base);
    *(ushort *)&_File->_flag = (ushort)_File->_flag & 0xfbf7;
    _File->_ptr = (char *)0x0;
    _File->_base = (char *)0x0;
    _File->_cnt = 0;
  }
  return;
}



/* crt_filbuf @ 00463f54 */

/* CRT: fill read buffer */

uint __cdecl crt_filbuf(undefined4 *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  void **ppvVar4;
  
  uVar2 = param_1[3];
  if (((uVar2 & 0x83) != 0) && ((uVar2 & 0x40) == 0)) {
    if ((uVar2 & 2) == 0) {
      param_1[3] = uVar2 | 1;
      if ((uVar2 & 0x10c) == 0) {
        crt_file_buffer_init(param_1);
      }
      else {
        *param_1 = param_1[2];
      }
      iVar3 = crt_read(param_1[4],(char *)param_1[2],param_1[6]);
      param_1[1] = iVar3;
      if ((iVar3 != 0) && (iVar3 != -1)) {
        if ((param_1[3] & 0x82) == 0) {
          uVar2 = param_1[4];
          if (uVar2 == 0xffffffff) {
            ppvVar4 = (void **)&crt_heap_ptr_table;
          }
          else {
            ppvVar4 = (&crt_pioinfo_table)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 9;
          }
          if (((uint)ppvVar4[1] & 0x82) == 0x82) {
            param_1[3] = param_1[3] | 0x2000;
          }
        }
        if (((param_1[6] == 0x200) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
          param_1[6] = 0x1000;
        }
        param_1[1] = iVar3 + -1;
        bVar1 = *(byte *)*param_1;
        *param_1 = (byte *)*param_1 + 1;
        return (uint)bVar1;
      }
      param_1[3] = param_1[3] | (-(uint)(iVar3 != 0) & 0x10) + 0x10;
      param_1[1] = 0;
    }
    else {
      param_1[3] = uVar2 | 0x20;
    }
  }
  return 0xffffffff;
}



/* crt_openfile @ 00464030 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CRT: open file with mode string parsing */

undefined4 * __cdecl crt_openfile(LPCSTR param_1,char *param_2,uint param_3,undefined4 *param_4)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint oflag;
  uint uVar6;
  
  bVar4 = false;
  bVar3 = false;
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    oflag = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      oflag = 0;
      uVar6 = crt_siglookup_flags | 1;
      goto LAB_00464071;
    }
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    oflag = 0x301;
  }
  uVar6 = crt_siglookup_flags | 2;
LAB_00464071:
  bVar2 = true;
LAB_00464074:
  cVar1 = param_2[1];
  param_2 = param_2 + 1;
  if ((cVar1 == '\0') || (!bVar2)) {
    iVar5 = crt_sopen(param_1,oflag,param_3,0x1a4);
    if (iVar5 < 0) {
      return (undefined4 *)0x0;
    }
    crt_file_handle_flags = crt_file_handle_flags + 1;
    param_4[3] = uVar6;
    param_4[1] = 0;
    *param_4 = 0;
    param_4[2] = 0;
    param_4[7] = 0;
    param_4[4] = iVar5;
    return param_4;
  }
  if (cVar1 < 'U') {
    if (cVar1 == 'T') {
      if ((oflag & 0x1000) == 0) {
        oflag = oflag | 0x1000;
        goto LAB_00464074;
      }
    }
    else if (cVar1 == '+') {
      if ((oflag & 2) == 0) {
        oflag = oflag & 0xfffffffe | 2;
        uVar6 = uVar6 & 0xfffffffc | 0x80;
        goto LAB_00464074;
      }
    }
    else if (cVar1 == 'D') {
      if ((oflag & 0x40) == 0) {
        oflag = oflag | 0x40;
        goto LAB_00464074;
      }
    }
    else if (cVar1 == 'R') {
      if (!bVar3) {
        bVar3 = true;
        oflag = oflag | 0x10;
        goto LAB_00464074;
      }
    }
    else if ((cVar1 == 'S') && (!bVar3)) {
      bVar3 = true;
      oflag = oflag | 0x20;
      goto LAB_00464074;
    }
  }
  else {
    if (cVar1 == 'b') {
      if ((oflag & 0xc000) != 0) goto LAB_00464154;
      oflag = oflag | 0x8000;
      goto LAB_00464074;
    }
    if (cVar1 == 'c') {
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 | 0x4000;
        goto LAB_00464074;
      }
    }
    else {
      if (cVar1 != 'n') {
        if ((cVar1 != 't') || ((oflag & 0xc000) != 0)) goto LAB_00464154;
        oflag = oflag | 0x4000;
        goto LAB_00464074;
      }
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 & 0xffffbfff;
        goto LAB_00464074;
      }
    }
  }
LAB_00464154:
  bVar2 = false;
  goto LAB_00464074;
}



/* crt_getstream @ 004641a0 */

/* CRT: allocate FILE struct from pool */

undefined4 * crt_getstream(void)

{
  FILE *pFVar1;
  int iVar2;
  FILE *pFVar3;
  
  pFVar3 = (FILE *)0x0;
  crt_lock(2);
  iVar2 = 0;
  if (0 < crt_stream_count) {
    do {
      pFVar1 = crt_stream_table[iVar2];
      if (pFVar1 == (FILE *)0x0) {
        pFVar1 = _malloc(0x38);
        crt_stream_table[iVar2] = pFVar1;
        if (crt_stream_table[iVar2] != (FILE *)0x0) {
          InitializeCriticalSection((LPCRITICAL_SECTION)(crt_stream_table[iVar2] + 0x20));
          EnterCriticalSection((LPCRITICAL_SECTION)(crt_stream_table[iVar2] + 0x20));
          pFVar3 = crt_stream_table[iVar2];
LAB_00464244:
          if (pFVar3 != (FILE *)0x0) {
            *(undefined4 *)(pFVar3 + 0x10) = 0xffffffff;
            *(undefined4 *)(pFVar3 + 4) = 0;
            *(undefined4 *)(pFVar3 + 0xc) = 0;
            *(undefined4 *)(pFVar3 + 8) = 0;
            *(undefined4 *)pFVar3 = 0;
            *(undefined4 *)(pFVar3 + 0x1c) = 0;
          }
        }
        break;
      }
      if (((byte)pFVar1[0xc] & 0x83) == 0) {
        crt_lock_file2(iVar2,(int)pFVar1);
        if (((byte)crt_stream_table[iVar2][0xc] & 0x83) == 0) {
          pFVar3 = crt_stream_table[iVar2];
          goto LAB_00464244;
        }
        crt_unlock_file2(iVar2,(int)crt_stream_table[iVar2]);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < crt_stream_count);
  }
  crt_unlock(2);
  return (undefined4 *)pFVar3;
}



/* crt_flsbuf @ 00464268 */

/* flush buffer or write single char (fputc core) */

uint __cdecl crt_flsbuf(uint param_1,int *param_2)

{
  uint uVar1;
  uint fd;
  char *buf;
  int *piVar2;
  byte bVar3;
  undefined3 extraout_var;
  void **ppvVar4;
  int *count;
  
  piVar2 = param_2;
  uVar1 = param_2[3];
  fd = param_2[4];
  if (((uVar1 & 0x82) == 0) || ((uVar1 & 0x40) != 0)) {
LAB_00464374:
    param_2[3] = uVar1 | 0x20;
  }
  else {
    if ((uVar1 & 1) != 0) {
      param_2[1] = 0;
      if ((uVar1 & 0x10) == 0) goto LAB_00464374;
      *param_2 = param_2[2];
      param_2[3] = uVar1 & 0xfffffffe;
    }
    uVar1 = param_2[3];
    param_2[1] = 0;
    param_2 = (int *)0x0;
    piVar2[3] = uVar1 & 0xffffffef | 2;
    if (((uVar1 & 0x10c) == 0) &&
       (((piVar2 != (int *)&crt_stdout_struct && (piVar2 != (int *)&crt_stderr_struct)) ||
        (bVar3 = crt_free_osfhandle(fd), CONCAT31(extraout_var,bVar3) == 0)))) {
      crt_file_buffer_init(piVar2);
    }
    if ((*(ushort *)(piVar2 + 3) & 0x108) == 0) {
      count = (int *)0x1;
      param_2 = (int *)crt_write(fd,(char *)&param_1,1);
    }
    else {
      buf = (char *)piVar2[2];
      count = (int *)(*piVar2 - (int)buf);
      *piVar2 = (int)(buf + 1);
      piVar2[1] = piVar2[6] + -1;
      if ((int)count < 1) {
        if (fd == 0xffffffff) {
          ppvVar4 = (void **)&crt_heap_ptr_table;
        }
        else {
          ppvVar4 = (&crt_pioinfo_table)[(int)fd >> 5] + (fd & 0x1f) * 9;
        }
        if (((uint)ppvVar4[1] & 0x20) != 0) {
          crt_lseek(fd,0,2);
        }
      }
      else {
        param_2 = (int *)crt_write(fd,buf,(uint)count);
      }
      *(undefined1 *)piVar2[2] = (undefined1)param_1;
    }
    if (param_2 == count) {
      return param_1 & 0xff;
    }
    piVar2[3] = piVar2[3] | 0x20;
  }
  return 0xffffffff;
}



/* crt_output @ 00464380 */

/* CRT: core printf formatter */

int __cdecl crt_output(int *param_1,byte *param_2,undefined4 *param_3)

{
  byte *pbVar1;
  uint uVar2;
  WCHAR *pWVar3;
  void *pvVar4;
  short *psVar5;
  int *piVar6;
  int iVar7;
  int extraout_EDX;
  byte bVar8;
  int iVar9;
  WCHAR *pWVar10;
  undefined1 *puVar11;
  undefined8 uVar12;
  WCHAR local_250 [255];
  undefined1 local_51;
  undefined4 local_50;
  undefined4 local_4c;
  CHAR local_48 [4];
  undefined4 local_44;
  int local_40;
  int local_3c;
  int local_38;
  WCHAR *local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined8 local_24;
  char local_1a;
  char local_19;
  int local_18;
  undefined1 *local_14;
  WCHAR *local_10;
  int local_c;
  uint local_8;
  
  local_40 = 0;
  local_14 = (undefined1 *)0x0;
  bVar8 = *param_2;
  local_18 = 0;
  local_34 = (WCHAR *)0x0;
  pbVar1 = param_2;
  do {
    if ((bVar8 == 0) || (param_2 = pbVar1 + 1, local_18 < 0)) {
      return local_18;
    }
    if (((char)bVar8 < ' ') || ('x' < (char)bVar8)) {
      uVar2 = 0;
    }
    else {
      uVar2 = (byte)"e+000"[(char)bVar8] & 0xf;
    }
    local_40 = (int)(char)(&DAT_0046fad8)[uVar2 * 8 + local_40] >> 4;
    switch(local_40) {
    case 0:
switchD_004643fc_caseD_0:
      local_30 = 0;
      if ((crt_ctype_table[(uint)bVar8 * 2 + 1] & 0x80) != 0) {
        crt_putc_nolock((int)(char)bVar8,param_1,&local_18);
        bVar8 = *param_2;
        param_2 = pbVar1 + 2;
      }
      crt_putc_nolock((int)(char)bVar8,param_1,&local_18);
      break;
    case 1:
      local_c = -1;
      local_44 = 0;
      local_3c = 0;
      local_2c = 0;
      local_28 = 0;
      local_8 = 0;
      local_30 = 0;
      break;
    case 2:
      if (bVar8 == 0x20) {
        local_8 = local_8 | 2;
      }
      else if (bVar8 == 0x23) {
        local_8 = local_8 | 0x80;
      }
      else if (bVar8 == 0x2b) {
        local_8 = local_8 | 1;
      }
      else if (bVar8 == 0x2d) {
        local_8 = local_8 | 4;
      }
      else if (bVar8 == 0x30) {
        local_8 = local_8 | 8;
      }
      break;
    case 3:
      if (bVar8 == 0x2a) {
        local_2c = crt_va_arg_int((int *)&param_3);
        if (local_2c < 0) {
          local_8 = local_8 | 4;
          local_2c = -local_2c;
        }
      }
      else {
        local_2c = (char)bVar8 + -0x30 + local_2c * 10;
      }
      break;
    case 4:
      local_c = 0;
      break;
    case 5:
      if (bVar8 == 0x2a) {
        local_c = crt_va_arg_int((int *)&param_3);
        if (local_c < 0) {
          local_c = -1;
        }
      }
      else {
        local_c = (char)bVar8 + -0x30 + local_c * 10;
      }
      break;
    case 6:
      if (bVar8 == 0x49) {
        if ((*param_2 != 0x36) || (pbVar1[2] != 0x34)) {
          local_40 = 0;
          goto switchD_004643fc_caseD_0;
        }
        param_2 = pbVar1 + 3;
        local_8 = local_8 | 0x8000;
      }
      else if (bVar8 == 0x68) {
        local_8 = local_8 | 0x20;
      }
      else if (bVar8 == 0x6c) {
        local_8 = local_8 | 0x10;
      }
      else if (bVar8 == 0x77) {
        local_8 = local_8 | 0x800;
      }
      break;
    case 7:
      pWVar10 = local_10;
      if ((char)bVar8 < 'h') {
        if ((char)bVar8 < 'e') {
          if ((char)bVar8 < 'Y') {
            if (bVar8 != 0x58) {
              if (bVar8 == 0x43) {
                if ((local_8 & 0x830) == 0) {
                  local_8 = local_8 | 0x800;
                }
                goto LAB_00464651;
              }
              if ((bVar8 != 0x45) && (bVar8 != 0x47)) {
                if (bVar8 == 0x53) {
                  if ((local_8 & 0x830) == 0) {
                    local_8 = local_8 | 0x800;
                  }
                  goto LAB_004645c1;
                }
                goto LAB_004649d4;
              }
              local_44 = 1;
              bVar8 = bVar8 + 0x20;
              goto LAB_00464623;
            }
LAB_00464830:
            local_38 = 7;
LAB_00464837:
            local_14 = (undefined1 *)0x10;
            if ((local_8 & 0x80) != 0) {
              local_1a = '0';
              local_19 = (char)local_38 + 'Q';
              local_28 = 2;
            }
            goto LAB_004648a0;
          }
          if (bVar8 == 0x5a) {
            psVar5 = (short *)crt_va_arg_int((int *)&param_3);
            if ((psVar5 == (short *)0x0) ||
               (pWVar10 = *(WCHAR **)(psVar5 + 2), pWVar10 == (WCHAR *)0x0)) {
              local_10 = (WCHAR *)PTR_DAT_0047b658;
              pWVar10 = (WCHAR *)PTR_DAT_0047b658;
              goto LAB_004647b1;
            }
            if ((local_8 & 0x800) == 0) {
              local_30 = 0;
              local_14 = (undefined1 *)(int)*psVar5;
            }
            else {
              local_30 = 1;
              local_14 = (undefined1 *)((uint)(int)*psVar5 >> 1);
            }
          }
          else if (bVar8 == 99) {
LAB_00464651:
            if ((local_8 & 0x810) == 0) {
              iVar9 = crt_va_arg_int((int *)&param_3);
              local_250[0]._0_1_ = (undefined1)iVar9;
              local_14 = (undefined1 *)0x1;
            }
            else {
              pvVar4 = crt_va_arg_short((int *)&param_3);
              local_14 = (undefined1 *)crt_alloc_osfhandle((LPSTR)local_250,(WCHAR)pvVar4);
              if ((int)local_14 < 0) {
                local_3c = 1;
              }
            }
            pWVar10 = local_250;
          }
          else if (bVar8 == 100) goto LAB_00464895;
        }
        else {
LAB_00464623:
          local_8 = local_8 | 0x40;
          pWVar10 = local_250;
          pWVar3 = local_250;
          if (local_c < 0) {
            local_c = 6;
          }
          else if (local_c == 0) {
            if (bVar8 == 0x67) {
              local_c = 1;
            }
          }
          else {
            if (0x200 < local_c) {
              local_c = 0x200;
            }
            if ((0xa3 < local_c) &&
               (local_10 = local_250, local_34 = _malloc(local_c + 0x15d), pWVar10 = local_34,
               pWVar3 = local_34, local_34 == (WCHAR *)0x0)) {
              local_c = 0xa3;
              pWVar10 = local_250;
              pWVar3 = local_10;
            }
          }
          local_10 = pWVar3;
          local_50 = *param_3;
          local_4c = param_3[1];
          param_3 = param_3 + 2;
          (*(code *)PTR_FUN_0047b1a8)(&local_50,pWVar10,(int)(char)bVar8,local_c,local_44);
          uVar2 = local_8 & 0x80;
          if ((uVar2 != 0) && (local_c == 0)) {
            (*(code *)PTR_FUN_0047b1b4)(pWVar10);
          }
          if ((bVar8 == 0x67) && (uVar2 == 0)) {
            (*(code *)PTR_FUN_0047b1ac)(pWVar10);
          }
          if ((char)*pWVar10 == '-') {
            local_8 = local_8 | 0x100;
            pWVar10 = (WCHAR *)((int)pWVar10 + 1);
            local_10 = pWVar10;
          }
LAB_004647b1:
          local_14 = (undefined1 *)_strlen((char *)pWVar10);
          pWVar10 = local_10;
        }
LAB_004649d4:
        local_10 = pWVar10;
        uVar2 = local_8;
        if (local_3c == 0) {
          if ((local_8 & 0x40) != 0) {
            if ((local_8 & 0x100) == 0) {
              if ((local_8 & 1) == 0) {
                if ((local_8 & 2) == 0) goto LAB_00464a0c;
                local_1a = ' ';
              }
              else {
                local_1a = '+';
              }
            }
            else {
              local_1a = '-';
            }
            local_28 = 1;
          }
LAB_00464a0c:
          iVar9 = (local_2c - local_28) - (int)local_14;
          if ((local_8 & 0xc) == 0) {
            crt_putc_repeat_nolock(0x20,iVar9,param_1,&local_18);
          }
          crt_putc_buffer_nolock(&local_1a,local_28,param_1,&local_18);
          if (((uVar2 & 8) != 0) && ((uVar2 & 4) == 0)) {
            crt_putc_repeat_nolock(0x30,iVar9,param_1,&local_18);
          }
          if ((local_30 == 0) || (puVar11 = local_14, pWVar10 = local_10, (int)local_14 < 1)) {
            crt_putc_buffer_nolock((char *)local_10,(int)local_14,param_1,&local_18);
          }
          else {
            do {
              puVar11 = puVar11 + -1;
              iVar7 = crt_alloc_osfhandle(local_48,*pWVar10);
              if (iVar7 < 1) break;
              crt_putc_buffer_nolock(local_48,iVar7,param_1,&local_18);
              pWVar10 = pWVar10 + 1;
            } while (puVar11 != (undefined1 *)0x0);
          }
          if ((local_8 & 4) != 0) {
            crt_putc_repeat_nolock(0x20,iVar9,param_1,&local_18);
          }
        }
      }
      else {
        if (bVar8 == 0x69) {
LAB_00464895:
          local_8 = local_8 | 0x40;
LAB_00464899:
          local_14 = (undefined1 *)0xa;
LAB_004648a0:
          if ((local_8 & 0x8000) == 0) {
            if ((local_8 & 0x20) == 0) {
              if ((local_8 & 0x40) == 0) {
                uVar2 = crt_va_arg_int((int *)&param_3);
                iVar9 = 0;
                goto LAB_004648f3;
              }
              uVar2 = crt_va_arg_int((int *)&param_3);
            }
            else if ((local_8 & 0x40) == 0) {
              uVar2 = crt_va_arg_int((int *)&param_3);
              uVar2 = uVar2 & 0xffff;
            }
            else {
              iVar9 = crt_va_arg_int((int *)&param_3);
              uVar2 = (uint)(short)iVar9;
            }
            iVar9 = (int)uVar2 >> 0x1f;
          }
          else {
            uVar2 = crt_va_arg_int64((int *)&param_3);
            iVar9 = extraout_EDX;
          }
LAB_004648f3:
          if ((((local_8 & 0x40) == 0) || (0 < iVar9)) || (-1 < iVar9)) {
            local_24 = CONCAT44(iVar9,uVar2);
          }
          else {
            local_8 = local_8 | 0x100;
            local_24 = CONCAT44(-(iVar9 + (uint)(uVar2 != 0)),-uVar2);
          }
          if ((local_8 & 0x8000) == 0) {
            local_24 = local_24 & 0xffffffff;
          }
          if (local_c < 0) {
            local_c = 1;
          }
          else {
            local_8 = local_8 & 0xfffffff7;
            if (0x200 < local_c) {
              local_c = 0x200;
            }
          }
          if ((uint)local_24 == 0 && local_24._4_4_ == 0) {
            local_28 = 0;
          }
          local_10 = (WCHAR *)&local_51;
          while( true ) {
            puVar11 = local_14;
            iVar9 = local_c + -1;
            if ((local_c < 1) && ((uint)local_24 == 0 && local_24._4_4_ == 0)) break;
            uVar2 = (int)local_14 >> 0x1f;
            local_c = iVar9;
            uVar12 = __aullrem((uint)local_24,local_24._4_4_,(uint)local_14,uVar2);
            iVar9 = (int)uVar12 + 0x30;
            local_24 = __aulldiv((uint)local_24,local_24._4_4_,(uint)puVar11,uVar2);
            if (0x39 < iVar9) {
              iVar9 = iVar9 + local_38;
            }
            pWVar10 = (WCHAR *)((int)local_10 + -1);
            *(char *)local_10 = (char)iVar9;
            local_10 = pWVar10;
          }
          iVar7 = -(int)local_10;
          local_14 = &local_51 + iVar7;
          pWVar10 = (WCHAR *)((int)local_10 + 1);
          local_c = iVar9;
          if (((local_8 & 0x200) != 0) &&
             ((*(char *)pWVar10 != '0' || (local_14 == (undefined1 *)0x0)))) {
            *(char *)local_10 = '0';
            local_14 = (undefined1 *)((int)&local_50 + iVar7);
            pWVar10 = local_10;
          }
          goto LAB_004649d4;
        }
        if (bVar8 != 0x6e) {
          if (bVar8 == 0x6f) {
            local_14 = (undefined1 *)0x8;
            if ((local_8 & 0x80) != 0) {
              local_8 = local_8 | 0x200;
            }
            goto LAB_004648a0;
          }
          if (bVar8 == 0x70) {
            local_c = 8;
            goto LAB_00464830;
          }
          if (bVar8 == 0x73) {
LAB_004645c1:
            iVar9 = 0x7fffffff;
            if (local_c != -1) {
              iVar9 = local_c;
            }
            pWVar3 = (WCHAR *)crt_va_arg_int((int *)&param_3);
            if ((local_8 & 0x810) == 0) {
              pWVar10 = pWVar3;
              if (pWVar3 == (WCHAR *)0x0) {
                pWVar3 = (WCHAR *)PTR_DAT_0047b658;
                pWVar10 = (WCHAR *)PTR_DAT_0047b658;
              }
              for (; (iVar9 != 0 && ((char)*pWVar3 != '\0')); pWVar3 = (WCHAR *)((int)pWVar3 + 1)) {
                iVar9 = iVar9 + -1;
              }
              local_14 = (undefined1 *)((int)pWVar3 - (int)pWVar10);
            }
            else {
              if (pWVar3 == (WCHAR *)0x0) {
                pWVar3 = (WCHAR *)PTR_DAT_0047b65c;
              }
              local_30 = 1;
              for (pWVar10 = pWVar3; (iVar9 != 0 && (*pWVar10 != L'\0')); pWVar10 = pWVar10 + 1) {
                iVar9 = iVar9 + -1;
              }
              local_14 = (undefined1 *)((int)pWVar10 - (int)pWVar3 >> 1);
              pWVar10 = pWVar3;
            }
            goto LAB_004649d4;
          }
          if (bVar8 != 0x75) {
            if (bVar8 != 0x78) goto LAB_004649d4;
            local_38 = 0x27;
            goto LAB_00464837;
          }
          goto LAB_00464899;
        }
        piVar6 = (int *)crt_va_arg_int((int *)&param_3);
        if ((local_8 & 0x20) == 0) {
          *piVar6 = local_18;
        }
        else {
          *(undefined2 *)piVar6 = (undefined2)local_18;
        }
        local_3c = 1;
      }
      if (local_34 != (WCHAR *)0x0) {
        crt_free_base(local_34);
        local_34 = (WCHAR *)0x0;
      }
    }
    bVar8 = *param_2;
    pbVar1 = param_2;
  } while( true );
}



/* crt_putc_nolock @ 00464b1e */

/* putc_nolock-style helper (increments count or sets -1 on error) */

void __cdecl crt_putc_nolock(uint param_1,int *param_2,int *param_3)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = param_2 + 1;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    uVar2 = crt_flsbuf(param_1,param_2);
  }
  else {
    *(undefined1 *)*param_2 = (undefined1)param_1;
    *param_2 = *param_2 + 1;
    uVar2 = param_1 & 0xff;
  }
  if (uVar2 == 0xffffffff) {
    *param_3 = -1;
    return;
  }
  *param_3 = *param_3 + 1;
  return;
}



/* crt_putc_repeat_nolock @ 00464b53 */

/* emit repeated chars via crt_putc_nolock (printf padding helper) */

void __cdecl crt_putc_repeat_nolock(uint param_1,int param_2,int *param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    crt_putc_nolock(param_1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}



/* crt_putc_buffer_nolock @ 00464b84 */

/* emit buffer chars via crt_putc_nolock (printf string helper) */

void __cdecl crt_putc_buffer_nolock(char *param_1,int param_2,int *param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    crt_putc_nolock((int)cVar1,param_3,param_4);
  } while (*param_4 != -1);
  return;
}



/* crt_va_arg_int @ 00464bbc */

/* [binja] int32_t sub_464bbc(int32_t* arg1) */

int __cdecl crt_va_arg_int(int *arg1)

{
  *arg1 = *arg1 + 4;
  return *(int *)(*arg1 + -4);
}



/* crt_va_arg_int64 @ 00464bc9 */

/* [binja] int32_t sub_464bc9(int32_t* arg1) */

int __cdecl crt_va_arg_int64(int *arg1)

{
  *arg1 = *arg1 + 8;
  return *(int *)(*arg1 + -8);
}



/* crt_va_arg_short @ 00464bd9 */

/* [binja] void* sub_464bd9(int32_t* arg1) */

void * __cdecl crt_va_arg_short(int *arg1)

{
  *arg1 = *arg1 + 4;
  return (void *)CONCAT22((short)((uint)*arg1 >> 0x10),*(undefined2 *)(*arg1 + -4));
}



/* FUN_00464be7 @ 00464be7 */

void __thiscall FUN_00464be7(void *this,uint *param_1,byte *param_2)

{
  uint uVar1;
  int iVar2;
  int unaff_EDI;
  uint uVar3;
  short local_1c [6];
  int local_10;
  undefined4 uStack_c;
  int local_8;
  
  uVar3 = 0;
  uVar1 = crt_fp_parse(this,local_1c,(ushort *)&local_8,(int *)param_2,(byte *)0x0,0,0,0,unaff_EDI);
  if ((uVar1 & 4) == 0) {
    iVar2 = crt_fp_classify(local_1c,&local_10);
    if (((uVar1 & 2) != 0) || (iVar2 == 1)) {
      uVar3 = 0x80;
    }
    if (((uVar1 & 1) != 0) || (iVar2 == 2)) {
      uVar3 = uVar3 | 0x100;
    }
  }
  else {
    uVar3 = 0x200;
    local_10 = 0;
    uStack_c = 0;
  }
  *param_1 = uVar3;
  *(ulonglong *)(param_1 + 4) = CONCAT44(uStack_c,local_10);
  param_1[1] = local_8 - (int)param_2;
  return;
}



/* _strlen @ 00464c70 */

/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_00464c90;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00464cc3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_00464c90:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_00464cc3;
}



/* FUN_004650d0 @ 004650d0 */

float10 __fastcall
FUN_004650d0(undefined4 param_1,int param_2,undefined2 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float10 in_ST0;
  int local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  double dStack_c;
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  uStack_20 = param_1;
  crt_file_write_buffered(param_2,&local_24,(uint)&param_3);
  return (float10)dStack_c;
}



/* __startOneArgErrorHandling @ 004650e7 */

/* Library Function - Single Match
    __startOneArgErrorHandling
   
   Library: Visual Studio */

float10 __fastcall
__startOneArgErrorHandling
          (undefined4 param_1,uint param_2,ushort param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  float10 in_ST0;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  double local_c;
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  local_20 = param_1;
  crt_file_write_buffered(param_2,&local_24,(uint)&param_3);
  return (float10)local_c;
}



/* FUN_00465130 @ 00465130 */

undefined1  [10] FUN_00465130(void)

{
  float10 in_ST0;
  float10 fVar1;
  undefined1 auVar2 [10];
  
  fVar1 = (float10)f2xm1(-(ROUND(in_ST0) - in_ST0));
  auVar2 = (undefined1  [10])fscale((float10)1 + fVar1,ROUND(in_ST0));
  return auVar2;
}



/* FUN_00465145 @ 00465145 */

void FUN_00465145(void)

{
  return;
}



/* FUN_0046515c @ 0046515c */

undefined4 FUN_0046515c(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) != 0) {
    return 7;
  }
  return 1;
}



/* __fload_withFB @ 00465175 */

/* Library Function - Single Match
    __fload_withFB
   
   Library: Visual Studio */

uint __fastcall __fload_withFB(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}



/* FUN_004651b8 @ 004651b8 */

uint __cdecl FUN_004651b8(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}



/* FUN_004651ce @ 004651ce */

void FUN_004651ce(void)

{
  return;
}



/* __math_exit @ 004651db */

/* Library Function - Single Match
    __math_exit
   
   Library: Visual Studio */

void __fastcall
__math_exit(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
           )

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    __startOneArgErrorHandling(param_1,param_2,unaff_retaddr,param_3,param_4,param_5);
    return;
  }
  return;
}



/* FUN_00465219 @ 00465219 */

void __fastcall
FUN_00465219(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  ushort in_FPUStatusWord;
  float10 in_ST0;
  ushort unaff_retaddr;
  uint uStack_4;
  
  uStack_4 = (uint)((ulonglong)(double)in_ST0 >> 0x20);
  if (((ulonglong)(double)in_ST0 & 0x7ff0000000000000) == 0) {
    fscale(in_ST0,(float10)1536.0);
  }
  else if ((uStack_4 & 0x7ff00000) == 0x7ff00000) {
    fscale(in_ST0,(float10)-1536.0);
  }
  else if (((unaff_retaddr == 0x27f) || ((unaff_retaddr & 0x20) != 0)) ||
          ((in_FPUStatusWord & 0x20) == 0)) {
    return;
  }
  if (param_2 == 0x1d) {
    FUN_004650d0(param_1,0x1d,unaff_retaddr,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  __startOneArgErrorHandling(param_1,param_2,unaff_retaddr,param_3,param_4,param_5);
  return;
}



/* FUN_004652bc @ 004652bc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4652bc(double arg1, int32_t arg2, int32_t arg3, double* arg4) */

int __cdecl FUN_004652bc(double arg1,int arg2,int arg3,double *arg4)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  dVar1 = arg1;
  if (arg1 < 0.0) {
    dVar1 = -arg1;
  }
  dVar2 = crt_daylight_flag;
  if (arg3 == 0x7ff00000) {
    if (arg2 != 0) {
LAB_00465347:
      if (arg1._4_4_ == 0x7ff00000) {
        if (arg1._0_4_ != 0) {
          return 0;
        }
        if (0.0 < _arg2) goto LAB_004653e2;
        if (_arg2 < 0.0) goto LAB_00465379;
      }
      else {
        if (arg1 != -INFINITY) {
          return 0;
        }
        iVar3 = FUN_004653ec(_arg2);
        if (0.0 < _arg2) {
          dVar2 = crt_daylight_flag;
          if (iVar3 == 1) {
            dVar2 = -crt_daylight_flag;
          }
          goto LAB_004653e2;
        }
        if (_arg2 < 0.0) {
          dVar2 = crt_timezone_name_std;
          if (iVar3 != 1) {
            dVar2 = 0.0;
          }
          goto LAB_004653e2;
        }
      }
      dVar2 = 1.0;
      goto LAB_004653e2;
    }
    if (1.0 < dVar1) goto LAB_004653e2;
    if (1.0 <= dVar1) {
LAB_0046530c:
      *arg4 = crt_timezone_offset_alt;
      return 1;
    }
  }
  else {
    if ((arg3 != -0x100000) || (arg2 != 0)) goto LAB_00465347;
    if (dVar1 <= 1.0) {
      if (1.0 <= dVar1) goto LAB_0046530c;
      goto LAB_004653e2;
    }
  }
LAB_00465379:
  dVar2 = 0.0;
LAB_004653e2:
  *arg4 = dVar2;
  return 0;
}



/* FUN_004653ec @ 004653ec */

undefined4 __cdecl FUN_004653ec(double param_1)

{
  uint uVar1;
  float10 fVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0046325f(SUB84(param_1,0),(uint)((ulonglong)param_1 >> 0x20));
  if ((uVar1 & 0x90) == 0) {
    fVar2 = __frnd(param_1);
    if ((double)fVar2 == param_1) {
      fVar2 = __frnd(param_1 / 2.0);
      if (fVar2 == (float10)(param_1 / 2.0)) {
        uVar3 = 2;
      }
      else {
        uVar3 = 1;
      }
      return uVar3;
    }
  }
  return 0;
}



/* crt_mt_init @ 00465451 */

/* CRT thread init (TLS + locks) */

undefined4 crt_mt_init(void)

{
  DWORD *lpTlsValue;
  WINBOOL WVar1;
  DWORD DVar2;
  
  crt_init_locks();
  crt_tls_slot_index = TlsAlloc();
  if (crt_tls_slot_index != 0xffffffff) {
    lpTlsValue = crt_calloc(1,0x74);
    if (lpTlsValue != (DWORD *)0x0) {
      WVar1 = TlsSetValue(crt_tls_slot_index,lpTlsValue);
      if (WVar1 != 0) {
        crt_init_thread_data(lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        return 1;
      }
    }
  }
  return 0;
}



/* crt_init_thread_data @ 004654a5 */

/* CRT: initialize per-thread data defaults */

void __cdecl crt_init_thread_data(void *ptd)

{
  *(undefined **)((int)ptd + 0x50) = &crt_thread_data_default;
  *(undefined4 *)((int)ptd + 0x14) = 1;
  return;
}



/* crt_get_thread_data @ 004654b8 */

/* CRT per-thread data accessor */

DWORD * crt_get_thread_data(void)

{
  DWORD dwErrCode;
  DWORD *lpTlsValue;
  WINBOOL WVar1;
  DWORD DVar2;
  
  dwErrCode = GetLastError();
  lpTlsValue = TlsGetValue(crt_tls_slot_index);
  if (lpTlsValue == (DWORD *)0x0) {
    lpTlsValue = crt_calloc(1,0x74);
    if (lpTlsValue != (DWORD *)0x0) {
      WVar1 = TlsSetValue(crt_tls_slot_index,lpTlsValue);
      if (WVar1 != 0) {
        crt_init_thread_data(lpTlsValue);
        DVar2 = GetCurrentThreadId();
        lpTlsValue[1] = 0xffffffff;
        *lpTlsValue = DVar2;
        goto LAB_00465513;
      }
    }
    __amsg_exit(0x10);
  }
LAB_00465513:
  SetLastError(dwErrCode);
  return lpTlsValue;
}



/* crt_free_thread_data @ 0046551f */

/* frees CRT per-thread data */

void __cdecl crt_free_thread_data(undefined *param_1)

{
  if (crt_tls_slot_index != 0xffffffff) {
    if ((param_1 != (undefined *)0x0) ||
       (param_1 = TlsGetValue(crt_tls_slot_index), param_1 != (undefined *)0x0)) {
      if (*(void **)(param_1 + 0x24) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x24));
      }
      if (*(void **)(param_1 + 0x28) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x28));
      }
      if (*(void **)(param_1 + 0x30) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x30));
      }
      if (*(void **)(param_1 + 0x38) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x38));
      }
      if (*(void **)(param_1 + 0x40) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x40));
      }
      if (*(void **)(param_1 + 0x44) != (void *)0x0) {
        crt_free_base(*(void **)(param_1 + 0x44));
      }
      if (*(undefined **)(param_1 + 0x50) != &crt_thread_data_default) {
        crt_free_base(*(undefined **)(param_1 + 0x50));
      }
      crt_free_base(param_1);
    }
    TlsSetValue(crt_tls_slot_index,(LPVOID)0x0);
    return;
  }
  return;
}



/* crt_commit @ 004655bf */

/* CRT: commit file buffers to disk */

int __cdecl crt_commit(int fd)

{
  void *hFile;
  WINBOOL WVar1;
  DWORD DVar2;
  uint *puVar3;
  int *piVar4;
  int iVar5;
  
  if ((uint)crt_nhandle <= (uint)fd) {
LAB_00465640:
    piVar4 = crt_errno_ptr();
    *piVar4 = 9;
    return -1;
  }
  if (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) == 0) goto LAB_00465640;
  crt_lock_fh(fd);
  if (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0) {
    hFile = crt_get_osfhandle(fd);
    WVar1 = FlushFileBuffers(hFile);
    if (WVar1 == 0) {
      DVar2 = GetLastError();
    }
    else {
      DVar2 = 0;
    }
    iVar5 = 0;
    if (DVar2 == 0) goto LAB_00465635;
    puVar3 = crt_doserrno_ptr();
    *puVar3 = DVar2;
  }
  piVar4 = crt_errno_ptr();
  *piVar4 = 9;
  iVar5 = -1;
LAB_00465635:
  crt_unlock_fh(fd);
  return iVar5;
}



/* crt_write @ 00465652 */

/* CRT: write handle with lock */

int __cdecl crt_write(int fd,char *buf,uint count)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  
  if (((uint)fd < (uint)crt_nhandle) &&
     (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0)) {
    crt_lock_fh(fd);
    iVar1 = crt_write_nolock(fd,buf,count);
    crt_unlock_fh(fd);
    return iVar1;
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 9;
  puVar3 = crt_doserrno_ptr();
  *puVar3 = 0;
  return -1;
}



/* crt_write_nolock @ 004656b7 */

/* CRT: write handle (no lock), text-mode CRLF translation */

int __cdecl crt_write_nolock(int fd,char *buf,uint count)

{
  void ***pppvVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  WINBOOL WVar7;
  int *piVar8;
  uint *puVar9;
  char local_418 [1028];
  int local_14;
  DWORD local_10;
  DWORD local_c;
  char *local_8;
  
  local_c = 0;
  local_14 = 0;
  if (count == 0) {
LAB_004656d0:
    iVar4 = 0;
  }
  else {
    pppvVar1 = &crt_pioinfo_table + (fd >> 5);
    uVar5 = fd & 0x1f;
    if (((uint)(*pppvVar1)[uVar5 * 9 + 1] & 0x20) != 0) {
      crt_lseek_nolock(fd,0,2);
    }
    if (((uint)(*pppvVar1 + uVar5 * 9)[1] & 0x80) == 0) {
      WVar7 = WriteFile((*pppvVar1)[uVar5 * 9],buf,count,&local_10,(LPOVERLAPPED)0x0);
      if (WVar7 == 0) {
        fd = GetLastError();
      }
      else {
        local_c = local_10;
        fd = 0;
      }
LAB_0046579f:
      if (local_c != 0) {
        return local_c - local_14;
      }
      if (fd == 0) goto LAB_00465811;
      if (fd == 5) {
        piVar8 = crt_errno_ptr();
        *piVar8 = 9;
        puVar9 = crt_doserrno_ptr();
        *puVar9 = 5;
      }
      else {
        crt_dosmaperr(fd);
      }
    }
    else {
      local_8 = buf;
      fd = 0;
      if (count != 0) {
        do {
          pcVar6 = local_418;
          do {
            if (count <= (uint)((int)local_8 - (int)buf)) break;
            pcVar2 = local_8 + 1;
            cVar3 = *local_8;
            local_8 = pcVar2;
            if (cVar3 == '\n') {
              local_14 = local_14 + 1;
              *pcVar6 = '\r';
              pcVar6 = pcVar6 + 1;
            }
            *pcVar6 = cVar3;
            pcVar6 = pcVar6 + 1;
          } while ((int)pcVar6 - (int)local_418 < 0x400);
          WVar7 = WriteFile((*pppvVar1)[uVar5 * 9],local_418,(int)pcVar6 - (int)local_418,&local_10,
                            (LPOVERLAPPED)0x0);
          if (WVar7 == 0) {
            fd = GetLastError();
            goto LAB_0046579f;
          }
          local_c = local_c + local_10;
          if (((int)local_10 < (int)pcVar6 - (int)local_418) ||
             (count <= (uint)((int)local_8 - (int)buf))) goto LAB_0046579f;
        } while( true );
      }
LAB_00465811:
      if ((((uint)(*pppvVar1)[uVar5 * 9 + 1] & 0x40) != 0) && (*buf == '\x1a')) goto LAB_004656d0;
      piVar8 = crt_errno_ptr();
      *piVar8 = 0x1c;
      puVar9 = crt_doserrno_ptr();
      *puVar9 = 0;
    }
    iVar4 = -1;
  }
  return iVar4;
}



/* crt_init_locks @ 00465842 */

/* initializes CRT critical sections */

void crt_init_locks(void)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_0047b738);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_0047b728);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_0047b718);
  InitializeCriticalSection((LPCRITICAL_SECTION)PTR_DAT_0047b6f8);
  return;
}



/* crt_lock @ 0046586b */

/* CRT lock table enter */

void __cdecl crt_lock(int param_1)

{
  int *piVar1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  piVar1 = (int *)(&crt_tls_slot_count + param_1 * 4);
  if (*(int *)(&crt_tls_slot_count + param_1 * 4) == 0) {
    lpCriticalSection = _malloc(0x18);
    if (lpCriticalSection == (LPCRITICAL_SECTION)0x0) {
      __amsg_exit(0x11);
    }
    crt_lock(0x11);
    if (*piVar1 == 0) {
      InitializeCriticalSection(lpCriticalSection);
      *piVar1 = (int)lpCriticalSection;
    }
    else {
      crt_free_base(lpCriticalSection);
    }
    crt_unlock(0x11);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)*piVar1);
  return;
}



/* crt_unlock @ 004658cc */

/* CRT lock table leave */

void __cdecl crt_unlock(int param_1)

{
  LeaveCriticalSection(*(LPCRITICAL_SECTION *)(&crt_tls_slot_count + param_1 * 4));
  return;
}



/* crt_bufcpy @ 004658f0 */

/* CRT: buffer copy helper (overlap-safe) */

void * __cdecl crt_bufcpy(void *dst,void *src,size_t size)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((src < dst) && (dst < (void *)(size + (int)src))) {
    puVar3 = (undefined4 *)((size - 4) + (int)src);
    puVar4 = (undefined4 *)((size - 4) + (int)dst);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = size >> 2;
      uVar2 = size & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return dst;
        case 2:
          goto switchD_00465aa7_caseD_2;
        case 3:
          goto switchD_00465aa7_caseD_3;
        }
        goto switchD_00465aa7_caseD_1;
      }
    }
    else {
      switch(size) {
      case 0:
        goto switchD_00465aa7_caseD_0;
      case 1:
        goto switchD_00465aa7_caseD_1;
      case 2:
        goto switchD_00465aa7_caseD_2;
      case 3:
        goto switchD_00465aa7_caseD_3;
      default:
        uVar1 = size - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_00465aa7_caseD_2;
            case 3:
              goto switchD_00465aa7_caseD_3;
            }
            goto switchD_00465aa7_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_00465aa7_caseD_2;
            case 3:
              goto switchD_00465aa7_caseD_3;
            }
            goto switchD_00465aa7_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_00465aa7_caseD_2;
            case 3:
              goto switchD_00465aa7_caseD_3;
            }
            goto switchD_00465aa7_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_00465aa7_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return dst;
    case 2:
switchD_00465aa7_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return dst;
    case 3:
switchD_00465aa7_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return dst;
    }
switchD_00465aa7_caseD_0:
    return dst;
  }
  puVar3 = dst;
  if (((uint)dst & 3) == 0) {
    uVar1 = size >> 2;
    uVar2 = size & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *(undefined4 *)src;
        src = (undefined4 *)((int)src + 4);
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return dst;
      case 2:
        goto switchD_00465925_caseD_2;
      case 3:
        goto switchD_00465925_caseD_3;
      }
      goto switchD_00465925_caseD_1;
    }
  }
  else {
    switch(size) {
    case 0:
      goto switchD_00465925_caseD_0;
    case 1:
      goto switchD_00465925_caseD_1;
    case 2:
      goto switchD_00465925_caseD_2;
    case 3:
      goto switchD_00465925_caseD_3;
    default:
      uVar1 = (size - 4) + ((uint)dst & 3);
      switch((uint)dst & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
        src = (void *)((int)src + 3);
        puVar3 = (undefined4 *)((int)dst + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_00465925_caseD_2;
          case 3:
            goto switchD_00465925_caseD_3;
          }
          goto switchD_00465925_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        src = (void *)((int)src + 2);
        puVar3 = (undefined4 *)((int)dst + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_00465925_caseD_2;
          case 3:
            goto switchD_00465925_caseD_3;
          }
          goto switchD_00465925_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        src = (void *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)dst + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_00465925_caseD_2;
          case 3:
            goto switchD_00465925_caseD_3;
          }
          goto switchD_00465925_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = *(undefined4 *)((int)src + (uVar1 - 7) * 4);
  case 6:
    puVar3[uVar1 - 6] = *(undefined4 *)((int)src + (uVar1 - 6) * 4);
  case 5:
    puVar3[uVar1 - 5] = *(undefined4 *)((int)src + (uVar1 - 5) * 4);
  case 4:
    puVar3[uVar1 - 4] = *(undefined4 *)((int)src + (uVar1 - 4) * 4);
  case 3:
    puVar3[uVar1 - 3] = *(undefined4 *)((int)src + (uVar1 - 3) * 4);
  case 2:
    puVar3[uVar1 - 2] = *(undefined4 *)((int)src + (uVar1 - 2) * 4);
  case 1:
    puVar3[uVar1 - 1] = *(undefined4 *)((int)src + (uVar1 - 1) * 4);
    src = (void *)((int)src + uVar1 * 4);
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_00465925_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    return dst;
  case 2:
switchD_00465925_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)src + 1);
    return dst;
  case 3:
switchD_00465925_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)src + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)src + 2);
    return dst;
  }
switchD_00465925_caseD_0:
  return dst;
}



/* crt_strcpy @ 00465c30 */

/* CRT strcpy implementation (word copy + null detection) */

char * __cdecl crt_strcpy(char *dst,char *src)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = (uint *)dst;
  while (((uint)src & 3) != 0) {
    bVar1 = (byte)*(uint *)src;
    uVar3 = (uint)bVar1;
    src = (char *)((int)src + 1);
    if (bVar1 == 0) goto LAB_00465d18;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *(uint *)src;
    uVar3 = *(uint *)src;
    src = (char *)((int)src + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_00465d18:
        *(byte *)puVar4 = (byte)uVar3;
        return dst;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return dst;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return dst;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return dst;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}



/* crt_strcat @ 00465c40 */

/* CRT strcat implementation (seek end, then copy) */

char * __cdecl crt_strcat(char *dst,char *src)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = (uint *)dst;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_00465c5c;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_00465c8f;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x00465cab;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_00465c5c:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x00465cab;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x00465cab;
    }
  }
LAB_00465c8f:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x00465cab:
  do {
    if (((uint)src & 3) == 0) {
      do {
        uVar2 = *(uint *)src;
        uVar4 = *(uint *)src;
        src = (char *)((int)src + 4);
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_00465d18:
            *(byte *)puVar5 = (byte)uVar4;
            return dst;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return dst;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return dst;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return dst;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*(uint *)src;
    uVar4 = (uint)bVar1;
    src = (char *)((int)src + 1);
    if (bVar1 == 0) goto LAB_00465d18;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}



/* crt_dosmaperr @ 00465d20 */

/* map Win32 error to errno/doserrno */

void __cdecl crt_dosmaperr(uint os_error)

{
  uint *puVar1;
  undefined **ppuVar2;
  int *piVar3;
  int iVar4;
  
  puVar1 = crt_doserrno_ptr();
  iVar4 = 0;
  *puVar1 = os_error;
  ppuVar2 = (undefined **)&crt_dosmaperr_table;
  do {
    if ((undefined *)os_error == *ppuVar2) {
      piVar3 = crt_errno_ptr();
      *piVar3 = *(int *)(iVar4 * 8 + 0x47b7c4);
      return;
    }
    ppuVar2 = ppuVar2 + 2;
    iVar4 = iVar4 + 1;
  } while (ppuVar2 < &PTR_crt_terminate_0047b928);
  if ((0x12 < os_error) && (os_error < 0x25)) {
    piVar3 = crt_errno_ptr();
    *piVar3 = 0xd;
    return;
  }
  if ((0xbb < os_error) && (os_error < 0xcb)) {
    piVar3 = crt_errno_ptr();
    *piVar3 = 8;
    return;
  }
  piVar3 = crt_errno_ptr();
  *piVar3 = 0x16;
  return;
}



/* crt_errno_ptr @ 00465d93 */

/* CRT errno pointer accessor (thread-local) */

int * crt_errno_ptr(void)

{
  DWORD *pDVar1;
  
  pDVar1 = crt_get_thread_data();
  return (int *)(pDVar1 + 2);
}



/* crt_doserrno_ptr @ 00465d9c */

/* CRT doserrno pointer accessor (thread-local) */

uint * crt_doserrno_ptr(void)

{
  DWORD *pDVar1;
  
  pDVar1 = crt_get_thread_data();
  return pDVar1 + 3;
}



/* crt_mktime @ 00465da5 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CRT: convert date/time to timestamp (mktime) */

long __cdecl crt_mktime(int year,int month,int day,int hour,int min,int sec,int dst)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_28 [2];
  int local_20;
  int local_18;
  uint local_14;
  int local_c;
  
  uVar3 = year - 0x76c;
  if (((int)uVar3 < 0x46) || (0x8a < (int)uVar3)) {
    iVar2 = -1;
  }
  else {
    iVar4 = *(int *)(&crt_day_of_year_leap + month * 4) + day;
    if (((uVar3 & 3) == 0) && (2 < month)) {
      iVar4 = iVar4 + 1;
    }
    crt_file_write_char();
    local_20 = hour;
    local_18 = month + -1;
    iVar2 = ((hour + (uVar3 * 0x16d + iVar4 + (year + -0x76d >> 2)) * 0x18) * 0x3c + min) * 0x3c +
            crt_timezone_offset + 0x7c558180 + sec;
    if ((dst == 1) ||
       (((dst == -1 && (crt_dst_flag != 0)) &&
        (local_14 = uVar3, local_c = iVar4, bVar1 = crt_get_local_time(local_28),
        CONCAT31(extraout_var,bVar1) != 0)))) {
      iVar2 = iVar2 + crt_timezone_seconds;
    }
  }
  return iVar2;
}



/* FUN_00465f2d @ 00465f2d */

void FUN_00465f2d(int param_1)

{
  __local_unwind2(*(int *)(param_1 + 0x18),*(int *)(param_1 + 0x1c));
  return;
}



/* crt_terminate @ 00465f48 */

/* invokes the per-thread terminate handler then aborts */

void crt_terminate(void)

{
  DWORD *pDVar1;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046fb98;
  puStack_10 = &LAB_00465e70;
  pvStack_14 = ExceptionList;
  local_8 = 0;
  ExceptionList = &pvStack_14;
  pDVar1 = crt_get_thread_data();
  if (pDVar1[0x18] != 0) {
    local_8 = 1;
    pDVar1 = crt_get_thread_data();
    (*(code *)pDVar1[0x18])();
  }
  local_8 = 0xffffffff;
  crt_abort_runtime();
  return;
}



/* crt_invalid_parameter_noinfo_noreturn @ 00465fa9 */

/* invokes invalid-parameter handler (if set) then terminates */

void crt_invalid_parameter_noinfo_noreturn(void)

{
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046fbb0;
  puStack_10 = &LAB_00465e70;
  pvStack_14 = ExceptionList;
  ExceptionList = &pvStack_14;
  if (PTR_crt_terminate_0047b928 != (undefined *)0x0) {
    local_8 = 1;
    ExceptionList = &pvStack_14;
    (*(code *)PTR_crt_terminate_0047b928)();
  }
  local_8 = 0xffffffff;
  crt_terminate();
  return;
}



/* crt_read @ 00465fff */

/* CRT: read handle with lock */

int __cdecl crt_read(int fd,char *buf,uint count)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  
  if (((uint)fd < (uint)crt_nhandle) &&
     (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0)) {
    crt_lock_fh(fd);
    iVar1 = crt_read_nolock(fd,buf,count);
    crt_unlock_fh(fd);
    return iVar1;
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 9;
  puVar3 = crt_doserrno_ptr();
  *puVar3 = 0;
  return -1;
}



/* crt_read_nolock @ 00466064 */

/* CRT: read handle (no lock), CRLF translation */

int __cdecl crt_read_nolock(int fd,char *buf,uint count)

{
  void ***pppvVar1;
  char cVar2;
  void *pvVar3;
  byte bVar4;
  uint uVar5;
  WINBOOL WVar6;
  DWORD DVar7;
  int *piVar8;
  uint *puVar9;
  char *pcVar10;
  int iVar11;
  DWORD local_10;
  char *local_c;
  char local_5;
  
  local_c = (char *)0x0;
  if (count != 0) {
    uVar5 = fd & 0x1f;
    pppvVar1 = &crt_pioinfo_table + (fd >> 5);
    iVar11 = uVar5 * 0x24;
    pvVar3 = (&crt_pioinfo_table)[fd >> 5][uVar5 * 9 + 1];
    if (((uint)pvVar3 & 2) == 0) {
      pcVar10 = buf;
      if ((((uint)pvVar3 & 0x48) != 0) &&
         (cVar2 = *(char *)((int)(&crt_pioinfo_table)[fd >> 5] + iVar11 + 5), cVar2 != '\n')) {
        count = count - 1;
        *buf = cVar2;
        pcVar10 = buf + 1;
        local_c = (char *)0x1;
        *(undefined1 *)((int)*pppvVar1 + iVar11 + 5) = 10;
      }
      WVar6 = ReadFile((*pppvVar1)[uVar5 * 9],pcVar10,count,&local_10,(LPOVERLAPPED)0x0);
      if (WVar6 == 0) {
        DVar7 = GetLastError();
        if (DVar7 == 5) {
          piVar8 = crt_errno_ptr();
          *piVar8 = 9;
          puVar9 = crt_doserrno_ptr();
          *puVar9 = 5;
        }
        else {
          if (DVar7 == 0x6d) {
            return 0;
          }
          crt_dosmaperr(DVar7);
        }
        return -1;
      }
      bVar4 = *(byte *)(*pppvVar1 + uVar5 * 9 + 1);
      if ((bVar4 & 0x80) == 0) {
        return (int)local_c + local_10;
      }
      if ((local_10 == 0) || (*buf != '\n')) {
        bVar4 = bVar4 & 0xfb;
      }
      else {
        bVar4 = bVar4 | 4;
      }
      *(byte *)(*pppvVar1 + uVar5 * 9 + 1) = bVar4;
      count = (uint)buf;
      local_c = buf + (int)local_c + local_10;
      pcVar10 = buf;
      if (buf < local_c) {
        do {
          cVar2 = *(char *)count;
          if (cVar2 == '\x1a') {
            bVar4 = *(byte *)(*pppvVar1 + uVar5 * 9 + 1);
            if ((bVar4 & 0x40) == 0) {
              *(byte *)(*pppvVar1 + uVar5 * 9 + 1) = bVar4 | 2;
            }
            break;
          }
          if (cVar2 == '\r') {
            if (count < local_c + -1) {
              if (*(char *)(count + 1) == '\n') {
                count = count + 2;
                goto LAB_004661ef;
              }
              *pcVar10 = '\r';
              pcVar10 = pcVar10 + 1;
              count = count + 1;
            }
            else {
              count = count + 1;
              WVar6 = ReadFile((*pppvVar1)[uVar5 * 9],&local_5,1,&local_10,(LPOVERLAPPED)0x0);
              if (((WVar6 == 0) && (DVar7 = GetLastError(), DVar7 != 0)) || (local_10 == 0)) {
LAB_00466209:
                *pcVar10 = '\r';
LAB_0046620c:
                pcVar10 = pcVar10 + 1;
              }
              else if (((uint)(*pppvVar1)[uVar5 * 9 + 1] & 0x48) == 0) {
                if ((pcVar10 == buf) && (local_5 == '\n')) {
LAB_004661ef:
                  *pcVar10 = '\n';
                  goto LAB_0046620c;
                }
                crt_lseek_nolock(fd,-1,1);
                if (local_5 != '\n') goto LAB_00466209;
              }
              else {
                if (local_5 == '\n') goto LAB_004661ef;
                *pcVar10 = '\r';
                pcVar10 = pcVar10 + 1;
                *(char *)((int)*pppvVar1 + iVar11 + 5) = local_5;
              }
            }
          }
          else {
            *pcVar10 = cVar2;
            pcVar10 = pcVar10 + 1;
            count = count + 1;
          }
        } while (count < local_c);
      }
      return (int)pcVar10 - (int)buf;
    }
  }
  return 0;
}



/* crt_io_init @ 0046623d */

/* CRT file handle table init */

void crt_io_init(void)

{
  undefined4 *puVar1;
  void **ppvVar2;
  undefined4 *puVar3;
  DWORD DVar4;
  HANDLE hFile;
  byte *pbVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  _STARTUPINFOA local_4c;
  byte *local_8;
  
  ppvVar2 = _malloc(0x480);
  if (ppvVar2 == (void **)0x0) {
    __amsg_exit(0x1b);
  }
  crt_nhandle = 0x20;
  crt_pioinfo_table = ppvVar2;
  for (; ppvVar2 < crt_pioinfo_table + 0x120; ppvVar2 = ppvVar2 + 9) {
    *(undefined1 *)(ppvVar2 + 1) = 0;
    *ppvVar2 = (void *)0xffffffff;
    ppvVar2[2] = (void *)0x0;
    *(undefined1 *)((int)ppvVar2 + 5) = 10;
  }
  GetStartupInfoA(&local_4c);
  if ((local_4c.cbReserved2 != 0) && ((int *)local_4c.lpReserved2 != (int *)0x0)) {
    iVar8 = *(int *)local_4c.lpReserved2;
    pbVar5 = (byte *)((int)local_4c.lpReserved2 + 4);
    local_8 = pbVar5 + iVar8;
    if (0x7ff < iVar8) {
      iVar8 = 0x800;
    }
    iVar9 = iVar8;
    if (crt_nhandle < iVar8) {
      puVar6 = &DAT_004da3c4;
      do {
        puVar3 = _malloc(0x480);
        iVar9 = crt_nhandle;
        if (puVar3 == (undefined4 *)0x0) break;
        crt_nhandle = crt_nhandle + 0x20;
        *puVar6 = puVar3;
        puVar1 = puVar3;
        for (; puVar3 < puVar1 + 0x120; puVar3 = puVar3 + 9) {
          *(undefined1 *)(puVar3 + 1) = 0;
          *puVar3 = 0xffffffff;
          puVar3[2] = 0;
          *(undefined1 *)((int)puVar3 + 5) = 10;
          puVar1 = (undefined4 *)*puVar6;
        }
        puVar6 = puVar6 + 1;
        iVar9 = iVar8;
      } while (crt_nhandle < iVar8);
    }
    uVar7 = 0;
    if (0 < iVar9) {
      do {
        if (((*(HANDLE *)local_8 != (HANDLE)0xffffffff) && ((*pbVar5 & 1) != 0)) &&
           (((*pbVar5 & 8) != 0 || (DVar4 = GetFileType(*(HANDLE *)local_8), DVar4 != 0)))) {
          ppvVar2 = (&crt_pioinfo_table)[(int)uVar7 >> 5];
          ppvVar2[(uVar7 & 0x1f) * 9] = *(void **)local_8;
          *(byte *)(ppvVar2 + (uVar7 & 0x1f) * 9 + 1) = *pbVar5;
        }
        local_8 = local_8 + 4;
        uVar7 = uVar7 + 1;
        pbVar5 = pbVar5 + 1;
      } while ((int)uVar7 < iVar9);
    }
  }
  iVar8 = 0;
  do {
    ppvVar2 = crt_pioinfo_table + iVar8 * 9;
    if (crt_pioinfo_table[iVar8 * 9] == (void *)0xffffffff) {
      *(undefined1 *)(ppvVar2 + 1) = 0x81;
      if (iVar8 == 0) {
        DVar4 = 0xfffffff6;
      }
      else {
        DVar4 = 0xfffffff5 - (iVar8 != 1);
      }
      hFile = GetStdHandle(DVar4);
      if ((hFile != (HANDLE)0xffffffff) && (DVar4 = GetFileType(hFile), DVar4 != 0)) {
        *ppvVar2 = hFile;
        if ((DVar4 & 0xff) != 2) {
          if ((DVar4 & 0xff) == 3) {
            *(byte *)(ppvVar2 + 1) = *(byte *)(ppvVar2 + 1) | 8;
          }
          goto LAB_004663e2;
        }
      }
      *(byte *)(ppvVar2 + 1) = *(byte *)(ppvVar2 + 1) | 0x40;
    }
    else {
      *(byte *)(ppvVar2 + 1) = *(byte *)(ppvVar2 + 1) | 0x80;
    }
LAB_004663e2:
    iVar8 = iVar8 + 1;
    if (2 < iVar8) {
      SetHandleCount(crt_nhandle);
      return;
    }
  } while( true );
}



/* crt_lseek @ 004663f9 */

/* lseek wrapper (locks file handle, then SetFilePointer) */

long __cdecl crt_lseek(int fd,long offset,int origin)

{
  long lVar1;
  int *piVar2;
  uint *puVar3;
  
  if (((uint)fd < (uint)crt_nhandle) &&
     (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0)) {
    crt_lock_fh(fd);
    lVar1 = crt_lseek_nolock(fd,offset,origin);
    crt_unlock_fh(fd);
    return lVar1;
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 9;
  puVar3 = crt_doserrno_ptr();
  *puVar3 = 0;
  return -1;
}



/* crt_lseek_nolock @ 0046645e */

/* lseek implementation via SetFilePointer */

long __cdecl crt_lseek_nolock(int fd,long offset,int origin)

{
  void *hFile;
  int *piVar1;
  DWORD DVar2;
  uint os_error;
  
  hFile = crt_get_osfhandle(fd);
  if (hFile == (void *)0xffffffff) {
    piVar1 = crt_errno_ptr();
    *piVar1 = 9;
  }
  else {
    DVar2 = SetFilePointer(hFile,offset,(PLONG)0x0,origin);
    if (DVar2 == 0xffffffff) {
      os_error = GetLastError();
    }
    else {
      os_error = 0;
    }
    if (os_error == 0) {
      *(byte *)((&crt_pioinfo_table)[fd >> 5] + (fd & 0x1fU) * 9 + 1) =
           *(byte *)((&crt_pioinfo_table)[fd >> 5] + (fd & 0x1fU) * 9 + 1) & 0xfd;
      return DVar2;
    }
    crt_dosmaperr(os_error);
  }
  return -1;
}



/* crt_lcmap_string @ 004664d1 */

/* CRT: LCMapString wrapper with multibyte/Unicode handling */

int __cdecl
crt_lcmap_string(uint locale,uint flags,char *src,int srclen,ushort *dst,int dstlen,uint codepage,
                int use_cp)

{
  int iVar1;
  int iVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fbd0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  if (crt_codepage_type == 0) {
    ExceptionList = &local_14;
    iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,&crt_winver,1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      crt_codepage_type = 2;
    }
    else {
      crt_codepage_type = 1;
    }
  }
  if (0 < srclen) {
    srclen = crt_environ_expand(src,srclen);
  }
  if (crt_codepage_type == 2) {
    iVar1 = LCMapStringA(locale,flags,src,srclen,(LPSTR)dst,dstlen);
    ExceptionList = local_14;
    return iVar1;
  }
  if (crt_codepage_type == 1) {
    if (codepage == 0) {
      codepage = crt_acp_codepage;
    }
    iVar1 = MultiByteToWideChar(codepage,(-(uint)(use_cp != 0) & 8) + 1,src,srclen,(LPWSTR)0x0,0);
    if (iVar1 != 0) {
      local_8 = 0;
      crt_chkstk();
      local_8 = 0xffffffff;
      if ((&stack0x00000000 != (undefined1 *)0x3c) &&
         (iVar2 = MultiByteToWideChar(codepage,1,src,srclen,(LPWSTR)&stack0xffffffc4,iVar1),
         iVar2 != 0)) {
        iVar2 = LCMapStringW(locale,flags,(LPCWSTR)&stack0xffffffc4,iVar1,(LPWSTR)0x0,0);
        if (iVar2 != 0) {
          if ((flags & 0x400) == 0) {
            local_8 = 1;
            crt_chkstk();
            local_8 = 0xffffffff;
            if (&stack0x00000000 == (undefined1 *)0x3c) {
              ExceptionList = local_14;
              return 0;
            }
            iVar1 = LCMapStringW(locale,flags,(LPCWSTR)&stack0xffffffc4,iVar1,
                                 (LPWSTR)&stack0xffffffc4,iVar2);
            if (iVar1 == 0) {
              ExceptionList = local_14;
              return 0;
            }
            if (dstlen == 0) {
              dstlen = 0;
              dst = (ushort *)0x0;
            }
            iVar2 = WideCharToMultiByte(codepage,0x220,(LPCWCH)&stack0xffffffc4,iVar2,(LPSTR)dst,
                                        dstlen,(LPCCH)0x0,(LPBOOL)0x0);
            iVar1 = iVar2;
          }
          else {
            if (dstlen == 0) {
              ExceptionList = local_14;
              return iVar2;
            }
            if (dstlen < iVar2) {
              ExceptionList = local_14;
              return 0;
            }
            iVar1 = LCMapStringW(locale,flags,(LPCWSTR)&stack0xffffffc4,iVar1,(LPWSTR)dst,dstlen);
          }
          if (iVar1 != 0) {
            ExceptionList = local_14;
            return iVar2;
          }
        }
      }
    }
  }
  ExceptionList = local_14;
  return 0;
}



/* FUN_004666f5 @ 004666f5 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_4666f5(int32_t* arg1) */

int __cdecl FUN_004666f5(int *arg1)

{
  byte bVar1;
  undefined3 extraout_var;
  int iVar2;
  void *pvVar3;
  
  bVar1 = crt_free_osfhandle(arg1[4]);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0;
  }
  if (arg1 == (int *)&crt_stdout_struct) {
    iVar2 = 0;
  }
  else {
    if (arg1 != (int *)&crt_stderr_struct) {
      return 0;
    }
    iVar2 = 1;
  }
  crt_file_handle_flags = crt_file_handle_flags + 1;
  if ((*(ushort *)(arg1 + 3) & 0x10c) != 0) {
    return 0;
  }
  if ((&crt_lc_ctype_type)[iVar2] == 0) {
    pvVar3 = _malloc(0x1000);
    (&crt_lc_ctype_type)[iVar2] = pvVar3;
    if (pvVar3 == (void *)0x0) {
      arg1[2] = (int)(arg1 + 5);
      *arg1 = (int)(arg1 + 5);
      arg1[6] = 2;
      arg1[1] = 2;
      goto LAB_00466771;
    }
  }
  iVar2 = (&crt_lc_ctype_type)[iVar2];
  arg1[6] = 0x1000;
  arg1[2] = iVar2;
  *arg1 = iVar2;
  arg1[1] = 0x1000;
LAB_00466771:
  *(ushort *)(arg1 + 3) = *(ushort *)(arg1 + 3) | 0x1102;
  return 1;
}



/* FUN_00466782 @ 00466782 */

void __cdecl FUN_00466782(int param_1,int *param_2)

{
  if ((param_1 != 0) && ((*(byte *)((int)param_2 + 0xd) & 0x10) != 0)) {
    crt_flushbuf(param_2);
    *(byte *)((int)param_2 + 0xd) = *(byte *)((int)param_2 + 0xd) & 0xee;
    param_2[6] = 0;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}



/* crt_calloc @ 004667ac */

/* CRT: allocate zeroed block (count*size) */

void * __cdecl crt_calloc(uint count,uint size)

{
  int iVar1;
  uint size_00;
  uint uVar2;
  uint _Size;
  LPVOID local_24;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046fbe8;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  size_00 = count * size;
  uVar2 = size_00;
  ExceptionList = &local_14;
  if (size_00 < 0xffffffe1) {
    if (size_00 == 0) {
      uVar2 = 1;
    }
    uVar2 = uVar2 + 0xf & 0xfffffff0;
    ExceptionList = &local_14;
  }
  do {
    local_24 = (LPVOID)0x0;
    if (uVar2 < 0xffffffe1) {
      if (crt_heap_mode == 3) {
        if (size_00 <= crt_sbh_reserved_b) {
          crt_lock(9);
          local_8 = 0;
          local_24 = crt_sbh_alloc(size_00);
          local_8 = 0xffffffff;
          FUN_00466845();
          _Size = size_00;
          if (local_24 == (void *)0x0) goto LAB_00466899;
LAB_00466888:
          _memset(local_24,0,_Size);
        }
LAB_00466894:
        if (local_24 != (LPVOID)0x0) {
          ExceptionList = local_14;
          return local_24;
        }
      }
      else {
        if ((crt_heap_mode != 2) || (crt_timezone_data_block < uVar2)) goto LAB_00466894;
        crt_lock(9);
        local_8 = 1;
        local_24 = crt_sbh_alloc_units(uVar2 >> 4);
        local_8 = 0xffffffff;
        FUN_004668ce();
        _Size = uVar2;
        if (local_24 != (void *)0x0) goto LAB_00466888;
      }
LAB_00466899:
      local_24 = HeapAlloc(crt_heap_handle,8,uVar2);
    }
    if (local_24 != (LPVOID)0x0) {
      ExceptionList = local_14;
      return local_24;
    }
    if (crt_nh_malloc_flag == 0) {
      ExceptionList = local_14;
      return (void *)0x0;
    }
    iVar1 = crt_call_new_handler(uVar2);
    if (iVar1 == 0) {
      ExceptionList = local_14;
      return (void *)0x0;
    }
  } while( true );
}



/* FUN_00466845 @ 00466845 */

/* [binja] int32_t sub_466845() */

int FUN_00466845(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* FUN_004668ce @ 004668ce */

/* [binja] int32_t sub_4668ce() */

int FUN_004668ce(void)

{
  int iVar1;
  
  iVar1 = crt_unlock(9);
  return iVar1;
}



/* crt_exception_filter @ 004668e9 */

/* CRT exception filter/dispatch */

long __cdecl crt_exception_filter(int code,_EXCEPTION_POINTERS *info)

{
  code *pcVar1;
  DWORD DVar2;
  DWORD DVar3;
  DWORD *pDVar4;
  int *piVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  
  pDVar4 = crt_get_thread_data();
  piVar5 = FUN_00466a27(code,(int *)pDVar4[0x14]);
  if ((piVar5 == (int *)0x0) || (pcVar1 = (code *)piVar5[2], pcVar1 == (code *)0x0)) {
    lVar6 = UnhandledExceptionFilter((_EXCEPTION_POINTERS *)info);
  }
  else if (pcVar1 == (code *)0x5) {
    piVar5[2] = 0;
    lVar6 = 1;
  }
  else {
    if (pcVar1 != (code *)0x1) {
      DVar2 = pDVar4[0x15];
      pDVar4[0x15] = (DWORD)info;
      if (piVar5[1] == 8) {
        if (crt_tls_data_a < crt_tls_data_c + crt_tls_data_a) {
          iVar7 = crt_tls_data_a * 0xc;
          iVar8 = crt_tls_data_a;
          do {
            *(undefined4 *)(iVar7 + 8 + pDVar4[0x14]) = 0;
            iVar8 = iVar8 + 1;
            iVar7 = iVar7 + 0xc;
          } while (iVar8 < crt_tls_data_c + crt_tls_data_a);
        }
        iVar7 = *piVar5;
        DVar3 = pDVar4[0x16];
        if (iVar7 == -0x3fffff72) {
          pDVar4[0x16] = 0x83;
        }
        else if (iVar7 == -0x3fffff70) {
          pDVar4[0x16] = 0x81;
        }
        else if (iVar7 == -0x3fffff6f) {
          pDVar4[0x16] = 0x84;
        }
        else if (iVar7 == -0x3fffff6d) {
          pDVar4[0x16] = 0x85;
        }
        else if (iVar7 == -0x3fffff73) {
          pDVar4[0x16] = 0x82;
        }
        else if (iVar7 == -0x3fffff71) {
          pDVar4[0x16] = 0x86;
        }
        else if (iVar7 == -0x3fffff6e) {
          pDVar4[0x16] = 0x8a;
        }
        (*pcVar1)(8,pDVar4[0x16]);
        pDVar4[0x16] = DVar3;
      }
      else {
        piVar5[2] = 0;
        (*pcVar1)(piVar5[1]);
      }
      pDVar4[0x15] = DVar2;
    }
    lVar6 = -1;
  }
  return lVar6;
}



/* FUN_00466a27 @ 00466a27 */

int * __cdecl FUN_00466a27(int param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = param_2;
  if (*param_2 != param_1) {
    do {
      piVar1 = piVar1 + 3;
      if (param_2 + crt_tls_data_b * 3 <= piVar1) break;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + crt_tls_data_b * 3 <= piVar1) || (*piVar1 != param_1)) {
    piVar1 = (int *)0x0;
  }
  return piVar1;
}



/* FUN_00466a61 @ 00466a61 */

/* [binja] HMODULE sub_466a61(int32_t* arg1) */

void * __cdecl FUN_00466a61(int *arg1)

{
  HMODULE pHVar1;
  int iVar2;
  
  *arg1 = 0;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  if (((short)pHVar1->unused == 0x5a4d) && (pHVar1[0xf].unused != 0)) {
    iVar2 = (int)&pHVar1->unused + pHVar1[0xf].unused;
    *(undefined1 *)arg1 = *(undefined1 *)(iVar2 + 0x1a);
    pHVar1 = (HMODULE)CONCAT31((int3)((uint)iVar2 >> 8),*(undefined1 *)(iVar2 + 0x1b));
    *(undefined1 *)((int)arg1 + 1) = *(undefined1 *)(iVar2 + 0x1b);
  }
  return pHVar1;
}



/* crt_heap_select @ 00466a8e */

/* selects CRT heap strategy */

int crt_heap_select(void)

{
  char cVar1;
  WINBOOL WVar2;
  DWORD DVar3;
  int iVar4;
  long lVar5;
  char *pcVar6;
  char *this;
  int unaff_EBX;
  char local_1230 [4240];
  char local_1a0 [260];
  DWORD local_9c;
  uint local_98;
  DWORD local_8c;
  CHAR aCStackY_18 [4];
  byte bVar7;
  
  crt_chkstk();
  local_9c = 0x94;
  WVar2 = GetVersionExA((LPOSVERSIONINFOA)&local_9c);
  if (((WVar2 == 0) || (local_8c != 2)) || (local_98 < 5)) {
    aCStackY_18[0] = -0x18;
    aCStackY_18[1] = 'j';
    aCStackY_18[2] = 'F';
    aCStackY_18[3] = '\0';
    DVar3 = GetEnvironmentVariableA("__MSVCRT_HEAP_SELECT",local_1230,0x1090);
    if (DVar3 != 0) {
      pcVar6 = local_1230;
      while (local_1230[0] != '\0') {
        cVar1 = *pcVar6;
        if (('`' < cVar1) && (cVar1 < '{')) {
          *pcVar6 = cVar1 + -0x20;
        }
        pcVar6 = pcVar6 + 1;
        local_1230[0] = *pcVar6;
      }
      builtin_memcpy(aCStackY_18,"&kF",4);
      iVar4 = _strncmp("__GLOBAL_HEAP_SELECTED",local_1230,0x16);
      if (iVar4 == 0) {
        pcVar6 = local_1230;
      }
      else {
        builtin_memcpy(aCStackY_18,"HkF",4);
        GetModuleFileNameA((HMODULE)0x0,local_1a0,0x104);
        pcVar6 = local_1a0;
        while (local_1a0[0] != '\0') {
          cVar1 = *pcVar6;
          if (('`' < cVar1) && (cVar1 < '{')) {
            *pcVar6 = cVar1 + -0x20;
          }
          pcVar6 = pcVar6 + 1;
          local_1a0[0] = *pcVar6;
        }
        pcVar6 = _strstr(local_1230,local_1a0);
      }
      if ((pcVar6 != (char *)0x0) && (pcVar6 = _strchr(pcVar6,0x2c), pcVar6 != (char *)0x0)) {
        pcVar6 = pcVar6 + 1;
        cVar1 = *pcVar6;
        this = pcVar6;
        while (cVar1 != '\0') {
          if (*this == ';') {
            *this = '\0';
          }
          else {
            this = this + 1;
          }
          cVar1 = *this;
        }
        aCStackY_18[0] = -0x52;
        aCStackY_18[1] = 'k';
        aCStackY_18[2] = 'F';
        aCStackY_18[3] = '\0';
        lVar5 = crt_strtol_l(this,pcVar6,(char *)0x0,(char **)0xa,unaff_EBX);
        if (lVar5 == 2) {
          return 2;
        }
        if (lVar5 == 3) {
          return 3;
        }
        if (lVar5 == 1) {
          return 1;
        }
      }
    }
    bVar7 = (byte)unaff_EBX;
    FUN_00466a61((int *)&stack0xfffffff8);
    iVar4 = 3 - (uint)(bVar7 < 6);
  }
  else {
    iVar4 = 1;
  }
  return iVar4;
}



/* crt_heap_init @ 00466bd6 */

/* CRT heap init (small/large block selection) */

undefined4 __cdecl crt_heap_init(int param_1)

{
  undefined **ppuVar1;
  
  crt_heap_handle = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (crt_heap_handle != (HANDLE)0x0) {
    crt_heap_mode = crt_heap_select();
    if (crt_heap_mode == 3) {
      ppuVar1 = (undefined **)crt_sbh_init(0x3f8);
    }
    else {
      if (crt_heap_mode != 2) {
        return 1;
      }
      ppuVar1 = crt_sbh_create_region();
    }
    if (ppuVar1 != (undefined **)0x0) {
      return 1;
    }
    HeapDestroy(crt_heap_handle);
  }
  return 0;
}



/* crt_sbh_init @ 00466c33 */

/* CRT small-block heap init */

undefined4 __cdecl crt_sbh_init(undefined4 param_1)

{
  crt_sbh_header_base = HeapAlloc(crt_heap_handle,0,0x140);
  if (crt_sbh_header_base == (LPVOID)0x0) {
    return 0;
  }
  crt_sbh_page_ptr = 0;
  crt_sbh_entry_count = 0;
  crt_sbh_scan_ptr = crt_sbh_header_base;
  crt_sbh_reserved_b = param_1;
  crt_sbh_capacity = 0x10;
  return 1;
}



/* crt_sbh_find_region @ 00466c7b */

/* CRT: find small-block heap region for a pointer */

void * __cdecl crt_sbh_find_region(void *ptr)

{
  void *pvVar1;
  
  pvVar1 = crt_sbh_header_base;
  while( true ) {
    if ((void *)((int)crt_sbh_header_base + crt_sbh_entry_count * 0x14) <= pvVar1) {
      return (void *)0x0;
    }
    if ((uint)((int)ptr - *(int *)((int)pvVar1 + 0xc)) < 0x100000) break;
    pvVar1 = (void *)((int)pvVar1 + 0x14);
  }
  return pvVar1;
}



/* crt_sbh_free_block @ 00466ca6 */

/* [binja] int32_t* sub_466ca6(void* arg1, int32_t* arg2) */

int * __cdecl crt_sbh_free_block(void *arg1,int *arg2)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  byte bVar7;
  uint uVar8;
  void *pvVar9;
  void *pvVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  uint local_8;
  
  piVar6 = *(int **)((int)arg1 + 0x10);
  puVar11 = (uint *)(arg2 + -1);
  uVar13 = (uint)((int)arg2 - *(int *)((int)arg1 + 0xc)) >> 0xf;
  piVar2 = piVar6 + uVar13 * 0x81 + 0x51;
  uVar12 = *puVar11;
  local_8 = uVar12 - 1;
  if ((local_8 & 1) == 0) {
    uVar4 = *(uint *)(local_8 + (int)puVar11);
    uVar5 = arg2[-2];
    if ((uVar4 & 1) == 0) {
      uVar8 = ((int)uVar4 >> 4) - 1;
      if (0x3f < uVar8) {
        uVar8 = 0x3f;
      }
      if (*(int *)((int)puVar11 + uVar12 + 3) == *(int *)((int)puVar11 + uVar12 + 7)) {
        if (uVar8 < 0x20) {
          pcVar1 = (char *)(uVar8 + 4 + (int)piVar6);
          uVar8 = ~(0x80000000U >> ((byte)uVar8 & 0x1f));
          piVar6[uVar13 + 0x11] = piVar6[uVar13 + 0x11] & uVar8;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *(uint *)arg1 = *(uint *)arg1 & uVar8;
          }
        }
        else {
          pcVar1 = (char *)(uVar8 + 4 + (int)piVar6);
          uVar8 = ~(0x80000000U >> ((byte)uVar8 - 0x20 & 0x1f));
          piVar6[uVar13 + 0x31] = piVar6[uVar13 + 0x31] & uVar8;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *(uint *)((int)arg1 + 4) = *(uint *)((int)arg1 + 4) & uVar8;
          }
        }
      }
      local_8 = local_8 + uVar4;
      *(undefined4 *)(*(int *)((int)puVar11 + uVar12 + 7) + 4) =
           *(undefined4 *)((int)puVar11 + uVar12 + 3);
      *(undefined4 *)(*(int *)((int)puVar11 + uVar12 + 3) + 8) =
           *(undefined4 *)((int)puVar11 + uVar12 + 7);
    }
    pvVar9 = (void *)(((int)local_8 >> 4) - 1);
    if ((void *)0x3f < pvVar9) {
      pvVar9 = (void *)0x3f;
    }
    pvVar10 = arg1;
    if ((uVar5 & 1) == 0) {
      puVar11 = (uint *)((int)puVar11 - uVar5);
      pvVar10 = (void *)(((int)uVar5 >> 4) - 1);
      if ((void *)0x3f < pvVar10) {
        pvVar10 = (void *)0x3f;
      }
      local_8 = local_8 + uVar5;
      pvVar9 = (void *)(((int)local_8 >> 4) - 1);
      if ((void *)0x3f < pvVar9) {
        pvVar9 = (void *)0x3f;
      }
      if (pvVar10 != pvVar9) {
        if (puVar11[1] == puVar11[2]) {
          if (pvVar10 < (void *)0x20) {
            uVar12 = ~(0x80000000U >> ((byte)pvVar10 & 0x1f));
            piVar6[uVar13 + 0x11] = piVar6[uVar13 + 0x11] & uVar12;
            pcVar1 = (char *)((int)pvVar10 + 4U + (int)piVar6);
            *pcVar1 = *pcVar1 + -1;
            if (*pcVar1 == '\0') {
              *(uint *)arg1 = *(uint *)arg1 & uVar12;
            }
          }
          else {
            uVar12 = ~(0x80000000U >> ((byte)pvVar10 - 0x20 & 0x1f));
            piVar6[uVar13 + 0x31] = piVar6[uVar13 + 0x31] & uVar12;
            pcVar1 = (char *)((int)pvVar10 + 4U + (int)piVar6);
            *pcVar1 = *pcVar1 + -1;
            if (*pcVar1 == '\0') {
              *(uint *)((int)arg1 + 4) = *(uint *)((int)arg1 + 4) & uVar12;
            }
          }
        }
        *(uint *)(puVar11[2] + 4) = puVar11[1];
        *(uint *)(puVar11[1] + 8) = puVar11[2];
      }
    }
    if (((uVar5 & 1) != 0) || (pvVar10 != pvVar9)) {
      puVar11[1] = piVar2[(int)pvVar9 * 2 + 1];
      puVar11[2] = (uint)(piVar2 + (int)pvVar9 * 2);
      (piVar2 + (int)pvVar9 * 2)[1] = (int)puVar11;
      *(uint **)(puVar11[1] + 8) = puVar11;
      if (puVar11[1] == puVar11[2]) {
        cVar3 = *(char *)((int)pvVar9 + 4U + (int)piVar6);
        *(char *)((int)pvVar9 + 4U + (int)piVar6) = cVar3 + '\x01';
        bVar7 = (byte)pvVar9;
        if (pvVar9 < (void *)0x20) {
          if (cVar3 == '\0') {
            *(uint *)arg1 = *(uint *)arg1 | 0x80000000U >> (bVar7 & 0x1f);
          }
          piVar6[uVar13 + 0x11] = piVar6[uVar13 + 0x11] | 0x80000000U >> (bVar7 & 0x1f);
        }
        else {
          if (cVar3 == '\0') {
            *(uint *)((int)arg1 + 4) =
                 *(uint *)((int)arg1 + 4) | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
          }
          piVar6[uVar13 + 0x31] = piVar6[uVar13 + 0x31] | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
        }
      }
    }
    *puVar11 = local_8;
    *(uint *)((local_8 - 4) + (int)puVar11) = local_8;
    *piVar2 = *piVar2 + -1;
    piVar6 = piVar2;
    if (*piVar2 == 0) {
      if (crt_sbh_page_ptr != (void *)0x0) {
        VirtualFree((LPVOID)(crt_sbh_page_index * 0x8000 + *(int *)((int)crt_sbh_page_ptr + 0xc)),0x8000,
                    0x4000);
        *(uint *)((int)crt_sbh_page_ptr + 8) =
             *(uint *)((int)crt_sbh_page_ptr + 8) | 0x80000000U >> ((byte)crt_sbh_page_index & 0x1f);
        *(undefined4 *)(*(int *)((int)crt_sbh_page_ptr + 0x10) + 0xc4 + crt_sbh_page_index * 4) = 0;
        pcVar1 = (char *)(*(int *)((int)crt_sbh_page_ptr + 0x10) + 0x43);
        *pcVar1 = *pcVar1 + -1;
        if (*(char *)(*(int *)((int)crt_sbh_page_ptr + 0x10) + 0x43) == '\0') {
          *(uint *)((int)crt_sbh_page_ptr + 4) = *(uint *)((int)crt_sbh_page_ptr + 4) & 0xfffffffe;
        }
        if (*(int *)((int)crt_sbh_page_ptr + 8) == -1) {
          VirtualFree(*(LPVOID *)((int)crt_sbh_page_ptr + 0xc),0,0x8000);
          HeapFree(crt_heap_handle,0,*(LPVOID *)((int)crt_sbh_page_ptr + 0x10));
          crt_memmove(crt_sbh_page_ptr,(void *)((int)crt_sbh_page_ptr + 0x14),
                      (crt_sbh_entry_count * 0x14 - (int)crt_sbh_page_ptr) + -0x14 + crt_sbh_header_base);
          crt_sbh_entry_count = crt_sbh_entry_count + -1;
          if (crt_sbh_page_ptr < arg1) {
            arg1 = (void *)((int)arg1 + -0x14);
          }
          crt_sbh_scan_ptr = crt_sbh_header_base;
        }
      }
      crt_sbh_page_ptr = arg1;
      piVar6 = arg1;
      crt_sbh_page_index = uVar13;
    }
  }
  return piVar6;
}



/* crt_sbh_alloc @ 00466fcf */

/* allocates a small-block heap chunk (size rounded to 16 bytes) */

void * __cdecl crt_sbh_alloc(uint size)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  int *piVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  uint *puVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  uint local_10;
  uint local_c;
  int local_8;
  
  puVar8 = crt_sbh_header_base + crt_sbh_entry_count * 5;
  uVar6 = size + 0x17 & 0xfffffff0;
  iVar7 = ((int)(size + 0x17) >> 4) + -1;
  bVar5 = (byte)iVar7;
  size = (uint)crt_sbh_scan_ptr;
  if (iVar7 < 0x20) {
    local_10 = 0xffffffff >> (bVar5 & 0x1f);
    local_c = 0xffffffff;
  }
  else {
    local_c = 0xffffffff >> (bVar5 - 0x20 & 0x1f);
    local_10 = 0;
  }
  for (; (size < puVar8 && ((*(uint *)(size + 4) & local_c) == 0 && (*(uint *)size & local_10) == 0)
         ); size = (uint)(size + 0x14)) {
  }
  puVar11 = crt_sbh_header_base;
  if ((uint *)size == puVar8) {
    for (; (puVar11 < crt_sbh_scan_ptr && ((puVar11[1] & local_c) == 0 && (*puVar11 & local_10) == 0));
        puVar11 = puVar11 + 5) {
    }
    size = (uint)puVar11;
    if (puVar11 == crt_sbh_scan_ptr) {
      for (; (puVar11 < puVar8 && (puVar11[2] == 0)); puVar11 = puVar11 + 5) {
      }
      puVar12 = crt_sbh_header_base;
      size = (uint)puVar11;
      if (puVar11 == puVar8) {
        for (; (puVar12 < crt_sbh_scan_ptr && (puVar12[2] == 0)); puVar12 = puVar12 + 5) {
        }
        size = (uint)puVar12;
        if ((puVar12 == crt_sbh_scan_ptr) && (size = (uint)FUN_004672d8(), (int *)size == (int *)0x0)) {
          return (void *)0x0;
        }
      }
      iVar7 = FUN_00467389(size);
      **(int **)(size + 0x10) = iVar7;
      if (**(int **)(size + 0x10) == -1) {
        return (void *)0x0;
      }
    }
  }
  piVar4 = *(int **)(size + 0x10);
  local_8 = *piVar4;
  if ((local_8 == -1) ||
     ((piVar4[local_8 + 0x31] & local_c) == 0 && (piVar4[local_8 + 0x11] & local_10) == 0)) {
    local_8 = 0;
    puVar8 = (uint *)(piVar4 + 0x11);
    if ((piVar4[0x31] & local_c) == 0 && (piVar4[0x11] & local_10) == 0) {
      do {
        puVar11 = puVar8 + 0x21;
        local_8 = local_8 + 1;
        puVar8 = puVar8 + 1;
      } while ((*puVar11 & local_c) == 0 && (local_10 & *puVar8) == 0);
    }
  }
  iVar7 = 0;
  piVar2 = piVar4 + local_8 * 0x81 + 0x51;
  local_10 = piVar4[local_8 + 0x11] & local_10;
  if (local_10 == 0) {
    local_10 = piVar4[local_8 + 0x31] & local_c;
    iVar7 = 0x20;
  }
  for (; -1 < (int)local_10; local_10 = local_10 << 1) {
    iVar7 = iVar7 + 1;
  }
  piVar10 = (int *)piVar2[iVar7 * 2 + 1];
  iVar9 = *piVar10 - uVar6;
  iVar14 = (iVar9 >> 4) + -1;
  if (0x3f < iVar14) {
    iVar14 = 0x3f;
  }
  crt_sbh_scan_ptr = (uint *)size;
  if (iVar14 != iVar7) {
    if (piVar10[1] == piVar10[2]) {
      if (iVar7 < 0x20) {
        pcVar1 = (char *)((int)piVar4 + iVar7 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar7 & 0x1f));
        piVar4[local_8 + 0x11] = uVar13 & piVar4[local_8 + 0x11];
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *(uint *)size = *(uint *)size & uVar13;
        }
      }
      else {
        pcVar1 = (char *)((int)piVar4 + iVar7 + 4);
        uVar13 = ~(0x80000000U >> ((byte)iVar7 - 0x20 & 0x1f));
        piVar4[local_8 + 0x31] = piVar4[local_8 + 0x31] & uVar13;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *(uint *)(size + 4) = *(uint *)(size + 4) & uVar13;
        }
      }
    }
    *(int *)(piVar10[2] + 4) = piVar10[1];
    *(int *)(piVar10[1] + 8) = piVar10[2];
    if (iVar9 == 0) goto LAB_00467295;
    piVar10[1] = piVar2[iVar14 * 2 + 1];
    piVar10[2] = (int)(piVar2 + iVar14 * 2);
    (piVar2 + iVar14 * 2)[1] = (int)piVar10;
    *(int **)(piVar10[1] + 8) = piVar10;
    if (piVar10[1] == piVar10[2]) {
      cVar3 = *(char *)(iVar14 + 4 + (int)piVar4);
      bVar5 = (byte)iVar14;
      if (iVar14 < 0x20) {
        *(char *)(iVar14 + 4 + (int)piVar4) = cVar3 + '\x01';
        if (cVar3 == '\0') {
          *(uint *)size = *(uint *)size | 0x80000000U >> (bVar5 & 0x1f);
        }
        piVar4[local_8 + 0x11] = piVar4[local_8 + 0x11] | 0x80000000U >> (bVar5 & 0x1f);
      }
      else {
        *(char *)(iVar14 + 4 + (int)piVar4) = cVar3 + '\x01';
        if (cVar3 == '\0') {
          *(uint *)(size + 4) = *(uint *)(size + 4) | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
        }
        piVar4[local_8 + 0x31] = piVar4[local_8 + 0x31] | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
      }
    }
  }
  if (iVar9 != 0) {
    *piVar10 = iVar9;
    *(int *)(iVar9 + -4 + (int)piVar10) = iVar9;
  }
LAB_00467295:
  piVar10 = (int *)((int)piVar10 + iVar9);
  *piVar10 = uVar6 + 1;
  *(uint *)((int)piVar10 + (uVar6 - 4)) = uVar6 + 1;
  iVar7 = *piVar2;
  *piVar2 = iVar7 + 1;
  if (((iVar7 == 0) && (size == crt_sbh_page_ptr)) && (local_8 == crt_sbh_page_index)) {
    crt_sbh_page_ptr = 0;
  }
  *piVar4 = local_8;
  return piVar10 + 1;
}



/* FUN_004672d8 @ 004672d8 */

/* [binja] int32_t* sub_4672d8() */

int * FUN_004672d8(void)

{
  int *piVar1;
  LPVOID pvVar2;
  
  if (crt_sbh_entry_count == crt_sbh_capacity) {
    pvVar2 = HeapReAlloc(crt_heap_handle,0,crt_sbh_header_base,(crt_sbh_capacity * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (int *)0x0;
    }
    crt_sbh_capacity = crt_sbh_capacity + 0x10;
    crt_sbh_header_base = pvVar2;
  }
  piVar1 = (int *)((int)crt_sbh_header_base + crt_sbh_entry_count * 0x14);
  pvVar2 = HeapAlloc(crt_heap_handle,8,0x41c4);
  piVar1[4] = (int)pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    piVar1[3] = (int)pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      piVar1[2] = -1;
      *piVar1 = 0;
      piVar1[1] = 0;
      crt_sbh_entry_count = crt_sbh_entry_count + 1;
      *(undefined4 *)piVar1[4] = 0xffffffff;
      return piVar1;
    }
    HeapFree(crt_heap_handle,0,(LPVOID)piVar1[4]);
  }
  return (int *)0x0;
}



/* FUN_00467389 @ 00467389 */

int __cdecl FUN_00467389(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  LPVOID pvVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *lpAddress;
  
  iVar3 = *(int *)(param_1 + 0x10);
  iVar9 = 0;
  for (iVar4 = *(int *)(param_1 + 8); -1 < iVar4; iVar4 = iVar4 << 1) {
    iVar9 = iVar9 + 1;
  }
  iVar8 = 0x3f;
  iVar4 = iVar9 * 0x204 + 0x144 + iVar3;
  iVar5 = iVar4;
  do {
    *(int *)(iVar5 + 8) = iVar5;
    *(int *)(iVar5 + 4) = iVar5;
    iVar5 = iVar5 + 8;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  lpAddress = (int *)(iVar9 * 0x8000 + *(int *)(param_1 + 0xc));
  pvVar6 = VirtualAlloc(lpAddress,0x8000,0x1000,4);
  if (pvVar6 == (LPVOID)0x0) {
    iVar9 = -1;
  }
  else {
    if (lpAddress <= lpAddress + 0x1c00) {
      piVar7 = lpAddress + 4;
      do {
        piVar7[-2] = -1;
        piVar7[0x3fb] = -1;
        piVar7[-1] = 0xff0;
        *piVar7 = (int)(piVar7 + 0x3ff);
        piVar7[1] = (int)(piVar7 + -0x401);
        piVar7[0x3fa] = 0xff0;
        piVar1 = piVar7 + 0x3fc;
        piVar7 = piVar7 + 0x400;
      } while (piVar1 <= lpAddress + 0x1c00);
    }
    *(int **)(iVar4 + 0x1fc) = lpAddress + 3;
    lpAddress[5] = iVar4 + 0x1f8;
    *(int **)(iVar4 + 0x200) = lpAddress + 0x1c03;
    lpAddress[0x1c04] = iVar4 + 0x1f8;
    *(undefined4 *)(iVar3 + 0x44 + iVar9 * 4) = 0;
    *(undefined4 *)(iVar3 + 0xc4 + iVar9 * 4) = 1;
    cVar2 = *(char *)(iVar3 + 0x43);
    *(char *)(iVar3 + 0x43) = cVar2 + '\x01';
    if (cVar2 == '\0') {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(0x80000000U >> ((byte)iVar9 & 0x1f));
  }
  return iVar9;
}



/* FUN_00467484 @ 00467484 */

/* [binja] int32_t sub_467484(int32_t* arg1, void** arg2, void* arg3) */

int __cdecl FUN_00467484(int *arg1,void **arg2,void *arg3)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  void *pvVar8;
  uint *puVar9;
  byte bVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint local_c;
  
  iVar7 = arg1[4];
  uVar14 = (int)arg3 + 0x17U & 0xfffffff0;
  uVar12 = (uint)((int)arg2 - arg1[3]) >> 0xf;
  iVar5 = uVar12 * 0x204 + 0x144 + iVar7;
  pvVar8 = arg2[-1];
  iVar11 = (int)pvVar8 + -1;
  uVar15 = *(uint *)((int)pvVar8 + -5 + (int)arg2);
  if (iVar11 < (int)uVar14) {
    if (((uVar15 & 1) != 0) || ((int)(uVar15 + iVar11) < (int)uVar14)) {
      return 0;
    }
    local_c = ((int)uVar15 >> 4) - 1;
    if (0x3f < local_c) {
      local_c = 0x3f;
    }
    if (*(int *)((int)arg2 + (int)pvVar8 + -1) == *(int *)((int)arg2 + (int)pvVar8 + 3)) {
      if (local_c < 0x20) {
        pcVar1 = (char *)(local_c + 4 + iVar7);
        uVar13 = ~(0x80000000U >> ((byte)local_c & 0x1f));
        puVar9 = (uint *)(iVar7 + 0x44 + uVar12 * 4);
        *puVar9 = *puVar9 & uVar13;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          *arg1 = *arg1 & uVar13;
        }
      }
      else {
        pcVar1 = (char *)(local_c + 4 + iVar7);
        uVar13 = ~(0x80000000U >> ((byte)local_c - 0x20 & 0x1f));
        puVar9 = (uint *)(iVar7 + 0xc4 + uVar12 * 4);
        *puVar9 = *puVar9 & uVar13;
        *pcVar1 = *pcVar1 + -1;
        if (*pcVar1 == '\0') {
          arg1[1] = arg1[1] & uVar13;
        }
      }
    }
    *(undefined4 *)(*(int *)((int)arg2 + (int)pvVar8 + 3) + 4) =
         *(undefined4 *)((int)arg2 + (int)pvVar8 + -1);
    *(undefined4 *)(*(int *)((int)arg2 + (int)pvVar8 + -1) + 8) =
         *(undefined4 *)((int)arg2 + (int)pvVar8 + 3);
    iVar11 = uVar15 + (iVar11 - uVar14);
    if (0 < iVar11) {
      uVar15 = (iVar11 >> 4) - 1;
      iVar2 = (int)arg2 + (uVar14 - 4);
      if (0x3f < uVar15) {
        uVar15 = 0x3f;
      }
      iVar5 = iVar5 + uVar15 * 8;
      *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(iVar5 + 4);
      *(int *)(iVar2 + 8) = iVar5;
      *(int *)(iVar5 + 4) = iVar2;
      *(int *)(*(int *)(iVar2 + 4) + 8) = iVar2;
      if (*(int *)(iVar2 + 4) == *(int *)(iVar2 + 8)) {
        cVar6 = *(char *)(uVar15 + 4 + iVar7);
        *(char *)(uVar15 + 4 + iVar7) = cVar6 + '\x01';
        bVar10 = (byte)uVar15;
        if (uVar15 < 0x20) {
          if (cVar6 == '\0') {
            *arg1 = *arg1 | 0x80000000U >> (bVar10 & 0x1f);
          }
          puVar9 = (uint *)(iVar7 + 0x44 + uVar12 * 4);
        }
        else {
          if (cVar6 == '\0') {
            arg1[1] = arg1[1] | 0x80000000U >> (bVar10 - 0x20 & 0x1f);
          }
          puVar9 = (uint *)(iVar7 + 0xc4 + uVar12 * 4);
          bVar10 = bVar10 - 0x20;
        }
        *puVar9 = *puVar9 | 0x80000000U >> (bVar10 & 0x1f);
      }
      piVar3 = (int *)((int)arg2 + (uVar14 - 4));
      *piVar3 = iVar11;
      *(int *)(iVar11 + -4 + (int)piVar3) = iVar11;
    }
    arg2[-1] = (void *)(uVar14 + 1);
    *(void **)((int)arg2 + (uVar14 - 8)) = (void *)(uVar14 + 1);
  }
  else if ((int)uVar14 < iVar11) {
    arg3 = (void *)(iVar11 - uVar14);
    arg2[-1] = (void *)(uVar14 + 1);
    puVar4 = (undefined4 *)((int)arg2 + (uVar14 - 4));
    uVar13 = ((int)arg3 >> 4) - 1;
    puVar4[-1] = (void *)(uVar14 + 1);
    if (0x3f < uVar13) {
      uVar13 = 0x3f;
    }
    if ((uVar15 & 1) == 0) {
      uVar14 = ((int)uVar15 >> 4) - 1;
      if (0x3f < uVar14) {
        uVar14 = 0x3f;
      }
      if (*(int *)((int)arg2 + (int)pvVar8 + -1) == *(int *)((int)arg2 + (int)pvVar8 + 3)) {
        if (uVar14 < 0x20) {
          pcVar1 = (char *)(uVar14 + 4 + iVar7);
          uVar14 = ~(0x80000000U >> ((byte)uVar14 & 0x1f));
          puVar9 = (uint *)(iVar7 + 0x44 + uVar12 * 4);
          *puVar9 = *puVar9 & uVar14;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            *arg1 = *arg1 & uVar14;
          }
        }
        else {
          pcVar1 = (char *)(uVar14 + 4 + iVar7);
          uVar14 = ~(0x80000000U >> ((byte)uVar14 - 0x20 & 0x1f));
          puVar9 = (uint *)(iVar7 + 0xc4 + uVar12 * 4);
          *puVar9 = *puVar9 & uVar14;
          *pcVar1 = *pcVar1 + -1;
          if (*pcVar1 == '\0') {
            arg1[1] = arg1[1] & uVar14;
          }
        }
      }
      *(undefined4 *)(*(int *)((int)arg2 + (int)pvVar8 + 3) + 4) =
           *(undefined4 *)((int)arg2 + (int)pvVar8 + -1);
      *(undefined4 *)(*(int *)((int)arg2 + (int)pvVar8 + -1) + 8) =
           *(undefined4 *)((int)arg2 + (int)pvVar8 + 3);
      arg3 = (void *)((int)arg3 + uVar15);
      uVar13 = ((int)arg3 >> 4) - 1;
      if (0x3f < uVar13) {
        uVar13 = 0x3f;
      }
    }
    iVar11 = iVar5 + uVar13 * 8;
    puVar4[1] = *(undefined4 *)(iVar5 + 4 + uVar13 * 8);
    puVar4[2] = iVar11;
    *(undefined4 **)(iVar11 + 4) = puVar4;
    *(undefined4 **)(puVar4[1] + 8) = puVar4;
    if (puVar4[1] == puVar4[2]) {
      cVar6 = *(char *)(uVar13 + 4 + iVar7);
      *(char *)(uVar13 + 4 + iVar7) = cVar6 + '\x01';
      bVar10 = (byte)uVar13;
      if (uVar13 < 0x20) {
        if (cVar6 == '\0') {
          *arg1 = *arg1 | 0x80000000U >> (bVar10 & 0x1f);
        }
        puVar9 = (uint *)(iVar7 + 0x44 + uVar12 * 4);
      }
      else {
        if (cVar6 == '\0') {
          arg1[1] = arg1[1] | 0x80000000U >> (bVar10 - 0x20 & 0x1f);
        }
        puVar9 = (uint *)(iVar7 + 0xc4 + uVar12 * 4);
        bVar10 = bVar10 - 0x20;
      }
      *puVar9 = *puVar9 | 0x80000000U >> (bVar10 & 0x1f);
    }
    *puVar4 = arg3;
    *(void **)((int)arg3 + -4 + (int)puVar4) = arg3;
  }
  return 1;
}



/* crt_sbh_create_region @ 0046777a */

/* CRT small-block heap region init */

undefined ** crt_sbh_create_region(void)

{
  bool bVar1;
  int *lpAddress;
  LPVOID pvVar2;
  undefined **ppuVar3;
  int iVar4;
  undefined **lpMem;
  
  if (crt_sbh_initialized == -1) {
    lpMem = &PTR_LOOP_0047baf0;
  }
  else {
    lpMem = HeapAlloc(crt_heap_handle,0,0x2020);
    if (lpMem == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  lpAddress = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (lpAddress != (int *)0x0) {
    pvVar2 = VirtualAlloc(lpAddress,0x10000,0x1000,4);
    if (pvVar2 != (LPVOID)0x0) {
      if (lpMem == &PTR_LOOP_0047baf0) {
        if (PTR_LOOP_0047baf0 == (undefined *)0x0) {
          PTR_LOOP_0047baf0 = (undefined *)&PTR_LOOP_0047baf0;
        }
        if (PTR_LOOP_0047baf4 == (undefined *)0x0) {
          PTR_LOOP_0047baf4 = (undefined *)&PTR_LOOP_0047baf0;
        }
      }
      else {
        *lpMem = (undefined *)&PTR_LOOP_0047baf0;
        lpMem[1] = PTR_LOOP_0047baf4;
        PTR_LOOP_0047baf4 = (undefined *)lpMem;
        *(undefined ***)lpMem[1] = lpMem;
      }
      lpMem[5] = (undefined *)(lpAddress + 0x100000);
      ppuVar3 = lpMem + 6;
      lpMem[3] = (undefined *)(lpMem + 0x26);
      lpMem[4] = (undefined *)lpAddress;
      lpMem[2] = (undefined *)ppuVar3;
      iVar4 = 0;
      do {
        bVar1 = 0xf < iVar4;
        iVar4 = iVar4 + 1;
        *ppuVar3 = (undefined *)((bVar1 - 1 & 0xf1) - 1);
        ppuVar3[1] = (undefined *)0xf1;
        ppuVar3 = ppuVar3 + 2;
      } while (iVar4 < 0x400);
      _memset(lpAddress,0,0x10000);
      for (; lpAddress < lpMem[4] + 0x10000; lpAddress = lpAddress + 0x400) {
        *(undefined1 *)(lpAddress + 0x3e) = 0xff;
        *lpAddress = (int)(lpAddress + 2);
        lpAddress[1] = 0xf0;
      }
      return lpMem;
    }
    VirtualFree(lpAddress,0,0x8000);
  }
  if (lpMem != &PTR_LOOP_0047baf0) {
    HeapFree(crt_heap_handle,0,lpMem);
  }
  return (undefined **)0x0;
}



/* FUN_004678be @ 004678be */

/* [binja] BOOL sub_4678be(int32_t* arg1) */

BOOL __cdecl FUN_004678be(int *arg1)

{
  undefined *puVar1;
  WINBOOL WVar2;
  
  puVar1 = (undefined *)VirtualFree((LPVOID)arg1[4],0,0x8000);
  if ((int *)PTR_LOOP_0047db10 == arg1) {
    puVar1 = (undefined *)arg1[1];
    PTR_LOOP_0047db10 = puVar1;
  }
  if ((undefined **)arg1 != &PTR_LOOP_0047baf0) {
    *(int *)arg1[1] = *arg1;
    *(int *)(*arg1 + 4) = arg1[1];
    WVar2 = HeapFree(crt_heap_handle,0,arg1);
    return WVar2;
  }
  crt_sbh_initialized = 0xffffffff;
  return (BOOL)puVar1;
}



/* FUN_00467914 @ 00467914 */

void __cdecl FUN_00467914(int param_1)

{
  WINBOOL WVar1;
  int *piVar2;
  int iVar3;
  int *arg1;
  int *piVar4;
  int local_8;
  
  arg1 = (int *)PTR_LOOP_0047baf4;
  do {
    piVar4 = arg1;
    if (arg1[4] != -1) {
      local_8 = 0;
      piVar4 = arg1 + 0x804;
      iVar3 = 0x3ff000;
      do {
        if (*piVar4 == 0xf0) {
          WVar1 = VirtualFree((LPVOID)(iVar3 + arg1[4]),0x1000,0x4000);
          if (WVar1 != 0) {
            *piVar4 = -1;
            crt_sbh_commit_count = crt_sbh_commit_count + -1;
            if (((int *)arg1[3] == (int *)0x0) || (piVar4 < (int *)arg1[3])) {
              arg1[3] = (int)piVar4;
            }
            local_8 = local_8 + 1;
            param_1 = param_1 + -1;
            if (param_1 == 0) break;
          }
        }
        iVar3 = iVar3 + -0x1000;
        piVar4 = piVar4 + -2;
      } while (-1 < iVar3);
      piVar4 = (int *)arg1[1];
      if ((local_8 != 0) && (arg1[6] == -1)) {
        piVar2 = arg1 + 8;
        iVar3 = 1;
        do {
          if (*piVar2 != -1) break;
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 2;
        } while (iVar3 < 0x400);
        if (iVar3 == 0x400) {
          FUN_004678be(arg1);
        }
      }
    }
    if ((piVar4 == (int *)PTR_LOOP_0047baf4) || (arg1 = piVar4, param_1 < 1)) {
      return;
    }
  } while( true );
}



/* crt_sbh_find_block @ 004679d6 */

/* CRT: map a pointer to its small-block heap block header */

void * __cdecl crt_sbh_find_block(void *ptr,void **region_out,uint *page_base)

{
  undefined **ppuVar1;
  uint uVar2;
  
  ppuVar1 = &PTR_LOOP_0047baf0;
  while ((ptr <= ppuVar1[4] || (ppuVar1[5] <= ptr))) {
    ppuVar1 = (undefined **)*ppuVar1;
    if (ppuVar1 == &PTR_LOOP_0047baf0) {
      return (void *)0x0;
    }
  }
  if (((uint)ptr & 0xf) != 0) {
    return (void *)0x0;
  }
  if (((uint)ptr & 0xfff) < 0x100) {
    return (void *)0x0;
  }
  *region_out = ppuVar1;
  uVar2 = (uint)ptr & 0xfffff000;
  *page_base = uVar2;
  return (void *)(((int)((int)ptr + (-0x100 - uVar2)) >> 4) + 8 + uVar2);
}



/* crt_sbh_decommit_pages @ 00467a2d */

/* [binja] void* sub_467a2d(void* arg1, int32_t arg2, char* arg3) */

void * __cdecl crt_sbh_decommit_pages(void *arg1,int arg2,char *arg3)

{
  int *piVar1;
  
  piVar1 = (int *)((int)arg1 + (arg2 - *(int *)((int)arg1 + 0x10) >> 0xc) * 8 + 0x18);
  *piVar1 = *piVar1 + (uint)(byte)*arg3;
  *arg3 = '\0';
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (crt_sbh_commit_count = crt_sbh_commit_count + 1, crt_sbh_commit_count == 0x20)) {
    piVar1 = (int *)FUN_00467914(0x10);
  }
  return piVar1;
}



/* crt_sbh_alloc_units @ 00467a72 */

/* WARNING: Type propagation algorithm not settling */
/* allocates small-block heap blocks in 16-byte units */

void * __cdecl crt_sbh_alloc_units(uint blocks)

{
  uint *puVar1;
  undefined **ppuVar2;
  undefined *puVar3;
  int *piVar4;
  void *pvVar5;
  undefined **ppuVar6;
  int *piVar7;
  uint *puVar8;
  undefined **ppuVar9;
  int local_8;
  
  piVar7 = (int *)PTR_LOOP_0047db10;
  do {
    if (piVar7[4] != -1) {
      puVar8 = (uint *)piVar7[2];
      piVar4 = (int *)(((int)puVar8 + (-0x18 - (int)piVar7) >> 3) * 0x1000 + piVar7[4]);
      if (puVar8 < piVar7 + 0x806) {
        do {
          if (((int)blocks <= (int)*puVar8) && (blocks < puVar8[1])) {
            pvVar5 = (void *)crt_sbh_resize_block(piVar4,*puVar8,blocks);
            if (pvVar5 != (void *)0x0) goto LAB_00467b3d;
            puVar8[1] = blocks;
          }
          puVar8 = puVar8 + 2;
          piVar4 = piVar4 + 0x400;
        } while (puVar8 < piVar7 + 0x806);
      }
      puVar1 = (uint *)piVar7[2];
      piVar4 = (int *)piVar7[4];
      for (puVar8 = (uint *)(piVar7 + 6); puVar8 < puVar1; puVar8 = puVar8 + 2) {
        if (((int)blocks <= (int)*puVar8) && (blocks < puVar8[1])) {
          pvVar5 = (void *)crt_sbh_resize_block(piVar4,*puVar8,blocks);
          if (pvVar5 != (void *)0x0) {
LAB_00467b3d:
            PTR_LOOP_0047db10 = (undefined *)piVar7;
            *puVar8 = *puVar8 - blocks;
            piVar7[2] = (int)puVar8;
            return pvVar5;
          }
          puVar8[1] = blocks;
        }
        piVar4 = piVar4 + 0x400;
      }
    }
    piVar7 = (int *)*piVar7;
    if (piVar7 == (int *)PTR_LOOP_0047db10) {
      ppuVar9 = &PTR_LOOP_0047baf0;
      while ((ppuVar9[4] == (undefined *)0xffffffff || (ppuVar9[3] == (undefined *)0x0))) {
        ppuVar9 = (undefined **)*ppuVar9;
        if (ppuVar9 == &PTR_LOOP_0047baf0) {
          ppuVar9 = crt_sbh_create_region();
          if (ppuVar9 == (undefined **)0x0) {
            return (void *)0x0;
          }
          piVar7 = (int *)ppuVar9[4];
          *(char *)(piVar7 + 2) = (char)blocks;
          PTR_LOOP_0047db10 = (undefined *)ppuVar9;
          *piVar7 = (int)piVar7 + blocks + 8;
          piVar7[1] = 0xf0 - blocks;
          ppuVar9[6] = ppuVar9[6] + -(blocks & 0xff);
          return piVar7 + 0x40;
        }
      }
      ppuVar2 = (undefined **)ppuVar9[3];
      local_8 = 0;
      piVar7 = (int *)(ppuVar9[4] + ((int)ppuVar2 + (-0x18 - (int)ppuVar9) >> 3) * 0x1000);
      puVar3 = *ppuVar2;
      ppuVar6 = ppuVar2;
      for (; (puVar3 == (undefined *)0xffffffff && (local_8 < 0x10)); local_8 = local_8 + 1) {
        ppuVar6 = ppuVar6 + 2;
        puVar3 = *ppuVar6;
      }
      piVar4 = VirtualAlloc(piVar7,local_8 << 0xc,0x1000,4);
      if (piVar4 != piVar7) {
        return (void *)0x0;
      }
      _memset(piVar7,local_8 << 0xc,0);
      ppuVar6 = ppuVar2;
      if (0 < local_8) {
        piVar4 = piVar7 + 1;
        do {
          *(undefined1 *)(piVar4 + 0x3d) = 0xff;
          piVar4[-1] = (int)(piVar4 + 1);
          *piVar4 = 0xf0;
          *ppuVar6 = (undefined *)0xf0;
          ppuVar6[1] = (undefined *)0xf1;
          piVar4 = piVar4 + 0x400;
          ppuVar6 = ppuVar6 + 2;
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
      for (; (ppuVar6 < ppuVar9 + 0x806 && (*ppuVar6 != (undefined *)0xffffffff));
          ppuVar6 = ppuVar6 + 2) {
      }
      PTR_LOOP_0047db10 = (undefined *)ppuVar9;
      ppuVar9[3] = (undefined *)(-(uint)(ppuVar6 < ppuVar9 + 0x806) & (uint)ppuVar6);
      *(char *)(piVar7 + 2) = (char)blocks;
      ppuVar9[2] = (undefined *)ppuVar2;
      *ppuVar2 = *ppuVar2 + -blocks;
      piVar7[1] = piVar7[1] - blocks;
      *piVar7 = (int)piVar7 + blocks + 8;
      return piVar7 + 0x40;
    }
  } while( true );
}



/* crt_sbh_resize_block @ 00467c7a */

int __cdecl crt_sbh_resize_block(int *param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  byte *pbVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = (byte *)*param_1;
  pbVar1 = (byte *)(param_1 + 0x3e);
  bVar3 = (byte)param_3;
  if ((uint)param_1[1] < param_3) {
    pbVar6 = pbVar2;
    if (pbVar2[param_1[1]] != 0) {
      pbVar6 = pbVar2 + param_1[1];
    }
    while( true ) {
      while( true ) {
        if (pbVar1 <= pbVar6 + param_3) {
          pbVar6 = (byte *)(param_1 + 2);
          while( true ) {
            while( true ) {
              if (pbVar2 <= pbVar6) {
                return 0;
              }
              if (pbVar1 <= pbVar6 + param_3) {
                return 0;
              }
              if (*pbVar6 == 0) break;
              pbVar6 = pbVar6 + *pbVar6;
            }
            uVar5 = 1;
            pbVar4 = pbVar6;
            while (pbVar4 = pbVar4 + 1, *pbVar4 == 0) {
              uVar5 = uVar5 + 1;
            }
            if (param_3 <= uVar5) break;
            param_2 = param_2 - uVar5;
            pbVar6 = pbVar4;
            if (param_2 < param_3) {
              return 0;
            }
          }
          if (pbVar6 + param_3 < pbVar1) {
            *param_1 = (int)(pbVar6 + param_3);
            param_1[1] = uVar5 - param_3;
          }
          else {
            param_1[1] = 0;
            *param_1 = (int)(param_1 + 2);
          }
          *pbVar6 = bVar3;
          pbVar2 = pbVar6 + 8;
          goto LAB_00467d8d;
        }
        if (*pbVar6 == 0) break;
        pbVar6 = pbVar6 + *pbVar6;
      }
      uVar5 = 1;
      pbVar4 = pbVar6;
      while (pbVar4 = pbVar4 + 1, *pbVar4 == 0) {
        uVar5 = uVar5 + 1;
      }
      if (param_3 <= uVar5) break;
      if (pbVar6 == pbVar2) {
        param_1[1] = uVar5;
        pbVar6 = pbVar4;
      }
      else {
        param_2 = param_2 - uVar5;
        pbVar6 = pbVar4;
        if (param_2 < param_3) {
          return 0;
        }
      }
    }
    if (pbVar6 + param_3 < pbVar1) {
      *param_1 = (int)(pbVar6 + param_3);
      param_1[1] = uVar5 - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    *pbVar6 = bVar3;
    pbVar2 = pbVar6 + 8;
  }
  else {
    *pbVar2 = bVar3;
    if (pbVar2 + param_3 < pbVar1) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    pbVar2 = pbVar2 + 8;
  }
LAB_00467d8d:
  return (int)pbVar2 * 0x10 + (int)param_1 * -0xf;
}



/* FUN_00467d9e @ 00467d9e */

/* [binja] int32_t sub_467d9e(void* arg1, void** arg2, char* arg3, int32_t arg4) */

int __cdecl FUN_00467d9e(void *arg1,void **arg2,char *arg3,int arg4)

{
  void **ppvVar1;
  int *piVar2;
  char cVar3;
  void **ppvVar4;
  void *pvVar5;
  uint uVar6;
  
  uVar6 = (uint)(byte)*arg3;
  piVar2 = (int *)((int)arg1 + ((int)arg2 - *(int *)((int)arg1 + 0x10) >> 0xc) * 8 + 0x18);
  if ((uint)arg4 < uVar6) {
    *arg3 = (char)arg4;
    *piVar2 = *piVar2 + (uVar6 - arg4);
    piVar2[1] = 0xf1;
  }
  else {
    if ((uint)arg4 <= uVar6) {
      return 0;
    }
    ppvVar1 = (void **)(arg3 + arg4);
    if (arg2 + 0x3e < ppvVar1) {
      return 0;
    }
    for (ppvVar4 = (void **)(arg3 + uVar6); (ppvVar4 < ppvVar1 && (*(char *)ppvVar4 == '\0'));
        ppvVar4 = (void **)((int)ppvVar4 + 1)) {
    }
    if (ppvVar4 != ppvVar1) {
      return 0;
    }
    *arg3 = (char)arg4;
    if ((arg3 <= *arg2) && (*arg2 < ppvVar1)) {
      if (ppvVar1 < arg2 + 0x3e) {
        pvVar5 = (void *)0x0;
        *arg2 = ppvVar1;
        cVar3 = *(char *)ppvVar1;
        while (cVar3 == '\0') {
          pvVar5 = (void *)((int)pvVar5 + 1);
          cVar3 = *(char *)((int)ppvVar1 + (int)pvVar5);
        }
        arg2[1] = pvVar5;
      }
      else {
        arg2[1] = (void *)0x0;
        *arg2 = arg2 + 2;
      }
    }
    *piVar2 = *piVar2 + (uVar6 - arg4);
  }
  return 1;
}



/* crt_call_new_handler @ 00467e47 */

/* CRT: call new-handler; returns nonzero to retry allocation */

int __cdecl crt_call_new_handler(size_t size)

{
  int iVar1;
  
  if (crt_new_handler_alt != (code *)0x0) {
    iVar1 = (*crt_new_handler_alt)(size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}



/* FUN_00467e62 @ 00467e62 */

int __thiscall FUN_00467e62(void *this,int *param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  undefined4 *puVar2;
  int *piVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  void *this_00;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  void *this_01;
  int *extraout_ECX_02;
  int *extraout_ECX_03;
  int *piVar7;
  byte bVar8;
  byte *pbVar9;
  byte *pbVar10;
  char *pcVar11;
  char *pcVar12;
  WCHAR *pWVar13;
  undefined *puVar14;
  int iVar15;
  bool bVar16;
  int *piVar17;
  char local_1c8;
  char local_1c7 [351];
  byte local_68 [32];
  undefined4 *local_48;
  WCHAR local_42;
  uint local_40;
  byte local_3c;
  undefined1 local_3b;
  byte local_39;
  int local_38;
  WCHAR *local_34;
  WCHAR *local_30;
  undefined8 local_2c;
  int local_24;
  int local_20;
  byte local_1c;
  char local_1b;
  char local_1a;
  char local_19;
  int *local_18;
  char local_13;
  char local_12;
  char local_11;
  int local_10;
  char local_9;
  undefined *local_8;
  
  local_19 = '\0';
  bVar1 = *param_2;
  local_8 = (undefined *)0x0;
  local_38 = 0;
  pbVar9 = param_2;
  piVar7 = (int *)crt_ctype_table;
  do {
    crt_ctype_table = (undefined *)piVar7;
    if (bVar1 == 0) {
LAB_00468868:
      if (local_18 == (int *)0xffffffff) {
LAB_0046886e:
        if ((local_38 == 0) && (local_19 == '\0')) {
          local_38 = -1;
        }
      }
      return local_38;
    }
    if ((int)crt_locale_type < 2) {
      uVar5 = *(byte *)((int)piVar7 + (uint)bVar1 * 2) & 8;
    }
    else {
      piVar7 = (int *)0x8;
      uVar5 = crt_isctype(this,(uint)bVar1,8);
    }
    if (uVar5 != 0) {
      local_8 = local_8 + -1;
      piVar7 = param_1;
      uVar5 = crt_stream_skip_whitespace((int *)&local_8,param_1);
      crt_stream_ungetc_safe(uVar5,piVar7);
      uVar5 = crt_isspace(this_00,(uint)pbVar9[1]);
      piVar7 = extraout_ECX;
      pbVar10 = pbVar9;
      while (pbVar9 = pbVar10 + 1, uVar5 != 0) {
        piVar17 = (int *)(uint)pbVar10[2];
        uVar5 = crt_isspace(piVar7,(int)(uint)pbVar10[2]);
        piVar7 = piVar17;
        pbVar10 = pbVar9;
      }
    }
    if (*pbVar9 == 0x25) {
      local_39 = 0;
      local_1c = 0;
      local_1b = '\0';
      local_12 = '\0';
      local_13 = '\0';
      local_1a = '\0';
      puVar14 = (undefined *)0x0;
      local_9 = '\0';
      local_20 = 0;
      local_24 = 0;
      local_10 = 0;
      local_11 = '\x01';
      local_34 = (WCHAR *)0x0;
      do {
        uVar5 = (uint)pbVar9[1];
        param_2 = pbVar9 + 1;
        if ((int)crt_locale_type < 2) {
          uVar6 = (byte)crt_ctype_table[uVar5 * 2] & 4;
          piVar7 = (int *)crt_ctype_table;
        }
        else {
          piVar17 = (int *)0x4;
          uVar6 = crt_isctype(piVar7,uVar5,4);
          piVar7 = piVar17;
        }
        if (uVar6 == 0) {
          if (uVar5 < 0x4f) {
            if (uVar5 != 0x4e) {
              if (uVar5 == 0x2a) {
                local_12 = local_12 + '\x01';
              }
              else if (uVar5 != 0x46) {
                if (uVar5 == 0x49) {
                  if ((pbVar9[2] != 0x36) || (pbVar9[3] != 0x34)) goto LAB_00467fbd;
                  local_34 = (WCHAR *)((int)local_34 + 1);
                  local_2c = 0;
                  param_2 = pbVar9 + 3;
                }
                else if (uVar5 == 0x4c) {
                  local_11 = local_11 + '\x01';
                }
                else {
LAB_00467fbd:
                  local_13 = local_13 + '\x01';
                }
              }
            }
          }
          else if (uVar5 == 0x68) {
            local_11 = local_11 + -1;
            local_9 = local_9 + -1;
          }
          else {
            if (uVar5 == 0x6c) {
              local_11 = local_11 + '\x01';
            }
            else if (uVar5 != 0x77) goto LAB_00467fbd;
            local_9 = local_9 + '\x01';
          }
        }
        else {
          local_24 = local_24 + 1;
          local_10 = (uVar5 - 0x30) + local_10 * 10;
        }
        pbVar9 = param_2;
      } while (local_13 == '\0');
      puVar2 = param_3;
      if (local_12 == '\0') {
        local_30 = (WCHAR *)*param_3;
        puVar2 = param_3 + 1;
        local_48 = param_3;
      }
      param_3 = puVar2;
      local_13 = '\0';
      if (local_9 == '\0') {
        if ((*param_2 == 0x53) || (*param_2 == 0x43)) {
          local_9 = '\x01';
        }
        else {
          local_9 = -1;
        }
      }
      uVar5 = *param_2 | 0x20;
      local_40 = uVar5;
      if (uVar5 != 0x6e) {
        if ((uVar5 == 99) || (uVar5 == 0x7b)) {
          local_8 = local_8 + 1;
          piVar7 = param_1;
          local_18 = (int *)crt_stream_getc(param_1);
        }
        else {
          piVar7 = param_1;
          local_18 = (int *)crt_stream_skip_whitespace((int *)&local_8,param_1);
        }
      }
      if ((local_24 != 0) && (local_10 == 0)) {
LAB_00468848:
        local_8 = local_8 + -1;
        crt_stream_ungetc_safe((uint)local_18,param_1);
        goto LAB_00468868;
      }
      if (uVar5 < 0x70) {
        if (uVar5 == 0x6f) {
LAB_00468575:
          if (local_18 == (int *)0x2d) {
            local_1b = '\x01';
          }
          else if (local_18 != (int *)0x2b) goto LAB_004685aa;
          local_10 = local_10 + -1;
          if ((local_10 == 0) && (local_24 != 0)) {
            local_13 = '\x01';
          }
          else {
            local_8 = local_8 + 1;
            piVar7 = param_1;
            local_18 = (int *)crt_stream_getc(param_1);
          }
          goto LAB_004685aa;
        }
        if (uVar5 != 99) {
          if (uVar5 == 100) goto LAB_00468575;
          if (uVar5 < 0x65) {
LAB_004682ed:
            if ((int *)(uint)*param_2 != local_18) goto LAB_00468848;
            local_19 = local_19 + -1;
            if (local_12 == '\0') {
              param_3 = local_48;
            }
            goto LAB_004687c9;
          }
          if (0x67 < uVar5) {
            if (uVar5 == 0x69) {
              uVar5 = 100;
              goto LAB_004680ab;
            }
            if (uVar5 != 0x6e) goto LAB_004682ed;
            puVar14 = local_8;
            if (local_12 != '\0') goto LAB_004687c9;
            goto LAB_004687a3;
          }
          pcVar11 = &local_1c8;
          if (local_18 == (int *)0x2d) {
            local_1c8 = '-';
            pcVar11 = local_1c7;
LAB_004680e1:
            local_10 = local_10 + -1;
            local_8 = local_8 + 1;
            piVar7 = param_1;
            local_18 = (int *)crt_stream_getc(param_1);
          }
          else if (local_18 == (int *)0x2b) goto LAB_004680e1;
          if ((local_24 == 0) || (0x15d < local_10)) {
            local_10 = 0x15d;
          }
          while( true ) {
            piVar17 = local_18;
            if ((int)crt_locale_type < 2) {
              uVar5 = (byte)crt_ctype_table[(int)local_18 * 2] & 4;
            }
            else {
              uVar5 = crt_isctype(piVar7,(int)local_18,4);
            }
            if ((uVar5 == 0) ||
               (iVar15 = local_10 + -1, bVar16 = local_10 == 0, local_10 = iVar15, bVar16)) break;
            local_20 = local_20 + 1;
            *pcVar11 = (char)piVar17;
            pcVar11 = pcVar11 + 1;
            local_8 = local_8 + 1;
            piVar7 = param_1;
            local_18 = (int *)crt_stream_getc(param_1);
          }
          if ((crt_null_char == (char)piVar17) &&
             (iVar15 = local_10 + -1, bVar16 = local_10 != 0, local_10 = iVar15, bVar16)) {
            local_8 = local_8 + 1;
            piVar7 = param_1;
            piVar17 = (int *)crt_stream_getc(param_1);
            *pcVar11 = crt_null_char;
            while( true ) {
              pcVar11 = pcVar11 + 1;
              local_18 = piVar17;
              if ((int)crt_locale_type < 2) {
                uVar5 = (byte)crt_ctype_table[(int)piVar17 * 2] & 4;
              }
              else {
                uVar5 = crt_isctype(piVar7,(int)piVar17,4);
              }
              if ((uVar5 == 0) ||
                 (iVar15 = local_10 + -1, bVar16 = local_10 == 0, local_10 = iVar15, bVar16)) break;
              local_20 = local_20 + 1;
              *pcVar11 = (char)piVar17;
              local_8 = local_8 + 1;
              piVar7 = param_1;
              piVar17 = (int *)crt_stream_getc(param_1);
            }
          }
          pcVar12 = pcVar11;
          if ((local_20 != 0) &&
             (((piVar17 == (int *)0x65 || (piVar17 == (int *)0x45)) &&
              (iVar15 = local_10 + -1, bVar16 = local_10 != 0, local_10 = iVar15, bVar16)))) {
            *pcVar11 = 'e';
            pcVar12 = pcVar11 + 1;
            local_8 = local_8 + 1;
            piVar7 = param_1;
            piVar17 = (int *)crt_stream_getc(param_1);
            local_18 = piVar17;
            if (piVar17 == (int *)0x2d) {
              *pcVar12 = '-';
              pcVar12 = pcVar11 + 2;
LAB_00468208:
              bVar16 = local_10 != 0;
              local_10 = local_10 + -1;
              if (bVar16) goto LAB_00468217;
              local_10 = 0;
            }
            else if (piVar17 == (int *)0x2b) goto LAB_00468208;
            while( true ) {
              if ((int)crt_locale_type < 2) {
                uVar5 = (byte)crt_ctype_table[(int)piVar17 * 2] & 4;
              }
              else {
                uVar5 = crt_isctype(piVar7,(int)piVar17,4);
              }
              if ((uVar5 == 0) ||
                 (iVar15 = local_10 + -1, bVar16 = local_10 == 0, local_10 = iVar15, bVar16)) break;
              local_20 = local_20 + 1;
              *pcVar12 = (char)piVar17;
              pcVar12 = pcVar12 + 1;
LAB_00468217:
              local_8 = local_8 + 1;
              piVar7 = param_1;
              piVar17 = (int *)crt_stream_getc(param_1);
              local_18 = piVar17;
            }
          }
          local_8 = local_8 + -1;
          piVar7 = param_1;
          crt_stream_ungetc_safe((uint)piVar17,param_1);
          if (local_20 != 0) {
            if (local_12 == '\0') {
              local_38 = local_38 + 1;
              *pcVar12 = '\0';
              (*(code *)PTR_FUN_0047b1b0)(local_11 + -1,local_30,&local_1c8);
              piVar7 = extraout_ECX_00;
            }
            goto LAB_004687c9;
          }
          goto LAB_00468868;
        }
        if (local_24 == 0) {
          local_10 = local_10 + 1;
          local_24 = 1;
        }
        if ('\0' < local_9) {
          local_1a = '\x01';
        }
        pcVar11 = &DAT_0047db20;
LAB_004683ce:
        local_1c = 0xff;
        pbVar9 = (byte *)pcVar11;
        pbVar10 = param_2;
LAB_004683d2:
        param_2 = pbVar10;
        _memset(local_68,0,0x20);
        if ((local_40 == 0x7b) && (*pbVar9 == 0x5d)) {
          uVar5 = 0x5d;
          local_68[0xb] = 0x20;
          pbVar9 = pbVar9 + 1;
        }
        else {
          uVar5 = (uint)local_39;
        }
        while (pWVar13 = local_30, bVar1 = *pbVar9, bVar1 != 0x5d) {
          if (((bVar1 == 0x2d) && (bVar8 = (byte)uVar5, bVar8 != 0)) &&
             (bVar4 = pbVar9[1], bVar4 != 0x5d)) {
            if (bVar4 <= bVar8) {
              uVar5 = (uint)bVar4;
              bVar4 = bVar8;
            }
            if ((byte)uVar5 <= bVar4) {
              iVar15 = (bVar4 - uVar5) + 1;
              do {
                local_68[uVar5 >> 3] = local_68[uVar5 >> 3] | '\x01' << ((byte)uVar5 & 7);
                uVar5 = uVar5 + 1;
                iVar15 = iVar15 + -1;
              } while (iVar15 != 0);
            }
            uVar5 = 0;
            pbVar9 = pbVar9 + 2;
          }
          else {
            uVar5 = (uint)bVar1;
            local_68[bVar1 >> 3] = local_68[bVar1 >> 3] | '\x01' << (bVar1 & 7);
            pbVar9 = pbVar9 + 1;
          }
        }
        if (*pbVar9 == 0) goto LAB_00468868;
        if (local_40 == 0x7b) {
          param_2 = pbVar9;
        }
        local_8 = local_8 + -1;
        local_34 = local_30;
        piVar7 = param_1;
        crt_stream_ungetc_safe((uint)local_18,param_1);
        while( true ) {
          if ((local_24 != 0) &&
             (iVar15 = local_10 + -1, bVar16 = local_10 == 0, local_10 = iVar15, bVar16))
          goto LAB_00468537;
          local_8 = local_8 + 1;
          local_18 = (int *)crt_stream_getc(param_1);
          if (local_18 == (int *)0xffffffff) break;
          bVar1 = (byte)local_18;
          piVar7 = (int *)(int)(char)(local_68[(int)local_18 >> 3] ^ local_1c);
          if (((uint)piVar7 & 1 << (bVar1 & 7)) == 0) break;
          if (local_12 == '\0') {
            if (local_1a == '\0') {
              *(byte *)pWVar13 = bVar1;
              pWVar13 = (WCHAR *)((int)pWVar13 + 1);
              local_30 = pWVar13;
            }
            else {
              local_3c = bVar1;
              if ((crt_ctype_table[((uint)local_18 & 0xff) * 2 + 1] & 0x80) != 0) {
                local_8 = local_8 + 1;
                uVar5 = crt_stream_getc(param_1);
                local_3b = (undefined1)uVar5;
              }
              crt_mbtowc_locking(&local_42,&local_3c,crt_locale_type);
              *pWVar13 = local_42;
              pWVar13 = pWVar13 + 1;
              piVar7 = extraout_ECX_01;
              local_30 = pWVar13;
            }
          }
          else {
            local_34 = (WCHAR *)((int)local_34 + 1);
          }
        }
        local_8 = local_8 + -1;
        piVar7 = param_1;
        crt_stream_ungetc_safe((uint)local_18,param_1);
LAB_00468537:
        if (local_34 == pWVar13) goto LAB_00468868;
        if ((local_12 == '\0') && (local_38 = local_38 + 1, local_40 != 99)) {
          if (local_1a == '\0') {
            *(byte *)local_30 = 0;
          }
          else {
            *local_30 = L'\0';
          }
        }
      }
      else {
        if (uVar5 == 0x70) {
          local_11 = '\x01';
          goto LAB_00468575;
        }
        if (uVar5 == 0x73) {
          if ('\0' < local_9) {
            local_1a = '\x01';
          }
          pcVar11 = s_____0047db18;
          goto LAB_004683ce;
        }
        if (uVar5 == 0x75) goto LAB_00468575;
        if (uVar5 != 0x78) {
          if (uVar5 != 0x7b) goto LAB_004682ed;
          if ('\0' < local_9) {
            local_1a = '\x01';
          }
          pbVar9 = param_2 + 1;
          pbVar10 = pbVar9;
          if (*pbVar9 == 0x5e) {
            pcVar11 = (char *)(param_2 + 2);
            param_2 = pbVar9;
            goto LAB_004683ce;
          }
          goto LAB_004683d2;
        }
LAB_004680ab:
        if (local_18 == (int *)0x2d) {
          local_1b = '\x01';
LAB_0046833a:
          local_10 = local_10 + -1;
          if ((local_10 == 0) && (local_24 != 0)) {
            local_13 = '\x01';
          }
          else {
            local_8 = local_8 + 1;
            piVar7 = param_1;
            local_18 = (int *)crt_stream_getc(param_1);
          }
        }
        else if (local_18 == (int *)0x2b) goto LAB_0046833a;
        if (local_18 == (int *)0x30) {
          local_8 = local_8 + 1;
          piVar7 = param_1;
          local_18 = (int *)crt_stream_getc(param_1);
          if (((char)local_18 == 'x') || ((char)local_18 == 'X')) {
            local_8 = local_8 + 1;
            piVar7 = param_1;
            local_18 = (int *)crt_stream_getc(param_1);
            uVar5 = 0x78;
          }
          else {
            local_20 = 1;
            if (uVar5 == 0x78) {
              local_8 = local_8 + -1;
              piVar7 = param_1;
              crt_stream_ungetc_safe((uint)local_18,param_1);
              local_18 = (int *)0x30;
            }
            else {
              uVar5 = 0x6f;
            }
          }
        }
LAB_004685aa:
        if (local_34 == (WCHAR *)0x0) {
          if (local_13 == '\0') {
            while ((piVar17 = local_18, uVar5 != 0x78 && (uVar5 != 0x70))) {
              if ((int)crt_locale_type < 2) {
                uVar6 = (byte)crt_ctype_table[(int)local_18 * 2] & 4;
              }
              else {
                piVar3 = (int *)0x4;
                uVar6 = crt_isctype(piVar7,(int)local_18,4);
                piVar7 = piVar3;
              }
              if (uVar6 == 0) goto LAB_00468771;
              if (uVar5 == 0x6f) {
                if (0x37 < (int)piVar17) goto LAB_00468771;
                iVar15 = (int)puVar14 << 3;
              }
              else {
                iVar15 = (int)puVar14 * 10;
              }
LAB_00468749:
              local_20 = local_20 + 1;
              puVar14 = (undefined *)(iVar15 + -0x30 + (int)piVar17);
              if ((local_24 != 0) && (local_10 = local_10 + -1, local_10 == 0)) goto LAB_0046877f;
              local_8 = local_8 + 1;
              piVar7 = param_1;
              local_18 = (int *)crt_stream_getc(param_1);
            }
            if ((int)crt_locale_type < 2) {
              uVar6 = (byte)crt_ctype_table[(int)local_18 * 2] & 0x80;
            }
            else {
              piVar3 = (int *)0x80;
              uVar6 = crt_isctype(piVar7,(int)local_18,0x80);
              piVar7 = piVar3;
            }
            if (uVar6 != 0) {
              iVar15 = (int)puVar14 << 4;
              piVar3 = piVar17;
              piVar17 = (int *)crt_hex_digit_value(piVar7,(uint)piVar17);
              piVar7 = piVar3;
              local_18 = piVar17;
              goto LAB_00468749;
            }
LAB_00468771:
            local_8 = local_8 + -1;
            piVar7 = param_1;
            crt_stream_ungetc_safe((uint)piVar17,param_1);
          }
LAB_0046877f:
          if (local_1b != '\0') {
            puVar14 = (undefined *)-(int)puVar14;
          }
        }
        else {
          if (local_13 == '\0') {
            while (piVar17 = local_18, uVar5 != 0x78) {
              if ((int)crt_locale_type < 2) {
                uVar6 = (byte)crt_ctype_table[(int)local_18 * 2] & 4;
              }
              else {
                uVar6 = crt_isctype(piVar7,(int)local_18,4);
              }
              if (uVar6 == 0) goto LAB_00468693;
              if (uVar5 == 0x6f) {
                if (0x37 < (int)piVar17) goto LAB_00468693;
                local_2c = __allshl(3,(int)local_2c._4_4_);
                piVar7 = extraout_ECX_02;
              }
              else {
                local_2c = __allmul((uint)local_2c,(int)local_2c._4_4_,10,0);
                piVar7 = extraout_ECX_03;
              }
LAB_00468665:
              local_20 = local_20 + 1;
              piVar17 = piVar17 + -0xc;
              local_2c = CONCAT44((int)local_2c._4_4_ + ((int)piVar17 >> 0x1f) +
                                  (uint)CARRY4((uint)local_2c,(uint)piVar17),
                                  (undefined *)((uint)local_2c + (int)piVar17));
              if ((local_24 != 0) && (local_10 = local_10 + -1, local_10 == 0)) goto LAB_004686a1;
              local_8 = local_8 + 1;
              piVar7 = param_1;
              local_18 = (int *)crt_stream_getc(param_1);
            }
            if ((int)crt_locale_type < 2) {
              uVar6 = (byte)crt_ctype_table[(int)local_18 * 2] & 0x80;
            }
            else {
              uVar6 = crt_isctype(piVar7,(int)local_18,0x80);
            }
            if (uVar6 != 0) {
              local_2c = __allshl(4,(int)local_2c._4_4_);
              piVar7 = piVar17;
              piVar17 = (int *)crt_hex_digit_value(this_01,(uint)piVar17);
              local_18 = piVar17;
              goto LAB_00468665;
            }
LAB_00468693:
            local_8 = local_8 + -1;
            piVar7 = param_1;
            crt_stream_ungetc_safe((uint)piVar17,param_1);
          }
LAB_004686a1:
          if (local_1b != '\0') {
            piVar7 = (int *)-((int)local_2c._4_4_ + (uint)((uint)local_2c != 0));
            local_2c = CONCAT44(piVar7,-(uint)local_2c);
          }
        }
        if (uVar5 == 0x46) {
          local_20 = 0;
        }
        if (local_20 == 0) goto LAB_00468868;
        if (local_12 == '\0') {
          local_38 = local_38 + 1;
LAB_004687a3:
          if (local_34 == (WCHAR *)0x0) {
            if (local_11 == '\0') {
              *local_30 = (WCHAR)puVar14;
            }
            else {
              *(undefined **)local_30 = puVar14;
            }
          }
          else {
            *(uint *)local_30 = (uint)local_2c;
            *(int **)(local_30 + 2) = local_2c._4_4_;
            piVar7 = local_2c._4_4_;
          }
        }
      }
LAB_004687c9:
      local_19 = local_19 + '\x01';
      param_2 = param_2 + 1;
      this = piVar7;
    }
    else {
      local_8 = local_8 + 1;
      piVar7 = (int *)crt_stream_getc(param_1);
      param_2 = pbVar9 + 1;
      local_18 = piVar7;
      if ((int *)(uint)*pbVar9 != piVar7) goto LAB_00468848;
      this = crt_ctype_table;
      if ((crt_ctype_table[((uint)piVar7 & 0xff) * 2 + 1] & 0x80) != 0) {
        local_8 = local_8 + 1;
        piVar17 = (int *)crt_stream_getc(param_1);
        this = (void *)(uint)*param_2;
        param_2 = pbVar9 + 2;
        if (this != piVar17) {
          local_8 = local_8 + -1;
          crt_stream_ungetc_safe((uint)piVar17,param_1);
          local_8 = local_8 + -1;
          crt_stream_ungetc_safe((uint)piVar7,param_1);
          goto LAB_00468868;
        }
        local_8 = local_8 + -1;
      }
    }
    if ((local_18 == (int *)0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
    goto LAB_0046886e;
    bVar1 = *param_2;
    pbVar9 = param_2;
    piVar7 = (int *)crt_ctype_table;
  } while( true );
}



/* crt_hex_digit_value @ 00468887 */

uint __thiscall crt_hex_digit_value(void *this,uint param_1)

{
  uint uVar1;
  
  if (crt_locale_type < 2) {
    uVar1 = (byte)crt_ctype_table[param_1 * 2] & 4;
  }
  else {
    uVar1 = crt_isctype(this,param_1,4);
  }
  if (uVar1 == 0) {
    param_1 = (param_1 & 0xffffffdf) - 7;
  }
  return param_1;
}



/* crt_stream_getc @ 004688be */

/* [binja] uint32_t sub_4688be(int32_t* arg1) */

uint __cdecl crt_stream_getc(int *arg1)

{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  
  piVar1 = arg1 + 1;
  *piVar1 = *piVar1 + -1;
  if (-1 < *piVar1) {
    bVar2 = *(byte *)*arg1;
    *arg1 = (int)((byte *)*arg1 + 1);
    return (uint)bVar2;
  }
  uVar3 = crt_filbuf(arg1);
  return uVar3;
}



/* crt_stream_ungetc_safe @ 004688d8 */

void __cdecl crt_stream_ungetc_safe(uint param_1,int *param_2)

{
  if (param_1 != 0xffffffff) {
    crt_ungetc(param_1,param_2);
  }
  return;
}



/* crt_stream_skip_whitespace @ 004688ef */

/* [binja] uint32_t sub_4688ef(int32_t* arg1, int32_t* arg2) */

uint __cdecl crt_stream_skip_whitespace(int *arg1,int *arg2)

{
  uint c;
  uint uVar1;
  void *this;
  
  do {
    *arg1 = *arg1 + 1;
    c = crt_stream_getc(arg2);
    uVar1 = crt_isspace(this,c);
  } while (uVar1 != 0);
  return c;
}



/* crt_skip_program_name @ 00468913 */

/* returns command line tail after argv[0] */

uchar * crt_skip_program_name(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if (crt_mbcs_initialized == 0) {
    crt_mbcs_init();
  }
  bVar1 = *crt_command_line_ptr;
  pbVar4 = crt_command_line_ptr;
  if (bVar1 == 0x22) {
    while( true ) {
      pbVar3 = pbVar4;
      bVar1 = pbVar3[1];
      pbVar4 = pbVar3 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      iVar2 = crt_isleadbyte(bVar1);
      if (iVar2 != 0) {
        pbVar4 = pbVar3 + 2;
      }
    }
    if (*pbVar4 == 0x22) goto LAB_00468950;
  }
  else {
    while (0x20 < bVar1) {
      bVar1 = pbVar4[1];
      pbVar4 = pbVar4 + 1;
    }
  }
  for (; (*pbVar4 != 0 && (*pbVar4 < 0x21)); pbVar4 = pbVar4 + 1) {
LAB_00468950:
  }
  return pbVar4;
}



/* crt_build_environ @ 0046896b */

/* builds environ array from environment block */

void crt_build_environ(void)

{
  char cVar1;
  size_t sVar2;
  char **ppcVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  
  if (crt_mbcs_initialized == 0) {
    crt_mbcs_init();
  }
  iVar5 = 0;
  for (pcVar6 = crt_env_string_copy; *pcVar6 != '\0'; pcVar6 = pcVar6 + sVar2 + 1) {
    if (*pcVar6 != '=') {
      iVar5 = iVar5 + 1;
    }
    sVar2 = _strlen(pcVar6);
  }
  ppcVar3 = _malloc(iVar5 * 4 + 4);
  crt_environ = ppcVar3;
  if (ppcVar3 == (char **)0x0) {
    __amsg_exit(9);
  }
  cVar1 = *crt_env_string_copy;
  pcVar6 = crt_env_string_copy;
  while (cVar1 != '\0') {
    sVar2 = _strlen(pcVar6);
    if (*pcVar6 != '=') {
      pcVar4 = _malloc(sVar2 + 1);
      *ppcVar3 = pcVar4;
      if (pcVar4 == (char *)0x0) {
        __amsg_exit(9);
      }
      crt_strcpy(*ppcVar3,pcVar6);
      ppcVar3 = ppcVar3 + 1;
    }
    pcVar6 = pcVar6 + sVar2 + 1;
    cVar1 = *pcVar6;
  }
  crt_free_base(crt_env_string_copy);
  crt_env_string_copy = (char *)0x0;
  *ppcVar3 = (char *)0x0;
  crt_environ_initialized = 1;
  return;
}



/* crt_build_argv @ 00468a24 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* parses command line into argv/argc */

void crt_build_argv(void)

{
  undefined4 *puVar1;
  byte *pbVar2;
  int local_c;
  int local_8;
  
  if (crt_mbcs_initialized == 0) {
    crt_mbcs_init();
  }
  GetModuleFileNameA((HMODULE)0x0,&crt_lc_collate_type,0x104);
  _DAT_004d99b0 = &crt_lc_collate_type;
  pbVar2 = &crt_lc_collate_type;
  if (*crt_command_line_ptr != 0) {
    pbVar2 = crt_command_line_ptr;
  }
  crt_parse_cmdline(pbVar2,(undefined4 *)0x0,(byte *)0x0,&local_8,&local_c);
  puVar1 = _malloc(local_c + local_8 * 4);
  if (puVar1 == (undefined4 *)0x0) {
    __amsg_exit(8);
  }
  crt_parse_cmdline(pbVar2,puVar1,(byte *)(puVar1 + local_8),&local_8,&local_c);
  _DAT_004d9998 = puVar1;
  _DAT_004d9994 = local_8 + -1;
  return;
}



/* crt_parse_cmdline @ 00468abd */

/* low-level argv parser for command line */

void __cdecl
crt_parse_cmdline(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  *param_5 = 0;
  *param_4 = 1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while( true ) {
      bVar1 = param_1[1];
      pbVar4 = param_1 + 1;
      if ((bVar1 == 0x22) || (bVar1 == 0)) break;
      if (((*(byte *)((int)&crt_char_type_table + bVar1 + 1) & 4) != 0) &&
         (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
        pbVar4 = param_1 + 2;
      }
      *param_5 = *param_5 + 1;
      param_1 = pbVar4;
      if (param_3 != (byte *)0x0) {
        *param_3 = *pbVar4;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar4 == 0x22) {
      pbVar4 = param_1 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *param_1;
        param_3 = param_3 + 1;
      }
      bVar1 = *param_1;
      pbVar4 = param_1 + 1;
      if ((*(byte *)((int)&crt_char_type_table + bVar1 + 1) & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        pbVar4 = param_1 + 2;
      }
      if (bVar1 == 0x20) break;
      if (bVar1 == 0) goto LAB_00468b68;
      param_1 = pbVar4;
    } while (bVar1 != 9);
    if (bVar1 == 0) {
LAB_00468b68:
      pbVar4 = pbVar4 + -1;
    }
    else if (param_3 != (byte *)0x0) {
      param_3[-1] = 0;
    }
  }
  bVar2 = false;
  puVar7 = param_2;
  while (*pbVar4 != 0) {
    for (; (*pbVar4 == 0x20 || (*pbVar4 == 9)); pbVar4 = pbVar4 + 1) {
    }
    if (*pbVar4 == 0) break;
    if (puVar7 != (undefined4 *)0x0) {
      *puVar7 = param_3;
      puVar7 = puVar7 + 1;
      param_2 = puVar7;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar3 = true;
      uVar6 = 0;
      for (; *pbVar4 == 0x5c; pbVar4 = pbVar4 + 1) {
        uVar6 = uVar6 + 1;
      }
      if (*pbVar4 == 0x22) {
        pbVar5 = pbVar4;
        if ((uVar6 & 1) == 0) {
          if ((!bVar2) || (pbVar5 = pbVar4 + 1, pbVar4[1] != 0x22)) {
            bVar3 = false;
            pbVar5 = pbVar4;
          }
          bVar2 = !bVar2;
          puVar7 = param_2;
        }
        uVar6 = uVar6 >> 1;
        pbVar4 = pbVar5;
      }
      for (; uVar6 != 0; uVar6 = uVar6 - 1) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      bVar1 = *pbVar4;
      if ((bVar1 == 0) || ((!bVar2 && ((bVar1 == 0x20 || (bVar1 == 9)))))) break;
      if (bVar3) {
        if (param_3 == (byte *)0x0) {
          if ((*(byte *)((int)&crt_char_type_table + bVar1 + 1) & 4) != 0) {
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if ((*(byte *)((int)&crt_char_type_table + bVar1 + 1) & 4) != 0) {
            *param_3 = bVar1;
            param_3 = param_3 + 1;
            pbVar4 = pbVar4 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *pbVar4;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      pbVar4 = pbVar4 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (puVar7 != (undefined4 *)0x0) {
    *puVar7 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}



/* crt_get_environment_strings @ 00468c71 */

/* returns a malloc'd copy of the environment block */

char * crt_get_environment_strings(void)

{
  char cVar1;
  WCHAR WVar2;
  WCHAR *pWVar3;
  WCHAR *pWVar4;
  int iVar5;
  size_t _Size;
  LPSTR lpMultiByteStr;
  char *pcVar6;
  char *pcVar7;
  LPWCH lpWideCharStr;
  LPCH penv;
  LPSTR local_8;
  
  lpWideCharStr = (LPWCH)0x0;
  penv = (LPCH)0x0;
  if (crt_env_string_type == 0) {
    lpWideCharStr = GetEnvironmentStringsW();
    if (lpWideCharStr != (LPWCH)0x0) {
      crt_env_string_type = 1;
LAB_00468cc8:
      if ((lpWideCharStr == (LPWCH)0x0) &&
         (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr == (LPWCH)0x0)) {
        return (char *)0x0;
      }
      WVar2 = *lpWideCharStr;
      pWVar4 = lpWideCharStr;
      while (WVar2 != L'\0') {
        do {
          pWVar3 = pWVar4;
          pWVar4 = pWVar3 + 1;
        } while (*pWVar4 != L'\0');
        pWVar4 = pWVar3 + 2;
        WVar2 = *pWVar4;
      }
      iVar5 = ((int)pWVar4 - (int)lpWideCharStr >> 1) + 1;
      _Size = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCCH)0x0,(LPBOOL)0x0);
      local_8 = (LPSTR)0x0;
      if (((_Size != 0) && (lpMultiByteStr = _malloc(_Size), lpMultiByteStr != (LPSTR)0x0)) &&
         (iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,lpMultiByteStr,_Size,(LPCCH)0x0,
                                      (LPBOOL)0x0), local_8 = lpMultiByteStr, iVar5 == 0)) {
        crt_free_base(lpMultiByteStr);
        local_8 = (LPSTR)0x0;
      }
      FreeEnvironmentStringsW(lpWideCharStr);
      return local_8;
    }
    penv = GetEnvironmentStrings();
    if (penv == (LPCH)0x0) {
      return (char *)0x0;
    }
    crt_env_string_type = 2;
  }
  else {
    if (crt_env_string_type == 1) goto LAB_00468cc8;
    if (crt_env_string_type != 2) {
      return (char *)0x0;
    }
  }
  if ((penv == (LPCH)0x0) && (penv = GetEnvironmentStrings(), penv == (LPCH)0x0)) {
    return (char *)0x0;
  }
  cVar1 = *penv;
  pcVar6 = penv;
  while (cVar1 != '\0') {
    do {
      pcVar7 = pcVar6;
      pcVar6 = pcVar7 + 1;
    } while (*pcVar6 != '\0');
    pcVar6 = pcVar7 + 2;
    cVar1 = *pcVar6;
  }
  pcVar7 = _malloc((size_t)(pcVar6 + (1 - (int)penv)));
  if (pcVar7 == (char *)0x0) {
    pcVar7 = (char *)0x0;
  }
  else {
    crt_bufcpy(pcVar7,penv,(size_t)(pcVar6 + (1 - (int)penv)));
  }
  FreeEnvironmentStringsA(penv);
  return pcVar7;
}



/* crt_runtime_error_banner @ 00468da3 */

/* runtime error prolog/epilog around report */

void crt_runtime_error_banner(void)

{
  if ((crt_os_type_flag == 1) || ((crt_os_type_flag == 0 && (crt_os_platform_type == 1)))) {
    crt_report_runtime_error(0xfc);
    if (crt_new_handler != (code *)0x0) {
      (*crt_new_handler)();
    }
    crt_report_runtime_error(0xff);
  }
  return;
}



/* crt_report_runtime_error @ 00468ddc */

/* formats and displays CRT runtime errors */

void __cdecl crt_report_runtime_error(DWORD param_1)

{
  undefined4 *puVar1;
  DWORD *pDVar2;
  DWORD DVar3;
  size_t sVar4;
  HANDLE hFile;
  int iVar5;
  CHAR *_Dest;
  char acStackY_1e3 [7];
  LPCVOID lpBuffer;
  LPOVERLAPPED lpOverlapped;
  CHAR local_1a8 [260];
  char local_a4 [160];
  
  iVar5 = 0;
  pDVar2 = &crt_signal_handler_table;
  do {
    if (param_1 == *pDVar2) break;
    pDVar2 = pDVar2 + 2;
    iVar5 = iVar5 + 1;
  } while (pDVar2 < &DAT_0047dbb8);
  if (param_1 == (&crt_signal_handler_table)[iVar5 * 2]) {
    if ((crt_os_type_flag == 1) || ((crt_os_type_flag == 0 && (crt_os_platform_type == 1)))) {
      pDVar2 = &param_1;
      puVar1 = (undefined4 *)(iVar5 * 8 + 0x47db2c);
      lpOverlapped = (LPOVERLAPPED)0x0;
      sVar4 = _strlen((char *)*puVar1);
      lpBuffer = (LPCVOID)*puVar1;
      hFile = GetStdHandle(0xfffffff4);
      WriteFile(hFile,lpBuffer,sVar4,pDVar2,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar3 = GetModuleFileNameA((HMODULE)0x0,local_1a8,0x104);
      if (DVar3 == 0) {
        crt_strcpy(local_1a8,"<program name unknown>");
      }
      _Dest = local_1a8;
      sVar4 = _strlen(local_1a8);
      if (0x3c < sVar4 + 1) {
        sVar4 = _strlen(local_1a8);
        _Dest = acStackY_1e3 + sVar4;
        _strncpy(_Dest,"...",3);
      }
      crt_strcpy(local_a4,"Runtime Error!\n\nProgram: ");
      crt_strcat(local_a4,_Dest);
      crt_strcat(local_a4,"\n\n");
      crt_strcat(local_a4,*(char **)(iVar5 * 8 + 0x47db2c));
      acStackY_1e3[3] = '\0';
      acStackY_1e3[4] = -0x71;
      acStackY_1e3[5] = 'F';
      acStackY_1e3[6] = '\0';
      crt_write_internal((int)local_a4,0x46feb8,0x12010);
    }
  }
  return;
}



/* crt_scanf_format_handler @ 00468f2f */

float10 __cdecl crt_scanf_format_handler(undefined8 param_1,short param_2)

{
  undefined8 local_c;
  
  local_c = (double)CONCAT26((param_2 + 0x3fe) * 0x10 | param_1._6_2_ & 0x800f,(int6)param_1);
  return (float10)local_c;
}



/* FUN_00468f58 @ 00468f58 */

undefined4 __cdecl FUN_00468f58(int param_1,uint param_2)

{
  undefined4 uStack_8;
  
  if (param_2 == 0x7ff00000) {
    if (param_1 == 0) {
      return 1;
    }
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    return 2;
  }
  if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
    uStack_8 = 3;
  }
  else {
    if (((param_2._2_2_ & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0 && (param_1 == 0)))) {
      return 0;
    }
    uStack_8 = 4;
  }
  return uStack_8;
}



/* FUN_00468fb2 @ 00468fb2 */

float10 __cdecl FUN_00468fb2(uint param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  float10 fVar5;
  undefined8 local_c;
  
  if ((double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))) ==
      0.0) {
    iVar4 = 0;
    local_c = 0.0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar4 = -0x3fd;
    if (0.0 <= (double)CONCAT17(param_2._3_1_,
                                CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1)))) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    while ((param_2._2_1_ & 0x10) == 0) {
      iVar2 = CONCAT13(param_2._3_1_,CONCAT12(param_2._2_1_,(ushort)param_2)) << 1;
      param_2._0_2_ = (ushort)iVar2;
      param_2._2_1_ = (byte)((uint)iVar2 >> 0x10);
      param_2._3_1_ = (byte)((uint)iVar2 >> 0x18);
      if ((param_1 & 0x80000000) != 0) {
        param_2._0_2_ = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
      iVar4 = iVar4 + -1;
    }
    uVar1 = CONCAT11(param_2._3_1_,param_2._2_1_) & 0xffef;
    param_2._2_1_ = (byte)uVar1;
    param_2._3_1_ = (byte)(uVar1 >> 8);
    if (bVar3) {
      param_2._3_1_ = param_2._3_1_ | 0x80;
    }
    fVar5 = crt_scanf_format_handler(CONCAT17(param_2._3_1_,
                                  CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))),0);
    local_c = (double)fVar5;
  }
  else {
    fVar5 = crt_scanf_format_handler(CONCAT17(param_2._3_1_,
                                  CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))),0);
    local_c = (double)fVar5;
    iVar4 = (short)((ushort)(param_2 >> 0x14) & 0x7ff) + -0x3fe;
  }
  *param_3 = iVar4;
  return (float10)local_c;
}



/* FUN_00469073 @ 00469073 */

void __cdecl
FUN_00469073(uint *param_1,uint *param_2,uint param_3,uint param_4,undefined8 *param_5,
            undefined8 *param_6)

{
  uint *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  
  uVar3 = param_3;
  puVar1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((param_3 & 0x10) != 0) {
    param_3 = 0xc000008f;
    param_1[1] = param_1[1] | 1;
  }
  if ((uVar3 & 2) != 0) {
    param_3 = 0xc0000093;
    param_1[1] = param_1[1] | 2;
  }
  if ((uVar3 & 1) != 0) {
    param_3 = 0xc0000091;
    param_1[1] = param_1[1] | 4;
  }
  if ((uVar3 & 4) != 0) {
    param_3 = 0xc000008e;
    param_1[1] = param_1[1] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_3 = 0xc0000090;
    param_1[1] = param_1[1] | 0x10;
  }
  param_1[2] = (~*param_2 & 1) << 4 | param_1[2] & 0xffffffef;
  param_1[2] = (~*param_2 & 4) << 1 | param_1[2] & 0xfffffff7;
  param_1[2] = ~*param_2 >> 1 & 4 | param_1[2] & 0xfffffffb;
  param_1[2] = ~*param_2 >> 3 & 2 | param_1[2] & 0xfffffffd;
  param_1[2] = ~*param_2 >> 5 & 1 | param_1[2] & 0xfffffffe;
  uVar3 = FUN_00469565();
  puVar2 = param_6;
  if ((uVar3 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar3 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar3 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar3 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar3 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar3 = *puVar1 & 0xc00;
  if (uVar3 == 0) {
    *param_1 = *param_1 & 0xfffffffc;
  }
  else {
    if (uVar3 == 0x400) {
      uVar3 = *param_1 & 0xfffffffd | 1;
    }
    else {
      if (uVar3 != 0x800) {
        if (uVar3 == 0xc00) {
          *param_1 = *param_1 | 3;
        }
        goto LAB_004691e8;
      }
      uVar3 = *param_1 & 0xfffffffe | 2;
    }
    *param_1 = uVar3;
  }
LAB_004691e8:
  uVar3 = *puVar1 & 0x300;
  if (uVar3 == 0) {
    uVar3 = *param_1 & 0xffffffeb | 8;
LAB_0046921e:
    *param_1 = uVar3;
  }
  else {
    if (uVar3 == 0x200) {
      uVar3 = *param_1 & 0xffffffe7 | 4;
      goto LAB_0046921e;
    }
    if (uVar3 == 0x300) {
      *param_1 = *param_1 & 0xffffffe3;
    }
  }
  *param_1 = (param_4 & 0xfff) << 5 | *param_1 & 0xfffe001f;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 4) = *param_5;
  param_1[0x14] = param_1[0x14] | 1;
  param_1[0x14] = param_1[0x14] & 0xffffffe3 | 2;
  *(undefined8 *)(param_1 + 0x10) = *param_6;
  FUN_00469573();
  RaiseException(param_3,0,1,(ULONG_PTR *)&param_1);
  if ((param_1[2] & 0x10) != 0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  if ((param_1[2] & 8) != 0) {
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  if ((param_1[2] & 4) != 0) {
    *puVar1 = *puVar1 & 0xfffffff7;
  }
  if ((param_1[2] & 2) != 0) {
    *puVar1 = *puVar1 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  uVar3 = *param_1 & 3;
  if (uVar3 == 0) {
    *puVar1 = *puVar1 & 0xfffff3ff;
  }
  else {
    if (uVar3 == 1) {
      uVar3 = *puVar1 & 0xfffff7ff | 0x400;
    }
    else {
      if (uVar3 != 2) {
        if (uVar3 == 3) {
          *(byte *)((int)puVar1 + 1) = *(byte *)((int)puVar1 + 1) | 0xc;
        }
        goto LAB_004692f3;
      }
      uVar3 = *puVar1 & 0xfffffbff | 0x800;
    }
    *puVar1 = uVar3;
  }
LAB_004692f3:
  uVar3 = *param_1 >> 2 & 7;
  if (uVar3 == 0) {
    uVar3 = *puVar1 & 0xfffff3ff | 0x300;
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 == 2) {
        *puVar1 = *puVar1 & 0xfffff3ff;
      }
      goto LAB_0046931c;
    }
    uVar3 = *puVar1 & 0xfffff3ff | 0x200;
  }
  *puVar1 = uVar3;
LAB_0046931c:
  *puVar2 = *(undefined8 *)(param_1 + 0x10);
  return;
}



/* FUN_00469326 @ 00469326 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __cdecl FUN_00469326(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  bool bVar2;
  uint uVar3;
  bool bVar4;
  float10 fVar5;
  undefined8 local_10;
  int local_8;
  
  uVar3 = param_1 & 0x1f;
  bVar2 = true;
  if (((param_1 & 8) != 0) && ((param_3 & 1) != 0)) {
    crt_noop();
    uVar3 = param_1 & 0x17;
    goto LAB_0046951b;
  }
  if (((param_1 & 4) != 0) && ((param_3 & 4) != 0)) {
    crt_noop();
    uVar3 = param_1 & 0x1b;
    goto LAB_0046951b;
  }
  if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
    if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
      bVar4 = (param_1 & 0x10) != 0;
      dVar1 = *param_2;
      if (dVar1 != 0.0) {
        fVar5 = FUN_00468fb2(SUB84(dVar1,0),(uint)((ulonglong)dVar1 >> 0x20),&local_8);
        local_8 = local_8 + -0x600;
        if (local_8 < -0x432) {
          local_10 = 0.0;
          bVar4 = bVar2;
        }
        else {
          local_10 = (double)(ulonglong)
                             (SUB87((double)fVar5,0) & 0xfffffffffffff | 0x10000000000000);
          if (local_8 < -0x3fd) {
            local_8 = -0x3fd - local_8;
            do {
              if ((((ulonglong)local_10 & 1) != 0) && (!bVar4)) {
                bVar4 = bVar2;
              }
              uVar3 = (uint)local_10 >> 1;
              if (((ulonglong)local_10 & 0x100000000) != 0) {
                local_10._3_1_ = (byte)((ulonglong)local_10 >> 0x18) >> 1;
                local_10._0_3_ = (undefined3)uVar3;
                local_10._0_4_ = CONCAT13(local_10._3_1_,(undefined3)local_10) | 0x80000000;
                uVar3 = (uint)local_10;
              }
              local_10._0_4_ = uVar3;
              local_10 = (double)CONCAT44(local_10._4_4_ >> 1,(uint)local_10);
              local_8 = local_8 + -1;
            } while (local_8 != 0);
          }
          if ((double)fVar5 < 0.0) {
            local_10 = -local_10;
          }
        }
        *param_2 = local_10;
        bVar2 = bVar4;
      }
      if (bVar2) {
        crt_noop();
      }
      uVar3 = param_1 & 0x1d;
    }
    goto LAB_0046951b;
  }
  crt_noop();
  uVar3 = param_3 & 0xc00;
  dVar1 = crt_daylight_flag;
  if (uVar3 == 0) {
    if (*param_2 <= 0.0) {
      dVar1 = -crt_daylight_flag;
    }
LAB_0046943b:
    *param_2 = dVar1;
  }
  else {
    if (uVar3 == 0x400) {
      dVar1 = crt_timezone_name_std;
      if (*param_2 <= 0.0) {
        dVar1 = -crt_daylight_flag;
      }
      goto LAB_0046943b;
    }
    if (uVar3 == 0x800) {
      if (*param_2 <= 0.0) {
        dVar1 = -crt_timezone_name_std;
      }
      goto LAB_0046943b;
    }
    if (uVar3 == 0xc00) {
      dVar1 = crt_timezone_name_std;
      if (*param_2 <= 0.0) {
        dVar1 = -crt_timezone_name_std;
      }
      goto LAB_0046943b;
    }
  }
  uVar3 = param_1 & 0x1e;
LAB_0046951b:
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    crt_noop();
    uVar3 = uVar3 & 0xffffffef;
  }
  return uVar3 == 0;
}



/* FUN_0046953d @ 0046953d */

/* [binja] int32_t* sub_46953d(int32_t* arg1) */

int * __cdecl FUN_0046953d(int *arg1)

{
  int *piVar1;
  
  if (arg1 == (int *)0x1) {
    arg1 = crt_errno_ptr();
    *arg1 = 0x21;
  }
  else if ((1 < (int)arg1) && ((int)arg1 < 4)) {
    piVar1 = crt_errno_ptr();
    *piVar1 = 0x22;
    return piVar1;
  }
  return arg1;
}



/* FUN_00469565 @ 00469565 */

int FUN_00469565(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



/* FUN_00469573 @ 00469573 */

int FUN_00469573(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}



/* FUN_00469582 @ 00469582 */

int FUN_00469582(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}



/* crt_noop @ 004695a5 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void crt_noop(void)

{
  return;
}



/* crt_cxx_frame_handler @ 004695fb */

/* MSVC C++ exception frame handler */

int __cdecl
crt_cxx_frame_handler
          (PEXCEPTION_RECORD record,PVOID frame,DWORD context,void *dispatcher,int *func_info,
          int try_level,PVOID handler_data,char is_rethrow)

{
  code *pcVar1;
  int iVar2;
  
  if (*func_info != 0x19930520) {
    crt_invalid_parameter_noinfo_noreturn();
  }
  if ((record->ExceptionFlags & 0x66) == 0) {
    if (func_info[3] != 0) {
      if (((record->ExceptionCode == 0xe06d7363) && (0x19930520 < record->ExceptionInformation[0]))
         && (pcVar1 = *(code **)(record->ExceptionInformation[2] + 8), pcVar1 != (code *)0x0)) {
        iVar2 = (*pcVar1)(record,frame,context,dispatcher,func_info,try_level,handler_data,
                          is_rethrow);
        return iVar2;
      }
      crt_cxx_find_handler(record,frame,context,dispatcher,(int)func_info,is_rethrow,try_level,handler_data)
      ;
    }
  }
  else if ((func_info[1] != 0) && (try_level == 0)) {
    crt_cxx_unwind_handler((int)frame,dispatcher,(int)func_info,-1);
  }
  return 1;
}



/* crt_cxx_find_handler @ 00469696 */

void __cdecl
crt_cxx_find_handler(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,int param_5,
            char param_6,int param_7,PVOID param_8)

{
  byte *arg1;
  bool bVar1;
  DWORD *pDVar2;
  undefined3 extraout_var;
  int *piVar3;
  int iVar4;
  int *piVar5;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_18 = local_18 & 0xffffff00;
  local_14 = *(int *)((int)param_2 + 8);
  if ((local_14 < -1) || (*(int *)(param_5 + 4) <= local_14)) {
    crt_invalid_parameter_noinfo_noreturn();
  }
  if (param_1->ExceptionCode == 0xe06d7363) {
    if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
       (param_1->ExceptionInformation[2] == 0)) {
      pDVar2 = crt_get_thread_data();
      if (pDVar2[0x1b] == 0) {
        return;
      }
      pDVar2 = crt_get_thread_data();
      param_1 = (PEXCEPTION_RECORD)pDVar2[0x1b];
      pDVar2 = crt_get_thread_data();
      param_3 = pDVar2[0x1c];
      local_18 = CONCAT31(local_18._1_3_,1);
      bVar1 = crt_is_valid_read_ptr(param_1,1);
      if (CONCAT31(extraout_var,bVar1) == 0) {
        crt_invalid_parameter_noinfo_noreturn();
      }
      if (param_1->ExceptionCode != 0xe06d7363) goto LAB_0046981e;
      if (((param_1->NumberParameters == 3) && (param_1->ExceptionInformation[0] == 0x19930520)) &&
         (param_1->ExceptionInformation[2] == 0)) {
        crt_invalid_parameter_noinfo_noreturn();
      }
    }
    iVar4 = local_14;
    if (((param_1->ExceptionCode == 0xe06d7363) && (param_1->NumberParameters == 3)) &&
       (param_1->ExceptionInformation[0] == 0x19930520)) {
      piVar3 = (int *)crt_cxx_match_handler(param_5,param_7,local_14,&local_8,&local_1c);
      do {
        if (local_1c <= local_8) {
          if (param_6 == '\0') {
            return;
          }
          crt_cxx_adjust_pointer(param_1);
          return;
        }
        if ((*piVar3 <= iVar4) && (iVar4 <= piVar3[1])) {
          arg1 = (byte *)piVar3[4];
          for (local_10 = piVar3[3]; iVar4 = local_14, 0 < local_10; local_10 = local_10 + -1) {
            piVar5 = *(int **)(param_1->ExceptionInformation[2] + 0xc);
            for (local_c = *piVar5; 0 < local_c; local_c = local_c + -1) {
              piVar5 = piVar5 + 1;
              iVar4 = FUN_004698f3((char *)arg1,(char *)*piVar5,
                                   (int *)param_1->ExceptionInformation[2]);
              if (iVar4 != 0) {
                crt_cxx_frame_handler3(param_1,param_2,param_3,param_4,param_5,arg1,(byte *)*piVar5,piVar3,
                             param_7,param_8);
                iVar4 = local_14;
                goto LAB_004697fe;
              }
            }
            arg1 = arg1 + 0x10;
          }
        }
LAB_004697fe:
        local_8 = local_8 + 1;
        piVar3 = piVar3 + 5;
      } while( true );
    }
  }
LAB_0046981e:
  if (param_6 == '\0') {
    FUN_00469849(param_1,param_2,param_3,param_4,param_5,local_14,param_7,param_8);
    return;
  }
  crt_terminate();
  return;
}



/* FUN_00469849 @ 00469849 */

void __cdecl
FUN_00469849(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,int param_5,
            int param_6,int param_7,PVOID param_8)

{
  DWORD *pDVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint local_c;
  uint local_8;
  
  pDVar1 = crt_get_thread_data();
  if ((pDVar1[0x1a] != 0) &&
     (iVar2 = FUN_00463431(&param_1->ExceptionCode,param_2,param_3,param_4,param_5,param_7,param_8),
     iVar2 != 0)) {
    return;
  }
  piVar3 = (int *)crt_cxx_match_handler(param_5,param_7,param_6,&local_8,&local_c);
  for (; local_8 < local_c; local_8 = local_8 + 1) {
    if ((*piVar3 <= param_6) && (param_6 <= piVar3[1])) {
      iVar4 = piVar3[3] * 0x10 + piVar3[4];
      iVar2 = *(int *)(iVar4 + -0xc);
      if ((iVar2 == 0) || (*(char *)(iVar2 + 8) == '\0')) {
        crt_cxx_frame_handler3(param_1,param_2,param_3,param_4,param_5,(byte *)(iVar4 + -0x10),(byte *)0x0,
                     piVar3,param_7,param_8);
      }
    }
    piVar3 = piVar3 + 5;
  }
  return;
}



/* FUN_004698f3 @ 004698f3 */

/* [binja] int32_t sub_4698f3(char* arg1, char* arg2, int32_t* arg3) */

int __cdecl FUN_004698f3(char *arg1,char *arg2,int *arg3)

{
  int iVar1;
  
  iVar1 = *(int *)(arg1 + 4);
  if ((iVar1 == 0) || (*(char *)(iVar1 + 8) == '\0')) {
LAB_0046994a:
    iVar1 = 1;
  }
  else {
    if (iVar1 == *(int *)(arg2 + 4)) {
LAB_00469924:
      if (((((*arg2 & 2U) == 0) || ((*arg1 & 8U) != 0)) &&
          (((*arg3 & 1U) == 0 || ((*arg1 & 1U) != 0)))) &&
         (((*arg3 & 2U) == 0 || ((*arg1 & 2U) != 0)))) goto LAB_0046994a;
    }
    else {
      iVar1 = _strcmp((char *)(iVar1 + 8),(char *)(*(int *)(arg2 + 4) + 8));
      if (iVar1 == 0) goto LAB_00469924;
    }
    iVar1 = 0;
  }
  return iVar1;
}



/* crt_cxx_unwind_handler @ 00469950 */

void __cdecl crt_cxx_unwind_handler(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046ffd0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  for (iVar2 = *(int *)(param_1 + 8); local_8 = 0xffffffff, iVar2 != param_4;
      iVar2 = *(int *)(*(int *)(param_3 + 8) + iVar2 * 8)) {
    if ((iVar2 < 0) || (*(int *)(param_3 + 4) <= iVar2)) {
      crt_invalid_parameter_noinfo_noreturn();
    }
    local_8 = 0;
    iVar1 = *(int *)(*(int *)(param_3 + 8) + 4 + iVar2 * 8);
    if (iVar1 != 0) {
      __CallSettingFrame_12(iVar1,param_1,0x103);
    }
  }
  *(int *)(param_1 + 8) = iVar2;
  ExceptionList = local_14;
  return;
}



/* crt_cxx_frame_handler3 @ 004699ee */

void __cdecl
crt_cxx_frame_handler3(PEXCEPTION_RECORD param_1,PVOID param_2,DWORD param_3,undefined4 param_4,int param_5,
            byte *param_6,byte *param_7,int *param_8,int param_9,PVOID param_10)

{
  undefined *UNRECOVERED_JUMPTABLE;
  
  if (param_7 != (byte *)0x0) {
    FUN_00469bae(param_1,(int)param_2,(char *)param_6,(char *)param_7);
  }
  if (param_10 == (PVOID)0x0) {
    param_10 = param_2;
  }
  crt_cxx_move_ctor((int)param_10,param_1);
  crt_cxx_unwind_handler((int)param_2,param_4,param_5,*param_8);
  *(int *)((int)param_2 + 8) = param_8[1] + 1;
  UNRECOVERED_JUMPTABLE =
       (undefined *)
       FUN_00469a69((DWORD)param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,
                    0x100);
  if (UNRECOVERED_JUMPTABLE != (undefined *)0x0) {
    FUN_004632f1(UNRECOVERED_JUMPTABLE);
  }
  return;
}



/* FUN_00469a69 @ 00469a69 */

undefined4 __cdecl
FUN_00469a69(DWORD param_1,undefined4 param_2,DWORD param_3,undefined4 param_4,undefined4 param_5,
            int param_6,int param_7)

{
  DWORD *pDVar1;
  undefined4 uVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_0046ffe0;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  crt_get_thread_data();
  crt_get_thread_data();
  pDVar1 = crt_get_thread_data();
  pDVar1[0x1b] = param_1;
  pDVar1 = crt_get_thread_data();
  pDVar1[0x1c] = param_3;
  local_8 = 1;
  uVar2 = FUN_004633b8(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  FUN_00469b36();
  ExceptionList = local_14;
  return uVar2;
}



/* FUN_00469b36 @ 00469b36 */

void FUN_00469b36(void)

{
  DWORD *pDVar1;
  int unaff_EBP;
  int unaff_ESI;
  int *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  pDVar1 = crt_get_thread_data();
  pDVar1[0x1b] = *(DWORD *)(unaff_EBP + -0x1c);
  pDVar1 = crt_get_thread_data();
  pDVar1[0x1c] = *(DWORD *)(unaff_EBP + -0x20);
  if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[4] == 3)) && (unaff_EDI[5] == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (*(int *)(unaff_EBP + -0x2c) != 0)))) {
    __abnormal_termination();
    crt_cxx_adjust_pointer(unaff_EDI);
  }
  return;
}



/* FUN_00469bae @ 00469bae */

/* [binja] void* sub_469bae(void* arg1, int32_t arg2, char* arg3, char* arg4) */

void * __cdecl FUN_00469bae(void *arg1,int arg2,char *arg3,char *arg4)

{
  int *dst;
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  void *pvVar3;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  void *extraout_EAX;
  size_t size;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_0046fff8;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  pvVar3 = *(void **)(arg3 + 4);
  if (pvVar3 == (void *)0x0) {
    return (void *)0x0;
  }
  if (*(char *)((int)pvVar3 + 8) == '\0') {
    return pvVar3;
  }
  if (*(int *)(arg3 + 8) == 0) {
    return (void *)0x0;
  }
  dst = (int *)(*(int *)(arg3 + 8) + 0xc + arg2);
  local_8 = 0;
  if ((*arg3 & 8U) == 0) {
    if ((*arg4 & 1U) == 0) {
      if (*(int *)(arg4 + 0x18) == 0) {
        ExceptionList = &local_14;
        bVar1 = crt_is_valid_read_ptr(*(void **)((int)arg1 + 0x18),1);
        if ((CONCAT31(extraout_var_03,bVar1) != 0) &&
           (bVar1 = crt_is_valid_write_ptr(dst,1), CONCAT31(extraout_var_04,bVar1) != 0)) {
          size = *(size_t *)(arg4 + 0x14);
          pvVar3 = (void *)crt_cxx_calc_catch_addr(*(int *)((int)arg1 + 0x18),(int *)(arg4 + 8));
          pvVar3 = crt_memmove(dst,pvVar3,size);
          ExceptionList = local_14;
          return pvVar3;
        }
      }
      else {
        ExceptionList = &local_14;
        bVar1 = crt_is_valid_read_ptr(*(void **)((int)arg1 + 0x18),1);
        if (((CONCAT31(extraout_var_05,bVar1) != 0) &&
            (bVar1 = crt_is_valid_write_ptr(dst,1), CONCAT31(extraout_var_06,bVar1) != 0)) &&
           (bVar1 = crt_is_valid_code_ptr(*(FARPROC *)(arg4 + 0x18)), CONCAT31(extraout_var_07,bVar1) != 0))
        {
          if ((*arg4 & 4U) != 0) {
            crt_cxx_calc_catch_addr(*(int *)((int)arg1 + 0x18),(int *)(arg4 + 8));
            pvVar3 = (void *)FUN_0046332c((int)dst,*(void **)(arg4 + 0x18));
            ExceptionList = local_14;
            return pvVar3;
          }
          crt_cxx_calc_catch_addr(*(int *)((int)arg1 + 0x18),(int *)(arg4 + 8));
          pvVar3 = (void *)crt_cxx_copy_ctor((int)dst,*(void **)(arg4 + 0x18));
          ExceptionList = local_14;
          return pvVar3;
        }
      }
    }
    else {
      ExceptionList = &local_14;
      bVar1 = crt_is_valid_read_ptr(*(void **)((int)arg1 + 0x18),1);
      if ((CONCAT31(extraout_var_01,bVar1) != 0) &&
         (bVar1 = crt_is_valid_write_ptr(dst,1), CONCAT31(extraout_var_02,bVar1) != 0)) {
        pvVar3 = crt_memmove(dst,*(void **)((int)arg1 + 0x18),*(size_t *)(arg4 + 0x14));
        if (*(int *)(arg4 + 0x14) != 4) {
          ExceptionList = local_14;
          return pvVar3;
        }
        iVar2 = *dst;
        if (iVar2 == 0) {
          ExceptionList = local_14;
          return (void *)0x0;
        }
        goto LAB_00469c3c;
      }
    }
  }
  else {
    ExceptionList = &local_14;
    bVar1 = crt_is_valid_read_ptr(*(void **)((int)arg1 + 0x18),1);
    if ((CONCAT31(extraout_var,bVar1) != 0) &&
       (bVar1 = crt_is_valid_write_ptr(dst,1), CONCAT31(extraout_var_00,bVar1) != 0)) {
      iVar2 = *(int *)((int)arg1 + 0x18);
      *dst = iVar2;
LAB_00469c3c:
      pvVar3 = (void *)crt_cxx_calc_catch_addr(iVar2,(int *)(arg4 + 8));
      *dst = (int)pvVar3;
      ExceptionList = local_14;
      return pvVar3;
    }
  }
  crt_invalid_parameter_noinfo_noreturn();
  ExceptionList = local_14;
  return extraout_EAX;
}



/* crt_cxx_adjust_pointer @ 00469d72 */

/* [binja] void* sub_469d72(void* arg1) */

void * __cdecl crt_cxx_adjust_pointer(void *arg1)

{
  void *arg2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00470008;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  if ((arg1 != (void *)0x0) &&
     (arg2 = *(void **)(*(int *)((int)arg1 + 0x1c) + 4), arg2 != (void *)0x0)) {
    local_8 = 0;
    ExceptionList = &local_14;
    arg1 = (void *)crt_cxx_copy_ctor(*(int *)((int)arg1 + 0x18),arg2);
  }
  ExceptionList = local_14;
  return arg1;
}



/* crt_cxx_calc_catch_addr @ 00469dd9 */

int __cdecl crt_cxx_calc_catch_addr(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_2[1];
  iVar2 = *param_2 + param_1;
  if (-1 < iVar1) {
    iVar2 = iVar2 + *(int *)(*(int *)(iVar1 + param_1) + param_2[2]) + iVar1;
  }
  return iVar2;
}



/* __CallSettingFrame@12 @ 00469e00 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* Library Function - Single Match
    __CallSettingFrame@12
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  
  pcVar1 = (code *)__NLG_Notify1(param_3);
  (*pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  __NLG_Notify1(param_3);
  return;
}



/* FUN_00469e4c @ 00469e4c */

uint __thiscall FUN_00469e4c(void *this,uint param_1,uint param_2)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined4 local_8;
  
  local_8 = CONCAT22((short)((uint)this >> 0x10),in_FPUControlWord);
  uVar1 = FUN_00469e97(local_8);
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  FUN_00469f29(uVar1);
  return uVar1;
}



/* FUN_00469e81 @ 00469e81 */

void __thiscall FUN_00469e81(void *this,uint param_1,uint param_2)

{
  FUN_00469e4c(this,param_1,param_2 & 0xfff7ffff);
  return;
}



/* FUN_00469e97 @ 00469e97 */

uint __cdecl FUN_00469e97(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((param_1 & 1) != 0) {
    uVar1 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    uVar1 = uVar1 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    uVar1 = uVar1 | 1;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x80000;
  }
  uVar2 = param_1 & 0xc00;
  if (uVar2 != 0) {
    if (uVar2 == 0x400) {
      uVar1 = uVar1 | 0x100;
    }
    else if (uVar2 == 0x800) {
      uVar1 = uVar1 | 0x200;
    }
    else if (uVar2 == 0xc00) {
      uVar1 = uVar1 | 0x300;
    }
  }
  if ((param_1 & 0x300) == 0) {
    uVar1 = uVar1 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    uVar1 = uVar1 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    uVar1 = uVar1 | 0x40000;
  }
  return uVar1;
}



/* FUN_00469f29 @ 00469f29 */

uint __cdecl FUN_00469f29(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (uint)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = param_1 & 0x300;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
    else if (uVar2 == 0x200) {
      uVar1 = uVar1 | 0x800;
    }
    else if (uVar2 == 0x300) {
      uVar1 = uVar1 | 0xc00;
    }
  }
  if ((param_1 & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}



/* FUN_00469fb2 @ 00469fb2 */

/* [binja] int32_t sub_469fb2(int32_t arg1, int32_t arg2) */

int __cdecl FUN_00469fb2(int arg1,int arg2)

{
  int *piVar1;
  int iVar2;
  
  if ((*(uint *)(arg1 + (arg2 / 0x20) * 4) & ~(-1 << (0x1fU - (char)(arg2 % 0x20) & 0x1f))) != 0) {
    return 0;
  }
  iVar2 = arg2 / 0x20 + 1;
  if (iVar2 < 3) {
    piVar1 = (int *)(arg1 + iVar2 * 4);
    do {
      if (*piVar1 != 0) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 3);
  }
  return 1;
}



/* FUN_00469ffb @ 00469ffb */

/* [binja] int32_t sub_469ffb(int32_t arg1, int32_t arg2) */

int __cdecl FUN_00469ffb(int arg1,int arg2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  
  puVar3 = (uint *)(arg1 + (arg2 / 0x20) * 4);
  iVar1 = crt_add_u32_carry(*puVar3,1 << (0x1fU - (char)(arg2 % 0x20) & 0x1f),puVar3);
  iVar2 = arg2 / 0x20 + -1;
  if (-1 < iVar2) {
    puVar3 = (uint *)(arg1 + iVar2 * 4);
    do {
      if (iVar1 == 0) {
        return 0;
      }
      iVar1 = crt_add_u32_carry(*puVar3,1,puVar3);
      iVar2 = iVar2 + -1;
      puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
  }
  return iVar1;
}



/* crt_cxx_type_info_match @ 0046a051 */

/* [binja] int32_t sub_46a051(int32_t arg1, int32_t* arg2) */

int __cdecl crt_cxx_type_info_match(int arg1,int *arg2)

{
  uint *puVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_8;
  
  local_8 = 0;
  puVar1 = (uint *)(arg1 + ((int)arg2 / 0x20) * 4);
  bVar3 = 0x1f - (char)((int)arg2 % 0x20);
  if (((*puVar1 & 1 << (bVar3 & 0x1f)) != 0) &&
     (iVar2 = FUN_00469fb2(arg1,(int)arg2 + 1), iVar2 == 0)) {
    local_8 = FUN_00469ffb(arg1,(int)arg2 + -1);
  }
  *puVar1 = *puVar1 & -1 << (bVar3 & 0x1f);
  iVar2 = (int)arg2 / 0x20 + 1;
  if (iVar2 < 3) {
    puVar5 = (undefined4 *)(arg1 + iVar2 * 4);
    for (iVar4 = 3 - iVar2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  return local_8;
}



/* crt_cxx_type_info_copy @ 0046a0dd */

/* [binja] int32_t* sub_46a0dd(int32_t arg1, int32_t* arg2) */

int * __cdecl crt_cxx_type_info_copy(int arg1,int *arg2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = arg1 - (int)arg2;
  iVar2 = 3;
  do {
    *(int *)(iVar1 + (int)arg2) = *arg2;
    arg2 = arg2 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return arg2;
}



/* crt_cxx_type_info_clear @ 0046a0f8 */

/* [binja] void sub_46a0f8(int32_t* arg1) */

void __cdecl crt_cxx_type_info_clear(int *arg1)

{
  *arg1 = 0;
  arg1[1] = 0;
  arg1[2] = 0;
  return;
}



/* crt_cxx_type_info_is_empty @ 0046a104 */

/* [binja] int32_t sub_46a104(int32_t* arg1) */

int __cdecl crt_cxx_type_info_is_empty(int *arg1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*arg1 != 0) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    arg1 = arg1 + 1;
  } while (iVar1 < 3);
  return 1;
}



/* crt_cxx_type_info_set @ 0046a11f */

/* [binja] int32_t* sub_46a11f(int32_t* arg1, int32_t arg2) */

int * __cdecl crt_cxx_type_info_set(int *arg1,int arg2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  int local_8;
  
  local_8 = 3;
  iVar2 = arg2 / 0x20;
  iVar6 = arg2 % 0x20;
  arg2 = 0;
  bVar4 = (byte)iVar6;
  puVar7 = (uint *)arg1;
  do {
    uVar1 = *puVar7;
    *puVar7 = uVar1 >> (bVar4 & 0x1f) | arg2;
    puVar7 = puVar7 + 1;
    arg2 = (uVar1 & ~(-1 << (bVar4 & 0x1f))) << (0x20 - bVar4 & 0x1f);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  iVar6 = 2;
  iVar5 = 8;
  do {
    if (iVar6 < iVar2) {
      *(undefined4 *)(iVar5 + (int)arg1) = 0;
      piVar3 = arg1;
    }
    else {
      piVar3 = *(int **)(iVar5 + iVar2 * -4 + (int)arg1);
      *(int **)(iVar5 + (int)arg1) = piVar3;
    }
    iVar6 = iVar6 + -1;
    iVar5 = iVar5 + -4;
  } while (-1 < iVar5);
  return piVar3;
}



/* crt_cxx_try_catch_block @ 0046a1ac */

/* [binja] int32_t sub_46a1ac(int16_t* arg1, int32_t* arg2, int32_t* arg3) */

int __cdecl crt_cxx_try_catch_block(short *arg1,int *arg2,int *arg3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_1c [3];
  uint local_10;
  int local_c;
  int local_8;
  
  uVar1 = arg1[5];
  local_10 = *(uint *)(arg1 + 3);
  local_c = *(int *)(arg1 + 1);
  uVar3 = uVar1 & 0x7fff;
  iVar4 = uVar3 - 0x3fff;
  local_8 = (uint)(ushort)*arg1 << 0x10;
  if (iVar4 == -0x3fff) {
    iVar4 = 0;
    iVar2 = crt_cxx_type_info_is_empty((int *)&local_10);
    if (iVar2 != 0) {
LAB_0046a2d8:
      iVar2 = 0;
      goto LAB_0046a2da;
    }
    crt_cxx_type_info_clear((int *)&local_10);
  }
  else {
    crt_cxx_type_info_copy((int)local_1c,(int *)&local_10);
    iVar2 = crt_cxx_type_info_match((int)&local_10,(int *)arg3[2]);
    if (iVar2 != 0) {
      iVar4 = uVar3 - 0x3ffe;
    }
    iVar2 = arg3[1];
    if (iVar4 < iVar2 - arg3[2]) {
      crt_cxx_type_info_clear((int *)&local_10);
    }
    else {
      if (iVar2 < iVar4) {
        if (*arg3 <= iVar4) {
          crt_cxx_type_info_clear((int *)&local_10);
          local_10 = local_10 | 0x80000000;
          crt_cxx_type_info_set((int *)&local_10,arg3[3]);
          iVar4 = arg3[5] + *arg3;
          iVar2 = 1;
          goto LAB_0046a2da;
        }
        local_10 = local_10 & 0x7fffffff;
        iVar4 = arg3[5] + iVar4;
        crt_cxx_type_info_set((int *)&local_10,arg3[3]);
        goto LAB_0046a2d8;
      }
      crt_cxx_type_info_copy((int)&local_10,local_1c);
      crt_cxx_type_info_set((int *)&local_10,iVar2 - iVar4);
      crt_cxx_type_info_match((int)&local_10,(int *)arg3[2]);
      crt_cxx_type_info_set((int *)&local_10,arg3[3] + 1);
    }
  }
  iVar4 = 0;
  iVar2 = 2;
LAB_0046a2da:
  local_10 = iVar4 << (0x1fU - (char)arg3[3] & 0x1f) | -(uint)((uVar1 & 0x8000) != 0) & 0x80000000 |
             local_10;
  if (arg3[4] == 0x40) {
    arg2[1] = local_10;
    *arg2 = local_c;
  }
  else if (arg3[4] == 0x20) {
    *arg2 = local_10;
  }
  return iVar2;
}



/* crt_fp_classify @ 0046a318 */

/* [binja] int32_t sub_46a318(int16_t* arg1, int32_t* arg2) */

int __cdecl crt_fp_classify(short *arg1,int *arg2)

{
  int iVar1;
  
  iVar1 = crt_cxx_try_catch_block(arg1,arg2,(int *)&DAT_0047dce0);
  return iVar1;
}



/* crt_cxx_type_info_destroy @ 0046a32e */

/* [binja] int32_t sub_46a32e(int16_t* arg1, int32_t* arg2) */

int __cdecl crt_cxx_type_info_destroy(short *arg1,int *arg2)

{
  int iVar1;
  
  iVar1 = crt_cxx_try_catch_block(arg1,arg2,(int *)&DAT_0047dcf8);
  return iVar1;
}



/* crt_fp_encode_single @ 0046a344 */

void __thiscall crt_fp_encode_single(void *this,uint *param_1,byte *param_2)

{
  int in_stack_fffffff0;
  
  crt_fp_parse(this,&stack0xfffffff0,(ushort *)&param_2,(int *)param_2,(byte *)0x0,0,0,0,
               in_stack_fffffff0);
  crt_fp_classify((short *)&stack0xfffffff0,(int *)param_1);
  return;
}



/* crt_fp_encode_double @ 0046a371 */

void __thiscall crt_fp_encode_double(void *this,uint *param_1,byte *param_2)

{
  int in_stack_fffffff0;
  
  crt_fp_parse(this,&stack0xfffffff0,(ushort *)&param_2,(int *)param_2,(byte *)0x0,0,0,0,
               in_stack_fffffff0);
  crt_cxx_type_info_destroy((short *)&stack0xfffffff0,(int *)param_1);
  return;
}



/* crt_fp_round_digits @ 0046a39e */

/* CRT: round float digits and adjust exponent for printf formatting */

void __cdecl crt_fp_round_digits(char *dst,int precision,int *fp_info)

{
  char *_Str;
  char *dst_00;
  char *pcVar1;
  size_t sVar2;
  char *pcVar3;
  char cVar4;
  
  dst_00 = dst;
  pcVar3 = (char *)fp_info[3];
  _Str = dst + 1;
  *dst = '0';
  pcVar1 = _Str;
  if (0 < precision) {
    dst = (char *)precision;
    precision = 0;
    do {
      cVar4 = *pcVar3;
      if (cVar4 == '\0') {
        cVar4 = '0';
      }
      else {
        pcVar3 = pcVar3 + 1;
      }
      *pcVar1 = cVar4;
      pcVar1 = pcVar1 + 1;
      dst = dst + -1;
    } while (dst != (char *)0x0);
  }
  *pcVar1 = '\0';
  if ((-1 < precision) && ('4' < *pcVar3)) {
    while (pcVar1 = pcVar1 + -1, *pcVar1 == '9') {
      *pcVar1 = '0';
    }
    *pcVar1 = *pcVar1 + '\x01';
  }
  if (*dst_00 == '1') {
    fp_info[1] = fp_info[1] + 1;
  }
  else {
    sVar2 = _strlen(_Str);
    crt_memmove(dst_00,_Str,sVar2 + 1);
  }
  return;
}



/* crt_fp_to_string @ 0046a415 */

/* formats a floating-point value for printf-style conversion */

int * __cdecl crt_fp_to_string(double value,int *out,uint *digits)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  undefined4 in_stack_ffffffbc;
  undefined2 uVar4;
  short local_2c;
  char local_2a;
  char local_28 [24];
  uint local_10;
  uint uStack_c;
  undefined2 uStack_8;
  
  uVar4 = (undefined2)((uint)in_stack_ffffffbc >> 0x10);
  crt_fp_decode_format((int *)&local_10,(int *)&value);
  iVar3 = crt_format_output(local_10,uStack_c,CONCAT22(uVar4,uStack_8),0x11,0,&local_2c);
  puVar2 = digits;
  piVar1 = out;
  out[2] = iVar3;
  *out = (int)local_2a;
  out[1] = (int)local_2c;
  crt_strcpy((char *)digits,local_28);
  piVar1[3] = (int)puVar2;
  return piVar1;
}



/* crt_fp_decode_format @ 0046a471 */

/* [binja] int32_t* sub_46a471(int32_t* arg1, int32_t* arg2) */

int * __cdecl crt_fp_decode_format(int *arg1,int *arg2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint local_8;
  
  uVar1 = *(ushort *)((int)arg2 + 6);
  uVar3 = (uVar1 & 0x7ff0) >> 4;
  uVar2 = *arg2;
  local_8 = 0x80000000;
  if (uVar3 == 0) {
    if (((arg2[1] & 0xfffffU) == 0) && (uVar2 == 0)) {
      arg1[1] = 0;
      *arg1 = 0;
      *(undefined2 *)(arg1 + 2) = 0;
      return arg1;
    }
    iVar4 = 0x3c01;
    local_8 = 0;
  }
  else if (uVar3 == 0x7ff) {
    iVar4 = 0x7fff;
  }
  else {
    iVar4 = uVar3 + 0x3c00;
  }
  local_8 = uVar2 >> 0x15 | (arg2[1] & 0xfffffU) << 0xb | local_8;
  arg1[1] = local_8;
  *arg1 = uVar2 << 0xb;
  while ((local_8 & 0x80000000) == 0) {
    local_8 = (uint)*arg1 >> 0x1f | local_8 * 2;
    *arg1 = *arg1 * 2;
    arg1[1] = local_8;
    iVar4 = iVar4 + 0xffff;
  }
  *(ushort *)(arg1 + 2) = uVar1 & 0x8000 | (ushort)iVar4;
  return arg1;
}



/* _memset @ 0046a530 */

/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}



/* crt_memmove @ 0046a590 */

/* CRT: copy memory with overlap handling */

void * __cdecl crt_memmove(void *dst,void *src,size_t size)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if ((src < dst) && (dst < (void *)(size + (int)src))) {
    puVar3 = (undefined4 *)((size - 4) + (int)src);
    puVar4 = (undefined4 *)((size - 4) + (int)dst);
    if (((uint)puVar4 & 3) == 0) {
      uVar1 = size >> 2;
      uVar2 = size & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
        switch(uVar2) {
        case 0:
          return dst;
        case 2:
          goto switchD_0046a747_caseD_2;
        case 3:
          goto switchD_0046a747_caseD_3;
        }
        goto switchD_0046a747_caseD_1;
      }
    }
    else {
      switch(size) {
      case 0:
        goto switchD_0046a747_caseD_0;
      case 1:
        goto switchD_0046a747_caseD_1;
      case 2:
        goto switchD_0046a747_caseD_2;
      case 3:
        goto switchD_0046a747_caseD_3;
      default:
        uVar1 = size - ((uint)puVar4 & 3);
        switch((uint)puVar4 & 3) {
        case 1:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          puVar3 = (undefined4 *)((int)puVar3 + -1);
          uVar1 = uVar1 >> 2;
          puVar4 = (undefined4 *)((int)puVar4 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_0046a747_caseD_2;
            case 3:
              goto switchD_0046a747_caseD_3;
            }
            goto switchD_0046a747_caseD_1;
          }
          break;
        case 2:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          puVar3 = (undefined4 *)((int)puVar3 + -2);
          puVar4 = (undefined4 *)((int)puVar4 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_0046a747_caseD_2;
            case 3:
              goto switchD_0046a747_caseD_3;
            }
            goto switchD_0046a747_caseD_1;
          }
          break;
        case 3:
          uVar2 = uVar1 & 3;
          *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
          *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + -3);
          puVar4 = (undefined4 *)((int)puVar4 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar4 = *puVar3;
              puVar3 = puVar3 + -1;
              puVar4 = puVar4 + -1;
            }
            switch(uVar2) {
            case 0:
              return dst;
            case 2:
              goto switchD_0046a747_caseD_2;
            case 3:
              goto switchD_0046a747_caseD_3;
            }
            goto switchD_0046a747_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar4[7 - uVar1] = puVar3[7 - uVar1];
    case 6:
      puVar4[6 - uVar1] = puVar3[6 - uVar1];
    case 5:
      puVar4[5 - uVar1] = puVar3[5 - uVar1];
    case 4:
      puVar4[4 - uVar1] = puVar3[4 - uVar1];
    case 3:
      puVar4[3 - uVar1] = puVar3[3 - uVar1];
    case 2:
      puVar4[2 - uVar1] = puVar3[2 - uVar1];
    case 1:
      puVar4[1 - uVar1] = puVar3[1 - uVar1];
      puVar3 = puVar3 + -uVar1;
      puVar4 = puVar4 + -uVar1;
    }
    switch(uVar2) {
    case 1:
switchD_0046a747_caseD_1:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      return dst;
    case 2:
switchD_0046a747_caseD_2:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      return dst;
    case 3:
switchD_0046a747_caseD_3:
      *(undefined1 *)((int)puVar4 + 3) = *(undefined1 *)((int)puVar3 + 3);
      *(undefined1 *)((int)puVar4 + 2) = *(undefined1 *)((int)puVar3 + 2);
      *(undefined1 *)((int)puVar4 + 1) = *(undefined1 *)((int)puVar3 + 1);
      return dst;
    }
switchD_0046a747_caseD_0:
    return dst;
  }
  puVar3 = dst;
  if (((uint)dst & 3) == 0) {
    uVar1 = size >> 2;
    uVar2 = size & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar3 = *(undefined4 *)src;
        src = (undefined4 *)((int)src + 4);
        puVar3 = puVar3 + 1;
      }
      switch(uVar2) {
      case 0:
        return dst;
      case 2:
        goto switchD_0046a5c5_caseD_2;
      case 3:
        goto switchD_0046a5c5_caseD_3;
      }
      goto switchD_0046a5c5_caseD_1;
    }
  }
  else {
    switch(size) {
    case 0:
      goto switchD_0046a5c5_caseD_0;
    case 1:
      goto switchD_0046a5c5_caseD_1;
    case 2:
      goto switchD_0046a5c5_caseD_2;
    case 3:
      goto switchD_0046a5c5_caseD_3;
    default:
      uVar1 = (size - 4) + ((uint)dst & 3);
      switch((uint)dst & 3) {
      case 1:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 2) = *(undefined1 *)((int)src + 2);
        src = (void *)((int)src + 3);
        puVar3 = (undefined4 *)((int)dst + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_0046a5c5_caseD_2;
          case 3:
            goto switchD_0046a5c5_caseD_3;
          }
          goto switchD_0046a5c5_caseD_1;
        }
        break;
      case 2:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)dst + 1) = *(undefined1 *)((int)src + 1);
        src = (void *)((int)src + 2);
        puVar3 = (undefined4 *)((int)dst + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_0046a5c5_caseD_2;
          case 3:
            goto switchD_0046a5c5_caseD_3;
          }
          goto switchD_0046a5c5_caseD_1;
        }
        break;
      case 3:
        uVar2 = uVar1 & 3;
        *(undefined1 *)dst = *(undefined1 *)src;
        src = (void *)((int)src + 1);
        uVar1 = uVar1 >> 2;
        puVar3 = (undefined4 *)((int)dst + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar3 = *(undefined4 *)src;
            src = (undefined4 *)((int)src + 4);
            puVar3 = puVar3 + 1;
          }
          switch(uVar2) {
          case 0:
            return dst;
          case 2:
            goto switchD_0046a5c5_caseD_2;
          case 3:
            goto switchD_0046a5c5_caseD_3;
          }
          goto switchD_0046a5c5_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar3[uVar1 - 7] = *(undefined4 *)((int)src + (uVar1 - 7) * 4);
  case 6:
    puVar3[uVar1 - 6] = *(undefined4 *)((int)src + (uVar1 - 6) * 4);
  case 5:
    puVar3[uVar1 - 5] = *(undefined4 *)((int)src + (uVar1 - 5) * 4);
  case 4:
    puVar3[uVar1 - 4] = *(undefined4 *)((int)src + (uVar1 - 4) * 4);
  case 3:
    puVar3[uVar1 - 3] = *(undefined4 *)((int)src + (uVar1 - 3) * 4);
  case 2:
    puVar3[uVar1 - 2] = *(undefined4 *)((int)src + (uVar1 - 2) * 4);
  case 1:
    puVar3[uVar1 - 1] = *(undefined4 *)((int)src + (uVar1 - 1) * 4);
    src = (void *)((int)src + uVar1 * 4);
    puVar3 = puVar3 + uVar1;
  }
  switch(uVar2) {
  case 1:
switchD_0046a5c5_caseD_1:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    return dst;
  case 2:
switchD_0046a5c5_caseD_2:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)src + 1);
    return dst;
  case 3:
switchD_0046a5c5_caseD_3:
    *(undefined1 *)puVar3 = *(undefined1 *)src;
    *(undefined1 *)((int)puVar3 + 1) = *(undefined1 *)((int)src + 1);
    *(undefined1 *)((int)puVar3 + 2) = *(undefined1 *)((int)src + 2);
    return dst;
  }
switchD_0046a5c5_caseD_0:
  return dst;
}



/* FUN_0046a8c5 @ 0046a8c5 */

/* [binja] int32_t sub_46a8c5() */

int FUN_0046a8c5(void)

{
  int extraout_EAX;
  
  __amsg_exit(2);
  return extraout_EAX;
}



/* crt_cxx_throw_exception @ 0046a8ce */

BOOL __cdecl
crt_cxx_throw_exception(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
            int param_7)

{
  undefined1 *puVar1;
  WINBOOL WVar2;
  int iVar3;
  WORD local_20 [2];
  undefined1 *local_1c;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_00470018;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  local_1c = &stack0xffffffc8;
  iVar3 = crt_sbh_threshold;
  ExceptionList = &local_14;
  puVar1 = &stack0xffffffc8;
  if (crt_sbh_threshold == 0) {
    ExceptionList = &local_14;
    WVar2 = GetStringTypeW(1,L"",1,local_20);
    iVar3 = 1;
    puVar1 = local_1c;
    if (WVar2 == 0) {
      WVar2 = GetStringTypeA(0,1,&crt_winver,1,local_20);
      if (WVar2 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      iVar3 = 2;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  crt_sbh_threshold = iVar3;
  if (crt_sbh_threshold != 2) {
    if (crt_sbh_threshold == 1) {
      if (param_5 == 0) {
        param_5 = crt_acp_codepage;
      }
      iVar3 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,
                                  (LPWSTR)0x0,0);
      if (iVar3 != 0) {
        local_8 = 0;
        crt_chkstk();
        local_1c = &stack0xffffffc8;
        _memset(&stack0xffffffc8,0,iVar3 * 2);
        local_8 = 0xffffffff;
        if ((&stack0x00000000 != (undefined1 *)0x38) &&
           (iVar3 = MultiByteToWideChar(param_5,1,param_2,param_3,(LPWSTR)&stack0xffffffc8,iVar3),
           iVar3 != 0)) {
          WVar2 = GetStringTypeW(param_1,(LPCWCH)&stack0xffffffc8,iVar3,param_4);
          ExceptionList = local_14;
          return WVar2;
        }
      }
    }
    ExceptionList = local_14;
    return 0;
  }
  if (param_6 == 0) {
    param_6 = crt_locale_id;
  }
  WVar2 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
  ExceptionList = local_14;
  return WVar2;
}



/* crt_get_file_handle_count @ 0046aa98 */

uint crt_get_file_handle_count(void)

{
  void **ppvVar1;
  void **ppvVar2;
  void ***pppvVar3;
  uint fd;
  int local_8;
  int local_4;
  
  fd = 0xffffffff;
  crt_lock(0x12);
  local_8 = 0;
  local_4 = 0;
  pppvVar3 = &crt_pioinfo_table;
  while (ppvVar2 = *pppvVar3, ppvVar1 = ppvVar2, ppvVar2 != (void **)0x0) {
    for (; ppvVar2 < ppvVar1 + 0x120; ppvVar2 = ppvVar2 + 9) {
      if (((uint)ppvVar2[1] & 1) == 0) {
        if (ppvVar2[2] == (void *)0x0) {
          crt_lock(0x11);
          if (ppvVar2[2] == (void *)0x0) {
            InitializeCriticalSection((LPCRITICAL_SECTION)(ppvVar2 + 3));
            ppvVar2[2] = (void *)((int)ppvVar2[2] + 1);
          }
          crt_unlock(0x11);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)(ppvVar2 + 3));
        if (((uint)ppvVar2[1] & 1) == 0) {
          *ppvVar2 = (void *)0xffffffff;
          fd = ((int)ppvVar2 - (int)*pppvVar3) / 0x24 + local_4;
          if (fd != 0xffffffff) goto LAB_0046abaa;
          break;
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(ppvVar2 + 3));
      }
      ppvVar1 = *pppvVar3;
    }
    local_4 = local_4 + 0x20;
    pppvVar3 = pppvVar3 + 1;
    local_8 = local_8 + 1;
    if (0x4da4bf < (int)pppvVar3) goto LAB_0046abaa;
  }
  ppvVar2 = _malloc(0x480);
  if (ppvVar2 != (void **)0x0) {
    crt_nhandle = crt_nhandle + 0x20;
    (&crt_pioinfo_table)[local_8] = ppvVar2;
    ppvVar1 = ppvVar2;
    for (; ppvVar2 < ppvVar1 + 0x120; ppvVar2 = ppvVar2 + 9) {
      *(undefined1 *)(ppvVar2 + 1) = 0;
      *ppvVar2 = (void *)0xffffffff;
      ppvVar2[2] = (void *)0x0;
      *(undefined1 *)((int)ppvVar2 + 5) = 10;
      ppvVar1 = (&crt_pioinfo_table)[local_8];
    }
    fd = local_8 << 5;
    crt_lock_fh(fd);
  }
LAB_0046abaa:
  crt_unlock(0x12);
  return fd;
}



/* crt_set_osfhandle @ 0046abbb */

/* [binja] int32_t sub_46abbb(int32_t arg1, HANDLE arg2) */

int __cdecl crt_set_osfhandle(int arg1,HANDLE arg2)

{
  int *piVar1;
  uint *puVar2;
  DWORD nStdHandle;
  
  if ((uint)arg1 < (uint)crt_nhandle) {
    if ((&crt_pioinfo_table)[arg1 >> 5][(arg1 & 0x1fU) * 9] == (void *)0xffffffff) {
      if (crt_os_platform_type == 1) {
        if (arg1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (arg1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (arg1 != 2) goto LAB_0046ac14;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,arg2);
      }
LAB_0046ac14:
      (&crt_pioinfo_table)[arg1 >> 5][(arg1 & 0x1fU) * 9] = arg2;
      return 0;
    }
  }
  piVar1 = crt_errno_ptr();
  *piVar1 = 9;
  puVar2 = crt_doserrno_ptr();
  *puVar2 = 0;
  return -1;
}



/* crt_get_osfhandle @ 0046ac37 */

/* [binja] int32_t sub_46ac37(int32_t arg1) */

int __cdecl crt_get_osfhandle(int arg1)

{
  void **ppvVar1;
  int *piVar2;
  uint *puVar3;
  DWORD nStdHandle;
  
  if ((uint)arg1 < (uint)crt_nhandle) {
    ppvVar1 = (&crt_pioinfo_table)[arg1 >> 5] + (arg1 & 0x1fU) * 9;
    if ((((uint)ppvVar1[1] & 1) != 0) && (*ppvVar1 != (void *)0xffffffff)) {
      if (crt_os_platform_type == 1) {
        if (arg1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (arg1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (arg1 != 2) goto LAB_0046ac93;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)0x0);
      }
LAB_0046ac93:
      (&crt_pioinfo_table)[arg1 >> 5][(arg1 & 0x1fU) * 9] = (void *)0xffffffff;
      return 0;
    }
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 9;
  puVar3 = crt_doserrno_ptr();
  *puVar3 = 0;
  return -1;
}



/* crt_get_osfhandle @ 0046acb6 */

/* CRT: map file descriptor to OS handle */

void * __cdecl crt_get_osfhandle(int fd)

{
  int *piVar1;
  uint *puVar2;
  
  if (((uint)fd < (uint)crt_nhandle) &&
     (((uint)(&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9 + 1] & 1) != 0)) {
    return (&crt_pioinfo_table)[fd >> 5][(fd & 0x1fU) * 9];
  }
  piVar1 = crt_errno_ptr();
  *piVar1 = 9;
  puVar2 = crt_doserrno_ptr();
  *puVar2 = 0;
  return (void *)0xffffffff;
}



/* crt_lock_fh @ 0046acf8 */

/* lock CRT file handle entry */

void __cdecl crt_lock_fh(uint fd)

{
  void **ppvVar1;
  uint uVar2;
  
  uVar2 = fd & 0x1f;
  ppvVar1 = (&crt_pioinfo_table)[(int)fd >> 5];
  if (ppvVar1[uVar2 * 9 + 2] == (void *)0x0) {
    crt_lock(0x11);
    if (ppvVar1[uVar2 * 9 + 2] == (void *)0x0) {
      InitializeCriticalSection((LPCRITICAL_SECTION)(ppvVar1 + uVar2 * 9 + 3));
      ppvVar1[uVar2 * 9 + 2] = (void *)((int)ppvVar1[uVar2 * 9 + 2] + 1);
    }
    crt_unlock(0x11);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)((&crt_pioinfo_table)[(int)fd >> 5] + uVar2 * 9 + 3));
  return;
}



/* crt_unlock_fh @ 0046ad57 */

/* unlock CRT file handle entry */

void __cdecl crt_unlock_fh(uint fd)

{
  LeaveCriticalSection
            ((LPCRITICAL_SECTION)((&crt_pioinfo_table)[(int)fd >> 5] + (fd & 0x1f) * 9 + 3));
  return;
}



/* crt_file_buffer_init @ 0046ad79 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CRT: allocate/init FILE buffer (4KB or fallback small buffer) */

void __cdecl crt_file_buffer_init(undefined4 *param_1)

{
  void *pvVar1;
  
  crt_file_handle_flags = crt_file_handle_flags + 1;
  pvVar1 = _malloc(0x1000);
  param_1[2] = pvVar1;
  if (pvVar1 == (void *)0x0) {
    param_1[3] = param_1[3] | 4;
    param_1[2] = param_1 + 5;
    param_1[6] = 2;
  }
  else {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return;
}



/* crt_sopen @ 0046adbd */

/* CRT: open file with share mode, wraps CreateFile */

int __cdecl crt_sopen(char *filename,int oflag,int shflag,int pmode)

{
  void **ppvVar1;
  uint uVar2;
  uint fd;
  int *piVar3;
  uint *puVar4;
  HANDLE hFile;
  DWORD DVar5;
  int iVar6;
  long lVar7;
  bool bVar8;
  _SECURITY_ATTRIBUTES local_20;
  DWORD local_14;
  DWORD local_10;
  DWORD local_c;
  byte local_5;
  
  bVar8 = (oflag & 0x80U) == 0;
  local_20.nLength = 0xc;
  local_20.lpSecurityDescriptor = (LPVOID)0x0;
  if (bVar8) {
    local_5 = 0;
  }
  else {
    local_5 = 0x10;
  }
  local_20.bInheritHandle = (WINBOOL)bVar8;
  if (((oflag & 0x8000U) == 0) && (((oflag & 0x4000U) != 0 || (DAT_004d9cd8 != 0x8000)))) {
    local_5 = local_5 | 0x80;
  }
  uVar2 = oflag & 3;
  if (uVar2 == 0) {
    local_10 = 0x80000000;
  }
  else if (uVar2 == 1) {
    local_10 = 0x40000000;
  }
  else {
    if (uVar2 != 2) goto LAB_0046aec1;
    local_10 = 0xc0000000;
  }
  if (shflag == 0x10) {
    local_14 = 0;
  }
  else if (shflag == 0x20) {
    local_14 = 1;
  }
  else if (shflag == 0x30) {
    local_14 = 2;
  }
  else {
    if (shflag != 0x40) goto LAB_0046aec1;
    local_14 = 3;
  }
  uVar2 = oflag & 0x700;
  if (uVar2 < 0x401) {
    if ((uVar2 == 0x400) || (uVar2 == 0)) {
      local_c = 3;
    }
    else if (uVar2 == 0x100) {
      local_c = 4;
    }
    else {
      if (uVar2 == 0x200) goto LAB_0046aedb;
      if (uVar2 != 0x300) goto LAB_0046aec1;
      local_c = 2;
    }
  }
  else {
    if (uVar2 != 0x500) {
      if (uVar2 == 0x600) {
LAB_0046aedb:
        local_c = 5;
        goto LAB_0046aeeb;
      }
      if (uVar2 != 0x700) {
LAB_0046aec1:
        piVar3 = crt_errno_ptr();
        *piVar3 = 0x16;
        puVar4 = crt_doserrno_ptr();
        *puVar4 = 0;
        return -1;
      }
    }
    local_c = 1;
  }
LAB_0046aeeb:
  uVar2 = 0x80;
  if (((oflag & 0x100U) != 0) && ((~DAT_004d9980 & pmode & 0x80) == 0)) {
    uVar2 = 1;
  }
  if ((oflag & 0x40U) != 0) {
    uVar2 = uVar2 | 0x4000000;
    local_10 = CONCAT13(local_10._3_1_,0x10000);
  }
  if ((oflag & 0x1000U) != 0) {
    uVar2 = uVar2 | 0x100;
  }
  if ((oflag & 0x20U) == 0) {
    if ((oflag & 0x10U) != 0) {
      uVar2 = uVar2 | 0x10000000;
    }
  }
  else {
    uVar2 = uVar2 | 0x8000000;
  }
  fd = crt_get_file_handle_count();
  if (fd == 0xffffffff) {
    piVar3 = crt_errno_ptr();
    *piVar3 = 0x18;
    puVar4 = crt_doserrno_ptr();
    *puVar4 = 0;
    return -1;
  }
  hFile = CreateFileA(filename,local_10,local_14,&local_20,local_c,uVar2,(HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffff) {
    DVar5 = GetFileType(hFile);
    if (DVar5 != 0) {
      if (DVar5 == 2) {
        local_5 = local_5 | 0x40;
      }
      else if (DVar5 == 3) {
        local_5 = local_5 | 8;
      }
      crt_set_osfhandle(fd,hFile);
      filename._3_1_ = local_5 & 0x48;
      *(byte *)((&crt_pioinfo_table)[(int)fd >> 5] + (fd & 0x1f) * 9 + 1) = local_5 | 1;
      if ((((local_5 & 0x48) == 0) && ((local_5 & 0x80) != 0)) && ((oflag & 2U) != 0)) {
        local_14 = crt_lseek_nolock(fd,-1,2);
        if (local_14 == 0xffffffff) {
          puVar4 = crt_doserrno_ptr();
          if (*puVar4 == 0x83) goto LAB_0046b065;
        }
        else {
          shflag = shflag & 0xffffff;
          iVar6 = crt_read_nolock(fd,(char *)((int)&shflag + 3),1);
          if ((((iVar6 != 0) || (shflag._3_1_ != '\x1a')) ||
              (iVar6 = crt_chsize(fd,local_14), iVar6 != -1)) &&
             (lVar7 = crt_lseek_nolock(fd,0,0), lVar7 != -1)) goto LAB_0046b065;
        }
        crt_close(fd);
        uVar2 = 0xffffffff;
      }
      else {
LAB_0046b065:
        uVar2 = fd;
        if ((filename._3_1_ == 0) && ((oflag & 8U) != 0)) {
          ppvVar1 = (&crt_pioinfo_table)[(int)fd >> 5] + (fd & 0x1f) * 9 + 1;
          *(byte *)ppvVar1 = *(byte *)ppvVar1 | 0x20;
        }
      }
      goto LAB_0046b07e;
    }
    CloseHandle(hFile);
  }
  DVar5 = GetLastError();
  crt_dosmaperr(DVar5);
  uVar2 = 0xffffffff;
LAB_0046b07e:
  crt_unlock_fh(fd);
  return uVar2;
}



/* crt_free_osfhandle @ 0046b08c */

byte __cdecl crt_free_osfhandle(uint param_1)

{
  if ((uint)crt_nhandle <= param_1) {
    return 0;
  }
  return *(byte *)((&crt_pioinfo_table)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) & 0x40;
}



/* crt_alloc_osfhandle @ 0046b0b5 */

int __cdecl crt_alloc_osfhandle(LPSTR param_1,WCHAR param_2)

{
  int iVar1;
  bool bVar2;
  
  InterlockedIncrement((LONG *)&crt_lock_count);
  bVar2 = crt_sbh_reserved_a != 0;
  if (bVar2) {
    InterlockedDecrement((LONG *)&crt_lock_count);
    crt_lock(0x13);
  }
  iVar1 = crt_wctomb_single(param_1,param_2);
  if (bVar2) {
    crt_unlock(0x13);
  }
  else {
    InterlockedDecrement((LONG *)&crt_lock_count);
  }
  return iVar1;
}



/* crt_wctomb_single @ 0046b10e */

int __cdecl crt_wctomb_single(LPSTR param_1,WCHAR param_2)

{
  LPSTR lpMultiByteStr;
  int iVar1;
  int *piVar2;
  
  lpMultiByteStr = param_1;
  if (param_1 == (LPSTR)0x0) {
    return 0;
  }
  if (crt_locale_id == 0) {
    if ((ushort)param_2 < 0x100) {
      *param_1 = (CHAR)param_2;
      return 1;
    }
  }
  else {
    param_1 = (LPSTR)0x0;
    iVar1 = WideCharToMultiByte(crt_acp_codepage,0x220,&param_2,1,lpMultiByteStr,crt_locale_type,(LPCCH)0x0
                                ,(LPBOOL)&param_1);
    if ((iVar1 != 0) && (param_1 == (LPSTR)0x0)) {
      return iVar1;
    }
  }
  piVar2 = crt_errno_ptr();
  *piVar2 = 0x2a;
  return -1;
}



/* __aulldiv @ 0046b180 */

/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar3 = param_1;
  uVar8 = param_4;
  uVar6 = param_2;
  uVar9 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar8 >> 1;
      uVar9 = uVar9 >> 1 | (uint)((uVar8 & 1) != 0) << 0x1f;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar6 & 1) != 0) << 0x1f;
      uVar8 = uVar5;
      uVar6 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar7,uVar3) / (ulonglong)uVar9;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar8 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar8)) ||
       ((param_2 <= uVar8 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}



/* __aullrem @ 0046b1f0 */

/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar3 = param_1;
  uVar4 = param_4;
  uVar9 = param_2;
  uVar10 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar4 >> 1;
      uVar10 = uVar10 >> 1 | (uint)((uVar4 & 1) != 0) << 0x1f;
      uVar8 = uVar9 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar9 & 1) != 0) << 0x1f;
      uVar4 = uVar5;
      uVar9 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar3) / (ulonglong)uVar10;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}



/* crt_fp_parse @ 0046b265 */

/* parses a floating-point string into an 80-bit buffer (CRT scanf helper) */

int __thiscall
crt_fp_parse(void *this,void *ctx,ushort *out,int *cursor,byte *str,int flags,int width,int prec,
            int mode)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  byte bVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  char local_60 [23];
  char local_49;
  ushort local_44;
  undefined2 uStack_42;
  undefined2 uStack_40;
  int *local_3e;
  ushort local_3a;
  int local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  byte *local_20;
  int local_1c;
  int local_18;
  int local_14;
  char *local_10;
  int local_c;
  uint local_8;
  
  local_10 = local_60;
  local_2c = 0;
  local_1c = 1;
  local_8 = 0;
  local_14 = 0;
  local_28 = 0;
  local_24 = 0;
  local_30 = 0;
  local_34 = 0;
  local_20 = (byte *)0x0;
  local_c = 0;
  local_18 = 0;
  pbVar8 = (byte *)cursor;
  while( true ) {
    bVar6 = *pbVar8;
    this = (void *)CONCAT31((int3)((uint)this >> 8),bVar6);
    if ((((bVar6 != 0x20) && (bVar6 != 9)) && (bVar6 != 10)) && (bVar6 != 0xd)) break;
    pbVar8 = pbVar8 + 1;
  }
  iVar1 = 4;
  iVar9 = 0;
  iVar5 = local_14;
LAB_0046b2bc:
  local_14 = iVar5;
  pbVar7 = pbVar8;
  iVar5 = 1;
  bVar6 = *pbVar7;
  pbVar8 = pbVar7 + 1;
  iVar2 = local_14;
  switch(iVar9) {
  case 0:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) {
LAB_0046b2d9:
      local_14 = iVar2;
      iVar9 = 3;
      goto LAB_0046b4fe;
    }
    if (bVar6 == crt_null_char) goto LAB_0046b2e8;
    if (bVar6 == 0x2b) {
      local_2c = 0;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else if (bVar6 == 0x2d) {
      local_2c = 0x8000;
      iVar9 = 2;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_0046b5d8;
    }
    goto LAB_0046b2bc;
  case 1:
    local_14 = 1;
    if (('0' < (char)bVar6) && (iVar2 = iVar5, (char)bVar6 < ':')) goto LAB_0046b2d9;
    iVar9 = iVar1;
    if (bVar6 != crt_null_char) {
      iVar9 = iVar5;
      if ((bVar6 == 0x2b) || (iVar9 = local_14, bVar6 == 0x2d)) goto LAB_0046b36d;
      iVar9 = iVar5;
      local_14 = iVar5;
      if (bVar6 != 0x30) goto LAB_0046b346;
    }
    goto LAB_0046b2bc;
  case 2:
    if (('0' < (char)bVar6) && ((char)bVar6 < ':')) goto LAB_0046b2d9;
    if (bVar6 == crt_null_char) {
LAB_0046b2e8:
      iVar9 = 5;
      iVar5 = local_14;
    }
    else {
      iVar9 = iVar5;
      pbVar7 = (byte *)cursor;
      iVar5 = local_14;
      if (bVar6 != 0x30) goto LAB_0046b5dd;
    }
    goto LAB_0046b2bc;
  case 3:
    local_14 = iVar5;
    while( true ) {
      if (crt_locale_type < 2) {
        uVar3 = (byte)crt_ctype_table[(uint)bVar6 * 2] & 4;
        this = crt_ctype_table;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = crt_isctype(this,(uint)bVar6,4);
        this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      else {
        local_c = local_c + 1;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    iVar9 = iVar1;
    iVar5 = local_14;
    if (bVar6 != crt_null_char) goto LAB_0046b45a;
    goto LAB_0046b2bc;
  case 4:
    local_14 = 1;
    local_28 = 1;
    iVar9 = iVar5;
    if (local_8 == 0) {
      while (iVar5 = local_28, iVar9 = local_14, bVar6 == 0x30) {
        local_c = local_c + -1;
        bVar6 = *pbVar8;
        pbVar8 = pbVar8 + 1;
      }
    }
    while( true ) {
      local_14 = iVar9;
      local_28 = iVar5;
      if (crt_locale_type < 2) {
        uVar3 = (byte)crt_ctype_table[(uint)bVar6 * 2] & 4;
        this = crt_ctype_table;
      }
      else {
        pbVar7 = (byte *)0x4;
        uVar3 = crt_isctype(this,(uint)bVar6,4);
        this = pbVar7;
      }
      if (uVar3 == 0) break;
      if (local_8 < 0x19) {
        local_8 = local_8 + 1;
        local_c = local_c + -1;
        pcVar4 = local_10 + 1;
        *local_10 = bVar6 - 0x30;
        local_10 = pcVar4;
      }
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
      iVar5 = local_28;
      iVar9 = local_14;
    }
LAB_0046b45a:
    iVar9 = local_14;
    if ((bVar6 == 0x2b) || (bVar6 == 0x2d)) {
LAB_0046b36d:
      local_14 = iVar9;
      iVar9 = 0xb;
      pbVar8 = pbVar8 + -1;
      iVar5 = local_14;
    }
    else {
LAB_0046b346:
      if (((char)bVar6 < 'D') ||
         (('E' < (char)bVar6 && (((char)bVar6 < 'd' || ('e' < (char)bVar6)))))) goto LAB_0046b5d8;
      iVar9 = 6;
      iVar5 = local_14;
    }
    goto LAB_0046b2bc;
  case 5:
    local_28 = iVar5;
    if (crt_locale_type < 2) {
      uVar3 = (byte)crt_ctype_table[(uint)bVar6 * 2] & 4;
      this = crt_ctype_table;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = crt_isctype(this,(uint)bVar6,4);
      this = pbVar7;
    }
    iVar9 = iVar1;
    pbVar7 = (byte *)cursor;
    if (uVar3 != 0) goto LAB_0046b4fe;
    goto LAB_0046b5dd;
  case 6:
    pbVar7 = pbVar7 + -1;
    this = pbVar7;
    cursor = (int *)pbVar7;
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      if (bVar6 == 0x2b) goto LAB_0046b533;
      if (bVar6 == 0x2d) goto LAB_0046b527;
      if (bVar6 != 0x30) goto LAB_0046b5dd;
LAB_0046b4cc:
      iVar9 = 8;
      iVar5 = local_14;
      goto LAB_0046b2bc;
    }
    break;
  case 7:
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) {
      pbVar7 = (byte *)cursor;
      if (bVar6 == 0x30) goto LAB_0046b4cc;
      goto LAB_0046b5dd;
    }
    break;
  case 8:
    local_24 = 1;
    while (bVar6 == 0x30) {
      bVar6 = *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
    if (((char)bVar6 < '1') || ('9' < (char)bVar6)) goto LAB_0046b5d8;
    break;
  case 9:
    local_24 = 1;
    pbVar7 = (byte *)0x0;
    goto LAB_0046b55e;
  default:
    goto switchD_0046b2c8_caseD_a;
  case 0xb:
    if (prec != 0) {
      if (bVar6 == 0x2b) {
LAB_0046b533:
        iVar9 = 7;
        this = pbVar7;
        cursor = (int *)pbVar7;
        iVar5 = local_14;
      }
      else {
        cursor = (int *)pbVar7;
        if (bVar6 != 0x2d) goto LAB_0046b5dd;
LAB_0046b527:
        local_1c = -1;
        iVar9 = 7;
        this = pbVar7;
        cursor = (int *)pbVar7;
        iVar5 = local_14;
      }
      goto LAB_0046b2bc;
    }
    iVar9 = 10;
    pbVar8 = pbVar7;
switchD_0046b2c8_caseD_a:
    pbVar7 = pbVar8;
    iVar5 = local_14;
    if (iVar9 != 10) goto LAB_0046b2bc;
    goto LAB_0046b5dd;
  }
  iVar9 = 9;
LAB_0046b4fe:
  pbVar8 = pbVar8 + -1;
  iVar5 = local_14;
  goto LAB_0046b2bc;
LAB_0046b55e:
  if (crt_locale_type < 2) {
    uVar3 = (byte)crt_ctype_table[(uint)bVar6 * 2] & 4;
    this = crt_ctype_table;
  }
  else {
    pbVar10 = (byte *)0x4;
    uVar3 = crt_isctype(this,(uint)bVar6,4);
    this = pbVar10;
  }
  if (uVar3 == 0) goto LAB_0046b5a8;
  this = (void *)(int)(char)bVar6;
  pbVar7 = (byte *)((int)this + (int)pbVar7 * 10 + -0x30);
  if (0x1450 < (int)pbVar7) goto LAB_0046b5a0;
  bVar6 = *pbVar8;
  pbVar8 = pbVar8 + 1;
  goto LAB_0046b55e;
LAB_0046b5a0:
  pbVar7 = (byte *)0x1451;
LAB_0046b5a8:
  while( true ) {
    local_20 = pbVar7;
    if (crt_locale_type < 2) {
      uVar3 = (byte)crt_ctype_table[(uint)bVar6 * 2] & 4;
      this = crt_ctype_table;
    }
    else {
      pbVar7 = (byte *)0x4;
      uVar3 = crt_isctype(this,(uint)bVar6,4);
      this = pbVar7;
    }
    if (uVar3 == 0) break;
    bVar6 = *pbVar8;
    pbVar8 = pbVar8 + 1;
    pbVar7 = local_20;
  }
LAB_0046b5d8:
  pbVar7 = pbVar8 + -1;
LAB_0046b5dd:
  *(byte **)out = pbVar7;
  if (local_14 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (int *)0x0;
    cursor = (int *)0x0;
    local_18 = 4;
    goto LAB_0046b6eb;
  }
  pcVar4 = local_10;
  if (0x18 < local_8) {
    if ('\x04' < local_49) {
      local_49 = local_49 + '\x01';
    }
    local_8 = 0x18;
    local_c = local_c + 1;
    pcVar4 = local_10 + -1;
  }
  if (local_8 == 0) {
    local_44 = 0;
    local_3a = 0;
    local_3e = (int *)0x0;
    cursor = (int *)0x0;
  }
  else {
    while (pcVar4 = pcVar4 + -1, *pcVar4 == '\0') {
      local_8 = local_8 - 1;
      local_c = local_c + 1;
    }
    crt_write_string(local_60,local_8,(int)&local_44);
    pbVar8 = local_20;
    if (local_1c < 0) {
      pbVar8 = (byte *)-(int)local_20;
    }
    pbVar8 = pbVar8 + local_c;
    if (local_24 == 0) {
      pbVar8 = pbVar8 + flags;
    }
    if (local_28 == 0) {
      pbVar8 = pbVar8 + -width;
    }
    if ((int)pbVar8 < 0x1451) {
      if (-0x1451 < (int)pbVar8) {
        crt_wide_num_format((int *)&local_44,(uint)pbVar8,(int)str);
        cursor = (int *)CONCAT22(uStack_40,uStack_42);
        goto LAB_0046b670;
      }
      local_34 = 1;
    }
    else {
      local_30 = 1;
    }
    local_3a = (ushort)cursor;
    local_3e = cursor;
    local_44 = local_3a;
  }
LAB_0046b670:
  if (local_30 == 0) {
    if (local_34 != 0) {
      local_44 = 0;
      local_3a = 0;
      local_3e = (int *)0x0;
      cursor = (int *)0x0;
      local_18 = 1;
    }
  }
  else {
    cursor = (int *)0x0;
    local_3a = 0x7fff;
    local_3e = (int *)0x80000000;
    local_44 = 0;
    local_18 = 2;
  }
LAB_0046b6eb:
  *(int **)((int)ctx + 6) = local_3e;
  *(int **)((int)ctx + 2) = cursor;
  *(ushort *)((int)ctx + 10) = local_3a | (ushort)local_2c;
  *(ushort *)ctx = local_44;
  return local_18;
}



/* crt_file_write_buffered @ 0046c4cb */

/* [binja] int32_t* sub_46c4cb(int32_t arg1, int32_t* arg2, uint32_t arg3) */

int * __cdecl crt_file_write_buffered(int arg1,int *arg2,uint arg3)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int *piVar3;
  uint uVar4;
  uint local_5c [10];
  undefined8 local_34;
  uint local_24;
  
  arg3 = (uint)*(ushort *)arg3;
  iVar1 = *arg2;
  if (iVar1 == 1) {
LAB_0046c510:
    uVar4 = 8;
  }
  else if (iVar1 == 2) {
    uVar4 = 4;
  }
  else if (iVar1 == 3) {
    uVar4 = 0x11;
  }
  else if (iVar1 == 4) {
    uVar4 = 0x12;
  }
  else {
    if (iVar1 == 5) goto LAB_0046c510;
    if (iVar1 == 7) {
      *arg2 = 1;
      goto LAB_0046c566;
    }
    if (iVar1 != 8) goto LAB_0046c566;
    uVar4 = 0x10;
  }
  bVar2 = FUN_00469326(uVar4,(double *)(arg2 + 6),arg3);
  if (CONCAT31(extraout_var,bVar2) == 0) {
    if (((arg1 == 0x10) || (arg1 == 0x16)) || (arg1 == 0x1d)) {
      local_34 = *(undefined8 *)(arg2 + 4);
      local_24 = local_24 & 0xffffffe3 | 3;
    }
    else {
      local_24 = local_24 & 0xfffffffe;
    }
    FUN_00469073(local_5c,&arg3,uVar4,arg1,(undefined8 *)(arg2 + 2),(undefined8 *)(arg2 + 6));
  }
LAB_0046c566:
  FUN_00469582();
  if (((*arg2 != 8) && (DAT_0047e088 == 0)) &&
     (piVar3 = (int *)crt_get_default_locale(), piVar3 != (int *)0x0)) {
    return piVar3;
  }
  piVar3 = FUN_0046953d((int *)*arg2);
  return piVar3;
}



/* __frnd @ 0046c59b */

/* Library Function - Single Match
    __frnd
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

float10 __cdecl __frnd(double param_1)

{
  return (float10)ROUND(param_1);
}



/* crt_file_write_char @ 0046c5ad */

void crt_file_write_char(void)

{
  if (crt_console_mode == 0) {
    crt_lock(0xb);
    if (crt_console_mode == 0) {
      crt_file_flush();
      crt_console_mode = crt_console_mode + 1;
    }
    crt_unlock(0xb);
  }
  return;
}



/* crt_file_flush @ 0046c5db */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void crt_file_flush(void)

{
  byte bVar1;
  byte bVar2;
  char *_Str1;
  DWORD DVar3;
  int iVar4;
  size_t sVar5;
  void *this;
  byte *_Source;
  int local_8;
  
  crt_lock(0xc);
  crt_local_year = 0xffffffff;
  crt_utc_year = 0xffffffff;
  crt_mbcs_codepage = 0;
  _Str1 = (char *)crt_getenv("TZ");
  if (_Str1 == (char *)0x0) {
    crt_unlock(0xc);
    DVar3 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&crt_tz_info_bias);
    if (DVar3 == 0xffffffff) {
      return;
    }
    crt_timezone_offset = (void *)(crt_tz_info_bias * 0x3c);
    crt_mbcs_codepage = 1;
    if (crt_tz_dst_month != 0) {
      crt_timezone_offset = (void *)((int)crt_timezone_offset + crt_tz_std_bias_minutes * 0x3c);
    }
    if ((crt_tz_std_month == 0) || (crt_tz_dst_bias_minutes == 0)) {
      crt_dst_flag = 0;
      crt_timezone_seconds = 0;
    }
    else {
      crt_dst_flag = 1;
      crt_timezone_seconds = (crt_tz_dst_bias_minutes - crt_tz_std_bias_minutes) * 0x3c;
    }
    iVar4 = WideCharToMultiByte(crt_acp_codepage,0x220,(LPCWCH)&DAT_004d9b9c,-1,PTR_DAT_0047defc,0x3f,
                                (LPCCH)0x0,&local_8);
    if ((iVar4 == 0) || (local_8 != 0)) {
      *PTR_DAT_0047defc = 0;
    }
    else {
      PTR_DAT_0047defc[0x3f] = 0;
    }
    iVar4 = WideCharToMultiByte(crt_acp_codepage,0x220,(LPCWCH)&DAT_004d9bf0,-1,PTR_DAT_0047df00,0x3f,
                                (LPCCH)0x0,&local_8);
    if ((iVar4 != 0) && (local_8 == 0)) {
      PTR_DAT_0047df00[0x3f] = 0;
      return;
    }
LAB_0046c84c:
    *PTR_DAT_0047df00 = 0;
  }
  else {
    if ((*_Str1 != '\0') &&
       ((crt_console_handle == (char *)0x0 || (iVar4 = _strcmp(_Str1,crt_console_handle), iVar4 != 0)))) {
      crt_free_base(crt_console_handle);
      sVar5 = _strlen(_Str1);
      crt_console_handle = _malloc(sVar5 + 1);
      if (crt_console_handle != (char *)0x0) {
        crt_strcpy(crt_console_handle,_Str1);
        crt_unlock(0xc);
        _strncpy(PTR_DAT_0047defc,_Str1,3);
        _Source = (byte *)(_Str1 + 3);
        PTR_DAT_0047defc[3] = 0;
        bVar1 = *_Source;
        if (bVar1 == 0x2d) {
          _Source = (byte *)(_Str1 + 4);
        }
        iVar4 = crt_strtol(this,_Source);
        crt_timezone_offset = (void *)(iVar4 * 0xe10);
        for (; (bVar2 = *_Source, bVar2 == 0x2b || (('/' < (char)bVar2 && ((char)bVar2 < ':'))));
            _Source = _Source + 1) {
        }
        if (*_Source == 0x3a) {
          _Source = _Source + 1;
          iVar4 = crt_strtol(crt_timezone_offset,_Source);
          crt_timezone_offset = (void *)((int)crt_timezone_offset + iVar4 * 0x3c);
          for (; ('/' < (char)*_Source && ((char)*_Source < ':')); _Source = _Source + 1) {
          }
          if (*_Source == 0x3a) {
            _Source = _Source + 1;
            iVar4 = crt_strtol(crt_timezone_offset,_Source);
            crt_timezone_offset = (void *)((int)crt_timezone_offset + iVar4);
            for (; ('/' < (char)*_Source && ((char)*_Source < ':')); _Source = _Source + 1) {
            }
          }
        }
        if (bVar1 == 0x2d) {
          crt_timezone_offset = (void *)-(int)crt_timezone_offset;
        }
        crt_dst_flag = (int)(char)*_Source;
        if (crt_dst_flag != 0) {
          _strncpy(PTR_DAT_0047df00,(char *)_Source,3);
          PTR_DAT_0047df00[3] = 0;
          return;
        }
        goto LAB_0046c84c;
      }
    }
    crt_unlock(0xc);
  }
  return;
}



/* crt_get_local_time @ 0046c862 */

bool __cdecl crt_get_local_time(int *param_1)

{
  bool bVar1;
  
  crt_lock(0xb);
  bVar1 = crt_get_system_time(param_1);
  crt_unlock(0xb);
  return bVar1;
}



/* crt_get_system_time @ 0046c883 */

bool __cdecl crt_get_system_time(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  if (crt_dst_flag != 0) {
    uVar5 = param_1[5];
    if ((uVar5 != crt_utc_year) || (uVar5 != crt_local_year)) {
      if (crt_mbcs_codepage == 0) {
        crt_time_to_day_of_year(1,1,uVar5,4,1,0,0,2,0,0,0);
        crt_time_to_day_of_year(0,1,param_1[5],10,5,0,0,2,0,0,0);
      }
      else {
        if (crt_tz_std_year != 0) {
          uVar6 = (uint)crt_tz_std_day;
          uVar3 = 0;
          uVar4 = 0;
        }
        else {
          uVar3 = (uint)DAT_004d9c34;
          uVar6 = 0;
          uVar4 = (uint)crt_tz_std_day;
        }
        crt_time_to_day_of_year(1,(uint)(crt_tz_std_year == 0),uVar5,(uint)crt_tz_std_month,uVar4,uVar3,uVar6,
                     (uint)DAT_004d9c38,(uint)DAT_004d9c3a,(uint)DAT_004d9c3c,(uint)DAT_004d9c3e);
        if (crt_tz_dst_year != 0) {
          uVar6 = (uint)crt_tz_dst_day;
          uVar3 = 0;
          uVar4 = 0;
          uVar5 = param_1[5];
        }
        else {
          uVar3 = (uint)DAT_004d9be0;
          uVar6 = 0;
          uVar4 = (uint)crt_tz_dst_day;
          uVar5 = param_1[5];
        }
        crt_time_to_day_of_year(0,(uint)(crt_tz_dst_year == 0),uVar5,(uint)crt_tz_dst_month,uVar4,uVar3,uVar6,
                     (uint)DAT_004d9be4,(uint)DAT_004d9be6,(uint)DAT_004d9be8,(uint)DAT_004d9bea);
      }
    }
    iVar1 = param_1[7];
    if (crt_utc_day_number < crt_local_day_number) {
      if ((crt_utc_day_number <= iVar1) && (iVar1 <= crt_local_day_number)) {
        if ((crt_utc_day_number < iVar1) && (iVar1 < crt_local_day_number)) {
          return true;
        }
LAB_0046c9fb:
        iVar2 = ((param_1[2] * 0x3c + param_1[1]) * 0x3c + *param_1) * 1000;
        if (iVar1 == crt_utc_day_number) {
          return crt_utc_time_ms <= iVar2;
        }
        return iVar2 < crt_day_of_year_normal;
      }
    }
    else {
      if (iVar1 < crt_local_day_number) {
        return true;
      }
      if (crt_utc_day_number < iVar1) {
        return true;
      }
      if ((iVar1 <= crt_local_day_number) || (crt_utc_day_number <= iVar1)) goto LAB_0046c9fb;
    }
  }
  return false;
}



/* crt_time_to_day_of_year @ 0046ca2f */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
crt_time_to_day_of_year(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      iVar1 = (&crt_day_of_year_normal)[param_4];
    }
    else {
      iVar1 = *(int *)(&crt_day_of_year_leap + param_4 * 4);
    }
    iVar2 = (int)(param_3 * 0x16d + -0x63db + iVar1 + 1 + ((int)(param_3 - 1) >> 2)) % 7;
    if (param_6 < iVar2) {
      iVar1 = iVar1 + 1 + (param_5 * 7 - iVar2) + param_6;
    }
    else {
      iVar1 = iVar1 + -6 + (param_5 * 7 - iVar2) + param_6;
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        iVar2 = *(int *)(&crt_days_in_month_normal + param_4 * 4);
      }
      else {
        iVar2 = *(int *)(&crt_days_in_month_leap + param_4 * 4);
      }
      if (iVar2 < iVar1) {
        iVar1 = iVar1 + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      iVar1 = (&crt_day_of_year_normal)[param_4];
    }
    else {
      iVar1 = *(int *)(&crt_day_of_year_leap + param_4 * 4);
    }
    iVar1 = iVar1 + param_7;
  }
  if (param_1 == 1) {
    crt_utc_year = param_3;
    crt_utc_time_ms = ((param_8 * 0x3c + param_9) * 0x3c + param_10) * 1000 + param_11;
    crt_utc_day_number = iVar1;
  }
  else {
    crt_day_of_year_normal = ((param_8 * 0x3c + param_9) * 0x3c + crt_timezone_seconds + param_10) * 1000 + param_11;
    if (crt_day_of_year_normal < 0) {
      crt_day_of_year_normal = crt_day_of_year_normal + 86400000;
      crt_local_day_number = iVar1 + -1;
    }
    else {
      crt_local_day_number = iVar1;
      if (86399999 < crt_day_of_year_normal) {
        crt_day_of_year_normal = crt_day_of_year_normal + -86400000;
        crt_local_day_number = iVar1 + 1;
      }
    }
    crt_local_year = param_3;
  }
  return;
}



/* crt_abort_runtime @ 0046cb6f */

void crt_abort_runtime(void)

{
  crt_report_runtime_error(10);
  crt_exit_process((void *)0x16);
                    /* WARNING: Subroutine does not return */
  __exit(3);
}



/* _strcmp @ 0046cb90 */

/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_0046cbd4;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_0046cba0;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_0046cbd4;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < ((byte *)_Str2)[1];
    if (bVar4 != ((byte *)_Str2)[1]) goto LAB_0046cbd4;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = (char *)((byte *)_Str2 + 2);
  }
LAB_0046cba0:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < ((byte *)_Str2)[1];
    if (bVar4 != ((byte *)_Str2)[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < ((byte *)_Str2)[2];
    if (bVar4 != ((byte *)_Str2)[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < ((byte *)_Str2)[3];
    if (bVar3 != ((byte *)_Str2)[3]) break;
    _Str2 = (char *)((byte *)_Str2 + 4);
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_0046cbd4:
  return (uint)bVar5 * -2 + 1;
}



/* _strncpy @ 0046cc20 */

/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uint)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x0046cc5e;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_0046cc9b;
        goto LAB_0046cd09;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x0046cd05:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_0046cd09:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_0046cc9b;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x0046cd05;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x0046cd05;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x0046cd05;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x0046cc5e:
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((int)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_0046cc9b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}



/* FUN_0046cd20 @ 0046cd20 */

int __cdecl FUN_0046cd20(byte *param_1,byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  iVar2 = -1;
  do {
    iVar2 = iVar2 + 1;
    bVar1 = *param_1;
    if (bVar1 == 0) {
      return iVar2;
    }
    param_1 = param_1 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return iVar2;
}



/* FUN_0046cd60 @ 0046cd60 */

byte * __cdecl FUN_0046cd60(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte abStack_28 [32];
  
  abStack_28[0x1c] = 0;
  abStack_28[0x1d] = 0;
  abStack_28[0x1e] = 0;
  abStack_28[0x1f] = 0;
  abStack_28[0x18] = 0;
  abStack_28[0x19] = 0;
  abStack_28[0x1a] = 0;
  abStack_28[0x1b] = 0;
  abStack_28[0x14] = 0;
  abStack_28[0x15] = 0;
  abStack_28[0x16] = 0;
  abStack_28[0x17] = 0;
  abStack_28[0x10] = 0;
  abStack_28[0x11] = 0;
  abStack_28[0x12] = 0;
  abStack_28[0x13] = 0;
  abStack_28[0xc] = 0;
  abStack_28[0xd] = 0;
  abStack_28[0xe] = 0;
  abStack_28[0xf] = 0;
  abStack_28[8] = 0;
  abStack_28[9] = 0;
  abStack_28[10] = 0;
  abStack_28[0xb] = 0;
  abStack_28[4] = 0;
  abStack_28[5] = 0;
  abStack_28[6] = 0;
  abStack_28[7] = 0;
  abStack_28[0] = 0;
  abStack_28[1] = 0;
  abStack_28[2] = 0;
  abStack_28[3] = 0;
  while( true ) {
    bVar1 = *param_2;
    if (bVar1 == 0) break;
    param_2 = param_2 + 1;
    abStack_28[(int)(uint)bVar1 >> 3] = abStack_28[(int)(uint)bVar1 >> 3] | '\x01' << (bVar1 & 7);
  }
  do {
    pbVar2 = param_1;
    bVar1 = *pbVar2;
    if (bVar1 == 0) {
      return (byte *)0x0;
    }
    param_1 = pbVar2 + 1;
  } while ((abStack_28[(int)(uint)bVar1 >> 3] >> (bVar1 & 7) & 1) == 0);
  return pbVar2;
}



/* crt_chkstk @ 0046cda0 */

/* WARNING: Unable to track spacebase fully for stack */
/* CRT: stack probing helper for large alloca (size in EAX) */

void crt_chkstk(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}



/* crt_strtol_l @ 0046cdcf */

/* CRT: parse integer with base (locale) */

long __thiscall crt_strtol_l(void *this,void *locale,char *str,char **endptr,int base)

{
  ulong uVar1;
  uint unaff_retaddr;
  
  uVar1 = crt_strtoxl(this,locale,str,endptr,0,unaff_retaddr);
  return uVar1;
}



/* crt_strtoxl @ 0046cde6 */

/* CRT: shared strto* core (base/sign/overflow) */

ulong __thiscall crt_strtoxl(void *this,void *locale,char *str,char **endptr,int base,uint flags)

{
  byte *pbVar1;
  char **ppcVar2;
  uint uVar3;
  char **ppcVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  char **this_00;
  byte bVar8;
  undefined *puVar9;
  char **local_c;
  byte *local_8;
  
  local_c = (char **)0x0;
  bVar8 = *(byte *)locale;
  pbVar1 = locale;
  while( true ) {
    local_8 = pbVar1 + 1;
    if (crt_locale_type < 2) {
      uVar3 = (byte)crt_ctype_table[(uint)bVar8 * 2] & 8;
      this = crt_ctype_table;
    }
    else {
      puVar9 = (undefined *)0x8;
      uVar3 = crt_isctype(this,(uint)bVar8,8);
      this = puVar9;
    }
    if (uVar3 == 0) break;
    bVar8 = *local_8;
    pbVar1 = local_8;
  }
  if (bVar8 == 0x2d) {
    base = base | 2;
LAB_0046ce41:
    bVar8 = *local_8;
    local_8 = pbVar1 + 2;
  }
  else if (bVar8 == 0x2b) goto LAB_0046ce41;
  if ((((int)endptr < 0) || (endptr == (char **)0x1)) || (0x24 < (int)endptr)) {
    if (str != (char *)0x0) {
      *(void **)str = locale;
    }
    return 0;
  }
  this_00 = (char **)0x10;
  if (endptr == (char **)0x0) {
    if (bVar8 != 0x30) {
      endptr = (char **)0xa;
      goto LAB_0046ceab;
    }
    if ((*local_8 != 0x78) && (*local_8 != 0x58)) {
      endptr = (char **)0x8;
      goto LAB_0046ceab;
    }
    endptr = (char **)0x10;
  }
  if (((endptr == (char **)0x10) && (bVar8 == 0x30)) && ((*local_8 == 0x78 || (*local_8 == 0x58))))
  {
    bVar8 = local_8[1];
    local_8 = local_8 + 2;
  }
LAB_0046ceab:
  ppcVar4 = (char **)(0xffffffff / ZEXT48(endptr));
  do {
    uVar3 = (uint)bVar8;
    if (crt_locale_type < 2) {
      uVar5 = (byte)crt_ctype_table[uVar3 * 2] & 4;
    }
    else {
      ppcVar2 = (char **)0x4;
      uVar5 = crt_isctype(this_00,uVar3,4);
      this_00 = ppcVar2;
    }
    if (uVar5 == 0) {
      if (crt_locale_type < 2) {
        uVar3 = *(ushort *)(crt_ctype_table + uVar3 * 2) & 0x103;
      }
      else {
        uVar3 = crt_isctype(this_00,uVar3,0x103);
      }
      if (uVar3 == 0) {
LAB_0046cf57:
        local_8 = local_8 + -1;
        if ((base & 8U) == 0) {
          if (str != (char *)0x0) {
            local_8 = locale;
          }
          local_c = (char **)0x0;
        }
        else if (((base & 4U) != 0) ||
                (((base & 1U) == 0 &&
                 ((((base & 2U) != 0 && ((char **)0x80000000 < local_c)) ||
                  (((base & 2U) == 0 && ((char **)0x7fffffff < local_c)))))))) {
          piVar7 = crt_errno_ptr();
          *piVar7 = 0x22;
          if ((base & 1U) == 0) {
            local_c = (char **)(((base & 2U) != 0) + 0x7fffffff);
          }
          else {
            local_c = (char **)0xffffffff;
          }
        }
        if (str != (char *)0x0) {
          *(byte **)str = local_8;
        }
        if ((base & 2U) == 0) {
          return (ulong)local_c;
        }
        return -(int)local_c;
      }
      iVar6 = crt_toupper((int)(char)bVar8);
      this_00 = (char **)(iVar6 + -0x37);
    }
    else {
      this_00 = (char **)((char)bVar8 + -0x30);
    }
    if (endptr <= this_00) goto LAB_0046cf57;
    if ((local_c < ppcVar4) ||
       ((local_c == ppcVar4 && (this_00 <= (char **)(0xffffffff % ZEXT48(endptr)))))) {
      local_c = (char **)((int)local_c * (int)endptr + (int)this_00);
      base = base | 8;
    }
    else {
      base = base | 0xc;
    }
    bVar8 = *local_8;
    local_8 = local_8 + 1;
  } while( true );
}



/* crt_mbtowc_locking @ 0046cfeb */

uint __cdecl crt_mbtowc_locking(LPWSTR param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  bool bVar2;
  
  InterlockedIncrement((LONG *)&crt_lock_count);
  bVar2 = crt_sbh_reserved_a != 0;
  if (bVar2) {
    InterlockedDecrement((LONG *)&crt_lock_count);
    crt_lock(0x13);
  }
  uVar1 = crt_mbtowc_internal(param_1,param_2,param_3);
  if (bVar2) {
    crt_unlock(0x13);
  }
  else {
    InterlockedDecrement((LONG *)&crt_lock_count);
  }
  return uVar1;
}



/* crt_mbtowc_internal @ 0046d048 */

uint __cdecl crt_mbtowc_internal(LPWSTR param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_2 != (byte *)0x0) && (param_3 != 0)) {
    bVar1 = *param_2;
    if (bVar1 != 0) {
      if (crt_locale_id == 0) {
        if (param_1 != (LPWSTR)0x0) {
          *param_1 = (ushort)bVar1;
        }
        return 1;
      }
      if ((crt_ctype_table[(uint)bVar1 * 2 + 1] & 0x80) == 0) {
        iVar2 = MultiByteToWideChar(crt_acp_codepage,9,(LPCCH)param_2,1,param_1,
                                    (uint)(param_1 != (LPWSTR)0x0));
        if (iVar2 != 0) {
          return 1;
        }
      }
      else {
        if (1 < (int)crt_locale_type) {
          if ((int)param_3 < (int)crt_locale_type) goto LAB_0046d0da;
          iVar2 = MultiByteToWideChar(crt_acp_codepage,9,(LPCCH)param_2,crt_locale_type,param_1,
                                      (uint)(param_1 != (LPWSTR)0x0));
          if (iVar2 != 0) {
            return crt_locale_type;
          }
        }
        if ((crt_locale_type <= param_3) && (param_2[1] != 0)) {
          return crt_locale_type;
        }
      }
LAB_0046d0da:
      piVar3 = crt_errno_ptr();
      *piVar3 = 0x2a;
      return 0xffffffff;
    }
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = L'\0';
    }
  }
  return 0;
}



/* __allshl @ 0046d120 */

/* Library Function - Single Match
    __allshl
   
   Library: Visual Studio */

longlong __fastcall __allshl(byte param_1,int param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 << (param_1 & 0x1f) | in_EAX >> 0x20 - (param_1 & 0x1f),
                    in_EAX << (param_1 & 0x1f));
  }
  return (ulonglong)(in_EAX << (param_1 & 0x1f)) << 0x20;
}



/* crt_ungetc @ 0046d13f */

uint __cdecl crt_ungetc(uint param_1,int *param_2)

{
  uint uVar1;
  
  if ((param_1 != 0xffffffff) &&
     ((uVar1 = param_2[3], (uVar1 & 1) != 0 || (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (param_2[2] == 0) {
      crt_file_buffer_init(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
      *param_2 = *param_2 + -1;
      *(char *)*param_2 = (char)param_1;
    }
    else {
      *param_2 = *param_2 + -1;
      if (*(char *)*param_2 != (char)param_1) {
        *param_2 = (int)((char *)*param_2 + 1);
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffefU | 1;
    return param_1 & 0xff;
  }
  return 0xffffffff;
}



/* crt_isleadbyte @ 0046d1ad */

/* [binja] int32_t sub_46d1ad(char arg1) */

int __cdecl crt_isleadbyte(char arg1)

{
  int iVar1;
  
  iVar1 = crt_isctype_masked(arg1,0,'\x04');
  return iVar1;
}



/* crt_isctype_masked @ 0046d1be */

/* [binja] int32_t sub_46d1be(char arg1, int32_t arg2, char arg3) */

int __cdecl crt_isctype_masked(char arg1,int arg2,char arg3)

{
  uint uVar1;
  
  if ((*(byte *)((int)&crt_char_type_table + (byte)arg1 + 1) & arg3) == 0) {
    if (arg2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = (uint)*(ushort *)(&DAT_0047b1ca + (uint)(byte)arg1 * 2) & arg2;
    }
    if (uVar1 == 0) {
      return 0;
    }
  }
  return 1;
}



/* crt_setmbcp @ 0046d1ef */

/* CRT: set multibyte code page and rebuild ctype tables */

int __cdecl crt_setmbcp(int codepage)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  WINBOOL WVar6;
  uint uVar7;
  uint uVar8;
  BYTE *pBVar9;
  int iVar10;
  byte *pbVar11;
  byte *pbVar12;
  int iVar13;
  undefined4 *puVar14;
  _cpinfo local_1c;
  uint local_8;
  
  crt_lock(0x19);
  CodePage = crt_wctomb_locking(codepage);
  if (CodePage != crt_heap_lock_flag) {
    if (CodePage != 0) {
      iVar13 = 0;
      pUVar5 = &DAT_0047df98;
LAB_0046d22c:
      if (*pUVar5 != CodePage) goto code_r0x0046d230;
      local_8 = 0;
      puVar14 = &crt_char_type_table;
      for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar14 = 0;
        puVar14 = puVar14 + 1;
      }
      iVar13 = iVar13 * 0x30;
      *(undefined1 *)puVar14 = 0;
      pbVar12 = (byte *)(iVar13 + 0x47dfa8);
      do {
        bVar3 = *pbVar12;
        pbVar11 = pbVar12;
        while ((bVar3 != 0 && (bVar3 = pbVar11[1], bVar3 != 0))) {
          uVar8 = (uint)*pbVar11;
          if (uVar8 <= bVar3) {
            bVar4 = (&DAT_0047df90)[local_8];
            do {
              pbVar2 = (byte *)((int)&crt_char_type_table + uVar8 + 1);
              *pbVar2 = *pbVar2 | bVar4;
              uVar8 = uVar8 + 1;
            } while (uVar8 <= bVar3);
          }
          pbVar11 = pbVar11 + 2;
          bVar3 = *pbVar11;
        }
        local_8 = local_8 + 1;
        pbVar12 = pbVar12 + 8;
      } while (local_8 < 4);
      crt_sbh_region_count = 1;
      crt_heap_lock_flag = CodePage;
      crt_sbh_active_flag = crt_wctomb_internal(CodePage);
      crt_sbh_region_list_c = *(undefined4 *)(iVar13 + 0x47df9c);
      crt_sbh_region_list_b = *(undefined4 *)(iVar13 + 0x47dfa0);
      crt_sbh_region_list_a = *(undefined4 *)(iVar13 + 0x47dfa4);
      goto LAB_0046d380;
    }
    goto LAB_0046d37b;
  }
  goto LAB_0046d216;
code_r0x0046d230:
  pUVar5 = pUVar5 + 0xc;
  iVar13 = iVar13 + 1;
  if ((UINT *)0x47e087 < pUVar5) goto code_r0x0046d23b;
  goto LAB_0046d22c;
code_r0x0046d23b:
  WVar6 = GetCPInfo(CodePage,&local_1c);
  uVar8 = 1;
  if (WVar6 == 1) {
    crt_sbh_active_flag = 0;
    puVar14 = &crt_char_type_table;
    for (iVar13 = 0x40; iVar13 != 0; iVar13 = iVar13 + -1) {
      *puVar14 = 0;
      puVar14 = puVar14 + 1;
    }
    *(undefined1 *)puVar14 = 0;
    if (local_1c.MaxCharSize < 2) {
      crt_sbh_region_count = 0;
      crt_heap_lock_flag = CodePage;
    }
    else {
      crt_heap_lock_flag = CodePage;
      if (local_1c.LeadByte[0] != '\0') {
        pBVar9 = local_1c.LeadByte + 1;
        do {
          bVar3 = *pBVar9;
          if (bVar3 == 0) break;
          for (uVar7 = (uint)pBVar9[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
            pbVar12 = (byte *)((int)&crt_char_type_table + uVar7 + 1);
            *pbVar12 = *pbVar12 | 4;
          }
          pBVar1 = pBVar9 + 1;
          pBVar9 = pBVar9 + 2;
        } while (*pBVar1 != 0);
      }
      do {
        pbVar12 = (byte *)((int)&crt_char_type_table + uVar8 + 1);
        *pbVar12 = *pbVar12 | 8;
        uVar8 = uVar8 + 1;
      } while (uVar8 < 0xff);
      crt_sbh_active_flag = crt_wctomb_internal(CodePage);
      crt_sbh_region_count = 1;
    }
    crt_sbh_region_list_c = 0;
    crt_sbh_region_list_b = 0;
    crt_sbh_region_list_a = 0;
  }
  else {
    if (crt_file_info_b == 0) {
      iVar13 = -1;
      goto LAB_0046d38d;
    }
LAB_0046d37b:
    crt_setmbcp_internal();
  }
LAB_0046d380:
  crt_get_system_locale();
LAB_0046d216:
  iVar13 = 0;
LAB_0046d38d:
  crt_unlock(0x19);
  return iVar13;
}



/* crt_wctomb_locking @ 0046d39c */

int __cdecl crt_wctomb_locking(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (param_1 == -2) {
    crt_file_info_b = 1;
                    /* WARNING: Could not recover jumptable at 0x0046d3b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetOEMCP();
    return iVar1;
  }
  if (param_1 == -3) {
    crt_file_info_b = 1;
                    /* WARNING: Could not recover jumptable at 0x0046d3cb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar1 = GetACP();
    return iVar1;
  }
  bVar2 = param_1 == -4;
  if (bVar2) {
    param_1 = crt_acp_codepage;
  }
  crt_file_info_b = (uint)bVar2;
  return param_1;
}



/* crt_wctomb_internal @ 0046d3e6 */

undefined4 __cdecl crt_wctomb_internal(int param_1)

{
  if (param_1 == 0x3a4) {
    return 0x411;
  }
  if (param_1 == 0x3a8) {
    return 0x804;
  }
  if (param_1 == 0x3b5) {
    return 0x412;
  }
  if (param_1 != 0x3b6) {
    return 0;
  }
  return 0x404;
}



/* crt_setmbcp_internal @ 0046d419 */

void crt_setmbcp_internal(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &crt_char_type_table;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  crt_heap_lock_flag = 0;
  crt_sbh_region_count = 0;
  crt_sbh_active_flag = 0;
  crt_sbh_region_list_c = 0;
  crt_sbh_region_list_b = 0;
  crt_sbh_region_list_a = 0;
  return;
}



/* crt_get_system_locale @ 0046d442 */

/* [binja] void* sub_46d442() */

void * crt_get_system_locale(void)

{
  WINBOOL WVar1;
  uint uVar2;
  void *pvVar3;
  char cVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  undefined1 uVar8;
  BYTE *pBVar9;
  CHAR *pCVar10;
  WORD local_518 [256];
  ushort local_318 [128];
  ushort local_218 [128];
  CHAR local_118 [256];
  _cpinfo local_18;
  
  WVar1 = GetCPInfo(crt_heap_lock_flag,&local_18);
  if (WVar1 == 1) {
    uVar2 = 0;
    do {
      local_118[uVar2] = (CHAR)uVar2;
      uVar2 = uVar2 + 1;
    } while (uVar2 < 0x100);
    local_118[0] = ' ';
    if (local_18.LeadByte[0] != 0) {
      pBVar9 = local_18.LeadByte + 1;
      do {
        uVar2 = (uint)local_18.LeadByte[0];
        if (uVar2 <= *pBVar9) {
          uVar5 = (*pBVar9 - uVar2) + 1;
          uVar6 = uVar5 >> 2;
          pCVar10 = local_118 + uVar2;
          while (uVar6 != 0) {
            uVar6 = uVar6 - 1;
            builtin_memcpy(pCVar10,"    ",4);
            pCVar10 = pCVar10 + 4;
          }
          for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
            *pCVar10 = ' ';
            pCVar10 = pCVar10 + 1;
          }
        }
        local_18.LeadByte[0] = pBVar9[1];
        pBVar9 = pBVar9 + 2;
      } while (local_18.LeadByte[0] != 0);
    }
    crt_cxx_throw_exception(1,local_118,0x100,local_518,crt_heap_lock_flag,crt_sbh_active_flag,0);
    crt_lcmap_string(crt_sbh_active_flag,0x100,local_118,0x100,local_218,0x100,crt_heap_lock_flag,0);
    crt_lcmap_string(crt_sbh_active_flag,0x200,local_118,0x100,local_318,0x100,crt_heap_lock_flag,0);
    pvVar3 = (void *)0x0;
    puVar7 = local_518;
    do {
      if ((*puVar7 & 1) == 0) {
        if ((*puVar7 & 2) != 0) {
          *(byte *)((int)pvVar3 + 0x4da281U) = *(byte *)((int)pvVar3 + 0x4da281U) | 0x20;
          uVar8 = *(undefined1 *)((int)local_318 + (int)pvVar3);
          goto LAB_0046d54e;
        }
        *(undefined1 *)((int)pvVar3 + 0x4da180) = 0;
      }
      else {
        *(byte *)((int)pvVar3 + 0x4da281U) = *(byte *)((int)pvVar3 + 0x4da281U) | 0x10;
        uVar8 = *(undefined1 *)((int)local_218 + (int)pvVar3);
LAB_0046d54e:
        *(undefined1 *)((int)pvVar3 + 0x4da180) = uVar8;
      }
      pvVar3 = (void *)((int)pvVar3 + 1);
      puVar7 = puVar7 + 1;
    } while (pvVar3 < (void *)0x100);
  }
  else {
    pvVar3 = (void *)0x0;
    do {
      if ((pvVar3 < (void *)0x41) || ((void *)0x5a < pvVar3)) {
        if (((void *)0x60 < pvVar3) && (pvVar3 < (void *)0x7b)) {
          *(byte *)((int)pvVar3 + 0x4da281U) = *(byte *)((int)pvVar3 + 0x4da281U) | 0x20;
          cVar4 = (char)pvVar3 + -0x20;
          goto LAB_0046d598;
        }
        *(undefined1 *)((int)pvVar3 + 0x4da180) = 0;
      }
      else {
        *(byte *)((int)pvVar3 + 0x4da281U) = *(byte *)((int)pvVar3 + 0x4da281U) | 0x10;
        cVar4 = (char)pvVar3 + ' ';
LAB_0046d598:
        *(char *)((int)pvVar3 + 0x4da180) = cVar4;
      }
      pvVar3 = (void *)((int)pvVar3 + 1);
    } while (pvVar3 < (void *)0x100);
  }
  return pvVar3;
}



/* crt_mbcs_init @ 0046d5c7 */

/* CRT: one-time init of multibyte/ctype tables (GetACP) */

void crt_mbcs_init(void)

{
  if (crt_mbcs_initialized == 0) {
    crt_setmbcp(-3);
    crt_mbcs_initialized = 1;
  }
  return;
}



/* crt_write_internal @ 0046d5e3 */

/* [binja] int32_t sub_46d5e3(int32_t arg1, int32_t arg2, int32_t arg3) */

int __cdecl crt_write_internal(int arg1,int arg2,int arg3)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (crt_file_info_a == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      crt_file_info_a = GetProcAddress(hModule,"MessageBoxA");
      if (crt_file_info_a != (FARPROC)0x0) {
        crt_file_flags_c = GetProcAddress(hModule,"GetActiveWindow");
        crt_file_flags_b = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_0046d632;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_0046d632:
    if (crt_file_flags_c != (FARPROC)0x0) {
      iVar1 = (*crt_file_flags_c)();
      if ((iVar1 != 0) && (crt_file_flags_b != (FARPROC)0x0)) {
        iVar1 = (*crt_file_flags_b)(iVar1);
      }
    }
    iVar1 = (*crt_file_info_a)(iVar1,arg1,arg2,arg3);
  }
  return iVar1;
}



/* crt_get_default_locale @ 0046d66c */

undefined4 crt_get_default_locale(void)

{
  return 0;
}



/* FUN_0046d66f @ 0046d66f */

/* [binja] int32_t __stdcall sub_46d66f(int32_t* arg1) */

int FUN_0046d66f(int *arg1)

{
  int *piVar1;
  bool bVar2;
  int extraout_EAX;
  undefined3 extraout_var;
  int iVar3;
  
  piVar1 = (int *)*arg1;
  if (((*piVar1 == -0x1f928c9d) && (piVar1[4] == 3)) && (piVar1[5] == 0x19930520)) {
    crt_terminate();
    return extraout_EAX;
  }
  if ((crt_file_flags_a != (FARPROC)0x0) &&
     (bVar2 = crt_is_valid_code_ptr(crt_file_flags_a), CONCAT31(extraout_var,bVar2) != 0)) {
    iVar3 = (*crt_file_flags_a)(arg1);
    return iVar3;
  }
  return 0;
}



/* crt_is_valid_read_ptr @ 0046d6d3 */

bool __cdecl crt_is_valid_read_ptr(void *param_1,UINT_PTR param_2)

{
  WINBOOL WVar1;
  
  WVar1 = IsBadReadPtr(param_1,param_2);
  return WVar1 == 0;
}



/* crt_is_valid_write_ptr @ 0046d6ef */

bool __cdecl crt_is_valid_write_ptr(LPVOID param_1,UINT_PTR param_2)

{
  WINBOOL WVar1;
  
  WVar1 = IsBadWritePtr(param_1,param_2);
  return WVar1 == 0;
}



/* crt_is_valid_code_ptr @ 0046d70b */

bool __cdecl crt_is_valid_code_ptr(FARPROC param_1)

{
  WINBOOL WVar1;
  
  WVar1 = IsBadCodePtr((FARPROC)param_1);
  return WVar1 == 0;
}



/* crt_exit_process @ 0046d723 */

/* [binja] int32_t sub_46d723(void* arg1) */

int __cdecl crt_exit_process(void *arg1)

{
  bool bVar1;
  DWORD *pDVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  undefined4 *puVar7;
  DWORD local_10;
  DWORD local_c;
  
  bVar1 = false;
  if (arg1 == (void *)0x2) {
    puVar7 = &crt_locale_name_numeric;
    pcVar6 = crt_locale_name_numeric;
LAB_0046d7a9:
    bVar1 = true;
    crt_lock(1);
    pDVar2 = arg1;
  }
  else {
    if (((arg1 != (void *)0x4) && (arg1 != (void *)0x8)) && (arg1 != (void *)0xb)) {
      if (arg1 == (void *)0xf) {
        puVar7 = &crt_locale_name_collate;
        pcVar6 = crt_locale_name_collate;
      }
      else if (arg1 == (void *)0x15) {
        puVar7 = &crt_locale_name_monetary;
        pcVar6 = crt_locale_name_monetary;
      }
      else {
        if (arg1 != (void *)0x16) {
          return -1;
        }
        puVar7 = &crt_locale_name_ctype;
        pcVar6 = crt_locale_name_ctype;
      }
      goto LAB_0046d7a9;
    }
    pDVar2 = crt_get_thread_data();
    uVar3 = crt_read_internal((int)arg1,pDVar2[0x14]);
    puVar7 = (undefined4 *)(uVar3 + 8);
    pcVar6 = (code *)*puVar7;
  }
  if (pcVar6 == (code *)0x1) {
    if (!bVar1) {
      return 0;
    }
    crt_unlock(1);
    return 0;
  }
  if (pcVar6 == (code *)0x0) {
    if (bVar1) {
      crt_unlock(1);
    }
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  if (((arg1 == (void *)0x8) || (arg1 == (void *)0xb)) || (arg1 == (void *)0x4)) {
    local_c = pDVar2[0x15];
    pDVar2[0x15] = 0;
    if (arg1 == (void *)0x8) {
      local_10 = pDVar2[0x16];
      pDVar2[0x16] = 0x8c;
      goto LAB_0046d81d;
    }
  }
  else {
LAB_0046d81d:
    if (arg1 == (void *)0x8) {
      if (crt_tls_data_a < crt_tls_data_c + crt_tls_data_a) {
        iVar4 = crt_tls_data_a * 0xc;
        iVar5 = crt_tls_data_a;
        do {
          iVar4 = iVar4 + 0xc;
          *(undefined4 *)((pDVar2[0x14] - 4) + iVar4) = 0;
          iVar5 = iVar5 + 1;
        } while (iVar5 < crt_tls_data_c + crt_tls_data_a);
      }
      goto LAB_0046d85b;
    }
  }
  *puVar7 = 0;
LAB_0046d85b:
  if (bVar1) {
    crt_unlock(1);
  }
  if (arg1 == (void *)0x8) {
    (*pcVar6)(8,pDVar2[0x16]);
  }
  else {
    (*pcVar6)(arg1);
    if ((arg1 != (void *)0xb) && (arg1 != (void *)0x4)) {
      return 0;
    }
  }
  pDVar2[0x15] = local_c;
  if (arg1 == (void *)0x8) {
    pDVar2[0x16] = local_10;
  }
  return 0;
}



/* crt_read_internal @ 0046d8a5 */

uint __cdecl crt_read_internal(int param_1,uint param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = param_2;
  if (*(int *)(param_2 + 4) != param_1) {
    uVar3 = param_2;
    do {
      uVar2 = uVar3 + 0xc;
      if (param_2 + crt_tls_data_b * 0xc <= uVar2) break;
      piVar1 = (int *)(uVar3 + 0x10);
      uVar3 = uVar2;
    } while (*piVar1 != param_1);
  }
  if ((param_2 + crt_tls_data_b * 0xc <= uVar2) || (*(int *)(uVar2 + 4) != param_1)) {
    uVar2 = 0;
  }
  return uVar2;
}



/* crt_add_u32_carry @ 0046d8e2 */

/* CRT: add two u32 values and return carry */

int __cdecl crt_add_u32_carry(uint a,uint b,uint *out)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  uVar1 = a + b;
  if ((uVar1 < a) || (uVar1 < b)) {
    iVar2 = 1;
  }
  *out = uVar1;
  return iVar2;
}



/* ___add_12 @ 0046d903 */

/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio 2003 Release */

void __cdecl ___add_12(uint *param_1,uint *param_2)

{
  int iVar1;
  
  iVar1 = crt_add_u32_carry(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = crt_add_u32_carry(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = crt_add_u32_carry(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  crt_add_u32_carry(param_1[2],param_2[2],param_1 + 2);
  return;
}



/* crt_u96_shl1 @ 0046d961 */

/* CRT: shift 96-bit value left by 1 (in-place) */

void __cdecl crt_u96_shl1(uint *value)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *value;
  uVar2 = value[1];
  *value = uVar1 * 2;
  value[1] = uVar2 * 2 | uVar1 >> 0x1f;
  value[2] = value[2] << 1 | uVar2 >> 0x1f;
  return;
}



/* crt_u96_shr1 @ 0046d98f */

/* CRT: shift 96-bit value right by 1 (in-place) */

void __cdecl crt_u96_shr1(uint *value)

{
  uint uVar1;
  
  uVar1 = value[1];
  value[1] = uVar1 >> 1 | value[2] << 0x1f;
  value[2] = value[2] >> 1;
  *value = *value >> 1 | uVar1 << 0x1f;
  return;
}



/* crt_write_string @ 0046d9bc */

/* [binja] int32_t sub_46d9bc(char* arg1, int32_t arg2, int32_t arg3) */

int __cdecl crt_write_string(char *arg1,int arg2,int arg3)

{
  int value;
  int iVar1;
  int extraout_EAX;
  uint local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  value = arg3;
  local_8 = 0x404e;
  *(undefined4 *)arg3 = 0;
  *(undefined4 *)(arg3 + 4) = 0;
  *(undefined4 *)(arg3 + 8) = 0;
  iVar1 = 0;
  if (arg2 != 0) {
    arg3 = arg2;
    do {
      local_14 = *(uint *)value;
      local_10 = *(undefined4 *)(value + 4);
      local_c = *(undefined4 *)(value + 8);
      crt_u96_shl1((uint *)value);
      crt_u96_shl1((uint *)value);
      ___add_12((uint *)value,&local_14);
      crt_u96_shl1((uint *)value);
      local_10 = 0;
      local_c = 0;
      local_14 = (uint)*arg1;
      iVar1 = ___add_12((uint *)value,&local_14);
      arg1 = arg1 + 1;
      arg3 = arg3 + -1;
    } while (arg3 != 0);
  }
  while (*(int *)(value + 8) == 0) {
    *(uint *)(value + 8) = *(uint *)(value + 4) >> 0x10;
    iVar1 = *(uint *)value << 0x10;
    local_8 = local_8 + 0xfff0;
    *(uint *)(value + 4) = *(uint *)value >> 0x10 | *(uint *)(value + 4) << 0x10;
    *(int *)value = iVar1;
  }
  while ((*(uint *)(value + 8) & 0x8000) == 0) {
    crt_u96_shl1((uint *)value);
    local_8 = local_8 + 0xffff;
    iVar1 = extraout_EAX;
  }
  *(undefined2 *)(value + 10) = (undefined2)local_8;
  return CONCAT22((short)((uint)iVar1 >> 0x10),(undefined2)local_8);
}



/* crt_format_output @ 0046da83 */

undefined4 __cdecl
crt_format_output(uint param_1,uint param_2,uint param_3,int param_4,byte param_5,short *param_6)

{
  short *psVar1;
  uint uVar2;
  short *psVar3;
  char cVar4;
  uint uVar5;
  short *psVar6;
  short *psVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14 [4];
  undefined2 uStack_10;
  undefined4 local_e;
  undefined1 local_a;
  char cStack_9;
  undefined4 local_8;
  
  psVar3 = param_6;
  uVar5 = param_3 & 0x7fff;
  local_20 = 0xcc;
  local_1f = 0xcc;
  local_1e = 0xcc;
  local_1d = 0xcc;
  local_1c = 0xcc;
  local_1b = 0xcc;
  local_1a = 0xcc;
  local_19 = 0xcc;
  local_18 = 0xcc;
  local_17 = 0xcc;
  local_16 = 0xfb;
  local_15 = 0x3f;
  local_8 = 1;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((short)uVar5 != 0) || (param_2 != 0)) || (param_1 != 0)) {
    if ((short)uVar5 == 0x7fff) {
      *param_6 = 1;
      if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
        if (((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) {
          if ((param_2 != 0x80000000) || (param_1 != 0)) goto LAB_0046db78;
          pcVar11 = "1#INF";
        }
        else {
          if (param_1 != 0) {
LAB_0046db78:
            pcVar11 = "1#QNAN";
            goto LAB_0046db7d;
          }
          pcVar11 = "1#IND";
        }
        crt_strcpy((char *)(param_6 + 2),pcVar11);
        *(undefined1 *)((int)psVar3 + 3) = 5;
      }
      else {
        pcVar11 = "1#SNAN";
LAB_0046db7d:
        crt_strcpy((char *)(param_6 + 2),pcVar11);
        *(undefined1 *)((int)psVar3 + 3) = 6;
      }
      return 0;
    }
    local_14._0_2_ = 0;
    local_a = (undefined1)uVar5;
    cStack_9 = (char)(uVar5 >> 8);
    sVar8 = (short)(((uVar5 >> 8) + (param_2 >> 0x18) * 2) * 0x4d + -0x134312f4 + uVar5 * 0x4d10 >>
                   0x10);
    local_e = param_2;
    unique0x100002bd = param_1;
    crt_wide_num_format((int *)local_14,-(int)sVar8,1);
    if (0x3ffe < CONCAT11(cStack_9,local_a)) {
      sVar8 = sVar8 + 1;
      crt_wide_int_format((short *)local_14,(int *)&local_20);
    }
    *psVar3 = sVar8;
    iVar10 = param_4;
    if (((param_5 & 1) == 0) || (iVar10 = param_4 + sVar8, 0 < param_4 + sVar8)) {
      if (0x15 < iVar10) {
        iVar10 = 0x15;
      }
      iVar9 = CONCAT11(cStack_9,local_a) - 0x3ffe;
      local_a = 0;
      cStack_9 = '\0';
      param_6 = (short *)0x8;
      do {
        crt_u96_shl1((uint *)local_14);
        param_6 = (short *)((int)param_6 + -1);
      } while (param_6 != (short *)0x0);
      if (iVar9 < 0) {
        param_6 = (short *)0x0;
        for (uVar5 = -iVar9 & 0xff; uVar5 != 0; uVar5 = uVar5 - 1) {
          crt_u96_shr1((uint *)local_14);
        }
      }
      param_4 = iVar10 + 1;
      psVar6 = psVar3 + 2;
      param_6 = psVar6;
      uVar5 = unique0x100001cb;
      uVar2 = local_e;
      if (0 < param_4) {
        do {
          local_e._2_2_ = (undefined2)(uVar2 >> 0x10);
          local_e._0_2_ = (undefined2)uVar2;
          uStack_10 = (undefined2)(uVar5 >> 0x10);
          local_14._2_2_ = (undefined2)uVar5;
          param_1 = CONCAT22(local_14._2_2_,local_14._0_2_);
          param_2 = CONCAT22((undefined2)local_e,uStack_10);
          param_3 = CONCAT13(cStack_9,CONCAT12(local_a,local_e._2_2_));
          unique0x100002d1 = uVar5;
          local_e = uVar2;
          crt_u96_shl1((uint *)local_14);
          crt_u96_shl1((uint *)local_14);
          ___add_12((uint *)local_14,&param_1);
          crt_u96_shl1((uint *)local_14);
          cVar4 = cStack_9;
          cStack_9 = '\0';
          psVar6 = (short *)((int)param_6 + 1);
          param_4 = param_4 + -1;
          *(char *)param_6 = cVar4 + '0';
          param_6 = psVar6;
          uVar5 = stack0xffffffee;
          uVar2 = local_e;
        } while (param_4 != 0);
      }
      psVar7 = psVar6 + -1;
      psVar1 = psVar3 + 2;
      if ('4' < *(char *)((int)psVar6 + -1)) {
        for (; psVar1 <= psVar7; psVar7 = (short *)((int)psVar7 + -1)) {
          if ((char)*psVar7 != '9') {
            if (psVar1 <= psVar7) goto LAB_0046dcd5;
            break;
          }
          *(char *)psVar7 = '0';
        }
        psVar7 = (short *)((int)psVar7 + 1);
        *psVar3 = *psVar3 + 1;
LAB_0046dcd5:
        *(char *)psVar7 = (char)*psVar7 + '\x01';
LAB_0046dcd7:
        cVar4 = ((char)psVar7 - (char)psVar3) + -3;
        *(char *)((int)psVar3 + 3) = cVar4;
        *(undefined1 *)(cVar4 + 4 + (int)psVar3) = 0;
        return local_8;
      }
      for (; psVar1 <= psVar7; psVar7 = (short *)((int)psVar7 + -1)) {
        if ((char)*psVar7 != '0') {
          if (psVar1 <= psVar7) goto LAB_0046dcd7;
          break;
        }
      }
      *psVar3 = 0;
      *(undefined1 *)(psVar3 + 1) = 0x20;
      *(undefined1 *)((int)psVar3 + 3) = 1;
      *(char *)psVar1 = '0';
      goto LAB_0046dd0d;
    }
  }
  *psVar3 = 0;
  *(undefined1 *)(psVar3 + 1) = 0x20;
  *(undefined1 *)((int)psVar3 + 3) = 1;
  *(undefined1 *)(psVar3 + 2) = 0x30;
LAB_0046dd0d:
  *(undefined1 *)((int)psVar3 + 5) = 0;
  return 1;
}



/* crt_chsize @ 0046dd16 */

/* resize file (truncate/extend via lseek + SetEndOfFile/zero fill) */

int __cdecl crt_chsize(int fd,int size)

{
  long offset;
  long lVar1;
  int iVar2;
  uint count;
  int iVar3;
  uint *puVar4;
  int *piVar5;
  void *hFile;
  WINBOOL WVar6;
  DWORD DVar7;
  int iVar8;
  uint uVar9;
  char local_1008 [4064];
  undefined4 uStackY_28;
  
  crt_chkstk();
  iVar8 = 0;
  offset = crt_lseek_nolock(fd,0,1);
  if ((offset == -1) || (lVar1 = crt_lseek_nolock(fd,0,2), lVar1 == -1)) {
    iVar8 = -1;
  }
  else {
    uVar9 = size - lVar1;
    if ((int)uVar9 < 1) {
      if ((int)uVar9 < 0) {
        crt_lseek_nolock(fd,size,0);
        hFile = crt_get_osfhandle(fd);
        WVar6 = SetEndOfFile(hFile);
        iVar8 = (WVar6 != 0) - 1;
        if (iVar8 == -1) {
          piVar5 = crt_errno_ptr();
          *piVar5 = 0xd;
          DVar7 = GetLastError();
          puVar4 = crt_doserrno_ptr();
          *puVar4 = DVar7;
        }
      }
    }
    else {
      _memset(local_1008,0,0x1000);
      uStackY_28 = 0x46dd83;
      iVar2 = crt_time_cvt(fd,0x8000);
      do {
        count = 0x1000;
        if ((int)uVar9 < 0x1000) {
          count = uVar9;
        }
        iVar3 = crt_write_nolock(fd,local_1008,count);
        if (iVar3 == -1) {
          puVar4 = crt_doserrno_ptr();
          if (*puVar4 == 5) {
            piVar5 = crt_errno_ptr();
            *piVar5 = 0xd;
          }
          iVar8 = -1;
          break;
        }
        uVar9 = uVar9 - iVar3;
      } while (0 < (int)uVar9);
      crt_time_cvt(fd,iVar2);
    }
    crt_lseek_nolock(fd,offset,0);
  }
  return iVar8;
}



/* crt_wide_int_format @ 0046de3b */

/* [binja] int16_t* sub_46de3b(int16_t* arg1, int32_t* arg2) */

short * __cdecl crt_wide_int_format(short *arg1,int *arg2)

{
  short *psVar1;
  short sVar2;
  int iVar3;
  short *psVar4;
  int *piVar5;
  short *psVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  uint uVar10;
  byte local_28;
  undefined1 uStack_27;
  short sStack_26;
  short local_24;
  undefined2 uStack_22;
  undefined2 local_20;
  undefined1 uStack_1e;
  byte bStack_1d;
  int *local_1c;
  int local_18;
  int local_14;
  ushort *local_10;
  ushort *local_c;
  short *local_8;
  
  piVar5 = arg2;
  psVar4 = arg1;
  local_18 = 0;
  local_28 = 0;
  uStack_27 = 0;
  sStack_26 = 0;
  local_24 = 0;
  uStack_22 = 0;
  local_20 = 0;
  uStack_1e = 0;
  bStack_1d = 0;
  psVar6 = (short *)((ushort)arg1[5] & 0x7fff);
  uVar9 = *(ushort *)((int)arg2 + 10) & 0x7fff;
  uVar10 = (ushort)(*(ushort *)((int)arg2 + 10) ^ arg1[5]) & 0x8000;
  psVar1 = (short *)(uVar9 + (int)psVar6);
  if ((((ushort)psVar6 < 0x7fff) && (uVar8 = (ushort)uVar9, uVar8 < 0x7fff)) &&
     ((ushort)psVar1 < 0xbffe)) {
    if ((ushort)psVar1 < 0x3fc0) {
LAB_0046dede:
      psVar4[4] = 0;
      psVar4[5] = 0;
      psVar4[2] = 0;
      psVar4[3] = 0;
      psVar4[0] = 0;
      psVar4[1] = 0;
      return (short *)0x0;
    }
    if ((((ushort)psVar6 != 0) ||
        (psVar1 = (short *)((int)psVar1 + 1), (*(uint *)(arg1 + 4) & 0x7fffffff) != 0)) ||
       ((psVar6 = (short *)0x0, *(int *)(arg1 + 2) != 0 || (*(int *)arg1 != 0)))) {
      arg1 = psVar1;
      if (((uVar8 == 0) && (arg1 = (short *)((int)arg1 + 1), (arg2[2] & 0x7fffffffU) == 0)) &&
         ((arg2[1] == 0 && (*arg2 == 0)))) goto LAB_0046dede;
      local_14 = 0;
      local_8 = &local_24;
      arg2 = (int *)0x5;
      do {
        if (0 < (int)arg2) {
          local_c = (ushort *)(psVar4 + local_14);
          local_10 = (ushort *)(piVar5 + 2);
          local_1c = arg2;
          do {
            iVar7 = crt_add_u32_carry(*(uint *)(local_8 + -2),(uint)*local_c * (uint)*local_10,
                                      (uint *)(local_8 + -2));
            if (iVar7 != 0) {
              *local_8 = *local_8 + 1;
            }
            local_c = local_c + 1;
            local_10 = local_10 + -1;
            local_1c = (int *)((int)local_1c + -1);
          } while (local_1c != (int *)0x0);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
        arg2 = (int *)((int)arg2 + -1);
      } while (0 < (int)arg2);
      arg1 = arg1 + 0x6001;
      if ((short)arg1 < 1) {
LAB_0046df92:
        arg1 = (short *)((int)arg1 + 0xffff);
        if ((short)arg1 < 0) {
          iVar7 = -(int)(short)arg1;
          arg1 = (short *)((int)arg1 + iVar7);
          do {
            if ((local_28 & 1) != 0) {
              local_18 = local_18 + 1;
            }
            crt_u96_shr1((uint *)&local_28);
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
          if (local_18 != 0) {
            local_28 = local_28 | 1;
          }
        }
      }
      else {
        do {
          if ((bStack_1d & 0x80) != 0) break;
          crt_u96_shl1((uint *)&local_28);
          arg1 = (short *)((int)arg1 + 0xffff);
        } while (0 < (short)arg1);
        if ((short)arg1 < 1) goto LAB_0046df92;
      }
      if ((0x8000 < CONCAT11(uStack_27,local_28)) ||
         (sVar2 = CONCAT11(bStack_1d,uStack_1e), iVar3 = CONCAT22(local_20,uStack_22),
         iVar7 = CONCAT22(local_24,sStack_26),
         (CONCAT22(sStack_26,CONCAT11(uStack_27,local_28)) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_24,sStack_26) == -1) {
          iVar7 = 0;
          if (CONCAT22(local_20,uStack_22) == -1) {
            if (CONCAT11(bStack_1d,uStack_1e) == -1) {
              arg1 = (short *)((int)arg1 + 1);
              sVar2 = -0x8000;
              iVar3 = 0;
              iVar7 = 0;
            }
            else {
              sVar2 = CONCAT11(bStack_1d,uStack_1e) + 1;
              iVar3 = 0;
              iVar7 = 0;
            }
          }
          else {
            sVar2 = CONCAT11(bStack_1d,uStack_1e);
            iVar3 = CONCAT22(local_20,uStack_22) + 1;
          }
        }
        else {
          iVar7 = CONCAT22(local_24,sStack_26) + 1;
          sVar2 = CONCAT11(bStack_1d,uStack_1e);
          iVar3 = CONCAT22(local_20,uStack_22);
        }
      }
      local_24 = (short)((uint)iVar7 >> 0x10);
      sStack_26 = (short)iVar7;
      local_20 = (undefined2)((uint)iVar3 >> 0x10);
      uStack_22 = (undefined2)iVar3;
      bStack_1d = (byte)((ushort)sVar2 >> 8);
      uStack_1e = (undefined1)sVar2;
      psVar6 = arg1;
      if (0x7ffe < (ushort)arg1) goto LAB_0046e03b;
      psVar6 = (short *)((uint)arg1 | uVar10);
      *psVar4 = sStack_26;
      *(uint *)(psVar4 + 1) = CONCAT22(uStack_22,local_24);
      *(uint *)(psVar4 + 3) = CONCAT13(bStack_1d,CONCAT12(uStack_1e,local_20));
    }
    psVar4[5] = (short)psVar6;
  }
  else {
LAB_0046e03b:
    psVar4[2] = 0;
    psVar4[3] = 0;
    psVar4[0] = 0;
    psVar4[1] = 0;
    *(uint *)(psVar4 + 4) = (-(uint)((short)uVar10 != 0) & 0x80000000) + 0x7fff8000;
  }
  return psVar6;
}



/* crt_wide_num_format @ 0046e05b */

void __cdecl crt_wide_num_format(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined **ppuVar3;
  undefined **arg2;
  undefined2 local_10;
  undefined4 local_e;
  undefined2 uStack_a;
  undefined *puStack_8;
  
  ppuVar3 = &PTR_s_November_0047e120;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      ppuVar3 = (undefined **)0x47e280;
    }
    if (param_3 == 0) {
      *(undefined2 *)param_1 = 0;
    }
    while (param_2 != 0) {
      ppuVar3 = ppuVar3 + 0x15;
      uVar1 = (int)param_2 >> 3;
      uVar2 = param_2 & 7;
      param_2 = uVar1;
      if (uVar2 != 0) {
        arg2 = ppuVar3 + uVar2 * 3;
        if (0x7fff < *(ushort *)(ppuVar3 + uVar2 * 3)) {
          local_10 = SUB42(*arg2,0);
          local_e._0_2_ = (undefined2)((uint)*arg2 >> 0x10);
          local_e._2_2_ = SUB42(arg2[1],0);
          uStack_a = (undefined2)((uint)arg2[1] >> 0x10);
          puStack_8 = arg2[2];
          local_e = CONCAT22(local_e._2_2_,(undefined2)local_e) + -1;
          arg2 = (undefined **)&local_10;
        }
        crt_wide_int_format((short *)param_1,(int *)arg2);
      }
    }
  }
  return;
}



/* crt_getenv @ 0046e0d7 */

int __cdecl crt_getenv(uchar *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  char **ppcVar3;
  
  if (((crt_environ_initialized != 0) &&
      ((crt_environ != (char **)0x0 ||
       (((crt_heap_descr_count != 0 && (iVar1 = crt_tzset_init(), iVar1 == 0)) &&
        (crt_environ != (char **)0x0)))))) && (ppcVar3 = crt_environ, param_1 != (uchar *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; *ppcVar3 != (char *)0x0; ppcVar3 = ppcVar3 + 1) {
      sVar2 = _strlen(*ppcVar3);
      if (((_MaxCount < sVar2) && ((*ppcVar3)[_MaxCount] == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*ppcVar3,param_1,_MaxCount), iVar1 == 0)) {
        return (int)(*ppcVar3 + _MaxCount + 1);
      }
    }
  }
  return 0;
}



/* FUN_0046e160 @ 0046e160 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [binja] int32_t sub_46e160(char* arg1, char* arg2, int32_t arg3) */

int __cdecl FUN_0046e160(char *arg1,char *arg2,int arg3)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  uint uVar5;
  void *locale;
  int iVar6;
  void *this;
  void *locale_00;
  bool bVar7;
  
  iVar2 = _crt_lock_count;
  iVar6 = 0;
  if (arg3 != 0) {
    if (crt_locale_id == 0) {
      do {
        bVar3 = *arg1;
        cVar1 = *arg2;
        uVar4 = CONCAT11(bVar3,cVar1);
        if (bVar3 == 0) break;
        uVar4 = CONCAT11(bVar3,cVar1);
        uVar5 = (uint)uVar4;
        if (cVar1 == '\0') break;
        arg1 = (char *)((byte *)arg1 + 1);
        arg2 = arg2 + 1;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar5 = (uint)CONCAT11(bVar3 + 0x20,cVar1);
        }
        uVar4 = (ushort)uVar5;
        bVar3 = (byte)uVar5;
        if ((0x40 < bVar3) && (bVar3 < 0x5b)) {
          uVar4 = (ushort)CONCAT31((int3)(uVar5 >> 8),bVar3 + 0x20);
        }
        bVar3 = (byte)(uVar4 >> 8);
        bVar7 = bVar3 < (byte)uVar4;
        if (bVar3 != (byte)uVar4) goto LAB_0046e1bf;
        arg3 = arg3 + -1;
      } while (arg3 != 0);
      iVar6 = 0;
      bVar3 = (byte)(uVar4 >> 8);
      bVar7 = bVar3 < (byte)uVar4;
      if (bVar3 != (byte)uVar4) {
LAB_0046e1bf:
        iVar6 = -1;
        if (!bVar7) {
          iVar6 = 1;
        }
      }
    }
    else {
      LOCK();
      _crt_lock_count = _crt_lock_count + 1;
      UNLOCK();
      bVar7 = 0 < crt_sbh_reserved_a;
      if (bVar7) {
        LOCK();
        UNLOCK();
        _crt_lock_count = iVar2;
        crt_lock(0x13);
      }
      uVar5 = (uint)bVar7;
      locale = (void *)0x0;
      locale_00 = (void *)0x0;
      do {
        locale = (void *)CONCAT31((int3)((uint)locale >> 8),*arg1);
        locale_00 = (void *)CONCAT31((int3)((uint)locale_00 >> 8),*arg2);
        if ((locale == (void *)0x0) || (locale_00 == (void *)0x0)) break;
        arg1 = arg1 + 1;
        arg2 = arg2 + 1;
        locale_00 = (void *)crt_tolower_l((void *)arg3,locale_00,(int)locale);
        locale = (void *)crt_tolower_l(this,locale,arg3);
        bVar7 = locale < locale_00;
        if (locale != locale_00) goto LAB_0046e235;
        arg3 = arg3 + -1;
      } while ((void *)arg3 != (void *)0x0);
      iVar6 = 0;
      bVar7 = locale < locale_00;
      if (locale != locale_00) {
LAB_0046e235:
        iVar6 = -1;
        if (!bVar7) {
          iVar6 = 1;
        }
      }
      if (uVar5 == 0) {
        LOCK();
        _crt_lock_count = _crt_lock_count + -1;
        UNLOCK();
      }
      else {
        crt_unlock(0x13);
      }
    }
  }
  return iVar6;
}



/* crt_time_cvt @ 0046e261 */

int __cdecl crt_time_cvt(uint param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  byte bVar3;
  
  bVar1 = *(byte *)((&crt_pioinfo_table)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1);
  if (param_2 == 0x8000) {
    bVar3 = bVar1 & 0x7f;
  }
  else {
    if (param_2 != 0x4000) {
      piVar2 = crt_errno_ptr();
      *piVar2 = 0x16;
      return -1;
    }
    bVar3 = bVar1 | 0x80;
  }
  *(byte *)((&crt_pioinfo_table)[(int)param_1 >> 5] + (param_1 & 0x1f) * 9 + 1) = bVar3;
  return (-(uint)((bVar1 & 0x80) != 0) & 0xffffc000) + 0x8000;
}



/* __mbsnbicoll @ 0046e2c2 */

/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  int iVar1;
  
  if (_MaxCount == 0) {
    return 0;
  }
  iVar1 = crt_lcmap_string_wrapper(crt_sbh_active_flag,1,_Str1,_MaxCount,_Str2,_MaxCount,crt_heap_lock_flag);
  if (iVar1 == 0) {
    return 0x7fffffff;
  }
  return iVar1 + -2;
}



/* crt_tzset_init @ 0046e301 */

/* [binja] int32_t sub_46e301() */

int crt_tzset_init(void)

{
  LPCWCH lpWideCharStr;
  size_t _Size;
  char *lpMultiByteStr;
  int iVar1;
  undefined4 *puVar2;
  
  lpWideCharStr = (LPCWCH)*crt_heap_descr_count;
  puVar2 = crt_heap_descr_count;
  while( true ) {
    if (lpWideCharStr == (LPCWCH)0x0) {
      return 0;
    }
    _Size = WideCharToMultiByte(1,0,lpWideCharStr,-1,(LPSTR)0x0,0,(LPCCH)0x0,(LPBOOL)0x0);
    if (((_Size == 0) || (lpMultiByteStr = _malloc(_Size), lpMultiByteStr == (char *)0x0)) ||
       (iVar1 = WideCharToMultiByte(1,0,(LPCWCH)*puVar2,-1,lpMultiByteStr,_Size,(LPCCH)0x0,
                                    (LPBOOL)0x0), iVar1 == 0)) break;
    crt_environ_set(lpMultiByteStr,0);
    lpWideCharStr = (LPCWCH)puVar2[1];
    puVar2 = puVar2 + 1;
  }
  return -1;
}



/* crt_lcmap_string_wrapper @ 0046e36f */

int __cdecl
crt_lcmap_string_wrapper(LCID param_1,DWORD param_2,byte *param_3,int param_4,byte *param_5,int param_6,
            UINT param_7)

{
  undefined1 *puVar1;
  int iVar2;
  WINBOOL WVar3;
  BYTE *pBVar4;
  int iVar5;
  _cpinfo local_40;
  undefined1 *local_2c;
  PCNZWCH local_28;
  int local_24;
  int local_20;
  undefined1 *local_1c;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004701b8;
  puStack_10 = &LAB_00465e70;
  local_14 = ExceptionList;
  local_1c = &stack0xffffffb0;
  ExceptionList = &local_14;
  puVar1 = &stack0xffffffb0;
  if (crt_tls_index == 0) {
    ExceptionList = &local_14;
    iVar2 = CompareStringW(0,0,L"",1,L"",1);
    if (iVar2 == 0) {
      iVar2 = CompareStringA(0,0,&crt_winver,1,&crt_winver,1);
      if (iVar2 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      crt_tls_index = 2;
      puVar1 = local_1c;
    }
    else {
      crt_tls_index = 1;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  if (0 < param_4) {
    param_4 = crt_environ_expand((char *)param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = crt_environ_expand((char *)param_5,param_6);
  }
  if (crt_tls_index == 2) {
    iVar2 = CompareStringA(param_1,param_2,(PCNZCH)param_3,param_4,(PCNZCH)param_5,param_6);
    ExceptionList = local_14;
    return iVar2;
  }
  if (crt_tls_index == 1) {
    if (param_7 == 0) {
      param_7 = crt_acp_codepage;
    }
    if ((param_4 == 0) || (param_6 == 0)) {
      if (param_4 == param_6) {
        ExceptionList = local_14;
        return 2;
      }
      if (1 < param_6) {
        ExceptionList = local_14;
        return 1;
      }
      if (1 < param_4) {
        ExceptionList = local_14;
        return 3;
      }
      WVar3 = GetCPInfo(param_7,&local_40);
      if (WVar3 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      if (0 < param_4) {
        if (local_40.MaxCharSize < 2) {
          ExceptionList = local_14;
          return 3;
        }
        pBVar4 = local_40.LeadByte;
        while( true ) {
          if (local_40.LeadByte[0] == 0) {
            ExceptionList = local_14;
            return 3;
          }
          if (pBVar4[1] == 0) break;
          if ((*pBVar4 <= *param_3) && (*param_3 <= pBVar4[1])) {
            ExceptionList = local_14;
            return 2;
          }
          pBVar4 = pBVar4 + 2;
          local_40.LeadByte[0] = *pBVar4;
        }
        ExceptionList = local_14;
        return 3;
      }
      if (0 < param_6) {
        if (local_40.MaxCharSize < 2) {
          ExceptionList = local_14;
          return 1;
        }
        pBVar4 = local_40.LeadByte;
        while( true ) {
          if (local_40.LeadByte[0] == 0) {
            ExceptionList = local_14;
            return 1;
          }
          if (pBVar4[1] == 0) break;
          if ((*pBVar4 <= *param_5) && (*param_5 <= pBVar4[1])) {
            ExceptionList = local_14;
            return 2;
          }
          pBVar4 = pBVar4 + 2;
          local_40.LeadByte[0] = *pBVar4;
        }
        ExceptionList = local_14;
        return 1;
      }
    }
    local_20 = MultiByteToWideChar(param_7,9,(LPCCH)param_3,param_4,(LPWSTR)0x0,0);
    if (local_20 != 0) {
      local_8 = 0;
      crt_chkstk();
      local_8 = 0xffffffff;
      if ((&stack0x00000000 != (undefined1 *)0x50) &&
         (local_28 = (PCNZWCH)&stack0xffffffb0, local_1c = &stack0xffffffb0,
         iVar2 = MultiByteToWideChar(param_7,1,(LPCCH)param_3,param_4,(LPWSTR)&stack0xffffffb0,
                                     local_20), iVar2 != 0)) {
        iVar2 = MultiByteToWideChar(param_7,9,(LPCCH)param_5,param_6,(LPWSTR)0x0,0);
        if (iVar2 != 0) {
          local_8 = 1;
          local_24 = iVar2;
          crt_chkstk();
          local_8 = 0xffffffff;
          if ((&stack0x00000000 != (undefined1 *)0x50) &&
             (local_2c = &stack0xffffffb0, local_1c = &stack0xffffffb0,
             iVar5 = MultiByteToWideChar(param_7,1,(LPCCH)param_5,param_6,(LPWSTR)&stack0xffffffb0,
                                         iVar2), iVar5 != 0)) {
            iVar2 = CompareStringW(param_1,param_2,local_28,local_20,(PCNZWCH)&stack0xffffffb0,iVar2
                                  );
            ExceptionList = local_14;
            return iVar2;
          }
        }
      }
    }
  }
  ExceptionList = local_14;
  return 0;
}



/* crt_environ_expand @ 0046e5ec */

int __cdecl crt_environ_expand(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = param_2;
  for (pcVar1 = param_1; (iVar2 != 0 && (iVar2 = iVar2 + -1, *pcVar1 != '\0')); pcVar1 = pcVar1 + 1)
  {
  }
  if (*pcVar1 != '\0') {
    return param_2;
  }
  return (int)pcVar1 - (int)param_1;
}



/* crt_environ_set @ 0046e617 */

/* [binja] int32_t sub_46e617(char* arg1, int32_t arg2) */

int __cdecl crt_environ_set(char *arg1,int arg2)

{
  byte *pbVar1;
  int iVar2;
  char **ppcVar3;
  size_t sVar4;
  char *dst;
  char **ppcVar5;
  bool bVar6;
  
  if (arg1 == (char *)0x0) {
    return -1;
  }
  pbVar1 = crt_strchr_byte((byte *)arg1,0x3d);
  if (pbVar1 == (byte *)0x0) {
    return -1;
  }
  if ((byte *)arg1 == pbVar1) {
    return -1;
  }
  bVar6 = pbVar1[1] == 0;
  if (crt_environ == DAT_004d99a4) {
    crt_environ = crt_environ_grow((int *)crt_environ);
  }
  if (crt_environ == (char **)0x0) {
    if ((arg2 == 0) || (crt_heap_descr_count == (undefined4 *)0x0)) {
      if (bVar6) {
        return 0;
      }
      crt_environ = _malloc(4);
      if (crt_environ == (char **)0x0) {
        return -1;
      }
      *crt_environ = (char *)0x0;
      if (crt_heap_descr_count == (undefined4 *)0x0) {
        crt_heap_descr_count = _malloc(4);
        if (crt_heap_descr_count == (undefined4 *)0x0) {
          return -1;
        }
        *crt_heap_descr_count = 0;
      }
    }
    else {
      iVar2 = crt_tzset_init();
      if (iVar2 != 0) {
        return -1;
      }
    }
  }
  ppcVar3 = crt_environ;
  iVar2 = crt_environ_find((uchar *)arg1,(int)pbVar1 - (int)arg1);
  if ((iVar2 < 0) || (*ppcVar3 == (char *)0x0)) {
    if (bVar6) {
      return 0;
    }
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    ppcVar3 = crt_realloc(ppcVar3,iVar2 * 4 + 8);
    if (ppcVar3 == (char **)0x0) {
      return -1;
    }
    ppcVar3[iVar2] = arg1;
    ppcVar3[iVar2 + 1] = (char *)0x0;
  }
  else {
    if (!bVar6) {
      ppcVar3[iVar2] = arg1;
      goto LAB_0046e74b;
    }
    ppcVar5 = ppcVar3 + iVar2;
    crt_free_base(ppcVar3[iVar2]);
    for (; *ppcVar5 != (char *)0x0; ppcVar5 = ppcVar5 + 1) {
      iVar2 = iVar2 + 1;
      *ppcVar5 = ppcVar5[1];
    }
    ppcVar3 = crt_realloc(ppcVar3,iVar2 << 2);
    if (ppcVar3 == (char **)0x0) goto LAB_0046e74b;
  }
  crt_environ = ppcVar3;
LAB_0046e74b:
  if (arg2 != 0) {
    sVar4 = _strlen(arg1);
    dst = _malloc(sVar4 + 2);
    if (dst != (char *)0x0) {
      crt_strcpy(dst,arg1);
      pbVar1[(int)dst - (int)arg1] = 0;
      SetEnvironmentVariableA
                (dst,(LPCSTR)(~-(uint)bVar6 & (uint)(pbVar1 + ((int)dst - (int)arg1) + 1)));
      crt_free_base(dst);
    }
  }
  return 0;
}



/* crt_environ_find @ 0046e79e */

int __cdecl crt_environ_find(uchar *param_1,size_t param_2)

{
  uchar *_Str2;
  int iVar1;
  char **ppcVar2;
  
  _Str2 = (uchar *)*crt_environ;
  ppcVar2 = crt_environ;
  while( true ) {
    if (_Str2 == (uchar *)0x0) {
      return -((int)ppcVar2 - (int)crt_environ >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,_Str2,param_2);
    if ((iVar1 == 0) && (((*ppcVar2)[param_2] == '=' || ((*ppcVar2)[param_2] == '\0')))) break;
    _Str2 = (uchar *)ppcVar2[1];
    ppcVar2 = ppcVar2 + 1;
  }
  return (int)ppcVar2 - (int)crt_environ >> 2;
}



/* crt_environ_grow @ 0046e7f6 */

/* [binja] void* sub_46e7f6(int32_t* arg1) */

void * __cdecl crt_environ_grow(int *arg1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  
  iVar5 = 0;
  if (arg1 != (int *)0x0) {
    iVar1 = *arg1;
    piVar2 = arg1;
    while (iVar1 != 0) {
      piVar2 = piVar2 + 1;
      iVar5 = iVar5 + 1;
      iVar1 = *piVar2;
    }
    puVar3 = _malloc(iVar5 * 4 + 4);
    if (puVar3 == (undefined4 *)0x0) {
      __amsg_exit(9);
    }
    pcVar4 = (char *)*arg1;
    puVar6 = puVar3;
    while (pcVar4 != (char *)0x0) {
      arg1 = arg1 + 1;
      pcVar4 = strdup_malloc(pcVar4);
      *puVar6 = pcVar4;
      puVar6 = puVar6 + 1;
      pcVar4 = (char *)*arg1;
    }
    *puVar6 = 0;
    return puVar3;
  }
  return (void *)0x0;
}



/* crt_strchr_byte @ 0046e85d */

byte * __cdecl crt_strchr_byte(byte *param_1,uint param_2)

{
  byte bVar1;
  byte *pbVar2;
  uint uVar3;
  
  if (crt_sbh_region_count == 0) {
    pbVar2 = (byte *)_strchr((char *)param_1,param_2);
  }
  else {
    crt_lock(0x19);
    while( true ) {
      bVar1 = *param_1;
      uVar3 = (uint)bVar1;
      if (bVar1 == 0) break;
      if ((*(byte *)((int)&crt_char_type_table + uVar3 + 1) & 4) == 0) {
        pbVar2 = param_1;
        if (param_2 == uVar3) break;
      }
      else {
        pbVar2 = param_1 + 1;
        if (param_1[1] == 0) {
          crt_unlock(0x19);
          return (byte *)0x0;
        }
        if (param_2 == CONCAT11(bVar1,param_1[1])) {
          crt_unlock(0x19);
          return param_1;
        }
      }
      param_1 = pbVar2 + 1;
    }
    crt_unlock(0x19);
    pbVar2 = (byte *)(~-(uint)(param_2 != uVar3) & (uint)param_1);
  }
  return pbVar2;
}



/* strdup_malloc @ 0046e8f4 */

/* malloc+copy helper */

char * __cdecl strdup_malloc(char *src)

{
  size_t sVar1;
  char *pcVar2;
  
  if (src != (char *)0x0) {
    sVar1 = _strlen(src);
    pcVar2 = _malloc(sVar1 + 1);
    if (pcVar2 != (char *)0x0) {
      pcVar2 = crt_strcpy(pcVar2,src);
      return pcVar2;
    }
  }
  return (char *)0x0;
}



