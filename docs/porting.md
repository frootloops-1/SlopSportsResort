# Porting ogws source into Resort

Pipeline: `compiler_sweep.sh` (pick compiler) -> `port_scan.py` (compile every ogws-sourced split with ogws's compiler and Wii/1.0, score) -> `port_flip.py` (locate data sections, write `config/RZTE01_01/ported_objects.json`) -> `ninja` + `port_sizecheck.py PRE_FLIP_PORTED` (drop units whose object .text size differs; skip `build/port_excluded.json`) -> `fix_split_ends.py`, `trim_text_ends.py` -> `resolve_externs.py` (name symbols the source expects) -> build; `link_gate.py`, `layout_check.py`, `dol_blame.py` find the unit to drop when the link or DOL breaks.

Status: 82 units Matching and linked (17 added 2026-11-09 from the blocked list), DOL matches `build.sha1`. 130 units scanned fully exact; 65 not ported yet:

## Formerly Wii/1.0 compile errors (8 left; all 19 compile since 2026-11-09)

Cause was `-DVERSION_RSPE01_01` missing from port_flip flags (ogws `#if VERSION_RSPE01_00/#elif _01` took neither
branch) plus float constants in `snd_Util.h`. Remaining blockers are layout, per unit:
- `math_arithmetic.cpp`: Resort adds Hermite, Bezier, fn_8013BB10, fn_8013BB70 (to 0x8013BBA0) using its .sdata2.
- `lyt_drawInfo.cpp`, `eggDisposer.cpp`, `g3d_camera.cpp`, `snd_AnimSound.cpp`, `snd_StrmChannel.cpp`,
  `snd_TaskThread.cpp`: object larger than the split (weak inlines placed differently / functions Resort lacks);
  lyt_drawInfo's weak `ut::Rect` dtor comes last in Resort under every Wii compiler -> source order differs.
- `g3d_rescommon.cpp`: following code shifts -12; check the next unit's alignment and extra functions.


- `egg/core/eggDisposer.cpp`
- `nw4r/g3d/g3d_camera.cpp`
- `nw4r/g3d/res/g3d_rescommon.cpp`
- `nw4r/lyt/lyt_drawInfo.cpp`
- `nw4r/math/math_arithmetic.cpp`
- `nw4r/snd/snd_AnimSound.cpp`
- `nw4r/snd/snd_StrmChannel.cpp`
- `nw4r/snd/snd_TaskThread.cpp`

## Pack (needs the SportsPack PCH) (1)

- `Pack/RPGraphics/RPGrpDrawPathShadowTexture.cpp`

## data section not located, or broke link/layout/DOL (39)

- `MSL/buffer_io.c`
- `MSL/file_io.c`
- `MSL/mbstring.c`
- `MSL/mem.c`
- `MSL/strtoul.c`
- `RVLFaceLib/RFL_DataUtility.c`
- `RVLFaceLib/RFL_MakeRandomFace.c`
- `egg/math/eggMath.cpp`
- `nw4r/ef/ef_draworder.cpp`
- `nw4r/g3d/g3d_3dsmax.cpp`
- `nw4r/g3d/g3d_anmobj.cpp`
- `nw4r/g3d/g3d_xsi.cpp`
- `nw4r/lyt/lyt_init.cpp`
- `nw4r/ut/ut_FileStream.cpp`
- `revolution/BTE/bta/hh/bta_hh_utils.c`
- `revolution/BTE/bta/sys/bd.c`
- `revolution/BTE/hci/src/hcisu_h2.c`
- `revolution/BTE/main/bte_hcisu.c`
- `revolution/BTE/stack/btm/btm_sco.c`
- `revolution/BTE/stack/gap/gap_api.c`
- `revolution/BTE/stack/hid/hidd_api.c`
- `revolution/BTE/stack/hid/hidd_pm.c`
- `revolution/BTE/stack/rfcomm/port_api.c`
- `revolution/BTE/stack/rfcomm/port_utils.c`
- `revolution/BTE/stack/sdp/sdp_db.c`
- `revolution/EXI/EXIBios.c`
- `revolution/MEM/mem_heapCommon.c`
- `revolution/NAND/NANDCheck.c`
- `revolution/OS/OSCache.c`
- `revolution/OS/OSMessage.c`
- `revolution/OS/OSStateFlags.c`
- `revolution/OS/__ppc_eabi_init.c`
- `revolution/SI/SIBios.c`
- `revolution/VF/pf_code.c`
- `revolution/VF/pf_filelock.c`
- `revolution/VF/pf_system.c`
- `runtime/NMWException.cpp`
- `runtime/global_destructor_chain.c`
- `runtime/ptmf.c`

## Known causes

- Wii/1.0 rejects some ogws headers (float in constant expressions, `offsetof` in constants, stricter access checks, C typedef redeclarations). The scan used scratch-only workarounds; the real build does not.
- `OSCache.c`: Resort pads its asm functions to 16 bytes; the ported build packs them.
- `mem_heapCommon.c`: the located `.bss` range is 0x18 larger than the object; the extra belongs to another unit.
- Units whose data is only referenced from data (vtables, tables) or from `extab` cannot be located from `.text` relocations yet.

## Fixing a port_flip link/split failure (2026-11-09)

Re-locating data after `data_assign.py` (scratchpad check over `build/port_excluded.json`) found all sections for
23 blocked units. The non-header ones failed only on symbol/split details, fixed per unit:
- `undefined: lbl_X`: another unit references this unit's global by placeholder name; rename it to the object's
  name (`objdump -t`). `bte_target_mode`, the three `bta_*_lkup_tbl`/`bta_security` tables.
- A Resort-only-looking `fn_` just before the split that touches the unit's statics is the unit's first function
  (`EUARTInit`): extend `.text` start, rename.
- dtk "ends within symbol": merge labels dtk split from one object (`sdp_cb` 0x4634; a `.sdata2` word), or pad the
  end to the next symbol. A false data pointer into an object goes in `block_relocations` (config.yml).
- Asm after a newly compiled unit loses the original's 16-byte `.text` alignment: give the next split `align:16`
  (name it from ogws's unit order if it is an auto unit: g3d_state, g3d_workmem, g3d_resanmamblight, db_directPrint).
- Newer SDK functions at a unit's edge that use its statics: write them (RFL_DefaultDatabase, scapi_prdinfo).
- `tools/port_extend.py` renames placeholder functions after a ported unit when the object has them in order.
Still located-but-blocked: `OSCache.c` (16-byte padded asm functions) and the header-error units below.
