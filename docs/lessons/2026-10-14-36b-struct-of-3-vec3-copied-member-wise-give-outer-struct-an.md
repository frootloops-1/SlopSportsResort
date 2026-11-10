# 36B struct of 3 Vec3 copied member-wise: give outer struct an empty user ctor

- status: works
- tags: struct-copy,mwcc
- scope: RPGol_802b7448
- source: fn_802B7458

symptom: orig lwz/stw groups 2,1,2,1,2,1; ours one flat 9-word copy
cause: POD aggregate copied as a block
fix: struct GolBasis { GolV3 a,b,c; GolBasis() {} }; keep GolV3 itself ctor-less (an empty ctor on it switches to lfs/stfs and reorders saved regs)
