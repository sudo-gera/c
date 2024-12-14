#include <set>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <tuple>
#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <concepts>
#include <deque>
#include <vector>
#include <optional>
#include <unordered_map>
#include <variant>
#include <iomanip>
#include <functional>
#include <list>
#include <thread>
#include <algorithm>
#include <limits>
#include <limits.h>
#include <chrono>
#include <random>
#include <new>

#if __cplusplus < 202000L
#error "need c++20"
#endif

inline constexpr std::size_t hardware_destructive_interference_size = 128;

using std::operator""s;

#define FORWARD(arg) std::forward<decltype(arg)>(arg)
#define THROW_ON_ERRNO(expr, ...) (([&](){ errno = 0 ; auto res__ = (expr) ; if (errno) { throw std::runtime_error{std::string() + "ERROR: " + #expr + ": " + strerror(errno) + " "s + quoted_all(__VA_ARGS__)} ; } ; return res__ ; })())
#define CATCH(e) catch(std::exception& e)

namespace thread_safe_time{
    const auto && clock = std::chrono::high_resolution_clock::now;
    using duration_t = decltype([](){
        auto time_point = std::chrono::high_resolution_clock::now();
        auto duration = time_point - time_point;
        return duration;
    }());
    auto clock_from_diff(duration_t duration){
        return duration.count() * duration_t::period::num;
    }
    using clock_t = decltype(clock_from_diff(duration_t()));
    constexpr clock_t clocks_per_sec = duration_t::period::den;
};

template<typename crit_sec>
concept CriticalSection = requires(crit_sec b){b.critical_section();};

template<typename Lock, typename time, CriticalSection cs>
struct lock_test{
    struct {
        Lock m_;
        void lock(){m_.lock();}
        void unlock(){m_.unlock();}
    } lock;
    std::mutex m;
    std::vector<thread_safe_time::clock_t> waits;
    size_t tsan_would_check_that_mutex_works = 0;
    cs c;
    size_t thread_count = 0;
    struct alignas(hardware_destructive_interference_size) thread_locals{
        std::thread thread;
        decltype(waits) local_waits;
    };
    lock_test(size_t thread_count_){
        thread_count = thread_count_;
        std::vector<thread_locals> threads(thread_count);
        for (auto& thread: threads){
            thread.local_waits.reserve(4'000'000 * time::num / time::den);
            thread.thread = std::thread([&](){worker(thread.local_waits);});
        }
        for (auto& thread: threads){
            thread.thread.join();
        }
        for (auto& thread: threads){
            std::copy(
                thread.local_waits.begin(),
                thread.local_waits.end(),
                std::back_inserter(waits)
            );
        }
    }
    void worker(auto& local_waits){
        auto program_start = thread_safe_time::clock();
        while (1){
            auto start_waiting = thread_safe_time::clock();
            decltype(start_waiting) stop_waiting;
            {
                std::unique_lock ul(lock);
                stop_waiting = thread_safe_time::clock();
                ++tsan_would_check_that_mutex_works;
                c.critical_section();
            }
            local_waits.push_back(
                thread_safe_time::clock_from_diff(
                    stop_waiting - start_waiting
                )
            );
            if (
                thread_safe_time::clock_from_diff(
                    stop_waiting - program_start
                ) * time::den
                > thread_safe_time::clocks_per_sec
                * time::num
            ){
                break;
            }
        }
        auto program_stop = thread_safe_time::clock();
        // std::cerr << (program_stop - program_start) << std::endl;
        // std::cerr << thread_safe_time::clock_from_diff(program_stop - program_start) << std::endl;
        // std::cerr << local_waits.size() << std::endl;
        // {
        //     std::unique_lock ul(m);
        //     waits.reserve(waits.size() + local_waits.size());
        //     std::copy(
        //         local_waits.begin(),
        //         local_waits.end(),
        //         std::back_inserter(waits)
        //     );
        // }
    }
    clock_t avg_wait_time(){
        return waits.empty() ? 0 : std::reduce(
            waits.begin(),
            waits.end(),
            typename decltype(waits)::value_type(0),
            [](auto left, auto right){return left + right;}
        ) / waits.size();
    }
    clock_t max_wait_time(){
        return waits.empty() ? 0 : std::reduce(
            waits.begin(),
            waits.end(),
            typename decltype(waits)::value_type(0),
            [](auto left, auto right){return std::max(left, right);}
        );
    }
};

