# Orphan static inlines from OS.h inflate .text; and fn order reversed with inline member

- status: works
- tags: headers,order,sha1
- scope: RPBox

symptom: verify.py 100% per function but DOL SHA1 fails; .o .text bigger than orig (OSSetGQR6/OSInitFastCast emitted) and function order reversed
cause: nw4r/math.h pulls revolution/OS.h whose non-inline statics are emitted into the TU; an inline member used by a function reverses emission order
fix: source-local forward decls instead of the heavy header; put functions in reverse order in source; compare 'objdump -h' .text size src vs obj and nm -n order, not just verify.py
