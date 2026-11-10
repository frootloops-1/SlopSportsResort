# ef_animcurve F32 narrow caller seed address also regresses

- status: fails
- tags: ef_animcurve,F32,coalescing,reference
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: U8 caller seed address boundary gave verified saved-map gains; F32 inline rangeIdx blocks loopr4.
cause: Narrow caller seed boundary in F32 changes more than the intended coalesced identity and does not meet score gate.
fix: Only dual first call: u16 cmdSeed0=*(u16*)v0; pass &cmdSeed0 to existing helper, otherwise unchanged. F32 95.615616->95.558556/884lines, reverted. Frame-output/expanded-body trials already rejected. No source helper retained.
