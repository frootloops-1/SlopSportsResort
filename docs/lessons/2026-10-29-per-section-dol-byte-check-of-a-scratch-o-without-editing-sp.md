# Per-section DOL byte check of a scratch .o without editing splits

- status: works
- tags: dol,verification,split,tooling
- scope: any
- source: claude/w-sd2-801d0120-1029

symptom: need to prove a proposed split or TU source reproduces DOL bytes before the orchestrator edits splits.txt
cause: objdiff needs config; the real link needs splits
fix: compile the scratch TU with the unit's flags, relocate it against main.dol: section bases from the proposed split, extern addresses from symbols.txt, r2=0x804C7A20, r13=0x804C5380, drop unreferenced locals, resolve weak @STRING@ to the earlier copy. Script: /private/tmp/scratch-sd2-801d0120-1029/dolcmp.py
