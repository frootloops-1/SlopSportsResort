# RPTns_8024c194 sdata2 tail is linker alignment padding

- status: works
- tags: RPTnsScene,sdata2,alignment,padding,flip-gate
- scope: Pack/RPSports/RPTnsScene/RPTns_8024c194
- source: codex-tns-c194-1103g; build/evidence/tns-c194-1103g

symptom: Reported near-95% sdata2 residue; current objdiff-cli 3.8.2 unit_cmp scores all data sections 100%. Original object sdata2 is 40 bytes, normal source object 36, both aligned to 8. Last four target bytes are the synthetic hidden gap_12_804C3224_sdata2, after the actual 4-byte float zero @1247 at 0x804C3220.
cause: The extra four bytes are section-end zero alignment padding, not a missing or incorrectly valued constant. The next unit RPTns_8024dc50 has an 8-aligned sdata2 section, so linking the 36-byte candidate contribution supplies the same four zeros. The original last real constant is loaded with lfs, not lfd; do not extend it into an invented double or add a dead literal merely to match raw object size.
fix: No data/source/symbol edit is needed. An ACTUAL temporary Matching flip of the baseline links equal-sized 3995168-byte DOLs with exactly 10 differing bytes, all in the four fn_8024D358 preheader instructions at 0x8024D610, 0x8024D618, 0x8024D628 and 0x8024D630. Direct linked-byte comparison of all 40 bytes at 0x804C3200..0x804C3228 is identical, including relocations and the tail gap. Only the three known symbol collisions present. Gate fails solely on code; unit remains NonMatching. Evidence target.s, baseline-gate.log and baseline-gate-summary.json; normal restored NonMatching DOL 0 is a health check using the original object, not candidate validation.
