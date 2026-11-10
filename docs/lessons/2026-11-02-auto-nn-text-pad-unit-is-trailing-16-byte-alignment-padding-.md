# auto_NN_*_text pad unit is trailing 16-byte alignment padding: extend the previous split

- status: works
- tags: splits,padding,auto_unit,MetroTRK,targimpl

symptom: auto_03_800C54C4_text: a 12-byte all-zero .text unit (pad_03_800C54C4_text) between targimpl.c and targsupp.s counted as an unmatched tier-A function
cause: Zero bytes aligning the next object (0x800C54D0) to 16; not code, not a real unit
fix: splits.txt: targimpl.c .text end 0x800C54C4 -> 0x800C54D0, dtk split, rebuild. DOL 0, sym_addr_check unchanged, unit count 1147 -> 1146, targimpl stays 100. Check other auto_*_text/pad units the same way (zero-filled, followed by an aligned unit).
