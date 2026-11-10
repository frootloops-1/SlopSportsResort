# Stack slots assigned in declaration order, descending; retail ca/cb act as declared after inline temps

- status: open
- tags: stack-slot,colour,b340
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104a

symptom: D0EC/D40C: retail ca/cb at 0x8/0xc, ours just under col
cause: Slots follow declaration order; retail locals behave as if created after every inline temp
fix: open: try ca/cb as inline-helper locals or temporaries created at use
