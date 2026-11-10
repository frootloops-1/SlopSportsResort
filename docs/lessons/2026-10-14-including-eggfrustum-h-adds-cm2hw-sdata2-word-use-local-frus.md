# Including eggFrustum.h adds cm2hw .sdata2 word; use local Frustum view with #line 391 assert

- status: works
- tags: frustum,sdata2,header
- source: RPBsb_8026e440

symptom: 99.5-99.7% on float fns; pool relocs shifted
cause: eggFrustum.h pulls g3d which pools an extra word at start of .sdata2
fix: local minimal EGG::Frustum view; inline SetFovy assert under #line 391 "eggFrustum.h", include only eggAssert.h + nw4r/math.h
