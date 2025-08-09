#include "hemera.h"

int main_loop(t_player *player, t_enemy *enemies, int enemy_count)
{
    char *cmd, *simple;
    const char *prompt;

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

        if (simple[0] == '/')
        {
            if (strcmp(simple, "/debug") == 0)
            {
                debug = !debug;
                printf("[DEBUG] Mode debug %s.\n", debug ? "activé" : "désactivé");
            }
            else if (strcmp(simple, "/exit") == 0 || strcmp(simple, "/quit") == 0)
            {
                printf("Au revoir %s !\n", player->name);
                free(simple);
                free(cmd);
                cleanup_and_exit(enemies);
                return 0;
            }
        }
        else if (is_alpha(cmd))
        {
            if (strcmp(simple, "exit") == 0 || strcmp(simple, "quit") == 0)
            {
                printf("Au revoir %s !\n", player->name);
                free(simple);
                free(cmd);
                cleanup_and_exit(enemies);
                return 0;
            }
            else if (strcmp(simple, "stats") == 0)
            {
                if (debug)
                    super_stats(*player);
                else
                    print_stats(*player);
            }
            else if (strcmp(simple, "levelup") == 0 && debug)
                level_up(player);
            else if (strcmp(simple, "enemies") == 0 && debug)
                list_enemies(enemies, enemy_count);
        }

        free(simple);
        free(cmd);
    }
}
