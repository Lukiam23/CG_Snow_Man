################################################################################
SOURCES		= raycasting.cpp
OUTPUT 		= test
CC			= g++
CFLAGS		= -Wall -c -std=c++11
LDFLAGS		= -lGLEW -lGL -lGLU -lglut -lIL -lILU -lILUT
################################################################################
all: build

build: obj bin bin/$(OUTPUT)

bin/$(OUTPUT): $(addprefix obj/,$(SOURCES:.cpp=.o))
	$(CC) -o $@ $^ $(LDFLAGS)

obj/%.o: %.cpp
	$(CC) -o $@ $^ $(CFLAGS)

obj: 
	@mkdir obj 

bin:
	@mkdir bin

clean: 
	rm -r obj bin

run: build
	./bin/$(OUTPUT)

.PHONY: build clean run
################################################################################
