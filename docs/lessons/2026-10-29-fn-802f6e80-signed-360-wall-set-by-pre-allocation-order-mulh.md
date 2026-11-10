# fn_802F6E80 signed %360 wall: set by pre-allocation order (mulhw,lhz,lfd,lfd,ori,sth,add); TBitFlag<u16> replaces h00 volatile cast

- status: fails
- tags: RPBox_802f6be0,regalloc,TBitFlag,volatile,mwcc_dbg
- scope: RPBox_802f6be0

symptom: target add r4/srawi r4/srwi r0 vs ours add r0/srawi r0/srwi r4, 99.77%
cause: add and srawi overlap no r0 value in ours, so lowest-free colouring gives both r0; srawi is numbered above srwi so it colours first. Target needs add/srawi to overlap the h00 lhz/ori/sth before allocation; no source shape produced that. mulhw/add/srawi never share a register in tests.
fix: Parked after 20+ more variants (statement order, inline Div360/Wrap360/Mod360, s16/int locals, volatile pointer, all compilers 3.0a3-3.0a5.2). Marker reduction kept: h00 as EGG::TBitFlag<u16> (set(4) reloads naturally) replaces the h00 volatile cast; 3 casts remain (w1c x2, w24), 99.0 without them. Check TBitFlag before volatile for flag reloads. Commit cd3692add, cherry-picked to main.
