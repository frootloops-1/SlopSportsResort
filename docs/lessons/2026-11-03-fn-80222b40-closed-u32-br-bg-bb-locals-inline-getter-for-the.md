# fn_80222B40 closed: u32 br/bg/bb locals + inline getter for the loop entry pointer

- status: works
- tags: colour-order,u32,clrlwi,copy-propagation,inline-getter,RPTns_80222a70,fn_80222B40
- scope: Pack/RPSports/RPTnsScene/RPTns_80222a70

symptom: 6 colour bytes from const u8[4] sdata2 tables: single-use u8 locals (br/bg/bb) came out as early-coloured load temps (r0,r3,r4), e/offset shifted to r5/r6
cause: backend: u8 local = clrlwi(lbz) and the in-loop (f32)u8 conversion adds another redundant clrlwi; the optimizer forwards the copy chain so the named local vanishes and the high-numbered lbz temp colours first. Named e (vreg below the @ i*4 offset) colours after the offset
fix: declare the single-use ones u32 (no in-loop clrlwi; stays named, coloured in decl order) and read e through static inline TnsGetEnt(self,i) (return @temp numbered above the offset): 96.5->100. MATCH-PENDING R17, ledger 125. u32 for all six: 87; e in-loop decl or no getter: 95-96; globals inlined in loop (LICM @temps): 94 and ar loaded twice
