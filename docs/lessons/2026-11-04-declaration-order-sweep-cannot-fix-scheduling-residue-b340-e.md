# Declaration-order sweep cannot fix scheduling residue (b340 E58C)

- status: fails
- tags: declaration-order,schedule,harness
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104d

symptom: two mr IV inits scheduled ahead of li
cause: Residue is scheduling, not colouring; 720-variant decl-order sweep bottoms out at current 4 diffs
fix: open
