# Flip diff with EQUAL total size: an unreferenced named sdata2 word was dead-stripped; force_active it in symbols.txt

- status: works
- tags: flip,force_active,sdata2,dead-strip,RPGol_802aaf88
- source: RPGol_802aaf88 48989e73c

symptom: Flipped unit objdiff 100%, DOL sizes equal but ~13.7k differing bytes; first data diff is a one-word shift in .sdata2.
cause: Unit's unreferenced global lbl_804C44BC (4-byte zero word) is dead-stripped by the linker; later .sdata2 shifts 4 bytes until the next unit's 8-aligned section start re-absorbs it, hiding the size change.
fix: Add force_active to that symbol's line in symbols.txt, rerun dtk dol split and configure.py. Tell: nm -n main.elf lacks the named symbol. Diagnose with a per-section DOL diff count then compare words near the first diff.
