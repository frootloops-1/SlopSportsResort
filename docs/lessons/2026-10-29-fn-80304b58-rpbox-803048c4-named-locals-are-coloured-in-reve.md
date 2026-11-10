# fn_80304B58 (RPBox_803048c4): named locals are coloured in reverse declaration order, so a named table pointer declared between body and j fixes the body/table/j colours

- status: open
- tags: RPBox_803048c4,regalloc,mwcc_dbg
- scope: RPBox

symptom: 99.4%: body r22/table r23 vs target body r23/table r22 (strength-reduced temp @354 has a higher vreg than the named body local, so it is coloured first)
cause: Compiler temps from strength reduction outrank named locals in colour order. A NAMED pointer (const char** nm; for (j=0, nm=lbl; j<0x10; j++, nm++) SetAnm(..., *nm, 0)) replaces the temp and gets a local vreg; within a block later-declared locals get LOWER vregs, so declare order body, nm, j gives body r23, nm r22, j r21. *nm++ inside the arg puts addi before bctrl (wrong); increment in the for-update. Debugger check is ~5s per variant (tools/mwcc_dbg.sh).
fix: Committed on claude/fn4b58-1029 (dc08ad4d7): 99.4 -> 99.7, 26 -> 10 diff lines. Remaining: tail 'for i<2 new RPGrpModelRecord' temps (@347/@349) are coloured BEFORE body so they take r25/r24 (lowest-used-reg-first), target has them after body at r24/r23. Tried: local record ptr r, shared function-level i (worse, 16). Untried: giving the tail temps lower vregs than body.


UPDATE 2026-10-29: superseded by main 37dab4ea1, which closed the unit with a simpler form: a free static inline BoxBodyModel(v,i) returning v->slot[i].obj->m[1], body declared at its use (RPGrpModel* body = BoxBodyModel(self,i)), tables still indexed (no nm pointer). 14/14 fns, DOL diff 0, unit Matching. My nm-pointer + member-accessor branch claude/fn4b58-1029 (e49672d72) is obsolete; do not merge. The .sdata 85.71% gap is only padding and does not block Matching.
