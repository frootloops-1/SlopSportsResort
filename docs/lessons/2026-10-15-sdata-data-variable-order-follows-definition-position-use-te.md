# sdata/data variable order follows definition position; use tentative decl + late initialized definition

- status: works
- tags: sdata,order,tentative
- scope: revolution/VI

symptom: vi3in1 sdata order: __tvType first in ours, after __cc4 in target; DOL data refs shifted
cause: initialized statics are laid out in source definition order
fix: static u32 __tvType; (tentative, early) and the real static u32 __tvType = 0xFF; where the original defined it
