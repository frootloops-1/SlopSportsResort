# ef_animcurve U8 scan and execution mask phase split improves table colours

- status: works
- tags: ef_animcurve,U8,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: U8 98.44958 with mask r30, tables r29/r28; 524 normalized changed lines.
cause: The early scan mask coalesces into a later execution-mask local with a lower vreg representative.
fix: Rename initial scan variable scanMask, copy to u8 mask immediately after pRandomTbl setup. U8 98.52521, 494 changed lines; tables r30/r29, mask r28. No new marker. .sdata2 100, DOL 0; object not a full match.
