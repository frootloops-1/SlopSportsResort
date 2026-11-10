# ef_animcurve F32 frame output is flat and dual seed body expansion regresses

- status: fails
- tags: ef_animcurve,F32,inline,register-allocation
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: F32 loop75 r6 is blocked from r4 by inline rangeIdx87, not late frame-result120.
cause: Frame output helper canonicalizes to unchanged source graph; caller expansion changes inline range identities and full schedule.
fix: F32-only caller frame out-reference clone produces identical95.615616/772lines. Dual first hash body expanded left-to-right with caller u16 cmdSeed0 gives95.10010/914lines; reverted. No helper retained. Narrow caller cmdSeed0 address substitution still untested; park after two no-gain trials.
