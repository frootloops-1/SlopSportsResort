# Const .sdata/.data 'seed' globals were function-local statics (rows 63/66/67/69/175/176 retired)

- status: works
- tags: markers,retire,sdata,static,scheduling
- scope: RPBsb,RPTns,RPSports
- source: claude/mr-b-1101

symptom: load from a writable .sdata/.data object hoisted above prologue stw and the function's own stores; needed const + section pragma + file-end definition
cause: MWCC schedules loads of a FUNCTION-LOCAL static like const loads; file-scope static or global does not. Local statics lay out in parse order (interleaved .data/.sdata per function); file-scope .sdata globals that precede them must be defined above the function. extern const + non-const definition is error 10563. Non-const local static int with visible initialiser is not folded to li. Local statics take a number from the @N counter (lbl_X$N); objdiff/link accept it
fix: commit ; untouched candidates: RPBsb_80273950 lbl_804BE378, RPBsb_80252e7c lbl_804BDE94/98, RPBsb_80263eec lbl_804BE1B8; symbols.txt size 0x8->0x4 for lbl_804BE238/804BDF08/804BE3A8 would allow scalars
