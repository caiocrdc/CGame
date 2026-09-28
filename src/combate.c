#include "combate.h"
#include "estado.h"
#include "formatacao.h"
#include "geral.h"

#include <stdio.h>

int func_combate(const char *nome_inimigo, int hp_inimigo, int dano_inimigo) {
    const int hp_inicial_inimigo = hp_inimigo;
    const int bonus_dano = colar_forca ? 3 : 0;

    if (colar_hp && hp_maximo < 60) {
        hp_maximo = 60;
        if (hp_jogador == 40) {
            hp_jogador = hp_maximo;
        }
    }

    mudar_cor(15);
    imprimir("\n==================================\n");
    imprimir("        COMBATE INICIADO!         \n");
    printf("Inimigo: ");
    mudar_cor(12);
    printf("%s", nome_inimigo);
    mudar_cor(15);
    printf(" | HP: %d | Dano: %d\n", hp_inimigo, dano_inimigo);
    imprimir("==================================\n");

    while (hp_jogador > 0 && hp_inimigo > 0) {
        if (sangramento) {
            mudar_cor(12);
            imprimir("\n[STATUS] Voce esta sangrando! Perdeu 5 de HP.\n");
            mudar_cor(15);
            hp_jogador -= 5;
            if (hp_jogador <= 0) break;
        }

        printf("\nSeu HP: %d/%d | HP Inimigo: %d\n", hp_jogador, hp_maximo, hp_inimigo);
        printf("Sua vez, %s. Escolha uma acao:\n", nome_jogador);
        imprimir("1 - Atacar\n");
        printf("2 - Usar Atadura (Cura 15 HP e para o sangramento) [%d restantes]\n", ataduras);

        switch (ler_opcao(1, 2)) {
            case 1: {
                int dano_causado = 2 + bonus_dano;
                int max_arma = 1;
                int arma;

                imprimir("Com qual arma?\n");
                printf("1 - Soco (Dano: %d)\n", 2 + bonus_dano);
                if (facao) printf("%d - Facao (Dano: %d)\n", ++max_arma, 6 + bonus_dano);
                if (pistola) {
                    ++max_arma;
                    printf("%d - Pistola (Dano: %d | Municao: %d)\n", max_arma, 10 + bonus_dano, municao);
                }
                arma = ler_opcao(1, max_arma);

                if (arma == 2 && facao) {
                    dano_causado = 6 + bonus_dano;
                } else if (arma == (facao ? 3 : 2) && pistola) {
                    if (municao > 0) {
                        dano_causado = 10 + bonus_dano;
                        municao--;
                    } else {
                        imprimir("A arma apenas faz um barulho de *click*. Sem municao! Voce deu um soco de desespero.\n");
                    }
                }

                printf("\n> Voce atacou causando %d de dano!\n", dano_causado);
                hp_inimigo -= dano_causado;
                break;
            }
            case 2:
                if (ataduras > 0) {
                    imprimir("\n> Voce rapidamente enfaixou seus machucados! (+15 HP)\n");
                    ataduras--;
                    hp_jogador += 15;
                    sangramento = 0;
                    if (hp_jogador > hp_maximo) hp_jogador = hp_maximo;
                } else {
                    imprimir("\n> Voce procura na bolsa, mas nao tem ataduras! Voce perdeu seu turno...\n");
                }
                break;
            default:
                imprimir("\n> Opcao invalida! Na confusao da batalha, voce tropecou e perdeu o turno.\n");
        }

        if (hp_inimigo > 0) {
            printf("> O ");
            mudar_cor(12);
            printf("%s", nome_inimigo);
            mudar_cor(15);
            printf(" te ataca, causando %d de dano!\n", dano_inimigo);
            hp_jogador -= dano_inimigo;
        }
    }

    if (hp_jogador <= 0) {
        hp_jogador = 0;
        mudar_cor(14);
        imprimir("\nSua visao escurece e voce cai no chao...\n");
        mudar_cor(15);
        return 0;
    }

    printf("\nO %s cai sem vida! Voce sobreviveu.\n", nome_inimigo);
    pontuacao += hp_inicial_inimigo * 2;
    return 1;
}

int luta_cultista(void) {
    vitoria = func_combate("Cultista Encapuzado", 15, 6);

    if (!vitoria) {
        mudar_cor(12);
        imprimir("\n=====FINAL RUIM=====\n");
        imprimir("A figura encapuzada ganha de voce e o usa como sacrificio para o Deus maligno que ela cultua.\n");
        mudar_cor(15);
        return 0;
    }

    mudar_cor(14);
    imprimir("Analisando o corpo da figura, uma chave chama sua atencao; ela provavelmente deve abrir algo importante.\n");
    mudar_cor(15);
    chave_simples = 1;
    combate = 1;
    return 1;
}
