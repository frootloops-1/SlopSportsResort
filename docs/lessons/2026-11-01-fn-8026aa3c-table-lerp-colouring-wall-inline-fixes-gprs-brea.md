# fn_8026AA3C: table-lerp colouring wall (inline fixes GPRs, breaks FPRs)

- status: fails
- tags: fn_8026AA3C,colouring,inline,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8026a198
- source: batch 2026-11-01

symptom: 99.8%: case-1 table lerp; non-inline FPRs exact but GPR n=r6/base=r4 (target n=r4/base=r6); with inline BsbTblLerp(3,p) GPRs exact but r=f5/frac=f4 (target r=f4/frac=f5)
cause: inline locals outrank every outer named local so frac colours first; named i/n rank below the back-end base temp. r would need to be an IRO temp or an inline local created after BsbTblLerp's locals
fix: none. Dead: declaration orders of r/mul/lo/n/frac, r*=mul and judge.f00=r*mul forms, BsbRandRange, BsbClamp01 (98.9), named row pointer (98.0), if vs one-case switch, whole-block inline, int i/n, n++, 8-min regsearch. mwcc_dbg.sh crashes on this function (gdb 0xfffffffc after backend-00, likely the 160-byte struct-copy loop) so no regalloc dump. Unit data issues too: .data 46%, .sdata2 8%, lbl_8038CE88 24 vs 20 bytes (BsbTbl5), lbl_803C5F58/5FB8/804BE240-248 missing
