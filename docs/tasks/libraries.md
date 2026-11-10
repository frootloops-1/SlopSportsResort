# Libraries (RVL SDK, NW4R, EGG, MSL, MetroTRK, BTE, RFL, HBM)

## Current state

- 2026-11-09 near-port lane (lib-nearport, +22 Matching: GXPixel, GXGeometry, GXInit, OSError, OSCache, OSMessage, OSAlarm,
  SIBios, NANDCheck, mem_heapCommon, ipcProfile, mtx44, pf_clib, pdm_dskmng, g3d_scnproc/camera/xsi/resdict/resanmchr/restex/
  light): changed functions rewritten from Resort asm. Recipes: the linker dead-strips unreferenced functions, so ogws-only
  extras (OSReport, OSJamMessage, L2*, swap-table fns) may stay in the source but a weak/duplicate copy that Resort emits
  elsewhere must be removed (OSReport); the unit text end 4/8/12 bytes short means the next split needs `align:16` (asm
  neighbour) or, for a compiled ported neighbour, `-func_align 16` on its cflags (g3d_reslightset), or carve the auto code
  as unk/text_<addr>.cpp align:16; compile with Wii/1.0 when the scan is equal (16-byte function alignment); static
  .bss neighbour with align 32 needs `align:32` on its .bss split (mem_heapCommon). Version strings differ (GXInit, SIBios:
  "Feb 27 2009 ... (0x4302_145)"). `tools/port_flip_ext.py` now ignores weak fns >0x1000 away and keeps the split's own
  range for unlocated .bss/.ctors. Parked: g3d_anmvis (TestExistence must be an out-of-line weak emitted last; needs
  TYPE_NAME/vtable renames, rodata carve unk/rodata_806616F0, ResAnmVisData +4 word, UpdateFrame rate guard), g3d_restev
  (GXSetTevAlphaIn/GXSetTevOrder rewritten but not matching), math_arithmetic (Bezier schedule), d_hash (_MakeWStr regalloc),
  OSPlayRecord (Block .bss 4-aligned in Resort, 8-aligned by the compiler), g3d_state (extra .sbss/.data, big rewrite).
- 2026-11-09 flip sweep 3 (+13 Matching, 107 ported entries): mem_frameHeap, nettime, NMWException, MSL math_api/mem/
  strtoul/uart_console_io_gcn (need `-func_align 4 -Cpp_exceptions off`; Resort MSL has no extab), bte_hcisu,
  OSArena, OSMutex, OSStateFlags, pf_filelock, pf_system (object 4-12 bytes short: next split `align:16`, new
  unk/text_8004C4B0, unk/text_80050C20, unk/text_800D10A0). New `tools/port_flip_ext.py` (extab lookup, byte-matched
  data; run port_sizecheck after). Still failing: size differs (ipcProfile, mtx44, OSMessage, AXAlloc, AXFXReverbHi,
  ef_handle, lyt_resourceAccessor; buffer_io +8, file_io +0xC0, FILE_POS +4, RFL_DataUtility +0x6C); data size
  disagrees (WUDHidHost, gki_ppc, MSL/alloc, GXFrameBuf, NANDCheck); SIBios .data bytes; extab size (RFL_MakeRandomFace,
  eggMath); overlap (btm_devctl, g3d_obj, eggDvdFile); ~25 with data not located (runtime ptmf/global_destructor_chain/
  __init_cpp_exceptions, EXIBios, AX, 11 BTE, ansi_files, mbstring, pf_code, ut_FileStream, ef_draworder, g3d_anmobj,
  lyt_init); EGG units needing include/egg edits (eggAudioExpMgr). 19 header-blocked units not attempted.
- 2026-11-09 rescan after split recovery (453 ogws-sourced splits, was 295): 92 fully exact; 48 flipped,
  13 kept (gki_buffer, bta_sys_conn, bta_dm_api, btm_inq, l2c_api, rfc_ts_frames, TPL, g3d_tmem, g3d_3dsmax,
  GXTransform, bte_logmsg, sdp_utils, g3d_rescommon; the last 4 with `align:16` on the next split). Dropped and why:
  object .text larger or smaller than Resort's split (`tools/port_sizecheck.py`): ipcProfile, mtx44, OSArena,
  OSMessage, OSMutex, OSStateFlags, AXAlloc, AXFXReverbHi, bte_hcisu, lyt_resourceAccessor, pf_system, ef_handle,
  snd_AnimSound, g3d_camera, g3d_xsi, lyt_drawInfo, eggDisposer, SIBios, pf_filelock, OSCache; one function short:
  OSAlarm (fn_80045700 uses AlarmQueue), g3d_resdict (ResDic::GetIndex(const char*)); link: MetroTRK/gamedev/main.c,
  g3d_maya, math_arithmetic, AXSPB, bta_dm_pm, bta_sys_main (+4); cycle: AXVPB; .bss: mem_heapCommon.
  42 more skipped by port_flip (extab/extabindex or a small data section not located).
- 82 units Matching, ported from ogws source (2026-11-09: +6 data-blocked, +11 of the 19 header-blocked; fixes in `docs/porting.md` "Fixing a port_flip link/split failure") (`config/RZTE01_01/ported_objects.json`, per-object compiler + flags);
  `revolution/BTE/stack/hcic/hcicmds.c` is in configure.py's `RVL_SDK` lib.
- 130 ogws-sourced units scanned fully exact (`build/port_full.json` after `tools/port_scan.py`); the other 65 and why
  are listed in `docs/porting.md`:
  - 19 compile only with scratch-only workarounds on Wii/1.0 (header issues: float/`offsetof` constant expressions,
    access checks, C typedef redeclarations, `VERSION_RSPE01_*` branches).
  - 31 have a data section the `.text` relocations do not reach (vtables/tables only).
  - the rest broke link, layout or the DOL (`OSCache.c` asm functions are 16-byte padded in Resort;
    `mem_heapCommon.c` `.bss` range 0x18 too large).
- 51 more units scanned >= 80% with no missing functions: tier-C candidates.
- Data ownership now covers most library data (`tools/data_assign.py`), which should unblock part of the 31.

## Next

1. Blocked list re-checked: the other 22 units with located data are header-error units (step 2) or OSCache.
   The rest still miss small sections (extab/extabindex for MSL/RFL/eggMath, `.rodata`/`.sdata` of 1-96 bytes):
   locate by hand from data references, then the same per-unit fixes.
2. Header work done (all 19 compile). 8 left with per-unit layout causes (`docs/porting.md`); math_arithmetic
   needs 4 new float functions written (decomp-standard/hard worker).
3. Tier-C batch over the >= 80% list.
