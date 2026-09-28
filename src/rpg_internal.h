#ifndef RPG_INTERNAL_H
#define RPG_INTERNAL_H

#include <stdbool.h>
#include <stddef.h>

#define PLAYER_NAME_SIZE 50

typedef enum {
    ITEM_FACAO = 1,
    ITEM_PISTOLA,
    ITEM_LANTERNA,
    ITEM_ATADURAS
} ItemType;

typedef enum { ROTA_DIREITA = 1, ROTA_ESQUERDA } Route;
typedef enum { COMBATE_VITORIA, COMBATE_DERROTA, COMBATE_FUGA } CombatResult;
typedef enum { FINAL_CRIATURA, FINAL_TENTACULO } FinalEncounter;

typedef struct {
    bool facao;
    bool pistola;
    bool lanterna;
    bool chave_simples;
    bool chave_verde;
    bool colar_forca;
    bool colar_hp;
    int municao;
    int ataduras;
} Inventory;

typedef struct {
    char nome[PLAYER_NAME_SIZE];
    int vida;
    int vida_maxima;
    int dano_base;
    bool sangrando;
    int combates_vencidos;
    Inventory inventario;
} Player;

typedef struct {
    const char *nome;
    int vida;
    int dano;
    bool causa_sangramento;
} Enemy;

typedef struct {
    int valor;
    const char *texto;
} MenuOption;

typedef struct {
    Player player;
    Route rota;
    bool cultista_eliminado;
    bool jogo_encerrado;
    unsigned int atraso_texto_us;
} GameState;

/* platform.c */
void print_text(const GameState *game, const char *text);
void print_format(const GameState *game, const char *format, ...);
int choose_menu(const GameState *game, const char *title,
                const MenuOption options[], size_t option_count);
void configure_text_speed(GameState *game);
void read_player_name(GameState *game);

/* game.c */
void initialize_game(GameState *game);
void print_introduction(const GameState *game);
void choose_initial_items(GameState *game);
void print_inventory(const GameState *game);
CombatResult fight(GameState *game, Enemy enemy, bool can_flee);
void print_bad_ending(GameState *game, const char *message);
void collect_simple_key(GameState *game);
bool resolve_cultist_combat(GameState *game, bool surprised);

/* story.c */
Route choose_initial_route(GameState *game);
void run_left_route(GameState *game);
void run_right_route(GameState *game);

#endif
