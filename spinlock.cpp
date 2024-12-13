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

#if __cplusplus < 202000L
#error "need c++20"
#endif

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

template<typename Lock>
struct lock_test{
    struct {
        Lock m_;
        void lock(){m_.lock();}
        void unlock(){m_.unlock();}
    } lock;
    std::list<clock_t> waits;
    lock_test(size_t thread_count){
        std::vector<std::thread> threads(thread_count);
        for (auto& thread: threads){
            thread = std::thread([&](){worker();});
        }
        for (auto& thread: threads){
            thread.join();
        }
    }
    void worker(){
        auto program_start = thread_safe_time::clock();
        decltype(waits) local_waits;
        while (1){
            auto start_waiting = thread_safe_time::clock();
            decltype(start_waiting) stop_waiting;
            {
                std::unique_lock ul(lock);
                stop_waiting = thread_safe_time::clock();
            }
            local_waits.push_back(
                thread_safe_time::clock_from_diff(
                    stop_waiting - start_waiting
                )
            );
            if (
                thread_safe_time::clock_from_diff(
                    stop_waiting - program_start
                ) * 10 > thread_safe_time::clocks_per_sec
            ){
                break;
            }
        }
        {
            std::unique_lock ul(lock);
            std::copy(
                local_waits.begin(),
                local_waits.end(),
                std::back_inserter(waits)
            );
        }
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
    std::vector<size_t> thread_counts(32);
    for (size_t i = 0; i < thread_counts.size() ; ++i){
        thread_counts[i] = (i % 16) * (1LLU << i / 16);
    }
    std::sort(thread_counts.begin(), thread_counts.end());
    thread_counts.resize(
            std::unique(
                thread_counts.begin(),
                thread_counts.end()
            ) - thread_counts.begin()
        );
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

template<typename Lock>
void run_test_for_lock(std::function<void(record_type)> on_result){
    for (auto thread_count: thread_counts){
        lock_test<Lock> t(thread_count);
        on_result({
            thread_count,
            t.avg_wait_time(),
            t.max_wait_time(),
        });
    }
}

template<typename T>
struct CAS{
    std::atomic<T>& a;
    CAS(std::atomic<T>& a):a(a){}
    std::optional<T> if_equals_to;
    std::optional<T> then_assign;
    std::optional<T> actual_value;
    std::optional<std::memory_order> success;
    std::optional<std::memory_order> failure;
    std::optional<bool> may_fail;
    bool cas(){
        assert(if_equals_to.has_value());
        assert(then_assign.has_value());
        assert(success.has_value());
        assert(failure.has_value());
        assert(may_fail.has_value());
        if (*may_fail){
            return a.compare_exchange_weak(*actual_value, *then_assign, *success, *failure);
        }else{
            return a.compare_exchange_strong(*actual_value, *then_assign, *success, *failure);
        }
    }
    operator T(){
        return *actual_value;
    }
};

struct TAS{
    std::atomic<bool> is_locked;
    void lock(){
        while (true){
            CAS cas(is_locked);
            cas.if_equals_to = false;
            cas.then_assign = true;
            cas.may_fail = true;
            cas.success = std::memory_order::acq_rel;
            cas.failure = std::memory_order::relaxed;
            if (cas.cas()){
                break;
            }
        }
    }
    void unlock(){
        is_locked.store(false, std::memory_order::release);
    }
};

struct TTAS{
    std::atomic<bool> is_locked;
    void lock(){
        while (true){
            while (is_locked.load(std::memory_order::relaxed) == true){}
            CAS cas(is_locked);
            cas.if_equals_to = false;
            cas.then_assign = true;
            cas.may_fail = true;
            cas.success = std::memory_order::acq_rel;
            cas.failure = std::memory_order::relaxed;
            if (cas.cas()){
                break;
            }
        }
    }
    void unlock(){
        is_locked.store(false, std::memory_order::release);
    }
};

struct TYTAS{
    std::atomic<bool> is_locked;
    void lock(){
        while (true){
            while (is_locked.load(std::memory_order::relaxed) == true){
                std::this_thread::yield();
            }
            CAS cas(is_locked);
            cas.if_equals_to = false;
            cas.then_assign = true;
            cas.may_fail = true;
            cas.success = std::memory_order::acq_rel;
            cas.failure = std::memory_order::relaxed;
            if (cas.cas()){
                break;
            }
        }
    }
    void unlock(){
        is_locked.store(false, std::memory_order::release);
    }
};

struct YTicketLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::relaxed);
        while (owner_ticket.load(std::memory_order::acquire) != my_ticket){
            std::this_thread::yield();
        }
    }
    void unlock(){
        auto next_owner = owner_ticket.load(std::memory_order::relaxed) + 1;
        owner_ticket.store(next_owner, std::memory_order::release);
    }
};

struct YITicketLock{
    std::atomic<size_t> first_unused_ticket;
    std::atomic<size_t> owner_ticket;
    void lock(){
        auto my_ticket = first_unused_ticket.fetch_add(1, std::memory_order::seq_cst);
        while (owner_ticket.load(std::memory_order::seq_cst) != my_ticket){
            std::this_thread::yield();
        }
    }
    void unlock(){
        owner_ticket.fetch_add(1, std::memory_order::seq_cst);
    }
};

int main(){
    std::vector<record_type> output;
    size_t current_progress = 0;
    #define add_test(lock) {run_test_for_lock<lock>, #lock}
    std::vector<std::pair<std::function<void(std::function<void(record_type)>)>, const char*>> tests = {
        add_test(std::mutex),
        add_test(TAS),
        add_test(TTAS),
        add_test(TYTAS),
        add_test(YTicketLock),
        add_test(YITicketLock),
    };
    size_t total_iterations = tests.size() * thread_counts.size();
    size_t progress_bar_width = 64;
    std::cout << "import matplotlib.pyplot as plt" << std::endl;
    std::cout << "fig, (plt_avg, plt_max) = plt.subplots(1, 2)" << std::endl;
    std::cout << "plt_avg.set_title('avg')" << std::endl;
    std::cout << "plt_max.set_title('max')" << std::endl;
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
        std::cout << "plt_avg.plot([";
        for (auto& record: output){
            std::cout << record.thread_count << ",";
        }
        std::cout << "],[";
        for (auto& record: output){
            std::cout << record.avg_wait_time << ",";
        }
        std::cout << "], '-_', label='"<< test.second <<"')\n";
        std::cout << "plt.plot([";
        for (auto& record: output){
            std::cout << record.thread_count << ",";
        }
        std::cout << "],[";
        for (auto& record: output){
            std::cout << record.max_wait_time << ",";
        }
        std::cout << "], '-_', label='"<< test.second <<"')\n";
        output.clear();
    }
    std::cerr << std::endl;
    std::cout << "plt_avg.legend(loc='upper left')" << std::endl;
    std::cout << "plt_max.legend(loc='upper left')" << std::endl;
    std::cout << "plt.show()\n" << std::endl;
}