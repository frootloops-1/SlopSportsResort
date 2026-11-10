# Unit's first fn refs a 0.0f+pad pool slot owned by the previous unit => unit boundary is wrong (RPGolUtlVec/UtlMtx)

- status: open
- tags: rpgolutlvec,splits,sdata2,boundary
- scope: RPGolUtlVec
- source: sonnet

symptom: fn_80295D28 refs lbl_804C3FB8 (UtlMtx sdata2 range) and sdata2 offsets of later fns are off by one
cause: fn_80295CB0 and fn_80295D28 were compiled in RPGolUtlMtx's TU; split .text boundary should be 0x80295D74
fix: move boundary UtlMtx end/UtlVec start to 0x80295D74 and move the two fns to RPGolUtlMtx.cpp (not done: UtlMtx out of scope this batch)
