# int->float temp register: assign to s16 local before setter

- status: works
- tags: mwcc,regalloc,scheduling,s16
- scope: RPGolDrawManager

symptom: fn_80294184 xoris r3 vs r0, q load scheduled early (96%)
cause: conversion order of float->s16 expression
fix: s16 x = a.x - (f32)(w / 2); setter(x, q); position setters as inline (s16 x, u8* q){flags|=1; pos=x;}
