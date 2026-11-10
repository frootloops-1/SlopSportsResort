# VI vi.c: copy the later-SDK reference structure instead of hand-expanding

- status: works
- tags: VI,vi.c,inline,statics
- scope: src/revolution/VI/vi.c

symptom: VIConfigure/VIConfigurePan/setFbbRegs/setVerticalRegs stuck 65-84% with unk_0x fields and hand-expanded helpers
cause: Wrong register array (setVerticalRegs read shdwRegs, target reads regs); AdjustPosition param was s16 VIAcv and DispPosX cast missing; helpers (calcFbbs, setPicConfig, setInterruptRegs) hand-unrolled
fix: Named HorVer/timing fields; calcFbbs x2 in setFbbRegs; AdjustPosition(u16) with (s16) casts and CLAMP; regs/HorVer non-static to match nm scope; name .data string-pool symbols in symbols.txt so reloc base matches (cleared the ...data.0 diff)
