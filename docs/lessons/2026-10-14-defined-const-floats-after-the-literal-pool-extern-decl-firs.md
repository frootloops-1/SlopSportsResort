# Defined const floats after the literal pool: extern decl first, define at file end

- status: works
- tags: sdata2,const,literal-order
- scope: RPGolScene
- source: claude/rpgol-family

symptom: named const floats land before @ literal pool entries
cause: initialized consts are laid out in source order; pool literals are appended at file end; visible values get folded into literals
fix: extern "C" const float X; before users, define at end of file; file-scope const int needs extern or C++ drops it; collapse dtk 1-byte lbz symbols into 4-byte colour symbols (fn_802AA614, sdata2 100%)
