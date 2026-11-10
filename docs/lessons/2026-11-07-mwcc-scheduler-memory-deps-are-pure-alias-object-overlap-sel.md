# MWCC scheduler memory deps are pure alias-object overlap; self/prm accesses share one virtual object

- status: works
- tags: scheduler,alias,mwcc,A0E0
- scope: MWCC GC/3.0a5.2
- source: fn_8031A0E0 round 8

symptom: Need to know when a load may move above a store (fn_8031A0E0 v1BC/v1C8 block)
cause: Scheduler edge = may_alias(pcode->alias): ObjectPart (obj,off,size) overlap. A pointer param gets a virtual object V (base offset 0x7FFFFF); prm=&self->prm propagates as V+0x258, so prm->x vs self->y never alias. Alias is fixed at the FIRST gather (start of backend CSE, initial pcode) and persists; an add/lfsx with an index whose li is in another block gives whole-V (size 0xFFFFFF) even after constprop folds it to lfs off(rX). Decomp of the logic: /private/tmp/rfl-mweppc/src/compiler/optimizer/Alias.c (2.7, matches 3.0 behaviour seen).
fix: Dump pcode alias structs: copy mwcc-sched-sim/fast_trace.py and read 48 bytes at pcode+28 (obj@16 off@20 size@24 type@44; type 0=whole,1=part,2=set). Script: /private/tmp/scratch-A0E0-r8/ft.py + al.py.
