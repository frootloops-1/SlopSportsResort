# Scheduling flip lbz/lbzx: named u8 local; &mpEntryList[i] local fixes reg alloc; deleting dtor without base call means inline {} base dtor

- status: works
- tags: scheduling,local,u8,entry-list,dtor,inline,LightManager,RPGrpModelScene
- scope: RPGrpModelScene
- source: sonnet worker 2026-10-12

symptom: swapped load order in two-priority fn; entry-list loop reg alloc; deleting dtors without base-dtor call
cause: inline expressions vs named locals; element address taken once; EGG::LightManager dtor/GetVersion pure
fix: u8 prio = arr[g]; before call; EntryList* pList=&mpEntryList[i]; make ~LightManager inline {} and GetVersion non-pure in eggLightManager.h (MWCC error 10194 rejects new of class with pure virtual); extern C decl with mangled asm name calls undeclared EGG members
