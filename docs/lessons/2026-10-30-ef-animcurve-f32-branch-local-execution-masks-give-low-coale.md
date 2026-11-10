# ef_animcurve F32 branch-local execution masks give low coalesced identity

- status: works
- tags: ef_animcurve,F32,register-allocation,phase,mask
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After the flags-threshold gain, the execution mask occupies r5 instead of target r0. An immediate scan/execution copy was a known failure.
cause: Six mutually exclusive execution-mask copies coalesce to the lowest caller-local identity, r37, instead of the original r73. The actual f32-masks dump confirms mask r37 -> r0 and preserves the corrected saved-register hierarchy.
fix: Scan using scanMask, then initialize a local u8 mask from it immediately before each of the six execution loops. F32 95.85085 -> 95.95095; 724 -> 610 changed lines. Other five functions unchanged; .sdata2 100%. The copies represent separate loop state and introduce no helper. Count, key, range and later interpolation register roles still differ. Not a full match.
