# fn_802B2740: field pointers in saved regs via base+N pointer arithmetic

- status: works
- tags: rpgol,802b1a0c,regalloc,pointer
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: retail pins self+0xB0..BC field ptrs in r31..r28; ours folds to self offsets, 16B size gap
cause: MWCC folds &self->field and base+0 into self offsets but not base+N
fix: float* base=&self->fac; b0=base+1; b4=base+2; b8=base+3; bc=base+4 (no helper); also *bc *= 0.9f; *bc += 0.1f*x split
