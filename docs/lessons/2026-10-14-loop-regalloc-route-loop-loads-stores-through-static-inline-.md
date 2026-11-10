# Loop regalloc: route loop loads/stores through static inline getters/setters

- status: works
- tags: regalloc,loop,inline,getter
- scope: RPTns_802499f8
- source: opus worker 2026-10-14

symptom: loop value gets lower saved reg than loop pointers; decl orders fail
cause: inline temps change vreg creation order
fix: TnsGetEnt(p,i) getter for loads, TnsSetIcon(elem,...) setter for stores; explicit *(T**)((u8*)self+i*4+8) for add-offset IV (RPTns_802499f8)
