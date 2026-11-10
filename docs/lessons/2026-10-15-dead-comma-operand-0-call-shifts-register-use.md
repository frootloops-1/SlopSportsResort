# Dead comma operand (0, call()) shifts register use

- status: works
- tags: REGALLOC,NV-REGS,dead-expression,permuter,RPSysKokeshi
- scope: src/Pack/RPKernel/RPSysKokeshi.cpp
- source: nm-perm-1

symptom: RPSysKokeshi::LoadResource 99.38% NV-REGS -1gpr
cause: MWCC keeps a trivial (0, expr) comma operand through early passes, which changes register colouring of the following locals
fix: void* p = (0, RPSysResourceManager::GetFileFromArchive(...)); 99.4 -> 99.8 (permuter 155 -> 60). Try it on other 1-gpr NV-REGS misses
