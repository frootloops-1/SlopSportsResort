# ef_animcurve Rotate second state and pointer phase fail function score gate

- status: fails
- tags: ef_animcurve,Rotate,register-allocation,objdiff
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After first random phase win99.068054/132 lines, ra4/rb5 differ from target; key setup also has independent preRA scheduling wall.
cause: Additional phase aliases alter allocator/coalescing globally; raw instruction-diff gains and fuzzy objdiff score can disagree.
fix: Split both random states:98.55671/154, rejected. Split first range pointer generation rangeA from execution ra:98.90265/38 lines, identical opcode counts and major colour improvement, but verify regression vs99.068054 so rejected. Preserve rotate_phase_ra.cpp for future gated work; never claim 38 lines is accepted. Two no-gain score trials reached.
