# eggController flip classified: weak TBuffer template order + sdata relocs

- status: open
- tags: link-flip,weak-order,template,sdata,eggController,C5
- scope: egg/core/eggController
- source: claude/nm-link-2 2026-10-15

symptom: egg/core/eggController (42/42 fns objdiff 100, .sdata 67%): flip + DOL link gives 1957 differing bytes, 27 symbols moved.
cause: First byte diffs inside CoreController::beginFrame, CoreControllerMgr::T__Disposer dtor and getNthController (before any address shift: likely .sdata reloc targets, objdiff .sdata 67%). Then weak errRangeOver__Q23EGG29TBuffer<eCoreDevType> is emitted +408 B late (orig 0x800a6d90, right before the TBuffer<CoreController*> dtor); CoreControllerMgr::beginFrame/endFrame shift +168.
fix: Not attempted (classification only, plan item 33). Next: check the .sdata symbol order/sizes for the TU, then the TBuffer member/instantiation order (class-template rule, lesson 2026-10-12). Opus C5 candidate.

O1 (Opus, 2026-10-15, claude/nm-weak-1): 1957 -> 294 DOL bytes, not applied (patch: docs/tasks/nearmiss-patches/eggController-tbuffer-294.patch, headers only).
- Not .sdata: the early diffs in beginFrame/Disposer/getNthController/ctor are relocations into moved .text/.data symbols; .sdata/.sbss order and sizes are already right.
- eggBuffer.h: define TBuffer allocate(int,int)/allocate(int,Heap*,int)/onAllocate out of class (still templates in the header) -> emitted at TU end per type in declaration order like orig (1957 -> 375). Inline in-class bodies made them follow the CoreControllerMgr ctor. eggController is the only TBuffer user.
- eggController.h: declare class NullController after CoreControllerMgr -> __vt__NullController lands at 0x80398240 (375 -> 294). Moving the sNullGCCont definition does nothing.
- Dead end: forcing early TBuffer<eCoreDevType> instantiation (sizeof typedef) -> 322.
- Left: errRangeOver<eCoreDevType> must precede the two ~TBuffer dtors after the CoreControllerMgr ctor (+240), and the .data @STRING@checkRange pairs are swapped (orig <CoreController*> first). Orig touched TBuffer<eCoreDevType>::checkRange/errRangeOver earlier than our source; TU uses `#pragma ipa file`.
