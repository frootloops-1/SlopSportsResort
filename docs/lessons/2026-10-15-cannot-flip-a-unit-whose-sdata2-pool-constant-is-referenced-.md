# Cannot flip a unit whose sdata2 pool constant is referenced by a NonMatching neighbour (global @NNN_addr symbol)

- status: open
- tags: flip,sdata2,link
- scope: RPSportsCommon

symptom: KokeshiLytDebug code 100%: flip -> Linker Error undefined '@171_804C1CE8' referenced from RPSportsButtonA.o
cause: MWLD merges identical sdata2 doubles across TUs; dtk exports the survivor as global @171_804C1CE8 and the target ButtonA.o references it; our object's copy is local
fix: flip both units together (ButtonA must match) or give the constant a global name via splits ownership; try other units first
