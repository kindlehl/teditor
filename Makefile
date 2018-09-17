CC=gcc
EXE=teditor

all: main.o
	$(CC) -g *.o -lSDL2 -lSDL2_image -lm -o $(EXE) 
main.o: palette.o tile.o screen.o level.o src/main.c
	$(CC) -g -c src/main.c -lm -lSDL2 -lSDL2_image
palette.o: src/palette.c include/palette.h
	$(CC) -g -c src/palette.c -lSDL2	
tile.o: src/tile.c include/tile.h
	$(CC) -g -c src/tile.c -lSDL2	
screen.o: src/screen.c include/screen.h tile.o
	$(CC) -g -c src/screen.c -lSDL2
level.o: screen.o src/level.c include/level.h
	$(CC) -g -c src/level.c -lSDL2
clean:
	rm *.o
