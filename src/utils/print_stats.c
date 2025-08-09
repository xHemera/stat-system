#include "hemera.h"

void print_stats(t_player player)
{
    printf("=== Stats de %s (Niveau %d) ===\n", player.name, player.level);

    // Survivabilité
    printf("  Health           : %.0f\n", player.total.health);
    printf("  Heal/Shield Power: %.1f\n", player.total.heal_shield_power);
    printf("  Vampirism        : %.1f%%\n", player.total.vampirism);

    // Magie
    printf("\n  Magical Dmg      : %.1f\n", player.total.magical_dmg);
    printf("  Magic Armor      : %.1f\n", player.total.magic_armor);
    printf("  Magic Pen        : %.1f\n", player.total.magic_pen);

    // Physique
    printf("\n  Physical Dmg     : %.1f\n", player.total.physical_dmg);
    printf("  Armor            : %.1f\n", player.total.armor);
    printf("  Armor Pen        : %.1f\n", player.total.armor_pen);

    // Énergie
    printf("\n  Energy           : %d\n", player.total.energy);
    printf("  Energy Regen     : %d\n", player.total.energy_regen);
}
