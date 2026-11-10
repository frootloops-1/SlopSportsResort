# Empty-ctor array members leave a trip-count remnant; first element is peeled (array starts one element earlier)

- status: works
- tags: ctor,array,loop,remnant,rpsports
- source: sp8020f-1104

symptom: fn_8020F530: 3x (addi begin; addi end; mulhw /648; addi n+1; cmpwi 8) with no stores, 21 insns short
cause: out-of-line ctor of a class with SelRow rows[3] arrays (SelRow contains SelEntry e[40] with empty inline ctor); MWCC peels element 0, so the remnant loop starts at rows+1
fix: class with three SelRow[3] at 0x68, real ctor __ct__11SpSelPickerFi (symbols rename + one Matching caller updated); objdiff showed 100 while immediates differed: byte-compare
