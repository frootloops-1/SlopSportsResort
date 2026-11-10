# resort: Resort Bowling dtors call no base dtor (open: authentic spelling)

- status: open
- tags: resort,bowling,dtor,MATCH-PENDING
- scope: resort
- source: bowling-lanes

symptom: virtual dtors are just if (p && del>0) delete p; return p
cause: base dtors trivial / no RP_DEBUG_STUB_1 call in Resort
fix: extern C mangled free function bytes-matches (R17 ledger #9); recover the real class hierarchy and write member dtors instead
