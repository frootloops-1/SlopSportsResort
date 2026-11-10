# Stack slots of temps follow @N order; ctor delegating to a by-value set() swaps the ctor-temp pair

- status: works
- tags: stack,slots,inline,ctor,temps
- scope: RPSports_801fdbc0
- source: sc801fdb-1102

symptom: fn_801FE454: two 8-byte temps (dead call-result copy, read param copy) at 0x28/0x30 swapped vs retail; objdiff 100 but DOL 6 bytes
cause: slots: named locals first, then @N temps in ascending @N (creation) order at descending addresses. A by-value class arg gets a parse-time temp (@22xx) when the call is parsed, inline-expansion locals get later @N (@26xx). Ours: ctor arg temp p (@2215, read) older than SpPanePos local c (@2672, call dest). mwcc_frontend_trace.py codegen-entry AST shows the @N names per statement
fix: worked: SpVec3f v(fn_801D01F0(...), z) with ctor SpVec3f(CurPos p,f32 z){ set(p,z); } and by-value set(CurPos,f32): ctor parse temp = call dest (older, 0x30), set's inline param copy = read (0x28). Dead: const-ref ctor param, const CurPos& c = call() (ref-bound temp goes to the named region), named block c (named region 0x58), SpId(CurPos) pass-through (outer arg temp numbered before inner), direct return in helper (call temp becomes codegen temp at 0x8)
