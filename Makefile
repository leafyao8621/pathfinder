CC = gcc
SRC = $(wildcard src/*/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = pf

%.o: %.c
	$(CC) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) -lsqlite3 -lncurses -lm

.PHONY: clean
clean:
	@rm $(OBJ)
	@rm $(BIN)
