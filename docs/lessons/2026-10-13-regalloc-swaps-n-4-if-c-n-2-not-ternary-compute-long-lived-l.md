# Regalloc swaps: 'n=4; if(c) n=2;' not ternary; compute long-lived local in static inline helper; move loop block to inline member

- status: works
- tags: regalloc,ternary,inline-helper,cursor
- scope: Pack/RPKernel/RPSysCursorDrawMgr

symptom: loop counter vs count swapped r31/r30; local colored too low
cause: MWCC coloring order depends on expression shape and inline boundaries
fix: default-then-override instead of ternary; static inline GetRemoteNum(); inline member for a loop block; plus symbols.txt: rename lbl_ to @NNNN locals, merge strings to @stringBase0 string_table, shrink padded bss
