# Matching unit links undefined global lbl_XXXX when a NonMatching neighbour's asm object reads its pool constant

- status: works
- tags: link,sdata2,flip,named-const,RPBow_80330FE8
- source: RPBow_80330FE8 011b312ca

symptom: Flipping a 100% unit to Matching fails at link: undefined 'lbl_804C6188'; objdiff shows 100%.
cause: A NonMatching neighbour (RPBowNpcManager) links from its original-asm object, which reads 0.0f/1.0f from this unit's .sdata2 by global symbol; the compiled unit only has local @N literals.
fix: extern const f32 lbl_X; declared first, then defined (= v) AFTER the last use, and use the name at every site of that value (all 0.0f incl. ctor args, else regalloc shifts). Defined before use gets folded into literals. Needs R17 marker + ledger row. Real fix: match the neighbour so units merge. Also: asm_diff.py normalises reloc names (said identical at verify 99.9%); use objdump -dr when they disagree.
