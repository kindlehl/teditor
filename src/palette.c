#include "palette.h"

void paletteInit(struct Palette* palette, char** paths, int num_paths){

	const int tile_width = 100;
	const int tile_height = 100;

	palette->selected = -1;
	palette->num = num_paths; 
	palette->tiles = (struct Tile*)malloc(palette->num * sizeof(struct Tile));

	if (!palette->tiles) {
		printf("Error allocating palette tiles");
	}

	palette->rows = palette->cols = 0;
	
	while(palette->cols * palette->cols < palette->num){
		palette->cols++;
	}

	palette->rows = palette->num <= palette->cols * palette->cols-1 ? palette->cols - 1: palette->cols;

	palette->window = SDL_CreateWindow("Palette", 0, 0, tile_width * palette->cols, tile_height * palette->rows, 0);

	if(!palette->window){
		printf("Palette Window not initialized");
	}

	/*
	 * This single function call below causes the program to segfault if the flag passed
	 * to SDL_CreateRenderer is not SDL_RENDERER_SOFTWARE. I do not know why
	 * at the time of this comment
	 */
	palette->renderer = SDL_CreateRenderer(palette->window, -1, SDL_RENDERER_SOFTWARE);

	if(!palette->renderer){
		printf("Palette Window not initialized");
	}

	SDL_Rect palette_tile;
	palette_tile.w = tile_width;
	palette_tile.h = tile_height;

	for(int i = 0; i < palette->num; i++) {

		palette_tile.x = (i % palette->cols) * tile_width;
		palette_tile.y = (i / palette->cols) * tile_height;
		tileInitFromSurface(palette->tiles + i, paths[i], palette_tile, palette->renderer, i);

	}

}

void paletteDestroy(struct Palette* palette){
	for(int i = 0; i < palette->num; i++){
		tileDestroy(palette->tiles + i);
	}

	free(palette->tiles);

	SDL_DestroyRenderer(palette->renderer);
	SDL_DestroyWindow(palette->window);
}

void paletteUpdate(struct Palette* palette) {
	for(int i = 0; i < palette->num; i++ ){
		tileRender(palette->tiles + i);
	}
}
