#define _POSIX_C_SOURCE 200809L

#include "rpg_internal.h"

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

#define INPUT_SIZE 100
#define MESSAGE_SIZE 512
#define TEXT_LINE_WIDTH 80

static void sleep_microseconds(unsigned int microseconds)
{
    if (microseconds == 0) {
        return;
    }

#ifdef _WIN32
    Sleep((microseconds + 999U) / 1000U);
#else
    {
        struct timespec remaining = {
            (time_t)(microseconds / 1000000U),
            (long)(microseconds % 1000000U) * 1000L
        };

        while (nanosleep(&remaining, &remaining) == -1 && errno == EINTR) {
        }
    }
#endif
}

static void print_character(const GameState *game, char character)
{
    putchar(character);
    fflush(stdout);
    sleep_microseconds(game->atraso_texto_us);
}

void print_text(const GameState *game, const char *text)
{
    size_t column = 0;

    while (*text != '\0') {
        const char *word_end;
        size_t word_length;

        if (*text == '\n') {
            print_character(game, *text++);
            column = 0;
            continue;
        }

        if (*text == ' ' || *text == '\t') {
            while (*text == ' ' || *text == '\t') {
                text++;
            }
            if (*text == '\0') {
                if (column > 0) {
                    print_character(game, ' ');
                }
                continue;
            }
            if (*text == '\n') {
                continue;
            }

            word_end = text;
            while (*word_end != '\0' && *word_end != '\n' &&
                   *word_end != ' ' && *word_end != '\t') {
                word_end++;
            }
            word_length = (size_t)(word_end - text);
            if (column > 0 && column + 1 + word_length > TEXT_LINE_WIDTH) {
                print_character(game, '\n');
                column = 0;
            } else if (column > 0) {
                print_character(game, ' ');
                column++;
            }
            continue;
        }

        word_end = text;
        while (*word_end != '\0' && *word_end != '\n' && *word_end != ' ' &&
               *word_end != '\t') {
            word_end++;
        }
        word_length = (size_t)(word_end - text);
        if (column > 0 && column + word_length > TEXT_LINE_WIDTH) {
            print_character(game, '\n');
            column = 0;
        }
        while (text < word_end) {
            print_character(game, *text++);
            column++;
        }
    }
}

static bool output_is_terminal(void)
{
#ifdef _WIN32
    return _isatty(_fileno(stdout)) != 0;
#else
    return isatty(fileno(stdout)) != 0;
#endif
}

static void clear_terminal(void)
{
    if (!output_is_terminal()) {
        return;
    }

#ifdef _WIN32
    {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO information;
        COORD origin = {0, 0};
        DWORD cells;
        DWORD written;

        if (console == INVALID_HANDLE_VALUE ||
            !GetConsoleScreenBufferInfo(console, &information)) {
            putchar('\n');
            fflush(stdout);
            return;
        }
        cells = (DWORD)information.dwSize.X * (DWORD)information.dwSize.Y;
        FillConsoleOutputCharacterA(console, ' ', cells, origin, &written);
        FillConsoleOutputAttribute(console, information.wAttributes, cells,
                                   origin, &written);
        SetConsoleCursorPosition(console, origin);
    }
#else
    fputs("\033[H\033[2J", stdout);
#endif

    /*
     * Alguns terminais integrados renderizam a limpeza e a primeira linha no
     * mesmo quadro, fazendo essa linha desaparecer. Avancar uma linha cria
     * uma fronteira visual antes que a proxima tela seja desenhada.
     */
    putchar('\n');
    fflush(stdout);
}

void print_format(const GameState *game, const char *format, ...)
{
    char message[MESSAGE_SIZE];
    va_list arguments;

    va_start(arguments, format);
    vsnprintf(message, sizeof(message), format, arguments);
    va_end(arguments);
    print_text(game, message);
}

static bool read_line(char *buffer, size_t size)
{
    size_t length;
    int character;

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return true;
    }

    while ((character = getchar()) != '\n' && character != EOF) {
    }
    return true;
}

static int read_number(const GameState *game, int minimum, int maximum)
{
    char input[INPUT_SIZE];
    char *end;
    long value;

    while (true) {
        if (!read_line(input, sizeof(input))) {
            return minimum;
        }

        errno = 0;
        end = NULL;
        value = strtol(input, &end, 10);
        while (end != NULL && (*end == ' ' || *end == '\t')) {
            end++;
        }

        if (errno != ERANGE && end != input && end != NULL && *end == '\0' &&
            value >= minimum && value <= maximum && value <= INT_MAX) {
            return (int)value;
        }
        print_format(game, "Escolha um numero entre %d e %d: ", minimum,
                     maximum);
    }
}

static int choose_menu_internal(const GameState *game, const char *title,
                                const MenuOption options[],
                                size_t option_count, bool clear_after_choice)
{
    size_t i;
    int selection;

    if (title != NULL && title[0] != '\0') {
        print_text(game, title);
    }
    for (i = 0; i < option_count; i++) {
        print_format(game, "%zu - %s\n", i + 1, options[i].texto);
    }
    print_text(game, "> ");
    selection = read_number(game, 1, (int)option_count);
    if (clear_after_choice) {
        clear_terminal();
    }
    return options[selection - 1].valor;
}

int choose_menu(const GameState *game, const char *title,
                const MenuOption options[], size_t option_count)
{
    return choose_menu_internal(game, title, options, option_count, true);
}

void configure_text_speed(GameState *game)
{
    const MenuOption options[] = {
        {1, "Normal"},
        {2, "Rapida"},
        {3, "Instantanea"}
    };

    switch (choose_menu_internal(game, "Escolha a velocidade do texto:\n",
                                 options,
                                 sizeof(options) / sizeof(options[0]), false)) {
        case 1:
            game->atraso_texto_us = 25000;
            break;
        case 2:
            game->atraso_texto_us = 5000;
            break;
        case 3:
            game->atraso_texto_us = 0;
            break;
    }
    print_text(game, "\n");
}

void read_player_name(GameState *game)
{
    while (true) {
        print_text(game, "Digite o nome do seu personagem: ");
        if (!read_line(game->player.nome, sizeof(game->player.nome))) {
            snprintf(game->player.nome, sizeof(game->player.nome), "Jogador");
            clear_terminal();
            return;
        }
        if (game->player.nome[0] != '\0') {
            clear_terminal();
            return;
        }
        print_text(game, "O nome nao pode ficar vazio.\n");
    }
}
