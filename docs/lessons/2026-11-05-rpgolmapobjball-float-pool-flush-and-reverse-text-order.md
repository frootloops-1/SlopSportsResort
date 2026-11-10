# RPGolMapObjBall: float pool flush and reverse text order

- status: works
- tags: pool,defer_codegen,order,RPGolMapObjBall
- scope: Pack/RPSports/RPGolScene/RPGolMapObjBall
- source: codex-golball-1105

symptom: Objdiff data 100% hid reversed function order and conversion bias after the last two float constants.
cause: Deferred code emission is reverse source order; first definition after defer_codegen off is emitted before the queued code and implicit conversion bias.
fix: Use reorder_fn to put definitions in descending source address order, leave prototypes for earlier helpers, retain dont_inline only for fn_8029859C and array constructors AEAC/AF24/AFA0/AFF8. Put defer_codegen off plus a plain extern declaration after 40F4, before 4100/4104 definitions; implicit 4330000080000000 lands at +0xC8. order_check passes. Nine code residues still prevent a source-linked DOL match.
