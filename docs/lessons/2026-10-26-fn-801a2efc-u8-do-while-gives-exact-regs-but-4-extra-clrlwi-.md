# fn_801A2EFC: u8 do-while gives exact regs but 4 extra clrlwi (12 lines)

- status: open
- tags: fn-801a2efc,RPSysSystemWinMgr,loop,u8
- source: claude 2026-10-26

symptom: target latch is addi r29,1; cmplwi r29,2 on the raw counter; for/while forms colour like natural (486)
cause: u8 do-while (++i<2, i++;while(i<2), <2u) keeps a clrlwi r0,r29,24 value in the latch at allocation time = the extra GPR node, exact signature, but emits 4 extra clrlwi (12 lines); != 2 / <= 1 do-whiles 20; combined && 510; switch on unk19 440 and unk19==0-first 304 (block order wrong); continue/implicit !=0/folding fn_801A2BB4/per-site macro flat; per-site do-while mixes coupled (copy1 alone 55)
fix: open lead: find a u8 counter form whose clrlwi lands in the same register (self-targeted, removable) or is folded into the cmplwi; keep branch skeleton from target (stb c1,0xd6 then reload unk19/unk18)
