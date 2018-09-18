CC=gcc
CXX_FLAGS=-g -I/usr/local/include -I./include
CXX_LINKER_FLAGS=-L/usr/local/lib -lprotobuf-c -lSDL2 -lSDL2_image -lm 
TEDEXE=teditor
GAMEEXE=game
TED_OBS=input.o tile.o screen.o level.o levelProtoBuf.o palette.o 
GAME_OBS=input.o tile.o screen.o level.o levelProtoBuf.o

teditor: teditor.o
	$(CC) $(CXX_FLAGS) $(TED_OBS) teditor.o $(CXX_LINKER_FLAGS) -o $(TEDEXE) 

game: game.o
	$(CC) $(CXX_FLAGS) $(GAME_OBS) game.o $(CXX_LINKER_FLAGS) -o $(GAMEEXE) 

generate: level.proto
	protoc --c_out=. level.proto; mv *pb-c.h include; mv *pb-c.c src

all: teditor game generate
	echo Making All Things

teditor.o: $(TED_OBS) src/teditor.c
	$(CC) $(CXX_FLAGS) -c src/teditor.c 
game.o: $(GAME_OBS) src/game.c
	$(CC) $(CXX_FLAGS) -c src/game.c 
levelProtoBuf.o: src/level.pb-c.c include/level.pb-c.h
	$(CC) $(CXX_FLAGS) -c src/level.pb-c.c -o levelProtoBuf.o
input.o: src/input.c include/input.h palette.o screen.o
	$(CC) $(CXX_FLAGS) -c src/input.c
palette.o: src/palette.c include/palette.h tile.o
	$(CC) $(CXX_FLAGS) -c src/palette.c 
tile.o: src/tile.c include/tile.h
	$(CC) $(CXX_FLAGS) -c src/tile.c
screen.o: src/screen.c include/screen.h level.o
	$(CC) $(CXX_FLAGS) -c src/screen.c 
level.o: src/level.c include/level.h levelProtoBuf.o tile.o 
	$(CC) $(CXX_FLAGS) -c src/level.c



clean:
	rm *.o
