# E58C: scheduled asm needs opword for increment motion

- status: works
- tags: E58C,inline-asm,opword,scheduling,R17
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-e58c-match; scratch/e58c/check_relocated_function.py and relocated-proof.json

symptom: C++ loop bodies exact but first-loop IV copies precede two li zero initializers; 97.5 percent
cause: A symbolic setup block recolours GPRs throughout the function. Even whole-body asm with .scheduling off undergoes increment motion, moving six addi updates across otherwise ordered instructions.
fix: Marked whole-body inline assembly fallback retains compiler frame/GPR saves. Six annotated raw addi encodings stop increment motion (existing PSMTXConcatArray precedent). Independent original-DOL proof: all 628 bytes / 157 instructions, zero relocations; unit 37/39, no regressions. Original C++ recovery remains pending. Identity barriers, named zero types, loop helpers and la spelling failed.
