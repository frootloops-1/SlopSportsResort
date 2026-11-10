# TU-boundary sweep: data-ownership xref finds mis-split sdata2/rodata and 'defined here as data' hacks

- status: works
- tags: split,sdata2,rodata,sweep,boundary,xref
- scope: RPSports_801E7EB4,RPBow_8031EFE4,RPBox_802c7924,RPBowNpcManager,RPSports_801f9150

symptom: Unit at 99%+ code but data sections 50-98%, or a Matching neighbour defines a string/float 'as data' that its own code never uses
cause: Split asm shows the object owned by unit A but referenced only by an adjacent unit B's functions (A's rodata/sdata2 range is off by 4-16 bytes, or text boundary is a few functions early)
fix: Parse build/RSPE01_01/asm/*.s (skip *_unsplit): owner map from .obj, ref map from .fn bodies; flag sdata2 float/rodata objs with foreign-only refs and fns whose only data refs are adjacent-unit objects. Found 801E7EB4/801ea458 sdata2@0x804C1F50, 8031C388/8031EFE4 rodata, Gol_802c7660/Box_802c7924 sdata2@0x804C4CA8, 80330FE8+NpcManager merge, 801f8750/801f9150 text. Note docs/tasks/sweep-tu-boundaries-2026-10-29.md. Pitfalls: dedupe single-value objs only; f0 pairs are pad noise; cross-unit float sharing in Gol/Tns also occurs in Matching units (weak inline consts).
