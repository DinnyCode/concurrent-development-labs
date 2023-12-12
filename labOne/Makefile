# Author: 		Denis Perepelyuk
# Student No.:	C00259076
# Description:	Contains commands to compile projects

CC=g++
CFLAGS= -std=c++11 -pthread
MUTFILES = mutualEx.cpp Semaphore.cpp Semaphore.h
DFLAGS = -08 -g

#Rule states that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

HELLO: helloThreads.o Semaphore.o
	$(CC) $(CFLAGS) helloThreads.o Semaphore.o -o HELLO

MUTUAL: $(MUTFILES)
	$(CC) $(CFLAGS) $(MUTFILES) -o muty

DEBUG: $(MUTFILES)
	$(CC) $(CFLAGS) $(DFLAGS) mutualEx.cpp Semaphore.cpp -o muty

#Deletes .o files
CLEAN:
	rm .o
	rm~
