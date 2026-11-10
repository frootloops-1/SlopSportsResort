# MWCC phase-0 sim: integer ops are a separate unit (2/cycle, one rlwinm/slwi per cycle); some 2nd-slot rejections still unmodelled

- status: open
- tags: sched,model,mwcc,sim
- source: round 11

symptom: mwcc-sched-sim mismatched a block with addi/add/rlwinm
cause: sim treated integer ops as FPU; real: dual issue, IU cap 2, shift/rotate cap 1; LSU-at-earliest blocks only the FPU slot; after fadds/psq_l the real scheduler rejects every 2nd-slot candidate (rule unknown)
fix: sim2.py/sim3.py in /private/tmp/scratch-A0E0-r11 (rate block exact; P/Q block first mismatch at 21/37)
