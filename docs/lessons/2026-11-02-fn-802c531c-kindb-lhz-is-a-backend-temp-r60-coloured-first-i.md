# fn_802C531C KindB: lhz is a backend temp (r60) coloured first; IRO always forwards the load into @C; sweep-2 lever does not apply

- status: fails
- tags: regalloc,IRO,expression-propagation,RPGol_802c441c
- scope: RPGol_802c441c fn_802C531C

symptom: 99.8%, 18 diff lines: lhz 0x120 in r3 / bool in r4, target is the reverse
cause: Bool is front-end var r42, CSE var @C=ld+0xFFFD is var r39, lhz result is backend temp r60; temps are numbered above vars so it is coloured first and takes r3. Target needs the lhz in a var like @C, but ExpressionPropagation forwards the load into @C every time. color_sim gives the bool degree 10 (< K=29), so the declare-last/sweep-2 lever from fn_80236358 cannot apply.
fix: No source found. Dead: volatile cast on the argument, named bool kb via local pointer, volatile u16 local, u16 f with two defs, combined early-return inline golShotKindAB (96.6: in condition context the 3-way test becomes a cmplwi chain, no bit test), regsearch --generic 8 min / 2025 evals (no variant below baseline 2.5). Idea: a form where IRO keeps the u16 load in its own var (CSE shared with a second st->f120 use removed later, or a load ExpressionPropagation may not forward). Parked.
