# RPBsb_8025a3e8 nested Vec temp order (outer call temp allocated before inner) unchanged by every call spelling

- status: fails
- tags: fn_8025C2C8,fn_8025B680,fn_8025AC2C,RPBsb_8025a3e8,temp-slots,stack-layout
- scope: RPBsb_8025a3e8
- source: claude/bsb5a3-c-1107 opus

symptom: C2C8/B680: BsbAddV(p, dir*c) target mul temp above add temp (temps descend in creation order); ours add temp first
cause: MWCC allocates the outer by-value call result temp before evaluating its arguments, for inline wrappers and direct calls alike
fix: failed: direct fn-ptr cast call, operator+, BsbAdd (local r), BsbMaddV/BsbLerpV, wrapper inline Madd2/Madd3, by-value inline param, BsbSetXZv, const& bound temp, aim=...;aim.y=.., named s local (worse). Kept asm.
