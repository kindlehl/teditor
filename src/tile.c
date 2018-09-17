#include "../include/tile.h"
#include <SDL2/SDL_image.h>

void tileInitFromSurface(struct Tile* tile, char* path, struct SDL_Rect rect, struct SDL_Renderer* renderer, int id){
	tile->rect = rect;
	tile->path = (char*)malloc(strlen(path) + 1);
	strcpy(tile->path, path);
	SDL_Surface* tile_surface = IMG_Load(path);
	if (!tile_surface) {
		printf("Error loading surface with image: %s\n", path);
	}
	tile->texture = SDL_CreateTextureFromSurface(renderer, tile_surface);
	if (!tile->texture) {
		printf("Error loading texture from surface using image: %s\n", path);
	}
	SDL_FreeSurface(tile_surface);
	tile->renderer = renderer;
	id = id;
}

void tileDestroy(struct Tile* tile){
	SDL_DestroyTexture(tile->texture);
	free(tile->path);
}

//probably useless
void tileChangeDimensions(struct Tile* tile, struct SDL_Rect rect){
	tile->rect = rect;
}

void tileRender(struct Tile* tile){
	SDL_RenderCopy(tile->renderer, tile->texture, NULL, &tile->rect);
}
