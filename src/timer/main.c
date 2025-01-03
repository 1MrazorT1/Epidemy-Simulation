#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "timer.h"

int main(int argc, char *argv[]) {
    // Check for valid command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <duration>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse PID and interval duration
    int pid = atoi(argv[1]);
    int duration = atoi(argv[2]);

    // Validate PID and duration
    if (pid <= 0 || duration <= 0) {
        fprintf(stderr, "Invalid PID or duration\n");
        return EXIT_FAILURE;
    }

    printf("Starting timer for PID %d with duration %d seconds.\n", pid, duration);

    // Initialize the timer
    set_timer(pid, duration);

    // Keep the program running to process SIGALRM
    while (1) {
        pause();  // Wait for incoming signals
    }

    return 0;
}
