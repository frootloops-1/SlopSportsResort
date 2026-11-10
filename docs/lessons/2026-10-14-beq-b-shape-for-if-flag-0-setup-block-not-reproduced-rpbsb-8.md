# beq+b shape for if(flag==0) setup block not reproduced (RPBsb_8028d9e8)

- status: open
- tags: branch-layout,control-flow,matching
- source: RPBsb_8028d9e8 partial 4/8 (claude/rpbsb 947f4a30)

symptom: Original emits 'beq setup; b end; setup: ...; end:' for if(flag==0){setup} in fn_8028D9E8, fn_8028DAC4, fn_8028DBFC (case 2); ours emits 'bne end' with the body fallthrough (D9E8 97.8%, DAC4 ~87%, DBFC 98.3%)
cause: Unknown. Not produced by a plain if, nor by an empty-then if/else with the body in else
fix: open: try a switch on flag, goto-based layout, or a shared inline helper for the setup block; compare the three functions together
