# Literal 0 divisor breaks MWCC (error 10139)

- status: works
- tags: mwcc,inliner,division,RPUtlLytFrameCursor
- scope: Pack/RPUtility/RPUtlLytFrameCursor
- source: docs/tasks/QUEUE.md, RPUtlLytFrameCursor row, 2026-10-08

symptom: MWCC internal error 10139 when building RPUtlLytFrameCursor; alphaRatio divides by a literal 0.
cause: The inliner folds a literal 0 divisor. The target really divides by int 0, so the division must survive.
fix: Call alphaRatio with a local 's32 limit = 0' instead of the literal 0.
