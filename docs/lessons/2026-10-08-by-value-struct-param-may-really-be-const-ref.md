# By-value struct param may really be const ref

- status: works
- tags: mwcc,abi,gxcolor

symptom: original passes &member directly to a by-value struct param; any source form copies
cause: callee codegen identical for by-value and const&; symbol name in symbols.txt was only a guess
fix: declare param const GXColor& and rename the symbol (RC8_GXColor); caller copy disappears
