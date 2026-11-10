# RPSports_801f9534 .sdata2: s32 magic double must precede u32 one; objdiff 100 hid it

- status: works
- tags: sdata2,pool-order,flip-gate,RPSports_801f9534
- scope: Pack/RPSports

symptom: 100% code + 100% .sdata2 in objdiff but flip_gate dol_diff 7 bytes (sda21 offsets in 4 fns and the 0x80 byte of the magic double)
cause: deferred reverse-order source compiles fn_801F9710 (u32->f32) before the s32 users; retail has the s32 magic double first
fix: R17 dead literal (void)4503601774854144.0; in fn_801F96B4 (compiled before fn_801F9710); ledger row 154. Always run flip_gate before assuming .sdata2 100 means layout
