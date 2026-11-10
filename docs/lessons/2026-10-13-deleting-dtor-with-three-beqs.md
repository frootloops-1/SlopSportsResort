# Deleting dtor with three beqs

- status: works
- tags: mwcc,dtor
- scope: RPGol_802b66c4
- source: sonnet-worker

symptom: branch targets wrong in deleting dtor
cause: flag check nested in middle if
fix: outer{ if(self){ if(self) dt(self,0); } if(flag>0) delete }
