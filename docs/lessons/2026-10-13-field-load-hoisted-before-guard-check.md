# Field load hoisted before guard check

- status: works
- tags: mwcc,scheduling
- source: RPGol_802b90b4

symptom: original loads a field before the if-test
cause: load happens unconditionally in source
fix: cache field in a local before the if: T* o=s->obj; if(s->b5&&s->n) fn(o);
