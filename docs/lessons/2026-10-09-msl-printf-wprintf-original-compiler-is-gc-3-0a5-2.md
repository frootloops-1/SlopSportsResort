# MSL printf/wprintf original compiler is GC/3.0a5.2

- status: works
- tags: msl,compiler,printf
- scope: MSL_C printf (check wprintf, others)
- source: claude/msl-text printf 2026-10-09

symptom: print_format struct copies use lfd/stfd, original uses lwz/stw; __pformatter stuck near 90%
cause: original built with GC/3.0a5.2; 3.0a3-3.0a5 copy 16-byte structs with lfd/stfd
fix: Object(..., mw_version='GC/3.0a5.2', cflags=cflags_msl_ss, extra_cflags=['-Cpp_exceptions on']); then delete the is_secure local (a5.2 emits it to .sdata2) and remove gap_* alignment symbols from symbols.txt. Also: old double2hex (fabsl==0 -> 0x0p0 at buff-6, I/N if-chain), float2str dec.exp += length-1, 'if((p=f())!=0) goto ok; goto err;' shape
