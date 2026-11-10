# permuter on MSL: sizeof(T)*N mis-parsed, compile error hangs wibo, cannot tune inlined helpers

- status: fails
- tags: permuter,msl,tooling
- scope: tools/permute.py
- source: claude/msl-text 2026-10-09

symptom: permute.py setup on MSL units gives nonsense base score or hangs
cause: pycparser prints sizeof(T)*N as sizeof((T)(*N)); a compile error makes wibo hang; pruning turns static helpers into prototypes so inlined helpers vanish
fix: Replace sizeof expressions with constants; the permuter cannot currently tune regalloc inside inlined helpers (needs a tool fix)
