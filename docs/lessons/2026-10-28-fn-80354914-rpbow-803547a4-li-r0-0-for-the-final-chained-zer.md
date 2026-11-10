# fn_80354914 (RPBow_803547A4): li r0,0 for the final chained zero stores is scheduled ~15 stores later than retail; source order does not move it

- status: fails
- tags: RPBow_803547A4,fn_80354914,schedule,li-hoist,zero-store
- scope: RPBow_803547A4
- source: claude/b54-1028 sonnet

symptom: 2 diff lines: retail li r0,0 after lfs f0,0xe0(r4) before stfs 0x80(r5); ours after lfs 0x30(r4) before stfs 0xbc(r5)
cause: pre-RA scheduler tie, not source order: position barely follows the copy count
fix: failed (identical 2-line diff): separate statements EC then 114, named u32 z=0 at fn top or after mpCurC=d, static inline for the final zero stores, static inline CopyRec(d,s) wrapping all 58 copies. Worse: d-> or local c=mpCurC for final stores drops the retail mpCurC reload (92.4/97.7); zero stores mid-run puts li at function top (22%); for-loops (52%); mpCurC=d after d->w00=s->w60 (90.9%). Parked; unit stays 7/8 exact
