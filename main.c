#include "hemera.h"

int main_loop(t_player player)
{
    char *cmd;
    char *simple;

    while (1)
    {
        cmd = readline("> ");
        if (cmd && is_alpha(cmd))
        {
            simple = str_simplify(cmd);
            if (simple && strcmp(simple, "stats") == 0)
                print_stats(player);
            free(simple);
        }
        free(cmd);
    }
    return 0;
}

int main()
{
    char *name;

    printf("Entrez un nom de joueur :\n");
    while (1)
    {
        name = readline("> ");
        if (name && is_alpha(name))
            break ;
        free(name); //Free uniquement quand le nom n'est pas valide (si valide on break)
    }

    t_player player = newPlayer(name);
    free(name);

    printf("Bienvenue %s!\n", player.name);
    main_loop(player);
    return 0;
}
