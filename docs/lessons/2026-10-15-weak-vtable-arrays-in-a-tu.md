# Weak vtable arrays in a TU

- status: works
- tags: vtable,data
- scope: RPTnsScene
- source: claude/rptns-3

symptom: other same-section objects addressed off a shared base (addi rX,rBase,off)
cause: non-weak array globals get section-relative addressing
fix: declare vtable arrays __declspec(weak)
