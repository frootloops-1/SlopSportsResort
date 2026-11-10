# RPTns fn_8022F318 closed: two-statement inline getters reorder colouring; dead 1.0f fixes pool order

- status: works
- tags: RPTnsScene,regalloc,colour,inline,pool,sdata2
- source: claude/tns-8022f2b8 2026-10-30

symptom: fn_8022F318 99.7: inline-popped entry in r29, target r27; after flip DOL had 60 bytes in sda21 offsets
cause: One-line getters for pos/mgr28 give temps numbered after the TnsMoveEnt temp; two-statement getters ({ T* p = &a->pos; return p; }) give temps coloured so the entry reuses pos's r27. Pool order differed only in the DOL (objdiff ignores it): 1.0f must be created first
fix: static inline TnsVec* TnsActorPos(a){TnsVec* p=&a->pos; return p;} + same for mgr28 (both needed; one-statement forms or pos-only fail) -> 100; '1.0f;' dead statement at top -> DOL 0, unit Matching. Always run the DOL link after flipping: NonMatching links the original object and hides pool-order diffs
