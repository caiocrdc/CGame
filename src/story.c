#include "rpg_internal.h"

Route choose_initial_route(GameState *game)
{
    const MenuOption paths[] = {
        {ROTA_DIREITA, "Ir para a direita"},
        {ROTA_ESQUERDA, "Ir para a esquerda"}
    };
    int left_attempts = 0;

    print_text(
        game,
        "\nUsando o pequeno barco, voce chega a ilha e encontra uma "
        "bifurcacao. Os caminhos parecem levar ao mesmo lugar.\n");
    while (left_attempts < 2) {
        Route route = (Route)choose_menu(
            game, left_attempts == 0 ? "Qual caminho deseja seguir?\n"
                                    : "Escolha novamente:\n",
            paths, sizeof(paths) / sizeof(paths[0]));
        switch (route) {
            case ROTA_DIREITA:
                return ROTA_DIREITA;
            case ROTA_ESQUERDA:
                left_attempts++;
                if (left_attempts < 2) {
                    print_text(game,
                               "Depois de caminhar pela esquerda, voce "
                               "retorna a mesma bifurcacao.\n");
                }
                break;
        }
    }
    return ROTA_ESQUERDA;
}

static bool explore_left_entrance(GameState *game)
{
    MenuOption options[3] = {
        {1, "Aproximar-se para enxergar melhor"},
        {2, "Esperar o barulho parar"},
        {3, "Iluminar o local com a lanterna"}
    };
    size_t count = game->player.inventario.lanterna ? 3 : 2;

    print_text(
        game,
        "Apos horas pelo caminho esquerdo, voce encontra uma abertura nos "
        "fundos de uma estrutura escura e escuta pessoas falando uma lingua "
        "estranha.\n");
    switch (choose_menu(game, "O que deseja fazer?\n", options, count)) {
        case 1: {
            const MenuOption reactions[] = {
                {1, "Atacar"},
                {2, "Tentar conversar"}
            };
            print_text(game,
                       "Voce tropeca em uma raiz e alerta uma figura "
                       "encapuzada, que avanca em sua direcao.\n");
            return resolve_cultist_combat(
                game, choose_menu(game, "Como reagir?\n", reactions, 2) == 2);
        }
        case 2:
            print_text(game,
                       "Vinte minutos depois, as vozes param e voce entra "
                       "na estrutura em seguranca.\n");
            return true;
        case 3:
            print_text(game,
                       "A lanterna revela o interior, mas denuncia sua "
                       "posicao. Um cultista avanca com uma faca.\n");
            return resolve_cultist_combat(game, false);
    }
    return false;
}

static void follow_footprints(GameState *game)
{
    if (!game->cultista_eliminado) {
        const MenuOption attack[] = {{1, "Atacar a figura por tras"}};

        print_text(game,
                   "Seguindo as pegadas, voce encontra uma figura de costas "
                   "diante de um altar.\n");
        choose_menu(game, "Ha apenas uma oportunidade segura:\n", attack, 1);
        print_text(game,
                   "Voce neutraliza o cultista rapidamente e evita um "
                   "combate direto.\n");
        game->cultista_eliminado = true;
        collect_simple_key(game);
    }
    print_text(
        game,
        "Na parede esta escrito 'Ph'nglui mglw'nafh Cthulhu R'lyeh "
        "wgah'nagl fhtagn'. Sob a frase ha um anel ensanguentado. Voce o "
        "guarda e segue para a porta entreaberta.\n");
}

static void search_room_corners(GameState *game)
{
    print_text(game,
               "Nos cantos do salao, uma passagem esta bloqueada por "
               "raizes.\n");
    if (game->player.inventario.facao) {
        print_text(game,
                   "Com o facao, voce corta as raizes e encontra pedras "
                   "preciosas antes de voltar ao altar.\n");
    } else {
        print_text(game,
                   "Sem uma ferramenta apropriada, voce volta ao altar.\n");
    }
}

