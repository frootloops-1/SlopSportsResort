# fn_801FB91C: addi-r5 struct copy from .data base = real PTMF constant copy (local aggregate initializer)

- status: works
- tags: ptmf,struct-copy,data
- scope: RPSports_801f9150

symptom: copy of 12B from lbl+off emitted as direct lwz (85%); target is lwz first word + addi rX,base,off + lwz 4/8(rX), base hoisted in r31
cause: the original has real pointer-to-member constants (compiler emits 12B blob in .data and copies it via a stack local); pun of extern data never gives this shape
fix: SpPm pm = &Cls::fn; self->f0C=0; self->pfn = pm; (struct with PTMF member + f0C + f104) -> instructions exact (98.9, remaining reloc/offset: earlier PTMF users must also be real PTMFs so blob offsets are 0x24/0x30/0x3C). Also 'local SpW3 tmp = {0,-1,(u32)fn}' gives right shape but lands in .rodata
