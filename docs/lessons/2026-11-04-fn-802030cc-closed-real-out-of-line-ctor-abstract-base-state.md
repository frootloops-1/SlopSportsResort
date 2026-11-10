# fn_802030CC closed: real out-of-line ctor + abstract base state class whose dead vptr store fixes scheduling

- status: works
- tags: ctor,ptmf,vtable,scheduling,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: ctor at 82.8 after real-ctor rename: li -1 and PMF address/load scheduling differ
cause: retail state members derive from an abstract base (vtable all zero, 0x14 bytes after the derived vtable); the eliminated base vptr store still shapes the scheduler blocks
fix: struct SpSelStateBase { virtual ~; 2 pure virtuals }; derived declares overrides; hand arrays __vt__14SpSelStateCtor[5] + __vt__14SpSelStateBase[5] (explicit_zero_data on) after defer_codegen off; rename fn_ to __ct__ in symbols.txt and in the caller unit's extern C decl/call
