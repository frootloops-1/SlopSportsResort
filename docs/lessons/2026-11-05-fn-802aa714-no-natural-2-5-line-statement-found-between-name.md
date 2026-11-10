# fn_802AA714: no natural 2-5 line statement found between names and colours

- status: fails
- tags: rpgol,aa614,block-split,dead-ends
- scope: fn_802AA714
- source: gol-aa614-1105

symptom: need 2-5 extra initial pcode lines between name and colour stmts to reproduce retail block split
cause: IRO removes dead exprs/locals before codegen; inline helpers with tbl/self params, pointer/ref table locals, empty member ctors, real C++ ctor, inline operator=, named temps all give 0 extra lines or change per-colour counts
fix: open: interleaving search (1495 orders + colour perms) tops at 81.3; remaining = block-A RA (retail keeps colour base r16). name[0] cannot move (string pool follows source order)
