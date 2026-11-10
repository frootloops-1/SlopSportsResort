# Vtable via template static member + split boundary moves jumptable base

- status: works
- tags: vtable,template,splits,data-order,rpbsb
- scope: RPBsb_8027a3c4
- source: claude/rpbsb-3

symptom: Manual extern vtable arrays are emitted before jumptables/PMF constants; fn using jumptable base shows ...data.0 +0x50 vs jumptable+0x28
cause: CW uses the TU .data section start as base register; a leading 0x28-byte vtable belonging to the previous TU sat first. Arrays defined at parse time emit early.
fix: Define vtables as template<int N> struct V{static void* tbl[N];} static members (emitted after first user fn; order = template declaration order); move the leading bytes to the previous unit in splits.txt and keep symbol extern. Also define adjacent small fns in descending address order.
