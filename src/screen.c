#include "screen.h"

void screenInit(struct Screen* screen, struct SDL_Renderer* renderer, struct ScreenSpec spec) {
	screen->spec = spec;

	levelInit(&screen->level, spec.rows, spec.cols);	
	//populate tiles with surface
	struct SDL_Rect temp = {
		.x = 0,
		.y = 0,
		.w = spec.width_px / spec.cols,
		.h = spec.height_px / spec.rows
	};


	for(int i = 0; i < screen->level.num; i++) {
		temp.x = (i % screen->spec.cols) * temp.w;
		temp.y = (i / screen->spec.cols) * temp.h;
		tileInitFromSurface(screen->level.tiles + i, spec.default_texture_path, temp, renderer, i);
	}
}

void screenInitFromFile(struct Screen* screen, struct SDL_Renderer* renderer, struct ScreenSpec spec) {

	screen->spec = spec;

	struct SDL_Rect temp = {
		.x = 0,
		.y = 0,
		.w = spec.width_px / spec.cols,
		.h = spec.height_px / spec.rows
	};

	levelInitFromFile(&screen->level, spec.level_path, temp, renderer);	

	for(int i = 0; i < screen->level.num; i++) {
		temp.x = (i % screen->spec.cols) * temp.w;
		temp.y = (i / screen->spec.rows) * temp.h;
		tileInitFromSurface(screen->level.tiles + i, screen->level.tiles[i].path, temp, renderer, i);
	}

}

void screenDestroy(struct Screen* screen) {
	levelDestroy(&screen->level);
}

struct Tile* screenGetTile(struct Screen* screen, int x, int y) {
	int rows = screen->spec.rows,
		cols = screen->spec.cols,
		w = screen->spec.width_px / screen->spec.cols,
		h = screen->spec.height_px / screen->spec.rows,
		index = ( ( y / h ) * cols + x / w );

	return screen->level.tiles + index;
}

void screenUpdate(struct Screen* screen) {
	struct Tile* tiles = screen->level.tiles;
	for(int i = 0; i < screen->level.num; i++ ){
		tileRender(tiles + i);
	}
}
