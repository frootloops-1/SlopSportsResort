# Index CSE killed across ternary join (fn_801E2970 num store)

- status: fails
- tags: mulli,ternary

symptom: orig reuses index reg r7 after total<10?total:10 branch; ours recomputes li r0,0; mulli
cause: unknown
fix: tried no-local ternary (93.8), PsMin inline (no change), if-form (91.7), 1-trip loop (82.4); still open at 95.5
