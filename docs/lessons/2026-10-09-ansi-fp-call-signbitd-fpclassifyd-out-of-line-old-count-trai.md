# ansi_fp: call __signbitd/__fpclassifyd out of line; old count_trailing_zero shape

- status: works
- tags: msl,ansi_fp
- scope: MSL_C ansi_fp
- source: claude/msl-text ansi_fp 2026-10-09

symptom: __num2dec_internal 0%, __dec2num 87.5%, .data 17.8% (extra jump tables), sdata2 bloat
cause: ss float.h/cmath inline the classification helpers; ss-only 'unused' string shifts string offsets
fix: Drop <cmath>/<climits>, declare prototypes (frexp, ldexp, pow, copysign, int __signbitd(double), int __fpclassifyd(double), extern int __float_huge[]); ctzl = 32-__cntlzw(~x&(x-1)); __count_trailing_zero locals n,hi,lo with lo=l[1]; hi=l[0]|0x100000; n=ctzl(lo); if(lo==0) n=32+ctzl(hi); __dec2num: 'if (__fpclassifyd(g) != 2) {} else goto done;'; delete ss-only strings. OPEN: __num2dec 98.65% has 2 reg swaps inside inlined __must_round/__dorounddecup
