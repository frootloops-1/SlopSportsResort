# single GXColor slot reproducible only with #pragma cplusplus off (fn_8024E9F4 exact, steering, not applied)

- status: open
- tags: GXColor,cplusplus-off,c-mode,fn_8024E9F4,fn_802CE89C,R17
- scope: RPBsb_8024e9a4, RPBox_802cb9cc
- source: unit sweep 2026-11-01

symptom: two sites writing one stack GXColor from two anonymous constants; C++ leaves temps or a second slot (fn_8024E9F4 10 lines, fn_802CE89C 12-line group)
cause: only the C front end gives compound-literal assignment into one object; the original layout (shared .sdata2 pool, @N numbering, C++ copy-ctor memberwise copy) proves one C++ TU, so a real C file is ruled out
fix: prototype (not applied): #pragma cplusplus off ... #pragma cplusplus reset around the function in the C++ file, typedef struct X X; for tags, BOOL/TRUE/FALSE, function-level GXColor c; and c = (GXColor){..} at both sites (+ #pragma c99 on in RPBox). fn_8024E9F4 10 -> 0 lines; fn_802CE89C 26 -> 14 (case-0 r5/r6 swap unchanged in every C form). Patch /tmp/whscratch/cplusplus_off_prototype.patch. Needs R17 marker + ledger row if adopted. Dead: cpp_extensions/ANSI_strict/c9x/gcc_extensions/cpp1x pragmas in C++ mode
