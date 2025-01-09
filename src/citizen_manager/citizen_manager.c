#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "citizen_manager.h"
#include "logger.h"

/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */
status_p *create_citizen(Person e,unsigned int x, unsigned int y,int id_name){
    const char *const names[] = {"Taha", "Mohamed", "Johann", "Brida", "Foulen", "Falten", "Foulena", "Bouhal",
                             "Saad", "Omar", "Hamza", "Ahmed", "Kamel", "Aymen", "Ramy", "Ayoub",
                             "Iyadh", "Abdlaaziz", "Souhem", "Abdelwehed", "Rachid", "Zekri", "Haythem", "Ben Lbokht", "Yassine", "Tareq",
                             "Eezedine", "Oussema", "Fawzi", "Achref", "Hatem", "Hazem", "Jamel", "Anas", "Ilyess",
                             "Zitoun", "Yazid", "Zied", "Ismail"};

      
    status_p *citi = (status_p *)malloc(sizeof(status_p));
   

    
    citi->positionX = x;
    citi->positionY = y;
    citi->contamination = 0;
    citi->is_sick = 0;
    citi->death_chance = 0;
    citi->days_spent_in_hospital_asHealthy = 0;
    citi->type = e;
    strcpy(citi->name, names[id_name]);

    if (e == DOCTOR){
        /* to complete after */
    }
    return citi;
    
}

void move(status_p* character){
    int rand_dx = rand() % 3;
    int rand_dy = rand() % 3;
    if(rand_dx == 0){
        if((character->positionX >= 1)){
            rand_dx = -1;
        }else{
            rand_dx = 0;
        }
    }else if(rand_dx == 1){
        rand_dx = 0;
    }else if(rand_dx == 2){
        if((character->positionX <= 5)){
            rand_dx = 1;
        }else{
            rand_dx = 0;
        }
    }

    if(rand_dy == 0){
        if((character->positionY >= 1)){
            rand_dy = -1;
        }else{
            rand_dy = 0;
        }
    }else if(rand_dy == 1){
        rand_dy = 0;
    }else if(rand_dy == 2){
        if((character->positionY <= 5)){
            rand_dy = 1;
        }else{
            rand_dy = 0;
        }
    }
    character->positionX = character->positionX + rand_dx;
    character->positionY = character->positionY + rand_dy;
}

int normal_citizen_moving(status_p* citizen, double local_contamination[7][7]){
    int isMoving = rand() % 100;
    if (isMoving <= 40){
        move(citizen);
        citizen->contamination = citizen->contamination + 0.02 * local_contamination[citizen->positionX][citizen->positionY];
        return 1;
    }else{
        citizen->contamination = citizen->contamination + 0.05 * local_contamination[citizen->positionX][citizen->positionY];
        return 0;
    }
}

int firefighter_moving(status_p* firefighter, double local_contamination[7][7]){
    int isMoving = rand() % 100;
    if (isMoving <= 40){
        move(firefighter);
        firefighter->contamination = firefighter->contamination + 0.02 * local_contamination[firefighter->positionX][firefighter->positionY];
        return 1;
    }else{
        firefighter->contamination = firefighter->contamination + 0.05 * local_contamination[firefighter->positionX][firefighter->positionY];
        return 0;
    }
}

int doctor_moving(status_p* doctor, double local_contamination[7][7]){
    int isMoving = rand() % 100;
    if (isMoving <= 40){
        move(doctor);
        doctor->contamination = doctor->contamination + 0.02 * local_contamination[doctor->positionX][doctor->positionY];
        return 1;
    }else{
        doctor->contamination = doctor->contamination + 0.05 * local_contamination[doctor->positionX][doctor->positionY];
        return 0;
    }
}

void heal(status_p* doctor, status_p* character, int in_hospital){
    if(doctor->care_pouch > 0){
        character->is_sick = 0;
        if(in_hospital){
            doctor->care_pouch--;
        }
    }
}

int is_going_to_be_sick(status_p* citizen){
    if((citizen->is_sick == 0) && (citizen->contamination > ((rand() % 100) / 100))){
        citizen->is_sick = 1;
        return 1;
    }else{
        return 0;
    }
}

int is_going_to_die(status_p* citizen, status_p** medics){
    if(citizen->type == 5){
        return 0;
    }
    
    if((citizen->is_sick >= 1) && (citizen->is_sick < 5)){
        
        citizen->is_sick = citizen->is_sick + 1;
    }else if(citizen->is_sick >= 5){
        citizen->death_chance = citizen->death_chance + 0.05;
        for(int i = 0; i < 4; i++){
            if ((medics[i]->positionX == citizen->positionX) && (medics[i]->positionY == citizen->positionY)){
                citizen->death_chance = citizen->death_chance / 2;
                return 0;
            }
        }
        if(citizen->death_chance > ((rand() % 100) / 100)){
            citizen->death_chance = 1;
            citizen->type = 5;
            return 1;
        }
    }
    return 0;
}

void decontaminate(int row, int col, double *contamination){
    
}


void display_citizen( status_p *citi) {
    printf("Name: %s\n", citi->name);
    printf("Type: %d\n", citi->type);
    printf("Position: (%d, %d)\n", citi->positionX, citi->positionY);
    printf("Contamination Level: %.2f\n", citi->contamination);
    printf("Is Sick: %s\n", citi->is_sick ? "Yes" : "No");
    if (citi->type==DOCTOR ) {
        printf("Medical Pouches: %d\n", citi->care_pouch);
    } 
    printf("\n");
}
