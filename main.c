#include "hemera.h"

int debug = 0;
static t_enemy *global_enemies = NULL;

void signal_handler(int sig)
{
    if (sig == SIGINT) // Ctrl+C
    {
        printf("Tapez 'exit' pour quitter proprement.\n");
        printf("Ou tapez Ctrl+D pour forcer la sortie.\n");

        // Réafficher le prompt
        const char *prompt = debug ? PROMPT_DEBUG : PROMPT_NORMAL;
        printf("%s", prompt);
        fflush(stdout);
    }
}

int main()
{
    char *name;
    debug = 0;

    // Configuration des signaux
    signal(SIGINT, signal_handler);
	clrscr();
    printf("Entrez un nom de joueur :\n");
    while (1)
    {
        name = readline("> ");
        if (!name) // Ctrl+D pendant la saisie du nom
        {
            printf("\nAu revoir !\n");
            exit(0);
        }
        if (name && is_alpha(name))
            break;
        free(name);
    }

    t_player player = newPlayer(name);
    free(name);

    printf("Bienvenue %s!\n", player.name);
    printf("Tapez 'exit' ou 'quit' pour quitter, ou utilisez Ctrl+D.\n");

    int enemy_count;
    t_enemy *enemies = load_enemies("data/enemies", &enemy_count);
    global_enemies = enemies;

    main_loop(&player, enemies, enemy_count);

    cleanup_and_exit(enemies);
    return 0;
}
