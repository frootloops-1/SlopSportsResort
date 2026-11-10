# regsearch: register-order search for one function (2026-10-28)

`tools/regsearch.py` compiles real source variants with the unit's own ninja compile command and scores them
against the original object. It replaces decomp-permuter for register-colouring and scheduling walls where the
permuter fails (C++ units, large float functions, helpers lost in the stand-in object). `tools/regroles.py`
prints the live range and spill features of every callee-saved register, original vs ours.

```sh
python3 tools/regsearch.py score  <unit> <fn-substring> [--src FILE]
python3 tools/regsearch.py search <unit> <fn-substring> --generic [--sites sites.json] -j 4 --minutes 12 --temp 8 --out build/search/<name>
python3 tools/regroles.py <unit> <fn-substring>
```

`<unit>` is the path under `src/` without extension (`nw4r/ef/ef_animcurve`). Needs a built original object
(`build/RSPE01_01/obj/<unit>.o`) and a ninja-configured worktree. Run one search per worktree (variants are written
to `build/search/`; the source file is never touched, the best variant is saved as `<out>/best.txt`).
Use `-j 4` or less: other workers share the machine.

## Objective

`score = 50*op + 10*imm + 4*rank + 0.25*reg`. `op`: instructions whose opcode stream differs; `imm`: same opcode,
different shape; `rank`: sum over callee-saved roles of |colour rank in the original - colour rank in ours| (roles
matched by instruction alignment, rank = register number counted down from r31); `reg`: register operand mismatches.
`rank` is the quantity that has to reach 0 for a colouring wall; `op`/`imm` guard the structure.

An earlier version scored with a coarse `perm` count and rewarded opcode alignment alone. It "improved" U8 to a
variant whose real rank distance was 30 against the baseline 28. Always read `rank` and `lines`, not only `score`.

## Mutations (`--generic`)

- hoist an initialised declaration to the function top (assignment stays in place), and bare block-scope declarations;
- integer type swaps (u8/u16/u32/s32/int families);
- swaps of adjacent pure declarations/assignments that share only read-only names, and of statements with
  disjoint identifiers;
- hand-written sites from JSON: `{"name": ..., "alts": [[{"sub": [old, new]} | {"suball": [old, new]} | {"decl": "T x;"}], ...]}`
  (alternative 0 is always the original).

The mutations assume the swapped lines are independent. A winning variant must be reviewed for meaning, then gated
(verify.py, DOL 0 bytes) before it is kept. A mutation can also touch another function that shares the same
anchor text (the first occurrence is replaced after earlier edits): read the diff of `best.txt` against the source.

## Validation (done before trusting it)

- Known fix rediscovered: pre-fix `AXFXChorusExp.c` `__CalcLFO` (needs `u64 diff`, the `(s64)diff * gradFactor`
  form, `(wtf = 1)` and a declaration-scope change). With explicit + generic sites the search reached score 0 in
  9 generations / 32 compiles (~2 s), and the winner gives 7/7 functions exact, `.text` 100.00% in verify.py. It found a
  declaration hoist that the hand-written sites had missed.
- A score of 0 agrees with verify.py (checked above); the baseline of an unmodified function reproduces
  `near_miss.py` (`lines` equals its `wrong=`).
- Race fixed during validation: identical rendered text from two gene vectors is evaluated once (single flight).

## Results on ef_animcurve

- `AnimCurveExecuteTexture` 99.53 -> 99.72 (32 -> 21 wrong lines) from hoisting `t`, `count`, `n` and two independent
  swaps; committed on the branch, not a full match.
- `AnimCurveExecuteU8`: generic search reduced rank 28 -> 21 with the opcode stream aligned, but the result is wider
  in reg tokens; not applied. regroles shows identical live ranges, use counts and loop weights on both sides with
  different colour orders, and neither order follows weight*(2*uses+defs). The order depends on IR vreg age (source
  declaration order / scoping), not on final-code features, so use-count hacks cannot move it.
- Tables before the mask loop (to mimic the target order) changes the opcode stream (the early return then follows
  the table loads); accessor chains and an out-param header helper compile to the same or worse code.

## Colouring rules learned by probing (GC/3.0a5.2 with the project flags; tools/regprobe.py)

Probe functions with controlled use patterns across opaque calls, 40 random patterns each, 5 parameters:

1. **Parameter saved copies are handed out strictly in argument order, newest argument first** (arg4 -> r31 ... arg0 lowest),
   independent of use count, first/last use, use order and loops.
2. **Locals are coloured before parameters** (independent call results: newest local first, then the parameters).
3. **A local pointer copy of a parameter is folded back onto the parameter**, so its saved register ranks as the parameter
   (lowest). All of these changed nothing: plain cast, cast via u32, accessor inline, out-parameter helper, reference alias,
   `const` pointer, `volatile` field access, identical-arm ternary, identical-arm if/else, `do { } while (0)`, `for` that
   re-assigns it, modifying the parameter after the copy, deriving it back from a table pointer.
4. **Only a real merge makes the copy a first-coloured local**: `H* h = a ? (H*)a : (H*)0;` gives colour order a, d, c, b
   (the target's `Texture` layout) but adds `cmpwi / beq / li`, which the original does not have.
5. Two values with disjoint lifetimes share a register, so a per-register role table can merge two vregs. In `Texture`,
   `tick` and the later temporary `length - 1` share r31 (ours) / r25 (target); in ours the temporary is coloured before
   the pHeader copy and takes r31 first.

Open for Texture/Child: the target has `mr r31, r3` as the first-coloured value with no compare or branch. A construct
with a real merge or a surviving distinct copy of the incoming parameter and no extra instruction has not been found.
Walking the parameter (`pCmdList += ...`) does make the header copy survive but adds 3-4 `mr` and shifts the tables
(lines 67 for walking the parameter, 44 for walking a copy, against 21 for the committed source).

## Third-party ef_animcurve.cpp (3070 lines), compared 2026-10-28

Compiled in our build with `AC_TARGET_TEXTURE1/2/IND` = 14/15/16: `Texture` rank 14 (same gap as ours, opcodes worse), `Child` rank 62 vs
60 (shape counts worse), `U8`/`Rotate`/`F32` far worse. Its F32Vec2/Vec3/N, U8Vec3 and two-pointer F32 belong to another
library version (the original has exactly 6 functions). Its Child declaration block is the one ours already uses. Across compilers,
the 3.0 family gives identical results and all Wii builds also give rank 14 on Texture, so the gap is not a compiler-version effect.

## REGSEARCH_DIFF=1 (2026-10-29)

`REGSEARCH_DIFF=1 python3 tools/regsearch.py search ...` ranks variants by `asm_diff`'s own number (changed lines of a unified
diff of the normalised instructions, x10, plus 0.25*reg as a tie-break) instead of `50*op + 10*imm + 4*rank + 0.25*reg`. The
default metric is blind to some float-register colourings and scheduling-only differences: on DrawPathDOF Lite it preferred a
variant with 46 real diff lines over the 30-line base, and `hw_before_dist` looked better (op 12 -> 6) while `asm_diff` got worse
(68 -> 78). Use the env var whenever the residue is FPR or schedule, and always confirm the winner with `asm_diff.py`.

