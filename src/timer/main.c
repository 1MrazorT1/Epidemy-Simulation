#include <stdio.h>
#include "timer.h"

int main() {
    printf("Testing error management\n");

    // Simulate an error condition and call the function
    manage_error_and_exit();

    return 0;
}
