#include "../include/screen.h"

void screenInit(struct Screen* screen, struct SDL_Renderer* renderer, char* path, int window_w, int window_h, int tile_w, int tile_h) {
	screen->width_px = window_w;
	screen->height_px = window_h;
	int cols = window_w/tile_w;
	int rows = window_h/tile_h;
	levelInit(&screen->level, rows, cols);	
	//populate tiles with surface
	struct SDL_Rect temp;
	temp.w = tile_w;	
	temp.h = tile_h;	
	for(int i = 0; i < cols * rows; i++) {
		temp.x = (i % cols) * tile_w;
		temp.y = (i / rows) * tile_h;
		tileInitFromSurface(screen->level.tiles + i, temp, IMG_Load(path), renderer, i);
	}
}

void screenDestroy(struct Screen* screen){
	levelDestroy(&screen->level);
}

void screenUpdate(struct Screen* screen) {
	struct Tile* tiles = screen->level.tiles;
	for(int i = 0; i < screen->level.num; i++ ){
		tileRender(tiles + i);
	}
}
