# RPGol_802b4f2c fn_802B51D0: three inline getters give ball/pos/pin retail colouring

- status: works
- tags: RPGol_802b4f2c,fn_802B51D0,colouring,getter

symptom: r26/r28 ball/pin swap 99.8, decl-order perms flat
cause: named locals get reverse-decl lowest vregs; pin (higher degree) coloured before ball
fix: GetBall/GetPin/GetPos static inline getters for all three (needs all three; any two 99.6-99.8), R17 row 82. Script sweep of 24 decl perms x 8 getter subsets takes ~2min
