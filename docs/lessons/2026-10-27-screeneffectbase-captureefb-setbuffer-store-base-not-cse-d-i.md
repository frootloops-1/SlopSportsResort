# ScreenEffectBase::captureEfb setBuffer store base not CSE'd in original: open

- status: open
- tags: egg,ScreenEffectBase,captureEfb,CSE,setBuffer
- source: claude/sfx-1027

symptom: captureEfb 98.1%, 12 bytes short: original emits addi rX,r30,0 before each of 3 inlined setBuffer stwx; ours reuses r31 (&spBufferSet from getBuffer loads); index r28 shared in both
cause: unknown; MWCC canonicalises all setBuffer address forms; something in the original kills the sum's availability
fix: dead ends: (spBufferSet+type)->, type[spBufferSet], ptr/ref local, int/const-ptr params (no change); (u32)type or const BufferType param / const getBuffer param / early-return shape (worse)
