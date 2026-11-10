# strtold: old MSL has no strtod symbol; atof inlines it; string-split symbols

- status: works
- tags: msl,strtold
- scope: MSL_C strtold
- source: claude/msl-text strtold 2026-10-09

symptom: atof 69.5, __strtold 98.7, rodata 72, sdata2 72.7
cause: ss has strtod as separate function and newer exponent logic; symbols.txt splits the 'NAN(' string into 1-byte symbols and oversizes INFINITY
fix: Delete strtod, inline its body in atof ('int overflow, count;' order; double DBL_MIN/DBL_MAX defines for own sdata2 constants); old exponent logic (SHRT_MAX/MIN after exp_value += exp_adjust; no zero early-out); result = (float)-(double)HUGE_VALF for fneg+frsp; symbols: lbl_8037B938 size 0x9, lbl_804C0B28 one 5-byte string
