# fn_802D3CF8: clrlwi on a u16 call arg survives only when the narrowed int's def is a CSE copy (re-read the field in the condition)

- status: works
- tags: fn_802D3CF8,RPBox_802cf93c,clrlwi,u16,zero-extend,inline,float-const
- scope: RPBox_802cf93c
- source: claude/box802cf-r5-1029 opus

symptom: retail has clrlwi r10,r10,16 before the call (u16 param); u16 h, int h, u32 h, s32-param prototypes all drop it (PCode const-prop turns the rlwinm into mr when the reaching defs are lhz/li)
cause: the extension is removable only when the reaching def is the lhz itself; if the condition re-reads dc->h0 (if (dc->h0 != 0 && ...)) the IR CSEs it and h's def becomes a copy, so the clrlwi stays; also: a float constant passed as an inline ARG is substituted (loaded late at the call) while a LOCAL f32 k = 1.0f is loaded early and held in a register
fix: int h = dc->h0; if (dc->h0 != 0 && w148 == dc->w14) { h = 0; w = 0.0f; } -> size match 99.1; inline takes const BoxInput& in (in.f14 read at the call) + local f32 k = 1.0f -> 99.3. Scratch harness: compile a tiny .cpp with the unit's flags to test such rules in seconds
