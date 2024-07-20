// by andrew.la

#include "coroutine.h"

#include <assert.h>
#include <setjmp.h>

// Make it thread-safe

// #include <pthread.h>
// #include <stdatomic.h>

#define COROUTINE_STACK_SIZE KILOBYTES(4)
#define QUEUE_CAPACITY (16)

typedef struct _taskObject task_object;
typedef struct _taskQueue task_queue;

struct _taskObject {
    struct {
        void (*entry) (void*);
        void* args;
    } function;

    jmp_buf env;
    u8* stack;
};

struct _taskQueue {
    task_object* tasks;
    usize number;
    usize capacity;
};

static task_queue g_task_queue;
static bool32 g_initialized = FALSE;
static bool32 g_running = FALSE;

static void queue_ctor(task_queue* const queue) {
    assert(queue != NULL);
    queue->number = 0;
    queue->capacity = QUEUE_CAPACITY;
    queue->tasks = safe_alloc(sizeof(task_object) * QUEUE_CAPACITY);
}

static void queue_dtor(task_queue* const queue) {
    assert(queue != NULL);

    for (usize i = 0; i < queue->number; i++)
        free(queue->tasks[i].stack);

    free(queue->tasks);
}

static task_object* queue_peek(const task_queue* const queue) {
    assert(queue != NULL);

    usize index = queue->number - 1;
    return &queue->tasks[index];
}

static task_object* queue_pop(task_queue* const queue) {
    assert(queue != NULL);

    usize index = queue->number - 1;
    queue->number--;

    return &queue->tasks[index];
}

static task_object* queue_get_place(task_queue* const queue) {
    assert(queue != NULL);

    if (queue->number == queue->capacity) {
        queue->tasks = safe_realloc(queue->tasks, queue->capacity * 2);
        queue->capacity *= 2;
    }

    return &queue->tasks[queue->number];
}

static void queue_push(task_queue* const queue, const task_object* const object) {
    task_object* new_task = queue_get_place(queue);
    new_task->function.entry = object->function.entry;
    new_task->function.args = object->function.args;
    new_task->stack = object->stack;

    queue->number++;
}

static void queue_emplace(task_queue* const queue, void (*entry) (void*), void* args) {
    task_object* new_task = queue_get_place(queue);
    new_task->function.entry = entry;
    new_task->function.args = args;
    new_task->stack = safe_alloc(COROUTINE_STACK_SIZE);

    queue->number++;
}

static inline bool32 queue_is_empty(const task_queue* const queue) {
    assert(queue != NULL);
    return queue->number == 0;
}

static void coroutines_exit(void) {
    if (!g_initialized)
        return;

    queue_dtor(&g_task_queue);
}

// COROUTINE STUFF
/// @todo: make it thread-safe (set-up mutexes)
/// @todo: create my own tests for that stuff

void coop_add_task(void (*entry) (void*), void* args) {
    if (!g_initialized) {
        queue_ctor(&g_task_queue);

        assert(atexit(coroutines_exit) == 0);
        g_initialized = TRUE;
    }

    if (g_running == TRUE)
        return;

    queue_emplace(&g_task_queue, entry, args);
}

void coop_sleep(void) {
    if (!g_running)
        return;

    task_object* active_task = queue_peek(&g_task_queue);
    longjmp(active_task->env, 1);
}

void coop_join(void) {
    assert(g_initialized);

    g_running = TRUE;

    while (!queue_is_empty(&g_task_queue)) {
        task_object* task = queue_peek(&g_task_queue);

        if (setjmp(task->env) > 0) {
            queue_push(&g_task_queue, task);
            continue;
        }

        __asm__ volatile (
            "movq %0, %%rdi\n"
            "movq %1, %%rsp\n"
            "movq %2, %%rax\n"
            "call *%%rax" :

            "=r" (task->function.args),
            "=r" (task->stack),
            "=r" (task->function.entry)
        );

        free(task->stack);
    }

    g_running = FALSE;
}
