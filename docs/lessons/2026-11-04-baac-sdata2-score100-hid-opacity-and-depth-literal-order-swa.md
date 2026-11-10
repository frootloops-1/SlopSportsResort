# BAAC sdata2 score100 hid opacity and depth literal order swap

- status: works
- tags: fn_8020BAAC,sdata2,pool,marker,objdiff
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-baac-1104

symptom: unit_cmp gave sdata2 100 but raw source bytes had -120 before 255, opposite retail, so source SDA relocations could not match original DOL.
cause: Objdiff paired pool atoms by value despite physical order; the getter loop introduces depth before opacity calculation.
fix: R17 dead (void)255.0f before the loop seeds opacity first, changes no code, and makes all sdata2 bytes equal retail plus linker zero alignment tail. Live f32 local adds FP state; const local adds a duplicate pooled constant. Rename only the three changed local pool names after verifying same-address bytes/sizes.
