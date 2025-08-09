#include "hemera.h"

// ===== AFFICHAGE =====

void display_health_bar(float health_percent)
{
	int bar_length = 20;
	int filled = (int)(health_percent / 100.0 * bar_length);

	printf("[");

	for (int i = 0; i < filled; i++)
	{
		if (health_percent > 60)
			printf("█");
		else if (health_percent > 30)
			printf("▓");
		else
			printf("▒");
	}

	for (int i = filled; i < bar_length; i++)
		printf("░");

	printf("] %.0f%%", health_percent);
}

static void display_combatant_status(const char *name, int level, float current_hp, float max_hp)
{
	float health_percent = (current_hp / max_hp) * 100;
	printf("%s (Niveau %d)\n", name, level);
	printf("❤️   %.0f/%.0f ", current_hp, max_hp);
	display_health_bar(health_percent);
	printf("\n");
}

static void display_combat_header(int turn)
{
	printf("╔═══════════════════════════════════════════════════════════════╗\n");
	char header_text[64];
	snprintf(header_text, sizeof(header_text), "COMBAT - Tour %d", turn);
	int header_len = strlen(header_text);
	int total_width = 63;
	int padding = (total_width - header_len) / 2;
	printf("║%*s%s%*s║\n", padding, "", header_text, total_width - padding - header_len, "");
	printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
}

// ===== INITIATIVE =====

int calculate_initiative(t_player *player, t_enemy *enemy)
{
	int level_diff = player->level - enemy->level;

	printf("🎲 Test d'initiative:\n");
	printf("   %s (Niveau %d) vs %s (Niveau %d)\n",
		   player->name, player->level, enemy->name, enemy->level);
	printf("   Différence de niveau: %+d\n", level_diff);

	// Victoire automatique basée sur les niveaux
	if (level_diff <= -5)
	{
		printf("   Votre niveau est trop faible... %s a l'initiative!\n", enemy->name);
		return 0;
	}
	if (level_diff >= 5)
	{
		printf("   L'ennemi est faible! %s a l'initiative!\n", player->name);
		return 1;
	}

	// Calcul pondéré par l'énergie
	printf("   Calcul d'initiative basé sur l'énergie...\n");
	printf("   %s énergie: %d\n", player->name, player->total.energy);
	printf("   %s énergie: %d\n", enemy->name, enemy->total.energy);

	int total_energy = player->total.energy + enemy->total.energy;
	int initiative_roll = rand() % total_energy;
	int player_wins = (initiative_roll < player->total.energy);

	printf("   %s gagne l'initiative! (tirage: %d/%d)\n",
		   player_wins ? player->name : enemy->name, initiative_roll, total_energy);

	return player_wins;
}

// ===== COMBAT LOGIC =====

float calculate_physical_damage(float attack, float armor, float armor_pen)
{
	float effective_armor = armor - armor_pen;
	if (effective_armor < 0) effective_armor = 0;

	float damage = attack - effective_armor;
	return damage > 1.0f ? damage : 1.0f; // Minimum 1 dégât
}

float calculate_magical_damage(float magic_attack, float magic_armor, float magic_pen)
{
	float effective_magic_armor = magic_armor - magic_pen;
	if (effective_magic_armor < 0) effective_magic_armor = 0;

	float damage = magic_attack - effective_magic_armor;
	return damage > 1.0f ? damage : 1.0f; // Minimum 1 dégât
}

// Fonction simplifiée pour les attaques physiques standards
static float calculate_damage(float attacker_dmg, float defender_armor)
{
	float damage = attacker_dmg - defender_armor;
	return damage > 1.0f ? damage : 1.0f; // Minimum 1 dégât
}

static void handle_debug_command(t_player *player, int *player_missing_health)
{
	float old_max_hp = player->total.health;
	float old_current_hp = player->total.health - *player_missing_health;

	player->base.health += 20;
	updateStats(player);

	float new_max_hp = player->total.health;
	float hp_difference = new_max_hp - old_max_hp;

	*player_missing_health -= hp_difference;
	if (*player_missing_health < 0) *player_missing_health = 0;

	printf(">> Boost de PV en plein combat!\n");
	printf("   PV max: %.0f -> %.0f (+%.0f)\n", old_max_hp, new_max_hp, hp_difference);
	printf("   PV actuels: %.0f -> %.0f\n", old_current_hp, new_max_hp - *player_missing_health);
	printf("   Vous ressentez une nouvelle vitalité!\n");
}

int execute_player_turn(t_player *player, t_enemy *enemy, int *enemy_missing_health, int *player_missing_health)
{
	printf("\n🎯 Tour de %s:\n", player->name);
	printf("╔═══════════════════════════════════════════════════════════════╗\n");
	printf("║                       Actions disponibles                     ║\n");
	printf("╚═══════════════════════════════════════════════════════════════╝\n");
	printf("🗡️  attack - Attaquer l'ennemi\n");
	printf("🏃 run - Fuir le combat\n");
	if (debug)
		printf("➕ add_max_hp - Ajouter 20 PV maximum (debug)\n");
	printf("────────────────────────────────────────────────────────────────\n");

	char *action = readline(PROMPT_FIGHT);
	if (!action) return 1; // Traiter NULL comme une fuite

	add_history(action);
	printf("\n");

	if (strcmp(action, "attack") == 0)
	{
		float raw_damage = player->total.physical_dmg;
		float armor = enemy->total.armor;
		float final_damage = calculate_damage(raw_damage, armor);
		*enemy_missing_health += final_damage;

		printf(">> %s attaque %s!\n", player->name, enemy->name);

		// Affichage détaillé des dégâts
		if (armor > 0 && raw_damage > armor)
		{
			printf("💥 %s subit %.0f dégâts ! (%.0f - %.0f armure)\n",
				   enemy->name, final_damage, raw_damage, armor);
		}
		else if (armor > 0)
		{
			printf("🛡️  L'armure absorbe la plupart des dégâts ! %s subit %.0f dégât minimum.\n",
				   enemy->name, final_damage);
		}
		else
		{
			printf("💥 %s subit %.0f dégâts !\n", enemy->name, final_damage);
		}
	}
	else if (strcmp(action, "run") == 0)
	{
		printf(">> %s s'enfuit du combat!\n", player->name);
		free(action);
		printf("\nPress ENTER to continue...");
		getchar();
		return 1;
	}
	else if (strcmp(action, "add_max_hp") == 0 && debug)
	{
		handle_debug_command(player, player_missing_health);
	}
	else
	{
		printf(">> Action inconnue : '%s'\n", action);
	}

	free(action);
	printf("\nPress ENTER to continue...");
	getchar();
	return 0;
}

