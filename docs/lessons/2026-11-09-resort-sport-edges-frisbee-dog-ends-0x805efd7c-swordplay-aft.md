# resort: sport edges: Frisbee Dog ends 0x805EFD7C (Swordplay after); text_804C17A8 starts with Canoeing VS layouts; sinit_8047F38C is Table Tennis

- status: works
- tags: resort,sport-map
- scope: resort
- source: can-fld

symptom: sport_map boundaries wrong
cause: attribution by resource votes; png_hit_can is a Table Tennis can target
fix: 0x805EFD7C-0x805F181C is Swordplay (unk/sinit_805EFD7C, sinit_805F0C58); unk/text_804C17A8 holds 65511-65515_can_VS_* layouts then Bowling score layouts - split it when next touched
