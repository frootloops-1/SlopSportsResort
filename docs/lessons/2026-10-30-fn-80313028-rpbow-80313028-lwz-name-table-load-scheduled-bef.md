# fn_80313028 (RPBow_80313028): lwz name-table load scheduled before stw conversion temp; lfs 100.0f should fill that slot

- status: fails
- tags: schedule,RPBow,fn_80313028,alias,int-to-float
- scope: Pack/RPSports/RPBowScene/RPBow_80313028

symptom: else-branch call fn_801C38B8(tbl.names[i],100.0f,y,...): ours xoris;lwz r3,0(r30);stw;li r4;lfs f1 vs target xoris;lfs f1;stw;li r4;lwz r3 (99.72%)
cause: unknown; target looks like lwz depends on the stw to the int->float temp (alias), ours treats them independent
fix: failed (identical diff): direct arg tbl.names[i], static-inline getter by const ptr, local const char* names[17] filled by struct cast, const char** names=tbl.names indexed, s32 table + cast, (f32)y / f32 fy temp, split decl+assign. Regressed: user pointer pn++ (reg swap), f32 x=100.0f local (hoisted into f30). version_sweep: only 3.0a5.2. mwcc_dbg.sh crashed (gdb MemoryError 0xfffffffc) after backend-00.
