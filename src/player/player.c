#include "hemera.h"

static t_stats stats_zero(void)
{
    t_stats s = {0};
    return s;
}

t_player newPlayer(char *name)
{
    if (strlen(name) >= 20) {
        fprintf(stderr, "Erreur: Le nom du joueur est trop long.\n");
        exit(EXIT_FAILURE);
    }

    t_player player = {0};
    strcpy(player.name, name);
	player.level = 1;

    // Stats de base (niveau 1)
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

    player.bonus = stats_zero();

    updateStats(&player);
    return player;
}

// Additionne deux t_stats, le premier étant déjà multiplié par le niveau
t_stats stats_add(const t_stats *base, int level, const t_stats *bonus)
{
    t_stats res;
    res.health = base->health * level + bonus->health;
    res.heal_shield_power = base->heal_shield_power * level + bonus->heal_shield_power;
    res.vampirism = base->vampirism * level + bonus->vampirism;

    res.magical_dmg = base->magical_dmg * level + bonus->magical_dmg;
    res.magic_armor = base->magic_armor * level + bonus->magic_armor;
    res.magic_pen = base->magic_pen * level + bonus->magic_pen;

    res.physical_dmg = base->physical_dmg * level + bonus->physical_dmg;
    res.armor = base->armor * level + bonus->armor;
    res.armor_pen = base->armor_pen * level + bonus->armor_pen;

    res.energy = base->energy + bonus->energy;
    res.energy_regen = base->energy_regen + bonus->energy_regen;
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
