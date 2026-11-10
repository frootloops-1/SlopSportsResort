# fn_8027DC80 base-vector const load scheduled first (data-ref residue)

- status: fails
- tags: fn_8027DC80,scheduler,const,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8027d3ec
- source: bsb7d3ec Opus 2026-11-02

symptom: instruction-identical but relocs differ: retail loads BE564(y,f2), BE560(x,f1), 0.0 CB8(z,f0); FLIP-FAIL dol_diff 6 bytes at 0x8027dd05
cause: a const/literal 0.0f load has no dependency on the preceding pointer store stw 0x7c(r28), so the pre-RA scheduler issues it first; the DDATA loads wait for the store. Retail shows the 0.0 load third
fix: none: all 6 assignment orders, ctor form, and a plain 0.0f literal all put the const load first (99.8-99.9). Existing ledger stand-in (const at y) remains
