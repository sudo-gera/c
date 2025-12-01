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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TO_STR_INTERNAL(x) #x
#define TO_STR(x) TO_STR_INTERNAL(x)

#define FORWARD(val) (std::forward<decltype(val)>(val))
#define VALUE_AS_STRING_AND_VALUE(x) #x << "\t\t\t\t" << x

#define BUFFER_SIZE 8192
#define none 0x5555'5555'5555'5555

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, size_t len_>
struct static_trivial_multiset{
    static_assert(std::is_trivial_v<T>);
    void insert(T value){
        assert(size_ < len_);
        data[size_] = value;
        size_ += 1;
    }
    void clear(){
        size_ = 0;
    }
    size_t count(T value){
        size_t n = 0;
        for (size_t i = 0; i < size_; ++i){
            if (data[i] == value){
                n += 1;
            }
        }
        return n;
    }
private:
    std::array<T, len_> data;
    size_t size_ = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct sys_msg_printer : std::stringstream {
    static_trivial_multiset<int, 64> ignored;
    int last_err = 0;
    // std::unordered_set<int> ignored;
    void ignore(int err){
        ignored.insert(err);
    }

#define add_syscall(name)                                                \
    template<typename...ARGS>                                            \
    auto name(ARGS&&... args) {                                          \
        errno = 0;                                                       \
        auto ret = ::name(FORWARD(args)...);                             \
        last_err = errno;                                                \
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
    add_syscall(connect)
    add_syscall(bind)
    add_syscall(listen)
    add_syscall(accept)
    add_syscall(signal)
    add_syscall(clock_gettime)
    add_syscall(pipe)
    add_syscall(getsockopt)
    add_syscall(setsockopt)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
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
    while (not *p)
    {
        ++p;
    }

}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using timespec_first_t = decltype(std::declval<struct timespec>().tv_sec);
using timespec_second_t = decltype(std::declval<struct timespec>().tv_nsec);

static_assert(std::is_integral_v<timespec_first_t>);
static_assert(std::is_integral_v<timespec_second_t>);

static_assert(sizeof(timespec_first_t) <= sizeof(size_t));
static_assert(sizeof(timespec_second_t) <= sizeof(size_t));

#define timespec_base (size_t(1'000'000'000))

struct time_storage;

bool operator<(const time_storage&, const time_storage&);
bool operator>(const time_storage&, const time_storage&);
bool operator==(const time_storage&, const time_storage&);
bool operator<=(const time_storage&, const time_storage&);
bool operator>=(const time_storage&, const time_storage&);
bool operator!=(const time_storage&, const time_storage&);

#if defined(__cpp_impl_three_way_comparison) and __cpp_impl_three_way_comparison >=	201907L
std::strong_ordering operator<=>(const time_storage& left, const time_storage& right);
#endif

struct time_storage{
    size_t first = none;
    size_t second = none;

    time_storage() = default;
    time_storage(time_storage&&) = default;
    time_storage(const time_storage&) = default;
    time_storage& operator=(time_storage&&) = default;
    time_storage& operator=(const time_storage&) = default;

    time_storage(timespec_first_t f, timespec_second_t s){
        assert(f >= 0);
        assert(s >= 0);
        assert(s < decltype(s)timespec_base);
        first = f;
        second = s;
        assert(second < decltype(second)timespec_base);
    }

    time_storage(timespec ts):
        time_storage(ts.tv_sec, ts.tv_nsec)
    {}

    time_storage(double time){
        assert(time > 0);
        first = time;
        time -= first;
        time *= timespec_base;
        second = time;
    }

    operator double()const{
        return (double)first + (double)second / timespec_base;
    }

    auto& operator+=(const time_storage& right){
        auto& left = *this;
        left.first  += right.first;
        left.second += right.second;
        left.first  += left.second / timespec_base;
        left.second  = left.second % timespec_base;
        return left;
    }

    auto& operator-=(const time_storage& right){
        auto& left = *this;
        assert(left >= right);
        while (left.second < right.second){
            left.second += timespec_base;
            left.first -= 1;
            assert(left >= right);
        }
        assert(left >= right);
        assert(left.first >= right.first);
        assert(left.second >= right.second);
        left.first  -= right.first;
        left.second -= right.second;
        return left;
    }

    static time_storage monotonic(){
        struct timespec tp;
        memset(&tp, 0, sizeof(tp));
        sys.clock_gettime(CLOCK_MONOTONIC, &tp);
        return tp;
    }

    static time_storage realtime(){
        struct timespec tp;
        memset(&tp, 0, sizeof(tp));
        sys.clock_gettime(CLOCK_REALTIME, &tp);
        return tp;
    }
};

char cmp(const time_storage& left, const time_storage& right){
    if (left.first < right.first){
        return '<';
    }
    if (left.first > right.first){
        return '>';
    }
    if (left.second < right.second){
        return '<';
    }
    if (left.second > right.second){
        return '>';
    }
    return '=';
}

bool operator<(const time_storage& left, const time_storage& right){
    return cmp(left, right) == '<';
}

bool operator==(const time_storage& left, const time_storage& right){
    return cmp(left, right) == '=';
}

bool operator>(const time_storage& left, const time_storage& right){
    return cmp(left, right) == '>';
}

bool operator>=(const time_storage& left, const time_storage& right){
    return cmp(left, right) != '<';
}

bool operator!=(const time_storage& left, const time_storage& right){
    return cmp(left, right) != '=';
}

bool operator<=(const time_storage& left, const time_storage& right){
    return cmp(left, right) != '>';
}

#if defined(__cpp_impl_three_way_comparison) and __cpp_impl_three_way_comparison >=	201907L
std::strong_ordering operator<=>(const time_storage& left, const time_storage& right){
    static_assert('<' < '=');
    static_assert('=' < '>');
    return cmp(left, right) <=> '=';
}
#endif

time_storage operator+(const time_storage& left, const time_storage& right){
    time_storage tmp = left;
    tmp += right;
    return tmp;
}

time_storage operator-(const time_storage& left, const time_storage& right){
    time_storage tmp = left;
    tmp -= right;
    return tmp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* bg_br_colors[] = {
    "\x1b[91m",
    "\x1b[92m",
    "\x1b[93m",
    "\x1b[94m",
    "\x1b[95m",
    "\x1b[96m",
};

const char* solid_block = "\xe2\x96\x88";

const char* uncolor = "\x1b[0m";

auto end_of_msg = [](){
    std::array<char, 64> data;
    sprintf(data.data(), "%s%s%s", solid_block, solid_block, uncolor);
    return data;
}();

#ifdef NDEBUG
#define log(...)
#else
#define log log_
#endif

#define log_(...)                                           \
    do {                                                    \
        auto current_time = time_storage::realtime();       \
        fprintf(stderr, "\r");                              \
        fprintf(                                            \
            stderr,                                         \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            "%s%s"                                          \
            " [%02d:%02d:%02d.%04d] ",                      \
            bg_br_colors[current_time.first / 279936 % 6],  \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 46656 % 6],   \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 7776 % 6],    \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 1296 % 6],    \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 216 % 6],     \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 36 % 6],      \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 6 % 6],       \
            end_of_msg.data(),                              \
            bg_br_colors[current_time.first / 1 % 6],       \
            end_of_msg.data(),                              \
            int(current_time.first / 3600 % 24),            \
            int(current_time.first / 60 % 60),              \
            int(current_time.first % 60),                   \
            int(current_time.second / 1'000'00 % 10000)     \
        );                                                  \
        fprintf(stderr, __VA_ARGS__);                       \
        fprintf(stderr, "\n");                              \
    } while(false)                                          \

