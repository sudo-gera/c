#include <bits/stdc++.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

// #define use_epoll

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct function;

template<typename R, typename...A>
struct function<R(A...)>{
    static function* current;
    struct base{
        virtual R operator()(A...) = 0;
        virtual ~base() = default;
        // virtual void copy_to(std::unique_ptr<base>& place) = 0;
    };
    template<typename L>
    struct storer:base{
        L val;
        template<typename V>
        requires(
            not std::is_same_v<
                std::decay_t<V>,
                storer
            >
        )
        storer(V&&v):val(FORWARD(v)){}
        virtual R operator()(A...args) override {
            return val(FORWARD(args)...);
        }
        ~storer() override = default;
        // void copy_to(std::unique_ptr<base>& place) override{
        //     place = std::make_unique<storer>(*this);
        // }
    };
    std::unique_ptr<base> func;
    template<typename L>
    requires(
        not std::is_same_v<
            std::decay_t<L>,
            function
        >
    )
    function(L&&val){
        func = std::make_unique<
            storer<
                std::decay_t<L>
            >
        >(FORWARD(val));
    }
    function(function&&) = default;
    function& operator=(function&&) = default;
    // function(const function&a){
    //     a.func->copy_to(func);
    // }

    // function& operator=(const function&a){
    //     a.func->copy_to(func);
    //     return *this;
    // }

    function() = default;
    operator bool(){
        return bool(func);
    }
    R operator()(A...args){
        auto prev = current;
        current = this;
        return (*func)(FORWARD(args)...);
        current = prev;
    }
};

template<typename R, typename...A>
function<R(A...)>* function<R(A...)>::current = nullptr;


using Task = function<void()>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct void_ptr_storage{
    struct item;
    using cont = std::list<item>;
    cont items;
    struct item{
        T value;
        cont::iterator iter;
    };
    T& get(void*ptr){
        auto iter = *(typename cont::iterator*)(ptr);
        return iter->value;
    }
    void del(void*ptr){
        auto iter = *(typename cont::iterator*)(ptr);
        items.erase(iter);
    }
    void* put(T val){
        auto iter = items.emplace(items.begin(), item{
            .value = std::move(val),
        });
        iter->iter = iter;
        return &iter->iter;
    }
    size_t size(){
        return items.size();
    }
    void clear(){
        items.clear();
    }
};

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

auto repr(auto&& val) {
    std::stringstream a;
    a << FORWARD(val);
    return repr_s(a.str());
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
        int err = errno;                                             \
        if (err and not ignored.count(err)) {                            \
            std::cerr << "\n <<< ERROR >>>\n";                           \
            std::cerr << "    " #name " Failed\n";                       \
            std::cerr << "    code = " << err << "\n";                   \
            std::cerr << "    text = " << strerror(err) << "\n";         \
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
#ifdef use_kqueue
    add_syscall(kqueue)
    add_syscall(kevent)
#endif
} sys;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
concept selector =  requires(T selector){
    static_cast < void(T::*const)(int, Task) > ( &T::async_read  );
    static_cast < void(T::*const)(int, Task) > ( &T::async_write );
    static_cast < void(T::*const)()          > ( &T::loop        );
};

#ifdef use_kqueue

    void print_kevent(struct kevent& value){
        std::cerr << "event{" << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.ident) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.filter) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.flags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.fflags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.data) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.udata) << std::endl
        << "}" << std::endl;
    }

    struct kqueue_selector{
    private:
        int kq = 0;
        std::pair<
            std::array<
                struct kevent,
                256
            >,
            size_t
        > events_to_process = {{}, 0};
        std::vector<
            struct kevent
        > events_to_add;
        void_ptr_storage<Task> callbacks;

        void add_descriptor(int desc, Task callback, short filter){
            auto& new_event = events_to_add.emplace_back();
            memset(&new_event, 0, sizeof(new_event));

            new_event.ident = desc;
            new_event.filter = filter;
            new_event.flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
            new_event.udata = callbacks.put(std::move(callback));
        }

    public:
        void async_read(auto desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_READ);
        }

        void async_write(auto desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_WRITE);
        }

        ~kqueue_selector(){
            sys.close(kq);
        }

        kqueue_selector(){
            kq = sys.kqueue();
            if (kq < 0){
                throw std::runtime_error{"error when creating selector"};
            }
        }

        void loop(){
            while(1){
                while (events_to_process.second-1 >= events_to_process.first.size()){

                    std::cerr << "have " << events_to_add.size() << " events to add." << std::endl;
                    for (auto& event : events_to_add){
                        print_kevent(event);
                    }

                    sys.ignore(EINTR);
                    events_to_process.second = sys.kevent(
                        kq,
                        events_to_add.data(),
                        events_to_add.size(),
                        events_to_process.first.data(),
                        events_to_process.first.size(),
                        nullptr
                    );
                    events_to_add.clear();
                    if (errno == EINTR){
                        callbacks.clear();
                        std::cerr << "interrupted" << std::endl;
                        return;
                    }
                    std::cerr << "have " << events_to_process.second << " events to process." << std::endl;
                    for (size_t q = 0; q < events_to_process.second; ++q){
                        auto& event = events_to_process.first[q];
                        print_kevent(event);
                    }
                }
                sys.eassert(events_to_process.second != 0);
                for (size_t i = 0; i < events_to_process.second; ++i){
                    auto ptr = events_to_process.first[i].udata;
                    std::cerr << "using " << ptr << std::endl;
                    callbacks.get(ptr)();
                    std::cerr << "freeing " << ptr << std::endl;
                    callbacks.del(ptr);
                }
                events_to_process.second = 0;
            }
        }
    };

    static_assert(selector<kqueue_selector>);
