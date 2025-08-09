#ifndef HEMERA_H
#define HEMERA_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int debug;

typedef struct s_stats {
	// Survivabilité
	float	health;             // Points de vie fixes. Les dégâts reçus sont réduits par armor ou magic_armor selon le type d'attaque.
	float	heal_shield_power;  // Soins/boucliers reçus × (1 + heal_shield_power / 10)
	float	vampirism;          // Vie volée = dégâts infligés × (vampirism / 100)

	// Magie
	float	magical_dmg;        // Puissance magique. Dégâts d'un sort = base_spell × {scaling du sort}
	float	magic_armor;        // Réduction des dégâts magiques reçus : dégâts subis = dégâts × (100 / (100 + magic_armor - magic_pen))
	float	magic_pen;          // Ignore une partie de la magic_armor adverse : magic_armor_effective = cible.magic_armor - magic_pen

	// Physique
	float	physical_dmg;       // Puissance physique. Dégâts d'une attaque = base_attack + physical_dmg
	float	armor;              // Réduction des dégâts physiques reçus : dégâts subis = dégâts × (100 / (100 + armor - armor_pen))
	float	armor_pen;          // Ignore une partie de l'armor adverse : armor_effective = cible.armor - armor_pen

	// Énergie
	int		energy;             // Ressource pour les actions spéciales (sorts, techniques)
	int		energy_regen;       // Points d'énergie récupérés par tour
} t_stats;

typedef struct s_player {
	char 	name[20];
	int		level;
	t_stats	base; //Scale en fonction du niveau
	t_stats bonus; //Bonus accorde par les items
	t_stats	total; //Stats totals utilises en combat
} t_player;

// Declaration des fonctions
t_player newPlayer(char *name);
int	is_alpha(char *src);
char *str_simplify(char *src);
void print_stats(t_player player);
void updateStats(t_player *player);
t_stats stats_add(const t_stats *base, int level, const t_stats *bonus);
void super_stats(t_player player);
void level_up(t_player *player);

#endif
