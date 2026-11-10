# LoadCompressed: const-pointer cast on first inlined FindFile call only (97.0 -> 98.9)

- status: open
- tags: inline,hoist,List_GetNext,RPSysResourceManager
- scope: RPSysResourceManager
- source: sonnet

symptom: inlined FindFile loop hoists addi rX,this,0x10 into callee-saved reg; orig recomputes addi r3,r26,0x10 in loop
cause: unknown; CSE of &mResourceLists[list] across loop
fix: partial: static_cast<const RPSysResourceManager*>(this)->FindFile(..) on first call only. dead ends: this->, (*this)., const local self, (EList)1, hand loop (97.4, extra li r31), editing FindFile body (regresses others)
