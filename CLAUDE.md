# Claude Code instructions

@AGENTS.md

Claude-specific additions (these extend AGENTS.md; where they differ, these win):

- **Role:** the main session is the orchestrator. It picks the target (roadmap phase order, then flippability), sets
  up a worktree per worker, dispatches, verifies, records, merges serially.
- **Workers:** `.claude/agents/` (`decomp-trivial` = Haiku, `decomp-standard` = Sonnet, `decomp-hard` = Opus). Opus is
  the ceiling. Routing: `docs/model-routing.md`. Every worker brief names the unit's source path, the functions with
  their current scores, the placeholder-naming rule, and the relevant `lessons.py search` hits.
- **Parallelism:** one worker per worktree; several worktrees at once is fine. Inside one checkout, one subagent at a time.
- **After every worker:** re-run `python3 tools/verify.py <unit>` yourself, check its symbol renames, then
  `python3 tools/route_functions.py record <fn> <model> <result>`; record new wins/dead ends with `lessons.py add`.
- **Permuter is not a default step.** Structural levers first (playbook); permuter only for a diagnosed pure register
  residue, ~10 min cap.
- **Skills** in `.claude/skills/`: `matcher`, `helper-recovery`, `wall-identifier`, `permute`, `orchestrator`,
  `decomp-code-rules`.
- **Session prompt:** `docs/prompts/routine-batch.md`. Keep context small: "Current state" of a task note only.
- **Two projects:** ogws (`~/Downloads/ogws-master`) is a read-only reference from here. Never edit it from a Resort
  session; port by copying.
