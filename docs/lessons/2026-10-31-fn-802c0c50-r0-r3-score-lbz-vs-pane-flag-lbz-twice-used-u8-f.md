# fn_802C0C50 r0/r3 (score lbz vs pane flag lbz): twice-used u8 flag local in SetVisible keeps a named low vreg + named Pane* local; pointer loads never move above pointer stores (R17, ledger 40)

- status: works
- tags: rpgol,802c0c50,setvisible,vreg,iro-propagate,scheduler,r17
- source: worker final-0c50 2026-10-31

symptom: 99.97%, 8 lines: score lbz got r3, pane flag lbz got r0 (target score r0, flag r3)
cause: Scheduler add_memory_dependencies keeps pointer loads behind pointer stores, so the order is fixed; the loads are back-end temps coloured highest vreg first and the flag load is created after the score load. IRO_PropagateExpressions substitutes away single-use locals, keeps those with uses != 1 as named low vregs
fix: inline body u8 f = mFlag; f = f & ~(1<<0); f = f | ((visible?1:0)<<0); mFlag = f; plus nw4r::lyt::Pane* pn = c->score[i]; pn->SetVisible(true); (named pn numbered below f: flag r3, pane r4; an IRO @temp pane is coloured first). Both needed. Dead: single-use flag local, split &=/sum/|= (98.0, extra stb), SetVisible before sum (98.3), regsearch --generic 8 min ~500 evals.
