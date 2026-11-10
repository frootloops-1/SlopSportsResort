# Doubled cmpwi;beq;beq before virtual Stop

- status: works
- tags: snd,handle
- scope: RPGol_802bb608
- source: opus-worker

symptom: two beq before handle Stop
cause: explicit IsAttachedSound check around Stop which checks again
fix: if (h.IsAttachedSound()) h.Stop(n);
