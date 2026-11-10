# fn_801BB9B8 FPR wall closed: colouring simulator + named dx

- status: works
- tags: fpr,regalloc,mwcc_dbg,fn_801BB9B8,RPUtlCollisionModel
- scope: Pack/RPUtility/RPUtlCollisionModel

symptom: first-block FPR colouring wall 98.6 (delta/e1/e2 in wrong callee-saved regs), many source variants flat
cause: MWCC priority list = repeated ascending passes removing nodes with <32 remaining neighbours (phys counted); late-pass nodes coloured first. Inline dot() made d1/d2 @-temps that stayed in pass 2; delta.x needed a vreg below delta.z
fix: write first-block dots as expressions (not inline dot), unname d3 (distances[3] = ...), and name only dx before Vector delta(dx, cy, cz) (R17). Tool: replay regalloc-fpr-pass-1-assigned.txt neighbours in a python sim (reproduces our order exactly at K=32), map vregs to target regs by aligning backend-02 to target asm, then search single-vreg renumberings -> it pointed straight at delta.x
