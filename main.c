#include "library/coroutine.h"
#include <stdio.h>

void sleep_sort(void* arg) {
    u32 depth = LO_DWORD((size_t) arg);
    u32 number = HI_DWORD((size_t) arg);

    if (depth < number) {
        coop_sleep();
        sleep_sort((void*) CREATE_QWORD(depth - 1, number));        
    }

    printf("%d ", number);
}

int main(void) {
    coop_add_task(sleep_sort, (void*) CREATE_QWORD(5, 5));
    coop_add_task(sleep_sort, (void*) CREATE_QWORD(2, 2));
    coop_add_task(sleep_sort, (void*) CREATE_QWORD(6, 6));
    coop_add_task(sleep_sort, (void*) CREATE_QWORD(1, 1));
    coop_add_task(sleep_sort, (void*) CREATE_QWORD(3, 3));

    coop_join();
    return 0;
}
