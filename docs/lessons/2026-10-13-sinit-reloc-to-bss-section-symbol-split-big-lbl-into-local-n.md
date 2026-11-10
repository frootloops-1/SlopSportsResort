# sinit reloc to .bss section symbol: split big lbl_ into local @NNNN 0xC dtor-chain entries + named static

- status: works
- tags: sinit,bss,symbols,dtor-chain
- scope: Pack/RPKernel

symptom: __sinit 99.7%, .bss 28.57%
cause: original lbl_ covers dtor chain records + static array; objdiff relocs differ
fix: symbols.txt: 4 local 0xC @NNNN entries + sTagColors__31@unnamed@..@ local; sinit and .bss 100