#endif

#ifdef use_epoll
    void print_kevent(struct epoll_event& value){
        std::cerr << "event{" << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.ident) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.filter) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.flags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.fflags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.data) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.udata) << std::endl
        << "}" << std::endl;
    }

    struct epoll_selector{
    private:
        int kq = 0;
        std::pair<
            std::array<
                struct kevent,
                256
            >,
            size_t
        > events_to_process = {{}, 0};
        std::vector<
            struct kevent
        > events_to_add;
        void_ptr_storage<Task> callbacks;

        void add_descriptor(int desc, Task callback, short filter){
            auto& new_event = events_to_add.emplace_back();
            memset(&new_event, 0, sizeof(new_event));

            new_event.ident = desc;
            new_event.filter = filter;
            new_event.flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
            new_event.udata = callbacks.put(std::move(callback));
        }

    public:
        void async_read(auto desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_READ);
        }

        void async_write(auto desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_WRITE);
        }

        ~kqueue_selector(){
            sys.close(kq);
        }

        kqueue_selector(){
            kq = sys.kqueue();
            if (kq < 0){
                throw std::runtime_error{"error when creating selector"};
            }
        }

        void loop(){
            while(1){
                while (events_to_process.second-1 >= events_to_process.first.size()){

                    std::cerr << "have " << events_to_add.size() << " events to add." << std::endl;
                    for (auto& event : events_to_add){
                        print_kevent(event);
                    }

                    sys.ignore(EINTR);
                    events_to_process.second = sys.kevent(
                        kq,
                        events_to_add.data(),
                        events_to_add.size(),
                        events_to_process.first.data(),
                        events_to_process.first.size(),
                        nullptr
                    );
                    events_to_add.clear();
                    if (errno == EINTR){
                        callbacks.clear();
                        std::cerr << "interrupted" << std::endl;
                        return;
                    }
                    std::cerr << "have " << events_to_process.second << " events to process." << std::endl;
                    for (size_t q = 0; q < events_to_process.second; ++q){
                        auto& event = events_to_process.first[q];
                        print_kevent(event);
                    }
                }
                sys.eassert(events_to_process.second != 0);
                for (size_t i = 0; i < events_to_process.second; ++i){
                    auto ptr = events_to_process.first[i].udata;
                    std::cerr << "using " << ptr << std::endl;
                    callbacks.get(ptr)();
                    std::cerr << "freeing " << ptr << std::endl;
                    callbacks.del(ptr);
                }
                events_to_process.second = 0;
            }
        }
    };

    static_assert(selector<epoll_selector>);
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct socket_closer{
    int s;
    socket_closer(int s):
        s(s)
    {
        std::cerr << "started owning " << s << std::endl;
    }
    ~socket_closer(){
        std::cerr << "stopped owning " << s << std::endl;
        sys.close(s);
    }
};

