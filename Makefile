CC:=g++
CFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g
INCLUDES=-Isrc/
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=bwbot.out

all:$(OUTPUT)

$(OUTPUT):$(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(HTMLFLAGS)

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm $(OBJECTS) $(OUTPUT)
