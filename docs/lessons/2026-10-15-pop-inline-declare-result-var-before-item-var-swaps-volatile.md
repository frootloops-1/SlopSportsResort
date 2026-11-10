# Pop inline: declare result var before item var swaps volatile regs

- status: works
- tags: regalloc,volatile,declaration,pool
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: AC7C it/node r7/r8 swapped
cause: earlier-declared variable gets the higher volatile register
fix: TnsAv* node; TnsItem* it = p->live.next; ... node = *it->slot; plus Acquire = Push(m, Pop(m->p1)) inline keeps the null join
