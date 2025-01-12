#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include "timer.h"

// Flag to track signal reception
static int signal_received = 0;

// Mock signal handler to track SIGUSR1
void mock_signal_handler(int sig) {
    if (sig == SIGUSR1) {
        signal_received = 1;
        printf("Mock signal handler: SIGUSR1 received.\n");
    }
}

// Test for set_timer function
void test_set_timer() {
    printf("Test: set_timer...\n");

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Error forking child process");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process: Wait and handle signal
        if (signal(SIGUSR1, mock_signal_handler) == SIG_ERR) {
            perror("Error setting mock signal handler");
            exit(EXIT_FAILURE);
        }

        // Sleep to allow parent to send signals
        sleep(5);
        exit(signal_received ? EXIT_SUCCESS : EXIT_FAILURE);
    } else {
        // Parent process: Set timer targeting the child process
        set_timer(child_pid, 2);

        // Wait for child to complete
        int status;
        waitpid(child_pid, &status, 0);

        // Verify child exited successfully
        assert(WIFEXITED(status));
        assert(WEXITSTATUS(status) == EXIT_SUCCESS);

        printf("OK\n");
    }
}

int main() {
    printf("Running tests for timer module...\n\n");

    test_set_timer();

    printf("\nAll tests passed successfully!\n");
    return 0;
}
