#################################################################################
# 	Introduction to Software Security Assignment (Laboratory) 5 Makefile	#
# 	Authors: Roy Simanovich (c) 2023				#
# 	Description: This Makefile compiles the programs and libraries 		#
# 				Date: 2023-06					#
# 			Course: Introduction to Software Security				#
# 				Assignment: 5					#
# 				Compiler: gcc					#
# 				OS: Linux					#
# 			IDE: Visual Studio Code					#
#################################################################################

# Flags for the compiler and linker.
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -pedantic
RM = rm -f

.PHONY: all clean

all: rand_vs_rdrand

rand_vs_rdrand: rand_vs_rdrand.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) -f *.o rand_vs_rdrand