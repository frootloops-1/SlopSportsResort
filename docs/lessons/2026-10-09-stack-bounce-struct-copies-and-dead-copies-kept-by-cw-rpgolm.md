# Stack-bounce struct copies and dead copies kept by CW (RPGolMapObjBase)

- status: works
- tags: golf,stack,struct-copy,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: lwz/stw to stack then lfs/stfs; dead copies present in orig
cause: CW keeps dead struct copies, CSEs loads; stack layout follows reverse declaration order; f32 struct copies use lfs/stfs
fix: alias 12-byte struct as u32 w[3] for the bounce; single local 3x3 struct; declare 'GolM33 m; GolV3 s8,d2c,d20,s14;'; write dead copies d2c then d20 after the live matrix copy
