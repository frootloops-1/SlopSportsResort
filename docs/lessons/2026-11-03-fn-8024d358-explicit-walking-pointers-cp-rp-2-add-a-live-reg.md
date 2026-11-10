# fn_8024D358 explicit walking pointers (cp/rp += 2) add a live register

- status: fails
- tags: fn_8024D358,RPTnsScene,preheader,iv
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194
- source: codex-tns-c194-trace-1103h

symptom: Preheader ADDI ownership still reversed (aliases r20/r19 own ADDI, IVs r26/r28 copy).
cause: Declaring cp=chosen and rp=related as explicit walking pointers (cp+=2, rp+=2) before the cho/rel aliases keeps cho/rel as separate live values, so prologue becomes _savegpr_16 (one extra callee-saved reg): 98.5%, 229 differing lines.
fix: No fix. Reverted. Explicit pointer-walk shapes are a dead end alongside delayed/opaque aliases; the alias must stay a single invariant base without a second live pointer.
