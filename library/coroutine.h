// by andrew.la

#ifndef LIBRARY_COROUTINE_H
#define LIBRARY_COROUTINE_H

#include "utils.h"
#include "memory_utils.h"

void coop_add_task(void (*entry) (void*), void* args);
void coop_sleep();
void coop_join();

#endif
