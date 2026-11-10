# Inlined early-out helper: test the macro, not the local, to fix the pWork/flag regswap (NWC24MsgCommit)

- status: works
- tags: regswap,inline,nwc24,regalloc
- scope: src/revolution/NWC24/NWC24MsgCommit.c

symptom: WriteXWiiMBRegDateField/DelayField inlined into NWC24CommitMsgInternal swapped r23/r24/r28 (flag vs pWork); standalone copies matched; declaration-order permutations (24) did nothing
cause: testing the local vs re-reading the field changes the coloring order in the caller (cause not fully understood)
fix: if (NWC24i_MSGOBJ_GET_MB_REGDATE(pMsg) == 0) return; keep regDate = macro before it (same for delay): 99.97 -> 100% code
