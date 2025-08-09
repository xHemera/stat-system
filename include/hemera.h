#ifndef HEMERA_H
#define HEMERA_H

// ============================================================================
//                               INCLUDES
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// ============================================================================
//                              CONSTANTES
// ============================================================================
#define MAX_NAME_LENGTH     20
#define MAX_ENEMY_NAME      50
#define MAX_ENEMIES         100
#define PROMPT_NORMAL       "> "
#define PROMPT_DEBUG        " > "

// ============================================================================
//                           VARIABLES GLOBALES
// ============================================================================
extern int debug;

// ============================================================================
//                              STRUCTURES
// ============================================================================

/**
 * @brief Structure contenant toutes les statistiques d'une entité
 */
typedef struct s_stats {
    // Survivabilité
    float health;             // Points de vie fixes
    float heal_shield_power;  // Soins/boucliers reçus × (1 + heal_shield_power / 10)
    float vampirism;          // Vie volée = dégâts infligés × (vampirism / 100)

    // Magie
    float magical_dmg;        // Puissance magique
    float magic_armor;        // Réduction des dégâts magiques reçus
    float magic_pen;          // Pénétration d'armure magique

    // Physique
    float physical_dmg;       // Puissance physique
    float armor;              // Réduction des dégâts physiques reçus
    float armor_pen;          // Pénétration d'armure physique

    // Énergie
    int energy;               // Ressource pour les actions spéciales
    int energy_regen;         // Points d'énergie récupérés par tour
} t_stats;

/**
 * @brief Structure représentant un joueur
 */
typedef struct s_player {
    char name[MAX_NAME_LENGTH];
    int level;
    t_stats base;             // Stats de base (scalent avec le niveau)
    t_stats bonus;            // Bonus accordés par les objets/buffs
    t_stats total;            // Stats totales utilisées en combat
} t_player;

/**
 * @brief Structure représentant un ennemi
 */
typedef struct s_enemy {
    char name[MAX_ENEMY_NAME];
    int level;
    t_stats base;             // Stats de base niveau 1
    t_stats total;            // Stats calculées selon le niveau
    int experience_reward;    // XP donnée à la mort
    int gold_reward;          // Or donné à la mort
} t_enemy;

// ============================================================================
//                          PROTOTYPES DE FONCTIONS
// ============================================================================

// --- Gestion du joueur ---
t_player newPlayer(char *name);
void updateStats(t_player *player);
void level_up(t_player *player);

// --- Gestion des ennemis ---
t_enemy load_enemy_from_line(char *line);
t_enemy *load_enemies(const char *filename, int *count);
t_enemy get_enemy_by_name(t_enemy *enemies, int count, const char *name);

// --- Affichage ---
void print_stats(t_player player);
void super_stats(t_player player);
void list_enemies(t_enemy *enemies, int enemy_count);

// --- Utilitaires ---
int is_alpha(char *src);
char *str_simplify(char *src);
t_stats stats_add(const t_stats *base, int level, const t_stats *bonus);
void cleanup_and_exit(t_enemy *enemies);

// --- Boucle principale ---
int main_loop(t_player *player, t_enemy *enemies, int enemy_count);

#endif /* HEMERA_H */
