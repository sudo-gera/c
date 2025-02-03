#include <stdexcept>
#include <array>
#include <cassert>
#include <cerrno>
#include <iostream>
#include <string>
#include <functional>
#include <arpa/inet.h>
#include <signal.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <new>
#include <sstream>
#include <list>
#include <map>
#include <csignal>
#include <cerrno>

// debug

#define TEXT_AS_STR(x) #x
#define VALUE_AS_STR(x) TEXT_AS_STR(x)
#define SYSCALL for (errno = 0;;({if (errno) {perror("SYSCALL ERROR: " __FILE__ ":" VALUE_AS_STR(__LINE__));}break;}))

#define VALUE_AS_STRING_AND_VALUE(x) #x << "\t\t\t\t" << x

#define assert_m(...) assert_f(__VA_ARGS__,#__VA_ARGS__)

bool assert_f(bool q,std::string f){
	bool*a=&q;
	if (not q){
		std::cerr<<"\x1b[91massertion failed: \x1b[0m"<<f<<std::endl;
		while (a){
			q=*++a;
		}
	}
	return q;
}

#define safe_assert assert_m

std::mutex cout_mutex;
struct Print: std::stringstream{
    ~Print(){
        std::unique_lock lock(cout_mutex);
        std::cout << str();
    }
};

// cache friendly constans

#ifdef __cpp_lib_hardware_interference_size
    using std::hardware_constructive_interference_size;
    using std::hardware_destructive_interference_size;
#else // from cppreference
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif

// threading

std::atomic<bool> have_to_stop = false;

template<typename T>
struct QueueMPMC{
    std::mutex m;
    std::condition_variable cv;
    std::queue<T> q;
    std::atomic<size_t> size;
    void push(T val){
        std::unique_lock lock(m);
        q.push(std::move(val));
        cv.notify_one();
        ++size;
    }
    std::optional<T> pop_nowait(){
        std::unique_lock lock(m);
        std::optional<T> result;
        if (q.empty()){
            return result;
        }
        result.emplace(std::move(q.front()));
        q.pop();
        --size;
        return result;
    }
    std::optional<T> pop_wait(){
        std::unique_lock lock(m);
        while (q.empty()){
            if (have_to_stop){
                return std::optional<T>();
            }
            cv.wait(lock);
        }
        auto tmp = std::move(q.front());
        q.pop();
        --size;
        return tmp;
    }
};

using Task = std::function<void()>;

std::vector<std::string> args;

struct alignas(hardware_destructive_interference_size) thread_info{
    std::thread thread;
    QueueMPMC<Task> queue;
};

thread_local size_t current_thread_num = -1;

std::vector<thread_info> threads(std::thread::hardware_concurrency());

thread_local auto random_thread_num = [
    dis = std::uniform_int_distribution<size_t>(0, threads.size()-1),
    gen = std::mt19937_64(std::random_device()())
]()mutable{
    return dis(gen);
};

void push_task(Task t){
    size_t q = random_thread_num();
    size_t w = random_thread_num();
    if (threads[q].queue.size > threads[w].queue.size){
        q = w;
    }
    threads[q].queue.push(std::move(t));
}

std::optional<Task> pop_task(){
    auto task = threads[current_thread_num].queue.pop_nowait();
    if (task){
        return task;
    }
    size_t q = random_thread_num();
    size_t w = random_thread_num();
    if (threads[q].queue.size < threads[w].queue.size){
        q = w;
    }
    task = threads[q].queue.pop_nowait();
    if (task){
        return task;
    }
    for (auto& thread: threads){
        auto task = thread.queue.pop_nowait();
        if (task){
            return task;
        }
    }
    return threads[current_thread_num].queue.pop_wait();
}

// callbacks

struct callback_storer;
using callback_storage = std::map<size_t, callback_storer>;
using callback_storage_iter = callback_storage::iterator;

struct callback_storer{
    Task task;
    callback_storage_iter iter;
};

