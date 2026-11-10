# ef_animcurve forecast-derived wins 2026-10-26

- status: works
- tags: ef_animcurve,hash,helpers,regalloc,forecast
- scope: src/nw4r/ef/ef_animcurve.cpp
- source: claude/animcurve-full-1026

symptom: ef_animcurve fns 87-95% from hand-nested hash and ad-hoc helpers
cause: orig shapes match doldecomp/forecast revision: flat left-to-right random hash, combined GetRandomRange(Stride) helper with typed &tbl->datas[idx], flag passed as fresh k[2] read, f32 a; f32 b; declared once before t
fix: Texture 97.5->99.4 flat hash; Rotate 98.5/U8 98.1/F32 95.5 via stride helper; u8* frame helper with own AnimCurveHeader* local; (len-1) not named n; pKey++,i++; decl split from assignment
