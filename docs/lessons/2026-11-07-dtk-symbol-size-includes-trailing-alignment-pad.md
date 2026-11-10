# dtk symbol size includes trailing alignment pad

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8024e9a4

symptom: dtk symbol size includes trailing alignment pad
cause: dtk symbol size includes trailing alignment pad
fix: shrink size in symbols.txt to the real object size (dtk then makes gap symbols); fixed 66.7% data syms
