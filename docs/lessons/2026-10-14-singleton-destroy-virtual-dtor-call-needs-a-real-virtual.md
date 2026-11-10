# Singleton destroy: virtual dtor call needs a real virtual

- status: works
- tags: vtable,dtor,singleton
- scope: RPGolScene
- source: claude/rpgol-small

symptom: manual vtbl[2] call-through 99.4% (r12 via different register)
cause: MWCC codegen differs for fn-pointer casts vs virtual calls
fix: struct V { virtual void* d(int); }; p->d(1); (fn_802AACA4/802AAF00)
