#include <type_traits>
#include <utility>
#include <cassert>
#include <limits.h>
#include <random>
#include <optional>
#include <utility>
#include <memory>
#include <type_traits>
#include <list>
#include <array>
#include <string>
#include <sstream>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <deque>
#include <algorithm>
#include <cstring>
#include <csignal>
#include <cerrno>
#include <cassert>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#if __has_include(<sys/event.h>)
    #define use_kqueue
    #include <sys/event.h>
#endif

#if __has_include(<sys/epoll.h>)
    #define use_epoll
    #include <sys/epoll.h>
#endif

#define FORWARD(val) (std::forward<decltype(val)>(val))
#define VALUE_AS_STRING_AND_VALUE(x) #x << "\t\t\t\t" << x

#define BUFFER_SIZE 8192
#define none 0x5555'5555'5555'5555

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// clang-format off
std::array<const char*, 256> escape = {
    "\\x00", "\\x01", "\\x02", "\\x03", "\\x04", "\\x05", "\\x06", "\\x07", "\\x08", "\\t",   "\\n",   "\\x0b", "\\x0c", "\\r",   "\\x0e", "\\x0f",
    "\\x10", "\\x11", "\\x12", "\\x13", "\\x14", "\\x15", "\\x16", "\\x17", "\\x18", "\\x19", "\\x1a", "\\x1b", "\\x1c", "\\x1d", "\\x1e", "\\x1f",
    " ",     "!",     "\"",    "#",     "$",     "%",     "&",     "\'",    "(",     ")",     "*",     "+",     ",",     "-",     ".",     "/",
    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ":",     ";",     "<",     "=",     ">",     "?",
    "@",     "A",     "B",     "C",     "D",     "E",     "F",     "G",     "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",
    "P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",     "X",     "Y",     "Z",     "[",     "\\\\",  "]",     "^",     "_",
    "`",     "a",     "b",     "c",     "d",     "e",     "f",     "g",     "h",     "i",     "j",     "k",     "l",     "m",     "n",     "o",
    "p",     "q",     "r",     "s",     "t",     "u",     "v",     "w",     "x",     "y",     "z",     "{",     "|",     "}",     "~",     "\\x7f",
    "\\x80", "\\x81", "\\x82", "\\x83", "\\x84", "\\x85", "\\x86", "\\x87", "\\x88", "\\x89", "\\x8a", "\\x8b", "\\x8c", "\\x8d", "\\x8e", "\\x8f",
    "\\x90", "\\x91", "\\x92", "\\x93", "\\x94", "\\x95", "\\x96", "\\x97", "\\x98", "\\x99", "\\x9a", "\\x9b", "\\x9c", "\\x9d", "\\x9e", "\\x9f",
    "\\xa0", "\\xa1", "\\xa2", "\\xa3", "\\xa4", "\\xa5", "\\xa6", "\\xa7", "\\xa8", "\\xa9", "\\xaa", "\\xab", "\\xac", "\\xad", "\\xae", "\\xaf",
    "\\xb0", "\\xb1", "\\xb2", "\\xb3", "\\xb4", "\\xb5", "\\xb6", "\\xb7", "\\xb8", "\\xb9", "\\xba", "\\xbb", "\\xbc", "\\xbd", "\\xbe", "\\xbf",
    "\\xc0", "\\xc1", "\\xc2", "\\xc3", "\\xc4", "\\xc5", "\\xc6", "\\xc7", "\\xc8", "\\xc9", "\\xca", "\\xcb", "\\xcc", "\\xcd", "\\xce", "\\xcf",
    "\\xd0", "\\xd1", "\\xd2", "\\xd3", "\\xd4", "\\xd5", "\\xd6", "\\xd7", "\\xd8", "\\xd9", "\\xda", "\\xdb", "\\xdc", "\\xdd", "\\xde", "\\xdf",
    "\\xe0", "\\xe1", "\\xe2", "\\xe3", "\\xe4", "\\xe5", "\\xe6", "\\xe7", "\\xe8", "\\xe9", "\\xea", "\\xeb", "\\xec", "\\xed", "\\xee", "\\xef",
    "\\xf0", "\\xf1", "\\xf2", "\\xf3", "\\xf4", "\\xf5", "\\xf6", "\\xf7", "\\xf8", "\\xf9", "\\xfa", "\\xfb", "\\xfc", "\\xfd", "\\xfe", "\\xff",
};
// clang-format on

auto repr_s(std::string data) {
    std::string result = "'";
    for (auto c : data) {
        result += escape[c & 0xff];
    }
    result += "'";
    return result;
}

template<typename T>
struct repr_m{
    static auto repr(T&& val) {
        std::stringstream a;
        a << FORWARD(val);
        return repr_s(a.str());
    }
};

template<typename R, typename...A>
struct repr_m<R(&)(A...)>{
    template<typename T>
    static auto repr(T&& val) {
        std::stringstream a;
        a << FORWARD(&val);
        return repr_s(a.str());
    }
};

