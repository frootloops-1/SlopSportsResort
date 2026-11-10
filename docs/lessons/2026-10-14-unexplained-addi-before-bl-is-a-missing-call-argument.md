# Unexplained addi before bl is a missing call argument

- status: works
- tags: regalloc,args,vec
- scope: RPTns_8022e3f8

symptom: 93.9%: FP regs differ plus extra 'addi r4, r31, 0x408' before a call
cause: callee fn_801BE0FC is normalize(VEC2* out, const VEC2* in); source passed one arg; also wrong constants and dx/dy temps
fix: check callee prototype; write single-use temps inline and order statements as the asm dataflow; VEC3 by value when caller copies a 12-byte temp to a second slot
