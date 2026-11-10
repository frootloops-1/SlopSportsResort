# Member-wise struct stores kept on stack: struct shares a member whose address escapes

- status: works
- tags: stack,struct
- scope: RPGol_802b8568
- source: fn_802B8920

symptom: stores not removed, re-read from stack
cause: address of sibling member passed to call
fix: struct GolXform{ GolMtx33 r; GolVec t; }; pass &x.r
