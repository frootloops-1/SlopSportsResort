# CpuTexture setColor with debugger oracle: 22 more constructs, offset-form and red-hoist families, no gain

- status: fails
- tags: cputexture,setcolor,regalloc,debugger
- scope: egg/gfxe/eggCpuTexture

symptom: need red = old vreg (coloured last, r8) and offset = new temp (r0); baseline has red as expression temp (coloured first) and offset as multi-def named var (last)
cause: two families, both blocked by the optimiser: (a) keep offset a non-forwardable multi-def var (+= form, pixel/store inline helpers, red via inline param, dead second assign): output identical, 8 lines, red stays an expression temp; (b) make offset a pure expression or single-def (indexed store, no offset var, pix/blk named, pixel helper inside the expression): buffer load is reassociated early and this/x swap, 40-42 lines; (c) hoist red above the switch (even after the asserts): load stays above the compare, 55 lines
fix: none. Insight: single-def values are forwarded/reassociated, so the target's all-temp shape (blk32 + pix, buf added by stbx) has to come from a construct the optimiser keeps as separate values without a named var; untried: a function-local struct/array for the pixel coords, or a different split of the (x,y) tile math across two inline helpers returning the products. Source restored
