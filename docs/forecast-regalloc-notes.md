# MWCC register-allocation model and levers (from the Forecast Channel decomp)

Source: another Wii decomp (Forecast Channel, same MWCC GC/3.0a5.2 family) documented how the allocator numbers
and colours virtual registers. The claims below are theirs, **unverified on our build** until a lesson says
otherwise (`python3 tools/lessons.py search forecast`). Use only when the instruction stream already matches and
only register numbers differ (`wall-identifier`: register/schedule class).

## Model

- Interference is half-open: a result may reuse a source register that dies in the same instruction.
- Colouring goes in **descending vreg order**; each node takes the lowest free register. Volatiles (r3-r12, f0-f13)
  first; callee-saved nodes get r31, r30, ... / f31, f30, ... in colouring order. Highest vreg = lowest volatile
  or highest callee-saved register.
- High-degree nodes (live across calls) are ordered by spill weight/degree instead; hard to predict, measure.
- vreg numbering, lowest to highest: parameters in order; **named locals** (first declared = highest, coloured first);
  all `@N` variables (inline-expansion locals/params, optimiser temps; within one expansion the last declared local is
  coloured first; a nested expansion is newer, so coloured later; strength-reduced table pointers are newest);
  expression temporaries last (later generated = coloured earlier).
- Net vreg order: params < named locals < `@` variables < expression temps. Colouring is highest first, so temps are
  coloured first and named locals last. Ask which value the target colours first, then pick declaration
  order/types to get it.

## Levers to try (cheapest first)

1. **Declare locals up front, uninitialised, in the order that gives the needed colouring; assign later** in the original
   statement order. Initialising at the declaration often changes code.
2. **Declared type of a local assigned from a load.** If the type matches the load it merges into the load's expression
   temp (coloured first); a different type stays a separate variable. Try both (`wchar_t c = *p` vs `u32 c = *p`).
3. **Put the loop inside one inline expansion.** If the search index must be coloured before the loop pointer/index,
   all three must be locals of the same inline; nesting a getter inline makes the index newer (coloured later).
   Early-return code inside the helper: `goto found` rather than `break` plus a pre-loop `glyph = -1`.
4. **Walk a copy of a parameter** (`const T* p = str; ... p++`) instead of incrementing the parameter.
5. **Non-POD class lvalue as a by-value struct argument** (class with a user ctor, e.g. `nw4r::ut::Color`): the hidden
   stack-copy address is hoisted before a loop instead of recomputed (`addi rX,r1,imm`) at each call.
   Cast an existing lvalue: `static_cast<const nw4r::ut::Color&>(rawColor)`. Check for a new weak dtor/ctor symbol.
6. **Reference to a local copy** (`Vec2 s = *p; Vec2& r = s;`) makes MWCC assume aliasing and reload after a store.
7. **Reuse the carried variable** for a derived value (`prev = a*b; cur += prev;`) instead of a separate temp: extends
   its live range as the target has it.
8. **Float result as a named variable** (temps are coloured before variables); assign in the target's order.
9. **Named local for a hoisted constant** (`f32 m1 = -1.0f;` inside the block): changes where loop-invariant constants
   land among callee-saved FPRs; position of the local matters.

## What did not help for them (skip)

Compiler version/flags, `#pragma opt_*`/`peephole`/`scheduling`, `const`/`register` on locals, long permuter runs on
whole functions for allocation-order problems, expression-level rewrites when the cause is vreg order.

## Related facts

- Function order in source must match the original, or every later function drifts (see `tools/order_check.py`).
- Weak-function emission order after `__sinit` can need `-ipa file` for the unit.
- Always check ninja's exit status; a failed link leaves the old DOL.

## Measured on our build (2026-10-28, `tools/regalloc_diag.py`)

