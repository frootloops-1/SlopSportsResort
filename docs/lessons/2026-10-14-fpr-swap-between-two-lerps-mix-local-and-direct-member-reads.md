# FPR swap between two lerps: mix local and direct member reads

- status: works
- tags: float,regalloc,lerp,vreg-order
- scope: RPTns_8024a5cc
- source: opus worker 2026-10-14

symptom: fmadds result vs loaded member f3/f2 swapped; all decl/load orders fail
cause: a direct member read creates its load vreg later than a local
fix: c8 = self->f8c local, but read self->f90 directly twice in n9; script local-vs-direct x order combos (fn_8024A5CC)
