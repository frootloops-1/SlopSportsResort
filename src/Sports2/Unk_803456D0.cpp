// Unk_803456D0: base class of Resort's shared state machine, 0x803456D0-0x80345820 (Resort-only).
// The template that derives from it (one weak copy per owner class) is in Sports2/Unk_StateMachine.h.
// File boundary: its vtable 0x806CCDF0 is padded to 8 bytes on both sides (one .data object per file).
// Its inline virtual dtor is linked once, at 0x801ED018 (first user in link order).

#include <Sports2/Unk_StateMachine.h>
#include <egg/core/eggHeap.h>

Unk_StateMachineBase::Unk_StateMachineBase(void*, s32 num, EGG::Heap* heap) {
    mNum = num;
    if (heap != NULL) {
        mHeap = heap;
    } else {
        mHeap = EGG::Heap::getCurrentHeap();
    }
}

void Unk_StateMachineBase::reset(s32 state) {
    mPrev = state;
    mCur = state;
    mNext = state;
    mChanging = true;
    mCallExit = false;
    mTimer = 0;
    mUnk14 = false;
}

void Unk_StateMachineBase::request(s32 state) {
    mNext = state;
    mChanging = true;
    mCallExit = true;
}

bool Unk_StateMachineBase::requestIfIdle(s32 state) {
    if (!mChanging) {
        request(state);
        return true;
    }
    return false;
}

bool Unk_StateMachineBase::isStateOrNext(s32 state) const {
    bool ret = false;
    if (state == mCur || (state == mNext && mChanging)) {
        ret = true;
    }
    return ret;
}

bool Unk_StateMachineBase::isState(s32 state) const {
    bool ret = false;
    if (state == mCur && (state == mNext || !mChanging)) {
        ret = true;
    }
    return ret;
}

void Unk_StateMachineBase::tick() {
    if (mTimer < 0x7FFFFFFF) {
        mTimer++;
    }
}

void Unk_StateMachineBase::advance() {
    mPrev = mCur;
    mCur = mNext;
    mChanging = false;
    mTimer = 0;
    mUnk14 = false;
}

void Unk_StateMachineBase::checkState(s32) {}
