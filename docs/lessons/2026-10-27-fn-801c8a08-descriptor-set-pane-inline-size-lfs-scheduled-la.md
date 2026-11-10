# fn_801C8A08 Descriptor::set(pane) inline: size lfs scheduled late; retail CSEs pane loads across strcpy

- status: fails
- tags: fn_801C8A08,RPUtlLytFrameCursor,schedule,CSE,struct-copy
- scope: function

symptom: 8 inlined set(PaneView*) copies: retail loads size and stack MTX words before cold lwz; retail also reuses lbz previous.valid and lwz mtx._01 (r27) where ours reloads (+2 instrs)
cause: unknown; not statement order (full sweep), not propagation, not copy form, not const param, not helper boundary
fix: failed: decl/store order sweep, opt_propagation off, MTX34 assign/ctor/_MTX34/const&, Pair/POD size temp, const PaneView*, ref param, setValues/setMtx helpers, VEC2 temps; parked at 90.4
