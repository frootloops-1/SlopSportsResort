# Global read hoisted above stores only via local declared before first store; first of two s32 locals gets lower reg

- status: works
- tags: regalloc,scheduling
- source: RPBsb_80275710

symptom: lwz of sdata global scheduled late
cause: direct field=global read scheduled late
fix: s32 cnt = lbl; before first store; separate float statements avoid fmadds; float sdata pair is f32 lbl[2]={0.1f,0.0f}; standalone =0.0f global goes to .sbss
