// timer.h
#ifndef TIMER_H
#define TIMER_H
void manage_error_and_exit();
void handle_alarm(int sig);
void set_timer(int target_pid, int interval);
#endif

/**
* @file timer.h
*
*  @brief This file contains functions used to manage the timer in order 
* to indicate the next day and the end of the epidemic simulation.
*
*/


