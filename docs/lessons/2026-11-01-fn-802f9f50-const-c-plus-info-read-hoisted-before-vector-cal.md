# fn_802F9F50: const c plus info read hoisted before vector calls

- status: works
- tags: constness,fn_802F9F50,scheduling,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802f9f50
- source: constsweep 2026-11-01

symptom: 98.5% (24 lines non-const, 2 lines after const BoxContact* c): lwz 0x40(r4) sits after the psq_st instead of after psq_l
cause: const c lets the scheduler float loads; the other->info load must stay before the first local store but not float further
fix: const BoxContact* c plus BoxHitInfo* info = other->info read before BoxVecAdd/BoxVecScale; const BoxChild* other hoists too far (still 2 lines); non-const c with the moved load is 91.6
