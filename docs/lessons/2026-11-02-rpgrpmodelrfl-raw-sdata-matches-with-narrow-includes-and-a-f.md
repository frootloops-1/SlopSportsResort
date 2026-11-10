# RPGrpModelRfl raw sdata matches with narrow includes and a four-byte split

- status: works
- tags: RPGrpModelRfl,sdata,headers,weak,padding,splits
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: Codex isolated 2026-11-02; sdata-matching-link.log

symptom: Synthetic [.sdata-0] scored 20%, though unit_cmp reported aggregate .sdata 100%.
cause: Broad g3d/egg/Pack headers emitted an unused weak animation policyTable (8 B, two relocations) before sBaseScale. Target split also included 4 B of zero alignment padding after the true 4 B scale.
fix: Use specific scene/resource/ModelEx and RP model headers with TU-local umbrella include guards; no shared header or compiler flag change. Trim .sdata split end from 0x804BDC18 to 0x804BDC14 and regenerate DTK: target and ours are now exactly 3f800000, raw sdata 100%. All six compiler builds keep 38/39 functions; code/order/sdata2 unchanged. Temporary Matching DOL still only 12 DrawGX bytes, three known collisions. Restored NonMatching DOL 0. No markers.
