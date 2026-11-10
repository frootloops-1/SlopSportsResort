# Trailing idx=0/cur=ents[idx] store scheduling

- status: works
- tags: scheduling,stores,index
- scope: RPTns_8022863c
- source: opus worker 2026-10-14

symptom: li r3,0 before lfs zero; six trailing stores in wrong order, all 720 orders fail
cause: cur indexed by the just-written field
fix: self->idx=0; self->cur=self->ents[self->idx]; self->next=0 (fn_80228B30)
