# fn_80304B58 tail-loop colours: read body through an inline accessor so it is an early inliner temp (MATCH-PENDING marker)

- status: works
- tags: RPBox_803048c4,regalloc,mwcc_dbg,marker
- scope: RPBox

symptom: After the named-nm fix, tail loop rec pointer/value took r24/r25 vs target r23/r24 (tail temps coloured before body)
cause: Named locals always get lower vregs than temps; locals of an inlined function become early temps with vregs above the tail loop temps. So body must come out of an inline while nm and j stay named in the caller.
fix: body = self->slot[i].obj->GetBodyModel() (invented inline returning m[1], MATCH-PENDING R17 + ledger row), 0 diff lines. Free static inline also works. Dead ends: inlining the whole if-body 56 lines (nm/j become temps too); body declared at first use 42 lines. Commit e49672d72 on claude/fn4b58-1029.


UPDATE 2026-10-29: superseded by main 37dab4ea1, which closed the unit with a simpler form: a free static inline BoxBodyModel(v,i) returning v->slot[i].obj->m[1], body declared at its use (RPGrpModel* body = BoxBodyModel(self,i)), tables still indexed (no nm pointer). 14/14 fns, DOL diff 0, unit Matching. My nm-pointer + member-accessor branch claude/fn4b58-1029 (e49672d72) is obsolete; do not merge. The .sdata 85.71% gap is only padding and does not block Matching.
