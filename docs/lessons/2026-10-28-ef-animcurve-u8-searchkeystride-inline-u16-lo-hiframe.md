# ef_animcurve U8: SearchKeyStride inline + u16 lo/hiFrame

- status: works
- tags: ef_animcurve,regalloc,inline-helper
- scope: nw4r/ef/ef_animcurve
- source: claude/ac-*-1028

symptom: U8 r16/r17 hi/idx vs loFrame swap
cause: binary key search hand-expanded
fix: static inline bool SearchKeyStride(u8*,u32 keySize,s32 frame,f32 time,s32&,u16&,u16&) with u16 lo/hiFrame locals: 98.1->98.2. Same helper hurts F32 95.3 and Rotate 98.4; SearchKey<RotKey> 98.2
