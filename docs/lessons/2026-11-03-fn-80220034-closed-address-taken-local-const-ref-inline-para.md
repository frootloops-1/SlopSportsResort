# fn_80220034 closed: address-taken local + const-ref inline param gives a late vreg

- status: works
- tags: RPTnsScene,regalloc,colour_sim,MATCH-PENDING
- source: claude/tns5530-1103 25d4b83b0

symptom: fn_80220034 99.8: id/idx callee-saved swap (id r31 vs r28, idx r28 vs r31); all four of self/flag/idx/id pushed in the final colour_sim sweep, ascending, so id (highest named vreg) coloured first
cause: target needs id pushed in sweep 1 (vreg above the loop temps). '&param' gives the param a late renumbered vreg (idx'78), '&local' makes the IRO forward it but the value gets a late vreg (r81) which was then coalesced into findLow's inline-param copy (rep = lowest vreg)
fix: u32* pid = &id; all uses *pid, and the inline TnsSndPre::findLow takes 'const u32& id' (no param copy, so the late vreg survives) -> 100 (MATCH-PENDING R17, ledger 128). findSame can stay by value; ref-only without pid: 99.2
