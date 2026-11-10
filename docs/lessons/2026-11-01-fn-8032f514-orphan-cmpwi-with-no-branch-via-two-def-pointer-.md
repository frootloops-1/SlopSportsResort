# fn_8032F514: orphan cmpwi with no branch via two-def pointer copy

- status: works
- tags: empty-block,copy-prop,fn_8032F514,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_8032F514
- source: batch 2026-11-01

symptom: 99.0%: retail has a cmpwi on b13 with no branch
cause: the block is empty only in the back end; ~35 front-end empty-body shapes fail
fix: BowInput* in = self; if (b13) in = self; use in->cur.b15 (R17 row 52). Unit .data scores 0: split range 0x803CA6B0-0x803CA738 holds other units' objects (table of fn_8032EA58.. now in RPBow_8032ADD8, gLaneXOffsets, RPBowNpcManager vtable, lbl_803CA700/714): splits fix before flipping
