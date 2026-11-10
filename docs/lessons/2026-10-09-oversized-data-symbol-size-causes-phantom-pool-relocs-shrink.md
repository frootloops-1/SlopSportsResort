# Oversized data symbol size causes phantom pool relocs; shrink to real size

- status: works
- tags: symbols,splits,msl
- scope: any unit
- source: claude/msl-text wprintf 2026-10-09

symptom: code identical but function 99.9% and .rodata/.data section <100; objdiff shows R_PPC_NONE pool reloc on an addi past the end of a string pool
cause: symbols.txt object size includes trailing alignment padding (lbl_8037BF48 0x8, lbl_80399280 0x58)
fix: Set the symbol to its real size (0x1, 0x56); same as gap_* padding symbol removal for printf. Also wprintf: float2str param long double so MWCC pools 0.0 with double2hex's; __wpformatter bad-conversion case 0xFFFF
