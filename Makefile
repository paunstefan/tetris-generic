CC = clang
CFLAGS = -Wall -Wextra -Iinclude -lSDL2 -g
OBJ = src/main.c


all: tetris_generic

tetris_generic: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm ./tetris_generic