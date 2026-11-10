# MWCC -inline deferred emits functions in reverse source order: list defs in descending address order

- status: works
- tags: order,inline,deferred,link,main.dol
- scope: RPGolMain

symptom: all objdiff scores 100% but main.dol checksum FAILED (1969 bytes differ)
cause: functions emitted in reverse source order; objdiff pairs by name so ignores layout
fix: write definitions in descending address order (vtable arrays/extern C block above); always finish with dtk shasum -c config/RSPE01_01/build.sha1 and cmp main.dol
