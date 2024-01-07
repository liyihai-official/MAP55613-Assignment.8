# Makefile for Assignment 8
# Date: 2024-01-07
#

CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lm

EXECS := assignment8a assignment8b
OBJS := function.o





all: $(EXECS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

assignment8a: assignment8a.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

assignment8b: assignment8b.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lpthread








.PHONY: all clean

clean:
	rm -f $(EXECS) $(OBJS)
