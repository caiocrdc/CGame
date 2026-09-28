CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
CPPFLAGS += -Isrc/include

ifeq ($(OS),Windows_NT)
EXEEXT := .exe
else
EXEEXT :=
endif

BIN_DIR := bin
COMMON_SOURCES := src/formatacao.c src/geral.c src/combate.c
HEADERS := $(wildcard src/include/*.h)
RPGLIN := $(BIN_DIR)/RPGLIN$(EXEEXT)
RPGWIN := $(BIN_DIR)/RPGWIN$(EXEEXT)

.PHONY: all clean

all: $(RPGLIN) $(RPGWIN)

$(BIN_DIR):
	mkdir -p $@

$(RPGLIN): src/RPGLIN.c $(COMMON_SOURCES) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/RPGLIN.c $(COMMON_SOURCES) -o $@

$(RPGWIN): src/RPGWIN.c $(COMMON_SOURCES) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/RPGWIN.c $(COMMON_SOURCES) -o $@

clean:
	rm -rf $(BIN_DIR)
