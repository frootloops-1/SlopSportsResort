# RPTns fn_8022F318: popped-entry temp gets r29 not r27; named obj lands r27 but breaks mg/l/n volatiles

- status: open
- tags: RPTnsScene,regalloc,colour,inline,mwcc_dbg
- source: claude/tns-8022f2b8 2026-10-30

symptom: fn_8022F318 99.7: e from inline TnsMoveEnt/TnsPopHead in r29 (hit's reg), target r27 (pos's reg)
cause: mwcc_dbg: e is temp @566 (obj coalesced into it), coloured before named mgr28/pos; GPR pick looks like 'lowest already-used callee-saved non-neighbour, else next new' (fits ours r29, target r27 = coloured after pos/mgr28). A named obj declared first in a nested block with mg/l/n named got coloured FIRST (r31), so order is not purely vreg-descending
fix: open: 'TnsFxEnt* obj; TnsMgr* mg=self->mgr; obj=TnsPopHead(mg->b); if(obj==0) obj=0; else TnsPush(mg->a,obj);' (obj declared in the r==1 block) gives obj r27 exactly but named mg gets r7 vs r4 and the pop temps shift (40 lines). Failed (22 lines, unchanged): obj decl moved into block, ref-out helper, if-assign, helper(self), if(T* obj=...), obj=0 pre-assign, pos/mgr28 via inline getters. Full manual expansion: r31. Next: make mg a temp coloured before the TnsPopHead temps while obj stays named
