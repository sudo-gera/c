#include <set>
#include <any>
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
#include <mutex>

#define assert_m(...) assert_f(__VA_ARGS__,#__VA_ARGS__)

std::mutex cout_mutex;
struct Print: std::stringstream{
    ~Print(){
        std::unique_lock lock(cout_mutex);
        std::cerr << str();
    }
};
bool assert_f(bool q,std::string f){
	bool*a=&q;
	if (not q){
		Print()<<"\x1b[91massertion failed: \x1b[0m"<<f<<std::endl;
		while (a){
			q=*++a;
		}
	}
	return q;
}

#if __cplusplus < 202000L
#error "need c++20"
#endif


struct MakeZero{
    template<typename T>
    operator T&&(){
        union {
            char data[sizeof(T)];
            T value;
        } result = {0};
        memset(result.data, 0, sizeof(result.data));
        std::construct_at(&result.value);
        return result.value;
    }
};

#define ZERO (MakeZero())

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
    using time_point_t = decltype(clock());
    constexpr clock_t clocks_per_sec = duration_t::period::den;
};

consteval auto thread_counts_vector(){
    std::vector<size_t> thread_counts(32);
    for (size_t i = 0; i < thread_counts.size() ; ++i){
        thread_counts[i] = i + 1;
        // thread_counts[i] = 64;
        // thread_counts[i] = 16;
        // thread_counts[i] = 4;
    }
    std::sort(thread_counts.begin(), thread_counts.end());
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
    thread_safe_time::clock_t avg_wait_time;
    thread_safe_time::clock_t max_wait_time;
};

static thread_local size_t thread_index = 0LLU-2;

template<typename T, bool check = true>
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

struct Emp{
    void yield(){}
};

