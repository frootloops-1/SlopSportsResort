# fn_80236358 r21/r22: colour replay says only slwi-temp+h merged or numbered above the li const fit

- status: fails
- tags: fn_80236358,RPTns_80235cd0,regalloc,color_sim
- scope: RPTns_80235cd0

symptom: li 1 (codegen r95) r22 vs shared slwi temp (IR CSE r47) r21; target swapped (99.8)
cause: Replay of the d5 graph: no single extra edge, no 2 extra r47 edges, no renumbering of any 1-2 other nodes reproduces the target; only slwi temp or h numbered > r95, or slwi temp and h as one named vreg (<=38) do
fix: no source found: int h reused as byte offset h = idx<<2 (IRO forward-substitutes; codegen slwi r89 still < li r96), u32 idx (14 lines), h after idx (16)
