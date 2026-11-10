# Use !(x < 0.0f) for plain fcmpo+blt (RPGolMapObjTree fn_8029661C)

- status: works
- tags: rpgolmapobjtree,fcmpo,compare
- scope: RPGolMapObjTree
- source: sonnet

symptom: x>=0.0f emits cror eq,gt,eq; bne (97.1%)
cause: compare lowering
fix: if(!(x<0.0f))
