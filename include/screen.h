#ifndef SCREEN_H
#define SCREEN_H

#include "level.h"
#include <SDL2/SDL_image.h>

struct Screen {
	struct Level level;
	int width_px, height_px;
};

void screenInit(struct Screen*, struct SDL_Renderer*, char*, int, int, int, int);
void screenInitFromFile(struct Screen*, struct SDL_Renderer*, char*, int, int, int, int);
void screenDestroy(struct Screen*);
struct Tile* screenGetTile(struct Screen*, int, int);
void screenUpdate(struct Screen*);

#endif
