# fn_801EFB68 closed: s32 flags local with both bit tests on the local (not u32 + field re-read)

- status: works
- tags: regalloc,volatile,flags,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: lwz r5,0x84(r3)/li r4,0 (retail) vs r4/r5 swapped: flags and the hidden bool swap volatile registers
cause: u32 flags plus a second self->f84 read for the &4 test; type/merge of the load temp changes which value is coloured first
fix: bool hidden = false; s32 flags = self->f84; if (!(flags & 2) && (flags & 4)) hidden = true; (a ternary init also matched). 99.9 -> 100, genuine
