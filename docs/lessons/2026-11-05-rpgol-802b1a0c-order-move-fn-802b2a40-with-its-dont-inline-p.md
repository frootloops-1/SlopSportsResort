# RPGol_802b1a0c order: move fn_802B2A40 with its dont_inline pragmas

- status: works
- tags: rpgol,802b1a0c,emission-order,reorder_fn
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: order_check: ours fn_802B2AB4 before fn_802B2A40
cause: reorder_fn.py left the surrounding #pragma dont_inline on/reset behind, so 2A40 got inlined
fix: move the whole pragma block + fn after fn_802B2AB4
