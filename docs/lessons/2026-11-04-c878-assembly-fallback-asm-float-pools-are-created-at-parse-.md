# C878 assembly fallback: asm float pools are created at parse time

- status: works
- tags: C878,inline-asm,pool,R17,byte-proof
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-c878-match; scratch/c878/check_relocated_function.py and relocated-proof.json

symptom: C++ stalled at 91.6; whole-body scheduled asm reached instruction 100 but moved its four literals to the start of sdata2
cause: InlineAsmPPC floatoperand creates pool objects during parsing, before deferred C++ codegen; objdiff masks the changed destinations. Compiler-managed C++ loop controls also reserve CR4 when the asm body uses CR0.
fix: Marked whole-body asm fallback plus unused inline seedLineConstants creates the original 11-literal pool prefix and emits no function. Include loop controls in asm, keep compiler frame/prologue/epilogue and symbolic POD stack fields. Independent original-DOL proof: 764 bytes, 191 instructions, 12 relocations exact. Not recovered C++; unit remains NonMatching. Volatile masks, full-loop inlines, dead array stores and partial asm blocks did not improve C++.
