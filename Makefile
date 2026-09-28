CC := gcc
AR := ar
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -Iinclude -Isrc
DEPFLAGS := -MMD -MP
ARFLAGS := rcs

BUILD_DIR := build
LIBRARY := $(BUILD_DIR)/librpg.a

ifeq ($(OS),Windows_NT)
TARGET := $(BUILD_DIR)/rpg.exe
CREATE_BUILD_DIR = if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
REMOVE_BUILD_DIR = if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
RUN_TARGET = $(subst /,\,$(TARGET))
else
TARGET := $(BUILD_DIR)/rpg
CREATE_BUILD_DIR = mkdir -p $(BUILD_DIR)
REMOVE_BUILD_DIR = rm -rf $(BUILD_DIR)
RUN_TARGET = ./$(TARGET)
endif

LIB_SOURCES := src/rpg.c src/platform.c src/game.c src/story.c
LIB_OBJECTS := $(LIB_SOURCES:src/%.c=$(BUILD_DIR)/%.o)
MAIN_OBJECT := $(BUILD_DIR)/main.o
DEPENDENCIES := $(LIB_OBJECTS:.o=.d) $(MAIN_OBJECT:.o=.d)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(MAIN_OBJECT) $(LIBRARY)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -L$(BUILD_DIR) -lrpg -o $@

$(LIBRARY): $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR):
	$(CREATE_BUILD_DIR)

run: $(TARGET)
	$(RUN_TARGET)

clean:
	$(REMOVE_BUILD_DIR)

-include $(DEPENDENCIES)
