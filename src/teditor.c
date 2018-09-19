#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "screen.h"
#include "palette.h"
#include "input.h"

#define TRUE 1
#define FALSE 0
#define MAX_FILES 20

char* paths[MAX_FILES] = { NULL };
const int FORMATS = 7;
int run = TRUE;
char filename[256];
SDL_Window* main_window;

int stringToInt(char* s) {
	int length = strlen(s);
	int result = 0;
	for(int i = 0; i < length;){
		result += (s[i] - 48) * pow(10, length - ++i);
	}
	return result;
}

int setTexturePaths() {
	const char* const supported_formats[] = {".png", ".jpg", ".jpeg", ".gif", ".bmp", ".ico", ".tga"};

	char* CWD_str = getcwd(NULL, 0);
	DIR* CWD = opendir(CWD_str);

	struct dirent* file;

	int i = 0, count = 0;

	while( (file = readdir(CWD)) ) {
		if( file->d_type == DT_REG ){
			int acceptable_format = FALSE;
			for(int i = 0; i < FORMATS; i++){

				if (strstr(file->d_name, supported_formats[i])) {
					//found a texture file
					fflush(stdout);
					acceptable_format = TRUE;
					paths[count] = (char*)malloc(strlen(CWD_str) + strlen(file->d_name) + 2);
					strcpy(paths[count], CWD_str);
					paths[count][strlen(CWD_str)] = '/';
					strcpy(paths[count] + strlen(CWD_str) + 1, file->d_name);
					printf("Found supported file: %s\n", paths[i]);
					if(++count == MAX_FILES){
						printf("You have reached the max number of supported textures: %d", MAX_FILES);
						printf("Exiting texxture loading");
						closedir(CWD);
						return MAX_FILES;
					}
					break;
				}

			}
			if(!acceptable_format){

				printf("Found unsupported file: %s\n", file->d_name);
				fflush(stdout);

			}
		} 
	}
	closedir(CWD);
	free(CWD_str);
	return count;
}

void freePaths(char** paths){
	for(int i = 0; i < MAX_FILES; i++){
		free(paths[i]);
	}
}

unsigned char parseArgs(struct ScreenSpec* spec, int argc, char** argv) {
	//all arguments are formed with a preceding --
	
	//This variable begins at two so that it will evaluate as false 
	//if more than one argument is not an option since it is decremented if there
	//is an invalid argument
	unsigned char successful = 1;

	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "--rows") == 0) {
			spec->rows = atoi(argv[++i]);
			continue;
		}
		if(strcmp(argv[i], "--cols") == 0) {
			spec->cols = atoi(argv[++i]);
			continue;
		}
		if(strcmp(argv[i], "--default-texture") == 0) {
			spec->default_texture_path = argv[++i];
			continue;
		}
		printf("Invalid argument \"%s\"\n", argv[i]);
		printf("\
Required options:\n\
--cols n\t\tNumber of columns when building level\n\
--rows n\t\tNumber of rows when building level\n\
--default-texture path\t\tpath to texture with which to initialize all tiles with\n");
		//return with error
		return 0;
	}	
	//good args, so calculate window size and tile scaling and such
	SDL_DisplayMode display;
	SDL_GetDisplayMode(0, 0, &display);
	
	int i = 0; 

	while( ++i &&  i * spec->rows < display.h * .7 && i * spec->cols < display.w * .7);

	spec->width_px = i * spec->cols;
	spec->height_px = i * spec->rows;
	
	//tilewidth = scale * windowwidth 
	//scale = tilewidth/windowwidth
	spec->tile_scale_factor = ((float)spec->width_px/spec->cols)/spec->width_px;

	return 1;
}

int main(int argc, char** argv) { 
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

	if ( argc < 3 ) exit(2);

	struct ScreenSpec mainScreenSpec;

	if(!parseArgs(&mainScreenSpec, argc, argv)) {
		printf("Aborting\n");
		exit(3);
	}

	printf("Width %d and Height %d\n", mainScreenSpec.width_px, mainScreenSpec.height_px);
	fflush(stdout);

	main_window = SDL_CreateWindow("Teditor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mainScreenSpec.width_px, mainScreenSpec.height_px, 0);

	if (!main_window) {
		printf("Error opening window: %s\n", SDL_GetError());
	}

	SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_SOFTWARE);

	if (!main_renderer) {
		printf("Error creating rendering context: %s\n", SDL_GetError());
	}

	int num_textures = setTexturePaths();

	if (num_textures == 0) {
		printf("No Textures found. Aborting");
		return 255;
	}

	struct Screen screen;
	struct Palette palette;

	screenInit(&screen, main_renderer, mainScreenSpec);
	paletteInit(&palette, paths, num_textures);
	//initialized by setTexturePaths
	freePaths(paths);
	
	while( run == TRUE ){
		SDL_SetRenderDrawColor(main_renderer, 255, 0, 0, 255);
		SDL_SetRenderDrawColor(palette.renderer, 255, 0, 0, 255);

		processEvents(&screen, &palette);
		
		screenUpdate(&screen);
		paletteUpdate(&palette);

		SDL_RenderPresent(main_renderer);
		SDL_RenderPresent(palette.renderer);
	}
	
	screenDestroy(&screen);
	paletteDestroy(&palette);
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyRenderer(palette.renderer);
	SDL_Quit();
	return 0;
}

