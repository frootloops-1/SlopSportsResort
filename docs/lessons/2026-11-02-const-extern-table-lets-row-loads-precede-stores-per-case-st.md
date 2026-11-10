# const extern table lets row loads precede stores; per-case static inline with named Pair; RPSports_801eb388 holds two TUs

- status: works
- tags: const-pointee,inline-helper,tu-split,RPSports_801eb388
- scope: RPSports_801eb388

symptom: fn_801EC034 96.9 (908 vs 924 B), fn_801EC510 99.3; rodata/data/sbss 0
cause: non-const extern table; hand-expanded stream helper; unit spans title scene + training menu scene
fix: extern const s32 tbl[][3] + cached index; SpEC034Slide5/6 inline (R17 113); SpPlayStream(const char*) with mgr as helper local; split at 0x801EC3C0 (4-byte .data pad, 8-byte sbss chunks, two string pools). Remaining: int-to-float double slots (retail 0x48,0x48 | 0x50,0x50 per case).
