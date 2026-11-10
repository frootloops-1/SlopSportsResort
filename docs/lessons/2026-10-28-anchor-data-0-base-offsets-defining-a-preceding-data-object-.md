# Anchor (...data.0) base offsets: defining a preceding .data object shifts the offsets; struct-merging statics regresses

- status: fails
- tags: data,anchor,rpsports
- scope: RPSports_801f9150
- source: claude/d3-1028

symptom: fn_801F9BA0 99.94: lis/addi base is ...data.0 vs target lbl_803C2E68 (4 lines)
cause: MWCC anchors on TU .data start; target anchor = lbl_803C2E68, so the 16B vtable lbl_803C2E58 at 0x803C2E58 is NOT in this TU's .data before it (defining it first makes offsets 0x64/0x70/0x7c instead of 0x54/0x60/0x6c, 18 diff lines); merging lbl_803C2E68+sButtonAnm7-9+sFrameAnm into one struct drops 9BA0 to 92.0
fix: none; keep statics as separate objects, accept the objdiff reloc-name artifact (DOL bytes unaffected). Also: unit .text emission order is scrambled vs address order (order_check #0), so sdata2 pool order (-5000f, 8000-dbl, 0000-dbl, 0.5f, 0.0f, 1.0f in target) cannot match until functions are reordered
