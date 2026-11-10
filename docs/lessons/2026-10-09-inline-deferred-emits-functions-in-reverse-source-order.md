# -inline deferred emits functions in reverse source order

- status: works
- tags: layout,order,inline-deferred,forceliteral,sdata2
- scope: RP
- source: claude-opus

symptom: objdiff 100% per fn but object .text order reversed vs original; FORCELITERAL needed for pool order
cause: cflags_rp uses -inline deferred, which emits definitions last-to-first
fix: write definitions from highest address down; pool order then follows naturally and DECOMP_FORCELITERAL can be dropped. Trailing 4B .sdata2 gap and static GX/OS header helpers + duplicate weak inlines are linker artifacts seen in Matching objects too
