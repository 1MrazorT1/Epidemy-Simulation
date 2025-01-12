/**
 * @file epidemic_sim.c
 * @brief Manage the epidemic simulation, create the shared memory, manage processus and semaphores
 * @details This file contains key functions to start, manage and end the simulation. 
 */


#include "epidemic_sim.h"
#include "logger.h"
#include "posix_semaphore.h"
#include "simulation_memory.h"


/* 
 * ----------------------------------------------------------------------------
 *                                  TO COMPLETE
 * ----------------------------------------------------------------------------
 */
// epidemic_sim.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define SHM_NAME "epidemic_shared_memory"
#define MAX_CITIZENS 100


/**
 * @brief Confiure and initialise the shared memory
 * @return A pointer to a SimulationMemory structure which represents the shared memory
 */
SimulationMemory* setup_shared_memory(){

    SimulationMemory* p;
    int shm_fd = shm_open("/epidemic_memory", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        handle_fatal_error("error : shm_open()");
    }

    if (ftruncate(shm_fd, sizeof(SimulationMemory)) == -1) {
        handle_fatal_error("error : ftruncate()");
    }

    p = mmap(0, sizeof(SimulationMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (p == MAP_FAILED) {
        handle_fatal_error("error : mmap()");
    }

    return p;

}

/**
 * @brief Update the simulation after a day passed
 * @details Update the map and characters accordind to the rules of the epidemic simulation
 */
void next_day(){
    SimulationMemory* memory;
    semaphore_t* sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    memory = get_data();
    memory->day++;
    update_wastelands(memory);
    update_normal_citizen(memory);
    update_doctor(memory);
    update_firefighter(memory);

    /*to complete*/
}   

/**
 * @brief Start the epidemic simulation
 * @details In the parent process, it runs the function which manages signal to coordinate all the sub programs. The child process runs all the sub programs. 
 */
void start_simulation(){
    pid_t pid = fork();
    if (pid == -1){
        handle_fatal_error("Error: fork()");
    }
    else if (pid == 0){
        /*to complete : run all the other programs*/
        manage_timer();
    }
    else{
        /*to complete : run epidemic sim as parent processus*/
    }
}


void epidemic_sim(){
    /*to complete : use next_day, ...*/

}

/**
 * @brief Manage the timer process in the epidemic simulation
 * @details 
 */
void manage_timer(){

    SimulationMemory * memory;
    semaphore_t *sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    memory = get_data();
    /* TIMER PID */
    memory->pids[2] = getpid(); 
    V(sem);

    if (munmap(memory, sizeof(memory)) == -1) {
        perror("munmap");
    }

    /* CALLS MANAGE_CITIZEN_MANAGER*/
    pid_t pid = fork();
    if (pid == -1) {
        handle_fatal_error("Error fork() in manage_timer() ");
    } 
    else if (pid == 0) {
        manage_citizen_manager();
    } 
    else {
        /* EXEC TIMER */
        wait(NULL);
        }
}

/**
 * @brief Manage the citizen manager process in the epidemic simulation.
 * @details 
 * Acceses and update the shared memory to store citizen_manager's PID. Runs citizen_manger in a child process.
 */
void manage_citizen_manager(){
    printf("citizen_manager process : %d\n", getpid());

    SimulationMemory * memory;
    semaphore_t *sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    
    memory = get_data();
    
    /* CITIZEN_MANAGER PID */
    memory->pids[1] = getpid(); 
    V(sem);

    if (munmap(memory, sizeof(memory)) == -1) {
        perror("munmap");
    }

    pid_t pid = fork();
    if (pid == -1) {
        handle_fatal_error("Error: first fork() in citizen_manager");
    } 
    else if (pid == 0) {
        manage_press_agency();
    }
    else {
        /* EXEC CITIZEN_MANAGER */ 
        pid = fork();
        if (pid == -1){
            handle_fatal_error("Error: second fork() in manage_citizen_manger");
        }
        else if (pid == 0){
            if (execl("./bin/citizen_manager", NULL) == -1) {
                handle_fatal_error("Error: execl citizen_manager");
            }
        }
        wait(NULL);
        wait(NULL);
    
    }
}

/**
 * @brief Manage the press_agency process in the epidemic simulation.
 * @details 
 */
void manage_press_agency(){
    printf("press_agency process : %d\n", getpid());

    SimulationMemory * memory;
    semaphore_t *sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    
    memory = get_data();
    
    /* PRESS_AGENCY PID */
    memory->pids[4] = getpid(); 
    V(sem);

    if (munmap(memory, sizeof(memory)) == -1) {
        perror("munmap");
    }

    pid_t pid = fork();
    if (pid == -1) {
        handle_fatal_error("Error: first fork() in managa_press_agency");
    } 
    else if (pid == 0) {
        manage_viewer();
    }
    else {
        pid = fork();
        if (pid == -1){
            handle_fatal_error("Error; second fork() in manage_press_agency");
        }
        else if (pid == 0){
            if (execl("./bin/press_agency", NULL) == -1) {
                handle_fatal_error("Error: execl press_agency");
            }
        }
        wait(NULL);
        wait(NULL);
    }
}

/**
 * @brief Manage the timer process in the epidemic simulation
 * @details 
 */
void manage_viewer(){
    printf("viewer process: %d\n", getpid());
    SimulationMemory * memory;
    semaphore_t *sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    memory = get_data();

    /* VIEWER PID */
    memory->pids[4] = getpid(); 
    V(sem);

    if (munmap(memory, sizeof(memory)) == -1) {
        perror("munmap");
    }

    /* RUNNING VIEWER */
    if (execl("./bin/viewer", NULL) == -1) {
        handle_fatal_error("Error: execl viewer");
    }
    
}

/**
 * @brief Manage the timer process in the epidemic simulation
 * @details 
 */
void end_simulation(int signal){
    SimulationMemory * memory;
    semaphore_t* sem;
    sem = open_semaphore("/epidemic_semaphore");
    P(sem);
    memory = get_data();
    memory->has_simulation_ended = 1;

    if (kill(memory->pids[1], SIGTERM) == -1) { /*citizen manager*/
        perror("kill()");
        exit(EXIT_FAILURE);
    }
 /*press agency*/
    if (kill(memory->pids[3], SIGTERM) == -1) {
        perror("kill()");
        exit(EXIT_FAILURE);
    }
    V(sem);
 
    if (munmap(memory, sizeof(SimulationMemory)) == -1) {
        perror("Error unmapping shared memory");
    }
    /*erase from shared memory*/
    shm_unlink("/epidemic_memory");
    exit(EXIT_SUCCESS);

}

