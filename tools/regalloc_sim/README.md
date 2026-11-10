# MWCC colouring simulator (from fn_80320EFC, 2026-11-06)

Offline model of MWCC's graph-colouring order, fed by `tools/mwcc_dbg.sh` dumps.
Model: each pass walks vregs ascending and removes nodes with < 32 neighbours (FPR; ~27-29 GPR),
counting physical regs + not-yet-removed vregs; colouring runs in reverse removal order; a
callee-saved value takes the lowest already-used free register, else a new one from f31/r31 down.
Reproduced all FPR/GPR choices for fn_80320EFC. `sim.py` = FPR sim, `simg2.py` = GPR,
`exp.py`/`expg.py` = try graph edits (drop/add edges) before changing source.
Scratch-quality scripts: read the source before use; paths/args are hard-coded in places.
See lessons: `python3 tools/lessons.py search allocator model`.

`vsim.py <regalloc-gpr-pass-1-assigned.txt>` recolours volatile GPRs (lowest free r0/r3..r12 in dump order; 0 mismatches on fn_8031A0E0 dumps). `vexp.py <file> "61=bk,60=j1" "60<61"` moves node 60 before 61 and prints the new colours.
