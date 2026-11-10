# Weak function/vtable emission order and an extra base __dt/__vt differ from original: 100% fn scores but DOL differs

- status: open
- tags: layout,weak,vtable,dtor,order,DOL,RPGrpDrawPath
- scope: RPGrpDrawPathManager
- source: coordinator 2026-10-12

symptom: All 19 fns exact but linked DOL differs (2063 bytes in .text 0x801A8600.. and .data 72 bytes) when object flipped to Matching
cause: Ours emits __dt__13RPGrpDrawPath/__vt__13RPGrpDrawPath in Manager TU (orig only has On/Off/IsEnable), dtor order XluSnap,SV,HDR,DOF,Bloom,Manager vs orig Manager,SV,HDR,DOF,Bloom,XluSnap, vtable order differs; source function order 'Construct,ctor,scnProcDraw,template' gives right fn order up to dtors
fix: unknown; verify.py does not cover layout - always try the DOL link (flip in configure.py + ninja) before declaring Matching
