# fn_802AA714: retail colour base r16 implies late colouring; ours base vreg coloured first

- status: open
- tags: regalloc,rpgol,aa614,colour-table
- scope: RPGol_802aa614 fn_802AA714
- source: gol-aa614-1105

symptom: with the retail block split (natural order + dead store probe) the 8D24 base still lands in r4, retail r16
cause: mwcc_dbg: GPR colouring order is by adjusted cost = cost/previous-neighbours; base vreg cost 66 / 3 -> 22, coloured first, lowest free r4. Retail r16 sits between c1 byte0 (r17) and byte1 (r15): its base had adjusted ~0.19, i.e. far fewer uses per vreg or a different vreg structure
fix: open; pointer local is propagated (no change), struct {names,cols} global 33.2, named GolColor locals scalarised 51.7. Parked.