struct socket_ptr{
    std::shared_ptr<socket_closer> ptr = nullptr;
    socket_ptr(int s = -1){
        if (s != -1){
            ptr = std::make_shared<socket_closer>(s);
        }
    }
    operator int(){
        assert(ptr.get());
        return ptr->s;
    }
    socket_ptr(const socket_ptr&) = default;
    socket_ptr(socket_ptr&&o) = default;
    socket_ptr& operator=(const socket_ptr&) = default;
    socket_ptr& operator=(socket_ptr&&o) = default;
};

auto create_non_blocking_socket(){
    socket_ptr s = sys.socket(AF_INET, SOCK_STREAM, 0);
    int flags = sys.fcntl(s, F_GETFL, 0);
    flags |= O_NONBLOCK;
    sys.fcntl(s, F_SETFL, flags);
    return s;
}

auto host_port_to_sockaddr(const char* addr, uint16_t port){
    union {
        sockaddr sa;
        sockaddr_in sai;
    } sau;
    memset(&sau, 0, sizeof(sau));
    sau.sai.sin_family = AF_INET;
    sau.sai.sin_port = htons(port);
    sys.eassert(sys.inet_pton(AF_INET, addr, &sau.sai.sin_addr) == 1);
    return sau.sa;
}

auto create_connecting_socket(const char* addr, uint16_t port){
    auto saddr = host_port_to_sockaddr(addr, port);
    auto s = create_non_blocking_socket();
    sys.ignore(EINPROGRESS);
    sys.connect(s, &saddr, sizeof(saddr));
    return s;
}

auto create_listening_socket(const char* addr, uint16_t port){
    auto saddr = host_port_to_sockaddr(addr, port);
    auto s = create_non_blocking_socket();
    sys.bind(s, &saddr, sizeof(saddr));
    sys.listen(s, 65536);
    return s;
}

auto start_server(auto& sel, const char* addr, uint16_t port, function<void(socket_ptr, const char*, uint16_t)> callback){
    auto s = create_listening_socket(addr, port);
    function<void()> func = [&sel, s, callback=std::move(callback)]()mutable{
        sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t client_len = sizeof(client);
        socket_ptr c = sys.accept(s, (sockaddr*)&client, &client_len);
        sys.eassert(client_len == sizeof(client));
        sys.eassert(client.sin_family == AF_INET);
        char client_addr[INET_ADDRSTRLEN];
        sys.inet_ntop(AF_INET, &client.sin_addr, client_addr, sizeof(client_addr));
        auto client_port = ntohs(client.sin_port);
        callback(c, client_addr, client_port);
        int s_ = s;
        auto& sel_ = sel;
        sel_.async_read(s_, std::move(*Task::current));
    };
    sel.async_read(s, std::move(func));
}

void handle(int signal){
    char data[64];
    memset(data, '?', sizeof(data));
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
    write(1, last, data + sizeof(data) - last);
}

