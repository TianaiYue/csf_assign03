# Makefile for CSF Assignment 3

CC = g++
CFLAGS = -g -std=c++14 -Wall -Wextra -pedantic

ASMFLAGS = -g -no-pie

LDFLAGS = -no-pie

TARGET = csim

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

csim.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

.PHONY: solution.zip

solution.zip :
	rm -f $@
	zip -9r $@ *.cpp Makefile README.txt

clean :
	rm -f *.o $(EXES)

depend.mak :
	touch $@

depend :
	$(CC) $(CFLAGS) -M \
		$(COMMON_C_SRCS) $(C_SRCS) $(DRIVER_SRCS) $(TEST_SRCS) \
		> depend.mak

include depend.mak
