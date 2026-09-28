#include "estado.h"
#include "formatacao.h"
#include "geral.h"

#include <stdio.h>
#include <stdlib.h>

void limpar_buffer(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int ler_int(void) {
    int valor;

    if (scanf("%d", &valor) != 1) {
        if (feof(stdin)) {
            printf("\nEntrada encerrada. Fim de jogo.\n");
            exit(EXIT_SUCCESS);
        }
        limpar_buffer();
        return -1;
    }

    limpar_buffer();
    return valor;
}

int ler_opcao(int minimo, int maximo) {
    int opcao;

    do {
        opcao = ler_int();
        if (opcao < minimo || opcao > maximo) {
            printf("Opcao invalida! Digite um numero entre %d e %d: ", minimo, maximo);
        }
    } while (opcao < minimo || opcao > maximo);

    return opcao;
}

void texto_item(int item) {
    switch (item) {
        case 1: imprimir("1 - Facao --> 6 de dano\n"); break;
        case 2: imprimir("2 - Pistola com 6 municoes --> 10 de dano por municao\n"); break;
        case 3: imprimir("3 - Lanterna --> ilumina lugares escuros\n"); break;
        case 4: imprimir("4 - 2 Ataduras --> curam 15 de vida e param sangramento\n"); break;
        default: break;
    }
}

void dar_item(int item) {
    switch (item) {
        case 1: facao = 1; break;
        case 2:
            pistola = 1;
            municao = 6;
            break;
        case 3: lanterna = 1; break;
        case 4: ataduras = 2; break;
        default: break;
    }
}

void escolher_itens_iniciais(void) {
    int primeiro;
    int segundo;

    for (int item = 1; item <= 4; item++) {
        texto_item(item);
    }
    primeiro = ler_opcao(1, 4);
    dar_item(primeiro);

    imprimir("\nAgora escolha o seu segundo item:\n");
    for (int item = 1; item <= 4; item++) {
        if (item != primeiro) {
            texto_item(item);
        }
    }

    do {
        segundo = ler_opcao(1, 4);
        if (segundo == primeiro) {
            printf("Voce ja escolheu esse item! Escolha outro: ");
        }
    } while (segundo == primeiro);

    dar_item(segundo);
}

void mostrar_inventario(void) {
    char buffer[100];

    imprimir("\nInventario:\n");
    if (facao) imprimir("Facao --> 6 de dano\n");
    if (pistola) {
        snprintf(buffer, sizeof(buffer), "Pistola --> 10 de dano por municao (Municao: %d)\n", municao);
        imprimir(buffer);
    }
    if (lanterna) imprimir("Lanterna --> ilumina lugares escuros\n");
    if (ataduras > 0) {
        snprintf(buffer, sizeof(buffer), "%d Ataduras --> curam 15 de vida e param sangramento\n", ataduras);
        imprimir(buffer);
    }
    if (colar_forca) imprimir("Colar de Rubi --> +3 de dano\n");
    if (colar_hp) imprimir("Colar de Esmeralda --> +20 de HP maximo\n");
    if (anel) imprimir("Anel ensanguentado com um pequeno diamante\n");
    if (cetro) imprimir("Cetro de pedra valiosa\n");
    if (chave_simples) imprimir("Chave Simples\n");
}
