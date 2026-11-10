# Unreferenced functions are dead-stripped from the DOL: add force_active in symbols.txt (shifts everything after)

- status: works
- tags: force_active,dead-strip,dol
- scope: config

symptom: flipping dolphin_trk/NETVersion/targsupp to Matching: millions of DOL bytes differ, sizes equal; first misplaced symbol is 4/8 bytes early
cause: gap_03_800C5A6C_text, NETGetRexPPCVersionPrintable, TRK*File stubs have no references so mwld strips them from OUR object; target keeps them
fix: append force_active to the symbol line in config/RSPE01_01/symbols.txt; locate with tools/sym_addr_check.py (first unique symbol whose linked address differs) and tools/dol_diff.py
