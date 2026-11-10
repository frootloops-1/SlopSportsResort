# RPSports_8020a5f0: string blob + Names tables -> literals/local arrays; magic-double pool order via dead literal

- status: works
- tags: string-pool,literals,sdata2,pool-order,RPSports_8020a5f0
- scope: RPSports_8020a5f0

symptom: fn_8020AF18 90.2, .rodata 0%, .sdata2 25%
cause: extern string blob + extern name tables instead of literals and local const char* arrays; int-to-float magic double is pooled at lowering after the function's other float literals
fix: Literals + local const char* x[N] arrays (rodata 0->100, AF18 100); (void)1.0f; (void)4503601774854144.0; dead literals give pool order 1.0f, double, 0.0f (R17 marker 100). bool f = a != 0 && b == 0 moved a flag to r4. fn_8020A5F0 stuck at 98.7: bOff vreg 41 deg 31 coloured before self; declaration order/scope/inline wrapper/regsearch all flat.
