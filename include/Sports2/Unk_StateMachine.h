#ifndef SPORTS2_UNK_STATE_MACHINE_H
#define SPORTS2_UNK_STATE_MACHINE_H

// Resort's shared state machine (placeholder names: no RTTI, strings or Wii Sports counterpart).
// Base: non-inline members at 0x803456D0-0x80345820 (Sports2/Unk_803456D0.cpp), vtable 0x806CCDF0
// {0, 0, dtor}; its inline virtual dtor is linked once, at 0x801ED018 (first user in link order).
// Unk_StateMachine<T>: one weak instantiation per owner class T (ctor, setState x2, calc,
// callEnter/callExec/callExit, deleting dtor; 3-word vtable {0, 0, dtor}).
// State tables hold 12-byte pointers to member functions, allocated from mHeap.
// Member names describe the code; they are not recovered names.

#include <types.h>

namespace EGG {
class Heap;
}
void* operator new[](size_t size, EGG::Heap* pHeap, int align);

class Unk_StateMachineBase {
public:
    Unk_StateMachineBase(void* owner, s32 num, EGG::Heap* heap); // 0x803457F4
    virtual ~Unk_StateMachineBase() {}

    void checkState(s32 state);          // 0x803456D0 (empty)
    void advance();                      // 0x803456D4
    void tick();                         // 0x803456F8
    bool isState(s32 state) const;       // 0x80345718
    bool isStateOrNext(s32 state) const; // 0x8034574C
    bool requestIfIdle(s32 state);       // 0x80345780
    void request(s32 state);             // 0x803457B8
    void reset(s32 state);               // 0x803457CC

    s32 mCur;        // at 0x4
    s32 mPrev;       // at 0x8
    s32 mNext;       // at 0xC
    s32 mTimer;      // at 0x10
    bool mUnk14;     // at 0x14
    bool mChanging;  // at 0x15
    bool mCallExit;  // at 0x16
    s32 mNum;        // at 0x18
    EGG::Heap* mHeap; // at 0x1C
};

template <class T>
class Unk_StateMachine : public Unk_StateMachineBase {
public:
    typedef void (T::*StateFn)();

    Unk_StateMachine(T* owner, s32 num, EGG::Heap* heap);
    virtual ~Unk_StateMachine() {}

    void setState(const StateFn& enter, const StateFn& exec, s32 state);
    void setState(const StateFn& enter, const StateFn& exec, const StateFn& exit, s32 state);
    void calc();
    void callEnter();
    void callExec();
    void callExit();

    T* mOwner;        // at 0x20
    StateFn* mEnter;  // at 0x24
    StateFn* mExec;   // at 0x28
    StateFn* mExit;   // at 0x2C
};

template <class T>
Unk_StateMachine<T>::Unk_StateMachine(T* owner, s32 num, EGG::Heap* heap)
    : Unk_StateMachineBase(owner, num, heap), mOwner(owner) {
    mEnter = new (mHeap, 4) StateFn[mNum];
    mExec = new (mHeap, 4) StateFn[mNum];
    mExit = new (mHeap, 4) StateFn[mNum];
    for (int i = 0; i < mNum; i++) {
        mEnter[i] = NULL;
        mExec[i] = NULL;
        mExit[i] = NULL;
    }
    reset(0);
}

template <class T>
void Unk_StateMachine<T>::setState(const StateFn& enter, const StateFn& exec, s32 state) {
    checkState(state);
    mEnter[state] = enter;
    mExec[state] = exec;
}

template <class T>
void Unk_StateMachine<T>::setState(const StateFn& enter, const StateFn& exec, const StateFn& exit,
                                   s32 state) {
    setState(enter, exec, state);
    mExit[state] = exit;
}

template <class T>
void Unk_StateMachine<T>::calc() {
    if (mChanging) {
        if (mCallExit) {
            callExit();
        }
        advance();
        callEnter();
    }
    callExec();
    tick();
}

template <class T>
void Unk_StateMachine<T>::callEnter() {
    if (mEnter[mCur]) {
        (mOwner->*mEnter[mCur])();
    }
}

template <class T>
void Unk_StateMachine<T>::callExec() {
    if (mExec[mCur]) {
        (mOwner->*mExec[mCur])();
    }
}

template <class T>
void Unk_StateMachine<T>::callExit() {
    if (mExit[mCur]) {
        (mOwner->*mExit[mCur])();
    }
}

#endif
