# Callee-saved reg of a post-loop local follows its declaration slot among loop locals

- status: works
- tags: regalloc,callee-saved,declaration-order
- source: RPBsb_80258768 fn_802597F4

symptom: post-loop pointer (new'd object / this+0x10) got r24 (lowest) vs orig r26 = loop counter reg; nothing else live
cause: vreg index = declaration position; colouring order by index; separate def-webs of one var still keep that slot
fix: C-style top-of-function decls; put 'u8* base; u8* base2;' right after 's32 i;' and before the loop pointer locals (fn_802597F4 97.6->98.6)
