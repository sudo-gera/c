#include <stdexcept>
#include <array>
#include <cassert>
#include <cerrno>
#include <iostream>
#include <string>
#include <functional>
#include <arpa/inet.h>

#define TEXT_AS_STR(x) #x
#define VALUE_AS_STR(x) TEXT_AS_STR(x)
#define SYSCALL for (errno = 0;;({if (errno) {perror("SYSCALL ERROR: " __FILE__ ":" VALUE_AS_STR(__LINE__));}break;}))

#define VALUE_AS_STRING_AND_VALUE(x) #x << "\t\t\t\t" << x

struct descriptor_info{

};

#if 1

    #include <stdio.h>
    #include <stdlib.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/event.h>
    #include <string.h>
    #include <unistd.h>

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
    // private:

        int kq = 0;
        std::pair<
            std::array<
                struct kevent,
                256
            >,
            size_t
        > events_to_process;
        std::pair<
            std::array<
                struct kevent,
                std::tuple_size_v<
                    decltype(events_to_process)
                > * 2
            >,
            size_t
        > events_to_add;

    public:
        void add_descriptor(int desc, void* data, short filter){
            assert(events_to_add.second < events_to_add.first.size());
            auto& new_event = events_to_add.first[events_to_add.second++];
            memset(&new_event, 0, sizeof(new_event));

            new_event.ident = desc;
            new_event.filter = filter;
            new_event.flags = EV_ADD | EV_ENABLE | EV_ONESHOT;
            new_event.udata = data;
        }

        Selector(){
            SYSCALL kq = kqueue();
            if (kq < 0){
                throw std::runtime_error{"error when creating selector"};
            }
        }

        struct kevent select(){
            if (events_to_process.second == 0){
                SYSCALL events_to_process.second = kevent(
                    kq,
                    events_to_add.first.data(),
                    events_to_add.second,
                    events_to_process.first.data(),
                    events_to_process.first.size(),
                    nullptr
                );
                events_to_add.second = 0;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.second) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].ident) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].filter) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].flags) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].fflags) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].data) << std::endl;
                std::cout << VALUE_AS_STRING_AND_VALUE(events_to_process.first[0].udata) << std::endl;
                if (events_to_process.second == 0-1LLU){
                    throw std::runtime_error{"kevent"};
                }
            }
            assert(events_to_process.second != 0);
            return events_to_process.first[--events_to_process.second];
        }
    };

#endif



int main(int argc, char**argv){
    assert(argc >= 1);
    uint16_t listen_port = std::stol(argv[1]);

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

    Selector selector;

    std::function<void()> handle_new_client = [&](){
        sockaddr_in server_socket_info;
        memset(&server_socket_info, 0, sizeof(server_socket_info));
        socklen_t server_socket_info_len = 0;
        int server_socket = 0;
        SYSCALL server_socket = accept(listen_socket, (struct sockaddr*)&server_socket_info, &server_socket_info_len);
        if (server_socket < 0){
            throw std::runtime_error{"server_socket accepting failed."};
        }

        int client_socket = 0;
        SYSCALL client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket < 0){
            throw std::runtime_error{"client socket creation failed."};
        }
        struct sockaddr_in client_socket_info;
        memser(&client_socket_info, 0, sizeof(client_socket_info));
        client_socket_info.sin_family = AF_INET;
        client_socket_info.sin_addr.s_addr = inet_addr("127.0.0.1");
        client_socket_info.sin_port = htons(22);

        int ret = 0;
        SYSCALL ret = connect(client_socket, (const struct sockaddr*)&client_socket_info, sizeof(client_socket_info));
        if (ret < 0){
            throw std::runtime_error{"client socket connecting failed."};
        }

        std::function<void()> handle_client_read = [&](){
            char data[65536];
            SYSCALL recv(client_socket, data, sizeof(data), 0);
            ///
        }

        selector.add_descriptor(server_socket, new std::function<void()>(handle), EVFILT_READ);
        selector.add_descriptor(client_socket, new std::function<void()>(handle_client_read), EVFILT_READ);
        selector.add_descriptor(listen_socket, new std::function<void()>(handle_new_client), EVFILT_READ);
    };

    selector.add_descriptor(listen_socket, new std::function<void()>(handle_new_client), EVFILT_READ);

    while (true){
        struct kevent event = selector.select();
        auto func_ptr = (std::function<void()>*)event.udata;
        func_ptr[0]();
        delete func_ptr;
    }
}

