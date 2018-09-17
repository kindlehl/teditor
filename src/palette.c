#include "../include/palette.h"

void paletteInit(struct Palette* palette, char** paths, int num_paths){

	const int tile_width = 100;
	const int tile_height = 100;

	palette->num = num_paths; 
	palette->tiles = (struct Tile*)malloc(palette->num * sizeof(struct Tile));

	if (!palette->tiles) {
		printf("Error allocating palette tiles");
	}

	palette->rows = palette->cols = 0;
	
	while(palette->rows * palette->rows < palette->num){
		palette->rows++;
	}

	palette->cols = palette->rows; //makes palette a square for now

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

	printf("Creating rect");
	SDL_Rect palette_tile;
	palette_tile.w = tile_width;
	palette_tile.h = tile_height;

	for(int i = 0; i < palette->num; i++) {

		palette_tile.x = (i % palette->cols) * tile_width;
		palette_tile.y = (i / palette->rows) * tile_height;
		printf("initializing tile %s", paths[i]);
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
