// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"

template<typename T>
class PoolAllocator {
public:
    explicit PoolAllocator(size_t size);
    ~PoolAllocator();

    T* Allocate();

    void Deallocate(T* p);

private:
    size_t mPoolSize;
    T* mpPool;
    Vector<T*> mFreeList;
};

template<typename T>
PoolAllocator<T>::PoolAllocator(size_t size) {
    mPoolSize = size;
    mpPool    = CAST<T*>(::operator new(size * sizeof(T)));
    for (size_t i = 0; i < size; ++i) {
        mFreeList.push_back(&mpPool[i]);
    }
}

template<typename T>
PoolAllocator<T>::~PoolAllocator() {
    ::operator delete(mpPool);
}

template<typename T>
T* PoolAllocator<T>::Allocate() {
    if (mFreeList.empty()) {
        throw std::bad_alloc();
    }

    T* obj = mFreeList.back();
    mFreeList.pop_back();
    return obj;
}

template<typename T>
void PoolAllocator<T>::Deallocate(T* p) {
    mFreeList.push_back(p);
}