int main()
{
    // All needed variables.
    int socket_listen_fd,
        portno = 1815,
        client_len,
        socket_connection_fd,
        kq,
        new_events;
    struct kevent change_event[4],
        event[4];
    struct sockaddr_in serv_addr,
        client_addr;

    // Create socket.
    if (((socket_listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0))
    {
        perror("ERROR opening socket");
        exit(1);
    }

    // Create socket structure and bind to ip address.
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(socket_listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket");
        exit(1);
    }

    // Start listening.
    listen(socket_listen_fd, 3);
    client_len = sizeof(client_addr);

    // Prepare the kqueue.
    // kq = kqueue();
    auto selector = Selector();

    // Create event 'filter', these are the events we want to monitor.
    // Here we want to monitor: socket_listen_fd, for the events: EVFILT_READ 
    // (when there is data to be read on the socket), and perform the following
    // actions on this kevent: EV_ADD and EV_ENABLE (add the event to the kqueue 
    // and enable it).
    // EV_SET(change_event, socket_listen_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

    // Register kevent with the kqueue.
    // if (kevent(kq, change_event, 1, NULL, 0, NULL) == -1)
    // {
    //     perror("kevent");
    //     exit(1);
    // }
    selector.add_descriptor(socket_listen_fd, nullptr, EVFILT_READ);

    // Actual event loop.
    for (;;)
    {
        // Check for new events, but do not register new events with
        // the kqueue. Hence the 2nd and 3rd arguments are NULL, 0.
        // Only handle 1 new event per iteration in the loop; 5th
        // argument is 1.
        // SYSCALL new_events = kevent(selector.kq, 0,0, 0, 0, NULL);
        // if (new_events == -1)
        // {
        //     perror("kevent");
        //     exit(1);
        // }
        // SYSCALL new_events = kevent(selector.kq, selector.events_to_add.first.data(), selector.events_to_add.second, 0, 0, NULL);
        // if (new_events == -1)
        // {
        //     perror("kevent");
        //     exit(1);
        // }
        // SYSCALL new_events = kevent(selector.kq, NULL, 0, event, 1, NULL);
        new_events = 1;
        event[0] = selector.select();
        // if (new_events == -1)
        // {
        //     perror("kevent");
        //     exit(1);
        // }

        for (int i = 0; new_events > i; i++)
        {
            printf("amount of new events: %d\n", new_events);
            int event_fd = event[i].ident;

            // When the client disconnects an EOF is sent. By closing the file
            // descriptor the event is automatically removed from the kqueue.
            if (event[i].flags == EV_EOF)
            {
                printf("Client has disconnected\n");
               close(event_fd);
            }
            // If the new event's file descriptor is the same as the listening
            // socket's file descriptor, we are sure that a new client wants 
            // to connect to our socket.
            else if (event_fd == socket_listen_fd)
            {
                printf("New connection coming in...\n");    

                // Incoming socket connection on the listening socket.
                // Create a new socket for the actual connection to client.
                socket_connection_fd = accept(event_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
                if (socket_connection_fd == -1)
                {
                    perror("Accept socket error");
                }

                // Put this new socket connection also as a 'filter' event
                // to watch in kqueue, so we can now watch for events on this
                // new socket.
                // EV_SET(change_event, socket_connection_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                // if (kevent(kq, change_event, 1, NULL, 0, NULL) < 0)
                // {
                //     perror("kevent error");
                // }
                selector.add_descriptor(socket_connection_fd, nullptr);
            }

            else if (event[i].filter == EVFILT_READ)
            {
                // Read bytes from socket
                char buf[1024];
                size_t bytes_read = recv(event_fd, buf, sizeof(buf), 0);
                printf("read %zu bytes\n", bytes_read);
            }
        }
    }

    return 0;
}


