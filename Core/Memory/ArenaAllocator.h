// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"

#include <iostream>

class ArenaAllocator {
public:
    explicit ArenaAllocator(size_t size) : mSize(size), mOffset(0) {
        mMemory = new char[mSize];
    }

    ~ArenaAllocator() {
        delete[] mMemory;
    }

    void* Allocate(size_t size, size_t alignment = alignof(std::max_align_t));

    void Reset() {
        mOffset = 0;
    }

private:
    char* mMemory;
    size_t mSize;
    size_t mOffset;
};
