# RPBox cf93c D7920: pre-RA dump shows mr r3 hoisted above lfs 4(base); s-load placement variants and regsearch flat

- status: fails
- tags: RPBox,cf93c,fn_802D7920,scheduler,mwcc_dbg
- scope: RPBox_802cf93c

symptom: fn_802D7920 li r3 vs r4 for the lbl_804C4DF0 base (99.88)
cause: In backend-02 the prepass scheduler puts mr r3,self before lfs f37,base,4 because the hoisted s load (lfs f33) leads the block, so the base vreg interferes with r3 and takes r4. The target needs mr r3 after that lfs.
fix: No source found. Flat (identical output): s declared after the M stores, lbl_804BDC30 inline in both lerps, scaleX/scaleY locals; regsearch --generic -j3 6 min = 101 evals, best stays 0.5 (baseline). Do not repeat.
