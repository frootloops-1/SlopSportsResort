# Unit with -inline deferred emits in reverse source order: write source in reverse address order

- status: works
- tags: emission-order,RPUtlLytFrameCursor,sdata2
- scope: unit

symptom: order_check: ours fn_801C9CFC first, target fn_801C8330 first; pool literals also follow emission order
cause: functions are emitted (and literal pool entries created) in reverse source order
fix: reverse function order in source; .data objects in definition order (table before vtable); __sinit-like ctor stays first in source
