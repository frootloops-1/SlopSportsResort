# RPSysPlayerSelectScene Calculate 76.6 -> 99.8: auto_inline off around the called state-9 handler fn_801D3C48

- status: works
- tags: inline,auto_inline,deferred,RPSysPlayerSelectScene,join-moved
- scope: Pack/RPSports
- source: claude opus worker 2026-11-02

symptom: Calculate 76.6%, 186 diff lines, HINT join point differs: -inline deferred auto-inlined same-file callee fn_801D3C48 where the original has bl
cause: callee defined in the same TU is auto-inlined; stray auto_inline off/reset pair around Calculate left by a04f90471 did nothing
fix: #pragma push / #pragma auto_inline off / (callee definition) / #pragma pop around fn_801D3C48; drop the stray pair around Calculate. Remaining 28 lines: callee-saved register choice only (state-2 r r30 vs r29, calcState11 loops)
