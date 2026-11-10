# Float 3-way lerp guard: bne/b join shape not reproduced

- status: open
- tags: branch,join,float
- source: RPBox_802cf93c fn_802D5F08 2026-10-23

symptom: target: fcmpu t,0; bne next; b end (empty first case) then t==1 copy, else lerp; ours folds to beq end
cause: unknown; empty if, early return in inline, nested if(t!=0) all give beq
fix: untried: inline returning pointer, switch-like goto, non-inline helper