- **Order keys** (918 functions, 150 target objects, non-volatile GPRs live across calls): no single key predicts which
  callee-saved register a value gets. Concordance of "higher register => higher key": uses 0.44, span 0.51, first-def
  position 0.45, calls-in-span 0.44. Only two weak signals: params get the lower register 64% of the time, and values
  whose last use is earlier get the higher register 62% of the time. The "high-degree nodes ordered by spill weight"
  sentence above is therefore not predictive with these keys; do not build an order predictor, diagnose per value.
- **Retrospective test, 5 functions** (pre-fix source compiled from the fix commit's parent):
  fn_8020489C (lever 1), fn_8022750C (lever 1), fn_802DFC10 (lever 7): the tool names the one value that moves
  (a `lwz 0x70(r30)` local, an r5/r6 argument-load pair, an `addi r3,0x1c` strength-reduced pointer) and lists the lever
  that closed it. fn_801E8ED0: wrong, it suggests levers 1/2; the real fix was an inline accessor (lever 3 family),
  so loads from a pointer parameter now list "inline getter first". fn_80220034 (all levers flat): flagged as a
  MODEL VIOLATION (target colours a param copy before a call result), which agrees with the six failed levers.
- **Population** (125 REGALLOC near-misses): volatile-only swaps 47, short value in a different register 23,
  clean colouring-order inversions 15, split/merged live ranges 37 (not an order problem: look at inlining/helpers).
  The tool is a diagnosis aid, not a predictor.

## Cross-check from other decomps and our FPR experiment (2026-10-28)

External sources (all single-function observations by their authors, not proven rules):
- cadmic/mwcc-debugger README: colouring input is a priority list built in "levels" (a node joins a level when its remaining
  neighbour count is below the free-register count, ~29 GPR); levels are in reverse numerical order; each node then takes the
  lowest-numbered register its coloured neighbours leave free (r0, r3-r12 first, then already-used saved regs, then a new
  saved reg from r31 down). Levers it names: make something a compiler temp instead of a local, move variables into inline
  functions, add/remove neighbours to shift levels, create coalesced variables. Needs GC/1.1 or GC/2.6; ours is GC/3.0a5.2.
- FFCC-Decomp docs/register_allocation.md: vreg numbering as above; declaration order only helps for same-kind swaps; cross-group
  swaps (named vs inline local vs temp) need a change in how many values are live together.
- universal-modder #275: sub-address temp (`p3 = base + 3; pe = p3 - 3;`), `&x` to force a lifetime split (only helps when the copy
  overlaps the original and the value is not rematerialisable), `u8` index to defeat cast CSE, typed virtual call, inline boundary.

Measured on our build (worktrees claude/fprA-1028, claude/fprB-1028; lessons `2026-10-28-mwcc-fpr-colouring-*`):
- **fn_802D930C closed (100%)**: a `static inline` helper taking the float as a param. The model's ordering held *within* each
  group (expression temp > `@N` inline local/param > named locals in declaration order > params), but two refinements:
  1. The split between "coloured first" and "coloured later" follows *live across many calls*, not a K~32 neighbour count
     (FP neighbour counts here were ~10).
  2. A late (one-call) node does **not** take the highest free callee-saved register; it reuses the lowest-numbered
     already-used register its neighbours leave free. To land on a dead f31 the value must be coloured early: inline param,
     `@N` local or expression temp, never a named local. Declaration-order moves inside the named group did nothing.
- **fn_8024F7C0 closed (100%)** and it was not colouring at all: a wrong callee prototype (missing `f32` arg already in f1)
  removed a live range. When a volatile value avoids a register that looks free, check callees on the path for a missing
  argument (other units may already declare the right prototype).
- **fn_8033DB38 not closed**: the "FPR order" wall is the pre-RA instruction schedule (target = ours with I/J mirrored); five lever
  families and ~12 variants did not reproduce it. The colouring model does not apply; treat as a scheduler wall.
