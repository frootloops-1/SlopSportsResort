# Small ctor helper inlined into owner ctor: dont_inline

- status: works
- tags: inline,ctor,pragma
- scope: RPTns
- source: RPTns_80222a70

symptom: original calls helper, ours inlined it
cause: auto-inlining of small fn defined before caller
fix: #pragma dont_inline on/reset around the helper (fn_80224C80)
