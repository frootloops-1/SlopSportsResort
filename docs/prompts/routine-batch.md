Run one routed decompilation batch on Wii Sports Resort (rules: AGENTS.md; phases: docs/decompilation-roadmap.md;
procedure: docs/matching-playbook.md; models: docs/model-routing.md).

1. `git status`, `git worktree list`, `git log main -15 --oneline`. `ninja` must end with `main.dol: OK`.
   `ninja progress`; `python3 tools/route_functions.py summary --limit 15`.
2. Pick targets from the lowest unfinished roadmap phase, by flippability: units with one function left and data at
   100% (`tools/unit_cmp.py`) first. Or use the object I name here: ______.
3. One worktree per worker: `tools/setup_worktree.sh /private/tmp/wsr-<task> claude/<task>`. Baseline there:
   `python3 tools/verify.py <unit> --save`.
4. Dispatch by tier (`route_functions.py unit <unit>`): A -> decomp-trivial, B -> decomp-standard, C/D and walls ->
   decomp-hard. Brief each worker with the unit's source path, function names and scores, the compiler/flags row from
   AGENTS.md, the placeholder-naming and symbol-rename rules, matching `lessons.py search` hits, and failed hypotheses
   from the component note. Time-box ~30 minutes per function.
5. After each worker: re-run `verify.py <unit>` yourself, check its symbols.txt renames, revert regressions,
   `route_functions.py record <fn> <model> <result>`, `lessons.py add` for new wins/dead ends (title mentions resort).
6. If a unit is now 100% code: `unit_cmp.py`, `flip_gate.py <unit>` (DOL OK, `dol_diff.py` 0, `sym_addr_check.py` 0),
   then flip it to Matching, one unit at a time.
7. Commit on the worker branch ("not a full match" if partial), update the component note's "Current state", merge
   into `main` serially after the gate. Report matches by model, flips, markers separately, and what is parked.
