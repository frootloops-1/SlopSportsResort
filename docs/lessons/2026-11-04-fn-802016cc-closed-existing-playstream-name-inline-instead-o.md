# fn_802016CC closed: existing PlayStream(name) inline instead of named name/mgr locals

- status: works
- tags: regalloc,inline,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: r29/r30 swap between spInstance and the name pointer (99.0)
cause: named locals name/mgr numbered in declaration order; inline params are numbered late
fix: PlayStream("STRM_...") in each branch (static inline taking pName, getting spInstance inside)
