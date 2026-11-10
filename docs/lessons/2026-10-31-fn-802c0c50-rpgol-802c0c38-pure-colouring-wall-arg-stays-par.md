# fn_802C0C50 (RPGol_802c0c38): pure colouring wall, arg stays param vreg 33; every copy/alias/inline form folds back (99.3 nogain)

- status: fails
- tags: rpgol,802c0c50,regalloc,colouring,vreg,nogain
- source: worker nx-c50 2026-10-31

symptom: 99.3%: 65 changed operands same opcodes; self r30->r31, n r25->r30, arg r31->r25, plus one r0/r3 swap (score lbz vs pane-flag lbz)
cause: allocator replay (mwcc_dbg + color_sim): self=vreg32, arg=vreg33 both reach sweep 3, arg coloured first so gets r31; target needs arg as a non-param sweep-2 vreg numbered ~44-70, coloured after loop temps. MWCC numbers named locals in reverse declaration order; a local copy of a parameter keeps the parameter's vreg; a local from an inline accessor takes the accessor temp's higher vreg.
fix: Dead: alias local, by-value struct param, inline-helper param, inline whole lower half (70.7: nested inlines stop expanding), inline state-machine helper (identical), int getNumPlayers() accessor for n (98.7, n moves right but loop temps shift), accessor + parSum helper (98.5), SetVisible before sum (97.7), regsearch --generic ~1560 evals (best = baseline 64.2), version sweep a5.2/a5/a3.2-3.4 identical. Untested: real member fn in a vtable class (changes .data). Park.
