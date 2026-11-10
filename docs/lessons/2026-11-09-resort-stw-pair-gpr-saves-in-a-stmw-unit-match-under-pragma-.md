# resort: stw-pair GPR saves in a stmw unit match under #pragma use_lmw_stmw off

- status: works
- tags: resort,pragma,prologue,MATCH-PENDING
- scope: resort
- source: bowling-lanes

symptom: header-like inlines/copy operators save 2 GPRs with stw pairs while the unit uses stmw
cause: those functions were compiled without lmw/stmw (probably another TU's setting for header inlines)
fix: #pragma use_lmw_stmw off around them (R17, ledger #10); optimize_for_size off instead unrolls copy loops
