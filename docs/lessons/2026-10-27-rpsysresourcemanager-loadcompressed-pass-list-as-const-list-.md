# RPSysResourceManager LoadCompressed: pass list as const List& to inlined FindFile

- status: works
- tags: licm,hoist,inline,RPSysResourceManager,flip
- scope: Pack/RPSystem/RPSysResourceManager
- source: claude/resmgr-1027 2026-10-27

symptom: Inlined list search hoisted this+off into a callee-saved reg (orig recomputes addi rX,this,off per iteration): 98.9, +4 bytes, flip blocked.
cause: FindFile(path, EList) indexing a member array lets MWCC keep the computed list address in a register across the loop.
fix: FindFile(pPath, const nw4r::ut::List& rList) with callers passing mResourceLists[i]; no cast needed: 100%, DOL 0. Dead ends: local const List* inside inline (96.1), non-const FindFile (97.0), break+single return (93.1), nested inline helper (97.0).
