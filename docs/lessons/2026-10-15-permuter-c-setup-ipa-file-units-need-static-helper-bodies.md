# permuter C setup: -ipa file units need static helper bodies

- status: works
- tags: permuter,setup,ipa,C,NWC24
- scope: tools/permute.py
- source: nm-perm-1

symptom: permute.py setup on a C unit reports hundreds of mismatched lines (NWC24CommitMsgInternal 721) for a 99.8% function; base.o far shorter than target
cause: strip_other_fns replaced static helpers with prototypes, but -ipa file inlines statics even when defined after the target; also header ASM(...) bodies break pycparser and any 'PERM_' text (NAND_PERM_RUSR) is read as a permuter macro
fix: permute.py (545c67d4): keep static bodies when cflags have -ipa file, score only the target symbol, prototype asm-bodied header functions, rename PERM_ -> PRMX_ in base.c. NWC24 then set up at 16 lines
