# Duplicated inline block into one member fixes name/id reg swap

- status: works
- tags: regalloc,inline

symptom: name/id land in swapped regs across sound calls
cause: block written inline twice
fix: move block into one inline member updateInfo()
