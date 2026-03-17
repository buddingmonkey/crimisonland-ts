/* grim_sound_init @ 1000e530 */

void grim_sound_init(void)

{
  grim_select_renderer_backend(1);
                    /* WARNING: Could not recover jumptable at 0x1000e53b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_10053cf4)();
  return;
}


