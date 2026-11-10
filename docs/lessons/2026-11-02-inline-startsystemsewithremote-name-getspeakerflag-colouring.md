# inline startSystemSeWithRemote(name, getSpeakerFlag) colouring: natural order is flag>str>id>mgr; target str/id>flag>mgr unreachable by spelling

- status: fails
- tags: regalloc,inline,RPSports,PlayerSelect
- scope: RPSysLytPlayerSelect_801DC37C
- source: sc801dc3-1102

symptom: fn_801DC4F0/fn_801DD798/fn_801DC784: callee-saved flag/id swapped (ours flag r29/30 id r28, target id above flag, mgr always lowest r27)
cause: mwcc_dbg: flag is outer inline param vreg (coloured before id); inlined mgr is a temp (coloured before any named local); matched RPBow_80335DB0 shows the same natural colouring, so target source differs structurally
fix: FAILED (no gain): named u32 flag local (flag r27 mgr r28 worse 99.5), named mgr, flag computed inside helper (91%, string addr hoisted), no pId/mgr locals (V1/V4 flat, V2 87%), pair helper PlayDecideSe (flat), regsearch --generic 8 min (rank 3 floor), direct RPSndAudioMgr::instance()->startSystemSeWithRemote(lit, getSpeakerFlag(-1)) (flat). DOL diff 119 bytes, all register-only in these 3 fns

superseded: closed by member inline getSpeakerFlag() + nested-inline helpers, see 2026-11-02-playerselect-se-colouring-closed-member-getspeakerflag-neste.md
