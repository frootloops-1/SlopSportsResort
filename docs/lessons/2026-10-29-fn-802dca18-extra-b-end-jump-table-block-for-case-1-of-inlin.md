# fn_802DCA18: extra 'b end' jump-table block for case 1 of inlined controller-mode switch not reproduced

- status: fails
- tags: RPBox_802cf93c,switch,jumptable
- scope: RPBox

symptom: target case 1 entry points at a lone 'b L_end' block; ours threads it straight to the join
cause: unknown; a copy removed after branch threading is suspected (cf. dead f32 u=t block in another switch of this unit)
fix: failed: goto done, case 1: break/return in pointer inline, direct switch, m=m, dead int u=m, BoxControllerMode int return (adds li r4,0 before b: 1 line), BoxMapControllerMode(w74,m), call-arg form
