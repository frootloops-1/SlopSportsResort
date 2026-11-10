# fn_8025AC2C: Vec temp slot order (BF1CC=0x44,BF32C=0x38,Add=0x2c) unreachable: outer BsbAdd result allocated first

- status: fails
- tags: fn_8025AC2C,RPBsb_8025a3e8,stack-layout,temp-slots
- scope: RPBsb_8025a3e8
- source: claude/bsb2-1028 sonnet

symptom: target addi r3,r1,0x44 for fn_801BF1CC result; ours 0x2c (slot order reversed)
cause: inline result slot allocated before arg temps (outer first); inline locals ascend in declaration order, arg temps descend
fix: failed: operator+/-/*, fn-ptr cast, by-value cast on fn_801BF32C, named locals t/u (grows diff), BsbAddTo(dst,a,b), whole-step inline BsbStep (97.6, right relative order, wrong absolute offsets). Do NOT change global fn_801BF32C decl to by-value: regresses fn_8025BD6C/BF00/C0AC/C2C8 in the unit
