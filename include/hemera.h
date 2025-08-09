#ifndef HEMERA_H
#define HEMERA_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>

typedef struct s_stats {
	int attack;
	int health;
} t_stats;

typedef struct s_player {
	char 	name[20];
	t_stats	stats;
} t_player;

// Declaration des fonctions
t_player newPlayer(char *name);
int	is_alpha(char *src);
char *str_simplify(char *src);
void print_stats(t_player player);

#endif
