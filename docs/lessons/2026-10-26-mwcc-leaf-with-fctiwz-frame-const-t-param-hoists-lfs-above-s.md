# MWCC leaf with fctiwz frame: const T* param hoists lfs above stwu

- status: works
- tags: scheduling,const,stwu,axfx,fctiwz
- scope: src/revolution/AXFX
- source: axfx-1026

symptom: AXFXReverbHiExpGetMemSize 59%: ours has lfs before stwu, target has stwu first and loads in source order
cause: const-qualified pointer param lets the scheduler hoist loads (incl. sda consts) above the frame setup; not compiler-version dependent
fix: drop const on the param (header + source): 59 -> 100 (also Dpl2)
