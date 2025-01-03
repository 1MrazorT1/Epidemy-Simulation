#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

static int pid;
static int duration;

void manage_error_and_exit() {
    perror("Critical error occurred!");
    exit(EXIT_FAILURE);
}

void handle_alarm(int sig) {
    if (sig != SIGALRM) return;

    if (kill(pid, SIGUSR1) == -1) {
        perror("Failed to send SIGUSR1 signal to target process");
        manage_error_and_exit();
    }

    printf("SIGALRM received. Sent SIGUSR1 to PID %d.\n", pid);

    alarm(duration);  // Reset the alarm
}

void set_timer(int target_pid, int interval) {
    pid = target_pid;
    duration = interval;

    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("Error setting signal handler");
        manage_error_and_exit();
    }

    printf("Timer initialized for PID %d with interval %d seconds.\n", pid, duration);

    alarm(duration);  // Start the timer
}
