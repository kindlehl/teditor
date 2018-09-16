#ifndef LEVEL_H
#define LEVEL_H

#include "../include/screen.h"

struct Level {
	struct Screen screen;
	int width_px, height_px;
};

void levelInit(struct Level*, struct SDL_Renderer*, char*, int, int, int, int);
void levelUpdate(struct Level*);

#endif
