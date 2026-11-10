# fn_802C531C RPGol_802c441c: colouring order is descending vreg number; backend temps outrank inline locals outrank fn locals

- status: open
- tags: regalloc,gpr,mwcc-debugger,inline
- scope: RPGol_802c441c fn_802C531C
- source: gol441c worker 2026-11-02

symptom: four volatile pairs where inline bool results get r4 and temps (lhz field, lwz 0x40(self) reload) get r3, target reverse
cause: dump shows temps r58+ coloured first, then inline-expansion locals (r38-r56, later expansion = lower number), then fn-level named locals (r33-r37); inline-level named locals and same-block fn-level named locals are copy-propagated away so cannot be used to reorder
fix: none yet: tried KindB as if/switch/ternary/!!/int, named f, fn-level v and c40, shots before a, v as inline param, sp inlined into fn (82 lines worse); 98.9 unchanged
