# fn_802597F4 const 8 in r4 vs r0: vtable+0x24 addi hoisted above 2nd handle-count store

- status: open
- tags: schedule,regalloc,ctor-inline
- source: RPBsb_80258768

symptom: 98.6: li r4,8 / addi r0,r3,0x24 before lfs; orig li r0,8 and addi r0 after stw 0x44
cause: unknown; IR order of vtable address vs 8-store
fix: failed: vtable store order/local/inline, floats first/last/struct/literal, nested ctor inlines, HandlesCt(this+0x3c), if(true) block
