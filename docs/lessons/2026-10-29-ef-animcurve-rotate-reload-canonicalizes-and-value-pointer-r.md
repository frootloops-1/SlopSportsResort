# ef_animcurve Rotate reload canonicalizes and value pointer reference regresses

- status: fails
- tags: ef_animcurve,Rotate,scheduling,reference
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Rejected rangeA phase has38lines but98.90265 below99.06805; preRA neg precedes k1 add.
cause: k0 flag reload is CSEd. v0 pointer is mutable in two branches, requiring branch-local mutable aliases for valid const reference.
fix: Flag reload remains98.90265/38. Valid initialV0 const-reference plus branch-local mutable v0 gives96.93289/455. Both reverted. Plain f32* const& v0 fails compile at v0++; not a valid experiment. No marker retained.
