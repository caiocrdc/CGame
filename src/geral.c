#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif

#include "estado.h"
#include "formatacao.h"
#include "geral.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <io.h>
#include <windows.h>
#else
#include <sys/ioctl.h>
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
    if (tecla == 'w' || tecla == 'W') return TECLA_CIMA;
    if (tecla == 's' || tecla == 'S') return TECLA_BAIXO;
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
    } else if (tecla == 'w' || tecla == 'W') {
        tecla = TECLA_CIMA;
    } else if (tecla == 's' || tecla == 'S') {
        tecla = TECLA_BAIXO;
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

static int ler_int(void) {
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

static int largura_terminal(void) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
        return info.srWindow.Right - info.srWindow.Left + 1;
    }
#else
    struct winsize tamanho;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &tamanho) == 0 && tamanho.ws_col > 0) {
        return tamanho.ws_col;
    }
#endif
    return 80;
}

static int linhas_menu(const char *opcoes[], int quantidade, int largura) {
    int linhas = 1;
    int largura_util = largura > 1 ? largura - 1 : largura;

    for (int indice = 0; indice < quantidade; indice++) {
        int caracteres = (int)strlen(opcoes[indice]) + 7;
        int linhas_opcao = (caracteres + largura_util - 1) / largura_util;
        linhas += linhas_opcao > 0 ? linhas_opcao : 1;
    }
    return linhas;
}

static void desenhar_menu(const char *opcoes[], int quantidade, int selecionada) {
    putchar('\n');
    for (int indice = 0; indice < quantidade; indice++) {
        if (indice == selecionada) {
            mudar_cor(14);
            printf("  > %d. %s", indice + 1, opcoes[indice]);
        } else {
            mudar_cor(15);
            printf("    %d. %s", indice + 1, opcoes[indice]);
        }
        mudar_cor(0);
        putchar('\n');
    }
    fflush(stdout);
}

int selecionar_opcao(int quantidade, const char *opcoes[]) {
    if (quantidade <= 0 || opcoes == NULL) return -1;

    if (!terminal_interativo()) {
        mudar_cor(15);
        for (int indice = 0; indice < quantidade; indice++) {
            printf("%d - %s\n", indice + 1, opcoes[indice]);
        }
        int opcao;
        do {
            opcao = ler_int();
            if (opcao < 1 || opcao > quantidade) {
                printf("Opcao invalida! Digite um numero entre 1 e %d: ", quantidade);
            }
        } while (opcao < 1 || opcao > quantidade);
        putchar('\n');
        mudar_cor(14);
        return opcao;
    }

    int selecionada = 0;
    int linhas = linhas_menu(opcoes, quantidade, largura_terminal());
    int tecla;

    fputs("\033[?25l", stdout);
    fflush(stdout);
    desenhar_menu(opcoes, quantidade, selecionada);
    while ((tecla = ler_tecla()) != TECLA_ENTER) {
        if (tecla == TECLA_CIMA) {
            selecionada = (selecionada + quantidade - 1) % quantidade;
        } else if (tecla == TECLA_BAIXO) {
            selecionada = (selecionada + 1) % quantidade;
        } else {
            continue;
        }
        printf("\033[%dA\r\033[J", linhas);
        desenhar_menu(opcoes, quantidade, selecionada);
    }

    fputs("\033[?25h", stdout);
    fflush(stdout);
    putchar('\n');
    mudar_cor(14);
    return selecionada + 1;
}

int escolher_menu(int quantidade, ...) {
    if (quantidade <= 0) return -1;
    if (quantidade > 50) quantidade = 50;

    const char *opcoes[50];
    va_list argumentos;
    va_start(argumentos, quantidade);
    for (int indice = 0; indice < quantidade; indice++) {
        opcoes[indice] = va_arg(argumentos, const char *);
    }
    va_end(argumentos);

    return selecionar_opcao(quantidade, opcoes);
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

    primeiro = escolher_menu(4,
        descricao_item(1),
        descricao_item(2),
        descricao_item(3),
        descricao_item(4));
    dar_item(primeiro);

    for (int item = 1; item <= 4; item++) {
        if (item != primeiro) {
            itens_disponiveis[quantidade] = item;
            quantidade++;
        }
    }
    segundo = itens_disponiveis[selecionar_opcao(quantidade, (const char *[]){
        descricao_item(itens_disponiveis[0]),
        descricao_item(itens_disponiveis[1]),
        descricao_item(itens_disponiveis[2])
    }) - 1];

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
