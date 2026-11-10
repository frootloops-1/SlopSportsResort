# SIInterruptHandler: volatile InputBufferVcount reproduces the retail reload in the poll-check ||

- status: works
- tags: SIBios,CSE,volatile,reload,marker
- scope: revolution/SI/SIBios
- source: SIBios session 3

symptom: Target reloads InputBufferVcount[i] in the || second operand (4 extra lwz, 16-byte gap); plain array CSEs it; operand order, nested if, x>>1, split ifs with continue did not help
cause: Retail load is not CSEd; volatile array gives exactly that and size 1004 matches (96.7 -> 98.8). Marker, ledger row 22
fix: static volatile u32 InputBufferVcount[] with MATCH-PENDING comment; residue is sr priority (target sr r26, ours r18; everything else shifts by one)
