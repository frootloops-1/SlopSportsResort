# fn_802DD1F0 literal: lwz pE4 loses cycle 1 to the ready stw r20,0x80 (scheduler tie on CountScheduled, height)

- status: open
- tags: fn_802DD1F0,RPBox_802cf93c,scheduler,lbl_804C4E10
- scope: RPBox_802cf93c
- source: claude/box802cf-r4-1029 opus

symptom: with f32 zero = 0.0f the pre-sched IR is identical to the extern version except the lfs object; the scheduler issues stw r42,0x80 at cycle 1 before lwz 0xe4 (scheduler disambiguates same-base stores/loads)
cause: select_ready_coloring_node: neither node critical, equal released-successor counts, stw height >= lwz height so first-in-order wins; the extern's DDATA read makes the stw wait on lfs latency
fix: idea untested: make the first -1 store depend on a copy issued at cycle 0 (e.g. a chain value that keeps a mr), or give lwz pE4 a released successor; reconstructed Scheduler.c lacks the offset disambiguation the real one has
