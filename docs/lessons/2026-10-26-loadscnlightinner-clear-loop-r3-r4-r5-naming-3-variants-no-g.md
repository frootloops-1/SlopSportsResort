# LoadScnLightInner clear-loop r3/r4/r5 naming: 3 variants no gain

- status: fails
- tags: egg,eggLightManager,regalloc
- scope: egg/gfxe/eggLightManager

symptom: orig counter r5, ppLightSet r4, temp r3; ours counter r3, ppLightSet r5, temp r4 (99.6)
cause: unknown
fix: tried: pSet->lightId[i] form (97.4), pObj pointer instead of LightObj&, local ppSet hoist: no change/worse; parked