struct Alg{
    void yield(){assert(false);}
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

template <typename T>
std::string strtype() {
    std::string a=__PRETTY_FUNCTION__;
    #ifdef __clang__
        assert(a.size() >= 28);
        return std::string(a.begin()+27,a.end()-1);
    #else
        assert(a.size() >= 32);
        a = std::string(a.begin() + 32, a.end());
        for (size_t i = 0; i < a.size(); ++i){
            if (a[i] == ';'){
                a = std::string(a.begin(), a.begin() + i);
                return a;
            }
        }
        assert(false);
    #endif
}

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

template<typename T>
struct mutex_stack{
    std::mutex m;
    std::vector<T> data;
    void put(T item){
        std::unique_lock l(m);
        data.push_back(std::move(item));
    }
    std::optional<T> get(){
        std::unique_lock l(m);
        std::optional<T> tmp;
        if (not data.empty()){
            tmp = std::move(data.back());
            data.pop_back();
        }
        return tmp;
    }
};

std::atomic<size_t> allocated_nodes = 0;
auto check_allocated_nodes = std::unique_ptr<char,
    decltype([](auto&&...){
        assert(allocated_nodes == 0);
    })
>((char*)&allocated_nodes);

uintptr_t pack_ptr(void* ptr, uint16_t data){
    static_assert(sizeof(void*) == 8);
    static_assert(sizeof(uintptr_t) == 8);
    static_assert(CHAR_BIT == 8);
    uintptr_t uptr = (uintptr_t)ptr;
    assert((uptr & 0xffff'0000'0000'0000) == 0);
    uintptr_t udata = data;
    udata <<= 16 * 3;
    uptr |= udata;
    return uptr;
}

template<typename T>
std::pair<T, uint16_t> unpack_ptr(uintptr_t data){
    static_assert(sizeof(void*) == 8);
    static_assert(sizeof(uintptr_t) == 8);
    static_assert(CHAR_BIT == 8);
    uintptr_t udata = data & 0xffff'0000'0000'0000;
    udata >>= 16 * 3;
    data = data & 0x0000'ffff'ffff'ffff;
    T ptr = (T)data;
    return {ptr, udata};
}

template<std::memory_order put_to_head_order, std::memory_order put_to_prev_order, Backoff back_off, typename Node, typename ct=std::nullptr_t>
void put_to_stack(Node* item, std::atomic<Node*>& place, ct&& callback = nullptr){
    auto prev_item = place.load(std::memory_order::relaxed);
    back_off b;
    while (true){
        item->prev.store(prev_item, put_to_prev_order);
        CAS cas(place);
        cas.if_equals_to = prev_item;
        cas.then_assign = item;
        cas.may_fail = true;
        cas.success = put_to_head_order;
        cas.failure = std::memory_order::relaxed;
        if (cas()){
            break;
        }else{
            prev_item = cas;
        }
        if constexpr(not std::is_same_v<ct, nullptr_t>){
            if (callback()){
                return;
            }
        }else{
            b.yield();
        }
    }
}

namespace hazard_pointers{
    constexpr size_t hazard_pointer_count = thread_counts.back() + 1;
    struct hazard_pointer{
        std::atomic<size_t> owner = 0LLU-1;
        std::atomic<void*> data = nullptr;
    };
    std::array<hazard_pointer, hazard_pointers::hazard_pointer_count> hazard_pointers;
    struct hazard_pointer_owner{
        hazard_pointer* owned_ptr = nullptr;
        hazard_pointer_owner(){
            static_assert(hazard_pointers.size());
            for (auto& ptr: hazard_pointers){
                CAS cas(ptr.owner);
                cas.if_equals_to = 0LLU-1;
                cas.then_assign = thread_index;
                cas.may_fail = false;
                cas.success = std::memory_order::acquire;
                cas.failure = std::memory_order::relaxed;
                if (cas()){
                    owned_ptr = &ptr;
                    return;
                }
            }
            assert(false);
        }
        ~hazard_pointer_owner(){
            owned_ptr->data.store(nullptr, std::memory_order::relaxed);
            owned_ptr->owner.store(0LLU-1, std::memory_order::release);
        }
        static std::atomic<void*>& get(){
            static thread_local hazard_pointer_owner owner;
            return owner.owned_ptr->data;
        }
    };
    template<typename T>
    void delete_from_void_ptr(void*ptr){
        delete (T*)ptr;
    }
    struct scheduled_deletion_node{
        void(*deleter)(void*) = nullptr;
        void* data;
        std::atomic<scheduled_deletion_node*> prev = nullptr;
    };
    template<typename T>
    struct scheduled_deletion_data{
        T data;
        scheduled_deletion_node node;
        scheduled_deletion_data(auto&&...args):data(FORWARD(args)...){}
    };
    std::atomic<scheduled_deletion_node*> scheduled_deletions = nullptr;
    using scheduled_deletion = scheduled_deletion_node;
    std::atomic<size_t> scheduled_to_delete_count = 0;
    bool is_present_among_hazard_pointers(void* item){
        for (auto& hazard_pointer: hazard_pointers){
            if (hazard_pointer.data.load(std::memory_order::acquire) == item){
                return true;
            }
        }
        return false;
    }
    template<Backoff back_off>
    void flush(){
        auto item = scheduled_deletions.exchange(nullptr);
        while (item){
            auto prev_item = item->prev.load(std::memory_order::acquire);
            if (is_present_among_hazard_pointers(item->data)){
                put_to_stack<
                    std::memory_order::relaxed,
                    std::memory_order::release,
                    back_off
                >(item, scheduled_deletions);
            }else{
                scheduled_to_delete_count.fetch_sub(1, std::memory_order::relaxed);
                item->deleter(item->data);
            }
            item = prev_item;
        }
    }
    template<Backoff back_off, typename T>
    void async_delete(T* item){
        auto ptr = (scheduled_deletion_data<T>*)item;
        put_to_stack<
            std::memory_order::release,
            std::memory_order::relaxed,
            back_off
        >(&ptr->node, scheduled_deletions);
        if (scheduled_to_delete_count.fetch_add(
            1, std::memory_order::relaxed
        ) > hazard_pointer_count){
            hazard_pointers::flush<back_off>();
        }
        
    }
    template<typename T>
    T* allocate_and_construct(auto&&...args){
        auto ptr = new scheduled_deletion_data<T>(FORWARD(args)...);
        ptr->node.deleter = delete_from_void_ptr<scheduled_deletion_data<T>>;
        ptr->node.data = ptr;
        assert((void*)ptr == (void*)&ptr->data);
        return &ptr->data;
    }
};



struct stack_test_event{
    size_t data;
    thread_safe_time::time_point_t start_time;
    thread_safe_time::time_point_t stop_time;
    struct types{enum type{put, get};};
    types::type type;
};

template<Backoff back_off, typename T_, bool eliminate, bool check = true>
struct lock_free_stack{
    using T = size_t;
    std::array<std::atomic<uintptr_t>, 16> elimination;
    lock_free_stack(){
        //memset(&elimination, 0, sizeof(elimination));
    }
    struct Node;
    struct task{
        std::optional<T> value;
        std::atomic<bool> is_done = false;
        Node* item = nullptr;
    };
    using elim_ptr_t = task*;
    struct Node{
        T data;
        std::atomic<Node*> prev = nullptr;
        Node(auto&&...args):data(FORWARD(args)...){
            prev = nullptr;
            if constexpr(check){
                allocated_nodes.fetch_add(1, std::memory_order::relaxed);
            }
        }
        ~Node(){
            if constexpr(check){
                allocated_nodes.fetch_sub(1, std::memory_order::relaxed);
            }
        }
    };
    std::atomic<Node*> head = nullptr;
    thread_local static std::mt19937 rand;
    void put(T data){
        Node* item = hazard_pointers::allocate_and_construct<Node>(std::move(data));
        auto& elim = elimination[rand() % elimination.size()];
        task t;
        t.value = item->data;
        t.item = item;
        back_off b;
        put_to_stack<
            std::memory_order::relaxed,
            std::memory_order::release,
            back_off
        >(item, head, [&](){
            return elim_backoff<stack_test_event::types::put>(elim, t, b);
        });
    }
    std::optional<T> get(){
        auto& hazard_pointer = hazard_pointers::hazard_pointer_owner::get();
        Node* item = head.load(std::memory_order::relaxed);
        back_off b;
        auto& elim = elimination[rand() % elimination.size()];
        task t;
        while (item){
            while (1){
                hazard_pointer.store(item, std::memory_order::release);
                auto actual_item = head.load(std::memory_order::relaxed);
                if (actual_item == item){
                    break;
                }else{
                    item = actual_item;
                }
            }
            if (item == nullptr){
                break;
            }
            CAS cas(head);
            cas.if_equals_to = item;
            cas.then_assign = item->prev.load(std::memory_order::acquire);
            cas.may_fail = true;
            cas.success = std::memory_order::acquire;
            cas.failure = std::memory_order::relaxed;
            if (cas()){
                break;
            }else{
                item = cas;
            }
            if (elim_backoff<stack_test_event::types::get>(elim, t, b)){
                break;
            }
        }
        hazard_pointer.store(nullptr, std::memory_order::release);
        if (item and not t.value.has_value()){
            t.value = std::move(item->data);
            t.item = item;
        }
        if (t.item){
            hazard_pointers::async_delete<back_off>(t.item);
        }
        return t.value;
    }
    template<stack_test_event::types::type type>
    bool elim_backoff(std::atomic<uintptr_t>&elim, task&t , back_off&b){
        if constexpr(not eliminate){
            b.yield();
            return false;
        }
        // Print() << thread_index << " eliming task " << &t << std::endl;
        CAS elim_cas(elim);
        auto elim_first_task = pack_ptr(&t, type);
        elim_cas.if_equals_to = 0;
        elim_cas.then_assign = elim_first_task;
        elim_cas.may_fail = false;
        elim_cas.success = std::memory_order::release;
        elim_cas.failure = std::memory_order::relaxed;
        if (not elim_cas()){
            auto elim_task = elim_cas;
            auto [elim_ptr, elim_type] = unpack_ptr<elim_ptr_t>(elim_task);
            if (elim_type != type){
                // Print() << thread_index << " eliming task " << &t << " failed, but i can help with " << elim_ptr << std::endl;
                elim_cas.reset();
                elim_cas.if_equals_to = elim_task;
                elim_cas.then_assign = 0;
                elim_cas.may_fail = false;
                elim_cas.success = std::memory_order::seq_cst;
                elim_cas.failure = std::memory_order::seq_cst;
                if (elim_cas()){
                    // Print() << thread_index << " eliming task " << &t << " failed, but stole task " << elim_ptr << std::endl;
                    if constexpr(type == stack_test_event::types::get){
                        t.value = std::move(elim_ptr->value);
                        t.item = elim_ptr->item;
                    }else{
                        elim_ptr->value = std::move(t.value);
                        elim_ptr->item = t.item;
                    }
                    t.is_done.store(true, std::memory_order::seq_cst);
                    elim_ptr->is_done.store(true, std::memory_order::seq_cst);
                    // Print() << thread_index << " eliming task " << &t << " failed, but made task " << elim_ptr << std::endl;
                    return true;
                }else{
                    // Print() << thread_index << " eliming task " << &t << " failed, but someone else helps " << elim_ptr << std::endl;
                    b.yield();
                    return false;
                }
            }else{
                // Print() << thread_index << " eliming task " << &t << " failed. extining." << std::endl;
                b.yield();
                return false;
            }
        }else{
            // Print() << thread_index << " eliming task " << &t << " succed, waiting..." << std::endl;
            b.yield();
            elim_cas.reset();
            elim_cas.if_equals_to = elim_first_task;
            elim_cas.then_assign = 0;
            elim_cas.may_fail = false;
            elim_cas.success = std::memory_order::seq_cst;
            elim_cas.failure = std::memory_order::seq_cst;
            if (elim_cas()){
                // Print() << thread_index << " eliming task " << &t << " succed, no one helped me" << std::endl;
                return false;
            }else{
                // Print() << thread_index << " eliming task " << &t << " succed, someone helped me, waiting..." << std::endl;
                while (not t.is_done.load(std::memory_order::seq_cst)){
                    b.yield();
                }
                // Print() << thread_index << " eliming task " << &t << " succed, someone helped me, done" << std::endl;
                return true;
            }
        }
        assert(false);
    }
    ~lock_free_stack(){
        while(1){
            auto item = get();
            if (not item.has_value()){
                break;
            }
        }
        hazard_pointers::flush<back_off>();
    }
};
template<Backoff back_off, typename T_, bool eliminate, bool check>
thread_local std::mt19937 lock_free_stack<back_off, T_, eliminate, check>::rand = std::mt19937(std::random_device()());

auto before_order(const stack_test_event& left, const stack_test_event& right){
    if (left.start_time > right.stop_time){
        return 1<=>0;
    }
    if (left.stop_time < right.start_time){
        return -1<=>0;
    }
    return 0<=>0;
}

template<size_t fill, size_t puts, size_t gets>
struct fill_then_random_puts_and_gets{
    std::mt19937 mt = std::mt19937(std::random_device()());
    std::uniform_int_distribution<size_t> ud = std::uniform_int_distribution<size_t>(1, gets + puts);
    size_t to_fill = fill;
    bool operator()(){
        if (--to_fill){
            return false;
        }
        return ud(mt) <= gets;
    }
};

template<typename stack_, typename time, typename should_get>
struct stack_test{
    size_t thread_count;
    struct alignas(hardware_destructive_interference_size) stack_test_thread{
        std::thread thread;
        std::vector<stack_test_event> events;
        should_get rand;
    };
    std::vector<stack_test_event> events;
    stack_ stack;
    stack_test(size_t thread_count):thread_count(thread_count){
        std::vector<stack_test_thread> threads(thread_count);
        auto rand_dev = std::random_device();
        for (stack_test::stack_test_thread& thread: threads){
            thread.thread = std::thread([&](){thread_index = &thread - &threads[0] ; worker(thread_index, thread);});
        }
        for (stack_test::stack_test_thread& thread: threads){
            thread.thread.join();
        }
        for (stack_test::stack_test_thread& thread: threads){
            std::copy(thread.events.begin(), thread.events.end(), std::back_inserter(events));
        }
        auto order = [](auto&&left, auto&&right){
            if (left.type != right.type){
                return left.type < right.type;
            }
            if (left.type == stack_test_event::types::put){
                return left.data < right.data;
            }
            if (left.type == stack_test_event::types::get){
                return left.data > right.data;
            }
            assert(false);
        };
        sort(events.begin(), events.end(), order);
        // for(auto&event: events){
        //     Print() << event.type << " " << event.data << std::endl;
        // }
        assert(not stack.get().has_value());
        for (size_t i = 0; i < events.size() ; ++i){
            auto tmp = events[i];
            if (tmp.type == stack_test_event::types::put){
                tmp.type = stack_test_event::types::get;
            }else{
                tmp.type = stack_test_event::types::put;
            }
            auto b = std::lower_bound(events.begin(), events.end(), tmp, order) - events.begin();
            auto e = std::upper_bound(events.begin(), events.end(), tmp, order) - events.begin();
            assert(e - b == 1);
            auto j = b;
            if (tmp.type == stack_test_event::types::get){
                assert(events[i].type == stack_test_event::types::put);
                assert(events[j].type == stack_test_event::types::get);
                assert(before_order(events[i], events[j]) <= 0);
            }else{
                assert(events[i].type == stack_test_event::types::get);
                assert(events[j].type == stack_test_event::types::put);
                assert(before_order(events[i], events[j]) >= 0);
            }
        }
    }
    void worker(size_t start, stack_test_thread& thread){
        auto& rand = thread.rand;
        auto program_start = thread_safe_time::clock();
        bool only_get = false;
        while (1){
            decltype(stack.get()) value = start;
            auto start_time = program_start;
            auto stop_time = program_start;
            stack_test_event::types::type type;
            if (only_get or (bool)rand()){
                type = stack_test_event::types::get;
                start_time = thread_safe_time::clock();
                value = stack.get();
                stop_time = thread_safe_time::clock();
            }else{
                type = stack_test_event::types::put;
                start += thread_count;
                start_time = thread_safe_time::clock();
                stack.put(value.value());
                stop_time = thread_safe_time::clock();
            }
            if (value.has_value()){
                thread.events.push_back(stack_test_event{
                    .data = value.value(),
                    .start_time = start_time,
                    .stop_time = stop_time,
                    .type = type,
                });
            }
            if (only_get and not value.has_value()){
                break;
            }
            if (thread_safe_time::clock_from_diff(
                stop_time-program_start
            ) * time::den > time::num * thread_safe_time::clocks_per_sec){
                only_get = true;
            }
        }
    }
    thread_safe_time::clock_t avg_wait_time(){
        std::vector<
            std::decay_t<
                decltype(
                    thread_safe_time::clock_from_diff(
                        events[0].stop_time - events[0].start_time
                    )
                )
            >
        > waits;
        for (auto& event: events){
            waits.push_back(
                thread_safe_time::clock_from_diff(
                    event.stop_time - event.start_time
                )
            );
        }
        return waits.empty() ? 0 : std::reduce(
            waits.begin(),
            waits.end(),
            std::decay_t<decltype(waits[0])>(0),
            [](auto&& left, auto&& right){
                return left + right;
            }
        ) / waits.size();
    }
    thread_safe_time::clock_t max_wait_time(){
        std::vector<
            std::decay_t<
                decltype(
                    thread_safe_time::clock_from_diff(
                        events[0].stop_time - events[0].start_time
                    )
                )
            >
        > waits;
        for (auto& event: events){
            waits.push_back(
                thread_safe_time::clock_from_diff(
                    event.stop_time - event.start_time
                )
            );
        }
        return waits.empty() ? 0 : std::reduce(
            waits.begin(),
            waits.end(),
            std::decay_t<decltype(waits[0])>(0),
            [](auto&& left, auto&& right){
                return std::max(left, right);
            }
        );
    }
};

// template<typename should_get, typename stack, typename time = std::ratio<1, 4'000'000>>
template<typename should_get, typename stack, typename time = std::ratio<1, 4'0>>
void run_test_for_lock(std::function<void(record_type)> on_result){
    for (auto thread_count: thread_counts){
        stack_test<stack, time, should_get> t(thread_count);
        on_result({
            thread_count,
            t.avg_wait_time(),
            t.max_wait_time(),
        });
    }
}

template<typename should_get_, typename function = std::function<void(std::function<void(record_type)>)>>
struct run_test_case{
    using should_get = should_get_;
    #define add_test(...) {function(run_test_for_lock<should_get, __VA_ARGS__>), #__VA_ARGS__}
    std::vector<std::pair<function, std::string>> tests = {
        add_test(lock_free_stack<Emp, size_t, true>),
        add_test(lock_free_stack<Emp, size_t, false>),
        add_test(lock_free_stack<Yield, size_t, true>),
        add_test(lock_free_stack<Yield, size_t, false>),
        add_test(lock_free_stack<LinYield, size_t, true>),
        add_test(lock_free_stack<ExpYield, size_t, true>),
        add_test(lock_free_stack<Sleep<100>, size_t, true>),
    };
    size_t tests_count(){
        return tests.size();
    }
};

int main(){
    auto pre_tests = std::tuple<void*
        , run_test_case<fill_then_random_puts_and_gets<1024, 1, 1>>*
        , run_test_case<fill_then_random_puts_and_gets<1024, 4, 1>>*
        , run_test_case<fill_then_random_puts_and_gets<1024, 1, 4>>*
    >();
    auto tests = std::apply([&](auto&&, auto&&...args){
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
        std::cout << "plt_avg["<<i<<"].set_title('"<<strtype<typename std::tuple_element_t<i, std::decay_t<decltype(tests_)>>::should_get>()<<".avg')" << std::endl;
        std::cout << "plt_max["<<i<<"].set_title('"<<strtype<typename std::tuple_element_t<i, std::decay_t<decltype(tests_)>>::should_get>()<<".max')" << std::endl;
        auto& tests = test.tests;

        std::vector<record_type> output;
        size_t progress_bar_width = 64;
        for (auto& test: tests){
            test.first([&](record_type record){
                output.push_back(record);
                auto pos = ++current_progress;
                for (size_t i = 0; i < pos * progress_bar_width  / total_iterations; ++i){
                    if ((i + pos) % 8 == 0){
                        std::clog << "$";
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
                Print() << " " << pos << "/" << total_iterations << "\r";
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
    Print() << std::endl;
    std::cout << "plt.show()\n" << std::endl;
    return 0;    
}

namespace plot{
    constexpr static inline size_t max_plot_colors = 10;

    constexpr static inline size_t tests_on_same_plot = [](){
        run_test_case<fill_then_random_puts_and_gets<0, 0, 0>, void (*)(std::function<void (record_type)>) > a;
        return a.tests.size();
    }();

    constexpr static inline bool is_tests_on_plot_more_than_colors = plot::tests_on_same_plot > plot::max_plot_colors;
    
    template<size_t a, size_t s>
    struct more_tests_on_plot_than_colors{};

    template<>
    struct [[
        deprecated("It may lead to showing multiple tests with the same color.")
    ]] more_tests_on_plot_than_colors<
        tests_on_same_plot,
        max_plot_colors
    >{};

    more_tests_on_plot_than_colors<
        plot::is_tests_on_plot_more_than_colors ? plot::tests_on_same_plot: 0LLU-1,
        plot::is_tests_on_plot_more_than_colors ? plot::max_plot_colors : 0LLU-1
    > warn;

};

