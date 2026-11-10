# Forecast lever 1 works: declare inline-arg temps up front in colouring order (fn_8022750C)

- status: works
- tags: forecast,regalloc,declaration-order,inline,args
- scope: RPTns_80225530/fn_8022750C
- source: forecast-regalloc

symptom: auto-inlined setter fn(self,k->a4,k->a8,k->ac): r5/r6 swapped for the ac/a8 loads (99.9)
cause: inline-param @vars coloured b before c; named locals are coloured in declaration order (first declared = first coloured = lowest volatile)
fix: TnsMi* c; TnsMi* b; TnsMi* a; TnsKok* k; k=self->kok; c=k->ac; b=k->a8; a=k->a4; fn(self,a,b,c); -> 100. Declaring a,b,c (t7) or initialising at declaration (t1/t2) failed; k must be declared last (else k takes r5)
