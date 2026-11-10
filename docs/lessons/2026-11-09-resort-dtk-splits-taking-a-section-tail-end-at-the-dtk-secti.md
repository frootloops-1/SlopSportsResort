# resort: dtk splits taking a section tail end at the dtk section end, not the DOL size

- status: works
- tags: resort,splits,dtk
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: dtk: Section .X does not contain range
cause: dtk section ends at the last symbol end
fix: final Swordplay unit ends: .rodata 0x8068C924, .data 0x806F0108, .sdata 0x806F3DE4, .sdata2 0x807053E8, .sbss 0x806F6074
