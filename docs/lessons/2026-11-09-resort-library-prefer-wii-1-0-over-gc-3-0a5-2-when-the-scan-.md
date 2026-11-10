# resort library: prefer Wii/1.0 over GC/3.0a5.2 when the scan ties

- status: works
- tags: resort,library,port

symptom: every later function shifts
cause: GC/3.0a5.2 packs functions at 4
fix: build the unit with Wii/1.0 (NANDCheck, g3d_restex)
