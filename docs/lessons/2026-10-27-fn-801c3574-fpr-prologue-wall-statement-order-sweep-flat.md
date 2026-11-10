# fn_801C3574 FPR prologue wall: statement-order sweep flat

- status: fails
- tags: fpr,register,wall,frustum
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-opus

symptom: after GPR fix, 60-68 diff lines remain: FPR numbering (ours f0-f8, retail f0-f7) in the ratio/y/x/z block
cause: register colouring order; not reached by source order
fix: none found: 24 topological orders of w/h/y/ratio/x/z, dist local, inline x/z, helper variants for y all 60-68 lines; park
