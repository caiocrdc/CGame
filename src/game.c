#include "rpg_internal.h"

#include <string.h>

void initialize_game(GameState *game)
{
    memset(game, 0, sizeof(*game));
    game->player.vida_maxima = 100;
    game->player.vida = game->player.vida_maxima;
    game->player.dano_base = 4;
}

void print_introduction(const GameState *game)
{
    print_format(
        game,
        "\nVoce e %s, um(a) explorador(a) que precisa desesperadamente de "
        "dinheiro para pagar uma divida. Boatos dizem que uma ilha proxima "
        "guarda tesouros capazes de quita-la. Depois de comprar um pequeno "
        "barco, seu dinheiro permite levar apenas dois itens.\n\n",
        game->player.nome);
}

static bool has_item(const Inventory *inventory, ItemType item)
{
    switch (item) {
        case ITEM_FACAO:
            return inventory->facao;
        case ITEM_PISTOLA:
            return inventory->pistola;
        case ITEM_LANTERNA:
            return inventory->lanterna;
        case ITEM_ATADURAS:
            return inventory->ataduras > 0;
    }
    return false;
}

static void add_item(Inventory *inventory, ItemType item)
{
    switch (item) {
        case ITEM_FACAO:
            inventory->facao = true;
            break;
        case ITEM_PISTOLA:
            inventory->pistola = true;
            inventory->municao = 6;
            break;
        case ITEM_LANTERNA:
            inventory->lanterna = true;
            break;
        case ITEM_ATADURAS:
            inventory->ataduras = 2;
            break;
    }
}

static const char *item_description(ItemType item)
{
    switch (item) {
        case ITEM_FACAO:
            return "Facao (+6 de dano corpo a corpo)";
        case ITEM_PISTOLA:
            return "Pistola (6 municoes, 10 de dano)";
        case ITEM_LANTERNA:
            return "Lanterna (revela caminhos e armadilhas)";
        case ITEM_ATADURAS:
            return "2 ataduras (curam 25 de vida e param sangramento)";
    }
    return "Item desconhecido";
}

void choose_initial_items(GameState *game)
{
    int selected = 0;

    while (selected < 2) {
        MenuOption options[4];
        size_t count = 0;
        ItemType item;
        int candidate;

        for (candidate = ITEM_FACAO; candidate <= ITEM_ATADURAS; candidate++) {
            item = (ItemType)candidate;
            if (!has_item(&game->player.inventario, item)) {
                options[count].valor = candidate;
                options[count].texto = item_description(item);
                count++;
            }
        }

        item = (ItemType)choose_menu(
            game, selected == 0 ? "Escolha o primeiro item:\n"
                                : "\nEscolha o segundo item:\n",
            options, count);
        add_item(&game->player.inventario, item);
        selected++;
    }
}

void print_inventory(const GameState *game)
{
    const Inventory *inventory = &game->player.inventario;

    print_format(game, "\n%s - vida: %d/%d\n", game->player.nome,
                 game->player.vida, game->player.vida_maxima);
    print_text(game, "Inventario:\n");
    if (inventory->facao) {
        print_text(game, "- Facao\n");
    }
    if (inventory->pistola) {
        print_format(game, "- Pistola (%d municoes)\n", inventory->municao);
    }
    if (inventory->lanterna) {
        print_text(game, "- Lanterna\n");
    }
    if (inventory->ataduras > 0) {
        print_format(game, "- Ataduras: %d\n", inventory->ataduras);
    }
    if (inventory->colar_forca) {
        print_text(game, "- Colar de forca (+3 de dano)\n");
    }
    if (inventory->colar_hp) {
        print_text(game, "- Colar de protecao (+20 de vida maxima)\n");
    }
    if (inventory->chave_simples) {
        print_text(game, "- Chave simples\n");
    }
    if (inventory->chave_verde) {
        print_text(game, "- Chave verde\n");
    }
}

static int player_strength_bonus(const Player *player)
{
    return player->inventario.colar_forca ? 3 : 0;
}

static void use_bandage(GameState *game)
{
    Player *player = &game->player;
    int previous_health = player->vida;

    player->inventario.ataduras--;
    player->vida += 25;
    if (player->vida > player->vida_maxima) {
        player->vida = player->vida_maxima;
    }
    player->sangrando = false;
    print_format(game, "Voce recuperou %d de vida e parou o sangramento.\n",
                 player->vida - previous_health);
}

