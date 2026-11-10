# Inline-instance var numbering: locals first, then param copies in reverse param order

- status: works
- tags: regalloc,inline,recursion,mwcc_dbg,RPGolKCol
- scope: Pack/RPSports/RPGolScene/RPGolKCol

symptom: fn_802A4760 self-inlined recursion: shift/node register rotation in one leaf block
cause: mwcc_dbg: per inline expansion vars are numbered locals (decl order) then modified-param copies in reverse param order (v<shift<node); nested/later expansions get lower numbers; a low-degree var is coloured by descending vreg, high-degree ones (deg >= ~35) first by cost
fix: Turning a param copy into a body local (u8* child) moves it below the params in every instance and also changes the top-level colouring (a named local is numbered above all params), so it cannot flip a single instance. Statement order, v type, load spelling and inline helpers (inline-depth budget) do not help. Parked.
