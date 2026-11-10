# Callee arg count hides register-only diffs: BoxOn value loaded to r4

- status: works
- tags: rpbox,802ca0a0,args
- scope: RPBox_802c7924
- source: x-golbox-1029

symptom: fn_802CA0A0 99.8%: target loads the BoxOn operand into r4, ours r3
cause: fn_802F9260/fn_802F9354 take a second arg (link / p40C) that the target keeps preloaded in r4 and CSE's with the BoxOn test load; prototypes had 1 arg
fix: declare (void*, void*) and pass BoxLinks(self)[i] / self->p40C: 99.8 -> 100
