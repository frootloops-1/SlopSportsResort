# resort: ported MSL C units need -func_align 4 and -Cpp_exceptions off

- status: works
- tags: resort,library,port,flip

symptom: port_scan exact but link shifts; extab/extabindex sections Resort lacks
cause: Resort MSL built without exceptions and 4-byte func alignment; ogws flags differ
fix: per-object flags in ported_objects.json: -func_align 4 -Cpp_exceptions off, no extab splits (math_api, mem, strtoul, uart_console_io_gcn)
