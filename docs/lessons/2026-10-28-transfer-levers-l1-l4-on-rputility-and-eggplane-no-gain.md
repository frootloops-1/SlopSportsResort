# Transfer levers L1/L4 on RPUtility and eggPlane: no gain

- status: fails
- tags: L1,L4,fn_801BF6C4,fn_801C6B64,eggPlane,project
- source: xfer-1028

symptom: fn_801BF6C4 99.86, fn_801C6B64 99.66, Plane3f::project 73.2-78
cause: fn_801BF6C4: dropping the count local reads entryCount in the loop (96.41), count at use 99.77, u32 count 99.86 same. fn_801C6B64: start/axis declared at use or reordered (99.51, one fn worse), threshold split (same). Plane3f::project: copy via ctor(x,y,z), member assignment, dot-before-copy all worse (62.4-73.3)
fix: none; these are register-numbering/scheduling walls, not declared-type decisions. Do not retry these forms
