# Local aggregate-init templates are pooled at parse: swap with a deferred descending pair

- status: works
- tags: sdata2,pool-order,template,defer_codegen,RPBox_802c7924
- scope: Pack/RPSports/RPBoxScene/RPBox_802c7924
- source: claude/z-boxsd2-1029

symptom: under #pragma defer_codegen off, two functions' s32 a[2]={-1,-1} templates (identical 0xFFFFFFFF bytes) sit in swapped .sdata2 order vs retail; only lwz sda21 bytes differ in the DOL
cause: the template object for a local {..} initializer is created at parse; retail parsed the later-address function first (deferred, descending source)
fix: put the pair in descending source order inside '#pragma defer_codegen on' ... '#pragma defer_codegen off': off flushes the queued bodies in reverse, so .text and the .data jump table stay in place (deferring to end of TU instead puts the jump table after the named .data table defined at file end). Changing to 1-element templates does not change the order.
