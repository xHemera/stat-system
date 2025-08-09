#include "hemera.h"

int main_loop(t_player *player, t_enemy *enemies, int enemy_count)
{
    char *cmd, *simple;
    const char *prompt;

    while (1)
    {
        updateStats(player);
        prompt = debug ? " > " : "> ";
        cmd = readline(prompt);
        if (!cmd)
        {
            free(cmd);
            continue;
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
        }
        else if (is_alpha(cmd))
        {
            if (strcmp(simple, "stats") == 0)
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
    return 0;
}