int main() {
    for (int i = 0; i < 256 ; ++i){
        sys.ignore(EINVAL);
        sys.signal(i, handle);
    }

    #ifdef use_kqueue
    kqueue_selector sel;
    #endif

    #ifdef use_epoll
    epoll_selector sel;
    #endif

    start_server(sel, "0.0.0.0", 9999, [&](auto a, const char*addr, uint16_t port){
        std::cerr << "connected " << addr << ":" << port << std::endl;
        auto c = create_connecting_socket("127.0.0.1", 8888);
        sel.async_write(c, [&sel, a, c]()mutable{
            auto&& setup_mover = [&sel](socket_ptr r, socket_ptr w){
                struct connection_ctx{
                    socket_ptr r;
                    socket_ptr w;
                    std::array<char, 65536> data;
                    size_t begin;
                    size_t end;
                    std::unique_ptr<int> _; //todo remove
                    function<void()> reader;
                    function<void()> writer;
                    std::unique_ptr<connection_ctx>* reader_ctx;
                    std::unique_ptr<connection_ctx>* writer_ctx;
                };
                auto ctx = std::make_unique<connection_ctx>();
                memset(&*ctx, 0, sizeof(*ctx));
                ctx->r = r;
                ctx->w = w;
                ctx->reader = std::move([&sel, ctx_ = decltype(ctx)(), ctx_ptr = &ctx->reader_ctx]()mutable{
                    *ctx_ptr = &ctx_;
                    connection_ctx* ctx = ctx_.get();
                    if (not ctx){
                        std::cerr << "no ctx" << std::endl;
                        return;
                    }
                    assert(ctx->writer);
                    assert(not ctx->reader);
                    ctx->reader = std::move(*Task::current);
                    assert(ctx->begin == ctx->end);
                    ctx->begin = 0;
                    ctx->end = sys.read(ctx->r, ctx->data.data(), ctx->data.size());
                    if (ctx->end == 0){
                        sys.ignore(ENOTCONN);
                        sys.shutdown(ctx->r, SHUT_RD);
                        sys.ignore(ENOTCONN);
                        sys.shutdown(ctx->w, SHUT_WR);
                        std::cerr << "EOF " << ctx->r << std::endl;
                        std::cerr << ctx->r << ".use_count = " << ctx->r.ptr.use_count() << std::endl;
                        std::cerr << ctx->w << ".use_count = " << ctx->w.ptr.use_count() << std::endl;
                        auto r = ctx->r;
                        auto w = ctx->w;
                        std::cerr << r << ".use_count = " << r.ptr.use_count() << std::endl;
                        std::cerr << w << ".use_count = " << w.ptr.use_count() << std::endl;
                        ctx_.reset();
                        std::cerr << r << ".use_count = " << r.ptr.use_count() << std::endl;
                        std::cerr << w << ".use_count = " << w.ptr.use_count() << std::endl;
                        r.ptr.reset();
                        w.ptr.reset();
                        std::cerr << 0 << ".use_count = " << r.ptr.use_count() << std::endl;
                        std::cerr << 0 << ".use_count = " << w.ptr.use_count() << std::endl;
                        return;
                    }
                    assert(0 <= ctx->begin);
                    assert(ctx->begin < ctx->end);
                    assert(ctx->end <= ctx->data.size());
                    *ctx->writer_ctx = std::move(ctx_);
                    sel.async_write(ctx->w, std::move(ctx->writer));
                });
                ctx->reader();
                ctx->writer = std::move([&sel, ctx_ = decltype(ctx)(), ctx_ptr = &ctx->writer_ctx]()mutable{
                    *ctx_ptr = &ctx_;
                    connection_ctx* ctx = ctx_.get();
                    if (not ctx){
                        std::cerr << "no ctx" << std::endl;
                        return;
                    }
                    assert(ctx->reader);
                    assert(not ctx->writer);
                    ctx->writer = std::move(*Task::current);
                    assert(0 <= ctx->begin);
                    assert(ctx->begin < ctx->end);
                    assert(ctx->end <= ctx->data.size());
                    ctx->begin += sys.write(ctx->w, ctx->data.data() + ctx->begin, ctx->end - ctx->begin);
                    assert(0 <= ctx->begin);
                    assert(ctx->begin <= ctx->end);
                    assert(ctx->end <= ctx->data.size());
                    if (ctx->begin == ctx->end){
                        *ctx->reader_ctx = std::move(ctx_);
                        sel.async_read(ctx->r, std::move(ctx->reader));
                    }else{
                        sel.async_write(ctx->r, std::move(ctx->writer));
                    }
                });
                ctx->writer();
                assert(ctx->writer_ctx);
                assert(ctx->reader_ctx);
                auto ctx_ = ctx.get();
                *ctx->reader_ctx = std::move(ctx);
                sel.async_read(ctx_->r, std::move(ctx_->reader));
            };
            setup_mover(a,c);
            setup_mover(c,a);

        });



    });

    sel.loop();

}
