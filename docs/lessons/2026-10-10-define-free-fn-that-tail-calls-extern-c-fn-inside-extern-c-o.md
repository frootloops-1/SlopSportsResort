# Define free fn that tail-calls extern C fn inside extern "C" or it mangles (RPGolCamera)

- status: works
- tags: rpgolcamera,extern-c,mangling
- scope: RPGolCamera
- source: haiku

symptom: fn_..__FPv symbol
cause: no extern C on definition
fix: wrap in extern "C" {}
