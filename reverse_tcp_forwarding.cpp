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
    static auto repr(auto&& val) {
        std::stringstream a;
        a << FORWARD(val);
        return repr_s(a.str());
    }
};

template<typename R, typename...A>
struct repr_m<R(&)(A...)>{
    static auto repr(auto&& val) {
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
    auto name(auto&&... args) {                                          \
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

    operator bool() const noexcept {
        return invoker_ != nullptr;
    }

    void reset(){
        std::destroy_at(this);
        std::construct_at(this);
    }
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

size_t max_connections = 0LLU-1;
size_t connection_timeout = 0LLU-1;

size_t internal_port = 0LLU-1;
const char* internal_host = nullptr;
sockaddr internal_sockaddr;

size_t external_port = 0LLU-1;
const char* external_host = nullptr;
sockaddr external_sockaddr;

namespace modes{
    enum modes{ server, client};
};

uint32_t mode = 0LLU-1;

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
    operator fd_owner&(){
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
    operator fd_owner&(){
        return s;
    }
    operator sockaddr()const{
        return s;
    }
    void shut_rd(){
        if (not shut_rd_){
            sys.shutdown(s, SHUT_RD);
            shut_rd_ = true;
        }
    }
    void shut_wr(){
        if (not shut_rd_){
            sys.shutdown(s, SHUT_WR);
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
    stream_socket_owner(fd_owner& server):
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
    operator fd_owner&(){
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

    void change_fd_in_pool(fd_owner& fd, Callback* callback, bool old_read, bool old_write, bool new_read, bool new_write){
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
        new_event.data.ptr = &callback;

        if (new_read){
            new_event.events |= EPOLLIN;
        }

        if (new_write){
            new_event.events |= EPOLLOUT;
        }

        sys.epoll_ctl(pool_fd, op, get_fd(fd), &new_event);
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
            get_fd(s),
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

        for (size_t q = 0; q < events_to_process.second; ++q){
            auto& event = events_to_process.first[q];
            print_event(event);
        }

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

    bool has_write_task = false;
    external_callback write_callback;

    bool has_read_task = false;
    external_callback read_callback;

    struct Handler{
        SplitCallbacks* outer;
        void operator()(bool to_write){
            outer->handle(to_write);
        }
    } handler;

    function_ref<void(bool)> handler_ref = handler;

    void handle(bool to_write){
        auto err = get_errno(s);
        if (err != 0){
            has_err = true;
        }
        if (to_write){
            auto write_callback_local = write_callback;
            write_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, has_read_task, true, has_read_task, false);
            has_write_task = false;
            write_callback_local(err);
        }else{
            auto read_callback_local = read_callback;
            read_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, true, has_write_task, false, has_write_task);
            has_read_task = false;
            read_callback_local(err);
        }
    }

public:
    void wait_read(external_callback callback){
        assert(not has_err);
        assert(not read_callback);
        assert(not has_read_task);
        selector.change_fd_in_pool(s, &handler_ref, false, has_write_task, true, has_write_task);
        read_callback = callback;
        has_read_task = true;
    }

    void wait_write(external_callback callback){
        assert(not has_err);
        assert(not write_callback);
        assert(not has_write_task);
        selector.change_fd_in_pool(s, &handler_ref, has_read_task, false, has_read_task, true);
        write_callback = callback;
        has_write_task = true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StreamSocketCompleter{

    StreamSocketCompleter(selector_t& selector, const sockaddr& addr):
        s(addr),
        c(selector, s),
        connected(false)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

    StreamSocketCompleter(selector_t& selector, fd_owner& server):
        s(server),
        c(selector, s),
        connected(true)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

private:
    stream_socket_owner s;
    SplitCallbacks<stream_socket_owner> c;

    using external_rw_callback = function_ref<void(const char*, size_t, error_t)>;
    using external_connected_callback = function_ref<void(error_t)>;

    bool connected = false;
    external_connected_callback connected_callback;

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
            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    struct WriteHandler{
        StreamSocketCompleter* outer;
        void operator()(error_t err){
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
        read_callback_local(read_buffer.data(), len_of_data_in_read_buffer, err);
    }

    void handle_write(error_t err){
        if (not connected){
            if (err == 0){
                connected = true;
            }
            auto connected_callback_local = connected_callback;
            connected_callback.reset();
            connected_callback(err);
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
        write_callback_local(write_buffer.data() + len_of_data_in_write_buffer_local - still_has_to_write_local, still_has_to_write_local, err);
    }

public:
    void full_read(size_t len, external_rw_callback callback){
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        assert(len <= read_buffer.size());
        c.wait_read(read_handler_ref);
        read_callback = callback;
        has_full_read_task = true;
        still_has_to_read = len;
    }

    void partial_read(external_rw_callback callback){
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        c.wait_read(read_handler_ref);
        read_callback = callback;
    }

    void full_write(const char* data, size_t len, external_rw_callback callback){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        c.wait_write(write_handler_ref);
        memmove(write_buffer.data(), data, len);
        write_callback = callback;
        has_full_write_task = true;
        still_has_to_write = len;
    }

    void partial_write(const char* data, size_t len, external_rw_callback callback){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        c.wait_write(write_handler_ref);
        memmove(write_buffer.data(), data, len);
        write_callback = callback;
        still_has_to_write = len;
    }

    void write_eof(){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        s.shut_wr();
    }

    void wait_connected(external_rw_callback callback){
        assert(not connected);
        c.wait_write(write_handler_ref);
    }

    operator fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
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
    SplitCallbacks<server_socket_owner> c;
    server_socket_owner s;

    using external_callback = function_ref<void(error_t)>;
    external_callback accept_callback;

    struct ReadHandler{
        ServerSocketCompleter* outer;
        void operator()(error_t err){
            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    void handle_read(error_t err){
        accept_callback(err);
    }

public:
    void accept(external_callback callback){
        accept_callback = callback;
        c.wait_read(read_handler_ref);
    }

    operator fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct connection_context{
    StreamSocketCompleter* external_socket;
    StreamSocketCompleter* internal_socket;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AppStorage{
    selector_t selector;

    std::vector<
        std::optional<
            StreamSocketCompleter
        >
    > sockets;

    std::vector<
        std::optional<
            connection_context
        >
    > connections;

    AppStorage():
        sockets(max_connections*2+2),
        connections(max_connections)
    {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct InternalServer{
    AppStorage& app_storage;

    ServerSocketCompleter s;
    
    std::optional<StreamSocketCompleter> c;

    struct AcceptHandler{
        InternalServer* outer;
        void operator()(error_t err){
            outer->handle_accept(err);
        }
    } accept_handler;

    function_ref<void(error_t)> accept_handler_ref = accept_handler;

    void handle_accept(error_t err){
        c.emplace(app_storage.selector, s);

    }

    InternalServer(AppStorage& app_storage, const sockaddr& addr):
        app_storage(app_storage),
        s(app_storage.selector, addr)
    {
        accept_handler.outer = this;
        s.accept(accept_handler_ref);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ExternalServer{

    ExternalServer(AppStorage& app_storage, const sockaddr& addr):
        app_storage(app_storage),
        s(app_storage.selector, addr)
    {
        accept_handler.outer = this;
        s.accept(accept_handler_ref);
    }

private:
    AppStorage& app_storage;

    ServerSocketCompleter s;

    struct AcceptHandler{
        ExternalServer* outer;
        void operator()(error_t err){
            outer->handle_accept(err);
        }
    } accept_handler;

    function_ref<void(error_t)> accept_handler_ref = accept_handler;

    void handle_accept(error_t err){
        std::optional<connection_context>* connection_ptr = nullptr;

        for (std::optional<connection_context>& connection: app_storage.connections){
            if (not connection.has_value()){
                connection_ptr = &connection;
            }
        }

        if (connection_ptr == nullptr){
            StreamSocketCompleter client(app_storage.selector, *this);
        }

        connection_ptr->emplace();

        connection_context& context = **connection_ptr;

        context.external_socket.emplace(app_storage.selector, s);

        // todo
    }

public:

    operator fd_owner&(){
        return s;
    }

    operator sockaddr()const{
        return s;
    }
};


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

int main(int argc, char**argv){
    args = decltype(args)(argv, argv + argc);
    init_by_argv(mode, [](auto&& s){
        if (s=="server"){return modes::server;}
        if (s=="client"){return modes::client;}
        throw std::runtime_error{"modes: client|server"};
    });

    init_by_argv(max_connections, atoll);
    init_by_argv(connection_timeout, atoll);

    init_by_argv(internal_port, atoll);
    init_by_argv(internal_host, [](const char* s){return s;});
    internal_sockaddr = host_port_to_sockaddr(internal_host, internal_port);

    init_by_argv(external_port, atoll);
    init_by_argv(external_host, [](const char* s){return s;});
    external_sockaddr = host_port_to_sockaddr(external_host, external_port);

    if (has_missing_flags){
        exit(1);
    }

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

// // #define add_syscall(name)                                                \
// //     auto name(auto&&... args) {                                          \
// //         errno = 0;                                                       \
// //         auto ret = ::name(FORWARD(args)...);                             \
// //         int err = errno;                                             \
// //         if (err and not ignored.count(err)) {                            \
// //             std::cerr << "\n <<< ERROR >>>\n";                           \
// //             std::cerr << "    " #name " Failed\n";                       \
// //             std::cerr << "    code = " << err << "\n";                   \
// //             std::cerr << "    text = " << std::strerror(err) << "\n";    \
// //             std::cerr << "\n <<< ARGS >>> " << std::endl;                \
// //             (void)((std::cerr << "    " << repr(args) << "\n"), ..., 0); \
// //             if (str().size()) {                                          \
// //                 std::cerr << "\n <<< MESSAGE >>> " << std::endl;         \
// //                 std::cerr << str() << std::endl;                         \
// //             }                                                            \
// //             std::cerr << std::endl;                                      \
// //             throw std::runtime_error("syscall failed");                  \
// //         }                                                                \
// //         std::stringstream tmp;                                           \
// //         swap(tmp);                                                       \
// //         ignored.clear();                                                 \
// //         return ret;                                                      \
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
