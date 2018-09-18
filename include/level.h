#ifndef level_H
#define level_H

/*
 * The level class is used as a container for tiles. It is agnostic to the actual dimensions in pixels
 * The level object is what transforms the boundaries between tiles to actual pixels. It supports wrapping.
 */
#include <stdio.h>
#include "tile.h"
#include "level.pb-c.h"

struct Level {
	int rows, cols, num;
	struct Tile* tiles; //logical 2D array of all tiles 
};

void levelInitFromFile(struct Level*, char*, SDL_Rect, SDL_Renderer*);
void levelSerializeToFile(struct Level*, char*);
void levelInit(struct Level*, int, int);
void levelDestroy(struct Level*);

#endif
