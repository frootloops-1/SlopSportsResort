# fn_802DCA18: lone 'b end' jump-table block kept by a dead float load in the case (survives IR jump chaining)

- status: works
- tags: fn_802DCA18,RPBox_802cf93c,switch,jumptable,marker
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: target case 1 jump-table entry points at a lone 'b end' block; ours threads straight to the join (99.7)
cause: IRO_DoJumpChaining (optimizer/IroJump.c chain_label) retargets case labels whose block is only a goto; int dead copies are removed by IR UseDef first, but a dead f32 copy/load survives IR and is only dropped in the backend, leaving the block
fix: switch in the caller with case 1: { f32 u = self->f118; break; } -> 100 (R17 marker). (f32 u = (f32)state keeps the conversion code: 98.9)
