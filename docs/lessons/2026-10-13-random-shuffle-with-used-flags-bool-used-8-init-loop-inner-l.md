# Random shuffle with used-flags: bool used[8] + init loop + inner loop with break

- status: works
- tags: mwcc,loop,unroll,regalloc
- source: RPGol_802b90b4

symptom: li r0,k before each cmpwi used_k, flags in GPRs; extra const-0 reg (savegpr_14)
cause: 8 bool locals is the wrong shape
fix: bool used[8]; for(j<8) used[j]=false; for(i<8){r=getU32(8-n); for(j<8) if(!used[j]&&--r<0){...;used[j]=true;n++;break;}} - MWCC unrolls and promotes array to regs
