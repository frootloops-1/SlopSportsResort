# extern C fn returning VEC2 needs explicit sret out param

- status: works
- tags: abi,vec2

symptom: VEC2 returned in r3/r4 instead of via hidden pointer
cause: nw4r VEC2 is small, returned in regs by default
fix: declare callee with explicit VEC2* out first param (fn_801DE594)
