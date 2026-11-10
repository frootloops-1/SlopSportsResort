# Symbol and split recovery (RZTE01_01)

No map, no debug build. Names and unit boundaries come from these passes, in this order.
Every step leaves `build/RZTE01_01/main.dol` matching `build.sha1`.

| Step | Tool | Source | Result |
|---|---|---|---|
| Exact signatures | `sig_match.py` + `apply_ogws.py` | ogws (Wii Sports) DOL+symbols | 1730 names, 73 .text splits |
| Dolphin map | `merge_dolphin_map.py` | Dolphin signature-DB map | 10 names (rest is duplicate-hash noise) |
| Address list | `merge_addr_list.py` | github.com/riptl/wii-symbols `RZTP01.txt` (same addresses as this DOL) | 2069 names |
| Splits by name | `port_splits.py` | forecast, zeldaret/ss, mkw, ogws `symbols.txt`/`splits.txt` | +194, then +99 .text splits |
| Fuzzy matching | `fuzzy_match.py` + `apply_names.py` | ogws DOL+symbols | ~1170 names; 20% holdout 98.8% precise |
| __sinit anchors | `sinit_splits.py` | `.ctors` table | 348 `unk/sinit_*.cpp` units (end exact, start an upper bound) |
| Vtables | `vtable_match.py` | ogws vtables | 80 vtable labels, 167 slot names (only from unchanged layouts) |
| RTTI | `rtti_names.py` | class-name strings in data (HBM, nw4hbm) | 21 `__RTTI__`, 16 `__vt__` |
| Class strings | `class_strings.py` | game strings like `Doh::DrawGX` | `docs/class_strings.md` (evidence only) |

| Data ownership | `data_assign.py` (+ `cycle_fix.py`, `link_fix.py`, `align_starts.py`, `close_gaps.py`) | exclusive references, code order | .data 85%, .rodata 68%, .sdata 90%, .sdata2 92%, .bss 34%, .sbss 75% assigned; 98.1% accurate on ogws |
| Vtable edges | `vtable_check.py`, `vtable_shift.py`, `merge_sinit_only.py` | vtable slots vs unit edges | 2 library splits extended, 4 `__sinit`-only units merged into their library file |
| Path layout | `unit_paths.py` (also applied inside `port_splits.py`) | ogws `src/` layout | 61 renames (`revolution/os`->`OS`, `MSL_C`->`MSL`, `TRK_MINNOW_DOLPHIN`->`MetroTRK`, `hbm/`->`homebuttonMiniLib/`, `unconfigured/*.o` by contents) |
| Carve unk units | `carve_unk.py` | ogws, ss, mkw, forecast splits by name | 48 library/RP files cut out of 28 `unk/sinit_*` units (+0x2EEAC bytes named); code before a file becomes `unk/text_<addr>.cpp`; data cut by exclusive refs, rounded up to the piece's alignment |
| Fill gaps | `carve_unk.py --gaps` (+ `data_assign.apply` for new units, `cycle_fix.py`) | same references | 57 files placed in gaps, 105 data ranges (11 dropped by `cycle_fix` in MetroTRK); second carve pass +3 files out of `unk/text_*`. Gap functions 2970 -> 1892. Names compared case-insensitively (macOS: `snd_dvdSoundArchive` vs `snd_DvdSoundArchive` were one object file) |

Tested and not applied:
- Inline-copy tails as file ends (`boundary_eval.py`): wrong model; on ogws inline copies are spread evenly through each file (12% precise).
- Game-code boundaries from vtable classes (`class_bounds.py eval`, signals in `file_signals.py`), scored on ogws game code
  in `__sinit`-delimited containers: a class change with no class straddling the gap holds a real boundary 85% of the
  time, but the cut lands exactly on it only 44-56% (best subset, adjacent classed functions with runs >= 3: 70%);
  recall ~10%. Other signals measured there: shared `.sdata2` symbol = same file 95% (`.rodata` 82%, `.sdata` 84%,
  `.data`/`.bss`/`.sbss` 37-65%); identical function bodies = different files 55%; unreferenced weak copies 100% but
  only 7 pairs in ogws and 6 groups in Resort game code; "vtable then non-vtable" in `.data` = boundary 28/44.
  Constants are pooled in emission order in Resort too (no per-file sawtooth). Not applied: game-code file
  boundaries come from matching (roadmap phase 3) until a better signal turns up.
- Constant-pool conflicts (`pool_bounds.py`): every function sharing a `.sdata2` constant is in one file (held on every ogws check); a boundary is
  forced between blocks with duplicate values, but placing it is only 85-89% precise and covers ~10% of real boundaries.

Re-run `port_splits.py`, `carve_unk.py` and `fuzzy_match.py` after adding names: each feeds the others.
`carve_unk.py` accepts a newer library version than `port_splits.py`: no reference coverage minimum at >= 3 hits,
duplicate names resolved to the unit holding >= 80% of the hits, no reference-order check (newer versions reorder
methods), and extra methods of the file's own classes allowed in between.
Placed by hand from source-filename strings plus reference neighbour order (ogws, forecast, ss): `OSLaunch.c`,
`WUD.c`, `dvd.c` ("Pdvd.c" is the string 3 bytes into its symbol), `ncdsystem.c` + `nettime.c`, `NWC24Config.c`,
`db_console.cpp`. Left in gaps: `fn_800516D0` and `fn_8005A8E0` (public, called from WPAD; file unknown).
Reference files are downloaded to `build/ext/` (not tracked).
