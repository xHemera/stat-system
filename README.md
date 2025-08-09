# 🎮 RPG Combat System

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)](https://www.linux.org/)

Un système de combat RPG complet développé en C avec interface en ligne de commande, featuring un système d'initiative avancé, un système d'armure réaliste et une architecture modulaire.

## 📋 Table des matières

- [✨ Fonctionnalités](#-fonctionnalités)
- [🛠️ Installation](#️-installation)
- [🎯 Utilisation](#-utilisation)
- [⚔️ Système de combat](#️-système-de-combat)
- [📊 Système de stats](#-système-de-stats)
- [🎮 Commandes disponibles](#-commandes-disponibles)
- [🏗️ Architecture](#️-architecture)
- [🧪 Mode debug](#-mode-debug)
- [📁 Structure du projet](#-structure-du-projet)
- [🤝 Contribution](#-contribution)

## ✨ Fonctionnalités

### 🎯 **Système de combat avancé**
- **Initiative basée sur les niveaux** : Différence de ±5 niveaux = avantage automatique
- **Tirage pondéré par l'énergie** : Plus d'énergie = plus de chances de jouer en premier
- **Ordre d'affichage intelligent** : Les PV sont affichés au bon moment selon l'initiative
- **Système d'armure réaliste** : Réduction directe des dégâts avec minimum de 1 dégât

### 🛡️ **Mécaniques de jeu**
- **Pénétration d'armure** : Support pour contourner les défenses
- **Dégâts physiques et magiques** : Systèmes séparés avec leurs propres armures
- **Vampirisme et régénération** : Mécaniques de survie avancées
- **Scaling par niveau** : Progression équilibrée des statistiques

### 🎨 **Interface utilisateur**
- **Barres de vie dynamiques** : Unicode blocks avec couleurs progressives
- **Headers ASCII professionnels** : Affichage de combat immersif
- **Système de prompts adaptatif** : Différents styles selon le contexte
- **Messages détaillés** : Calculs de dégâts transparents

### 🏗️ **Architecture technique**
- **Système de commandes modulaire** : Pointeurs de fonction pour extensibilité
- **Gestion mémoire sécurisée** : Protection contre les buffer overflows
- **Parser robuste** : Chargement d'ennemis depuis fichiers avec validation
- **Code optimisé** : Performance et maintenabilité

## 🛠️ Installation

### Prérequis
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libreadline-dev

# Fedora/CentOS
sudo dnf install gcc readline-devel

# Arch Linux
sudo pacman -S gcc readline
```

### Compilation
```bash
git clone https://github.com/xHemera/stat-system.git
cd stat-system
make
```

### Nettoyage
```bash
make clean    # Supprime les fichiers objets
make fclean   # Nettoyage complet
make re       # Recompilation complète
```

## 🎯 Utilisation

### Lancement du jeu
```bash
./stat-system
```

### Premier démarrage
1. **Entrez votre nom** (lettres uniquement, max 19 caractères)
2. **Explorez les commandes** avec `help`
3. **Activez le debug** avec `/debug` pour plus d'options
4. **Commencez à combattre** avec `fight`

### Exemple de session
```
Entrez un nom de joueur :
> Aragorn
Bienvenue Aragorn!

Simple RPG combat management
> help
> /debug
[DEBUG] Mode debug activé.
> stats
> enemies
> fight goblin
```

## ⚔️ Système de combat

### Initiative
Le système d'initiative détermine qui attaque en premier :

```
Différence de niveau = Niveau joueur - Niveau ennemi

Si différence ≤ -5  → Ennemi a l'initiative automatiquement
Si différence ≥ +5  → Joueur a l'initiative automatiquement
Sinon              → Tirage aléatoire pondéré par l'énergie
```

### Calcul des dégâts
```
Dégâts physiques = max(1, Attaque physique - Armure)
Dégâts magiques  = max(1, Attaque magique - Armure magique)

Avec pénétration :
Armure effective = max(0, Armure - Pénétration)
```

### Exemple de combat
```
🎲 Test d'initiative:
   Aragorn (Niveau 5) vs Orc (Niveau 3)
   Différence de niveau: +2
   Calcul d'initiative basé sur l'énergie...
   Aragorn énergie: 20
   Orc énergie: 20
   Aragorn gagne l'initiative! (tirage: 15/40)

╔═══════════════════════════════════════════════════════════════╗
║                        COMBAT - Tour 1                        ║
╚═══════════════════════════════════════════════════════════════╝

Aragorn (Niveau 5)
❤️   500/500 [████████████████████] 100%
Orc (Niveau 3)
❤️   360/360 [████████████████████] 100%

🎯 Tour de Aragorn:
╔═══════════════════════════════════════════════════════════════╗
║                       Actions disponibles                     ║
╚═══════════════════════════════════════════════════════════════╝
🗡️  attack - Attaquer l'ennemi
🏃 run - Fuir le combat
```

## 📊 Système de stats

### Stats de base
| Stat | Description | Scaling |
|------|-------------|---------|
| **Health** | Points de vie | × Niveau |
| **Physical Dmg** | Dégâts physiques | × Niveau |
| **Armor** | Réduction dégâts physiques | × Niveau |
| **Magical Dmg** | Dégâts magiques | × Niveau |
| **Magic Armor** | Réduction dégâts magiques | × Niveau |
| **Energy** | Ressource pour actions spéciales | + Base |
| **Vampirism** | Vol de vie en % | × Niveau |

### Formules de calcul
```c
Stat totale = (Stat de base × Niveau) + Bonus d'équipement
Énergie     = Stat de base + Bonus d'équipement
```

## 🎮 Commandes disponibles

### Commandes générales
| Commande | Description |
|----------|-------------|
| `help` | Affiche l'aide complète |
| `stats` | Affiche vos statistiques |
| `fight [cible]` | Combat contre un ennemi |
| `enemies` | Liste tous les ennemis |
| `exit` / `quit` | Quitte le jeu |

### Paramètres de combat
```bash
fight                 # Menu interactif
fight goblin         # Combat par nom
fight 1              # Combat par index
fight random         # Ennemi aléatoire
```

### Commandes debug
| Commande | Description |
|----------|-------------|
| `levelup` / `lvl` | Monte d'un niveau |
| `add_max_hp` | +20 PV max (en combat) |

### Commandes système
| Commande | Description |
|----------|-------------|
| `/debug` | Active/désactive le mode debug |

## 🏗️ Architecture

### Organisation modulaire
```
src/
├── core/           # Logique principale
│   ├── commands.c  # Système de commandes
│   └── loop.c      # Boucle principale
├── entities/       # Gestion des entités
│   ├── player.c    # Joueur et stats
│   └── enemy.c     # Ennemis et chargement
├── fight/          # Système de combat
│   ├── fight.c     # Logique de combat
│   └── fight_utils.c # Utilitaires combat
└── utils/          # Fonctions utilitaires
    ├── utils.c     # Fonctions générales
    ├── debug.c     # Mode debug
    └── print_stats.c # Affichage stats
```

### Structures principales
```c
typedef struct s_stats {
    float health, physical_dmg, armor;
    float magical_dmg, magic_armor;
    float vampirism, heal_shield_power;
    int energy, energy_regen;
} t_stats;

typedef struct s_player {
    char name[MAX_NAME_LENGTH];
    int level;
    t_stats base, bonus, total;
} t_player;

typedef struct s_command {
    char *name;
    int (*handler)(t_player*, t_enemy*, int, char*);
    int admin_only;
    char *description;
} t_command;
```

## 🧪 Mode debug

Activez le mode debug avec `/debug` pour accéder à :

### Affichage avancé
```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│              SUPER STATS de Aragorn      (Niveau 5)             │
│───────────────────────────────────────────────────────────────────────────│
│   Health            │ Total:    500.0 │ Base:    500.0 │ Bonus:      0.0 │
│   Physical Dmg      │ Total:     50.0 │ Base:     50.0 │ Bonus:      0.0 │
│   Armor             │ Total:     50.0 │ Base:     50.0 │ Bonus:      0.0 │
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Commandes supplémentaires
- **levelup** : Montée de niveau instantanée
- **add_max_hp** : Boost de PV en plein combat
- **Détails combat** : Calculs d'initiative détaillés

## 📁 Structure du projet

```
stat-system/
├── README.md
├── Makefile
├── .gitignore
├── include/
│   └── hemera.h        # Header principal
├── src/
│   ├── core/           # Cœur du système
│   ├── entities/       # Gestion joueur/ennemis
│   ├── fight/          # Système de combat
│   └── utils/          # Utilitaires
├── data/
│   └── enemies         # Base de données ennemis
└── obj/                # Fichiers objets (généré)
```

### Format des ennemis
Le fichier `data/enemies` utilise le format pipe-separated :
```
# Nom|Niveau|HP|HealPwr|Vamp|MagDmg|MagArmor|MagPen|PhysDmg|Armor|ArmorPen|Energy|EnergyRegen|XP|Gold
Goblin|1|50|1|0|0|5|0|8|4|0|10|1|10|5
Orc|3|120|1|0|5|15|0|15|8|0|20|2|50|25
```

## 🚀 Fonctionnalités avancées

### Système de pénétration
```c
float calculate_physical_damage(float attack, float armor, float armor_pen) {
    float effective_armor = armor - armor_pen;
    if (effective_armor < 0) effective_armor = 0;
    
    float damage = attack - effective_armor;
    return damage > 1.0f ? damage : 1.0f; // Minimum 1 dégât
}
```

### Gestion des signaux
- **Ctrl+C** : Affiche un message mais ne quitte pas
- **Ctrl+D** : Sortie propre avec nettoyage mémoire

### Optimisations
- **Gestion mémoire** : Protection buffer overflow avec `strncpy`
- **Performance** : Boucles optimisées et structures efficaces
- **Validation** : Parsing robuste avec nettoyage des données
- **Extensibilité** : Architecture modulaire pour ajouts futurs

## 🤝 Contribution

### Pour contribuer
1. **Fork** le repository
2. **Créez** une branche feature (`git checkout -b feature/amazing-feature`)
3. **Committez** vos changements (`git commit -m 'Add amazing feature'`)
4. **Push** vers la branche (`git push origin feature/amazing-feature`)
5. **Ouvrez** une Pull Request

### Standards de code
- **Style** : Code en anglais, commentaires en français
- **Naming** : `snake_case` pour fonctions, `t_` pour types
- **Sécurité** : Toujours valider les entrées utilisateur
- **Memory** : Libérer toute mémoire allouée

### TODO
- [ ] Système d'expérience et de progression
- [ ] Équipements et inventaire
- [ ] Sauvegarde/chargement de parties
- [ ] Plus de types d'attaques spéciales
- [ ] Interface graphique simple

---

**Développé avec ❤️ en C**

*Un projet éducatif démontrant les concepts avancés de programmation système, la gestion mémoire et l'architecture logicielle.*
