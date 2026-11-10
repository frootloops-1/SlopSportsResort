# DrawPathDOF Lite closed by vreg-number levers from the mwcc_dbg FPR/GPR colouring dump

- status: works
- tags: drawpathdof,regalloc,fpr,gpr,debugger,vreg
- scope: egg/gfxe/eggDrawPathDOF

symptom: internalDrawLite 26 lines after an exhaustive 2687 statement-order search: size.x/size.y load order, tan/inv/absZ FPRs, W/H lwz GPRs, preheader zero vs signed magic
cause: colour order is descending vreg (temps > @inline vars > named, later @ expansion = lower vreg); target needs tan (@GetTanFovy) coloured before the size.x load (a temp), inv before absZ (@FAbs), W lwz before H lwz, half after the H fctiwz; a named local declared after i drops i's degree in sweep 1 and scrambles callee-saved GPRs; zero's hoist position follows its first statement
fix: f32 sx = GetSize().x (named, below tan's @); height = GetSize().y; width/height declared before the loop; f32 inv declared first + __fabsf(z) builtin (named, so inv > absZ); named half = GetSize().y*0.5f; zero declared after the alpha line: 26 -> 0 (each step measured: 32/30/30/20/46/4/0)
