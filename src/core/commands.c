#include "hemera.h"

// ============================================================================
//                           HANDLERS DE COMMANDES
// ============================================================================

int cmd_exit(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    (void)args; (void)enemy_count;
    printf("Au revoir %s !\n", player->name);
    cleanup_and_exit(enemies);
    exit(0);
}

int cmd_stats(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    (void)enemies; (void)enemy_count; (void)args;
    if (debug)
        super_stats(*player);
    else
        print_stats(*player);
    return 0;
}

int cmd_fight(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    t_enemy *chosen_enemy = choose_enemy(enemies, enemy_count, args);

    if (chosen_enemy)
    {
        int result = fight(player, chosen_enemy);
        const char *messages[] = {
            "Le combat a échoué.\n",
            "Vous avez gagné le combat !\n",
            "Vous avez perdu le combat.\n"
        };

        // Gestion sécurisée des résultats
        if (result >= -1 && result <= 1)
            printf("%s", messages[result + 1]);
        else
            printf("Résultat de combat inattendu.\n");
    }
    return 0;
}

int cmd_levelup(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    (void)enemies; (void)enemy_count; (void)args;
    level_up(player);
    return 0;
}

int cmd_enemies(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    (void)player; (void)args;
    list_enemies(enemies, enemy_count);
    return 0;
}

int cmd_help(t_player *player, t_enemy *enemies, int enemy_count, char *args)
{
    (void)player; (void)enemies; (void)enemy_count; (void)args;

    extern t_command commands[]; // Déclaration externe

    printf("\n=== COMMANDES DISPONIBLES ===\n");
    printf("Commandes générales :\n");

    for (int i = 0; commands[i].name; i++)
    {
        if (!commands[i].admin_only)
            printf("  %-10s - %s\n", commands[i].name, commands[i].description);
    }

    if (debug)
    {
        printf("\nCommandes admin (mode debug) :\n");
        for (int i = 0; commands[i].name; i++)
        {
            if (commands[i].admin_only)
                printf("  %-10s - %s\n", commands[i].name, commands[i].description);
        }
    }

    printf("\nCommandes système :\n");
    printf("  /debug     - Activer/désactiver le mode debug\n");
    printf("\n");
    return 0;
}

// ============================================================================
//                            TABLE DES COMMANDES
// ============================================================================

t_command commands[] = {
    {"exit",     cmd_exit,    0, "Quitter le jeu"},
    {"quit",     cmd_exit,    0, "Quitter le jeu"},
    {"stats",    cmd_stats,   0, "Afficher les statistiques du joueur"},
    {"help",     cmd_help,    0, "Afficher cette aide"},
    {"fight",    cmd_fight,   1, "Combattre un ennemi (fight, fight <nom>, fight <index>, fight random)"},
    {"levelup",  cmd_levelup, 1, "Monter d'un niveau (debug)"},
	{"lvl",      cmd_levelup, 1, "MACRO levelup"},
    {"enemies",  cmd_enemies, 1, "Lister tous les ennemis disponibles"},
    {NULL,       NULL,        0, NULL} // Sentinelle pour marquer la fin
};

// ============================================================================
//                          FONCTIONS UTILITAIRES
// ============================================================================

t_command *find_command(char *name)
{
    if (!name)
        return NULL;

    for (int i = 0; commands[i].name; i++)
    {
        if (strcmp(commands[i].name, name) == 0)
            return &commands[i];
    }
    return NULL;
}

int execute_command(char *input, t_player *player, t_enemy *enemies, int enemy_count)
{
    if (!input || strlen(input) == 0)
        return 0;

    // Séparer la commande des arguments
    char *cmd_copy = strdup(input);
    char *cmd_name = strtok(cmd_copy, " ");
    char *args = strtok(NULL, ""); // Récupère le reste de la ligne

    if (!cmd_name)
    {
        free(cmd_copy);
        return 0;
    }

    // Chercher la commande
    t_command *cmd = find_command(cmd_name);

    if (!cmd)
    {
        printf("Commande inconnue : '%s'. Tapez 'help' pour voir les commandes disponibles.\n", cmd_name);
        free(cmd_copy);
        return 0;
    }

    // Vérifier les permissions admin
    if (cmd->admin_only && !debug)
    {
        printf("Cette commande nécessite le mode debug. Tapez '/debug' pour l'activer.\n");
        free(cmd_copy);
        return 0;
    }

    // Exécuter la commande
    int result = cmd->handler(player, enemies, enemy_count, args);

    free(cmd_copy);
    return result;
}
