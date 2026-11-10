# Named sdata2 lbl_ consts between consecutive @N neighbours are pool literals; fresh in-for counters + inline flag temp (RPBow_80323790)

- status: works
- tags: sdata2,literals,regalloc,vtable,RPBow_80323790
- scope: RPBow_80323790

symptom: sdata2 98.96, .data 0, fn_803256C4 99.8, fn_80323F30 98.3
cause: lbl_804C6014.. were pool literals @385..@396 of fn_80323F30 declared as named consts; vtable lbl_803CA5F0 undefined
fix: literals + rename to @N scope:local; hand void* vtable (R17 109); fn_803256C4: fresh for(s32 i)/for(s32 j) counters + static inline BowIsSettled (R17 110). fn_80323F30 stays 98.4: pure pre-RA schedule order of pool loads vs zero stores (equal height 10); dead: store moves, struct view, fill loop.
