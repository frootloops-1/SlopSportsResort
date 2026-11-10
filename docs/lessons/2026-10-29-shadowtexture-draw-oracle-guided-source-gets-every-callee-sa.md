# ShadowTexture Draw: oracle-guided source gets every callee-saved register right (35 -> 22 lines, .text 99.60 -> 99.88)

- status: works
- tags: shadowtexture,draw,regalloc,debugger,regsearch
- scope: egg/gfxe/eggShadowTexture

symptom: Draw: alpha r29/h r31/simple r31/x r27 vs target alpha r31/h,x r29/simple r27/pCap r30
cause: two values were coloured before every named local: (a) bool simple became a forwarded single-def temp (r145) and took r31; (b) the inline getCapTexture() result @16800 took r31/r30. With them demoted, named order decides: alpha must be the first-declared named local
fix: u8 simple (stays a named local); read the cap texture without the inline-result temp (stand-in: raw +8 member read, MATCH-PENDING; getCapTexture() into a named pCap still keeps the @N temp, rank 2); declare alpha and pCap uninitialised at the top, then alpha first among w/h; pEfb pointer instead of rEfb ref; formats[intensity ? 1 : 0]. Found by mwcc_dbg.sh (identify the first-coloured temps) then regsearch with hand sites (1373 + 1097 evals). Remaining: last capture block volatile regs (fmt r4/flags r6 vs ours r5/r4) and 3-insn order; the inline-row form fixes cntlzw/lis/add regs but moves the add (17 lines, op=2). Branch shadow-flip, not merged
