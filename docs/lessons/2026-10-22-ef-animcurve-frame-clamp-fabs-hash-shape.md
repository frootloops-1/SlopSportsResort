# ef_animcurve frame clamp / fabs / hash shape

- status: works
- tags: ef_animcurve,fabs,clamp
- source: decomp-hard U8 2026-10-22

symptom: U8 frame calc and hash order mismatch
cause: ternary clamp and split hash statements differ from orig
fix: u16 f=tick; if(tick>=len-1) f=len-1; use __fabs not fabs; hash as seed*C1+hdr*C2+(loop*C3+cmd*C4+0x4BF53); frame inline returns u16 with s32 internal, single exit