consteval auto thread_counts_vector(){
    std::vector<size_t> thread_counts(64);
    for (size_t i = 0; i < thread_counts.size() ; ++i){
        // thread_counts[i] = (i % 16) * (1LLU << i / 16) + 1;
        thread_counts[i] = i + 1;
        // thread_counts[i] = 1;
    }
    std::sort(thread_counts.begin(), thread_counts.end());
    // thread_counts.resize(
    //         std::unique(
    //             thread_counts.begin(),
    //             thread_counts.end()
    //         ) - thread_counts.begin()
    //     );
    return thread_counts;
}

consteval size_t thread_counts_size(){
    return thread_counts_vector().size();
}

constexpr auto thread_counts = []()consteval{
    std::array<size_t, thread_counts_size()> res_a;
    auto res_v = thread_counts_vector();
    std::copy(res_v.begin(), res_v.end(), res_a.begin());
    return res_a;
}();

struct record_type{
    size_t thread_count;
    clock_t avg_wait_time;
    clock_t max_wait_time;
};

template<CriticalSection cs, typename Lock, typename time = std::ratio<1, 10>>
void run_test_for_lock(std::function<void(record_type)> on_result){
    for (auto thread_count: thread_counts){
        lock_test<Lock, time, cs> t(thread_count);
        on_result({
            thread_count,
            t.avg_wait_time(),
            t.max_wait_time(),
        });
    }
}

template<typename T, bool check=true>
struct CAS{
    std::atomic<T>& a;
    CAS(std::atomic<T>& a):a(a){}
    std::conditional_t<check, std::optional<T>, T> if_equals_to;
    std::conditional_t<check, std::optional<T>, T> then_assign;
    std::conditional_t<check, std::optional<T>, T> actual_value;
    std::conditional_t<check, std::optional<std::memory_order>, std::memory_order> success;
    std::conditional_t<check, std::optional<std::memory_order>, std::memory_order> failure;
    std::conditional_t<check, std::optional<bool>, bool> may_fail;
    bool operator()(){
        if constexpr(check){
            assert(if_equals_to.has_value());
            assert(then_assign.has_value());
            assert(success.has_value());
            assert(failure.has_value());
            assert(may_fail.has_value());
        }
        actual_value = if_equals_to;
        bool result;
        if constexpr(check){
            if (may_fail.value()){
                result = a.compare_exchange_weak(
                    actual_value.value(),
                    then_assign.value(),
                    success.value(),
                    failure.value()
                );
            }else{
                result = a.compare_exchange_strong(
                    actual_value.value(),
                    then_assign.value(),
                    success.value(),
                    failure.value()
                );
            }
        }else{
            if (may_fail){
                result = a.compare_exchange_weak(
                    actual_value,
                    then_assign,
                    success,
                    failure
                );
            }else{
                result = a.compare_exchange_strong(
                    actual_value,
                    then_assign,
                    success,
                    failure
                );
            }
        }
        return result;
    }
    void reset(){
        if constexpr(check){
            actual_value.reset();
            if_equals_to.reset();
            then_assign.reset();
            success.reset();
            failure.reset();
            may_fail.reset();
        }
    }
    operator T(){
        if constexpr(check){
            return actual_value.value();
        }else{
            return actual_value;
        }
    }
};

template<typename backoff>
concept Backoff = requires(backoff b){b.yield();};

template<Backoff backoff>
struct TAS{
    std::atomic<bool> is_locked;
    void lock(){
        backoff b;
        while (true){
            CAS cas(is_locked);
            cas.if_equals_to = false;
            cas.then_assign = true;
            cas.may_fail = true;
            cas.success = std::memory_order::relaxed;
            cas.failure = std::memory_order::relaxed;
            if (cas()){
                is_locked.load(std::memory_order::acquire);
                break;
            }
            b.yield();
        }
    }
    void unlock(){
        is_locked.store(false, std::memory_order::release);
    }
};

template<Backoff backoff>
struct TTAS{
    std::atomic<bool> is_locked;
    void lock(){
        backoff b;
        while (true){
            while ((is_locked.load(std::memory_order::relaxed) == true))[[likely]]{
                b.yield();
            }
            CAS cas(is_locked);
            cas.if_equals_to = false;
            cas.then_assign = true;
            cas.may_fail = true;
            cas.success = std::memory_order::acq_rel;
            cas.failure = std::memory_order::relaxed;
            if ((cas())){
                break;
            }
        }
    }
    void unlock(){
        is_locked.store(false, std::memory_order::release);
    }
};

