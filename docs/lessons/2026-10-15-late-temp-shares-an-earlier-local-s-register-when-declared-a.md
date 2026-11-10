# Late temp shares an earlier local's register when declared at function top

- status: works
- tags: regalloc,locals
- scope: Pack/RPSports/RPTnsScene/RPTns_802338a4

symptom: fn_802356E4: lbl_804BF708 temp got r29 (root's reg); target reuses r30 (b's)
cause: callee-saved coloring follows declaration order
fix: declare o18, b, h at top (in that order) then root const; assign h late -> 100%
