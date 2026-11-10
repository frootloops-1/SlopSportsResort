# RPSports_801ea458 split at 0x801EABF4: two 0.0f in sdata2 were two TUs, R17 global const removed

- status: works
- tags: sdata2,pool-order,split,vtable,RPSports
- scope: RPSports_801ea458
- source: claude/ea458-1029

symptom: retail pools 0.0f at 1F50 and 1F78 in one split; one TU dedups, a global const 0.0f at file end was the workaround
cause: two TUs: A=801EA458..801EABF4 (sdata2 1F50..1F70, rodata 387438, data 2650 vtable {0,0,fn_801EAB9C,0}) and B=801EABF4..801EB388 (u32 magic double 1F70 + 0.0f 1F78, rodata 387458/387500/387510, data 2660 vtable with fn_801EB2C0/EB1A0/EB158/EAD68). fn_801EAB9C is the deleting dtor of the A-side class (emitted last), so EABF4 starts B; EABF4 vs EAC58 as the first B function cannot be told apart by data (neither touches sdata2/rodata of its own at the edge)
fix: split_at 0x801EABF4 in splits.txt + configure.py (new unit RPSports_801eabf4), source split with identical preamble, literal 0.0f in A, workaround and ledger row removed; no function score changed (14104 fns compared), DOL 0, text order clean. Open: fn_801EB388 ctor uses B's vtable/table so the B|801eb388 text boundary is probably later than EB388; .sdata2 now has 4-byte section tail in both units
