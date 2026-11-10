# fn_801F0B24 closed: do { } while (--i >= 0) instead of for (; i >= 0; i--) fixes the zero-constant/self/IV colour order

- status: works
- tags: regalloc,loop-form,do-while,sweep,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: 88.8: retail IV r31/i r30/self r29/one r28/zero r27, ours zero r31; color_sim said only renumbering the merged li 0 (after init's lis 0x4330) works
cause: the for-loop form changes IR/vreg numbering of the loop constants; a 720-variant store/init/flag order sweep reached only 18 lines (copy p+0x234 first)
fix: s32 i = 3; do { body } while (--i >= 0); (retail subic. decrement-and-test) -> 100, genuine. Try the loop form before sweeping statement orders
