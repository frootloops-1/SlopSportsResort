# RPBow_80319C98 table-base/index GPR swap is insensitive to source shape

- status: fails
- tags: RPBow,BowCamShake,regalloc,table-lerp,GPR
- scope: Pack/RPSports/RPBowScene/RPBow_80319C98

symptom: fn_80319E94 (g/i r5<->r6), fn_8031B3F4 + fn_8031A0E0 shake (tbl r3 vs r4, i*12 r4 vs r5), fn_8031A0E0 1C6C/2734 lerp: table base from lbl_804BF9A8->p4 coloured after index/address temps; lbl load scheduled one slot early as a knock-on
cause: unknown; tbl/g behaves like a late-coloured named local in every spelling; mwcc_dbg dump not obtained (port 9001 held >30 min by another worker)
fix: failed (harness, all exactly flat or worse): g/i/j/tbl decl order and hoisting, const/void*/u32/ref/BowRes& types, s32 vs int index (s32 alone folds i+1 -> 0x1498 and gives target g colour but wrong code), separate int j, lerp inline helpers (g as inline local or param, t-first/fr-first), accessor inlines incl. ((T**)lbl)[1], pointer/ref to entries, no-local (lfsx form, +1 insn), x/y/z temps, fr inline, regsearch --generic 8 min (rank 0, op 4). fn_8031A0E0 float block: decl order of rate/height/angle/fovy/dist (120 perms) flat; lerp helper/operand order flat
