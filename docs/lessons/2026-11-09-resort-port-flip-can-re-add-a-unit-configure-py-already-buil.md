# resort: port_flip can re-add a unit configure.py already builds

- status: works
- tags: resort,library,port,flip

symptom: Duplicate object name (hcicmds)
cause: unit is in configure.py directly and in ported_objects.json
fix: remove the ported_objects.json entry and revert its split edit
