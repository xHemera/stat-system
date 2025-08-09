#include "hemera.h"

t_player newPlayer(char *name)
{
    if (!name || strlen(name) == 0)
    {
        fprintf(stderr, "Erreur: Le nom du joueur ne peut pas être vide.\n");
        exit(EXIT_FAILURE);
    }

    if (strlen(name) >= MAX_NAME_LENGTH)
    {
        fprintf(stderr, "Erreur: Le nom du joueur est trop long (max %d caractères).\n", MAX_NAME_LENGTH - 1);
        exit(EXIT_FAILURE);
    }

    t_player player = {0};
    strncpy(player.name, name, MAX_NAME_LENGTH - 1);
    player.name[MAX_NAME_LENGTH - 1] = '\0'; // Assurer la terminaison
	player.level = 1;

    // Stats de base (niveau 1) - utilisation d'initialisation compound
    player.base = (t_stats){
        .health = 100,
        .heal_shield_power = 1,
        .vampirism = 0,
        .magical_dmg = 0,
        .magic_armor = 10,
        .magic_pen = 0,
        .physical_dmg = 10,
        .armor = 10,
        .armor_pen = 0,
        .energy = 20,
        .energy_regen = 2
    };

    player.bonus = (t_stats){0}; // Initialisation plus claire

    updateStats(&player);
    return player;
}

// Additionne deux t_stats, le premier étant déjà multiplié par le niveau
t_stats stats_add(const t_stats *base, int level, const t_stats *bonus)
{
    t_stats res = {
        .health = base->health * level + bonus->health,
        .heal_shield_power = base->heal_shield_power * level + bonus->heal_shield_power,
        .vampirism = base->vampirism * level + bonus->vampirism,
        .magical_dmg = base->magical_dmg * level + bonus->magical_dmg,
        .magic_armor = base->magic_armor * level + bonus->magic_armor,
        .magic_pen = base->magic_pen * level + bonus->magic_pen,
        .physical_dmg = base->physical_dmg * level + bonus->physical_dmg,
        .armor = base->armor * level + bonus->armor,
        .armor_pen = base->armor_pen * level + bonus->armor_pen,
        .energy = base->energy + bonus->energy,
        .energy_regen = base->energy_regen + bonus->energy_regen
    };
    return res;
}

void updateStats(t_player *player)
{
    player->total = stats_add(&player->base, player->level, &player->bonus);
}

void level_up(t_player *player)
{
	printf("Vous avez monte de niveau!\n");
	player->level += 1;
}
