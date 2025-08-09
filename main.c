#include "hemera.h"

int debug = 0;

int main()
{
    char *name;
    debug = 0;

    printf("Entrez un nom de joueur :\n");
    while (1)
    {
        name = readline("> ");
        if (name && is_alpha(name))
            break ;
        free(name);
    }

    t_player player = newPlayer(name);
    free(name);

    printf("Bienvenue %s!\n", player.name);

    int enemy_count;
    t_enemy *enemies = load_enemies("data/enemies", &enemy_count);
    if (enemies)
        printf("Chargé %d ennemis\n", enemy_count);

    main_loop(&player, enemies, enemy_count);

    free(enemies);
    return 0;
}
