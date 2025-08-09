#include "hemera.h"

int debug = 0;

int main_loop(t_player *player)
{
    char *cmd;
    char *simple;
    const char *prompt;

    while (1)
    {
        updateStats(player);
        prompt = debug ? " > " : "> ";
        cmd = readline(prompt);
        if (!cmd)
            continue;
        simple = str_simplify(cmd);

        if (strcmp(simple, "/debug") == 0)
        {
            debug = !debug;
            printf("[DEBUG] Mode debug %s.\n", debug ? "activé" : "désactivé");
        }
        else if (strcmp(simple, "stats") == 0)
            debug ? super_stats(*player) : print_stats(*player);
		// else if (strcmp(simple, "exemple") == 0)
        // {
        // 	debug ? fonction_admin(*player) : fonction_normale(*player);
		// 	fonction_normale(*player); si pas de commande admin
        // }

        free(simple);
        free(cmd);
    }
    return 0;
}

int main()
{
    char *name;
    debug = 0; // Remise à zéro à chaque démarrage

    printf("Entrez un nom de joueur :\n");
    while (1)
    {
        name = readline("> ");
        if (name && is_alpha(name))
            break ;
        free(name); // Free uniquement quand le nom n'est pas valide
    }

    t_player player = newPlayer(name);
    free(name);

    printf("Bienvenue %s!\n", player.name);
    main_loop(&player);
    return 0;
}
