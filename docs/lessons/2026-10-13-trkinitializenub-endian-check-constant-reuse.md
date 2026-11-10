# TRKInitializeNub endian check constant reuse

- status: open
- tags: trk,metrotrk,nubinit,inline,coalesce
- scope: MetroTRK

symptom: orig stores gTRKBigEndian=FALSE from r31 (ret=0) and ret=TRUE via mr r31,r6; ours li r0,0 / li r31,1 (97.9)
cause: plain code never CSEs the constants (int/BOOL/DSError ret all same). Inlined BOOL helper with result var DOES reuse the constants but result lands in r4 and is copied mr r31,r4 (96.8)
fix: untried: other helper shapes; tried static/non-static, before/after, DSError result, decl-init, dead store, assignment-in-if: all 96.8