CombatResult fight(GameState *game, Enemy enemy, bool can_flee)
{
    Player *player = &game->player;
    int round = 1;

    print_format(game, "\n===== COMBATE: %s =====\n", enemy.nome);
    while (player->vida > 0 && enemy.vida > 0) {
        MenuOption actions[4];
        size_t count = 0;
        int action;
        int damage = 0;

        print_format(game, "\n%s: %d/%d de vida | %s: %d de vida\n",
                     player->nome, player->vida, player->vida_maxima,
                     enemy.nome, enemy.vida);
        if (player->sangrando) {
            print_text(game, "Status: sangrando (-5 de vida por turno)\n");
        }

        actions[count++] = (MenuOption){
            1, player->inventario.facao ? "Atacar com o facao"
                                        : "Atacar sem arma"};
        if (player->inventario.pistola && player->inventario.municao > 0) {
            actions[count++] = (MenuOption){2, "Atirar com a pistola"};
        }
        if (player->inventario.ataduras > 0) {
            actions[count++] = (MenuOption){3, "Usar uma atadura"};
        }
        if (can_flee) {
            actions[count++] = (MenuOption){4, "Fugir"};
        }

        action = choose_menu(game, "Escolha sua acao:\n", actions, count);
        switch (action) {
            case 1:
                damage = player->dano_base + player_strength_bonus(player);
                if (player->inventario.facao) {
                    damage += 6;
                }
                print_format(game, "Voce causa %d de dano.\n", damage);
                enemy.vida -= damage;
                break;
            case 2:
                player->inventario.municao--;
                damage = 10 + player_strength_bonus(player);
                print_format(game,
                             "O disparo causa %d de dano. Restam %d municoes.\n",
                             damage, player->inventario.municao);
                enemy.vida -= damage;
                break;
            case 3:
                use_bandage(game);
                break;
            case 4:
                print_text(game, "Voce consegue fugir do combate.\n");
                return COMBATE_FUGA;
        }

        if (player->sangrando) {
            player->vida -= 5;
            print_text(game, "O sangramento causa 5 de dano.\n");
        }
        if (player->vida <= 0) {
            return COMBATE_DERROTA;
        }
        if (enemy.vida <= 0) {
            player->combates_vencidos++;
            print_format(game, "Voce derrotou %s.\n", enemy.nome);
            return COMBATE_VITORIA;
        }

        player->vida -= enemy.dano;
        print_format(game, "%s causa %d de dano em voce.\n", enemy.nome,
                     enemy.dano);
        if (enemy.causa_sangramento && round % 2 == 0 && !player->sangrando) {
            player->sangrando = true;
            print_text(game, "O golpe abriu uma ferida: voce esta sangrando.\n");
        }
        round++;
    }

    return player->vida > 0 ? COMBATE_VITORIA : COMBATE_DERROTA;
}

void print_bad_ending(GameState *game, const char *message)
{
    print_text(game, "\n===== FINAL RUIM =====\n");
    print_text(game, message);
    print_text(game, "\n");
    game->jogo_encerrado = true;
}

void collect_simple_key(GameState *game)
{
    print_text(
        game,
        "Entre os pertences do cultista, uma chave simples chama sua "
        "atencao. Ela provavelmente abre algo importante.\n");
    game->player.inventario.chave_simples = true;
}

bool resolve_cultist_combat(GameState *game, bool surprised)
{
    Enemy cultist = {"Cultista encapuzado", 24, 6, true};
    CombatResult result;

    if (surprised) {
        game->player.sangrando = true;
        print_text(game, "A figura te esfaqueia. Voce comeca sangrando.\n");
    }
    result = fight(game, cultist, true);
    switch (result) {
        case COMBATE_VITORIA:
            game->cultista_eliminado = true;
            collect_simple_key(game);
            return true;
        case COMBATE_FUGA:
            print_text(game,
                       "Voce escapa, mas o cultista continua em algum lugar "
                       "do templo.\n");
            return true;
        case COMBATE_DERROTA:
            print_bad_ending(
                game,
                "A figura encapuzada vence e usa voce como sacrificio para "
                "o deus maligno que ela cultua.");
            return false;
    }
    return false;
}
