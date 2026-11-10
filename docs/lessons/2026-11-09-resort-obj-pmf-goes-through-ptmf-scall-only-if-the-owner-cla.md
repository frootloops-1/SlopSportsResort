# resort: (obj->*pmf)() goes through __ptmf_scall only if the owner class is polymorphic

- status: works
- tags: resort,template,ptmf
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: pointer-to-member call compiled as a direct call, no __ptmf_scall
cause: MWCC uses the simple PTMF form for non-polymorphic classes
fix: placeholder owner classes need at least one declared virtual; null PTMF is __ptmf_null (0x80655680), fn_8000770C is __ptmf_cast
