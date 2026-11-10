# resort library: linker dead-strips unreferenced functions, oversize ported objects can still link exact

- status: works
- tags: resort,library,port

symptom: port_sizecheck says .text too big
cause: ogws-only functions get stripped
fix: try the flip anyway; but remove weak copies Resort emits elsewhere (OSReport)
