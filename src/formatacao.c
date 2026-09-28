#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DELAY_LETRA
#define DELAY_LETRA 3500L
#endif

void mudar_cor(int cor) {
    switch (cor) {
        case 0: printf("\033[0m"); break;
        case 15: printf("\033[97m"); break;
        case 14: printf("\033[93m"); break;
        case 12: printf("\033[91m"); break;
        default: return;
    }
    fflush(stdout);
}

void limpar_terminal(void) {
#ifdef _WIN32
    system("cls");
#else
    fputs("\033[2J\033[H", stdout);
    fflush(stdout);
#endif
}

void imprimir(const char *texto) {
    const size_t tamanho = strlen(texto);

    for (size_t indice = 0; indice < tamanho; indice++) {
        putchar((unsigned char)texto[indice]);
        fflush(stdout);
#ifdef _WIN32
        Sleep((DWORD)((DELAY_LETRA + 999L) / 1000L));
#else
        const struct timespec atraso = {
            .tv_sec = DELAY_LETRA / 1000000L,
            .tv_nsec = (DELAY_LETRA % 1000000L) * 1000L
        };
        nanosleep(&atraso, NULL);
#endif
    }
}
