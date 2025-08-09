#include "hemera.h"

t_player newPlayer(char *name)
{
	// Gerer le cas d'erreur
	if (strlen(name) >= 20) {
		fprintf(stderr, "Erreur: Le nom du joueur est trop long.\n");
		exit(EXIT_FAILURE);
	}

	t_player player;

	player.stats.attack = 1;
	player.stats.health = 10;
	strcpy(player.name, name);

	return player;
}
