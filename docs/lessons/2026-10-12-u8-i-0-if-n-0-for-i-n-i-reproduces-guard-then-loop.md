# u8 i=0; if(n!=0) for(;i<n;i++) reproduces guard-then-loop

- status: works
- tags: loop
- scope: RPKernel
- source: RPSysTagProcessor/SystemWinMgr 2026-10-12

symptom: loop guard shape cmpwi/beq/b cond differs
cause: for-loop folding
fix: hoist guard into if around for with i declared outside
