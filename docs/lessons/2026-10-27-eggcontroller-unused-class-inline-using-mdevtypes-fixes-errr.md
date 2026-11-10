# eggController: unused class inline using mDevTypes fixes errRangeOver<eCDT>/dtor order and checkRange pool order

- status: works
- tags: eggController,TBuffer,weak-order,weak-string,template,class-inline
- scope: egg/core/eggController
- source: claude/controller-1027

symptom: DOL 294 bytes: weak errRangeOver<eCoreDevType> emitted after the TBuffer dtors (retail: before), and @STRING@checkRange pools eCoreDevType pair first (retail: CoreController* pair first)
cause: errRangeOver is a virtual call inside checkRange (bctrl, not devirtualized); the weak copy is emitted after the function whose compile first instantiated checkRange<T>. Retail instantiated checkRange<eCoreDevType> during class-inline processing (before any .cpp function), so it is queued ahead of the vtable-driven dtors and its pool is created first (pools are LIFO). A .cpp function using mDevTypes instead emits errRange<eCDT> right after itself.
fix: Unused in-class inline in CoreControllerMgr: eCoreDevType getNthDevType(int i) { return mDevTypes(i); } (MATCH-PENDING R17, name inferred). DOL 294 -> 0, unit flipped to Matching. Other includers (RPSysControllerMgr) unchanged.
