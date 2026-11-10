# CpuTexture setColor: GXColor param type, direct member access and header inline bodies no gain

- status: fails
- tags: cputexture,setcolor,header,gxcolor,version-sweep
- scope: egg/gfxe/eggCpuTexture

symptom: setColor I8 red r0 vs r8, offset r6 vs r0 (8 lines)
cause: param constness, member-vs-getter access and getter inline bodies do not change the colouring of the I8 block; compiler build is not the lever either (version_sweep: 3.0a5.2 and 3.0a5 and 3.0a3.3/3.4 identical 15/16, 3.0a3/3.2 worse)
fix: none: const GXColor param (cpp only and cpp+header) 8 lines; mWidth/mpBuffer direct 8; all-direct setColor 10; new getBufferU8()/getWidthTiles8() header inlines 8/10. Header edits caused 0 regressions in eggLightTexture, eggPostEffectMaskDOF, eggDrawPathBloom, eggCapTexture (all still 100%, baselined). Sources restored; mw_version unchanged (GC/3.0a5.2)
