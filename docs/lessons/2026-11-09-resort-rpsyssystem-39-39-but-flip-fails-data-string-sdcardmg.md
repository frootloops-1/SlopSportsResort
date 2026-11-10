# resort: RPSysSystem 39/39 but flip fails: .data string 'SDCardMgr' must follow the vtables

- status: open
- tags: resort,rpsyssystem,data-order,flip

symptom: flip_gate: DOL 32 bytes short, __vt__11RPSysSystem shifted; unit_cmp said .data 100 (content-only, misses order)
cause: Retail .data = RPSysSystem vt (0xC) + pad, RPSysConfigData vt 0x10..0x48, then the non-const char[] 'SDCardMgr' at 0x48. MWCC emits file-scope and function-local static data at parse time, before the deferred vtables
fix: Tried: file-scope char[] (first), literal at call site (goes to .rodata), function-local static char[] (first), definition moved to end of file with extern first (first). Untried: #pragma defer_codegen off (R17 steering) or finding the real owner construct (maybe a header inline emitted in the deferred flush)

Follow-up (same day): also failed: `#pragma defer_codegen off` before a definition at file end (string still first;
the vtables are emitted at the final flush regardless), `#pragma readonly_strings off` around the user function (literal
still .rodata, 4 functions regress), and an inline accessor with a function-local `static char[]` (weak, still at .data
offset 0; temp flip fails to link because other units reference lbl_806B8250). Evidence: the same
`lbl_806F5240 != NULL, "SDCardMgr"` check at one address recurs in other files (0x8022F398 in RPSysScene), so the string
is shared, not file-local; `main` (0x8022E3A8) sits between RPSysSystem and RPSysSceneCreator. Next idea: find how
the other users reference it once their units are written (an SDCardMgr header with an extern name array).
