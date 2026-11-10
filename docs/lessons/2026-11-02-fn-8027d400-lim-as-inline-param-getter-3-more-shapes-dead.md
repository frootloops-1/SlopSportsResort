# fn_8027D400: lim as inline param / getter, 3 more shapes dead

- status: fails
- tags: fn_8027D400,fpr,inline,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8027d3ec
- source: bsb7d3ec 2026-11-02

symptom: reloaded limit still f2 not f0 (99.3)
cause: lim stays an IRO/inline-param vreg (f34) below back-end pos/timer temps f52-f63; arg evaluated at the call keeps load early but vreg low
fix: none: getter->local 99.84 same; getter direct in compare 97.3 (load after stores); inline Adv(s,d,G) with explicit adds same; Adv->Wrap(lim) two-level same
