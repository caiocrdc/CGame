CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
CPPFLAGS += -Isrc/include
BIN_DIR := bin

ifeq ($(OS),Windows_NT)
EXEEXT := .exe
MKDIR_P := if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
RMDIR := if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
else
EXEEXT :=
MKDIR_P := mkdir -p $(BIN_DIR)
RMDIR := rm -rf $(BIN_DIR)
endif

COMMON_SOURCES := src/formatacao.c src/geral.c src/combate.c
HEADERS := $(wildcard src/include/*.h)
RPGLIN := $(BIN_DIR)/RPGLIN$(EXEEXT)
RPGWIN := $(BIN_DIR)/RPGWIN$(EXEEXT)

.PHONY: all clean

all: $(RPGLIN) $(RPGWIN)

$(BIN_DIR):
	$(MKDIR_P)

$(RPGLIN): src/RPGLIN.c $(COMMON_SOURCES) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/RPGLIN.c $(COMMON_SOURCES) -o $@

$(RPGWIN): src/RPGWIN.c $(COMMON_SOURCES) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) src/RPGWIN.c $(COMMON_SOURCES) -o $@

clean:
	$(RMDIR)
