#ifndef level_H
#define level_H

/*
 * The level class is used as a container for tiles. It is agnostic to the actual dimensions in pixels
 * The level object is what transforms the boundaries between tiles to actual pixels. It supports wrapping.
 */
#include "../include/tile.h"

struct Level {
	int rows, cols, num;
	struct Tile* tiles; //logical 2D array of all tiles 
};

void levelInit(struct Level*, int, int);
void levelDestroy(struct Level*);

#endif
