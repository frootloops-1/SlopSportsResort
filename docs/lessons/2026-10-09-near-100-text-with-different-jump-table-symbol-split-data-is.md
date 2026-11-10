# Near-100% .text with different jump-table symbol: split .data is wrong

- status: works
- tags: splits,jumptable,msl
- scope: any unit
- source: claude/msl-text strtoul 2026-10-09

symptom: .text 99.9% and the only diffs are 'lis rN, jumptable_XXXX@ha' vs '@NNN@ha'
cause: a unit's switch jump tables live in .data inside a neighbour's range (strtoul's two tables sat in scanf's .data)
fix: Move the .data range boundary in splits.txt (scanf .data end 0x80398FA8, strtoul .data 0x80398FA8..0x80399030); then .text and .data both reach 100%. Also delete ss-only functions (strtoul/strtol/atoi wrappers) the original object lacks
