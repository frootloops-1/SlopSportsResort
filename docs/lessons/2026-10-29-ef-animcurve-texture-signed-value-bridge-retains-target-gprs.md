# ef_animcurve Texture signed value bridge retains target GPRs at 99.97319

- status: works
- tags: ef_animcurve,Texture,reference,conditional,register-allocation
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Lifetime signed n reference gets target saved GPRs but ternary generates branch diamond; u8 bridge gets14diff.
cause: Ordinary signed bridge keeps branchless conditional arm eligible while delaying truncation until the arm expression.
fix: With command-to-particle phase and const s32& n, use s32 endFrame=n then ternary 0:static_cast<u8>(endFrame). Texture99.71850->99.97319/4diff lines (2FPR instructions); all saved GPRs match. n+0 folds and fails98.02949. R17 comments and ledger required for pointer/ref/alias steering. Not a full match.
