# ef_animcurve F32 scalar flag reference and output reference regress

- status: fails
- tags: ef_animcurve,F32,register-allocation,reference
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Helper flagsv121 r27 vs target22; n124r28 already right.
cause: F32-only scalar ref clone changes key/branch CSE (3 extra lhz and two cmpwi replaced by rlwinm.); caller outref preserves loads but misses saved colouring.
fix: Scalar-ref flags clone94.32933/799 lines and safe flags outref95.52052/784 vs95.615616 baseline. Both reverted, original shared helper unchanged. Prepared but untried frame-result outref isolates loop/frame swap. No helper retained.
