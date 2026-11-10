# Inline return vars lower a shared load's degree so it colours late (b340 BD58/DED4)

- status: works
- tags: regalloc,inline,degree,colouring,b340,BD58,DED4
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: hoisted load L (lbl_804BDDA0) should colour first (f0) but ours late; named-var and helper sweeps all failed
cause: 6 selLerp inline return @-vars had vregs below L; simplify removed them first, dropping L degree 41->31 < K=32, so L was not deferred
fix: write the lerp expression directly in selLerpV (delete selLerp): L stays high-degree, deferred, coloured first. BD58 89.5->100, DED4 91.4->100. Diagnose: regalloc-fpr-pass-1-all dump, which nodes defer (degree>=32 after lower-vreg neighbours removed)
