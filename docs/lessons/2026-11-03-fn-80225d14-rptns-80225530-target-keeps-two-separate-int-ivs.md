# fn_80225D14 (RPTns_80225530): target keeps two separate int IVs 6 and 7 (slots i*2, i*2+1); MWCC always merges them

- status: fails
- tags: induction,strength-reduction,iv-merge,RPTns,parked
- scope: Pack/RPSports/RPTnsScene/RPTns_80225530

symptom: second loop: target li r30,6 / li r29,7 both subi 2, clrlwi to u8 at loop top, one extra callee-saved reg (savegpr_22); ours derives b = a+1 (addi) -> 1 insn short (0x1f8 vs 0x1fc), 94.3%
cause: unknown source shape; MWCC CSE/IV elimination merges any linear relation
fix: failed (all <=94.4 except unsigned hacks): u8 b=a+1 (orig), b=i*2+1 (either order, 2*i, i<<1, i+i+1, (i+1)*2-1, (s32)/L casts), inline i*2+1 in calls, b first + a after the if, int k temps, explicit int counters a=6,b=7 (int/u32/s32 mixes all merged), separate j counters (j=7 step -2, j=3 step -1, j declared at fn top), u8 IV counters (two IVs but clrlwi at update, 93.5). Only signedness split a=i*2, b=i*2U+1 kept 2 IVs (96.7, but 6+addi not 7) -- steering, not applied.
