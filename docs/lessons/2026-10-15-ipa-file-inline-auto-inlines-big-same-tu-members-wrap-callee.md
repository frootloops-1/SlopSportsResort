# ipa file + inline auto inlines big same-TU members: wrap callee in #pragma auto_inline off; alloca/idx/decl-order idioms (ef stripe tube)

- status: works
- tags: nw4r,ef,inline,alloca,stack
- scope: nw4r/ef

symptom: callers grow to 2.8KB because callees get auto-inlined
cause: -ipa file -inline auto
fix: #pragma push / auto_inline off / pop around callee; int idx=0,step=1; if(..) rather than if/else; __alloca(n) builtin; first-declared struct local gets highest frame offset
