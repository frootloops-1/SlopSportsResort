# RPBox_802f71b0 sdata2: 4 dtk 1-byte symbols = 4-lbz colour copy; pool order via dead literals; rodata table off-by-one

- status: works
- tags: sdata2,pool-order,GXColor,fn_802F9CF4,fn_802F7C84
- scope: Pack/RPSports/RPBoxScene/RPBox_802f71b0
- source: worker-1103d

symptom: .sdata2 94 / .rodata 99: lbl_804C54C0..C3 missing, pool -0.001/0.99/-0.01/0.999 in wrong order, lbl_80390E80 words shifted
cause: dtk split one GXColor-like object into 1-byte symbols; function-local const/static colour or struct copy gives li-CSE'd base (lbl+0x1(r7)) or stack temp (worse). Pool order of literals bound to locals follows parse order, retail had the last four reversed in pairs
fix: define four __declspec(section .sdata2) u8 lbl_804C54C0..C3 and keep the extern byte loads (fn_802F9CF4 exact), symbols.txt C3 size 5->1 + gap_12_804C54C4_sdata2; dead (void)-0.001f;(void)0.99f;(void)-0.01f;(void)0.999f before the locals (R17 ledger 149, .sdata2 99.03, remainder is tail pad); fix s32 table by diffing objdump -s of obj vs src
