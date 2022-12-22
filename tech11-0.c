#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <sched.h>

int exit_pipe[2];


void handler(int sig) {
    char msg[] = "123";
    write(exit_pipe[1], msg, sizeof(msg));
}


int main() {
    pipe(exit_pipe);

    dprintf(2, "signal\n");
    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    
    sigaction(SIGINT, &sa, NULL);
    
    int epoll_fd = epoll_create1(0);  // no flags
    
    fcntl(exit_pipe[0], F_SETFL, O_NONBLOCK);
    fcntl(0, F_SETFL, O_NONBLOCK);
    
    int fifo_fd = open("test_fifo", O_RDONLY);
    fcntl(fifo_fd, F_SETFL, O_NONBLOCK);
    
    dprintf(2, "epoll_ctl...\n");
    int all_fds[] = {exit_pipe[0], 0, fifo_fd};
    for (int i = 0; i < 3; ++i) {
        struct epoll_event event = {
            .events = EPOLLIN,
            .data.fd = all_fds[i]
        };
        
        // Будем ожидать готовности на чтение
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, all_fds[i], &event);
    }
    
    dprintf(2, "Main loop\n");
    while (1) {
        struct epoll_event event;
        int N = epoll_wait(epoll_fd, &event, /*maxevents=*/ 1, /*timeout=*/ 1000);
        
        if (N <= 0) {
            sched_yield();
            continue;
        }
        
        int fd = event.data.fd;
        
        if (fd == exit_pipe[0]) {
            break;
        }
        
        char buffer[1024];
        size_t len = read(fd, buffer, sizeof(buffer));
        write(1, buffer, len);
    }
    
    dprintf(2, "Closing all\n");
    
    for (int i = 0; i < 3; ++i) {
        close(all_fds[i]);
    }
    
    close(epoll_fd);
    
    dprintf(2, "Exiting...\n");
    
    return 0;
}
