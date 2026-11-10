# Named locals colour last; a one-field holder lifts a long-lived bool above them

- status: works
- tags: regalloc,holder,flag,RPBow_80319C98
- source: RPBow_80319C98 round 4

symptom: fn_8031A0E0: bool flag (mfcr) gets r7, retail r4; j/rows shifted
cause: named function locals get the lowest vregs and colour after all IRO @vars; the holder makes flag an @var (r78) coloured earlier
fix: struct BowCamFlagRef { bool b; } flag; flag.b = cond; plus tEF4 rows via (T*)((Row*)res->p4 + k) helper -> flag r4 j r5 (R17 265/266). A k holder overshoots (k r5). Refs/VEC3* holder on &self->v1F8 do not reproduce retail's addi r6,r29,0x1f8
