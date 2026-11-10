# Deleting dtor: count the beq chain, nest if(self) to match

- status: works
- tags: dtor,deleting,beq
- scope: RPTns_8023bb84
- source: sonnet worker 2026-10-14

symptom: deleting dtor 95.8%, one beq short, 4 bytes smaller
cause: orig has three consecutive null checks (inlined dtor chain)
fix: nest if(self) as many times as asm has beq before the base dtor call
