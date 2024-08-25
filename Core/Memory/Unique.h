// Author: Jake Rieger
// Created: 8/24/2024.
//

#pragma once

template<class T>
class Unique {
private:
    T* ptr;

public:
    explicit Unique(T* p = nullptr) : ptr(p) {}

    Unique(Unique<T>&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    ~Unique() {
        delete ptr;
    }

    Unique<T>& operator=(Unique<T>&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr       = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    Unique(const Unique<T>&)               = delete;
    Unique<T>& operator=(const Unique<T>&) = delete;

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T* Get() const {
        return ptr;
    }

    T* Release() {
        T* temp = ptr;
        ptr     = nullptr;
        return temp;
    }

    void Reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};
