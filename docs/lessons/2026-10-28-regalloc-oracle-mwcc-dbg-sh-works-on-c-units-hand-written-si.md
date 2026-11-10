# Regalloc oracle (mwcc_dbg.sh) works on C++ units; hand-written sites.json for Draw/CalcView add nothing

- status: works
- tags: regalloc,debugger,regsearch,sites,cputexture,shadowtexture,lightmanager
- scope: egg/gfxe

symptom: register-colouring walls resist all spellings; regsearch generic and hand sites find no gain
cause: hand sites (12 for Draw: alpha/xy/simple/pCap/params/w,h types/range/intensity/enable; 8 for CalcView) = 3337 and 462 evals, best = baseline; spelling search cannot move vregs that the optimiser forwards or that sit behind early-coloured temps. The debugger gives vreg identities and the true colouring order
fix: Use tools/mwcc_dbg.sh <unit> <unqualified-fn> <outdir> to see which temp/@N values are coloured before the named locals, then choose a construct that creates, removes or ages THAT value. CpuTexture: red is a temp (coloured first), offset a named multi-def (last); target is reverse. Draw: temps r145/@16800 hold r31/r30 across alpha, so alpha-first only reorders vregs. regsearch sites.json is cheap but only worth it once the debugger names the value
