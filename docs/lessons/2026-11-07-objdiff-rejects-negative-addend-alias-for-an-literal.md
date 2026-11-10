# objdiff rejects negative-addend alias for an @-literal

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8024e9a4

symptom: objdiff rejects negative-addend alias for an @-literal
cause: objdiff rejects negative-addend alias for an @-literal
fix: define a named object at the literal's address in the pool namespace instead
