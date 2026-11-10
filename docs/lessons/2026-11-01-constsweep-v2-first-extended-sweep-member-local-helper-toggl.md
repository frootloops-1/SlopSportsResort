# constsweep v2 first extended sweep: member/local/helper toggles rarely help

- status: open
- tags: constness,constsweep,sweep
- scope: tools/constsweep.py
- source: constsweep 2026-11-01

symptom: 242 fns >=85%, 4555 trials over param/member/local/helper/method/ret
cause: most const toggles are neutral or fail to compile; gains: fn_802F9F50 24->2 (param), fn_80206670 28->2 (params), fn_802CE89C 176->58 (member pB8), marginal 1-2 line gains on fn_802E43EC, fn_8020C530, fn_801F0B24, fn_801C3574
fix: run tools/constsweep.py --deep 3, then --rank; hand winners to a worker with the patch_<fn>.diff
