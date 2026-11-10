# fn_8027D400 FPR numbering: reloaded .sdata limit gets f2 not f0

- status: fails
- tags: regalloc,fpr,rpbsb
- source: RPBsb_8027d3ec 2026-10-17

symptom: 99.3: orig lim f0, pos/d temps f2/f1; ours lim f2, temps f1/f0
cause: unknown; the newest value gets the lowest FPR, so lim seems created after the add temps but is loaded before the stores
fix: failed: no local (load moves after stores), inline accessor, Add inline, ref p, compare reversed, (timer+=1)>=lim, top decl, dx/dy/dz locals, per-component locals, temp-return Mul inline, const global (hoisted to f27)
