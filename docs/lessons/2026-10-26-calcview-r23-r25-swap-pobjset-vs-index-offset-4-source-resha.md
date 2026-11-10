# CalcView r23/r25 swap (pObjSet vs index offset): 4 source reshapes no gain

- status: fails
- tags: egg,eggLightManager,regalloc
- scope: egg/gfxe/eggLightManager

symptom: orig pObjSet=r25, idx<<2 temp shares r23 with viewNo; ours swapped (99.6)
cause: unknown coloring order
fix: tried: declare pObjSet/pObj in other order (99.4), int i hoisted outside for (97.8), u16 idx local (95.6), pObj init then pObjSet=pObj (99.4): all worse; parked
