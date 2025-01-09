#include <stdio.h>
#include <stdlib.h>


#include "simulation_memory.h"
#include "logger.h"
#include "citizen_manager/citizen_manager.c"

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */

void set_headline(SimulationMemory *memory){
    strcpy(memory->headline_of_the_day, "Good morning");
}

void set_day(SimulationMemory *memory, int day){
    memory->day = day;
}

void set_pid_epidemic_sim(SimulationMemory *memory, pid_t pid_epidemic_sim){
    memory->pid_epidemic_sim = pid_epidemic_sim;
}

void set_building(SimulationMemory *memory, int row, int col, int building_type){
    memory->buildings[row][col] = building_type;
}

void set_hospital(SimulationMemory *memory){
    set_building(memory, CITY_ROWS / 2, CITY_COLUMNS / 2, 1);
}

void set_fire_stations(SimulationMemory *memory){
    set_building(memory, 0, CITY_COLUMNS - 1, 0);
    set_building(memory, CITY_ROWS - 1, 0, 0);
}

void set_houses(SimulationMemory *memory){
    int i = 0;
    while (i < 12){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        if (memory->buildings[rand_row][rand_col] == 4){
            set_building(memory, rand_row, rand_col, 2);
            i++;
        }
    }
}

void set_buildings(SimulationMemory *memory){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
                set_building(memory, row, col, 4);
        }
    }

    set_hospital(memory);
    set_fire_stations(memory);
    set_houses(memory);

    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            if (memory->buildings[row][col] == 4){
                set_building(memory, row, col, 3);
            }
        }
    } 
}

void add_citizens(SimulationMemory *memory, int row, int col, int citizens_count, int id){
    memory->citizens[id] = create_citizen(CITIZEN, row, col, rand() % 32);
    memory->n_of_citizens[row][col] = memory->n_of_citizens[row][col] + citizens_count;
}

void update_normal_citizen(SimulationMemory *memory){
    for(int i = 1; i < MAX_NORMAL_CITIZEN; i++){
        int old_row = memory->citizens[i]->positionX;
        int old_col = memory->citizens[i]->positionY;
        if (normal_citizen_moving(memory->citizens[i], memory->contamination_level) == 1){
            int new_row = memory->citizens[i]->positionX;
            int new_col = memory->citizens[i]->positionY;
            memory->n_of_citizens[old_row][old_col] = memory->n_of_citizens[old_row][old_col] - 1;
            memory->n_of_citizens[new_row][new_col] = memory->n_of_citizens[new_row][new_col] + 1;
            if(memory->buildings[new_row][new_col] == 1){
                memory->contamination_level[new_row][new_col] = memory->contamination_level[new_row][new_col] + 0.01 * memory->citizens[i]->contamination * 0.25;
            }else if (memory->buildings[new_row][new_col] != 0){
                memory->contamination_level[new_row][new_col] = memory->contamination_level[new_row][new_col] + 0.01 * memory->citizens[i]->contamination;
            }
        }

        is_going_to_be_sick(memory->citizens[i]) == 1;

        if(is_going_to_die(memory->citizens[i], memory->doctors) == 1){
            add_dead_citizens(memory, memory->citizens[i]->positionX, memory->citizens[i]->positionY, 1, memory->citizens[i]->id);
        }
        
    }
}

void add_firefighters(SimulationMemory *memory, int row, int col, int firefighters_count, int id){
    memory->firefighters[id] = create_citizen(FIREFIGHTER, row, col, rand() % 32);
    memory->n_of_firefighters[row][col] = memory->n_of_firefighters[row][col] + firefighters_count;
}

void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count, int id){
    memory->doctors[id] = create_citizen(DOCTOR, row, col, rand() % 32);
    memory->n_of_doctors[row][col] = memory->n_of_doctors[row][col] + doctors_count;
}

void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count, int id){
    memory->dead_citizens[id] = create_citizen(DEAD, row, col, rand() % 32);
    memory->citizens[id] = NULL;
    memory->n_of_citizens[row][col] = memory->n_of_citizens[row][col] - 1;
    memory->n_of_dead_citizens[row][col] = memory->n_of_dead_citizens[row][col] + dead_citizens_count;
}

void add_ashes(SimulationMemory *memory, int row, int col, int ashes_count, int id){
    memory->ashes[id] = create_citizen(BURNED, row, col, rand() % 32);
    memory->n_of_ashes[row][col] = memory->n_of_ashes[row][col] + ashes_count;
}

void init_people(SimulationMemory *memory, int number_of_citizens, int number_of_firefighters, int number_of_doctors, int number_of_dead_citizens, int number_of_ashes){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            memory->n_of_citizens[row][col] = 0;
            memory->n_of_firefighters[row][col] = 0;
            memory->n_of_doctors[row][col] = 0;
            memory->n_of_dead_citizens[row][col] = 0;
            memory->n_of_ashes[row][col] = 0;
        }
    }

    for(int i = 0; i < 25; i++){
        memory->citizens[i] = (status_p *)malloc(sizeof(status_p));
        memory->dead_citizens[i] = (status_p *)malloc(sizeof(status_p));
        memory->ashes[i] = (status_p *)malloc(sizeof(status_p));
    }

    for(int i = 0; i < 6; i++){
        memory->firefighters[i] = (status_p *)malloc(sizeof(status_p));
    }

    for(int i = 0; i < 4; i++){
        memory->doctors[i] = (status_p *)malloc(sizeof(status_p));
    }



    add_doctors(memory, CITY_ROWS / 2, CITY_COLUMNS / 2, 1, number_of_doctors);
    add_firefighters(memory, 0, CITY_COLUMNS - 1, 1, number_of_firefighters);
    add_firefighters(memory, CITY_ROWS - 1, 0, 1, number_of_firefighters);

    int medic = number_of_doctors - 1;
    while (medic > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_doctors(memory, rand_row, rand_col, 1, medic);
        medic--;
    }

    int firefighters = number_of_firefighters - 2;
    while (firefighters > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_firefighters(memory, rand_row, rand_col, 1, firefighters);
        firefighters--;
    }

    int citizens = number_of_citizens - 1;
    while (citizens > 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        add_citizens(memory, rand_row, rand_col, 1, citizens);
        citizens--;
    }
}

void init_contamination_level(SimulationMemory *memory){
    double wastelands_counter = 0;
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            memory->contamination_level[row][col] = 0;
            if(memory->buildings[row][col] == 3){
                wastelands_counter++;
            }
        }
    }

    int infected_wastelands = (int)(wastelands_counter * 0.1);

    while(infected_wastelands != 0){
        int rand_row = rand() % 7;
        int rand_col = rand() % 7;
        if(memory->buildings[rand_row][rand_col] == 3){
            memory->contamination_level[rand_row][rand_col] = (rand() % 20 + 20) * 0.01;
            infected_wastelands--;
        }
    }
    
}


void initialize_memory(SimulationMemory *memory){
    //set_headline(memory);
    //set_day(memory, 1);
    set_buildings(memory);
    init_contamination_level(memory);
    init_people(memory, 25, 6, 4, 0, 0);
}

void update_memory(SimulationMemory *memory){
    update_normal_citizen(memory);
}