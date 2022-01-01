CC=gcc
FLAGS=-Wall
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:src/%.c=build/%.o)
EXECUTABLE=dame

.PHONY= all clean build
.DEFAULT=all

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS) 
	$(CC) -o $@ $^

build:
	mkdir -p build

build/%.o: src/%.c | build
	$(CC) $(FLAGS) -c $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
	-rm -rf build