void execute_enemy_turn(t_player *player, t_enemy *enemy, int *player_missing_health)
{
	printf("\n🤖 Tour de %s:\n", enemy->name);

	float raw_damage = enemy->total.physical_dmg;
	float armor = player->total.armor;
	float final_damage = calculate_damage(raw_damage, armor);
	*player_missing_health += final_damage;

	printf(">> %s attaque %s!\n", enemy->name, player->name);

	// Affichage détaillé des dégâts reçus
	if (armor > 0 && raw_damage > armor)
	{
		printf("💥 Vous subissez %.0f dégâts ! (%.0f - %.0f armure)\n",
			   final_damage, raw_damage, armor);
	}
	else if (armor > 0)
	{
		printf("🛡️  Votre armure absorbe la plupart des dégâts ! Vous subissez %.0f dégât minimum.\n",
			   final_damage);
	}
	else
	{
		printf("💥 Vous subissez %.0f dégâts !\n", final_damage);
	}

	printf("\nPress ENTER to continue...");
	getchar();
}

// ===== MAIN COMBAT LOOP =====

static int check_combat_end(t_player *player, t_enemy *enemy, float player_hp, float enemy_hp)
{
	if (player_hp <= 0)
	{
		printf("\n💀 %s s'effondre... Défaite!\n", player->name);
		printf("\nPress ENTER to continue...");
		getchar();
		return -1; // Défaite
	}
	if (enemy_hp <= 0)
	{
		printf("\n🏆 %s est vaincu! Victoire!\n", enemy->name);
		printf("\nPress ENTER to continue...");
		getchar();
		return 1; // Victoire
	}
	return 0; // Combat continue
}

int execute_combat(t_player *player, t_enemy *enemy, int who_has_initiative)
{
	int player_missing_health = 0;
	int enemy_missing_health = 0;
	int turn = 1;

	printf("\n💥 Le combat commence! %s gagne l'initiative.\n\n",
		   who_has_initiative ? player->name : enemy->name);

	while (1)
	{
		// Calculer les HP actuels
		float player_current_hp = player->total.health - player_missing_health;
		float enemy_current_hp = enemy->total.health - enemy_missing_health;

		// Vérifier la fin du combat
		int combat_result = check_combat_end(player, enemy, player_current_hp, enemy_current_hp);
		if (combat_result != 0)
			return (combat_result == 1) ? 1 : 0;

		// Exécuter les tours selon l'initiative
		if (who_has_initiative)
		{
			// JOUEUR A L'INITIATIVE : afficher d'abord, puis actions
			display_combat_header(turn);
			display_combatant_status(player->name, player->level, player_current_hp, player->total.health);
			display_combatant_status(enemy->name, enemy->level, enemy_current_hp, enemy->total.health);
			printf("\n");

			// Tour du joueur puis de l'ennemi
			if (execute_player_turn(player, enemy, &enemy_missing_health, &player_missing_health) == 1)
				return 0; // Fuite

			if (enemy->total.health - enemy_missing_health > 0)
				execute_enemy_turn(player, enemy, &player_missing_health);
		}
		else
		{
			// ENNEMI A L'INITIATIVE : ennemi attaque d'abord, puis affichage
			if (turn == 1)
			{
				// Premier tour : afficher l'état initial
				display_combat_header(turn);
				display_combatant_status(player->name, player->level, player_current_hp, player->total.health);
				display_combatant_status(enemy->name, enemy->level, enemy_current_hp, enemy->total.health);
				printf("\n");
			}

			// Tour de l'ennemi
			execute_enemy_turn(player, enemy, &player_missing_health);

			// Recalculer les HP après l'attaque de l'ennemi
			player_current_hp = player->total.health - player_missing_health;

			// Vérifier si le joueur est mort après l'attaque de l'ennemi
			combat_result = check_combat_end(player, enemy, player_current_hp, enemy_current_hp);
			if (combat_result != 0)
				return (combat_result == 1) ? 1 : 0;

			// Afficher l'état après l'attaque de l'ennemi
			display_combat_header(turn);
			display_combatant_status(player->name, player->level, player_current_hp, player->total.health);
			display_combatant_status(enemy->name, enemy->level, enemy_current_hp, enemy->total.health);
			printf("\n");

			// Tour du joueur
			if (execute_player_turn(player, enemy, &enemy_missing_health, &player_missing_health) == 1)
				return 0; // Fuite
		}

		turn++;
	}
}

int fight(t_player *player, t_enemy *enemy)
{
	updateStats(player);
	printf("%s entre en combat contre %s!\n", player->name, enemy->name);

	int who_has_initiative = calculate_initiative(player, enemy);
	return execute_combat(player, enemy, who_has_initiative);
}
