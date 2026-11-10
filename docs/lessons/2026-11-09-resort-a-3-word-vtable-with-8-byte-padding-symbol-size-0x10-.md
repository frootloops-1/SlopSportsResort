# resort: a 3-word vtable with 8-byte padding (symbol size 0x10) marks a file's .data end

- status: works
- tags: resort,splits,vtable
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: where does a file's .data end inside an unk container
cause: vtables within one file pack at 4; the last one of a file is padded to 8
fix: cut at the padded vtable; carved Sports2/Unk_803456D0 (state-machine base) out of unk/sinit_80344DC4
