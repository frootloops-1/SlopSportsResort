# Inlined helper reg order follows declaration order; one shared helper can't satisfy two callers

- status: works
- tags: msl,ansi_fp,regalloc,inline
- scope: MSL ansi_fp, any shared inlined helper
- source: claude/msl-text ansi_fp 2026-10-09

symptom: __num2dec 98.65%: base/i registers swapped inside inlined __must_round/__dorounddecup
cause: volatile reg assignment follows declaration order; __timesdec/__str2dec need b-first, __num2dec needs i-first; hoisted 'e' pointer in __must_round also wrong
fix: __must_round: for (i++; i < d->sig.text + d->sig.length; i++) with no hoisted e; give __rounddec its own i-first loop and mark it static inline (otherwise it stops auto-inlining)
