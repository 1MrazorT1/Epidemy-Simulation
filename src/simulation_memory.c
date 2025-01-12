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



int is_valid_location(int row, int col){
    return ((row >=0) && (row <=6) && (col >=0) && (col <=6));
}

void update_wastelands(SimulationMemory *memory){
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            if(memory->buildings[row][col] == 3){
                /*NORTH WEST*/
                if(is_valid_location(row - 1, col - 1)){
                    if((memory->buildings[row - 1][col - 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row - 1][col - 1]) && (rand() % 100 <= 3)){
                        memory->contamination_level[row - 1][col - 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }

                /*WEST*/
                if(is_valid_location(row - 1, col)){
                    if((memory->buildings[row - 1][col] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row - 1][col]) && (rand() % 100 <= 3)){
                        memory->contamination_level[row - 1][col] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*SOUTH WEST*/
                if(is_valid_location(row - 1, col + 1)){
                    if((memory->buildings[row - 1][col + 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row - 1][col + 1]) && (rand() % 100 <= 3)){
                        memory->contamination_level[row - 1][col + 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*NORTH*/
                if(is_valid_location(row, col - 1)){
                    if((memory->buildings[row][col - 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row][col - 1]) && (rand() % 100 <= 15)){
                        memory->contamination_level[row][col - 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*SOUTH*/
                if(is_valid_location(row, col + 1)){
                    if((memory->buildings[row][col + 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row][col + 1]) && (rand() % 100 <= 15)){
                        memory->contamination_level[row][col + 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*NORTH EAST*/
                if(is_valid_location(row + 1, col - 1)){
                    if((memory->buildings[row + 1][col - 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row + 1][col - 1]) && (rand() % 100 <= 20)){
                        memory->contamination_level[row + 1][col - 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*EAST*/
                if(is_valid_location(row + 1, col)){
                    if((memory->buildings[row + 1][col] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row + 1][col]) && (rand() % 100 <= 25)){
                        memory->contamination_level[row + 1][col] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
                
                /*SOUTH EAST*/
                if(is_valid_location(row + 1, col + 1)){
                    if((memory->buildings[row + 1][col + 1] == 3) && (memory->contamination_level[row][col] > memory->contamination_level[row + 1][col + 1]) && (rand() % 100 <= 20)){
                        memory->contamination_level[row + 1][col + 1] += fabs((memory->contamination_level[row][col] - memory->contamination_level[row - 1][col - 1])) * ((1 + rand() % 20) * 0.01);
                    }
                }
            }
        }
    }
}

int is_in_hospital(status_p* character){
    return((character != NULL) && (character->positionX == HOSPITAL_ROWS) && (character->positionY == HOSPITAL_COLUMNS));
}

int is_in_firestation(status_p* character){
    return(is_in_top_firestation(character) || is_in_buttom_firestation(character));
}

int is_in_top_firestation(status_p* character){
    return((character != NULL) && (character->positionX == FIRESTATION_TOP_X) && (character->positionY == FIRESTATION_TOP_X));
}

int is_in_buttom_firestation(status_p* character){
    return((character != NULL) && (character->positionX == FIRESTATION_BUTTOM_X) && (character->positionY == FIRESTATION_BUTTOM_X));
}

int is_allowed_in_the_firestation(SimulationMemory *memory, status_p* character){
    if(character->type == FIREFIGHTER){
        return 1;
    }else if(memory->buildings[character->positionX][character->positionY] == 0){
        for(int i = 0; i < MAX_FIREFIGHTER; i++){
            if((character->positionX == memory->firefighters[i]->positionX) && (character->positionY == memory->firefighters[i]->positionY)){
                return 1;
            }
        }
    }else{
        return 0;
    }
}

void be_treated_in_hospital(status_p* character, double hospital_contamination_level){
    character->death_chance /= 4;
    if(character->contamination > hospital_contamination_level){
        character->contamination *= 0.9;
        if(character->contamination < hospital_contamination_level){
            character->contamination = hospital_contamination_level;
        }
    }
}

void be_healed_in_hospital(status_p* character){
    character->is_sick = 0;
}

int count_medics_in_hospital(SimulationMemory *memory, int ensure_not_sick){
    int count = 0;
    for(int i = 0; i < MAX_DOCTORS; i++){
        if(is_in_hospital(memory->doctors[i])){
            if(ensure_not_sick){
                if(memory->doctors[i]->is_sick == 0){
                    count++;
                }
            }else{
                count++;
            }
        }
    }
    return count;
}

void heal_in_hospital(SimulationMemory *memory, int number_of_medics){
    int* IDs = NULL;
    int n = get_IDs(HOSPITAL_ROWS, HOSPITAL_COLUMNS, memory->citizens, IDs);
    if(IDs != NULL){
        while(number_of_medics){

            /*figure out the sickest among the ones in the hospital*/
            int sickest_citizen = -1;
            int sickness = -1;
    
            for(int i = 0; i < n; i++){
                if((memory->citizens[IDs[i]]->is_sick > 0) && (memory->citizens[IDs[i]]->is_sick > sickness)){
                    sickness = memory->citizens[IDs[i]]->is_sick;
                    sickest_citizen = i;
                }
            }

            /*healing by order of sickness*/
            if(sickest_citizen != -1){
                be_healed_in_hospital(memory->citizens[IDs[sickest_citizen]]);
            }

            number_of_medics--;
        }
    }
}

void update_hospital(SimulationMemory *memory){
    for(int i = 0; i < MAX_NORMAL_CITIZEN; i++){
        if(is_in_hospital(memory->citizens[i])){
            be_treated_in_hospital(memory->citizens[i], memory->contamination_level[HOSPITAL_ROWS][HOSPITAL_COLUMNS]);
        }
    }

    for(int i = 0; i < MAX_FIREFIGHTER; i++){
        if(is_in_hospital(memory->firefighters[i])){
            be_treated_in_hospital(memory->firefighters[i], memory->contamination_level[HOSPITAL_ROWS][HOSPITAL_COLUMNS]);
        }
    }

    for(int i = 0; i < MAX_DOCTORS; i++){
        if(is_in_hospital(memory->doctors[i])){
            be_treated_in_hospital(memory->doctors[i], memory->contamination_level[HOSPITAL_ROWS][HOSPITAL_COLUMNS]);
        }
    }

    heal_in_hospital(memory, count_medics_in_hospital(memory, 1));
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

void init_news(NewsMemory *news){

    for(int day = 0; day < SIMULATION_DURATION; day++){
        news->n_of_well_citizens[day] = 0;
        news->n_of_ill_citizens[day] = 0;
        news->n_of_corpses[day] = 0;
        news->n_of_ashes[day] = 0;
        news->average_contamination_level[day] = 0;
    }

    FILE *fq;
    fq = fopen("resources/evolution.txt", "w");
    fprintf(fq, "%d %d %d %d %d %f\n", 0, news->n_of_well_citizens[0], news->n_of_ill_citizens[0], news->n_of_corpses[0], news->n_of_ashes[0], news->average_contamination_level[0]);
    fclose(fq);
}

void update_news(SimulationMemory *memory, NewsMemory *news, int day){
    for(int i = 0; i < MAX_NORMAL_CITIZEN; i++){
        if(memory->citizens[i] != NULL){
            if(memory->citizens[i]->is_sick == 0){
            news->n_of_well_citizens[day]++;
            }else if(memory->citizens[i]->is_sick != 0){
                news->n_of_ill_citizens[day]++;
            }

            if(memory->citizens[i]->type == 5){
                news->n_of_corpses[day]++;
            }else if(memory->citizens[i]->type == 6){
                news->n_of_ashes[day]++;
            }
        }
        
    }

    double average = 0;
    double somme = 0;
    for(int row = 0; row < CITY_ROWS; row++){
        for(int col = 0; col < CITY_COLUMNS; col++){
            somme += memory->contamination_level[row][col];
        }
    }

    news->average_contamination_level[day] = somme / (CITY_ROWS * CITY_COLUMNS);
}

void transmit_news(NewsMemory *news, int day){
    FILE *fq;
    fq = fopen("resources/evolution.txt", "a");
    fprintf(fq, "%d %d %d %d %d %f\n", day, news->n_of_well_citizens[day], news->n_of_ill_citizens[day], news->n_of_corpses[day], news->n_of_ashes[day], news->average_contamination_level[day] * 100);
    fclose(fq);
}

void update_normal_citizen(SimulationMemory *memory){
    for(int i = 1; i < MAX_NORMAL_CITIZEN; i++){
        int old_row = memory->citizens[i]->positionX;
        int old_col = memory->citizens[i]->positionY;
        if (normal_citizen_moving(memory->citizens[i], memory->contamination_level) == 1){
            if(is_in_firestation(memory->citizens[i])){
                if(!is_allowed_in_the_firestation(memory, memory->citizens[i])){
                    move(memory->citizens[i]);
                }else{
                    memory->citizens[i]->contamination *= 0.8;
                    acquire_measuring_tool(memory->citizens[i]);
                }
            }


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
    acquire_measuring_tool(memory->firefighters[id]);
    if(is_in_firestation(memory->firefighters[id])){
        refill_sprayer(memory->firefighters[id], 100);
    }else{
        refill_sprayer(memory->firefighters[id], 50);
    }
    memory->n_of_firefighters[row][col] = memory->n_of_firefighters[row][col] + firefighters_count;
}

int get_IDs(int row, int col, status_p* *character, int* IDs){
    int n = 0;
    for(int i = 0; i < 25; i++){
        if((character[i] != NULL) && (character[i]->positionX == row) && (character[i]->positionY == col)){
            n++;
            IDs = malloc(n * sizeof(int));
            IDs[n-1] = i;
        }
    }
    return n;
}

void update_firefighter(SimulationMemory *memory){
    for(int i = 1; i < MAX_FIREFIGHTER; i++){
        int old_row = memory->firefighters[i]->positionX;
        int old_col = memory->firefighters[i]->positionY;
        if (firefighter_moving(memory->firefighters[i], memory->contamination_level) == 1){
            if(is_in_firestation(memory->firefighters[i])){
                if(!is_allowed_in_the_firestation(memory, memory->firefighters[i])){
                    move(memory->firefighters[i]);
                }else{
                    memory->firefighters[i]->contamination *= 0.8;
                    acquire_measuring_tool(memory->firefighters[i]);
                    refill_sprayer(memory->firefighters[i], 100 - memory->firefighters[i]->sprayer);
                }
            }



            int new_row = memory->firefighters[i]->positionX;
            int new_col = memory->firefighters[i]->positionY;
            memory->n_of_firefighters[old_row][old_col] = memory->n_of_firefighters[old_row][old_col] - 1;
            memory->n_of_firefighters[new_row][new_col] = memory->n_of_firefighters[new_row][new_col] + 1;
            int* IDs = NULL;
            int n = get_IDs(new_row, new_col, memory->citizens, IDs);
            if(IDs != NULL){
                for(int j = 0; j < n; j++){
                    if(memory->citizens[IDs[j]]->contamination > 0){
                        memory->citizens[IDs[j]]->contamination = memory->citizens[IDs[j]]->contamination - 0.2 * memory->citizens[IDs[j]]->contamination;
                    }
                }
            }else{
                if(memory->contamination_level[new_row][new_col] > 0){
                    memory->contamination_level[new_row][new_col] = memory->contamination_level[new_row][new_col] - 0.2 * memory->contamination_level[new_row][new_col];
                }
            }
        }
    }
}

void add_doctors(SimulationMemory *memory, int row, int col, int doctors_count, int id){
    memory->doctors[id] = create_citizen(DOCTOR, row, col, rand() % 32);
    if(is_in_hospital(memory->doctors[id])){
        memory->doctors[id]->care_pouch = 10;
    }else{
        memory->doctors[id]->care_pouch = 5;
    }
    memory->n_of_doctors[row][col] = memory->n_of_doctors[row][col] + doctors_count;
}

void update_doctor(SimulationMemory *memory){
    for(int i = 1; i < MAX_DOCTORS; i++){
        int old_row = memory->doctors[i]->positionX;
        int old_col = memory->doctors[i]->positionY;
        if (doctor_moving(memory->doctors[i], memory->contamination_level) == 1){
            if(is_in_firestation(memory->doctors[i])){
                if(!is_allowed_in_the_firestation(memory, memory->doctors[i])){
                    move(memory->doctors[i]);
                }else{
                    memory->doctors[i]->contamination *= 0.8;
                    acquire_measuring_tool(memory->doctors[i]);
                }
            }




            int new_row = memory->doctors[i]->positionX;
            int new_col = memory->doctors[i]->positionY;
            memory->n_of_doctors[old_row][old_col] = memory->n_of_doctors[old_row][old_col] - 1;
            memory->n_of_doctors[new_row][new_col] = memory->n_of_doctors[new_row][new_col] + 1;
            if(is_in_hospital(memory->doctors[i])){
                memory->doctors[i]->care_pouch = memory->doctors[i]->care_pouch + 10;
            }
            if(memory->doctors[i]->is_sick == 0){
                int* IDs = NULL;
                int n = get_IDs(new_row, new_col, memory->citizens, IDs);
                if(IDs != NULL){
                    /*Searching for the highest contaminated, then healing them*/
                    double max = 0;
                    int k = -1;
                    for(int j = 0; j < n; j++){
                        if((memory->citizens[IDs[j]]->is_sick > 0) && (!is_in_hospital(memory->citizens[IDs[j]]))){
                            if(memory->citizens[IDs[j]]->contamination > max){
                                max = memory->citizens[IDs[j]]->contamination;
                                k = j;
                            }
                        }
                    }
                    heal(memory->doctors[i], memory->citizens[IDs[k]], is_in_hospital(memory->citizens[IDs[k]]));
                }
            }else if(memory->doctors[i]->is_sick < 10){
                heal(memory->doctors[i], memory->doctors[i], is_in_hospital(memory->doctors[i]));
            }
        }
    }
}

void add_dead_citizens(SimulationMemory *memory, int row, int col, int dead_citizens_count, int id){
    memory->dead_citizens[id] = create_citizen(DEAD, row, col, rand() % 32);
    memory->citizens[id] = NULL;
    //memory->n_of_citizens[row][col] = memory->n_of_citizens[row][col] - 1;
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
        if(citizens <= 2){
            memory->citizens[citizens]->type = JOURNALIST;
        }
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
    set_day(memory, 1);
    set_buildings(memory);
    init_contamination_level(memory);
    init_people(memory, 25, 6, 4, 0, 0);
    memory->news = malloc(sizeof(NewsMemory));
    init_news(memory->news);
}

void update_memory(SimulationMemory *memory){
    memory->day++;
    update_normal_citizen(memory);
    update_firefighter(memory);
    update_doctor(memory);
    update_wastelands(memory);
    update_hospital(memory);
    if(memory->day <= 100){
        update_news(memory, memory->news, memory->day - 1);
        transmit_news(memory->news, memory->day - 1);
    }
}