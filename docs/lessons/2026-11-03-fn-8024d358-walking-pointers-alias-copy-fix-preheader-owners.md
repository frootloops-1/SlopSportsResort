# fn_8024D358 walking pointers + alias=copy fix preheader ownership, leave colouring

- status: open
- tags: fn_8024D358,RPTnsScene,preheader,iv,colouring
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194
- source: codex-tns-c194-trace-1103h

symptom: Baseline 99.94774% has reversed preheader ADDI/MR ownership (aliases r20/r19 own the ADDIs). Delayed-identity ports were 97.8-98.7% with extra registers.
cause: Making cp/rp explicit walking pointers (cp=chosen; rp=related; cho=cp; rel=rp; cp+=2; rp+=2, no related[n*2] IV) makes the aliases copies of the loop pointers, as in retail (ADDI r26/r28 then mr r20/r19). Needs cho/chosen reads spelled via cho (db->mIndex = *(s32*)((u8*)cho+off)), args still related/chosen, and the first cho store as cho[k] so the lwzx forms survive. Result: 2296/2296 bytes, every mnemonic multiset equal, only register numbers differ: 99.585% with rp,cp declared first at the function top (99.52% otherwise). Colour dump: named walkers have low vreg numbers (r61/r60) so they are coloured after the SR temps @1158..@1176; retail colours rp r28 > k r27 > cp r26 early and the self+j*4 temp r23 late. Regsearch (two 8-min runs) found nothing real (rank 8, imm 3).
fix: Not applied: baseline kept in tree (99.94774 > 99.585). Patch at docs/repros/tns_walker_alias_variant.patch. Next: get the walkers a high vreg number/early colouring (inline-param or helper boundary, or an SR-created temp that is not a named local), then re-check the n*2 IV, k and self+j*4 temp colours with tools/color_sim.py.