template<Backoff backoff>
struct TicketLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        backoff b;
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::relaxed);
        while ((owner_ticket.load(std::memory_order::relaxed) != my_ticket))[[likely]]{
            b.yield();
        }
        owner_ticket.load(std::memory_order::acquire);
    }
    void unlock(){
        auto next_owner = owner_ticket.load(std::memory_order::relaxed) + 1;
        owner_ticket.store(next_owner, std::memory_order::release);
    }
};

template<Backoff backoff>
struct TicketWaitLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        backoff b;
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::relaxed);
        size_t owner_ticket_value = 0;
        while (((owner_ticket_value = owner_ticket.load(std::memory_order::relaxed)) != my_ticket))[[likely]]{
            owner_ticket.wait(owner_ticket_value, std::memory_order::relaxed);
        }
        owner_ticket.load(std::memory_order::acquire);
    }
    void unlock(){
        auto next_owner = owner_ticket.load(std::memory_order::relaxed) + 1;
        owner_ticket.store(next_owner, std::memory_order::release);
        owner_ticket.notify_one();
    }
};

template<Backoff backoff>
struct FTicketWaitLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        backoff b;
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::relaxed);
        size_t owner_ticket_value = 0;
        while (((owner_ticket_value = owner_ticket.load(std::memory_order::relaxed)) != my_ticket)){
            owner_ticket.wait(owner_ticket_value, std::memory_order::relaxed);
        }
        owner_ticket.load(std::memory_order::acquire);
    }
    void unlock(){
        owner_ticket.fetch_add(1, std::memory_order::release);
        owner_ticket.notify_one();
    }
};

template<Backoff backoff>
struct FTicketLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::relaxed);
        backoff b;
        while ((owner_ticket.load(std::memory_order::relaxed) != my_ticket))[[likely]]{
            b.yield();
        }
        owner_ticket.load(std::memory_order::acquire);
    }
    void unlock(){
        owner_ticket.fetch_add(1, std::memory_order::release);
    }
};

template<Backoff backoff>
struct QueueLock{
    struct queue_item{
        std::atomic<queue_item*> comes_after_me = nullptr;
        std::atomic<bool> is_owner = false;
    };
    std::atomic<queue_item*> last_added_to_queue = nullptr;
    queue_item* owner = nullptr;
    void lock(){
        backoff b;
        auto item = new queue_item;
        auto prev_item = last_added_to_queue.exchange(item, std::memory_order::acq_rel);
        if (prev_item != nullptr){
            prev_item->comes_after_me.store(item, std::memory_order::relaxed);
            while ((not item->is_owner.load(std::memory_order::relaxed)))[[likely]]{
                b.yield();
            }
            item->is_owner.load(std::memory_order::acquire);
        }
        owner = item;
    }
    void unlock(){
        backoff b;
        queue_item* item = owner;
        owner = nullptr;
        CAS last_added_to_queue_cas(last_added_to_queue);
        last_added_to_queue_cas.if_equals_to = item;
        last_added_to_queue_cas.then_assign = nullptr;
        last_added_to_queue_cas.may_fail = false;
        last_added_to_queue_cas.success = std::memory_order::release;
        last_added_to_queue_cas.failure = std::memory_order::acquire;
        if (not last_added_to_queue_cas()){
            queue_item* next_item = nullptr;
            while ((next_item = item->comes_after_me.load(std::memory_order::relaxed)) == nullptr)[[likely]]{
                b.yield();
            }
            next_item->is_owner.store(true, std::memory_order::release);
        }
        delete item;
    }
};

