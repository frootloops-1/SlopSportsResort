# Data diff of one byte: check string case and float ULP

- status: works
- tags: rodata,sdata2,string,float
- scope: RPTns
- source: RPTns_80222a70

symptom: .rodata/.sdata2 98-99% with identical sizes
cause: string literal case typo (tns_ vs Tns_) or float literal 1 ULP off (0x3e19999a vs 0x3e199999)
fix: decode objdiff data_diff bytes; write 0.14999999f for 0x3e199999; fix string case
