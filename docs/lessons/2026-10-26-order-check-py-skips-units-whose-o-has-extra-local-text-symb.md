# order_check.py skips units whose .o has extra local text symbols

- status: works
- tags: emission-order,order_check,flip
- scope: RPSports_802041d0

symptom: Unit 100% in objdiff but Matching flip fails shasum; order_check.py reports nothing
cause: order_check returns early when sorted(text symbols) differ; RPSports_802041d0.o has 38 T/t symbols (18 extra inline pool funcs like GXSetViewportv) vs 20 in target, and unit emitted fully reversed
fix: Use nm -n vs symbols.txt addresses; reorder_fn.py 18 moves to descending address (unit emits reverse of source); flip then gives DOL 0 diff, sha OK
