# captureEfb: fresh addi per setBuffer store needs the GETTER's address node unshared (const EffectBuffer* local in getBuffer)

- status: works
- tags: eggScreenEffectBase,CSE,getter,mwcc_dbg
- scope: egg/gfxe/eggScreenEffectBase

symptom: setBuffer stores reuse getBuffer's &spBufferSet[type] node (stwx r31); original emits fresh addi rX,r30,0 per store
cause: front-end CSE entry shared between getBuffer's load and setBuffer's store (mwcc_dbg backend-00-initial-code: r39 = r56 + r37 reused by stw)
fix: getBuffer reads through a local: const EffectBuffer* p = &spBufferSet[type]; return p->mpTexBuffer; (98.1 -> 100). Eleven setBuffer-side spellings failed; change the getter's expression shape, not the setter.
