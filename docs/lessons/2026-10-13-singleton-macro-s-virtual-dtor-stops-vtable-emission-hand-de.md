# Singleton macro's virtual dtor stops vtable emission; hand-declare

- status: works
- tags: vtable,singleton,key-function,controllermgr
- scope: Pack/RPKernel/RPSysControllerMgr

symptom: create 99.6%; U __vt__ in our .o
cause: RP_SINGLETON_DECL declares virtual ~T() undefined => key function elsewhere
fix: hand-write instance()/spInstance without virtual dtor when the original vtable has no dtor slot; loops as private member inlines; for-loop not do-while
