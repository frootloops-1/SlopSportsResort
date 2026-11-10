# resort: Wii Sports inline method out of line in Resort; weak vtable stubs placed by reverse emission

- status: works
- tags: resort,RP,inline,weak,vtable,emission-order
- source: rp-tagparms worker 2026-11-09

symptom: RPSysTagParms: extra 0x20 function at file start, stub order differs from ogws
cause: Resort's RPSysTagParameters::add is not inline; -inline deferred emits in reverse source order, so weak stubs defined at file end land first
fix: drop 'inline' on add; move RPSysTagParm::write after the TagParm ctor; keep read/dump weak at the end; identify stubs from the vtable words in the DOL
