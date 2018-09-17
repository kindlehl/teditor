CC=gcc
CXX_FLAGS=-g -I/usr/local/include -I./include
CXX_LINKER_FLAGS=-L/usr/local/lib -lprotobuf-c -lSDL2 -lSDL2_image -lm 
EXE=teditor

all: main.o
	$(CC) $(CXX_FLAGS) *.o $(CXX_LINKER_FLAGS) -o $(EXE) 
main.o: input.o palette.o tile.o screen.o level.o protobuf.target  src/main.c
	$(CC) $(CXX_FLAGS) -c src/main.c 
protobuf.target: src/*.pb-c.c include/*.pb-c.h
	$(CC) $(CXX_FLAGS) -c src/*.pb-c.c 
input.o: src/input.c include/input.h
	$(CC) $(CXX_FLAGS) -c src/input.c
palette.o: src/palette.c include/palette.h
	$(CC) $(CXX_FLAGS) -c src/palette.c 
tile.o: src/tile.c include/tile.h
	$(CC) $(CXX_FLAGS) -c src/tile.c
screen.o: src/screen.c include/screen.h tile.o
	$(CC) $(CXX_FLAGS) -c src/screen.c 
level.o: screen.o src/level.c include/level.h
	$(CC) $(CXX_FLAGS) -c src/level.c
clean:
	rm *.o
