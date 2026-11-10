# RPGrpModelRfl weak sdata is linked exact; IPA removes table but breaks order

- status: fails
- tags: RPGrpModelRfl,sdata,DrawGX,ipa,emission-order
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: Codex isolated 2026-11-02; build/evidence/rfl-20261102

symptom: 38/39 exact, DrawGX 99.652176%; raw sdata 12 B vs target 8 B; synthetic [.sdata-0] scores 20%, despite aggregate section score 100.
cause: unit_cmp ignores synthetic section symbols: its aggregate .sdata score reflects sBaseScale, not the raw section comparison. The first 8 B are a weak GetAnmPlayPolicy policyTable discarded at link; scale links at retail 0x804BDC10. Baseline Matching gate differs only by 12 DrawGX bytes. IPA removes the table but changes text emission order.
fix: No gain: record/array table entries and volatile table load with saved index/store, across six compiler versions and with/without IPA, all keep 38/39. Reject -ipa file: 3621 linked differing bytes and 34 shifted symbols. Set IPA before SportsPack prefix to probe; extra_cflags appends too late. Restored baseline NonMatching DOL 0. No source/config change or new marker.
