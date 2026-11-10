# resort: cutting game-code containers: duplicate .sdata2 values, per-file string-pool base and vtable, repeated weak tails

- status: works
- tags: resort,splits,bowling
- scope: resort
- source: bowling-rest

symptom: one unk/sinit unit holds many Resort-only layout UI files
cause: each file has its own .sdata2 pool (so 1.0/0.5/-1 repeat), own .rodata string-pool base, own vtable; weak-tail sequences repeat at each file end
fix: cut at those boundaries; sinit_804F2830 became 15 units with the DOL OK
