# MetroTRK __exception: hand-written .init vector table matches as a .s source, 0 DOL diff

- status: works
- tags: asm,metrotrk,init,dol-flip
- scope: MetroTRK/debugger/Processor/__exception
- source: scratchpad/gen_exception.py

symptom: __exception unit was an empty .c with one 7988-byte pad_ function (0%); looked like undecompilable data
cause: Retail code is hand-written asm: 375 insns in ~24 vectors at 0x100 strides, rest zero fill; dtk disassembly is the ground truth
fix: Generate src/.../__exception.s from build asm (mnemonics kept, zero runs -> .skip, banner -> .string, plain labels + .type/.size; .fn macros are not available to the project's gas). Object bytes, relocs and symbols equal the target; trial Matching flip gave dol_diff 0. Left NonMatching pending owner review.