template<Backoff backoff>
struct ArrayLock{
    struct queue_item{
        std::atomic<queue_item*> comes_after_me = nullptr;
        std::atomic<bool> is_owner = false;
        std::atomic<bool> used = false;
    };
    std::array<queue_item, thread_counts.back()> items;
    std::atomic<queue_item*> last_added_to_queue = nullptr;
    std::atomic<size_t> item_to_get = 0;
    queue_item* owner = nullptr;
    void lock(){
        backoff b;
        queue_item* item = nullptr;
        while (true){
            item = items.data() + item_to_get.fetch_add(1, std::memory_order::relaxed) % items.size();
            CAS item_cas(item->used);
            item_cas.if_equals_to = false;
            item_cas.then_assign = true;
            item_cas.may_fail = false;
            item_cas.success = std::memory_order::relaxed;
            item_cas.failure = std::memory_order::relaxed;
            if ((item_cas()))[[likely]]{
                break;
            }
        }
        item->comes_after_me.store(nullptr, std::memory_order::relaxed);
        item->is_owner.store(false, std::memory_order::relaxed);
        auto prev_item = last_added_to_queue.exchange(item, std::memory_order::acq_rel);
        if (prev_item != nullptr){
            prev_item->comes_after_me.store(item, std::memory_order::relaxed);
            while ((not item->is_owner.load(std::memory_order::relaxed)))[[likely]]{
                b.yield();
            }
            item->is_owner.load(std::memory_order::acquire);
        }
        owner = item;
    }
    void unlock(){
        backoff b;
        queue_item* item = owner;
        owner = nullptr;
        CAS last_added_to_queue_cas(last_added_to_queue);
        last_added_to_queue_cas.if_equals_to = item;
        last_added_to_queue_cas.then_assign = nullptr;
        last_added_to_queue_cas.may_fail = false;
        last_added_to_queue_cas.success = std::memory_order::release;
        last_added_to_queue_cas.failure = std::memory_order::acquire;
        if (not last_added_to_queue_cas()){
            queue_item* next_item = nullptr;
            while ((next_item = item->comes_after_me.load(std::memory_order::relaxed)) == nullptr)[[likely]]{
                b.yield();
            }
            next_item->is_owner.store(true, std::memory_order::release);
        }
        item->used.store(false, std::memory_order::relaxed);
    }
};

struct Nop{
    void yield(){}
};

struct Yield{
    void yield(){
        std::this_thread::yield();
    }
};

struct LinYield{
    size_t n = 1;
    void yield(){
        for (size_t i = 0; i < n; ++i){
            std::this_thread::yield();
        }
        n+=1;
    }
};

struct ExpYield{
    size_t n = 1;
    void yield(){
        for (size_t i = 0; i < n; ++i){
            std::this_thread::yield();
        }
        n*=2;
    }
};

template<size_t n>
struct Sleep{
    std::mt19937 gen;
    void yield(){
        auto t = ((gen() * n ) >> 40) + n;
        std::this_thread::sleep_for((std::chrono::nanoseconds)t);
    }
};

struct NoCriticalSection{
    void critical_section(){}
};


struct FlushCriticalSection{
    void critical_section(){
        std::cout<<std::flush;
        std::cerr<<std::flush;
    }
};

struct SetCriticalSection{
    std::set<size_t> data;
    std::mt19937_64 rand;
    void critical_section(){
        data.insert(rand());
    }
};

template <typename T>
std::string strtype() {
    #ifdef __clang__
        std::string a=__PRETTY_FUNCTION__;
        assert(a.size() >= 28);
        return std::string(a.begin()+27,a.end()-1);
    #else
	    return std::string("(unknown type)");
    #endif
}

template<CriticalSection crit_sec_>
struct run_test_case{
    using crit_sec = crit_sec_;
    #define add_test(...) {run_test_for_lock<crit_sec, __VA_ARGS__>, #__VA_ARGS__}
    std::vector<std::pair<std::function<void(std::function<void(record_type)>)>, std::string>> tests = {
        add_test(TAS<Nop>),
        add_test(TAS<Yield>),
        // add_test(TAS<LinYield>),
        // add_test(TAS<ExpYield>),
        // add_test(TAS<Sleep<1>>),
        // add_test(TAS<Sleep<100>>),
        // add_test(TAS<Sleep<10000>>),
        // add_test(TAS<Sleep<1000000>>),
        // add_test(TAS<Sleep<100000000>>),

        add_test(TTAS<Nop>),
        add_test(TTAS<Yield>),
        // add_test(TTAS<LinYield>),
        // add_test(TTAS<Sleep<10000>>),
        // add_test(TTAS<ExpYield>),
        // add_test(TTAS<Sleep<1>>),
        // add_test(TTAS<Sleep<100>>),
        // add_test(TTAS<Sleep<1000000>>),
        // add_test(TTAS<Sleep<100000000>>),

        add_test(TicketLock<Yield>),
        add_test(TicketWaitLock<Yield>),
        // add_test(FTicketLock<Yield>),
        // add_test(FTicketWaitLock<Yield>),
        add_test(QueueLock<Yield>),
        add_test(ArrayLock<Yield>),
        add_test(std::mutex),
    };
    size_t tests_count(){
        return tests.size();
    }
    // int work(size_t& current_progress){
    // }
};

