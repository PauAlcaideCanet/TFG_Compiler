CC = gcc
CFLAGS = -Wall -g

SRC = token.c stack.c node.c stack_node.c automata.c main.c
OBJ = $(SRC:.c=.o)

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) main
