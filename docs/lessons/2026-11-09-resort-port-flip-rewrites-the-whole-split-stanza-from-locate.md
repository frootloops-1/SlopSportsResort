# resort: port_flip rewrites the whole split stanza from located sections only

- status: works
- tags: resort,library,port,flip

symptom: flip silently loses .sbss (FILE_POS errno) or widens a data range (alloc .bss)
cause: port_flip writes only the sections it found
fix: diff splits.txt after every flip; port_sizecheck.py afterwards
