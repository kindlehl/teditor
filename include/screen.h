#ifndef SCREEN_H
#define SCREEN_H

#include "level.h"
#include <SDL2/SDL_image.h>


/*                      A				B			  C
 *                __________________________________________
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                |           | %%%%%%%%%%%%%%%%% |        |
 *                __________________________________________
 *                
 * This is the general layout for the screen. The filled-in field in the center
 * represents the things that are rendered to the application window.
 * The Fields are summarized below.
 *
 * A + B + C: This region describes the level. You can think of this entire screen structure as a 
 *    microscope focused on a cluster of blood cells. You can see a small portion of the blood cells,
 *    but as you move the microscope slide around, you see more and newerblood cells. In this case, the level
 *    which contains rendering tiles is the microscope slide and the screen acts as the microscope.
 *
 * A: Described by left_pad. left_pad is the distance between the left edge of the window
 *	  and the left-most tile in the level. It is not rendered. This region logically exists off the
 *	  window to the left.
 *
 * B: The part of the level that is being rendered to the window. Its dimensions are 
 *    demarked by the variables width_px and height_px.
 *
 * C: Described by right_pad. right_pad is the distance between the right edge of the window
 *	  and the right edge of the right-most tile in the level. This region logically exists off the
 *	  window to the right.
 */

struct ScreenSpec {
	int width_px, 
		height_px,
		rows,
		cols;
	float tile_scale_factor;
	char* level_path, //do NOT free()
		* default_texture_path;	
};

struct Screen {
	struct Level level;
	struct ScreenSpec spec;
	int left_pad,
		right_pad;
};

void screenInit(struct Screen*, struct SDL_Renderer*, struct ScreenSpec);
void screenInitFromFile(struct Screen*, struct SDL_Renderer*, struct ScreenSpec);
void screenDestroy(struct Screen*);
struct Tile* screenGetTile(struct Screen*, int, int);
void screenUpdate(struct Screen*);

#endif
