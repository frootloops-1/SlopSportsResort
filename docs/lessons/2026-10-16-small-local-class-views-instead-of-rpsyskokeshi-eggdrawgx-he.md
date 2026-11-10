# small local class views instead of RPSysKokeshi/eggDrawGX headers

- status: works
- tags: headers,inlines,kokeshi,rpbsb
- source: RPBsb_8027c2f0 2026-10-16

symptom: extra inlines and sdata symbols in the .o
cause: big headers drag in inline bodies
fix: local class views with same offsets; MWCC vptr after members; pass EGG::DrawGX::BLACK by value
