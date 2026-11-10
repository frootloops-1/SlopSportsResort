# IRPSysHostIOSocket vtables end GenMessage, 0: 14 retail vtables have a 6th null slot

- status: open
- tags: vtable,header,hostio
- source: sp8020f-1104

symptom: __vt__18RPSportsMailHolder 0x18 retail vs 0x14 ours
cause: shared header include/Pack/RPKernel/IRPSysHostIOSocket.h lacks a 4th (pure, null-slot) virtual
fix: orchestrator: add the pure virtual to the shared header and re-verify all derived units
