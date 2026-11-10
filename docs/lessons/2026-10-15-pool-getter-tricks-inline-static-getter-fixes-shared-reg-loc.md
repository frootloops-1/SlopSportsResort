# Pool/getter tricks: inline static getter fixes shared reg; locals GXColor pool at parse time

- status: works
- tags: mwcc,regalloc,sdata2,RPBox
- scope: RPBox_802f438c

symptom: manager ptr and CreateData result should share r28; GXColor consts land before codegen floats in .sdata2
cause: named local vs direct spCurrent access; parse-time constant placement
fix: call through inline static getter RPGrpModelResManager::GetCurrent()->CreateData(); GXColor locals pool at parse time (function-local static const copy dropped to 74.9 - rejected); orig symbols split 4-byte consts into 1-byte labels (symbols.txt fix needed for reloc naming)
