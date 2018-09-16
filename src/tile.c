#include "../include/tile.h"

void tileInitFromSurface(struct Tile* tile, struct SDL_Rect rect, struct SDL_Surface* surface, struct SDL_Renderer* renderer, int id){
	tile->rect = rect;
	tile->texture = SDL_CreateTextureFromSurface(renderer, surface);
	tile->renderer = renderer;
	id = id;
}

void tileDestroy(struct Tile* tile){
	SDL_DestroyTexture(tile->texture);
}

//probably useless
void tileChangeDimensions(struct Tile* tile, struct SDL_Rect rect){
	tile->rect = rect;
}

void tileRender(struct Tile* tile){
	SDL_RenderCopy(tile->renderer, tile->texture, NULL, &tile->rect);
}
