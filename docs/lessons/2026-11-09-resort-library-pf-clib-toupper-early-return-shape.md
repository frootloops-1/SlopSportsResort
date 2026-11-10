# resort library: pf_clib toupper early-return shape

- status: works
- tags: resort,library,port

symptom: addi/ble/mr instead of cmpwi/bltlr
cause: ||/&& and ternary forms
fix: if (c < 'a') return c; if (c <= 'z') return c - 32; return c;
