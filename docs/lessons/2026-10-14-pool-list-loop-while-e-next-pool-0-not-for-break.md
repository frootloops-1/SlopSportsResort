# Pool-list loop: while((e=Next(pool))!=0) not for(;;) break

- status: works
- tags: while-loop,iterator,linked-list
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: orig loop has the test at the bottom (b cond; body; cond: bne body); for(;;){e=Next(); if(!e)break;} puts test at top, 23%
cause: loop shape
fix: TnsPool* p=self->pool; p->cur=0; p->nxt=p->head; TnsElem* e; while ((e = TnsPoolNext(self->pool)) != 0) e->vfn(); with static inline Next reloading self->pool
