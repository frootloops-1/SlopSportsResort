# resort: RPGrpCamera is a Resort revision (sync/orbit changes, extra virtual, no SaveCameraMatrix)

- status: works
- tags: resort,RP,RPGrpCamera
- source: rp-camera worker 2026-11-09

symptom: 0/8, 60%
cause: Resort changed SyncFromMatrix/CalcMatrix/CopyFromAnother and the API; file includes ctor/dtor/__sinit beyond the name-matched split
fix: see RPGrpCamera.cpp/.h; absorbed the sinit placeholder with its .ctors line; name the sinit __sinit_\\RPGrpCamera_cpp (FORCEACTIVE needs a global name)
