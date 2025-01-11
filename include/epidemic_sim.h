#ifndef EPIDEMIC_SIM
#define EPIDEMIC_SIM

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include "simulation_memory.h"
#include "posix_semaphore.h"

#define SHM_NAME "epidemic_shared_memory"
#define MAX_CITIZENS 100

typedef struct {
    int healthy;
    int sick;
    int dead;
    int burned;
} CityState;

SimulationMemory* setup_shared_memory();
void manage_timer();
void manage_citizen_manager();
void manage_press_agency();
void manage_viewer();
void manage_epidemic_simulation();
void start_simulation();
void end_simulation(int signal);


#endif
