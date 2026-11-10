# fn_801F9A00 (RPSports_801f9534) SetVisible lbz r5 vs r0: more dead spellings

- status: fails
- tags: RPSports_801f9534,fn_801F9A00,schedule,SetVisible
- scope: RPSports_801f9534

symptom: 98.0%, 4 lines: ours lbz r5/li r0,2 before rlwinm; retail lbz r0, rlwinm r5,r0, then li r0,2
cause: Scheduler hoists li r0,2 above rlwinm in ours; load vreg then cannot take r0. Pure pre-RA order wall.
fix: Dead (2026-11-03): named u8 flag local (802C0C50 shape), block-scoped u8* flag, anm-obj local, u8 playMode param, direct mFrameCtrl.reset/start/mPlayMode=2 (96.2), restart() before SpSetBit (84.1). None moves li r0,2. Parked.
