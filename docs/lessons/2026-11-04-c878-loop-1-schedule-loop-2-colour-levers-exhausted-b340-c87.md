# C878 loop 1 schedule/loop 2 colour levers exhausted (b340-c878g)

- status: fails
- tags: regalloc,schedule,declaration-order,b340,C878
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: retail loop 1 loads ax,ay,bx (early ay+dy); loop 2 -100/0.5/magic want f31/f30/f29
cause: store order not source-ordered; named locals merge into load temps; named half const or helper shapes worse
fix: dead: named h=0.5 all z/h/step orders (43-55); 120 store perms identical; 384 raw/inline x order (>=44); bx2 720 perms (47); x0/x1 precompute (49); SetSelLine helper (86); compute-all-then-store (60-63). Next: compare backend-01/02/07 schedule dumps for ay vs bx priority
