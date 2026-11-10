# fn_8028F0E8 regalloc permutation dead ends (99.3%)

- status: fails
- tags: RPGolCameraManager,regalloc

symptom: orig m=r31,pin=r30,bpos=r29,player=r28,ppos=r27; ours player=r31,pin=r30,m=r29,bpos=r28,ppos=r27
cause: unknown
fix: failed: decl order, decl/init split, inline getters, local copy of m, references, counter forms, nested ifs, end-section inline; whole top part in an inline gives m=r31 but reverses stack slots
