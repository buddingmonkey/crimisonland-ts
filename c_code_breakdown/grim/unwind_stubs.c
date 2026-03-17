/* `vector_deleting_destructor' @ 1000b2fd */

/* Library Function - Single Match
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 2003 Release */

void * __thiscall CODBCFieldInfo::_vector_deleting_destructor_(CODBCFieldInfo *this,uint param_1)

{
  CODBCFieldInfo *pCVar1;
  
  if ((param_1 & 2) == 0) {
    grim_zip_reader_close((char *)this);
    pCVar1 = this;
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    pCVar1 = this + -4;
    grim_crt_buffer_alloc((int)this,0x10,*(int *)pCVar1,0x100161b6);
    if ((param_1 & 1) != 0) {
      operator_delete(pCVar1);
    }
  }
  return pCVar1;
}



/* FID_conflict:`vector_deleting_destructor' @ 1000b348 */

/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall ATL::CStringT<char,class StrTraitMFC<char,class ATL::ChTraitsCRT<char>
   > >::`vector deleting destructor'(unsigned int)
    public: void * __thiscall ATL::CStringT<wchar_t,class StrTraitMFC<wchar_t,class
   ATL::ChTraitsCRT<wchar_t> > >::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 2003 Release */

int * __thiscall FID_conflict__vector_deleting_destructor_(void *this,byte param_1)

{
  int *piVar1;
  
  if ((param_1 & 2) == 0) {
    thunk_grim_zip_buffer_free(this);
    piVar1 = this;
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    piVar1 = (int *)((int)this + -4);
    grim_crt_buffer_alloc((int)this,4,*piVar1,0x100165ce);
    if ((param_1 & 1) != 0) {
      operator_delete(piVar1);
    }
  }
  return piVar1;
}



/* `vector_constructor_iterator' @ 1000b393 */

/* Library Function - Single Match
    void __stdcall `vector constructor iterator'(void *,unsigned int,int,void * (__thiscall*)(void
   *))
   
   Library: Visual Studio 2003 Release */

void _vector_constructor_iterator_
               (void *param_1,uint param_2,int param_3,_func_void_ptr_void_ptr *param_4)

{
  void *unaff_EDI;
  
  if (-1 < param_3 + -1) {
    do {
      (*param_4)(unaff_EDI);
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}



/* Catch@1001c069 @ 1001c069 */

undefined * Catch_1001c069(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -0x3c) = *(undefined4 *)(unaff_EBP + -0x14);
  return &DAT_1001c07b;
}



/* seh_prolog @ 1004b5b0 */

/* MSVC SEH prolog helper (sets FS:[0]) */

void seh_prolog(void)

{
  undefined1 auStack_c [12];
  
  ExceptionList = auStack_c;
  return;
}



/* __aullshr @ 1004b770 */

/* Library Function - Single Match
    __aullshr
   
   Library: Visual Studio */

ulonglong __fastcall __aullshr(byte param_1,uint param_2)

{
  uint in_EAX;
  
  if (0x3f < param_1) {
    return 0;
  }
  if (param_1 < 0x20) {
    return CONCAT44(param_2 >> (param_1 & 0x1f),
                    in_EAX >> (param_1 & 0x1f) | param_2 << 0x20 - (param_1 & 0x1f));
  }
  return (ulonglong)(param_2 >> (param_1 & 0x1f));
}



/* Unwind@1004b7e0 @ 1004b7e0 */

void Unwind_1004b7e0(void)

{
  grim_noop();
  return;
}



/* Unwind@1004b800 @ 1004b800 */

void Unwind_1004b800(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 4));
  return;
}



/* Unwind@1004b820 @ 1004b820 */

void Unwind_1004b820(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 0xc));
  return;
}



/* Unwind@1004b835 @ 1004b835 */

void Unwind_1004b835(void)

{
  int unaff_EBP;
  
  grim_file_stream_close((void *)(unaff_EBP + -0x70));
  return;
}



/* Unwind@1004b83d @ 1004b83d */

void Unwind_1004b83d(void)

{
  int unaff_EBP;
  
  grim_zip_reader_close((char *)(unaff_EBP + -0x1c));
  return;
}



/* Unwind@1004b84f @ 1004b84f */

void Unwind_1004b84f(void)

{
  int unaff_EBP;
  
  grim_file_stream_close((void *)(unaff_EBP + -0x98));
  return;
}



/* Unwind@1004b85a @ 1004b85a */

void Unwind_1004b85a(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x2c));
  return;
}



/* Unwind@1004b864 @ 1004b864 */

void Unwind_1004b864(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x28));
  return;
}



/* Unwind@1004b86e @ 1004b86e */

void Unwind_1004b86e(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x34));
  return;
}



/* Unwind@1004b878 @ 1004b878 */

void Unwind_1004b878(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x44));
  return;
}



/* Unwind@1004b88c @ 1004b88c */

void Unwind_1004b88c(void)

{
  int unaff_EBP;
  
  grim_file_stream_close((void *)(unaff_EBP + -0x8c));
  return;
}



/* Unwind@1004b8a1 @ 1004b8a1 */

void Unwind_1004b8a1(void)

{
  int unaff_EBP;
  
  grim_registry_read_config((int *)(unaff_EBP + -0x3c));
  return;
}



/* Unwind@1004b8a9 @ 1004b8a9 */

void Unwind_1004b8a9(void)

{
  int unaff_EBP;
  
  grim_alloc_context_free((int *)(unaff_EBP + -0x2c));
  return;
}



/* Unwind@1004b8bb @ 1004b8bb */

void Unwind_1004b8bb(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x54));
  return;
}



/* Unwind@1004b8c5 @ 1004b8c5 */

void Unwind_1004b8c5(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x5c));
  return;
}



