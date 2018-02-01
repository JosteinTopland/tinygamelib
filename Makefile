CC=g++
CFLAGS=-c -Wall -Iinclude
LDFLAGS=-lSDL2 -lSDL2_mixer -lSDL2_image
SOURCES=src/tinygamelib.cpp src/examples/vampire/vampire.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=vampire

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
