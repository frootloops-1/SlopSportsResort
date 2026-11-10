# ef_animcurve Rotate successor-pointer flag load regresses current tail

- status: fails
- tags: ef_animcurve,Rotate,regalloc,tail,pointer
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Rotate is 99.1673 with 28 changed lines. The values pointer needs a real same-block successor before the boolean temporaries.
cause: Computing v1 before reading the flag through reinterpret_cast<u8*>(v1)[-10] changes allocation/scheduling widely instead of closing the tail.
fix: One bounded trial regressed 99.1673 -> 97.47164 with 399 changed lines and was reverted. It differs from a plain statement reorder but is not a viable fix. The pointer-steering comment was not retained. No fresh rejected-candidate graph was captured, so the exact pass responsible is unproven.
