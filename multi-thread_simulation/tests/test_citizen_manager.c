#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "citizen_manager.h"

// Prototypes des fonctions utilitaires pour les tests
void test_create_citizen();
void test_move_citizen();
void test_acquire_measuring_tool();
void test_refill_sprayer();
void test_can_enter_hospital();

int main() {
    printf("Démarrage des tests pour citizen_manager...\n\n");

    test_create_citizen();
    test_move_citizen();
    test_acquire_measuring_tool();
    test_refill_sprayer();
    test_can_enter_hospital();

    printf("\nTous les tests ont réussi !\n");
    return 0;
}

// Tests pour create_citizen
void test_create_citizen() {
    printf("Test de create_citizen...\n");
    
    status_p *citizen = create_citizen(CITIZEN, 2, 3, 0);

    assert(citizen->positionX == 2);
    assert(citizen->positionY == 3);
    assert(citizen->contamination == 0);
    assert(strcmp(citizen->name, "Taha") == 0);

    free(citizen);
    printf("OK\n");
}

// Tests pour move
void test_move_citizen() {
    printf("Test de move...\n");

    status_p *citizen = create_citizen(CITIZEN, 3, 3, 1);
    int originalX = citizen->positionX;
    int originalY = citizen->positionY;

    move(citizen);

    assert(citizen->positionX >= originalX - 1 && citizen->positionX <= originalX + 1);
    assert(citizen->positionY >= originalY - 1 && citizen->positionY <= originalY + 1);

    free(citizen);
    printf("OK\n");
}

// Tests pour acquire_measuring_tool
void test_acquire_measuring_tool() {
    printf("Test de acquire_measuring_tool...\n");

    status_p *citizen = create_citizen(FIREFIGHTER, 1, 1, 2);
    acquire_measuring_tool(citizen);

    assert(citizen->measuring_tool == 1);

    free(citizen);
    printf("OK\n");
}

// Tests pour refill_sprayer
void test_refill_sprayer() {
    printf("Test de refill_sprayer...\n");

    status_p *citizen = create_citizen(FIREFIGHTER, 1, 1, 3);
    refill_sprayer(citizen, 50);

    assert(citizen->sprayer == 50);

    free(citizen);
    printf("OK\n");
}

// Tests pour can_enter_the_hospital
void test_can_enter_hospital() {
    printf("Test de can_enter_the_hospital...\n");

    status_p *doctor = create_citizen(DOCTOR, 3, 3, 4);
    status_p *firefighter = create_citizen(FIREFIGHTER, 3, 3, 5);
    status_p *healthy_citizen = create_citizen(CITIZEN, 3, 3, 6);

    assert(can_enter_the_hospital(doctor) == 1);
    assert(can_enter_the_hospital(firefighter) == 1);
    assert(can_enter_the_hospital(healthy_citizen) == 0);

    healthy_citizen->is_sick = 1;
    assert(can_enter_the_hospital(healthy_citizen) == 1);

    free(doctor);
    free(firefighter);
    free(healthy_citizen);
    printf("OK\n");
}
