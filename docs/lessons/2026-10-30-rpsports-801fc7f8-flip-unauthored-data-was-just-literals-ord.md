# RPSports_801fc7f8 flip: unauthored data was just literals + order

- status: works
- tags: sdata2,rodata,bss,order,flip,RPSports_801fc7f8

symptom: unit_cmp SIZE-MISMATCH on extern lbl_ string pool/bss/sdata2 floats and .sdata2 88.89, order differs at #0
cause: externs hid what were TU-local compiler pools: 0.0f/1.0f literals, string literals under -str pool, a static bss array; fn order was source-order reversed
fix: descending-address source order via reorder_fn; replace lbl_80388B48+off with string literals, lbl_804C2110/14 with 0.0f/1.0f, extern wchar_t buf with static wchar_t[32]; all sections 100, DOL 0 bytes, flipped
