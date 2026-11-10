# fn_802AA714: scheduler hoists 5 colour lbz groups, retail 4 (pre-RA window, not regalloc)

- status: open
- tags: rpgol,aa614,scheduler,hoist,colour-table,ctor
- scope: fn_802AA714
- source: gol-aa614-1105 16f0c7cb9

symptom: fn_802AA714 33.7%, 462 diff lines; ours loads colour 0 byte (lbz r21) right after the string-base lis; c4 bytes spilled to stack 0x68..0x74
cause: mwcc_dbg backend dumps: pre-RA scheduler hoists lbz of colours c0..c4 above all stores; retail hoists only c0..c3 and loads c4+ after c0..c3 stores; retail keeps the colour-table base in r16
fix: open. Failed: plain GolColor for colour 0 (same), interleaved string/colour stmts (23.4), inline SetCol by value (32.4) / const-ref (33.7), local const GolColor aggregates (0.0: pool->stack->table copy), static const locals (33.6), user copy ctor (build error). Next: change pre-schedule insn count (string address shape), 4-colour inline setter as alias barrier
