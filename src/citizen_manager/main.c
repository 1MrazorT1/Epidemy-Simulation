#include <stdlib.h>

#include "citizen_manager.h"
#include "logger.h"

/*
 * Runs the Citizen Manager process.
 */
int main(int argc, const char *argv[]) {
    srand( time( NULL ) );
    status_p *citizen1 = create_citizen(CITIZEN, 2, 3, 0);
    status_p *doctor1 = create_citizen(DOCTOR, 15, 25, 1);
    status_p *firefighter1 = create_citizen(FIREFIGHTER, 5, 10, 2);

    printf("Displaying Citizen:\n");
    display_citizen(citizen1);

    //while(1){
    //    if(normal_citizen_moving(citizen1) == 1){
    //        printf("Moving Citizen:\n");
    //        display_citizen(citizen1);
    //    }
    //    
    //}
    

    printf("Displaying Doctor:\n");
    display_citizen(doctor1);

    printf("Displaying Firefighter:\n");
    display_citizen(firefighter1);

    return 0;
}
