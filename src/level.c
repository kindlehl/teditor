#include "../include/level.h"

void levelInit(struct Level* level, int rows, int cols){
	level->rows = rows; 
	level->cols = cols; 
	level->num = rows * cols;
	level->tiles = (struct Tile*)malloc( sizeof(struct Level) * level->num );
}

void levelDestroy(struct Level* level){
	for ( int i = 0; i < level->num; i++ ) {
		tileDestroy(level->tiles + i);
	}
	free(level->tiles);
}
