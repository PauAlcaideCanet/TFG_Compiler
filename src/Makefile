# Makefile for Shift-Reduce Automata Parser (Windows)

CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = token.o stack.o automata.o main.o
EXEC = parser.exe

# Default rule
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compile object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files (Windows version)
clean:
	del /Q $(OBJ) $(EXEC)

# Run the parser (Windows version)
run: $(EXEC)
	$(EXEC)
