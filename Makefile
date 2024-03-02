# Makefile for CSF Assignment 3

CXX = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic

all: csim

csim : main.o
	$(CXX) $(LDFLAGS) -o csim main.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

.PHONY: solution.zip

solution.zip :
	rm -f $@
	zip -9r $@ *.cpp Makefile README.txt

clean :
	rm -f *.o $(EXES)

depend.mak :
	touch $@

depend :
	$(CXX) $(CFLAGS) -M > depend.mak

include depend.mak
