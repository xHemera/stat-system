#include "hemera.h"

void super_stats(t_player player)
{
    const char *top =  "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    const char *sep =  "│───────────────────────────────────────────────────────────────────────────│";
    const char *bottom = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    printf("\n%s\n", top);
    printf("│              SUPER STATS de %-20s (Niveau %-2d)             │\n", player.name, player.level);
    printf("%s\n", sep);

    // Survivabilité
    printf("│   Health            │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.health, player.base.health * player.level, player.bonus.health);
    printf("│   Heal/Shield Power │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.heal_shield_power, player.base.heal_shield_power * player.level, player.bonus.heal_shield_power);
    printf("│   Vampirism         │ Total:%8.1f%% │ Base: %8.1f%%│ Bonus:%8.1f%% │\n",
        player.total.vampirism, player.base.vampirism * player.level, player.bonus.vampirism);

    printf("%s\n", sep);

    // Magie
    printf("│   Magical Dmg       │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.magical_dmg, player.base.magical_dmg * player.level, player.bonus.magical_dmg);
    printf("│   Magic Armor       │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.magic_armor, player.base.magic_armor * player.level, player.bonus.magic_armor);
    printf("│   Magic Pen         │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.magic_pen, player.base.magic_pen * player.level, player.bonus.magic_pen);

    printf("%s\n", sep);

    // Physique
    printf("│   Physical Dmg      │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.physical_dmg, player.base.physical_dmg * player.level, player.bonus.physical_dmg);
    printf("│   Armor             │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.armor, player.base.armor * player.level, player.bonus.armor);
    printf("│   Armor Pen         │ Total: %8.1f │ Base: %8.1f │ Bonus: %8.1f │\n",
        player.total.armor_pen, player.base.armor_pen * player.level, player.bonus.armor_pen);

    printf("%s\n", sep);

    // Énergie
    printf("│   Energy            │ Total: %8d │ Base: %8d │ Bonus: %8d │\n",
        player.total.energy, (int)(player.base.energy * player.level), player.bonus.energy);
    printf("│   Energy Regen      │ Total: %8d │ Base: %8d │ Bonus: %8d │\n",
        player.total.energy_regen, (int)(player.base.energy_regen * player.level), player.bonus.energy_regen);

    printf("%s\n\n", bottom);
}

void list_enemies(t_enemy *enemies, int enemy_count)
{
    if (!enemies || enemy_count <= 0)
    {
        printf("Aucun ennemi chargé.\n");
        return;
    }

    const char *top =    "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
    const char *sep =    "│─────────────────────────────────────────────────────────────────────────────────────────────────│";
    const char *bottom = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

    printf("\n%s\n", top);
    printf("│                               LISTE DES ENNEMIS (%d chargés)                                │\n", enemy_count);
    printf("%s\n", sep);
    printf("│ %-20s │ Niv │   HP   │ P.Dmg │ M.Dmg │ Armor │ M.Armor │  XP  │ Gold │\n", "Nom");
    printf("%s\n", sep);

    for (int i = 0; i < enemy_count; i++)
    {
        printf("│ %-20s │ %3d │ %6.0f │ %5.1f │ %5.1f │ %5.1f │  %5.1f  │ %4d │ %4d │\n",
            enemies[i].name,
            enemies[i].level,
            enemies[i].total.health,
            enemies[i].total.physical_dmg,
            enemies[i].total.magical_dmg,
            enemies[i].total.armor,
            enemies[i].total.magic_armor,
            enemies[i].experience_reward,
            enemies[i].gold_reward
        );
    }
    printf("%s\n\n", bottom);
}
