#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// volatile - ОБЯЗАТЕЛЬНО!
volatile int int_cnt = 0;

volatile int is_running = 1;

void handler(int sig_num) {
    if (sig_num == SIGINT) {
        ++int_cnt;
    } else if (sig_num == SIGTERM) {
        is_running = 0;
    }
}

int main() {

    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART,
    };
    
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    
    printf("%d\n", getpid());
    fflush(stdout);

    while (is_running) {
        pause();
    }
    printf("%d\n", int_cnt);


    return 0;
}

