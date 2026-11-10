# ef_animcurve Texture fresh header assignment and pointer getter canonicalize

- status: fails
- tags: ef_animcurve,Texture,register-allocation
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Texture 99.71850 still needs header r31 instead of r24; n r31/tick r31 disjoint.
cause: Header local remains coalesced with oldest pCmdList vreg32.
fix: Two no-gain tries: assign pHeader inside pKeyTbl expression; inline getter reading through u8** and local raw pointer. Both 99.71850 and 42 normalized changed lines, identical to retained baseline. Reverted; no helper retained.
