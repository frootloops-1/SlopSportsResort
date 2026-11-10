# u16 field in {3,4,16}: bitmask test only for direct field reads

- status: works
- tags: bitmask,switch,u16,compare
- scope: RPGol_802c441c
- source: claude/rpgolscene-unsplit

symptom: orig addis/subi/clrlwi/slw/andi. bitmask; ours plain compares
cause: MWCC forms the bitmask only from a direct || chain on the field
fix: return st->f120==3 || st->f120==4 || st->f120==16; (no cached local, no switch, no r=false/if form)
