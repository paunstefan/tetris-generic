CC = clang
CFLAGS = -Wall -Wextra -Iinclude -lSDL2 -g
OBJ = src/main.c src/game.c src/sdl2/generic_sdl.c src/display.c


all: tetris_generic

tetris_generic: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm ./tetris_generic