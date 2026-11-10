# fn_801A2EFC header-body angle closed: restart/reset/start bodies and field widths flat

- status: fails
- tags: fn-801a2efc,RPSysFrameCtrl,RPSysLytAnmObj,header
- source: claude 2026-10-26

symptom: natural restart() colours pMgr r28 / c1 r27 in the 4 UpdateButtonAnm copies (486 lines)
cause: exact restart sites fix store order stfs 0x14, stb 0x5, sth 0x6 so Q3 order is not the original; direct-field bodies, (f32)/(s32)/temp conversions, reference, setFrame+start and mIsEnabled u16 / mFlags,mPlayMode bool / start()=1 all give identical 486-line signature
fix: unsolved; extra GPR value does not come from restart()/reset() bodies. Kept reset();start() split = 4 lines
