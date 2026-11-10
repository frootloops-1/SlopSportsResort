# ef_animcurve U8 named raw stride intermediate canonicalizes

- status: fails
- tags: ef_animcurve,U8,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: At99.54622, initial clique raw add0/rangeoffset6/keyoffset8 differs target8/0/6.
cause: Named single-def rawKeySize does not change emitted allocation; the candidate graph was not dumped.
fix: u32 rawKeySize=count+13; keySize=rawKeySize&~1 at original computation is identical99.54622/38lines. Reverted. Earlier interp movement also failed; park after two no-gain trials. Untried evidence-grounded found-key variant: cursor phase then pass already-loaded flag, removing rejected phase old-base lifetime.
