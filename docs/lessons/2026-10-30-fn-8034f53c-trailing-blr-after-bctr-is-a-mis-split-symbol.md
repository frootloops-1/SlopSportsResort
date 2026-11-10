# fn_8034F53C trailing blr after bctr is a mis-split symbol

- status: works
- tags: split,symbols,tail-call,bctr,blr,RPBow_8034E974,fn_8034F53C
- source: claude/bow-1030

symptom: Function ends in bctr tail call; ours adds one dead blr (size 52 vs 48); 14+ source shapes fail
cause: dtk split the dead exit blr into a separate unreferenced 4-byte function (fn_8034F56C). MWCC always keeps the exit blr when the tail-call block is last
fix: Remove the empty stub from source, set the caller size to include the blr in symbols.txt and delete the stub symbol. DOL links 0 bytes. Check: is the next 4-byte blr-only fn unreferenced?
