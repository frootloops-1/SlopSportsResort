# resort: mwld internal error ELF_gen.c 2802 = data split starts below its section alignment

- status: works
- tags: resort,splits,linker,sdata2,alignment
- scope: splits.txt data ranges
- source: carve_unk.py 2026-11-09

symptom: After cutting a unit's .sdata2 range, link fails: internal linker error File 'ELF_gen.c' Line 2802
cause: The new piece started at a 4-mod-8 address (a float) but held 8-aligned doubles, so the object's section alignment was 8 and its start cannot sit there
fix: Round each data cut up to the max symbol alignment inside the piece (earlier symbols stay with the previous unit); tools/carve_unk.py does this. The real boundary was 0x80700930, not 0x8070092C
