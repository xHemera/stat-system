#include "hemera.h"

int main_loop(t_player *player, t_enemy *enemies, int enemy_count)
{
    char *cmd, *simple;
    const char *prompt;

    printf("Simple RPG combat management\n");
    while (1)
    {
        updateStats(player);
        prompt = debug ? PROMPT_DEBUG : PROMPT_NORMAL;
        cmd = readline(prompt);

        // Gestion de Ctrl+D (EOF)
        if (!cmd)
        {
            printf("\nAu revoir %s !\n", player->name);
            cleanup_and_exit(enemies);
            return 0;
        }

        simple = str_simplify(cmd);
        if (!simple)
        {
            free(cmd);
            continue;
        }

        // Commandes système commençant par /
        if (simple[0] == '/')
        {
            if (strcmp(simple, "/debug") == 0)
            {
                debug = !debug;
                printf("[DEBUG] Mode debug %s.\n", debug ? "activé" : "désactivé");
            }
            else
                printf("Commande système inconnue : '%s'\n", simple);
        }
        else
            execute_command(simple, player, enemies, enemy_count);

        free(simple);
        free(cmd);
    }
}
