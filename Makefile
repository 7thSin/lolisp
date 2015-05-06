# Makefile for lolisp
OUTPUT = lolisp
CC=c++
VERFLAGS = -std=c++1y
CCFLAGS = -O2
WARNING = -Wall -Wno-strict-aliasing
LDFLAGS = -lreadline
DGFLAGS = -g -O0

all:
	@mkdir -p bin
	@echo "* Building lolisp..."
	$(CC) $(VERFLAGS) $(CCFLAGS) src/main.cpp -o bin/$(OUTPUT) $(LDFLAGS) $(WARNING)

debug:
	@mkdir -p bin
	$(CC) $(VERFLAGS) $(DGFLAGS) src/main.cpp -o bin/$(OUTPUT)-debug $(LDFLAGS) $(WARNING)

clean: 
	@rm -vr bin

run:
	bin/$(OUTPUT)

valgrind:
	valgrind bin/$(OUTPUT)-debug
	
fun:
	@echo lol
