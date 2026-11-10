# Opus nogain batch: LinkNpcLanes, CpuTexture setColor, fn_801BF6C4, fn_80227C3C

- status: fails
- tags: regalloc,rename,loop,ctr
- source: claude/nm-3 2026-10-16

symptom: single REGALLOC rename near-misses (99.6-99.8) after permuter nogain
cause: unknown; swaps of loop pointers/counters
fix: failed: LinkNpcLanes temps/const map/index forms/u32 i (89.8)/ref (98.3); setColor offset forms (pixel temp swaps params, 93.6); fn_801BF6C4 local inline copy, decl moves, u32 count; fn_80227C3C for/while form gives target regs but becomes mtctr/bdnz loop (96.3) - need a form that blocks ctr conversion
