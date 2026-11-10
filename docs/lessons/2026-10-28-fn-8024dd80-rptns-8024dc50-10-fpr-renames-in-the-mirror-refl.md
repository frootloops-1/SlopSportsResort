# fn_8024DD80 (RPTns_8024dc50): ~10 FPR renames in the mirror/reflect block are scheduler residue

- status: fails
- tags: regalloc,fpr,schedule
- scope: RPTns_8024dc50 fn_8024DD80
- source: FPR batch 2 2026-10-28

symptom: 98.26
cause: statement reorder changes the load schedule, helpers leave colouring unchanged
fix: none: 6 orders of the 4 negation statements (95.9), tnsReflectXZ by pointer or float params (98.26/92.5), named negated locals, dot operand swap, 2*dot*n form. park
