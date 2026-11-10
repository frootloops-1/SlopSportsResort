# resort: ported ogws units need -DVERSION_RSPE01_01; asm after a compiled unit needs align:16

- status: works
- tags: resort,porting,headers,alignment,splits
- scope: library porting
- source: lib-header-fixes 2026-11-09

symptom: Wii/1.0 'work1 was not assigned to a FPR register' in math_arithmetic.h FInv; after flipping, following code shifts by -4/-8/-12
cause: port_flip stripped VERSION_RSPE01_01 so ogws #if/#elif version blocks took neither branch; dtk emits auto/asm units with .balign 4 while the original C++ object after it was 16-aligned
fix: port_flip appends -DVERSION_RSPE01_01; add align:16 to the next .text split (named from ogws unit order if auto). Also: newer SDK functions at a unit edge (RFL_DefaultDatabase Unk_8010AE84/AEC0, scapi_prdinfo Unk_80054850 + CHN area) written exact first try
