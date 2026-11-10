# resort: ported object 4-12 bytes shorter than its split shifts the link

- status: works
- tags: resort,library,port,flip

symptom: DOL diverges after the ported unit
cause: Resort pads to 16 before the next file
fix: align:16 on the next split; if the next code is auto, carve unk/text_<addr>.cpp with align:16 to the next known split; dol_blame names the unit
