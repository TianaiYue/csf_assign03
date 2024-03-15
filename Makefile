# Makefile for CSF Assignment 3

CXX = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic

all: csim

csim : main.o cache.o
	$(CXX) $(LDFLAGS) -o csim main.o cache.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cache.o: cache.cpp cache.h
	$(CXX) $(CXXFLAGS) -c cache.cpp

.PHONY: solution.zip

solution.zip :
	rm -f $@
	zip -9r $@ *.h *.cpp Makefile README.txt

clean :
	rm -f *.o $(EXES)

depend.mak :
	touch $@

depend :
	$(CXX) $(CFLAGS) -M > depend.mak

include depend.mak
