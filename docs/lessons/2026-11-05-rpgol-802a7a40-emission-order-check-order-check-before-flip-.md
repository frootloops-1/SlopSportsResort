# RPGol_802a7a40 emission order: check order_check before flip; reorder_fn fixed two misplaced fns

- status: works
- tags: emission-order,flip,RPGol
- source: RPGol_802a7a40 2026-11-05 opus

symptom: flip_gate 5657 bytes, unknown shifted symbols although 28/28 exact
cause: fn_802A8170 and fn_802AA2A4 defined at the wrong source position (unit emits in reverse source order)
fix: tools/reorder_fn.py FILE fn_802A8170 before fn_802A8110 fn_802AA2A4 before fn_802AA044; order_check clean
