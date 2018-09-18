#include "level.h"

void levelInitFromFile(struct Level* level, char* path, SDL_Rect tile_rect, SDL_Renderer* renderer){
	FILE* level_file = fopen(path, "rb");
	fseek(level_file, 0, SEEK_END);
	size_t file_length = ftell(level_file);
	char* buffer = malloc(file_length);
	fseek(level_file, 0, SEEK_SET);
	fread(buffer, 1, file_length, level_file);
	LevelMessage* msg = level_message__unpack(NULL, file_length, buffer);	
	level->rows = msg->rows;
	level->cols = msg->cols;
	level->num = msg->num;
	if (level->num) {
		level->tiles = (struct Tile*)malloc(sizeof(struct Tile) * level->num);
	}
	for(int i = 0; i < level->num; i++){
		int id = msg->ids[i];
		tileInitFromSurface(level->tiles + i, msg->paths[i], tile_rect, renderer, id); 
	}
	free(buffer);
	level_message__free_unpacked(msg, NULL);
}

void levelSerializeToFile(struct Level* level, char* path) {
	LevelMessage msg = LEVEL_MESSAGE__INIT;
	msg.n_ids = msg.n_paths = level->num;
	//relies on level->num and the ids being stored as ints
	msg.ids = malloc( sizeof(int) * level->num );
	msg.paths = malloc( sizeof(char*) * level->num );

	for(int i = 0; i < level->num; i++) {
		msg.ids[i] = level->tiles[i].id;
		msg.paths[i] = level->tiles[i].path;
	}

	msg.rows = level->rows;
	msg.cols = level->cols;
	msg.num = level->num;

	int length = level_message__get_packed_size(&msg);
	void* buffer = malloc(length);
	level_message__pack(&msg, buffer);

	FILE* file = fopen(path, "wb");
	
	fwrite(buffer, 1, length, file);
	fclose(file);
	free(msg.ids);
	free(msg.paths);
}

void levelInit(struct Level* level, int rows, int cols){
	level->rows = rows; 
	level->cols = cols; 
	level->num = rows * cols;
	level->tiles = (struct Tile*)malloc( sizeof(struct Tile) * level->num );
}

void levelDestroy(struct Level* level){
	for ( int i = 0; i < level->num; i++ ) {
		tileDestroy(level->tiles + i);
	}
	free(level->tiles);
}
