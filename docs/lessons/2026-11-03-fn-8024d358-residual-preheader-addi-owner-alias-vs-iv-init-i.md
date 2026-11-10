# fn_8024D358 residual: preheader addi owner (alias vs IV init) is decided by definition order, frontend always hoists alias defs before IV inits

- status: fails
- tags: RPTnsScene,iv,licm,value-numbering,fn_8024D358,parked
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194

symptom: 99.9, 8 lines: target 'addi r26,r1,0x28; mr r20,r26' (IV init owns addi, base alias is the mr), ours 'addi r20; mr r26,r20'; same for related r28/r19
cause: mwcc_dbg: frontend preheader = named assignments (incl. LICM-hoisted in-loop 'cho = chosen') then IV inits; back-end value numbering turns the later identical addi into mr of the earlier. Vreg number is irrelevant (named pointer counter declared last still loses).
fix: failed: u8* aliases; s32* const aliases (init at the group = 175 lines, at loop 2 = no change); decl-group permutations of n/col2/p/first/cho/rel (all 8 lines); alias assigned at loop top + loop end (no change) or only loop end (225); opaque-zero alias defs chosen+(n-n), &chosen[k-k] (no change), (u8*)chosen+(off-k*4) (223); named pointer counter cp=chosen;cp+=2 with cho=cp (cp owns addi but an extra copy + savegpr_16, 217-261) or cho before cp (76); earlier: alias positions, inline base getter, cho=&chosen[n*2], dropping aliases.
