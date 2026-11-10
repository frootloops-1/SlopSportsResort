# RPSports 801E7EB4/801ea458 sdata2 move: cm2hw leak, reversed emission, two pooled 0.0f

- status: works
- tags: split,sdata2,pool-order,dedup,cm2hw
- scope: RPSports_801E7EB4,RPSports_801ea458

symptom: Bare splits edit moving sdata2 floats raised neighbour but dropped 801ea458 sdata2 and regressed fn_801EB1A0
cause: src had extern lbl_ floats (no pool entries), source order ascending while MWCC emits text+pool in reverse source order, a header-leaked cm2hw table sat in 801E7EB4 sdata2, and retail has two pooled 0.0f which MWCC dedups
fix: literals in using code, inline SpSetFovy/SinCosDeg shape (/2.0f then *256/360) gives 10,0.5,0.7111 order, reverse source to descending with reorder_fn.py (hoist structs/externs), #define NW4R_G3D_PLATFORM_GPU_H in 801E7EB4, keep second 0.0f via global const defined at file end (R17 marker)
