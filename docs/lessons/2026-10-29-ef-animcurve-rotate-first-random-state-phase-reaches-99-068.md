# ef_animcurve Rotate first random state phase reaches 99.068

- status: works
- tags: ef_animcurve,Rotate,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Rotate98.467865/172 normalized lines; dual random0 is r4 instead of targetr9.
cause: Separate generation/selection state from sign/channel execution state chooses a later, lower coalesced representative without changing instructions.
fix: Rename initial dual random0 to rangeRandom0 through F32Random+U8Select; after rb selection initialize u32 random0=rangeRandom0. Rotate99.068054/132 lines, identical opcode counts, random0 targetr9. No new helper; source preserves random-update order. DOL0, no other function/unit changes; not a full match.
