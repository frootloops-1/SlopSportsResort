# TRK sbss var accessed via lis/addi is a common symbol

- status: works
- tags: trk,metrotrk,sbss,common,reloc
- scope: MetroTRK

symptom: mainloop fn instructions identical but 99.76%: reloc target gTRKInputPendingPtr in .sbss (orig) vs .bss (ours); orig code uses absolute lis/addi despite sbss
cause: orig built with -sdata 0 plus -common on: uninitialized global emitted as .comm, linker put it in .sbss; no #pragma common exists (illegal pragma); __declspec(section .sdata) makes access sda21 (95.8%)
fix: needs -common on in cflags for the unit (configure.py, orchestrator); manual compile with -common on gives 100%. Removing the definition (extern only) also scores 100 but is a hack
