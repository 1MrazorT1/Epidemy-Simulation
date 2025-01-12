#ifndef CITY_MANAGER_H
#define CITY_MANAGER_H

#define CITY_WIDTH 7
#define CITY_HEIGHT 7
#define NBR_TOTAL 37
#include "citizen_manager.h"
#include "stdlib.h"




typedef enum building_type {
    WASTELAND, HOUSE, HOSPITAL, FIRESTATION
} building_type;


/**
 * Représente une case de la grille :
 * - locationType : type de lieu (hôpital, caserne, etc.)
 * - contaminationLevel : niveau de contamination [0.0 .. 1.0]
 * - capacity : capacité maximale de la case
 * - currentOccupancy : nombre actuel de citoyens
 */
typedef struct {
    building_type _locationType;
    double _contaminationLevel;
    int _capacity;
    int _currentOccupancy;
} city_tile_t;

/**
 * Représente la ville sous forme d'une grille 7x7
 */
typedef struct {
    city_tile_t _grid[CITY_HEIGHT][CITY_WIDTH];
    status_p _citizens[NBR_TOTAL];
} city_t;

/**
 * @brief Crée une case de la grille avec les paramètres spécifiés.
 * @param type Le type de bâtiment (WASTELAND, HOUSE, HOSPITAL, FIRESTATION).
 * @return Une structure city_tile_t initialisée.
 */
city_tile_t create_tile(building_type type);

/**
 * @brief Initialise la ville avec une grille vide et des citoyens non définis.
 * @param city Pointeur vers la structure de la ville à initialiser.
 */
void init_city(city_t *city);

/**
 * @brief Ajoute un citoyen à la ville en le plaçant dans une case spécifique.
 * @param city Pointeur vers la structure de la ville.
 * @param num_c Numéro d'identification du citoyen.
 * @param type Le type de citoyen (défini dans Person).
 */
void add_citizen(city_t *city, int num_c, Person type);

/**
 * @brief Crée la population initiale de citoyens pour la ville.
 * @param city Pointeur vers la structure de la ville.
 */
void create_population(city_t *city);

/**
 * @brief Ajoute un niveau de contamination à une case spécifique.
 * @param tile Pointeur vers la case à contaminer.
 * @param cont Le niveau de contamination à ajouter (0.0 à 1.0).
 */
void add_tile_contamination(city_tile_t *tile, double cont);

/**
 * @brief Trouve le citoyen le plus malade sur une case donnée.
 * @param city Pointeur vers la structure de la ville.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 * @return L'identifiant du citoyen le plus malade.
 */
int sickest_of_title(city_t *city, unsigned int x, unsigned int y);

/**
 * @brief Calcule le niveau moyen de contamination dans toute la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le niveau moyen de contamination (0.0 à 1.0).
 */
double average_contamination(city_t *city);

/**
 * @brief Contamine tous les citoyens présents sur une case spécifique.
 * @param city Pointeur vers la structure de la ville.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 */
void contaminate_citizens_on_tile(city_t *city, unsigned int x, unsigned int y);

/**
 * @brief Contamine les citoyens sur les cases voisines autour d'une case spécifique.
 * @param city Pointeur vers la structure de la ville.
 * @param x Coordonnée x de la case centrale.
 * @param y Coordonnée y de la case centrale.
 */
void contaminate_citizens_on_tiles_around(city_t *city, unsigned int x, unsigned int y);

/**
 * @brief Éjecte tous les citoyens guéris de leurs cases actuelles.
 * @param city Pointeur vers la structure de la ville.
 */
void eject_healed(city_t *city);

/**
 * @brief Vérifie si un médecin est présent sur une case spécifique.
 * @param city Pointeur vers la structure de la ville.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 * @return 1 si un médecin est présent, 0 sinon.
 */
int doctor_present(city_t *city, unsigned int x, unsigned int y);

/**
 * @brief Vérifie si un pompier est présent sur une case spécifique.
 * @param city Pointeur vers la structure de la ville.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 * @return 1 si un pompier est présent, 0 sinon.
 */
int hasFireFighter(city_t *city, unsigned int x, unsigned int y);

/**
 * @brief Compte le nombre total de citoyens morts dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre de citoyens morts.
 */
int get_number_of_dead(city_t *city);

/**
 * @brief Compte le nombre total de citoyens en bonne santé dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre de citoyens en bonne santé.
 */
int get_number_of_healthy(city_t *city);

/**
 * @brief Compte le nombre total de citoyens malades dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre de citoyens malades.
 */
int get_number_of_sick(city_t *city);

/**
 * @brief Affiche l'état actuel de la ville (grille et statistiques).
 * @param city Pointeur vers la structure de la ville.
 */
void display_city(city_t *city);

/**
 * @brief Compte le nombre total de citoyens présents dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre total de citoyens.
 */
int get_number_citizen(city_t *city);

/**
 * @brief Compte le nombre de citoyens brûlés dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre de citoyens brûlés.
 */
int get_number_of_burned(city_t *city);

/**
 * @brief Compte le nombre de citoyens sur une case spécifique.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 * @param city Pointeur vers la structure de la ville.
 * @return Le nombre de citoyens sur la case.
 */
int get_number_citizen_on_tile(int x, int y, city_t *city);

/**
 * @brief Récupère les identifiants des citoyens morts dans la ville.
 * @param city Pointeur vers la structure de la ville.
 * @return Un tableau contenant les identifiants des citoyens morts.
 */
int *get_dead_id(city_t *city);

/**
 * @brief Propage la contamination à partir des terrains vagues dans la ville.
 * @param city Pointeur vers la structure de la ville.
 */
void wasteland_contamination_spread(city_t *city);




/* ... d'autres fonctions pour gérer la contamination, etc. ... */

#endif /* CITY_MANAGER_H */
