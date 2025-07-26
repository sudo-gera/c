#include <atomic>
#include <tuple>
#include <thread>
#include <cassert>
#include <iostream>
#include <cassert>
#include <csetjmp>

template<typename T>
struct CAS{
    std::atomic<T>& a;
    std::array<T, 2> values;
    std::jmp_buf buf;
    CAS(std::atomic<T>& a, T val):a(a){
        values[0] = val;
    }
    auto operator=(T val){
        values[1] = val;
        if (a.compare_exchange_strong(values[0], values[1])){
            return values[0];
        }
        longjmp(buf, 2);
        return values[0];
    }
    operator T(){
        return values[0];
    }
};

template<typename T>
std::pair<bool, T> cas(std::atomic<T>& a, T if_equals, T set){
    // return {a.compare_exchange_strong(if_equals, set), if_equals};
    T real_value;
    CAS c(a, if_equals);
    if (setjmp(c.buf) != 2){
        c = set;
        real_value = c;
        return {true, real_value};
    }else{
        real_value = c;
        return {false, real_value};
    }
}

template<typename T>
void fetch_add(std::atomic<T>& a, T v){
    auto old_value = a.load();
    while (1){
        auto new_value = old_value + v;
        auto res = cas(a, old_value, new_value);
        old_value = res.second;
        if (res.first){
            break;
        }
    }
}

int main(){
    std::atomic<size_t> counter1 = 0;
    std::atomic<size_t> counter2 = 0;
    // size_t counter = 0;
    size_t iterations = 0;
    std::cin >> iterations;
    assert(iterations % 2 == 0);
    std::vector<std::thread> threads(64);
    for (auto& thread: threads){
        thread = std::thread([&, thread_num = &thread - &threads[0]](){
            auto c1 = &counter1;
            auto c2 = &counter2;
            for (size_t q = 0; q < iterations ; ++q){
                if (q){
                    std::swap(c1, c2);
                }
                fetch_add(*c1, thread_num + size_t(1));
                fetch_add(*c2, threads.size() - thread_num);
            }
        });
    }
    for (auto& thread: threads){
        thread.join();
    }
    std::cout << counter1 << std::endl;
    std::cout << counter2 << std::endl;
    assert(counter1 == 2080 * iterations);
    assert(counter2 == 2080 * iterations);
}

