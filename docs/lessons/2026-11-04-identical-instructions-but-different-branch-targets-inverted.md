# Identical instructions but different branch targets = inverted condition

- status: works
- tags: branch,condition,harness,objdump
- scope: global
- source: claude/b340-1104e

symptom: asm_diff shows only label/branch-target differences
cause: Logic inverted (e.g. isDefaultMode vs f198c != 0 || isSelIdle) yields same instruction list
fix: Compare raw branch targets with objdump; fn_harness normalises targets so it cannot see this
