# fn_801F7B80 closed: by-value class param instead of pointer for the copied record

- status: works
- tags: RPSports,colouring,by-value,copy,vtable,fn_801F7B80
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f6ebc
- source: opus 2026-11-02

symptom: 8-word copy into local rec with vtable store: target vt lis/addi r12 first, w0..w7 r11..r0; ours vt r5, w r0,r6..r12 (93.7)
cause: src was a pointer param; the sibling caller fn_801F9150 had the same copy pattern matched with a by-value param (comment there: pointer param keeps the loads behind the stores, named temps colour wrong)
fix: void fn_801F7B80(SpPlayerRef* self, SpRecCopy src) { SpRecCopy rec; rec.vt = lbl_803C34D8; rec.w[0] = src.w[0]; ... } -> 100, no markers. Check sibling units for an already-matched instance of the same idiom first
