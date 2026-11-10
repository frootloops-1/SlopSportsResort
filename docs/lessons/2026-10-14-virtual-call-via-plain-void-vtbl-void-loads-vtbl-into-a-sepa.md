# Virtual call via plain void(**vtbl)(void*) loads vtbl into a separate reg: use dummy virtual struct

- status: works
- tags: virtual,vtable,tailcall
- source: RPBsb_80274934

symptom: lwz r5; lwz r12,0x14(r5) instead of lwz r12,0(r3); lwz r12,0x14(r12)
cause: function-pointer-array call form
fix: struct with virtual vf08..vf14 and cast self to it; tail call with unchanged incoming arg: declare callee with the 2nd param and pass it through (unused param still allocates r4)
