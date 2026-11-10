# DATA-REF near-miss from alias label/linker symbol names: use the name dtk shows in the asm

- status: works
- tags: relocation,label,alias,OS,data-ref
- scope: revolution/OS/OS

symptom: OSInit/OSExceptionInit 99.9% with DATA-REF diffs: sym name differs at same address (__OSDBJUMPSTART vs __OSDBINTEND, _db_stack_end vs _stack_addr)
cause: dtk names a relocation target by address (first label / known linker symbol); source used an alias name for the same address
fix: Source uses the asm's name: __OSDBINTEND for jump start (drop the extra entry label), _stack_addr instead of _db_stack_end. Adding a duplicate label in symbols.txt does not help (it renames all uses and regresses __OSDBJump).
