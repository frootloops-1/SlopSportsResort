# Unexplained higher volatile reg (r5 with r3/r4 free): look for an unused trailing vararg

- status: works
- tags: regalloc,vararg,sprintf,coalesce,RPBow_80320EFC
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: a pointer local gets r5 in retail although no neighbour holds r4 and the block has the same instruction count; lowest-free colouring holds for every other node
cause: a value passed as an extra variadic argument (sprintf with more args than specifiers) is copied into precoloured r5; RA coalesces the copy, so the local lives in r5 from its definition and no mr remains
fix: fn_80320EFC: sprintf(sbuf, fmt, last.x, last.y, ctx) -> exact. Method: verify lowest-free on the dump (all volatile nodes), confirm no post-RA deletions (backend-03 vs 07 counts), then search for a precoloured coalesce partner: the next call's unused arg slots.
