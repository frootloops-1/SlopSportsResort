# float->u16->float args via named u16 locals in fctiwz order

- status: works
- tags: mwcc,casts,args
- scope: RPGol_802b614c
- source: sonnet-worker

symptom: f32 locals or inline casts 13-81%
cause: conversion order follows locals
fix: u16 h1 = a->fC; u16 h0 = a->f8; declared in the fctiwz load order
