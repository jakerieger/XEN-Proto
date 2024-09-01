// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "ArenaAllocator.h"
void* ArenaAllocator::Allocate(size_t size, size_t alignment) {
    const size_t currentOffset = mOffset;
    size_t adjustment          = alignment - (currentOffset % alignment);
    if (adjustment == alignment) {
        adjustment = 0;
    }

    const size_t alignedOffset = currentOffset + adjustment;
    if (alignedOffset + size > mSize) {
        std::cerr << "[ArenaAllocator::Allocate] Ran out of memory for allocation. Try "
                     "resizing the allocated block\n";
        return None;  // Not enough space
    }

    mOffset = alignedOffset + size;
    return mMemory + alignedOffset;
}