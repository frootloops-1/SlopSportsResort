# mwcc @-id classes: inline locals/params first, then source-order temps (new/return), then optimizer temps; within a colouring group smaller @id -> lower register

- status: works
- tags: regalloc,inline-level,mwcc,RPBow_8031641C,accessor
- scope: GC/3.0a5.2 Pack
- source: RPBow_8031641C round 4

symptom: Loop locals colour in the wrong rotation (e.g. body r30 vs retail r26) although instructions match
cause: Dump of fn_80316C7C/fn_80318EB0: hand-new/inline locals and nested-inline params get the lowest @ids (in source order), inline RETURN temps and new-temps are numbered afterwards in source order, LICM/strength-reduction temps last; named locals are below all @. In a group, smaller @id gets the lower callee-saved register
fix: Reorder by turning values into inline return temps and ordering the calls: RPBow_8031641C kokeshi loops closed with body accessor called BEFORE head accessor and the mirror material read through a return-value accessor BowGetMaterial(mdl,i) passed to the nested BowSwapCull (R17 246/247); nesting level of an inline local does not matter