static void equip_health_necklace(GameState *game)
{
    Player *player = &game->player;

    if (!player->inventario.colar_hp) {
        player->inventario.colar_hp = true;
        player->vida_maxima += 20;
        player->vida += 20;
    }
    print_text(game,
               "A caixa contem um colar de esmeralda. Ao coloca-lo, sua "
               "vida maxima aumenta em 20.\n");
}

static void explore_altar(GameState *game)
{
    MenuOption options[3];
    size_t count = 0;
    int choice;

    print_text(game,
               "\nNo altar, voce encontra um cetro valioso, uma caixa com "
               "cadeado e uma chave verde.\n");
    game->player.inventario.chave_verde = true;
    options[count++] = (MenuOption){1, "Sair e testar a chave verde"};
    if (game->player.inventario.facao) {
        options[count++] = (MenuOption){2, "Forcar a caixa com o facao"};
    }
    if (game->player.inventario.chave_simples) {
        options[count++] = (MenuOption){3, "Abrir a caixa com a chave simples"};
    }
    choice = choose_menu(game, "O que deseja fazer?\n", options, count);
    if (choice == 2 || choice == 3) {
        equip_health_necklace(game);
    }
}

static bool leave_great_hall(GameState *game)
{
    if (game->cultista_eliminado) {
        return true;
    }
    print_text(game,
               "Ao sair do salao, voce e emboscado pelo cultista que ainda "
               "rondava o templo.\n");
    return resolve_cultist_combat(game, false);
}

static void run_tentacle_ending(GameState *game)
{
    const MenuOption options[] = {
        {1, "Entrar na sala e enfrentar o monstro"},
        {2, "Fugir do templo com os tesouros encontrados"}
    };

    print_text(game,
               "\nA chave verde abre a porta ornamental. Dentro da sala ha "
               "um enorme diamante, mas um tentaculo maior que um homem se "
               "move pelas paredes.\n");
    switch (choose_menu(game, "Qual sera sua decisao?\n", options, 2)) {
        case 1: {
            Enemy tentacle = {"Tentaculo ancestral", 36, 7, true};
            if (fight(game, tentacle, false) == COMBATE_DERROTA) {
                print_bad_ending(
                    game,
                    "O tentaculo arremessa seu corpo para fora e fecha a "
                    "porta, esperando a proxima vitima.");
                return;
            }
            print_text(game, "\n===== FINAL BOM =====\n");
            print_text(game,
                       "Voce conquista o diamante, foge da ilha e paga toda "
                       "a divida, vivendo com conforto por muitos anos.\n");
            break;
        }
        case 2:
            print_text(game, "\n===== FINAL NEUTRO =====\n");
            print_text(game,
                       "Os tesouros pagam parte da divida. Voce escapa com "
                       "vida, mas ainda trabalhara por anos para quitar o "
                       "restante.\n");
            break;
    }
    game->jogo_encerrado = true;
}

static void run_creature_ending(GameState *game)
{
    Enemy creature = {"Criatura do altar", 40, 8, true};

    print_text(game,
               "\nA chave verde abre a porta ornamental. Um diamante enorme "
               "repousa diante de uma figura ajoelhada. A criatura vira o "
               "pescoco, encontra seu olhar e ataca.\n");
    if (fight(game, creature, false) == COMBATE_DERROTA) {
        print_bad_ending(game,
                         "Voce e devorado ainda vivo pela criatura. Eu sei "
                         "que voce vai voltar.");
        return;
    }
    print_text(game, "\n===== FINAL BOM =====\n");
    print_format(game,
                 "%s conquista o diamante, foge da ilha e paga toda a "
                 "divida, vivendo com conforto por muitos anos.\n",
                 game->player.nome);
    game->jogo_encerrado = true;
}

