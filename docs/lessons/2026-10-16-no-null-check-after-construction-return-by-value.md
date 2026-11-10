# no null check after construction: return by value

- status: works
- tags: ctor,new,rpbsb
- source: RPBsb_8027039c 2026-10-16

symptom: placement new always adds cmpwi/beq
cause: operator new null check
fix: extern "C" Cls fn_X() { return Cls(); } constructs into r3, no null check
