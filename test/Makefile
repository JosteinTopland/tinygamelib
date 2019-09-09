CC=gcc
CFLAGS=-I/Users/jostein/Libraries/include -Wall
LIBS=-L/Users/jostein/Libraries/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

test.exe: test.c
	$(CC) test.c -o test.exe $(CFLAGS) $(LIBS)

clean:
	rm -f test.exe