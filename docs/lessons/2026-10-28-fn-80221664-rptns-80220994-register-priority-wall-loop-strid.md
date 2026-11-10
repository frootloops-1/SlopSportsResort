# fn_80221664 (RPTns_80220994): register-priority wall, loop strides get the highest callee-saved regs in ours, the lowest in the original; 6 tries + 8-min permuter no match

- status: fails
- tags: RPTns_80220994,fn_80221664,register,priority,F6,wall
- scope: Pack/RPSports/RPTnsScene/RPTns_80220994
- source: orchestrator-1028

symptom: 87.85%: prologue 0x80221674 orig mr r30,r3 (self), ours mr r26,r3. Orig i=r31, self=r30, pl=r29, stride4=r28, stride12=r27, stride24=r26; ours strides=r31/r30/r29, i=r28, pl=r27, self=r26. Also new sub-object kept in r4 with 'add r3,self,stride; stw r4,0x138(r3)' in orig vs r5/add r4 in ours
cause: class 3: out-of-line call multiset and branches identical; the original gives i/self/pl the high callee-saved registers and the three stride variables the lowest; ours is the reverse; not source-visible from use counts
fix: failed: TnsStoreValue replaced by TnsStore(base,disp,v) / raw (void**) store / TnsStoreAt helper (identical 87.8), i/pl declared outside loop or do{}while(--i>=0) (identical), self->q[i][k] member-array indexing (o in r4 as orig but MWCC hoists self+12i/24i/4i as pointer induction vars, 85.0), dropping #pragma opt_common_subs off (86.0, pragma needed). Permuter (--keep-bodies --name fn_80221664 --static, PERMUTER_DIR set) 8 min -j 4: base 1730, best 1530, no match, output reformatted C so the change was not read or re-scored.
