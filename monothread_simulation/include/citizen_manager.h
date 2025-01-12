#ifndef CITIZEN_MANAGER_H
#define CITIZEN_MANAGER_H

/**
* @file citizen_manager.h
*
* @brief This file contains structures and prototypes of functions to manage the citizen behaviors.
*
*
*/


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
    int care_pouch;
    int measuring_tool;
    int sprayer;
}status_p;

/**
 * Create and initiaze right values for type citizen
 * @return status_p struct which represents the citizen.
 */

status_p* create_citizen(Person,unsigned in, unsigned int , int id_name);

/**
 * display status of citizen
 */

void display_citizen(status_p*);

/**
 * @brief Updates the movement and contamination level of a normal citizen.
 * 
 * @param citizen Pointer to the citizen whose state is being updated.
 * @param local_contamination A 2D array representing contamination levels in the city grid.
 * @return 1 if the citizen moved, 0 otherwise.
 */
int normal_citizen_moving(status_p* citizen, double local_contamination[7][7]);

/**
 * @brief Updates the movement and contamination level of a firefighter.
 * 
 * @param firefighter Pointer to the firefighter whose state is being updated.
 * @param local_contamination A 2D array representing contamination levels in the city grid.
 * @return 1 if the firefighter moved, 0 otherwise.
 */
int firefighter_moving(status_p* firefighter, double local_contamination[7][7]);

/**
 * @brief Tells if a citizen is going to be sick.
 * 
 * @param citizen Pointer to the citizen to evaluate if he is going to be sick.
 * @return 1 if the citizen is becoming sick, 0 otherwise.
 */
int is_going_to_be_sick(status_p* citizen);


/**
 * @brief Tells if a citizen is going to die based on the state of his sickness and the available doctors.
 * 
 * @param citizen Pointer to the citizen to evaluate if he is going to die.
 * @param medics Array of pointers to medics available in the simulation.
 * @return 1 if the citizen is going to die, 0 otherwise.
 */
int is_going_to_die(status_p* citizen, status_p** medics);

#endif /* CITIZEN_MANAGER_H */
