# Lift a local above the params: declare it right after an uninitialised multi-var list

- status: works
- tags: regalloc,declaration,rank
- scope: RPTns_80228ba8
- source: opus worker 2026-10-14

symptom: local should rank above params (r30) but sits low (r22)
cause: MWCC ranks a local declared right after 'int a, b, c;' just under the first local
fix: int last=-1; int cnt=0; int hitA, B, C; int dirA; (fn_80229564)
