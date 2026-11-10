# Function-local static array of VEC3-like struct: 0x200 .bss plus 1-byte @GUARD@ in .sbss, no init code

- status: works
- tags: bss,sbss,static,guard
- source: RPBsb_8026e62c

symptom: .bss 0x200 and .sbss 8 in split with no init code
cause: local static of struct whose member type has empty user ctor
fix: function-local 'static Entry entries[16]'; declare locals vmin,vmax,tmp,sum in that order for stack offsets; 'e++, i++' in loop tail
