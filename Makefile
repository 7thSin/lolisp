# Makefile for lolisp
OUTPUT = lolisp
CC = g++ -std=c++14
CCFLAGS = -O2
WARNING = -Wall -Wno-strict-aliasing
LDFLAGS = -lreadline
DGFLAGS = -g -O0

all:
	mkdir -p bin
	@echo "* Building lolisp..."
	$(CC) $(CCFLAGS) src/main.cpp -o bin/$(OUTPUT) $(LDFLAGS) $(WARNING)

debug:
	mkdir -p bin
	$(CC) $(DGFLAGS) src/main.cpp -o bin/$(OUTPUT)-debug $(LDFLAGS) $(WARNING)

clean: 
	rm -vr bin

run:
	bin/lolisp
