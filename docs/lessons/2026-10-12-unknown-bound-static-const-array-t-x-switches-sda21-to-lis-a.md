# Unknown-bound static const array (T X[];) switches sda21 to lis/addi; direct index in inline keeps bytes in saved regs

- status: works
- tags: sda21,static,const,array,inline,regalloc,VFILTER_BLUR,ternary,by-value,RPGrpView
- scope: RPGrpView

symptom: Draw 93.5%: VFILTER_BLUR addressed via sda21 vs orig lis/addi; reload at second inline use; ClearBuffer colour copy after helper
cause: Header declared known bound; setVFilterBlur went through a const u8* parameter; if/return helper hoisted before args
fix: static const u8 VFILTER_BLUR[]; loop VFILTER_BLUR[i] directly in the inline; missing PostEffectBlurSimple field stores after configure(); GetEnableScreen as ternary 'a ? a : b' so colour copy comes first
