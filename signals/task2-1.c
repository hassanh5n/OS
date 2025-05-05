#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    
    if (sigaction(SIGKILL, &sa, NULL) == -1)
        printf("Cannot ignore SIGKILL: %s\n", strerror(errno));


    if (sigaction(SIGSTOP, &sa, NULL) == -1)
        printf("Cannot ignore SIGSTOP: %s\n", strerror(errno));

 
    while (1) {
        sleep(1);
    }

    return 0;
}

