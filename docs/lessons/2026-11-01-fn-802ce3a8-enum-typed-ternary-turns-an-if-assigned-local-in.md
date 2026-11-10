# fn_802CE3A8: enum-typed ternary turns an if-assigned local into a back-end temp coloured between two copies

- status: works
- tags: enum,ternary,backend-temp,colouring,fn_802CE3A8,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: unit sweep 2026-11-01

symptom: 99.8%: callee-saved rotation in the first by-value BoxData copy (kind r22 vs r28)
cause: branch-2 n was IRO temp @3557 coloured last; target needs it coloured between copy-2 temps (r123..) and copy-1 temps (r72..)
fix: rec.unk44 = self->kind == 1 ? BOX_MSG_1 : BOX_MSG_2; (enum arms make it a branch with a back-end result temp; int arms fold to arithmetic). Branch 1 must keep n = 2; if (kind==1) n = 1; (enum ternary there: 46 lines)
