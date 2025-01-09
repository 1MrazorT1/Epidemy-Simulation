#ifndef CITIZEN_MANAGER_H
#define CITIZEN_MANAGER_H

#define CITIZEN_MAX_NAME_LENGTH 32

typedef enum Person{
    CITIZEN,
    DOCTOR,
    FIREFIGHTER,
    JOURNALIST,
    REPORTER,
    DEAD,
    BURNED,
}Person;

typedef struct status {
    int id; /*from 0 to the maximum number of that person's type, is unique and it helps keeping the citizen count under the maximum number of that person's type.*/
    int positionX;
    int positionY;
    double contamination;
    double death_chance;
    int is_sick;
    char name[CITIZEN_MAX_NAME_LENGTH];
    unsigned int nbr_days_sickness;
    Person type;
    int  days_spent_in_hospital_asHealthy;
    int days_out_hospital;
    int care_pouch;   /* if doctor out of hopital=> 5 care pouch 
                        ..  ..     in  the   ..  => 10 care pouch  */
}status_p;

/**
 * Create and initiaze right values for type citizen
 * @return
 */

status_p* create_citizen(Person,unsigned in, unsigned int , int id_name);

/**
 * display status of citizen
 */

void display_citizen(status_p*);

int normal_citizen_moving(status_p* citizen, double local_contamination[7][7]);

int is_going_to_be_sick(status_p* citizen);

int is_going_to_die(status_p* citizen, status_p** medics);

#endif /* CITIZEN_MANAGER_H */
