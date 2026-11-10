# fn_80257804 (RPBsb_802564b4): declare inner pointer p and row up front closes 99.5 -> 99.9

- status: works
- tags: forecast,regalloc,fn_80257804,declare-up-front
- scope: fn_80257804

symptom: nested loop i/row/p callee-saved regs permuted (i r27 vs r25, p r25 vs r27)
cause: colouring order of i/row/p
fix: declare 'const char** p; const char** row;' at function top (that order), assign inside loop; diag lever #1 right. Remaining: li r22/li r29 induction-init order. Dead: named k=i*4 local (93.2), row=&tbl[i*4] (94.3), (i*4+j-1) operand swap, dropping 'register' (flat).
