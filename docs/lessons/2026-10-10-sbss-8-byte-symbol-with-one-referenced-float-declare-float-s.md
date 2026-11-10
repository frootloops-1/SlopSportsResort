# sbss 8-byte symbol with one referenced float: declare float sym[2] use sym[0]

- status: works
- tags: rpgolcameratilt,sbss
- scope: RPGolCameraTilt
- source: sonnet

symptom: size mismatch of sbss symbol
cause: only first float referenced
fix: float lbl[2]
