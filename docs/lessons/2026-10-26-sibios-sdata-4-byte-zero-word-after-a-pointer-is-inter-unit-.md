# SIBios .sdata: 4-byte zero word after a pointer is inter-unit alignment padding, shrink the split

- status: works
- tags: SIBios,sdata,splits,padding
- scope: revolution/SI/SIBios
- source: SIBios session 3

symptom: .sdata 66.67; writable zero word at 0x804BD9A4 after __SIVersion; const/non-const zero globals land in sdata2/sbss
cause: The word is linker alignment pad before the next unit's 8-aligned .sdata, not an object of this unit (same as the .bss gap)
fix: splits.txt: SIBios .sdata end 0x804BD9A8 -> 0x804BD9A4; .sdata 100, DOL 0 diff, sym check 4 known
