# existNandMemorySync uses NAND_CLUSTER_SIZE; local bool before if; icon speed via int temp

- status: works
- tags: nand,bool,inline,RPSysSaveDataMgr
- scope: RPSysSaveDataMgr
- source: sonnet

symptom: bitfield shifts 18/14 vs 15/17; extra bool materialization in update; li r29/r30 swapped in initBanner
cause: block count divides by 0x4000 cluster size; inlined bool return in if; mask/speed eval order
fix: divide/mod by NAND_CLUSTER_SIZE; 'bool error = expr; if (error)'; 'int speed = iconSpeed & ~(3<<i); iconSpeed = speed | ((2&3)<<i);'
