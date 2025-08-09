#include "hemera.h"

int	is_alpha(char *src)
{
    if (!src || !src[0])
        return 0;

    for (int i = 0; src[i]; i++)
    {
        if (!isalpha((unsigned char)src[i]))
            return 0;
    }
    return 1;
}

char *str_simplify(char *src)
{
    if (!src)
        return NULL;

    int len = strlen(src);
    char *ret = malloc(len + 1);
    if (!ret)
        return NULL;

    for (int i = 0; i <= len; i++) // Inclut le '\0'
    {
        ret[i] = tolower((unsigned char)src[i]);
    }
    return ret;
}

void cleanup_and_exit(t_enemy *enemies)
{
    if (enemies)
        free(enemies);

    clear_history();

    if (debug)
        printf("[DEBUG] Nettoyage terminé.\n");

    exit(0);
}
