#ifndef EGG_CORE_ALLOCATOR_H
#define EGG_CORE_ALLOCATOR_H
#include <egg/types_egg.h>

#include <revolution/MEM.h>

namespace EGG {

// Forward declarations
class Heap;

class Allocator : public MEMAllocator {
public:
    Allocator(Heap* pHeap, s32 align = 32);
    virtual ~Allocator();

    virtual void* alloc(u32 size);
    virtual void free(void* pBlock);

private:
    // Resort: 0x1C bytes (ctor 0x801C1E28 stores both)
    Heap* mHeap;  // at 0x14
    s32 mAlign;   // at 0x18
};

} // namespace EGG

#endif
