# fn_802CDFC0 (RPBox_802cb9cc): fctiwz temp never takes f0 under any declaration order or inline wrapper

- status: fails
- tags: regalloc,fpr
- scope: RPBox_802cb9cc fn_802CDFC0
- source: FPR batch 2 2026-10-28

symptom: 99.80, opcodes identical; target fctiwz f0, step f2, remaining f1
cause: pure colouring residue; t-first puts step on f2 but hoists its load into the prologue (98.8)
fix: none: tried t first, t/remaining/step orders, BoxSeqTicks inline, BoxStgDecF2C inline (98.8). park
