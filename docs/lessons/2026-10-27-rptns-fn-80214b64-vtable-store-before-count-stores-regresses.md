# RPTns fn_80214B64: vtable store before count stores regresses 98.3->95.8

- status: fails
- tags: RPTns_80214480,fn_80214B64,scheduling
- scope: RPTns_80214480

symptom: Moving actor->vptr store above the two count stores swaps the schedule badly (lis/li/addi reorder)
cause: MWCC schedules the vtable address ahead of the count stores, changing register pressure
fix: Keep original store order; do not hoist the vptr store
