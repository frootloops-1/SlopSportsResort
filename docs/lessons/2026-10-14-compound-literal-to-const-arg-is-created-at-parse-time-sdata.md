# Compound literal to const& arg is created at parse time (sdata2 order); by value at codegen

- status: works
- tags: sdata2,pool-order,compound-literal,param
- scope: RPTns_802479cc
- source: opus worker 2026-10-14

symptom: colour constant lands before the 0x4330 double in .sdata2
cause: const& compound literal is a parse-time object
fix: declare the callee param by value (fn_801F5634(..., TnsColor)) (RPTns_802479cc)
