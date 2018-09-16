#ifndef SCREEN_H
#define SCREEN_H

#include "../include/level.h"
#include <SDL2/SDL_image.h>

struct Screen {
	struct Level level;
	int width_px, height_px;
};

void screenInit(struct Screen*, struct SDL_Renderer*, char*, int, int, int, int);
void screenDestroy(struct Screen*);
void screenUpdate(struct Screen*);

#endif
