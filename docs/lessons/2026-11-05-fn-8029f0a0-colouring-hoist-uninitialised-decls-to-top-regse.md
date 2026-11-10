# fn_8029F0A0 colouring: hoist uninitialised decls to top (regsearch --generic)

- status: works
- tags: rpgol,rpgolplayer
- scope: Pack/RPSports/RPGolScene/RPGolPlayer

symptom: 97.9 reg colouring
cause: decl order
fix: declare h,q,m,ok uninitialised at function top
