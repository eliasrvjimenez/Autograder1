# Makefile

# Variables
CC=gcc
CFLAGS=-Wall -g
N ?= 10
SOURCE_FILE=template.c
SOL_DIR=./solutions
BINARIES=$(addprefix $(SOL_DIR)/sol_, $(shell seq 1 $(N)))

# Default target
all: autograder $(BINARIES)

# Compile autograder
autograder: autograder.c
	$(CC) $(CFLAGS) -o $@ $^

# Compile template.c into N binaries
$(SOL_DIR)/sol_%: $(SOURCE_FILE)
	mkdir -p $(SOL_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Clean the build
clean:
	rm -f autograder $(BINARIES) submissions.txt

.PHONY: all clean
