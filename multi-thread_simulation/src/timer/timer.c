#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

// Global variables to store PID and interval duration
static int pid;
static int duration;

// Function to handle critical errors and exit
void manage_error_and_exit() {
    perror("Critical error occurred!");
    exit(EXIT_FAILURE);
}

// Signal handler for SIGALRM
void handle_alarm(int sig) {
    if (sig != SIGALRM) return;  // Ensure it's an ALRM signal

    // Send SIGUSR1 to the target process
    if (kill(pid, SIGUSR1) == -1) {
        perror("Failed to send SIGUSR1 signal to target process");
        manage_error_and_exit();
    }

    printf("SIGALRM received. Sent SIGUSR1 to PID %d.\n", pid);

    // Reset the alarm for the next interval
    alarm(duration);
}

// Function to initialize the timer
void set_timer(int target_pid, int interval) {
    pid = target_pid;
    duration = interval;

    // Attach handle_alarm() to SIGALRM
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("Error setting signal handler");
        manage_error_and_exit();
    }

    printf("Timer initialized for PID %d with interval %d seconds.\n", pid, duration);

    // Start the timer
    alarm(duration);
}
