# Inline helper args evaluated right-to-left: reverse param order

- status: works
- tags: inline,args,load-order
- scope: RPTns
- source: RPTns_80222a70

symptom: x,y,z loaded z,y,x from inline Set3(d,x,y,z)
cause: MWCC evaluates inline call args right to left
fix: declare helper (z,y,x) and call reversed (fn_802231CC 91.7->98.3)
