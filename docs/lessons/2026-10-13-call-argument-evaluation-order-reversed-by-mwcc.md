# Call-argument evaluation order reversed by MWCC

- status: works
- tags: mwcc,call,order
- source: RPGol_802b90b4

symptom: two nested call args evaluated in the wrong order
cause: MWCC evaluates call arguments in its own order
fix: hoist the first call to a temp: int r=A(); f(self,r,B(self));
