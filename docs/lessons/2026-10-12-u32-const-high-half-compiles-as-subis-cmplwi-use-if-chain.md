# u32==const high-half compiles as subis+cmplwi: use if-chain

- status: works
- tags: switch,compare
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: switch(id) on 0x2000x gives cmpw tree
cause: CW lowers id==0x20000..3 as subis+cmplwi only in an if-chain
fix: write if/else-if chain
