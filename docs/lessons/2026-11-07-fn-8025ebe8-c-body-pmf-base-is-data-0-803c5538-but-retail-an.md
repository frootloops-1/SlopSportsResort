# fn_8025EBE8: C body PMF base is ...data.0 (803C5538) but retail anchors at 803C5548 -> BsbAccelTracker vtable/ctor/dtor belong to RPBsb_80259bbc

- status: works
- tags: fn_8025EBE8,RPBsb_8025a3e8,splits,data-anchor,pmf
- scope: RPBsb_8025a3e8
- source: claude/bsb5a3-c-1107 opus

symptom: C EBE8 reads PMF literals as addi rX,r31,0x2c.. vs retail lis/addi lbl_803C5548 + 0x1c.. (16 bytes off); data 100 once hand bsbPtmf00-15 dropped and bsbZeroGap moved after the fn
cause: retail .data TU start is 0x803C5548: lbl_803C5538 (vtable of BsbAccelTracker), fn_8025A3E8 (its dtor), fn_8025A428 (ctor, uses lbl_804BDF10 from 80259bbc) belong to RPBsb_80259bbc
fix: needs splits.txt change (orchestrator): move 0x8025A3E8..(after fn_8025A428) .text and 0x803C5538-0x803C5548 .data into RPBsb_80259bbc; then C EBE8 still has an lfs 0.0/lis scheduling residue after the unrolled states reset loop. __declspec(weak) on lbl_803C5538 kills the anchor entirely (76.8)
- resolved 2026-11-07: splits fixed (see rpbsb-80259bbc-8025a3e8-boundary lesson); EBE8 C then 96.5, scheduling wall
