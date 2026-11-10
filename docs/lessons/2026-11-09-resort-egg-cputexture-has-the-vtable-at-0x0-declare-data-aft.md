# resort: EGG::CpuTexture has the vtable at 0x0 (declare data after the virtuals), only dtor+configure virtual, alloc(Heap* = NULL)

- status: works
- tags: resort,EGG,layout,vtable,CpuTexture
- source: rp-egg-layouts worker 2026-11-09

symptom: RPGrpCaptureTexture ctor 98.4%
cause: MWCC places the vptr where the first virtual is declared; Resort's CpuTexture declares virtuals first
fix: move data members after the virtual declarations; getTexObj/load non-virtual; CapTexture::load non-virtual too
