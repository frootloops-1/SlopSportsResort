# Reassigning an existing local starts a new live range (own register)

- status: works
- tags: regalloc,live-range,webs
- scope: RPTns_8023758c
- source: opus worker 2026-10-14

symptom: a = spInstance after earlier use of a doesn't take a's register
cause: MWCC colors each web separately
fix: don't rely on variable reuse to pin a register; open case fn_80237CB0 (r29 vs r28)
