/**
 * File: recv_signal.c
 * Modified by: Dillon Fayas
 * 
 * Brief summary of program: Receives a SIGUSR1 signal and prints the integer value sent with it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 with value: %d\n", info->si_value.sival_int);
}

int main() {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while (1) {
        pause();
    }

    return 0;
}