#define PART_SIZE 64

std::string part_repr_impl(const char* data, size_t size){
    auto s = repr(std::string(data, data+size));
    std::string res;
    if (s.size() > PART_SIZE * 2){
        assert(s.begin()                <=    s.begin() + PART_SIZE);
        assert(s.begin() + PART_SIZE    <=      s.end() - PART_SIZE);
        assert(s.end() - PART_SIZE      <=                  s.end());
        res = std::string(s.begin(), s.begin() + PART_SIZE) + "..." + std::string(s.end() - PART_SIZE, s.end());
    }else{
        res = s;
    }
    assert(res.size() < PART_SIZE * 2 + 4);
    return res;
}

#define part_repr(...) (part_repr_impl(__VA_ARGS__).data())

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename>
class function_ref;

template <typename R, typename... Args>
class function_ref<R(Args...)> {
public:
    void* callable_ = nullptr;
    R (*invoker_)(void*, Args&&...) = nullptr;

    function_ref() = default;

    template<typename T>
    static R invoker(void* ptr, Args&&... args) {
        return (*reinterpret_cast<T*>(ptr))(std::forward<Args>(args)...);
    };

    template <typename Callable>
    function_ref(Callable& callable) noexcept {
        using T = std::remove_reference_t<Callable>;
        static_assert(std::is_invocable_r_v<R, T&, Args...>,
                      "Callable must be invocable with the correct signature");

        callable_ = static_cast<void*>(&callable);
        invoker_ = function_ref::invoker<T>;

    }

    function_ref(function_ref&) = default;
    function_ref(const function_ref&) = default;
    function_ref(function_ref&&) = default;
    function_ref& operator=(function_ref&) = default;
    function_ref& operator=(const function_ref&) = default;
    function_ref& operator=(function_ref&&) = default;

