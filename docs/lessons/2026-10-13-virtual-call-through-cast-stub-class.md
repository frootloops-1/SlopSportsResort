# Virtual call through cast stub class

- status: works
- tags: mwcc,virtual
- scope: RPGol_802bb044
- source: sonnet-worker

symptom: fn-pointer table call loads vtable into temp r5
cause: manual vtable indexing
fix: struct V{virtual void del(s32);}; ((V*)p)->del(1) gives lwz r12,0(r3); lwz r12,8(r12); delete (V*)p adds extra null check
