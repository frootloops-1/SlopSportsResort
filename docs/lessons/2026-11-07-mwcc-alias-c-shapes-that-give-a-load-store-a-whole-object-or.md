# MWCC Alias.c: shapes that give a load/store a whole-object or worst-case alias

- status: works
- tags: alias,scheduler,mwcc,Alias.c,whole-object,worst-case
- scope: global
- source: rfl-mweppc Alias.c/ConstantPropagation.c/IroPropagate.c, round 10

symptom: Need a memory op to depend on stores it provably does not overlap (or to be free of them)
cause: Aliases are set at the first gather (ValueNumbering, right after peephole forward) from initial pcode and only widen afterwards. Whole object: indexed lfsx/stfsx or add whose index reg is not an li in the same block before the use (li in another block, or rlwinm/slwi-scaled index even of a same-block li); update forms (lfsu); one use reached by 2+ address defs of the same object with different offsets. Worst case: base reg with any reaching def that is not an address def (loaded pointer, call result, mr from r3 after a call), address passed through a non add/addi op (or/rlwinm/subf). Virtual objects (pointer params) join worst_case_ptr only if the address escapes to memory or a physical reg; otherwise only worst_case_func (calls)
fix: C-level trigger that folds back to lfs d(rB): an int index assigned a constant on a path that does not dominate the use (int ci; if (x) ci = 1; ... (&p->a)[ci]). IRO avail-propagation needs all paths so it keeps the var; backend const-prop needs one reaching def so it folds lfsx->lfs, and deletedeadloads removes the li. Cost: only the guard. Constant indices in the same/dominating block are folded by IRO (precise)
