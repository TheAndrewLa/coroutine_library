#pragma once
#include <cassert>

template <typename T>
struct Singleton {
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static T* const get() {
        static T* instance;

        if (instance == nullptr) {
            instance = new T;
        }

        return instance;
    }
};
