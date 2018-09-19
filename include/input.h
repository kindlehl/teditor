#ifndef INPUT_H
#define INPUT_H

#include "palette.h"
#include "screen.h"
#include <SDL2/SDL.h>

#define TRUE 1
#define FALSE 0

extern int run;
extern SDL_Window* main_window;
extern char filename[256];

static unsigned char MOUSE_DOWN = FALSE;

void processEvents(struct Screen* screen, struct Palette* palette);
void handleMouse(struct Screen* screen, struct Palette* palette,  SDL_Event* e);
void handleHotkeys(struct Screen* screen, struct Palette* palette,  SDL_Event* e);

unsigned char parseArgs(struct ScreenSpec*, int argc, char** argv);

#endif