- Of 4 functions tried: 1 closed by the model's lever (with an R17 marker), 1 closed by a prototype fix the model did not predict,
  1 scheduler wall, 2 skipped because their diffs were GPR-only. The model is a good diagnostic, not a generator.

### Roll-up after the second FPR batch (2026-10-28, 19 functions, `docs/lessons/*FPR batch 2*`)

Screen: `tools/regalloc_diag.py` on all 114 REGALLOC near-misses; 23 were FPR-only (same opcodes, `f` renames only). Of the 19 tried:
7 closed (fn_802D930C, fn_8024F7C0, fn_802C7D08, fn_802C4970, fn_802BBEB4, fn_802C1FC0, fn_80322B68), 1 partial (fn_802FD5A8 94.89 -> 97.1),
11 no gain. Two of the seven carry an R17 marker (fn_802D930C, fn_802C1FC0).

Levers that closed functions, in the order to try them:
1. **Callee prototype** (missing FP/int arg already in its register): fn_8024F7C0.
2. **Name vs expression temp for one value** (age of the vreg): a named local is older (coloured later, higher volatile / lower callee-saved),
   a call-argument expression is newest. Pass the field straight into the call (fn_802C4970), or name a value before a ctor (fn_802BBEB4).
   A `const` local with a literal init is propagated as a *newest* literal temp; dropping `const` keeps it an old named vreg (fn_80322B68).
3. **Reload into a named local + divide inside the call arg** when a member is re-read after an aliasing store (fn_802C7D08).
4. **Existing inline helper instead of a hand-expanded form**: a flipped commutative operand order (MWCC canonicalises it by vreg class)
   points to a missing inline (fn_802FD5A8 BoxLerp).
5. **Inline param** for a value that must be coloured early (fn_802D930C), or an expression for one that must be newest (fn_802C1FC0).

Do not spend time on: swapping source operands (canonicalised), declare-up-front for an uninitialised value (the vreg follows the first
definition), declaration-order sweeps inside the named group, naming a single-use temp (copy-propagated back), invented float-param
helpers (often fold constants differently, -3..-10%). When the opcode stream differs or fdivs/lfd move, it is a scheduler wall: park.
Remaining misses are mostly pairs where the model predicts the wrong direction (ternary join value, nested-inline temps outranking an
outer inline param, fctiwz temp never f0).

## Verified by probe on our build (2026-10-28, from the Melee `regalloc_explain.py` / DeepWiki allocator page)

Source: stephenjayakar/melee-mwcc-register-skill (Melee, GC/1.2.5n). Its script is only a hardcoded table plus a
spill-cost calculator, not a predictor. Two of its claims were probed with GC/3.0a5.2 and the project flags:

- **Volatile GPR order starts at r0, then r3-r12.** The first-coloured plain-ALU value gets r0 (`li 8` coloured before
  `li 5`: `li r4,5; li r0,8`). Values used as a load/store base never take r0. So an "r0 vs rN" diff means a different
  value is coloured first; the target's r0 holder has the higher vreg. Matches `li r0 / li r4` lessons.
- **Spill choice follows cost = flow_weight*(2*uses+defs)/degree.** 19-21 values live across calls vs 18 callee-saved
  GPRs: fewest-use values spill first (1 use, then 2, then 4); a 1-use value inside a loop stayed in a register while a
  2-use straight-line value spilled (loop weight counts); ties go to the lowest vreg. Only matters when a unit really
  has more than 18 live-across-call values.
- Probe harness: compile a scratch .cpp with the unit's flags (`ninja -t commands <obj>`), disassemble with
  `dtk elf disasm`. Do not use for predicting colouring in real functions (see the order-keys result above).
- Applied to fn_801FC7F8 (limit r0 vs r4): the model explains the diff (target colours `limit` before the loaded flag)
  but 4 declaration-order/type variants (named flag local after limit, limit after c, limit uninit with if/else,
  `(s32)(u32)` flag) all stayed at 16 diff lines. Still parked.
