# fn_80225D14 closed: do-while with a=i*2, b=i*2+1 gives two IRO IVs (6,7) coloured first; anm via sweep 2

- status: works
- tags: induction,strength-reduction,colouring,sweep2,do-while,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_80225530/fn_80225D14
- source: opus 2026-11-03 claude/tns5530-1103

symptom: 97.6 with named ja/jb do-while counters: same insns, but anm/ja/jb coloured after the IRO pointer IVs (target anm r31 ja r30 jb r29)
cause: IRO derived-IV temps get vreg numbers above named locals and are created in order of first appearance; in i=3; do{...}while(--i>=0) MWCC does NOT CSE i*2 into i*2+1 (unlike for-loops) so both become IV temps 6/7 created before the pointer IVs. anm (deg 30) survives sweep 1 only if it is the lowest named vreg except self (declared last, inner u8 a/b moved to fn top). Loop-1 e must be an IV temp (e[i] indexing off a named base TnsEnt* e = self->a keeps the addi self,0xd4 base) so it colours before the loop-1 pointer IVs.
fix: u8 a; u8 b; TnsAnmV* anm = ... declared last; TnsEnt* e = self->a; loop1 uses e[i].x; i=3; do { a=i*2; b=i*2+1; ... f=self->a[i].f8 ... } while(--i>=0); f32 cap; f32 rem=1.0f; cap=rem; (FPR swap). -> 100, FLIP-OK. Inner-scope u8 a/b: 97.4. self->a[i] in loop1: 99.5 (base self, offsets 0xf0). Dumps took 6 s each; colour replay (color_sim + DFS over valid colour orders) pinned the needed vreg order before any source try.
