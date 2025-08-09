#include "hemera.h"

static void calculate_enemy_stats(t_enemy *enemy)
{
    // Scaling simple : stats_base × niveau
    enemy->total.health = enemy->base.health * enemy->level;
    enemy->total.heal_shield_power = enemy->base.heal_shield_power * enemy->level;
    enemy->total.vampirism = enemy->base.vampirism * enemy->level;

    enemy->total.magical_dmg = enemy->base.magical_dmg * enemy->level;
    enemy->total.magic_armor = enemy->base.magic_armor * enemy->level;
    enemy->total.magic_pen = enemy->base.magic_pen * enemy->level;

    enemy->total.physical_dmg = enemy->base.physical_dmg * enemy->level;
    enemy->total.armor = enemy->base.armor * enemy->level;
    enemy->total.armor_pen = enemy->base.armor_pen * enemy->level;

    enemy->total.energy = enemy->base.energy;
    enemy->total.energy_regen = enemy->base.energy_regen;
}

t_enemy load_enemy_from_line(char *line)
{
    t_enemy enemy = {0};
    char *token;
    int field = 0;
    const int expected_fields = 15;

    token = strtok(line, "|");
    while (token != NULL && field < expected_fields)
    {
        // Nettoyer les espaces en début/fin
        while (*token == ' ') token++;
        int len = strlen(token);
        while (len > 0 && token[len-1] == ' ') token[--len] = '\0';

        switch (field)
        {
            case 0:
                strncpy(enemy.name, token, MAX_ENEMY_NAME - 1);
                enemy.name[MAX_ENEMY_NAME - 1] = '\0';
                break;
            case 1: enemy.level = atoi(token); break;
            case 2: enemy.base.health = atof(token); break;
            case 3: enemy.base.heal_shield_power = atof(token); break;
            case 4: enemy.base.vampirism = atof(token); break;
            case 5: enemy.base.magical_dmg = atof(token); break;
            case 6: enemy.base.magic_armor = atof(token); break;
            case 7: enemy.base.magic_pen = atof(token); break;
            case 8: enemy.base.physical_dmg = atof(token); break;
            case 9: enemy.base.armor = atof(token); break;
            case 10: enemy.base.armor_pen = atof(token); break;
            case 11: enemy.base.energy = atoi(token); break;
            case 12: enemy.base.energy_regen = atoi(token); break;
            case 13: enemy.experience_reward = atoi(token); break;
            case 14: enemy.gold_reward = atoi(token); break;
        }
        token = strtok(NULL, "|");
        field++;
    }

    // Validation des données critiques
    if (enemy.level <= 0) enemy.level = 1;
    if (enemy.base.health <= 0) enemy.base.health = 10;

    calculate_enemy_stats(&enemy);
    return enemy;
}

t_enemy *load_enemies(const char *filename, int *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Erreur: impossible d'ouvrir %s\n", filename);
        *count = 0;
        return NULL;
    }

    t_enemy *enemies = malloc(sizeof(t_enemy) * 100); // Max 100 ennemis
    char line[512];
    *count = 0;

    while (fgets(line, sizeof(line), file) && *count < 100)
    {
        // Ignorer les commentaires et lignes vides
        if (line[0] == '#' || line[0] == '\n')
            continue;

        // Supprimer le \n
        line[strcspn(line, "\n")] = 0;

        enemies[*count] = load_enemy_from_line(line);
        (*count)++;
    }

    fclose(file);
    return enemies;
}

t_enemy get_enemy_by_name(t_enemy *enemies, int count, const char *name)
{
    if (!enemies || !name || count <= 0)
    {
        t_enemy empty = {0};
        strncpy(empty.name, "Unknown", MAX_ENEMY_NAME - 1);
        empty.name[MAX_ENEMY_NAME - 1] = '\0';
        return empty;
    }

    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(enemies[i].name, name) == 0) // Comparaison insensible à la casse
            return enemies[i];
    }

    // Retourner un ennemi vide si non trouvé
    t_enemy empty = {0};
    strncpy(empty.name, "Unknown", MAX_ENEMY_NAME - 1);
    empty.name[MAX_ENEMY_NAME - 1] = '\0';
    return empty;
}
