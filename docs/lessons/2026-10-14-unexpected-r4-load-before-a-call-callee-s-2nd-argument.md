# Unexpected r4 load before a call = callee's 2nd argument

- status: works
- tags: args,signature,call
- scope: RPTns_8022c4c8
- source: opus worker 2026-10-14

symptom: lwzx into r4 where ours uses r3 just before a call
cause: extern prototype missing a parameter
fix: check callee asm for mr rX,r4 and add the param (fn_80222E98(TnsEnt*, TnsEnt*))
