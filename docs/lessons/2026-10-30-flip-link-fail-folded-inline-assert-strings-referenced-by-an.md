# Flip link fail: folded inline-assert strings referenced by another unit as lbl_ globals

- status: works
- tags: flip,link,undefined,assert-strings,eggShadowTexture,RPBsb_80252e7c,RPBow_8034E974
- scope: Pack/RPSports/RPBsbScene/RPBsb_80252e7c

symptom: objdiff 100% all sections but main.elf link fails: undefined lbl_803C5418/lbl_803C5428 referenced from RPBow_8034E974 fn_8034F168
cause: unit emitted the eggShadowTexture.h assert strings as anonymous literals; retail has them as globals in this unit's .data used by another unit
fix: define extern "C" char lbl_803C5418[] = "adjust >= 0.f"; char lbl_803C5428[] = "eggShadowTexture.h"; after the last .data table and use them in the inline assert; .data stays 100, DOL 0. Always try the DOL link before trusting a 100% unit
