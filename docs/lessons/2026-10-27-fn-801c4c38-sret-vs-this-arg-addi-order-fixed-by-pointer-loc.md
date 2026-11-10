# fn_801C4C38 sret vs this-arg addi order fixed by pointer local declared before scale

- status: works
- tags: scheduling,sret,arg-order,pointer-local,RPUtl_801C4B7C
- source: Pack/RPUtility/RPUtl_801C4B7C

symptom: call args swapped: target addi r4,r28,0xb0 (matrix ptr) scheduled before addi r3,sp (sret); ours r3 first
cause: the r4 pointer must exist in IR before the sret address; a pointer local assigned earlier (before scale/updateBasis) gives that order and copy-propagates back into addi r28 (no extra reg) when used only by that call
fix: const Mtx* transpose = &self->transpose; declared after torqueForce, before scale(); use it only in the first fn_801C3250 call. Failed: inline returning the ptr, explicit out-param, member call, transpose ptr/helper inside updateBasis, operator*=, nested temps (stack moves), ptr local used by both calls or declared before torqueForce (gets r31, 98.8)
