// by andrew.la

#include "memory_utils.h"

void* safe_alloc(usize size) {
    void* ptr = malloc(size);
    if (ptr != NULL)
        return ptr;

    exit(1);
}

void* safe_realloc(void* ptr, usize size) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr != NULL)
        return ptr;

    exit(1);
}
