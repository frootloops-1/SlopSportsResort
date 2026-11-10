# RPBsb_80285870 data complete; fn_80288E90 block-split phase (dead base-vtable store at record 4 vs retail record 12)

- status: open
- tags: block-split,pcode,vtable,sdata,const-hoist,sbss,RPBsb_80285870
- scope: RPBsb_80285870 fn_80288E90

symptom: fn_80288E90 84.3% (2496 vs 2492 B): retail keeps the dead lbl_803C1A4C base-vtable store at record 12 (0x1AC), ours at record 4 (0xAC); ours saves r18-r31 with frame 0x1e0, retail r20-r31 with 0x1d0; ...data.0 anchor reloc where retail references @10508
cause: Same block-split mechanism as fn_80268A30: mwcc_dbg shows a 3-pcode header and 24 pcodes per record; a 100-pcode simulator (.scratch/sim*.py in the worker tree, not committed) predicts and a build confirmed that a header ~9 pcodes longer moves the surviving dead store from record 4 to record 12.
fix: Not closed. obj in the base ctor + 3 dead stores to vptr 0x28 reproduces 0x1AC and frame 0x1d0 but swaps the obj/derived store order (81.7) and relies on invented dummy stores (not kept). Dead: abstract middle zero-vtable store (80.1), obj in base + middle store (79.8), ctor with default params (57.9), 802656a4-style st[17] loop (partially unrolled by 8 with ctr, 24.9). Data recipe that worked: vtables at file end; sbss guard size 0x8->0x1 in symbols.txt (rest is alignment pad); writable .sdata floats that retail loads as const: __declspec(section .sdata) extern const defined AFTER all code (R17 ledger row 95); extern const then non-const definition is a compile error; switching extern const pool floats to literals can swap lfs operand order (v.x = v.x * -1.0f loads the literal first; v.x *= -1.0f restores it, fn_802858F0); pool_renames.py --unit X --apply for @N .sdata2 names.
