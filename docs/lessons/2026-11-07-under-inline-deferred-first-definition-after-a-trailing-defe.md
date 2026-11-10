# Under -inline deferred, first definition after a trailing defer_codegen off is emitted before the flush

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025ff94

symptom: Under -inline deferred, first definition after a trailing defer_codegen off is emitted before the flush
cause: Under -inline deferred, first definition after a trailing defer_codegen off is emitted before the flush
fix: put a harmless definition (hand .ctors entry) first so hand vtables follow the jump table
