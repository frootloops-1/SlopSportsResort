# RPGrpModelRfl raw data and rodata match via novtable and padding split

- status: works
- tags: RPGrpModelRfl,data,rodata,novtable,padding,splits
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: Codex 2026-11-02; build/evidence/rfl-rawdata-20261102/matching-link.log

symptom: Synthetic .data-0 was 90.83558%, .rodata-0 76.92308%, despite all named data objects matching.
cause: Our data emitted an extra 32 B weak IScnObjCallback base vtable after the exact 208 B derived vtable. Original rodata split included six bytes of zero alignment padding after the exact 10 B string pool.
fix: Forward-declare nw4r::g3d::IScnObjCallback with __declspec(novtable) in this TU, as only derived callbacks are constructed here; shared header unchanged. Trim rodata split end 0x80383788 -> 0x80383782 and regenerate DTK. Raw data/rodata/sdata/sdata2 all 100%; 38/39 functions and order unchanged on all six compilers. Temporary Matching DOL still only 12 DrawGX bytes, three known collisions; restored NonMatching DOL 0. No markers.
