# This is a Makefile for the mmn23 project
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CCLINK = $(CC)
LIBS = -lm
OBJS = numbers.o
RM = rm -f
# Creating the executable (mmn23)
mmn23: $(OBJS)
	$(CCLINK) -o mmn23 $(OBJS) $(LIBS)

# Creating object files using default rules
numbers.o: numbers.c 

# Cleaning old files before new make
clean:
	$(RM) mmn23 screen_test *.o *.bak *~ "#"* core
