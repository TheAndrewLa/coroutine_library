#pragma once

#include <queue>
#include <tuple>

#include "singleton.h"

template <typename... Args>
struct CoroutineManager : Singleton<CoroutineManager<Args...>> {
    using function_type = std::function<void(Args...)>;

    template <typename... Ts>
    void add_task(function_type function, Ts&&... args) {
        functions_.push(function);
        args_.emplace(std::forward<Ts>(args)...);
    }

    void sleep() {
        // Magic with asm & setjmp & longjmp
    }

    void execute() {
        // Magic with asm & setjmp & longjmp
    }

    private:
    std::queue<function_type> functions_;
    std::queue<std::tuple<Args...>> args_;
};
