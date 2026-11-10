# ef_animcurve F32 key-setup tail (k0 r10 vs r12, k1 r12 vs r9) is a pre-RA scheduler placement wall

- status: open
- tags: ef_animcurve,F32,scheduler
- scope: nw4r/ef/ef_animcurve

symptom: At 99.05 only the tail key setup (12 lines) and lo=0 li placement remain
cause: Pre-RA scheduler hoists interp=k0+4 and k1's add between flag0 neg/or, so k0 stops interfering with the or temp and k1 interferes with the neg temp; source order, interp spellings (v0-8, &k0[4], struct ->interp), no-flag locals, U8 pKey/value-pointer shape and 150 random statement orders all canonicalize or regress. Splitting lo decl (bool found; s32 lo; lo = 0; found = ...) fixes li r28 and the whole front (22 lines) but objdiff scores it lower (98.964 < 99.049), so not kept.
fix: Not found. Need a dependency change that delays interp/k1 in the pre-RA schedule. Also: verify/m.sh can report a stale object when a scripted replace hits the wrong function; always ninja the object first and check its exit code.
