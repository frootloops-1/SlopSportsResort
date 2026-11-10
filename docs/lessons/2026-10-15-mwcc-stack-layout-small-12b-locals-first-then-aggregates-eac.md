# MWCC stack layout: small (12B) locals first, then aggregates, each in reverse declaration order

- status: works
- tags: stack,locals,layout,mwcc
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: fn_8022B7D4 95%: three 12B vectors at low offsets, orig has them between 0x24/0x30 aggregates; declaration order/blocks/ctors had no effect
cause: MWCC allocates <=12B locals first (reverse decl), then larger ones (reverse decl)
fix: group the three vectors into one 36B struct (look-at basis {x,y,z}) so it sorts with the aggregates; declare in reverse of wanted bottom-up order
