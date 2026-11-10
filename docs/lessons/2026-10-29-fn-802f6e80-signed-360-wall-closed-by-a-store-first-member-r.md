# fn_802F6E80 signed %360 wall closed by a store-first member rewrite (dead early store + member re-reads shift the pre-RA schedule)

- status: works
- tags: RPBox_802f6be0,scheduler,regalloc,dead-store,mwcc_dbg
- scope: RPBox_802f6be0

symptom: target add r4/srawi r4/srwi r0 vs ours add r0/srawi r0/srwi r4 (99.77%); 75 statement-order permutations and h00 accessor variants made no difference
cause: With the old pre-RA order (lhz/ori/sth h00 all before the add) the add/srawi results overlap no r0 value, so lowest-free colouring gives them r0. The target's pre-RA order puts sth h00 after the srawi (mwcc_dbg backend-02), so the h00 temps (numbered higher, coloured first, r0) overlap Q/A/S and push them to r4; the post-RA scheduler (backend-06->07) then moves sth h00 back above the add. The early dead store h02=ni plus re-reading h02 changes the backend-01 code (extra sth/mr) and so the pre-RA schedule; the dead store is gone before final code.
fix: Write h02 = ni; frac = f04 - h02; h02 = h02 % 360; h00.set(4); f04 = h02 + frac; (no u16 local). Exact. General lever: if a register wall needs an overlap that the final order doesn't show, compare backend-02 with final; an extra store or reload to the same member that is removed later can move the pre-RA schedule.
