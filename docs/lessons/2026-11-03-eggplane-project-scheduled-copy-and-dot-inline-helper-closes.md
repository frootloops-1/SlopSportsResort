# eggPlane project: scheduled copy and dot inline helper closes code and DOL (R17)

- status: works
- tags: egg,Plane3f,project,inline-asm,scheduling,NRVO,FPR,R17
- scope: egg/geom/eggPlane
- source: 2026-11-03; build/evidence/eggplane-20261103/; adapted from RPGrpModelRfl DrawGX scheduling lesson

symptom: project 73.17073%, multScalar exact; retail interleaves early dot loads with integer return-buffer copy and compiler prologue. Raw extab/extabindex 66.66667% from extra weak destructor records.
cause: Normal C++ copy/dot forms did not reproduce both interference and scheduling. Direct inline asm disables NRVO; hardcoded FPRs reserve f0-f4 for the entire function, changing the C++ tail. An invented inline helper preserves NRVO and symbolic locals let the compiler reuse its registers afterward.
fix: Retain MATCH-PENDING R17 copyAndDistance helper: 17 symbolic-register asm instructions for out=input and normal.dot(input)-depth. Leave first lfs/lwz schedulable, then .scheduling off. Declare float scratches in reverse order (4,3,2,1,0) and copy words x,y,z; no hardcoded registers. All six GC builds give 2/2 exact and text 100. Flip gate passes: DOL 0 bytes, three known collisions, extra weak destructor and its exception records discarded. This is an assembly workaround, not recovered original C++.
