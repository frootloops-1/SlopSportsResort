# 1.0 multiplier kept unfolded via inline returning 1.0f

- status: works
- tags: rpgol,rpgolplayer
- scope: Pack/RPSports/RPGolScene/RPGolPlayer

symptom: extern lbl stand-in for 1.0 left 12 fns at 99.9 (reloc)
cause: MWCC folds 1.0f*x literal but not inline return
fix: inline GolOne() at multiplier sites, plain 1.0f elsewhere (R17)
