# schedule once + solved declaration order reproduces callee-saved FPR colouring (fn_801BD7E0 100%)

- status: works
- tags: fpr,scheduling,regalloc,pragma,marker,RPUtlDirMath
- scope: Pack/RPUtility/RPUtlDirMath
- source: claude/dirmath-1027

symptom: retail keeps all loads early and long-lived weights in f29-f31; every natural form under default scheduling stays all-volatile (pre-RA scheduler sinks loads next to uses, even locals/register locals declared first)
cause: MWCC default is schedule twice; the pre-RA pass reduces pressure. With '#pragma schedule once' RA runs on source order; colouring then goes in declaration order (compiler temps such as a 2.0f literal first), lowest free volatile f0-f13 else f31 downward, preferring a dying operand's register (lowest one)
fix: MATCH-PENDING marker: #pragma schedule once/reset around the fn, one value per statement in retail instruction order, all locals on one declaration line in an order solved by a small colouring simulator (scratch sim2.py/solve2.py idea: greedy-random order where each node's simulated colour equals retail's); try several solutions, ~1 in 6 matched exactly
