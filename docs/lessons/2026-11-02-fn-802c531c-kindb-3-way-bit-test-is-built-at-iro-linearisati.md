# fn_802C531C KindB: 3-way == bit test is built at IRO linearisation; CSE var sits inside the bool shape

- status: fails
- tags: colouring,bool,bit-test,IRO,CSE,RebuildLogicalExpressions,RPGol,fn_802C531C
- scope: Pack/RPSports/RPGolScene/RPGol_802c441c
- source: gol441c2-1102-opus

symptom: x==3||x==4||x==16 (u16) bool lands r4, lhz/addis chain r3; target the reverse
cause: IRO linearisation emits @b=0; if((u16)ld+0xfffd>13) goto F; if(!((1<<..)&0x2003)) goto F; @b=1. Pass-1 CommonSubs puts @C=(u16)ld+0xfffd inside that shape, so RebuildLogicalExpressions cannot rebuild it, and ExpressionPropagation (063) forwards any u16 local into @C, so the lhz stays a codegen temp that colours before every @var
fix: none: tried st->f120 x3, ELOR as call arg (neutral), u16 local, s=st copy, ?true:false, scalarised struct member, f=st->f120 as arg, explicit int d=ld+0xFFFD bit test (158: bool rebuilt but backend makes li 1 -> mr from slw constant), d=ld; d+=0xFFFD (156: lhz lands in var but d+K becomes codegen temps). Untested: CSE only at the last CommonSubs (074) with f a fn-level local
