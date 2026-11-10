# Compare result as bool via static inline gives mfcr/extrwi (fn_8028F0E8)

- status: works
- tags: RPGolCameraManager,float,bool

symptom: orig uses mfcr+extrwi./srwi. after fcmpo
cause: comparison returned as bool from helper
fix: static inline bool isFarther/isCloser on GolVec2 lenSq; GolVec2 w = v; for extra stfs copy; goto end for early exit
