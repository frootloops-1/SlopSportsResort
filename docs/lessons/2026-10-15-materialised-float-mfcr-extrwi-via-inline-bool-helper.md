# Materialised float == (mfcr/extrwi.) via inline bool helper

- status: works
- tags: fcmpu,mfcr,bool
- scope: mwcc
- source: RPTns_802390b0

symptom: orig fcmpu;mfcr;extrwi.;beq, ours fcmpu;bne
cause: comparison result passes through a bool-returning inline
fix: static inline bool TnsIsZero(f32 v){return 0.0f == v;} if (!TnsIsZero(b->hp))
