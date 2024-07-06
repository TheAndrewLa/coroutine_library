// by andrew.la

#ifndef LIBRARY_COROUTINE_H
#define LIBRARY_COROUTINE_H

#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>

typedef struct __coroutine_manager {
    // task queue
} coroutine_manager;

typedef struct __coroutine_function {
    void (*entry) (void*);
    void* args;
} coroutine_function;

#endif
