#include "hemera.h"

void print_stats(t_player player)
{
	printf("=== Stats de %s ===\n󰓥 Attack: %i\n Health: %i\n", player.name, player.stats.attack, player.stats.health);
	return ;
}
