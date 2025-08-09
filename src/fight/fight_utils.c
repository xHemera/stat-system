#include "hemera.h"

t_enemy *choose_enemy(t_enemy *enemies, int enemy_count, char *param)
{
    if (!enemies || enemy_count <= 0)
    {
        printf("Aucun ennemi disponible pour le combat.\n");
        return NULL;
    }

    // Si aucun paramètre → menu interactif
    if (!param || strlen(param) == 0)
    {
        printf("\n=== CHOISIR UN ENNEMI ===\n");

        int i = 0;
        while (i < enemy_count)
        {
            printf("%d. %s (Niveau %d) - HP: %.0f\n",
                   i + 1, enemies[i].name, enemies[i].level, enemies[i].total.health);
            i++;
        }

        printf("0. Annuler\n");
        printf("Votre choix : ");

        char *input = readline("");
        if (!input) return NULL;

        int choice = atoi(input);
        free(input);

        if (choice == 0) return NULL;
        if (choice < 1 || choice > enemy_count)
        {
            printf("Choix invalide.\n");
            return NULL;
        }

        return &enemies[choice - 1];
    }

    // Si paramètre "random" → ennemi aléatoire
    if (strcmp(param, "random") == 0)
    {
        int random_index = rand() % enemy_count;
        printf("Ennemi choisi au hasard : %s\n", enemies[random_index].name);
        return &enemies[random_index];
    }

    // Si paramètre numérique → ennemi par index
    int index = atoi(param);
    if (index > 0 && index <= enemy_count)
    {
        return &enemies[index - 1];
    }

    // Recherche par nom (sans boucle for)
    int i = 0;
    while (i < enemy_count)
    {
        if (strcasecmp(enemies[i].name, param) == 0)
        {
            return &enemies[i];
        }
        i++;
    }

    printf("Ennemi '%s' introuvable.\n", param);
    printf("Tapez 'enemies' pour voir la liste des ennemis disponibles.\n");
    return NULL;
}

char *extract_fight_param(char *cmd)
{
    if (strncmp(cmd, "fight", 5) != 0)
        return NULL;

    char *param_start = cmd + 5;

    while (*param_start == ' ')
        param_start++;

    if (*param_start == '\0')
        return NULL;

    char *param = strdup(param_start);

    int len = strlen(param);
    while (len > 0 && param[len - 1] == ' ')
    {
        param[len - 1] = '\0';
        len--;
    }
    return param;
}
