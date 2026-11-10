# fn_801CBB98 box corners: non-const center ref + up-front decl order + Vector3f normal copies -> 100

- status: works
- tags: RPUtlLoadSaveDataScene,fn_801CBB98,scheduling,FPR,const-param
- source: claude/rputl-lsds-1027

symptom: FPR-heavy straight-line box-corner builder: 12 vs 17 saved FPRs, size 648 vs 728, 65.7%
cause: const ref params let the scheduler hoist later loads (lower pressure); local declaration order sets FPR colouring; per-component normal stores scheduled early
fix: center as non-const ref; declare scaledX/Y/Z then axis2z..axis0x up front; Y,X,Z load+scale order; normals[0..2] = axes[i] whole-vector copies (negated ones per component). 65.7->100, no markers
