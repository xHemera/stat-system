#include "hemera.h"

int	is_alpha(char *src)
{
    int i = 0;
    if (!src || !src[0])
        return 0;
    while (src[i])
    {
        if (!isalpha((unsigned char)src[i]))
            return 0;
        i++;
    }
    return 1;
}

char *str_simplify(char *src)
{
    int len = strlen(src);
    char *ret = malloc(len + 1);
    if (!ret)
        return NULL;
    int i = 0;
    while (src[i])
    {
        ret[i] = tolower((unsigned char)src[i]);
        i++;
    }
    ret[i] = '\0';
    return ret;
}