#if 1

    #include <stdio.h>
    #include <stdlib.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/event.h>
    #include <string.h>
    #include <unistd.h>

    void print_kevent(struct kevent& value){
        Print() << "kevent{" << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.ident) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.filter) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.flags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.fflags) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.data) << std::endl
        << "      " << VALUE_AS_STRING_AND_VALUE(value.udata) << std::endl
         << "}" << std::endl;
    }

    /*
    int kevent(
        int kq,
        const struct kevent *changelist, // ro-list of changes in the queue (add fd, rm fd, etc...)
        int nchanges,                    // len of list above
        struct kevent *eventlist,        // wo-list to output received events
        int nevents,                     // len of list above
        const struct timespec *timeout
    )
    */

    struct Selector{
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
        std::mutex m;
        callback_storage callbacks;
        size_t callbacks_num = 0;

        void add_descriptor(int desc, Task callback, short filter){
            std::unique_lock lock(m);
            auto& new_event = events_to_add.emplace_back();
            memset(&new_event, 0, sizeof(new_event));

            auto tmp = callbacks.insert({callbacks_num++, {std::move(callback), {}}});
            assert(tmp.second);
            tmp.first->second.iter = tmp.first;

            new_event.ident = desc;
            new_event.filter = filter;
            new_event.flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
            new_event.udata = &tmp.first->second.iter;


            Print() << "have " << events_to_add.size() << " events to add." << std::endl;
            for (auto& event : events_to_add){
                print_kevent(event);
            }

            int ret = 0;
            SYSCALL ret = kevent(
                kq,
                events_to_add.data(),
                events_to_add.size(),
                0,
                0,
                nullptr
            );
            if (ret < 0){
                throw std::runtime_error{"kevent_add"};
            }
            events_to_add.resize(0);
        }

    public:
        void add_descriptor_read(int desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_READ);
        }

        void add_descriptor_write(int desc, Task callback){
            add_descriptor(desc, std::move(callback), EVFILT_WRITE);
        }

        Selector(){
            SYSCALL kq = kqueue();
            if (kq < 0){
                throw std::runtime_error{"error when creating selector"};
            }
        }

        void select_loop(){
            while(1){
                while (events_to_process.second-1 >= events_to_process.first.size()){
                    SYSCALL events_to_process.second = kevent(
                        kq,
                        0,
                        0,
                        events_to_process.first.data(),
                        events_to_process.first.size(),
                        nullptr
                    );
                    if (events_to_process.second == size_t(-1)){
                        if (errno == EINTR){
                            have_to_stop = true;
                            callbacks.clear();
                            for (auto& thread: threads){
                                thread.queue.cv.notify_all();
                            }
                            return;
                        }
                        throw std::runtime_error{"kevent"};
                    }
                    Print() << "have " << events_to_process.second << " events to process." << std::endl;
                    for (size_t q = 0; q < events_to_process.second; ++q){
                        auto& event = events_to_process.first[0];
                        print_kevent(event);
                    }
                }
                safe_assert(events_to_process.second != 0);
                auto tmp = events_to_process.first[--events_to_process.second];
                auto iter = *(callback_storage_iter*)(tmp.udata);
                auto task = std::move(iter->second.task);
                task();
                {
                    std::unique_lock lock(m);
                    callbacks.erase(iter);
                }
            }
        }
    };

#endif

// socket syscall wrapper

Selector selector;

int create_listen_socket(uint16_t listen_port){
    int listen_socket = 0;
    SYSCALL listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket < 0){
        throw std::runtime_error{"listen socket creation failed."};
    }

    struct sockaddr_in listen_socket_info;
    memset(&listen_socket_info, 0, sizeof(listen_socket_info));

    listen_socket_info.sin_family = AF_INET;
    listen_socket_info.sin_addr.s_addr = INADDR_ANY;
    listen_socket_info.sin_port = htons(listen_port);

    int ret = 0;
    SYSCALL ret = bind(listen_socket, (const struct sockaddr*)&listen_socket_info, sizeof(listen_socket_info));
    if (ret < 0){
        throw std::runtime_error{"listen socket binding failed."};
    }
    listen(listen_socket, 65536);
    return listen_socket;
}

int create_connect_socket(uint16_t listen_port, const char* address){
    int client_socket = 0;
    SYSCALL client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0){
        throw std::runtime_error{"client socket creation failed."};
    }

    struct sockaddr_in client_socket_info;
    memset(&client_socket_info, 0, sizeof(client_socket_info));

    client_socket_info.sin_family = AF_INET;
    client_socket_info.sin_addr.s_addr = inet_addr(address);
    client_socket_info.sin_port = htons(listen_port);

    int ret = 0;
    SYSCALL ret = connect(client_socket, (const struct sockaddr*)&client_socket_info, sizeof(client_socket_info));
    if (ret < 0){
        throw std::runtime_error{"client socket connecting failed."};
    }

    return client_socket;
}

int create_accept_socket(int listen_socket){
    struct sockaddr_in client_socket_info;
    memset(&client_socket_info, 0, sizeof(client_socket_info));

    socklen_t client_socket_info_len = sizeof(client_socket_info);

    int client_socket = 0;
    SYSCALL client_socket = accept(listen_socket, (struct sockaddr*)&client_socket_info, &client_socket_info_len);
    if (client_socket < 0){
        throw std::runtime_error{"client socket connecting failed."};
    }

    return client_socket;
}

// socket interface

