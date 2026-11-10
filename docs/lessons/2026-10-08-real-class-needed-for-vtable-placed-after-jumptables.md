# Real class needed for vtable placed after jumptables

- status: works
- tags: vtable,data,layout,thunks
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene

symptom: manual extern C vtable array is emitted at parse time, before all switch jumptables; orig .data has jumptables then vtable, so jumptable relocs mismatch (325C/32B0 99.3%)
cause: MWCC emits plain globals at definition, jumptables at codegen, compiler vtables at end of TU
fix: local-view class (RPSysScene view + IRPSysHostIOSocket) with real virtual overrides; rename vtable-proven symbols in symbols.txt (Configure/LoadResource/Reset/Calculate/Exit/UserDraw/__dt__ + @36@/@68@ thunks); thunks and dtor then match for free
