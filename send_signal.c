/**
 * File: send_signal.c
 * Modified by: Dillon Fayas
 * 
 * Brief summary of program: Sends a SIGUSR1 signal with a random integer value to a specified process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);

    srand(time(NULL));
    int value = rand() % 100;

    union sigval sig_data;
    sig_data.sival_int = value;

    printf("Sending SIGUSR1 with value: %d to process %d\n", value, pid);

    if (sigqueue(pid, SIGUSR1, sig_data) == -1) {
        perror("sigqueue");
        exit(EXIT_FAILURE);
    }

    return 0;
}