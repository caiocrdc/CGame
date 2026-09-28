#include "rpg.h"
#include "rpg_internal.h"

#include <stdlib.h>

int start_rpg(void)
{
    GameState game;

    initialize_game(&game);
    configure_text_speed(&game);
    read_player_name(&game);
    print_introduction(&game);
    choose_initial_items(&game);
    print_inventory(&game);

    game.rota = choose_initial_route(&game);
    switch (game.rota) {
        case ROTA_DIREITA:
            run_right_route(&game);
            break;
        case ROTA_ESQUERDA:
            run_left_route(&game);
            break;
    }

    if (game.player.vida > 0) {
        print_inventory(&game);
    }
    return EXIT_SUCCESS;
}
