# DrawFreeStrategy::Draw PSMTXConcat arg-address order (addi r5 before r4) not fixable by call shape

- status: fails
- tags: ef_drawfreestrategy,PSMTXConcat,schedule
- scope: nw4r/ef/drawstrategy/ef_drawfreestrategy
- source: gx-df-1026

symptom: 99.97: target addi r5,0x90 then addi r4,0xc0 before PSMTXConcat; ours r4 then r5 (2 lines)
cause: arg-address materialisation order by scheduler
fix: tried direct PSMTXConcat(*view, glbMtx, posMtx) and GXLoadPosMtxImm(*MTX34Mult(...)): both identical to baseline; parked
