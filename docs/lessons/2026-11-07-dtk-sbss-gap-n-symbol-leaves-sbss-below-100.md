# dtk .sbss gap_N symbol leaves .sbss below 100

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8024e9a4

symptom: dtk .sbss gap_N symbol leaves .sbss below 100
cause: dtk .sbss gap_N symbol leaves .sbss below 100
fix: define an unreferenced global array with the gap symbol's name/size right after the preceding var (RPBsb_8024e9a4 .sbss 80->100)
