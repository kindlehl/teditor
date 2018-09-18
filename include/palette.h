#ifndef PALETTE_H
#define PALETTE_H

#include <stdio.h>
#include "tile.h"

struct Palette {
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct Tile* tiles;
	int rows, cols, num;
	int selected;
};

void paletteInit(struct Palette*, char**, int);
void paletteDestroy(struct Palette*);
void paletteUpdate(struct Palette*);


#endif
