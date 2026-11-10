# CpuTexture setColor I8: inline-helper vreg-numbering forms do not move red r0/offset r6

- status: fails
- tags: cputexture,setcolor,register,inline-helper,coloring
- scope: egg/gfxe/eggCpuTexture
- source: worker claude/cpu3-1027 2026-10-27

symptom: setColor I8: red byte r0 (orig r8), pixel/final offset r6 (orig r0); orig colors offset before red
cause: Coloring order is not set by virtual-register creation order: moving the offset computation into a static inline (expanded after the red temp) leaves the allocation unchanged. Order seems fixed by the pre-RA schedule or interference degree, not source numbering
fix: Failed: (1) static inline setColorI8(this,x,y,color.r) holding the whole I8 body; (2) red loaded at call site + static inline calcOffsetI8(this,x,y) returning the multi-def offset. Both identical 8-line diff (6 DOL bytes). Parked.
