#include <type_traits>
#include <utility>
#include <cassert>

template <typename>
class function_ref; // Primary template

template <typename R, typename... Args>
class function_ref<R(Args...)> {
    void* callable_ = nullptr;
    R (*invoker_)(void*, Args&&...) = nullptr;

public:
    function_ref() = default;

    // Handle function pointers
    function_ref(R(*func)(Args...)) noexcept {
        callable_ = reinterpret_cast<void*>(func);
        invoker_ = [](void* ptr, Args&&... args) -> R {
            auto f = reinterpret_cast<R(*)(Args...)>(ptr);
            return f(std::forward<Args>(args)...);
        };
    }

    // Handle functors/lambdas (non-owning reference)
    template <typename Callable>
    function_ref(Callable& callable) noexcept {
        using T = std::remove_reference_t<Callable>;
        static_assert(std::is_invocable_r_v<R, T&, Args...>,
                      "Callable must be invocable with the correct signature");

        callable_ = static_cast<void*>(&callable);
        invoker_ = [](void* ptr, Args&&... args) -> R {
            return (*reinterpret_cast<T*>(ptr))(std::forward<Args>(args)...);
        };
    }

    function_ref(const function_ref&) = default;
    function_ref& operator=(const function_ref&) = default;

    R operator()(Args... args) const {
        assert(invoker_ && "function_ref is empty");
        return invoker_(callable_, std::forward<Args>(args)...);
    }

    explicit operator bool() const noexcept {
        return invoker_ != nullptr;
    }
};

#if __INCLUDE_LEVEL__ == 0
#include <iostream>

void call_twice(function_ref<void(int)> fn) {
    fn(1);
    fn(2);
}

void test(int x) {
    std::cout << "Free function: " << x << '\n';
}

int main() {
    auto lambda = [](int x) { std::cout << "Lambda: " << x << '\n'; };
    call_twice(lambda);    // Ok
    call_twice(test);      // Ok

    auto lambda_ = [](int x)mutable{ std::cout << "Lambda: " << x << '\n'; };
    call_twice(lambda_);    // Ok

    // Big object? Still works — we’re not copying it!
    struct Big {
        char data[1024];
        void operator()(int x) const { std::cout << "Big: " << x << '\n'; }
    } big;
    call_twice(big);       // Ok — passed by reference
}
#endif
