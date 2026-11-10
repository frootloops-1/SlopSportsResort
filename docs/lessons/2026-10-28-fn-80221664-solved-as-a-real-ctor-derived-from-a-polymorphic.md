# fn_80221664 solved as a real ctor: derived from a POLYMORPHIC base with out-of-line ctor, compiler stores the vtable; 87.85 -> 100.0 objdump

- status: works
- tags: RPTns_80220994,fn_80221664,ctor,polymorphic-base,induction,vtable,decomp-hard
- scope: Pack/RPSports/RPTnsScene/RPTns_80220994
- source: orchestrator-1028

symptom: free-function form stuck at 87.85-88.1: pointer induction variables (addi rX,self,12), strides coloured top, self last; opt_common_subs off only imitated the ctor
cause: the function is TnsMgr::TnsMgr() whose class derives from a polymorphic base TnsBase{virtual ~TnsBase();} with an out-of-line ctor; the compiler itself stores the vtable. Only that shape yields offset IVs (li 12/36/72) with strides coloured last (i r31, self r30, pl r29)
fix: Model as class ctor (names inferred) with symbols.txt fn_80221664 -> __ct__6TnsMgrFv, lbl_803C40A8 -> __vt__6TnsMgr. These give pointer IVs instead: non-polymorphic base, polymorphic derived with no base, explicit fn_801BC3DC(this)+explicit vt store; an inline polymorphic base ctor gives the right registers but adds a base-vtable store. The TnsPl alloc and the three double-stored sub-objects need an inline scope (static inline new+ctor helper or real new T); the other seven stay inline __nw__FUl/if/ctor; all in helpers rotates strides back to the top. Store form q[i][0]=o; q[i][0]->pl=pl; and for double stores q[i][2]=t[i]=New(); q[i][2]->pl=pl (deref the member stored last: no reload, o stays r4). Pragma sweeps and declaration order flat. Remaining diff: bl __ct__7TnsBaseFv vs retail bl fn_801BC3DC (58 source files reference fn_801BC3DC). Four helpers carry MATCH-PENDING (R17) + ledger row; real source probably used new T with real out-of-line ctors.
