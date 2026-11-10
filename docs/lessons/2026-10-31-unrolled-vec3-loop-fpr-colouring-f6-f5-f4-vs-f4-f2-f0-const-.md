# Unrolled VEC3 += loop FPR colouring f6/f5/f4 vs f4/f2/f0: const pointee lets 3.0a5.2 alias analysis hoist next copy's lfs; use the non-const pointer type the caller declares

- status: works
- tags: rpbow,8031c3f8,alias,const,unroll,fpr,iro-cse,r17
- source: worker vreg-31c3 2026-10-31

symptom: 98.57%, 135 lines: paired-single work regs f6/f5/f4 vs target f4/f2/f0 in the 4x unrolled sum loop; plus case-4 loop re-reads index/samples in the target while ours caches them
cause: (1) a const pointee on pts makes Alias.c treat its lfs as safe, so the pre-RA scheduler floats each copy's three lfs above the previous copy's psq_l/ps_add/psq_st chain and the work regs interfere; (2) IRO_CommonSubs does not match const-qualified loads with plain loads of the same field
fix: (1) fn_8031C3F8(BowSwing*, Vector3f* pts, ...) non-const, as the caller RPBow_80320EFC declares it (plain source, no marker); check pointer constness before treating an unrolled-loop colouring diff as a wall. (2) case-4 body via GetC with const GetIndex()/GetSamples() getters and capacity via the non-const pointer (R17, ledger row 44); plain Get(i) + (1) leaves 47 lines. Dead: this-based body accessor, bool ok temp (98.2), address of a temporary, sum escaping to a global. Fast loop: extract the loop to a small TU with the unit flags (~2 s compile and dump); MWCC_DEBUG=1 on mwcc_debugger.py prints raw PCode headers (u32 at +0x0c: 0x02 read, 0x04 write, 0x20 ptr-op, 0x40 seen on loads).
