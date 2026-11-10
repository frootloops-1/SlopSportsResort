# Argument computed before an earlier call: wrap the call argument in a static inline

- status: works
- tags: order,args,inline
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig computes extrwi before bl; plain local moves it after
cause: scheduling of argument evaluation
fix: wrap the call's argument expression in a static inline (golCamDone())
