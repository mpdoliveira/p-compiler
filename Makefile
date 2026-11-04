CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -MMD -MP

CPPFLAGS = -Iinclude

SRC = $(wildcard src/*.c)

OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

DEP = $(OBJ:.o=.d)

TARGET = build/compiler

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	@if not exist build mkdir build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -rf build

.PHONY: all clean