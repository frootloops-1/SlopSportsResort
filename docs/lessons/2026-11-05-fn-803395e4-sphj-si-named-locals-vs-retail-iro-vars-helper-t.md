# fn_803395E4: sphJ/si named locals vs retail IRO @vars; helper too big to inline

- status: open
- tags: colouring,iro,inline-helper,fn_803395E4
- scope: Pack/RPSports/RPBowScene/RPBow_803381DC

symptom: 234-line GPR+FPR diff; sphJ/si coloured last in ours, retail sphJ first and si after the nearI IV
cause: retail sphere pointers are @vars (IRO/inline), ours named; removing the locals reloads pins (more code)
fix: open. Dead: decl-order perm, pj/pi/sph removal, si=&sphI[a], a/b-loop inline (not inlined: n 489), k-loop inline (190), BowResolvePinContact call (218), statement perms (only vi/vj order matters, vi-first +5)
