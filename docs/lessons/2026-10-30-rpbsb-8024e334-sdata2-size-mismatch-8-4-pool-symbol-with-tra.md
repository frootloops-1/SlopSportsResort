# RPBsb_8024e334 .sdata2 size-mismatch 8!=4: pool symbol with trailing 0.0f

- status: works
- tags: sdata2,pool,size-mismatch,rpbsb
- scope: RPBsb_8024e334

symptom: lbl_804C32B0 original size 8 (.float 440 + .float 0), ours 4; unit .sdata2 85.71%
cause: symbols.txt sizes the symbol 8 (440.0f then padding 0.0f never referenced by code)
fix: define as extern const f32 lbl_804C32B0[2] = {440.0f, 0.0f} and use [0]; code stays exact, unit flipped to Matching, DOL 0 bytes
