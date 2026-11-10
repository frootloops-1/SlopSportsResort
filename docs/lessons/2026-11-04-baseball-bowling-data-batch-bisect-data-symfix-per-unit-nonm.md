# Baseball/bowling data batch: bisect data_symfix per unit; NonMatching partial-code unit can shift DOL; zsh no word-split

- status: works
- tags: data,symbols,data_symfix,baseball,bowling,explicit_zero_data
- scope: RPBsb_802656a4, RPBsb_80283fe0, RPBowPinSetter, RPBowTrajectoryGuide

symptom: data_symfix on 33 baseball/bowling units: whole batch gave 866-byte DOL diff; my per-group bisect falsely passed
cause: RPBsb_80283fe0 (NonMatching, code 60.9%) edits shift linked layout. Bisect falsely passed because the Bash tool runs zsh: unquoted $VAR with newline-separated paths is ONE argument, data_symfix crashed with AttributeError and applied nothing
fix: Gate each unit alone in a loop over $(cat file) (that does split), drop failing units, apply the rest; in zsh use ${=VAR}. Merged hand vtable array (void* x[10]) with an all-pure 2nd half: split into two arrays, the zero one under #pragma explicit_zero_data (else .bss). Source sbss pad vars (u16 gap_2 + u8 gap_4[4]) need matching gap_2/gap_4 config lines instead of dtk gap_6
