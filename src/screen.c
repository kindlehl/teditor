#include "../include/level.h"
#include <SDL2/SDL_image.h>

void levelInit(struct Level* level, struct SDL_Renderer* renderer, char* path, int window_w, int window_h, int tile_w, int tile_h) {
	level->width_px = window_w;
	level->height_px = window_h;
	int cols = window_w/tile_w;
	int rows = window_h/tile_h;
	screenInit(&level->screen, window_w/tile_w, window_h/tile_h);	
	//populate tiles with surface
	struct SDL_Rect temp;
	temp.w = tile_w;	
	temp.h = tile_h;	
	for(int i = 0; i < cols * rows; i++) {
		temp.x = (i % cols) * tile_w;
		temp.y = (i / rows) * tile_h;
		tileInitFromSurface(level->screen.tiles + i, temp, IMG_Load(path), renderer, i);
	}
}

void levelUpdate(struct Level* level) {
	struct Tile* tiles = level->screen.tiles;
	for(int i = 0; i < level->screen.num; i++ ){
		tileRender(tiles + i);
	}
}