/* Unwind@1004b8cf @ 1004b8cf */

void Unwind_1004b8cf(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x48));
  return;
}



/* Unwind@1004b8e3 @ 1004b8e3 */

void Unwind_1004b8e3(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x10));
  return;
}



/* Unwind@1004b8f7 @ 1004b8f7 */

void Unwind_1004b8f7(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b901 @ 1004b901 */

void Unwind_1004b901(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b915 @ 1004b915 */

void Unwind_1004b915(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x30));
  return;
}



/* Unwind@1004b91f @ 1004b91f */

void Unwind_1004b91f(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x30));
  return;
}



/* Unwind@1004b933 @ 1004b933 */

void Unwind_1004b933(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x2c));
  return;
}



/* Unwind@1004b93d @ 1004b93d */

void Unwind_1004b93d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x2c));
  return;
}



/* Unwind@1004b947 @ 1004b947 */

void Unwind_1004b947(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x2c));
  return;
}



/* Unwind@1004b95b @ 1004b95b */

void Unwind_1004b95b(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b965 @ 1004b965 */

void Unwind_1004b965(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b96f @ 1004b96f */

void Unwind_1004b96f(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b983 @ 1004b983 */

void Unwind_1004b983(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b98d @ 1004b98d */

void Unwind_1004b98d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x1c));
  return;
}



/* Unwind@1004b9a1 @ 1004b9a1 */

void Unwind_1004b9a1(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x44));
  return;
}



/* Unwind@1004b9ab @ 1004b9ab */

void Unwind_1004b9ab(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x30));
  return;
}



/* Unwind@1004b9bf @ 1004b9bf */

void Unwind_1004b9bf(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x40));
  return;
}



/* Unwind@1004b9c9 @ 1004b9c9 */

void Unwind_1004b9c9(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x3c));
  return;
}



/* Unwind@1004b9d3 @ 1004b9d3 */

void Unwind_1004b9d3(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x40));
  return;
}



/* Unwind@1004b9e7 @ 1004b9e7 */

void Unwind_1004b9e7(void)

{
  int unaff_EBP;
  
  grim_vertex_space_converter_destroy(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004b9f9 @ 1004b9f9 */

void Unwind_1004b9f9(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004ba0d @ 1004ba0d */

void Unwind_1004ba0d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x10));
  return;
}



/* Unwind@1004ba21 @ 1004ba21 */

void Unwind_1004ba21(void)

{
  int unaff_EBP;
  
  grim_vertex_space_converter_destroy(*(void **)(unaff_EBP + -0x14));
  return;
}



/* Unwind@1004ba29 @ 1004ba29 */

void Unwind_1004ba29(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x10));
  return;
}



/* Unwind@1004ba3d @ 1004ba3d */

void Unwind_1004ba3d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + -0x24));
  return;
}



/* Unwind@1004ba51 @ 1004ba51 */

void Unwind_1004ba51(void)

{
  int unaff_EBP;
  
  grim_vertex_space_converter_destroy(*(void **)(unaff_EBP + -0x10));
  return;
}



/* Unwind@1004ba63 @ 1004ba63 */

void Unwind_1004ba63(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba6d @ 1004ba6d */

void Unwind_1004ba6d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba77 @ 1004ba77 */

void Unwind_1004ba77(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba81 @ 1004ba81 */

void Unwind_1004ba81(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba8b @ 1004ba8b */

void Unwind_1004ba8b(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba95 @ 1004ba95 */

void Unwind_1004ba95(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004ba9f @ 1004ba9f */

void Unwind_1004ba9f(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004baa9 @ 1004baa9 */

void Unwind_1004baa9(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bab3 @ 1004bab3 */

void Unwind_1004bab3(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004babd @ 1004babd */

void Unwind_1004babd(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bac7 @ 1004bac7 */

void Unwind_1004bac7(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bad1 @ 1004bad1 */

void Unwind_1004bad1(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004badb @ 1004badb */

void Unwind_1004badb(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bae5 @ 1004bae5 */

void Unwind_1004bae5(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004baef @ 1004baef */

void Unwind_1004baef(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004baf9 @ 1004baf9 */

void Unwind_1004baf9(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb03 @ 1004bb03 */

void Unwind_1004bb03(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb0d @ 1004bb0d */

void Unwind_1004bb0d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb17 @ 1004bb17 */

void Unwind_1004bb17(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb21 @ 1004bb21 */

void Unwind_1004bb21(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb2b @ 1004bb2b */

void Unwind_1004bb2b(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb35 @ 1004bb35 */

void Unwind_1004bb35(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb3f @ 1004bb3f */

void Unwind_1004bb3f(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb49 @ 1004bb49 */

void Unwind_1004bb49(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb53 @ 1004bb53 */

void Unwind_1004bb53(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb5d @ 1004bb5d */

void Unwind_1004bb5d(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb67 @ 1004bb67 */

void Unwind_1004bb67(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb71 @ 1004bb71 */

void Unwind_1004bb71(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb7b @ 1004bb7b */

void Unwind_1004bb7b(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb85 @ 1004bb85 */

void Unwind_1004bb85(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb8f @ 1004bb8f */

void Unwind_1004bb8f(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bb99 @ 1004bb99 */

void Unwind_1004bb99(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bba3 @ 1004bba3 */

void Unwind_1004bba3(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bbad @ 1004bbad */

void Unwind_1004bbad(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bbb7 @ 1004bbb7 */

void Unwind_1004bbb7(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bbc1 @ 1004bbc1 */

void Unwind_1004bbc1(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}



/* Unwind@1004bbcb @ 1004bbcb */

void Unwind_1004bbcb(void)

{
  int unaff_EBP;
  
  operator_delete(*(void **)(unaff_EBP + 8));
  return;
}






