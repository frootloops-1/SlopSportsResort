# golRemapClamp: if (0.0f == (d -= in0)) fixes in0 vs compare-zero colours

- status: works
- tags: fpr,remap,golf,RPGol_802c58d4
- scope: Pack/RPSports/RPGolScene
- source: opus pass 4

symptom: lim = golRemapClamp(1.0f,0.25f,...): target in0 f0 / compare 0.0 f1, ours swapped
cause: separate d -= in0 statement orders the zero literal temp after in0
fix: float d = in1; float r; if (0.0f == (d -= in0)) {...}; t's remap still matches
