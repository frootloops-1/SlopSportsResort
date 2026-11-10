# MWCC emission rules: class template member order (generic members after vtable in declaration order)

- status: works
- tags: emission-order,vtable,template,jumptable,specialization,inline-deferred,RPGrpModelAnmImplement
- scope: RPGrpModelAnmImplement
- source: opus worker, verified 2026-10-12

symptom: Vtable mid-.data with jumptables of later functions after it; vtable always last for explicit class specialization
cause: Strong fns/explicit specializations: reverse source order then vtable; inline virtuals after vtable in reverse declaration order; never_inline inline fns right after first user; generic class-template member definitions are instantiated after the vtable in CLASS DECLARATION order, weak, not inlined
fix: Make the class a primary template; define trailing functions as template<Kind K> members, declare in original .text order; others as template<> specializations. Remove override declarations without definitions (template vtable references all). Try this for ModelMisc/ModelManager and the GetWorldMtx order in ModelG3D
