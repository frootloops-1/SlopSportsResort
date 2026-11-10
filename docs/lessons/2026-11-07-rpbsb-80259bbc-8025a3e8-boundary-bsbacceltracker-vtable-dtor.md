# RPBsb 80259bbc/8025a3e8 boundary: BsbAccelTracker vtable/dtor/ctor belong to 80259bbc

- status: works
- tags: splits,data-anchor,RPBsb_8025a3e8,RPBsb_80259bbc
- scope: Pack/RPSports/RPBsbScene

symptom: fn_8025EBE8 C body anchored PMF literals at ...data.0 (803C5538) while retail anchors at 803C5548
cause: lbl_803C5538 vtable + fn_8025A3E8/fn_8025A428 were split into the wrong unit
fix: splits: 80259bbc .text end 0x8025A4D0, .data end 0x803C5548; 8025a3e8 starts there. fn_8025A4D0 (empty VEC3 ctor) stays in 8025a3e8. Moved dtor needed operator delete(self) not delete self (Vector3f members with dtor add a 2nd null check). Both units 100, flip_gate OK
