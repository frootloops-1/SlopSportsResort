# ctr/bdnz loop from while(h>0): write for(;;){if(h==0)break;h--;if(...)break;}

- status: works
- tags: loop,bdnz,ctr,slot,search,RPGrpModelResManager
- scope: RPGrpModelResManager::CreateData
- source: sonnet worker, verified 2026-10-12

symptom: Free-slot search loop compiled as ctr/bdnz; target is an unrotated loop with clrlwi. at top and bne back
cause: CW converts counted decrement loops to ctr loops (also for continue/goto/pointer variants)
fix: for(;;){ if(h==0) break; h--; if(list[h].type==Type_None) break; }