static void explore_great_hall(GameState *game, FinalEncounter encounter)
{
    const MenuOption places[] = {
        {1, "Procurar algo no altar"},
        {2, "Procurar nos cantos da sala"}
    };

    print_text(game,
               "\nA porta entreaberta leva a um grande salao semelhante a "
               "uma igreja. A luz da lua revela um altar e pilares com "
               "cabecas de barbas em forma de tentaculos.\n");
    if (choose_menu(game, "Onde deseja procurar?\n", places, 2) == 2) {
        search_room_corners(game);
    }
    explore_altar(game);
    if (!leave_great_hall(game) || game->jogo_encerrado) {
        return;
    }

    switch (encounter) {
        case FINAL_TENTACULO:
            run_tentacle_ending(game);
            break;
        case FINAL_CRIATURA:
            run_creature_ending(game);
            break;
    }
}

void run_left_route(GameState *game)
{
    const MenuOption paths[] = {
        {1, "Seguir as pegadas"},
        {2, "Entrar pela porta entreaberta"}
    };

    if (!explore_left_entrance(game) || game->jogo_encerrado) {
        return;
    }
    print_text(game,
               "\nDentro da estrutura, voce encontra duas barras de ouro. "
               "Pegadas levam a uma sala iluminada; perto dali ha uma porta "
               "entreaberta e outra porta com fechadura verde.\n");
    if (choose_menu(game, "Qual caminho deseja seguir?\n", paths, 2) == 1) {
        follow_footprints(game);
    }
    explore_great_hall(game, FINAL_TENTACULO);
}

static void equip_strength_necklace(GameState *game)
{
    if (!game->player.inventario.colar_forca) {
        game->player.inventario.colar_forca = true;
        print_text(game,
                   "A lanterna revela moedas e um colar de rubi. Ao "
                   "coloca-lo, seu dano aumenta em 3.\n");
    }
}

static void inspect_temple_entrance(GameState *game)
{
    print_text(game,
               "Na entrada, voce le 'Templo do nosso senhor Cthulhu', ve "
               "tentaculos esculpidos e encontra duas barras de ouro.\n");
    if (game->player.inventario.lanterna) {
        equip_strength_necklace(game);
    }
}

static bool explore_shining_chamber(GameState *game)
{
    MenuOption options[3] = {
        {1, "Ir diretamente na direcao do brilho"},
        {2, "Nao arriscar e continuar explorando"},
        {3, "Usar a lanterna para procurar armadilhas"}
    };
    size_t count = game->player.inventario.lanterna ? 3 : 2;

    print_text(game,
               "\nNos corredores escuros, algo brilhando em uma camara "
               "chama sua atencao. Pode ser outra barra de ouro.\n");
    switch (choose_menu(game, "O que deseja fazer?\n", options, count)) {
        case 1: {
            Enemy cultist = {"Cultista encapuzado", 24, 6, true};
            CombatResult result;

            print_text(game,
                       "Voce bate em ossos pendurados e atrai um cultista.\n");
            result = fight(game, cultist, true);
            if (result == COMBATE_DERROTA) {
                print_bad_ending(game,
                                 "O cultista vence e oferece seu corpo como "
                                 "sacrificio.");
                return false;
            }
            if (result == COMBATE_VITORIA) {
                game->cultista_eliminado = true;
                collect_simple_key(game);
            }
            break;
        }
        case 2:
            print_text(game,
                       "Voce prefere nao arriscar e continua explorando.\n");
            break;
        case 3:
            print_text(game,
                       "A lanterna revela ossos pendurados. Voce evita a "
                       "armadilha, recolhe a barra de ouro e sai em silencio.\n");
            break;
    }
    return true;
}

void run_right_route(GameState *game)
{
    const MenuOption entrance[] = {
        {1, "Analisar a entrada do templo"},
        {2, "Entrar imediatamente no templo"}
    };

    print_text(game,
               "Seguindo pela direita, voce encontra um templo antigo que "
               "parece abandonado ha muito tempo.\n");
    if (choose_menu(game, "O que deseja fazer?\n", entrance, 2) == 1) {
        inspect_temple_entrance(game);
    }
    if (!explore_shining_chamber(game) || game->jogo_encerrado) {
        return;
    }
    print_text(game,
               "Mais adiante, uma porta ornamental trancada parece exigir "
               "uma chave especial. Depois, voce chega a um grande salao.\n");
    explore_great_hall(game, FINAL_CRIATURA);
}
