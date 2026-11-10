# Object with only weak-dup .data/.text/.bss surplus can flip to Matching when DOL CHECK passes

- status: works
- tags: nw4r,ef,matching,data,weak
- scope: nw4r/ef

symptom: ef_particlemanager 17/17 fns exact but .data 96%, ours has extra weak vtable/code/bss
cause: Surplus weak symbols are deduped by the linker; objdiff section score is not authoritative
fix: Flip to Matching, run full ninja, confirm CHECK build.sha1 OK
