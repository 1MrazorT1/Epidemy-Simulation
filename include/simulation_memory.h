#ifndef SIMULATION_MEMORY_H
#define SIMULATION_MEMORY_H

/**
 * @file simulation_memory.h

 * @brief This file defines structures and functions used to work on the shared memory.
 * 
 */


#include <sys/types.h>
#include "citizen_manager.h"

#define SIMULATION_MEMORY_PATH "/epidemic2023"
#define CITY_ROWS    7
#define CITY_COLUMNS 7
#define MAX_NORMAL_CITIZEN 25
#define MAX_FIREFIGHTER 6
#define MAX_DOCTORS 4




typedef struct simulation_memory_s SimulationMemory;

struct simulation_memory_s {
    char headline_of_the_day[255];
    int day;
    pid_t pid_epidemic_sim;
    int buildings[7][7];
    double contamination_level[7][7];
    int n_of_citizens[7][7];
    int n_of_firefighters[7][7];
    int n_of_doctors[7][7];
    int n_of_dead_citizens[7][7];
    int n_of_ashes[7][7];
    status_p* citizens[MAX_NORMAL_CITIZEN];
    status_p* firefighters[6];
    status_p* doctors[4];
    status_p* dead_citizens[MAX_NORMAL_CITIZEN];
    status_p* ashes[MAX_NORMAL_CITIZEN];

    character_thread_t* citizen_threads[MAX_NORMAL_CITIZEN];

    int has_simulation_ended; /*
                            if 0 not
                            else yes but need to precise the end situation
                            */
    int pids[5];
    /*
    pids[0] : epidemic_simulation 
    pids[1]: citizen manager
    pids[2]: timer
    pids[3] : press agency 
    pid[4] : viewer
    */
};

/**
* @brief Sets the headline of the day in the simulation memory.
*
* @param SimulationMemory pointer to the shared memory.
*
*/
void set_headline(SimulationMemory *memory);

/**
* @brief Sets the day in the simulation memory.
*
* @param SimulationMemory pointer to the shared memory.
*
*/
void set_day(SimulationMemory *memory, int day);

/**
* @brief Store the pid of the epidemic sim in the simulation memory.
*
* @param memory Pointer to the shared memory.
* @param pid_epidemic_sim The PID to store.
*
*/
void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim);

/**
* @brief Set a building type at a given position in the grid.
*
* @param memory Pointer to the shared memory.
* @param row The row index of the building.
* @param col The column index of the building.
* @param building_type The type of the building to set.
*
*/
void set_building(SimulationMemory *memory, int row, int col, int building_type);

/**
* @brief Initializes the contamination level at the start in the city.
*
* @param memory pointer to the shared memory.
*
*/
void init_contamination_level(SimulationMemory *memory);

/**
* @brief Sets up the simulation memory with all the starting values of the simulation.
*
* @param memory Pointer to the shared memory.
*
*/
void initialize_memory(SimulationMemory *memory);

/**
* @brief Set a citizen at a given position.
*
* @param memory Pointer to the shared simulation memory.
* @param row The row index of the building.
* @param col The column index of the building.
* @param citizens_count The number of citizen on the given position before adding the new one.
* @param id The ID of the new citizen.
*
*/

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count, int id);


void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count, int id);

/**
 * @brief Add a doctors at a given position.
 * @param memory Pointer to the shared simulation memory.
 * @param row The row index of the doctors.
 * @param col The column index of the doctors.
 * @param doctors_count The number of doctors to add.
 * @param id The ID of the doctor to assign.
 */

/**
 * @brief Updates the movement, health, and actions of doctors according to the rules of the simulation.
 * @param memory Pointer to the shared simulation memory.
 */ 
void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count, int id);

/**
 * @brief Takes account the death of a citizen and updates the map simulaiton accordingly.
 * @param memory Pointer to the shared simulation memory.
 * @param row The row index for the dead citizen.
 * @param col The column index for the dead citizen.
 * @param dead_citizens_count The number of dead citizens to add.
 * @param id The ID of the dead citizen.
 */
void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count, int id);


void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count, int id);

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes);

/**
 * @brief Updates the state of buildings and characters and contamination levels in the simulation.
 * @param memory Pointer to the shared memory.
 */
void update_memory(SimulationMemory *memory);

void update_normal_citizen(SimulationMemory *memory);
void update_firefighter(SimulationMemory *memory);
void update_doctor(SimulationMemory* memory);


#endif
