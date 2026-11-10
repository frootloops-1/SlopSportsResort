# Model routing

Goal: spend expensive models only where cheaper ones demonstrably fail. `tools/route_functions.py`
measures each unmatched function from its original assembly (instruction count, loops, branches,
float/paired-single ops, virtual calls, whether types are known) and its objdiff score, assigns a tier,
and escalates from the attempt log `build/evidence/routing-log.jsonl`. Codex routing was removed
2026-10-26 (`docs/archive/codex/`); Codex work now happens through decomp.wtf, outside this repo's routing.

Opus is the ceiling (no Fable on this plan). "Park" = record the remaining diff in the component note and
revisit after the surrounding types/headers improve; it stops burning usage and is not failure.

## Tiers

| Tier | What it looks like | Start with | Escalation |
| --- | --- | --- | --- |
| A trivial | <=16 instructions, no loops, <=1 branch/call | **Haiku** (`decomp-trivial`), batches of 20-50 | -> Sonnet after 2 no-gain tries |
| B normal | most functions | **Sonnet** (`decomp-standard`) | -> Opus after 2 no-gain tries |
| C near-miss | already >=97% | **Sonnet** with the playbook's structural checklist (permuter only for a diagnosed pure register residue, ~10 min, run by hand) | -> Opus after 2 no-gain tries -> park |
| D hard | large, loops, paired-single/float-heavy, unknown types | **Opus** (`decomp-hard`) | park after 2 no-gain tries |

After two no-gain outcomes on a function in one batch, write the handoff and stop that function for the
batch even if the log recommends escalating; resume with a distinct hypothesis or new evidence.

**Shape hints override tier C.** `tools/near_miss.py` tags near-misses whose diff points at a source-level fix
(`join-moved`, `one-case-switch`, `double-cond`, `extra-cmp`/`fewer-cmp`, `ret-mask`, `early-return`, `loop-ctr`,
`returns-self`; legend in its docstring). With `build/evidence/near_miss.json` present, `route_functions.py`
sends any hinted function >=80% to Sonnet first, with the hints in its "why" column. On 2026-10-16 this closed
18 functions in two Sonnet batches while the permuter and Opus closed none of the register-only near-misses.
Give the worker the recipes `docs/lessons/2026-10-16-label-only-diffs-*` and `-branch-shape-*`.

## Non-function work

| Work | Model |
| --- | --- |
| Orchestrating (pick object, dispatch, verify, merge, handoff) | Sonnet main session |
| Flipping Matching flags, trimming docs, report parsing, porting library code that already compiles | Haiku or Sonnet |
| Recovering a class layout or shared header used by many functions | Opus (one good header makes dozens of functions tier B) |
| TU-split heuristics for the sport blobs, reviewing split proposals | Opus |
| Naming classes/methods from RTTI, vtables, strings | Sonnet; Opus for ambiguous cases |
| Per-unit `symbols.txt` data fixes (12 DATA-REF functions per batch, edits only inside the unit's split ranges) | Sonnet |

## Commands

```sh
ninja progress                                        # report must be fresh first
python3 tools/route_functions.py summary              # tiers + objects closest to done
python3 tools/route_functions.py unit Pack/RPUtility/RPUtlMapData
python3 tools/route_functions.py next --limit 20      # nearest-complete objects first
python3 tools/route_functions.py next --tier A --limit 50
python3 tools/route_functions.py record fn_801BF6C4 opus nogain --note "r29/r30 swap persists"
python3 tools/near_miss.py -j 6 --min-pct 80 --json build/evidence/near_miss.json   # enables shape routing
python3 tools/near_miss.py --shape --skip-tried --min-pct 80 --exclude BTE --limit 30
```

`--skip-tried` reads the routing log, which lives in each checkout's ignored `build/evidence/`; copy new
records back to the primary checkout's log after a worktree session. The cut-offs are starting hypotheses:
change one at a time after reading the log (if Haiku matches most tier A, raise the tier-A instruction cut-off;
if Sonnet rarely gains on tier B before escalating, lower the tier-D threshold in `classify()`).
