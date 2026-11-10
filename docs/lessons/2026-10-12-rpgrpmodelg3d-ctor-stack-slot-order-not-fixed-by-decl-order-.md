# RPGrpModelG3D ctor stack-slot order not fixed by decl order/blocks/ternary

- status: fails
- tags: ctor,stack,slot,temp,RPGrpModelG3D
- scope: RPGrpModelImplement
- source: sonnet worker 2026-10-12

symptom: ctor 99.93%: target size 0x8, simple-path temp 0xc, ScnMdl temp 0x10, ResFile 0x14; ours size 0x10, simple 0xc, ScnMdl 0x8
cause: unknown temp creation order
fix: Tried: size decl before mdl/pScnObj, block wrapping, inverted if/else (95.9%), ternary (91.4%): all worse or no gain
