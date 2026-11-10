# RPBow_803381DC: local fabs/fabsf copies instead of <cmath> needed for fn_803395E4 (cause open)

- status: open
- tags: rpbow,cmath,fabs,honesty

symptom: including real MSL <cmath> drops fn_803395E4 100 -> 90.5; local copies of MSL fabs/fabsf bodies give exact
cause: unknown: likely overload/inline resolution or a different __fabs path via the header
fix: Open: investigate why the real header differs, then replace the local copies (they are not R17-marked; a source comment explains)
