# Weak @STRING@ header-inline strings at the start of a unit's .data belong to the previous unit's split

- status: works
- tags: splits,data,weak,STRING,egg
- scope: egg/gfxe
- source: claude

symptom: eggPostEffectBlur .data 56%: target .data starts with @STRING@SetProjectionType strings our object never emits
cause: eggPostEffectBase.o emits them weak at the end of its .data (inlined SetProjectionType); the split boundary was wrong
fix: move the split boundary after the strings (+pad), mark them scope:weak; previous unit stays 100%
