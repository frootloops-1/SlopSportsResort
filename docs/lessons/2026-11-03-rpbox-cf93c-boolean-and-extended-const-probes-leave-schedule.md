# RPBox cf93c: boolean and extended const probes leave scheduler walls open

- status: fails
- tags: RPBox_802cf93c,constsweep,bool,scheduling,vcall,FPR
- scope: RPBox_802cf93c
- source: 2026-11-03 codex-rpbox-cf93c-20261103; build/evidence/rpbox-pass/probe.py and const-probe.py

symptom: D235C vptr r5 vsr12; D7920 array base r4 vsr3; D98BC inline ternary ordering and D0404 branch-threading residue.
cause: Different IR/schedule identities survive scalar spelling changes; fixed-register call asm adds frame and CR saves.
fix: No gain: bool/u8/u32 BoxCond5a, all-bool condition chain, bool attack/swing, b ref/h unsigned; const virtual interface, raw const/volatile vptr, scheduling off, identical-arm ternary, comma virtual call; nonconst array element and blend helper. 37 targeted const sites were invalid or gave no regression-free gain. Discarded ABI call asm. Array address asm failed compilation: ignore its stale object score. Older compiler builds regress existing exact code. No permuter run.
