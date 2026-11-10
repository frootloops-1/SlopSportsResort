# fn_801A2EFC: code-free dummy locals/casts do not reach the allocator

- status: fails
- tags: fn-801a2efc,RPSysSystemWinMgr,steering
- source: claude 2026-10-26

symptom: need one invisible GPR node in pAnm inner blocks; tried dummy locals, (void), self-assign, u8 j=i, T**/T*& locals, (T*)(u32) and (s32)(u32) casts, scoped u32 n
cause: all optimised away before register allocation: 486 lines, natural signature; only code-emitting constructs (extra start(), unkB3++, reload) change the signature
fix: unsolved. Closest: kept reset();start() split 4 lines; Q3 store order (mFlags,mIsEnabled,mFrame) gives exact regs, 16 lines
