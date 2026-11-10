# MWCC stack slots with per-section private inlines (Calc/ctor)

- status: works
- tags: RPGrpModelMaterial,stack-slots,inline,sdata2
- scope: RPGrpModelMaterial.cpp
- source: claude 2026-10-12

symptom: Big Calc/ctor stack layout and loop register order differed
cause: Locals in private inline helpers form per-call blocks (descend in call order, ascending inside, larger first); caller locals go above all. Local const u8* p=tbl[idx] reloads after calls; direct tbl[idx][0] CSEs. Static local in inline member -> weak @LOCAL@ sdata2; use file-scope statics (sdata2 in declaration order)
fix: Split Calc into per-section inlines; loop in caller with per-element inline taking *mpArr[i]; ChanCtrl trailing bytes as u8[2]; 16B PixInfo default static in init list