template<size_t b, size_t e>
decltype(auto) make_const(size_t n, auto&&f){
    static_assert(b < e);
    assert(b <= n);
    assert(n < e);
    if constexpr(b + 1 == e){
        assert(n == b);
        return std::invoke(FORWARD(f), std::integral_constant<size_t, b>());
    }else{
        constexpr size_t c = (b+e)/2;
        if (n < c){
            return make_const<b, c>(n, FORWARD(f));
        }else{
            return make_const<c, e>(n, FORWARD(f));
        }
    }
}

decltype(auto) tuple_for(auto&& tuple, auto&& f){
    constexpr auto size = std::tuple_size_v<std::decay_t<decltype(tuple)>>;
    for (size_t i = 0; i < size; ++i){
        make_const<0, size>(i, f);
    }
}

int main(){
    auto pre_tests = std::tuple<void*
        , run_test_case<NoCriticalSection>*
        // , run_test_case<FlushCriticalSection>*
        // , run_test_case<SetCriticalSection>*
    >();
    auto tests = std::apply([&](auto&&arg, auto&&...args){
        return std::tuple<std::decay_t<decltype(*args)>...>();
    }, pre_tests);
    auto& tests_ = tests;
    size_t tests_count = 0;
    size_t test_cases_count = std::tuple_size_v<decltype(tests)>;
    tuple_for(tests, [&](auto i){
        tests_count += std::get<i>(tests).tests_count();
    });
    size_t total_iterations = tests_count * thread_counts.size();
    std::cout << "import matplotlib.pyplot as plt" << std::endl;
    std::cout << "fig, (plt_avg, plt_max) = plt.subplots(2, "<<test_cases_count<<")" << std::endl;
    if (test_cases_count == 1){
        std::cout << "plt_avg, plt_max = [plt_avg], [plt_max]" << std::endl;
    }
    size_t current_progress = 0;
    tuple_for(tests, [&](auto i){
        auto& test = std::get<i>(tests);
        std::cout << "plt_avg["<<i<<"].set_title('"<<strtype<typename std::tuple_element_t<i, std::decay_t<decltype(tests_)>>::crit_sec>()<<".avg')" << std::endl;
        std::cout << "plt_max["<<i<<"].set_title('"<<strtype<typename std::tuple_element_t<i, std::decay_t<decltype(tests_)>>::crit_sec>()<<".max')" << std::endl;
        auto& tests = test.tests;

        std::vector<record_type> output;
        size_t progress_bar_width = 64;
        for (auto& test: tests){
            test.first([&](record_type record){
                output.push_back(record);
                auto pos = ++current_progress;
                for (size_t i = 0; i < pos * progress_bar_width  / total_iterations; ++i){
                    if ((i + pos) % 8 == 0){
                        std::clog << "#";
                    }else{
                        std::clog << ".";
                    }
                }
                for (size_t i = pos * progress_bar_width  / total_iterations; i < progress_bar_width ; ++i){
                    if ((i + pos) % 8 == 0){
                        std::clog << "#";
                    }else{
                        std::clog << "-";
                    }
                }
                std::cerr << " " << pos << "/" << total_iterations << "\r";
            });
            std::cout << "plt_avg["<<i<<"].plot([";
            for (auto& record: output){
                std::cout << record.thread_count << ",";
            }
            std::cout << "],[";
            for (auto& record: output){
                std::cout << record.avg_wait_time << "/" << thread_safe_time::clocks_per_sec << ",";
            }
            std::cout << "], '-_', label='"<< test.second <<"')\n";
            std::cout << "plt_max["<<i<<"].plot([";
            for (auto& record: output){
                std::cout << record.thread_count << ",";
            }
            std::cout << "],[";
            for (auto& record: output){
                std::cout << record.max_wait_time << "/" << thread_safe_time::clocks_per_sec << ",";
            }
            std::cout << "], '-_', label='"<< test.second <<"')\n";
            output.clear();
        }
        std::cout << "plt_avg["<<i<<"].legend(loc='upper left')" << std::endl;
        std::cout << "plt_max["<<i<<"].legend(loc='upper left')" << std::endl;
    });
    std::cerr << std::endl;
    std::cout << "plt.show()\n" << std::endl;
    
}
