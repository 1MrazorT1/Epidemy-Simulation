#ifndef SIMULATION_MEMORY_H
#define SIMULATION_MEMORY_H

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
};


void set_headline(SimulationMemory *memory);
void set_day(SimulationMemory *memory, int day);
void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim);
void set_building(SimulationMemory *memory, int row, int col, int building_type);
void init_contamination_level(SimulationMemory *memory);
void initialize_memory(SimulationMemory *memory);

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count, int id);
void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count, int id);
void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count, int id);
void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count, int id);
void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count, int id);

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes);

void update_memory(SimulationMemory *memory);
void update_normal_citizen(SimulationMemory *memory);
void update_firefighter(SimulationMemory *memory);


#endif
