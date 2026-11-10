# fn_802D2E84: addi base,0xe8 + lwzx array read needs pointer += index, not pl[i]

- status: works
- tags: RPBox_802cf93c,addressing,lwzx
- scope: RPBox

symptom: target addi r3,r3,0xe8; rlwinm; lwzx r3,r3,r0 vs ours add r3,r3,r0; lwz r3,0xe8(r3) for o->pl[w148==0]
cause: MWCC folds the member offset into the displacement for pl[i], (&pl[0])[i], local BoxObj**=pl then pl[i], member-fn this->p[i]; only a separate pointer increment keeps base+0xe8 materialised
fix: static inline BoxObj* BoxPlGet(BoxPl* o,int i){ BoxObj** p=o->pl; p+=i; return *p; } closed fn_802D2E84 98.9->100
