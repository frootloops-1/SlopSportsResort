# mem_expHeap RecycleRegion_ closes when MemRegion struct is used consistently (not just in RecycleRegion_)

- status: works
- tags: mem_expHeap,RecycleRegion_,struct-vs-array,stack-layout,regalloc
- source: branch claude/cp932-1028 in /private/tmp/ogws-cp932-1028

symptom: RecycleRegion_ r5/r6 load-order swap after ~40 variants; typed MemRegion only in RecycleRegion_ (callers still void*[2]) gave no change
cause: void* x[2] arrays vs struct MemRegion locals/params across the helpers (GetRegionOfMBlock_, InitMBlock_, InitFreeMBlock_) and every caller changes stack slot assignment/colouring; per-function typing is not enough
fix: Declare typedef struct MemRegion {void* start; void* end;} and use it for every region local, helper param and caller (region.start/.end, &region, const MemRegion* in RecycleRegion_). 11/11 exact, DOL 0. Lever: when one function of a family resists, convert the whole family's shared representation, not just that function. Also tried and useless: scheduling/peephole/opt_level pragmas, volatile reads, scalar locals, inline-expanded InitFree, field-order swap (semantic hack).
