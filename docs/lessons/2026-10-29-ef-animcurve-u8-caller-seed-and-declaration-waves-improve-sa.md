# ef_animcurve U8 caller seed and declaration waves improve saved map to 99.18908

- status: works
- tags: ef_animcurve,U8,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: nextLoop61 colours before parameters, seed24,target23,header22,range21 vs target25,24,23,22.
cause: Ascending simplify waves control ordering; right seed optimizer temp leaves nextLoop at degree29 during proposed triple-hoist. Named caller seed read passed by address removes that late blocker.
fix: Bare nextLoop before pKeys98.768906->99.0. keys,nextLoop,rightRangeIdx,keySize before pKeys plus caller right seed passed by address99.05042. Bare n before early flags99.09664 (n20 flags21). idx before loFrame99.18908. Exact opcode multiset retained; each has actual compiler graph; target saved hierarchy now correct, not a full match.