template<typename T>
auto repr(T&& val){
    return repr_m<T>::repr(FORWARD(val));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto eassert(bool cond){
    if (not cond){
        errno = 255;
    }
    return cond;
}

struct sys_msg_printer : std::stringstream {
    std::unordered_set<int> ignored;
    void ignore(int err){
        ignored.insert(err);
    }

#define add_syscall(name)                                                \
    template<typename...ARGS>                                            \
    auto name(ARGS&&... args) {                                          \
        errno = 0;                                                       \
        auto ret = ::name(FORWARD(args)...);                             \
        int err = errno;                                                 \
        if (err and not ignored.count(err)) {                            \
            std::cerr << "\n <<< ERROR >>>\n";                           \
            std::cerr << "    " #name " Failed\n";                       \
            std::cerr << "    code = " << err << "\n";                   \
            std::cerr << "    text = " << std::strerror(err) << "\n";    \
            std::cerr << "\n <<< ARGS >>> " << std::endl;                \
            (void)((std::cerr << "    " << repr(args) << "\n"), ..., 0); \
            if (str().size()) {                                          \
                std::cerr << "\n <<< MESSAGE >>> " << std::endl;         \
                std::cerr << str() << std::endl;                         \
            }                                                            \
            std::cerr << std::endl;                                      \
            throw std::runtime_error("syscall failed");                  \
        }                                                                \
        std::stringstream tmp;                                           \
        swap(tmp);                                                       \
        ignored.clear();                                                 \
        return ret;                                                      \
    }

    add_syscall(shutdown)
    add_syscall(write)
    add_syscall(read)
    add_syscall(close)
    add_syscall(socket)
    add_syscall(fcntl)
    add_syscall(inet_pton)
    add_syscall(inet_ntop)
    add_syscall(eassert)
    add_syscall(connect)
    add_syscall(bind)
    add_syscall(listen)
    add_syscall(accept)
    add_syscall(signal)
    add_syscall(clock_gettime)
    add_syscall(pipe)
    add_syscall(getsockopt)
    add_syscall(open)
#ifdef use_kqueue
    add_syscall(kqueue)
    add_syscall(kevent)
#endif
#ifdef use_epoll
    add_syscall(epoll_ctl)
    add_syscall(epoll_wait)
    add_syscall(epoll_pwait)
    add_syscall(epoll_create)
    add_syscall(epoll_create1)
#endif
} sys;

#undef assert
#define assert(x) assert_f(x, #x, __FILE__, __LINE__)
void assert_f(bool cond, const char* s, const char* f, size_t l){
    if (cond){
        return;
    }
    std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!Assertion failed" << std::endl;
    std::cerr << s << std::endl;
    std::cerr << f << ":" << l << std::endl;
    char const volatile* p = "";
    while (*p)
    {
        ++p;
    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define timespec_base (1'000'000'000)

using timespec_pair = std::pair<
    decltype(
        ((struct timespec*)(0))->tv_sec
    ),
    decltype(
        ((struct timespec*)(0))->tv_nsec
    )
>;

timespec_pair monotonic(){
    struct timespec tp;
    sys.clock_gettime(CLOCK_MONOTONIC, &tp);
    return {tp.tv_sec, tp.tv_nsec};
}

auto operator+(timespec_pair left, timespec_pair right){
    left.first  += right.first;
    left.second += right.second;
    left.first  += left.second / timespec_base;
    left.second  = left.second % timespec_base;
    return left;
}

auto operator-(timespec_pair left, timespec_pair right){
    assert(left >= right);
    while (left.second < right.second){
        left.second += timespec_base;
        left.first -= 1;
    }
    assert(left >= right);
    left.first  -= right.first;
    left.second -= right.second;
    return left;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename>
class function_ref; // Primary template

template <typename R, typename... Args>
class function_ref<R(Args...)> {
public:
    void* callable_ = nullptr;
    R (*invoker_)(void*, Args&&...) = nullptr;

    function_ref() = default;

    // // Handle function pointers
    // function_ref(R(*func)(Args...)) noexcept {
    //     callable_ = reinterpret_cast<void*>(func);
    //     invoker_ = [](void* ptr, Args&&... args) -> R {
    //         auto f = reinterpret_cast<R(*)(Args...)>(ptr);
    //         return f(std::forward<Args>(args)...);
    //     };
    // }

    template<typename T>
    static R invoker(void* ptr, Args&&... args) {
        return (*reinterpret_cast<T*>(ptr))(std::forward<Args>(args)...);
    };


    // Handle functors/lambdas (non-owning reference)
    template <typename Callable>
    requires(
        not std::is_same_v<
            function_ref,
            std::decay_t<Callable>
        >
    )
    function_ref(Callable& callable) noexcept {
        using T = std::remove_reference_t<Callable>;
        static_assert(std::is_invocable_r_v<R, T&, Args...>,
                      "Callable must be invocable with the correct signature");

        callable_ = static_cast<void*>(&callable);
        invoker_ = function_ref::invoker<T>;
        // invoker_ = [](void* ptr, Args&&... args) -> R {
        //     return (*reinterpret_cast<T*>(ptr))(std::forward<Args>(args)...);
        // };
    }

    function_ref(const function_ref&) = default;
    function_ref& operator=(const function_ref&) = default;
    function_ref(function_ref&&) = default;
    function_ref& operator=(function_ref&&) = default;

    R operator()(Args... args) const {
        // std::cerr << (void*)callable_ << " " << (void*)invoker_ << " " << (void*)this << std::endl;
        assert(invoker_ && "function_ref is empty");
        return invoker_(callable_, std::forward<Args>(args)...);
    }

    operator bool() const noexcept {
        assert((invoker_ == nullptr) == (callable_ == nullptr));
        return invoker_ != nullptr;
    }

    void reset(){
        callable_ = nullptr;
        invoker_ = nullptr;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct defer{
    T val;
    defer(T&& val):val(val){}
    ~defer(){val();}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // struct one_connection_context{
// //     char incoming_buffer[8192];
// //     char outgoing_buffer[8192];
// //     int internal_fd = -1;
// //     int external_fd = -1;
// //     uint32_t buf_len = 0;
// //     uint32_t buf_sent = 0;
// //     bool eof_on_external_socket = false;
// //     bool eof_on_internal_socket = false;

// //     bool selector_told_us_that_we_can_read_on_internal_socket = false;
// //     bool selector_told_us_that_we_can_read_on_external_socket = false;
// //     bool selector_told_us_that_we_can_write_on_internal_socket = false;
// //     bool selector_told_us_that_we_can_write_on_external_socket = false;

// //     void called_by_selector(){
// //         if (incoming_buffer
// //     }
// // };



// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// bool has_to_stop = false;

// #ifdef use_kqueue

//     void print_event(struct kevent& value){
//         std::cerr << "event{" << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.ident) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.filter) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.flags) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.fflags) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.data) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.udata) << std::endl
//         << "}" << std::endl;
//     }

//     struct kqueue_selector{
//     private:
//         int sd = 0;
//         std::pair<
//             std::array<
//                 struct kevent,
//                 256
//             >,
//             size_t
//         > events_to_process = {{}, 0};
//         std::vector<
//             struct kevent
//         > events_to_add;
//         void_ptr_storage<Task> callbacks;
//         std::multimap<timespec_pair, Task> sleeping_tasks;

//         void add_descriptor(int fd, Task callback, short filter){
//             auto& new_event = events_to_add.emplace_back();
//             std::memset(&new_event, 0, sizeof(new_event));

//             new_event.ident = fd;
//             new_event.filter = filter;
//             new_event.flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
//             new_event.udata = callbacks.put(std::move(callback));
//         }

//     public:
//         void async_read(auto fd, Task callback){
//             add_descriptor(fd, std::move(callback), EVFILT_READ);
//         }

//         void async_write(auto fd, Task callback){
//             add_descriptor(fd, std::move(callback), EVFILT_WRITE);
//         }

//         void async_wait(timespec_pair seconds, Task callback){
//             auto ct = monotonic();
//             std::cerr << "async wait called at " << ct.first << "." << ct.second << std::endl;
//             ct = ct + seconds;
//             std::cerr << "async wait would sleep intil " << ct.first << "." << ct.second << std::endl;
//             sleeping_tasks.insert({
//                 seconds + monotonic(),
//                 std::move(callback)
//             });
//         }

//         ~kqueue_selector(){
//             std::cerr << "exiting" << std::endl;
//             sys.close(sd);
//         }

//         kqueue_selector(){
//             sd = sys.kqueue();
//             if (sd < 0){
//                 throw std::runtime_error{"error when creating selector"};
//             }
//         }

//         void loop(){
//             while(not has_to_stop){

//                 std::cerr << "have " << events_to_add.size() << " events to add." << std::endl;
//                 for (auto& event : events_to_add){
//                     print_event(event);
//                 }

//                 struct timespec to_sleep;
//                 struct timespec* to_sleep_ptr = nullptr;
//                 if (not sleeping_tasks.empty()){
//                     auto  wake_at = sleeping_tasks.begin()->first;
//                     auto current_time = monotonic();
//                     if (wake_at < current_time){
//                         wake_at = current_time;
//                     }
//                     wake_at = wake_at - current_time;

//                     to_sleep.tv_sec = wake_at.first;
//                     to_sleep.tv_nsec = wake_at.second;
//                     to_sleep_ptr = &to_sleep;
//                 }

//                 if (to_sleep_ptr){
//                     std::cerr << "have to sleep " << to_sleep_ptr->tv_sec << "." << to_sleep_ptr->tv_nsec << std::endl;
//                 }else{
//                     std::cerr << "dont have to sleep " << std::endl;
//                 }

//                 sys.ignore(EINTR);
//                 events_to_process.second = sys.kevent(
//                     sd,
//                     events_to_add.data(),
//                     events_to_add.size(),
//                     events_to_process.first.data(),
//                     events_to_process.first.size(),
//                     to_sleep_ptr
//                 );
//                 events_to_add.clear();
//                 if (errno == EINTR){
//                     std::cerr << "interrupted" << std::endl;
//                     return;
//                 }
//                 assert(errno == 0);
//                 assert(events_to_process.second < events_to_process.first.size());
//                 std::cerr << "have " << events_to_process.second << " events to process." << std::endl;
//                 for (size_t q = 0; q < events_to_process.second; ++q){
//                     auto& event = events_to_process.first[q];
//                     print_event(event);
//                 }
//                 // sys.eassert(events_to_process.second != 0);
//                 for (size_t i = 0; i < events_to_process.second; ++i){
//                     auto ptr = events_to_process.first[i].udata;
//                     std::cerr << "using " << ptr << std::endl;
//                     callbacks.get(ptr)();
//                     std::cerr << "freeing " << ptr << std::endl;
//                     callbacks.del(ptr);
//                 }
//                 events_to_process.second = 0;

//                 auto it = sleeping_tasks.begin();
//                 auto ct = monotonic();
//                 while(it != sleeping_tasks.end()){
//                     auto nx = std::next(it);
//                     auto& [wake_at, task] = *it;
//                     if (wake_at <= ct){
//                         std::cout << "found task to be executed at " << wake_at.first << "." << wake_at.second << std::endl;
//                         task();
//                         std::cout << "deleted task to be executed at " << wake_at.first << "." << wake_at.second << std::endl;
//                         sleeping_tasks.erase(it);
//                         std::cout << sleeping_tasks.size() << std::endl;
//                     }
//                     if (nx == sleeping_tasks.end()){
//                         break;
//                     }
//                     it = nx;
//                     ++nx;
//                 }
//             }
//             std::cerr << "has to stop" << std::endl;
//         }
//     };

//     static_assert(selector<kqueue_selector>);
// #endif

// #ifdef use_epoll
//     void print_event(struct epoll_event& value){
//         std::cerr << "event{" << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.events) << std::endl
//         << "      " << VALUE_AS_STRING_AND_VALUE(value.data.fd) << std::endl
//         << "}" << std::endl;
//     }

//     struct epoll_selector{
//     private:
//         int sd = 0;
//         std::pair<
//             std::array<
//                 struct epoll_event,
//                 256
//             >,
//             size_t
//         > events_to_process = {{}, 0};
//         std::deque<
//             std::array<
//                 Task, 2
//             >
//         > callbacks;
//         std::multimap<timespec_pair, Task> sleeping_tasks;

//         void prepare_callbacks(int fd){
//             callbacks.resize(
//                 std::max(
//                     callbacks.size(),
//                     size_t(fd+1)
//                 )
//             );
//         }

//         constexpr static uint32_t actions[2] = {
//             EPOLLIN,
//             EPOLLOUT,
//         };

//         void epoll_mod(int fd, bool action_index, bool add){
//             prepare_callbacks(fd);
//             bool has_other = callbacks[fd][not action_index];
//             auto op = has_other ? EPOLL_CTL_MOD : (add ? EPOLL_CTL_ADD : EPOLL_CTL_DEL);
//             struct epoll_event new_event;
//             std::memset(&new_event, 0, sizeof(new_event));
//             new_event.data.fd = fd;
//             if (add){
//                 new_event.events |= actions[action_index];
//             }
//             if (has_other){
//                 new_event.events |= actions[not action_index];
//             }
//             std::cerr << "have 1 event to mod" << std::endl;
//             std::cerr << "action_index = " << action_index << std::endl;
//             std::cerr << "add = " << add << std::endl;
//             print_event(new_event);
//             sys.epoll_ctl(sd, op, fd, &new_event);
//         }

//         void add_descriptor(int fd, Task callback, bool action_index){
//             epoll_mod(fd, action_index, 1);
//             callbacks[fd][action_index] = std::move(callback);
//         }

//     public:
//         void async_read(auto fd, Task callback){
//             add_descriptor(fd, std::move(callback), 0);
//         }

//         void async_write(auto fd, Task callback){
//             add_descriptor(fd, std::move(callback), 1);
//         }

//         void async_wait(timespec_pair seconds, Task callback){
//             auto ct = monotonic();
//             std::cerr << "async wait called at " << ct.first << "." << ct.second << std::endl;
//             ct = ct + seconds;
//             std::cerr << "async wait would sleep intil " << ct.first << "." << ct.second << std::endl;
//             sleeping_tasks.insert({
//                 seconds + monotonic(),
//                 std::move(callback)
//             });
//         }

//         ~epoll_selector(){
//             std::cerr << "exiting" << std::endl;
//             sys.close(sd);
//         }

//         epoll_selector(){
//             sd = sys.epoll_create1(0);
//             if (sd < 0){
//                 throw std::runtime_error{"error when creating selector"};
//             }
//         }

//         void loop(){
//             while(not has_to_stop){
//                 double to_sleep = timespec_base;
//                 if (not sleeping_tasks.empty()){
//                     auto  wake_at = sleeping_tasks.begin()->first;
//                     auto current_time = monotonic();
//                     if (wake_at < current_time){
//                         wake_at = current_time;
//                     }
//                     wake_at = wake_at - current_time;

//                     to_sleep = 0;
//                     to_sleep += wake_at.second;
//                     to_sleep /= timespec_base;
//                     to_sleep += wake_at.first;
//                     to_sleep *= 1000;
//                 }

//                 if (to_sleep != timespec_base){
//                     std::cerr << "have to sleep " << to_sleep << std::endl;
//                 }else{
//                     std::cerr << "dont have to sleep " << std::endl;
//                 }

//                 sys.ignore(EINTR);
//                 events_to_process.second = sys.epoll_wait(
//                     sd,
//                     events_to_process.first.data(),
//                     events_to_process.first.size(),
//                     to_sleep
//                 );
//                 if (errno == EINTR){
//                     std::cerr << "interrupted" << std::endl;
//                     return;
//                 }
//                 assert(errno == 0);
//                 assert(events_to_process.second < events_to_process.first.size());
//                 std::cerr << "have " << events_to_process.second << " events to process." << std::endl;
//                 for (size_t q = 0; q < events_to_process.second; ++q){
//                     auto& event = events_to_process.first[q];
//                     print_event(event);
//                 }
//                 for (size_t i = 0; i < events_to_process.second; ++i){
//                     auto& event = events_to_process.first[i];
//                     auto fd = event.data.fd;
//                     auto events = event.events;
//                     for (bool action_index: std::array<bool, 2>({0, 1})){
//                         if (events & actions[action_index]){
//                             std::cerr << "using fd=" << fd << ", action_index=" << action_index << std::endl;
//                             assert(callbacks.size() > size_t(fd));
//                             epoll_mod(fd, action_index, 0);
//                             auto func = std::move(callbacks[fd][action_index]);
//                             func();
//                         }
//                     }
//                 }
//                 events_to_process.second = 0;

//                 auto it = sleeping_tasks.begin();
//                 auto ct = monotonic();
//                 while(it != sleeping_tasks.end()){
//                     auto nx = std::next(it);
//                     auto& [wake_at, task] = *it;
//                     std::cout << "having task to be executed at " << wake_at.first << "." << wake_at.second << std::endl;
//                     std::cout << "now is " << ct.first << "." << ct.second << std::endl;
//                     if (wake_at <= ct){
//                         std::cout << "found task to be executed at " << wake_at.first << "." << wake_at.second << std::endl;
//                         task();
//                         std::cout << "deleted task to be executed at " << wake_at.first << "." << wake_at.second << std::endl;
//                         sleeping_tasks.erase(it);
//                         std::cout << sleeping_tasks.size() << std::endl;
//                     }
//                     if (nx == sleeping_tasks.end()){
//                         break;
//                     }
//                     it = nx;
//                     ++nx;
//                 }
//             }
//             std::cerr << "has to stop" << std::endl;
//         }
//     };

//     static_assert(selector<epoll_selector>);
// #endif

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct socket_closer{
//     int s;
//     socket_closer(int s):
//         s(s)
//     {
//         std::cerr << "started owning " << s << std::endl;
//     }
//     ~socket_closer(){
//         std::cerr << "stopped owning " << s << std::endl;
//         sys.close(s);
//     }
// };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using host_port = std::pair<
                    std::array<
                        char,
                        INET_ADDRSTRLEN
                    >,
                    uint16_t
                >;

host_port sockaddr_to_host_port(const sockaddr& sa){
    union {
        sockaddr sa;
        sockaddr_in sai;
    } sau;
    sau.sa = sa;
    host_port result;
    sys.inet_ntop(AF_INET, &sau.sai.sin_addr, result.first.data(), result.first.size());
    result.second = ntohs(sau.sai.sin_port);
    return result;
}

sockaddr host_port_to_sockaddr(const char* addr, uint16_t port){
    union {
        sockaddr sa;
        sockaddr_in sai;
    } sau;
    std::memset(&sau, 0, sizeof(sau));
    sau.sai.sin_family = AF_INET;
    sau.sai.sin_port = htons(port);
    sys.eassert(sys.inet_pton(AF_INET, addr, &sau.sai.sin_addr) == 1);
    return sau.sa;
}

sockaddr host_port_to_sockaddr(const host_port& hp){
    return host_port_to_sockaddr(hp.first.data(), hp.second);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ll_create_non_blocking_socket(){
    int s = sys.socket(AF_INET, SOCK_STREAM, 0);
    int flags = sys.fcntl(s, F_GETFL, 0);
    flags |= O_NONBLOCK;
    sys.fcntl(s, F_SETFL, flags);
    return s;
}

int ll_create_connecting_socket(const sockaddr& addr){
    auto s = ll_create_non_blocking_socket();
    sys.ignore(EINPROGRESS);
    sys.connect(s, &addr, sizeof(addr));
    return s;
}

int ll_create_listening_socket(const sockaddr& addr){
    auto s = ll_create_non_blocking_socket();
    sys.bind(s, &addr, sizeof(addr));
    sys.listen(s, 65536);
    return s;
}

std::pair<
    int,
    sockaddr
> ll_accept(int s){
    sockaddr addr;
    std::memset(&addr, 0, sizeof(addr));
    socklen_t addr_len = sizeof(addr);
    int c = sys.accept(s, &addr, &addr_len);
    return {
        c,
        addr,
    };
}

using error_t = std::decay_t<decltype(errno)>;

error_t get_errno(int fd){
    error_t err = 0;
    socklen_t err_len = sizeof(err);
    sys.getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
    assert(err_len == sizeof(err));
    return err;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// auto start_server(auto& sel, const char* addr, uint16_t port, function<void(socket_ptr, const char*, uint16_t)> callback){
//     auto s = create_listening_socket(addr, port);
//     function<void()> func = [&sel, s, callback=std::move(callback)]()mutable{
//         sockaddr_in client;
//         std::memset(&client, 0, sizeof(client));
//         socklen_t client_len = sizeof(client);
//         socket_ptr c = sys.accept(s, (sockaddr*)&client, &client_len);
//         sys.eassert(client_len == sizeof(client));
//         sys.eassert(client.sin_family == AF_INET);
//         char client_addr[INET_ADDRSTRLEN];
//         sys.inet_ntop(AF_INET, &client.sin_addr, client_addr, sizeof(client_addr));
//         auto client_port = ntohs(client.sin_port);
//         callback(c, client_addr, client_port);
//         int s_ = s;
//         auto& sel_ = sel;
//         sel_.async_read(s_, std::move(*Task::current));
//     };
//     sel.async_read(s, std::move(func));
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool should_exit = false;

std::array<int, 2> signal_pipe = [](){
    std::array<int, 2> p;
    sys.pipe(p.data());
    return p;
}();

size_t handle_calls = 0;

void handle(int signal){
    char data[64];
    std::memset(data, '?', sizeof(data));
    auto last = data + sizeof(data);
    *--last = '\n';
    bool neg = signal < 0;
    if (neg){
        signal = - signal;
    }
    while (signal){
        *--last = signal % 10 + '0';
        signal /= 10;
    }
    if (neg){
        *--last = '-';
    }
    char msg[] = "signal = ";
    for (size_t i = sizeof(msg) - 2; i < sizeof(msg); --i){
        *--last = msg[i];
    }
    *--last = '\n';
    int rc = write(1, last, data + sizeof(data) - last);
    (void)rc;
    rc = write(signal_pipe[1], "", 1);
    (void)rc;
    if (++handle_calls > 4){
        abort();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// size_t max_connections = none;
timespec_pair connection_timeout = {none, none};
timespec_pair clock_interval = {none, none};
size_t max_accepted_sockets_per_server = none;
size_t max_connected_sockets = none;

const char* first_bytes_filename = nullptr;
char first_bytes_data[BUFFER_SIZE];
size_t first_bytes_size = none;

size_t internal_port = none;
const char* internal_host = nullptr;
sockaddr internal_sockaddr;

size_t external_port = none;
const char* external_host = nullptr;
sockaddr external_sockaddr;

namespace modes{
    enum modes{ server, client};
};

size_t mode = none;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct fd_owner;

int get_fd(const fd_owner& s);

struct fd_owner{
private:
    int s;
public:
    fd_owner(int s):
        s(s)
    {
        std::cerr << "started owning fd=" << s << std::endl;
    }
    ~fd_owner(){
        std::cerr << "stopped owning fd=" << s << std::endl;
        sys.close(s);
    }
    fd_owner(fd_owner&&) = delete;
    fd_owner(const fd_owner&) = delete;
    int get_fd_()const{
        return s;
    }
};

int get_fd(const fd_owner& s){
    return s.get_fd_();
}

struct stream_socket_owner;
struct server_socket_owner;

struct socket_owner{
private:
    fd_owner s;
    sockaddr addr;
    socket_owner(std::pair<int, sockaddr> s):
        s(s.first),
        addr(s.second)
    {}
    operator const fd_owner&(){
        return s;
    }
    operator sockaddr()const{
        return addr;
    }
    friend stream_socket_owner;
    friend server_socket_owner;
};

struct stream_socket_owner{
private:
    socket_owner s;
    bool shut_rd_ = false;
    bool shut_wr_ = false;
public:
    operator const fd_owner&(){
        return s;
    }
    operator sockaddr()const{
        return s;
    }
    void shut_rd(){
        if (not shut_rd_){
            sys.ignore(ENOTCONN);
            sys.shutdown(get_fd(s), SHUT_RD);
            shut_rd_ = true;
        }
    }
    void shut_wr(){
        if (not shut_rd_){
            sys.ignore(ENOTCONN);
            sys.shutdown(get_fd(s), SHUT_WR);
            shut_wr_ = true;
        }
    }
    ~stream_socket_owner(){
        shut_rd();
        shut_wr();
    }
    stream_socket_owner(const sockaddr& addr):
        s({ll_create_connecting_socket(addr), addr})
    {}
    stream_socket_owner(const fd_owner& server):
        s(ll_accept(get_fd(server)))
    {}
};

struct server_socket_owner{
private:
    socket_owner s;
public:
    operator sockaddr()const{
        return s;
    }
    operator const fd_owner&(){
        return s;
    }
    server_socket_owner(const sockaddr& addr):
        s({ll_create_listening_socket(addr), addr})
    {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct one_socket{
//     char buf_to_sent_into_this_socket[8192];
//     std::optional<stream_socket_owner> socket;
//     size_t buf_begin = 0;
//     size_t buf_end = 0;
//     bool got_eof_from_this_socket = false;
//     bool got_error_from_this_socket = false;
//     // bool this_socket_has_data_to_read = false;
//     // bool this_socket_has_space_to_write = false;
//     bool socket_waits_to_write = false;
//     bool socket_waits_to_read = false;
// };

// struct two_sockets{
//     one_socket internal_socket;
//     one_socket external_socket;
//     time_t last_event = 0;
// };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef use_epoll

template<typename Callback>
struct Selector{
    fd_owner pool_fd = sys.epoll_create1(0);

    std::pair<
        std::array<
            struct epoll_event,
            1024
        >,
        size_t
    > events_to_process;

    void change_fd_in_pool(const fd_owner& fd, Callback* callback, bool old_read, bool old_write, bool new_read, bool new_write){
        if (old_read == new_read and old_write == new_write){
            return;
        }

        int op = EPOLL_CTL_MOD;

        if (not old_read and not old_write){
            op = EPOLL_CTL_ADD;
        }

        if (not new_read and not new_write){
            op = EPOLL_CTL_DEL;
        }

        struct epoll_event new_event;
        std::memset(&new_event, 0, sizeof(new_event));
        new_event.data.ptr = callback;

        if (new_read){
            new_event.events |= EPOLLIN;
        }

        if (new_write){
            new_event.events |= EPOLLOUT;
        }

        sys.epoll_ctl(get_fd(pool_fd), op, get_fd(fd), &new_event);
    }

    void wait(std::optional<timespec_pair> timeout){
        double to_sleep = timespec_base;
        if (timeout){
            to_sleep = 0;
            to_sleep += timeout->second;
            to_sleep /= timespec_base;
            to_sleep += timeout->first;
            to_sleep *= 1000;
        }

        sys.ignore(EINTR);
        events_to_process.second = sys.epoll_wait(
            get_fd(pool_fd),
            events_to_process.first.data(),
            events_to_process.first.size(),
            to_sleep
        );

        if (errno == EINTR){
            std::cerr << "interrupted" << std::endl;
            return;
        }

        assert(errno == 0);
        assert(events_to_process.second < events_to_process.first.size());
        std::cerr << "have " << events_to_process.second << " events to process." << std::endl;

        // for (size_t q = 0; q < events_to_process.second; ++q){
        //     auto& event = events_to_process.first[q];
        //     // print_event(event);
        // }

        for (size_t q = 0; q < events_to_process.second; ++q){
            auto& event = events_to_process.first[q];
            if (event.events & EPOLLIN){
                (*(Callback*)event.data.ptr)(false);
            }
            if (event.events & EPOLLOUT){
                (*(Callback*)event.data.ptr)(true);
            }
        }
    }
};

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using selector_t = Selector<function_ref<void(bool)>>;

using header_t = uint_least64_t;

#define CMD_SOCKET_HEADER_SIZE (sizeof(header_t))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename s_owner>
struct SplitCallbacks{
    SplitCallbacks(selector_t& selector, s_owner& s):
        selector(selector),
        s(s)
    {
        handler.outer = this;
    }

private:
    selector_t& selector;

    s_owner& s;

    using external_callback = function_ref<void(error_t)>;

    bool has_err = false;

    bool has_write_task_ = false;
    external_callback write_callback;

    bool has_read_task_ = false;
    external_callback read_callback;

    struct Handler{
        SplitCallbacks* outer;
        void operator()(bool to_write){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle(to_write);
        }
    } handler;

    function_ref<void(bool)> handler_ref = handler;

    void handle(bool to_write){
        auto err = get_errno(get_fd(s));
        if (err != 0){
            has_err = true;
        }
        if (to_write){
            assert(write_callback);
            auto write_callback_local = write_callback;
            write_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, has_read_task_, true, has_read_task_, false);
            has_write_task_ = false;
            assert(write_callback_local);
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            // std::cerr << (void*)write_callback_local.callable_ << " " << (void*)write_callback_local.invoker_ << " " << (void*)&write_callback_local << std::endl;
            write_callback_local(err);
        }else{
            assert(read_callback);
            auto read_callback_local = read_callback;
            read_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, true, has_write_task_, false, has_write_task_);
            has_read_task_ = false;
            assert(read_callback_local);
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            read_callback_local(err);
        }
    }

public:
    bool has_read_task(){
        return has_read_task_;
    }

    bool has_write_task(){
        return has_write_task_;
    }

    void wait_read(external_callback callback){
        assert(not has_err);
        assert(not read_callback);
        assert(not has_read_task_);
        assert(callback);
        selector.change_fd_in_pool(s, &handler_ref, false, has_write_task_, true, has_write_task_);
        read_callback = callback;
        has_read_task_ = true;
    }

    void wait_write(external_callback callback){
        assert(not has_err);
        assert(not write_callback);
        assert(not has_write_task_);
        assert(callback);
        selector.change_fd_in_pool(s, &handler_ref, has_read_task_, false, has_read_task_, true);
        write_callback = callback;
        has_write_task_ = true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StreamSocketCompleter{

    StreamSocketCompleter(selector_t& selector, const sockaddr& addr):
        last_event(monotonic()),
        s(addr),
        c(selector, s),
        connected(false)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

    StreamSocketCompleter(selector_t& selector, const fd_owner& server):
        last_event(monotonic()),
        s(server),
        c(selector, s),
        connected(true)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

private:
    timespec_pair last_event;

    stream_socket_owner s;
    SplitCallbacks<stream_socket_owner> c;

    using external_rw_callback = function_ref<void(const char*, size_t, error_t)>;
    // using external_connected_callback = function_ref<void(error_t)>;

    bool eof_is_written_ = false;
    bool connected = false;
    external_rw_callback connected_callback;

    std::array<char, 8192> write_buffer;
    bool has_full_write_task = false;
    size_t len_of_data_in_write_buffer = none;
    size_t still_has_to_write = none;
    external_rw_callback write_callback;

    std::array<char, 8192> read_buffer;
    bool has_full_read_task = false;
    size_t len_of_data_in_read_buffer = none;
    size_t still_has_to_read = none;
    external_rw_callback read_callback;

    struct ReadHandler{
        StreamSocketCompleter* outer;
        void operator()(error_t err){
            outer->last_event = monotonic();
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    struct WriteHandler{
        StreamSocketCompleter* outer;
        void operator()(error_t err){
            outer->last_event = monotonic();
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_write(err);
        }
    } write_handler;

    function_ref<void(bool)> write_handler_ref = write_handler;

    void handle_read(error_t err){
        if (err == 0){
            if (has_full_read_task){
                assert(0 < still_has_to_read);
                assert(len_of_data_in_read_buffer + still_has_to_read <= read_buffer.size());
                size_t readen = sys.read(get_fd(s), read_buffer.data() + len_of_data_in_read_buffer, still_has_to_read);
                len_of_data_in_read_buffer += readen;
                still_has_to_read -= readen;
                if (readen != 0 and still_has_to_read != 0){
                    return;
                }
            }else{
                assert(len_of_data_in_read_buffer == 0);
                assert(still_has_to_read == none);
                size_t readen = sys.read(get_fd(s), read_buffer.data(), read_buffer.size());
                len_of_data_in_read_buffer += readen;
            }
        }
        auto read_callback_local = read_callback;
        read_callback.reset();
        auto len_of_data_in_read_buffer_local = len_of_data_in_read_buffer;
        len_of_data_in_read_buffer = none;
        still_has_to_read = none;
        has_full_read_task = false;
        // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        read_callback_local(read_buffer.data(), len_of_data_in_read_buffer_local, err);
    }

    void handle_write(error_t err){
        if (not connected){
            if (err == 0){
                connected = true;
            }
            auto connected_callback_local = connected_callback;
            connected_callback.reset();
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            connected_callback_local(nullptr, 0, err);
            return;
        }
        if (err == 0){
            if (has_full_write_task){
                assert(0 < still_has_to_write);
                assert(still_has_to_write <= len_of_data_in_write_buffer);
                assert(0 < len_of_data_in_write_buffer);
                assert(len_of_data_in_write_buffer <= write_buffer.size());
                size_t written = sys.write(get_fd(s), write_buffer.data() + len_of_data_in_write_buffer - still_has_to_write, still_has_to_write);
                still_has_to_write -= written;
                if (still_has_to_write != 0){
                    return;
                }
            }else{
                assert(still_has_to_write == len_of_data_in_write_buffer);
                assert(0 < len_of_data_in_write_buffer);
                assert(len_of_data_in_write_buffer <= write_buffer.size());
                size_t written = sys.write(get_fd(s), write_buffer.data(), write_buffer.size());
                still_has_to_write -= written;
            }
        }
        auto write_callback_local = write_callback;
        write_callback.reset();
        auto len_of_data_in_write_buffer_local = len_of_data_in_write_buffer;
        len_of_data_in_write_buffer = none;
        auto still_has_to_write_local = still_has_to_write;
        still_has_to_write = none;
        has_full_write_task = false;
        // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        write_callback_local(write_buffer.data() + len_of_data_in_write_buffer_local - still_has_to_write_local, still_has_to_write_local, err);
    }

public:
    bool has_read_task(){
        return c.has_read_task();
    }

    bool has_write_task(){
        return c.has_write_task();
    }

    void full_read(size_t len, external_rw_callback callback){
        // std::cerr << "Registering user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        assert(len <= read_buffer.size());
        assert(callback);
        c.wait_read(read_handler_ref);
        read_callback = callback;
        has_full_read_task = true;
        still_has_to_read = len;
        len_of_data_in_read_buffer = len;
    }

    void partial_read(external_rw_callback callback){
        // std::cerr << "Registering user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        assert(callback);
        c.wait_read(read_handler_ref);
        read_callback = callback;
    }

    void full_write(const char* data, size_t len, external_rw_callback callback){
        // std::cerr << "Registering user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        assert(not eof_is_written_);
        assert(callback);
        c.wait_write(write_handler_ref);
        memmove(write_buffer.data(), data, len);
        write_callback = callback;
        has_full_write_task = true;
        still_has_to_write = len;
        len_of_data_in_write_buffer = len;
    }

    void partial_write(const char* data, size_t len, external_rw_callback callback){
        // std::cerr << "Registering user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        assert(not eof_is_written_);
        assert(callback);
        c.wait_write(write_handler_ref);
        memmove(write_buffer.data(), data, len);
        write_callback = callback;
        still_has_to_write = len;
        len_of_data_in_write_buffer = len;
    }

    void write_eof(){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(not eof_is_written_);
        s.shut_wr();
        eof_is_written_ = true;
    }

    bool eof_is_written()const{
        return eof_is_written_;
    }

    void wait_connected(external_rw_callback callback){
        // std::cerr << "Registering user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        // std::cerr << (void*)callback.callable_ << " " << (void*)callback.invoker_ << " " << (void*)&callback << std::endl;
        assert(not connected);
        assert(callback);
        c.wait_write(write_handler_ref);
        connected_callback = callback;
    }

    bool is_connected()const{
        return connected;
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }

    timespec_pair get_last_event(){
        return last_event;
    }
};

struct ServerSocketCompleter{

    ServerSocketCompleter(selector_t& selector, const sockaddr& addr):
        s(addr),
        c(selector, s)
    {
        read_handler.outer = this;
    }

private:
    server_socket_owner s;
    SplitCallbacks<server_socket_owner> c;

    using external_callback = function_ref<void(error_t)>;
    external_callback accept_callback;

    struct ReadHandler{
        ServerSocketCompleter* outer;
        void operator()(error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    void handle_read(error_t err){
        // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
        accept_callback(err);
    }

public:
    void accept(external_callback callback){
        assert(callback);
        c.wait_read(read_handler_ref);
        accept_callback = callback;
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename stream_context>
struct ServerManager;

struct AcceptedSocketCMD;

struct AcceptedSocketTCP;

struct AppServer;

uint_least64_t get_rand64(AppServer& app_server);

ServerManager<AcceptedSocketCMD>& get_cmd_server_manager(AppServer& app_server);
ServerManager<AcceptedSocketTCP>& get_tcp_server_manager(AppServer& app_server);

void handle_accept_ctl(AppServer& app, size_t index, header_t header);
void handle_accept_cmd(AppServer& app, size_t index, header_t header);
void handle_accept_tcp(AppServer& app, size_t index, header_t header);

void handle_read_ctl(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_cmd(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_tcp(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);

void handle_write_ctl(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_cmd(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_tcp(AppServer& app, const char* data, size_t size, error_t err, size_t index, header_t header);

template<typename stream_context>
struct ServerManager{
    ServerManager(AppServer& app_server, selector_t& selector, const sockaddr& addr):
        app_server(app_server),
        selector(selector),
        server(selector, addr),
        streams(max_accepted_sockets_per_server)
    {
        accept_handler.outer = this;
        start_waiting_for_accept();
    }

private:
    AppServer& app_server;

    selector_t& selector;

    ServerSocketCompleter server;

    std::vector<
        std::optional<
            stream_context
        >
    > streams;

    struct AcceptHandler{
        ServerManager* outer;
        void operator()(error_t err){
            assert(outer->is_waiting_for_accept);
            outer->is_waiting_for_accept = false;
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_accept(err);
        }
    } accept_handler;

    function_ref<void(error_t)> accept_handler_ref = accept_handler;

    bool is_waiting_for_accept = false;

    void start_waiting_for_accept(){
        if (not is_waiting_for_accept){
            server.accept(accept_handler_ref);
            is_waiting_for_accept = true;
        }
    }

    void handle_accept(error_t err){
        assert(err == 0);

        for (size_t i = 0; i < streams.size(); ++i){
            if (not streams[i].has_value()){
                auto& stream = streams[i];
                stream.emplace(selector, server, i, app_server);
                start_waiting_for_accept();
                return;
            }
        }
    }

public:
    size_t get_streams_size(){
        return streams.size();
    }

    stream_context* get_stream(size_t i){
        assert(i < streams.size());
        auto& stream = streams[i];
        return stream.has_value() ? &*stream : nullptr;
    }

    void close_stream(size_t i){
        auto& stream = streams[i];
        if (stream.has_value()){
            stream.reset();
            start_waiting_for_accept();
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace accepted_cmd_socket_states{
    enum accepted_cmd_socket_states{
        fresh, readen_first_bytes, main, worker
    };
};

struct AcceptedSocketCMD{

    AcceptedSocketCMD(selector_t& selector, const fd_owner& server, size_t index, AppServer& app_server):
        index(index),
        selector(selector),
        s(selector, server),
        app_server(app_server),
        accepted_cmd_socket_state(accepted_cmd_socket_states::fresh)
    {
        read_handler.outer = this;
        write_handler.outer = this;
        s.full_read(first_bytes_size, read_handler_ref);
    }

    size_t index = none;
    size_t other_index = none;
    header_t header = 0;
private:
    selector_t& selector;
    StreamSocketCompleter s;
    AppServer& app_server;
    size_t accepted_cmd_socket_state = none;

    struct ReadHandler{
        AcceptedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        AcceptedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_write(data, size, err);
        }
    } write_handler;

    function_ref<void(const char*, size_t, error_t)> write_handler_ref = write_handler;

    void close(){
        get_cmd_server_manager(app_server).close_stream(index);
    }

    void handle_read(const char* data, size_t size, error_t err){
        switch (accepted_cmd_socket_state){
            case accepted_cmd_socket_states::fresh:{
                if (err != 0){
                    close();
                    return;
                }
                assert(size <= first_bytes_size);
                if (size != first_bytes_size){
                    close();
                    return;
                }
                accepted_cmd_socket_state = accepted_cmd_socket_states::readen_first_bytes;
                s.full_read(CMD_SOCKET_HEADER_SIZE, read_handler_ref);
            }
            break;
            case accepted_cmd_socket_states::readen_first_bytes:{
                if (err != 0){
                    close();
                    return;
                }
                assert(size <= CMD_SOCKET_HEADER_SIZE);
                if (size != CMD_SOCKET_HEADER_SIZE){
                    close();
                    return;
                }
                header_t header = 0;
                static_assert(CHAR_BIT == 8);
                static_assert(CMD_SOCKET_HEADER_SIZE <= sizeof(header));
                assert(size <= sizeof(header));
                memcpy(&header, data, size);
                if (header == 0){
                    accepted_cmd_socket_state = accepted_cmd_socket_states::main;
                    handle_accept_ctl(app_server, index, header);
                }else{
                    accepted_cmd_socket_state = accepted_cmd_socket_states::worker;
                    handle_accept_cmd(app_server, index, header);
                }
            }
            break;
            case accepted_cmd_socket_states::main:{
                handle_read_ctl(app_server, data, size, err, index, header);
                assert(false);
            }
            break;
            case accepted_cmd_socket_states::worker:{
                handle_read_cmd(app_server, data, size, err, index, header);
            }
            break;
            default:
                assert(false);
        }
    }

    void handle_write(const char* data, size_t size, error_t err){
        if (header == 0){
            handle_write_ctl(app_server, data, size, err, index, header);
        }else{
            handle_write_cmd(app_server, data, size, err, index, header);
        }
    }

public:
    bool has_read_task(){
        return s.has_read_task();
    }

    bool has_write_task(){
        return s.has_write_task();
    }

    void full_read(size_t len){
        s.full_read(len, read_handler_ref);
    }

    void partial_read(){
        s.partial_read(read_handler_ref);
    }

    void full_write(const char* data, size_t len){
        s.full_write(data, len, write_handler_ref);
    }

    void partial_write(const char* data, size_t len){
        s.partial_write(data, len, write_handler_ref);
    }

    void write_eof(){
        s.write_eof();
    }

    bool eof_is_written(){
        return s.eof_is_written();
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }

    timespec_pair get_last_event(){
        return s.get_last_event();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AcceptedSocketTCP{

    AcceptedSocketTCP(selector_t& selector, const fd_owner& server, size_t index, AppServer& app_server):
        header(get_rand64(app_server) | 1),
        index(index),
        selector(selector),
        s(selector, server),
        app_server(app_server)
    {
        read_handler.outer = this;
        write_handler.outer = this;
        handle_accept_tcp(app_server, index, header);
    }

    bool request_for_cmd_socket_is_sent = false;
    header_t header;
    size_t index = none;
    size_t other_index = none;
private:
    selector_t& selector;
    StreamSocketCompleter s;
    AppServer& app_server;

    struct ReadHandler{
        AcceptedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        AcceptedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_write(data, size, err);
        }
    } write_handler;

    function_ref<void(const char*, size_t, error_t)> write_handler_ref = write_handler;

    void close(){
        get_tcp_server_manager(app_server).close_stream(index);
    }

    void handle_read(const char* data, size_t size, error_t err){
        handle_read_tcp(app_server, data, size, err, index, header);
    }

    void handle_write(const char* data, size_t size, error_t err){
        handle_write_tcp(app_server, data, size, err, index, header);
    }

public:
    bool has_read_task(){
        return s.has_read_task();
    }

    bool has_write_task(){
        return s.has_write_task();
    }

    void full_read(size_t len){
        s.full_read(len, read_handler_ref);
    }

    void partial_read(){
        s.partial_read(read_handler_ref);
    }

    void full_write(const char* data, size_t len){
        s.full_write(data, len, write_handler_ref);
    }

    void partial_write(const char* data, size_t len){
        s.partial_write(data, len, write_handler_ref);
    }

    void write_eof(){
        s.write_eof();
    }

    bool eof_is_written(){
        return s.eof_is_written();
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }

    timespec_pair get_last_event(){
        return s.get_last_event();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AppServer{
    AppServer(selector_t& selector, const sockaddr& cmd_addr, const sockaddr& tcp_addr):
        PRNG(std::random_device{}()),
        selector(selector),
        cmd_server(*this, selector, cmd_addr),
        tcp_server(*this, selector, tcp_addr)
    {}

    std::mt19937_64 PRNG;

    selector_t& selector;

    ServerManager<AcceptedSocketCMD> cmd_server;
    ServerManager<AcceptedSocketTCP> tcp_server;

    size_t main_index = none;

    AcceptedSocketCMD& get_main(){
        AcceptedSocketCMD* main_ptr = cmd_server.get_stream(main_index);
        assert(main_ptr);
        return *main_ptr;
    }

    void ctl_maybe_send_some_request(){
        auto& main = get_main();
        if (main.has_write_task()){
            return;
        }
        for (size_t i = 0; i < tcp_server.get_streams_size(); ++i){
            auto stream_ptr = tcp_server.get_stream(i);
            if (not stream_ptr){
                continue;
            }
            auto& stream = *stream_ptr;
            if (not stream.request_for_cmd_socket_is_sent){
                char message[CMD_SOCKET_HEADER_SIZE];
                memset(message, 0, sizeof(message));
                static_assert(sizeof(stream.header) <= CMD_SOCKET_HEADER_SIZE);
                memcpy(message, &stream.header, sizeof(stream.header));
                main.full_write(message, sizeof(message));
                break;
            }
        }
    }

    void cleanup(){
        auto current_time = monotonic();
        for (size_t i = 0; i < cmd_server.get_streams_size(); ++i){
            auto cmd_stream_ptr = cmd_server.get_stream(i);
            if (not cmd_stream_ptr){
                continue;
            }
            auto& cmd_stream = *cmd_stream_ptr;
            if ( current_time - cmd_stream.get_last_event() < connection_timeout ){
                continue;
            }
            if (cmd_stream.other_index == none){
                cmd_server.close_stream(cmd_stream.index);
            }
            auto tcp_stream_ptr = tcp_server.get_stream(cmd_stream.other_index);
            assert(tcp_stream_ptr);
            auto& tcp_stream = *tcp_stream_ptr;
            assert(tcp_stream.other_index == cmd_stream.index);
            assert(cmd_stream.other_index == tcp_stream.index);
            cmd_server.close_stream(cmd_stream.index);
            tcp_server.close_stream(tcp_stream.index);
        }
        for (size_t i = 0; i < tcp_server.get_streams_size(); ++i){
            auto tcp_stream_ptr = tcp_server.get_stream(i);
            if (not tcp_stream_ptr){
                continue;
            }
            auto& tcp_stream = *tcp_stream_ptr;
            if ( current_time - tcp_stream.get_last_event() < connection_timeout ){
                continue;
            }
            if (tcp_stream.other_index == none){
                tcp_server.close_stream(tcp_stream.index);
            }
            auto cmd_stream_ptr = cmd_server.get_stream(tcp_stream.other_index);
            assert(cmd_stream_ptr);
            auto& cmd_stream = *cmd_stream_ptr;
            assert(tcp_stream.other_index == cmd_stream.index);
            assert(cmd_stream.other_index == tcp_stream.index);
            cmd_server.close_stream(cmd_stream.index);
            tcp_server.close_stream(tcp_stream.index);
        }
    }
};

ServerManager<AcceptedSocketCMD>& get_cmd_server_manager(AppServer& app_server){
    return app_server.cmd_server;
}
ServerManager<AcceptedSocketTCP>& get_tcp_server_manager(AppServer& app_server){
    return app_server.tcp_server;
}

void handle_accept_ctl(AppServer& app_server, size_t index, header_t header){
    assert(header == 0);
    if (app_server.main_index != none){
        app_server.cmd_server.close_stream(app_server.main_index);
    }
    app_server.main_index = index;
}

void handle_read_ctl(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(header == 0);
    assert(app_server.main_index == index);
    if (err != 0){
        app_server.main_index = none;
        app_server.cmd_server.close_stream(index);
        return;
    }
}

void handle_write_ctl(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(header == 0);
    assert(app_server.main_index == index);
    if (err != 0){
        app_server.main_index = none;
        app_server.cmd_server.close_stream(index);
        return;
    }
    assert(size == 0);
    app_server.ctl_maybe_send_some_request();
}

void handle_accept_tcp(AppServer& app_server, size_t index, header_t header){    
    app_server.ctl_maybe_send_some_request();
}

void handle_accept_cmd(AppServer& app_server, size_t index, header_t header){
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index == none);
    for (size_t i = 0; i < app_server.tcp_server.get_streams_size(); ++i){
        auto stream_ptr = app_server.tcp_server.get_stream(i);
        if (not stream_ptr){
            continue;
        }
        auto& stream = *stream_ptr;
        if (stream.header == header){
            assert(stream.index == i);
            if (stream.other_index != none){
                app_server.cmd_server.close_stream(index);
                return;
            }
            stream.other_index = index;
            cmd_stream.other_index = i;
            break;
        }
    }
    if (cmd_stream.other_index == none){
        app_server.cmd_server.close_stream(index);
    }
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(cmd_stream.other_index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.index == cmd_stream.other_index);
    assert(cmd_stream.index == tcp_stream.other_index);
    tcp_stream.partial_read();
    cmd_stream.partial_read();
}

void handle_read_tcp(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.other_index != none);
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(tcp_stream.other_index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index == index);

    if (err != 0){
        app_server.cmd_server.close_stream(cmd_stream.index);
        app_server.tcp_server.close_stream(tcp_stream.index);
        return;
    }

    if (size != 0){
        cmd_stream.full_write(data, size);
        return;
    }
    
    assert(not cmd_stream.eof_is_written());
    cmd_stream.write_eof();
    if (tcp_stream.eof_is_written()){
        app_server.cmd_server.close_stream(cmd_stream.index);
        app_server.tcp_server.close_stream(tcp_stream.index);
    }
}

void handle_read_cmd(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index != none);
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(cmd_stream.other_index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.other_index == index);

    if (err != 0){
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
        return;
    }

    if (size != 0){
        tcp_stream.full_write(data, size);
        return;
    }
    
    assert(not tcp_stream.eof_is_written());
    tcp_stream.write_eof();
    if (cmd_stream.eof_is_written()){
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
    }
}

void handle_write_tcp(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index != none);
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(cmd_stream.other_index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.other_index == index);

    if (err != 0){
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
        return;
    }

    cmd_stream.partial_read();
}

void handle_write_cmd(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index != none);
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(cmd_stream.other_index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.other_index == index);

    if (err != 0){
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
        return;
    }

    tcp_stream.partial_read();
}

uint_least64_t get_rand64(AppServer& app_server){
    return app_server.PRNG();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AppClient;

struct ConnectedSocketCMD;
struct ConnectedSocketTCP;

struct ClientManager;

ClientManager& get_client_manager(AppClient& app_client);
const sockaddr& get_cmd_addr(AppClient& app_client);
const sockaddr& get_tcp_addr(AppClient& app_client);

void handle_connect_ctl(AppClient& app_server, size_t index, header_t header);
void handle_connect_cmd(AppClient& app_server, size_t index, header_t header);
void handle_connect_tcp(AppClient& app_server, size_t index, header_t header);
void handle_read_ctl(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_cmd(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_tcp(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_ctl(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_cmd(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_tcp(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header);

namespace connected_socket_states{
    enum connected_socket_states{
        fresh, connected, header_written, 
    };
};

struct ClientManager{

    ClientManager(selector_t& selector, AppClient& app_client):
        app_client(app_client),
        stream_pairs(max_connected_sockets),
        selector(selector)
    {
        enable_main();
    }

    std::unique_ptr<
        std::optional<
            ConnectedSocketCMD
        >
    > main_client = std::make_unique<
        std::optional<
            ConnectedSocketCMD
        >
    >();

private:
    AppClient& app_client;

    std::vector<
        std::optional<
            std::pair<
                ConnectedSocketCMD,
                ConnectedSocketTCP
            >
        >
    > stream_pairs;

    selector_t& selector;

public:
    void maybe_open_pair(header_t header);

    void close_pair(size_t index);

    void disable_main();

    void enable_main();

    size_t get_stream_pairs_size(){
        return stream_pairs.size();
    }

    std::pair<
        ConnectedSocketCMD,
        ConnectedSocketTCP
    >* get_stream_pair(size_t i);

};

struct ConnectedSocketCMD{
    ConnectedSocketCMD(selector_t& selector, const sockaddr& addr, size_t index, header_t header, AppClient& app_client):
        selector(selector),
        index(index),
        header(header),
        app_client(app_client),
        s(selector, addr),
        state(connected_socket_states::fresh)
    {
        s.wait_connected(write_handler_ref);
        read_handler.outer = this;
        write_handler.outer = this;
    }

    selector_t& selector;
    size_t index = none;
    header_t header = none;
    AppClient& app_client;
    StreamSocketCompleter s;
    size_t state = none;

    struct ReadHandler{
        ConnectedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        ConnectedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_write(data, size, err);
        }
    } write_handler;

    function_ref<void(const char*, size_t, error_t)> write_handler_ref = write_handler;

    void handle_read(const char* data, size_t size, error_t err){
        if (header == 0){
            handle_read_ctl(app_client, data, size, err, index, header);
        }else{
            handle_read_cmd(app_client, data, size, err, index, header);
        }
    }

    void close_pair(){
        if (header == 0){
            get_client_manager(app_client).disable_main();
        }else{
            get_client_manager(app_client).close_pair(index);
        }
    }

    void handle_write(const char* data, size_t size, error_t err){
        switch (state){
            case connected_socket_states::fresh:
                if (err != 0){
                    close_pair();
                    return;
                }
                assert(s.is_connected());
                state = connected_socket_states::connected;
                char message[CMD_SOCKET_HEADER_SIZE];
                memset(message, 0, sizeof(message));
                static_assert(sizeof(header) <= CMD_SOCKET_HEADER_SIZE);
                memcpy(message, &header, sizeof(header));
                s.full_write(message, sizeof(message), write_handler_ref);
            break;
            case connected_socket_states::connected:
                if (err != 0){
                    close_pair();
                    return;
                }
                assert(size == 0);
                state = connected_socket_states::header_written;
                if (header == 0){
                    handle_connect_ctl(app_client, index, header);
                }else{
                    handle_connect_cmd(app_client, index, header);
                }
            break;
            case connected_socket_states::header_written:
                if (header == 0){
                    handle_write_ctl(app_client, data,size, err, index, header);
                }else{
                    handle_write_cmd(app_client, data,size, err, index, header);
                }
            break;
            default:
                assert(false);
        }
    }

    bool has_read_task(){
        return s.has_read_task();
    }

    bool has_write_task(){
        return s.has_write_task();
    }

    void full_read(size_t len){
        s.full_read(len, read_handler_ref);
    }

    void partial_read(){
        s.partial_read(read_handler_ref);
    }

    void full_write(const char* data, size_t len){
        s.full_write(data, len, write_handler_ref);
    }

    void partial_write(const char* data, size_t len){
        s.partial_write(data, len, write_handler_ref);
    }

    void write_eof(){
        s.write_eof();
    }

    bool eof_is_written(){
        return s.eof_is_written();
    }

    bool is_connected()const{
        return s.is_connected();
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }

    timespec_pair get_last_event(){
        return s.get_last_event();
    }
};

struct ConnectedSocketTCP{
    ConnectedSocketTCP(selector_t& selector, const sockaddr& addr, size_t index, header_t header, AppClient& app_client):
        selector(selector),
        index(index),
        header(header),
        app_client(app_client),
        s(selector, addr),
        state(connected_socket_states::fresh)
    {
        s.wait_connected(write_handler_ref);
        read_handler.outer = this;
        write_handler.outer = this;
    }

    selector_t& selector;
    size_t index;
    header_t header;
    AppClient& app_client;
    StreamSocketCompleter s;
    size_t state = none;

    struct ReadHandler{
        ConnectedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        ConnectedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
            // std::cerr << "Calling user-defined callback from " << __PRETTY_FUNCTION__ << std::endl;
            outer->handle_write(data, size, err);
        }
    } write_handler;

    function_ref<void(const char*, size_t, error_t)> write_handler_ref = write_handler;

    void handle_read(const char* data, size_t size, error_t err){
        handle_read_cmd(app_client, data, size, err, index, header);
    }

    void handle_write(const char* data, size_t size, error_t err){
        handle_write_cmd(app_client, data, size, err, index, header);
    }

    void close_pair(){
        get_client_manager(app_client).close_pair(index);
    }

    bool has_read_task(){
        return s.has_read_task();
    }

    bool has_write_task(){
        return s.has_write_task();
    }

    void full_read(size_t len){
        s.full_read(len, read_handler_ref);
    }

    void partial_read(){
        s.partial_read(read_handler_ref);
    }

    void full_write(const char* data, size_t len){
        s.full_write(data, len, write_handler_ref);
    }

    void partial_write(const char* data, size_t len){
        s.partial_write(data, len, write_handler_ref);
    }

    void write_eof(){
        s.write_eof();
    }

    bool eof_is_written(){
        return s.eof_is_written();
    }

    bool is_connected()const{
        return s.is_connected();
    }

    operator const fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }

    timespec_pair get_last_event(){
        return s.get_last_event();
    }
};

void ClientManager::maybe_open_pair(header_t header){
    for (size_t i = 0; i < stream_pairs.size(); ++i){
        if (stream_pairs[i].has_value()){
            continue;
        }
        stream_pairs[i].emplace(
            std::piecewise_construct,
            std::forward_as_tuple(
                    selector,
                    get_cmd_addr(app_client),
                    i,
                    header,
                    app_client
            ),
            std::forward_as_tuple(
                    selector,
                    get_tcp_addr(app_client),
                    i,
                    header,
                    app_client
            )
        );
        break;
    }
}

void ClientManager::close_pair(size_t index){
    // std::cerr << index << " " << stream_pairs.size() << std::endl;
    assert(index < stream_pairs.size());
    stream_pairs[index].reset();
}

void ClientManager::disable_main(){
    main_client->reset();
}

void ClientManager::enable_main(){
    if (not main_client->has_value()){
        main_client->emplace(selector, get_cmd_addr(app_client), none, 0, app_client);
    }
}

std::pair<
    ConnectedSocketCMD,
    ConnectedSocketTCP
>* ClientManager::get_stream_pair(size_t i){
    assert(i < stream_pairs.size());
    auto& stream_pair = stream_pairs[i];
    return stream_pair.has_value() ? &*stream_pair : nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AppClient{
    selector_t& selector;
    const sockaddr& cmd_addr;
    const sockaddr& tcp_addr;

    ClientManager client;

    AppClient(selector_t& selector, const sockaddr& cmd_addr, const sockaddr& tcp_addr):
        selector(selector),
        cmd_addr(cmd_addr),
        tcp_addr(tcp_addr),
        client(selector, *this)
    {}

    void cleanup(){
        auto current_time = monotonic();
        for (size_t i = 0; i < client.get_stream_pairs_size(); ++i){
            auto stream_pair_ptr = client.get_stream_pair(i);
            if (not stream_pair_ptr){
                continue;
            }
            auto& stream_pair = *stream_pair_ptr;
            if (current_time - stream_pair.first.get_last_event() > connection_timeout){
                client.close_pair(i);
                continue;
            }
            if (current_time - stream_pair.second.get_last_event() > connection_timeout){
                client.close_pair(i);
                continue;
            }
        }
        if (current_time - (*client.main_client)->get_last_event() > connection_timeout){
            client.disable_main();
        }
        client.enable_main();
    }
};

ClientManager& get_client_manager(AppClient& app_client){
    return app_client.client;
}

const sockaddr& get_cmd_addr(AppClient& app_client){
    return app_client.cmd_addr;
}

const sockaddr& get_tcp_addr(AppClient& app_client){
    return app_client.tcp_addr;
}

void handle_connect_ctl(AppClient& app_server, size_t index, header_t header){
    assert(index == none);
    assert(header == 0);
    assert(app_server.client.main_client->has_value());
    auto& main = **app_server.client.main_client;
    main.full_read(CMD_SOCKET_HEADER_SIZE);
}

void handle_read_ctl(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    if (err != 0){
        app_server.client.disable_main();
        return;
    }
    assert(size == CMD_SOCKET_HEADER_SIZE);
    assert(index == none);
    assert(header == 0);
    assert(app_server.client.main_client->has_value());
    auto& main = **app_server.client.main_client;
    static_assert(CMD_SOCKET_HEADER_SIZE <= sizeof(header));
    header = 0;
    assert(size <= sizeof(header));
    memcpy(&header, data, size);
    app_server.client.maybe_open_pair(header);
    main.full_read(CMD_SOCKET_HEADER_SIZE);
}

void handle_write_ctl(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(false);
}

void handle_connect_cmd(AppClient& app_server, size_t index, header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    if (not stream_pair.second.is_connected()){
        return;
    }
    stream_pair.first.partial_read();
    stream_pair.second.partial_read();
}

void handle_connect_tcp(AppClient& app_server, size_t index,  header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.second.is_connected());
    if (not stream_pair.first.is_connected()){
        return;
    }
    stream_pair.second.partial_read();
    stream_pair.first.partial_read();
}

void handle_read_cmd(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());

    if (err != 0){
        app_server.client.close_pair(index);
        return;
    }

    if (size != 0){
        stream_pair.second.full_write(data, size);
        return;
    }

    assert(not stream_pair.second.eof_is_written());
    stream_pair.second.write_eof();
    if (stream_pair.first.eof_is_written()){
        app_server.client.close_pair(index);
    }
}

void handle_read_tcp(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());

    if (err != 0){
        app_server.client.close_pair(index);
        return;
    }

    if (size != 0){
        stream_pair.first.full_write(data, size);
        return;
    }

    assert(not stream_pair.first.eof_is_written());
    stream_pair.first.write_eof();
    if (stream_pair.second.eof_is_written()){
        app_server.client.close_pair(index);
    }
}

void handle_write_cmd(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());

    if (err != 0){
        app_server.client.close_pair(index);
        return;
    }

    assert(size == 0);
    stream_pair.second.partial_read();
}

void handle_write_tcp(AppClient& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_server.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_server.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());

    if (err != 0){
        app_server.client.close_pair(index);
        return;
    }

    assert(size == 0);
    stream_pair.first.partial_read();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fd_owner signal_pipe_owners[] = {signal_pipe[0], signal_pipe[1]};

struct App{
    selector_t selector;

    std::optional<AppServer> app_server;
    std::optional<AppClient> app_client;

    struct Handler{
        void operator()(bool to_write){
            should_exit = true;
        }
    } handler;

    function_ref<void(bool)> handler_ref = handler;

    App(){
        sys.signal(SIGHUP,  handle);
        sys.signal(SIGINT,  handle);
        sys.signal(SIGTERM, handle);
        sys.signal(SIGPIPE, SIG_IGN);

        selector.change_fd_in_pool(signal_pipe_owners[0], &handler_ref, false, false, true, false);

        switch (mode){
            case modes::client:
                app_client.emplace(selector, internal_sockaddr, external_sockaddr);
            break;
            case modes::server:
                app_server.emplace(selector, internal_sockaddr, external_sockaddr);
            break;
            default:
                assert(false);
        }

        timespec_pair last_cleanup = monotonic();
        while (not should_exit){
            timespec_pair current_time = monotonic();
            if (current_time - last_cleanup > clock_interval){
                if (app_client.has_value()){
                    app_client->cleanup();
                }
                if (app_server.has_value()){
                    app_server->cleanup();
                }
                last_cleanup = current_time;
            }
            selector.wait(clock_interval);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// void register_main_stream(AppServer& app_server, size_t index){
//     app_server.main_index = index;
// }

// void handle_accept_tcp(AppServer& app_server, size_t index){

// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct Server{
    
// };


// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct connection_context{
//     uint32_t external_socket;
//     uint32_t internal_socket;
// };

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct AppStorage{
//     selector_t selector;

//     std::vector<
//         std::optional<
//             StreamSocketCompleter
//         >
//     > sockets;

//     std::vector<
//         std::optional<
//             connection_context
//         >
//     > connections;

//     AppStorage():
//         sockets(max_connections*2+2),
//         connections(max_connections)
//     {}
// };

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct InternalServer{
//     AppStorage& app_storage;

//     ServerSocketCompleter server;
    
//     uint32_t client;

//     struct AcceptHandler{
//         InternalServer* outer;
//         void operator()(error_t err){
//             outer->handle_accept(err);
//         }
//     } accept_handler;

//     function_ref<void(error_t)> accept_handler_ref = accept_handler;

//     void handle_accept(error_t err){
//         auto socket_ptr = app_storage.sockets.end();
//         for (auto sock_ptr = app_storage.sockets.begin(); sock_ptr != app_storage.sockets.end(); ++sock_ptr){
//             if (not sock_ptr->has_value()){
//                 socket_ptr = sock_ptr;
//                 break;
//             }
//         }
//         assert(socket_ptr != app_storage.sockets.end());
//         socket_ptr->emplace(app_storage.selector, server);
//         auto& client = **socket_ptr;
//         client
//     }

//     InternalServer(AppStorage& app_storage, const sockaddr& addr):
//         app_storage(app_storage),
//         server(app_storage.selector, addr)
//     {
//         accept_handler.outer = this;
//         server.accept(accept_handler_ref);
//     }
// };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct ExternalServer{

//     ExternalServer(AppStorage& app_storage, const sockaddr& addr):
//         app_storage(app_storage),
//         s(app_storage.selector, addr)
//     {
//         accept_handler.outer = this;
//         s.accept(accept_handler_ref);
//     }

// private:
//     AppStorage& app_storage;

//     ServerSocketCompleter s;

//     struct AcceptHandler{
//         ExternalServer* outer;
//         void operator()(error_t err){
//             outer->handle_accept(err);
//         }
//     } accept_handler;

//     function_ref<void(error_t)> accept_handler_ref = accept_handler;

//     void handle_accept(error_t err){
//         std::optional<connection_context>* connection_ptr = nullptr;

//         for (std::optional<connection_context>& connection: app_storage.connections){
//             if (not connection.has_value()){
//                 connection_ptr = &connection;
//             }
//         }

//         if (connection_ptr == nullptr){
//             StreamSocketCompleter client(app_storage.selector, *this);
//         }

//         connection_ptr->emplace();

//         connection_context& context = **connection_ptr;

//         context.external_socket.emplace(app_storage.selector, s);

//         // todo
//     }

// public:

//     operator const fd_owner&(){
//         return s;
//     }

//     operator sockaddr()const{
//         return s;
//     }
// };


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Struct 

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//     struct CmdMainClientOneConnectionAttempt{
//         App& app;

//         stream_socket_owner connection;

//         struct Handler{
//             void operator()(bool to_write){

//             }
//         } handler;

//         function_ref<void(bool)> handler_ref = handler;

//         CmdMainClientOneConnectionAttempt(App& app, const sockaddr& addr):
//             app(app),
//             connection(stream_socket_owner(addr))
//         {
//             app.selector.change_fd_in_pool(connection, &handler_ref, false, false, false, true);
//         }
//     };

//     struct CmdMainCleint{
//         App& app;

//         std::optional<stream_socket_owner> connection;

//         CmdMainClient(App& app, const sockaddr& addr):
//             app(app)
//         {}
//     };
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//     template<typename Callback>
//     struct TcpServer{
//         App& app;
//         server_socket_owner server;

//         Callback callback;

//         struct AcceptHandler{
//             TcpServer* server;
//             void operator()(bool){
//                 callback(server);
//             }
//         } accept_handler;

//         function_ref<void(bool)> accept_handler_ref = accept_handler;

//         TcpServer(Callback callback, App& app, const sockaddr& addr):
//             app(app),
//             server(server_socket_owner::start_server(addr)),
//             callback(callback)
//         {
//             accept_handler.server = this;
//             app.selector.change_fd_in_pool(server, &accept_handler_ref, false, false, true, false);
//         }
//     };

//     struct CmdClient{
//         App& app;

//         CmdClient(App& app){

//         }
//     };

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// struct App{
//     App(App&&) = delete;
//     App(const App&) = delete;

//     selector_t selector;

//     std::vector<
//         std::optional<
//             two_sockets
//         >
//     > socket_pairs;

//     App():
//         socket_pairs(max_connections)
//     {
//         sys.signal(SIGHUP,  handle);
//         sys.signal(SIGINT,  handle);
//         sys.signal(SIGTERM, handle);
//         sys.signal(SIGPIPE, SIG_IGN);

//         assert(mode == modes::server or mode == modes::client);

//         std::optional<CmdServer> internal_server;
//         std::optional<CmdServer> internal_client;
//         std::optional<TcpServer> external_server;

//         if (mode == modes::server){
//             internal_server.emplace(*this, internal_sockaddr);
//             external_server.emplace(*this, external_sockaddr);
//         }else{
//             internal_client.emplace(*this, internal_sockaddr);
//         }

//         while (1)
//         {
//             selector.wait();
//         }


//     }
// };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<const char*> args;

bool has_missing_flags = false;

template<typename T, typename F>
void argv_initializer(T& value, const char* name, F f){
    std::string flag = "--";
    flag += name;
    for (size_t i = 2 ; i < args.size(); ++i){
        if (args[i-1] == flag){
            value = f(args[i]);
            return;
        }
    }
    std::cerr << "Missing flag: " << flag << std::endl;
    has_missing_flags = true;
}


#define init_by_argv(name, f) argv_initializer(name, #name, f)

size_t read_file(const char* filename, char* data, size_t size){
    int fd = sys.open(filename, O_RDONLY);
    defer closer([&](){
        sys.close(fd);
    });
    size_t still_has_to_read = size;
    size_t readen = none;
    while (still_has_to_read != 0 and readen != 0){
        readen = sys.read(fd, data + size - still_has_to_read, still_has_to_read);
        still_has_to_read -= readen;
    }
    return size - still_has_to_read;
}

int main(int argc, char**argv){
    args = decltype(args)(argv, argv + argc);
    init_by_argv(mode, [](auto&& s){
        if (strcmp(s, "server") == 0){return modes::server;}
        if (strcmp(s, "client") == 0){return modes::client;}
        throw std::runtime_error{"modes: client|server"};
    });

    // init_by_argv(max_connections, atoll);
    init_by_argv(connection_timeout, ([](const char* s){
        auto v = strtold(s, nullptr);
        timespec_pair res = {none, none};
        res.first = v;
        res.second = (v - res.first) * timespec_base;
        return res;
    }));
    init_by_argv(clock_interval, ([](const char* s){
        auto v = strtold(s, nullptr);
        timespec_pair res = {none, none};
        res.first = v;
        res.second = (v - res.first) * timespec_base;
        return res;
    }));
    init_by_argv(max_accepted_sockets_per_server, atoll);
    init_by_argv(max_connected_sockets, atoll);

    init_by_argv(first_bytes_filename, [](const char* s){return s;});

    init_by_argv(internal_port, atoll);
    init_by_argv(internal_host, [](const char* s){return s;});

    init_by_argv(external_port, atoll);
    init_by_argv(external_host, [](const char* s){return s;});

    if (has_missing_flags){
        exit(1);
    }

    first_bytes_size = read_file(first_bytes_filename, first_bytes_data, sizeof(first_bytes_data));
    internal_sockaddr = host_port_to_sockaddr(internal_host, internal_port);
    external_sockaddr = host_port_to_sockaddr(external_host, external_port);

    App app;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// int main() {
//     sys.signal(SIGHUP,  handle);
//     sys.signal(SIGINT,  handle);
//     sys.signal(SIGTERM, handle);

//     #ifdef use_kqueue
//     kqueue_selector sel;
//     #endif

//     #ifdef use_epoll
//     epoll_selector sel;
//     #endif

//     sel.async_read(signal_pipe[0], [&](){
//         has_to_stop = true;
//     });

//     start_server(sel, "0.0.0.0", 9999, [&](auto a, const char*addr, uint16_t port){
//         std::cerr << "connected " << addr << ":" << port << std::endl;
//         auto c = create_connecting_socket("127.0.0.1", 8888);
//         sel.async_write(c, [&sel, a, c]()mutable{
//             auto&& setup_mover = [&sel](socket_ptr r, socket_ptr w){
//                 struct connection_ctx{
//                     socket_ptr r;
//                     socket_ptr w;
//                     std::array<char, 65536> data;
//                     size_t begin;
//                     size_t end;
//                     function<void()> reader;
//                     function<void()> writer;
//                     std::unique_ptr<connection_ctx>* reader_ctx;
//                     std::unique_ptr<connection_ctx>* writer_ctx;
//                     connection_ctx(const connection_ctx&) = delete;
//                     connection_ctx(connection_ctx&&) = delete;
//                     connection_ctx() = default;
//                     connection_ctx&operator=(const connection_ctx&) = delete;
//                     connection_ctx&operator=(connection_ctx&&) = delete;
//                 };
//                 auto ctx = std::make_unique<connection_ctx>();
//                 std::memset(&ctx->data, 0, sizeof(ctx->data));
//                 ctx->begin = 0;
//                 ctx->end = 0;
//                 ctx->r = r;
//                 ctx->w = w;
//                 ctx->reader = std::move([&sel, ctx_ = decltype(ctx)(), ctx_ptr = &ctx->reader_ctx]()mutable{
//                     *ctx_ptr = &ctx_;
//                     connection_ctx* ctx = ctx_.get();
//                     if (not ctx){
//                         std::cerr << "no ctx" << std::endl;
//                         return;
//                     }
//                     assert(ctx->writer);
//                     assert(not ctx->reader);
//                     ctx->reader = std::move(*Task::current);
//                     assert(ctx->begin == ctx->end);
//                     ctx->begin = 0;
//                     ctx->end = sys.read(ctx->r, ctx->data.data(), ctx->data.size());
//                     if (ctx->end == 0){
//                         sys.ignore(ENOTCONN);
//                         sys.shutdown(ctx->r, SHUT_RD);
//                         sys.ignore(ENOTCONN);
//                         sys.shutdown(ctx->w, SHUT_WR);
//                         std::cerr << "EOF " << ctx->r << std::endl;
//                         std::cerr << ctx->r << ".use_count = " << ctx->r.ptr.use_count() << std::endl;
//                         std::cerr << ctx->w << ".use_count = " << ctx->w.ptr.use_count() << std::endl;
//                         auto r = ctx->r;
//                         auto w = ctx->w;
//                         std::cerr << r << ".use_count = " << r.ptr.use_count() << std::endl;
//                         std::cerr << w << ".use_count = " << w.ptr.use_count() << std::endl;
//                         ctx_.reset();
//                         std::cerr << r << ".use_count = " << r.ptr.use_count() << std::endl;
//                         std::cerr << w << ".use_count = " << w.ptr.use_count() << std::endl;
//                         r.ptr.reset();
//                         w.ptr.reset();
//                         std::cerr << 0 << ".use_count = " << r.ptr.use_count() << std::endl;
//                         std::cerr << 0 << ".use_count = " << w.ptr.use_count() << std::endl;
//                         return;
//                     }
//                     assert(0 <= ctx->begin);
//                     assert(ctx->begin < ctx->end);
//                     assert(ctx->end <= ctx->data.size());
//                     *ctx->writer_ctx = std::move(ctx_);
//                     sel.async_write(ctx->w, std::move(ctx->writer));
//                 });
//                 ctx->reader();
//                 ctx->writer = std::move([&sel, ctx_ = decltype(ctx)(), ctx_ptr = &ctx->writer_ctx]()mutable{
//                     *ctx_ptr = &ctx_;
//                     connection_ctx* ctx = ctx_.get();
//                     if (not ctx){
//                         std::cerr << "no ctx" << std::endl;
//                         return;
//                     }
//                     assert(ctx->reader);
//                     assert(not ctx->writer);
//                     ctx->writer = std::move(*Task::current);
//                     assert(0 <= ctx->begin);
//                     assert(ctx->begin < ctx->end);
//                     assert(ctx->end <= ctx->data.size());
//                     ctx->begin += sys.write(ctx->w, ctx->data.data() + ctx->begin, ctx->end - ctx->begin);
//                     assert(0 <= ctx->begin);
//                     assert(ctx->begin <= ctx->end);
//                     assert(ctx->end <= ctx->data.size());
//                     if (ctx->begin == ctx->end){
//                         *ctx->reader_ctx = std::move(ctx_);
//                         sel.async_read(ctx->r, std::move(ctx->reader));
//                     }else{
//                         sel.async_write(ctx->r, std::move(ctx->writer));
//                     }
//                 });
//                 ctx->writer();
//                 assert(ctx->writer_ctx);
//                 assert(ctx->reader_ctx);
//                 auto ctx_ = ctx.get();
//                 *ctx->reader_ctx = std::move(ctx);
//                 sel.async_read(ctx_->r, std::move(ctx_->reader));
//             };
//             setup_mover(a,c);
//             setup_mover(c,a);
//         });
//     });

//     sel.async_wait({1, 0}, [&](){
//         std::cerr << "hello" << std::endl;
//         sel.async_wait({1, 0}, std::move(*Task::current));
//     });


//     sel.loop();

// }




// // #include <iostream>
// // #include <vector>
// // #include <map>
// // #include <unordered_map>
// // #include <algorithm>
// // #include <cstring>
// // #include <cstdlib>
// // #include <csignal>
// // #include <cerrno>
// // #include <unistd.h>
// // #include <fcntl.h>
// // #include <netinet/in.h>
// // #include <sys/socket.h>
// // #include <sys/types.h>
// // #include <sys/epoll.h>
// // #include <arpa/inet.h>
// // #include <ctime>

// // struct sys_msg_printer : std::stringstream {
// //     std::unordered_set<int> ignored;
// //     void ignore(int err){
// //         ignored.insert(err);
// //     }


// //     add_syscall(shutdown)
// //     add_syscall(write)
// //     add_syscall(read)
// //     add_syscall(close)
// //     add_syscall(socket)
// //     add_syscall(fcntl)
// //     add_syscall(inet_pton)
// //     add_syscall(inet_ntop)
// //     add_syscall(eassert)
// //     add_syscall(connect)
// //     add_syscall(bind)
// //     add_syscall(listen)
// //     add_syscall(accept)
// //     add_syscall(signal)
// //     add_syscall(clock_gettime)
// //     add_syscall(pipe)
// // #ifdef use_kqueue
// //     add_syscall(kqueue)
// //     add_syscall(kevent)
// // #endif
// // #ifdef use_epoll
// //     add_syscall(epoll_ctl)
// //     add_syscall(epoll_wait)
// //     add_syscall(epoll_pwait)
// //     add_syscall(epoll_create)
// //     add_syscall(epoll_create1)
// // #endif
// // } sys;


// // #define MAX_EVENTS 1024
// // #define BUFFER_SIZE 8192

// // enum Mode {
// //     MODE_SERVER,
// //     MODE_CLIENT
// // };

// // struct Conn {
// //     int internal_fd = -1;
// //     int external_fd = -1;
// //     char buffer[BUFFER_SIZE];
// //     size_t buf_len = 0;
// //     size_t buf_sent = 0;
// //     bool has_internal_eof = false;
// //     bool has_external_eof = false;
// //     time_t last_activity = 0;
// // };

// // struct Config {
// //     Mode mode;
// //     const char* internal_host;
// //     const char* internal_port;
// //     const char* external_host;
// //     const char* external_port;
// //     size_t max_connections;
// //     size_t timeout_seconds;
// // };

// // int set_nonblocking(int fd) {
// //     int flags = fcntl(fd, F_GETFL, 0);
// //     if (flags == -1) return -1;
// //     return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
// // }

// // void log(const std::string& msg) {
// //     std::cerr << "[" << time(nullptr) << "] " << msg << std::endl;
// // }

// // int create_and_bind(const std::string& host, uint16_t port) {
// //     int fd = socket(AF_INET, SOCK_STREAM, 0);
// //     if (fd < 0) return -1;
// //     sockaddr_in addr{};
// //     addr.sin_family = AF_INET;
// //     addr.sin_port = htons(port);
// //     if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) return -1;
// //     int reuse = 1;
// //     setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
// //     if (bind(fd, (sockaddr*)&addr, sizeof(addr)) < 0) return -1;
// //     return fd;
// // }

// // int create_and_connect(const std::string& host, uint16_t port) {
// //     int fd = socket(AF_INET, SOCK_STREAM, 0);
// //     if (fd < 0) return -1;
// //     set_nonblocking(fd);
// //     sockaddr_in addr{};
// //     addr.sin_family = AF_INET;
// //     addr.sin_port = htons(port);
// //     if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) return -1;
// //     connect(fd, (sockaddr*)&addr, sizeof(addr)); // non-blocking connect
// //     return fd;
// // }

// // class Forwarder {
// // public:
// //     Forwarder(const Config& config): config(config) {
// //         epoll_fd = epoll_create1(0);
// //         if (epoll_fd < 0) {
// //             perror("epoll_create1");
// //             exit(1);
// //         }
// //     }

// //     void run();

// // private:
// //     Config config;
// //     int epoll_fd;
// //     std::unordered_map<int, Conn> connections;
// //     std::vector<epoll_event> events;

// //     void add_epoll_fd(int fd, uint32_t events);
// //     void modify_epoll_fd(int fd, uint32_t events);
// //     void delete_epoll_fd(int fd);
// //     void close_connection(int fd);
// //     void accept_connection(int listen_fd);
// //     void handle_read(int fd);
// //     void handle_write(int fd);
// //     void transfer_data(int from_fd);
// //     void update_timeout(int fd);
// //     void check_timeouts();
// // };

// // void Forwarder::add_epoll_fd(int fd, uint32_t ev) {
// //     epoll_event e{};
// //     e.events = ev;
// //     e.data.fd = fd;
// //     if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &e) < 0) {
// //         perror("epoll_ctl add");
// //         exit(1);
// //     }
// // }

// // void Forwarder::modify_epoll_fd(int fd, uint32_t ev) {
// //     epoll_event e{};
// //     e.events = ev;
// //     e.data.fd = fd;
// //     if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &e) < 0) {
// //         perror("epoll_ctl mod");
// //         exit(1);
// //     }
// // }

// // void Forwarder::delete_epoll_fd(int fd) {
// //     epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
// // }

// // void Forwarder::close_connection(int fd) {
// //     auto it = connections.find(fd);
// //     if (it == connections.end()) return;
// //     int peer = it->second.peer_fd;
// //     log("Closing connection: " + std::to_string(fd) + " <-> " + std::to_string(peer));
// //     delete_epoll_fd(fd);
// //     close(fd);
// //     connections.erase(it);
// //     if (connections.find(peer) != connections.end()) {
// //         delete_epoll_fd(peer);
// //         close(peer);
// //         connections.erase(peer);
// //     }
// // }

// // void Forwarder::run() {
// //     events.resize(MAX_EVENTS);
// //     log("Forwarder running in mode: " + std::string(config.mode == MODE_SERVER ? "server" : "client"));

// //     int listen_fd = create_and_bind(config.listen_host, config.listen_port);
// //     if (listen_fd < 0) {
// //         perror("bind failed");
// //         exit(1);
// //     }
// //     set_nonblocking(listen_fd);
// //     listen(listen_fd, SOMAXCONN);
// //     add_epoll_fd(listen_fd, EPOLLIN);

// //     while (true) {
// //         int nfds = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, 1000);
// //         if (nfds < 0) {
// //             if (errno == EINTR) continue;
// //             perror("epoll_wait");
// //             break;
// //         }
// //         for (int i = 0; i < nfds; ++i) {
// //             int fd = events[i].data.fd;
// //             uint32_t ev = events[i].events;
// //             if (fd == listen_fd) {
// //                 accept_connection(listen_fd);
// //             } else {
// //                 if (ev & EPOLLIN) handle_read(fd);
// //                 if (ev & EPOLLOUT) handle_write(fd);
// //                 if (ev & (EPOLLHUP | EPOLLERR)) close_connection(fd);
// //             }
// //         }
// //         check_timeouts();
// //     }
// //     close(listen_fd);
// // }

// // void Forwarder::accept_connection(int listen_fd) {
// //     sockaddr_in client_addr;
// //     socklen_t client_len = sizeof(client_addr);
// //     int client_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_len);
// //     if (client_fd < 0) {
// //         perror("accept");
// //         return;
// //     }
// //     set_nonblocking(client_fd);

// //     int target_fd = create_and_connect(config.remote_host, config.remote_port);
// //     if (target_fd < 0) {
// //         log("Failed to connect to remote");
// //         close(client_fd);
// //         return;
// //     }

// //     Conn c1 = {client_fd, target_fd, {}, 0, 0, false, false, time(nullptr)};
// //     Conn c2 = {target_fd, client_fd, {}, 0, 0, false, false, time(nullptr)};

// //     connections[client_fd] = c1;
// //     connections[target_fd] = c2;

// //     add_epoll_fd(client_fd, EPOLLIN);
// //     add_epoll_fd(target_fd, EPOLLIN);

// //     log("Accepted and connected: " + std::to_string(client_fd) + " <-> " + std::to_string(target_fd));
// // }

// // // CONTINUE IN NEXT CHUNK
// // // This part of code stays the same

// // void Forwarder::handle_read(int fd) {
// //     auto& conn = connections[fd];
// //     ssize_t n = read(fd, conn.buffer, BUFFER_SIZE);
// //     if (n < 0) {
// //         if (errno != EAGAIN && errno != EWOULDBLOCK) {
// //             perror("read");
// //             close_connection(fd);
// //         }
// //         return;
// //     } else if (n == 0) {
// //         log("EOF received on fd " + std::to_string(fd));
// //         conn.eof_received = true;
// //         shutdown(conn.peer_fd, SHUT_WR);
// //         if (conn.buf_len == conn.buf_sent) {
// //             close_connection(fd);
// //         }
// //         return;
// //     }

// //     conn.buf_len = n;
// //     conn.buf_sent = 0;
// //     modify_epoll_fd(conn.peer_fd, EPOLLOUT | EPOLLIN);
// //     update_timeout(fd);
// //     update_timeout(conn.peer_fd);
// // }

// // void Forwarder::handle_write(int fd) {
// //     auto& conn = connections[fd];
// //     auto& peer = connections[conn.peer_fd];

// //     while (peer.buf_sent < peer.buf_len) {
// //         ssize_t n = write(fd, peer.buffer + peer.buf_sent, peer.buf_len - peer.buf_sent);
// //         if (n < 0) {
// //             if (errno != EAGAIN && errno != EWOULDBLOCK) {
// //                 perror("write");
// //                 close_connection(fd);
// //             }
// //             return;
// //         }
// //         peer.buf_sent += n;
// //     }

// //     if (peer.buf_sent == peer.buf_len) {
// //         peer.buf_len = 0;
// //         peer.buf_sent = 0;
// //         if (peer.eof_received) {
// //             log("EOF fully forwarded, closing " + std::to_string(peer.fd));
// //             close_connection(peer.fd);
// //             return;
// //         }
// //         modify_epoll_fd(fd, EPOLLIN);
// //     }

// //     update_timeout(fd);
// //     update_timeout(peer.fd);
// // }

// // void Forwarder::update_timeout(int fd) {
// //     if (connections.find(fd) != connections.end()) {
// //         connections[fd].last_activity = time(nullptr);
// //     }
// // }

// // void Forwarder::check_timeouts() {
// //     time_t now = time(nullptr);
// //     std::vector<int> to_close;
// //     for (auto& [fd, conn] : connections) {
// //         if (now - conn.last_activity >= config.timeout_seconds) {
// //             log("Timeout on fd " + std::to_string(fd));
// //             to_close.push_back(fd);
// //         }
// //     }
// //     for (int fd : to_close) close_connection(fd);
// // }

// // // CONTINUE IN NEXT CHUNK

// // // This part of code stays the same

// // int parse_port(const char* str) {
// //     int port = std::atoi(str);
// //     if (port < 1 || port > 65535) {
// //         std::cerr << "Invalid port: " << str << std::endl;
// //         exit(1);
// //     }
// //     return port;
// // }

// // void print_usage(const char* prog) {
// //     std::cerr << "Usage:\n"
// //               << prog << " server <listen_host> <listen_port> <remote_host> <remote_port> <max_conn> <timeout>\n"
// //               << prog << " client <connect_host> <connect_port> <forward_host> <forward_port> <max_conn> <timeout>\n";
// //     exit(1);
// // }

// // int main(int argc, char* argv[]) {
// //     if (argc < 8) print_usage(argv[0]);

// //     Config config{};
// //     std::string mode = argv[1];
// //     if (mode == "server") {
// //         config.mode = MODE_SERVER;
// //         config.listen_host = argv[2];
// //         config.listen_port = parse_port(argv[3]);
// //         config.remote_host = argv[4];
// //         config.remote_port = parse_port(argv[5]);
// //         config.max_connections = std::atoi(argv[6]);
// //         config.timeout_seconds = std::atoi(argv[7]);
// //     } else if (mode == "client") {
// //         config.mode = MODE_CLIENT;
// //         config.listen_host = argv[4];
// //         config.listen_port = parse_port(argv[5]);
// //         config.remote_host = argv[2];
// //         config.remote_port = parse_port(argv[3]);
// //         config.max_connections = std::atoi(argv[6]);
// //         config.timeout_seconds = std::atoi(argv[7]);
// //     } else {
// //         print_usage(argv[0]);
// //     }

// //     log("Starting reverse TCP forwarder");
// //     Forwarder fwd(config);
// //     fwd.run();
// //     return 0;
// // }
