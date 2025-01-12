#ifndef EPIDEMIC_SIM
#define EPIDEMIC_SIM

/**
 * @file epidemic_simulation.h

 * @brief Prototypes of functions used by epidemic_simulation.c
 */


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

/**
 * @brief Confiure and initialise the shared memory.
 * @return A pointer to a SimulationMemory structure which represents the shared memory.
 */
SimulationMemory* setup_shared_memory();


/**
 * @brief Manage the timer process in the epidemic simulation
 * @details 
 */
void manage_timer();

/**
 * @brief Manage the citizen manager process in the epidemic simulation.
 * Accesses and update the shared memory to store citizen_manager's PID. 
 * Runs citizen_manager in a child process.
 */
void manage_citizen_manager();


/**
 * @brief Manage the press_agency process in the epidemic simulation.
 * @details 
 */
void manage_press_agency();

/**
 * @brief Manage the viewer process in the epidemic simulation.
 * @details 
 */
void manage_viewer();


/**
 * @brief Manage the timer process in the epidemic simulation
 * @details 
 */
void epidemic_simulation();

/**
 * @brief Start the epidemic simulation. In the parent process, 
 * it runs the function which manages signal to coordinate all the sub programs.
 * The child process runs all the sub programs. 
 */
void start_simulation();


/**
 * @brief Ends the epidemic simulation and clean ressources 
 *
 * @details Terminates the simulation by accessing to the shared memory. 
 * Sends signals to child processes to terminate them.
 * Releases ressources.
 *
 * @param 
 */
void end_simulation(int signal);



/**
 * @brief Function to update the simulation after a day has passed.
 * @details Update the map and characters accordind to the rules of the epidemic simulation.
 */
void next_day();



#endif