struct Socket{

    alignas(hardware_destructive_interference_size)
    const int read_socket = 0;
    std::atomic<bool> has_read_task = false;
    std::pair<
        std::array<char, 65536>,
        int
    > read_buffer = {{}, 0};

    alignas(hardware_destructive_interference_size)
    const int write_socket = 0;
    std::atomic<bool> has_write_task = false;
    std::pair<
        std::array<char, 65536>,
        int
    > write_buffer = {{}, 0};


    Socket(int socket): read_socket(socket), write_socket(socket) {
    }

    void async_read(Task then){
        safe_assert (not has_read_task);
        has_read_task = true;
        selector.add_descriptor_read(read_socket, Task([&, then=then](){
            safe_assert (has_read_task);
            has_read_task = false;
            SYSCALL read_buffer.second = read(read_socket, read_buffer.first.data(), read_buffer.first.size());
            push_task(std::move(then));
        }));
    }

    void async_write(Task then){
        safe_assert (not has_write_task);
        has_write_task = true;
        // safe_assert(write_buffer.second);
        selector.add_descriptor_write(write_socket, Task([&, then=then](){
            safe_assert(write_buffer.second < write_buffer.first.size());
            Print() << "have " << write_buffer.second << " bytes to write." << std::endl;
            size_t written = 0;
            SYSCALL written = write(write_socket, write_buffer.first.data(), write_buffer.second);
            Print() << "could write " << written << " bytes." << std::endl;
            write_buffer.second -= written;
            safe_assert (has_write_task);
            has_write_task = false;
            if (write_buffer.second == 0 or written < 0){
                write_buffer.second = written;
                push_task(std::move(then));
                return;
            }
            memmove(write_buffer.first.data(), write_buffer.first.data() + written, write_buffer.second);
            async_write(std::move(then));
        }));
    }

    ~Socket(){
        SYSCALL close(read_socket);
        assert(read_socket == write_socket);
    }
};

// work with sockets

void copy(std::shared_ptr<Socket> r, std::shared_ptr<Socket> w){
    r->async_read([r=r, w=w](){
        if (r->read_buffer.second <= 0){
            SYSCALL shutdown(r->read_socket, SHUT_RD);
            SYSCALL shutdown(w->write_socket, SHUT_WR);
            return;
        }
        w->write_buffer.second = r->read_buffer.second;
        memmove(w->write_buffer.first.data(), r->read_buffer.first.data(), r->read_buffer.second);
        w->async_write([r=r, w=w](){
            if (w->write_buffer.second < 0){
                SYSCALL shutdown(r->read_socket, SHUT_RD);
                SYSCALL shutdown(w->write_socket, SHUT_WR);
                return;
            }
            copy(r, w);
        });
    });
}

void handle_new_socket(int accept_socket){
    Print() << "handled socket " << accept_socket << std::endl;
    auto as = std::make_shared<Socket>(accept_socket);

    Print() << "connecting to " << args[2] << ":" << args[3] << std::endl;
    int connect_socket = create_connect_socket(std::stol(args[3]), args[2].data());
    Print() << "made socket " << connect_socket << std::endl;
    auto cs = std::make_shared<Socket>(connect_socket);

    copy(as, cs);
    copy(cs, as);
}

// handle signals

void sighandler(int){
    char message[] = "exiting...\n";
    write(1, message, sizeof(message)-1);
}

// main

int main(int argc, char**argv){
    SYSCALL signal(SIGHUP, sighandler);
    SYSCALL signal(SIGINT, sighandler);
    SYSCALL signal(SIGQUIT, sighandler);
    SYSCALL signal(SIGTERM, sighandler);

    args = decltype(args)(argv, argv+argc);
    safe_assert(args.size() == 4);

    uint16_t listen_port = std::stol(argv[1]);

    int listen_socket = create_listen_socket(listen_port);

    Task setup_accept_handler = [&](){
        selector.add_descriptor_read(listen_socket, Task([&](){
            int accept_socket = create_accept_socket(listen_socket);
            push_task([&](){
                handle_new_socket(accept_socket);
            });
            setup_accept_handler();
        }));
    };
    setup_accept_handler();

    for (auto& thread: threads){
        size_t current_thread_num_ = &thread - &threads[0];
        thread.thread = std::thread([&, current_thread_num_=current_thread_num_](){
            current_thread_num = current_thread_num_;
            while (1){
                auto task = pop_task();
                if (not task.has_value()){
                    break;
                }
                task.value()();
            }
        });
    }

    selector.select_loop();

    for (auto& thread: threads){
        thread.thread.join();
    }

    SYSCALL close(listen_socket);

    Print() << " all threads joined. " << std::endl;
}

