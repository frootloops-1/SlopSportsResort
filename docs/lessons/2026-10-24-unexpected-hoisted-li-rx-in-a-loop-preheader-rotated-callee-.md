# Unexpected hoisted 'li rX' in a loop preheader / rotated callee-saved block: move the scalar init to its first use

- status: works
- tags: regalloc,loop,hoist
- scope: VF
- source: claude

symptom: VFiPFENT_ITER_DoGetEntry 98.1%: all param regs rotated, extra li in preheader
cause: a scalar initialised at the top of the loop body is hoisted to a callee-saved register
fix: move 'name_len = 0;' to just before its first use (98.1 -> 99.9). Hoisted loop constants get registers in creation order of the pre-schedule stream; reordering two statements inside an inlined function moves them
