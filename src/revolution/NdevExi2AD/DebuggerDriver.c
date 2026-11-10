#include <revolution/NdevExi2AD.h>
#include <revolution/OS.h>

// Explicitly initialised, in ascending .sbss order: the SDK object
// (NDEV/lib/NdevExi2A.a DebuggerDriver.o) lists these symbols in declaration
// order ahead of the handlers, which only initialised statics reproduce.
static OSInterruptHandler __DBMtrCallback = NULL;
static OSInterruptHandler __DBDbgCallback = NULL;
static u8 __DBEXIInputFlag = FALSE;
static u32 __DBRecvMail = 0;
static u32 __DBRecvDataSize = 0;

static u8 __DBReadUSB_CSR(void);
static void __DBWaitForSendMail(void);

static void __DBMtrHandler(s16 type, OSContext* ctx) {
    __DBEXIInputFlag = TRUE;

    if (__DBMtrCallback != NULL)
        __DBMtrCallback(0, ctx);
}

static void __DBIntrHandler(s16 type, OSContext* ctx) {
    PI_HW_REGS[PI_INTSR] = PI_INTSR_DEBUG;
    if (__DBDbgCallback != NULL)
        __DBDbgCallback(type, ctx);
}

static void __DBCheckMailBox(void) {
    u8 csr = __DBReadUSB_CSR();
    if (!(csr & 0x8)) {
        u32 mail;
        __DBReadMailbox(&mail);
        if (ODEMUIsValidMail(mail)) {
            __DBRecvMail = mail;
            __DBRecvDataSize = ODEMUGetSize(mail);
            __DBEXIInputFlag = TRUE;
        }
    }
}

static u8 __DBReadUSB_CSR(void) {
    u8 val;
    __DBEXIReadReg(0x34000000, &val, sizeof(val));
    return val;
}

void DBInitComm(u8** flagOut, OSInterruptHandler handler) {
    BOOL enabled = OSDisableInterrupts();

    *flagOut = &__DBEXIInputFlag;
    __DBMtrCallback = handler;
    __DBEXIInit();

    OSRestoreInterrupts(enabled);
}

// Matches only with GC/3.0a3 (the SDK object's .comment is version 14) and the
// SDK prototype __OSSetInterruptHandler(__OSInterrupt = s16, ...). With
// GC/3.0a5.2 or an int/enum parameter, the handler lands in r5 and li r3, 0x19
// is hoisted above the store.
void DBInitInterrupts(void) {
    __OSMaskInterrupts(OS_INTR_MASK(OS_INTR_EXI_2_EXI) | OS_INTR_MASK(OS_INTR_EXI_2_TC));
    __OSMaskInterrupts(OS_INTR_MASK(OS_INTR_PI_DEBUG));
    __DBDbgCallback = __DBMtrHandler;
    __OSSetInterruptHandler(OS_INTR_PI_DEBUG, __DBIntrHandler);
    __OSUnmaskInterrupts(OS_INTR_MASK(OS_INTR_PI_DEBUG));
}

u32 DBQueryData(void) {
    __DBEXIInputFlag = FALSE;

    if (__DBRecvDataSize == 0) {
        BOOL enabled = OSDisableInterrupts();
        __DBCheckMailBox();
        OSRestoreInterrupts(enabled);
    }

    return __DBRecvDataSize;
}

BOOL DBRead(void* dst, u32 size) {
    BOOL enabled = OSDisableInterrupts();

    __DBRead(ODEMUGetPc2NngcOffset(__DBRecvMail) + 0x1000, dst,
             ROUND_UP(size, 4));
    __DBRecvDataSize = 0;
    __DBEXIInputFlag = FALSE;

    OSRestoreInterrupts(enabled);

    return FALSE;
}

BOOL DBWrite(const void* src, u32 size) {
    static u8 l_byOffsetCounter = 128;

    BOOL enabled = OSDisableInterrupts();

    u32 ofs, mail;

    __DBWaitForSendMail();

    ofs = 0;
    if (!(++l_byOffsetCounter & 0x1)) {
        ofs = 0;
    } else {
        ofs = 0x800;
    }

    while (__DBWrite(ofs, src, ROUND_UP(size, 4)) == 0) {
    }

    __DBWaitForSendMail();

    mail = ODEMUGenMailData(l_byOffsetCounter, size);
    while (__DBWriteMailbox(mail) == 0) {
    }

    __DBWaitForSendMail();

    OSRestoreInterrupts(enabled);

    return FALSE;
}

static void __DBWaitForSendMail(void) {
    while (__DBReadUSB_CSR() & 0x4) {
    }
}

void DBOpen(void) {}

void DBClose(void) {}
