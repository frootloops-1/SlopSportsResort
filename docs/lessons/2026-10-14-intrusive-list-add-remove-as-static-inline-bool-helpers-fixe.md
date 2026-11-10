# Intrusive list add/remove as static inline bool helpers fixes param regs and reload

- status: works
- tags: inline,register-order,linked-list
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: open-coded pool add/remove had pool/elem in wrong regs (r6/r5 vs r5/r6) and an extra reload of self->elem[idx]
cause: original used static inline bool helpers then re-read elem into a local before state store + vcall
fix: static inline bool Add(TnsPool*,TnsElem*)/Remove(...); caller: if (Remove(self->pool, self->elem[idx])) { TnsElem* x = self->elem[idx]; x->state=0; x->s14(); }
