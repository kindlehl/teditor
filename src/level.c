#include "../include/screen.h"

void screenInit(struct Screen* screen, int rows, int cols){
	screen->rows = rows; 
	screen->cols = cols; 
	screen->num = rows * cols;
	screen->tiles = (struct Tile*)malloc( sizeof(struct Screen) * screen->num );
}

void screenDestroy(struct Screen* screen){
	for ( int i = 0; i < screen->num; i++ ) {
		tileDestroy(screen->tiles + i);
	}
	free(screen->tiles);
}
