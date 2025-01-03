#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

void manage_error_and_exit() {
    perror("Critical error occurred!");
    exit(EXIT_FAILURE);
}

void handle_alarm(int sig) {}

void set_timer(int target_pid, int interval) {}
