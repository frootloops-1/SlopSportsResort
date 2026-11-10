# Stack slot order under -inline deferred: parse locals, then inline-expansion locals

- status: works
- tags: stack-slot,inline,deferred
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104b

symptom: struct locals at wrong frame offsets
cause: Frame = parse-time locals/temps in creation order, then inline expansions (callee parse locals inserted reversed, nested expansions appended). const& param + local copy creates the copy at expansion time; by-value params are parse-time arg temps
fix: Use const& + local copy helpers to push a local to expansion time
