#include "../include/input.h"

void processEvents( struct Screen* screen, struct Palette* palette){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				run = FALSE;
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_WINDOWEVENT:
				handleMouse(screen, palette, &e);
				break;
			case SDL_KEYDOWN:
				handleHotkeys(screen, palette, &e);
				break;
		}
	}
}

void handleMouse( struct Screen* screen, struct Palette* palette,  SDL_Event* e){

	int screen_ID = SDL_GetWindowID(main_window);
	int palette_ID = SDL_GetWindowID(palette->window);

	if( !(screen_ID && palette_ID)  ){
		printf("Error gathering window IDs: %s\n", SDL_GetError());
	}

	if(e->type == SDL_MOUSEBUTTONDOWN){

		int x = e->button.x,
			y = e->button.y,
			w = palette->tiles[0].rect.w,
			h = palette->tiles[0].rect.h,
			rows = palette->rows,
			cols = palette->cols;

		if(e->button.windowID == palette_ID){

			//not sure why the -1 is needed in this scenario...
			palette->selected = ( (y / h) * cols ) + x / w;
			printf("clicked palette item number %d", palette->selected);
			fflush(stdout);

		}else{
		
			int index = palette->selected;
			//causes memory leak.
			struct Tile* screen_tile = screenGetTile(screen, x, y);
			tileDestroy(screen_tile);
			tileInitFromSurface(screen_tile, palette->tiles[index].path, screen_tile->rect, screen_tile->renderer, 0);


		}

	}else if(e->type == SDL_WINDOWEVENT){

	//Makes any window you mouse over active. This prevents the user from needing to click
	//anytime he wants to go between the two windows
		if(e->window.event == SDL_WINDOWEVENT_ENTER){
			SDL_SetWindowInputFocus(SDL_GetWindowFromID(e->window.windowID));
		}else if(e->window.event==SDL_WINDOWEVENT_CLOSE){
			run = FALSE;
		}

	}
}

void handleHotkeys(struct Screen* screen, struct Palette* palette,  SDL_Event* e) {
	switch(e->key.keysym.sym){
		case SDLK_n:
			printf("Enter the path to save the level to: ");
			scanf("%255s", filename);
		case SDLK_s:
			//levelSerialize(&screen->level);
			break;
	}
}
