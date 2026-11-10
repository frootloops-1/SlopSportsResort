# AXFX reverb callback: read a guard field before an unrelated store

- status: works
- tags: FLOAT,schedule,stfsx,AXFX,permuter
- scope: src/revolution/AXFX/AXFXReverbHiExp.c
- source: nm-perm-1

symptom: AXFXReverbHiExpCallback 97.4%: +stfsx / load order around earlyLine[...] = data and if (reverb->preDelayLength != 0)
cause: orig loads preDelayLength before the early-line store; reading the field in the if after the store lets MWCC reorder differently
fix: local u32 preDelayLength = reverb->preDelayLength; placed before the store, test the local: 97.4 -> 99.0 (permuter find, 570 -> 170)
