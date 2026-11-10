# fn_80200600 / fn_80200A88 (RPSports_801ffec0): GPR colour-order residue, helper boundaries do not move it

- status: fails
- tags: regalloc,colouring,inline,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: 600: two-branch a r28 vs r29, loop IV r30 vs r29; A88: self r31/IV r30/i r29 vs retail IV r31/i r30/self r29
cause: mwcc_dbg: IRO IVs (r55-57) colour before named r (r45); self coloured first despite low vreg
fix: failed: shared fn-level i, row-body inline helper, play-last inline, TV-adjust inline, SetFwd/SetBwd inlines, typed self param vs local copy. A88 IV form fixed by indexing self->rows[i] through the struct (0x70(r31))