    R operator()(Args... args) const {

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct defer{
    T val;
    defer(T&& val):val(val){}
    ~defer(){val();}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    assert(sys.inet_pton(AF_INET, addr, &sau.sai.sin_addr) == 1);
    return sau.sa;
}

sockaddr host_port_to_sockaddr(const host_port& hp){
    return host_port_to_sockaddr(hp.first.data(), hp.second);
}

int ll_create_non_blocking_socket(){
    int s = sys.socket(AF_INET, SOCK_STREAM, 0);
    int flags = sys.fcntl(s, F_GETFL, 0);
    flags |= O_NONBLOCK;
    sys.fcntl(s, F_SETFL, flags);
    return s;
}

int ll_create_listening_socket(const sockaddr& addr){
    auto s = ll_create_non_blocking_socket();
    int enable = 1;
    sys.setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    sys.bind(s, &addr, sizeof(addr));
    sys.listen(s, 65536);
    return s;
}

int ll_create_connecting_socket(const sockaddr& addr){
    auto s = ll_create_non_blocking_socket();
    sys.ignore(EINPROGRESS);
    sys.connect(s, &addr, sizeof(addr));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    int rc = write(2, last, data + sizeof(data) - last);
    (void)rc;
    rc = write(signal_pipe[1], "", 1);
    (void)rc;
    if (++handle_calls > 4){
        abort();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

time_storage connection_timeout;
time_storage clock_interval;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct fd_owner;

int get_fd(const fd_owner& s);

struct fd_owner{
private:
    int s;
public:
    fd_owner(int s):
        s(s)
    {
        log("[%4d] ++++++++ started owning", s);
    }
    ~fd_owner(){
        log("[%4d] -------- stopped owning", s);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    Selector(){
        clear_events();
    }

    void clear_events(){
        memset(events_to_process.first.data(), 0, sizeof(events_to_process.first));
        events_to_process.second = 0;
    }

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

    void wait(std::optional<time_storage> timeout = std::nullopt){
        double to_sleep = -1;
        if (timeout){
            to_sleep = *timeout;
            to_sleep *= 1000;
        }

        sys.ignore(EINTR);
        events_to_process.second = sys.epoll_wait(
            get_fd(pool_fd),
            events_to_process.first.data(),
            events_to_process.first.size(),
            to_sleep
        );

        if (sys.last_err == EINTR){
            log("epoll_wait() was interrupted by signal.");
            return;
        }

        assert(sys.last_err == 0);
        assert(events_to_process.second < events_to_process.first.size());

        for (size_t q = 0; q < events_to_process.second; ++q){
            auto& event = events_to_process.first[q];
            log("[%20p] [%20p] before checking for rw events", event.data.ptr, &event);
            if (event.events & EPOLLIN){
                log("[%20p] [%20p] before handling read event", event.data.ptr, &event);
                (*(Callback*)event.data.ptr)(false);
                log("[%20p] [%20p] after handling read event", event.data.ptr, &event);
            }
            if (event.events & EPOLLOUT){
                log("[%20p] [%20p] before handling write event", event.data.ptr, &event);
                (*(Callback*)event.data.ptr)(true);
                log("[%20p] [%20p] after handling write event", event.data.ptr, &event);
            }
            log("[%20p] [%20p] after checking for rw events", event.data.ptr, &event);
        }
        clear_events();
    }

    void notify_closed(void* ctx){
        log("[%20p] before notifying about closed socket", ctx);
        for (auto& event_to_process: events_to_process.first){
            if (event_to_process.data.ptr == ctx){
                log("[%20p] [%20p] this event has requested context, removing handler", ctx, &event_to_process);
                event_to_process.events = 0;
                event_to_process.data.ptr = nullptr;
            }else{
                // log("[%20p] [%20p] this event does not have requested context", ctx, &event_to_process);
            }
        }
        log("[%20p] after notifying about closed socket", ctx);
    }
};

#endif

using selector_t = Selector<function_ref<void(bool)>>;

using header_t = uint_least64_t;

#define CMD_SOCKET_HEADER_SIZE (sizeof(header_t))

template<typename s_owner>
struct SplitCallbacks{
    SplitCallbacks(selector_t& selector, s_owner& s):
        selector(selector),
        s(s)
    {
        handler.outer = this;
    }

    ~SplitCallbacks(){
        selector.notify_closed(&handler_ref);
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
            outer->handle(to_write);
        }
    } handler;

    function_ref<void(bool)> handler_ref = handler;

    void handle(bool to_write){
        auto err = get_errno(get_fd(s));
        if (err != 0){
            // std::cerr << __PRETTY_FUNCTION__ << " fd=" << get_fd(s) << " " << strerror(err) << std::endl;
            has_err = true;
        }
        if (to_write){
            assert(write_callback);
            auto write_callback_local = write_callback;
            write_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, has_read_task_, true, has_read_task_, false);
            has_write_task_ = false;
            assert(write_callback_local);

            write_callback_local(err);
        }else{
            assert(read_callback);
            auto read_callback_local = read_callback;
            read_callback.reset();
            selector.change_fd_in_pool(s, &handler_ref, true, has_write_task_, false, has_write_task_);
            has_read_task_ = false;
            assert(read_callback_local);

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StreamSocketCompleter{

    StreamSocketCompleter(selector_t& selector, const sockaddr& addr):
        last_event(time_storage::monotonic()),
        s(addr),
        c(selector, s),
        connected(false)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

    StreamSocketCompleter(selector_t& selector, const fd_owner& server):
        last_event(time_storage::monotonic()),
        s(server),
        c(selector, s),
        connected(true)
    {
        read_handler.outer = this;
        write_handler.outer = this;
    }

private:
    time_storage last_event;

    stream_socket_owner s;
    SplitCallbacks<stream_socket_owner> c;

    using external_rw_callback = function_ref<void(const char*, size_t, error_t)>;

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
            outer->last_event = time_storage::monotonic();

            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    struct WriteHandler{
        StreamSocketCompleter* outer;
        void operator()(error_t err){
            outer->last_event = time_storage::monotonic();

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
        auto still_has_to_read_local = still_has_to_read;
        still_has_to_read = none;
        has_full_read_task = false;
        if (still_has_to_read_local == none){
            log("[%4d] (%d:%s) after reading %zu bytes: %s", get_fd(s), err, strerror(err), len_of_data_in_read_buffer_local, part_repr(read_buffer.data(), len_of_data_in_read_buffer_local));
        }else{
            log("[%4d] (%d:%s) after reading %zu of %zu bytes: %s", get_fd(s), err, strerror(err), len_of_data_in_read_buffer_local, len_of_data_in_read_buffer_local + still_has_to_read_local, part_repr(read_buffer.data(), len_of_data_in_read_buffer_local));
        }
        read_callback_local(read_buffer.data(), len_of_data_in_read_buffer_local, err);
    }

    void handle_write(error_t err){
        if (not connected){
            if (err == 0){
                connected = true;
            }
            auto connected_callback_local = connected_callback;
            connected_callback.reset();
            log("[%4d] (%d:%s) after waiting for connect", get_fd(s), err, strerror(err));
            connected_callback_local(nullptr, 0, err);
            return;
        }
        if (err == 0){
            if (has_full_write_task){
                assert(0 < still_has_to_write);
                assert(still_has_to_write <= len_of_data_in_write_buffer);
                assert(0 < len_of_data_in_write_buffer);
                assert(len_of_data_in_write_buffer <= write_buffer.size());
                sys.ignore(EPIPE);
                size_t written = sys.write(get_fd(s), write_buffer.data() + len_of_data_in_write_buffer - still_has_to_write, still_has_to_write);
                if (errno){
                    err = errno;
                }else{
                    still_has_to_write -= written;
                    if (still_has_to_write != 0){
                        return;
                    }
                }
            }else{
                assert(still_has_to_write == len_of_data_in_write_buffer);
                assert(0 < len_of_data_in_write_buffer);
                assert(len_of_data_in_write_buffer <= write_buffer.size());
                sys.ignore(EPIPE);
                size_t written = sys.write(get_fd(s), write_buffer.data(), write_buffer.size());
                if (errno){
                    err = errno;
                }else{
                    still_has_to_write -= written;
                }
            }
        }
        auto write_callback_local = write_callback;
        write_callback.reset();
        auto len_of_data_in_write_buffer_local = len_of_data_in_write_buffer;
        len_of_data_in_write_buffer = none;
        auto still_has_to_write_local = still_has_to_write;
        still_has_to_write = none;
        has_full_write_task = false;
        log("[%4d] (%d:%s) after writing %zu bytes and not writing %zu bytes: %s and %s",
            get_fd(s),
            err,
            strerror(err),
                                                                    len_of_data_in_write_buffer_local - still_has_to_write_local,
                                                                                                        still_has_to_write_local,
            part_repr(write_buffer.data(),                          len_of_data_in_write_buffer_local - still_has_to_write_local),
            part_repr(write_buffer.data()+len_of_data_in_write_buffer_local - still_has_to_write_local, still_has_to_write_local)
        );
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
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        assert(len <= read_buffer.size());
        assert(callback);
        log("[%4d] before full read of %zu bytes", get_fd(s), len);
        c.wait_read(read_handler_ref);
        read_callback = callback;
        has_full_read_task = true;
        still_has_to_read = len;
        len_of_data_in_read_buffer = 0;
    }

    void partial_read(external_rw_callback callback){
        assert(connected);
        assert(not read_callback);
        assert(not has_full_read_task);
        assert(still_has_to_read == none);
        assert(len_of_data_in_read_buffer == none);
        assert(callback);
        log("[%4d] before partial read", get_fd(s));
        c.wait_read(read_handler_ref);
        read_callback = callback;
        len_of_data_in_read_buffer = 0;
    }

    void full_write(const char* data, size_t len, external_rw_callback callback){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        assert(not eof_is_written_);
        assert(callback);
        log("[%4d] before full write of %zu bytes: %s", get_fd(s), len, part_repr(data, len));
        c.wait_write(write_handler_ref);
        memmove(write_buffer.data(), data, len);
        write_callback = callback;
        has_full_write_task = true;
        still_has_to_write = len;
        len_of_data_in_write_buffer = len;
    }

    void partial_write(const char* data, size_t len, external_rw_callback callback){
        assert(connected);
        assert(not write_callback);
        assert(not has_full_write_task);
        assert(still_has_to_write == none);
        assert(len_of_data_in_write_buffer == none);
        assert(len <= write_buffer.size());
        assert(not eof_is_written_);
        assert(callback);
        log("[%4d] before partial write of %zu bytes: %s", get_fd(s), len, part_repr(data, len));
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
        log("[%4d] write EOF", get_fd(s));
        s.shut_wr();
        eof_is_written_ = true;
    }

    bool eof_is_written()const{
        return eof_is_written_;
    }

    void wait_for_connect(external_rw_callback callback){
        assert(not connected);
        assert(callback);
        log("[%4d] before waiting for connect", get_fd(s));
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

    time_storage get_last_event(){
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

            outer->handle_read(err);
        }
    } read_handler;

    function_ref<void(bool)> read_handler_ref = read_handler;

    void handle_read(error_t err){
        log("[%4d] (%d:%s) after waiting for accept", get_fd(s), err, strerror(err));
        accept_callback(err);
    }

public:
    void wait_for_accept(external_callback callback){
        assert(callback);
        log("[%4d] before waiting for accept", get_fd(s));
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename stream_context>
struct ServerManager;

struct AcceptedSocketCMD;

struct AcceptedSocketTCP;

struct AppServer;

uint_least64_t get_rand64(AppServer& app_server);

bool has_main_connection(AppServer& app_server);
void ctl_maybe_send_some_request(AppServer& app_server);

void notify_closing_stream(AppServer& app_server, AcceptedSocketCMD& stream);
void notify_closing_stream(AppServer& app_server, AcceptedSocketTCP& stream);

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

            outer->handle_accept(err);
        }
    } accept_handler;

    function_ref<void(error_t)> accept_handler_ref = accept_handler;

    bool is_waiting_for_accept = false;

    void start_waiting_for_accept(){
        if (not is_waiting_for_accept){
            server.wait_for_accept(accept_handler_ref);
            is_waiting_for_accept = true;
        }
    }

    void handle_accept(error_t err){
        assert(err == 0);

        log("before accept loop");

        for (size_t i = 0; i < streams.size(); ++i){
            if (not streams[i].has_value()){
                auto& stream = streams[i];
                log("accepting %4d at %zu", get_fd(*stream), i);
                stream.emplace(selector, server, i, app_server);
                ctl_maybe_send_some_request(app_server);
                start_waiting_for_accept();
                return;
            }
        }

        log("not accepting socket");
    }

public:
    size_t get_streams_size(){
        return streams.size();
    }

    stream_context* get_stream(size_t i){
        assert(i != none);
        assert(i < streams.size());
        auto& stream = streams[i];
        return stream.has_value() ? &*stream : nullptr;
    }

    void close_stream(size_t i){
        auto& stream = streams[i];
        if (stream.has_value()){
            notify_closing_stream(app_server, *stream);
            stream.reset();
            start_waiting_for_accept();
        }
    }
};

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
        assert(index != none);
        read_handler.outer = this;
        write_handler.outer = this;
        s.full_read(first_bytes_size, read_handler_ref);
    }

    const size_t index = none;
    size_t other_index = none;
    header_t header = none;
private:
    selector_t& selector;
    StreamSocketCompleter s;
    AppServer& app_server;
    size_t accepted_cmd_socket_state = none;

    struct ReadHandler{
        AcceptedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){

            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        AcceptedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){

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
                    log("[%4d] closing by err during reading first bytes", get_fd(s));
                    close();
                    return;
                }
                assert(size <= first_bytes_size);
                if (size != first_bytes_size){
                    log("[%4d] closing by EOF during reading first bytes", get_fd(s));
                    close();
                    return;
                }

                accepted_cmd_socket_state = accepted_cmd_socket_states::readen_first_bytes;

                s.full_read(CMD_SOCKET_HEADER_SIZE, read_handler_ref);
            }
            break;
            case accepted_cmd_socket_states::readen_first_bytes:{
                if (err != 0){
                    log("[%4d] closing by err during reading header", get_fd(s));
                    close();
                    return;
                }
                assert(size <= CMD_SOCKET_HEADER_SIZE);
                if (size != CMD_SOCKET_HEADER_SIZE){
                    log("[%4d] closing by EOF during reading header", get_fd(s));
                    close();
                    return;
                }
                header_t header_ = 0;
                static_assert(CHAR_BIT == 8);
                static_assert(CMD_SOCKET_HEADER_SIZE <= sizeof(header_));
                assert(size <= sizeof(header_));
                memcpy(&header_, data, size);
                header = header_;
                if (header == 0){

                    accepted_cmd_socket_state = accepted_cmd_socket_states::main;

                    handle_accept_ctl(app_server, index, header);
                }else{

                    accepted_cmd_socket_state = accepted_cmd_socket_states::worker;

                    if (not has_main_connection(app_server)){
                        log("[%4d] closing new worker by not having main connection", get_fd(s));
                        close();
                        return;
                    }

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

    time_storage get_last_event(){
        return s.get_last_event();
    }
};

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

            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        AcceptedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
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

    time_storage get_last_event(){
        return s.get_last_event();
    }
};

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
    size_t cleanups_without_main = 0;

    AcceptedSocketCMD& get_main(){
        AcceptedSocketCMD* main_ptr = cmd_server.get_stream(main_index);
        assert(main_ptr);
        return *main_ptr;
    }

    bool has_main_connection(){
        return main_index != none;
    }

    void ctl_maybe_send_some_request(){
        if (not has_main_connection()){
            log("not sending new connection request without main connection");
            return;
        }
        auto& main = get_main();
        if (main.has_write_task()){
            log("not sending new connection request as main connection is busy");
            return;
        }
        for (size_t i = 0; i < tcp_server.get_streams_size(); ++i){
            log("checking if stream with index=%zu needs new connection request", i);
            auto stream_ptr = tcp_server.get_stream(i);
            if (not stream_ptr){
                log("there is no stream with index=%zu", i);
                continue;
            }
            auto& stream = *stream_ptr;
            if (stream.request_for_cmd_socket_is_sent){
                log("stream with index=%zu is already processed", i);
                continue;
            }
            log("sending new connection request for stream with index=%zu", i);
            char message[CMD_SOCKET_HEADER_SIZE];
            memset(message, 0, sizeof(message));
            static_assert(sizeof(stream.header) <= CMD_SOCKET_HEADER_SIZE);
            memcpy(message, &stream.header, sizeof(stream.header));
            log("[%4d] sending new conneciton request", get_fd(stream));
            main.full_write(message, sizeof(message));
            stream.request_for_cmd_socket_is_sent = true;
            return;
        }
        log("not sending new connection request as there is no pending requests.");
    }

    void cleanup(){
        auto current_time = time_storage::monotonic();
        bool allow_to_survive = true;
        if (has_main_connection()){
            cleanups_without_main = 0;
        }else{
            allow_to_survive = cleanups_without_main < 4;
            cleanups_without_main += 1;
        }
        for (size_t i = 0; i < cmd_server.get_streams_size(); ++i){
            auto cmd_stream_ptr = cmd_server.get_stream(i);
            if (not cmd_stream_ptr){
                continue;
            }
            auto& cmd_stream = *cmd_stream_ptr;
            if (allow_to_survive and current_time - cmd_stream.get_last_event() < connection_timeout){
                continue;
            }
            if (cmd_stream.other_index == none){
                log("[%4d] closing by timeout", get_fd(cmd_stream));
                cmd_server.close_stream(cmd_stream.index);
                continue;
            }
            auto tcp_stream_ptr = tcp_server.get_stream(cmd_stream.other_index);
            assert(tcp_stream_ptr);
            auto& tcp_stream = *tcp_stream_ptr;
            assert(tcp_stream.other_index == cmd_stream.index);
            assert(cmd_stream.other_index == tcp_stream.index);
            log("[%4d] closing by timeout", get_fd(cmd_stream));
            cmd_server.close_stream(cmd_stream.index);
            log("[%4d] closing by timeout", get_fd(tcp_stream));
            tcp_server.close_stream(tcp_stream.index);
        }
        for (size_t i = 0; i < tcp_server.get_streams_size(); ++i){
            auto tcp_stream_ptr = tcp_server.get_stream(i);
            if (not tcp_stream_ptr){
                continue;
            }
            auto& tcp_stream = *tcp_stream_ptr;
            if (allow_to_survive and current_time - tcp_stream.get_last_event() < connection_timeout){
                continue;
            }
            if (tcp_stream.other_index == none){
                log("[%4d] closing by timeout", get_fd(tcp_stream));
                tcp_server.close_stream(tcp_stream.index);
                continue;
            }
            auto cmd_stream_ptr = cmd_server.get_stream(tcp_stream.other_index);
            assert(cmd_stream_ptr);
            auto& cmd_stream = *cmd_stream_ptr;
            assert(tcp_stream.other_index == cmd_stream.index);
            assert(cmd_stream.other_index == tcp_stream.index);
            log("[%4d] closing by timeout", get_fd(cmd_stream));
            cmd_server.close_stream(cmd_stream.index);
            log("[%4d] closing by timeout", get_fd(tcp_stream));
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
    log("[%4d] accepted new main stream with index=%zu", get_fd(*app_server.cmd_server.get_stream(index)), index);
    if (app_server.main_index != none){
        log("[%4d] closing old main stream with index=%zu", get_fd(*app_server.cmd_server.get_stream(app_server.main_index)), app_server.main_index);
        assert(app_server.main_index != index);
        app_server.cmd_server.close_stream(app_server.main_index);
    }
    app_server.main_index = index;
    log("checking for new connection requests after accepting main stream");
    app_server.ctl_maybe_send_some_request();
}

void handle_read_ctl(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(false);
}

void handle_write_ctl(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(header == 0);
    log("%zu %zu", app_server.main_index, index);
    assert(app_server.main_index == index);
    if (err != 0){
        log("[%4d] closing by err during writing new connection header", get_fd(*app_server.cmd_server.get_stream(app_server.main_index)));
        app_server.main_index = none;
        app_server.cmd_server.close_stream(index);
        return;
    }
    assert(size == 0);
    log("checking for new connection requests after sending one");
    app_server.ctl_maybe_send_some_request();
}

void handle_accept_tcp(AppServer& app_server, size_t index, header_t header){}

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
                log("[%4d] TCP stream with this header already has CMD stream", get_fd(cmd_stream));
                app_server.cmd_server.close_stream(index);
                return;
            }
            stream.other_index = index;
            cmd_stream.other_index = i;
            break;
        }
    }
    if (cmd_stream.other_index == none){
        log("[%4d] cannot find TCP stream for this header", get_fd(cmd_stream));
        app_server.cmd_server.close_stream(index);
        return;
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
        log("[%4d] closing by err during reading data", get_fd(tcp_stream));
        app_server.cmd_server.close_stream(cmd_stream.index);
        app_server.tcp_server.close_stream(tcp_stream.index);
        return;
    }

    if (size != 0){
        cmd_stream.full_write(data, size);
        return;
    }

    assert(not cmd_stream.eof_is_written());
    log("[%4d] sending EOF", get_fd(cmd_stream));
    cmd_stream.write_eof();
    if (tcp_stream.eof_is_written()){
        log("[%4d] [%4d] closing by mutual EOF", get_fd(tcp_stream), get_fd(cmd_stream));
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
        log("[%4d] closing by err during reading data", get_fd(cmd_stream));
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
        return;
    }

    if (size != 0){
        tcp_stream.full_write(data, size);
        return;
    }

    assert(not tcp_stream.eof_is_written());
    log("[%4d] sending EOF", get_fd(tcp_stream));
    tcp_stream.write_eof();
    if (cmd_stream.eof_is_written()){
        log("[%4d] [%4d] closing by mutual EOF", get_fd(tcp_stream), get_fd(cmd_stream));
        app_server.tcp_server.close_stream(tcp_stream.index);
        app_server.cmd_server.close_stream(cmd_stream.index);
    }
}

void handle_write_tcp(AppServer& app_server, const char* data, size_t size, error_t err, size_t index, header_t header){
    auto tcp_stream_ptr = app_server.tcp_server.get_stream(index);
    assert(tcp_stream_ptr);
    auto& tcp_stream = *tcp_stream_ptr;
    assert(tcp_stream.other_index != none);
    auto cmd_stream_ptr = app_server.cmd_server.get_stream(tcp_stream.other_index);
    assert(cmd_stream_ptr);
    auto& cmd_stream = *cmd_stream_ptr;
    assert(cmd_stream.other_index == index);

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

void notify_closing_stream(AppServer& app_server, AcceptedSocketCMD& stream){
    if (stream.index == app_server.main_index){
        app_server.main_index = none;
    }
}

void notify_closing_stream(AppServer& app_server, AcceptedSocketTCP& stream){}

void ctl_maybe_send_some_request(AppServer& app_server){
    log("checking for new connection requests after accepting tcp stream");
    return app_server.ctl_maybe_send_some_request();
}

bool has_main_connection(AppServer& app_server){
    return app_server.has_main_connection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AppClient;

struct ConnectedSocketCMD;
struct ConnectedSocketTCP;

struct ClientManager;

ClientManager& get_client_manager(AppClient& app_client);
const sockaddr& get_cmd_addr(AppClient& app_client);
const sockaddr& get_tcp_addr(AppClient& app_client);

void handle_connect_ctl(AppClient& app_client, size_t index, header_t header);
void handle_connect_cmd(AppClient& app_client, size_t index, header_t header);
void handle_connect_tcp(AppClient& app_client, size_t index, header_t header);
void handle_read_ctl(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_cmd(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_read_tcp(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_ctl(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_cmd(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);
void handle_write_tcp(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header);

namespace connected_socket_states{
    enum connected_socket_states{
        fresh, connected, first_bytes_written, header_written,
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
        s.wait_for_connect(write_handler_ref);
        read_handler.outer = this;
        write_handler.outer = this;
    }

    selector_t& selector;
    size_t index = none;
    header_t header = none;
    AppClient& app_client;
private:
    StreamSocketCompleter s;
public:
    size_t state = none;

    struct ReadHandler{
        ConnectedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){

            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        ConnectedSocketCMD* outer;
        void operator()(const char* data, size_t size, error_t err){

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
            case connected_socket_states::fresh:{
                if (err != 0){
                    log("[%4d] closing by err during connecting", get_fd(s));
                    close_pair();
                    return;
                }
                assert(s.is_connected());

                state = connected_socket_states::connected;

                char message[BUFFER_SIZE];
                memset(message, 0, sizeof(message));
                assert(first_bytes_size <= sizeof(message));
                memcpy(message, first_bytes_data, first_bytes_size);
                full_write(message, first_bytes_size);
            break;}
            case connected_socket_states::connected:{
                if (err != 0){
                    log("[%4d] closing by EOF during writting first bytes", get_fd(s));
                    close_pair();
                    return;
                }
                assert(size == 0);

                state = connected_socket_states::first_bytes_written;

                char message[CMD_SOCKET_HEADER_SIZE];
                memset(message, 0, sizeof(message));
                static_assert(sizeof(header) <= CMD_SOCKET_HEADER_SIZE);
                memcpy(message, &header, sizeof(header));
                full_write(message, sizeof(message));
            break;}
            case connected_socket_states::first_bytes_written:{
                if (err != 0){
                    log("[%4d] closing by err during writting header", get_fd(s));
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
            break;}
            case connected_socket_states::header_written:{
                if (header == 0){
                    handle_write_ctl(app_client, data, size, err, index, header);
                }else{
                    handle_write_cmd(app_client, data, size, err, index, header);
                }
            break;}
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

    time_storage get_last_event(){
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
        s.wait_for_connect(write_handler_ref);
        read_handler.outer = this;
        write_handler.outer = this;
    }

    selector_t& selector;
    size_t index;
    header_t header;
    AppClient& app_client;
private:
    StreamSocketCompleter s;
public:
    size_t state = none;

    struct ReadHandler{
        ConnectedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){

            outer->handle_read(data, size, err);
        }
    } read_handler;

    function_ref<void(const char*, size_t, error_t)> read_handler_ref = read_handler;

    struct WriteHandler{
        ConnectedSocketTCP* outer;
        void operator()(const char* data, size_t size, error_t err){
            outer->handle_write(data, size, err);
        }
    } write_handler;

    function_ref<void(const char*, size_t, error_t)> write_handler_ref = write_handler;

    void handle_read(const char* data, size_t size, error_t err){
        handle_read_tcp(app_client, data, size, err, index, header);
    }

    void handle_write(const char* data, size_t size, error_t err){
        switch (state){
            case connected_socket_states::fresh:{
                if (err != 0){
                    log("[%4d] closing by err during connecting", get_fd(s));
                    close_pair();
                    return;
                }
                assert(s.is_connected());

                state = connected_socket_states::connected;

                assert(header != 0);
                handle_connect_tcp(app_client, index, header);
            break;}
            case connected_socket_states::connected:{
                handle_write_tcp(app_client, data, size, err, index, header);
            break;}
            default:
                assert(false);
        }
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

    time_storage get_last_event(){
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
        auto current_time = time_storage::monotonic();
        for (size_t i = 0; i < client.get_stream_pairs_size(); ++i){
            auto stream_pair_ptr = client.get_stream_pair(i);
            if (not stream_pair_ptr){
                continue;
            }
            auto& stream_pair = *stream_pair_ptr;
            if (current_time - stream_pair.first.get_last_event() > connection_timeout){
                log("[%4d] closing by timeout", get_fd(stream_pair.first));
                log("[%4d] closing by timeout", get_fd(stream_pair.second));
                client.close_pair(i);
                continue;
            }
            if (current_time - stream_pair.second.get_last_event() > connection_timeout){
                log("[%4d] closing by timeout", get_fd(stream_pair.first));
                log("[%4d] closing by timeout", get_fd(stream_pair.second));
                client.close_pair(i);
                continue;
            }
        }
        if (current_time - (*client.main_client)->get_last_event() > connection_timeout){
            log("[%4d] closing by timeout", get_fd(**client.main_client));
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

void handle_connect_ctl(AppClient& app_client, size_t index, header_t header){
    assert(index == none);
    assert(header == 0);
    assert(app_client.client.main_client->has_value());
    auto& main = **app_client.client.main_client;
    main.full_read(CMD_SOCKET_HEADER_SIZE);
}

void handle_read_ctl(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    if (err != 0){
        log("[%4d] closing by err during reading new connection header", get_fd(**app_client.client.main_client));
        app_client.client.disable_main();
        return;
    }
    if (size < CMD_SOCKET_HEADER_SIZE){
        log("[%4d] closing by EOF during reading new connection header", get_fd(**app_client.client.main_client));
        app_client.client.disable_main();
        return;
    }
    assert(size == CMD_SOCKET_HEADER_SIZE);
    assert(index == none);
    assert(header == 0);
    assert(app_client.client.main_client->has_value());
    auto& main = **app_client.client.main_client;
    static_assert(CMD_SOCKET_HEADER_SIZE <= sizeof(header));
    header = 0;
    assert(size <= sizeof(header));
    memcpy(&header, data, size);
    app_client.client.maybe_open_pair(header);
    main.full_read(CMD_SOCKET_HEADER_SIZE);
}

void handle_write_ctl(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(false);
}

void handle_connect_cmd(AppClient& app_client, size_t index, header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.first.state == connected_socket_states::header_written);
    if (not stream_pair.second.is_connected()){
        return;
    }
    stream_pair.first.partial_read();
    stream_pair.second.partial_read();
}

void handle_connect_tcp(AppClient& app_client, size_t index,  header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.second.is_connected());
    if (stream_pair.first.state != connected_socket_states::header_written){
        return;
    }
    stream_pair.second.partial_read();
    stream_pair.first.partial_read();
}

void handle_read_cmd(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());
    assert(stream_pair.first.state == connected_socket_states::header_written);

    if (err != 0){
        log("[%4d] closing by err during reading data", get_fd(stream_pair.first));
        app_client.client.close_pair(index);
        return;
    }

    if (size != 0){
        stream_pair.second.full_write(data, size);
        return;
    }

    assert(not stream_pair.second.eof_is_written());
    log("[%4d] sending EOF", get_fd(stream_pair.second));
    stream_pair.second.write_eof();
    if (stream_pair.first.eof_is_written()){
        log("[%4d] [%4d] closing by mutual EOF", get_fd(stream_pair.first), get_fd(stream_pair.second));
        app_client.client.close_pair(index);
    }
}

void handle_read_tcp(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());
    assert(stream_pair.first.state == connected_socket_states::header_written);

    if (err != 0){
        log("[%4d] closing by err during reading data", get_fd(stream_pair.second));
        app_client.client.close_pair(index);
        return;
    }

    if (size != 0){
        stream_pair.first.full_write(data, size);
        return;
    }

    assert(not stream_pair.first.eof_is_written());
    log("[%4d] sending EOF", get_fd(stream_pair.first));
    stream_pair.first.write_eof();
    if (stream_pair.second.eof_is_written()){
        log("[%4d] [%4d] closing by mutual EOF", get_fd(stream_pair.first), get_fd(stream_pair.second));
        app_client.client.close_pair(index);
    }
}

void handle_write_cmd(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());
    assert(stream_pair.first.state == connected_socket_states::header_written);

    if (err != 0){
        log("[%4d] closing by err during sending data", get_fd(stream_pair.first));
        app_client.client.close_pair(index);
        return;
    }

    assert(size == 0);
    stream_pair.second.partial_read();
}

void handle_write_tcp(AppClient& app_client, const char* data, size_t size, error_t err, size_t index, header_t header){
    assert(index < app_client.client.get_stream_pairs_size());
    auto stream_pair_ptr = app_client.client.get_stream_pair(index);
    assert(stream_pair_ptr);
    auto& stream_pair = *stream_pair_ptr;
    assert(stream_pair.first.is_connected());
    assert(stream_pair.second.is_connected());
    assert(stream_pair.first.state == connected_socket_states::header_written);

    if (err != 0){
        log("[%4d] closing by err during sending data", get_fd(stream_pair.second));
        app_client.client.close_pair(index);
        return;
    }

    assert(size == 0);
    stream_pair.first.partial_read();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        time_storage last_cleanup = time_storage::monotonic();
        while (not should_exit){
            time_storage current_time = time_storage::monotonic();
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool has_missing_flags = false;

auto same = [](auto&&val)->decltype(auto){return FORWARD(val);};

template<typename T, typename F = decltype(same)>
void argv_initializer(int argc, char** argv, T& value, const char* name, F f = same){
    std::string flag = "--";
    flag += name;
    for (int i = 2 ; i < argc; ++i){
        if (argv[i-1] == flag){
            value = f(argv[i]);
            return;
        }
    }
    std::cerr << "Missing flag: " << flag << std::endl;
    has_missing_flags = true;
}

#define init_by_argv(name, ...) argv_initializer(argc, argv, name, #name __VA_OPT__(,) __VA_ARGS__)

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
    if (strlen(argv[0])==0){
        printf("%s", TO_STR(SOURCE_CODE));
        return 0;
    }
    init_by_argv(mode, [](auto&& s){
        if (strcmp(s, "server") == 0){return modes::server;}
        if (strcmp(s, "client") == 0){return modes::client;}
        throw std::runtime_error{"modes: client|server"};
    });

    init_by_argv(connection_timeout, ([](const char* s){
        return time_storage(strtold(s, nullptr));
    }));
    init_by_argv(clock_interval, ([](const char* s){
        return time_storage(strtold(s, nullptr));
    }));
    init_by_argv(max_accepted_sockets_per_server, atoll);
    init_by_argv(max_connected_sockets, atoll);

    init_by_argv(first_bytes_filename);

    init_by_argv(internal_port, atoll);
    init_by_argv(internal_host);

    init_by_argv(external_port, atoll);
    init_by_argv(external_host);

    if (has_missing_flags){
        exit(1);
    }

    first_bytes_size = read_file(first_bytes_filename, first_bytes_data, sizeof(first_bytes_data));
    internal_sockaddr = host_port_to_sockaddr(internal_host, internal_port);
    external_sockaddr = host_port_to_sockaddr(external_host, external_port);

    App app;
}

