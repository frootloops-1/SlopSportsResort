# fn_8024D358 MATCHED: in-loop opaque alias (rlwinm identity with +1/-1) reverses preheader ownership

- status: works
- tags: fn_8024D358,RPTnsScene,preheader,iv,rlwinm,alias,match
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194
- source: codex-tns-c194-trace-1103h

symptom: fn_8024D358 stuck at 99.94774%: aliases cho/rel owned the preheader addi (addi r20/r19; mr r26/r28) where retail has the SR pointer IVs own it (addi r26/r28; mr r20/r19).
cause: Plain aliases are created before strength reduction (frontend trace), so backend CSE copies IVs from aliases. Defining the alias in the loop through an identity intrinsic delays it until the back end hoists it after the IV initializers. Two follow-on problems: (1) the intrinsic's input addi is an in-loop value, so call arguments chosen/related were CSE'd to copies (mr r5,r19); fixed by feeding the intrinsic an offset address, (arr + 1) rotated then - 1, which folds only later; (2) a store through the alias as (u8*)cho+off and join loads via (u8*)chosen+off gave add+lwz or an extra live base; use cho[k] for the first cho store and (u8*)cho+off for the db->mIndex join loads. Named walking-pointer variants fix ownership but not colouring: named locals always get lower vreg numbers than SR temps and colour order in the core is descending vreg number.
fix: cho = (s32*)(u32)__rlwinm((u32)(chosen + 1), 0, 0, 31) - 1; (same for rel/related) at the top of the loop body after off; call args plain chosen/related; first cho store cho[k] = second->m2C; db->mIndex = *(s32*)((u8*)cho + off) x2. Result: 25/25, all sections 100%, flip_gate FLIP-OK, DOL 0 bytes. R17 marker, ledger row 140.
