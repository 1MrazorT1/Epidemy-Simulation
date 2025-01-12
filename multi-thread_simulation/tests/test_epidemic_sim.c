#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include "epidemic_sim.h"
#include "simulation_memory.h"
#include "posix_semaphore.h"

// Prototypes des fonctions utilitaires pour les tests
void test_setup_shared_memory();
void test_manage_timer();
void test_end_simulation();

int main() {
    printf("Démarrage des tests pour epidemic_sim...\n\n");

    test_setup_shared_memory();
    test_manage_timer();
    test_end_simulation();

    printf("\nTous les tests ont réussi !\n");
    return 0;
}

void test_setup_shared_memory() {
    printf("Test de setup_shared_memory...\n");

    SimulationMemory* memory = setup_shared_memory();

    assert(memory != NULL);
    assert(memory->day == 0);
    assert(memory->has_simulation_ended == 0);

    // Nettoyage de la mémoire partagée
    if (munmap(memory, sizeof(SimulationMemory)) == -1) {
        perror("Error during munmap");
    }
    shm_unlink("/epidemic_memory");

    printf("OK\n");
}

void test_manage_timer() {
    printf("Test de manage_timer...\n");

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error: fork()");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Enfant : exécute le timer
        manage_timer();
        exit(0);
    } else {
        // Parent : attend que le processus enfant termine
        int status;
        waitpid(pid, &status, 0);

        assert(WIFEXITED(status));
        printf("OK\n");
    }
}

void test_end_simulation() {
    printf("Test de end_simulation...\n");

    // Initialisation de la mémoire partagée et des sémaphores
    SimulationMemory* memory = setup_shared_memory();
    semaphore_t* sem = open_semaphore("/epidemic_semaphore");
    P(sem);

    memory->pids[1] = fork(); // Simuler citizen_manager
    memory->pids[3] = fork(); // Simuler press_agency
    V(sem);

    // Simuler la fin de simulation
    end_simulation(SIGTERM);

    // Vérifications : les processus enfants doivent être terminés
    int status;
    waitpid(memory->pids[1], &status, 0);
    assert(WIFEXITED(status));

    waitpid(memory->pids[3], &status, 0);
    assert(WIFEXITED(status));

    printf("OK\n");
}
