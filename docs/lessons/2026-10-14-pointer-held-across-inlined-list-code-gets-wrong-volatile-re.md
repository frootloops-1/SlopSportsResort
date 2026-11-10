# Pointer held across inlined list code gets wrong volatile reg: wrap code in inline taking it

- status: works
- tags: regalloc,volatile,inline,pool
- scope: RPTns_80240fe0
- source: opus worker 2026-10-14

symptom: M=self->mgr gets highest volatile reg; orig lowest
cause: code shape: orig used inline helpers taking the manager as a parameter
fix: static inline Release(Mgr* m, Node* n) / Acquire(Mgr* m) / NewMgr(); u32[2] initializer is one .sdata2 object (merge split symbols) (RPTns_80240fe0)
