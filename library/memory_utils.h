// by andrew.la

#ifndef LIBRARY_MEMORY_UTILS_H
#define LIBRARY_MEMORY_UTILS_H

#include "utils.h"
#include <stdlib.h>

#define KILOBYTES(n) ((usize) (1024 * (n)))
#define MEGABYTES(n) ((usize) (1024 * 1024 * (n)))
#define GIGABYTES(n) ((usize) (1024 * 1024 * 1024 (n)))

void* safe_alloc(usize size);
void* safe_realloc(void* ptr, usize size);

#endif
