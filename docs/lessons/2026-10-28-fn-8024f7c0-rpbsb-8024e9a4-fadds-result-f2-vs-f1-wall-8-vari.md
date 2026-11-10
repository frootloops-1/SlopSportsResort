# fn_8024F7C0 (RPBsb_8024e9a4): fadds result f2 vs f1 wall, 8 variants no gain

- status: fails
- tags: rpbsb,regalloc,fpr,fn_8024F7C0
- scope: RPBsb_8024e9a4

symptom: orig fadds f2,f0,f1 (timer+dt) with case-6 compare on f2; ours uses f1 (3 instrs differ)
cause: sum apparently interferes with both f0/f1 in orig RA; not reproduced
fix: failed: local sum used in case 6, self->timer += self->dt, dt/timer decl swap, timer+=dt local, static inline add / advance helper, (void)timer, timer+dt in case 6 compare. Several are worse (10 diff lines).
