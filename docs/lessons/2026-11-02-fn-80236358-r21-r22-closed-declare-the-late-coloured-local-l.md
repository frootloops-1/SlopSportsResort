# fn_80236358 r21/r22 closed: declare the late-coloured local LAST (h), hoist inner-block fa/fb above it

- status: works
- tags: regalloc,colouring,declaration-order,RPTns_80235cd0
- scope: RPTns_80235cd0 fn_80236358

symptom: fn_80236358 99.8%: r21/r22 swap between hoisted li 1 (vreg 95) and slwi temp (vreg 47)
cause: h (vreg 38) was pushed in simplify sweep 1 because lower-numbered neighbours fb/cur dropped its degree; the hoisted li was coloured before it
fix: Declare void* h last in the loop body and hoist int fa, fb to the loop top so h has the lowest named vreg, keeps degree>=29 through sweep 1 and lands in sweep 2. Check with a sweep-membership replay (tools/color_sim.py on mwcc_dbg dump). Corrects 2026-11-02 lesson: h and the slwi temp need not be merged; the earlier 'h after idx' failed because fb/cur were still numbered below h.
