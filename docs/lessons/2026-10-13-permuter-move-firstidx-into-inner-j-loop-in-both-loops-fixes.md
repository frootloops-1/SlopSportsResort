# Permuter: move firstIdx into inner j loop in both loops fixes callee-saved reg rotation

- status: works
- tags: permuter,regalloc,loop,RPSysPlayerMgr
- scope: RPSysPlayerMgr
- source: permuter

symptom: saveOldData 99.1%: firstIdx/offset/pointer regs rotated r25-r30
cause: live range of hoisted firstIdx
fix: declare 's32 firstIdx = rel2Abs[i];' inside the inner j loop in both loops (permuter output, score 85->40, then second loop by hand)
