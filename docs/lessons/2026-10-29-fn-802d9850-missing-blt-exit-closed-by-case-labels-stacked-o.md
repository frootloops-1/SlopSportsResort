# fn_802D9850: missing blt exit closed by case labels stacked on default (Switch.c binary-search model)

- status: works
- tags: fn_802D9850,RPBox_802cf93c,switch,jumptree,marker
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: cmp 9;beq;bge;cmp 1;beq;blt;b;b (target) vs bge instead of blt (99.8)
cause: emit_case_range_binary_search (~/Downloads/mwcc-cuyler36/src/backend/Switch.c) splits on case RANGES incl. default gaps; 'blt default; recurse(right)' at pivot [1] needs a non-single range right of it, and the extra trailing b is the first case body. Labels stacked on default share its pclabel and merge with adjacent stacked cases
fix: switch{case 1: body; break; case 9: return; case 2: case 3: case 10: default: break;} -> 100 (R17 marker). Simulate build_case_ranges + emit_case_range_binary_search by hand to design case sets for any compare-tree diff
