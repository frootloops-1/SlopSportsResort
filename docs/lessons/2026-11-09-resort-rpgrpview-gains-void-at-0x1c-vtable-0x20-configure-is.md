# resort: RPGrpView gains void* at 0x1C (vtable 0x20); Configure is not virtual in the base

- status: works
- tags: resort,RP,layout,RPGrpView
- source: rp-graphics-layouts worker 2026-11-09

symptom: RPGrpViewRender2D 5/6, view ctor 0xA8 vs 0x58
cause: Resort RPGrpView layout and vtable differ (base vtable 0x806B9E50 has no Configure slot)
fix: mUnk1C at 0x1C, Configure non-virtual in RPGrpView, new last virtual in RPGrpViewRender2D; 2D 6/6, 3D ctor/AttachCamera/GetCamera 100
