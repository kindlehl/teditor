#ifndef SCREEN_H
#define SCREEN_H

/*
 * The screen class is used as a container for tiles. It is agnostic to the actual dimensions in pixels
 * The level object is what transforms the boundaries between tiles to actual pixels. It supports wrapping.
 */
#include "../include/tile.h"

struct Screen {
	int rows, cols, num;
	struct Tile* tiles; //logical 2D array of all tiles 
};

void screenInit(struct Screen*, int, int);
void screenDestroy(struct Screen*);

#endif
