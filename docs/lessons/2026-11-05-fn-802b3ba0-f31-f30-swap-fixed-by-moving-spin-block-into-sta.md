# fn_802B3BA0: f31/f30 swap fixed by moving spin block into static inline helper

- status: works
- tags: rpgol,802b1a0c,regalloc,inline
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: d/c swapped f31/f30; decl order no effect
cause: inline helper boundary changes colouring
fix: static inline golSpinX(GolPBS*, const GolV3&); lerp: uninitialised locals declared up front then range=0.5f; range-=start; f198 -= m; f198 *= 0.9f
