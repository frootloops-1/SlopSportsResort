# fn_802CE89C: white GXColor single-slot and case-0 r5/r6 swap are structural walls

- status: fails
- tags: fn_802CE89C,fn_8024E9F4,GXColor,stack-slot,colouring,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: unit sweep 2026-11-01

symptom: 26 lines: case-1/case-5 white GXColor at 0xc/0x8 vs shared 0x8; case-0 M reload r5/r6 swap
cause: target has ONE GXColor object assigned at two sites (C compound-literal assignment in a -lang=c harness gives exactly this; C++ MWCC always leaves a temp or separate slot); the 0xc hole is 8-byte alignment padding before the 0x48 BoxData copy (compress_data_area drops unreferenced locals). Case 0: M load r75 is a back-end temp below chain loads r76/r77 which colour first (descending vreg)
fix: none. Dead: compound-literal assignment forms (const literal, cast/pointer target, inline operator=, c99/gcc_extensions pragmas, typedef struct in extern C), sibling scopes, by-value helpers/params, static const local + function var (98.2), placement new (adds addic./beq), named g/j or void* chain locals (98.8). RPBsb_8024e9a4 fn_8024E9F4 has the same 10-line wall. Park until a new idea (e.g. a C-compiled TU for this function)
