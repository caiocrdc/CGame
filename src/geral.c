#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif

#include "estado.h"
#include "formatacao.h"
#include "geral.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#include <io.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

enum { TECLA_ENTER = 13, TECLA_CIMA = 1000, TECLA_BAIXO };

static int terminal_interativo(void) {
#ifdef _WIN32
    return _isatty(_fileno(stdin));
#else
    return isatty(STDIN_FILENO);
#endif
}

static int ler_tecla(void) {
#ifdef _WIN32
    int tecla = _getch();
    if (tecla == 0 || tecla == 224) {
        tecla = _getch();
        if (tecla == 72) return TECLA_CIMA;
        if (tecla == 80) return TECLA_BAIXO;
        return 0;
    }
    return tecla == '\r' ? TECLA_ENTER : tecla;
#else
    struct termios modo_original;
    if (tcgetattr(STDIN_FILENO, &modo_original) != 0) return getchar();

    struct termios modo_raw = modo_original;
    modo_raw.c_lflag &= (tcflag_t)~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &modo_raw) != 0) return getchar();

    int tecla = getchar();
    if (tecla == '\033') {
        int inicio_sequencia = getchar();
        tecla = inicio_sequencia == '[' ? getchar() : 0;
        if (tecla == 'A') tecla = TECLA_CIMA;
        else if (tecla == 'B') tecla = TECLA_BAIXO;
        else tecla = 0;
    } else if (tecla == '\n' || tecla == '\r') {
        tecla = TECLA_ENTER;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &modo_original);
    return tecla;
#endif
}

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
    if (minimo > maximo) return minimo;

    mudar_cor(15);
    if (terminal_interativo()) {
        int opcao = minimo;
        int tecla;

        printf("Use as setas e Enter. Opcao: %d", opcao);
        fflush(stdout);
        while ((tecla = ler_tecla()) != TECLA_ENTER) {
            if (tecla == TECLA_CIMA) {
                opcao = opcao == minimo ? maximo : opcao - 1;
            } else if (tecla == TECLA_BAIXO) {
                opcao = opcao == maximo ? minimo : opcao + 1;
            } else {
                continue;
            }
            printf("\r\033[KUse as setas e Enter. Opcao: %d", opcao);
            fflush(stdout);
        }
        putchar('\n');
        limpar_terminal();
        mudar_cor(14);
        return opcao;
    }

    int opcao;
    do {
        opcao = ler_int();
        if (opcao < minimo || opcao > maximo) {
            printf("Opcao invalida! Digite um numero entre %d e %d: ", minimo, maximo);
        }
    } while (opcao < minimo || opcao > maximo);

    limpar_terminal();
    mudar_cor(14);
    return opcao;
}

static const char *descricao_item(int item) {
    switch (item) {
        case 1: return "Facao --> 6 de dano";
        case 2: return "Pistola com 6 municoes --> 10 de dano por municao";
        case 3: return "Lanterna --> ilumina lugares escuros";
        case 4: return "2 Ataduras --> curam 15 de vida e param sangramento";
        default: return "";
    }
}

static void imprimir_opcao_item(int opcao, int item) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%d - %s\n", opcao, descricao_item(item));
    imprimir(buffer);
}

void texto_item(int item) {
    imprimir_opcao_item(item, item);
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
    int itens_disponiveis[3];
    int primeiro;
    int segundo;
    int quantidade = 0;

    mudar_cor(15);
    for (int item = 1; item <= 4; item++) {
        texto_item(item);
    }
    primeiro = ler_opcao(1, 4);
    dar_item(primeiro);

    mudar_cor(15);
    imprimir("\nAgora escolha o seu segundo item:\n");
    for (int item = 1; item <= 4; item++) {
        if (item != primeiro) {
            itens_disponiveis[quantidade] = item;
            imprimir_opcao_item(++quantidade, item);
        }
    }
    segundo = itens_disponiveis[ler_opcao(1, quantidade) - 1];

    dar_item(segundo);
}

void mostrar_inventario(void) {
    char buffer[100];

    mudar_cor(14);
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
