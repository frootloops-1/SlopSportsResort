# RPBsb fn_80275810 parked at 96.8: lfs placement and r0/r6/r7 int regs

- status: fails
- tags: near-miss,regalloc,scheduling
- source: RPBsb_80275710

symptom: lfs lbl_804BE3A0 after fadds (orig before spInstance lwz); count/li0/fctiwz regs r0/r6/r7 in orig
cause: unknown
fix: Dead ends: all 120 store orders x 4 local forms, 360/1260 orderings with cnt/spd locals, inline setter subsets, k local/k*()/v*=k/inline helper, struct-array ids table, t+=0.5f. Separate float statements t=6*x; t=3.6*t; v=0.5+t; v*=k gives fuls/fadds (no fmadds) and sdata2 order. Best copy scratchpad bsb_80275710_967.cpp. Try permuter
