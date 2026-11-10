# Switch with cases 1,2 only compares 2 first: add empty case 0; alloc loop needs real new-expression

- status: works
- tags: switch,new,regalloc
- source: RPBsb_80274ba8

symptom: 98.5%: switch tests 2 before 1; alloc loop 97.7-98.3 with manual __nw__FUl + null check
cause: compiler orders compares by case set; manual alloc changes reg assignment
fix: add empty 'case 0: break;' so compare 1 first; use 'self->child[i] = new T;' with local struct T:View whose inline ctor calls base ctor fn, plus 'void* operator new(size_t);'
