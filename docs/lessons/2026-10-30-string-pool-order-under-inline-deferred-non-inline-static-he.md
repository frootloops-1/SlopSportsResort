# String pool order under -inline deferred: non-inline static helpers compile at their own source slot and pool their literals there

- status: works
- tags: string-pool,rodata,inline,order
- scope: Pack/RPSports/RPSportsCommon/RPSysLytPlayerSelect*

symptom: @stringBase0 order differs: a later function's literal (CURSOR_02, N_arrowR...) sits ahead of literals from functions compiled earlier; dead-branch literals (constant or optimizer-folded is4) do NOT pool
cause: code literals pool at codegen in compile order (reverse source); a non-inline static function (auto-inlined, dead-stripped at link) is itself compiled at its definition slot: at file END it is compiled first; mid-file it was sometimes deferred until after its caller (placing it right after fn_801DD0D0, before other helper prototypes, worked)
fix: move the literal-bearing code into a 'static void' helper and place its definition where it must compile (file end = first in pool). Also: #define NW4R_G3D_PLATFORM_GPU_H drops cm2hw from .sdata2; trailing pool padding -> shrink @stringBase0 size in symbols.txt; DE958 table was {P_arrowL,P_arrowR} (asm_diff masks the swap). Regalloc: CountControllers inline helper fixed active/count/i colours in fn_801DD798
