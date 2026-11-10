# Inline helper argument eval order is right-to-left

- status: works
- tags: order,args,inline,eval
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: a value orig computes last is computed first (or vice versa)
cause: MWCC evaluates call args right to left; in a binary expr the call-containing operand goes first
fix: pass the values as inline-function args in the order needed, e.g. golDist(len, abs(x), abs(y)); put v last in remap(in0,in1,out0,out1,v) so it loads first
