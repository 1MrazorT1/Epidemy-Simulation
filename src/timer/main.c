#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "timer.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <duration>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pid = atoi(argv[1]);
    int duration = atoi(argv[2]);

    if (pid <= 0 || duration <= 0) {
        fprintf(stderr, "Invalid PID or duration\n");
        return EXIT_FAILURE;
    }

    printf("Starting timer for PID %d with duration %d seconds.\n", pid, duration);

    set_timer(pid, duration);  // Initialize the timer

    // Keep the program running to allow SIGALRM to be processed
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}
