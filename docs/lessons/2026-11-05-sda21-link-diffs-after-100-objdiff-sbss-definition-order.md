# sda21 link diffs after 100% objdiff: .sbss definition order

- status: works
- tags: rpgol,802b1a0c,sbss,layout
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: DOL 17 bytes off in sda21 refs though all fns 100%
cause: compiler emits .sbss in declaration order; source declared 938,930,934
fix: reorder definitions to address order (930/934/938)
