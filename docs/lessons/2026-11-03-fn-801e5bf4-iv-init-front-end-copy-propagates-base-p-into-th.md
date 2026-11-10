# fn_801E5BF4 IV init: front end copy-propagates base.p into the loop-1 names IV (lis/addi), so retail's addi rX,rBase,0 is not reachable by assignment-form changes

- status: fails
- tags: iv-init,copy-propagation,holder,801E51B4
- scope: RPSports_801E51B4
- source: orchestrator 2026-11-03

symptom: 2 lines left: ours 'mr r29,r31' before 'mr r30,r26', retail 'mr r30,r26' then 'addi r29,r31,0x0'
cause: mwcc_dbg backend-00: names IV is initialised with its own 'lis;addi' of the global (base.p value substituted in the same basic block), optimizer CSEs it to a copy; only loop 1 shares a block with the base def, pair/panel IVs already use 'addi rBase,imm'
fix: Dead (all 2 lines unless noted): &lbl[0], (u32) cast chain, via tmp (68), +z, assign after state store, double assign, two holders, trailing base.p=NULL, base.p+=40/31 cursor, unsized/80/const extern decl, mixed global/holder in loop 1, separate j counter (6, changes latch order), inline helper with base param (93), param 'base=base' (80), opt_propagation off (35). Open idea: a way to put loop-1 init in a different block than the base def without extra branches
