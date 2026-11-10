# ef_animcurve per-unit cflags sweep: nothing beats the unit's current flags

- status: fails
- tags: ef_animcurve,cflags,proc,inline,ipa
- source: xfer-1028

symptom: five fns share the same saved-reg-order wall, so a TU-level cause was suspected
cause: extra_cflags sweep on the unit: -inline deferred/noauto, -sdatathreshold 0 identical (97.78); -ipa off 97.76; -fp_contract on 92.45; -O4,s 35.37; -proc 750/7400/603e/604e fail to compile (headers use gekko paired-single asm). Compiler versions were already swept (lesson ef_animcurve callee-saved priority wall)
fix: TU-level flags/compiler are ruled out; the cause is in source structure (inline boundaries / vreg ages)
