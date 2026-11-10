# -inline deferred unit: defer_codegen off + ascending order breaks inlining when a fn is called before defined

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025ff94

symptom: -inline deferred unit: defer_codegen off + ascending order breaks inlining when a fn is called before defined
cause: -inline deferred unit: defer_codegen off + ascending order breaks inlining when a fn is called before defined
fix: keep deferred; move every fn_ definition to file end in descending address order with a prototype block
