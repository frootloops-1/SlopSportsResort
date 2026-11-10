// Swf_80602BD4: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>
#include <Pack/RPSystem/RPSysResourceManager.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_803286C0(u8*);
void fn_80328CCC(u8*);
void fn_80604530(u8*);
void fn_80604540(u8*);
extern void* lbl_806EBCE0[];



void fn_80603144(u8* p) { fn_803286C0(*(u8**)(p + 0x15c)); }

void fn_80603000(u8* p) { fn_80604540(*(u8**)(p + 0x174)); }

void fn_80602FE4(u8* p) { fn_80604530(*(u8**)(p + 0x174)); }


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;
extern char* lbl_806F38F4;
const char* fn_803251DC(char*);
void fn_805FC590(u8*);
void fn_80328CCC(u8*);

u8* fn_80604254(u8* p) {
    fn_80328CCC(p);
    *(void***)p = lbl_806EBCE0;
    *(void***)(p + 0x34) = lbl_806EBCE0 + 10;
    lbl_806F5FF0 = p;
    return p;
}

void fn_80604248() { lbl_806F5FF0 = 0; }

void fn_80603008() { fn_805FC590(*(u8**)(lbl_806F5FF0 + 0x170)); }

void fn_80602FEC(u8* p, s32 v) {
    if (v == 1) {
        *(s32*)(p + 0x1c0) = 1;
    }
}


void* fn_80602FDC(u8* p, const char* name, u32* size) {
    return RPSysResourceManager::GetFileFromArchive(*(EGG::Archive**)(p + 0x1b0), name, size);
}

void* fn_80602F98(u8* p, u8*, u32* size) {
    return RPSysResourceManager::GetFileFromArchive(*(EGG::Archive**)(p + 0x1b0), fn_803251DC(lbl_806F38F4), size);
}

void* fn_80602F90(u8* p, const char* name, u32* size) {
    return RPSysResourceManager::GetFileFromArchive(*(EGG::Archive**)(p + 0x1b4), name, size);
}

}  // extern "C"
