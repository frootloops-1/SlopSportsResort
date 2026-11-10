# fn_802D235C (RPBox_802cf93c) vcall: virtual v40 call loads vptr from arg copy r3, retail loads from r4 before mr

- status: fails
- tags: regalloc,vcall,rpbox,fn_802D235C
- scope: fn_802D235C
- source: claude/box1-1028

symptom: lwz r12,0x144(r4) before mr r3,r4 in retail; explicit fn-ptr table call gives lwz r5 then lwz r12,0x40(r5) (99.8, 4 diff); other->v40(2) gives right regs but lwz after mr/li (96.6, scheduling regress)
cause: real virtual call lowering loads vptr through the copied this arg; retail kept it on original vreg (as in fn_802D0404 inlined BoxAtkReady where user is live after)
fix: failed: other->v40(2), local BoxObj* o, BOOL r, static inline wrapper; baseline explicit fn-ptr form kept (99.8)
