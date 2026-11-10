# Self->arr[i].field direct indexing vs element pointer local

- status: works
- tags: mwcc,loop,addressing
- scope: RPGol_802bca94
- source: opus-worker

symptom: GolLytBall* b=&self->ball[i] gave addi base+0x88
cause: pointer local strength-reduced differently
fix: index self->ball[i].field directly (mr rX,self + 0x88 offsets)
