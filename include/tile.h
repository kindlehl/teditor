#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

struct Tile {
	int id;
	struct SDL_Rect rect;
	struct SDL_Renderer* renderer; //This pointer is not owned by the Tile struct.
	struct SDL_Texture* texture;
};

void tileInitFromSurface(struct Tile*, struct SDL_Rect, struct SDL_Surface*, struct SDL_Renderer*, int);
void tileDestroy(struct Tile*);
void tileChangeDimensions(struct Tile*, struct SDL_Rect);
void tileRender(struct Tile*);

#endif
