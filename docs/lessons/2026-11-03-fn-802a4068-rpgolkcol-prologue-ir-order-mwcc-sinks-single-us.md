# fn_802A4068 (RPGolKCol) prologue IR order: MWCC sinks single-use prism pointer to its call arg

- status: fails
- tags: rpgol,golkcol,scheduling,prologue,inline-helper,mfcr
- source: claude/gol-4068-1103e worker report

symptom: 88.7%: retail loads cur, prisms, idx, ext, slwi (prism) before mulli (ext), k=r9/prisms=r8/ext=r7; ours loads ext first, mulli before slwi, k=r6
cause: MWCC moves a single-use local pointer (prism=&k->prisms[*k->cur]) down to its one use (call arg) before scheduling; confirmed with #pragma scheduling off. Only a branch or a real second use restores def-site order (both add code)
fix: Not closed (Opus; branch claude/gol-4068-1103e 44d50bfe5 unmerged, 90.0). Works for the tail only: static inline int f(f32 dist,f32 r){ if (dist >= -r) return 1; return 0; } on all three edge tests removes mfcr/extrwi/cntlzw (a bool 'return dist>=-r' helper is worse, 83.3). Dead: decl order, const/register/reference, getters, pointer-copy helpers, pos local, unused nrm, one-trip for, brace init, regsearch generic (8 min, 4338 evals flat), version_sweep identical. Struct-assign edge copies 78.3 (lwz/stw instead of lfs/stfs); whole-body inline helper 88.5. Not merged: invented helper name + R17 marker for a 1.3-point partial gain
