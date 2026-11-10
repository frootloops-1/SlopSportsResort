# Named u8[N] .sbss pad for an odd-address gap gets aligned and breaks the link

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025a3e8

symptom: Named u8[N] .sbss pad for an odd-address gap gets aligned and breaks the link
cause: Named u8[N] .sbss pad for an odd-address gap gets aligned and breaks the link
fix: only works when the gap is naturally placed (8024e9a4 case); else accept .sbss <100 if DOL 0
