# F1 split target symbols to match source object boundaries (bss 0x28 -> 0x1C+0xC, sdata2 8 -> two 4)

- status: works
- tags: F1,symbols,bss,sdata2
- scope: RPBox_802e9774,RPBox_802f438c
- source: claude/nm-data

symptom: hidden: reloc lbl_X+28 vs ours separate lbl_Y; lbz from pooled 8-byte const
cause: target symbol larger than source objects
fix: split symbol at the source object boundaries, compiler arrays named @N (RPBox_802e9774, RPBox_802f438c)
