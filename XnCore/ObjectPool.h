// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include "Shared/Types.h"
#include "XnCore/Memory/PoolAllocator.h"
#include "XnCore/SceneContext.h"

template<typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t capacity);
    ~ObjectPool();

    template<typename... Args>
    void Spawn(const Shared<SceneContext>& context, Args&&... args);

    void Drain();

private:
    Unique<PoolAllocator<T>> mPool;
};

template<typename T>
ObjectPool<T>::ObjectPool(const size_t capacity) {
    mPool = std::make_unique<PoolAllocator<T>>(capacity);
}

template<typename T>
ObjectPool<T>::~ObjectPool() {


    mPool.reset();
}

template<typename T>
template<typename... Args>
void ObjectPool<T>::Spawn(const Shared<SceneContext>& context, Args&&... args) {
    // Request a block of memory from our memory pool
    auto ptr = mPool->Allocate();
    // Create the game object with our newly allocated memory chunk
    new (ptr) T(std::forward<Args>(args)...);
    // Create a shared ptr of our game object with a custom deleter
    // for removing the memory from the pool
    auto shared = std::shared_ptr<T>(ptr, [this, context](T* p) {
        p->Destroyed(context);
        p->~T();  // Manually call the destructor
        mPool->Deallocate(p);
    });

    context->GameObjects[(ptr)->GetName()] = shared;
    ptr->Awake(context);
}

template<typename T>
void ObjectPool<T>::Drain() {}
