# sda-address CSE (li sym@sda21 + lbz 1(rX)) vs direct lbz sym+i@sda21

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802e2a84

symptom: sda-address CSE (li sym@sda21 + lbz 1(rX)) vs direct lbz sym+i@sda21
cause: sda-address CSE (li sym@sda21 + lbz 1(rX)) vs direct lbz sym+i@sda21
fix: symbolic asm lbz c, sym+i; colours follow decl order of ALL asm-defined register vars; a C constant zero coalesces into r0
