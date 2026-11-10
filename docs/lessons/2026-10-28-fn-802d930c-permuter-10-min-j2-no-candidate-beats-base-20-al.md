# fn_802D930C permuter 10 min -j2: no candidate beats base 20, all ties are formatting no-ops

- status: fails
- tags: permuter,regalloc,fpr,rpbox,fn_802D930C
- scope: fn_802D930C
- source: claude/pm4-1028

symptom: sel second def f21 vs retail f31 (4 instr); permute.py setup start mismatch 9 lines, base score 20
cause: ~700 iterations, 6 equal-score outputs are paren/if(1)/do-while(0)/volatile pad noise only; no score below 20 reached; web split not reachable by mutations
fix: none: do not rerun permuter; remaining lever needs a different DAG (e.g. sel=... expression shape change, hp/p/fn_802FD2B8 call order) not a spelling variant
