# Golf camera manager ctor/dtor/vtable shapes (RPGolCameraManager)

- status: works
- tags: RPGolCameraManager,vtable,ctor,virtual

symptom: virtual call at slot 0x8 came out 0x10 with dummy virtuals; ctor-like helper return unused
cause: local class first declared virtual is slot 0x8; helper returning ptr stored after bl needs void*(void*) signature
fix: manual extern C void*[3]={0,0,fn} vtables in descending order, lbl_803C77D0 before 77DC; nested if(self) dtors; __nw__FUl(sz); if(o) o=ctor(o)
