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

void start_simulation(){
    pid_t pid = fork();
    if (pid == -1){
        handle_fatal_error("Error: fork()");
    }
    else if (pid == 0){
        /*to complete : run all the other programs*/
    }
    else{
        /*to complete : run epidemic sim as parent processus*/
    }
}

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
    shm_unlink("/epidemic_memory");
    exit(EXIT_SUCCESS);

}