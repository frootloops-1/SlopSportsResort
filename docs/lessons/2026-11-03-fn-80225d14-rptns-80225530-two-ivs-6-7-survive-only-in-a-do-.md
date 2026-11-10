# fn_80225D14 (RPTns_80225530): two IVs 6/7 survive only in a do-while with explicit int counters (94.3->97.6)

- status: works
- tags: induction,strength-reduction,iv-merge,do-while,RPTns,colouring
- scope: Pack/RPSports/RPTnsScene/RPTns_80225530/fn_80225D14
- source: opus 2026-11-03 claude/tns5530-1103

symptom: target keeps li 6 / li 7 int IVs (subi 2 each, clrlwi at loop top); every for-loop spelling merged b into a+1 (1 insn short)
cause: in a for(i=3;i>=0;i--) loop MWCC relates any basic IV j with constant init to i (j=2i+1) and rewrites it as i*2+1, then CSEs i*2 (also for explicit j=7 / u32 j). With while(--i>=0) (unknown i init) j survived; with i=3; do{...}while(--i>=0) the init is constant yet j is NOT related. Derived IVs never fold the +1 (b=j+1 / i*2U+1 stay addi).
fix: ja=6; jb=7; i=3; do { u8 a=ja; u8 b=jb; ...; ja-=2; jb-=2; } while(--i>=0); -> same insn count as target (57/57 diff lines), 97.1; declaring anm, ja, jb first -> 97.6. Remaining = pure colouring: target anm r31, ja r30, jb r29 coloured BEFORE the IRO pointer IVs (nx r28 ids r27 w/aptr r26 e/w2 r25, i r24); ours pointers first. Indexing self->a[i] in loop 1 (no named e) reproduces the target pointer live ranges exactly (12-114/14-113/16-112/18-111) but scores 96.7 (jb coalesces with i). Inline getter for anm: no change. mwcc_dbg unavailable 2026-11-03: ~/Downloads/retrowin32 (target/lto/retrowin32) is gone, so no dump was taken.
