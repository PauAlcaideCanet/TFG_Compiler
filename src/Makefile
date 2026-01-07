# Compiler
CC = gcc

# Source files
SRCS = automata.c cgen.c main.c node_stack.c node.c stack.c token.c util.c

# Output executable
OUT = main

# Default target
all: $(OUT)

# Rule to build the executable
$(OUT): $(SRCS)
	$(CC) $(SRCS) -o $(OUT)

# Clean up build files
clean:
	rm -f $(OUT)