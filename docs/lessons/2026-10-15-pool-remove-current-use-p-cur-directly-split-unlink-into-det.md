# Pool remove-current: use p->cur directly, split unlink into detach(it)+free(p,p->cur)

- status: works
- tags: mwcc,regalloc,inline,linked-list
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: remove-cur inline: it/next/node volatile regs rotated; nxt compare loaded before cur
cause: orig reads p->cur for check/slot/detach and re-reads it once for the free tail
fix: if(!p->cur) return 0; node=*p->cur->slot; Detach(p->cur); Free(p, p->cur) where Free(p,it){if(it==p->nxt)...; it->next=free; free=it;}
