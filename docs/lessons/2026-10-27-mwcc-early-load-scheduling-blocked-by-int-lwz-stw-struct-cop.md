# MWCC early-load scheduling blocked by int lwz->stw struct copy before call (eggPlane project)

- status: fails
- tags: egg,plane,scheduling,dot,nrvo
- scope: egg/geom/eggPlane
- source: worker a73f8cb18f79c4c6a 2026-10-27

symptom: Plane3f::project dot gets f0-f2 allocation instead of original f0-f4 (fmuls f4) pattern; stuck at 73.2%
cause: Early float-load pass stops when the pre-call block has int lwz->stw copies (NRVO struct copy); const stores or copies after the call do not block it; scheduling off gives plain allocation
fix: None found: ~35 source forms, GC 3.0a3-3.0a5.2 and Wii 1.0-1.1, 11 pragmas, VEC3Dot all <=73.2. Original compiler input differs in an unreproduced way; parked.
