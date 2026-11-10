# RPGol_802b1a0c order: fn_802B2A40 must stay above its inlining callers

- status: fails
- tags: rpgol,802b1a0c,emission-order
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: order_check: ours fn_802B2AB4 before target fn_802B2A40
cause: moving fn_802B2A40 after fn_802B2AB4 stops it inlining into 2AB4/2F90 (91.0/68.1)
fix: dead end: reorder_fn 2A40 after 2AB4; try defer_codegen/separate inline copy of 2A40 body instead
